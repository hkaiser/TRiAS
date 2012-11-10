#include "trias01p.hxx"

#if defined(_DEBUG)

#include <strmhelp.hxx>
#include <stdarg.h>

void CDECL Trace (LPCSTR lpszFormat, ...)
{
va_list args;
va_start(args, lpszFormat);
TCHAR szBuffer[512]; 

	vsprintf(szBuffer, lpszFormat, args);
	OutputDebugString (szBuffer);

	va_end(args);
}

CStreamWrapper::CStreamWrapper (IStream *pIStream, LPCSTR pcName)
	: m_pIStream (pIStream), m_strName("")
{
	m_pIStream -> AddRef();
	m_dwRefCnt = 1;
	if (pcName) m_strName = pcName;

	Trace ("Stream::Stream(pIStr: %lx, Name: %s)\n", pIStream, m_strName.c_str());
}
CStreamWrapper::~CStreamWrapper (void)
{
	Trace ("%s: Stream::~Stream()\n", m_strName.c_str());
	
	m_pIStream -> Release();
}

STDMETHODIMP CStreamWrapper::QueryInterface (THIS_ REFIID riid, void ** ppvObject)
{
	Trace ("%s: Stream::QueryInterface(...)\n", m_strName.c_str());
	
	return m_pIStream -> QueryInterface (riid, ppvObject);
}
STDMETHODIMP_(ULONG) CStreamWrapper::AddRef (THIS)
{
	Trace ("%s: Stream::AddRef()\n", m_strName.c_str());
	
	return ++m_dwRefCnt;
}
STDMETHODIMP_(ULONG) CStreamWrapper::Release (THIS)
{
	Trace ("%s: Stream::Release()\n", m_strName.c_str());
	
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

// *** IStream methods ***
STDMETHODIMP CStreamWrapper::Read (THIS_ void * pv, ULONG cb, ULONG * pcbRead)
{
	Trace ("%s: Stream::Read(pv: %lx, cb: %ld", m_strName.c_str(), pv, cb);
			
HRESULT hr = m_pIStream -> Read (pv, cb, pcbRead);

	if (pcbRead)
		Trace (", cbRead: %ld) : %lx\n", *pcbRead, hr);
	else
		Trace (", cbRead: NULL) : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::Write (THIS_ VOID const * pv, ULONG cb, ULONG * pcbWritten)
{
	Trace ("%s: Stream::Write(pv: %lx, cb: %ld", m_strName.c_str(), pv, cb);
			
HRESULT hr = m_pIStream -> Write (pv, cb, pcbWritten);

	if (pcbWritten)
		Trace (", cbWritten: %ld) : %lx\n", *pcbWritten, hr);
	else
		Trace (", cbWritten: NULL) : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::Seek (THIS_ LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER * plibNewPosition)
{
	Trace ("%s: Stream::Seek(dlibMove: %lx, dwOrigin: %ld", m_strName.c_str(), dlibMove.LowPart, dwOrigin);
			
HRESULT hr = m_pIStream -> Seek (dlibMove, dwOrigin, plibNewPosition);
	
	if (plibNewPosition)
		Trace (", libNewPosition: %ld) : %lx\n", plibNewPosition -> LowPart, hr);
	else
		Trace (", libNewPosition: NULL) : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::SetSize (THIS_ ULARGE_INTEGER libNewSize)
{
	Trace ("%s: Stream::SetSize(libNewSize: %lx", m_strName.c_str(), libNewSize.LowPart);
			
HRESULT hr = m_pIStream -> SetSize (libNewSize);

	Trace (") : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::CopyTo (THIS_ IStream * pStm, ULARGE_INTEGER cb, ULARGE_INTEGER * pcbRead, ULARGE_INTEGER * pcbWritten)
{
	Trace ("%s: Stream::CopyTo(pStm: %lx, cb", m_strName.c_str(), cb.LowPart);
			
HRESULT hr = m_pIStream -> CopyTo (pStm, cb, pcbRead, pcbWritten);
	
	if (pcbRead)
		Trace (", cbRead: %ld", pcbRead -> LowPart);
	else
		Trace (", cbRead: NULL");
	if (pcbWritten)
		Trace (", cbWritten: %ld) : %lx\n", pcbWritten -> LowPart, hr);
	else
		Trace (", cbWritten: NULL) : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::Commit (THIS_ DWORD grfCommitFlags)
{
	Trace ("%s: Stream::Commit(grfCommitFlags: %lx", m_strName.c_str(), grfCommitFlags);
			
HRESULT hr = m_pIStream -> Commit (grfCommitFlags);

	Trace (") : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::Revert (THIS)
{
	Trace ("%s: Stream::Revert(", m_strName.c_str());
			
HRESULT hr = m_pIStream -> Revert();

	Trace (") : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::LockRegion (THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	Trace ("%s: Stream::LockRegion(...", m_strName.c_str());
			
HRESULT hr = m_pIStream -> LockRegion (libOffset, cb, dwLockType);

	Trace (") : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::UnlockRegion (THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	Trace ("%s: Stream::UnlockRegion(...", m_strName.c_str());
			
HRESULT hr = m_pIStream -> UnlockRegion (libOffset, cb, dwLockType);

	Trace (") : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::Stat (THIS_ STATSTG * pstatstg, DWORD grfStatFlag)
{
	Trace ("%s: Stream::Stat(...", m_strName.c_str());
			
HRESULT hr = m_pIStream -> Stat (pstatstg, grfStatFlag);

	Trace (") : %lx\n", hr);

	return hr;
}
STDMETHODIMP CStreamWrapper::Clone (THIS_ IStream ** ppstm)
{
	Trace ("%s: Stream::Clone(...", m_strName.c_str());
			
HRESULT hr = m_pIStream -> Clone (ppstm);

	Trace (") : %lx\n", hr);

	return hr;
}

#endif // _DEBUG
