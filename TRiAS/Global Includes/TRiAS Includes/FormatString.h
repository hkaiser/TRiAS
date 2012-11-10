// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/01/1998 09:10:47 AM
//
// @doc
// @module FormatString.h | Formatfunktion für 'string'

#if !defined(_FORMATSTRING_H__8EA74AE4_10AF_11D2_9E8D_006008447800__INCLUDED_)
#define _FORMATSTRING_H__8EA74AE4_10AF_11D2_9E8D_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <stdarg.h>

#if !defined(_TRIAS02_ENTRY)
#define _TRIAS02_ENTRY
#endif // !defined(_TRIAS02_ENTRY)

_TRIAS02_ENTRY void __cdecl Format (string& rStr, LPCTSTR lpszFormat, ...);
_TRIAS02_ENTRY void FormatV (string& rStr, LPCTSTR lpszFormat, va_list argList);
_TRIAS02_ENTRY void __cdecl Format (string& rStr, class ResID resFormat, ...);
_TRIAS02_ENTRY void FormatV (string& rStr, class ResID resFormat, va_list argList);

#endif // !defined(_FORMATSTRING_H__8EA74AE4_10AF_11D2_9E8D_006008447800__INCLUDED_)
