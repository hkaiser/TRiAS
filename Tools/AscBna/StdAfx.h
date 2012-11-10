// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 18.10.2001 23:05:47 
//
// @doc
// @module StdAfx.h | Precompiled Header stuff

#if !defined(_STDAFX_H__D38252B8_2016_4DE7_9CBC_B467B28BFD12__INCLUDED_)
#define _STDAFX_H__D38252B8_2016_4DE7_9CBC_B467B28BFD12__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "AscBnaConfig.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <crtdbg.h>
#include <string.h>
#include <time.h>

#include <atlbase.h>
extern CComModule _Module;
#include <atlconv.h>
#include <atlcom.h>

#include <ospace/com/smartif.h>

#endif // !defined(_STDAFX_H__D38252B8_2016_4DE7_9CBC_B467B28BFD12__INCLUDED_)
