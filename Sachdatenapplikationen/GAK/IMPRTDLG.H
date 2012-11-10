// ImprtDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportDlg
class CImportDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CImportDlg)

// Construction
public:
	CImportDlg(LPCTSTR pszCaption, CWnd *pParentWnd = NULL, UINT iSelectPage = 0 );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImportDlg();

	// Generated message map functions
protected:
	CImportParams	m_ImportParams;
	CInputTablePage m_pgInputTable;
	COutputTablePage m_pgOutputTable;
	CImportParamPage m_pgImportParam;
	CImportSumPage m_pgImportSum;
	CDoImportPage m_pgDoImport;
	CImportResultPage m_pgImportResult;
	//{{AFX_MSG(CImportDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
