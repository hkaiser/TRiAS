// -*- C++ -*--
// amdb_idxstruct.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_idxstruct.cc,v 1.9 2000/03/15 00:24:19 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_idxstruct.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786)
#endif
// VCPORT_E

#include "amdb_idxstruct.h"
#include "gist.h"


// STL

// VCPORT_B
#ifdef WIN32
#include <algorithm>
#include <iostream>
#else
#include <algo.h> // for sort()
#endif
// VCPORT_E

///////////////////////////////////////////////////////////////////////////////
// amdb_idxstruct::splitNode - update idxstruct to reflect node split
//
// Description:
// 	- Update index structure to reflect regular node split. All
//	  rightChildren must exist in the nodeMap at that time (or are ignored).
//	- the children of rightSib get their parent entry updated
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_idxstruct::splitNode(
    shpid_t 	pageNo,
    shpid_t 	rightSib,
    Vector* 	rightChildren)
{
    // erase rightChildren from original node
    NodeStruct* origNode = (NodeStruct *) nodeMap[pageNo];
    origNode->nonce++; // we're changing this node
    sort(origNode->children.begin(), origNode->children.end());
    sort(rightChildren->begin(), rightChildren->end());
    NodeStruct::ChildVect diff(origNode->children.size() - rightChildren->size());
    set_difference(origNode->children.begin(), origNode->children.end(),
        rightChildren->begin(), rightChildren->end(), diff.begin());
    origNode->children = diff;

    // create new right sibling and insert it in parent
    NodeStruct* rightNode = new NodeStruct(rightSib, origNode->parent,
        origNode->level);
    nodeMap[rightSib] = (void *) rightNode;
    NodeStruct* parentNode = (NodeStruct *) nodeMap[origNode->parent];
    parentNode->children.push_back((void *) rightNode->pid);
    rightNode->children = *rightChildren; // copy rightChildren
    // adjust children's parent pointers
    NodeStruct::ChildVect::const_iterator it;
    for (it = rightNode->children.begin(); it != rightNode->children.end();
        it++) {

	// the children have a new parent
	NodeStruct* child = (NodeStruct *) nodeMap[(shpid_t) *it];
	if (child != NULL) {
	    child->parent = rightSib;
	}
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_idxstruct::splitRoot - update idxstruct to reflect root split
//
// Description:
//	- creates new left node as copy of root, calls splitNode() to 
// 	  handle split of new left node and put entry for right sib in root
///////////////////////////////////////////////////////////////////////////////

void
amdb_idxstruct::splitRoot(
    shpid_t 			left,
    shpid_t 			right,
    NodeStruct::ChildVect* 	rightChildren)
{
    // create left child as copy of root (at same level of old root)
    NodeStruct* rootNode = (NodeStruct *) nodeMap[rootNo];
    NodeStruct* leftNode = new NodeStruct(left, rootNo, rootNode->level);
    nodeMap[left] = (void *) leftNode;
    rootNode->nonce++; // we're changing the root
    rootNode->level++; // the root moved up one level
    leftNode->children = rootNode->children;
    rootNode->children.erase(rootNode->children.begin(),
        rootNode->children.end());
    rootNode->children.push_back((void *) left);

    // split left child
    splitNode(left, right, rightChildren);

    // adjust left node's children's parent pointers
    NodeStruct::ChildVect::const_iterator it;
    for (it = leftNode->children.begin(); it != leftNode->children.end();
        it++) {

	// the children have a new parent
	NodeStruct* child = (NodeStruct *) nodeMap[(shpid_t) *it];
	if (child != NULL) {
	    child->parent = left;
	}
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_idxstruct::relocateChild - update idxstruct to reflect new parent
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void 
amdb_idxstruct::relocateChild(
    shpid_t child,
    shpid_t oldParent,
    shpid_t newParent)
{
    NodeStruct* childNode = (NodeStruct *) nodeMap[child];
    childNode->parent = newParent; // point to new parent
    // remove from old parent
    NodeStruct* oldParentNode = (NodeStruct *) nodeMap[oldParent];
    oldParentNode->nonce++; // reflect update
    Vector::iterator pos = find(oldParentNode->children.begin(),
        oldParentNode->children.end(), (void *) child);
    oldParentNode->children.erase(pos);
    // attach to new parent
    NodeStruct* newParentNode = (NodeStruct *) nodeMap[newParent];
    newParentNode->nonce++; // reflect update
    newParentNode->children.push_back((void *) child);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_idxstruct::amdb_idxstruct - constructor
//
// Description:
//	- build idxstruct for 'index'
///////////////////////////////////////////////////////////////////////////////

amdb_idxstruct::amdb_idxstruct(
    gist* index)
{
    rootNo = index->getRootNo();

    // call getChildren() to find out level of root
    NodeStruct::ChildVect v;
    int level;
    index->getChildren(rootNo, level, &v);

    // create NodeStruct for root and record it
    NodeStruct* root = new NodeStruct(rootNo, rootNo, level);
    nodeMap[rootNo] = (void *) root;

    // build tree
    _buildStruct(index, rootNo, root);
}


///////////////////////////////////////////////////////////////////////////////
// amdb_idxstruct::_buildStruct - recursively descend tree and record entries
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void
amdb_idxstruct::_buildStruct(
    gist* index,
    shpid_t pageno,
    NodeStruct* node)
{
    int level;
    index->getChildren(pageno, level, &node->children);
    NodeStruct::ChildVect::const_iterator it;
    for (it = node->children.begin(); it != node->children.end(); it++) {
	shpid_t childNo = (shpid_t) *it;
	NodeStruct* child = new NodeStruct(childNo, pageno, level-1);
	    // level-1: getChildren() returns level of 'pageno'
	nodeMap[childNo] = (void *) child;
	if (level > 2) {
	    _buildStruct(index, childNo, child);
	}
    }
}


///////////////////////////////////////////////////////////////////////////////
// amdb_idxstruct::~amdb_idxstruct - destructor
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

amdb_idxstruct::~amdb_idxstruct()
{
    NodeMap::const_iterator it;
    for (it = nodeMap.begin(); it != nodeMap.end(); it++) {
        delete (NodeStruct *) (*it).second;
    }
    nodeMap.erase(nodeMap.begin(), nodeMap.end());
}

void
amdb_idxstruct::print(
    ostream& s)
{
    _printSub(s, rootNo);
}

void
amdb_idxstruct::_printSub(
    ostream& s,
    shpid_t pageno)
{
    NodeStruct* node = (NodeStruct *) nodeMap[pageno];
    // print node info
    s << "[" << pageno << "]\tparent: " << node->parent << endl;
    s << "\tchildren: ";
    NodeStruct::ChildVect::const_iterator it;
    for (it = node->children.begin(); it != node->children.end(); it++) {
	s << (shpid_t) *it << " ";
    }
    s << endl;

    // print children recursively
    for (it = node->children.begin(); it != node->children.end(); it++) {
	_printSub(s, (shpid_t) *it);
    }
}

ostream&
operator<<(
    ostream& 		s,
    amdb_idxstruct& 	strct)
{
    strct.print(s);
    return s;
}
