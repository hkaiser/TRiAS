// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/06/1998 10:30:29 PM
//
// @doc
// @module UIUTIL.H | Allgemeine Makrodefinitionen et.al.

#if !defined(_UIUTIL_H__FECFEB47_5C7D_11D2_9ED7_006008447800__INCLUDED_)
#define _UIUTIL_H__FECFEB47_5C7D_11D2_9ED7_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Größe eines Arrays
#define _countof(x) (sizeof(x)/sizeof(x[0]))

///////////////////////////////////////////////////////////////////////////////
// Zerlegen eines Objektes/Arrays
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!x) {} else { delete(x); x = NULL; }
#endif // DELETE_OBJ

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(!x) {} else { delete[](x); x = NULL; }
#endif // DELETE_VEC

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) "): " desc)

///////////////////////////////////////////////////////////////////////////////
// Anzahl der Bytes für ein BSTR in einem Stream
inline 
ULONG LenForStream (const CComBSTR &bstr)
{
	return (bstr.m_str ? ::SysStringByteLen(bstr.m_str)+sizeof(OLECHAR) : 0) + sizeof(ULONG);
}

inline
HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

inline
HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

///////////////////////////////////////////////////////////////////////////////
// WindowsVersion
bool WINAPI IsWin31 (void);
bool WINAPI IsWin40 (void);
bool WINAPI IsWin41 (void);
bool WINAPI IsWin50 (void);
bool WINAPI IsWin32s (void);
bool WINAPI IsWinNT (void);

/////////////////////////////////////////////////////////////////////////////
// Helper für BSTR-Operationen
inline bool operator== (const CComBSTR &rl, const CComBSTR &rr) throw()
{
	return wcscmp(rl, rr) == 0 ? true : false;
}

inline bool operator< (const CComBSTR &rl, const CComBSTR &rr) throw()
{
	return wcscmp (rl, rr) < 0 ? true : false;
}

#endif // !defined(_UIUTIL_H__FECFEB47_5C7D_11D2_9ED7_006008447800__INCLUDED_)
