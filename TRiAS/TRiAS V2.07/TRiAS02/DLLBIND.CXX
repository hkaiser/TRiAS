// Funktionen für dynamisches Binden der DLL ----------------------------------
// File: DLLBIND.CXX

#include "trias02p.hxx"

#if defined(WIN32)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

EXPORT02 DLLBind :: DLLBind (const char *DLLName, DWORD dwFlags) 
{
// ParameterTest
	if (DLLName == NULL) {
		_hLib = NULL;
		return;
	}

	m_strName = DLLName;

// WindowsFehlerMeldung unterdrücken
unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

#if defined(WIN32)
	_hLib = LoadLibraryEx ((char *)DLLName, NULL, dwFlags);
#else
	_hLib = LoadLibrary ((char *)DLLName);
#endif
	if (LOADLIBRARY_FAILED(_hLib))         // Fehler: kann DLL nicht laden
		_hLib = NULL;

// vorherigen Zustand wieder einstellen
	SetErrorMode (oldErrMode);
}

EXPORT02 DLLBind :: ~DLLBind (void) 
{    // DLL wieder freigeben
	if (_hLib != NULL)
		FreeLibrary (_hLib);
}

DLLBind *EXPORT02 DLLBind :: CreateInstance (const char *pDLLName, DWORD dwFlags)
{
DLLBind *pDLL = new DLLBind (pDLLName, dwFlags);

	if (pDLL == NULL || pDLL -> hLib() == NULL) {
		DELETE (pDLL);
		return NULL;
	}

return pDLL;
}

// Memberfunktionen -----------------------------------------------------------
FARPROC EXPORT02 DLLBind :: GetProcAddress (const char *FunctionName) 
{
	if (_hLib != NULL)
		return ::GetProcAddress (_hLib, FunctionName);
	else
		return NULL;	// Fehler
}

LPCSTR EXPORT02 DLLBind :: GetName (void)
{ 
	return m_strName.c_str(); 
}
