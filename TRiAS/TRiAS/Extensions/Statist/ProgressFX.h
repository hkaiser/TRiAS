// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 19.09.2001 12:27:11 
//
// @doc
// @module ProgressFX.h | Declaration of the <c CProgressFX> class

#if !defined(_PROGRESSFX_H__873E8847_1456_4913_A6CB_37CC85206D24__INCLUDED_)
#define _PROGRESSFX_H__873E8847_1456_4913_A6CB_37CC85206D24__INCLUDED_

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

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CProgressFX window

template<class BASE_TYPE>
class CProgressFX : 
	public BASE_TYPE
{
private:
	enum { 
		BORDER_SIZE = 3, 
		PROGRESS_HEIGHT = 16,
		PROGRESS_SIZE = 50, 
		STEP_SIZE = 10 
	};

	CRect m_rcBorder;
	CRect m_rcProg;
	HBRUSH m_hBorderBrush;
	HBRUSH m_hFillBrush;

// Construction
public:
	CProgressFX()
	{
		ShowWaitMessage();
	}

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CProgressFX() {}

protected:
	virtual void PreAnimation(HTREEITEM hItemMsg);
	virtual void DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep);
	virtual void PostAnimation();
};

/////////////////////////////////////////////////////////////////////////////
// CProgressFX
template<class BASE_TYPE>
void CProgressFX<BASE_TYPE>::PreAnimation(HTREEITEM hItemMsg)
{
	BASE_TYPE::PreAnimation(hItemMsg);

// get msg item rect
	GetItemRect(hItemMsg, &m_rcBorder, TRUE);

int margin = (m_rcBorder.Height() - PROGRESS_HEIGHT) / 2;

	margin = (margin < 0) ? 0 : margin;

// set height
	m_rcBorder.top += margin;
	m_rcBorder.bottom -= margin;

// calc progress rect
	m_rcBorder.OffsetRect(m_rcBorder.Width()+BORDER_SIZE, 0);
	m_rcProg = m_rcBorder;
	m_rcProg.DeflateRect(BORDER_SIZE, BORDER_SIZE);

// set width
	m_rcProg.right = m_rcProg.left;
	m_rcBorder.right = m_rcBorder.left + BORDER_SIZE*2 + PROGRESS_SIZE;

// create brushes
	m_hBorderBrush = CreateSolidBrush(RGB(0,0,0));
	m_hFillBrush = CreateSolidBrush(RGB(255,0,0));
}

template<class BASE_TYPE>
void CProgressFX<BASE_TYPE>::PostAnimation()
{
	DeleteObject(m_hBorderBrush);
	DeleteObject(m_hFillBrush);

	BASE_TYPE::PostAnimation();
}

template<class BASE_TYPE>
void CProgressFX<BASE_TYPE>::DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep)
{
	BASE_TYPE::DoAnimation(bTimerEvent, iMaxSteps, iStep);

	if (bTimerEvent) return;	// process only redraw events

CClientDC dc(m_hWnd);

	dc.FrameRect(&m_rcBorder, m_hBorderBrush);

	if (iMaxSteps > 0)	// linear progress
		m_rcProg.right = m_rcProg.left + iStep*PROGRESS_SIZE/iMaxSteps;
	else	// endless progress
		m_rcProg.right = m_rcProg.left + (LONG)(PROGRESS_SIZE*(1 + 
			STEP_SIZE*(double)iStep/PROGRESS_SIZE - 
			log(exp(2) + exp(2*STEP_SIZE*(double)iStep/PROGRESS_SIZE) - 1)/2));

	dc.FillRect(&m_rcProg, m_hFillBrush);
}

#endif // !defined(_PROGRESSFX_H__873E8847_1456_4913_A6CB_37CC85206D24__INCLUDED_)
