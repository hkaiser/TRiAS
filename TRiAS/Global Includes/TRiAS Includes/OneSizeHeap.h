///////////////////////////////////////////////////////////////////////////
// @doc 
// @module OneSizeHeap.h | OneSizeHeap template
// 29/1/1997 18:52  Author: Poul A. Costinsky  poul@wizsoft.com
// Copyright (C) WizSoft Inc., 1997

#if !defined(_ONESIZEHEAP_H__CF648164_9E24_11D1_BA1C_080036D63803__INCLUDED_)
#define _ONESIZEHEAP_H__CF648164_9E24_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_DEBUG)
#include <ospace/std/string>
#else
#undef _DUMP_PENDING_OBJECTS
#undef USE_DLIB
#endif // _DEBUG

#include <d_lib/d_lib.h>		// debug/tracing support
#include <new>		// std::bad_alloc()

//lint -esym(534, CWin32HeapAllocator::Retry)

///////////////////////////////////////////////////////////////////
template<class TYPE, class ALLOCATOR>
class CWizOneSizeHeap
{
// Debug support
	D_CLASS(CWizOneSizeHeap);

public:
//lint -save -e1503
#if defined(_DEBUG)
	enum GUARD_VALUE {
		PREGUARD_VALUE = 0xFC,		// Werte für Guards
		POSTGUARD_VALUE = 0xFC,
		INITIAL_VALUE = 0xCC,		// Speicher ist initialisiert
		FREED_VALUE = 0xDD,			// Speicher ist freigegeben
	};
	enum GUARD_SIZE {
		GUARDSIZE = 4,				// Größe der Guardbereiche
	};

	struct DATA {
		BYTE m_dwPreGuard[GUARDSIZE];	// guard before data
		union {							// helper for managing the pool
			char data[sizeof(TYPE)];		// object place
			DATA *next;						// pointer to the next free chunk
		} datafield;
		BYTE m_dwPostGuard[GUARDSIZE];	// guard behind data
		ULONG m_ulAllocCount;			// add room for allocation counter
	};
#else
	enum GUARD_SIZE {
		GUARDSIZE = 0,				// Größe der Guardbereiche
	};
	struct DATA {
		union {					// helper for managing the pool
			char data[sizeof(TYPE)];		// object place
			DATA *next;						// pointer to the next free chunk
		} datafield;
	};
#endif // defined(_DEBUG)
//lint -restore

// Internal goodies
	enum { 
		HEAP_STEP = 1024,			// default grow step
		HEAP_SIZE = sizeof(DATA)	// size of one element in the heap
	};

public:
// Constructor:
	explicit CWizOneSizeHeap(LPCSTR pcClassName, bool fThrow = true, bool fTestRelease = true, int Step = -1);
	CWizOneSizeHeap ();
	CWizOneSizeHeap (const CWizOneSizeHeap &rhs);

// Destructor:
	~CWizOneSizeHeap();

// Operations:
	int Size()		const { return m_nSize - m_nFreeSize; }
	int FreeSize()	const { return m_nFreeSize; }
	bool IsEmpty()	const { return (NULL == m_Pool) && m_fTestRelease; }

	TYPE* Alloc();
	void Free (void *p);
	bool DidAlloc (void *p) const;

	CWizOneSizeHeap &operator= (const CWizOneSizeHeap &rhs);

protected:
// Implementation:
	bool TestRelease();
	bool TestPool();
	bool InitPool();
	bool ReallocPool();
	void InitPointers();

private:
// data members
	ALLOCATOR	m_All;
	DATA *		m_Pool;
	DATA *		m_pFirstFree;
	int			m_nStep;
	int			m_nSize;
	int			m_nFreeSize;
	bool		m_fMemExceptions;
	bool		m_fTestRelease;

#if defined(_DEBUG)
public:
	os_string	m_strClassName;
	ULONG		m_ulAllocCount;
	ULONG		m_ulFreeCount;
	ULONG		m_ulHeapCount;
#endif // defined(_DEBUG)
};

#if defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Testen, ob Speicherbereich wie erwartet gefüllt ist
inline bool TestFillBytes (void *p, BYTE c, int iCnt)
{
	for (int i = 0; i < iCnt; i++) {
		if (((BYTE *)p)[i] != c)
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Speicherbereich gezielt füllen
inline void FillBytes (void *p, BYTE c, int iCnt)
{
	memset (p, c, iCnt);
}
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
namespace CWizOneSizeHeapAllocators
{
	///////////////////////////////////////////////////////////////////
	// simple allocator which gets the memory from malloc
	class CMallocator  
	{
	// Debug support
		D_CLASS(CMallocator);

	public:
		CMallocator()						{}
		~CMallocator()						{}
		static void* Alloc(size_t& size)	{ return ::malloc(size); }
		static void Free(void* p)			{ if (p) ::free(p); }
		static void* ReAlloc(size_t &size, void *p);
	};

	///////////////////////////////////////////////////////////////////
	// Don't use this class! Use CGlobalHeapAllocator or CLocalHeapAllocator!!!
	class CWin32HeapAllocator	// Gets memory right from Win32 API.
	{
	// Debug support
		D_CLASS(CWin32HeapAllocator);

	protected: // Don't use it directly!
		CWin32HeapAllocator() : m_hHeap (NULL) {}
	public:
		~CWin32HeapAllocator() { m_hHeap = NULL; }
		void* Alloc(size_t& size);
		void Free(void* p);
		void* ReAlloc(size_t &size, void *p);

	protected:
		void * _Alloc   (size_t size);
		void * _ReAlloc (size_t size, void *p);
		size_t _Size	(void *p);
		bool TestHeap();
		UINT Retry();

		HANDLE m_hHeap;
	};

	///////////////////////////////////////////////////////////////////
	//
	class CGlobalHeapAllocator : public CWin32HeapAllocator
	{
	// Debug support
		D_CLASS(CGlobalHeapAllocator);

	public:
		CGlobalHeapAllocator()	{ m_hHeap = GetProcessHeap(); }
	};
	
	///////////////////////////////////////////////////////////////////
	//
	class CLocalHeapAllocator : public CWin32HeapAllocator
	{
	// Debug support
		D_CLASS(CLocalHeapAllocator);

	public:
		CLocalHeapAllocator()	{}
		~CLocalHeapAllocator()	{ if(m_hHeap) { ::HeapDestroy(m_hHeap); m_hHeap = NULL; } }
	};
} // namespace

///////////////////////////////////////////////////////////////////
// Macros to minimize typing:

#if defined(_USE_ONESIZEHEAP)
// OneSizeHeaps verwenden

///////////////////////////////////////////////////////////////////
#if defined(_DEBUG) 

#if defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#include <OneSizeHeapDebugDefines.h>
#else // defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)
#include <OneSizeHeapReleaseDefines.h>
#endif // defined(_MFC_VER) && !defined(_AFX_NO_DEBUG_CRT)

#else // defined(_DEBUG)
#include <OneSizeHeapReleaseDefines.h>
#endif // defined(_DEBUG) 

#else // _USE_ONESIZEHEAP
// normale Speicherverwaltung verwenden

#define DECLARE_ONE_SIZE_PRIVATE_HEAP()
#define DECLARE_ONE_SIZE_PRIVATE_HEAP2(x)

#define IMPLEMENT_ONE_SIZE_PRIVATE_HEAP(allocator, dataclass)
#define IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP(dataclass)
#define IMPLEMENT_ONE_SIZE_PRIVATE_GLOBAL_HEAP(dataclass)

#endif // _USE_ONESIZEHEAP

///////////////////////////////////////////////////////////////////
// Concrete heaps to use:

///////////////////////////////////////////////////////////////////
// malloc's heap

template<class TYPE>
class CWizOneSizeMallocHeap : 
	public CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CMallocator>
{
public:
#if defined(_DEBUG)
	explicit CWizOneSizeMallocHeap(LPCSTR pcClsName, int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CMallocator>(pcClsName, Step) {}
#else
	explicit CWizOneSizeMallocHeap(int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CMallocator>(Step) {}
#endif // defined(_DEBUG)
};

///////////////////////////////////////////////////////////////////
// CLocalHeapAllocator's heap

template<class TYPE>
class CWizOneSizeLocalHeap : 
	public CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CLocalHeapAllocator>
{
public:
#if defined(_DEBUG)
	explicit CWizOneSizeLocalHeap(LPCSTR pcClsName, int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CLocalHeapAllocator>(pcClsName, Step) {}
#else
	explicit CWizOneSizeLocalHeap(int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CLocalHeapAllocator>(Step) {}
#endif // defined(_DEBUG)
};

///////////////////////////////////////////////////////////////////
// CGlobalHeapAllocator's heap

template<class TYPE>
class CWizOneSizeGlobalHeap : 
	public CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CGlobalHeapAllocator>
{
public:
#if defined(_DEBUG)
	explicit CWizOneSizeGlobalHeap(LPCSTR pcClsName, int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CGlobalHeapAllocator>(pcClsName, Step) {}
#else
	explicit CWizOneSizeGlobalHeap(int Step = -1)
		: CWizOneSizeHeap<TYPE, CWizOneSizeHeapAllocators::CGlobalHeapAllocator>(Step) {}
#endif // defined(_DEBUG)
};

///////////////////////////////////////////////////////////////////
// Implementation:

template<class TYPE, class ALLOCATOR>
inline CWizOneSizeHeap<TYPE, ALLOCATOR>::CWizOneSizeHeap(LPCSTR pcClsName, bool fThrow, bool fTestRelease, int Step) 
		: m_Pool(NULL) , m_pFirstFree (NULL),
		  m_nStep(Step), m_nSize(0), m_nFreeSize(0), m_fMemExceptions(fThrow), m_fTestRelease(fTestRelease)
#if defined(_DEBUG)
		, m_strClassName(pcClsName), m_ulAllocCount(0L), m_ulFreeCount(0L), m_ulHeapCount(0L)
#endif // defined(_DEBUG)
{
	_ASSERTE(sizeof(DATA) == HEAP_SIZE);

// adjust step to reasonable value
//lint --e(527)
	if (m_nStep < HEAP_STEP) 
		m_nStep = HEAP_STEP;
	else 
		m_nStep = ((m_nStep + HEAP_STEP - 1)/HEAP_STEP)*HEAP_STEP;
}

template<class TYPE, class ALLOCATOR>
inline CWizOneSizeHeap<TYPE, ALLOCATOR>::CWizOneSizeHeap() 
		: m_Pool(NULL) , m_pFirstFree (NULL), 
		  m_nStep(HEAP_STEP), m_nSize(0), m_nFreeSize(0), m_fMemExceptions(true), m_fTestRelease(true)
#if defined(_DEBUG)
		, m_strClassName(""), m_ulAllocCount(0L), m_ulFreeCount(0L), m_ulHeapCount(0L)
#endif // defined(_DEBUG)
{
	_ASSERTE(sizeof(DATA) == HEAP_SIZE);
}

template<class TYPE, class ALLOCATOR>
inline CWizOneSizeHeap<TYPE, ALLOCATOR>::CWizOneSizeHeap(const CWizOneSizeHeap &rhs) 
		: m_Pool(rhs.m_Pool), m_pFirstFree (rhs.m_pFirstFree),
		  m_nStep(rhs.m_nStep), m_nSize(rhs.m_nSize), m_nFreeSize(rhs.m_nFreeSize),
		  m_fMemExceptions(rhs.m_fMemExceptions), m_fTestRelease(rhs.m_fTestRelease)
#if defined(_DEBUG)
		, m_strClassName(rhs.m_strClassName), m_ulAllocCount(0L), m_ulFreeCount(0L), m_ulHeapCount(0L)
#endif // defined(_DEBUG)
{
}

template<class TYPE, class ALLOCATOR>
CWizOneSizeHeap<TYPE, ALLOCATOR> &CWizOneSizeHeap<TYPE, ALLOCATOR>::operator= (const CWizOneSizeHeap &rhs)
{
	if (&rhs != this) {
		m_Pool = rhs.m_Pool;
		m_pFirstFree = rhs.m_pFirstFree;
		m_nStep = rhs.m_nStep;
		m_nSize = rhs.m_nSize;
		m_nFreeSize = rhs.m_nFreeSize;
		m_fMemExceptions = rhs.m_fMemExceptions;
		m_fTestRelease = rhs.m_fTestRelease;
#if defined(_DEBUG)
		m_strClassName = rhs.m_strClassName;
		m_ulAllocCount = rhs.m_ulAllocCount;
		m_ulFreeCount = rhs.m_ulFreeCount;
		m_ulHeapCount = rhs.m_ulHeapCount;
#endif // defined(_DEBUG)
	}
	return *this;
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline CWizOneSizeHeap<TYPE, ALLOCATOR>::~CWizOneSizeHeap()
{
	if (m_Pool != NULL) {
#if defined(_DEBUG)
		if (m_nFreeSize != m_nSize)	{
			D_OUTF3(1, 
				"OneSizeHeap: %s:", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>", 
				" Releasing heap(%08lx)", m_Pool, 
				" with %ld allocated object(s)!", m_nSize-m_nFreeSize);

#if defined(_DUMP_PENDING_OBJECTS)
		DATA *p = m_Pool;

			for (int i = 0; i < m_nStep; i++, p++) {
				if (0 != p -> m_ulAllocCount) {
				// Objekt nicht freigegeben: Dump-Funktion für dieses Objekt rufen
					reinterpret_cast<TYPE *>(p -> datafield.data) -> Dump();
				} 
			}
#endif // _DUMP_PENDING_OBJECTS
		}
#endif // defined(_DEBUG)
		m_All.Free(m_Pool);		//lint !e1705
	}
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline TYPE* CWizOneSizeHeap<TYPE, ALLOCATOR>::Alloc()
{
	if (!TestPool())
		return NULL;

TYPE *p = (TYPE *)&m_pFirstFree -> datafield.data;
#if defined(_DEBUG)
DATA *pNewElement = m_pFirstFree;
#endif // defined(_DEBUG)

	_ASSERTE(p != NULL);
	_ASSERTE(m_pFirstFree != m_pFirstFree -> datafield.next);
	_ASSERTE(0 == m_pFirstFree -> m_ulAllocCount);			// nicht benutzter Eintrag

	m_pFirstFree = m_pFirstFree -> datafield.next;
	m_nFreeSize--;

#if defined(_DEBUG)
// Speicher initialisieren
	FillBytes (&pNewElement -> m_dwPreGuard, PREGUARD_VALUE, sizeof(pNewElement -> m_dwPreGuard));
	FillBytes (&pNewElement -> datafield.data, INITIAL_VALUE, sizeof(TYPE));
	FillBytes (&pNewElement -> m_dwPostGuard, POSTGUARD_VALUE, sizeof(pNewElement -> m_dwPostGuard));
	pNewElement -> m_ulAllocCount = ++m_ulAllocCount;		// save actual allocation counter
#endif // defined(_DEBUG)
	return p;
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline void CWizOneSizeHeap<TYPE, ALLOCATOR>::Free (void *p)
{
#if defined(_DEBUG)
	m_ulFreeCount++;		// free counter
	_ASSERTE(m_ulAllocCount >= m_ulFreeCount);
#endif // defined(_DEBUG)

DATA* p1 = (DATA *)((BYTE *)p - GUARDSIZE);

	_ASSERTE(p1 -> m_ulAllocCount > 0 && p1 -> m_ulAllocCount <= m_ulAllocCount);		// noch nicht freigegeben
	_ASSERTE(TestFillBytes (&p1 -> m_dwPreGuard, PREGUARD_VALUE, GUARDSIZE));
	_ASSERTE(TestFillBytes (&p1 -> m_dwPostGuard, POSTGUARD_VALUE, GUARDSIZE));

	_ASSERTE(NULL != m_Pool && p1 >= m_Pool);
	_ASSERTE(NULL != m_Pool && p1 <  m_Pool + m_nSize);

#if defined(_DEBUG)
// Speicher wieder in den Pool aufnehmen und entsprechend initialisieren
	FillBytes (p1, FREED_VALUE, sizeof(TYPE));
#endif // defined(_DEBUG)

	if(m_pFirstFree == NULL) {
	// If the pool was empty - here it is!
		p1 -> datafield.next = NULL;
#if defined(_DEBUG)
		p1 -> m_ulAllocCount = 0;		// ist freigeben !
#endif // defined(_DEBUG)

		m_pFirstFree = p1;
		m_nFreeSize++;
	}
	else {
	// the new chunk becomes the first free one
		_ASSERTE(p1 != m_pFirstFree);

		p1 -> datafield.next = m_pFirstFree;
#if defined(_DEBUG)
		p1 -> m_ulAllocCount = 0;		// ist freigeben !
#endif // defined(_DEBUG)

		m_pFirstFree = p1;
		m_nFreeSize++;
	
	// If all the pool is free - release it
		TestRelease();
	}
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline bool CWizOneSizeHeap<TYPE, ALLOCATOR>::DidAlloc (void *p) const
{
	return (NULL != m_Pool && NULL != p && m_Pool <= p && p < m_Pool + m_nSize);
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline bool CWizOneSizeHeap<TYPE, ALLOCATOR>::TestRelease()
{
// Since you're not going to allocate one object from the pool,
// it's desirable to release all the pool when last object gone.
	if (m_Pool == NULL || m_nFreeSize < m_nSize || !m_fTestRelease)
		return false;
	_ASSERTE(m_nFreeSize == m_nSize);

//lint --e(1705)
	m_All.Free(m_Pool);
	m_Pool = m_pFirstFree = NULL;
	m_nSize = m_nFreeSize = 0;
	return true;
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline bool CWizOneSizeHeap<TYPE, ALLOCATOR>::TestPool()
{
	if (m_Pool == NULL) {
		if (!InitPool())
			return false;
	}
	if (m_pFirstFree == NULL) {
		if (!ReallocPool())
			return false;
	}
	return true;
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline bool CWizOneSizeHeap<TYPE, ALLOCATOR>::InitPool()
{
	_ASSERTE(m_nSize == 0);
	_ASSERTE(m_pFirstFree == NULL);

size_t s = size_t(m_nStep*HEAP_SIZE);

	m_Pool = (DATA *)m_All.Alloc(s);		//lint !e1705
	if (NULL == m_Pool) {
		if (m_fMemExceptions)
			throw std::bad_alloc();
		return false;
	}

	D_OUTF3(2, 
		"OneSizeHeap: %s:", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>",
		" InitPool (%08lx),", m_Pool,
		" size(%ld).", s);

	s /= HEAP_SIZE;
	m_pFirstFree = m_Pool;
	m_nSize = s;
	m_nFreeSize = m_nSize;
	InitPointers ();
	return true;
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline bool CWizOneSizeHeap<TYPE, ALLOCATOR>::ReallocPool()
{
register size_t delta = size_t(m_nStep);
const size_t s = size_t((m_nSize + m_nStep)*HEAP_SIZE);
size_t s1 = s;

	D_OUTF3(2, 
		"OneSizeHeap: %s:", m_strClassName.size() > 0 ? m_strClassName.c_str() : "<Unknown>",
		" ReAllocPool(%ld),", s, 
		" size(%ld).", m_nSize);

DATA *p = (DATA*)m_All.ReAlloc(s1, m_Pool);		//lint !e1705

	if (p == NULL) {
		if (m_fMemExceptions)
			throw std::bad_alloc();
		return false;
	}

	_ASSERTE(m_Pool == p);
	if (s != s1) {
		delta = (s - s1)/HEAP_SIZE;
		if (delta == 0) {
			if (m_fMemExceptions)
				throw std::bad_alloc();
			return false;
		}
	}

//lint --e(613)
	m_pFirstFree = m_Pool + m_nSize;
	m_nSize		+= delta;
	m_nFreeSize += delta;
	InitPointers ();
	return true;
}

//*****************************************************************
template<class TYPE, class ALLOCATOR>
inline void CWizOneSizeHeap<TYPE, ALLOCATOR>::InitPointers ()
{
DATA *p = m_pFirstFree;

	_ASSERTE(NULL != p);
	for (int i = 0; i < m_nStep; i++, p++) {
		if (i == m_nStep-1) {
			p -> datafield.next = NULL;		// letzter Pointer muß NULL sein
		} else {
			p -> datafield.next = p + 1;
		}
#if defined(_DEBUG)
		p -> m_ulAllocCount = 0;
#endif // defined(_DEBUG)
	}
}

///////////////////////////////////////////////////////////////////
namespace CWizOneSizeHeapAllocators
{

//*****************************************************************
inline void* CMallocator::ReAlloc(size_t &size, void *p) 
{ 
void* p1 = ::_expand(p, size);

// if expand cannot get the full size, it tries to do the best.
	if (p1 == NULL) {
	size_t size1 = _msize(p);

		if (size1 > size) {
			size = size1;
			p1 = p;
		} else
			size = 0;
	}
	return p1;
}

//*****************************************************************
enum {
	INITIAL_HEAP_SIZE = 65536,	// 64K
	MAXIMUM_HEAP_SIZE = 0		// 64K
};

//*****************************************************************
inline
void* CWin32HeapAllocator::Alloc(size_t& size) 
{ 
	if (!TestHeap())
		return NULL;

void *p = _Alloc(size);

	if(p == NULL) {
		Retry();
		p = _Alloc(size);
		if (p == NULL)
			return NULL;
	}
	size = _Size(p);
	return p;
}

//*****************************************************************
inline
void CWin32HeapAllocator::Free(void* p)		
{ 
	if(p)
		::HeapFree(m_hHeap, 0, p);
}

//*****************************************************************
inline
void* CWin32HeapAllocator::ReAlloc(size_t &size, void *p) 
{ 
	if (!TestHeap())
		return NULL;

void* p1 = _ReAlloc(size, p);

	if (p1 == NULL)	{
		Retry();
		p1 = _ReAlloc(size, p);
		if (p1 == NULL)
			return NULL;
	}
	p = p1;
	size = _Size(p);
	return p;
}

//*****************************************************************
inline
void * CWin32HeapAllocator::_Alloc (size_t size)	
{ 
	return ::HeapAlloc(m_hHeap, 0, size); 
}

//*****************************************************************
inline
void * CWin32HeapAllocator::_ReAlloc (size_t size, void *p) 
{ 
	return ::HeapReAlloc(m_hHeap, HEAP_REALLOC_IN_PLACE_ONLY, p, size); 
}

//*****************************************************************
inline
size_t CWin32HeapAllocator::_Size (void *p)		
{ 
	return ::HeapSize(m_hHeap, 0, p); 
}

//*****************************************************************
inline
bool CWin32HeapAllocator::TestHeap()
{
	if (NULL != m_hHeap)
		return true;

	m_hHeap = ::HeapCreate(0, INITIAL_HEAP_SIZE, MAXIMUM_HEAP_SIZE);
	return (NULL != m_hHeap) ? true : false;
}

//*****************************************************************
inline
UINT CWin32HeapAllocator::Retry()
{	
	return ::HeapCompact(m_hHeap, 0); 
}

} // namespace

///////////////////////////////////////////////////////////////////

#if defined(_DEBUG) && defined(_DUMP_PENDING_OBJECTS)

// spezielles Interface
struct __declspec(uuid("019ADAF7-3579-4914-834D-FE97F7D1612E"))
IDumpObject : IUnknown
{
    virtual HRESULT __stdcall get_IsA (BSTR *pbstrName) = 0;
    virtual HRESULT __stdcall Dump () = 0;
};

template<class T>
class IDumpObjectImpl :
	public IDumpObject
{
public:
	STDMETHOD(get_IsA)(BSTR *pbstrName) { return E_NOTIMPL; }
	STDMETHOD(Dump)() { return E_NOTIMPL; }
};

#define COM_INTERFACE_ENTRY_DUMPOBJECT()	COM_INTERFACE_ENTRY(IDumpObject)

#else

template<class T> class IDumObjectImpl {};

#define COM_INTERFACE_ENTRY_DUMPOBJECT()		/**/

#endif // defined(_DEBUG) && defined(_DUMP_PENDING_OBJECTS)

#endif // !defined(_ONESIZEHEAP_H__CF648164_9E24_11D1_BA1C_080036D63803__INCLUDED_)
