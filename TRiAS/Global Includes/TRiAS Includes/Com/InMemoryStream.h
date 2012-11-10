// @doc 
// @module InMemoryStream.h | In-memory implementation of IStream

#if !defined(_INMEMORYSTREAM_H__E41F1421_CB3D_11D2_9BA6_006008447800__INCLUDED_)
#define _INMEMORYSTREAM_H__E41F1421_CB3D_11D2_9BA6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/MemoryHelper.h>

/////////////////////////////////////////////////////////////////////////////
// spezielles InitialisierungsInterface
MIDL_INTERFACE("A741369A-CBB9-11D2-9BA7-006008447800")
IStreamOnTaskMem : IUnknown
{
	STDMETHOD(Initialize)(BYTE *pBytes, BOOL fDeleteOnRelease) = 0;
	STDMETHOD(GetBytes)(BOOL fDetach, BYTE **pBytes) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CInMemoryStream
class ATL_NO_VTABLE CInMemoryStream : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public IStream,
	public IStreamOnTaskMem
{
public:
	CInMemoryStream() :
		m_ulSeekPos(0), m_fIsOwner(FALSE)
	{
	}
	~CInMemoryStream()
	{
		if (!m_fIsOwner)
			m_Mem.Detach();
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CInMemoryStream)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CInMemoryStream)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInMemoryStream)
		COM_INTERFACE_ENTRY(IStream)
		COM_INTERFACE_ENTRY(ISequentialStream)
		COM_INTERFACE_ENTRY(IStreamOnTaskMem)
	END_COM_MAP()

	STDMETHOD(Initialize)(BYTE *pv, BOOL fDeleteOnRelease)
	{
#if defined(_DEBUG)
		_ASSERTE(NULL == m_Mem.Attach (pv));
#else
		m_Mem.Attach (pv);
#endif
		if ((ULONG)-1 == GetSize())
			return E_UNEXPECTED;

		m_fIsOwner = fDeleteOnRelease;
		return S_OK;
	}
	STDMETHOD(GetBytes)(BOOL fDetach, BYTE **pBytes)
	{
		if (NULL != pBytes)
			*pBytes = NULL;
		else
			return E_POINTER;
		*pBytes = GetItems();
		if (fDetach)
			m_fIsOwner = FALSE;
		return S_OK;
	}

// IStream
public:
	STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
	{
		if (NULL != plibNewPosition && IsBadWritePtr ((void *)plibNewPosition, sizeof(ULARGE_INTEGER)))
			return STG_E_INVALIDPOINTER;

		switch (dwOrigin) {
		case STREAM_SEEK_SET:
		// Interpret as unsigned
			m_ulSeekPos = dlibMove.LowPart;
			break;

		case STREAM_SEEK_CUR:
			m_ulSeekPos += (LONG)dlibMove.LowPart;
			break;

		case STREAM_SEEK_END:
			m_ulSeekPos = GetSize() + (LONG)dlibMove.LowPart;
			break;

		default:
			return STG_E_INVALIDFUNCTION;
		}

	// Can't seek past the beginning, but the seek position can be past the end
		if (m_ulSeekPos < 0)
			m_ulSeekPos = 0;
		if (plibNewPosition)
			ULISet32(*plibNewPosition, m_ulSeekPos);
		return S_OK;
	}
	STDMETHOD(SetSize)(ULARGE_INTEGER libNewSize)
	{
		if (0 != libNewSize.HighPart)
			return STG_E_INVALIDFUNCTION;

		if (libNewSize.LowPart == (ULONG)GetSize())
			return S_OK;

		if (SUCCEEDED(SetSize (libNewSize.LowPart))) {
			if (m_ulSeekPos >= GetSize())
				m_ulSeekPos = GetSize()-1;
			return S_OK;
		}
		return STG_E_MEDIUMFULL;
	}
	STDMETHOD(CopyTo)(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
	{
		if (NULL == pstm)
			return STG_E_INVALIDPOINTER;

	// pcbWritten can be NULL
		if (NULL != pcbWritten && IsBadWritePtr ((void *)pcbWritten, sizeof(ULONG)))
			return STG_E_INVALIDPOINTER;

	// pcbRead can be NULL
		if (NULL != pcbRead && IsBadWritePtr ((void *)pcbRead, sizeof(ULONG)))
			return STG_E_INVALIDPOINTER;

	ULONG uWritten = 0;
	ULONG uRead = 0;
	HRESULT hr = S_OK;

		if (0 != cb.LowPart) {
		// Check for reading past the end
			if ((int)(m_ulSeekPos + cb.LowPart) > GetSize()) {
				if (m_ulSeekPos >= GetSize())
					hr = S_FALSE;
				else
					uRead = GetSize()-m_ulSeekPos;
			} else
				uRead = cb.LowPart;

			if (S_OK == hr) {
			// Write data to other stream and increment seek if successful
				hr = pstm->Write ((void *)(GetItems() + m_ulSeekPos), uRead, &uWritten);
				if (SUCCEEDED(hr))
					m_ulSeekPos += uRead;
			}
		}
		if (pcbRead)
			ULISet32(*pcbRead, uRead);
		if (pcbWritten)
			ULISet32(*pcbWritten, uWritten);
		return hr;
	}
	STDMETHOD(Commit)(DWORD grfCommitFlags)
	{
		return S_OK;
	}
	STDMETHOD(Revert)(void)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(LockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(UnlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Stat)(STATSTG *pstatstg, DWORD grfStatFlag)
	{
		if (NULL == pstatstg || IsBadWritePtr (pstatstg, sizeof(STATSTG)))
			return STG_E_INVALIDPOINTER;

		ZeroMemory(pstatstg, sizeof(STATSTG));
		pstatstg -> type = STGTY_LOCKBYTES;
		ULISet32(pstatstg -> cbSize, GetSize());
		return S_OK;
	}
	STDMETHOD(Clone)(IStream **ppstm)
	{
		if (NULL == ppstm)
			return E_POINTER;
		else
			*ppstm = NULL;

	CComObject<CInMemoryStream> *pStream;
	HRESULT hr = CComObject<CInMemoryStream>::CreateInstance (&pStream);

		if (FAILED(hr)) return hr;

	__Interface<IStream> strm (pStream);

		if (SUCCEEDED(pStream -> SetSize (GetSize()))) {
			CopyMemory((void *)GetItems(), (void *)pStream -> GetItems(), GetSize());
			*ppstm = strm.detach();

		LARGE_INTEGER li;
		
			LISet32 (li, m_ulSeekPos);
			return pStream -> Seek (li, STREAM_SEEK_SET, NULL);
		}
		return E_OUTOFMEMORY;
	}

// ISequentialStream
	STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead)
	{
	// Must have buffer
		if (NULL == pv || IsBadWritePtr (pv, cb))
			return STG_E_INVALIDPOINTER;

	// pcbRead can be NULL
	ULONG uRead;

		if (NULL == pcbRead)
			pcbRead = &uRead;
		else if (IsBadWritePtr ((void *)pcbRead, sizeof(ULONG)))
			return STG_E_INVALIDPOINTER;

	// Check for end of file
		if (m_ulSeekPos >= GetSize()) {
			*pcbRead = 0;
			return S_FALSE;
		} else {
		// Check for reading past the end
			if ((int)(m_ulSeekPos+cb) > GetSize())
				*pcbRead = GetSize()-m_ulSeekPos;
			else
				*pcbRead = cb;

		// Copy data to outbound buffer and increment seek
			CopyMemory(pv, (void*)(GetItems()+m_ulSeekPos), *pcbRead);
			m_ulSeekPos += *pcbRead;
		}
		return S_OK;
	}
	STDMETHOD(Write)(const void *pv, ULONG cb, ULONG *pcbWritten)
	{
	// Must have buffer
		if (NULL == pv || IsBadReadPtr (pv, cb))
			return STG_E_INVALIDPOINTER;

	// pcbWritten can be NULL
	ULONG uWritten;

		if (NULL == pcbWritten)
			pcbWritten = &uWritten;
		else if (IsBadWritePtr ((void *)pcbWritten, sizeof(ULONG)))
			return STG_E_INVALIDPOINTER;

		*pcbWritten = 0;
		if (0 != cb) {
		// Expand the storage buffer
			if (SUCCEEDED(SetSize(m_ulSeekPos+cb))) {
			// Copy data and increment seek
				CopyMemory((void *)(GetItems()+m_ulSeekPos), pv, cb);
				m_ulSeekPos += cb;
				*pcbWritten = cb;
			} else
				return STG_E_MEDIUMFULL;
		}
		return S_OK;
	}

protected:
	ULONG GetSize() const { return m_Mem.GetSize(); }
	BYTE *GetItems() { return static_cast<BYTE *>(m_Mem); }
	HRESULT SetSize (ULONG ulNewSize) { return m_Mem.SetSize (ulNewSize); }

private:
	ULONG m_ulSeekPos;
	BOOL m_fIsOwner;
	CMallocMem<BYTE> m_Mem; 
};

///////////////////////////////////////////////////////////////////////////////
// usefull API-functions
inline
HRESULT CreateStreamOnTaskMem (void *pv, BOOL fDeleteOnRelease, IStream **ppIStrm)
{
	if (NULL == ppIStrm)
		return E_POINTER;
	else
		*ppIStrm = NULL;

CComObject<CInMemoryStream> *pStream = NULL;
HRESULT hr = CComObject<CInMemoryStream>::CreateInstance (&pStream);

	if (SUCCEEDED(hr)) {
		pStream -> Initialize(static_cast<BYTE *>(pv), fDeleteOnRelease);
		(*ppIStrm = static_cast<IStream *>(pStream)) -> AddRef();
	}
	return hr;
}

inline
HRESULT GetTaskMemFromStream (IStream *pIStrm, BOOL fDetach, void **ppvBits)
{
	if (NULL == pIStrm)
		return E_POINTER;

__Interface<IStreamOnTaskMem> strm;
HRESULT hr = pIStrm -> QueryInterface (strm.ppi());

	if (SUCCEEDED(hr)) 
		hr = strm -> GetBytes (fDetach, reinterpret_cast<BYTE **>(ppvBits));
	return hr;
}

#endif // !defined(_INMEMORYSTREAM_H__E41F1421_CB3D_11D2_9BA6_006008447800__INCLUDED_)
