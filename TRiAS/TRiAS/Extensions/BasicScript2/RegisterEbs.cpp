// RegisterEbs.cpp : Implementation of CRegisterEbs
#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <dirisole.h>

#include "macrguid.h"

#include "conststr.h"
#include "RegisterEbs.h"

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
#if _ATL_VER >= 0x0200
const wchar_t g_wcbZero[] = L"0";
const wchar_t g_wcbOne[] = L"1";
#else
const TCHAR g_cbZero[] = TEXT("0");
const TCHAR g_cbOne[] = TEXT("1");
#endif // _ATL_VER


/////////////////////////////////////////////////////////////////////////////
// CRegisterEbs

// Globale Zusatzmodule (rgFlags & EXTENSIONFLAGS_Global)
// ----------------------------------------------------------------------------
// Folgende Key's müssen in der Registry erzeugt werden:
// HKCU\Software\uve\TRiAS\Extensions\ProgId oder {ClsId}
//		"(Default)"="Name"		(Parameter von RegisterTRiASExtension)
// HKCU\Software\uve\TRiAS\Extensions\ProgId oder {ClsId}\CLSID
//		"(Default)"="{ClsID des zugehörigen Wrappers}"
// HKCU\Software\uve\TRiAS\Extensions\ProgId oder {ClsId}\UnRegister
//		"(Default)"="{ClsID des zugehörigen RegistrierObjektes}"
// HKCU\Software\uve\TRiAS\Extensions\ProgId oder {ClsId}\Config
//		"(Default)"="(value not set)"
//		"Visible"=dword:...		(entsprechend rgFlags&EXTENSIONFLAGS_Visible)
//		"UnLoadable"=dword:...	(entsprechend rgFlags&EXTENSIONFLAGS_UnLoadable)
//		"FileProgID"="Target"	(Parameter von RegisterTRiASExtension)
//		"NotPrimary"=dword:1	(immer setzen)
//		"ToolboxBitmap32"=dword:...	(optional - Wert: 0xc: Normal, 0xd: systeminternes Makro)
//
///////////////////////////////////////////////////////////////////////////////
// Zuordnungsdaten für Variablen in RegistryScript
#define REGMAP_PROGID		0
#define REGMAP_LONGNAME		1
#define REGMAP_VISIBLE		2
#define REGMAP_UNLOADABLE	3
#define REGMAP_TARGET		4
#define REGMAP_TOOLBOX		5
#define REGMAP_COMPANY		6
#define REGMAP_PRODUCT		7

static _ATL_REGMAP_ENTRY regEntryMap[] = 
{
#if _ATL_VER >= 0x0200
	{ L"PROGID", NULL },		// REGMAP_PROGID
	{ L"LONGNAME", NULL },		// REGMAP_LONGNAME
	{ L"VISIBLE", NULL },		// REGMAP_VISIBLE
	{ L"UNLOADABLE", NULL },	// REGMAP_UNLOADABLE
	{ L"TARGET", NULL },		// REGMAP_TARGET
	{ L"TOOLBOX", NULL },		// REGMAP_TOOLBOX
	{ L"COMPANY", NULL },		// REGMAP_COMPANY
	{ L"PRODUCT", NULL },		// REGMAP_PRODUCT
#else
	{ TEXT("PROGID"), NULL },	// REGMAP_PROGID
	{ TEXT("LONGNAME"), NULL },	// REGMAP_LONGNAME
	{ TEXT("VISIBLE"), NULL },	// REGMAP_VISIBLE
	{ TEXT("UNLOADABLE"), NULL },	// REGMAP_UNLOADABLE
	{ TEXT("TARGET"), NULL },	// REGMAP_TARGET
	{ TEXT("TOOLBOX"), NULL },	// REGMAP_TOOLBOX
#pragma message("COMPANY und PRODUCT Makros nachsetzen.")
#endif // _ATL_VER
	{ NULL, NULL },		// EndeKennung
};

// RegisterTRiASExtension wird grundsätzlich gerufen, wenn eine Erweiterung neu
// registriert werden soll, selbst, wenn es sich um eine projektbezogene
// Registrierung handelt.
STDMETHODIMP CRegisterEbs::RegisterTRiASExtension(
	BSTR bstrTarget, BSTR *pbstrName, BSTR *pbstrID, EXTENSIONFLAGS *prgFlags)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	TEST_E_POINTER("CRegisterEbs::RegisterTRiASExtension", prgFlags);

	HRESULT hr = NOERROR;
	LPOLESTR poleID = NULL;

	USES_CONVERSION;	
	try
	{
	// DateiName/StreamName ist Bezeichner für dieses Makro
		if (NULL != pbstrName) 
		{
			if (*pbstrName) ::SysFreeString (*pbstrName);	// [in, out]

			os_path target (OLE2A(bstrTarget));		
			CComBSTR bstrName (target.base().c_str());
			
			*pbstrName = bstrName.Detach();
			if (NULL == *pbstrName) _com_issue_error(E_OUTOFMEMORY);
		}

		if (!(*prgFlags & EXTENSIONFLAGS_Global)) 
		{// projektbezogene Erweiterungen hier nicht registrieren, RAUS
			if (NULL != pbstrID) 
			{
				if (*pbstrID) ::SysFreeString (*pbstrID);		// [in, out]
				*pbstrID = ::SysAllocString(L"TRiAS.BasicScriptWrapperExtension.1");
				if (NULL == *pbstrID) _com_issue_error(E_OUTOFMEMORY);
			}
			return S_OK;
		}

		// Einem BasicScript wird immer ein eigener GUID zugeordnet
		GUID guid;
		HRESULT hr = CoCreateGuid (&guid);
		if (FAILED(hr)) _com_issue_error(hr);
		// dieser GUID wird als IdentifikationsString verwendet
		hr = StringFromCLSID ((REFCLSID)guid, &poleID);
		if (FAILED(hr)) _com_issue_error(hr);
		// ID liefern
		if (NULL != pbstrID) 
		{
			if (*pbstrID) ::SysFreeString (*pbstrID);		// [in, out]
			// Allocierung *pbstrID und kopiert poleID nach *pbstrID
			*pbstrID = ::SysAllocString(poleID);
			if (NULL == *pbstrID) _com_issue_error(E_OUTOFMEMORY);
		}

	// jetzt die nötigen RegistryEintragungen vornehmen
	#if _ATL_VER >= 0x0200
	CComBSTR bstrCompany (REG_COMPANY_KEY);
	CComBSTR bstrProduct (REG_PRODUCT_KEY);

		regEntryMap[REGMAP_PROGID].szData = *pbstrID;
		regEntryMap[REGMAP_LONGNAME].szData = *pbstrName;
		regEntryMap[REGMAP_VISIBLE].szData = (*prgFlags & EXTENSIONFLAGS_Visible) ? g_wcbOne : g_wcbZero;
		regEntryMap[REGMAP_UNLOADABLE].szData = (*prgFlags & EXTENSIONFLAGS_UnLoadable) ? g_wcbOne : g_wcbZero;
		regEntryMap[REGMAP_TARGET].szData = bstrTarget;
		regEntryMap[REGMAP_TOOLBOX].szData = (*prgFlags & EXTENSIONFLAGS_Visible) ? L"12" : L"13";
		regEntryMap[REGMAP_COMPANY].szData = bstrCompany;
		regEntryMap[REGMAP_PRODUCT].szData = bstrProduct;
	#else
		regEntryMap[REGMAP_PROGID].szData = OLE2A(*pbstrID);
		regEntryMap[REGMAP_LONGNAME].szData = OLE2A(*pbstrName);
		regEntryMap[REGMAP_VISIBLE].szData = (*prgFlags & EXTENSIONFLAGS_Visible) ? g_cbOne : g_cbZero;
		regEntryMap[REGMAP_UNLOADABLE].szData = (*prgFlags & EXTENSIONFLAGS_UnLoadable) ? g_cbOne : g_cbZero;
		regEntryMap[REGMAP_TARGET].szData = OLE2A(bstrTarget);
		regEntryMap[REGMAP_TOOLBOX].szData = (*prgFlags & EXTENSIONFLAGS_Visible) ? TEXT("12") : TEXT("13");
	#endif // _ATL_VER

		hr = _Module.UpdateRegistryFromResource(IDR_REGISTERSCRIPT, true, regEntryMap);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e); 
	}
	if (NULL != poleID) CoTaskMemFree (poleID);
	return hr;
}

// Projektbezogene Zusatzmodule (!(rgFlags & EXTENSIONFLAGS_Global))
// ----------------------------------------------------------------------------
// Folgende Einträge müssen in der jeweiligen Projekt-INI erzeugt werden:
// [Parameters]
// NumExtensions32=Anzahl der Einträge unter [Extensions32] (increment/decrement)
// [Extensions32]
// ...
// Name=ProgId des zugehörigen Wrappers,1	;(Parameter von RegisterTRiASExtension)
// [Name]
// FileProgID=Target			;(Parameter von RegisterTRiASExtension)

// RegisterProjectExtension wird für projektbezogene Registrierungen gerufen
STDMETHODIMP CRegisterEbs::RegisterProjectExtension(
	long hPr, BSTR bstrName, BSTR bstrID, BSTR bstrTarget)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ASSERT(NULL != hPr);
	if (NULL == hPr) return E_INVALIDARG;
	
	USES_CONVERSION;

	os_path ini;
	HRESULT hr = GetActiveProjectIni (hPr, ini);
	if (FAILED(hr)) return hr;

// jetzt ini schreiben/aktualisieren
	int iCnt = GetPrivateProfileInt (g_cbParameters, g_cbNumExtensions32, 0, ini);
	char cbBuffer[32];

	LPCSTR pcName = OLE2A(bstrName);

	WritePrivateProfileString (g_cbParameters, g_cbNumExtensions32, ltoa (iCnt+1, cbBuffer, 10), ini);
	WritePrivateProfileString (g_cbExtensions32, pcName, "TRiAS.BasicScriptWrapperExtension.1,1", ini);
	WritePrivateProfileString (pcName, g_cbFileProgID, OLE2A(bstrTarget), ini);
	return S_OK;
}

STDMETHODIMP CRegisterEbs::UnRegisterTRiASExtension(
	BSTR bstrName, BSTR bstrID, long hPr)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	USES_CONVERSION;

	if (NULL == hPr) {
	// global entfernen, die entsprechenden RegistryEintragungen löschen
	#if _ATL_VER >= 0x0200
	CComBSTR bstrCompany (REG_COMPANY_KEY);
	CComBSTR bstrProduct (REG_PRODUCT_KEY);

		regEntryMap[REGMAP_PROGID].szData = bstrID;
		regEntryMap[REGMAP_LONGNAME].szData = bstrName;
		regEntryMap[REGMAP_VISIBLE].szData = g_wcbNil;
		regEntryMap[REGMAP_UNLOADABLE].szData = g_wcbNil;
		regEntryMap[REGMAP_TARGET].szData = g_wcbNil;
		regEntryMap[REGMAP_TOOLBOX].szData = g_wcbNil;
		regEntryMap[REGMAP_COMPANY].szData = bstrCompany;
		regEntryMap[REGMAP_PRODUCT].szData = bstrProduct;
	#else
		regEntryMap[REGMAP_PROGID].szData = OLE2A(bstrID);
		regEntryMap[REGMAP_LONGNAME].szData = OLE2A(bstrName);
		regEntryMap[REGMAP_VISIBLE].szData = g_cbNil;
		regEntryMap[REGMAP_UNLOADABLE].szData = g_cbNil;
		regEntryMap[REGMAP_TARGET].szData = g_cbNil;
		regEntryMap[REGMAP_TOOLBOX].szData = g_cbNil;
	#endif // _ATL_VER

		return _Module.UpdateRegistryFromResource(IDR_REGISTERSCRIPT, false, regEntryMap);
	} else {
	// projektbezogen entfernen
	os_path ini;
	HRESULT hr = GetActiveProjectIni (hPr, ini);

		if (FAILED(hr)) return hr;

	// jetzt in ini löschen/aktualisieren
	int iCnt = GetPrivateProfileInt (g_cbParameters, g_cbNumExtensions32, 0, ini);
	char cbBuffer[32];
	LPCSTR pcName = OLE2A(bstrName);

		ASSERT(iCnt > 0);
		WritePrivateProfileString (g_cbParameters, g_cbNumExtensions32, ltoa (iCnt-1, cbBuffer, 10), ini);
		WritePrivateProfileString (g_cbExtensions32, pcName, NULL, ini);
		WritePrivateProfileString (pcName, NULL, NULL, ini);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Besorgen der aktuellen ProjektIni
HRESULT CRegisterEbs::GetActiveProjectIni (long hPr, os_path &path)
{
	try {
	char cbBuffer[_MAX_PATH];

		if (NULL == DEX_GetActiveProject (cbBuffer))
			_com_issue_error(E_UNEXPECTED);
		
		path = os_string(cbBuffer);
		path.extension (g_cbINI);	// DateiExtension ist jetzt .ini
	
	} catch (_com_error &e) {
		return _COM_ERROR(e);
	} catch (...) {
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

