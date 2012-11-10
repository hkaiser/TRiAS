// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 21:54:21
//
// @doc
// @module QueryDef.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include <TRiASDB_i.c>
#include <selobwnd.h>
#include <AddAsClsPrp.h>
#include <DelFromClsPrp.h>
#include <DstObWnd.h>
#include <triashelper.h>
#include <triashelper_i.c>

#include "QueryDef.h"
#include "QueryDef_i.c"

#include "Version.h"
#include "QueryDefExt.h"
#include "TRiASCollectObjects.h"
#include "RemoveFromObjectClass.h"
#include "UndoRedoAddObjToClass.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_QueryDefExt, CQueryDefExtension)
	OBJECT_ENTRY(CLSID_TRiASCollectObjects, CTRiASCollectObjects)
	OBJECT_ENTRY(CLSID_RemoveFromObjectClass, CRemoveFromObjectClass)
	OBJECT_ENTRY(CLSID_UndoRedoAddObjToClass, CUndoRedoAddObjToClass)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSID's
//extern "C" const CLSID CLSID_ProgressIndicator = {0x07963819,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbQueryDefProgID[] = _T("TRiAS.QueryDef.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_TRiASQueryDef;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_QueryDefExt, g_cbQueryDefProgID, IDS_LONGCLASSNAME,
				QUERYDEF_MAJORVERSION, QUERYDEF_MINORVERSION, EFPreLoad))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_QueryDefExt, g_cbQueryDefProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



