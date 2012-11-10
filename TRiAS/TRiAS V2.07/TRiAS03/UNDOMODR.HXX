// Undo/Redo für Relation erzeugen --------------------------------------------
// File: UNDOMODR.HXX

#if !defined(_UNDOMODR_HXX)
#define _UNDOMODR_HXX

class CUndoRedoCreateObjectRelation : public IUndoRedoCreateObjectRelation {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	MODRELATION m_mrObj;		// identisch mit DELRELATION

protected:
	BOOL FInit (LONG lONr, LONG lSecONr, ULONG ulRCode, short iRTyp);

		~CUndoRedoCreateObjectRelation (void);

public:
		CUndoRedoCreateObjectRelation (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoCreateRelation ***
	STDMETHOD(Init)(THIS_ LONG lONr, LONG lSecONr, ULONG ulRCode, short iRTyp);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOMODR_HXX
