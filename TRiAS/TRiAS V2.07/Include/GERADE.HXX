// Geometrieobjekt (Gerade)
// File: GERADE.HXX
// erstellt: J. Benkenstein                             begonnen am: 27.11.91

#ifndef _GERADE_HXX
#define _GERADE_HXX

#if !defined(NOGERADE)
/* Gerade -------------------------------------------------------------------
   Eine Gerade wird durch 2 Punkte beschrieben, wobei ihre Richtung durch den
   Verlauf von einem Anfangs- zu einem Endpunkt bestimmt ist. */
class Gerade {
private:
// Attribute
    Punkt _AP;	    // Anfangspunkt
    Punkt _EP;	    // Endpunkt

public:
// Konstruktoren
    Gerade () : _AP (0,0), _EP (0,0) {}	            // Null-Initialisierung
    Gerade (KoOrd Xa, KoOrd Ya, KoOrd Xe, KoOrd Ye) // Koordinaten übergeben	   
	      : _AP (Xa, Ya), _EP (Xe, Ye) {}		
    Gerade (const Punkt& AP, const Punkt& EP) 	    // Punkte direkt übergeben
	      : _AP (AP), _EP (EP) {}	

// Member-Funktionen
    Punkt& AP() { return _AP; }	 // lesen Anfangs- und
    Punkt& EP() { return _EP; }	 //	 Endpunkt der Geraden
    double Betrag ();		// Betrag der Geraden zw. _AP u. _EP
    Punkt MittelPunkt (Punkt& AP, Punkt& EP); // berechnet den Mittelpunkt der
			// durch AnfPkt und EndPkt gegeben Geraden (Strecke)
    Bool Y (const double& x, double& y); // berechnet die y-Koordinate eines 
	   // Punktes auf der Geraden bei gegebenem x-Wert,
	   // TRUE, wenn Koordinate durch y = mx + n berechenbar, sonst FALSE

    // Operatoren
    Bool operator ! ();	// TRUE, wenn Gerade ungültig, sonst FALSE
    operator Bool ();	// TRUE, wenn Gerade gültig, sonst FALSE
    
    Bool operator == (Punkt& Pkt); 	// TRUE, wenn Punkt auf Geraden liegt,
				   	// sonst FALSE
    Bool operator == (Gerade& Ger); 	// TRUE, wenn Geraden aufeinander liegen,
				    	// sonst FALSE
    Gerade operator + (long Abstand); 	// Parallele im positivem Abstand,
	  // die am Anfangs- und Endpunkt jeweils um "Abstand" verlängert wird
    Gerade operator - (long Abstand); 	// Parallele im negativem Abstand,
	  // die am Anfangs- und Endpunkt jeweils um "Abstand" verlängert wird

    Bool operator || (Gerade& G); 	// TRUE, wenn Geraden parallel sind
					// sonst FALSE
    Punkt operator ^ (Gerade& G);
    // Berechnet den Schnittpunkt zweier Geraden, wenn ihre Anstiege ver-
    // schieden sind. Existiert kein Schnittpunkt, wird der 
    // Punkt (LONG_MAX, LONG_MAX) zurückgegeben.

// Destruktor
		// keiner
};

inline long DtoL (const double& D);	// konvertiere double nach long

#endif // NOGERADE

#endif // _GERADE_HXX
