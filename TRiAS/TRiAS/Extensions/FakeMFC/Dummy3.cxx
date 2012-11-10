// DummyVarianten für diverse Funktionen --------------------------------------
// File: DUMMY3.CXX

#include "fakemfcp.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL GetTypeLibName (TCHAR *)
{
	return false;		// kein TypeLibName
}

