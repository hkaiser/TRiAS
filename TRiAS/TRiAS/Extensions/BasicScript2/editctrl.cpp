// editctrl.cpp : implementation file
//
#include "bscriptp.hxx"
#include "bscript.h"

#include <iobjman.h>
#include <registrx.hxx>

#include "macrguid.h"

#include "iscrprop.h"

#include "strinfo.h"
#include "mru.h"
#include "dummypar.h"
#include "conststr.h"
#include "toolbarx.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "DebCtrl.h"
#include "splitter.h"
#include "split.h"
#include "editctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// The following names from WINDOWSX.H collide with names in this file
#undef SubclassWindow

/////////////////////////////////////////////////////////////////////////////
// CEditCtrl
CEditCtrl::CEditCtrl()
{
	m_pDebugger = NULL;
	m_hAccel = NULL;
}

CEditCtrl::~CEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CEditCtrl, CWnd)
	//{{AFX_MSG_MAP(CEditCtrl)
	ON_COMMAND(ID_DEBUG_GO, OnDebugGo)
	ON_COMMAND(ID_DEBUG_TRACEIN, OnDebugTracein)
	ON_WM_NCDESTROY()
	ON_COMMAND(ID_DEBUG_TRACEOVER, OnDebugTraceover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditCtrl message handlers
BOOL CEditCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	ASSERT(pParentWnd);
	if (!SubClassEditWindow(((CDebuggerCtrl *)pParentWnd) -> GetDebugger()))
		return false;
	return GetAccelerator();
}

bool CEditCtrl::SubClassEditWindow(CebDebugger *pDeb)
{
// Parent ist hier nun Debugger
	ASSERT(pDeb);

	m_pDebugger = pDeb;
	
	char buf[40];
	HWND hWndEdit = ::GetWindow(GetDebugger() -> GetWindow(), GW_CHILD);

	while (hWndEdit) 
	{
		GetClassName(hWndEdit, buf, sizeof(buf));
		if (!lstrcmpi(PRODUCT_EDIT_CLASS, buf)) break;
		hWndEdit = ::GetWindow(hWndEdit, GW_HWNDNEXT);
	}

	if (hWndEdit)
	{
		if (!SubclassWindow(hWndEdit))
			return false;
	}

	return true;
}

void CEditCtrl::OnNcDestroy() 
{	
	if (m_hWnd && IsWindow(m_hWnd))
	{
		UnsubclassWindow();
	}
	CWnd::OnNcDestroy();
}

BOOL CEditCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		ASSERT(m_hAccel);
		if (NULL != m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
			return true;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

bool CEditCtrl::GetAccelerator()
{
	ASSERT(g_hInstance);
	// free automaticly
	m_hAccel = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_EDITCTRL));
	ASSERT(m_hAccel);
	if (m_hAccel) return true;

	return false;
}

void CEditCtrl::OnDebugGo() 
{
	CWnd *pWnd = GetParent();
	ASSERT(pWnd);

	GetParent() -> SendMessage(WM_COMMAND, ID_DEBUG_GO);	
}

void CEditCtrl::OnDebugTracein() 
{
	CWnd *pWnd = GetParent();
	ASSERT(pWnd);

	GetParent() -> SendMessage(WM_COMMAND, ID_DEBUG_TRACEIN);	
}


void CEditCtrl::OnDebugTraceover() 
{
	GetParent() -> SendMessage(WM_COMMAND, ID_DEBUG_TRACEOVER);	
}
