



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




// Instantiate a few B-trees.

#include "base/tbtreimp.cxx"
#include "base/basicops.cxx"

#if defined (__GNUC__) && __GNUC_MINOR__ >= 6
template class CL_BTree<CL_String>;
template class CL_BTree<CL_ObjectPtr>;
template class CL_BTree<long>;

template class CL_TemplateNodeSpace<CL_String>;
template class CL_TemplateNodeSpace<CL_ObjectPtr>;
template class CL_TemplateNodeSpace<long>;

template class CL_Comparator<CL_ObjectPtr>;
template class CL_Comparator<long>;

template class CL_BTreeIterator<CL_String>;
template class CL_BTreeIterator<long>;
template class CL_BTreeIterator<CL_ObjectPtr>;

#elif defined(_MSC_VER)
template CL_BTree<CL_String>;
template CL_BTree<CL_ObjectPtr>;
template CL_BTree<long>;
         
template CL_TemplateNodeSpace<CL_String>;
template CL_TemplateNodeSpace<CL_ObjectPtr>;
template CL_TemplateNodeSpace<long>;
         
template CL_Comparator<CL_ObjectPtr>;
template CL_Comparator<long>;
         
template CL_BTreeIterator<CL_String>;
template CL_BTreeIterator<long>;
template CL_BTreeIterator<CL_ObjectPtr>;


#elif defined(__IBMCPP__)
#pragma define(CL_BTree<CL_String>)
#pragma define(CL_BTree<CL_ObjectPtr>)
#pragma define(CL_BTree<long>)
#pragma define(CL_Comparator<CL_ObjectPtr>)

#pragma define(CL_BTreeIterator<CL_String>)
#pragma define(CL_BTreeIterator<long>)
#pragma define(CL_BTreeIterator<CL_ObjectPtr>)
#endif

typedef CL_BTree<CL_String> CL_StringBTree;
typedef CL_BTree<CL_ObjectPtr> CL_ObjectPtrBTree;

typedef CL_BTreeIterator<CL_String> CL_StringBTreeIterator;
typedef CL_BTreeIterator<CL_ObjectPtr> CL_ObjectPtrBTreeIterator;

typedef CL_TemplateNodeSpace<CL_String> CL_StringBTreeNodeSpace;
typedef CL_TemplateNodeSpace<CL_ObjectPtr> CL_ObjectPtrBTreeNodeSpace;

