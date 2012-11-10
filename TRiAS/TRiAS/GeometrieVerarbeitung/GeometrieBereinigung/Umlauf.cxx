// Funktionen für Geometriefehler "falscher Umlaufsinn einer Flächenkontur"
// File: UMLAUF.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "umlauf.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
Umlauf :: Umlauf (EObjekt& GO, double& dFlInh, int iKaNr)
		: GeoFehler (GO) 
{
	_ASSERTE (GO.isA() == OT_FLAECHE);
	_ASSERTE (iKaNr >= 0);

	_iKaNr = iKaNr;
	_dFlInh = dFlInh;
}
        
        
//-------------------------------------------------------------------------------------------------
Umlauf :: Umlauf (Umlauf& UL)
		: GeoFehler (UL._GO, UL._isCorrected)
{
	_ASSERTE (UL._iKaNr >= 0);

	_iKaNr = UL._iKaNr;
	_dFlInh = UL._dFlInh;
}
        
        
//-------------------------------------------------------------------------------------------------
Umlauf :: ~Umlauf (void) 
{
}
        

//-------------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool Umlauf :: AddGeoFehler (GeoFehlerListe& GFL) 
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, Umlauf) (*this) != NULL)
		return true;
	DEX_Error (RC_umlauf, EC_NOMEMORY);
	return false;
}


//-------------------------------------------------------------------------------------------------
// Beschreibung des bereinigten Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void Umlauf :: AnalysePuffern (string& sAnalyseText, CoordTransX*)
{
ResString resText (ResID (IDS_UMLAUFBER, pRF), 50);

	sAnalyseText += resText.Addr();
	sAnalyseText += "\r\n";

} // AnalysePuffern
        

//-------------------------------------------------------------------------------------------------
// Bereinigung des Umlauf-Fehlers durch Umkehrung der Stützpunktfolge
void Umlauf :: ErrorCorrection (void)
{
	_ASSERTE (_GO.isA() == OT_FLAECHE);

	if (_isCorrected || 0. == _dFlInh)	// wenn Umlaufsinn nicht bestimmbar (_dFlInh == 0.),
		return;							//  dann keine Fehlerbereinigung

	((EFlaeche&)_GO).OrientDreh (_iKaNr);
	_isCorrected = true;		// Fehler wurde bereinigt

} // ErrorCorrection
