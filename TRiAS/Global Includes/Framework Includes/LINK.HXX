//	Header file for Computer Associates FreeStore release 2.0
//
//	Implementation of Computer Associates FreeStore release 3.1
//
//	Computer Associates Framework for object storage
//
//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//  link.hxx - This file declares the Linked_List class to implement a 
//	general reusable linked list.
//
//-------------------------------------------------------------------------

#ifndef _LINK_HXX
#define _LINK_HXX

typedef class Node *pNode;

class Node
{
friend class Linked_List;
	pNode			next;
protected:
	long 			key;
public:
					Node();
					~Node();

	void *operator new ( unsigned );
	void operator delete ( void * );
};

class Linked_List
{
protected:
	pNode			first;
	pNode			current;
	pNode			prev;
public:
					Linked_List();
	pNode			First() { prev = 0; return current = first; }
	pNode			Next() 
		{ return ((prev = current) ? 
					(current = current -> next) 
					: current ); }

	void			Insert ( long, Node *);

	Node *			Find(long);
	Node *			FindNoMTF(long);

	Node *			Remove(long);
	Node *			Remove();

	void			MoveToFront();

	void *operator new( unsigned );
	void operator delete( void * );
};

#endif
