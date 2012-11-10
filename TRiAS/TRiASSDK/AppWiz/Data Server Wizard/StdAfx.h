// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2000 22:44:52 
//
// @doc
// @module StdAfx.h | Declaration of the <c CStdAfx> class

#if !defined(AFX_STDAFX_H__1724BD40_E51D_11D2_9BD8_E6AA20524153__INCLUDED_)
#define AFX_STDAFX_H__1724BD40_E51D_11D2_9BD8_E6AA20524153__INCLUDED_

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#include "debug.h"			// For ASSERT, VERIFY, and TRACE
#include <customaw.h>		// Custom AppWizard interface

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1724BD40_E51D_11D2_9BD8_E6AA20524153__INCLUDED_)
