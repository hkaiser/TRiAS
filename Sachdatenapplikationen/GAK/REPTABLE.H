// RepTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportTable dialog
class CErzListeSet;
class CReportTable : public CDialog
{
// Construction
public:
	CReportTable(CWnd* pParent, CErzListeSet *pSet, const CString &strTableName); 

// Dialog Data
	//{{AFX_DATA(CReportTable)
	enum { IDD = IDD_REPORT_TABLE };
	CButton	m_btErzListDruckVor;
	CButton	m_btOK;
	CButton	m_btErzListDruck;
	CListCtrl	m_lcListe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CErzListeSet *m_pSet;
	CString m_strTable;
	bool init;

	// Generated message map functions
	//{{AFX_MSG(CReportTable)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnErzlistdruck();
	afx_msg void OnErzlistdruckvor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Druck(bool bToWindow);
};
