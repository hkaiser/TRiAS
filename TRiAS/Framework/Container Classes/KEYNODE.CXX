//	Implementation of Glockenspiel Container release 2.0,
//
//	Glockenspiel's Framework for managing objects
//
//	Copyright 1990 Glockenspiel Limited
//
//	Version 2.0		July 27th 1990
//
//	Tab stops in this file are at	4 * n + 1
//
//  KeyNode.cxx - Implementation file for the KeyNode class
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CKeyNode, CNode, 1)

#define new DEBUG_NEW


#if defined(_DEBUG)
void _DLLENTRY CKeyNode :: AssertValid (void)
{
	ASSERT (m_pCont);
}
#endif


void _DLLENTRY CKeyNode :: Serialize (CArchive &ar)
{
	CNode :: Serialize (ar);
}	
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


_DLLENTRY CKeyNode :: CKeyNode (void)
{
	m_pCont = NULL;
}


_DLLENTRY CKeyNode :: CKeyNode (CKeyContainer & kc)
		    : m_pCont (&kc)
{
	// nothing else to do
}

_DLLENTRY CKeyNode :: CKeyNode (FSHandle h, CKeyContainer & kc)
		    : CNode (h), 
		      m_pCont (&kc)
{
	// nothing else to do
}

int _DLLENTRY CKeyNode :: Compare (void * key) const
{
//	ASSERT_VALID (this);
	TX_ASSERT (key);
	
#if !defined(WIN32)
CFreeStore *pfs = GetContainer ().GetFreeStore ();
#endif
pGetKeyFcn getkey = ((CKeyContainer &)GetContainer ()).m_pGetKeyFcn;
pKeyCmpFcn keycmp = ((CKeyContainer &)GetContainer ()).m_pKeyCmpFcn;

	TX_ASSERT(getkey);
	TX_ASSERT(keycmp);
	{
#if !defined(WIN32)
	CNakedLock nl (pfs, GetHandle());
#else
	CNakedLock nl (GetHandle());
#endif	
		if (nl.Valid ())
			return (*keycmp) (key, (*getkey)(nl.P()));
		else {
			TX_ASSERT(false);
			return 1;	// Should not happen.
		}
	}
}


CKeyNode * _DLLENTRY CKeyNode :: FindNext (void * key) const
{
//	ASSERT_VALID (this);
	TX_ASSERT (key);
	
CKeyNode *ret = Next ();

	if (ret && ret -> Compare (key) == 0 )
		return ret;
	else
		return 0;
}


CNode * _DLLENTRY CKeyNode :: CurrentAfterDelete (CNode * current)
{
	if (this != current)
		return current;
	else {
//
// #HK930720 ------------------------------------------------------------------
// das folgende Prozedere widerspricht der Intention, daß alle Elemente 
// eines Containers mit einer Anweisung wie dieser zu löschen sein 
// müssen: 	myNav.First(); while (myNav.Delete()) ;
//
//		// Get the key, and do a FindNext on it.
//		KeyContainer & keycont = (KeyContainer &) GetContainer ();
//		void * key = 0;
//		this -> Lock ();
//		{
//			NakedLock nl ( keycont . GetFreeStore (), GetHandle () );
//			if ( nl.Valid ())
//				key = (*( keycont . getkeyfcn )) ( nl.P ());
//		}
//		this -> Unlock ();
//		return FindNext ( key );
//
// Es wird daher nur der jeweils nächste Eintrag aktiv gesetzt: 
//
		return Next();
//		return Prev();		// #HK960128: Probleme mit FindNext, daher Prev()
	}
}

CKeyNode * _DLLENTRY CKeyNode :: FindPrev (void *key) const
{
//	ASSERT_VALID (this);
	TX_ASSERT (key);
	
CKeyNode *ret = Prev ();

	if (ret && ret -> Compare (key) == 0)
		return ret;
	else
		return 0;
}

// Eine Routine, die das erste Vorkommen eines Schlüssels in Bäumen findet,
// in denen Schlüssel nicht eindeutig sind
CKeyNode *CKeyNode :: FindFirst (void *key) const 
{
//	ASSERT_VALID (this);
	TX_ASSERT (key);

CKeyNode *locNode = Find(key);

	while (locNode) {
	CKeyNode *oldNode = locNode;

		locNode = locNode -> Prev();
		if (!locNode || locNode -> Compare(key) != 0)
		// erster entsprechender Eintrag in Container gefunden
			return oldNode;		
	}
	return 0;
}


