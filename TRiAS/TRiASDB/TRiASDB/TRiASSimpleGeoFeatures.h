// $Header: /TRiAS/TRiASDB/TRiASDB/TRiASSimpleGeoFeatures.h 1     15.06.98 21:31 Hartmut Kaiser $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 06/03/1998 10:57:25 PM
//
// @doc
// @module TRiASSimpleGeoFeatures.h | Declaration of the <c CTRiASSimpleGeoFeatures> class

#if !defined(_TRIASSIMPLEGEOFEATURES_H__701CD5C8_FB01_11D1_863E_00600875138A__INCLUDED_)
#define _TRIASSIMPLEGEOFEATURES_H__701CD5C8_FB01_11D1_863E_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "TRiASFeatures.h"	// WEnumWTRiASFeature

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleGeoFeatures
class ATL_NO_VTABLE CTRiASSimpleGeoFeatures : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASSimpleGeoFeatures, &CLSID_TRiASSimpleGeoFeatures, &IID_ITRiASSimpleGeoFeatures>,
	public ITRiASFeaturesCallback,
	public ISupportErrorInfo,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASSimpleGeoFeatures>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSimpleGeoFeatures, &IID_ITRiASSimpleGeoFeatures, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASSimpleGeoFeatures()
		: m_lInitData(0)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleGeoFeatures)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASSimpleGeoFeatures);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEGEOFEATURES)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASSimpleGeoFeatures)
		COM_INTERFACE_ENTRY(ITRiASSimpleGeoFeatures)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITRiASFeaturesCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatures, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo2, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo, m_BaseUnk.p)
//		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatureEvents, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln

		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeatures, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASFeatures BaseObjs;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObjs.ppi()));
		return BaseObjs -> putref_FeaturesCallback(this);
	}
	void FinalRelease (void)
	{
		m_BaseUnk.Assign(NULL);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeaturesCallback
public:
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupFeatures)(/*[in]*/ IDispatch *pIObjs, /*[in,optional,defaultvalue]*/ SETUPFEATURESMODE rgMode);
	STDMETHOD(OnCreate)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ BSTR Type, /*[in]*/ FEATURETYPE rgType, /*[out, retval]*/ ITRiASFeature **ppIFeat);
	STDMETHOD(OnDelete)(/*[in]*/ VARIANT vWhich);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDFEATURES rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDFEATURES rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(OnFinalRelease)();

protected:
	HRESULT GetOrCreateObject (BSTR bstrName, FEATURETYPE rgType);

	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedHandle();

private:
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeatures)
	LONG m_lInitData;				// Semaphore für Initialiserung
};

/////////////////////////////////////////////////////////////////////////////
// InitialisierungsObjekt für ein SimpleFeature-Objekt

DefineSmartInterface(TRiASSimpleFeature);		// WTRiASSimpleFeature

class CInitializeGeoFeature :
	public binary_initialize<WTRiASFeature>
{
private:
	CComBSTR m_bstrName;
	FEATURETYPE m_rgType;
	WDispatch m_App;
	WDispatch m_Parent;

public:
	CInitializeGeoFeature (BSTR bstrName, FEATURETYPE rgType, IDispatch *pIApp = NULL, IDispatch *pIParent = NULL)
		: m_App(pIApp), m_Parent(pIParent), m_rgType(rgType), m_bstrName(bstrName)
	{}

	HRESULT operator() (binary_inititialize_target Feat, bool fFullInit)
	{
		COM_TRY {
			if (fFullInit) {
//				_ASSERTE(m_App.IsValid() && m_Parent.IsValid());	// bei fullinit müssen App&Parent gegeben sein

				THROW_FAILED_HRESULT(WPersistStreamInit(Feat) -> InitNew());
				THROW_FAILED_HRESULT(Feat -> put_Application (m_App));
				THROW_FAILED_HRESULT(Feat -> put_Parent (m_Parent));
			}
			THROW_FAILED_HRESULT(WTRiASSimpleFeature(Feat) -> InitTarget (CComVariant(m_bstrName), m_rgType));

		} COM_CATCH;
		return S_OK;
	}
};

#endif // !defined(_TRIASSIMPLEGEOFEATURES_H__701CD5C8_FB01_11D1_863E_00600875138A__INCLUDED_)
