// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 04.06.2002 10:57:30 
//
// @doc
// @module TRiASTabChild.h | Declaration of the <c CTRiASTabChild> class

#if !defined(_TRIASTABCHILD_H__855E78EC_1824_4789_987E_4A58124B2D64__INCLUDED_)
#define _TRIASTABCHILD_H__855E78EC_1824_4789_987E_4A58124B2D64__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASTabChild window

class CTRiASTabChild : public CWnd
{
// Construction
public:
	CTRiASTabChild(CWnd *pParent = NULL);

	//{{AFX_DATA(CTRiASTabChild)
	enum { IDD = IDD_TRIASTABCHILD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CComVariant GetIcon()
	{ 
		EnsureIcon();
		return CComVariant(reinterpret_cast<INT_PTR>(m_hIcon), VT_I4); 
	}

// Operations
public:
	void SetBackgroundColor(COLORREF cBackColor);	
	COLORREF GetBackgroundColor();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASTabChild)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTRiASTabChild();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTRiASTabChild)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	bool EnsureIcon();

// Datamember
protected:
	COLORREF m_BackColor;
	HICON m_hIcon;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_TRIASTABCHILD_H__855E78EC_1824_4789_987E_4A58124B2D64__INCLUDED_)
