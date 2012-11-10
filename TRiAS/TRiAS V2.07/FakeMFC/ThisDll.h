// Das CWinApp für TRiAS
// File: THISDLL.H

#if !defined(_THISDLL_H)
#define _THISDLL_H

class CThisDLL : 
	public CWinApp 
{
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThisDLL)
	public:
	virtual bool InitInstance (void);	// Initialization
	virtual int ExitInstance (void);	// Termination (WEP-like code)
	virtual BOOL IsIdleMessage(MSG* pMsg);  // checks for special messages
	//}}AFX_VIRTUAL

// nothing special for the constructor
		CThisDLL (const char* pszAppName) 
			: CWinApp(pszAppName) {}

	//{{AFX_MSG(CThisDLL)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // _THISDLL_H
