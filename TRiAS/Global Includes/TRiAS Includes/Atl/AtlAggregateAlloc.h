// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/17/1998 09:44:07 AM
//
// @doc
// @module AtlAggregateAlloc.h | Makros für die klassenspezifische Speicherverwaltung
// von aggregierten Objekten

#if !defined(_ATLAGGREGATEALLOC_H__712CE005_94BB_11D2_9F08_006008447800__INCLUDED_)
#define _ATLAGGREGATEALLOC_H__712CE005_94BB_11D2_9F08_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Helperklasse für eigene Speicherverwaltung
#if defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#define DECLARE_AGGR_ALLOCATORTRAITS(x)							\
	class _alloc_t { public:									\
	static void *Alloc (size_t nSize, LPCSTR lpszFileName, int nLine); \
	static void Free (void* p, size_t size);					\
	};
#else // defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#define DECLARE_AGGR_ALLOCATORTRAITS(x)							\
	class _alloc_t { public:									\
	static void *Alloc (size_t nSize);							\
	static void Free (void* p, size_t size);					\
	};
#endif // defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)

// classfactory für aggregierte Objekte mit eigener Speicherverwaltung
#define DECLARE_AGGREGATABLE_EX2(x) public:						\
	DECLARE_AGGR_ALLOCATORTRAITS(x)								\
	typedef CComCreator2< CComCreator< CComObject< x > >, CComCreator< CComAggObjectEx< x, _alloc_t > > > _CreatorClass;

#define DECLARE_ONLY_AGGREGATABLE_EX2(x) public:				\
	DECLARE_AGGR_ALLOCATORTRAITS(x)								\
	typedef CComCreator2< CComFailCreator<E_FAIL>, CComCreator< CComAggObjectEx< x, _alloc_t > > > _CreatorClass;

#if defined(_USE_ONESIZEHEAP)
// OneSizeHeaps verwenden

#if defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(dataclass)	\
namespace {														\
	COneSizeHeapList<CComAggObjectEx<dataclass, dataclass::_alloc_t>, \
					 CWizOneSizeHeapAllocators::CLocalHeapAllocator> \
		MAKEUNIQUENAME(theHeap)(#dataclass); 					\
};																\
void *dataclass::_alloc_t::Alloc (size_t nSize, LPCSTR lpszFileName, int nLine) \
{																\
	if (nSize != sizeof(CComAggObjectEx<dataclass, dataclass::_alloc_t>)) \
		return ::operator new(nSize,lpszFileName,nLine);		\
	return MAKEUNIQUENAME(theHeap).Alloc();						\
}																\
void dataclass::_alloc_t::Free (void* p, size_t size)			\
{																\
	if (NULL == p) return; /* do nothing */						\
	if (size != sizeof(CComAggObjectEx<dataclass, dataclass::_alloc_t>)) \
		{ ::operator delete(p); return; }						\
	MAKEUNIQUENAME(theHeap).Free(p);							\
} 
#else // defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(dataclass)	\
namespace {														\
	COneSizeHeapList<CComAggObjectEx<dataclass, dataclass::_alloc_t>, \
					 CWizOneSizeHeapAllocators::CLocalHeapAllocator> \
		MAKEUNIQUENAME(theHeap)(#dataclass); 					\
};																\
void *dataclass::_alloc_t::Alloc (size_t nSize)					\
{																\
	if (nSize != sizeof(CComAggObjectEx<dataclass, dataclass::_alloc_t>)) \
		return ::operator new(nSize);							\
	return MAKEUNIQUENAME(theHeap).Alloc();						\
} \
void dataclass::_alloc_t::Free (void* p, size_t size)			\
{																\
	if (NULL == p) return; /* do nothing */						\
	if (size != sizeof(CComAggObjectEx<dataclass, dataclass::_alloc_t>)) \
		{ ::operator delete(p); return; }						\
	MAKEUNIQUENAME(theHeap).Free(p);							\
} 
#endif // defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)

#else // _USE_ONESIZEHEAP

// normale Speicherverwaltung verwenden
#if defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(dataclass)	\
void *dataclass::_alloc_t::Alloc (size_t nSize, LPCSTR lpszFileName, int nLine)	\
{																\
	return ::operator new(nSize, lpszFileName, nLine);			\
} \
void dataclass::_alloc_t::Free (void* p, size_t size)			\
{																\
	::operator delete(p);										\
} 
#else // defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(dataclass)	\
void *dataclass::_alloc_t::Alloc (size_t nSize)					\
{																\
	return ::operator new(nSize);								\
} \
void dataclass::_alloc_t::Free (void* p, size_t size)			\
{																\
	::operator delete(p);										\
} 
#endif // defined(_DEBUG) && defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)

#endif // defined(_USE_ONESIZEHEAP)

#endif // !defined(_ATLAGGREGATEALLOC_H__712CE005_94BB_11D2_9F08_006008447800__INCLUDED_)
