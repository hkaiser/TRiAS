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
//  Hash.cxx - Container 2.0 HashTable class implementation
//
//	#HK930501: void Container :: Insert() --> BOOL Container :: Insert()
//
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CHashTable, CKeyContainer, 1)

#define new DEBUG_NEW

void _DLLENTRY CHashTable :: Serialize (CArchive &ar)
{
	CKeyContainer :: Serialize (ar);
	
	if (ar.IsStoring()) {
		ar << m_pBuckets;
	} else {
		ar >> m_pBuckets;
		m_pBuckets -> SetContainer (this);
	}
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG) && defined(WIN32)
void _DLLENTRY CHashTable :: AssertValid (void) const 
{
	CKeyContainer::AssertValid();
	TX_ASSERT (m_pBuckets);
	TX_ASSERT (m_pHashFcn);
}
#endif


CNode * _DLLENTRY CHashTable :: DataStructure (void) const
{
//	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_pBuckets;
}


_DLLENTRY CHashTable :: CHashTable (CONTFLAG fContFlags)
		      : CKeyContainer (fContFlags)
{
	m_pHashFcn = NULL;
	m_pBuckets = NULL;
}


_DLLENTRY CHashTable :: CHashTable (pGetKeyFcn keyfn, pKeyCmpFcn cmpfn, pHashFcn phf, 
				    uint nobuckets, CONTFLAG fContFlags)
		      : CKeyContainer (keyfn, cmpfn, fContFlags)
{
	m_pHashFcn = phf;
	m_pBuckets = new CHashNode (*this, nobuckets);
}

#if !defined(WIN32)
_DLLENTRY CHashTable :: CHashTable (CFreeStore & fs, pGetKeyFcn keyfn, pKeyCmpFcn cmpfn,
				    pHashFcn phf, uint nobuckets, CONTFLAG fContFlags)
		      : CKeyContainer (fs, keyfn, cmpfn, fContFlags)
{
	m_pHashFcn = phf;
	m_pBuckets = new CHashNode (*this, nobuckets);
}
#endif

uint _DLLENTRY CHashTable :: Size (void) const
{
//	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_pBuckets -> Size ();
}


CNode * _DLLENTRY CHashTable :: FirstNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	for (uint i = 0; i < Size(); i++) {
		if (m_pBuckets -> GetNode (i))
			return m_pBuckets -> GetNode (i);
	}

	TX_ASSERT(i == Size());

return NULL;
}

CNode * _DLLENTRY CHashTable :: LastNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	for (int i = Size(); i-- > 0; ) {
	CHListNode * last = m_pBuckets -> GetNode (i);
	
		if (last) {
			while (last -> GetNext ())
				last = last -> GetNext ();
			return last;
		}
	}

	TX_ASSERT(i <= 0);

return NULL;
}

uint _DLLENTRY CHashTable :: EmptyBuckets (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);
uint count = 0;

	for (uint i = 0; i < m_pBuckets -> Size(); i++) {
		if (!m_pBuckets -> GetNode (i))
			count++;
	}
	
	TX_ASSERT(i == m_pBuckets -> Size());

return count;
}

uint _DLLENTRY CHashTable :: BucketsOfLength (uint len) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);
uint count = 0;

	for (uint i = 0; i < m_pBuckets -> Size(); i++) {
	uint listlen = 0;
	CHListNode *phl = m_pBuckets -> GetNode (i);
	
		while (phl) {
			listlen++;
			phl = phl -> GetNext();
		}

		if (listlen == len)
			count++;
	}

	TX_ASSERT(i == m_pBuckets -> Size());

return count;
}

uint _DLLENTRY CHashTable :: AverageCompares (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);
ulong avPerBuckX2 = 0;
uint nonEmptyBuckets = 0;

	for (uint i = 0; i < m_pBuckets -> Size(); i++) {
	uint listlen = 0;
	CHListNode * phl = m_pBuckets -> GetNode(i);
	
		while (phl) {
			listlen++;
			phl = phl -> GetNext();
		}

		if (listlen) {
			nonEmptyBuckets++;
			avPerBuckX2 += listlen + 1;
		}
	}

	TX_ASSERT(i == m_pBuckets -> Size());

return uint (avPerBuckX2 / (nonEmptyBuckets * 2));
}

BOOL _DLLENTRY CHashTable :: Insert (FSHandle h, void * pobj)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pobj);

CSyncThread Sync (this);
uint hashval = (*m_pHashFcn)((*m_pGetKeyFcn)(pobj)) % Size ();

	if (m_pBuckets -> GetNode (hashval)) {
	CHListNode * last = m_pBuckets -> GetNode (hashval);
	
		while (last -> GetNext ())
			last = last -> GetNext ();
		last -> Append (new CHListNode (h, *this));
	} else
		m_pBuckets -> SetNode (hashval, new CHListNode (h, *this));

return CKeyContainer :: Insert (h, pobj);		// updates the Count()
}

BOOL _DLLENTRY CHashTable :: Delete (CNode *node)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (node);

CSyncThread Sync (this);

	if (CKeyContainer :: Delete (node))		// destroys object, count--
	{
		// Remove the node from the list, if not at the start of a bucket.
		if (((CHListNode *) node ) -> GetPrev ())
			((CHListNode *) node) -> Remove();
		else {
			// must find which Bucket this node belongs to.
			for (uint i = 0; i < Size(); i++) {
				if (node == m_pBuckets -> GetNode (i)) {
					m_pBuckets -> SetNode (i, ((CHListNode *)node) -> GetNext());
					((CHListNode *)node) -> Remove();
					break;
				}
			}
		}
		delete (CHListNode *) node;
		return true;
	} else
		return false;
}

void _DLLENTRY CHashTable :: Every (pGenericFcn pfcn)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(pfcn);

CSyncThread Sync (this);

	for (uint i = 0; i < Size(); i++) {
		for (CHListNode * nodeObj = m_pBuckets -> GetNode (i);
				nodeObj;
				nodeObj = nodeObj -> GetNext ())
		{
			nodeObj -> Lock ();

#if !defined(WIN32)
		CNakedLock nl (GetFreeStore (), nodeObj -> GetHandle ());
#else
		CNakedLock nl (nodeObj -> GetHandle ());
#endif

			if (nl.Valid ())
				(*pfcn) (nl.P());	// Call generic function.
			else
				TX_ASSERT(false);

			nodeObj -> Unlock ();
		}
	}
	TX_ASSERT(i == Size());
}


BOOL _DLLENTRY CHashTable :: Every (pGenericDataFcn pfcn, void *pData)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(pfcn);

CSyncThread Sync (this);
BOOL fRet;

	for (uint i = 0; i < Size (); i++) {
		for (CHListNode * nodeObj = m_pBuckets -> GetNode (i);
				nodeObj;
				nodeObj = nodeObj -> GetNext ())
		{
			nodeObj -> Lock ();

#if !defined(WIN32)
		CNakedLock nl (GetFreeStore (), nodeObj -> GetHandle ());
#else
		CNakedLock nl (nodeObj -> GetHandle ());
#endif
			if (nl.Valid())
				fRet = (*pfcn) (nl.P(), pData);	// Call generic function.
			else
				TX_ASSERT(false);

			nodeObj -> Unlock ();

			if (!fRet) return false;
		}
	}
	TX_ASSERT(i == Size());
	
return true;
}


_DLLENTRY CHashTable :: ~CHashTable (void)
{
CSyncThread Sync (this);

	if (m_pBuckets) delete m_pBuckets;
}
