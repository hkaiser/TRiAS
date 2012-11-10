// Funktionen für Geometriefehler "DoppelPunkt"
// File: DOPPUNKT.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "doppunkt.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
DoppelPunkt :: DoppelPunkt (EObjekt& GO, long lSPNr, int iKaNr, bool bNull, double dSpEps)
			 : GeoFehler (GO)
{
	_ASSERTE (GO.isA() != OT_PUNKT);
	_ASSERTE (lSPNr >= 0);

	_lSPNr = lSPNr;
	_iKaNr = iKaNr;
	_bNull = bNull;
	m_dSpEps = dSpEps;

	if (OT_KANTE == GO.isA())
	{
		_DPkt1 = ((EKante&)GO).SP(_lSPNr);
		_DPkt2 = ((EKante&)GO).SP(_lSPNr-1);
	}
	else			// Fläche
	{
		_ASSERTE (GO.isA() == OT_FLAECHE);
		_DPkt1 = ((EFlaeche&)GO).KA(_iKaNr).SP(_lSPNr);
		_DPkt2 = ((EFlaeche&)GO).KA(_iKaNr).SP(_lSPNr-1);
	}
}


//-------------------------------------------------------------------------------------------------
DoppelPunkt :: DoppelPunkt (DoppelPunkt& DP)
			 : GeoFehler (DP._GO)
{
	_lSPNr = DP._lSPNr;
	_iKaNr = DP._iKaNr;
	_bNull = DP._bNull;
	m_dSpEps = DP.m_dSpEps;
	_DPkt1 = DP._DPkt1;
	_DPkt2 = DP._DPkt2;
}


//-------------------------------------------------------------------------------------------------
DoppelPunkt :: ~DoppelPunkt (void)
{
}
          
          
//-------------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool DoppelPunkt :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, DoppelPunkt) (*this) != NULL)
		return true;
	DEX_Error (RC_doppunkt, EC_NOMEMORY);
	return false;
}


// --------------------------------------------------------------------------------------------
// Beschreibung des bereingten bzw. unbereinigten Geometriefehlers als Merkmalstext in
// sAnalyseText eintragen
void DoppelPunkt :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_DOPPEL, pRF), 50);			// unbereinigter naher Stützpunkt

	if (_bNull)
		resText = ResString (ResID (IDS_DOPPELBER, pRF), 50);	// bereinigter doppelter Stützpunkt

	if (pCT)
	{
	double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten der doppelten Punkte

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_DPkt1, XOut1, YOut1, pCT);
		DBKoordInReal (_DPkt2, XOut2, YOut2, pCT);

	string sBuffer;

		Format (sBuffer, "%s (%ld,%ld),(%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut1),
				DtoL(YOut1), DtoL(XOut2), DtoL(YOut2));
		sAnalyseText += sBuffer;
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern
          

//---------------------------------------------------------------------------------------------
// Bereinigung des DoppelPunkt-Fehlers durch Löschen des Punktes
void DoppelPunkt :: ErrorCorrection (void)
{
	_ASSERTE (_GO.isA() != OT_PUNKT);
	_ASSERTE (_lSPNr >= 0);

	if (_isCorrected) return;
/*
	if (OT_KANTE == _GO.isA())
	{
	EKante* pKt = (EKante*)&_GO;

		pKt->SubPunkt (1, _lSPNr);

21.10.98: Wenn bei einer geschlossenen Kante zu einem der beiden "Schloßpunkte" die
          DoppelPunkt-Situation besteht, muß sie logischerweise auch zu dem anderen
		  "Schloßpunkte" bestehen; würde dieser dann auch noch gelöscht, wäre die ursprünglich
		  geschlossene Kante jetzt offen
	long lLen = pKt->ASP();		// Länge der Kante

		if (lLen > 1 && pKt->SP(0) == pKt->SP(lLen-1))	// geschlossene Kante
		{
			if (0 == _lSPNr)
				pKt->SubPunkt (1, lLen-1);
			else if (lLen-1 == _lSPNr)
				pKt->SubPunkt (1, 0);
		}
	}

	else		// Fläche
	{
		_ASSERTE (_GO.isA() == OT_FLAECHE);

	EFlaeche* pFl = (EFlaeche*)&_GO;
//	long lLen = pFl->KA(_iKaNr).ASP();

		pFl->KA(_iKaNr).SubPunkt (1, _lSPNr);

21.10.98: Wenn bei einer Kontur zu einem der beiden "Schloßpunkte" die DoppelPunkt-Situation
          besteht, muß sie logischerweise auch zu dem anderen "Schloßpunkte" bestehen; würde
		  dieser dann auch noch gelöscht, wäre die Kontur jetzt offen
		if (lLen > 2)
		{
			if (0 == _lSPNr)
				pFl->KA(_iKaNr).SubPunkt (1, lLen-2);	// eigentlich "lLen-1", aber durch SubPunkt()
														// wurde lLen schon um 1 verkleinert
			else if (lLen > 3 &&	// damit nicht aus einer Linie unnötig ein Punkt wird
					 lLen - 1 == _lSPNr)
				pFl->KA(_iKaNr).SubPunkt (1, 0);
		}
	}
*/
	DblPointCorrection (&_GO, _iKaNr, _lSPNr, m_dSpEps);

	_isCorrected = true;	// Fehler wurde bereinigt

} // ErrorCorrection
