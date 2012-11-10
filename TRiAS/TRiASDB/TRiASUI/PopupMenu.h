// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/03/1998 09:58:23 AM
//
// @doc
// @module PopupMenu.h | Description goes here

#if !defined(_POPUPMENU_H__F57F67A5_723B_11D2_9EEF_006008447800__INCLUDED_)
#define _POPUPMENU_H__F57F67A5_723B_11D2_9EEF_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// class CPopUpMenu
class CPopUpMenu 
{
public:
// Constructors:
	CPopUpMenu (CWnd *pWnd, UINT nIDMenu, INT_PTR dwData = 0, UINT nSubMenu = 0, CPoint *pPt = NULL);
	CPopUpMenu (CWnd *pWnd, CMenu *pMenu, INT_PTR dwData = 0, UINT nSubMenu = 0, CPoint *pPt = NULL);
	virtual ~CPopUpMenu();

public:
// Operations:
	void EnableItem (UINT nItem, BOOL bEnable = TRUE)
	{
		m_pMenu -> EnableMenuItem (nItem, MF_BYCOMMAND | ((bEnable) ? MF_ENABLED : MF_GRAYED));
	}
	INT_PTR GetMenuData() { return m_dwData; }
	void SetMenuData (INT_PTR dwData) { m_dwData = dwData; }

	CMenu *GetSubMenu() { _ASSERTE(NULL != m_pMenu); return m_pMenu -> GetSubMenu (m_nSubMenu); }
	CMenu *GetMenu() { _ASSERTE(NULL != m_pMenu); return m_pMenu; }
	
// Virtual operations:
	virtual void UpdateUI(CCmdTarget* pTarget, BOOL bDisableIfNoHndler);
	virtual DWORD Track(UINT uiTrackFlags = TPM_LEFTALIGN|TPM_LEFTBUTTON);

protected:
	static void UpdateMenu (CMenu *pParent, CMenu *pMenu, CCmdTarget *pTarget, BOOL bDisableIfNoHndler);

protected:
// Implementation:
	CMenu *m_pMenu;
	BOOL m_fAttached;
	CWnd *m_pWnd;
	CPoint m_Point;
	UINT m_nSubMenu;
	UINT m_nDefItem;
	BOOL m_bInAction;
	INT_PTR m_dwData;		// evtl. zusätzliche (Kontext-) Daten
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_POPUPMENU_H__F57F67A5_723B_11D2_9EEF_006008447800__INCLUDED_)
