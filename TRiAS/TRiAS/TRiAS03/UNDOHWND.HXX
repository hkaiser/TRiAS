// Undo/Redo für Objekt aus OR-Fenster entfernen ------------------------------
// File: UNDOHWND.HXX

#if !defined(_UNDOHWND_HXX)
#define _UNDOHWND_HXX

///////////////////////////////////////////////////////////////////////////////
//
class CUndoRedoDeleteObjectWnd : 
	public IUndoRedoDeleteObjectWnd,
	public IPropagateObjectNumber 
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
	BOOL FInit2 (HWND hWnd, LONG lONr, BOOL fSelected, BOOL fActivated);

		~CUndoRedoDeleteObjectWnd (void);

public:
		CUndoRedoDeleteObjectWnd (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IPropagateObjectNumber
	STDMETHOD(GetUndoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetUndoObjectNumber) (THIS_ INT_PTR lONr);
	STDMETHOD(GetRedoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetRedoObjectNumber) (THIS_ INT_PTR lONr);

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr);
	STDMETHOD(Init2)(THIS_ HWND hWnd, LONG lONr, BOOL fSelected, BOOL fActivated);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
//
class CUndoRedoReplaceObjectWnd : 
	public IUndoRedoReplaceObjectWnd, 
	public IPropagateObjectNumber 
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
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr, LONG lNewONr);

// *** IPropagateObjectNumber
	STDMETHOD(GetUndoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetUndoObjectNumber) (THIS_ INT_PTR lONr);
	STDMETHOD(GetRedoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetRedoObjectNumber) (THIS_ INT_PTR lONr);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
//
class CUndoRedoAddToObjectWnd : 
	public IUndoRedoAddToObjectWnd, 
	public IPropagateObjectNumber 
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
	BOOL FInit2 (HWND hWnd, LONG lONr, BOOL fSelected, BOOL fActivated);

		~CUndoRedoAddToObjectWnd (void);

public:
		CUndoRedoAddToObjectWnd (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr);
	STDMETHOD(Init2)(THIS_ HWND hWnd, LONG lONr, BOOL fSelected, BOOL fActivated);

// *** IPropagateObjectNumber
	STDMETHOD(GetUndoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetUndoObjectNumber) (THIS_ INT_PTR lONr);
	STDMETHOD(GetRedoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetRedoObjectNumber) (THIS_ INT_PTR lONr);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOHWND_HXX
