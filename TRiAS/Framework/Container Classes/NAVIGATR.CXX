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
//  Navigatr.cxx - Containers 2.0 Navigators implementation
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_DYNAMIC (CNavigator, CObject)

#define new DEBUG_NEW
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_DLLENTRY CNavigator :: CNavigator (CContainer & c)
		      : m_rCont (c)
{
	m_pCurrentNode = 0;
	m_rCont.Register (this);
}

_DLLENTRY CNavigator :: CNavigator (CNavigator & nav)
		      : m_rCont (nav.m_rCont)
{
	m_pCurrentNode = nav.m_pCurrentNode;
	m_rCont.Register (this);
}

BOOL _DLLENTRY CNavigator :: Valid (void) const
{
	return GetContainer().Count() > 0 && m_pCurrentNode != 0;
}

CContainer & CNavigator :: GetContainer (void) const
{
	return m_rCont;
}

FSHandle _DLLENTRY CNavigator :: GetHandle (void) const
{
	if (m_pCurrentNode)
		return m_pCurrentNode -> GetHandle ();

return NULL;
}

// It should be possible to delete all objs in the Container by:
//		mynav.First (); while ( mynav.Delete () );
BOOL _DLLENTRY CNavigator :: Delete (void)
{
	if (!m_pCurrentNode) return FALSE;

// Navigators get told that a deletion is taking place
// by the DeleteNotify function which should update currentNode if
// necessary. This happens before the Node is deleted in the Container.
return m_rCont.Delete (m_pCurrentNode);
}

void _DLLENTRY CNavigator :: DeleteNotify (CNode * pn)
{
	if (pn && m_pCurrentNode)
		m_pCurrentNode = pn -> CurrentAfterDelete (m_pCurrentNode);
}

void _DLLENTRY CNavigator :: Reset (void)
{
	m_pCurrentNode = NULL;
}

BOOL _DLLENTRY CNavigator :: First (void)
{
	m_pCurrentNode = GetContainer().FirstNode();
	
return m_pCurrentNode != 0;
}

BOOL _DLLENTRY CNavigator :: Last (void)
{
	m_pCurrentNode = GetContainer().LastNode();
	
return m_pCurrentNode != 0;
}
	
_DLLENTRY CNavigator :: ~CNavigator (void)
{
	m_rCont.Unregister (this);
}
