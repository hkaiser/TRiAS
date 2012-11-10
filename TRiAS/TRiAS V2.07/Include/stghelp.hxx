// DebugHelper für Überwachung eines IStream ----------------------------------
// File: STRMHELP.HXX

#if defined(_DEBUG)

#if !defined(_STRMHELP_HXX)
#define _STRMHELP_HXX

#if defined(WIN32)
#include <smartif.h>

DefineSmartInterface(Storage);

class CStorageWrapper : public IStorage {
private:
	DWORD m_dwRefCnt;
	WStorage m_Stg;

public:
		CStorageWrapper (IStorage *pIStg, LPCSTR pcName = NULL)
			: m_Stg (pIStg)
		{
			m_dwRefCnt = 1;
		}
		~CStorageWrapper (void)
		{
		}

	STDMETHODIMP QueryInterface (THIS_ REFIID riid, void ** ppvObject)
	{
		return m_Stg -> QueryInterface (riid, ppvObject);
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

// *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
    STDMETHOD_(ULONG,AddRef) (THIS)  ;
    STDMETHOD_(ULONG,Release) (THIS) ;

// *** IStorage methods ***
    STDMETHOD(CreateStream) (THIS_ LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm);
    STDMETHOD(OpenStream) (THIS_ LPCOLESTR pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm);
    STDMETHOD(CreateStorage) (THIS_ LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg);
    STDMETHOD(OpenStorage) (THIS_ LPCOLESTR pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg);
    STDMETHOD(CopyTo) (THIS_ DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest);
    STDMETHOD(MoveElementTo) (THIS_ LPCOLESTR lpszName, IStorage *pstgDest, LPCOLESTR lpszNewName, DWORD grfFlags);
    STDMETHOD(Commit) (THIS_ DWORD grfCommitFlags);
    STDMETHOD(Revert) (THIS);
    STDMETHOD(EnumElements) (THIS_ DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenm);
    STDMETHOD(DestroyElement) (THIS_ LPCOLESTR pwcsName);
    STDMETHOD(RenameElement) (THIS_ LPCOLESTR pwcsOldName, LPCOLESTR pwcsNewName) ;
    STDMETHOD(SetElementTimes) (THIS_ LPCOLESTR lpszName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime);
    STDMETHOD(SetClass) (THIS_ REFCLSID clsid);
    STDMETHOD(SetStateBits) (THIS_ DWORD grfStateBits, DWORD grfMask);
    STDMETHOD(Stat) (THIS_ STATSTG *pstatstg, DWORD grfStatFlag);
};

#else

typedef const char * LPCOLESTR;

class CStorageWrapper {
private:
	DWORD m_dwRefCnt;
	IStorage *m_pIStorage;
	string m_strName;

public:
		CStorageWrapper (IStorage *pIStorage, LPCSTR pcName = NULL);
		~CStorageWrapper (void);

// *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
    STDMETHOD_(ULONG,AddRef) (THIS);
    STDMETHOD_(ULONG,Release) (THIS);

// *** IStorage methods ***
    STDMETHOD(CreateStream) (THIS_ LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm);
    STDMETHOD(OpenStream) (THIS_ LPCOLESTR pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm);
    STDMETHOD(CreateStorage) (THIS_ LPCOLESTR pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg);
    STDMETHOD(OpenStorage) (THIS_ LPCOLESTR pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg);
    STDMETHOD(CopyTo) (THIS_ DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest);
    STDMETHOD(MoveElementTo) (THIS_ LPCOLESTR lpszName, IStorage *pstgDest, LPCOLESTR lpszNewName, DWORD grfFlags);
    STDMETHOD(Commit) (THIS_ DWORD grfCommitFlags);
    STDMETHOD(Revert) (THIS);
    STDMETHOD(EnumElements) (THIS_ DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenm);
    STDMETHOD(DestroyElement) (THIS_ LPCOLESTR pwcsName);
    STDMETHOD(RenameElement) (THIS_ LPCOLESTR pwcsOldName, LPCOLESTR pwcsNewName) ;
    STDMETHOD(SetElementTimes) (THIS_ LPCOLESTR lpszName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime);
    STDMETHOD(SetClass) (THIS_ REFCLSID clsid);
    STDMETHOD(SetStateBits) (THIS_ DWORD grfStateBits, DWORD grfMask);
    STDMETHOD(Stat) (THIS_ STATSTG *pstatstg, DWORD grfStatFlag);
};                                 

#endif // WIN32

#endif // _STRMHELP_HXX

#endif // _DEBUG
