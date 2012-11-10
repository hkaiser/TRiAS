// AbfallP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfallParam dialog
class CSelectSet;
class CAbfallParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CAbfallParam)

// Construction
public:
	CAbfallParam();
	~CAbfallParam();

	CDaoQueryDef *m_pQueryDef;

// Dialog Data
	//{{AFX_DATA(CAbfallParam)
	enum { IDD = IDD_ABFALL_PARAM };
	CEdit	m_edName;
	CEdit	m_edAbfall;
	CRealEdit m_edMenge;
	CButton	m_btSelect;
	CButton	m_btOnlySonder;
	CButton	m_btAlle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAbfallParam)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAbfallParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectAbfallart();
	afx_msg void OnChangeAbfart();
	afx_msg void OnChangeMenge();
	afx_msg void OnHelp();
	afx_msg void OnAlleAbfallarten();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CSelectSet *m_pSet;
	CDaoParameterInfo m_QueryInfoNurSonderAbf;
	CDaoParameterInfo m_QueryInfoAlleAbf;
	CDaoParameterInfo m_QueryInfoAbfArt;
	CDaoParameterInfo m_QueryInfoAbfMenge;

	void OutputName (const CString &);
	void SetWButtons ();
};
