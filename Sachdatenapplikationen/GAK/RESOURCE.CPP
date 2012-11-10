/*
File: RESOURCE.CPP
realiert die Ressourcenverwaltung für den Begleitscheinabgleich

erarbeitet : J. Benkenstein	Stand vom 18. Dezember 1996
*/

#include "stdafx.h" 		//	prec. Header
#include "res.h"			//	Resourcen

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" {
// Die Routine OutputTemplate kopiert eine Dateiresource
// in eine Ausgabedatei (oder String), deren File-Handle gegeben ist. Es wird davon
// ausgegangen, daá die Ausgabedatei eröffnet und richtig positioniert ist.
char *OutputResourceTemplate (UINT uiResID) 
{            
	ASSERT (uiResID > 0);

	char *pResource;
    DWORD SRes;
    HRSRC hFindRes;
    char *pResult = NULL;   //  ErgebnisString     
    HINSTANCE hInst = AfxGetInstanceHandle ();
    ASSERT (NULL != hInst);

//  Resource laden
    HGLOBAL hRes = LoadResource (hInst, hFindRes = FindResource (hInst,
					   			 MAKEINTRESOURCE (uiResID),
					   			 MAKEINTRESOURCE (DATEI)));
    if (!hFindRes || !hRes)
		return NULL;

//  Resource im Speicher festhalten
    pResource = (char*) LockResource (hRes);

    if (pResource) {        // wenn Resource erfolgreich geladen

    	//  Resource in Ausgabe-File/String schreiben
		if ((SRes = SizeofResource (hInst, hFindRes)) == 0)
	    	return NULL;

		if (*(pResource + SRes - 1) == '\0')    // Größe ggf. korrigieren
	    	SRes = lstrlen (pResource);

	// 	Ausgabe in String
	    if ((pResult = new char [(short) SRes + 1]) == NULL)
			AfxThrowMemoryException ();
	    memcpy (pResult, pResource, (size_t) SRes);
	    pResult [(short) SRes] = '\0';
		
	//  Resource wieder freigeben
#ifndef WIN32
		GlobalUnlock (hRes);		// für WIN32 nicht notwendig
#endif
		FreeResource (hRes);
    } else {
    //  Resource existiert nicht
		FreeResource (hRes);
		return NULL;
    }

    return pResult;
}

} // extern "C"

