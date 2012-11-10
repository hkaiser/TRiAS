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
//  Seq.cxx - Containers 2.0 implementation of SeqContainer
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CSeqContainer, CContainer, 1);

#define new DEBUG_NEW


void _DLLENTRY CSeqContainer :: Serialize (CArchive &ar)
{
	CContainer :: Serialize (ar);
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_DLLENTRY CSeqContainer :: CSeqContainer (CONTFLAG fContFlags)
			 : CContainer (fContFlags)
{
	// Nothing to do
}

#if !defined(WIN32)
_DLLENTRY CSeqContainer :: CSeqContainer (CFreeStore &fs, CONTFLAG fContFlags)
			 : CContainer (fs, fContFlags)
{
	// Nothing to do
}
#endif

void _DLLENTRY CSeqContainer :: Every (pGenericFcn pfcn)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pfcn);

CSyncThread Sync (this);

	for (CSeqNode * nodeObj = (CSeqNode *) FirstNode ();
			nodeObj && nodeObj -> GetHandle ();
			nodeObj = nodeObj -> Next())
	{
		nodeObj -> Lock ();

#if !defined(WIN32)
	CNakedLock nl (GetFreeStore (), nodeObj -> GetHandle ());
#else
	CNakedLock nl (nodeObj -> GetHandle ());
#endif

		if (nl.Valid())
			(*pfcn) (nl.P());		// Call generic function.
		else
			TX_ASSERT(false);
		nodeObj -> Unlock ();
	}
}


BOOL _DLLENTRY CSeqContainer :: Every (pGenericDataFcn pfcn, void *pData)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pfcn);

CSyncThread Sync (this);
BOOL fRet;

	for (CSeqNode * nodeObj = (CSeqNode *) FirstNode ();
			nodeObj && nodeObj -> GetHandle ();
			nodeObj = nodeObj -> Next () )
	{
		nodeObj -> Lock();

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

return true;
}
