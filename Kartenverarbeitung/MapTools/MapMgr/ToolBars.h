/////////////////////////////////////////////////////////////////////////////
// CBaseToolBar window

class CBaseToolBar : public CToolBar
{
// Construction
public:
	CBaseToolBar();

// Attributes
public:

// Operations
public:
	virtual void ResetState();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBaseToolBar();
	BOOL Create( CWnd* pParent, DWORD dwAddStyle, UINT nID, UINT *pIDS, int nIDS );

	// Generated message map functions
protected:
	//{{AFX_MSG(CBaseToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTBModes window

class CTBModes : public CBaseToolBar
{
// Construction
public:
	CTBModes();

// Attributes
public:
	enum { IDD = IDW_TB_MODES };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTBModes)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTBModes();
	BOOL Create( CWnd* pParent );

	// Generated message map functions
protected:
	//{{AFX_MSG(CTBModes)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CTBObjects window

class CTBObjects : public CBaseToolBar
{
// Construction
public:
	CTBObjects();

// Attributes
public:
	enum { IDD = IDW_TB_OBJECTS };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTBObjects)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTBObjects();
	BOOL Create( CWnd *pParent );

	// Generated message map functions
protected:
	//{{AFX_MSG(CTBObjects)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CTBMaps window

class CTBMaps : public CBaseToolBar
{
	CComboBox	m_cbMapNames;
// Construction
public:
	CTBMaps();
	void	AddMapName( LPCTSTR lpszMapName );
	void	DelMapName( LPCTSTR lpszMapName );
	void	GetCurSel( CString& S );
	void	SetCurSel( LPCTSTR lpszSel );

// Attributes
public:
	enum { IDD = IDW_TB_MAPS };

// Operations
public:
	virtual void ResetState();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTBMaps)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTBMaps();
	BOOL Create( CWnd *pParent );

	// Generated message map functions
protected:
	//{{AFX_MSG(CTBMaps)
	//}}AFX_MSG
	afx_msg void OnSelchangeMap();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
