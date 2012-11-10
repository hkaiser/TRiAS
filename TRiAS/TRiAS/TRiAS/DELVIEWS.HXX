// Loeschen einer/mehrerer Sichten nach Vorgabe -------------------------------
// File: DELVIEWS.HXX

#if !defined(_DELVIEWS_HXX)
#define _DELVIEWS_HXX

class CDeleteViewsDlg : public DialogWindow {
private:
	MultiSelListBox m_ViewList;
	PushButton m_OKButton;
#if defined(WIN16)
	PushButton m_HelpButton;
#endif // WIN16

	DatenBasisObjekt &m_rDBO;
	
protected:
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt);
		
	void DeleteSight (pMenu pM, short iIndex);
	
public:
		CDeleteViewsDlg (pWindow pW, DatenBasisObjekt &rDBO);
		~CDeleteViewsDlg (void);

	BOOL Init (char *pActView);
	int DeleteSelectedViews (pMenu pM);
};


#endif // _DELVIEWS_HXX

