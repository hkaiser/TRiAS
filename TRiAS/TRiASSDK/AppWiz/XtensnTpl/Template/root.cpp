// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$
//
// @doc
// @module $$root$$App.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include "$$root$$.h"
#include "$$root$$_i.c"

#include "Version.h"
#include "$$root$$Ext.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_$$safe_root$$, C$$safe_root$$Extension)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cb$$safe_root$$ProgID[] = _T("TRiAS.$$safe_root$$.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_$$root$$;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_$$safe_root$$, g_cb$$safe_root$$ProgID, IDS_LONGCLASSNAME,
				$$SAFE_ROOT$$_MAJORVERSION, $$SAFE_ROOT$$_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_$$safe_root$$, g_cb$$safe_root$$ProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



