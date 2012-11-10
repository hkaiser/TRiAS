#include "vismod.h"
#include "Linesig.h"

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#define	APSTUDIO_INVOKED
#include "resource.h"       // main symbols
#define	IDC_WMF_SHAPE _APS_NEXT_RESOURCE_VALUE + 1
#undef	APSTUDIO_INVOKED

/////////////////////////////////////////////////////////////////////////////
// CKartenApp : See karten.cpp for implementation.

#ifdef _DEBUG
	#define THIS_MODULE "linesig.vmd (Debug)"
#else
	#define THIS_MODULE "linesig.vmd (Release)"
#endif

class CLinesigApp : public CTRiASVMDModule {
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;
