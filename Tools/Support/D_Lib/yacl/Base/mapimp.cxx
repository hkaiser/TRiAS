



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




#ifndef _mapimp_cxx_
#define _mapimp_cxx_  /* Prevent multiple includes */


#if defined(__CFRONT__) && !defined(__CFRONT_MAP_IMPL__)
#include "base/map.h"
#else


#ifdef __GNUC__
#pragma implementation
#endif

#define _no_cl_map_typedefs_
#include "base/map.h"
#include "base/stream.h"
#include "base/basicops.h"

// #include "base/long.h"
// #include "base/voidptr.h"
// #include "base/objptr.h"

#include "base/basicops.cxx"

#include <iostream.h>


#ifdef __BORLANDC__
#pragma warn -lvc
#endif

#if defined(__IBMCPP__)
#include "base/cmparatr.cxx"
#pragma define(CL_Comparator<CL_ObjectPtr>)
#endif



// -------------------- MapAssoc methods -----------------------------


template <class Key, class Value>
short CL_MapAssoc<Key, Value>::Compare (const CL_Object& o) const
{
    return CL_Basics<Key>::Compare
        (key, ((const CL_MapAssoc<Key,Value>&) o).key);
}


template <class Key, class Value>
CL_MapAssoc<Key, Value>::CL_MapAssoc ()
    : key (CL_Basics<Key>  ::NullValue()),
      value (CL_Basics<Value>::NullValue())
{
}


template <class Key, class Value>
CL_MapAssoc<Key, Value>::CL_MapAssoc
(const Key& k, const Value& v)
    : key (k), value (v)
{
}

template <class Key, class Value>
CL_MapAssoc<Key, Value>::CL_MapAssoc
(const CL_MapAssoc<Key,Value>& a)
    : key (a.key), value (a.value)
{
}

template <class Key, class Value>
void CL_MapAssoc<Key, Value>::operator=
(const CL_MapAssoc<Key,Value>& o)
{
    if (this != &o) {
        if (PrepareToChange()) {
            key   = o.key;
            value = o.value;
            Notify();
        }
    }
};



template <class Key, class Value>
CL_String CL_MapAssoc<Key, Value>::AsString () const
{
    return CL_Basics<Key>::PrintableForm(key) + " --> "
        + CL_Basics<Value>::PrintableForm (value);
}








// ------------------------ Map methods ---------------------------





template <class Key, class Value>
CL_Map<Key, Value>::CL_Map ()
    : _nullValue (CL_Basics<CL_MapAssoc<Key, Value> > :: NullValue())
{
}





template <class Key, class Value>
CL_Map<Key, Value>::CL_Map
    (CL_MapAssoc <Key, Value> assoc[], long count)
    : _nullValue (CL_Basics<CL_MapAssoc<Key, Value> > :: NullValue())
{
    if (!assoc)
        return;
    for (long i = 0; i < count; i++)
        Add (assoc[i].key, assoc[i].value);
}


template <class Key, class Value>
CL_Map<Key, Value>::CL_Map (const CL_Map<Key, Value>& m)
: _data (m.Size()),
  _nullValue (CL_Basics<CL_MapAssoc<Key, Value> > :: NullValue())

{
    long n = m.Size();
    for (long i = 0; i < n; i++)
        _data(i) = new CL_MapAssoc<Key, Value>
            (* (CL_MapAssoc<Key, Value>*) m._data(i));
}

         


template <class Key, class Value>
long CL_Map<Key, Value>::StorableFormWidth () const
{
    return sizeof (CL_ClassId) + _data.StorableFormWidth ();
}

template <class Key, class Value>
void CL_Map<Key, Value>::operator= (const CL_Object& o)
{
    if (CheckClassType (o, "CL_Map::op="))
        *this = ((const CL_Map<Key, Value>&) o);
}




//
// ---------------------- Element access -----------------------------
//

// IncludesKey: Tell whether the map includes the given key.
template <class Key, class Value>
bool CL_Map<Key, Value>::IncludesKey (const Key& key) const
{
    long index = 0;
    CL_MapAssoc<Key,Value> a;
    a.key = key;
    return (_data.BinarySearch (&a, index));
}


// op[]: return the value associated with the given key. The
// return value is a reference, and may be modified, resulting in
// modification of the map.
template <class Key, class Value>
Value& CL_Map<Key, Value>::operator []
    (const Key& key)
{
    long index = 0;
    CL_MapAssoc<Key,Value> a;

    a.key = key;
    if (_data.BinarySearch (&a, index)) {
        return ((CL_MapAssoc<Key,Value> *)_data(index))->value;
    }
    else {
        _nullValue.value =  CL_Basics<Value>::NullValue ();
        return _nullValue.value;
    }
}



template <class Key, class Value>
const Value& CL_Map<Key, Value>::operator []
    (const Key& key) const
{
    return ((CL_Map<Key, Value>*) this)->operator[] (key);
    // Throw away the const
}


template <class Key, class Value>
const CL_MapAssoc<Key, Value>& CL_Map<Key, Value>::ItemWithRank (long i) const
{
    i = maxl (0, minl (i, Size() - 1));
    return *(CL_MapAssoc<Key, Value>*) _data(i);
}



template <class Key, class Value>
long CL_Map<Key, Value>::RankOf (const Key& key) const
{
    long index = 0;
    Value p;
    CL_MapAssoc<Key,Value> a (key, p);
    bool b = _data.BinarySearch (&a, index);
    return b ? index : index+1;
}


//
// ------------------------- Modification ---------------------------
//


template <class Key, class Value>
bool CL_Map<Key, Value>::Add (const Key& key, const Value& value) 
{
    if (!PrepareToChange ())
        return FALSE;
    CL_MapAssoc<Key,Value>* p =
        new CL_MapAssoc<Key,Value> (key, value);
    if (!p)
        return FALSE;
    long index = 0;
    if (_data.BinarySearch (p, index)) {
        delete p;
        return FALSE;
    }
    if (_data.Insert (p, index)) {
        Notify ();
        return TRUE;
    }
    return FALSE;
}


    

template <class Key, class Value>
CL_MapAssoc<Key, Value> CL_Map<Key, Value>::Remove
     (const Key& key)
{
    if (!PrepareToChange ())
        return CL_Basics<CL_MapAssoc<Key, Value> >::NullValue();
    CL_MapAssoc<Key,Value> a;
    a.key = key;

    long i;
    if (!_data.BinarySearch (&a, i))
        return CL_Basics<CL_MapAssoc<Key, Value> >::NullValue();
    CL_MapAssoc<Key,Value>* p =
        (CL_MapAssoc<Key,Value>*) _data(i);
    if (_data.Remove (i)) {
        CL_MapAssoc<Key, Value> a = *p;
        delete p;
        Notify ();
        return a;
    }
    return CL_Basics<CL_MapAssoc<Key, Value> >::NullValue();
}




template <class Key, class Value>
void CL_Map<Key, Value>::operator=
    (const CL_Map<Key,Value>& o)
{
    if (this == &o)
        return;
    if (!PrepareToChange())
        return;
    _data.DestroyContents ();
    if (!_data.ChangeSize (o._data.Size()))
        return;
    for (long i = 0; i < o._data.Size(); i++)
        _data(i) = new CL_MapAssoc<Key, Value>
            (*(CL_MapAssoc<Key, Value>*) o._data(i));
    Notify();
}



template <class Key, class Value>
CL_Map<Key, Value>::~CL_Map ()
{
    _data.DestroyContents ();
}


template <class Key, class Value>
void CL_Map<Key, Value>::MakeEmpty ()
{
    if (PrepareToChange()) {
        _data.DestroyContents ();
        Notify();
    }
}


template <class Key, class Value>
void CL_Map<Key, Value>::DestroyContents ()
{
    if (!PrepareToChange())
        return;
    long size = _data.Size();
    for (long i = 0; i < size; i++) {
        CL_MapAssoc<Key, Value>* p = (CL_MapAssoc<Key, Value>*) _data(i);
        CL_Basics<Key>  ::DoDestroy (p->key);
        CL_Basics<Value>::DoDestroy (p->value);
    }
    _data.DestroyContents ();
    Notify();
}



template <class Key, class Value>
void CL_Map<Key, Value>::IntoStream (ostream& strm) const
{
    register long size = _data.Size();
    for (register long i = 0; i < size; i++) {
        CL_MapAssoc<Key, Value>* p =
            (CL_MapAssoc<Key, Value>*) _data(i);
        strm << p->AsString() << endl;
    }
}



template <class Key, class Value>
bool CL_Map<Key, Value>::_ReadKey (Key& key,
                                             const CL_Stream& s)
{
    return CL_Basics<Key>::Read (key, s);
}

template <class Key, class Value>
bool CL_Map<Key, Value>::_ReadValue (Value& v,
                                               const CL_Stream& s)
{
    return CL_Basics<Value>::Read (v, s);
}

template <class Key, class Value>
bool CL_Map<Key, Value>::ReadFrom (const CL_Stream& s)
{
    if (!PrepareToChange())
        return FALSE;
    _data.DestroyContents ();
    long sz;
    if (!s.Read (sz) || !_data.ChangeSize (sz))
        return FALSE;
    for (long i = 0; i < sz; i++) {
        CL_MapAssoc<Key, Value>* m = new CL_MapAssoc <Key, Value>;
        if (!m || !_ReadAssoc (*m, s))
            return FALSE;
        _data(i) = m;
    }
    Notify();
    return TRUE;
}







template <class Key, class Value>
bool CL_Map<Key, Value>::_WriteKey (const Key& key,
                                              CL_Stream& s) const
{
    return CL_Basics<Key>::Write (key, s);
}

template <class Key, class Value>
bool CL_Map<Key, Value>::_WriteValue (const Value& v,
                                                CL_Stream& s) const
{
    return CL_Basics<Value>::Write (v, s);
}

template <class Key, class Value>
bool CL_Map<Key, Value>::WriteTo (CL_Stream& s) const
{
    long size = _data.Size();
    if (!s.Write (size))
        return FALSE;
    for (long i = 0; i < size; i++) {
        CL_MapAssoc<Key, Value>* m = (CL_MapAssoc<Key, Value>*) _data(i);
        if (!m || !_WriteAssoc (*m, s))
            return FALSE;
    }
    return TRUE;
}








// -------------------------- MapIterator methods ---------------------

template <class Key, class Value>
CL_MapIterator<Key, Value>::CL_MapIterator (const CL_Map<Key,Value>& map)
: _map (map)
{
    _index = 0;
}


template <class Key, class Value>
CL_MapIterator<Key, Value>::CL_MapIterator
    (const CL_MapIterator<Key, Value>& itr)
: _map (itr._map)
{
    _index = itr._index;
}


template <class Key, class Value>
void CL_MapIterator<Key, Value>::Reset()
{
    _index = 0;
}


template <class Key, class Value>
void CL_MapIterator<Key, Value>::BeginFromRank (long l)
{
    _index = maxl (l, 0);
}


template <class Key, class Value>
bool CL_MapIterator<Key, Value>::More()
{
    return _index < _map.Size();
}




template <class Key, class Value>
const CL_MapAssoc<Key, Value>& CL_MapIterator<Key, Value>::Next()
{
    if (_index < _map.Size()) {
        CL_MapAssoc<Key, Value>* p =
            (CL_MapAssoc<Key, Value>*) _map._data(_index);
        _index++;
        return *p;
    }
    ((CL_Map<Key, Value>) _map)._nullValue =
        CL_Basics <CL_MapAssoc<Key, Value> >::NullValue();
    return _map._nullValue;
}



#endif /* CFRONT stuff */

#endif /* _mapimp_cxx_ */


