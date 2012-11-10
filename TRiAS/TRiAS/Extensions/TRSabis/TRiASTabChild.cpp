// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 04.06.2002 10:57:36 
//
// @doc
// @module TRiASTabChild.cpp | Definition of the <c CTRiASTabChild> class

#include "stdafx.h"
#include "TRSABIS.h"
#include "TRiASTabChild.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASTabChild

CTRiASTabChild::CTRiASTabChild(CWnd *pParent/* = NULL*/) :
	m_hIcon(NULL)
{
CRect rcSize;

	if (!CWnd::CreateEx(WS_EX_CONTROLPARENT, 
			AfxRegisterWndClass(CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW, 
				::LoadCursor(NULL, IDC_ARROW)), 
			"", WS_CHILD, rcSize, pParent, IDD))
	{
		TRACE("Failed to construct TabChildWnd!");
	}
	m_BackColor = GetSysColor(COLOR_WINDOW);
}

CTRiASTabChild::~CTRiASTabChild()
{
}


void CTRiASTabChild::SetBackgroundColor(COLORREF cBackColor)
{
	m_BackColor = cBackColor;
	Invalidate();
}

COLORREF CTRiASTabChild::GetBackgroundColor()
{
	return m_BackColor;
}

///////////////////////////////////////////////////////////////////////////////
// Anzuzeigendes Bildchen
bool CTRiASTabChild::EnsureIcon()
{
	if (NULL == m_hIcon) {
		m_hIcon = ::LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_SABiS));
		_ASSERTE(NULL != m_hIcon);
	}
	return (NULL != m_hIcon) ? true : false;
}

BEGIN_MESSAGE_MAP(CTRiASTabChild, CWnd)
	//{{AFX_MSG_MAP(CTRiASTabChild)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTRiASTabChild message handlers

BOOL CTRiASTabChild::OnEraseBkgnd(CDC* pDC) 
{
	// Input abtesten
	if (NULL == pDC)
		return false;

	CRect InvRect;
	GetClientRect(&InvRect); 

	pDC->FillSolidRect(InvRect, m_BackColor);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// PreTranslateMessage (copied from DlgCore.cpp)
#define _countof(array) (sizeof(array)/sizeof(array[0]))

BOOL AFXAPI _CompareClassName(HWND hWnd, LPCTSTR lpszClassName)
{
	ASSERT(::IsWindow(hWnd));
	TCHAR szTemp[32];
	::GetClassName(hWnd, szTemp, _countof(szTemp));
	return lstrcmpi(szTemp, lpszClassName) == 0;
}

BOOL CTRiASTabChild::PreTranslateMessage(MSG* pMsg)
{
	// for modeless processing (or modal)
	ASSERT(m_hWnd != NULL);

	// allow tooltip messages to be filtered
	if (CWnd::PreTranslateMessage(pMsg))
		return TRUE;

	// don't translate dialog messages when in Shift+F1 help mode
	CFrameWnd* pFrameWnd = GetTopLevelFrame();
	if (pFrameWnd != NULL && pFrameWnd->m_bHelpMode)
		return FALSE;

	// start with first parent frame
	pFrameWnd = GetParentFrame();
	while (pFrameWnd != NULL)
	{
	// allow parent frames to translate before DialogMessage does
		if (pFrameWnd->PreTranslateMessage(pMsg))
			return TRUE;

	// try parent frames until there are no parent frames
		pFrameWnd = pFrameWnd->GetParentFrame();
	}

	// fix around for VK_ESCAPE in a multiline Edit that is on a Dialog
	// that doesn't have a cancel or the cancel is disabled.
	if (pMsg->message == WM_KEYDOWN &&
		(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_CANCEL) &&
		(::GetWindowLong(pMsg->hwnd, GWL_STYLE) & ES_MULTILINE) &&
		_CompareClassName(pMsg->hwnd, _T("Edit")))
	{
		HWND hItem = ::GetDlgItem(m_hWnd, IDCANCEL);
		if (hItem == NULL || ::IsWindowEnabled(hItem))
		{
			SendMessage(WM_COMMAND, IDCANCEL, 0);
			return TRUE;
		}
	}
	// filter both messages to dialog and from children
	return PreTranslateInput(pMsg);
}
