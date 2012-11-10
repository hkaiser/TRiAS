// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 11:40:41 
//
// @doc
// @module StdAfx.h | include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#if !defined(_STDAFX_H__81FBE933_3930_41A8_9025_7AE13536B0A1__INCLUDED_)
#define _STDAFX_H__81FBE933_3930_41A8_9025_7AE13536B0A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CvrtCoordsConfig.h"
#include <TRiASConfig.h>

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <atlbase.h>
extern CComModule _Module;
#include <atlconv.h>
#include <atlcom.h>

#include <tstring>
#include <ospace/com/smartif.h>
#include <ospace/com/ComErrorMacros.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__81FBE933_3930_41A8_9025_7AE13536B0A1__INCLUDED_)
