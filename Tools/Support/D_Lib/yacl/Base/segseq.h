

#ifndef _segseq_h_ /* Fri Apr 26 22:48:24 1996 */
#define _segseq_h_



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


// CL_SegmentedSequence is a private class intended only for use by YACL
// internals.


#if defined(__GNUC__)
#pragma interface
#endif

#include "base/defs.h"

struct CL_SegDesc {
    short _cap;  // Number of cells
    long* _data; // The cells themselves
};


class YACL_BASE CL_SegmentedSequence {

public:
    CL_SegmentedSequence (long initial_cap = 8);
    
    ~CL_SegmentedSequence ();

    bool ResizeTo    (long new_cap);
    // Guarantee that there are at least new_cap cells in the sequence.

    CL_VoidPtr& operator[] (long index);


protected:
    CL_SegDesc*      _segs;
    short            _numSegs;
    long             _totalCap;
};



inline CL_VoidPtr& CL_SegmentedSequence::operator[] (long index)
{
    return (CL_VoidPtr&) (_segs[index >> 13]._data[index & 0x1fff]);
}


#endif /* _segseq_h_ */
