// Fensterklasse fuer ObjektZwischenAblage -------------------------------------
// File: OBJCLDLG.HXX

#if !defined(_OBJCLDLG_HXX)
#define _OBJCLDLG_HXX

enum ObjClpStatus {
	OCVInValid = -1,	// irgend was ist ungültig
	OCVIdle = 0,		// leer
	OCVObjectValid = 1,	// Objekt ist geladen
	OCVInfoValid = 2,	// sonstige Info eingestellt
};

enum IMode {
	IMCopy = 1,		// IDM_COPY
	IMDelete = 2,		// IDM_CUT
};

extern "C" {
	BOOL _XTENSN_EXPORT PASCAL PasteObject (long lONr, BOOL, void *pData);
}

class ObjMerkmalsListe;
class UndoList;

class ObjClipboardViewer : public DialogWindow {
private:
// dieses Fenster hat ein eigenes Menu
	Menu _ObjClpMenu;

// hier folgen die FensterControls
	FixedText _ObjClpStatusField;	// Anzeige des Status der Zwischenablage
	CheckBox _Lage;
	CheckBox _Form;
	CheckBox _Ident;		// Identifikator
	ComboBox _CBIdent;
	CheckBox _Merkmale;		// Merkmale
	MultiSelListBox _LBMerkmale;
	ComboBox _CBMerkmal;
//	CheckBox _Relationen;		// Relationen
//	MultiSelListBox _LBRelationen;
//	CheckBox _CopyRelObjs;		// Relationale Objekte kopieren

	ResourceFile &_RF;

	Bool _isViewerShown;
	Bool _wasViewerShown;

	Bool _iCopyLage;
	Bool _iCopyForm;
	
	short m_iIdBase;
	short m_iMkBase;

	ObjClpStatus _OCS;

// eigentliche ClipboardInformation
	UndoList *_pUList;

	OBJGEOMETRIE *_pOG;
	ObjMerkmalsListe *_pOML;

protected:
// EventHandler
	void ButtonClick (ControlEvt);
	void MenuCommand (MenuCommandEvt);
	void MenuInit (MenuInitEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	Bool QueryClose (Event);

	Bool ShowViewer (void);
	Bool HideViewer (void);

	Bool DeleteClipboard (void);
	Bool UpdateViewer (void);

	ObjClpStatus EvalStatus (void);
	Bool FillMerkmale (Bool = FALSE);
	Bool UpdateMList (short = -1);

	Bool isNotMCodeUsed (long);
	long GetCurrentPBDMCode (char ** = NULL);

public:
// Konstruktor/Destruktor
		ObjClipboardViewer (pWindow, ResourceFile *);
		~ObjClipboardViewer (void);

	Bool &isViewerShown (void) { return _isViewerShown; }
	ObjClpStatus &Status (void) { return _OCS; }

// TRIAS(R) -EventBehandlung
	void OpenedProject (void);
	void ClosingProject (void);

	void ToggleStatus (void);

// ClipboardFunktionen
	Bool InsertObject (long ONr, IMode = IMCopy);

	Bool PasteObjectLocal (HWND);
	Bool PasteObjectGlobal (void);

friend BOOL _XTENSN_EXPORT PASCAL PasteObject (long lONr, BOOL, void *pData);

	void ReReadIdents (long = 0);	// PBD (Idents) neu lesen
	void ReReadMCodes (long = 0);	// PBD (MCodes) neu lesen

	void EditMWert (Bool = FALSE);
	void DeleteMerkmale (void);
	void DeleteMerkmalsWerte (void);

	void ResetUndoHandle (HWND hWnd); 

// Besorgen diverser Objektinformationen
friend OBJGEOMETRIE *InsertObjectGeometrie (long lONr);
friend ObjMerkmalsListe *InsertObjectMerkmale (long lONr);
};


#endif // _OBJCLDLG_HXX
