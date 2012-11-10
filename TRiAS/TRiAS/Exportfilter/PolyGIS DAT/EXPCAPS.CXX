// Funktion, die Eigenschaften des Export-Filters liefert ---------------------
// File: EXPCAPS.CXX

#include "stdafx.h"
#include "PolygisDatImpl.h"

//XX	extern "C" 
//XX	short EXPORTFLT PASCAL PolygisDatGetExportCaps (ExportCapability CapIndex) 
/*XX*/	short GetExportCaps (ExportCapability CapIndex) 
{
	switch (CapIndex) {
	case EC_Merkmale:	
		return SHRT_MAX;	// keine Begrenzung der Merkmalsanzahl

	case EC_Relationen:
		return TRUE;		// kann Relationen behandlen


	default:
		return FALSE;
	}
}
