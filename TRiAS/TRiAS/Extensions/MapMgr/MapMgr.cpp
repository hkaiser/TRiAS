#include "stdafx.h"

#include <Esnecil.h>

#include "Version.h"
#include "resource.h"
#include "MapMgr.h"
#include "MapImport.h"

#include "ImportDlg.h"
#include "PictHolder.h"
#include <statguid.h>

#include "MapMgr_i.c"

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbMapMgrExtProgID[] = _T("TRiAS.MapMgr.Import.1");

/////////////////////////////////////////////////////////////////////////////
// Das ATL - COM-Modul
//CComModule _Module;

/////////////////////////////////////////////////////////////////////////////
// Das MFC - Application - Objekt

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_MapImport, CMapImport)
	OBJECT_ENTRY(CLSID_PictHolder, CPictHolder)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_MAPMGRLib;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
	CEsnecil esnecil;
	DWORD dwFlags = EFUnLoadable|EFVisible;

		if (esnecil.VerifyOptions(CKIOPTION_RASTERIMPORT))
			dwFlags |= EFPreLoad;

		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_MapImport, g_cbMapMgrExtProgID, IDS_MAPIMPORTCAPTION,
				MAPMGR_MAJORVERSION, MAPMGR_MINORVERSION, dwFlags))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_MapImport, g_cbMapMgrExtProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



