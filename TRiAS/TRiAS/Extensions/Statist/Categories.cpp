// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 13.09.2001 19:01:22 
//
// @doc
// @module Categories.cpp | Definition of the <c CCategories> class

#include "StdAfx.h"

#include "Categories.h"

///////////////////////////////////////////////////////////////////////////////
// 
LRESULT CCategories::OnCtlColorListbox(HDC /*hDC*/, HWND hWnd)
{
// benötigte Breite feststellen
long iListWidth = 0;
HDC hDC = GetDC();
HFONT hOldFont = (HFONT)::SelectObject (hDC, GetFont());

	for (int i = 0; i < GetCount(); i++) {
	CString str;
	CSize sz;

		GetLBText (i, str);
		GetTextExtentPoint32 (hDC, str, str.GetLength(), &sz);
		if (::GetWindowLong(hWnd, GWL_STYLE) & WS_VSCROLL)
			sz.cx += GetSystemMetrics (SM_CXVSCROLL);		// ggf. mit Scrollbar
		sz.cx += 16;		// Bildchenbreite 
		iListWidth = max (iListWidth, sz.cx);
	}

// jetzt die neue breite setzen
	if (0 < iListWidth) {
	CRect rect;
		
		::GetWindowRect(hWnd, &rect);
		if (rect.Width() < iListWidth) {
		// FensterRahmen und etwas Platz lassen
			rect.right = rect.left + iListWidth + 4*GetSystemMetrics(SM_CXBORDER) +2;

		// aufpassen, daß das Fenster auf dem Bildschirm bleibt
		CSize szScreen(::GetSystemMetrics(SM_CXFULLSCREEN), ::GetSystemMetrics(SM_CYFULLSCREEN));
		CSize szToMove (0, 0);

			if (rect.right > szScreen.cx)
				szToMove.cx = rect.right - szScreen.cx;

			rect -= szToMove;
			::MoveWindow(hWnd, rect.left, rect.top, rect.Width(), rect.Height(), FALSE);
		}
	}
	::SelectObject (hDC, hOldFont);
	ReleaseDC(hDC);

	return TRUE;
}

