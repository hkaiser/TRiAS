// Import aus dem DIRIS-ASC Austaschformat ------------------------------------
// File: SIMPLE.CXX

#include "simplep.hxx"
#include "simple.h"		// ResourceKonstanten

#include <initguid.h>		// nur im einem Module notwendig
#include "simpguid.h"

#include "version.h"

#include "simple.hxx"		// die Erweiterung selbst


///////////////////////////////////////////////////////////////////////////////
// NEU: An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die 
// Erweiterung jetzt in der ATL ObjectMap eingetragen werden (zusammen 
// mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_SimpleExtension, CSimpleExtension)
// hier evtl. andere Objekte eintragen
// ...
END_OBJECT_MAP()

// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus
// dieser Erweiterung eingebunden
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

///////////////////////////////////////////////////////////////////////////////
// Alles weitere bleibt beim alten
// ...
//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Simple.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_SimpleExtension, 
				TEXT("TRiAS.Simple.1"), IDS_LONGCLASSNAME,
				SIMPLE_MAJORVERSION, SIMPLE_MINORVERSION,
				EFUnLoadable|EFVisible);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_SimpleExtension, 
					      TEXT("TRiAS.Simple.1"));
	}

return true;	// alles ok
}


// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden. Die Destruktoren sind 'virtual', so daß auch so
// alles sauber aufgeräumt werden kann.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CSimpleExtension :: CSimpleExtension (void)
		  : CTriasExtension (IDR_SIMPLEMENU, IDR_SIMPLEORMENU)
{
	// nothing else to do
}

STDMETHODIMP_(bool) CSimpleExtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	switch (wParam) {
	case ID_SIMPLE_BEEP:
		MessageBeep(NULL != hWnd ? MB_ICONASTERISK : MB_ICONHAND);
		return true;

	case ID_SIMPLE_ABOUT:
		break;
	}

return false;
}

