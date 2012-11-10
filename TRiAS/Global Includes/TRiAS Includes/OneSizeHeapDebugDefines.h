// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.02.2000 11:06:38 
//
// @doc
// @module OneSizeHeapDebugDefines.h | OneSizeHeap template macro helpers (debug)

#if !defined(_ONESIZEHEAPDEBUGDEFINES_H__798EA8EE_968D_478C_9245_0D6291EDDBE0__INCLUDED_)
#define _ONESIZEHEAPDEBUGDEFINES_H__798EA8EE_968D_478C_9245_0D6291EDDBE0__INCLUDED_

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
#if defined(_DUMP_PENDING_OBJECTS)
// Helpermacros für die Deklaration des Heaps im Header des betreffenden Objektes
#define DECLARE_ONE_SIZE_PRIVATE_HEAP()							\
static void *operator new (size_t nSize, LPCSTR lpszFileName = "", int nLine = 0);\
static void operator delete (void* p, size_t size);				\
HRESULT __stdcall Dump();
#define DECLARE_ONE_SIZE_PRIVATE_HEAP2(x)						\
static void *operator new (size_t nSize, LPCSTR lpszFileName = "", int nLine = 0);\
static void operator delete (void* p, size_t size);				\
HRESULT __stdcall Dump();													\
HRESULT __stdcall get_IsA (BSTR *pbstrName) { CComBSTR bstr(L#x); *pbstrName = bstr.Detach(); return S_OK; }
#else
// Helpermacros für die Deklaration des Heaps im Header des betreffenden Objektes
#define DECLARE_ONE_SIZE_PRIVATE_HEAP()							\
static void *operator new (size_t nSize, LPCSTR lpszFileName = "", int nLine = 0);\
static void operator delete (void* p, size_t size);
#define DECLARE_ONE_SIZE_PRIVATE_HEAP2(x)	DECLARE_ONE_SIZE_PRIVATE_HEAP()
#endif // defined(_DUMP_PENDING_OBJECTS)

//==================================================================
#define IMPLEMENT_ONE_SIZE_PRIVATE_HEAP(allocator, dataclass)	\
namespace { CWizOneSizeHeap<dataclass,allocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
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
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP(dataclass)		\
namespace { CWizOneSizeHeap<dataclass,CWizOneSizeHeapAllocators::CLocalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
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
#define IMPLEMENT_ONE_SIZE_PRIVATE_GLOBAL_HEAP(dataclass)		\
namespace { CWizOneSizeHeap<dataclass,CWizOneSizeHeapAllocators::CGlobalHeapAllocator> MAKEUNIQUENAME(theHeap)(#dataclass); };	\
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

#endif // !defined(_ONESIZEHEAPDEBUGDEFINES_H__798EA8EE_968D_478C_9245_0D6291EDDBE0__INCLUDED_)
