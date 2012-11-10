



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




#ifndef _tbtreimp_cxx_ /* Wed May 18 15:39:57 1994 */
#define _tbtreimp_cxx_


#include "base/tbtree.h"

#if !defined(__CFRONT__) || defined(__CFRONT_TBTREE_IMPL__)


#ifdef __GNUC__
#pragma implementation
#endif


#include "base/basicops.h"
// #include "base/voidptr.h"
#include "base/tbtree.h"
#include "base/cmparatr.cxx"


#include <iostream.h>


template <class ItemType>
CL_TemplateNodeSpace<ItemType>::~CL_TemplateNodeSpace ()
{
    _DestroySubtree (_root);
    _root = 0;    // This gets rid of the items also, because this class'
                  // version of the virtual DestroyItem is called.
}



// ----------------------- CL_BTree methods --------------------------

template <class ItemType>
CL_BTree<ItemType>::CL_BTree (short order,  CL_BTreeNodeSpace* space)
    : _nullValue (CL_Basics<ItemType> :: NullValue())
{
    _comparator = new CL_Comparator<ItemType>;
    if (space) {
        _space = NULL; // We don't own the node space
        _tree = new CL_GenericBTree (*_comparator, order, space);
    }
    else {
        _space = new CL_TemplateNodeSpace<ItemType> (order, *_comparator);
        _tree = new CL_GenericBTree (*_comparator, order, _space);
    }
        
}


template <class ItemType>
CL_BTree<ItemType>::CL_BTree (CL_AbstractComparator& cmp,
                              short order,  CL_BTreeNodeSpace* space)
    : _nullValue (CL_Basics<ItemType> :: NullValue())
{
    _tree = new CL_GenericBTree (cmp, order, space);
}


template <class ItemType>
CL_BTree<ItemType>::~CL_BTree ()
{
    if (_space)
        delete _space; // We own it if it's non-null
    if (_comparator)
        delete _comparator;
    if (_tree)
        delete _tree;
}


//
// ----------------------- Search and related methods ------------------


template <class ItemType>
ItemType CL_BTree<ItemType>::Find (const ItemType& item) const
{
    CL_VoidPtr p =  CL_Basics<ItemType>::MakePointer (item);
    CL_VoidPtr q = _tree->Find (p);
    if (q)
        return CL_Basics<ItemType>::Deref (q);
    ((CL_BTree<ItemType>*) this)->_nullValue =
        CL_Basics<ItemType>::NullValue();
    return _nullValue;
}




template <class ItemType>
ItemType CL_BTree<ItemType>::ItemWithRank (long i) const
{
    CL_VoidPtr p = _tree->ItemWithRank (i);
    if (p)
        return CL_Basics<ItemType>::Deref (p);
    ((CL_BTree<ItemType>*) this)->_nullValue =
        CL_Basics<ItemType>::NullValue();
    return _nullValue;
}



template <class ItemType>
long CL_BTree<ItemType>::RankOf (const ItemType& item) const
{
    CL_VoidPtr p = CL_Basics<ItemType>::MakePointer (item);
    return _tree->RankOf (p);
}


template <class ItemType>
long CL_BTree<ItemType>::Size () const
{
    return _tree->Size();
}


template <class ItemType>
bool CL_BTree<ItemType>::Add  (const ItemType& item)
{
    if (!PrepareToChange())
        return FALSE;
    CL_VoidPtr p = CL_Basics<ItemType>::MakeCopy (item);
    if (_tree->Add (p)) {
        Notify();
        return TRUE;
    }
    CL_Basics<ItemType>::Destroy (p);
    return FALSE;
}



template <class ItemType>
ItemType CL_BTree<ItemType>::Remove (const ItemType& item)
{
    if (!PrepareToChange())
        return CL_Basics<ItemType>::NullValue();
    CL_VoidPtr p = CL_Basics<ItemType>::MakePointer (item);
    CL_VoidPtr q = _tree->Remove (p);
    if (q) {
        ItemType r = CL_Basics<ItemType>::Deref(q);
        CL_Basics<ItemType>::Destroy (q);
        Notify ();
        return r;
    }
    return CL_Basics<ItemType>::NullValue();
}


template <class ItemType>
ItemType CL_BTree<ItemType>::ExtractMin ()
{
    if (!PrepareToChange())
        return CL_Basics<ItemType>::NullValue ();
    CL_VoidPtr p = _tree->ExtractMin ();
    if (p) {
        Notify();
        ItemType t = CL_Basics<ItemType>::Deref (p);
        CL_Basics<ItemType>::Destroy (p);
        return t;
    }
    return CL_Basics<ItemType>::NullValue ();
}




template <class ItemType>
void CL_BTree<ItemType>::IntoStream (ostream& strm) const
{
    CL_BTreeNodeSpace* space = _tree->NodeSpace ();
    if (space) {
        CL_BTreeNodeHandle h = space->RootHandle();
        PrintTree (h, 0, strm);
    }
}




template <class ItemType>
void CL_BTree<ItemType>::PrintTree (CL_BTreeNodeHandle h, short level,
                                    ostream& strm) const
{
    if (h == 0)
        return;
    CL_BTreeNodeSpace* space = _tree->NodeSpace ();
    CL_GenericBTreeNode* z = space->BorrowNode (h);

    for (short i = 0; i < z->Size(); i++) {
        PrintTree (z->Subtree(i), level+1, strm);
        for (short j = 0; j < 4*level; j++)
            strm << ' ';
        CL_VoidPtr q = z->Item(i);
        ItemType p = CL_Basics<ItemType>::Deref (q);
	CL_String st = CL_Basics<ItemType>::PrintableForm (p);
        strm << "------>" << (const char*) st << endl << flush;
    }
    PrintTree (z->Subtree(z->Size()), level+1, strm);
    space->ReturnNode (z);
}






// ---------------------------------------------------------------------
//                    CL_BTreeIterator methods
// ---------------------------------------------------------------------




template <class ItemType>
CL_BTreeIterator<ItemType>::CL_BTreeIterator(const CL_BTree<ItemType>& t)
: _iter (*(t._tree))
{
}

template <class ItemType>
CL_BTreeIterator<ItemType>::CL_BTreeIterator
    (const CL_BTreeIterator<ItemType>& itr) 
: _iter (itr._iter)
{
}


template <class ItemType>
void CL_BTreeIterator<ItemType>::Reset()
{
    _iter.Reset();
}



template <class ItemType>
void CL_BTreeIterator<ItemType>::BeginFrom (const ItemType& t)
{
    const CL_VoidPtr p = CL_Basics<ItemType>::MakePointer (t);
    _iter.BeginFrom (p);
}



template <class ItemType>
bool CL_BTreeIterator<ItemType>::More()
{
    return _iter.More ();
}


template <class ItemType>
const ItemType& CL_BTreeIterator<ItemType>::Next()
{
    CL_VoidPtr q = _iter.Next();
    _data = CL_Basics<ItemType>::Deref (q);
    return _data;
}



#endif /* CFRONT stuff */

#endif /* _tbtreimp_cxx_ */
