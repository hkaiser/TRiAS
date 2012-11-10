/*

 File: DRW_OBJ1.HXX

 Zeichenobjekt (Kreis)

 erstellt: J. Benkenstein		am: 20.11.91

*/

#ifndef _DRW_OBJ1_HXX
#define _DRW_OBJ1_HXX

#if !defined(NOKREISOBJEKT)
// KreisObjekt ---------------------------------------------------------------
class KreisObjekt : public ExtShapeObject {
private:
	GeoKreis *_pGKr;	// Zeiger auf Geometrie-Daten

protected:
	void DrawEx (DWORD);	// Kreis zeichnen

public:
// Konstruktoren
		KreisObjekt (void) : ExtShapeObject (Point(0, 0), Dimension())
				{ _pGKr = NULL; }
		KreisObjekt (GeoKreis &GK) : ExtShapeObject (Point (0,0), Dimension())
				{ _pGKr = &GK; }
		KreisObjekt (KreisObjekt &);

// Memberfunktionen
	ObjTyp isTyp (void);
	GeoKreis &GKr (void) const { return *_pGKr; } 	// Zeiger aud Geometrie
	void operator= ( KreisObjekt& );		// Zuweisung überladen

// Zeichenattribute setzen
	VisInfo *SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *, CONrTable &, VisType, short);
	void ResetAttributes (void);
 
// Identifikator und Objektnummer liefern
	INT_PTR &Id (void);
	INT_PTR &ObjNr (void);

// TypKonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

	GeoObjekt *NewGI (GeoObjekt *);

// Destruktor
		~KreisObjekt (void);
};
#endif // NOKREISOBJEKT

#endif // _DRW_OBJ1_HXX
