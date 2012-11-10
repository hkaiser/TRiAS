/*
File: RESOURCE.CXX
realiert die Ressourcenverwaltung für die Komplexrecherche.

erarbeitet : J. Benkenstein				 Stand vom 20.9. 1993
*/

#include "pheader.h"

#include "komplexr.hr"		   // Resource-IDs

extern "C" {

extern HINSTANCE g_hInstance;

// Die Routine OutputTemplate kopiert eine Dateiresource
// in eine Ausgabedatei (oder String), deren File-Handle gegeben ist. Es wird davon
// ausgegangen, daß die Ausgabedatei eröffnet und richtig positioniert ist.
pchar OutputResourceTemplate (int ResID, int fh) {

	pchar pResource;
	DWORD SRes;
	HRSRC hFindRes;
	pchar pResult = NULL;   //  ErgebnisString

//  Resource laden
	HGLOBAL hRes = LoadResource (g_hInstance, hFindRes = FindResource (g_hInstance,
								 MAKEINTRESOURCE (ResID),
								 MAKEINTRESOURCE (DATEI)));
	if (!hFindRes || !hRes)
		return NULL;

//  Resource im Speicher festhalten
	pResource = (pchar) LockResource (hRes);

	if (pResource) {		// wenn Resource erfolgreich geladen

	//  Resource in Ausgabe-File/String schreiben
		if ((SRes = SizeofResource (g_hInstance, hFindRes)) == 0)
			return NULL;

		if (*(pResource + SRes - 1) == '\0')	// Größe ggf. korrigieren
			SRes = lstrlen (pResource);

		if (fh)	 // wenn FileHandle gegeben
			_lwrite (fh, pResource, (UINT) SRes);
		else {	  // Ausgabe in String
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

} // extern "C"
