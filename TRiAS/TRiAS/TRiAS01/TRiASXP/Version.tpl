// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 12.08.2001 17:48:05 
//
// @doc
// @module Version.tpl | Declaration of the <c CVersion> class

#if !defined(_VERSION_TPL__99EE5059_8092_474E_9A2F_9363BF2411A3__INCLUDED_)
#define _VERSION_TPL__99EE5059_8092_474E_9A2F_9363BF2411A3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define TRIASXP_VERSION		"@A"
#define TRIASXP_RELEASE		"@B"
#define TRIASXP_BUILD		"@C"
#define TRIASXP_COPYRIGHT	"@D"

#define TRIASXP_VERSION_L	OLESTR("@A")
#define TRIASXP_RELEASE_L	OLESTR("@B")
#define TRIASXP_BUILD_L		OLESTR("@C")
#define TRIASXP_COPYRIGHT_L	OLESTR("@D")

#endif // !defined(_VERSION_TPL__99EE5059_8092_474E_9A2F_9363BF2411A3__INCLUDED_)
