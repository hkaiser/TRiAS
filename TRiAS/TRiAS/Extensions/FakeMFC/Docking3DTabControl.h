// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.03.2001 21:54:35 
//
// @doc
// @module Docking3DTabControl.h | Declaration of the <c CDocking3DTabControl> class

#if !defined(_DOCKING3DTABCONTROL_H__C1BDFDD4_847A_4ADC_87F6_BE2F0E896422__INCLUDED_)
#define _DOCKING3DTABCONTROL_H__C1BDFDD4_847A_4ADC_87F6_BE2F0E896422__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ot_dockingwindows.h>		// Objective Toolkit docking windows
#include <ot_tabwnd.h>				// Objective Toolkit tab windows

/////////////////////////////////////////////////////////////////////////////
// CDocking3DTabControl window

class CDocking3DTabControl : public SEC3DTabControl
{
    DECLARE_DYNCREATE(CDocking3DTabControl);
    
// Construction
public:
	CDocking3DTabControl();

// Attributes
public:

// Operations
public:
	void InitializeFonts(DWORD dwStyle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocking3DTabControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocking3DTabControl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocking3DTabControl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_DOCKING3DTABCONTROL_H__C1BDFDD4_847A_4ADC_87F6_BE2F0E896422__INCLUDED_)
