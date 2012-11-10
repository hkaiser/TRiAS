// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.02.2000 13:05:32
//
// @doc
// @module OleDocumentWrapper.cpp | Implementation of the <c COleDocumentWrapper> class

#include "stdafx.h"

#include "Strings.h"
#include "OleDocumentWrapper.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_OleDocumentWrapper, COleDocumentWrapper)

/////////////////////////////////////////////////////////////////////////////
// spezielle RegistryFunktion
static _ATL_REGMAP_ENTRY s_regEntryMap[] = 
{
	{ L"MAINMODULE", NULL },		// REM_MAINMODULE
	{ L"FAKETRIASNAME", NULL },		// REM_FAKETRIASNAME
	{ NULL, NULL },					// EndeKennung
};

HRESULT WINAPI COleDocumentWrapper::UpdateRegistry (BOOL bRegister)
{
HMODULE hTRiAS = GetModuleHandle (NULL);
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hTRiAS, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;
	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

	s_regEntryMap[0].szData = pszModule;
	s_regEntryMap[1].szData = A2OLE(g_cbTRiAS);
	return _Module.UpdateRegistryFromResource(IDR_OLEDOCUMENTWRAPPER, bRegister, s_regEntryMap);
}

/////////////////////////////////////////////////////////////////////////////
// COleDocumentWrapper
