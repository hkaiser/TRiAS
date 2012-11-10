

#ifndef _clntset_h_ /* Tue Mar  8 15:35:57 1994 */
#define _clntset_h_





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




// A ClientSet is a set of bindings and corresponding parameters,
// used for maintaining client sets for notification. This class uses copy
// semantics; when an AbstractBinding is added to it, it makes a copy using
// the {\tt Clone} method. It destroys all its copies when it is destroyed.
// The two most useful methods it provides are {\tt NotifyAll} and {\tt
// Permits}.

#ifdef __GNUC__
#pragma interface
#endif


#include "base/objset.h"
#include "base/binding.h"

    
class YACL_BASE CL_ClientSet: public CL_Object {

public:
    ~CL_ClientSet ();

    long Size () const;
    // Return the number of bindings in the set.
    
    bool Add    (const CL_AbstractBinding& binding);
    // Add {\tt binding} to this set. Return FALSE if
    // either memory allocation failed or {\tt binding} was already
    // included in the set, and TRUE otherwise. The test for inclusion is
    // done using the AbstractBinding's virtual {\tt Compare} method.

    bool Remove   (const CL_AbstractBinding& binding);
    // Remove {\tt binding} from the set.
    // Return FALSE if there was no such binding included in the set, and
    // TRUE otherwise. The test for inclusion is
    // done using the AbstractBinding's virtual {\tt Compare} method.

    bool Includes (const CL_AbstractBinding& binding) const;
    // Return whether this set includes {\tt binding}. The test for
    // inclusion is done using the AbstractBinding's virtual {\tt Compare}
    // method.


    CL_AbstractBinding* Find (const CL_AbstractBinding& binding) const;
    // Return a pointer to the binding value associated with the given
    // binding. Return NULL if no such binding.

    void MakeEmpty ();
    // Remove all the contained bindings and make this ClientSet empty.
    
    void NotifyAll (CL_Object& o) const;
    // Execute all the contained bindings, with parameter {\tt o}. Ignore
    // the return values of the executed bindings. There is no particular
    // order in which the contained bindings are executed.
    
    bool Permits (CL_Object& o) const;
    // Execute all the contained bindings, with parameter o; return TRUE if all
    // of them return TRUE, and FALSE otherwise. The notification process
    // stops as soon as one of the bindings returns FALSE, so that
    // subsequent bindings in the set are not invoked. Here, each
    // binding's return value is viewed as ``permission'' from the client to
    // perform some operation, and this method's return value is TRUE only
    // if all contained bindings permit it. There is no particular order in
    // which the contained bindings are executed.

    CL_String AsString () const;
    // Return a String representation of this Set.
    
    const char* ClassName () const {return "CL_ClientSet";};
    // Override method inherited from CL_Object.


protected:
    CL_ObjectSet _set;

};


inline long CL_ClientSet::Size() const
{
    return _set.Size();
}

#endif /* _clntset_h_ */
