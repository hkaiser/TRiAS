// amdb_idxstruct.h						-*- c++ -*--
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_idxstruct.h,v 1.10 1998/12/11 05:04:03 marcel Exp $

#ifndef AMDB_IDXSTRUCT_H
#define AMDB_IDXSTRUCT_H

#ifdef __GNUG__
#pragma interface "amdb_idxstruct.h"
#endif

#include "gist_defs.h"
#include "amdb_defs.h" // for Vector

class gist;


class amdb_idxstruct {

public:

    class NodeStruct {
    public:

	shpid_t pid;
	int nonce; // keeps track of the number of updates to this node
	shpid_t parent;
	int level; // leaf level: 1

	// typedef vector<shpid_t> ChildVect
	typedef Vector ChildVect;
	ChildVect children; // contains child page #'s

	NodeStruct(shpid_t pid, shpid_t parent, int level) :
	    pid(pid), nonce(0), parent(parent), level(level), children() {}
    };

    typedef NodeStruct::ChildVect::iterator ChildIterator; // for convenience

    // typedef map<shpid_t, NodeStruct *, less<shpid_t> >  NodeMap;
    typedef Map NodeMap;
    NodeMap nodeMap; // map of all existing nodes
    shpid_t rootNo; // page # of root

    // Update index structure to reflect regular node split. All rightChildren
    // must exist in the nodeMap at that time (or are ignored). The new node
    // is registered with rightParent, and the children of rightSib have their parent
    // entry updated.
    void splitNode(
        shpid_t node,
	shpid_t rightSib,
	NodeStruct::ChildVect* rightChildren);

    // Update index structure to reflect root split
    void splitRoot(
        shpid_t left,
        shpid_t right,
	NodeStruct::ChildVect* rightChildren);

    // Update index structure to reflect actual parent of a node
    void relocateChild(
        shpid_t child,
        shpid_t oldParent,
        shpid_t newParent);

    // Increment the node's nonce to reflect a change of its content
    void updateNode(
        shpid_t node)
    {
        ((NodeStruct *) nodeMap[node])->nonce++;
    }

    amdb_idxstruct(gist* index);
    ~amdb_idxstruct();

    friend ostream& operator<<(ostream& s, amdb_idxstruct& strct);
    void print(ostream& s);

private: 

    void _buildStruct(
	gist* index,
	shpid_t pageno,
	NodeStruct* node);

    void _printSub(ostream& s, shpid_t pageno);

};

#endif


