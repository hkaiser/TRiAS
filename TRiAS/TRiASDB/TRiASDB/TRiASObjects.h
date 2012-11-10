///////////////////////////////////////////////////////////////////////////
// TRiASObjects.h : Declaration of the CTRiASObjects

#if !defined(_TRIASOBJECTS_H__7C8CB9BC_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASOBJECTS_H__7C8CB9BC_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

#include <Atl/Ciid.h>
#include <Atl/CieThis.h>

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C6-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASObject = 
	{0x422fb8c6,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

///////////////////////////////////////////////////////////////////////////////
// Geeigneter Enumerator für TRiASObject's, der gleichzeitig den schnellen
// Zugriff über die Namen ermöglicht

//DefineSortingEnumerator2(WTRiASObject, IID_IEnumTRiASObject);		// SEnumWTRiASObject
//DefineSmartEnumerator2(WTRiASObject, IID_IEnumTRiASObject);		// WEnumWTRiASObject

// Enumerator soll FindItem und RemoveItem über CComBSTR haben (s. iterenum.h)
typedef IEnumEx<INT_PTR, WTRiASObject> IEnumTRiASObject;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen.

// Helperklasse zur Verpackung des CLSID's als Klasse
DefineEnumIIDWrapper2(WTRiASObject, IID_IEnumTRiASObject);		// CIID_WTRiASObjectEnum

// der eigentliche Enumerator
typedef map<INT_PTR, WTRiASObject, less<INT_PTR> > CEnumObjectMap;	// unterliegende Map
typedef __Enumerator<WTRiASObject, CIID_WTRiASObjectEnum, CEnumObjectMap, 
			__EnumeratorBaseTarget<WTRiASObject, CEnumObjectMap, IEnumTRiASObject> > 
		TEnumWTRiASObject;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
typedef __Interface<IEnumTRiASObject, CIID_WTRiASObjectEnum, CComPtr<IEnumTRiASObject> > WEnumWTRiASObject;

DefineSmartInterface(TRiASObjectsOperations);					// WTRiASObjectsOperations

///////////////////////////////////////////////////////////////////////////////
// hier geht's los

#include <Com/OleObjectNotImpl.h>

#include "CPTRiASPropertyEvents.h"		// connection points
#include "CPTRiASFeatureEvents.h"
#include "CPTRiASObjectsEvents.h"
#include "CPTRiASObjectEvents.h"

#include "TRiASProperties.h"
#include "TRiASObjectsOperations.h"

#include "PropertySupport.h"
#include "PropertyBase.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjects
const LONG INVALID_OBJECTCOUNT = -1L;

class ATL_NO_VTABLE CTRiASObjects : 
	public ISupportErrorInfo,
	public IPersistStreamInit,
	public IOleObjectNotImpl,
	public IOleClientSite,
	public CManagePropertySupport<CTRiASObjects>,
	public CManagePropertyBase<CTRiASObjects>,
	public CProxyITRiASPropertyEvents<CTRiASObjects>,
	public CProxyITRiASFeatureEvents<CTRiASObjects>,
	public CProxyITRiASObjectsEvents<CTRiASObjects>,
	public CProxyITRiASObjectEvents<CTRiASObjects>,
	public IConnectionPointContainerImpl<CTRiASObjects>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASFeatureEvents,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASObjects>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IProvideClassInfo2Impl<&CLSID_TRiASObjects, &IID_ITRiASObjectsEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASObjects, &IID_ITRiASObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public CReportErrorComCoClass<CTRiASObjects, &CLSID_TRiASObjects, &IID_ITRiASObjects>
{
	D_CLASS(CTRiASObjects);

public:
	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASObjects)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASObjects)

	typedef ITRiASObjects interface_t;
	typedef ITRiASObject controlled_t;
	typedef IConnectionPointContainerImpl<CTRiASObjects> CPC;

	CTRiASObjects()
		: m_pIParent(NULL), m_rgType(OBJECTTYPE_Unknown), m_rgCollType(OBJECTSCOLLECTIONTYPE_Unknown),
		  m_fIsInitialized(false), m_fIsDirty(false), m_fUpdatable(true),
		  m_hObjects(NULL), m_pICallback(NULL),
  		  m_fIsLoaded(false), m_fOksIsIdent(true),
		  m_lCount(INVALID_OBJECTCOUNT), m_lSemData(0),
		  m_dwFeatCookie(0), m_dwGeoFeatCookie(0)
	{
		m_bstrName = g_cbNil;
		m_bstrDesc = g_cbNil;
		m_bstrOKS = g_cbNil;
		m_bstrDefaultGeom = g_cbGeometry;
		m_bstrPrimaryKey = g_cbObjGuid;
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASObjects);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOBJECTS)
	DECLARE_AGGREGATABLE_EX2(CTRiASObjects)

	BEGIN_COM_MAP(CTRiASObjects)
		COM_INTERFACE_ENTRY(ITRiASObjects)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASObjects)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(ITRiASFeatureEvents)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)

		COM_INTERFACE_ENTRY_TEAR_OFF(IID_ITRiASObjectsOperations, CTRiASObjectsOperationsTearOff)
	    COM_INTERFACE_ENTRY_THIS()						// Expose implementation class
		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASObjects)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASFeatureEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASObjectEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASObjectsEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CTRiASObjects)
		PROPERTYSUPPORT_ENTRY(g_cbFeatureMap, CLSID_GenObjectMap)
		PROPERTYSUPPORT_ENTRY(g_cbNameIsDefault, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(FEATUREPROPERTY_HasObjectGuid, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct (void);
	void FinalRelease (void);

	HRESULT CreateNewEnum (IEnumTRiASObject **ppIEnum)
	{
		ATLTRY(*ppIEnum = new TEnumWTRiASObject());	// Konstruktor hinterläßt RefCnt==1
		return (NULL == *ppIEnum) ? E_OUTOFMEMORY : S_OK;
	}
	HRESULT InitEnum (IEnumTRiASObject *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}
	void SetObjectsHandle (HOBJECTS hObjects)
	{
		m_hObjects = hObjects;
	}
	IDispatch *GetDispatch() { return static_cast<ITRiASObjects *>(this); }

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

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

// ITRiASPropertyBase
//	STDMETHOD(get_Property)(BSTR Which, /*[out, retval]*/ ITRiASProperty * *pVal);
//	STDMETHOD(get_Properties)(/*[out, retval]*/ ITRiASProperties * *pVal);
//	STDMETHOD(put_Properties)(/*[in]*/ ITRiASProperties *pVal);

	HRESULT IsInitialized()
	{
		if (m_fIsInitialized) 
			return S_OK;
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	}

// ITRiASObjects
public:
	STDMETHOD(get_DefaultGeometry)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DefaultGeometry)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_PrimaryKey)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_PrimaryKey)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_GeometryFeature)(/*[in]*/ VARIANT vItem, /*[in, defaultvalue]*/ VARIANT_BOOL fCreate, /*[in, defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASFeature **pVal);
	STDMETHOD(get_GeometryFeatures)(/*[out, retval]*/ ITRiASFeatures **pVal);
	STDMETHOD(put_GeometryFeatures)(/*[in]*/ ITRiASFeatures *newVal);
	STDMETHOD(get_Feature)(/*[in]*/ VARIANT vItem, /*[in, defaultvalue]*/ VARIANT_BOOL fCreate, /*[in, defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASFeature **pVal);
	STDMETHOD(get_Features)(/*[out, retval]*/ ITRiASFeatures * *pVal);
	STDMETHOD(put_Features)(/*[in]*/ ITRiASFeatures * newVal);
	STDMETHOD(get_OKS)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_OKS)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Types)(/*[out, retval]*/ OBJECTTYPE *pVal);
	STDMETHOD(put_Types)(/*[in]*/ OBJECTTYPE newVal);
	STDMETHOD(get_Handle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(put_Handle)(/*[in]*/ INT_PTR newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Updatable)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_TableName)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Count)(/*[in]*/ long newVal);

	STDMETHOD(get_CollectionType)(/*[out, retval]*/ OBJECTSCOLLECTIONTYPE *pVal);
	STDMETHOD(put_CollectionType)(/*[in]*/ OBJECTSCOLLECTIONTYPE newVal);

	STDMETHOD(Item)(/*[in]*/ VARIANT vItem, /*[out, retval]*/ ITRiASObject **pVal);
	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **pVal);
	STDMETHOD(Add)(/*[in]*/ BSTR Name, /*[in, optional,defaultvalue]*/ BSTR Type, /*[in, optional,defaultvalue]*/ OBJECTTYPE rgType, /*[out, retval]*/ ITRiASObject **pVal);
	STDMETHOD(Delete)(/*[in]*/ VARIANT vWhich);
	STDMETHOD(Classify)(/*[in]*/ ITRiASObject *pIObj, /*[in]*/ CLASSIFYMODE rgMode);

	STDMETHOD(_Add)(/*[in]*/ ITRiASObject *newVal, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL FullAdd);
	STDMETHOD(_Reset)();
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASObjects **pVal);
	STDMETHOD(_Remove)(/*[in]*/ VARIANT vWhich);

	STDMETHOD(SetEventSink)(/*[in]*/ IUnknown *Unk, /*[in]*/ VARIANT_BOOL fAdvise);
	STDMETHOD(Refresh)();

	STDMETHOD(putref_ObjectsCallback)(ITRiASObjectsCallback *pICB);

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR bstrCommand, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR bstrCommand, /*[in]*/ ITRiASObjects *pIObjs, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

	HRESULT PropertiesRefreshed();
	HRESULT EnsureObjectsLoaded();

protected:
// operations
	HRESULT EnsureObjectsHandle(OBJECTMAPMODE rgMode = OBJECTMAPMODE_CreateObjectHandle, HOBJECTS hObjsNew = NULL);
	HRESULT EnsureObjectsCount();

	HRESULT GetMkName (BSTR *pbstrMkName);
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);

	HRESULT BindNewFeatures (WTRiASFeatures &rFeat, ITRiASFeatures *pIFeat, DWORD *pdwCookie);

	bool HasCount() { return (m_lCount != INVALID_OBJECTCOUNT) ? true : false; }
	bool IsLoaded() { return (m_fIsLoaded || OBJECTSCOLLECTIONTYPE_Temporary == m_rgCollType) ? true : false; }

	HRESULT GetSearchFeature (SAFEARRAY *pParams, ITRiASFeature **ppIFeat);
	static HRESULT GetMatchObject (BSTR bstrCommand, BSTR bstrPattern, DMatchString **ppIMatch);

	HRESULT RemoveDeleteHelper (VARIANT vWhich, bool fForceDelete);
	HRESULT OnDelete(HOBJECT hObj);
	HRESULT OnRemove(ITRiASObject *pIObj);

private:
// data members
	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;

	CComBSTR m_bstrName;		// Name dieser Objektmenge
	CComBSTR m_bstrDesc;		// BeschreibungsInfo dieser Objektmenge
	CComBSTR m_bstrOKS;			// Objektklassenschlüssel dieser Objektmenge
	CComBSTR m_bstrDefaultGeom;	// Name der PrimärGeometrie-Eigenschaft
	CComBSTR m_bstrPrimaryKey;	// Name des eindeutigen Objektkennzeichens

	OBJECTTYPE m_rgType;		// Objekttyp(en)
	OBJECTSCOLLECTIONTYPE m_rgCollType;		// Typ dieser Objektsammlung
	HOBJECTS m_hObjects;		// ZugriffsHandle

	bool m_fIsDirty;
	bool m_fIsInitialized;
	bool m_fIsLoaded;
	bool m_fOksIsIdent;			// kein OKS gegeben, Ident wird verwendet
	bool m_fUpdatable;

	WEnumWTRiASObject m_Enum;
	WTRiASFeatures m_Features;				// alle Objekte dieser Objektmenge haben diese Features
	WTRiASFeatures m_GeometryFeatures;		// alle Objekte dieser Objektmenge haben diese Geometrien

	ITRiASObjectsCallback *m_pICallback;
	long m_lCount;	
	LONG m_lSemData;

	DWORD m_dwFeatCookie;		// Cookie für Events von Feats
	DWORD m_dwGeoFeatCookie;
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long OBJECTS_SIGNATURE = 0x534A424FL;		// "OBJS"
const long OBJECTS_VERSION_MINOR_MASK = 0xff;
const long OBJECTS_VERSION_100 = 0x0100L;
const long OBJECTS_VERSION_101 = 0x0101L;		// es fehlten m_bstrDefaultGeom & m_bstrPrimaryKey
const long OBJECTS_VERSION_102 = 0x0102L;		// ParentMoniker wird nicht mehr geschrieben/benötigt (#HK000123)
const long LASTKNOWN_OBJECTS_VERSION = OBJECTS_VERSION_102;

#endif // !defined(_TRIASOBJECTS_H__7C8CB9BC_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
