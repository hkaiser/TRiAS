// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.01.2001 17:02:18 
//
// @doc
// @module anyModel.h | Compiler dependend wrapper for anyModel.h

#if !defined(_ANYMODEL_H__17F3ADE3_0AE1_42A6_9511_D9BFEA66DF44__INCLUDED_)
#define _ANYMODEL_H__17F3ADE3_0AE1_42A6_9511_D9BFEA66DF44__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(__ICL)
#include <SIUnits/Icl/anyModel.h>
#else
#include <SIUnits/Msc/anyModel.h>
#endif // defined(__ICL)

#endif // !defined(_ANYMODEL_H__17F3ADE3_0AE1_42A6_9511_D9BFEA66DF44__INCLUDED_)
