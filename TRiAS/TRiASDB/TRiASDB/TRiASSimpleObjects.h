///////////////////////////////////////////////////////////////////////////
// TRiASSimpleObjects.h : Declaration of the CTRiASSimpleObjects

#if !defined(_TRIASSIMPLEOBJECTS_H__3F9633F4_C718_11D1_85D6_00600875138A__INCLUDED_)
#define _TRIASSIMPLEOBJECTS_H__3F9633F4_C718_11D1_85D6_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
//
#include <Com/OleItemContainerSupport.h>

#include <NativePbd.h>
#include <NativeIdent.h>
#include <NativeObject.h>
#include <NativeMerkmal.h>

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'

#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#import "tlb/TDBGeo.tlb" raw_interfaces_only	raw_dispinterfaces no_namespace named_guids \
	exclude("_DGMPoint", "_DGMPoints")

using namespace trias_nativepbd;
using namespace trias_nativeident;
using namespace trias_nativeobject;
using namespace trias_nativemerkmal;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASSimpleObjects);		// WTRiASSimpleObjects

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleObjects

typedef vector<INT_PTR> CLocalHandles;
typedef map<INT_PTR, INT_PTR, less<INT_PTR> > CObjHandleMap;

class ATL_NO_VTABLE CTRiASSimpleObjects : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASSimpleObjects, &CLSID_TRiASSimpleObjects, &IID_ITRiASSimpleObjects>,
	public IPersistStreamInit,
	public ISupportErrorInfo,
	public ITRiASObjectsCallback,
	public COleItemContainerSupport<CTRiASSimpleObjects>,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASSimpleObjects>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASSimpleObjects, &IID_ITRiASSimpleObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef CComCoClass<CTRiASSimpleObjects, &IID_ITRiASObjects> base_t;

	CTRiASSimpleObjects()
		: m_lIdent(0L), m_hPr(NULL), m_fIsInitialized(false), m_fIsDirty(false), 
		  m_fHasFeatures(false), m_fHasGeoFeatures(false),
		  m_rgInitState(INITSTATE_NotInitialized), m_pObjs(NULL), m_phMap(NULL),
		  m_lInitData(0), m_lOnUnload(0)
	{
		ResetCounters(true);
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleObjects)

//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASSimpleObjects)
	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASSimpleObjects);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEOBJECTS)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASSimpleObjects)
		COM_INTERFACE_ENTRY(ITRiASSimpleObjects)
		COM_INTERFACE_ENTRY(ITRiASObjectsEx)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASObjectsEx)
		COM_INTERFACE_ENTRY(ITRiASObjectsCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IOleItemContainer)		// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IOleContainer)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IParseDisplayName)		// --> COleItemContainerSupport

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObjects, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln

		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CTRiASSimpleObjects)
		OLEITEMCONTAINERSUPPORT_ENTRY(g_cbMkFeature, GetFeature)
	END_OLEITEMCONTAINERSUPPORT_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASObjects, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASObjects BaseObjs;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObjs.ppi()));
		return BaseObjs -> putref_ObjectsCallback(this);
	}
	void FinalRelease (void);

// Funktionen für das ErrorHandling
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASSimpleObjects)
		{ 
			CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, hr); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr, REFIID riid = IID_ITRiASSimpleObjects)
		{
			return base_t::Error (pcText, riid, hr); 
		}

// Enumeration aller Objekte mit gegebenem Ident/GeometrieTyp 
	struct CEnumObjectCallback
	{
		CTRiASSimpleObjects *m_pThis;
		class CNativeIdent *m_pIdent;
#if defined(_DEBUG)
		DWORD m_dwTypes;
#endif // _DEBUG
	};
	static HRESULT CALLBACK EnumObjectCallBack (INT_PTR lObject, DWORD dwType, UINT_PTR dwData);

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

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR Command, /*[in, optional]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR Command, /*[in]*/ ITRiASObjects *pIObjs, /*[in, optional]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

// ITRiASObjectsCallback
public:
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupFeatures)(/*[in,optional,defaultvalue]*/ SETUPFEATURESMODE rgMode);
	STDMETHOD(SetupObjects)(/*[in]*/ SETUPOBJECTSMODE rgMode);

	STDMETHOD(OnDelete)(/*[in]*/ INT_PTR hObj);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDOBJECTS rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDOBJECTS rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(OnCreate)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTTYPE rgType, /*[out, retval]*/ ITRiASObject **ppIObj);
	STDMETHOD(OnAdd)(/*[in]*/ ITRiASObject *pIObj, /*[in]*/ CLASSIFYMODE rgMode);
	STDMETHOD(OnRemove)(/*[in]*/ ITRiASObject *pIObj);
	STDMETHOD(MapFeatureHandle)(/*[in]*/ VARIANT vNameOrHandle, /*[out,retval]*/ VARIANT *pvNewNameOrHandle);
	STDMETHOD(OnFinalRelease)();

// ITRiASSimpleObjects
	STDMETHOD(InitTarget)(/*[in]*/ LONG lIdent, /*[in]*/ OBJECTTYPE rgVisType, /*[in]*/ VARIANT_BOOL fCreate, /*[in, out]*/ INT_PTR *phObjs);
	STDMETHOD(get_Count)(/*[in]*/ OBJECTTYPE rgType, /*[out, retval]*/ long *plObjCnt);
	STDMETHOD(get_LocalHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(get_Handles)(/*[in]*/ long lCount, /*[in, out, size_is(Count)]*/INT_PTR *plObjs);
	STDMETHOD(EnsureLoaded)(/*[in]*/ INT_PTR hObj, /*[in]*/ BSTR GeomName, /*[in, out]*/ SAFEARRAY **ppConstraints, /*[out, retval]*/ ITRiASObject **ppIObj);
	STDMETHOD(MayUnload)(/*[in]*/ INT_PTR hObj);

protected:
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
	{
		if (NULL == m_hPr) {
			COM_TRY {
			WDispatch Parent;

				THROW_FAILED_HRESULT(WTRiASObjects(m_BaseUnk) -> get_Parent (Parent.ppi()));
				THROW_FAILED_HRESULT(WTRiASDatabase(Parent) -> get_Handle ((INT_PTR *)&m_hPr));

			} COM_CATCH;
		}
		*phPr = m_hPr;
		return S_OK;
	}
	HRESULT RetrievePbdHandle (HPROJECT *phPrPbd);

	void ResetCounters(bool fResetAll = false)
	{
		ZeroMemory (m_lCounts, sizeof(m_lCounts));
		DELETE_OBJ(m_pObjs);
		DELETE_OBJ(m_phMap);

		if (fResetAll) 
			m_lCountAll = 0L;
		m_rgInitState = INITSTATE_NotInitialized;
	}

	HRESULT EnsureObjectsCount();
	HRESULT EnsureObjectsLocalHandles();
	HRESULT EnsureObjectsHandles();
	HRESULT EnsureObjectsLoaded();
	HRESULT EnsureFeatures(VARIANT_BOOL fForceSetup);

	HRESULT EnsureLookupWindow (LPCSTR pcGeomName, CNativeObject &rObj, 
		VARIANT vWindow, ITRiASSimpleRectangle **ppIRect);

	HRESULT GetOrCreateObject (INT_PTR &rhObj, LONG lObject, OBJECTTYPE rgType, 
		REFCLSID rClsId, ITRiASObject **ppIObj = NULL, BOOL fCountObjects = FALSE);

	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedOKS();
	HRESULT OnChangedHandle();
	HRESULT OnChangedTypes();
	HRESULT OnChangedROMode();

	void IncrementObjectCount (OBJECTTYPE rgType, BOOL fFullCnt = TRUE);
	void DecrementObjectCount (OBJECTTYPE rgType);

// OleItemContainerSupport
	HRESULT GetFeature (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, 
		LPVOID *ppvObj, bool fTestRunningOnly);

private:
	LONG m_lIdent;					// Identifikator
	HPROJECT m_hPr;

	bool m_fIsDirty;
	bool m_fIsInitialized;
	bool m_fHasFeatures;
	bool m_fHasGeoFeatures;

	enum INITSTATE {
		INITSTATE_NotInitialized = 0x00,
		INITSTATE_CountsInitialized = 0x01,
		INITSTATE_LocalHandlesInitialized = 0x02,
		INITSTATE_HandlesInitialized = 0x04,
		INITSTATE_ObjectsInitialized = 0x08,
	};
	INITSTATE m_rgInitState;

	long m_lCounts[4];
	long m_lCountAll;

	CLocalHandles *m_pObjs;			// Objektnummern
	CObjHandleMap *m_phMap;			// Handles --> ObjektNummern

	HRESULT EnsureLocalHandleCont(bool fClearMap = false);
	HRESULT EnsureHandleMap(bool fClearMap = false);

	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASObjects)
	LONG m_lInitData;				// Semaphore für Initialiserung
	LONG m_lOnUnload;				// Semaphore für Entladen
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long SIMPLEOBJECTS_SIGNATURE = 0x53424F54L;	// "TOBS"
const long SIMPLEOBJECTS_VERSION_MINOR_MASK = 0xff;
const long SIMPLEOBJECTS_VERSION_100 = 0x0100L;
const long LASTKNOWN_SIMPLEOBJECTS_VERSION = SIMPLEOBJECTS_VERSION_100;

///////////////////////////////////////////////////////////////////////////////
// InitialisierungsHelper für <o TRiASSimpleObjects> -Objekte

#include "FindInMapOrCreateObject.h"

class CInitializeSimpleObjects :
	public binary_initialize<WTRiASObjects>
{
private:
	DWORD m_dwTypes;
	WDispatch m_App;
	WDispatch m_Parent;

public:
	CInitializeSimpleObjects (IDispatch *pIApp, IDispatch *pIParent, DWORD dwTypes = OBJECTTYPE_All)
		: m_App(pIApp), m_Parent(pIParent), m_dwTypes(dwTypes)
	{}

// operator erzeugen oder initialisieren 
	HRESULT operator() (
		WTRiASObjects Objs, INT_PTR &rlIdent, INT_PTR &rhObjs, bool fFullInit)
	{
	HRESULT hr = S_OK;

		COM_TRY {
			if (fFullInit) {
				THROW_FAILED_HRESULT(WPersistStreamInit(Objs) -> InitNew());

				THROW_FAILED_HRESULT(Objs -> put_Application (m_App));
				THROW_FAILED_HRESULT(Objs -> put_Parent (m_Parent));
			}

		WTRiASSimpleObjects SimpleObjs (Objs);

			THROW_FAILED_HRESULT(hr = SimpleObjs -> InitTarget (rlIdent, (OBJECTTYPE)m_dwTypes, VARIANT_FALSE, &rhObjs));
			if (NULL == rlIdent) {
			// für neu erzeugte Objektklasse lokales Handle liefern
				THROW_FAILED_HRESULT(SimpleObjs -> get_LocalHandle (&rlIdent));
			}

		} COM_CATCH;
		return hr;
	}
};

class CCreateSimpleObjects :
	public binary_initialize<WTRiASObjects>
{
private:
	DWORD m_dwTypes;
	WDispatch m_App;
	WDispatch m_Parent;

public:
	CCreateSimpleObjects (IDispatch *pIApp, IDispatch *pIParent, DWORD dwTypes = OBJECTTYPE_All)
		: m_App(pIApp), m_Parent(pIParent), m_dwTypes(dwTypes)
	{}

// operator fürs neu erzeugen
	HRESULT operator() (
		WTRiASObjects Objs, INT_PTR lIdent, INT_PTR &rhObjs)
	{
	HRESULT hr = S_OK;

		COM_TRY {
			THROW_FAILED_HRESULT(WPersistStreamInit(Objs) -> InitNew());

			THROW_FAILED_HRESULT(Objs -> put_Application (m_App));
			THROW_FAILED_HRESULT(Objs -> put_Parent (m_Parent));

			THROW_FAILED_HRESULT(hr = WTRiASSimpleObjects(Objs) -> InitTarget (lIdent, (OBJECTTYPE)m_dwTypes, VARIANT_TRUE, &rhObjs));

		} COM_CATCH;
		return hr;
	}
};

#endif // !defined(_TRIASSIMPLEOBJECTS_H__3F9633F4_C718_11D1_85D6_00600875138A__INCLUDED_)
