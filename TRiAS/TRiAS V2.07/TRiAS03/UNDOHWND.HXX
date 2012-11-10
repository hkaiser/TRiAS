// Undo/Redo für Objekt aus OR-Fenster entfernen ------------------------------
// File: UNDOHWND.HXX

#if !defined(_UNDOHWND_HXX)
#define _UNDOHWND_HXX

///////////////////////////////////////////////////////////////////////////////
//
class CUndoRedoDeleteObjectWnd : 
	public IUndoRedoDeleteObjectWnd 
{
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	HWND m_hWnd;		// FensterHandle des ORFensters
	LONG m_lONr;		// ObjektNummer
	unsigned int m_fSelected : 1;
	unsigned int m_fActivated : 1;

protected:
	BOOL FInit (HWND hWnd, LONG lONr);

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
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
//
class CUndoRedoReplaceObjectWnd : 
	public IUndoRedoReplaceObjectWnd 
{
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	HWND m_hWnd;		// FensterHandle des ORFensters
	LONG m_lONr;		// ObjektNummer
	LONG m_lNewONr;		// neue Objektnummer

protected:
	BOOL FInit (HWND hWnd, LONG lONr, LONG lNewONr);

		~CUndoRedoReplaceObjectWnd (void);

public:
		CUndoRedoReplaceObjectWnd (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr, LONG lNewONr);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
//
class CUndoRedoAddToObjectWnd : 
	public IUndoRedoAddToObjectWnd 
{
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	HWND m_hWnd;		// FensterHandle des ORFensters
	LONG m_lONr;		// ObjektNummer
	unsigned int m_fSelected : 1;
	unsigned int m_fActivated : 1;

protected:
	BOOL FInit (HWND hWnd, LONG lONr);

		~CUndoRedoAddToObjectWnd (void);

public:
		CUndoRedoAddToObjectWnd (LPFNDESTROYED pfnDestroy);

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
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOHWND_HXX
