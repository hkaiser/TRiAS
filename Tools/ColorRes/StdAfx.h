// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.2002 10:01:19 
//
// @doc
// @module StdAfx.h | include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#if !defined(_STDAFX_H__DC28AFFD_7479_46B7_B0B5_52C7350B3923__INCLUDED_)
#define _STDAFX_H__DC28AFFD_7479_46B7_B0B5_52C7350B3923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define OS_WIN_95
#define OS_ALTERNATIVE_STRING_NAMES
#define OS_MULTI_THREADED
#define OS_NO_STREAM_SUPPORT
#define OS_NO_ALLOCATORS
#define OS_STL_ASSERT

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#include <iostream>
#include <tstring>

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__DC28AFFD_7479_46B7_B0B5_52C7350B3923__INCLUDED_)
