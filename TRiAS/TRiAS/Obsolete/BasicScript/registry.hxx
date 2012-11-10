// Wrapperklassen für RegistryZugriff -----------------------------------------
// File: REGISTRY.HXX

#if !defined(_REGISTRY_HXX)
#define _REGISTRY_HXX

class CRegistry {
private:
	HKEY m_hKey;

protected:
#if defined(WIN32)
	bool FSubKeyDelete (HKEY hUpKey, LPCTSTR szRegPath);
#endif // WIN32

public:
		CRegistry (HKEY hRoot, LPCTSTR pKey, bool fCreate = false);
		~CRegistry (void);

#if defined(WIN32)
	bool SetDWORD (LPCTSTR pSubKey, DWORD dwData);
	bool GetDWORD (LPCTSTR pSubKey, DWORD &dwData);
	bool SetSubSZ (LPCTSTR pSubKey, LPCTSTR pBuffer);
	bool GetSubSZ (LPCTSTR pSubKey, LPTSTR pBuffer, DWORD &dwLen);
#else
	bool SetSubSZ (LPCTSTR pSubKey, LPCTSTR pBuffer)
		{ return SetSZ (pSubKey, pBuffer); }
	bool GetSubSZ (LPCTSTR pSubKey, LPTSTR pBuffer, DWORD &dwLen)
		{ return GetSZ (pSubKey, pBuffer, (LONG &)dwLen); }
#endif // WIN32
	bool SetSZ (LPCTSTR pSubKey, LPCTSTR pBuffer);
	bool GetSZ (LPCTSTR pSubKey, LPTSTR pBuffer, LONG &dwLen);

	bool DeleteKey (LPCTSTR pSubKey, bool fAllSubKeys = true);
	
	bool isValid (void) { return m_hKey != NULL; }
};

class CClassesRoot : public CRegistry {
public:
	CClassesRoot (LPCTSTR pKey, bool fCreate = false) 
		: CRegistry (HKEY_CLASSES_ROOT, pKey, fCreate) {}
};

#if defined(WIN32)
class CCurrentUser : public CRegistry {
public:
	CCurrentUser (LPCTSTR pKey, bool fCreate = false) 
		: CRegistry (HKEY_CURRENT_USER, pKey, fCreate) {}
};

class CLocalMachine : public CRegistry {
public:
	CLocalMachine (LPCTSTR pKey, bool fCreate = false) 
		: CRegistry (HKEY_LOCAL_MACHINE, pKey, fCreate) {}
};
#endif

#endif // _REGISTRY_HXX
