// exportre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportResultDlg dialog

class CExportResultDlg : public CDialog
{
// Construction
public:
	CExportResultDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExportResultDlg)
	enum { IDD = IDD_EXPORT_RESULT };
	CString	m_strAbfCnt;
	CString	m_strErzCnt;
	CString	m_strSumCnt;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CExportResultDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
