#include "bscriptp.hxx"

#if defined(_DEBUG)

#include "stghelp.hxx"


CStorageWrapper::CStorageWrapper (IStorage *pIStorage, LPCSTR pcName)
	: m_pIStorage (pIStorage), m_strName("")
{
	m_pIStorage -> AddRef();
	m_dwRefCnt = 1;
	if (pcName) m_strName = pcName;

	TRACE ("Storage::Storage(pIStr: %lx, Name: %s)\n", pIStorage, m_strName.c_str());
}
CStorageWrapper::~CStorageWrapper (void)
{
	TRACE ("%s: Storage::~Storage()\n", m_strName.c_str());
	
	m_pIStorage -> Release();
}

STDMETHODIMP CStorageWrapper::QueryInterface (THIS_ REFIID riid, void ** ppvObject)
{
	TRACE ("%s: Storage::QueryInterface(...)\n", m_strName.c_str());
	
	return m_pIStorage -> QueryInterface (riid, ppvObject);
}
STDMETHODIMP_(ULONG) CStorageWrapper::AddRef (THIS)
{
	TRACE ("%s: Storage::AddRef()\n", m_strName.c_str());
	
	return ++m_dwRefCnt;
}
STDMETHODIMP_(ULONG) CStorageWrapper::Release (THIS)
{
	TRACE ("%s: Storage::Release()\n", m_strName.c_str());
	
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

// *** IStorage methods ***
STDMETHODIMP CStorageWrapper::CreateStream (
	const USHORT *  pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm)
{
	TRACE ("%s: Storage::CreateStream(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> CreateStream (pwcsName, grfMode, 0, 0, ppstm);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::OpenStream (
	const USHORT * pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm)
{
	TRACE ("%s: Storage::OpenStream(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> OpenStream (pwcsName, 0, grfMode, 0, ppstm);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::CreateStorage (
	const USHORT * pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg)
{
	TRACE ("%s: Storage::CreateStorage(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> CreateStorage (pwcsName, grfMode, 0, 0, ppstg);
	
	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::OpenStorage (
	const USHORT * pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg)
{
	TRACE ("%s: Storage::OpenStorage(Name: %s, grfMode: %xd", m_strName.c_str(), pwcsName, grfMode);
			
HRESULT hr = m_pIStorage -> OpenStorage (pwcsName, NULL, grfMode, 0, 0, ppstg);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::CopyTo (
	DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest)
{
	TRACE ("%s: Storage::CopyTo(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> CopyTo (ciidExclude, rgiidExclude, snbExclude, pstgDest);
	
	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::MoveElementTo (
	const USHORT * lpszName, IStorage *pstgDest, const USHORT * lpszNewName, DWORD grfFlags)
{
	TRACE ("%s: Storage::MoveElementTo(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> MoveElementTo (lpszName, pstgDest, lpszNewName, grfFlags);
	
	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::Commit (THIS_ DWORD grfCommitFlags)
{
	TRACE ("%s: Storage::Commit(grfCommitFlags: %lx", m_strName.c_str(), grfCommitFlags);
			
HRESULT hr = m_pIStorage -> Commit (grfCommitFlags);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::Revert (THIS)
{
	TRACE ("%s: Storage::Revert(", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> Revert();

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::EnumElements (
	DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenm)
{
	TRACE ("%s: Storage::EnumElements(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> EnumElements (0, 0, 0, ppenm);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::DestroyElement (THIS_ const USHORT * pwcsName)
{
	TRACE ("%s: Storage::DestroyElement(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> DestroyElement (pwcsName);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::RenameElement (
	const USHORT * pwcsOldName, const USHORT *  pwcsNewName)
{
	TRACE ("%s: Storage::RenameElement(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> RenameElement (pwcsOldName, pwcsNewName);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::SetElementTimes (
	const USHORT *  lpszName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime)
{
	TRACE ("%s: Storage::SetElementTimes(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> SetElementTimes (lpszName, pctime, patime, pmtime);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::SetClass (THIS_ REFCLSID clsid)
{
	TRACE ("%s: Storage::SetClass(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> SetClass (clsid);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::SetStateBits (DWORD grfStateBits, DWORD grfMask)
{
	TRACE ("%s: Storage::SetStateBits(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> SetStateBits (grfStateBits, grfMask);

	TRACE (") : %lx\n", hr);
	return hr;
}
STDMETHODIMP CStorageWrapper::Stat (STATSTG *pstatstg, DWORD grfStatFlag)
{
	TRACE ("%s: Storage::Stat(...", m_strName.c_str());
			
HRESULT hr = m_pIStorage -> Stat (pstatstg, grfStatFlag);

	TRACE (") : %lx\n", hr);
	return hr;
}

#endif // _DEBUG
