// Funktionen für Geometriefehler "Kollinearität"
// File: KOLLINEA.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "kollinea.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// globale Variable
extern ResourceFile* pRF;



//-------------------------------------------------------------------------------------------------
Kollinearitaet :: Kollinearitaet (EObjekt& GO, long lSPNr, int iKaNr)
				: GeoFehler (GO) 
{
	_ASSERTE (lSPNr >= 0);

	_lSPNr = lSPNr;
	_iKaNr = iKaNr;

	if (OT_KANTE == GO.isA())
		_KPkt = ((EKante&)GO).SP(_lSPNr);
	else
	{
		_ASSERTE (GO.isA() == OT_FLAECHE);
		_KPkt = ((EFlaeche&)GO).KA(_iKaNr).SP(_lSPNr);
	}
}
                
                
//-------------------------------------------------------------------------------------------------
Kollinearitaet :: Kollinearitaet (Kollinearitaet& KO)
				: GeoFehler (KO._GO, KO._isCorrected)
{
	_ASSERTE (KO._lSPNr >= 0);

	_lSPNr = KO._lSPNr;
	_iKaNr = KO._iKaNr;
	_KPkt = KO._KPkt;
}
                
                
//-------------------------------------------------------------------------------------------------
Kollinearitaet :: ~Kollinearitaet (void) 
{
}
                
                
//-------------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool Kollinearitaet :: AddGeoFehler (GeoFehlerListe& GFL) 
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, Kollinearitaet) (*this) != NULL)
		return true;
	DEX_Error (RC_kollinea, EC_NOMEMORY);
	return false;
}


//-------------------------------------------------------------------------------------------------
// Beschreibung des bereinigten Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void Kollinearitaet :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_KOLLINEARBER, pRF), 50);

	if (pCT)
	{
	double XOut, YOut;	// Real-Koordinaten des Kollinearitäts-Punktes

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_KPkt, XOut, YOut, pCT);

	string sBuffer;

		Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut), DtoL(YOut));
		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern
  

//-------------------------------------------------------------------------------------------------
// Bereinigung der Kollinearität durch Löschen der redundanten Punkte
void Kollinearitaet :: ErrorCorrection (void) 
{
	if (_isCorrected) return;

	CollinearCorrection (&_GO, _iKaNr, _lSPNr);
	_isCorrected = true;	// Fehler wurde bereinigt

} // ErrorCorrection
