///////////////////////////////////////////////////////////////////////////
// TRiASFeatures.h : Declaration of the CTRiASFeatures

#if !defined(_TRIASFEATURES_H__7C8CB9BA_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASFEATURES_H__7C8CB9BA_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/PropertyMacros.h>
#include <Atl/CieThis.h>

#include "resource.h"       // main symbols
#include "TRiASFeature.h"

///////////////////////////////////////////////////////////////////////////////
// Geeigneter Enumerator für Features, der gleichzeitig den schnellen
// Zugriff über die Namen ermöglicht

// {422FB8C8-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASFeature = 
	{0x422fb8c8,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineSmartInterface(TRiASFeature);

// Enumerator soll FindItem und RemoveItem über CComBSTR haben (s. iterenum.h)
typedef IEnumEx<CComBSTR, WTRiASFeature> IEnumFeature;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen (hier über den
// Bezeichner des ViewItems, s.a. 'bool operator< (const CComBSTR &, const CComBSTR &)' ).

// Helperklasse zur Verpackung des CLSID's als Klasse
DefineEnumIIDWrapper2(WTRiASFeature, IID_IEnumTRiASFeature);		// CIID_WTRiASFeatureEnum

// der eigentliche Enumerator
typedef map<CComBSTR, WTRiASFeature, less<CComBSTR> > CEnumFeatureMap;	// unterliegende Map
typedef __Enumerator<WTRiASFeature, CIID_WTRiASFeatureEnum, CEnumFeatureMap, 
			__EnumeratorBaseTarget<WTRiASFeature, CEnumFeatureMap, IEnumFeature> > 
		TEnumWTRiASFeature;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
typedef __Interface<IEnumFeature, CIID_WTRiASFeatureEnum, CComPtr<IEnumFeature> > WEnumWTRiASFeature;

/////////////////////////////////////////////////////////////////////////////
// CTRiASFeatures
class ATL_NO_VTABLE CTRiASFeatures : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASFeatures, &CLSID_TRiASFeatures, &IID_ITRiASFeatures>, 
	public ISupportErrorInfo,
	public ITRiASFeatureEvents,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASFeatures>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IProvideClassInfo2Impl<&CLSID_TRiASFeatures, &IID_ITRiASFeatureEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASFeatures, &IID_ITRiASFeatures, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASFeatures interface_t;
	typedef ITRiASFeature controlled_t;

	CTRiASFeatures()
		: m_dwCookie(0L), m_pIParent(NULL), m_lSemDel(0L), 
		  m_FeaturesType(FEATURESTYPE_Unknown),
		  m_pICallback(NULL), m_pIRelDisp(NULL)
	{
	}

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASFeatures)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASFeatures);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASFEATURES)
	DECLARE_AGGREGATABLE_EX2(CTRiASFeatures)

	BEGIN_COM_MAP(CTRiASFeatures)
		COM_INTERFACE_ENTRY(ITRiASFeatures)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASFeatures)
		COM_INTERFACE_ENTRY(ITRiASFeatureEvents)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY_THIS()
		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct();
	void FinalRelease (void);

	HRESULT CreateNewEnum (IEnumFeature **ppIEnum)
	{
		ATLTRY((*ppIEnum) = new TEnumWTRiASFeature());	// Konstruktor hinterläßt RefCnt==1
		if (NULL == *ppIEnum)
			return E_OUTOFMEMORY;

		return S_OK;
	}
	HRESULT InitEnum (IEnumFeature *pTarget)
	{ 
		RETURN_FAILED_HRESULT(pTarget -> Clone (m_Enum.ppi())); 
		return S_OK;
	}


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeatureEvents
	STDMETHOD(CreatingFeature)(VARIANT NameOrHandle, VARIANT_BOOL *pVal);
	STDMETHOD(FeatureToCreate)(VARIANT NameOrHandle);
	STDMETHOD(FeatureCreated)(IDispatch *pIViewItem);
	STDMETHOD(ModifyingFeature)(IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	STDMETHOD(FeatureToModify)(IDispatch *pIViewItem);
	STDMETHOD(FeatureModified)(BSTR Name);
	STDMETHOD(DeletingFeature)(IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	STDMETHOD(FeatureToDelete)(IDispatch *pIViewItem);
	STDMETHOD(FeatureDeleted)(BSTR Name);

// ITRiASFeatures
public:
	STDMETHOD(Refresh)();
	STDMETHOD(RefreshEx)(SETUPFEATURESMODE Mode);
	STDMETHOD(SetEventSink)(/*[in]*/ IUnknown *pIUnk, /*[in, out]*/ DWORD *pdwCookie, /*[in]*/ VARIANT_BOOL fAdvise);
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASFeatures **ppIFeatures);
	STDMETHOD(_Add)(/*[in]*/ ITRiASFeature *pIFeature, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL FullAdd);

	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ ITRiASFeature **ppIFeature);
	STDMETHOD(Add)(/*[in]*/ VARIANT NameOrHandle, /*[in, optional, defaultvalue]*/ BSTR Type, /*[in, optional, defaultvalue]*/ FEATURETYPE rgType, /*[out, retval]*/ ITRiASFeature **ppIFeature);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	STDMETHOD(putref_FeaturesCallback)(ITRiASFeaturesCallback *pICB);

	STDMETHOD(get_RelatedObject)(/*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(putref_RelatedObject)(/*[in]*/ IDispatch * newVal);
	DECLARE_PROPERTY_ACCESS(FeaturesType, FEATURESTYPE)

	HRESULT RemoveFeature(ITRiASFeature *pIFeature);
	HRESULT RemoveFeature(BSTR bstrName, ITRiASFeature *pIFeature);

protected:
// Events verschicken
	HRESULT Fire_CreatingFeature (VARIANT NameOrHandle, VARIANT_BOOL *pVal);
	HRESULT Fire_FeatureToCreate (VARIANT NameOrHandle);
	HRESULT Fire_FeatureCreated (IDispatch * pIConn);
	HRESULT Fire_DeletingFeature (IDispatch *pIConn, VARIANT_BOOL * pVal);
	HRESULT Fire_FeatureToDelete (IDispatch * pIConn);
	HRESULT Fire_FeatureDeleted(BSTR Name);

private:
	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;			// no AddRef (fully contained)

	WEnumWTRiASFeature m_Enum;		// Enumerator der zugehörigen ViewItems

	LONG m_lSemDel;					// Semaphore für Eventbehandlung
	DWORD m_dwCookie;				// Connection zu Objektmenge
	FEATURESTYPE m_FeaturesType;	// Typ dieser Objekteigenschaftsmenge

	ITRiASFeaturesCallback *m_pICallback;
	IDispatch *m_pIRelDisp;
};

#endif // !defined(_TRIASFEATURES_H__7C8CB9BA_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
