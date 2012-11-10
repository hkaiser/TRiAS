

#ifndef _long_h_ /* Mon Aug  8 14:03:07 1994 */
#define _long_h_





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


#if !defined(__CFRONT__) || defined(__CFRONT_LONG_IMPL__)

// Template specializations for the type-specific "basic operations" on
// the long type.

#include "base/stream.h"
#include "base/string.h"


#if defined(__BORLANDC__) && (__BCPLUSPLUS__ >= 0x0340)
class YACL_BASE CL_Basics<long> {
public:
#if defined(YACL_DEFINE_NULL)
    inline static long&         NullValueRef ();
#endif
    inline static long          NullValue ();
    inline static short         Compare (const long& o1, const long& o2);
    inline static CL_String     PrintableForm (const long& o);
    inline static bool          Read  (long& o, const CL_Stream& s);
    inline static bool          Write (const long& o, CL_Stream& s);
    inline static long          StoreWidth (const long& p);
    inline static long&         Deref (const CL_VoidPtr& p);
    inline static void          Destroy (CL_VoidPtr p);
    inline static CL_VoidPtr    MakeCopy (const long& o);
    inline static void          DoDestroy (const long& o);
    inline static CL_VoidPtr    MakePointer (const long& o);
};
#endif



#if defined(YACL_DEFINE_NULL)
#if !defined(__CFRONT__)
inline
#endif
long&       CL_Basics<long>::NullValueRef ()
{
    _Null = 0;
    return _Null;
}
#endif



#if !defined(__CFRONT__)
inline
#endif
long  CL_Basics<long>::NullValue ()
{
    return 0;
}


#if !defined(__CFRONT__)
inline
#endif
short      CL_Basics<long>::Compare (const long& o1, const long&
                                            o2)
{
    return o1 < o2 ? -1 : (o1 == o2 ? 0 : 1);
}


#if !defined(__CFRONT__)
inline
#endif
CL_String  CL_Basics<long>::PrintableForm (const long& o)
{
    return CL_String (o);
}


#if !defined(__CFRONT__)
inline
#endif
bool       CL_Basics<long>::Read  (long& o, const CL_Stream& s)
{
    return s.Read (o);
}


#if !defined(__CFRONT__)
inline
#endif
bool       CL_Basics<long>::Write (const long& o, CL_Stream& s)
{
    return s.Write (o);
}


#if !defined(__CFRONT__)
inline
#endif
long       CL_Basics<long>::StoreWidth (const long&)
{
    return sizeof (long);
}


#if !defined(__CFRONT__)
inline
#endif
void       CL_Basics<long>::Destroy (CL_VoidPtr)
{
    // Do nothing
}


#if !defined(__CFRONT__)
inline
#endif
long& CL_Basics<long>::Deref (const CL_VoidPtr& p)
{
    return (long&) p;
}



#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr    CL_Basics<long>::MakeCopy (const long& o)
{
    register CL_VoidPtr p = (const CL_VoidPtr&) o;
    return p;
}



#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr    CL_Basics<long>::MakePointer (const long& o)
{
    register CL_VoidPtr p = (const CL_VoidPtr&) o;
    return p;
}


#if !defined(__CFRONT__)
inline
#endif
void          CL_Basics<long>::DoDestroy (const long&)
{
}




#if defined(__IBMCPP__)
#pragma define(CL_Basics<long>)
#endif


#endif /* CFRONT stuff */

#endif /* _long_h_ */
