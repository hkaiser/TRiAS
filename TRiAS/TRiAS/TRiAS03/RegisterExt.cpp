// RegisterExt.cpp : Implementation of CRegisterExt

#include "trias03p.hxx"

#include <Registry.hxx>
#include <CExtReg.hxx>
#include <dirisole.h>

#include "TRiASHelper.h"
#include "Strings.h"
#include "RegisterExt.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterExt

// Globale Zusatzmodule (rgFlags&EXTENSIONFLAGS_Global bzw. hPr==NULL)
// ----------------------------------------------------------------------------
// TRiAS Erweiterungen registrieren sich i.a. selbst

STDMETHODIMP CRegisterExt::RegisterTRiASExtension(
	BSTR bstrTarget, BSTR *pbstrName, BSTR *pbstrID, EXTENSIONFLAGS *prgFlags)
{
	USES_CONVERSION;
	TEST_E_POINTER("CRegisterExt::RegisterTRiASExtension", prgFlags);

// globale Erweiterung in Registry eintragen lassen
CVersionBind Ver;
string strPath (OLE2A(bstrTarget));
CExtReg Ext (Ver, strPath);

	if (!Ext.SupportsSelfRegister() || !Ext.Register()) 
		return SELFREG_E_CLASS;

	if (NULL != pbstrID) {
	// Versuchen, diese Erweiterung wiederzufinden, um zusätzliche
	// Info's herauszukriegen
	string strLongName;
	string strProgID;

		if (!FindExtNameFromDLLName (Ext.GetPath(), strLongName, strProgID))
			return E_UNEXPECTED;

	// Rückkehrwerte setzen
	CComBSTR bstrID (strProgID.c_str());

		if (NULL != *pbstrID) ::SysFreeString(*pbstrID);		// [in, out]
		*pbstrID = bstrID.Detach();
		if (NULL == *pbstrID) return E_OUTOFMEMORY;

	// Bezeichner (LongName) soll ebenfalls abgeliefert werden
		if (NULL != pbstrName) {
		CComBSTR bstrName (strLongName.c_str());

			if (NULL != *pbstrName) ::SysFreeString(*pbstrName);	// [in, out]
			*pbstrName = bstrName.Detach();
			if (NULL == *pbstrName) return E_OUTOFMEMORY;
		}
	}
	return S_OK;
}

// Projektbezogene Zusatzmodule (!rgFlags&EXTENSIONFLAGS_Global bzw. hPr!=NULL)
// ----------------------------------------------------------------------------
// Projektbezogene Erweiterungen sollten zusätzlich in der Registry eingetragen 
// sein, damit alle nötigen Info's verfügbar sind.
//
// Folgende Einträge müssen in der jeweiligen Projekt-INI erzeugt werden:
// [Parameters]
// NumExtensions32=Anzahl der Einträge unter [Extensions32] (increment/decrement)
// [Extensions32]
// Name=ProgId,1	;(Parameter von RegisterTRiASExtension)

STDMETHODIMP CRegisterExt::RegisterProjectExtension(
	long hPr, BSTR bstrName, BSTR bstrID, BSTR /*bstrTarget*/)
{
	USES_CONVERSION;

// projektbezogene Erweiterung in ProjektINI eintragen
	TX_ASSERT(NULL != hPr);

os_path ini;
HRESULT hr = GetActiveProjectIni (hPr, ini);

	if (FAILED(hr)) return hr;

// jetzt ini schreiben/aktualisieren
int iCnt = GetPrivateProfileInt (g_cbParameters, g_cbNumExtensions32, 0, ini);
char cbBuffer[32];
string strVal (OLE2A(bstrID));

	strVal += TEXT(",1");
	WritePrivateProfileString (g_cbParameters, g_cbNumExtensions32, ltoa (iCnt+1, cbBuffer, 10), ini);
	WritePrivateProfileString (g_cbExtensions32, OLE2A(bstrName), strVal.c_str(), ini);
	return S_OK;
}

STDMETHODIMP CRegisterExt::UnRegisterTRiASExtension(
	BSTR bstrName, BSTR bstrID, long hPr)
{
	USES_CONVERSION;

	if (NULL == hPr) {
	string strPath;

		if (!ServerFromProgID (OLE2A(bstrID), strPath))
			return E_UNEXPECTED;

	CVersionBind Ver;
	CExtReg Ext (Ver, strPath);

		if (!Ext.SupportsSelfRegister() || !Ext.Unregister()) 
			return SELFREG_E_CLASS;

	} else {
	// projektbezogen entfernen
	os_path ini;
	HRESULT hr = GetActiveProjectIni (hPr, ini);

		if (FAILED(hr)) return hr;

	// jetzt in ini löschen/aktualisieren
	int iCnt = GetPrivateProfileInt (g_cbParameters, g_cbNumExtensions32, 0, ini);
	char cbBuffer[32];

		TX_ASSERT(iCnt > 0);
		WritePrivateProfileString (g_cbParameters, g_cbNumExtensions32, ltoa (iCnt-1, cbBuffer, 10), ini);
		WritePrivateProfileString (g_cbExtensions32, OLE2A(bstrName), NULL, ini);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Besorgen der aktuellen ProjektIni
HRESULT CRegisterExt::GetActiveProjectIni (long /*hPr*/, os_path &path)
{
// #HK980109
// hPr: wird ignoriert, da DEX_GetActiveProject im IsTRiASDBBased-Mode das aktive
// Projekt liefert

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

///////////////////////////////////////////////////////////////////////////////
// Finden des Kurz-/Langbezeichners einer Erweiterung über den gegebenen 
// Dateinamen.
bool FindExtNameFromDLLName (/*[in]*/string strDLLPath, 
	/*[out]*/string &rStrExtName, /*[out]*/string &rStrProgID)
{
	rStrExtName = g_cbNil;
	rStrProgID = g_cbNil;

#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) return false;
#endif // ENABLE_WIN32S_CODE

HKEY hKey = NULL;
DWORD i = 0;
bool fFound = false;
char cbTriasKey[_MAX_PATH];
string strTriasKey;
string strLongName;

	if (ERROR_SUCCESS != RegOpenKey (HKEY_CURRENT_USER, g_cbExtensions, &hKey)) 
		return false;
	
	while (RegEnumKey (hKey, i++, cbTriasKey, _MAX_PATH) == ERROR_SUCCESS) {
		strTriasKey = cbTriasKey;
		strLongName = g_cbNil;

		if (CompareDLLName (strTriasKey, strDLLPath, strLongName)) {
			rStrProgID = strTriasKey;	// ProgID
			rStrExtName = strLongName;
			fFound = true;
			break;
		}
	}
	RegCloseKey (hKey);   // Close the key handle.
	return fFound;
}

bool CompareDLLName (
	/*[in]*/string strProgID, /*[in]*/string strDLLPath, 
	/*[out]*/string &rStrLongName)
{
char cbBuffer[_MAX_PATH];

// Langen Bezeichner besorgen (für alle Fälle)
	{
	CCurrentUser regClsName (g_cbExtensions);
	LONG dwLen = _MAX_PATH;

		if (!regClsName.isValid() || !regClsName.GetSZ (strProgID.c_str(), cbBuffer, dwLen))
			return false;
		rStrLongName = cbBuffer;
	}

// vollständiger ErweiterungsSchlüssel
string strExtKey (string(g_cbExtensions) + g_cbDel + strProgID);

// wenn der gefundene Eintrag einer SekundärErweiterung gehört, dann raus
	{
	string strKey (strExtKey + g_cbDel + g_cbConfig);
	CCurrentUser regCfg (strKey.c_str());
	DWORD dwData = 0L;

		if (regCfg.isValid() && regCfg.GetDWORD (g_cbNotPrimary, dwData) && 0 != dwData)
			return false;		// der nächste bitte
	}

// ClassID besorgen
	{
	CCurrentUser regClsId (strExtKey.c_str());
	LONG dwLen = _MAX_PATH;

		if (!regClsId.isValid() || !regClsId.GetSZ (g_cbClsId, cbBuffer, dwLen))
			return false;
	}

// InprocServer32 besorgen
	{
	string strCLSID (g_cbClsId);
	
		strCLSID +=  string(g_cbDel) + cbBuffer;

	CClassesRoot regClsId (KEY_READ, strCLSID.c_str());
	LONG lLen = _MAX_PATH;

		if (!regClsId.isValid() || !regClsId.GetSZ (g_cbInprocServer, cbBuffer, lLen))
			return false;
	}
	return (strDLLPath == cbBuffer);	// wenn der Pfad stimmt, haben wir's
}

///////////////////////////////////////////////////////////////////////////////
// DLLNamen vom ProgID besorgen
bool ServerFromProgID (LPCSTR pcProgID, string &rStr)
{
CClassesRoot reg (KEY_READ, pcProgID);
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (!reg.isValid() || !reg.GetSZ (g_cbClsId, cbBuffer, lLen))
		return false;

string strClsId (g_cbClsId);

	strClsId += string (g_cbDel) + cbBuffer;

CClassesRoot regCls (KEY_READ, strClsId.c_str());

	lLen = sizeof(cbBuffer);
	if (!regCls.isValid() || !regCls.GetSZ (g_cbInprocServer, cbBuffer, lLen))
		return false;

	rStr = cbBuffer;
	return true;
}

