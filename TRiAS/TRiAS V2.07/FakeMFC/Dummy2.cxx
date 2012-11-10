// DummyVarianten für diverse Funktionen --------------------------------------
// File: DUMMY2.CXX

#include "fakemfcp.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool GetTypeLibGUID (GUID &)
{
	return false;		// keine TypeLib
}

