// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "enhstbar.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CEnhStatusBar message handlers

BEGIN_MESSAGE_MAP(CEnhStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CEnhStatusBar)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_LEFTARROW, OnLeftArrow)
	ON_BN_CLICKED(IDC_BUTTON_RIGHTARROW, OnRightArrow)
	ON_BN_CLICKED(IDC_BUTTON_INFO, OnInfo)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_LEFTARROW, OnUpdateLeftArrow)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_RIGHTARROW, OnUpdateRightArrow)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_INFO, OnUpdateInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEnhStatusBar::CEnhStatusBar()
{
	controlHeight = 13;
	controlSpacing = 2;
	arrowControlWidth = 14;
	infoControlWidth = 14;

	currentMessagePosition = 0;
	statusFlags = 0;
	progressControlPane = -1;
	scrollControlPane = -1;
}

CEnhStatusBar::~CEnhStatusBar()
{
	ClearMessages(FALSE);
}

BOOL CEnhStatusBar::Create(CWnd *wnd, int flags, int progressPane,
		int scrollPane)
{
	if (m_hWnd == 0)
	{
		if (!CStatusBar::Create(wnd))
			return FALSE;
	}
	ClearMessages(FALSE);
	DestroyControls();

	statusFlags = flags;
	progressControlPane = progressPane;
	scrollControlPane = scrollPane;

	if (!AddProgressControl())
		return FALSE;

	if (!AddStatusBarButtons())
		return FALSE;

	if (!AddCustomControls())
		return FALSE;

	EnableToolTips(TRUE);
	PositionControls();
	PositionCustomControls();

	return TRUE;
}

void CEnhStatusBar::DestroyControls()
{
	if (leftButton.m_hWnd)
		leftButton.DestroyWindow();
	if (rightButton.m_hWnd)
		rightButton.DestroyWindow();
	if (infoButton.m_hWnd)
		infoButton.DestroyWindow();
	if (progressControl.m_hWnd)
		progressControl.DestroyWindow();
	DestroyCustomControls();
}

void CEnhStatusBar::DestroyCustomControls()
{
}

void CEnhStatusBar::OnLeftArrow()
{
	OnMessageLeft();
}

void CEnhStatusBar::OnRightArrow()
{
	OnMessageRight();
}

void CEnhStatusBar::OnInfo()
{
	if (currentMessagePosition)
		OnMessageInfo((CStatusBarMessage *)messages.GetAt(currentMessagePosition));
}

void CEnhStatusBar::OnUpdateLeftArrow(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (CanClickLeft());
}

void CEnhStatusBar::OnUpdateRightArrow(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (CanClickRight());
}

void CEnhStatusBar::OnUpdateInfo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (CanClickInfo());
}

int CEnhStatusBar::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	if (!pTI)
		return -1;

	int noPanes = m_nCount;
	int i;
	CRect rect;

	for (i = 0; i < noPanes; i++)
	{
		GetItemRect(i, rect);
		if (rect.PtInRect(point))
		{
			pTI->rect.left = rect.left;
			pTI->rect.top = rect.top;
			pTI->rect.right = rect.right;
			pTI->rect.bottom = rect.bottom;
			CString str(((CEnhStatusBar *)this)->GetToolText(i));
			if (str == "")
				return -1;

			pTI->lpszText = new TCHAR[str.GetLength() + 1];
			strcpy(pTI->lpszText, (LPCTSTR) str);
	
			pTI->hwnd = m_hWnd;
	
			pTI->uFlags = TTF_ALWAYSTIP ;
			pTI->cbSize = sizeof TOOLINFO;
			pTI->uId = (UINT)-2;		   // Dummy id
			return i;
		}
	}

	return -1;
}

// Override me
CString CEnhStatusBar::GetToolText(int i)
{
	return CString("");
}

void CEnhStatusBar::PositionControls()
{
	if ((statusFlags & ENHSBAR_SCROLL_INFO)
		&& (infoButton.m_hWnd == 0 || scrollControlPane == -1))
		return;
	if ((statusFlags & ENHSBAR_SCROLL_ARROWS)
		&& (leftButton.m_hWnd == 0 || rightButton.m_hWnd == 0 ||
		scrollControlPane == -1))
		return;
	if ((statusFlags & ENHSBAR_PROGRESS_BAR)
		&& (progressControl.m_hWnd == 0 || progressControlPane == -1))
		return;

	if (statusFlags & ENHSBAR_SCROLL_ARROWS)
	{
		CRect itemRect;
		GetItemRect(scrollControlPane, &itemRect);
		int rightMost =  itemRect.right - 1;

		int controlTop = ((itemRect.bottom - itemRect.top) - controlHeight)/2 + itemRect.top;

		if (statusFlags & ENHSBAR_SCROLL_INFO)
		{
			CRect infoRect;
			infoRect.right = rightMost;
			infoRect.left = infoRect.right - infoControlWidth;
			infoRect.top = controlTop;
			infoRect.bottom = infoRect.top + controlHeight;
			infoButton.MoveWindow(infoRect);

			rightMost = infoRect.left - controlSpacing;
		}

		CRect rightArrowRect;
		rightArrowRect.right = rightMost;
		rightArrowRect.left = rightArrowRect.right - arrowControlWidth;
		rightArrowRect.top = controlTop;
		rightArrowRect.bottom = rightArrowRect.top + controlHeight;
		rightButton.MoveWindow(rightArrowRect);

		CRect leftArrowRect;
		leftArrowRect.right = rightArrowRect.left - controlSpacing;
		leftArrowRect.left = leftArrowRect.right - arrowControlWidth;
		leftArrowRect.top = controlTop;
		leftArrowRect.bottom = leftArrowRect.top + controlHeight;
		leftButton.MoveWindow(leftArrowRect);
	}

	if (statusFlags & ENHSBAR_PROGRESS_BAR)
	{
		CRect progressRect;
		GetItemRect(progressControlPane, &progressRect);
		if (progressControl.m_hWnd)
			progressControl.MoveWindow(progressRect);
	}
}

void CEnhStatusBar::PositionCustomControls()
{
}

BOOL CEnhStatusBar::AddStatusBarButtons()
{
	// Add buttons to the status bar
	CRect buttonRect;
	if (statusFlags & ENHSBAR_SCROLL_ARROWS)
	{
		buttonRect.left = 100;
		buttonRect.top = 2;
		buttonRect.right = 120;
		buttonRect.bottom = 14;
		if (!leftButton.Create(
			"", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, buttonRect, this,
			IDC_BUTTON_LEFTARROW))
		{
			TRACE0("Failed to create status line left button\n");
			return FALSE;
		}
		if (!leftButton.LoadBitmaps(IDB_LEFTARROW, IDB_LEFTARROW_SEL,
			NULL, IDB_LEFTARROW_DIS))
		{
			TRACE0("Failed to load left arrow bitmap\n");
			return FALSE;
		}
		leftButton.EnableWindow(FALSE);
	
		buttonRect.left = 100;
		buttonRect.top = 2;
		buttonRect.right = 120;
		buttonRect.bottom = 14;
		if(!rightButton.Create(
			"", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, buttonRect, this,
			IDC_BUTTON_RIGHTARROW))
		{
			TRACE0("Failed to create status line right button\n");
			return FALSE;
		}
		if (!rightButton.LoadBitmaps(IDB_RIGHTARROW, IDB_RIGHTARROW_SEL,
			NULL, IDB_RIGHTARROW_DIS))
		{
			TRACE0("Failed to load right arrow bitmap\n");
			return FALSE;
		}
		rightButton.EnableWindow(FALSE);
	}

	if (statusFlags & ENHSBAR_SCROLL_INFO)
	{
		buttonRect.left = 100;
		buttonRect.top = 2;
		buttonRect.right = 120;
		buttonRect.bottom = 14;
		if (!infoButton.Create(
			"", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, buttonRect, this,
			IDC_BUTTON_INFO))
		{
			TRACE0("Failed to create info button\n");
			return FALSE;
		}
		if (!infoButton.LoadBitmaps(IDB_INFO, IDB_INFO_SEL,
			NULL, IDB_INFO_DIS))
		{
			TRACE0("Failed to load info button bitmap\n");
			return FALSE;
		}
		infoButton.EnableWindow(FALSE);
	}
	return TRUE;
}

BOOL CEnhStatusBar::AddProgressControl()
{
	if (statusFlags & ENHSBAR_PROGRESS_BAR)
	{
		// Add progress control to the status bar
		CRect progressRect;
		progressRect.left = 100;
		progressRect.top = 2;
		progressRect.right = 120;
		progressRect.bottom = 14;
		if (!progressControl.Create(WS_CHILD, progressRect, this,
			IDC_PROGRESS_STATUS))
		{
			TRACE0("Failed to create status line left button\n");
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CEnhStatusBar::AddCustomControls()
{
	return TRUE;
}

BOOL CEnhStatusBar::ClearMessages(BOOL update)
{
	POSITION pos = messages.GetHeadPosition();
	CStatusBarMessage *msg = NULL;
	POSITION oldPos = pos;
	while (pos && (msg = (CStatusBarMessage *)messages.GetNext(pos)))
	{
		delete msg;
		messages.RemoveAt(oldPos);
		oldPos = pos;
	}
	currentMessagePosition = 0;
	if (update)
		UpdateStatusBarButtons();
	return TRUE;
}

BOOL CEnhStatusBar::AddMessage(CStatusBarMessage *msg, BOOL update,
							   BOOL showThis)
{
	POSITION pos = messages.AddTail(msg);
	if (currentMessagePosition == 0)
		currentMessagePosition = messages.GetHeadPosition();
	if (showThis)
		currentMessagePosition = pos;

	if (update)
		UpdateStatusBarButtons();
	return TRUE;
}

BOOL CEnhStatusBar::AddMessage(const CString& msg, BOOL update,
							   BOOL showThis)
{
	return AddMessage(new CStatusBarMessage(msg),
		update, showThis);
}

BOOL CEnhStatusBar::RemoveMessage(CStatusBarMessage *message, BOOL update)
{
	POSITION pos = messages.Find(message);
	if (pos)
	{
		messages.RemoveAt(pos);
		if (pos == currentMessagePosition)
			currentMessagePosition = messages.GetHeadPosition();
		if (update)
			UpdateStatusBarButtons();
	}
	return TRUE;
}

BOOL CEnhStatusBar::UpdateStatusBarButtons(BOOL disable)
{
	if ((statusFlags & ENHSBAR_SCROLL_ARROWS) != ENHSBAR_SCROLL_ARROWS)
		return FALSE;

	if ((currentMessagePosition == 0) || disable)
	{
		GetLeftButton().EnableWindow(FALSE);
		GetRightButton().EnableWindow(FALSE);
		if (statusFlags & ENHSBAR_SCROLL_INFO)
			GetInfoButton().EnableWindow(FALSE);
		SetPaneText(0, "Ready");
	}
	else
	{
		GetLeftButton().EnableWindow((currentMessagePosition != messages.GetHeadPosition()));
		GetRightButton().EnableWindow((currentMessagePosition != messages.GetTailPosition()));
		if (statusFlags & ENHSBAR_SCROLL_INFO)
			GetInfoButton().EnableWindow(TRUE);
		CStatusBarMessage *msg = (CStatusBarMessage *)messages.GetAt(currentMessagePosition);
		SetPaneText(0, msg->GetMessage());
	}
	return TRUE;
}

void CEnhStatusBar::ShowProgress(int i, int range)
{
	if ((statusFlags & ENHSBAR_PROGRESS_BAR) != ENHSBAR_PROGRESS_BAR)
		return;
	if (!GetProgressControl().m_hWnd)
		return;

	if (i == -1)
	{
		GetProgressControl().ShowWindow(SW_HIDE);
		return;
	}
	if (range > 0)
		GetProgressControl().SetRange(0, range);

	GetProgressControl().ShowWindow(SW_SHOW);
	GetProgressControl().SetPos(i);
}

void CEnhStatusBar::ShowMessage(const CString& msg, int i)
{
	SetPaneText(i, msg);
	UpdateWindow();
}

void CEnhStatusBar::OnMessageLeft()
{
	if (currentMessagePosition)
	{
		(void) messages.GetPrev(currentMessagePosition);
		UpdateStatusBarButtons();
	}
}

void CEnhStatusBar::OnMessageRight()
{
	if (currentMessagePosition)
	{
		(void) messages.GetNext(currentMessagePosition);
		UpdateStatusBarButtons();
	}
}

void CEnhStatusBar::OnMessageInfo(CStatusBarMessage *msg)
{
	// Add code here, or override
}

BOOL CEnhStatusBar::CanClickLeft()
{
	return ((currentMessagePosition != 0) && (currentMessagePosition != messages.GetHeadPosition()));
}

BOOL CEnhStatusBar::CanClickRight()
{
	return ((currentMessagePosition != 0) && (currentMessagePosition != messages.GetTailPosition()));
}

BOOL CEnhStatusBar::CanClickInfo()
{
	return (currentMessagePosition != 0);
}

/////////////////////////////////////////////////////////////////////////////
// CEnhStatusBar message handlers

void CEnhStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
	
	PositionControls();
	PositionCustomControls();
}
