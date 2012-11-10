/*
File: RESOURCE.CXX
realiert die Ressourcenverwaltung für den AutoCAD-Filter.

erarbeitet : J. Benkenstein                 Stand vom 13. April 1994
*/

#include "stdafx.h"
#include "AcadDXFImpl.h"

//XX#include "acaddxf.hr"           // Resourcen-Defines

//XX	extern "C" {
//XX	extern HINSTANCE hDLLInst;         // hInst dieser DLL

// Die Routine OutputTemplate kopiert eine Dateiresource
// in eine Ausgabedatei (oder String), deren File-Handle gegeben ist. Es wird davon
// ausgegangen, daá die Ausgabedatei eröffnet und richtig positioniert ist.
pchar OutputResourceTemplate (int ResID, int fh) {

    pchar pResource;
    DWORD SRes;
    HRSRC hFindRes;
    pchar pResult = NULL;   //  ErgebnisString

//  Resource laden
//XX	    HGLOBAL hRes = LoadResource (hDLLInst, hFindRes = FindResource (hDLLInst,
/*XX*/	    HGLOBAL hRes = LoadResource (_Module.GetResourceInstance(), hFindRes = FindResource (_Module.GetResourceInstance(),
					   			 MAKEINTRESOURCE (ResID),
					   			 MAKEINTRESOURCE (DATEI)));
    if (!hFindRes || !hRes)
		return NULL;

//  Resource im Speicher festhalten
    pResource = (pchar) LockResource (hRes);

    if (pResource) {        // wenn Resource erfolgreich geladen

    	//  Resource in Ausgabe-File/String schreiben
//XX			if ((SRes = SizeofResource (hDLLInst, hFindRes)) == 0)
/*XX*/			if ((SRes = SizeofResource (_Module.GetResourceInstance(), hFindRes)) == 0)
	    	return NULL;

		if (*(pResource + SRes - 1) == '\0')    // Größe ggf. korrigieren
	    	SRes = lstrlen (pResource);

		if (fh)     // wenn FileHandle gegeben
	    	_lwrite (fh, pResource, (UINT) SRes);
		else {      // Ausgabe in String
	    	if ((pResult = new char [(short) SRes + 1]) == NULL)
				return NULL;
	    	memcpy (pResult, pResource, (size_t) SRes);
	    	pResult [(short) SRes] = '\0';
		}

	//  Resource wieder freigeben
		GlobalUnlock (hRes);
		FreeResource (hRes);
    } else {
    //  Resource existiert nicht
		FreeResource (hRes);
		return NULL;
    }

    return fh ? (pchar) 1 : pResult;
}

//XX	} // extern "C"
