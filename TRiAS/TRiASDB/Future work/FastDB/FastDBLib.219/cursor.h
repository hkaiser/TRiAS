//-< CURSOR.H >------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Table cursor
//-------------------------------------------------------------------*--------*

#ifndef __CURSOR_H__
#define __CURSOR_H__

class dbOrderByNode;

class dbSelection { 
  public:
    enum { quantum = 1024 };
    class segment { 
      public:
	segment* prev;
	segment* next;
	size_t   nRows;
	oid_t    rows[quantum];

	segment(segment* after) { 
	    prev = after;
	    next = NULL;
	    nRows = 0;
	}	
    };
    segment*  first;
    segment*  last;
    segment*  curr;
    size_t    nRows;
    size_t    pos;

    void add(oid_t oid) { 
	if (last == NULL) { 
	    first = last = new segment(NULL);
	} else if (last->nRows == quantum) { 
	    last = last->next = new segment(last);
	}
	last->rows[last->nRows++] = oid;
	nRows += 1;
    }
    
    void sort(dbDatabase* db, dbOrderByNode* order);
    static int compare(dbRecord* a, dbRecord* b, dbOrderByNode* order);

    dbSelection() { 
	nRows = 0;
	pos = 0;
	first = curr = last = NULL;
    }
    void reverse();
    void reset();
};

enum dbCursorType { 
    dbCursorViewOnly,
    dbCursorForUpdate
};

class dbL2List { 
  public:
    dbL2List* next; 
    dbL2List* prev; 

    void link(dbL2List* elem) { 
	elem->prev = this;
	elem->next = next;
	next = next->prev = elem;
    }
    void unlink() { 
	next->prev = prev;
	prev->next = next;
        next = prev = this;
    }
    bool isEmpty() { 
	return next == this;
    }
    dbL2List() { 
	next = prev = this;
    }
    ~dbL2List() { 
	unlink();
    }
};


class dbAnyCursor : public dbL2List { 
    friend class dbDatabase;
    friend class dbHashTable;
    friend class dbTtreeNode;
    friend class dbSubSql;
    friend class dbStatement;
    friend class dbServer;
  public:
    int getNumberOfRecords() { return selection.nRows; }

    void remove();
    
    bool isEmpty() { return currId == 0; }

    bool isLimitReached() { return selection.nRows >= limit; }

    int select(dbQuery& query, dbCursorType aType) {
	type = aType;
	reset();
	db->select(this, query); 
	if (gotoFirst() && prefetch) { 
	    fetch();
	}
	return selection.nRows;
    } 
 
    int select(dbQuery& query) { 
	return select(query, defaultType);
    }

    int select(char const* condition, dbCursorType aType) { 
	dbQuery query(condition);
	return select(query, aType);
    } 

    int select(char const* condition) { 
	return select(condition, defaultType);
    }

    int select(dbCursorType aType) { 
	type = aType;
	reset();
	db->select(this); 
	if (gotoFirst() && prefetch) { 
	    fetch();
	}
	return selection.nRows;
    } 

    int select() {
	return select(defaultType);
    }

    void update() { 
	assert(type == dbCursorForUpdate && currId != 0);
	db->update(currId, table, record);
    }

    void removeAll() {
	db->deleteTable(table);
	reset();
    }

    void removeAllSelected();

    void setSelectionLimit(size_t lim) { limit = lim; }
    
    void unsetSelectionLimit() { limit = dbDefaultSelectionLimit; }

    void setPrefetchMode(bool mode) { prefetch = mode; }

    void reset();

    bool isLast(); 
    bool isFirst(); 

    void freeze();
    void unfreeze();

  protected: 
    dbDatabase*        db;
    dbTableDescriptor* table;
    dbCursorType       type;
    dbCursorType       defaultType;
    dbSelection        selection;
    bool               allRecords;
    oid_t              firstId;
    oid_t              lastId;
    oid_t              currId;
    byte*              record;
    size_t             limit;

    int4*              bitmap; // bitmap to avoid duplicates
    size_t             bitmapSize;
    bool               eliminateDuplicates;
    bool               prefetch;
    
    void checkForDuplicates() { 
	if (!eliminateDuplicates && limit > 1) { 
	    eliminateDuplicates = true;
	    size_t size = (db->currIndexSize + 31) / 32;
	    if (size > bitmapSize) { 
		delete[] bitmap;
		bitmap = new int4[size];
		bitmapSize = size;
	    }
	    memset(bitmap, 0, size*4);
	}
    }

    bool isMarked(oid_t oid) { 
	return bitmap != NULL && (bitmap[oid >> 5] & (1 << (oid & 31))) != 0;
    }

    void mark(oid_t oid) { 
	if (bitmap != NULL) { 
	    bitmap[oid >> 5] |= 1 << (oid & 31);
	}
    }    

    bool add(oid_t oid) { 
	if (selection.nRows < limit) { 
	    if (eliminateDuplicates) { 
		if (bitmap[oid >> 5] & (1 << (oid & 31))) { 
		    return true;
		}
		bitmap[oid >> 5] |= 1 << (oid & 31);
	    } 
	    selection.add(oid);
	    return selection.nRows < limit;
	} 
	return false;
    }

    bool gotoNext();
    bool gotoPrev(); 
    bool gotoFirst();
    bool gotoLast();
    
    void setCurrent(dbAnyReference const& ref);

    void fetch() { 
	assert(!(db->currIndex[currId] 
		 & (dbInternalObjectMarker|dbFreeHandleMarker)));
	table->columns->fetchRecordFields(record, 
					  (byte*)db->getRow(currId));
    }

    void adjustReferences(size_t base, size_t size, long shift) { 
	if (currId != 0) { 
	    table->columns->adjustReferences(record, base, size, shift);
	}
    }

    dbAnyCursor(dbTableDescriptor& aTable, dbCursorType aType, byte* rec)
    : table(&aTable),type(aType),defaultType(aType),
      allRecords(false),currId(0),record(rec)
    {
	db = NULL;
	limit = dbDefaultSelectionLimit;
	prefetch = true;
	bitmap = NULL; 
	bitmapSize = 0;
	eliminateDuplicates = false;
    }
    ~dbAnyCursor();
};

template<class T>
class dbCursor : public dbAnyCursor { 
  protected:
    T record;
    
  public:
    dbCursor(dbCursorType type = dbCursorViewOnly) 
        : dbAnyCursor(T::dbDescriptor, type, (byte*)&record) {}

    dbCursor(dbDatabase* aDb, dbCursorType type = dbCursorViewOnly)
	: dbAnyCursor(T::dbDescriptor, type, (byte*)&record)
    {
	db = aDb;
	table = db->lookupTable(table);
    }

    T* get() { 
	return currId == 0 ? (T*)NULL : &record; 
    }
    T* next() { 
	if (gotoNext()) { 
	    fetch();
	    return &record;
	}
	return NULL;
    }
    T* prev() {	
	if (gotoPrev()) { 
	    fetch();
	    return &record;
	}
	return NULL;
    }
    T* first() { 
	if (gotoFirst()) {
	    fetch();
	    return &record;
	}
	return NULL;
    }
    T* last() { 
	if (gotoLast()) {
	    fetch();
	    return &record;
	}
	return NULL;
    }    
    T* operator ->() { 
	assert(currId != 0);
	return &record;
    }
    T* at(dbReference<T> const& ref) { 
	setCurrent(ref);
	return &record;
    }
    dbReference<T> currentId() { 
	return dbReference<T>(currId);
    }
};

class dbParallelQueryContext { 
  public:
    dbDatabase* const      db;
    dbCompiledQuery* const query;
    oid_t                  firstRow;
    dbTable*               table;
    dbSelection            selection[dbMaxParallelSearchThreads];

    void search(int i); 

    dbParallelQueryContext(dbDatabase* aDb, dbTable* aTable, 
			   dbCompiledQuery* aQuery)
      : db(aDb), query(aQuery), firstRow(aTable->firstRow), table(aTable) {}
};


extern char* strupper(char* s);

extern char* strlower(char* s);

#endif
