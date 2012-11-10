// EdPage5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditPage5 dialog

class CEditPage5 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditPage5)

// Construction
public:
	CString m_strIDE;
	CPG1GBArray* m_parrPG1GB;
	CEditPage5();
	~CEditPage5();

// Dialog Data
	//{{AFX_DATA(CEditPage5)
	enum { IDD = IDD_EDITPAGE5 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA
	CString	m_strG[10];
	double	m_rGF[10];
	double	m_rVZ[10];
	double	m_rGH[10];
	BOOL	m_bV[10];
	short	m_iOffset;
	short	m_iGebZahl;

	void	SetGeaendert( BOOL f = TRUE );

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditPage5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	InitData();
	void	RestoreData();
	void	SpecialDDX_Text( CDataExchange*, UINT, double& );
	void	SpecialDDX_Check( CDataExchange*, UINT, BOOL& );
	void	HideControl( CDataExchange*, UINT );

	// Generated message map functions
	//{{AFX_MSG(CEditPage5)
	virtual BOOL OnInitDialog();
	afx_msg void OnNeu();
	afx_msg void OnDelete();
	afx_msg void OnWeiter();
	afx_msg void OnZurueck();
	afx_msg void OnChangeEdGf1();
	afx_msg void OnChangeEdGf10();
	afx_msg void OnChangeEdGf2();
	afx_msg void OnChangeEdGf3();
	afx_msg void OnChangeEdGf4();
	afx_msg void OnChangeEdGf5();
	afx_msg void OnChangeEdGf6();
	afx_msg void OnChangeEdGf7();
	afx_msg void OnChangeEdGf8();
	afx_msg void OnChangeEdGf9();
	afx_msg void OnChangeEdGh1();
	afx_msg void OnChangeEdGh10();
	afx_msg void OnChangeEdGh2();
	afx_msg void OnChangeEdGh3();
	afx_msg void OnChangeEdGh4();
	afx_msg void OnChangeEdGh5();
	afx_msg void OnChangeEdGh6();
	afx_msg void OnChangeEdGh7();
	afx_msg void OnChangeEdGh8();
	afx_msg void OnChangeEdGh9();
	afx_msg void OnEdVa1();
	afx_msg void OnEdVa10();
	afx_msg void OnEdVa2();
	afx_msg void OnEdVa3();
	afx_msg void OnEdVa4();
	afx_msg void OnEdVa5();
	afx_msg void OnEdVa6();
	afx_msg void OnEdVa7();
	afx_msg void OnEdVa8();
	afx_msg void OnEdVa9();
	afx_msg void OnChangeEdVz1();
	afx_msg void OnChangeEdVz10();
	afx_msg void OnChangeEdVz2();
	afx_msg void OnChangeEdVz3();
	afx_msg void OnChangeEdVz4();
	afx_msg void OnChangeEdVz5();
	afx_msg void OnChangeEdVz6();
	afx_msg void OnChangeEdVz7();
	afx_msg void OnChangeEdVz8();
	afx_msg void OnChangeEdVz9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
