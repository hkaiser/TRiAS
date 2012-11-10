//	Header file for Glockenspiel FreeStore release 2.0
//
//	Glockenspiel's Framework for object storage
//
//	Copyright 1990 Glockenspiel Limited
//
//	Version 2.0		July 27th 1990
//
//	Tab stops in this file are at	4 * n + 1
//
//  fslink.hxx - This file declares the TaskList class to 
//	implement a linked list of TaskNodes.
//
//-------------------------------------------------------------------------
#ifndef FSLINK_HXX
#define FSLINK_HXX 1

#include <freestor.hxx>
#include <link.hxx>

class FS_Selection : public Node {
private:
#if !defined(__386__)
	unsigned	ds;
#endif // __386__
	pFreeStore 	pfreestore;

public:
#if !defined(__386__)
			FS_Selection (pFreeStore, unsigned ds);
#else
			FS_Selection (pFreeStore);
#endif // __386__
			~FS_Selection (void);

#if !defined(__386__)
	unsigned 	DS (void) { return ds ; }
#endif // __386__
	CFreeStore*	CurrentFS (void) { return pfreestore; }
};
typedef FS_Selection * pFS_Selection;

class TaskNode : public Node {
private:
	Linked_List SelectionList;
	int noselected;

public:
		TaskNode();

	void   		Add (FS_Selection*);
	FS_Selection*   Remove (CFreeStore*);
	FS_Selection*	Current (void)
		{ return (FS_Selection*)SelectionList. First(); }
	Bool   		InUse() { return noselected; }
};
typedef	TaskNode * pTaskNode;

class TaskList : public Linked_List {
public:
		TaskList (void);

static pTaskNode 	AddNewTask();
static pTaskNode 	FindTask();
static pTaskNode 	GetTask();
static void		UpdateTask();
};
typedef TaskList * pTaskList;

#endif

