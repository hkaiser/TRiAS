// ImpResPg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportResultPage dialog

class CImportResultPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CImportResultPage)

// Construction
public:
	CImportResultPage();
	~CImportResultPage();

	void SetParams (CImportParams &Params);

// Dialog Data
	//{{AFX_DATA(CImportResultPage)
	enum { IDD = IDD_IMPORT_RESULT };
	CButton	m_btErrorHelp;
	CStatic	m_stSumErrCnt;
	CStatic	m_stSumCnt;
	CStatic	m_stNewErrCnt;
	CStatic	m_stNewCnt;
	CStatic	m_stActErrCnt;
	CStatic	m_stActCnt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImportResultPage)
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
	//{{AFX_MSG(CImportResultPage)
	afx_msg void OnShowProtokoll();
	afx_msg void OnErrorHelp();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
