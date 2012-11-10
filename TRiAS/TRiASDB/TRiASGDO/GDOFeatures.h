// @doc 
// @module GDOFeatures.h | Declaration of the <c CGDOFeatures> class

#if !defined(_GDOFEATURES_H__1B52E2A7_EA84_11D1_861E_00600875138A__INCLUDED_)
#define _GDOFEATURES_H__1B52E2A7_EA84_11D1_861E_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CGDOFeatures
class ATL_NO_VTABLE CGDOFeatures :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CGDOFeatures, &CLSID_GDOFeatures>,
	public CErrSupport<CGDOFeatures, &IID_IGDOFeatures>,
	public IDispatchImpl<IGDOFeatures, &IID_IGDOFeatures, TLB_TRiASGDO_SIGNAT>,
	public ITRiASFeaturesCallback
{
private:
	WUnknown			m_BaseUnk;				// aggregiertes Objekt (TRiASFeatures)
	LONG				m_lInitData;			// Semaphore für Initialiserung
	WDGMConnection		m_pDGMConnection;
	WGDatabase			m_pGDatabase;
	VARIANT_BOOL		m_bWritable;

#define	BASE_OF_GDOFEATURES	WTRiASFeatures(m_BaseUnk)

	HRESULT	IsInitialized() { return m_pGDatabase.IsValid() ? S_OK : S_FALSE; }

protected:
	HRESULT GetGTableDef (WGTableDef& rGTableDef) 
	{
	WDispatch pParent;
	WGDOObjects pGDOObjects;

		ERROR_FAILED_HRESULT(BASE_OF_GDOFEATURES -> get_Parent (pParent.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(pParent -> QueryInterface (pGDOObjects.ppi()), GDO_E_NOPARENT);

	CComBSTR strTablename;

		ERROR_FAILED_HRESULT(pGDOObjects -> get_Tablename (CLEARED(strTablename)), E_FAIL);

	WGTableDefs	pGTableDefs;

		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_GTableDefs( pGTableDefs.ppi() ), NDB_E_NATIVEDB );
		EXT_ERROR_FAILED_HRESULT(pGTableDefs -> get_Item( CComVariant(strTablename), rGTableDef.ppi() ), NDB_E_NATIVEDB );
		return S_OK;
	}

	HRESULT	OnChangingName( const VARIANT& vNewName, VARIANT_BOOL *pbDisallow );
	HRESULT OnChangedName( const VARIANT& vOldValue );

	HRESULT OnChangingDescription( const VARIANT& vNewDescr, VARIANT_BOOL *pbDisallow );
	HRESULT OnChangedDescription( const VARIANT& vOldValue );

	HRESULT OnChangingHandle( const VARIANT& vNewHandle, VARIANT_BOOL* pbDisallow );
	HRESULT OnChangedHandle( const VARIANT& vOldValue );
public:
//	static HRESULT CreateInstance( IGDOFeatures** ppFeature );
	CGDOFeatures()
		: m_BaseUnk(NULL),
		  m_lInitData(0),
		  m_bWritable(VARIANT_FALSE)
	{
	}

	HRESULT FinalConstruct() 
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeatures, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASFeatures BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObj.ppi()));
		return BaseObj -> putref_FeaturesCallback(this);
	}
	void FinalRelease (void) 
	{
		m_BaseUnk.Assign(NULL);
	}

	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDOFeatures)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDOFeatures)

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_GDOFEATURES)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_AGGREGATE_EX_SUPPORT();
	BEGIN_COM_MAP(CGDOFeatures)
		COM_INTERFACE_ENTRY(IGDOFeatures)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITRiASFeaturesCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatures, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo2, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatureEvents, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

public:
// IGDOFeatures
	DECLARE_DEBUG_FUNCENTRY_2(CGDOFeatures,InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		);

// ITRiASFeaturesCallback
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeatures,get_DefaultType,/*[out, retval]*/ BSTR*, pbstrType);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOFeatures,SetupFeatures,/*[in]*/ IDispatch*, pIObjs, SETUPFEATURESMODE, SetupMode );
	DECLARE_DEBUG_FUNCENTRY_4(CGDOFeatures,OnCreate,/*[in]*/ VARIANT, NameOrHandle, /*[in]*/ BSTR, Type, /*[in]*/ FEATURETYPE, rgType, /*[out, retval]*/ ITRiASFeature**, ppIFeat);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeatures,OnDelete,/*[in]*/ VARIANT, vWhich);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOFeatures,OnChanging,/*[in]*/ CHANGEDFEATURES, rgWhat, VARIANT, vNewValue, VARIANT_BOOL*, pbDisallow );
	DECLARE_DEBUG_FUNCENTRY_2(CGDOFeatures,OnChanged,/*[in]*/ CHANGEDFEATURES, rgWhat, VARIANT, vOldValue );
    DECLARE_DEBUG_FUNCENTRY_0(CGDOFeatures,OnFinalRelease);
};

#endif // !defined(_GDOFEATURES_H__1B52E2A7_EA84_11D1_861E_00600875138A__INCLUDED_)
