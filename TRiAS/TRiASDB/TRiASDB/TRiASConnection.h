//////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASConnection.h | Definition of the <c CTRiASConnection> class

#if !defined(AFX_TRIASCONNECTION_H__191A9AF6_37FE_11D1_96B6_00A024D6F582__INCLUDED_)
#define AFX_TRIASCONNECTION_H__191A9AF6_37FE_11D1_96B6_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

#include <Atl/Ciid.h>

#include "CPTRiASPropertyEvents.h"		// connection points

#include "TRiASDatabase.h"
#include "PropertySupport.h"
#include "PropertyBase.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnection

class ATL_NO_VTABLE CTRiASConnection : 
	public ISupportErrorInfo,
	public IOleClientSite,
	public IPersistStreamInit,
	public IPersistStorage,
	public CProxyITRiASPropertyEvents<CTRiASConnection>,
	public IConnectionPointContainerImpl<CTRiASConnection>,
	public CReportErrorComCoClass<CTRiASConnection, &CLSID_TRiASConnection, &IID_ITRiASConnection>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CManagePropertySupport<CTRiASConnection>,
	public CManagePropertyBase<CTRiASConnection>,
	public ITRiASPropertyEvents,
	public IDispatchImpl<ITRiASConnection, &IID_ITRiASConnection, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IProvideClassInfo2Impl<&CLSID_TRiASConnection, &IID_ITRiASPropertyEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASConnection() 
		: m_fIsInitialized(false), m_fIsDirty(false), 
		  m_fIsReadOnly(false), m_fMustConnectAfterLoad(false),
		  m_fHasMultipleFiles(false), m_fPathIsStorageName(false), m_fPathIsConnectName(false),
		  m_fIsInitializing(false), m_fUseOldMks(false),
		  m_rgMode(CONNECTMODE_OpenReadOnly), m_dwCookie(0L),
		  m_dwRegROT(0), m_dwOldRegROT(0), 
#if defined(_REGISTER_WILDCARD_MONIKERS)
		  m_dwRegROTAll(0), m_dwOldRegROTAll(0),
#endif // _REGISTER_WILDCARD_MONIKERS
		  m_bstrName(g_cbNil), m_bstrDesc(g_cbNil), m_bstrConnect(g_cbNil),
		  m_bstrType(g_cbNil), m_bstrPath(g_cbNil), m_bstrRelPath(g_cbNil)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASConnection)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASConnection)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCONNECTION)

	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CTRiASConnection)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASConnection)
		COM_INTERFACE_ENTRY(ITRiASConnection)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY_FUNC(IID_IPersistStorage, 
			offsetofclass(IPersistStorage, _ComMapClass), 
			_Choice)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(ITRiASPropertyEvents)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASConnection)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CTRiASConnection)
		PROPERTYSUPPORT_ENTRY_AGGR(g_cbTRiASCSService, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct();
	void FinalRelease (void);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// IPersistStorage: wird lediglich für Storagebasierte DB's verwendet um diese zu speichern etc.
	STDMETHOD(InitNew)(IStorage *pStorage);
	STDMETHOD(Load)(IStorage *pStorage);
	STDMETHOD(Save)(IStorage *pStorage, BOOL fSameAsLoad);
	STDMETHOD(SaveCompleted)(IStorage *pStorage);
	STDMETHOD(HandsOffStorage)(void);

// IOleClientSite
	STDMETHOD(SaveObject)();
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
	STDMETHOD(GetContainer)(IOleContainer **ppContainer);
	STDMETHOD(ShowObject)();
	STDMETHOD(OnShowWindow)(BOOL fShow);
	STDMETHOD(RequestNewObjectLayout)();

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

// ITRiASPropertyEvents
	STDMETHOD(CreatingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyCreated)(/*[in]*/ IDispatch *pIProp);
	STDMETHOD(ModifyingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToModify)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyModified)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToDelete)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyDeleted)(/*[in]*/ BSTR Name);

// ITRiASConnection
public:
// Properties
	STDMETHOD(get_GuidPath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_VersionLong)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Transactions)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_SchemaUpdatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Database)(/*[out, retval]*/ ITRiASDatabase * *pVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Location)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Location)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Type)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Mode)(/*[out, retval]*/ CONNECTMODE *pVal);
	STDMETHOD(put_Mode)(/*[in]*/ CONNECTMODE newVal);
	STDMETHOD(get_Param)(/*[out, retval]*/ CONNECTPARAM *pVal);
	STDMETHOD(get_Status)(/*[out, retval]*/ CONNECTSTATUS *pVal);
	STDMETHOD(get_ConnectInfo)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ConnectInfo)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Locations)(/*[out, retval]*/ IUnknown **pVal);
	STDMETHOD(put_Locations)(/*[in]*/ IUnknown *newVal);

// Methods
	typedef enum tagSAVEMODE {
		SAVEMODE_NoSave = 0,
		SAVEMODE_NormalSave = 1,
		SAVEMODE_SaveAs = 2,
	} SAVEMODE;

	STDMETHOD(Disconnect)(/*[in, optional, defaultvalue(CONNECTMODE_UseDefaultMode)]*/ CONNECTMODE rgMode);
	STDMETHOD(Connect)(/*[in, optional, defaultvalue(CONNECTMODE_UseDefaultMode)]*/ CONNECTMODE rgMode);
	STDMETHOD(Remove)();
	STDMETHOD(SaveConnectedDatabase)(/*[in]*/ CONNECTMODE rgMode);
	STDMETHOD(SaveAsConnectedDatabase)(/*[in]*/ CONNECTMODE rgMode);

// ITRiASPropertyBase
	HRESULT IsInitialized()
	{
		if (m_fIsInitialized/* && m_DB.IsValid()*/)
			return S_OK;
		if (m_fIsInitializing)
			return S_FALSE;
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	}
	HRESULT PropertiesRefreshed();		// Properties wurden neu eingelesen

	ITRiASConnection *GetConnection() { return static_cast<ITRiASConnection *>(this); }
	IDispatch *GetDispatch() { return static_cast<IDispatch *>(GetConnection()); }

// AskMode rücksetzen
	static void ResetAskMode() { m_rgAskMode = ASKMODE_NoOptions; }
	static void ResetAskModeOpenRO() { m_rgAskMode &= ~(ASKMODE_YesAllOpenRO|ASKMODE_NoAllOpenRO); }
	static void ResetAskModeSave() { m_rgAskMode &= ~(ASKMODE_YesAllSelectOtherName|ASKMODE_NoAllSelectOtherName|ASKMODE_YesAllSave|ASKMODE_NoAllSave); }

protected:
	HRESULT Fire_OpeningConnection (BSTR Name, VARIANT_BOOL *pVal);
	HRESULT Fire_ConnectionToOpen (BSTR Name);
	HRESULT Fire_ConnectionOpened (IDispatch * pIConn);
	HRESULT Fire_ClosingConnection (IDispatch *pIConn, VARIANT_BOOL * pVal);
	HRESULT Fire_ConnectionToClose (IDispatch * pIConn);
	HRESULT Fire_ConnectionClosed(BSTR Name);
	HRESULT Fire_RenamingConnection(BSTR OldName, BSTR NewName, VARIANT_BOOL * pVal);
	HRESULT Fire_ConnectionToRename(BSTR OldName, BSTR NewName);
	HRESULT Fire_ConnectionRenamed(IDispatch *pIConn);
	HRESULT Fire_ChangingConnectedDatasource(IDispatch *pIConn, VARIANT_BOOL *pVal);
	HRESULT Fire_ConnectedDatasourceToChange(IDispatch *pIConn);
	HRESULT Fire_ConnectedDatasourceChanged(IDispatch *pIConn);

	HRESULT AskToOpenConnectionRO (HRESULT hr);
	bool TellThatCannotSaveDirectly (LPCSTR pcName, UINT resID, BSTR *pNewName, bool &rfCommit);
	bool AskToSaveDirectly (LPCSTR pcName, bool &rfNewName, BSTR *pNewName);
	bool AskToSaveNormal (LPCSTR pcName, bool &rfCommit, bool fSaving);
	bool AskToRepairLink ();
	bool ShowSaveAsDialog (UINT uiCap, LPCSTR pcName, BSTR *pbstrNewName, UINT uiResIDApp = 0);
	bool ShowFileDialog (UINT uiCap, BOOL fOpenDlg, BSTR bstrName, BSTR *bstrNewName, ITRiASDataServerRegEntry *pIRegEntry = NULL);
	bool ShowOpenFileDialog (UINT uiCap, BSTR bstrName, BSTR *bstrNewName, ITRiASDataServerRegEntry *pIRegEntry = NULL)
	{
		return ShowFileDialog (uiCap, TRUE, bstrName, bstrNewName, pIRegEntry);
	}
	bool ShowSaveAsFileDialog (UINT uiCap, BSTR bstrName, BSTR *bstrNewName, ITRiASDataServerRegEntry *pIRegEntry = NULL)
	{
		return ShowFileDialog (uiCap, FALSE, bstrName, bstrNewName, pIRegEntry);
	}
	bool ShowFileBasedDialog (ITRiASDataServerRegEntry *pIRegEntry, UINT uiCap, BOOL fOpenDlg, BSTR bstrName, BSTR *pbstrNewName);
	bool ShowDirectoryBasedDialog (UINT uiCap, BOOL fOpenDlg, BSTR bstrName, BSTR *pbstrNewName);
	bool TellThatWeCanOpenOnlyOne (BSTR bstrName);

	HRESULT SaveConnectedDatabase (CONNECTMODE rgMode, bool fSaving);

	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);
	HRESULT GetOldThisMoniker (DWORD dwWhich, IMoniker **ppIMk);
	HRESULT GetMkName (BSTR *pbstrMkName);

	HRESULT RenameConnection (BSTR bstrName = NULL);
	HRESULT RenamingConnection (void);

	HRESULT GetProjectPath (os_string &rStrPath);
	HRESULT MakeFullRelativePath (BSTR *pbstrFullRel);
	HRESULT CalculateRelPath (LPCSTR pcRisPath);
	HRESULT GetProjectSubStorage (bool fRO, IStorage **ppIStg);

	HRESULT PutLocation (BSTR newVal);

	HRESULT EnsureUniqueGuid (ITRiASProject *pIPrj, CComBSTR &rbstrGuid);

// support für Fragen bei RO öffnen
	enum ASKMODE {
		ASKMODE_NoOptions = 0x0,
		ASKMODE_YesAllOpenRO = 0x1,				// alle weiteren RO öffnen
		ASKMODE_NoAllOpenRO = 0x2,				// alle weiteren nicht öffnen
		ASKMODE_YesAllSelectOtherName = 0x4,	// für alle weiteren Namen vorgeben
		ASKMODE_NoAllSelectOtherName = 0x8,		// alle weiteren einfach ohne speichern schließen
		ASKMODE_YesAllSave = 0x10,				// für alle weiteren speichern
		ASKMODE_NoAllSave = 0x20,				// alle weiteren einfach nicht speichern
	};
	static DWORD m_rgAskMode;

private:
// allgemeine Daten
	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	bool m_fIsDirty;
	bool m_fIsInitialized;		// wurde initialisiert
	bool m_fIsInitializing;		// wird gerade initialisiert
	bool m_fMustConnectAfterLoad;
	bool m_fUseOldMks;			// 'altes' MonikerFormat

// connection spezifische Daten
	CComBSTR m_bstrName;		// ConnectionName
	CComBSTR m_bstrDesc;		// Beschreibende Info
	CComBSTR m_bstrConnect;		// ConnectString zur Database
	CComBSTR m_bstrType;		// ProgID der TRiASDatabase
	CComBSTR m_bstrPath;		// Pfad zur Database
	CComBSTR m_bstrRelPath;		// relativer Pfad vom Projekt zur Database
	CIID m_GuidPath;			// Guid für pfadunabhängige Moniker
	WEnumString m_Files;		// evtl. DateiNamen

	bool m_fIsReadOnly;			// Connection ist RO
	bool m_fHasMultipleFiles;
	bool m_fPathIsStorageName;	// in m_bstrPath ist StorageName relativ zu Projektwurzel
	bool m_fPathIsConnectName;	// in m_bstrPath ist Connectstring einer 'freien' Datenquelle
	CONNECTMODE m_rgMode;
	DWORD m_dwCookie;			// ConnectionEvents

	DWORD m_dwRegROT;
	DWORD m_dwOldRegROT;

#if defined(_REGISTER_WILDCARD_MONIKERS)
	DWORD m_dwRegROTAll;
	DWORD m_dwOldRegROTAll;
#endif // _REGISTER_WILDCARD_MONIKERS

// angehängte TRiASDatabase
	WTRiASDatabase m_DB;
};

///////////////////////////////////////////////////////////////////////////////
// Version des PersistStream-Formates
const long CONNECTION_SIGNATURE = 0x4E4E4F43L;	// "CONN"
const long CONNECTION_VERSION_MINOR_MASK = 0xff;
const long CONNECTION_VERSION_100 = 0x0100L;
const long CONNECTION_VERSION_101 = 0x0101L;
const long CONNECTION_VERSION_102 = 0x0102L;
const long CONNECTION_VERSION_103 = 0x0103L;	// #HK990710
const long CONNECTION_VERSION_104 = 0x0104L;	// #HK991117: m_fPathIsStorageName
const long CONNECTION_VERSION_105 = 0x0105L;	// #HK000112: m_fPathIsConnectName
const long CONNECTION_VERSION_106 = 0x0106L;	// #HK000114: m_fPathIsConnectName hatte einen BUG
const long LASTKNOWN_CONNECTION_VERSION = CONNECTION_VERSION_106;

#endif // !defined(AFX_TRIASCONNECTION_H__191A9AF6_37FE_11D1_96B6_00A024D6F582__INCLUDED_)
