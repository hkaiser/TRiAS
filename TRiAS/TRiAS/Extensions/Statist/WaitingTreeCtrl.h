// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 19.09.2001 11:05:24 
//
// @doc
// @module WaitingTreeCtrl.h | Declaration of the <c CWaitingTreeCtrl> class

#if !defined(_WAITINGTREECTRL_H__213FA492_A69D_4A83_9B77_1E9738535B0F__INCLUDED_)
#define _WAITINGTREECTRL_H__213FA492_A69D_4A83_9B77_1E9738535B0F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#pragma comment(lib, "winmm.lib")

/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000 by Paolo Messina
// (ppescher@yahoo.com)
//
// Free for non-commercial use.
// You may change the code to your needs,
// provided that credits to the original 
// author is given in the modified files.
//  
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWaitingTreeCtrl window
template<class TBase = CTreeViewCtrl, class TWinTraits = CControlWinTraits>
class CWaitingTreeCtrlT : public TBase
{
private:
	HANDLE m_hThread;				// secondary thread for animations
	HANDLE m_hTimerEvent;			// signaled at each timer period
	HANDLE m_hRedrawEvent;			// signaled at each population update
	volatile BOOL m_bAbortAnimation;	// request to terminate secondary thread
	UINT m_nTimerID;				// animation timer id
	UINT m_nTimerDelay;				// animation timer period (ms)
	CString m_sWaitMsg;				// text for the wait message
	HICON m_hIconMsg;				// icon for the wait message
	BOOL m_bShowWaitMsg;			// wether to show the wait message
	int m_iItemIndex;				// population progress index
	int m_iItemCount;				// population progress max index
	HTREEITEM m_hItemMsg;			// wait message item
	HTREEITEM m_hItemToPopulate;	// item being populated

	BOOL m_bDrawSnapshot;			// whether to draw background during populating
	CBitmap m_bmpSnapshot;			// snapshot bitmap

public:
// snapshot support
	LRESULT OnEraseBkGnd(HDC hDC)
	{
		if (!m_bDrawSnapshot)
			return FALSE;

		DrawSnapshot(hDC);
		SetEvent(m_hRedrawEvent);
		return TRUE;
	}

private:
	void TakeSnapshot()
	{
	CRect rcClient;

		GetClientRect(&rcClient);

	int width = rcClient.Width(), height = rcClient.Height();

	// create the snapshot
	CClientDC dc(m_hWnd);
	CDC dcSnapshot;

		dcSnapshot.CreateCompatibleDC(dc);
		m_bmpSnapshot.CreateCompatibleBitmap(dc, width, height);

	// copy the control's background
	CBitmapHandle hOldBmp (dcSnapshot.SelectBitmap(m_bmpSnapshot));

		dcSnapshot.BitBlt(0, 0, width, height, dc, 0, 0, SRCCOPY);
		dcSnapshot.SelectBitmap(hOldBmp);

		m_bDrawSnapshot = TRUE;
	}

	void DrawSnapshot(HDC hDC)
	{
	BITMAP bm;
	
		m_bmpSnapshot.GetBitmap(&bm);

	// prepare the snapshot
	CDC dcSnapshot;
	
		dcSnapshot.CreateCompatibleDC(hDC);
	
	// copy to the control's background
	CBitmapHandle hOldBmp (dcSnapshot.SelectBitmap(m_bmpSnapshot));

		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, dcSnapshot, 0, 0, SRCCOPY);
		dcSnapshot.SelectBitmap(hOldBmp);
	}

	void DestroySnapshot()
	{
		m_bmpSnapshot.DeleteObject();
		m_bDrawSnapshot = FALSE;
	}

// secondary thread entry point
	static DWORD WINAPI AnimationThreadProc(LPVOID pThis)
	{
	CWaitingTreeCtrl* me = (CWaitingTreeCtrl *)pThis;
	HANDLE events[2] = { me->m_hTimerEvent, me->m_hRedrawEvent };
		
		while (!me->m_bAbortAnimation)
		{
		DWORD wait = WaitForMultipleObjects(2, events, FALSE, INFINITE);
			
			if (me->m_bAbortAnimation || wait == WAIT_FAILED)
				break;

			if (wait == WAIT_OBJECT_0)	// timer event
				me->DoAnimation(TRUE, me->m_iItemCount, me->m_iItemIndex);
			else	// redraw event
				me->DoAnimation(FALSE, me->m_iItemCount, me->m_iItemIndex);
		}
		return 0;
	}
	
	void StartAnimation()			// set up animation thread
	{
	// user-defined setup
		PreAnimation(m_hItemMsg);

	// animation can go
		m_bAbortAnimation = FALSE;

	// automatic reset events, signaled
		m_hTimerEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		m_hRedrawEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

	// start animation thread
	DWORD dwThreadID = 0;

		m_hThread = CreateThread(NULL, 0, AnimationThreadProc, this, THREAD_PRIORITY_HIGHEST, &dwThreadID);
	
	// setup timer, if specified
		if (m_nTimerDelay > 0)
			m_nTimerID = (UINT)timeSetEvent(m_nTimerDelay, 5, (LPTIMECALLBACK)m_hTimerEvent, 0, TIME_PERIODIC | TIME_CALLBACK_EVENT_SET);
	}
	void StopAnimation()			// animation clean up
	{
	// stop and destroy timer
		timeKillEvent(m_nTimerID);

	// signal thread to terminate
		m_bAbortAnimation = TRUE;
		SetEvent(m_hRedrawEvent);	// make sure it can see the signal

	// wait thread termination
		WaitForSingleObject(m_hThread, INFINITE);

	// clean up
		CloseHandle(m_hTimerEvent);
		m_hTimerEvent = NULL;
		CloseHandle(m_hRedrawEvent);
		m_hRedrawEvent = NULL;
		CloseHandle(m_hThread);
		m_hThread = NULL;

	// user-defined cleanup
		PostAnimation();
	}

public:
	void PreExpandItem(HTREEITEM hItem)	// before expanding
	{
		if (!NeedsChildren(hItem)) {
			if (WantsRefresh(hItem)) {
			// delete child items before populating
				DeleteChildren(hItem);
			}
			else {
			// doesn't want new items
				m_hItemToPopulate = NULL;
				return;
			}
		}
	
	// if it wants new child items, go on
		m_hItemToPopulate = hItem;

	// fix redraw when expanded programatically
		UpdateWindow();
	
	// hide changes until it's expanded
		SetRedraw(FALSE);
	
	// add wait msg, to allow item expansion
		m_hItemMsg = InsertItem(m_sWaitMsg, m_hItemToPopulate, TVI_LAST);
	
	// zero progress
		m_iItemCount = 1;
		m_iItemIndex = 0;
	}

	void ExpandItem(HTREEITEM hItem)		// after expanded
	{
		if (m_hItemToPopulate == NULL)
			return;	// just expand, doesn't want new items

		_ASSERTE(hItem == m_hItemToPopulate);	// should never fail!!!

		if (m_bShowWaitMsg) {
		// display wait msg now, make sure it's visible
			SetRedraw();
			EnsureVisible(m_hItemMsg);
			UpdateWindow();
		}
	
	// setup animation thread, call PreAnimation
		StartAnimation();
	
	// draw icon
		if (m_bShowWaitMsg)
			DrawUserIcon();
	
	// delay redraw after populating
		SetRedraw(FALSE);
	
	// take a snapshot of the background
		TakeSnapshot();

	// del temporary item (wait msg still shown)
		DeleteItem(m_hItemMsg);
	
	// fill in with sub items
	BOOL bCheckChildren = PopulateItem(hItem);
	
	// clean up animation thread, call PostAnimation
		StopAnimation();
	
	// change parent to reflect current children number
		if (hItem != TVI_ROOT) {
		TVITEM item;
		
			item.hItem = hItem;
			item.mask = TVIF_HANDLE | TVIF_CHILDREN;
			item.cChildren = NeedsChildren(hItem) ? 0 : 1;
			if (bCheckChildren)
				SetItem(&item);
			else if (item.cChildren == 0)
			// restore item's plus button if no children inserted
				SetItemState(hItem, 0, TVIS_EXPANDED);
		}
	// clean up snapshot
		DestroySnapshot();

	// redraw now
		SetRedraw(TRUE);
	}
	void DeletingItem (HTREEITEM hItem)
	{
	}

private:
	BOOL NeedsChildren(HTREEITEM hParent)	// true if no child items
	{
		return (GetChildItem(hParent) == NULL);
	}
	void DeleteChildren(HTREEITEM hParent)
	{
	HTREEITEM hChild = GetChildItem(hParent);

		while (hChild != NULL) {
		HTREEITEM hNext = GetNextSiblingItem(hChild);

			DeleteItem(hChild);
			hChild = hNext;
		}
	}

	void DrawUserIcon()	// draw wait message icon
	{
	// draw user defined icon
	CRect rcIcon;

		if (!GetItemImageRect(m_hItemMsg, &rcIcon))
			return;	// no image

	// create background brush with current bg color (take rgb part only)
	CBrush brush (CreateSolidBrush(GetBkColor() & 0x00FFFFFF));
	CClientDC dc (m_hWnd);

		if (m_hIconMsg != NULL)
			dc.DrawIconEx(rcIcon.left, rcIcon.top, m_hIconMsg, rcIcon.Width(), rcIcon.Height(), 0, brush, DI_NORMAL);
		else
			dc.FillRect(&rcIcon, brush);
	}

// Construction
public:
	CWaitingTreeCtrlT()
	{
		m_bDrawSnapshot = FALSE;

		m_sWaitMsg.LoadString(IDS_LOADING);		// "Loading ..."
		_ASSERTE(m_sWaitMsg.GetLength() > 0);
		m_bShowWaitMsg = FALSE;
		m_hIconMsg = NULL;			// default: blank icon
		m_nTimerDelay = 0;			// default: no timer

		m_hRedrawEvent = NULL;
		m_hTimerEvent = NULL;
		m_hThread = NULL;
	}
	virtual ~CWaitingTreeCtrlT()
	{
	}

// Implementation
public:
	void RefreshSubItems(HTREEITEM hParent)
	{
		if (hParent != TVI_ROOT && !ItemHasChildren(hParent))
			return;

		SetRedraw(FALSE);
		DeleteChildren(hParent);
		if (hParent == TVI_ROOT)
			PopulateRoot();
		else {
			PreExpandItem(hParent);
			ExpandItem(hParent);
		}
		SetRedraw(TRUE);
	}
	void SetWaitMessage(LPCTSTR pszText, HICON hIcon = NULL)
	{
		if (NULL != pszText)
			m_sWaitMsg = pszText;
		m_hIconMsg = hIcon;
	}
	void ShowWaitMessage()
	{
		m_bShowWaitMsg = TRUE;
	}

protected:
// animation functions (with timer)
	void SetAnimationDelay(UINT nMilliseconds)
	{
		// if greater than zero, periodic DoAnimation() will be called
		m_nTimerDelay = nMilliseconds;
	}

// animation functions (with or without timer)
	virtual void PreAnimation(HTREEITEM hItemMsg)
	{
		UNREFERENCED_PARAMETER(hItemMsg);
	}
	virtual void DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep)
	{
		UNREFERENCED_PARAMETER(bTimerEvent);
		UNREFERENCED_PARAMETER(iMaxSteps);
		UNREFERENCED_PARAMETER(iStep);
	}
	virtual void PostAnimation()
	{
	}

// API functions
	BOOL GetItemImageRect(HTREEITEM hItem, LPRECT pRect)
	{
		if (GetImageList(TVSIL_NORMAL) == NULL)
			return FALSE;	// no images

	// get item rect
	CRect rc;

		if (!GetItemRect(hItem, &rc, TRUE))
			return FALSE;

	int cx = GetSystemMetrics(SM_CXSMICON);
	int cy = GetSystemMetrics(SM_CYSMICON);

	// move onto the icon space
	int margin = (rc.Height()-cy)/2;

		rc.OffsetRect(-cx-3 , margin);
		rc.right = rc.left + cx;		// make it square
		rc.bottom = rc.top + cy;		// make it square

		*pRect = rc;
		return TRUE;
	}

	virtual BOOL WantsRefresh(HTREEITEM hItem)
	{
		UNREFERENCED_PARAMETER(hItem);
		return FALSE;	// default implementation, no refresh
	}
	virtual BOOL PopulateItem(HTREEITEM hParent)	// must be implemented
	{
		UNREFERENCED_PARAMETER(hParent);
		_ASSERTE(FALSE);	// must provide an implementation in the derived class
		return FALSE;
	}

public:
// tree content functions
	void PopulateRoot()
	{
		PreExpandItem(TVI_ROOT);
		ExpandItem(TVI_ROOT);
	
	// force update, don't scroll
	SCROLLINFO si;
	
		SetRedraw(FALSE);
		GetScrollInfo(SB_HORZ, &si);
		EnsureVisible(GetChildItem(TVI_ROOT));
		SetScrollInfo(SB_HORZ, &si, FALSE);
		SetRedraw();
	}
// tree content functions (for animations without timer)
	int GetPopulationCount(int *piMaxSubItems)
	{
		if (piMaxSubItems != NULL)
			*piMaxSubItems = m_iItemCount;
		return m_iItemIndex;
	}
	void SetPopulationCount(int iMaxSubItems, int iFirstSubItem = 0)
	{
		m_iItemCount = iMaxSubItems;
		m_iItemIndex = iFirstSubItem;
		SetEvent(m_hRedrawEvent);
	}
	void IncreasePopulation(int iSubItemsToAdd = 1)
	{
		m_iItemIndex += iSubItemsToAdd;
		SetEvent(m_hRedrawEvent);
	}
	void UpdatePopulation(int iSubItems)
	{
		m_iItemIndex = iSubItems;
		SetEvent(m_hRedrawEvent);
	}
};

typedef CWaitingTreeCtrlT<CTreeViewCtrl> CWaitingTreeCtrl;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_WAITINGTREECTRL_H__213FA492_A69D_4A83_9B77_1E9738535B0F__INCLUDED_)
