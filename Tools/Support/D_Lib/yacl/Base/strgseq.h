

#ifndef _strgseq_h_ /* Fri May 20 19:15:07 1994 */
#define _strgseq_h_







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





// The StringSequence is a Sequence of Strings. 

#ifdef __GNUC__
#pragma interface
#endif

#include "base/sequence.h"
#include "base/string.h"

class YACL_BASE CL_StringSequence: public CL_Sequence<CL_String> {

public:
    //
    // ------------------------ Creation and destruction --------------
    //
    CL_StringSequence (long n = 0);
    // Construct a StringSequence with $n$ cells.

    CL_StringSequence (const CL_String data[], long count);
    // Create this StringSequence from a C-style array of Strings. The
    // resulting sequence has {\tt count} cells initialized to the values in
    // {\tt data}, which is assumed to contain {\tt count} strings.
    
    CL_StringSequence (const char* data[], long count = -1);
    // Create this Sequence from a C-style array of character  pointers. The
    // resulting Sequence has {\tt count} cells initialized to the values in
    // {\tt data}, which is assumed to contain {\tt count} strings. If {\tt
    // count} is $-1$, then the last cell of the {\tt data} array is assumed to
    // contain  a NULL pointer. This allows initialization in the following
    // style:
    // 
    // \begin{verbatim}
    //        const char* data[] = {"One", "Two", "Three", 0};
    //        CL_StringSequence seq (data);
    // \end{verbatim}
    //
    // \noindent
    // So you don't have to count the number of strings in the initializing
    // array.
    
    CL_StringSequence (const CL_Sequence<CL_String>& s);
    // Copy constructor.

    virtual CL_Sequence<CL_String>& operator= (const
                                               CL_Sequence<CL_String>&);

    void operator= (const CL_Object&);

    const char* ClassName () const {return "CL_StringSequence";};
    
    CL_ClassId ClassId () const { return _CL_StringSequence_CLASSID; };
    
};



#endif /* _strgseq_h_ */
