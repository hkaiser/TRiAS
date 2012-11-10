// DummyVarianten für diverse Funktionen --------------------------------------
// File: DUMMY4.CXX

#include "fakemfcp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if !defined(WIN32) || defined(OLE2ANSI)
BOOL GetLicenseKey (LPSTR, size_t)
{
	return true;		// keine Lizensierung notwendig
}
#else
BOOL GetLicenseKey (LPWSTR, size_t)
{
	return true;		// keine Lizensierung notwendig
}
#endif // WIN32

BOOL GetLicensed (void)		// so tun, als ob lizensiert wäre
{
	return true;
}

#if defined(WIN32)
BOOL SetLicensed (LPCSTR)		// Lizensierung ist erfolgt
{
	return true;
}
#else
void SetLicensed (void)		// Lizensierung ist erfolgt
{
}
#endif // WIN32

