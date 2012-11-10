// Ausgabe der Visualiserungsinformationen einer Datenbank im VISASC-Format ---
// File: VISEXP.HXX

#if !defined(_VISEXP_HXX)
#define _VISEXP_HXX

class CExportVisInfoDlg : public DialogWindow {
private:
	char *m_pBuff;
	char *m_pInBuff;
	char *m_pOutBuff;
	ResourceFile &m_rRF;
	long m_lSichtMCode;
	long m_lSichtLegMCode;
	
	short m_cnIdents;		// Z‰hler aller Idents
	short m_iIdBase;
	
	PushButton m_pbFName;
	MultiSelListBox m_mslbViews;
	SingleLineEdit m_sleFName;
	PushButton m_pbOK;
	PushButton m_pbSelectAll;
	RadioButton m_rbRGB;
	RadioButton m_rbHSB;
        CheckBox m_cbDefaultView;
	CheckBox m_cbObjVisInfo;
	CheckBox m_cbViewFeatures;
	CheckBox m_cbLegendInfo;
	        
	class CStatus *m_pStatus;
	
protected:
	void ButtonClick (ControlEvt e);
	void EditChange (ControlEvt e);
	void ListBoxSel (ControlEvt e);

	bool ExportSelectedViews (void);	// abschlieﬂende Aktion
	bool ExportView (short fh, char *pView, 
			 bool fRGB, bool fFeatures = false, 
			 bool fOVis = false, bool fLegInfo = false);
	bool SelectExportFileName (void);
	
	int CountIdents (char *pView);
	int CountAllIdents (void);
	
public:
// Konstruktor/Destruktor
		CExportVisInfoDlg (pWindow pW, ResourceFile *pRF, 
				   long lVMCode, long lLMCode);
		~CExportVisInfoDlg (void);

static CExportVisInfoDlg *CreateInstance (pWindow pW, ResourceFile *pRF, long lVMCode, long lLMCode);

	bool Init (void);	// Initialisierung der Klasse
};

#endif // _VISEXP_HXX
