/////////////////////////////////////////////////////////////////////////////
// CDlgPgColor dialog

class CDlgPgColor : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPgColor)

// Construction
public:
	CString m_strViewPalette;
	CString	m_strMapPalette;
	CStringArray	m_strPalettes;
	CMapStringToOb* m_pPaletteList;
	CDlgPgColor();
	~CDlgPgColor();

// Dialog Data
	//{{AFX_DATA(CDlgPgColor)
	enum { IDD = IDD_PAGE_COLORPARAM };
	CListBox	m_lbPalettes;
	int		m_chkSingleMap;
	BOOL	m_bTransparent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPgColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void PrepareValues();
	void RetrieveValues();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPgColor)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListofpalettes();
	afx_msg void OnChkallmaps();
	afx_msg void OnChksinglemap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgPgDirectories dialog

class CDlgPgDirectories : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPgDirectories)

// Construction
public:
	CDlgPgDirectories();
	~CDlgPgDirectories();

// Dialog Data
	CStringArray m_strMapDirs;
	//{{AFX_DATA(CDlgPgDirectories)
	enum { IDD = IDD_PAGE_DIRECTORIES };
	CUpDownList	m_lbMapDirs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPgDirectories)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void PrepareValues();
	void RetrieveValues();

// Implementation
protected:
	afx_msg void OnAddDir();
	// Generated message map functions
	//{{AFX_MSG(CDlgPgDirectories)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_iPos;
// KK010108
	int ChangeKVZList(void) { return m_iPos; }

};
/////////////////////////////////////////////////////////////////////////////
// CDlgPgVisparam dialog

class CDlgPgVisparam : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPgVisparam)

// Construction
public:
	CDlgPgVisparam();
	~CDlgPgVisparam();

// Dialog Data
	//{{AFX_DATA(CDlgPgVisparam)
	enum { IDD = IDD_PAGE_VISPARAM };
	CComboBox	m_cbToScale;
	CComboBox	m_cbFromScale;
	BOOL	m_bMapsVisible;
	CString	m_strFromScale;
	CString	m_strToScale;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPgVisparam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void PrepareValues();
	void RetrieveValues();

// Implementation
protected:
	void CheckScales( );
	// Generated message map functions
	//{{AFX_MSG(CDlgPgVisparam)
	afx_msg void OnSelchangeFromScale();
	afx_msg void OnSelchangeToScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgSheetMapParam

class CDlgSheetMapParam : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgSheetMapParam)

	CDlgPgColor			m_pgColor;
	CDlgPgVisparam		m_pgVisparam;
	CDlgPgDirectories	m_pgDirs;

// Construction
public:
	CDlgSheetMapParam(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDlgSheetMapParam(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSheetMapParam)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgSheetMapParam();

	// Generated message map functions
protected:
	void CreateCommon();
	//{{AFX_MSG(CDlgSheetMapParam)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
