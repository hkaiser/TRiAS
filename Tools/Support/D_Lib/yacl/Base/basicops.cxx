



#ifndef _basicops_cxx_ /* Wed Dec 20 15:01:30 1995 */
#define _basicops_cxx_

#if defined(__CFRONT__) && !defined(__CFRONT_BASICOPS_IMPL__)
#include "base/basicops.h"
#else

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



#include "base/basicops.h"
#include "base/string.h"
#include "base/stream.h"


//
// cfront doesn't like inline static functions for template classes.
// Looks like gcc greater than 2.6 doesn't either, but for sake of
// minimal change, I'll leave it like it is -- Jody Hagins
//
#if defined(__CFRONT__)
#define inline
#endif




// Warning: Place the template specialization functions textually BEFORE the
// general template-based definitions (e.g., CL_Basics<long>::Compare is
// defined BEFORE template <class Base> CL_Basics<Base>::Compare), otherwise
// Borland C++ complains. 
//
// Include the template specializations for these static methods:

#if defined(__BORLANDC__)
#    if (__BCPLUSPLUS__ <= 0x0330)
#    include "base/long.h"
#    include "base/voidptr.h"
#    include "base/objptr.h"
#    endif
#else
#include "base/long.h"
#include "base/voidptr.h"
#include "base/objptr.h"
#endif

// The real template methods:

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
BaseType       CL_Basics<BaseType>::NullValue ()
{
    return BaseType ();
}

    

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
short CL_Basics<BaseType>::Compare (const BaseType& o1,
                                           const BaseType& o2)
{
    return o1.Compare (o2);
}
    

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
CL_String      CL_Basics<BaseType>::PrintableForm (const BaseType& o) 
{
    return o.AsString ();
}

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
bool           CL_Basics<BaseType>::Read (BaseType& o,
                                                 const CL_Stream& s) 
{
    return o.ReadFrom (s);
}

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
bool           CL_Basics<BaseType>::Write (const BaseType& o,
                                                  CL_Stream& s) 
{
    return o.WriteTo (s);
}

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
long           CL_Basics<BaseType>::StoreWidth (const BaseType& o) 
{
    return o.StorableFormWidth ();
}

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
void       CL_Basics<BaseType>::Destroy (CL_VoidPtr p)
{
    if (p) delete (BaseType*) p;
}



template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
CL_VoidPtr    CL_Basics<BaseType>::MakeCopy (const BaseType& o) 
{
    return  (CL_VoidPtr) new BaseType (o);
}


template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
CL_VoidPtr    CL_Basics<BaseType>::MakePointer (const BaseType& o) 
{
    return  (CL_VoidPtr) &o;
}

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
BaseType&      CL_Basics<BaseType>::Deref (const CL_VoidPtr& p)
{
    return *(BaseType*&) p;
}

template <class BaseType>
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
inline
#endif
void       CL_Basics<BaseType>::DoDestroy (const BaseType&)
{
}



#if defined(__CFRONT__)
#undef inline
#endif


#endif /* __CFRONT__  && !__CFRONT_BASICOPS_IMPL__ */



#if defined(__BORLANDC__) && (__BCPLUSPLUS__ >= 0x0340)
#include "base/long.h"
#include "base/voidptr.h"
#include "base/objptr.h"
#endif

#endif /* _basicops_cxx_ */
