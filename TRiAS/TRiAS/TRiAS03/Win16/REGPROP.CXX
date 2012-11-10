// PropertySheet, welcher zusätzliche Pages über die Registry lädt ------------
// File: REGPROP.CXX

#include "trias03p.hxx"

#include <shlobj.h>
#include <xtsnguid.h>
#include <ixtnext.hxx>

#include "regprop.hxx"

static const char s_cbApplication[] = TEXT("TRiAS.Application.2");

///////////////////////////////////////////////////////////////////////////////
CPropertySheetExt::CPropertySheetExt (LPCSTR pszCaption, Window *pParentWnd, 
									  DWORD dwStyle, UINT iSelectPage)
				  : CPropertySheet (pszCaption, pParentWnd, dwStyle, iSelectPage) 
{ 
	m_pPages = NULL;
}

CPropertySheetExt::~CPropertySheetExt (void)
{
	DELETE(m_pPages);
}

// alle registrierten Pages hinzufügen ----------------------------------------
HRESULT CPropertySheetExt::LoadExtPagesFromRegistry (
			HKEY hKeyRoot, LPCSTR pcKey, LPCSTR pcSubKey,
			LPDATAOBJECT pIDO, LPCITEMIDLIST pcidl)
{
// Key zusammenbauen
string strKey = string(pcKey) + TEXT("\\") + pcSubKey;

// Registrierte Pages enumerieren
HKEY hKey = NULL;
DWORD i = 0;
char cbEnumKey[_MAX_PATH];
DWORD retCode = RegOpenKey (hKeyRoot, strKey.c_str(), &hKey);
HRESULT hr = NOERROR;

	if (retCode != ERROR_SUCCESS) return ResultFromScode (E_FAIL);

// alle registrierten EInträge durchgehen
	while (RegEnumKey (hKey, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
		LoadExtPageFromRegistry (hKey, cbEnumKey, pcSubKey, pIDO, pcidl);
		i++;
	}

// Schlüssel wieder abschließen
	RegCloseKey (hKey);   // Close the key handle.

// keine Subschlüssel vorhanden und noch nicht an der Application nachgesehen
	if (0 == i && string(pcKey) != s_cbApplication) {
		hr = LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, 
					s_cbApplication, pcSubKey, pIDO, pcidl);
	}

return hr;
}

// Einen Key abarbeiten -------------------------------------------------------
HRESULT CPropertySheetExt::LoadExtPageFromRegistry (
			HKEY hKey, LPCSTR pcKey, LPCSTR pcSubKey, 
			LPDATAOBJECT pIDO, LPCITEMIDLIST pcidl)
{
// ClassID aus Registry besorgen
CLSID clsID;
HRESULT hr = CLSIDFromProgID (WideString(pcKey), &clsID);

	if (FAILED(hr)) {
	// evtl. Zusammenfassung von SubKeys: über TRiAS.Application.2 versuchen
	string strKey = string(pcSubKey) + TEXT("\\") + pcKey;

		return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, 
					s_cbApplication, strKey.c_str(), pIDO, pcidl);
	}

// Objekt instantiieren
WTriasExtInit IPSExtInit;

	hr = CoCreateInstance (clsID, NULL, CLSCTX_INPROC_SERVER, 
						   IID_ITriasExtInit, IPSExtInit.ppv());
	if (FAILED(hr)) return hr;

// Objekt initialisieren
	hr = IPSExtInit -> Initialize (pcidl, pIDO, hKey);
	if (FAILED(hr)) return hr;

// Pages hinzufügen
WTriasPropSheetExt IPSExt = IPSExtInit;		// (-> QueryInterface)

	hr = GetLastHRESULT();
	if (FAILED(hr)) return hr;

	hr = IPSExt -> AddPages (AddPropSheetPageProc, (LPARAM)this);

// Objekt in unserem Container festhalten, damit selbige geladen bleiben
	if (NULL == m_pPages) {
		m_pPages = new CPageList;
		if (NULL == m_pPages) return ResultFromScode (E_OUTOFMEMORY);
	}
	m_pPages -> push_back(IPSExt);

return hr;
}

// Funktion, die von außen gerufen wird, um Page hinzuzufügen -----------------
bool CALLBACK AddPropSheetPageProc (HPROPSHEETPAGE hPage, LPARAM lParam)
{
UINT uiPage = ((CPropertySheet *)lParam) -> AddPage (hPage);

	return uiPage < UINT_MAX;
}

