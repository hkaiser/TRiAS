/*
File: RESOURCE.CXX
realiert die Ressourcenverwaltung für den Arc/Info-Filter.

erarbeitet : J. Benkenstein				 Stand vom 30. April 1993
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

//XX#include "triasarc.hr"		   // Resource-IDs

extern "C" {

#define hDLLInst _Module.GetModuleInstance()		 // hInst dieser DLL

// Die Routine OutputTemplate kopiert eine Dateiresource
// in eine Ausgabedatei (oder String), deren File-Handle gegeben ist. Es wird davon
// ausgegangen, daß die Ausgabedatei eröffnet und richtig positioniert ist.
pchar OutputResourceTemplate (uint ResID, int fh) {

	pchar pResource;
	DWORD SRes;
	HRSRC hFindRes;
	pchar pResult = NULL;   //  ErgebnisString

//  Resource laden
	HGLOBAL hRes = LoadResource (hDLLInst, hFindRes = FindResource (hDLLInst,
										   MAKEINTRESOURCE (ResID),
										   MAKEINTRESOURCE (DATEI)));
	if (!hFindRes || !hRes)
		return NULL;

//  Resource im Speicher festhalten
	pResource = (pchar) LockResource (hRes);

	if (pResource) {		// wenn Resource erfolgreich geladen

	//  Resource in Ausgabe-File/String schreiben
		if ((SRes = SizeofResource (hDLLInst, hFindRes)) == 0)
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
