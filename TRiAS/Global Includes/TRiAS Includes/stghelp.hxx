///////////////////////////////////////////////////////////////////////////
// @doc 
// @module stghelp.hxx | Description goes here

#if !defined(_STGHELP_HXX__0AC6D224_6FA1_11D1_B9EC_080036D63803__INCLUDED_)
#define _STGHELP_HXX__0AC6D224_6FA1_11D1_B9EC_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// DebugHelper für Überwachung eines IStream ----------------------------------
// File: STRMHELP.HXX

#if defined(_DEBUG)

#if !defined(__CV__)
#define TX_TRACE	TRACE
#define TX_TRACE1	TRACE1
#define TX_TRACE2	TRACE2
#define TX_TRACE3	TRACE3
#endif // !__CV__

class CStorageWrapper : public IStorage 
{
private:
	DWORD m_dwRefCnt;
	IStorage *m_pStg;
	os_string m_strName;

public:
		CStorageWrapper (IStorage *pIStg, LPCSTR pcName = NULL)
			: m_pStg (pIStg), m_strName(pcName)
		{
			m_dwRefCnt = 1;
			if (NULL != m_pStg) 
				m_pStg -> AddRef();
			TX_TRACE2("Storage::Storage(pIStr: %lx, Name: %s)\n", pIStg, m_strName.c_str());
		}
		~CStorageWrapper (void)
		{
			TX_TRACE1("%s: Storage::~Storage()\n", m_strName.c_str());
			if (NULL != m_pStg) m_pStg -> Release();
		}

	static HRESULT CreateInstance (IStorage *pIStg, LPCSTR pcName, IStorage **ppIStg)
	{
	CStorageWrapper *pWrap = NULL;
	
		ATLTRY(pWrap = new CStorageWrapper (pIStg, pcName));
		if (NULL != pWrap) {
			*ppIStg = pWrap;		// übernimmet RefCnt
			return S_OK;
		}
		return E_OUTOFMEMORY;
	}

	STDMETHODIMP QueryInterface (THIS_ REFIID riid, void ** ppvObject)
	{
		TX_TRACE1("%s: Storage::QueryInterface(...)\n", m_strName.c_str());
		if (riid == IID_IStorage) {
			*ppvObject = this;
			LPUNKNOWN(*ppvObject) -> AddRef();
			return S_OK;
		}
		return m_pStg -> QueryInterface (riid, ppvObject);
	}
	STDMETHODIMP_(ULONG) AddRef (THIS)
	{
		TX_TRACE2("%s: Storage::AddRef(), new RefCnt: %ld\n", m_strName.c_str(), ++m_dwRefCnt);
		return m_dwRefCnt;
	}
	STDMETHODIMP_(ULONG) Release (THIS)
	{
		TX_TRACE2("%s: Storage::Release(), new RefCnt: %ld\n", m_strName.c_str(), --m_dwRefCnt);
		if (m_dwRefCnt == 0) {
			TX_TRACE1("%s: Deleting...\n", m_strName.c_str());
			delete this;
			return 0L;
		}
		return m_dwRefCnt;
	}

// *** IStorage methods ***
    STDMETHOD(CreateStream) (THIS_ LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm)
	{
		TX_TRACE3("%s: Storage::CreateStream(Name: %ls, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
		HRESULT hr = m_pStg -> CreateStream (pwcsName, grfMode, reserved1, reserved2, ppstm);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(OpenStream) (THIS_ LPCOLESTR pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm)
	{
		TX_TRACE3("%s: Storage::OpenStream(Name: %ls, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
		HRESULT hr = m_pStg -> OpenStream (pwcsName, reserved1, grfMode, reserved2, ppstm);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(CreateStorage) (THIS_ LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg)
	{
		TX_TRACE3("%s: Storage::CreateStorage(Name: %ls, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
		HRESULT hr = m_pStg -> CreateStorage (pwcsName, grfMode, reserved1, reserved2, ppstg);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(OpenStorage) (THIS_ LPCOLESTR pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg)
	{
		TX_TRACE3("%s: Storage::OpenStorage(Name: %ls, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
		HRESULT hr = m_pStg -> OpenStorage (pwcsName, pstgPriority, grfMode, snbExclude, reserved, ppstg);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(CopyTo) (THIS_ DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest)
	{
		TX_TRACE1("%s: Storage::CopyTo(...", m_strName.c_str());
		HRESULT hr = m_pStg -> CopyTo (ciidExclude, rgiidExclude, snbExclude, pstgDest);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(MoveElementTo) (THIS_ LPCOLESTR pwcsName, IStorage *pstgDest, LPCOLESTR lpszNewName, DWORD grfFlags)
	{
		TX_TRACE3("%s: Storage::MoveElementTo(%ls --> %ls ...", m_strName.c_str(), pwcsName, lpszNewName);
		HRESULT hr = m_pStg -> MoveElementTo (pwcsName, pstgDest, lpszNewName, grfFlags);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(Commit) (THIS_ DWORD grfCommitFlags)
	{
		TX_TRACE2("%s: Storage::Commit(grfCommitFlags: %lx", m_strName.c_str(), grfCommitFlags);
		HRESULT hr = m_pStg -> Commit (grfCommitFlags);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(Revert) (THIS)
	{
		TX_TRACE1("%s: Storage::Revert(", m_strName.c_str());
		HRESULT hr = m_pStg -> Revert();
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(EnumElements) (THIS_ DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenm)
	{
		TX_TRACE1("%s: Storage::EnumElements(...", m_strName.c_str());
		HRESULT hr = m_pStg -> EnumElements (reserved1, reserved2, reserved3, ppenm);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(DestroyElement) (THIS_ LPCOLESTR pwcsName)
	{
		TX_TRACE2("%s: Storage::DestroyElement(%ls ...", m_strName.c_str(), pwcsName);
		HRESULT hr = m_pStg -> DestroyElement (pwcsName);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(RenameElement) (THIS_ LPCOLESTR pwcsOldName, LPCOLESTR pwcsNewName) 
	{
		TX_TRACE3("%s: Storage::RenameElement(%ls --> %ls ...", m_strName.c_str(), pwcsOldName, pwcsNewName);
		HRESULT hr = m_pStg -> RenameElement (pwcsOldName, pwcsNewName);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(SetElementTimes) (THIS_ LPCOLESTR lpszName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime)
	{
		TX_TRACE1("%s: Storage::SetElementTimes(...", m_strName.c_str());
		HRESULT hr = m_pStg -> SetElementTimes (lpszName, pctime, patime, pmtime);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(SetClass) (THIS_ REFCLSID clsid)
	{
		TX_TRACE1("%s: Storage::SetClass(...", m_strName.c_str());
		HRESULT hr = m_pStg -> SetClass (clsid);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(SetStateBits) (THIS_ DWORD grfStateBits, DWORD grfMask)
	{
		TX_TRACE1("%s: Storage::SetStateBits(...", m_strName.c_str());
		HRESULT hr = m_pStg -> SetStateBits (grfStateBits, grfMask);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
    STDMETHOD(Stat) (THIS_ STATSTG *pstatstg, DWORD grfStatFlag)
	{
		TX_TRACE1("%s: Storage::Stat(...", m_strName.c_str());
		HRESULT hr = m_pStg -> Stat (pstatstg, grfStatFlag);
		TX_TRACE1(") : %lx\n", hr);
		return hr;
	}
};

#endif // _DEBUG
#endif // !defined(_STGHELP_HXX__0AC6D224_6FA1_11D1_B9EC_080036D63803__INCLUDED_)
