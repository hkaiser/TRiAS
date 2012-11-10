// Methoden für GeometriefehlerListe
// Datei: GERRLIST.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "SelbInzi.hxx"			// SelbstInzi
#include "ErrorCorrection.hxx"	// SeparateEndLoop


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



//-------------------------------------------------------------------------------------------------
// Konstruktor / Destruktor
GeoFehlerListe :: GeoFehlerListe (EObjekt& GO)
				: _GO (GO),     // Initialisierung des Datenelements _GO
				  CListContainer () 
{
}


//-------------------------------------------------------------------------------------------------
GeoFehlerListe :: ~GeoFehlerListe (void) 
{
// 'EveryDelete' ruft für alle Objekte der Liste die Funktion 'UserDelete()'
	EveryDelete ();     // alle Elemente dieser Liste löschen

}  // an dieser Stelle wird implizit der Destruktor des CListContainers gerufen


//-------------------------------------------------------------------------------------------------
// 'UserDelete' wird für jedes Objekt, das aus der GeoFehlerListe gelöscht werden soll, gerufen,
// wobei pObj auf eben dieses Objekt verweist
void GeoFehlerListe :: UserDelete (void* pObj) 
{
	_ASSERTE (pObj);
	((GeoFehler*)pObj) -> ~GeoFehler ();	
}

  
//-------------------------------------------------------------------------------------------------
// Beschreibung aller (bereinigten) GeoFehler in Puffer sAnalyseText eintragen
void GeoFehlerListe :: GesamtAnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
	if (0 == Count()) return;	// GeoFehlerListe enthält keine Einträge

CRing ri (*this);

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoFehlerLock ml (ri);

		if (! ml) continue;	// wenn kein Zugriff möglich, weiter in der for-Schleife
		ml -> AnalysePuffern (sAnalyseText, pCT);	// Aufruf der Elementfunktion von GeoFehler
	}
} // GesamtAnalysePuffern

  
//-------------------------------------------------------------------------------------------------
// Testen, ob Konturinzidenz zwischen den Konturen iKNr1 und iKNr2 diagnostiziert wurde, dann
// Rückgabe von true, sonst false
bool GeoFehlerListe :: DieseZweiKonturen (int iKNr1, int iKNr2)
{
	if (0 == Count()) return false;	// GeoFehlerListe enthält keine Einträge

CRing ri (*this);

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoFehlerLock ml (ri);
	int iKNrFL1 = -1;	// in GeoFehlerListe eingetragene Konturnummern
	int iKNrFL2 = -1;

		if (!ml)
			continue;	// wenn kein Zugriff möglich, weiter in der for-Schleife
		ml -> ZweiKonturen (iKNrFL1, iKNrFL2);
		if ((iKNr1 == iKNrFL1 && iKNr2 == iKNrFL2) ||
			(iKNr1 == iKNrFL2 && iKNr2 == iKNrFL1))
			return true;
	}
	return false;
} // DieseZweiKonturen


//-------------------------------------------------------------------------------------------------
// Testen, ob GeoFehler erkannt und (wenn ja) bereinigt wurden oder nicht
// mit return-Wert
//    0:  kein GeoFehler in GeoFehlerListe abgelegt
//    1:  alle GeoFehler wurden bereinigt
//    2:  wenigstens ein GeoFehler wurde nicht bereinigt
int GeoFehlerListe :: BeseitigungsArt (void)
{
	if (0 == Count())
		return 0;	// kein GeoFehler in GeoFehlerListe abgelegt

CRing ri (*this);

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoFehlerLock ml (ri);

		if (!ml)
			continue;	// wenn kein Zugriff möglich, weiter in der for-Schleife
		if (ml -> WasCorrected() == false)
			return 2;	// wenigstens 1 unbereinigten Fehler gefunden
	}
	return 1;	// nur bereinigte Fehler gefunden
}
  

//-------------------------------------------------------------------------------------------------
// automatische Bereinigung von Selbstinzidenzen durch Zerlegen des Objektes, wenn
// - es sich um eine Schleife am Anfang und/oder Ende einer Kante handelt und
// - keine anderen unbereinigten Fehler vorliegen
bool GeoFehlerListe :: EndLoopCorrection (void) 
{
	if (1 > Count() || Count() > 2)
		return false;	// keine Bereinigung, da maximal 2 Fehler vorliegen dürfen

EKante& Kt = (EKante&)GO();	// Originalobjekt
long lKL = Kt.ASP();		// Länge,
EPunkt AP = Kt.SP(0);		//  Anfangspunkt und
EPunkt EP = Kt.SP(lKL-1);	//  Endpunkt der originalen Kante
long lPInd;					// Index des Selbstinzidenzpunktes

CRing ri (*this);

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoFehlerLock ml (ri);

		if (!ml)
			return false;	// keine Bereinigung, da unklarer GFL-Eintrag;

		if (GFT_Selbstinzidenz != ml->GetType())
			return false;	// keine Bereinigung, da auch andere Fehler vorhanden

	SelbstInzid* pSI = (SelbstInzid*)(GeoFehler*)ml;

		if (0 <= pSI->RK())
			return false;	// keine Bereinigung, da keine Kante, sondern Flächenkontur

		if (RAND != pSI->RF())
			return false;	// keine Bereinigung, da keine Stützpunktwiederholung

	EPunkt GP1 = pSI->RP(1);	// Selbstinzidenzpunkt

		if (GP1 != AP && GP1 != EP)
			return false;	// keine Bereinigung, da Selbstinzidenz nicht an einem der beiden Endpunkte

		if (! Kt.IsLoopLarge (GP1.X(), GP1.Y(), lPInd))
			return false;	// keine Bereinigung, da Schleife zu klein
	}

	// Test, der Fall vorliegt, dass an beiden Enden eine Schleife existiert und die Kantenlänge
	// zwischen den beiden Inzidenzpunkten Null ist, d.h. AP == EP; dann keine Abtrennung, weil
	// Kante optisch wie eine "8" aussieht, die (noch) nicht automatisch bereinigt wird
	if (AP == EP)
		return false;

	// das eigentliche Abtrennen der Schleife erst in einer zweiten for-Schleife, da erst bei einem
	// evtl. 2. GFL-Eintrag einer der Gründe auftreten kann, der zu einem "return false" führt	
	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoFehlerLock ml (ri);
	SelbstInzid* pSI = (SelbstInzid*)(GeoFehler*)ml;
	EPunkt GP1 = pSI->RP(1);		// Selbstinzidenzpunkt
	EKante* pLoopKt = new EKante();	// die abgetrennte Schleife (wird im Destruktor von SelbstInzid freigegeben)

		// Index des Selbstinzidenzpunktes ermitteln
		Kt.IsLoopLarge (GP1.X(), GP1.Y(), lPInd);

		// Schleife abtrennen
		if (! SeparateEndLoop (&Kt, GP1.X(), GP1.Y(), lPInd, pLoopKt))
			return false;

		pSI->SetEndLoop (pLoopKt);
		pSI->ErrorCorrection();	// setzt _isCorrected = true
	}

	return true;

} // EndLoopCorrection
