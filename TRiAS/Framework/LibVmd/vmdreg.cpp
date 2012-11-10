#include	"stdafx.h"

#include <vinfomfc.h>
#include "vismod.h"
#ifdef WIN32
#include <winnls.h>
#include <winreg.h>
#endif
// #include <shellapi.h>

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: vmdreg.cpp 1.2 1996/08/14 12:43:00 andy Exp andy $";
/* $Log: vmdreg.cpp $
// Revision 1.2  1996/08/14  12:43:00  andy
// initial version
//
// Revision 1.1  1996/07/12  17:30:39  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

#ifdef WIN32
static LPCTSTR g_cbIniFile			= TEXT("trias20.ini");
#else
static LPCTSTR g_cbIniFile			= TEXT("trias13.ini");
#endif

#ifdef WIN32
#define IsWin32s	((GetVersion() & ~0x80000000) && LOBYTE(LOWORD(GetVersion()))<4)
#endif

static LPCTSTR g_cbParams			= TEXT("Parameters");
static LPCTSTR g_cbVisModules		= TEXT("VisModules");
static LPCTSTR g_cbNumVisModules	= TEXT("NumVisModules");

static LPCTSTR g_cbNil		= TEXT("\0");
static LPCTSTR g_cbClsID	= TEXT("CLSID\\%s");

//static LPCTSTR g_cbVMKey	= TEXT("Software\\TRiAS\\InterTRiAS\\VisModules\\%s");
//static LPCTSTR g_cbVMCfgKey	= TEXT("Software\\TRiAS\\InterTRiAS\\VisModules\\%s\\Config");
static LPCTSTR g_cbVMKey	= TEXT("Software\\%s\\%s\\VisModules\\%s");
static LPCTSTR g_cbVMCfgKey	= TEXT("Software\\%s\\%s\\VisModules\\%s\\Config");

#ifndef WIN32
typedef const char* LPCWSTR;
#endif

int CTriasVMD::GetRegistryValue( LPCTSTR lpszKeyValue, COleVariant& val )
{


	CString	strKey;
//	strKey.Format( g_cbVMCfgKey, GetProgIdent() );
	strKey.Format( g_cbVMCfgKey, REG_COMPANY_KEY,REG_PRODUCT_KEY,GetProgIdent() );

	val.Clear();
	HKEY	hKey;
	DWORD	dwType;
	if( ERROR_SUCCESS == ::RegOpenKeyEx( HKEY_CURRENT_USER, strKey, 0L, KEY_READ, &hKey ) )
	{
		TCHAR	szBuffer[256];
		ULONG	lSize = sizeof( szBuffer ) / sizeof( *szBuffer );
		if( ERROR_SUCCESS == ::RegQueryValueEx( hKey, lpszKeyValue, 0L, &dwType, (BYTE*) szBuffer, &lSize ) )
		{
			switch( dwType )
			{
			case REG_DWORD :
				val = *(long*) szBuffer;
				break;
			case REG_SZ :
				val = (LPCTSTR) szBuffer;
				break;
			default :
				dwType = REG_NONE;
			}
		}
		else
			dwType = REG_NONE;
		::RegCloseKey( hKey );
	}
	return dwType;
}

// Help and other support -----------------------------------------------------
char *ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
#ifdef WIN32
	int badConversion = FALSE;
    WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, NULL, &badConversion);
#else
	strncpy( buf, (LPCTSTR) strIn, size );
#endif
	return buf;
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

BOOL WINAPI ExtOleRegisterHelperEx (LPCTSTR FAR* rglpszRegister,
	LPCTSTR FAR* rglpszSymbols, int nSymbols, BOOL bReplace, HKEY hkey)
{
	ASSERT(hkey != NULL);
	ASSERT(rglpszRegister != NULL);
	ASSERT(nSymbols == 0 || rglpszSymbols != NULL);

	CString strKey;
	CString strValue;

	while (*rglpszRegister != NULL)
	{
		LPCTSTR lpszKey = *rglpszRegister++;
		LPCTSTR lpszValue = lpszKey + _tcslen(lpszKey) + 1;

		ExtFormatStrings (strKey, lpszKey, rglpszSymbols, nSymbols);
		ExtFormatStrings (strValue, lpszValue, rglpszSymbols, nSymbols);

		if ((hkey == HKEY_CLASSES_ROOT) && strKey.GetLength() == 0)
		{
			TRACE1("Warning: skipping empty key '%Fs'\n", lpszKey);
			continue;
		}

		if (!bReplace)
		{
			TCHAR szBuffer[256];
			LONG lSize = sizeof(szBuffer)/sizeof(*szBuffer);
		
			if (::RegQueryValue(hkey, strKey, szBuffer, &lSize) == ERROR_SUCCESS)
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
		if (::RegSetValue(hkey, strKey, REG_SZ, strValue, 0) != ERROR_SUCCESS)
		{
			TRACE2("Error: failed setting key '%Fs' to value '%Fs'\n",
				(LPCTSTR)strKey, (LPCTSTR)strValue);
			return FALSE;
		}
	}
	return TRUE;
}

#if _WIN32
///////////////////////////////////////////////////////////////////////////////////////
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

	if( ERROR_SUCCESS == ( dwResult = ::RegOpenKeyEx( hParentKey, szKeyName, 0L, KEY_ALL_ACCESS, &hCurrentKey) ) )
	{
		// remove all subkeys of the key to delete
		while( ERROR_SUCCESS == ( dwResult = ::RegEnumKey( hCurrentKey, 0, szSubKeyName, sizeof( szSubKeyName ) ) ) )
		{
			::OutputDebugString(szSubKeyName);
			::OutputDebugString(TEXT("\r\n"));
			if ( ERROR_SUCCESS != ( dwResult = _ExtRecursiveRegDeleteKey( hCurrentKey, szSubKeyName ) ) )
				break;
		}

		// if all went well, we should now be able to delete the requested key
		if( ERROR_NO_MORE_ITEMS == dwResult )
			dwResult = ::RegDeleteKey( hParentKey, szKeyName );
	}

	RegCloseKey(hCurrentKey);
	return dwResult;
}

inline BOOL _ExtRegDeleteKeySucceeded(LONG error)
{
	return (error == ERROR_SUCCESS) || (error == ERROR_BADKEY) || (error == ERROR_FILE_NOT_FOUND);
}
#else
LONG _ExtRecursiveRegDeleteKey(HKEY hParentKey, LPTSTR szKeyName)
{
	return ::RegDeleteKey( hParentKey, szKeyName );
}

inline BOOL _ExtRegDeleteKeySucceeded(LONG error)
{
	return (error == ERROR_SUCCESS);
}
#endif

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
//				ProgID\OldName\...

// VisModule	Software\uve\TRiAS\VisModules\ProgID			FullName (%1)
// VisModule	Software\uve\TRiAS\VisModules\ProgID\CLSID		{VisModule} (%2)
// VisModule	Software\uve\TRiAS\VisModules\ProgID\Config		REG_DWORD:ObjTypes:0x..

static LPCTSTR BASED_CODE rglpszExtProgID[] =
{
	TEXT("\0") TEXT("%1"),
	TEXT("CLSID\0") TEXT("%2"),
	TEXT("OldName\0") TEXT("%3"),
	NULL,
};

BOOL VMDRegister(HINSTANCE hInstance, REFCLSID rclsid, LPCTSTR lpszProgID, LPCTSTR lpszLongName, DWORD dwObjTypes)
{
	DWORD	dwVersion = ::GetVersion();

	OLECHAR oleszClassID[GUID_CCH];
	TCHAR szClassID[GUID_CCH];
	int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return FALSE;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

	BOOL bSuccess = FALSE;
	TCHAR szKey[_MAX_PATH];
	CString strTypeName, strOldName; 
	
	::AfxExtractSubString( strTypeName, lpszLongName, 0, '\n' );
	::AfxExtractSubString( strOldName, lpszLongName, 1, '\n' );

	if( strTypeName.IsEmpty() )
		strTypeName = lpszProgID;

	//  Attempt to open registry keys.
	HKEY hkeyClassID = NULL;
	HKEY hkeyProgID = NULL;

	wsprintf(szKey, g_cbClsID, szClassID);
	if (::RegCreateKey (HKEY_CLASSES_ROOT, szKey, &hkeyClassID) != ERROR_SUCCESS)
		goto labelError;
	if (::RegCreateKey (HKEY_CLASSES_ROOT, lpszProgID, &hkeyProgID) != ERROR_SUCCESS)
		goto labelError;

	ASSERT (hkeyClassID != NULL);
	ASSERT (hkeyProgID != NULL);

	LPCTSTR rglpszSymbols[3];
	TCHAR szPathName[_MAX_PATH];

	::GetModuleFileName (AfxGetInstanceHandle(), szPathName, _MAX_PATH);

	// ClassID generieren
	rglpszSymbols[0] = strTypeName;			// FullName
	rglpszSymbols[1] = lpszProgID;			// ProgID
	rglpszSymbols[2] = szPathName;			// Path

	if( !ExtOleRegisterHelperEx (rglpszClassID, rglpszSymbols, 3, TRUE, hkeyClassID) )
		goto labelError;

	// ProgID generieren

	rglpszSymbols[0] = strTypeName;			// FullName
	rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
	rglpszSymbols[2] = strOldName;

	if( !ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 3, TRUE, hkeyProgID) )
		goto labelError;

#ifdef _WIN32
	if( !(dwVersion & 0x80000000) || LOBYTE(LOWORD(GetVersion())) > 3 )
	{
		HKEY hkeyUser = NULL;

//		wsprintf (szKey, g_cbVMKey, lpszProgID);
		wsprintf (szKey, g_cbVMKey, REG_COMPANY_KEY,REG_PRODUCT_KEY,lpszProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) != ERROR_SUCCESS)
			goto labelError;

		rglpszSymbols[0] = strTypeName;			// FullName
		rglpszSymbols[1] = szClassID;			// {xxxxxxxx-...}
		rglpszSymbols[2] = strOldName;

		ExtOleRegisterHelperEx (rglpszExtProgID, rglpszSymbols, 3, TRUE, hkeyUser);
		
		if (hkeyUser != NULL)
			::RegCloseKey(hkeyUser);

		// zuständig für folgende ObjektTypen
//		wsprintf (szKey, g_cbVMCfgKey, lpszProgID);
		wsprintf (szKey, g_cbVMCfgKey, REG_COMPANY_KEY,REG_PRODUCT_KEY,lpszProgID);
		if (::RegCreateKey (HKEY_CURRENT_USER, szKey, &hkeyUser) != ERROR_SUCCESS)
			goto labelError;

		if (hkeyUser != NULL)
		{
			::RegSetValueEx (hkeyUser, TEXT("ObjTypes"), NULL, REG_DWORD, (const LPBYTE)&dwObjTypes, sizeof(DWORD));
			::RegCloseKey(hkeyUser);
		}
	}
	else
	{
		// Vismodule sind weiterhin in INI eingetragen
		int iExtNums = GetPrivateProfileInt (g_cbParams, g_cbNumVisModules, 0, g_cbIniFile);
		BOOL fExists = FALSE;
	
		if (::GetPrivateProfileString (g_cbVisModules, strTypeName, g_cbNil, szKey, _MAX_PATH, g_cbIniFile) > 0)
		{	// Erweiterung ist bereits registriert
			fExists = TRUE;
		}
		
		// Erweiterung in INI ordnungsgemäß registrieren
		wsprintf (szKey, TEXT("%s,%ld"), lpszProgID, dwObjTypes);
		::WritePrivateProfileString (g_cbVisModules, strTypeName, szKey, g_cbIniFile);
		if (!fExists)		// Anzahl hochsetzen
		{
			wsprintf (szKey, TEXT("%d"), ++iExtNums);
			::WritePrivateProfileString (g_cbParams, g_cbNumVisModules, szKey, g_cbIniFile);
		}
	}
#endif // _WIN32

labelError:
	if (hkeyProgID != NULL)	::RegCloseKey(hkeyProgID);
	if (hkeyClassID != NULL) ::RegCloseKey(hkeyClassID);

	return TRUE;
}

BOOL VMDUnRegister(REFCLSID rclsid, LPCTSTR lpszProgID)
{
	DWORD	dwVersion = ::GetVersion();

	OLECHAR oleszClassID[GUID_CCH];
	TCHAR szClassID[GUID_CCH];
	int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return FALSE;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // WIN32

	TCHAR szKey[_MAX_PATH];
	long error;
	BOOL bRetCode = TRUE;

	wsprintf(szKey, g_cbClsID, szClassID);
	error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, szKey);
	bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);

	if (bRetCode)
	{
		error = _ExtRecursiveRegDeleteKey(HKEY_CLASSES_ROOT, (LPTSTR)lpszProgID);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}

#if _WIN32
	if( bRetCode && ( !(dwVersion & 0x80000000) || LOBYTE(LOWORD(GetVersion())) > 3) )
	{
//		wsprintf (szKey, g_cbVMKey, lpszProgID);
		wsprintf (szKey, g_cbVMKey,REG_COMPANY_KEY,REG_PRODUCT_KEY, lpszProgID);
		error = _ExtRecursiveRegDeleteKey(HKEY_CURRENT_USER, szKey);
		bRetCode = bRetCode && _ExtRegDeleteKeySucceeded(error);
	}
#endif
	return bRetCode;
}
