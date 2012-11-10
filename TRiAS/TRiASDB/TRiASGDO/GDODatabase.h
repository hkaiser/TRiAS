// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.02.2000 20:07:47 
//
// @doc
// @module GDODatabase.h | Declaration of the <c CGDODatabase> class

#if !defined(_GDODATABASE_H__7884B7C8_5470_4F74_ACCF_84945553088E__INCLUDED_)
#define _GDODATABASE_H__7884B7C8_5470_4F74_ACCF_84945553088E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stl/hashmap.h>

class ATL_NO_VTABLE CGDODatabase : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CGDODatabase, &CLSID_GDODatabase>,
	public CErrSupport<CGDODatabase, &IID_IGDODatabase>,
	public IDispatchImpl<IGDODatabase, &IID_IGDODatabase, TLB_TRiASGDO_SIGNAT>,
	public IDispatchImpl<ITRiASAccessDatabase, &IID_ITRiASAccessDatabase, TLB_TRiASDB_SIGNAT>,
	public IDispatchImpl<ITRiASDatabase, &IID_ITRiASDatabase, TLB_TRiASDB_SIGNAT>,
	public IConnectionPointContainerImpl<CGDODatabase>,
	public CManagePropertySupportWithDefaultValues<CGDODatabase>,
	public CProxyITRiASPropertyEvents<CGDODatabase>,
	public ITRiASPropertyCallback,
	public COleItemContainerSupport<CGDODatabase>,
	public CManagePropertyBase<CGDODatabase>
{
//////////////////////////////////////////////////////////////////////
	bool						m_bDirty;
	CComPtr<IDispatch>			m_pApplication;
	CComPtr<IDispatch>			m_pParent;
	VARIANT_BOOL				m_bWritable;
	DATABASESTORAGEMODE			m_rgStgMode;

//////////////////////////////////////////////////////////////////////
// unsere Heiligtümer ;-)
	AC_DGMConnection			m_pDBConnection;
	AC_GDatabase				m_pGDatabase;

//////////////////////////////////////////////////////////////////////
// diese Services werden gebraucht
	WDGMServerTransService		m_pDGMServerTransService;
	WTRiASCSStorageServiceGDO	m_pTRiASCSStorageServiceGDO;			// StorageService
	WTRiASCSTransform			m_pTRiASCSTransform;	// Koordinatentransformator
	WTRiASCS					m_csIn;					// Eingangskoordinatensystem
	CSID						m_csGUID;				// GUID des Eingangskoordinatensystems für m_csTransform

//////////////////////////////////////////////////////////////////////
// 
	WDGMGeometryStorageService	m_stgGMService;			// Geomedia-Storageservice
	WDGMCoordSystemsMgr			m_pDGMCoordSystemsMgr;	// Standard-Outputkoordinatensystem für Geomedia

	HRESULT EnsureObjectsColl();
	HRESULT ReloadObjectsColl();
	WGDOObjectsCollection		m_pGDOObjectsCollection;

//////////////////////////////////////////////////////////////////////
// Datenbankcontainer
	CCSRectangleGeometry		m_rcContainer;
	bool						m_bInitContainer;

//////////////////////////////////////////////////////////////////////
// Standardgeometrien
	typedef map<long, CComVariant> MapGeoTypeToDefault;
	MapGeoTypeToDefault			m_mapGeoTypeToDefault;
	HRESULT SetupDefaultGeometries();

	CRandomGenerator			m_randGen;		// eindeutige Namen in char()-PKey-Feldern

	long						m_lMaxModEntry;	// größter ModLogEntry, der ignoriert werden kann
	long						m_lSessionId;	// Id dieser Session

	HRESULT	DoCloseDatabase();
	HRESULT	DoCreateConnection(
			/*[in]*/ const BSTR &Name
			, /*[in]*/ const BSTR &connName
			, /*[in, optional, defaultvalue]*/ const BSTR &Source
			, /*[in, optional, defaultvalue]*/ const VARIANT_BOOL Exclusive
			, /*[in, optional, defaultvalue]*/ const VARIANT_BOOL ReadOnly
			, /*[in, optional, defaultvalue]*/ const VARIANT_BOOL ModTrack
	);

// Hilfsfunktionen für IGDOAccess
	HRESULT	TryUpdate(GRecordset* rs) 
	{
		EXT_ERROR_FAILED_HRESULT(rs->Update(), NDB_E_NATIVEDB);
		return S_OK;
	}
	HRESULT CopyDefaults(WGFields& flds, WTRiASFeatures& feats);
	
// Cache für Geometrien
//	typedef			MapCB2CV MapOfGeometrys;	// wird nur in der Klasse gebraucht
	class CHashBSTR :
		public unary_function<CComBSTR, size_t>
	{
	public:
		size_t operator() (const CComBSTR &rToHash) const
		{
			return LHashValOfName (LOCALE_SYSTEM_DEFAULT, rToHash);
		}
	};
	typedef hash_map<CComBSTR, CComVariant, CHashBSTR> MapOfGeometrys;
	MapOfGeometrys	m_mapOfGeometrysR;

	CComBSTR m_strCurrGeomR;
	HRESULT LoadGeometrys(IGDOObjects *pIGDOObjects, const CComBSTR& strClassName, const CComBSTR& strGeometryName, const CComBSTR& strPKeyname);

	HRESULT RetrieveGeoSearchParams(SAFEARRAY *pParams, VARIANT& vGeometryFilter, BOOL& bExact);
	HRESULT RetrieveTextSearchParams(SAFEARRAY *pParams, CComBSTR& strWhereClause);
	HRESULT GetObjectNames(IGDOObjects* pObjects, IGDOObject* pObject, CComBSTR& strObjectname, CComBSTR& strPKeyname);

public:
	CGDODatabase() :
		m_bWritable(VARIANT_FALSE), m_rgStgMode(DATABASESTORAGEMODE_Unknown),
		m_bInitContainer(false),
		m_bDirty(false),
		m_strCurrGeomR(_T("")),
		m_lMaxModEntry(-1), m_lSessionId(0)
	{
	}
	~CGDODatabase();
	
	DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, FinalConstruct);
	DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, FinalRelease);

	HRESULT IsInitialized() 
	{
		return ((!!m_pDBConnection && !!m_pGDatabase) ? S_OK : E_FAIL);
	}

public:
	DECLARE_REGISTRY_RESOURCEID(IDR_GDODATABASE)
	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDODatabase)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDODatabase)
	BEGIN_COM_MAP(CGDODatabase)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASDatabase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(IGDODatabase)
		COM_INTERFACE_ENTRY(ITRiASDatabase)
		COM_INTERFACE_ENTRY(ITRiASAccessDatabase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IOleItemContainer)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IOleContainer)				// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IParseDisplayName)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CGDODatabase)
//		PROPERTYSUPPORT_ENTRY(g_cbObjectsMap, CLSID_GenObjectMap)
//		PROPERTYSUPPORT_ENTRY(g_cbObjectMap, CLSID_GenObjectMap)
		PROPERTYSUPPORT_ENTRY_INITFUNC(g_cbGDODataSource, CLSID_TRiASVariantProperty, GetDefaultValuesProc())
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

// Defaultwerte für Properties
	BEGIN_PROPERTYSUPPORT_DEFAULTVALUE_MAP()
		PROPERTYSUPPORT_DEFAULTVALUE_ENTRY(g_cbGDODataSource, VT_BOOL, VARIANT_TRUE, PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly)
	END_PROPERTYSUPPORT_DEFAULTVALUE_MAP()

	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CGDODatabase)
		OLEITEMCONTAINERSUPPORT_ENTRYEX(g_cbMkObjectsDef, GetObjectsDef, ParseObjectsDef)
		OLEITEMCONTAINERSUPPORT_ENTRYEX(g_cbMkObjectDef, GetObjectDef, ParseObjectDef)
	END_OLEITEMCONTAINERSUPPORT_MAP()

	BEGIN_CONNECTION_POINT_MAP(CGDODatabase)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
	END_CONNECTION_POINT_MAP()

	IDispatch *GetDispatch() { return static_cast<IGDODatabase *>(this); }

protected:
// OleItemContainerSupport
	HRESULT GetObjectsDef(LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetObjectDef(LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT ParseObjectsDef(LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut);
	HRESULT ParseObjectDef(LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut);

// OnReload...
	HRESULT OnResetLookupWindow();
	HRESULT OnReloadObjects();
	HRESULT OnReloadEnvelope();

public:
// (I)(T)RiAS(P)roperty(S)upport
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, CreateProperty,/*[in]*/ BSTR, Name, /*[out, retval]*/ ITRiASProperty**, Property);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, RemoveProperty,/*[in]*/ BSTR, Name);
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, PutValue,/*[in]*/ BSTR, Name, VARIANT, newVal);
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, GetValue,/*[in]*/ BSTR, Name, VARIANT*, pVal);
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, PutType,/*[in]*/ BSTR, Name, PROPERTY_TYPE, newVal);
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, GetType,/*[in]*/ BSTR, Name, PROPERTY_TYPE*, pVal);
	DECLARE_DEBUG_FUNCENTRY_3(CGDODatabase, GetValueAndType,/*[in]*/ BSTR, Name, /*[out]*/ VARIANT*, pVal, /*[out]*/ PROPERTY_TYPE*, pType);
	DECLARE_DEBUG_FUNCENTRY_3(CGDODatabase, PutValueAndType,/*[in]*/ BSTR, Name, /*[in]*/ VARIANT, Val, /*[in]*/ PROPERTY_TYPE, Type);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, Refresh,/*[in]*/ BSTR, Name);

// (I)(T)RiAS(A)ccess(D)atabase
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Views,/*[out, retval]*/ ITRiASViews**, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_StartViewName,/*[out, retval]*/ BSTR*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_ObjectsDefs,/*[out, retval]*/ ITRiASObjectsCollection**, pVal);
	DECLARE_DEBUG_FUNCENTRY_4(CGDODatabase, get_ObjectsDef,/*[in]*/ VARIANT, vItem, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, fCreate, /*[in, optional, defaultvalue]*/ BSTR, Type, /*[out, retval]*/ ITRiASObjects**, pVal);
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, get_Envelope, ENVELOPETYPE, rgType, IDispatch**, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_ObjectCount, long*, pVal);
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, get_AttachedCS, BSTR, bstrDbName, BSTR *, pbstrAssocCS);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_ConnectionFilter, ITRiASConnectionFilter **, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, put_ConnectionFilter, ITRiASConnectionFilter *, pVal);

// ITRiASBase
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Parent,/*[out, retval]*/ IDispatch**, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, put_Parent,/*[in]*/ IDispatch*, newVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Application,/*[out, retval]*/ IDispatch**, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, put_Application,/*[in]*/ IDispatch*, newVal);

// ITRiASDatabase
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_TemporaryName,/*[out, retval]*/ BSTR*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Temporary,/*[out, retval]*/ VARIANT_BOOL*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, put_Temporary,/*[in]*/ VARIANT_BOOL, newVal);

	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_IsDirty,/*[out, retval]*/ VARIANT_BOOL*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, put_IsDirty,/*[in]*/ VARIANT_BOOL, newVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Handle,/*[out, retval]*/ INT_PTR *, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_VersionLong,/*[out, retval]*/ LONG*, pVal);
    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Version, BSTR*, Version);

	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_SchemaUpdatable,/*[out, retval]*/ VARIANT_BOOL*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Name,/*[out, retval]*/ BSTR*, pVal);

	DECLARE_DEBUG_FUNCENTRY_5(CGDODatabase, OpenDatabase
		, /*[in]*/ BSTR, Name
		, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, Exclusive
		, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, ReadOnly
		, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, ModTrack
		, /*[in, optional, defaultvalue]*/ BSTR, Source
	);
	DECLARE_DEBUG_FUNCENTRY_5(CGDODatabase, OpenFilesAsDatabase,
		/*[in]*/ IUnknown*, pEnum
		, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, bExclusive
		, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, bReadOnly
		, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, bModTrack
		, /*[in, optional, defaultvalue]*/ BSTR, Source
	);
	DECLARE_DEBUG_FUNCENTRY_3(CGDODatabase, CreateDatabaseFromFiles, IUnknown*, pIEnum, BSTR, Locale, BSTR, Source);
	DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, Close);

    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_CollatingOrder, long*, pCollatingOrder);
    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Connect, BSTR*, Connect);
    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Transactions, VARIANT_BOOL*, Transactions);

    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_GAliasTable, BSTR*, AliasTableName);
    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_SQLConformance, long*, pSQLConformance);

    DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, BeginTrans);
    DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, ClearModificationLog,/*[in, optional, defaultvalue]*/ LONG, Entry);
    DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, CommitTrans);
    DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, Rollback);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, ReLoad, /*[in]*/ RELOADDATABASE, ToReLoad);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, RefreshChangesFromModificationLog, /*[in]*/ ITRiASRefreshChangesCallback *, Callback);

    DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, GetExtension, BSTR, Name, IDispatch**, ppGExtension);

	DECLARE_DEBUG_FUNCENTRY_3(CGDODatabase, CreateDatabase,/*[in]*/ BSTR, Name, /*[in]*/ BSTR, Locale, BSTR, Source);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, SaveAs,/*[in]*/ BSTR, NewName);
	DECLARE_DEBUG_FUNCENTRY_0(CGDODatabase, Save);

	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_OpenedAsCopy,/*[out, retval]*/ VARIANT_BOOL*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_CouldOpenTarget,/*[out, retval]*/ VARIANT_BOOL*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Updatable,/*[out, retval]*/ VARIANT_BOOL*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_Type,/*[out, retval]*/ BSTR*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, get_StorageMode,/*[out, retval]*/ DATABASESTORAGEMODE*, pVal);

	DECLARE_DEBUG_FUNCENTRY_5(CGDODatabase, OpenStorageAsDatabase, IUnknown *, pIStorage, VARIANT_BOOL, Exclusive, VARIANT_BOOL, fReadOnly, VARIANT_BOOL, ModTrack, BSTR, Source);
	DECLARE_DEBUG_FUNCENTRY_4(CGDODatabase, CreateDatabaseOnStg, IUnknown *, pIUnk, BSTR, Name, BSTR, Locale, BSTR, Source);

// IGDODatabase
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, GetDefaultGeometry
			, /*[in]*/ long, geometryType
			, /*[out, retval]*/ VARIANT*, vDefaultGeometry
	);
	DECLARE_DEBUG_FUNCENTRY_3(CGDODatabase, GetPipes
			, /*[out]*/ IUnknown**, ppIOriginatingPipe
			, /*[out]*/ IUnknown**, ppICSSTransformPipe
			, /*[out]*/ IUnknown**, ppISpatialFilterPipe
	);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, TransformGeometry, /*[in]*/ IUnknown*, pObject);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODatabase, TransformGeometryInverse, /*[in]*/ IUnknown*, pObject);
	DECLARE_DEBUG_FUNCENTRY_6(CGDODatabase, GetRecordset
			, /*[in]*/ BSTR, strTablename
			, /*[in]*/ VARIANT, vGeometryFilter
			, /*[in]*/ BSTR, strGeometryField
			, /*[in, optional, defaultvalue(NULL)]*/ BSTR, strFilter
			, VARIANT *, pvCSGuid, 
			, /*[out, retval]*/ IUnknown**, ppIRecordset
	);

//////////////////////////////////////////////////////////////////////
//	Operationen für Objektklassen
	DECLARE_DEBUG_FUNCENTRY_2(CGDODatabase, CreateObject
		, /*[in]*/ IGDOObjects*, pObjects
		, /*[out, retval]*/ BSTR*, pStrNameOfObject
	);
	DECLARE_DEBUG_FUNCENTRY_5(CGDODatabase, QueryGeometry
		, /*[in]*/ IGDOObjects*, pGDOObjects
		, /*[in]*/ IGDOObject*, pGDOObject
		, /*[in]*/ IGDOFeature*, pGDOFeature
		, /*[in, out]*/ SAFEARRAY**, pConstraints
		, /*[in, out]*/ VARIANT*, pValue
	);
	DECLARE_DEBUG_FUNCENTRY_4(CGDODatabase, UpdateGeometry
		, /*[in]*/ IGDOObjects*, pGDOObjects
		, /*[in]*/ IGDOObject*, pGDOObject
		, /*[in]*/ IGDOFeature*, pGDOFeature
		, /*[in]*/ VARIANT, newValue
	);
};

#endif // !defined(_GDODATABASE_H__7884B7C8_5470_4F74_ACCF_84945553088E__INCLUDED_)
