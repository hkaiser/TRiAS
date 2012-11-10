// Funktion, die Eigenschaften des Export-Filters liefert
// File: POLYGISCAP.CXX

#include "stdafx.h"

extern "C"
short EXPORTFLT PASCAL PolygisPMFGetExportCaps (ExportCapability CapIndex) 
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
