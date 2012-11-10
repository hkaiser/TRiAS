// Funktionen für dynamisches Binden der DLL ----------------------------------
// File: DLLBINDX.CPP

#include "fakemfcp.hxx"

#include <dllbindx.hxx>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if !defined(WIN16)
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

	m_strName = DLLName;

// WindowsFehlerMeldung unterdrücken
unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

// #HK990620 work around WinNT4 LoadProcess bug
char szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (m_strName.c_str(), szModuleShort, _MAX_PATH);
LPCSTR pcModule = NULL;

	if (cbShortName == _MAX_PATH)
		return;
	pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? m_strName.c_str() : szModuleShort;

	_hLib = LoadLibrary (pcModule);
	if (LOADLIBRARY_FAILED(_hLib))         // Fehler: kann DLL nicht laden
		_hLib = NULL;

// vorherigen Zustand wieder einstellen
	SetErrorMode (oldErrMode);
}

CDllBindX :: ~CDllBindX (void)	// DLL wieder freigeben
{
	if (_hLib != NULL)
		FreeLibrary (_hLib);
}

// Memberfunktionen -----------------------------------------------------------
FARPROC CDllBindX :: GetProcAddress (const char *FunctionName)
{
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
