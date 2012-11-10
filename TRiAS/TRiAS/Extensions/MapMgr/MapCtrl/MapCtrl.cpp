#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "MapCtrl.h"
#include "MapCtrl_i.c"

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

CComModule _Module;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	} else if (dwReason == DLL_PROCESS_DETACH) {
		_Module.Term();
	}
	return TRUE;    // ok
}

STDAPI DllCanUnloadNow(void) {
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
	return _Module.GetClassObject(rclsid, riid, ppv);
}
STDAPI DllRegisterServer(void) {
	return _Module.RegisterServer(TRUE);
}
STDAPI DllUnregisterServer(void) {
	_Module.UnregisterServer();
	return S_OK;
}
