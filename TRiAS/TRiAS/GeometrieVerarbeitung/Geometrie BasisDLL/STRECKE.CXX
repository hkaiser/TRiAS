// Geometrieobjekt Strecke
// File: STRECKE.CXX
// W. Mörtl

#include "GeometrP.hxx"

#include "FormatString.hxx"	// Format()


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#if __HIGHC__
	#define max(a,b)  (((a) > (b)) ? (a) : (b))
	#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif // __HIGHC__





// --------------------------------------------------------------------------------------------
// Berechnung der y-Koordinate eines Punktes auf der Strecke bei gegebenem x-Wert. true, wenn
// Koordinate berechenbar, sonst false
bool _GEOMETR_EXPORT Strecke :: YWert (KoOrd x, KoOrd& y)
{
KoOrd x1 = _AP.X();
KoOrd y1 = _AP.Y();
KoOrd x2 = _EP.X();
KoOrd y2 = _EP.Y();

	if (x < min(x1, x2) || x > max(x1, x2))
		return false;

	// y = ((x - x1) / (x2 - x1) * (y2 - y1)) + y1
	if (x1 == x2)
		y = y1;
	else
	     y = DtoL ((double)(x - x1) * (double)(y2 - y1) / (double)(x2 - x1)) + y1;
	return true;
} // YWert

	
// --------------------------------------------------------------------------------------------
// Die Container zweier Strecken (this-Strecke und die durch Anfangspunkt AP und Endpunkt EP
// definierte Strecke) haben wenigstens einen Punkt gemeinsam (true), sonst false
bool _GEOMETR_EXPORT Strecke :: ContainerSchnitt (EPunkt& AP, EPunkt& EP)
{
KoOrd xmin1 = min (_AP.X(), _EP.X());	// min. x-Koordinate,
KoOrd xmax1 = max (_AP.X(), _EP.X());	// max. x-Koordinate,
KoOrd ymin1 = min (_AP.Y(), _EP.Y());	// min. y-Koordinate,
KoOrd ymax1 = max (_AP.Y(), _EP.Y());	// max. y-Koordinate des Containers der this-Strecke
KoOrd xmin2 = min (AP.X(), EP.X());
KoOrd xmax2 = max (AP.X(), EP.X());
KoOrd ymin2 = min (AP.Y(), EP.Y());
KoOrd ymax2 = max (AP.Y(), EP.Y());

	return ((xmax1 >= xmin2) && (xmax2 >= xmin1) && (ymax1 >= ymin2) && (ymax2 >= ymin1));
}
	

// --------------------------------------------------------------------------------------------
// Berechnung eines bzw. zweier gemeinsamer Punkte von zwei Strecken (this-Strecke und die durch
// Anfangspunkt AP und Endpunkt EP definierte Strecke) unter Berücksichtigung einer möglichen
// Epsilon-Abweichung; return-Werte sind
//   KEINE      Strecken schneiden sich nicht, GP1 und GP2 unbestimmt
//   ECHT       Strecken schneiden sich, GP1 enthält Schnittpunkt, GP2 unbestimmt
//   RAND       Strecken berühren sich in jeweils genau einem Endpunkt, GP1 enthält
//              Berührungspunkt, GP2 unbestimmt
//   INNEN      Endpunkt der einen Strecke liegt im "Inneren" der anderen Strecke,
//              GP1 enthält Berührungspunkt, GP2 unbestimmt
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander, GP1 und GP2
//              sind die beiden Endpunkte des gemeinsamen Bereiches
SchnittErg _GEOMETR_EXPORT Strecke :: EpsGemeinsamePunkte (EPunkt& AP, EPunkt& EP,
								  DoublePair& GP1, DoublePair& GP2, double dEpsX, double dEpsY)
{
// ????????????  reicht das bei einer geodätischen Datenbank aus  ???????????
//double dEps = sqrt(dEpsX*dEpsX + dEpsY*dEpsY);
double dEps = max (dEpsX, dEpsY);	// 28.01.98

//	if (_AP.EpsGleich(_EP,false,dEps,dEps) || AP.EpsGleich(EP,false,dEps,dEps))
	if (_AP.EpsGleich(_EP,dEpsX,dEpsY,false) || AP.EpsGleich(EP,dEpsX,dEpsY,false))	// 28.01.98
		return KEINE;	// eine der beiden Strecken ist Eps-entartet

	// ein echter Schnitt geht vor alle anderen Tests (09.02.98)
	if (ECHT == Gemeinsam0 (AP, EP, GP1))
		return ECHT;
		
double dAStr;	// Abstand von _AP zur Strecke Str
double dEStr;	// Abstand von _EP zur Strecke Str
double dAthis;	// Abstand von AP zur this-Strecke
double dEthis;	// Abstand von EP zur this-Strecke

	AbstandPktStrecke (DoublePair(_AP.X(),_AP.Y()), DoublePair(AP.X(), AP.Y()),
					   DoublePair(EP.X(),EP.Y()), dAStr);
	AbstandPktStrecke (DoublePair(_EP.X(),_EP.Y()), DoublePair(AP.X(), AP.Y()),
					   DoublePair(EP.X(),EP.Y()), dEStr);
	AbstandPktStrecke (DoublePair(AP.X(),AP.Y()), DoublePair(_AP.X(), _AP.Y()),
					   DoublePair(_EP.X(),_EP.Y()), dAthis);
	AbstandPktStrecke (DoublePair(EP.X(),EP.Y()), DoublePair(_AP.X(), _AP.Y()),
					   DoublePair(_EP.X(),_EP.Y()), dEthis);

int iAnz = 0;		// Anzahl der Abstände, die höchstens dEps sind

	if (dAStr <= dEps) iAnz++;
	if (dEStr <= dEps) iAnz++;
	if (dAthis <= dEps) iAnz++;
	if (dEthis <= dEps) iAnz++;

	switch (iAnz)
	{
		case 0:	// Strecken schneiden sich nicht (KEINE) oder richtig (ECHT)
//			return Gemeinsam0 (AP, EP, GP1);	09.02.98
			return KEINE;

		case 1:	// Innenberührung (INNEN) oder Überlappung (UEBERLAPP)
			return Gemeinsam1 (AP, EP, GP1, GP2, dAStr, dEStr, dAthis, dEthis, dEps);

		case 2:	// Randberührung (RAND) oder Überlappung (UEBERLAPP)
			return Gemeinsam2 (AP, EP, GP1, GP2, dAStr, dEStr, dAthis, dEthis, dEps);

		case 3:	// Überlappung (UEBERLAPP)
			if (dAStr > dEps || dEStr > dEps)
			{
				GP1.X() = AP.X();
				GP1.Y() = AP.Y();
				GP2.X() = EP.X();
				GP2.Y() = EP.Y();
				return UEBERLAPP;
			}
			// dAthis > dEps oder dEthis > dEps
			GP1.X() = _AP.X();
			GP1.Y() = _AP.Y();
			GP2.X() = _EP.X();
			GP2.Y() = _EP.Y();
			return UEBERLAPP;
			
		case 4:	// Überlappung (UEBERLAPP)
			GP1.X() = _AP.X();
			GP1.Y() = _AP.Y();
			GP2.X() = _EP.X();
			GP2.Y() = _EP.Y();
			return UEBERLAPP;
	}
	
	DEX_Error (RC_EpsGemeinsamePunkte, EC_ILLPARS);
	MessageBox (__hWndM, "Fehlerhafter Parameter in Routine Strecke::EpsGemeinsamePunkte", "Achtung:", MB_ICONEXCLAMATION | MB_OK);

	_ASSERTE (false);

	return KEINE;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden

} // EpsGemeinsamePunkte


// --------------------------------------------------------------------------------------------
// Hilfsroutine für EpsGemeinsamePunkte(), wenn keine der Abstände höchstens dEps lang ist
SchnittErg Strecke :: Gemeinsam0 (EPunkt& AP, EPunkt& EP, DoublePair& GP1)
{
	if ((TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), AP.X(), AP.Y()) *
		 TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), EP.X(), EP.Y()) > 0) ||
	    (TurnDirection (AP.X(), AP.Y(), EP.X(), EP.Y(), _AP.X(), _AP.Y()) *
		 TurnDirection (AP.X(), AP.Y(), EP.X(), EP.Y(), _EP.X(), _EP.Y()) > 0))
		return KEINE;

	GP1 = StreckenSchnittPunkt (_AP, _EP, AP, EP);
	return ECHT;
	
} // Gemeinsam0


// --------------------------------------------------------------------------------------------
// Hilfsroutine für EpsGemeinsamePunkte(), wenn genau ein Abstand höchstens dEps lang ist
SchnittErg Strecke :: Gemeinsam1 (EPunkt& AP, EPunkt& EP, DoublePair& GP1, DoublePair& GP2,
						 double dAStr, double dEStr, double dAthis, double dEthis, double dEps)
{
	if ((TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), AP.X(), AP.Y()) *
		 TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), EP.X(), EP.Y()) > 0) ||
	    (TurnDirection (AP.X(), AP.Y(), EP.X(), EP.Y(), _AP.X(), _AP.Y()) *
		 TurnDirection (AP.X(), AP.Y(), EP.X(), EP.Y(), _EP.X(), _EP.Y()) > 0))
	{
		// gemeinsamer Punkt zwischen Str1- und Str2-Strecke
		if (dAStr <= dEps)
		{
			GP1.X() = _AP.X();
			GP1.Y() = _AP.Y();
			return INNEN;
		}
		if (dEStr <= dEps)
		{
			GP1.X() = _EP.X();
			GP1.Y() = _EP.Y();
			return INNEN;
		}
		if (dAthis <= dEps)
		{
			GP1.X() = AP.X();
			GP1.Y() = AP.Y();
			return INNEN;
		}
		// es bleibt nur noch dEthis <= dEps
		GP1.X() = EP.X();
		GP1.Y() = EP.Y();
		return INNEN;
	}
	
	// Str1- und Str2-Strecke haben einen gemeinsamen Punkt
	GP1 = StreckenSchnittPunkt (_AP, _EP, AP, EP);	// gemeinsamer Punkt beider Strecken
	if (dAStr <= dEps)
	{
//		if (GP1.EpsGleich(_AP,false,dEps,dEps))
	double dx = GP1.X() - _AP.X();
	double dy = GP1.Y() - _AP.Y();

		if (dx*dx + dy*dy <= 2.*dEps*dEps)	// das Radizieren auf beiden Seiten spare ich mir
		{
			GP1.X() = _AP.X();
			GP1.Y() = _AP.Y();
			return INNEN;
		}
		GP2.X() = _AP.X();
		GP2.Y() = _AP.Y();
		return UEBERLAPP;
	}
	if (dEStr <= dEps)
	{
//		if (GP1.EpsGleich(_EP,false,dEps,dEps))
	double dx = GP1.X() - _EP.X();
	double dy = GP1.Y() - _EP.Y();

		if (dx*dx + dy*dy <= 2.*dEps*dEps)	// das Radizieren auf beiden Seiten spare ich mir
		{
			GP1.X() = _EP.X();
			GP1.Y() = _EP.Y();
			return INNEN;
		}
		GP2.X() = _EP.X();
		GP2.Y() = _EP.Y();
		return UEBERLAPP;
	}
	if (dAthis <= dEps)
	{
//		if (GP1.EpsGleich(AP,false,dEps,dEps))
	double dx = GP1.X() - AP.X();
	double dy = GP1.Y() - AP.Y();

		if (dx*dx + dy*dy <= 2.*dEps*dEps)	// das Radizieren auf beiden Seiten spare ich mir
		{
			GP1.X() = AP.X();
			GP1.Y() = AP.Y();
			return INNEN;
		}
		GP2.X() = AP.X();
		GP2.Y() = AP.Y();
		return UEBERLAPP;
	}
	// es bleibt nur noch dEthis <= dEps
//	if (GP1.EpsGleich(EP,false,dEps,dEps))
double dx = GP1.X() - EP.X();
double dy = GP1.Y() - EP.Y();

	if (dx*dx + dy*dy <= 2.*dEps*dEps)	// das Radizieren auf beiden Seiten spare ich mir
	{
		GP1.X() = EP.X();
		GP1.Y() = EP.Y();
		return INNEN;
	}
	GP2.X() = EP.X();
	GP2.Y() = EP.Y();
	return UEBERLAPP;
	
} // Gemeinsam1


// --------------------------------------------------------------------------------------------
// Hilfsroutine für EpsGemeinsamePunkte(), wenn genau zwei Abstände höchstens dEps lang ist
SchnittErg Strecke :: Gemeinsam2 (EPunkt& AP, EPunkt& EP, DoublePair& GP1, DoublePair& GP2,
						 double dAStr, double dEStr, double dAthis, double dEthis, double dEps)
{
	if (dAStr <= dEps)
	{
		GP1.X() = _AP.X();
		GP1.Y() = _AP.Y();
		if (_AP.EpsGleich (AP,dEps,dEps) || _AP.EpsGleich (EP,dEps,dEps))
			return RAND;
		if (dEStr <= dEps)
		{
			GP2.X() = _EP.X();
			GP2.Y() = _EP.Y();
			return UEBERLAPP;
		}
		if (dAthis <= dEps)
		{
			GP2.X() = AP.X();
			GP2.Y() = AP.Y();
			return UEBERLAPP;
		}
		// es bleibt nur noch dEthis <= dEps
		GP2.X() = EP.X();
		GP2.Y() = EP.Y();
		return UEBERLAPP;
	}
	if (dEStr <= dEps)
	{
		GP1.X() = _EP.X();
		GP1.Y() = _EP.Y();
		if (_EP.EpsGleich (AP,dEps,dEps) || _EP.EpsGleich (EP,dEps,dEps))
			return RAND;
		if (dAStr <= dEps)
		{
			GP2.X() = _AP.X();
			GP2.Y() = _AP.Y();
			return UEBERLAPP;
		}
		if (dAthis <= dEps)
		{
			GP2.X() = AP.X();
			GP2.Y() = AP.Y();
			return UEBERLAPP;
		}
		// es bleibt nur noch dEthis <= dEps
		GP2.X() = EP.X();
		GP2.Y() = EP.Y();
		return UEBERLAPP;
	}
	if (dAthis <= dEps)
	{
		GP1.X() = AP.X();
		GP1.Y() = AP.Y();
		if (AP.EpsGleich (_AP,dEps,dEps) || AP.EpsGleich (_EP,dEps,dEps))
			return RAND;
		if (dEthis <= dEps)
		{
			GP2.X() = EP.X();
			GP2.Y() = EP.Y();
			return UEBERLAPP;
		}
		if (dAStr <= dEps)
		{
			GP2.X() = _AP.X();
			GP2.Y() = _AP.Y();
			return UEBERLAPP;
		}
		// es bleibt nur noch dEStr <= dEps
		GP2.X() = _EP.X();
		GP2.Y() = _EP.Y();
		return UEBERLAPP;
	}
	// es bleibt nur noch dEthis <= dEps
	GP1.X() = EP.X();
	GP1.Y() = EP.Y();
	if (EP.EpsGleich (_AP,dEps,dEps) || EP.EpsGleich (_EP,dEps,dEps))
		return RAND;
	if (dAthis <= dEps)
	{
		GP2.X() = AP.X();
		GP2.Y() = AP.Y();
		return UEBERLAPP;
	}
	if (dAStr <= dEps)
	{
		GP2.X() = _AP.X();
		GP2.Y() = _AP.Y();
		return UEBERLAPP;
	}
	// es bleibt nur noch dEStr <= dEps
	GP2.X() = _EP.X();
	GP2.Y() = _EP.Y();
	return UEBERLAPP;
	
} // Gemeinsam2


// --------------------------------------------------------------------------------------------
// Pkt liegt auf der euklidischen Strecke einschließlich der beiden Endpunkte (true), sonst
// false; für Anfangs- und Endpunkt der Strecke sowie fraglichen Punkt muß gelten
// TurnDirection (AP, EP, Pkt) == 0, dies impliziert die Kollinearität
bool _GEOMETR_EXPORT Strecke :: operator == (EPunkt& Pkt)
{
	return (0 == TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), Pkt.X(), Pkt.Y()));
}


// --------------------------------------------------------------------------------------------
// (absolute) Länge d des Lots von Punkt Pt auf die Trägergerade der this-Strecke;
// Wird true zurückgegeben, dann ist der Abstand zur Trägergeraden der this-Strecke bestimmbar,
// bei false ist die this-Strecke entartet (Anfangs- und Endpunkt fallen zusammen). d ist dabei
// unbestimmt.
bool _GEOMETR_EXPORT Strecke :: LotPktGerade (EPunkt& Pt, double& d)
{
	if (Pt == _AP || Pt == _EP)
	{
		d = 0.;
		return true;
	}

double xl, yl;	// Koordinaten des Lotpunktes von Pt auf die Trägergerade der this-Strecke

	if (!GeradenLotPunkt (Pt.X(), Pt.Y(), _AP.X(), _AP.Y(), _EP.X(), _EP.Y(), xl, yl))
		return false;

double dx = Pt.X() - xl;
double dy = Pt.Y() - yl;

	d = sqrt (dx*dx + dy*dy);
	return true;

} // LotPktGerade


// --------------------------------------------------------------------------------------------
// (absolute) Länge d des Lots von Punkt Pt auf die this-Strecke (mit Maximum-Norm);
// Wird true zurückgegeben, dann ist der Abstand zur this-Strecke bestimmbar, bei false gilt
// der berechnete Abstand nur für die Trägergerade, nicht aber für die Strecke. Ist die
// this-Strecke entartet (Anfangs- und Endpunkt fallen zusammen), wird ebenfalls false
// zurückgegeben. d ist dabei negativ.
// In LPkt wird der Lotpunkt von Pt auf Trägergerade der this-Strecke zurückgegeben.
bool _GEOMETR_EXPORT Strecke :: LotPktStrecke (EPunkt& Pt, KoOrd& d, EPunkt& LPkt)
{
	if (Pt == _AP)
	{
		d = 0;
		LPkt = _AP;
		return true;
	}

	if (Pt == _EP)
	{
		d = 0;
		LPkt = _EP;
		return true;
	}

double xl, yl;	// Koordinaten des Lotpunktes von Pt auf die Trägergerade der this-Strecke

	if (!GeradenLotPunkt (Pt.X(), Pt.Y(), _AP.X(), _AP.Y(), _EP.X(), _EP.Y(), xl, yl)) 
	{
		d = -1;
		return false;
	}

double dx = fabs (Pt.X() - xl);
double dy = fabs (Pt.Y() - yl);

	if (dx > dy) d = DtoL (dx);
	else d = DtoL (dy);

	LPkt.X() = DtoL (xl);
	LPkt.Y() = DtoL (yl);

	if (_AP.X() == _EP.X() &&	// senkrechte Strecke (28.07.98)
		min (_AP.Y(), _EP.Y()) <= LPkt.Y() && LPkt.Y() <= max (_AP.Y(), _EP.Y()))
		return true;

	if (_AP.Y() == _EP.Y() &&	// waagrechte Strecke
		min (_AP.X(), _EP.X()) <= LPkt.X() && LPkt.X() <= max (_AP.X(), _EP.X()))
		return true;

	// Normalfall (schräge Strecke)
	if (min (_AP.X(), _EP.X()) <= LPkt.X() && LPkt.X() <= max (_AP.X(), _EP.X()) &&
		min (_AP.Y(), _EP.Y()) <= LPkt.Y() && LPkt.Y() <= max (_AP.Y(), _EP.Y()))
		return true;
	return false;

} // LotPktStrecke (Maximum-Norm)


// --------------------------------------------------------------------------------------------
// (absolute) Länge d des Lots von Punkt Pt auf die this-Strecke (mit euklidischer Norm);
// Wird true zurückgegeben, dann ist der Abstand zur this-Strecke bestimmbar, bei false gilt
// der berechnete Abstand nur für die Trägergerade, nicht aber für die Strecke. Ist die
// this-Strecke entartet (Anfangs- und Endpunkt fallen zusammen), wird ebenfalls false
// zurückgegeben. d ist dabei negativ.
// In LPkt werden die Koordinaten im double-Format des Lotpunktes von Pt auf Trägergerade der
// this-Strecke zurückgegeben.
bool _GEOMETR_EXPORT Strecke :: LotPktStrecke (EPunkt& Pt, double& d, DoublePair& LPkt)
{
	if (Pt == _AP)
	{
		d = 0.;
		LPkt.X() = _AP.X();
		LPkt.Y() = _AP.Y();
		return true;
	}

	if (Pt == _EP)
	{
		d = 0.;
		LPkt.X() = _EP.X();
		LPkt.Y() = _EP.Y();
		return true;
	}

	if (!GeradenLotPunkt (Pt.X(), Pt.Y(), _AP.X(), _AP.Y(), _EP.X(), _EP.Y(),
								  LPkt.X(),LPkt.Y()))
	{
		d = -1.;
		return false;
	}

double dx = LPkt.X() - Pt.X();
double dy = LPkt.Y() - Pt.Y();

	d = sqrt (dx*dx + dy*dy);

	if (_AP.X() == _EP.X() &&	// senkrechte Strecke (28.07.98)
		min (_AP.Y(), _EP.Y()) <= LPkt.Y() && LPkt.Y() <= max (_AP.Y(), _EP.Y()))
		return true;

	if (_AP.Y() == _EP.Y() &&	// waagrechte Strecke
		min (_AP.X(), _EP.X()) <= LPkt.X() && LPkt.X() <= max (_AP.X(), _EP.X()))
		return true;

	// Normalfall (schräge Strecke)
	if (min (_AP.X(), _EP.X()) <= LPkt.X() && LPkt.X() <= max (_AP.X(), _EP.X()) &&
		min (_AP.Y(), _EP.Y()) <= LPkt.Y() && LPkt.Y() <= max (_AP.Y(), _EP.Y()))
		return true;
	return false;

} // LotPktStrecke (euklidische Norm)




///////////////////////////////////////////////////////////////////////////////////////////////
// Für die nachfolgenden Routinen wird keine this-Strecke mehr vorausgesetzt. Anfangspunkt AP
// und Endpunkt EP der Strecke werden als Parameter übergeben. Damit kann das Bilden eines
// Strecken- Objektes entfallen

// --------------------------------------------------------------------------------------------
// Mittelpunkt der Strecke (Pkt1, Pkt2) (als 2 double-Werte)
void _GEOMETR_EXPORT Mitte (EPunkt& Pkt1, EPunkt& Pkt2, double& xm, double& ym)
{
double x1 = Pkt1.X();
double y1 = Pkt1.Y();
double x2 = Pkt2.X();
double y2 = Pkt2.Y();

	xm = ((double)x1 + (double)x2) / 2.;
	ym = ((double)y1 + (double)y2) / 2.;
}


// --------------------------------------------------------------------------------------------
// Koordinaten des Teilungspunktes DPT der Strecke DP1-DP2, der die Strecke
// im Verhältnis m:n = dLambda teilt
void _GEOMETR_EXPORT StreckenTeilung (DoublePair DP1, DoublePair DP2, DoublePair& DPT,
									  double dLambda)
{
double x1 = DP1.X();
double y1 = DP1.Y();
double x2 = DP2.X();
double y2 = DP2.Y();

	DPT.X() = (x1 + dLambda*x2) / (1. + dLambda);
	DPT.Y() = (y1 + dLambda*y2) / (1. + dLambda);
} // StreckenTeilung


// --------------------------------------------------------------------------------------------
// Durch Anfangspunkt AP und Endpunkt EP ist eine Strecke gegeben. Gesucht ist ein auf 
// dieser Strecke liegender Punkt TPkt, der von AP eine Entfernung von dTeilLaenge hat. Ist
// Streckenlänge == 0 oder dTeilLaenge > Streckenlänge, wird false zurückgegeben, sonst true.
bool _GEOMETR_EXPORT StreckenTeilung (EPunkt& AP, EPunkt& EP, double dTeilLaenge, EPunkt& TPkt)
{
double dStrLaenge = AbstandPktPktE (AP, EP);	// Länge der Strecke AP-EP

	if (dStrLaenge == 0 ||			// entartete Strecke
		dTeilLaenge > dStrLaenge)	// Teilstrecke zu lang, d.h. Strecke kann nicht geteilt werden
		return false;

	if (dTeilLaenge == 0)
	{
		TPkt = AP;
		return true;
	}

	if (dTeilLaenge == dStrLaenge)
	{
		TPkt = EP;
		return true;
	}

double m = dTeilLaenge;					// m und n stehen für das Verhältnis, in dem
double n = dStrLaenge - dTeilLaenge;	//  die Streckenlänge geteilt werden soll

	TPkt.X() = DtoL ((AP.X() * n + EP.X() * m) / dStrLaenge);
	TPkt.Y() = DtoL ((AP.Y() * n + EP.Y() * m) / dStrLaenge);

	return true;

} // StreckenTeilung


// --------------------------------------------------------------------------------------------
// Lotpunkt LPkt ermitteln, der sich ergibt, wenn von Pkt auf die Strecke AP-EP das Lot gefällt
// wird. Wird true zurückgegeben, dann liegt der Lotpunkt auf der Strecke (einschl. Anfangs-
// und Endpunkt), bei false liegt der Lotpunkt nur auf der Trägergerade, nicht aber auf der
// Strecke. Ist die Strecke entartet (Anfangs- und Endpunkt fallen zusammen), wird ebenfalls
// false zurückgegeben.
bool _GEOMETR_EXPORT LotPunkt (EPunkt& Pkt, EPunkt& AP, EPunkt& EP, EPunkt& LPkt)
{
	if (Pkt == AP)
	{
		LPkt = AP;
		return true;
	}

	if (Pkt == EP)
	{
		LPkt = EP;
		return true;
	}

double xl, yl;	// Koordinaten des Lotpunktes von Pkt auf die Trägergerade der Strecke AP-EP

	if (!GeradenLotPunkt (Pkt.X(), Pkt.Y(), AP.X(), AP.Y(), EP.X(), EP.Y(), xl, yl))
		return false;

	LPkt.X() = DtoL (xl);
	LPkt.Y() = DtoL (yl);

	if (AP.X() == EP.X() &&	// senkrechte Strecke (28.07.98)
		min (AP.Y(), EP.Y()) <= LPkt.Y() && LPkt.Y() <= max (AP.Y(), EP.Y()))
		return true;

	if (AP.Y() == EP.Y() &&	// waagrechte Strecke
		min (AP.X(), EP.X()) <= LPkt.X() && LPkt.X() <= max (AP.X(), EP.X()))
		return true;

	// Normalfall (schräge Strecke)
	if (min (AP.X(), EP.X()) <= LPkt.X() && LPkt.X() <= max (AP.X(), EP.X()) &&
		min (AP.Y(), EP.Y()) <= LPkt.Y() && LPkt.Y() <= max (AP.Y(), EP.Y()))
		return true;
	return false;

} // LotPunkt


// --------------------------------------------------------------------------------------------
// (absolute) Länge d des Lots von Punkt Pkt auf die Strecke AP-EP (mit euklidischer Norm);
// Wird true zurückgegeben, dann ist der Abstand zur Strecke bestimmbar, bei false gilt der
// berechnete Abstand nur für die Trägergerade, nicht aber für die Strecke. Ist die Strecke
// entartet (Anfangs- und Endpunkt fallen zusammen), wird ebenfalls false zurückgegeben. d ist
// dabei negativ.
bool _GEOMETR_EXPORT LotStrecke (EPunkt& Pkt, EPunkt& AP, EPunkt& EP, double& d)
{
	if (IdenticalPoints (AP.X(), AP.Y(), EP.X(), EP.Y()))	// Strecke entartet
	{
		d = -1.;
		return false;
	}

	if (Pkt == AP || Pkt == EP)
	{
		d = 0.;
		return true;
	}

double xl, yl;	// Koordinaten des Lotpunktes von Pkt auf die Trägergerade der Strecke AP-EP

	if (!GeradenLotPunkt (Pkt.X(), Pkt.Y(), AP.X(), AP.Y(), EP.X(), EP.Y(), xl, yl))
	{
		d = -1.;
		return false;
	}

double dx = xl - Pkt.X();
double dy = yl - Pkt.Y();

	d = sqrt (dx*dx + dy*dy);

	if (AP.X() == EP.X() &&	// senkrechte Strecke (28.07.98)
		min (AP.Y(), EP.Y()) <= yl && yl <= max (AP.Y(), EP.Y()))
		return true;

	if (AP.Y() == EP.Y() &&	// waagrechte Strecke
		min (AP.X(), EP.X()) <= xl && xl <= max (AP.X(), EP.X()))
		return true;

	// Normalfall (schräge Strecke)
	if (min (AP.X(), EP.X()) <= xl && xl <= max (AP.X(), EP.X()) &&
		min (AP.Y(), EP.Y()) <= yl && yl <= max (AP.Y(), EP.Y()))
		return true;
	return false;

} // LotStrecke (euklidische Norm)


// --------------------------------------------------------------------------------------------
// (absolute) Länge d des Lots von Punkt DP0 auf die Strecke DP1-DP2 (mit euklidischer Norm);
// Wird true zurückgegeben, dann ist der Abstand zur Strecke bestimmbar, bei false gilt der
// berechnete Abstand nur für die Trägergerade, nicht aber für die Strecke. Ist die Strecke
// entartet (Anfangs- und Endpunkt fallen zusammen), wird ebenfalls false zurückgegeben. d ist
// dabei negativ.
bool _GEOMETR_EXPORT LotStrecke (DoublePair DP0, DoublePair DP1, DoublePair DP2, double& d)
{
	if (IdenticalPoints (DP1.X(), DP1.Y(), DP2.X(), DP2.Y()))	// Strecke entartet
	{
		d = -1.;
		return false;
	}

	// evtl. beim Vergleich der double-Werte "Rauschen" mit dREps berücksichtigen !!!!!!!!!!!!!!!
	if ((DP0.X() == DP1.X() && DP0.Y() == DP1.Y()) ||	// DP0 == DP1
		(DP0.X() == DP2.X() && DP0.Y() == DP2.Y()))		// DP0 == DP2
	{
		d = 0.;
		return true;
	}

double xl, yl;	// Koordinaten des Lotpunktes von DP0 auf die Trägergerade der Strecke DP1-DP2

	if (!GeradenLotPunkt (DP0.X(), DP0.Y(), DP1.X(), DP1.Y(), DP2.X(), DP2.Y(),
								  xl, yl))
	{
		d = -1.;
		return false;
	}

double dx = xl - DP0.X();
double dy = yl - DP0.Y();

	d = sqrt (dx*dx + dy*dy);

//	if (DP1.X() == DP2.X() &&	// senkrechte Strecke
	if (fabs (DP1.X() - DP2.X()) <= dREps &&	// senkrechte Strecke (01.04.99)
		min (DP1.Y(), DP2.Y()) <= yl && yl <= max (DP1.Y(), DP2.Y()))
		return true;

//	if (DP1.Y() == DP2.Y() &&	// waagerechte Strecke
	if (fabs (DP1.Y() - DP2.Y()) <= dREps &&	// waagerechte Strecke (01.04.99)
		min (DP1.X(), DP2.X()) <= xl && xl <= max (DP1.X(), DP2.X()))
		return true;

	// Normalfall (schräge Strecke)
	if (min (DP1.X(), DP2.X()) <= xl && xl <= max (DP1.X(), DP2.X()) &&
		min (DP1.Y(), DP2.Y()) <= yl && yl <= max (DP1.Y(), DP2.Y()))
		return true;
	return false;

} // LotStrecke (euklidischer Norm)


// --------------------------------------------------------------------------------------------
// (absoluter) double-Abstand d des Punktes DP0 von der Strecke DP1-DP2 (mit euklidischer
// Norm); Ist i.a. das Lot auf die Strecke. Läßt sich dies nicht fällen (sondern nur auf die
// Trägergerade), wird der Abstand zum nächstgelegenen Endpunkt der this-Strecke ermittelt
// Ist die this-Strecke entartet (Anfangs- und Endpunkt fallen zusammen), wird false
// zurückgegeben, sonst true.
bool _GEOMETR_EXPORT AbstandPktStrecke (DoublePair DP0, DoublePair DP1, DoublePair DP2,
										double& d)
{
	if (LotStrecke (DP0, DP1, DP2, d))	// gesuchter Abstand = Länge d des Lots
		return true;

	if (d < 0.)	// this-Strecke entartet
		return false;

// von Punkt DP0 konnte nur auf die Trägergerade, nicht auf die Strecke selbst das Lot gefällt
// werden; deshalb Suche des Abstands zum nächstgelegenen Endpunkt der Strecke DP1-DP2
double dx1 = DP1.X() - DP0.X();
double dy1 = DP1.Y() - DP0.Y();
double d1 = sqrt (dx1*dx1 + dy1*dy1);
double dx2 = DP2.X() - DP0.X();
double dy2 = DP2.Y() - DP0.Y();
double d2 = sqrt (dx2*dx2 + dy2*dy2);

	(d1 < d2) ? (d = d1) : (d = d2);
	return true;

} // AbstandPktStrecke (euklidische Norm)
	

// --------------------------------------------------------------------------------------------
// Wert zwischen 0 und 360, der nicht gleich dem Winkel ist, den eine Strecke (x1,y1)-(x2,y2)
// mit der Waagerechten bildet, der jedoch die gleiche Ordnungseigenschaft wie dieser Winkel
// besitzt
double _GEOMETR_EXPORT QuasiWinkel (double x1, double y1, double x2, double y2)
{
	if (x1 == x2 && y1 == y2)
	_ASSERTE (x1 != x2 || y1 != y2);

double dx = x2 - x1;
double ax = fabs (dx);
double dy = y2 - y1;
double ay = fabs (dy);
double t = (ax+ay == 0.) ? 0. : dy/(ax+ay);

	if (dx < 0.)
		t = 2. - t;
	else
		if (dy < 0.)
			t = 4. + t;
	return t * 90.;

} // QuasiWinkel


// --------------------------------------------------------------------------------------------

// !!!!!   eine meiner wichtigsten Routinen, in der jede Menge Kreativität steckt   !!!!!

// nachfolgende Routine wird bei Test auf Überschneidung der Strecken zweier Kanten, NICHT
// beim Test auf Selbstinzidenz (und Konturinzidenz) eingesetzt
// Lage der 2 Strecken AP1-EP1 und AP2-EP2 zueinander
//   KEINE      Strecken schneiden sich nicht
//   ECHT       Strecken schneiden sich
//   RAND       Strecken berühren sich in jeweils genau einem Randpunkt
//   INNEN      Randpunkt der einen Strecke liegt im "Inneren" der anderen Strecke
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander
// die gemeinsamen Punkte werden in GP1 (GP2) zurückgegeben
SchnittErg _GEOMETR_EXPORT GemeinsamePunkte (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2, EPunkt& EP2,
											 DoublePair& GP1, DoublePair& GP2)
{
// durch die Rundung der Stützpunktkoordinaten von double auf KoOrd können bei der von TRiAS
// verwendeten Vektordarstellung folgende Probleme auftreten:
// 1. die Strecken AP1-EP1 bzw. AP2-EP2 können entartet sein
	if (AP1 == EP1 || AP2 == EP2)
		return KEINE;

// 2. ein Stützpunkt, der eigentlich exakt AUF einer Strecke eines anderen Objektes liegen
// müßte, liegt leicht DANEBEN, weil eben an genau dieser Stelle kein Punkt mit GANZZAHLIGEN
// Koordinaten liegen kann;
// deshalb wird bei der Testung, wie 2 Strecken zueinander liegen, nicht das übliche Verfahren
// mit den Kreuzprodukten von Vektordifferenzen verwendet, weil dabei Fehlinterpretationen
// auftreten können, z. B.
//	scheinbar ECHT		tatsächlich INNEN
//	scheinbar KEINE		tatsächlich INNEN bzw. UEBERLAPP
//	scheinbar RAND		tatsächlich UEBERLAPP
// Um diese Dreckeffekte zu umgehen, wird folgendermaßen vorgegangen: Es wird von dem Endpunkt
// der einen Strecke das Lot auf die jeweils andere Strecke gefällt. Ist die Länge des Lots
// unterhalb eines vorgegebenen Epsilons, dann gehe ich davon aus, daß besagter Endpunkt auf
// der anderen Strecke liegen müßte und nur deshalb dort nicht liegt, weil dort kein Punkt mit
// ganzzahligen Koordinaten liegen kann.
double dAbst;	// Abstand für Routine LotStrecke()

// RAND oder UEBERLAPP
	if (AP1 == AP2)
	{
		GP1 = DoublePair (AP1.X(), AP1.Y());

		if (LotStrecke (EP1, AP2, EP2, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (EP1.X(), EP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (EP2, AP1, EP1, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (EP2.X(), EP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

	if (AP1 == EP2)
	{
		GP1 = DoublePair (AP1.X(), AP1.Y());

		if (LotStrecke (EP1, AP2, EP2, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (EP1.X(), EP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (AP2, AP1, EP1, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (AP2.X(), AP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == AP2)
	{
		GP1 = DoublePair (EP1.X(), EP1.Y());

		if (LotStrecke (AP1, AP2, EP2, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (AP1.X(), AP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (EP2, AP1, EP1, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (EP2.X(), EP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == EP2)
	{
		GP1 = DoublePair (EP1.X(), EP1.Y());

		if (LotStrecke (AP1, AP2, EP2, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (AP1.X(), AP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (AP2, AP1, EP1, dAbst) && dAbst < dGlEps)
		{
			GP2 = DoublePair (AP2.X(), AP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}


// UEBERLAPP
int iAnz = 0;		// Anzahl der "Fast-Berührungen"

	if (LotStrecke (AP1, AP2, EP2, dAbst) && dAbst < dGlEps)
	{
		GP1 = DoublePair (AP1.X(), AP1.Y());
		iAnz++;
	}

	if (LotStrecke (EP1, AP2, EP2, dAbst) && dAbst < dGlEps)
	{
		if (0 == iAnz)
			GP1 = DoublePair (EP1.X(), EP1.Y());
		else
			GP2 = DoublePair (EP1.X(), EP1.Y());
		iAnz++;
		if (2 == iAnz) return UEBERLAPP;
	}

	if (LotStrecke (AP2, AP1, EP1, dAbst) && dAbst < dGlEps)
	{
		if (0 == iAnz)
			GP1 = DoublePair (AP2.X(), AP2.Y());
		else
			GP2 = DoublePair (AP2.X(), AP2.Y());
		iAnz++;
		if (2 == iAnz) return UEBERLAPP;
	}

	if (LotStrecke (EP2, AP1, EP1, dAbst) && dAbst < dGlEps)
	{
		if (0 == iAnz)
			GP1 = DoublePair (EP2.X(), EP2.Y());
		else
			GP2 = DoublePair (EP2.X(), EP2.Y());
		iAnz++;
	}

	if (2 == iAnz) return UEBERLAPP;


// ECHT, INNEN/*, RAND*/ oder UEBERLAPP
	if (Intersection (AP1.X(), AP1.Y(), EP1.X(), EP1.Y(), AP2.X(), AP2.Y(), EP2.X(), EP2.Y()))
	{
		if (0 == iAnz)
		{
			GP1 = StreckenSchnittPunkt (AP1, EP1, AP2, EP2);

/*
erst einmal doch nicht (20.10.98)
Text aus GeometrieModule.doc:
Wenn sich 2 Strecken schneiden, muß auch hier mit dem zulässigen "Rauschen" getestet werden, ob der
Schnittpunkt eigentlich doch nur ein inneliegender oder Randpunkt ist. 
			// 07.10.98
			// die nachfolgenden 2 if-Anweisungen wurden als Abwehrstrategie gegen Dreckeffekte
			// eingefügt, die durch Rundung von double auf KoOrd entstehen können;
			// AUCH hier muß noch mit dem Epsilon "dGlEps" getestet werden, ob der Schnittpunkt
			// GP1 eigentlich doch nur ein inneliegender oder Randpunkt ist
			if (AP1.EpsGleich (GP1) || EP1.EpsGleich (GP1))
			{
				if (AP2.EpsGleich (GP1) || EP2.EpsGleich (GP1))
					return RAND;
				return INNEN;
			}

			if (AP2.EpsGleich (GP1) || EP2.EpsGleich (GP1))
			{
				if (AP1.EpsGleich (GP1) || EP1.EpsGleich (GP1))
					return RAND;
				return INNEN;
			}
*/
			return ECHT;
		}

		GP2 = StreckenSchnittPunkt (AP1, EP1, AP2, EP2);

	double dx = GP2.X() - GP1.X();
	double dy = GP2.Y() - GP1.Y();

		if (dx*dx + dy*dy < dGlEps*dGlEps)	// sqrt auf beiden Seiten spare ich mir (07.10.98)
			return INNEN;
		return UEBERLAPP;
	}

	if (1 == iAnz) return INNEN;

// Strecken schneiden sich nicht
	return KEINE;

} // GemeinsamePunkte


// --------------------------------------------------------------------------------------------
// nachfolgende Routine wird bei Test auf Selbstinzidenz (und Konturinzidenz) eingesetzt, NICHT
// beim Test auf Überschneidung der Strecken zweier Kanten
// Lage der 2 Strecken AP1-EP1 und AP2-EP2 zueinander
//   KEINE      Strecken schneiden sich nicht
//   ECHT       Strecken schneiden sich
//   RAND       Strecken berühren sich in jeweils genau einem Randpunkt
//   INNEN      Randpunkt der einen Strecke liegt im "Inneren" der anderen Strecke
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander
// die gemeinsamen Punkte werden in GP1 (GP2) zurückgegeben
SchnittErg GemeinsamePunkte (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2, EPunkt& EP2, EPunkt& GP1,
							 EPunkt& GP2)
{
	if (AP1 == EP1 || AP2 == EP2)
		return KEINE;

// RAND oder UEBERLAPP
	if (AP1 == AP2)
	{
		GP1 = AP1;

		if (Kollinear (EP1, AP2, EP2))
		{
			GP2 = EP1;
			return UEBERLAPP;
		}

		if (Kollinear (EP2, AP1, EP1))
		{
			GP2 = EP2;
			return UEBERLAPP;
		}
		return RAND;
	}

	if (AP1 == EP2)
	{
		GP1 = AP1;

		if (Kollinear (EP1, AP2, EP2))
		{
			GP2 = EP1;
			return UEBERLAPP;
		}

		if (Kollinear (AP2, AP1, EP1))
		{
			GP2 = AP2;
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == AP2)
	{
		GP1 = EP1;

		if (Kollinear (AP1, AP2, EP2))
		{
			GP2 = AP1;
			return UEBERLAPP;
		}

		if (Kollinear (EP2, AP1, EP1))
		{
			GP2 = EP2;
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == EP2)
	{
		GP1 = EP1;

		if (Kollinear (AP1, AP2, EP2))
		{
			GP2 = AP1;
			return UEBERLAPP;
		}

		if (Kollinear (AP2, AP1, EP1))
		{
			GP2 = AP2;
			return UEBERLAPP;
		}
		return RAND;
	}


// INNEN oder UEBERLAPP
int iAnz = 0;		// Anzahl der Kollinearitäten

	if (Kollinear (AP1, AP2, EP2))
	{
		GP1 = AP1;
		iAnz++;
	}

	if (Kollinear (EP1, AP2, EP2))
	{
		if (0 == iAnz)
			GP1 = EP1;
		else
			GP2 = EP1;
		iAnz++;
		if (2 == iAnz) return UEBERLAPP;
	}

	if (Kollinear (AP2, AP1, EP1))
	{
		if (0 == iAnz)
			GP1 = AP2;
		else
			GP2 = AP2;
		iAnz++;
		if (2 == iAnz) return UEBERLAPP;
	}

	if (Kollinear (EP2, AP1, EP1))
	{
		if (0 == iAnz)
			GP1 = EP2;
		else
			GP2 = EP2;
		iAnz++;
	}

	if (2 == iAnz) return UEBERLAPP;
	if (1 == iAnz) return INNEN;


// ECHT oder KEINE
	if (Intersection (AP1.X(), AP1.Y(), EP1.X(), EP1.Y(), AP2.X(), AP2.Y(), EP2.X(), EP2.Y()))
	{
	DoublePair GP = StreckenSchnittPunkt (AP1, EP1, AP2, EP2);

		GP1.X() = DtoL (GP.X()); 
		GP1.Y() = DtoL (GP.Y()); 
		return ECHT;
	}

	return KEINE;

} // GemeinsamePunkte


// --------------------------------------------------------------------------------------------
// Berechnung des Schnitt- oder Berührungspunktes der 2 Strecken AP1-EP1 und AP2-EP2;
// hierbei wird vorausgesetzt, daß beide Strecken genau einen Punkt gemeinsam haben
DoublePair _GEOMETR_EXPORT StreckenSchnittPunkt (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2,
												 EPunkt& EP2)
{
	if (AP1 == AP2 || AP1 == EP2)
		return DoublePair (AP1.X(), AP1.Y());

	if (EP1 == AP2 || EP1 == EP2)
		return DoublePair (EP1.X(), EP1.Y());

double xs, ys;	// Koordinaten des Schnittpunktes der Trägergeraden der beiden Strecken AP1-EP1
				// und AP2-EP2

	if (GeradenSchnittPunkt (AP1.X(), AP1.Y(), EP1.X(), EP1.Y(), AP2.X(), AP2.Y(), EP2.X(),
							 EP2.Y(), xs, ys))
	{
	// entscheidende Erweiterung:
	// es wird getestet, ob der double-Schnittpunkt (xs, ys) nach Rundung auf KoOrd mit einem
	// Streckenendpunkt zusammenfällt; ist dies der Fall, wird dieser Endpunkt zurückgegeben
	EPunkt GP (DtoL(xs), DtoL(ys));

		if (GP == AP1 || GP == EP1 || GP == AP2 || GP == EP2)
			return DoublePair (GP.X(), GP.Y());
		return DoublePair (xs, ys);
	}

	// hierhin dürfte das Programm gar nicht mehr kommen !!!!
	_ASSERTE (false);
	return DoublePair (-1, -1);

} // StreckenSchnittPunkt


// --------------------------------------------------------------------------------------------
// Berechnung des Schnittpunktes (xs,ys) zweier Geraden, die jeweils durch 2 Punkte (x11,y11)
// und (x21,y21) bzw. (x12,y12) und (x22,y22) gegeben sind; wird false zurückgegeben, ist der
// Schnittpunkt nicht ermittelbar, xs und ys sind dann unbestimmt
bool _GEOMETR_EXPORT GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
						double x12, double y12, double x22, double y22, double& xs, double& ys)
{
double a1 = y21 - y11;
double b1 = x11 - x21;
double a2 = y22 - y12;
double b2 = x12 - x22;
double dNenner = a1*b2 - a2*b1;

	// wenn beide Geraden identisch oder parallel sind bzw. wenn ein (oder beide) Punktepaare
	// zu einem Punkt zusammenfallen, ist der Schnittpunkt nicht ermittelbar
	if (0. == dNenner) return false;

double c1 = -y11*b1 - x11*a1;
double c2 = -y12*b2 - x12*a2;

	xs = (c2*b1 - c1*b2) / dNenner;
	ys = (c1*a2 - c2*a1) / dNenner;

	return true;

} // GeradenSchnittPunkt


// --------------------------------------------------------------------------------------------
// Berechnung des Schnittpunktes (xs,ys) zweier Geraden, die durch 2 Punkte (x11,y11) und
// (x21,y21) bzw. einen Punkt (x2,y2) und den Anstieg dAnst gegeben sind; wird false
// zurückgegeben, ist der Schnittpunkt nicht ermittelbar; xs und ys sind dann unbestimmt
bool _GEOMETR_EXPORT GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
									double x2, double y2, double dAnst, double& xs, double& ys)
{
double a1 = y21 - y11;
double b1 = x11 - x21;
double a2, b2;

	if (dAnst < DBL_MAX)	// 2. Gearde nicht senkrecht
	{		
		a2 = dAnst;	//double a2 = y22 - y2;		
		b2 = -1;	//double b2 = x2 - x22;
	}
	else					// 2. Gerade senkrecht
	{
		a2 = 1.;	// Wert beliebig, da er herausgekürzt wird
		b2 = 0.;
	}

double dNenner = a1*b2 - a2*b1;

	// wenn beide Geraden identisch oder parallel sind bzw. wenn das Punktepaare zu einem Punkt
	// zusammenfällt, ist der Schnittpunkt nicht ermittelbar
	if (0. == dNenner) return false;

double c1 = -y11*b1 - x11*a1;
double c2 = -y2*b2 - x2*a2;

	xs = (c2*b1 - c1*b2) / dNenner;
	ys = (c1*a2 - c2*a1) / dNenner;

	return true;

} // GeradenSchnittPunkt


// --------------------------------------------------------------------------------------------
// Berechnung des Lotpunktes (xl,yl) vom Punkt (xp,yp) auf eine Gerade g1, die durch die 2
// Punkte (x1,y1) und (x2,y2) gegeben ist; wird false zurückgegeben, ist der Lotpunkt nicht
// ermittelbar, xl und yl sind dann unbestimmt
bool _GEOMETR_EXPORT GeradenLotPunkt (double xp, double yp, double x1, double y1, double x2,
									  double y2, double& xl, double& yl)
{
double a1 = y1 - y2;	// Parameter für allgemeine Gleichung a1*x+b1*y+c1=0 der Geraden g1	
double b1 = x2 - x1;	// (werden aus Zwei-Punkte-Gleichung ermittelt)

	if (0. == a1 && 0. == b1)	// Gerade g1 ist zu einem Punkt entartet, damit kein Lotpunkt
		return false;			// ermittelbar

	if (a1 != 0)	// g1 nicht waagerecht
	{
	double c1 = -x1*a1 - y1*b1;
	double a2, b2, c2;	// Parameter für allgemeine Gleichung a2*x+b2*y+c2=0 der Geraden g2,
						// die senkrecht auf g1 steht und durch Punkt (xp,yp) geht (werden aus
						// Punkt- Richtungs-Gleichung ermittelt)

		a2 = b1 / a1;
		b2 = -1;
		c2 = yp - a2*xp;

	// Hilfsgröße (wird genau dann Null, wenn beide Geraden parallel sind); dies dürfte hier
	// aber nicht zutreffen, da g2 so konstruiert wurde, daß g2 auf g1 senkrecht steht
	double dNenner = a1*b2 - a2*b1;
				
		if (0. == dNenner)
		{
			_ASSERTE (dNenner != 0.);
			return false;
		}

		xl = (b1*c2 - b2*c1) / dNenner;	// x-Koordinate bzw.
		yl = (a2*c1 - a1*c2) / dNenner;	// y-Koordinate des Schnittpunktes von g1 und g2
	}

	else		// g1 waagerecht, damit g2 senkrecht
	{
		xl = xp;
		yl = y1;
	}

	return true;

} // GeradenLotPunkt


// --------------------------------------------------------------------------------------------
// Berechnung des POSITIVEN Winkels im Bogenmaß (d.h. zwischen 0 ... 2*Pi), den die 3 Punkte
// P0(x0,y0), P1(x1,y1) und P2(x2,y2) bilden; es wird der Winkel berechnet, der dadurch
// entsteht, daß die Strecke P1-P2 im mathematisch positiven Sinn solange um P1 gedreht wird,
// bis sie auf der Strecke P0-P1 liegt; ist mindestens eine der beiden Strecken zu einem Punkt
// entartet, wird false zurückgegeben; dWinkel ist in diesem Fall unbestimmt
bool _GEOMETR_EXPORT Winkel (KoOrd x0, KoOrd y0, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
							 double& dWinkel)
{
	// es muß gelten P0 != P1 und P1 != P2
	if ((x0 == x1 && y0 == y1) || (x1 == x2 && y1 == y2))
		return false;	// mindestens eine der beiden Strecken ist zu einem Punkt entartet

double dx1 = x1 - x0;	// "double", weil atan() ein double-Argument verlangt und
double dy1 = y1 - y0;	// damit die nachfolgenden Divisionen double-Ergebnisse liefern
double dx2 = x2 - x1;
double dy2 = y2 - y1;

	if (0. == dx1)	// Strecke P0-P1 steht senkrecht
	{
		if (dx2 != 0.)	// Strecke P1-P2 steht NICHT senkrecht
		{
			dWinkel = atan (dy2/dx2);
			// Ergebnis von atan() liegt im Bereich von -Pi/2 bis Pi/2, deshalb kann in ALLEN
			// Fällen bei der nachfolgenden Winkelberechnung SUBTRAHIERT werden
			if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
				dWinkel = 0.5*Pi - dWinkel;	// konvexe Ecke 
			else
				dWinkel = 1.5*Pi - dWinkel;	// konkave Ecke 
		}
		else	// BEIDE Strecken stehen senkrecht
		{
			if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
				dWinkel = Pi;	// die Strecken liegen hintereinander, aber exakt auf einer
								// Geraden
			else
				dWinkel = 0.;	// eine Strecke liegt exakt auf bzw. in der anderen
		}
		return true;
	}

	if (0. == dx2)	// Strecke P1-P2 steht senkrecht
	{
		dWinkel = atan (dy1/dx1);
		if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
			dWinkel += 0.5*Pi;	// konvexe Ecke
		else
			dWinkel += 1.5*Pi;	// konkave Ecke
		return true;
	}

	// die Strecken stehen senkrecht aufeinander
	// (an dieser Stelle wird der Genauigkeit wegen bewußt nicht mit den durch Division
	// ermittelten Werte m1 und m2 getestet)
	if (dy1*dy2 == -dx1*dx2)
	{
		if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
			dWinkel = 0.5*Pi;	// konvexe Ecke
		else
			dWinkel = 1.5*Pi;	// konkave Ecke 
		return true;
	}

double m1 = dy1 / dx1;	// die Anstieg der Strecke P0-P1	
double m2 = dy2 / dx2;	// die Anstieg der Strecke P1-P2

	dWinkel = atan ((m1 - m2) / (1. + m1*m2));

	if (0. == dWinkel)		// die Strecken haben den gleichen Anstieg
	{
		if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
			dWinkel = Pi;	// die Strecken liegen hintereinander, aber exakt auf einer Geraden
		return true;
	}

	if (dWinkel < 0.) dWinkel += Pi;	// Winkel soll IMMER positiv sein
	if (-1 == TurnDirection (x0, y0, x1, y1, x2, y2))
		dWinkel += Pi;	// konkave Ecke 
	return true;

} // Winkel


// --------------------------------------------------------------------------------------------
// Test, ob die beiden Punkte (x0,y0) und (y0,y1) identisch sind; wenn ja, dann Fehlermeldung
// und return-Wert "true"
bool IdenticalPoints (double x0, double y0, double x1, double y1)
{
	if (x0 == x1 && y0 == y1)
	{
#ifdef _DEBUG
	string sBuffer;

		Format (sBuffer, "Objekt mit doppelten Stützpunkten gefunden!\n (%ld,%ld)\r\n",
				DtoL (x0), DtoL (y0));

		MessageBox (__hWndM, sBuffer.c_str(), "Achtung:", MB_ICONERROR | MB_OK);// MB_ICONWARNING,MB_ICONASTERISK
#endif
		return true;
	}
	return false;

} // IdenticalPoints
