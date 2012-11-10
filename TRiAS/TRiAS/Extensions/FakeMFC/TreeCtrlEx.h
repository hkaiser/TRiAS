///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TreeCtrlEx.h | Description goes here

#if !defined(_TREECTRLEX_H__0E04E1C3_B2CB_11D1_85AA_00600875138A__INCLUDED_)
#define _TREECTRLEX_H__0E04E1C3_B2CB_11D1_85AA_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <secdll.h>
#include <slstctip.h>
#include <trctlx.h>
#endif // !defined(_SEC_VER) || _SEC_VER < 0x0600

/////////////////////////////////////////////////////////////////////////////
// CSECTreeCtrlEx window

class CSECTreeCtrlEx : 
	public SECTreeCtrl
{
// Construction
public:
	CSECTreeCtrlEx();

	int InsertItem(const LV_ITEM* pItem)
		{ return SECListCtrl::InsertItem (pItem); }
	HTREEITEM InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST)
		{ return SECTreeCtrl::InsertItem(lpszItem, nImage, nSelectedImage, hParent, hInsertAfter); }
	HTREEITEM InsertItem (LPTV_INSERTSTRUCT lpInsertStruct)
		{ return SECTreeCtrl::InsertItem (lpInsertStruct); }
	BOOL SetListItemState (HTREEITEM hItem, UINT nState, UINT nMask)
		{ return SECListCtrl::SetItemState (GetItemIndex(hItem), nState, nMask); }

// Attributes
public:

// Operations
public:
	void FitColumn (int iCol = -1);
	int InsertColumn(int nCol, UINT uiColHead,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	int GetItemIndex (HTREEITEM hItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSECTreeCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSECTreeCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSECTreeCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#if !defined(MINCOLWIDTH)
#define MINCOLWIDTH		10
#endif // MINCOLWIDTH

#endif // !defined(_TREECTRLEX_H__0E04E1C3_B2CB_11D1_85AA_00600875138A__INCLUDED_)
