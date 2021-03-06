// Objekte, die Zeichnen der Geometrieobjekte erm�glichen ---------------------
// File: OBJLISTE.HXX

#if !defined(_OBJLISTE_HXX)
#define _OBJLISTE_HXX

#if !defined(_OBJFELD_HXX)
#include <objfeld.hxx>
#endif

#if !defined(_LISTOBJ_HXX)
#include <listobj.hxx>
#endif

#if !defined(NOEXTSHAPEOBJECT)

// Erweiterte Basisklasse f�r zu zeichnende Objekte ---------------------------
#if !defined(_OBJSTAT_HXX)
#include <objstat.hxx>
#endif // _OBJSTATUS_HXX

typedef enum tagDRAWSTATUS {
	DRAWSTATUS_VisInfoNotChanged = 0,
	DRAWSTATUS_VisInfoChanged = 1,
	DRAWSTATUS_NoDrawing = 2,
} DRAWSTATUS;

class CFeature;
class CFeatureTree;

class ExtShapeObject : 
	public ShapeObject, 
	public Transformation 
{
private:
	ObjStatus _OS;
	class CFeatureTree *m_pFT;	// MerkmalsCache
	unsigned short m_fIsDrawn : 1;	// wurde gezeichnet
	
public:
// Konstruktoren
	EXPORT02 ExtShapeObject (Point P, Dimension D,
				 pPen pP = NULL, pBrush pB = NULL, 
				 ObjStatus OS = OS_Normal);

// Memberfuntkionen
virtual ObjTyp isTyp (void) { return OT_UNKNOWN; }	// liefert ObjektTyp

// Typkonvertierung
_TRIAS02_ENTRY virtual GeoObjekt * EXPORT02 operator -> (void);
_TRIAS02_ENTRY virtual	EXPORT02 operator GeoObjekt * (void);

// Pen und Brush zug�nglich machen
	pPen GetPen (void) { return mypen; }
	pBrush GetBrush (void) { return mybrush; }
	Dimension &Size (void) { return dim; }		// liefert ObjGr��e

// ObjektStatus zug�nglich machen
	ObjStatus &Status (void) { return _OS; }
	void ResetBase (void) { ChangeBrush (NULL); ChangePen (NULL); }

// ZeichenAttribute einstellen
_TRIAS02_ENTRY virtual VisInfo * EXPORT02 SetAttributes (CIdentifikator *pId, Dimension, CTable &, VisType = VT_Default, short = 0);
_TRIAS02_ENTRY virtual void EXPORT02 ResetAttributes (void);

// ObjektNummer und Identifikator des zugeh�rigen GeoObjektes liefern
_TRIAS02_ENTRY virtual long & EXPORT02 ObjNr (void);
_TRIAS02_ENTRY virtual long & EXPORT02 Id (void);

// ObjektContainer in WindowsKoordinaten liefern
_TRIAS02_ENTRY virtual Rectangle EXPORT02 BoundingBox (void);

// Geometrie des abgeleiteten GeoObjektes �ndern
virtual GeoObjekt *NewGI (GeoObjekt *) { return NULL; }

// typabh�ngige Visualisierung
_TRIAS02_ENTRY virtual void EXPORT02 TypeDependendDraw (CIdentifikator *, CTable &, Dimension);

// Verwaltung des MerkmalsCaches
_TRIAS02_ENTRY void ClearFeatureCache (void);
_TRIAS02_ENTRY class CFeature *FFindFeature (long lMCode);
_TRIAS02_ENTRY bool FAddFeature (long lMCode, char *pMWert);
_TRIAS02_ENTRY bool FDeleteFeature (long lMCode);
	
	Window *GetCanvas (void) { return canvas; }
	Window *SetCanvas (Window *pW) { Window *p = canvas; canvas = pW; return p; }

// special effects for object oriented visualisation
	DRAWSTATUS SpecialEffects (long lONr, VisType iVTyp, CIdentifikator *pId, int fFlags, VisInfo **ppVisInfo);

// Destruktor
_TRIAS02_ENTRY virtual	EXPORT02 ~ExtShapeObject (void);

// Sichtbarkeit
inline	bool isVisible (void) { return m_fIsDrawn ? true : false; }
inline	void SetVisible (bool fVis = true) { m_fIsDrawn = fVis ? true : false; }
};
#endif // NOEXTSHAPEOBJECT

#if !defined(NOEXTBITMAP)
// erweiterte Bitmap ---------------------------------------------------------
class ExtBitmapObject : public BitmapObject, public Transformation {
protected:
	Color _myC;	// lokale Farbeinstellung
	void Draw (void);       // Bitmap zeichnen

public:
// Konstruktoren
		ExtBitmapObject (Point P, Dimension D, pBitmap pB, Color C) :
					BitmapObject (P, D, pB) { _myC = C; }
};

#if 0
#if !defined(NOCOLORBITMAP)
class CColorBitmapObject : public ExtBitmapObject {
private:
	short m_iXOffset;	// Offset in BitmapBar
	Color m_2ndC;		// sekund�re Farbe

protected:
	void Draw (void);       // ColorBitmap zeichnen

public:
// Konstruktoren
		CColorBitmapObject (Point P, Dimension D, pBitmap pB, 
				    Color C, Color C2nd, short xOffset) :
			ExtBitmapObject (P, D, pB, C) 
				{ m_iXOffset = xOffset; m_2ndC = C2nd; }
};
#endif // NOCOLORBITMAP
#endif
#endif // NOEXTBITMAP

#endif // _OBJLISTE_HXX

