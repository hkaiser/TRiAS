// QueryPar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterQueryParam dialog

class CEnterQueryParam : public CDialog
{
// Construction
public:
	CEnterQueryParam(CWnd* pParent = NULL);   // standard constructor
	CDaoParameterInfo m_varParamInfo;

// Dialog Data
	//{{AFX_DATA(CEnterQueryParam)
	enum { IDD = IDD_QUERY_PARAM };
	CStatic	m_stType;
	CStatic	m_stInfoText;
	CButton	m_btOk;
	CEdit	m_edParam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterQueryParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterQueryParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeParam();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CQueryParams

class CQueryParams : public CPropertySheet
{
	DECLARE_DYNAMIC(CQueryParams)

// Construction
public:
	// CQueryParams(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CQueryParams(CDaoQueryDef *pQueryDef, CWnd* pParentWnd = NULL,
				 LPCTSTR pszCaption = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CErzeugerParam m_pgErzeugerParam;
	CBrancheParam m_pgBranchenParam;
	CResultParam m_pgResultParam;
	CGebietParam m_pgGebietParam;
	CAbfallParam m_pgAbfallParam;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryParams)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQueryParams();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQueryParams)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
