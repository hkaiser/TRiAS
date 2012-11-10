// $Header: /TRiAS/TRiASDB/TRiASDB/TRiASSimpleGeoFeature.h 1     15.06.98 21:30 Hartmut Kaiser $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 06/03/1998 10:52:51 PM
//
// @doc
// @module TRiASSimpleGeoFeature.h | Declaration of the <c CTRiASSimpleGeoFeature> class

#if !defined(_TRIASSIMPLEGEOFEATURE_H__701CD5C7_FB01_11D1_863E_00600875138A__INCLUDED_)
#define _TRIASSIMPLEGEOFEATURE_H__701CD5C7_FB01_11D1_863E_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/OleObjectNotImpl.h>

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObjectsOperations);	// WTRiASObjectsOperations

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleGeoFeature

class ATL_NO_VTABLE CTRiASSimpleGeoFeature : 
	public CComCoClass<CTRiASSimpleGeoFeature, &CLSID_TRiASSimpleGeoFeature>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASFeatureCallback,
	public ISupportErrorInfo,
	public IOleObjectNotImpl,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASSimpleGeoFeature>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASSimpleFeature, &IID_ITRiASSimpleFeature, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASSimpleGeoFeature()
		: m_hPr(NULL), m_lInitData(0L), m_fIsInitialized(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleGeoFeature)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASSimpleGeoFeature)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEGEOFEATURE)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASSimpleGeoFeature)
		COM_INTERFACE_ENTRY(ITRiASSimpleFeature)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASSimpleFeature)
		COM_INTERFACE_ENTRY(ITRiASFeatureCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IOleObject)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeature, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertyBase, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertySupport, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo2, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStreamInit, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStream, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersist, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ISpecifyPropertyPages, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln

		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeature, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASFeature BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObj.ppi()));
		return BaseObj -> putref_FeatureCallback(this);
	}
	void FinalRelease (void);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeatureCallback
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(Update)(/*[in]*/ ITRiASObject *Obj, /*[in]*/ VARIANT Val);
	STDMETHOD(Eval)(/*[in]*/ ITRiASObject *Obj, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(EvalEx)(/*[in]*/ ITRiASObject *Obj, /*[in, out]*/ SAFEARRAY **ppConstraints, /*[out, retval]*/ VARIANT *Val);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(Clone)(/*[out, retval]*/ ITRiASFeature **ppIFeat);
	STDMETHOD(OnFinalRelease)();
	STDMETHOD(SetupFeature)(SETUPFEATUREMODE rgWhat);

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR Command, /*[in, optional]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR Command, /*[in]*/ ITRiASObjects *pIObjs, /*[in, optional]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

// IOleObject
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// ITRiASSimpleFeature
public:
	STDMETHOD(get_LocalHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(InitTarget)(/*[in]*/ VARIANT Name, /*[in]*/ FEATURETYPE rgType);

protected:
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
	{ 
		if (NULL == m_hPr) {
			RETURN_FAILED_HRESULT(::RetrieveDBHandle (m_BaseUnk, &m_hPr)); 
		}
		*phPr = m_hPr;
		return S_OK;
	}

	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedHandle();
	HRESULT OnChangedROMode();
	HRESULT OnChangedType();

// MonikerSupport
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);

// Enumeration aller Objekte mit gegebenem Ident/GeometrieTyp 
	struct CFindObjectCallback
	{
		WTRiASObjectHandleMap m_Map;
		WTRiASObjects m_Objs;
	};
	static HRESULT CALLBACK FindObjectCallBack (INT_PTR lObject, UINT_PTR dwData);

private:
	HPROJECT m_hPr;					// zugehörige Datenquelle
	long m_lInitData;				// Semaphore
	bool m_fIsInitialized;
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeature)
};

#endif // !defined(_TRIASSIMPLEGEOFEATURE_H__701CD5C7_FB01_11D1_863E_00600875138A__INCLUDED_)
