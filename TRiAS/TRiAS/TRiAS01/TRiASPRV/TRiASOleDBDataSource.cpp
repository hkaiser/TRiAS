// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 21:58:03 
//
// @doc
// @module TRiASOleDBDataSource.cpp | Definition of the <c CTRiASOleDBDataSource> class

#include "StdAfx.h"

#include <shfolder.h>
#include <WinVersion.h>

#include <ospace/file/path.h>

#include "TRiASOleDBDataSource.h"
#include "TRiASOleDBSession.h"
#include "SchemaRowsets.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// global Windows Version Object
CWinVersion g_Version;

///////////////////////////////////////////////////////////////////////////////
// WindowsVersion
bool IsWin31 (void) { return g_Version.IsWin31(); }
bool IsWin40 (void) { return g_Version.IsWin40(); }
bool IsWin41 (void) { return g_Version.IsWin41(); }
bool IsWin50 (void) { return g_Version.IsWin50(); }
bool IsWin32s (void) { return g_Version.IsWin32s(); }
bool IsWinNT (void) { return g_Version.IsWinNT(); }

// Funktion entscheidet, ob IDBCreateSession und IDBInfo verfügbar sind oder nicht
HRESULT WINAPI CTRiASOleDBSource::_FailIfNotInitialized (void *pv, REFIID iid, void** ppvObject, DWORD dw)
{
CTRiASOleDBSource *pThis = (CTRiASOleDBSource *)pv;

	if (!(pThis -> m_dwStatus & DSF_INITIALIZED)) 
		return E_NOINTERFACE;		// Interface ist nicht verfügbar, da DQ nicht initialisiert ist

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen, daß GeoDB geöffnet ist
namespace {
	HRESULT DbPropvalStgm2Stgm(DWORD dwMode, DWORD *pdwStgmMode)
	{
		_ASSERTE(NULL != pdwStgmMode);

		*pdwStgmMode = 0;
		switch (dwMode & DB_MODE_READWRITE) {
		case DB_MODE_READ:
			*pdwStgmMode |= STGM_READ;
			break;

		case DB_MODE_WRITE:
			*pdwStgmMode |= STGM_WRITE;
			break;

		default:					// default ist ReadWrite
		case DB_MODE_READWRITE:
			*pdwStgmMode |= STGM_READWRITE;
			break;
		}

		switch (dwMode & (DB_MODE_SHARE_EXCLUSIVE|DB_MODE_SHARE_DENY_NONE)) {
		case DB_MODE_SHARE_DENY_READ:
			*pdwStgmMode |= STGM_SHARE_DENY_READ;
			break;

		case DB_MODE_SHARE_DENY_WRITE:
			*pdwStgmMode |= STGM_SHARE_DENY_WRITE;
			break;

		case DB_MODE_SHARE_EXCLUSIVE:
			*pdwStgmMode |= STGM_SHARE_EXCLUSIVE;
			break;

		case DB_MODE_SHARE_DENY_NONE:
			*pdwStgmMode |= STGM_SHARE_DENY_NONE;
			break;

		default:
			break;		// DefaultRechte sind vom RO-Status abhängig
		}
		return S_OK;
	}
}

/////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
STDMETHODIMP CTRiASOleDBSource::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDBInitialize,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions
HRESULT CTRiASOleDBSource::AskUserForParameters(HWND hWnd, CComBSTR &rbstrName, DWORD &rdwMode)
{
bool bResult = false;

	USES_CONVERSION;
	COM_TRY {
	CFileDialog dlgFile (TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, NULL, hWnd);

		dlgFile.m_ofn.Flags &= ~OFN_HIDEREADONLY;

	#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50()))		// Win98 oder WinNT50
			dlgFile.m_ofn.Flags |= OFN_ENABLESIZING;
	#endif // OFN_ENABLESIZING

	CComBSTR allFilter;
	CComBSTR bstrFilter;
		
		bstrFilter.LoadString(IDS_OPENFILENAMEFILTER);
		allFilter.LoadString(IDS_ALLFILTER);
		_ASSERTE(bstrFilter.Length() > 0);
		_ASSERTE(allFilter.Length() > 0);

		bstrFilter.Append(allFilter);
		bstrFilter += L"|*.*||";	// next string please

	CString strFilter (bstrFilter);
	LPTSTR pch = strFilter.GetBuffer(0);

		while ((pch = _tcschr (pch, _T('|'))) != NULL)
			*pch++ = _T('\0');

		dlgFile.m_ofn.lpstrFilter = strFilter;
		dlgFile.m_ofn.nMaxCustFilter = 2;

	// StartPfad setzen
	os_path path (OLE2A(rbstrName));
	os_string dir;

		dlgFile.m_ofn.lpstrInitialDir = NULL;
		dlgFile.m_ofn.nFilterIndex = 0;
		if (path.has_directory()) {
			if (path.has_drive()) {
				dir = path.drive();
				dir += path.drive_separator();
			}
			dir += path.directory();
			dlgFile.m_ofn.lpstrInitialDir = dir.c_str();
		}

	// Dateinamen setzen
	CString strFile (path.filename().c_str());

		dlgFile.m_ofn.lpstrFile = strFile.GetBuffer(_MAX_PATH);

	// Default extension setzen
		dlgFile.m_ofn.lpstrDefExt = ".ris";

	// Caption setzen
	CString title;

		title.LoadString(IDS_OPENFILECAP);
		_ASSERTE(title.GetLength() > 0);

		dlgFile.m_ofn.lpstrTitle = title;
		bResult = (IDOK == dlgFile.DoModal()) ? TRUE : FALSE;
		strFile.ReleaseBuffer();

		if (bResult) 
			rbstrName = strFile;

	} COM_CATCH;
	return bResult ? S_OK : DB_E_CANCELED;
} 

HRESULT CTRiASOleDBSource::EnsureDatasourceOpened(INT_PTR *phPr)
{
CTRiASOleDBSource::ObjectLock l(this);

	if (NULL != phPr)
		*phPr = NULL;

// ggf. ist GeoDB bereits geöffnet
	if (NULL != m_hPr) {
		if (NULL != phPr)
			*phPr = m_hPr;
		return S_FALSE;
	}

// Service sicherstellen
	RETURN_ERROR(EnsureServices());

// ProviderString auswerten
CComBSTR bstrProvider;

	RETURN_ERROR(GetProviderString(&bstrProvider));
	RETURN_ERROR(AnalyseProviderString(bstrProvider));

// GeoDB eröffnen
CComBSTR bstrName;
DWORD dwMode;
DWORD dwPrompt;
HWND hWnd = NULL;

	RETURN_ERROR(GetDataSourceParams(&bstrName, &dwMode, &dwPrompt, &hWnd));

// ask the user if applicable
HRESULT hr = S_OK;

	if (DBPROMPT_PROMPT == dwPrompt) {
	// immer beim Nutzer nachfragen
		if (FAILED(hr = AskUserForParameters(hWnd, bstrName, dwMode)))
			return hr;
		_ASSERTE(bstrName.Length() > 0);
	}

	if (0 == bstrName.Length()) {
	// keine Datenquelle gegeben, ggf. selbst nachfragen
		if (DBPROMPT_NOPROMPT == dwPrompt)
			return E_INVALIDARG;
		if (FAILED(hr = AskUserForParameters(hWnd, bstrName, dwMode)))
			return hr;
	}

	_ASSERTE(bstrName.Length() > 0);
	_ASSERTE(m_GeoDBService != NULL);

// set corresponding StorageModeFlags
DWORD dwStgmMode = 0;

	RETURN_FAILED_HRESULT(DbPropvalStgm2Stgm(dwMode, &dwStgmMode));

// Datenbank öffnen
INT_PTR hPr = NULL;
NATIVEOPENMODE rgOpenMode = NATIVEOPENMODE(NATIVEOPENMODE_NoCaseIdents|NATIVEOPENMODE_NoCaseAttribs);

	MAKE_OLEDB_ERROR_EX2(m_GeoDBService -> Open(bstrName, dwStgmMode, rgOpenMode, &hPr), 
		HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
	m_hPr = hPr;

	RETURN_ERROR(InitProperties());
	if (NULL != phPr)
		*phPr = m_hPr;
	return S_OK;
}

// Default-Datenpfad zusammenbauen
bool CTRiASOleDBSource::GetDefaultDataStore (BSTR *pbstrLoc)
{
CRegKey regDirs;
char cbDefaultDir[_MAX_PATH];

	if (ERROR_SUCCESS == regDirs.Open(HKEY_CURRENT_USER, "Software", KEY_READ) && 
		ERROR_SUCCESS == regDirs.Open(regDirs, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regDirs.Open(regDirs, REG_PRODUCT_KEY, KEY_READ))
	{
	CRegKey regKey;

		if (ERROR_SUCCESS == regKey.Open(regDirs, "Directories") ||
			ERROR_SUCCESS == regKey.Create(regDirs, "Directories"))
		{
			regDirs.Close();
			regDirs.Attach(regKey.Detach());

		DWORD dwLen = sizeof(cbDefaultDir);

			cbDefaultDir[0] = '\0';
			if (ERROR_SUCCESS != regDirs.QueryValue(cbDefaultDir, "DefaultDataSourceDir", &dwLen) ||
				'\0' == cbDefaultDir[0]) 
			{
			// ggf. fürs nächste mal schreiben
			DWORD dwFlags = CSIDL_PERSONAL;

				if (IsWinNT() && IsWin50())
					dwFlags |= CSIDL_FLAG_CREATE;

				SHGetFolderPath(NULL, dwFlags, NULL, 0, cbDefaultDir);
				PathAppend(cbDefaultDir, REG_COMPANY_KEY);
				PathAppend(cbDefaultDir, REG_PRODUCT_KEY);
				PathAppend(cbDefaultDir, "DataSources");
				PathAddBackslash(cbDefaultDir);

				regDirs.SetValue(cbDefaultDir, "DefaultDataSourceDir");

			// Verzeichnis auch noch erzeugen
				CreateDirectory (cbDefaultDir, NULL);
			}

		CComBSTR bstrLoc (cbDefaultDir);

			*pbstrLoc = bstrLoc.Detach();
			return true;
		}
	}
	return false;
}

// diverse Properties des Datasource-Objektes initialisieren
HRESULT CTRiASOleDBSource::InitProperties()
{
	_ASSERTE(NULL != m_hPr);

// diverse Properties setzen
CComBSTR bstrDbmsVersion, bstrName, bstrVersion;
CComBool fRO;
char cbComputer[MAX_COMPUTERNAME_LENGTH + 1];
char cbUser[_MAX_PATH];
ULONG ulComputerLen = sizeof(cbComputer);
ULONG ulUserLen = sizeof(cbUser);

	MAKE_OLEDB_ERROR_EX2(m_GeoDBService -> get_DbmsVersion(&bstrDbmsVersion), E_UNEXPECTED);
	MAKE_OLEDB_ERROR_EX2(m_GeoDBService -> get_Version(m_hPr, &bstrVersion), E_UNEXPECTED);
	MAKE_OLEDB_ERROR_EX2(m_GeoDBService -> get_Name (m_hPr, &bstrName), E_UNEXPECTED);
	MAKE_OLEDB_ERROR_EX2(m_GeoDBService -> get_OpenedRO (m_hPr, &fRO), E_UNEXPECTED);
	MAKE_OLEDB_ERROR(GetComputerName(cbComputer, &ulComputerLen));
	MAKE_OLEDB_ERROR(GetUserName(cbUser, &ulUserLen));

CComVariant vDbmsVersion(bstrDbmsVersion);
CComVariant vVersion(bstrVersion);
CComVariant vName(bstrName);
CComVariant vRO ((bool)fRO);
CComVariant vComputer(cbComputer);
CComVariant vUser(cbUser);

	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_DATASOURCEINFO, DBPROP_DBMSVER, &vDbmsVersion));
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_DATASOURCEINFO, DBPROP_DATASOURCENAME, &vName));
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_DATASOURCEINFO, DBPROP_DATASOURCEREADONLY, &vRO));
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_DATASOURCEINFO, DBPROP_SERVERNAME, &vComputer));
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_DATASOURCEINFO, DBPROP_USERNAME, &vUser));
	
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_TRiAS_DATASOURCEINFO, DBPROP_TRiAS_DBVERSION, &vVersion));

// andere properties abfragen und lokal ablegen
CComVariant vGeomType;
HRESULT hr = GetPropValue(&DBPROPSET_TRiAS_INITDATASOURCE, DBPROP_TRiAS_GEOMETRYTYPE, &vGeomType);

	if (SUCCEEDED(hr)) {
		MAKE_OLEDB_ERROR(vGeomType.ChangeType(VT_I4));
		m_dwGeomType = V_I4(&vGeomType);
	} 

	if (m_dwGeomType != DBPROPVAL_TRiAS_GEOMETRYCOLUMNS && m_dwGeomType != DBPROPVAL_TRiAS_GEOMETRYTABLES)
#if defined(_USE_PROP_GEOMETRYAS)
		m_dwGeomType = DBPROPVAL_TRiAS_GEOMETRYCOLUMNS;
#else
		m_dwGeomType = DBPROPVAL_TRiAS_GEOMETRYTABLES;
#endif // defined(_USE_PROP_GEOMETRYAS)

CComVariant vViewMode;

	hr = GetPropValue(&DBPROPSET_TRiAS_INITDATASOURCE, DBPROP_TRiAS_GENERATEVIEWS, &vViewMode);
	if (SUCCEEDED(hr)) {
		MAKE_OLEDB_ERROR(vViewMode.ChangeType(VT_BOOL));
		m_fViewMode = V_BOOL(&vViewMode) ? true : false;
	}
	return S_OK;
}

HRESULT CTRiASOleDBSource::InitPropertiesDbInit()
{
CDBPropSet setInit (DBPROPSET_DBINIT);
CComBSTR bstrLoc;

	if (GetDefaultDataStore (&bstrLoc))
		setInit.AddProperty(DBPROP_INIT_LOCATION, bstrLoc);

	return SetProperties(1, &setInit);
}
 
// Sicherstellen, das GeoDB wieder geschlossen ist
HRESULT CTRiASOleDBSource::EnsureDatasourceClosed()
{
CTRiASOleDBSource::ObjectLock l(this);

	if (NULL == m_hPr)
		return S_OK;

	if (m_GeoDBService != NULL) {
		m_GeoDBService -> Save(m_hPr);
		m_GeoDBService -> Close(m_hPr);
	}

	m_hPr = NULL;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Parameter zum Öffnen aus Properties lesen
HRESULT CTRiASOleDBSource::GetDataSourceParams (
	BSTR *pbstrName, DWORD *pdwMode, DWORD *pdwPrompt, HWND *phWnd)
{
	_ASSERTE(NULL != pbstrName && NULL != pdwMode && NULL != pdwPrompt && NULL != phWnd);

	*pbstrName = NULL;
	*pdwMode = VARIANT_FALSE;
	*pdwPrompt = 0;

ULONG cPropertyIDSets = 1;
DBPROPIDSET rgPropertyIDSets[1];
ULONG cPropertySets;
DBPROPSET *prgPropertySets = NULL;
DBPROPID rgPropId[4];
	
	rgPropId[0] = DBPROP_INIT_DATASOURCE;
	rgPropId[1] = DBPROP_INIT_MODE;
	rgPropId[2] = DBPROP_INIT_PROMPT;
	rgPropId[3] = DBPROP_INIT_HWND;
	rgPropertyIDSets[0].rgPropertyIDs = rgPropId;
	rgPropertyIDSets[0].cPropertyIDs = _countof(rgPropId);
	rgPropertyIDSets[0].guidPropertySet = DBPROPSET_DBINIT;

	MAKE_OLEDB_ERROR(GetProperties(cPropertyIDSets, rgPropertyIDSets, &cPropertySets, &prgPropertySets));
	if (prgPropertySets) {
		*pbstrName = V_BSTR(&prgPropertySets->rgProperties[0].vValue);		// übernimmt Referenz
		*pdwMode = V_I4(&prgPropertySets->rgProperties[1].vValue);
		*pdwPrompt = V_I2(&prgPropertySets->rgProperties[2].vValue);
		*phWnd = reinterpret_cast<HWND>(V_I4(&prgPropertySets->rgProperties[3].vValue));

		CoTaskMemFree(prgPropertySets->rgProperties);
		CoTaskMemFree(prgPropertySets);
		return S_OK;
	}
	return OleDBError(E_UNEXPECTED);
}

HRESULT CTRiASOleDBSource::GetDataSourceCreateParams (int *piCompatible, bool *pfCompressed)
{
	_ASSERTE(NULL != piCompatible && NULL != pfCompressed);

	*piCompatible = 500;
	*pfCompressed = true;

ULONG cPropertyIDSets = 1;
DBPROPIDSET rgPropertyIDSets[1];
ULONG cPropertySets;
DBPROPSET *prgPropertySets = NULL;
DBPROPID rgPropId[2];
	
	rgPropId[0] = DBPROP_TRiAS_CREATE_COMPATIBLE;
	rgPropId[1] = DBPROP_TRiAS_CREATE_COMPRESSED;
	rgPropertyIDSets[0].rgPropertyIDs = rgPropId;
	rgPropertyIDSets[0].cPropertyIDs = _countof(rgPropId);
	rgPropertyIDSets[0].guidPropertySet = DBPROPSET_TRiAS_CREATEDATASOURCE;

	MAKE_OLEDB_ERROR(GetProperties(cPropertyIDSets, rgPropertyIDSets, &cPropertySets, &prgPropertySets));
	if (prgPropertySets) {
		*piCompatible = V_I4(&prgPropertySets->rgProperties[0].vValue);
		*pfCompressed = V_BOOL(&prgPropertySets->rgProperties[1].vValue) ? true : false;

		if (*piCompatible < 300)
			*pfCompressed = false;

		CoTaskMemFree(prgPropertySets->rgProperties);
		CoTaskMemFree(prgPropertySets);
		return S_OK;
	}
	return OleDBError(E_UNEXPECTED);
}

HRESULT CTRiASOleDBSource::GetProviderString (BSTR *pbstrProvider)
{
	_ASSERTE(NULL != pbstrProvider);

	*pbstrProvider = NULL;

ULONG cPropertyIDSets = 1;
DBPROPIDSET rgPropertyIDSets[1];
ULONG cPropertySets;
DBPROPSET *prgPropertySets;
DBPROPID rgPropId[1];
	
	rgPropId[0] = DBPROP_INIT_PROVIDERSTRING;
	rgPropertyIDSets[0].rgPropertyIDs = rgPropId;
	rgPropertyIDSets[0].cPropertyIDs = _countof(rgPropId);
	rgPropertyIDSets[0].guidPropertySet = DBPROPSET_DBINIT;

	MAKE_OLEDB_ERROR(GetProperties(cPropertyIDSets, rgPropertyIDSets, &cPropertySets, &prgPropertySets));
	if (prgPropertySets) {
		*pbstrProvider = V_BSTR(&prgPropertySets->rgProperties[0].vValue);	// übernimmt Referenz

		CoTaskMemFree(prgPropertySets->rgProperties);
		CoTaskMemFree(prgPropertySets);
		return S_OK;
	}
	return OleDBError(E_UNEXPECTED);
}

///////////////////////////////////////////////////////////////////////////////
// Analyse des ProviderStrings und ersetzen der voreingestellten Werte aus den
// ggf. gelesenen properties
namespace {
	bool ExtractTag (LPCOLESTR pcoleAfterTag, BSTR *pbstrTag)
	{
		_ASSERTE(NULL != pbstrTag);

	wchar_t *pT = wcschr(pcoleAfterTag, L';');
	size_t iLen = (NULL != pT) ? pT-pcoleAfterTag : wcslen(pcoleAfterTag);
	CComBSTR bstrResult (iLen, pcoleAfterTag);

		*pbstrTag = bstrResult.Detach();
		return (NULL != *pbstrTag) ? true : false;
	}

// expected tag description
	typedef struct tagINITTAG {
		LPCOLESTR pcoleName;
		DWORD rgTag;
		DWORD dwType;
		const GUID *pcGuid;
	} INITTAG;

	const INITTAG s_rgInitTags[] = {
	// standard initialization tags
		{ L"Data Source=", DBPROP_INIT_DATASOURCE, VT_BSTR, &DBPROPSET_DBINIT, },
		{ L"Mode=", DBPROP_INIT_MODE, VT_I2, &DBPROPSET_DBINIT, },
		{ L"Prompt=", DBPROP_INIT_PROMPT, VT_I4, &DBPROPSET_DBINIT, },
		{ L"Window Handle=", DBPROP_INIT_HWND, VT_I4, &DBPROPSET_DBINIT, },

	// TRiAS specifics
#if defined(_USE_PROP_GEOMETRYAS)
		{ L"TRiAS OleDB:GeometryAs=", DBPROP_TRiAS_GEOMETRYTYPE, VT_I4, &DBPROPSET_TRiAS_INITDATASOURCE, },
#endif // defined(_USE_PROP_GEOMETRYAS)
#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
		{ L"TRiAS OleDB:PredefinedViews=", DBPROP_TRiAS_GENERATEVIEWS, VT_BOOL, &DBPROPSET_TRiAS_INITDATASOURCE, },
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)
		{ L"TRiAS OleDB:CreateCompatible=", DBPROP_TRiAS_CREATE_COMPATIBLE, VT_I4, &DBPROPSET_TRiAS_CREATEDATASOURCE, },
		{ L"TRiAS OleDB:CreateCompressed=", DBPROP_TRiAS_CREATE_COMPRESSED, VT_BOOL, &DBPROPSET_TRiAS_CREATEDATASOURCE, },
	};
}

HRESULT CTRiASOleDBSource::AnalyseProviderString (BSTR bstrProvString)
{
	if (NULL == bstrProvString || 0 == SysStringLen(bstrProvString))
		return S_OK;		// nothing to do

// iterate all known provider tags
	for (int i = 0; i < _countof(s_rgInitTags); ++i) {
	const INITTAG *pcTag = &s_rgInitTags[i];
	wchar_t *pT = wcsstr(bstrProvString, pcTag -> pcoleName);
	
		if (NULL != pT) {
		// current tag found
		CComBSTR bstrTag;

			if (ExtractTag (pT + wcslen(pcTag -> pcoleName), &bstrTag)) {
			CComVariant v (bstrTag);

				if (SUCCEEDED(v.ChangeType(pcTag -> dwType)))
					MAKE_OLEDB_ERROR(SetPropValue (pcTag -> pcGuid, pcTag -> rgTag, &v));
			}
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// support for IDBDatasourceAdmin
HRESULT CTRiASOleDBSource::CreateAndOpenDatasource()
{
CTRiASOleDBSource::ObjectLock l(this);

// ggf. ist GeoDB bereits geöffnet
	if (NULL != m_hPr) 
		return S_FALSE;

// Service sicherstellen
	RETURN_ERROR(EnsureServices());

// ProviderString auswerten
CComBSTR bstrProvider;

	RETURN_ERROR(GetProviderString(&bstrProvider));
	RETURN_ERROR(AnalyseProviderString(bstrProvider));

// GeoDB eröffnen
CComBSTR bstrName;
DWORD dwMode;
DWORD dwPrompt;
HWND hWnd = NULL;
int iCompatible = 500;
bool fCompressed = true;

	RETURN_ERROR(GetDataSourceParams(&bstrName, &dwMode, &dwPrompt, &hWnd));
	RETURN_ERROR(GetDataSourceCreateParams(&iCompatible, &fCompressed));
	_ASSERTE(iCompatible >= 300 || !fCompressed);

// ask the user if applicable
HRESULT hr = S_OK;

	if (DBPROMPT_PROMPT == dwPrompt) {
	// immer beim Nutzer nachfragen
		if (FAILED(hr = AskUserForParameters(hWnd, bstrName, dwMode)))
			return hr;
		_ASSERTE(bstrName.Length() > 0);
	}

	if (0 == bstrName.Length()) {
	// keine Datenquelle gegeben, ggf. selbst nachfragen
		if (DBPROMPT_NOPROMPT == dwPrompt)
			return E_INVALIDARG;
		if (FAILED(hr = AskUserForParameters(hWnd, bstrName, dwMode)))
			return hr;
	}

	_ASSERTE(bstrName.Length() > 0);
	_ASSERTE(m_GeoDBService != NULL);

// create new datasource
NATIVECREATEMODE rgCreateMode = NATIVECREATEMODE_FailIfThere;

	if (iCompatible < 300)
		rgCreateMode = NATIVECREATEMODE(rgCreateMode | NATIVECREATEMODE_CompatibleV2);
	else if (iCompatible < 500)
		rgCreateMode = NATIVECREATEMODE(rgCreateMode | NATIVECREATEMODE_CompatibleV4);

	if (fCompressed)
		rgCreateMode = NATIVECREATEMODE(rgCreateMode | NATIVECREATEMODE_Compressed);
	
	MAKE_OLEDB_ERROR(m_GeoDBService -> Create(bstrName, rgCreateMode));

// set corresponding StorageModeFlags
DWORD dwStgmMode = 0;

	RETURN_FAILED_HRESULT(DbPropvalStgm2Stgm(dwMode, &dwStgmMode));

// Datenbank öffnen
INT_PTR hPr = NULL;
NATIVEOPENMODE rgOpenMode = NATIVEOPENMODE(NATIVEOPENMODE_NoCaseIdents|NATIVEOPENMODE_NoCaseAttribs);

	MAKE_OLEDB_ERROR_EX2(m_GeoDBService -> Open(bstrName, dwStgmMode, rgOpenMode, &hPr), ERROR_FILE_NOT_FOUND);
	m_hPr = hPr;

	RETURN_ERROR(InitProperties());
	return S_OK;
}

HRESULT CTRiASOleDBSource::CloseAndDestroyDatasource()
{
	_ASSERTE(NULL != m_hPr);		// muß geöffnet sein

// Namen der Datenquelle holen
CComBSTR bstrName;

	MAKE_OLEDB_ERROR(m_GeoDBService -> get_Name(m_hPr, &bstrName));

// Datenquelle schließen
	MAKE_OLEDB_ERROR(EnsureDatasourceClosed());

// Datenquelle löschen
	MAKE_OLEDB_ERROR(m_GeoDBService ->Destroy(bstrName));

	return S_OK;
}

