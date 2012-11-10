// Undo/Redo für ObjIdent modifizieren ----------------------------------------
// File: UNDOMODI.HXX

#if !defined(_UNDOMODI_HXX)
#define _UNDOMODI_HXX

class CUndoRedoModIdent : public IUndoRedoModIdent {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	LONG m_lONr;			// betroffenes Objekt
	int m_iMode;			// Mode für ModObjIdent
	ULONG m_ulNewIdent;		// neuer Ident
	ULONG m_ulOldIdent;		// alter Ident

protected:
	BOOL FInit (LONG lONr, ULONG lNewIdent, ULONG lOldIdent, int iMode);

		~CUndoRedoModIdent (void);

public:
		CUndoRedoModIdent (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoModIdent ***
	STDMETHOD(Init)(THIS_ LONG lONr, ULONG ulNewIdent, 
					ULONG ulOldIdent/* = 0L */, int iMode /* = 0 */);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOMODI_HXX
