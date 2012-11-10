// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:34:24 
//
// @doc
// @module Version.tpl | Versionen dieses Modules

#if !defined(_VERSION_TPL__87B1F81C_CDF5_443D_A298_F73777FECA5C__INCLUDED_)
#define _VERSION_TPL__87B1F81C_CDF5_443D_A298_F73777FECA5C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define TRIASOLEDB_VERSION		"@A"
#define TRIASOLEDB_RELEASE		"@B"
#define TRIASOLEDB_BUILD		"@C"
#define TRIASOLEDB_COPYRIGHT	"@D"

#define TRIASOLEDB_VERSION_L	OLESTR("@A")
#define TRIASOLEDB_RELEASE_L	OLESTR("@B")
#define TRIASOLEDB_BUILD_L		OLESTR("@C")
#define TRIASOLEDB_COPYRIGHT_L	OLESTR("@D")

#endif // !defined(_VERSION_TPL__87B1F81C_CDF5_443D_A298_F73777FECA5C__INCLUDED_)
