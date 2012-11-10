// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 26.07.2000 12:38:29 
//
// @doc
// @module AtlCtrl_Tree.h | Declaration of the <c TTreeCtrl> class

#if !defined(_ATLCTRL_TREE_H__CBDB899A_4E4D_4B69_A37F_8533958BE7A2__INCLUDED_)
#define _ATLCTRL_TREE_H__CBDB899A_4E4D_4B69_A37F_8533958BE7A2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include <commctrl.h>

///////////////////////////////////////////////////////////////////////////////
// Repräsentiert ein Item in einem Baum
template <class T, class S>
class TTreeCursor 
{
private:
	HTREEITEM	m_hTreeItem;
	T			*m_pTree;

// Implementation
protected:
	TTreeCursor <T, S> _Insert(LPCTSTR strItem, HTREEITEM hAfter, int nImageIndex) 
	{
		TV_INSERTSTRUCT ins;
		ins.hParent = m_hTreeItem;
		ins.hInsertAfter = hAfter;
		ins.item.mask = TVIF_TEXT;
		ins.item.pszText = (LPTSTR) strItem;
		if (nImageIndex != -1)
		{
			ins.item.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			ins.item.iImage = nImageIndex;
			ins.item.iSelectedImage = nImageIndex;
		}
		return TTreeCursor <T, S>(m_pTree, m_pTree->InsertItem(&ins));
	}

// Operation
public:
	TTreeCursor(T *pTree = NULL, HTREEITEM hTreeItem = NULL)
		: m_pTree(pTree), m_hTreeItem(hTreeItem) {}
	TTreeCursor(const TTreeCursor& posSrc) 
	{
		*this = posSrc;
	}
	~TTreeCursor() 
	{
	}

	const TTreeCursor& operator=(const TTreeCursor& posSrc) 
	{
		if (&posSrc != this)
		{
			m_hTreeItem = posSrc.m_hTreeItem;
			m_pTree = posSrc.m_pTree;
		}
		return *this;
	}
	operator HTREEITEM() 
	{
		return m_hTreeItem; 
	}
	TTreeCursor InsertAfter(LPCTSTR strItem, HTREEITEM hAfter, int nImageIndex = -1) 
	{
		return _Insert(strItem, nImageIndex, hAfter); 
	}
	TTreeCursor AddHead(LPCTSTR strItem, int nImageIndex = -1) 
	{
		return _Insert(strItem, nImageIndex, TVI_FIRST);
	}
	TTreeCursor AddTail(LPCTSTR strItem, int nImageIndex = -1) 
	{
		return _Insert(strItem, nImageIndex, TVI_LAST);
	}
	int GetImageID() 
	{
		TV_ITEM item;
		item.mask = TVIF_HANDLE | TVIF_IMAGE;
		item.hItem = m_hTreeItem;
		m_pTree->GetItem(item);
		return item.iImage;
	}
	BOOL GetRect(LPRECT lpRect, BOOL bTextOnly) 
	{
		return m_pTree->GetItemRect(m_hTreeItem, lpRect, bTextOnly);
	}
	TTreeCursor GetNext(UINT nCode) 
	{
		return m_pTree->GetNextItem(m_hTreeItem, nCode); 
	}
	TTreeCursor GetChildItem() 
	{
		return m_pTree->GetChildItem(m_hTreeItem); 
	}
	TTreeCursor GetNextSibling() 
	{
		return m_pTree->GetNextSiblingItem(m_hTreeItem);
	}
	TTreeCursor GetPrevSibling() 
	{
		return m_pTree->GetPrevSiblingItem(m_hTreeItem);
	}
	TTreeCursor GetParent() 
	{
		return m_pTree->GetParentItem(m_hTreeItem);
	}
	TTreeCursor GetFirstVisible() 
	{
		return m_pTree->GetFirstVisibleItem();
	}
	TTreeCursor GetNextVisible() 
	{
		return m_pTree->GetNextVisibleItem(m_hTreeItem);
	}
	TTreeCursor GetPrevVisible() 
	{
		return m_pTree->GetPrevVisibleItem(m_hTreeItem); 
	}
	TTreeCursor GetSelected() 
	{
		return m_pTree->GetSelectedItem(); 
	}
	TTreeCursor GetDropHilight() 
	{
		return m_pTree->GetDropHilightItem();
	}
	TTreeCursor GetRoot() 
	{
		return m_pTree->GetRootItem();
	}
	TTreeCursor FindItem(const S& strItemName) 
	{
		return m_pTree->FindItem(m_hTreeItem, strItemName);
	}
	S GetText() 
	{
		return m_pTree->GetItemText(m_hTreeItem);
	}
	TTreeCursor InsertItem(LPCTSTR strItem, HTREEITEM hInsertAfter = TVI_LAST, int nImageIndex = -1) 
	{
		return _Insert(strItem, hInsertAfter, nImageIndex);
	}
	BOOL GetImage(int& nImage, int& nSelectedImage) 
	{
		return m_pTree->GetItemImage(m_hTreeItem, nImage, nSelectedImage);
	}
	UINT GetState(UINT nStateMask) 
	{
		return m_pTree->GetItemState(m_hTreeItem, nStateMask); 
	}
	DWORD GetData() 
	{
		return m_pTree->GetItemData(m_hTreeItem);
	}
	BOOL SetData(DWORD dwData) 
	{
		return m_pTree->SetItemData(m_hTreeItem, dwData);
	}
//	BOOL Set(UINT nMask, LPCTSTR lpszItem, int nImage, 
//		int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam) {
//	}
	BOOL SetText(LPCTSTR lpszItem) 
	{
		return m_pTree->SetItemText(m_hTreeItem, lpszItem);
	}
	BOOL SetImage(int nImage, int nSelectedImage) 
	{
		return m_pTree->SetItemImage(m_hTreeItem, nImage, nSelectedImage);
	}
	BOOL SetState(UINT nState, UINT nStateMask) 
	{
		return m_pTree->SetItemState(m_hTreeItem, nState, nStateMask);
	}
//	BOOL SetData(DWORD dwData) {
//		return m_pTree->SetItemData(m_hTreeItem,dwData);
//	}
	BOOL HasChild() 
	{
		return m_pTree->ItemHasChildren(m_hTreeItem);
	}
// Operations
	BOOL Delete() 
	{
		return m_pTree->DeleteItem(m_hTreeItem);
	}
	BOOL Expand(UINT nCode = TVE_EXPAND) 
	{
		return m_pTree->Expand(m_hTreeItem, nCode);
	}
	BOOL Select(UINT nCode = TVGN_CARET) 
	{
		return m_pTree->Select(m_hTreeItem, nCode);
	}
	BOOL SelectItem() 
	{
		return m_pTree->SelectItem(m_hTreeItem);
	}
	TTreeCursor SelectDropTarget() 
	{
		return m_pTree->SelectDropTarget(m_hTreeItem);
	}
	TTreeCursor SelectSetFirstVisible() 
	{
		return m_pTree->SelectSetFirstVisible(m_hTreeItem);
	}
//	CEdiT *EditLabel() {
//		return m_pTree->EditLabel(m_hTreeItem);
//	}
//	CImageLisT *CreateDragImage() {
//		return m_pTree->CreateDragImage(m_hTreeItem);
//	}
	BOOL SortChildren() 
	{
		return m_pTree->SortChildren(m_hTreeItem);
	}
	BOOL EnsureVisible() 
	{
		return m_pTree->EnsureVisible(m_hTreeItem);
	}
};


/////////////////////////////////////////////////////////////////////////////
// TTreeCtrl: Wrapper für SysTreeControl
template <class T, class S>
class TTreeCtrl 
{
public:
	TTreeCtrl() {}
	~TTreeCtrl() {}
	HIMAGELIST SetImageList(HIMAGELIST hImageList, int nImageListType = TVSIL_NORMAL) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_SetImageList(pT->m_hWnd, hImageList, nImageListType);
	}
	HIMAGELIST GetImageList(int nImageListType = TVSIL_NORMAL) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_GetImageList(pT->m_hWnd, nImageListType);
	}
	BOOL DeleteAllItems() 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_DeleteAllItems(pT->m_hWnd);
	}
	BOOL SetItemText(HTREEITEM hItem, LPCTSTR lpszText) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_TEXT;
		is.hItem = hItem;
		is.pszText = lpszText;
		return TreeView_SetItem(pT->m_hWnd, &is);
	}
	S GetItemText(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TCHAR	sz[_MAX_PATH];
		TV_ITEM	is;
		is.mask = TVIF_TEXT;
		is.hItem = hItem;
		is.pszText = sz;
		is.cchTextMax = sizeof(sz)/sizeof(sz[0]);
		if (TreeView_GetItem(pT->m_hWnd, &is))
		{
			return S(sz);
		}
		 else 
		{
			return S(_T(""));
		}
	}
	BOOL GetItemImage(HTREEITEM hItem, int& nImage, int& nSelectedImage) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		is.hItem = hItem;
		if (!TreeView_GetItem(pT->m_hWnd, &is))
			return FALSE;
		nImage = is.iImage;
		nSelectedImage = is.iSelectedImage;
		return TRUE;
	}
	BOOL SetItemImage(HTREEITEM hItem, int nImage, int nSelectedImage) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		is.hItem = hItem;
		is.iImage = nImage;
		is.iSelectedImage = nSelectedImage;
		return TreeView_SetItem(pT->m_hWnd, &is);
	}
	BOOL SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_STATE;
		is.hItem = hItem;
		is.state = nState;
		is.stateMask = nStateMask;
		return TreeView_SetItem(pT->m_hWnd, &is);
	}
	UINT GetItemState(HTREEITEM hItem, UINT nStateMask) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_STATE;
		is.hItem = hItem;
		is.stateMask = nStateMask;
		TreeView_GetItem(pT->m_hWnd, &is);
		return is.state;
	}
	BOOL SetItemData(HTREEITEM hItem, DWORD dwData) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_PARAM;
		is.hItem = hItem;
		is.lParam = dwData;
		return TreeView_SetItem(pT->m_hWnd, &is);
	}
	DWORD GetItemData(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		TV_ITEM	is;
		is.mask = TVIF_PARAM;
		is.hItem = hItem;
		TreeView_GetItem(pT->m_hWnd, &is);
		return is.lParam;
	}
	BOOL GetItem(TV_ITEM& item) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_GetItem(pT->m_hWnd, &item);
	}
	BOOL GetItemRect(HTREEITEM hItem, LPRECT r, BOOL bTextOnly) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_GetItemRect(pT->m_hWnd, hItem, r, bTextOnly);
	}
	BOOL ItemHasChildren(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_GetChild(pT->m_hWnd, hItem) ? TRUE : FALSE;
	}
	BOOL DeleteItem(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_DeleteItem(pT->m_hWnd, hItem);
	}
	BOOL Expand(HTREEITEM hItem, UINT nCode) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_Expand(pT->m_hWnd, hItem, nCode);
	}
	BOOL SortChildren(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_SortChildren(pT->m_hWnd, hItem, 0);
	}
	BOOL EnsureVisible(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_EnsureVisible(pT->m_hWnd, hItem);
	}
	TTreeCursor <T, S> InsertItem(LPCTSTR lpszItemName, HTREEITEM hParent = NULL, HTREEITEM hAfter = TVI_LAST, int nImage = -1) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, hParent).InsertItem(lpszItemName, hAfter, nImage);
	}
	TTreeCursor <T, S> InsertItem(LPTV_INSERTSTRUCT lpInsertStruct) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, TreeView_InsertItem(pT->m_hWnd, lpInsertStruct));
	}
	TTreeCursor <T, S> GetRootItem() 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, TreeView_GetRoot(pT->m_hWnd));
	}
	TTreeCursor <T, S> GetChildItem(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, TreeView_GetChild(pT->m_hWnd, hItem));
	}
	TTreeCursor <T, S> GetNextItem(HTREEITEM hItem, UINT nCode) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, TreeView_GetNextItem(pT->m_hWnd, hItem, nCode));
	}
	TTreeCursor <T, S> GetItem(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, hItem);
	}
	TTreeCursor <T, S> FindItem(HTREEITEM hItem, const S& strItemName) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		HTREEITEM	hSrch = hItem;
		S			strFound;
		if (hSrch)
		{
			do 
			{
				strFound = GetItemText(hSrch);
				if (0 == TextCompare <S, S>(strFound, strItemName))
					return TTreeCursor <T, S>(pT, hSrch);
				for (hSrch = TreeView_GetChild(pT->m_hWnd, hItem); hSrch; hSrch = TreeView_GetNextSibling(pT->m_hWnd, hSrch))
				{
					TTreeCursor <T, S> bmk = FindItem(hSrch, strItemName);
					if (!!bmk)
						return bmk;
				}
			} while (hSrch);
		}
/*
		for (hSrch = TreeView_GetChild(pT->m_hWnd, hItem); hSrch; hSrch = TreeView_GetNextSibling(pT->m_hWnd, hSrch))
		{
			strFound = TTreeCursor <T, S>(pT, hSrch).GetText();
			if (0 == TextCompare <S, S>(strFound, strItemName))
				return TTreeCursor <T, S>(pT, hSrch);
		}
		for (hSrch = TreeView_GetChild(pT->m_hWnd, hItem); hSrch; hSrch = TreeView_GetNextSibling(pT->m_hWnd, hSrch))
		{
			strFound = TTreeCursor <T, S>(pT, hSrch).GetText();
			if (0 == TextCompare <S, S>(strFound, strItemName))
				return TTreeCursor <T, S>(pT, hSrch);
			TTreeCursor <T, S> bmk = FindItem(hSrch, strItemName);
			if (!!bmk)
				return bmk;
		}
*/		return TTreeCursor <T, S>();
	}
	TTreeCursor <T, S> GetSelectedItem() 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, (HTREEITEM)::SendMessage(pT->m_hWnd, TVM_GETNEXTITEM, TVGN_CARET, 0));
	}
	TTreeCursor <T, S> GetNextSiblingItem(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TTreeCursor <T, S>(pT, (HTREEITEM)::SendMessage(pT->m_hWnd, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem));
	}
	BOOL Select(HTREEITEM hItem, UINT nCode = TVGN_CARET) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_Select(pT->m_hWnd, hItem, nCode);
	}
	BOOL SelectItem(HTREEITEM hItem) 
	{
		T *pT = static_cast <T *>(this);
		_ASSERTE(::IsWindow(pT->m_hWnd));
		return TreeView_SelectItem(pT->m_hWnd, hItem);
	}

	TTreeCursor GetPrevSiblingItem(HTREEITEM hItem);
	TTreeCursor GetParentItem(HTREEITEM hItem);
	TTreeCursor GetFirstVisibleItem();
	TTreeCursor GetNextVisibleItem(HTREEITEM hItem);
	TTreeCursor GetPrevVisibleItem(HTREEITEM hItem);
	TTreeCursor GetDropHilightItem();
	TTreeCursor InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
		int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, 
		HTREEITEM hParent, HTREEITEM hInsertAfter);
	TTreeCursor InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	TTreeCursor SelectDropTarget(HTREEITEM hItem);
	TTreeCursor SelectSetFirstVisible(HTREEITEM hItem);
	TTreeCursor HitTest(LPPOINT pt, UINT *pFlags = NULL);
	TTreeCursor HitTest(TV_HITTESTINFO* pHitTestInfo);
};

/////////////////////////////////////////////////////////////////////////
// TreeControl für ATL
#if defined(__ATLWIN_H__)

class CAtlTreeCtrl :
	public CContainedWindow,
	public TTreeCtrl <CAtlTreeCtrl, CComBSTR>
{
public:
	CAtlTreeCtrl(LPTSTR lpszClassName, CMessageMap* pObject, DWORD dwMsgMapID = 0) :
		CContainedWindow(lpszClassName, pObject, dwMsgMapID)
	{ 
	}
};
typedef TTreeCursor <CAtlTreeCtrl, CComBSTR> CAtlTreeCursor;

///////////////////////////////////////////////////////////////////////////////
// 
template <class S1, class S2> int TextCompare(const S1& s1, const S2& s2);
template <>
inline int TextCompare(const CComBSTR& str1, const CComBSTR& str2) 
{
	return wcscmp(str1, str2);
}
#endif

#endif // !defined(_ATLCTRL_TREE_H__CBDB899A_4E4D_4B69_A37F_8533958BE7A2__INCLUDED_)
