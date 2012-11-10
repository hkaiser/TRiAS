// Undo/Redo für TextObjekt löschen -------------------------------------------
// File: UNDOMODO.HXX

#if !defined(_UNDOMODO_HXX)
#define _UNDOMODO_HXX

class CUndoRedoModifyObject : public IUndoRedoModifyObject {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	OBJGEOMETRIE m_ogOld;
	OBJGEOMETRIE m_ogNew;

	string m_strText;
	RECT m_rcObj;
	unsigned int m_fRect : 1;

protected:
	bool FInit (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc);

		~CUndoRedoModifyObject (void);

public:
		CUndoRedoModifyObject (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteText ***
	STDMETHOD(Init)(THIS_ LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc /* = NULL */);

// sonstige Member
inline	bool isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (bool fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOMODO_HXX
