// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/03/1998 10:01:10 AM
//
// @doc
// @module PopupMenu.cpp | Description goes here

#include <stdafx.h>

#include "PopupMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////
// class CPopUpMenu

// Default Constructor
CPopUpMenu::CPopUpMenu(CWnd *pWnd, UINT nIDMenu, INT_PTR dwData, UINT nSubMenu, CPoint *pPt)
	: m_pWnd(pWnd), m_Point(10, 10), m_nSubMenu(nSubMenu), m_bInAction(FALSE), m_dwData(dwData)
{
	if (NULL != pPt)
		m_Point = *pPt;
	else 
		::GetCursorPos (&m_Point);

	ATLTRY(m_pMenu = new CMenu());
	m_fAttached = false;
	VERIFY(m_pMenu -> LoadMenu(nIDMenu));
}

CPopUpMenu::CPopUpMenu(CWnd *pWnd, CMenu *pMenu, INT_PTR dwData, UINT nSubMenu, CPoint *pPt)
	: m_pWnd(pWnd), m_Point(10, 10), m_nSubMenu(nSubMenu), m_bInAction(FALSE), m_dwData(dwData)
{
	if (NULL != pPt)
		m_Point = *pPt;
	else 
		::GetCursorPos (&m_Point);

	m_pMenu = pMenu;
	m_fAttached = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
CPopUpMenu::~CPopUpMenu()
{
	if (!m_fAttached) {
		delete m_pMenu;
		m_pMenu = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
DWORD CPopUpMenu::Track(UINT uiTrackFlags)
{
DWORD dwCmd = 0;

	if (!m_bInAction) {
		m_bInAction = TRUE;
	
	CMenu *pPopupMenu = GetSubMenu();

		ASSERT(NULL != pPopupMenu);

	// By position
		if (0 != m_nDefItem) 
			SetMenuDefaultItem (pPopupMenu->m_hMenu, m_nDefItem, TRUE);
		dwCmd = pPopupMenu->TrackPopupMenu (uiTrackFlags, m_Point.x, m_Point.y, m_pWnd);
		m_bInAction = FALSE;
	}
	return dwCmd;
}

///////////////////////////////////////////////////////////////////////////////
//
/*static*/
void CPopUpMenu::UpdateMenu (CMenu *pParent, CMenu *pMenu, CCmdTarget *pTarget, BOOL bDisableIfNoHndler)
{
	if (pMenu == NULL)
		return;

const int imax = pMenu -> GetMenuItemCount();
CCmdUI ui;

	ui.m_pParentMenu = pParent;
	ui.m_nIndexMax = imax;
	for (int i = 0; i < imax; i++) {
	int nID = pMenu->GetMenuItemID(i);

		ui.m_nIndex = i;
		ui.m_nID = nID;

		ui.m_pMenu = pMenu;
		ui.m_pSubMenu = NULL;
		ui.m_pOther = NULL;
		ui.DoUpdate (pTarget, bDisableIfNoHndler);
	
	// Recurce to submenus
		UpdateMenu (pMenu, pMenu->GetSubMenu(i), pTarget, bDisableIfNoHndler);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
void CPopUpMenu::UpdateUI(CCmdTarget* pTarget, BOOL bDisableIfNoHndler)
{
CMenu* pPopupMenu = GetSubMenu();

	ASSERT(NULL != pPopupMenu);
	UpdateMenu (GetMenu(), pPopupMenu, pTarget, bDisableIfNoHndler);
}
