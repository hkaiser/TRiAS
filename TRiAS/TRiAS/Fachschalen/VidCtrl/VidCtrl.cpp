// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.06.2002 16:35:25
//
// @doc
// @module VidCtrlApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include <dtoolbar.h>
#include <ictf.h>

#include "VidCtrl.h"

#include "VidCtrl_i.c"
#include "Toolbar_i.c"

#include "Version.h"
#include "VidCtrlExt.h"
#include "HotSpot.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_VidCtrl, CVidCtrlExtension)
	OBJECT_ENTRY(CLSID_HotSpot, CHotSpot)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
// additional GUID's to define
EXTERN_C const IID IID_ICoordTransformInit = 
	{0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbVidCtrlProgID[] = _T("TRiAS.VidCtrl.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_VidCtrl;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_VidCtrl, g_cbVidCtrlProgID, IDS_LONGCLASSNAME,
				VIDCTRL_MAJORVERSION, VIDCTRL_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;

	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_VidCtrl, g_cbVidCtrlProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}
