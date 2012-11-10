// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.01.2001 17:02:18 
//
// @doc
// @module natModel.h | Compiler dependend wrapper for natModel

#if !defined(_NATMODEL_H__8092FF22_8790_4DC4_9B2B_721376FDE364__INCLUDED_)
#define _NATMODEL_H__8092FF22_8790_4DC4_9B2B_721376FDE364__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(__ICL)
#include <SIUnits/Icl/natModel.h>
#else
#include <SIUnits/Msc/natModel.h>
#endif // defined(__ICL)

#endif // !defined(_NATMODEL_H__8092FF22_8790_4DC4_9B2B_721376FDE364__INCLUDED_)
