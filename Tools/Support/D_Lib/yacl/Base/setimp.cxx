



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



#ifndef _setimp_cxx_
#define _setimp_cxx_


#ifdef __GNUC__
#pragma implementation
#endif


#include "base/set.h"
#include "base/genseq.h"
#include "base/cmparatr.cxx"

template <class BaseType>
class YACL_BASE SetImplSeq: public CL_GenericSequence {
    // This is a private class used only for implementing the set.
public:
    SetImplSeq (long n = 0)
        : CL_GenericSequence(n, new CL_Comparator<BaseType>) {};

    ~SetImplSeq () {delete _cmp;};

};


#if !defined(__CFRONT__) || defined(__CFRONT_SET_IMPL__)

#include "base/bytstrng.h"
#include "base/binding.h"
#include "base/basicops.h"
#include "base/voidptr.h"


#ifdef __BORLANDC__
#pragma warn -lvc
#endif



template <class BaseType>
CL_Set<BaseType>::CL_Set()
    : _nullValue (CL_Basics<BaseType>::NullValue()) 
{
    _idata = new SetImplSeq<BaseType>;
}


template <class BaseType>
CL_Set<BaseType>::~CL_Set()
{
    if (_idata) {
        SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
        for (long i = data.Size()-1; i >= 0; i--)
            CL_Basics<BaseType>::Destroy (data(i));
        delete ((SetImplSeq<BaseType>*)_idata);
    }
}


/*----------------------------------------------------------------------- */

template <class BaseType>
CL_Set<BaseType>::CL_Set(void* p)
    : _nullValue (CL_Basics<BaseType>::NullValue()) 
{
    _idata = p;
}



/*----------------------------------------------------------------------- */



template <class BaseType>
CL_Set<BaseType>::CL_Set (const CL_Set<BaseType>& s)
    : _nullValue (CL_Basics<BaseType>::NullValue()) 
{
    _idata = new SetImplSeq<BaseType>;
    *this = s;
}






/*----------------------------------------------------------------------- */


//
// Add an object to the set. Return true on success.
//
template <class BaseType>
bool CL_Set<BaseType>::Add (const BaseType& o)
{
    if (!_idata || !PrepareToChange())
        return FALSE;
    long index = 0;
    if (_FindPos (o, index))
        return FALSE;
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    if (data.Insert (CL_Basics<BaseType>::MakeCopy(o), index)) {
        Notify ();
        return TRUE;
    }
    return FALSE;
}





/*----------------------------------------------------------------------- */
// Remove the object equal to o from the set (if it's there). Return
// true on success.
template <class BaseType>
BaseType CL_Set<BaseType>::Remove (const BaseType& o)
{
    if (!_idata || !PrepareToChange())
        return  CL_Basics<BaseType>::NullValue ();
    long i;
    if (!_FindPos (o, i))
        return  CL_Basics<BaseType>::NullValue ();
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    void* p = data.Remove (i);
    BaseType retVal (CL_Basics<BaseType>::Deref (p));
    CL_Basics<BaseType>::Destroy (p);
    Notify ();
    return retVal;
}




template <class BaseType>
long CL_Set<BaseType>::Size () const
{
    return ((SetImplSeq<BaseType>*) _idata)->Size();
}





/*----------------------------------------------------------------------- */
template <class BaseType>
void CL_Set<BaseType>::MakeEmpty ()
{
    if (!_idata || !PrepareToChange())
        return;
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    for (long i = data.Size()-1; i >= 0; i--)
        CL_Basics<BaseType>::Destroy (data(i));
    data.ChangeSize(0);
    Notify ();
}



/*----------------------------------------------------------------------- */


// Determine if o is in the set
template <class BaseType>
bool CL_Set<BaseType>::Includes (const BaseType& o) const
{
    if (!_idata)
        return FALSE;
    long i = 0;
    return _FindPos (o, i);
}




template <class BaseType>
long CL_Set<BaseType>::RankOf (const BaseType& o) const
{
    if (!_idata)
        return 0;
    long index;
    bool b = _FindPos (o, index);
    return b ? index : index+1;
}


template <class BaseType>
const BaseType& CL_Set<BaseType>::ItemWithRank (long i) const
{
    if (!_idata) {
        ((CL_Set<BaseType>*) this)->_nullValue =
            CL_Basics<BaseType>::NullValue(); // Cast away const
        return _nullValue;
    }
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    long n = data.Size();
    if (n <= 0) {
        ((CL_Set<BaseType>*) this)->_nullValue =
            CL_Basics<BaseType>::NullValue();
        return _nullValue;
    }
    i = maxl (0, minl (i, n-1));
    return CL_Basics<BaseType>::Deref (data(i));
}



/*----------------------------------------------------------------------- */

// Check if o is the same as this set
template <class BaseType>
bool CL_Set<BaseType>::operator== (const CL_Set<BaseType>& o) const
{
    if (!IsA (o))
        return FALSE;
    if (!_idata)
        return FALSE;
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& odata = (* (SetImplSeq<BaseType>*) o._idata);
    long n = o.Size();
    if (Size() != n)
        return FALSE;
    for (long i = 0; i < n; i++) {
        short result = CL_Basics<BaseType>::Compare
            (CL_Basics<BaseType>::Deref(data(i)),
             CL_Basics<BaseType>::Deref(odata(i)));
        if (result != 0)
            return FALSE;
    }
    return TRUE;
}




/*----------------------------------------------------------------------- */


// Assignment

template <class BaseType>
CL_Set<BaseType>& CL_Set<BaseType>::operator= (const CL_Set<BaseType>& s)
{
    if (this == &s || !_idata || !PrepareToChange())
        return *this;
    SetImplSeq<BaseType>& data  = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& odata = (* (SetImplSeq<BaseType>*) s._idata);
    long i = 0;
    for (i = Size() - 1; i >= 0; i--)
        CL_Basics<BaseType>::Destroy (data(i));
    long n = s.Size();
    if (data.ChangeSize (n)) {
        for (i = 0; i < n; i++)
            data(i) = CL_Basics<BaseType>::MakeCopy
                (CL_Basics<BaseType>::Deref (odata(i)));
        Notify ();
    }
    return *this;
}



/*----------------------------------------------------------------------- */
template <class BaseType>
void CL_Set<BaseType>::operator= (const CL_Object& o)
{
    if (CheckClassType (o, "CL_Set::op="))
        *this = ((const CL_Set<BaseType>&) o);
}




/*----------------------------------------------------------------------- */



template <class BaseType>
bool CL_Set<BaseType>::IncludesAll (const CL_Set<BaseType>& s) const
{
    if (!_idata)
        return FALSE;
    SetImplSeq<BaseType>&  data = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& sdata = (* (SetImplSeq<BaseType>*) s._idata);
    register long m = data.Size();
    register long n = sdata.Size();
    if (m < n)
        return FALSE;
    register long i = 0, j = 0, count = 0;
    while (i < m && j < n) {
        short result = CL_Basics<BaseType>::Compare
            (CL_Basics<BaseType>::Deref(data(i)),
             CL_Basics<BaseType>::Deref(sdata(j)));
        if (result < 0)
            i++;
        else if (result == 0) {
            i++; j++; count++;
        }
        else j++;
    }
    return count == n;
}

/*----------------------------------------------------------------------- */

template <class BaseType>
CL_Set<BaseType> CL_Set<BaseType>::operator* (const CL_Set<BaseType>& s) const
{
    if (!_idata)
        return CL_Set<BaseType> ();
    SetImplSeq<BaseType>&  data = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& sdata = (* (SetImplSeq<BaseType>*) s._idata);
    long m = data.Size();
    long n = sdata.Size();
    SetImplSeq<BaseType> *res   = new SetImplSeq<BaseType> (m+n);
    if (!res)
        return CL_Set<BaseType> ();
    long i = 0, j = 0, count = 0;
    while (i < m && j < n) {
        short result = CL_Basics<BaseType>::Compare
            (CL_Basics<BaseType>::Deref(data(i)),
             CL_Basics<BaseType>::Deref(sdata(j)));
        if (result < 0)
            i++;
        else if (result == 0) {
            (*res)(count++) = data(i);
            i++; j++;
        }
        else j++;
    }
    res->ChangeSize (count);
    return CL_Set<BaseType> (res);
}




template <class BaseType>
CL_Set<BaseType> CL_Set<BaseType>::operator+ (const CL_Set<BaseType>& s) const
{
    if (!_idata)
        return CL_Set<BaseType> ();
    SetImplSeq<BaseType>&  data = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& sdata = (* (SetImplSeq<BaseType>*) s._idata);
    long m = data.Size();
    long n = sdata.Size();
    SetImplSeq<BaseType> *res   = new SetImplSeq<BaseType> (m+n);
    if (!res)
        return CL_Set<BaseType> ();
    long i = 0, j = 0, count = 0;
    while (i < m || j < n) {
        short result = (i >= m) ? 1
            : ((j >= n) ? -1
               : CL_Basics<BaseType>::Compare
               (CL_Basics<BaseType>::Deref(data(i)),
                CL_Basics<BaseType>::Deref(sdata(j))
               )
              );
        if (result < 0) {
            (*res)(count) = data(i);
            i++;
        }
        else if (result == 0) {
            (*res)(count) = data(i);
            i++; j++;
        }
        else {
            (*res)(count) = sdata(j);
            j++;
        }
        count++;
    }
    res->ChangeSize (count);
    return CL_Set<BaseType> (res);
}



template <class BaseType>
CL_Set<BaseType> CL_Set<BaseType>::operator- (const CL_Set<BaseType>& s) const
{
    if (!_idata)
        return CL_Set<BaseType> ();
    SetImplSeq<BaseType>&  data = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& sdata = (* (SetImplSeq<BaseType>*) s._idata);
    long m = data.Size();
    long n = sdata.Size();
    SetImplSeq<BaseType> *res   = new SetImplSeq<BaseType> (m+n);
    if (!res)
        return CL_Set<BaseType> ();
    long i = 0, j = 0, count = 0;
    while (i < m) {
        short result = (j >= n) ? -1
            : CL_Basics<BaseType>::Compare
                (CL_Basics<BaseType>::Deref(data(i)),
                 CL_Basics<BaseType>::Deref(sdata(j)));
        if (result < 0) {
            (*res)(count++) = data(i);
            i++;
        }
        else if (result == 0) {
            i++; j++;
        }
        else {
            j++;
        }
    }
    res->ChangeSize (count);
    return CL_Set<BaseType> (res);
}





template <class BaseType>
CL_Set<BaseType> CL_Set<BaseType>::operator^ (const CL_Set<BaseType>& s) const
{
    if (!_idata)
        return CL_Set<BaseType> ();
    SetImplSeq<BaseType>&  data = (* (SetImplSeq<BaseType>*) _idata);
    SetImplSeq<BaseType>& sdata = (* (SetImplSeq<BaseType>*) s._idata);
    long m = data.Size();
    long n = sdata.Size();
    SetImplSeq<BaseType> *res   = new SetImplSeq<BaseType> (m+n);
    if (!res)
        return CL_Set<BaseType> ();
    long i = 0, j = 0, count = 0;
    while (i < m) {
        short result = (j >= n) ? -1
            : CL_Basics<BaseType>::Compare
            (CL_Basics<BaseType>::Deref(data(i)),
             CL_Basics<BaseType>::Deref(sdata(j)));
        if (result < 0) {
            (*res)(count++) = data(i);
            i++;
        }
        else if (result == 0) {
            i++; j++;
        }
        else {
            (*res)(count++) = sdata(j);
            j++;
        }
    }
    res->ChangeSize (count);
    return CL_Set<BaseType> (res);
}








/*----------------------------------------------------------------------- */
    
    

template <class BaseType>
CL_Set<BaseType>& CL_Set<BaseType>::operator += (const CL_Set<BaseType>& s)
{
    // Notification done by operator=
    *this = (*this) + s;
    return *this;
}



/*----------------------------------------------------------------------- */


// Set intersection

template <class BaseType>
CL_Set<BaseType>& CL_Set<BaseType>::operator *= (const CL_Set<BaseType>& s)
{
    (*this) = (*this) * s;
    return *this;
}



/*----------------------------------------------------------------------- */


// Set difference

template <class BaseType>
CL_Set<BaseType>& CL_Set<BaseType>::operator -= (const CL_Set<BaseType>& s)
{
    (*this) = (*this) - s;
    return *this;
}



/*----------------------------------------------------------------------- */



// Symmetric difference (xor)

template <class BaseType>
CL_Set<BaseType>& CL_Set<BaseType>::operator ^= (const CL_Set<BaseType>& s)
{
    (*this) = (*this) ^ s;
    return *this;
}



/*----------------------------------------------------------------------- */



template <class BaseType>
bool CL_Set<BaseType>::_ReadElement (const CL_Stream& s,
                                     BaseType& element)
{
    return CL_Basics<BaseType>::Read  (element, s);
}




template <class BaseType>
bool CL_Set<BaseType>::ReadFrom (const CL_Stream& s)
{
    if (!PrepareToChange())
        return FALSE;
    CL_ClassId id;
    if (!s.Read (id) || id != ClassId())
        return FALSE;
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    long n;
    if (!s.Read (n))
        return FALSE;
    long curSize = data.Size();
    if (n < curSize) {
        for (long i = n; i < curSize; i++)
            CL_Basics<BaseType>::Destroy (data(i));
        if (!data.ChangeSize (n))
            return FALSE;
    }
    else if (n > curSize) {
        if (!data.ChangeSize (n))
            return FALSE;
        for (long i = curSize; i < n; i++)
            data(i) = CL_Basics<BaseType>::MakeCopy (_nullValue);
    }
    for (register long i = 0; i < n; i++) {
        BaseType& b = CL_Basics<BaseType>::Deref (data(i));
        if (!_ReadElement (s, b))
            return FALSE;
    }
    Notify ();
    return TRUE;
}


template <class BaseType>
bool CL_Set<BaseType>::_WriteElement (CL_Stream& s, const BaseType& e) const
{
    return CL_Basics<BaseType>::Write (e, s);
}




template <class BaseType>
bool CL_Set<BaseType>::WriteTo  (CL_Stream& s) const
{
    if (!_idata)
        return FALSE;
    CL_Sequence<void*>& data = (* (CL_Sequence<void*>*) _idata);
    register long n = Size();
    if (!s.Write (ClassId()) || !s.Write (n) )
        return FALSE;
    for (register long i = 0; i < n; i++) {
        if (!_WriteElement (s, CL_Basics<BaseType>::Deref(data(i))))
            return FALSE;
    }
    return TRUE;
}





template <class BaseType>
long CL_Set<BaseType>::StorableFormWidth () const
{
    long siz = 0;
    CL_Sequence<void*>& data = (* (CL_Sequence<void*>*) _idata);
    for (long i = Size()-1; i >= 0; i--)
        siz += CL_Basics<BaseType>::StoreWidth
            (CL_Basics<BaseType>::Deref (data(i)));
    return sizeof (CL_ClassId) + siz;
}


//
// Protected CL_Set methods
//


template <class BaseType>
bool CL_Set<BaseType>::_FindPos (const BaseType& o, long& pos) const
{
    pos = -1;
    if (!_idata)
        return FALSE;
    CL_VoidPtr p = CL_Basics<BaseType>::MakePointer (o);
    SetImplSeq<BaseType>& data = (* (SetImplSeq<BaseType>*) _idata);
    return data.BinarySearch (p, pos);
}




    
/*----------------------------------------------------------------------- */


//
//------------------------------------------------------------
//

// CL_SetIterator methods

typedef CL_Binding0<CL_Object> CL_ObjectBinding0;

template <class BaseType>
CL_SetIterator<BaseType>::CL_SetIterator (const CL_Set<BaseType>& o)
    :_set (o) 
{
    _index = 0;
    CL_ObjectBinding0 bind
        (this, (CL_ObjectBinding0::MethodPtr)
         &CL_SetIterator<BaseType>::_SetModified);
    ((CL_Set<BaseType>&) _set).AddPreChangeDependent (bind);
}

template <class BaseType>
CL_SetIterator<BaseType>::~CL_SetIterator ()
{
    CL_ObjectBinding0 bind
        (this, (CL_ObjectBinding0::MethodPtr)
         &CL_SetIterator<BaseType>::_SetModified);
    ((CL_Set<BaseType>&) _set).RemovePreChangeDependent (bind);
}



/*----------------------------------------------------------------------- */

template <class BaseType>
CL_SetIterator<BaseType>::CL_SetIterator (const CL_SetIterator<BaseType>& s)
    :_set (s._set), _index (s._index)
{
    CL_ObjectBinding0 bind
        (this, (CL_ObjectBinding0::MethodPtr)
         &CL_SetIterator<BaseType>::_SetModified);
    ((CL_Set<BaseType>&) _set).AddPreChangeDependent (bind);
}



/*----------------------------------------------------------------------- */

template <class BaseType>
void CL_SetIterator<BaseType>::Reset ()
{   
    _index = 0;
}


/*----------------------------------------------------------------------- */

template <class BaseType>
void CL_SetIterator<BaseType>::BeginFromRank (long l)
{   
    _index = maxl (0, l);
}


/*----------------------------------------------------------------------- */

template <class BaseType>
const BaseType& CL_SetIterator<BaseType>::Next ()
{
    register SetImplSeq<BaseType>* data = (SetImplSeq<BaseType>*)
        _set._idata;
    if (data && (_index < data->Size()) )
        return CL_Basics<BaseType>::Deref ((*data)(_index++));
    ((CL_Set<BaseType>&) _set)._nullValue =
        CL_Basics<BaseType>::NullValue();
    return _set._nullValue;
}



/*----------------------------------------------------------------------- */

template <class BaseType>
bool CL_SetIterator<BaseType>::More ()
{
    return _index < _set.Size();
}






/*----------------------------------------------------------------------- */


template <class BaseType>
bool CL_SetIterator<BaseType>::_SetModified ()
{
    if (_index >= 0 && _index < _set.Size())
        CL_Error::Warning ("SetIterator %08x: Attempt to modify Set %08x "
                           " while iterator active", this, &_set);
    return TRUE;
}



#endif /* CFRONT stuff */

#endif /* _setimp_cxx_ */

