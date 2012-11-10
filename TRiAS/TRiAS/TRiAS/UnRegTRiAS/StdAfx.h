// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.12.2000 11:40:26 
//
// @doc
// @module StdAfx.h | Declaration of the <c CStdAfx> class

#if !defined(_STDAFX_H__7F456904_924F_432F_A286_4BBE82B7309A__INCLUDED_)
#define _STDAFX_H__7F456904_924F_432F_A286_4BBE82B7309A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "UnRegTRiASConfig.h"
#include <TRiASConfig.h>

#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <crtdbg.h>

#include <string.h>
#include <tstring>		// STDCPP
#include <protos.h>

#include <trias02m.hxx>
#include <trias03m.hxx>
#include <triasm.hxx>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#include <atl20.h>
extern CComModule _Module;		// Hauptmodule für ATL

#include <ospace/com/smartif.h>

#include <commonvu.hxx>
#include <containr.hxx>

#include <ristypes.hxx>
#include <errcodes.hxx>
#include <errinst.hxx>

#include <xtension.h>
#include <ixtensn.hxx>

#include "resource.h"

#endif // !defined(_STDAFX_H__7F456904_924F_432F_A286_4BBE82B7309A__INCLUDED_)
