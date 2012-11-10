



#ifndef _iterator_h_ /* Sat Nov 12 14:32:19 1994 */
#define _iterator_h_



// {\tt CL_Iterator} is an abstract class providing the basic interface for
// all YACL iterators. It is a class template with template parameter {\tt
// T}, and its {\tt Next} method returns a reference to an object of type
// {\tt T}.


#ifdef __GNUC__
#pragma implementation
#endif

#include "base/object.h"


template <class T>
class YACL_BASE CL_Iterator: public CL_Object {

public:
    ~CL_Iterator() {};
    
    virtual void      Reset () = 0;
    // Reset the iterator to the beginning. (Pure virtual.)

    virtual bool      More  () = 0;
    // Return TRUE if there are more elements to be returned. (Pure
    // virtual.)

    virtual const T&  Next  () = 0;
    // Return the next element.  (Pure virtual.)

    
};

#endif /* _iterator_h_ */
