// @doc
// @module TRiASProject.cpp | Dieser Modul enthält die Implementation des 
// Objektes <c CTRiASProjekt>, welches einen <tr> Workspace repräsentiert.

#include "stdafx.h"

#include <ospace/file/path.h>
#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>
#include <Com/PropertyWrapper.h>
#include <idl/Collection.h>

#include <zprotos.h>
#include <dbd.hxx>
#include <HeaderEntry.h>
#include <ScopeVar.h>

#include "PersistEnum.h"
#include "Strings.h"
#include "Wrapper.h"		// SmartIF's
#include "TRiASDBGuids.h"
#include "CSFactory.h"

#include "TRiASDBEngine.h"
#include "TRiASProject.h"
#include "TRiASProperty.h"
#include "TRiASConnections.h"
#include "TRiASConnection.h"
#include "TRiASObjectsCollection.h"

// include once in a module
#include "PropertySupportImpl.cpp"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

using namespace trias_nativeheader;

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASProject, CTRiASProject)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCS);				// WTRiASCS
DefineSmartInterface(TRiASMainDBEngine);	// WTRiASMainDBEngine
DefineSmartInterface(TRiASAccessDatabase);	// WTRiASAccessDatabase
DefineSmartInterface(DynamicCollection);	// WDynamicCollection

/////////////////////////////////////////////////////////////////////////////
// {5BEA520E-1E15-49F2-A934-020A5E532B73}
extern "C" const IID __declspec(selectany) CLSID_TRiASDBSubObjects = 
	{0x5bea520e,0x1e15,0x49f2,{0xa9,0x34,0x02,0x0a,0x5e,0x53,0x2b,0x73}};

/////////////////////////////////////////////////////////////////////////////
// CTRiASProject: static data
UINT CTRiASProject::m_cf = ::RegisterClipboardFormat(g_cbProjectData);
UINT CTRiASProject::m_cfWorkSpace = ::RegisterClipboardFormat(g_cbTRiASProject);
UINT CTRiASProject::m_cfObjects = ::RegisterClipboardFormat(g_cbObjectsData);

/////////////////////////////////////////////////////////////////////////////
// spezielle RegistryFunktion
//static _ATL_REGMAP_ENTRY s_regEntryMap[] = 
//{
//	{ L"MAINMODULE", NULL },		// REM_MAINMODULE
//	{ L"FAKETRIASNAME", NULL },		// REM_FAKETRIASNAME
//	{ NULL, NULL },					// EndeKennung
//};
//
//HRESULT WINAPI CTRiASProject::UpdateRegistry (BOOL bRegister)
//{
//HMODULE hTRiAS = GetModuleHandle (NULL);
//TCHAR szModule[_MAX_PATH];
//
//	GetModuleFileName (hTRiAS, szModule, _MAX_PATH);
//
//TCHAR szModuleShort[_MAX_PATH];
//int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
//LPOLESTR pszModule;
//
//	USES_CONVERSION;
//	if (cbShortName == _MAX_PATH)
//		return E_OUTOFMEMORY;
//	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);
//
//	s_regEntryMap[0].szData = pszModule;
//	s_regEntryMap[1].szData = A2OLE(g_cbTRiAS);
//	return _Module.UpdateRegistryFromResource(IDR_TRIASPROJECT, bRegister, s_regEntryMap);
//}

/////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
STDMETHODIMP CTRiASProject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASProject,
	};
	for (unsigned int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASProject::FinalConstruct (void)
{
	return S_OK;
}

void CTRiASProject::FinalRelease (void)
{
	ReleaseSubObjects();

	m_Parent = NULL;
	m_ClientSite.Assign (NULL);
}

HRESULT CTRiASProject::CreateCollections(bool fCreate)
{
	COM_TRY {
	// Properties Collection erzeugen
		if (fCreate)
			THROW_FAILED_HRESULT(CreatePropertiesCollection());

	// Connection Collection erzeugen
		if (!m_Connections) 
			m_Connections = WTRiASConnections (CLSID_TRiASConnections);

	WDispatch App(m_ClientSite);
	WDispatch Parent;

		if (App.IsValid()) 
			THROW_FAILED_HRESULT(m_Connections -> put_Application (App));

		THROW_FAILED_HRESULT(m_Connections -> get_Parent (Parent.ppi()));
		if (!Parent.IsValid()) {
			THROW_FAILED_HRESULT(m_Connections -> put_Parent (static_cast<ITRiASProject *>(this)));
			THROW_FAILED_HRESULT(m_Connections -> SetEventSink (GetUnknown(), VARIANT_TRUE));
		}

	// View Collection erzeugen
		if (!m_Views) 
			m_Views = WTRiASViews (CLSID_TRiASViews);

		if (App.IsValid())
			THROW_FAILED_HRESULT(m_Views -> put_Application (App));

		THROW_FAILED_HRESULT(m_Views -> get_Parent (Parent.ppi()));
		if (!Parent.IsValid()) {
			THROW_FAILED_HRESULT(m_Views -> put_Parent (static_cast<ITRiASProject *>(this)));
			THROW_FAILED_HRESULT(m_Views -> SetEventSink (GetUnknown(), VARIANT_TRUE));
		}

	// QueryDefs Collection erzeugen
		if (!m_QueryDefs)
			m_QueryDefs = WTRiASObjectsCollection (CLSID_TRiASObjectsCollection);

		if (App.IsValid())
			THROW_FAILED_HRESULT(m_QueryDefs -> put_Application (App));

		THROW_FAILED_HRESULT(m_QueryDefs -> get_Parent (Parent.ppi()));
		if (!Parent.IsValid()) {
			THROW_FAILED_HRESULT(m_QueryDefs -> put_Parent (static_cast<ITRiASProject *>(this)));
//			THROW_FAILED_HRESULT(m_QueryDefs -> SetEventSink (GetUnknown(), VARIANT_TRUE));
		}

	// ConnectionFilter Collection erzeugen
		if (!m_ConnFilters)
			m_ConnFilters = WTRiASConnectionFilters (CLSID_TRiASConnectionFilters);

	} COM_CATCH;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objektklassen in allen Datenquellen laden
HRESULT CTRiASProject::LoadObjectsDefs()
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_UNKNOWN));

		WTRiASConnection Conn (V_UNKNOWN(&var));
		CONNECTSTATUS rgMode = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status(&rgMode));
			if (CONNECTSTATUS_Opened == rgMode) {
			WTRiASDatabase DBase;
			WTRiASObjectsCollection ObjsDefs;

				THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
				THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs(ObjsDefs.ppi()));
			}
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Nach einem Load die überfälligen Connects abarbeiten
HRESULT CTRiASProject::ConnectAll (void)
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		CTRiASConnection::ResetAskModeOpenRO();		// wieder neu fragen
		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_UNKNOWN));

		WTRiASConnection Conn (V_UNKNOWN(&var));
		HRESULT hr = S_OK;

			if (FAILED(hr = Conn -> Connect (CONNECTMODE_ConnectAfterLoadIfApplicable))) {
			// konnte nicht wieder geöffnet werden
			CComBSTR bstrName (g_cbNil);

				Conn -> get_Name (&bstrName);
				VMessageBox (FakeTRiASName (IDS_OPENPROJECTCAP, g_cbTRiAS).c_str(), 
					MB_TASKMODAL|MB_ICONEXCLAMATION, IDS_COULDNOTREOPENCONNECTION, bstrName, hr);
			}
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Beim Schließen alle Connections abkoppeln
HRESULT CTRiASProject::DisconnectAll (VARIANT_BOOL fCommit)
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		CTRiASConnection::ResetAskModeSave();
		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) {
		// alle existierenden Connections durchgehen
			THROW_FAILED_HRESULT(var.ChangeType (VT_UNKNOWN));

		WTRiASConnection Conn (V_UNKNOWN(&var));

		// nur geöffnete Connection schließen
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));

			if (CONNECTSTATUS_Opened == rgStatus) {
			// Mode fürs schließen berechnen
			CONNECTMODE rgMode, rgModeMod;

				if (SUCCEEDED(Conn -> get_Mode (&rgMode))) {
					rgModeMod = (CONNECTMODE)(rgMode & ~CONNECTMODE_CloseResolutionFlags);
					if (fCommit) 
						SetType (rgModeMod, CONNECTMODE_CloseUserResolves);
					else 
						SetType (rgModeMod, CONNECTMODE_CloseNoResolution);
				} else
					rgModeMod = CONNECTMODE_CloseNoResolution;

			HRESULT hr = Conn -> Disconnect (rgModeMod);

				THROW_FAILED_HRESULT(hr);
				if (hr == S_FALSE) return S_FALSE;		// Nutzer hat abgebrochen
			}
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASProject::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = CLSID_OleDocumentWrapper;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStorage
STDMETHODIMP CTRiASProject::IsDirty (void)
{
	COM_TRY {
		if (S_OK == WPersistStorage(m_Connections) -> IsDirty())
			return S_OK;

		if (S_OK == WPersistStorage(m_Views) -> IsDirty())
			return S_OK;

		if (S_OK == WPersistStorage(m_QueryDefs) -> IsDirty())
			return S_OK;

		if (S_OK == WPersistStorage(m_ConnFilters) -> IsDirty())
			return S_OK;

	} COM_CATCH;

	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASProject::InitNew (IStorage *pIStg)
{
	if (m_fIsInitialized || NULL != (IStorage *)m_Stg)
		return E_UNEXPECTED;

	USES_CONVERSION;
	COM_TRY {
	// zwar noch nicht initialisiert, aber immerhin gerade dabei
	CScopeVar<bool> Scope(m_fIsInitializing, true);
	
	// erste rudimentäre StorageVorbereitungen
		THROW_FAILED_HRESULT(::WriteFmtUserTypeStg(pIStg, m_cf, A2OLE(g_cbProjectData)));
	
	// eigenen SubStream erzeugen
	WStream Strm;

		THROW_FAILED_HRESULT(GetSubStream (pIStg, A2OLE(g_cbProjectData), Strm.ppi(), true));

		THROW_FAILED_HRESULT(SaveLong(Strm, PROJECTFILE_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong(Strm, LASTKNOWN_PROJECTFILE_VERSION));

	// eigene Database erzeugen und öffnen
		THROW_FAILED_HRESULT(CreateDatabase (pIStg));
		THROW_FAILED_HRESULT(OpenDatabase (pIStg));

		THROW_FAILED_HRESULT(SaveEnumeratedItems (GetProperties(), Strm, &FMTID_EnumProperties, (ITRiASProperty *)NULL));

	// jetzt substorages etc. initialisieren
		{
		// SubObjekte
		WStorage SubStg;
		DWORD rgStgc = STGC_DEFAULT;
			
			if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;

			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbObjects, CLSID_TRiASDBSubObjects, SubStg.ppi(), true));
			THROW_FAILED_HRESULT(::WriteFmtUserTypeStg(SubStg, m_cfObjects, A2OLE(g_cbObjectsData)));
			THROW_FAILED_HRESULT(LocalConnections_InitNew (SubStg));
			THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));
			m_ObjectStg = SubStg;

		// Connections
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnections, CLSID_CObjectManagement, SubStg.ppi(), true));
			THROW_FAILED_HRESULT(WPersistStorage(m_Connections) -> InitNew (SubStg));
			THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));
			m_ConnStg = SubStg;

		// Ausgabe-Koordinatensystem und Transformator anlegen und initialisieren
			THROW_FAILED_HRESULT(InitCoordSystemService());
			THROW_FAILED_HRESULT(ConnectCookieHolder());

		// Ansichten
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbViews, CLSID_CObjectManagement, SubStg.ppi(), true));
			THROW_FAILED_HRESULT(WPersistStorage(m_Views) -> InitNew (SubStg));
			THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));
			m_ViewStg = SubStg;

		// QueryDefs
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbQueries, CLSID_CObjectManagement, SubStg.ppi(), true));
			THROW_FAILED_HRESULT(WPersistStorage(m_QueryDefs) -> InitNew (SubStg));
			THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));
			m_QueryStg = SubStg;

		// ConnectFilts
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnFilts, CLSID_CObjectManagement, SubStg.ppi(), true));
			THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> InitNew (SubStg));
			THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));
			m_ConnFiltStg = SubStg;
		}

	// erfolgreich initialisiert
		m_Stg = pIStg;
		m_Strm = Strm;
		m_StgMode = STGMODE_Normal;

	} COM_CATCH_EX(e) {
		m_Strm.Assign(NULL);
		m_Stg.Assign(NULL);
		m_ConnStg.Assign(NULL);
		m_ViewStg.Assign(NULL);
		m_QueryStg.Assign(NULL);
		m_ConnFiltStg.Assign(NULL);
		m_ObjectStg.Assign(NULL);
		return _COM_ERROR(e);
	} 

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASProject::CreateDatabase (IStorage *pIStg)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (IDR_DBDRIW, dwResSize);

	if (NULL == lpRes)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CDBDictCompoundFile *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// SubStorage erzeugen
	WStorage SubStg;
	DWORD dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;
	LPCOLESTR poleName = A2OLE(g_cbProjectDataBase);
	HRESULT hr = pIStg -> OpenStorage (poleName, NULL, dwMode, NULL, 0, SubStg.ppi());

		if (FAILED(hr)) {	
			if (STG_E_FILENOTFOUND == hr) {
			// existiert noch nicht, anlegen
				dwMode |= STGM_CREATE;
				THROW_FAILED_HRESULT(pIStg -> CreateStorage (poleName, dwMode, 0, 0, SubStg.ppi()));
			} else
				_com_issue_error(hr);			// sonstiger Fehler
		}

	// TRiAS® 3.0 Projekt Workspace
		ATLTRY(pDBDict = CDBDictCompoundFile::CreateInstance (lpRes, FALSE));	// #HK001030: now compressed
		if (pDBDict == NULL) 
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	IStorage *pISubStg = SubStg;	// nur temporär kopieren
	ErrCode EC = pDBDict -> CreateDBEx (NULL, NULL, NULL, &pISubStg,
								&CLSID_OleDocumentWrapper, g_cbProjectData);
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	// alles Speichern			
	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	}

	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

HRESULT CTRiASProject::OpenDatabase (IStorage *pIStg)
{
	USES_CONVERSION;
	COM_TRY {
	WStorage SubStg;
	LPOLESTR poleName = A2OLE(g_cbProjectDataBase);

		THROW_FAILED_HRESULT(GetSubStorage (pIStg, poleName, CLSID_OleDocumentWrapper, SubStg.ppi()));

	bool fRO = m_fIsReadOnly;

		m_hPr = OpenDB(SubStg, fRO);

	// Properties neu einlesen 
		THROW_FAILED_HRESULT(CreateCollections (true));

	// Datenbank rücksetzen
		::SetDirty (m_hPr, FALSE);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProject::Load (IStorage *pIStg)
{
	if (m_fIsInitialized || NULL != (IStorage *)m_Stg || NULL != m_hPr)
		return E_UNEXPECTED;

bool fDirty = false;

	USES_CONVERSION;
	COM_TRY {
	// zwar noch nicht initialisiert, aber immerhin gerade dabei
	CScopeVar<bool> Scope(m_fIsInitializing, true);
	
	// eigene Daten einlesen
	WStream Strm;

		THROW_FAILED_HRESULT(GetSubStream (pIStg, A2OLE(g_cbProjectData), Strm.ppi()));

	long lSignature = 0L;

		THROW_FAILED_HRESULT(LoadLong (Strm, lSignature));			// Signatur
		ERROR_EXPR_TRUE(PROJECTFILE_SIGNATURE != lSignature, TRIASDB_E_BADOBJECTSIGNATURE);

		THROW_FAILED_HRESULT(LoadLong(Strm, m_lVersion));
		ERROR_EXPR_TRUE((m_lVersion & ~PROJECTFILE_VERSION_MINOR_MASK) > LASTKNOWN_PROJECTFILE_VERSION, TRIASDB_W_NEWERPROJECT);

	// Datenbank öffnen
		THROW_FAILED_HRESULT(OpenDatabase(pIStg));

		THROW_FAILED_HRESULT(LoadEnumeratedItems (GetProperties(), Strm, &FMTID_EnumProperties, (ITRiASProperty *)NULL, PROJECTFILE_VERSION_301 <= m_lVersion));

	// die Welt in Kenntnis setzen (das Projekt ist hier ja geöffnet ...)
		THROW_FAILED_HRESULT(g_pDBEngine -> Fire_ProjectIsOpening(GetDispatch()));

	// jetzt Daten aus Substorages laden 
		{
		// SubObjekte
		WStorage SubStg;

			if (SUCCEEDED(GetSubStorage (pIStg, g_cbObjects, CLSID_TRiASDBSubObjects, SubStg.ppi())))
			{
				THROW_FAILED_HRESULT(LocalConnections_Load (SubStg));
				m_ObjectStg = SubStg;
			}

		// Connections
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnections, CLSID_CObjectManagement, SubStg.ppi()));
			THROW_FAILED_HRESULT(WPersistStorage(m_Connections) -> Load (SubStg));
			m_ConnStg = SubStg;

		// Ausgabe-Koordinatensystem und Transformator anlegen und initialisieren
			THROW_FAILED_HRESULT(InitCoordSystemService());

		// die existierenden Connections sind noch nicht mit ihren Datenbanken verbunden
		// das holen wir hier nach (muß passieren bevor die nachfolgenden Objekte 
		// instantiiert werden, da diese evtl. die Database-Moniker benötigen)
			THROW_FAILED_HRESULT(ConnectCookieHolder());
			THROW_FAILED_HRESULT(ConnectAll());

		// Cookies verwalten
			THROW_FAILED_HRESULT(RetrieveLastCookie());
			
		// Ansichten
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbViews, CLSID_CObjectManagement, SubStg.ppi()));
			THROW_FAILED_HRESULT(WPersistStorage(m_Views) -> Load (SubStg));
			m_ViewStg = SubStg;

		// QueryDefs
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbQueries, CLSID_CObjectManagement, SubStg.ppi()));
			THROW_FAILED_HRESULT(WPersistStorage(m_QueryDefs) -> Load (SubStg));
			m_QueryStg = SubStg;

		// ConnectFilts
			if ((m_lVersion >= PROJECTFILE_VERSION_302)) {
			// nur laden, wenn nicht zu altes Projekt
				if (SUCCEEDED(GetSubStorage (pIStg, g_cbConnFilts, CLSID_CObjectManagement, 
					SubStg.ppi())))
				{
					THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> Load (SubStg));
				}
			}
			else {
			// nachfolgendes Neuerzeugen triggern
				SubStg.Assign(NULL);
			}
		
		// ggf. eben neu erzeugen
			if (!SubStg.IsValid()) {
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnFilts, CLSID_CObjectManagement, 
					SubStg.ppi(), true));
				THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> InitNew (SubStg));

			DWORD rgStgc = STGC_DEFAULT;
				
				if (IsWin50() && IsWinNT()) 
					rgStgc |= STGC_CONSOLIDATE;
				THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));
				fDirty = true;
			}
			m_ConnFiltStg = SubStg;
		}

	// jetzt ist unser Storage gültig
		m_Stg = pIStg;
		m_Strm = Strm;
		m_StgMode = STGMODE_Normal;

	} COM_CATCH_OP(
	// die Welt von dem Fehler in Kenntnis setzen
		THROW_FAILED_HRESULT(g_pDBEngine -> Fire_ErrorOpeningProject(GetDispatch()));
		CloseDB(true);
	);

	m_fIsDirty = fDirty;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
HRESULT CTRiASProject::CloseDB (bool fFullRelease)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

HRESULT hr = S_OK;
ErrCode RC = EC_OKAY;

// Datenbank schließen
	{
	CActDB ActDB (m_hPr);

		RC = (ErrCode)z_close (m_hPr, false);	// DB schließen
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPr = NULL;
		ActDB.Reset();
	}

	COM_TRY {
		GetProperties() -> put_Parent (NULL);
		GetProperties() -> SetEventSink (GetUnknown(), VARIANT_FALSE);

		m_Connections -> put_Parent (NULL);
		m_Connections -> SetEventSink (GetUnknown(), VARIANT_FALSE);

		m_Views -> put_Parent (NULL);
		m_Views -> SetEventSink (GetUnknown(), VARIANT_FALSE);

		m_QueryDefs -> put_Parent (NULL);
	//	m_QueryDefs -> SetEventSink (GetUnknown(), VARIANT_FALSE);

		THROW_FAILED_HRESULT(DisconnectCookieHolder());

	} COM_CATCH;

	if (fFullRelease) 
		ReleaseSubObjects();
	return hr;
}

HRESULT CTRiASProject::ReleaseSubObjects()
{
// Member freigeben
	COM_TRY {
		FreePropertiesCollection();		// alles aufräumen

		m_Connections.Assign(NULL);
		m_Views.Assign(NULL);
		m_QueryDefs.Assign(NULL);
		m_ConnFilters.Assign(NULL);

		m_bstrName.Empty();

// globale HandleTabellen leeren
		{
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());		// throws hr

			THROW_FAILED_HRESULT(Map -> RemoveObject (NULL, OBJECTMAPMODE_RemoveAllObjects));
		}
		{
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());			// throws hr

			THROW_FAILED_HRESULT(Map -> RemoveObject (NULL, OBJECTMAPMODE_RemoveAllObjects));
		}
		{
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetFeaturesMap());		// throws hr

			THROW_FAILED_HRESULT(Map -> RemoveObject (NULL, OBJECTMAPMODE_RemoveAllObjects));
		}

	} COM_CATCH;
	return S_OK;
}

HPROJECT CTRiASProject::OpenDB (IStorage *pIStg, bool &rfReadOnly) throw (_com_error)
{
	if (NULL == pIStg) _com_issue_error(E_POINTER);

HPROJECT hPr = (HPROJECT)z_open_storage_ex (pIStg, rfReadOnly ? TRUE : FALSE, FALSE, &CLSID_OleDocumentWrapper);

	if (NULL == hPr && !rfReadOnly) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// muß ReadOnly geöffnet werden
			rfReadOnly = true;
			hPr = (HPROJECT)z_open_storage_ex (pIStg, TRUE, FALSE, &CLSID_OleDocumentWrapper);
		}
		if (NULL == hPr)		// erfolgloser Versuch
			_com_issue_error(HRESULT_FROM_ERRCODE(EC_NOOPEN));
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (rfReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY);  /*lint !e569, !e534*/	// DB ReadOnly

	return hPr;
}

STDMETHODIMP CTRiASProject::Save (IStorage *pIStg, BOOL fSameAsLoad)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	_ASSERTE(STGMODE_Normal == m_StgMode);
	_ASSERTE(m_Connections.IsValid());
	_ASSERTE(m_Views.IsValid());
	_ASSERTE(m_QueryDefs.IsValid());
	_ASSERTE(m_ConnFilters.IsValid());

	USES_CONVERSION;
	COM_TRY {
	// Cookies verwalten
		THROW_FAILED_HRESULT(SaveLastCookie());

	// Die Welt in Kenntnis setzen
		{
			_ASSERTE(NULL != g_pDBEngine);

		VARIANT_BOOL fSame = fSameAsLoad ? VARIANT_TRUE : VARIANT_FALSE;
		WUnknown UnkStg (pIStg);

			THROW_FAILED_HRESULT(g_pDBEngine -> Fire_Save (static_cast<ITRiASProject *>(this), UnkStg, fSame));
		}

		THROW_FAILED_HRESULT(::WriteFmtUserTypeStg(pIStg, m_cfWorkSpace, A2OLE(g_cbTRiASProject)));

	// eigenen SubStream speichern
		_ASSERTE(NULL != (IStream *)m_Strm);
		if (!fSameAsLoad) {
			THROW_FAILED_HRESULT(GetSubStream (pIStg, A2OLE(g_cbProjectData), m_Strm.ppi(), true));
		} else {
		// Stream zurückstellen
		LARGE_INTEGER li;

			LISet32 (li, 0);
			THROW_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
		}
		THROW_FAILED_HRESULT(SaveLong(m_Strm, PROJECTFILE_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong(m_Strm, LASTKNOWN_PROJECTFILE_VERSION));
		THROW_FAILED_HRESULT(SaveEnumeratedItems (GetProperties(), m_Strm, &FMTID_EnumProperties, (ITRiASProperty *)NULL));

	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(m_Strm -> Commit (rgStgc));

	// eigene DatenBank speichern
		if (fSameAsLoad) {
		// DB aktivieren
		CActDB Act (m_hPr);

			THROW_FAILED_ERRCODE(DBFlush(m_hPr, FLUSH_ACTDB));								// alles wegschreiben
			THROW_FAILED_ERRCODE(DBPageZeroFlush(m_hPr, FLUSH_ACTDB|FLUSH_COMMITDATA));		// PageZero's auch wegschreiben

			::SetDirty (m_hPr, FALSE);

		} else {
		WStorage SubStg;
		LPOLESTR poleName = A2OLE(g_cbProjectDataBase);

			THROW_FAILED_HRESULT(GetSubStorage (pIStg, poleName, CLSID_OleDocumentWrapper, SubStg.ppi(), true));

		HRESULT hr = CopyToStorageProject (m_hPr, g_cbProjectDataBase, reinterpret_cast<IStorage **>(&SubStg), &CLSID_OleDocumentWrapper, g_cbTRiASDBProject);

			if (FAILED(hr)) {
				THROW_FAILED_HRESULT(SubStg -> DestroyElement (poleName));
			} else {
				THROW_FAILED_HRESULT(SubStg -> Commit(rgStgc));
			}
		}

	// Daten in Substorages speichern
		{
		// SubObjekte
		WStorage Stg;

			if (!fSameAsLoad || !m_ObjectStg.IsValid()) {
			HRESULT hr = S_OK;

				THROW_FAILED_HRESULT(hr = GetSubStorage (pIStg, g_cbObjects, CLSID_TRiASDBSubObjects, Stg.ppi(), true));
				if (S_FALSE == hr)
				{
					THROW_FAILED_HRESULT(::WriteFmtUserTypeStg(Stg, m_cfObjects, A2OLE(g_cbObjectsData)));
				}
			} else 
				Stg = m_ObjectStg;	//.detach();

			THROW_FAILED_HRESULT(LocalConnections_Save (Stg, fSameAsLoad));
			THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));
			m_ObjectStg = Stg;

		// Ansichten
			if (!fSameAsLoad) {
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbViews, CLSID_CObjectManagement, Stg.ppi(), true));
			} else 
				Stg = m_ViewStg;	//.detach();

			THROW_FAILED_HRESULT(WPersistStorage(m_Views) -> Save (Stg, fSameAsLoad));
			THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));
			m_ViewStg = Stg;

		// Queries
			if (!fSameAsLoad) {
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbQueries, CLSID_CObjectManagement, Stg.ppi(), true));
			} else 
				Stg = m_QueryStg;	//.detach();

			THROW_FAILED_HRESULT(WPersistStorage(m_QueryDefs) -> Save (Stg, fSameAsLoad));
			THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));
			m_QueryStg = Stg;

		// ConnFilts
			if (!fSameAsLoad) {
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnFilts, CLSID_CObjectManagement, Stg.ppi(), true));
			} else 
				Stg = m_ConnFiltStg;	//.detach();

			THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> Save (Stg, fSameAsLoad));
			THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));
			m_ConnFiltStg = Stg;

		// Connections (als letztes speichern, da hier u.U. die Datenbanken geschlossen/wieder geöffnet werden)
			if (!fSameAsLoad) {
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnections, CLSID_CObjectManagement, Stg.ppi(), true));
			} else 
				Stg = m_ConnStg;	//.detach();

			THROW_FAILED_HRESULT(WPersistStorage(m_Connections) -> Save (Stg, fSameAsLoad));
			THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));
			m_ConnStg = Stg;
		}
		if (!fSameAsLoad) 
			m_Stg = pIStg;

		m_fIsDirty = false;
		m_StgMode = STGMODE_NoScribble;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProject::SaveCompleted (IStorage *pIStg)
{
	if (!m_fIsInitialized || STGMODE_Normal == m_StgMode)
		return E_UNEXPECTED;

	_ASSERTE(STGMODE_NoScribble == m_StgMode || (STGMODE_HandsOff & m_StgMode));
	_ASSERTE(NULL != g_pDBEngine);

	USES_CONVERSION;
	COM_TRY {
		if (NULL == pIStg) {
			if (STGMODE_HandsOff & m_StgMode) 
				return E_POINTER;

		// Die Welt in Kenntnis setzen
		CComVariant Stg (DISP_E_PARAMNOTFOUND, VT_ERROR);

			THROW_FAILED_HRESULT(g_pDBEngine -> Fire_SaveCompleted (static_cast<ITRiASProject *>(this), Stg));

			THROW_FAILED_HRESULT(LocalConnections_SaveCompleted (NULL));
			THROW_FAILED_HRESULT(WPersistStorage(m_Connections) -> SaveCompleted (NULL));
			THROW_FAILED_HRESULT(WPersistStorage(m_Views) -> SaveCompleted (NULL));
			THROW_FAILED_HRESULT(WPersistStorage(m_QueryDefs) -> SaveCompleted (NULL));
			THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> SaveCompleted (NULL));

		} else {
		// etvl. HandsOffStorage simulieren
			if (STGMODE_NoScribble == m_StgMode)
				THROW_FAILED_HRESULT(CTRiASProject::HandsOffStorage());

		// jetzt alles wieder aufmachen
		WStream Strm;

			THROW_FAILED_HRESULT(GetSubStream (pIStg, A2OLE(g_cbProjectData), Strm.ppi()));

		// Datenbank wieder öffnen
			THROW_FAILED_HRESULT(OpenDatabase(pIStg));

		// vorheriges Storage freigeben, neues geben lassen
			{
			// SubObjekte
			WStorage Stg;

				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbObjects, CLSID_TRiASDBSubObjects, Stg.ppi()));
				THROW_FAILED_HRESULT(LocalConnections_SaveCompleted (Stg));
				m_ObjectStg = Stg;

			// Connections
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnections, CLSID_CObjectManagement, Stg.ppi()));
				THROW_FAILED_HRESULT(WPersistStorage(m_Connections) -> SaveCompleted (Stg));
				m_ConnStg = Stg;

				THROW_FAILED_HRESULT(InitCoordSystemService());
				THROW_FAILED_HRESULT(ConnectCookieHolder());

			// Ansichten
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbViews, CLSID_CObjectManagement, Stg.ppi()));
				THROW_FAILED_HRESULT(WPersistStorage(m_Views) -> SaveCompleted (Stg));
				m_ViewStg = Stg;

			// QueryDefs
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbQueries, CLSID_CObjectManagement, Stg.ppi()));
				THROW_FAILED_HRESULT(WPersistStorage(m_QueryDefs) -> SaveCompleted (Stg));
				m_QueryStg = Stg;

			// QueryDefs
				THROW_FAILED_HRESULT(GetSubStorage (pIStg, g_cbConnFilts, CLSID_CObjectManagement, Stg.ppi()));
				THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> SaveCompleted (Stg));
				m_ConnFiltStg = Stg;
			}

			m_Strm = Strm;
			m_Stg = pIStg;

		// Die Welt in Kenntnis setzen
		CComVariant Stg (pIStg);

			THROW_FAILED_HRESULT(g_pDBEngine -> Fire_SaveCompleted (static_cast<ITRiASProject *>(this), Stg));
		}

	// Properties neu einlesen 
		THROW_FAILED_HRESULT(CreateCollections());

	// nur, wenn alles glatt gegangen ist
		m_fIsDirty = false;
		m_StgMode = STGMODE_Normal;

	} COM_CATCH_OP(((NULL != pIStg) ? m_Stg.Assign(NULL) : pIStg = NULL));
	return S_OK;
}

STDMETHODIMP CTRiASProject::HandsOffStorage (void)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	_ASSERTE(NULL != g_pDBEngine);
	COM_TRY {
	// Die Welt in Kenntnis setzen
		THROW_FAILED_HRESULT(g_pDBEngine -> Fire_HandsOffStorage (static_cast<ITRiASProject *>(this)));

		THROW_FAILED_HRESULT(LocalConnections_HandsOffStorage());
		THROW_FAILED_HRESULT(WPersistStorage(m_Connections) -> HandsOffStorage());
		THROW_FAILED_HRESULT(WPersistStorage(m_Views) -> HandsOffStorage());
		THROW_FAILED_HRESULT(WPersistStorage(m_QueryDefs) -> HandsOffStorage());
		THROW_FAILED_HRESULT(WPersistStorage(m_ConnFilters) -> HandsOffStorage());

		THROW_FAILED_HRESULT(CloseDB (false));		// nur Hände heben

		m_Strm.Assign(NULL);

		m_ObjectStg.Assign(NULL);
		m_ConnStg.Assign(NULL);
		m_ViewStg.Assign(NULL);
		m_QueryStg.Assign(NULL);
		m_ConnFiltStg.Assign(NULL);

		m_Stg.Assign(NULL);

		if (STGMODE_Normal == m_StgMode)
			m_StgMode = STGMODE_HandsOffAfterNormal;
		else if (STGMODE_NoScribble == m_StgMode)
			m_StgMode = STGMODE_HandsOffAfterSave;
		else {
			_ASSERTE(STGMODE_NoScribble == m_StgMode || STGMODE_Normal == m_StgMode);
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// support IPersistStorage for all connections, which support IPersistStorage
HRESULT CTRiASProject::LocalConnections_InitNew(IStorage *pIStg)
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_DISPATCH));

		WTRiASConnection Conn (V_DISPATCH(&var));
		WTRiASDatabase Dbase;
		WPersistStorage ps;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));
			if (SUCCEEDED(Dbase -> QueryInterface (ps.ppi())))
				ps -> InitNew (pIStg);		// ignore errors
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::LocalConnections_Save (IStorage *pIStg, BOOL fSameAsLoad)
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_DISPATCH));

		WTRiASConnection Conn (V_DISPATCH(&var));
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened != rgStatus)
				continue;		// nur geöffnete DB's untersuchen

		WTRiASDatabase Dbase;
		WPersistStorage ps;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));
			if (SUCCEEDED(Dbase -> QueryInterface (ps.ppi())))
				ps -> Save (pIStg, fSameAsLoad);		// ignore errors
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::LocalConnections_SaveCompleted (IStorage *pIStg)
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_DISPATCH));

		WTRiASConnection Conn (V_DISPATCH(&var));
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened != rgStatus)
				continue;		// nur geöffnete DB's untersuchen

		WTRiASDatabase Dbase;
		WPersistStorage ps;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));
			if (SUCCEEDED(Dbase -> QueryInterface (ps.ppi())))
				ps -> SaveCompleted (pIStg);		// ignore errors
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::LocalConnections_Load (IStorage *pIStg)
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_DISPATCH));

		WTRiASConnection Conn (V_DISPATCH(&var));
		WTRiASDatabase Dbase;
		WPersistStorage ps;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));
			if (SUCCEEDED(Dbase -> QueryInterface (ps.ppi())))
				ps -> Load (pIStg);			// ignore errors
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::LocalConnections_HandsOffStorage()
{
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			THROW_FAILED_HRESULT(var.ChangeType (VT_DISPATCH));

		WTRiASConnection Conn (V_DISPATCH(&var));
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened != rgStatus)
				continue;		// nur geöffnete DB's untersuchen

		WTRiASDatabase Dbase;
		WPersistStorage ps;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));
			if (SUCCEEDED(Dbase -> QueryInterface (ps.ppi())))
				ps -> HandsOffStorage();			// ignore errors
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASProject::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::get_Application");
	TEST_OUT_PARAM(pVal);

	COM_TRY {
	WDispatch App (m_ClientSite);

		*pVal = App.detach();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProject::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
		m_ClientSite = newVal;

		if (m_Connections.IsValid())
			THROW_FAILED_HRESULT(m_Connections -> put_Application (newVal));
		if (m_Views.IsValid())
			THROW_FAILED_HRESULT(m_Views -> put_Application (newVal));
		if (m_QueryDefs.IsValid())
			THROW_FAILED_HRESULT(m_QueryDefs -> put_Application (newVal));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASProject::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Parent = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Version(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Version");
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	*pVal = m_lVersion;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Name");
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

CComBSTR bstrVal (m_bstrName);

	if (!bstrVal) 
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	*pVal = bstrVal.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASProject::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	m_bstrName = newVal;
	if (!m_bstrName) 
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Updatable(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Updateable");
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	*pVal = m_fIsReadOnly ? VARIANT_FALSE : VARIANT_TRUE;	
	return S_OK;
}


STDMETHODIMP CTRiASProject::put_Updatable(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_fIsReadOnly = newVal ? false : true;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Temporary(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Updateable");
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	*pVal = m_fIsTemporary ? VARIANT_TRUE : VARIANT_FALSE;	
	return S_OK;
}


STDMETHODIMP CTRiASProject::put_Temporary(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_fIsTemporary = newVal ? true : false;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_OpenedAsCopy(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_OpenedAsCopy");
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	*pVal = m_fIsOpenedAsCopy ? VARIANT_TRUE : VARIANT_FALSE;	
	return S_OK;
}

STDMETHODIMP CTRiASProject::put_OpenedAsCopy(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_fIsOpenedAsCopy = newVal ? true : false;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_CouldOpenTarget(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_CouldOpenTarget");

CActDB ActDB (m_hPr);
BOOL fCouldOpenTarget = FALSE;

	if (!::CouldOpenTarget (m_hPr, &fCouldOpenTarget))
		return REPORT_DBERROR(E_UNEXPECTED);

	*pVal = fCouldOpenTarget ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Connections(ITRiASConnections **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized && !m_fIsInitializing) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Connections");

WTRiASConnections Conns (m_Connections);

	*pVal = Conns.detach();
	return m_fIsInitialized ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASProject::get_Connection(VARIANT vItem, ITRiASConnection **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Connection");

	if (!m_Connections)
		return E_UNEXPECTED;
	return m_Connections -> Item (vItem, pVal);
}

STDMETHODIMP CTRiASProject::get_Views(ITRiASViews **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Views");

WTRiASViews Views (m_Views);

	*pVal = Views.detach();
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_View (BSTR bstrName, VARIANT_BOOL fCreate, ITRiASView **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_View");

HRESULT hr = E_FAIL;

	COM_TRY {
		hr = m_Views -> Item (CComVariant(bstrName), pVal);
		if (TRIASDB_E_UNKNOWN_VIEW == hr && fCreate) {	// evtl. neu erzeugen
			hr = m_Views -> Add (bstrName, pVal);
			if (S_OK == hr) hr = S_FALSE;				// Ansicht wurde neu erzeugt
		}
	} COM_CATCH;
	return hr;
}

STDMETHODIMP CTRiASProject::get_Handle(INT_PTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Handle");

	*pVal = (LONG)m_hPr;
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Dirty(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Dirty");

	*pVal = (S_OK == CTRiASProject::IsDirty()) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASProject::put_Dirty(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_fIsDirty = newVal ? true : false;
	if (NULL != m_hPr)
		::SetDirty (m_hPr, m_fIsDirty);
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Activated(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Activated");

	*pVal = m_fActivated ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASProject::put_Activated(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_fActivated = newVal ? true : false;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASProject::Close(VARIANT_BOOL fCommit)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	_ASSERTE(NULL != g_pDBEngine);

CComBSTR bstrName (m_bstrName);		// kopieren, damit Fire_... funktionieren kann

	COM_TRY {
		{
		CPropertyWrapper PropWrap (GetPropertyBase(), g_cbClosingProject, VARIANT_TRUE);
		
		// soll geschlossen werden ?
		VARIANT_BOOL fClose = VARIANT_FALSE;

			THROW_FAILED_HRESULT(g_pDBEngine -> Fire_ClosingProject (GetDispatch(), &fClose));
			if (fClose != VARIANT_FALSE)
				return S_FALSE;		// abgebrochen oder Fehler

		// wenn gespeichert werden soll, dann dieses hier tun
		HRESULT hr_disconnectall = S_OK;

			if (fCommit) {
				_ASSERTE(NULL != (IStorage *)m_Stg);
				if (STGMODE_Normal != m_StgMode)
					return REPORT_DBERROR(TRIASDB_E_CANNOTSAVE_AT_THIS_POINT);

				THROW_FAILED_HRESULT(CTRiASProject::Save (m_Stg, true));

			// alle Connections schließen, hier _nach_ Save, da Save auch den Status
			// der Connections speichert
				hr_disconnectall = DisconnectAll(VARIANT_TRUE);
				THROW_FAILED_HRESULT(hr_disconnectall);

			// jetzt alles festschreiben
			DWORD rgStgc = STGC_DEFAULT;
				
				if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
				THROW_FAILED_HRESULT(m_Stg -> Commit (rgStgc));
			} else {
			// lediglich alle Connections schließen
				hr_disconnectall = DisconnectAll(VARIANT_FALSE);
				THROW_FAILED_HRESULT(hr_disconnectall);
			}

			if (S_FALSE == hr_disconnectall) {
				CTRiASProject::SaveCompleted(NULL);	// wieder gültig machen
				return S_FALSE;			// Nutzer hat abgebrochen
			}

		// jetzt wird aber wirklich geschlossen, Event kommt erst _nach_
		// evtl. speichern, damit Objekte, die sich bei ...ToClose abhängen, während
		// des Speicherns noch leben.
			THROW_FAILED_HRESULT(g_pDBEngine -> Fire_ProjectToClose(GetDispatch()));

		} // CPropertyWrapper goes out of scope

	// Hände weg, Storage wird freigegeben, und alle Objekte entlassen
		THROW_FAILED_HRESULT(CTRiASProject::HandsOffStorage());
		ReleaseSubObjects();
		ReleasePropertySupportObjects();

	} COM_CATCH;
	m_fIsDirty = false;

// jetzt wurde geschlossen
	g_pDBEngine -> Fire_ProjectClosed (bstrName);

	m_fIsInitialized = false;
	return S_OK;
}

STDMETHODIMP CTRiASProject::NewPassword(BSTR OldPassword, BSTR NewPassword)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	ATLTRACENOTIMPL("CTRiASProject::NewPassword");
}

STDMETHODIMP CTRiASProject::Save()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized) 
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);

	_ASSERTE(NULL != (IStorage *)m_Stg);

	COM_TRY {
	CPropertyWrapper PropWrap (GetPropertyBase(), g_cbSavingProject, VARIANT_TRUE);
	DWORD rgStgc = STGC_DEFAULT;

		if (STGMODE_Normal != m_StgMode)
			return REPORT_DBERROR(TRIASDB_E_CANNOTSAVE_AT_THIS_POINT);

		THROW_FAILED_HRESULT(CTRiASProject::Save (m_Stg, true));

		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(m_Stg -> Commit (rgStgc));

		THROW_FAILED_HRESULT(CTRiASProject::SaveCompleted (NULL));

	} COM_CATCH;
	m_fIsDirty = false;

	return S_OK;
}

STDMETHODIMP CTRiASProject::SaveAs(BSTR NewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

	_ASSERTE(NULL != (IStorage *)m_Stg);

STATSTG stg;

	ZeroMemory (&stg, sizeof(STATSTG));
	COM_TRY {
	CPropertyWrapper PropWrap (GetPropertyBase(), g_cbSavingProjectAs, VARIANT_TRUE);
	WStorage Stg;
	DWORD dwMode = STGM_CREATE | STGM_READWRITE | STGM_SHARE_DENY_WRITE | STGM_TRANSACTED;
	bool fSameFile = false;

		if (m_bstrName) {
		os_path pathold = OLE2A(m_bstrName);
		os_path pathnew = OLE2A(NewName);

			pathold.become_simplified();
			pathnew.become_simplified();

			fSameFile = (pathold == pathnew) ? true : false;
		}

	// zuerst muß sichergestellt sein, daß alle Objektklassen geladen sind, da sonst die Ansichten
	// unvollständig gespeichert werden
		THROW_FAILED_HRESULT(LoadObjectsDefs());

	// jetzt das eigentliche Speichern
		THROW_FAILED_HRESULT(::StgCreateDocfile (fSameFile ? NULL : NewName, dwMode, 0, Stg.ppi()));
		THROW_FAILED_HRESULT(::WriteClassStg(Stg, CLSID_OleDocumentWrapper));

		THROW_FAILED_HRESULT(CTRiASProject::Save (Stg, false));

	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));

	// alte Datei löschen, neue umbenennen
		if (fSameFile) {
			THROW_FAILED_HRESULT(CTRiASProject::HandsOffStorage());						// loslassen
			THROW_FAILED_HRESULT(Stg -> Stat (&stg, STATFLAG_DEFAULT));		// alter Name

		// umbenennen
			if (!MoveFileEx (OLE2A(stg.pwcsName), OLE2A(m_bstrName), MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED))
				THROW_FAILED_HRESULT(HRESULT_FROM_WIN32(GetLastError()));

		// neu eröffnen
			dwMode = STGM_READWRITE | STGM_TRANSACTED | (IsNovellDrive(m_bstrName) ? STGM_SHARE_DENY_NONE : STGM_SHARE_DENY_WRITE);
			if (IsWin40() && !IsWinNT())
				dwMode |= STGM_NOSCRATCH;
			THROW_FAILED_HRESULT(::StgOpenStorage (m_bstrName, NULL, dwMode, NULL, 0L, Stg.ppi()));
		}
		
	// neues Storage an alle weiterverteien (incl. uns selbst)
		THROW_FAILED_HRESULT(CTRiASProject::SaveCompleted (Stg));

		m_bstrName = NewName;								// neuen Namen merken
		ClearType (m_rgOpenMode, OPENMODE_ReadOnly);		// ist auf keinen Fall mehr schreibgeschützt
		
	} COM_CATCH_OP(CoTaskMemFree (stg.pwcsName));
	m_fIsDirty = false;

	CoTaskMemFree (stg.pwcsName);
	return S_OK;
}

STDMETHODIMP CTRiASProject::ExportCopyAs(BSTR NewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	_ASSERTE(NULL != (IStorage *)m_Stg);

	USES_CONVERSION;

STATSTG stg;

	ZeroMemory (&stg, sizeof(STATSTG));
	COM_TRY {
	CPropertyWrapper PropWrap (GetPropertyBase(), g_cbSavingProjectAs, VARIANT_TRUE);
	WStorage Stg;
	DWORD dwMode = STGM_CREATE | STGM_READWRITE | STGM_SHARE_DENY_WRITE | STGM_TRANSACTED;
	bool fSameFile = false;

		if (m_bstrName) {
		os_path pathold = OLE2A(m_bstrName);
		os_path pathnew = OLE2A(NewName);

			pathold.become_simplified();
			pathnew.become_simplified();

			fSameFile = (pathold == pathnew) ? true : false;
		}

	WStorage OldStg (m_Stg);	// bisheriges Storage wird wieder gebraucht

		THROW_FAILED_HRESULT(::StgCreateDocfile (fSameFile ? NULL : NewName, dwMode, 0, Stg.ppi()));
		THROW_FAILED_HRESULT(::WriteClassStg(Stg, CLSID_OleDocumentWrapper));

		THROW_FAILED_HRESULT(CTRiASProject::Save (Stg, false));

	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));

	// alte Datei löschen, neue umbenennen
		if (fSameFile) {
		// same as SaveAs auf identische Datei
			THROW_FAILED_HRESULT(CTRiASProject::HandsOffStorage());						// loslassen
			THROW_FAILED_HRESULT(Stg -> Stat (&stg, STATFLAG_DEFAULT));		// alter Name

		// umbenennen
			if (!MoveFileEx (OLE2A(stg.pwcsName), OLE2A(m_bstrName), MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED))
				THROW_FAILED_HRESULT(HRESULT_FROM_WIN32(GetLastError()));

		// neu eröffnen
			dwMode = STGM_READWRITE | STGM_TRANSACTED | (IsNovellDrive(m_bstrName) ? STGM_SHARE_DENY_NONE : STGM_SHARE_DENY_WRITE);
			if (IsWin40() && !IsWinNT())
				dwMode |= STGM_NOSCRATCH;

			THROW_FAILED_HRESULT(::StgOpenStorage (m_bstrName, NULL, dwMode, NULL, 0L, Stg.ppi()));
			THROW_FAILED_HRESULT(CTRiASProject::SaveCompleted (Stg));			// neues Storage ist auch für uns das aktive
			m_bstrName = NewName;		// neuen Namen merken (sollte der alte sein)
			
		} else {
		// altes Storage wieder in Umlauf bringen (incl. uns selbst), es bleibt beim alten Namen
			THROW_FAILED_HRESULT(CTRiASProject::SaveCompleted (OldStg));
		}

	} COM_CATCH_OP(CoTaskMemFree (stg.pwcsName));
	m_fIsDirty = false;

	CoTaskMemFree (stg.pwcsName);
	return S_OK;
}

STDMETHODIMP CTRiASProject::get_Mode(OPENMODE * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_Mode");

	*pVal = m_rgOpenMode;
	return S_OK;
}

STDMETHODIMP CTRiASProject::put_Mode(OPENMODE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_rgOpenMode = newVal;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASProject::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::CreateProperty");

	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_CreatingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToCreate (bstrName));

	// eigentliche Aktion
	CComObject<CTRiASProperty> *pNew = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASProperty>::CreateInstance (&pNew));

	WTRiASProperty Prop (pNew);		// required AddRef;
	WTRiASPropertyCallback Supp;

		THROW_FAILED_HRESULT(pNew -> put_Name (bstrName));
		THROW_FAILED_HRESULT(GetPropertySupportSite (bstrName, GetUnknown(), this, Supp.ppi()));
		THROW_FAILED_HRESULT(pNew -> SetSite (Supp));		// using IObjectWithSite
		*Property = Prop.detach();

	// Events hinterher
		THROW_FAILED_HRESULT(Fire_PropertyCreated (*Property));

	} COM_CATCH;

	return S_OK;
}

// Einlesen aller Eigenschaften der Database und aller lokaler Props des
// Objektes.
// Die Eigenschaften einer TRiAS-Database sind im sog. Header gespeichert.

// Props zeigt auf einen bereits existierenden Enumerator und wird durch 
// diese Funktion lediglich mit allen Properties gefüllt.
STDMETHODIMP CTRiASProject::FillWithProperties (IUnknown **Props)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	COM_TRY {
	// zuerst die feststehenden Properties hinzufügen
		THROW_FAILED_HRESULT(CManagePropertySupport<CTRiASProject>::FillWithProperties(Props));

	// danach die im Projekt enthaltenen
	CActDB ActDB (m_hPr);
	CPrjHeader DBProp (m_hPr);
	CEnumPropertyCallback CallBackData;

		CallBackData.m_pTarget = this;
		CallBackData.m_Enum = *Props;	// throws hr

		THROW_FAILED_HRESULT(DBProp.EnumHeaderData (RefreshCallBack, (UINT_PTR)&CallBackData)); 

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProject::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::RemoveProperty");

HRESULT hr = S_OK;

	USES_CONVERSION;
	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_DeletingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToDelete (bstrName));

	// nur im Header löschen, wenn's keine vordefinierte Property ist
		if (S_OK != PropertyIsPredefined (bstrName)) {
		// eigentliche Aktion
		CActDB ActDB (m_hPr);
		CPrjHeader DBProp (m_hPr, OLE2A(bstrName));

			THROW_FAILED_HRESULT(DBProp.DeleteHeaderEntry()); 

		// ggf. zuständiges Objekt freigeben, S_FALSE (nicht gefunden) darf vorkommen
			THROW_FAILED_HRESULT(ReleasePropertySupportSite (bstrName));
		}
		else
			THROW_FAILED_HRESULT(hr = ReleasePropertySupportSite (bstrName));	// zuständiges Objekt freigeben

	// Event hinterher
		if (S_OK == hr) {
			m_fIsDirty = true;
			THROW_FAILED_HRESULT(Fire_PropertyDeleted (bstrName));
		}
	} COM_CATCH;
	return hr;		// S_FALSE heißt: nicht gefunden
}

STDMETHODIMP CTRiASProject::PutValue (BSTR Name, VARIANT Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::PutValue");

	USES_CONVERSION;
	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_ModifyingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToModify (bstrName));

	// HeaderEntry neu schreiben/erzeugen
	CActDB ActDB (m_hPr);
	CPrjHeader DBProp (m_hPr, OLE2A(bstrName));
	CComVariant v;

		THROW_FAILED_HRESULT(v.ChangeType (VT_BSTR, &Value));

	CComBSTR Val (V_BSTR(&v));
	LONG lFlags = 0;

		DBProp.GetHeaderEntry (NULL, 0, &lFlags);	// evtl. Fehler ignorieren
		THROW_FAILED_HRESULT(DBProp.PutHeaderEntry (OLE2A(Val), Val.Length(), lFlags));
		m_fIsDirty = true;

	// Event hinterher
		THROW_FAILED_HRESULT(Fire_PropertyModified (bstrName));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProject::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::GetValue");

	USES_CONVERSION;
	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// HeaderEntry komplett einlesen
	CActDB ActDB (m_hPr);
	CPrjHeader DBProp (m_hPr, OLE2A(bstrName));
	size_t iLen = 0;

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntryLen(&iLen));

	char *pBuffer = (char *)_alloca(iLen);

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntry (pBuffer, iLen, NULL));

	CComVariant v (pBuffer);

		THROW_FAILED_HRESULT(v.Detach(pVal));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProject::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::PutType");

	USES_CONVERSION;
	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_ModifyingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToModify (bstrName));

	// HeaderEntry neu schreiben/erzeugen
	CActDB ActDB (m_hPr);
	CPrjHeader DBProp (m_hPr, OLE2A(bstrName));
	size_t iLen = 0;

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntryLen(&iLen));

	char *pBuffer = (char *)_alloca(iLen);

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntry (pBuffer, iLen, NULL));
		THROW_FAILED_HRESULT(DBProp.PutHeaderEntry (pBuffer, iLen-1, Value));
		m_fIsDirty = true;

	//Event hinterher
		THROW_FAILED_HRESULT(Fire_PropertyModified (bstrName));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProject::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::GetType");

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// HeaderEntry komplett einlesen
PROPERTY_TYPE lFlags;
CActDB ActDB (m_hPr);
CPrjHeader DBProp (m_hPr, OLE2A(bstrName));

	RETURN_FAILED_HRESULT(DBProp.GetHeaderEntry (NULL, 0, (LONG *)&lFlags));

	*pVal = lFlags;
	return S_OK;
}

STDMETHODIMP CTRiASProject::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::PutType");

	USES_CONVERSION;
	COM_TRY{
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_ModifyingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToModify (bstrName));

	// HeaderEntry neu schreiben/erzeugen
	CActDB ActDB (m_hPr);
	CPrjHeader DBProp (m_hPr, OLE2A(bstrName));
	CComVariant v;

		THROW_FAILED_HRESULT(v.ChangeType (VT_BSTR, &Val));

	CComBSTR bstrVal (V_BSTR(&v));

		THROW_FAILED_HRESULT(DBProp.PutHeaderEntry (OLE2A(bstrVal), bstrVal.Length(), Type));
		m_fIsDirty = true;

	// Event hinterher
		THROW_FAILED_HRESULT(Fire_PropertyModified (bstrName));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProject::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::GetType");

	USES_CONVERSION;
	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// HeaderEntry komplett einlesen
	PROPERTY_TYPE lFlags;
	CActDB ActDB (m_hPr);
	CPrjHeader DBProp (m_hPr, OLE2A(bstrName));
	size_t iLen = 0;

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntryLen(&iLen));

	char *pBuffer = (char *)_alloca(iLen);

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntry (pBuffer, iLen, (LONG *)&lFlags));

	CComVariant v (pBuffer);

		THROW_FAILED_HRESULT(v.Detach(pVal));
		*pType = lFlags;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProject::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized && 
		(0 == SysStringLen(bstrName) || !wcscmp (bstrName, g_cbTRiASCSService))) 
	{
	// evtl. Koordinatensystem neu berechnen
		RETURN_FAILED_HRESULT(InitCoordSystemService());
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASConnectionEvents-Wrapper
STDMETHODIMP CTRiASProject::CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{ 
	return Fire_CreatingConnection (Name, pVal); 
}

STDMETHODIMP CTRiASProject::ConnectionToCreate (BSTR Name)
{
	return Fire_ConnectionToCreate (Name); 
}

STDMETHODIMP CTRiASProject::ConnectionCreated (IDispatch *pIConn)
{
	m_fIsDirty = true;
	return Fire_ConnectionCreated (pIConn); 
}

STDMETHODIMP CTRiASProject::OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_OpeningConnection (Name, pVal); 
}

STDMETHODIMP CTRiASProject::ConnectionToOpen (BSTR Name)
{
	return Fire_ConnectionToOpen (Name); 
}

STDMETHODIMP CTRiASProject::ConnectionOpened (IDispatch *pIConn)
{
	m_fIsDirty = true;
	RETURN_FAILED_HRESULT(RetrieveLastCookie());
	return Fire_ConnectionOpened (pIConn); 
}

STDMETHODIMP CTRiASProject::ClosingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return Fire_ClosingConnection (pIConn, pVal); 
}

STDMETHODIMP CTRiASProject::ConnectionToClose (IDispatch *pIConn)
{
	return Fire_ConnectionToClose (pIConn); 
}

STDMETHODIMP CTRiASProject::ConnectionClosed (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_ConnectionClosed (Name); 
}

STDMETHODIMP CTRiASProject::DeletingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return Fire_DeletingConnection (pIConn, pVal); 
}

STDMETHODIMP CTRiASProject::ConnectionToDelete (IDispatch *pIConn)
{
	return Fire_ConnectionToDelete (pIConn); 
}

STDMETHODIMP CTRiASProject::ConnectionDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_ConnectionDeleted (Name); 
}

STDMETHODIMP CTRiASProject::RenamingConnection (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return Fire_RenamingConnection (OldName, NewName, pVal);
}

STDMETHODIMP CTRiASProject::ConnectionToRename (BSTR OldName, BSTR NewName)
{
	return Fire_ConnectionToRename (OldName, NewName);
}

STDMETHODIMP CTRiASProject::ConnectionRenamed (IDispatch *pIConn)
{
	return Fire_ConnectionRenamed (pIConn);
}

STDMETHODIMP CTRiASProject::ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return Fire_ChangingConnectedDatasource (pIConn, pVal);
}

STDMETHODIMP CTRiASProject::ConnectedDatasourceToChange (IDispatch *pIConn)
{
	return Fire_ConnectedDatasourceToChange (pIConn);
}

STDMETHODIMP CTRiASProject::ConnectedDatasourceChanged (IDispatch *pIConn)
{
	return Fire_ConnectedDatasourceChanged(pIConn);
}

// ITRiASViewEvent-Wrapper
STDMETHODIMP CTRiASProject::CreatingView (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_CreatingView (Name, pVal); 
}

STDMETHODIMP CTRiASProject::ViewToCreate (BSTR Name)
{
	return Fire_ViewToCreate (Name); 
}

STDMETHODIMP CTRiASProject::ViewCreated (IDispatch *pIView)
{
	m_fIsDirty = true;
	return Fire_ViewCreated (pIView);
}

STDMETHODIMP CTRiASProject::ChangingView (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return Fire_ChangingView (OldName, NewName, pVal);
}

STDMETHODIMP CTRiASProject::ViewToChange (BSTR Name, BSTR NewName)
{
	return Fire_ViewToChange (Name, NewName);
}

STDMETHODIMP CTRiASProject::ViewChanged (IDispatch *pIView)
{
	m_fIsDirty = true;
	return Fire_ViewChanged (pIView);
}

STDMETHODIMP CTRiASProject::DeletingView (IDispatch *pIView, VARIANT_BOOL *pVal)
{
	return Fire_DeletingView (pIView, pVal);
}

STDMETHODIMP CTRiASProject::ViewToDelete (IDispatch *pIView)
{
	return Fire_ViewToDelete (pIView);
}

STDMETHODIMP CTRiASProject::ViewDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_ViewDeleted (Name);
}

STDMETHODIMP CTRiASProject::GetObjectStorage (
	LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (FAILED(IsInitialized())) 
		return TRIASDB_E_DATABASE_NOT_OPENED;

	if (!wcscmp (g_cbStgService, pszItem)) {
	// Projekt-RootStorage gefragt
		_ASSERTE(m_Stg.IsValid());
		if (!m_Stg.IsValid())
			return MK_E_NOOBJECT;

		return m_Stg -> QueryInterface (riid, ppvStorage);
	}

DWORD dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;

	if (NULL != pbc) {
	BIND_OPTS bindOpts;

		ZeroMemory (&bindOpts, sizeof(BIND_OPTS));
		bindOpts.cbStruct = sizeof(BIND_OPTS);
		if (SUCCEEDED(pbc -> GetBindOptions (&bindOpts)))
			dwMode = bindOpts.grfMode;
	}

// RootStorage der enthaltenen Objekte gefragt
	_ASSERTE(m_ObjectStg.IsValid());
	if (!m_ObjectStg.IsValid())
		return MK_E_NOOBJECT;

	if (!wcscmp (g_cbObjectStgService, pszItem)) 
		return m_ObjectStg -> QueryInterface (riid, ppvStorage);

// zuerst versuchen, existierendes Storage zu eröffnen
WStorage SubStg;
HRESULT hr = m_ObjectStg -> OpenStorage (pszItem, NULL, dwMode & ~STGM_CREATE, NULL, 0L, SubStg.ppi());

	if (FAILED(hr) && (dwMode & STGM_CREATE)) {
	// Storage erzeugen
	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		RETURN_FAILED_HRESULT(hr = m_ObjectStg -> CreateStorage (pszItem, dwMode, 0, 0, SubStg.ppi()));
		RETURN_FAILED_HRESULT(m_ObjectStg -> Commit (rgStgc));
		m_fIsDirty = true;			// globales Commit erzwingen
	}
	return SUCCEEDED(hr) ? SubStg -> QueryInterface (riid, ppvStorage) : hr;
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASProject::SaveObject()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASProject::SaveObject");
}

STDMETHODIMP CTRiASProject::GetMoniker (
	DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppmk) return E_POINTER;
	*ppmk = NULL;

CComBSTR bstrName;

	if (!m_fIsInitialized) {
	// Projekt ist noch nicht fertig initialisiert
		if (!m_fIsInitializing)
			return TRIASDB_E_DATABASE_NOT_OPENED;

	// Projekt wird gerade initialisiert, also Namen von DBengine holen
	WTRiASMainDBEngine DBEng;

		VERIFY(SUCCEEDED(g_pDBEngine -> QueryInterface (IID_ITRiASMainDBEngine, DBEng.ppv())));
		RETURN_FAILED_HRESULT(DBEng -> get_ProjectToOpen(CLEARED(&bstrName)));
	} else
		bstrName = m_bstrName;

	switch (dwWhichMoniker) {
	case OLEWHICHMK_OBJREL:
	case OLEWHICHMK_OBJFULL:
	// This is just the file we're living in.
		return CreateFileMoniker (bstrName, ppmk);
			
	case OLEWHICHMK_CONTAINER:
	default:
		break;
	}
	return (NULL == *ppmk) ? E_FAIL : S_OK;
}

STDMETHODIMP CTRiASProject::GetContainer (IOleContainer **ppContainer)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASProject::GetContainer");
}

STDMETHODIMP CTRiASProject::ShowObject()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASProject::ShowObject");
}

STDMETHODIMP CTRiASProject::OnShowWindow (BOOL fShow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASProject::OnShowWindow");
}

STDMETHODIMP CTRiASProject::RequestNewObjectLayout()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASProject::RequestNewObjectLayout");
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTRiASProject::get_ObjectsDefs(ITRiASObjectsCollection **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_ObjectsDefs");

// wenn die Collection bereits existiert, dann lediglich diese zurückliefern
	if (m_QueryDefs.IsValid()) {
		*pVal = m_QueryDefs;
		(*pVal) -> AddRef();
		return S_OK;
	}

	return E_UNEXPECTED;	// ansonsten Fehler melden
}

STDMETHODIMP CTRiASProject::get_ObjectsDef (
	VARIANT vItem, VARIANT_BOOL fCreate, BSTR Type, ITRiASObjects ** pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_ObjectsDef");

HRESULT hr = E_FAIL;

	_ASSERTE(m_QueryDefs.IsValid());
	COM_TRY {
		hr = m_QueryDefs -> Item (vItem, pVal);
		if (TRIASDB_E_UNKNOWN_OBJECTS == hr && fCreate) {	// evtl. neu erzeugen
		CComVariant v;

			THROW_FAILED_HRESULT(v.ChangeType (VT_BSTR, &vItem));

		CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

#pragma MESSAGE("TODO: ClsId 'CLSID_TRiASSimpleQuery' einsetzen, wenn SimpleQuery implementiert ist !")

			if (!ClsId)	ClsId = CLSID_TRiASObjects;	// default ClsId

			hr = m_QueryDefs -> Add (V_BSTR(&v), CComBSTR(ClsId.ProgID().c_str()), pVal);
			if (S_OK == hr) hr = S_FALSE;				// Objektmenge wurde neu erzeugt
		}
	} COM_CATCH;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTRiASProject::get_ConnectionFilters(ITRiASConnectionFilters **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_ConnectionFilters");

// wenn die Collection bereits existiert, dann lediglich diese zurückliefern
	if (m_ConnFilters.IsValid()) {
		*pVal = m_ConnFilters;
		(*pVal) -> AddRef();
		return S_OK;
	}
	return E_UNEXPECTED;	// ansonsten Fehler melden
}

STDMETHODIMP CTRiASProject::get_ConnectionFilter (
	VARIANT vItem, VARIANT_BOOL fCreate, ITRiASConnectionFilter ** pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProject::get_ConnectionFilter");

HRESULT hr = E_FAIL;

	_ASSERTE(m_ConnFilters.IsValid());
	COM_TRY {
	CComVariant vValue;
	WDynamicCollection Coll(m_ConnFilters);

		_ASSERTE(VT_BSTR == V_VT(&vItem));
		hr = Coll -> get_Item (vItem, &vValue);

		if (E_INVALIDARG == hr && fCreate) {	// evtl. neu erzeugen
		WTRiASConnectionFilter Filter;

			THROW_FAILED_HRESULT(m_ConnFilters -> Add(V_BSTR(&vItem), Filter.ppi()));
			hr = S_FALSE;				// Objektmenge wurde neu erzeugt
			vValue = CComVariant(Filter);
		}

		if (SUCCEEDED(hr)) {
			THROW_FAILED_HRESULT(vValue.ChangeType(VT_DISPATCH));
			THROW_FAILED_HRESULT(V_DISPATCH(&vValue) -> QueryInterface(pVal));
		}

	} COM_CATCH;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Workspace-Koordinatensystem erzeugen und als Property speichern
HRESULT CTRiASProject::InitCoordSystemService()
{
	COM_TRY {
	// Ausgabe-Koordinatensystem erzeugen und als Property speichern
	CCSFactory CSService;
	WTRiASPropertyBase PropBase(GetPropertyBase());

	WTRiASCS CS (GetProperty (GetProperties(), g_cbTRiASCSService, (IDispatch *)NULL), false);

		if (CS.IsValid()) {
			THROW_FAILED_HRESULT(CSService.ReInitCS (PropBase, CS));
		} 
		else {
			THROW_FAILED_HRESULT(CSService.RetrieveCS (PropBase, CS.ppi()));
			THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbTRiASCSService, CComVariant(CS), true));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OleItemContainerSupport
HRESULT CTRiASProject::GetConnection (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	if (!m_fIsInitialized || NULL == m_hPr || !m_Connections)			// noch nicht geöffnet
		return TRIASDB_E_PROJECT_NOT_OPENED;

CIID Guid (pcItem, CIID::INITCIID_InitFromGuid);

	if (!Guid) return E_UNEXPECTED;

WTRiASConnection Conn;
HRESULT hr = m_Connections -> Item (CComVariant(pcItem), Conn.ppi());

	if (SUCCEEDED(hr) && !fTestRunningOnly && NULL != ppvObj)
	{
		_ASSERTE(Conn.IsValid());
		return Conn -> QueryInterface (riid, ppvObj);
	}
	return hr;
}

// nach einer bestimmten Objektklasse fragen
HRESULT CTRiASProject::GetObjectsDef (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	if (!m_QueryDefs) {
		if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)
			return MK_E_EXCEEDEDDEADLINE;

	// evtl. Neuerzeugen der benötigten Collection
	WTRiASObjectsCollection Coll;

		RETURN_FAILED_HRESULT(get_ObjectsDefs (Coll.ppi()));	// fills in m_ObjectsDefs
	}
	_ASSERTE(!!m_QueryDefs);

HRESULT hr = S_OK;

	COM_TRY {
	WTRiASObjects Objs;
		
		hr = m_QueryDefs -> Item (CComVariant(pcItem), Objs.ppi());
		if (TRIASDB_E_UNKNOWN_OBJECTS == hr && !fTestRunningOnly) {
		// Objektklasse ist neu und muß erzeugt werden
			if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)
				return MK_E_EXCEEDEDDEADLINE;
			hr = m_QueryDefs -> Add (CComBSTR(pcItem), CComBSTR("TRiASDB.TRiASCollectObjects.1"), Objs.ppi());
		}

		if (SUCCEEDED(hr) && !fTestRunningOnly && NULL != ppvObj)	// Objektklasse ist (jetzt) bekannt
		{
			_ASSERTE(Objs.IsValid());
			THROW_FAILED_HRESULT(Objs -> QueryInterface (riid, ppvObj));
		}
	} COM_CATCH;
	return hr;
}

HRESULT CTRiASProject::ParseObjectsDef (
	LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut)
{
CComBSTR bstrItem(pcItem);

	RETURN_FAILED_HRESULT(CreateItemMoniker (g_cbMkDel, bstrItem, ppmkOut));
	*pulEaten += bstrItem.Length();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IOleObject
STDMETHODIMP CTRiASProject::SetClientSite (IOleClientSite *pClientSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	m_ClientSite = pClientSite;
	return S_OK;
}

STDMETHODIMP CTRiASProject::GetClientSite (IOleClientSite **ppClientSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(ppClientSite);

	*ppClientSite = m_ClientSite;
	if (NULL != *ppClientSite)
		(*ppClientSite) -> AddRef();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Cookies verwalten
HRESULT CTRiASProject::ConnectCookieHolder()
{
	_ASSERTE(0 == m_dwCookieHolderCookie);

	COM_TRY {
	WCookieHelper CookieHolder;

		THROW_FAILED_HRESULT(g_pDBEngine -> GetCookieHelper (CookieHolder.ppi()));
		THROW_FAILED_HRESULT(AtlAdvise (CookieHolder, GetUnknown(), IID_ICookieHelperEvents, &m_dwCookieHolderCookie));

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::DisconnectCookieHolder()
{
	_ASSERTE(0 != m_dwCookieHolderCookie);

	COM_TRY {
	WCookieHelper CookieHolder;

		THROW_FAILED_HRESULT(g_pDBEngine -> GetCookieHelper (CookieHolder.ppi()));
		THROW_FAILED_HRESULT(AtlUnadvise (CookieHolder, IID_ICookieHelperEvents, m_dwCookieHolderCookie));
		m_dwCookieHolderCookie = 0;

	} COM_CATCH;
	return S_OK;
}

namespace {
	typedef struct tagCOOKIENAMES {
		const wchar_t *m_pName;
		const wchar_t *m_pLastName;
	} COOKIENAMES;

	COOKIENAMES s_cbCookieNames[] = {
		{ g_cbObjectsMap, g_cbLastObjectsCookie,},
		{ g_cbObjectMap, g_cbLastObjectCookie, },
		{ g_cbFeatureMap, g_cbLastFeatCookie, },
		{ NULL, NULL, },
	};
}

HRESULT CTRiASProject::SaveLastCookie()
{
	if (!m_fMustSaveLastCookie) 
		return S_OK;

	for (COOKIENAMES *pCookieNames = s_cbCookieNames; NULL != pCookieNames -> m_pName; ++pCookieNames) 
	{
		SaveLastCookie (CComBSTR(pCookieNames -> m_pName), CComBSTR(pCookieNames -> m_pLastName));
	}
	m_fMustSaveLastCookie = false;		// Cookies sind jetzt gespeichert

	return S_OK;
}

HRESULT CTRiASProject::SaveLastCookie (BSTR bstrCookieName, BSTR bstrLastCookieName)
{
	COM_TRY {
		_ASSERTE(NULL != g_pDBEngine);

	INT_PTR lLastCookie = g_pDBEngine -> GetLastCookie (bstrCookieName);
	WEnumVARIANT Enum;
	CComVariant var;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			_ASSERTE(SUCCEEDED(var.ChangeType (VT_DISPATCH)));

		WTRiASConnection Conn (V_DISPATCH(&var));
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened != rgStatus)
				continue;		// nur geöffnete DB's untersuchen

		WTRiASDatabase Dbase;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));

		WTRiASPropertyBase PropBase(Dbase);

			THROW_FAILED_HRESULT(SetPropertyBy (PropBase, bstrLastCookieName, lLastCookie, true, LANG_ENGLISH));
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::RetrieveLastCookie()
{
	COM_TRY {
		THROW_FAILED_HRESULT(SaveLastCookie());		// evtl. aktuellen Zustand speichern

	// den größten aller Cookies feststellen
		for (COOKIENAMES *pCookieNames = s_cbCookieNames; NULL != pCookieNames -> m_pName; ++pCookieNames) 
		{
			THROW_FAILED_HRESULT(RetrieveLastCookie (CComBSTR(pCookieNames -> m_pName), CComBSTR(pCookieNames -> m_pLastName)));
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASProject::RetrieveLastCookie (BSTR bstrCookieName, BSTR bstrLastCookieName)
{
	COM_TRY {
	// den größten aller Cookies feststellen
	WEnumVARIANT Enum;
	CComVariant var;
	UINT_PTR lLastCookie = g_pDBEngine -> GetLastCookie (bstrCookieName);
	INT_PTR lCookie = 0L;

		THROW_FAILED_HRESULT(m_Connections -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/) 
		{
			_ASSERTE(SUCCEEDED(var.ChangeType (VT_DISPATCH)));

		WTRiASConnection Conn (V_DISPATCH(&var));
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened != rgStatus)
				continue;		// nur geöffnete DB's untersuchen

		WTRiASDatabase Dbase;

			THROW_FAILED_HRESULT(Conn -> get_Database (Dbase.ppi()));

		WTRiASPropertyBase PropBase(Dbase);

			lCookie = GetPropertyFrom (PropBase, bstrLastCookieName, INT_PTR(0), LANG_ENGLISH);
			if (UINT_PTR(lCookie) > lLastCookie) {
				_ASSERTE(UINT_PTR(lCookie) != ULONG_MAX);
				lLastCookie = UINT_PTR(lCookie);
			}
		}

	// CookieHelper neu initialisieren
		_ASSERTE(NULL != g_pDBEngine);
		if (lLastCookie != 0) 
			THROW_FAILED_HRESULT(g_pDBEngine -> SetInitialCookie (bstrCookieName, lLastCookie+1));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ICookieHelperEvents
STDMETHODIMP CTRiASProject::CookieHolderInitialized (BSTR Name, INT_PTR NewCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_hPr);

	return S_OK;
}

STDMETHODIMP CTRiASProject::IssuedNextCookie (BSTR Name, INT_PTR NextCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_hPr);

//	RETURN_FAILED_HRESULT(SaveLastCookie());
	m_fMustSaveLastCookie = true;		// cookies müssen gespeichert werden
	return S_OK;
}


