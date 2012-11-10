

#ifndef _intset_h_ /* Thu Mar 31 09:23:19 1994 */
#define _intset_h_





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




// CL_IntegerSet is an extension of {\tt CL_Set<long>} with an additional
// methods {\tt AsString} and {\tt SmallestNonMember}. The
// CL_IntegerSetIterator class  provides iteration over this Set.


#ifdef __GNUC__
#pragma interface
#endif

#include "base/set.h"

class YACL_BASE CL_BitSet;

class YACL_BASE CL_IntegerSet: public CL_Set<long> {

public:
    CL_IntegerSet () {};
    // Default constructor: build an empty set.

    CL_IntegerSet (long low, long hi);
    // Build an integer set with containing all the numbers in the range
    // {\tt low} through {\tt hi}. If ${\tt low} > {\tt hi}$, the empty set
    // is built. 
    
    CL_IntegerSet (const CL_Set<long>& s) : CL_Set<long> (s) {};
    // Copy constructor.

    virtual long SmallestNonMemberAbove (long n) const;
    // Return the smallest element that exceeds $n$ and is not in the set.
    // Return $n$ if there is no such element.

    long SmallestNonMember () const {return SmallestNonMemberAbove (-1);};
    // Return the smallest non-negative element that is {\it not\/} in the
    // set. Return $-1$ if the set is empty.

    CL_String AsString () const;
    // Returns a string containing a representation of the set, in the
    // form \verb|{1,3,6}|.

    //
    // ------------------------- Basic methods --------------------
    //

    virtual CL_Set<long>& operator= (const CL_Set<long>&);

    void operator= (const CL_Object&);

    CL_Object* Clone () const
        {return new CL_IntegerSet (*this);};
    
    const char* ClassName() const
        {return "CL_IntegerSet";};
    
};



typedef CL_SetIterator<long> CL_IntegerSetIterator;

#endif /* _intset_h_ */
