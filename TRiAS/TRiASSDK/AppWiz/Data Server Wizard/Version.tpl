// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.01.2000 16:03:19 
//
// @doc
// @module Version.tpl | Versionsinformationen

#if !defined(_VERSION_TPL__6AB68B8E_EF2D_4A3A_9A27_86FC19671396__INCLUDED_)
#define _VERSION_TPL__6AB68B8E_EF2D_4A3A_9A27_86FC19671396__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// VersionsInfo des DataServers
#define TRIASDBDS_VERSION	"@A"
#define TRIASDBDS_RELEASE	"@B"
#define TRIASDBDS_BUILD		"@C"

#define BUILD_DATE			"@D"
#define COMPANY_NAME        "@E"

#endif // !defined(_VERSION_TPL__6AB68B8E_EF2D_4A3A_9A27_86FC19671396__INCLUDED_)
