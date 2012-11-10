// @doc
// @module ExportApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include "ExportApp.h"
#include "ExportApp_i.c"

#include <SrChoice.h>
#include <selidprp.h>
#include <SelectExportObjectsGuid.h>

#include "Version.h"
#include "Export.h"
#include "ExportPropertyAction.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Export, CExport)
	OBJECT_ENTRY(CLSID_ExportPropertyAction, CExportPropertyAction)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbExportProgID[] = _T("TRiAS.Export.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_Export;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_Export, g_cbExportProgID, IDS_LONGCLASSNAME,
				EXPORT_MAJORVERSION, EXPORT_MINORVERSION, EFPreLoad))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_Export, g_cbExportProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}


