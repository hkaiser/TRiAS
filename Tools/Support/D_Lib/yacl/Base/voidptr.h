

#ifndef _voidptr_h_ /* Mon Aug  8 14:02:32 1994 */
#define _voidptr_h_





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


#if !defined(__CFRONT__) || defined(__CFRONT_VOIDPTR_IMPL__)

// Template specializations for the type-specific "basic operations" on
// the CL_VoidPtr type.

#include "base/string.h"

#if defined(__BORLANDC__) && (__BCPLUSPLUS__ >= 0x0340)
class YACL_BASE CL_Basics<CL_VoidPtr> {
public:

#if defined(YACL_DEFINE_NULL)
    inline static CL_VoidPtr&   NullValueRef ();
#endif
    inline static CL_VoidPtr    NullValue ();
    inline static short         Compare (const CL_VoidPtr& o1,
                                         const CL_VoidPtr& o2);
    inline static CL_String     PrintableForm (const CL_VoidPtr& o);
    inline static bool          Read  (CL_VoidPtr& o, const CL_Stream& s);
    inline static bool          Write (const CL_VoidPtr& o, CL_Stream& s);
    inline static long          StoreWidth (const CL_VoidPtr& p);
    inline static CL_VoidPtr&         Deref (const CL_VoidPtr& p);
    inline static void          Destroy (CL_VoidPtr p);
    inline static CL_VoidPtr    MakeCopy (const CL_VoidPtr& o);
    inline static void          DoDestroy (const CL_VoidPtr& o);
    inline static CL_VoidPtr    MakePointer (const CL_VoidPtr& o);
};
#endif



#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr       CL_Basics<CL_VoidPtr>::NullValue ()
{
    return (CL_VoidPtr) 0;
}


#if defined(YACL_DEFINE_NULL)
#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr&       CL_Basics<CL_VoidPtr>::NullValueRef ()
{
    _Null = 0;
    return _Null;
}
#endif




#if !defined(__CFRONT__)
inline
#endif
short      CL_Basics<CL_VoidPtr>::Compare (const CL_VoidPtr& o1,
                                                  const CL_VoidPtr& o2)
{
#if defined(__MS_WINDOWS__) || defined(__DOS__)
    void huge* p1 = o1, *p2 = o2;
    return (p1 < p2 ? -1 : (p1 == p2 ? 0 : 1));
#else
    return o1 < o2 ? -1 : (o1 == o2 ? 0 : 1);
#endif
}


#if !defined(__CFRONT__)
inline
#endif
CL_String  CL_Basics<CL_VoidPtr>::PrintableForm (const CL_VoidPtr& o)
{
    CL_String s;
    s.AssignWithFormat ("%lx", o);
    return s;
}


#if !defined(__CFRONT__)
inline
#endif
bool       CL_Basics<CL_VoidPtr>::Read (CL_VoidPtr&, const CL_Stream&)
{
    return FALSE; // Do nothing
}


#if !defined(__CFRONT__)
inline
#endif
bool       CL_Basics<CL_VoidPtr>::Write (const CL_VoidPtr&, CL_Stream&)
{
    return FALSE; // Do nothing
}


#if !defined(__CFRONT__)
inline
#endif
long       CL_Basics<CL_VoidPtr>::StoreWidth (const CL_VoidPtr&)
{
    return sizeof (CL_VoidPtr);
}


#if !defined(__CFRONT__)
inline
#endif
void       CL_Basics<CL_VoidPtr>::Destroy (CL_VoidPtr)
{
    // Do nothing
}



#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr& CL_Basics<CL_VoidPtr>::Deref (const CL_VoidPtr& p)
{
    return (CL_VoidPtr&) p;
}



#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr    CL_Basics<CL_VoidPtr>::MakeCopy (const CL_VoidPtr& o)
{
    return o;
}

#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr    CL_Basics<CL_VoidPtr>::MakePointer (const CL_VoidPtr& o)
{
    return o;
}


#if !defined(__CFRONT__)
inline
#endif
void          CL_Basics<CL_VoidPtr>::DoDestroy (const CL_VoidPtr&)
{
}



#if defined(__IBMCPP__)
#pragma define(CL_Basics<CL_VoidPtr>)
#endif


#endif /* CFRONT stuff */

#endif /* _voidptr_h_ */
