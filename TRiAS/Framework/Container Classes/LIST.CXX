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
//  List.cxx - Containers 2.0 implementation of ListContainer class
//
//	#HK930501: void Container::Insert() --> BOOL Container::Insert()
//
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CListContainer, CSeqContainer, 1)

#define new DEBUG_NEW

#if defined(_DEBUG)
void _DLLENTRY CListContainer :: AssertValid (void)
{
	ASSERT (m_pBase);
}
#endif

void _DLLENTRY CListContainer :: Serialize (CArchive &ar)
{
	CSeqContainer :: Serialize (ar);

WORD cCnt;
	
	if (ar.IsStoring()) {
	CListNode *pNode = m_pBase -> GetNext();
		
	// Kettenlänge feststellen
		cCnt = 0;
		while (pNode) {
			cCnt ++;
			pNode = pNode -> GetNext();
		}

	// Kette wegschreiben
		ar << cCnt;
		pNode = m_pBase -> GetNext();
		while (pNode) {
			ar << pNode;
			pNode = pNode -> GetNext();
		}
	} else {
	CListNode *pNode, *pLastNode = NULL;
		
	// Kettenlänge feststellen
		ar >> cCnt;
		for (uint cChain = 0; cChain < cCnt; cChain++) {
			ar >> pNode;
			if (cChain == 0) m_pBase -> SetNext(pNode);
			else {
				pLastNode -> SetNext (pNode);
				pNode -> SetPrev (pLastNode);
			}
			pLastNode = pNode;
		}
		m_pBase -> SetPrev (pLastNode);
	}
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(WIN32) && defined(_DEBUG)
void CListContainer :: AssertValid (void) const
{
	CSeqContainer::AssertValid();
	TX_ASSERT(m_pBase);
}
#endif

CNode * _DLLENTRY CListContainer :: DataStructure (void) const
{
// base is a ListNode * whose GetNext() points to the head of the list
// and whose GetPrev() points to the tail of the list. Note:
//		base -> GetNext() -> GetPrev() == 0 and != &base
//		base -> GetPrev() -> GetNext() == 0 and != &base
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_pBase -> GetNext ();
}

CNode * _DLLENTRY CListContainer :: LastNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_pBase -> GetPrev ();
}

_DLLENTRY CListContainer :: CListContainer (CONTFLAG fContFlags)
			  : CSeqContainer (fContFlags)
{
	m_pBase = new CListNode;
}

#if !defined(WIN32)
_DLLENTRY CListContainer :: CListContainer (CFreeStore &fs, CONTFLAG fContFlags)
			  : CSeqContainer (fs, fContFlags)
{
	m_pBase = new CListNode;
}
#endif

BOOL _DLLENTRY CListContainer :: Insert (FSHandle h, void * pobj)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pobj);
	TX_ASSERT (h);

CSyncThread Sync (this);
CListNode *newnode = new CListNode (h);

	if (!m_pBase -> GetNext ())
		m_pBase -> SetNext (newnode);

	if (m_pBase -> GetPrev ())
		m_pBase -> GetPrev () -> Append (newnode);

	m_pBase -> SetPrev (newnode);

return CSeqContainer :: Insert (h, pobj);
}

BOOL _DLLENTRY CListContainer :: Delete (CNode *node)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (node);

CSyncThread Sync (this);

	if (CSeqContainer :: Delete (node))	// Destroys object, count --
	{
		// remove node from list.
		if (node == m_pBase -> GetNext ())
			m_pBase -> SetNext (((CListNode *)node) -> GetNext());

		if (node == m_pBase -> GetPrev ())
			m_pBase -> SetPrev (((CListNode *)node) -> GetPrev());

		((CListNode *)node) -> Remove();
		delete (CListNode *)node;
		return true;
	}
	TX_ASSERT(false);
	return false;
}

_DLLENTRY CListContainer :: ~CListContainer (void)
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	if (m_pBase) delete m_pBase;
}
