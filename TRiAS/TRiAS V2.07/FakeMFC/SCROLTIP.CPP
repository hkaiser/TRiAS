// Scroltip.cpp : implementation file
//
// (C)1994-6 Mark Conway.
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation. In addition, you may also charge for any
//  application	using this source code, and are under no obligation to supply
//  source code to purchasers. You must accredit the author in the "About Box",
//  and/or banner of your application.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
// $Author: Hartmut Kaiser $
// $Date: 15.06.98 22:04 $
// $Revision: 8 $

#include "fakemfcp.hxx"
#include "scroltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRCScrollTip

CMRCScrollTip::CMRCScrollTip()
{
}

CMRCScrollTip::~CMRCScrollTip()
{
}

///////////////////////////////////////////////////////////////////////////////
// statics
CBrush  CMRCScrollTip::m_brBackground;
CString	CMRCScrollTip::m_strWndClass;	
CFont	CMRCScrollTip::m_fntFont;		

CSize	CMRCScrollTip::m_sizeVScroll;		// SM_CYVSCROLL, SM_CXVSCROLL metrics
CSize	CMRCScrollTip::m_sizeHScroll;		// SM_CYHSCROLL, SM_CXHSCROLL metrics
CSize   CMRCScrollTip::m_sizeThumb;         // SM_CXHTHUMB, SM_CYVTHUMB metrics


BEGIN_MESSAGE_MAP(CMRCScrollTip, CWnd)
	//{{AFX_MSG_MAP(CMRCScrollTip)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMRCScrollTip message handlers

// Handles the thumbtrack message. ie moves the window to the slider position,
// and sets the window text
BOOL CMRCScrollTip::HandleThumbTrackMessage(
	CWnd *pParent, int nBar, LPCTSTR pszText, CScrollBar *pBar, BOOL fPos)
{
// workout the size of the text
	CSize sizeText;
	{
	CClientDC dc(this);				
    CFont * pOldFont = dc.SelectObject(CFont::FromHandle(m_hFont));			

		sizeText = dc.GetTextExtent(pszText);		
		dc.SelectObject(pOldFont);
	}				// release client DC
	sizeText.cx += 6;			// allow space for a border
	sizeText.cy += 6;

// work-out where to place the slider
	if (fPos) {
		m_pt = GetSliderPositionHelper(pParent, nBar, pBar, sizeText);

	// now clip to size of screen
		if (IsWin40()) {
		CRect rc;

			SystemParametersInfo (SPI_GETWORKAREA, 0, (RECT *)&rc, 0);
			m_pt.x = min(m_pt.x, rc.right - sizeText.cx);
			m_pt.y = min(m_pt.y, rc.bottom - sizeText.cy);
		} else {
			m_pt.x = min(m_pt.x, (GetSystemMetrics(SM_CXSCREEN/*SM_CXFULLSCREEN*/) - sizeText.cx));
			m_pt.y = min(m_pt.y, (GetSystemMetrics(SM_CYSCREEN/*SM_CYFULLSCREEN*/) - sizeText.cy));
		}
	}
			
// Set the window text, and move the window
	SetWindowText(pszText);
	SetWindowPos(NULL, m_pt.x, m_pt.y, sizeText.cx, sizeText.cy, SWP_SHOWWINDOW | SWP_NOACTIVATE) ;
	InvalidateRect(NULL);
	UpdateWindow();				// force update of window
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// lazy message - does all the tooltip stuff for you.
BOOL CMRCScrollTip::HandleScrollMessage(CWnd * pParent, UINT nSBCode, int nBar, LPCTSTR pszText, CScrollBar * pBar)
{
	switch(nSBCode)
	{
	case SB_THUMBTRACK:
		{
			// create the window if neccessary
			if (m_hWnd == NULL) {
				if (!Create(pParent))
					return FALSE;

				HandleThumbTrackMessage(pParent, nBar, pszText, pBar, TRUE);
				break;
			} 
		    
			HandleThumbTrackMessage(pParent, nBar, pszText, pBar, FALSE);
            break;
		}

	case SB_THUMBPOSITION:
		{
			if (m_hWnd != NULL)
			{
				DestroyWindow();			// destroy the window
			}
			break;
		}
	}
	return TRUE;
}

BOOL CMRCScrollTip::Create(CWnd * pParent)
{
  	m_sizeVScroll.cx = GetSystemMetrics(SM_CXVSCROLL);
  	m_sizeVScroll.cy = GetSystemMetrics(SM_CYVSCROLL);
  	m_sizeHScroll.cx = GetSystemMetrics(SM_CXHSCROLL);
  	m_sizeHScroll.cy = GetSystemMetrics(SM_CYHSCROLL);
  	m_sizeThumb.cx = GetSystemMetrics(SM_CXHTHUMB);
  	m_sizeThumb.cy = GetSystemMetrics(SM_CYVTHUMB);

	// register a classname for this window...
  	if (m_strWndClass.IsEmpty())
  	{
    	// register the class name
    	m_strWndClass = AfxRegisterWndClass(/*CS_BYTEALIGNCLIENT |*/ CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW,
							0 ,
							NULL);	// Use a NULL brush - we draw the background ourselves
		// for vertical-only scroll bars, we could use CS_BYTEALIGNCLIENT, which results
		// in marginally faster drawing, but not much use for following horizonals, as we'd
		// jump in byte-sized chunks
		

    	// we're we successful?
    	if (m_strWndClass.IsEmpty())
     	 	return FALSE;  // return failed
  	
	
		VERIFY(m_brBackground.CreateSolidBrush((::GetSysColor(COLOR_INFOBK))));
	}

	
// create the bubble window and set the created flag
CRect rect;

  	rect.SetRectEmpty();
  	
BOOL bCreated = CreateEx(0, m_strWndClass, "", WS_POPUP | WS_BORDER,
    						rect.left, rect.top, rect.right, rect.bottom, 
       						pParent->GetSafeHwnd(),
        	                (HMENU) NULL);

	if (!bCreated)
		return FALSE;
	
// create a suitable font to use...
	if(m_fntFont.GetSafeHandle() == NULL) {
	CClientDC dc(this);  // used to calculate the font size
	LOGFONT lf;

		memset(&lf, 0, sizeof(LOGFONT));
      
	    lf.lfHeight = -::MulDiv(-10, dc.GetDeviceCaps(LOGPIXELSY), 72);
    	lf.lfCharSet = ANSI_CHARSET;
    	lf.lfQuality = DEFAULT_QUALITY;
    	lf.lfClipPrecision = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
    	lf.lfPitchAndFamily = FF_SWISS;

    	if (!m_fntFont.CreateFontIndirect(&lf))
			return FALSE;
	}
    m_hFont = HFONT(m_fntFont);             // current font = this default one

  	// success
  	return TRUE;
}


//---------------------------------------------------------------------------
void CMRCScrollTip::OnPaint() 
//---------------------------------------------------------------------------
{
CPaintDC dc(this); // device context for painting
	
// paint the window text, centred in the window
CRect rect;

  	GetClientRect(rect);
  
CFont *pOldFont = dc.SelectObject(CFont::FromHandle(m_hFont));
	
	dc.SetBkMode(TRANSPARENT);
  	dc.SetTextColor(::GetSysColor(COLOR_INFOTEXT));  

// draw the text
CString strText;

  	GetWindowText(strText);
  	dc.FillRect(&rect, &m_brBackground);				// erase as close to draw as possible	
	dc.DrawText(strText, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER | DT_SINGLELINE); // know it'll fit 
  
// clean up the DC
  	dc.SelectObject(pOldFont);
}


///////////////////////////////////////////////////////////////////////////////
// returns suitable position for centre of the slider for a scrollbar
CPoint CMRCScrollTip::GetSliderPositionHelper(
	CWnd *pParent, int nBar, CScrollBar *pBar, CSize sizeText)
{
CPoint pt;    
CWnd * pWnd;
SCROLLINFO SI;
CRect rcWnd;			
int nWidth, nPos;
    
    if (pBar == NULL)
    {
		pParent->GetScrollInfo(nBar, &SI, SIF_TRACKPOS | SIF_PAGE | SIF_RANGE);
		pWnd = pParent;
    }
    else
    {
        nBar = ((pBar->GetStyle() & SBS_VERT) ? SB_VERT : SB_HORZ);
		pBar->GetScrollInfo(&SI, SIF_TRACKPOS | SIF_PAGE | SIF_RANGE);
        pWnd = pBar;
    }
	
    pWnd->GetClientRect(&rcWnd);
	if (SI.nMin == SI.nMax)
		return FALSE;			// NULL range - prevent divide by zero later
                    
    if (nBar == SB_VERT)
	{
        nWidth = rcWnd.Height() - m_sizeVScroll.cy * 2;
	}
	else
	{
		nWidth = rcWnd.Width() - m_sizeHScroll.cx * 2;
	}
    
    if (SI.nPage == 0)
    {
        nWidth -= (nBar == SB_VERT ? m_sizeThumb.cy : m_sizeThumb.cx);
    }            
    
    nPos = (SI.nTrackPos + (SI.nPage / 2)) * nWidth / (SI.nMax - SI.nMin);

	if (nBar == SB_VERT)
	{
		pt.y = nPos + m_sizeVScroll.cy - sizeText.cy / 2;
		pt.x = rcWnd.Width();
        if (pBar == NULL)
            pt.x += m_sizeVScroll.cx;
        if (SI.nPage == 0)
            pt.y += m_sizeThumb.cy / 2;
    }   
	else
	{
		pt.x = nPos + m_sizeHScroll.cx - sizeText.cx / 2;
		pt.y = rcWnd.Height();
        if (pBar == NULL)
            pt.y += m_sizeHScroll.cy;
        if (SI.nPage == 0)
            pt.x += m_sizeThumb.cx / 2;
    }
	pWnd->ClientToScreen(&pt);
    return pt;
}

