// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.01.2001 17:02:18 
//
// @doc
// @module hepModel.h | Compiler dependend wrapper for hepModel

#if !defined(_HEPMODEL_H__A344D3EE_23E5_447F_AEA2_A015992DC671__INCLUDED_)
#define _HEPMODEL_H__A344D3EE_23E5_447F_AEA2_A015992DC671__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(__ICL)
#include <SIUnits/Icl/hepModel.h>
#else
#include <SIUnits/Msc/hepModel.h>
#endif // defined(__ICL)

#endif // !defined(_HEPMODEL_H__A344D3EE_23E5_447F_AEA2_A015992DC671__INCLUDED_)
