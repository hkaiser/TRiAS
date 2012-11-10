

#ifndef _objset_h_ /* Wed Apr 20 11:06:03 1994 */
#define _objset_h_





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




// ObjectSet represents a set of pointers to Objects. Typically, ObjectSets
// are used for holding heterogeneous collections of objects, so that it
// cannot compare its contained objects for relative order. ObjectSet
// therefore uses linear search when looking up an item, either for
// insertion, removal or membership testing. It also overrides the set
// operators for union, intersection and difference, and the overriding
// methods use the more expensive linear-search-based algorithms.
//
// ObjectSet also provides the
// {\tt Find} operation and supports persistence.


#ifdef __GNUC__
#pragma interface
#endif


#include "base/set.h"
#include "base/stream.h"
#include "base/builder.h"

class YACL_BASE CL_ObjectSet: public CL_Set<CL_ObjectPtr> {

public:
    CL_ObjectSet (CL_ObjectBuilder* bld = NULL);
    // Constructor. The parameter {\tt bld} is a pointer to an ObjectBuilder
    // that can be used to reconstruct contained objects when an instance of
    // this ObjectSet is restored from a Stream. If the parameter
    // is NULL, no ObjectBuilder is used; instead, the Stream is asked to
    // restore the individual objects.

    CL_ObjectSet (const CL_ObjectSet&);
    // Copy constructor.

    virtual CL_ObjectPtr Find (CL_ObjectPtr p) const;
    // Determine whether the given object is in the set, and if so, return
    // a pointer to the contained object. If not, return NULL. This method
    // is useful in situations where a compound object is stored in the
    // set, where equality testing for the contained object is based only
    // on some (not all) of its components. The implementation uses linear
    // search, because we cannot use object
    // addresses for comparison between heterogeneous objects in general.
    
    void DestroyContents ();
    // Invoke the destructors of all the contained objects, and set our
    // size to zero. Note that this is not the same as the inherited
    // method {\tt MakeEmpty}, since the latter does not destroy contained
    // objects.

    CL_Set<CL_ObjectPtr> operator+ (const CL_Set<CL_ObjectPtr>& o) const;
    // Override the inherited method to do linear-search-based union.

    CL_Set<CL_ObjectPtr> operator- (const CL_Set<CL_ObjectPtr>& o) const;
    // Override the inherited method to do linear-search-based difference.

    CL_Set<CL_ObjectPtr> operator* (const CL_Set<CL_ObjectPtr>& o) const;
    // Override the inherited method to do linear-search-based intersection.

    CL_Set<CL_ObjectPtr> operator^ (const CL_Set<CL_ObjectPtr>& o) const;
    // Override the inherited method to do linear-search-based xor.


    CL_Set<CL_ObjectPtr>& operator+= (const CL_Set<CL_ObjectPtr>& o);

    CL_Set<CL_ObjectPtr>& operator-= (const CL_Set<CL_ObjectPtr>& o);

    CL_Set<CL_ObjectPtr>& operator*= (const CL_Set<CL_ObjectPtr>& o);

    virtual CL_Set<CL_ObjectPtr>& operator= (const CL_Set<CL_ObjectPtr>&);

    void operator= (const CL_Object&);

    bool ReadFrom (const CL_Stream&);
    // Override the method inherited from Object.

    bool WriteTo  (CL_Stream&) const;
    // Override the method inherited from Object.
    
    CL_ClassId ClassId() const {return _CL_ObjectSet_CLASSID;};
    
    const char* ClassName () const {return "CL_ObjectSet";};


protected:
    CL_ObjectBuilder* _bld;

    virtual bool _FindPos (const CL_ObjectPtr& o, long& pos) const;
    // Override the inherited method with code that uses linear search.
    
};


typedef CL_SetIterator<CL_ObjectPtr> CL_ObjectSetIterator;



#endif /* _objset_h_ */
