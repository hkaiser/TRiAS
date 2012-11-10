



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






#ifndef _map_cxx_ /* Tue Nov 16 22:12:10 1993 */
#define _map_cxx_

#ifdef __GNUC__
#pragma implementation
#endif


#include "base/string.h"

#define _no_cl_map_typedefs_
#include "base/mapimp.cxx"




#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
template class CL_Map<long, CL_String>;
template class CL_Map<long, long>;
template class CL_Map<long, CL_ObjectPtr>;
template class CL_Map<CL_String, CL_String>;
template class CL_Map<CL_String, long>;
template class CL_Map<CL_String, CL_ObjectPtr>;
template class CL_Map<CL_ObjectPtr, CL_ObjectPtr>;
template class CL_Map<CL_ObjectPtr, long>;


template class CL_MapAssoc<long, CL_String>;
template class CL_MapAssoc<long, long>;
template class CL_MapAssoc<long, CL_ObjectPtr>;
template class CL_MapAssoc<CL_String, CL_String>;
template class CL_MapAssoc<CL_String, long>;
template class CL_MapAssoc<CL_String, CL_ObjectPtr>;
template class CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr>;
template class CL_MapAssoc<CL_ObjectPtr, long>;


template class CL_MapIterator<long, CL_String>;
template class CL_MapIterator<long, long>;
template class CL_MapIterator<long, CL_ObjectPtr>;
template class CL_MapIterator<CL_String, CL_String>;
template class CL_MapIterator<CL_String, long>;
template class CL_MapIterator<CL_String, CL_ObjectPtr>;
template class CL_MapIterator<CL_ObjectPtr, CL_ObjectPtr>;
template class CL_MapIterator<CL_ObjectPtr, long>;


template class CL_Iterator<CL_MapAssoc<long, CL_String> >;
template class CL_Iterator<CL_MapAssoc<long, long> >;
template class CL_Iterator<CL_MapAssoc<long, CL_ObjectPtr> >;
template class CL_Iterator<CL_MapAssoc<CL_String, CL_String> >;
template class CL_Iterator<CL_MapAssoc<CL_String, long> >;
template class CL_Iterator<CL_MapAssoc<CL_String, CL_ObjectPtr> >;
template class CL_Iterator<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> >;
template class CL_Iterator<CL_MapAssoc<CL_ObjectPtr, long> >;

template class CL_Basics<CL_MapAssoc<long, CL_String> >;
template class CL_Basics<CL_MapAssoc<long, long> >;
template class CL_Basics<CL_MapAssoc<long, CL_ObjectPtr> >;
template class CL_Basics<CL_MapAssoc<CL_String, CL_String> >;
template class CL_Basics<CL_MapAssoc<CL_String, long> >;
template class CL_Basics<CL_MapAssoc<CL_String, CL_ObjectPtr> >;
template class CL_Basics<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> >;
template class CL_Basics<CL_MapAssoc<CL_ObjectPtr, long> >;

#elif defined(_MSC_VER)
#pragma warning (disable:4661)

template CL_Map<long, CL_String>;
template CL_Map<long, long>;
template CL_Map<long, CL_ObjectPtr>;
template CL_Map<CL_String, CL_String>;
template CL_Map<CL_String, long>;
template CL_Map<CL_String, CL_ObjectPtr>;
template CL_Map<CL_ObjectPtr, CL_ObjectPtr>;
template CL_Map<CL_ObjectPtr, long>;
         
         
template CL_MapAssoc<long, CL_String>;
template CL_MapAssoc<long, long>;
template CL_MapAssoc<long, CL_ObjectPtr>;
template CL_MapAssoc<CL_String, CL_String>;
template CL_MapAssoc<CL_String, long>;
template CL_MapAssoc<CL_String, CL_ObjectPtr>;
template CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr>;
template CL_MapAssoc<CL_ObjectPtr, long>;
         
         
template CL_MapIterator<long, CL_String>;
template CL_MapIterator<long, long>;
template CL_MapIterator<long, CL_ObjectPtr>;
template CL_MapIterator<CL_String, CL_String>;
template CL_MapIterator<CL_String, long>;
template CL_MapIterator<CL_String, CL_ObjectPtr>;
template CL_MapIterator<CL_ObjectPtr, CL_ObjectPtr>;
template CL_MapIterator<CL_ObjectPtr, long>;
         
         
template CL_Iterator<CL_MapAssoc<long, CL_String> >;
template CL_Iterator<CL_MapAssoc<long, long> >;
template CL_Iterator<CL_MapAssoc<long, CL_ObjectPtr> >;
template CL_Iterator<CL_MapAssoc<CL_String, CL_String> >;
template CL_Iterator<CL_MapAssoc<CL_String, long> >;
template CL_Iterator<CL_MapAssoc<CL_String, CL_ObjectPtr> >;
template CL_Iterator<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> >;
template CL_Iterator<CL_MapAssoc<CL_ObjectPtr, long> >;
         
template CL_Basics<CL_MapAssoc<long, CL_String> >;
template CL_Basics<CL_MapAssoc<long, long> >;
template CL_Basics<CL_MapAssoc<long, CL_ObjectPtr> >;
template CL_Basics<CL_MapAssoc<CL_String, CL_String> >;
template CL_Basics<CL_MapAssoc<CL_String, long> >;
template CL_Basics<CL_MapAssoc<CL_String, CL_ObjectPtr> >;
template CL_Basics<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> >;
template CL_Basics<CL_MapAssoc<CL_ObjectPtr, long> >;

#elif defined(__IBMCPP__)
#pragma define(CL_Basics<CL_ObjectPtr>)
#pragma define(CL_Basics<CL_VoidPtr>)
#pragma define(CL_Basics<long>)
#pragma define(CL_Basics<CL_String>)

#pragma define(CL_MapIterator<long, CL_String>)
#pragma define(CL_MapIterator<long, long>)
#pragma define(CL_MapIterator<long, CL_ObjectPtr>)
#pragma define(CL_MapIterator<CL_String, CL_String>)
#pragma define(CL_MapIterator<CL_String, long>)
#pragma define(CL_MapIterator<CL_String, CL_ObjectPtr>)
#pragma define(CL_MapIterator<CL_ObjectPtr, CL_ObjectPtr>)
#pragma define(CL_MapIterator<CL_ObjectPtr, long>)
         
#pragma define(CL_Basics<CL_MapAssoc<long, CL_String> >)
#pragma define(CL_Basics<CL_MapAssoc<long, long> >)
#pragma define(CL_Basics<CL_MapAssoc<long, CL_ObjectPtr> >)
#pragma define(CL_Basics<CL_MapAssoc<CL_String, CL_String> >)
#pragma define(CL_Basics<CL_MapAssoc<CL_String, long> >)
#pragma define(CL_Basics<CL_MapAssoc<CL_String, CL_ObjectPtr> >)
#pragma define(CL_Basics<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> >)
#pragma define(CL_Basics<CL_MapAssoc<CL_ObjectPtr, long> >)

#elif defined(__SGI_DELTA_CC__)
#pragma instantiate CL_Basics<CL_ObjectPtr>
#pragma instantiate CL_Basics<CL_VoidPtr>
#pragma instantiate CL_Basics<long>
#pragma instantiate CL_Basics<CL_String>

#pragma instantiate CL_MapIterator<long, CL_String>
#pragma instantiate CL_MapIterator<long, long>
#pragma instantiate CL_MapIterator<long, CL_ObjectPtr>
#pragma instantiate CL_MapIterator<CL_String, CL_String>
#pragma instantiate CL_MapIterator<CL_String, long>
#pragma instantiate CL_MapIterator<CL_String, CL_ObjectPtr>
#pragma instantiate CL_MapIterator<CL_ObjectPtr, CL_ObjectPtr>
#pragma instantiate CL_MapIterator<CL_ObjectPtr, long>
         
#pragma instantiate CL_Basics<CL_MapAssoc<long, CL_String> >
#pragma instantiate CL_Basics<CL_MapAssoc<long, long> >
#pragma instantiate CL_Basics<CL_MapAssoc<long, CL_ObjectPtr> >
#pragma instantiate CL_Basics<CL_MapAssoc<CL_String, CL_String> >
#pragma instantiate CL_Basics<CL_MapAssoc<CL_String, long> >
#pragma instantiate CL_Basics<CL_MapAssoc<CL_String, CL_ObjectPtr> >
#pragma instantiate CL_Basics<CL_MapAssoc<CL_ObjectPtr, CL_ObjectPtr> >
#pragma instantiate CL_Basics<CL_MapAssoc<CL_ObjectPtr, long> >
#endif



#include "base/mapdef.h"







#endif /* _map_cxx_ */

