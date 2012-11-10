/*

 File: GERADE.CXX

 Geometrieobjekt (Gerade)

 erstellt: J. Benkenstein		begonnen am: 27.11.91

*/

#include "trias02p.hxx"

#if defined(_FORCE_LEGACY_CODE)

#include <math.h>
#include <limits.h>
#include <gerade.hxx>

// konvertiere double nach long
inline long DtoL (const double &D) 
{
	return (long (D + 0.5));   // runden und zurück
}

// berechnet den Betrag der Geraden zw. Anfangs- u. Endpunkt
double Gerade :: Betrag (void) 
{
// = Wurzel ((x2 - x1) ^2 + (y2 - y1) ^2)
return (sqrt(((double)_EP.X()*_EP.X()) + ((double)_AP.X()*_AP.X()) - (2.0*_EP.X()*_AP.X())+
   	     ((double)_EP.Y()*_EP.Y()) + ((double)_AP.Y()*_AP.Y()) - (2.0*_EP.Y()*_AP.Y())));
}

// berechnet den Mittelpunkt der durch AnfPkt und EndPkt gegeben Geraden
// (Strecke)
/*inline*/ Punkt Gerade :: MittelPunkt (Punkt& AP, Punkt& EP) 
{
	return (Punkt ((AP.X() + EP.X()) / 2,	 // x-Koordinate
        	       (AP.Y() + EP.Y()) / 2));	 // y-Koordinate
}

// berechnet die y-Koordinate eines Punktes auf der Geraden bei gegebenem
// x-Wert, TRUE, wenn Koordinate durch y = mx + n berechenbar, sonst FALSE
Bool Gerade :: Y (const double& x, double& y) 
{
    	if (_AP.X() == _EP.X())  // bei unendlichem Anstieg
		return False;	     // zurück mit Fehler

// y = ((x - x1) / (x2 - x1) * (y2 - y1)) + y1
	y = ((double)(x - _AP.X()) * (double)(_EP.Y() - _AP.Y()) /
	     (double)(_EP.X() - _AP.X())) + (double)_AP.Y();	

return True;
}

// TRUE, wenn Punkt auf Geraden liegt, sonst FALSE
inline Gerade :: operator == (Punkt& Pkt) 
{
// (y -y1) * (x2 -x1) == (y2 -y1) * (x - x1) ?
    return ((double)(Pkt.Y() - _AP.Y()) * (double)(_EP.X() - _AP.X())) ==
	   ((double)(_EP.Y() - _AP.Y()) * (double)(Pkt.X() - _AP.X()));
}


// TRUE, wenn Geraden parallel sind, sonst FALSE
inline Bool Gerade :: operator || (Gerade& G) 
{
// (y2 -y1) * (x4 - x3) == (y4 - y3) * (x2 -x1) ?
    return ((double)((_EP.Y() - _AP.Y()) * (double)(G._EP.X() - G._AP.X())) ==
	   ((double)(G._EP.Y() - G._AP.Y()) * (double)(_EP.X() - _AP.X())));
}


// TRUE, wenn Geraden aufeinander liegen, sonst FALSE
Bool Gerade :: operator == (Gerade& Ger) 
{
   return ((*this || Ger) &&	   // wenn Geraden parallel und
	   (*this == Ger.AP()));   // AnfPkt auf Geraden liegt
}


// Parallele im positivem Abstand, die am Anfangs- und Endpunkt jeweils um
// "Abstand" verlängert wird
Gerade Gerade :: operator + (long Abstand) 
{
	if (Abstand < 0) 
		return operator - (-Abstand);

	if (Abstand == 0)
		return *this;		

double Betrg = Betrag();	// Betrag zwischen Anf- u. EndPkt
double xv = (double)Abstand * (_EP.X() - _AP.X()) / Betrg; // x-Verschiebung
double yv = (double)Abstand * (_EP.Y() - _AP.Y()) / Betrg; // y-Verschiebung

    return (Gerade( DtoL (_AP.X() - xv - yv),  // x-Koordinate AnfPkt (P1)
		    DtoL (_AP.Y() + xv - yv),  // y-Koordinate
		    DtoL (_EP.X() + xv - yv),  // x-Koordinate EndPkt (P2)
		    DtoL (_EP.Y() + xv + yv)));	// y-Koordinate
}

// Parallele im negativem Abstand, die am Anfangs- und Endpunkt jeweils um
// "Abstand" verlängert wird
Gerade Gerade :: operator - (long Abstand) {

    	if (Abstand < 0)
		return operator + (-Abstand);

	if (Abstand == 0)
		return *this;
		
double Betrg = Betrag();	// Betrag zwischen Anf- u. EndPkt
double xv = (double)Abstand * (_EP.X() - _AP.X()) / Betrg; // x-Verschiebung
double yv = (double)Abstand * (_EP.Y() - _AP.Y()) / Betrg; // y-Verschiebung

    return (Gerade( DtoL (_AP.X() - xv + yv),  // x-Koordinate AnfPkt (P4)
		    DtoL (_AP.Y() - xv - yv),  // y-Koordinate
		    DtoL (_EP.X() + xv + yv),  // x-Koordinate EndPkt (P3)
		    DtoL (_EP.Y() - xv + yv)));	// y-Koordinate
}

// Berechnet den Schnittpunkt zweier Geraden, wenn ihre Anstiege verschieden
// sind. Existiert kein Schnittpunkt, wird der Punkt (LONG_MAX, LONG_MAX)
// zurckgegeben.

Punkt Gerade :: operator ^ (Gerade& G) {

	if (*this || G)		  // wenn Geraden parallel,
		return	Punkt(LONG_MAX, LONG_MAX); // zurck mit ungltigem Punkt

// Formel: (dx1*dx2*(y3 - y1) - dy2*dx1x3 + dy1*dx2*x1) / 	
//                    (dy1*dx2 - dy2*dx1) mit dy1 = y2 - y1 usw.  
double Za = // Z„hler;
	((double)(_EP.X() - _AP.X()) * (double)(G._EP.X() - G._AP.X()) * 
	 (double)(G._AP.Y() - _AP.Y()))-
	((double)(G._EP.Y() - G._AP.Y()) * (double)(_EP.X() - _AP.X()) * 
	 (double)G._AP.X()) +
	((double)(_EP.Y() - _AP.Y()) * (double)(G._EP.X() - 
	 (double)G._AP.X()) * (double)_AP.X());
double Ne = // Nenner;
	((double)(_EP.Y() - _AP.Y()) * (double)(G._EP.X() - G._AP.X())) -
	((double)(G._EP.Y() - G._AP.Y()) * (double)(_EP.X() - _AP.X()));
double x = Za / Ne;	// x-Koordinate
double y;		// y-Koordinate berechnen

	if (Y (x, y) || G.Y (x, y))		  // wenn Wert OK
		return Punkt (DtoL (x), DtoL (y));    // mit Schnittpunkt zurck 

return Punkt (LONG_MAX, LONG_MAX);    // mit Fehlerpunkt zurck
}

#endif // defined(_FORCE_LEGACY_CODE)
