// File: GeoUtil.cpp

#include "StdAfx.h"
#include "TDBGeoImpl.h"

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTyble in ein CString
void __cdecl FormatMessage(CString & rStr , UINT uiError , ...)
{
	// format message into temporary buffer lpszTemp
	DWORD dwFlags = FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER;
	LPTSTR lpszTemp = NULL;
	va_list argList;

	va_start(argList , uiError);
	if (::FormatMessage (dwFlags , _Module.GetResourceInstance() , uiError , 0 , (LPTSTR) & lpszTemp , 0 , & argList) == 0 ||
		lpszTemp == NULL)
	{
#if defined(_DEBUG)
		dwFlags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS;

		DWORD dwError = GetLastError();

		::FormatMessage (dwFlags , NULL , dwError , 0 , (LPTSTR) & lpszTemp , 0 , NULL);
		rStr = lpszTemp;
#else
		rStr = g_cbNoMemory;
#endif // _DEBUG
	}
	else	// assign lpszTemp into the resulting string and free lpszTemp
		rStr = lpszTemp;

	if (lpszTemp) LocalFree(lpszTemp);
	va_end(argList);
}
