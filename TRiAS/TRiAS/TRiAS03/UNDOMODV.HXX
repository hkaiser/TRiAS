// Undo/Redo für TextObjekt löschen -------------------------------------------
// File: UNDOMODV.HXX

#if !defined(_UNDOMODV_HXX)
#define _UNDOMODV_HXX

class CUndoRedoVisInfo : public IUndoRedoVisInfo {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	HANDLEVISINFO m_viOld;
	HANDLEVISINFO m_viNew;

protected:
	BOOL FInit (const HANDLEVISINFO *pVINew, const HANDLEVISINFO *pVIOld);

		~CUndoRedoVisInfo (void);

public:
		CUndoRedoVisInfo (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteText ***
	STDMETHOD(Init)(THIS_ const HANDLEVISINFO *pVINew, 
						  const HANDLEVISINFO *pVIOld/* = NULL */);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOMODV_HXX
