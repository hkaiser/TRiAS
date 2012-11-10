// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.02.2000 18:56:32 
//
// @doc
// @module OneSizeHeapListReleaseDefines.h | OneSizeHeapList template macro helpers (release)

#if !defined(_ONESIZEHEAPLISTRELEASEDEFINES_H__6E442BC9_9868_4F7D_8473_EE2EC4377FFB__INCLUDED_)
#define _ONESIZEHEAPLISTRELEASEDEFINES_H__6E442BC9_9868_4F7D_8473_EE2EC4377FFB__INCLUDED_

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
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(dataclass)	\
namespace { COneSizeHeapList<dataclass,CWizOneSizeHeapAllocators::CLocalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
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
#define IMPLEMENT_ONE_SIZE_PRIVATE_GLOBAL_HEAP_LIST(dataclass)	\
namespace { COneSizeHeapList<dataclass,CWizOneSizeHeapAllocators::CGlobalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
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

#endif // !defined(_ONESIZEHEAPLISTRELEASEDEFINES_H__6E442BC9_9868_4F7D_8473_EE2EC4377FFB__INCLUDED_)
