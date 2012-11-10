// ImpQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportQueryDialog dialog

class CImportQueryDialog : public CDialog
{
// Construction
public:
	CImportQueryDialog(CWnd* pParent, CDaoDatabase *pSource, CDaoDatabase *pDest);   

// Dialog Data
	//{{AFX_DATA(CImportQueryDialog)
	enum { IDD = IDD_IMPORT_QUERY };
	CButton	m_btOk;
	CListBox	m_lbQueries;
	CButton	m_btSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoDatabase *m_pSourceDatabase;
	CDaoDatabase *m_pDestDatabase;
	// Generated message map functions
	//{{AFX_MSG(CImportQueryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	virtual void OnOK();
	afx_msg void OnSelchangeQueries();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
