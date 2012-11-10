


#ifndef _cmparatr_cxx_ /* Wed Jan 24 20:55:27 1996 */
#define _cmparatr_cxx_



/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1996. You are free
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

#include "base/cmparatr.h"


#if !defined(__CFRONT__) || defined(__CFRONT_CMPARATR_IMPL__)

#include "base/basicops.cxx"

// BC++ 3.1 gives a strange "argument not used" warning here --
// looks like a compiler bug. 
// That's the reason for the next two pragmas.

#ifdef __BORLANDC__
#pragma warn -par
#pragma warn -aus
#endif

template <class Base>
#if !defined(__CFRONT__)
inline
#endif
short CL_Comparator<Base>::operator() (CL_VoidPtr p1, CL_VoidPtr p2)
    const
{
    if (p1 && p2) {
        register const Base& r1 = CL_Basics<Base>::Deref (p1);
        register const Base& r2 = CL_Basics<Base>::Deref (p2);
        return  CL_Basics<Base>::Compare (r1, r2);
    }
#if defined(__MS_WINDOWS__) || defined(__DOS__)
    void huge* o1 = p1, *o2 = p2;
    return (o1 < o2 ? -1 : (o1 == o2 ? 0 : 1));
#else
    return p1 < p2 ? -1 : (p1 == p2 ? 0 : 1);
#endif
}

// And if we undo the pragmas, the warnings are still emitted!! So we have
// to leave them out, so some legitimate warnings might not be emitted.
// Too bad.
//
// #ifdef __BORLANDC__
// #pragma warn .par
// #pragma warn .aus
// #endif

#endif /* cfront-specific */


#endif /* _cmparatr_cxx_ */
