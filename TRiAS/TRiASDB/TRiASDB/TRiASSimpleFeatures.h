///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASSimpleFeatures.h | Declaration of the <c CTRiASSimpleFeatures> class

#if !defined(_TRIASSIMPLEFEATURES_H__1B52E2A7_EA84_11D1_861E_00600875138A__INCLUDED_)
#define _TRIASSIMPLEFEATURES_H__1B52E2A7_EA84_11D1_861E_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "TRiASFeatures.h"	// WEnumWTRiASFeature

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleFeatures
class ATL_NO_VTABLE CTRiASSimpleFeatures : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASSimpleFeatures, &CLSID_TRiASSimpleFeatures, &IID_ITRiASSimpleFeatures>,
	public ITRiASFeaturesCallback,
	public ISupportErrorInfo,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASSimpleFeatures>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSimpleFeatures, &IID_ITRiASSimpleFeatures, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASSimpleFeatures()
		: m_lInitData(0)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleFeatures)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASSimpleFeatures);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEFEATURES)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASSimpleFeatures)
		COM_INTERFACE_ENTRY(ITRiASSimpleFeatures)
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

// Länge einer Objekteigenschaft
	enum FEATURELEN {
		FEATURELEN_DEFAULT = 256,
		FEATURELEN_GUID = 40,
	};
	
// ITRiASSimpleFeatures
	STDMETHOD(get_Feature)(/*[in]*/ INT_PTR lLocalHandle, /*[out, retval]*/ ITRiASFeature **ppIFeat);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeaturesCallback
public:
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupFeatures)(/*[in]*/ IDispatch *pIParent, /*[in,optional,defaultvalue]*/ SETUPFEATURESMODE rgSetupMode);
	STDMETHOD(OnCreate)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ BSTR Type, /*[in]*/ FEATURETYPE rgType, /*[out, retval]*/ ITRiASFeature **ppIFeat);
	STDMETHOD(OnDelete)(/*[in]*/ VARIANT vWhich);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDFEATURES rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDFEATURES rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(OnFinalRelease)();

protected:
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
		{ return ::RetrieveDBHandle (m_BaseUnk, phPr); }
	HRESULT RetrievePbdHandle (HPROJECT *phPrPbd);
	HRESULT GetOrCreateObject (VARIANT vNameOrHandle, DWORD dwType, const CLSID *pCldId = &CLSID_TRiASSimpleFeature, long lLength = FEATURELEN_DEFAULT, ITRiASFeature **ppIFeat = NULL);

	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedHandle();

	struct CEnumFeatureCallback {
		CTRiASSimpleFeatures *m_pThis;
	};
	static HRESULT CALLBACK EnumFeatureCallBack (INT_PTR lMCode, DWORD dwType, UINT_PTR dwData);

private:
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeatures)
	LONG m_lInitData;				// Semaphore für Initialiserung
};

/////////////////////////////////////////////////////////////////////////////
// InitialisierungsObjekt für ein SimpleFeature-Objekt

DefineSmartInterface(TRiASSimpleFeature);		// WTRiASSimpleFeature

class CInitializeFeature :
	public binary_initialize<WTRiASFeature>
{
private:
	long m_lMCode;
	DWORD m_dwType;
	WDispatch m_App;
	WDispatch m_Parent;

public:
	CInitializeFeature (long lMCode, DWORD dwType, IDispatch *pIApp = NULL, IDispatch *pIParent = NULL)
		: m_App(pIApp), m_Parent(pIParent), m_lMCode(lMCode), m_dwType(dwType)
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
			THROW_FAILED_HRESULT(WTRiASSimpleFeature(Feat) -> InitTarget (CComVariant(m_lMCode), (FEATURETYPE)m_dwType));

		} COM_CATCH;
		return S_OK;
	}
};

#endif // !defined(_TRIASSIMPLEFEATURES_H__1B52E2A7_EA84_11D1_861E_00600875138A__INCLUDED_)
