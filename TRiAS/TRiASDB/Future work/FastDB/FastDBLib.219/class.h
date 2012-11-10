//-< CLASS.H >-------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Metaclass information
//-------------------------------------------------------------------*--------*

#ifndef __CLASS_H__
#define __CLASS_H__

#include "stdtp.h"
#include "sync.h"

#ifndef dbDatabaseOffsetBits 
#define dbDatabaseOffsetBits 32
#endif

#ifndef dbDatabaseOidBits 
#define dbDatabaseOidBits 32
#endif

#if dbDatabaseOidBits > 32
typedef nat8 oid_t;  // It will work only for 64-bit OS
#else
typedef nat4 oid_t;
#endif

#if dbDatabaseOffsetBits > 32
typedef nat8 offs_t; // It will work only for 64-bit OS
#else
typedef nat4 offs_t;
#endif

enum dbIndexType { 
    HASHED  = 1, // hash table
    INDEXED = 2, // T-tree

    DB_FIELD_CASCADE_DELETE = 8,   // Used by OWNER macro, do not set it explicitly

    DB_FIELD_INHERITED_MASK = ~(HASHED|INDEXED)
};

#define KEY(x, index) \
    *dbDescribeField(new dbFieldDescriptor(#x, (char*)&x-(char*)this, \
                                           sizeof(x), index), x)

#define FIELD(x) KEY(x, 0)

// raw binary field
#define RAWFIELD(x) \
    *dbDescribeRawField(new dbFieldDescriptor(#x, (char*)&x-(char*)this, \
                                              sizeof(x), 0))

#define RELATION(x,inverse) \
    *dbDescribeField(new dbFieldDescriptor(#x, (char*)&x-(char*)this, \
                                           sizeof(x), 0, #inverse), x)

#define OWNER(x,member) \
    *dbDescribeField(new dbFieldDescriptor(#x, (char*)&x-(char*)this, \
                                           sizeof(x), DB_FIELD_CASCADE_DELETE, \
                                           #member), x)

#define METHOD(x) \
    *dbDescribeMethod(new dbFieldDescriptor(#x), &self::x)

#define SUPERCLASS(x) \
    x::dbDescribeComponents(NULL)->adjustOffsets((char*)((x*)this)-(char*)this)

#define TYPE_DESCRIPTOR(fields) \
    dbFieldDescriptor* dbDescribeComponents(dbFieldDescriptor*) { \
	return &fields; \
    } \
    static dbTableDescriptor dbDescriptor 

#define CLASS_DESCRIPTOR(name, fields) \
    typedef name self; \
    dbFieldDescriptor* dbDescribeComponents(dbFieldDescriptor*) { \
	return &fields; \
    } \
    static dbTableDescriptor dbDescriptor 

#define REGISTER_IN(table, database) \
    dbTableDescriptor* dbGetTableDescriptor(table*) \
      { return &table::dbDescriptor; }            \
    static dbFieldDescriptor* dbDescribeComponentsOf##table() \
      { return ((table*)0)->dbDescribeComponents(NULL); }     \
    dbTableDescriptor table::dbDescriptor(#table, database, sizeof(table), \
                                          &dbDescribeComponentsOf##table)

#define REGISTER(table) REGISTER_IN(table, NULL)

#define DETACHED_TABLE ((dbDatabase*)-1)
#define REGISTER_UNASSIGNED(table) REGISTER_IN(table, DETACHED_TABLE)


class dbDatabase;
class dbAnyArray;
class dbTableDescriptor;
class dbAnyMethodTrampoline;

class dbFieldDescriptor { 
  public:
    dbFieldDescriptor* next; // next file within scope
    dbFieldDescriptor* prev; // previous field within scope

    dbFieldDescriptor* nextField;

    dbFieldDescriptor* nextHashedField;
    dbFieldDescriptor* nextIndexedField;
    dbFieldDescriptor* nextInverseField;

    int                fieldNo;
    char*              name;
    char*              longName;
    char*              refTableName;
    dbTableDescriptor* refTable;
    dbTableDescriptor* defTable;
    dbFieldDescriptor* inverseRef;
    char*              inverseRefName;  
    int                type;
    int                indexType;
    int                dbsOffs;
    int                appOffs;
    dbFieldDescriptor* components;
    void*              trampoline;
    oid_t              hashTable;
    oid_t              tTree;
    size_t             dbsSize;
    size_t             appSize;
    size_t             alignment;

    enum FieldAttributes { 
	ComponentOfArray   = 0x01,
	HasArrayComponents = 0x02,
	OneToOneMapping    = 0x04,
	Updated            = 0x08
    };
    int                attr;

    int                oldDbsType;
    int                oldDbsOffs;
    int                oldDbsSize;

    dbAnyMethodTrampoline* method;

    void (*arrayAllocator)(dbAnyArray* array, void* data, size_t length);
    
    size_t calculateRecordSize(byte* base, size_t offs);
    size_t calculateNewRecordSize(byte* base, size_t offs);
    size_t convertRecord(byte* dst, byte* src, size_t offs);

    int    sizeWithoutOneField(dbFieldDescriptor* field, 
			       byte* base, size_t& size);
    
    size_t copyRecordExceptOneField(dbFieldDescriptor* field, 
				    byte* dst, byte* src, size_t offs); 

    size_t storeRecordFields(byte* dst, byte* src, size_t offs);

    void markUpdatedFields(byte* dst, byte* src);

    void fetchRecordFields(byte* dst, byte* src);

    void adjustReferences(byte* record, size_t base, size_t size, long shift);

    dbFieldDescriptor* find(const char* name);

    dbFieldDescriptor& operator, (dbFieldDescriptor& field) { 
	dbFieldDescriptor* tail = field.prev;
	tail->next = this;
	prev->next = &field;
	field.prev = prev;
	prev = tail;
	return *this;
    }

    dbFieldDescriptor& adjustOffsets(long offs);

    dbFieldDescriptor(char* name, int offs, int size, int indexType, 
		      char* inverse = NULL,
		      dbFieldDescriptor* components = NULL);

    dbFieldDescriptor(char* name);
    ~dbFieldDescriptor() { delete[] longName; }
};

class dbTableDescriptor { 
    friend class dbCompiler;
    friend class dbDatabase;
    friend class dbTable;
    friend class dbAnyCursor;
    friend class dbSubSql;
    friend class dbHashTable;
    friend class dbTtreeNode;
    friend class dbServer;
  protected:
    dbTableDescriptor*  next;
    static dbTableDescriptor* chain;

    dbTableDescriptor*  nextDbTable; // next table in the database

    char*               name;
    oid_t               tableId;
    dbFieldDescriptor*  columns; 
    dbFieldDescriptor*  hashedFields;
    dbFieldDescriptor*  indexedFields;
    dbFieldDescriptor*  inverseFields;
    dbFieldDescriptor*  firstField;
    dbFieldDescriptor** nextFieldLink;
    dbDatabase*         db;
    bool                fixedDatabase;
    bool                isStatic;
    size_t              appSize;
    size_t              fixedSize;
    size_t              nFields;
    size_t              nColumns;

    dbTableDescriptor*  cloneOf;
    typedef dbFieldDescriptor* (*describeFunc)();
    describeFunc        describeComponentsFunc;

    dbTableDescriptor*  clone();

    size_t              totalNamesLength();

    int calculateFieldsAttributes(dbFieldDescriptor* fieldsList, 
				  char const* prefix, int offs, 
				  int indexMask, int& attr);

    dbFieldDescriptor* buildFieldsList(dbTable* table, char const* prefix,
				       int prefixLen, int& attr);

  public:
    dbFieldDescriptor* find(char const* name);

    void setFlags();

    bool equal(dbTable* table);

    bool match(dbTable* table);

    void checkRelationship();

    dbDatabase* getDatabase() { return db; }

    void storeInDatabase(dbTable* table);

    static void cleanup();

    dbTableDescriptor(dbTable* table);

    dbTableDescriptor(char* tableName, dbDatabase* db, size_t objSize, 
		      describeFunc func, dbTableDescriptor* original = NULL);
    ~dbTableDescriptor();
};

struct dbVarying { 
    nat4 size; // number of elements in the array
    int4 offs; // offset from the beginning of the record
};

struct dbField { 
    enum FieldTypes { 
	tpBool,
	tpInt1,
	tpInt2,
	tpInt4,
	tpInt8,
	tpReal4, 
	tpReal8, 
	tpString,
	tpReference,
	tpArray,
	tpMethodBool,
	tpMethodInt1,
	tpMethodInt2,
	tpMethodInt4,
	tpMethodInt8,
	tpMethodReal4,
	tpMethodReal8,
	tpMethodString,
	tpMethodReference,
	tpStructure,
	tpRawBinary, 
	tpUnknown
    };
	
    dbVarying name;     
    dbVarying tableName; // only for references: name of referenced table
    dbVarying inverse;   // only for relations: name of inverse reference field
    int4      type;
    int4      offset; 
    nat4      size;
    oid_t     hashTable;
    oid_t     tTree;
};     


class dbRecord { 
  public:
    nat4   size;
    oid_t  next;
    oid_t  prev;
};

class dbTable : public dbRecord { 
  public:
    dbVarying name;
    dbVarying fields;
    nat4      fixedSize;
    nat4      nRows;
    nat4      nColumns;
    oid_t     firstRow;
    oid_t     lastRow;
};

inline dbFieldDescriptor* dbDescribeRawField(dbFieldDescriptor* fd)
{
    fd->type = dbField::tpRawBinary;
    fd->alignment = 1;
    return fd;
}


template<class T>
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, T& x) 
{ 
    fd->type = dbField::tpStructure;
    fd->components = x.dbDescribeComponents(fd);
    return fd;
}

inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, int1&) 
{ 
    fd->type = dbField::tpInt1; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, int2&) 
{ 
    fd->type = dbField::tpInt2; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, int4&) 
{ 
    fd->type = dbField::tpInt4; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, int8&) 
{ 
    fd->type = dbField::tpInt8; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, nat1&) 
{ 
    fd->type = dbField::tpInt1; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, nat2&) 
{ 
    fd->type = dbField::tpInt2; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, nat4&) 
{ 
    fd->type = dbField::tpInt4; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, nat8&) 
{ 
    fd->type = dbField::tpInt8; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, bool&) 
{ 
    fd->type = dbField::tpBool; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, real4&) 
{ 
    fd->type = dbField::tpReal4; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, real8&) 
{ 
    fd->type = dbField::tpReal8; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, char const*&) 
{ 
    fd->type = dbField::tpString; 
    fd->dbsSize = sizeof(dbVarying); 
    fd->alignment = 4;
    fd->components = new dbFieldDescriptor("[]");
    fd->components->type = dbField::tpInt1;
    fd->components->dbsSize = fd->components->appSize = 1;
    fd->components->alignment = 1; 
    return fd;
}
inline dbFieldDescriptor* dbDescribeField(dbFieldDescriptor* fd, char*&) 
{ 
    fd->type = dbField::tpString; 
    fd->dbsSize = sizeof(dbVarying); 
    fd->alignment = 4;
    fd->components = new dbFieldDescriptor("[]");
    fd->components->type = dbField::tpInt1;
    fd->components->dbsSize = fd->components->appSize = 1;
    fd->components->alignment = 1; 
    return fd;
}

class dbAnyMethodTrampoline { 
  public:
    dbFieldDescriptor* cls;

    virtual void invoke(byte* data, void* result) = 0;
    virtual dbAnyMethodTrampoline* optimize() = 0;

    dbAnyMethodTrampoline(dbFieldDescriptor* fd) { cls = fd; }
    virtual~dbAnyMethodTrampoline();
};
    
template<class T, class R>
class dbMethodTrampoline : public dbAnyMethodTrampoline { 
  public:
    typedef R (T::*mfunc)();
    mfunc method;

    void invoke(byte* data, void* result) {
	T rec;
	cls->components->fetchRecordFields((byte*)&rec, data);
	*(R*)result = (rec.*method)();
    }
    dbAnyMethodTrampoline* optimize();
 
    dbMethodTrampoline(dbFieldDescriptor* fd, mfunc f) 
    : dbAnyMethodTrampoline(fd), method(f) {} 
};

template<class T, class R>
class dbMethodFastTrampoline : public dbMethodTrampoline<T,R> { 
  public:
    void invoke(byte* data, void* result) {
	*(R*)result = (((T*)(data + cls->dbsOffs))->*method)();
    }
    dbMethodFastTrampoline(dbMethodTrampoline<T,R>* mt) 
    : dbMethodTrampoline<T,R>(mt->cls, mt->method) { 
	delete mt;
    }
};

template<class T, class R>
inline dbAnyMethodTrampoline* dbMethodTrampoline<T,R>::optimize() { 
    return new dbMethodFastTrampoline<T,R>(this);
}
    

template<class T, class R>
inline dbFieldDescriptor* dbDescribeMethod(dbFieldDescriptor* fd, R (T::*p)()) 
{ 
    R ret;
    dbDescribeField(fd, ret);
    assert(fd->type <= dbField::tpReference);
    fd->type += dbField::tpMethodBool;
    fd->method = new dbMethodTrampoline<T,R>(fd, p);
    return fd;
}

#endif


