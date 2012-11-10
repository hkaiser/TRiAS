///////////////////////////////////////////////////////////////////////////////
// @doc
// @module Utils.cpp | Diverse Hilfsfunktionen

#include "trias02p.hxx"

#include "Strings.h"
#include "utils.h"

extern "C" HINSTANCE g_hInstance;
extern char g_pDLLName[260];

// FormatMessage aus MessageTable in ein CString
void __cdecl FormatMessage(string &rStr, UINT uiError, ...)
{
// format message into temporary buffer lpszTemp
DWORD dwFlags = FORMAT_MESSAGE_FROM_HMODULE|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER;
LPTSTR lpszTemp = NULL;
va_list argList;

	va_start(argList, uiError);
	if (::FormatMessage (dwFlags, g_hInstance, uiError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		lpszTemp == NULL)
	{
		rStr = g_cbNoMemory;
	}
	else	// assign lpszTemp into the resulting string and free lpszTemp
		rStr = lpszTemp;

	if (lpszTemp) LocalFree(lpszTemp);
	va_end(argList);
}

void ShowError (HRESULT hr, UINT resID, LPCTSTR pcRoutine)
{ 
ResourceFile RF (g_pDLLName);
string str; 

	FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
	ErrorWindow (NULL, FakeTRiASName (ResID (resID, &RF)).c_str(), str.c_str());
}

string FakeTRiASName (ResID resID, ...)
{
char cbOut[1024];

	try {
	ResString resTempl (resID, _MAX_PATH);
	va_list params;

		va_start (params, resID);
		wvsprintf (cbOut, resTempl, params);
		va_end (params);

		return string(cbOut);
	
	} catch (...) {
	// irgendein Fehler
		return string(g_cbNil);
	}
}

string FakeTRiASName (LPCSTR pcTempl, ...)
{
char cbOut[1024];

	try {
	va_list params;

		va_start (params, pcTempl);
		wvsprintf (cbOut, pcTempl, params);
		va_end (params);

		return string(cbOut);
	
	} catch (...) {
	// irgendein Fehler
		return string(g_cbNil);
	}
}

