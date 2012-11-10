///////////////////////////////////////////////////////////////////////////
// @doc 
// @module AtlSingletonCF.h | 
// Template parameters: 
// ClassName - The name of the class to turn into a singleton
//
// Usage:
// Pass this class with your concrete ATL class as the template parameter to
// DECLARE_CLASSFACTORY_EX().  Here's an example:
//    
// DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CPollManager>)
//
// Actual construction of the Singleton will be deferred to the first time
// CreateInstance is called.  This is the main advantage over the stock
// singleton ATL provides (it creates a global static instance on startup).
//

#if !defined(_ATLSINGLETONCF_H__648EE2A2_C4D2_11D1_85D1_00600875138A__INCLUDED_)
#define _ATLSINGLETONCF_H__648EE2A2_C4D2_11D1_85D1_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template <class ClassName>
class CComSingletonFactory : public CComClassFactory
{
public:
	CComSingletonFactory() { ResetInstance(); }
	virtual ~CComSingletonFactory() {}

	STDMETHOD(CreateInstance)(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj)
	{
	HRESULT hRes = E_POINTER;

		if (pUnkOuter != NULL)
			return CLASS_E_NOAGGREGATION;

		if (!staticInstance) {
		// First time in, so we need to create the instance
		ClassName* tmp = new CComObject<ClassName>;

			if (NULL == tmp) 
				return E_OUTOFMEMORY;

			staticInstance = tmp;
			hRes = staticInstance->FinalConstruct();
			if (FAILED(hRes)) {
				staticInstance = 0;
				return hRes;
			}
		}

	// We've already created the singleton
		return staticInstance->_InternalQueryInterface (riid, ppvObj);
	}
	static void ResetInstance() { staticInstance = NULL; }

private:
	static ClassName* staticInstance;
};

template <class ClassName>
ClassName *CComSingletonFactory<ClassName>::staticInstance = NULL;

#endif // !defined(_ATLSINGLETONCF_H__648EE2A2_C4D2_11D1_85D1_00600875138A__INCLUDED_)
