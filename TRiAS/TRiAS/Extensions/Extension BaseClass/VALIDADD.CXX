// Testen, ob eine Addresse gültig ist ----------------------------------------
// File: VALIDADD.CXX

#include "xtensnp.hxx"

#if defined(WIN32)
bool WINAPI ExtIsValidString (LPCWSTR lpsz, int nLength)
{
	if (lpsz == NULL)
		return false;
	return IsWin32s() || ::IsBadStringPtrW(lpsz, nLength) == 0;
}
#endif // WIN32

bool WINAPI ExtIsValidString(LPCSTR lpsz, int nLength)
{
	if (lpsz == NULL)
		return false;
#if defined(WIN32)
	return ::IsBadStringPtrA(lpsz, nLength) == 0;
#else
	return ::IsBadStringPtr (lpsz, nLength) == 0;
#endif
}

bool WINAPI ExtIsValidAddress(const void* lp, UINT nBytes, bool bReadWrite)
{
// simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}

