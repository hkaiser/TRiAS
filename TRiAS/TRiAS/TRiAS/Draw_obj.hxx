///////////////////////////////////////////////////////////////////////////
// Datenbankobjekte (GeoPunkt, GeoKante, GeoFlaeche, GeoKO)
// Draw_obj.hxx

#if !defined(_DRAW_OBJ_HXX__A37D8268_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _DRAW_OBJ_HXX__A37D8268_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <attribs.hxx>
#include <objliste.hxx>

///////////////////////////////////////////////////////////////////////////////
// erweiterte Bitmap 
class ExtBitmapObject : 
	public BitmapObject
{
protected:
	Color _myC;	// lokale Farbeinstellung
	void Draw (void);       // Bitmap zeichnen

public:
// Konstruktoren
	ExtBitmapObject (Point P, Dimension D, pBitmap pB, Color C)
		: BitmapObject (P, D, pB), _myC(C) {}
};

///////////////////////////////////////////////////////////////////////////////
// PunktObjekt 
class PunktObjekt : 
	public ExtShapeObject 
{
private:
	GeoPunkt *_pGP;			// Geometrie
	unsigned int _Marker;	// Markertyp
	Color _C;				// Farbe
	short m_iRotation;		// Drehung
	Color m_SecC;			// zweite Farbe

protected:
	void DrawEx (DWORD);	// Punkt Zeichnen

public:
// Konstruktor
		PunktObjekt (GeoPunkt &rPt, Color *pC = NULL);

// Memberfunktionen
	Rectangle BoundingBox (void);	// Container (HiHi) WindowKoord
	void SetMarker (unsigned int MTyp) { _Marker = MTyp; }
	ObjTyp isTyp (void);
	Color ChangeColor (Color *newColor) 
		{ Color oldColor = _C; _C = *newColor; return oldColor;	}
	Color Change2ndColor (Color newColor) 
		{ Color oldColor = m_SecC; m_SecC = newColor; return oldColor;	}
	void SetRotation (short iRot) { m_iRotation = iRot; }
	short GetRotation (void) { return m_iRotation; }
	GeoPunkt &GP(void) const { return *_pGP; }

// Zeichenattribute setzen
	VisInfo *SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *pId, CONrTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);
	void TypeDependendDraw (CIdentifikator *, CONrTable &, Dimension);

// ObjektNummer und Identifikator liefern
	INT_PTR &ObjNr (void);
	INT_PTR &Id (void);

// Typkonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *pGO);

// Destruktor
		~PunktObjekt (void);
};

///////////////////////////////////////////////////////////////////////////////
// KantenObjekt 
class KantenObjekt : 
	public ExtShapeObject 
{
private:
	GeoKante *_pGK;         // Geometrie
	
protected:
	void DrawEx (DWORD);           // KanteZeichnen

public:
// Konstruktor
		KantenObjekt (GeoKante &, pPen = NULL);

// Memberfunktionen
	Rectangle BoundingBox ();       // KantenContainer in WindowKoord
	ObjTyp isTyp (void);
	GeoKante &GK (void) const { return *_pGK; }

// Zeichenattribute setzen
	VisInfo *SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *pId, CONrTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);

// ObjektNummer und Identifikator liefern
	INT_PTR &ObjNr (void);
	INT_PTR &Id (void);

// TypKonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *pGO);

// Destruktor
		~KantenObjekt (void);
};

///////////////////////////////////////////////////////////////////////////////
// MaschenObjekt 
class MaschenObjekt : 
	public ExtShapeObject 
{
private:
	GeoFlaeche *_pGF;			// Geometrie
	short _iMode;
	Color m_BkCol;				// HintergrundFarbe für Opaque
	Bitmap *m_pBmp;

protected:
	void DrawEx (DWORD);		// Masche zeichen

public:
// Konstruktor
		MaschenObjekt (GeoFlaeche &, pPen = NULL, pBrush = NULL);

// Memberfunktionen
	Rectangle BoundingBox (void);	// MaschenContainer in WindowKoord
	ObjTyp isTyp (void);
	GeoFlaeche &GF (void) const { return *_pGF; }

// Zeichenattribute setzen
	VisInfo *SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *pId, CONrTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);
	void TypeDependendDraw (CIdentifikator *, CONrTable &, Dimension);

// ObjektNummer und Identifikator liefern
	INT_PTR &ObjNr (void);
	INT_PTR &Id (void);

// TypKonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *pGO);

	short isOpaque (void) { return _iMode & BMOpaque; }
	bool isBkConture (void) { return _iMode & BMBkConture; }
	void SetBkMode (short isOpaque);
	void SetBkConture (bool isBkConture);
	void SetBkColor (Color C) { m_BkCol = C; }
	Color GetBkColor (void) { return m_BkCol; }	
	void ChangeBitmap (Bitmap *pBmp) { m_pBmp = pBmp; }

	bool DrawNormal (HDC hDC, DatenBasisObjekt *pDBO, bool fForceHollow = false);	// normales Zeichnen
	bool FrameObject (HDC hDC, DatenBasisObjekt *pDBO);					// dieses Objekt ist ClipregionObj --> mit Frame versehen
	bool DrawTransparentWithPattern (HDC hDC, DatenBasisObjekt *pDBO);	// transparente patterns

// Destruktor
		~MaschenObjekt (void);
};

const short WSActVis 	= 0x01;		// Konstanten für WriteSightIDs
const short WSDelView 	= 0x02;

#if !defined(LONGCOMP)
#define LONGCOMP
// Funktionen für ObjektListe : Tree (Zugriffs- und Vergleichsfunktionen) -----
inline int LongCmp (void *Key1, void *Key2) 
{
long Par1 = *(long *)Key1, Par2 = *(long *)Key2;

	if (Par1 > Par2)        return 1;
	else if (Par1 < Par2)   return -1;
	else                    return 0;
}
#endif // LONGCOMP

///////////////////////////////////////////////////////////////////////////////
// DatenBasisObjekt
#include "DBObject.h"

#endif // !defined(_DRAW_OBJ_HXX__A37D8268_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
