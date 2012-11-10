// Stat1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatus1Dlg dialog

class CStatus1Dlg : public CDialog
{
// Construction
public:
	void Text( short, const char* );
	CStatus1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatus1Dlg)
	enum { IDD = IDD_STATUS1 };
	CString	m_strText0;
	CString	m_strText1;
	CString	m_strText2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatus1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatus1Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
