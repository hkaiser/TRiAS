// DebugHelper für Überwachung eines IStream ----------------------------------
// File: STRMHELP.HXX

#if defined(_DEBUG)

#if !defined(_STRMHELP_HXX)
#define _STRMHELP_HXX


class CStorageWrapper : public IStorage
{
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
    STDMETHOD(CreateStream) (THIS_ const USHORT *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm);
    STDMETHOD(OpenStream) (THIS_ const USHORT *pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm);
    STDMETHOD(CreateStorage) (THIS_ const USHORT *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg);
    STDMETHOD(OpenStorage) (THIS_ const USHORT *pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg);
    STDMETHOD(CopyTo) (THIS_ DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest);
    STDMETHOD(MoveElementTo) (THIS_ const USHORT *lpszName, IStorage *pstgDest, const USHORT *lpszNewName, DWORD grfFlags);
    STDMETHOD(Commit) (THIS_ DWORD grfCommitFlags);
    STDMETHOD(Revert) (THIS);
    STDMETHOD(EnumElements) (THIS_ DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenm);
    STDMETHOD(DestroyElement) (THIS_ const USHORT *pwcsName);
    STDMETHOD(RenameElement) (THIS_ const USHORT *pwcsOldName, const USHORT *pwcsNewName) ;
    STDMETHOD(SetElementTimes) (THIS_ const USHORT *lpszName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime);
    STDMETHOD(SetClass) (THIS_ REFCLSID clsid);
    STDMETHOD(SetStateBits) (THIS_ DWORD grfStateBits, DWORD grfMask);
    STDMETHOD(Stat) (THIS_ STATSTG *pstatstg, DWORD grfStatFlag);
};                                 


#endif // _STRMHELP_HXX

#endif // _DEBUG
