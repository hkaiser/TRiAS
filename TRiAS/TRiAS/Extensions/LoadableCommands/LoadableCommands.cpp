// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 12.11.2004 11:41:37
//
// @doc
// @module LoadableCommandsApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include "LoadableCommands.h"
#include "LoadableCommands_i.c"

#include "Version.h"
#include "LoadableCommandsExt.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_LoadableCommands, CLoadableCommandsExtension)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbLoadableCommandsProgID[] = _T("TRiAS.LoadableCommands.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_LoadableCommands;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_LoadableCommands, g_cbLoadableCommandsProgID, IDS_LONGCLASSNAME,
				LOADABLECOMMANDS_MAJORVERSION, LOADABLECOMMANDS_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_LoadableCommands, g_cbLoadableCommandsProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



