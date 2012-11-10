// ResultP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultParam dialog

class CResultParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CResultParam)

// Construction
public:
	CResultParam();
	~CResultParam();

	CDaoQueryDef *m_pQueryDef;

// Dialog Data
	//{{AFX_DATA(CResultParam)
	enum { IDD = IDD_RESULT_PARAM };
	CString	m_strQueryName;
	CString	m_strInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CResultParam)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CResultParam)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
