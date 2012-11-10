// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "CopyDLKW.h"
#include "DlgProxy.h"
#include "CopyDLKWDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKWDlgAutoProxy

IMPLEMENT_DYNCREATE(CCopyDLKWDlgAutoProxy, CCmdTarget)

CCopyDLKWDlgAutoProxy::CCopyDLKWDlgAutoProxy()
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
	ASSERT_KINDOF(CCopyDLKWDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CCopyDLKWDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CCopyDLKWDlgAutoProxy::~CCopyDLKWDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CCopyDLKWDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CCopyDLKWDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CCopyDLKWDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCopyDLKWDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCopyDLKWDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICopyDLKW to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {7B9062F7-7AC7-456A-BB57-E195F9BEAFEB}
static const IID IID_ICopyDLKW =
{ 0x7b9062f7, 0x7ac7, 0x456a, { 0xbb, 0x57, 0xe1, 0x95, 0xf9, 0xbe, 0xaf, 0xeb } };

BEGIN_INTERFACE_MAP(CCopyDLKWDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CCopyDLKWDlgAutoProxy, IID_ICopyDLKW, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {4CEF2C91-1754-41F7-B240-C3F7B25DE487}
IMPLEMENT_OLECREATE2(CCopyDLKWDlgAutoProxy, "CopyDLKW.Application", 0x4cef2c91, 0x1754, 0x41f7, 0xb2, 0x40, 0xc3, 0xf7, 0xb2, 0x5d, 0xe4, 0x87)

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKWDlgAutoProxy message handlers
