// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2001 08:47:39 
//
// @doc
// @module CoolBtn.h | Declaration of the <c CCoolBtn> class

#if !defined(_COOLBTN_H__4DF21FC5_8F2F_4186_B210_86377EF58E22__INCLUDED_)
#define _COOLBTN_H__4DF21FC5_8F2F_4186_B210_86377EF58E22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolBtn window

#define PrepareMenuString "WM_PREPAREPOPUPMENU"
#define DestroyMenuString "WM_DESTROYPOPUPMENU"
#define MenuButtonPushed  "WM_MENUBUTTONPUSHED"

class CCoolBtn : public CButton
{
// Construction
public:
	CCoolBtn();
	BOOL Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
	BOOL SetButtonImage(UINT nResourceId, COLORREF crMask);
	BOOL AddMenuItem(UINT nMenuId,const CString strMenu, UINT nFlags);

// Attributes
protected:
  CMenu        m_menu;
  CBitmap      m_btnImage;
  CImageList   m_IL;
  BOOL         m_bPushed;
  BOOL         m_bMenuPushed;
  BOOL         m_bMenuLoaded;
  BOOL         m_bLoaded;
  BITMAP       m_bm;
  COLORREF	   m_crMask;
  HBITMAP	   m_hbmpDisabled;	

// Operations
public:
protected:
  void DrawArrow(CDC* pDC,CPoint ArrowTip);
  BOOL HitMenuBtn(CPoint point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCoolBtn)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSysColorChange();
	afx_msg LRESULT OnMenuButtonPushed(WPARAM, LPARAM);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_COOLBTN_H__4DF21FC5_8F2F_4186_B210_86377EF58E22__INCLUDED_)
