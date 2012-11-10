///////////////////////////////////////////////////////////////////////////
// @doc 
// @module VmdMenuMap.h | Description goes here

#if !defined(_VMDMENUMAP_H__9CFAB4CC_B36F_11D2_95A5_006008447800__INCLUDED_)
#define _VMDMENUMAP_H__9CFAB4CC_B36F_11D2_95A5_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Registrx.hxx>
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// ein MapEintrag
class CVMDMenuItem
{
public:
	CVMDMenuItem() : m_dwOTypes(0) {}
	CVMDMenuItem(DWORD dwObjTypes, LPCSTR pcModule, LPCSTR pcText)
		: m_dwOTypes(dwObjTypes), m_strModule(pcModule), m_strMenuText(pcText)
	{
	}
	const CVMDMenuItem& operator= (const CVMDMenuItem& rhs)
	{
		if (this != &rhs) {
			m_dwOTypes = rhs.m_dwOTypes;
			m_strModule = rhs.m_strModule;
			m_strMenuText = rhs.m_strMenuText;
		}
		return *this;
	}

	DWORD GetType() const { return m_dwOTypes; }
	LPCSTR GetMenuString() const { return m_strMenuText.c_str(); }
	LPCSTR GetModuleName() const { return m_strModule.c_str(); }

private:
	DWORD m_dwOTypes;
	os_string m_strModule;
	os_string m_strMenuText;
};

const UINT IDM_VMDSEPARATOR = 20;	// MenuItemBase

class CVMDMenuMap :
	public map<UINT, CVMDMenuItem, less<UINT> >
{
public:
	CVMDMenuMap () {}
	
	bool FInit (UINT uiMenuOffset)
	{
	HKEY hKey = NULL;
	DWORD i = 0;
	char cbKey[_MAX_PATH];
	DWORD retCode = RegOpenKey (HKEY_CURRENT_USER, s_cbVisModules, &hKey);

		if (retCode != ERROR_SUCCESS) return false;

	// alle Erweiterungen mit Priorität laden
		while (RegEnumKey (hKey, i++, cbKey, _MAX_PATH) == ERROR_SUCCESS) 
			LoadVisModuleRegistry (i+uiMenuOffset+IDM_VMDSEPARATOR, cbKey);

		RegCloseKey (hKey);   // Close the key handle.
		return true;
	}

protected:
	bool LoadVisModuleRegistry (UINT uiID, LPCSTR pcKey)
	{
	os_string strName, strOldName; 
	DWORD dwObjTypes = 0;

	// Lesbaren Bezeichner holen
		{
		CCurrentUser regExt (KEY_READ, s_cbVisModules);
		TCHAR cbName [_MAX_PATH];
		LONG lLen = _MAX_PATH;

			if (regExt.GetSZ (pcKey, cbName, lLen))		// Name lesen
				strName = cbName;
			else 
				strName = pcKey;
		}

	// oldname
		{
		os_string strKey = os_string(s_cbVisModules) + TEXT("\\") + pcKey;
		CCurrentUser regExt (KEY_READ, strKey.c_str());
		TCHAR cbName [_MAX_PATH];
		LONG lLen = _MAX_PATH;

			if (regExt.GetSZ (TEXT("OldName"), cbName, lLen))		// OldName lesen
				strOldName = cbName;
			else 
				strOldName = pcKey;
		}

	// ConfigOptions
		{
		os_string strKey = string(s_cbVisModules) + TEXT("\\") + pcKey + TEXT("\\Config");
		CCurrentUser regExt (KEY_READ, strKey.c_str());

			if (!regExt.GetDWORD (TEXT("ObjTypes"), dwObjTypes))		// Options lesen
				return false;
		}

	pair<iterator, bool> p = insert (value_type(uiID, CVMDMenuItem(dwObjTypes, strOldName.c_str(), strName.c_str())));
		
		return p.second;
	}
};

#endif // !defined(_VMDMENUMAP_H__9CFAB4CC_B36F_11D2_95A5_006008447800__INCLUDED_)
