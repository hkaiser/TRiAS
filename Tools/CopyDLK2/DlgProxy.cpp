// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "CopyDLK2.h"
#include "DlgProxy.h"
#include "CopyDLKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKDlgAutoProxy

IMPLEMENT_DYNCREATE(CCopyDLKDlgAutoProxy, CCmdTarget)

CCopyDLKDlgAutoProxy::CCopyDLKDlgAutoProxy()
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
	ASSERT_KINDOF(CCopyDLKDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CCopyDLKDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CCopyDLKDlgAutoProxy::~CCopyDLKDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CCopyDLKDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CCopyDLKDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CCopyDLKDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCopyDLKDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCopyDLKDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICopyDLK2 to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {820C20D5-392C-4144-8EC3-A1989A271CD7}
static const IID IID_ICopyDLK2 =
{ 0x820c20d5, 0x392c, 0x4144, { 0x8e, 0xc3, 0xa1, 0x98, 0x9a, 0x27, 0x1c, 0xd7 } };

BEGIN_INTERFACE_MAP(CCopyDLKDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CCopyDLKDlgAutoProxy, IID_ICopyDLK2, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {41E61E77-14C4-45CC-AD27-9D644227085D}
IMPLEMENT_OLECREATE2(CCopyDLKDlgAutoProxy, "CopyDLK2.Application", 0x41e61e77, 0x14c4, 0x45cc, 0xad, 0x27, 0x9d, 0x64, 0x42, 0x27, 0x8, 0x5d)

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKDlgAutoProxy message handlers
