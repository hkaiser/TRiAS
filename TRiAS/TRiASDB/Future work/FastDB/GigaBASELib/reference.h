//-< REFERENCE.H >---------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Database table field reference type
//-------------------------------------------------------------------*--------*

#ifndef __REFERENCE_H__
#define __REFERENCE_H__

class dbAnyReference {  
    friend class dbAnyCursor;
    friend class dbDatabase;
    friend class dbFieldDescriptor;
  protected:
    oid_t       oid;

    dbAnyReference(oid_t oid) { 
	this->oid = oid;
    }
  public: 
    oid_t getOid() const { 
	return oid;
    }
    friend bool isNull(dbAnyReference const& ref) { 
	return ref.oid == 0; 
    }
    bool isNull() { return oid == 0; }
};

class dbNullReference {};

extern dbNullReference null;

#if defined(_MSC_VER) && _MSC_VER+0 <= 1100 
//
// Visual C++ prior to 5.0 version (with applied Service Pack 3)
// didn't support lazy template instantiation. As far as VC has bug
// with treating local function prototypes, we have to use friend function.
//
template<class T>
extern dbTableDescriptor* dbGetTableDescriptor(T*);
#endif


template<class T>
class dbReference : public dbAnyReference { 
  public:
    dbFieldDescriptor* dbDescribeComponents(dbFieldDescriptor* fd) { 
        fd->type = dbField::tpReference;
#if defined(_MSC_VER)
#if _MSC_VER+0 <= 1100 
	fd->refTable = dbGetTableDescriptor((T*)0);
#else
        fd->refTable = &T::dbDescriptor;
#endif
#else
	// This doesn't work with Microsoft Visual C++
	extern dbTableDescriptor* dbGetTableDescriptor(T*);
	fd->refTable = dbGetTableDescriptor((T*)0);
#endif
	fd->dbsSize = fd->alignment = sizeof(oid_t);
        return NULL;
    }

    dbReference& operator = (dbReference const& ref) { 
	oid = ref.oid;
	return *this;
    }
    dbReference& operator = (dbNullReference const&) { 
	oid = 0;
	return *this;
    }
    
    bool operator == (dbReference const& ref) const { 
	return oid == ref.oid; 
    }
    bool operator != (dbReference const& ref) const { 
	return oid != ref.oid; 
    }
    bool operator == (dbNullReference const&) const { 
	return oid == 0;
    }
    bool operator != (dbNullReference const&) const { 
	return oid != 0;
    }

    dbReference(dbNullReference const&) : dbAnyReference(0) {}
    dbReference(dbReference const& ref) : dbAnyReference(ref.oid) {}
    dbReference(oid_t oid=0) : dbAnyReference(oid) {}
};

#endif





