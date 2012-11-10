// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:34:24 
//
// @doc
// @module Version.tpl | Versionen dieses Modules

#if !defined(_VERSION_TPL__F8FD4A95_358B_4EEA_B22F_8CBA34D02A4C__INCLUDED_)
#define _VERSION_TPL__F8FD4A95_358B_4EEA_B22F_8CBA34D02A4C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define TRIASNATIVEDB_VERSION "@A"
#define TRIASNATIVEDB_RELEASE "@B"
#define TRIASNATIVEDB_BUILD	"@C"

#endif // !defined(_VERSION_TPL__F8FD4A95_358B_4EEA_B22F_8CBA34D02A4C__INCLUDED_)
