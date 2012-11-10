// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 20:04:06 
//
// @doc
// @module BSTRHelpers.h | Helfer für Behandlung von OLE-Strings

#if !defined(__BSTR_HELPERS_H_B209B6E0_B501_11d2_98E0_0060085FC1CE)
#define __BSTR_HELPERS_H_B209B6E0_B501_11d2_98E0_0060085FC1CE

#if _ATL_VER < 0x0700
inline bool operator< (const CComBSTR &r1, const CComBSTR &r2) 
{
	_ASSERTE (NULL != r1.m_str && NULL != r2.m_str); 
	return (wcscmp (r1.m_str, r2.m_str) < 0) ? true : false;
}
inline bool operator== (const CComBSTR &s1, const CComBSTR &s2) 
{
	_ASSERTE (NULL != s1.m_str && NULL != s2.m_str); 
	if (SysStringLen (s1.m_str) != SysStringLen (s2.m_str))
		return false;
	return wcscmp (s1.m_str, s2.m_str) == 0 ? true : false;
}
inline bool operator== (const CComBSTR &s1, LPCOLESTR s2) 
{
	_ASSERTE (NULL != s1.m_str && NULL != s2); 
	return (wcscmp (s1.m_str, s2) == 0) ? true : false;
}
#endif // _ATL_VER < 0x0700

inline bool operator< (const CComBSTR &s1, LPCOLESTR s2)
{
	_ASSERTE (NULL != s1.m_str && NULL != s2); 
	return (wcscmp (s1.m_str, s2) < 0) ? true : false;
}

inline bool operator< (LPCOLESTR s1, const CComBSTR &s2) 
{
	_ASSERTE (NULL != s1 && NULL != s2.m_str); 
	return (wcscmp (s1, s2.m_str) < 0) ? true : false;
}
inline bool operator== (LPCOLESTR s1, const CComBSTR &s2) 
{
	_ASSERTE (NULL != s1 && NULL != s2.m_str); 
	return (wcscmp (s1, s2.m_str) == 0) ? true : false;
}

//////////////////////////////////////////////////////////////////////
// bei get_ ... (BSTR*) muß alter Inhalt von CComBSTR vor dem Aufruf
// freigegeben werden (sonst wird's irgendwann knapp mit dem Speicher...)
//
//          CComBSTR    strFooValue;
//           ....
//          HRESULT hr = IFooObject->get_FooValue (CLEARED(strFooValue)); 

inline BSTR *CLEARED(CComBSTR &s) 
{
	if (NULL != s.m_str) 
		s.Empty();
	return &s;
}

#endif __BSTR_HELPERS_H_B209B6E0_B501_11d2_98E0_0060085FC1CE
