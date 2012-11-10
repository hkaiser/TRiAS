// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 11.04.2001 11:10:25 
//
// @doc
// @module Util.h | Declaration of of some helper functions

#if !defined(_UTIL_H__A7410C7A_49B6_403E_ABC0_A365B15EF0CA__INCLUDED_)
#define _UTIL_H__A7410C7A_49B6_403E_ABC0_A365B15EF0CA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// diverse Macros
#define _countof(x) (sizeof(x)/sizeof(x[0]))

///////////////////////////////////////////////////////////////////////////////
// FileHandling
bool TestFileRO (LPCSTR pcName, BOOL &rRO);

///////////////////////////////////////////////////////////////////////////////
// eine beliebige Resource laden
BYTE *ReadResource (int iResID, DWORD &dwResSize, HINSTANCE hInstance = NULL);

///////////////////////////////////////////////////////////////////////////////
// Helperklasse für Enumeratoren
template<typename T>
class _CopyVariantFromPtr :
	public _Copy<VARIANT>
{
public:
	static HRESULT copy(VARIANT* p1, T *p2) 
	{
	CComVariant v(*p2);

		return v.Detach(p1);
	}
};

#endif // !defined(_UTIL_H__A7410C7A_49B6_403E_ABC0_A365B15EF0CA__INCLUDED_)
