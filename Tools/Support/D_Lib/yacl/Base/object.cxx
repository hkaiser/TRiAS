



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


#include <iostream.h>

#include "base/clntset.h"
#include "base/stream.h"
#include "base/map.h"
#include "base/basicops.h"


static CL_Map<long,long>* __FAR TheClassIdMap = NULL;


CL_Map<long,long>& CL_Object::_ClassIdMap =
TheClassIdMap ? *TheClassIdMap
: *(TheClassIdMap = new CL_Map<long,long>);


CL_ClassIdEntryMaker::CL_ClassIdEntryMaker (CL_ClassId id, CL_Creator func)
{
    if (!TheClassIdMap) {
        TheClassIdMap = new CL_Map<long,long>;
    }
    TheClassIdMap->Add (id, (long) func);
}


CL_ClassIdEntryMaker::~CL_ClassIdEntryMaker ()
{
    if (TheClassIdMap) {
        delete TheClassIdMap;
        TheClassIdMap = NULL;
    }
}


bool CL_Object::CheckClassType (const CL_Object& o, const char*
                                       msg) const
{
    register bool b = IsA (o);
    if (!b)
        CL_Error::Warning ("%s: Invalid class '%s'", msg, o.ClassName());
    return b;
}

void CL_Object::NotImplemented (const char* method_name) const
{
    CL_Error::Warning ("Class '%s' does not implement method '%s'\n",
                       ClassName(), method_name);
}
    
CL_Object* CL_Object::Clone () const
{
    NotImplemented ("Clone"); return NULL;
}



void CL_Object::operator= (const CL_Object&)
{
    NotImplemented ("op= (const CL_Object&)");
}

void CL_Object::FromStream (istream&)
{
    NotImplemented ("FromStream (istream&)");
}

CL_String CL_Object::AsString() const
{
    NotImplemented ("CL_Object::AsString");
    return "";
}


bool CL_Object::operator== (const CL_Object& o) const
{
#if defined(__DOS__) || defined(__MS_WINDOWS__)
    return ((void huge *) this) == ((void huge *) &o);
#else
    return ((ulong) this) == ((ulong) &o);
#endif
}


bool CL_Object::operator< (const CL_Object& o) const
{
#if defined(__DOS__) || defined(__MS_WINDOWS__)
    return ((ulong) (void huge *) this) < ((ulong) (void huge *) &o);
#else
    return ((ulong) this) < ((ulong) &o);
#endif
}



istream& operator>> (istream& s, CL_Object& o)
{
    o.FromStream (s);
    return s;
}



ostream& operator<< (ostream& s, const CL_Object& o)
{
    o.IntoStream (s);
    return s;
}




void CL_Object::IntoStream (ostream& o) const
{
    CL_String s = AsString ();
    o << s.AsPtr();
}


bool CL_Object::ReadClassId (const CL_Stream& s) const
{
    long id;
    if (!s.Read (id))
        return FALSE;
    if (id != ClassId()) {
        s.SeekTo (s.Offset() - sizeof id);
        return FALSE;
    }
    return TRUE;
}

bool CL_Object::ReadFrom  (const CL_Stream&)
{
    NotImplemented ("ReadFrom");
    return FALSE;
}


bool CL_Object::WriteTo  (CL_Stream&) const
{
    NotImplemented ("WriteTo");
    return FALSE;
}




bool CL_Object::CompareWith (const CL_Object& obj,
                             CL_ComparisonOperator op) const
{
    short result;
    if (!obj.IsA (*this))
        result = (this < &obj ? -1 : 1);
    else
        result = Compare (obj);
    switch (op) {
    case CL_CMP_EQUAL:
        return result == 0;
        
    case CL_CMP_LESSTHAN:
        return result < 0;
        
    case CL_CMP_GTRTHAN:
        return result > 0;
        
    case CL_CMP_LESSEQ:
        return result <= 0;
        
    case CL_CMP_GTREQ:
        return result >= 0;
        
    case CL_CMP_NOTEQUAL:
        return result != 0;
        
    case CL_CMP_PREFIX:
    case CL_CMP_CONTAINS:
        return AsString().CompareWith (obj.AsString(), op);

    default:
        CL_Error::Warning ("CL_Object::CompareWith: bad operator %d",
                           (short) op);
        break;
    }
    return FALSE;
}



bool CL_Object::CompareWith (const CL_String& obj,
                             CL_ComparisonOperator op) const
{
    return AsString().CompareWith (obj, op);
}










// ---------------------- Dependency methods ------------------------


struct CL_DependStruct {
    CL_ClientSet postChange;
    CL_ClientSet preChange;
};

CL_Object::~CL_Object()
{
    if (_dependSet) {
        delete  _dependSet;
    }
}

        

void CL_Object::Notify ()
{
    if (_dependSet) {
        ( _dependSet)->postChange.NotifyAll (*this);
    }
}


void CL_Object::AddDependent (const CL_AbstractBinding& binding)
{
    if (!_dependSet) {
        _dependSet = new CL_DependStruct;
        if (!_dependSet)
            return; // No memory
    }
    _dependSet->postChange.Add (binding);
}




void CL_Object::RemoveDependent (const CL_AbstractBinding& binding)
{
    if (_dependSet) {
        ( _dependSet)->postChange.Remove (binding);
    }
}



bool CL_Object::HasDependent (const CL_AbstractBinding& o) const
{
    return _dependSet && _dependSet->postChange.Includes (o);
}



// Pre-change notification methods



bool CL_Object::PrepareToChange ()
{
    if (_dependSet)
        return  ( _dependSet)->preChange.Permits (*this);
    return TRUE;
}



void CL_Object::AddPreChangeDependent (const CL_AbstractBinding& binding)
{
    if (!_dependSet) {
        _dependSet = new CL_DependStruct;
        if (!_dependSet)
            return; // No memory
    }
    ( _dependSet)->preChange.Add (binding);
}


// Remove a binding from our dependent list
void CL_Object::RemovePreChangeDependent (const CL_AbstractBinding& b)
{
    if (_dependSet) {
        ( _dependSet)->preChange.Remove (b);
    }
}


// Is the given object dependent on us?
bool CL_Object::HasPreChangeDependent (const CL_AbstractBinding& b) const
{
    return _dependSet &&
        ( _dependSet)->preChange.Includes (b);
}


const CL_ClientSet* CL_Object::PreChangeDependents() const
{
    return _dependSet ? &(_dependSet->preChange) : 0;
}

const CL_ClientSet* CL_Object::PostChangeDependents() const
{
    return _dependSet ? &(_dependSet->postChange) : 0;
}



#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
template class CL_Binding0<CL_Object>;
#elif defined(__SGI_DELTA_CC__)
#pragma instantiate CL_Binding0<CL_Object>
#endif





//
// All static objects in the base library are declared here.
//


#include "base/base.h"
#include "base/basicops.h"

#if !defined(__GNUC__)
#include "base/basicops.cxx"
#endif


//
// Make specializations
//
#if defined(__CFRONT__)

#define __CFRONT_OBJPTR_IMPL__
#include "base/objptr.h"
#undef __CFRONT_OBJPTR_IMPL__

#define __CFRONT_VOIDPTR_IMPL__
#include "base/voidptr.h"
#undef __CFRONT_VOIDPTR_IMPL__

#define __CFRONT_LONG_IMPL__
#include "base/long.h"
#undef __CFRONT_LONG_IMPL__

#endif


// Invoke all the define_class macros

CL_DEFINE_CLASS (CL_BitSet,          _CL_BitSet_CLASSID);
CL_DEFINE_CLASS (CL_ByteArray,       _CL_ByteArray_CLASSID);
CL_DEFINE_CLASS (CL_ByteString,      _CL_ByteString_CLASSID);
CL_DEFINE_CLASS (CL_Date,            _CL_Date_CLASSID);
CL_DEFINE_CLASS (CL_Integer,         _CL_Integer_CLASSID);
CL_DEFINE_CLASS (CL_IntegerSequence, _CL_IntegerSequence_CLASSID);
CL_DEFINE_CLASS (CL_IntegerSet,      _CL_IntegerSet_CLASSID);
// CL_DEFINE_CLASS (CL_GenericMap,      _CL_GenericMap_CLASSID);
CL_DEFINE_CLASS (CL_IntStringMap,    _CL_IntStringMap_CLASSID);
CL_DEFINE_CLASS (CL_IntIntMap,       _CL_IntIntMap_CLASSID);
CL_DEFINE_CLASS (CL_IntPtrMap,       _CL_IntPtrMap_CLASSID);
CL_DEFINE_CLASS (CL_StringStringMap, _CL_StringStringMap_CLASSID);
CL_DEFINE_CLASS (CL_StringIntMap,    _CL_StringIntMap_CLASSID);
CL_DEFINE_CLASS (CL_StringPtrMap,    _CL_StringPtrMap_CLASSID);
CL_DEFINE_CLASS (CL_PtrIntMap,       _CL_PtrIntMap_CLASSID);
CL_DEFINE_CLASS (CL_ObjectSequence,  _CL_ObjectSequence_CLASSID);
CL_DEFINE_CLASS (CL_ObjectSet,       _CL_ObjectSet_CLASSID);
CL_DEFINE_CLASS (CL_StringSequence,  _CL_StringSequence_CLASSID);
CL_DEFINE_CLASS (CL_String,          _CL_String_CLASSID);
CL_DEFINE_CLASS (CL_TimeOfDay,       _CL_TimeOfDay_CLASSID);



// CL_Integer   CL_Basics<CL_Integer  >::_Null
//     = CL_Basics<CL_Integer >::NullValue();
// 
// CL_String    CL_Basics<CL_String   >::_Null
//     = CL_Basics<CL_String>::NullValue();
// 
// CL_TimeOfDay CL_Basics<CL_TimeOfDay>::_Null
//     = CL_Basics<CL_TimeOfDay>::NullValue();
// 
// CL_Date      CL_Basics<CL_Date    >::_Null
//     = CL_Basics<CL_Date  >::NullValue();
// 
// long           CL_Basics<long       >::_Null = 0;
// 
// CL_VoidPtr     CL_Basics<CL_VoidPtr >::_Null = (CL_VoidPtr) 0;
// 
// CL_ObjectPtr   CL_Basics<CL_ObjectPtr>::_Null = (CL_ObjectPtr) 0;
// 
// 
// 
// CL_MapAssoc<long, CL_String>
//     CL_Basics<CL_MapAssoc<long, CL_String> > :: _Null =
//     CL_Basics<CL_MapAssoc<long, CL_String> > :: NullValue();
// CL_MapAssoc<long, long>
//     CL_Basics<CL_MapAssoc<long, long> > :: _Null =
//     CL_Basics<CL_MapAssoc<long, long> > :: NullValue();
// CL_MapAssoc<long, CL_ObjectPtr>
//     CL_Basics<CL_MapAssoc<long, CL_ObjectPtr> > :: _Null =
//     CL_Basics<CL_MapAssoc<long, CL_ObjectPtr> > :: NullValue();
// CL_MapAssoc<CL_String, CL_String>
//     CL_Basics<CL_MapAssoc<CL_String, CL_String> > :: _Null =
//     CL_Basics<CL_MapAssoc<CL_String, CL_String> > :: NullValue();
// CL_MapAssoc<CL_String, long>
//     CL_Basics<CL_MapAssoc<CL_String, long> > :: _Null =
//     CL_Basics<CL_MapAssoc<CL_String, long> > :: NullValue();
// CL_MapAssoc<CL_String, CL_ObjectPtr>
//     CL_Basics<CL_MapAssoc<CL_String, CL_ObjectPtr> > :: _Null =
//     CL_Basics<CL_MapAssoc<CL_String, CL_ObjectPtr> > :: NullValue();
// CL_MapAssoc<CL_ObjectPtr, long>
//     CL_Basics<CL_MapAssoc<CL_ObjectPtr, long> > :: _Null =
//     CL_Basics<CL_MapAssoc<CL_ObjectPtr, long> > :: NullValue();
// 
// #if defined(__GNUC__) || defined(_MSC_VER) || defined(__IBMCPP__)
// // Don't want this under Borland C yet
// CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr>
//     CL_Basics<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> > :: _Null =
//     CL_Basics<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> > :: NullValue();
// #endif

