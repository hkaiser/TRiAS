// DummyVarianten für diverse Funktionen --------------------------------------
// File: DUMMY5.CXX

#include "xtensnp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(WIN32)

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// keine ObjectMap
}

#endif // WIN32