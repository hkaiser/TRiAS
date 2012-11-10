// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 30.09.1999 10:36:06 
//
// @doc
// @module ClassFactoryMap.h | Declaration of the <c CClassFactoryMap> class

#if !defined(_CLASSFACTORYMAP_H__3E21BB98_77D3_4022_BF9F_2D1A7A838462__INCLUDED_)
#define _CLASSFACTORYMAP_H__3E21BB98_77D3_4022_BF9F_2D1A7A838462__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/GUIDHelpers.h>
#include <Com/ClassFactoryCache.h>

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Map, die Guids den gecachten ClassFactories zuordnet
class CClassFactoryMap 
{
public:
	typedef map<GUID, __Interface<IClassFactory> > CClassFactories;

	template<class __InterfaceType> 
	static inline HRESULT CreateInstance(REFGUID rGuid, __InterfaceType &rpout, IUnknown *punkOuter = NULL)
	{
		return CreateInstance (rGuid, rpout.GetIID(), rpout.ppv(), punkOuter);
	}

	static inline HRESULT CreateInstance(REFGUID rGuid, REFIID riid, LPVOID *ppv, IUnknown *punkOuter = NULL)
	{
	CClassFactories::iterator it = m_Factories.find (rGuid);

		if (it == m_Factories.end()) {
		// noch nicht instantiiert: ClsFactMap nach der entsprechenden Factory absuchen
			for (_COM_CLASSFACTOR_ENTRY *pT = GetClassFactories(); NULL != pT -> pclsid; ++pT) {
				if (InlineIsEqualGUID (rGuid, *(pT -> pclsid))) {
				// eine derartige ClassFactory ist uns bekannt, fürs nächste mal speichern
				__Interface<IClassFactory> Fact ((*pT -> pfnGetClassFactory)());

					m_Factories.insert (CClassFactories::value_type(rGuid, Fact));

				// jetzt das gewünschte Objekt erzeugen
					RETURN_FAILED_HRESULT(Fact -> CreateInstance (punkOuter, riid, ppv));
					return S_OK;
				}
			}

		// für diesen Guid existiert keine gecachte ClassFactory
		WUnknown Unk;

			RETURN_FAILED_HRESULT(Unk.CreateInstance (rGuid));
			RETURN_FAILED_HRESULT(Unk -> QueryInterface (riid, ppv));
			return S_OK;
		}
		RETURN_FAILED_HRESULT((*it).second -> CreateInstance (punkOuter, riid, ppv));
		return S_OK;
	}
	static void ClassFactoryCacheTerm ()
	{
		m_Factories.clear();
	}

private:
	static CClassFactories m_Factories;
};

#endif // !defined(_CLASSFACTORYMAP_H__3E21BB98_77D3_4022_BF9F_2D1A7A838462__INCLUDED_)
