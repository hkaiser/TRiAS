#include "Vismod.h"
#include "Karten.h"

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

//#include "TKResrc.h"       // main symbols
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CKartenApp : See karten.cpp for implementation.

#ifdef _DEBUG
	#define THIS_MODULE "karten.vmd (Debug)"
#else
	#define THIS_MODULE "karten.vmd (Release)"
#endif

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ


class CKartenApp : public CTRiASVMDModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;
