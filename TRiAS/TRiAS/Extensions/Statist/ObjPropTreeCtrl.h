// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.01.2001 10:49:44 
//
// @doc
// @module ObjPropTreeCtrl.h | Declaration of the <c CObjPropTreeCtrl> class

#if !defined(_OBJPROPTREECTRL_H__19B5C9DB_5DCA_4961_BB13_4D16823B87CE__INCLUDED_)
#define _OBJPROPTREECTRL_H__19B5C9DB_5DCA_4961_BB13_4D16823B87CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>
#include "PopupTreeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// special support for CheckBox's in TreeCtrl's
#define TV_CHECK_NOMARK		(INDEXTOSTATEIMAGEMASK(0))
#define TV_CHECK_OFF		(INDEXTOSTATEIMAGEMASK(1))
#define TV_CHECK_ON			(INDEXTOSTATEIMAGEMASK(2))
#define TV_CHECK_PASSIVE	(INDEXTOSTATEIMAGEMASK(3))
#define TV_CHECK_PARTIAL_ON	(INDEXTOSTATEIMAGEMASK(4))

///////////////////////////////////////////////////////////////////////////////
// Indizies in Imagelist (IDB_OBJPROPTYPES)
#define IMG_FOLDER		1
#define IMG_OPENFOLDER	2
#define IMG_TEXTPROP	3
#define IMG_BOOLPROP	4
#define IMG_DATUMPROP	8
#define IMG_INTEGERPROP	9
#define IMG_UNKNOWNPROP	10
#define IMG_DOUBLEPROP	11

///////////////////////////////////////////////////////////////////////////////
// StandardFunktion für Einfügen eines Items in Baum (alles außer Interaktiv)
typedef bool(*INCLUDEOBJPROP)(DWORD);

inline bool IncludeObjProp (DWORD dwFlags)
{
	return !(dwFlags & (PROPCAPS_INTERACTIVE|PROPCAPS_INTERACTIVE_INIT));
}
inline bool IncludeWritable (DWORD dwFlags)
{
	return IncludeObjProp(dwFlags) && (dwFlags & PROPCAPS_NOTREADONLY);
}
inline bool IncludeAll (DWORD dwFlags)
{
	return true;		// _alle_ eischließen
}

///////////////////////////////////////////////////////////////////////////////
// TreeControl, welches Objekteigenschaften anzeigt
class CObjPropTreeCtrl :
	public CWindowImpl<CObjPropTreeCtrl, CTreeViewCtrl>
{
public:
	typedef map<os_string, HTREEITEM, less<os_string> > CItemMap;

	CObjPropTreeCtrl(INCLUDEOBJPROP pFcn = IncludeAll, bool fUseCheckMarks = true, bool fUsePartialCheckMarks = false) :
		m_pFcn(pFcn), m_fHasSelectedItem(false)
	{
#if defined(_USE_CHECKMARK_OBJPROPTREE)
		m_fUseCheckMarks = fUseCheckMarks;
		m_fUsePartialCheckMarks = fUsePartialCheckMarks;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
	}
	~CObjPropTreeCtrl() {}

// Initialisierung
	BOOL Init(IObjectProps *pIProps, LPCSTR pcToSelect)
	{
	list<os_string> listStr;

		ATLTRY(listStr.push_back(pcToSelect));
		return Init (pIProps, listStr);
	}
	BOOL Init(IObjectProps *pIProps, list<os_string> &rStrs);

#if defined(_USE_CHECKMARK_OBJPROPTREE)
// CheckStuff
	void SetCheckStateEx (HTREEITEM hItem, UINT uiState, bool fPropagateUp = true, bool fPropagateDown = true);
	int GetCheckState(HTREEITEM hItem) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return GetItemState(hItem, TVIS_STATEIMAGEMASK);
	}
	void HideStateImage(HTREEITEM hItem)
	{
		SetCheckState(hItem, TV_CHECK_NOMARK);
	}
	bool ToggleCheckMark (HTREEITEM hItem);

// Resultate abfragen
	HRESULT GetSelectedObjProps (list<os_string> &rlstObjProps, HTREEITEM hItem = TVI_ROOT);
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	int CountSelectedItems (HTREEITEM hItem = TVI_ROOT, int iCnt = 0);
	HRESULT GetSelectedObjProp (CString &rStrSelected, CString *pStrFull);
	HRESULT GetObjPropName(HTREEITEM hItem, CString &rStrSelected, CString *pStrFull);
	HRESULT GetSelectObject (IUnknown **ppIUnk);
	static HRESULT GetObjectProp (LPCSTR pcObjProp, IObjectProps *pIProps, IObjectProperty **ppIObjProp);

// MessageHandling
	BEGIN_MSG_MAP_EX(CObjPropTreeCtrl)
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

#if defined(_USE_CHECKMARK_OBJPROPTREE)
	bool UseCheckMarks() { return m_fUseCheckMarks; }
	bool UsePartialCheckMarks() { return m_fUsePartialCheckMarks; }
	UINT CalcParentCheckState (HTREEITEM hItem);
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	void SetCheckState (HTREEITEM hItem, UINT uiState)
	{
		SetItemState(hItem, uiState, TVIS_STATEIMAGEMASK);
	}

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

private:
	INCLUDEOBJPROP m_pFcn;
	bool m_fHasSelectedItem;

#if defined(_USE_CHECKMARK_OBJPROPTREE)
	bool m_fUseCheckMarks;
	bool m_fUsePartialCheckMarks;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
};

#endif // !defined(_OBJPROPTREECTRL_H__19B5C9DB_5DCA_4961_BB13_4D16823B87CE__INCLUDED_)
