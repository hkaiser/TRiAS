// NewQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewQueryDef dialog
class CDaoDatabase;

class CNewQueryDef : public CDialog
{
// Construction
public:
	CNewQueryDef(CWnd* pParent, CDaoDatabase *pDatabase);   // standard constructor
	~CNewQueryDef (void);

	BOOL CheckSQL (const CString &);	// SQL-Ausdruck prüfen

	CString m_strName;
	CString m_strSQL;

// Dialog Data
	//{{AFX_DATA(CNewQueryDef)
	enum { IDD = IDD_QUERY_DEF };
	CButton	m_btAbfrageArt;
	CButton	m_btErrorHelp;
	CStatic	m_stTables;
	CStatic	m_stOperators;
	CStatic	m_stFunctions;
	CStatic	m_stFields;
	CButton	m_btCheck;
	CEdit	m_edDescription;
	CButton	m_btBack;
	CListBox	m_lbTables;
	CListBox	m_lbOperators;
	CListBox	m_lbFunctions;
	CListBox	m_lbFields;
	CButton	m_btOk;
	CEdit	m_edSQL;
	CEdit	m_edName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewQueryDef)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoDatabase *m_pDatabase;
	CString m_strTableName;

	void SetControlState ();
	void DeleteFieldInfos (void);

	void DisplayDaoException (CDaoException *de);

	// Generated message map functions
	//{{AFX_MSG(CNewQueryDef)
	virtual void OnOK();
	afx_msg void OnChangeName();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSql();
	afx_msg void OnSelchangeFields();
	afx_msg void OnDblclkFields();
	afx_msg void OnDblclkTables();
	afx_msg void OnSelchangeTables();
	afx_msg void OnSelchangeOperators();
	afx_msg void OnDblclkOperators();
	afx_msg void OnDblclkFunctions();
	afx_msg void OnSelchangeFunctions();
	afx_msg void OnEdBack();
	afx_msg void OnCheck();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnQueryArt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
