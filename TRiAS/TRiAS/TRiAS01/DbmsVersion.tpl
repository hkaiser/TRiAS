// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 26.06.2001 20:55:28 
//
// @doc
// @module DbmsVersion.h | Declaration of the DbmsVersion constants

#if !defined(_DBMSVERSION_H__88222B40_39B2_4168_A0CA_FAC8E6B1D6EB__INCLUDED_)
#define _DBMSVERSION_H__88222B40_39B2_4168_A0CA_FAC8E6B1D6EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define TRIASDBMS_VERSION_STR	"@A"
#define TRIASDBMS_RELEASE_STR	"@B"
#define TRIASDBMS_BUILD_STR		"@C"

#define TRIASDBMS_VERSION	@A
#define TRIASDBMS_RELEASE	@B
#define TRIASDBMS_BUILD		@C

#endif // !defined(_DBMSVERSION_H__88222B40_39B2_4168_A0CA_FAC8E6B1D6EB__INCLUDED_)
