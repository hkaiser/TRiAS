// Undo/Redo für ein Merkmal --------------------------------------------------
// File: UNDOFEAT.HXX

#if !defined(_UNDOFEAT_HXX)
#define _UNDOFEAT_HXX

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
// Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);
#endif // _LPFNDESTROY_DEFINED

class CUndoRedoObjectFeature : 
	public IUndoRedoObjectFeature, 
	public IPropagateObjectNumber
{
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	LONG m_lONr;		// ObjektNummer
	ULONG m_ulMCode;	// MerkmalsCode
	string m_strOld;	// alter MerkmalsWert
	string m_strNew;	// neuer MerkmalsWert
	int m_iMkBase;		// ZahlenBasis des MerkmalsCodes

protected:
	BOOL FInit (HOBJECT lONr, HFEATURE ulMCode, LPCTSTR pNew, LPCTSTR pOld);

		~CUndoRedoObjectFeature (void);

public:
		CUndoRedoObjectFeature (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoObjectFeature ***
	STDMETHOD(Init)(THIS_ HOBJECT lONr, HFEATURE ulMCode, LPCTSTR pNew, LPCTSTR pOld /* = NULL */);

// *** IPropagateObjectNumber
	STDMETHOD(GetUndoObjectNumber) (THIS_ HOBJECT *plONr);
	STDMETHOD(SetUndoObjectNumber) (THIS_ HOBJECT lONr);
	STDMETHOD(GetRedoObjectNumber) (THIS_ HOBJECT *plONr);
	STDMETHOD(SetRedoObjectNumber) (THIS_ HOBJECT lONr);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOFEAT_HXX
