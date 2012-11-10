// DlgTB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTB dialog

class CDlgTB : public CDialog
{
// Construction
public:
	CDlgTB(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTB)
	enum { IDD = IDD_VORBEREIT_TB };
	BOOL	m_bAnrFl;
	BOOL	m_bGesFl;
	BOOL	m_bGlobal;
	double	m_dTiefe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTB)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
