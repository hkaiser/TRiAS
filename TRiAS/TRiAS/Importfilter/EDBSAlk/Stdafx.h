// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.09.2000 19:14:56 
//
// @doc
// @module Stdafx.h | Declaration of the <c CStdafx> class

#if !defined(_STDAFX_H__E851FC8D_B363_43B1_AC04_934ABA78567D__INCLUDED_)
#define _STDAFX_H__E851FC8D_B363_43B1_AC04_934ABA78567D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "EdbsAlkConfig.h"
#include <TRiASConfig.h>

#pragma warning ( disable : 4237 )

#if _TRiAS_VER < 0x300
#define TRiAS_REGKEY "Software\\uve\\TRiAS\\"
#else
#define TRiAS_REGKEY "Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\"
#endif

#include <afxctl.h>
#include <afxext.h>
#include <afxdb.h>
#include "bool.h"

#ifndef _WIN32
#include <ole16.h>
#endif	// WIN32

#include <tstring>
//#include <string.h>
//#include <string.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////
// richtige ATL Version verwenden

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define __ATL_11_USED__ or __ATL_20_USED__!"
#endif

extern CComModule _Module;
extern _ATL_OBJMAP_ENTRY *GetObjectMap (void);

#include <ospace/com/iterenum.h>

//#include <containr.hxx>
#include <errcodes.hxx>         // FehlerCodes

#include <triasm.hxx>
#include <xtension.h>
#include <ShlObj.h>
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <Ixtnext.hxx>

#include <xtencatl.hxx>
#include <xtsnaux.hxx>
#include <XtsnImpAtl.h>		// ImportInterface
#include "import.hpp"		// ImportInterface

#ifndef DELETE_OBJ
#define DELETE_OBJ(x) {	if (!x){}else{ delete(x); x = NULL; }}
#endif	// DELETE

#ifndef DELETE_VEC
#define DELETE_VEC(x) {	if (!x){}else{ delete [] x; x = NULL; }}
#endif	// DELETE_VEC

#endif // !defined(_STDAFX_H__E851FC8D_B363_43B1_AC04_934ABA78567D__INCLUDED_)
