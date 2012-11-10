// ErzInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErzInfo dialog

class CErzInfo : public CDialog
{
// Construction
public:
	CErzInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CErzInfo)
	enum { IDD = IDD_ERZ_INFO };
	CString	m_strAnfOrt;
	CString	m_strAnf;
	CString	m_strBranche;
	CString	m_strFax;
	CString	m_strPartner;
	CString	m_strTel;
	CString	m_strFirma;
	CString	m_strStrasse;
	//}}AFX_DATA

	CString m_strErzNr;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErzInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErzInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
