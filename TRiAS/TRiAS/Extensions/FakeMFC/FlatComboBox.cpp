// FlatComboBox.cpp : implementation file
// 
// Copyright © 1998 Kirk Stowell 
// All Rights Reserved. 
// 
// Email: kstowel@sprynet.com 
// URL:   www.geocities.com/SiliconValley/Haven/8230 
// 
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. If the source code in this file is used in 
// any  commercial application then a statement along the lines of 
// "Portions Copyright © 1998 Kirk Stowell" must be included in 
// the startup banner, "About" box or printed documentation. An email 
// letting me know that you are using it would be nice as well. That's 
// not much to ask considering the amount of work that went into this.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy, and let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into 
// this file. 
//
// History:
// --------
// This control is constantly evolving, sometimes due to new features that I
// feel are necessary, and sometimes due to existing bugs. Where possible I 
// have credited the changes to those who contributed code corrections or
// enhancements (names in brackets) or code suggestions (suggested by...)
//   
//          1.0     02 Oct 1998   First release version.
//          1.01    05 Oct 1998   Fixed cross platform offset bug (Todd Brannam)
//                                to use GetSystemMetrics(), instead of hard coded values.
//			1.02	02 Nov 1998 - Added OnSetFocus(), OnKillFocus() and
//								  modified OnPaint() so the control remains
//								  beveled until it actually looses focus -
//								  (Vachik Hovhannissian).
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.

#if !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <secdll.h>
#include <sdocksta.h>
#include <tbarcust.h>
#endif // !defined(_SEC_VER) || _SEC_VER < 0x0600

#include "FlatComboBox.h"
#include "CoolControlManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatComboBox

CFlatComboBox::CFlatComboBox()
{
	m_bLBtnDown  = false;
	m_bPainted = false;
}

CFlatComboBox::~CFlatComboBox()
{
}

BEGIN_MESSAGE_MAP(CFlatComboBox, SECComboBtn)
	//{{AFX_MSG_MAP(CFlatComboBox)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ENABLE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatComboBox message handlers

//void CFlatComboBox::OnMouseMove(UINT nFlags, CPoint point) 
//{
//	SetTimer(1, 10, NULL);
//	SECComboBtn::OnMouseMove(nFlags, point);
//}
BOOL CFlatComboBox::OnSetCursor (CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) {
		if (message == WM_MOUSEMOVE) {
		CRect rcWindow;

			GetWindowRect (&rcWindow);
			if (rcWindow.PtInRect(GetCurrentMessage()->pt))
			{
				SetTimer(1, 10, NULL);
			}
		}
	}
	return SECComboBtn::OnSetCursor(pWnd, nHitTest, message);
}

void CFlatComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) 
		m_bLBtnDown = true;
	SECComboBtn::OnLButtonDown(nFlags, point);
}

void CFlatComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) {
		m_bLBtnDown = false;
		CComboBox::Invalidate();
	}
	SECComboBtn::OnLButtonUp(nFlags, point);
}

void CFlatComboBox::OnTimer(UINT nIDEvent) 
{
	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) {
	POINT pt;
	CRect rcItem;
		
		GetCursorPos(&pt);
		GetWindowRect(&rcItem);

	// OnLButtonDown, show pressed.
		if (m_bLBtnDown) {
			KillTimer (1);
			if (m_bPainted) {
				DrawCombo(FC_DRAWPRESSD, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
				m_bPainted = false;
			}
			return;
		}

	// If mouse leaves, show flat.
		if (!rcItem.PtInRect(pt)) {
			KillTimer (1);
			if (m_bPainted) {
				DrawCombo(FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_BTNFACE));
				m_bPainted = false;
			}
			return;
		}
		else {
		// On mouse over, show raised.
			if (m_bPainted)
				return;
			else {
				m_bPainted = true;
				DrawCombo (FC_DRAWRAISED, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
			}
		}
	}
	SECComboBtn::OnTimer(nIDEvent);
}

void CFlatComboBox::OnPaint() 
{
//	SECComboBtn::OnPaint();
//	if (m_pToolBar->CoolLookEnabled())
//		DrawCombo (FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_BTNFACE));

	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) {
		ModifyStyleEx (WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 0, SWP_FRAMECHANGED);
		
		SECComboBtn::OnPaint();

	CPoint pt;
	CRect rcItem;

		GetCursorPos(&pt);
		GetWindowRect(&rcItem);

		if ((rcItem.PtInRect(pt)) || (::GetFocus() == m_edit.m_hWnd))
			DrawCombo(FC_DRAWRAISED, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
		else
			DrawCombo(FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_BTNFACE));
	} else
		SECComboBtn::OnPaint();
}

void CFlatComboBox::DrawCombo(DWORD dwStyle, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
CRect rcItem;
CDC* pDC = GetDC();

	GetClientRect(&rcItem);
	
// Cover up dark 3D shadow.
	pDC->Draw3dRect(rcItem, clrTopLeft, clrBottomRight);
	rcItem.DeflateRect(1,1);
	
	if (!IsWindowEnabled()) {
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
	}
	
	else {
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNFACE),
			::GetSysColor(COLOR_BTNFACE));
	}

// Cover up dark 3D shadow on drop arrow.
	rcItem.DeflateRect(1,1);
	rcItem.left = rcItem.right-Offset();
	pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNFACE),
		::GetSysColor(COLOR_BTNFACE));
	
// Cover up normal 3D shadow on drop arrow.
	rcItem.DeflateRect(1,1);
	pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_BTNFACE));
	
	if (!IsWindowEnabled()) 
		return;

	switch (dwStyle) {
	case FC_DRAWNORMAL:
		rcItem.top -= 1;
		rcItem.bottom += 1;
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNHIGHLIGHT));
		rcItem.left -= 1;
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNHIGHLIGHT));
		break;

	case FC_DRAWRAISED:
		rcItem.top -= 1;
		rcItem.bottom += 1;
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));
		break;

	case FC_DRAWPRESSD:
		rcItem.top -= 1;
		rcItem.bottom += 1;
		rcItem.OffsetRect(1,1);
		pDC->Draw3dRect(rcItem, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
		break;
	}

	ReleaseDC(pDC);
}

int CFlatComboBox::Offset()
{
	return ::GetSystemMetrics(SM_CXHTHUMB);		// Thanks to Todd Brannam for this suggestion...
}

void CFlatComboBox::OnSetFocus(CWnd* pOldWnd) 
{
	SECComboBtn::OnSetFocus(pOldWnd);
	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) 
		DrawCombo(FC_DRAWRAISED, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
}

void CFlatComboBox::OnKillFocus(CWnd* pNewWnd) 
{
	SECComboBtn::OnKillFocus(pNewWnd);
	if (m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) 
		DrawCombo(FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_BTNFACE));	
}

void CFlatComboBox::OnEnable(BOOL bEnable) 
{
	SECComboBtn::OnEnable(bEnable);
	if (!bEnable && m_pToolBar->CoolLookEnabled() && !GetCtrlManager().IsEnabled()) 
		DrawCombo(FC_DRAWNORMAL, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_BTNFACE));	
}

///////////////////////////////////////////////////////////////////////////////
// Breite des DropDownFensters gleich hier mit anpassen
HBRUSH CFlatComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
HBRUSH hbr = SECComboBtn::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) {
	case CTLCOLOR_EDIT:
		break;

	case CTLCOLOR_LISTBOX:
		{             
		// benötigte Breite feststellen
		long iListWidth = 0;
		CDC *pDC = GetDC();
		CFont *pOldFont = pDC -> SelectObject (GetFont());

			for (int i = 0; i < GetCount(); i++) {
			CString str;
			CSize sz;

				GetLBText (i, str);
				GetTextExtentPoint32 (pDC -> GetSafeHdc(), str, str.GetLength(), &sz);
				if (pWnd -> GetStyle() & WS_VSCROLL)
					sz.cx += GetSystemMetrics (SM_CXVSCROLL);
				iListWidth = max (iListWidth, sz.cx);
			}

		// jetzt die neue breite setzen
			if (0 < iListWidth) {
			CRect rect;
				
				pWnd->GetWindowRect(&rect);
				if (rect.Width() < iListWidth) {
				// FensterRahmen und etwas Platz lassen
					rect.right = rect.left + iListWidth + 4*GetSystemMetrics(SM_CXBORDER) +2;
					pWnd->MoveWindow(&rect);
				}
			}
			pDC -> SelectObject (pOldFont);
			ReleaseDC(pDC);
		}
		break;
	}
	return hbr; 
}

