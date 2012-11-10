// RegDB mit spezifischen Einträgen initialisieren ----------------------------
// File: TRIASEXT.CXX
#include "bscriptp.hxx"

#include "triasext.h"		// Alle Header auf einen Blick

#define GUID_CCH	39	// Characters in string form of guid, including '\0'


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
// HKCU				Software\TRiAS\InterTRiAS\ProgID(Target)\PropertySheetHandlers\ProgID(PropSheet)\...	{PropSheet}
static LPCTSTR BASED_CODE rglpszTargetID[] =
{
	TEXT("\0") TEXT("%1"),
	NULL,
};


// Registriert diese Erweiterung als PropertySheetExt ----------------------
bool RegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, UINT uiName, 
					  REFCLSID rTargetId, LPCTSTR pcTargetPropgID)
{
// ClassID's als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
TCHAR szTargetCls[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

	cchGuid = ::StringFromGUID2 (rTargetId, oleszClassID, GUID_CCH);
	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szTargetCls, GUID_CCH);
#else
	strncpy (szTargetCls, oleszClassID, GUID_CCH);
	szTargetCls[GUID_CCH] = '\0';
#endif // WIN32

// ResourceString lesen
CString strTypeName; strTypeName.LoadString (uiName);
bool bSuccess = false;

//  Attempt to open registry keys.
HKEY hkeyClassID = NULL;
HKEY hkeyTargetID = NULL;
HKEY hkeyProgID = NULL;
TCHAR szKey[_MAX_PATH];
int cbShortName;

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto labelError;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, pcProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto labelError;
	wsprintf (szKey, TEXT("%s\\TRiASEx\\PropertySheetHandlers\\Customize\\%s"), pcTargetPropgID, pcProgID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyTargetID) != ERROR_SUCCESS)
		goto labelError;

	ASSERT (hkeyClassID != NULL);
	ASSERT (hkeyProgID != NULL);
	ASSERT (hkeyTargetID != NULL);

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
	
// am Target anhängen
	rglpszSymbols[0] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
					   1, true, hkeyTargetID);
	if (!bSuccess) goto labelError;

	if (!IsWin32s()) {
	HKEY hkeyUser = NULL;

		wsprintf (szKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\PropertySheetHandlers\\Customize\\%s"), 
						 pcTargetPropgID, pcProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) != ERROR_SUCCESS)
			goto labelError;

		rglpszSymbols[0] = szClassID;		// {PropSheet}
		ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
								1, true, hkeyUser);

		if (hkeyUser != NULL) ::RegCloseKey(hkeyUser);
	}

labelError:
	if (hkeyProgID != NULL)	::RegCloseKey(hkeyProgID);
	if (hkeyClassID != NULL) ::RegCloseKey(hkeyClassID);
	if (hkeyTargetID != NULL) ::RegCloseKey(hkeyTargetID);

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
// ClassID's als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
TCHAR szTargetCls[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

	cchGuid = ::StringFromGUID2 (rTargetId, oleszClassID, GUID_CCH);
	TX_ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szTargetCls, GUID_CCH);
#else
	strncpy (szTargetCls, oleszClassID, GUID_CCH);
	szTargetCls[GUID_CCH] = '\0';
#endif // WIN32

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
		wsprintf (szKey, TEXT("%s\\TRiASEx\\PropertySheetHandlers\\Customize\\%s"), pcTargetPropgID, pcProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}

	if (!IsWin32s() && bRetCode) {
		wsprintf (szKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\PropertySheetHandlers\\Customize\\%s"), 
						 pcTargetPropgID, pcProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CURRENT_USER, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
	return bRetCode;
}
