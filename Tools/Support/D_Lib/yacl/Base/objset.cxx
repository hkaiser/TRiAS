



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
template class CL_Set<CL_ObjectPtr>;
template class CL_Iterator<CL_ObjectPtr>;
template class CL_SetIterator<CL_ObjectPtr>;
template class CL_Binding0<CL_SetIterator<CL_ObjectPtr> >;
template class SetImplSeq<CL_ObjectPtr>;
#elif defined(_MSC_VER)
// The following pragma is needed to disable a warning about CL_Iterator
// methods not neing available:
#pragma warning (disable:4661)

template CL_Set<CL_ObjectPtr>;
template CL_Iterator<CL_ObjectPtr>;
template CL_SetIterator<CL_ObjectPtr>;
template CL_Binding0<CL_SetIterator<CL_ObjectPtr> >;
template SetImplSeq<CL_ObjectPtr>;
#endif


#include "base/objset.h"
#include "base/objseq.h"
#include "base/objptr.h"


#if defined(__IBMCPP__)
#pragma define(CL_Set<CL_ObjectPtr>)
#pragma define(CL_SetIterator<CL_ObjectPtr>)
#pragma define(CL_Basics<CL_ObjectPtr>)
#elif defined(__SGI_DELTA_CC__)
#pragma instantiate CL_Set<CL_ObjectPtr>
#pragma instantiate CL_SetIterator<CL_ObjectPtr>
#pragma instantiate CL_Basics<CL_ObjectPtr>
#endif





CL_ObjectSet::CL_ObjectSet (CL_ObjectBuilder* b)
: CL_Set<CL_ObjectPtr> (new CL_ObjectSequence), _bld (b)
{
}


CL_ObjectSet::CL_ObjectSet (const CL_ObjectSet& s)
: CL_Set<CL_ObjectPtr> (s), _bld (s._bld)
{
}



bool CL_ObjectSet::_FindPos (const CL_ObjectPtr& p, long& index) const
{
    if (!_idata)
        return FALSE;
    SetImplSeq<CL_ObjectPtr>&  data = *(SetImplSeq<CL_ObjectPtr>*) _idata;
    long n = data.Size();
    short result = 1;
    long i;
    for (i = 0; i < n; i++) {
        result = CL_Basics<CL_ObjectPtr>::Compare
            (CL_Basics<CL_ObjectPtr>::Deref (data (i)),
             CL_Basics<CL_ObjectPtr>::Deref (p));
        if (result == 0)
            break;
    }
    if (result == 0) {
        index = i;
        return TRUE;
    }
    index = i-1;
    return FALSE;
}


CL_ObjectPtr CL_ObjectSet::Find (CL_ObjectPtr p) const
{
    if (!_idata)
        return NULL;
    long l;
    if (_FindPos (p, l)) {
        SetImplSeq<CL_ObjectPtr>& data = * (SetImplSeq<CL_ObjectPtr>*) _idata;
        return (CL_ObjectPtr) data(l);
    }
    return NULL;
}



CL_Set<CL_ObjectPtr> CL_ObjectSet::operator+ (const CL_Set<CL_ObjectPtr>& s)
    const
{
    CL_Set<CL_ObjectPtr> t (*this);
    t += s;
    return t;
}

CL_Set<CL_ObjectPtr>& CL_ObjectSet::operator+= (const CL_Set<CL_ObjectPtr>& s)
{
    if (!_idata || !PrepareToChange() || this == &s)
        return *this;
    long pos = 0;
    SetImplSeq<CL_ObjectPtr>& seq = *(SetImplSeq<CL_ObjectPtr> *)_idata;
    CL_ObjectSetIterator itr (s);
    while (itr.More()) {
        CL_ObjectPtr p = itr.Next();
        if (!_FindPos (p, pos))
            seq.Insert (p, pos);
    }
    Notify();
    return *this;
}



CL_Set<CL_ObjectPtr>& CL_ObjectSet::operator-= (const CL_Set<CL_ObjectPtr>& s)
{
    if (!_idata || !PrepareToChange())
        return *this;
    if (this == &s) {
        MakeEmpty();
        Notify();
        return *this;
    }
    long pos = 0;
    SetImplSeq<CL_ObjectPtr>& seq = *(SetImplSeq<CL_ObjectPtr> *)_idata;
    CL_ObjectSetIterator itr (s);
    while (itr.More()) {
        CL_ObjectPtr p = itr.Next();
        if (_FindPos (p, pos))
            seq.Remove (pos);
    }
    Notify();
    return *this;
}


CL_Set<CL_ObjectPtr> CL_ObjectSet::operator- (const CL_Set<CL_ObjectPtr>& s)
    const
{
    CL_ObjectSet result = *this;
    result -= s;
    return result;
}


CL_Set<CL_ObjectPtr>& CL_ObjectSet::operator*= (const CL_Set<CL_ObjectPtr>& s)
{
    if (!_idata || !PrepareToChange() || this == &s)
        return *this;
    SetImplSeq<CL_ObjectPtr>& seq = *(SetImplSeq<CL_ObjectPtr> *)_idata;
    for (long i = Size()-1; i >= 0; i--)
        if (!s.Includes ((CL_ObjectPtr) seq(i)))
            seq.Remove (i);
    Notify();
    return *this;
}


CL_Set<CL_ObjectPtr> CL_ObjectSet::operator* (const CL_Set<CL_ObjectPtr>& s)
    const
{
    CL_ObjectSet result = *this;
    result -= s;
    return result;
}



CL_Set<CL_ObjectPtr> CL_ObjectSet::operator^ (const CL_Set<CL_ObjectPtr>& s)
    const
{
    return (*this) + s - ((*this) * s);
}



void CL_ObjectSet::DestroyContents ()
{
    if (_idata) {
        SetImplSeq<CL_ObjectPtr>& seq = *(SetImplSeq<CL_ObjectPtr> *)_idata;
        for (long i = seq.Size() - 1; i >= 0; i--)
            delete (CL_ObjectPtr) seq(i);
        seq.ChangeSize (0);
    }
}



bool CL_ObjectSet::ReadFrom (const CL_Stream& s)
{
    CL_ClassId id;
    register bool b = s.Read (id) && id == ClassId();
    if (!b || !_idata)
        return FALSE;
    SetImplSeq<CL_ObjectPtr>& seq = *(SetImplSeq<CL_ObjectPtr> *)_idata;
    long size = 0;
    if (!s.Read (size))
        return FALSE;
    seq.ChangeSize (size);
    for (long i = 0; i < size; i++) {
        if (_bld)
            seq(i) = _bld->BuildFrom (s);
        else
            s.Read ((CL_ObjectPtr&) seq(i));
    }
    seq.Sort();
    return TRUE;
}

bool CL_ObjectSet::WriteTo  (CL_Stream& s) const
{
    if (!_idata || !s.Write (ClassId()))
        return FALSE;
    SetImplSeq<CL_ObjectPtr>& seq = *(SetImplSeq<CL_ObjectPtr> *)_idata;
    long size = seq.Size();
    for (long i = 0; i < size; i++)
        s.Write ((CL_ObjectPtr) seq(i));
    return TRUE;
}




CL_Set<CL_ObjectPtr>& CL_ObjectSet::operator= (const CL_Set<CL_ObjectPtr>& o)
{
    CL_Set<CL_ObjectPtr>::operator= (o);
    return *this;
}


void CL_ObjectSet::operator= (const CL_Object& o)
{
    if (o.IsA (*this))
        CL_Set<CL_ObjectPtr>::operator= (o);
}

