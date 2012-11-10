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
bool GetLicenseKey (LPSTR, size_t)
{
	return true;		// keine Lizensierung notwendig
}
#else
bool GetLicenseKey (LPWSTR, size_t)
{
	return true;		// keine Lizensierung notwendig
}
#endif // WIN32

bool GetLicensed (void)		// so tun, als ob lizensiert wäre
{
	return true;
}

#if defined(WIN32)
bool SetLicensed (LPCSTR)		// Lizensierung ist erfolgt
{
	return true;
}
#else
void SetLicensed (void)		// Lizensierung ist erfolgt
{
}
#endif // WIN32

