// Veraendern der VisAttribute eines Identifikators ---------------------------
// File: VISPARAM.HXX

#if !defined(_VISPARAM_HXX)
#define _VISPARAM_HXX

///////////////////////////////////////////////////////////////////////////////
// verwendete Interfaces
//DefineSmartInterface(Storage);
//DefineSmartInterface(DataObject);

class DatenBasisObjekt;

class VisInfoDlg : public CPropertySheet {
public:
		VisInfoDlg (pWindow pW);
		~VisInfoDlg (void);

//friend HRESULT CreateDataObject (WStorage &rIStg, WDataObject &rIDO);
//friend HRESULT LoadPages (CPropertySheetExt &, LPCSTR pcKey, LPCSTR pcSubKey);
};

class CVisInfoPage : public CPropertyPage {
private:
	PushButton m_pbDefine;
	RadioButton m_rbRGB;
	RadioButton m_rbHSB;
	MultiSelListBox m_mslbIdentList;
	
	long m_lID;
	char *m_pIDString;
	DatenBasisObjekt &m_rDBO;

	int m_iIdBase;				// IdentBase
	VisType m_rgVTyp;			// behandelter Objekttyp

	bool m_fI;
	bool m_fO;

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);

	void FillEntryList (void);
	Bool AddEntry (CIdentifikator *pId, char *pKT);
	void ChangeVisEntry (VisType iVTyp);

	void WindowInit (Event e);
	bool OnOK (NotifyEvt e);

	void AdjustButton (short iIndex);
	void ChangeButton (bool fI, bool fO);

friend bool EXPORTTRIAS FillIdentSelBox (void *pObj, void *pData);

public:
// Konstruktor/Destruktor
		CVisInfoPage (DatenBasisObjekt &, long Id, VisType rgVTyp, LPCSTR pcCation);
		~CVisInfoPage (void);

// sonstige Memberfunktionen
	long GetVisIdent (void) { return m_lID; }
	char *IDString (void) { return m_pIDString; }
	ErrCode ChangeIdVisInfo (VisType = VT_Default);
	DatenBasisObjekt & DBO (void) { return m_rDBO; }
	VisType VTyp (void) { return m_rgVTyp; }
};

#endif // _VISPARAM_HXX

