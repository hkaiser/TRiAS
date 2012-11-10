// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 19.09.2001 12:29:58 
//
// @doc
// @module HourglassFX.h | Declaration of the <c CHourglassFX> class

#if !defined(_HOURGLASSFX_H__EE68A4B2_4CF7_4068_A57E_8010649E22EC__INCLUDED_)
#define _HOURGLASSFX_H__EE68A4B2_4CF7_4068_A57E_8010649E22EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

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
// CHourglassFX window

template<class BASE_TYPE>
class CHourglassFX : 
public BASE_TYPE
{
private:
	enum { 
		ANICURSOR_FRAMES = 10 
	};

	HBRUSH m_hBrush;
	CRect m_rcIcon;
	int m_iAniStep;
	HCURSOR m_hAniCur;

// Construction-Destruction
public:
	CHourglassFX()
	{
		ShowWaitMessage();
		SetAnimationDelay(125);

		m_hAniCur = LoadAniCursor(_Module.GetResourceInstance(), IDR_HOURGLASS);
		_ASSERTE(NULL != m_hAniCur);
	}
	virtual ~CHourglassFX()
	{
		DestroyCursor(m_hAniCur);
	}

protected:
	HCURSOR LoadAniCursor(HINSTANCE hInst, UINT nID)
	{
	HRSRC hRes = FindResource(hInst, MAKEINTRESOURCE(nID), "ANICURSORS");

		if (NULL == hRes)
			return NULL;

	DWORD dwSize = SizeofResource(hInst, hRes);
	HGLOBAL hGlob = LoadResource(hInst, hRes);
	LPBYTE pBytes = (LPBYTE)LockResource(hGlob); 

		if (NULL == hGlob || NULL == pBytes)
			return NULL;

	HCURSOR hCursor = (HCURSOR)CreateIconFromResource(pBytes, dwSize, FALSE, 0x00030000);

		UnlockResource(hGlob);
		return hCursor;
	}

// Implementation
protected:
	virtual void PreAnimation(HTREEITEM hItemMsg);
	virtual void DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep);
	virtual void PostAnimation();
};

/////////////////////////////////////////////////////////////////////////////
// CHourglassFX

template<class BASE_TYPE>
void CHourglassFX<BASE_TYPE>::PreAnimation(HTREEITEM hItemMsg)
{
	BASE_TYPE::PreAnimation(hItemMsg);

	m_iAniStep = 0;

// get msg image rect
	GetItemImageRect(hItemMsg, &m_rcIcon);

// create background brush with current bg color (take rgb part only)
	m_hBrush = CreateSolidBrush(GetBkColor() & 0x00FFFFFF);
}

template<class BASE_TYPE>
void CHourglassFX<BASE_TYPE>::PostAnimation()
{
	DeleteObject(m_hBrush);

	BASE_TYPE::PostAnimation();
}

template<class BASE_TYPE>
void CHourglassFX<BASE_TYPE>::DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep)
{
	BASE_TYPE::DoAnimation(bTimerEvent, iMaxSteps, iStep);

	if (!bTimerEvent) return;	// process only timer events

	m_iAniStep = (m_iAniStep + 1) % ANICURSOR_FRAMES;

CClientDC dc (m_hWnd);

	dc.DrawIconEx(m_rcIcon.left, m_rcIcon.top, m_hAniCur,
		m_rcIcon.Width(), m_rcIcon.Height(), m_iAniStep, m_hBrush, DI_NORMAL);
}

#endif // !defined(_HOURGLASSFX_H__EE68A4B2_4CF7_4068_A57E_8010649E22EC__INCLUDED_)
