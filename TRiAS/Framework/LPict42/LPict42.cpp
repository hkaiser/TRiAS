#include "stdafx.h"
#include <afxdllx.h>
#include "LPictImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

extern BOOL InitMasterMap(HINSTANCE hInstance);

static AFX_EXTENSION_MODULE LPict40DLL = { NULL, NULL };

extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (dwReason == DLL_PROCESS_ATTACH) {
		TRACE0( PICT_DLL " Initializing...");
		// Extension DLL one-time initialization
		AfxInitExtensionModule(LPict40DLL, hInstance);
		// Insert this DLL into the resource chain
		new CDynLinkLibrary(LPict40DLL);
		if( !InitMasterMap( hInstance ) ) {
			TRACE0( "FAILED!\n" );
			return 0;
		}
		TRACE0( "OK!\n" );
	} 
	else if (dwReason == DLL_PROCESS_DETACH) {
		CPolyGISPicture::ReleaseCache();
		AfxTermExtensionModule(LPict40DLL);
		TRACE0( PICT_DLL " Terminating...\n");
		TRACE0( "OK!\n" );
	}
	return 1;   // ok
}

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
