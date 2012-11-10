



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







#ifndef _seqimp_cxx_ /* Sun Nov  7 12:38:41 1993 */
#define _seqimp_cxx_


#ifdef __GNUC__
#pragma implementation
#endif

// Helper class for managing segments

#include "base/defs.h"


#if defined(__CFRONT__) && !defined(__CFRONT_SEQUENCE_IMPL__)
#include "base/sequence.h"
#else


// Implementation of the sequence data structure
// Invariants maintained:
//     - Initially nullify all cells from 0 to _size-1.




#include "base/sequence.h" 
#include "base/intset.h"
#include "base/basicops.h"
#include "base/stream.h"

#include "base/segseq.h"


//                                                                     
// ------------------------ Creation and destruction --------------    
//


template <class BaseType>
CL_Sequence<BaseType>::CL_Sequence (long initial_size)
    : _nullValue (CL_Basics<BaseType>::NullValue())
{
    _idata = new CL_SegmentedSequence (initial_size);
    if (_idata)
        _size = initial_size;
    else
        _size = 0;
    if (_idata) {
        CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
        for (long i = 0; i < _size; i++)
            _data[i] = CL_Basics<BaseType>::MakeCopy (_nullValue);
    }
}




template <class BaseType>
CL_Sequence<BaseType>::CL_Sequence (const BaseType s[], long count)
    : _nullValue (CL_Basics<BaseType>::NullValue())
{
    _idata = new CL_SegmentedSequence (count);
    if (_idata)
        _size = count;
    else
        _size = 0;
    if (_idata) {
        _size = count;
        CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
        for (long i = 0; i < count; i++)
            _data[i] = CL_Basics<BaseType>::MakeCopy (s[i]);
    }
    else
        _size = 0;
}


// Copy constructor
template <class BaseType>
CL_Sequence<BaseType>::CL_Sequence (const CL_Sequence<BaseType>& a)
    : _nullValue (CL_Basics<BaseType>::NullValue())
{
    _size = 0;
    _idata = new CL_SegmentedSequence;
    if (_idata)
        *this = a;
}






//
// ------------------------ Element access ---------------------------

template <class BaseType>
long CL_Sequence<BaseType>::Add (const BaseType& o)
{
    long pos = Size()-1;
    return Insert (o, pos) ? pos+1 : -1;
}


template <class BaseType>
bool CL_Sequence<BaseType>::Insert (const BaseType& o, long i)
{
    if (!PrepareToChange() ||  !_DoInsert (o, i))
        return FALSE;
    Notify ();
    return TRUE;
}
            

template <class BaseType>
BaseType& CL_Sequence<BaseType>::operator[] (long index) const
{
#ifndef CL_NO_SUBSCRIPT_CHECK
    if (!_idata) {
        ((CL_Sequence<BaseType>*) this)->_nullValue =
            CL_Basics<BaseType>::NullValue();
        return (BaseType&) _nullValue;
    }
    if (index < 0 ||  index >= _size) {
        CL_Error::Warning ("CL_Sequence::op[]: index %ld"
                           " out of range 0..%ld", index, _size-1);
        ((CL_Sequence<BaseType>*) this)->_nullValue =
            CL_Basics<BaseType>::NullValue();
        return (BaseType&) _nullValue;
    }
#endif
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    return CL_Basics<BaseType>::Deref (_data[index]);
}

template <class BaseType>
BaseType& CL_Sequence<BaseType>::operator() (long index) const
{
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    return CL_Basics<BaseType>::Deref (_data[index]);
}



template <class BaseType>
short CL_Sequence<BaseType>::_Compare (const BaseType& o1,
                                       const BaseType& o2) const
{
    return CL_Basics<BaseType>::Compare (o1, o2);
}







template <class BaseType>
short CL_Sequence<BaseType>::_DoInsert (const BaseType& o, long i)
{
    if (i < -1 || (i >= _size && _size > 0))
        return FALSE;
    if (!_idata) {
        return FALSE;
    }
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    if (i == _size-1) {
        if (!_data.ResizeTo (_size+1))
            return FALSE;
        _data[i+1] = CL_Basics<BaseType>::MakeCopy (o);
        _size++;
    }
    else {
        if (!_ShiftRightAt (i+1, 1))
            return FALSE;
        (*this)(i+1) = o;
    }
    return TRUE;
}







template <class BaseType>
long CL_Sequence<BaseType>::InsertByRank (const BaseType& o)
{
    if (!_idata || !PrepareToChange())
        return FALSE;
    register long i;
    register long n = Size();
    for (i = 0; i < n; i++)
        if (CL_Basics<BaseType>::Compare ((*this)(i), o) >= 0)
            break;
    if (_DoInsert (o, i)) {
        Notify();
        return i;
    }
    return -1;
}



template <class BaseType>
BaseType CL_Sequence<BaseType>::Remove (long i)
{
    if (!PrepareToChange() || !_idata || _size <= 0 || i < 0 || i >= _size)
        return CL_Basics<BaseType>::NullValue();
    BaseType r = (*this)(i);
    if (_ShiftLeftAt (i+1, 1)) {
        Notify ();
        return r;
    }
    return CL_Basics<BaseType>::NullValue();
}


template <class BaseType>
BaseType CL_Sequence<BaseType>::ExtractLeftmost ()
{
    if (!_idata || _size <= 0 || !PrepareToChange())
        return CL_Basics<BaseType>::NullValue ();
    BaseType p = (*this)(0);
    _ShiftLeftAt (1,1);
    Notify ();
    return p;
}

template <class BaseType>
BaseType CL_Sequence<BaseType>::ExtractRightmost ()
{
    BaseType p;
    if (!_idata || _size <= 0 || !PrepareToChange())
        return CL_Basics<BaseType>::NullValue ();
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    p = (*this)(_size-1);
    CL_Basics<BaseType>::Destroy (_data[_size-1]);
    _size--;
    _data.ResizeTo (_size);
    Notify ();
    return p;
}




// ------------------- Sequence methods ------------------------

template <class BaseType>
bool CL_Sequence<BaseType>::ShiftRightAt (long pos, long amount)
{
    if (!PrepareToChange ())
        return FALSE;
    if (!_ShiftRightAt (pos, amount))
        return FALSE;
    Notify();
    return TRUE;
}




template <class BaseType>
bool CL_Sequence<BaseType>::_ShiftRightAt (long pos, long amount)
{
    if (pos < 0 || pos > _size || amount < 0)
        return FALSE;
    if (!_idata) {
        return FALSE;
    }
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    if (!_data.ResizeTo (_size + amount))
        return FALSE;
    long i;
    for (i = _size + amount - 1; i > pos; i--)
        _data[i] = _data [i-amount];
    for (i = pos; i < pos + amount; i++) {
        _data[i] = CL_Basics<BaseType>::MakeCopy (_nullValue);
    }
    _size += amount;
    return TRUE;
}



template <class BaseType>
void CL_Sequence<BaseType>::operator= (const CL_Object& o)
{
    if (CheckClassType (o, "CL_Sequence::op="))
        *this = ((const CL_Sequence<BaseType>&) o);
}

template <class BaseType>
CL_Sequence<BaseType>& CL_Sequence<BaseType>::operator=
    (const CL_Sequence<BaseType>& a)
{
    if (this == &a || !PrepareToChange())
        return *this; // Do nothing
    long i;
    
    if (!_idata)
        return *this;
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    for (i = 0; i < _size; i++)
        CL_Basics<BaseType>::Destroy (_data[i]);
    if (!_data.ResizeTo (a.Size()))
        return *this;
    _size = a.Size();
    for (i = 0; i < _size; i++) {
        _data[i] = CL_Basics<BaseType>::MakeCopy (a[i]);
    }
    Notify ();
    return *this;
}



template <class BaseType>
CL_Sequence<BaseType>& CL_Sequence<BaseType>::operator +=
    (const CL_Sequence<BaseType>& a)
{
    if (!_idata) {
        return *this;
    }
    if (!PrepareToChange())
        return *this;
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    if (!_data.ResizeTo (_size + a._size))
        return *this;
    long old_size = _size;
    _size += a._size;
    register long n = a._size; 
    for (long i = 0; i < n; i++) {
        _data [old_size + i] = CL_Basics<BaseType>::MakeCopy (a(i));
    }
    Notify ();
    return *this;
}



template <class BaseType>
CL_Sequence<BaseType> CL_Sequence<BaseType>::Subsequence
    (const CL_IntegerSet& s) const
{
    register long m = Size();
    CL_Sequence<BaseType> retVal;
    // Note that we cannot declare retVal to be of a particular size,
    // because we don't know how many elements of s represent legal
    // indices in this sequence. Well, maybe we could do something like
    //     CL_IntegerSet t (0, Size()-1); t *= s;
    // and then use t's size to be the initial size of retVal. But that
    // will likely not save much of the overhead incurred by expanding
    // retVal if it weren't pre-sized.
    for (long i = 0; i < m; i++)
        if (s.Includes (i)) {
            retVal.Add ((*this)(i));
        }
    return retVal;
}


template <class BaseType>
CL_Sequence<BaseType> CL_Sequence<BaseType>::operator-
    (const CL_IntegerSet& s) const
{
    CL_IntegerSet t (0, Size()-1);
    return Subsequence (t-s);
}

template <class BaseType>
void CL_Sequence<BaseType>::operator-= (const CL_IntegerSet& s)
{
    Remove (s);  // Remove does the notification
}


template <class BaseType>
CL_Sequence<BaseType> CL_Sequence<BaseType>::Remove (const CL_IntegerSet& s)
{
    CL_Sequence<BaseType> p;
    Move (s, p);  // Move does the notification
    return p;
}


template <class BaseType>
long  CL_Sequence<BaseType>::Move (const CL_IntegerSet& s,
                                   CL_Sequence<BaseType>& toSeq)
{
    register long m = Size();
    long oldSize = toSeq.Size();
    if (!_idata)
        return 0; // No memory
    CL_IntegerSet t = s * CL_IntegerSet (0, m-1);
    long n = t.Size();
    if (n <= 0)
        return 0;
    if (!PrepareToChange() || !toSeq.PrepareToChange())
        return 0;
    CL_SegmentedSequence& _data  = (* (CL_SegmentedSequence*) _idata);
    CL_SegmentedSequence& _data2 = (* (CL_SegmentedSequence*) toSeq._idata);
    if (!_data2.ResizeTo (oldSize + n))
        return 0;
    long current = t.ItemWithRank (0);
    for (register long i = 0; i < n; i++) {
        long next = i < n-1 ? t.ItemWithRank (i+1) : m;
        _data2[oldSize + i] = _data[current];
        for (register long j = current+1; j < next; j++)
            _data[j-i-1] = _data[j];
        current = next;
    }
    _data.ResizeTo (m - n);
    _size = m-n;
    toSeq._size = oldSize + n;
    Notify ();
    toSeq.Notify();
    return n;
}


template <class BaseType>
void CL_Sequence<BaseType>::MakeEmpty ()
{
    if (!_idata) {
        return;
    }
    if (!PrepareToChange())
        return;
    _DoMakeEmpty ();
    Notify ();
}

template <class BaseType>
void CL_Sequence<BaseType>::_DoMakeEmpty ()
{
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    for (long i = 0; i < _size; i++)
        CL_Basics<BaseType>::Destroy (_data[i]);
    _size = 0;
    _data.ResizeTo (0);
}






template <class BaseType>
bool CL_Sequence<BaseType>::ChangeSize (long new_size)
{
    if (!PrepareToChange ())
        return FALSE;
    if (!_idata)
        return FALSE;
    if (new_size == _size)
        return TRUE;
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    if (new_size < _size) {
        for (register long i = new_size; i < _size; i++)
            CL_Basics<BaseType>::Destroy (_data[i]);
    }
    if (!_data.ResizeTo (new_size))
        return FALSE;
    if (new_size > _size)  {
        for (register long i = _size; i < new_size; i++)
            _data[i] = CL_Basics<BaseType>::MakeCopy (_nullValue);
    }
    _size = new_size;
    Notify();
    return TRUE;
}








template <class BaseType>
bool CL_Sequence<BaseType>::ShiftLeftAt (long pos, long amount)
{
    if (!PrepareToChange ())
        return FALSE;
    if (!_ShiftLeftAt (pos, amount))
        return FALSE;
    Notify();
    return TRUE;
}



template <class BaseType>
bool CL_Sequence<BaseType>::_ShiftLeftAt (long pos, long amount)
{
    if (!_idata || pos < 1 || pos > _size || amount > pos)
        return FALSE;
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    long i;
    for (i = pos-amount; i < pos; i++)
        CL_Basics<BaseType>::Destroy (_data[i]);
    for (i = pos; i < _size; i++) {
        _data[i-amount] = _data[i];
    }
    for (i = _size-amount; i < _size; i++)
        _data[i] = NULL;
    _size -= amount;
    _data.ResizeTo (_size);
    return TRUE;
}


template <class BaseType>
bool CL_Sequence<BaseType>::IsSorted () const
{
    long i;
    for (i = 0; i < _size-1; i++)
        if (_Compare ((*this)(i), (*this)(i+1)) > 0)
            return FALSE;
    return TRUE;
}





template <class BaseType>
bool CL_Sequence<BaseType>::Sort (long pos, long len)
{
    if (!_idata || !PrepareToChange())
        return FALSE;
    if (pos < 0 || pos >= _size)
        return FALSE;
    if (_QuickSort (pos, minl (pos + len - 1, _size - 1))) {
        Notify ();
        return TRUE;
    }
    return FALSE;
}






template <class BaseType>
long CL_Sequence<BaseType>::LinearSearch (const BaseType& o) const
{
    if (!_idata || _size == 0)
        return -1;
    long i;
    short result;
    for (i = 0; i < _size; i++) {
        result = _Compare ((*this)(i), o);
        if (result == 0)
            return i;
    }
    return -1;
}






template <class BaseType>
bool CL_Sequence<BaseType>::BinarySearch (const BaseType& o, long& index) const
{
    if (!_idata)
        return FALSE;
    long i;
    short result;
    if (_size <= 7) { // Small number of keys, do a linear search
        if (_size == 0) {
            index = -1;
            return FALSE;
        }
        for (i = 0; i < _size; i++) {
            result = _Compare ((*this)(i), o);
            if (result >= 0)
                break;
        }
        if (result == 0) {
            index = i;
            return TRUE;
        }
        else  {
            index = i-1;
            return FALSE;
        }
    }

    // Do a binary search
    long lo = 0, hi = _size-1, mid;
    while (lo <= hi) {
        mid = (lo + hi)/2;
        result = _Compare ((*this)(mid), o);
        if (result == 0) {
            index = mid;
            break;
        }
        if (result < 0)
            lo = mid+1;
        else
            hi = mid-1;
    }
    if (result == 0) {
        // Find the first occurrence
        index = mid;
        long i = index-1;
        for (; i >= 0; i--) {
            if (_Compare ((*this)(i), o) < 0)
                break;
        }
        index = i+1;
        return TRUE;
    }
        
    index = result < 0 ? mid :  mid-1;
    return FALSE;
}







// #include <stdlib.h>

template <class BaseType>
bool CL_Sequence<BaseType>::_QuickSort (long left, long right)
{
    if (!_idata) {
        return FALSE;
    }
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);

    // The sort code is basically stolen from Bentley's "Programming
    // Pearls" book.
    long i;

    for (i = left; i < right; i++) // Scan to see if already sorted
        if (_Compare ((*this)(i), (*this)(i+1)) > 0)
            break;
    if (i >= right) // It's already sorted
        return FALSE;

    while (left < right) {
        CL_VoidPtr tmp;
        long r, m;
        // r = random (right - left - 1) + left + 1;
        r = left + 1;

        tmp         = _data[r];
        _data[r]    = _data[left];
        _data[left] = (CL_VoidPtr) tmp;

        m = left;
        for (i = left+1; i <= right; i++) {
            if (_Compare ((*this)(i), (*this)(left))
                < 0) {
                m ++;
                tmp      = _data[m];
                _data[m] = _data[i];
                _data[i] = tmp;
            }
        }
        tmp         = _data[m];
        _data[m]    = _data[left];
        _data[left] = tmp;

        // Now recurse on the smaller half, and loop back for the
        // bigger half so as to minimize stack depth
        if (m-left < right-m) {
            _QuickSort (left, m-1);
            left = m+1;
        }
        else {
            _QuickSort (m+1, right);
            right = m-1;
        }
    }
    return TRUE;
}






template <class BaseType>
long CL_Sequence<BaseType>::StorableFormWidth () const
{
    if (!_idata) {
        return 0;
    }
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    long l = 0;
    for (long i = 0; i < _size; i++)
        l += CL_Basics<BaseType>::StoreWidth
            (CL_Basics<BaseType>::Deref (_data [i]));
    return l + (sizeof _size) + sizeof (CL_ClassId);
}




template <class BaseType>
bool CL_Sequence<BaseType>::ReadFrom (const CL_Stream& s)
{
    if (!_idata) {
        return FALSE;
    }
    if (!PrepareToChange() || !ReadClassId (s) )
        return FALSE;
    CL_SegmentedSequence& _data = (* (CL_SegmentedSequence*) _idata);
    long size;
    if (!s.Read (size))
        return FALSE;
    if (size < _size) {
        for (long i = size; i < _size; i++)
            CL_Basics<BaseType>::Destroy (_data[i]);
        if (!_data.ResizeTo (size))
            return FALSE;
    }
    else {
        if (!_data.ResizeTo (size))
            return FALSE;
        for (long i = _size; i < size; i++)
            _data[i] = CL_Basics<BaseType>::MakeCopy  (_nullValue);
    }
    _size = size;
    for (long i = 0; i < _size; i++)
        _ReadElement (s, i);
    Notify();
    return TRUE;
};
        

template <class BaseType>
bool CL_Sequence<BaseType>::_ReadElement (const CL_Stream& s, long i)
{
    return CL_Basics<BaseType>::Read ((*this)(i), s);
}





template <class BaseType>
bool CL_Sequence<BaseType>::WriteTo (CL_Stream& s) const
{
    if (!_idata) {
        return FALSE;
    }
    if (!s.Write (ClassId())  || !s.Write (_size))
        return FALSE;
    for (long i = 0; i < _size; i++) {
        if (!_WriteElement (s, i))
            return FALSE;
    }
    return TRUE;
}


template <class BaseType>
bool CL_Sequence<BaseType>::_WriteElement (CL_Stream& s, long i) const
{
    return CL_Basics<BaseType>::Write ((*this)(i), s);
}




template <class BaseType>
CL_Sequence<BaseType>::~CL_Sequence ()
{
    _DoMakeEmpty ();
    if (_idata)
        delete (CL_SegmentedSequence*) _idata;
}






//
//------------------------------------------------------------
//

// CL_SequenceIterator methods


template <class BaseType>
CL_SequenceIterator<BaseType>::CL_SequenceIterator
    (const CL_Sequence<BaseType>& o)
:_seq (o) 
{
    _index = 0;
}



/*----------------------------------------------------------------------- */

template <class BaseType>
CL_SequenceIterator<BaseType>::CL_SequenceIterator
    (const CL_SequenceIterator<BaseType>& s)
    :_seq (s._seq), _index (s._index)
{
}



/*----------------------------------------------------------------------- */

template <class BaseType>
void CL_SequenceIterator<BaseType>::Reset ()
{   
    _index = 0;
}


/*----------------------------------------------------------------------- */

template <class BaseType>
const BaseType& CL_SequenceIterator<BaseType>::Next ()
{
    return _seq(_index++);
}



/*----------------------------------------------------------------------- */

template <class BaseType>
bool CL_SequenceIterator<BaseType>::More ()
{
    return _index < _seq.Size();
}






#endif /* CFRONT stuff */

#endif   /* _seqimp_cxx */

