// ConsApp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "ConsApp.h"
#include "ConsAppaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE ConsAppDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("CONSAPP.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(ConsAppDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(ConsAppDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&ConsAppaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("CONSAPP.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(ConsAppDLL);
	}
	return 1;   // ok
}
