// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2001 10:29:15 
//
// @doc
// @module PopupMenu.h | Declaration of the <c CPopupMenu> class

#if !defined(_POPUPMENU_H__0E95718C_046E_4214_B9B8_6AF005214DA4__INCLUDED_)
#define _POPUPMENU_H__0E95718C_046E_4214_B9B8_6AF005214DA4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

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
		_ASSERTE(NULL != m_pMenu);
		m_pMenu -> EnableMenuItem (nItem, MF_BYCOMMAND | ((bEnable) ? MF_ENABLED : MF_GRAYED));
	}
	void CheckItem (UINT nItem, BOOL fChecked = TRUE)
	{
		_ASSERTE(NULL != m_pMenu);
		m_pMenu -> CheckMenuItem (nItem, fChecked ? MF_CHECKED : MF_UNCHECKED);
	}
	void RemoveItem (UINT nItem, UINT uiFlags = MF_BYCOMMAND)
	{
		_ASSERTE(NULL != m_pMenu);
		m_pMenu -> RemoveMenu(nItem, uiFlags);
	}
	void DeletePopup (int iPopup)
	{
		_ASSERTE(NULL != m_pMenu);
		m_pMenu -> DeleteMenu(iPopup, MF_BYPOSITION);
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

#endif // !defined(_POPUPMENU_H__0E95718C_046E_4214_B9B8_6AF005214DA4__INCLUDED_)
