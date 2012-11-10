// StatBarE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusBarExt window

class CStatusBarExt : public CStatusBar
{
// Construction
public:
	BOOL m_bIgnoreSetText;		// Nachricht WM_SETTEXT ign.
	CStatusBarExt(void) { m_bIgnoreSetText = FALSE; }

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarExt)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusBarExt() {}

	// Generated message map functions
protected:
	//{{AFX_MSG(CStatusBarExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT OnSetText (WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
