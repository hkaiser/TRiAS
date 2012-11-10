// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:42:36 
//
// @doc
// @module MapInfoImpl.h | Declaration of the <c CMapInfoImpl> class

#if !defined(_MAPINFOIMPL_H__67DA8A1B_034E_4FF2_937E_C02608DE61D6__INCLUDED_)
#define _MAPINFOIMPL_H__67DA8A1B_034E_4FF2_937E_C02608DE61D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
#pragma HDR_ON()

#include "resource.h"
#include "../ExportStdResrc.h"
#include "MapInfo.h"

#include <Errcodes.hxx>	
#include <xtension.h>
#include <xtensnx.h>

#include <zprotos.h>
#include <ristypes.hxx>

typedef char* pchar;	// Wird in ImpExp.hxx verwendet...
#include <ImpExp.hxx>

#include "../ExportInl.h"
#include "../ExportOEIface.h"

///////////////////////////////////////////////////////////////////////////////
// Größe eines Arrays
#define _countof(x) (sizeof(x)/sizeof(x[0]))

#pragma HDR_OFF()

#endif // !defined(_MAPINFOIMPL_H__67DA8A1B_034E_4FF2_937E_C02608DE61D6__INCLUDED_)
