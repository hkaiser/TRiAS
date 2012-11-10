// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/23/1998 11:01:59 PM
//
// @doc
// @module OneSizeHeapList.h | Liste von Heaps, die gemeinsam behandelt werden

#if !defined(_ONESIZEHEAPLIST_H__CC0DEF63_0AAE_11D2_865C_00600875138A__INCLUDED_)
#define _ONESIZEHEAPLIST_H__CC0DEF63_0AAE_11D2_865C_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(_DEBUG)		
#undef _DUMP_PENDING_OBJECTS
#undef USE_DLIB
#endif // !defined(_DEBUG)

#include <d_lib/d_lib.h>		// debug/tracing support
#include <ospace/std/list>
#include <Atl/_Resource_guard.h>
#include <OneSizeHeap.h>

/////////////////////////////////////////////////////////////////////////////
// Eine Liste von Klassen-lokalen Heaps

template<class TYPE, class ALLOCATOR, class CS = TYPE::_CritSec>
class COneSizeHeapList :
	public resource_guard<list<CWizOneSizeHeap<TYPE, ALLOCATOR> >, CS>
{
// Debug support
	D_CLASS(COneSizeHeapList);

public:
	typedef CWizOneSizeHeap<TYPE, ALLOCATOR> base_t;
	typedef base_t::DATA DATA;
	typedef list<CWizOneSizeHeap<TYPE, ALLOCATOR> > _resources_list_t;
	typedef _resources_list_t::iterator iterator;
	typedef resource_guard<_resources_list_t, CS>::guard guard_t;

	enum { 
		HEAP_STEP = base_t::HEAP_STEP,		// default grow step
		HEAP_SIZE = base_t::HEAP_SIZE		// size of the object
	};

public:
// ctor/dtor
	explicit COneSizeHeapList(LPCSTR pcClassName, int Step = -1);
	~COneSizeHeapList();

// operations
	TYPE* Alloc();
	void Free (void *p);
	bool DidAlloc (void *p) const;

private:
	int m_nStep;

#if defined(_DEBUG)
public:
	os_string m_strClassName;
	ULONG m_ulAllocCount;
	ULONG m_ulFreeCount;
	ULONG m_ulHeapCount;
	ULONG m_ulMaxAllocCount;
#endif // defined(_DEBUG)
};

/////////////////////////////////////////////////////////////////////////////
// Macros to minimize typing:

#if defined(_USE_ONESIZEHEAP)	// OneSizeHeaps verwenden

#if defined(_DEBUG) 

#if defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#include <OneSizeHeapListDebugDefines.h>
#else
#include <OneSizeHeapListReleaseDefines.h>
#endif // defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)

#else // defined(_DEBUG) 
#include <OneSizeHeapListReleaseDefines.h>
#endif // defined(_DEBUG)

#else // _USE_ONESIZEHEAP
// normale Speicherverwaltung verwenden

#define IMPLEMENT_ONE_SIZE_PRIVATE_HEAP_LIST(allocator, dataclass)
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(dataclass)
#define IMPLEMENT_ONE_SIZE_PRIVATE_GLOBAL_HEAP_LIST(dataclass)

#endif // defined(_USE_ONESIZEHEAP)

/////////////////////////////////////////////////////////////////////////////
// Implementation

template<class TYPE, class ALLOCATOR, class CS>
inline COneSizeHeapList<TYPE, ALLOCATOR, CS>::COneSizeHeapList(LPCSTR pcClsName, int Step) 
		: m_nStep(Step)
#if defined(_DEBUG)
		, m_strClassName(pcClsName), m_ulAllocCount(0L), m_ulFreeCount(0L), 
		  m_ulHeapCount(0L), m_ulMaxAllocCount(0L)
#endif // defined(_DEBUG)
{
	_ASSERTE(sizeof(DATA) == HEAP_SIZE);		// account for alllocation counter

// adjust step to reasonable value
//lint --e(527)
	if (m_nStep < HEAP_STEP) 
		m_nStep = HEAP_STEP;
	else 
		m_nStep = ((m_nStep + HEAP_STEP - 1)/HEAP_STEP)*HEAP_STEP;
}

template<class TYPE, class ALLOCATOR, class CS>
inline COneSizeHeapList<TYPE, ALLOCATOR, CS>::~COneSizeHeapList()
{
#if defined(_DEBUG)
	D_OUTF5(1, 
		"OneSizeHeapList: %s:\r\n", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>", 
		"\tmax count: %ld", m_ulMaxAllocCount,
		" (in %ld heaps),", m_ulHeapCount,
		" alloc count: %ld,", m_ulAllocCount,
		" free count: %ld.", m_ulFreeCount);
			   
	if (m_ulAllocCount != m_ulFreeCount) 
	{
		D_OUTF1(1, "\treleasing heaplist with %ld allocated object(s)!", m_ulAllocCount-m_ulFreeCount);
	}
#endif // defined(_DEBUG)
}

/////////////////////////////////////////////////////////////////////////////
// Speicher anfordern
template<class TYPE, class ALLOCATOR, class CS>
inline TYPE *COneSizeHeapList<TYPE, ALLOCATOR, CS>::Alloc()
{
guard_t guard (Guard());	// threadsafety

#if defined(_DEBUG)
	m_ulAllocCount++;		// AllocZähler
	if (m_ulAllocCount-m_ulFreeCount > m_ulMaxAllocCount)
		m_ulMaxAllocCount = m_ulAllocCount-m_ulFreeCount;		// maximale Anzahl der Allocs mitführen
#endif // defined(_DEBUG)

// zuerst versuchen, in einem der Heaps Platz zu finden
	for (iterator it = (*guard).begin(); it != (*guard).end(); ++it) {
	TYPE *p = NULL;
	
		ATLTRY(p = (*it).Alloc());
		if (NULL != p) {
			if (it != (*guard).begin())
				(*guard).splice ((*guard).begin(), *guard, it);	// an den Anfang rücken
			return p;
		}
		else {
			D_OUTF4(2, 
				"OneSizeHeapList: %s:", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>", 
				" Failed to allocate from heap(%08lx),", (*it).m_ulHeapCount,
				" alloc(%ld),", (*it).Size(),
				" free(%ld).", (*it).FreeSize());
		}
	}

// kein Platz mehr gefunden, neuen Heap anlegen, Heap ohne Exceptions!
#if defined(_DEBUG)
iterator itnew = (*guard).insert((*guard).begin(), base_t(m_strClassName.c_str(), false, 0 != (*guard).size(), m_nStep));

	(*itnew).m_ulHeapCount = ++m_ulHeapCount;	// HeapZähler setzen
	D_OUTF3(2, 
		"OneSizeHeapList: %s:", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>", 
		" Creating new heap(%ld),", m_ulHeapCount,
		" size: %ld.", (*guard).size());
#else
iterator itnew = (*guard).insert((*guard).begin(), base_t("<Unknown>", false, 0 != (*guard).size(), m_nStep));
#endif // defined(_DEBUG)

	if (itnew == (*guard).end())
		throw std::bad_alloc();	// no memory at all

TYPE *p = (*itnew).Alloc();		// der Neue muß Platz haben

	if (NULL == p)
		throw std::bad_alloc();	// snh !!
	return p;
}

/////////////////////////////////////////////////////////////////////////////
// Speicher freigeben
template<class TYPE, class ALLOCATOR, class CS>
inline void COneSizeHeapList<TYPE, ALLOCATOR, CS>::Free (void *p)
{
guard_t guard (Guard());	// threadsafety

#if defined(_DEBUG)
	m_ulFreeCount++;		// AllocZähler
#endif // defined(_DEBUG)

// Heap finden, zu dem dieser Pointer gehört
	for (iterator it = (*guard).begin(); it != (*guard).end(); ++it) {
		if ((*it).DidAlloc(p)) {
		// Heap, gefunden, Speicher freigeben
			(*it).Free(p);

		// Heap entsprechend behandeln
			if ((*it).IsEmpty()) {
				D_OUTF2(2, 
					"OneSizeHeapList: %s:", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>", 
					" Freeing empty heap(%ld).", (*it).m_ulHeapCount);
				(*guard).erase (it);				// es war das letzte aus diesem Heap
			}
			else if (it != (*guard).begin())
				(*guard).splice ((*guard).begin(), *guard, it);	// an den Anfang rücken
			return;
		}
	}
	_ASSERTE(it != (*guard).end());	// keinen Heap gefunden
}

/////////////////////////////////////////////////////////////////////////////
// Speicher angelegt?
template<class TYPE, class ALLOCATOR, class CS>
inline bool COneSizeHeapList<TYPE, ALLOCATOR, CS>::DidAlloc (void *p) const
{
// Heap finden, zu dem dieser Pointer gehört
guard_t guard (Guard());	// threadsafety

	for (iterator it = (*guard).begin(); it != (*guard).end(); ++it) {
		if ((*it).DidAlloc(p)) 
			return true;	// der wars
	}
	return false;			// wir waren es nicht
}

#endif // !defined(_ONESIZEHEAPLIST_H__CC0DEF63_0AAE_11D2_865C_00600875138A__INCLUDED_)
