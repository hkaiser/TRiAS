// Funktion, die Eigenschaften des Export-Filters liefert
// File: ATLASCAP.CXX

#include "stdafx.h"

extern "C"
short EXPORTFLT PASCAL AtlasBnaGetExportCaps (ExportCapability CapIndex) 
{
	switch (CapIndex) {
	case EC_Merkmale:	
		return 1;		// lediglich 1 Merkmal möglich

	case EC_NoConvertCoords:
		return true;	// Koordinaten nur auf 'alte' Weise konvertieren

	default:
		return FALSE;
	}
}
