// SuchDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchDialog dialog

class CSuchDialog : public CDialog
{
// Construction
public:
	CSuchDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSuchDialog)
	enum { IDD = IDD_SUCHEN };
	CTabCtrl	m_tabSuch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSuchDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
