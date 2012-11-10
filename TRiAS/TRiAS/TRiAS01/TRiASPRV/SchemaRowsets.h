// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.06.2001 19:35:49 
//
// @doc
// @module SchemaRowsets.h | Declaration of the SchemaRowset classes

#if !defined(_SCHEMAROWSETS_H__E51481F2_D1F5_4CE6_9E98_CA6CF2AD3557__INCLUDED_)
#define _SCHEMAROWSETS_H__E51481F2_D1F5_4CE6_9E98_CA6CF2AD3557__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Schema Rowsets
#include "TRiASOleDBSessionTRSchemaRowset.h"
#include "TRiASOleDBSessionTISchemaRowset.h"
#include "TRiASOleDBSessionColSchemaRowset.h"
#include "TRiASOleDBSessionPTSchemaRowset.h"
#include "TRiASOleDBSessionStatistSchemaRowset.h"
#include "TRiASOleDBSessionIdxSchemaRowset.h"
#include "TRiASOleDBSessionPrimaryKeysSchemaRowset.h"

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
#include "TRiASOleDBSessionVRSchemaRowset.h"
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)

// OGC Schema Rowsets
#include "TRiASOleDBSessionSchemaOGISTables.h"
#include "TRiASOleDBSessionSchemaOGISGeoColumns.h"
#include "TRiASOleDBSessionSchemaSpatRef.h"

#endif // !defined(_SCHEMAROWSETS_H__E51481F2_D1F5_4CE6_9E98_CA6CF2AD3557__INCLUDED_)
