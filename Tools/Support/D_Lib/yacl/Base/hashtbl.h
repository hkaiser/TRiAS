


#ifndef _hashtbl_h_ /* Sat Jan 27 10:38:35 1996 */
#define _hashtbl_h_

/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */

// This is the beginnings of a template-based hash table class. It is
// nowhere near complete.

#if defined(__GNUC__)
#pragma interface
#endif


#include "base/object.h"
#include "base/iterator.h"
#include "base/map.h"

class YACL_BASE CL_GenericSequence;

class YACL_BASE CL_AbstractHashFunction {

public:
    virtual long operator() (CL_VoidPtr p) = 0;
};


template <class BaseType>
class YACL_BASE CL_HashFunction: public CL_AbstractHashFunction {

public:
    ~CL_HashFunction () {};
    
    long operator() (CL_VoidPtr p);

};


template <class Key, class Value>
class YACL_BASE CL_AssocHashFunction: public CL_AbstractHashFunction {

public:
    ~CL_AssocHashFunction () {};
    
    long operator() (CL_VoidPtr p);

};



template <class BaseType> class YACL_BASE CL_HashTableIterator;

template <class BaseType>
class YACL_BASE CL_HashTable: public CL_Object {

public:
    CL_HashTable (CL_AbstractHashFunction* fn = NULL);

    ~CL_HashTable();

    const BaseType& Find (const BaseType& obj) const;

    bool Includes (const BaseType& obj) const;

    virtual bool Add (const BaseType& obj);

    virtual bool Remove (const BaseType& obj);

    long Size() const {return _size;};


protected:
    long                      _size;
    CL_GenericSequence*       _data;
    CL_AbstractHashFunction*  _hash;
    CL_HashFunction<BaseType> _privateHash;

    CL_VoidPtr _Find (const BaseType& obj) const;

    friend CL_HashTableIterator<BaseType>;
};



template <class Key, class Value>
class YACL_BASE CL_HashMap: public CL_Object {

public:
    CL_HashMap ();

    bool Add (const Key& key, const Value& value);

    bool Remove (const Key& key);

    bool Includes (const Key& key) const;

    Value& operator[] (const Key& key);
    
    long Size () const {return _table.Size();};
    

protected:
    CL_AssocHashFunction<Key, Value>        _fn;
    CL_HashTable <CL_MapAssoc<Key, Value> > _table;
};



template <class BaseType>
class YACL_BASE CL_HashTableIterator : public CL_Iterator<BaseType> {

public:
    CL_HashTableIterator (const CL_HashTable<BaseType>&);

    ~CL_HashTableIterator ();

    void Reset ();

    bool More ();

    const BaseType& Next ();

protected:
    const CL_HashTable<BaseType>& _table;
    
};



typedef CL_HashTable<long>        CL_IntHashTable;
typedef CL_HashTable<CL_String>   CL_StringHashTable;
typedef CL_HashMap<long, long>    CL_IntIntHashMap;


#endif /* _hashtbl_h_ */
