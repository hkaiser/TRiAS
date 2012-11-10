// Methoden fuer Zeichen-Objekte -----------------------------------------------
// File: DRAW_OBJ.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>
#include <xtensnd.h>
#include <funcs03.h>

#include "clbmpobj.hxx"

#define MYROPCODE 	0x00b8074a
#define MYROPCODEINV	0x00e20746

extern HPALETTE hPalette;
extern bool PrintEFlag;

#if 0 // ======================================================================
enum PRINTMODE {
	PM_PRINTPSCRIPT1 = 1,
	PM_PRINTPSCRIPT2 = 2,
};

int g_rgPrintMode = PM_PRINTPSCRIPT1;
#endif // =====================================================================

HRGN CreateObjectRegion (GeoObjekt *pGO, CoOrd dY); 
_TRIAS02_ENTRY bool EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);

#if !defined(WIN32)
bool IsWin31 (void);
#endif

// lokale Konvertierung des VisTypes in entsprechende Bits --------------------
static short VisTypeToBits (VisType iVTyp, short iDefFlags)
{
	switch (iVTyp) {
	case VT_Punkt:		return TPPunkt;
	case VT_Linie:		return TPLinie;
	case VT_Flaeche:	return TPFlaeche;
	case VT_Text:		return TPText;
	case VT_Default:	return iDefFlags;
	default:
		break;
	}

return 0;
}


// Konstruktor der BasisKlasse ------------------------------------------------
ExtShapeObject :: ExtShapeObject (Point P, Dimension D, pPen pP, pBrush pB, ObjStatus OS)
		: ShapeObject (P, D, pP, pB) 
{
	_OS = OS;
	m_pFT = NULL;		// kein MerkmalsCache
	SetVisible (false);
}

// PunktObjekt (Zeichnen eines Punktes) ---------------------------------------
// Konstruktor
PunktObjekt :: PunktObjekt (GeoPunkt &Pt, unsigned int MTyp, Color *pC)
	     : ExtShapeObject (OCtoDC (Pt), Dimension (13, 13), NULL, NULL)
{
// GeometrieObjekt setzen
	_pGP = &Pt;

// Marker setzen
	_Marker = MTyp;

// Farbe setzen
	if (pC == NULL) {
	// Standard setzen
	unsigned long Col = GetSysColor (COLOR_WINDOWTEXT);
		_C = *(Color *)&Col;
	} else
	// Vorgaben wählen
		_C = *pC;

// alles Andere Initialisieren
	m_iRotation = 0;	// keine Drehung
	m_SecC = Color ((ColorVal)0xff, (ColorVal)0xff, (ColorVal)0xff);
}


// Zeichnen eines PunktObjektes -----------------------------------------------
inline CoOrd imax (CoOrd x1, CoOrd x2) { return (x1 < x2) ? x1 : x2; }

CBitmapBar *DatenBasisObjekt :: GetBmp (unsigned int uiPntID, Dimension &dim) const
{
	if (uiPntID >= (unsigned int)m_iBmpCnt) return NULL;	// Fehler

// Je nach geforderter Größe wird die TargetBitmap ausgewählt
// Die TargetBitmaps sind 15*15, 23*23 und 32*32 Pixel groß. Es wird bevorzugt 
// gestreckt als gestaucht.
CoOrd iWidth = m_pBmp15sw -> FWidth(uiPntID);
CoOrd iHeight = m_pBmp15sw -> FHeight(uiPntID);

	if (iWidth < 0 || iHeight < 0)
	    	return NULL;	// Fehler

	if (iWidth >= dim.Width() && iHeight >= dim.Height())
	    	return m_pBmp15sw;

	if (m_pBmp23sw -> FWidth(uiPntID) >= dim.Width() && 
	    m_pBmp23sw -> FHeight(uiPntID) >= dim.Height())
	    	return m_pBmp23sw;

return m_pBmp32sw;
}

void PunktObjekt :: DrawEx (DWORD dwData) 
{
// Marker für Punktobjekte auswählen
Point locPt (OCtoDC (GP()));

	if (!((DatenBasisObjekt *)dwData) -> FNewPnts()) {
	Bitmap *pBM = new Bitmap (ResID (_Marker));
	ExtBitmapObject EBMO (locPt, Size(), pBM, _C);
	
		GetCanvas() -> Draw (&EBMO);
		DELETE (pBM);
	} else {
	DatenBasisObjekt *pDBO = (DatenBasisObjekt *)dwData;
	unsigned int uiMarker = pDBO -> FGetIndex (_Marker + 1 - MARKER1);
	CBitmapBar *pBmp =  pDBO -> GetBmp (uiMarker, Size());
	
		if (pBmp) {
		CColorBitmapObject CBMO (locPt, Size(), *pBmp, _C, 
					 m_SecC, uiMarker, m_iRotation);
		
			GetCanvas() -> DrawEx (&CBMO, (DWORD)(void *)hPalette);
		}
	}
}


// Umschließendes Rechteck eines Punktobjektes --------------------------------
Rectangle EXPORTTRIAS PunktObjekt :: BoundingBox (void) 
{
Point Pt = OCtoDC (GP()); // .X(), GP().Y());
Dimension Dim = Size();

	Pt.X() -= Dim.Width()/2;
	Pt.Y() += Dim.Height()/2;

return (Rectangle (Pt, Dim));
}

void PunktObjekt :: ResetAttributes (void) {}

// setzen der Zeichenattribute eines Punktobjektes ----------------------------
VisInfo *PunktObjekt :: SetAttributes (CIdentifikator *pId, Dimension DotsPerMM, 
				       CTable &, VisType iVTyp, short fFlags) 
{
	if (pId == NULL) return NULL;	// Ident nicht da -> nicht zeichnen

	if (iVTyp == VT_Default) 	// visualiseren als
		iVTyp = VT_Punkt;

// Einstellen der ObjektParameter
long res = 10L;

	if (GetGeoDBVersion() >= VERSION05000004)
		res = 100L;

// evtl. Neueinstellen der Parameter in einer Erweiterung
Dimension locSize (0, 0);
Color locC;
short _iDrawResult = DO_UnChanged;
VisInfo *pOldVI = NULL;
short _iVisInfoChanged = false;

	switch (pId -> DType() & DT_DrawingMask) {
	case DT_HasNewVI:
	// eine überschlaue Erweiterung hat eine neue VI für uns
		{
		// nur beim normalen Zeichnen
		DRAWOBJECT dObj;

			dObj.dwSize = sizeof(DRAWOBJECT);
			dObj.lObjNr = ObjNr();		// ObjektNummer
			if (pId -> hasVI (iVTyp))
				dObj.pNewVI = (VisInfo *)pId -> VI(iVTyp).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = pId -> Id();
			dObj.m_fFlags = fFlags;

			if ((_iDrawResult = DEXN_DrawObject (dObj)) & DT_NoDrawing) {
				if (_iDrawResult & DO_ColorChanged)
					FullDCInit() |= FDC_PaletteOnly;
				if (dObj.pNewVI) delete dObj.pNewVI;
				DEXD_ObjectNotDrawed1 (ObjNr());
				return NULL;
			}

			if (_iDrawResult & DO_VisInfoChanged) {
				if (!(FullDCInit() & FDC_ActivateOnly) &&
				    _iDrawResult & DO_ColorChanged) {
				// evtl. Farbe, die noch nicht in der Palette existiert
					if (ExpandPalette (hPalette, dObj.pNewVI))
						FullDCInit() |= FDC_PaletteOnly;
				}
				pOldVI = pId -> ChangeVisInfo (dObj.pNewVI, iVTyp);
				_iVisInfoChanged = true;
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			}
		}
		break;

	case DT_Normal:
	// alles wie gehabt
		break;

	default:
		DEXD_ObjectNotDrawed2 (ObjNr());
		return NULL;
	}

	FullDCInit() &= ~FDC_ActivateOnly;
                                
// Testen, ob VisInfo gegeben ist
short iVMsk = VisTypeToBits (iVTyp, TPPunkt);

	if (!pId -> isCustomized(iVMsk)) 	// Warnung ausgeben
		pId -> ReportVisInfoError (WC_NOVISINFOPUNKT, RC_SetAttributesPunkt, iVTyp);

// wenn anderer ObjektTyp vorgegaukelt werden soll
VisType VT;

	if (pId -> hasVI(iVTyp) && 
	    (VT = pId -> VI(iVTyp).isA()) != VT_Punkt && VT != VT_Default) 
	{
		if (pOldVI) {
		VisInfo *pVI = pId -> ChangeVisInfo (pOldVI, iVTyp);

			DELETE (pVI);
		}
		DEXD_ObjectNotDrawed3 (ObjNr());
		return VI_OtherType;
	}
	                                
	locSize = pId -> Size (VT_Punkt);
	locC = pId -> GetColor (VT_Punkt);
	_Marker = pId -> Marker();

// PunktSymbolgröße einstellen
CoOrd LogPX = (short)(((long)DotsPerMM.Width() * (long)(locSize.Width())) / (res * M()));
CoOrd LogPY = (short)(((long)DotsPerMM.Height() * (long)(locSize.Height())) / (res * M()));

	LogPX = max (LogPX, 1);		// für Recherche mind. 1 Pixel groß
	LogPY = max (LogPY, 1);

// jetzt testen, ob gezeichnet werden soll
Point BMLoc (OCtoDC (GP())); 		// .X(), GP().Y()));

// long Arithmetik, da sonst bei hohen Auflösungen Überlauffehler entstehen
// Lage überprüfen (in/außerhalb der Clippingarea)
Rectangle rcEA = EA();

	if ((long)LogPX * (long)LogPY < 16L   ||
	    (long)BMLoc.X() + LogPX < (long)rcEA.Left()   || (long)BMLoc.X() - LogPX > (long)rcEA.Right() ||
	    (long)BMLoc.Y() + LogPY < (long)rcEA.Bottom() || (long)BMLoc.Y() - LogPY > (long)rcEA.Top()) 
	{
		SetVisible (false);
		if (pOldVI) {
		VisInfo *pVI = pId -> ChangeVisInfo (pOldVI, VT_Punkt);

			DELETE (pVI);
		}
		DEXD_ObjectNotDrawed4 (ObjNr());
		return NULL;		// nicht zeichnen
	}
	SetVisible();

// Objekt dieses Identifikators wird gezeichnet
	Size() = Dimension (LogPX, LogPY);	// Größe einstellen
	pId -> SetVisible (TPPunkt);
	
	ChangeColor (&locC);	// Farbe in PunktObjekt setzen
	Change2ndColor (pId -> Get2ndColor());
	SetRotation (pId -> Rotation());

	if (_iVisInfoChanged)
		return pOldVI != NULL ? pOldVI : VI_Changed;

return VI_NotChanged;
}


// KantenObjekt (Zeichnen einer Kante) ----------------------------------------
// Konstruktor
KantenObjekt :: KantenObjekt (GeoKante &Kt, pPen pP)
	      : ExtShapeObject (
				OCtoDC (Kt.SP()), // .X(), Kt.SP().Y()),
				Dimension (),
				pP, NULL
		)
{
// GeometrieObjekt setzen
	_pGK = &Kt;
}

void KantenObjekt :: DrawEx (DWORD /*dwData*/) 
{                  // Kante zeichnen
long j = 1;

// Kante zeichnen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HPEN hOldPen;

HPALETTE hOldPalette;
int oldBkMode = TRANSPARENT;

	if (FullDCInit()) {
		if (hPalette != NULL) {
		// Palette einstellen       
			hOldPalette = SelectPalette (hDC, hPalette, false);
			RealizePalette (hDC);
		}
		if (!(FullDCInit() & FDC_PaletteOnly))
			oldBkMode = SetBkMode (hDC, TRANSPARENT);
	}

ExtPen *pEPen = (ExtPen *)GetPen();	// Pen dieses Objektes holen

// Punktweises umrechnen der Koordinaten
Point __huge *lpPoints = new __huge Point[GK().ASP()];
short iLocCnt = pEPen != NULL ? pEPen -> iCnt() : 1;

	if (lpPoints != NULL) {
	// Koordinaten transformieren
		OCtoDC (&(GK().SP()), lpPoints, GK().ASP());
		
//		for (j = 0; j < GK().ASP(); j++) {
//		Punkt &Pkt = GK().SP(j);
//
//			lpPoints[j] = OCtoDC (Pkt); //.X(), Pkt.Y());
//		}

	// alle Linien dieses ExtPens ausgeben
		for (short iCnt = 0; iCnt < iLocCnt; iCnt++) {
		// aktuellen Pen selektieren
			if (pEPen != NULL) 
				hOldPen = (HPEN)SelectObject (hDC, pEPen -> GetHandle(iCnt));

		// Linie zeichnen         
			if (!Polyline (hDC, (POINT *)lpPoints, (int)GK().ASP()))
				DEXD_ObjectNotDrawed5 (ObjNr());

		// DeviceKontext zurücksetzen
			if (pEPen != NULL) SelectObject (hDC, hOldPen);
		}
	// Feld wieder freigeben
//  		DELETE (lpPoints);
		delete [GK().ASP()] (Point __huge *)lpPoints;
	}

	if (FullDCInit()) {
		if (hPalette)
			SelectPalette (hDC, hOldPalette, false);

		if (!(FullDCInit() & FDC_PaletteOnly))
			SetBkMode (hDC, oldBkMode);
		else 
			FullDCInit() &= ~FDC_PaletteOnly;
	}
}


Rectangle EXPORTTRIAS KantenObjekt :: BoundingBox (void) 
{      // KantenContainer
ObjContainer OCont;

	OCont = GK().GetCont ();                // Kantencontainer bestimmen

return (Rectangle (OCtoDC (OCont.XMin(), OCont.YMin()),
		   OCtoDC (OCont.XMax(), OCont.YMax())));
}

void KantenObjekt :: ResetAttributes (void) 
{
	ChangePen (NULL);
}

// Setzen der Zeichenattribute für eine Kante ---------------------------------
VisInfo *KantenObjekt :: SetAttributes (CIdentifikator *pId, Dimension DotsPerMM, 
					CTable &, VisType iVTyp, short fFlags) 
{
// Testen, ob diese Kante überhaupt gezeichnet werden muß
ObjContainer ocT = GK().GetCont();

	SetVisible (false);
	if (!(ExpOC() ^ ocT)) {
		DEXD_ObjectNotDrawed4 (ObjNr());
		return NULL;
	}
	SetVisible();

// Pen aus IdentifikatorTree holen und in KantenObjekt setzen
	if (pId == NULL) return NULL;

	if (iVTyp == VT_Default) iVTyp = VT_Linie;	// visualisieren als

// Objekt mit diesem Id wird gezeichnet
	pId -> SetVisible (TPLinie);

// Parameter im Objekt einstellen
long locWidth;
short _iDrawResult = DO_UnChanged;
short _iVisInfoChanged = false;
VisInfo *pOldVI = NULL;

	switch (pId -> DType() & DT_DrawingMask) {
	case DT_HasNewVI:
	// eine überschlaue Erweiterung hat eine neue VI für uns
//		if (!(FullDCInit() & FDC_ActivateOnly)) {
		{
		// nur beim normalen Zeichnen
		DRAWOBJECT dObj;

			dObj.dwSize = sizeof(DRAWOBJECT);
			dObj.lObjNr = ObjNr();		/// ObjektNummer
			if (pId -> hasVI (iVTyp)) 
				dObj.pNewVI = (VisInfo *)pId -> VI(iVTyp).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = pId -> Id();
			dObj.m_fFlags = fFlags;
			
			if ((_iDrawResult = DEXN_DrawObject (dObj)) & DT_NoDrawing) {
				if (_iDrawResult & DO_ColorChanged)
					FullDCInit() |= FDC_PaletteOnly;
				if (dObj.pNewVI) delete dObj.pNewVI;
				DEXD_ObjectNotDrawed1 (ObjNr());
				return NULL;
			}

			if (fFlags & DF_Blinking) 
				dObj.pNewVI -> Style() = DEF_STYLE;

			if (_iDrawResult & DO_VisInfoChanged) {
				if (!(FullDCInit() & FDC_ActivateOnly) &&
				    _iDrawResult & DO_ColorChanged) {
				// evtl. Farbe, die noch nicht in der Palette existiert
					if (ExpandPalette (hPalette, dObj.pNewVI))
						FullDCInit() |= FDC_PaletteOnly;
				}
				pOldVI = pId -> ChangeVisInfo (dObj.pNewVI, iVTyp);
				_iVisInfoChanged = true;
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			}
		}
		break;

	case DT_Normal:
		break;

	default:
		DEXD_ObjectNotDrawed2 (ObjNr());
		return NULL;
	}
                                                           
// Testen, ob VisInfo gegeben ist
short iVMsk = VisTypeToBits (iVTyp, TPLinie);

	if (!pId -> isCustomized(iVMsk)) 	// Warnung ausgeben
		pId -> ReportVisInfoError (WC_NOVISINFOLINIE, RC_SetAttributesLinie, iVTyp);

// wenn ein anderer ObjektTyp vorgegaukelt werden soll
VisType VT;

	if (pId -> hasVI (iVTyp) && 
	    (VT = pId -> VI (iVTyp).isA()) != VT_Linie && VT != VT_Default) 
	{
		if (pOldVI) {
		VisInfo *pVI = pId -> ChangeVisInfo (pOldVI, iVTyp);

			DELETE (pVI);
		}
		DEXD_ObjectNotDrawed3 (ObjNr());
		return VI_OtherType;
	}

// normales Zeichnen                                                           
	FullDCInit() &= ~FDC_ActivateOnly;

	locWidth = pId -> Width ();

// neuerdings Linienbreite in 1/100 mm
	if (GetGeoDBVersion() >= VERSION05000004)
		locWidth = long( ( (double(locWidth) * double(DotsPerMM.Width())) / (100.0*M()) ) + 0.5);
	else
		locWidth = long(locWidth / M() + 0.5);

// Pen generieren
	ChangePen (pId -> GetPen (VT_Linie, short(locWidth)));

	if (_iVisInfoChanged) 
		return pOldVI != NULL ? pOldVI : VI_Changed;

return VI_NotChanged;
}


// MaschenObjekt (Zeichnen einer Fläche) --------------------------------------
// Konstruktor
MaschenObjekt :: MaschenObjekt (GeoFlaeche &M, pPen pP, pBrush pB)
	       : ExtShapeObject (
			OCtoDC (M.KA().SP()), //.X(), M.KA().SP().Y()),
			Dimension (),
			pP, pB
		 )
{
// GeometrieObjekt setzen
	_pGF = &M;
	m_BkCol = DEF_COLOR;
}

void MaschenObjekt :: DrawEx (DWORD /*dwData*/) 
{
register int i = 0;
//long j;

// Fläche zeichnen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HPALETTE hOldPalette;
int oldBkMode = TRANSPARENT;
int oldFillMode;

	if (FullDCInit()) {
		if (hPalette != NULL) {
		// Palette einstellen       
			hOldPalette = SelectPalette (hDC, hPalette, false);
			RealizePalette (hDC);
		}

		if (!(FullDCInit() & FDC_PaletteOnly)) {
			oldBkMode = :: SetBkMode (hDC, isOpaque() ? OPAQUE : TRANSPARENT);
			oldFillMode = SetPolyFillMode (hDC, ALTERNATE);
		} 
	} else 
		oldBkMode = :: SetBkMode (hDC, isOpaque() ? OPAQUE : TRANSPARENT);

// evtl. neuen Pinsel einstellen
HBRUSH hOldBrush;

	if (GetBrush() != NULL)	{
	HBRUSH hBr = GetBrush() -> Handle();
	
//		UnrealizeObject (hBr);
		hOldBrush = (HBRUSH)SelectObject (hDC, hBr);
	}

// evtl. neuen Stift setzen
HPEN hOldPen;

	if (GetPen() != NULL) hOldPen = (HPEN)SelectObject (hDC, GetPen() -> Handle());

// HinterGrundFarbe setzen
COLORREF crOldBkColor = ::SetBkColor (hDC, (COLORREF &)GetBkColor());
	
// Zeichnen der Fläche
#if !defined(WIN32)
	if (!IsWin31() || GF().KantenAnz() == 1 || GetBrush() == NULL) {
#else
	if (GF().KantenAnz() == 1 || GetBrush() == NULL) {
#endif
	// Nur ein PolygonZug (keine Löcher)
		while (i < GF().KantenAnz()) {
		Kante &tK = GF().KA(i);
		Point __huge *lpPoints = new __huge Point[tK.ASP()];

			if (lpPoints == NULL) break;

		// Punkte transformieren
			OCtoDC (&(tK.SP()), lpPoints, tK.ASP());
			
		// Zeichnen der Fläche
			if (GetBrush() == NULL) {
			// Fläche nicht füllen
				if (!Polyline (hDC, (POINT *)lpPoints, (int)tK.ASP()))
					DEXD_ObjectNotDrawed5 (ObjNr());
			} else {
			// Fläche füllen und nur Außenkontur
				if (!Polygon (hDC, (POINT *)lpPoints, (int)tK.ASP()))
					DEXD_ObjectNotDrawed5 (ObjNr());
			}

		// Feld wieder freigeben
			delete [tK.ASP()] (Point __huge *)lpPoints;
			i++;
		}
	} else {
	// Diese Fläche hat Löcher und muß gefüllt werden
	// nur ab Version 3.1, da PolyPolygon in V3.0 'nen Schuß hat
	Point __huge *lpPoints = new __huge Point[GF().ASP()];
	long cnt = 0;		// zählt alle Stützpunkte durch
	int *pASPs = new int[GF().KantenAnz()];

		if (lpPoints != NULL && pASPs != NULL) {
			while (i < GF().KantenAnz()) {
			// Punktweises umrechnen der Koordinaten
			Kante &tK = GF().KA(i);

				OCtoDC (&(tK.SP()), &lpPoints[cnt], tK.ASP());
				cnt += tK.ASP();
				pASPs[i++] = int(tK.ASP());
			}
		// Fläche füllen
			if (!PolyPolygon (hDC, (POINT *)lpPoints, pASPs, GF().KantenAnz()))
				DEXD_ObjectNotDrawed5 (ObjNr());

		// Feld wieder freigeben
			delete [GF().ASP()] (Point __huge *)lpPoints;
			DELETE (pASPs);
		}
	}

// DeviceKontext zurücksetzen
	::SetBkColor (hDC, crOldBkColor);
	if (GetBrush() != NULL) SelectObject (hDC, hOldBrush);
	if (GetPen() != NULL) SelectObject (hDC, hOldPen);

	if (FullDCInit()) {
		if (hPalette)
			SelectPalette (hDC, hOldPalette, false);

		if (!(FullDCInit() & FDC_PaletteOnly)) {
			:: SetBkMode (hDC, oldBkMode);
			SetPolyFillMode (hDC, oldFillMode);
		} else
			FullDCInit() &= ~FDC_PaletteOnly;
	} else
		:: SetBkMode (hDC, oldBkMode);
}

Rectangle EXPORTTRIAS MaschenObjekt :: BoundingBox (void) 
{
ObjContainer OCont;

	OCont = GF().GetCont ();

return (Rectangle (OCtoDC (OCont.XMin(), OCont.YMin()),
		   OCtoDC (OCont.XMax(), OCont.YMax())));
}

void MaschenObjekt :: ResetAttributes (void)
{
	ChangePen (NULL);
	ChangeBrush (NULL);
}

// Setzen des HintergrundModes für eine Fläche --------------------------------
void MaschenObjekt :: SetBkMode (short isOpaque)
{
	_iMode &= ~BMOpaque;
	if (isOpaque == OPAQUE) _iMode |= BMOpaque;
}

// Setzen des HintergrundModes für eine FlächenKontur -------------------------
void MaschenObjekt :: SetBkConture (bool isBkConture)
{
	_iMode &= ~BMBkConture;
	if (isBkConture) _iMode |= BMBkConture;
}

// Setzen der Zeichenattribute einer MAsche -----------------------------------
VisInfo *MaschenObjekt :: SetAttributes (CIdentifikator *pId, Dimension DotsPerMM, 
					 CTable &, VisType iVTyp, short fFlags) 
{
// Testen, ob diese Fläche überhaupt gezeichnet werden muá
ObjContainer ocT = GF().GetCont();

	SetVisible (false);
	if (!(ExpOC() ^ ocT)) {
		DEXD_ObjectNotDrawed4 (ObjNr());
		return NULL;
	}
	SetVisible();

// Pen aus IdentifikatorTree holen und in MaschenObjekt setzen
	if (pId == NULL) return NULL;

// Visualisierung als
	if (iVTyp == VT_Default) iVTyp = VT_Flaeche;

// Objekt mit diesem Id wird gezeichnet 
	pId -> SetVisible (TPFlaeche);

// Parameter im Objekt einstellen
long locWidth;
short _iDrawResult = DO_UnChanged;
short _iVisInfoChanged = false;
VisInfo *pOldVI = NULL;

	switch (pId -> DType() & DT_DrawingMask) {
	case DT_HasNewVI:
	// eine überschlaue Erweiterung hat eine neue VI für uns
		{
		// nur beim normalen Zeichnen
		DRAWOBJECT dObj;

			dObj.dwSize = sizeof(DRAWOBJECT);
			dObj.lObjNr = ObjNr();		/// ObjektNummer
			if (pId -> hasVI (iVTyp))
				dObj.pNewVI = (VisInfo *)pId -> VI(iVTyp).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = pId -> Id();
			dObj.m_fFlags = fFlags;

			if ((_iDrawResult = DEXN_DrawObject (dObj)) & DT_NoDrawing) {
				if (_iDrawResult & DO_ColorChanged)
					FullDCInit() |= FDC_PaletteOnly;
				if (dObj.pNewVI) delete dObj.pNewVI;
				DEXD_ObjectNotDrawed1 (ObjNr());
				return NULL;
			}

			if (_iDrawResult & DO_VisInfoChanged) {		
				if (!(FullDCInit() & FDC_ActivateOnly) &&
				    _iDrawResult & DO_ColorChanged) 
				{
				// evtl. Farbe, die noch nicht in der Palette existiert
					if (ExpandPalette (hPalette, dObj.pNewVI))
						FullDCInit() |= FDC_PaletteOnly;
				}
				pOldVI = pId -> ChangeVisInfo (dObj.pNewVI, iVTyp);
				_iVisInfoChanged = true;
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			} 
		}
		break;

	case DT_Normal:
	// alles wie gehabt
		break;

	default:
		DEXD_ObjectNotDrawed2 (ObjNr());
		return NULL;
	}

// Testen, ob VisInfo gegeben ist
short iVMsk = VisTypeToBits (iVTyp, TPFlaeche);

	if (!pId -> isCustomized(iVMsk)) 	// Warnung ausgeben
		pId -> ReportVisInfoError (WC_NOVISINFOFLAECHE, RC_SetAttributesFlaeche, iVTyp);

// wenn ein anderer ObjektTyp vorgegaukelt werden soll
VisType VT;

	if (pId -> hasVI (iVTyp) && 
	    (VT = pId -> VI (iVTyp).isA()) != VT_Flaeche && VT != VT_Default) 
	{
		if (pOldVI) {
		VisInfo *pVI = pId -> ChangeVisInfo (pOldVI, iVTyp);

			DELETE (pVI);
		}
		DEXD_ObjectNotDrawed3 (ObjNr());
		return VI_OtherType;
	}

	FullDCInit() &= ~FDC_ActivateOnly;

	locWidth = pId -> FrameWidth ();

// Flächenkontur bei Bedarf verdünnen (skalieren)				
	if (GetGeoDBVersion() >= VERSION05000004) {
	// neuerdings Linienbreite in 1/100 mm
		if (M() > 1.0) 
			locWidth = long( ( (double(locWidth) * double(DotsPerMM.Width())) / (100.0 * M()) ) + 0.5);
		else
			locWidth = long( ( (double(locWidth) * double(DotsPerMM.Width())) / 100.0) + 0.5);
	} else {
		if (M() > 1.0) 
			locWidth = long( (double(locWidth) / M()) + 0.5);
	}

/*	if (GetGeoDBVersion() >= VERSION05000004)
		locWidth = (short)(((long)locWidth * (long)DotsPerMM.Width()) / 100L);

// Flächenkontur bei Bedarf verdünnen (skalieren)				
	if (M() > 1.0) locWidth = (short)(locWidth / M() + 0.5);
*/
// Pen generieren
HDC hDC = (HDC)GetCanvas() -> Handle (API_WINDOW_TARGETHDC/*HDC*/);

	ChangePen (pId -> GetPen (VT_Flaeche, short(locWidth)));
	ChangeBrush (pId -> GetBrush (hDC, pId -> FillMode()));
	SetBkMode (pId -> BKMode (VT_Flaeche));
	SetBkConture (pId -> isBkConture());
	
// HintergrundFarbe setzen
	SetBkColor (pId -> GetBkColor());

	if (_iVisInfoChanged) 
		return pOldVI != NULL ? pOldVI : VI_Changed;

return VI_NotChanged;
}

// ExtShapeObject -- Memberfunktionen -----------------------------------------
// Fenster skalieren
bool DatenBasisObjekt :: Scale (Window *pW, ObjContainer &R, Point &Aspect, Rectangle *pRc) 
{
	Transformation::InitStaticData();		// alles rücksetzen

// KoordinatenTransformation fragen, welcher Aspect zusätzlich notwendig ist
double CTAspect = pCT() -> CoordTransAspectRatio (R);

// AspektRatio setzen
	SetAspectRatio (Aspect, CTAspect);

// wenn kein Rechteck gegeben ist, dann ganzen Canvasbereich nutzen
Rectangle CR;
CoOrd VOrgY;

	if (pRc == NULL) {
		CR = pW -> CanvasRect ();
		VOrgY = CR.Top() - CR.Bottom();
	} else {
		CR = *pRc;
		VOrgY = CR.Top();
	}

	if (CR.Right() <= CR.Left() || CR.Top() <= CR.Bottom())
		return false;

Ausdehnung WExt (R.XMax()-R.XMin(), R.YMin()-R.YMax());
Dimension VExt (CR.Right()-CR.Left(), CR.Bottom()-CR.Top());
Point VOrg (CR.Left(), VOrgY);
Punkt WOrg (R.XMin(), R.YMax());

	SetWindowExt (WExt);
	SetViewportExt (VExt);
	SetViewportOrg (VOrg);
	SetWindowOrg (WOrg);

	Transformation::SetValid (true);		// T-Parameter sind jetzt gültig

return true;
}

// ExtBitmapObject zeichnen (mit WINDOWS-Funktionen) --------------------------
void ExtBitmapObject :: Draw (void) 
{
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HDC hTargetDC = Handle (API_TARGET_HDC);
HBITMAP hBM = bitmap -> Handle (API_BITMAP_HBITMAP); // hBitmap holen

HPALETTE hOldPalette;
int oldBkMode;

	if (FullDCInit()) {
		if (hPalette != NULL) {
		// Palette einstellen       
			hOldPalette = SelectPalette (hDC, hPalette, false);
			RealizePalette (hDC);
		}

		if (!(FullDCInit() & FDC_PaletteOnly)) 
			oldBkMode = SetBkMode (hDC, TRANSPARENT);
	}

// Hintergrundfarbe auf weiß (default setzen)
DWORD oldBkColor = SetBkColor (hDC, 0x00ffffff);
DWORD oldTextColor = SetTextColor (hDC, 0);

// Bitmap darstellen
HDC hMemDC = CreateCompatibleDC (hTargetDC);
HBITMAP hOldBM = (HBITMAP)SelectObject (hMemDC, hBM);

Brush B (_myC, SolidHatch);
HBRUSH hBrush = B.Handle();
HBRUSH hOldBrush = (HBRUSH)SelectObject (hDC, hBrush);

// Größen vor und nach der Projektion bestimmen
Dimension BMdim = bitmap -> GetSize();

//      int Result =
	StretchBlt (hDC,    pt.X()-dim.Width()/2, pt.Y()+dim.Height()/2,
			    dim.Width(), -dim.Height(),
		    hMemDC, 0, 0, 
			    BMdim.Width(), BMdim.Height(),
		    MYROPCODE);

// alte BKColor wieder herstellen
	SetTextColor (hDC, oldTextColor);
	SetBkColor (hDC, oldBkColor);

// alten Zustand wieder herstellen
	SelectObject (hDC, hOldBrush);
	SelectObject (hMemDC, hOldBM);
	DeleteDC (hMemDC);

	if (FullDCInit()) {
		if (hPalette)
			SelectPalette (hDC, hOldPalette, false);

		if (!(FullDCInit() & FDC_PaletteOnly)) 
			:: SetBkMode (hDC, oldBkMode);
		else
			FullDCInit() &= ~FDC_PaletteOnly;
	}
}


void CColorBitmapObject :: DrawEx (DWORD dwData) 
{
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HDC hTargetDC = Handle (API_TARGET_HDC);

// Palette initialisieren
HPALETTE hOldPalette;
int oldBkMode;

	if (FullDCInit()) {
		if (HPALETTE(dwData) != NULL) {
		// Palette einstellen       
			hOldPalette = SelectPalette (hDC, HPALETTE(dwData), false);
			RealizePalette (hDC);
		}

		if (!(FullDCInit() & FDC_PaletteOnly)) 
			oldBkMode = SetBkMode (hDC, TRANSPARENT);
	}

// eigentliches Zeichnen
#if defined(WIN32)
	if (0 != GetRotation())
		DrawWithRotation (hDC, hTargetDC, HPALETTE(dwData));
	else {
		DrawWithOutRotation (hDC, hTargetDC, WhiteMask(), BlackMask(),
				     XOffset(), YOffset(), GetHeight(), GetWidth(),
				     HPALETTE(dwData));
	}
#else
	DrawWithOutRotation (hDC, hTargetDC, WhiteMask(), BlackMask(),
			     XOffset(), YOffset(), GetHeight(), GetWidth(),
			     HPALETTE(dwData));
#endif // WIN32

// Palette wieder aufräumen
	if (FullDCInit()) {
		if ((HPALETTE)dwData)
			SelectPalette (hDC, hOldPalette, false);

		if (!(FullDCInit() & FDC_PaletteOnly))
			SetBkMode (hDC, oldBkMode);
		else
			FullDCInit() &= ~FDC_PaletteOnly;
	}
}

#if defined(WIN32)

const double PI = 2 * asin (1.0);

const long c_lBase = 16384L;

// Drehbare Punkte nur hier (HiHi) --------------------------------------------
void CColorBitmapObject :: DrawWithRotation (HDC hDC, HDC hTargetDC, HPALETTE hPal)
{
// diverse sonstige Initialisierungen
CoOrd iMaskDimX = GetHeight();
CoOrd iMaskDimY = GetWidth();
CoOrd iXOffset = XOffset();
CoOrd iYOffset = YOffset();

// DrehStruktur initialisieren, Erzeugen der gedrehten Masken
GRADIENT gradAngle;

	gradAngle.x = int(cos((-GetRotation()*PI)/1800) * c_lBase);
	gradAngle.y = int(sin((-GetRotation()*PI)/1800) * c_lBase);

// weiße Maske erzeugen
HBITMAP hMask = WhiteMask (hTargetDC, iXOffset, iYOffset, iMaskDimX, iMaskDimY);
HBITMAP hWhite = RotateBitmap (hTargetDC, hMask, gradAngle, c_lBase);

	::DeleteObject ((HGDIOBJ)hMask);		// wird nicht mehr benötigt

	hMask = BlackMask (hTargetDC, iXOffset, iYOffset, iMaskDimX, iMaskDimY);

// schwarze Maske erzeugen
HBITMAP hBlack = RotateBitmap (hTargetDC, hMask, gradAngle, c_lBase, &iMaskDimX, &iMaskDimY);

	::DeleteObject ((HGDIOBJ)hMask);		// wird nicht mehr benötigt

// gewünschte Größe auch drehen
int iX, iY;

	CalcRotatedSize (dim.Width(), dim.Height(), gradAngle, c_lBase, iX, iY);
	dim.Width() = iX;
	dim.Height() = iY;

// gedrehte Masken ausgeben
	DrawWithOutRotation (hDC, hTargetDC, hWhite, hBlack, 
			     0, 0, iMaskDimX, iMaskDimY, hPal);

	::DeleteObject ((HGDIOBJ)hWhite);		// Bitmaps wieder wegräumen
	::DeleteObject ((HGDIOBJ)hBlack);
}

#endif // WIN32

// Das Punktsymbol aus der Gesamtmaske herauskopieren -------------------------
HBITMAP CColorBitmapObject :: CreateSubMask (HDC hDC, HBITMAP hBmp, 
		int iXOffset, int iYOffset, int iMaskDimX, int iMaskDimY, DWORD dwROP)
{
HBITMAP hSubMask = CreateBitmap (iMaskDimX, iMaskDimY, 1, 1, NULL);

	if (NULL == hSubMask) return NULL;

HDC hDCPts = CreateCompatibleDC (hDC);
HBITMAP hOldBM = (HBITMAP)SelectObject (hDCPts, hBmp);	/*BM2S*/

HDC hDCMask = CreateCompatibleDC (hDC);
HBITMAP hOldMask = (HBITMAP)SelectObject (hDCMask, hSubMask);

	BitBlt (hDCMask, 0, 0, iMaskDimX, iMaskDimY, 
		    hDCPts, iXOffset, iYOffset, //iMaskDimX, iMaskDimY, 
		    dwROP);

// aufräumen
	SelectObject (hDCMask, hOldMask);
	DeleteDC (hDCMask);

	SelectObject (hDCPts, hOldBM);
	DeleteDC (hDCPts);

return hSubMask;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe ienes Punktsymboles auf Screen oder anderen hDC
void CColorBitmapObject :: DrawWithOutRotation (
		HDC hDC, HDC hTargetDC, HBITMAP hWhite, HBITMAP hBlack,
		CoOrd iXOffset, CoOrd iYOffset, CoOrd iMaskDimX, CoOrd iMaskDimY,
		HPALETTE hPal)
{
#if defined(WIN32)
bool fOffScreen = PrintEFlag && (GetObjectType (hDC) != OBJ_ENHMETADC) && !IsWinNT();
//		   (GetDeviceCaps (hDC, TECHNOLOGY) == DT_RASDISPLAY));
#else
bool fOffScreen = GetDeviceCaps (hDC, TECHNOLOGY) == DT_RASDISPLAY;
#endif // WIN32

// Zwei s/w Bitmaps, die jeweils den schwarzen und den weißen
// Anteil der Quellbitmap enthalten. mit MYROPCODE und den
// vorgegebenen Farben in den OffScreen-Buffer (bzw. direkt ins ZielDC) kopieren.
HPALETTE hOldDCPal;
int oldStretchMode;
HBITMAP hOldBMos;
CoOrd dimHeight = abs(dim.Height());

// OffScreenBuffer erzeugen und initialisieren.
HDC hDCos = fOffScreen ? CreateCompatibleDC (hTargetDC) : NULL;	/*DC1C*/
DWORD oldBkColor, oldTextColor;

#if !defined(WIN32)
	oldStretchMode = SetStretchBltMode (fOffScreen ? hDCos : hDC, WHITEONBLACK);
#else
	if (isColored()) {
		oldStretchMode = SetStretchBltMode (fOffScreen ? hDCos : hDC, HALFTONE);
		SetBrushOrgEx (hDC, 0, 0, NULL);
	} else 
		oldStretchMode = SetStretchBltMode (fOffScreen ? hDCos : hDC, BLACKONWHITE);
#endif

// diverse sonstige Initialisierungen
CoOrd iSwapHeight = toSwap() ? -dimHeight : dimHeight;

	if (fOffScreen) {
	// Ausgabe über OffScreenBuffer organisieren
		ASSERT(NULL != hDCos);

		if (hPal) 
			hOldDCPal = (HPALETTE)SelectPalette (hDCos, hPal, false);	

	HBITMAP hBmpOS = CreateCompatibleBitmap (hTargetDC, dim.Width(), dimHeight);

		hOldBMos = (HBITMAP)SelectObject (hDCos, hBmpOS);		// BM1C, BM1S
//		StretchBlt (hDCos,	0, 0, dim.Width(), dimHeight, 
//				    hDC, 	pt.X()-dim.Width()/2, pt.Y()+dim.Height()/2,
//				    		dim.Width(), -dim.Height(), SRCCOPY);
		StretchBlt (hDCos,	0, 0, dim.Width(), dimHeight, 
				    hDC, 	pt.X()-dim.Width()/2, pt.Y()+iSwapHeight/2,
				    		dim.Width(), -iSwapHeight, SRCCOPY);

	// Weiße Maske mit Sekundärfarbe/transparent in den os-Buffer kopieren
	HDC hDCSym = CreateCompatibleDC (hTargetDC);		// DC2C
	HBITMAP hOldBM = (HBITMAP)SelectObject (hDCSym, hWhite);	// BM2S
	HBRUSH hBrushCol = CreateSolidBrush ((COLORREF &)m_2ndC);
	HBRUSH hOldBrushCol = (HBRUSH)SelectObject (hDCos, hBrushCol);	// BR1C, BR1S

		StretchBlt (hDCos,	0, 0, dim.Width(), dimHeight,
					hDCSym, iXOffset, iYOffset, iMaskDimX, iMaskDimY, MYROPCODE);

	// Schwarze Maske erzeugen mit PrimärFarbe/transparent in den os-Buffer kopieren
		SelectObject (hDCSym, hBlack);					// BM2S
		::DeleteObject (hBrushCol);						// BR2C, BR2S, BR1U, BR1D

		hBrushCol = CreateSolidBrush ((COLORREF &)m_1stC);
		SelectObject (hDCos, hBrushCol);
		StretchBlt (hDCos,	0, 0, dim.Width(), dimHeight,
					hDCSym,	iXOffset, iYOffset, iMaskDimX, iMaskDimY, MYROPCODE);
		SelectObject (hDCos, hOldBrushCol);
		::DeleteObject (hBrushCol);	// BR2U, BR2D

	// Bitmaps (Masken) wegräumen
		SelectObject (hDCSym, hOldBM);					// BM2U
		DeleteDC (hDCSym);								// DC2D

	// os-Buffer in den Bildschirm zurückkopieren
		StretchBlt (hDC, 	pt.X()-dim.Width()/2, pt.Y()+iSwapHeight/2,
							dim.Width(), -iSwapHeight, 
					hDCos,  0, 0, dim.Width(), dimHeight, SRCCOPY);

	// OffScreen-Stuff aufräumen
		SelectObject (hDCos, hOldBMos);
		::DeleteObject (hBmpOS);		/*BM1U, BM1D*/
		SetStretchBltMode (hDCos, oldStretchMode);
		if (hPal) SelectPalette (hDCos, hOldDCPal, false);	
		DeleteDC (hDCos);								/*DC1D*/

	} else {
	// Weiße Maske mit Sekundärfarbe/transparent in den hDC kopieren
	int iX = pt.X()-dim.Width()/2;
	int iY = pt.Y()+iSwapHeight/2;

#if 0 // ======================================================================
		if (PM_PRINTPSCRIPT1 == g_rgPrintMode) {
#endif // =====================================================================

		HDC hDCSym = CreateCompatibleDC (hTargetDC);		// DC2C
		HBITMAP hOldBM = (HBITMAP)SelectObject (hDCSym, hWhite);	// BM2S
		HBRUSH hBrushCol = CreateSolidBrush ((COLORREF &)m_2ndC);
		HBRUSH hOldBrushCol = (HBRUSH)SelectObject (hDC, hBrushCol);	// BR1C, BR1S

			oldBkColor = SetBkColor (hDC, RGB(0xff, 0xff, 0xff));

			oldTextColor = SetTextColor (hDC, RGB(0, 0, 0)); 
			StretchBlt (hDC,	iX, iY,	dim.Width(), -iSwapHeight,
						hDCSym,	iXOffset, iYOffset, iMaskDimX, iMaskDimY, MYROPCODE);
			SetTextColor (hDC, (COLORREF &)m_2ndC);
			StretchBlt (hDC,	iX, iY,	dim.Width(), -iSwapHeight,
						hDCSym,	iXOffset, iYOffset, iMaskDimX, iMaskDimY, MYROPCODE);

		// Schwarze Maske erzeugen mit PrimärFarbe/transparent in den hDC kopieren
			SelectObject (hDCSym, hBlack);					// BM2S
			::DeleteObject (hBrushCol);	// BR2C, BR2S, BR1U, BR1D

			hBrushCol = CreateSolidBrush ((COLORREF &)m_1stC);
			SelectObject (hDC, hBrushCol);

			SetTextColor (hDC, RGB(0, 0, 0));
			StretchBlt (hDC,	iX, iY,	dim.Width(), -iSwapHeight,
						hDCSym,	iXOffset, iYOffset, iMaskDimX, iMaskDimY, MYROPCODE);
			SetTextColor (hDC, (COLORREF &)m_1stC);
			StretchBlt (hDC,	iX, iY,	dim.Width(), -iSwapHeight,
						hDCSym,	iXOffset, iYOffset, iMaskDimX, iMaskDimY, MYROPCODE);

		// Bitmaps (Masken) wegräumen
			SelectObject (hDCSym, hOldBM);					// BM2U
			DeleteDC (hDCSym);								// DC2D

		// Aufräumarbeiten
			SelectObject (hDC, hOldBrushCol);
			::DeleteObject (hBrushCol);	// BR2U, BR2D
			SetStretchBltMode (hDC, oldStretchMode);
			SetTextColor (hDC, oldTextColor);
			SetBkColor (hDC, oldBkColor);

#if 0 // ======================================================================
		} else {
		HDC hDCSym = CreateCompatibleDC (hTargetDC);		// DC2C
		HBITMAP hOldBM = (HBITMAP)SelectObject (hDCSym, hWhite);	// BM2S

			oldBkColor = SetBkColor (hDC, RGB(0xff, 0xff, 0xff));
			oldTextColor = SetTextColor (hDC, (COLORREF &)m_2ndC); //RGB(0, 0, 0)); 
			StretchBlt (hDC,	iX, iY,	dim.Width(), -iSwapHeight,
						hDCSym,	iXOffset, iYOffset, iMaskDimX, iMaskDimY, SRCERASE);

		// Bitmaps (Masken) wegräumen
			SelectObject (hDCSym, hOldBM);					// BM2U
			DeleteDC (hDCSym);								// DC2D

		// Aufräumarbeiten
			SetStretchBltMode (hDC, oldStretchMode);
			SetTextColor (hDC, oldTextColor);
			SetBkColor (hDC, oldBkColor);
		}
#endif // =====================================================================
	}
}


// Virtuelle Funktionen -------------------------------------------------------
// 1. ObjektNummer liefern
long &PunktObjekt :: ObjNr (void) { return GP().ObjNr(); }
long &KantenObjekt :: ObjNr (void) { return GK().ObjNr(); }
long &MaschenObjekt :: ObjNr (void) { return GF().ObjNr(); }

// 2. Identifikator liefern
long &PunktObjekt :: Id (void) { return GP().Id(); }
long &KantenObjekt :: Id (void) { return GK().Id(); }
long &MaschenObjekt :: Id (void) { return GF().Id(); }

// 3. ObjektTyp liefern
ObjTyp PunktObjekt :: isTyp (void) { return GP().isA(); }
ObjTyp KantenObjekt :: isTyp (void) { return GK().isA(); }
ObjTyp MaschenObjekt :: isTyp (void) { return GF().isA(); }
ObjTyp DatenBasisObjekt :: isTyp (void) { return (ObjTyp) DB().isA(); }

// 4. TypKonvertierung
GeoObjekt *PunktObjekt :: operator -> (void) { return &GP(); }
GeoObjekt *KantenObjekt :: operator -> (void) { return &GK(); }
GeoObjekt *MaschenObjekt :: operator -> (void) { return &GF(); }

PunktObjekt :: operator GeoObjekt * (void) { return &GP(); }
KantenObjekt :: operator GeoObjekt * (void) { return &GK(); }
MaschenObjekt :: operator GeoObjekt * (void) { return &GF(); }

// 5. Destruktoren 
EXPORTTRIAS PunktObjekt :: ~PunktObjekt (void) 
{
	ResetBase ();		// ExtShapeObjekt zurücksetzen
	DELETE (_pGP);
}

EXPORTTRIAS KantenObjekt :: ~KantenObjekt (void) 
{
	ResetBase ();		// ExtShapeObjekt zurücksetzen
	DELETE (_pGK);
}

EXPORTTRIAS MaschenObjekt :: ~MaschenObjekt (void) 
{
	ResetBase ();		// ExtShapeObjekt zurücksetzen
	DELETE (_pGF);
}

// Geometrie modifizieren -----------------------------------------------------
GeoObjekt *PunktObjekt :: NewGI (GeoObjekt *pNewGP) 
{
	if (pNewGP == NULL) return NULL;

GeoObjekt *pOldGP = _pGP;

	_pGP = (GeoPunkt *)pNewGP;

return pOldGP;
}

GeoObjekt *KantenObjekt :: NewGI (GeoObjekt *pNewGK) 
{
	if (pNewGK == NULL) return NULL;

GeoObjekt *pOldGK = _pGK;

	_pGK = (GeoKante *)pNewGK;

return pOldGK;
}

GeoObjekt *MaschenObjekt :: NewGI (GeoObjekt *pNewGF) 
{
	if (pNewGF == NULL) return NULL;

GeoObjekt *pOldGF = _pGF;

	_pGF = (GeoFlaeche *)pNewGF;

return pOldGF;
}


// Generieren einer ClippingRegion, die sich aus dem aktuellen Ausschnitt
// und einem optional gegebenen Objekt zusammensetzt
HRGN DatenBasisObjekt :: CreatePaintRegion (HDC hDC, Rectangle &EA, long ONr) 
{
Rectangle R = GetCanvas() -> CanvasRect();
CoOrd dY = R.Bottom() - R.Top();

#if defined(WIN32)
Rectangle rcClip (-(dY + EA.Top()), EA.Left(), -(dY + EA.Bottom()), EA.Right());
#else
Rectangle rcClip = EA;

	LPtoDP (hDC, (POINT *)&rcClip, 2);
#endif // WIN32	

HRGN hRgn = CreateRectRgnIndirect ((RECT *)&rcClip);

// wenn kein ClippingObjekt gegeben ist, nur Exposed Area verwenden
	if (ONr == -1L) return hRgn;

// ansonsten kombinierte Region erzeugen
// dazu: 1. Objekt besorgen
CTable tabObj (Shapes().ObjNumTree());
GeoObjekt *pGO = NULL;
HRGN hObjRgn;

	if (tabObj.Find (&ONr)) {
	// Objekt ist im Speicher
	ExtShapeObjectLock l(tabObj);

		if (l) 
			pGO = l -> operator GeoObjekt *();
		else 	
			return hRgn;	// Fehler

	// Region aus ObjektGeometrie machen
		hObjRgn = CreateObjectRegion (pGO, dY);
	} else {
	// Objekt ist nicht geladen
		if (DB().GetGI (ONr, &pGO) != EC_OKAY)
			return hRgn;

		if (pGO == NULL) return hRgn;

	// Region aus ObjektGeometrie machen
		hObjRgn = CreateObjectRegion (pGO, dY);

	// Speicher für Geometrie wieder freigeben
		switch (pGO -> isA()) {
		case OT_PUNKT:		delete (GeoPunkt *)pGO; break;
		case OT_KANTE: 		delete (GeoKante *)pGO; break;
		case OT_FLAECHE:	delete (GeoFlaeche *)pGO; break;
		case OT_KREIS:		delete (GeoKreis *)pGO; break;
		case OT_LABEL:
		case OT_TEXT:		delete (BasicGeoText *)pGO; break;
		case OT_KO:		delete (KomplexObjekt *)pGO; break;
		case OT_UNKNOWN:
		default:		break;
		}
	}
	if (hObjRgn == 0) 	// Fehler oder keine Fläche
		return hRgn;

HRGN hPaintRegion = CreateRectRgn (0, 0, 0, 0);	// leere Region als Ziel
int Result = CombineRgn (hPaintRegion, hObjRgn, hRgn, RGN_AND);
	
	::DeleteObject (hObjRgn);
	::DeleteObject (hRgn);

return hPaintRegion;
}


HRGN CreateObjectRegion (GeoObjekt *pGO, CoOrd dY) 
{
// wenn es keine Fläche ist, dann sofort wieder raus
	if (pGO -> isA() != OT_FLAECHE)	return 0;

// ansonsten Region bilden
HRGN hRgn;
GeoFlaeche *pGF = (GeoFlaeche *)pGO;	// zu bearbeitende GeoFlaeche
register int i = 0;
long j = 0;

	if (pGF -> KantenAnz() == 1) {
	// Nur ein PolygonZug (keine Löcher)
	Kante &tK = pGF -> KA(0);
	Point *lpPoints = new Point[tK.ASP()];

		if (lpPoints == NULL) return 0;

	// Punkte transformieren
		for (j = 0; j < tK.ASP(); j++) {
			lpPoints[j] = OCtoDC (tK.SP(j)); //.X(), tK.SP(j).Y());
			lpPoints[j].Y() = -(dY + lpPoints[j].Y());
		}
		hRgn = CreatePolygonRgn ((POINT *)lpPoints, (int)tK.ASP(), ALTERNATE);

		DELETE (lpPoints);	// Feld freigeben
	} else {
	// Fläche mit Löchern
	Point *lpPoints = new Point[pGF -> ASP()];
	short cnt = 0;		// zählt alle Stützpunkte durch
	int *ASPs = new int[pGF -> KantenAnz()];

		if (lpPoints != NULL && ASPs != NULL) {
			while (i < pGF -> KantenAnz()) {
			// Punktweises umrechnen der Koordinaten
			Kante &tK = pGF -> KA(i);

				for (j = 0; j < tK.ASP(); j++, cnt++) {
					lpPoints[cnt] = OCtoDC (tK.SP(j)); // .X(), tK.SP(j).Y());
					lpPoints[cnt].Y() = -(dY + lpPoints[cnt].Y());
				}
				ASPs[i] = int(j);
				i++;
			}
			hRgn = CreatePolyPolygonRgn ((POINT *)lpPoints, ASPs, pGF -> KantenAnz(), ALTERNATE);

		// Feld wieder freigeben
			DELETE (lpPoints);
			DELETE (ASPs);
		} else {
			DELETE (lpPoints);
			return 0;
		}
	}

return hRgn;
}

// ----------------------------------------------------------------------------
// Typabhängige Visualisierung ------------------------------------------------
// Zeichnen eines Objektes entsprechend VisInfoTyp und ObjektTyp --------------
void PunktObjekt :: TypeDependendDraw (CIdentifikator *pId, CTable &, Dimension)
{                      
	if (!pId -> hasVI(VT_Punkt)) 
		return;	// keine VisInfo, kein Zeichnen

	switch (pId -> PVI().isA()) {
	case VT_Linie:
	case VT_Flaeche:
		break;

	case VT_Punkt:	// kommt nicht vor
	case VT_Default:
	case VT_Text:	// Punkt als TextObjekt zeichnen
	default:	// sinnlos, DefaultPunkt zeichnen
		GetCanvas() -> Draw (this);	// normal zeichnen
		break;
	}
}

/*		
	case OT_TEXT:
		switch (VT) {
		case VisInfo :: VT_Punkt:
		case VisInfo :: VT_Linie:
		case VisInfo :: VT_Flaeche:
			break;
			
		case VisInfo :: VT_Default:
		case VisInfo :: VT_Text:		// kommt nicht vor
			CurrActW -> Draw (pESO);	// normal zeichnen
			break;
			
		default:
			break;
		}
		return;
		
	case OT_KREIS:
	case OT_KO:
		CurrActW -> Draw (pESO);	// normal zeichnen
		return;
		
	case OT_UNKNOWN:
	default:
		return;		// kann nichts zeichnen
	}
}
*/

void MaschenObjekt :: TypeDependendDraw (CIdentifikator *pId, CTable &tabONr, 
					 Dimension DotsPerMM)
{                      
	if (!pId -> hasVI (VT_Flaeche)) 
		return;	// keine VisInfo, kein Zeichnen

	switch (pId -> FVI().isA()) {	// Typ der VisInfo
	case VT_Punkt:	// FlächenSchwerpunkt zeichnen
		{                                                                         
		// Flächenschwerpunkt berechnen
		Punkt Pt;
		GeoFlaeche *pGO = (GeoFlaeche *)(operator GeoObjekt *());
			
			pGO -> SchwerPunkt (Pt);

		// neues PunktObjekt bilden 
		GeoPunkt *pGP = new GeoPunkt (pGO->DB(), pGO -> ObjNr(), pId -> Id(), Pt);
		PunktObjekt PO (*pGP);
		VisInfo *pVI = PO.SetAttributes (pId, DotsPerMM, tabONr, VT_Flaeche);
			
			GetCanvas() -> Draw (&PO);		// FlächenSchwerpunkt zeichnen
			if (pVI != VI_NotChanged) {
				pVI = pId -> ChangeVisInfo (pVI, VT_Flaeche);
				DELETE (pVI);
			}
		}
		break;
			
	case VT_Linie:
		break;
			
	case VT_Flaeche:		// kommt nicht vor
	case VT_Default:
		GetCanvas() -> Draw (this);	// normal zeichnen
		break;
			
	case VT_Text:	// Text an FlächenSchwerpunkt zeichnen
	default:
		break;
	}
}


