// GPSImport.h : main header file for the GPSImport application
//

#if !defined(AFX_GPSIMPORT_H__472CE383_0FE4_4E4E_87F5_34BC3A0D0118__INCLUDED_)
#define AFX_GPSIMPORT_H__472CE383_0FE4_4E4E_87F5_34BC3A0D0118__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGPSImportWApp:
// See GPSImport.cpp for the implementation of this class
//

class CGPSImportApp : public CWinApp
{
public:
	CGPSImportApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPSImportWApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGPSImportApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSIMPORTW_H__472CE383_0FE4_4E4E_87F5_34BC3A0D0118__INCLUDED_)
