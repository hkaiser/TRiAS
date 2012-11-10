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
//  Keyed.cxx - Containers 2.0 KeyContainer classes implementation
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CKeyContainer, CContainer, 1)

#define new DEBUG_NEW


void _DLLENTRY CKeyContainer :: Serialize (CArchive &ar)
{
	CContainer :: Serialize (ar);	// nur weiterreichen
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG) && defined(WIN32)
void _DLLENTRY CKeyContainer :: AssertValid (void) const 
{
	CContainer::AssertValid();
	TX_ASSERT (m_pGetKeyFcn);
	TX_ASSERT (m_pKeyCmpFcn);
}
#endif


_DLLENTRY CKeyContainer :: CKeyContainer (CONTFLAG fContFlags)
			 : CContainer (fContFlags)
{
	m_pGetKeyFcn = NULL;
	m_pKeyCmpFcn = NULL;
}

_DLLENTRY CKeyContainer :: CKeyContainer (pGetKeyFcn keyfn, pKeyCmpFcn cmpfn, 
					  CONTFLAG fContFlags)
			 : CContainer (fContFlags)
{
	m_pGetKeyFcn = keyfn;
	m_pKeyCmpFcn = cmpfn;
}

#if !defined(WIN32)
_DLLENTRY CKeyContainer :: CKeyContainer (CFreeStore &fs, pGetKeyFcn keyfn, 
					  pKeyCmpFcn cmpfn, CONTFLAG fContFlags)
			 : CContainer (fs, fContFlags)
{
	m_pGetKeyFcn = keyfn;
	m_pKeyCmpFcn = cmpfn;
}
#endif
