// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.01.2001 17:02:18 
//
// @doc
// @module stdModel.h | Compiler dependend wrapper for stdModel

#if !defined(_STDMODEL_H__1665B8BC_11BA_47FF_8B60_4A8FE98E906C__INCLUDED_)
#define _STDMODEL_H__1665B8BC_11BA_47FF_8B60_4A8FE98E906C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(__ICL)
// Intel compiler
#include <SIUnits/Icl/stdModel.h>

#if defined(_DEBUG)
#pragma comment(lib, "libstdModelIcld.lib")
#else
#pragma comment(lib, "libstdModelIcl.lib")
#endif

#else
// original MSVC
#include <SIUnits/Msc/stdModel.h>

#if defined(_DEBUG)
#pragma comment(lib, "libstdModeld.lib")
#else
#pragma comment(lib, "libstdModel.lib")
#endif

#endif // defined(__ICL)

#endif // !defined(_STDMODEL_H__1665B8BC_11BA_47FF_8B60_4A8FE98E906C__INCLUDED_)
