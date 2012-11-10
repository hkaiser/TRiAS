// @doc
// @module ExtendedDataConversion.cpp | Implementation of the <c CExtendedDataConversion> class

#include "stdafx.h"

#include <Array.h>
#include <ospace/com/ComErrorMacros.h>

#include "AlkBerlin.h"
#include "Diesel.h"
#include "ExtendedDataConversion.h"

/////////////////////////////////////////////////////////////////////////////
// Stringkonstanten
const TCHAR g_cbSetVarExpr[] = "$(setvar,Oks,%s)$(setvar,ObjName,%s)$(setvar,UIdent,%s)$(setvar,Name4,%s)";
const TCHAR g_cbSetMCodeExpr[] = "$(setvar,ObjNameMCode,%ld)$(setvar,UIdentMCode,%ld)$(setvar,Name4MCode,%ld)";

/////////////////////////////////////////////////////////////////////////////
// CExtendedDataConversion

STDMETHODIMP CExtendedDataConversion::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExtendedDataConversion,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CExtendedDataConversion::PreOutputHeader(SAFEARRAY *psaParams, BSTR * pbstrHeader, VARIANT_BOOL *pfOutput)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Variablen zur DIESEL-engine hinzufügen
char cbExprBuffer[_MAX_PATH];
char cbOutBuffer[_MAX_PATH];
CSafeArray sa (VT_UI4);

	if (!sa.Attach (psaParams, true))
		return E_UNEXPECTED;

	{
	CSafeArrayLock<ULONG> lock(sa);
	
		USES_CONVERSION;
		wsprintf(cbExprBuffer, g_cbSetMCodeExpr, lock[0], lock[1], lock[2]);
		if (0 != diesel (cbExprBuffer, cbOutBuffer))
			return E_UNEXPECTED;	// Fehler (?)!
	}

	*pfOutput = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CExtendedDataConversion::PostOutputHeader(BSTR * pbstrHeader)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// alle definierten Regeln abarbeiten
	return m_PostOutputHeaderRules.EvalRules (pbstrHeader);
}

STDMETHODIMP CExtendedDataConversion::PreOutputObjectStart(
	LONG lCnt, SAFEARRAY *psaParams, BSTR * pbstrStart, VARIANT_BOOL * pfOutput)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Variablen zur DIESEL-engine hinzufügen
char cbExprBuffer[_MAX_PATH];
char cbOutBuffer[_MAX_PATH];
CSafeArray sa (VT_BSTR);

	if (!sa.Attach (psaParams, true))
		return E_UNEXPECTED;

	{
	CSafeArrayLock<BSTR> lock(sa);
	
		USES_CONVERSION;
		wsprintf(cbExprBuffer, g_cbSetVarExpr, OLE2A(lock[0]), OLE2A(lock[1]), OLE2A(lock[2]), OLE2A(lock[3]));
		if (0 != diesel (cbExprBuffer, cbOutBuffer))
			return E_UNEXPECTED;	// Fehler (?)!
	}

	*pfOutput = VARIANT_TRUE;		// Objekt immer ausgeben
	return S_OK;
}

STDMETHODIMP CExtendedDataConversion::PostOutputObjectStart(LONG lCnt, BSTR *pbstrStart)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// alle definierten Regeln abarbeiten
	return m_PostObjectStartRules.EvalRules (pbstrStart);
}

STDMETHODIMP CExtendedDataConversion::PreOutputAttribute(LONG * plMCode, BSTR * pbstrAttribute, VARIANT_BOOL * pfOutput)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CExtendedDataConversion::PostOutputAttribute(LONG lMCode, BSTR * pbstrOutput)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CExtendedDataConversion::PreOutputTrailer(BSTR * pbstrTrailer, VARIANT_BOOL *pfOutput)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

//CComBSTR bstr ("; Kurz vor Ende\n");
//
//	bstr += *pbstrTrailer;
//
//	::SysFreeString (*pbstrTrailer);
//	*pbstrTrailer = bstr.Detach();
	*pfOutput = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CExtendedDataConversion::PostOutputTrailer(BSTR *pbstrTrailer)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

//CComBSTR bstr ("; Kurz nach Ende\n");
//
//	*pbstrTrailer = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CExtendedDataConversion::put_ConfigFile(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrCfg = newVal;
	return InitConfigData();
}

///////////////////////////////////////////////////////////////////////////////
// fertig initialisieren
HRESULT CExtendedDataConversion::InitConfigData()
{
// Configdaten lesen
	if (!m_bstrCfg || m_bstrCfg.Length() == 0)
		return E_UNEXPECTED;

// 1. in Tratir.ini unsere INI holen
	USES_CONVERSION;

char cbBuffer[_MAX_PATH];
DWORD dwLen = ::SearchPath (NULL, OLE2A(m_bstrCfg), NULL, sizeof(cbBuffer), cbBuffer, NULL);

	if (0 == dwLen)
		return S_FALSE;		// nichts gefunden, aber ok

char cbInString[_MAX_PATH];

	if (0 == ::GetPrivateProfileString ("Tratir.AlkBerlin.1", "ConversionRules", "", cbInString, sizeof(cbInString), cbBuffer))
		return S_FALSE;

	dwLen = ::SearchPath (NULL, cbInString, NULL, sizeof(cbBuffer), cbBuffer, NULL);
	if (0 == dwLen)
		return S_FALSE;		// nichts gefunden, aber ok

// jetzt Rules lesen und in unseren Listen wegspeichern
	RETURN_FAILED_HRESULT(m_PostOutputHeaderRules.InsertRules ("PostOutputHeader", cbBuffer));
	RETURN_FAILED_HRESULT(m_PostObjectStartRules.InsertRules ("PreOutputObjectStart", cbBuffer));
	
	return S_OK;
}

HRESULT CExtendedDataConversion::
CRulesList::InsertRules (LPCSTR pcSection, LPCSTR pcINI)
{
char cbInString[_MAX_PATH];
int iRules = ::GetPrivateProfileInt (pcSection, "NumRules", 0, pcINI);

	if (0 == iRules) return S_FALSE;	// keine Regeln gegeben

	for (int i = 1; i <= iRules; i++) {
	char cbRule[32];

		wsprintf (cbRule, "Rule%d", i);
		if (0 == ::GetPrivateProfileString (pcSection, cbRule, "", cbInString, sizeof(cbInString), pcINI))
			return S_FALSE;

		push_back (os_string(cbInString));
	}
	return S_OK;
}

HRESULT CExtendedDataConversion::
CRulesList::EvalRules (BSTR *pbstrOut)
{
CComBSTR bstrOut ("");

	for (CRulesList::iterator it = begin(); it != end(); it++) {
	char cbBuffer[_MAX_PATH];

		if (0 == diesel ((LPSTR)(*it).c_str(), cbBuffer) && strlen(cbBuffer) > 0) 
			bstrOut += CComBSTR(cbBuffer);
	}

	*pbstrOut = bstrOut.Detach();
	return S_OK;
}
