// DragDropTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ShowOKS.h"
#include "DragDropTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// globale Systemvariablen
const TCHAR g_cbWindowsSection[] = _T("windows");
const TCHAR g_cbScrollInset[] = _T("DragScrollInset");
const TCHAR g_cbScrollDelay[] = _T("DragScrollDelay");

DWORD g_dwScrollInset = ::GetProfileInt (g_cbWindowsSection, g_cbScrollInset, DD_DEFSCROLLINSET);
DWORD g_dwScrollDelay = ::GetProfileInt (g_cbWindowsSection, g_cbScrollDelay, DD_DEFSCROLLDELAY);

/////////////////////////////////////////////////////////////////////////////
// CDragDropTreeCtrl

CDragDropTreeCtrl::CDragDropTreeCtrl()
	: m_fDragging(false), m_fDragDrop(false), 
	  m_fHideCursor(false), m_fScroll(true),
	  m_pDragImage(NULL), m_uiTimer(0L)
{
}

CDragDropTreeCtrl::~CDragDropTreeCtrl()
{
	if (NULL != m_pDragImage)
		delete m_pDragImage;
}


/***********************************************************/
//  DoBeginDrag - private helper function
//  Parameter: The listview pointer that comes with the 
// LVN_BEGINDRAG notification.
//  CreateDragImage, get the initial location, the cursor 
// position and then calculate the hotspot position. Hide 
// cursor and capture mouse.
/***********************************************************/
void CDragDropTreeCtrl::DoBeginDrag (NM_TREEVIEW *pTV)
{
    ASSERT (NULL != pTV);

    m_hDragItem = pTV -> itemNew.hItem;
	m_pDragImage = CreateDragImage (m_hDragItem);
    ASSERT (NULL != m_pDragImage);

// Get the click position. We use GetMessagePos since 
// TVN_BEGINDRAG notification does not give us this info.
DWORD dwPos = GetMessagePos();
CPoint ptClickClient, ptClickScreen;

    ptClickScreen.x = LOWORD (dwPos);
    ptClickScreen.y = HIWORD (dwPos);

    ptClickClient = ptClickScreen;
    ScreenToClient (&ptClickClient);

// Get the cursor hotspot position with respect to 
// the top-left of the drag image.
CPoint ptHotSpot (0, 0);
CRect rcCurrent;

	GetItemRect (m_hDragItem, &rcCurrent, TRUE);

	ptHotSpot.x = ptClickClient.x - rcCurrent.left + 18;	// ImageBreite + 2
	ptHotSpot.y = ptClickClient.y - rcCurrent.top;

    if (m_pDragImage -> BeginDrag (0, ptHotSpot)) {
	// DragEnter uses the desktop window, so that the cursor 
	// gets displayed even if the user moves the cursor out 
	// of the treeview.
        m_pDragImage -> DragEnter (NULL, ptClickScreen);
		if (m_fHideCursor)
			ShowCursor (FALSE);

		m_uiTimer = SetTimer (TIMER_FAKE_MOUSEMOVE, TIMER_FAKE_MOUSEMOVE_TIMEOUT, NULL);
        SetCapture();
        m_fDragging = TRUE;
    }
}

/***********************************************************/
// DoEndDrag - private helper function
// Ends the drag operation. Called from WM_LBUTTONUP handler.
// Parameter: Point to move to, flag indicating whether to move 
// the item or not. Flag is false if the user presses 
// Escape to abort dragging. If the item is to be moved, then 
// call out to virtual function to handle the actual move.
/***********************************************************/
void CDragDropTreeCtrl::DoEndDrag (CPoint point, BOOL bMoveItem)
{
    if (m_fDragging) {
        ASSERT (NULL != m_pDragImage);

        m_pDragImage -> DragLeave (NULL);
        m_pDragImage -> EndDrag();
		SelectDropTarget(NULL);

		delete m_pDragImage;
		m_pDragImage = NULL;

		if (0 != m_uiTimer) {
			KillTimer (TIMER_FAKE_MOUSEMOVE);
			m_uiTimer = 0;
		}

        m_fDragging = false;
		if (m_fHideCursor)
			ShowCursor (TRUE);
        ReleaseCapture();		// unbedingt _nach_ m_fDragging = false, da sonst Rekursion

	// Call out to virtual function which will handle 
	// the actual moving.
        if (bMoveItem) 
            HandleItemMove (m_hDragItem, point);
    }
}

/***********************************************************/
// OnCustomGetDlgCode - handler for WM_GETDLGCODE. We are 
// not using MFC's OnGetDlgCode because we need the w and 
// lParams. For more information, read the note on the MSDN
// CD-ROM PSS No. Q83302.
// This just handles the escape key while you are dragging.
/***********************************************************/
LRESULT CDragDropTreeCtrl::OnCustomGetDlgCode (UINT wParam, LPARAM lParam)
{
LRESULT lResult = Default();

    if (m_fDragging && 0L != lParam) {
	LPMSG lpMsg = (LPMSG)lParam;

		if (WM_KEYDOWN == lpMsg->message && VK_ESCAPE == lpMsg->wParam) {
		POINT pt;       // Not used logically.

            DoEndDrag (pt, FALSE);
            lResult |= DLGC_WANTMESSAGE;
        }
    }
    return lResult;
}

///////////////////////////////////////////////////////////////////////////////
// Während des DD's scrollen
void CDragDropTreeCtrl::ScrollUpDown(bool fUp)
{
	ASSERT(NULL != m_pDragImage);

HTREEITEM hFirst = GetFirstVisibleItem();

	if (NULL == hFirst)	return;			// no items in tree (snh)

HTREEITEM hNext = GetNextItem (hFirst, fUp ? TVGN_PREVIOUSVISIBLE : TVGN_NEXTVISIBLE);
HTREEITEM hItem = GetDropHilightItem();

	if (NULL != hItem)
		hItem = GetNextItem (hItem, TVGN_NEXTVISIBLE);

	if (NULL != hNext && NULL != hItem) {
	// wenn nicht das allerletzte Item 
		m_pDragImage -> DragShowNolock(FALSE);
		Select (hNext, TVGN_FIRSTVISIBLE);
		UpdateWindow();
		m_pDragImage -> DragShowNolock(TRUE);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Default overrideables.

/***********************************************************/
// AllowDragOperation - virtual function. Override to 
// control whether an item can be moved or not.
// Current implementation allows dragging for icon and 
// small icon views.
// Parameters: Current view and item to move.
// Return TRUE to allow drag, FALSE to disallow.
/***********************************************************/
BOOL CDragDropTreeCtrl::AllowDragOperation (HTREEITEM hDragItem)
{
	return m_fDragDrop;
}

/***********************************************************/
// HandleDragMove - overrideable virtual function.
// Parameters: CImageList pointer. This is initially set 
// to the default listview image. pt indicates the client 
// position of the mouse.
// The default version does nothing. 
// Set the imagelist pointer to what you want displayed and 
// the point at which it is to be displayed.
/***********************************************************/
void CDragDropTreeCtrl::HandleDragMove (CImageList *pDragImage, CPoint& pt)
{
}

/***********************************************************/
// HandleItemMove - virtual function. Override to do the 
// actual move of the item.
// Current implementation moves the item for icon and 
// small icon views.
// Parameters: Dragged item, point at which item was 
// dropped (client coordinates).
/***********************************************************/
void CDragDropTreeCtrl::HandleItemMove (HTREEITEM hDragItem, CPoint point)
{
}

/////////////////////////////////////////////////////////////////////////////
// CDragDropTreeCtrl message handlers

BEGIN_MESSAGE_MAP(CDragDropTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CDragDropTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    ON_MESSAGE(WM_GETDLGCODE, OnCustomGetDlgCode)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_TIMER()
	ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDragDropTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    SetFocus();    
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CDragDropTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnLButtonUp(nFlags, point);
    if (m_fDragging)
        DoEndDrag (point, TRUE);
}

void CDragDropTreeCtrl::OnMouseMove(UINT nFlags, CPoint pt) 
{
    if (m_fDragging) {
		ASSERT (NULL != m_pDragImage);
	
	// Call out to virtual function to handle move.
		HandleDragMove (m_pDragImage, pt);

	// Convert to screen coordinates, since DragMove uses the 
	// desktop window.
	POINT ptScreen = pt;

		ClientToScreen (&ptScreen);
		m_pDragImage -> DragMove (ptScreen);

	// Hilite target
	TV_HITTESTINFO tvHit;

		tvHit.pt.x = pt.x;
		tvHit.pt.y = pt.y;

	HTREEITEM hTarget;

		if (NULL != (hTarget = HitTest (&tvHit))) {
			m_pDragImage -> DragShowNolock(FALSE);
			EnsureVisible (hTarget);
			SelectDropTarget (hTarget);
			m_pDragImage -> DragShowNolock(TRUE);
		}

	// wenn scrolling erlaubt und notwendig, dann dieses hier tun
		if (m_fScroll) {
		CRect rcC;

			GetClientRect (&rcC);

		// Check vertical inset
			if (tvHit.flags & TVHT_ABOVE || pt.y <= rcC.top + (int)g_dwScrollInset)
				ScrollUpDown (true);
			else if (tvHit.flags & TVHT_BELOW || pt.y >= rcC.bottom - (int)g_dwScrollInset)
				ScrollUpDown (false);
		}
	}

	CTreeCtrl::OnMouseMove(nFlags, pt);
}

/*
// Check horizontal inset
	if (pt.x <= rcC.left + (int)m_uiScrollInset)
		uRet |= UDROP_INSETLEFT;
	else if (pt.x >= rcC.right - (int)m_uiScrollInset)
		uRet |= UDROP_INSETRIGHT;
*/
void CDragDropTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pTV = (NM_TREEVIEW*)pNMHDR;
	
	if (m_fDragDrop && AllowDragOperation (pTV -> itemNew.hItem))
		DoBeginDrag (pTV);
	*pResult = 0;
}


void CDragDropTreeCtrl::OnTimer(UINT nIDEvent) 
{
	if (TIMER_FAKE_MOUSEMOVE == nIDEvent) {
		ASSERT(m_fDragging);
		ASSERT(NULL != m_pDragImage);
	
	// Call out to virtual function to handle move.
	DWORD dwPos = GetMessagePos();
	CPoint pt (LOWORD(dwPos), HIWORD(dwPos));

		ScreenToClient (&pt);
		HandleDragMove (m_pDragImage, pt);

	// wenn scrolling erlaubt und notwendig, dann dieses hier tun
		if (m_fScroll) {
		CRect rcC;
		UINT uiFlags = 0;

			GetClientRect (&rcC);
			HitTest (pt, &uiFlags);

		// Check vertical inset
			if (uiFlags & TVHT_ABOVE || pt.y <= rcC.top + (int)g_dwScrollInset)
				ScrollUpDown (true);
			else if (uiFlags & TVHT_BELOW || pt.y >= rcC.bottom - (int)g_dwScrollInset)
				ScrollUpDown (false);
		}
	}
	CTreeCtrl::OnTimer(nIDEvent);
}

void CDragDropTreeCtrl::OnCaptureChanged(CWnd *pWnd) 
{
	CTreeCtrl::OnCaptureChanged(pWnd);
    if (m_fDragging) {
	CPoint ptDummy;

		DoEndDrag (ptDummy, FALSE);
	}
}

