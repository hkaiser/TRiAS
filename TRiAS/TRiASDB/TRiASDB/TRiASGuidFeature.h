// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 11/05/1998 12:20:43 PM
//
// @doc
// @module TRiASGuidFeature.h | Spezielle Objekteigenschaft, die eideutige 
// Objektkennung (Guid) liefert

#if !defined(_TRIASGUIDFEATURE_H__BED66F37_7351_11D2_9EF1_006008447800__INCLUDED_)
#define _TRIASGUIDFEATURE_H__BED66F37_7351_11D2_9EF1_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include <Com/OleObjectNotImpl.h>

/////////////////////////////////////////////////////////////////////////////
// CTRiASGuidFeature
class ATL_NO_VTABLE CTRiASGuidFeature : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASGuidFeature, &CLSID_TRiASGuidFeature>,
	public ITRiASFeatureCallback,
	public IOleObjectNotImpl,
	public ISupportErrorInfo,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASGuidFeature>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASSimpleFeature, &IID_ITRiASSimpleFeature, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASGuidFeature()
		: m_fIsInitialized(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASGuidFeature)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASGuidFeature);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASGUIDFEATURE)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASGuidFeature)
		COM_INTERFACE_ENTRY(ITRiASSimpleFeature)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASSimpleFeature)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)
		COM_INTERFACE_ENTRY(ITRiASFeatureCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IOleObject)

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
	void FinalRelease (void)
	{
		m_BaseUnk.Assign(NULL);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeatureCallback
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(Update)(/*[in]*/ ITRiASObject *Obj, /*[in]*/ VARIANT Val);
	STDMETHOD(Eval)(/*[in]*/ ITRiASObject *Obj, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(EvalEx)(/*[in]*/ ITRiASObject *Obj, /*[in, out]*/ SAFEARRAY **ppConstraints, /*[out, retval]*/ VARIANT *Val);
	STDMETHOD(Clone)(/*[out, retval]*/ ITRiASFeature **ppIFeat);
	STDMETHOD(OnFinalRelease)();
	STDMETHOD(SetupFeature)(SETUPFEATUREMODE rgWhat);

// IOleObject
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR Command, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR Command, /*[in]*/ ITRiASObjects *pIObjs, /*[in, optional]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

// ITRiASSimpleFeature
public:
	STDMETHOD(get_LocalHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(InitTarget)(/*[in]*/ VARIANT vName, FEATURETYPE dwType);

protected:
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
		{ return ::RetrieveDBHandle (m_BaseUnk, phPr); }

	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedHandle();
	HRESULT OnChangedROMode();

// MonikerSupport
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);

private:
	long m_lInitData;				// Semaphore
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeature)
	bool m_fIsInitialized;
};

#endif // !defined(_TRIASGUIDFEATURE_H__BED66F37_7351_11D2_9EF1_006008447800__INCLUDED_)
