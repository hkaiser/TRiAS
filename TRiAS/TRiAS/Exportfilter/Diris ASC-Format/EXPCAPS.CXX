// Funktion, die Eigenschaften des Export-Filters liefert ---------------------
// File: EXPCAPS.CXX

#include "stdafx.h"
//XX	#include "dirisexp.hxx"
#include "DirisASCImpl.h"

//XX	extern "C" 
//XX	short EXPORTFLT PASCAL DirisAscGetExportCaps (ExportCapability CapIndex) 
/*XX*/	short GetExportCaps (ExportCapability CapIndex) 
{
	switch (CapIndex) {
	case EC_Merkmale:	
		return SHRT_MAX;	// keine Begrenzung der Merkmalsanzahl

	case EC_Relationen:
		return TRUE;		// kann Relationen behandlen

//	case EC_NoConvertCoords:
//		return true;		// Koordinaten nur auf 'alte' Weise konvertieren

	default:
		return FALSE;
	}
}
