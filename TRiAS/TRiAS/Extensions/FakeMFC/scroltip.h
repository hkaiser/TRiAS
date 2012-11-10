// scroltip.h : header file
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
// $Date: 29.05.98 23:41 $
// $Revision: 5 $

/////////////////////////////////////////////////////////////////////////////
// CMRCScrollTip window
#ifndef __SCROLTIP_H__
#define __SCROLTIP_H__

class CMRCScrollTip : public CWnd
{
// Construction
public:
	CMRCScrollTip();

// Attributes
public:
	static CString	m_strWndClass;	// class name
	static CFont	m_fntFont;		// font to use
	static CBrush   m_brBackground;	// brush to use for background
	static CSize	m_sizeVScroll;	// SM_CYVSCROLL, SM_CXVSCROLL metrics
	static CSize	m_sizeHScroll;	// SM_CYHSCROLL, SM_CXHSCROLL metrics
	static CSize    m_sizeThumb;    // SM_CXHTHUMB, SM_CYVTHUMB metrics
    HFONT           m_hFont;        // font to use for text
	CPoint m_pt;					// last Position

// Operations
public:
    BOOL HandleThumbTrackMessage(CWnd * pParent, int nBar, LPCTSTR pszText, CScrollBar * pBar, BOOL fPos);
	BOOL HandleScrollMessage(CWnd * pParent,
                            UINT nSBCode,
                            int nBar,           // SB_VERT or SB_HORZ
                            LPCTSTR pszText,
                            CScrollBar * pBar);  // pointer to the scrollbar  
	
    BOOL Create(CWnd * pParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRCScrollTip)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMRCScrollTip();
    static CPoint GetSliderPositionHelper(CWnd *pParent, int nBar, CScrollBar *pBar, CSize sizeText = CSize(0,0));

	// Generated message map functions
protected:
	//{{AFX_MSG(CMRCScrollTip)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif
/////////////////////////////////////////////////////////////////////////////
