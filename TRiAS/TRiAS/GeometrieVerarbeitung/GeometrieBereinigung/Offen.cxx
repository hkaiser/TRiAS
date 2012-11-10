// Funktionen für Geometriefehler "offene Kontur einer Fläche"
// File: OFFEN.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "offen.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;

                        

// --------------------------------------------------------------------------------------------
Offen :: Offen (EObjekt& GO, int iKaNr, bool bDblCoord)
       : GeoFehler (GO) 
{
	_ASSERTE (iKaNr >= 0);

	_iKaNr = iKaNr;	// Kantennummer (0 ... Außenkontur, > 0 Innenkontur)
	_bDblCoord = bDblCoord;
	_OPkt = ((EFlaeche&)GO).KA(_iKaNr).SP(0);
}


// --------------------------------------------------------------------------------------------
Offen :: Offen (Offen& OF)
       : GeoFehler (OF._GO, OF._isCorrected)
{
	_ASSERTE (OF._iKaNr >= 0);

	_iKaNr = OF._iKaNr;
	_bDblCoord = OF._bDblCoord;
	_OPkt = OF._OPkt;
}


// --------------------------------------------------------------------------------------------
Offen :: ~Offen (void)
{
}


// --------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool Offen :: AddGeoFehler (GeoFehlerListe& GFL) 
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, Offen) (*this) != NULL)
		return true;
	DEX_Error (RC_offen, EC_NOMEMORY);
	return false;
}


// --------------------------------------------------------------------------------------------
// Beschreibung des bereinigten bzw. unbereinigten Geometriefehlers als Merkmalstext in
// sAnalyseText eintragen;
// eine offene Kontur kann nur geschlossen werden, wenn die Fläche mit double-Koordinaten AN
// GEOREIN ÜBERGEBEN wurde; hatte die Fläche schon von vornherein KoOrd-Koordinaten, wird die
// Kontur nur mit Verlust eines Stützpunktes geschlossen (gilt nicht als Bereinigung !!!)
void Offen :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_OFFEN, pRF), 100);				// unbereinigte offene Kontur

	if (_isCorrected)
		resText = ResString (ResID (IDS_OFFENBER, pRF), 50);	// bereinigte offene Kontur

	if (pCT)
	{
	double XOut, YOut;	// Real-Koordinaten des Anfangspunktes der entsprechenden Kontur

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_OPkt, XOut, YOut, pCT);

	string sBuffer;

		Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut), DtoL(YOut));
		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern
  

// --------------------------------------------------------------------------------------------
// Korrektur einer offenen Kontur;
// Wenn das Ursprungsobjekt BEI DER ÜBERGABE an GeoRein double-Koordinaten hatte
// (_bDblCoord == true), entsteht durch die Konvertierung von double nach KoOrd in
// OBJGEOMETRIEinEObj() ausreichend Platz im Speicherbereich für die Koordinaten, so daß die
// Kontur durch Anhängen des 1. Konturpunktes geschlossen werden kann (echte
// Fehlerbereinigung).
// Hatte das Ursprungsobjekt von vornherein KoOrd-Koordinaten (_bDblCoord == false), ist kein
// Platz für einen zusätzlichen Stützpunkt vorhanden. Die Kontur wird deshalb unkorrekt dadurch
// geschlossen, indem der 1. Konturpunkt auf den letzten Konturpunkt gesetzt wird. Dies gilt
// aber nicht als richtige Korrektur und ist deshalb im Merkmal "Geometriefehler" zu vermerken.
void Offen :: ErrorCorrection (void) 
{
	_ASSERTE (_GO.isA() == OT_FLAECHE);

	if (_isCorrected) return;

EFlaeche* pFl = (EFlaeche*)&_GO;
KoOrd x = pFl->KA(_iKaNr).SP(0).X();
KoOrd y = pFl->KA(_iKaNr).SP(0).Y();

	if (_bDblCoord)	// ursprünglich waren es double-Koordinaten
	{
		pFl->AddPunkt (&x, &y, 1, -1, _iKaNr+1);
		_isCorrected = true;		// Fehler wurde bereinigt
	}
	else			// ursprünglich waren es schon KoOrd-Koordinaten
	{
	long lLInd = pFl->KA(_iKaNr).ASP() - 1;	// letzter Index der _iKaNr-ten Kontur

		// 1. Konturpunkt auf den letzten Konturpunkt setzen (gilt nicht als Bereinigung !!!)
		pFl->KA(_iKaNr).SP(lLInd).X() = pFl->KA(_iKaNr).SP(0).X();
		pFl->KA(_iKaNr).SP(lLInd).Y() = pFl->KA(_iKaNr).SP(0).Y();
		_OPkt = pFl->KA(_iKaNr).SP(lLInd);
	}

} // ErrorCorrection
