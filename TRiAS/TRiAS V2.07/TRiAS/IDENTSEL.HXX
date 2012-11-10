// DialogBox zur Auswahl der anzuzeigenden Objekte
// File: IDENTSEL.HXX

#if !defined(_IDENTSEL_HXX)
#define _IDENTSEL_HXX

#include <ident.hxx>

#if !defined(NOIDENT)
#if !defined(NOIDSELDLG)

class GeoDB;

// Dialogfenster für Identifikatorauswahl -------------------------------------
#define TIPunkt		0x01
#define TILinie		0x02
#define TIFlaeche	0x04
#define TIText		0x08

// Objekte, die hinter den ListBoxEinträgen hängen ----------------------------
class CIdentSelData {
private:
	unsigned m_fTypInfo : 4;	// Typs gehören zur Sicht
	unsigned m_bfTypInfo : 4;	// Backup der Typs

	unsigned m_fOTypes : 4;		// existierende GeoTypen

	unsigned m_fSel : 1;		// ist derzeit selektiert
	unsigned m_fwasSel : 1;		// war zu Beginn selektiert

	unsigned m_fReadAll : 1;	// TypeInfo von Platte lesen
	
	long m_lIdent;			// Identifikator
	char *m_pText;			// angezeigter Text

public:
		CIdentSelData (long lIdent, char *pText);
		~CIdentSelData (void);

	long FIdent (void) { return m_lIdent; }
	char *FText (void) { return m_pText; }

	Bool hasP (void) { return m_fTypInfo & TIPunkt; }
	Bool hasL (void) { return m_fTypInfo & TILinie; }
	Bool hasF (void) { return m_fTypInfo & TIFlaeche; }
	Bool hasT (void) { return m_fTypInfo & TIText; }

	void setP (Bool newP = TRUE) { if (newP) m_fTypInfo |= TIPunkt; else m_fTypInfo &= ~TIPunkt; }
	void setL (Bool newL = TRUE) { if (newL) m_fTypInfo |= TILinie; else m_fTypInfo &= ~TILinie; }
	void setF (Bool newF = TRUE) { if (newF) m_fTypInfo |= TIFlaeche; else m_fTypInfo &= ~TIFlaeche; }
	void setT (Bool newT = TRUE) { if (newT) m_fTypInfo |= TIText; else m_fTypInfo &= ~TIText; }

	Bool hasOne (void) { return m_fTypInfo != 0; }

	short GetBits (void) { return m_fTypInfo; }
	void SetBits (short iBits = TPAll) { m_fTypInfo = iBits; }
	void FBackupBits (void) { m_bfTypInfo = m_fTypInfo; }
	void FRestoreBits (void) { m_fTypInfo = m_bfTypInfo; }

	Bool isSelected (void) { return m_fSel; }
	void setSel (Bool newS = TRUE) { m_fSel = newS; }

	Bool wasSelected (void) { return m_fwasSel; }
	void SetInitSel (Bool newS = TRUE) { m_fwasSel = newS; }

	short GetOTypes (void) { return m_fOTypes; }
	void SetOTypes (short iNewTypes) { m_fOTypes = iNewTypes; }
	
	void SetReadAll (Bool newS = TRUE) { m_fReadAll = newS; }
	Bool ReadAll (void) { return m_fReadAll; }
};


// ListBoxKlasse, die es erlaubt MausEvents abzufangen ------------------------
class CMultipleListBoxWindow : public OwnerDrawListBoxEx {
protected:
	void MouseButtonDn (MouseEvt);
	void FocusChange (FocusChangeEvt e);

	short CalcIndex (CoOrd iIndex, CoOrd &X, CoOrd &Y);

public:
		CMultipleListBoxWindow (pDialogWindow pDW, ResID rsc);
		~CMultipleListBoxWindow (void);

	int GetSelectedItems (int MaxItems, int *pSelItems);	// liefert selektierte Items

// umgelenkte StandardFunktionen
	int GetCount (void) { return LocCtrl() -> GetCount(); }
};

// Der Container IdT enthält bei Aufruf des Dialogfensters alle Id's der
// DatenBasis. Nach dem Aufruf des Dialogfensters enthält IdT nur noch die vom 
// Nutzer ausgewählten Identifikatoren.
class CIdentSelektion : public OwnerDrawDialogWindow {
private:
//	SingleLineEdit m_SLE;		// Eingabe eine AnsichtenNamens
//	PushButton m_DelSightButton;	// Ansicht löschen
//	PushButton m_OKButton;		// Fertig
//	PushButton m_CancelButton;	// Abbrechen

	ComboBox m_NewViewName;		// Auswahl des AnsichtenNamens
	CMultipleListBoxWindow m_SelBox;	// Eingabe der Id's über direkte Auswahl
#if !defined(WIN32)
	PushButton m_HelpButton;	// Hilfe anfordern
#endif // WIN32
	PushButton m_SelAllButton;	// Alle Selektieren/unSelektieren
	PushButton m_NewSightButton;	// Neue Ansicht definieren
	PushButton m_pbTempView;	// temporäre Ansicht definieren
	CheckBox m_Standard;		// zum Standard machen
	CheckBox m_ActVisInfo;		// Farben aus aktueller Sicht
	CheckBox m_RenameView;		// BezugsSicht löschen
	NumEdit m_BMasstab;		// BezugsMaßstab
	SingleLineEdit m_sleDesc;	// Sichtbeschreibung
	
	unsigned m_fSetAllStatus : 1;	// Zustand des SetAllButtons
	unsigned m_fStandard : 1;	// Namen als Standard verwenden
	unsigned m_fShowMenu : 1;	// Menu derzeit angezeigt
	unsigned m_fHadDesc : 1;
	
	DatenBasisObjekt &m_rDBO;

public:
	CIdTree &Idents (void) { return m_rDBO.Idents(); }	// Ident's die gelistet werden
	GeoDB &DB (void) { return m_rDBO.DB(); }
	DatenBasisObjekt &DBO (void) { return m_rDBO; }

private:
	char *m_actSight;
	long m_lMasstab;		// lokaler BezugsMasstab
	short m_iActIndex;		// derzeit aktiver Eintrag
	HMENU m_hMenu;

protected:
// Eventhandler
	void ButtonClick (ControlEvt);
	void EditFocusChg (EditFocusChgEvt);
	void EditChange (ControlEvt);
	void ListBoxSel (ControlEvt);
	void MenuCommand (MenuCommandEvt);
	void MenuInit (MenuInitEvt);

	Bool EXPORTTRIAS DrawEntireItem (DrawItemEvt e);
	Bool EXPORTTRIAS DrawItemFocus (DrawItemEvt e);
	Bool EXPORTTRIAS DrawItemSelect (DrawItemEvt e);
	int EXPORTTRIAS CompareItem (OwnerDrawEvt, void *pItem1, void *pItem2);
	Bool EXPORTTRIAS MeasureItem (MeasureItemEvt e);
	Bool EXPORTTRIAS DeleteItem (DeleteItemEvt e);

	LRESULT EXPORTTRIAS Dispatch (Event);

	long GetBMasstab (void);
	ErrCode OKButtonSelected (void);
	ErrCode ReadVisInfoFromSight (Sicht *pS, long lIdent, 
					VisType iVTyp,
					HPALETTE &hPal, VisInfo *& pVI);
	ErrCode ReadVisInfoFromDefaultSight (Sicht *pS, long lIdent, 
					VisType iVTyp,
					HPALETTE &hPal, VisInfo *& pVI);
	void ShowMenu (short iIndex, short X, short Y);
	void AdjustData (BOOL fRestore = TRUE);
	void ForgetInitialSelection (void);

	void AdjustOK (void);		// OK-Knöpfe richten
		
public:
// Konstruktor/Destruktor
		CIdentSelektion (pWindow pW, DatenBasisObjekt &rDBO, char *Name, long);
		~CIdentSelektion (void);

// Member
	bool WriteNewSight (bool &rfNew);
	void DeleteSight (void);

	bool GetNewSightName (LPSTR pBuffer, int iLen);

// Friends
friend void EXPORTTRIAS FillSelBox (void *pObj);
friend void EXPORTTRIAS ResetPaintFlag (void *pObj);
};

#define WM_SHOWTYPEMENU	WM_USER+1000

#endif // NOIDSELDLG
#endif // NOIDENT

#endif // _IDENSEL_HXX
