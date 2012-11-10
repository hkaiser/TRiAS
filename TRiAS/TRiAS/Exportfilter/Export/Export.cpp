// @doc
// @module ExportApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"
#include "ExportImpl.h"

#include "ExportXTension.h"

#include <initguid.h>
#include <TRiASHelper.h>
#include <TRiASHelper_i.c>

#include "Export_i.c"
#import "MSXML.dll"	no_implementation, named_guids

#if defined(_USE_XML_GEOCOMPONENTS)
DEFINE_GUID(CLSID_SelectFromObjectWindow, 0x0E54C9EAL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
#endif // defined(_USE_XML_GEOCOMPONENTS)

#include <SrChoice.h>
#include <selidprp.h>
#include <SelectExportObjectsGuid.h>

#include "ExportPropertyAction.h"

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ExportXTension, CExportXtension)
	OBJECT_ENTRY(CLSID_ExportPropertyAction, CExportPropertyAction)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

_ATL_OBJMAP_ENTRY *GetObjectMap (void) {
	return ObjectMap;		// liefert ObjectMap
}

BOOL GetTypeLibGUID (GUID &rGuid) {
	rGuid = LIBID_ExportXTension;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbExportProgID[] = _T("TRiAS.Export.1");

#define EXPORT_MAJORVERSION	1
#define	EXPORT_MINORVERSION	0

/////////////////////////////////////////////////////////////////////////////
// Registrierung über ATL-Mechanismus; Stub wird aber noch gebraucht
#define REG_MFC
#if defined(REG_MFC)
BOOL UpdateRegistry (BOOL fRegister) {
	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass(
				_Module.GetModuleInstance()
				, CLSID_ExportXTension
				, g_cbExportProgID
				, IDS_LONGCLASSNAME
				, EXPORT_MAJORVERSION
				, EXPORT_MINORVERSION
				, EFPreLoad )
				)
			return FALSE;
	
	} else {
	// RegDB säubern
		if (!ExtOleUnregisterClass (CLSID_ExportXTension, g_cbExportProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}
#else
BOOL UpdateRegistry (BOOL fRegister) {
	return TRUE;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Lizensierung für Exporterweiterung selbst
#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
BOOL GetLicenseKeyObsolete (LPWSTR pwKey, size_t iLen);
BOOL GetLicensedObsolete (void);
BOOL SetLicensedObsolete (LPCSTR lpNewKey);
#endif // _TRiAS_VER < 0x0400


BOOL GetLicenseKey (LPWSTR pwKey, size_t iLen)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return GetLicenseKeyObsolete(pwKey, iLen);
#endif // _TRiAS_VER < 0x0400

// Lizensierung nicht mehr hier
	return TRUE;
}

BOOL GetLicensed (void)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return GetLicensedObsolete();
#endif // _TRiAS_VER < 0x0400

// Lizensierung nicht mehr hier
	return TRUE;
}

BOOL SetLicensed (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return SetLicensedObsolete(lpNewKey);
#endif // _TRiAS_VER < 0x0400

// Lizensierung nicht mehr hier
	return TRUE;
}

