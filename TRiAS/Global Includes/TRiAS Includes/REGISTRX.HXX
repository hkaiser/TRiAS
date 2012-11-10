// Wrapperklassen für RegistryZugriff -----------------------------------------
// File: REGISTRX.HXX

#if !defined(_REGISTRX_HXX)
#define _REGISTRX_HXX

class CRegistry {
private:
	HKEY m_hKey;

protected:
#if !defined(WIN16)
	bool FSubKeyDelete (HKEY hUpKey, LPCTSTR szRegPath);
#endif // WIN16

public:
		CRegistry (HKEY hRoot, REGSAM samDesired, LPCTSTR pKey);
		CRegistry (HKEY hRoot, LPCTSTR pKey, bool fCreate = false, REGSAM samDesired = KEY_ALL_ACCESS);
		~CRegistry (void);

#if !defined(WIN16)
	bool SetDWORD (LPCTSTR pSubKey, DWORD dwData);
	bool GetDWORD (LPCTSTR pSubKey, DWORD &dwData);
	bool SetSubSZ (LPCTSTR pSubKey, LPCTSTR pBuffer);
	bool GetSubSZ (LPCTSTR pSubKey, LPTSTR pBuffer, DWORD &dwLen);
	bool DeleteValue (LPCTSTR pcValueName);
#else
	bool SetSubSZ (LPCTSTR pSubKey, LPCTSTR pBuffer)
		{ return SetSZ (pSubKey, pBuffer); }
	bool GetSubSZ (LPCTSTR pSubKey, LPTSTR pBuffer, DWORD &dwLen)
		{ return GetSZ (pSubKey, pBuffer, (LONG &)dwLen); }
#endif // WIN16
	bool SetSZ (LPCTSTR pSubKey, LPCTSTR pBuffer);
	bool GetSZ (LPCTSTR pSubKey, LPTSTR pBuffer, LONG &dwLen);

	bool DeleteKey (LPCTSTR pSubKey, bool fAllSubKeys = true);
	
	bool isValid (void) { return m_hKey != NULL; }

	operator HKEY() const { return m_hKey; };
};

class CClassesRoot : 
	public CRegistry 
{
public:
	CClassesRoot (REGSAM samDesired, LPCTSTR pKey) 
		: CRegistry (HKEY_CLASSES_ROOT, samDesired, pKey) {}
	CClassesRoot (LPCTSTR pKey, bool fCreate = false, REGSAM samDesired = KEY_ALL_ACCESS) 
		: CRegistry (HKEY_CLASSES_ROOT, pKey, fCreate, samDesired) {}
};

#if !defined(WIN16)
class CCurrentUser : 
	public CRegistry 
{
public:
	CCurrentUser (REGSAM samDesired, LPCTSTR pKey) 
		: CRegistry (HKEY_CURRENT_USER, samDesired, pKey) {}
	CCurrentUser (LPCTSTR pKey, bool fCreate = false, REGSAM samDesired = KEY_ALL_ACCESS) 
		: CRegistry (HKEY_CURRENT_USER, pKey, fCreate, samDesired) {}
};

class CLocalMachine : 
	public CRegistry 
{
public:
	CLocalMachine (REGSAM samDesired, LPCTSTR pKey) 
		: CRegistry (HKEY_LOCAL_MACHINE, samDesired, pKey) {}
	CLocalMachine (LPCTSTR pKey, bool fCreate = false, REGSAM samDesired = KEY_ALL_ACCESS) 
		: CRegistry (HKEY_LOCAL_MACHINE, pKey, fCreate, samDesired) {}
};
#endif

#endif // _REGISTRX_HXX
