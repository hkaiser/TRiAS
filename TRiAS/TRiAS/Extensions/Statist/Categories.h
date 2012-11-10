// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 13.09.2001 18:57:41 
//
// @doc
// @module Categories.h | Declaration of the <c CCategories> class

#if !defined(_CATEGORIES_H__B5AD952B_3EC0_401E_BEF9_EB906B780A29__INCLUDED_)
#define _CATEGORIES_H__B5AD952B_3EC0_401E_BEF9_EB906B780A29__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
class CCategories :
	public CWindowImpl<CCategories, CComboBoxEx>
{
public:
// Construction
	typedef CWindowImpl<CCategories, CComboBoxEx> base_t;

	CCategories() {}

// Attributes
public:

// Operations
public:

// Implementation
public:
	~CCategories() {}

	// Generated message map functions
protected:
	BEGIN_MSG_MAP_EX(CCategories)
		MSG_OCM_CTLCOLORLISTBOX(OnCtlColorListbox)
	END_MSG_MAP()

	LRESULT OnCtlColorListbox (HDC hDC, HWND hWnd);
};

#endif // !defined(_CATEGORIES_H__B5AD952B_3EC0_401E_BEF9_EB906B780A29__INCLUDED_)
