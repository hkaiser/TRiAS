

#ifndef _intseq_h_ /* Tue Nov 23 09:38:24 1993 */
#define _intseq_h_





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


// The IntegerSequence is a Sequence whose cells are {\tt long} values.

#ifdef __GNUC__
#pragma interface
#endif


#include "base/sequence.h"

class YACL_BASE CL_IntegerSequence: public CL_Sequence<long>  {

public:
    CL_IntegerSequence (long initial_size = 0);
    // Make an IntegerSequence of size 0.

    CL_IntegerSequence (long data[], long n);
    // Create this IntegerSequence from a C-style array {\tt data} containing
    // {\tt n} values.
    
    CL_IntegerSequence (const CL_Sequence<long>& s);
    // Copy constructor.

    virtual CL_Sequence<long>& operator= (const CL_Sequence<long>&);

    void operator= (const CL_Object&);

    const char* ClassName () const {return "CL_IntegerSequence";};
    // Return the string ``{\tt CL_IntegerSequence}.''

    CL_ClassId ClassId () const { return _CL_IntegerSequence_CLASSID; };

    CL_Object* Clone () const {return new CL_IntegerSequence (*this);};
    
};




#endif /* _intseq_h_ */
