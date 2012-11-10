// ViewPortDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewPortDlg dialog

class CViewPortDlg : public CDialog
{
// Construction
public:
	CViewPortDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewPortDlg)
	enum { IDD = IDD_VIEWPORTDATA };
	long	m_lVPoldOrgX;
	long	m_lVPoldOrgY;
	long	m_lVPoldExtX;
	long	m_lVPoldExtY;
	long	m_lVPnewOrgX;
	long	m_lVPnewOrgY;
	long	m_lVPnewExtX;
	long	m_lVPnewExtY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewPortDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
