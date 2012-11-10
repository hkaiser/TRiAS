// Funktionen für dynamisches Binden der DLL ----------------------------------
// File: DLLBIND.CXX

#include "trias02p.hxx"

#if !defined(WIN16)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

EXPORT02 DLLBind::DLLBind (const char *pcDLLName, DWORD dwFlags) 
{
// ParameterTest
	if (NULL == pcDLLName) {
		_hLib = NULL;
		return;
	}
	m_strName = pcDLLName;

// WindowsFehlerMeldung unterdrücken
unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

#if !defined(WIN16)
// #HK990620 work around WinNT4 LoadProcess bug
char szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (m_strName.c_str(), szModuleShort, _MAX_PATH);
LPCSTR pcModule = NULL;

	if (cbShortName == _MAX_PATH)
		return;
	pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? m_strName.c_str() : szModuleShort;
	_hLib = LoadLibraryEx (pcModule, NULL, dwFlags);
#else
	_hLib = LoadLibrary ((char *)m_strName.c_str());
#endif
	if (LOADLIBRARY_FAILED(_hLib))         // Fehler: kann DLL nicht laden
		_hLib = NULL;

// vorherigen Zustand wieder einstellen
	SetErrorMode (oldErrMode);
}

EXPORT02 DLLBind::~DLLBind (void) 
{    // DLL wieder freigeben
	if (_hLib != NULL)
		FreeLibrary (_hLib);
}

DLLBind *EXPORT02 DLLBind::CreateInstance (const char *pDLLName, DWORD dwFlags)
{
DLLBind *pDLL = NULL;

	TX_TRY(pDLL = new DLLBind (pDLLName, dwFlags));
	if (pDLL == NULL || pDLL -> hLib() == NULL) {
		DELETE_OBJ (pDLL);
		return NULL;
	}
	return pDLL;
}

// Memberfunktionen -----------------------------------------------------------
FARPROC EXPORT02 DLLBind::GetProcAddress (const char *FunctionName) 
{
	if (_hLib != NULL)
		return ::GetProcAddress (_hLib, FunctionName);
	else
		return NULL;	// Fehler
}

LPCSTR EXPORT02 DLLBind::GetName (void)
{ 
	return m_strName.c_str(); 
}
