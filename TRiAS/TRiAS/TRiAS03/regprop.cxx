// PropertySheet, welcher zusätzliche Pages über die Registry lädt ------------
// File: REGPROP.CXX

#include "trias03p.hxx"

#include <shlobj.h>
#include <xtsnguid.h>
#include <ixtnext.hxx>

#include "regprop.hxx"

static const char s_cbApplication[] = TEXT("TRiAS.Application.4");

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectWithSite);		// WObjectWithSite

///////////////////////////////////////////////////////////////////////////////
CPropertySheetExt::CPropertySheetExt (LPCSTR pszCaption, Window *pParentWnd, 
									  DWORD dwStyle, UINT iSelectPage)
				  : CPropertySheet (pszCaption, pParentWnd, dwStyle, iSelectPage) 
{ 
	m_pPages = NULL;
}

CPropertySheetExt::~CPropertySheetExt (void)
{
// Site wieder rücksetzen
	if (NULL != m_pPages) {
#if _TRiAS_VER >= 0x0300
		for (CPageList::iterator it = m_pPages -> begin(); it != m_pPages -> end(); ++it)
		{
		WObjectWithSite ObjSite;

			if (SUCCEEDED((*it) -> QueryInterface (IID_IObjectWithSite, ObjSite.ppv())))
				ObjSite -> SetSite (NULL);
		}
#endif // _TRiAS_VER >= 0x0300

	// alle Pages freigeben
		DELETE_OBJ(m_pPages);
	}
}

// alle registrierten Pages hinzufügen ----------------------------------------
HRESULT CPropertySheetExt::LoadExtPagesFromRegistry (
	HKEY hKeyRoot, LPCSTR pcKey, LPCSTR pcSubKey,
	LPDATAOBJECT pIDO, LPCITEMIDLIST pcidl
#if _TRiAS_VER >= 0x0300
	, IUnknown *pIUnkSite, LPCSTR pcProgID, int *piPage
#endif // _TRiAS_VER >= 0x0300
	)
{
// Key zusammenbauen
string strKey = string(pcKey) + TEXT("\\") + pcSubKey;

// Registrierte Pages enumerieren
HKEY hKey = NULL;
DWORD i = 0;
char cbEnumKey[_MAX_PATH];
DWORD retCode = RegOpenKeyEx (hKeyRoot, strKey.c_str(), 0L, KEY_READ, &hKey);
HRESULT hr = NOERROR;

	if (retCode == ERROR_SUCCESS) {
	// alle registrierten Einträge durchgehen
		while (RegEnumKey (hKey, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
#if _TRiAS_VER >= 0x0300
			LoadExtPageFromRegistry (hKey, cbEnumKey, pcSubKey, pIDO, pcidl, pIUnkSite, pcProgID, piPage);
#else
			LoadExtPageFromRegistry (hKey, cbEnumKey, pcSubKey, pIDO, pcidl);
#endif // _TRiAS_VER >= 0x0300
			i++;
		}

	// Schlüssel wieder abschließen
		RegCloseKey (hKey);   // Close the key handle.
	}

// keine Subschlüssel vorhanden und noch nicht an der Application nachgesehen
	if (0 == i && string(pcKey) != s_cbApplication) {
#if _TRiAS_VER >= 0x0300
		hr = LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, 
					s_cbApplication, pcSubKey, pIDO, pcidl, pIUnkSite, pcProgID, piPage);
#else
		hr = LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, 
					s_cbApplication, pcSubKey, pIDO, pcidl);
#endif // _TRiAS_VER >= 0x0300
	}
	return hr;
}

// Einen Key abarbeiten -------------------------------------------------------
HRESULT CPropertySheetExt::LoadExtPageFromRegistry (
	HKEY hKey, LPCSTR pcKey, LPCSTR pcSubKey, 
	LPDATAOBJECT pIDO, LPCITEMIDLIST pcidl
#if _TRiAS_VER >= 0x0300
	, IUnknown *pIUnkSite, LPCSTR pcProgID, int *piPage
#endif // _TRiAS_VER >= 0x0300
	)
{
	USES_CONVERSION;

// ClassID aus Registry besorgen
CLSID clsID;
HRESULT hr = CLSIDFromProgID (A2OLE(pcKey), &clsID);

	if (FAILED(hr)) {
	// evtl. Zusammenfassung von SubKeys: über TRiAS.Application.4 versuchen
	string strKey = string(pcSubKey) + TEXT("\\") + pcKey;

#if _TRiAS_VER >= 0x0300
		return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, 
					s_cbApplication, strKey.c_str(), pIDO, pcidl, pIUnkSite, pcProgID, piPage);
#else
		return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, 
					s_cbApplication, strKey.c_str(), pIDO, pcidl);
#endif // _TRiAS_VER >= 0x0300
	}

	try {
	// Objekt instantiieren
	WTriasExtInit IPSExtInit (clsID);		// throws hr

#if _TRiAS_VER >= 0x0300
		if (NULL != pcProgID && NULL != piPage && !strcmp (pcProgID, pcKey))
			*piPage = m_pPages -> size();	// Nummer der gesuchten Page speichern

		if (NULL != pIUnkSite) {
		WObjectWithSite ObjSite;

			if (SUCCEEDED(IPSExtInit -> QueryInterface (IID_IObjectWithSite, ObjSite.ppv())))
				ObjSite -> SetSite (pIUnkSite);
		}
#endif // _TRiAS_VER >= 0x0300

	// Objekt initialisieren
		hr = IPSExtInit -> Initialize (pcidl, pIDO, hKey);
		if (FAILED(hr)) _com_issue_error(hr);

	// Pages hinzufügen
	WTriasPropSheetExt IPSExt = IPSExtInit;		// (-> QueryInterface)

		hr = IPSExt -> AddPages (AddPropSheetPageProc, (LPARAM)this);
		if (FAILED(hr)) _com_issue_error(hr);

	// Objekt in unserem Container festhalten, damit selbige geladen bleiben
		if (NULL == m_pPages) {
			TX_TRY(m_pPages = new CPageList);
			if (NULL == m_pPages) _com_issue_error(E_OUTOFMEMORY);
		}
		m_pPages -> push_back(IPSExt);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return hr;
}

// Funktion, die von außen gerufen wird, um Page hinzuzufügen -----------------
BOOL CALLBACK AddPropSheetPageProc (HPROPSHEETPAGE hPage, LPARAM lParam)
{
UINT uiPage = ((CPropertySheet *)lParam) -> AddPage (hPage);

	return uiPage < UINT_MAX;
}

