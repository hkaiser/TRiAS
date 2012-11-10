// Funktionen für Geometriefehler "Inzidenz zwischen Konturen"
// File: KONTINZI.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "kontinzi.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
KonturInzid :: KonturInzid (EObjekt& GO, int iKaNr1, int iKaNr2, EPunkt& GemPkt1,
							EPunkt& GemPkt2, SchnittErg Form)
			 : GeoFehler (GO)
{
	_ASSERTE (iKaNr1 >= 0);
	_ASSERTE (iKaNr2 >= 0);

	_iKaNr1 = iKaNr1;
	_iKaNr2 = iKaNr2;
	_GemPkt1 = GemPkt1;
	_GemPkt2 = GemPkt2;
	_Form = Form;
}


// --------------------------------------------------------------------------------------------
KonturInzid :: KonturInzid (KonturInzid& KI)
			 : GeoFehler (KI._GO, KI._isCorrected)
{
	_ASSERTE (KI._iKaNr1 >= 0);
	_ASSERTE (KI._iKaNr2 >= 0);

	_iKaNr1 = KI._iKaNr1;
	_iKaNr2 = KI._iKaNr2;
	_GemPkt1 = KI._GemPkt1;
	_GemPkt2 = KI._GemPkt2;
	_Form = KI._Form;
}


// --------------------------------------------------------------------------------------------
KonturInzid :: ~KonturInzid (void)
{
}


// --------------------------------------------------------------------------------------------
// Eintrag in Fehlerliste konnte vorgenommen werden (true), sonst false
bool KonturInzid :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, KonturInzid) (*this) != NULL)
		return true;
	DEX_Error (RC_kontinzi, EC_NOMEMORY);
	return false;
}


// --------------------------------------------------------------------------------------------
// Beschreibung des Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void KonturInzid :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_KINZIDENZ, pRF), 30);

	if (pCT)
	{
	double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten der Inzidenz-Punkte

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_GemPkt1, XOut1, YOut1, pCT);

	string sBuffer;

		switch (_Form)
		{
			case ECHT:
			case RAND_MIT:
			case INNEN_MIT:
				Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut1),
						DtoL(YOut1));
				break;
				
			case UEBERLAPP:
				DBKoordInReal (_GemPkt2, XOut2, YOut2, pCT);
				Format (sBuffer, "%s (%ld,%ld)-(%ld,%ld)\r\n", (char*)resText.Addr(),
						DtoL(XOut1), DtoL(YOut1), DtoL(XOut2), DtoL(YOut2));
				break;
				
			case BERUE_OHNE:
				DBKoordInReal (_GemPkt2, XOut2, YOut2, pCT);
				Format (sBuffer, "%s (%ld,%ld),(%ld,%ld)\r\n", (char*)resText.Addr(),
						DtoL(XOut1), DtoL(YOut1), DtoL(XOut2), DtoL(YOut2));
				break;
		}

		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern
