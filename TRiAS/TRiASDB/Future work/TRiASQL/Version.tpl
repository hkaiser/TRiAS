// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 09:48:28 
//
// @doc
// @module Version.h | DVersionen dieses Modules

#if !defined(_VERSION_TPL__E5891241_F7A6_4069_B9CE_EFB962CAD4DB__INCLUDED_)
#define _VERSION_TPL__E5891241_F7A6_4069_B9CE_EFB962CAD4DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define TRIASQL_VERSION "@A"
#define TRiASQL_RELEASE "@B"
#define TRiASQL_BUILD	"@C"

#endif // !defined(_VERSION_TPL__E5891241_F7A6_4069_B9CE_EFB962CAD4DB__INCLUDED_)
