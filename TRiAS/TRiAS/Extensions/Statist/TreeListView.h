// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 05.09.2001 14:26:20 
//
// @doc
// @module TreeListView.h | Declaration of the <c CTreeListView> class

#if !defined(_TREELISTVIEW_H__8C3AED92_F46B_4032_B124_6A4C9F94F75F__INCLUDED_)
#define _TREELISTVIEW_H__8C3AED92_F46B_4032_B124_6A4C9F94F75F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListView - A TreeView with additional columns
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2001-2002 Bjarke Viksoe.
//
// Partly implemented from a MFC CTreeListView control by Gerolf Kühnel
// available at www.codeproject.com.
// Horizontal scrolling supplied by Oleg Reabciuc (olegr@compudava.com).
// Nail Kaipov fixed the horizontal scrollbar code (roof@crypt.nsk.ru).
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#ifndef __cplusplus
  #error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLAPP_H__
  #error TreeListView.h requires atlapp.h to be included first
#endif

#ifndef __ATLCTRLS_H__
  #error TreeListView.h requires atlctrls.h to be included first
#endif

#if (_WIN32_IE < 0x0400)
  #error TreeListView.h requires _WIN32_IE >= 0x0400
#endif

#ifndef TVS_NOHSCROLL
#define TVS_NOHSCROLL 0x8000
#endif // TVS_NOHSCROLL

typedef struct tagTLVITEM {
	UINT	 mask;
	int 	 iSubItem;
	UINT	 state;
	UINT	 stateMask;
	UINT	 format;
	LPTSTR	 pszText;
	UINT	 cchTextMax;
	int 	 iImage;
	COLORREF clrText;
	COLORREF clrBack;
	LPARAM	 lParam;
} TLVITEM, *LPTLVITEM;

// mask flags
#define TLVIF_TEXT				 0x0001
#define TLVIF_IMAGE 			 0x0002
#define TLVIF_PARAM 			 0x0004
#define TLVIF_STATE 			 0x0008
#define TLVIF_FORMAT			 0x0010
#define TLVIF_TEXTCOLOR 		 0x0020

// format flags
#define TLVIFMT_LEFT			 0x00000000
#define TLVIFMT_CENTER			 0x00000001
#define TLVIFMT_RIGHT			 0x00000002

// state flags
#define TLVIS_NORMAL			 0x0000
#define TLVIS_BOLD				 0x0001
#define TLVIS_ITALIC			 0x0002
#define TLVIS_UNDERLINE 		 0x0004
#define TLVIS_STRIKEOUT 		 0x0008

///////////////////////////////////////////////////////////////////////////////
// 
#define TVMX_GETSUBITEM			 (WM_USER+1233)
#define TVMX_SETSUBITEM			 (WM_USER+1234)

///////////////////////////////////////////////////////////////////////////////
// dummy TreeBase with dummy required methods
template<class TBase = CWindow>
class CDummyTreeCtrlBase :
	public CTreeViewCtrlT<TBase>
{
public:
	CDummyTreeCtrlBase(HWND hWnd = NULL) : CTreeViewCtrlT<TBase>(hWnd) {}
	~CDummyTreeCtrlBase() {}

	void ExpandItem(HTREEITEM hItem) {}			// after expanded
	void PreExpandItem(HTREEITEM hItem) {}		// before expanding
	void DeletingItem(HTREEITEM hItem) {}		// after deleting item
	LRESULT OnEraseBkGnd(HDC hDC)
	{
		return FALSE;
	}
};

///////////////////////////////////////////////////////////////////////////////
// CTreeListViewImpl
template <class T, class TTreeBase = CDummyTreeCtrlBase<CWindow>, class TBase = CWindow, 
	class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CTreeListViewImpl : 
	public CWindowImpl<T, TBase, TWinTraits>,
	public CCustomDraw<T>
{
public:
	CContainedWindowT<TTreeBase> m_ctrlTree;
	CContainedWindowT<CHeaderCtrl> m_ctrlHeader;

	typedef CSimpleArray<TLVITEM *> tMapItem;
	CSimpleMap<HTREEITEM, tMapItem *> m_mapItems;
	CSimpleArray<RECT> m_rcColumns;

	CFont m_fontHeader;
	COLORREF m_clrBack;
	COLORREF m_clrText;
	CBrush m_brBack;
	bool m_fShowHeader;
	LONG m_cxHeader;
	LONG m_nOffset;

	UINT m_iItemState;
	RECT m_rcItem;

	DWORD m_dwHdrStyle;

//	CToolTipCtrl m_tip;
	long m_lDividerX;
	long m_lDividerOffset;
	long m_lDividerMin;

	CTreeListViewImpl(DWORD dwHdrStyle = WS_CHILD|WS_VISIBLE|HDS_BUTTONS|HDS_HORZ|HDS_DRAGDROP) :
		m_fShowHeader(dwHdrStyle & WS_VISIBLE ? true : false), m_dwHdrStyle(dwHdrStyle),
		m_lDividerX(0), m_lDividerOffset(0), m_lDividerMin(0), m_nOffset(0)
	{ 
	}
	
	// Message map and handlers
	
	BEGIN_MSG_MAP(CTreeListViewImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
		CHAIN_MSG_MAP(CCustomDraw< T >)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_SETTINGCHANGE, OnSettingChange)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
		NOTIFY_CODE_HANDLER(TVN_DELETEITEMA, OnTreeItemDelete)
		NOTIFY_CODE_HANDLER(TVN_DELETEITEMW, OnTreeItemDelete)
		NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDEDA, OnTreeItemExpanded)
		NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDEDW, OnTreeItemExpanded)
		NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDINGA, OnTreeItemExpanding)
		NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDINGW, OnTreeItemExpanding)
		NOTIFY_CODE_HANDLER(HDN_ITEMCHANGEDA, OnHeaderItemChanged)
		NOTIFY_CODE_HANDLER(HDN_ITEMCHANGEDW, OnHeaderItemChanged)
		NOTIFY_CODE_HANDLER(NM_RELEASEDCAPTURE, OnHeaderItemChanged)
		NOTIFY_CODE_HANDLER(HDN_BEGINDRAG, OnHeaderBeginDrag)
		NOTIFY_CODE_HANDLER(HDN_ENDDRAG, OnHeaderEndDrag)
		NOTIFY_CODE_HANDLER(HDN_BEGINTRACKA, OnHeaderBeginTrack)
		NOTIFY_CODE_HANDLER(HDN_TRACKA, OnHeaderTrack)
		NOTIFY_CODE_HANDLER(HDN_ENDTRACKA, OnHeaderEndTrack)
		NOTIFY_CODE_HANDLER(HDN_BEGINTRACKW, OnHeaderBeginTrack)
		NOTIFY_CODE_HANDLER(HDN_TRACKW, OnHeaderTrack)
		NOTIFY_CODE_HANDLER(HDN_ENDTRACKW, OnHeaderEndTrack)
//		NOTIFY_CODE_HANDLER(TTN_GETDISPINFO, OnToolTipDispInfo);
		FORWARD_NOTIFICATIONS()
	ALT_MSG_MAP(1) // Tree
		MESSAGE_HANDLER(WM_NCDESTROY, OnTreeNcDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnTreeFixButtonHit)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnTreeFixButtonHit)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnTreeEraseBkGnd)
		MESSAGE_HANDLER(TVM_INSERTITEM, OnTreeItemInsert)
		MESSAGE_HANDLER(TVM_SETBKCOLOR, OnTreeSetColor)
		MESSAGE_HANDLER(TVM_SETTEXTCOLOR, OnTreeSetColor)
		MESSAGE_HANDLER(TVM_SETITEM, OnTreeSetItem)
		MESSAGE_HANDLER(TVMX_GETSUBITEM, OnTreeGetSubItem)
		MESSAGE_HANDLER(TVMX_SETSUBITEM, OnTreeSetSubItem)
		MESSAGE_HANDLER(TVM_GETITEMRECT, OnTreeGetItemRect)
	ALT_MSG_MAP(2) // Header
		MESSAGE_HANDLER(HDM_INSERTITEM, OnHeaderItemInsert)
		MESSAGE_HANDLER(HDM_DELETEITEM, OnHeaderItemDelete)
	END_MSG_MAP()
		
// Operations
	BOOL SubclassWindow(HWND hWnd)
	{
		ATLASSERT(m_hWnd == NULL);
		ATLASSERT(::IsWindow(hWnd));
		BOOL bRet = CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(hWnd);
		if (bRet)
			_Init();
		return bRet;
	}
	
	// Implementation
	
	void _Init()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		
#if defined(_DEBUG)
	// Check class
		TCHAR szBuffer[16];
		if (::GetClassName(m_hWnd, szBuffer, sizeof(szBuffer)/sizeof(TCHAR)))
		{
			ATLASSERT(::lstrcmpi(szBuffer, CTreeViewCtrl::GetWndClassName()) == 0);
			ATLASSERT(GetStyle() & WS_CHILD);
		}
#endif // defined(_DEBUG)

	// Create the tree control
	// Thanks to Nicola Tufarelli for suggesting using the GetDlgCtrlID() to
	// preserve the original control ID...
		m_ctrlTree.Create(this, 1, m_hWnd, &rcDefault, NULL, GetStyle(), 0, GetDlgCtrlID());
		ATLASSERT(m_ctrlTree.IsWindow());
		m_ctrlTree.ModifyStyle(0, TVS_NOHSCROLL | TVS_SHOWSELALWAYS);  // we need this
		
	// Create the header control
		m_ctrlHeader.Create(this, 2, m_hWnd, &rcDefault, NULL, m_dwHdrStyle);
		ATLASSERT(m_ctrlHeader.IsWindow());
		
		SendMessage(WM_SETTINGCHANGE);

//		m_tip.Create(m_ctrlTree, rcDefault, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP);
//		m_tip.Activate(TRUE);

	T* pT = static_cast<T*>(this);

		pT->UpdateLayout();

	// FIX: When used in a view...
		m_ctrlTree.ShowWindow(SW_SHOW);
		m_ctrlHeader.ShowWindow(SW_SHOW);
	}
	
	LPTLVITEM _GetSubItem(HTREEITEM hItem, int iSubItem)
	{
		if (iSubItem < 0 || iSubItem > m_ctrlHeader.GetItemCount())
			return NULL;
	tMapItem *pVal = m_mapItems.Lookup(hItem);
	
		ATLASSERT(pVal);
		ATLASSERT(iSubItem < pVal->GetSize());
	
		if (pVal == NULL)
			return NULL;
		if (iSubItem >= pVal->GetSize())
			return NULL;
		return (*pVal)[iSubItem];
	}
	
	void _DeleteSubItem(const LPTLVITEM pItem)
	{
		ATLASSERT(!::IsBadReadPtr(pItem, sizeof(TLVITEM)));
		if (pItem->mask & TLVIF_TEXT)
			ATLTRY(delete[] pItem->pszText);
		ATLTRY(delete pItem);
	}
	
	void _CalcColumnSizes()
	{
	// Keep track of header sizes
		m_rcColumns.RemoveAll();
		m_cxHeader = 0;
		int cnt = m_ctrlHeader.GetItemCount();
		for (int i = 0; i < cnt; i++) {
		RECT rc;

			m_ctrlHeader.GetItemRect(i, &rc);
			m_rcColumns.Add(rc);
			m_cxHeader += rc.right - rc.left;
		}

	// FIX: Nail Kaipov fixed the horizontal scrollbar code
	// If the width of all headers is bigger than the width of the client-area 
	// of the TreeView, then the Scrollbar is to be enabled
		RECT rcClient;
		GetClientRect(&rcClient);
		if (GetStyle() & WS_VSCROLL) 
			rcClient.right += ::GetSystemMetrics(SM_CXHTHUMB);
		LONG cxClient = (rcClient.right - rcClient.left);
		if (m_cxHeader - cxClient >= 0) {
			SCROLLINFO si;
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			si.nMax  = m_cxHeader;
			si.nMin  = 0;
			si.nPage = cxClient;
			si.nPos  = GetScrollPos(SB_HORZ);   // Preserve scroller position
			SetScrollInfo(SB_HORZ, &si, TRUE);  // Setup scrollbar params
			ModifyStyle(0, WS_HSCROLL, SWP_FRAMECHANGED);
			m_nOffset = -si.nPos;    // Save scrollbar position for correct drawing
			if (si.nPos) {           // Scroll position is non-zero. code is stolen from OnHScroll()
				RECT rcHeader, rcTree;
				m_ctrlHeader.GetClientRect(&rcHeader);
				m_ctrlTree.GetClientRect(&rcTree);
				m_ctrlHeader.SetWindowPos(NULL, 
					-si.nPos, 
					0, 
					abs(si.nPos) + ::GetSystemMetrics(SM_CXVSCROLL) + 1 + rcTree.right - rcTree.left,
					rcHeader.bottom - rcHeader.top, 
					SWP_SHOWWINDOW);
			}
		}
		else {
			SetScrollPos(SB_HORZ, 0, TRUE);
			ModifyStyle(WS_HSCROLL, 0, SWP_FRAMECHANGED);
			m_nOffset = 0;
			Invalidate();
		}
	}
	
	// Message Handlers
	
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		_Init();
		return 0;
	}
	
	LRESULT OnSettingChange(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (!m_fontHeader.IsNull())
			m_fontHeader.DeleteObject();
	
	NONCLIENTMETRICS ncm = { 0 };
	
		ncm.cbSize = sizeof(ncm);
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
		m_fontHeader.CreateFontIndirect(&ncm.lfMenuFont);
		m_ctrlHeader.SetFont(m_fontHeader);
		
		m_clrText = m_ctrlTree.GetTextColor();
		if (m_clrText == -1)
			m_clrText = ::GetSysColor(COLOR_WINDOWTEXT);
		m_clrBack = m_ctrlTree.GetBkColor();
		if (m_clrBack == -1)
			m_clrBack = ::GetSysColor(COLOR_WINDOW);
		
		if (!m_brBack.IsNull())
			m_brBack.DeleteObject();
		m_brBack.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		
		Invalidate();
		return 0;
	}
	
	LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_ctrlTree.SetFocus();
		return 0;
	}
	
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
	T* pT = static_cast<T*>(this);

		pT->UpdateLayout(); 	
		return 0;
	}

	LRESULT OnEraseBkGnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 1; // Children fill entire client area
	}
	
	static long StretchWidth(long nWidth, long nMeasure)
	{
		return ((nWidth / nMeasure) + 1) * nMeasure;
	}
	LPARAM OnHScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{  
		// Thanks to Oleg Reabciuc for providing the horizontal scrolling
		// support for this control
		
		int nSBCode = (int) LOWORD(wParam);
		int nPos = (int) HIWORD(wParam);
		
		RECT rcClient;
		m_ctrlTree.GetClientRect(&rcClient);
		
		int cxClient = abs(rcClient.right - rcClient.left);   // One Page
		const int nWidthLine = 6;               // Microsoft's line-step in a CListCtrl, got from MFC - sourcecode
		int nCurPos = GetScrollPos(SB_HORZ);    // Current scrollingposition
		int nPrevPos = nCurPos;                 // Save current scrolling position for calculating
		
		int nScrollMin;                         // Minimum scrolling value
		int nScrollMax;                         // Maximum scrolling value
		GetScrollRange(SB_HORZ, &nScrollMin, &nScrollMax);
		
		// Check which kind of scoll is wanted
		switch( nSBCode ) {
		case SB_LEFT :                          // Scoll to left most position
			nCurPos = 0;
			break;
		case SB_RIGHT :                         // Scroll to right most position
			nCurPos = nScrollMax;
			break;
		case SB_LINELEFT :                      // Scroll left with the button
			nCurPos = max(nCurPos - nWidthLine, 0);
			break;
		case SB_LINERIGHT :                     // Scroll right with the button
			nCurPos = min(nCurPos + nWidthLine, nScrollMax);
			break;
		case SB_PAGELEFT :                      // Scroll left with a click to the background of the scrollbar
			nCurPos = max(nCurPos - cxClient, 0);
			break;
		case SB_PAGERIGHT :                     // Scroll left with a click to the background of the scrollbar
			nCurPos = min(nCurPos + cxClient, nScrollMax);
			break;
		case SB_THUMBPOSITION :                 // Scroll by moving the scrollbutton with the mouse
		case SB_THUMBTRACK :                    // Drop the scrollbarbutton
			// Check for illegal positions and correct them (out of the scrollbar?)
			if( nPos == 0 ) {
				nCurPos = 0;
			}
			else {
				nCurPos = min(StretchWidth(nPos, nWidthLine), nScrollMax);
			}
		}
		
		// Move the scrollbarbutton to the position (graphically)
		SetScrollPos(SB_HORZ, nCurPos, TRUE);
		m_nOffset = -nCurPos;
		
		// Smoothly Scroll the Tree control
		RECT rcTree;
		m_ctrlTree.GetClientRect(&rcTree);
		m_ctrlTree.ScrollWindowEx(nPrevPos - nCurPos, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE);
		
		RECT rcHeader;
		GetClientRect(&rcClient);
		m_ctrlHeader.GetClientRect(&rcHeader);
		
		if( rcTree.right - rcTree.left != 0 ) {
			int iVSWidth = ::GetSystemMetrics(SM_CXVSCROLL) + 1;
			m_ctrlHeader.SetWindowPos(NULL, m_nOffset, 0, abs(m_nOffset) + iVSWidth + rcTree.right - rcTree.left, rcHeader.bottom - rcHeader.top, SWP_SHOWWINDOW);
		}
		
		// Redraw the treecontrol so you can see the scrolling
		m_ctrlTree.Invalidate();
		return 0;
	}

//	LRESULT OnToolTipDispInfo(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
//	{
//	LPNMTTDISPINFO lpnmttdi = (LPNMTTDISPINFO)pnmh;
//
//		lpnmttdi->lpszText = "Test Tooltip";
//		return 0;
//	}

	LRESULT OnTreeEraseBkGnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if (!m_ctrlTree.OnEraseBkGnd((HDC)wParam))
			bHandled = FALSE;
		else
			bHandled = TRUE;
		return TRUE;
	}
	LRESULT OnTreeNcDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// Clean up memory on destruction
		m_ctrlTree.DeleteAllItems();
		bHandled = FALSE;
		return 0;
	}
	
	LRESULT OnTreeFixButtonHit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
	// If a click is to the right of the label then we're still clicking on the item...
	// Handling TVM_HITTEST would be a lot nicer, but the TreeView control doesn't 
	// actually use it internally :-(
	TVHITTESTINFO hti;
	RECT rcClient;

		GetClientRect(&rcClient);
		hti.pt.x = GET_X_LPARAM(lParam) - m_nOffset;
		hti.pt.y = GET_Y_LPARAM(lParam);
		if (hti.pt.x > rcClient.right - rcClient.left) 
			hti.pt.x = rcClient.right - 40;

		m_ctrlTree.HitTest(&hti);
		if (hti.flags == TVHT_ONITEMRIGHT)
		{
			RECT rc;
			m_ctrlTree.GetItemRect(hti.hItem, &rc, TRUE);
			hti.pt.x = rc.left;
		}
		lParam = MAKELONG(hti.pt.x, hti.pt.y);
		return m_ctrlTree.DefWindowProc(uMsg, wParam, lParam);
	}
	
	LRESULT OnTreeItemInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
	HTREEITEM hItem = (HTREEITEM)m_ctrlTree.DefWindowProc(uMsg, wParam, lParam);
	
		if (hItem == NULL)
			return (LRESULT)hItem;
		
	// Create a new item
	tMapItem *pVal;

		ATLTRY(pVal = new tMapItem);
		ATLASSERT(pVal);
		if (NULL == pVal)
			return (LRESULT)NULL;

	LPTLVITEM pItem;
	int cnt = m_ctrlHeader.GetItemCount();

		for (int i = 0; i < cnt; i++)
		{
			ATLTRY(pItem = new TLVITEM);
			ATLASSERT(pItem);
			if (NULL != pItem) {
				::ZeroMemory(pItem, sizeof(TLVITEM));
				pVal->Add(pItem);
			}
			else {
				return (LRESULT)NULL;
			}
		}

	// Add the new item
		m_mapItems.Add(hItem, pVal);

	// Then add the item structure...
		if (cnt > 0) {
		// Convert TVITEM into a TLVITEM
		LPTVINSERTSTRUCT pTVIS = reinterpret_cast<LPTVINSERTSTRUCT>(lParam);
		TLVITEM itm = { 0 };

			ATLASSERT(pTVIS);
			itm.iSubItem = 0;
			if (pTVIS->item.mask & TVIF_TEXT)
			{
				ATLASSERT(pTVIS->item.pszText != LPSTR_TEXTCALLBACK); // Not supported
				itm.mask |= TLVIF_TEXT;
				itm.pszText = pTVIS->item.pszText;
			}
			SetSubItem(hItem, &itm);
		}
		return (LRESULT)hItem;
	}

	LRESULT OnTreeSetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (!m_ctrlTree.DefWindowProc(uMsg, wParam, lParam))
			return (LRESULT)FALSE;
	
	LPTVITEMEX pItem = reinterpret_cast<LPTVITEMEX>(lParam);
	LPTLVITEM pItemT = _GetSubItem(pItem->hItem, 0);
	
		ATLASSERT(pItemT);
		if (pItemT == NULL)
			return FALSE;

	// Then change the item structure...
	// Copy attributes from caller's TVITEM to internally stored TLVITEM structure.
		if (pItem->mask & TVIF_TEXT)
		{
			if (pItemT->mask & TLVIF_TEXT)
				ATLTRY(delete[] pItemT->pszText);
			ATLTRY(pItemT->pszText = new TCHAR[::lstrlen(pItem->pszText) + 1]);
			::lstrcpy(pItemT->pszText, pItem->pszText);
			pItemT->mask |= TLVIF_TEXT;
		}
		if (pItem->mask & TVIF_IMAGE)
		{
			pItemT->iImage = pItem->iImage;
			pItemT->mask |= TLVIF_IMAGE;
		}
		if (pItem->mask & TVIF_PARAM)
		{
			pItemT->lParam = pItem->lParam;
			pItemT->mask |= TLVIF_PARAM;
		}
		if (pItem->mask & TVIF_STATE)
		{
			pItemT->state &= ~pItem->stateMask;
			pItemT->state |=(pItem->state & pItem->stateMask);
			pItemT->mask |= TLVIF_STATE;
		}
		return (LRESULT)TRUE;
	}
	
	LRESULT OnTreeSetSubItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;	// no need to handle further
		return LRESULT(SetSubItem(reinterpret_cast<HTREEITEM>(wParam), 
			reinterpret_cast<LPTLVITEM>(lParam)));
	}
	
	LRESULT OnTreeGetSubItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;	// no need to handle further
		return LRESULT(GetSubItem(reinterpret_cast<HTREEITEM>(wParam), 
			reinterpret_cast<LPTLVITEM>(lParam)));
	}
	
	LRESULT OnTreeItemDelete(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
	{
	LPNMTREEVIEW pnmt = (LPNMTREEVIEW)pnmh;
	HTREEITEM hItem = pnmt->itemOld.hItem;

		m_ctrlTree.DeletingItem(hItem);

	tMapItem *pVal = m_mapItems.Lookup(hItem);
	
		ATLASSERT(pVal);

	int cnt = pVal->GetSize();

		for (int i = 0; i < cnt; i++)
		{
			LPTLVITEM pItem = (*pVal)[i];
			_DeleteSubItem(pItem);
		}

		m_mapItems.Remove(hItem);
		ATLTRY(delete pVal);
		bHandled = FALSE;
		return 0;
	}
	
	LRESULT OnTreeItemExpanding(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& bHandled)
	{
	NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;

		if (NULL != pNMTreeView && pNMTreeView->action & TVE_EXPAND)
			m_ctrlTree.PreExpandItem(pNMTreeView->itemNew.hItem);

		bHandled = FALSE;
		return 0;
	}
	LRESULT OnTreeItemExpanded(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& bHandled)
	{
	// CWaitingTreeCtrl
	NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;

		if (NULL != pNMTreeView && pNMTreeView -> action & TVE_EXPAND)
			m_ctrlTree.ExpandItem(pNMTreeView -> itemNew.hItem);

	// Auto-scale the first column to the largest tree-item
		if (m_ctrlHeader.GetItemCount() > 0) {
		int cx = 0;
		HTREEITEM hItem = m_ctrlTree.GetNextItem(NULL, TVGN_FIRSTVISIBLE);

			while (hItem != NULL) 
			{
				RECT rc;
				m_ctrlTree.GetItemRect(hItem, &rc, TRUE);
				if (rc.left > cx)
					cx = rc.left;
				hItem = m_ctrlTree.GetNextItem(hItem, TVGN_NEXTVISIBLE);
			}

		HDITEM hdr = { 0 };

			hdr.mask = HDI_WIDTH;
			m_ctrlHeader.GetItem(0, &hdr);
			cx = max(hdr.cxy, cx);
			if (hdr.cxy != cx)
			{
				hdr.cxy = cx;
				m_ctrlHeader.SetItem(0, &hdr);
			}
		}
		bHandled = FALSE;
		return 0;
	}
	
	LRESULT OnTreeSetColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
	LRESULT lRes = m_ctrlTree.DefWindowProc(uMsg, wParam, lParam);
	T* pT = static_cast<T*>(this);
	BOOL bDummy;

		pT->OnSettingChange(0, 0, 0, bDummy);
		return lRes;
	}
	
	LRESULT OnTreeGetItemRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return m_ctrlTree.DefWindowProc(uMsg, wParam, lParam);
	}
	
	LRESULT OnHeaderItemInsert(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		ATLASSERT((int)wParam == m_ctrlHeader.GetItemCount()); // Only supports appending right now!
		LRESULT lRes = m_ctrlHeader.DefWindowProc(uMsg, wParam, lParam);
		if (lRes!=-1)
		{
			LPTLVITEM pItem;
			for (int i = 0; i < m_mapItems.GetSize(); i++)
			{
				tMapItem *pVal = m_mapItems.GetValueAt(i);
				ATLTRY(pItem = new TLVITEM);
				ATLASSERT(pItem);
				::ZeroMemory(pItem, sizeof(TLVITEM));
				pVal->Add(pItem);
			}
			_CalcColumnSizes();
		}
		return lRes;
	}
	
	LRESULT OnHeaderItemDelete(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		for (int i = 0; i < m_mapItems.GetSize(); i++)
		{
			tMapItem *pVal = m_mapItems.GetValueAt(i);
			ATLASSERT(pVal);
			LPTLVITEM pItem = (*pVal)[(int)wParam];
			ATLASSERT(pItem);
			pVal->RemoveAt((int)wParam);
			_DeleteSubItem(pItem);
		}
		bHandled = FALSE;
		return 0;
	}
	
	LRESULT OnHeaderItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& bHandled)
	{
	BOOL bDummy;
	
		OnTreeItemExpanded(0, NULL, bDummy);
		_CalcColumnSizes();
		Invalidate();
		bHandled = FALSE;
		return 0;
	}
	
	LRESULT OnHeaderBeginDrag(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
	{
		LPNMHEADER pnmhd = (LPNMHEADER)pnmh;
		if (pnmhd->iItem == 0)
			return TRUE; // Cannot drag first column
		bHandled = FALSE;
		return 0;
	}
	
	LRESULT OnHeaderEndDrag(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
	{
		LPNMHEADER pnmhd = (LPNMHEADER)pnmh;
		if (pnmhd->iItem == 0)
			return TRUE; // Cannot drag first column, really!
	
	// Bug in MS control requires this extra check.
	RECT rcItem;
	
		m_ctrlHeader.GetItemRect(0, &rcItem);
	
	CPoint pt (GetClientMessagePos());

		if (pt.x <= rcItem.right)
			return TRUE; // Cannot re-order first column
		bHandled = FALSE;
		return 0;
	}
	
	CPoint GetClientMessagePos()
	{
	DWORD dwPos = ::GetMessagePos();
	CPoint pt (GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos));
	
		ScreenToClient(&pt);
		return pt;
	}

	LRESULT OnHeaderBeginTrack(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
	{
	CPoint pt (GetClientMessagePos());
	CRect rcItem;
	LPNMHEADER pnmhd = (LPNMHEADER)pnmh;

		m_ctrlHeader.GetItemRect (pnmhd -> iItem, &rcItem);
		m_lDividerOffset = pt.x - rcItem.right;
		m_lDividerMin = rcItem.left;
		DrawDivider(pt.x);
		return 0;
	}

	LRESULT OnHeaderTrack(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
	{
	long lDividerX = GetClientMessagePos().x;

		DrawDivider();
		if (m_lDividerMin <= lDividerX-m_lDividerOffset)
			DrawDivider(lDividerX);
		else
			DrawDivider(max(m_lDividerMin+m_lDividerOffset, lDividerX));
		return 0;
	}

	LRESULT OnHeaderEndTrack(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
	{
		DrawDivider(max(m_lDividerMin+m_lDividerOffset, m_lDividerX));

	T* pT = static_cast<T*>(this);
	
		pT->UpdateLayout();
		return 0;
	}

	void DrawDivider()
	{
		DrawDivider(m_lDividerX);
	}
	void DrawDivider (long lDividerX)
	{
	CClientDC DC (m_ctrlTree);

		{
		CRect rcTree;
		CPen pen;

			m_ctrlTree.GetClientRect(&rcTree);
			pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

		HPEN hOldPen = DC.SelectPen(pen);

			DC.SetROP2(R2_NOT);
			DC.MoveTo(lDividerX-m_lDividerOffset, rcTree.top);
			DC.LineTo(lDividerX-m_lDividerOffset, rcTree.bottom);
			DC.SelectPen(hOldPen);
		}
		m_lDividerX = lDividerX;
	}

	DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
	{
		if (lpNMCustomDraw->hdr.hwndFrom != m_ctrlTree)
			return CDRF_DODEFAULT;
		::SetViewportOrgEx(lpNMCustomDraw->hdc, m_nOffset, 0, NULL);
		return CDRF_NOTIFYITEMDRAW;   // We need per-item notifications
	}
	
	DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
	{
		if (lpNMCustomDraw->hdr.hwndFrom != m_ctrlTree)
			return CDRF_DODEFAULT;
		
	LPNMTVCUSTOMDRAW pCustomDraw = reinterpret_cast<LPNMTVCUSTOMDRAW>(lpNMCustomDraw);
	
		pCustomDraw->clrText = m_clrBack;
		pCustomDraw->clrTextBk = m_clrBack;
		
	// Reset the focus because it will be drawn by us
		m_iItemState = lpNMCustomDraw->uItemState;
		lpNMCustomDraw->uItemState &= ~(CDIS_FOCUS | CDIS_SELECTED);
		
	// Remember the drawing rectangle of the item so we can draw it ourselves
		m_ctrlTree.GetItemRect((HTREEITEM)lpNMCustomDraw->dwItemSpec, &m_rcItem, TRUE);
		m_rcItem.right = (lpNMCustomDraw->rc.right > m_cxHeader) ? pCustomDraw->nmcd.rc.right : m_cxHeader;
		
		return CDRF_NOTIFYPOSTPAINT;   // We need more notifications
	}
	
	DWORD OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
	{
		if (lpNMCustomDraw->hdr.hwndFrom != m_ctrlTree)
			return CDRF_DODEFAULT;
		T* pT = static_cast<T*>(this);
		pT->DrawTreeItem(lpNMCustomDraw->hdc, (HTREEITEM)lpNMCustomDraw->dwItemSpec, m_iItemState, m_rcItem);
		return CDRF_DODEFAULT;
	}
	
// Overridables
	void UpdateLayout()
	{
		ATLASSERT(::IsWindow(m_ctrlTree));
		ATLASSERT(::IsWindow(m_ctrlHeader));
		
	// FIX: Horizontal scrollbar fix by Nail Kaipov
		m_nOffset = 0;
		if (GetStyle() & WS_HSCROLL) 
			m_nOffset = -GetScrollPos(SB_HORZ); // read scrollbar position

	RECT rcClient;

		GetClientRect(&rcClient);

	WINDOWPOS wpos;
	HDLAYOUT hdl = { 0 };

		hdl.prc = &rcClient;
		hdl.pwpos = &wpos;
		m_ctrlHeader.Layout(&hdl);
		ATLASSERT(wpos.y == 0);
		ATLASSERT(rcClient.top != 0); // We assume that HDLAYOUT is updated (docs doesn't mention it)
		m_ctrlTree.SetWindowPos(HWND_TOP, &rcClient, SWP_NOACTIVATE | SWP_NOZORDER);
		m_ctrlHeader.SetWindowPos(HWND_TOP, wpos.x, wpos.y, wpos.cx, wpos.cy, SWP_NOACTIVATE);
		
		_CalcColumnSizes();

	// FIX: Repaint entire control.
	// NOTE:Cannot just use Invalidate() since WS_CLIPCHILDREN may not be there!!!
		m_ctrlHeader.Invalidate();
		m_ctrlTree.Invalidate();
	}
	
	void DrawTreeItem(HDC hDC, HTREEITEM hItem, UINT iState, RECT &rcItem)
	{
		tMapItem *pVal = m_mapItems.Lookup(hItem);
		ATLASSERT(pVal);
		
		if (iState & CDIS_SELECTED)
		{
			RECT rcHigh = rcItem;
			::FillRect(hDC, &rcHigh, m_brBack);
		}

	// If the item had focus then draw it
		if (iState & CDIS_FOCUS)
		{
			RECT rcFocus = rcItem;
//			rcFocus.left = 1;
			::DrawFocusRect(hDC, &rcFocus);
		}
		
	// Always write text without background
		::SetBkMode(hDC, TRANSPARENT);
		
	// Draw all columns of the item
	RECT rc = rcItem;
	int cnt = pVal->GetSize();

		for (int i = 0; i < cnt; i++)
		{
		LPTLVITEM pItem = (*pVal)[i];
			
			if (i != 0)
				rc.left = m_rcColumns[i].left;
			rc.right = m_rcColumns[i].right;
			
			if (pItem->mask & TLVIF_IMAGE)
			{
			CImageList il = m_ctrlTree.GetImageList(TVSIL_NORMAL);
			int cx, cy;

				il.GetIconSize(cx, cy);
				il.DrawEx(pItem->iImage, hDC, rc.left, rc.top, min(cx, rc.right - rc.left), 
					cy, CLR_NONE, CLR_NONE, ILD_TRANSPARENT);
				rc.left += cx;
			}
			
			if (pItem->mask & TLVIF_TEXT)
			{
				rc.left += 2;
				
				COLORREF clrText = m_clrText;
				if (pItem->mask & TLVIF_TEXTCOLOR)
					clrText = pItem->clrText;
				if (iState & (CDIS_FOCUS | CDIS_SELECTED))
					clrText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
				::SetTextColor(hDC, clrText);
				
			CFont font; 
			HFONT hOldFont = NULL;

				if (pItem->mask & TLVIF_STATE) {
				LOGFONT lf;

					::GetObject(m_ctrlTree.GetFont(), sizeof(LOGFONT), &lf);
					if (pItem->state & TLVIS_BOLD)
						lf.lfWeight += FW_BOLD - FW_NORMAL;
					if (pItem->state & TLVIS_ITALIC)
						lf.lfItalic = TRUE;
					if (pItem->state & TLVIS_UNDERLINE)
						lf.lfUnderline = TRUE;
					if (pItem->state & TLVIS_STRIKEOUT)
						lf.lfStrikeOut = TRUE;

					font.CreateFontIndirect(&lf);
					ATLASSERT(!font.IsNull());
					hOldFont = (HFONT)::SelectObject(hDC, (HFONT)font);
				}
				
			UINT format = pItem->mask & TLVIF_FORMAT ? pItem->format : 0;
				
				::DrawText(hDC, pItem->pszText, -1, &rc, DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS | format);
				if (pItem->mask & TLVIF_STATE)
					::SelectObject(hDC, hOldFont);
			}
		}
	}
	
// Operations
	void ShowHeader(BOOL bShow)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		m_bShowHeader = (bShow == TRUE);
	
	T* pT = static_cast<T*>(this);
	
		pT->UpdateLayout();
		Invalidate();
	}
	
	BOOL SetSubItem(HTREEITEM hItem, const LPTLVITEM pItem)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		ATLASSERT(!::IsBadReadPtr(pItem, sizeof(TLVITEM)));
		if (pItem->iSubItem < 0 || pItem->iSubItem >= m_ctrlHeader.GetItemCount())
			return FALSE;
		
	LPTLVITEM pItemT = _GetSubItem(hItem, pItem->iSubItem);
	
		ATLASSERT(pItemT);
		if (pItemT == NULL)
			return FALSE;
		
	// Copy attributes from caller's TLVITEM to internally stored TLVITEM structure.
		if (pItem->mask & TLVIF_TEXT)
		{
			if (pItemT->mask & TLVIF_TEXT)
				ATLTRY(delete[] pItemT->pszText);
			ATLTRY(pItemT->pszText = new TCHAR[::lstrlen(pItem->pszText) + 1]);
			::lstrcpy(pItemT->pszText, pItem->pszText);
			pItemT->mask |= TLVIF_TEXT;
		}
		if (pItem->mask & TLVIF_IMAGE)
		{
			pItemT->iImage = pItem->iImage;
			pItemT->mask |= TLVIF_IMAGE;
		}
		if (pItem->mask & TLVIF_PARAM)
		{
			pItemT->lParam = pItem->lParam;
			pItemT->mask |= TLVIF_PARAM;
		}
		if (pItem->mask & TLVIF_FORMAT)
		{
			pItemT->format = pItem->format;
			pItemT->mask |= TLVIF_FORMAT;
		}
		if (pItem->mask & TLVIF_STATE)
		{
			pItemT->state &= ~pItem->stateMask;
			pItemT->state |= (pItem->state & pItem->stateMask);
			pItemT->mask |= TLVIF_STATE;
		}
		if (pItem->mask & TLVIF_TEXTCOLOR)
		{
			pItemT->clrText = pItem->clrText;
			pItemT->mask |= TLVIF_TEXTCOLOR;
		}
		return TRUE;
	}
	
	BOOL GetSubItem(HTREEITEM hItem, LPTLVITEM pItem)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		ATLASSERT(!::IsBadWritePtr(pItem, sizeof(TLVITEM)));
		LPTLVITEM pItemT = _GetSubItem(hItem, pItem->iSubItem); 	 
		if (pItemT == NULL)
			return FALSE;
	
	// Copy item data
	UINT mask = pItem->mask;
	
		if (mask & TLVIF_TEXT)
		{
			ATLASSERT(!::IsBadWritePtr(pItem->pszText, pItem->cchTextMax));
			::lstrcpyn(pItem->pszText, pItemT->pszText == NULL ? _T("") : pItemT->pszText, pItem->cchTextMax);
		}
		if (mask & TLVIF_IMAGE)
			pItem->iImage = pItemT->iImage;
		if (mask & TLVIF_FORMAT)
			pItem->format = pItemT->format;
		if (mask & TLVIF_STATE)
		{
			pItem->state &= ~pItem->stateMask;
			pItem->state |= pItemT->state & pItem->stateMask;
		}
		if (mask & TLVIF_TEXTCOLOR)
			pItem->clrText = pItemT->clrText;
		if (mask & TLVIF_PARAM)
			pItem->lParam = pItemT->lParam;	 
		return TRUE;
	}
	
	BOOL SetSubItemText(HTREEITEM hItem, int nSubItem, LPCTSTR pstrString)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		ATLASSERT(!::IsBadStringPtr(pstrString, (UINT) - 1));
		TLVITEM itm = { 0 };
		itm.iSubItem = nSubItem;
		itm.mask = TLVIF_TEXT;
		itm.pszText = const_cast<LPTSTR>(pstrString);
		return SetSubItem(hItem, &itm);
	}
	
	BOOL GetSubItemText(HTREEITEM hItem, int nSubItem, LPTSTR pstrString, UINT cchMax)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		ATLASSERT(!::IsBadWritePtr(pstrString, cchMax));
		LPTLVITEM pItem = _GetSubItem(hItem, nSubItem);
		if (pItem == NULL)
			return FALSE;
		::lstrcpyn(pstrString, pItem->pszText, cchMax);
		return TRUE;
	}
	
	CTreeViewCtrl &GetTreeControl() 
	{
		ATLASSERT(::IsWindow(m_ctrlTree));
		return m_ctrlTree;
	}
	
	CHeaderCtrl &GetHeaderControl() 
	{
		ATLASSERT(::IsWindow(m_ctrlHeader));
		return m_ctrlHeader;
	}
};

///////////////////////////////////////////////////////////////////////////////
// CTreeListView
class CTreeListView : 
	public CTreeListViewImpl<CTreeListView>
{
public:
	DECLARE_WND_CLASS(_T("WTL_TreeListView"))
};

#endif // !defined(_TREELISTVIEW_H__8C3AED92_F46B_4032_B124_6A4C9F94F75F__INCLUDED_)
