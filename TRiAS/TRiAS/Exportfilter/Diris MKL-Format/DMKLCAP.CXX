// Funktion, die Eigenschaften des Export-Filters liefert ---------------------
// File: DMKLCAP.CXX

#include "merkmp.hxx"

#include <limits.h>

extern "C" 
short EXPORTFLT PASCAL DirisMKLGetExportCaps (ExportCapability CapIndex) 
{
	switch (CapIndex) {
	case EC_Merkmale:	
		return SHRT_MAX;	// alle Merkmale

	default:
		return FALSE;
	}
}
