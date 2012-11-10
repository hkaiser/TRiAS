// SelTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelTable dialog

class CSelTable : public CDialog
{
// Construction
public:
	CString m_strTableName, m_strCaption;
	CDatabase *m_pDataBase;
	BOOL m_bEnterNew, m_bTableExists;

	CSelTable(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelTable)
	enum { IDD = IDD_SELECT_TABLE };
	CButton	m_btOk;
	CListBox	m_lbTables;
	CEdit	m_edTable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelTable)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeTable();
	afx_msg void OnDblclkListTables();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeListTables();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
