// dlgabh.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgAbh dialog

class CDlgAbh : public CDialog
{
private:          
	CHelper *m_pHelper;
	long m_lIdent;	
	CString m_Sight;
// Construction
public:
	CDlgAbh(CWnd* pParent = NULL, CHelper* pHelper = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAbh)
	enum { IDD = IDD_DIALOG3 };
	CButton	m_OK;
	CListBox	m_lbIdList;
	CButton m_cLoesch;
	BOOL m_bLoesch;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlgAbh)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	virtual void OnOK();
	afx_msg void OnLoesch();
	afx_msg void OnAllId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
