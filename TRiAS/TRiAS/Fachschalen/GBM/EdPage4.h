// EdPage4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditPage4 dialog

class CEditPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditPage4)

// Construction
public:
	BOOL	m_bFE;
	BOOL	m_bFZ;
	BOOL	m_bFZE;
	CEditPage4();
	~CEditPage4();

// Dialog Data
	//{{AFX_DATA(CEditPage4)
	enum { IDD = IDD_EDITPAGE4 };
	CButton	m_ckZentrEnts;
	CButton	m_ckDezEnts;
	BOOL	m_bZE;
	BOOL	m_bSGR;
	BOOL	m_bSGT;
	BOOL	m_bKK;
	BOOL	m_bVF;
	BOOL	m_bK;
	BOOL	m_bKKT;
	double	m_rAWE;
	double	m_rAEW;
	double	m_rEGW;
	CString	m_strSonst;
	double	m_rFS;
	double	m_rFKK;
	BOOL	m_bANNWL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableKK( BOOL );
	void EnableSG( BOOL );
	void EnableDlgWindow( UINT id, BOOL flag );
	void EnableDezEntsorg( BOOL flag );
	void SetGeaendert( BOOL = TRUE );
	// Generated message map functions
	//{{AFX_MSG(CEditPage4)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnRadio1();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnCheck9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
