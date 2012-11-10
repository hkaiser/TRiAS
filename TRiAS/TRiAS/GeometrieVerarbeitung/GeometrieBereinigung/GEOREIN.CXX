// Funktionen für Erweiterungs-DLL "Geometriebereinigung"
// File: GEOREIN.CXX
// W. Mörtl


#include "GeoReinP.hxx"

#include <limits.h>		// ULONG_MAX
#include <resstrg.h>    // IDS_UIFORMAT

#include "GeomDLL.hxx"	// InitGeometrie
#include "GeometrR.h"	// IDS_GEOERROR, ...
#include "datbank.hxx"	// WriteFeatureText()

#include "GeoReinR.h"	// IDS_LONGCLASSNAME

#include "SelbInzi.hxx"	// SelbstInzi
#include "pa.hxx"		// PolygonApproximation()

#include <initguid.h>	// nur in einem Modul für Linken (*guid.h, CLSID_*) notwendig
#include "version.h"	// GEOREIN_MAJORVERSION, ...
#include "georein.hxx"	// GeoReinExtension


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern UINT __DexNotify;
extern UINT __DexCmd;
extern char g_pDLLName [_MAX_PATH];
    


///////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY(CLSID_GeometrieBereinigung, GeoReinExtension)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Bereinigung.1') ist eine Zeichenkette, die die Erweiterung in der
// RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die
// VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine normal-lesbare
// Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die Bezeichnung der
// Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)
	{
	// RegDB initialisieren ...
	bool bRet = ExtOleRegisterExtensionClass (g_hInstance, CLSID_GeometrieBereinigung,
											  TEXT("TRiAS.Bereinigung.1"), IDS_LONGCLASSNAME,
											  GEOREIN_MAJORVERSION, GEOREIN_MINORVERSION, 
											  EFPreLoad|EFPriorityLoad);

	// ... durch Eintrag des Schlüssels "GeoRein", der anzeigt, ob die Geometriefehler,
	// die eigentlich mit gutem Gewissen nicht automatisch bereinigt werden können,
	// doch zwangsweise bereinigt werden sollen (default: ja, d.h. alle Bits setzen)
	// Bit 0: Selbstinzidenz
	// Bit 1: Konturinzidenz
	// Bit 2: Insel außerhalb der Außenkontur
	// Bit 3: Insel innerhalb einer anderen Insel
	// Bit 4: Entartung
	// Bit 5: ungültige Koordinaten

	// ... durch Eintrag der Schlüssel DoppelPunkt, SpitzenWinkel bzw. Schleife, die anzeigen,
	// mit welcher Genauigkeit auf "doppelte Punkte", "Spitzen" bzw. "Schleifen" getestet werden soll
	// (default: dDopEps, dSpiEps bzw. iLoopLen)

	// ... durch Eintrag des Schlüssels PolyApprox, der anzeigt, ob bei der Abspeicherung
	// eines Geometrieobjektes in die TRiAS-Datenbank eine Polygonapproximation
	// durchgeführt werden soll (default: nein, d.h. 0)
	// der eingetragene Wert (0 ... 100) ist ein Maß für die Reduzierung der Stützpunktanzahl

	ResourceFile RF (g_pDLLName);
	ResString ErrClean (ResID (IDS_ERRCLEAN, &RF), 30);		// für Schlüssel "GeoRein"
	ResString AutoClear (ResID (IDS_AUTOCLEAR, &RF), 30);	// für Schlüssel "AutoClear"	
	ResString PolyApprox (ResID (IDS_POLYAPPROX, &RF), 30);	
	CCurrentUser cuExtConfig (RegistryExtPathRein, true);	// Software\\...\\TRiAS\\Extensions\\TRiAS.Bereinigung.1\\Config
	DWORD dwWert1 = 0x3F;					// default-Wert des Schlüssels "GeoRein"
	DWORD dwWert2 = bClear;					// default-Wert des Schlüssels "AutoClear"
	DWORD dwWert3 = DtoL (10. * dDopEps);	// default-Wert des Schlüssels "DoppelPunkt"
	DWORD dwWert4 = DtoL (10. * dSpiEps);	// default-Wert des Schlüssels "Spitze"
	DWORD dwWert5 = iLoopLen;				// default-Wert des Schlüssels "Schleife"
	DWORD dwWert6 = DtoL (100. * dRedEps);	// default-Wert des Schlüssels "PolyApprox"

		// wenn Schlüssel "GeoRein" bisher noch nicht in der RegDB existiert, dann diesen
		// Schlüssel anlegen und alle Bits setzen
		if (!cuExtConfig.GetDWORD (ErrClean.Addr(), dwWert1))
			cuExtConfig.SetDWORD (ErrClean.Addr(), dwWert1);

		// wenn Schlüssel "AutoClear" bisher noch nicht in der RegDB existiert, dann diesen
		// Schlüssel anlegen und auf bClear setzen
		if (!cuExtConfig.GetDWORD (AutoClear.Addr(), dwWert2))
			cuExtConfig.SetDWORD (AutoClear.Addr(), dwWert2);

		// wenn Schlüssel "DoppelPunkt" bisher noch nicht in der RegDB existiert, dann diesen
		// Schlüssel anlegen und auf 10*dDopEps setzen (um eine Kommastelle zu ermöglichen)
		if (!cuExtConfig.GetDWORD (RegDoppelPunkt, dwWert3))
			cuExtConfig.SetDWORD (RegDoppelPunkt, dwWert3);

		// wenn Schlüssel "SpitzenWinkel" bisher noch nicht in der RegDB existiert, dann diesen
		// Schlüssel anlegen und auf 10*dSpiEps setzen (um eine Kommastelle zu ermöglichen)
		if (!cuExtConfig.GetDWORD (RegSpitzenWinkel, dwWert4))
			cuExtConfig.SetDWORD (RegSpitzenWinkel, dwWert4);

		// wenn Schlüssel "Schleife" bisher noch nicht in der RegDB existiert, dann diesen
		// Schlüssel anlegen und auf iLoopLen setzen
		if (!cuExtConfig.GetDWORD (RegSchleife, dwWert5))
			cuExtConfig.SetDWORD (RegSchleife, dwWert5);

		// wenn Schlüssel "PolyApprox" bisher noch nicht in der RegDB existiert, dann
		// diesen Schlüssel anlegen und auf 100*dRedEps setzen (um zwei Kommastelle zu
		// ermöglichen)
		if (!cuExtConfig.GetDWORD (PolyApprox.Addr(), dwWert6))
			cuExtConfig.SetDWORD (PolyApprox.Addr(), dwWert6);

#if _TRiAS_VER < 0x0300
	// alte Schlüsselbezeichnungen in Software\\...\\TRiAS\\Config löschen
	ResString RegistryPfad (ResID (IDS_REGPFAD, &RF), 100);
	CCurrentUser cuConfig (RegistryPfad.Addr(), true);	// Software\\...\\TRiAS\\Config

		cuConfig.DeleteValue (ErrClean.Addr());
		cuConfig.DeleteValue (PolyApprox.Addr());
#endif // _TRiAS_VER < 0x0300

		return bRet;
	}
	else
		// RegDB säubern
		// die eigenen Einträge müßten hier wieder gelöscht werden !!!
		return ExtOleUnregisterClass (CLSID_GeometrieBereinigung, TEXT("TRiAS.Bereinigung.1"));

	return true;	// alles ok
}



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
ResourceFile* pRF = NULL;
bool bMess;		// Flag für Ausgabe im DebugWindow (wird in InitExtension gesetzt)

             


///////////////////////////////////////////////////////////////////////////////////////////////
int ErrHandler (int iWC, int iRoutine, ...);



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet, welche wiederum als
// einzigen Parameter den ResID des im Hauptfenster einzuhängenden Menüs übergeben bekommt.
GeoReinExtension :: GeoReinExtension (void)
				  : CTriasExtension()
{
	// Member initialisieren
	m_pCT = NULL;
	m_ulMCodeGeoErr = (ulong)-1;	// MerkmalsCode für Geometriefehler
	m_ulMCodeGeoClear = (ulong)-1;	// MerkmalsCode für bereinigten Geometriefehler
	m_ulMCodeInterSect = (ulong)-1;	// MerkmalsCode für Verschnitt
	m_lSem = -1L;
	m_bAnzeige = false;				// Anzeige bei KoOrd-Koordinaten noch nicht erfolgt
}


// --------------------------------------------------------------------------------------------
// Destruktor
GeoReinExtension :: ~GeoReinExtension (void) 
{
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

// --------------------------------------------------------------------------------------------
// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung
// durch TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(BOOL) GeoReinExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	
	RegisterNotification (__DexCmd, false); // Windows-Message
	pRF = &RF();
	
	_ASSERTE (pRF != NULL);

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_REIN, ErrHandler, &m_oldEH);

	// TRiAS-Messages (nur 1 Parameter) anfordern
	RegisterNotification (DEX_PROJECTOPEN);	// registriere Benachrichtigung zu Projektöffnung
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_RESCALE);
	RegisterNotification (DEX_HEADERREREAD);
	RegisterNotification (DEX_N_SAVECOMPLETED);

	m_iMode = iMode;
	InitAndOPEN (iMode);

	return true;
} // InitExtension


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) GeoReinExtension :: UnLoadExtension (void)
{
// Interface's wieder freigeben
	m_wTopoRel.Assign (NULL);	// TopoRel freigeben

// TRiAS-Messages wieder abmelden
	UnRegisterNotification (DEX_N_SAVECOMPLETED);
	UnRegisterNotification (DEX_HEADERREREAD);
	UnRegisterNotification (DEX_RESCALE);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);
	
	UnRegisterNotification (__DexCmd, false);

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_REIN, m_oldEH, NULL);

	// restliche Abmeldungen
	UnLoadAndCLOSE();

	// die einstellbaren Parameter in die Registry-DB wegschreiben
	AdjustValuesToRegistry();

	return CTriasExtension :: UnLoadExtension();
} // UnLoadExtension


// --------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen
STDMETHODIMP_(LRESULT) GeoReinExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg)
	{
		case DEX_PROJECTOPEN:	// Projekt wird geöffnet
			InitAndOPEN (m_iMode);
			break;
        
		case DEX_PROJECTCLOSE:
			UnLoadAndCLOSE();
			break;

		case DEX_N_SAVECOMPLETED:
		case DEX_RESCALE:
		case DEX_HEADERREREAD:
			DELETE_OBJ (m_pCT);
			m_pCT = new CoordTransX();
			if (! m_pCT) 
				DEX_Error (RC_georein, EC_NOMEMORY);
			m_bMetric = m_pCT->isMetric();
			break;

		default:		// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension :: Notification (iMsg, p);

} // Notification


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(LRESULT) GeoReinExtension :: WindowsNotification (UINT wMsg, WPARAM wParam,
																LPARAM lParam)
{
	if (wParam != DEX_MODIFYOBJGEOMETRIE)	// nur Reaktion, wenn Objekt eingespeichert werden soll	 
		return false;						// Meldung wird nicht bearbeitet

	if (piInterlockedIncrement (&m_lSem) > 0)
	{
		piInterlockedDecrement (&m_lSem);
		return false;		// nicht mehrfach aufrufen
	}

OBJGEOMETRIE *pOG = (OBJGEOMETRIE *)lParam;
IUnknown *pICS = NULL;

	if (sizeof(GEOMETRIEWITHCS) == pOG->dwSize)
	{
		pICS = ((GEOMETRIEWITHCS *)lParam) -> pICS;
		pOG = ((GEOMETRIEWITHCS *)lParam) -> pOG;
	}

int iFlags = pOG->iFlags;	// Flags des zu testenden Objektes

	if (iFlags & OGGeometryIsChecked)	// Geometrie ist schon (mit der KurzAnalyse) getestet,
	{									//  deshalb keine weitere Testung
		iFlags &= ~OGGeometryIsChecked;	// OGGeometryIsChecked zurücksetzen
		piInterlockedDecrement (&m_lSem);
		return false;
	}

	GeometrieCheck (pOG, pICS);
	piInterlockedDecrement (&m_lSem);

	return false;
} // WindowsNotification


// --------------------------------------------------------------------------------------------
// Aktionen, die bei InitExtension und DEX_PROJECTOPEN gleich sind
bool GeoReinExtension :: InitAndOPEN (int iMode)
{
	m_ulMCodeGeoErr = ULONG_MAX;	// MerkmalsCode für Geometriefehler
	m_ulMCodeGeoClear = ULONG_MAX;	// MerkmalsCode für bereinigten Geometriefehler
	m_ulMCodeInterSect = ULONG_MAX;	// MerkmalsCode für Verschnitt

// CoordTransX anlegen
	if (DEX_TestActiveProject())    // ein Projekt ist schon geöffnet
	{
		DELETE_OBJ (m_pCT);		// vorsichtshalber löschen
		m_pCT = new CoordTransX();	// KoordinatenTransformation
		if (! m_pCT)				// (nur einmal für jedes Projekt anlegen)
		{                                                                      
			DEX_Error (RC_georein, EC_NOMEMORY);
			return false;
		}
		m_bMetric = m_pCT->isMetric();
	}

// Abfrage in der RegDB,
// ... mit welcher Genauigkeit auf "doppelte Punkte", "Spitzen" und "Schleifen" getestet werden soll
// ... ob eine Polygonapproximation durchgeführt werden soll
ResString AutoClear (ResID (IDS_AUTOCLEAR, pRF), 30);	
ResString PolyApprox (ResID (IDS_POLYAPPROX, pRF), 30);	
CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathRein);
DWORD dwWert1, dwWert2, dwWert3, dwWert4, dwWert5;

	if (cuExtConfig.GetDWORD (AutoClear.Addr(), dwWert1))
		m_bClear = dwWert1;
	else
		m_bClear = bClear;

	if (cuExtConfig.GetDWORD (RegDoppelPunkt, dwWert2))
		m_dDPEps = dwWert2 / 10.;
	else
		m_dDPEps = dDopEps;

	if (cuExtConfig.GetDWORD (RegSpitzenWinkel, dwWert3))
		m_dSpEps = dwWert3 / 10.;
	else
		m_dSpEps = dSpiEps;

	if (cuExtConfig.GetDWORD (RegSchleife, dwWert4))
		m_iLoopLen = dwWert4;
	else
		m_iLoopLen = iLoopLen;

	if (cuExtConfig.GetDWORD (PolyApprox.Addr(), dwWert5))
		m_dReduz = dwWert5 / 100.;
	else
		m_dReduz = dRedEps;

	return true;

} // InitAndOPEN


// --------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void GeoReinExtension :: UnLoadAndCLOSE (void)
{
	DELETE_OBJ (m_pCT);
}


// --------------------------------------------------------------------------------------------
// die einstellbaren Parameter in die Registry-DB wegschreiben, da sie durch die
// Interface-Funktion SetAdjustValue() verändert worden sein können
void GeoReinExtension :: AdjustValuesToRegistry (void)
{
ResString AutoClear (ResID (IDS_AUTOCLEAR, pRF), 30);	
ResString PolyApprox (ResID (IDS_POLYAPPROX, pRF), 30);	
CCurrentUser cuExtConfig (RegistryExtPathRein, true);
DWORD dwWert2 = m_bClear;				// Wert des Schlüssels "AutoClear"
DWORD dwWert3 = DtoL (10. * m_dDPEps);	// Wert des Schlüssels "DoppelPunkt"
DWORD dwWert4 = DtoL (10. * m_dSpEps);	// Wert des Schlüssels "Spitze"
DWORD dwWert5 = m_iLoopLen;				// Wert des Schlüssels "Schleife"
DWORD dwWert6 = DtoL (100. * m_dReduz);	// Wert des Schlüssels "PolyApprox"

	if (!cuExtConfig.GetDWORD (AutoClear.Addr(), dwWert2))
		cuExtConfig.SetDWORD (AutoClear.Addr(), dwWert2);

	if (!cuExtConfig.GetDWORD (RegDoppelPunkt, dwWert3))
		cuExtConfig.SetDWORD (RegDoppelPunkt, dwWert3);

	if (!cuExtConfig.GetDWORD (RegSpitzenWinkel, dwWert4))
		cuExtConfig.SetDWORD (RegSpitzenWinkel, dwWert4);

	if (!cuExtConfig.GetDWORD (RegSchleife, dwWert5))
		cuExtConfig.SetDWORD (RegSchleife, dwWert5);

	if (!cuExtConfig.GetDWORD (PolyApprox.Addr(), dwWert6))
		cuExtConfig.SetDWORD (PolyApprox.Addr(), dwWert6);

} // AdjustValuesToRegistry


// --------------------------------------------------------------------------------------------
// Test, ob Geometrie überhaupt überprüft werden soll und Aufruf der GeometrieTest-Routine;
// Rückgabe von true, wenn Objektgeometrie überprüft wurde, sonst false
bool GeoReinExtension :: GeometrieCheck (OBJGEOMETRIE *pOG, IUnknown *pICS)
{
	_ASSERTE (pOG != NULL);

	if (! pOG) return false;

int iFlags = pOG->iFlags;	//  Flags des zu testenden Objektes

	m_iOT = pOG->iObjTyp;	// Objekttyp (Punkt, Linie, Fläche, Text, ...) bzw.
	if ((m_iOT != OT_PUNKT && m_iOT != OT_KANTE && m_iOT != OT_FLAECHE &&
		m_iOT != OT_TEXT && m_iOT != OT_LABEL) ||	// weder Geometrie- noch (indirektes) Textobjekt bzw.
		iFlags & OGTempObject ||	// temporäre Abspeicherung oder
		iFlags & OGOverlay)			// schon vorhandene Geometrie übernehmen
		return false;	// dann keine Testung der Geometrie; Objekt wird deshalb nur durchgereicht
				
	Approximation32 (pOG);

bool bDblCoord = iFlags & OGConverted;	// Koordinaten des an GeoRein übergebenen Objektes sind
										// im double- (true) bzw. KoOrd-Format (false)

// Konvertierung in ElementarObjekt (EPunkt, EKante, EFlaeche); aus Text wird auch Punkt
EObjekt* pEO = NULL;	// EObjekt, das aus OBJGEOMETRIE rekonstruiert wird

	if (!OBJGEOMETRIEinEObj (pOG, pEO, m_pCT, pICS))
	{
		DELETE_OBJ (pEO);	// vorsichtshalber
		return false;
	}
                    
string sUIdent;
long lONr = pOG->lONr;	// Objektnummer des zu testenden Objektes
	
	if (0 != lONr && -1 != lONr)	// neue lokale Stringresource
	{
	ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

		Format (sUIdent, (char*)resText.Addr(), lONr);
	}
	else
		sUIdent = ResString (ResID (IDS_UINEUTRAL, pRF), 20);

bool bEIO = false;		// pEO (noch) nicht in OBJGEOMETRIE zurückübertragen
string sAnalyseText;	// Ergebnis der Fehleranalyse

// Test auf Geometriefehler und evtl. Bereinigung; enthält das Objekt noch Fehler, die
// nicht automatisch bereinigt werden konnten, dann Rückgabe von false
GeoFehlerListe GFL(*pEO);

	if (! GeometrieTest (GFL, *pEO, bDblCoord, iFlags, sAnalyseText))	// Geometriefehler
		SetFeatureWithError (lONr, pEO, pOG, bDblCoord, iFlags, bEIO, sAnalyseText, sUIdent);

	else	// kein Geometriefehler (mehr)
		SetFeatureWithoutError (lONr, pEO, pOG, bDblCoord, iFlags, bEIO, sAnalyseText, sUIdent, GFL);

	if (! bEIO)	// (bereinigtes) Geometrieobjekt wieder in Struktur OBJGEOMETRIE einschreiben
		EObjInOBJGEOMETRIE (pEO, m_iOT, pOG, bDblCoord);

	DELETE_OBJ (pEO);
	
	return true;
} // GeometrieCheck


// --------------------------------------------------------------------------------------------
// Behandlung des Merkmals "Geometriefehler" für ein Objekt mit Geometriefehler
void GeoReinExtension :: SetFeatureWithError (long lONr, EObjekt* pEO, OBJGEOMETRIE* pOG,
				  bool bDblCoord, int& iFlags, bool& bEIO, string sAnalyseText, string sUIdent)
{
ErrCode rcDummy;	// für DEX_SetError()

	// Liegt ein Geometriefehler vor, wird das Objekt entweder abgewiesen oder unter bestimmten
	// Bedingungen trotzdem abgespeichert, aber mit dem Merkmal "Geometriefehler" versehen, in
	// dem der Fehler beschrieben wird.

	// ein schon in der DB vorhandenes Objekt wurde modifiziert
	if (iFlags & OGModObject)	// Geometrie des Objektes ersetzen
	{
		// hatte dieses Objekt schon Geometriefehler, wird es trotz der immer noch vorhandenen
		// Fehler abgespeichert, da ja für deren Bereinigung mehrere Schritte nötig sein können;
		// die Fehlermitteilung wird aktualisiert
		if (S_FALSE != FehlerhaftesObjekt (NULL, lONr))
		{
			EObjInOBJGEOMETRIE (pEO, m_iOT, pOG, bDblCoord);	// pEO ist (evtl.) teilbereinigt
			bEIO = true;							// pEO in OBJGEOMETRIE zurückübertragen
			GeometryErrorToFeature (pOG, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT,
									m_ulMCodeGeoErr, sAnalyseText, sUIdent);
		}


		// dieses Objekt war bisher fehlerfrei, ist aber jetzt fehlerbehaftet
		else
		{
		struct ErrBox ebDate;

			ebDate.bAnsw = false;	// YES/NO gedrückt (true/false)

			// nur dann abgespeichert, wenn das OGAskWhenError-Flag gesetzt ist und ...
			if (iFlags & OGAskWhenError)
			{
			ResString resText (ResID (IDS_DEFECTSTORE, pRF), 150);

				ebDate.sErrText = resText.Addr();
				DEX_SetError (rcDummy, 0, WC_MESSAGE_REIN, (void*)&ebDate);
			}

			// ... der Anwender die Abfrage bejaht
			if (ebDate.bAnsw)	// fehlerbehaftet abspeichern
			{
				EObjInOBJGEOMETRIE (pEO, m_iOT, pOG, bDblCoord);
				bEIO = true;
				GeometryErrorToFeature (pOG, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT,
									    m_ulMCodeGeoErr, sAnalyseText, sUIdent);
			}
			else		// nicht abspeichern
				pOG->iFlags |= OGIgnoreGeometry;	// neue Geometrie ignorieren
		}
	}


	// ein bisher noch nicht in der DB vorhandenes Objekt soll eingespeichert werden
	else
	{
	long lNewONr = 0;	// Objektnummer, wenn das Objekt fehlerhaft abgespeichert wird
				
	// bei aufgetretenen Fehlern wird nur dann abgespeichert, wenn das OGAskWhenError-Flag
	// gesetzt ist und ...
	struct ErrBox ebDate;

		ebDate.bAnsw = false;	// YES/NO gedrückt (true/false)

		if (iFlags & OGAskWhenError)
		{
		ResString resText (ResID (IDS_DEFECTSTORE, pRF), 150);

			ebDate.sErrText = resText.Addr();
			DEX_SetError (rcDummy, 0, WC_MESSAGE_REIN, (void*)&ebDate);
		}

		// ... der Anwender die Abfrage bejaht (z.B. bei Neueditierung) oder wenn das
		// OGForceGeoError-Flag nicht gesetzt ist (z.B. bei Daten-Import)
		if (ebDate.bAnsw || !(iFlags & OGForceGeoError))
		{
			EObjInOBJGEOMETRIE (pEO, m_iOT, pOG, bDblCoord);	// pEO ist (evtl.) teilbereinigt
			bEIO = true;

			// vor dem Anhängen des Merkmals "Geometriefehler" wird dieses Objekt in der
			// Routine GeometryErrorToFeature() erst einmal erzeugt
			GeometryErrorToFeature (pOG, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT,
									m_ulMCodeGeoErr, sAnalyseText, sUIdent);
			lNewONr = pOG->lONr;
		}

		// Objekt ist jetzt evenuell in die Datenbank abgespeichert;
		// durch das noch nachfolgend gesetzte OGIgnoreGeometry-Flag wird TRiAS mitgeteilt,
		// daß das Objekt fehlerhaft ist und deshalb nicht in die DB einzuspeichern ist
		// (war das OGForceGeoError-Flag rückgesetzt gewesen, ist dieses Objekt schon durch
		// die Routine GeometryErrorToFeature() fehlerhaft abgespeichert worden)
		pOG->iFlags |= OGIgnoreGeometry;
		pOG->lONr = lNewONr;
	}
} // SetFeatureWithError


// --------------------------------------------------------------------------------------------
// Behandlung des Merkmals "Geometriefehler" für ein Objekt ohne bzw. mit automatisch
// bereinigtem Geometriefehler
void GeoReinExtension :: SetFeatureWithoutError (long lONr, EObjekt* pEO, OBJGEOMETRIE* pOG,
                                  bool bDblCoord, int& iFlags, bool& bEIO, string sAnalyseText,
								  string sUIdent, GeoFehlerListe& GFL)
{	
	// Geometrie eines schon in der DB vorhandenen Objektes soll ersetzt werden
	if (iFlags & OGModObject)
		FehlerMerkmalLoeschen (lONr);	// dann Merkmal "Geometriefehler" löschen

	if (sAnalyseText.length() > 0)	// Text für automatisch bereinigte Geometriefehler
	{
		EObjInOBJGEOMETRIE (pEO, m_iOT, pOG, bDblCoord);	// pEO ist (evtl.) teilbereinigt
		bEIO = true;

		if (GeometryErrorToFeature (pOG, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT,
									m_ulMCodeGeoClear, sAnalyseText, sUIdent))
									
		// nur wenn Objekt bisher noch nicht existiert hatte, wurde es jetzt durch
		// GeometryErrorToFeature() angelegt und in die DB eingespeichert; deshalb soll Objekt
		// im weiteren Speicherprozess von TRiAS ignoriert werden
		if (0 == (iFlags & OGModObject))
			pOG->iFlags |= OGIgnoreGeometry;
			
		// Test, ob sich am Kantenende eine Schleife befand
		IsLineWithLoop (GFL, pOG->lIdent, iFlags, sUIdent);
	}
} // SetFeatureWithoutError


// --------------------------------------------------------------------------------------------
// Die folgende Funktion verpaßt dem fehlerhaften bzw. dem bereinigten Objekt ein Merkmal, in
// dem die Beschreibung der (bereinigten) Geometriefehler eingetragen sind. Wenn das Objekt
// noch nicht existiert, wird es vorher erzeugt.
bool GeoReinExtension :: GeometryErrorToFeature (OBJGEOMETRIE* pOG, uint uiResKey,
			   uint uiResKT, uint uiResLT, ulong& ulMCode, string sAnalyseText, string sUIdent)
{
	_ASSERTE (pOG != NULL);

	if (0 == (pOG->iFlags & OGModObject))	// Geometrie des Objektes nicht ersetzen,
	{										// d.h. Objekt existiert noch nicht
	// Test, ob sAnalyseText IRGENDWO ein 'F' enthält
	size_t pos1 = 0, pos2;
		
		for (;;)
		{
			pos2 = sAnalyseText.find ('F', pos1);
			if (NPOS == pos2) break;		// kein 'F' (mehr) gefunden

			// sAnalyseText enthält irgendwo ein 'F'; Folgt darauf das Zeichen '1' ... '9' ?
			if ('1' <= sAnalyseText[pos2+1] && sAnalyseText[pos2+1] <= '9')
			{
				// Folgt danach ": " ?
				if (':' == sAnalyseText[pos2+2] && ' ' == sAnalyseText[pos2+3])
				{	// Objekt hat Geometriefehler, soll aber trotzdem abgespeichert werden
					pOG->iFlags |= OGObjectHasGeometryErrors;
					break;
				}

				// bzw. Ziffer und ": " ?
				else if ('0' <= sAnalyseText[pos2+2] && sAnalyseText[pos2+2] <= '9' &&
						 ':' == sAnalyseText[pos2+3] && ' ' == sAnalyseText[pos2+4])
				{
					pOG->iFlags |= OGObjectHasGeometryErrors;
					break;
				}

				// bzw. Kleinbuchstabe und ": " ?
				else if ('a' <= sAnalyseText[pos2+2] && sAnalyseText[pos2+2] <= 'z' &&
						 ':' == sAnalyseText[pos2+3] && ' ' == sAnalyseText[pos2+4])
				{
					pOG->iFlags |= OGObjectHasGeometryErrors;
					break;
				}
			
				// bzw. Ziffer, Kleinbuchstabe und ": " ?
				else if ('0' <= sAnalyseText[pos2+2] && sAnalyseText[pos2+2] <= '9' &&
						 'a' <= sAnalyseText[pos2+3] && sAnalyseText[pos2+3] <= 'z' &&
						 ':' == sAnalyseText[pos2+4] && ' ' == sAnalyseText[pos2+5])
				{
					pOG->iFlags |= OGObjectHasGeometryErrors;
					break;
				}}

			pos1 = pos2 + 1;
		}

		// Da das Objekt noch nicht existiert, wird an dieser Stelle versucht, es in der
		// Datenbank zu erzeugen.
#if _TRiAS_VER < 0x0300
		DEX_ModObjGeometrie (*pOG);
#else
		pOG->iFlags |= OGNoExtendedErrorCheck;	// das Teilen von Kanten wird erst einmal unterbunden (#WM021217)
		DEX_ModObjGeometrieEx (DEX_GetContextDataSource(), *pOG);
#endif // _TRiAS_VER < 0x0300

		if (0 == pOG->lONr || -1 == pOG->lONr)
			return false;	// Objekt wurde nicht erzeugt

		// um in Zukunft doppeltes Einspeichern verhindern:
		pOG->iFlags &= ~OGNewObject;	// kein neues Objekt generieren, sondern
		pOG->iFlags |= OGModObject;		//  Geometrie des Objektes ersetzen
	
		// für alle Fälle unseren UniqueIdent verpassen
		if (sUIdent == ResString (ResID (IDS_UINEUTRAL, pRF), 20).Addr())
		{
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

			Format (sUIdent, (char*)resText.Addr(), pOG->lONr);
		}

#if _TRiAS_VER < 0x0300
		WriteFeatureText (pOG->lONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIdent);
#else
	HPROJECT hPr = DEX_GetObjectProject (pOG->lONr);

		WriteFeatureText (pOG->lONr, DEX_GetUniqueIdentMCodeEx (hPr), TT_Objekt, sUIdent);
#endif // _TRiAS_VER < 0x0300
	}

	// Merkmal an dieses Objekt schreiben, der MerkmalsCode befindet sich im DBHeader
	if (0 == ulMCode || (ulong)-1 == ulMCode)
	{
		ulMCode = GetHeaderMCode (true, uiResKey, uiResKT, uiResLT,
								  DEX_GetObjIdent(pOG->lONr));
		if (0 == ulMCode || (ulong)-1 == ulMCode)
			return false;
	}

	return WriteFeatureText (pOG->lONr, ulMCode, TT_Objekt, sAnalyseText);

} // GeometryErrorToFeature


// --------------------------------------------------------------------------------------------
// Testen, ob das Merkmal "Geometriefehler" überhaupt existiert und wenn ja, dann am
// lONr-Objekt löschen
void GeoReinExtension :: FehlerMerkmalLoeschen (long lONr)
{
// MerkmalsCode für Merkmal "Geometriefehler" aus DBHeader holen
ulong ulMCode = GetHeaderMCode (false, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT,
								DEX_GetObjIdent(lONr));

	if (0 == ulMCode || (ulong)-1 == ulMCode)
		return;	// Merkmal "Geometriefehler" existiert überhaupt nicht

	WriteFeatureText (lONr, ulMCode, TT_Objekt, "");
} // FehlerMerkmalLoeschen


// --------------------------------------------------------------------------------------------
// Polygonapproximation (derzeit nur !!!) für Linienobjekte;
// Rückgabe von true, wenn Approximation durchgeführt wurde, sonst false
bool GeoReinExtension :: Approximation32 (OBJGEOMETRIE* pOG)
{
	if (m_dReduz <= dRedEps) return false;	// keine Reduzierung der Stützpunkte

	_ASSERTE (pOG != NULL);

	if (! pOG) return false;

	if (pOG->iObjTyp != OT_KANTE)	// keine Linie
		return false;

// ACHTUNG: Nachfolgend wird davon ausgegangen, daß in der übergebenen Geometrie das Flag
// OGConverted gesetzt ist, d.h. daß die Koordinaten im double-Format vorliegen. Der Fall,
// daß OGConverted nicht gesetzt ist, bleibt vorerst noch unbearbeitet.
int iFlags = pOG->iFlags;

	if ((iFlags & OGConverted) == 0)
	{
		if (! m_bAnzeige)
		{
			MessageBox (hWnd(), "Es wird keine Polygonapproximation durchgeführt,\nda das Flag OGConverted nicht gesetzt ist!", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
			m_bAnzeige = true;
		}
		return false;
	}

long lAnzv = pOG->lCnt;	// Stützpunktanzahl vor Approximation

	if (lAnzv <= k0)		// Mindestanzahl an Stützpunkten für Approximation
		return false;

long lAnzn = lAnzv;			// Stützpunktanzahl nach Approximation

	if (PolygonApproximation ((double*)pOG->pdblX, (double*)pOG->pdblY, lAnzn, m_dReduz, k0) == false)
	{
		pOG->iFlags |= OGIgnoreGeometry;	// Geometrie ignorieren (nicht verändern)
		piInterlockedDecrement (&m_lSem);
		return false;	// keine Abspeicherung der Geometrie (wurde bei PolygonApproximation zerstört)
	}
			
	// Objekt pOG aktualisieren, wenn Stützpunktanzahl reduziert wurde
	if (lAnzv > lAnzn)	
		pOG->lCnt = lAnzn;	// Stützpunktanzahl nach Approximation

	return true;
} // Approximation32


// --------------------------------------------------------------------------------------------
// Test, ob in der GeoFehlerListe SelbstInzid-Fehler mit abgetrennten Schleifen eingetragen
// wurden;
// die Variable "sAnalyseText" wird nicht als Parameter an diese Funktion übergeben, da sie 
// die Beschreibung von möglicherweise 2 abgetrennten Schleifen enthalten kann; an die
// abgetrennten Schleifen soll aber nur EINE Beschreibung angehangen werden
bool GeoReinExtension :: IsLineWithLoop (GeoFehlerListe& GFL, long lIdent, int iFlags,
										 string sUIdent)
{
ResString resText (ResID (IDS_SINZIDENZBER1, pRF), 70);
string sAnalyseText;	// Beschreibung der bereinigten Selbstinzidenz
double XOut, YOut;		// Real-Koordinaten des Inzidenz-Punktes

CRing ri (GFL);	// Navigator für sequentiellen Container auf aktuelle GeoFehlerListe

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoFehlerLock ml (ri);

		if (!ml) continue;

		if (GFT_Selbstinzidenz == ml->GetType())
		{
		SelbstInzid* pSI = (SelbstInzid*)(GeoFehler*)ml;

			if (pSI->GetEndLoop())	// Selbstinzidenz mit abgetrennter Schleife
			{
			// zuerst EKante --> OBJGEOMETRIE wegen GeometryErrorToFeature()
			EKante* pLoopKt = pSI->GetEndLoop();
			OBJGEOMETRIE LoopOG;

				INITSTRUCT (LoopOG, OBJGEOMETRIE);
				LoopOG.lIdent = lIdent;
				LoopOG.iObjTyp = OT_KANTE;
				LoopOG.iFlags = iFlags & ~OGConverted;	// KoOrd- und nicht double-Koordinsten
				LoopOG.iFlags |= OGNewObject;			// neues Objekt generieren und
				LoopOG.iFlags &= ~OGModObject;			//  nicht Geometrie des Objektes ersetzen
				LoopOG.lCnt = pLoopKt->ASP();
				LoopOG.pdblX = new KoOrd [LoopOG.lCnt];
				LoopOG.pdblY = new KoOrd [LoopOG.lCnt];

			    if (!LoopOG.pdblX || !LoopOG.pdblY)
				{
					DEX_Error (RC_georein, EC_NOMEMORY);
    				return false;
				}

				pLoopKt->GetKante ((KoOrd*)LoopOG.pdblX, (KoOrd*)LoopOG.pdblY, LoopOG.lCnt);

				DBKoordInReal (pSI->RP(1), XOut, YOut, m_pCT);	// Datenbank- in Real-Koordinaten
				Format (sAnalyseText, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut),
					    DtoL(YOut));

				// hier wird die Schleife als neues Objekt nach TRiAS gespeichert und mit den
				// Merkmalen der ursprünglichen Kante versehen
				GeometryErrorToFeature (&LoopOG, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT,
								        m_ulMCodeGeoErr, sAnalyseText, sUIdent);
				DELETE_OBJ(LoopOG.pdblX);
				DELETE_OBJ(LoopOG.pdblY);
			}
		}
	}

	return true;

} // IsLineWithLoop


// --------------------------------------------------------------------------------------------
//	DebugSection-Eintrag aus win.ini lesen
bool GeoReinExtension :: _GetDebugOutputFlag (void)
{
ResString Section (ResID (IDS_DEBUGSECTION, pRF), 30);
ResString Entry (ResID (IDS_DEBUGENTRY, pRF), 30);	
char pcBuffer [5] = "";
	
	return GetProfileString (Section.Addr(), Entry.Addr(), "0", pcBuffer, sizeof (pcBuffer)) 
		   && (atoi (pcBuffer) > 0) ? true : false;
} // _GetDebugOutputFlag


// --------------------------------------------------------------------------------------------
// Reaktion auf Fehlercode iWC
int ErrHandler (int iWC, int iRoutine, ...)
{
va_list vaArgs;		// Liste der unbenannten Argumente

	va_start (vaArgs, iRoutine);

void* pvData = va_arg (vaArgs, void*);	// Makro, um die unbenannten Argumente herauszuholen

	va_end (vaArgs);

ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
				
	if (IDYES == MessageBox (__hWndM, ((ErrBox*)pvData)->sErrText.c_str(), resTitel.Addr(),
							 MB_ICONERROR | MB_YESNO))
	{
		// nachfolgende Zeile ist erforderlich, da die return-Werte ("1" bzw. "0")
		// komischerweise bei DEX_SetError() nicht ankommen
		((ErrBox*)pvData)->bAnsw = true;	// für "YES"
		return 1;	// für "YES"
	}

	((ErrBox*)pvData)->bAnsw = false;		// für "NO"
	return 0;		// für "NO"

} // ErrHandler
