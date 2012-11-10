// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.11.2000 17:22:32 
//
// @doc
// @module ClassFactorySingletonLic.h | Declaration of the <c CClassFactorySingletonLic> class

#if !defined(_CLASSFACTORYSINGLETONLIC_H__D11065A7_C52B_4219_82C4_2F70BD43E013__INCLUDED_)
#define _CLASSFACTORYSINGLETONLIC_H__D11065A7_C52B_4219_82C4_2F70BD43E013__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Classfactory für lizensierte Singletons
template <class T, class lic>
class CComClassFactorySingleton2 : 
	public CComClassFactory2<lic>
{
public:
	void FinalRelease()
	{
		CoDisconnectObject(m_Obj.GetUnknown(), 0);
	}

	// IClassFactory
	STDMETHOD(CreateInstance)(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj)
	{
		HRESULT hRes = E_POINTER;
		if (ppvObj != NULL)
		{
			*ppvObj = NULL;
			// aggregation is not supported in Singletons
			ATLASSERT(pUnkOuter == NULL);
			if (pUnkOuter != NULL)
				hRes = CLASS_E_NOAGGREGATION;
			else
			{
				if (!IsLicenseValid())
					return CLASS_E_NOTLICENSED;

				if (m_Obj.m_hResFinalConstruct != S_OK)
					hRes = m_Obj.m_hResFinalConstruct;
				else
					hRes = m_Obj.QueryInterface(riid, ppvObj);
			}
		}
		return hRes;
	}
	// IClassFactory2
	STDMETHOD(CreateInstanceLic)(IUnknown* pUnkOuter, IUnknown* pUnkReserved,
				REFIID riid, BSTR bstrKey, void** ppvObject)
	{
		if (ppvObject == NULL)
			return E_POINTER;
		*ppvObject = NULL;
		if ( ((bstrKey != NULL) && !VerifyLicenseKey(bstrKey)) ||
			 ((bstrKey == NULL) && !IsLicenseValid()) )
			return CLASS_E_NOTLICENSED;
		if ((pUnkOuter != NULL) && !InlineIsEqualUnknown(riid))
			return CLASS_E_NOAGGREGATION;
		else {
			if (m_Obj.m_hResFinalConstruct != S_OK)
				return m_Obj.m_hResFinalConstruct;
			else
				return m_Obj.QueryInterface(riid, ppvObject);
		}
	}
	CComObjectGlobal<T> m_Obj;
};

#define DECLARE_CLASSFACTORY_SINGLETON2(obj,lic) \
	typedef CComClassFactorySingleton2<obj, lic> _ClassFactorySingletonLic; \
	DECLARE_CLASSFACTORY_EX(_ClassFactorySingletonLic)

#endif // !defined(_CLASSFACTORYSINGLETONLIC_H__D11065A7_C52B_4219_82C4_2F70BD43E013__INCLUDED_)
