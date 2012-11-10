// Funktionen für Geometriefehler "Selbstinzidenz"
// File: SELBINZI.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "selbinzi.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
SelbstInzid :: SelbstInzid (EObjekt& GO, int iKaNr, EPunkt& GemPkt1, EPunkt& GemPkt2,
							SchnittErg Form, EKante* pEndLoop)
			 : GeoFehler (GO)
{
	_iKaNr = iKaNr;
	_GemPkt1 = GemPkt1;
	_GemPkt2 = GemPkt2;
	_Form = Form;
	_pEndLoop = pEndLoop;
}


// --------------------------------------------------------------------------------------------
SelbstInzid :: SelbstInzid (SelbstInzid& SI)
			 : GeoFehler (SI._GO, SI._isCorrected)
{
	_iKaNr = SI._iKaNr;
	_GemPkt1 = SI._GemPkt1;
	_GemPkt2 = SI._GemPkt2;
	_Form = SI._Form;
	_pEndLoop = SI._pEndLoop;
}


// --------------------------------------------------------------------------------------------
SelbstInzid :: ~SelbstInzid (void)
{
	DELETE_OBJ(_pEndLoop);
}


// --------------------------------------------------------------------------------------------
// Eintrag in Fehlerliste konnte vorgenommen werden (true), sonst false
bool SelbstInzid :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, SelbstInzid) (*this) != NULL)
		return true;
	DEX_Error (RC_selbinzi, EC_NOMEMORY);
	return false;
}
  
  
// --------------------------------------------------------------------------------------------
// Beschreibung des Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void SelbstInzid :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_SINZIDENZ, pRF), 30);

	if (pCT)
	{
	double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten der Inzidenz-Punkte

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_GemPkt1, XOut1, YOut1, pCT);

	string sBuffer;

		switch (_Form)
		{
			case ECHT:
			case INNEN:
				Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut1),
						DtoL(YOut1));
				break;

			case RAND:
				// die Selbstinzidenz besteht in einer Schleife am Anfang bzw. Ende einer
				// offenen Kante und wurde automatisch durch das Abtrennen der Schleife bereinigt
				if (_pEndLoop)
					resText = ResString (ResID (IDS_SINZIDENZBER1, pRF), 70);

				Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut1),
						DtoL(YOut1));
				break;
				
			case UEBERLAPP:
				DBKoordInReal (_GemPkt2, XOut2, YOut2, pCT);
				Format (sBuffer, "%s (%ld,%ld)-(%ld,%ld)\r\n", (char*)resText.Addr(),
						DtoL(XOut1), DtoL(YOut1), DtoL(XOut2), DtoL(YOut2));
				break;
		}

		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern
