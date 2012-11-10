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
//  HashNode.cxx - Implementation file for the HashNode class
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CHashNode, CKeyNode, 1)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

#if defined(_DEBUG)
void _DLLENTRY CHashNode :: AssertValid (void)
{
	ASSERT (m_ppBuckets);
}
#endif


void _DLLENTRY CHashNode :: Serialize (CArchive &ar)
{
	CKeyNode :: Serialize (ar);
	
WORD cCnt;

	if (ar.IsStoring()) {
		ar << (long)m_uiSize;		// Anzahl der Buckets
		for (uint i = 0; i < m_uiSize; i++) {
		CHListNode *pNode = m_ppBuckets[i];
		
		// Kettenlänge feststellen
			cCnt = 0;
			while (pNode) {
				cCnt ++;
				pNode = pNode -> GetNext();
			}

		// Kette wegschreiben
			ar << cCnt;
			pNode = m_ppBuckets[i];
			while (pNode) {
				ar << pNode;
				pNode = pNode -> GetNext();
			}
		}
	} else {
	long lInSize;
	
		ar >> lInSize;
		ReSize ((uint)lInSize);

	// Hashtabelle wieder einlesen
		for (uint i = 0; i < m_uiSize; i++) {
		CHListNode *pNode, *pLastNode = NULL;
		
		// Kettenlänge feststellen
			ar >> cCnt;
			for (uint cChain = 0; cChain < cCnt; cChain++) {
				ar >> pNode;
				if (cChain == 0) m_ppBuckets[i] = pNode;
				else {
					pLastNode -> SetNext (pNode);
					pNode -> SetPrev (pLastNode);
				}
				pLastNode = pNode;
			}
		}
	}
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_DLLENTRY CHashNode :: CHashNode (void)
{
	m_ppBuckets = NULL;
	m_uiSize = 0;
}


void CHashNode :: ReSize (uint nobuckets)
{
	TX_ASSERT(m_ppBuckets == NULL);
	TX_ASSERT(nobuckets > 0);

	m_ppBuckets = new CHListNode * [m_uiSize = nobuckets];
}

_DLLENTRY CHashNode :: CHashNode (CHashTable & ht, uint nobuckets)
		     : CKeyNode (ht)
{
	TX_ASSERT(nobuckets > 0);
	
	m_ppBuckets = new CHListNode * [m_uiSize = nobuckets];
	for (uint i = 0; i < nobuckets; i++)
		m_ppBuckets[i] = 0;
	
	TX_ASSERT(i == nobuckets);
}

CNode * _DLLENTRY CHashNode :: CurrentAfterDelete (CNode * current)
{
	return current;			// The hash node is never destroyed.
}

CKeyNode * _DLLENTRY CHashNode :: Find (void *key) const
{
//	TX_ASSERT_VALID(this);
	TX_ASSERT (key);
	
uint hashval = (*((CHashTable &)GetContainer()).m_pHashFcn) (key) % m_uiSize;

	if (m_ppBuckets [hashval])
		return m_ppBuckets[hashval] -> Find (key);
	else
		return NULL;
}

// HashNode::Next and HashNode::Prev are never used by HashTable
CKeyNode * _DLLENTRY CHashNode :: Next (void) const
{
	TX_ASSERT(false);
	return NULL;
}

CKeyNode * _DLLENTRY CHashNode :: Prev (void) const
{
	TX_ASSERT(false);
	return NULL;
}

_DLLENTRY CHashNode :: ~CHashNode (void)
{
//	ASSERT_VALID (this);
	
	delete [m_uiSize] m_ppBuckets;
}
