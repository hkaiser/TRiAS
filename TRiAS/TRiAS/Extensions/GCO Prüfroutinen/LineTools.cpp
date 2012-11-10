// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.11.2002 09:25:38
//
// @doc
// @module LineToolsApp.cpp | Implementation of exports for a TRiAS extension module.

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
#include "LineTools.h"
#include "LineTools_i.c"


#include "relkey.h"

//#include "codeguids.h"

#include "Version.h"
#include "LineToolsExt.h"
#include "CodeCheck.h"
#include "CCodeStat.h"
#include "CodeLine.h"
#include "ClsfyByCode.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_LineTools, CLineToolsExtension)
	OBJECT_ENTRY(CLSID_CodeCheck, CCodeCheck)
	OBJECT_ENTRY(CLSID_CCodeStat, CCCodeStat)
	OBJECT_ENTRY(CLSID_CodeLine, CCodeLine)
	OBJECT_ENTRY(CLSID_ClsfyByCode, CClsfyByCode)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbLineToolsProgID[] = _T("TRiAS.LineTools.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_LineTools;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_LineTools, g_cbLineToolsProgID, IDS_LONGCLASSNAME,
				LINETOOLS_MAJORVERSION, LINETOOLS_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_LineTools, g_cbLineToolsProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



