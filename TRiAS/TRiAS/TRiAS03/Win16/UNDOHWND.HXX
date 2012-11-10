// Undo/Redo für Objekt aus OR-Fenster entfernen ------------------------------
// File: UNDOHWND.HXX

#if !defined(_UNDOHWND_HXX)
#define _UNDOHWND_HXX

class CUndoRedoDeleteObjectWnd : public IUndoRedoDeleteObjectWnd {
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	HWND m_hWnd;		// FensterHandle des ORFensters
	LONG m_lONr;		// ObjektNummer
	unsigned int m_fSelected : 1;
	unsigned int m_fActivated : 1;

protected:
	bool FInit (HWND hWnd, LONG lONr);

		~CUndoRedoDeleteObjectWnd (void);

public:
		CUndoRedoDeleteObjectWnd (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr);

// sonstige Member
inline	bool isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (bool fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOHWND_HXX
