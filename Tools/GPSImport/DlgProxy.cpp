// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "GPSImport.h"
#include "DlgProxy.h"
#include "GPSImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPSImportDlgAutoProxy

IMPLEMENT_DYNCREATE(CGPSImportDlgAutoProxy, CCmdTarget)

CGPSImportDlgAutoProxy::CGPSImportDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CGPSImportDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CGPSImportDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CGPSImportDlgAutoProxy::~CGPSImportDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CGPSImportDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CGPSImportDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CGPSImportDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGPSImportDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CGPSImportDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IGPSImport to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {4F5C7448-666A-455e-8567-1720211CD6FE}
static const IID IID_IGPSImport =
{ 0x4F5C7448, 0x666A, 0x455e, { 0x85, 0x67, 0x17, 0x20, 0x21, 0x1C, 0xD6, 0xFE } };

BEGIN_INTERFACE_MAP(CGPSImportDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CGPSImportDlgAutoProxy, IID_IGPSImport, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {7F951599-25B0-480b-B0C9-419B1336A0F5}
IMPLEMENT_OLECREATE2(CGPSImportDlgAutoProxy, "GPSImport.Application", 0x7F951599, 0x25B0, 0x480b, 0xB0, 0xC9, 0x41, 0x9B, 0x13, 0x36, 0xA0, 0xF5)

/////////////////////////////////////////////////////////////////////////////
// CGPSImportDlgAutoProxy message handlers
