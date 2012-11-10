// Verwaltung von Objektmerkmalen ---------------------------------------------
// File: FEATURE.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include <initguid.h>		// nur im einem Module notwendig
#include "featguid.h"

#include "version.h"

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
{
	return new CFeatureExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_FeatureExtension, sizeof (GUID));
	return true;
}

//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Features.1') ist eine ZeichenKette, die die Erweiterung
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
				CLSID_FeatureExtension, 
				TEXT("TRiAS.Features.1"), IDS_LONGCLASSNAME,
				FEATURE_MAJORVERSION, FEATURE_MINORVERSION,
				EFUnLoadable);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_FeatureExtension, 
					      TEXT("TRiAS.Features.1"));
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
CFeatureExtension :: CFeatureExtension (void)
		   : CTriasExtension (IDR_FEATUREMENU)
{
	// nothing to do
}

// Destruktor -----------------------------------------------------------------
CFeatureExtension :: ~CFeatureExtension (void) 
{
	// nothing to do
}


// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen. Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CFeatureExtension :: InitExtension (short iMode)
{
	return CTriasExtension :: InitExtension (iMode);
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CFeatureExtension :: UnLoadExtension (void)
{
	return CTriasExtension :: UnLoadExtension();
}


STDMETHODIMP_(bool) CFeatureExtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	switch (wParam) {
	case ID_FEATURE_DUPLICATE:
		return FindDupFeatures();

	default:
		break;
	}

return false;
}

STDMETHODIMP_(LRESULT) CFeatureExtension :: Notification (WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case DEX_QUERYRECHOBJECT:
		{
		// untersuchtes Merkmale anzeigen
                RECHOBJECT *pRO = (RECHOBJECT *)lParam;
		char cbBuffer[_MAX_PATH];
		
			if (ReadTextMerkmal (TT_Objekt, pRO -> lONr, m_lMCode, cbBuffer, _MAX_PATH)) {
				strncpy (pRO -> lpText, cbBuffer, pRO -> iTextLen);
				pRO -> lpText[pRO -> iTextLen-1] = '\0';
			}
		}
		break;

	default:
		break;
	}
	
return false; // immer weiterleiten
}

bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen)
{
TARGETMERKMAL gm;

        gm.dwSize = sizeof(TARGETMERKMAL);
        gm.lTarget = (LPARAM)lTarget;
        gm.lMCode = lMCode;
        gm.imaxLen = pText != NULL ? iLen : 0;
        gm.pMText = pText;
        gm.iTTyp = iTTyp;
        if (DEX_GetTextMerkmal (gm) == NULL)
                return false;

return true;
}
