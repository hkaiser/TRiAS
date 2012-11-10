// FreeRelD.hpp : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFreeRelDialog dialog

class CFreeRelDialog : public CDialog
{
// Construction
public:
	BOOL m_bResult;
	CFreeRelDialog(CWnd* pParent, CString &strMaster,
				   CString &strKoppelField, short sKType, HPROJECT hPr);  

// Dialog Data
	//{{AFX_DATA(CFreeRelDialog)
	enum { IDD = IDD_FREE_REL };
	CButton	m_btStoreConnection;
	CComboBox	m_cbTables;
	CComboBox	m_cbKoppelFields;
	CTabbedDialogs m_tbDsn;
	CHelpText	m_stDescription;
	CEdit	m_edAliasName;
	CFileDlg m_dlgFileDsn;
	CUserDlg m_dlgUserDsn;
	CUserDlg m_dlgSystemDsn;
	//}}AFX_DATA

	BOOL Result (void) { return m_bResult; }
	BOOL GetRelation (CString &strAliasName,   	// aktuelle Relation lesen
					  CString &strKoppelField);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreeRelDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CODBCInfos m_OdbcInfos;
	CString m_strKoppelField;
	CString m_strAliasName;
	CString m_strDsn;
	BOOL m_bInfosStored;
	short m_sKoppelType;
	DataSourceType m_tType;
	HPROJECT m_hProject;
	
	void SetStoreButton (void);			// Store-Button akt.
	void ResetODBCInfos (void); 		// alle über ODBC gelesenen Infos löschen 
	BOOL StoreActConnection (void);		//	aktuellen Anbindungen speichern 

	// Generated message map functions
	//{{AFX_MSG(CFreeRelDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeKoppelfield();
	afx_msg void OnSelchangeTablename();
	afx_msg void OnChangeAliasname();
	afx_msg void OnOutputAliasDescription();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
