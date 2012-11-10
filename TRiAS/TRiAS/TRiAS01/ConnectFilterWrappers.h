// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.12.2002 20:27:05 
//
// @doc
// @module ConnectFilterWrappers.h | Declaration of the <c CConnectFilterWrappers> class

#if !defined(_CONNECTFILTERWRAPPERS_H__1B8467A3_5E84_47CF_A27B_2BA1DA785F20__INCLUDED_)
#define _CONNECTFILTERWRAPPERS_H__1B8467A3_5E84_47CF_A27B_2BA1DA785F20__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <protos.h>
#include <NativeObject.h>

namespace trias_connectfilter {

///////////////////////////////////////////////////////////////////////////////
// Test, ob Objekt durch ConnectFilter gefiltert wird
inline 
BOOL ApplyConnectFilter (HPROJECT hPr, INT_PTR lONr)
{
#if defined(_USE_CONNECTFILTER)
CONNECTFILTEREX *pConnectFilter = NULL;

	if (SUCCEEDED(::GetConnectFilter(hPr, &pConnectFilter))) {
	trias_nativeobject::CNativeObject Obj(hPr, lONr);

		if (S_OK != Obj.ApplyConnectFilter("Geometry", pConnectFilter))
			return TRUE;		// dieses Objekt nicht nehmen
	}
#endif // defined(_USE_CONNECTFILTER)
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Version mit 2 Parametern
inline 
HRESULT EnumObjectsWrapper (
	HPROJECT hPr, INT_PTR lONr, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), 
	UINT_PTR dwData)
{
	if (ApplyConnectFilter(hPr, lONr))
		return S_OK;

	return pFcn (lONr, dwData);
}

///////////////////////////////////////////////////////////////////////////////
// Versionen mit 3 Parametern
inline 
HRESULT EnumObjectsWrapper (
	HPROJECT hPr, INT_PTR lONr, DWORD dwType,
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	if (ApplyConnectFilter(hPr, lONr))
		return S_OK;

	return pFcn (lONr, dwType, dwData);
}

inline 
HRESULT EnumObjectsWrapper (
	HPROJECT hPr, INT_PTR lONr, int iRelMask,
	HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData)
{
	if (ApplyConnectFilter(hPr, lONr))
		return S_OK;

	return pFcn (lONr, iRelMask, dwData);
}

}	// namespace trias_connectfilter

#endif // !defined(_CONNECTFILTERWRAPPERS_H__1B8467A3_5E84_47CF_A27B_2BA1DA785F20__INCLUDED_)
