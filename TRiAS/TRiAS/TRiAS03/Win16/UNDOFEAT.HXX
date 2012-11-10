// Undo/Redo für ein Merkmal --------------------------------------------------
// File: UNDOFEAT.HXX

#if !defined(_UNDOFEAT_HXX)
#define _UNDOFEAT_HXX

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
// Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);
#endif // _LPFNDESTROY_DEFINED

class CUndoRedoObjectFeature : public IUndoRedoObjectFeature {
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
	bool FInit (LONG lONr, ULONG ulMCode, LPCTSTR pNew, LPCTSTR pOld);

		~CUndoRedoObjectFeature (void);

public:
		CUndoRedoObjectFeature (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoObjectFeature ***
	STDMETHOD(Init)(THIS_ LONG lONr, ULONG ulMCode, 
			LPCTSTR pNew, LPCTSTR pOld /* = NULL */);

// sonstige Member
inline	bool isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (bool fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOFEAT_HXX
