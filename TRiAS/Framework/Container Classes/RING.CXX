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
//  Ring.cxx - Containers 2.0 Ring implementation
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_DYNAMIC (CRing, CNavigator)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_DLLENTRY CRing :: CRing (CSeqContainer &cont)
		 : CNavigator (cont)
{
}

_DLLENTRY CRing :: CRing (CRing &r)
		 : CNavigator (r)
{
	m_ulRank = r.m_ulRank;
}

BOOL _DLLENTRY CRing :: First (void)
{
	if (CNavigator :: First ())
	{
		m_ulRank = 0;
		return true;
	}
	return false;
}

BOOL _DLLENTRY CRing :: Last (void)
{
	if (CNavigator :: Last ()) {
		m_ulRank = GetContainer().Count () - 1;
		return true;
	}
	return false;
}

BOOL _DLLENTRY CRing :: Next (void)
{
	if (!m_pCurrentNode)		// in Reset position
		return First();
	else if (++m_ulRank < GetContainer().Count())	// Not off the end yet
	{
		m_pCurrentNode = ((CSeqNode *)m_pCurrentNode) -> Next ();
		return true;
	} else {	// off the end now
		Reset ();
		return false;
	}
}

BOOL _DLLENTRY CRing :: Prev (void)
{
	if (!m_pCurrentNode)		// in Reset position
		return Last ();
	else if (m_ulRank-- > 0) {	// Not off the end yet
		m_pCurrentNode = ((CSeqNode *)m_pCurrentNode) -> Prev();
		return true;
	} else {	// off the end now
		Reset ();
		return false;
	}
}

BOOL _DLLENTRY CRing :: Goto (ulong index)
{
	m_pCurrentNode = ((CSeqContainer &) GetContainer ()).FirstNode ();
	if (m_pCurrentNode && index < GetContainer().Count()) {
		m_pCurrentNode = ((CSeqNode *) m_pCurrentNode) -> Next (m_ulRank = index);
		return true;
	}
	Reset ();
	return false;
}

ulong _DLLENTRY CRing :: GetRank (void) const
{
	return m_ulRank;
}
