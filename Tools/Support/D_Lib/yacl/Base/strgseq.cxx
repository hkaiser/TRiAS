



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
#include "base/basicops.cxx"
#include "base/strgseq.h"


// Instantiate the template:

#if defined(__GNUC__) && __GNUC_MINOR__ >= 6

template class CL_Sequence<CL_String>;

#elif defined(_MSC_VER)

template CL_Sequence<CL_String>;

#elif defined(__IBMCPP__)

#pragma define(CL_Sequence<CL_String>)
#pragma define(CL_Basics<CL_String>)

#elif defined(__SGI_DELTA_CC__)

#pragma instantiate CL_Sequence<CL_String>
#pragma instantiate CL_Basics<CL_String>

#endif


               
typedef CL_Sequence<CL_String> stringseq; // Instantiate the template



CL_StringSequence::CL_StringSequence (long initial_size)
: CL_Sequence<CL_String> (initial_size)
{
}

CL_StringSequence::CL_StringSequence (const CL_String data[], long count)
: CL_Sequence<CL_String> (data, count)
{
}


CL_StringSequence::CL_StringSequence (const char* data[], long count)
{
    long i = 0;
    if (count < 0) {
        for (; data[i] != NULL; i++);
        count = i;
    }
    ChangeSize (count);
    for (i = 0; i < count; i++)
        (*this)[i] = data[i];
}


CL_StringSequence::CL_StringSequence (const CL_Sequence<CL_String>& s)
: CL_Sequence<CL_String> (s)
{
}



CL_Sequence<CL_String>& CL_StringSequence::operator=
     (const CL_Sequence<CL_String>& o)
{
    CL_Sequence<CL_String>::operator= (o);
    return *this;
}


void CL_StringSequence::operator= (const CL_Object& o)
{
    if (o.IsA (*this))
        operator= ((const CL_Sequence<CL_String>&) o);
}
