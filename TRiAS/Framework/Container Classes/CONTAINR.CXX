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
//  Containr.cxx - Containers 2.0 implementation
//
//	#HK930501: void Container::Insert() --> BOOL Container::Insert()
//
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CContainer, CObject, 1)

#define new DEBUG_NEW

void _DLLENTRY CContainer::Serialize (CArchive &ar)
{
	CObject::Serialize (ar);

	if (ar.IsStoring) {
		ar << (long)m_ulCount;
	} else {
	long lCount;
	
		ar >> lCount;			// Anzahl der Elemente
		m_ulCount = lCount;
	}
}
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// aus Registry geladene Flags, die vorgeben, was überhaupt erlaubt ist
typedef enum tagCONTFLAGS CONTFLAG;		// forward decl
CONTFLAG g_rgContFlags = static_cast<CONTFLAG>(CFAutoDelete|CFUniqueKey);

///////////////////////////////////////////////////////////////////////////////
//
#if defined(WIN32) && defined(_DEBUG)
void CContainer::AssertValid (void) const
{
}
#endif

_DLLENTRY CContainer::CContainer (CONTFLAG fContFlags)
	: CSyncMonitor ((fContFlags & g_rgContFlags & CFSyncThreads) ? true : false)
{
#if !defined(WIN32)
	m_pFS = NULL;
#endif
	m_ulCount = 0;
	m_fContFlags = static_cast<CONTFLAG>(fContFlags & g_rgContFlags);
	for (int i = 0; i < MAX_NAVIGATORS; i++ )
		m_grNavs[i] = 0;
}

#if !defined(WIN32)
_DLLENTRY CContainer::CContainer (CFreeStore &f, CONTFLAG fContFlags)
	: CSyncMonitor (false)
{
	m_pFS = &f;
	m_ulCount = 0;
	m_fContFlags = static_cast<CONTFLAG>(fContFlags & g_rgContFlags);
	for (int i = 0; i < MAX_NAVIGATORS; i++)
		m_grNavs[i] = 0;
}
#endif

void _DLLENTRY CContainer::Register (CNavigator * pnav)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pnav);

CSyncThread Sync (this);
	
	for (int i = 0; i < MAX_NAVIGATORS; i++) {
		if (m_grNavs[i] == 0) {
			m_grNavs[i] = pnav;
			return;
		}
	}

// WOOPS, if we fell out here we never found a place for our nav.
//	TX_TRACE("Couldn't register navigator with container\r\n");
	TX_ASSERT(false);
}

void _DLLENTRY CContainer::Unregister (CNavigator * pnav)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (pnav);

CSyncThread Sync (this);

	for (int i = 0; i < MAX_NAVIGATORS; i++) {
		if (m_grNavs[i] == pnav) {
			m_grNavs[i] = 0;
			return;
		}
	}
	
// WOOPS, we never found this navigator.
//	TX_TRACE("Couldn't unregister navigator with container\r\n");
	TX_ASSERT(false);
}

#if !defined(WIN32)
CFreeStore * _DLLENTRY CContainer::GetFreeStore (void) const
{
	return m_pFS;
}
#endif

CNode * _DLLENTRY CContainer::FirstNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return DataStructure ();
}

CNode * _DLLENTRY CContainer::LastNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return DataStructure ();
}

ulong _DLLENTRY CContainer::Count (void) const
{
//	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_ulCount;
}

BOOL _DLLENTRY CContainer::Delete (CNode * node)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT (node);

CSyncThread Sync (this);

	if (node -> Locked ()) {
		TX_ASSERT(false);
		return false;
	}

	// Notify all the navigators.
	for (int i = 0; i < MAX_NAVIGATORS; i++) {
		if (m_grNavs[i])
			m_grNavs[i] -> DeleteNotify (node);
	}

	// Call the objects destructor.
	{
#if !defined(WIN32)
	CNakedLock l (m_pFS, node -> GetHandle ());
#else
	CNakedLock l (node -> GetHandle());
#endif	
		if (l.Valid ())
			UserDelete (l.P());
		else {
			TX_ASSERT(false);
			return false;
		}
	}

// Deallocate the space.
	if (m_fContFlags & CFAutoDelete) {	// #HK940605
	// nur freigeben, wenn es verlangt wurde
#if !defined(WIN32)
		if (m_pFS)
			m_pFS -> Dealloc (node -> GetHandle ());
		else 
#endif
		{
			if (node -> GetHandle())
				delete (void *) node -> GetHandle ();
			else {
				TX_ASSERT(false);
				return false;
			}
		}
	}
	node -> SetHandle (0);		// #HK930411
	--m_ulCount;
	
	TX_ASSERT(m_ulCount >= 0);
	return true;
}

BOOL _DLLENTRY CContainer::Insert (FSHandle, void *)
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	++m_ulCount;
	return true;
}

BOOL _DLLENTRY CContainer::EveryDelete (void)
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	while (Count()) {
		if (!Delete (LastNode()))
			break;
	}

	TX_ASSERT(Count() == 0);
	return Count() == 0;
}

