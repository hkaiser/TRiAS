// ChangeNr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeNummerDlg dialog
class CDaoDatabase;

class CChangeNummerDlg : public CDialog
{
// Construction
public:
	CString m_strNummer;

	CChangeNummerDlg(CDaoDatabase *pDatabase, const char *pSel = NULL, 
					 CWnd* pParent = NULL, BOOL bSelect = FALSE);  

// Dialog Data
	//{{AFX_DATA(CChangeNummerDlg)
	enum { IDD = IDD_CHANGE_ERZ_NR };
	CStatic	m_stInfo;
	CEdit		m_edNummer;
	CListBox	m_lbNummern;
	CButton	m_btOk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeNummerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoDatabase *m_pDatabase;
	BOOL m_bSelect;

	void OutputNummern (void);
	// Generated message map functions
	//{{AFX_MSG(CChangeNummerDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnChangeNummer();
	virtual void OnOK();
	afx_msg void OnDblclkNummern();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
