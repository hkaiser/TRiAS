// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.12.2000 18:44:33 
//
// @doc
// @module StatistUtil.cpp | Definition of the <c CStatistUtil> class

#include "StdAfx.h"
#include "StatistUtil.h"

HRESULT LoadString (IStream *pIStm, os_string &rStr)
{
long lCnt = 0;
HRESULT hr = pIStm -> Read (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

char cbBuffer[256];

	_ASSERTE(lCnt < sizeof(cbBuffer));
	hr = pIStm -> Read (cbBuffer, lCnt, NULL);
	if (FAILED(hr)) return hr;

	rStr = cbBuffer;
	return S_OK;
}

HRESULT SaveString (IStream *pIStm, os_string str)
{
long lCnt = str.size()+1;
HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (str.c_str(), lCnt, NULL);
}

DWORD GetSizeMax (os_string &rStr)
{
	return rStr.size() + sizeof(long) + 1;
}

