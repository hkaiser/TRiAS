// DaoLayer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DaoLayer.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoLayerApp

BEGIN_MESSAGE_MAP(CDaoLayerApp, CWinApp)
	//{{AFX_MSG_MAP(CDaoLayerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaoLayerApp construction

CDaoLayerApp::CDaoLayerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDaoLayerApp object

CDaoLayerApp theApp;
