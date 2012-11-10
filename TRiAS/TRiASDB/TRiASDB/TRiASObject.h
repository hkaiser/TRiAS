///////////////////////////////////////////////////////////////////////////
// TRiASObject.h : Declaration of the CTRiASObject

#if !defined(_TRIASOBJECT_H__7C8CB9BB_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASOBJECT_H__7C8CB9BB_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/OleObjectNotImpl.h>

#include "resource.h"					// main symbols

#include "CPTRiASPropertyEvents.h"		// connection points
#include "CPTRiASFeatureEvents.h"

#include "TRiASProperties.h"
#include "PropertySupport.h"
#include "PropertyBase.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASObject

class ATL_NO_VTABLE CTRiASObject : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASObject, &CLSID_TRiASObject, &IID_ITRiASObject>, 
	public ISupportErrorInfo,
	public IOleObjectNotImpl,
	public IOleClientSite,
	public IPersistStreamInit,
	public CManagePropertySupport<CTRiASObject>,
	public CManagePropertyBase<CTRiASObject>,
	public CProxyITRiASPropertyEvents<CTRiASObject>,
	public CProxyITRiASFeatureEvents<CTRiASObject>,
	public IConnectionPointContainerImpl<CTRiASObject>,
	public ITRiASFeatureEvents,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASObject>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IProvideClassInfo2Impl<&CLSID_TRiASObject, &IID_ITRiASFeatureEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASObject, &IID_ITRiASObject, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef IConnectionPointContainerImpl<CTRiASObject> CPC;

	CTRiASObject()
		: m_rgType(OBJECTTYPE_Unknown), m_hObject(NULL), m_hObjects(NULL),
		  m_fIsDirty(false), m_fIsInitialized(false), m_pICallback(NULL),
		  m_bstrName(g_cbNil), m_dwFeatCookie(0), m_dwGeoFeatCookie(0)
	{
	}

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASObject)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASObject);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOBJECT)
	DECLARE_AGGREGATABLE_EX2(CTRiASObject)

	BEGIN_COM_MAP(CTRiASObject)
		COM_INTERFACE_ENTRY(ITRiASObject)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASObject)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(ITRiASFeatureEvents)
		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASObject)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASFeatureEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CTRiASObject)
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;		// jetzt erst, wenn benötigt: CreatePropertiesCollection();
	}
	void FinalRelease (void);
	IDispatch *GetDispatch() { return static_cast<ITRiASObject *>(this); }

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

	HRESULT IsInitialized()
	{
		if (m_fIsInitialized) 
			return S_OK;
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	}

// IOleObject
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// IOleClientSite
	STDMETHOD(SaveObject)();
	STDMETHOD(GetContainer)(IOleContainer **ppContainer);
	STDMETHOD(ShowObject)();
	STDMETHOD(OnShowWindow)(BOOL fShow);
	STDMETHOD(RequestNewObjectLayout)();

// ITRiASFeatureEvents
	STDMETHOD(CreatingFeature)(VARIANT NameOrHandle, VARIANT_BOOL *pVal);
	STDMETHOD(FeatureToCreate)(VARIANT NameOrHandle);
	STDMETHOD(FeatureCreated)(IDispatch *pIFeature);
	STDMETHOD(ModifyingFeature)(IDispatch *pIFeature, VARIANT_BOOL *pVal);
	STDMETHOD(FeatureToModify)(IDispatch *pIFeature);
	STDMETHOD(FeatureModified)(BSTR Name);
	STDMETHOD(DeletingFeature)(IDispatch *pIFeature, VARIANT_BOOL *pVal);
	STDMETHOD(FeatureToDelete)(IDispatch *pIFeature);
	STDMETHOD(FeatureDeleted)(BSTR Name);

// ITRiASObject
public:
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	STDMETHOD(get_Type)(/*[out, retval]*/ OBJECTTYPE *pVal);
	STDMETHOD(put_Type)(/*[in]*/ OBJECTTYPE newVal);
	STDMETHOD(get_Handle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(put_Handle)(/*[in]*/ INT_PTR newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

	STDMETHOD(get_ObjectsHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(put_ObjectsHandle)(/*[in]*/ INT_PTR newVal);
	STDMETHOD(get_DatabaseHandle)(/*[out, retval]*/ INT_PTR *pVal);

	STDMETHOD(putref_ObjectCallback)(ITRiASObjectCallback *pICB);

	STDMETHOD(get_Features)(ITRiASFeatures **pVal);
	STDMETHOD(put_Features)(ITRiASFeatures *newVal);
	STDMETHOD(get_GeometryFeatures)(ITRiASFeatures **pVal);
	STDMETHOD(put_GeometryFeatures)(ITRiASFeatures *newVal);

	STDMETHOD(Delete)();

protected:
	HRESULT EnsureObjectHandle(OBJECTMAPMODE rgMode = OBJECTMAPMODE_CreateObjectHandle);
	HRESULT BindNewFeatures (WTRiASFeatures &rFeat, ITRiASFeatures *pIFeat, DWORD *pdwCookie);

	HRESULT GetMkName (BSTR *pbstrMkName);
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);

private:
// data members
	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	CComBSTR m_bstrName;

	OBJECTTYPE m_rgType;
	HOBJECT m_hObject;
	HOBJECTS m_hObjects;				// zugehörige Objektklasse

	bool m_fIsDirty;
	bool m_fIsInitialized;

	WTRiASFeatures m_Features;			// dieses Objekt hat (evtl.) diese Features
	WTRiASFeatures m_GeometryFeatures;	// dieses Objekt hat (evtl.) diese GeoFeatures

	ITRiASObjectCallback *m_pICallback;

	DWORD m_dwFeatCookie;				// Cookie für zugehörige Objekteigenschaften
	DWORD m_dwGeoFeatCookie;			// Cookie für zugehörige GeoObjekteigenschaften
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long OBJECT_SIGNATURE = 0x434A424FL;		// "OBJE"
const long OBJECT_VERSION_MINOR_MASK = 0xff;
const long OBJECT_VERSION_100 = 0x0100L;
const long LASTKNOWN_OBJECT_VERSION = OBJECT_VERSION_100;

#endif // !defined(_TRIASOBJECT_H__7C8CB9BB_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
