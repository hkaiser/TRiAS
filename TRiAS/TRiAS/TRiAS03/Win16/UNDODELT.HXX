// Undo/Redo für TextObjekt löschen -------------------------------------------
// File: UNDODELT.HXX

#if !defined(_UNDODELT_HXX)
#define _UNDODELT_HXX

class CUndoRedoDeleteTextObject : public IUndoRedoDeleteText {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	TEXTGEOMETRIE m_tgText;
	string m_strText;
	POINTL m_ptlText;
	RECT m_rcText;
	unsigned int m_fRect : 1;

protected:
	bool FInit (LONG lONr, LPCRECT prc);

		~CUndoRedoDeleteTextObject (void);

public:
		CUndoRedoDeleteTextObject (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteText ***
	STDMETHOD(Init)(THIS_ LONG lONr, LPCRECT prc /* = NULL */);

// sonstige Member
inline	bool isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (bool fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDODELT_HXX
