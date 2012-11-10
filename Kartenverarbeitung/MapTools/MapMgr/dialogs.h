/////////////////////////////////////////////////////////////////////////////
// CMapSelectDialog dialog

class CMapSelectDialog : public CDialog {
// Construction
public:
	CMapSelectDialog(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CMapSelectDialog)
	enum { IDD = IDD_DLG_MAPSELECT };
	CMapTreeCtrl	m_treeOfMapTypes;
	//}}AFX_DATA
	CString	m_strMapIdent;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL UpdateData( BOOL bSaveAndValidate = TRUE );
	// Generated message map functions
	//{{AFX_MSG(CMapSelectDialog)
	afx_msg void OnBtnApply();
	afx_msg void OnItemexpandedTreeOfMaps(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreeOfMaps(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgMapName dialog

class CDlgMapName : public CDialog
{
// Construction
public:
	CDlgMapName(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDlgMapName)
	enum { IDD = IDD_DLG_MAPNAME };
	int		m_mapType;
	CString	m_strMapIdent;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL UpdateData( BOOL bSaveAndValidate = TRUE );
// Implementation
protected:
	void OnDblClick();
	// Generated message map functions
	//{{AFX_MSG(CDlgMapName)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnTree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
