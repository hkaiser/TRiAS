// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:14:00
//
// @doc
// @module SegmentApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"


#include <tstring>
#include <Registrx.hxx>

#include <ipropseq.hxx>

#include <xtsnguid.h>

#include <SrChoice.h>
#include <selidprp.h>

#include <TRiASHelper.h>

#include <initguid.h>
#include "Segment.h"
#include "Segment_i.c"

#include "segguids.h"

#include "Version.h"
#include "SegmentExt.h"
#include "Strecken.h"

//#include <com/Errormacros2Impl.cpp>
//#include <Com/PropertyActionBase.cpp>

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Segment, CSegmentExtension)
	OBJECT_ENTRY(CLSID_Strecken, CStrecken)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbSegmentProgID[] = _T("TRiAS.Segment.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_Segment;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_Segment, g_cbSegmentProgID, IDS_LONGCLASSNAME,
				SEGMENT_MAJORVERSION, SEGMENT_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_Segment, g_cbSegmentProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



