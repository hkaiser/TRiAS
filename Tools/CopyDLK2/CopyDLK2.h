// CopyDLK2.h : main header file for the COPYDLK2 application
//

#if !defined(AFX_COPYDLK2_H__8D29722C_B6B1_45F9_B4D6_8C84C216F536__INCLUDED_)
#define AFX_COPYDLK2_H__8D29722C_B6B1_45F9_B4D6_8C84C216F536__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CopyDLK2_i.h"

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKApp:
// See CopyDLK2.cpp for the implementation of this class
//

class CCopyDLKApp : public CWinApp
{
public:
	CCopyDLKApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyDLKApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCopyDLKApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bATLInited;
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYDLK2_H__8D29722C_B6B1_45F9_B4D6_8C84C216F536__INCLUDED_)
