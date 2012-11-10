// Undo/Redo für Textobjekt erzeugen ------------------------------------------
// File: UNDOTEXT.HXX

#if !defined(_UNDOTEXT_HXX)
#define _UNDOTEXT_HXX

class CUndoRedoCreateTextObject : public IUndoRedoCreateText {
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	TEXTGEOMETRIE m_tgText;
	string m_strText;
	POINTL m_ptlText;

protected:
	BOOL FInit (LONG lONr);

		~CUndoRedoCreateTextObject (void);

public:
		CUndoRedoCreateTextObject (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoCreateText ***
	STDMETHOD(Init)(THIS_ LONG lONr);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOTEXT_HXX
