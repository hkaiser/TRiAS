// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.02.2000 11:05:42 
//
// @doc
// @module OneSizeHeapReleaseDefines.h | OneSizeHeap template macro helpers (release)

#if !defined(_ONESIZEHEAPRELEASEDEFINES_H__2243D470_E4EB_4A4D_AC1D_1F561418B602__INCLUDED_)
#define _ONESIZEHEAPRELEASEDEFINES_H__2243D470_E4EB_4A4D_AC1D_1F561418B602__INCLUDED_

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
#define DECLARE_ONE_SIZE_PRIVATE_HEAP()							\
static void *operator new (size_t size);						\
static void operator delete (void* p, size_t size);
#define DECLARE_ONE_SIZE_PRIVATE_HEAP2(x)	DECLARE_ONE_SIZE_PRIVATE_HEAP()

//==================================================================
#define IMPLEMENT_ONE_SIZE_PRIVATE_HEAP(allocator, dataclass)	\
namespace { CWizOneSizeHeap<dataclass,allocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
void * dataclass::operator new (size_t size)					\
{																\
	if (size != sizeof(dataclass))								\
		return ::operator new(size);							\
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
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP(dataclass)		\
namespace { CWizOneSizeHeap<dataclass,CWizOneSizeHeapAllocators::CLocalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
void * dataclass::operator new (size_t size)					\
{																\
	if (size != sizeof(dataclass))								\
		return ::operator new(size);							\
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
#define IMPLEMENT_ONE_SIZE_PRIVATE_GLOBAL_HEAP(dataclass)		\
namespace { CWizOneSizeHeap<dataclass,CWizOneSizeHeapAllocators::CGlobalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
void * dataclass::operator new (size_t size)					\
{																\
	if (size != sizeof(dataclass))								\
		return ::operator new(size);							\
	return MAKEUNIQUENAME(theHeap).Alloc();						\
}																\
void  dataclass::operator delete (void* p, size_t size)			\
{																\
	if (NULL == p) return; /* do nothing */						\
	if (size != sizeof(dataclass))								\
		{ ::operator delete(p); return; }						\
	MAKEUNIQUENAME(theHeap).Free(p);							\
}

#endif // !defined(_ONESIZEHEAPRELEASEDEFINES_H__2243D470_E4EB_4A4D_AC1D_1F561418B602__INCLUDED_)
