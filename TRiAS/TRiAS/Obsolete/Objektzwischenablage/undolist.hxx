// Liste, die ein einstufuges UnDo der ObjClipboardOperationen erlaubt --------
// File: UNDOLIST.HXX


#if !defined(_UNDOLIST_HXX)
#define _UNDOLIST_HXX

enum UStatus {                                           
	USNotModified = 0x0,
	USIdentModified = 0x01,
	USGeometrieModified = 0x02,
	USMerkmaleModified = 0x04,
	USNewObject = 0x08,
	USObjectDeleted = 0x10,
};

class Undo {
private:
	OBJGEOMETRIE *_pOG;		// ObjektGeometrie etc.
	ObjMerkmalsListe *_pOML;	// sämtliche Objektmerkmale
	UStatus _US;			// Status dieses UndoElements
	
public:
		Undo (long lONr, UStatus = USNotModified);
		~Undo (void);

	Bool PlayUndo (HWND);		// dieses Undo machen
	void ResetUStatus (UStatus US = USNotModified) { _US = US; }
	void SetUStatus (UStatus US) { _US = UStatus(_US|US); }	// Status setzen (additiv)
	UStatus GetUStatus (void) { return _US; }	// Status liefern
	long ONr (void) { return _pOG ? _pOG -> lONr : -1L; }
		
friend OBJGEOMETRIE *InsertObjectGeometrie (long lONr);
friend ObjMerkmalsListe *InsertObjectMerkmale (long lONr);
friend void DeleteAllMerkmale (long lONr);
};


class UndoList : public CListContainer {
private:
	HWND _hWnd;			// FensterHandle des ORFensters
	
protected:
	void UserDelete (void *);

public:
		UndoList (HWND = 0);
		~UndoList (void);

	Bool PlayUndo (void);		// Operation rückgängig machen
	Bool AddUndo (long lONr, UStatus = USNotModified);	// Ein UndoElement bilden 
	void SetUStatus (long lONr, UStatus);
	void ResetHandle (HWND);
};
DeclareLock (UndoList, Undo);


#endif // _UNDOLIST_HXX

