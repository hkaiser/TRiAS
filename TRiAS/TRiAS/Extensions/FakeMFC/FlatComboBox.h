// FlatComboBox.h : header file
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
/////////////////////////////////////////////////////////////////////////////

#if !defined(FLATCOMBOBOX_H_INCLUDED)
#define FLATCOMBOBOX_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TbtnCmbo.h"

#define FC_DRAWNORMAL	0x00000001
#define FC_DRAWRAISED	0x00000002
#define FC_DRAWPRESSD	0x00000004

/////////////////////////////////////////////////////////////////////////////
// CFlatComboBox window

class CFlatComboBox : public SECComboBtn
{
// Construction
public:
	CFlatComboBox();

// Attributes
public:
	bool		m_bLBtnDown;
	bool		m_bPainted;
	COLORREF	m_clrHilite;
	COLORREF	m_clrShadow;
	COLORREF    m_clrDkShad;
	COLORREF	m_clrButton;

// Operations
public:
	void DrawCombo(DWORD dwStyle, COLORREF clrTopLeft, COLORREF clrBottomRight);
	int Offset();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFlatComboBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(FLATCOMBOBOX_H_INCLUDED)
