///////////////////////////////////////////////////////////////////////////
// TRiASDBEngine.h : Declaration of the CTRiASDBEngine
//
// 21.02.2001 17:36:01
//		 Added ITRiASDBEngineEvents

#if !defined(_TRIASDBENGINE_H__7C8CB9B6_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASDBENGINE_H__7C8CB9B6_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"				// main symbols
#include "CPTRiASProjectEvents.h"	// connection point
#include "CPTRiASDBEngineEvents.h"

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'

#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#import "tlb/TDBGeo.tlb" raw_interfaces_only	raw_dispinterfaces no_namespace named_guids \
	exclude("_DGMPoint", "_DGMPoints")

#import "tlb/Helper.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids	\
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASCSStorageService);	// WTRiASCSStorageService
DefineSmartInterface(CookieHelper);				// WCookieHelper

/////////////////////////////////////////////////////////////////////////////
// CTRiASDBEngine

typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;

class ATL_NO_VTABLE CTRiASDBEngine : 
	public ISupportErrorInfo,
	public IOleClientSite,
	public IConnectionPointContainerImpl<CTRiASDBEngine>,
	public CReportErrorComCoClass<CTRiASDBEngine, &CLSID_TRiASDBEngine, &IID_ITRiASDBEngine>,
	public CProxyITRiASProjectEvents<CTRiASDBEngine>,
	public CProxyITRiASDBEngineEvents<CTRiASDBEngine>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public IProvideClassInfo2Impl<&CLSID_TRiASDBEngine, &IID_ITRiASProjectEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASDBEngine, &IID_ITRiASDBEngine, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASMainDBEngine, &IID_ITRiASMainDBEngine, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASDBEngine()
		: m_fIsStarted(false),
		  m_bstrUserName(g_cbNil), m_bstrPassword(g_cbNil), m_bstrPrjName(g_cbNil),
		  m_iCurrAskToContinueCount(0)
	{
	}
	
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASDBEngine)
//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASDBENGINE)
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

	DECLARE_CLASSFACTORY_SINGLETON(CTRiASDBEngine)	// DBEngines existieren nur einmal

	BEGIN_COM_MAP(CTRiASDBEngine)
		COM_INTERFACE_ENTRY(ITRiASMainDBEngine)
		COM_INTERFACE_ENTRY(ITRiASDBEngine)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASDBEngine)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IOleClientSite)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASDBEngine)
		CONNECTION_POINT_ENTRY(IID_ITRiASProjectEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASDBEngineEvents)
	END_CONNECTION_POINT_MAP()

	HRESULT FinalConstruct();
	void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOleClientSite
	STDMETHOD(SaveObject)();
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
	STDMETHOD(GetContainer)(IOleContainer **ppContainer);
	STDMETHOD(ShowObject)();
	STDMETHOD(OnShowWindow)(BOOL fShow);
	STDMETHOD(RequestNewObjectLayout)();

// ITRiASDBEngine
public:
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_Password)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(Start)(/* [in] */ STARTMODE rgMode);
	STDMETHOD(EnumDataBaseTypes)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Stop)();

// ITRiASMainDBEngine
	STDMETHOD(get_ProjectToOpen)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Projects)(/*[out, retval]*/ ITRiASProjects **pVal);
	STDMETHOD(get_ActiveProject)(/*[out, retval]*/ ITRiASProject **pVal);
	STDMETHOD(OpenProject)(/*[in]*/ BSTR Name, /*[in, defaultvalue]*/ OPENMODE rgMode, /*[out, retval]*/ ITRiASProject **Project);
	STDMETHOD(CreateProject)(/*[in, defaultvalue]*/ BSTR Name, /*[in, defaultvalue]*/ OPENMODE rgMode, /*[out, retval]*/ ITRiASProject **ppIProject);
	STDMETHOD(OpenProjectStg)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ BSTR Name, /*[in, defaultvalue]*/ OPENMODE rgMode, /*[out, retval]*/ ITRiASProject **Project);
	STDMETHOD(CreateProjectStg)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ BSTR Name, /*[in, defaultvalue]*/ OPENMODE rgMode, /*[out, retval]*/ ITRiASProject **ppIProject);

private:
	bool m_fIsStarted;
	CComBSTR m_bstrUserName;
	CComBSTR m_bstrPassword;
	CComBSTR m_bstrPrjName;

	WTRiASProjects m_Projects;			// alle geöffnete Projekte
	WTRiASObjectHandleMap m_ObjMap;		// Map für Object-Handles
	WTRiASObjectHandleMap m_ObjsMap;	// Map für Objects-Handles
	WTRiASObjectHandleMap m_FeatureMap;	// Map für Feature-Handles

	WTRiASCSStorageService m_Service;	// Service für Geometrieoperationen
	WCookieHelper m_CookieHolder;

public:
	BSTR GetUserName (void) const { return m_bstrUserName; }
	BSTR GetPassword (void) const { return m_bstrPassword; }

// Konvertieren Blob <--> _DGMGeometry
	HRESULT StorageToGeometry (const VARIANT &Blob, GEOMETRYTYPE *prgType, IDispatch **ppIGeometry) throw(_com_error &)
	{
		_ASSERTE(m_Service.IsValid());
		return m_Service -> StorageToGeometry (Blob, prgType, ppIGeometry);
	}
	HRESULT GeometryToStorage (GEOMETRYTYPE rgType, IDispatch *pIGeometry, VARIANT *pBlob) throw(_com_error &)
	{
		_ASSERTE(m_Service.IsValid());
		return m_Service -> GeometryToStorage (rgType, pIGeometry, pBlob);
	}

// Cookies verwalten
	HRESULT GetCookieHelper (ICookieHelper **ppICookieHelper) throw(_com_error &)
	{
		_ASSERTE(m_CookieHolder.IsValid());
		return m_CookieHolder -> QueryInterface(ppICookieHelper);
	}
	HRESULT InitCookieHolder (BSTR bstrName, INT_PTR InitCookie, INT_PTR *pCookieHolder) throw(_com_error &)
	{
		_ASSERTE(m_CookieHolder.IsValid());
		return m_CookieHolder -> CreateCookieHolder (bstrName, InitCookie, pCookieHolder);
	}
	void DeleteCookieHolder(INT_PTR CookieHolder) throw(_com_error &)
	{
		_ASSERTE(m_CookieHolder.IsValid());
		m_CookieHolder -> DeleteCookieHolder (CookieHolder);		//lint !e534
	}
	INT_PTR GetNextCookie(INT_PTR CookieHolder) throw(_com_error &)
	{
	INT_PTR lCookie = 0L;

		_ASSERTE(m_CookieHolder.IsValid());
		m_CookieHolder -> GetNextCookie (CookieHolder, &lCookie);	//lint !e534
		return lCookie;
	}
	INT_PTR SetInitialCookie(INT_PTR CookieHolder, INT_PTR lCookie) throw(_com_error &)
	{
		_ASSERTE(m_CookieHolder.IsValid());
		return m_CookieHolder -> SetInitialCookie (CookieHolder, lCookie);
	}
	INT_PTR GetLastCookie(INT_PTR CookieHolder) throw(_com_error &)
	{
	INT_PTR lCookie = 0L;

		_ASSERTE(m_CookieHolder.IsValid());
		m_CookieHolder -> GetLastCookie (CookieHolder, &lCookie);	//lint !e534
		return lCookie;
	}

// das Gleiche, aber mit dem Namen
	void DeleteCookieHolder(BSTR bstrName) throw(_com_error &)
	{
		_ASSERTE(m_CookieHolder.IsValid());

	INT_PTR lCookieHolder = 0L;

		VERIFY(SUCCEEDED(m_CookieHolder -> GetCookieHolder (bstrName, &lCookieHolder)));
		m_CookieHolder -> DeleteCookieHolder (lCookieHolder);		//lint !e534
	}
	INT_PTR GetCookieHolder (BSTR bstrName) throw(_com_error &)
	{
	INT_PTR lCookieHolder = 0L;

		_ASSERTE(m_CookieHolder.IsValid());
		VERIFY(SUCCEEDED(m_CookieHolder -> GetCookieHolder (bstrName, &lCookieHolder)));
		return lCookieHolder;
	}
	INT_PTR GetNextCookie(BSTR bstrName) throw(_com_error &)
	{
	INT_PTR lCookie = 0L;
	INT_PTR lCookieHolder = 0L;

		_ASSERTE(m_CookieHolder.IsValid());
		VERIFY(SUCCEEDED(m_CookieHolder -> GetCookieHolder (bstrName, &lCookieHolder)));
		m_CookieHolder -> GetNextCookie (lCookieHolder, &lCookie);	//lint !e534
		return lCookie;
	}
	INT_PTR SetInitialCookie(BSTR bstrName, INT_PTR lCookie) throw(_com_error &)
	{
	INT_PTR lCookieHolder = 0L;

		_ASSERTE(m_CookieHolder.IsValid());
		VERIFY(SUCCEEDED(m_CookieHolder -> GetCookieHolder (bstrName, &lCookieHolder)));
		return m_CookieHolder -> SetInitialCookie (lCookieHolder, lCookie);
	}
	INT_PTR GetLastCookie(BSTR bstrName) throw(_com_error &)
	{
	INT_PTR lCookie = 0L;
	INT_PTR lCookieHolder = 0L;

		_ASSERTE(m_CookieHolder.IsValid());
		VERIFY(SUCCEEDED(m_CookieHolder -> GetCookieHolder (bstrName, &lCookieHolder)));
		m_CookieHolder -> GetLastCookie (lCookieHolder, &lCookie);	//lint !e534
		return lCookie;
	}

// Handles über Maps auflösen
	HRESULT GetObjObject (HOBJECT hObj, IUnknown **ppIObj) throw(_com_error &)
	{
		_ASSERTE(m_ObjMap.IsValid());
		return m_ObjMap -> GetObject (hObj, ppIObj);
	}
	ITRiASObjectHandleMap *GetObjectMap() { return m_ObjMap; }

	HRESULT GetObjsObject (HOBJECTS hObjs, IUnknown **ppIObjs) throw(_com_error &)
	{
		_ASSERTE(m_ObjsMap.IsValid());
		return m_ObjsMap -> GetObject (hObjs, ppIObjs);
	}
	ITRiASObjectHandleMap *GetObjectsMap() { return m_ObjsMap; }

	HRESULT GetFeaturesObject (HFEATURE hFeat, IUnknown **ppIFeat) throw(_com_error &)
	{
		_ASSERTE(m_FeatureMap.IsValid());
		return m_FeatureMap -> GetObject (hFeat, ppIFeat);
	}
	ITRiASObjectHandleMap *GetFeaturesMap() { return m_FeatureMap; }

// support for AskToContinue
	CONTINUEMODE AskToContinue (int iCallPriority = 1);

private:
	int m_iCurrAskToContinueCount;
};

/////////////////////////////////////////////////////////////////////////////
// globale Instanz der DBEngine
extern CTRiASDBEngine *g_pDBEngine;
extern STARTMODE g_rgStartMode;

///////////////////////////////////////////////////////////////////////////////
// Konstanten
const MAX_ASKTOCONTINUE_COUNT = 1000;

#endif // !defined(_TRIASDBENGINE_H__7C8CB9B6_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
