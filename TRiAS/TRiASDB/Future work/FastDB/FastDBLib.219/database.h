//-< DATABASE.H >----------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 23-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Database management
//-------------------------------------------------------------------*--------*

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "class.h"
#include "reference.h"
#include "file.h"

const size_t dbDefaultInitDatabaseSize = 4*1024*1024;
const size_t dbDefaultInitIndexSize = 64*1024;
const size_t dbDefaultExtensionQuantum = 4*1024*1024;
const unsigned dbMaxParallelSearchThreads = 64;

enum dbInternalObject { 
    dbTableRow, 
    dbPageObjectMarker,
    dbTtreeMarker,
    dbTtreeNodeMarker,
    dbHashTableMarker,
    dbHashTableItemMarker,
    
    dbInternalObjectMarker = 7 // mask for internals object markers
};
    
const offs_t dbFreeHandleMarker = (offs_t)1 << (sizeof(offs_t)*8 - 1); 

const size_t dbAllocationQuantumBits = 4;
const size_t dbAllocationQuantum = 1 << dbAllocationQuantumBits;
const size_t dbPageBits = 12;
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

enum predefinedIds { 
    dbInvalidId,
    dbMetaTableId, 
    dbBitmapId,
    dbFirstUserId = dbBitmapId + dbBitmapPages
};

class dbHeader { 
  public:
    offs_t size;  // database file size
    int4   curr;  // current root
    int4   dirty; // database was not closed normally
    int4   initialized; // database is initilaized
    struct { 
	offs_t index;           // offset to object index
	offs_t shadowIndex;     // offset to shadow index
	oid_t  indexSize;       // size of object index
	oid_t  shadowIndexSize; // size of object index
	oid_t  indexUsed;       // used part of the index   
	oid_t  freeList;        // L1 list of free descriptors
    } root[2];
};

union  dbSynthesizedAttribute;
struct dbInheritedAttribute;

class dbMonitor { 
  public:
    sharedsem_t sem;
    int  nReaders;
    int  nWriters;
    int  nWaitReaders;
    int  nWaitWriters;
    int  waitForUpgrade;

    int  backupInProgress;
    
    unsigned lastDeadlockRecoveryTime;

    int  version; 
    int  users;  

    int  dirtyPagesMap[dbDirtyPageBitmapSize/4];
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
    friend class dbTtree;
    friend class dbTtreeNode;
    friend class dbParallelQueryContext; 
    friend class dbServer;
  public:
    bool open(char const* databaseName, 
	      char const* fileName = NULL, 
	      unsigned    waitLockTimeout = INFINITE);

    void close();

    void commit();
    void precommit();
    void rollback();
    
    void attach();
    void detach();

    void lock() { beginTransaction(true); }

    bool backup(char const* file);
    
    void assign(dbTableDescriptor& desc) { 
	assert(((void)"Table is not yet assigned to the database", 
		desc.tableId == 0));
	desc.db = this; 
	desc.fixedDatabase = true;
    }

    void setConcurrency(unsigned nThreads);

    long getAllocatedSize() { return allocatedSize; }

    enum dbErrorClass { 
	NoError, 
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
    const size_t initSize;
    const size_t extensionQuantum;
    const size_t initIndexSize;

    static unsigned dbParallelScanThreshold; 

    void insertRecord(dbTableDescriptor* table, dbAnyReference* ref, 
		      void const* record);

    bool isOpen() const { return opened; }

    void erase();

#ifndef NO_MEMBER_TEMPLATES
    template<class T>
    dbReference<T> insert(T const& record) {
	dbReference<T> ref;
	insertRecord(lookupTable(&T::dbDescriptor), &ref, &record);
	return ref;
    }
#endif
    dbTableDescriptor* lookupTable(dbTableDescriptor* desc);

    dbDatabase(dbAccessType type = dbAllAccess,
	       size_t dbInitSize = dbDefaultInitDatabaseSize,
	       size_t dbExtensionQuantum = dbDefaultExtensionQuantum,
	       size_t dbInitIndexSize = dbDefaultInitIndexSize,
	       int nThreads = 1 
	       // Do not specify the last parameter - it is only for checking
	       // that application and GigaBASE library were built with the 
	       // same compiler options (-DNO_PTHREADS is critical)
	       // Mismached parameters should cause linker error
#ifdef NO_PTHREADS
	       , bool usePthreads = false
#endif
	       );

    virtual ~dbDatabase(); 

  protected:
    static size_t internalObjectSize[];
    
    dbThreadContext<dbDatabaseThreadContext> threadContext;

    byte*     baseAddr;         // base address of database file mapping
    dbHeader* header;           // base address of database file mapping
    offs_t*   currIndex;        // current database object index
    offs_t*   index[2];
    unsigned  parThreads;
    bool      modified;

    int       concurrentTransId;

    size_t    currBitmapPage;    
    size_t    currBitmapOffs;
    int       inAllocator;
    
    char*     databaseName;
    int       databaseNameLen;
    char*     fileName;
    int       version;
    
    size_t    committedIndexSize;
    size_t    currIndexSize;
    oid_t     updatedRecordId;

    unsigned  dbWaitLockTimeout;


    dbFile                    file;
    dbSharedObject<dbMonitor> shm;
    dbGlobalCriticalSection   cs;
    dbInitializationMutex     initMutex;
    dbSemaphore               writeSem; 
    dbSemaphore               readSem; 
    dbSemaphore               upgradeSem; 
    dbEvent                   backupCompletedEvent;
    dbMonitor*                monitor;

    dbTableDescriptor*        tables;

    int*                      bitmapPageAvailableSpace;
    bool                      opened;

    long                      allocatedSize;

    dbRecord* getRow(oid_t oid) { 
	assert(!(currIndex[oid]&(dbFreeHandleMarker|dbInternalObjectMarker)));
	return (dbRecord*)(baseAddr + currIndex[oid]); 
    }

    dbRecord* putRow(oid_t oid, size_t newSize); 

    dbRecord* putRow(oid_t oid) { 
	if (oid < committedIndexSize && index[0][oid] == index[1][oid]) { 
	    size_t size = getRow(oid)->size;
	    size_t pageNo = oid/dbHandlesPerPage;
	    monitor->dirtyPagesMap[pageNo >> 5] |= 1 << (pageNo & 31);
	    cloneBitmap(currIndex[oid], size);
	    allocate(size, oid);
	} 
	return (dbRecord*)(baseAddr + currIndex[oid]); 
    }

    byte* get(oid_t oid) { 
	return baseAddr + (currIndex[oid] & ~dbInternalObjectMarker); 
    }

    byte* put(oid_t oid) { 
	if (oid < committedIndexSize && index[0][oid] == index[1][oid]) { 
	    offs_t offs = currIndex[oid];
	    size_t size = internalObjectSize[offs & dbInternalObjectMarker];
	    size_t pageNo = oid/dbHandlesPerPage;
	    monitor->dirtyPagesMap[pageNo >> 5] |= 1 << (pageNo & 31);
	    allocate(size, oid);
	    cloneBitmap(offs & ~dbInternalObjectMarker, size);
	} 
	return baseAddr + (currIndex[oid] & ~dbInternalObjectMarker); 
    }

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
    bool evaluate(dbExprNode* expr, oid_t oid, dbTable* table);

    void select(dbAnyCursor* cursor);
    void select(dbAnyCursor* cursor, dbQuery& query);
    void traverse(dbAnyCursor* cursor, dbQuery& query);

    void update(oid_t oid, dbTableDescriptor* table, void const* record);
    void remove(dbTableDescriptor* table, oid_t oid);

    offs_t allocate(size_t size, oid_t oid = 0);
    void free(offs_t pos, size_t size);
    void extend(offs_t size);
    void cloneBitmap(offs_t pos, size_t size);

    oid_t allocateId(int n = 1);
    void freeId(oid_t oid, int n = 1);

    
    void recovery();

    oid_t allocateObject(dbInternalObject marker) { 
	oid_t oid = allocateId();
	currIndex[oid] = allocate(internalObjectSize[marker]) + marker;
	return oid;
    }
    oid_t allocateRow(oid_t tableId, size_t size);
    void freeRow(oid_t tableId, oid_t oid);
    void freeObject(oid_t oid); 
    
    static void deleteCompiledQuery(dbExprNode* tree); 

    bool beginTransaction(bool modify);
    void endTransaction();

    void initializeMetaTable();
    bool loadScheme(bool alter);

    bool completeDescriptorsInitialization();

    void reformatTable(oid_t tableId, dbTableDescriptor* desc);
    bool addIndices(bool alter, dbTableDescriptor* desc);
    oid_t addNewTable(dbTableDescriptor* desc);

    void updateTableDescriptor(dbTableDescriptor* desc, oid_t tableId);
    void insertInverseReference(dbFieldDescriptor* fd, 
				oid_t reverseId, oid_t targetId);

    void removeInverseReferences(dbTableDescriptor* desc, oid_t oid);
    void removeInverseReference(dbFieldDescriptor* fd, 
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
    T::dbDescriptor.getDatabase()->insertRecord(&T::dbDescriptor, &ref, &record);
    return ref;
}

#ifdef NO_MEMBER_TEMPLATES
template<class T>
dbReference<T> insert(dbDatabase& db, T const& record) {
    dbReference<T> ref;
    db.insertRecord(db.lookupTable(&T::dbDescriptor), &ref, &record);
    return ref;
}
#endif

class dbSearchContext { 
  public:
    dbDatabase*  db;
    dbExprNode*  condition;
    dbAnyCursor* cursor;
    char*        firstKey;
    int          firstKeyInclusion;
    char*        lastKey;
    int          lastKeyInclusion;
    int          type;
    int          offs;
    int          probes;
};


#endif
