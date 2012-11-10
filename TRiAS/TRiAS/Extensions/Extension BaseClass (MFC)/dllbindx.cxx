// Funktionen für dynamisches Binden der DLL ----------------------------------
// File: DLLBINDX.CXX

#include "xtensnp.hxx"

#include <dllbindx.hxx>

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if !defined(WIN16)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

CDllBindX::CDllBindX (const char *pcDLLName) 
{
	Init(pcDLLName, 0);
}

CDllBindX::CDllBindX (const char *pcDLLName, DWORD dwFlags) 
{
	Init(pcDLLName, dwFlags);
}

void CDllBindX::Init(const char *pcDLLName, DWORD dwFlags)
{
// ParameterTest
	if (NULL == pcDLLName) {
		_hLib = NULL;
		return;
	}
	m_strName = pcDLLName;

// WindowsFehlerMeldung unterdrücken
unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

// #HK990620 work around WinNT4 LoadProcess bug
char szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (m_strName.c_str(), szModuleShort, _MAX_PATH);
LPCSTR pcModule = NULL;

	if (cbShortName == _MAX_PATH)
		return;
	pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? m_strName.c_str() : szModuleShort;

	_hLib = LoadLibraryEx (pcModule, NULL, dwFlags);
	if (LOADLIBRARY_FAILED(_hLib))         // Fehler: kann DLL nicht laden
		_hLib = NULL;

// vorherigen Zustand wieder einstellen
	SetErrorMode (oldErrMode);
}

CDllBindX::~CDllBindX (void)	// DLL wieder freigeben
{
	if (_hLib != NULL)
		FreeLibrary (_hLib);
}

// Memberfunktionen -----------------------------------------------------------
FARPROC CDllBindX::GetProcAddress (const char *FunctionName)
{
	if (_hLib != NULL)
		return ::GetProcAddress (_hLib, FunctionName);
	else
		return NULL;	// Fehler
}


// Anlegen einer Instanz ------------------------------------------------------
CDllBindX *CDllBindX::CreateInstance (const char *pDLLName)
{
CDllBindX *pCDllBindX = NULL;

	try { pCDllBindX = new CDllBindX (pDLLName); } catch(...) {;}
	if (NULL == pCDllBindX || NULL == pCDllBindX -> _hLib) {
		delete pCDllBindX;
		return NULL;
	}
	return pCDllBindX;
}

CDllBindX *CDllBindX::CreateInstance (const char *pcDLLName, DWORD dwFlags)
{
CDllBindX *pCDllBindX = NULL;

	try { pCDllBindX = new CDllBindX (pcDLLName, dwFlags); } catch(...) {;}
	if (NULL == pCDllBindX || NULL == pCDllBindX -> _hLib) {
		delete pCDllBindX;
		return NULL;
	}
	return pCDllBindX;
}
