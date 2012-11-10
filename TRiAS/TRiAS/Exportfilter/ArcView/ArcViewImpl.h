// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 11:04:07 
//
// @doc
// @module ArcViewImpl.h | Implementation details

#if !defined(_ARCVIEWIMPL_H__3F1C38FD_7455_4F5C_ACE2_529A99464833__INCLUDED_)
#define _ARCVIEWIMPL_H__3F1C38FD_7455_4F5C_ACE2_529A99464833__INCLUDED_

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
#include "ArcView.h"

#include <Errcodes.hxx>	
#include <xtension.h>
#include <xtensnx.h>

#include <trias01m.hxx>
#include <versions.h>

#define _RISDB_NO_STRUCTS
#include <risdb.h>
#include <ristypes.hxx>

typedef char* pchar;	// Wird in ImpExp.hxx verwendet...
#include <ImpExp.hxx>

#include "../ExportInl.h"
#include "../ExportOEIface.h"

///////////////////////////////////////////////////////////////////////////////
// Größe eines Arrays
#define _countof(x) (sizeof(x)/sizeof(x[0]))

#pragma HDR_OFF()

#endif // !defined(_ARCVIEWIMPL_H__3F1C38FD_7455_4F5C_ACE2_529A99464833__INCLUDED_)
