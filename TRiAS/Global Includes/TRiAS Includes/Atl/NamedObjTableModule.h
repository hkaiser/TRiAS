//NamedObjTableModule.h
// Copyright (c) 1998 Valery Pryamikov.

// usage:
// include "NamedObjTableModule.h" just after inclusion of the "atlbase.h" but before definition of the _Module variable.
// Redefine your _Module variable next way:
//	- for dll server it must be defined as an instance of CNamedObjTableModule (or your custom module class that inherits from CNamedObjTableModule)
//	- for exe server you must inherit generated CExeModule class from CNamedObjTableModule instead of CComModule.
// include "NamedObjects.h" just after inclusion of the "atlcom.h"
// for more info look NamedObjects.h file.

// Implementation details: uses GIT internally for retrieving named object reference.
// named objects does not AddRef (weak reference). 
// When the client releases last reference to the named object than
// CComNamedObject automatically deletes correspondent GIT entry from GIT (NamedObjects.h)

#ifndef __NAMEDOBJTABLEMODULE_H__
#define __NAMEDOBJTABLEMODULE_H__

#include <Atl/_resource_guard.h>
#include <ospace/std/map>

class __declspec(uuid("{CF53E410-82D4-11d2-B2AE-00A0C9AA1C0C}")) ATL_NO_VTABLE INamedObjectFactory: public IUnknown
{
public:
	STDMETHOD(GetNamedObject)(LPCOLESTR name, void *pv, REFIID riid, void **ppv)=0;
};

typedef HRESULT (WINAPI _NAMEDOBJECT_CREATORFUNC)(LPCOLESTR szwName, void* pv, REFIID riid, LPVOID* ppv);

class CNamedObjTableModule: public CComModule
{
public:
	struct CGITHelper {
		static inline IGlobalInterfaceTable *GIT();
	};

private:
	class CReference: public IObjectWithSite //I'm using p/s of IObjectWithSite
	{
	public:
        STDMETHODIMP QueryInterface(REFIID riid,void **ppvObject) {
			if (!ppvObject)
				return E_POINTER;
			*ppvObject = NULL;
			if (riid != IID_IUnknown && riid != IID_IObjectWithSite)
				return E_NOINTERFACE;
			*ppvObject = this;
			return S_OK;
		}
        STDMETHODIMP_(ULONG) AddRef() {return 2;}
        STDMETHODIMP_(ULONG) Release() {return 1;}
        STDMETHODIMP SetSite(IUnknown *pUnkSite) {return E_NOTIMPL;}
        STDMETHODIMP GetSite(REFIID riid, void **ppvSite) {
			if (!ppvSite) 
				return E_POINTER;
			*ppvSite = NULL;
			if (!lpunk)
				return E_UNEXPECTED;
			return lpunk->QueryInterface(riid, ppvSite);
		}
		LPUNKNOWN lpunk; //doesn't add ref (to avoid cyclic references);
	public:
		CReference(LPUNKNOWN lpunk) {CReference::lpunk = lpunk;}
	};

	struct CReferenceHolder {
	public:
		CReferenceHolder(LPUNKNOWN lpunk) :
			Reference(lpunk)
		{
			gitcookie = 0;
			MarshalInGIT();
		}
		~CReferenceHolder() 
		{
			if (gitcookie && NULL != CGITHelper::GIT()) 
				CGITHelper::GIT()->RevokeInterfaceFromGlobal(gitcookie);
		}
		HRESULT GetInterthreadObjectInterface(REFIID riid, void**ppvObject) 
		{
			if (!ppvObject)
				return E_POINTER;
			*ppvObject = NULL;
			if (!gitcookie) 
				return E_UNEXPECTED;
			HRESULT hr;
			CComPtr<IObjectWithSite> pthis;
			if (NULL != CGITHelper::GIT()) {
				if (SUCCEEDED( hr = CGITHelper::GIT()->GetInterfaceFromGlobal(
					gitcookie, IID_IObjectWithSite, (void**)&pthis))) 
				{
						hr = pthis->GetSite(riid, ppvObject);
				}
			}
			return hr;
		}
	public:
		bool IsPrepared() const { return (gitcookie!=0); }

	private:
		HRESULT MarshalInGIT() 
		{
			if (NULL != CGITHelper::GIT())
				return CGITHelper::GIT()->RegisterInterfaceInGlobal(&Reference, IID_IObjectWithSite, &gitcookie);
			return E_UNEXPECTED;
		}
	private:
		CReference Reference;
		DWORD gitcookie;
	};

	typedef map< DWORD, CReferenceHolder* > _resources_map_t;

private:
	HRESULT AddObjectReference(LPCOLESTR name, LPUNKNOWN pObj) { 
		//it's preferably to use GetOrConstructNewReference instead of this one 
		// if you don't want to take a risk of possible race condition
		if (!name || !pObj) return E_INVALIDARG;
		resource_guard< _resources_map_t >::guard bag(CNamedObjTableModule::bag.Guard());
		DWORD tmpName = LHashValOfName(LOCALE_SYSTEM_DEFAULT, name);
		_resources_map_t::iterator it = (*bag).find(tmpName);
		if (it != (*bag).end())
			return E_UNEXPECTED;
		CReferenceHolder *holder = NULL;
		ATLTRY(holder = new CReferenceHolder(pObj));
		if (holder) {
			if (!holder->IsPrepared()) {
				delete holder;
				return E_FAIL;
			}
			ATLTRY((*bag)[tmpName] = holder);
		} 
		return S_OK;
	}

	HRESULT ReleaseObjectReference(LPCOLESTR name) {
		resource_guard< _resources_map_t >::guard bag(CNamedObjTableModule::bag.Guard());
		DWORD tmpName = LHashValOfName(LOCALE_SYSTEM_DEFAULT, name);
		_resources_map_t::iterator it = (*bag).find(tmpName);
		if (it == (*bag).end())
			return E_UNEXPECTED;
		if ((*it).second) delete (*it).second;
		(*bag).erase(it);
		return S_OK;
	}

	HRESULT GetObjectReference(LPCOLESTR name, REFIID riid, void**pv) {
		resource_guard< _resources_map_t >::guard bag(CNamedObjTableModule::bag.Guard());
		DWORD tmpName = LHashValOfName(LOCALE_SYSTEM_DEFAULT, name);
		_resources_map_t::iterator it = (*bag).find(tmpName);
		if (it == (*bag).end())
			return E_UNEXPECTED;
		return (*it).second->GetInterthreadObjectInterface(riid, pv);
	}

	HRESULT GetOrConstructNewReference(LPCOLESTR name, REFIID riid, void**ppv, void* pv, _NAMEDOBJECT_CREATORFUNC *pfnCreate) {
		DWORD tmpName = LHashValOfName(LOCALE_SYSTEM_DEFAULT, name);
		resource_guard< _resources_map_t >::guard bag(CNamedObjTableModule::bag.Guard());
		_resources_map_t::iterator it = (*bag).find(tmpName);
		if (it == (*bag).end()) {
			CComPtr<IUnknown> punk;
			HRESULT hr = pfnCreate(name, pv, riid, (void**)&punk);
			if (FAILED(hr)) return hr;
			CReferenceHolder *holder = NULL;
			ATLTRY(holder = new CReferenceHolder(punk));
			if (holder) {
				if (!holder->IsPrepared()) {
					delete holder;
					return E_FAIL;
				}
				ATLTRY((*bag)[tmpName] = holder);
			} 
			return (*(IUnknown**)ppv = punk)->AddRef(), S_OK;
		}
		return (*it).second->GetInterthreadObjectInterface(riid, ppv);
	}

public:
	CNamedObjTableModule() : pGIT(NULL)
	{ 
		InitGIT();		// try to initialize GIT
	}
	~CNamedObjTableModule() 
	{
		clean_bag();
	}
	IGlobalInterfaceTable *GIT() { InitGIT(); return pGIT; }

	HRESULT InitGIT()
	{
		if (NULL != pGIT.p) return S_OK;
		return CoCreateInstance(CLSID_StdGlobalInterfaceTable, NULL,
					CLSCTX_INPROC_SERVER, IID_IGlobalInterfaceTable, (void **)&pGIT);
	}

private:
	void clean_bag() {
		resource_guard< _resources_map_t >::guard bag(CNamedObjTableModule::bag.Guard());
		for (_resources_map_t::iterator it = (*bag).begin(); it != (*bag).end(); it++) {
			if ((*it).second) delete (*it).second;
		}
		(*bag).erase((*bag).begin(), (*bag).end());
	}
	resource_guard< _resources_map_t > bag;
	CComPtr<IGlobalInterfaceTable> pGIT;

	friend HRESULT NamedObjectGetReference(LPCOLESTR name, REFIID riid, void**ppv);
	friend HRESULT NamedObjectGetReference(REFCLSID cslid, LPCOLESTR name, REFIID riid, void**ppv);
	friend HRESULT NamedObjectGetReference(REFCLSID cslid, void*pv, LPCOLESTR name, REFIID riid, void**ppv);
	friend HRESULT _NamedObjectGetOrConstruct(LPCOLESTR name, void* pv, _NAMEDOBJECT_CREATORFUNC *pfnCreate, REFIID riid, void**ppv);
	friend HRESULT _NamedObjectReleaseReference(LPCOLESTR name);
};

#endif //__NAMEDOBJTABLEMODULE_H__
