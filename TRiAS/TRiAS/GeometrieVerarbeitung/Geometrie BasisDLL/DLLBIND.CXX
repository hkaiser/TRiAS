// Funktionen für dynamisches Binden der DLL ----------------------------------
// File: CDllBindX.CXX

#include "GeometrP.hxx"

#if !defined(MSWIND)
#error "Diese Datei kann nur für MS-Windows verwendet werden"
#endif

#if defined(WIN32)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

CDllBindX :: CDllBindX (const char *DLLName) 
{
// ParameterTest
	if (DLLName == NULL) {
		_hLib = NULL;
		return;
	}

// WindowsFehlerMeldung unterdrücken
unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

	_hLib = LoadLibrary ((char *)DLLName);
	if (LOADLIBRARY_FAILED(_hLib))         // Fehler: kann DLL nicht laden
		_hLib = NULL;

// vorherigen Zustand wieder einstellen
	SetErrorMode (oldErrMode);
}

CDllBindX :: ~CDllBindX (void) {    // DLL wieder freigeben

	if (_hLib != NULL)
		FreeLibrary (_hLib);
}

// Memberfunktionen -----------------------------------------------------------
FARPROC CDllBindX :: GetProcAddress (const char *FunctionName) {

	if (_hLib != NULL)
		return ::GetProcAddress (_hLib, FunctionName);
	else
		return NULL;	// Fehler
}


// Anlegen einer Instanz ------------------------------------------------------
CDllBindX *CDllBindX :: CreateInstance (const char *pDLLName)
{
CDllBindX *pCDllBindX = new CDllBindX (pDLLName);

	if (pCDllBindX == NULL) return NULL;
	if (pCDllBindX -> _hLib == NULL) {
		delete pCDllBindX;
		return NULL;
	}

return pCDllBindX;
}
