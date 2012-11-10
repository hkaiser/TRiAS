// Funktion, die Eigenschaften des Export-Filters liefert
// File: EXPCAPS.CXX				Stand vom 19. November 1992

#include "pheader.h"

#include <attribs.hxx>
#include <impexp.hxx>
#include "caddyasc.hxx"		

extern "C" {

short EXPORTFLT PASCAL CadAscGetExportCaps (ExportCapability CapIndex) {

    switch (CapIndex) {
	case EC_Merkmale:
	    return TRUE;		// Merkmals-Bearbeitung
	case EC_MerkmalDescription:
	    return FALSE;		// keine Merkmals-Beschreibung

	case EC_IdentDescription:
	    return TRUE;		// bearbeite ID-Beschreibung

	case EC_Relationen:
		return FALSE;		// Relationen werden nicht unterstützt
	default:
		return FALSE;		// sonstige auch nicht
    }
}

}	// extern "C"
