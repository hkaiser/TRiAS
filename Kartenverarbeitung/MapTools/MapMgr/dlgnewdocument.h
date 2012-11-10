// DlgNewDocument.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPgDocStart dialog

class CPgDocStart : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgDocStart)

// Construction
public:
	CPgDocStart();
	~CPgDocStart();

// Dialog Data
	//{{AFX_DATA(CPgDocStart)
	enum { IDD = IDD_PG_DOCSTART };
	int		m_nStartAction;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgDocStart)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPgDocStart)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMaplast();
	afx_msg void OnBtnMapother();
	afx_msg void OnBtnPrjnew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPgMapType dialog

class CPgMapType : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgMapType)

// Construction
public:
	CString m_strMapTypes;
	CPgMapType();
	~CPgMapType();

// Dialog Data
	//{{AFX_DATA(CPgMapType)
	enum { IDD = IDD_PG_MAPTYPE };
	CEdit	m_editSearchMask;
	CButton	m_chkSrchMaps;
	CComboBox	m_listMapTypes;
	CUpDownList	m_listMapDirs;
	int		m_nMapType;
	BOOL	m_bSrchMaps;
	CString	m_strSearchMask;
	CString	m_strMapItem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgMapType)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPgMapType)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearchmaps();
	afx_msg void OnSelchangeDropMaptypestypes();
	//}}AFX_MSG
	afx_msg void OnAddDir();
	afx_msg void OnDelDir();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPgDoSearch dialog

class CPgDoSearch : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgDoSearch)

// Construction
public:
	int m_mapType;
	CString m_strSearchDirs;
	CString	m_strSearchMask;
	CPgDoSearch();
	~CPgDoSearch();

// Dialog Data
	//{{AFX_DATA(CPgDoSearch)
	enum { IDD = IDD_PG_DOSEARCH };
	CListBox	m_listMaps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgDoSearch)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWinThread* m_pSrchThread;
	// Generated message map functions
	//{{AFX_MSG(CPgDoSearch)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg LONG OnThreadMessage( UINT, LONG );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPgFinishNewDoc dialog

class CPgFinishNewDoc : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgFinishNewDoc)

// Construction
public:
	CPgFinishNewDoc();
	~CPgFinishNewDoc();

// Dialog Data
	//{{AFX_DATA(CPgFinishNewDoc)
	enum { IDD = IDD_PG_FINISHDOCNEW };
	CString	m_strMapParam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgFinishNewDoc)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPgFinishNewDoc)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CDlgNewDocument

class CDlgNewDocument : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgNewDocument)

// Construction
public:
	CDlgNewDocument(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	// Set...
	CString	m_strMapTypes;
	// Get...
	int m_nStartAction;
	int m_mapType;
	CString m_strMapDirs;
	CString m_strMaps;

// Attributes
public:
	enum { IDD = IDD_DLG_DOCNEWDIALOG };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewDocument)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgNewDocument();

	// Generated message map functions
protected:
	void FormatFinish();
	CString FormatDirs( BOOL bForFinish = FALSE );
	CPgDocStart		m_pgDocStart;
	CPgMapType		m_pgMapType;
	CPgDoSearch		m_pgSearch;
	CPgFinishNewDoc	m_pgFinish;

	//{{AFX_MSG(CDlgNewDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	afx_msg void OnWizardNext();
	afx_msg void OnWizardBack();
	afx_msg void OnWizardFinish();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
