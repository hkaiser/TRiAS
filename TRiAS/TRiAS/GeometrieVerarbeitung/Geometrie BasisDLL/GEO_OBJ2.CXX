// Weitere Methoden für ObjRechteck und Geometrieobjekte EObjekt bzw. EPunkt
// File: GEO_OBJ2.CXX
// W. Mörtl


#include "GeometrP.hxx"
#include "ErrorCorrection.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#if __HIGHC__
	#define max(a,b)  (((a) > (b)) ? (a) : (b))
	#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif // __HIGHC__





// ============================================================================================
// Methoden für OBJRECHTECK
// Memberfunktionen
// 2 Container haben mindestens 1 Punkt gemeinsam (true), sonst false
bool _GEOMETR_EXPORT ObjRechteck :: Durchschnitt (ObjRechteck& OC)
{
	return (_XMax >= OC._XMin && OC._XMax >= _XMin &&
			_YMax >= OC._YMin && OC._YMax >= _YMin);
}


// --------------------------------------------------------------------------------------------
// 2 Container haben nach Zugabe einer Eps-Toleranz (sowohl in x- als auch in y-Richtung)
// mindestens 1 Punkt gemeinsam (true), sonst false
bool _GEOMETR_EXPORT ObjRechteck :: EpsDurchschnitt (ObjRechteck& OC, KoOrd lEpsX,
													  KoOrd lEpsY)
{
	return (_XMax+lEpsX >= OC._XMin && OC._XMax+lEpsX >= _XMin &&
			_YMax+lEpsY >= OC._YMin && OC._YMax+lEpsY >= _YMin);
}


// --------------------------------------------------------------------------------------------
// Durchschnitt zweier Container ermitteln und als neuen Container in pDC zurückgeben;
// der Durchschnittscontainer kann zu einem Punkt oder einer Kante entarten; haben beide
// Ausgangscontainer keinen einzigen Punkt gemeinsam, wird false zurückgegeben, sonst true
bool _GEOMETR_EXPORT ObjRechteck :: DurchschnittsCont (ObjRechteck& AC, ObjRechteck& DC)
{
	DC.SetXMin (max (_XMin, AC._XMin));
	DC.SetXMax (min (_XMax, AC._XMax));
	DC.SetYMin (max (_YMin, AC._YMin));
	DC.SetYMax (min (_YMax, AC._YMax));
	if (DC.XMin() <= DC.XMax() && DC.YMin() <= DC.YMax())
		return true;
	return false;
}

 
// --------------------------------------------------------------------------------------------
// friend-Funktionen
// ObjRechteck OC1 liegt innerhalb des ObjRechteck OC2, dabei ist ein
// (teilweises) Überlappen der Kanten möglich (true), sonst false
bool _GEOMETR_EXPORT operator <= (ObjRechteck& O1, ObjRechteck& O2)
{
	return (O1.XMin() >= O2.XMin() && O1.XMax() <= O2.XMax() &&
			O1.YMin() >= O2.YMin() && O1.YMax() <= O2.YMax());
}
 
 
// --------------------------------------------------------------------------------------------
// ObjRechteck OC1 liegt außerhalb des ObjRechteck OC2, dabei ist ein
// (teilweises) Überlappen der Kanten möglich (true), sonst false
bool _GEOMETR_EXPORT operator >= (ObjRechteck& O1, ObjRechteck& O2)
{
	return (O1.XMin() <= O2.XMin() && O1.XMax() >= O2.XMax() &&
			O1.YMin() <= O2.YMin() && O1.YMax() >= O2.YMax());
}






// ============================================================================================
// Methoden für Basisklasse: EObjekt
// Konstruktor / Destruktor
_GEOMETR_EXPORT EObjekt :: EObjekt (void)
{
}


// --------------------------------------------------------------------------------------------
_GEOMETR_EXPORT EObjekt :: ~EObjekt (void)
{
}






// ============================================================================================
// Methoden für ElementarObjekt: EPUNKT
// friend-Funktionen

// --------------------------------------------------------------------------------------------
// Abstand zwischen den Punkten AP und EP mit Maximum-Norm
KoOrd _GEOMETR_EXPORT AbstandPktPktM (EPunkt& AP, EPunkt& EP)
{
KoOrd dx = labs (EP.X() - AP.X());
KoOrd dy = labs (EP.Y() - AP.Y());

	if (dx > dy) return dx;
	return dy;
}


// --------------------------------------------------------------------------------------------
// Abstand zwischen den Punkten (x1,y1) und (x2,y2) mit Maximum-Norm
KoOrd _GEOMETR_EXPORT AbstandPktPktM (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2)
{
KoOrd dx = labs (x2 - x1);
KoOrd dy = labs (y2 - y1);

	if (dx > dy) return dx;
	return dy;
}


// --------------------------------------------------------------------------------------------
// Abstand zwischen den Punkten AP und EP mit euklidischer Norm (als double-Wert)
double _GEOMETR_EXPORT AbstandPktPktE (EPunkt& AP, EPunkt& EP)
{
double dx = EP.X() - AP.X();
double dy = EP.Y() - AP.Y();

	return sqrt (dx*dx + dy*dy);
}


// --------------------------------------------------------------------------------------------
// Abstand zwischen den Punkten (x1,y1) und (x2,y2) mit euklidischer Norm (als double-Wert)
double _GEOMETR_EXPORT AbstandPktPktE (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2)
{
double dx = x2 - x1;
double dy = y2 - y1;

	return sqrt (dx*dx + dy*dy);
}


// --------------------------------------------------------------------------------------------
// Kreuzprodukt zweier Vektoren mit Randpunkten Pkt1 und Pkt2
double _GEOMETR_EXPORT KreuzProd (EPunkt& Pkt1, EPunkt& Pkt2)
{
	return (double)Pkt1.X()*Pkt2.Y() - (double)Pkt2.X()*Pkt1.Y();
}


// --------------------------------------------------------------------------------------------
// Kollinearität von 3 Punkten (true), sonst false
bool _GEOMETR_EXPORT Kollinear (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3)
{
double dx1 = Pkt2.X() - Pkt1.X();
double dy1 = Pkt2.Y() - Pkt1.Y();
double dx2 = Pkt3.X() - Pkt1.X();
double dy2 = Pkt3.Y() - Pkt1.Y();

	return (0. == dx1*dy2 - dx2*dy1);
}


// --------------------------------------------------------------------------------------------
// Kollinearität von 3 Punkten (true), sonst false
bool _GEOMETR_EXPORT Kollinear (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2, KoOrd x3, KoOrd y3)
{
double dx1 = x2 - x1;
double dy1 = y2 - y1;
double dx2 = x3 - x1;
double dy2 = y3 - y1;

	return (0. == dx1*dy2 - dx2*dy1);
}


// --------------------------------------------------------------------------------------------
// Epsilon-Kollinearität von 3 Punkten (true), sonst false;
// mindestens eine Höhe im Dreieck (Pkt1, Pkt2, Pkt3) ist höchstens iEpsilon lang
bool _GEOMETR_EXPORT EpsKollinear (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3, int iEpsilon)
{
double dAbst;	// Länge des Lots

	if (Strecke (Pkt1, Pkt2).LotPktGerade (Pkt3, dAbst) && dAbst <= iEpsilon)
		return true;
	if (Strecke (Pkt1, Pkt3).LotPktGerade (Pkt2, dAbst) && dAbst <= iEpsilon)
		return true;
	if (Strecke (Pkt2, Pkt3).LotPktGerade (Pkt1, dAbst) && dAbst <= iEpsilon)
		return true;
	return false;
}


// --------------------------------------------------------------------------------------------
// 3 Punkte sind paarweise eps-verschieden (true), sonst false
bool _GEOMETR_EXPORT PaarVergl (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3, int eps)
{
	return ((AbstandPktPktE (Pkt1, Pkt2) > eps) &&
			(AbstandPktPktE (Pkt1, Pkt3) > eps) &&
			(AbstandPktPktE (Pkt2, Pkt3) > eps));
}


// --------------------------------------------------------------------------------------------
// für 3 Punkte gilt, daß P2 von P1 und P3 eps-verschieden ist (true), sonst false
bool _GEOMETR_EXPORT MittVergl (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3, int eps)
{
	return ((AbstandPktPktE (Pkt2, Pkt1) > eps) &&
			(AbstandPktPktE (Pkt2, Pkt3) > eps));
}


// --------------------------------------------------------------------------------------------
// Rechteck aus den 2 Punkten Pkt1 und Pkt2 bilden
ObjRechteck _GEOMETR_EXPORT BuildRectangle (EPunkt& Pkt1, EPunkt& Pkt2)
{
KoOrd XMin = min (Pkt1.X(), Pkt2.X());
KoOrd XMax = max (Pkt1.X(), Pkt2.X());
KoOrd YMin = min (Pkt1.Y(), Pkt2.Y());
KoOrd YMax = max (Pkt1.Y(), Pkt2.Y());

	return ObjRechteck (XMin, XMax, YMin, YMax);
}

	

// --------------------------------------------------------------------------------------------
// Schwerpunkt des Dreiecks Pkt1-Pkt2-Pkt3
DoublePair _GEOMETR_EXPORT SchwerPunkt (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3)
{
double xs = (Pkt1.X() + Pkt2.X() + Pkt3.X()) / 3.;
double ys = (Pkt1.Y() + Pkt2.Y() + Pkt3.Y()) / 3.;

	return DoublePair (xs, ys);
}


// --------------------------------------------------------------------------------------------
// Memberfunktionen
// Epsilon-Gleichheit zwischen this-EPunkt und P; wenn bEuklid == true (default), dann wird die
// euklidische Norm verwendet, sonst die Maximum-Norm
bool _GEOMETR_EXPORT EPunkt :: EpsGleich (EPunkt& P, double dEpsX, double dEpsY, bool bEuklid)
{
	if (bEuklid)
//		return ( AbstandPktPktE(*this, P) <= sqrt(dEpsX*dEpsX + dEpsY*dEpsY) );
	{
	// 07.10.98: was wird diese Fehlerkorrektur für Auswirkungen haben ?????
	double dEps = (dEpsX + dEpsY) / 2.;

		return ( AbstandPktPktE (*this, P) <= dEps );
	}

	return (labs (_X - P._X) <= dEpsX && labs (_Y - P._Y) <= dEpsY);
}


// --------------------------------------------------------------------------------------------
// Epsilon-Gleichheit zwischen this-EPunkt und DoublePair DP; wenn bEuklid == true (default),
// dann wird die euklidische Norm verwendet, sonst die Maximum-Norm
bool _GEOMETR_EXPORT EPunkt :: EpsGleich (DoublePair DP, double dEpsX, double dEpsY,
										  bool bEuklid)
{
double dx = _X - DP.X();
double dy = _Y - DP.Y();

	if (bEuklid)
		// eigentlich auf beiden Seiten der Ungleichung sqrt()
//		return ( fabs(dx*dx + dy*dy) <= fabs(dEpsX*dEpsX + dEpsY*dEpsY) );
	{
	// 07.10.98: was wird diese Fehlerkorrektur für Auswirkungen haben ?????
	double dEps = (dEpsX + dEpsY) / 2.;

		return ( dx*dx + dy*dy <= dEps*dEps );
	}

	return ( fabs(dx) <= dEpsX && fabs(dy) <= dEpsY );
}


// --------------------------------------------------------------------------------------------
// Epsilon-Ungleichheit zwischen this-EPunkt und P; wenn bEuklid == true (default), dann wird
// die euklidische Norm verwendet, sonst die Maximum-Norm
bool _GEOMETR_EXPORT EPunkt :: EpsUngleich (EPunkt& P, double dEpsX, double dEpsY,
											bool bEuklid)
{
	if (bEuklid)
//		return ( AbstandPktPktE(*this, P) > sqrt(dEpsX*dEpsX + dEpsY*dEpsY) );
	{
	// 07.10.98: was wird diese Fehlerkorrektur für Auswirkungen haben ?????
	double dEps = (dEpsX + dEpsY) / 2.;

		return ( AbstandPktPktE (*this, P) > dEps );
	}

	return (labs (_X - P._X) > dEpsX || labs (_Y - P._Y) > dEpsY);
}


// --------------------------------------------------------------------------------------------
// Differenz zweier Vektoren
// (Subtrahend ist der Vektor, der mit Endpunkt Pkt übergeben wird)
EPunkt _GEOMETR_EXPORT EPunkt :: operator - (const EPunkt& Pkt)
{
	return EPunkt (_X - Pkt._X, _Y - Pkt._Y);
}


// --------------------------------------------------------------------------------------------
// EPunkt ungültig setzen
void _GEOMETR_EXPORT EPunkt :: UnValid (void)
{
	_X = LONG_MAX;
	_Y = LONG_MAX;
}


// --------------------------------------------------------------------------------------------
// Punkt hat ungültige Koordinaten (true), sonst false
bool _GEOMETR_EXPORT EPunkt :: isBad (void)
{
	return (_X < 0 || _X > MAXKOORD || _Y < 0 || _Y > MAXKOORD);
}


// --------------------------------------------------------------------------------------------
// Punkt liegt innerhalb des Containers OC (einschließlich auf dessen Rand), dann Rückgabe von
// true
bool _GEOMETR_EXPORT EPunkt :: PktInCont (ObjRechteck& OC)
{
	if (_X >= OC.XMin() && _X <= OC.XMax() && _Y >= OC.YMin() && _Y <= OC.YMax())
		return true;
	return false;
}


// --------------------------------------------------------------------------------------------
// Enthaltensein eines Punktes in der Fläche, die durch eine geschlossene Kante bzw. eine
// Flächenkontur gebildet wird;
// bez. der Lage AUF dem this-Vektor wird mit einer dEps-Genauigkeit gearbeitet (02.06.99);
// return-Werte sind
//   INNERH   Punkt liegt innerhalb der Fläche
//   KONTUR   Punkt liegt auf Flächenrand
//   AUSSERH  Punkt liegt außerhalb der Fläche
//   OFFEN    Flächenrand nicht geschlossen bzw. entartete Fläche
Posit _GEOMETR_EXPORT EPunkt :: Position (EKante* pK, double dEps)
{
	_ASSERTE (pK != 0);

	if (! pK) return UNKLAR;
	
// #HK020307
	PartialCleaningForLines(pK);

long n = pK->ASP(); // Kantenlänge

	if (pK->SP(0) != pK->SP(n-1))       // Kante nicht geschlossen
		return OFFEN;

Strecke TLinie (*this, *this);		// Testlinie

	TLinie.EP().X() = LONG_MAX;		// Testlinie soll waagrecht sein

long AnzSchn = 0;	// Zähler für echte Schnitte der Testlinie mit EKante K
long j = n-2;		// Index des letzten Konturpunktes, von dem bekannt ist, daß
					// er nicht auf der Testlinie liegt

	while (TLinie == pK->SP(j))
	{
		j--;
		if (j < 0)
			return OFFEN;	// entartete Fläche, d.h. alle Punkte liegen auf einer Geraden,
							// die mit der Trägergeraden der TLinie identsch ist
	}

int r1, r2, r3;
double dAbst;		// absoluter Abstand von Punkt Pkt zur Strecke Str
DoublePair DP0, DP1, DP2;

	DP0.X() = _X;
	DP0.Y() = _Y;

	for (long i = 0; i < n-1; i++)
	{
		// Test, ob this-Punkt mit dEps-Genauigkeit AUF pK-Kante liegt
		DP1.X() = pK->SP(i).X();
		DP1.Y() = pK->SP(i).Y();
		DP2.X() = pK->SP(i+1).X();
		DP2.Y() = pK->SP(i+1).Y();
		AbstandPktStrecke (DP0, DP1, DP2, dAbst);
		if (dAbst < 0)
			return UNKLAR;
		if (dAbst <= dEps)
			return KONTUR;	// this-Punkt liegt mit dEps-Genauigkeit AUF pK-Kante

		// Im 1. Teil der nachfolgenden if-Anweisung wird der Fall behandelt, daß der nächste
		// Stützpunkt pK->SP(i) nicht auf der waagrechten Testlinie liegt.
		// Liegt pK->SP(i) auf der Testlinie (else-Zweig), wird pK->SP(i) i.a. ignoriert.
		// Liegt jedoch der zu testende Punkt im Dreieck pK->SP(i-1), pK->SP(i),
		// pK->SP(i+1), ergibt sich durch das Weglassen von pK->SP(i) eine
		// Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
		if (!(TLinie == pK->SP(i)))
		{
			// Zähler inkrementieren, wenn echter Schnitt vorliegt, d. h. pK->SP(i) und
			// und pK->SP(j) auf verschiedenen Seiten der Testlinie liegen
			if (Intersection (pK->SP(i).X(), pK->SP(i).Y(), pK->SP(j).X(), pK->SP(j).Y(),
							  TLinie.AP().X(), TLinie.AP().Y(), TLinie.EP().X(), TLinie.EP().Y()))
				AnzSchn++;
			j = i;
		}
		else    // pK->SP(i) liegt auf der Teststrecke
		{
			r2 = TurnDirection (pK->SP(i).X(), pK->SP(i).Y(), pK->SP(i+1).X(), pK->SP(i+1).Y(), _X, _Y);

			if (i > 0)
			{
				r1 = TurnDirection (pK->SP(i-1).X(), pK->SP(i-1).Y(), pK->SP(i).X(), pK->SP(i).Y(), _X, _Y);
				r3 = TurnDirection (pK->SP(i+1).X(), pK->SP(i+1).Y(), pK->SP(i-1).X(), pK->SP(i-1).Y(), _X, _Y);
			}
			else    // i = 0
			{
				r1 = TurnDirection (pK->SP(n-2).X(), pK->SP(n-2).Y(), pK->SP(0).X(), pK->SP(0).Y(), _X, _Y);
				r3 = TurnDirection (pK->SP(1).X(), pK->SP(1).Y(), pK->SP(n-2).X(), pK->SP(n-2).Y(), _X, _Y);
			}

			if (r1 >= 0 && r2 >= 0 && r3 >= 0)	// konvexe Ecke der geschlossenen pK-EKante:
				return INNERH;					//  Punkt liegt innerhalb
			if (r1 <= 0 && r2 <= 0 && r3 <= 0)	// konkave Ecke der geschlossenen pK-EKante:
				return AUSSERH;					//  Punkt liegt außerhalb
		}

	}
	if (AnzSchn & 1)        // ungerader Zähler bedeutet Enthaltensein
		return INNERH;
	return AUSSERH;
} // Position


// --------------------------------------------------------------------------------------------
// Test, wie der this-EPunkt bez. der EKante pKt liegt;
// return-Werte sind
//   AUSSERH  Punkt liegt außerhalb der Kante
//   KONTUR   Punkt liegt auf einem  der beiden Endpunkte einer offenen Kante
//   INNERH   Punkt liegt "richtig" innerhalb der Kante (NICHT auf einem  der beiden Endpunkte
//            einer offenen Kante)
//   UNKLAR   Kante ist nicht definiert (NULL-Pointer)
Posit _GEOMETR_EXPORT EPunkt :: PunktAufKante (EKante* pKt)
{
	_ASSERTE (pKt != 0);

	if (! pKt) return UNKLAR;

ObjRechteck OC = pKt->GetCont ();

	if (!PktInCont (OC))
		return AUSSERH;	// this-EPunkt liegt nicht im pKt-Container

long lKL = pKt->ASP();

	if (pKt->SP(0) != pKt->SP(lKL-1) &&						// Kante offen
		(*this == pKt->SP(0) || *this == pKt->SP(lKL-1)))	// this-EPunkt == pKt-Randpunkt
		return KONTUR;

	for (long i = 0; i < lKL-1; i++)
		if (0 == TurnDirection (pKt->SP(i).X(), pKt->SP(i).Y(), pKt->SP(i+1).X(),
								pKt->SP(i+1).Y(), _X, _Y))
			return INNERH;

	return AUSSERH;

} // PunktAufKante


// --------------------------------------------------------------------------------------------
// Lage des this-Punktes bezüglich der Fläche pFl; es werden auch Inseln von pFl mit
// berücksichtigt, d.h. liegt this-EPunkt innerhalb einer pFl-Insel, dann liegt this-EPunkt
// außerhalb von pFl
Posit _GEOMETR_EXPORT EPunkt :: EnthaltenIn (EFlaeche* pFl, void*)
{
	_ASSERTE (pFl != 0);

	if (! pFl) return UNKLAR;

ObjRechteck OC = pFl->GetCont();

	if (PktInCont (OC) == false)
		return AUSSERH;	// this-EPunkt liegt nicht im pFl-Container

int iKAnz = pFl->KantenAnz ();	// Anzahl der Konturen von pFl
Posit posLage;    // Lagemarkierung

	for (int i = 0; i < iKAnz; i++)
	{
		posLage = Position (&pFl->KA(i));    // Lagemarkierung

		// Test mit pFl-Innenkonturen (i > 0) nur erforderlich, wenn der Test mit der
		// pFl-Außenkontur posLage == INNERH ergeben hat
		if (i == 0 && posLage != INNERH)
			return posLage;
			
		if (i > 0)			// pFl-Innenkonturen wurden noch mit herangezogen
		{
			// für INNERH, KONTUR und ILLPARS ist alles klar
			if (posLage == INNERH || posLage == KONTUR || posLage == UNKLAR)
			{
				// vollständig innerhalb einer pFl-Insel heißt außerhalb der pFl-Fläche
				if (posLage == INNERH)
					posLage = AUSSERH;
				return posLage;
			}
		}
	} // für AUSSERH ist posLage noch nicht eindeutig klärbar

	
	// dieser Programmteil wird nur erreicht, wenn this-EPunkt innerhalb der Außenkontur liegt
	// und bez. aller Innenkonturen (so es sie überhaupt gibt) AUSSERH gilt; dann gilt INNERH
	return INNERH;

} // EPunkt :: EnthaltenIn





// ============================================================================================
// Methoden für Klasse: PUNKTVEC
// Konstruktor
PunktVec :: PunktVec (long lLen)
{
	_ASSERTE (lLen > 0);

	m_lLen = 0;
	m_pSPF = 0;  // für alle Fälle
	if (lLen <= 0)
	{
		DEX_Error (RC_ctPunktVec, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine PunktVec::PunktVec", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	m_pSPF = new SpecPunkt[lLen];
	if (m_pSPF == 0)
	{
		DEX_Error (RC_ctPunktVec, EC_NOMEMORY);
		return;
	}
	m_lLen = lLen;
}


// --------------------------------------------------------------------------------------------
// Destruktor	
PunktVec :: ~PunktVec (void)
{
	if (m_pSPF)
	{
		DELETE_VEC (m_pSPF);
		m_pSPF = 0;
	}
	m_lLen = 0;
}
