// Das CWinApp für TRiAS
// File: THISDLL.H

#if !defined(_THISDLL_H)
#define _THISDLL_H

#include <AniWaitCursor.h>

class CThisDLL : 
	public CWinApp 
{
protected:
	HCURSOR m_hAniCursors[ANICURSOR_MAX];
	HCURSOR m_hWaitCursorRestore;
	int m_nWaitCursorCount;

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThisDLL)
	public:
	virtual BOOL InitInstance (void);	// Initialization
	virtual int ExitInstance (void);	// Termination (WEP-like code)
	virtual BOOL IsIdleMessage(MSG* pMsg);  // checks for special messages
	void DoWaitCursor(int nCode);		// WaitCursorHandling
	//}}AFX_VIRTUAL

// nothing special for the constructor
		CThisDLL (const char* pszAppName) 
			: CWinApp(pszAppName),
			  m_hWaitCursorRestore(NULL), m_nWaitCursorCount(0)
		{
			memset(m_hAniCursors, '\0', sizeof(HCURSOR)*ANICURSOR_MAX);
		}

	//{{AFX_MSG(CThisDLL)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
// Printersupport
	BOOL UpdatePrinterSelection(DVTARGETDEVICE *ptd);
};

#endif // _THISDLL_H
