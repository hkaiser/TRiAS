// Verwaltung von Objektmerkmalen ---------------------------------------------
// File: FEATUREX.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include <initguid.h>		// nur im einem Module notwendig
#include <oprpguid.h>

#include "featguid.h"

#include "version.h"

#include "selidprp.hxx"		// PropertyAction's
#include "clsfyprp.hxx"
#include "selrlprp.hxx"
#include "selobwnd.hxx"
#include "dstobwnd.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// Der ProgID (hier 'TRiAS.Recherche.1') ist eine ZeichenKette, die die Erweiterung
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
				TEXT("TRiAS.Recherche.1"), IDS_LONGCLASSNAME,
				FEATURE_MAJORVERSION, FEATURE_MINORVERSION,
				EFUnLoadable);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_FeatureExtension, 
					      TEXT("TRiAS.Recherche.1"));
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
		   : CTriasExtension (IDR_FEATUREMENU/*, IDR_ORFEATUREMENU*/)
{
	m_pProps = NULL;
}

// Destruktor -----------------------------------------------------------------
CFeatureExtension :: ~CFeatureExtension (void) 
{
	DELETE(m_pProps);
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CFeatureExtension :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	if (riid == IID_IObjectProps) {
		*ppvObj = m_pProps;	// Objekteigenschaften
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return CTriasExtension::QueryInterface (riid, ppvObj);
}


// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen. Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CFeatureExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_OBJWNDCLOSED);

	try {
	// Interface für Objekteigenschaften erzeugen
	ResString resGroupName (ResID (IDS_GROUPNAME, &RF()), 64);

		m_pProps = CObjectProperties::CreateInstance (m_pUnk ? m_pUnk : this,
							      resGroupName);
		if (NULL == m_pProps) return false;

	// Objekteigenschaften installieren
	LPCLASSPROPERTY pProp = CSelIDPropAct::CreateInstance();

		if (NULL != pProp) {
			m_pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
			pProp -> Release();
		}

		pProp = CClsfyPropAct::CreateInstance (m_pXtnSite);
		if (NULL != pProp) {
			m_pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
			pProp -> Release();
		}				

		pProp = CGenKomplexObj::CreateInstance (m_pXtnSite);
		if (NULL != pProp) {
			m_pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
			pProp -> Release();
		}				

		pProp = CSelObjWndPropAct::CreateInstance();
		if (NULL != pProp) {
			m_pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
			pProp -> Release();
		}				

		pProp = CDestObjWndPropAct::CreateInstance();
		if (NULL != pProp) {
			m_pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
			pProp -> Release();
		}				

	} catch (...) {
		TX_ASSERT(/*Catched unhandled exception*/false);
		return false;
	}
		
return true;
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CFeatureExtension :: UnLoadExtension (void)
{
// Objekteigenschaften freigeben
	m_pProps -> RemoveAllClassPropertyFunctions();

// Notifikationen abmelden
	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);

return CTriasExtension :: UnLoadExtension();
}

STDMETHODIMP_(bool) CFeatureExtension :: MenuInit (
			HMENU hMenu, LPARAM lParam, HWND hWnd)
{
// überprüfen, ob unser Menu gefragt ist
	if (hWnd == NULL && hMenu != MenuHandle()) return false;
	if (hWnd != NULL && hMenu != ORMenuHandle()) return false;

return true;
}

// MenuCommands ---------------------------------------------------------------
STDMETHODIMP_(bool) CFeatureExtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	switch (wParam) {
	case ID_RECHERCHE_OBJEKTRELATIONENERZEUGEN:
		return ClassifyORObjects();

	case ID_FEATURE_CLASSIFY:
		return ClassifyObjects();

	case ID_FEATURE_DUPDELETE:
		break;

	default:
		break;
	}

return false;
}

STDMETHODIMP_(LRESULT) CFeatureExtension :: Notification (WPARAM wParam, LPARAM lParam)
{
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

