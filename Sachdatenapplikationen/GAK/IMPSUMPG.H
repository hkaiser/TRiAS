// ImpSumPg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportSumPage dialog

class CImportSumPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CImportSumPage)

// Construction
public:
	CImportSumPage();
	~CImportSumPage();

	void SetParams (CImportParams &Params);

// Dialog Data
	//{{AFX_DATA(CImportSumPage)
	enum { IDD = IDD_IMPORT_SUM };
	CStatic	m_stAsNewTable;
	CStatic	m_stTableKind;
	CStatic	m_stSelected;
	CStatic	m_stOutputTable;
	CStatic	m_stOutputDatabase;
	CStatic	m_stInputTable;
	CStatic	m_stInputDatabase;
	CStatic	m_stAtcual;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImportSumPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImportParams *m_pParams;
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd::GetParent (); }
	// Generated message map functions
	//{{AFX_MSG(CImportSumPage)
		afx_msg void OnHelp();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
