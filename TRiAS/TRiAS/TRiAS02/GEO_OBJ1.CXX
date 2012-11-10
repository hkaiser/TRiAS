/*

 File: GEO_OBJ1.CXX

 Geometrieobjekte (Kreis, Ellipse)

 erstellt: J. Benkenstein		am: 20.11.91

*/
#include "trias02p.hxx"

#if defined(_FORCE_LEGACY_CODE)

#include <limits.h>	 // für LONG_MAX
#include <math.h>	 // für "sqrt()"

#include <gerade.hxx>	 // Geraden-Klasse

// Konstantendefinitionen -----------------------------------------------------
const long ID_BUFFEROFFSET = 1000000000L;	// Neuer Ident bei Pufferung
const long ON_BUFFEROFFSET = 1000000L;		// Neue Objektnummer bei Pufferung

// Konstruktoren für Ellipsen -------------------------------------------------
Ellipsen :: Ellipsen (Punkt &Pkt, long a, long b) 
{
    _MP = Pkt;		       // Mittelpunkt
    _Xa = a;		       // Halbachsenabschnitte
    if (b == 0) _Yb = a;       // beim Kreis
    else	_Yb = b;
}

Ellipsen :: Ellipsen (KoOrd x, KoOrd y, long a, long b) 
{
    _MP.X() = x; _MP.Y() = y;  // Mittelpunkt
    _Xa = a;		       // Halbachsenabschnitte
    if (b == 0) _Yb = a;	       // beim Kreis
    else        _Yb = b;
}

// Buffering eines Punktes ----------------------------------------------------
GeoObjekt* GeoPunkt :: operator+ (long Dehnung) 
{
    if (Dehnung <= 0) return this;

GeoObjekt* pGO = new GeoKreis (DB(), ObjNr() + ON_BUFFEROFFSET, 
			       Id() + ID_BUFFEROFFSET, 
			       *this, Dehnung);

        if (pGO == NULL) {
        	db_error (EC_NOMEMORY, RC_opplGeoPkt);
		return this;
        } 

return pGO;
}

// Buffering eines Kreises ----------------------------------------------------
GeoObjekt* GeoKreis :: operator+ (long Dehnung) 
{
	if (Dehnung <= 0) return this;

GeoObjekt* pGO = new GeoKreis (DB(), ObjNr() + ON_BUFFEROFFSET, 
			       Id() + ID_BUFFEROFFSET, 
			       MP(), Radius() + Dehnung);

        if (pGO == NULL) {
            	db_error (EC_NOMEMORY, RC_opplGeoKrs);
	    	return this;
        }

return pGO;
}

ObjContainer Ellipsen :: GetCont (void)
{
	return ObjContainer (_MP.X() - _Xa, _MP.X() + _Xa, _MP.Y() - _Yb, _MP.Y() + _Yb);
}

// true, wenn alle Zwischenpunkte für Buffering-Operator OK, sonst false
#pragma warning (disable:4270)

bool GeoKante :: _ZwischenPunkte (Punkt* PV, long Dehnung, long lMI) 
{
Gerade G1, G2;		// Zwei Geraden erzeugen
long HI;  	    	// Hilfindex;

    for (long i = 1; i < (_Size - 1); i++) {	// bis zum vorletzten Punkt
    // i-te Schnittpunkt = Schnittpunkt aus pos. Parallelen
	HI = labs (lMI -i);	   // Hilfsindex für Zugriff auf Punkt-Vektor
	G1 = Gerade (_SPF [i-1], _SPF [i]); // Geraden neu init.
	G2 = Gerade (_SPF [i], _SPF [i+1]);	   // Schnittpunkt der
	PV [HI] = (G1 + Dehnung) ^ (G2 + Dehnung); // der Geraden G1 und G2

    // Schnittpunkt OK ?
	if (!PV [HI]) {		// wenn Punkt ungültig und
	    if (G1 == G2) {	// Geraden aufeinander liegen
                G1 = G1 + Dehnung;  // Parallelen berechnen
                G2 = G2 + Dehnung;
		PV [HI] = G1.MittelPunkt (G1.EP(), G2.AP());// Punkt speichern
	    } else 
	        return false;   // Berechnung abbrechen
        }
    }
    return true;                // Berechnung aller Punkte OK	
}
 
// Buffering einer GeoKante, das eine GeoFlaeche erzeugt
GeoObjekt* GeoKante :: operator + (long Dehnung)
{
    if ((_Size == 1) ||     // wenn Folge nur aus einem Punkt besteht oder
        (Dehnung <= 0))     // Dehnung ungültig ist
	return this;        // mit akt. Objekt zurück

long lMI = 2 * _Size;   // größter Index
Punkt* PV = new Punkt [lMI + 1]; // Speicher f. Punkt-Vektor anfordern

    if (PV == NULL)	// wenn keiner mehr vorhanden
    {
	db_error (EC_NOMEMORY, RC_opplGeoKante);  // Fehlermeldung ausgeben
	return this;
    }

// berechne Anfangs- und Endpunkte
Gerade G1 (_SPF [0], _SPF [1]);   // Gerade G1 init.
Gerade G2 = G1 + Dehnung;         // Parallele im pos. Abstand

    PV [0] = G2.AP();		      // AnfPunkt der entsteh. Fläche
    PV [lMI--] = PV [0]; 	      // gleich dem EndPunkt

    G2 = G1 - Dehnung;                // neg. Parallele
    PV [lMI] = G2.AP();		      // vorletzter Punkt der Fläche

// alle weiteren Zwischenpunkte berechnen
    if (_Size > 2)		    // wenn mehr als 2 Punkte in der Folge
    {
	if (_ZwischenPunkte (PV, Dehnung, 0) && // Schnittpkte. d. pos. u.
	    _ZwischenPunkte (PV, -Dehnung, lMI)) // neg. Parallelen OK
	// mittlere Punkte berechnen
        {
           G1 = Gerade (_SPF [_Size-2], _SPF [_Size-1]);
           G2 = G1 + Dehnung;         // positive Parallele
           PV [_Size-1] = G2.EP();    // 1. mittlerer Punkt
           G2 = G1 - Dehnung;         // negative Parallele
	   PV [_Size] = G2.EP();      // 2. mittlerer Punkt
        }
	else
	{
	    db_error(EC_NOSCHNITTPUNKT, RC_opplGeoKante); // Fehlerm. ausgeben
	    return this;
	}
    }
    else
    {		// berechne fehlenden 2 Punkte
        PV [--lMI] = G2.EP();
        G2 = G1 + Dehnung;
        PV [--lMI] = G2.EP();
    }

// neue GeoFlaeche erzeugen
GeoObjekt* pGO = new GeoFlaeche (DB(), ObjNr() + ON_BUFFEROFFSET, 
				 Id() + ID_BUFFEROFFSET, 
				 PV, (2*_Size) + 1);

    if (pGO == NULL) {          // wenn kein Speicherplatz mehr vorhanden
	db_error (EC_NOMEMORY, RC_opplGeoKante); // Fehlermeldung ausgeben	
        return this;
    }
    else
        return pGO;	// mit GeoObjekt-Zeiger zurück
}
				
/*
Berechnet den vorzeichenbehafteten Inhalt einer geschlossenen Kante (Fläche),
der bei einem Fehler gleich 0 ist.

Inhalt > 0 --> Verlauf der Fläche im math. positiven Drehsinn
Inhalt < 0 --> negativer Drehsinn
Formel: Anfangswert + Summe über alle x(n) * (y(n+1) - y(n-1)) von n = 1
	bis Anzahl Punkte (AP) - 2, mit den Punkten P0, P1, ... P(AP-1) und
	dem Anfangswert = x(AP-1) * (y1 - y(AP-2))
*/
double Masche :: FlInhalt (Kante& K, CoordTrans *pCTF) 
{
// teste Parameter der Fläche
short Size = short (K.ASP());    // Anzahl Punkte

    if ((!(K.SP (0) == K.SP (Size-1))) ||   // wenn AnfPkt verschieden EndPkt
	(Size <= 3))			    // oder zuwenig Punkte
    {	     
	     return 0;	// mit ungültigem Wert zurück
    }

	if (!pCTF/* || pCTF -> isMetric()*/) {
	double Fl = (double)K.SP(Size-1).X() * (double)(K.SP(1).Y() - K.SP(Size - 2).Y());

	// berechne Summe
		for (short i = 1; i < Size - 1; i++) {
			Fl += (double)K.SP(i).X() * 
				  (double)(K.SP(i + 1).Y() -K.SP(i - 1).Y());
		}
		return (Fl / 2);	// Inhalt halbieren und zurück
	}

// berechne Anfangswert der Fläche
DoublePair DP1;
DoublePair DP2;
DoublePair DP3;

#if defined(WIN32)
LPVOID pCTFData = NULL;
double Fl = 0.0;

	if (pCTF -> GetMetricParam (K.SP(1), &pCTFData)) {
	// Koordinatentransformation an erstem Punkt orientieren
		pCTF -> MetricEx (K.SP(Size-1), &DP1.X(), &DP1.Y(), pCTFData);
		pCTF -> MetricEx (K.SP(1), &DP2.X(), &DP2.Y(), pCTFData);
		pCTF -> MetricEx (K.SP(Size - 2), &DP3.X(), &DP3.Y(), pCTFData);
	
	//double Fl = (double)K.SP(Size-1).X() * (double)(K.SP(1).Y() - K.SP(Size - 2).Y());
		Fl = DP1.X() * (DP2.Y() - DP3.Y());

	// berechne Summe
		for (short i = 1; i < Size - 1; i++) {
			pCTF -> MetricEx (K.SP(i), &DP1.X(), &DP1.Y(), pCTFData);
			pCTF -> MetricEx (K.SP(i + 1), &DP2.X(), &DP2.Y(), pCTFData);
			pCTF -> MetricEx (K.SP(i - 1), &DP3.X(), &DP3.Y(), pCTFData);
		
	//		Fl += (double)K.SP(i).X() * (double)(K.SP(i + 1).Y() - K.SP(i - 1).Y());
			Fl += DP1.X() * (DP2.Y() - DP3.Y());
		}

//		if (pCTFData) CoTaskMemFree (pCTFData);
		pCTF -> FreeMetricParam (pCTFData);
	} else
#endif // WIN32
	{
		pCTF -> Metric (K.SP(Size-1), &DP1.X(), &DP1.Y());
		pCTF -> Metric (K.SP(1), &DP2.X(), &DP2.Y());
		pCTF -> Metric (K.SP(Size - 2), &DP3.X(), &DP3.Y());
		
	//double Fl = (double)K.SP(Size-1).X() * (double)(K.SP(1).Y() - K.SP(Size - 2).Y());
		Fl = DP1.X() * (DP2.Y() - DP3.Y());

	// berechne Summe
		for (short i = 1; i < Size - 1; i++) {
			pCTF -> Metric (K.SP(i), &DP1.X(), &DP1.Y());
			pCTF -> Metric (K.SP(i + 1), &DP2.X(), &DP2.Y());
			pCTF -> Metric (K.SP(i - 1), &DP3.X(), &DP3.Y());
			
	//		Fl += (double)K.SP(i).X() * (double)(K.SP(i + 1).Y() - K.SP(i - 1).Y());
			Fl += DP1.X() * (DP2.Y() - DP3.Y());
		}
	}

return (Fl / 2);	// Inhalt halbieren und zurück
}

// berechnet den Flächeninhalt aller in einer Masche enthaltenen Flächen, der
// bei einem Fehler gleich 0 ist
double Masche :: Inhalt (CoordTrans *pCTF) 
{
// berechne Inhalt der äuáeren Fläche
double Inhalt = fabs (FlInhalt (_KAF [0], pCTF));

    if (Inhalt == 0)	     // wenn Inhalt nicht berechnet werden konnte
	return 0;	     // mit 0 zurück
    else
	for (int i = 1; i < _Size; i++) 	      // subtrahiere den In-
	    Inhalt -= fabs (FlInhalt (_KAF [i], pCTF));     // halt aller"L”cher,

return Inhalt;					      // mit Differenz zurück
}

// Buffering-Operator erzeugt einen Zeiger auf eine neue GeoFlaeche
GeoObjekt* GeoFlaeche :: operator + (long Dehnung) 
{	// aüßere Masche
// teste Anfangswerte
Kante &Ka = _KAF [0];	       // Referenz auf äußere Masche
double FlI = FlInhalt (Ka, NULL);	// Flächeninhalt der aüáeren Masche

    if ((Dehnung <= 0) ||	       // wenn Dehnung oder
	(FlI == 0))		       // Flächeninhalt ungültig
	  return this;		       // mit akt. Objekt zurück

// teste Drehsinn der Fläche
    if (FlI > 0)            // entgegen Uhrzeigerrichtung
	Dehnung = -Dehnung; // Vorzeichenumkehr
   	
// Speicher anfordern
short Size = short(Ka.ASP());    // Anzahl Stützpunkte
Punkt* PV = new Punkt [Size];    // Speicher f. Punkt-Vektor anfordern

    if (PV == NULL)	// wenn keiner mehr vorhanden
    {
	db_error (EC_NOMEMORY, RC_opplGeoFlaeche); // Fehlermeldung ausgeben
	return this;
    }

// berechne alle Schnittpunkte der positiven Parallelen
Gerade G1 (Ka.SP(0), Ka.SP(1));	      		// Geraden G1 und
Gerade G2 (Ka.SP(Size-2), Ka.SP(Size-1)); 	// G2 init.
short i = 0; 			              	// PV-Index
    do {
	PV [i] = (G1 + Dehnung) ^ (G2 + Dehnung); // Schnittpkt. ber.
    // Schnittpunkt-Test
	if (!PV [i])		// wenn Punkt ungültig
        {                       // und
	    if (G1 == G2)       // Geraden aufeinander liegen
            {
                G1 = G1 + Dehnung;  // Parallelen berechnen
                G2 = G2 + Dehnung;
		PV [i] = G1.MittelPunkt (G1.EP(), G2.AP()); // Punkt speichern
            }
	    else 
	    {						       // Fehlermeldg.
		db_error(EC_NOSCHNITTPUNKT, RC_opplGeoFlaeche); // ausgeben
		return this;
	    }
	}
	if (++i < (Size - 1))			  // Zugriffsschutz testen
	{
	    G1 = Gerade (Ka.SP(i-1), Ka.SP(i)); // Geraden G1 und
	    G2 = Gerade (Ka.SP(i), Ka.SP(i+1));	  // G2 neu init.
            continue;
	}
	else
	    break;				  // alle Punkte ok
    } while (i);	                // bis auf letzten Punkt alle behandeln

    PV [Size-1] = PV [0];	// EndPkt = AnfPkt

// neue GeoFlaeche erzeugen
GeoObjekt* pGO = new GeoFlaeche (DB(), ObjNr() + ON_BUFFEROFFSET, 
				 Id() + ID_BUFFEROFFSET, 
				 PV, Size);

    if (pGO == NULL)            // wenn kein Speicherplatz mehr vorhanden
    {
	db_error (EC_NOMEMORY, RC_opplGeoFlaeche); // Fehlermeldung ausgeben
        return this;
    }

return pGO;	// mit GeoObjekt-Zeiger zurück
}

// berechnet den vorzeichenbehafteten Flächeninhalt und Schwerpunkt der äuáeren
// Masche (ohne Löcher) einer Fläche. Fehler wenn Flächeninhalt == 0.0.
double Masche :: SchwerPunkt (Punkt &Pt) 
{
// teste Parameter der Fläche
Kante& Ka = _KAF [0];		// Referenz auf äuáere Kante
long Size = Ka.ASP();		// Anzahl Stützpunkte

	if ((Ka.SP(0) != Ka.SP(Size - 1)) ||    // wenn AnfPkt versch. EnPkt
			(Size <= 3))		// oder zuwenig Punkte
		return 0.0; 			// mit ungültigem Wert zurück

// kleinste X/Y-Koordinate bestimmen
ObjContainer OC = Ka.GetCont();	// Koordinaten bestimmen und
KoOrd Xmin = OC.XMin();		// lesen
KoOrd Ymin = OC.YMin();

// Schwerpunkt u. Flächeninhalt berechnen
double Xs, Ys, Xsi, Ysi, Inh;	// Schwerpunkt-Koordinaten, Flä.-Inhalt
double FlI;			// Flächeninhalt

	Xs = Ys = FlI = 0.0;		// Werte definiert initialisieren
	for (long i = 0; i < (Size - 1); i++) {	// für alle Punkte der Folge
	// akt. Koordinaten lesen
	double X1 = double (Ka.SP(i).X()   - Xmin),
	       Y1 = double (Ka.SP(i).Y()   - Ymin),
	       X2 = double (Ka.SP(i+1).X() - Xmin),
	       Y2 = double (Ka.SP(i+1).Y() - Ymin);

	// Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {	   // wenn Berechnung m”glich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) /
				(3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 *Y2)) /
				(3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;

		} else 
			Xsi = Ysi = Inh = 0.0;      // alle Werte 0 setzen

	// Zwischenwerte aktualisieren
		Xs += Xsi * Inh;	      // Schwerpunkt
		Ys += Ysi * Inh;
		FlI += Inh;		      // Inhalt der Fläche
	}

// Endkoordinaten berechnen
	if (FlI == 0.0) {	      // wenn Fl.-Inhalt ungültig
		db_error (EC_NOSCHWERPUNKT, RC_SchwPktMasche); // Fehlermeldung ausg.
		return 0.0;
	} else {
		Pt = Punkt (KoOrd ((Xs / FlI) + Xmin + 0.5),   // Koordinaten
			    KoOrd ((Ys / FlI) + Ymin + 0.5)); // runden u. zurück
		return FlI;
	}
}

#endif // defined(_FORCE_LEGACY_CODE)
