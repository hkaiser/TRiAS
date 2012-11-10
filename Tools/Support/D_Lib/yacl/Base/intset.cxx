



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



#include "base/setimp.cxx"
#include "base/cmparatr.cxx"

#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
template class CL_Set<long>;
template class CL_Iterator<long>;
template class CL_SetIterator<long>;
template class CL_Binding0<CL_SetIterator<long> >;
template class SetImplSeq<long>;
#elif defined(_MSC_VER)
// The following pragma is needed to disable a warning about CL_Iterator
// methods not neing available:
#pragma warning (disable:4661)

template CL_Set<long>;
template CL_Iterator<long>;
template CL_SetIterator<long>;
template CL_Binding0<CL_SetIterator<long> >;
template SetImplSeq<long>;

#elif defined(__SGI_DELTA_CC__)
#    pragma instantiate CL_Set<long>
#    pragma instantiate CL_Iterator<long>
#    pragma instantiate CL_SetIterator<long>
#    pragma instantiate CL_Binding0<CL_SetIterator<long> >
#    pragma instantiate SetImplSeq<long>
#endif


#include "base/string.h"
#include "base/intset.h"
#include "base/sequence.h"
#include "base/long.h"



#if defined(__IBMCPP__)
#pragma define(CL_Set<long>)
#pragma define(CL_SetIterator<long>)
#pragma define(CL_Basics<long>)
#endif





CL_IntegerSet::CL_IntegerSet (long lo, long hi)
{
    if (!_idata)
        return;
    CL_Sequence<long>& data = *(CL_Sequence<long>*) _idata;
    data.ChangeSize (hi-lo+1);
    for (long i = lo; i <= hi; i++)
        data[i-lo] = i;
}


CL_String CL_IntegerSet::AsString() const
{
    if (!_idata)
        return  "{}";
    CL_String s ("{");
    long n = Size();
    for (long i = 0; i < n; i++) {
        s += CL_String (ItemWithRank (i));
        if (i < n-1)
            s += ", ";
    }
    s += "}";
    return s;
}

long CL_IntegerSet::SmallestNonMemberAbove (long p) const
{
    long n = Size();
    if (n <= 0 || !_idata)
        return p;
    long pos = 0;
    bool b = _FindPos (++p, pos);
    if (!b)
        return p;
    SetImplSeq<long>& data = * (SetImplSeq<long>*)_idata;
    for (long i = pos; i < n; i++, p++)
        if (CL_Basics<long>::Compare ((long) data(i), p) != 0)
            break;
    return p;
}


CL_Set<long>& CL_IntegerSet::operator= (const CL_Set<long>& o)
{
    CL_Set<long>::operator= (o);
    return *this;
}


void CL_IntegerSet::operator= (const CL_Object& o)
{
    if (o.IsA (*this))
        CL_Set<long>::operator= (o);
}


        


