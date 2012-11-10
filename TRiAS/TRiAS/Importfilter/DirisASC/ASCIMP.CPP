// Import aus dem DIRIS-ASC Austaschformat ------------------------------------
// File: ASCIMP.CPP

#include "ascimpp.hpp"

#include "ascimp.h"		// ResourceKonstanten
#include <xtsnguid.h>

#include "version.h"

EXTERN_C const GUID CLSID_ImpAscExtension = {0xED9655C4L, 0x3122, 0x101C, {0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C}};
//EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
//EXTERN_C const IID IID_IImportGeoDataWithResult = {0x261288a3,0xf3df,0x11d1,{0x86,0x2e,0x00,0x60,0x08,0x75,0x13,0x8a}};

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
//CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
//{
//	return new CImpAscExtension();
//}

///////////////////////////////////////////////////////////////////////////////
// ClassFactories
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ImpAscExtension, CImpAscExtension)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// ObjectMap liefern
}


//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_ImpAscExtension, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	BOOL fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_ImpAscExtension, 
				TEXT("TRiAS.AscImport.1"), IDS_LONGCLASSNAME,
				ASCIMP_MAJORVERSION, ASCIMP_MINORVERSION,
				EFUnLoadable|EFCanImport);
		if (!fSuccess) return false;

		return ExtOleRegisterImportClass (g_hInstance,
				CLSID_ImpAscExtension, TEXT("TRiAS.AscImport.1"), 
				IDS_FORMATDESCRIPTION, IDS_DEFAULTEXTENSION);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_ImpAscExtension, 
				TEXT("TRiAS.AscImport.1"));
	}

return true;	// alles ok
}

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CImpAscExtension::CImpAscExtension (void)
{
	m_hWnd = NULL;	
}

// Destruktor -----------------------------------------------------------------
CImpAscExtension::~CImpAscExtension (void) 
{
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) CImpAscExtension::InitExtension (short iMode)
{
	return CTriasExtension::InitExtension (iMode);
}

STDMETHODIMP_(BOOL) CImpAscExtension::UnLoadExtension (void)
{
	return CTriasExtension::UnLoadExtension();
}

