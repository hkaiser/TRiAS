///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Objliste.hxx | Objekte, die Zeichnen der Geometrieobjekte ermöglichen

#if !defined(_OBJLISTE_HXX__766329D4_0736_11D2_8657_00600875138A__INCLUDED_)
#define _OBJLISTE_HXX__766329D4_0736_11D2_8657_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <drawobj.hxx>

#include <objfeld.hxx>
#include <listobj.hxx>
#include <objstat.hxx>

// Erweiterte Basisklasse für zu zeichnende Objekte 
typedef enum tagDRAWSTATUS {
	DRAWSTATUS_VisInfoNotChanged = 0,
	DRAWSTATUS_VisInfoChanged = 1,
	DRAWSTATUS_NoDrawing = 2,
} DRAWSTATUS;

// Verschiedene Modi bei der Initialisierung des hDC 
const int FDC_NoInit 		= 0x00;
const int FDC_FullInit 		= 0x01;
const int FDC_PaletteOnly 	= 0x02;
const int FDC_ActivateOnly	= 0x04;

class CIdentifikator;
class CFeature;
class CFeatureTree;
class DatenBasisObjekt;

class ExtShapeObject : 
	public ShapeObject
{
private:
	ObjStatus _OS;
	class CFeatureTree *m_pFT;		// MerkmalsCache
	unsigned short m_fIsDrawn : 1;	// wurde gezeichnet

	static int _FullDCInit;		// DC für jedes Objekt vollständig initialisieren
	
public:
// Konstruktoren
	ExtShapeObject (Point P, Dimension D,
				 pPen pP = NULL, pBrush pB = NULL, 
				 ObjStatus OS = OS_Normal);

// Memberfuntkionen
virtual ObjTyp isTyp (void) { return OT_UNKNOWN; }	// liefert ObjektTyp

// Typkonvertierung
_TRIAS02_ENTRY virtual GeoObjekt * operator -> (void);
_TRIAS02_ENTRY virtual operator GeoObjekt * (void);

// Pen und Brush zugänglich machen
	pPen GetPen (void) { return mypen; }
	pBrush GetBrush (void) { return mybrush; }
	Dimension &Size (void) { return dim; }		// liefert ObjGröße

// ObjektStatus zugänglich machen
	ObjStatus &Status (void) { return _OS; }
	void ResetBase (void) { ChangeBrush (NULL); ChangePen (NULL); }

// ZeichenAttribute einstellen
_TRIAS02_ENTRY virtual VisInfo *SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *pId, CONrTable &, VisType = VT_Default, short = 0);
_TRIAS02_ENTRY virtual void ResetAttributes (void);

// ObjektNummer und Identifikator des zugehörigen GeoObjektes liefern
_TRIAS02_ENTRY virtual INT_PTR & ObjNr (void);
_TRIAS02_ENTRY virtual INT_PTR & Id (void);

// ObjektContainer in WindowsKoordinaten liefern
_TRIAS02_ENTRY virtual Rectangle BoundingBox (void);

// Geometrie des abgeleiteten GeoObjektes ändern
virtual GeoObjekt *NewGI (GeoObjekt *) { return NULL; }

// typabhängige Visualisierung
_TRIAS02_ENTRY virtual void TypeDependendDraw (CIdentifikator *, CONrTable &, Dimension);

// Verwaltung des MerkmalsCaches
_TRIAS02_ENTRY void ClearFeatureCache (void);
_TRIAS02_ENTRY class CFeature *FFindFeature (long lMCode);
_TRIAS02_ENTRY BOOL FAddFeature (long lMCode, char *pMWert);
_TRIAS02_ENTRY BOOL FDeleteFeature (long lMCode);
	
	int &FullDCInit (void) { return _FullDCInit; }

	Window *GetCanvas (void) { return canvas; }
	Window *SetCanvas (Window *pW) { Window *p = canvas; canvas = pW; return p; }

// special effects for object oriented visualisation
	DRAWSTATUS SpecialEffects (long lONr, VisType iVTyp, CIdentifikator *pId, int fFlags, VisInfo **ppVisInfo);

// Destruktor
_TRIAS02_ENTRY virtual ~ExtShapeObject (void);

// Sichtbarkeit
inline	BOOL isVisible (void) { return m_fIsDrawn ? true : false; }
inline	void SetVisible (BOOL fVis = true) { m_fIsDrawn = fVis ? true : false; }
};

#endif // !defined(_OBJLISTE_HXX__766329D4_0736_11D2_8657_00600875138A__INCLUDED_)
