// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.01.2001 17:02:18 
//
// @doc
// @module relModel.h | Compiler dependend wrapper for relModel

#if !defined(_RELMODEL_H__A71094A1_E17B_4996_A225_E44105AA0872__INCLUDED_)
#define _RELMODEL_H__A71094A1_E17B_4996_A225_E44105AA0872__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(__ICL)
#include <SIUnits/Icl/relModel.h>
#else
#include <SIUnits/Msc/relModel.h>
#endif // defined(__ICL)

#endif // !defined(_RELMODEL_H__A71094A1_E17B_4996_A225_E44105AA0872__INCLUDED_)
