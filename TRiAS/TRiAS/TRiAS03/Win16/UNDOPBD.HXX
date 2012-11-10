// Undo/Redo für einen PBD-Eintrag --------------------------------------------
// File: UNDOPBD.HXX

#if !defined(_UNDOPBD_HXX)
#define _UNDOPBD_HXX

class CUndoRedoPBDData : public IUndoRedoPBDData {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;	// wurde bereits initialisiert

	PBDDATATYPE m_rgType;			// Typ des behandelten PBD-Eintrages
	ULONG m_ulTarget;			// Code des PBD-Eintrages
	int m_rgBase;				// Zahlenbasis
	ErrCode m_ecIgnoreCode;			// für ErrInstall

	PBDDATA *m_pOldPBDData;			// Alter PBD-Eintrag
	PBDDATA *m_pNewPBDData;			// Neuer PBD-Eintrag

protected:
	bool FInitDelete (PBDDATATYPE rgType, ULONG ulTarget);
	bool FInitModify (const PBDDATA *pNewData, const PBDDATA *pOldData);

	PBDDATA *CopyPBDData (PBDDATATYPE rgType, const PBDDATA *pData);
	PBDDATA *ReadPBDData (PBDDATATYPE rgType, ULONG ulTarget);

		~CUndoRedoPBDData (void);

public:
		CUndoRedoPBDData (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoPBDData ***
        STDMETHOD(InitModify)(THIS_ const PBDDATA *pNewData, const PBDDATA *pOldData);
        STDMETHOD(InitDelete)(THIS_ PBDDATATYPE rgType, ULONG ulTarget);

// sonstige Member
inline	bool isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (bool fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

// Funktionen für das Erzeugen und Freigeben einer typspezifischen PBDDATA-Struktur
PBDDATA *__ctPBDDATA (PBDDATATYPE rgType, ULONG lTarget, bool fInitStrings = true);
void __dtPBDDATA (PBDDATA *&rpPBDData);

PBDDATATYPE GetPBDType (int iType);
int GetPBDBase (PBDDATATYPE rgType);
ErrCode GetPBDIgnoreCode (PBDDATATYPE rgType);

#endif // _UNDOPBD_HXX
