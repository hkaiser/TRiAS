// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/12/1998 09:46:52 AM
//
// @doc
// @module DelegatorSvc.cpp | Description goes here

#include "trias03p.hxx"

#include "CoDelegator.h"

extern LONG g_cLock;

struct REG_DATA
{
    const TCHAR *pszKeyName;
    const TCHAR *pszValueName;
    const TCHAR *pszValue;
    BOOL        bDeleteOnUnregister;
};

extern char g_pDLLName[];

const REG_DATA g_rgEntries[] =
{
    { __TEXT("CLSID\\{58DAD7D5-6F34-11D2-9EEC-006008447800}"),
      0,
      __TEXT("TRiAS CoDelegator class"),
      TRUE
    },
    { __TEXT("CLSID\\{58DAD7D5-6F34-11D2-9EEC-006008447800}\\InprocServer32"),
      0,
      g_pDLLName,
      TRUE
    },
    { __TEXT("CLSID\\{58DAD7D5-6F34-11D2-9EEC-006008447800}\\InprocServer32"),
      __TEXT("ThreadingModel"),
      __TEXT("Both"),
      TRUE
    }
};
const int g_cEntries = sizeof(g_rgEntries)/sizeof(*g_rgEntries);

static HRESULT UnregisterDelegator(const REG_DATA *rgEntries, int cEntries)
{
    BOOL bSuccess = TRUE;
    for (int i = cEntries - 1; i >= 0; i--)
        if (rgEntries[i].bDeleteOnUnregister)
        {
            
            LONG err = RegDeleteKey(HKEY_CLASSES_ROOT,
                                    rgEntries[i].pszKeyName);
            if (err != ERROR_SUCCESS)
                bSuccess = FALSE;
        }
    return bSuccess ? S_OK : S_FALSE;
}

static HRESULT RegisterDelegator(const REG_DATA *rgEntries, int cEntries)
{
    BOOL bSuccess = TRUE;
    const REG_DATA *pEntry = rgEntries;
    while (pEntry < rgEntries + cEntries)
    {
        HKEY hkey;
        LONG err = RegCreateKey(HKEY_CLASSES_ROOT,
                                pEntry->pszKeyName,
                                &hkey);
        if (err == ERROR_SUCCESS)
        {
            err = RegSetValueEx(hkey, 
                                pEntry->pszValueName,
                                0, REG_SZ, 
                                (const BYTE*)pEntry->pszValue,
                                (lstrlen(pEntry->pszValue) + 1) * sizeof(TCHAR));
            if (err != ERROR_SUCCESS)
            {
                bSuccess = FALSE;
                UnregisterDelegator(rgEntries, 1 + pEntry - rgEntries);
            }
            RegCloseKey(hkey);
        }
        if (err != ERROR_SUCCESS)
        {
            bSuccess = FALSE;
            if (pEntry != rgEntries)
                UnregisterDelegator(rgEntries, pEntry - rgEntries);
        }
        pEntry++;
    }
    return bSuccess ? S_OK : E_FAIL;
}

void DelegatorSvcLock()
{
	InterlockedIncrement (&g_cLock) ;
}

void DelegatorSvcUnlock()
{
	InterlockedDecrement (&g_cLock) ;
}

class CoDelegatorFactory : public IDelegatorFactory
{
public:
	STDMETHODIMP QueryInterface (REFIID iid, void** ppv) 
	{
		if (!ppv) 
			return E_POINTER;
		if (IID_IDelegatorFactory == iid) 
			*ppv = (IDelegatorFactory *) this;
		else if  (IID_IUnknown == iid) 
			*ppv = (IDelegatorFactory *) this;
		else 
			return (*ppv = 0), E_NOINTERFACE;
		((IUnknown*)*ppv)->AddRef();
		return S_OK;
	}
	STDMETHODIMP_(ULONG) AddRef()
	{
		DelegatorSvcLock();
		return 2;
	}
	STDMETHODIMP_(ULONG) Release()
	{
		DelegatorSvcUnlock();
		return 1;
	}
	STDMETHODIMP CreateDelegator (IUnknown* pUnkOuter, IUnknown* pUnkInner,
		REFIID iid, void** ppv) 
	{
	// must pass both an outer and inner
		if (!pUnkOuter || !pUnkInner) 
			return E_UNEXPECTED;
	CoDelegator *p = NULL;
	
		ATLTRY(p = new CoDelegator (pUnkOuter, pUnkInner));
		if (!p) return E_OUTOFMEMORY;

		p->AddRef();

	HRESULT hr = p->QueryInterface (iid, ppv);

		p->Release();
		return hr;
	}
};

CoDelegatorFactory g_factory;

HRESULT CreateDelegatorFactory (REFIID riid, LPVOID *ppv)
{
	return g_factory.QueryInterface (riid, ppv);
}

STDAPI DelegatorRegisterServer()
{
	return RegisterDelegator (g_rgEntries, g_cEntries) ;
}

STDAPI DelegatorUnregisterServer()
{
	return UnregisterDelegator (g_rgEntries, g_cEntries) ;
}
