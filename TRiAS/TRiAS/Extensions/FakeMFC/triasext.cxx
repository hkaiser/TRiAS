// RegDB mit spezifischen Eintr�gen initialisieren ----------------------------
// File: TRIASEXT.CXX

#include "fakemfcp.hxx"		// Alle Header auf einen Blick

#include <dirisole.h>
#include <shellapi.h>

#include "fakemfc.h"

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// PropSheetHandler: CLSID\{PropSheetHandler}\...					FullName (%1)
//					 CLSID\{PropSheetHandler}\InprocServer32\...	Pfad (%3)
//					 CLSID\{PropSheetHandler}\ProgID\...			ProgID (%2)
static LPCTSTR BASED_CODE rglpszClassID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("ProgID\0") TEXT("%2"),
	TEXT("InprocServer32\0") TEXT("%3"),
	NULL,
};

// PropSheetHandler	ProgID\...										FullName (%1)
//					ProgID\CLSID\...								{PropSheetHandler} (%2)
static LPCTSTR BASED_CODE rglpszExtProgID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("CLSID\0") TEXT("%2"),
	NULL,
};

// Target			ProgID\TRiASEx\PropertySheetHandlers\ProgID(PropSheet)...	{PropSheetHandler} (%1)
// Target			CLSID\{Target}\TRiASEx\PropertySheetHandlers\{PropSheetHandler}\..	""
// HKCU				Software\fez\TRiAS\ProgID(Target)\PropertySheetHandlers\ProgID(PropSheet)\...	{PropSheet}
static LPCTSTR BASED_CODE rglpszTargetID[] =
{
	TEXT("\0") TEXT("%1"),
	NULL,
};


// Registriert diese Erweiterung als PropertySheetExt ----------------------
bool RegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, UINT uiName, 
					  REFCLSID rTargetId, LPCTSTR pcTargetPropgID)
{
	USES_CONVERSION;

// ClassID's als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
TCHAR szTargetCls[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

	strncpy (szClassID, OLE2A(oleszClassID), GUID_CCH);
	szClassID[GUID_CCH] = '\0';

	cchGuid = ::StringFromGUID2 (rTargetId, oleszClassID, GUID_CCH);
	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

	strncpy (szTargetCls, OLE2A(oleszClassID), GUID_CCH);
	szTargetCls[GUID_CCH] = '\0';

// ResourceString lesen
CString strTypeName; VERIFY(strTypeName.LoadString (uiName));
bool bSuccess = false;

//  Attempt to open registry keys.
HKEY hkeyClassID = NULL;
HKEY hkeyTargetID = NULL;
HKEY hkeyProgID = NULL;
HKEY hkeyTargetCls = NULL;
TCHAR szKey[_MAX_PATH];
int cbShortName;

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto labelError;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, pcProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto labelError;
	wsprintf (szKey, TEXT("%s\\TRiASEx\\PropertySheetHandlers\\%s"), pcTargetPropgID, pcProgID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyTargetID) != ERROR_SUCCESS)
		goto labelError;
	wsprintf (szKey, TEXT("CLSID\\%s\\TRiASEx\\PropertySheetHandlers\\%s"), szTargetCls, szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyTargetCls) != ERROR_SUCCESS)
		goto labelError;

	ASSERT (hkeyClassID != NULL);
	ASSERT (hkeyProgID != NULL);
	ASSERT (hkeyTargetID != NULL);
	ASSERT (hkeyTargetCls != NULL);

LPCTSTR rglpszSymbols[3];
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (g_hInstance, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
LPSTR pszModule;

	cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? (szModule) : (szModuleShort);

// ClassID generieren
	rglpszSymbols[0] = strTypeName;			// FullName
	rglpszSymbols[1] = pcProgID;			// ProgID
	rglpszSymbols[2] = pszModule;			// Path
	bSuccess = ExtOleRegisterHelperEx (rglpszClassID, rglpszSymbols, 
					   3, true, hkeyClassID);
	if (!bSuccess) goto labelError;

// ProgID generieren
	rglpszSymbols[0] = strTypeName;			// FullName
	rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
					   2, true, hkeyProgID);
	if (!bSuccess) goto labelError;
	
// am Target anh�ngen
	rglpszSymbols[0] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
					   1, true, hkeyTargetID);
	if (!bSuccess) goto labelError;

// CLSID des Targets
	rglpszSymbols[0] = TEXT("");			// ""
	bSuccess = ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
					   1, true, hkeyTargetCls);
	if (!bSuccess) goto labelError;

#if _TRiAS_VER < 0x0400
#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
	HKEY hkeyUser = NULL;

		wsprintf (szKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\PropertySheetHandlers\\%s"), 
						 pcTargetPropgID, pcProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) != ERROR_SUCCESS)
			goto labelError;

		rglpszSymbols[0] = szClassID;		// {PropSheet}
		ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
								1, true, hkeyUser);

		if (hkeyUser != NULL) ::RegCloseKey(hkeyUser);
	}
#endif // _TRiAS_VER < 0x0400

labelError:
	if (hkeyProgID != NULL)	::RegCloseKey(hkeyProgID);
	if (hkeyClassID != NULL) ::RegCloseKey(hkeyClassID);
	if (hkeyTargetID != NULL) ::RegCloseKey(hkeyTargetID);
	if (hkeyTargetCls != NULL) ::RegCloseKey(hkeyTargetCls);
	return true;
}


// DeRegistriert diese Erweiterung --------------------------------------------
inline bool _ExtRegDeleteKeySucceeded(LONG error)
{
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY) ||
		(error == ERROR_FILE_NOT_FOUND);
}

bool UnRegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, 
						REFCLSID rTargetId, LPCTSTR pcTargetPropgID)
{
	USES_CONVERSION;

// ClassID's als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
TCHAR szTargetCls[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

	strncpy (szClassID, OLE2A(oleszClassID), GUID_CCH);
	szClassID[GUID_CCH] = '\0';

	cchGuid = ::StringFromGUID2 (rTargetId, oleszClassID, GUID_CCH);
	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

	strncpy (szTargetCls, OLE2A(oleszClassID), GUID_CCH);
	szTargetCls[GUID_CCH] = '\0';

TCHAR szKey[_MAX_PATH];
long error;
bool bRetCode = true;

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
	bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);

	if (bRetCode) {
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, (LPTSTR)pcProgID);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
	if (bRetCode) {
		wsprintf (szKey, TEXT("%s\\TRiASEx\\PropertySheetHandlers\\%s"), pcTargetPropgID, pcProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
	if (bRetCode) {
		wsprintf (szKey, TEXT("CLSID\\%s\\TRiASEx\\PropertySheetHandlers\\%s"), szTargetCls, szClassID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}

#if _TRiAS_VER < 0x0400
#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s())
#endif // defined(_USE_WIN32S_CODE)
		if (bRetCode) {
			wsprintf (szKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\PropertySheetHandlers\\%s"), 
							 pcTargetPropgID, pcProgID);
			error = _ExtRecursiveRegDeleteKey(HKEY_CURRENT_USER, szKey);
			bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
		}
#endif // _TRiAS_VER < 0x0400

	return bRetCode;
}

