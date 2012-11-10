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
//  Node.cxx - Containers 2.0 implementation of Node classes
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CNode, CObject, 1)
IMPLEMENT_SERIAL (CSeqNode, CNode, 1)
IMPLEMENT_SERIAL (CArrayNode, CSeqNode, 1)
IMPLEMENT_SERIAL (CListNode, CSeqNode, 1)

#define new DEBUG_NEW
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_DLLENTRY CNode :: CNode (void)
{
	m_fsHandle = 0;
	m_iLocks = 0;
}

_DLLENTRY CNode :: CNode (FSHandle h)
{
	m_fsHandle = h;
	m_iLocks = 0;
}

CNode & _DLLENTRY CNode :: operator = (CNode &node)
{
	if (&node == this) return *this;

	m_fsHandle = node.m_fsHandle;
	m_iLocks = node.m_iLocks;
	
	node.m_fsHandle = 0;
	node.m_iLocks = 0;
	
// alle aktiven Navigatoren fragen, ob sie auf diesen Node zeigen
// ...

return *this;
}

_DLLENTRY CSeqNode :: CSeqNode (void)
{
	// Nothing to do
}

_DLLENTRY CSeqNode :: CSeqNode (FSHandle h)
		    : CNode (h)
{
	// Nothing to do
}

_DLLENTRY CArrayNode :: CArrayNode (void)
{
	// Nothing to do
}

_DLLENTRY CArrayNode :: CArrayNode (FSHandle h)
		      : CSeqNode (h)
{
	// Nothing to do
}

CSeqNode * _DLLENTRY CArrayNode :: Next (ulong nodes) const
{
#if defined(WIN32)
	return (CSeqNode *) (this + nodes);
#else
	return (CSeqNode *) ((CArrayNode __huge *)this + nodes);
#endif // WIN32
}

CSeqNode * _DLLENTRY CArrayNode :: Prev (ulong nodes) const
{
#if defined(WIN32)
	return (CSeqNode *) (this - nodes);
#else
	return (CSeqNode *) ((CArrayNode __huge *)this - nodes);
#endif
}

CNode * _DLLENTRY CArrayNode :: CurrentAfterDelete (CNode *current)
{
#if defined(WIN32)
	if (current > this)
		return current - 1;
	else
		return this;
#else
	if ((CNode __huge *)current > (CArrayNode __huge *)this)
		return ((CNode __huge *)current) - 1;
	else
		return this;
#endif
}

_DLLENTRY CListNode :: CListNode (void)
{
	m_pNext = m_pPrev = NULL;
}

_DLLENTRY CListNode :: CListNode (FSHandle h)
		     : CSeqNode (h)
{
	m_pNext = m_pPrev = NULL;
}

CSeqNode * _DLLENTRY CListNode :: Next (ulong nodes) const
{
CListNode * ret = m_pNext;

	while (--nodes > 0 && ret)
		ret = ret -> m_pNext;

return ret;
}

CListNode * _DLLENTRY CListNode :: GetNext (void) const
{
	return m_pNext;
}


CSeqNode * _DLLENTRY CListNode :: Prev (ulong nodes) const
{
CListNode * ret = m_pPrev;

	while (--nodes > 0 && ret)
		ret = ret -> m_pPrev;

return ret;
}

CListNode * _DLLENTRY CListNode :: GetPrev (void) const
{
	return m_pPrev;
}

CNode * _DLLENTRY CListNode :: CurrentAfterDelete (CNode *current)
{
	if (current == this)
		return m_pNext;
	else
		return current;		// BUGBUG: return this; #HK960711
}


// Serialisation Support -----------------------------------------------------
/*
void _DLLENTRY CNode :: Serialize (CArchive &ar)
{
	CObject :: Serialize (ar);

	if (ar.IsStoring ()) {
	CNakedLock nl (NULL, GetHandle());
	
		ASSERT (nl.Valid());
		ar << (CObject *)nl.P();
	} else {
	CObject *pObj;
	
		ar >> pObj;			// Objekt selbst holen
		SetHandle ((FSHandle)pObj);
	}
}

void _DLLENTRY CSeqNode :: Serialize (CArchive &ar)
{
	CNode :: Serialize (ar);
}

void _DLLENTRY CArrayNode :: Serialize (CArchive &ar)
{
	CSeqNode :: Serialize (ar);
}

void _DLLENTRY CListNode :: Serialize (CArchive &ar)
{
	CSeqNode :: Serialize (ar);
}

*/
