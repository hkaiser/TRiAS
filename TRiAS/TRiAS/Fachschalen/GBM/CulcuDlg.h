// CulcuDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCulcuDlg dialog
class CCulcuDlg : public CDialog
{
// Construction
public:
	CCulcuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCulcuDlg)
	enum { IDD = IDD_CALCULATOR };
	CString	m_strText1;
	CString	m_strText2;
	CString	m_strText3;
	CString	m_strText4;
	CString	m_strText5;
	CString	m_strText6;
	CString	m_strText7;
	CString	m_strText8;
	CString	m_strText9;
	CString	m_strText10;
	CString	m_strText11;
	CString	m_strtext12;
	CString	m_strText13;
	CString	m_strText20;
	CString	m_strText21;
	CString	m_strText22;
	CString	m_strText23;
	CString	m_strText24;
	CString	m_strText25;
	CString	m_strText26;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCulcuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCulcuDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
