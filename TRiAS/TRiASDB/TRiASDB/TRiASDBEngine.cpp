// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.02.2001 17:35:14 
//
// 21.02.2001 17:35:30
//		 Added ITRiASDBEngineEvents
//
// @doc
// @module TRiASDBEngine.cpp | Implementation of the <c CTRiASDBEngine> class

#include "stdafx.h"
#include <sys/stat.h>
#include <ospace/file/path.h>
#include <ScopeVar.h>

#include "Version.h"
#include "Strings.h"
#include "Wrapper.h"		// SmartIF's
#include "TRiASDBGuids.h"

#include "TRiASDBApp.h"
#include "TRiASDBEngine.h"
#include "TRiASProject.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// Debughilfe für Storage
//#define _DEBUG_ISTORAGE
#if defined(_DEBUG) && defined(_DEBUG_ISTORAGE)
#include <stghelp.hxx>
#endif // defined(_DEBUG) && defined(_DEBUG_ISTORAGE)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASDBEngine, CTRiASDBEngine)

/////////////////////////////////////////////////////////////////////////////
// globale Instanz der DBEngine
CTRiASDBEngine *g_pDBEngine = NULL;
STARTMODE g_rgStartMode = STARTMODE_Normal;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectWithName);		// WObjectWithName

///////////////////////////////////////////////////////////////////////////////
// Registrieren der notwendigen Keys
namespace {
	static _ATL_REGMAP_ENTRY regEntryMap[] = 
	{
		{ L"TRIASNAME", NULL },
		{ NULL, NULL },		// EndeKennung
	};
}

HRESULT WINAPI CTRiASDBEngine::UpdateRegistry(BOOL fRegister)
{
	USES_CONVERSION;
	regEntryMap[0].szData = A2OLE(g_cbTRiAS);
	return _Module.UpdateRegistryFromResource(IDR_TRIASDBENGINE, fRegister, regEntryMap);
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASDBEngine

STDMETHODIMP CTRiASDBEngine::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASDBEngine,
		&IID_ITRiASMainDBEngine,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASDBEngine::FinalConstruct (void)
{
	return S_OK;
}

void CTRiASDBEngine::FinalRelease()
{
	ASSERT(NULL == g_pDBEngine);	// existiert nicht mehr (sollte jedenfalls)
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASDBEngine::get_Version(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::get_Version");

CString strVersion;

	strVersion.Format (g_cbVersionFormat, TRIASDB_VERSION, TRIASDB_RELEASE, TRIASDB_BUILD);

CComBSTR bstrVersion (strVersion);

	*pVal = bstrVersion.Detach();
	return S_OK;
}


STDMETHODIMP CTRiASDBEngine::put_UserName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrUserName = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASDBEngine::put_Password(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrPassword = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASDBEngine::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::get_Version");

// Wert aus der Registry lesen
CRegKey regKey;
char cbBuffer[_MAX_PATH];
DWORD dwLen = sizeof(cbBuffer);

	if (ERROR_SUCCESS != regKey.Open(HKEY_CLASSES_ROOT, "TRiASDB.TRiASDBEngine.1", KEY_READ) || 
		ERROR_SUCCESS != regKey.QueryValue(cbBuffer, NULL, &dwLen))
	{
		return E_UNEXPECTED;
	}

CComBSTR bstr (cbBuffer);

	if (!bstr)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASDBEngine::get_Projects(ITRiASProjects **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsStarted)
		return REPORT_DBERROR(TRIASDB_E_NOT_STARTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::get_Projects");

WTRiASProjects Prjs (m_Projects);

	*pVal = Prjs.detach();
	return S_OK;
}

STDMETHODIMP CTRiASDBEngine::get_ActiveProject(ITRiASProject **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsStarted)
		return REPORT_DBERROR(TRIASDB_E_NOT_STARTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::get_ActiveProject");

	return m_Projects -> get_ActiveProject(pVal);
}

STDMETHODIMP CTRiASDBEngine::get_ProjectToOpen(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsStarted)
		return REPORT_DBERROR(TRIASDB_E_NOT_STARTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::get_Projects");
	if (0 == m_bstrPrjName.Length())
		return REPORT_DBERROR(TRIASDB_E_NOT_OPENING);

CComBSTR bstrName (m_bstrPrjName);

	if (!bstrName)
		return REPORT_OUTOFMEMORY();
	*pVal = bstrName.Detach();

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods

STDMETHODIMP CTRiASDBEngine::Start (STARTMODE rgMode)
{
	{
		AFX_MANAGE_STATE(AfxGetAppModuleState())

	UINT uiDexCmd = ::RegisterWindowMessage (g_cbTriasExtensionMessage);
	UINT uiDexNfy = ::RegisterWindowMessage (g_cbTriasNotification);
	UINT uiDexxCmd = ::RegisterWindowMessage (g_cbTriasCPPExtensionMessage);
	CWnd *pWnd = AfxGetMainWnd();

		::InitTrias01 (pWnd -> GetSafeHwnd(), uiDexCmd, uiDexNfy, uiDexxCmd);
		::SetCopyrightFlag (FALSE);
		::SetStartMode (rgMode);

	// Anzahl der zu verwendenden GeoDB-Pages setzen
	CRegKey key;

		if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
			ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
			ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
		{
		CRegKey cfgkey;

			if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config"))) {
			DWORD dwData = 0;

				if (ERROR_SUCCESS == cfgkey.QueryValue (dwData, TEXT("NumOfPages")) && 0 != dwData)
					z_setpages (dwData);	// Pageanzahl einstellen
			}
		}
	}
		
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL == g_pDBEngine);	// darf nur einmal gerufen werden
	g_pDBEngine = this;
	g_rgStartMode = rgMode;

	COM_TRY {
		m_Projects = WTRiASProjects(CLSID_TRiASProjects);

		THROW_FAILED_HRESULT(m_Projects -> put_Application (static_cast<ITRiASDBEngine *>(this)));
		THROW_FAILED_HRESULT(m_Projects -> put_Parent (static_cast<ITRiASDBEngine *>(this)));
		THROW_FAILED_HRESULT(m_Projects -> SetEventSink (GetUnknown(), VARIANT_TRUE));

	// singletons instantiieren und initialisieren
		m_Service = WTRiASCSStorageService(CLSID_TRiASCSStorageService);
		m_CookieHolder = WCookieHelper(CLSID_CookieHelper);

		m_ObjMap = WTRiASObjectHandleMap(CLSID_TRiASObjectHandleMap);
		THROW_FAILED_HRESULT(WObjectWithName(m_ObjMap) -> put_Name (CComBSTR(g_cbObjectMap)));

		m_ObjsMap = WTRiASObjectHandleMap(CLSID_TRiASObjectsHandleMap);
		THROW_FAILED_HRESULT(WObjectWithName(m_ObjsMap) -> put_Name (CComBSTR(g_cbObjectsMap)));

		m_FeatureMap = WTRiASObjectHandleMap(CLSID_TRiASFeatureHandleMap);
		THROW_FAILED_HRESULT(WObjectWithName(m_FeatureMap) -> put_Name (CComBSTR(g_cbFeatureMap)));

	} COM_CATCH;

	m_fIsStarted = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Stoppt das unterliegende Datenbanksystem, wird einmal am Ende gerufen.
STDMETHODIMP CTRiASDBEngine::Stop()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	ASSERT(m_fIsStarted);
	if (!m_fIsStarted)
		return REPORT_DBERROR(TRIASDB_E_NOT_STARTED);

	m_Projects -> SetEventSink (GetUnknown(), VARIANT_FALSE);
	m_Projects.Assign(NULL);

// ObjektTabellen abhängen und freigeben
	m_ObjMap -> ShutDown();
	m_ObjMap.Assign(NULL);

	m_ObjsMap -> ShutDown();
	m_ObjsMap.Assign(NULL);

	m_FeatureMap -> ShutDown();
	m_FeatureMap.Assign(NULL);

	m_Service.Assign(NULL);
	m_CookieHolder.Assign(NULL);

	::CleanUpTrias01();
	g_pDBEngine = NULL;				// das letzte vom Tage

#if defined(_USE_PERFMON_COUNTERS)
// PerformanceCounter stoppen
	theApp.StopPerfCounters();
#endif // defined(_USE_PERFMON_COUNTERS)

	return S_OK;
}

static 
CComBSTR EnsureValidProjectName (LPCSTR pcName = NULL, bool fTempDir = true)
{
os_path path;
LPSTR pT = NULL;

	try {
	int iCnt = 0;

		while (true) {
			if (NULL == pcName) {
			CString strNoName;

				ATLTRY(strNoName.Format ((0 == iCnt) ? IDS_NONAME : IDS_NONAME_CNT, iCnt));
				path = (LPCSTR)strNoName;
			} else
				path = pcName;

			path.become_simplified();
			if (!path.has_directory() && fTempDir) {
			// %TMP%-Verzeichnis verwenden
			char cbBuffer[_MAX_PATH];

				if (0 == GetTempPath (sizeof(cbBuffer), cbBuffer)) 
					_com_issue_error (E_UNEXPECTED);

				pT = _tempnam (cbBuffer, g_cbTmpPrefix);

			os_path tmp (pT);

				free (pT);
				path.drive (*tmp.drive().c_str());
				path.directory (tmp.directory());
			}
			if (!path.has_extension())
				path.extension (g_cbRiw);

		struct _stat stat;

			if (0 == _stat (os_string(path).c_str(), &stat) && -1 == _unlink(os_string(path).c_str()))
			// Datei existiert und läßt sich nicht löschen
				iCnt++;
			else
				break;		// ok, Dateiname erzeugt
		}

	} catch (...) {
		if (NULL != pT) 
			free(pT);
		return CComBSTR (g_cbNil);
	}
	return CComBSTR (path);
}

STDMETHODIMP CTRiASDBEngine::CreateProject(BSTR Name, OPENMODE rgMode, ITRiASProject **ppIProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIProject)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::CreateProject");
	*ppIProject = NULL;

	if (OPENMODE_Unknown == rgMode)
		rgMode = OPENMODE_Normal;

	COM_TRY {
	DWORD dwMode = STGM_CREATE | STGM_READWRITE | STGM_SHARE_DENY_WRITE | STGM_TRANSACTED;
	VARIANT_BOOL fTemporary = (rgMode & OPENMODE_ReadOnly) ? VARIANT_TRUE : VARIANT_FALSE;
	CComBSTR bstrName;		// evtl. temporäre datei erzeugen

		USES_CONVERSION;
		if (fTemporary)
			SetType (rgMode, OPENMODE_DoNotAddToMRU);

		if (NULL != Name && SysStringLen(Name) > 0)	// Name ist gegeben
			bstrName = EnsureValidProjectName(OLE2A(Name), false);
		else {
			bstrName = EnsureValidProjectName();
			dwMode |= STGM_DELETEONRELEASE; 
			fTemporary = VARIANT_TRUE;
		}

		Fire_ProjectToCreate(bstrName);		// die Welt in Kenntnis setzen

	WStorage Stg;
	WTRiASProject Prj (CLSID_TRiASProject);

		THROW_FAILED_HRESULT(::StgCreateDocfile (bstrName, dwMode, 0, Stg.ppi()));
		THROW_FAILED_HRESULT(::WriteClassStg (Stg, CLSID_OleDocumentWrapper));

		{
		CScopeVar<CComBSTR> Scope (m_bstrPrjName, bstrName);

			THROW_FAILED_HRESULT(WOleObject(Prj) -> SetClientSite (static_cast<IOleClientSite *>(this)));
			THROW_FAILED_HRESULT(WPersistStorage(Prj) -> InitNew (Stg));
		}

	// jetzt noch interne Daten des Projektes setzen
		THROW_FAILED_HRESULT(Prj -> put_Parent(static_cast<ITRiASDBEngine *>(this)));
		THROW_FAILED_HRESULT(Prj -> put_Application(static_cast<ITRiASDBEngine *>(this)));

		if (NULL != (BSTR)bstrName)
			THROW_FAILED_HRESULT(Prj -> put_Name(bstrName));

		THROW_FAILED_HRESULT(Prj -> put_Updatable(VARIANT_TRUE));
		THROW_FAILED_HRESULT(Prj -> put_OpenedAsCopy(VARIANT_FALSE));
		THROW_FAILED_HRESULT(Prj -> put_Temporary(fTemporary));
		THROW_FAILED_HRESULT(Prj -> put_Mode(rgMode));

		Fire_ProjectCreated (Prj);			// die Welt in Kenntnis setzen

		*ppIProject = Prj.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDBEngine::CreateProjectStg(
	IUnknown *pIUnk, BSTR bstrName, OPENMODE rgMode, ITRiASProject **ppIProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIProject)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::CreateProject");
	*ppIProject = NULL;

	COM_TRY {
	CComBSTR bstrStgName (bstrName);

		if (NULL == bstrName || 0 == SysStringLen(bstrName))
			bstrStgName = EnsureValidProjectName();	// letzte Rettung
		Fire_ProjectToCreate(bstrStgName);			// die Welt in Kenntnis setzen

	WStorage Stg (pIUnk);		// Pointer muß suf ein Stoarge zeigen
	WTRiASProject Prj (CLSID_TRiASProject);

		THROW_FAILED_HRESULT(::WriteClassStg (Stg, CLSID_OleDocumentWrapper));
		{
		CScopeVar<CComBSTR> Scope (m_bstrPrjName, bstrStgName);

			THROW_FAILED_HRESULT(WOleObject(Prj) -> SetClientSite (static_cast<IOleClientSite *>(this)));
			THROW_FAILED_HRESULT(WPersistStorage(Prj) -> InitNew (Stg));
		}

	// jetzt noch interne Daten des Projektes setzen
		THROW_FAILED_HRESULT(Prj -> put_Parent(static_cast<ITRiASDBEngine *>(this)));
		THROW_FAILED_HRESULT(Prj -> put_Application(static_cast<ITRiASDBEngine *>(this)));

		if (NULL != (BSTR)bstrName)
			THROW_FAILED_HRESULT(Prj -> put_Name(bstrStgName));
		if (OPENMODE_Unknown == rgMode)
			rgMode = (OPENMODE)(OPENMODE_DoNotAddToMRU|OPENMODE_HideDocument);

		THROW_FAILED_HRESULT(Prj -> put_Updatable(VARIANT_TRUE));
		THROW_FAILED_HRESULT(Prj -> put_OpenedAsCopy(VARIANT_FALSE));
		THROW_FAILED_HRESULT(Prj -> put_Temporary(VARIANT_FALSE));
		THROW_FAILED_HRESULT(Prj -> put_Mode(rgMode));

		Fire_ProjectCreated (Prj);			// die Welt in Kenntnis setzen
		*ppIProject = Prj.detach();

	} COM_CATCH;
	return S_OK;
}

// Die folgende Funktion wird im allgemeinen in folgendem Kontext benutzt:
//
// HRESULT hr = DBEngine.OpenProject (Name, VARIANT_FALSE, Prj.ppi());
// 
//	if (TRIASDB_S_MUSTOPENASCOPY == hr && AskToOpenCopy())
//		hr = DBEngine.OpenProject (Name, VARIANT_TRUE, Prj.ppi());
//
// D.h. Wenn die Datei bereits genutzt ist, dann muß beim Nutzer nachgefragt
// werden, ob eine Kopie geöffnet werden soll oder eben auch nicht.

STDMETHODIMP CTRiASDBEngine::OpenProject(
	BSTR Name, OPENMODE rgMode, ITRiASProject **ppIProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsStarted)
		return REPORT_DBERROR(TRIASDB_E_NOT_STARTED);
	if (NULL == ppIProject)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::OpenProject");
	*ppIProject = NULL;

	if (OPENMODE_Unknown == rgMode)
		rgMode = OPENMODE_Normal;

BOOL fRO = (OPENMODE_ReadOnly & rgMode) ? TRUE : FALSE;

	USES_CONVERSION;
	COM_TRY {
	// zuerst versuchen entsprechend Flag zu öffnen
	WStorage Stg;
	DWORD dwMode = 0;
	
		if (fRO)
			dwMode = STGM_READ | STGM_SHARE_DENY_NONE;
		else
			dwMode = STGM_READWRITE | (IsNovellDrive(Name) ? STGM_SHARE_DENY_NONE : STGM_SHARE_DENY_WRITE);

		dwMode |= STGM_TRANSACTED;
		if (IsWin40() && !IsWinNT() && !fRO)	// nicht bei RO
			dwMode |= STGM_NOSCRATCH;

	VARIANT_BOOL fOpen = VARIANT_FALSE;			// darf geöffnet werden ?

		THROW_FAILED_HRESULT(Fire_OpeningProject(Name, &fOpen));
		if (fOpen != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler

		THROW_FAILED_HRESULT(Fire_ProjectToOpen(Name));		// die Welt in Kenntnis setzen

	HRESULT hr = ::StgOpenStorage (Name, NULL, dwMode, 0, 0, Stg.ppi());
	bool fOpenedAsCopy = false;

	// wenn das fehlschlägt, explizit RO eröffnen
		if (STG_E_SHAREVIOLATION == hr || STG_E_LOCKVIOLATION == hr) {
		// ZugriffsRechtsÜberschreitung
			if (!fRO && !TestFileRO (OLE2A(Name), fRO)) 	// keine Datei oder existiert nicht
				return REPORT_DBERROR(TRIASDB_E_FILENOTEXISTS);

		// wenn Datei nicht RO geöffnet werden soll oder RO ist, dann wieder raus
			if (!fRO)
				return REPORT_DBERROR(TRIASDB_S_MUSTOPENASCOPY);

		// normal RO öffnen, wenn 
//			if (fRO || AskToOpenCopy()) 
			{
				dwMode = STGM_TRANSACTED|STGM_READ;
				SetType (rgMode, OPENMODE_ReadOnly);

				hr = ::StgOpenStorage (Name, NULL, dwMode, 0, 0, Stg.ppi());
				if (SUCCEEDED(hr))
					fOpenedAsCopy = true;
			// alles ok es geht als Kopie weiter
			//
			} 
//			else
//				return S_FALSE;	// abgebrochen, Nutzer will keine Kopie erstellen
			
		} else if (STG_E_ACCESSDENIED == hr) {
		// lediglich ReadOnly
			if (!TestFileRO (OLE2A(Name), fRO))			// keine Datei oder existiert nicht
				return REPORT_DBERROR(TRIASDB_E_FILENOTEXISTS);

		// Kopie anlegen
			dwMode = STGM_TRANSACTED|STGM_READ;
			SetType (rgMode, OPENMODE_ReadOnly);

			hr = ::StgOpenStorage (Name, NULL, dwMode, 0, 0, Stg.ppi());
			if (SUCCEEDED(hr)) {
			// wenn fRO noch nicht true ist, dann ist die Datei zwar nicht schreibgeschützt,
			// aber sicherlich das Verzeichnis oder die Netzwerkfreigabe
				fRO = true;
				fOpenedAsCopy = true;
			}
		}
		if (FAILED(hr)) 		// sonstiger Fehler
			return REPORT_DBERROR(TRIASDB_E_COULD_NOT_OPEN);

	// überprüfen, ob Datei ein TRiAS Projekt ist
	CLSID ClsId;

		THROW_FAILED_HRESULT(::ReadClassStg(Stg, &ClsId));
		if (!IsEqualCLSID(ClsId, CLSID_OleDocumentWrapper))
			return REPORT_DBERROR(TRIASDB_E_NOTAPROJECT);

	// jetzt Projekt anlegen und initialisieren
	WTRiASProject Prj (CLSID_TRiASProject);
		
		{
		CScopeVar<CComBSTR> Scope (m_bstrPrjName, Name);

			THROW_FAILED_HRESULT(WOleObject(Prj) -> SetClientSite (static_cast<IOleClientSite *>(this)));
			THROW_FAILED_HRESULT(WPersistStorage(Prj) -> Load (Stg));
		}

	// jetzt noch interne Daten des Projektes setzen
		THROW_FAILED_HRESULT(Prj -> put_Parent(static_cast<ITRiASDBEngine *>(this)));
//		THROW_FAILED_HRESULT(Prj -> put_Application(static_cast<ITRiASDBEngine *>(this)));

		THROW_FAILED_HRESULT(Prj -> put_Name(Name));
		THROW_FAILED_HRESULT(Prj -> put_Updatable(fRO ? VARIANT_FALSE : VARIANT_TRUE));
		THROW_FAILED_HRESULT(Prj -> put_OpenedAsCopy(fOpenedAsCopy ? VARIANT_TRUE : VARIANT_FALSE));
		THROW_FAILED_HRESULT(Prj -> put_Mode(rgMode));

		Fire_ProjectOpened (Prj);
		*ppIProject = Prj.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDBEngine::OpenProjectStg(
	IUnknown *pIUnk, BSTR bstrName, OPENMODE rgMode, ITRiASProject **ppIProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsStarted)
		return REPORT_DBERROR(TRIASDB_E_NOT_STARTED);
	if (NULL == ppIProject)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDBEngine::OpenProject");
	*ppIProject = NULL;

	if (OPENMODE_Unknown == rgMode)
		rgMode = (OPENMODE)(OPENMODE_DoNotAddToMRU|OPENMODE_HideDocument);

BOOL fRO = (OPENMODE_ReadOnly & rgMode) ? TRUE : FALSE;

	COM_TRY {
	// zuerst versuchen entsprechend Flag zu öffnen
	WStorage Stg (pIUnk);		// Pointer muß IStorage sein
	CComBSTR bstrStgName (bstrName);

		if (NULL == bstrName || 0 == SysStringLen(bstrName)) {
		STATSTG StatStg;

			THROW_FAILED_HRESULT(Stg -> Stat (&StatStg, STATFLAG_DEFAULT));
			bstrStgName = StatStg.pwcsName;
			CoTaskMemFree (StatStg.pwcsName);
		}

	VARIANT_BOOL fOpen = VARIANT_FALSE;		// darf geöffnet werden ?

		THROW_FAILED_HRESULT(Fire_OpeningProject(bstrStgName, &fOpen));
		if (fOpen != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ProjectToOpen(bstrStgName));		// die Welt in Kenntnis setzen

	// überprüfen, ob Datei ein TRiAS Projekt ist
	CLSID ClsId;

		THROW_FAILED_HRESULT(::ReadClassStg(Stg, &ClsId));
		if (!IsEqualCLSID(ClsId, CLSID_OleDocumentWrapper))
			return REPORT_DBERROR(TRIASDB_E_NOTAPROJECT);

	// jetzt Projekt anlegen und initialisieren
	WTRiASProject Prj (CLSID_TRiASProject);
		
		{
		CScopeVar<CComBSTR> Scope (m_bstrPrjName, bstrStgName);

			THROW_FAILED_HRESULT(WOleObject(Prj) -> SetClientSite (static_cast<IOleClientSite *>(this)));
			THROW_FAILED_HRESULT(WPersistStorage(Prj) -> Load (Stg));
		}

	// jetzt noch interne Daten des Projektes setzen
		THROW_FAILED_HRESULT(Prj -> put_Parent(static_cast<ITRiASDBEngine *>(this)));
//		THROW_FAILED_HRESULT(Prj -> put_Application(static_cast<ITRiASDBEngine *>(this)));

		SetType (rgMode, OPENMODE_DoNotAddToMRU|OPENMODE_HideDocument);
		THROW_FAILED_HRESULT(Prj -> put_Name(bstrStgName));
		THROW_FAILED_HRESULT(Prj -> put_Updatable(fRO ? VARIANT_FALSE : VARIANT_TRUE));
		THROW_FAILED_HRESULT(Prj -> put_OpenedAsCopy(VARIANT_FALSE));
		THROW_FAILED_HRESULT(Prj -> put_Mode(rgMode));

		Fire_ProjectOpened (Prj);
		*ppIProject = Prj.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Enumerator, der alle bekannten Projekttypen enthält
// Zur Zeit werden 2 (3) Projekttypen unterstützt
const LPCOLESTR s_poleTypesSysAdmin[] = {
	g_cbTRiASProject120,
	g_cbTRiASProject130,
#if defined(_DEBUG)
	g_cbTRiASProject3,
#endif // defined(_DEBUG)
};
const LPCOLESTR s_poleTypesNormal[] = {
	g_cbTRiASProject130,
#if defined(_DEBUG)
	g_cbTRiASProject3,
#endif // defined(_DEBUG)
};

STDMETHODIMP CTRiASDBEngine::EnumDataBaseTypes(IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CComObject<CEnumString> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumString>());
	if (NULL == pIEnum) return Error (g_cbNoMemory, E_OUTOFMEMORY);

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
LPOLESTR *ppStringsStart = (LPOLESTR *)&s_poleTypesNormal[0];
LPOLESTR *ppStringsEnd = (LPOLESTR *)&s_poleTypesNormal[_countof(s_poleTypesNormal)];

	if (STARTMODE_CompatibleWithStb & g_rgStartMode) {
		ppStringsStart = (LPOLESTR *)&s_poleTypesSysAdmin[0];
		ppStringsEnd = (LPOLESTR *)&s_poleTypesSysAdmin[_countof(s_poleTypesSysAdmin)];
	}

HRESULT hr = pIEnum -> Init (ppStringsStart, ppStringsEnd, static_cast<ITRiASDBEngine *>(this), AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIEnum);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASDBEngine::SaveObject()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDBEngine::SaveObject");
}

STDMETHODIMP CTRiASDBEngine::GetMoniker (
	DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDBEngine::GetMoniker");
}

STDMETHODIMP CTRiASDBEngine::GetContainer (IOleContainer **ppContainer)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDBEngine::GetContainer");
}

STDMETHODIMP CTRiASDBEngine::ShowObject()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDBEngine::ShowObject");
}

STDMETHODIMP CTRiASDBEngine::OnShowWindow (BOOL fShow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDBEngine::OnShowWindow");
}

STDMETHODIMP CTRiASDBEngine::RequestNewObjectLayout()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDBEngine::RequestNewObjectLayout");
}

///////////////////////////////////////////////////////////////////////////////
// support for AskToContinue
CONTINUEMODE CTRiASDBEngine::AskToContinue (int iCallPriority)
{
CONTINUEMODE rgMode = CONTINUEMODE_Continue;

	_ASSERTE(0 < iCallPriority && iCallPriority <= MAX_ASKTOCONTINUE_COUNT);
	if (0 == m_iCurrAskToContinueCount % iCallPriority)
		Fire_AskToContinue(&rgMode);

	if (++m_iCurrAskToContinueCount > MAX_ASKTOCONTINUE_COUNT)
		m_iCurrAskToContinueCount = 0;
	return rgMode;
}


