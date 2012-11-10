// Funktionen für Geometriefehler "Insel innerhalb einer anderen Insel"
// File: INSEL_IN.CXX

#include "GeoReinP.hxx"

#include "insel_in.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
InselInInsel :: InselInInsel (EObjekt& GO, int iKaNr1, int iKaNr2)
			  : GeoFehler (GO)
{
	_ASSERTE (iKaNr1 >= 0);
	_ASSERTE (iKaNr2 >= 0);

	_iKaNr1 = iKaNr1;
	_iKaNr2 = iKaNr2;
	_AP1 = ((EFlaeche&)GO).KA(_iKaNr1).SP(0);
	_AP2 = ((EFlaeche&)GO).KA(_iKaNr2).SP(0);
}


//-------------------------------------------------------------------------------------------------
InselInInsel :: InselInInsel (InselInInsel& II)
			  : GeoFehler (II._GO, II._isCorrected)
{
	_iKaNr1 = II._iKaNr1;
	_iKaNr2 = II._iKaNr2;
	_AP1 = II._AP1;
	_AP2 = II._AP2;
}


//-------------------------------------------------------------------------------------------------
InselInInsel :: ~InselInInsel (void)
{
}


//-------------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool InselInInsel :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, InselInInsel) (*this))
		return true;
	DEX_Error (RC_insel_in, EC_NOMEMORY);
	return false;
}
 

//-------------------------------------------------------------------------------------------------
// Beschreibung des Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void InselInInsel :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_INSELINN, pRF), 30);

	if (pCT)
	{
	double XOut1, YOut1;	// Real-Koordinaten des Anfangspunktes der inneren Insel
	double XOut2, YOut2;	// Real-Koordinaten des Anfangspunktes der äußeren Insel

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
