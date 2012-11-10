

#ifndef _treewalk_h_ /* Tue Mar 15 12:28:42 1994 */
#define _treewalk_h_





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
#pragma interface
#endif

#ifdef __IBMCPP__
#pragma implementation("treewalk.cxx")
#endif

#include "base/tree.h"


// The PostOrderWalker is an iterator that walks through a (subtree of a)
// Tree in postorder.


template <class ItemType>
class YACL_BASE CL_PostOrderWalker: public CL_Object {

public:
    CL_PostOrderWalker (CL_TreeNode<ItemType>* node);
    // Constructor: to walk the subtree rooted at the given node.

    ~CL_PostOrderWalker ();
    
    void Reset ();
    // Reset the iterator. The next call to {\tt Next} will return the
    // leftmost leaf in the tree, in accordance with postorder.

    bool More  ();
    // Return TRUE if there are nodes left in the walk.

    CL_TreeNode<ItemType>* Next();
    // Return the next node in postorder.

protected:
    CL_TreeNode<ItemType>*    _subtreeRoot;
    CL_ObjectSequence         _stack;
};





// The PreOrderWalker is an iterator that walks through a (subtree of a)
// Tree in  preorder.



template <class ItemType>
class YACL_BASE CL_PreOrderWalker: public CL_Object {

public:
    CL_PreOrderWalker (CL_TreeNode<ItemType>* node);
    // Constructor: to walk the subtree rooted at the given node.

    ~CL_PreOrderWalker ();

    void Reset ();
    // Reset the iterator. The next call to {\tt Next} will return the root
    // of the subtree, in accordance with preorder.

    bool More  ();
    // Return TRUE if there are nodes left in the walk.

    CL_TreeNode<ItemType>* Next();
    // Return the next node in preorder.

protected:
    CL_TreeNode<ItemType>*    _subtreeRoot;
    CL_ObjectSequence         _stack;
};



#ifndef _no_cl_treewalk_typedefs_
#include "base/treewdef.h"
#endif

#endif /* _treewalk_h_ */
