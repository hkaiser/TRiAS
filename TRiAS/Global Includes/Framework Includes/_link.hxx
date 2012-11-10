//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
#ifndef _LINK_HXX
#define _LINK_HXX
#include <cv_types.hxx>

class _TF_ENTRY32 CVLink
{
friend class CVLinked_List;
friend class CVTable;
	CVLink*			next;

protected:
	HANDLE 			key;
	void *			item;
public:
	CVLink (HANDLE h, void * i, CVLink *n);
	~CVLink (void);

	void*			Item()	{ 	return item; }
	HANDLE			Key()	{ 	return key; }
	CVLink*			Next()	{ 	return next; }
};

class _TF_ENTRY32 CVLinked_List
{
protected:
	CVLink*			first;
	CVLink*			current;
	CVLink*			prev;
	unsigned char	IsOrderLocked;

protected:
void *		_Find (HANDLE);
void *		_Find (HANDLE, void *);
void		MoveToFront();

public:
	CVLinked_List();

void		Insert (HANDLE, void *);

void *		Find (HANDLE);
void *		TaskFind (HANDLE);

void		Delete (void);
void		Delete (HANDLE);
void		Delete (HANDLE, void *);

	CVLink*	First() { prev = 0; return current = first; }
	CVLink*	Next (void)
	{ return ((prev = current) ? (current = current -> next) : current ); }
	void LockOrder (unsigned char tf) { IsOrderLocked = tf; }
};

class _TF_ENTRY32 CVTable: public CVLinked_List
{
public:
		CVTable (void) {}
	
	void Insert ( unsigned int i, const char * s) 
			{ CVLinked_List :: Insert ((HANDLE)i, (void*) s); }

int			FindItemDeep (const char *);
int			FindItemShallow (const char *);
};

#endif

