//-< BTREE.CPP >-----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:      1-Jan-99    K.A. Knizhnik  * / [] \ *
//                          Last update: 25-Oct-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// B-Tree interface
//-------------------------------------------------------------------*--------*

#ifndef __BTREE_H__
#define __BTREE_H__


const int dbMaxKeyLen = dbPageSize / 2;

class dbBtree : public dbRecord { 
  protected:
    oid_t root;
    int4  height;
    int4  type;
    bool  caseInsensitive;

  public:
    enum OperationEffect { 
	done,
	overflow,
	underflow,
	not_found
    };
	
    static oid_t allocate(dbDatabase* db, int type, bool caseInsensitive);
    static void  find(dbDatabase* db, oid_t treeId, dbSearchContext& sc);
    static void  insert(dbDatabase* db, oid_t treeId, oid_t recordId, int offs);
    static void  remove(dbDatabase* db, oid_t treeId, oid_t recordId,  int offs);
    static void  drop(dbDatabase* db, oid_t treeId);
    static void  purge(dbDatabase* db, oid_t treeId);
    
    static void  traverseForward(dbDatabase* db, oid_t treeId,
				 dbAnyCursor* cursor, dbExprNode* condition);
    static void  traverseBackward(dbDatabase* db, oid_t treeId,
				  dbAnyCursor* cursor, dbExprNode* condition);
    static void  traverseForward(dbDatabase* db, oid_t treeId,
				 dbAnyCursor* cursor)
    {
	traverseForward(db, treeId, cursor, NULL);
    }
    static void  traverseBackward(dbDatabase* db, oid_t treeId,
				  dbAnyCursor* cursor)
    {
	traverseBackward(db, treeId, cursor, NULL);
    }
};

class dbBtreePage {
  public:
    nat4 nItems;
    nat4 size;
    
    struct item { 
        oid_t oid;
	int   keyLen;
	union { 
	    int1   keyInt1;
	    int2   keyInt2;
	    int4   keyInt4;
	    int8   keyInt8;
	    real4  keyReal4;
	    real8  keyReal8;
	    char   keyChar[dbMaxKeyLen];
	};
    };
    enum { 
	maxItems = (dbPageSize - 8) / sizeof(oid_t)
    };

    struct str {
	oid_t oid;
	nat2  size;
	nat2  offs;
    };    

    union {
	oid_t  record[maxItems];
	int1   keyInt1[(dbPageSize-8) / sizeof(int1)];
	int2   keyInt2[(dbPageSize-8) / sizeof(int2)];
	int4   keyInt4[(dbPageSize-8) / sizeof(int4)];
	int8   keyInt8[(dbPageSize-8) / sizeof(int8)];
	real4  keyReal4[(dbPageSize-8) / sizeof(real4)];
	real8  keyReal8[(dbPageSize-8) / sizeof(real8)];
	char   keyChar[dbPageSize-8];
        str    keyStr[1];    
    };
    
    static oid_t allocate(dbDatabase* db, oid_t root, int type, item& ins);
    
    static int   insert(dbDatabase* db, oid_t pageId, 
			int type, item& ins, int height);
    static int   remove(dbDatabase* db, oid_t pageId, 
			int type, item& rem, int height);

    static void  purge(dbDatabase* db, oid_t pageId, int type, int height);

    int          insertStrKey(dbDatabase* db, int r, item& ins, int height);
    int          replaceStrKey(dbDatabase* db, int r, item& ins, int height);
    int          removeStrKey(int r);
    void         compactify(int m);
    
    int          handlePageUnderflow(dbDatabase* db, int r, int type, item& rem,
				     int height);

    bool         find(dbDatabase* db, dbSearchContext& sc, int type, int height);

    bool         traverseForward(dbDatabase* db, dbAnyCursor* cursor,
				 dbExprNode* condition, int type, int height);
    bool         traverseBackward(dbDatabase* db, dbAnyCursor* cursor,
				  dbExprNode* condition, int type, int height);
};
  

#endif



