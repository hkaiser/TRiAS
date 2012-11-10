

#ifndef _objseq_h_ /* Wed Apr 20 22:52:00 1994 */
#define _objseq_h_





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




// The ObjectSequence is a Sequence of pointers to Objects. It is a
// derived class, rather than a typedef, so that
// we can support storage and retrieval of object sequences.



#ifdef __GNUC__
#pragma interface
#endif


#include "base/sequence.h"
#include "base/builder.h"

class YACL_BASE CL_AbstractComparator;

class YACL_BASE CL_ObjectSequence: public CL_Sequence<CL_ObjectPtr> {

public:

    CL_ObjectSequence (long initial_size = 0, CL_ObjectBuilder* bld = NULL);
    // Construct a new ObjectSequence. The last parameter, if non-null,
    // will be used whenever this Sequence is to be restored from a passive
    // form.

    CL_ObjectSequence (const CL_ObjectPtr data[], long count,
                       CL_ObjectBuilder* bld = NULL);
    // Create this object from a C-style array.  The last parameter, if
    // non-null, will be used whenever this Sequence is to be restored from
    // a passive form.
    
    CL_ObjectSequence (const CL_ObjectSequence& s);
    // Copy constructor.

    ~CL_ObjectSequence ();
    // Destructor.


    void Sort (const CL_AbstractComparator& cmp);
    // Sort this ObjectSequence using the ordering relation stipulated by
    // the given AbstractComparator.

    bool Sort () {return Sort (0, Size());};
    
    bool Sort (long i, long n)
        {return CL_Sequence<CL_ObjectPtr>::Sort (i,n);};
    // Override the inherited method to avoid the "hides virtual" warning.
    
    void DestroyContents ();
    // Invoke the destructors of all the contained objects, and set our
    // size to zero. Note that this is not the same as the inherited
    // method {\tt MakeEmpty}, since the latter does not destroy contained
    // objects.

    virtual CL_Sequence<CL_ObjectPtr>& operator= (const
                                                  CL_Sequence<CL_ObjectPtr>&);

    void operator= (const CL_Object&);

    CL_ClassId ClassId() const {return _CL_ObjectSequence_CLASSID;};
    
    const char* ClassName () const {return "CL_ObjectSequence";};


protected:
    CL_ObjectBuilder*      _bld;

    CL_AbstractComparator* _cmp;
    
    bool       _ReadElement  (const CL_Stream& s, long i);
    
    bool       _WriteElement (CL_Stream& s, long i) const;

    short      _Compare (const CL_ObjectPtr& p1, const CL_ObjectPtr& p2) const;
    
    
};


#endif /* _objseq_h_ */
