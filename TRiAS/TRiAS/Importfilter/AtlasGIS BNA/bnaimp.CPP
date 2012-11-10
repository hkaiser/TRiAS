// Import aus dem PolyGIS-BNA Format ------------------------------------
// File: BNAIMP.CPP

#include "bnaimpp.hpp"

#include "bnaimp.h"
#include "bnaimp_i.c"

#include <xtsnguid.h>
#include <Esnecil.h>

#include "bnapars.h"
#include "version.h"

#include "BNAImportConfig.h"

//#include "bnaimpif.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// ClassFactories
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ImpBnaExtension, CImpBnaExtension)
	OBJECT_ENTRY(CLSID_ImpDatExtension, CImpBnaExtension)
	OBJECT_ENTRY(CLSID_BNAImportConfig, CBNAImportConfig)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// ObjectMap liefern
}

///////////////////////////////////////////////////////////////////////////////
// spezielle RegistryEintäge für GCO Produktion
/*static*/
HRESULT WINAPI CImpBnaExtension::UpdateRegistry(BOOL bRegister)
{
CEsnecil esnecil;
HRESULT hr = S_OK;

    if (!bRegister || esnecil.VerifyOptions(CKIOPTION_GCOPRODUCTION)) {
	    hr = _Module.UpdateRegistryFromResource(IDR_POLYGISFEATURE_REG, bRegister);
		if (SUCCEEDED(hr))
			hr = _Module.UpdateRegistryFromResource(IDR_DATIMPORTCONFIG_REG, bRegister);
	}
    return hr;
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_ImpBnaExtension, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	BOOL fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_ImpBnaExtension, 
				TEXT("TRiAS.AtlasGisBNAImport.1"), IDS_LONGCLASSNAME,
				BNAIMP_MAJORVERSION, BNAIMP_MINORVERSION,
				EFUnLoadable|EFCanImport);
		if (!fSuccess) return false;

		fSuccess =  ExtOleRegisterImportClass (g_hInstance,
				CLSID_ImpBnaExtension, TEXT("TRiAS.AtlasGisBNAImport.1"), 
				IDS_FORMATDESCRIPTION, IDS_DEFAULTEXTENSION);
		if (!fSuccess) return false;

	// PolyGIS DAT nur registrieren, wenn GCO Produktion aktiv ist
	CEsnecil esnecil;

		if (esnecil.VerifyOptions(CKIOPTION_GCOPRODUCTION)) {
			fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
					CLSID_ImpDatExtension, 
					TEXT("TRiAS.PolygisDATImport.1"), IDS_NEXTCLASSNAME,
					BNAIMP_MAJORVERSION, BNAIMP_MINORVERSION,
					EFUnLoadable|EFCanImport);
			if (!fSuccess) return false;

			fSuccess = ExtOleRegisterImportClass (g_hInstance,
				CLSID_ImpDatExtension, TEXT("TRiAS.PolygisDATImport.1"), 
				IDS_NEXTFORMAT, IDS_NEXTEXTENSION);
		}
		return fSuccess;
	} 
	else {
	// RegDB säubern
		ExtOleUnregisterClass (CLSID_ImpBnaExtension, 
				TEXT("TRiAS.PolygisBNAImport.1"));

		ExtOleUnregisterClass (CLSID_ImpBnaExtension, 
				TEXT("TRiAS.AtlasGisBNAImport.1"));

		ExtOleUnregisterClass (CLSID_ImpBnaExtension, 
				TEXT("TRiAS.PolygisDATImport.1"));
	}
	return true;	// alles ok
}

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CImpBnaExtension::CImpBnaExtension (void)
{
	m_dwFlags = 0;
}

// Destruktor -----------------------------------------------------------------
CImpBnaExtension::~CImpBnaExtension (void) 
{
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) CImpBnaExtension::InitExtension (short iMode)
{
	return CTriasExtension::InitExtension (iMode);
}

STDMETHODIMP_(BOOL) CImpBnaExtension::UnLoadExtension (void)
{
	return CTriasExtension::UnLoadExtension();
}

