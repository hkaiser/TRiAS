// Undo/Redo für Relation löschen ---------------------------------------------
// File: UNDODELR.HXX

#if !defined(_UNDODELR_HXX)
#define _UNDODELR_HXX

class CUndoRedoDeleteObjectRelation : public IUndoRedoDeleteObjectRelation {
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	MODRELATION m_mrObj;		// identisch mit DELRELATION

protected:
	bool FInit (LONG lONr, LONG lSecONr, ULONG ulRCode, short iRTyp);

		~CUndoRedoDeleteObjectRelation (void);

public:
		CUndoRedoDeleteObjectRelation (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteObjectRelation ***
	STDMETHOD(Init)(THIS_ LONG lONr, LONG lSecONr, ULONG ulRCode, short iRTyp);

// sonstige Member
inline	bool isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (bool fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDODELR_HXX
