// ImportDBEngine.cpp : Implementation of CTRiASImportApp and DLL registration.

#include "stdafx.h"

#include "Version.h"
#include "TRiASGlb.h"
#include "TRiASImport.h"
#include "ImportDBEngine.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CImportDBEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASDBEngine,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties

///////////////////////////////////////////////////////////////////////////////
// Liefert die Version des unterliegenden Datenbanksystems
STDMETHODIMP CImportDBEngine::get_Version(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CImportDBEngine::get_Version");

CString strVersion;

	strVersion.Format (g_cbVersionFormat, TRIASIMP_VERSION, TRIASIMP_RELEASE, TRIASIMP_BUILD);

CComBSTR bstrVersion (strVersion);

	*pVal = bstrVersion.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Setzt Nutzername und Password für nachfolgende Aktivitäten (optional)
STDMETHODIMP CImportDBEngine::put_UserName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CImportDBEngine::put_UserName");
}

STDMETHODIMP CImportDBEngine::put_Password(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CImportDBEngine::put_Password");
}

///////////////////////////////////////////////////////////////////////////////
// Liefert etwas ausführlichere Beschreibung (für UI)
STDMETHODIMP CImportDBEngine::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CImportDBEngine::get_Description");

CString str;

	ATLTRY(str.LoadString (IDS_DBENGINE_DESC));
	if (str.IsEmpty())
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CComBSTR bstr (str);

	if (!bstr)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methods

///////////////////////////////////////////////////////////////////////////////
// Startet das unterliegende Datenbanksystem, wird einmal am Anfang gerufen,
// nach dem alle Randbedingungen eingestellt sind.
STDMETHODIMP CImportDBEngine::Start(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Stoppt das unterliegende Datenbanksystem, wird einmal am Ende gerufen.
STDMETHODIMP CImportDBEngine::Stop()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Enumerator, der die ProgID's aller bekannten Projekttypen enthält
// (z.B. 'Access.GDatabase').
// Rückgabewert ist ein IEnumString, der hier als IUnknown getarnt ist, damit
// die Funktion [oleautomation] - kompatibel ist
STDMETHODIMP CImportDBEngine::EnumDataBaseTypes(IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// alle registrierten DatenServer enumerieren und zwischenspeichern
CRegKey key;

	key.Attach (OpenDataServerKey());
	ASSERT(NULL != HKEY(key));

int iCnt = CountRegisteredDataServers (key);

	ASSERT(0 < iCnt);		// wenigstens einer muß registriert sein

// Zeiger umkopieren, damit ein zusammenhängender Vektor entsteht,
// dazu auf dem Stack den Speicher anfordern (gibt sich selbst frei!)
LPOLESTR *ppStrs = (LPOLESTR*)alloca(sizeof(LPOLESTR) * iCnt);
DWORD dwCnt = 0;
TCHAR cbEnumKey[_MAX_PATH];

	USES_CONVERSION;
	while (ERROR_SUCCESS == ::RegEnumKey (key, dwCnt, cbEnumKey, _MAX_PATH)) 
		ppStrs[dwCnt++] = A2OLE(cbEnumKey);		// nutzt ebenfalls alloca()

	ASSERT(int(dwCnt) <= iCnt);		// sind es plötzlich mehr geworden

// Enumeratorobjekt anlegen und füllen
CComObject<CEnumString> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumString>());		// AddRef ist noch 0
	if (NULL == pIEnum) return Error (g_cbNoMemory, E_OUTOFMEMORY);

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
HRESULT hr = pIEnum -> Init ((LPOLESTR *)&ppStrs[0], (LPOLESTR *)&ppStrs[iCnt], (IDispatch *)this, AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIEnum);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

	return hr;
}
