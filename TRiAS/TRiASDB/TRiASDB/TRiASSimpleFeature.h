///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASSimpleFeature.h | Declaration of the <c CTRiASSimpleFeature> class

#if !defined(_TRIASSIMPLEFEATURE_H__7A1CA233_EAFB_11D1_861F_00600875138A__INCLUDED_)
#define _TRIASSIMPLEFEATURE_H__7A1CA233_EAFB_11D1_861F_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObjectsOperations);	// WTRiASObjectsOperations

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleFeature

class ATL_NO_VTABLE CTRiASSimpleFeature : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASSimpleFeature, &CLSID_TRiASSimpleFeature>,
	public ITRiASFeatureCallback,
	public ISupportErrorInfo,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASSimpleFeature>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASSimpleFeature, &IID_ITRiASSimpleFeature, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASSimpleFeature()
		: m_lMCode(0L), m_hPr(NULL), m_lInitData(0L)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleFeature)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASSimpleFeature);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEFEATURE)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASSimpleFeature)
		COM_INTERFACE_ENTRY(ITRiASSimpleFeature)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASSimpleFeature)
		COM_INTERFACE_ENTRY(ITRiASFeatureCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeature, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln

		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeature, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASFeature BaseFeat;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseFeat.ppi()));
		return BaseFeat -> putref_FeatureCallback(this);
	}
	void FinalRelease (void);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeatureCallback
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupFeature)(/*[in]*/ SETUPFEATUREMODE rgWhat);
	STDMETHOD(Update)(/*[in]*/ ITRiASObject *Obj, /*[in]*/ VARIANT Val);
	STDMETHOD(Eval)(/*[in]*/ ITRiASObject *Obj, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(EvalEx)(/*[in]*/ ITRiASObject *Obj, /*[in, out]*/ SAFEARRAY **ppConstraints, /*[out, retval]*/ VARIANT *Val);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(Clone)(/*[out, retval]*/ ITRiASFeature **ppIFeat);
	STDMETHOD(OnFinalRelease)();

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR Command, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR Command, /*[in]*/ ITRiASObjects *pIObjs, /*[in, optional]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

// ITRiASSimpleFeature
public:
	STDMETHOD(get_LocalHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(InitTarget)(VARIANT lMCode, FEATURETYPE dwType);

protected:
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
	{ 
		if (NULL == m_hPr) {
			RETURN_FAILED_HRESULT(::RetrieveDBHandle (m_BaseUnk, &m_hPr)); 
		}
		*phPr = m_hPr;
		return S_OK;
	}
	HRESULT RetrievePbdHandle (HPROJECT *phPrPbd);

	HRESULT OnChangedName(BSTR bstrOldName);
	HRESULT OnChangedDescription();
	HRESULT OnChangedHandle();
	HRESULT OnChangedROMode();
	HRESULT OnChangedType();

// Enumeration aller Objekte entsprechend Suchkriterium
	struct CFindObjectCallback
	{
		HPROJECT m_hPr;
		WTRiASObjectHandleMap m_ObjMap;
		WTRiASObjectHandleMap m_ObjsMap;
		WTRiASObjects m_Objs;
	};
	static HRESULT CALLBACK FindObjectCallBack (INT_PTR lObject, UINT_PTR dwData);

private:
	long m_lMCode;					// MerkmalsCode
	HPROJECT m_hPr;					// zugehörige Datenquelle

	long m_lInitData;				// Semaphore
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeature)
};

#endif // !defined(_TRIASSIMPLEFEATURE_H__7A1CA233_EAFB_11D1_861F_00600875138A__INCLUDED_)
