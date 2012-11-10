// Verwaltung der RegDB-Einträge für eine Erweiterung -------------------------
// File: EXTREG.CXX

#include "fakemfcp.hxx"

#include <comcat.h>
#include <TrCatIds.h>
#undef IDS_ALLFILES
#include <resstrg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

HRESULT RegisterCLSIDInCategory (REFCLSID clsid, CATID catid);
HRESULT UnRegisterCLSIDInCategory (REFCLSID clsid, CATID catid);

// Help and other support -----------------------------------------------------
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
#if defined(WIN32)
			if (_istlead  (*pchSrc))
				++nTotalLen, ++pchSrc;
#endif // WIN32
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
#if defined(WIN32)
			if (_istlead(*pchSrc))
				rString += *pchSrc++; // copy first of 2 bytes
#endif
			rString += *pchSrc++;
		}
	}
}

inline bool _ExtRegDeleteKeySucceeded(LONG error)
{
#if defined(WIN32)
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY) ||
		(error == ERROR_FILE_NOT_FOUND);
#else
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY);
#endif
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

#if defined(WIN32)
	// hack for adding Apartment value under InprocServer32
		if (!strcmp (strKey.c_str(), TEXT("InprocServer32"))) {
		LPCTSTR pcValue = TEXT("Apartment");
		HKEY hSubKey = NULL;
		bool fReturn = true;

			if (::RegOpenKey (hkey, TEXT("InprocServer32"), &hSubKey) != ERROR_SUCCESS || 
				::RegSetValueEx (hSubKey, TEXT("ThreadingModel"), 0L, REG_SZ, 
					(BYTE * const)pcValue, (strlen(pcValue)+1)*sizeof(TCHAR)) != ERROR_SUCCESS)
			{
				TX_TRACE("Error: failed setting key 'ThreadingModel' to value 'InprocServer'\n");
				fReturn = false;
			}
			if (NULL != hSubKey)
				::RegCloseKey (hSubKey);
			if (!fReturn)
				return false;
		}
#endif // WIN32
	}

return true;
}


bool WINAPI ExtOleRegisterTypeLib (HINSTANCE hInstance, REFGUID tlid,
	LPCTSTR pszFileName, LPCTSTR pszHelpDir)
{
	USES_CONVERSION;

bool bSuccess = false;
string strPathName;
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hInstance, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPSTR pszModule;

	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? szModule : szModuleShort;
	strPathName = pszModule;

// If a filename wcified, replace final component of path with it.
	if (pszFileName != NULL)
	{
	int iBackslash = strPathName.rfind(TEXT('\\'));

		using namespace ::ospace;
		if (iBackslash != os_npos)
			strPathName = strPathName.erase (iBackslash+1);
		strPathName += pszFileName;
	}

LPTYPELIB ptlib = NULL;

	if (SUCCEEDED(LoadTypeLib ((OLECHAR *)A2OLE(strPathName.c_str()), &ptlib))) {
		TX_ASSERT_POINTER (ptlib, ITypeLib);

	LPTLIBATTR pAttr;
	GUID tlidActual = GUID_NULL;

		if (SUCCEEDED(ptlib->GetLibAttr(&pAttr)))
		{
			TX_ASSERT_POINTER(pAttr, TLIBATTR);
			tlidActual = pAttr->guid;
			ptlib->ReleaseTLibAttr(pAttr);
		}

	// Check that the guid of the loaded type library matches
	// the tlid parameter.
		TX_ASSERT(IsEqualGUID(tlid, tlidActual));

		if (IsEqualGUID(tlid, tlidActual)) {
			// Register the type library.
			if (SUCCEEDED(RegisterTypeLib(ptlib,
					(OLECHAR *)A2OLE(strPathName.c_str()), 
					(OLECHAR *)A2OLE(pszHelpDir))))
			{
				bSuccess = true;
			}
		}
		RELEASE (ptlib);
	}

return bSuccess;
}


#if defined(WIN32)
#define TYPELIBWIN   TEXT("win32")
#define TYPELIBWIN_2 TEXT("win16")
#else
#define TYPELIBWIN   TEXT("win16")
#define TYPELIBWIN_2 TEXT("win32")
#endif

bool WINAPI ExtOleUnregisterTypeLib (REFGUID tlid)
{
	USES_CONVERSION;

// Format typelib guid as a string
OLECHAR oleszTypeLibID[GUID_CCH];
TCHAR szTypeLibID[GUID_CCH];
int cchGuid = ::StringFromGUID2(tlid, oleszTypeLibID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;

	strncpy (szTypeLibID, OLE2A(oleszTypeLibID), GUID_CCH);
	szTypeLibID[GUID_CCH] = '\0';

TCHAR szKey[_MAX_PATH];

// check to see if a win16 key is found when unregistering win32 (or vice versa)
	wsprintf(szKey, TEXT("TYPELIB\\%s\\1.0\\0\\%s"), szTypeLibID, TYPELIBWIN_2);

HKEY hkey;
bool bSurgical = RegOpenKey(HKEY_CLASSES_ROOT, szKey, &hkey) == ERROR_SUCCESS;
LONG error;

	if (bSurgical) {
	// Only remove the keys specific to this version of the control,
	// leaving things in tact for the other version.
	// Note that a dangling HELPDIR key would be inevitable.
		wsprintf(szKey, TEXT("TypeLib\\%s\\1.0\\0\\%s"), szTypeLibID, TYPELIBWIN);
		error = RegDeleteKey(HKEY_CLASSES_ROOT, szKey);
	} else {
	// No other versions of this control were detected,
	// so go ahead and remove the control completely.
		wsprintf(szKey, TEXT("TYPELIB\\%s"), szTypeLibID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
	}

return _ExtRegDeleteKeySucceeded(error);
}

#if !defined(BASED_CODE)
#if defined(WIN32) && !defined(BASED_CODE)
#define BASED_CODE
#else
#define BASED_CODE CDECL __based(__segname("_CODE"))
#endif 
#endif // BASED_CODE

static LPCTSTR BASED_CODE rglpszExtProgID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("CLSID\0") TEXT("%2"),
	NULL
};

static LPCTSTR BASED_CODE rglpszExtClassID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("ProgID\0") TEXT("%2"),
#if defined(WIN32)
	TEXT("InprocServer32\0") TEXT("%3"),
	TEXT("Version32\0") TEXT("%4"),
#else
	TEXT("InprocServer\0") TEXT("%3"),
	TEXT("Version\0") TEXT("%4"),
#endif
	TEXT("TypeLib\0") TEXT("%5"),
	NULL
};

static LPCTSTR BASED_CODE rglpszExtClassIDwoTypeLib[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("ProgID\0") TEXT("%2"),
#if defined(WIN32)
	TEXT("InprocServer32\0") TEXT("%3"),
	TEXT("Version32\0") TEXT("%4"),
#else
	TEXT("InprocServer\0") TEXT("%3"),
	TEXT("Version\0") TEXT("%4"),
#endif
	NULL
};

bool WINAPI ExtOleRegisterExtensionClass(HINSTANCE hInstance,
	REFCLSID clsid, LPCTSTR pszProgID, UINT idTypeName, 
	WORD wVerMajor, WORD wVerMinor, int bFlags, GUID *ptlid)
{
	USES_CONVERSION;

// CATID's registrieren
	RegisterCLSIDInCategory (clsid, CATID_TRiASExtension);
	if (bFlags & EFCanImport)
		RegisterCLSIDInCategory (clsid, CATID_TRiASImportModule);

bool bSuccess = false;

// Format class ID as a string
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (clsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;

	strncpy (szClassID, OLE2A(oleszClassID), GUID_CCH);
	szClassID[GUID_CCH] = '\0';

// Format typelib guid as a string
TCHAR szTypeLibID[GUID_CCH];

	if (ptlid) {
	OLECHAR oleszTypeLibID[GUID_CCH];

		cchGuid = ::StringFromGUID2(*ptlid, oleszTypeLibID, GUID_CCH);
		TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
		if (cchGuid != GUID_CCH)
			return false;

		strncpy (szTypeLibID, OLE2A(oleszTypeLibID), GUID_CCH);
		szTypeLibID[GUID_CCH] = '\0';
	}

TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hInstance, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPSTR pszModule;

	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? (szModule) : (szModuleShort);

string strTypeName;
TCHAR cbBuffer[_MAX_PATH];

	if (::LoadString (hInstance, idTypeName, cbBuffer, _MAX_PATH))
		strTypeName = cbBuffer;
	else {
		ASSERT(false);			 // Name string not present in resources
		strTypeName = szClassID; // Use Class ID instead
	}

// Format version string as "major.minor"
TCHAR szVersion[_MAX_PATH];

	wsprintf (szVersion, TEXT("%d.%d"), wVerMajor, wVerMinor);

//  Attempt to open registry keys.
#if defined(WIN32)
HKEY hkeyTRiAS = NULL;
DWORD dwData = 0;
#endif
HKEY hkeyClassID = NULL;
HKEY hkeyProgID = NULL;
TCHAR szKey[_MAX_PATH];

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto Error;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, pszProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto Error;

	TX_ASSERT(hkeyClassID != NULL);
	TX_ASSERT(hkeyProgID != NULL);

LPCTSTR rglpszSymbols[5];

	rglpszSymbols[0] = strTypeName.c_str();		// long name

#if defined(WIN32)
TCHAR szTRiASKey[_MAX_PATH];

#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
	// \HKEY_CURRENT_USER\Software\TRiAS\InterTRiAS\Extensions\...
		wsprintf (szTRiASKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions") TEXT("\\%s"), pszProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szTRiASKey, &hkeyTRiAS) != ERROR_SUCCESS)
			goto Error;
		TX_ASSERT(hkeyTRiAS != NULL);

		rglpszSymbols[1] = szClassID;
		bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
						   2, true, hkeyTRiAS);
		if (!bSuccess) goto Error;

	// \HKEY_CURRENT_USER\Software\TRiAS\InterTRiAS\Extensions\ProgID\Config\...
		::RegCloseKey(hkeyTRiAS);
		hkeyTRiAS = NULL;
		strcat (szTRiASKey, TEXT("\\Config"));
		if (::RegCreateKey (HKEY_CURRENT_USER, szTRiASKey, &hkeyTRiAS) != ERROR_SUCCESS)
			goto Error;

		if (bFlags & EFPriorityLoad) {
			dwData = (bFlags & EFPriorityLoadMask) >> 12;
			if (0 == dwData)
				dwData = 1;		// for compatibility with old settings
		} else
			dwData = 0;

		if (dwData && ::RegSetValueEx (hkeyTRiAS, TEXT("PriorityLoad"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;
		dwData = bFlags & EFAggregate ? true : false;
		if (dwData && ::RegSetValueEx (hkeyTRiAS, TEXT("Aggregate"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;

		dwData = bFlags & EFPreLoad ? true : false;
		if (::RegSetValueEx (hkeyTRiAS, TEXT("PreLoad"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;
		dwData = bFlags & EFUnLoadable ? true : false;
		if (::RegSetValueEx (hkeyTRiAS, TEXT("UnLoadable"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;
		dwData = bFlags & EFVisible ? true : false;
		if (::RegSetValueEx (hkeyTRiAS, TEXT("Visible"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;
		dwData = bFlags & EFCanImport ? true : false;
		if (::RegSetValueEx (hkeyTRiAS, TEXT("CanImport"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;

	// #HK000923
		dwData = bFlags & EFDragDropTarget ? true : false;
		if (::RegSetValueEx (hkeyTRiAS, TEXT("DragDropTarget"), 0, REG_DWORD, 
			(CONST BYTE *)&dwData, sizeof(dwData)) != ERROR_SUCCESS)
			goto Error;
	}
#endif // WIN32
#if defined(_USE_WIN32S_CODE)
	else {
	// in TRiAS.INI registrieren, wenn Win32s oder WIN16
	// zuerst testen, ob diese Erweiterung bereits in der INI vertreten ist
#if defined(__CV__)
	ResString resFile (IDS_PROFILE, 20);	// StringResourcen aus TRiAS lesen
	ResString resParams (IDS_IRISPARS, 20);
	ResString resExts (IDS_EXTENSION, 20);
	ResString resNums (IDS_EXTNUMS, 20);
#else
// die folgenden Resourcen müssen aus der TRiAS.EXE gelesen werden
	HINSTANCE hTrias = GetModuleHandle (TRIAS_MODULENAME);

		AfxSetResourceHandle (hTrias);

	CString resFile; resFile.LoadString (IDS_PROFILE);	// StringResourcen aus TRiAS lesen
	CString resParams; resParams.LoadString (IDS_IRISPARS);
	CString resExts; resExts.LoadString (IDS_EXTENSION);
	CString resNums; resNums.LoadString (IDS_EXTNUMS);
	
//		AfxSetResourceHandle (g_hInstance);
#endif
	int iExtNums = GetPrivateProfileInt (resParams, resNums, 0, resFile);
	bool fExists = false;
	
		if (::GetPrivateProfileString (resExts, strTypeName.c_str(), 
					       TEXT("\0"), szKey, _MAX_PATH, resFile) > 0)
		{	// Erweiterung ist bereits registriert
			fExists = true;
		}
		
	// Erweiterung in INI ordnungsgemäß registrieren
	int iMode = ((bFlags & EFPreLoad) ? 1 : 0) +	// beim Start von TRiAS geladen 
		    ((bFlags & EFUnLoadable) ? 0 : 2) +	// nicht entladbar
		    ((bFlags & EFVisible) ? 0 : 4) +	// nicht in Dialogen sichtbar
		    ((bFlags & EFCanImport) ? 8 : 0) +	// kann Daten importieren
			((bFlags & EFPriorityLoad) ? 16 : 0);
	
		wsprintf (szKey, TEXT("%s,%d"), pszProgID, iMode);
		::WritePrivateProfileString (resExts, strTypeName.c_str(),
					     szKey, resFile);
		if (!fExists) {
		// Anzahl hochsetzen
			wsprintf (szKey, TEXT("%d"), ++iExtNums);
			::WritePrivateProfileString (resParams, resNums, szKey, resFile);
		}
	}
#endif // defined(_USE_WIN32S_CODE)

// \HKEY_CLASSES_ROOT\ProgID\...
	rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
	bSuccess = ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 
					   2, true, hkeyProgID);
	if (!bSuccess) goto Error;

// \HKEY_CLASSES_ROOT\CLSID\...
	rglpszSymbols[1] = pszProgID;
	rglpszSymbols[2] = pszModule;
	rglpszSymbols[3] = szVersion;
	rglpszSymbols[4] = szTypeLibID;

	if (ptlid) {
		bSuccess = ExtOleRegisterHelperEx (rglpszExtClassID, rglpszSymbols, 
						   5, true, hkeyClassID);
	} else {
		bSuccess = ExtOleRegisterHelperEx (rglpszExtClassIDwoTypeLib, 
						   rglpszSymbols, 
						   4, true, hkeyClassID);
	}
	if (!bSuccess) goto Error;

// Insertable/NotInsertable
	if (bFlags & EFInsertable) {
		bSuccess =
			(::RegSetValue(hkeyProgID, TEXT("Insertable"), REG_SZ, TEXT(""), 0) ==
				ERROR_SUCCESS) &&
			(::RegSetValue(hkeyClassID, TEXT("Insertable"), REG_SZ, TEXT(""), 0) ==
				ERROR_SUCCESS);
	} 
/*	else {
		bSuccess =
			(::RegSetValue(hkeyProgID, TEXT("NotInsertable"), REG_SZ, TEXT(""), 0) ==
				ERROR_SUCCESS) &&
			(::RegSetValue(hkeyClassID, TEXT("NotInsertable"), REG_SZ, TEXT(""), 0) ==
				ERROR_SUCCESS);
	}
*/
Error:
	if (hkeyProgID != NULL)
		::RegCloseKey(hkeyProgID);

	if (hkeyClassID != NULL)
		::RegCloseKey(hkeyClassID);

#if defined(WIN32)
	if (hkeyTRiAS != NULL)
		::RegCloseKey(hkeyTRiAS);
#endif

return bSuccess;
}

#if defined(WIN32)
#define INPROCSERVER	TEXT("InprocServer32")
#define INPROCSERVER_2	TEXT("InprocServer")
#define VERSION		TEXT("Version32")
#else
#define INPROCSERVER	TEXT("InprocServer")
#define INPROCSERVER_2	TEXT("InprocServer32")
#define VERSION		TEXT("Version")
#endif

bool WINAPI ExtOleUnregisterClass (REFCLSID clsid, LPCTSTR pszProgID)
{
	USES_CONVERSION;

// Format class ID as a string
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (clsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;

	strncpy (szClassID, OLE2A(oleszClassID), GUID_CCH);
	szClassID[GUID_CCH] = '\0';

TCHAR szKey[_MAX_PATH];
long error;
bool bRetCode = true;

// check to see if a 16-bit InprocServer key is found when unregistering
// 32-bit (or vice versa).
	wsprintf(szKey, TEXT("CLSID\\%s\\%s"), szClassID, INPROCSERVER_2);

HKEY hkey;
bool bSurgical = RegOpenKey (HKEY_CLASSES_ROOT, szKey, &hkey) == ERROR_SUCCESS;

	if (bSurgical)	{
	// Only remove the keys specific to this version of the extension,
	// leaving things in tact for the other version.
		wsprintf(szKey, TEXT("CLSID\\%s\\%s"), szClassID, INPROCSERVER);
		error = RegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);

		wsprintf(szKey, TEXT("CLSID\\%s\\%s"), szClassID, VERSION);
		error = RegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	} else {
	// No other versions of this extension were detected,
	// so go ahead and remove the extension completely.
		wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);

		if (pszProgID != NULL) {
			error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, (LPTSTR)pszProgID);
			bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
		}
	}

#if defined(WIN32)
// \HKEY_CURRENT_USER\Software\TRiAS\InterTRiAS\Extensions\...
#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
		if (!bSurgical) {
		// nur löschen, wenn keine andere Version dieser Erweiterung installiert ist
			wsprintf (szKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions") TEXT("\\%s"), pszProgID);
			error = _ExtRecursiveRegDeleteKey(HKEY_CURRENT_USER, (LPTSTR)szKey);
			bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);

		// wenn das die letzte Erweiterung war, dann ...\\Extensions auch noch löschen
		// wenn noch subkeys da sind, dann macht diese Funktion garnichts.
			RegDeleteKey (HKEY_CURRENT_USER, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions"));
		}
	} 
#endif
	
return bRetCode;
}


static LPCTSTR BASED_CODE rglpszClsClassID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("ProgID\0") TEXT("%2"),
#if defined(WIN32)
	TEXT("InprocServer32\0") TEXT("%3"),
#else
	TEXT("InprocServer\0") TEXT("%3"),
#endif
	NULL
};

bool WINAPI _ExtOleRegisterClass(HINSTANCE hInstance, REFCLSID clsid,
	LPCTSTR pszProgID, UINT idTypeName)
{
	USES_CONVERSION;

// Format class ID as a string
bool bSuccess = false;
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (clsid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;

	strncpy (szClassID, OLE2A(oleszClassID), GUID_CCH);
	szClassID[GUID_CCH] = '\0';

TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hInstance, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPSTR pszModule;

	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? (szModule) : (szModuleShort);

string strTypeName;
char cbBuffer[_MAX_PATH];

	if (!::LoadString (g_hInstance, idTypeName, cbBuffer, _MAX_PATH)) {
		TX_ASSERT(false);  	// Name string not present in resources
		strTypeName = szClassID; // Use Class ID instead
	} else
		strTypeName = cbBuffer;

// Attempt to open registry keys.
HKEY hkeyClassID = NULL;
HKEY hkeyProgID = NULL;
TCHAR szKey[_MAX_PATH];

	wsprintf(szKey, TEXT("CLSID\\%s"), szClassID);
	if (::RegCreateKey(HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto Error;
	if (::RegCreateKey(HKEY_CLASSES_ROOT, pszProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto Error;

	TX_ASSERT(hkeyClassID != NULL);
	TX_ASSERT(hkeyProgID != NULL);

LPCTSTR rglpszSymbols[3];

	rglpszSymbols[0] = strTypeName.c_str();
	rglpszSymbols[1] = szClassID;
	ExtOleRegisterHelperEx(rglpszExtProgID, rglpszSymbols, 2, true, hkeyProgID);

	rglpszSymbols[1] = pszProgID;
	rglpszSymbols[2] = pszModule;
	ExtOleRegisterHelperEx(rglpszClsClassID, rglpszSymbols, 3, true, hkeyClassID);

	bSuccess = true;

Error:
	if (hkeyProgID != NULL)
		::RegCloseKey(hkeyProgID);

	if (hkeyClassID != NULL)
		::RegCloseKey(hkeyClassID);

return bSuccess;
}


static LPCTSTR BASED_CODE rglpszImport[] =
{
	TEXT("Description") TEXT("\0") TEXT("%1"),
	TEXT("FileExtension") TEXT("\0") TEXT("%2"),
	NULL
};


bool WINAPI ExtOleRegisterImportClass (HINSTANCE hInstance, 
		REFIID riid, LPCTSTR pszProgID, UINT uiFormat, UINT uiExt)
{
	USES_CONVERSION;

bool bSuccess = false;

// Format class ID as a string
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (riid, oleszClassID, GUID_CCH);

	TX_ASSERT(cchGuid == GUID_CCH);	// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH)
		return false;

	strncpy (szClassID, OLE2A(oleszClassID), GUID_CCH);
	szClassID[GUID_CCH] = '\0';

TCHAR szKey[_MAX_PATH];
string strFormat, strExt;

	if (!::LoadString (hInstance, uiFormat, szKey, _MAX_PATH)) {
		TX_ASSERT(false);	// Name string not present in resources
		strFormat = szClassID;	// Use Class ID instead
	} else
		strFormat = szKey;

	if (!::LoadString (hInstance, uiExt, szKey, _MAX_PATH)) {
		TX_ASSERT(false);	// Name string not present in resources
		strExt = "*";		// alle Dateien anzeigen
	} else
		strExt = szKey;

HKEY hkeyProgID = NULL;
HKEY hkeyTRiAS = NULL;
LPCTSTR rglpszSymbols[2];

	rglpszSymbols[0] = strFormat.c_str();		// Description
	rglpszSymbols[1] = strExt.c_str();		// FileExtension

string strKey = pszProgID;

#if defined(WIN32)
#if defined(_USE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // defined(_USE_WIN32S_CODE)
	{
	// \HKEY_CURRENT_USER\Software\TRiAS\InterTRiAS\Extensions\...
		wsprintf (szKey, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions") 
				 TEXT("\\%s") TEXT("\\ImportFormat"), pszProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyTRiAS) != ERROR_SUCCESS)
			goto labelError;
		TX_ASSERT(hkeyTRiAS != NULL);

		if (::RegSetValueEx (hkeyTRiAS, TEXT("Description"), 0, REG_SZ, 
				     (CONST BYTE *)strFormat.c_str(), strFormat.length()+1) != ERROR_SUCCESS)
			goto labelError;
		if (::RegSetValueEx (hkeyTRiAS, TEXT("FileExtension"), 0, REG_SZ, 
				     (CONST BYTE *)strExt.c_str(), strExt.length()+1) != ERROR_SUCCESS)
			goto labelError;
	} 
#endif // WIN32
#if defined(_USE_WIN32S_CODE)
	else {
	// nur in Win31 und Win32s
		strKey += TEXT("\\ImportFormat");
		if (::RegCreateKey (HKEY_CLASSES_ROOT, strKey.c_str(), &hkeyProgID) != ERROR_SUCCESS)
			goto labelError;

		TX_ASSERT(hkeyProgID != NULL);

	// \HKEY_CLASSES_ROOT\ProgID\ImportFormat
		bSuccess = ExtOleRegisterHelperEx (rglpszImport, rglpszSymbols, 
						   2, true, hkeyProgID);
		if (!bSuccess) goto labelError;
	}
#endif // defined(_USE_WIN32S_CODE)

labelError:
	if (hkeyProgID != NULL)
		::RegCloseKey(hkeyProgID);

	if (hkeyTRiAS != NULL)
		::RegCloseKey(hkeyTRiAS);

return bSuccess;
}

///////////////////////////////////////////////////////////////////////////////
// CATID's registrieren
HRESULT RegisterCLSIDInCategory (REFCLSID clsid, CATID catid)
{
// Register your component categories information.
ICatRegister* pcr = NULL ;
HRESULT hr = S_OK ;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (SUCCEEDED(hr)) {
	// Register this category as being "implemented" by
	// the class.
	CATID rgcatid[1] ;

		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories (clsid, 1, rgcatid);
    }

	if (pcr != NULL) pcr->Release();
  
return hr;
}
 
HRESULT UnRegisterCLSIDInCategory (REFCLSID clsid, CATID catid)
{
ICatRegister* pcr = NULL ;
HRESULT hr = S_OK ;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (SUCCEEDED(hr)) {
	// Unregister this category as being "implemented" by
	// the class.
	CATID rgcatid[1] ;

		rgcatid[0] = catid;
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL) pcr->Release();
  
	return hr;
}

