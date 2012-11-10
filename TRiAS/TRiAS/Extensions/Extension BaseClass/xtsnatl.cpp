// ATL-Implementation ---------------------------------------------------------
// File: XTSNATL.CPP

#include "xtensnp.hxx"

#if !defined(__ATL_70_USED__)

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(__ATL_20_USED__)
#include <atlimpl.cpp>
#elif defined(__ATL_11_USED__)
#include <atlimpl11.h>
#else
#include <ospace/com/atlimpl.h>
#endif

#endif // !defined(__ATL_70_USED__)
