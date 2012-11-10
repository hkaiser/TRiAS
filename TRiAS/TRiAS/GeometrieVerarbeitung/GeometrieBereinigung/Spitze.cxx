// Funktionen für Geometriefehler "Spitze"
// File: SPITZE.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "spitze.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;

                        

// --------------------------------------------------------------------------------------------
Spitze :: Spitze (EObjekt& GO, long lSPNr, int iKaNr, bool bNull, double dDPEps,
				  DoublePair dpUF, bool bMetric)
		: GeoFehler (GO)
{
	_ASSERTE (lSPNr >= 0);

	_lSPNr = lSPNr;
	_iKaNr = iKaNr;
	m_bNull = bNull;
	m_dDPEps = dDPEps;
	m_dpUF = dpUF;
	m_bMetric = bMetric;

	if (OT_KANTE == GO.isA())
		_SPkt = ((EKante&)GO).SP(_lSPNr);
	else
	{
		_ASSERTE (GO.isA() == OT_FLAECHE);

		_SPkt = ((EFlaeche&)GO).KA(_iKaNr).SP(_lSPNr);
	}
}
        
        
// --------------------------------------------------------------------------------------------
Spitze :: Spitze (Spitze& SZ)
		: GeoFehler (SZ._GO, SZ._isCorrected)
{
	_ASSERTE (SZ._lSPNr >= 0);

	_lSPNr = SZ._lSPNr;
	_iKaNr = SZ._iKaNr;
	m_bNull = SZ.m_bNull;
	m_dDPEps = SZ.m_dDPEps;
	m_dpUF = SZ.m_dpUF;
	m_bMetric = SZ.m_bMetric;
	_SPkt = SZ._SPkt;
}
        
        
// --------------------------------------------------------------------------------------------
Spitze :: ~Spitze (void)
{
}
        
        
// --------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool Spitze :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, Spitze) (*this) != NULL)
		return true;
	DEX_Error (RC_spitze, EC_NOMEMORY);
	return false;
}


// --------------------------------------------------------------------------------------------
// Beschreibung des bereinigten bzw. unbereinigten Geometriefehlers als Merkmalstext in
// sAnalyseText eintragen
void Spitze :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_SPITZE, pRF), 50);				// unbereinigte Spitze

	if (m_bNull)
		resText = ResString (ResID (IDS_SPITZEBER, pRF), 50);	// bereinigte Spitze

	if (pCT)
	{
	double XOut, YOut;	// Real-Koordinaten der Spitze

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_SPkt, XOut, YOut, pCT);

	string sBuffer;

		Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut), DtoL(YOut));
		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern


// --------------------------------------------------------------------------------------------
// die Bereinigung einer Spitze erfolgt i. d. R. NICHT mehr durch Löschen, sondern durch
// Modifizieren des entsprechenden Stützpunktes; dazu wird von dem vorherigen bzw. nachfolgenden
// Stützpunkt das Lot auf die längere der beiden Strecken, die die Spitze bilden, gefällt; dies
// wird dann der modifizierte Stützpunkt an der Spitze
// Sonderfall: die Spitze hat 0°, dann wird wie bisher schlicht und einfach gelöscht
void Spitze :: ErrorCorrection (void)
{
	if (_isCorrected) return;

	_isCorrected = AcuteAngleCorrection (&_GO, _iKaNr, _lSPNr, m_bNull, m_dDPEps, m_dpUF,
										 m_bMetric);
} // ErrorCorrection


// --------------------------------------------------------------------------------------------
// durch die Korrektur von Spitzen können DoppelPunkte entstehen, die es vorher nicht gab;
// da in der Routine GeoAnalyse() die Stützpunkte mit FALLENDEM Index abgearbeitet werden,
// würde so ein nachträglich entstandener DoppelPunkt, der aus dem _lSPNr- und dem
// lVorInd-Stützpunkt besteht, nicht mehr erkannt (und damit auch nicht mehr bereinigt) werden
void Spitze :: SpecialRemove (EKante* pLine, long lLen, bool bClosed, long lVorInd)
{
	_ASSERTE (pLine != NULL);

bool bNull;		// Parameter von isDoppel(); wird hier nicht ausgewertet

	if (pLine->isDoppel (bNull, m_dDPEps, m_dpUF, m_bMetric, _lSPNr, lVorInd))
	{
		pLine->SubPunkt (1, _lSPNr);

		if (lLen > 2 && bClosed)
		{
			if (0 == _lSPNr)
				pLine->SubPunkt (1, lLen-2);	// eigentlich "lLen-1", aber durch SubPunkt()
												// wurde lLen schon um 1 verkleinert
			else if (lLen > 3 &&	// damit nicht aus einer Linie unnötig ein Punkt wird
					 lLen - 1 == _lSPNr)
				pLine->SubPunkt (1, 0);
		}
	}

} // SpecialRemove
