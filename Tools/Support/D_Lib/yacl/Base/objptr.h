

#ifndef _objptr_h_ /* Mon Aug  8 14:03:31 1994 */
#define _objptr_h_


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





// Template specializations for the type-specific "basic operations" on
// the CL_ObjectPtr type.

#if !defined(__CFRONT__) || defined(__CFRONT_OBJPTR_IMPL__)


#include "base/stream.h"
#include "base/string.h"



#if defined(__BORLANDC__) && (__BCPLUSPLUS__ >= 0x0340)
class YACL_BASE CL_Basics<CL_ObjectPtr> {
public:
#if defined(YACL_DEFINE_NULL)
    inline static CL_ObjectPtr& NullValueRef ();
#endif
    inline static CL_ObjectPtr  NullValue ();
    inline static short         Compare (const CL_ObjectPtr& o1,
                                         const CL_ObjectPtr& o2);
    inline static CL_String     PrintableForm (const CL_ObjectPtr& o);
    inline static bool          Read  (CL_ObjectPtr& o, const CL_Stream& s);
    inline static bool          Write (const CL_ObjectPtr& o, CL_Stream& s);
    inline static long          StoreWidth (const CL_ObjectPtr& p);
    inline static CL_ObjectPtr& Deref (const CL_VoidPtr& p);
    inline static void          Destroy (CL_VoidPtr p);
    inline static CL_VoidPtr    MakeCopy (const CL_ObjectPtr& o);
    inline static void          DoDestroy (const CL_ObjectPtr& o);
    inline static CL_VoidPtr    MakePointer (const CL_ObjectPtr& o);
};
#endif


#if defined(YACL_DEFINE_NULL)
#if !defined(__CFRONT__)
inline
#endif
CL_ObjectPtr&       CL_Basics<CL_ObjectPtr>::NullValueRef ()
{
    _Null = 0;
    return _Null;
}
#endif


#if !defined(__CFRONT__)
inline
#endif
CL_ObjectPtr       CL_Basics<CL_ObjectPtr>::NullValue ()
{
    return 0;
}



#if !defined(__CFRONT__)
inline
#endif
short CL_Basics<CL_ObjectPtr>::Compare
    (const CL_ObjectPtr& o1, const CL_ObjectPtr& o2)
{
#if defined(__MS_WINDOWS__) || defined(__DOS__)
    void huge* p1 = o1, *p2 = o2;
    return (o1 == NULL || o2 == NULL || !o2->IsA (*o1))
        ? (p1 < p2 ? -1 : (p1 == p2 ? 0 : 1))
        : (o1->Compare (*o2));
#else
    long l1 = (const long&) o1, l2 = (const long&) o2;
    return (o1 == NULL || o2 == NULL || !o2->IsA (*o1)) ?
        (l1 < l2 ? -1 : (l1 == l2 ? 0 : 1))
        : (o1->Compare (*o2));
#endif
}



#if !defined(__CFRONT__)
inline
#endif
CL_String  CL_Basics<CL_ObjectPtr>::PrintableForm
    (const CL_ObjectPtr& o)
{
    CL_String s;
    if (!o)
        s = "0x0";
    else {
        s.AssignWithFormat ("0x%8lx", o);
        s += " -> " + o->AsString ();
    }
    return s;
}


#if !defined(__CFRONT__)
inline
#endif
bool       CL_Basics<CL_ObjectPtr>::Read (CL_ObjectPtr& p,
                                                 const CL_Stream& s)
{
    return s.Read (p);
}


#if !defined(__CFRONT__)
inline
#endif
bool       CL_Basics<CL_ObjectPtr>::Write (const CL_ObjectPtr& p,
                                                  CL_Stream& s)
{
    return s.Write (p);
}


#if !defined(__CFRONT__)
inline
#endif
long       CL_Basics<CL_ObjectPtr>::StoreWidth (const CL_ObjectPtr& p)
{
    return p ? p->StorableFormWidth ()  : 0;
}


#if !defined(__CFRONT__)
inline
#endif
CL_ObjectPtr&      CL_Basics<CL_ObjectPtr>::Deref (const CL_VoidPtr& p)
{
    return (CL_ObjectPtr&) p;
}

#if !defined(__CFRONT__)
inline
#endif
void       CL_Basics<CL_ObjectPtr>::Destroy (CL_VoidPtr)
{
    // Do nothing
}


#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr    CL_Basics<CL_ObjectPtr>::MakeCopy (const CL_ObjectPtr& o)
{
    register CL_VoidPtr p = (const CL_VoidPtr&) o;
    return p;
}

#if !defined(__CFRONT__)
inline
#endif
CL_VoidPtr    CL_Basics<CL_ObjectPtr>::MakePointer
    (const CL_ObjectPtr& o)
{
    register CL_VoidPtr p = (const CL_VoidPtr&) o;
    return p;
}

#if !defined(__CFRONT__)
inline
#endif
void          CL_Basics<CL_ObjectPtr>::DoDestroy (const CL_ObjectPtr& p)
{
    if (p)
        delete p;
}



#if defined(__IBMCPP__)
#pragma define(CL_Basics<CL_ObjectPtr>)
#endif


#endif /* CFRONT stuff */

#endif /* _objptr_h_ */

