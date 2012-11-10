// Loeschen einer/mehrerer Sichten nach Vorgabe -------------------------------
// File: SELNVIEW.HXX

#if !defined(_SELNVIEW_HXX)
#define _SELNVIEW_HXX

class CSelectViewDlg : public DialogWindow {
private:
	ListBox m_ViewList;
	PushButton m_OKButton;
	CheckBox m_cbDefView;

#if !defined(WIN32)
	PushButton m_HelpButton;
#endif // WIN32

	DatenBasisObjekt &m_rDBO;

	string m_strDefView;

protected:
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt e);
	void ListBoxClk (ControlEvt e);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif

	void AdjustDefView (void);
	bool GetNewView (char *pBuffer, int iLen);
	void HandleDefView (void);

public:
		CSelectViewDlg (pWindow pW, DatenBasisObjekt &rDBO);
		~CSelectViewDlg (void);

	bool Init (LPCSTR pcActView);
	bool SelectView (void);
};


#endif // _SELNVIEW_HXX

