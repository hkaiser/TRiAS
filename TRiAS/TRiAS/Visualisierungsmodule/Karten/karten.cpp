#include "stdafx.h"
#include "KartenImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

CKartenApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x0603C947, 0xB16A, 0x11cf, { 0x86, 0xaa, 0x00, 0xa0, 0x24, 0x14, 0x57, 0x48 } };

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

////////////////////////////////////////////////////////////////////////////
// CKartenApp::InitInstance - DLL initialization

BOOL CKartenApp::InitInstance() {
	TRACE( THIS_MODULE " Initializing... " );

	BOOL bInit = CTRiASVMDModule::InitInstance();
	if (bInit) {
		// TODO: Add your own module initialization code here.
		TRACE( "OK" );
	} else {
		TRACE( "FAILED" );
	}
	TRACE( "\n" );
	return bInit;
}

////////////////////////////////////////////////////////////////////////////
// CKartenApp::ExitInstance - DLL termination

int CKartenApp::ExitInstance() {
	// TODO: Add your own module termination code here.
	TRACE( THIS_MODULE " Terminating!\n" );
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

extern "C"
STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	return AfxDllGetClassObject (rclsid, riid, ppv);
}

extern "C" 
STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	return AfxDllCanUnloadNow();
}
