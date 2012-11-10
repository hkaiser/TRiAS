// DummyVarianten für diverse Funktionen --------------------------------------
// File: DUMMY3.CXX

#include "xtensnp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

BOOL GetTypeLibName (TCHAR *)
{
	return false;		// kein TypeLibName
}

