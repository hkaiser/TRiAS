// @doc
// @module GDOFeature.h | Declaration of the <c CGDOFeature> class

#if !defined(_GDOFEATURE_H__7A1CA233_EAFB_11D1_861F_00600875138A__INCLUDED_)
#define _GDOFEATURE_H__7A1CA233_EAFB_11D1_861F_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// evtl. ClassFactorycache benutzen
#if defined(_USE_CLASSFACTORY_CACHE)
typedef CClassFactoryCache<&CLSID_TRiASFeature> CFeatureFactory;
extern CFeatureFactory MakeFeature;
#endif // defined(_USE_CLASSFACTORY_CACHE)

/////////////////////////////////////////////////////////////////////////////
// CGDOFeature

class ATL_NO_VTABLE CGDOFeature
	: public CComObjectRootEx<CComObjectThreadModel>,
	  public CComCoClass<CGDOFeature, &CLSID_GDOFeature>,
	  public CErrSupport<CGDOFeature, &IID_IGDOFeature>,
	  public IDispatchImpl<IGDOFeature, &IID_IGDOFeature, TLB_TRiASGDO_SIGNAT>,
	  public ITRiASFeatureCallback,
	  public IDispatchImpl<GField, &IID_GField, &LIBID_PClient>
{
private:
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeature)
	WDGMConnection m_pDGMConnection;
	WGDatabase m_pGDatabase;
	VARIANT_BOOL m_bWritable;
	long m_lInitData;				// Semaphore
	CComBSTR m_strMCode;

#define BASE_OF_GDOFEATURE	WTRiASFeature(m_BaseUnk)

	CComBSTR m_strFieldname;
	CComVariant m_vDefault;
	bool m_bIsGeoFeature;
	CComVariant m_vValue;

	HRESULT	IsInitialized() { return (m_pGDatabase.IsValid() /*&& !! m_pMetadataService*/) ? S_OK : S_FALSE; }
	HRESULT GetGField (WGField& rGField) 
	{
	WGTableDef pGTableDef;
	WGFields pGFields;

		ERROR_FAILED_HRESULT(FindSpecificParent (GetUnknown(), pGTableDef.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(pGTableDef -> get_GFields (pGFields.ppi()), NDB_E_NATIVEDB);
		ERROR_FAILED_HRESULT(pGFields -> get_Item (CComVariant(m_strFieldname), rGField.ppi()), NDB_E_NATIVEDB);
		return S_OK;
	}
	HRESULT	EvalDefaultValue (CComVariant& vDefaultValue);

protected:
	HRESULT	OnChangingName( const VARIANT& vNewName, VARIANT_BOOL *pbDisallow );
	HRESULT OnChangedName( const VARIANT& vOldName );
	HRESULT OnChangingDescription( const VARIANT& vNewDescr, VARIANT_BOOL *pbDisallow );
	HRESULT OnChangedDescription( const VARIANT& vOldValue );
	HRESULT	OnChangingHandle( const VARIANT& vNewHanlde, VARIANT_BOOL *pbDisallow );
	HRESULT OnChangedHandle( const VARIANT& vOldValue );

public:
//	static HRESULT CreateInstance( IGDOFeature** ppFeature );
	CGDOFeature()
		: m_BaseUnk(NULL),
		  m_lInitData(0),
		  m_bWritable(VARIANT_FALSE),
		  m_bIsGeoFeature(false),
		  m_strMCode(_T("0"))
	{
	}

	HRESULT FinalConstruct() 
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		RETURN_FAILED_HRESULT(MakeFeature.CreateInstance (m_BaseUnk.ppi(), GetControllingUnknown()));
#else
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeature, CLSCTX_ALL, GetControllingUnknown()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	WTRiASFeature BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObj.ppi()));
		return BaseObj -> putref_FeatureCallback(this);
	}
	void FinalRelease (void)
	{
		m_BaseUnk.Assign(NULL);
	}

	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDOFeature)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDOFeature)

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_GDOFEATURE)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_AGGREGATE_EX_SUPPORT();
	BEGIN_COM_MAP(CGDOFeature)
		COM_INTERFACE_ENTRY(IGDOFeature)
		COM_INTERFACE_ENTRY(ITRiASHandle)
		COM_INTERFACE_ENTRY2(IDispatch, IGDOFeature)
		COM_INTERFACE_ENTRY(GField)
		COM_INTERFACE_ENTRY(ITRiASFeatureCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeature, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertyBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertySupport, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo2, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStreamInit,m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStream, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersist, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IOleObject, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

public:
// IGDOFeature
	DECLARE_DEBUG_FUNCENTRY_6(CGDOFeature,InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ DWORD, dwTypeOfFeature
		, /*[in]*/ BSTR, strMCode
		, /*[in]*/ BSTR, strFieldname
		, /*[in]*/ BSTR, strFeaturename
		);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,get_DefaultValue,/*[out, retval]*/ VARIANT*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,SetupFeature,/*[in]*/ SETUPFEATUREMODE, rgMode);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,get_Fieldname,/*[out, retval]*/ BSTR*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,put_Fieldname,/*[in]*/ BSTR, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,get_FieldValue,/*[out, retval]*/ VARIANT*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,put_FieldValue,/*[in]*/ VARIANT, pVal);
	STDMETHOD(get_MCode)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MCode)(/*[in]*/ BSTR newVal);

// ITRiASFeatureCallback
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,get_DefaultType,/*[out, retval]*/BSTR*, pbstrType);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOFeature,OnChanging,/*[in]*/ CHANGEDFEATURE, rgWhat, VARIANT, vNewValue, VARIANT_BOOL*, pbDisallow );
	DECLARE_DEBUG_FUNCENTRY_2(CGDOFeature,OnChanged,/*[in]*/ CHANGEDFEATURE, rgWhat, VARIANT, vOldValue );
	DECLARE_DEBUG_FUNCENTRY_2(CGDOFeature,Update,/*[in]*/ITRiASObject*, Obj,/*[in]*/VARIANT, Val);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOFeature,Eval,/*[in]*/ITRiASObject*, Obj,/*[out, retval]*/VARIANT*, pVal);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOFeature,EvalEx,/*[in]*/ITRiASObject*, Obj, /*[in, out]*/SAFEARRAY**, ppConstraints,/*[out, retval]*/VARIANT*, Val);
    DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,Clone, ITRiASFeature**, NewFeat );
    DECLARE_DEBUG_FUNCENTRY_0(CGDOFeature,OnFinalRelease);

// GField
	STDMETHOD(get_Value)(VARIANT * pValue) {
		CHECKINPOINTER(pValue);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_Value( pValue );
	}
	STDMETHOD(put_Value)(VARIANT /*pValue*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_AllowZeroLength)(VARIANT_BOOL * pAllow) {
		CHECKINPOINTER(pAllow);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_AllowZeroLength(pAllow);
	}
	STDMETHOD(put_AllowZeroLength)(VARIANT_BOOL /*pAllow*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_Attributes)(LONG * pAttr) {
		CHECKINPOINTER(pAttr);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_Attributes(pAttr);
	}
	STDMETHOD(put_Attributes)(LONG /*pAttr*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_CollatingOrder)(LONG * pOrder) {
		CHECKINPOINTER(pOrder);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_CollatingOrder(pOrder);
	}
	STDMETHOD(get_CoordSystemGUID)(VARIANT * CSGuid) {
		CHECKINPOINTER(CSGuid);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_CoordSystemGUID(CSGuid);
	}
	STDMETHOD(put_CoordSystemGUID)(VARIANT /*CSGuid*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_DataUpdatable)(VARIANT_BOOL * pUpdatable) {
		CHECKINPOINTER(pUpdatable);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_DataUpdatable(pUpdatable);
	}
	STDMETHOD(put_DefaultValue)(BSTR /*pValue*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_DefaultValue)(BSTR * pValue) {
		CHECKINPOINTER(pValue);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_DefaultValue(pValue);
	}
	STDMETHOD(get_Name)(BSTR * pName) {
		CHECKINPOINTER(pName);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_Name(pName);
	}
	STDMETHOD(put_Name)(BSTR /*pName*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_Required)(VARIANT_BOOL * pRequired) {
		CHECKINPOINTER(pRequired);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_Required(pRequired);
	}
	STDMETHOD(put_Required)(VARIANT_BOOL /*pRequired*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_Size)(LONG * pSize) {
		CHECKINPOINTER(pSize);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_Size(pSize);
	}
	STDMETHOD(put_Size)(LONG /*pSize*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_SourceDatabase)(BSTR * pDatabase) {
		CHECKINPOINTER(pDatabase);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_SourceDatabase(pDatabase);
	}
	STDMETHOD(get_SourceField)(BSTR * pField) {
		CHECKINPOINTER(pField);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_SourceField(pField);
	}
	STDMETHOD(get_SourceTable)(BSTR * pTable) {
		CHECKINPOINTER(pTable);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_SourceTable(pTable);
	}
	STDMETHOD(get_SubType)(LONG * pGeometryType) {
		CHECKINPOINTER(pGeometryType);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_SubType(pGeometryType);
	}
	STDMETHOD(put_SubType)(LONG /*pGeometryType*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(get_Type)(SHORT * pType) {
		CHECKINPOINTER(pType);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->get_Type(pType);
	}
	STDMETHOD(put_Type)(SHORT /*pType*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(AppendChunk)(VARIANT /*Val*/) {
		return E_NOTIMPL;
	}
	STDMETHOD(FieldSize)(LONG * pSize) {
		CHECKINPOINTER(pSize);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->FieldSize(pSize);
	}
	STDMETHOD(GetChunk)(LONG /*Offset*/, LONG /*Bytes*/, VARIANT * pChunk) {
		CHECKINPOINTER(pChunk);
		return E_NOTIMPL;
	}
	STDMETHOD(GetExtension)(BSTR Name, IDispatch * * ppIDispatch) {
		CHECKOUTPOINTER(ppIDispatch);
		WGField	pGField;
		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
		return pGField->GetExtension(Name, ppIDispatch);
	}

// ITRiASHandle
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,GetHandle,LONG*, pVal) {
		CHECKINPOINTER(pVal);
		ERROR_FAILED_HRESULT( WTRiASFeature(m_BaseUnk)->get_Handle((INT_PTR *)pVal), E_FAIL );
		return S_OK;
	}
	DECLARE_DEBUG_FUNCENTRY_1(CGDOFeature,PutHandle,LONG, pVal) {
		ERROR_FAILED_HRESULT( WTRiASFeature(m_BaseUnk)->put_Handle(pVal), E_FAIL );
		return S_OK;
	}
};

class CInitGDOFeature :
	public binary_initialize<WTRiASFeature>
{
private:
	WDispatch m_App;
	WDispatch m_Parent;
	WUnknown m_pDGMConnection;
	WUnknown m_pGDatabase;
	VARIANT_BOOL m_bWritable;
	DWORD m_dwTypeOfFeature;
	CComBSTR m_strMCode;
	CComBSTR m_strFieldname;
	CComBSTR m_strFeaturename;

public:
	CInitGDOFeature (IDispatch *pIApp, IDispatch *pIParent, IUnknown* pDGMConnection,
			IUnknown* pGDatabase, VARIANT_BOOL bWritable, DWORD dwTypeOfFeature,
			const CComBSTR& strMCode, const CComBSTR& strFieldname, const CComBSTR& strFeaturename)
		: m_App(pIApp),
		  m_Parent(pIParent),
		  m_pDGMConnection(pDGMConnection),
		  m_pGDatabase(pGDatabase),
		  m_bWritable(bWritable),
		  m_dwTypeOfFeature(dwTypeOfFeature),
		  m_strMCode(strMCode),
		  m_strFieldname(strFieldname),
		  m_strFeaturename(strFeaturename)
	{
	}

	HRESULT operator() (WTRiASFeature Feat, bool fFullInit) {
//		_ASSERTE( m_App.IsValid() && m_Parent.IsValid() );
		COM_TRY {
			if (fFullInit) {
				THROW_FAILED_HRESULT(WPersistStreamInit(Feat) -> InitNew());
				THROW_FAILED_HRESULT(Feat -> put_Application (m_App));
				THROW_FAILED_HRESULT(Feat -> put_Parent (m_Parent));
			}
		
		MC::ArrayUnknown	arr(2);
		
			arr[0] = WUnknown(m_pDGMConnection).Detach();
			arr[1] = WUnknown(m_pGDatabase).Detach();
			THROW_FAILED_HRESULT(WGDOFeature(Feat) -> InitTarget (&arr, m_bWritable, m_dwTypeOfFeature, m_strMCode, m_strFieldname, m_strFeaturename));
		} COM_CATCH;
		return S_OK;
	}
};

#endif // !defined(_GDOFEATURE_H__7A1CA233_EAFB_11D1_861F_00600875138A__INCLUDED_)
