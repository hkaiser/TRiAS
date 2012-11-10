// RegDB mit spezifischen Einträgen initialisieren ----------------------------
// File: AUTOREG.CXX

#include "precomp.hxx"		// Alle Header auf einen Blick

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>
#include <shellapi.h>

#include "oleautor.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

static LPCTSTR BASED_CODE rglpszExtProgID[] =
{
	TEXT("CLSID\0") TEXT("%1"),
	NULL,
};

static LPCTSTR BASED_CODE rglpszClassID[] =
{
	TEXT("\0") TEXT("%1"),
#if defined(WIN32)
	TEXT("ProgID\0") TEXT("TRiAS.Application.2"),
	TEXT("LocalServer32\0") TEXT("%2 /Automation"),
#else
	TEXT("ProgID\0") TEXT("TRiAS.Application.1"),
	TEXT("LocalServer\0") TEXT("%2 /Automation"),
#endif
	TEXT("VersionIndependentProgID\0") TEXT("TRiAS.Application"),
	TEXT("DefaultIcon\0") TEXT("%2,1"),
	NULL,
};


// Registriert diese Erweiterung als OleAutomationServer ----------------------
bool RegisterAutomationServer (REFCLSID clsid)
{
// ClassID als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (clsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;
#if defined(WIN32) && !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

// ResourceString lesen
CString strTypeName; strTypeName.LoadString (IDS_LONGCLASSNAME);
bool bSuccess = false;

// ModuleHandle von TRiAS besorgen
#if !defined(WIN32)
HINSTANCE hTrias = GetModuleHandle ("TRIAS.EXE");
#else
HINSTANCE hTrias = GetModuleHandle ("TRIAS32.EXE");
#endif

//  Attempt to open registry keys.
HKEY hkeyClassID = NULL;
HKEY hkeyProgID = NULL;
HKEY hkeyProgID_V = NULL;
TCHAR szKey[_MAX_PATH];

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto labelError;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, TEXT("TRiAS.Application"), &hkeyProgID) != ERROR_SUCCESS)
		goto labelError;

#if defined(WIN32)
	if (::RegCreateKey (HKEY_CLASSES_ROOT, TEXT("TRiAS.Application.2"), &hkeyProgID_V) != ERROR_SUCCESS)
#else
	if (::RegCreateKey (HKEY_CLASSES_ROOT, TEXT("TRiAS.Application.1"), &hkeyProgID_V) != ERROR_SUCCESS)
#endif // WIN32
		goto labelError;

	ASSERT (hkeyClassID != NULL);
	ASSERT (hkeyProgID != NULL);
	ASSERT (hkeyProgID_V != NULL);

LPCTSTR rglpszSymbols[2];
TCHAR szPathName[_MAX_PATH];

	::GetModuleFileName (hTrias, szPathName, _MAX_PATH);

// ClassID generieren
	rglpszSymbols[0] = strTypeName;
	rglpszSymbols[1] = szPathName;
	bSuccess = ExtOleRegisterHelperEx (rglpszClassID, rglpszSymbols, 
					   2, true, hkeyClassID);
	if (!bSuccess) goto labelError;

// ProgID generieren
	rglpszSymbols[0] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
					   1, true, hkeyProgID);
	if (!bSuccess) goto labelError;
	
	bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
					   1, true, hkeyProgID_V);

labelError:
	if (hkeyProgID != NULL)	::RegCloseKey(hkeyProgID);
	if (hkeyProgID_V != NULL) ::RegCloseKey(hkeyProgID_V);
	if (hkeyClassID != NULL) ::RegCloseKey(hkeyClassID);

return true;
}


// DeRegistriert diese Erweiterung --------------------------------------------
#if defined(WIN32)
#define LOCALSERVER   TEXT("LocalServer32")
#define LOCALSERVER_2 TEXT("LocalServer")
#else
#define LOCALSERVER   TEXT("LocalServer")
#define LOCALSERVER_2 TEXT("LocalServer32")
#endif

inline bool _ExtRegDeleteKeySucceeded(LONG error)
{
#if defined(WIN32)
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY) ||
		(error == ERROR_FILE_NOT_FOUND);
#else
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY);
#endif
}

bool UnRegisterAutomationServer (REFCLSID clsid)
{
// Format class ID as a string
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2(clsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;
#if defined(WIN32) && !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

TCHAR szKey[_MAX_PATH];
long error;
bool bRetCode = true;
HKEY hkey;

// check to see if a 16-bit InprocServer key is found when unregistering
// 32-bit (or vice versa).
	wsprintf (szKey, TEXT("CLSID\\%s\\%s"), szClassID, LOCALSERVER_2);
	if (::RegOpenKey (HKEY_CLASSES_ROOT, szKey, &hkey) == ERROR_SUCCESS) {
	// Only remove the keys specific to this version of the extension,
	// leaving things in tact for the other version.
		wsprintf (szKey, TEXT("CLSID\\%s\\%s"), szClassID, LOCALSERVER);
		error = ::RegDeleteKey (HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	} else {
	// No other versions of this extension were detected,
	// so go ahead and remove the extension completely.
		wsprintf (szKey, TEXT("CLSID\\%s"), szClassID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}

return bRetCode;
}
