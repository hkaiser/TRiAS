/*
File: PUNKTLI.HPP
realiert die Verwaltung einer Punkt-Liste.

erarbeitet : J. Benkenstein		Stand vom 21. August 1995
*/

#ifndef _PUNKTLI_HPP
#define _PUNKTLI_HPP

#ifndef NO_PUNKT
class Punkt {
private:
// Attribute
	double _X, _Y;			// Koordinaten

public:
// Konstruktor/Destruktor
	Punkt (void) { _X = _Y = 0.0; }
	Punkt (double X, double Y) : _X (X), _Y (Y) {}
	Punkt (Punkt *pPt) : _X (pPt -> _X), _Y (pPt -> _Y) {}
	~ Punkt (void) {};

//  sonstige Member
	double & X (void) { return _X; }
	double & Y (void) { return _Y; }
	
//	Operatoren
	BOOL operator == (Punkt &P) { return ((P.X() == _X) && (P.Y() == _Y)); }			
};
#endif // NO_PUNKT

#ifndef NO_PUNKT_LISTE
// PunktListe verwaltet Punkte iin einer Liste
class PunktListe;
class PunktListe : public CListContainer
{
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
	PunktListe   (void);
	~ PunktListe (void);

// sonstige Member
	Bool AddPunkt (double X, double Y); // True, wenn neuer Punkt
										  // in Liste aufgenommen, sonst False
	Bool AddPunkt (Punkt *pPt); // True, wenn neuer Punkt
							   	// in Liste aufgenommen, sonst False
	Bool AddFirstPunkt (void); 	// True, wenn neuer 1. Punkt an das akt. Ende
							   	// der Liste kopiert, sonst False
	Bool OutPunkte (double *&pX, double *&pY);  // alle Punkte in Speicher ausgeben
					
	Bool isFlaeche (void); 	// ist diese Punktmenge eine evtl.Flaeche ?

	Bool GetLastPunkt (double &X, double&Y); 	//	letzten Punkt lesen
	Bool GetFirstPunkt (double &X, double&Y); 	// 	ersten Punkt lesen

//	Koordinaten transformieren
//	neue Liste ist explizit freizugeben
	PunktListe *Transform (double dXBasis, double dYBasis,
						   double dXInsert, double dYInsert,
						   double dXMasstab, double dYMasstab,
						   double dDrehWinkel,
						   double dXOffset, double dYOffset);

//	operatoren
	Bool operator = (PunktListe&);
	Bool operator += (PunktListe&);
};

DeclareLock (PunktListe, Punkt);
#endif // NO_TEXT_MERKMALS_LISTE

#endif // _PUNKTLI_HPP
