// InTablPg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputTablePage dialog

class CInputTablePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CInputTablePage)

// Construction
public:
	CInputTablePage();
	~CInputTablePage();

	void SetParams (CImportParams &Params);

// Dialog Data
	//{{AFX_DATA(CInputTablePage)
	enum { IDD = IDD_IMPORT_INPUT };
	CListBox	m_lbTables;
	CEdit	m_edDatabase;
	CButton	m_btMdbTable;
	CButton	m_btAbfall;
//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInputTablePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImportParams *m_pParams;
	void SetWizardButton (void);
	void SetTableInfo (ImportType iType, TableType tType);
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd::GetParent (); }
	BOOL CheckDatabase (void);
	BOOL m_bOpenTyp;
	// Generated message map functions
	//{{AFX_MSG(CInputTablePage)
	afx_msg void OnHelp();
	afx_msg void OnMdbTable();
	afx_msg void OnFoxTable();
	afx_msg void OnChangeDatabase();
	afx_msg void OnAbfall();
	afx_msg void OnErzeuger();
	afx_msg void OnBranch();
	afx_msg void OnAbfallArten();
	afx_msg void OnTransporteure();
	afx_msg void OnEntsorger();
	afx_msg void OnGemeinden();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTables();
	afx_msg void OnOldVersionMdb();
	afx_msg void OnOldVersionFox();
	afx_msg void OnKreise();
	afx_msg void OnVerbringung();
	afx_msg void OnVerfahren();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
