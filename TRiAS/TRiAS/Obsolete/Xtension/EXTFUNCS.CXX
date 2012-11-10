// Funktionen von anderen Erweiterungen direkt rufen --------------------------
// File: EXTFUNCS.CXX

extern "C" {
	#include <windows.h>
	#include <string.h>

	#include <zprotos.h>
}

#include <commonvu.hxx>
#define NOWODELETE
#include <containr.hxx>

#include <dllbind.hxx>
#include "extfunc.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
ExtFuncProc :: ExtFuncProc (const char *pName)
{
	if (pName) {
		_pName = new char [strlen(pName)+1];
		if (_pName) strcpy (_pName, pName);
	}
}

ExtFuncProc :: ~ExtFuncProc (void)
{
	DELETE (_pName);
}

void *GetDLLName (void *pObj)
{
	return ((ExtFuncProc *)pObj) -> _pName;
}

// Funktionen fr den Baum ----------------------------------------------------
void ExtFuncProcTree :: UserDelete (void *pObj)
{
	((ExtFuncProc *)pObj) -> ExtFuncProc :: ~ExtFuncProc ();
}


// Klasse der Erweiterung die diese Eigenschaften hat -------------------------
// Registrieren einer Funktion in einer anderen Erweiterung -------------------
EXTPROC ExtFuncExtension :: RegisterExtFunction (const char *pEName, 
					 	 const char *pFName)
{
// 1. dafr sorgen, daá die geforderte Erweiterung geladen ist
	if (DEX_LoadExtension (pEName) == 0) return NULL;

// 2. Func merken
	if (_pEFL == NULL) {
		_pEFL = new ExtFuncProcTree();
		if (_pEFL == NULL) return NULL;
	}

Table t(*_pEFL);

	if (!t.Find (pEName)) {
	ExtFuncProcCreator EFCr (*_pEFL);
	ExtFuncProc *pEFP = Create (EFCr, ExtFuncProc)(pEName);

		if (pEFP) return pEFP -> GetProcAddress (pFName);
	} else {
	ExtFuncProcLock l(t);

		if (l) return l -> GetProcAddress (pFName);
	}

return NULL;
}
