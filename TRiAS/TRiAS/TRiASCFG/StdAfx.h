// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.12.2000 18:42:18 
//
// @doc
// @module StdAfx.h | Include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#if !defined(AFX_STDAFX_H__B95FEC63_A210_4144_A42B_85D217B101E7__INCLUDED_)
#define AFX_STDAFX_H__B95FEC63_A210_4144_A42B_85D217B101E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TRiASCFGConfig.h"
#include <TRiASConfig.h>

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <atlbase.h>
#include <atlapp.h>

extern CComModule _Module;
#include <atlcom.h>

#include <AtlWin.h>
#include <AtlMisc.h>

#include <tstring>

#include <ospace/com/smartif.h>
#include <ospace/com/comerrormacros.h>
#include <com/errormacros2.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B95FEC63_A210_4144_A42B_85D217B101E7__INCLUDED_)
