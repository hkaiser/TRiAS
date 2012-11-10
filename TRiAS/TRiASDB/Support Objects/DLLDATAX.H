///////////////////////////////////////////////////////////////////////////
// DLLDATAX.H

#if !defined(_DLLDATAX_H__8F6964F4_7897_11D1_9760_00A024D6F582__INCLUDED_)
#define _DLLDATAX_H__8F6964F4_7897_11D1_9760_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _MERGE_PROXYSTUB

extern "C" 
{
BOOL WINAPI PrxDllMain(HINSTANCE hInstance, DWORD dwReason, 
	LPVOID lpReserved);
STDAPI PrxDllCanUnloadNow(void);
STDAPI PrxDllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
STDAPI PrxDllRegisterServer(void);
STDAPI PrxDllUnregisterServer(void);
}

#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_DLLDATAX_H__8F6964F4_7897_11D1_9760_00A024D6F582__INCLUDED_)
