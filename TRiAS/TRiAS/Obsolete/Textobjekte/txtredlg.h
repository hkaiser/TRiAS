
// txtredlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTxtReDlg dialog 

extern "C"
{
   	BOOL FAR PASCAL _XTENSN_EXPORT EnumMCodeProc (long lMCode, BOOL, void *pData);
}// extern "C"

class CTxtReDlg : public CDialog
{
// Construction
private:  
	CHelper *m_pHelper;
	CString m_Sight; 
	long m_rlCBIdent;
	short Event();
	CString GetText (void) {CString eBuffer(' ',64);
							m_eText.GetWindowText(eBuffer);
							   return eBuffer; };    
    long m_lMCode;
    HWND m_hWnd;
	HMENU m_hMenu;
	
public:
	CTxtReDlg(CWnd* pParent = NULL, HWND hWnd = 0, HMENU hMenu = 0, CHelper *pHelper = NULL);	// standard constructor
    char* GetKText (CString &cbKText, char cKey ,long lItem);
// Dialog Data
	//{{AFX_DATA(CTxtReDlg)
	enum { IDD = IDD_DIALOG2 };
	CButton	m_cbPosPtTexts;
	CButton	m_rObLoesch;
	CButton m_rRename;
	CButton	m_cRelat;
	CComboBox m_cbxMCode;
	CComboBox m_cbxObClList;
	CButton m_OK;
	CButton m_rText;
	CButton m_rMCode; 
	CButton m_rTxtPerm;
	CButton m_rTxtTemp;
	CButton m_cPutObCl;
	CStatic m_stSForm;
	CEdit m_eText;	
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTxtReDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRMCode();
	afx_msg void OnRPerm();
	afx_msg void OnRTemp();
	afx_msg void OnRTxtExpl();
	afx_msg void OnSetFocEd();
	afx_msg void OnSelCombo();
	afx_msg void OnInputEd();
	afx_msg void OnCheckRelat();
	afx_msg void OnPutObCl();
	afx_msg void OnRename();
	afx_msg void OnLoesch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
