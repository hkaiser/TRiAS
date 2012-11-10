//-< DATABASE.H >----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 14-Feb-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Database management
//-------------------------------------------------------------------*--------*

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "class.h"
#include "reference.h"
#include "file.h"
#include "pagepool.h"

const size_t dbDefaultInitIndexSize = 1024*1024;
const size_t dbDefaultExtensionQuantum = 16*1024*1024;

const unsigned dbMaxParallelSearchThreads = 64;

enum dbHandleFlags { 
    dbPageObjectFlag = 1,
    dbModifiedFlag   = 2,
    dbFreeHandleFlag = 4,
    dbFlagsMask      = 7,
    dbFlagsBits      = 3
};

const size_t dbAllocationQuantumBits = 6;
const size_t dbAllocationQuantum = 1 << dbAllocationQuantumBits;
const size_t dbPageBits = 13;
const size_t dbPageSize = 1 << dbPageBits;
const size_t dbIdsPerPage = dbPageSize / sizeof(oid_t);
const size_t dbHandlesPerPage = dbPageSize / sizeof(offs_t);
const size_t dbBitmapSegmentBits = dbPageBits + 3 + dbAllocationQuantumBits;
const size_t dbBitmapSegmentSize = 1 << dbBitmapSegmentBits;
const size_t dbBitmapPages = 1 << (dbDatabaseOffsetBits-dbBitmapSegmentBits);
const size_t dbDirtyPageBitmapSize = 1 << (dbDatabaseOidBits-dbPageBits-3);
const size_t dbDefaultSelectionLimit = 2000000000;

const int    dbBMsearchThreshold = 512;

const char   dbMatchAnyOneChar = '_';
const char   dbMatchAnySubstring = '%';

const int    dbMaxFileSegments = 64;

enum predefinedIds { 
    dbInvalidId,
    dbMetaTableId, 
    dbBitmapId,
    dbFirstUserId = dbBitmapId + dbBitmapPages
};

class dbHeader { 
  public:
    int4   curr;  // current root
    int4   dirty; // database was not closed normally
    int4   initialized; // database is initilaized
    struct { 
	offs_t size;            // database file size
	offs_t index;           // offset to object index
	offs_t shadowIndex;     // offset to shadow index
	oid_t  indexSize;       // size of object index
	oid_t  shadowIndexSize; // size of object index
	oid_t  indexUsed;       // userd part of the index   
	oid_t  freeList;        // L1 list of free descriptors
	oid_t  bitmapEnd;       // index of last allocated bitmap page
    } root[2];
};

class dbSynthesizedAttribute;
class dbInheritedAttribute;

class dbMonitor { 
  public:
    int  nReaders;
    int  nWriters;
    int  nWaitReaders;
    int  nWaitWriters;
    int  waitForUpgrade;
    
    dbMutex mutex;
};

class dbDatabaseThreadContext;
class dbAnyCursor;
class dbQuery;
class dbExprNode;



class dbDatabase { 
    friend class dbSelection;
    friend class dbAnyCursor;
    friend class dbHashTable;
    friend class dbQuery;
    friend class dbBtree;
    friend class dbBtreePage;
    friend class dbBtreeLeafPage;
    friend class dbInheritedAttribute;
    friend class dbParallelQueryContext; 
    friend class dbServer;

  public:
    bool open(char const* databaseName);
    void close();

    void commit();
    void precommit();
    void rollback();

    void attach();
    void detach();

    void lock() { beginTransaction(true); }

    bool backup(char const* backupFileName);
    bool restore(char const* backupFileName, char const* databaseFileName);
    
    void assign(dbTableDescriptor& desc) { 
	assert(((void)"Table is not yet assigned to the database", 
		desc.tableId == 0));
	desc.db = this; 
	desc.fixedDatabase = true;
    }

    void setConcurrency(unsigned nThreads);

    enum dbErrorClass { 
	QueryError,
	ArithmeticError,
	IndexOutOfRangeError,
	DatabaseOpenError,
	FileError,
	OutOfMemoryError,
	Deadlock,
	NullReferenceError
    };

    virtual void handleError(dbErrorClass error, char const* msg = NULL, 
			     int arg = 0); 

    enum dbAccessType { 
	dbReadOnly  = 0,
	dbAllAccess = 1
    };
    const dbAccessType accessType;
    const size_t extensionQuantum;
    const size_t initIndexSize;

    static unsigned dbParallelScanThreshold; 

    void insert(dbTableDescriptor* table, dbAnyReference* ref, 
		void const* record);

    offs_t used();

    dbDatabase(dbAccessType type = dbAllAccess,
	       size_t poolSize = 0, // autodetect size of available memory
	       size_t dbExtensionQuantum = dbDefaultExtensionQuantum,
	       size_t dbInitIndexSize = dbDefaultInitIndexSize,
	       int nThreads = 1);

    virtual ~dbDatabase(); 

  protected:
    dbThreadContext<dbDatabaseThreadContext> threadContext;

    dbHeader* header;           // base address of database file mapping
    int4*     dirtyPagesMap;    // bitmap of changed pages in current index
    unsigned  parThreads;
    bool      modified;

    int       concurrentTransId;

    size_t    currRBitmapPage;//current bitmap page for allocating records
    size_t    currRBitmapOffs;//offset in current bitmap page for allocating 
                              //unaligned records
    size_t    currPBitmapPage;//current bitmap page for allocating page objects
    size_t    currPBitmapOffs;//offset in current bitmap page for allocating 
                              //page objects
    int       inAllocator;
    
    size_t    committedIndexSize;
    size_t    currIndexSize;

    oid_t     updatedRecordId;

    dbFile*                   file;
    dbMutex                   mutex;
    dbSemaphore               writeSem; 
    dbSemaphore               readSem; 
    dbSemaphore               upgradeSem; 
    dbMonitor                 monitor;
    dbPagePool                pool;
    dbTableDescriptor*        tables;

    int*                      bitmapPageAvailableSpace;
    bool                      opened;

    offs_t getPos(oid_t oid) { 
	byte* p = pool.get(header->root[1-header->curr].index
			   + oid / dbHandlesPerPage * dbPageSize);
	offs_t pos = *((offs_t*)p + oid % dbHandlesPerPage);
	pool.unfix(p);
	return pos;
    }

    void setPos(oid_t oid, offs_t pos) { 
	byte* p = pool.put(header->root[1-header->curr].index
			   + oid / dbHandlesPerPage * dbPageSize);
	*((offs_t*)p + oid % dbHandlesPerPage) = pos;
	pool.unfix(p);
    }

    dbRecord* getRow(dbGetTie& tie, oid_t oid) { 
	offs_t pos = getPos(oid);
	assert(!(pos & (dbFreeHandleFlag|dbPageObjectFlag)));
	tie.set(pool, pos & ~dbFlagsMask);
	return (dbRecord*)tie.get();
    }

    void getHeader(dbRecord& rec, oid_t oid) { 
	offs_t pos = getPos(oid);
	int offs = (int)pos & (dbPageSize-1);
	byte* p = pool.get(pos - offs);
	rec = *(dbRecord*)(p + (offs & ~dbFlagsMask));
	pool.unfix(p);
    }

    byte* put(oid_t oid) { 
	offs_t pos = getPos(oid);
	int offs = (int)pos & (dbPageSize-1);
	return pool.put(pos-offs) + (offs & ~dbFlagsMask);
    }
       
    byte* get(oid_t oid) { 
	offs_t pos = getPos(oid);
	int offs = (int)pos & (dbPageSize-1);
	return pool.get(pos-offs) + (offs & ~dbFlagsMask);
    }
       
    dbRecord* putRow(dbPutTie& tie, oid_t oid, size_t newSize); 
    dbRecord* putRow(dbPutTie& tie, oid_t oid);
    byte* put(dbPutTie& tie, oid_t oid);

    void restoreTablesConsistency();

    bool isIndexApplicable(dbAnyCursor* cursor, 
			   dbExprNode* expr, dbExprNode* andExpr, 
			   dbFieldDescriptor* &indexedField);

    bool isIndexApplicable(dbAnyCursor* cursor, 
			   dbExprNode* expr, dbExprNode* andExpr);

    bool followInverseReference(dbExprNode* expr, dbExprNode* andExpr, 
				dbAnyCursor* cursor, oid_t iref);

    bool existsInverseReference(dbExprNode* expr, int nExistsClauses);

    static void _fastcall execute(dbExprNode* expr, 
				  dbInheritedAttribute& iattr,
				  dbSynthesizedAttribute& sattr);
    bool evaluate(dbExprNode* expr, oid_t oid, dbTableDescriptor* table);

    void select(dbAnyCursor* cursor);
    void select(dbAnyCursor* cursor, dbQuery& query);
    void traverse(dbAnyCursor* cursor, dbQuery& query);

    void update(oid_t oid, dbTableDescriptor* table, void const* record);
    void remove(dbTableDescriptor* table, oid_t oid);

    offs_t allocate(size_t size, oid_t oid = 0);
    void free(offs_t pos, size_t size);
    void extend(offs_t size);
    void cloneBitmap(offs_t pos, size_t size);

    oid_t allocateId();
    void freeId(oid_t oid);

    oid_t allocatePage() { 
	oid_t oid = allocateId();
	setPos(oid, allocate(dbPageSize) | dbPageObjectFlag | dbModifiedFlag);
	return oid;
    }
    void freePage(oid_t oid); 

    oid_t allocateRow(oid_t tableId, size_t size, 
		      dbTableDescriptor* desc = NULL);
    void freeRow(oid_t tableId, oid_t oid, dbTableDescriptor* desc = NULL);
    
    static void deleteCompiledQuery(dbExprNode* tree); 

    void beginTransaction(bool modify);
    void endTransaction();

    void initializeMetaTable();
    bool loadScheme();

    bool completeDescriptorsInitialization();

    void reformatTable(oid_t tableId, dbTableDescriptor* desc);
    void addIndices(dbTableDescriptor* desc);
    oid_t addNewTable(dbTableDescriptor* desc);

    void updateTableDescriptor(dbTableDescriptor* desc, 
			       oid_t tableId, dbTable* table);


    void removeInverseReferences(dbTableDescriptor* desc, oid_t oid);

    void insertInverseReference(dbFieldDescriptor* desc, oid_t reverseId, 
				oid_t targetId);
    void removeInverseReference(dbFieldDescriptor* desc, 
				oid_t reverseId, oid_t targetId);

	
    void deleteTable(dbTableDescriptor* desc);
    void dropTable(dbTableDescriptor* desc);

    void createIndex(dbFieldDescriptor* fd);
    void createHashTable(dbFieldDescriptor* fd);
    void dropIndex(dbFieldDescriptor* fd);
    void dropHashTable(dbFieldDescriptor* fd);

    void linkTable(dbTableDescriptor* table, oid_t tableId);
    void unlinkTable(dbTableDescriptor* table);

    dbTableDescriptor* findTable(char const* name);
};

template<class T>
dbReference<T> insert(T const& record) { 
    dbReference<T> ref;
    T::dbDescriptor.getDatabase()->insert(&T::dbDescriptor, &ref, &record);
    return ref;
}

typedef int4 pkey_t; // packed key type (used in B-Tree)

class dbSearchContext { 
  public:
    dbDatabase*  db;
    dbExprNode*  condition;
    dbAnyCursor* cursor;
    char*        firstKey;
    pkey_t       firstPKey;
    int          firstKeyInclusion;
    char*        lastKey;
    pkey_t       lastPKey;
    int          lastKeyInclusion;
    int          offs;
    int          probes;
};


#endif
