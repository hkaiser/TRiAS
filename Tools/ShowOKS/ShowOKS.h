// ShowOKS.h : main header file for the SHOWOKS application
//

#if !defined(AFX_SHOWOKS_H__0AC131D7_C5EF_11D0_9595_00A024D6F582__INCLUDED_)
#define AFX_SHOWOKS_H__0AC131D7_C5EF_11D0_9595_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowOKSApp:
// See ShowOKS.cpp for the implementation of this class
//

class CShowOKSApp : public CWinApp
{
public:
	CShowOKSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowOKSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShowOKSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWOKS_H__0AC131D7_C5EF_11D0_9595_00A024D6F582__INCLUDED_)
