// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.03.2001 13:34:00 
//
// @doc
// @module Docking3DTab.cpp | Definition of the <c CDocking3DTab> class

#include "stdafx.h"

#if defined(_USE_DOCKEDTABWINDOW)

#include <Com/ComBool.h>

#include "fakemfc.h"
#include "Docking3DTab.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDocking3DTab, SEC3DTabWnd)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CDocking3DTab

CDocking3DTab::CDocking3DTab()
{
}

CDocking3DTab::~CDocking3DTab()
{
}

int CDocking3DTab::ClickedOnTab()
{
CDocking3DTabControl *pTabCtrl = (CDocking3DTabControl *)GetTabControl();

	_ASSERTE(NULL != pTabCtrl);
	_ASSERTE(pTabCtrl -> IsKindOf(RUNTIME_CLASS(CDocking3DTabControl)));

CPoint ptMouse;

	GetCursorPos(&ptMouse);
	pTabCtrl -> ScreenToClient(&ptMouse);
	for (int i = 0; i < GetTabCount(); ++i) {
		if (pTabCtrl -> TabHit(i, ptMouse))
			return i;
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen einer TabBeschreibung
HRESULT CDocking3DTab::AddTabWindowDelayed(BSTR bstrName, ITabWindowCallback *pICallback)
{
	COM_TRY {
	CKnownTabs::iterator it = m_Tabs.find(bstrName);

		if (it != m_Tabs.end())
			return S_FALSE;		// kennen wir schon

		m_Tabs.insert(CKnownTabs::value_type(bstrName, CTabMapData(pICallback, 0)));

	} COM_CATCH;
	return S_OK;
}

SECTab *CDocking3DTab::AddTab(CWnd *pWnd, LPCTSTR lpszLabel)
{
	return SEC3DTabWnd::AddTab(pWnd, lpszLabel);
}

BOOL CDocking3DTab::FindTab(const CWnd* const pWnd, int& nTab) const
{
	return SEC3DTabWnd::FindTab(pWnd, nTab);
}

void CDocking3DTab::RemoveTab(int nIndex, bool fRemoveCallback)
{
// erstmal sicherstellen, daß das Tabfenster zerlegt wird
	USES_CONVERSION;
	for (CKnownTabs::iterator it = m_Tabs.begin(); it != m_Tabs.end(); ++it) {
	int iTabIndex = FindTab (OLE2A((*it).first));		// Name des Tabfensters

		if (iTabIndex == nIndex) {
		// existierendes Tabfenster ausblenden
			(*it).second.first -> DeleteTabWindow();
			if (fRemoveCallback)
				m_Tabs.erase(it);
			break;
		}
	}
	SEC3DTabWnd::RemoveTab(nIndex);
}

BOOL CDocking3DTab::RenameTab(int nIndex, BSTR bstrOldName, BSTR bstrNewName)
{
	USES_CONVERSION;
	COM_TRY {
		if (!wcscmp(bstrOldName, bstrNewName)) 
			return TRUE;

	CKnownTabs::iterator it = m_Tabs.find(bstrOldName);

		if (it == m_Tabs.end())
			return FALSE;		// kennen wir nicht

		m_Tabs.insert(CKnownTabs::value_type(bstrNewName, (*it).second));
		m_Tabs.erase(it);

		SEC3DTabWnd::RenameTab(nIndex, OLE2A(bstrNewName));

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 

BEGIN_MESSAGE_MAP(CDocking3DTab, SEC3DTabWnd)
	//{{AFX_MSG_MAP(CDocking3DTab)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocking3DTab message handlers

int CDocking3DTab::FindTab (LPCTSTR pcName)
{
	for (int i = 0; i < GetTabCount(); ++i) {
	LPCSTR pcMenu = NULL;
	BOOL fSelected = FALSE;
	CWnd *pWnd = NULL;
	void *pExtra = NULL;

		if (GetTabInfo(i, pcMenu, fSelected, pWnd, pExtra)) {
			if (!strcmp (pcMenu, pcName))
				return i;
		}
	}
	return -1;
}

void CDocking3DTab::OnExtendContextMenu(CMenu* pCtxMenu)
{
	_ASSERTE(-1 != ClickedOnTab());

int iCnt = GetTabCount();

	_ASSERTE(0 < iCnt);
	pCtxMenu -> AppendMenu(MF_SEPARATOR);

UINT uiID = SEC_IDW_TABCLIENT_FIRST; 

	USES_CONVERSION;
	for (CKnownTabs::iterator it = m_Tabs.begin(); it != m_Tabs.end(); ++it) {
	LPCSTR pcMenu = OLE2A((*it).first);
	int iTabIndex = FindTab (pcMenu);

	BOOL fSelected = FALSE;
	CWnd *pWnd = NULL;
	void *pExtra = NULL;

		if (iTabIndex >= 0 && GetTabInfo(iTabIndex, pcMenu, fSelected, pWnd, pExtra)) {
			if (1 == iCnt) 
				pCtxMenu -> AppendMenu(MF_STRING|MF_GRAYED|MF_CHECKED, uiID, pcMenu);
			else {
			CComBool fMayAdd;

				(*it).second.first -> get_MayAddTabWindow(&fMayAdd);
				pCtxMenu -> AppendMenu(MF_CHECKED|MF_STRING|(fMayAdd ? 0 : MF_GRAYED), uiID, pcMenu);
			}
		} 
		else {
//			_ASSERTE(1 < iCnt);		// es müssen mehr als ein Tabfenster da sein
			pCtxMenu -> AppendMenu(MF_STRING, uiID, pcMenu);
		}
		(*it).second.second = uiID;		// zugehörigen MenuID speichern
		++uiID;							// nächster MenuID
	}
	_ASSERTE(uiID < SEC_IDW_TABCLIENT_FIRST+256);
}

///////////////////////////////////////////////////////////////////////////////
// Menucommand
void CDocking3DTab::OnTabCommand(UINT uiID)
{
	USES_CONVERSION;
	for (CKnownTabs::iterator it = m_Tabs.begin(); it != m_Tabs.end(); ++it) {
		if (uiID == (*it).second.second) {
		int iTabIndex = FindTab (OLE2A((*it).first));		// Name des Tabfensters

			if (iTabIndex >= 0) {
			// existierendes Tabfenster ausblenden
				(*it).second.first -> DeleteTabWindow();
			}
			else {
			// nicht sichtbares Tabfenster anzeigen
				(*it).second.first -> AddTabWindow();
			}
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Private drawing helpers for drawing 3D lines and fills.
// Note, draw Vert lines before Horz lines.
// This is necessary so the joining of a horz
// and vert line is drawn properly.
const COLORREF rgbBlack = RGB(0,0,0);
const COLORREF rgbWhite = RGB(255,255,255);
const COLORREF rgbShadow = ::GetSysColor(COLOR_BTNSHADOW);
const COLORREF rgbFace = ::GetSysColor(COLOR_BTNFACE);

void CDocking3DTab::VLine3DEx(CDC* pDC, int x, int y, int nHeight)
{
	rgbFill(pDC, x,   y, 1, nHeight, rgbWhite);
	rgbFill(pDC, x+1, y, 1, nHeight, rgbFace);
	rgbFill(pDC, x+2, y, 1, nHeight, rgbShadow);
	rgbFill(pDC, x+3, y, 1, nHeight, rgbBlack);
}

void CDocking3DTab::HLine3DEx(CDC* pDC, int x, int y, int nWidth, BOOL bFlip)
{
	if (bFlip) {
		rgbFill(pDC, x+2, y,   nWidth-5, 1, rgbWhite);
		rgbFill(pDC, x+1, y+1, nWidth-3, 1, rgbFace);
		rgbFill(pDC, x+1, y+2, nWidth-2, 1, rgbShadow);
		rgbFill(pDC, x,   y+3, nWidth,   1, rgbBlack);
	}
	else {
		rgbFill(pDC, x,   y,   nWidth-1, 1, rgbWhite);
		rgbFill(pDC, x+1, y+1, nWidth-3, 1, rgbFace);
		rgbFill(pDC, x+2, y+2, nWidth-6, 1, rgbShadow);
		rgbFill(pDC, x+3, y+3, nWidth-8, 1, rgbBlack);
	}
}

void CDocking3DTab::OnPaint() 
{
    ASSERT_VALID(this);

CPaintDC dc(this); // device context for painting
CRect rectInside;

	GetInsideRect(rectInside);

CRect rectInvalid;

    dc.GetClipBox(&rectInvalid);
    MapWindowPoints(m_pTabCtrl, rectInvalid);
	m_pTabCtrl->RedrawWindow(rectInvalid, NULL, RDW_INVALIDATE);
	m_pTabCtrl->UpdateWindow();

// Draw 3D borders
	VLine3DEx(&dc, rectInside.left-4, rectInside.top-4, rectInside.Height()+8);
	VLine3DEx(&dc, rectInside.right, rectInside.top-4, rectInside.Height()+8);
	HLine3DEx(&dc, rectInside.left-4, rectInside.top-4, rectInside.Width()+8);
	HLine3DEx(&dc, rectInside.left-4, rectInside.bottom+1, rectInside.Width()+8, TRUE);

	if (0 == GetTabCount()) 
		rgbFill(&dc, rectInside.left-3, rectInside.top-3, rectInside.right-1, rectInside.bottom+2, rgbFace);

	// Do not call SEC3DTabWnd::OnPaint() for painting messages
}

BOOL CDocking3DTab::CreateTabCtrl(DWORD dwStyle, UINT nID)
{
    ASSERT_VALID(this);

	m_pTabCtrl = new CDocking3DTabControl();
    ASSERT_VALID(this);
	VERIFY(m_pTabCtrl->Create(WS_VISIBLE | m_dwTabCtrlStyle,
		CRect(0, 0, 0, 0), this, nID));

	dwStyle; // UNUSED
	return (m_pTabCtrl != NULL);
}

#endif // defined(_USE_DOCKEDTABWINDOW)
