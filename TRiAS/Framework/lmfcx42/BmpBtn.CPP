// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "LafxPriv.h"

#ifdef AFX_AUX_SEG
#pragma code_seg(AFX_AUX_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

IMPLEMENT_DYNAMIC(CBmpBtn, CButton)

/////////////////////////////////////////////////////////////////////////////
// CBmpBtn

CBmpBtn::CBmpBtn()
{
}

CBmpBtn::~CBmpBtn()
{
}


BEGIN_MESSAGE_MAP(CBmpBtn, CButton)
	//{{AFX_MSG_MAP(CBmpBtn)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpBtn message handlers

BOOL CBmpBtn::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	static BOOL bLockout = FALSE;

	if (message == WM_COMMAND && !bLockout)
	{
		int nCode;
#ifdef WIN32
		nCode = HIWORD(wParam);
#else
	#define BN_DBLCLK BN_DOUBLECLICKED
		nCode = HIWORD(lp);
#endif
		if (nCode == BN_CLICKED || nCode == BN_DBLCLK)
		{
			bLockout = TRUE;
			GetOwner()->SendMessage(message, wParam, lParam);
			bLockout = FALSE;
		}
	}
	return CButton::OnChildNotify(message,wParam,lParam,pLResult);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpBtn operations

BOOL CBmpBtn::LoadBitmaps(UINT nIDBitmapResource,
	UINT nIDBitmapResourceSel, UINT nIDBitmapResourceFocus,
	UINT nIDBitmapResourceDisabled)
	{ return LoadBitmaps(MAKEINTRESOURCE(nIDBitmapResource),
		MAKEINTRESOURCE(nIDBitmapResourceSel),
		MAKEINTRESOURCE(nIDBitmapResourceFocus),
		MAKEINTRESOURCE(nIDBitmapResourceDisabled)); }

// LoadBitmaps will load in one, two, three or all four bitmaps
// returns TRUE if all specified images are loaded
BOOL CBmpBtn::LoadBitmaps(LPCTSTR lpszBitmapResource,
	LPCTSTR lpszBitmapResourceSel, LPCTSTR lpszBitmapResourceFocus,
	LPCTSTR lpszBitmapResourceDisabled)
{
	// delete old bitmaps (if present)
	m_bitmap.DeleteObject();
	m_bitmapSel.DeleteObject();
	m_bitmapFocus.DeleteObject();
	m_bitmapDisabled.DeleteObject();

	if (!m_bitmap.LoadBitmap(lpszBitmapResource))
	{
		TRACE0("Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}
	BOOL bAllLoaded = TRUE;
	if (lpszBitmapResourceSel != NULL)
	{
		if (!m_bitmapSel.LoadBitmap(lpszBitmapResourceSel))
		{
			TRACE0("Failed to load bitmap for selected image.\n");
			bAllLoaded = FALSE;
		}
	}
	if (lpszBitmapResourceFocus != NULL)
	{
		if (!m_bitmapFocus.LoadBitmap(lpszBitmapResourceFocus))
			bAllLoaded = FALSE;
	}
	if (lpszBitmapResourceDisabled != NULL)
	{
		if (!m_bitmapDisabled.LoadBitmap(lpszBitmapResourceDisabled))
			bAllLoaded = FALSE;
	}
#ifdef _MAC
	ASSERT(m_bitmap.m_hObject != NULL);
	::SetBitmapReadOnly((HBITMAP)m_bitmap.m_hObject, BRO_READONLY);
	if (m_bitmapSel.m_hObject != NULL)
		::SetBitmapReadOnly((HBITMAP)m_bitmapSel.m_hObject, BRO_READONLY);
	if (m_bitmapFocus.m_hObject != NULL)
		::SetBitmapReadOnly((HBITMAP)m_bitmapFocus.m_hObject, BRO_READONLY);
	if (m_bitmapDisabled.m_hObject != NULL)
		::SetBitmapReadOnly((HBITMAP)m_bitmapDisabled.m_hObject, BRO_READONLY);
#endif
	return bAllLoaded;
}

// SizeToContent will resize the button to the size of the bitmap
void CBmpBtn::SizeToContent()
{
	ASSERT(m_bitmap.m_hObject != NULL);
	CSize bitmapSize;
	BITMAP bmInfo;
	VERIFY(m_bitmap.GetObject(sizeof(bmInfo), &bmInfo) == sizeof(bmInfo));
	VERIFY(SetWindowPos(NULL, -1, -1, bmInfo.bmWidth, bmInfo.bmHeight,
		SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE));
}

// Autoload will load the bitmap resources based on the text of
//  the button
// Using suffices "U", "D", "F" and "X" for up/down/focus/disabled
BOOL CBmpBtn::AutoLoad(UINT nID, CWnd* pParent)
{
	// first attach the CBmpBtn to the dialog control
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	CString buttonName;
	GetWindowText(buttonName);
	ASSERT(!buttonName.IsEmpty());      // must provide a title

	LoadBitmaps(buttonName + _T("U"), buttonName + _T("D"),
	  buttonName + _T("F"), buttonName + _T("X"));

	// we need at least the primary
	if (m_bitmap.m_hObject == NULL)
		return FALSE;

	// size to content
	SizeToContent();
	return TRUE;
}

// Draw the appropriate bitmap
void CBmpBtn::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);
	// must have at least the first bitmap loaded before calling DrawItem
	ASSERT(m_bitmap.m_hObject != NULL);     // required

	// use the main bitmap for up, the selected bitmap for down
	CBitmap* pBitmap = &m_bitmap;
	UINT state = lpDIS->itemState;
	if ((state & ODS_SELECTED) && m_bitmapSel.m_hObject != NULL)
		pBitmap = &m_bitmapSel;
#ifndef _MAC
	else if ((state & ODS_FOCUS) && m_bitmapFocus.m_hObject != NULL)
#else
	else if ((state & ODS_FOCUS) && m_bitmapFocus.m_hObject != NULL &&
			(GetParent()->GetStyle() & DS_WINDOWSUI))
#endif
		pBitmap = &m_bitmapFocus;   // third image for focused
	else if ((state & ODS_DISABLED) && m_bitmapDisabled.m_hObject != NULL)
		pBitmap = &m_bitmapDisabled;   // last image for disabled

	// draw the whole button
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOld = memDC.SelectObject(pBitmap);
	if (pOld == NULL)
		return;     // destructors will clean up

	CRect rect;
	rect.CopyRect(&lpDIS->rcItem);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpBtn diagnostics
#ifdef _DEBUG
void CBmpBtn::AssertValid() const
{
	CButton::AssertValid();

	m_bitmap.AssertValid();
	m_bitmapSel.AssertValid();
	m_bitmapFocus.AssertValid();
	m_bitmapDisabled.AssertValid();
}

void CBmpBtn::Dump(CDumpContext& dc) const
{
	CButton::Dump(dc);

	dc << "m_bitmap = " << (UINT)m_bitmap.m_hObject;
	dc << "\nm_bitmapSel = " << (UINT)m_bitmapSel.m_hObject;
	dc << "\nm_bitmapFocus = " << (UINT)m_bitmapFocus.m_hObject;
	dc << "\nm_bitmapDisabled = " << (UINT)m_bitmapDisabled.m_hObject;

	dc << "\n";
}
#endif

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////

