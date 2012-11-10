



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





#ifdef __GNUC__
#pragma implementation
#endif


#include "base/seqimp.cxx"    // Include this first, to appease GNU C++

#include "base/objptr.h"
#include "base/objseq.h"
#include "base/stream.h"
#include "base/cmparatr.h"


// Instantiate the sequence:
#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
template class CL_Sequence<CL_ObjectPtr>;
template class CL_Basics<CL_ObjectPtr>;
#endif

#if defined(_MSC_VER)
template CL_Sequence<CL_ObjectPtr>;
#endif


#if defined(__IBMCPP__)
#include "base/cmparatr.cxx"
#pragma define(CL_Sequence<CL_ObjectPtr>)
#pragma define(CL_Basics<CL_ObjectPtr>)
#pragma define(CL_Comparator<CL_ObjectPtr>)
#elif defined(__SGI_DELTA_CC__)
#pragma instantiate CL_Sequence<CL_ObjectPtr>
#pragma instantiate CL_Basics<CL_ObjectPtr>
#pragma instantiate CL_Comparator<CL_ObjectPtr>
#endif



typedef CL_Sequence<CL_ObjectPtr> CL_PtrSeq;  // Don't use this: use the class
                                              // CL_ObjectSequence instead.


CL_ObjectSequence::CL_ObjectSequence (long initial_size, CL_ObjectBuilder* b)
: CL_Sequence<CL_ObjectPtr> (initial_size), _bld (b)
{
    _cmp = NULL;
}


CL_ObjectSequence::CL_ObjectSequence
    (const CL_ObjectPtr data[], long count, CL_ObjectBuilder* b)
: CL_Sequence<CL_ObjectPtr> (data, count), _bld (b)
{
    _cmp = NULL;
}

CL_ObjectSequence::CL_ObjectSequence (const CL_ObjectSequence& s)
: CL_Sequence<CL_ObjectPtr> (s), _bld (s._bld)
{
    _cmp = NULL;
}


CL_ObjectSequence::~CL_ObjectSequence ()
{
}




void CL_ObjectSequence::DestroyContents ()
{
    if (!PrepareToChange())
        return;
    long n = Size();
    for (long i = 0; i < n; i++) {
        CL_ObjectPtr p = (*this)[i];
        if (p)
            delete p;
    }
    _size = 0;
    Notify ();
}



bool CL_ObjectSequence::_ReadElement (const CL_Stream& s, long i)
{
    if (_bld) {
        CL_Object* p =_bld->BuildFrom (s);
        (*this)[i] = p;
        return p != NULL;
    }
    return s.Read ((*this)[i]);
}


bool CL_ObjectSequence::_WriteElement (CL_Stream& s, long i) const
{
    return s.Write ((*this)[i]);
}



CL_Sequence<CL_ObjectPtr>& CL_ObjectSequence::operator=
    (const CL_Sequence<CL_ObjectPtr>& o)
{
    CL_Sequence<CL_ObjectPtr>::operator= (o);
    return *this;
}


void CL_ObjectSequence::operator= (const CL_Object& o)
{
    if (o.IsA (*this))
        operator= ((const CL_Sequence<CL_ObjectPtr>&) o);
}


void CL_ObjectSequence::Sort (const CL_AbstractComparator& cmp)
{
    _cmp = &(CL_AbstractComparator&) cmp;
    CL_Sequence<CL_ObjectPtr>::Sort ();
    _cmp = NULL;
}

short CL_ObjectSequence::_Compare (const CL_ObjectPtr& p1, const
                                  CL_ObjectPtr& p2) const
{
    return _cmp ? (*_cmp) (p1, p2)
        : CL_Sequence<CL_ObjectPtr>::_Compare (p1, p2);
}

