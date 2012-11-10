// @doc 
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__9CFAB4CD_B36F_11D2_95A5_006008447800__INCLUDED_)
#define _STRINGS_H__9CFAB4CD_B36F_11D2_95A5_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

extern const char s_cbVisModules[];		// TEXT("Software\\TRiAS\\InterTRiAS\\VisModules");
extern const char g_cbSysProperty[];	// TEXT("Property %ld");

extern const char g_cbDefaultVisInfo[];	// TEXT("__DefaultVisInfo__");

// aktueller TRiAS-Name
extern char g_cbTRiAS[];

extern const char g_cbCopyrightName[];	// TEXT("TRiAS");
extern const char g_cbTRiASName[];		// TEXT("TRiASName");
extern const char g_cbRegConfig[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Config");

#endif // !defined(_STRINGS_H__9CFAB4CD_B36F_11D2_95A5_006008447800__INCLUDED_)
