

#ifndef _strgset_h_ /* Wed Jul 27 16:54:28 1994 */
#define _strgset_h_



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
#pragma interface
#endif

#include "base/set.h"
#include "base/string.h"

// StringSet is a Set of Strings. It is derived from {\tt CL_Set
// <CL_String>} and adds the {\tt StringsWithPrefix} method for obtaining
// subsets of Strings with a given prefix.

class YACL_BASE CL_StringSet: public CL_Set<CL_String> {

public:
    CL_StringSet () : CL_Set<CL_String> () {};
    // Default constructor: construct an empty StringSet.
    
    CL_StringSet (const char* data[]);
    // Convenience constructor: build a StringSet from the given array of
    // pointers. The last cell in the array should be NULL. For example, you
    // could write:
    // \par\begin{verbatim}
    //       char* data[] = {"One", "Two", "Three", 0};
    //       CL_StringSet mySet (data);
    // \end{verbatim}
    // \par
    
    CL_StringSet StringsWithPrefix (const CL_String& s) const;
    // Return a set containing all those strings in this set that have
    // {\tt s} as prefix.
    
    //
    // ------------------------- Basic methods --------------------
    //
    virtual CL_Set<CL_String>& operator= (const CL_Set<CL_String>&);

    void operator= (const CL_Object&);

    CL_Object* Clone () const
        {return new CL_Set<CL_String> (*this);};
    // Overrides the method inherited from {\tt CL_Object}. Returns a
    // copy of this Set. The caller of this method is responsible for
    // destroying the returned Set.
    
    const char* ClassName() const {return "CL_StringSet";};
    
    CL_ClassId ClassId() const
        { return _CL_StringSet_CLASSID;};



    // -------------------- End public protocol ---------------------------

};


typedef CL_SetIterator<CL_String>  CL_StringSetIterator;

#endif /* _strgset_h_ */
