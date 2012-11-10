/* $Header:   G:/cv.win/pvcs/commonvu/src/_link.cxv   1.4   17 Oct 1991 13:18:48   RONAN  $
 *
 *	_l i n k . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Modification log:
 *
 *	0.1	ferg	26sep88	Changed Link and pLink to CVLink and pCVLink to
 *						avoid name clashes in container. (not logged in code
 *						too many occurences).
 *	0.2 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs 		20feb90 Implementation of Move-To-Front Find.
 *						This version of Find moves the found item to the top
 *						of the list. This gives an efficiency gain where 
 *						operations on the same items tend to occur in sequence
 *						ie Windows messages.
 *						Greater search efficiency could be gained by
 *						moving found item in front of current front item 
 *						resulting in the list forming in order of most recently
 *						used, however worst case times are much worse.
 *						See Dr. Dobbs Journal February 1990.
 *
 *						Also Insert doesn't need to insert in order as the
 *						ordering has no meaning in Windows.
 *						i.e The fact that handle h1 is greater than handle
 *						h2 says nothing about their relationship to each other.
 */

#include "tfrmpre.hxx"

class		CVLink;

typedef	CVLink	 *	pCVLink;
// typedef	unsigned int	HANDLE;
typedef	void	 *	npvoid;

#include	<_Link.hxx>

#if !defined(_DLLENTRY) && defined(__BCPLUSPLUS__)
#define _DLLENTRY __export
#else
//#undef _DLLENTRY
//#define _DLLENTRY
#endif

#if !defined(WIN32)
extern "C" int PASCAL_FUNC lstrcmpi (const char*, const char *);
#endif

_DLLENTRY CVLink :: CVLink(HANDLE k, void *data, CVLink * n)
{
	key = k;
	item = data;
	next = n;
}

_DLLENTRY CVLink :: ~CVLink() 
{ }


_DLLENTRY CVLinked_List :: CVLinked_List ()
{
	current = prev = first = 0;
	IsOrderLocked = 0;
}

void _DLLENTRY CVLinked_List :: Insert ( HANDLE k, void * data)
{
	CVLink * pcv = new CVLink(k, data, first);
	current = first = pcv;
	prev  = 0;
}

void  * _DLLENTRY CVLinked_List :: Find ( HANDLE k )
{
	if (k)
		{
		for (First(); current && (current -> key != k); Next());

		if (current && (!IsOrderLocked))
		{
			if (prev)
			{
				prev->next = current->next;
				current->next = first;
				first = current;
				prev = 0;
			}
		}
		return ( current ? current -> item : 0);
		}
	else
		return 0;
}

void * _DLLENTRY CVLinked_List :: _Find (HANDLE k)
{
	for (First(); current && (current -> key != k); Next())
		;

return ( current ? current -> item : 0);
}

// #HK950321 ------------------------------------------------------------------
void * _DLLENTRY CVLinked_List :: _Find (HANDLE k, void *pItem)
{
	for (First(); 
	     current && (current -> key != k) && (current -> item != pItem); 
	     Next())
	{
		;
	}

return (current ? current -> item : 0);
}

void*	_DLLENTRY CVLinked_List ::  TaskFind	(HANDLE k)		// * 1.2 start *
{
	for (First(); current && (current -> key != k); Next())
		;

	return ( current ? current -> item : 0);
}


void _DLLENTRY CVLinked_List :: Delete (void)
{
CVLink *del = current;

	if (del) {
		if (prev)
			current = prev -> next = del -> next;
		else
			current = first = del -> next;
		delete del;
	}
}

void _DLLENTRY CVLinked_List :: Delete (HANDLE k)
{
	_Find (k);
	Delete();
	return;
}

// #HK950321 ------------------------------------------------------------------
void _DLLENTRY CVLinked_List :: Delete (HANDLE k, void *pItem)
{
	_Find (k, pItem);
	Delete();
}

void _DLLENTRY CVLinked_List :: MoveToFront()
{
		if (current && (!IsOrderLocked))
		{
			if (prev)
			{
				prev->next = current->next;
				current->next = first;
				first = current;
				prev = 0;
			}
		}
}

int _DLLENTRY CVTable :: FindItemShallow (const char* s)
{
	if (s)
		{
		for (First(); current && (current -> item != (void*)s); Next());
 		MoveToFront();
		return ( current ? (int)(current -> key) : 0);
		}
	else
		return 0;
}


int  _DLLENTRY CVTable :: FindItemDeep( const char* s)
{
	if (s)
		{
		for (First(); current && (lstrcmpi((char*)current -> item,(char*)s) != 0); Next());

		MoveToFront();
		return ( current ? (int)(current -> key) : 0);
		}
	else
		return 0;
}


