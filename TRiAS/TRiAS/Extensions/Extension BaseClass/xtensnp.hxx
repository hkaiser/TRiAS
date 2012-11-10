// Precompiled Header für XTENSN.LIB ------------------------------------------
// File: XTENSNP.HXX

#if !defined(_XTENSNP_HXX)
#define _XTENSNP_HXX

#if _MSC_VER >= 1100
#include "XtensionConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <bool.h>

#if defined(__MFC__)

#if defined(WIN32)
#include <afxwin.h>

///////////////////////////////////////////////////////////////////////////////
// richtige ATL Version verwenden
#if defined(__ATL_70_USED__)
#include <atlbase.h>
#include <atlcom.h>
#elif defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#include <ospace/com/atl10.h>
#endif
extern CComModule _Module;
extern _ATL_OBJMAP_ENTRY *GetObjectMap (void);

#include <ospace/com/smartif.h>
#include <olectl.h>

#else
#include <afxctl.h>
#endif
#include <afxdisp.h>

#elif defined(__WTL__)

#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
extern _ATL_OBJMAP_ENTRY *GetObjectMap (void);
#include <atlcom.h>
#include <atlctl.h>
#include <atlwin.h>
#include <atlmisc.h>

#include <ospace/com/smartif.h>

#else // __MFC__

#include <windows.h>

#if defined(WIN32)

///////////////////////////////////////////////////////////////////////////////
// richtige ATL Version verwenden
#if defined(__ATL_70_USED__)
#include <atlbase.h>
#include <atlcom.h>
#elif defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#include <ospace/com/atl10.h>
#endif
extern CComModule _Module;
extern _ATL_OBJMAP_ENTRY *GetObjectMap (void);

#include <ospace/com/smartif.h>

#else // WIN32
#include <shellapi.h>
#include <ole2.h>
#include <olenls.h>
#include <dispatch.h>
#endif // !WIN32

#include <olectl.h>

#endif // __MFC__

#include <stdlib.h>
#if !defined(__NOTRIASSTRINGS__)
#include <tstring>
#else
#include <string>
#endif // __NOTRIASSTRINGS__

#include <tchar.h>

#include <protos.h>

#include <xtension.h>
#include <xtensnx.h>
#include <xtensnxx.h>
#include <xtensnn.h>
#include <xtsnaux.hxx>

#if defined(__CV__)
#include <commonvu.hxx>
#endif
#include <containr.hxx>

#include <errcodes.hxx>
#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#if !defined(__ATL_XTENSION_BASE__)
#include <xtencunk.hxx>		// die Erweiterung selbst
#include "cimpxtsn.hxx"
#else
#include <xtencatl.hxx>		// die Erweiterung selbst
#endif // !__ATL_XTENSION_BASE__

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);(x)=NULL;}
#endif // DELETE_OBJ

#endif // _XTENSNP_HXX
