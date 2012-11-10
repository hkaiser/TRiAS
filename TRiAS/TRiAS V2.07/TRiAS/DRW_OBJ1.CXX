/*

 File: DRW_OBJ1.CXX

 Zeichenobjekt (Kreis)

 erstellt: J. Benkenstein		am: 25.11.91

*/

#include "triaspre.hxx"

#include <xtensnd.h>

// copy-constructor realisiert Initialisierung eines KreisObjektes ------------
KreisObjekt :: KreisObjekt (KreisObjekt& KrsObj) 
	     : ExtShapeObject (Point (0, 0), Dimension())
{
// Werte von KrsObj übernehmen
	_pGKr = new GeoKreis(KrsObj.GKr().DB(), KrsObj._pGKr->ObjNr(), KrsObj._pGKr->Id(), 
		             KrsObj._pGKr->MP(), KrsObj._pGKr->Radius()); 
	if (_pGKr == NULL) // wenn kein Speicherplatz mehr vorh.
		db_error (EC_NOMEMORY, RC_cpyKrsObj); // Fehlermeldung ausgeben
}


// Assignment-Operator überladen ----------------------------------------------
void KreisObjekt :: operator= (KreisObjekt& KrsObj) 
{
	if (this != &KrsObj) {		// keine Selbstzuweisung
		if (_pGKr != NULL) // wenn noch alte Geometriedaten existieren,
			DELETE (_pGKr);  // diese löschen

	// Werte von KreisObj übernehmen
		_pGKr = new GeoKreis(KrsObj.GKr().DB(), KrsObj.GKr().ObjNr(), KrsObj.GKr().Id(),
				     KrsObj.GKr().MP(), KrsObj.GKr().Radius());
		if (_pGKr == NULL) // wenn kein Speicherplatz mehr vorh.
			db_error (EC_NOMEMORY, RC_asKrsObj); // Fehlermeldung ausgeben
   	}
}	

KreisObjekt :: ~KreisObjekt (void) 
{
	ResetBase ();		// ExtShapeObjekt zurücksetzen
	DELETE (_pGKr);
}


void KreisObjekt :: ResetAttributes (void)
{
	ChangePen (NULL);
	ChangeBrush (NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Zeichenattribute setzen 
VisInfo *KreisObjekt :: SetAttributes (CIdentifikator *pId, Dimension DotsPerMM, 
				       CTable &, VisType, short) 
{
// Pen & Brush aus IdentifikatorTree holen und in KreisObjekt setzen
	if (pId == NULL) return NULL;

// Objekt mit diesem Ident wird gezeichnet
	pId -> SetVisible (TPFlaeche);

// Testen, ob VisInfo gegeben ist
	if (!pId -> isCustomized(TPFlaeche)) 	// Warnung ausgeben
		pId -> ReportVisInfoError (WC_NOVISINFOFLAECHE, RC_SetAttributesFlaeche, VT_Flaeche);

VisInfo *pVI = pId -> hasVI(VT_Flaeche) ? &pId -> FVI() : NULL;
short locWidth = pId -> FrameWidth ();

// neuerdings Linienbreite in 1/100 mm
	if (GetGeoDBVersion() >= VERSION05000004)
		locWidth = (short)(((long)locWidth * (long)DotsPerMM.Width()) / 100L);

// Flächenkontur bei Bedarf verdünnen (skalieren)				
	if (M() > 1.0)
		locWidth = (short)(locWidth / M() + 0.5);

	ChangePen (pId -> GetPen (VT_Flaeche, locWidth));
	ChangeBrush (pId -> GetBrush ((HDC)GetCanvas() -> Handle (API_WINDOW_TARGETHDC)));

	return VI_NotChanged;	// erstmal immer zeichnen
}

// Zeichnen eines KreisObjektes
extern HPALETTE hPalette;

void KreisObjekt :: DrawEx (DWORD /*dwData*/) 
{
HDC hDC = Handle(API_DRAWOBJECT_HDC);
HPALETTE hOldPalette;
int oldBkMode;
int oldFillMode;

	if (FullDCInit()) {
		if (hPalette != NULL) {
		// Palette einstellen       
			hOldPalette = SelectPalette (hDC, hPalette, FALSE);
			RealizePalette (hDC);
		}

		if (!(FullDCInit() & FDC_PaletteOnly)) {
			oldBkMode = SetBkMode (hDC, TRANSPARENT);
			oldFillMode = SetPolyFillMode (hDC, ALTERNATE);
		}
	} else
		oldBkMode = SetBkMode (hDC, TRANSPARENT);


// neuen Stift einstellen
HPEN hOldPen;

	if (GetPen() != NULL) hOldPen = (HPEN)SelectObject (hDC, GetPen() -> Handle());

// neuen Pinsel einstellen
HBRUSH hOldBrush;
Brush *pHollowBrush = NULL;

	if (GetBrush() != NULL) {
	HBRUSH hBr = GetBrush() -> Handle();
	
		UnrealizeObject (hBr);
		hOldBrush = (HBRUSH)SelectObject (hDC, hBr);
	} else {
		pHollowBrush = new Brush (HollowBrush);
		hOldBrush = (HBRUSH)SelectObject (hDC, pHollowBrush -> Handle());
	}

// Kreis (Ellipse) zeichnen
long Rad = GKr().Radius();	// Kreisradius bestimmen
Point olP = OCtoDC (GKr().MP().X() - Rad, GKr().MP().Y() + Rad); 
Point urP = OCtoDC (GKr().MP().X() + Rad, GKr().MP().Y() - Rad); 

// Windows-Zeichenfunktion
	if (!Ellipse (hDC, olP.X(), olP.Y(), urP.X(), urP.Y()))
		DEXD_ObjectNotDrawed5 (ObjNr());

// DeviceKontext zurücksetzen
	if (GetPen() != NULL) SelectObject (hDC, hOldPen);

	SelectObject (hDC, hOldBrush);
	if (pHollowBrush) delete pHollowBrush;

	if (FullDCInit()) {
		if (hPalette)
			SelectPalette (hDC, hOldPalette, FALSE);

		if (!(FullDCInit() & FDC_PaletteOnly)) {
			SetBkMode (hDC, oldBkMode);
			SetPolyFillMode (hDC, oldFillMode);
		} else
			FullDCInit() &= ~FDC_PaletteOnly;
	} else
		SetBkMode (hDC, oldBkMode);
}

// Virtuelle Funktionen -------------------------------------------------------
KreisObjekt :: operator GeoObjekt * (void) { return &GKr(); }
GeoObjekt *KreisObjekt :: operator -> (void) { return &GKr(); }
ObjTyp KreisObjekt :: isTyp (void) { return GKr().isA(); }
long &KreisObjekt :: Id (void) { return GKr().Id(); }
long &KreisObjekt :: ObjNr (void) { return GKr().ObjNr(); }

GeoObjekt *KreisObjekt :: NewGI (GeoObjekt *pNewGKr) {

	if (pNewGKr == NULL) return NULL;

GeoObjekt *pOldGKr = _pGKr;

	_pGKr = (GeoKreis *)pNewGKr;

return pOldGKr;
}
