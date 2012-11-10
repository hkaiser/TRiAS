// Funktionen für Geometriefehler "Insel außerhalb einer Fläche"
// File: INSEL_EX.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "insel_ex.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
InselExt :: InselExt (EObjekt& GO, int iKaNr)
		  : GeoFehler (GO)
{
	_ASSERTE (iKaNr >= 0);

	_iKaNr = iKaNr;
	_AP1 = ((EFlaeche&)GO).KA(_iKaNr).SP(0);	// Anfangspunkt der externen Insel
	_AP2 = ((EFlaeche&)GO).KA(0).SP(0);			// Anfangspunkt der Außenkontur
}


//-------------------------------------------------------------------------------------------------
InselExt :: InselExt (InselExt& IE)
		  : GeoFehler (IE._GO, IE._isCorrected)
{
	_iKaNr = IE._iKaNr;
	_AP1 = IE._AP1;
	_AP2 = IE._AP2;
}
 
 
//-------------------------------------------------------------------------------------------------
InselExt :: ~InselExt (void)
{
}
   
   
//-------------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool InselExt :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, InselExt) (*this))
		return true;
	DEX_Error (RC_insel_ex, EC_NOMEMORY);
	return false;
}


//-------------------------------------------------------------------------------------------------
// Beschreibung des Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void InselExt :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_INSELEXT, pRF), 30);

	if (pCT)
	{
	double XOut1, YOut1;	// Real-Koordinaten des Anfangspunktes der externen Insel
	double XOut2, YOut2;	// Real-Koordinaten des Anfangspunktes der Außenkontur

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_AP1, XOut1, YOut1, pCT);
		DBKoordInReal (_AP2, XOut2, YOut2, pCT);

	string sBuffer;

		Format (sBuffer, "%s (%ld,%ld),(%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut1),
				DtoL(YOut1), DtoL(XOut2), DtoL(YOut2));
		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern
