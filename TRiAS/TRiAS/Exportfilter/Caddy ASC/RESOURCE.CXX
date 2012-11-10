/*
File: RESOURCE.C
realiert die Ressourcenverwaltung für den CADdy-Filter.

erarbeitet : J. Benkenstein		    Stand vom 18. November 1992
*/

#include "pheader.h"
    
#include "caddyasc.hr"	// zugehörige Konstanten		

extern "C" {
extern HINSTANCE hDLLInst;	// hInst dieser DLL

// Die Routine OutputTemplate kopiert eine Dateiresource
// in eine Ausgabedatei, deren File-Handle gegeben ist. Es wird davon ausge-
// gangen, daß die Ausgabedatei eröffnet und richtig positioniert ist.
BOOL FAR PASCAL OutputResourceTemplate (int fh, int ResID) {

    char *lpResource;
    DWORD SRes;
    HRSRC hFindRes;

//  Resource laden
    HGLOBAL hRes = LoadResource (hDLLInst, hFindRes = FindResource (hDLLInst,
					   MAKEINTRESOURCE (ResID),
					   MAKEINTRESOURCE (DATEI)));
    if (!hFindRes || !hRes)
        return FALSE;

//  Resource im Speicher festhalten
    lpResource = (char *) LockResource (hRes);

    if (lpResource) {	    // wenn Resource erfolgreich geladen

    //	Resource in Ausgabe-File schreiben
		if ((SRes = SizeofResource (hDLLInst, hFindRes)) == 0)
	    	return FALSE;

		if (*(lpResource + SRes - 1) != '\0')
	    	_lwrite (fh, lpResource, (UINT) SRes);
		else
	    	_lwrite (fh, lpResource, lstrlen (lpResource));

    // Resource wieder freigeben
		GlobalUnlock (hRes);
		FreeResource (hRes);
    } else {
    	// Resource existiert nicht
		FreeResource (hRes);
		return FALSE;
    }

    return TRUE;
}
}               // extern "C"
