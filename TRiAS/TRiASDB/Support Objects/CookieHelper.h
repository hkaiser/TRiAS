// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/08/1998 12:35:29 PM
//
// @doc
// @module CookieHelper.h | Declaration of the <c CCookieHelper> class

#if !defined(_COOKIEHELPER_H__BED66F3B_7351_11D2_9EF1_006008447800__INCLUDED_)
#define _COOKIEHELPER_H__BED66F3B_7351_11D2_9EF1_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "CPCookieHelperEvents.h"

/////////////////////////////////////////////////////////////////////////////
// CCookieHelper

class ATL_NO_VTABLE CCookieHelper : 
#if defined(__ATL_20_USED__)
	public CComObjectRootEx<CComObjectThreadModel>,
	public IConnectionPointContainerImpl<CCookieHelper>,
	public IDispatchImpl<ICookieHelper, &IID_ICookieHelper, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>,
#else
	public CComObjectRoot,
	public CComDualImpl<ICookieHelper, &IID_ICookieHelper, &LIBID_TRiASSupport>,
#endif
	public ISupportErrorInfo,
	public CComCoClass<CCookieHelper, &CLSID_CookieHelper>,
	public CProxyICookieHelperEvents< CCookieHelper >
{
public:
	CCookieHelper()
		: m_dwCookie(100)
	{
	}
	~CCookieHelper() {}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CCookieHelper)
	DECLARE_REGISTRY_RESOURCEID(IDR_COOKIEHELPER)
	DECLARE_CLASSFACTORY_SINGLETON(CCookieHelper)

	BEGIN_COM_MAP(CCookieHelper)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ICookieHelper)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CCookieHelper)
		CONNECTION_POINT_ENTRY(IID_ICookieHelperEvents)
	END_CONNECTION_POINT_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICookieHelper
public:
	STDMETHOD(GetLastCookie)(/*[in]*/ INT_PTR CookieHolder, /*[out, retval]*/ INT_PTR *pLastCookie);
	STDMETHOD(SetInitialCookie)(/*[in]*/ INT_PTR CookieHolder, /*[in]*/ INT_PTR newVal);
	STDMETHOD(GetCookieHolder)(/*[in]*/ BSTR Name, /*[out, retval]*/ INT_PTR *CookieHolder);
	STDMETHOD(DeleteCookieHolder)(/*[in]*/ INT_PTR CookieHolder);
	STDMETHOD(GetNextCookie)(/*[in]*/ INT_PTR CookieHolder, /*[out, retval]*/ INT_PTR *NewCookie);
	STDMETHOD(CreateCookieHolder)(/*[in]*/ BSTR Name, /*[in, optional, defaultvalue(1)]*/ INT_PTR FirstCookie, /*[out, retval]*/ INT_PTR *CookieHolder);

protected:
// Datenstruktur für einen Cookie
	class CCookieData
	{
	public:
		CCookieData(INT_PTR FirstCookie, BSTR bstrName) 
			: m_Cookie(FirstCookie), m_bstrName(bstrName), m_ulRefCnt(1) {}
		~CCookieData() {}

		ULONG AddRef() { return ++m_ulRefCnt; }
		ULONG Release() { return --m_ulRefCnt; }

		INT_PTR GetNextCookie() { return m_Cookie++; }
		const CComBSTR &GetName() const { return m_bstrName; }
		INT_PTR SetInitialCookie (INT_PTR Cookie) { INT_PTR ActCookie = m_Cookie; m_Cookie = Cookie; return ActCookie; }
		INT_PTR GetLastCookie() const { return m_Cookie; }

	private:
		INT_PTR m_Cookie;
		CComBSTR m_bstrName;
		ULONG m_ulRefCnt;
	};
	typedef map<INT_PTR, CCookieData, less<INT_PTR> > CCookieHolders;

// locks verwalten
	class CLockCS {
	private:
		CComObjectRootEx<CComObjectThreadModel> &m_rSync;

	public:
			CLockCS (CComObjectRootEx<CComObjectThreadModel> &rSync) : m_rSync(rSync) { rSync.Lock(); }
			~CLockCS () { m_rSync.Unlock(); }
	};

// Liefert einen bekannten CookieHolder (evtl. mit AddRef)
	HRESULT GetCookieHolder (BSTR Name, INT_PTR *pCookieHolder, bool fAddRef);

private:
	CCookieHolders m_Holders;
	DWORD m_dwCookie;
};

#endif // !defined(_COOKIEHELPER_H__BED66F3B_7351_11D2_9EF1_006008447800__INCLUDED_)
