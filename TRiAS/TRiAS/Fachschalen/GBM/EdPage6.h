// EdPage6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditPage6 dialog

class CEditPage6 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditPage6)

// Construction
public:
	CEditPage6();
	~CEditPage6();

// Dialog Data
	//{{AFX_DATA(CEditPage6)
	enum { IDD = IDD_EDITPAGE6 };
	CString	m_strBem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditPage6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditPage6)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
