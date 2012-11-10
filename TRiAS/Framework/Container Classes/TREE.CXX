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
//  Tree.cxx - Containers 2.0 Tree class implementation
//
//	#HK930501: void Container::Insert() --> BOOL Container::Insert()
//
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CTree, CKeyContainer, 1)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW


void _DLLENTRY CTree :: Serialize (CArchive &ar)
{
	CKeyContainer :: Serialize (ar);
	
	if (ar.IsStoring()) {
		ar << m_pRoot;
	} else {
		ar >> m_pRoot;
	}
}



#if defined(_DEBUG)
// Gültigkeit des Objektes testen --------------------------------------------
void _DLLENTRY CTree :: AssertValid (void)
{
	ASSERT_VALID ((CKeyContainer *)this);
	ASSERT (m_pRoot);
}
#endif
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(WIN32) && defined(_DEBUG)
void CTree :: AssertValid (void) const
{
	CKeyContainer::AssertValid();
	TX_ASSERT(m_pRoot);
}
#endif


CNode * _DLLENTRY CTree :: DataStructure (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_pRoot -> Left ();
}


_DLLENTRY CTree :: CTree (CONTFLAG fContFlags)
		 : CKeyContainer (fContFlags)
{
	m_pRoot = new CBinaryNode (*this);
}


_DLLENTRY CTree :: CTree (pGetKeyFcn getkey, pKeyCmpFcn cmpfcn, CONTFLAG fContFlags)
		 : CKeyContainer (getkey, cmpfcn, fContFlags)
{
	m_pRoot = new CBinaryNode (*this);
}

#if !defined(WIN32)
_DLLENTRY CTree :: CTree (CFreeStore &fs, pGetKeyFcn getkey, pKeyCmpFcn cmpfcn, CONTFLAG fContFlags)
		 : CKeyContainer (fs, getkey, cmpfcn, fContFlags)
{
	m_pRoot = new CBinaryNode (*this);
}
#endif

CNode * _DLLENTRY CTree :: FirstNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	if (Count ())
		return m_pRoot -> LeftMost ();
	else
		return 0;
}

CNode * _DLLENTRY CTree :: LastNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	if (Count ())
		return m_pRoot -> Left() -> RightMost();
	else
		return 0;
}

BOOL _DLLENTRY CTree :: Insert (FSHandle h, void * pobj)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pobj);
	TX_ASSERT (h);

CSyncThread Sync (this);

	if (Count()) {
	void * key = (*m_pGetKeyFcn) (pobj);

		TX_ASSERT(key);

		for (CBinaryNode * look = m_pRoot -> Left(); look; ) {
		int cmp = look -> Compare (key);                     
		
			if (cmp == 0 && ContFlags() & CFUniqueKey) {
				return FALSE;		// doppelter Key
			} else if (cmp >= 0) {		// key > this
				if (look -> Right ())
					look = look -> Right ();
				else {
					look -> SetRight (new CBinaryNode (h, *this, look));
					break;
				}
			} else if (cmp < 0) {	// key < this
				if (look -> Left ())
					look = look -> Left ();
				else {
					look -> SetLeft (new CBinaryNode (h, *this, look));
					break;
				}
			}
		}
			
	} else
		m_pRoot -> SetLeft (new CBinaryNode (h, *this, m_pRoot));

return CKeyContainer :: Insert (h, pobj);	// updates the Count (), etc...
}

BOOL _DLLENTRY CTree :: Delete (CNode *node)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (node);

CSyncThread Sync (this);

	if (CKeyContainer :: Delete (node)) {	// destroys object, count--
	CBinaryNode * bnode = (CBinaryNode *) node;
	
		if (!bnode -> Left ())
			bnode -> Parent () -> Graft (bnode, bnode -> Right ());
		else if (!bnode -> Right ())
			bnode -> Parent () -> Graft ( bnode, bnode -> Left ());
		else {
		CBinaryNode * righty = bnode -> Left () -> RightMost ();
		
			if ( righty != bnode -> Left ()) {
				righty -> Parent () -> SetRight (righty -> Left ());
				if (righty -> Left ())
					righty -> Left () -> SetParent (righty -> Parent ());

				righty -> SetLeft (bnode -> Left ());
				bnode -> Left () -> SetParent (righty);
			}

			righty -> SetRight (bnode -> Right ());
			bnode -> Right () -> SetParent (righty);

			bnode -> Parent () -> Graft (bnode, righty);
		}
		delete bnode;
		return TRUE;
	} else
		return FALSE;
}

void _DLLENTRY CTree :: Every (pGenericFcn pfcn)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(pfcn);

CSyncThread Sync (this);

	if (Count())
		InOrder ((CBinaryNode *) DataStructure (), pfcn);
}

BOOL _DLLENTRY CTree :: Every (pGenericDataFcn pfcn, void *pData)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(pfcn);

CSyncThread Sync (this);

	if (Count()) return InOrder ((CBinaryNode *)DataStructure(), pfcn, pData);

return FALSE;
}

void _DLLENTRY CTree :: PreOrder (CBinaryNode *bnode, pGenericFcn pfcn)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pfcn);
	TX_ASSERT (bnode);

CSyncThread Sync (this);

#if defined(RECURSION)
	// The recursive solution is clean and simple
	{
		bnode -> Lock ();

#if !defined(WIN32)
	CNakedLock nl (GetFreeStore(), bnode -> GetHandle ());
#else
	CNakedLock nl (bnode -> GetHandle ());
#endif	
		if ( nl.Valid ())
			(*pfcn) (nl.P());			// Call generic function.
		bnode -> Unlock ();
	}

	if (bnode -> Left ())
		InOrder ( bnode -> Left (), pfcn);

	if (bnode -> Right ())
		InOrder (bnode -> Right (), pfcn);
#else
	// The non-recursive solution is nasty and complicated
CBinaryNode * pnode = bnode;

	while (TRUE) {
		{
			pnode -> Lock ();

		CNakedLock nl ( GetFreeStore (), pnode -> GetHandle () );
		
			if (nl.Valid ())
				(*pfcn) (nl.P());			// Call generic function.
			pnode -> Unlock ();
		}
		if ( pnode -> Left ())
			pnode = pnode -> Left ();
		else if ( pnode -> Right ())
			pnode = pnode -> Right ();
		else {
			while (pnode != bnode &&
			       (pnode -> Parent () -> Left () != pnode ||
				!pnode -> Parent () -> Right ())) 
			{
				pnode = pnode -> Parent ();
			}

			if (pnode != bnode)
				pnode = pnode -> Parent () -> Right ();
			else
				return;
		}
	}
#endif
}

void _DLLENTRY CTree :: InOrder (CBinaryNode *bnode, pGenericFcn pfcn)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pfcn);
	TX_ASSERT (bnode);

CSyncThread Sync (this);

#if defined(RECURSION)
	// The recursive solution is clean and simple
	if ( bnode -> Left ())
		InOrder ( bnode -> Left (), pfcn );

	{
		bnode -> Lock ();

#if !defined(WIN32)
	CNakedLock nl (GetFreeStore (), bnode -> GetHandle ());
#else
	CNakedLock nl (bnode -> GetHandle () );
#endif
	
		if (nl.Valid())
			(*pfcn)(nl.P());			// Call generic function.
		else
			TX_ASSERT(false);
		bnode -> Unlock ();
	}

	if ( bnode -> Right ())
		InOrder ( bnode -> Right (), pfcn );
#else
CBinaryNode * pnode = bnode -> LeftMost ();

	while (TRUE) {
		{
			pnode -> Lock ();

		CNakedLock nl ( GetFreeStore (), pnode -> GetHandle () );
		
			if (nl.Valid())
				(*pfcn)(nl.P());			// Call generic function.
			else
				TX_ASSERT(false);
			pnode -> Unlock();
		}

		if (pnode -> Right ())
			pnode = pnode -> Right () -> LeftMost ();

		else
		{
			while ( pnode -> Parent () -> Left () != pnode )
				if ( pnode == bnode )
					return;
				else
					pnode = pnode -> Parent ();

			pnode = pnode -> Parent ();
		}
	}
#endif
}


BOOL _DLLENTRY CTree :: InOrder (CBinaryNode *bnode, pGenericDataFcn pfcn, void *pData)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pfcn);
	TX_ASSERT (bnode);

CSyncThread Sync (this);

	// The recursive solution is clean and simple
	if (bnode -> Left ()) {
		if (!InOrder (bnode -> Left(), pfcn, pData))
			return FALSE;
	}

	{
		bnode -> Lock ();

#if !defined(WIN32)
	CNakedLock nl (GetFreeStore (), bnode -> GetHandle());
#else
	CNakedLock nl (bnode -> GetHandle());
#endif
	BOOL fRet;
		
		if (nl.Valid ())
			fRet = (*pfcn) (nl.P(), pData);			// Call generic function.
		else {
			TX_ASSERT(false);
			fRet = false;
		}

		bnode -> Unlock ();
		if (!fRet) return FALSE;
	}

	if (bnode -> Right ()) {
		if (!InOrder (bnode -> Right (), pfcn, pData))
			return FALSE;
	}

return TRUE;
}

void _DLLENTRY CTree :: PostOrder (CBinaryNode * bnode, pGenericFcn pfcn )
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pfcn);
	TX_ASSERT (bnode);

CSyncThread Sync (this);

#if defined(RECURSION)
	// The recursive solution is clean and simple
	if ( bnode -> Left ())
		InOrder ( bnode -> Left (), pfcn );

	if ( bnode -> Right ())
		InOrder ( bnode -> Right (), pfcn );

	{
		bnode -> Lock ();
		
#if !defined(WIN32)
	CNakedLock nl (GetFreeStore(), bnode -> GetHandle());
#else
	CNakedLock nl (bnode -> GetHandle());
#endif	
		if ( nl.Valid ())
			(*pfcn) ( nl.P() );			// Call generic function.
		else
			TX_ASSERT(false);

		bnode -> Unlock ();
	}
#else
CBinaryNode * pnode = bnode -> LeftMost ();

	do {
		{
			pnode -> Lock ();

		CNakedLock nl (GetFreeStore (), pnode -> GetHandle ());

			if (nl.Valid())
				(*pfcn) (nl.P());	// Call generic function.
			else
				TX_ASSERT(false);
			pnode -> Unlock ();
		}

		if ( pnode == bnode )
			pnode = 0;
		else if ( pnode -> Parent () -> Right () == pnode ||
			  	pnode -> Parent () -> Right () == 0 )
			pnode = pnode -> Parent ();
		else
			pnode = pnode -> Parent () -> Right () -> LeftMostOrRight ();

	} while ( pnode );
#endif
}

static ulong Cost (CBinaryNode * bnode, uint depth )
{
	if (bnode == 0)	return 0;

	depth ++;

return depth + Cost (bnode -> Left (), depth) +
	       Cost (bnode -> Right (), depth);
}

uint _DLLENTRY CTree :: AverageCompares (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return uint (Cost (m_pRoot -> Left (), 0) / Count ());
}

_DLLENTRY CTree :: ~CTree (void)
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	delete m_pRoot;
}

// weitere Memberdefinitionen für Tree ----------------------------------------
// Ein Element eines Baumes an eine andere Stelle hängen ----------------------
CNode * _DLLENTRY CTree :: ReInsert (CBinaryNode *bnode, void *newKey, unsigned short KeySize) 
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(bnode);
	TX_ASSERT(newKey);
	TX_ASSERT(KeySize > 0);

CSyncThread Sync (this);

// Element an der alten Stelle beseitigen
	if (!bnode -> Left())
		bnode -> Parent() -> Graft (bnode, bnode -> Right());
	else if (!bnode -> Right())
		bnode -> Parent() -> Graft (bnode, bnode -> Left());
	else {
	CBinaryNode *righty = bnode -> Left() -> RightMost();

		if (righty != bnode -> Left()) {
			righty -> Parent() -> SetRight (righty -> Left());
			if (righty -> Left())
				righty -> Left() -> SetParent (righty -> Parent());
			righty -> SetLeft (bnode -> Left());
			bnode -> Left() -> SetParent (righty);
		}
		righty -> SetRight (bnode -> Right());
		bnode -> Right() -> SetParent (righty);
		bnode -> Parent() -> Graft (bnode, righty);
	}

FSHandle h = bnode -> GetHandle();
CBinaryNode *newCurrNode = NULL;

// Schlüssel im Node austauschen
	{
#if !defined(WIN32)
	CNakedLock nl (GetFreeStore(), h);
#else
	CNakedLock nl (h);
#endif
		if (nl.Valid ()) {
		char *dest = (char *)(*m_pGetKeyFcn)(nl.P());
		char *src = (char *)newKey;

			while (KeySize--) 
				*dest++ = *src++;
		} else {
			TX_ASSERT(false);
			if (bnode) delete bnode;
			return NULL;
		}
	}

// neues Element wieder reinhängen
	if (Count() > 1) {
	// nicht erstes Element
		for (CBinaryNode *look = m_pRoot -> Left(); look; ) {
		int cmp = look -> Compare (newKey);

			if (cmp >= 0) {		// key > this
				if (look -> Right())
					look = look -> Right();
				else {
					newCurrNode = new CBinaryNode (h, *this, look);
					look -> SetRight (newCurrNode);
					break;
				}
			} else if (cmp < 0) {
				if (look -> Left())
					look = look -> Left();
				else {
					newCurrNode = new CBinaryNode (h, *this, look);
					look -> SetLeft (newCurrNode);
					break;
				}
			}
		}
	} else {
	// das erste Element dieses Baumes
		newCurrNode = new CBinaryNode (h, *this, m_pRoot);
		m_pRoot -> SetLeft (newCurrNode);
	}

// alten Node freigeben
	if (bnode) delete bnode;
	
return (CNode *)newCurrNode;
}


