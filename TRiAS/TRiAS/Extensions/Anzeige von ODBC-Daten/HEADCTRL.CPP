// This is a part of the Objective Grid C++ Library.
// Copyright (C) 1995-1997 ClassWorks, Stefan Hoenig.
// All rights reserved.
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//

// HeadCtrl.cpp : implementation file
//

#include "pheader.h"
#include "resource.h"
#include "HeadCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_CONTROL(CHeaderBtnControl, CGXStatic)

/////////////////////////////////////////////////////////////////////////////
// CHeaderBtnControl control

CHeaderBtnControl::CHeaderBtnControl(CGXGridCore* pGrid)
	: CGXStatic(pGrid)
{
	m_bPressed = FALSE;
}

CHeaderBtnControl::~CHeaderBtnControl()
{
}

void CHeaderBtnControl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	// Rectangle
	CRect rectItem = rect;

	CRect rectText = GetCellRect(nRow, nCol, rect);

	if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
		return;

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	ROWCOL nCurRow, nCurCol;
	BOOL bCurrent = Grid()->GetCurrentCell(nCurRow, nCurCol) &&		// haben wir überhaupt eine aktive Zelle
						(((nCol == nCurCol) && (nCol != 0)) ||		// JG sind wir in der gleichen Zelle / SPalte ungleich (NULL)
						 ((nRow == nCurRow) && (nRow != 0)) || 
						 ((nRow == nCurRow) && (nCol == nCurCol))	// oder sind wir einfach die aktive Zelle
						);	
	BOOL bActive = Grid()->IsCurrentCell(nRow, nCol) && !Grid()->IsPrinting()
				&& Grid()->IsActiveFrame();

	// Cell-Color
	COLORREF rgbText = style.GetTextColor();

	if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		rgbText = RGB(0,0,0);

	CGXRange r(nRow, nCol);
	Grid()->GetCoveredCellsRowCol(nRow, nCol, r);

	BOOL bDrawPressed = !Grid()->IsPrinting() && bActive && m_bPressed
/*			|| Grid()->GetParam()->m_nLastSortedCol == nCol*/;

	// Background
	DrawBackground(pDC, rect, style);

#if _MFC_VER >= 0x0400
	COLORREF rgb3dDkShadow = ::GetSysColor(COLOR_3DDKSHADOW);
	COLORREF rgb3dHilight = ::GetSysColor(COLOR_3DHILIGHT);
	COLORREF rgb3dShadow = ::GetSysColor(COLOR_3DSHADOW);
	COLORREF rgb3dFace = ::GetSysColor(COLOR_BTNFACE);
#else
	COLORREF rgb3dDkShadow = RGB(0, 0, 0);
	COLORREF rgb3dHilight = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF rgb3dShadow = ::GetSysColor(COLOR_BTNSHADOW);
#endif

	// Draw button look (if not pressed)
	if (!bDrawPressed)
	{
		// Raised
		// 
/*		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgb3dDkShadow, rgb3dDkShadow);
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-2, rect.bottom-2, 1,
			rgb3dHilight, rgb3dShadow);
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgb3dDkShadow, rgb3dDkShadow);
*/		
		if (!bCurrent)
		{
			GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
				rgb3dHilight,  rgb3dShadow);
		}
		else
		{
			// außen
			GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
				rgb3dHilight, rgb3dDkShadow);
			// innen
			GXDraw3dFrame(pDC, rect.left+1, rect.top, rect.right-2, rect.bottom-2, 1,
				rgb3dHilight, rgb3dShadow);
		}
	}
	else
	{
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgb3dDkShadow, rgb3dDkShadow);

		// text will be moved to the bottom-right corner a bit
		rectText += CPoint(1,1);
	}

	pDC->SetBkMode(TRANSPARENT);

	DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();

	if (style.GetWrapText())
		dtAlign |= DT_NOPREFIX | DT_WORDBREAK;
	else
		dtAlign |= DT_NOPREFIX | DT_SINGLELINE;

	pDC->SetTextColor(rgbText);

	CString sOutput;
	if (GetControlText(sOutput, nRow, nCol, NULL, style))
	{
		GXDrawTextLikeMultiLineEdit(pDC,
			sOutput,
			-1,
			rectText,
			(UINT) dtAlign);
	}

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);

	if (pOldFont)
		pDC->SelectObject(pOldFont);
}

BOOL CHeaderBtnControl::LButtonDown(UINT nFlags, CPoint pt, UINT nHitState)
{
	m_bMouseDown = TRUE;
	m_bPressed = TRUE;
	Refresh();

	// unreferenced:
	nFlags, pt, nHitState;

	return TRUE;
}

BOOL CHeaderBtnControl::RButtonDown(UINT nFlags, CPoint pt, UINT nHitState)
{
	m_bMouseDown = TRUE;
	m_bPressed = TRUE;
	Refresh();

	// unreferenced:
	nFlags, pt, nHitState;

	return TRUE;
}

BOOL CHeaderBtnControl::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	nFlags, pt;

	CRect rect = CGXControl::GetCellRect(m_nRow, m_nCol);

	if (m_bMouseDown && m_bPressed && rect.PtInRect(pt))
		OnClickedButton(NULL);

	m_bPressed = FALSE;
	m_bMouseDown = FALSE;
	Refresh();

	// unreferenced:
	nFlags, pt, nHitState;

	return TRUE;
}

BOOL CHeaderBtnControl::RButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	
	CRect rect = CGXControl::GetCellRect(m_nRow, m_nCol);
	if (m_bMouseDown && m_bPressed && rect.PtInRect(pt))
		CGXControl::RButtonUp(nFlags, pt, nHitState);
//		Grid()->OnRButtonClickedRowCol(m_nRow, m_nCol, nFlags, pt);
//		OnClickedButton(NULL);

	m_bPressed = FALSE;
	m_bMouseDown = FALSE;
	Refresh();

	// unreferenced:
	nFlags, pt, nHitState;

	return TRUE;
}

BOOL CHeaderBtnControl::MouseMove(UINT nFlags, CPoint pt, UINT nHitState)
{
	nFlags, pt;

	CRect rect = CGXControl::GetCellRect(m_nRow, m_nCol);

	BOOL bState = rect.PtInRect(pt);

	if (m_bMouseDown && bState != m_bPressed)
	{
		m_bPressed = bState;
		Refresh();
		GridWnd()->UpdateWindow();
	}

	// unreferenced:
	nFlags, pt, nHitState;

	return TRUE;
}

BOOL CHeaderBtnControl::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	// unused:
	nMessage, nRepCnt, flags;

	if (nChar == 32 && nMessage == WM_KEYDOWN)
	{
		// Draw pressed
		m_bPressed = TRUE;
		Refresh();
	}
	else if (nChar == 32 && nMessage == WM_KEYUP && m_bPressed)
	{
		// trigger event
		OnClickedButton(NULL);

		// Draw normal
		m_bPressed = FALSE;
		Refresh();
	}
	return TRUE;
}

void CHeaderBtnControl::InvertBorders(CDC* pDC, const CRect& r)
{
	// I don't want an inverted frame

	// unreferenced:
	pDC, r;
}
