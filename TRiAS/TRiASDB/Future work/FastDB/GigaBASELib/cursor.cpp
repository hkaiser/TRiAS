//-< CURSOR.H >------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 21-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Table cursor
//-------------------------------------------------------------------*--------*

#include "gigabase.h"
#include "compiler.h"
#include <ctype.h>

inline void dbSelection::reset()
{
    for (segment *next, *seg = first; seg != NULL; seg = next) { 
	next = seg->next;
	delete seg;
    }
    first = last = curr = NULL;
    nRows = 0;
    pos = 0;
}

void dbSelection::reverse() 
{
    segment *next, *seg;
    for (seg = first; seg != NULL; seg = next) { 
	next = seg->next;
	seg->next = seg->prev;
	seg->prev = next;
	for (int l = 0, r = seg->nRows-1; l < r; l++, r--) { 
	    oid_t oid = seg->rows[l];
	    seg->rows[l] = seg->rows[r];
	    seg->rows[r] = oid;
	}
    }
    seg = first;
    first = last;
    last = seg;
}

int dbSelection::compare(dbRecord* a, dbRecord* b, dbOrderByNode* order)
{
    char* p = (char*)a;
    char* q = (char*)b;
    int diff = 0;
    do { 
	int offs = order->field->dbsOffs;
	switch (order->field->type) { 
	  case dbField::tpBool:
	    diff = *(bool*)(p + offs) - *(bool*)(q + offs);
	    break;
	  case dbField::tpInt1:
	    diff = *(int1*)(p + offs) - *(int1*)(q + offs);
	    break;
	  case dbField::tpInt2:
	    diff = *(int2*)(p + offs) - *(int2*)(q + offs);
	    break;
	  case dbField::tpInt4:
	  case dbField::tpArray: // compre arrays length
	    diff = *(int4*)(p + offs) - *(int4*)(q + offs);
	    break;
	  case dbField::tpInt8:
	    diff = *(int8*)(p + offs) < *(int8*)(q + offs) ? -1 :
		*(int8*)(p + offs) == *(int8*)(q + offs) ? 0 : 1;
	    break;
	  case dbField::tpReal4:
	    diff = *(real4*)(p + offs) < *(real4*)(q + offs) ? -1 :
		*(real4*)(p + offs) == *(real4*)(q + offs) ? 0 : 1;
	    break;
	  case dbField::tpReal8:
	    diff = *(real8*)(p + offs) < *(real8*)(q + offs) ? -1 :
		*(real8*)(p + offs) == *(real8*)(q + offs) ? 0 : 1;
	    break;
	  case dbField::tpString:
#ifdef USE_LOCALE_SETTINGS
	    diff = strcoll(p + ((dbVarying*)(p + offs))->offs, 
			   q + ((dbVarying*)(q + offs))->offs);
#else
	    diff = strcmp(p + ((dbVarying*)(p + offs))->offs, 
			  q + ((dbVarying*)(q + offs))->offs);
#endif
	    break;
	  default:
	    assert(false);
	}
	if (!order->ascent) { 
	    diff = -diff;
	}
    } while (diff == 0 && (order = order->next) != NULL);

    return diff;
}

struct dbSortRecord { 
    oid_t  oid;
    int4   high;
    int4   low;
};

struct dbSortContext { 
    dbDatabase*    db;
    dbOrderByNode* order;
};

inline int8 packStrKey(byte* p) 
{
#ifdef USE_LOCALE_SETTINGS
    char buf[8];
    strxfrm(buf, (char*)p, sizeof buf);
    p = (byte*)buf;
#endif
    int8 pkey = 0;
    for (int i = 0; i < 8 && p[i] != 0; i++) { 
        pkey |= int8(p[i]) << ((7-i)*8);
    }
    // As far as signed comparison is used for packed key, 
    // and strcmp compares characters as unsign, we should make this 
    // correction
    return pkey - (int8(-1) << 63);
}


static int cmpIntKey(void const* a, void const* b) 
{ 
    return ((dbSortRecord*)a)->high - ((dbSortRecord*)b)->high;
}

static int cmpLongKey(void const* a, void const* b) 
{ 
    return ((dbSortRecord*)a)->high == ((dbSortRecord*)b)->high
	?  ((dbSortRecord*)a)->low  - ((dbSortRecord*)b)->low
	:  ((dbSortRecord*)a)->high - ((dbSortRecord*)b)->high;
}

static dbThreadContext<dbSortContext> sortThreadContext;

int dbSelection::exactKeyCmp(void const* a, void const* b) 
{
    dbGetTie ta, tb;
    dbSortContext* ctx = sortThreadContext.get();
    return compare(ctx->db->getRow(ta, ((dbSortRecord*)a)->oid),
		   ctx->db->getRow(tb, ((dbSortRecord*)b)->oid),
		   ctx->order);				
}


void dbSelection::sort(dbDatabase* db, dbOrderByNode* order)
{
    int i, j, k, n = nRows;
    dbSortRecord* keys = new dbSortRecord[n];
    segment* seg = first;
    dbGetTie tie;
    byte* p;
    int offs = order->field->dbsOffs;

    TRACE_MSG(("Sort %d records\n", n));

    switch (order->field->type) {
      case dbField::tpBool:
      case dbField::tpInt1:
	for (i = 0; seg != NULL; seg = seg->next) { 
	    for (j = 0, k = seg->nRows; j < k; j++, i++) { 
		p = (byte*)db->getRow(tie, seg->rows[j]);
		int4 val = *(int1*)(p + offs);
		keys[i].high = order->ascent ? val : -val;
		keys[i].low = 0;
		keys[i].oid = seg->rows[j];
	    }
	}
	qsort(keys, n, sizeof(dbSortRecord), cmpIntKey);
	break;
      case dbField::tpInt2:
	for (i = 0; seg != NULL; seg = seg->next) { 
	    for (j = 0, k = seg->nRows; j < k; j++, i++) { 
		p = (byte*)db->getRow(tie, seg->rows[j]);
		int4 val = *(int2*)(p + offs);
		keys[i].high = order->ascent ? val : -val;
		keys[i].low = 0;
		keys[i].oid = seg->rows[j];
	    }
	}
	qsort(keys, n, sizeof(dbSortRecord), cmpIntKey);
	break;
      case dbField::tpInt4:
      case dbField::tpReal4:
      case dbField::tpArray:
	for (i = 0; seg != NULL; seg = seg->next) { 
	    for (j = 0, k = seg->nRows; j < k; j++, i++) { 
		p = (byte*)db->getRow(tie, seg->rows[j]);
		int4 val = *(int4*)(p + offs);
		keys[i].high = order->ascent ? val : -val;
		keys[i].low = 0;
		keys[i].oid = seg->rows[j];
	    }
	}
	qsort(keys, n, sizeof(dbSortRecord), cmpIntKey);
	break;
      case dbField::tpInt8:
      case dbField::tpReal8:
	for (i = 0; seg != NULL; seg = seg->next) { 
	    for (j = 0, k = seg->nRows; j < k; j++, i++) { 
		p = (byte*)db->getRow(tie, seg->rows[j]);
		int8 val = *(int8*)(p + offs);
		if (!order->ascent) { 
		    val = -val;
		}
		keys[i].high = int8_high_part(val);
		keys[i].low = int8_low_part(val);
		keys[i].oid = seg->rows[j];
	    }
	}
	qsort(keys, n, sizeof(dbSortRecord), cmpLongKey);
	break;
      case dbField::tpString:
	for (i = 0; seg != NULL; seg = seg->next) { 
	    for (j = 0, k = seg->nRows; j < k; j++, i++) { 
		byte* p = (byte*)db->getRow(tie, seg->rows[j]);
		int8 val = packStrKey(p + ((dbVarying*)(p + offs))->offs);
		if (!order->ascent) { 
		    val = -val;
		}
		keys[i].high = int8_high_part(val);
		keys[i].low = int8_low_part(val);
		keys[i].oid = seg->rows[j];
	    }
	}
	qsort(keys, n, sizeof(dbSortRecord), cmpLongKey);
	break;
      default:
	assert(false);
    }
    if (order->next != NULL || order->field->type == dbField::tpString) {
	dbSortContext ctx;
	ctx.db = db;
	ctx.order = order;
	sortThreadContext.set(&ctx);
	for (i = 0, k = 0; i < n; i = j) { 
	    for (j = i+1; j < n && keys[j].high == keys[i].high
		 && keys[j].low == keys[i].low; j++);
	    if (j > i + 1) {
		qsort(keys + i, j - i, sizeof(dbSortRecord), exactKeyCmp);
	    }
	}
    }
    if (n != 0) { 
	for (i = 0, j = 0, seg = first, k = seg->nRows; i < n; i++, j++) { 
	    if (j == k) { 
		seg = seg->next;
		k = seg->nRows;
		j = 0;
	    }
	    seg->rows[j] = keys[i].oid;
	}
    }
    delete[] keys;
}			      


void dbAnyCursor::setCurrent(dbAnyReference const& ref)
{
    assert(ref.oid != 0);
    reset();
    table.db->threadContext.get()->cursors.link(this);
    currId = ref.oid;
    selection.nRows = 1;
    if (prefetch) { 
	fetch();
    }
}


void dbAnyCursor::remove()
{
    assert(type == dbCursorForUpdate && currId != 0);
    if (allRecords) { 
	dbRecord rec;
	table.db->getHeader(rec, currId);
	table.db->remove(&table, currId);
	currId = rec.next;
    } else { 
	table.db->remove(&table, currId);
	if (selection.curr != NULL) { 
	    if (--selection.curr->nRows == 0) { 
		dbSelection::segment* next = selection.curr->next;
		if (selection.curr->prev != NULL) { 
		    selection.curr->prev->next = next;
		} else { 
		    selection.first = next;
		}
		if (next != NULL) { 
		    next->prev = selection.curr->prev;
		    currId = next->rows[0];
		    delete selection.curr;
		    selection.curr = next;
		    selection.pos = 0;
		} else { 
		    selection.last = selection.curr->prev;
		    delete selection.curr;
		    if ((selection.curr = selection.last) != NULL) { 
			selection.pos = selection.curr->nRows-1;
			currId = selection.curr->rows[selection.pos];
		    } else { 
			currId = 0;
		    }
		}
	    } else { 
		if (selection.pos < selection.curr->nRows) { 
		    memcpy(selection.curr->rows + selection.pos, 
			   selection.curr->rows + selection.pos + 1, 
			   (selection.curr->nRows - selection.pos)
			    *sizeof(oid_t));
		} else { 
		    selection.pos -= 1;
		}
		currId = selection.curr->rows[selection.pos];
	    }    
	} else { 
	    currId = 0;
	}
    }
    if (currId != 0) {
	fetch();	
    }
}


void dbAnyCursor::removeAllSelected()
{
    assert(type == dbCursorForUpdate);
    if (allRecords) { 
	removeAll();
    } else if (selection.first != NULL) { 
        dbSelection::segment* curr;
	for (curr = selection.first; curr != NULL; curr = curr->next) { 
	    for (int i = 0, n = curr->nRows; i < n; i++) { 
		table.db->remove(&table, curr->rows[i]);
	    }
	}
	reset();
    } else if (currId != 0) {	
	table.db->remove(&table, currId);
	currId = 0;
    }
}


bool dbAnyCursor::gotoNext() 
{ 
    if (allRecords) { 
	if (currId != 0) { 
	    dbRecord rec;
	    table.db->getHeader(rec, currId);
	    if (rec.next != 0) {
		currId = rec.next;
		return true;
	    } 
	}
    } else if (selection.curr != NULL) { 
	if (++selection.pos == selection.curr->nRows) { 
	    if (selection.curr->next == NULL) { 
		selection.pos -= 1;
		return false;
	    }
	    selection.pos = 0;
	    selection.curr = selection.curr->next;
	}
	currId = selection.curr->rows[selection.pos];
	return true;
    }  
    return false;
}

bool dbAnyCursor::gotoPrev()
{
    if (allRecords) { 
	if (currId != 0) { 
	    dbRecord rec;
	    table.db->getHeader(rec, currId);
	    if (rec.prev != 0) {
		currId = rec.prev;
		return true;
	    }
	}
    } else if (selection.curr != NULL) { 
	if (selection.pos == 0) { 
	    if (selection.curr->prev == NULL) { 
		return false;
	    }
	    selection.curr = selection.curr->prev;
	    selection.pos = selection.curr->nRows;
	} 
	currId = selection.curr->rows[--selection.pos];
	return true;
    } 
    return false;
}


bool dbAnyCursor::gotoFirst()
{
    if (allRecords) { 
	currId = firstId;
	return (currId != 0);
    } else { 
	selection.curr = selection.first;
	selection.pos = 0;
	if (selection.curr == NULL) { 
	    return (currId != 0);
	} else { 
	    currId = selection.curr->rows[0];
	    return true;
	}
    }
}

bool dbAnyCursor::gotoLast()
{
    if (allRecords) { 
	currId = lastId;
	return (currId != 0);
    } else { 
	selection.curr = selection.last;
	if (selection.curr == NULL) { 
	    return (currId != 0);
	} else { 
	    selection.pos = selection.curr->nRows-1;
	    currId = selection.curr->rows[selection.pos];
	    return true;
	}
    }
}

void dbAnyCursor::reset()
{
    assert(((void)"cursor associated with online database table", 
	    table.tableId != 0));
    unlink();
    selection.reset();
    eliminateDuplicates = false;
    allRecords = false;
    currId = 0;
    tie.reset();
}

dbAnyCursor::~dbAnyCursor() 
{ 
    selection.reset();
    delete[] bitmap;
}




void dbParallelQueryContext::search(int i)
{
    int nThreads = db->parThreads;
    oid_t oid = firstRow;
    dbRecord rec;
    int j;
    for (j = i; --j >= 0;) { 
	db->getHeader(rec, oid);
	oid = rec.next;
    }
    while (oid != 0) { 
	if (db->evaluate(query->tree, oid, table)) { 
	    selection[i].add(oid);
	}
	db->getHeader(rec, oid);
	oid = rec.next;
	for (j = nThreads; --j > 0 && oid != 0;) { 
	    db->getHeader(rec, oid);
	    oid = rec.next;
	}
    }
    if (query->order != NULL) { 
	selection[i].sort(db, query->order);
    }
}


char* strupper(char* s)
{
    byte* p = (byte*)s;
    while (*p != '\0') { 
	*p = toupper(*p);
	p += 1;
    }
    return s;
}


char* strlower(char* s)
{
    byte* p = (byte*)s;
    while (*p != '\0') { 
	*p = tolower(*p);
	p += 1;
    }
    return s;
}






