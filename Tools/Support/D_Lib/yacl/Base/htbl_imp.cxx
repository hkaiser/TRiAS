

#ifndef _htbl_imp_cxx_ /* Sat Jan 27 10:56:56 1996 */
#define _htbl_imp_cxx_

#if defined(__GNUC__)
#pragma implementation
#endif


#include "base/hashtbl.h"
#include "base/genseq.h"
#include "base/string.h"
#include "base/basicops.cxx"

long CL_HashFunction<CL_String>::operator() (CL_VoidPtr p)
{
    CL_String* s = (CL_String*) p;
    if (!s)
        return 0;
    long h = 0;
    char* ptr = (char*) s->AsPtr();
    long n = s->Size();
    for (long i = 0; i < n; i += 4) {
        long t = 0;
        for (short j = 0; j < 4; j++) {
            if (i + j < n)
                t = (t << 8) + ptr[j];
            else
                break;
        }
        ptr += 4;
        h += t;
    }
    return h;
}
        

template <class BaseType>
long CL_HashFunction<BaseType>::operator() (CL_VoidPtr p)
{
    return (long) p;
}



template <class Key, class Value>
long CL_AssocHashFunction<Key, Value>::operator() (CL_VoidPtr p)
{
    CL_MapAssoc<Key,Value>& assoc = *(CL_MapAssoc<Key,Value>*) p;
    CL_HashFunction<Key> fn;
    return fn (CL_Basics<Key>::MakePointer (assoc.key));
}



enum {
#if defined(__MS_DOS__) || defined(__MS_WINDOWS__)
    INITIAL_HASH_TABLE_SIZE = 253
#else
    INITIAL_HASH_TABLE_SIZE = 1029
#endif
};

template <class BaseType>
CL_HashTable<BaseType>::CL_HashTable (CL_AbstractHashFunction* fn)
{
    _data = new CL_GenericSequence (INITIAL_HASH_TABLE_SIZE);
    _size = 0;
    if (fn)
        _hash = fn;
    else
        _hash = &_privateHash;
}



template <class BaseType>
CL_HashTable<BaseType>::~CL_HashTable()
{
    if (_data)
        delete _data;
}



template <class BaseType>
const BaseType& CL_HashTable<BaseType>::Find (const BaseType& obj) const
{
    CL_VoidPtr p = _Find (obj);
    if (p)
        return CL_Basics<BaseType>::Deref (p);
    return CL_Basics<BaseType>::NullValueRef();
}



template <class BaseType>
bool CL_HashTable<BaseType>::Includes (const BaseType& obj) const
{
    CL_VoidPtr p = _Find (obj);
    return p ? TRUE : FALSE;
}



template <class BaseType>
CL_VoidPtr CL_HashTable<BaseType>::_Find (const BaseType& obj) const
{
    long h = (*_hash) (CL_Basics<BaseType>::MakePointer (obj)) % _data->Size();
    if ((*_data) (h)) {
        CL_GenericSequence& sq = *(CL_GenericSequence*) (*_data)(h);
        for (long i = sq.Size() - 1; i >= 0; i--) {
            CL_VoidPtr p = sq(i);
            if (CL_Basics<BaseType>::Compare
                (CL_Basics<BaseType>::Deref (p), obj) == 0)
                return p;
        }
    }
    return NULL;
}



template <class BaseType>
bool CL_HashTable<BaseType>::Add (const BaseType& obj)
{
    long h = (*_hash) (CL_Basics<BaseType>::MakePointer (obj)) % _data->Size();
    if (! (*_data) (h))
        (*_data) (h) = new CL_GenericSequence;
    CL_GenericSequence& sq = *(CL_GenericSequence*) (*_data)(h);
    for (long i = sq.Size() - 1; i >= 0; i--)
        if (CL_Basics<BaseType>::Compare
            (CL_Basics<BaseType>::Deref (sq(i)), obj) == 0)
            return FALSE;
    if (!PrepareToChange())
        return FALSE;
    sq.Add (CL_Basics<BaseType>::MakeCopy (obj));
    _size++;
    Notify ();
    return TRUE;
}


template <class BaseType>
bool CL_HashTable<BaseType>::Remove (const BaseType& obj)
{
    if (!PrepareToChange())
        return FALSE;
    long h = (*_hash) (CL_Basics<BaseType>::MakePointer (obj)) % _data->Size();
    if ((*_data) (h)) {
        CL_GenericSequence& sq = *(CL_GenericSequence*) (*_data)(h);
        for (long i = sq.Size() - 1; i >= 0; i--) {
            if (CL_Basics<BaseType>::Compare
                (CL_Basics<BaseType>::Deref (sq(i)), obj) == 0) {
                sq.Remove (i);
                if (sq.Size() <= 0) {
                    delete (CL_GenericSequence*) (*_data)(h);
                    (*_data)(h) = 0;
                }
                _size--;
                Notify ();
                return TRUE;
            }
        }
    }
    Notify();
    return FALSE;
}








// -----------------------------------------------------------------

template <class Key, class Value>
CL_HashMap<Key,Value>::CL_HashMap ()
: _table (&_fn)
{
}



template <class Key, class Value>
bool CL_HashMap<Key,Value>::Add (const Key& key, const Value& value)
{
    return _table.Add (CL_MapAssoc<Key,Value> (key, value));
}


template <class Key, class Value>
bool CL_HashMap<Key,Value>::Remove (const Key& key)
{
    return _table.Remove (CL_MapAssoc<Key,Value>
                          (key, CL_Basics<Value>::NullValueRef()));
}


template <class Key, class Value>
bool CL_HashMap<Key,Value>::Includes (const Key& key) const
{
    return _table.Includes (CL_MapAssoc<Key,Value>
                            (key, CL_Basics<Value>::NullValueRef()));
}



template <class Key, class Value>
Value& CL_HashMap<Key,Value>::operator[] (const Key& key) const
{
    CL_MapAssoc<Key,Value>& assoc = (CL_MapAssoc<Key,Value>&) _table.Find
        (CL_MapAssoc<Key,Value> (key, CL_Basics<Value>::NullValueRef()));
    return assoc.value;
}









// ---------------------------------------------------------------------


template <class BaseType>
CL_HashTableIterator<BaseType>::CL_HashTableIterator
    (const CL_HashTable<BaseType>& tbl)
: _table (tbl)
{
    Reset ();
}


template <class BaseType>
CL_HashTableIterator<BaseType>::~CL_HashTableIterator ()
{
}


template <class BaseType>
void CL_HashTableIterator<BaseType>::Reset ()
{
    _mainIndex = _auxIndex = _objRank = 0;
    CL_GenericSequence& data = *(CL_GenericSequence*) _table->_data;
    long n = data.Size();
    CL_GenericSequence* s = 0;
    for (_mainIndex = 0; _mainIndex < n; _mainIndex++) {
        s = (CL_GenericSequence*) data(_mainIndex);
        if (s)
            break;
    }
}



template <class BaseType>
bool CL_HashTableIterator<BaseType>::More ()
{
    return _objRank < _table.Size();
}


template <class BaseType>
const BaseType& CL_HashTableIterator<BaseType>::Next ()
{
//     CL_GenericSequence& data = *(CL_GenericSequence*) _table->_data;
//     long n = data.Size();
//     if (_mainIndex < n) {
//         long i;
//         CL_GenericSequence* s = 0;
//         for (i = _mainIndex; i < n; i++) {
//             s = (CL_GenericSequence*) data(i);
//             if (s)
//                 break;
//         }
//         if (!s)
//             return CL_Basics<BaseType>::NullValueRef();
//         if (!s->Size()) {
//             CL_Error::Warning ("CL_HashTableIterator: internal error: "
//                                "empty secondary sequence");
//             return CL_Basics<BaseType>::NullValueRef();
//         }
//         CL_GenericSequence& data = *(CL_GenericSequence*) _table->_data;
    return CL_Basics<BaseType>::NullValueRef(); // For now
}



#endif /* _htbl_imp_cxx_ */
