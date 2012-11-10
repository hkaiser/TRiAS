// DlgOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions

class CDlgOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgOptions)

// Construction
public:
	CDlgOptions(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDlgOptions(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptions)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgOptions();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgOptions)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
