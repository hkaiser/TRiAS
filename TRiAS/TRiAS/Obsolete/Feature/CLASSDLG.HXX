// DialogFenster zur Anzeige und Auswertung klassifizierter Merkmale 
// File: CLASSDLG.HXX

#if !defined(_CLASSDLG_HXX)
#define _CLASSDLG_HXX

class CClassifiedDlg : public DialogWindow {
private:
	PushButton m_pbShow;
	MultiSelListBox m_mslFeatures;

	CUIdentObjects &m_rAllObjs;
	CUIdentObjects &m_rDupObjs;

	ULONG m_ulMCode;

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);

	bool AdjustButtons (void);
	bool ShowObjects (void);
	bool CopyToClipBoard (void);

public:
		CClassifiedDlg (pWindow pW, ResID uiRes, 
			CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs,
			ULONG ulMCode);
		~CClassifiedDlg (void);

static CClassifiedDlg *CreateInstance (pWindow pW, ResID uiRes, 
			CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs,
			ULONG ulMCode);

	bool FInit (void);
};

#endif // _CLASSDLG_HXX
