// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.02.2000 18:54:52 
//
// @doc
// @module OneSizeHeapListDebugDefines.h | OneSizeHeapList template macro helpers (debug)

#if !defined(_ONESIZEHEAPLISTDEBUGDEFINES_H__3003BB48_E61C_42AD_A742_15E0F972F9C2__INCLUDED_)
#define _ONESIZEHEAPLISTDEBUGDEFINES_H__3003BB48_E61C_42AD_A742_15E0F972F9C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if !defined(MAKEUNIQUENAME)
#define __XY__(X,Y) X##Y
#define MAKEUNIQUENAMEXY(FX,LINE) __XY__(FX,LINE)
#define MAKEUNIQUENAME(FX) MAKEUNIQUENAMEXY(FX,__LINE__)
#endif // MAKEUNIQUENAME

//==================================================================
#define IMPLEMENT_ONE_SIZE_PRIVATE_HEAP_LIST(allocator, dataclass)	\
namespace { COneSizeHeapList<dataclass,allocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
void * dataclass::operator new (size_t nSize, LPCSTR lpszFileName, int nLine)\
{																\
	if (nSize != sizeof(dataclass))								\
		return ::operator new(nSize,lpszFileName,nLine);		\
	return MAKEUNIQUENAME(theHeap).Alloc();						\
}																\
void  dataclass::operator delete (void* p, size_t size)			\
{																\
	if (NULL == p) return; /* do nothing */						\
	if (size != sizeof(dataclass))								\
		{ ::operator delete(p); return; }						\
	MAKEUNIQUENAME(theHeap).Free(p);							\
}

//==================================================================
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(dataclass)		\
namespace { COneSizeHeapList<dataclass,CWizOneSizeHeapAllocators::CLocalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
void * dataclass::operator new (size_t nSize, LPCSTR lpszFileName, int nLine)\
{																\
	if (nSize != sizeof(dataclass))								\
		return ::operator new(nSize,lpszFileName,nLine);		\
	return MAKEUNIQUENAME(theHeap).Alloc();						\
}																\
void  dataclass::operator delete (void* p, size_t size)			\
{																\
	if (NULL == p) return; /* do nothing */						\
	if (size != sizeof(dataclass))								\
		{ ::operator delete(p); return; }						\
	MAKEUNIQUENAME(theHeap).Free(p);							\
}

//==================================================================
#define IMPLEMENT_ONE_SIZE_PRIVATE_GLOBAL_HEAP_LIST(dataclass)		\
namespace { COneSizeHeapList<dataclass,CWizOneSizeHeapAllocators::CGlobalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
void * dataclass::operator new (size_t nSize, LPCSTR lpszFileName, int nLine)\
{																\
	if (nSize != sizeof(dataclass))								\
		return ::operator new(nSize,lpszFileName,nLine);		\
	return MAKEUNIQUENAME(theHeap).Alloc();						\
}																\
void  dataclass::operator delete (void* p, size_t size)			\
{																\
	if (NULL == p) return; /* do nothing */						\
	if (size != sizeof(dataclass))								\
		{ ::operator delete(p); return; }						\
	MAKEUNIQUENAME(theHeap).Free(p);							\
}

#endif // !defined(_ONESIZEHEAPLISTDEBUGDEFINES_H__3003BB48_E61C_42AD_A742_15E0F972F9C2__INCLUDED_)
