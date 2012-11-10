// Veraendern der VisAttribute eines Identifikators ---------------------------
// File: VISPARAM.HXX

#if !defined(_VISPARAM_HXX)
#define _VISPARAM_HXX

class DatenBasisObjekt;

class VisInfoDlg : public DialogWindow {
protected:
	PushButton CancelButton;
	PushButton PButton;
	PushButton LButton;                 
	PushButton FButton;
	PushButton TButton;

	MultiSelListBox IdentList;
	
	RadioButton m_rbRGB;
	RadioButton m_rbHSB;
	
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);

	long _ID;
	char *_IDString;
	DatenBasisObjekt &_DBO;

	int m_iIdBase;		// IdentBase

	unsigned short m_fChangeType : 1;
	
	void FillEntryList (void);
	Bool AddEntry (CIdentifikator *pId, char *pKT);
	void AdjustButtons (short iIndex);
	void ChangeVisEntry (VisType iVTyp);

friend bool EXPORTTRIAS FillIdentSelBox (void *pObj, void *pData);

public:
// Konstruktor/Destruktor
		VisInfoDlg (pWindow pW, DatenBasisObjekt &, long Id = -1, 
			    Bool iChangeType = FALSE);
		~VisInfoDlg (void);

// sonstige Memberfunktionen
	long GetVisIdent (void) { return _ID; }
	char *IDString (void) { return _IDString; }
	ErrCode ChangeIdVisInfo (VisType = VT_Default);
	DatenBasisObjekt & DBO (void) { return _DBO; }
};

#endif // _VISPARAM_HXX

