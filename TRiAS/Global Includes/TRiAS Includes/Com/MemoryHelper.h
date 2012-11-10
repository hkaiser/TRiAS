// @doc 
// @module MemoryHelper.h | HelperKlassen für die Speicherverwaltung

#if !defined(_MEMORYHELPER_H__31510E37_B566_11D2_95A8_006008447800__INCLUDED_)
#define _MEMORYHELPER_H__31510E37_B566_11D2_95A8_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// HilfsKlassen für die Verwaltung eines globalen Speicherbereiches
class CGlobalMem
{
public:
	CGlobalMem() : m_hGbl(NULL)
	{
	}
	CGlobalMem (DWORD dwSize, UINT uiFlags = GHND) : m_hGbl(NULL)
	{
		m_hGbl = GlobalAlloc (uiFlags, dwSize);
		if (NULL == m_hGbl) _com_issue_error(E_OUTOFMEMORY);
	}
	~CGlobalMem()
	{
		Tidy();
	}
	HGLOBAL Handle() { return m_hGbl; }
	HGLOBAL Detach() 
	{ HGLOBAL hGbl = m_hGbl; m_hGbl = NULL; return hGbl; }
	HGLOBAL Attach(HGLOBAL hNewGbl) 
	{ HGLOBAL hGbl = m_hGbl; m_hGbl = hNewGbl; return hGbl; }

	HGLOBAL *operator &() { Tidy(); return &m_hGbl; }
	bool operator! () { return NULL == m_hGbl ? true : false; }
	HGLOBAL GetHandle() { return m_hGbl; }

public:
	template<class T>
	class Lock 
	{
	public:
		Lock (CGlobalMem &rMem) : m_hGbl(NULL), m_pGbl(NULL)
			{
				m_pGbl = reinterpret_cast<T *>(GlobalLock (rMem.Handle())); 
				if (NULL == m_pGbl) _com_issue_error(E_OUTOFMEMORY);
				m_hGbl = rMem.Handle();
			}
		Lock (HGLOBAL hGbl) : m_hGbl(NULL), m_pGbl(NULL)
			{ 
				m_pGbl = reinterpret_cast<T *>(GlobalLock (hGbl)); 
				if (NULL == m_pGbl) _com_issue_error(E_OUTOFMEMORY);
				m_hGbl = hGbl;
			}
		~Lock() 
			{
				if (NULL != m_hGbl) {
					GlobalUnlock (m_hGbl); 
					m_hGbl = NULL;
					m_pGbl = NULL;
				}
			}

		operator T *() { return m_pGbl; }
		DWORD GetSize() { return (NULL != m_hGbl) ? ::GlobalSize(m_hGbl) : 0L; }
		DWORD GetCount() { _ASSERTE(0 < sizeof(T)); return GetSize()/sizeof(T); }

	private:
		HGLOBAL m_hGbl;
		T *m_pGbl;
	};

protected:
	void Tidy()
	{
		if (NULL != m_hGbl) {
			GlobalFree(m_hGbl);
			m_hGbl = NULL;
		}
	}

	HGLOBAL m_hGbl;
};

///////////////////////////////////////////////////////////////////////////////
// HilfsKlasse für die Verwaltung eines IMalloc-Speicherbereiches 
template<class T>
class CMallocMem
{
public:
	CMallocMem () : m_pMem(NULL) {}
	CMallocMem (void *pMem) : m_pMem(pMem) { _ASSERTE((ULONG)-1L != GetSize()); }
	CMallocMem (ULONG ulSize) throw(_com_error &): m_pMem(NULL)
		{
			m_pMem = reinterpret_cast<T *>(CoTaskMemAlloc(ulSize));
			if (NULL == m_pMem) _com_issue_error(E_OUTOFMEMORY);
		}
	~CMallocMem()
		{ Tidy(); }

	T* Attach(T *pNewMem) { T *pT = m_pMem; m_pMem = pNewMem; return pT; }
	T *Detach() { return Attach (NULL); }
	operator T *() { return m_pMem; }
	T **operator &() { Tidy(); return &m_pMem; }

	ULONG GetSize() const 
	{ 
		if (NULL == m_pMem)
			return (ULONG)-1L;

	__Interface<IMalloc> allocator;

		CoGetMalloc (1, allocator.ppi());
		if (1 != allocator -> DidAlloc(m_pMem)) {
			_ASSERTE(1 == allocator -> DidAlloc(m_pMem));
			return (ULONG)-1L;
		}
		return allocator -> GetSize(m_pMem); 
	}
	HRESULT SetSize (ULONG ulSize) 
	{
		if (ulSize == (ULONG)-1)
			return E_INVALIDARG;

	T *pNewMem = reinterpret_cast<T *>(CoTaskMemRealloc (m_pMem, ulSize));

		if (0 != ulSize && NULL == pNewMem) 
			return E_OUTOFMEMORY;
		m_pMem = pNewMem;		// new memory
		return S_OK;
	}

protected:
	void Tidy() 
		{
			if (NULL != m_pMem) {
				CoTaskMemFree(m_pMem);
				m_pMem = NULL;
			}
		}

protected:
	T *m_pMem;
};

#endif // !defined(_MEMORYHELPER_H__31510E37_B566_11D2_95A8_006008447800__INCLUDED_)
