// Geometrieobjekte (Kreis, Ellipse)
// File: GEO_OBJ1.CXX

// erstellt:    J. Benkenstein	  am: 20.11.91
// modifiziert: W. Mörtl


#include "GeometrP.hxx"



// ============================================================================================
// Methoden für EFLAECHE
// Berechnung des Flächeninhalt einer Flächen unter Berücksichtigung von Innenkonturen, der bei
// einem Fehler gleich 0 ist
double _GEOMETR_EXPORT EFlaeche :: AreaSize (CoordTransX* pCT)
{
// berechne Inhalt der äußeren Fläche
double dInhalt = fabs (_KAF[0].PolygonArea (pCT));

    if (0 == dInhalt)	// wenn Inhalt nicht berechnet werden konnte,
		return 0;		// mit 0 zurück

	if (_Size > 1)	// Fläche hat Inseln
		for (int i = 1; i < _Size; i++)					// subtrahiere den Inhalt
			dInhalt -= fabs (_KAF[i].PolygonArea (pCT));	// aller Inseln

	return dInhalt;		// mit Differenz zurück
}



// berechnet den vorzeichenbehafteten Flächeninhalt und Schwerpunkt der äußeren
// Kontur (ohne Löcher) einer Fläche. Fehler wenn Flächeninhalt == 0.0.
double _GEOMETR_EXPORT EFlaeche :: SchwerPunkt (EPunkt &Pt) {
// teste Parameter der Fläche
EKante& Ka = _KAF [0];	   // Referenz auf äußere Kante
long Size = Ka.ASP();	   // Anzahl Stützpunkte

	if ((Ka.SP(0) != Ka.SP(Size - 1)) ||    // wenn AnfPkt versch. EnPkt
			(Size <= 3))	// oder zuwenig Punkte
		return 0.0;			// mit ungültigem Wert zurück

// kleinste X/Y-Koordinate bestimmen
ObjRechteck OC = Ka.GetCont(); // Koordinaten bestimmen und
KoOrd Xmin = OC.XMin();	 // lesen
KoOrd Ymin = OC.YMin();

// Schwerpunkt u. Flächeninhalt berechnen
double Xs, Ys, Xsi, Ysi, Inh;   // Schwerpunkt-Koordinaten, Flächeninhalt
double FlI;						// Flächeninhalt

	Xs = Ys = FlI = 0.0;	    // Werte definiert initialisieren
	for (long i = 0; i < (Size - 1); i++) { // für alle Punkte der Folge
	// akt. Koordinaten lesen
	double X1 = double (Ka.SP(i).X()   - Xmin),
	       Y1 = double (Ka.SP(i).Y()   - Ymin),
	       X2 = double (Ka.SP(i+1).X() - Xmin),
	       Y2 = double (Ka.SP(i+1).Y() - Ymin);

	// Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {      // wenn Berechnung möglich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) / (3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 * Y2)) / (3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;

		} else 
			Xsi = Ysi = Inh = 0.0;      // alle Werte 0 setzen

	// Zwischenwerte aktualisieren
		Xs += Xsi * Inh;	// Schwerpunkt
		Ys += Ysi * Inh;
		FlI += Inh;			// Inhalt der Fläche
	}

// Endkoordinaten berechnen
	if (FlI == 0.0) {	     // wenn Fl.-Inhalt ungültig
		DEX_Error (RC_SchwPktMasche, EC_NOSCHWERPUNKT);	// Fehlermeldung ausg.
		return 0.0;
	} else {
		Pt = EPunkt (KoOrd ((Xs / FlI) + Xmin + 0.5),	// Koordinaten
					 KoOrd ((Ys / FlI) + Ymin + 0.5));	// runden u. zurück
		return FlI;
	}
}

                
                
                
// Methoden für ELLIPSEN --------------------------------------------------------------------------------------
// Konstruktoren
_GEOMETR_EXPORT Ellipsen :: Ellipsen (EPunkt &Pkt, long a, long b) {

    _MP = Pkt;	// Mittelpunkt
    _Xa = a;	// Halbachsenabschnitte
    if (b == 0)
		_Yb = a;	// beim Kreis
    else
		_Yb = b;
}
         
         
_GEOMETR_EXPORT Ellipsen :: Ellipsen (KoOrd x, KoOrd y, long a, long b) {

    _MP.X() = x; _MP.Y() = y;  // Mittelpunkt
    _Xa = a;		// Halbachsenabschnitte
    if (b == 0)
		_Yb = a;	// beim Kreis
    else
		_Yb = b;
}





// Methoden für GEOKREIS --------------------------------------------------------------------------------------
// Konstruktoren

_GEOMETR_EXPORT GeoKreis :: GeoKreis (long ObjNr, ulong Id)
						  : GeoObjekt (ObjNr, Id)
{
// keine weiteren Aktivitäten
}

_GEOMETR_EXPORT GeoKreis :: GeoKreis (long ObjNr, ulong Id,  EPunkt &Pkt, long Radius)
						  : GeoObjekt (ObjNr, Id), Kreis(Pkt, Radius)
{
// keine weiteren Aktivitäten
}    

                                                                               
                                                                               
                                                                               
//  ---------------------------------------------------------------------------
// Virtuelle Funktionen
ObjTyp _GEOMETR_EXPORT Kreis :: isA (void) { return OT_KREIS; }
ObjTyp _GEOMETR_EXPORT GeoKreis :: isA (void) { return OT_KREIS; }
