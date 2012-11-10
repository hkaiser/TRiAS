



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



#ifdef __GNUC__
#pragma implementation
#endif


#include "base/clntset.h"
#include "base/string.h"


CL_ClientSet::~CL_ClientSet ()
{
    _set.DestroyContents();
}


bool CL_ClientSet::Add (const CL_AbstractBinding& b)
{
    CL_AbstractBinding* element = (CL_AbstractBinding*) b.Clone ();
    bool flg = _set.Add (element);
    if (!flg)
        delete element;
    return flg;
}




bool CL_ClientSet::Remove (const CL_AbstractBinding& b)
{
    CL_AbstractBinding* element = (CL_AbstractBinding*)
        _set.Remove ((CL_ObjectPtr) (&b));
    if (element) {
        delete element;
        Notify ();
        return TRUE;
    }
    return FALSE;
}


bool CL_ClientSet::Includes (const CL_AbstractBinding& b) const
{
    return _set.Includes ((CL_ObjectPtr) &b);
}



CL_AbstractBinding* CL_ClientSet::Find (const CL_AbstractBinding& b) const
{
    return (CL_AbstractBinding*) _set.Find ((CL_Object*) &b);
}


void CL_ClientSet::NotifyAll (CL_Object& o) const
{
    CL_AbstractBinding* e;
    long n = _set.Size();
    for (short i = 0; i < n; i++) {
        e = (CL_AbstractBinding*) _set.ItemWithRank (i);
        if (e)
            e->Execute (o);
    }
}


bool CL_ClientSet::Permits (CL_Object& o) const
{
    CL_AbstractBinding* e;
    long n = _set.Size();
    // Stop after the first FALSE return
    for (short i = 0; i < n; i++) {
        e = (CL_AbstractBinding*) _set.ItemWithRank (i);
        if (e && !e->Execute (o))
            return FALSE;
    }
    return TRUE;
}


void CL_ClientSet::MakeEmpty ()
{
    _set.DestroyContents();
}


CL_String CL_ClientSet::AsString () const
{
    CL_String ret;
    CL_AbstractBinding* e;
    long n = _set.Size();
    for (short i = 0; i < n; i++) {
        e = (CL_AbstractBinding*) _set.ItemWithRank (i);
        if (e)
            ret += "  -- " + e->AsString () + "\n";
        else
            ret += "  --\n";
    }
    return ret;
}
