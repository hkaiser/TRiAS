// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.02.2000 22:52:43 
//
// @doc
// @module GDOObject.h | Declaration of the <c CGDOObject> class

#if !defined(_GDOOBJECT_H__A7969118_4188_4CC2_B366_12DC1F2BFC57__INCLUDED_)
#define _GDOOBJECT_H__A7969118_4188_4CC2_B366_12DC1F2BFC57__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// evtl. ClassFactorycache benutzen
#if defined(_USE_CLASSFACTORY_CACHE)
typedef CClassFactoryCache<&CLSID_TRiASObject> CObjectFactory;
extern CObjectFactory MakeObject;
#endif // defined(_USE_CLASSFACTORY_CACHE)

#include <Com/OleClientSiteNotImpl.h>

///////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CGDOObject : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CGDOObject, &CLSID_GDOObject>,
	public CErrSupport<CGDOObject, &IID_IGDOObject>,
	public IDispatchImpl<IGDOObject, &IID_IGDOObject, TLB_TRiASGDO_SIGNAT>,
	public ITRiASObjectCallback,
	public IOleClientSiteNotImpl
{
private:
	WUnknown m_BaseUnk;
	long m_lInitData;
//	WDGMConnection m_pDGMConnection;
//	WGDatabase m_pGDatabase;
	VARIANT_BOOL m_bWritable;

	bool m_bIsInitialized;
	bool m_bIsDirty;
	bool m_bHaveFeatures;

#if defined(_GEOMETRYCACHEDBYOBJECT)
	CComVariant	m_vGeometry;
#endif // defined(_GEOMETRYCACHEDBYOBJECT)

private:
	HRESULT	IsInitailized( ) { return m_bIsInitialized ? S_OK : S_FALSE; }
	HRESULT	OnChangingName( VARIANT& vNewName, VARIANT_BOOL* pbDisallow );
	HRESULT	OnChangedName( VARIANT& vOldName );
	HRESULT	EnsureFeatures( bool bForceSetup );

#define BASE_OF_GDOOBJECT WTRiASObject(m_BaseUnk)

protected:
	HRESULT GetMkName (BSTR *pbstrMkName);
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);

public:
	static HRESULT GetObjectMoniker( LPCOLESTR lpszName, IMoniker *pIContMk, DWORD dwWhich, IMoniker **ppIMk );
//	static HRESULT CreateInstance( IGDOObject** ppObject );
//	bool m_bRequiresSave;

	CGDOObject()
		: m_BaseUnk(NULL),
		  m_lInitData(0),
		  m_bWritable(VARIANT_FALSE),
		  m_bIsInitialized(false),
		  m_bIsDirty(false),
//		  m_bRequiresSave(false),
#if defined(_GEOMETRYCACHEDBYOBJECT)
		  m_vGeometry(VT_EMPTY),
#endif // defined(_GEOMETRYCACHEDBYOBJECT)
		  m_bHaveFeatures(false)
	{
	}

	HRESULT FinalConstruct() 
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		RETURN_FAILED_HRESULT(MakeObject.CreateInstance (m_BaseUnk.ppi(), GetControllingUnknown()));
#else
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASObject, CLSCTX_ALL, GetControllingUnknown()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	WTRiASObject BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObj.ppi()));
		return BaseObj -> putref_ObjectCallback(this);
	}
	void FinalRelease (void) 
	{
		m_BaseUnk.Assign(NULL);
	}

	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDOObject)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDOObject)

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_GDOOBJECT)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_AGGREGATE_EX_SUPPORT();
	BEGIN_COM_MAP(CGDOObject)
		COM_INTERFACE_ENTRY(IGDOObject)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY(ITRiASHandle)
		COM_INTERFACE_ENTRY(ITRiASObjectCallback)

		COM_INTERFACE_ENTRY2(IDispatch, IGDOObject)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObject, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertyBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASPropertySupport, m_BaseUnk.p)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatureEvents, m_BaseUnk.p)

	// selbst nichts zu speichern, daher alles an das Aggregat delegieren
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStream, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersistStreamInit,m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IPersist,m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IOleObject, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IProvideClassInfo2, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_CHAIN(errsupport_t)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

//	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CGDOObject)
//		OLEITEMCONTAINERSUPPORT_ENTRY(g_cbMkFeature, GetFeature)
//	END_OLEITEMCONTAINERSUPPORT_MAP()

public:
// IGDOObject
	DECLARE_DEBUG_FUNCENTRY_4(CGDOObject,InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ DWORD, dwType
		, /*[in]*/ BSTR, strObjectname
		);

#if defined(_GEOMETRYCACHEDBYOBJECT)
// IGDOObjectGeometry
	STDMETHOD(PutGeometry)(VARIANT pGeometry) {
		return m_vGeometry.Copy( &pGeometry );
	}
	STDMETHOD(GetGeometry)(VARIANT* pGeometry) {
//		if( IS_EMPTY(&m_vGeometry) ) {
//			ReloadGeometry();
//		}
		return m_vGeometry.Detach( pGeometry );
	}
#endif // defined(_GEOMETRYCACHEDBYOBJECT)

// IOleClientSite
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// ITRiASObjectCallback
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObject,get_DefaultType,/*[out,retval]*/BSTR*, strType);
    DECLARE_DEBUG_FUNCENTRY_1(CGDOObject,SetupObject, SETUPOBJECTMODE, SetupMode);
    DECLARE_DEBUG_FUNCENTRY_1(CGDOObject,SetupFeatures, SETUPFEATURESMODE, SetupMode );
    DECLARE_DEBUG_FUNCENTRY_0(CGDOObject,OnDelete);
	DECLARE_DEBUG_FUNCENTRY_3(CGDOObject,OnChanging,/*[in]*/ CHANGEDOBJECT, rgWhat, VARIANT, vNewValue, VARIANT_BOOL*, pbDisallow );
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObject,OnChanged,/*[in]*/ CHANGEDOBJECT, rgWhat, VARIANT, vOldValue );
    DECLARE_DEBUG_FUNCENTRY_0(CGDOObject,OnFinalRelease);

// ITRiASHandle
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObject,GetHandle, LONG*, pVal) {
		CHECKINPOINTER(pVal);
		ERROR_FAILED_HRESULT( WTRiASObject(m_BaseUnk)->get_Handle((INT_PTR *)pVal), E_FAIL );
		return S_OK;
	}
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObject,PutHandle, LONG, pVal) {
		ERROR_FAILED_HRESULT( WTRiASObject(m_BaseUnk)->put_Handle(pVal), E_FAIL );
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long GDOOBJECT_VERSION = 0x0100L;
const long LASTKNOWN_GDOOBJECT_VERSION = GDOOBJECT_VERSION;

//////////////////////////////////////////////////////////////////////
// Initialisierungsobjekte
class CInitGDOObject : 
	public binary_initialize<WTRiASObject> 
{
private:
	WDispatch m_App;
	WDispatch m_Parent;
	WUnknown m_pDGMConnection;
	WUnknown m_pGDatabase;
	VARIANT_BOOL m_bWritable;
	OBJECTTYPE m_ot;
	CComBSTR m_strIdent;

public:
	CInitGDOObject (IDispatch *pIApp, IDispatch *pIParent, IUnknown* pDGMConnection, IUnknown* pGDatabase, VARIANT_BOOL bWritable)
		: m_App(pIApp),
		  m_Parent(pIParent),
		  m_pDGMConnection(pDGMConnection),
		  m_pGDatabase(pGDatabase),
		  m_bWritable(bWritable),
		  m_strIdent(_T("")),
		  m_ot(OBJECTTYPE_Unknown)
	{
	}
	void SetIdent (const BSTR& strIdent) { m_strIdent = strIdent; }
	void SetType (const OBJECTTYPE& t) { m_ot = t; }

	HRESULT operator() (WTRiASObject& rObj, bool bCreate = false) 
	{
//		_ASSERTE( m_App.IsValid() && m_Parent.IsValid() );
		COM_TRY {
			if(bCreate) {
// #HK000305: removed creation 
//				CComObject<CGDOObject> *pNew = NULL;
//				CComObject<CGDOObject>::CreateInstance(&pNew);
//				THROW_FAILED_HRESULT( pNew->QueryInterface( rObj.GetIID(), rObj.ppv() ) );
				_ASSERTE(rObj.IsValid());
				THROW_FAILED_HRESULT(WPersistStreamInit(rObj) -> InitNew());
				THROW_FAILED_HRESULT(rObj -> put_Application (m_App));
				THROW_FAILED_HRESULT(rObj -> put_Parent (m_Parent));
			}
		
		MC::ArrayUnknown arr(3);
		
			arr[0] = WUnknown(m_pDGMConnection).Detach();
			arr[1] = WUnknown(m_pGDatabase).Detach();
			RETURN_FAILED_HRESULT(WGDOObject(rObj) -> InitTarget (&arr, m_bWritable, m_ot, m_strIdent));
		} COM_CATCH;
		return S_OK;
	}
};

#endif // !defined(_GDOOBJECT_H__A7969118_4188_4CC2_B366_12DC1F2BFC57__INCLUDED_)
