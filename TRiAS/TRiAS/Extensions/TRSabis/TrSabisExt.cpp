// Zusätzliche COM-Objekte für Sachdatenkopplung
// File: TRSABISEXT.CPP

#include "StdAfx.h"

#include "resource.h"		// ResourceKonstanten
#include "version.h"

#include "TrSabis.h"
#include "TrSabisExt.h"

#include "SabisChildWindow.h"
#include "SabisTabChildWindow.h"

#include <initguid.h>		// nur im einem Module notwendig
#include "TrSabis_i.c"
#include "DummyUIOwner.h"
#include "MkSABiSTabChildWindow.h"
#include "SABiSTabChildWindowCallback.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// NEU: An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die 
// Erweiterung jetzt in der ATL ObjectMap eingetragen werden (zusammen 
// mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TRiASSabis, CTRiASSabisExt)
	OBJECT_ENTRY(CLSID_SabisChildWindow, CSabisChildWindow)
	OBJECT_ENTRY(CLSID_SabisTabChildWindow, CSabisTabChildWindow)
	OBJECT_ENTRY(CLSID_DummyUIOwner, CDummyUIOwner)
	OBJECT_ENTRY(CLSID_MkSabisTabChildWindow, CMkSABiSTabChildWindow)
	OBJECT_ENTRY(CLSID_SabisTabChildWindowCallback, CSABiSTabChildWindowCallback)
END_OBJECT_MAP()

// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus
// dieser Erweiterung eingebunden
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

///////////////////////////////////////////////////////////////////////////////
// Registrierung/DeRegistrierung
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_TRiASSabis, 
				TEXT("TRiAS.TRiASSabis.1"), IDS_LONGCLASSNAME,
				TRIASSABIS_MAJORVERSION, TRIASSABIS_MINORVERSION,
				EFPriorityLoad2);		// darf erst entladen werden, wenn alle 
										// SABiS-Erweiterungen weg sind
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_TRiASSabis, 
					      TEXT("TRiAS.TRiASSabis.1"));
	}
	return true;	// alles ok
}


// Konstruktor der ExtensionKlasse --------------------------------------------
CTRiASSabisExt::CTRiASSabisExt (void)
{
}

STDMETHODIMP_(BOOL) CTRiASSabisExt::InitExtension (short iMode) 
{
	if (!CTriasExtension::InitExtension(iMode))
		return false;

// TabFenster in TRiAS instantiieren
	return SUCCEEDED(CSabisTabChildWindow::RegisterTabWindows());
}

STDMETHODIMP_(BOOL) CTRiASSabisExt::UnLoadExtension (void)
{
	return CTriasExtension::UnLoadExtension();
}

