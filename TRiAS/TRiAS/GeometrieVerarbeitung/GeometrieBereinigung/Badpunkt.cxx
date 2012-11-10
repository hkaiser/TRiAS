// Funktionen für Geometriefehler "Ungültige Koordinaten"
// File: BADPUNKT.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include "badpunkt.hxx"
    

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
BadPunkt :: BadPunkt (EObjekt& GO, long lSPNr, int iKaNr)
		  : GeoFehler (GO)
{
	_lSPNr = lSPNr;
	_iKaNr = iKaNr;

	if (OT_PUNKT == GO.isA())
		_BPkt = (EPunkt&)GO;
	else if (OT_KANTE == GO.isA())
		_BPkt = ((EKante&)GO).SP(_lSPNr);
	else			// Fläche
	{
		_ASSERTE (GO.isA() == OT_FLAECHE);
		_BPkt = ((EFlaeche&)GO).KA(_iKaNr).SP(_lSPNr);
	}
}


//-------------------------------------------------------------------------------------------------
BadPunkt :: BadPunkt (BadPunkt& BP)
		  : GeoFehler (BP._GO, BP._isCorrected)
{
	_lSPNr = BP._lSPNr;
	_iKaNr = BP._iKaNr;
	_BPkt = BP._BPkt;
}


//-------------------------------------------------------------------------------------------------
BadPunkt :: ~BadPunkt (void)
{
}                                


//-------------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool BadPunkt :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, BadPunkt) (*this) != NULL)
		return true;
	DEX_Error (RC_badpunkt, EC_NOMEMORY);
	return false;
}


// --------------------------------------------------------------------------------------------
// Beschreibung des unbereinigten Geometriefehlers als Merkmalstext in sAnalyseText eintragen
void BadPunkt :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
ResString resText (ResID (IDS_UNKOORD, pRF), 50);	// unbereinigter ungültiger Punkt

	if (pCT)
	{
	double XOut, YOut;	// Real-Koordinaten des fehlerhaften Punktes

		// Konvertierung der Datenbank- in Real-Koordinaten
		DBKoordInReal (_BPkt, XOut, YOut, pCT);

// !!!!! die nachfolgend herauskommentierten Zeilen müßten mit der Aussage "_isCorrected == false"
//       identisch sein !!!!! (15.05.98)
//	ObjTyp OT = _GO.isA();
	string sBuffer;

//		if (OT == OT_PUNKT ||					// Punktobjekt
//			(OT == OT_KANTE &&					// Linienobjekt, das nur (noch - evtl. durch vorhergehende
//			((Kante&)_GO).ASP() == 1) ||		//  Bereinigungen) einen Stützpunkt hat
//			(OT == OT_FLAECHE &&				// Flächenobjekt, dessen Außen- bzw. Innenkontur nur (noch - evtl.
//			((EFlaeche&)_GO).KA(_iKaNr).ASP() == 1))	//  durch vorhergehende Bereinigungen) einen Stützpunkt hat
//		{
			Format (sBuffer, "%s (%ld,%ld)\r\n", (char*)resText.Addr(), DtoL(XOut),
					DtoL(YOut));
			sAnalyseText += sBuffer;
//		}
	}
	else
		sAnalyseText += resText.Addr();

} // AnalysePuffern


//---------------------------------------------------------------------------------------------
// Bereinigung des Badpunkt-Fehlers;
// Badpunkt-Fehler werden so behandelt, daß negative Koordinaten auf 0 bzw. "zu große"
// Koordinaten auf MAXKOORD gesetzt werden, um die Datenbank-Struktur nicht zu gefährden; dies
// gilt jedoch NICHT als Bereinigung des Fehlers.
void BadPunkt :: ErrorCorrection (void)
{
	if (_isCorrected) return;

	if (OT_PUNKT == _GO.isA()/* || _lSPNr < 0*/)	// Punkt
	{
	EPunkt* pP = (EPunkt*)&_GO;

		if (pP->X() < 0)
			pP->X() = 0;
		else if (pP->X() > MAXKOORD)
			pP->X() = MAXKOORD;
		if (pP->Y() < 0)
			pP->Y() = 0;
		else if (pP->Y() > MAXKOORD)
			pP->Y() = MAXKOORD;
	}

	else if (OT_KANTE == _GO.isA())
	{
	EKante* pKt = (EKante*)&_GO;

		if (pKt->SP(_lSPNr).X() < 0)
			pKt->SP(_lSPNr).X() = 0;
		else if (pKt->SP(_lSPNr).X() > MAXKOORD)
			pKt->SP(_lSPNr).X() = MAXKOORD;
		if (pKt->SP(_lSPNr).Y() < 0)
			pKt->SP(_lSPNr).Y() = 0;
		else if (pKt->SP(_lSPNr).Y() > MAXKOORD)
			pKt->SP(_lSPNr).Y() = MAXKOORD;
	}

	else			// Fläche
	{
		_ASSERTE (_GO.isA() == OT_FLAECHE);

	EFlaeche* pFl = (EFlaeche*)&_GO;

		if (pFl->KA(_iKaNr).SP(_lSPNr).X() < 0)
			pFl->KA(_iKaNr).SP(_lSPNr).X() = 0;
		else if (pFl->KA(_iKaNr).SP(_lSPNr).X() > MAXKOORD)
			pFl->KA(_iKaNr).SP(_lSPNr).X() = MAXKOORD;
		if (pFl->KA(_iKaNr).SP(_lSPNr).Y() < 0)
			pFl->KA(_iKaNr).SP(_lSPNr).Y() = 0;
		else if (pFl->KA(_iKaNr).SP(_lSPNr).Y() > MAXKOORD)
			pFl->KA(_iKaNr).SP(_lSPNr).Y() = MAXKOORD;
	}
} // ErrorCorrection
