// TablNDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableNameDlg dialog
class CTableNameDlg : public CDialog
{
// Construction
public:
	CTableNameDlg(CWnd* pParent, CString strDatabase); 

	CString m_strTableName,
			m_strDatabase;

// Dialog Data
	//{{AFX_DATA(CTableNameDlg)
	enum { IDD = IDD_INPUT_TABLE_NAME };
	CEdit	m_edDatabase;
	CEdit	m_edName;
	CButton	m_btOk;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableNameDlg)
	afx_msg void OnChangeName();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectDatabase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
