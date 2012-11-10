// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.11.2000 11:40:17 
//
// @doc
// @module ExportImpl.cpp | Definition of the <c CExportImpl> class

#include "stdafx.h"
#include "ExportImpl.h"

#include <com/Errormacros2Impl.cpp>
#include <Com/PropertyActionBase.cpp>

#include <TrCatIDs.h>

HRESULT LoadEngines (map<CLSID, WTRiASExtDataEngine, less<CLSID> > &mapOfRegisteredEngines) 
{
CATID catIDs[1];

	catIDs[0] = CATID_TRiASExportModule;

WCatInformation	pCatInformation;
WEnumCLSID	pEnumCLSID;

	RETURN_FAILED_HRESULT(pCatInformation.CreateInstance (CLSID_CatSimpleCache));
	RETURN_FAILED_HRESULT(pCatInformation->EnumClassesOfCategories (1, catIDs, 0, NULL, pEnumCLSID.ppi()));

CATID clsid;
ULONG ulFetched;
long lCount = 0;

	for (pEnumCLSID->Reset(); S_OK == pEnumCLSID -> Next (1, &clsid, &ulFetched); ++lCount)
	{
	WTRiASExtDataEngine	pTRiASExtDataEngine;
	WPersistStreamInit pPersistStreamInit;

		if (FAILED(pTRiASExtDataEngine.CreateInstance(clsid)))
			continue;
		if (FAILED(pTRiASExtDataEngine -> QueryInterface (pPersistStreamInit.ppi())))
			continue;									// muß bereitgestellt werden
		mapOfRegisteredEngines.insert (clsid, pTRiASExtDataEngine);
	}
	return lCount > 0 ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// überprüfen, ob wenigstens eine Engine registriert ist
HRESULT TestExistsEngine() 
{
CATID catIDs[1];

	catIDs[0] = CATID_TRiASExportModule;

WCatInformation	pCatInformation;
WEnumCLSID pEnumCLSID;
	
	RETURN_FAILED_HRESULT(pCatInformation.CreateInstance (CLSID_CatSimpleCache));
	RETURN_FAILED_HRESULT(pCatInformation -> EnumClassesOfCategories (1, catIDs, 0, NULL, pEnumCLSID.ppi()));

CATID clsid;

	pEnumCLSID -> Reset(); 
	return pEnumCLSID -> Next (1, &clsid, NULL);
}

#include <registrx.hxx>

#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

#if _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Versionskontrolle
extern DWORD g_dwVer4;

///////////////////////////////////////////////////////////////////////////////
// Registrierung über eigene Seriennummer, die in Registry steht
const char g_cbRegVersion[]	= TEXT("SOFTWARE\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\3.0");
const char g_cbSerial[] = TEXT("Serial");

HRESULT IsLegalRegNumber (LPCSTR pcRegEntry);

BOOL GetLicenseKeyObsolete (LPWSTR pwKey, size_t iLen)
{
CLocalMachine regName (KEY_READ, g_cbRegVersion);
char cbRegEntry[65];
DWORD dwLen = sizeof(cbRegEntry);

	if (regName.GetSubSZ (g_cbSerial, cbRegEntry, dwLen) &&
		S_OK == IsLegalRegNumber (cbRegEntry)) 
	{
		if (NULL != pwKey)		// Key kopieren
			mbstowcs (pwKey, cbRegEntry, min((size_t)dwLen, iLen));
		return true;
	} 
	return false;
}

BOOL GetLicensedObsolete (void)
{
CLocalMachine regName (KEY_READ, g_cbRegVersion);
char cbRegEntry[65];
DWORD dwLen = sizeof(cbRegEntry);

	if (!regName.GetSubSZ (g_cbSerial, cbRegEntry, dwLen))
		return false;

	return S_OK == IsLegalRegNumber (cbRegEntry) ? true : false;	// lizensiert ??
}

BOOL SetLicensedObsolete (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
	if (S_OK != IsLegalRegNumber(lpNewKey))
		return false;

CLocalMachine regName (g_cbRegVersion, true);

	return regName.SetSubSZ (g_cbSerial, lpNewKey);
}
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// LizensierungsHelper für Classfactory
BOOL CVerifyExportLicense::VerifyLicenseKey(BSTR bstr) 
{
CComBSTR strKey;

	USES_CONVERSION;
	if ((GetLicenseKey(0, &strKey) && 0 == wcscmp (strKey, bstr)) || ::SetLicensed (OLE2A(bstr))) 
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CVerifyExportLicense::GetLicenseKey (DWORD, BSTR *pBstr) 
{
CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

	if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
		return FALSE;
		
	*pBstr = bstrKey.Detach(); 
	return TRUE;
}

BOOL CVerifyExportLicense::IsLicenseValid() 
{
	return g_fGlobalLic || ::GetLicensed(); 
}
