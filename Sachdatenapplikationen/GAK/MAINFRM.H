// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	void SetStatusBarText (const char *pText, BOOL bIgnore /* TRUE*/);
	void GetStatusBarText (CString &strText);
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

//	Tabelle erzeugen
	void CreateTable (CDaoDatabase *pDatabase, const char *pTableName, UINT uiResId, 
					  IndexFieldInfo *pFieldInfo);

//	lese Anzahl Datensätze in Tabelle
	long GetAnzahl (CDaoDatabase *pDatabase, const char *strTable);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBarExt  m_wndStatusBar;
	CToolBar       m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnImport();
	afx_msg void OnStatistik();
	afx_msg void OnHelpDatabaseErrors();
	afx_msg void OnConfigDsn();
	afx_msg void OnCallAdmin();
	afx_msg void OnDestroy();
	afx_msg void OnExport();
	afx_msg void OnUpdateAktbilanz(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOdbcAcess(CCmdUI* pCmdUI);
	afx_msg void OnOdbcAcess();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
