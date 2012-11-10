// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 23.09.2001 20:16:16 
//
// @doc
// @module CatSimpleCache.h | Declaration of the <c CCatSimpleCache> class

#if !defined(_CATSIMPLECACHE_H__5445C80A_C87C_47A0_8506_0DA031228460__INCLUDED_)
#define _CATSIMPLECACHE_H__5445C80A_C87C_47A0_8506_0DA031228460__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <comcat.h>
#include "TRiAS03.h"

/////////////////////////////////////////////////////////////////////////////
// CCatSimpleCache

class ATL_NO_VTABLE CCatSimpleCache : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCatSimpleCache, &CLSID_CatSimpleCache>,
	public ICatSimpleCache,
	public ICatInformation
{
public:
// Construction
	CCatSimpleCache() {}
	~CCatSimpleCache() {}

// Initialisation
	STDMETHODIMP CCatSimpleCache::FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_StdCatMgr.CreateInstance(CLSID_StdComponentCategoriesMgr, CLSCTX_ALL, GetControllingUnknown()));
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}
	void FinalRelease()
	{
		m_StdCatMgr.Assign(NULL);
	}

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_CATSIMPLECACHE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

// Interface map
	BEGIN_COM_MAP(CCatSimpleCache)
		COM_INTERFACE_ENTRY(ICatSimpleCache)
		COM_INTERFACE_ENTRY(ICatInformation)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_StdCatMgr.p)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ICatSimpleCache
	STDMETHODIMP IsCacheInitialized (CATID catidImpl);
	STDMETHODIMP InitializeCache(CATID catidImpl, VARIANT_BOOL fForce);
	STDMETHODIMP ClearCache (CATID catidImpl);
	STDMETHODIMP ClearCacheAll ();
	STDMETHODIMP EnumClassesOfCategoryFromCache (CATID catidImpl, IEnumCLSID **ppenumClsid);

// ICatInformation
	STDMETHODIMP EnumCategories(LCID lcid, IEnumCATEGORYINFO **penumCategoryInfo)
	{
		_ASSERTE(m_StdCatMgr.IsValid());

	__Interface<ICatInformation> CatInfo;

		if (SUCCEEDED(m_StdCatMgr -> QueryInterface(CatInfo.ppi())))
			return CatInfo -> EnumCategories(lcid, penumCategoryInfo);
		return E_NOINTERFACE;
	}
	STDMETHODIMP GetCategoryDesc(REFCATID rcatid, LCID lcid, LPWSTR *pszDesc)
	{
		_ASSERTE(m_StdCatMgr.IsValid());

	__Interface<ICatInformation> CatInfo;

		if (SUCCEEDED(m_StdCatMgr -> QueryInterface(CatInfo.ppi())))
			return CatInfo -> GetCategoryDesc(rcatid, lcid, pszDesc);
		return E_NOINTERFACE;
	}
	STDMETHODIMP EnumClassesOfCategories(ULONG cImplemented, CATID rgcatidImpl[], ULONG cRequired, CATID rgcatidReq[], IEnumCLSID **ppenumClsid);
	STDMETHODIMP IsClassOfCategories(REFCLSID rclsid, ULONG cImplemented, CATID rgcatidImpl[], ULONG cRequired, CATID rgcatidReq[])
	{
		_ASSERTE(m_StdCatMgr.IsValid());

	__Interface<ICatInformation> CatInfo;

		if (SUCCEEDED(m_StdCatMgr -> QueryInterface(CatInfo.ppi())))
			return CatInfo -> IsClassOfCategories(rclsid, cImplemented, rgcatidImpl, cRequired, rgcatidReq);
		return E_NOINTERFACE;
	}
	STDMETHODIMP EnumImplCategoriesOfClass(REFCLSID rclsid, IEnumCATID **ppenumCatid)
	{
		_ASSERTE(m_StdCatMgr.IsValid());

	__Interface<ICatInformation> CatInfo;

		if (SUCCEEDED(m_StdCatMgr -> QueryInterface(CatInfo.ppi())))
			return CatInfo -> EnumImplCategoriesOfClass(rclsid, ppenumCatid);
		return E_NOINTERFACE;
	}
	STDMETHODIMP EnumReqCategoriesOfClass(REFCLSID rclsid, IEnumCATID **ppenumCatid)
	{
		_ASSERTE(m_StdCatMgr.IsValid());

	__Interface<ICatInformation> CatInfo;

		if (SUCCEEDED(m_StdCatMgr -> QueryInterface(CatInfo.ppi())))
			return CatInfo -> EnumReqCategoriesOfClass(rclsid, ppenumCatid);
		return E_NOINTERFACE;
	}

protected:
	HRESULT Aggr_EnumClassesOfCategories(ULONG cImplemented, CATID rgcatidImpl[], ULONG cRequired, CATID rgcatidReq[], IEnumCLSID **ppenumClsid);

private:
	WUnknown m_StdCatMgr;
};

#endif // !defined(_CATSIMPLECACHE_H__5445C80A_C87C_47A0_8506_0DA031228460__INCLUDED_)
