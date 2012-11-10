// Funktionen fÅr dynamisches Binden der DLL ----------------------------------
// File: DLLBIND.CXX

extern "C" {
	#include <windows.h>
}

#include <dllbind.hxx>

#if !defined(MSWIND)
#error "Diese Datei kann nur fÅr MS-Windows verwendet werden"
#endif

DLLBind :: DLLBind (const char *DLLName) {

// WindowsFehlerMeldung unterdrÅcken
unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

	_hLib = LoadLibrary ((char *)DLLName);
	if (_hLib < 32)         // Fehler: kann DLL nicht laden
		_hLib = NULL;

// vorherigen Zustand wieder einstellen
	SetErrorMode (oldErrMode);
}

DLLBind :: ~DLLBind (void) {    // DLL wieder freigeben

	if (_hLib != NULL)
		FreeLibrary (_hLib);
}

// Memberfunktionen -----------------------------------------------------------
FARPROC DLLBind :: GetProcAddress (const char *FunctionName) {

	if (_hLib != NULL)
		return ::GetProcAddress (_hLib, FunctionName);
	else
		return NULL;	// Fehler
}
