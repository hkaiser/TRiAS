// $Header: $
// Copyright© 1999 TRiAS GmbH, All rights reserved
// Created: 07/01/1998 09:10:47 AM
//
// @doc
// @module FormatString.hxx

#if !defined(_FORMATSTRING_H__8EA74AE4_10AF_11D2_9E8D_006008447800__INCLUDED_)
#define _FORMATSTRING_H__8EA74AE4_10AF_11D2_9E8D_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



_GEOMETR_ENTRY void __cdecl Format (string& rStr, LPCTSTR lpszFormat, ...);
_GEOMETR_ENTRY void FormatV (string& rStr, LPCTSTR lpszFormat, va_list argList);

#endif // !defined(_FORMATSTRING_H__8EA74AE4_10AF_11D2_9E8D_006008447800__INCLUDED_)
