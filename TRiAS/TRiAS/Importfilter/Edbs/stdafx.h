// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.08.2000 21:41:06 
//
// @doc
// @module Stdafx.h | Declaration of the <c CStdafx> class

#if !defined(_STDAFX_H__16E4765E_BC2F_4F94_84F4_59FE676B7A3E__INCLUDED_)
#define _STDAFX_H__16E4765E_BC2F_4F94_84F4_59FE676B7A3E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
#include "EdbsImpConfig.h"
#include <TRiASConfig.h>

#pragma warning (disable: 4237)

#include <afxctl.h>
#include <afxext.h>

#if defined(WIN16)
#include <ole16.h>
#endif	// WIN16

#include <tstring>

#include <ospace/com/ComErrorMacros.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <errcodes.hxx>		// FehlerCodes

//#include <triasm.hxx>
#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <xtsnimp.hxx>		// ImportInterface

#include "import.hpp"		// ImportInterface

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!x){}else{delete x; x = NULL;}
#endif	// DELETE

#if !defined(DELETE_VEC)
#define DELETE_VEC(x) if(!x){}else{delete [] x; x = NULL;}
#endif	// DELETE_VEC

#endif // !defined(_STDAFX_H__16E4765E_BC2F_4F94_84F4_59FE676B7A3E__INCLUDED_)
