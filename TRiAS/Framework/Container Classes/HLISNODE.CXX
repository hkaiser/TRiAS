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
//  HLisNode.cxx - Implementation file for the HLisNode class
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CHListNode, CKeyNode, 1)

#define new DEBUG_NEW


void _DLLENTRY CHListNode :: Serialize (CArchive &ar)
{
	CKeyNode :: Serialize (ar);	// nothing else
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


_DLLENTRY CHListNode :: CHListNode (void)
{
	m_pNext = m_pPrev = NULL;
}


_DLLENTRY CHListNode :: CHListNode (CHashTable & ht)
		      : CKeyNode (ht)
{
	m_pNext = m_pPrev = NULL;
}
	
 _DLLENTRY CHListNode :: CHListNode (FSHandle h, CHashTable & ht)
		       : CKeyNode (h, ht)
{
	m_pNext = m_pPrev = NULL;
}

CKeyNode *  _DLLENTRY CHListNode :: Find (void * key) const
{
	TX_ASSERT (key);
	
	for (const CHListNode * phl = this; phl; phl = phl -> m_pNext) {
		if (phl -> Compare (key) == 0)
			return (CKeyNode *)phl;
	}

return NULL;
}

CKeyNode *  _DLLENTRY CHListNode :: FindNext (void *key) const
{
	TX_ASSERT (key);
	
	for (CHListNode * phl = m_pNext; phl; phl = phl -> m_pNext) {
		if ( phl -> Compare (key) == 0 )
			return phl;
	}

return NULL;	// added: #HK930730
}

CKeyNode *  _DLLENTRY CHListNode :: FindPrev (void *key) const
{
	TX_ASSERT (key);
	
	for (CHListNode * phl = m_pPrev; phl; phl = phl -> m_pPrev) {
		if (phl -> Compare (key) == 0)
			return phl;
	}

return NULL;	// added: #HK930730
}

CKeyNode *  _DLLENTRY CHListNode :: Next (void) const
{
//	ASSERT_VALID ((CKeyNode *)this);
	
	if (m_pNext)
		return m_pNext;
	else {
	// Get the key of the current node, hash it and find the next node
	// in the buckets after the hashed value.
	CHashNode *buckets = ((CHashTable&)GetContainer()).m_pBuckets;
	pGetKeyFcn getkey = ((CHashTable &)GetContainer()).m_pGetKeyFcn;
	pHashFcn hashfcn = ((CHashTable &)GetContainer()).m_pHashFcn;
#if !defined(WIN32)
	CFreeStore *pfs = ((CHashTable &)GetContainer()).GetFreeStore ();
	CNakedLock nl (pfs, GetHandle());
#else
	CNakedLock nl (GetHandle());
#endif
		TX_ASSERT(buckets);
		TX_ASSERT(getkey);
		TX_ASSERT(hashfcn);

		if (!nl.Valid ()) {
			TX_ASSERT(false);
			return NULL;
		}

	uint hashval = (*hashfcn)((*getkey)(nl.P())) % buckets -> Size();

		while (++hashval < buckets -> Size()) {
			if (buckets -> GetNode (hashval))
				return buckets -> GetNode (hashval);
		}

		TX_ASSERT(hashval == buckets -> Size());
		
		return NULL;
	}
}

CKeyNode *  _DLLENTRY CHListNode :: Prev (void) const
{
//	ASSERT_VALID ((CKeyNode *)this);
	
	if (m_pPrev)
		return m_pPrev;
	else {
	CHashNode *buckets = ((CHashTable&)GetContainer()).m_pBuckets;
	
		TX_ASSERT(buckets);
		for (int i = 0; i < (int)buckets -> Size(); i++) {
			if (this == buckets -> GetNode(i)) {
				for (--i; i >= 0; i--) {
					if (buckets -> GetNode (i)) {
					// move to the end and return it.
					CHListNode * ret = buckets -> GetNode (i);
					
						while (ret -> m_pNext)
							ret = ret -> m_pNext;
						return ret;
					}
				}
				TX_ASSERT(i < 0);
				return NULL;
			}
		}
		TX_ASSERT(i == (int)buckets -> Size());
		return NULL;
	}
}

