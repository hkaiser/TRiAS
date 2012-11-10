/*
Datei: GENSCRPT.CXX

Das Modul stellt ein allgemeines Interface zur Generierung eines DQL-Scriptes
bereit.

Erarbeitet: J. Benkenstein				  Stand vom: 19.10.1993
*/

#include "pheader.h"

extern "C" {
	#include "komplexr.hr"	   // Ressourcen-Defines
}

#include "genscrpt.htp"		 // Klassen-Selektion
#include <commonvu.hxx>
#include <containr.hxx>
#include "genscrpt.hxx"		 // zugeh. Header

//  globale Variablen
DQLScript *pScript = NULL;		  // aktuelles Script-Objekt

//  exteren Variablen
extern ResourceFile *pRF;

//  Konstanten
short MAX_FNAME = 8;

// Fehlerkodes einbauen !
const RoutCode RC_ctDQLSrcipt = (RoutCode) -1;
const RoutCode RC_GenerateDQLScript = (RoutCode) -2;

//  "C"-Funktionen
extern "C" {
BOOL FAR PASCAL __export GenerateDQLScript (
				EnumScriptAction ESA,	   	// durchzuführende Aktion
				short ParamType,			// Parameter-Typ
				void *pParam) {			 	// Parameter
	switch (ESA) {
		case OpenScript: {				  	// Script erzeugen
			DELETE_OBJ (pScript);	   		// alten Script ggf. löschen
			if ((pScript = new DQLScript ((pchar) pParam)) && pScript -> Result ())
				return TRUE;
			else {
				DEX_Error (RC_GenerateDQLScript, EC_NOMEMORY);
				return FALSE;
			}
		}
		case FensterSpec:				   // Fenster-Spezifikation setzen
			return pScript && pScript -> SetSichtSpec ((EnumSichtSpec) ParamType, pParam) ?
																TRUE : FALSE;
		case GebietsSpec:				   // Gebiets-Spezifikation setzen
			return pScript && pScript -> SetGebietsSpec ((EnumGebietsSpec) ParamType, pParam) ?
																TRUE : FALSE;
		case GenerateScript:				// Script erzeugen
		break;
		case ExecuteScript:				 // gen. Script ausführen
		break;
		case GetScript:					 // gen. Script kopieren
		break;
		case DeleteScript:				  // alten Script löschen
			DELETE_OBJ (pScript);
		return TRUE;
		default:
		return FALSE;					   // Aktion ist nicht definiert
	}               
	return FALSE;
}
}   // extern "C"

//  DQLScript -----------------------------------------------------------------
DQLScript :: DQLScript (pchar pComment) {
//  alle Variablen setzen
	_pComment = NULL;
	// pScript = NULL;
	_SichtSpecType = DefaultSicht;
	_GebietSpecType = DefaultGebiet;
	_Result = True;

	if (pComment && *pComment) {	//  Kommentar übernehmen
		if (! (_pComment = new char [lstrlen (pComment) + 1])) {
			DEX_Error (RC_ctDQLSrcipt, EC_NOMEMORY);
			_Result = False;
			return;
		}
		lstrcpy (_pComment, pComment);
		return;
	} else {						// Standard-Kommentar gener.
		if (! pRF) {
			_Result = False;
			DEX_Error (RC_ctDQLSrcipt, EC_SYSERROR);
			return;
		}
		char Buffer [_MAX_PATH] = "";
		char FName [_MAX_FNAME] = "";
		DEX_GetActiveProject (Buffer);
		if (!*Buffer) {
			_Result = False;
			DEX_Error (RC_ctDQLSrcipt, EC_SYSERROR);
			return;
		}
		_splitpath (Buffer, NULL, NULL, FName, NULL);
		if (lstrlen (FName) > MAX_FNAME)			// Länge ggf. begrenzen
			FName [MAX_FNAME] = '\0';
		strupr (FName);

	//  Standard-Text zusammenbauen
		ResString Comment (ResID (IDS_COMMENT, pRF), 80);
		wsprintf (Buffer, Comment, FName);
		if (! (_pComment = new char [lstrlen (Buffer) + 1])) {
			DEX_Error (RC_ctDQLSrcipt, EC_NOMEMORY);
			_Result = False;
			return;
		}
		lstrcpy (_pComment, Buffer);
		return;
	}
}

DQLScript :: ~DQLScript (void) {
	// DELETE_VEC (_pScript);
	DELETE_VEC (_pComment);
}

//  Sicht-Spezifikation setzen
Bool DQLScript :: SetSichtSpec (EnumSichtSpec ESS, void *) {
	switch (ESS) {
		case DefaultSicht: {			// aktuelle Sicht
			_SichtSpecType = DefaultSicht;
			return True;
		}
		case StringSicht: {			 // angegebene Sicht
			_SichtSpecType = StringSicht;
			//  kopiere Sichtname
			return True;
		}
		case IdentList: {			   // Id-Liste
			_SichtSpecType = IdentList;
			return True;
		}
		case SelectedObjects: {		 // selektierte Objekte
			_SichtSpecType = SelectedObjects;
			return True;
		}
		case SingleObject: {			// über Objekt-Nummer gegebenes Objekt
			_SichtSpecType = SingleObject;
			return True;
		}
		default:						// unbekannter Parameter-Typ
			return False;
	}
}

Bool DQLScript :: SetGebietsSpec (EnumGebietsSpec EGS, void *) {
	switch (EGS) {
		case DefaultGebiet: {			// aktuell sel. Fenster
			_GebietSpecType = DefaultGebiet;
			return True;
		}
		case ActualUmkreis: {			 // akt. sel. Umkreis
			_GebietSpecType = ActualUmkreis;
			return True;
		}
		case ActualBuffer: {			   // akt. Puffer
			_GebietSpecType = ActualBuffer;
			return True;
		}
		default:						// unbekannter Parameter-Typ
			return False;
	}
}

