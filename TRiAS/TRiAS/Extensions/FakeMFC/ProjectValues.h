// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.03.2001 10:13:26 
//
// @doc
// @module ProjectValues.h | Declaration of the <c CProjectValues> class

#if !defined(_PROJECTVALUES_H__4DE8F705_CC72_4B63_AD90_F669E1DE0ED2__INCLUDED_)
#define _PROJECTVALUES_H__4DE8F705_CC72_4B63_AD90_F669E1DE0ED2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "fakemfc.h"

#include "ResizableDialog.h"
#include "ProjectValueStore.h"
#include "ProjectValueCategories.h"

/////////////////////////////////////////////////////////////////////////////
// CProjectValues dialog

class CProjectValues : public CResizableDialog
{
// Construction
public:
	CProjectValues(CWnd *pParent = NULL);   // standard constructor
	~CProjectValues();

// Dialog Data
	//{{AFX_DATA(CProjectValues)
	enum { IDD = IDD_PROJECTVALUES };
	CProjectValueStore	m_ValueStore;
	CProjectValueCategories	m_Categories;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectValues)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectValues)
	afx_msg void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PROJECTVALUES_H__4DE8F705_CC72_4B63_AD90_F669E1DE0ED2__INCLUDED_)
