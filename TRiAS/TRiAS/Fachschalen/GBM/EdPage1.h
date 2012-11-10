// EdPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditPage1 dialog

class CEditPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditPage1)

// Construction
public:
	CString m_strNFP1_NEIG;
	CString m_strTB;
	BOOL m_bEditIDE;
	CEditPage1();
	~CEditPage1();

// Dialog Data
	//{{AFX_DATA(CEditPage1)
	enum { IDD = IDD_EDITPAGE1 };
	CEdit	m_wndNA_B_PLAN;
	CComboBox	m_cbBAR;
	CString	m_strNFP1_ENA;
	CString	m_strNFP1_IDE;
	CString	m_strNFP1_EAN;
	CString	m_strNFP1_EPL;
	CString	m_strNFP1_EOR;
	CString	m_strNFP1_ORT;
	CString	m_strNFP1_FLU;
	CString	m_strNFP1_FST;
	double	m_rNFP1_KAT;
	double	m_rNFP1_GFZ;
	double	m_rNFP1_BMZ;
	double	m_rNFP1_VGZ;
	double	m_rNFP1_GUZ;
	int		m_iNFP1_BAR;
	CString	m_strNFP1_ANDAT;
	CString	m_strNA_B_PLAN;
	double	m_rNFP1_VOLU;
	BOOL	m_bNFP1_TIEF;
	CString	m_strNFP1_GEFS;
	CString	m_strNFP1_AGGS;
	CString	m_strNFP1_AGG;
	CString	m_strNFP1_TIEB;
	CString	m_strEigentumArt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableBPlan();
	void SetGeaendert( BOOL = TRUE );
	// Generated message map functions
	//{{AFX_MSG(CEditPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnAendern();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
