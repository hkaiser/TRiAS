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
//  Table.cxx - Containers 2.0 Table implementation
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_DYNAMIC (CTable, CNavigator)

#define new DEBUG_NEW
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_DLLENTRY CTable :: CTable (CKeyContainer & c)
		  : CNavigator (c)
{
}

_DLLENTRY CTable :: CTable (CTable & t)
		  : CNavigator (t) 
{
}

BOOL _DLLENTRY CTable :: Find (void * key)
{
	TX_ASSERT(key);

	m_pCurrentNode = ((CKeyContainer &) GetContainer()).DataStructure ();
	if (m_pCurrentNode)
		m_pCurrentNode = ((CKeyNode *)m_pCurrentNode) -> Find (key);

	return m_pCurrentNode != 0;
}

BOOL _DLLENTRY CTable :: FindNext (void * key)
{
	TX_ASSERT(key);

	if (m_pCurrentNode)
		m_pCurrentNode = ((CKeyNode *) m_pCurrentNode ) -> FindNext (key);

	return m_pCurrentNode != 0;
}

BOOL _DLLENTRY CTable :: FindPrev (void * key)
{
	TX_ASSERT(key);

	if (m_pCurrentNode)
		m_pCurrentNode = ((CKeyNode *) m_pCurrentNode) -> FindPrev (key);

	return m_pCurrentNode != 0;
}

BOOL _DLLENTRY CTable :: Next (void)
{
	if (m_pCurrentNode)
		m_pCurrentNode = ((CKeyNode *) m_pCurrentNode ) -> Next ();
	else
		First();

	return m_pCurrentNode != 0;
}

BOOL _DLLENTRY CTable :: Prev (void)
{
	if (m_pCurrentNode)
		m_pCurrentNode = ((CKeyNode *) m_pCurrentNode ) -> Prev ();
	else
		Last ();

	return m_pCurrentNode != 0;
}

// Gegenstück dazu für den zugehürigen Navigator ------------------------------
BOOL _DLLENTRY CTable :: FindFirst (void *key) 
{
	TX_ASSERT(key);

	m_pCurrentNode = ((CKeyContainer &)GetContainer()) . DataStructure ();
	if (m_pCurrentNode)
		m_pCurrentNode = ((CKeyNode *)m_pCurrentNode) -> FindFirst (key);

return m_pCurrentNode != 0;
}


BOOL _DLLENTRY CTable :: ReInsert (void *newKey, unsigned short KeySize) 
{
	TX_ASSERT(newKey);
	TX_ASSERT(KeySize > 0);

// wenn kein aktuelles Element existiert, dann wieder raus
	if (m_pCurrentNode == NULL) return FALSE;

// Container beauftragen, diesen Eintrag umzuhüngen
	m_pCurrentNode = ((CTree &)GetContainer()).ReInsert (
						(CBinaryNode *)m_pCurrentNode, 
						newKey, KeySize);
return m_pCurrentNode != 0;
}


