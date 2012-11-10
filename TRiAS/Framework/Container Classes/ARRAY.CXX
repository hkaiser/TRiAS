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
// Array.cxx - Container 2.0 implementation of ArrayContainer class
//
//	#HK930501: void Container :: Insert() --> BOOL Container :: Insert()
//
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

#include <tassert.hxx>
#include <limits.h>

// Grenze, ab der HUGE-Pointer verwendet werden sollen ------------------------
#define HUGELIMIT ((USHRT_MAX/sizeof(CArrayNode))*31L)/32L

/*
IMPLEMENT_SERIAL (CArrayContainer, CSeqContainer, 1)

#define new DEBUG_NEW

void _DLLENTRY CArrayContainer :: Serialize (CArchive &ar)
{
	CSeqContainer :: Serialize (ar);

	if (ar.IsStoring()) {
		ar << (long)m_uiSize;
		for (uint i = 0; i < m_uiSize; i++) 
			ar << &m_pArray[i];
	} else {
	long lInSize;
	
		ar >> lInSize;			// Größe lesen
		Resize ((uint)lInSize);		// neue Größe einstellen

		for (uint i = 0; i < m_uiSize; i++) {
		CArrayNode *pANode;
		
			ar >> pANode;
			m_pArray[i] = *pANode;
		}
	}
}

*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG) && defined(WIN32)
void CArrayContainer :: AssertValid (void) const
{
	CSeqContainer::AssertValid();
	TX_ASSERT (Count() <= m_uiSize);
	TX_ASSERT (m_pArray);
}
#endif

#if !defined(WIN32)
#pragma optimize ("", off)
#endif // WIN32

_DLLENTRY CArrayContainer :: CArrayContainer (uint noelems, CONTFLAG fContFlags)
			   : CSeqContainer (fContFlags)
{
	m_uiSize = 0;
	m_pArray = NULL;

register uint iNum = noelems;

	if (iNum > 0) {
#if !defined(WIN32)
		if (iNum < HUGELIMIT) {
			m_pArray = new CArrayNode [iNum];
		} 
		else {
			m_pArray = new __huge CArrayNode [iNum];
		}
#else
		m_pArray = new CArrayNode [iNum];
#endif // WIN32
		if (NULL != m_pArray) m_uiSize = iNum;
	}
}

#if !defined(WIN32)
_DLLENTRY CArrayContainer :: CArrayContainer (CFreeStore &fs, uint noelems, CONTFLAG fContFlags)
			   : CSeqContainer (fs, fContFlags)
{
	m_uiSize = 0;
	m_pArray = NULL;

uint iNum = noelems;

	if (iNum > 0) {
		if (iNum >= HUGELIMIT) {
			m_pArray = new __huge CArrayNode [iNum];
		} else {
			m_pArray = new CArrayNode [iNum];
		}
		if (NULL != m_pArray) m_uiSize = iNum;
	}
}
#endif

CNode *  _DLLENTRY CArrayContainer :: DataStructure (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);
	
	return m_pArray;
}

CNode *  _DLLENTRY CArrayContainer :: LastNode (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);
	
#if !defined(WIN32)
	if (Size() >= HUGELIMIT) {
		return (CArrayNode __huge *)m_pArray + (Count() - 1);
	}
#endif // WIN32
	
	return m_pArray + (Count() - 1);
}

uint  _DLLENTRY CArrayContainer :: Size (void) const
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

	return m_uiSize;
}

BOOL  _DLLENTRY CArrayContainer :: Resize (uint newsize)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(newsize >= m_uiSize);
	
CSyncThread Sync (this);

	if (newsize < Count ())	return false;

CArrayNode *newarray = NULL;
uint iNewNum = newsize;

#if !defined(WIN32)
	if (iNewNum < HUGELIMIT) {
		newarray = new CArrayNode [iNewNum];
	} else {
		newarray = new __huge CArrayNode [iNewNum];
	}
#else
	newarray = new CArrayNode [iNewNum];
#endif // WIN32

	if (NULL == newarray) return false;

	if (m_pArray) {
#if !defined(WIN32)
		if (iNewNum >= HUGELIMIT) {
			for (uint i = 0; i < Count (); i++)
				((CArrayNode __huge *)newarray)[i].SetHandle (((CArrayNode __huge *)m_pArray)[i].GetHandle());
			
			if (m_uiSize >= HUGELIMIT) {
				if (m_pArray)
					delete [m_uiSize] (CArrayNode __huge *)m_pArray;
			} else {
				if (m_pArray)
					delete [m_uiSize] m_pArray;
			}
		} else
#endif // WIN32	
		{
			for (uint i = 0; i < Count (); i++)
				newarray[i].SetHandle (m_pArray[i].GetHandle());
			if (m_pArray)
				delete [m_uiSize] m_pArray;
		}
	}

	m_uiSize = iNewNum;
	m_pArray = newarray;

return true;
}

#if !defined(WIN32)
#pragma optimize ("", on)
#endif // WIN32

BOOL _DLLENTRY CArrayContainer :: Insert (FSHandle h, void *p)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(p);
	TX_ASSERT(h);

CSyncThread Sync (this);
		
	if (Count() < Size() || Resize (Size() * 3 / 2)) {
#if !defined(WIN32)
		if (Size() >= HUGELIMIT) 
		{
			((CArrayNode __huge *)m_pArray) [Count()].SetHandle (h);
		} else
#endif
		{
			m_pArray [Count()].SetHandle (h);
		}
		return CSeqContainer :: Insert (h, p);		// updates the Count ().
	}
	
	TX_ASSERT(false);	// Could not resize

return false;
}

BOOL _DLLENTRY CArrayContainer :: Delete (CNode * node)
{
	TX_ASSERT_VALID_CONT(this);
	TX_ASSERT(node);

CSyncThread Sync (this);
		
	if (CSeqContainer :: Delete (node)) // Destroys object, count --
	{
	// Copy all nodes above the deleted node, down one place.
#if !defined(WIN32)
		if (Size() >= HUGELIMIT) {
		CArrayNode __huge *last = (CArrayNode __huge *)m_pArray + Count();

			for (CArrayNode __huge *anode = (CArrayNode __huge *)node; 
			     anode < (CArrayNode __huge *)last; anode++) 
			{
				anode[0] = anode[1];
			}
			TX_ASSERT(anode == last);
			((CArrayNode __huge *)last) -> SetHandle(0);		// mark last node as unused.
		} else
#endif // WIN32
		{
		CArrayNode *last = m_pArray + Count();

			for (CArrayNode * anode = (CArrayNode *)node; anode < last; anode++)
				anode[0] = anode[1];

			TX_ASSERT(anode == last);
			last -> SetHandle (0);		// mark last node as unused.
		}
		return true;
	}

return false;
}

_DLLENTRY CArrayContainer :: ~CArrayContainer (void)
{
	TX_ASSERT_VALID_CONT(this);

CSyncThread Sync (this);

#if !defined(WIN32)	
	if (Size() >= HUGELIMIT) {
		if (m_pArray) 
			delete [m_uiSize] (CArrayNode __huge *)m_pArray;
	} else
#endif // WIN32
	{
		if (m_pArray) delete [m_uiSize] m_pArray;
	}
}


