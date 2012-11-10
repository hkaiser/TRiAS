#include "precomp.h"
#include "CoDelegator.h"
#include "delegate.h"
#include "delegate_i.c"
#include "crt.h"

long g_cLocks;

struct REG_DATA
{
    const TCHAR *pszKeyName;
    const TCHAR *pszValueName;
    const TCHAR *pszValue;
    BOOL        bDeleteOnUnregister;
};

TCHAR g_szFileName[MAX_PATH];

const REG_DATA g_rgEntries[] =
{
    { __TEXT("CLSID\\{58DAD7D5-6F34-11D2-9EEC-006008447800}"),
      0,
      __TEXT("TRiAS CoDelegator class"),
      TRUE
    },
    { __TEXT("CLSID\\{58DAD7D5-6F34-11D2-9EEC-006008447800}\\InprocServer32"),
      0,
      g_szFileName,
      TRUE
    },
    { __TEXT("CLSID\\{58DAD7D5-6F34-11D2-9EEC-006008447800}\\InprocServer32"),
      __TEXT("ThreadingModel"),
      __TEXT("Both"),
      TRUE
    }
};

const int g_cEntries = sizeof(g_rgEntries)/sizeof(*g_rgEntries);

static HRESULT Unregister(const REG_DATA *rgEntries, int cEntries)
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

static HRESULT Register(const REG_DATA *rgEntries, int cEntries)
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
                Unregister(rgEntries, 1 + pEntry - rgEntries);
            }
            RegCloseKey(hkey);
        }
        if (err != ERROR_SUCCESS)
        {
            bSuccess = FALSE;
            if (pEntry != rgEntries)
                Unregister(rgEntries, pEntry - rgEntries);
        }
        pEntry++;
    }
    return bSuccess ? S_OK : E_FAIL;
}

void SvcLock()
{
	InterlockedIncrement( &g_cLocks );
}

void SvcUnlock()
{
	InterlockedDecrement( &g_cLocks );
}

class CoDelegatorFactory : public IDelegatorFactory
{
public:
	STDMETHODIMP QueryInterface( REFIID iid, void** ppv )
	{
		if ( !ppv )
			return E_POINTER;
		if ( IID_IDelegatorFactory == iid )
			*ppv = (IDelegatorFactory*) this;
		else if ( IID_IUnknown == iid )
			*ppv = (IDelegatorFactory*) this;
		else return (*ppv = 0), E_NOINTERFACE;
		((IUnknown*)*ppv)->AddRef();
		return S_OK;
	}
	STDMETHODIMP_(ULONG) AddRef()
	{
		SvcLock();
		return 2;
	}
	STDMETHODIMP_(ULONG) Release()
	{
		SvcUnlock();
		return 1;
	}
	STDMETHODIMP CreateDelegator( IUnknown* pUnkOuter, IUnknown* pUnkInner,
		REFIID iid, void** ppv )
	{
		// must pass both an outer and inner
		if ( !pUnkOuter || !pUnkInner )
			return E_UNEXPECTED;
		CoDelegator* p = new CoDelegator( pUnkOuter, pUnkInner );
		if ( !p )
			return E_OUTOFMEMORY;
		p->AddRef();
		HRESULT hr = p->QueryInterface( iid, ppv );
		p->Release();
		return hr;
	}
};

CoDelegatorFactory g_factory;

BOOL WINAPI DllMain(HINSTANCE h, DWORD dwReason, void *)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
		#ifdef _DEBUG
		OutputDebugString( __TEXT( "delegate.dll loaded\n" ) );
		#endif // _DEBUG

		// we must initialize static data ourselves (no crt)
//		new( &g_factory ) CoDelegatorFactory;

        GetModuleFileName(h, g_szFileName, MAX_PATH);
    }
	else if ( dwReason == DLL_PROCESS_DETACH )
	{
		#ifdef _DEBUG
		OutputDebugString( __TEXT( "delegate.dll unloaded\n" ) );
		#endif // _DEBUG
	}
    return TRUE;
}

STDAPI DllCanUnloadNow()
{
	return g_cLocks ? S_FALSE : S_OK;
}

STDAPI DllGetClassObject( REFCLSID clsid, REFIID iid, void** ppv )
{
	if ( CLSID_CoDelegator == clsid )
		 return g_factory.QueryInterface( iid, ppv );
	else return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllRegisterServer()
{
	return Register( g_rgEntries, g_cEntries );
}

STDAPI DllUnregisterServer()
{
	return Unregister( g_rgEntries, g_cEntries );
}
