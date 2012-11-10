



#ifndef _tree_h_ /* Mon Aug 23 17:09:26 1993 */
#define _tree_h_





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





// Tree is  a  class template that maintains parent-child relationships among
// objects of type ItemType, the template parameter. Each node  of the
// tree contains a single item of type ItemType; this item is returned by
// the node's {\tt Content} method. Each node is
// labeled with an  element of type  LabelType (which is {\tt typedef'ed} as
// a {\tt long}), and all  the nodes of the
// tree are required to have distinct labels.
// 
// The destructor of the tree destroys all the nodes in it. As with other
// YACL containers, if the tree's items (those returned by the TreeNode's
// {\tt Content} method) are class objects (i.e., ItemType is
// a class), they are also destroyed when the tree is destroyed.  If, however,
// the tree is instantiated with a pointer-based template base type (as is
// GenericTree), the pointed-to objects are {\it not\/} destroyed by the
// tree's destructor; a tree walker (see {\tt treewalk.h}) can be used to
// do so before destroying the tree.
// 
// Caveat: In the interests of future expandability, do not use
// templated
// names  for types; use only the {\tt typedef} names at  the end of this file
// (e.g., use VoidPtrTree but  not {\small\tt  CL_Tree <VoidPtr>}).  This
// will allow the implementation to be made more efficient (later) without
// affecting the  interface.



#ifdef __GNUC__
#pragma interface
#endif

#ifdef __IBMCPP__
#pragma implementation("treeimp.cxx")
#endif

#include "base/object.h"
#include "base/sequence.h"
#include "base/map.h"
#include "base/binding.h"

template <class ItemType> class YACL_BASE CL_TreeNode;
    

typedef long CL_TreeNodeLabel;

template <class ItemType>
class YACL_BASE  CL_Tree: public CL_Object {

public:

    // --------------- Construction and destruction ----------------

    CL_Tree ();
    // Default constructor: build an empty tree.

    CL_Tree (CL_TreeNodeLabel root);
    // Constructor: build a tree with root having the given label.

    ~CL_Tree()
        { _DeleteSubtree (_root);}
    // Destructor.
    
    // -------------------- Querying operations ------------------------

    CL_TreeNode<ItemType>* Root () const
        { return _root;};
    // Return the root of the tree. Return the NULL pointer if the tree is
    // empty.

    CL_TreeNode<ItemType>* Node (CL_TreeNodeLabel l) const;
    // Return the node with the given label, if it exists; return NULL if
    // no such node exists. The return value points to  an object owned by the
    // tree and must not be destroyed by the caller.
    
    bool IsAncestor (CL_TreeNodeLabel n1, CL_TreeNodeLabel n2) const;
    // Return TRUE if the node with label {\tt n1} is an ancestor of (or is
    // the same as) the node with label {\tt n2}. This method returns FALSE
    // if either of the labels is invalid.
    

    // ---------- Addition and removal of nodes and subtrees -----------
    
    CL_TreeNode<ItemType>* AddChild (CL_TreeNodeLabel obj,
                                      CL_TreeNodeLabel parent,
                                      long i = 200000L);
    // Add obj as the $i$-th child of the given parent; return the newly
    // created node. Return NULL on error (e.g. parent is not in tree,
    // invalid index specified, a node with the given label is already
    // in the tree, or a memory allocation error occurs). An index of
    // $-1$ specifies leftmost child. 
    // Specifying a very large index (specifically, anything larger
    // than the number of siblings) causes addition as the rightmost
    // child. The default value of the index is large enough, in most
    // situations, to mean addition as rightmost child.

    CL_TreeNode<ItemType>* NewRoot (CL_TreeNodeLabel l);
    // Create a new root with given label, and make the current root
    // the (only) child of the new root. Return the new root if
    // successful, and NULL on failure.
    
    CL_Tree<ItemType>* ExtractSubtree (CL_TreeNodeLabel obj);
    // Remove and return the subtree rooted at the given node. The
    // returned tree must be destroyed by the caller of this method.
    
    void DestroySubtree (CL_TreeNodeLabel x);
    // Destroy the subtree rooted at x, and remove x from its
    // parent's set of children.

    // --------------------- Traversal -----------------------------

    long PostOrderWalk (CL_TreeNodeLabel l, const
                        CL_AbstractBinding& bind) const;
    // Perform a post-order traversal of the subtree rooted at the
    // node with the given label, and at each node in the traversal,
    // execute binding {\tt bind}. The parameter to the binding method is
    // the node being visited. The traversal
    // continues while the called
    // binding returns TRUE, and  stops when either the binding returns
    // FALSE or the subtree has been completely visited. The called
    // method should {\it not\/} modify the tree.
    //
    //    The return value is the number of nodes traversed.

    long Traverse (CL_TreeNodeLabel l, const CL_AbstractBinding& action1,
                   const CL_AbstractBinding& action2) const;
    // This is a generalized traversal of the tree,
    // incorporating both preorder and postorder as special cases.
    // It traverses the subtree rooted at the node with the given label,
    // using the following algorithm:
    //
    // \begin{enumerate}
    // \item  Invoke {\tt action1} at current node $v$, with $v$ as
    //        parameter
    // \item  For each child $w$ of current node $v$, in left-to-right order,
    //            recursively traverse the subtree rooted at $w$
    // \item  Invoke {\tt action2} at current node $v$, with $v$ as
    //        parameter 
    // \end{enumerate}
    // \noindent
    // The traversal terminates when either the subtree has been
    // completed, or when either of the action calls returns FALSE.
    // The return value of the method is the number of nodes traversed.
    // Note that there are {\it two\/} calls at each node, once when entering
    // the node and once when backing up into the node. This is true
    // even for leaf nodes.
    //
    // If the Binding is not valid (see {\tt binding.h})
    // the action is not invoked.
    //
    // Neither of the binding client methods should modify the tree.
    
    // --------------------- Basic methods ---------------------------

    const char* ClassName() const { return "CL_Tree";};
    
    CL_ClassId ClassId() const   { return _CL_Tree_CLASSID;};


    // --------------------- End public protocol ----------------------
    
    
    
protected:

    void _DeleteSubtree (CL_TreeNode<ItemType>* node);

    void _BuildSubmap   (CL_TreeNode<ItemType>* node);

    bool _Walk          (CL_TreeNode<ItemType>* node,
                         const CL_AbstractBinding& b1,
                         const CL_AbstractBinding& b2,
                         long& count) const;
    
    CL_TreeNode<ItemType>* _root;
    CL_IntPtrMap           _map; // The map of label values to node pointers
};





// The class TreeNode is intended to be used only in conjunction with the
// class Tree; nodes of the tree may be accessed via the Node() method of
// the tree. Caveat: Do not use TreeNode methods for modifying the node
// directly. The only exception to this is the return value of the {\tt
// Content} method, which the application can modify as needed.

template <class ItemType>
class YACL_BASE  CL_TreeNode: public CL_Object {
    
public:
    CL_TreeNode (CL_TreeNodeLabel lbl);
    // Create a TreeNode with the given label.

    ~CL_TreeNode();

    // ------------------ Querying functions -------------------------

    CL_TreeNodeLabel Label () const
    { return _label; }
    // Return the label of this TreeNode.

    CL_TreeNode<ItemType>* Parent () const
    { return _parent; };
    // Return a pointer to this TreeNode's parent in the Tree.
    
    const CL_ObjectSequence& Children () const {return  _childPtrs;};
    // Return the Sequence of children of this node.

    CL_TreeNode<ItemType>* Child (long i) const;
    // Return a pointer to child $i$ of this node. If $i < 0$ or $i \ge n$
    // (where $n$ is the number of children of this node), NULL is returned.
    
    long IndexInParent () const
        { return _indexInParent; };
    // Return the index of this node among its siblings (e.g., 0 if it is
    // the leftmost child of its parent, $i$ if it has $i$ left siblings).
    
    long ChildCount () const
        { return _childPtrs.Size();};
    // Return the number of children of this node.

    bool IsLeaf () const
        {return ChildCount() == 0;};
    // Return TRUE if this node is a leaf. The method is equivalent to
    // testing if this node has {\tt ChildCount} equal to zero.
    

    ItemType& Content ();
    // Return the user-specified content of this node. Note that a
    // reference is returned, which can be modified by the user of
    // this class.

protected:
    friend class CL_Tree<ItemType>;

    // ------------------- Modification functions -------------------

    CL_TreeNode<ItemType>* AddChild (CL_TreeNodeLabel lbl, long
                                     leftSiblingIndex = 200000L);
    // Add a child to this node, immediately to the right of the child
    // with given index. Index of $-1$ specifies leftmost child.
    // Specifying a very larger index (specifically, anything larger
    // than the number of siblings) causes addition as the rightmost
    // child. The default value of the index is large enough, in most
    // situations, to mean addition as rightmost child.
    // If successful, return a pointer to the new child node; otherwise,
    // return NULL.

    
    CL_TreeNode<ItemType>* AddChild (CL_TreeNode<ItemType>* node,
                                     long leftSiblingIndex = 200000L);
    // Add the given node as a child of this node.



    CL_TreeNodeLabel        _label;
    CL_TreeNode<ItemType>*  _parent;
    CL_ObjectSequence       _childPtrs;      // Ptrs to nodes
    long                    _indexInParent;  // Child number of this
                                             // node
    CL_VoidPtr              _content;

    
};





#ifndef _no_cl_tree_typedefs_
#include "base/treedef.h"
#endif



#endif


