// SuchResDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchResDlg dialog

class CSuchResDlg : public CDialog
{
// Construction
public:
	CSuchResDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSuchResDlg)
	enum { IDD = IDD_SUCHRESULT };
	CStatic	m_txtInfo;
	CString	m_strGesamt;
	CString	m_strGesamt2;
	//}}AFX_DATA
	int	m_iGesamt;
	int m_iFehl;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuchResDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSuchResDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
