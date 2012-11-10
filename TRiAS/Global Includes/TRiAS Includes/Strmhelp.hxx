// DebugHelper für Überwachung eines IStream ----------------------------------
// File: STRMHELP.HXX

#if defined(_DEBUG)

#if !defined(_STRMHELP_HXX)
#define _STRMHELP_HXX

#if !defined(WIN16)
#include <ospace/com/smartif.h>

DefineSmartInterface(Stream);

class CStreamWrapper : public IStream {
private:
	DWORD m_dwRefCnt;
	WStream m_Stream;

public:
		CStreamWrapper (IStream *pIStream, LPCSTR pcName = NULL)
			: m_Stream (pIStream)
		{
			m_dwRefCnt = 1;
		}
		~CStreamWrapper (void)
		{
		}

	STDMETHODIMP QueryInterface (THIS_ REFIID riid, void ** ppvObject)
	{
		return m_Stream -> QueryInterface (riid, ppvObject);
	}
	STDMETHODIMP_(ULONG) AddRef (THIS)
	{
		return ++m_dwRefCnt;
	}
	STDMETHODIMP_(ULONG) Release (THIS)
	{
		if (--m_dwRefCnt == 0) {
			delete this;
			return 0L;
		}

	return m_dwRefCnt;
	}

// *** IStream methods ***
	STDMETHODIMP Read (THIS_ void * pv, ULONG cb, ULONG * pcbRead)
	{
		return m_Stream -> Read (pv, cb, pcbRead);
	}
	STDMETHODIMP Write (THIS_ VOID const * pv, ULONG cb, ULONG * pcbWritten)
	{
		return m_Stream -> Write (pv, cb, pcbWritten);
	}
	STDMETHODIMP Seek (THIS_ LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER * plibNewPosition)
	{
		return m_Stream -> Seek (dlibMove, dwOrigin, plibNewPosition);
	}
	STDMETHODIMP SetSize (THIS_ ULARGE_INTEGER libNewSize)
	{
		return m_Stream -> SetSize (libNewSize);
	}
	STDMETHODIMP CopyTo (THIS_ IStream * pStm, ULARGE_INTEGER cb, ULARGE_INTEGER * pcbRead, ULARGE_INTEGER * pcbWritten)
	{
		return m_Stream -> CopyTo (pStm, cb, pcbRead, pcbWritten);
	}
	STDMETHODIMP Commit (THIS_ DWORD grfCommitFlags)
	{
		return m_Stream -> Commit (grfCommitFlags);
	}
	STDMETHODIMP Revert (THIS)
	{
		return m_Stream -> Revert();
	}
	STDMETHODIMP LockRegion (THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return m_Stream -> LockRegion (libOffset, cb, dwLockType);
	}
	STDMETHODIMP UnlockRegion (THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
	{
		return m_Stream -> UnlockRegion (libOffset, cb, dwLockType);
	}
	STDMETHODIMP Stat (THIS_ STATSTG * pstatstg, DWORD grfStatFlag)
	{
		return m_Stream -> Stat (pstatstg, grfStatFlag);
	}
	STDMETHODIMP Clone (THIS_ IStream ** ppstm)
	{
		return m_Stream -> Clone (ppstm);
	}
};

#else

class CStreamWrapper {
private:
	DWORD m_dwRefCnt;
	IStream *m_pIStream;
	string m_strName;

public:
		CStreamWrapper (IStream *pIStream, LPCSTR pcName = NULL);
		~CStreamWrapper (void);

	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void ** ppvObject);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

// *** IStream methods ***
	STDMETHOD(Read)(THIS_ void * pv, ULONG cb, ULONG * pcbRead);
	STDMETHOD(Write)(THIS_ VOID const * pv, ULONG cb, ULONG * pcbWritten);
	STDMETHOD(Seek)(THIS_ LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER * plibNewPosition);
	STDMETHOD(SetSize)(THIS_ ULARGE_INTEGER libNewSize);
	STDMETHOD(CopyTo)(THIS_ IStream * pStm, ULARGE_INTEGER cb, ULARGE_INTEGER * pcbRead, ULARGE_INTEGER * pcbWritten);
	STDMETHOD(Commit)(THIS_ DWORD grfCommitFlags);
	STDMETHOD(Revert)(THIS);
	STDMETHOD(LockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHOD(UnlockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHOD(Stat)(THIS_ STATSTG * pstatstg, DWORD grfStatFlag);
	STDMETHOD(Clone)(THIS_ IStream ** ppstm);
};                                 

#endif // WIN16

#endif // _STRMHELP_HXX

#endif // _DEBUG
