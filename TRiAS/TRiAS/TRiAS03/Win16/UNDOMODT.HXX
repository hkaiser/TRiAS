// Undo/Redo für TextObjekt modifizieren --------------------------------------
// File: UNDOMODT.HXX

#if !defined(_UNDOMODT_HXX)
#define _UNDOMODT_HXX

class CUndoRedoTextObject : public CUndoRedo {
private:
	TEXTGEOMETRIE m_tgOText;		// altes Textobjekt
	string m_strOText;
	POINTL m_ptlOText;

	TEXTGEOMETRIE m_tgNText;		// neues Textobjekt
	string m_strNText;
	POINTL m_ptlNText;

protected:
	bool FInit (void);

		CUndoRedoTextObject (LONG lONr);
		~CUndoRedoTextObject (void);

public:
_TRIAS03_ENTRY static CUndoRedoTextObject *CreateInstance (LONG lONr);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);
};

#endif // _UNDOMODT_HXX
