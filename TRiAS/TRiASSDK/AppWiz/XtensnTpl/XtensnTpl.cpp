// XtensnTpl.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "XtensnTpl.h"
#include "XtensnTplaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE XtensnTplDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("XTENSNTPL.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(XtensnTplDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(XtensnTplDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&XtensnTplaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("XTENSNTPL.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(XtensnTplDLL);
	}
	return 1;   // ok
}
