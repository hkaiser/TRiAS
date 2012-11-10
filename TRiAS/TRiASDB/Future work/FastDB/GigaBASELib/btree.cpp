//-< BTREE.CPP >-----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:      1-Jan-99    K.A. Knizhnik  * / [] \ *
//                          Last update: 25-Oct-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// B-Tree implementation
//-------------------------------------------------------------------*--------*

#include "gigabase.h"
#include "btree.h"
#include <ctype.h>

static const int keySize[] = {
    sizeof(bool),  // tpBool
    sizeof(int1),  // tpInt1
    sizeof(int2),  // tpInt2
    sizeof(int4),  // tpInt4
    sizeof(int8),  // tpInt8
    sizeof(real4), // tpReal4 
    sizeof(real8)  // tpReal8
};

inline void strlower(char* dst, const char* src)
{
    byte ch;
    do { 
	ch = *src++;
	*dst++ = tolower(ch);
    } while (ch != 0);
}

void dbBtree::find(dbDatabase* db, oid_t treeId, dbSearchContext& sc)
{
    dbGetTie tie;
    dbBtree* tree = (dbBtree*)db->getRow(tie, treeId);
    oid_t rootId = tree->root;
    int   height = tree->height;
    char  firstKeyBuf[dbMaxKeyLen];
    char  lastKeyBuf[dbMaxKeyLen];
#ifdef USE_LOCALE_SETTINGS
    char cnvBuf[dbMaxKeyLen];
#endif
    if (tree->type == dbField::tpString) { 
	if (sc.firstKey != NULL) { 
	    if (tree->caseInsensitive) { 
		strlower(firstKeyBuf, sc.firstKey);
		sc.firstKey = firstKeyBuf;
	    }
#ifdef USE_LOCALE_SETTINGS
	    strxfrm(cnvBuf, sc.firstKey, dbMaxKeyLen);
	    sc.firstKey = cnvBuf;
#endif
	}
	if (sc.lastKey != NULL) { 
	    if (tree->caseInsensitive) { 
		strlower(lastKeyBuf, sc.lastKey);
		sc.lastKey = lastKeyBuf;
	    }
#ifdef USE_LOCALE_SETTINGS
	    // Hack!!! firstKeyBuf is free at rthis moment and cnvBuf is used.
	    // So use firstKeyBuf for convertsion of last key.
	    strxfrm(firstKeyBuf, sc.lastKey, dbMaxKeyLen);
	    sc.lastKey = firstKeyBuf;
#endif
	}

    }
    if (rootId != 0) { 
	dbBtreePage* page = (dbBtreePage*)db->get(rootId);
	page->find(db, sc, tree->type, height);
	db->pool.unfix(page);
    }
}

oid_t dbBtree::allocate(dbDatabase* db, int type, bool caseInsensitive)
{
    oid_t oid = db->allocateId();
    db->setPos(oid, db->allocate(sizeof(dbBtree)) | dbModifiedFlag);
    dbPutTie tie;
    dbBtree* tree = (dbBtree*)db->putRow(tie, oid);
    tree->size = sizeof(dbBtree);
    tree->root = 0;
    tree->height = 0;
    tree->type = type;
    tree->caseInsensitive = caseInsensitive;
    return oid;
}

void dbBtree::insert(dbDatabase* db, oid_t treeId, oid_t recordId, int offs)
{
    dbGetTie treeTie;
    dbBtree* tree = (dbBtree*)db->getRow(treeTie, treeId);
    oid_t rootId = tree->root;
    int   height = tree->height;
    dbBtreePage::item ins;
    dbGetTie tie;

    byte* p = (byte*)db->getRow(tie, recordId);
    if (tree->type == dbField::tpString) { 
	ins.keyLen = ((dbVarying*)(p + offs))->size;
	assert(ins.keyLen <= dbMaxKeyLen);
#ifdef USE_LOCALE_SETTINGS
	char cnvBuf[dbMaxKeyLen];
	if (tree->caseInsensitive) { 
	    ins.keyLen = strxfrm(cnvBuf, 
				 (char*)(p + ((dbVarying*)(p + offs))->offs), 
				 dbMaxKeyLen) + 1;
	    strlower(ins.keyChar, cnvBuf);
	} else { 
	    ins.keyLen = strxfrm(ins.keyChar, 
				 (char*)(p + ((dbVarying*)(p + offs))->offs), 
				 dbMaxKeyLen) + 1;
	}
#else
	if (tree->caseInsensitive) { 
	    strlower(ins.keyChar, (char*)(p + ((dbVarying*)(p + offs))->offs));
	} else { 
	    strcpy(ins.keyChar, (char*)(p + ((dbVarying*)(p + offs))->offs));
	}
#endif
    } else { 
	memcpy(ins.keyChar, p + offs, keySize[tree->type]);
    }
    ins.oid = recordId;

    if (rootId == 0) {
	dbPutTie tie;
        dbBtree* t = (dbBtree*)db->putRow(tie, treeId);
	t->root = dbBtreePage::allocate(db, 0, tree->type, ins);
	t->height = 1;
    } else { 
	int result;
	result = dbBtreePage::insert(db, rootId, tree->type, ins, height);
	assert(result != not_found);
	if (result == overflow) { 
	    dbPutTie tie;
	    dbBtree* t = (dbBtree*)db->putRow(tie, treeId);
	    t->root = dbBtreePage::allocate(db, rootId, tree->type, ins);
	    t->height += 1;
	}
    }
}


void dbBtree::remove(dbDatabase* db, oid_t treeId, oid_t recordId, int offs)
{
    dbGetTie treeTie;
    dbBtree* tree = (dbBtree*)db->getRow(treeTie, treeId);
    dbBtreePage::item rem;
    oid_t rootId = tree->root;
    int   height = tree->height;
    dbGetTie tie;

    byte* p = (byte*)db->getRow(tie, recordId);
    if (tree->type == dbField::tpString) { 
	rem.keyLen = ((dbVarying*)(p + offs))->size;
	assert(rem.keyLen <= dbMaxKeyLen);
#ifdef USE_LOCALE_SETTINGS
	char cnvBuf[dbMaxKeyLen];
	if (tree->caseInsensitive) { 
	    rem.keyLen = strxfrm(cnvBuf, 
				 (char*)(p + ((dbVarying*)(p + offs))->offs), 
				 dbMaxKeyLen) + 1;
	    strlower(rem.keyChar, cnvBuf);
	} else { 
	    rem.keyLen = strxfrm(rem.keyChar, 
				 (char*)(p + ((dbVarying*)(p + offs))->offs), 
				 dbMaxKeyLen) + 1;
	}
#else
	if (tree->caseInsensitive) { 
	    strlower(rem.keyChar, (char*)(p + ((dbVarying*)(p + offs))->offs));
	} else { 
	    strcpy(rem.keyChar, (char*)(p + ((dbVarying*)(p + offs))->offs));
	}
#endif
    } else { 
	memcpy(rem.keyChar, p + offs, keySize[tree->type]);
    }
    rem.oid = recordId;
    
    int result = dbBtreePage::remove(db, rootId, tree->type, rem, height);
    assert(result != not_found);
    if (result == underflow && height != 1) { 
	dbBtreePage* page = (dbBtreePage*)db->get(rootId);
	if (page->nItems == 0) { 	
	    dbPutTie tie;
	    dbBtree* t = (dbBtree*)db->putRow(tie, treeId);
	    if (tree->type == dbField::tpString) { 
		t->root = page->keyStr[0].oid;
	    } else { 
		t->root = page->record[dbBtreePage::maxItems-1];
	    }
	    t->height -= 1;
	    db->freePage(rootId);
	}
	db->pool.unfix(page);
    } else if (result == dbBtree::overflow) { 
	dbPutTie tie;
	dbBtree* t = (dbBtree*)db->putRow(tie, treeId);
	t->root = dbBtreePage::allocate(db, rootId, tree->type, rem);
	t->height += 1;
    }
}

void dbBtree::purge(dbDatabase* db, oid_t treeId) 
{
    dbPutTie tie;
    dbBtree* tree = (dbBtree*)db->putRow(tie, treeId);
    if (tree->root != 0) { 
	dbBtreePage::purge(db, tree->root, tree->type, tree->height);
	tree->root = 0;
	tree->height = 0;
    }
}
    
void dbBtree::drop(dbDatabase* db, oid_t treeId) 
{
    purge(db, treeId);
    db->free(db->getPos(treeId) & ~dbFlagsMask, sizeof(dbBtree));
    db->freeId(treeId);
}
    
void dbBtree::traverseForward(dbDatabase* db, oid_t treeId, 
			      dbAnyCursor* cursor, dbExprNode* condition)
{
    dbGetTie tie;
    dbBtree* tree = (dbBtree*)db->getRow(tie, treeId);
    if (tree->root != 0) { 
	dbBtreePage* page = (dbBtreePage*)db->get(tree->root);
	page->traverseForward(db, cursor, condition, tree->type, tree->height);
	db->pool.unfix(page);
    }
}


void dbBtree::traverseBackward(dbDatabase* db, oid_t treeId,
			       dbAnyCursor* cursor, dbExprNode* condition)
{
    dbGetTie tie;
    dbBtree* tree = (dbBtree*)db->getRow(tie, treeId);
    if (tree->root != 0) { 
	dbBtreePage* page = (dbBtreePage*)db->get(tree->root);
	page->traverseBackward(db, cursor, condition, tree->type, tree->height);
	db->pool.unfix(page);
    }
}

#define CHECK(a, b, inclusion) (a - b >= inclusion)

#define FIND(KEY, TYPE)                                                           \
	if (sc.firstKey != NULL) {                                                \
	    TYPE key = *(TYPE*)sc.firstKey;                                       \
  	    while (l < r)  {                                                      \
		 int i = (l+r) >> 1;                                              \
		 if (CHECK(key, KEY[i], (TYPE)sc.firstKeyInclusion)) {            \
		     l = i+1;                                                     \
		 } else {                                                         \
		     r = i;                                                       \
		 }                                                                \
            }                                                                     \
	    assert(r == l);                                                       \
	}                                                                         \
	if (sc.lastKey != NULL) {                                                 \
	    TYPE key = *(TYPE*)sc.lastKey;                                        \
	    if (height == 0) {                                                    \
		while (l < n) {                                                   \
		    if (CHECK(KEY[l], key, (TYPE)sc.lastKeyInclusion)) {          \
			return false;                                             \
		    }                                                             \
		    if (!sc.condition                                             \
			|| db->evaluate(sc.condition, record[maxItems-1-l],table))\
		    {                                                             \
			if (!sc.cursor->add(record[maxItems-1-l])) {              \
			    return false;                                         \
			}                                                         \
		    }                                                             \
		    l += 1;                                                       \
		}                                                                 \
 	        return true;                                                      \
	    } else {                                                              \
		do {                                                              \
		    dbBtreePage* pg = (dbBtreePage*)db->get(record[maxItems-1-l]);\
		    if (!pg->find(db, sc, type, height)) {                        \
			db->pool.unfix(pg);                                       \
			return false;                                             \
		    }                                                             \
		    db->pool.unfix(pg);                                           \
                    if (l == n) {                                                 \
                        return true;                                              \
                    }                                                             \
		} while(KEY[l++] <= key);                                         \
		return false;                                                     \
	    }                                                                     \
	}                                                                         \
        break

bool dbBtreePage::find(dbDatabase* db, dbSearchContext& sc, int type, int height)
{
    int l = 0, n = nItems, r = n;
    dbTableDescriptor* table = &sc.cursor->table;
    height -= 1;

    switch (type) { 
      case dbField::tpBool:
      case dbField::tpInt1:
	FIND(keyInt1, int1);
      case dbField::tpInt2:
	FIND(keyInt2, int2);
      case dbField::tpInt4:
	FIND(keyInt4, int4);
      case dbField::tpInt8:
	FIND(keyInt8, int8);
#undef  CHECK
#define CHECK(a, b, inclusion) (a > b || (a == b && !inclusion))
      case dbField::tpReal4:
	FIND(keyReal4, real4);
      case dbField::tpReal8:
	FIND(keyReal8, real8);
      case dbField::tpString:
	if (sc.firstKey != NULL) { 
	    char* firstKey = sc.firstKey;
	    while (l < r)  {
		int i = (l+r) >> 1;
		if (strcmp(firstKey, &keyChar[keyStr[i].offs]) 
		    >= sc.firstKeyInclusion) 
		{
		    l = i + 1; 
		} else { 
		    r = i;
		}
	    }
	    assert(r == l); 
	}
	if (sc.lastKey != NULL) { 
	    char* lastKey = sc.lastKey;
	    if (height == 0) { 
		while (l < n) { 
		    if (strcmp(&keyChar[keyStr[l].offs], 
			       lastKey) >= sc.lastKeyInclusion) 
		    { 
			return false;
		    }
		    if (!sc.condition 
			|| db->evaluate(sc.condition, keyStr[l].oid, table))
		    {
			if (!sc.cursor->add(keyStr[l].oid)) { 
			    return false;
			}
		    }
		    l += 1;
		}
	    } else { 
		do {
		    dbBtreePage* pg = (dbBtreePage*)db->get(keyStr[l].oid);
		    if (!pg->find(db, sc, type, height)) {
			db->pool.unfix(pg);
			return false;
		    }
		    db->pool.unfix(pg);
		    if (l == n) { 
			return true;
		    }
		} while (strcmp(&keyChar[keyStr[l++].offs], lastKey) <= 0);
		return false;
	    }
	} else { 
	    if (height == 0) { 
		if (sc.condition) { 
		    while (l < n) { 
			if (db->evaluate(sc.condition, keyStr[l].oid, table)) {
			    if (!sc.cursor->add(keyStr[l].oid)) { 
				return false;
			    }
			}
			l += 1;
		    }
		} else { 
		    while (l < n) { 
			if (!sc.cursor->add(keyStr[l].oid)) { 
			    return false;
			}
			l += 1;
		    }
		}
	    } else {
		do {
		    dbBtreePage* pg = (dbBtreePage*)db->get(keyStr[l].oid);
		    if (!pg->find(db, sc, type, height)) {
			db->pool.unfix(pg);
			return false;
		    }
		    db->pool.unfix(pg);
		} while (++l <= n);
	    }
	}
	return true;
      default:
	assert(false);
    }
    if (height == 0) { 
	if (sc.condition) { 
	    while (l < n) { 
		if (db->evaluate(sc.condition, record[maxItems-1-l], table)) {
		    if (!sc.cursor->add(record[maxItems-1-l])) { 
			return false;
		    }
		}
		l += 1;
	    }
	} else { 
	    while (l < n) { 
		if (!sc.cursor->add(record[maxItems-1-l])) { 
		    return false;
		}
		l += 1;
	    }
	}
    } else { 
	do {
	    dbBtreePage* pg = (dbBtreePage*)db->get(record[maxItems-1-l]);
	    if (!pg->find(db, sc, type, height)) {
		db->pool.unfix(pg);
		return false;
	    }
	    db->pool.unfix(pg);
	} while (++l <= n);
    }
    return true;
}


oid_t dbBtreePage::allocate(dbDatabase* db, oid_t root, int type, item& ins)
{
    oid_t pageId = db->allocatePage();
    dbBtreePage* page = (dbBtreePage*)db->put(pageId);
    page->nItems = 1;
    if (type == dbField::tpString) { 
	page->size = ins.keyLen;
	page->keyStr[0].offs = sizeof(page->keyChar) - ins.keyLen;
	page->keyStr[0].size = ins.keyLen;
	page->keyStr[0].oid = ins.oid;
	page->keyStr[1].oid = root;
	strcpy(&page->keyChar[page->keyStr[0].offs], ins.keyChar); 
    } else { 
	memcpy(page->keyChar, ins.keyChar, keySize[type]);
	page->record[maxItems-1] = ins.oid;
	page->record[maxItems-2] = root;
    }
    db->pool.unfix(page);
    return pageId;
}




#define INSERT(KEY, TYPE) {                                                 \
    TYPE key = ins.KEY;                                                     \
    while (l < r)  {                                                        \
	int i = (l+r) >> 1;                                                 \
	if (key > pg->KEY[i]) l = i+1; else r = i;                          \
    }                                                                       \
    assert(l == r);                                                         \
    /* insert before e[r] */                                                \
    if (--height != 0) {                                                    \
	result = insert(db, pg->record[maxItems-r-1], type, ins, height);   \
	assert(result == dbBtree::done || result == dbBtree::overflow);     \
	if (result == dbBtree::done) {                                      \
      	    db->pool.unfix(pg);                                             \
	    return result;                                                  \
	}                                                                   \
        n += 1;                                                             \
    }                                                                       \
    db->pool.unfix(pg);                                                     \
    pg = (dbBtreePage*)db->put(tie, pageId);                                \
    const int max = sizeof(pg->KEY) / (sizeof(oid_t) + sizeof(TYPE));       \
    if (n < max) {                                                          \
	memmove(&pg->KEY[r+1], &pg->KEY[r], (n - r)*sizeof(TYPE));          \
	memcpy(&pg->record[maxItems-n-1], &pg->record[maxItems-n],          \
	       (n-r)*sizeof(oid_t));                                        \
	pg->KEY[r] = ins.KEY;                                               \
	pg->record[maxItems-r-1] = ins.oid;                                 \
	pg->nItems += 1;                                                    \
	return dbBtree::done;                                               \
    } else { /* page is full then divide page */                            \
	oid_t pageId = db->allocatePage();                                  \
	dbBtreePage* b = (dbBtreePage*)db->put(pageId);                     \
        assert(n == max);                                                   \
	const int m = max/2;                                                \
	if (r < m) {                                                        \
	    memcpy(b->KEY, pg->KEY, r*sizeof(TYPE));                        \
	    b->KEY[r] = ins.KEY;                                            \
	    memcpy(&b->KEY[r+1], &pg->KEY[r], (m-r-1)*sizeof(TYPE));        \
	    memcpy(pg->KEY, &pg->KEY[m-1], (max-m+1)*sizeof(TYPE));         \
	    memcpy(&b->record[maxItems-r], &pg->record[maxItems-r],         \
		   r*sizeof(oid_t));                                        \
	    b->record[maxItems-r-1] = ins.oid;                              \
	    memcpy(&b->record[maxItems-m], &pg->record[maxItems-m+1],       \
		   (m-r-1)*sizeof(oid_t));                                  \
            memmove(&pg->record[maxItems-max+m-1],&pg->record[maxItems-max],\
                    (max-m+1)*sizeof(oid_t));                               \
	} else {                                                            \
	    memcpy(b->KEY, pg->KEY, m*sizeof(TYPE));                        \
	    memcpy(pg->KEY, &pg->KEY[m], (r-m)*sizeof(TYPE));               \
	    pg->KEY[r-m] = ins.KEY;                                         \
	    memcpy(&pg->KEY[r-m+1], &pg->KEY[r], (max-r)*sizeof(TYPE));     \
	    memcpy(&b->record[maxItems-m], &pg->record[maxItems-m],         \
		   m*sizeof(oid_t));                                        \
	    memmove(&pg->record[maxItems-r+m], &pg->record[maxItems-r],     \
		    (r-m)*sizeof(oid_t));                                   \
	    pg->record[maxItems-r+m-1] = ins.oid;                           \
    	    memmove(&pg->record[maxItems-max+m-1],&pg->record[maxItems-max],\
		    (max-r)*sizeof(oid_t));                                 \
	}                                                                   \
	ins.oid = pageId;                                                   \
	ins.KEY = b->KEY[m-1];                                              \
        if (height == 0) {						    \
    	    pg->nItems = max - m + 1;                                       \
  	    b->nItems = m;                                                  \
        } else {                                                            \
    	    pg->nItems = max - m;                                           \
  	    b->nItems = m - 1;                                              \
        }                                                                   \
	db->pool.unfix(b);                                                  \
	return dbBtree::overflow;                                           \
    }                                                                       \
}


int dbBtreePage::insert(dbDatabase* db, oid_t pageId, int type, item& ins, 
			int height)
{
    dbPutTie tie;
    dbBtreePage* pg = (dbBtreePage*)db->get(pageId);
    int result;
    int l = 0, n = pg->nItems, r = n;

    switch (type) { 
      case dbField::tpBool:
      case dbField::tpInt1:
	INSERT(keyInt1, int1);
      case dbField::tpInt2:
	INSERT(keyInt2, int2);
      case dbField::tpInt4:
	INSERT(keyInt4, int4);
      case dbField::tpInt8:
	INSERT(keyInt8, int8);
      case dbField::tpReal4:
	INSERT(keyReal4, real4);
      case dbField::tpReal8:
	INSERT(keyReal8, real8);
      case dbField::tpString:
      {
	char* key = ins.keyChar;
	while (l < r)  {
	    int i = (l+r) >> 1;
	    if (strcmp(key, &pg->keyChar[pg->keyStr[i].offs]) > 0) { 
		l = i+1; 
	    } else { 
		r = i;
	    }
	}
	if (--height != 0) { 
	    result = insert(db, pg->keyStr[r].oid, type, ins, height);
	    assert (result != dbBtree::not_found);
	    if (result != dbBtree::overflow) {
		db->pool.unfix(pg);         
		return result;                              
	    }                                             
	}                 
        db->pool.unfix(pg);
	pg = (dbBtreePage*)db->put(tie, pageId);
	return pg->insertStrKey(db, r, ins, height);
      }
      default:
	assert(false);
    }
    return dbBtree::done;
}

int dbBtreePage::insertStrKey(dbDatabase* db, int r, item& ins, int height)
{
    int n = height != 0 ? nItems+1 : nItems;
    // insert before e[r]
    int len = ins.keyLen;
    if (size + len + (n+1)*sizeof(str) <= sizeof(keyChar)) { 
	memmove(&keyStr[r+1], &keyStr[r], (n-r)*sizeof(str));
	size += len;
	keyStr[r].offs = sizeof(keyChar) - size;
	keyStr[r].size = len;
	keyStr[r].oid = ins.oid;
	memcpy(&keyChar[sizeof(keyChar) - size], ins.keyChar, len);
	nItems += 1;
    } else { // page is full then divide page
	oid_t pageId = db->allocatePage();
	dbBtreePage* b = (dbBtreePage*)db->put(pageId);
	size_t moved = 0;
	size_t inserted = len;
	for (int bn = 0, i = 0; ; bn += 1) { 
	    size_t keyLen;
	    if (bn == r) { 
		keyLen = len;
		inserted = 0;
	    } else { 
		keyLen =  keyStr[i].size;
	    }
	    if (moved != 0 
		&& moved + keyLen > size - keyLen + inserted) 
	    { 
		char insKey[dbMaxKeyLen];
		if (bn <= r) { 
		    memcpy(insKey, ins.keyChar, len);
		}
		if (height == 0) { 
		    strcpy(ins.keyChar, &b->keyChar[b->keyStr[bn-1].offs]);
		    ins.keyLen = b->keyStr[bn-1].size;
		} else {
		    assert(((void)"String fits in the B-Tree page", 
			    moved + (bn+1)*sizeof(str) <= sizeof(keyChar)));
		    if (bn != r) { 
			ins.keyLen = keyLen;
			memcpy(ins.keyChar, &keyChar[keyStr[i].offs], 
			       keyLen);
			b->keyStr[bn].oid = keyStr[i].oid;
			size -= keyLen;
			i += 1;
		    } else {
			b->keyStr[bn].oid = ins.oid;
		    }
		}
		compactify(i);
		if (bn < r || (bn == r && height == 0)) { 
		    memmove(&keyStr[r-i+1], &keyStr[r-i], 
			    (n - r)*sizeof(str));
		    size += len;
		    nItems += 1;
		    assert(((void)"String fits in the B-Tree page", 
			    size + (n-i+1)*sizeof(str) <= sizeof(keyChar)));
		    keyStr[r-i].offs = sizeof(keyChar) - size;
		    keyStr[r-i].size = len;
		    keyStr[r-i].oid = ins.oid;
		    memcpy(&keyChar[keyStr[r-i].offs], insKey, len);
		}
		b->nItems = bn;
		b->size = moved;
		ins.oid = pageId;
		db->pool.unfix(b);
		return dbBtree::overflow;
	    }
	    moved += keyLen;
	    assert(((void)"String fits in the B-Tree page", 
		    moved + (bn+1)*sizeof(str) <= sizeof(keyChar)));
	    b->keyStr[bn].size = keyLen;
	    b->keyStr[bn].offs = sizeof(keyChar) - moved;
	    if (bn == r) { 
		b->keyStr[bn].oid = ins.oid;
		memcpy(&b->keyChar[b->keyStr[bn].offs], ins.keyChar, keyLen);
	    } else { 
		b->keyStr[bn].oid = keyStr[i].oid;
		memcpy(&b->keyChar[b->keyStr[bn].offs], 
		       &keyChar[keyStr[i].offs], keyLen);
		size -= keyLen;
		i += 1;
	    }
	}
    }
    return size + sizeof(str)*(nItems+1) < sizeof(keyChar)/2
	? dbBtree::underflow : dbBtree::done;
}

void dbBtreePage::compactify(int m)
{
    int i, j, offs, len, n = nItems;
    int size[dbPageSize];
    int index[dbPageSize];
    if (m == 0) { 
	return;
    }
    if (m < 0) {
	m = -m;
	for (i = 0; i < n-m; i++) { 
	    len = keyStr[i].size;
	    size[keyStr[i].offs + len] = len;
	    index[keyStr[i].offs + len] = i;
	}	
	for (; i < n; i++) { 
	    len = keyStr[i].size;
	    size[keyStr[i].offs + len] = len;
	    index[keyStr[i].offs + len] = -1;
	}
    } else { 
	for (i = 0; i < m; i++) { 
	    len = keyStr[i].size;
	    size[keyStr[i].offs + len] = len;
	    index[keyStr[i].offs + len] = -1;
	}
	for (; i < n; i++) { 
	    len = keyStr[i].size;
	    size[keyStr[i].offs + len] = len;
	    index[keyStr[i].offs + len] = i - m;
	    keyStr[i-m].oid = keyStr[i].oid;
	    keyStr[i-m].size = len;
	}	
	keyStr[i-m].oid = keyStr[i].oid;
    }
    nItems = n -= m;
    for (offs = sizeof(keyChar), i = offs; n != 0; i -= len) { 
	len = size[i];
	j = index[i];
	if (j >= 0) {
	    offs -= len;
	    n -= 1;
	    keyStr[j].offs = offs;
	    if (offs != i - len) { 
		memmove(&keyChar[offs], &keyChar[i - len], len);
	    }
	}
    }
}

int dbBtreePage::removeStrKey(int r)
{
    int len = keyStr[r].size;
    int offs = keyStr[r].offs;
    memmove(keyChar + sizeof(keyChar) - size + len, 
	    keyChar + sizeof(keyChar) - size, 
	    size - sizeof(keyChar) + offs);
    memcpy(&keyStr[r], &keyStr[r+1], (nItems-r)*sizeof(str));
    nItems -= 1;
    size -= len;
    for (int i = nItems; --i >= 0; ) { 
	if (keyStr[i].offs < offs) { 
	    keyStr[i].offs += len;
	}
    }	   
    return size + sizeof(str)*(nItems+1) < sizeof(keyChar)/2
	? dbBtree::underflow : dbBtree::done;
}

int dbBtreePage::replaceStrKey(dbDatabase* db, int r, item& ins, int height)
{
    ins.oid = keyStr[r].oid;
    removeStrKey(r);
    return insertStrKey(db, r, ins, height);
}

int dbBtreePage::handlePageUnderflow(dbDatabase* db, int r, int type, item& rem,
				     int height)
{
    dbPutTie tie;
    if (type == dbField::tpString) { 
	dbBtreePage* a = (dbBtreePage*)db->put(tie, keyStr[r].oid);
	int an = a->nItems;
	if (r < int(nItems)) { // exists greater page
	    dbBtreePage* b = (dbBtreePage*)db->get(keyStr[r+1].oid);
	    int bn = b->nItems; 
	    size_t merged_size = (an+bn)*sizeof(str) + a->size + b->size;
	    if (height != 1) { 
		merged_size += keyStr[r].size + sizeof(str)*2;
	    }
	    if (merged_size > sizeof(keyChar)) {
		// reallocation of nodes between pages a and b
		int i, j, k;
		dbPutTie tie;
		db->pool.unfix(b);
		b = (dbBtreePage*)db->put(tie, keyStr[r+1].oid);
		size_t size_a = a->size;
		size_t size_b = b->size;
		if (height != 1) { 
		    size_a += keyStr[r].size;
		}
		for (i = 0; size_a + b->keyStr[i].size < size_b; i++) { 
		    int len = b->keyStr[i].size;
		    size_a += len;
		    size_b -= len;
		}
		int result = dbBtree::done;
		if (i > 0) { 
		    k = i;
		    if (height != 1) { 
			int len = keyStr[r].size;
			a->size += len;
			a->keyStr[an].offs = sizeof(a->keyChar) - a->size;
			a->keyStr[an].size = len;
			memcpy(a->keyChar + a->keyStr[an].offs,
			       keyChar + keyStr[r].offs, len);
			k -= 1;
			an += 1;
			a->keyStr[an+k].oid = b->keyStr[k].oid;
			b->size -= b->keyStr[k].size;
		    }
		    for (j = 0; j < k; j++) { 
			int len = b->keyStr[j].size;
			a->size += len;
			b->size -= len;
			a->keyStr[an].offs = sizeof(a->keyChar) - a->size;
			a->keyStr[an].size = len;
			a->keyStr[an].oid = b->keyStr[j].oid;
			memcpy(a->keyChar + a->keyStr[an].offs,
			       b->keyChar + b->keyStr[j].offs, len);
			an += 1;
		    }
		    memcpy(rem.keyChar, b->keyChar + b->keyStr[i-1].offs, 
			   b->keyStr[i-1].size);
		    rem.keyLen = b->keyStr[i-1].size;
		    result = replaceStrKey(db, r, rem, height);
		    a->nItems = an;
		    b->compactify(i);
		}
		return result;
	    } else { // merge page b to a
		if (height != 1) { 
		    a->size += a->keyStr[an].size = keyStr[r].size;
		    a->keyStr[an].offs = sizeof(keyChar) - a->size;
		    memcpy(&a->keyChar[a->keyStr[an].offs], 
			   &keyChar[keyStr[r].offs], keyStr[r].size);
		    an += 1;
		    a->keyStr[an+bn].oid = b->keyStr[bn].oid;
		}
		for (int i = 0; i < bn; i++, an++) { 
		    a->keyStr[an] = b->keyStr[i];
		    a->keyStr[an].offs -= a->size;
		}
		a->size += b->size;
		a->nItems = an;
		memcpy(a->keyChar + sizeof(keyChar) - a->size,
		       b->keyChar + sizeof(keyChar) - b->size,
		       b->size);
		db->pool.unfix(b);
		db->freePage(keyStr[r+1].oid);
		keyStr[r+1].oid = keyStr[r].oid;
		return removeStrKey(r);
	    }
	} else { // page b is before a
	    dbBtreePage* b = (dbBtreePage*)db->get(keyStr[r-1].oid);
	    int bn = b->nItems; 
	    size_t merged_size = (an+bn)*sizeof(str) + a->size + b->size;
	    if (height != 1) { 
		merged_size += keyStr[r-1].size + sizeof(str)*2;
	    }
	    if (merged_size > sizeof(keyChar)) {
		// reallocation of nodes between pages a and b
		dbPutTie tie;
		int i, j, k;
		db->pool.unfix(b);
		b = (dbBtreePage*)db->put(tie, keyStr[r-1].oid);
		size_t size_a = a->size;
		size_t size_b = b->size;
		if (height != 1) { 
		    size_a += keyStr[r-1].size;
		}
		for (i = 0; size_a + b->keyStr[bn-i-1].size < size_b; i++) { 
		    int len = b->keyStr[bn-i-1].size;
		    size_a += len;
		    size_b -= len;
		}

		int result = dbBtree::done;
		if (i > 0) { 
		    k = i;
		    assert(i < bn);
		    if (height != 1) { 
			memmove(&a->keyStr[i], a->keyStr, (an+1)*sizeof(str));
			k -= 1;
			a->keyStr[k].oid = b->keyStr[bn].oid;
			int len = keyStr[r-1].size;
			a->keyStr[k].size = len;
			a->size += len;
			a->keyStr[k].offs = sizeof(keyChar) - a->size;
			memcpy(&a->keyChar[a->keyStr[k].offs], 
			       &keyChar[keyStr[r-1].offs], len);
		    } else { 
			memmove(&a->keyStr[i], a->keyStr, an*sizeof(str));
		    }
		    for (j = 0; j < k; j++) { 
			int len = b->keyStr[bn-k+j].size;
			a->size += len;
			b->size -= len;
			a->keyStr[j].offs = sizeof(a->keyChar) - a->size;
			a->keyStr[j].size = len;
			a->keyStr[j].oid = b->keyStr[bn-k+j].oid;
			memcpy(a->keyChar + a->keyStr[j].offs,
			       b->keyChar + b->keyStr[bn-k+j].offs, len);
		    }
		    an += i;
		    a->nItems = an;
		    memcpy(rem.keyChar, b->keyChar + b->keyStr[bn-k-1].offs, 
			   b->keyStr[bn-k-1].size);
		    rem.keyLen =  b->keyStr[bn-k-1].size;
		    result = replaceStrKey(db, r-1, rem, height);
		    b->compactify(-i);
		}
		return result;
	    } else { // merge page b to a
		if (height != 1) { 
		    memmove(a->keyStr + bn + 1, a->keyStr, (an+1)*sizeof(str));
		    a->size += a->keyStr[bn].size = keyStr[r-1].size;
		    a->keyStr[bn].offs = sizeof(keyChar) - a->size;
		    a->keyStr[bn].oid = b->keyStr[bn].oid;
		    memcpy(&a->keyChar[a->keyStr[bn].offs], 
			   &keyChar[keyStr[r-1].offs], keyStr[r-1].size);
		    an += 1;
		} else { 
		    memmove(a->keyStr + bn, a->keyStr, an*sizeof(str));
		}
		for (int i = 0; i < bn; i++) { 
		    a->keyStr[i] = b->keyStr[i];
		    a->keyStr[i].offs -= a->size;
		}
		an += bn;
		a->nItems = an;
		a->size += b->size;
		memcpy(a->keyChar + sizeof(keyChar) - a->size,
		       b->keyChar + sizeof(keyChar) - b->size,
		       b->size);
		db->pool.unfix(b);
		db->freePage(keyStr[r-1].oid);
		return removeStrKey(r-1);
	    }
	}
    } else { 
	dbBtreePage* a = (dbBtreePage*)db->put(tie, record[maxItems-r-1]);
	int an = a->nItems;
	int itemSize = keySize[type];
	if (r < int(nItems)) { // exists greater page
	    dbBtreePage* b = (dbBtreePage*)db->get(record[maxItems-r-2]);
	    int bn = b->nItems; 
	    assert(bn >= an);
	    if (height != 1) { 
		memcpy(a->keyChar + an*itemSize, keyChar + r*itemSize,
		       itemSize);
		an += 1;
		bn += 1;
	    }
	    size_t merged_size = (an+bn)*(sizeof(oid_t) + itemSize);
	    if (merged_size > sizeof(keyChar)) { 
		// reallocation of nodes between pages a and b
		int i = bn - ((an + bn) >> 1);
		dbPutTie tie;
		db->pool.unfix(b);
		b = (dbBtreePage*)db->put(tie, record[maxItems-r-2]);
		memcpy(a->keyChar + an*itemSize, b->keyChar, i*itemSize);
		memcpy(b->keyChar, b->keyChar + i*itemSize, (bn-i)*itemSize);
		memcpy(&a->record[maxItems-an-i], &b->record[maxItems-i], 
		       i*sizeof(oid_t));
		memmove(&b->record[maxItems-bn+i], &b->record[maxItems-bn], 
			(bn-i)*sizeof(oid_t));
		memcpy(keyChar + r*itemSize,  a->keyChar + (an+i-1)*itemSize,
		       itemSize);
		b->nItems -= i;
		a->nItems += i;
		return dbBtree::done;
	    } else { // merge page b to a  
		memcpy(a->keyChar + an*itemSize, b->keyChar, bn*itemSize);
		memcpy(&a->record[maxItems-an-bn], &b->record[maxItems-bn],
		       bn*sizeof(oid_t));
		db->pool.unfix(b);
		db->freePage(record[maxItems-r-2]);
		memmove(&record[maxItems-nItems], &record[maxItems-nItems-1], 
			(nItems - r - 1)*sizeof(oid_t));
		memcpy(keyChar + r*itemSize, keyChar + (r+1)*itemSize,
		       (nItems - r - 1)*itemSize);
		a->nItems += bn;
		nItems -= 1;
		return (nItems+1)*(itemSize + sizeof(oid_t)) < sizeof(keyChar)/2
		    ? dbBtree::underflow : dbBtree::done;
	    }
	} else { // page b is before a
	    dbBtreePage* b = (dbBtreePage*)db->get(record[maxItems-r]);
	    int bn = b->nItems; 
	    assert(bn >= an);
	    if (height != 1) { 
		an += 1;
		bn += 1;
	    }
	    size_t merged_size = (an+bn)*(sizeof(oid_t) + itemSize);
	    if (merged_size > sizeof(keyChar)) { 
		// reallocation of nodes between pages a and b
		int i = bn - ((an + bn) >> 1);
		dbPutTie tie;
		db->pool.unfix(b);
		b = (dbBtreePage*)db->put(tie, record[maxItems-r]);
		memmove(a->keyChar + i*itemSize, a->keyChar, an*itemSize);
		memcpy(a->keyChar, b->keyChar + (bn-i)*itemSize, i*itemSize);
		memcpy(&a->record[maxItems-an-i], &a->record[maxItems-an], 
		       an*sizeof(oid_t));
		memcpy(&a->record[maxItems-i], &b->record[maxItems-bn], 
		       i*sizeof(oid_t));
		if (height != 1) { 
		    memcpy(a->keyChar + (i-1)*itemSize, keyChar + (r-1)*itemSize,
			   itemSize);
		}
		memcpy(keyChar + (r-1)*itemSize, b->keyChar + (bn-i-1)*itemSize,
		       itemSize);
		b->nItems -= i;
		a->nItems += i;
		return dbBtree::done;
	    } else { // merge page b to a
		memmove(a->keyChar + bn*itemSize, a->keyChar, an*itemSize);
		memcpy(a->keyChar, b->keyChar, bn*itemSize);
		memcpy(&a->record[maxItems-an-bn], &a->record[maxItems-an],
		       an*sizeof(oid_t));
		memcpy(&a->record[maxItems-bn], &b->record[maxItems-bn], 
		       bn*sizeof(oid_t));
		if (height != 1) { 
		    memcpy(a->keyChar + (bn-1)*itemSize, keyChar + (r-1)*itemSize,
			   itemSize);
		}
		db->pool.unfix(b);
		db->freePage(record[maxItems-r]);
		record[maxItems-r] = record[maxItems-r-1];
		a->nItems += bn;
		nItems -= 1;
		return (nItems+1)*(itemSize + sizeof(oid_t)) < sizeof(keyChar)/2
		    ? dbBtree::underflow : dbBtree::done;
	    }
	}
    }
}

#define REMOVE(KEY,TYPE) {                                                        \
    TYPE key = rem.KEY;                                                           \
    while (l < r)  {                                                              \
	i = (l+r) >> 1;                                                           \
	if (key > pg->KEY[i]) l = i+1; else r = i;                                \
    }                                                                             \
    if (--height == 0) {                                                          \
        oid_t oid = rem.oid;                                                      \
	while (r < n) {                                                           \
	    if (key == pg->KEY[r]) {                                              \
		if (pg->record[maxItems-r-1] == oid) {                            \
		    db->pool.unfix(pg);                                           \
		    pg = (dbBtreePage*)db->put(tie, pageId);                      \
		    memcpy(&pg->KEY[r], &pg->KEY[r+1], (n - r - 1)*sizeof(TYPE)); \
		    memmove(&pg->record[maxItems-n+1], &pg->record[maxItems-n],   \
			    (n - r - 1)*sizeof(oid_t));                           \
		    pg->nItems = --n;                                             \
		    return n*(sizeof(TYPE)+sizeof(oid_t)) < sizeof(pg->keyChar)/2 \
			? dbBtree::underflow : dbBtree::done;                     \
		}                                                                 \
	    } else {                                                              \
		break;                                                            \
	    }                                                                     \
	    r += 1;                                                               \
	}                                                                         \
        db->pool.unfix(pg);                                                       \
        return dbBtree::not_found;                                                \
    }                                                                             \
    break;                                                                        \
}

int dbBtreePage::remove(dbDatabase* db, oid_t pageId,  int type, item& rem, 
			int height)
{
    dbBtreePage* pg = (dbBtreePage*)db->get(pageId);
    dbPutTie tie;
    int i, n = pg->nItems, l = 0, r = n;

    switch (type) { 
      case dbField::tpBool:
      case dbField::tpInt1:
	REMOVE(keyInt1, int1);
      case dbField::tpInt2:
	REMOVE(keyInt2, int2);
      case dbField::tpInt4:
	REMOVE(keyInt4, int4);
      case dbField::tpInt8:
	REMOVE(keyInt8, int8);
      case dbField::tpReal4:
	REMOVE(keyReal4, real4);
      case dbField::tpReal8:
	REMOVE(keyReal8, real8);
      case dbField::tpString:
      { 
	char* key = rem.keyChar;
	while (l < r)  {
	    i = (l+r) >> 1;
	    if (strcmp(key, &pg->keyChar[pg->keyStr[i].offs]) > 0) { 
		l = i+1; 
	    } else { 
		r = i;
	    }
	}
	if (--height != 0) {
	    do {  
		switch (remove(db, pg->keyStr[r].oid, type, rem, height)) {
		  case dbBtree::underflow: 
		    db->pool.unfix(pg);
		    pg = (dbBtreePage*)db->put(tie, pageId);
		    return pg->handlePageUnderflow(db, r, type, rem, height);
 		  case dbBtree::done:
		    db->pool.unfix(pg);
		    return dbBtree::done;
 		  case dbBtree::overflow:
		    db->pool.unfix(pg);
		    pg = (dbBtreePage*)db->put(tie, pageId);
		    return pg->insertStrKey(db, r, rem, height);
		}
	    } while (++r <= n);
	} else { 
	    while (r < n) { 
		if (strcmp(key, &pg->keyChar[pg->keyStr[r].offs]) == 0) { 
		    if (pg->keyStr[r].oid == rem.oid) { 
			db->pool.unfix(pg);
			pg = (dbBtreePage*)db->put(tie, pageId);
			return pg->removeStrKey(r);
		    }
		} else { 
		    break;
		}
		r += 1;
	    }
	}
	db->pool.unfix(pg);
	return dbBtree::not_found;
      }
      default:
	assert(false);
    }
    do { 
	switch (remove(db, pg->record[maxItems-r-1], type, rem, height)) {
	  case dbBtree::underflow: 
	    db->pool.unfix(pg);
	    pg = (dbBtreePage*)db->put(tie, pageId);
	    return pg->handlePageUnderflow(db, r, type, rem, height);
	  case dbBtree::done:
	    db->pool.unfix(pg);
	    return dbBtree::done;
	} 
    } while (++r <= n);

    db->pool.unfix(pg);
    return dbBtree::not_found;
}


void dbBtreePage::purge(dbDatabase* db, oid_t pageId, int type, int height)
{
    if (--height != 0) { 
	dbBtreePage* pg = (dbBtreePage*)db->get(pageId);
	int n = pg->nItems+1;
	if (type == dbField::tpString) { // page of strings
	    while (--n >= 0) { 
		purge(db, pg->keyStr[n].oid, type, height);
	    }
	} else { 
	    while (--n >= 0) { 
		purge(db, pg->record[maxItems-n-1], type, height);
	    }
	}
	db->pool.unfix(pg);
    } 
    db->freePage(pageId);
}

bool dbBtreePage::traverseForward(dbDatabase* db, dbAnyCursor* cursor, 
				  dbExprNode* condition, int type, int height)
{
    int n = nItems;
    if (--height != 0) {
	if (type == dbField::tpString) { // page of strings
	    for (int i = 0; i <= n; i++) { 
		dbBtreePage* pg = (dbBtreePage*)db->get(keyStr[i].oid);
		if (!pg->traverseForward(db, cursor, condition, type, height)) { 
		    db->pool.unfix(pg);
		    return false;
		}
		db->pool.unfix(pg);
	    }
	} else { 
	    for (int i = 0; i <= n; i++) { 
		dbBtreePage* pg = (dbBtreePage*)db->get(record[maxItems-i-1]);
		if (!pg->traverseForward(db, cursor, condition, type, height)) { 
		    db->pool.unfix(pg);
		    return false;
		}
		db->pool.unfix(pg);
	    }
	}
    } else { 
	if (type != dbField::tpString) { // page of scalars
	    if (condition == NULL) { 
		for (int i = 0; i < n; i++) { 
		    if (!cursor->add(record[maxItems-1-i])) { 
			return false;
		    }
		}
	    } else { 
		dbTableDescriptor* table = &cursor->table;
		for (int i = 0; i < n; i++) { 
		    if (db->evaluate(condition, record[maxItems-1-i], table)) { 
			if (!cursor->add(record[maxItems-1-i])) { 
			    return false;
			}
		    }
		}
	    }
	} else { // page of strings
	    if (condition == NULL) { 
		for (int i = 0; i < n; i++) { 
		    if (!cursor->add(keyStr[i].oid)) { 
			return false;
		    }
		}
	    } else { 
		dbTableDescriptor* table = &cursor->table;
		for (int i = 0; i < n; i++) { 
		    if (db->evaluate(condition, keyStr[i].oid, table)) { 
			if (!cursor->add(keyStr[i].oid)) { 
			    return false;
			}
		    }
		}
	    }	
	}
    }
    return true;
}


bool dbBtreePage::traverseBackward(dbDatabase* db, dbAnyCursor* cursor, 
				   dbExprNode* condition, int type, int height)
{
    int n = nItems;
    if (--height != 0) {
	if (type == dbField::tpString) { // page of strings
	    do {
		dbBtreePage* pg = (dbBtreePage*)db->get(keyStr[n].oid);
		if (!pg->traverseBackward(db, cursor, condition, type, height)) { 
		    db->pool.unfix(pg);
		    return false;
		}
		db->pool.unfix(pg);
	    } while (--n >= 0);
	} else { 
	    do { 
		dbBtreePage* pg = (dbBtreePage*)db->get(record[maxItems-n-1]);
		if (!pg->traverseBackward(db, cursor, condition, type, height)) { 
		    db->pool.unfix(pg);
		    return false;
		}
		db->pool.unfix(pg);
	    } while (--n >= 0);
	}
    } else { 
	if (type != dbField::tpString) { // page of scalars
	    if (condition == NULL) { 
		while (--n >= 0) { 
		    if (!cursor->add(record[maxItems-1-n])) { 
			return false;
		    }
		}
	    } else { 
		dbTableDescriptor* table = &cursor->table;
		while (--n >= 0) { 
		    if (db->evaluate(condition, record[maxItems-1-n], table)) { 
			if (!cursor->add(record[maxItems-1-n])) { 
			    return false;
			}
		    }
		}
	    }
	} else { // page of strings
	    if (condition == NULL) { 
		while (--n >= 0) { 
		    if (!cursor->add(keyStr[n].oid)) { 
			return false;
		    }
		}
	    } else { 
		dbTableDescriptor* table = &cursor->table;
		while (--n >= 0) { 
		    if (db->evaluate(condition, keyStr[n].oid, table)) { 
			if (!cursor->add(keyStr[n].oid)) { 
			    return false;
			}
		    }
		}
	    }	
	}
    }
    return true;
}
