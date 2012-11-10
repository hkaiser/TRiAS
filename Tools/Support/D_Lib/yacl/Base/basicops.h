

#ifndef _basicops_h_ /* Sun May 22 12:44:53 1994 */
#define _basicops_h_




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



// Basics is a class template with template parameter {\tt BaseType}.
// This ``basic operations'' class provides inline static methods for primitive
// operations on data types, namely comparison, null values, object
// input/output and conversion functions for the container classes. This
// class contains only static methods and data, and is  not intended for use
// as an object. It is merely an encapsulation of the type-dependent
// operations provided for the container classes to access in a uniform
// manner.


#ifdef __GNUC__
#pragma interface
#endif


#ifdef __IBMCPP__
#pragma implementation("basicops.cxx")
#endif

#include "base/defs.h"
#include "base/string.h"
#include "base/stream.h"



//
// cfront doesn't take kindly to inline static functions for template
// classes.  So...
//
#if defined(__CFRONT__) || defined(__IBMCPP__)
#define inline
#endif


template <class BaseType>
class YACL_BASE CL_Basics {

public:

    // -------------- Null values --------------------
    
    inline static BaseType          NullValue ();
    // Return a copy of the null value of {\tt BaseType}. The default
    // implementation returns an object returned by {\tt BaseType}'s
    // parameterless  constructor.

#if defined(YACL_DEFINE_NULL)
    inline static BaseType&         NullValueRef ();
    // This is now obsolete; retained only for backward compatibility.
    //  -- MAS, Oct 11, 1996

#endif
    

    // ----------------------- Comparison ---------------------
    
    inline static short      Compare (const BaseType& o1, const BaseType& o2);
    // Return $-1$, 0 or $+1$ depending on whether {\tt o1} is less than,
    // equal to or greater than {\tt o2} in the ordering determined by the
    // type {\tt BaseType}. The default implementation assumes that  {\tt
    // BaseType} defines a {\tt Compare} method, and returns the return
    // value of {\tt o1.Compare(o2)}.

    // ----------------------- Object I/O ---------------------
    
    inline static CL_String     PrintableForm (const BaseType& o);
    // Return a String containing a printable representation of the contents
    // of {\tt o}. The default implementation assumes that {\tt
    // BaseType} defines an {\tt AsString} method, and returns its return
    // value.
    
    inline static bool          Read  (BaseType& o, const CL_Stream& s);
    // Read the contents of {\tt o} from the binary Stream {\tt s}. Return
    // TRUE on success,  FALSE on failure. The default implementation uses
    // {\tt BaseType}'s {\tt ReadFrom} method.
    
    inline static bool          Write (const BaseType& o, CL_Stream& s);
    // Write the contents of {\tt o} to the binary Stream {\tt s}. Return
    // TRUE on success,  FALSE on failure. The default implementation uses
    // {\tt BaseType}'s {\tt WriteTo} method.

    inline static long          StoreWidth (const BaseType& p);
    // Return the number of bytes used in the binary representation of {\tt
    // p}. The default implementation uses {\tt BaseType}'s {\tt
    // StorableFormWidth} method.
    
    // ----------------- Conversion to/from CL_VoidPtr --------
    
    inline static BaseType&         Deref (const CL_VoidPtr& p);
    // [Conversion: for use by containers]
    // Treat {\tt p} as a pointer to an object of type {\tt BaseType},
    // dereference it, and return a reference to the object.
    
    inline static void          Destroy (CL_VoidPtr p);
    // [For use by containers] Treat {\tt p} as a pointer to an object of
    // type {\tt BaseType} and destroy it.

    inline static CL_VoidPtr    MakeCopy (const BaseType& o);
    // [For use by containers] Make a copy of {\tt o} on the heap and return
    // a pointer to the copy as a {\tt CL_VoidPtr}.

    inline static void          DoDestroy (const BaseType& o);
    // This function is provided as a convenience for container
    // implementations. Its implementation for most types does nothing. The
    // only exception is for the case where {\tt BaseType} is {\tt
    // CL_ObjectPtr}; in this case, it destroys the object pointed to by
    // {\tt o}.
    
    inline static CL_VoidPtr    MakePointer (const BaseType& o);
    // [For use by containers]
    // Return a pointer to the object {\tt o}. If {\tt BaseType} is a class
    // type, this function returns the address of {\tt o}. If {\tt BaseType} is
    // a pointer type, it returns the value of {\tt o}.


#if defined(YACL_DEFINE_NULL)
protected:
    static BaseType _Null;
    // This is now obsolete. The containers do not use this variable, in
    // order to support multi-threading. -- MAS, Oct 11, 1996

#endif

};


#if defined(__CFRONT__) || defined(__IBMCPP__)
#undef inline
#endif


#endif /* _basicops_h_ */
