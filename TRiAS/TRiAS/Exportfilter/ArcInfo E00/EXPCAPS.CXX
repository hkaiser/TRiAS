// Funktion, die Eigenschaften des Export-Filters liefert
// File: EXPCAPS.CXX							Stand vom 30. April 1993

#include "stdafx.h"               

extern "C" {
		#include <limits.h>
}

#include <attribs.hxx>
#include <impexp.hxx>

// Prototypen
short GetExportCaps (ExportCapability CapIndex);

short GetExportCaps (ExportCapability CapIndex)
{
	switch (CapIndex) {
		case EC_Merkmale:
			return SHRT_MAX;			// Merkmals-Bearbeitung
		case EC_MerkmalDescription:
			return TRUE;				// Merkmals-Beschreibung

		case EC_IdentDescription:
			return TRUE;				// bearbeite ID-Beschreibung

		case EC_Relationen:
				return FALSE;		   // Relationen werden nicht unterstützt
		default:
				return FALSE;		   // sonstige auch nicht
	}		   
}

extern "C" {

// AutoCAD-Export
short EXPORTFLT PASCAL ArcInfoGetExportCaps (ExportCapability CapIndex)
{
	return GetExportCaps (CapIndex);
}

}	   // extern "C"
