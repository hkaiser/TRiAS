#ifndef __CGDOOBJECTS_H_
#define __CGDOOBJECTS_H_

DefineSmartInterface2(DMatchString, IID_DMatchString);	// WDMatchString

class ATL_NO_VTABLE CGDOObjects : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CGDOObjects, &CLSID_GDOObjects>,
	public CErrSupport<CGDOObjects, &IID_IGDOObjects>,
	public IDispatchImpl<IGDOObjects, &IID_IGDOObjects, TLB_TRiASGDO_SIGNAT>,
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, TLB_TRiASGDO_SIGNAT>,
	public COleItemContainerSupport<CGDOObjects>,
	public ITRiASObjectsCallback,
	public IPersistStreamInit,
	public IDispatchImpl<GTableDef, &IID_GTableDef, &LIBID_PClient>
{
private:
	WUnknown m_BaseUnk;
	ITRiASObjects *m_pBaseTRiASObjects;
	ITRiASObjects *BASE_OF_GDOOBJECTS() { return m_pBaseTRiASObjects; }
	long m_lInitData;
	bool m_bFeaturesLoaded;
	bool m_bCounted;
	bool m_fReloaded;
	bool m_fIsDirty;
	bool m_fIsInitialized;
	bool m_bWritable;
	CComBSTR m_strTablename;
	CComBSTR m_bstrLastObjName;

	WDGMConnection m_pDGMConnection;
	WGDatabase m_pGDatabase;
	WDGMCoordSystemsMgr m_pDGMCoordSystemsMgr;
	WTRiASMDSMap m_pTRiASMDSMap;					// Metadatenservicemap
	map<CComBSTR, bool> m_strFeaturesToDelete;

	WTRiASObjectHandleMap m_pTRiASObjectHandleMap;	// globale ObjectMap; singleton Object(!!)
	WTRiASObjectHandleMap m_pTRiASFeatureHandleMap;	// klassenspezifische FeatureMap; Property an der Basisklasse

//	WDGMServerTransService		m_pDGMServerTransService;
//	WDGMGeometryStorageService	m_pDGMGeometryStorageService;

	class CPostFilter 
	{
	private:
		typedef const bool(CPostFilter::*matchfunc)(const BSTR& strValue);

		WGField m_fldToSearch;
		CComBSTR m_strKeyToSearch;
		WDMatchString m_pDMatchString;		// Match-Objekt
		bool m_fFirst;

	public:
		CPostFilter();
		~CPostFilter();
		
		HRESULT	Setup(const BSTR& strCommand, const CComBSTR& strKey, const CComBSTR& strFilter, const short gmType, CComBSTR& strWhereClause);
		HRESULT operator()(AC_GRecordset& rs);
	};
	
	HRESULT	GetGTableDef(WGTableDef& rpGTableDef) 
	{
	WGTableDefs	pGTableDefs;
	
		ERROR_FAILED_HRESULT(m_pGDatabase->get_GTableDefs(pGTableDefs.ppi()), NDB_E_NATIVEDB);
		ERROR_FAILED_HRESULT(pGTableDefs->get_Item(CComVariant(m_strTablename), rpGTableDef.ppi()), NDB_E_NATIVEDB);
		return S_OK;
	}

protected:
////////////////////////////////////////////////////////////////////////////
// Helferfunktionen für's Speichern
	HRESULT UpdateFeatures(ITRiASFeatures* pTRiASFeatures, VARIANT_BOOL* pbChanged);
	HRESULT UpdateFeature(/*const*/ CComBSTR& strOldFieldname, /*const*/ CComBSTR& strNewFieldname, /*const*/ CComBSTR& strDescription);
	HRESULT DeleteFeatures(VARIANT_BOOL* pbChanged);
	HRESULT DeleteFeature(/*const*/ CComBSTR& strFieldname);

////////////////////////////////////////////////////////////////////////////
// Helferfunktionen für Features
	HRESULT GetOrCreateFeature(const CComBSTR& strFieldname, const CComBSTR& strFeaturename, CComBSTR& strMCode, DWORD dwType, ITRiASFeatures* pFeatures, ITRiASFeature **ppIFeat);
	HRESULT EnsureFeatures();
	HRESULT ReloadFeatures(ITRiASFeatures* pTRiASFeatures, CComBSTR& strPrimaryfeature, ITRiASFeatures* pTRiASGeoFeatures, CComBSTR& strPrimarygeometry, bool fForce = false);
	HRESULT QueryFeatures(ITRiASFeatures* pTRiASFeatures, IGDOObject* pGDOObject);
	HRESULT CacheLocatedFeatures(AC_GRecordset &rs, ITRiASFeatures* pTRiASFeatures);

////////////////////////////////////////////////////////////////////////////
// Helferfunktionen für Objekte
	HRESULT EnsureObjectsCounted();
	HRESULT EnsureObjectsLoaded();

////////////////////////////////////////////////////////////////////////////
// Helferfunktionen für Recherche
	HRESULT DoLoadObjects(AC_GRecordset& rs, ITRiASObjects* pTRiASObjects, CPostFilter& postFilter, long& nObjects, bool bForceAdd = false);
	HRESULT RetrieveGeoSearchParams(SAFEARRAY *pParams, WGDODatabase& rpGDODatabase, IDispatch **ppIGeometry, BOOL& bExact);
	HRESULT RetrieveTextSearchParams(SAFEARRAY *pParams, CComBSTR& strKey, CComBSTR& strFilter, short& gmType);
	HRESULT DoSearchObjects(ITRiASObjects* pTRiASObjects, IDispatch *pIGeometry, long lSpatialOperator);
	HRESULT DoSearchObjects(ITRiASObjects* pTRiASObjects, const CComBSTR& strTextFilter, CPostFilter& postFilter);

////////////////////////////////////////////////////////////////////////////
	HRESULT ClearMDSMap();
	HRESULT SetDirty();

	HRESULT GetObjectNames(IGDOObject* pGDOObject, CComBSTR& strObjectname, CComBSTR& strPKeyname);

public:
////////////////////////////////////////////////////////////////////////////
// Konstruktor / Destruktor usw.
//	static HRESULT CreateInstance (IGDOObjects** ppObject);
	CGDOObjects() :
		m_lInitData(0),
		m_bWritable(false),
		m_pBaseTRiASObjects(NULL),
		m_bCounted(false),
		m_bFeaturesLoaded(false),
		m_fReloaded(false),
		m_fIsDirty(false),
		m_fIsInitialized(false),
		m_bstrLastObjName(L"")
	{
	}

	HRESULT FinalConstruct() 
	{
		COM_TRY {
			RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance(CLSID_TRiASObjects, CLSCTX_ALL, GetControllingUnknown()));
			WTRiASObjects	pTRiASObjects;
			RETURN_FAILED_HRESULT(m_BaseUnk->QueryInterface(pTRiASObjects.ppi()));
			m_pBaseTRiASObjects = pTRiASObjects;
			RETURN_FAILED_HRESULT(BASE_OF_GDOOBJECTS()->putref_ObjectsCallback(this));
			
//			m_pDGMGeometryStorageService = WDGMGeometryStorageService(CLSID_GeometryStorageService);
//			m_pDGMServerTransService = WDGMServerTransService(CLSID_ServerTransService);
			m_pTRiASObjectHandleMap = WTRiASObjectHandleMap(CLSID_TRiASObjectHandleMap);		// singleton!
		} COM_CATCH
		return S_OK;
	}
	void FinalRelease(void) 
	{
		m_BaseUnk.Assign(NULL);
	}

protected:
	HRESULT	GetPipes(CComBSTR &strPGeomName, WOriginatingPipe &pO, WDGMCSSTransformPipe &pT, 
		ISpatialFilterPipe **ppF = NULL) 
	{
		EXT_ERROR_FAILED_HRESULT(m_pDGMConnection -> CreateOriginatingPipe(pO.ppi()), NDB_E_NATIVEDB);
		pT = WDGMCSSTransformPipe(CLSID_CSSTransformPipe);
		if (NULL != ppF)
			*ppF = WISpatialFilterPipe(CLSID_SpatialFilterPipe).detach();

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(strPGeomName)), E_FAIL);

#if defined(_DEBUG)
	CComBSTR bstrPGeomNameFld;

	// BEGIN??
	WTRiASFeatures pTRiASFeatures;
	WTRiASFeature pTRiASFeature;
	WGDOFeature pGDOFeature;

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_GeometryFeatures(pTRiASFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strPGeomName), pTRiASFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(bstrPGeomNameFld)), E_FAIL);
	// END??
		_ASSERTE(bstrPGeomNameFld == strPGeomName);
#endif // defined(_DEBUG)
		
		EXT_ERROR_FAILED_HRESULT(pO -> put_Table(m_strTablename), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pO -> put_GeometryFieldName(CComVariant(strPGeomName)), NDB_E_NATIVEDB);

		EXT_ERROR_FAILED_HRESULT(pT -> putref_CoordSystemsMgr(m_pDGMCoordSystemsMgr), NDB_E_NATIVEDB);
		return S_OK;
	}
	HRESULT	GetPipe (CComBSTR &strPGeomName, WOriginatingPipe &pO) 
	{
		EXT_ERROR_FAILED_HRESULT(m_pDGMConnection -> CreateOriginatingPipe(pO.ppi()), NDB_E_NATIVEDB);

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(strPGeomName)), E_FAIL);

#if defined(_DEBUG)
	CComBSTR bstrPGeomNameFld;

	// BEGIN??
	WTRiASFeatures pTRiASFeatures;
	WTRiASFeature pTRiASFeature;
	WGDOFeature pGDOFeature;

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_GeometryFeatures(pTRiASFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strPGeomName), pTRiASFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(bstrPGeomNameFld)), E_FAIL);
	// END??
		_ASSERTE(bstrPGeomNameFld == strPGeomName);
#endif // defined(_DEBUG)

		EXT_ERROR_FAILED_HRESULT(pO -> put_Table(m_strTablename), NDB_E_NATIVEDB);
//		EXT_ERROR_FAILED_HRESULT(pO -> put_GeometryFieldName(CComVariant(strPGeomName)), NDB_E_NATIVEDB);
		return S_OK;
	}

	HRESULT	GetPipe (WOriginatingPipe &pO) 
	{
		EXT_ERROR_FAILED_HRESULT(m_pDGMConnection -> CreateOriginatingPipe(pO.ppi()), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pO -> put_Table(m_strTablename), NDB_E_NATIVEDB);
		return S_OK;
	}

	HRESULT GetFilter(CComBSTR& strObjectname, CComBSTR &strFieldname, CComBSTR &strFilter) 
	{
	WTRiASFeatures pTRiASFeatures;
	WTRiASFeature pTRiASFeature;
	WGDOFeature pGDOFeature;

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_PrimaryKey(CLEARED(strFieldname)), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strFieldname), pTRiASFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strFieldname)), E_FAIL);
	
	// wenn FeldTyp gdbText ist, dann Feldnamen quoten
	short gmType;
	
		ERROR_FAILED_HRESULT(WGField(pTRiASFeature) -> get_Type(&gmType), NDB_E_NATIVEDB);
	
		strFilter = strFieldname;
		strFilter.Append(L"=");
		if (gdbText == gmType) 
			strFilter.Append(QuoteStatement(strObjectname));
		else
			strFilter.Append(strObjectname);
		return S_OK;
	}
	HRESULT LocateRecord(CComBSTR &strObjectname, AC_GRecordset &rs, CComBSTR &strPKeyname /*PKey*/) 
	{
	CComBSTR strFilter;
	
		RETURN_FAILED_HRESULT(GetFilter(strObjectname, strPKeyname, strFilter));

	WOriginatingPipe pO;
	CComBSTR strGeometry;

		RETURN_FAILED_HRESULT(GetPipe(strGeometry, pO));
//		EXT_ERROR_FAILED_HRESULT(pO -> put_Table(EnBraceStatement(m_strTablename)), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pO -> put_Filter(strFilter), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pO -> get_OutputRecordset(rs.ppi()), NDB_E_NATIVEDB);

	// BEGIN??
		EXT_ERROR_FAILED_HRESULT(rs -> MoveFirst(), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(rs -> MoveLast(), NDB_E_NATIVEDB);
	
	long lCount = 0;
		
		EXT_ERROR_FAILED_HRESULT(rs -> get_RecordCount(&lCount), NDB_E_NATIVEDB);
	// END??
		return S_OK;
	}

	HRESULT	OnChangingName(const VARIANT& vNewName, VARIANT_BOOL *pbDisallow);
	HRESULT OnChangedName(const VARIANT& vOldName);

	HRESULT OnChangingDescription(const VARIANT& vNewDescr, VARIANT_BOOL *pbDisallow);
	HRESULT OnChangedDescription(const VARIANT& vOldValue);

	HRESULT OnChangingOKS(const VARIANT& vNewOKS, VARIANT_BOOL* pbDisallow);
	HRESULT OnChangedOKS(const VARIANT& vOldOKS);

	HRESULT OnChangingHandle(const VARIANT& vNewHandle, VARIANT_BOOL* pbDisallow);
	HRESULT OnChangedHandle(const VARIANT& vOldHandle);

	HRESULT OnChangingTypes(const VARIANT& vNewTypes, VARIANT_BOOL* pbDisallow);
	HRESULT OnChangedTypes(const VARIANT& vOldTypes);

	HRESULT IsInitialized() 
	{
		return ((!m_pGDatabase /*|| !m_pMetadataService*/) ? E_FAIL : S_OK);
	}

public:
	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDOObjects)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDOObjects)
	DECLARE_REGISTRY_RESOURCEID(IDR_GDOOBJECTS)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_AGGREGATE_EX_SUPPORT();
	BEGIN_COM_MAP(CGDOObjects)
		COM_INTERFACE_ENTRY(IGDOObjects)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IOleClientSite, m_BaseUnk.p)
		COM_INTERFACE_ENTRY(ITRiASHandle)
		COM_INTERFACE_ENTRY(ITRiASObjectsCallback)

		COM_INTERFACE_ENTRY2(IDispatch, IGDOObjects)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObjects, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertyBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertySupport, m_BaseUnk.p)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatureEvents, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_CHAIN(errsupport_t)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)

		COM_INTERFACE_ENTRY(IOleItemContainer)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IOleContainer)				// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IParseDisplayName)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo2, m_BaseUnk.p)

//	// selbst nichts zu speichern, daher alles an das Aggregat delegieren
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStream, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStreamInit,m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersist,m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IOleObject, m_BaseUnk.p)
		COM_INTERFACE_ENTRY(GTableDef)

		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CGDOObjects)
		OLEITEMCONTAINERSUPPORT_ENTRY(g_cbMkFeature, GetFeature)
	END_OLEITEMCONTAINERSUPPORT_MAP()
	HRESULT GetFeature(LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	inline IDispatch *GetDispatch() { return static_cast < IGDOObjects *>(this); }
public:
// IGDOObjects
	DECLARE_DEBUG_FUNCENTRY_6(CGDOObjects, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ long, objsTypes
		, /*[in]*/ BSTR, strOKS
		, /*[in]*/ BSTR, strTablename
		, /*[in]*/ BSTR, strClassname
	);
	DECLARE_DEBUG_FUNCENTRY_7(CGDOObjects, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ long, objsTypes
		, /*[in]*/ BSTR, strOKS
		, /*[in]*/ BSTR, strTablename
		, /*[in]*/ BSTR, strClassname
		, /*[in]*/ BSTR, strDescription
	);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, CreateFeatures
		, /*[in]*/ IGDOObject*, pGDOObject
		, /*[in]*/ IGDOFeatures**, ppTRiASFeatures
	);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, SetupFeatures
		, /*[in]*/ IGDOFeatures*, pGDOFeatures
	);
	DECLARE_DEBUG_FUNCENTRY_5(CGDOObjects, CreateFeature
		, /*[in]*/ IGDOFeatures*, pGDOFeatures
		, /*[in]*/ VARIANT, vNameOrHandle
		, /*[in]*/ BSTR, bstrType
		, /*[in]*/ long, lType
		, /*[out, retval]*/ IGDOFeature**, ppIGDOFeature
	);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, DeleteFeature
		, /*[in]*/ IGDOFeatures*, pGDOFeatures
		, /*[in]*/ VARIANT, vNameOrHandle
	);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, RenameFeature
		, /*[in]*/ IGDOFeature*, pFeature
		, /*[in]*/ VARIANT, vOldName
	);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, ReclassFeature
		, /*[in]*/ IGDOFeature*, pFeature
		, /*[in]*/ VARIANT, vOldMCode
	);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, RedescribeFeature
		, /*[in]*/ IGDOFeature*, pFeature
	);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOObjects, UpdateFeature
		, /*[in]*/ IGDOFeature*, pGDOFeature
		, /*[in]*/ IGDOObject*, pGDOObject
		, /*[in]*/ VARIANT, vNewValue
	);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOObjects, QueryFeature
		, /*[in]*/ IGDOFeature*, pGDOFeature
		, /*[in]*/ IGDOObject*, pGDOObject
		, /*[out, retval]*/ VARIANT*, pvNewValue
	);

	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, RenameObject
		, /*[in]*/ IGDOObject*, pGDOObject
		, /*[in]*/ BSTR, strOldName
	);

	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, get_Tablename
		, /*[out, retval]*/ BSTR*, pVal
	);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, put_Tablename
		, /*[in]*/ BSTR, pVal
	);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, Save
		, /*[in, out]*/ VARIANT_BOOL*, pbHaveChanced
	);

// ITRiASSearchObjects
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, ConsiderSearch, /*[in]*/ BSTR, Command, /*[in, optional]*/ SAFEARRAY*, pParams);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOObjects, SearchObjects, /*[in]*/ BSTR, Command, /*[in]*/ ITRiASObjects*, ppIObjs, /*[in, optional]*/ SAFEARRAY *, pParams);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, ConstraintObjects, /*[in]*/ ITRiASObjects*, pObjs);

// ITRiASObjectsCallback
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, get_DefaultType,/*[out, retval]*/BSTR*, strType);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, SetupObjects, SETUPOBJECTSMODE, mode);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, SetupFeatures, SETUPFEATURESMODE, SetupMode);
	DECLARE_DEBUG_FUNCENTRY_4(CGDOObjects, OnCreate,/*[in]*/ BSTR, Name, /*[in]*/ BSTR, progId, OBJECTTYPE, objType, ITRiASObject**, pObj);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOObjects, OnChanging,/*[in]*/ CHANGEDOBJECTS, rgWhat, VARIANT, vNewValue, VARIANT_BOOL*, pbDisallow);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, OnChanged,/*[in]*/ CHANGEDOBJECTS, rgWhat, VARIANT, vOldValue);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, OnDelete,/*[in]*/ INT_PTR, vWhich);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, OnAdd,/*[in]*/ ITRiASObject*, pObject, CLASSIFYMODE, mode);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, OnRemove, ITRiASObject*, Obj);
    DECLARE_DEBUG_FUNCENTRY_2(CGDOObjects, MapFeatureHandle, VARIANT, NameOrHandle, VARIANT *, NewNameOrHandle);
    DECLARE_DEBUG_FUNCENTRY_0(CGDOObjects, OnFinalRelease);

// ITRiASHandle
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, GetHandle, LONG*, pVal) 
	{
		CHECKINPOINTER(pVal);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS()->get_Handle((INT_PTR *)pVal), E_FAIL);
		return S_OK;
	}
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjects, PutHandle, LONG, pVal) 
	{
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS()->put_Handle(pVal), E_FAIL);
		return S_OK;
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// GTableDef
	STDMETHOD(get_GFields)(GFields * * Fields) 
	{
		CHECKOUTPOINTER(Fields);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_GFields(Fields), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_GIndexes)(GIndexes * * Indexes) 
	{
		CHECKOUTPOINTER(Indexes);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_GIndexes(Indexes), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_DateCreated)(VARIANT * pDate) 
	{
		CHECKOUTPOINTER(pDate);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_DateCreated(pDate), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_LastUpdated)(VARIANT * pLastUpdated) 
	{
		CHECKOUTPOINTER(pLastUpdated);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_LastUpdated(pLastUpdated), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_Name)(BSTR * pName) 
	{
		CHECKOUTPOINTER(pName);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_Name(pName), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(put_Name)(BSTR pName) 
	{
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->put_Name(pName), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_RecordCount)(LONG * pCount) 
	{
		CHECKOUTPOINTER(pCount);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_RecordCount(pCount), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_Updatable)(VARIANT_BOOL * pUpdatable) 
	{
		CHECKOUTPOINTER(pUpdatable);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->get_Updatable(pUpdatable), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(CreateField)(VARIANT Name, VARIANT Type, VARIANT Size, GField * * ppField) 
	{
		CHECKOUTPOINTER(ppField);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->CreateField(Name, Type, Size, ppField), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(CreateIndex)(VARIANT Name, GIndex * * ppIndex) 
	{
		CHECKOUTPOINTER(ppIndex);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->CreateIndex(Name, ppIndex), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(GetExtension)(BSTR Name, IDispatch * * ppGExtension) 
	{
		CHECKOUTPOINTER(ppGExtension);
		COM_TRY {
			WGTableDef	pGTableDef;
			RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
			EXT_ERROR_FAILED_HRESULT(pGTableDef->GetExtension(Name, ppGExtension), NDB_E_NATIVEDB);
		} COM_CATCH;
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long GDOOBJECTS_SIGNATURE = 0x53424F47L;	// "GOBS"
const long GDOOBJECTS_VERSION = 0x0100L;
const long LASTKNOWN_GDOOBJECTS_VERSION = GDOOBJECTS_VERSION;

/////////////////////////////////////////////////////////////////////////////
// Initialisierungsobjekt für GDOObjects

class CInitGDOObjects 
	: public binary_initialize < WTRiASObjects>
{
	WDispatch m_App;
	WDispatch m_Parent;
	WUnknown m_pDGMConnection;
	WUnknown m_pGDatabase;
	WUnknown m_pCoordsystemsMgr;
	VARIANT_BOOL m_bWritable;
	CComBSTR m_strOKS;
	CComBSTR m_strTablename;
	CComBSTR m_strClassname;
	CComBSTR m_strDescription;
	OBJECTTYPE m_ot;
public:
	CInitGDOObjects(
			IDispatch *pIApp,
			IDispatch *pIParent,
			IUnknown* pDGMConnection,
			IUnknown* pGDatabase,
			IUnknown* pCoordsystemsMgr,
			VARIANT_BOOL bWritable,
			OBJECTTYPE ot,
			const CComBSTR& strOKS,
			const CComBSTR& strTablename,
			const CComBSTR& strClassname,
			const CComBSTR& strDescription
	) :
		m_App(pIApp),
		m_Parent(pIParent),
		m_pDGMConnection(pDGMConnection),
		m_pGDatabase(pGDatabase),
		m_pCoordsystemsMgr(pCoordsystemsMgr),
		m_bWritable(bWritable),
		m_ot(ot),
		m_strOKS(strOKS),
		m_strTablename(strTablename),
		m_strClassname(strClassname),
		m_strDescription(strDescription)
	{
	}
	
	HRESULT operator()(binary_inititialize_target Objs, bool fFullInit) 
	{
		COM_TRY {
			if (fFullInit) {
				WPersistStreamInit(Objs)->InitNew();
				THROW_FAILED_HRESULT(Objs -> put_Application(m_App));
				THROW_FAILED_HRESULT(Objs -> put_Parent(m_Parent));
			}
		
		MC::ArrayUnknown arr(3);
		
			arr[0] = WUnknown(m_pDGMConnection).Detach();
			arr[1] = WUnknown(m_pGDatabase).Detach();
			arr[2] = WUnknown(m_pCoordsystemsMgr).Detach();
			RETURN_FAILED_HRESULT(WGDOObjects(Objs)->InitTarget(&arr, m_bWritable, m_ot, m_strOKS, m_strTablename, m_strClassname, m_strDescription));
		} COM_CATCH;
		return S_OK;
	}
};

#endif //__CGDOOBJECTS_H_
