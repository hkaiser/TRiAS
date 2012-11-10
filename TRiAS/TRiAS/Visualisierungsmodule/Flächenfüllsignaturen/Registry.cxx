// Wrapperklassen für RegistryZugriff -----------------------------------------
// File: REGISTRY.CXX

#include "stdafx.h"

#if !defined(WIN32)
#include <shellapi.h>
#include <tchar.h>
#endif 
#include <registrx.hxx>

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor -----------------------------------------------------
CRegistry :: CRegistry (HKEY hRoot, LPCTSTR pKey, bool fCreate, REGSAM samDesired)
		    : m_hKey (NULL)
{
	if (fCreate) 
		::RegCreateKeyEx (hRoot, pKey, 0L, NULL, REG_OPTION_NON_VOLATILE, samDesired, NULL, &m_hKey, NULL);
	else
		::RegOpenKeyEx (hRoot, pKey, 0L, samDesired, &m_hKey);
}

CRegistry::CRegistry (HKEY hRoot, REGSAM samDesired, LPCTSTR pKey)
	: m_hKey (NULL)
{
	::RegOpenKeyEx (hRoot, pKey, 0L, samDesired, &m_hKey);
}

CRegistry :: ~CRegistry (void)
{
	if (isValid()) {
		::RegCloseKey (m_hKey);
		m_hKey = NULL;
	}
}

#if defined(WIN32)
bool CRegistry :: SetDWORD (LPCTSTR pSubKey, DWORD dwData)
{
	if (!isValid()) return false;

return ::RegSetValueEx (m_hKey, pSubKey, NULL, REG_DWORD, 
			(const LPBYTE)&dwData, sizeof(DWORD)) == ERROR_SUCCESS;
}

bool CRegistry :: GetDWORD (LPCTSTR pSubKey, DWORD &rdwData)
{
	if (!isValid()) return false;

DWORD dwType = REG_DWORD;
DWORD dwSize = sizeof(DWORD);
DWORD dwData = 0L;
LONG lRet = ::RegQueryValueEx (m_hKey, pSubKey, NULL, &dwType, (LPBYTE)&dwData, &dwSize);

	if (lRet == ERROR_SUCCESS && dwType == REG_DWORD && dwSize == sizeof(DWORD)) {
		rdwData = dwData;
		return true;
	}

return false;
}


bool CRegistry :: SetSubSZ (LPCTSTR pSubKey, LPCTSTR pBuffer)
{
	if (!isValid()) return false;

return ::RegSetValueEx (m_hKey, pSubKey, NULL, REG_SZ, 
			(const LPBYTE)pBuffer, strlen(pBuffer)+1) == ERROR_SUCCESS;
}

bool CRegistry :: GetSubSZ (LPCTSTR pSubKey, LPTSTR pBuffer, DWORD &dwLen)
{
	if (!isValid()) return false;

DWORD dwType = REG_SZ;
LONG lRet = ::RegQueryValueEx (m_hKey, pSubKey, NULL, 
			       &dwType, (LPBYTE)pBuffer, &dwLen);
	if (lRet == ERROR_SUCCESS && dwType == REG_SZ) 
		return true;

	*pBuffer = '\0';
	return false;
}

#endif // WIN32

bool CRegistry :: SetSZ (LPCTSTR pSubKey, LPCTSTR pBuffer)
{
	if (!isValid()) return false;

return ::RegSetValue (m_hKey, pSubKey, REG_SZ, 
		      pBuffer, strlen(pBuffer)+1) == ERROR_SUCCESS;
}

bool CRegistry :: GetSZ (LPCTSTR pSubKey, LPTSTR pBuffer, LONG &dwLen)
{
	if (!isValid()) return false;

return ::RegQueryValue (m_hKey, pSubKey, pBuffer, &dwLen) == ERROR_SUCCESS;
}

bool CRegistry :: DeleteKey (LPCTSTR szKey, bool fAllSubKeys)
{
#if defined(WIN32)	// nur hier möglich
// alle Unterschlüssel mit weglöschen
	if (fAllSubKeys)
		return FSubKeyDelete (m_hKey, szKey);
#endif		

	return (RegDeleteKey (m_hKey, szKey) == ERROR_SUCCESS);
}

#if defined(WIN32)

bool CRegistry :: FSubKeyDelete (HKEY hUpKey, LPCTSTR szRegPath)
{
HKEY hKey;
DWORD retCode;
char cbBuffer[_MAX_PATH];

// Use RegOpenKey() with the new Registry path to get an open handle
// to the child key you want to enumerate.
	retCode = RegOpenKey (hUpKey, szRegPath, &hKey);
	if (retCode != ERROR_SUCCESS) return false;

// alle Subkeys löschen
DWORD i = 0;

	while (RegEnumKey (hKey, i++, cbBuffer, sizeof(cbBuffer)) == ERROR_SUCCESS) {
		if (!FSubKeyDelete (hKey, cbBuffer))
			break;
	}
	RegCloseKey (hKey);   // Close the key handle.

// Key selbst löschen
	retCode = RegDeleteKey (hUpKey, szRegPath);

return (retCode == ERROR_SUCCESS);
}

#endif // WIN32

