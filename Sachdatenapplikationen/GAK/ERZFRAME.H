// ErzFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErzFrame frame

class CErzFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CErzFrame)
protected:
	CErzFrame() {}           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErzFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CErzFrame() {}

	// Generated message map functions
	//{{AFX_MSG(CErzFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
