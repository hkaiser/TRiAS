// DlgFileProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPgFileGeometry dialog

class CPgFileGeometry : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgFileGeometry)
// Construction
public:
	CPgFileGeometry();
	~CPgFileGeometry();
// Dialog Data
	ASC_HEADER	m_ascHeader;
	TOPOMAPTYPE m_mapType;
	//{{AFX_DATA(CPgFileGeometry)
	enum { IDD = IDD_PG_HDRGEODATA };
	CComboBox	m_listMapTypes;
	double	m_nOffsetX;
	double	m_nOffsetY;
	double	m_nScale11;
	double	m_nScale12;
	double	m_nScale21;
	double	m_nScale22;
	int		m_nMapType;
	CString	m_strCoordTrans;
	//}}AFX_DATA
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgFileGeometry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	void PrepareValues();
	void RetrieveValues();
	// Generated message map functions
	//{{AFX_MSG(CPgFileGeometry)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMaptype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPgVisdata dialog

class CPgVisdata : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgVisdata)
// Construction
public:
	CPgVisdata();
	~CPgVisdata();
// Dialog Data
	MMGR_ASC_HEADER	m_ascHeader;
	//{{AFX_DATA(CPgVisdata)
	enum { IDD = IDD_PG_HDRVISDATA };
	int		m_nIdentBase;
	int		m_nMcodeBase;
	CString	m_strMapVcode;
	CString	m_strMapMcode;
	CString	m_strIdent;
	CString	m_strMapIcode;
	int		m_nVersion;
	//}}AFX_DATA
protected:
	DWORD	m_dwTKIdent;
	DWORD	m_dwTKIcode;
	DWORD	m_dwTKMcode;
	DWORD	m_dwTKVcode;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgVisdata)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	void PrepareValues();
	void RetrieveValues();
	// Generated message map functions
	//{{AFX_MSG(CPgVisdata)
	afx_msg void OnIdent10();
	afx_msg void OnIdent16();
	afx_msg void OnMcode10();
	afx_msg void OnMcode16();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusUniqueident();
	afx_msg void OnKillfocusMapmcode();
	afx_msg void OnKillfocusMapvcode();
	afx_msg void OnKillfocusIdent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPgFileOpt dialog

class CPgFileOpt : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgFileOpt)

// Construction
public:
	CPgFileOpt();
	~CPgFileOpt();

// Dialog Data
	//{{AFX_DATA(CPgFileOpt)
	enum { IDD = IDD_PG_FILEOPT };
	int		m_nJumpX;
	int		m_nJumpY;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgFileOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPgFileOpt)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CDlgFileProp

class CDlgFileProp : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgFileProp)

	CPgFileGeometry	m_pgGeometry;
	CPgVisdata		m_pgVisdata;
	CPgFileOpt		m_pgFileOpt;

// Construction
public:
	CDlgFileProp(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	enum { IDD = IDD_DLG_DOCPROPERTIES };

	MMGR_ASC_HEADER	m_ascHeader;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFileProp)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgFileProp();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgFileProp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
