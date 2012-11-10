// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/16/1998 09:25:37 PM
//
// @doc
// @module ParamArray.h | SafeArray, welches die 4 beschreibenden BNA-Zeichenketten 
// eines Objektes enthält

#if !defined(_PARAMARRAY_H__F2ACEC52_4D87_11D2_9EC8_006008447800__INCLUDED_)
#define _PARAMARRAY_H__F2ACEC52_4D87_11D2_9EC8_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Array.h>

class CParamArray :
	public CSafeArray 
{
public:
	CParamArray (LPCSTR pcName1, LPCSTR pcName2, LPCSTR pcName3, LPCSTR pcName4)
		: CSafeArray(VT_BSTR, 4)
	{
	CSafeArrayLock<BSTR> lock (*this);

		lock[0] = CComBSTR(pcName1).Detach();
		lock[1] = CComBSTR(pcName2).Detach();
		lock[2] = CComBSTR(pcName3).Detach();
		lock[3] = CComBSTR(pcName4).Detach();
	}
	~CParamArray() {}
};

class CMCodeArray :
	public CSafeArray
{
public:
	CMCodeArray (ULONG lMCode1, ULONG lMCode2, ULONG lMCode3)
		: CSafeArray(VT_UI4, 3)
	{
	CSafeArrayLock<ULONG> lock (*this);

		lock[0] = lMCode1;
		lock[1] = lMCode2;
		lock[2] = lMCode3;
	}
	~CMCodeArray() {}
};

#endif // !defined(_PARAMARRAY_H__F2ACEC52_4D87_11D2_9EC8_006008447800__INCLUDED_)
