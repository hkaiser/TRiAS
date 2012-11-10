// udlist.h : main header file for the UDLIST application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include <LGeoRes.h>

/////////////////////////////////////////////////////////////////////////////
// CMapMgrApp:
// See udlist.cpp for the implementation of this class
//

class CMapMgrApp : public CWinApp
{
public:
	CMapMgrApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation
protected:
	BOOL	FirstInstance();

	//{{AFX_MSG(CMapMgrApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
