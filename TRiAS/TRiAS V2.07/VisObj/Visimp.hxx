// Importieren einer VisAscdatei ----------------------------------------------
// File: VISIMP.HXX


#if !defined(_VISIMP_HXX)
#define _VISIMP_HXX

extern "C" 
BOOL PASCAL _XTENSN_EXPORT FillViewTree (char *pView, BOOL, void *pData);

class CImportVisInfoDlg : public DialogWindow {
private:
	char *m_pBuff;
	char *m_pInBuff;
	ResourceFile &m_rRF;

	SingleLineEdit m_sleFName;
	PushButton m_pbOK;
	PushButton m_pbFName;
	PushButton m_pbAllViews;
	MultiSelListBox m_mslbViews;
	
	RadioButton m_rbAutoSelect;
	RadioButton m_rbRGB;
	RadioButton m_rbHSB;
	CheckBox m_cbDefaultView;
	CheckBox m_cbObjVisInfo;
	CheckBox m_cbViewFeatures;
	CheckBox m_cbDeleteViews;
	CheckBox m_cbLegInfo;
#if defined(WIN32)
	CheckBox m_cbExistend;
#endif // WIN32

	class CImpViewTree *m_pViews;
	
protected:
	void ButtonClick (ControlEvt e);
	void EditChange (ControlEvt e);

	bool ImportVisAsc (void);
	bool SelectImportFileName (void);
	CImpViewTree *AnalyzeVSCFile (char *pFName);
	bool DeleteOldViews (void);

public:
		CImportVisInfoDlg (pWindow pW, ResourceFile *pRF);
		~CImportVisInfoDlg (void);
		
	bool Init (void);
};


#endif // _VISIMP_HXX

