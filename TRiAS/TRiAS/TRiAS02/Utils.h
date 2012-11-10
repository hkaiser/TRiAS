///////////////////////////////////////////////////////////////////////////////
// @doc
// @module Utils.h | Diverse Hilfsfunktionen

#if !defined(_UTILS_H__5EA16686_5F37_11D1_B9E5_080036D63803__INCLUDED_)
#define _UTILS_H__5EA16686_5F37_11D1_B9E5_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTable in ein string
void __cdecl FormatMessage(string &rStr, UINT uiError, ...);
void ShowError (HRESULT hr, UINT resID, LPCTSTR pcRoutine = NULL);

string __cdecl FakeTRiASName (ResID resID, ...);
string __cdecl FakeTRiASName (LPCSTR pcTempl, ...);

#endif // !defined(_UTILS_H__5EA16686_5F37_11D1_B9E5_080036D63803__INCLUDED_)
