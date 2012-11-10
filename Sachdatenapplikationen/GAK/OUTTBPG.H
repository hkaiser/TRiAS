// OutTbPg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputTablePage dialog

class COutputTablePage : public CPropertyPage
{
	DECLARE_DYNCREATE(COutputTablePage)

// Construction
public:
	COutputTablePage();
	~COutputTablePage();

	void SetParams (CImportParams &Params);

// Dialog Data
	//{{AFX_DATA(COutputTablePage)
	enum { IDD = IDD_OUTPUT_TABLE };
	CButton	m_btAsNew;
	CStatic	m_stInfo;
	CButton	m_btCreate;
	CListBox	m_lbTables;
	CEdit	m_edTableName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COutputTablePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImportParams *m_pParams;
	void SetWizardButton (void);
	void OutputTableNames (void);
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd::GetParent (); }

	// Generated message map functions
	//{{AFX_MSG(COutputTablePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeTableName();
	afx_msg void OnSelchangeTables();
	afx_msg void OnCreate();
	afx_msg void OnAsNew();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
