// DlgMapSpecial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSpecial dialog

class CDlgMapSpecial : public CDialog
{
// Construction
public:
	CDlgMapSpecial(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMapSpecial)
	enum { IDD = IDD_DLG_MAPSPECIAL };
	CStatic	m_bmp2;
	CStatic	m_bmp1;
	long	m_X;
	long	m_Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapSpecial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMapSpecial)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
