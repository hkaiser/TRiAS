// QueryRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryResult dialog

class CQueryResult : public CDialog
{
// Construction
public:
	CQueryResult(CWnd* pParent, CDaoRecordset *pSet, const CString& strQueryName);  

// Dialog Data
	//{{AFX_DATA(CQueryResult)
	enum { IDD = IDD_QUERY_RESULT };
	CStatic	m_stInfo;
	CListCtrl	m_lcListe;
	CButton	m_btFeldNamen;
	CButton	m_btCopy;
	CButton	m_btAlle;
	CButton m_btTable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoRecordset *m_pSet;
	CString m_strQueryName;

	void CopyToClipboard (void);
	void CopyToTable (void);

	// Generated message map functions
	//{{AFX_MSG(CQueryResult)
	virtual BOOL OnInitDialog();
	afx_msg void OnCopy();
	afx_msg void OnClickQueryList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOnlySelected();
	afx_msg void OnAlle();
	afx_msg void OnTable();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
