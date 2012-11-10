// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.09.99 18:43:53 
//
// @doc
// @module ClassFactoryCache.h | Declaration of the <c CClassFactoryCache> class

#if !defined(_CLASSFACTORYCACHE_H__648FCBD9_9A79_4925_A86B_31EC80800CCE__INCLUDED_)
#define _CLASSFACTORYCACHE_H__648FCBD9_9A79_4925_A86B_31EC80800CCE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_USE_CLASSFACTORY_CACHE)

///////////////////////////////////////////////////////////////////////////////
// cached eine ClassFactory fürs beschleunigte Erzeugen von Objekten
template<const GUID *pclsid>
class CClassFactoryCache 
{
public:
	CClassFactoryCache() {}
	~CClassFactoryCache() {}

	static void WINAPI ClassFactoryMain (bool bStarting)
	{
		if (!bStarting)	ClearCache();
	}

// neue Instanz des Targetobjekites erzeugen
	static HRESULT CreateInstance (REFIID riid, LPVOID *ppv, IUnknown *ppUnkOuter = NULL)
	{
	HRESULT hr = S_OK;

		if (FAILED(hr = InitCache()))
			return hr;
		return m_ClsFact -> CreateInstance (ppUnkOuter, riid, ppv);
	}
	template<class X>
	static HRESULT CreateInstance (X **ppi, IUnknown *ppUnkOuter = NULL)
	{
		return CreateInstance (__uuidof(X), (LPVOID *)ppi, ppUnkOuter);
	}

	operator IClassFactory * () { THROW_FAILED_HRESULT(InitCache()); return m_ClsFact; }
	IClassFactory * operator -> () { THROW_FAILED_HRESULT(InitCache()); return m_ClsFact; }
	static IClassFactory * WINAPI GetClassFactory() { THROW_FAILED_HRESULT(InitCache()); return m_ClsFact; } 

protected:
	static inline HRESULT InitCache()
	{ 
		if (!m_ClsFact.IsValid()) {
			RETURN_FAILED_HRESULT(CoGetClassObject (*pclsid, CLSCTX_INPROC_SERVER, NULL, m_ClsFact.GetIID(), m_ClsFact.ppv())); 
			m_ClsFact -> LockServer(TRUE);		// classfactory/server festhalten
		}
		return S_OK;
	}
	static void ClearCache() 
	{ 
		if (m_ClsFact.IsValid()) {
			m_ClsFact -> LockServer (FALSE);	// classfactory/server freigeben
			m_ClsFact.Assign(NULL); 
		}
	}

private:
	static __Interface<IClassFactory> m_ClsFact;
};

template<const GUID *pclsid>
__Interface<IClassFactory> CClassFactoryCache<pclsid>::m_ClsFact;

///////////////////////////////////////////////////////////////////////////////
// Map, in der alle zu behandelnden ClassFactories gegeben werden
struct _COM_CLASSFACTOR_ENTRY
{
	const CLSID* pclsid;
	void (WINAPI *pfnClassFactMain)(bool bStarting);
	IClassFactory * (WINAPI *pfnGetClassFactory)();
};

#define CLASSFACTORY_CACHE_BEGIN(x) _COM_CLASSFACTOR_ENTRY *GetClassFactories() { \
static _COM_CLASSFACTOR_ENTRY theClassFactoryMap[] = {
#define CLASSFACTORY_CACHE_ENTRY(clsid, class) { &clsid, class::ClassFactoryMain, class::GetClassFactory, },
#define CLASSFACTORY_SIMPLE_CACHE_ENTRY(clsid) { &clsid, CClassFactoryCache<&clsid>::ClassFactoryMain, CClassFactoryCache<&clsid>::GetClassFactory },
#define CLASSFACTORY_CACHE_END() {NULL, NULL, }}; return theClassFactoryMap; }

_COM_CLASSFACTOR_ENTRY *GetClassFactories();

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen fürs Initialisieren und aufräumen
inline
void ClassFactoryCacheInit (_COM_CLASSFACTOR_ENTRY *pCF)
{
	for (_COM_CLASSFACTOR_ENTRY *pT = pCF; NULL != pT -> pclsid; ++pT)
		(*pT -> pfnClassFactMain)(true);
}

inline
void ClassFactoryCacheTerm (_COM_CLASSFACTOR_ENTRY *pCF)
{
	for (_COM_CLASSFACTOR_ENTRY *pT = pCF; NULL != pT -> pclsid; ++pT)
		(*pT -> pfnClassFactMain)(false);
}

#else

///////////////////////////////////////////////////////////////////////////////
// Map, in der alle zu behandelnden ClassFactories gegeben werden
#define CLASSFACTORY_CACHE_BEGIN(x) static _COM_CLASSFACTOR_ENTRY x[] = {
#define CLASSFACTORY_CACHE_ENTRY(clsid, class) 
#define CLASSFACTORY_SIMPLE_CACHE_ENTRY(clsid) 
#define CLASSFACTORY_CACHE_END() {NULL}};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen fürs Initialisieren und aufräumen 
struct _COM_CLASSFACTOR_ENTRY { void *pdummy; };

inline void ClassFactoryCacheInit (_COM_CLASSFACTOR_ENTRY *pCF) {}
inline void ClassFactoryCacheTerm (_COM_CLASSFACTOR_ENTRY *pCF) {}

#endif // defined(_USE_CLASSFACTORY_CACHE)

#endif // !defined(_CLASSFACTORYCACHE_H__648FCBD9_9A79_4925_A86B_31EC80800CCE__INCLUDED_)
