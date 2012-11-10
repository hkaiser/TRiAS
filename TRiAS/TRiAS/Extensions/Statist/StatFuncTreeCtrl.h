// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.01.2001 09:51:23 
//
// @doc
// @module StatFuncTreeCtrl.h | Declaration of the <c CStatFuncTreeCtrl> class

#if !defined(_STATFUNCTREECTRL_H__98298C61_C696_4E36_97AC_774D7D05AB95__INCLUDED_)
#define _STATFUNCTREECTRL_H__98298C61_C696_4E36_97AC_774D7D05AB95__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>
#include "PopupTreeDlg.h"

///////////////////////////////////////////////////////////////////////////////
// Indizies in Imagelist (IDB_STATFUNCS)
#define IMG_FOLDER		1
#define IMG_OPENFOLDER	2
#define IMG_STATFUNC	3

///////////////////////////////////////////////////////////////////////////////
// TreeControl, welches Objekteigenschaften anzeigt
class CStatFuncTreeCtrl :
	public CWindowImpl<CStatFuncTreeCtrl, CTreeViewCtrl>
{
public:
	typedef map<os_string, HTREEITEM, less<os_string> > CItemMap;

	CStatFuncTreeCtrl() :
		m_fHasSelectedItem(false)
	{
	}
	~CStatFuncTreeCtrl() {}

// Initialisierung
	BOOL Init(LPCSTR pcToSelect);

	int CountSelectedItems (HTREEITEM hItem = TVI_ROOT, int iCnt = 0);
	HRESULT GetSelectedStatFunc (CString &rStrSelected, CString *pStrFull);
	HRESULT GetStatFuncName(HTREEITEM hItem, CString &rStrSelected, CString *pStrFull);
	HRESULT GetSelectObject (IUnknown **ppIUnk);
	static HRESULT GetStatFunc (LPCSTR pcStatFunc, IGenericStatistics **ppIStatFunc);

// MessageHandling
	BEGIN_MSG_MAP_EX(CStatFuncTreeCtrl)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		REFLECTED_NOTIFY_HANDLER_EX(IDC_POPUPTREE, TVN_ITEMEXPANDED, OnItemExpanded)
		REFLECTED_NOTIFY_HANDLER_EX(IDC_POPUPTREE, TVN_SELCHANGED, OnSelChanged)
		REFLECTED_NOTIFY_HANDLER_EX(IDC_POPUPTREE, TVN_DELETEITEM, OnItemDeleted)
	END_MSG_MAP()

	LRESULT OnItemExpanded (NMHDR *pNmHdr);
	LRESULT OnSelChanged (NMHDR *pNmHdr);
	LRESULT OnItemDeleted (NMHDR *pNmHdr);
	void OnKillFocus (HWND hWnd);
	void OnLButtonDown (UINT uiFlags, CPoint ptPos);
	void OnLButtonUp (UINT uiFlags, CPoint ptPos);

protected:
	HTREEITEM CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup);
	HTREEITEM CalcParentItem (CItemMap &rItems, LPCSTR pcGroup);

	void AdjustParentImage (HTREEITEM hItem)
	{
		if (ItemHasChildren (hItem)) {
		// nur Parents behandeln
			if (GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
				SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
			else
				SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
		}
	}

// globaler (gecachter) enumerator für GUID's der Statistischen Kenngrößen
	class CEnumGuids
		: public NEnumGUID
	{
	public:
		CEnumGuids() : m_fIsInitialized(false) {}
		~CEnumGuids() {}

		HRESULT InitGuids (REFGUID rGuid, bool fForce = false);
		bool IsValid() { return m_fIsInitialized; }

		void RemoveActiveItem()
		{
		iterator itprev = m_itcur;

			--itprev;
			m_data.erase(itprev);		// aktuelles Item nicht mehr enumerieren
		}
		
	private:
		bool m_fIsInitialized;
	};
	static CEnumGuids s_StatValueGUIDs;

private:
	bool m_fHasSelectedItem;
};

#endif // !defined(_STATFUNCTREECTRL_H__98298C61_C696_4E36_97AC_774D7D05AB95__INCLUDED_)
