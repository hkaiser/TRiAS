



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


#include "base/seqimp.cxx"


#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
template class CL_Sequence<long>;
template class CL_Basics<long>;
#endif

#if defined(_MSC_VER)
template CL_Sequence<long>;
#endif

#include "base/long.h"
#include "base/intseq.h"



#if defined(__IBMCPP__)
#pragma define(CL_Sequence<long>)
#pragma define(CL_Basics<long>)

#elif defined(__SGI_DELTA_CC__)
#pragma instantiate CL_Sequence<long>
#pragma instantiate CL_Basics<long>
#endif




CL_IntegerSequence::CL_IntegerSequence (long initial_size)
: CL_Sequence<long> (initial_size)
{
}


CL_IntegerSequence::CL_IntegerSequence (long data[], long count)
{
    ChangeSize (count);
    for (register long i = 0; i < count; i++)
        (*this)(i) = data[i];
}


CL_IntegerSequence::CL_IntegerSequence (const CL_Sequence<long>& s)
: CL_Sequence<long> (s)
{
}


CL_Sequence<long>& CL_IntegerSequence::operator= (const CL_Sequence<long>& o)
{
    CL_Sequence<long>::operator= (o);
    return *this;
}


void CL_IntegerSequence::operator= (const CL_Object& o)
{
    if (o.IsA (*this))
        operator= ((const CL_Sequence<long>&) o);
}



