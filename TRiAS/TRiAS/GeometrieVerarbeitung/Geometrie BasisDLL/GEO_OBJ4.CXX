// Weitere Methoden für Elementarobjekt EFlaeche
// File: GEO_OBJ4.CXX
// W. Mörtl


#include "GeometrP.hxx"

#include "cliplist.hxx"
#include "ErrorCorrection.hxx"	// PartialCleaningForLines()


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/*
#define _DEBUG_HEAP
#if defined(_DEBUG_HEAP)
//debughilfe
#include <malloc.h>
bool HEAPCHECK (void)
{
int iStatus = _heapchk();

	if (iStatus != _HEAPOK) 
	{
		_ASSERTE (iStatus == _HEAPOK);
		return false;	// hierauf den Breakpoint setzen; bei Fehler wird hier angehalten !!!!!
	}

return true;
}
#else
#define HEAPCHECK()
#endif
*/



// ============================================================================================
// Methoden für das ElementarObjekt: EFLAECHE
// Innenkontur(en) einer Fläche löschen
// 1 <= iAnzahl < _Size Innenkonturen werden ab Konturindex 1 <= iIndex < _Size gelöscht;
// für iIndex == -1 wird letzte Innenkontur gelöscht
// sollen mehr Innenkonturen gelöscht werden als vorhanden sind, werden die Innenkonturen ab
// iIndex bis zur letzten gelöscht
void _GEOMETR_EXPORT EFlaeche :: SubKante (int iAnzahl, int iIndex)
{
	_ASSERTE (iAnzahl >= 1);
	_ASSERTE (iAnzahl < _Size);
	_ASSERTE (iIndex >= -1);
	_ASSERTE (iIndex != 0);
	_ASSERTE (iIndex < _Size);

	if (iIndex == -1 && _Size > 1)   // letzte Innenkontur löschen
		iIndex = _Size-1;

	if (_Size - iIndex < iAnzahl)		// es sollen mehr Innenkonturen gelöscht werden
		iAnzahl = _Size - iIndex;		// als ab iIndex noch vorhanden sind

	if (1 == _Size  // keine Innenkonturen
	    || iAnzahl < 1 || iAnzahl > _Size -1
	    || iIndex < 1 || iIndex > _Size -1)
	{
		DEX_Error (RC_SubKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::SubKante", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	for (int i = iIndex; i < _Size-iAnzahl; i++)
		_KAF[i] = _KAF[i+iAnzahl];

	_Size -= iAnzahl;

} // SubKante


// --------------------------------------------------------------------------------------------
// Punkt(e) in einer der Flächenkonturen löschen
// Len > 0 Punkte werden ab Stützpunktnummer 0 <= KIndex < _KAF[MIndex-1].ASP() gelöscht;
// 1 <= MIndex <= _Size ist der Konturindex
void _GEOMETR_EXPORT EFlaeche :: SubPunkt (long Len, long KIndex, int MIndex)
{
	_ASSERTE (Len > 0);
	_ASSERTE (KIndex >= 0);
	_ASSERTE (MIndex >= 1);
	_ASSERTE (MIndex <= _Size);

	if (MIndex < 1 || MIndex > _Size)		// unerlaubte Parameter
	{
		DEX_Error (RC_SubPunktMasche, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::SubPunkt/I", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	
	if (MIndex == 1)	// Außenkontur
	{
		if (_KAF[0].ASP() <= Len)	// es müßte die komplette Außenkontur gelöscht werden
		{
			DEX_Error (RC_SubPunktMasche, EC_ILLPARS);	// das geht aber nicht !!!
			MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::SubPunkt/II", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
			return;
		}
		else
			_KAF[MIndex-1].EKante :: SubPunkt (Len, KIndex);
	}
	else				// Innenkontur
	{
		if (_KAF[MIndex-1].ASP() <= Len)	// es wird eine komplette Innenkontur gelöscht
			SubKante (1, MIndex-1);
		else
			_KAF[MIndex-1].EKante :: SubPunkt (Len, KIndex);
	}
} // EFlaeche :: SubPunkt


// --------------------------------------------------------------------------------------------
// Außenkontur und i-te Innenkontur werden getauscht, d.h. die i-te Innenkontur wird zur
// Außenkontur; wenn der Tausch erfolgreich war, wird true zurückgegeben, sonst false
bool _GEOMETR_EXPORT EFlaeche :: TauschKante (int i)
{
	_ASSERTE (i >= 0);
	_ASSERTE (i < _Size);

	if (i < 0 || i >= _Size)
		return false;

EFlaeche* pNewOut = new EFlaeche (&_KAF[i], 1);	// neue Außenkontur
EFlaeche* pNewIn = new EFlaeche (&_KAF[0], 1);	// neue Innenkontur

	if (!pNewOut || !pNewIn)
	{
		DELETE_VEC (pNewOut);
		DEX_Error (RC_geo_obj4, EC_NOMEMORY);
		return false;
	}

	SubKante (1, i);			// i-te Innenkontur löschen
	AddKante (*pNewOut, 1, 0);	// neue Außenkontur hinzufügen
	SubKante (1, 1);			// alte Außenkontur löschen
	AddKante (*pNewIn, 1, -1);	// neue Innenkontur hinzufügen

	DELETE_OBJ (pNewOut);
	DELETE_OBJ (pNewIn);

	return true;

} // TauschKante


// --------------------------------------------------------------------------------------------
// Test auf Geometriefehler
// Kontur einer Fläche ist offen (true), d.h. 1. und letzter Punkt sind verschieden, sonst
// false; 0 <= i < _Size ist Konturindex
bool _GEOMETR_EXPORT EFlaeche :: isOffen (int i)
{
	_ASSERTE (i >= 0);
	_ASSERTE (i < _Size);

	if (i < 0 || i >= _Size)
		return false;

long lKCnti = _KAF[i].ASP();  // Länge der i-ten Kontur

	if (lKCnti <= 2)	// eine entartete Kontur wird an anderer Stelle angemeckert und ist
		return false;	// durch Schließen nicht mehr zu retten (08.09.98)

double hw = AbstandPktPktE (_KAF[i].SP(0), _KAF[i].SP(lKCnti-1));

//	return ((lKCnti >= 2) && (hw > 0));
	return (hw > 0);	// 08.09.98

} // isOffen


// --------------------------------------------------------------------------------------------
// Umlaufsinn einer Kontur fehlerhaft (true), sonst false;
// Außenkontur muß mathematisch positiv, Innenkonturen müssen mathematisch negativ orientiert
// sein (durch Berechnung des vorzeichenbehafteten Flächeninhaltes FlInh eines geschlossenen
// Polygonzuges); 0 <= i < _Size ist der Konturindex
bool _GEOMETR_EXPORT EFlaeche :: isWrongTurning (int i)
{
	_ASSERTE (i >= 0);
	_ASSERTE (i < _Size);

	if (i < 0 || i >= _Size)
		return false;

double dFlInh = _KAF[i].PolygonArea();

	return ((i == 0 && dFlInh <= 0.0) ||	// Außenkontur
			(i > 0 && dFlInh >= 0.0));		// Innenkontur(en)
} // isWrongTurning


// --------------------------------------------------------------------------------------------
// Umlaufsinn einer Kontur umorientieren (0 <= i < _Size ist der Konturindex)
void _GEOMETR_EXPORT EFlaeche :: OrientDreh (int i)
{
	_ASSERTE (i >= 0);
	_ASSERTE (i < _Size);

long lKCnti = _KAF[i].ASP();

	if (i < 0 || i >= _Size)
	{
		DEX_Error (RC_OrientDreh, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::OrientDreh", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	for (long k = 0; k < lKCnti/2; k++)
	{
	KoOrd x = _KAF[i].SP(lKCnti-k-1).X();
	KoOrd y = _KAF[i].SP(lKCnti-k-1).Y();

		_KAF[i].SP(lKCnti-k-1).X() = _KAF[i].SP(k).X();
		_KAF[i].SP(lKCnti-k-1).Y() = _KAF[i].SP(k).Y();
		_KAF[i].SP(k).X() = x;
		_KAF[i].SP(k).Y() = y;
	}
} // OrientDreh


// --------------------------------------------------------------------------------------------
// Test auf Überschneidung zwischen den Konturen (return-Wert: true), sonst false
// mit Rückgabewert Fo
//   KEINE      keine Überschneidung, GP1 und GP2 unbestimmt
//   ECHT       Überschneidung, so daß Schnittpunkt GP1 jeweils im "Inneren" der beiden
//              betr. Konturstrecken liegt, GP2 unbestimmt
//   RAND_MIT   Überschneidung, so daß Schnittpunkt GP1 bei beiden betr. Konturen ein
//              Stützpunkt ist (Stützpunktgleichheit mit Seitenwechsel), GP2 unbestimmt
//   INNEN_MIT  Überschneidung, so daß Schnittpunkt GP1 bei einer Kontur ein Stützpunkt,
//              bei der anderen im "Inneren" einer Konturstrecke liegt (Berührungspunkt
//              mit Seitenwechsel), GP2 unbestimmt
//   UEBERLAPP  Überlappung von Strecken beider Konturen, GP1 und GP2 sind die beiden
//              Endpunkte des gemeinsamen Bereiches
//   BERUE_OHNE Konturinzidenz (Stützpunktgleichheit bzw. Berührung) ohne Seitenwechsel,
//              betreffender Punkt in GP1, GP2 ist unbestimmt
//   i, ii sind Indizes der zu vergleichenden Konturen, j, jj die Indizes der Stützpunkte,
//   KonInzOS	Zähler für Stützpunktwiederholung bzw. Berührung ohne Seitenwechsel
bool _GEOMETR_EXPORT EFlaeche :: isKontInz (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2, EPunkt& EP2,
											int i, int ii, long j, long jj, long& KonInzOS,
											EPunkt& GP1, EPunkt& GP2, SchnittErg& Fo)
{
	_ASSERTE (i >= 0);
	_ASSERTE (ii >= 0);
	_ASSERTE (j >= 0);
	_ASSERTE (jj >= 0);

// warum ich am 02.10.98 nachfolgende Routine nehmen wollte, weiß ich nicht mehr; aber heute am
// 17.11.98 merke ich, daß dies nicht geht; wenn ich bei der Erzeugung von Objekten (z. B. in
// ObjOper.ext) und den dazugehörigen Tests mit
//  Aufbereitung2 / Aufbereitung / KantenSchnitt / GemeinsamePunkte (...,DoublePair,DoublePair)
// arbeite, muß ich es hier auch tun, d. h. auch Epsilon-Toleranzen zulassen

//	Fo = GemeinsamePunkte (AP1, EP1, AP2, EP2, GP1, GP2);

DoublePair DP1, DP2;

	Fo = GemeinsamePunkte (AP1, EP1, AP2, EP2, DP1, DP2);     // Fo == KEINE ... UEBERLAPP

	GP1.X() = DtoL (DP1.X());
	GP1.Y() = DtoL (DP1.Y());
	GP2.X() = DtoL (DP2.X());
	GP2.Y() = DtoL (DP2.Y());

	// Stützpunktwiederholungen werden immer 4-mal, Berührungspunkte immer doppelt erkannt,
	// wobei nur der Fall GP1 == EP1 && GP1 == EP2 als der einzig relevante angesehen wird
	if ((Fo == RAND || Fo == INNEN) && (GP1 == AP1 || GP1 == AP2))	// nun wohl doch wieder (02.10.98)
	{
		Fo = KEINE;
		return false;
	}

bool ksw = false;	// kein Seitenwechsel (true), sonst false

	// Vorarbeiten für Test auf Stützpunktwiederholung bzw. Berührungspunkt
	if (Fo == RAND || Fo == INNEN)
	{
	EPunkt Pj2, Pjj2;
	double qwj1, qwj2, qwjj1, qwjj2;	// Quasi-Winkel von Strecken mit der Waagrechten

		if (j < _KAF[i].ASP()-2)
			Pj2 = _KAF[i].SP(j+2);
		else
			Pj2 = _KAF[i].SP(1);
		if (jj < _KAF[ii].ASP()-2)
			Pjj2 = _KAF[ii].SP(jj+2);
		else
			Pjj2 = _KAF[ii].SP(1);
			
		qwj1 = QuasiWinkel (GP1.X(), GP1.Y(), AP1.X(), AP1.Y());
		qwjj1 = QuasiWinkel (GP1.X(), GP1.Y(), AP2.X(), AP2.Y());

		if (Fo == RAND)    // Stützpunktwiederholung
		{
			qwj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pj2.X(), Pj2.Y());
			qwjj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pjj2.X(), Pjj2.Y());
		}
		else
		{
			// Bei Berührung muß unterschieden werden, ob Endpunkt von i-Strecke innerhalb der
			// ii-Strecke liegt (GP1 == SP(j+1) oder Endpunkt von ii-Strecke innerhalb der
			// i-Strecke (GP1 == SP(jj+1)
			if (EP1.EpsGleich(DP1))
			{
				qwj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pj2.X(), Pj2.Y());
				qwjj2 = QuasiWinkel (GP1.X(), GP1.Y(), EP2.X(), EP2.Y());
			}
			else
			{
				qwj2 = QuasiWinkel (GP1.X(), GP1.Y(), EP1.X(), EP1.Y());
				qwjj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pjj2.X(), Pjj2.Y());
			}
		}

		// Sind zwei Quasi-Winkel gleich, dann ist die diagnostizierte Stützpunktwiederholung
		// bzw. Berührung nicht echt, sondern nur ein Endpunkt einer Konturüberlappung
		if (qwj1 == qwjj1 || qwj1 == qwjj2 || qwj2 == qwjj1 || qwj2 == qwjj2)
		{
			Fo = KEINE;
			return false;
		}

	double kj, kjj, gj, gjj;	// die kleineren bzw. größeren der beiden j- bzw. jj-Winkel

		// Ermittlung der jeweils kleineren bzw. größeren der beiden j- bzw. jj-Winkel
		if (qwj1 < qwj2) { kj = qwj1; gj = qwj2; }
		else { kj = qwj2; gj =qwj1; }
		if (qwjj1 < qwjj2) { kjj = qwjj1; gjj = qwjj2; }
		else { kjj = qwjj2; gjj =qwjj1; }

		// kein Seitenwechsel (true)
		ksw = (gj < kjj || (kj < kjj && gjj < gj) ||
		       gjj < kj || (kjj < kj && gj < gjj));
	}

	// Stützpunktwiederholungen (Fo == RAND) bzw. Berührung (Fo == INNEN) mit Seitenwechsel
	// werden immer als Fehler gemeldet (bleibt Fo = RAND bzw. Fo = INNEN), ohne Seitenwechsel
	// erst dann, wenn dieser Fall wenigstens zweimal aufgetreten ist; dabei wird nicht mehr
	// zwischen Stützpunktwiederholung und Berührung unterschieden (Fo == BERUE_OHNE). Ist die
	// geordnete Folge der Quasi-Winkel zwischen j und jj nicht alternierend, dann liegt
	// Seitenwechsel vor
	if ((Fo == RAND || Fo == INNEN) && ksw)
	{
		KonInzOS++;
		Fo = BERUE_OHNE;
	}

	// eine einzige Konturinzidenz (Stützpunktwiederholung bzw. Berührung ohne Seitenwechsel)
	// ist noch kein Fehler, erst das mehrmalige Auftreten
	if (Fo == KEINE || (Fo == BERUE_OHNE && KonInzOS == 1))
		return false;
	return true;

} // isKontInz


// --------------------------------------------------------------------------------------------
// Test, ob Innenkontur i, die die Außenkontur nicht echt schneidet, außerhalb der Außenkontur
// liegt (true), sonst false
bool _GEOMETR_EXPORT EFlaeche :: isAussen (int i)
{
	_ASSERTE (i >= 1);			// Index einer Innenkontur
	_ASSERTE (i < _Size);

	if (i < 1 || i >= _Size)	// kein Index einer Innenkontur
		return false;
		
	if (_KAF[0].ASP() < 4)		// Außenkontur hat zu wenig Stützpunkte
		return false;

long lCntKi = _KAF[i].ASP();	// Länge der i-ten Kontur

	for (long j = 0; j < lCntKi; j++)
	{
	Posit posLage = _KAF[i].SP(j).Position (&_KAF[0], dGlEps);

		if (INNERH == posLage)
			return false;
		if (AUSSERH == posLage)
			return true;
		if (OFFEN == posLage)	// Außenkontur nicht geschlossen
			return false;
	}

	// dieser Progammteil dürfte nur erreicht werden, wenn alle _KAF[i]-Stützpunkte auf der
	// _KAF[0]-Außenkontur liegen; diese Konturinzidenz wurde aber von vornherein
	// ausgeschlossen;
	// mit der Assertion wird der Fall abgefangen, daß die _KAF[i]-Kontur nur aus einem
	// Stützpunkt besteht (entartete Kontur), der genau auf der _KAF[0]-Außenkontur liegt
	_ASSERTE (lCntKi <= 1);

	return false;

} // isAussen


// --------------------------------------------------------------------------------------------
// Test, ob Kontur i1 (kann auch die Außenkontur sein), die die Innenkontur i2 nicht echt
// schneidet, innerhalb von i2 liegt (true), sonst false
bool _GEOMETR_EXPORT EFlaeche :: isInnen (int i1, int i2)
{
	_ASSERTE (i1 >= 0);		// Index einer Kontur
	_ASSERTE (i1 < _Size);
	_ASSERTE (i2 >= 1);		// Index einer Innenkontur
	_ASSERTE (i2 < _Size);

	if (i1 < 0 || i1 >= _Size || i2 < 1 || i2 >= _Size	// kein Index einer Kontur
	    || i1 == i2)									// Test mit sich selbst
		return false;
		
	if (_KAF[i2].ASP() < 4)		// i2-Innenkontur hat zu wenig Stützpunkte
		return false;

long lCntKi1 = _KAF[i1].ASP();	// Länge der i1-ten Kontur

	for (long j = 0; j < lCntKi1; j++)
	{
	Posit posLage = _KAF[i1].SP(j).Position (&_KAF[i2]);

		if (INNERH == posLage)
			return true;
		if (AUSSERH == posLage)
			return false;
		if (OFFEN == posLage)	// i2-Innenkontur nicht geschlossen
			return false;
	}

	// dieser Progammteil dürfte nur erreicht werden, wenn alle _KAF[i1]-Stützpunkte auf der
	// _KAF[i2]-Kontur liegen; diese Konturinzidenz wurde aber von vornherein ausgeschlossen;
	// mit der Assertion wird der Fall abgefangen, daß die _KAF[i1]-Kontur nur aus einem
	// Stützpunkt besteht (entartete Kontur), der genau auf der _KAF[i2]-Außenkontur liegt
	_ASSERTE (lCntKi1 <= 1);

	return false;

} // isInnen


// --------------------------------------------------------------------------------------------
// Umlaufsinn aller Konturen einer Fläche prüfen und ggf. richtig drehen,
// falls der Flächeninhalt der Fläche bzw. einer Insel 0 ist, Rückgabe von false 
bool _GEOMETR_EXPORT EFlaeche :: Umlaufsinn (void)
{
	for (int i = 0; i < _Size; i++)
	{
	double dFlInh = _KAF[i].PolygonArea();	// vorzeichenbehafteter Flächeninhalt

		if (0 == dFlInh)   // entartete oder fehlerhafte Fläche
			return false;

		if ((i == 0 && dFlInh < 0) ||	// Außenkontur math. negativ bzw.
			(i > 0 && dFlInh > 0))		// Innenkontur math. positiv orientiert
			OrientDreh (i);			// Konturumlaufsinn umdrehen
	}
	return true;

} // Umlaufsinn


// --------------------------------------------------------------------------------------------
// Lage der this-Fläche bezüglich der Fläche pFl; es werden sowohl von der this-Fläche als auch
// von pFl Inseln mit berücksichtigt, d.h. liegt this-Fläche innerhalb einer pFl-Insel, dann
// liegt this-Fläche außerhalb von pFl sowie umgekehrt
Posit _GEOMETR_EXPORT EFlaeche :: EnthaltenIn (EFlaeche* pFl, void* pPSt)
{
	_ASSERTE (pFl != 0);	// pPSt kann 0 sein

	if (! pFl) return UNKLAR;

ObjRechteck OC1 = GetCont();
ObjRechteck OC2 = pFl->GetCont();

	if (OC1.Durchschnitt (OC2) == false)
		return AUSSERH;		// Container haben keinen Punkt gemeinsam

int iKAnz = pFl->KantenAnz();		// Anzahl der Konturen von pFl
bool bOverlap;   // Parameter von KantenPosit(); werden
int iTouchOut;	// hier nicht ausgewertet
Posit posLage;	// Ergebnis der Routine KantenPosit
bool bInnenB = false;	// this-Fläche liegt zur pFl-Außenkontur INNERHB (true) oder nicht
						// (false)
bool bAussenB = false;	// this-Fläche liegt zu mindestens einer pFl-Innenkontur AUSSERHB
						// (true)
bool bLeer;				// Container der beiden in Aufbereitung2() verglichenen Objekte sind
						// durchschnittsleer (true)
bool bAbbr;				// Parameter von Routine Aufbereitung2(); wird hier nicht ausgewertet

// Feld für die Indizes der pFl-Inseln, die noch mit den this-Inseln zu vergleichen sind
int k = 0;	// Laufindex für piInsel
int* piInsel = new int[iKAnz];	

	if (! piInsel)
	{
		DEX_Error (RC_geo_obj4, EC_NOMEMORY);
		return UNKLAR;
	}
	memset (piInsel, 0 , iKAnz*sizeof(int));

   	for (int i = 0; i < iKAnz; i++)	// Test mit allen pFl-Konturen
	{											// (Außen- und Innenkontur)
	// pML1 muß in die for-Schleife, da dieses Variable in Aufbereitung2() verändert wird
	MarkLine* pML1 = new MarkLine (_KAF[0].ASP(), 0);
	MarkLine* pML2 = new MarkLine (pFl->KA(i).ASP(), i, true/*, 0 == i*/);

		if (!pML1  || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_EnthaltenInMasche, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			DELETE_VEC (piInsel);
			return UNKLAR;
		}

		if (!_KAF[0].Aufbereitung2 (&pFl->KA(i), pML1, pML2, bLeer, bAbbr, pPSt))
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);

			// bLeer == true bedeutet, daß der Container der i-ten pFl-Kontur und Container der
			// Außenkontur der this-Fläche durchschnittsleer sind. Für Außenkontur (i == 0)
			// wurde dies schon oben abgefangen. Hier kann der Fall nur noch bei Innenkonturen
			// auftreten (i > 0). Dabei ist die Lage noch nicht klärbar.
			if (bLeer) continue;

			// false-Rückgabe von Aufbereitung2() bedeutet Abbruch durch den Anwender, falsche
			// Parameter oder unzureichender dynamischer Speicher
			DELETE_VEC (piInsel);
			return UNKLAR;
		}

		posLage = KantenPosit (&pFl->KA(i), pML1, bOverlap, iTouchOut);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		if (0 == i)			// pFl-Außenkontur
		{
			// wird pFl-Außenkontur von this-Außenkontur umschlossen bzw. wenn beide
			// Außenkonturen identisch sind, muß (wenn vorhanden) noch Test mit
			// this-Innenkonturen durchgeführt werden
			if (UMSCHL == posLage || UMSCHLB == posLage ||
				KONTUR == posLage ||		// 16.06.98
				GLEICH == posLage)			// 15.04.99
				break;
				
			// Test mit pFl-Innenkonturen (i > 0) nur erforderlich, wenn der Test mit der
			// pFl-Außenkontur posLage == INNERH oder posLage == INNERHB ergeben hat
			if (INNERH != posLage && INNERHB != posLage)
			{
				DELETE_VEC (piInsel);
				return posLage;
			}
			if (INNERHB == posLage)
				bInnenB = true;
		}
			
		if (i > 0)			// pFl-Innenkonturen wurden noch mit herangezogen
		{
			// für INNERH, INNERHB, INNAUSS, KONTUR, GLEICH und UNKLAR ist alles klar
			if (INNERH == posLage || INNERHB == posLage || INNAUSS == posLage ||
				KONTUR == posLage || GLEICH == posLage || UNKLAR == posLage)
			{
				DELETE_VEC (piInsel);
				if (INNERH == posLage)	// vollständig innerhalb einer pFl-Insel heißt
					return AUSSERH;		//  außerhalb der pFl-Fläche
				if (INNERHB == posLage)	// innerhalb der pFl-Außenkontur, aber bez. einer
					return AUSSERHB;	//  pFl-Insel INNERHB bedeutet AUSSERHB
				if (KONTUR == posLage)	// vollständig auf einer pFl-Insel heißt AUSSERHB
					return AUSSERHB;	//  bez. der pFl-Fläche (16.07.98)
				return posLage;
			}
				
			// für AUSSERH, AUSSERHB, UMSCHL bzw. UMSCHLB der this-Außenkontur bez. einer
			// pFl-Insel ist posLage noch nicht eindeutig klärbar
			if (AUSSERHB == posLage)
				bAussenB = true;

			if (UMSCHL == posLage || UMSCHLB == posLage)	// 16.10.98
			{
				piInsel[k] = i;
				k++;
			}
		}
	} // for
	
	// dieser Programmteil wird nur erreicht, wenn
	// 1. this- und pFl-Außenkontur identisch sind
	// 2. this-Fläche innerhalb der pFl-Außenkontur liegt
	//    a) und bez. aller pFl-Innenkonturen AUSSERH bzw. AUSSERHB gilt;
	//       dann gilt bez. der pFl-Außenkontur INNERHB (bInnenB == true) oder bez. der
	//       pFl-Innenkonturen mindestens einmal AUSSERHB (bAussenB == true), dann gilt bez.
	//       der gesamten pFl-Fläche INNERHB, sonst INNERH
	//    b) und bez. der pFl-Innenkonturen mindestens einmal UMSCHL bzw. UMSCHLB gilt;
	//       dann gilt
	//       INNERH,  wenn zu allen diesen pFl-Innenkonturen mit UMSCHL auch this-Innenkonturen
	//                mit UMSCHL existieren
	//       INNERHB, wenn UMSCHLB bzw. KONTUR
	//       INNAUSS  in allen übrigen Fällen
	// 3. pFl-Fläche innerhalb der this-Außenkontur liegt (i == 0 und posLage == UMSCHL oder
	//    UMSCHLB); dann ist die gleiche Prozedur zwischen pFl->KA(0) und allen Innenkonturen
	//    der this-Fläche durchzuführen (so die this-Fläche überhaupt Innenkonturen besitzt),
	//    innerhalb derer ja die pFl-Fläche liegen könnte
	
	// >>>>> 1. Fall: this- und pFl-Außenkontur sind identisch
	if (0 == i && (KONTUR == posLage || GLEICH == posLage))
	{
		DELETE_VEC (piInsel);
		return BeideAussenkonturenIdentisch (pFl, iKAnz);
	}
	
	// >>>>> 2. Fall: this-Fläche innerhalb der pFl-Außenkontur
	if (i > 0 || (UMSCHL != posLage && UMSCHLB != posLage))
	{
		if (0 == piInsel[0])	// 19.10.98
		{
			DELETE_VEC (piInsel);
			if (bAussenB || bInnenB)
				return INNERHB;
			return INNERH;
		}

		// noch weitere Tests mit den this-Innenkonturen (so sie vorhanden sind)
		if (_Size > 1)
			posLage = EnthaltenInWeiter (pFl, piInsel);
		DELETE_VEC (piInsel);
		return posLage;
	}

	// >>>>> 3. Fall: pFl-Fläche innerhalb der this-Außenkontur
	if (1 == _Size)		// this-Fläche hat keine Innenkonturen
		return posLage;
		
	if (UMSCHL == posLage)
		bInnenB = false;
	else	// posLage == UMSCHLB
		bInnenB = true;

	// da die this-Außenkontur die pFl-Fläche umschließt, gibt es für die Lage der this-Fläche
	// bezüglich der pFl-Fläche nur noch die beiden Möglichkeiten:
	// - AUSSERH bzw. AUSSERHB, wenn die pFl-Fläche vollständig innerhalb einer this-Insel liegt
	// - INNAUSS ansonsten
   	for (i = 1; i < _Size; i++)	// Test mit allen this-Innenkonturen reicht aus, da schon klar
	{							//  ist, daß pFl-Fläche innerhalb der this-Außenkontur liegt
	MarkLine* pML1 = new MarkLine (pFl->KA(0).ASP(), 0);
	MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_EnthaltenInMasche, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return UNKLAR;
		}

		if (!pFl->KA(0).Aufbereitung2 (&_KAF[i], pML1, pML2, bLeer, bAbbr, 0))
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);

			// bLeer == true bedeutet, daß der Container der i-ten this-Kontur und Container
			// der pFl-Außenkontur durchschnittsleer sind. Bei den hier nur noch herangezogenen
			// Innenkonturen (i > 0) ist die Lage noch nicht klärbar.
			if (bLeer) continue;

			// false-Rückgabe von Aufbereitung2() bedeutet Abbruch durch den Anwender, falsche
			// Parameter oder unzureichender dynamischer Speicher
			return UNKLAR;
		}

		posLage = KantenPosit (&_KAF[i], pML1, bOverlap, iTouchOut);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		// für INNERH, INNERHB, INNAUSS, KONTUR, GLEICH, UMSCHL, UMSCHLB und UNKLAR ist alles
		// klar
		if (INNERH == posLage || INNERHB == posLage || INNAUSS == posLage || KONTUR == posLage ||
			GLEICH == posLage || UMSCHL == posLage || UMSCHLB == posLage || UNKLAR == posLage)
		{
			// vollständig innerhalb einer this-Insel heißt außerhalb der this-Fläche
			if (INNERH == posLage)
				return AUSSERH;
			// innerhalb der this-Außenkontur, aber bez. einer this-Innenkontur INNERHB bzw.
			// mit dieser vollständig deckungsgleich (KONTUR oder GLEICH) bedeutet AUSSERHB
			if (INNERHB == posLage ||
				KONTUR == posLage ||		// 16.06.98
				GLEICH == posLage)			// 15.04.99
				return AUSSERHB;
			// eine this-Innenkontur umschließen heißt INNAUSS bez. der this-Fläche
			if (UMSCHL == posLage || UMSCHLB == posLage)
				return INNAUSS;
			return posLage;
		}
	}

	return INNAUSS;
	
} // EFlaeche :: EnthaltenIn


// --------------------------------------------------------------------------------------------
// Hilfsroutine für EFlaeche :: EnthaltenIn()
Posit EFlaeche :: BeideAussenkonturenIdentisch (EFlaeche* pFl, int iKAnz)
{
	_ASSERTE (pFl != 0);	// pPSt kann 0 sein

	if (1 == _Size && 1 == iKAnz)	// this- und pFl-Fläche haben keine Innenkonturen
		return GLEICH;

	if (_Size > 1 && 1 == iKAnz)
		return INNERHB;

	if (1 == _Size && iKAnz > 1)
		return INNAUSS;

// es bleibt:   iKAnz > 1 && _Size > 1
// dafür sind immer noch INNAUSS, INNERHB, KONTUR und GLEICH möglich
bool bLeer, bAbbr;	// Parameter von Aufbereitung2(); werden hier nicht ausgewertet
bool bOverlap;		// Parameter von KantenPosit(); werden
int iTouchOut;		// hier nicht ausgewertet

// piKennz ist ein 2-dimensionales Feld (Vektor von Vektoren) mit
//   1. Index: Indizes der this-Insel   } jeweils von 0 ... KantenAnz()-2;
//   2. Index: Indizes der pFl-Insel    }  deswegen überall i-1 bzw. ii-1
// die Belegung von piKennz hat folgende Bedeutung:
//   -1  noch unklar (Initialisierung)
//    0  zur i-ten bzw. ii-ten Insel gibt es eine Insel der "anderen" Fläche, die haarscharf
//       auf dieser Insel liegt (Inseln, zu der es eine deckungsgleiche Insel der "anderen"
//       Fläche gibt, werden aus der weiteren Betrachtung heraus gelassen)
//    1  die i-te Insel liegt außerhalb der ii-ten Insel
//    2  die i-te Insel umschließt die ii-te Insel
vector < vector <int> > piKennz;

	piKennz.resize (_Size-1);	// Größe des Feldes anlegen
	for (int i = 0; i < static_cast<int>(piKennz.size()); i++)
		piKennz[i].resize (iKAnz-1);

	for (i = 1; i < _Size; i++)	// Initialisierung
		for (int ii = 1; ii < iKAnz; ii++)
			piKennz[i-1][ii-1] = -1;

	for (i = 1; i < _Size; i++)
		for (int ii = 1; ii < iKAnz; ii++)
		{
			if (0 == piKennz[i-1][ii-1])
				continue;

		MarkLine* pML1 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);
		MarkLine* pML2 = new MarkLine (pFl->KA(ii).ASP(), ii, true/*, false*/);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_geo_obj4, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return UNKLAR;
			}

			if (!_KAF[i].Aufbereitung2 (&pFl->KA(ii), pML1, pML2, bLeer, bAbbr, 0))
			{
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);

				if (bLeer)	// Container beider Konturen sind durchschnittsleer
				{
					piKennz[i-1][ii-1] = 1;
					continue;
				}
				else
					return UNKLAR;
			}

		Posit posLage = KantenPosit (&pFl->KA(ii), pML1, bOverlap, iTouchOut);

			DELETE_OBJ (pML1); DELETE_OBJ (pML2);

			if (INNAUSS == posLage || INNERH == posLage || INNERHB == posLage)
				return INNAUSS;

			if (UNKLAR == posLage)
				return UNKLAR;

			if (KONTUR == posLage)
			{
				for (int jj = 1; jj < iKAnz; jj++)
					piKennz[i-1][jj-1] = 0;

				for (int j = 1; j < _Size; j++)
					piKennz[j-1][ii-1] = 0;
				break;	// nächste KA(i)-Insel
			}

			_ASSERTE (piKennz[i-1][ii-1] == -1);

			if (AUSSERH == posLage || AUSSERHB == posLage)
				piKennz[i-1][ii-1] = 1;
			else	// UMSCHL == posLage || UMSCHLB == posLage
				piKennz[i-1][ii-1] = 2;
		}

// nachfolgender Test kann NICHT gleich mit der vorangegangenen for-Schleife abgefangen werden,
// da die Kennzeichnungen "1" bzw. "2" nachträglich noch auf "0" gesetzt werden können, da sich
// erst SPÄTER herausstellen kann, daß es zu einer Insel eine deckungsgleiche Insel der
// "anderen" Fläche gibt
bool bAusser = false;	// das Kennzeichen piKennz[][] == 1 tritt auf, d.h. mindestens einmal
						// war posLage == AUSSERH bzw. posLage == AUSSERHB (true)
bool bUmschl = false;	// das Kennzeichen piKennz[][] == 2 tritt auf, d.h. mindestens einmal
						// war posLage == UMSCHL bzw. posLage == UMSCHLB (true)

	for (i = 1; i < _Size; i++)
		for (int ii = 1; ii < iKAnz; ii++)
		{
		int iKZ = piKennz[i-1][ii-1];

			if (1 == iKZ)
				bAusser = true;
			else if (2 == iKZ)
				bUmschl = true;
		}

	if (!bAusser)
	{
		if (bUmschl)
			return INNERHB;

		// bAusser == false && bUmschl == false
		if (_Size == iKAnz)
//			return KONTUR;		15.04.99
			return GLEICH;

		if (_Size > iKAnz)
			return INNERHB;

		if (_Size < iKAnz)
			return INNAUSS;
	}

	// bAusser == true, d.h. es bleibt immer noch INNAUSS und INNERHB
	// Wenn es mindestens eine KA(ii)-Insel der pFl-Bezugsfläche gibt, für die für ALLE
	// KA(i)-Inseln piKennz[i][.] == 1 gilt, dann INNAUSS, sonst INNERHB
	for (int ii = 1; ii < iKAnz; ii++)
	{
	bool bAllNull = true;	// es gilt piKennz[.][ii] == 0 für alle i

		for (int i = 1; i < _Size; i++)
		{
		int iKZ = piKennz[i-1][ii-1];

			if (0 == iKZ) continue;
			bAllNull = false;
			if (1 != iKZ) break;
		}

		if (i == _Size && !bAllNull)
			return INNAUSS;
	}

	return INNERHB;

} // BeideAussenkonturenIdentisch


// --------------------------------------------------------------------------------------------
// 19.10.98: Hilfsroutine zu EFlaeche::EnthaltenIn() für folgenden Fall:
// this-Fläche liegt innerhalb der pFl-Außenkontur und und bez. der pFl-Innenkonturen gilt
// mindestens einmal UMSCHL bzw. UMSCHLB (diese pFl-Innenkonturen sind in piInsel aufgelistet);
// für das Verhältnis der this-Fläche bez. der pFl-Fläche gilt dann
//   INNERH,  wenn zu allen diese pFl-Innenkonturen auch this-Innenkonturen mit UMSCHL
//            existieren
//   INNERHB, wenn zu allen diese pFl-Innenkonturen auch this-Innenkonturen mit UMSCHLB bzw.
//            KONTUR existieren
//   INNAUSS  in allen übrigen Fällen
Posit EFlaeche :: EnthaltenInWeiter (EFlaeche* pFl, int* piInsel)
{
	_ASSERTE (pFl != 0);
	_ASSERTE (piInsel != 0);

	if (0 == piInsel[0] || 1 == _Size) return UNKLAR;

bool bAbbr = false;		// true: Abbruch der while-Schleife
int k = 0;				// Laufindex für piInsel
bool bOverlap;			// Parameter von LageKonturZuKontur(); werden hier
int iTouchOut;			// nicht ausgewertet
bool bInnerhB = false;	// this-Fläche liegt bez. der pFl-Fläche INNERHB (true)

	// Lage der pFl-Inseln, die innerhalb der this-Außenkontur liegen, zu den this-Inseln
	while (0 != piInsel[k])	// pFl-Inseln
	{
	bool bInn = false;	// this-Insel liegt bez. einer pFl-Insel INNERH (true)
	bool bInnB = false;	// this-Insel liegt bez. einer pFl-Insel INNERHB (true)
	int i = piInsel[k];	// Index für die pFl-Inseln, die innerhalb der this-Außenkontur liegen 

		for (int ii = 1; ii < _Size; ii++)	// this-Inseln
		{
		MarkLine* pML1 = new MarkLine (pFl->KA(i).ASP(), i, true/*, false*/);
		MarkLine* pML2 = new MarkLine (_KAF[ii].ASP(), ii, true/*, false*/);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_geo_obj4, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return UNKLAR;
			}

		Posit posLage = pFl->KA(i).LageKonturZuKontur (&_KAF[ii], pML1, pML2, bOverlap,
													   iTouchOut);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);

			if (INNERH == posLage)
			{
				bInn = true;
				break;
			}

			else if (INNERHB == posLage || KONTUR == posLage || GLEICH == posLage)
			{
				bInnB = true;
				bInnerhB = true;
				break;
			}

			else if (OFFEN == posLage || UNKLAR == posLage)
			{
				_ASSERTE (posLage != OFFEN);
				_ASSERTE (posLage != UNKLAR);

				return UNKLAR;
			}

		} // for

		if (!bInn && !bInnB)
			return INNAUSS;

		k++;
	} // while

	if (bInnerhB)
		return INNERHB;
	return INNERH;

} // EnthaltenInWeiter


// --------------------------------------------------------------------------------------------
// Vereinigung zweier Flächen (this- und pFl-Fläche) mit (bInsel == true) bzw. ohne
// (bInsel == false) Berücksichtigung der Innenkonturen; wenn
// - beide Flächen keinen oder nur endlich viele Punkte gemeinsam haben
// - sich kein Anfangspunkt für die Außenkontur der vereinigten Fläche finden läßt
// - nicht genügend dynamischer Speicher verfügbar ist,
// dann keine Vereinigung möglich (Rückgabe von NULL)
EFlaeche* _GEOMETR_EXPORT EFlaeche :: FlaechenVereinigung (EFlaeche* pFl, bool& bAbbr,
														   void* pPSt, bool bInsel)
{
	_ASSERTE (pFl != 0);	// pPSt wird weiter unten getestet

	if (! pFl) return NULL;
	
ObjRechteck OC1 = GetCont();		// Container der this-Fläche
ObjRechteck OC2 = pFl->GetCont();	// Container von pFl

	// Test, ob beide Container genau 1 Punkt gemeinsam haben. (Der Fall, daß Container völlig
	// durchschnittsleer sind, wird in Aufbereitung2() abgefangen.)
	if (EPunkt (OC1.XMin(), OC1.YMin()) == EPunkt (OC2.XMax(), OC2.YMax()) ||
		EPunkt (OC1.XMax(), OC1.YMin()) == EPunkt (OC2.XMin(), OC2.YMax()) ||
	    EPunkt (OC1.XMin(), OC1.YMax()) == EPunkt (OC2.XMax(), OC2.YMin()) ||
		EPunkt (OC1.XMax(), OC1.YMax()) == EPunkt (OC2.XMin(), OC2.YMin()))
		return 0;

/* Erst einmal nach Buffering.cxx verlagert (28.07.99)
	// Uff, wieder so eine welterneuernde Ergänzung; derzeit ist nur bekannt, daß diese
	// Bereinigung zwingend notwendig für die Pufferbildung ist, da bei dem schrittweisen
	// Aufbau der Pufferfläche die Partialflächen doppelte Punkte enthalten können, die bisher
	// nicht bereinigt wurden, weil diese Partialflächen nicht gespeichert werden (erst hier
	// käme ja GeoRein zu Zuge) (27.07.99)
	PartialCleaningForLines (&_KAF[0]);
	PartialCleaningForLines (&pFl->KA(0));
*/

// aus Stützpunktfolge der this-Außenkontur wird Vektor pML1, aus Außenkontur der pFl-Fläche
// wird Vektor pML2 mit markierten Punkten erzeugt; diese Vektoren werden in Aufbereitung2()
// evtl. noch erweitert
MarkLine* pML1 = new MarkLine (_KAF[0].ASP(), 0);
MarkLine* pML2 = new MarkLine (pFl->KA(0).ASP(), 0);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_geo_obj4, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return 0;
	}

// Die beiden nachfolgenden Zeilen könnten an vielen Stellen anstatt der new-Definition
// geschrieben werden. Dann muß aber nach Aufbereitung() noch als Parameter durchgereicht
// werden, ob es sich um eine echte Kante (pML2 bleibt 0) oder eine Flächenkontur (pML2 wird
// gesetzt) handelt.
//MarkLine* pML1 = 0;
//MarkLine* pML2 = 0;

bool bLeer;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet

	if (!_KAF[0].Aufbereitung2 (&pFl->KA(0), pML1, pML2, bLeer, bAbbr, pPSt))
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return 0;
	}

// KantenPosit() ermittelt die Position "posLage" der beiden Außenkonturen der this-Fläche und
// pFl zueinander
bool bOverlap;	// this-Fläche hat mit pFl-Außenkontur einen Überlappungsbereich
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet
Posit posLage = KantenPosit (&pFl->KA(0), pML1, bOverlap, iTouchOut);
EFlaeche* pVFl = NULL;	// Vereinigungsfläche
bool bNew = false;		// pVFl wurde (noch nicht) mit new dynamisch angelegt

	switch (posLage)
	{
		case INNERH:	// this-Fläche innerhalb der Außenkontur von pFl
		case INNERHB:
			if (bInsel)	// mit Inseln
			{
			EFlaeche* pHF = pFl->FlaechenVereinigung1 (this);

				if (pHF)	// FlaechenVereinigung1() hat nicht 0 zurückgeliefert
				{
					pVFl = new EFlaeche (*pHF);
					bNew = true;
				}
			}
			else		// ohne Inseln
			{
//				pVFl = new EFlaeche (*pFl);
				pVFl = new EFlaeche (&pFl->KA(0),1);	// pFl könnte Inseln haben (#WM030110)
				bNew = true;
			}
			break;

		case UMSCHL:	// pFl innerhalb der Außenkontur der this-Fläche
		case UMSCHLB:
		case KONTUR:	// Außenkonturen der this-Fläche und pFl liegen genau übereinander
//		case GLEICH:	// KantenPosit() hat den Rückkehrwert "GLEICH" nicht (#WM030110)
			if (bInsel)
			{
			EFlaeche* pHF = FlaechenVereinigung1 (pFl);

				if (pHF)	// FlaechenVereinigung1() hat nicht NULL zurückgeliefert
				{
					pVFl = new EFlaeche (*pHF);
					bNew = true;
				}
			}
			else		// ohne Inseln
			{
//				pVFl = new EFlaeche (*this);
				pVFl = new EFlaeche (&_KAF[0],1);		// this könnte Inseln haben (#WM030110)
				bNew = true;
			}
			break;

		case AUSSERHB:	// pFl außerhalb der this-Fläche mit Berührung
			if (bOverlap)
			{
				pVFl = new EFlaeche();
				bNew = true;
				if (! pVFl) break;
				if (!ContourUnion (pML1, pML2, pVFl, bInsel) &&
					0 == pVFl->KantenAnz())
				{
					DELETE_OBJ (pVFl);
					break;
				}
				if (bInsel)
					pVFl->AddInseln1 (this, pFl);  // blankes Hinzufügen der Innenkonturen
			}
			break;	// anderenfalls ist keine Vereinigung möglich, d. h. pVFl == 0

		case INNAUSS:
			// Aufbau der Außenkontur (und evtl. einiger Innenkonturen) der Vereinigungsfläche
			pVFl = new EFlaeche();
			bNew = true;
			if (! pVFl) break;
			if (!ContourUnion (pML1, pML2, pVFl, bInsel) &&
				0 == pVFl->KantenAnz())
			{
				DELETE_OBJ (pVFl);
				break;
			}
			if (bInsel &&		// Inseln (verschnitten) hinzufügen
				(KantenAnz() > 1 || pFl->KantenAnz() > 1))
				pVFl->AddInseln2 (this, pFl);
			break;
	} // switch
	// für posLage == AUSSERH bzw. UNKLAR ist keine Vereinigung möglich, d. h. pVFl == NULL

	if (bNew && !pVFl)
		DEX_Error (RC_geo_obj4, EC_NOMEMORY);

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);

	return pVFl;

} // FlaechenVereinigung


// --------------------------------------------------------------------------------------------
// Spezielle Flächenvereinigung von this- und pFl-Fläche mit Berücksichtigung sämtlicher
// Inseln, wobei vorausgesetzt wird, daß pFl vollständig innerhalb der this-Außenkontur liegt.
// Es werden folgende Fälle unterschieden:
// - pFl liegt innerhalb einer this-Insel und berührt diese Innenkontur höchstens an einzelnen
//   Punkten, dann ist keine Flächenvereinigung möglich, es wird 0 zurückgegeben
// - this-Fläche hat keine Inseln bzw. pFl liegt außerhalb aller this-Inseln, dann wird die
//   this-Fläche unverändert zurückgegeben
// - In allen anderen Fällen wird die this-Fläche mit folgenden Inseln zurückgegeben:
//   . Teile der this-Inseln, die außerhalb der pFl-Außenkontur liegen
//   . Flächen, die sich beim Durchschnitt jeder this-Insel mit jeder pFl-Insel ergeben
EFlaeche* EFlaeche :: FlaechenVereinigung1 (EFlaeche* pFl)
{
	if (1 == _Size)	// this-Fläche hat keine Inseln
		return this;

	_ASSERTE (pFl != 0);

// Wenn this-Fläche auch Inseln hat, dann Lage der pFl-Außenkontur bez. dieser this-Inseln
// bestimmen
bool bLeer;		// Container der beiden in Aufbereitung2() verglichenen Objekte sind
				// durchschnittsleer (true)
bool bAbbr;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet
bool bOverlap;	// pFl-Außenkontur hat mit einer this-Insel einen Überlappungsbereich
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet

	for (int i = 1; i < _Size; i++)
	{
	MarkLine* pML1 = new MarkLine (pFl->KA(0).ASP(), 0);			// 09.06.98: von ...
	MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_geo_obj4, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return 0;
		}

//		if (false == _KAF[i].Aufbereitung2 (&pFl->KA(0), pML2, pML1, bLeer, bAbbr, 0))
		if (!pFl->KA(0).Aufbereitung2 (&_KAF[i], pML1, pML2, bLeer, bAbbr, 0))	// 27.07.98
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			if (bLeer) continue;		// 11.11.98
			return 0;
		}																// ... bis

	Posit posLage = KantenPosit (&_KAF[i], pML1, bOverlap, iTouchOut);

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		if (INNERH == posLage ||				// pFl liegt innerhalb einer this-Insel
			(INNERHB == posLage && !bOverlap))	// pFl berührt this-Insel höchstens an einzelnen
												// Punkten
			return 0;	// deshalb keine Flächenvereinigung möglich
							
		// Außenkontur der pFl-Fläche ist mit der i-ten Insel der this-Fläche völlig identisch (09.06.98)
		else if (KONTUR == posLage || GLEICH == posLage)
		{
			// i-te Insel der this-Fläche löschen und dafür Inseln der pFl-Fläche hinzunehmen
			AddInseln3 (pFl, i);
			return this;
		}

		// Außenkontur der pFl-Fläche umschließt (d.h. überdeckt) die i-te Insel der
		// this-Fläche (27.07.98)
		else if (UMSCHL == posLage ||	// 27.07.98
				 UMSCHLB == posLage)
		{
			// i-te Insel der this-Fläche löschen und dafür andere Inseln hinzunehmen
			AddInseln4 (pFl, i);
			return this;
		}

		else if (AUSSERH != posLage && AUSSERHB != posLage)
			break;	// pFl ragt in ein "Inselloch" hinein
	}

	if (i == _Size)	// pFl ist bez. aller this-Inseln AUSSERH bzw. AUSSERHB
		return this;

	AddInseln5 (pFl);	// Inseln (verschnitten) hinzufügen
	
	return this;	// evtl. mit Inseln ergänzt
	
} // FlaechenVereinigung1


// --------------------------------------------------------------------------------------------
// Aufbau der Außenkontur der Vereinigungsfläche pVFl (und für bInsel == true Innenkonturen,
// die durch konkave Stellen bei pML1 bzw. pML2 enstehen können) bei Vereinigung zweier
// geschlossener Konturen, die durch die Vektoren pML1 und pML2 gegeben sind;
// schon vorhandene Innenkonturen der Ausgangsflächen werden hier nicht berücksichtigt
bool EFlaeche :: ContourUnion (MarkLine* pML1, MarkLine* pML2, EFlaeche*& pVFl, bool bInsel)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);
	_ASSERTE (pVFl != 0);

EFlaeche* pKVFl = 0;	// Kontur der Vereinigungsfläche
//double dUmlauf;			// Umlaufsinn einer Kontur der vereinigten Fläche
long lAI = 0;			// Anfangsindex für Suche nach Anfangspunkt einer Kontur
Mar1 mark;				// Markierung
long lNewSize1 = pML1->ADP();
long lNewSize2 = pML2->ADP();
bool bRest;				// nach Verlassen der do-Schleife ist die soeben aufgebaute Kontur noch
						//  durch einen restlichen Teil zu ergänzen

int iKInd1 = pML1->GetKInd();		_ASSERTE (iKInd1 >= 0);
int iKInd2 = pML2->GetKInd();		_ASSERTE (iKInd2 >= 0);
bool bMax;		// SEHR wichtiger Parameter von EckeMitBeruehrung()

	if (0 == iKInd1 && 0 == iKInd2)
		bMax = false;
	else if (0 == iKInd1 && iKInd2 > 0)
		bMax = true;
	else if (iKInd1 > 0 && 0 == iKInd2)
	{
		_ASSERTE (false);	// nur zu Testzwecken, da
		bMax = false;	// diesen Fall hatte ich noch nicht
	}
	else	// if (iKInd1 > 0 && iKInd2 > 0)
		bMax = true;	// 29.10.98

bool bWechsel;	// bei BERUE_UMG ist bei pML2 fortzusetzen (true); wird durch
				// EckeMitBeruehrung() gesetzt
bool bAussen;	// pML1 und pML2 sind beide aus Außen- (true) bzw. Innenkonturen (false)
				// entstanden

	if (0 == iKInd1 && 0 == iKInd2)
		bAussen = true;
	else if (iKInd1 > 0 && iKInd2 > 0)
	{
		bAussen = false;

		_ASSERTE (!bInsel);	// sonst könnte "Insel in Insel" entstehen (28.05.99)
	}
	else
		_ASSERTE (false);

	// for-Schleife wird mehrfach durchlaufen, wenn bei der Vereinigung durch konkave Stellen
	// auch Innenkonturen entstehen
	for (;;)
	{
		// Suche nach einem Punkt der pML1-Kontur, so daß die folgende Strecke noch
		// "unverbraucht" ist und der anschließende Teil der pML1-Kontur außerhalb der
		// pML2-Kontur liegt, um dort mit dem Aufbau einer Kontur der vereinigten Fläche zu
		// beginnen, da es sein kann, daß der bisherige Anfangspunkt der pML1-Kontur durch die
		// Vereinigung innerhalb der vereinigten Fläche liegt und somit nicht mehr verwendbar
		// ist; dazu wird getestet, wo der Mittelpunkt (!) der einzelnen Strecken der
		// pML1-Kontur bez. der um die Schnittpunkte erweiterten pML2-Kontur liegt.
		for (long i = lAI; i < lNewSize1-1; i++)
			if (UNVERBR == pML1->GetMk2(i) &&		// noch "unverbrauchte" Strecke
				AUSSERH == pML2->Position (pML1, i))
				break;  // geeigneter Punkt gefunden
		
		if (i == lNewSize1-1)    // alle this-Strecken abgearbeitet
		{
			if (0 == pVFl->KantenAnz())	// kein geeigneter Anfangspunkt gefunden
				DEX_Error (RC_ContourUnion, EC_NOANFANG);
			return false;
		}

		// Anfangsindex für einen evtl. weiteren do-Durchlauf aktualisieren, der erforderlich
		// wird, wenn sich mindestens eine Innenkontur ergibt
		(i < lNewSize1-2) ? (lAI = i + 1) : (lAI = 0);

	// punktweiser Aufbau einer Kontur pKVFl der vereinigten Fläche, zuerst mit Punkten der
	// this-Außenkontur
	KoOrd x = DtoL (pML1->x(i));
	KoOrd y = DtoL (pML1->y(i));

		pKVFl = new EFlaeche (&x, &y, 1); // Anfang einer Kontur der Vereinigungsfläche
		if (! pKVFl)
		{
			DEX_Error (RC_geo_obj4, EC_NOMEMORY);
			return false;
		}

	EPunkt PA (x, y);	// Anfangspunkt einer Kontur der Vereinigungsfläche
	long lAnfId1 = lAI;	// Anfangsindex für den Teil der Kontur, der aus pML1 übernommen wird

		do      // weiterer Aufbau einer Kontur der vereinigten Fläche
		{
			bRest = true;
			pML1->ModMark2 (i, VERBR);       // Strecke (pML1[i], pML1[i+1] "verbraucht"
			(i < lNewSize1-2) ? (i++) : (i = 0);

			// aktueller Punkt pML1[i] ist Schnittpunkt (SCHNITT) oder Endpunkt mit
			// "Zuführung" aus der Umgebung der pML2-Fläche (RAND_UMG), dann pKVFl mit Punkten
			// von pFl ergänzen
			mark = pML1->GetMk1(i);

			if (BERUE_UMG == mark)
				pML1->EckeMitBeruehrung (pML2, i, MOVEDIR_UP, MOVEDIR_UP, bMax, bWechsel);

			if (PA != pML1->SP(i) &&
				(SCHNITT == mark || RAND_UMG == mark
				|| (BERUE_UMG == mark && bWechsel)))
			{
				// Teil der Kontur von pML1 an pKVFl anhängen
				pKVFl->KA(0).AddKonturTeil (pML1, lAnfId1, i, -1);
				if (PA == pML1->SP(i))
					break;	// 13.10.98
				pKVFl->ZweiteFlaeche (pML1, pML2, i);	// pKVFl mit Punkten von pML2 ergänzen

				(i < lNewSize1-2) ? (lAnfId1 = i + 1) : (lAnfId1 = 0);

				bRest = false;
			}
		}
		while (PA != pML1->SP(i));		// Abbruch, wenn Kontur geschlossen

		// restlichen Teil an pKVFl anhängen, wenn in der do-Schleife noch Stützpunkte
		// gesammelt wurden, die jedoch mit AddKonturTeil noch nicht an die Kontur angefügt
		// wurden; bRest == false, wenn unmittelbar nach dem Aufruf der Routine SpezAddPunkt()
		// die do-Schleife mit geschlossener Kontur beendet wurde
		if (bRest)
			pKVFl->KA(0).AddKonturTeil (pML1, lAnfId1, i, -1);

	// Da es möglich ist, daß durch die Eps-Arithmetik der Anfangs- und Endpunkt nur eps-gleich
	// sind, werden beide Punkte vorsichtshalber völlig identisch gemacht.
	long lSPAnz = pKVFl->KA(0).ASP();
		
		pKVFl->KA(0).SP(lSPAnz-1) = PA;

		// Vereinigung zweier Außenkonturen
		if (bAussen)
		{
		// Ermittlung des Umlaufsinns der neu erzeugten Kontur
		double dUmlauf = pKVFl->KA(0).PolygonArea();

			// es wurde eine Außenkontur erzeugt, die "vorn" anzufügen ist
			if (dUmlauf > 0.)
			{
				pVFl->AddKante (*pKVFl, 1, 0);

				// wenn keine Inseln gefordert sind, kann nach Aufbau der Außenkontur die Suche
				// nach weiteren "unverbrauchten" Strecken abgebrochen werden
				if (! bInsel)	
					lAI = lNewSize1-1;
			}

			// es wurde eine Innenkontur erzeugt, die "hinten" anzufügen ist
			else if (dUmlauf < 0.)
				pVFl->AddKante (*pKVFl, 1, -1);

			_ASSERTE (dUmlauf != 0.);	// es wurde "etwas" erzeugt
		}

		// Vereinigung zweier Innenkonturen (hier kann das Ergebnis nur die Außenkontur von
		// pKVFl sein
		else
			pVFl->AddKante (*pKVFl, 1, 0);

		DELETE_OBJ (pKVFl);
			
	} // for

	return true;

} // ContourUnion


// --------------------------------------------------------------------------------------------
// Innenkonturen der Flächen pFl1 und pFl2 werden unverändert als Innenkonturen der this-Fläche
// hinzugefügt (bei Routine FlaechenVereinigung() benötigt)
void EFlaeche :: AddInseln1 (EFlaeche* pFl1, EFlaeche* pFl2)
{
	_ASSERTE (pFl1 != 0);
	_ASSERTE (pFl2 != 0);

int iKAnz1 = pFl1->KantenAnz();
int iKAnz2 = pFl2->KantenAnz();

	if (iKAnz1 > 1)
		for (int i = 1; i < iKAnz1; i++)
			AddKante (EFlaeche (&pFl1->KA(i), 1), 1, -1);
	if (iKAnz2 > 1)
		for (int i = 1; i < iKAnz2; i++)
			AddKante (EFlaeche (&pFl2->KA(i), 1), 1, -1);
} // AddInseln1


// --------------------------------------------------------------------------------------------
// Innenkonturen der Flächen pFl1 und pFl2 werden unter Berücksichtung möglicher Überlappungen
// als Innenkonturen der this-Fläche hinzugefügt (bei Routinen FlaechenVereinigung() benötigt)
void EFlaeche :: AddInseln2 (EFlaeche* pFl1, EFlaeche* pFl2)
{
	_ASSERTE (pFl1 != 0);
	_ASSERTE (pFl2 != 0);

	if (! pFl1 || ! pFl2)
		return;

ClipListe CL;	// Liste für die Ergebnisse der Schnittoperation
int iKAnz1 = pFl1->KantenAnz();
int iKAnz2 = pFl2->KantenAnz();

	// Erzeugen von Inseln für die Vereinigungsfläche
	// Teile der pFl1-Inseln, die außerhalb der pFl2-Außenkontur liegen
	if (iKAnz1 > 1)
		for (int i = 1; i < iKAnz1; i++)
			pFl1->KA(i).SchnittKonturMitKontur (&pFl2->KA(0), i, 0, LAUSS, CL);
	
	// Teile der pFl2-Inseln, die außerhalb der pFl1-Außenkontur liegen
	if (iKAnz2 > 1)
		for (int ii = 1; ii < iKAnz2; ii++)
			pFl2->KA(ii).SchnittKonturMitKontur (&pFl1->KA(0), ii, 0, LAUSS, CL);
		
	// Flächen, die sich beim Durchschnitt jeder pFl1-Insel mit jeder pFl2-Insel ergeben
	if (iKAnz1 > 1 && iKAnz2 > 1)
	{
		for (int ii = 1; ii < iKAnz2; ii++)
			for (int i = 1; i < iKAnz1; i++)
				pFl1->KA(i).SchnittKonturMitKontur (&pFl2->KA(ii), i, ii, LINN, CL);
	}

CRing ri (CL);	// Navigator für ListContainer ClipListe CL

	if (CL.Count() > 0)		// es hat sich wenigstens eine Insel ergeben
	{
		for (ri.First(); ri.Valid(); ri.Next())
		{
		GeoObjektLock ml (ri);

			if (! ml)		// kein Zugriff möglich
			{
				DEX_Error (RC_geo_obj4, EC_NOLOCK);
				continue;
			}

			_ASSERTE (((GeoObjekt*)ml)->isA() == OT_FLAECHE);

			AddKante (*((GeoFlaeche*)(GeoObjekt*)ml), 1, -1);
		}
	}
} // AddInseln2


// --------------------------------------------------------------------------------------------
// i-te Insel der this-Fläche löschen und dafür Inseln der pFl-Fläche hinzunehmen (bei Routine
// FlaechenVereinigung1() benötigt)
void EFlaeche :: AddInseln3 (EFlaeche* pFl, int i)
{
	_ASSERTE (pFl != 0);
	_ASSERTE (i >= 1);

	SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen

int iKAnz = pFl->KantenAnz();

	if (iKAnz > 1)
	{
		for (int j = 1; j < iKAnz; j++)
			AddKante (EFlaeche (&pFl->KA(j), 1), 1, -1);	// pFl-Inseln hinzunehmen	
	}

} // AddInseln3


// --------------------------------------------------------------------------------------------
// i-te Insel der this-Fläche löschen und dafür neue Inseln hinzunehmen, u. z.
// - die Bereiche, die innerhalb der i-ten Insel der this-Fläche und außerhalb der Außenkontur
//   der pFl-Fläche liegen sowie
// - die Inseln der pFl-Fläche bzw. deren Bereiche, die innerhalb der i-ten Insel der
//   this-Fläche liegen
// (bei Routine FlaechenVereinigung1() benötigt)
void EFlaeche :: AddInseln4 (EFlaeche* pFl, int i)
{
	_ASSERTE (pFl != 0);
	_ASSERTE (i >= 1);

ClipListe CL;	// Liste für die Ergebnisse der Schnittoperation
CRing ri (CL);	// Navigator für ListContainer ClipListe CL

	// Teile der i-ten this-Insel, die außerhalb der pFl-Außenkontur liegen
	_KAF[i].SchnittKonturMitKontur (&pFl->KA(0), i, 0, LAUSS, CL);

int iKCnt = pFl->KantenAnz();

	if (iKCnt > 1)	// pFl-Fläche hat Inseln
		// Teile der j-ten pFl-Insel, die innerhalb der i-ten this-Insel liegen
		for (int j = 1; j < iKCnt; j++)
			pFl->KA(j).SchnittKonturMitKontur (&_KAF[i], j, i, LINN, CL);

	if (CL.Count() > 0)		// es hat sich wenigstens eine Insel ergeben
	{
		for (ri.First(); ri.Valid(); ri.Next())
		{
		GeoObjektLock ml (ri);

			if (! ml)		// kein Zugriff möglich
			{
				DEX_Error (RC_geo_obj4, EC_NOLOCK);
				continue;
			}

			_ASSERTE (((GeoObjekt*)ml)->isA() == OT_FLAECHE);

			AddKante (*((GeoFlaeche*)(GeoObjekt*)ml), 1, -1);
		}
	}

	SubKante (1, i);	// i-te Insel der this-Fläche löschen (06.07.99)

} // AddInseln4


// --------------------------------------------------------------------------------------------
// Innenkonturen der this-Fläche und von pFl werden unter Berücksichtung möglicher
// Überlappungen als Innenkonturen der this-Fläche hinzugefügt (bei Routine
// FlaechenVereinigung1() benötigt)
void EFlaeche :: AddInseln5 (EFlaeche* pFl)
{
	_ASSERTE (pFl != 0);

ClipListe CL;	// Liste für die Ergebnisse der Schnittoperation
CRing ri (CL);	// Navigator für ListContainer ClipListe CL
int iKAnz1 = _Size;
	
	// Erzeugen von Inseln für die Vereinigungsfläche
	if (iKAnz1 > 1)
	{
		// Teile der this-Inseln, die außerhalb der pFl-Außenkontur liegen
		for (int i = 1; i < iKAnz1; i++)
			_KAF[i].SchnittKonturMitKontur (&pFl->KA(0), i, 0, LAUSS, CL);

	// Flächen, die sich beim Durchschnitt jeder this-Insel mit jeder pFl-Insel ergeben
	int iKAnz2 = pFl->KantenAnz();

		if (iKAnz2 > 1)
		{
			for (int ii = 1; ii < iKAnz2; ii++)
				for (int i = 1; i < iKAnz1; i++)
					_KAF[i].SchnittKonturMitKontur (&pFl->KA(ii), i, ii, LINN, CL);
		}
	}

	// die bisherigen this-Inseln löschen
	SubKante (iKAnz1-1, 1);

	if (CL.Count() > 0)		// es hat sich wenigstens eine Insel ergeben
	{
		for (ri.First(); ri.Valid(); ri.Next())
		{
		GeoObjektLock ml (ri);

			if (! ml)		// kein Zugriff möglich
			{
				DEX_Error (RC_geo_obj4, EC_NOLOCK);
				continue;
			}

			_ASSERTE (((GeoObjekt*)ml)->isA() == OT_FLAECHE);

			AddKante (*((GeoFlaeche*)(GeoObjekt*)ml), 1, -1);
		}
	}
} // AddInseln5


// --------------------------------------------------------------------------------------------
// pKVFl mit Punkten von pML2 ergänzen
// (siehe auch Routine SpezAddPunkt() in geo_obj3.cxx)
void EFlaeche :: ZweiteFlaeche (MarkLine* pML1, MarkLine* pML2, long& i)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

long lVekL1 = pML1->ADP();   // Länge des Vektors pML1
long lVekL2 = pML2->ADP();   //  bzw. pML2

// Index des pML2-Punktes, der mit Punkt pML1[i] übereinstimmt
long ii = pML1->GetRefInd(i);

	_ASSERTE (ii >= 0);

long lAnfId2;	// Anfangsindex für den Teil der Kontur, der aus pML2 übernommen wird
Mar1 mark;		// Markierung

int iKInd1 = pML1->GetKInd();		_ASSERTE (iKInd1 >= 0);
int iKInd2 = pML2->GetKInd();		_ASSERTE (iKInd2 >= 0);
bool bWechsel;	// bei BERUE_UMG ist bei pML1 fortzusetzen (true); wird durch
				// EckeMitBeruehrung() gesetzt
bool bMax;		// SEHR wichtiger Parameter von EckeMitBeruehrung()

	if (0 == iKInd1 && 0 == iKInd2)
		bMax = false;
	else if (0 == iKInd1 && iKInd2 > 0)
		bMax = true;
	else if (iKInd1 > 0 && 0 == iKInd2)
	{
		_ASSERTE (false);	// nur zu Testzwecken, da
		bMax = false;	// diesen Fall hatte ich noch nicht
	}
	else	// if (iKInd1 > 0 && iKInd2 > 0)
		bMax = true;	// 29.10.98

	(ii < lVekL2-2) ? (lAnfId2 = ii + 1) : (lAnfId2 = 0);

	do
	{
		(ii < lVekL2-2) ? (ii++) : (ii = 0);
		mark = pML2->GetMk1(ii);
		if (BERUE_UMG == mark)
			pML2->EckeMitBeruehrung (pML1, ii, MOVEDIR_UP, MOVEDIR_UP, bMax, bWechsel);
	}
	// Abbruch bei Schnitt- oder Endpunkten mit "Zuführung" in die pML2-Umgebung
	// und/oder nicht mit Berührungspunkt
	while (mark != SCHNITT && mark != RAND_UMG
		   && !(mark == BERUE_UMG && bWechsel));

	// Teil der Kontur von pML2 an pKVFl anhängen
	_KAF[0].AddKonturTeil (pML2, lAnfId2, ii, -1);

	// Index des pML1-Punktes, der mit dem letzten hinzugefügten Punkt pML2[ii] übereinstimmt
	i = pML2->GetRefInd(ii);

	_ASSERTE (i >= 0);

} // ZweiteFlaeche


// --------------------------------------------------------------------------------------------
// Inseln der this-Fläche, die am Rand der in CL enthaltenen Schnittergebnisse liegen, bei
// Schnittoperationen mit Schnittkante berücksichtigen; die ersten iSkip Einträge in CL sind
// dabei zu übergehen;
// in bModify wird zurückgegeben, ob an mindestens einer CL-Fläche eine Veränderung durch
// "Anknabbern" der Außenkontur vorgenommen wurde (true), sonst false
bool EFlaeche :: InselnAmRand (ClipListe& CL, int iSkip, int* piVbInsel, bool& bModify)
{
	bModify = false;

	if (0 == CL.Count() || 1 == _Size) return true;	// keine Inseln

	_ASSERTE (piVbInsel != 0);

CRing ri (CL);	// Navigator für ListContainer ClipListe CL
ClipListe CLZw;	// ClipListe für Zwischenergebnisse
bool bOverlap;  // Teilfläche hat mit dem Rand einer this-Insel einen Überlappungsbereich bzw.
int iTouchOut;	// iTouchOut Berührungspunkte mit "Zuführung" aus der _KAF[i]-Umgebung gemeinsam

	for (int i = 1; i < _Size; i++)	// alle Inseln, die noch nicht verbraucht sind
	{
	bool bVerbr = false;	// Insel noch nicht verbraucht

		for (int j = 0; j < _Size-1; j++)
		{
			if (piVbInsel[j] == i)
			{
				bVerbr = true;	// diese Insel wurde schon verarbeitet
				break;
			}
			if (piVbInsel[j] == 0) break;
		}
		if (bVerbr) continue;

		// do-Schleife für alle in CL befindlichen Schnittergebnisse (die ersten iSkip Einträge
		// in CL sind zu übergehen)
		ri.First();
		if (iSkip > 0)
			for (int ii = 1; ii <= iSkip; ii++)
				ri.Next();

		do
		{
		bool bDel = false;	// im Zugriff befindliches Teilobjekt (kann Fläche aber auch Kante
							// sein) ist aus CL (noch) nicht zu löschen

			{ // Klammerung für ri.Delete() erforderlich
			GeoObjektLock ml (ri);

				if (! ml)		// kein Zugriff möglich
				{
					DEX_Error (RC_geo_obj4, EC_NOLOCK);
					ri.Next();
					continue;
				}

				if (OT_KANTE == ((GeoObjekt*)ml)->isA())
				{
					ri.Next();
					continue;
				}

			GeoFlaeche* pTF = (GeoFlaeche*)(GeoObjekt*) ml;

			PartialCleaningForLines (&pTF->KA(0));	// 09.02.99

			// aus Stützpunktfolge der Außenkontur der ml-Teilfläche wird Vektor pML1, aus
			// _KAF[i]-Insel wird Vektor pML2 mit markierten Punkten erzeugt; diese Vektoren
			// werden in Aufbereitung2() evtl. noch erweitert
			// Bildung von pML2 muß innerhalb der do-Schleife erfolgen, da diese Variable in
			// LageKonturZuKontur() durch Aufbereitung2() verändert wird
			MarkLine* pML1 = new MarkLine (pTF->KA(0).ASP(), 0);
			MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

				if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
				{
					DEX_Error (RC_geo_obj4, EC_NOMEMORY);
					DELETE_OBJ (pML1); DELETE_OBJ (pML2);
					return false;
				}
				
			// Lage der this-Inseln bez. der Teilflächen aus CL bestimmen
			Posit posLage = pTF->KA(0).LageKonturZuKontur (&_KAF[i], pML1, pML2, bOverlap,
														   iTouchOut);

				// gleich schneiden;  es können dabei mehrere Teilflächen entstehen
				// (UMSCHLB statt INNERHB, da Inseln math.neg. orientiert sind)
				if (INNAUSS == posLage ||
					(UMSCHLB == posLage && (bOverlap || iTouchOut > 1)))
				{
				long lONr = pTF->ObjNr();
				ulong ulIdent = pTF->Id();

					TeilFlaechen2 (pML1, pML2, lONr, ulIdent, LAUSS, CLZw);
					bDel = true;	// im Zugriff befindliche Teilfläche soll aus CL gelöscht werden
					bModify = true;	// eine CL-Fläche wurde modifiziert

					// Insel als verbraucht registrieren
					for (int j = 0; j < _Size-1; j++)
					{
						if (piVbInsel[j] == i) break;	// Insel ist schon als verbraucht registriert
						if (piVbInsel[j] == 0)
						{
							piVbInsel[j] = i;
							break;
						}
					}

					_ASSERTE (j < _Size-1);
				}
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			}

			if (bDel) ri.Delete();	// aktuelle Teilfläche in CL löschen (diese wurde durch	die
									//  "angeknabberte" Unter-Teilflächen ersetzt)
			else ri.Next();
		}
		while (ri.Valid());

		// wenn in CLZw Zwischenergebnisse abgelegt wurden, dann diese jetzt nach CL übernehmen
		if (0 == CLZw.Count()) continue;

	CRing riz (CLZw);

		for (riz.First(); riz.Valid(); riz.Next())
		{
		GeoObjektLock mlz (riz);

			if (! mlz) continue;	// kein Zugriff möglich
			mlz->AddClipObjekt (CL);
		}

		CLZw.EveryDelete();

	} // for

	return true;

} // InselnAmRand


// --------------------------------------------------------------------------------------------
// Inseln der this-Fläche, die innerhalb EINER (!) in CL enthaltenen Schnittfläche liegen, bei
// Schnittoperationen mit Schnittkante berücksichtigen; die ersten iSkip Einträge in CL sind
// dabei zu übergehen
bool EFlaeche :: InselnInnerhalb (ClipListe& CL, int iSkip, int* piVbInsel)
{
	// piVbInsel kann 0 sein (bei Schnittergebnis "außerhalb")

	if (1 == _Size) return true;	// keine Inseln vorhanden

// in CL sind jetzt die durch am Rand liegende Inseln "angeknabberten" Teilflächen enthalten;
// diese sind noch mit den echten Inseln zu komplettieren (die ersten iSkip Einträge aus CL
// wieder übergehen)
CRing ri (CL);	// Navigator für ListContainer ClipListe CL

	ri.First();
	if (iSkip > 0)
		for (int i = 1; i <= iSkip; i++)
			ri.Next();

bool bOverlap;	// Teilfläche hat mit dem Rand einer this-Insel einen Überlappungsbereich bzw.
int iTouchOut;	// iTouchOut Berührungspunkte mit "Zuführung" aus der _KAF[i]-Umgebung gemeinsam

	for (; ri.Valid(); ri.Next()) // alle Teilflächen aus CL
	{
	GeoObjektLock ml (ri);

		if (! ml)		// kein Zugriff möglich
		{
			DEX_Error (RC_geo_obj4, EC_NOLOCK);
			continue;
		}

		if (OT_KANTE == ((GeoObjekt*)ml)->isA())
			continue;

	GeoFlaeche* pTF = (GeoFlaeche*)(GeoObjekt*) ml;

		PartialCleaningForLines (&pTF->KA(0));	// 09.02.99

		for (int i = 1; i < _Size; i++)	// alle Inseln, die noch nicht verbraucht sind 
		{
		bool bVerbr = false;	// Insel noch nicht verbraucht

			if (piVbInsel)	// piVbInsel == 0 bei Schnittergebnis "außerhalb"
			{
				for (int j = 0; j < _Size-1; j++)
				{
					if (piVbInsel[j] == i)
					{
						bVerbr = true;	// diese Insel wurde schon verarbeitet
						break;
					}
					if (piVbInsel[j] == 0) break;
				}
				if (bVerbr) continue;
			}

		// aus Stützpunktfolge der Außenkontur der ml-Teilfläche wird Vektor pML1, aus
		// _KAF[i]-Insel wird Vektor pML2 mit markierten Punkten erzeugt; diese Vektoren werden
		// in LageKonturZuKontur() durch Aufbereitung2() evtl. noch erweitert
		MarkLine* pML1 = new MarkLine (pTF->KA(0).ASP(), 0);
		MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_geo_obj4, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return false;
			}

		// Lage der this-Inseln bez. der Außenkontur der Teilflächen aus CL bestimmen
		Posit posLage = pTF->KA(0).LageKonturZuKontur (&_KAF[i], pML1, pML2, bOverlap, iTouchOut);

			if (UMSCHL == posLage ||	// UMSCHL statt INNERH, da Inseln math.neg. orientiert sind
				(UMSCHLB == posLage && !bOverlap && iTouchOut <= 1))
			{
				if (1 == pTF->KantenAnz())	// 1. Insel hinzufügen (08.02.99)
					pTF->AddKante (EFlaeche (&_KAF[i], 1), 1, -1);
				else				// weitere Inseln mit den schon vorhandenen Inseln abtesten
					pTF->InselZweiteFlaeche (CL, &_KAF[i], i);
			}

			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		}
	} // for

	return true;

} // InselnInnerhalb


// --------------------------------------------------------------------------------------------
// Inseln der this-Fläche bei Schnittoperationen mit Schnittkante berücksichtigen; die ersten
// iSkip Einträge in CL sind dabei zu übergehen
bool EFlaeche :: InselnBeiSchnittMitKante (ClipListe& CL, int iSkip)
{
bool bModify;	// wird hier nicht ausgewertet

// Feld für die Indizes der Inseln, die schon "verbraucht" wurden
int* piVbInsel = new int[_Size];

	if (! piVbInsel)
	{
		DEX_Error (RC_geo_obj4, EC_NOMEMORY);
		return false;
	}

	memset (piVbInsel, 0 , _Size*sizeof(int));

bool bRet1 = InselnAmRand (CL, iSkip, piVbInsel, bModify);
bool bRet2 = InselnInnerhalb (CL, iSkip, piVbInsel);

	DELETE_VEC (piVbInsel);

	return bRet1 && bRet2; 

} // InselnBeiSchnittMitKante


// --------------------------------------------------------------------------------------------
// Inseln bei Schnittoperationen der this-Fläche mit pSFl-Schnittfläche berücksichtigen 
bool _GEOMETR_EXPORT EFlaeche :: InselnBeiSchnittMitFlaeche (EFlaeche* pSFl, ClipListe& CL,
															 int iSkip)
{
	_ASSERTE (pSFl != 0);

bool bRet;
int iKAnz = pSFl->KantenAnz();	// Anzahl der pSFl-Konturen

	if (_Size > 1)		// this-Fläche hat Inseln
	{
		if (iKAnz == 1)		// nur this-Fläche hat Inseln
			bRet = InselnBeiSchnittMitKante (CL, iSkip);	// this-Inseln berücksichtigen
		else				// beide Flächen mit Inseln
		{
		bool bModify1 = true;	// an mindestens einer CL-Fläche wurden durch die this-Inseln
		bool bModify2 = true;	//  bzw. die pSFl-Inseln Veränderungen vorgenommen (true)
		bool bRet1 = true;
		bool bRet2 = true;

		// Felder für die Indizes der Inseln, die schon "verbraucht" wurden
		int iKAnz2 = pSFl->KantenAnz();
		int* piVbInsel1 = new int[_Size];
		int* piVbInsel2 = new int[iKAnz2];

			if (!piVbInsel1 || !piVbInsel2)
			{
				DEX_Error (RC_geo_obj4, EC_NOMEMORY);
				DELETE_VEC (piVbInsel1);
				return false;
			}
			memset (piVbInsel1, 0 , _Size*sizeof(int));
			memset (piVbInsel2, 0 , iKAnz2*sizeof(int));

			if (InselnAmRand (CL, iSkip, piVbInsel1, bModify1) == false)
				bRet1 = false;
			if (pSFl->InselnAmRand (CL, iSkip, piVbInsel2, bModify2) == false)
				bRet2 = false;

			// durch das "Ankabbern" mit den pSFl-Inseln können wieder this-Inseln die
			// Außenkontur der CL-Fläche "anknabbern" wollen, usw.
			while (bModify2)
			{
				if (InselnAmRand (CL, iSkip, piVbInsel1, bModify1) == false)
					bRet1 = false;
				if (bModify1)
				{
					if (pSFl->InselnAmRand (CL, iSkip, piVbInsel2, bModify2) == false)
					bRet2 = false;
				}
				else
					bModify2 = false;
			}

		bool bRet3 = InselnInnerhalb (CL, iSkip, piVbInsel1);
		bool bRet4 = pSFl->InselnInnerhalb (CL, iSkip, piVbInsel2);

			DELETE_VEC (piVbInsel1);
			DELETE_VEC (piVbInsel2);

			bRet = bRet1 && bRet2 && bRet3 && bRet4;
		}
	}

	else	// this-Fläche hat keine Inseln
	{
		if (iKAnz == 1) return true;	// beide Flächen ohne Inseln

		bRet = pSFl->InselnBeiSchnittMitKante (CL, iSkip);	// pSFl-Inseln berücksichtigen
	}

	return bRet;

} // InselnBeiSchnittMitFlaeche


// --------------------------------------------------------------------------------------------
// Es wird ein Punkt zurückgegeben, der garantiert innerhalb der this-EFlaeche liegt.
bool _GEOMETR_EXPORT EFlaeche :: InneliegenderPunkt (double& dInX, double& dInY)
{
// zuerst wird getestet, ob der Mittelpunkt des umschließenden Rechtecks innerhalb der
// this-EFlaeche liegt
ObjRechteck OC = GetCont ();

	dInX = (OC.XMax() + OC.XMin()) / 2.;	// Mittelpunkt des umschließenden
	dInY = (OC.YMax() + OC.YMin()) / 2.;	// Rechtecks

EPunkt MP (DtoL(dInX), DtoL(dInY));

	if (INNERH == MP.EnthaltenIn (this))
		return true;	// liegt innerhalb

// klappt das noch nicht, wird durch den Mittelpunkt (dInX, dInY) eine waagrechte Testkante TKt
// gelegt, welche mit den Flächenkonturen geschnitten wird; von den ECHTEN Schnittpunkten
// werden die beiden mit den kleinsten x-Koordinaten gesucht; der Mittelpunkt zwischen diesen
// beiden Schnittpunkten muß mit Wahrscheinlichkeit 1 innerhalb der this-EFlaeche liegen
double dTestY = dInY;
double dSchrittY = OC.YMax() - OC.YMin();
KoOrd x[2] = { -MAXKOORD, MAXKOORD };
KoOrd y[2] = { DtoL(dTestY), DtoL(dTestY) };
EKante TKt (x, y, 2);	// waagrechte Testkante (aus 1 Strecke bestehend) durch den
						// Mittelpunkt des umschließenden Rechtecks
DoublePair ZPA, ZPE;	// evtl. gemeinsame Punkte der Testkante mit den Strecken der
						// Flächenkonturen
double xs1 = DBL_MAX,	// die beiden kleinsten x-Koordinaten von allen
	   xs2 = DBL_MAX;	// Schnittpunkten der Flächenkonturen mit der waagrechten Testkante

int iKAnz = KantenAnz();
int i = 0;
long j = -1;

	do
	{
	long lCSize = _KAF[i].ASP();

		do
		{
			j++;

			if (!Intersection (_KAF[i].SP(j).X(), _KAF[i].SP(j).Y(),
							   _KAF[i].SP(j+1).X(), _KAF[i].SP(j+1).Y(), TKt.SP(0).X(),
							   TKt.SP(0).Y(), TKt.SP(1).X(), TKt.SP(1).Y()))
				continue;       // die beiden Strecken haben keinen Punkt gemeinsam

		SchnittErg Fo = _KAF[i].KantenSchnitt (&TKt, j, 0, ZPA, ZPE);

			// Überlappungen und die Berührung einer Innenkontur mit der Außenkontur machen an
			// dieser Stelle Probleme, deshalb wird die waagrechte Testkante etwas parallel
			// verschoben
			if (UEBERLAPP == Fo ||
				((ECHT == Fo || INNEN_MIT == Fo || RAND_MIT == Fo) && i > 0 && xs1 == ZPA.X()))
			{
				if (dTestY + dSchrittY < OC.YMax())
					dTestY += dSchrittY;
				else
				{
					dTestY = (dTestY + OC.YMin()) / 2.;
					dSchrittY /= 2.;
				}

				TKt.SP(0).Y() = TKt.SP(1).Y() = DtoL(dTestY);
				xs1 = xs2 = DBL_MAX;
				i = -1;
				break;
			}

			else if (ECHT == Fo || INNEN_MIT == Fo || RAND_MIT == Fo)
			{
				if (ZPA.X() < xs1)
				{
					xs2 = xs1;
					xs1 = ZPA.X();
				}
				else if (ZPA.X() < xs2) xs2 = ZPA.X();
			}
		}
		while (j < lCSize - 2);

		i++;
		j = -1;
	}
	while (i < iKAnz);

	_ASSERTE (xs1 < DBL_MAX);
	_ASSERTE (xs2 < DBL_MAX);

	dInX = (xs2 + xs1) / 2.;
	dInY = dTestY;

	MP.X() = DtoL (dInX);
	MP.Y() = DtoL (dInY);

	if (INNERH == MP.EnthaltenIn (this))
		return true;

	_ASSERTE (false);

	return false;

} // InneliegenderPunkt
