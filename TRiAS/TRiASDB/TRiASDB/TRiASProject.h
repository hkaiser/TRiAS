///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASProject.h | Deklaration der Klasse <c CTRiASProject>

#if !defined(_TRIASPROJECT_H__7C8CB9BD_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASPROJECT_H__7C8CB9BD_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/OleObjectNotImpl.h>
#include <Com/OleItemContainerSupport.h>

#include "resource.h"					// main symbols
#include "CPTRiASConnectionEvents.h"	// connection points
#include "CPTRiASPropertyEvents.h"
#include "CPTRiASViewEvents.h"

#include "ActDB.h"
#include "TRiASDBEngine.h"
#include "TRiASProperties.h"

#include "PropertySupport.h"
#include "PropertyBase.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(OleClientSite);

/////////////////////////////////////////////////////////////////////////////
// aktuelle ProjektDateiVersion
const long PROJECTFILE_SIGNATURE = 0x4A4F5250L;			// "PROJ"
const long PROJECTFILE_VERSION_MINOR_MASK = 0xff;
const long PROJECTFILE_VERSION_300 = 0x0300L;
const long PROJECTFILE_VERSION_301 = 0x0301L;		// #HK990710
const long PROJECTFILE_VERSION_302 = 0x0302L;		// #HK021212
const long PROJECTFILE_VERSION_400 = 0x0400L;		// #HK040902
const long LASTKNOWN_PROJECTFILE_VERSION = PROJECTFILE_VERSION_400;

/////////////////////////////////////////////////////////////////////////////
// CTRiASProject
class ATL_NO_VTABLE CTRiASProject : 
	public ISupportErrorInfo,
	public IOleClientSite,
	public IOleObjectNotImpl,
	public COleItemContainerSupport<CTRiASProject>,
	public IPersistStorage,
	public ITRiASPropertyCallback,
	public CProxyITRiASConnectionEvents<CTRiASProject>,
	public CProxyITRiASPropertyEvents<CTRiASProject>,
	public CProxyITRiASViewEvents<CTRiASProject>,
	public IConnectionPointContainerImpl<CTRiASProject>,
	public CManagePropertySupport<CTRiASProject>,
	public CManagePropertyBase<CTRiASProject>,
	public CReportErrorComCoClass<CTRiASProject, &CLSID_TRiASProject, &IID_ITRiASProject>, 
	public IProvideClassInfo2Impl<&CLSID_TRiASProject, &IID_ITRiASConnectionEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public ITRiASConnectionEvents,
	public ITRiASViewEvents,
	public ICookieHelperEvents,
	public IDispatchImpl<ITRiASProject, &IID_ITRiASProject, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public CComObjectRootEx<CComObjectThreadModel>
{
public:
	typedef CComCoClass<CTRiASProject, &CLSID_TRiASProject> base_t;

	CTRiASProject()
		: m_fIsDirty(false), m_fIsTemporary(false),
		  m_fIsReadOnly(false), m_fIsOpenedAsCopy(false),
		  m_StgMode(STGMODE_Unknown), m_hPr(NULL), m_rgOpenMode(OPENMODE_Normal), 
		  m_fActivated(false), m_fIsInitialized(false), 
		  m_fIsInitializing(false), m_fMustSaveLastCookie(false),
		  m_bstrName(g_cbNil), m_dwCookieHolderCookie(0L)
	{
		m_lVersion = LASTKNOWN_PROJECTFILE_VERSION;
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASProject)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASProject)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPROJECT)
//	static HRESULT WINAPI UpdateRegistry (BOOL bRegister);

	BEGIN_COM_MAP(CTRiASProject)
		COM_INTERFACE_ENTRY(ITRiASProject)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASProject)	// main dispatch
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStorage)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)		// Connections benutzen diese Funktionen hier
		COM_INTERFACE_ENTRY(ITRiASViewEvents)			// Views benutzen diese Funktionen hier
//		COM_INTERFACE_ENTRY(ITRiASPropertyEvents)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IOleItemContainer)
		COM_INTERFACE_ENTRY(IOleContainer)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(IParseDisplayName)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(ICookieHelperEvents)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASProject)
		CONNECTION_POINT_ENTRY(IID_ITRiASConnectionEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASViewEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CTRiASProject)
		PROPERTYSUPPORT_ENTRY_AGGR(g_cbCTFService, CLSID_TRiASCTFProperty)
		PROPERTYSUPPORT_ENTRY_AGGR(g_cbStgService, CLSID_TRiASStgProperty)
		PROPERTYSUPPORT_ENTRY(g_cbSysAdmin, CLSID_TRiASAutoSaveProperty)
		PROPERTYSUPPORT_ENTRY_AGGR(g_cbTRiASCSService, CLSID_TRiASAutoSaveProperty)
		PROPERTYSUPPORT_ENTRY(g_cbSavingProject, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbSavingProjectAs, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbClosingProject, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbCoordExternPipe, CLSID_TRiASVariantProperty)
	END_PROPERTYSUPPORT_MAP()

	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CTRiASProject)
		OLEITEMCONTAINERSUPPORT_ENTRY(g_cbMkConnection, GetConnection)
		OLEITEMCONTAINERSUPPORT_ENTRYEX(g_cbMkObjectsDef, GetObjectsDef, ParseObjectsDef)
	END_OLEITEMCONTAINERSUPPORT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct();
	void FinalRelease (void);

	HRESULT CreateCollections(bool fCreate = false);

	HRESULT ConnectAll (void);
	HRESULT DisconnectAll (VARIANT_BOOL fCommit);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(FillWithProperties)(/*[in, out]*/ IUnknown **Props);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

// ITRiASConnectionEvents
	STDMETHOD(CreatingConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionCreated)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(OpeningConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToOpen)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionOpened)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ClosingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToClose)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionClosed)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToDelete)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionDeleted)(/*[in]*/ BSTR Name);
	STDMETHOD(RenamingConnection)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToRename)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName);
	STDMETHOD(ConnectionRenamed)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ChangingConnectedDatasource)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectedDatasourceToChange)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectedDatasourceChanged)(/*[in]*/ IDispatch *pIConn);

// ITRiASViewEvents
	STDMETHOD(CreatingView)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ViewCreated)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(ChangingView)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToChange)(/*[in]*/ BSTR Name, /*[in]*/ BSTR NewName);
	STDMETHOD(ViewChanged)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(DeletingView)(/*[in]*/ IDispatch *pIView, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToDelete)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(ViewDeleted)(/*[in]*/ BSTR Name);

// ICookieHelperEvents
	STDMETHOD(CookieHolderInitialized)(/*[in]*/ BSTR Name, /*[in]*/ INT_PTR NewCookie);
	STDMETHOD(IssuedNextCookie)(/*[in]*/ BSTR Name, /*[in]*/ INT_PTR NextCookie);

// IOleItemContainer
	STDMETHOD(GetObjectStorage)(LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage);

// IOleClientSite
	STDMETHOD(SaveObject)();
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
	STDMETHOD(GetContainer)(IOleContainer **ppContainer);
	STDMETHOD(ShowObject)();
	STDMETHOD(OnShowWindow)(BOOL fShow);
	STDMETHOD(RequestNewObjectLayout)();

// ITRiASProject
public:
	STDMETHOD(get_ConnectionFilter)(/*[in]*/ VARIANT vItem, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fCreate, /*[out, retval]*/ ITRiASConnectionFilter **pVal);
	STDMETHOD(get_ConnectionFilters)(/*[out, retval]*/ ITRiASConnectionFilters **pVal);
	STDMETHOD(get_ObjectsDef)(/*[in]*/ VARIANT vItem, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fCreate, /*[in, optional, defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASObjects * *pVal);
	STDMETHOD(get_ObjectsDefs)(/*[out, retval]*/ ITRiASObjectsCollection * *pVal);
	STDMETHOD(get_Activated)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Activated)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Dirty)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Dirty)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Handle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(get_Temporary)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Temporary)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_View)(/*[in]*/ BSTR bstrName, /*[in,defaultvalue,optional]*/ VARIANT_BOOL fCreate, /*[out, retval]*/ ITRiASView **pVal);
	STDMETHOD(get_Views)(/*[out, retval]*/ ITRiASViews * *pVal);
	STDMETHOD(get_Mode)(/*[out, retval]*/ OPENMODE *pVal);
	STDMETHOD(put_Mode)(/*[in]*/ OPENMODE newVal);
	STDMETHOD(get_Connections)(/*[out, retval]*/ ITRiASConnections **pVal);
	STDMETHOD(get_Connection)(/*[in]*/ VARIANT vItem, /*[out, retval]*/ ITRiASConnection **pVal);
	STDMETHOD(get_OpenedAsCopy)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_OpenedAsCopy)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_CouldOpenTarget)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Updatable)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	HRESULT IsInitialized()
	{
		if (m_fIsInitialized) 
			return S_OK;
		if (m_fIsInitializing)
			return S_FALSE;
		return REPORT_DBERROR(TRIASDB_E_PROJECT_NOT_OPENED);
	}

	STDMETHOD(Close)(/*[in, optional, defaultvalue]*/ VARIANT_BOOL fCommit);
	STDMETHOD(NewPassword)(/*[in]*/ BSTR OldPassword, /*[in]*/ BSTR NewPassword);
	STDMETHOD(Save)();
	STDMETHOD(SaveAs)(BSTR NewName);
	STDMETHOD(ExportCopyAs)(BSTR NewName);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStorage
	STDMETHOD(IsDirty)(void);
	STDMETHOD(InitNew)(IStorage *pStorage);
	STDMETHOD(Load)(IStorage *pStorage);
	STDMETHOD(Save)(IStorage *pStorage, BOOL fSameAsLoad);
	STDMETHOD(SaveCompleted)(IStorage *pStorage);
	STDMETHOD(HandsOffStorage)(void);

protected:
	HRESULT CreateDatabase (IStorage *pIStg);
	HRESULT OpenDatabase (IStorage *pIStg);

	HPROJECT OpenDB (IStorage *pIStg, bool &rfReadOnly) throw (_com_error);
	HRESULT CloseDB (bool fFullRelease);
	HRESULT ReleaseSubObjects();

	HRESULT GetRunning (LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, void **ppvObject, bool fTestRunningOnly);

	HRESULT InitCoordSystemService();
	HRESULT LoadObjectsDefs();
	
// OleItemContainerSupport
	HRESULT GetConnection (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetObjectsDef (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT ParseObjectsDef (LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut);

// IOleObject
	STDMETHOD(SetClientSite)(IOleClientSite *pClientSite);
	STDMETHOD(GetClientSite)(IOleClientSite **ppClientSite);

// Cookies verwalten
	HRESULT RetrieveLastCookie();
	HRESULT RetrieveLastCookie (BSTR bstrCookieName, BSTR bstrLastCookieName);
	HRESULT SaveLastCookie();
	HRESULT SaveLastCookie (BSTR bstrCookieName, BSTR bstrLastCookieName);
	
	HRESULT ConnectCookieHolder();
	HRESULT DisconnectCookieHolder();

	ITRiASPropertyBase *GetPropertyBase() { return static_cast<ITRiASPropertyBase *>(this); }
	IDispatch *GetDispatch() { return static_cast<ITRiASProject *>(this); }

// evtl. IPersistStorage der Connections ansprechen
	HRESULT LocalConnections_InitNew(IStorage *pIStg);
	HRESULT LocalConnections_Load (IStorage *pIStg);
	HRESULT LocalConnections_Save (IStorage *pIStg, BOOL fSameAsLoad);
	HRESULT LocalConnections_SaveCompleted (IStorage *pIStg);
	HRESULT LocalConnections_HandsOffStorage();

private:
	CComPtr<IDispatch> m_Parent;
	WOleClientSite m_ClientSite;

// eigene Daten, die aus Stream gelesen werden
	long m_lVersion;

	CComBSTR m_bstrName;
	bool m_fIsReadOnly;
	bool m_fIsOpenedAsCopy;
	bool m_fIsTemporary;
	bool m_fActivated;

	bool m_fIsDirty;
	bool m_fIsInitialized;				// wurde fertig initialisert
	bool m_fIsInitializing;				// wird gerade initialisert
	bool m_fMustSaveLastCookie;			// Cookies müssen gespeichert werden

	HPROJECT m_hPr;						// eigene Datenbank
	OPENMODE m_rgOpenMode;				// Mode zum Öffnen (Parameter für TRiAS)

// Storageverwaltung etc.
	STGMODE m_StgMode;
	WStorage m_Stg;						// Storage dieses Projektes
	WStream m_Strm;						// eigene Daten

	WStorage m_ConnStg;					// Storage für Connections
	WStorage m_ViewStg;					// Storage für Ansichten
	WStorage m_QueryStg;				// Storage für Queries
	WStorage m_ObjectStg;				// Storage für SubObjekte
	WStorage m_ConnFiltStg;				// Storage für Verbindungsfilter

	static UINT m_cf;
	static UINT m_cfWorkSpace;
	static UINT m_cfObjects;

// im Storage enthaltene Daten
	WTRiASConnections m_Connections;		// alle zu diesem Projekt gehörenden DatenQuellen
	WTRiASViews m_Views;					// alle zu diesem Projekt gehörenden Ansichten
	WTRiASObjectsCollection m_QueryDefs;	// alle (übergreifenden) Objektklassen dieses Projektes
	WTRiASConnectionFilters m_ConnFilters;	// alle Verbindungsfilter

// CookieHolder 
	DWORD m_dwCookieHolderCookie;
};

#endif // !defined(_TRIASPROJECT_H__7C8CB9BD_2EA9_11d1_969E_00A024D6F582__INCLUDED_)

