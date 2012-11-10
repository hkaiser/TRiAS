///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASObjectHandleMap.cpp | Declaration of the 
// <c CTRiASObjectHandleMapBase>, <c CTRiASObjectHandleMap>, 
// <c CTRiASObjectsHandleMap>, <c CTRiASFeatureHandleMap> and
// <c CTRiASGenericHandleMap> classes

#if !defined(_TRIASOBJECTHANDLEMAP_H__D4C24AD7_A5EA_11D1_BA31_080036D63803__INCLUDED_)
#define _TRIASOBJECTHANDLEMAP_H__D4C24AD7_A5EA_11D1_BA31_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"			// main symbols
#include "TRiASDBEngine.h"

class CObjectHandleEntry
{
public:
	typedef CComObjectThreadModel::AutoCriticalSection _CritSec;

private:
	IUnknown *m_pIUnk;
	LONG m_lCookie;
	CComBSTR m_bstrName;
	OBJECTMAPMODE m_rgMode;

public:
	DECLARE_ONE_SIZE_PRIVATE_HEAP()

	CObjectHandleEntry() :
		m_bstrName(g_cbNil)
	{
		m_pIUnk = NULL;
		m_lCookie = NULL;
	}
	CObjectHandleEntry (IUnknown *pIUnk, LONG lCookie, BSTR bstrName, OBJECTMAPMODE rgMode)
		: m_pIUnk(NULL), m_lCookie(lCookie), m_bstrName(bstrName), m_rgMode(rgMode)
	{
		m_pIUnk = pIUnk;
		if (NULL != m_pIUnk && HasType (m_rgMode, OBJECTMAPMODE_RegistrationKeepsAlive))
			m_pIUnk -> AddRef();
	}
	CObjectHandleEntry (const CObjectHandleEntry &rhs)
	{
		m_pIUnk = const_cast<CObjectHandleEntry &>(rhs).GetObject (HasType (m_rgMode, OBJECTMAPMODE_RegistrationKeepsAlive));
		m_bstrName = rhs.GetName();
		m_lCookie = rhs.GetCookie();
		m_rgMode = rhs.GetMode();
	}
	~CObjectHandleEntry()
	{
		if (NULL != m_pIUnk && HasType (m_rgMode, OBJECTMAPMODE_RegistrationKeepsAlive)) {
			m_pIUnk -> Release();
			m_pIUnk = NULL;
		}		
	}

	CObjectHandleEntry & operator= (const CObjectHandleEntry &rhs)
	{
		if (&rhs != this) {
			m_pIUnk = const_cast<CObjectHandleEntry &>(rhs).GetObject (HasType (m_rgMode, OBJECTMAPMODE_RegistrationKeepsAlive));
			m_bstrName = rhs.GetName();
			m_lCookie = rhs.GetCookie();
			m_rgMode = rhs.GetMode();
		}
		return *this;
	}

	OBJECTMAPMODE GetMode() const { return m_rgMode; }
	BSTR GetName() const { return m_bstrName; }
	LONG GetCookie() const { return m_lCookie; }
	IUnknown *GetObject (bool fAddRef = false) 
	{ 
		if (fAddRef && NULL != m_pIUnk) 
			m_pIUnk -> AddRef(); 
		return m_pIUnk; 
	}
};

///////////////////////////////////////////////////////////////////////////////
// Deklaration CObjectHandleSet und CObjectNameSet

typedef map<LONG, CObjectHandleEntry *, less<LONG> > CObjectHandleMap;

#if !defined(_USE_HASHMAP_FOR_OBJECTNAMEMAP)
typedef map<CComBSTR, CObjectHandleEntry *, less<CComBSTR> > CObjectNameMap;
#else
#include <ospace/stl/hashmap.h>
class CHashBSTR :
	public unary_function<CComBSTR, size_t>
{
public:
	size_t operator() (const CComBSTR &rToHash) const
	{
		return LHashValOfName (LOCALE_SYSTEM_DEFAULT, rToHash);
	}
};
typedef hash_map<CComBSTR, CObjectHandleEntry *, CHashBSTR> CObjectNameMap;
#endif !defined(_USE_HASHMAP_FOR_OBJECTNAMEMAP)

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectHandleMapBase
class ATL_NO_VTABLE CTRiASObjectHandleMapBase : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IObjectWithName,
	public IDispatchImpl<ITRiASObjectHandleMap, &IID_ITRiASObjectHandleMap, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASObjectHandleMapBase()
		: m_CookieHolder(0),  m_bstrName(g_cbNil)
	{
	}

	BEGIN_COM_MAP(CTRiASObjectHandleMapBase)
		COM_INTERFACE_ENTRY(ITRiASObjectHandleMap)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IObjectWithName)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	virtual HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASObjectHandleMap) = 0;

	void FinalRelease()
	{
		DeleteCookieHolder();
		_ASSERTE(0 == m_CookieHolder);		// muß breits freigegeben sein
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASObjectHandleMap
public:
	STDMETHOD(RemoveObject)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode);
	STDMETHOD(GetObject)(/*[in]*/ INT_PTR Handle, /*[out, retval]*/ IUnknown **Object);
	STDMETHOD(GetObjectEx)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode, /*[out, retval]*/ IUnknown **Object);
	STDMETHOD(GetObjectHandle)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ IUnknown *Object, /*[in]*/ OBJECTMAPMODE rgMode, /*[out, retval]*/ INT_PTR *Handle);
	STDMETHOD(ShutDown)();

// IObjectWithName
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

protected:
	HRESULT InitCookieHolder (BSTR bstrName, INT_PTR InitCookie)
	{
		_ASSERTE(0 == m_CookieHolder);		// nur einmal rufen
		_ASSERTE(NULL != g_pDBEngine);
		m_bstrName = bstrName;
		if (NULL != g_pDBEngine) 
			return g_pDBEngine -> InitCookieHolder(bstrName, InitCookie, &m_CookieHolder);
		return E_UNEXPECTED;
	}
	void DeleteCookieHolder()
	{
		if (NULL != g_pDBEngine) {
			_ASSERTE(0 != m_CookieHolder);		// muß initialisiert sein
			g_pDBEngine -> DeleteCookieHolder(m_CookieHolder);
			m_CookieHolder = 0L;
		}
	}
	INT_PTR GetNextCookie()
	{
		_ASSERTE(NULL != g_pDBEngine);
		if (NULL != g_pDBEngine) 
			return g_pDBEngine -> GetNextCookie (m_CookieHolder);
		return E_UNEXPECTED;
	}

// Abgleich des zuletzt verwendeten Cookies
	HRESULT EnsureCorrectCookie (INT_PTR hHandleToCompare)
	{
		_ASSERTE(0 != m_CookieHolder);		// muß initialisiert sein
		_ASSERTE(NULL != g_pDBEngine);

		if (hHandleToCompare >= g_pDBEngine -> GetLastCookie (m_CookieHolder)) {
			g_pDBEngine -> SetInitialCookie(m_CookieHolder, hHandleToCompare+1);
			return S_OK;
		}
		return S_FALSE;		// nicht korrigiert
	}

private:
	CObjectHandleMap m_Objects;	// die registrierten Objekte
	CObjectNameMap m_Names;		// und deren Namen
	CComBSTR m_bstrName;		// der Bezeichner dieser Objkettabelle

	INT_PTR m_CookieHolder;		// Cookie des CookieHolders
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectHandleMap (HandleMap für <o TRiASObject>- Objekte)
class ATL_NO_VTABLE CTRiASObjectHandleMap : 
	public CComCoClass<CTRiASObjectHandleMap, &CLSID_TRiASObjectHandleMap>,
	public CTRiASObjectHandleMapBase
{
public:
	CTRiASObjectHandleMap()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASObjectHandleMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOBJECTHANDLEMAP)
	DECLARE_CLASSFACTORY_SINGLETON(CTRiASObjectHandleMap)
//	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CTRiASObjectHandleMap>)

	HRESULT FinalConstruct()
	{
	HRESULT hr = CTRiASObjectHandleMapBase::InitCookieHolder(CComBSTR(g_cbObjectMap), (INT_PTR)0x10000000L);

		return SUCCEEDED(hr) ? S_OK : hr;
	}

	typedef CComCoClass<CTRiASObjectHandleMap, &CLSID_TRiASObjectHandleMap> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASObjectHandleMap)
	{
		CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
		return base_t::Error (str, riid, hr); 
	}

#if defined(_DEBUG)
// ITRiASObjectHandleMap
public:
	STDMETHOD(RemoveObject)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode)
	{
		return CTRiASObjectHandleMapBase::RemoveObject (Handle, Mode);
	}
	STDMETHOD(GetObject)(/*[in]*/ INT_PTR Handle, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObject (Handle, Object);
	}
	STDMETHOD(GetObjectEx)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObjectEx (Handle, Mode, Object);
	}
	STDMETHOD(GetObjectHandle)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ IUnknown *Object, /*[in]*/ OBJECTMAPMODE rgMode, /*[out, retval]*/ INT_PTR *Handle)
	{
		return CTRiASObjectHandleMapBase::GetObjectHandle (NameOrHandle, Object, rgMode, Handle);
	}
#endif // defined(_DEBUG)
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsHandleMap (HandleMap für <o TRiASObjects>- Objekte)
class ATL_NO_VTABLE CTRiASObjectsHandleMap : 
	public CComCoClass<CTRiASObjectsHandleMap, &CLSID_TRiASObjectsHandleMap>,
	public CTRiASObjectHandleMapBase
{
public:
	CTRiASObjectsHandleMap()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASObjectsHandleMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOBJECTSHANDLEMAP)
	DECLARE_CLASSFACTORY_SINGLETON(CTRiASObjectsHandleMap)
//	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CTRiASObjectsHandleMap>)

	HRESULT FinalConstruct()
	{
	HRESULT hr = CTRiASObjectHandleMapBase::InitCookieHolder(CComBSTR(g_cbObjectsMap), (INT_PTR)0xE0000001L);

		return SUCCEEDED(hr) ? S_OK : hr;
	}

	typedef CComCoClass<CTRiASObjectsHandleMap, &CLSID_TRiASObjectsHandleMap> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASObjectHandleMap)
	{
		CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
		return base_t::Error (str, riid, hr); 
	}

#if defined(_DEBUG)
// ITRiASObjectHandleMap
public:
	STDMETHOD(RemoveObject)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode)
	{
		return CTRiASObjectHandleMapBase::RemoveObject (Handle, Mode);
	}
	STDMETHOD(GetObject)(/*[in]*/ INT_PTR Handle, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObject (Handle, Object);
	}
	STDMETHOD(GetObjectEx)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObjectEx (Handle, Mode, Object);
	}
	STDMETHOD(GetObjectHandle)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ IUnknown *Object, /*[in]*/ OBJECTMAPMODE rgMode, /*[out, retval]*/ INT_PTR *Handle)
	{
		return CTRiASObjectHandleMapBase::GetObjectHandle (NameOrHandle, Object, rgMode, Handle);
	}
#endif // defined(_DEBUG)
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsHandleMap (HandleMap für <o TRiASFeature>- Objekte)
class ATL_NO_VTABLE CTRiASFeatureHandleMap : 
	public CComCoClass<CTRiASFeatureHandleMap, &CLSID_TRiASFeatureHandleMap>,
	public CTRiASObjectHandleMapBase
{
public:
	CTRiASFeatureHandleMap()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASFeatureHandleMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASFEATUREHANDLEMAP)
	DECLARE_CLASSFACTORY_SINGLETON(CTRiASFeatureHandleMap)
//	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CTRiASObjectsHandleMap>)

	HRESULT FinalConstruct()
	{
	HRESULT hr = CTRiASObjectHandleMapBase::InitCookieHolder(CComBSTR(g_cbFeatureMap), (INT_PTR)2100000000L);

		return SUCCEEDED(hr) ? S_OK : hr;
	}

	typedef CComCoClass<CTRiASFeatureHandleMap, &CLSID_TRiASFeatureHandleMap> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASObjectHandleMap)
	{
		CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
		return base_t::Error (str, riid, hr); 
	}

#if defined(_DEBUG)
// ITRiASObjectHandleMap
public:
	STDMETHOD(RemoveObject)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode)
	{
		return CTRiASObjectHandleMapBase::RemoveObject (Handle, Mode);
	}
	STDMETHOD(GetObject)(/*[in]*/ INT_PTR Handle, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObject (Handle, Object);
	}
	STDMETHOD(GetObjectEx)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObjectEx (Handle, Mode, Object);
	}
	STDMETHOD(GetObjectHandle)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ IUnknown *Object, /*[in]*/ OBJECTMAPMODE rgMode, /*[out, retval]*/ INT_PTR *Handle)
	{
		return CTRiASObjectHandleMapBase::GetObjectHandle (NameOrHandle, Object, rgMode, Handle);
	}
#endif // defined(_DEBUG)
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASGenericHandleMap (HandleMap für beliebige- Objekte), _kein singleton_
class ATL_NO_VTABLE CTRiASGenericHandleMap : 
	public CComCoClass<CTRiASGenericHandleMap, &CLSID_TRiASGenericHandleMap>,
	public ITRiASPropertyCallback,
	public CTRiASObjectHandleMapBase
{
public:
	CTRiASGenericHandleMap()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASGenericHandleMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASGENERICHANDLEMAP)

	BEGIN_COM_MAP(CTRiASGenericHandleMap)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASObjectHandleMapBase)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
	HRESULT hr = CTRiASObjectHandleMapBase::InitCookieHolder(CComBSTR(g_cbGenericMap), (INT_PTR)1900000000L);

		return SUCCEEDED(hr) ? S_OK : hr;
	}

	typedef CComCoClass<CTRiASGenericHandleMap, &CLSID_TRiASGenericHandleMap> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASObjectHandleMap)
	{
		CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
		return base_t::Error (str, riid, hr); 
	}

public:
// ITRiASPropertyCallback
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

#if defined(_DEBUG)
// ITRiASObjectHandleMap
public:
	STDMETHOD(RemoveObject)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode)
	{
		return CTRiASObjectHandleMapBase::RemoveObject (Handle, Mode);
	}
	STDMETHOD(GetObject)(/*[in]*/ INT_PTR Handle, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObject (Handle, Object);
	}
	STDMETHOD(GetObjectEx)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode, /*[out, retval]*/ IUnknown **Object)
	{
		return CTRiASObjectHandleMapBase::GetObjectEx (Handle, Mode, Object);
	}
	STDMETHOD(GetObjectHandle)(/*[in]*/ VARIANT NameOrHandle, /*[in]*/ IUnknown *Object, /*[in]*/ OBJECTMAPMODE rgMode, /*[out, retval]*/ INT_PTR *Handle)
	{
		return CTRiASObjectHandleMapBase::GetObjectHandle (NameOrHandle, Object, rgMode, Handle);
	}
#endif // defined(_DEBUG)
};

#endif // !defined(_TRIASOBJECTHANDLEMAP_H__D4C24AD7_A5EA_11D1_BA31_080036D63803__INCLUDED_)
