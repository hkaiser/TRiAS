// Klassendefinition fuer SchriftObjekte
// File: SCHRIFT.HXX

#if !defined(_SCHRIFT_HXX)
#define _SCHRIFT_HXX

#if !defined(NOSCHRIFTOBJEKT)

#define SO_Transparent 	0x01
#define SO_hasBox	0x02
#define SO_RoundFrame	0x20

#define SO_LeftAlign	0x00
#define SO_Centred	0x04
#define SO_RightAlign	0x08
#define SO_Justified	0x10

#define SO_AlignStyle	0x1c

#define SO_ObjectDrawn	0x80

class SchriftObjekt : public ExtShapeObject {
private:
	BasicGeoText *_pGT;		// eigentlicher Text
	pFont _pF;		// ausgew‰hlter Font
	Color _C;		// ausgew‰hlte Farbe
	short _fStyles;		// SchriftSpezifikation (Extras)
	Rectangle _Box;		// umschreibender Container
	short m_iEscapement;	// Drehwinkel
	
public:
// Konstruktor/Destruktor
		SchriftObjekt (BasicGeoText &);
		~SchriftObjekt (void);

// virtuelle Funktionen
	ObjTyp isTyp (void);
	long &ObjNr (void);
	long &Id (void);
	VisInfo *SetAttributes (CIdentifikator *pId, Dimension, CTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);

	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);
	Rectangle BoundingBox (void) { return _Box; }

protected:
	void DrawEx (DWORD);	// SchriftZug malen

public:
// sonstige Memberfunktionen
	BasicGeoText &GT (void) { return *_pGT; }
	Color ChangeColor (Color *);
	pFont ChangeFont (pFont);
	Bool ChangeMode (Bool newMode);
	Bool ChangeFrame (Bool newFrameMode);
	Bool RoundFrame (Bool newRoundFrame);

	short SetAlignStyle (short newStyle);
	void SetEscapement (short newEscape);
	short GetEscapement (void) { return m_iEscapement; }
		
	char *ChangeText (char *);

	GeoObjekt *NewGI (GeoObjekt *);

	void CorrectPosition (Point &);
};

// drehen des umschlieﬂenden Rechtecks ----------------------------------------
void RotateRect (Point *pPts, Point &prRot, Rectangle &, short iEscapement, short iAlignStyle);

#endif // NOSCHRIFTOBJEKT

#endif // _SCHRIFT_HXX

