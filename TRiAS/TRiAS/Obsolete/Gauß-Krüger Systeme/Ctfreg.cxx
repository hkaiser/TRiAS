// RegistryBehandlung ---------------------------------------------------------
// File: CTFREG.CXX

#include "besslgkp.hxx"

#include "besslres.h"

#include <string.h>
#include <tchar.h>

#include <dirisole.h>
#include <ctfpguid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" char g_pDLLName[260];
extern "C" HINSTANCE g_hInstance;

///////////////////////////////////////////////////////////////////////////////
// Help and other support -----------------------------------------------------

inline char *__ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
int badConversion = false;
  
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     NULL, &badConversion);

return buf;
}

inline char *ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
	return __ConvertStrWtoA (strIn, buf, size);
}

void WINAPI ExtFormatStrings (string& rString, LPCTSTR lpszFormat,
			      LPCTSTR *rglpsz, int nString)
{
// determine length of destination string
int nTotalLen = 0;
LPCTSTR pchSrc = lpszFormat;

	while (*pchSrc != '\0') {
		if (pchSrc[0] == '%' && (pchSrc[1] >= '1' && pchSrc[1] <= '9')) {
		int i = pchSrc[1] - '1';
		
			pchSrc += 2;
			if (i >= nString)
				++nTotalLen;
			else if (rglpsz[i] != NULL)
				nTotalLen += lstrlen(rglpsz[i]);
		} else {
			if (_istlead  (*pchSrc))
				++nTotalLen, ++pchSrc;
			++pchSrc;
			++nTotalLen;
		}
	}

	pchSrc = lpszFormat;
	rString.remove();

	while (*pchSrc != '\0')	{
		if (pchSrc[0] == '%' && (pchSrc[1] >= '1' && pchSrc[1] <= '9'))	{
		int i = pchSrc[1] - '1';
		
			pchSrc += 2;
			if (i >= nString) {
				TX_TRACE1("Error: illegal string index requested %d.\n", i);
				rString += '?';
			} else if (rglpsz[i] != NULL)
				rString += rglpsz[i];
		} else {
			if (_istlead(*pchSrc))
				rString += *pchSrc++; // copy first of 2 bytes
			rString += *pchSrc++;
		}
	}
}

inline bool _ExtRegDeleteKeySucceeded(LONG error)
{
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY) ||
		(error == ERROR_FILE_NOT_FOUND);
}

// Under Win32, a reg key may not be deleted unless it is empty.
// Thus, to delete a tree,  one must recursively enumerate and
// delete all of the sub-keys.
// Under Win16, RegDeleteKey does this for you.
LONG _ExtRecursiveRegDeleteKey(HKEY hParentKey, LPTSTR szKeyName)
{
DWORD   dwIndex = 0L;
TCHAR   szSubKeyName[256];
HKEY    hCurrentKey;
DWORD   dwResult;

	if ((dwResult = RegOpenKey(hParentKey, szKeyName, &hCurrentKey)) == ERROR_SUCCESS)
	{
	// remove all subkeys of the key to delete
		while ((dwResult = RegEnumKey(hCurrentKey, 0, szSubKeyName, 255)) == ERROR_SUCCESS)
		{
			OutputDebugString(szSubKeyName);
			OutputDebugString(TEXT("\r\n"));
			if ((dwResult = _ExtRecursiveRegDeleteKey(hCurrentKey, szSubKeyName)) != ERROR_SUCCESS)
				break;
		}

	// if all went well, we should now be able to delete the requested key
		if (dwResult == ERROR_NO_MORE_ITEMS)
			dwResult = RegDeleteKey(hParentKey, szKeyName);
	}

	RegCloseKey(hCurrentKey);
	return dwResult;
}

bool WINAPI ExtOleRegisterHelperEx (LPCTSTR FAR* rglpszRegister,
	LPCTSTR FAR* rglpszSymbols, int nSymbols, bool bReplace, HKEY hkey)
{
	TX_ASSERT(hkey != NULL);
	TX_ASSERT(rglpszRegister != NULL);
	TX_ASSERT(nSymbols == 0 || rglpszSymbols != NULL);

string strKey;
string strValue;

	while (*rglpszRegister != NULL) {
	LPCTSTR lpszKey = *rglpszRegister++;
	LPCTSTR lpszValue = lpszKey + _tcslen(lpszKey) + 1;

		ExtFormatStrings (strKey, lpszKey, rglpszSymbols, nSymbols);
		ExtFormatStrings (strValue, lpszValue, rglpszSymbols, nSymbols);

		if ((hkey == HKEY_CLASSES_ROOT) && strKey.length() == 0) {
			TX_TRACE1("Warning: skipping empty key '%Fs'\n", lpszKey);
			continue;
		}

		if (!bReplace) {
		TCHAR szBuffer[256];
		LONG lSize = sizeof(szBuffer)/sizeof(*szBuffer);
		
			if (::RegQueryValue(hkey, strKey.c_str(), szBuffer, &lSize) ==
				ERROR_SUCCESS)
			{
#ifdef _DEBUG
				if (strValue != szBuffer) {
					TX_TRACE3("Warning: Leaving value '%Fs' for key '%Fs' in registry\n\tintended value was '%Fs'\n",
						(LPCTSTR)szBuffer, (LPCTSTR)strKey.c_str(), (LPCTSTR)strValue.c_str());
				}
#endif
				continue;
			}
		}

		if (::RegSetValue(hkey, strKey.c_str(), REG_SZ, strValue.c_str(), 0)
			!= ERROR_SUCCESS)
		{
			TX_TRACE2("Error: failed setting key '%Fs' to value '%Fs'\n",
				(LPCTSTR)strKey.c_str(), (LPCTSTR)strValue.c_str());
			return false;
		}
	}

return true;
}

// Registriert diese Erweiterung als PropertySheetExt ----------------------
bool RegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, UINT uiName, 
			REFCLSID rTargetId, LPCTSTR pcTargetPropgID);

// DeRegistriert diese Erweiterung --------------------------------------------
bool UnRegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, 
			REFCLSID rTargetId, LPCTSTR pcTargetPropgID);

///////////////////////////////////////////////////////////////////////////////
// eigentliche Regirierung/DeRegistrierung
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
#if defined(ELLIPSE_BESSEL)
	if (fRegister) {
	// RegDB initialisieren
		return RegisterHandler (CLSID_CTFBesselGKProp, 
					TEXT("TRiASEx.CTFBesselGKExt.1"), IDS_LONGCLASSNAMEBE, 
				CLSID_DirisProject, TEXT("TRiAS.Document.2"));
	} else {
	// RegDB säubern
		return UnRegisterHandler (
				CLSID_CTFBesselGKProp, TEXT("TRiASEx.CTFBesselGKExt.1"), 
				CLSID_DirisProject, TEXT("TRiAS.Document.2"));
	}
#elif defined(ELLIPSE_KRASSOVSKY)
	if (fRegister) {
	// RegDB initialisieren
		return RegisterHandler (CLSID_CTFKrassGKProp, 
					TEXT("TRiASEx.CTFKrassovskyGKExt.1"), IDS_LONGCLASSNAMEKR, 
				CLSID_DirisProject, TEXT("TRiAS.Document.2"));
	} else {
	// RegDB säubern
		return UnRegisterHandler (
				CLSID_CTFKrassGKProp, TEXT("TRiASEx.CTFKrassovskyGKExt.1"), 
				CLSID_DirisProject, TEXT("TRiAS.Document.2"));
	}
#else
#error "No Ellipse defined."
#endif

return true;	// alles ok
}

///////////////////////////////////////////////////////////////////////////////
// Registrierung --------------------------------------------------------------

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

// PropSheetHandler:ProgID\...										FullName (%1)
//					ProgID\CLSID\...								{PropSheetHandler} (%2)
static LPCTSTR BASED_CODE rglpszExtProgID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("CLSID\0") TEXT("%2"),
	NULL,
};

// Coordinates:		HKCR\TRiAS.Application.2\PropertySheetHandlers\Coordinates\ProgID(PropSheet)...	{PropSheetHandler} (%1)
// Target:			ProgID\TRiASEx\PropertySheetHandlers\Coordinates ""
// HKCU				Software\uve\TRiAS\ProgID(Target)\PropertySheetHandlers\Coordinates ""
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
bool bSuccess = false;
string strTypeName (_MAX_PATH, default_size); 

	LoadString (g_hInstance, uiName, (char *)strTypeName.c_str(), _MAX_PATH);
	strTypeName.adjustlen();

//  Attempt to open registry keys.
HKEY hkeyClassID = NULL;
HKEY hkeyTargetID = NULL;
HKEY hkeyProgID = NULL;
HKEY hkeyCoordsCls = NULL;
TCHAR szKey[_MAX_PATH];

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto labelError;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, pcProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto labelError;
	wsprintf (szKey, TEXT("%s\\TRiASEx\\PropertySheetHandlers\\Coordinates"), pcTargetPropgID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyTargetID) != ERROR_SUCCESS)
		goto labelError;
	wsprintf (szKey, TEXT("TRiAS.Application.2\\TRiASEx\\PropertySheetHandlers\\Coordinates\\%s"), pcProgID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyCoordsCls) != ERROR_SUCCESS)
		goto labelError;

	TX_ASSERT (hkeyClassID != NULL);
	TX_ASSERT (hkeyProgID != NULL);
	TX_ASSERT (hkeyTargetID != NULL);
	TX_ASSERT (hkeyCoordsCls != NULL);

LPCTSTR rglpszSymbols[3];
TCHAR szPathName[_MAX_PATH];

	::GetModuleFileName (g_hInstance, szPathName, _MAX_PATH);

// ClassID generieren
	rglpszSymbols[0] = strTypeName.c_str();	// FullName
	rglpszSymbols[1] = pcProgID;			// ProgID
	rglpszSymbols[2] = szPathName;			// Path
	bSuccess = ExtOleRegisterHelperEx (rglpszClassID, rglpszSymbols, 
					   3, true, hkeyClassID);
	if (!bSuccess) goto labelError;

// ProgID generieren
	rglpszSymbols[0] = strTypeName.c_str();	// FullName
	rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
					   2, true, hkeyProgID);
	if (!bSuccess) goto labelError;
	
// am Target anhängen
	rglpszSymbols[0] = TEXT("");			// Alternativen für Koordinatensysteme
	bSuccess = ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
					   1, true, hkeyTargetID);
	if (!bSuccess) goto labelError;

// An Applcation werden Alternativen definiert
	rglpszSymbols[0] = szClassID;			// {xxxx...}
	bSuccess = ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
					   1, true, hkeyCoordsCls);
	if (!bSuccess) goto labelError;

	if (!IsWin32s()) {
	HKEY hkeyUser = NULL;

		wsprintf (szKey, TEXT("Software\\uve\\TRiAS\\%s\\PropertySheetHandlers\\Coordinates"), 
						 pcTargetPropgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) == ERROR_SUCCESS)
		{
			rglpszSymbols[0] = TEXT("");		// ""
			ExtOleRegisterHelperEx (rglpszTargetID, rglpszSymbols, 
								1, true, hkeyUser);
			if (hkeyUser != NULL) ::RegCloseKey(hkeyUser);
		}
	}

labelError:
	if (hkeyProgID != NULL)	::RegCloseKey(hkeyProgID);
	if (hkeyClassID != NULL) ::RegCloseKey(hkeyClassID);
	if (hkeyTargetID != NULL) ::RegCloseKey(hkeyTargetID);
	if (hkeyCoordsCls != NULL) ::RegCloseKey(hkeyCoordsCls);

return true;
}

// DeRegistriert diese Erweiterung --------------------------------------------
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
/*	if (bRetCode) {
		wsprintf (szKey, TEXT("%s\\TRiASEx\\PropertySheetHandlers\\%s"), pcTargetPropgID, pcProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
*/	if (bRetCode) {
		wsprintf (szKey, TEXT("TRiAS.Application.2\\TRiASEx\\PropertySheetHandlers\\Coordinates\\%s"), szClassID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}

/*	if (!IsWin32s() && bRetCode) {
		wsprintf (szKey, TEXT("Software\\uve\\TRiAS\\%s\\PropertySheetHandlers\\%s"), 
						 pcTargetPropgID, pcProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CURRENT_USER, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
*/
return bRetCode;
}
