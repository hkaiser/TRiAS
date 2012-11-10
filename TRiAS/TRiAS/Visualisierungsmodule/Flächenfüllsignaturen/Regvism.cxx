// RegDB mit spezifischen Eintr‰gen initialisieren ----------------------------
// File: REGVISM.CXX

#include "stdafx.h"		// Alle Header auf einen Blick

#include <shellapi.h>
#include <AtlConv.h>

#include "fillmode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

#if defined(_ENABLE_WIN32S)
const char g_cbIniFile[] = TEXT("trias20.ini");
const char g_cbParams[] = TEXT("Parameters");
const char g_cbVisModules[] = TEXT("VisModules");
const char g_cbNumVisModules[] = TEXT("NumVisModules");
#endif // defined(_ENABLE_WIN32S)

const char g_cbNil[] = TEXT("\0");
const char g_cbClsID[] = TEXT("CLSID\\%s");
const char g_cbVMKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\VisModules\\%s");
const char g_cbVMCfgKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\VisModules\\%s\\Config");

// Help and other support -----------------------------------------------------
inline char *__ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
int badConversion = false;
  
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     NULL, &badConversion);

return buf;
}

char *ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
	return __ConvertStrWtoA (strIn, buf, size);
}

void WINAPI ExtFormatStrings (CString& rString, LPCTSTR lpszFormat,
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
#if defined(WIN32)
			if (_istlead  (*pchSrc))
				++nTotalLen, ++pchSrc;
#endif // WIN32
			++pchSrc;
			++nTotalLen;
		}
	}

	pchSrc = lpszFormat;
	rString.Empty();

	while (*pchSrc != '\0')	{
		if (pchSrc[0] == '%' && (pchSrc[1] >= '1' && pchSrc[1] <= '9'))	{
		int i = pchSrc[1] - '1';
		
			pchSrc += 2;
			if (i >= nString) {
				TRACE1("Error: illegal string index requested %d.\n", i);
				rString += '?';
			} else if (rglpsz[i] != NULL)
				rString += rglpsz[i];
		} else {
#if defined(WIN32)
			if (_istlead(*pchSrc))
				rString += *pchSrc++; // copy first of 2 bytes
#endif
			rString += *pchSrc++;
		}
	}
}

bool WINAPI ExtOleRegisterHelperEx (LPCTSTR FAR* rglpszRegister,
	LPCTSTR FAR* rglpszSymbols, int nSymbols, bool bReplace, HKEY hkey)
{
	ASSERT(hkey != NULL);
	ASSERT(rglpszRegister != NULL);
	ASSERT(nSymbols == 0 || rglpszSymbols != NULL);

CString strKey;
CString strValue;

	while (*rglpszRegister != NULL) {
	LPCTSTR lpszKey = *rglpszRegister++;
	LPCTSTR lpszValue = lpszKey + _tcslen(lpszKey) + 1;

		ExtFormatStrings (strKey, lpszKey, rglpszSymbols, nSymbols);
		ExtFormatStrings (strValue, lpszValue, rglpszSymbols, nSymbols);

		if ((hkey == HKEY_CLASSES_ROOT) && strKey.GetLength() == 0) {
			TRACE1("Warning: skipping empty key '%Fs'\n", lpszKey);
			continue;
		}

		if (!bReplace) {
		TCHAR szBuffer[256];
		LONG lSize = sizeof(szBuffer)/sizeof(*szBuffer);
		
			if (::RegQueryValue(hkey, strKey, szBuffer, &lSize) ==
				ERROR_SUCCESS)
			{
#ifdef _DEBUG
				if (strValue != szBuffer) {
					TRACE3("Warning: Leaving value '%Fs' for key '%Fs' in registry\n\tintended value was '%Fs'\n",
						(LPCTSTR)szBuffer, (LPCTSTR)strKey, (LPCTSTR)strValue);
				}
#endif
				continue;
			}
		}

		if (::RegSetValue(hkey, strKey, REG_SZ, strValue, 0)
			!= ERROR_SUCCESS)
		{
			TRACE2("Error: failed setting key '%Fs' to value '%Fs'\n",
				(LPCTSTR)strKey, (LPCTSTR)strValue);
			return false;
		}
	}

return true;
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


///////////////////////////////////////////////////////////////////////////////
// VisModule: CLSID\{VisModule}\...					FullName (%1)
//			  CLSID\{VisModule}\InprocServer32\...	Pfad (%3)
//			  CLSID\{VisModule}\ProgID\...			ProgID (%2)
static LPCTSTR BASED_CODE rglpszClassID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("ProgID\0") TEXT("%2"),
	TEXT("InprocServer32\0") TEXT("%3"),
	NULL,
};

// VisModule	ProgID\...							FullName (%1)
//				ProgID\CLSID\...					{VisModule} (%2)

// VisModule	Software\uve\TRiAS\VisModules\ProgID			FullName (%1)
// VisModule	Software\uve\TRiAS\VisModules\ProgID\CLSID		{VisModule} (%2)
// VisModule	Software\uve\TRiAS\VisModules\ProgID\Config		REG_DWORD:ObjTypes:0x..

static LPCTSTR BASED_CODE rglpszExtProgID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("CLSID\0") TEXT("%2"),
	NULL,
};


// Registriert diese Erweiterung als PropertySheetExt ----------------------
bool RegisterVisModule (REFCLSID rclsid, LPCTSTR pcProgID, 
						HINSTANCE hInstance, UINT uiName, DWORD dwObjTypes)
{
	USES_CONVERSION;

TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hInstance, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? A2OLE(szModule) : A2OLE(szModuleShort);

// ClassID's als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

// ResourceString lesen
bool bSuccess = false;
TCHAR szKey[_MAX_PATH];
CString strTypeName; 
	
	if (::LoadString (hInstance, uiName, szKey, sizeof(szKey)))
		strTypeName = szKey;
	else
		strTypeName = pcProgID;

//  Attempt to open registry keys.
HKEY hkeyClassID = NULL;
HKEY hkeyProgID = NULL;

	wsprintf(szKey, g_cbClsID, szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto labelError;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, pcProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto labelError;

	ASSERT (hkeyClassID != NULL);
	ASSERT (hkeyProgID != NULL);

LPCTSTR rglpszSymbols[3];

// ClassID generieren
	rglpszSymbols[0] = strTypeName;			// FullName
	rglpszSymbols[1] = pcProgID;			// ProgID
	rglpszSymbols[2] = OLE2A(pszModule);	// Path
	bSuccess = ExtOleRegisterHelperEx (rglpszClassID, rglpszSymbols, 
					   3, true, hkeyClassID);
	if (!bSuccess) goto labelError;

// ProgID generieren
	rglpszSymbols[0] = strTypeName;			// FullName
	rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
					   2, true, hkeyProgID);
	if (!bSuccess) goto labelError;

#if defined(_ENABLE_WIN32S)
	if (!IsWin32s()) 
#endif // defined(_ENABLE_WIN32S)
	{
	HKEY hkeyUser = NULL;

		wsprintf (szKey, g_cbVMKey, pcProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) != ERROR_SUCCESS)
			goto labelError;

		rglpszSymbols[0] = strTypeName;			// FullName
		rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
		ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
								2, true, hkeyUser);
		
		if (hkeyUser != NULL) ::RegCloseKey(hkeyUser);

	// zust‰ndig f¸r folgende ObjektTypen
		wsprintf (szKey, g_cbVMCfgKey, pcProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) != ERROR_SUCCESS)
			goto labelError;

		if (hkeyUser != NULL) {
			::RegSetValueEx (hkeyUser, TEXT("ObjTypes"), NULL, REG_DWORD, 
							 (const LPBYTE)&dwObjTypes, sizeof(DWORD));
			::RegCloseKey(hkeyUser);
		}
	}
#if defined(_ENABLE_WIN32S)
	else {
	// Vismodule sind weiterhin in INI eingetragen
	int iExtNums = GetPrivateProfileInt (g_cbParams, g_cbNumVisModules, 0, g_cbIniFile);
	bool fExists = false;
	
		if (::GetPrivateProfileString (g_cbVisModules, strTypeName, 
					       g_cbNil, szKey, _MAX_PATH, g_cbIniFile) > 0)
		{	// Erweiterung ist bereits registriert
			fExists = true;
		}
		
	// Erweiterung in INI ordnungsgem‰ﬂ registrieren
		wsprintf (szKey, TEXT("%s,%ld"), pcProgID, dwObjTypes);
		::WritePrivateProfileString (g_cbVisModules, strTypeName,
					     szKey, g_cbIniFile);
		if (!fExists) {
		// Anzahl hochsetzen
			wsprintf (szKey, TEXT("%d"), ++iExtNums);
			::WritePrivateProfileString (g_cbParams, g_cbNumVisModules, szKey, g_cbIniFile);
		}
	}
#endif // defined(_ENABLE_WIN32S)

labelError:
	if (hkeyProgID != NULL)	::RegCloseKey(hkeyProgID);
	if (hkeyClassID != NULL) ::RegCloseKey(hkeyClassID);
	return true;
}


// DeRegistriert diese Erweiterung --------------------------------------------
inline bool _ExtRegDeleteKeySucceeded(LONG error)
{
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY) ||
		(error == ERROR_FILE_NOT_FOUND);
}

bool UnRegisterVisModule (REFCLSID rclsid, LPCTSTR pcProgID)
{
// ClassID's als String generieren
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

TCHAR szKey[_MAX_PATH];
long error;
bool bRetCode = true;

	wsprintf(szKey, g_cbClsID, szClassID);
	error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
	bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);

	if (bRetCode) {
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, (LPTSTR)pcProgID);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}

#if defined(_ENABLE_WIN32S)
	if (!IsWin32s() && bRetCode) {
		wsprintf (szKey, g_cbVMKey, pcProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CURRENT_USER, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
#endif // defined(_ENABLE_WIN32S)
	
	return bRetCode;
}
