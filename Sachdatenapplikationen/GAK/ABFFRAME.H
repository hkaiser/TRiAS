// AbfFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfFrame frame

class CAbfFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CAbfFrame)
protected:
	CAbfFrame() {}          // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAbfFrame() {}

	// Generated message map functions
	//{{AFX_MSG(CAbfFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
