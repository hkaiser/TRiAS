

#ifndef _cmparatr_h_ /* Wed Aug  3 16:17:51 1994 */
#define _cmparatr_h_




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

#ifdef __IBMCPP__
#pragma implementation("cmparatr.cxx")
#endif

#include "base/basicops.h"

// An AbstractComparator is a function object. It encapsulates an algorithm
// for comparing two objects
// specified by void pointers. The comparison is done using the operator(),
// and returns a {\tt short} value that is $-1$, 0 or $+1$ according to whether
// the first operand is less than, equal to or greater than the second.


#if defined(__CFRONT__)
#define inline
#endif

class YACL_BASE CL_AbstractComparator {

public:
    virtual ~CL_AbstractComparator () {};
    
    virtual short operator() (CL_VoidPtr p1, CL_VoidPtr p2) const = 0;
    // [Pure virtual]
    // Compare  the two objects pointed to by the parameters, and return
    // $-1$, 0 or $+1$ according to whether the first object is less than,
    // equal to or greater than the second.
    
};


// A Comparator is a class template derived from AbstractComparator and is 
// used for comparing two objects of the template parameter type.

template <class Base>
class YACL_BASE CL_Comparator: public CL_AbstractComparator {

public:
    ~CL_Comparator () {};
    
    inline short operator() (CL_VoidPtr p1, CL_VoidPtr p2) const;
    // Overrides the inherited operator. The implementation uses the basic
    // operation {\tt Compare} (see {\tt basicops.h}) of the type {\tt
    // Base}.

};


#if defined(__CFRONT__)
#undef inline
#endif



#endif /* _cmparatr_h_ */

