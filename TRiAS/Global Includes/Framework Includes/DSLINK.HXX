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
//  dslink.hxx - This file declares the DS_LinkedList class to implement 
//	a linked list of local heaps.
//
//-------------------------------------------------------------------------
#ifndef DSLINK_HXX
#define DSLINK_HXX 1

#include	"freestor.hxx"
#include	"link.hxx"

class	DSNode : public Node
{
private:
	unsigned	MaxAlloc;
	unsigned	Allocs;
public:
				DSNode();
	unsigned	GetDS() 
				{ return (unsigned)((((ulong)this) >> 16) & 0xFFFF);}
	unsigned	NbofAllocs() { return Allocs;}			
	unsigned 	SpaceAvail() { return MaxAlloc; }

	FSHandle	Alloc(size_t nBytes);
	void		Free(FSHandle);

				~DSNode();
	void *  	operator new    ( size_t, size_t);
	void *  	operator new    ( size_t);
	void		operator delete (void *);
};
typedef DSNode * pDSNode;



class DS_LinkedList : public Linked_List
{
public:
				DS_LinkedList ();
				~DS_LinkedList ();

};

typedef DS_LinkedList * pDS_LinkedList;
#endif

