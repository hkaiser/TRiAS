// $Header: $
// Copyrightę 1998-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 21:21:48 
//
// This file was generated by the TRiASDB Data Server Wizard V1.02.103 (#HK000729)
//
// @doc
// @module dlldatax.h | Declarations for proxy/stub stuff

#if !defined(_DLLDATAX_H__B225876A_B814_48F3_9656_F93334E997E1__INCLUDED_)
#define _DLLDATAX_H__B225876A_B814_48F3_9656_F93334E997E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_DLLDATAX_H__B225876A_B814_48F3_9656_F93334E997E1__INCLUDED_)
