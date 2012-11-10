// Klassendefinition fuer RelationsObjekte
// File: RELOBJ.HXX

#if !defined(_RELOBJ_HXX)
#define _RELOBJ_HXX

#if !defined(NORELATIONSOBJEKT)

class RelationsObjekt : 
	public ExtShapeObject 
{
private:
	KomplexObjekt *_pKO;	// KomplexObjekt
	Rectangle _Box;			// umschreibendes Rechteck
	Dimension _DotsPerMM;	// Auflösung des Bezugsfensters
	CIdentifikator *_pId;	// IdentifikatorBeschreibung des KomplexObjektes
	CONrTable *_pTabONr;	// ShapesSubTable
	short m_fFlags;			// ZeichenFlags zwischenspeichern

public:
// Konstruktor/Destruktor
		RelationsObjekt (KomplexObjekt &);
		~RelationsObjekt (void);

// virtuelle Funktionen
	ObjTyp isTyp (void);
	INT_PTR &ObjNr (void);
	INT_PTR &Id (void);
	VisInfo *SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *, CONrTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);

	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);
	Rectangle BoundingBox (void) { return _Box; }
	GeoObjekt *NewGI (GeoObjekt *);
	Color ChangeColor (Color *);

protected:
	void DrawEx (DWORD);	// SchriftZug malen

public:
// sonstige Memberfunktionen
	KomplexObjekt &KO (void) { return *_pKO; }
};

#endif // NORELATIONSOBJEKT

#endif // _RELOBJ_HXX

