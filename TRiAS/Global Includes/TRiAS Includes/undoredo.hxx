// Implementation des IUndoRedo (BasisKlasse) ---------------------------------
// File: UNDOREDO.HXX

#if !defined(_UNDOREDO_HXX)
#define _UNDOREDO_HXX

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
// Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);
#endif // _LPFNDESTROY_DEFINED

class CUndoRedo : 
	public IUndoRedo
{
private:
	DWORD m_dwRefCnt;					// ReferenzZähler
	GUID m_IID;							// unterstützter GUID
	LPFNDESTROYED m_pfnDestroy;			// bei zerlegen rufen
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

protected:
// diese Klasse soll wirklich nur als Basisklasse fungieren
		CUndoRedo (REFIID riid, LPFNDESTROYED pfnDestroy);
	virtual ~CUndoRedo (void);

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};


// UndoRedo, der mehrere separate Undoredo's enthält und verwaltet ------------
class CEnumUndoRedo;

class CUndoRedoList : 
	public IUndoRedoList,
	public IPropagateObjectNumber 
{
private:
	DWORD m_dwRefCnt;		// reference count

	CEnumUndoRedo m_UndoList;	// Liste der UndoRedo's

	DWORD m_dwCaps;			// gemeinsame Capabilities
	string m_strDesc;		// Beschreibungs-String

	LONG m_lUndoONr;
	LONG m_lRedoONr;

protected:
	BOOL FInit (void);

		CUndoRedoList (LPCTSTR, int iCnt);
		~CUndoRedoList (void);

public:
// Objekt nur dynamisch über CreateInstance zu erzeugen
static CUndoRedoList *CreateInstance (LPCTSTR pDesc, int iCnt);

// diverse HelperFunktionen, die auf Container direkt zugreifen
	void EveryDelete (void);
	HRESULT Clone (LPENUMUNKNOWN *ppEnum);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoList methods ***
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(AddUndoRedo)(THIS_ LPUNDOREDO pIUndoRedo);
	STDMETHOD_(DWORD, Undo)(THIS_ LONG lNum, LPUNDOREDOLIST pIRedoList);
	STDMETHOD_(DWORD, Redo)(THIS_ LONG lNum, LPUNDOREDOLIST pIUndoList);

// *** IPropagateObjectNumber
	STDMETHOD(GetUndoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetUndoObjectNumber) (THIS_ INT_PTR lONr);
	STDMETHOD(GetRedoObjectNumber) (THIS_ INT_PTR *plONr);
	STDMETHOD(SetRedoObjectNumber) (THIS_ INT_PTR lONr);
};

// HelperFunktion für Kombination mehrerer cap's verschiedener Undo's ---------
inline DWORD CombineCaps (DWORD dwCaps, DWORD dwNew)
{
	dwCaps |= dwNew & UNDOREDOCAPS_ORFLAGS;
	dwCaps &= ((dwNew & UNDOREDOCAPS_ANDFLAGS) | UNDOREDOCAPS_ORFLAGS);
	return dwCaps;
}

#endif // _UNDOREDO_HXX
