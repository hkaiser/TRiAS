// @doc
// @module MemDiffExtApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include "MemDiffExt.h"
#include "MemDiffExt_i.c"

#include "Version.h"
#include "MemDiffExtExt.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_MemDiffExt, CMemDiffExtExtension)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbMemDiffExtProgID[] = _T("TRiAS.MemDiffExt.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_MemDiffExt;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_MemDiffExt, g_cbMemDiffExtProgID, IDS_LONGCLASSNAME,
				MEMDIFFEXT_MAJORVERSION, MEMDIFFEXT_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_MemDiffExt, g_cbMemDiffExtProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



