// Dialogfenster zur Definitition einer IdentBeschreibung in einer PBD
// File: DEFIDENT.HXX

#if !defined(_DEFIDENT_HXX)
#define _DEFIDENT_HXX

class DefineIdentDlg : 
	public DialogWindow 
{
private:
	SingleLineEdit EDKurzText;
	MultiLineEdit EDLangText;
	PushButton OKButton, CancelButton;
	ComboBox m_Connections;
	ComboBox m_SelectOKS;
#if defined(_DEBUG)
	CheckBox m_ROMode;
#endif // defined(_DEBUG)

	long _actId;
	HPROJECT m_hPr;
	long m_lConnCnt;
	bool m_fIsValid;
	bool m_fEditExisting;

protected:
	void ButtonClick (ControlEvt);
	void HelpRequest (HelpRequestEvt e);
	void ListBoxSel (ControlEvt e);
	void EditChange (ControlEvt e);
	LRESULT Dispatch (Event e);

	HRESULT InitConnectionControls (long lIdent = 0, HPROJECT hPr = HACTCONNECTION);

	HRESULT AdjustConnectionControls(long lCnt, int iIndex, LPCSTR pcName, long lIdent = 0);
	BOOL IsIdentIdent (long lIdent, HPROJECT *phPr);

	BOOL InitRemainingControls();
	BOOL InitRemainingControlsOKS(LPCSTR pcOKS);
	BOOL InitDescTexts();
	BOOL InitOKSList(LPCSTR pcOKS = NULL);

	int OnOK();
	
	void AdjustOK();

public:
		DefineIdentDlg (pWindow pParent, ResID resID);
		~DefineIdentDlg (void) {}

	BOOL FInit (long lIdent);
	BOOL FInit (LPCSTR pcOKS, HPROJECT hPr = HACTCONNECTION);

	long GetIdent() { return _actId; }
	HPROJECT GetProject() { return m_hPr; }
};

// Rückgabewerte von OnOk
#define ONOK_ERROR		0
#define ONOK_MODIFIED	1
#define ONOK_CREATED	2

#endif 	// _DEFIDENT_HXX
