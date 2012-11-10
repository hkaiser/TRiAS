// textdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog
#if !defined(_TEXTDLG_HPP)
#define _TEXTDLG_HPP 

class CTextDlg : public CDialog
{
// Construction 
private:            
	CHelper *m_pHelper;
	CString m_Sight;
	long m_rlIdent;
	long m_rlMCode;
	long m_rlCBIdent;
	CString m_eObj;
	short Event();       
	short m_iERR;
public:
	CTextDlg(CWnd* pParent = NULL, CHelper *pHelper = NULL);	// standard constructor
    char* GetKText (CString &cbKText, char cKey ,long lItem);
// Dialog Data
	//{{AFX_DATA(CTextDlg)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_cbPosPtTexts;
	CStatic	m_stSForm;
	CButton	m_rObLoesch;
	CButton	m_cRelat;
	CEdit	m_eText;
	CButton	m_OKButton;
	CComboBox m_cbxMCodeList;
	CComboBox m_cbxObClList;
	CListBox m_lbIdList;
	CButton m_rText;
	CButton m_rMCode; 
	CButton m_rTxtPerm;
	CButton m_rTxtTemp;
	CButton m_cPutObCl;
	CButton	m_rRename;
	//}}AFX_DATA
	long  GetMCode (void) { return m_rlMCode; };
    	CString GetText (void) {CString eBuffer(' ',64);
							m_eText.GetWindowText(eBuffer);
							   return eBuffer; };    
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTextDlg)
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelList();
	afx_msg void OnSelCom();
	afx_msg void OnRadioTxt();
	afx_msg void OnSetFocusE1();
	afx_msg void OnRadioMCText();
	afx_msg void OnInputE1();
	afx_msg void OnRadioTxtPerm();
	afx_msg void OnRadioTxtTemp();
	afx_msg void OnAllId();
	afx_msg void OnCheckRelat();
	afx_msg void OnPutObCl();
	afx_msg void OnRename();
	afx_msg void OnObLoesch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // _TEXTDLG_HPP
