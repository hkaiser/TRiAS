// @doc
// @module PropActSubSeqApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include "PropActSubSeq.h"
#include "PropActSubSeq_i.c"

#include "Version.h"
#include "PropActSubSeqExt.h"
#include "MergeTwoSources.h"
#include "DeleteAttributes.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_PropActSubSeq, CPropActSubSeqExtension)
	OBJECT_ENTRY(CLSID_MergeTwoSources, CMergeTwoSources)
	OBJECT_ENTRY(CLSID_DeleteAttributes, CDeleteAttributes)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbPropActSubSeqProgID[] = _T("TRiAS.PropActSubSeq.1");

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_PropActSubSeq;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)
BOOL UpdateRegistry (BOOL fRegister)	
{
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_PropActSubSeq, g_cbPropActSubSeqProgID, IDS_LONGCLASSNAME,
				PROPACTSUBSEQ_MAJORVERSION, PROPACTSUBSEQ_MINORVERSION, EFUnLoadable|EFVisible))
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_PropActSubSeq, g_cbPropActSubSeqProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}



