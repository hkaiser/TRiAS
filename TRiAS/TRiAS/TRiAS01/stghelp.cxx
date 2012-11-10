#include "trias01p.hxx"

#if defined(_DEBUG)

#include <stghelp.hxx>

extern void CDECL Trace (LPCSTR lpszFormat, ...);

CStorageWrapper::CStorageWrapper (IStorage *pIStorage, LPCSTR pcName)
	: m_pIStorage (pIStorage), m_strName("")
{
	m_pIStorage -> AddRef();
	m_dwRefCnt = 1;
	if (pcName) m_strName = pcName;

	Trace ("Storage::Storage(pIStr: %lx, Name: %s)\n", pIStorage, m_strName.c_str());
}
CStorageWrapper::~CStorageWrapper (void)
{
	Trace ("%s: Storage::~Storage()\n", m_strName.c_str());
	
	m_pIStorage -> Release();
}

STDMETHODIMP CStorageWrapper::QueryInterface (THIS_ REFIID riid, void ** ppvObject)
{
	Trace ("%s: Storage::QueryInterface(...)\n", m_strName.c_str());
	
	return m_pIStorage -> QueryInterface (riid, ppvObject);
}
STDMETHODIMP_(ULONG) CStorageWrapper::AddRef (THIS)
{
	Trace ("%s: Storage::AddRef()\n", m_strName.c_str());
	
	return ++m_dwRefCnt;
}
STDMETHODIMP_(ULONG) CStorageWrapper::Release (THIS)
{
	Trace ("%s: Storage::Release()\n", m_strName.c_str());
	
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

// *** IStorage methods ***
STDMETHODIMP CStorageWrapper::CreateStream (
	LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm)
{
	Trace ("%s: Storage::CreateStream(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> CreateStream (pwcsName, grfMode, 0, 0, ppstm);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::OpenStream (
	LPCOLESTR pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm)
{
	Trace ("%s: Storage::OpenStream(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> OpenStream (pwcsName, 0, grfMode, 0, ppstm);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::CreateStorage (
	LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg)
{
	Trace ("%s: Storage::CreateStorage(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> CreateStorage (pwcsName, grfMode, 0, 0, ppstg);
	
	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::OpenStorage (
	LPCOLESTR pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg)
{
	Trace ("%s: Storage::OpenStorage(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> OpenStorage (pwcsName, NULL, grfMode, 0, 0, ppstg);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::CopyTo (
	DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest)
{
	Trace ("%s: Storage::CopyTo(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> CopyTo (ciidExclude, rgiidExclude, snbExclude, pstgDest);
	
	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::MoveElementTo (
	LPCOLESTR lpszName, IStorage *pstgDest, LPCOLESTR lpszNewName, DWORD grfFlags)
{
	Trace ("%s: Storage::MoveElementTo(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> MoveElementTo (lpszName, pstgDest, lpszNewName, grfFlags);
	
	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::Commit (THIS_ DWORD grfCommitFlags)
{
	Trace ("%s: Storage::Commit(grfCommitFlags: %lx", m_strName.c_str(), grfCommitFlags);
			
HRESULT hr = m_pIStorage -> Commit (grfCommitFlags);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::Revert (THIS)
{
	Trace ("%s: Storage::Revert(", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> Revert();

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::EnumElements (
	DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenm)
{
	Trace ("%s: Storage::EnumElements(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> EnumElements (0, 0, 0, ppenm);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::DestroyElement (THIS_ LPCOLESTR pwcsName)
{
	Trace ("%s: Storage::DestroyElement(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> DestroyElement (pwcsName);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::RenameElement (
	LPCOLESTR pwcsOldName, LPCOLESTR pwcsNewName)
{
	Trace ("%s: Storage::RenameElement(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> RenameElement (pwcsOldName, pwcsNewName);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::SetElementTimes (
	LPCOLESTR lpszName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime)
{
	Trace ("%s: Storage::SetElementTimes(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> SetElementTimes (lpszName, pctime, patime, pmtime);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::SetClass (THIS_ REFCLSID clsid)
{
	Trace ("%s: Storage::SetClass(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> SetClass (clsid);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::SetStateBits (DWORD grfStateBits, DWORD grfMask)
{
	Trace ("%s: Storage::SetStateBits(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> SetStateBits (grfStateBits, grfMask);

	Trace (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::Stat (STATSTG *pstatstg, DWORD grfStatFlag)
{
	Trace ("%s: Storage::Stat(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> Stat (pstatstg, grfStatFlag);

	Trace (") : %lx\n", hr);
	return hr;
}

#endif // _DEBUG
