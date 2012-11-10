// Methoden für Geometrietest
// File: GEOMTEST.CXX
// W. Mörtl


#include "GeoReinP.hxx"

#include "BasicFunctions.hxx"	// Intersection()
#include "strecke.hxx"			// Strecke
#include "badpunkt.hxx"
#include "doppunkt.hxx"
#include "kollinea.hxx"
#include "spitze.hxx"
#include "offen.hxx"
#include "umlauf.hxx"
#include "selbinzi.hxx"
#include "kontinzi.hxx"
#include "entartet.hxx"
#include "insel_ex.hxx"
#include "insel_in.hxx"
#include "georein.hxx"			// GeoReinExtension


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



//===============================================================================================
// Test von ElementarGeoObjekten auf Geometrie-Fehler und teilweise Fehlerbereinigung.
// Die Gültigkeit von pCT wird weiter unten getestet.
bool GeoReinExtension :: GeometrieTest (GeoFehlerListe& GFL, EObjekt& EO, bool bDblCoord,
										int iFlags, string& sAnalyseText)
{
bool bRet = true;	// Objekt ist fehlerfrei bzw. konnte automatisch bereinigt werden (true)

	if (OT_PUNKT == EO.isA())
		bRet = GeoAnalyse ((EPunkt&)EO, GFL);

	else if (OT_KANTE == EO.isA())
	{
	bool dummy = false;	// Parameter für GeoAnalyse(); wird bei Test einer Kante nicht
						//  benötigt (nur bei Test von Flächenkonturen)

		bRet = GeoAnalyse ((EKante&)EO, GFL, dummy, dummy);

		if (! bRet &&
			0 == (iFlags & OGNoExtendedErrorCheck))	// Objekt kommt nicht von Geometrieoperationen i.w.S sondern vom Import
			bRet = GFL.EndLoopCorrection();
	}

	else
		bRet = GeoAnalyse ((EFlaeche&)EO, bDblCoord, GFL);

	GFL.GesamtAnalysePuffern (sAnalyseText, m_pCT);

	return bRet;

} // GeometrieTest



// --------------------------------------------------------------------------------------------
// vollständiger Geometrietest für Punkt
bool GeoReinExtension :: GeoAnalyse (EPunkt& Pkt, GeoFehlerListe& GFL, long j, int i)
{
// BadPunkt
	if (Pkt.isBad())
	{
	BadPunkt* pGeoFB = new BadPunkt (GFL.GO(), j, i);

		if (! pGeoFB)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		// Badpunkt-Fehler werden so behandelt, daß negative Koordinaten auf 0 bzw. "zu große"
		// Koordinaten auf MAXKOORD gesetzt werden
		pGeoFB->ErrorCorrection();		// fehlerhaften Punkt modifizieren
		pGeoFB->AddGeoFehler (GFL);		// Fehlermeldung in GFL sammeln
		DELETE_OBJ (pGeoFB);
		return false;
	}
	return true;

} // GeoAnalyse für Punkt


// --------------------------------------------------------------------------------------------
// vollständiger Geometrietest für Kante (Streckenzug)
bool GeoReinExtension :: GeoAnalyse (EKante& Kt, GeoFehlerListe& GFL, bool& bSInz,
									 bool& bEntart, int i)
{
ObjRechteck OC = Kt.GetCont();
DoublePair dpUF = UmrechnungsFaktor (OC.XMin(), OC.YMax(), OC.XMax(), OC.YMin(), m_pCT);

bool bRet = true;		// Objekt ist fehlerfrei bzw. Fehler wurden automatisch bereinigt (true)
bool bClosed = false;	// originale Kante geschlossen (true)
long lKL = Kt.ASP();	// Länge der Kante Kt

	if (Kt.SP(0).X() == Kt.SP(lKL-1).X() && Kt.SP(0).Y() == Kt.SP(lKL-1).Y())
		bClosed = true;	// originale Kante geschlossen

bool bNull;		// Parameter von isSpitz() bzw. isDoppel()

	for (long j = lKL-1; j >= 0; j--)
	{
// Geometriefehler bei Punkten
		if (!GeoAnalyse (Kt.SP(j), GFL, j, i))
			bRet = false;

// Spitze
		if (Kt.isSpitz (bNull, m_dSpEps, j))
		{
		Spitze* pGeoFS = new Spitze (GFL.GO(), j-1, i, bNull, m_dDPEps, dpUF, m_bMetric);

			if (! pGeoFS)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			// _isCorrected wird nicht ausgewertet
			if (m_bClear || bNull)
				pGeoFS->ErrorCorrection();		// Spitze modifizieren oder löschen
			if (! m_bClear)
				pGeoFS->AddGeoFehler (GFL);		// Fehlermeldung in GFL sammeln
			DELETE_OBJ (pGeoFS);
		}

// Kollinearität
		if (Kt.isKoll (j))
		{
		Kollinearitaet* pGeoFK = new Kollinearitaet (GFL.GO(), j-1, i);

			if (! pGeoFK)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			pGeoFK->ErrorCorrection();
			if (! m_bClear)
				pGeoFK->AddGeoFehler (GFL);	// Fehlermeldung in GFL sammeln
			DELETE_OBJ (pGeoFK);
		}

// DoppelPunkt (NACH Spitze und Kollinearität, da durch deren Bereinigung ein DoppelPunkt
//				entstehen kann, den es vorher so nicht gab)
		if (Kt.isDoppel (bNull, m_dDPEps, dpUF, m_bMetric, j))
		{
		DoppelPunkt* pGeoFD = new DoppelPunkt (GFL.GO(), j, i, bNull, m_dSpEps);

			if (! pGeoFD)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			if (m_bClear || bNull)
				pGeoFD->ErrorCorrection();		// doppelten Punkt löschen
			if (! m_bClear)
				pGeoFD->AddGeoFehler (GFL);		// Fehlermeldung in GFL sammeln

			DELETE_OBJ (pGeoFD);
		}
	} // for j


// bei ursprünglich geschlossener Kante bzw. Flächenkontur zusätzlich
	if (bClosed)
	{
		if (!ExtraTestClosedLine (Kt, GFL, i, dpUF))
			return false;
	}


// Selbstinzidenz
	bSInz = false;	// es wurden Selbstinzidenzen nicht/entdeckt (false/true)
	lKL = Kt.ASP();	// Länge der Kante Kt neu bestimmen, da sie evtl. verändert sein könnte

	// Um sinnvoll auf Selbstinzidenz zu testen, muß eine Kante mindestens aus 4 und eine
	// Flächenkontur wenigstens aus 5 Stützpunkten bestehen. Liegen weniger Punkte vor, könnte
	// als spezielle Form der Selbstinzidenz nur eine Überlappung zwischen benachbarten
	// Strecken vorliegen. Dieser Fall wird aber bei Test auf Spitzen erkannt.
	if ((i < 0 && lKL >= 4) ||		// Kante
		(i >= 0 && lKL >= 5))		// Flächenkontur
	{
	EPunkt GP1, GP2;	// eventuelle gemeinsame Punkte
	SchnittErg Fo;		// Form der Selbstinzidenz

		for (j = 0; j <= lKL-4; j++)
		{
		Strecke* pSj = new Strecke (Kt.SP(j), Kt.SP(j+1));

			if (! pSj)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			
			for (long jj = j+2; jj <= lKL-2; jj++)
			{
				// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur nächsten
				// Strecke
				if (!pSj->ContainerSchnitt (Kt.SP(jj), Kt.SP(jj+1)))
					continue;

				// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
				if (!Intersection (Kt.SP(j).X(), Kt.SP(j).Y(), Kt.SP(j+1).X(), Kt.SP(j+1).Y(),
					               Kt.SP(jj).X(), Kt.SP(jj).Y(), Kt.SP(jj+1).X(), Kt.SP(jj+1).Y()))
					continue;

				if (Kt.isSelbInz (*pSj, Kt.SP(jj), Kt.SP(jj+1), j, jj, GP1, GP2, Fo))
				{
				SelbstInzid* pGeoFI = new SelbstInzid (GFL.GO(), i, GP1, GP2, Fo);

					if (! pGeoFI)
					{
						DEX_Error (RC_geomtest, EC_NOMEMORY);
						return false;
					}

					pGeoFI->AddGeoFehler (GFL);
					bSInz = true;
					DELETE_OBJ (pGeoFI);
					bRet = false;	// Objekt enthält Fehler, der nicht automatisch bereinigt
				}					// werden kann
			}
			DELETE_OBJ (pSj);
		}
	}
	

// Entartung der Kante zu einem Punkt bzw. einer Flächenkontur zu einer Linie bzw. zu einem Punkt:
int iAnz = 2;		// min. Anzahl der Stützpunkte bei einer Kante

	if (i >= 0)
		iAnz = 4;	// min. Anzahl der Stützpunkte bei einer Flächenkontur (i = Konturindex)

	if (lKL < iAnz)
	{
	Entartung* pGeoFE = new Entartung (GFL.GO(), i);

		if (! pGeoFE)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		pGeoFE->ErrorCorrection();
		m_iOT = pGeoFE->GetOTNeu();		// evtl. Typumwandlung
//		bRet = pGeoFE->WasCorrected();	// d.h. bRet = _isCorrected (#WM021210)
		if (! pGeoFE->WasCorrected())
			bRet = false;
		pGeoFE->AddGeoFehler (GFL);		// bereinigte UND unbereinigte Fehler in GFL sammeln
		DELETE_OBJ (pGeoFE);
		bEntart = true;
	}

	return bRet;

} // GeoAnalyse für Kante


// --------------------------------------------------------------------------------------------
// zusätzlicher Test am Anfangs-/Endpunkt bei ursprünglich geschlossenen Kanten
bool GeoReinExtension :: ExtraTestClosedLine (EKante& Kt, GeoFehlerListe& GFL, int i,
											  DoublePair dpUF)
{
bool bNull;				// Parameter von isSpitz() bzw. isDoppel()
long lLastInd;			// letzter "nutzbarer" Index
long lKL = Kt.ASP();	// Länge der Kante Kt neu bestimmen, da sie evtl. reduziert worden ist

	if (lKL < 2)
		return true;

	(Kt.SP(0) == Kt.SP(lKL-1)) ? (lLastInd = lKL - 2) : (lLastInd = lKL - 1);

// Spitze am Anfangs/Endpunkt
	if (Kt.isSpitz (bNull, m_dSpEps, 1, 0, lLastInd))
	{
	Spitze* pGeoFS = new Spitze (GFL.GO(), 0, i, bNull, m_dDPEps, dpUF, m_bMetric);

		if (! pGeoFS)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		// _isCorrected wird nicht ausgewertet
		if (m_bClear || bNull)
			pGeoFS->ErrorCorrection();		// Spitze modifizieren oder löschen
		if (! m_bClear)
			pGeoFS->AddGeoFehler (GFL);		// Fehlermeldung in GFL sammeln

		DELETE_OBJ (pGeoFS);

		// bei der Korrektur einer Spitze werden MANCHMAL Stützpunkte gelöscht; deshalb einige
		// Parameter neu bestimmen (05.10.98)
		lKL = Kt.ASP();

		_ASSERTE (lKL >= 2);

		(Kt.SP(0) == Kt.SP(lKL-1)) ? (lLastInd = lKL - 2) : (lLastInd = lKL - 1);
	}


// Kollinearität am Anfangs/Endpunkt
	if (Kt.isKoll (1, 0, lLastInd))
	{
	Kollinearitaet* pGeoFK = new Kollinearitaet (GFL.GO(), 0, i);

		if (! pGeoFK)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		pGeoFK->ErrorCorrection();		// Anfangs- und Endpunkt löschen
		if (! m_bClear)
			pGeoFK->AddGeoFehler (GFL);	// bereinigte Fehler in GFL sammeln
		DELETE_OBJ (pGeoFK);
	}

// DoppelPunkt (NACH Spitze und Kollinearität, da durch deren Bereinigung ein DoppelPunkt
//				entstehen kann, den es vorher so nicht gab)
	if (Kt.isDoppel (bNull, m_dDPEps, dpUF, m_bMetric, 1, 0))	// der DoppelPunkt (0, lLastInd) wird schon
													// in SpecialRemove() in spitze.cxx abgestestet (21.01.99)
	{
// !!!!!!  die Konsequenzen der nachfolgenden Korrektur überschaue ich noch nicht so recht; es geht mir
// hier nur um die Einheitlichkeit der Behandlung aller DoppelPunkte (06.10.98)
//	DoppelPunkt* pGeoFD = new DoppelPunkt (GFL.GO(), lLastInd, i, bNull);	// 06.10.98
	DoppelPunkt* pGeoFD = new DoppelPunkt (GFL.GO(), 0, i, bNull, m_dSpEps);

		if (! pGeoFD)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		if (m_bClear || bNull)
			pGeoFD->ErrorCorrection();		// doppelten Punkt löschen
		if (! m_bClear)
			pGeoFD->AddGeoFehler (GFL);		// Fehlermeldung in GFL sammeln

		DELETE_OBJ (pGeoFD);
	}

// ist eine aus 3 Stützpunkten bestehende Kante geschlossen, dann ist der Endpunkt als
// doppelter Punkt anzusehen und entsprechend zu behandeln
bool bKtZu;		// Kante bzw. Flächenkontur immer noch geschlossen (true)

	lKL = Kt.ASP();

	_ASSERTE (lKL >= 1);

	(Kt.SP(0) == Kt.SP(lKL-1)) ? (bKtZu = true) : (bKtZu = false);

	if (3 == lKL && bKtZu)
	{
	DoppelPunkt* pGeoFD = new DoppelPunkt (GFL.GO(), lKL-1, i, bNull, m_dSpEps);

		if (! pGeoFD)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		pGeoFD->ErrorCorrection();		// doppelten Punkt löschen
		if (! m_bClear)
			pGeoFD->AddGeoFehler (GFL);	// Fehlermeldung in GFL sammeln

		DELETE_OBJ (pGeoFD);
	}

// ist eine aus 2 Stützpunkten bestehende Kante geschlossen, dann ist der Endpunkt als
// doppelter Punkt anzusehen und entsprechend zu behandeln (#HK000608),
// das kann nach einer Bereining im vorhergehenden Schritt auftreten
	lKL = Kt.ASP();
	_ASSERTE (lKL >= 1);

	if (2 == lKL && (Kt.SP(0) == Kt.SP(1)))
	{
	DoppelPunkt* pGeoFD = new DoppelPunkt (GFL.GO(), 1, i, true, m_dSpEps);

		if (! pGeoFD)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		pGeoFD->ErrorCorrection();		// doppelten Punkt löschen
		if (! m_bClear)
			pGeoFD->AddGeoFehler (GFL);	// Fehlermeldung in GFL sammeln

		DELETE_OBJ (pGeoFD);
	}

// evtl. erneutes Schließen einer durch Fehlerbereinigung jetzt offenen, aber ursprünglich
// geschlossenen Kante bzw. Flächenkontur
	lKL = Kt.ASP();

	_ASSERTE (lKL >= 1);

	(Kt.SP(0) == Kt.SP(lKL-1)) ? (bKtZu = true) : (bKtZu = false);

	if (!bKtZu &&	// Kante jetzt offen,
		lKL >= 3)	// aber mindestens aus 3 Stützpunkten (08.07.98)
		Kt.AddPunkt (&Kt.SP(0).X(), &Kt.SP(0).Y(), 1, -1);

	return true;

} // ExtraTestClosedLine


// --------------------------------------------------------------------------------------------
// vollständiger Geometrietest für Fläche (Polygon aus einem oder mehreren geschlossenen
// Streckenzügen bestehend)
bool GeoReinExtension :: GeoAnalyse (EFlaeche& Fl, bool bDblCoord, GeoFehlerListe& GFL)
{
bool bRet = true;	// Objekt ist fehlerfrei bzw. konnte automatisch bereinigt werden (true),
					// sonst false
int iKAnz = Fl.KantenAnz();	// Anzahl der Flächenkonturen

	for (int i = iKAnz-1; i >= 0; i--)	// alle Konturen einzeln abarbeiten
	{
// Kontur offen
		if (Fl.isOffen (i))
		{
		Offen* pGeoFO = new Offen (GFL.GO(), i, bDblCoord);

			if (! pGeoFO)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			pGeoFO->ErrorCorrection();		// offene Kontur (evtl.) schließen
//			bRet = pGeoFO->WasCorrected();	// false: offene Kontur wurde mit Stützpunktverlust (#WM021210)
											// geschlossen, d.h. Objekt bleibt fehlerhaft
			if (! pGeoFO->WasCorrected())	// false: offene Kontur wurde mit Stützpunktverlust
				bRet = false;				// geschlossen, d.h. Objekt bleibt fehlerhaft
//			if (!bRet || !m_bClear)			// (#WM021210)
			if (! pGeoFO->WasCorrected() || ! m_bClear)
				pGeoFO->AddGeoFehler (GFL);	// Fehlermeldung in GFL sammeln
			DELETE_OBJ (pGeoFO);
		}


// Geometriefehler bei Kanten
	bool bSInz = false,		// bei der nachfolgenden GeoAnalyse() sind Selbstinzidenzen bzw.
		 bEntart = false;	// Entartung diagnostiziert worden (true)

		if (!GeoAnalyse (Fl.KA(i), GFL, bSInz, bEntart, i))
			bRet = false;

		iKAnz = Fl.KantenAnz();		// Anzahl der Flächenkonturen neu ermitteln, da sie in
									// GeoAnalyse() verringert worden sein kann

		// aus dem gleichen Grund ist nachfolgende if-Anweisung notwenig
		if (i < iKAnz)
		{
// Umlaufsinn einer Kontur
			// bei Selbstinzidenzen und bei Entartung kann ich mir den Umlauftest sparen
			if (!bSInz && !bEntart)	// keine Selbstinzidenzen und keine Entartung
			{
				if (Fl.isWrongTurning (i))
				{
				double dFlInh = Fl.KA(i).PolygonArea();
				Umlauf* pGeoFU = new Umlauf (GFL.GO(), dFlInh, i);

					if (! pGeoFU)
					{
						DEX_Error (RC_geomtest, EC_NOMEMORY);
						return false;
					}

					pGeoFU->ErrorCorrection();
					DELETE_OBJ (pGeoFU);
				}
			}
		}
	} // for i

	
	if (1 == iKAnz)			// Fläche hat nur (noch) eine Kontur
		return bRet;


// Entartung der Fläche dadurch, daß sie keine Konturen mehr besitzt (derzeit wird keine
// automatische Bereinigung vorgenommen)
// Die mögliche Entartung der einzelnen Flächenkonturen wurde schon bei GeoAnalyse für Kante
// getestet.
	if (0 == iKAnz)		// keine Konturen mehr
	{
	Entartung* pGeoFE = new Entartung (GFL.GO(), 0);

		if (! pGeoFE)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		pGeoFE->AddGeoFehler (GFL);
		DELETE_OBJ (pGeoFE);
		return false;	// keine automatische Bereinigung
	}


// Fläche hat auch Innenkontur:
// Überschneidung von Konturen untereinander (keine Korrektur möglich)
EPunkt Rett;		// Zwischenspeicher für Berührungspunkt bzw. Wiederholungspunkt ohne Seitenwechsel
EPunkt GP1, GP2;	// eventuelle gemeinsame Punkte
SchnittErg Fo;		// Form der Konturinzidenz
bool bKontInzid = false;	// Fläche hat (mindestens) eine Konturinzidenz (true)

	for (i = 0; i < iKAnz-1; i++)	// die eine Kontur für den Überschneidungstest
	{
	long lKLi = Fl.KA(i).ASP();	// Länge der Kontur i
	ObjRechteck* pOC1 = new ObjRechteck (Fl.KA(i).GetCont());	// kleinstes umschließendes Rechtecke
	
		if (! pOC1)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		for (int ii = i+1; ii < iKAnz; ii++)	// die anderen Konturen
		{
		long lKLii = Fl.KA(ii).ASP();	// Länge der Kontur ii
		ObjRechteck* pOC2 = new ObjRechteck (Fl.KA(ii).GetCont());

			if (! pOC2)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				DELETE_OBJ (pOC1);
				return false;
			}

			if (pOC1->Durchschnitt (*pOC2))	// Container haben mind. 1 Punkt gemeinsam
			{
			long lKInzOS = 0;	// Zähler für Wiederholungs- bzw. Berührungspunkt ohne
								// Seitenwechsel
                 
				for (long j = 0; j < lKLi-1; j++)
				{
				Strecke* pSj = new Strecke (Fl.KA(i).SP(j), Fl.KA(i).SP(j+1));

					if (! pSj)
					{
						DEX_Error (RC_geomtest, EC_NOMEMORY);
						return false;
					}

					for (long jj = 0; jj < lKLii-1; jj++)
					{
						// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur
						// nächsten Strecke
						if (!pSj->ContainerSchnitt (Fl.KA(ii).SP(jj), Fl.KA(ii).SP(jj+1)))
							continue;

						// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
						if (!Intersection (Fl.KA(i).SP(j).X(), Fl.KA(i).SP(j).Y(),
											   Fl.KA(i).SP(j+1).X(), Fl.KA(i).SP(j+1).Y(),
											   Fl.KA(ii).SP(jj).X(), Fl.KA(ii).SP(jj).Y(),
											   Fl.KA(ii).SP(jj+1).X(), Fl.KA(ii).SP(jj+1).Y()))
							continue;

					bool bKI = Fl.isKontInz (Fl.KA(i).SP(j), Fl.KA(i).SP(j+1), Fl.KA(ii).SP(jj),
									  Fl.KA(ii).SP(jj+1), i, ii, j, jj, lKInzOS, GP1, GP2, Fo);
			
						// beim erstmaligen Auftreten einer Konturinzidenz ohne Seitenwechsel
						// (Stützpunktwiederholung oder Berührung) wird der Inzidenzpunkt
						// zwischengespeichert
						if (Fo == BERUE_OHNE && lKInzOS == 1)
							Rett = GP1;

						// beim 2. Auftreten einer Konturinzidenz ohne Seitenwechsel werden beide
						// Inzidenzpunkte als Fehler notiert
						if (Fo == BERUE_OHNE && lKInzOS == 2)
						{
							GP2 = GP1;
							GP1 = Rett;
						}

						if (bKI)  // Konturinzidenz wurde diagnostiziert
						{
						KonturInzid* pGeoFKI1 = new KonturInzid (GFL.GO(), i, ii, GP1, GP2, Fo);
            
							if (! pGeoFKI1)
							{
								DEX_Error (RC_geomtest, EC_NOMEMORY);
								return false;
							}

							pGeoFKI1->AddGeoFehler (GFL);
							// Beim 2. Auftreten einer Konturinzidenz ohne Seitenwechsel
							// werden beide Fehler in GFL notiert
							if (Fo == BERUE_OHNE && lKInzOS == 2)
							{
							KonturInzid* pGeoFKI2 = new KonturInzid (GFL.GO(), i, ii, GP2, GP1, Fo);

								if (! pGeoFKI2)
								{
									DEX_Error (RC_geomtest, EC_NOMEMORY);
									return false;
								}

								pGeoFKI2->AddGeoFehler (GFL);
								DELETE_OBJ (pGeoFKI2);
							}
							DELETE_OBJ (pGeoFKI1);
							bKontInzid = true;	// Fläche hat (mindestens) eine Konturinzidenz
							bRet = false;		// Objekt enthält Fehler, der nicht automatisch
												// bereinigt werden kann
						}
					}
				}
			}
		}
	}

bool bOutside = true;	// mindestens eine Innenkontur liegt außerhalb der Außenkontur (true)

	if (KonturTausch (Fl, bKontInzid, bOutside, GFL))
		return bRet;


// Lage der Konturen zueinander
	for (i = 1; i < iKAnz; i++)
	{
// Innenkontur außerhalb der Außenkontur (keine Korrektur möglich)
		if (bOutside &&
			! GFL.DieseZweiKonturen (0, i) &&	// zwischen Außenkontur (1. Parameter = 0) und i-ter
												//  Innenkontur wurde keine Konturinzidenz diagnostiziert
			Fl.isAussen (i))
		{
		InselExt* pGeoFE = new InselExt (GFL.GO(), i);

			if (! pGeoFE)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			pGeoFE->AddGeoFehler (GFL);
			DELETE_OBJ (pGeoFE);
			bRet = false;	// Objekt enthält Fehler, der nicht automatisch bereinigt werden kann
		}

		for (int ii = 1; ii < iKAnz; ii++)

// Innenkontur innerhalb einer anderen Innenkontur (keine Korrektur möglich)
			if (i != ii && 
				! GFL.DieseZweiKonturen (i, ii) &&	// zwischen i-ter und und ii-ter Innenkontur wurde
													//  keine Konturinzidenz diagnostiziert
				Fl.isInnen (i, ii))
			{
			InselInInsel* pGeoFI = new InselInInsel (GFL.GO(), i, ii);

				if (! pGeoFI)
				{
					DEX_Error (RC_geomtest, EC_NOMEMORY);
					return false;
				}

				pGeoFI->AddGeoFehler (GFL);
				DELETE_OBJ (pGeoFI);
				bRet = false;	// Objekt enthält Fehler, der nicht automatisch bereinigt
								// werden kann
			}
	}

	return bRet;

} // GeoAnalyse für Fläche


// --------------------------------------------------------------------------------------------
// Austausch der Konturen, um ggf. den Fehler, daß Innenkonturen außerhalb der Außenkontur
// liegen, zu bereinigen (return-Wert ist true, wenn Austausch erfolgreich durchgeführt wurde);
// Voraussetzung ist aber, daß keinerlei Konturinzidenzen vorliegen (bKontInzid == false)
bool GeoReinExtension :: KonturTausch (EFlaeche& Fl, bool bKontInzid, bool& bOutside,
									   GeoFehlerListe& GFL)
{
	if (bKontInzid)
		return false;	// Fl hat Konturinzidenzen

int iKCnt = Fl.KantenAnz();	// Anzahl der Flächenkonturen

	if (1 == iKCnt)
		return false;	// Fl hat nur eine Kontur

// für m_bClear == false werden auch bereinigte Fehler in der GeoFehlerListe GFL gesammelt,
// deshalb Feld für Markierung, ob i-te Innenkontur außerhalb der Außenkontur liegt (true),
// bereitstellen
bool* pbOutsideError = new bool[iKCnt];

	if (! pbOutsideError)
	{
		DEX_Error (RC_geomtest, EC_NOMEMORY);
		return false;
	}

	if (! m_bClear)		// Initialisierung von pbOutsideError
		for (int i = 1; i < iKCnt; i++)
			pbOutsideError[i] = false;

	bOutside = false;	// keine Innenkonturen außerhalb der Außenkontur

	for (int i = 1; i < iKCnt; i++)
	{
	bool bOut = Fl.isAussen (i);

		if (bOut)
			bOutside = true;

		if (m_bClear)
		{
			if (bOut)
				break;
		}
		else
			pbOutsideError[i] = true;	// i-te Innenkontur liegt außerhalb der Außenkontur
	}

	if (!bOutside)	// alle Innenkontur liegen innerhalb der Außenkontur
	{
		DELETE_VEC (pbOutsideError);
		return false;
	}

// mindestens eine Innenkontur liegt außerhalb der Außenkontur, deshalb die Kontur mit dem
// größten Flächeninhalt suchen
double dFlInhalt = -1.;
int iKInd;		// Index, der Kontur mit dem größten Flächeninhalt

	for (i = 0; i < iKCnt; i++)
	{
	double dFlInh = fabs (Fl.KA(i).PolygonArea());	// Flächeninhalt der i-ten Kontur

		if (dFlInh > dFlInhalt)
		{
			dFlInhalt = dFlInh;
			iKInd = i;
		}
	}

	if (0 == iKInd)		// die bisherige Außenkontur ist die flächenmäßig größte Kontur,
	{					// deshalb ist ein Konturtauschversuch nicht sinnvoll
		DELETE_VEC (pbOutsideError);
		return false;
	}

	// testen, ob alle "anderen" Konturen innerhalb der flächenmäßig größten Kontur liegen
	for (i = 0; i < iKCnt; i++)
	{
		if (i == iKInd)
			continue;
		if (!Fl.isInnen (i, iKInd))		// mindestens eine "andere" Kontur liegt nicht
		{								// innerhalb der flächenmäßig größten Kontur,
										// deshalb wird kein Konturtausch vorgenommen
			DELETE_VEC (pbOutsideError);
			return false;
		}
	}

	// Tausch der Außenkontur mit der iKInd-ten Innenkonturen, um den Fehler "Insel außerhalb
	// der Außenkontur" zu bereinigen
	if (Fl.TauschKante (iKInd))
	{
		Fl.OrientDreh (0);
		Fl.OrientDreh (iKInd);

		bOutside = false;	// jetzt keine Innenkonturen mehr außerhalb der Außenkontur

		if (! m_bClear)
		{
			for (int i = 1; i < iKCnt; i++)
				if (pbOutsideError[i])
				{
				InselExt* pGeoFE = new InselExt (GFL.GO(), i);

					if (! pGeoFE)
					{
						DELETE_VEC (pbOutsideError);
						DEX_Error (RC_geomtest, EC_NOMEMORY);
						return false;
					}

					pGeoFE->AddGeoFehler (GFL);
					DELETE_OBJ (pGeoFE);
				}
		}
		
		DELETE_VEC (pbOutsideError);
		return true;
	}

	DELETE_VEC (pbOutsideError);
	return false;

} // KonturTausch




// ============================================================================================
// ein verkürzter Geometrietest wird durchgeführt, wenn ein Objekt manuell editiert oder
// modifiziert (Stützpunkt hinzufügen, löschen, verschieben) wird

// --------------------------------------------------------------------------------------------
// verkürzter Geometrietest; es wird nur zurückgegeben, ob das Objekt einen Geometriefehler
// enthält, der nicht automatisch bereinigt werden kann (false), oder nicht (true);
// sinnvoll bei manueller Modifikation eines fehlerfreien Objektes durch den Awender
bool GeoReinExtension :: KurzAnalyse (IObjektGeometrie* pIOG, TestRicht trRicht, long& lSInd)
{
	_ASSERTE (pIOG != NULL);
	_ASSERTE (lSInd >= 0);

	if (!pIOG || lSInd < 0) return false;
			
short iOT;	// Objekttyp des zu testenden Objektes

	pIOG->GetObjTyp (&iOT);

	_ASSERTE (iOT == OT_KANTE || iOT == OT_FLAECHE);
	if (iOT != OT_KANTE && iOT != OT_FLAECHE) return false;

KoOrd* plXK; KoOrd* plYK;

	pIOG->GetX ((void**)&plXK);	// Pointer auf den x-Vektor
	pIOG->GetY ((void**)&plYK);	// Pointer auf den y-Vektor

bool bRet;	// return-Wert dieser Routine

	if (iOT == OT_KANTE)	// Test eines Linienobjektes
	{
	long lCnt;	// Gesamtanzahl der Stützpunkte

		pIOG->GetCnt (&lCnt);

		if (lCnt >= 2)
		{
		EKante* pKt = new EKante (plXK, plYK, lCnt);

			if (! pKt)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			bRet = KurzGeoAnalyse (pKt, trRicht, lSInd);
			DELETE_OBJ (pKt);
		}

		else if (1 == lCnt)
		{
		EPunkt* pPkt = new EPunkt (plXK[0], plYK[0]);

			if (! pPkt)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			bRet = EObjInIObjGeometrie (pPkt, pIOG);
			DELETE_OBJ (pPkt);
		}
		else
		{
			_ASSERTE (lCnt >= 1);
			bRet = false;
		}
			
		return bRet;
	}


// Test eines Flächenobjektes
short iKCnt;	// Größe des Konturfeldes
long* plCnt;	// Anzahl der Stützpunkte in Konturen

	pIOG->GetKCnt (&iKCnt);
	pIOG->GetLPCnt (&plCnt);

EFlaeche* pFl = EFlaecheErzeugen (iKCnt, plXK, plYK, plCnt);

	if (! pFl)
	{
		DEX_Error (RC_geomtest, EC_NOMEMORY);
		DELETE_OBJ (pFl);	// sicherheitshalber
		return false;
	}

int iKInd = 0;	// Index der Kontur, in der der lKSInd-te Stützpunkt liegt
long lSumm = 0;	// Anfangswert für Teilsummenbildung

	if (iKCnt > 1)	// wenigstens 1 Innenkontur
		// Index der Kontur ermitteln, in der der Stützpunkt modifiziert wurde
		for (int i = 0; i < iKCnt; i++)
		{
			if (lSInd >= lSumm && lSInd < lSumm + plCnt[i]) break;
			lSumm += plCnt [i];
			iKInd++;
		}

long lKSInd = lSInd - lSumm;	// Index des modifizierten Stützpunktes bez. der Kontur
long lCLen = plCnt[iKInd];

	if (lCLen >= 4)
	{
	bool bObjMod;	// pFl-Objekt wurde in KurzGeoAnalyse() nicht/modifiziert (false/true)

		bRet = KurzGeoAnalyse (pFl, trRicht, lKSInd, iKInd, bObjMod);

		if (bObjMod)	// pFl wurde modifiziert
		{
			lSInd = lKSInd + lSumm;			// lKSInd wurde i.d.R. auch mofdifiziert
			EObjInIObjGeometrie (pFl, pIOG);
		}

		DELETE_OBJ (pFl);
	}
	else if (lCLen >= 2 && lCLen < 4 && 1 == iKCnt && 0 == iKInd)
	{
	EKante* pKt = new EKante (plXK, plYK, lCLen);

		if (! pKt)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		bRet = EObjInIObjGeometrie (pKt, pIOG);
		DELETE_OBJ (pKt);
	}
	else
	{
		_ASSERTE (lCLen >= 2);
		_ASSERTE (iKCnt == 1);
		_ASSERTE (iKInd == 0);
		bRet = false;
	}

	return bRet;

} // KurzAnalyse


// --------------------------------------------------------------------------------------------
// verkürzter Geometrietest für Kante
// dieser Test ist dann sinnvoll, wenn nur ein einziger Stützpunkt (Index lSInd) in der Kontur
// iKInd (für eine eigentliche Kante gilt iKInd == -1) hinzugefügt, gelöscht bzw. verschoben
// wurde; trRicht gibt an, ob ausgehend vom Stützpunkt lSInd die Strecke zum nachfolgenden
// und/oder vorhergehenden Stützpunkt oder überhaupt keine Strecke auf Selbstinzidenz getestet
// werden soll
bool GeoReinExtension :: KurzGeoAnalyse (EKante* pKt, TestRicht trRicht, long& lSInd,
										 int iKInd)
{
	_ASSERTE (pKt != NULL);
	_ASSERTE (lSInd >= 0);

	if (!pKt || lSInd < 0) return false;

long lKL = pKt->ASP();	// Länge der pKt-Kante

	if (lKL >= 2 &&		// 30.10.98
		lSInd == lKL && iKInd == -1)	// letzter Stützpunkt einer eigentlichen Kante wurde
		return true;					// gelöscht hier gibt es nichts zu testen

// pKt geschlossen/offen (true/false)
bool bGeschl = AbstandPktPktE (pKt->SP(0), pKt->SP(lKL-1)) == 0;
long lIndv = lSInd - 1;	// der vorhergehende Index bez. lSInd
long lIndn = lSInd + 1;	// der nachfolgende Index bez. lSInd

	if (lSInd == 0 && bGeschl) lIndv = lKL - 2;	// Vorgänger des 1. Index
	if (lSInd == lKL-1)		// letzter Index
	{
		if (bGeschl)
		{
			lIndn = 1;		// Nachfolger des letzten Index bei geschlossener Kante
			lSInd = 0;		// Test mit "sich selbst" (jj == lSInd) beginnt bei jj == 0
		}
		else lIndn = -1;	// der letzte Index einer offenen Kante hat keinen Nachfolger
	}

// Test auf Selbstinzidenz
EPunkt GP1, GP2;	// Parameter für Routine isSelbInz(); werden
SchnittErg Fo;		// hier nicht weiter ausgewertet

	if ((trRicht == VORW || trRicht == VORRUECK) && lIndn != -1)
	{
	Strecke* pSj = new Strecke (pKt->SP(lSInd), pKt->SP(lIndn));

		if (! pSj)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		for (long jj = 0; jj < lKL-1; jj++)
		{
			if (jj == lSInd) continue;	// kein Test mit "sich selbst"

			// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur nächsten
			// Strecke
			if (!pSj->ContainerSchnitt (pKt->SP(jj), pKt->SP(jj+1)))
				continue;

			// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
			if (!Intersection (pKt->SP(lSInd).X(), pKt->SP(lSInd).Y(),
							   pKt->SP(lIndn).X(), pKt->SP(lIndn).Y(), pKt->SP(jj).X(),
							   pKt->SP(jj).Y(), pKt->SP(jj+1).X(), pKt->SP(jj+1).Y()))
				continue;

			if (pKt->isSelbInz (*pSj, pKt->SP(jj), pKt->SP(jj+1), lSInd, jj, GP1, GP2, Fo))
			{
				DELETE_OBJ (pSj);	// Objekt enthält Fehler, der nicht automatisch bereinigt
				return false;		// werden kann
			}
		}
		DELETE_OBJ (pSj);
	}

	if ((trRicht == RUECKW || trRicht == VORRUECK) && lIndv != -1)
	{
	Strecke* pSj = new Strecke (pKt->SP(lIndv), pKt->SP(lSInd));

		if (! pSj)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}
		
		for (long jj = 0; jj < lKL-1; jj++)
		{
			if (jj == lIndv) continue;	// kein Test mit "sich selbst"

			// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur nächsten
			// Strecke
			if (!pSj->ContainerSchnitt (pKt->SP(jj), pKt->SP(jj+1)))
				continue;

			// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
			if (!Intersection (pKt->SP(lIndv).X(), pKt->SP(lIndv).Y(),
							   pKt->SP(lSInd).X(), pKt->SP(lSInd).Y(), pKt->SP(jj).X(),
							   pKt->SP(jj).Y(), pKt->SP(jj+1).X(), pKt->SP(jj+1).Y()))
				continue;

			if (pKt->isSelbInz (*pSj, pKt->SP(jj), pKt->SP(jj+1), lIndv, jj, GP1, GP2, Fo))
			{
				DELETE_OBJ (pSj);	// Objekt enthält Fehler, der nicht automatisch bereinigt
				return false;		//  werden kann
			}
		}
		DELETE_OBJ (pSj);
	}


// Test auf Geometriefehler, die normalerweise automatisch bereinigt werden (DoppelPunkt,
// Spitze, Kollinearität)
ObjRechteck OC = pKt->GetCont();
DoublePair dpUF = UmrechnungsFaktor (OC.XMin(), OC.YMax(), OC.XMax(), OC.YMin(), m_pCT);
bool bNull;		// Parameter von isSpitz() bzw. isDoppel(); wird hier nicht ausgewertet

	if ((lIndv != -1 && pKt->isDoppel (bNull, m_dDPEps, dpUF, m_bMetric, lIndv, lSInd)) ||	// DoppelPunkt
		(lIndn != -1 && pKt->isDoppel (bNull, m_dDPEps, dpUF, m_bMetric, lSInd, lIndn)) ||
		(lIndv != -1 && lIndn != -1 && pKt->isSpitz (bNull, m_dSpEps, lIndv, lSInd, lIndn)) ||// Spitze
		(lIndv != -1 && lIndn != -1 && pKt->isKoll (lIndv, lSInd, lIndn)))	// Kollinearität
	{
	// Test, ob durch die automatische Bereinigung des erkannten Geometriefehlers eine
	// Entartung entstehen würde; ist dies der Fall, kann der Fehler nicht bereinigt werden;
	// das Objekt bleibt fehlerhaft
	int iAnz = 2;		// min. Anzahl der Stützpunkte bei einer Kante

		if (iKInd >= 0) iAnz = 4;	// min. Anzahl der Stützpunkte bei einer Flächenkontur
									// (iKInd = Konturindex)
		if (lKL-1 < iAnz) return false;
		pKt->SubPunkt (1, lSInd);
		return true;
	}

	return true;

} // KurzGeoAnalyse für Kante


// --------------------------------------------------------------------------------------------
// verkürzter Geometrietest für Fläche
// bObjMod = false/true: Objekt pFl wurde nicht/modifiziert
bool GeoReinExtension :: KurzGeoAnalyse (EFlaeche* pFl, TestRicht trRicht, long& lSInd,
										 int iKInd, bool& bObjMod)
{
	bObjMod = false;

	_ASSERTE (pFl != NULL);
	_ASSERTE (lSInd >= 0);
	_ASSERTE (iKInd >= 0);

	if (!pFl || lSInd < 0 || iKInd < 0) return false;

// Test auf Geometriefehler innerhalb der Flächenkontur
	if (!KurzGeoAnalyse (&pFl->KA(iKInd), trRicht, lSInd, iKInd))
		return false;

int iKAnz = pFl->KantenAnz();		// Anzahl der Konturen

// Test auf Umlaufsinn
	for (int i = 0; i < iKAnz; i++)	// alle Konturen einzeln testen
	{
		if (pFl->isWrongTurning (i))	// falschen Umlaufsinn
		{
			pFl->OrientDreh (i);		// korrigieren
			lSInd = pFl->KA(iKInd).ASP() - lSInd - 1;
			bObjMod = true;
		}
	}

	if (1 == pFl->KantenAnz())    // es existiert nur eine Kontur
		return true;

// Test auf Überschneidung der modifizierten Strecken der iKInd-ten Kontur mit den anderen
// Konturen (keine Korrektur möglich)
long lIndv = lSInd - 1;		// der vorhergehende Index bez. lSInd
long lIndn = lSInd + 1;		// der nachfolgende Index bez. lSInd
long lKLi = pFl->KA(iKInd).ASP();	// Länge der Kontur iKInd

	if (lSInd == 0) lIndv = lKLi - 2;	// Vorgänger des 1. Index
	if (lSInd == lKLi-1) lIndn = 1;		// Nachfolger des letzten Index

	if ((trRicht == VORW || trRicht == VORRUECK) &&
		KonturInzidenzfrei1 (pFl, lSInd, lIndn, iKInd) == false)
		return false;

	if ((trRicht == RUECKW || trRicht == VORRUECK) &&
		KonturInzidenzfrei1 (pFl, lIndv, lSInd, iKInd) == false)
		return false;

	return true;

} // KurzGeoAnalyse für Fläche


// --------------------------------------------------------------------------------------------
// Hilfsroutine für KurzGeoAnalyse (EFlaeche& ...)
// Test, ob zwischen der Strecke, die aus den Stützpunkten mit den Indizes lInd1 und lInd2 der
// iKInd-ten Kontur besteht, und den anderen Konturen der Fläche Fl Konzidenzfreiheit besteht;
// wenn ja, Rückgabe von true
bool GeoReinExtension :: KonturInzidenzfrei1 (EFlaeche* pFl, long lInd1, long lInd2, int iKInd)
{
	_ASSERTE (pFl != NULL);

	if (! pFl) return false;

// Container der zu testende Strecke
ObjRechteck OC1 = BuildRectangle (pFl->KA(iKInd).SP(lInd1), pFl->KA(iKInd).SP(lInd2));
// ObjRechteck* pOC1 = new ObjRechteck (AP, EP) kann nicht so ohne weiteres verwendet werden,
// da der Konstruktor voraussetzt, daß der 1. Punkt der linke untere und der 2. Punkt der
// rechte obere des umschließenden Rechtecks ist
int iKAnz = pFl->KantenAnz();	// Anzahl der Flächenkonturen

	for (int ii = 0; ii < iKAnz; ii++)	// die anderen Konturen
	{
		if (ii == iKInd) continue;	// kein Test mit "sich selbst"

	ObjRechteck* pOC2 = new ObjRechteck (pFl->KA(ii).GetCont());	// Konturcontainer

		if (! pOC2)
		{
			DEX_Error (RC_geomtest, EC_NOMEMORY);
			return false;
		}

		if (OC1.Durchschnitt(*pOC2))	// Container haben mind. 1 Punkt gemeinsam
		{
		long lKInzOS = 0;	// Zähler für Wiederholungs- bzw. Berührungspunkt ohne
							// Seitenwechsel (für Routine isKontInz())

			if (KonturInzidenzfrei2 (pFl, lInd1, lInd2, iKInd, ii, lKInzOS) == false)
			{
				DELETE_OBJ (pOC2);
				return false;
			}

			// wenn genau eine Berührung ohne Seitenwechsel erkannt wurde, muß getestet werden,
			// ob schon eine weitere von vornherein vorhanden war
			if (1 == lKInzOS)
			{
			long lKLi = pFl->KA(iKInd).ASP();	// Länge der Kontur iKInd

				for (long j = 0; j < lKLi-1; j++)
				{
					if (j == lInd1)	// diese Strecke wurde schon getestet
						continue;

					if (!KonturInzidenzfrei2 (pFl, j, j+1, iKInd, ii, lKInzOS))
					{
						DELETE_OBJ (pOC2);
						return false;
					}
				}
			}
		}

		DELETE_OBJ (pOC2);
	}

	return true;
} // KonturInzidenzfrei1


// --------------------------------------------------------------------------------------------
// Hilfsroutine für KonturInzidenzfrei1
bool GeoReinExtension :: KonturInzidenzfrei2 (EFlaeche* pFl, long lInd1, long lInd2,
											  int iKInd, int ii, long& lKInzOS)
{
	_ASSERTE (pFl != NULL);

	if (! pFl) return false;

EPunkt GP1, GP2;	// eventuelle gemeinsame Punkte } für Routine isKontInz(); wird hier nicht
SchnittErg Fo;		// Form der Konturinzidenz      }  weiter ausgewertet
long lKLii = pFl->KA(ii).ASP();	// Länge der Kontur ii
// zu testende Strecke
Strecke* pSj = new Strecke (pFl->KA(iKInd).SP(lInd1), pFl->KA(iKInd).SP(lInd2));

	if (! pSj)
	{
		DEX_Error (RC_geomtest, EC_NOMEMORY);
		return false;
	}

	for (long jj = 0; jj < lKLii-1; jj++)	// alle Strecken der ii-ten Kontur
	{
		// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
		if (!pSj->ContainerSchnitt (pFl->KA(ii).SP(jj), pFl->KA(ii).SP(jj+1)))
			continue;

		// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
		if (!Intersection (pFl->KA(iKInd).SP(lInd1).X(), pFl->KA(iKInd).SP(lInd1).Y(),
						   pFl->KA(iKInd).SP(lInd2).X(), pFl->KA(iKInd).SP(lInd2).Y(),
						   pFl->KA(ii).SP(jj).X(), pFl->KA(ii).SP(jj).Y(),
						   pFl->KA(ii).SP(jj+1).X(), pFl->KA(ii).SP(jj+1).Y()))
			continue;

	// Test mit Routine Intersection() reicht nicht aus, da eine einmalige Berührung ohne
	// Seitenwechsel (Fo == BERUE_OHNE) noch keine Konturinzidenz darstellt
	bool bKI = pFl->isKontInz (pSj->AP(), pSj->EP(), pFl->KA(ii).SP(jj), pFl->KA(ii).SP(jj+1),
							   iKInd, ii, lInd1, jj, lKInzOS, GP1, GP2, Fo);
				
		if (bKI)	// wurde Konturinzidenz erkannt, kann auf weitere Tests verzichtet werden
		{
			DELETE_OBJ (pSj);
			return false;
		}
	}

	DELETE_OBJ (pSj);
	return true;

} // KonturInzidenzfrei2


// --------------------------------------------------------------------------------------------
// vollständiger Geometrietest und Dokumentation der Geometriefehler, die nicht automatisch
// bereinigt werden können;
// sinnvoll bei Datenimport und bei manueller Modifikation eines fehlerhaften Objektes durch
// den Anwender
bool GeoReinExtension :: GeometriePutzen (IObjektGeometrie* pIOG)
{
	_ASSERTE (pIOG != NULL);

	if (! pIOG) return false;

	if (piInterlockedIncrement (&m_lSem) > 0)
	{
		piInterlockedDecrement (&m_lSem);
		return false;		// nicht mehrfach aufrufen
	}

ulong ulIdent;
short iOT, iFlags, iKCnt;
long lCnt;
KoOrd* plXK; KoOrd* plYK;
long* plCnt;

	pIOG->GetIdent (&ulIdent);
	pIOG->GetObjTyp (&iOT);
    pIOG->GetFlags (&iFlags);
    pIOG->GetCnt (&lCnt);
	pIOG->GetKCnt (&iKCnt);
    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);
	pIOG->GetLPCnt (&plCnt);

OBJGEOMETRIE OG;

	INITSTRUCT (OG, OBJGEOMETRIE);
	OG.lIdent = ulIdent;
	OG.iObjTyp = iOT;
	OG.iFlags = iFlags;
	OG.lCnt = lCnt;
	OG.iKCnt = iKCnt;
	OG.pdblX = plXK;
	OG.pdblY = plYK;
	OG.plCnt = plCnt;

bool bRet = GeometrieCheck (&OG);

	piInterlockedDecrement (&m_lSem);

	pIOG->SetIdent (OG.lIdent);
	pIOG->SetObjTyp (OG.iObjTyp);
    pIOG->SetFlags (OG.iFlags);
    pIOG->SetCnt (OG.lCnt);
	pIOG->SetKCnt (OG.iKCnt);
    pIOG->SetX (OG.pdblX);
    pIOG->SetY (OG.pdblY);
	pIOG->SetLPCnt (OG.plCnt, OG.iKCnt);

	return bRet;

} // GeometriePutzen


// --------------------------------------------------------------------------------------------
// Test, ob pIOG fehlerfrei ist (return-Wert: true);
// wird für GeometrieObjekte in schreibgeschützten Datenquellen bzw. Objektklassen benötigt
bool GeoReinExtension :: GeometrieAnalysieren (IObjektGeometrie* pIOG)
{
bool bRet = false;	// Rückkehrwert für diese Routine
short iOT;
long lCnt;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetObjTyp (&iOT);
    pIOG->GetCnt (&lCnt);
    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);

	switch (iOT)
	{
		case OT_PUNKT:
		{
			_ASSERTE (1 == lCnt);

			return PointAnalysis (EPunkt(plXK[0],plYK[0]));
		}

		case OT_KANTE:
		{
		EKante* pKt = new EKante (plXK, plYK, lCnt);

			if (! pKt)
			{
				DEX_Error (RC_geomtest, EC_NOMEMORY);
				return false;
			}

			bRet = LineAnalysis (*pKt, lCnt);
			DELETE_OBJ (pKt);
			break;		// 22.09.99
		}

		case OT_FLAECHE:
		{
		short iKCnt;
		long* plCnt;

			pIOG->GetKCnt (&iKCnt);
			pIOG->GetLPCnt (&plCnt);

		EFlaeche* pFl = EFlaecheErzeugen (iKCnt, plXK, plYK, plCnt);

			if (! pFl)
			{
				DELETE_OBJ (pFl);	// sicherheitshalber
				return false;
			}

			bRet = AreaAnalysis (*pFl, iKCnt);
			DELETE_OBJ (pFl);
			break;
		}

		default:
			_ASSERTE (OT_PUNKT == iOT || OT_KANTE == iOT || OT_FLAECHE == iOT);
	}

	return bRet;

} // GeometrieAnalysieren


// --------------------------------------------------------------------------------------------
// Test, ob Punktobjekt fehlerfrei ist (return-Wert: true)
bool GeoReinExtension :: PointAnalysis (EPunkt& Pt)
{
// BadPunkt
	if (Pt.isBad())
		return false;
	return true;

} // PointAnalysis


// --------------------------------------------------------------------------------------------
// Test, ob Linienobjekt fehlerfrei ist (return-Wert: true)
// OHNE Test auf Spitzen, Kollinearitäten und doppelte Punkte (wird in
// ReducedGeometryCleaning() getestet)
bool GeoReinExtension :: LineAnalysis (EKante& Kt, long lCnt, int i)
{
ObjRechteck OC = Kt.GetCont();
DoublePair dpUF = UmrechnungsFaktor (OC.XMin(), OC.YMax(), OC.XMax(), OC.YMin(), m_pCT);

	for (long j = lCnt-1; j >= 0; j--)
	{
// Geometriefehler bei Punkten
		if (!PointAnalysis (Kt.SP(j)))
			return false;

// Funktionalität (Spitze, Kollinearität bzw. DoppelPunkt) wird in ReducedGeometryCleaning() getestet
	}


// bei geschlossener Kante bzw. Flächenkontur zusätzlich
	if (Kt.SP(0).X() == Kt.SP(lCnt-1).X() && Kt.SP(0).Y() == Kt.SP(lCnt-1).Y())
	{
		if (!ExtraTestClosedLine (Kt, i, dpUF))
			return false;
	}


// Selbstinzidenz
	// Um sinnvoll auf Selbstinzidenz zu testen, muß eine Kante mindestens aus 4 und eine
	// Flächenkontur wenigstens aus 5 Stützpunkten bestehen. Liegen weniger Punkte vor, könnte
	// als spezielle Form der Selbstinzidenz nur eine Überlappung zwischen benachbarten
	// Strecken vorliegen. Dieser Fall wird aber bei Test auf Spitzen erkannt.
	if ((i < 0 && lCnt >= 4) ||		// Kante
		(i >= 0 && lCnt >= 5))		// Flächenkontur
	{
	EPunkt GP1, GP2;	// eventuelle gemeinsame Punkte
	SchnittErg Fo;		// Form der Selbstinzidenz

		for (j = 0; j <= lCnt-4; j++)
		{
		Strecke Strj (Kt.SP(j), Kt.SP(j+1));
			
			for (long jj = j+2; jj <= lCnt-2; jj++)
			{
				// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur nächsten
				// Strecke
				if (!Strj.ContainerSchnitt (Kt.SP(jj), Kt.SP(jj+1)))
					continue;

				// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
				if (!Intersection (Kt.SP(j).X(), Kt.SP(j).Y(), Kt.SP(j+1).X(),
								   Kt.SP(j+1).Y(), Kt.SP(jj).X(), Kt.SP(jj).Y(),
								   Kt.SP(jj+1).X(), Kt.SP(jj+1).Y()))
					continue;

				if (Kt.isSelbInz (Strj, Kt.SP(jj), Kt.SP(jj+1), j, jj, GP1, GP2, Fo))
					return false;
			}
		}
	}
	

// Entartung der Kante zu einem Punkt bzw. einer Flächenkontur zu einer Linie bzw. zu einem
// Punkt:
int iAnz;	// min. Anzahl der Stützpunkte bei einer Kante bzw. Flächenkontur

	(i < 0) ? (iAnz = 2) : (iAnz = 4);	// i: Konturindex

	if (lCnt < iAnz)
		return false;
	
	return true;

} // LineAnalysis


// --------------------------------------------------------------------------------------------
// Test, ob Flächenobjekt fehlerfrei ist (return-Wert: true)
// OHNE Test des Umlaufsinns der Konturen (wird in ReducedGeometryCleaning() getestet)
bool GeoReinExtension :: AreaAnalysis (EFlaeche& Fl, short iKCnt )
{
	for (int i = iKCnt-1; i >= 0; i--)	// alle Konturen einzeln abarbeiten
	{
// Kontur offen
		if (Fl.isOffen (i))
			return false;

// Funktionalität (Umlaufsinn) wird in ReducedGeometryCleaning() getestet

// Geometriefehler bei Kanten
		if (!LineAnalysis (Fl.KA(i), i))
			return false;
	} // for i

	if (1 == iKCnt)		// Fläche hat nur eine Kontur
		return true;

// Entartung der Fläche dadurch, daß sie keine Konturen besitzt; die mögliche Entartung der
// einzelnen Flächenkonturen wurde schon bei LineAnalysis() getestet
	if (0 == iKCnt)		// keine Konturen
		return false;

// Fläche hat auch Innenkontur:
// Überschneidung von Konturen untereinander
EPunkt GP1, GP2;	// eventuelle gemeinsame Punkte
SchnittErg Fo;		// Form der Konturinzidenz

	for (i = 0; i < iKCnt-1; i++)			// die eine Kontur für den Überschneidungstest
	{
	long lKLi = Fl.KA(i).ASP();				// Länge der Kontur i
	ObjRechteck OC1 (Fl.KA(i).GetCont());	// kleinstes umschließendes Rechtecke
	
		for (int ii = i+1; ii < iKCnt; ii++)	// die anderen Konturen
		{
		long lKLii = Fl.KA(ii).ASP();			// Länge der Kontur ii
		ObjRechteck OC2 (Fl.KA(ii).GetCont());

			if (OC1.Durchschnitt (OC2))			// Container haben mind. 1 Punkt gemeinsam
			{
			long lKInzOS = 0;	// Zähler für Konturinzidenzen (Wiederholungs- bzw.
								// Berührungspunkt) ohne Seitenwechsel
                 
				for (long j = 0; j < lKLi-1; j++)
				{
				Strecke Strj (Fl.KA(i).SP(j), Fl.KA(i).SP(j+1));

					for (long jj = 0; jj < lKLii-1; jj++)
					{
						// wenn Container der Strecken nichts gemeinsam haben, dann gleich zur
						// nächsten Strecke
						if (!Strj.ContainerSchnitt (Fl.KA(ii).SP(jj), Fl.KA(ii).SP(jj+1)))
							continue;

						// wenn Strecken nichts gemeinsam haben, dann gleich zur nächsten Strecke
						if (!Intersection (Fl.KA(i).SP(j).X(), Fl.KA(i).SP(j).Y(),
										   Fl.KA(i).SP(j+1).X(), Fl.KA(i).SP(j+1).Y(),
										   Fl.KA(ii).SP(jj).X(), Fl.KA(ii).SP(jj).Y(),
										   Fl.KA(ii).SP(jj+1).X(), Fl.KA(ii).SP(jj+1).Y()))
							continue;

						if (!Fl.isKontInz (Fl.KA(i).SP(j), Fl.KA(i).SP(j+1),
										   Fl.KA(ii).SP(jj), Fl.KA(ii).SP(jj+1),
										   i, ii, j, jj, lKInzOS, GP1, GP2, Fo))
							return false;
					}
				}
			}
		}
	}

// Lage der Konturen zueinander
	for (i = 1; i < iKCnt; i++)
	{
// Innenkontur außerhalb der Außenkontur
		if (Fl.isAussen (i))
			return false;

// Innenkontur innerhalb einer anderen Innenkontur
		for (int ii = 1; ii < iKCnt; ii++)
			if (Fl.isInnen (i, ii))
				return false;
	}

	return true;

} // AreaAnalysis


// --------------------------------------------------------------------------------------------
// zusätzlicher Test am Anfangs-/Endpunkt bei geschlossenen Kanten
bool GeoReinExtension :: ExtraTestClosedLine (EKante& Kt, int i, DoublePair dpUF)
{
bool bNull;				// Parameter von isSpitz() bzw. isDoppel()
long lLastInd;			// letzter "nutzbarer" Index
long lKL = Kt.ASP();	// Länge der Kante Kt

	(Kt.SP(0) == Kt.SP(lKL-1)) ? (lLastInd = lKL - 2) : (lLastInd = lKL - 1);

// Spitze am Anfangs/Endpunkt
	if (Kt.isSpitz (bNull, m_dSpEps, 1, 0, lLastInd))
		return false;

// Kollinearität am Anfangs/Endpunkt
	if (Kt.isKoll (1, 0, lLastInd))
		return false;

// DoppelPunkt
	if (Kt.isDoppel (bNull, m_dDPEps, dpUF, m_bMetric, 1, 0))
		return false;

	// ist eine aus 3 Stützpunkten bestehende Kante geschlossen, dann ist der Endpunkt als
	// doppelter Punkt anzusehen
	if (3 == lKL)
		return false;

	return true;

} // ExtraTestClosedLine
