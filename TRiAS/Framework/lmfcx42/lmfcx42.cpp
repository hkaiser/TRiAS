#include "stdafx.h"
#include <afxdllx.h>

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: lmfcx.cpp 1.1 1996/08/14 11:42:04 andy Exp $";
/* $Log: lmfcx.cpp $
// Revision 1.1  1996/08/14  11:42:04  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

//static AFX_EXTENSION_MODULE Mfcl40DLL = { NULL, NULL };
//
//extern "C" int APIENTRY
//DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
//	if (dwReason == DLL_PROCESS_ATTACH) {
//		TRACE0( THIS_DLL " Initializing!\n");
//		// Extension DLL one-time initialization
//		AfxInitExtensionModule(Mfcl40DLL, hInstance);
//		// Insert this DLL into the resource chain
//		new CDynLinkLibrary(Mfcl40DLL);
//	} else if (dwReason == DLL_PROCESS_DETACH) {
//		TRACE0( THIS_DLL " Terminating!\n");
//	}
//	return 1;   // ok
//}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void) {
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void) {
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void) {
	return S_OK;
}
