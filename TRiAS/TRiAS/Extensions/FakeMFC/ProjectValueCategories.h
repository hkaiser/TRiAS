// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.03.2001 20:22:26 
//
// @doc
// @module ProjectValueCategories.h | Declaration of the <c CProjectValueCategories> class

#if !defined(_PROJECTVALUECATEGORIES_H__6E40B9B2_5FC3_47D4_A10B_CDAF7568AD97__INCLUDED_)
#define _PROJECTVALUECATEGORIES_H__6E40B9B2_5FC3_47D4_A10B_CDAF7568AD97__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectValueCategories window

class CProjectValueCategories : public CComboBoxEx
{
// Construction
public:
	CProjectValueCategories();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectValueCategories)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProjectValueCategories();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProjectValueCategories)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PROJECTVALUECATEGORIES_H__6E40B9B2_5FC3_47D4_A10B_CDAF7568AD97__INCLUDED_)
