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
//  Lock.cxx - Containers 2.0 Lock implementation
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_DYNAMIC (CLock, CObject)
IMPLEMENT_DYNAMIC (CCreator, CLock);

#define new DEBUG_NEW
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(WIN32) && defined(_DEBUG)
void CLock :: AssertValid (void) const
{
}
#endif


void  _DLLENTRY CLock :: lock (void)
{
//	TX_ASSERT_VALID_CONT(this);

	if (m_pNode) m_pNode -> Lock ();
#if !defined(WIN32)
	if (m_pFS && m_fsHandle)
		m_pObj = m_pFS -> Lock (m_fsHandle);
	else
#endif
        	m_pObj = (void *) m_fsHandle;
}

void _DLLENTRY CLock :: Unlock ()
{
//	TX_ASSERT_VALID_CONT(this);

	if (m_pNode) m_pNode -> Unlock ();
#if !defined(WIN32)
	if (m_pFS && m_pObj)
		m_pFS -> Unlock (m_fsHandle);
#endif
	m_pObj = 0;
}


_DLLENTRY CLock :: CLock (CNavigator & nav)
{
#if !defined(WIN32)
	m_pFS = nav.GetContainer().GetFreeStore();
#endif
	m_fsHandle = nav.GetHandle();
	m_pNode = nav.m_pCurrentNode;

	lock ();
}

#if defined(WIN32)
_DLLENTRY CLock :: CLock (FSHandle h)
#else
_DLLENTRY CLock :: CLock (CFreeStore * pf, FSHandle h)
#endif
{
#if !defined(WIN32)
	m_pFS = pf;
#endif
	m_fsHandle = h;
	m_pNode = 0;
	lock ();
}

_DLLENTRY CLock :: ~CLock (void)
{
	TX_ASSERT_VALID_CONT(this);

	Unlock ();
}

#if defined(WIN32)
_DLLENTRY CNakedLock :: CNakedLock (FSHandle hobj)
		      : CLock (hobj)
#else
_DLLENTRY CNakedLock :: CNakedLock (CFreeStore * pfs, FSHandle hobj)
		      : CLock (pfs, hobj)
#endif
{
}

#if defined(WIN32) && defined(_DEBUG)
void CCreator :: AssertValid (void) const
{
	CLock::AssertValid();
}
#endif

void _DLLENTRY CCreator :: Insert (void)
{
	TX_ASSERT_VALID_CONT(this);

CContainer :: CSyncThread Sync (&m_rCont);

#if defined(_DEBUG)
	if (!m_rCont.Insert (GetHandle(), P()))
		TX_ASSERT(false);
#else
	m_rCont.Insert (GetHandle(), P());
#endif // _DEBUG

	Unlock();
	GetHandle() = 0;	    // avoids double insertion
}

void * _DLLENTRY CCreator :: Alloc (size_t size)
{
	TX_ASSERT_VALID_CONT(this);

CContainer :: CSyncThread Sync (&m_rCont);

	if (GetHandle()) Insert();

#if !defined(WIN32)
	if (GetFreeStore())
    	GetHandle() = GetFreeStore() -> Alloc (size);
	else
#endif
	{
		try {
			GetHandle() = (FSHandle) new char [size];
		} catch (...) {
			;
		}
	}	
	lock();
	return P();
}

#if _MSC_VER >= 1200
void _DLLENTRY CCreator :: Free (void *pMem)
{
	TX_ASSERT_VALID_CONT(this);
	if (NULL != pMem) 
		delete [] pMem;
}
#endif // _MSC_VER >= 1200

void * _DLLENTRY CCreator :: InsertPointer (void *pData)	// #HK940606
{
	TX_ASSERT_VALID_CONT(this);

CContainer :: CSyncThread Sync (&m_rCont);

	if (GetHandle()) Insert();

	GetHandle() = (FSHandle)pData;
	lock();
	
return P();
}

_DLLENTRY CCreator :: CCreator (CContainer & c)
#if defined(WIN32)
		    : CLock (0), 
#else
		    : CLock (c.GetFreeStore(), 0), 
#endif
		      m_rCont (c)
{
	// Nothing to do.
}

_DLLENTRY CCreator :: ~CCreator (void)
{
	TX_ASSERT_VALID_CONT(this);
	
CContainer :: CSyncThread Sync (&m_rCont);

	if (GetHandle ()) {
#if defined(_DEBUG)
		if (!m_rCont.Insert (GetHandle(), P()))
			TX_ASSERT(false);
#else
		m_rCont.Insert (GetHandle(), P());
#endif // _DEBUG
	}
}

