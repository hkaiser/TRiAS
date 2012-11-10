// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.03.2001 20:22:13 
//
// @doc
// @module ProjectValuesStore.h | Declaration of the <c CProjectValueStore> class

#if !defined(_PROJECTVALUESSTORE_H__AA31566D_2E00_4E00_8B48_EF152566B42E__INCLUDED_)
#define _PROJECTVALUESSTORE_H__AA31566D_2E00_4E00_8B48_EF152566B42E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TreeCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CProjectValueStore window

class CProjectValueStore : public CSECTreeCtrlEx
{
// Construction
public:
	CProjectValueStore();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectValueStore)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProjectValueStore();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProjectValueStore)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PROJECTVALUESSTORE_H__AA31566D_2E00_4E00_8B48_EF152566B42E__INCLUDED_)
