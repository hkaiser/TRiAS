#include "stdafx.h"
#include "LinesigImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

CLinesigApp NEAR theApp;

// {1380EAD5-04AF-11d0-AC37-00A024145748}
const GUID CDECL BASED_CODE _tlid =
	{ 0x1380ead5, 0x4af, 0x11d0, { 0xac, 0x37, 0x0, 0xa0, 0x24, 0x14, 0x57, 0x48 } };

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

////////////////////////////////////////////////////////////////////////////
// CKartenApp::InitInstance - DLL initialization

BOOL CLinesigApp::InitInstance() {
	TRACE( THIS_MODULE " Initializing... " );

	BOOL bInit = CTRiASVMDModule::InitInstance();

	if (bInit) {
		TRACE( "OK" );
	} else {
		TRACE( "FAILED" );
	}
	TRACE( "\n" );
	return bInit;
}

////////////////////////////////////////////////////////////////////////////
// CKartenApp::ExitInstance - DLL termination

int CLinesigApp::ExitInstance() {
	return CTRiASVMDModule::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void) {
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void) {
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	return NOERROR;
}

HRESULT FAR PASCAL DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv) {
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	return AfxDllGetClassObject (rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void) {
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	return AfxDllCanUnloadNow();
}
