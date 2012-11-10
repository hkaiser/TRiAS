// Memberfunktionen fuer SchriftObjekte
// File: SCHRIFT.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>
#include <xtensnd.h>
#include <funcs03.h>

#include "schrift.hxx"

extern bool DrawTextObjs;
extern bool PrintEFlag;
extern bool GenerateLegendOnly;
extern bool g_fPosTextAtBaseLine;

extern HPALETTE hPalette;

_TRIAS02_ENTRY bool EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);

// Konstruktor ----------------------------------------------------------------
SchriftObjekt :: SchriftObjekt (BasicGeoText &GT) 
	       : ExtShapeObject (OCtoDC (GT.X(), GT.Y()),
				 GT.Size(), NULL, NULL)
{
// GeometrieObjekt anhängen
	_pGT = &GT;

// Größe ist erst mal Null
	_Box = Rectangle (0, 0, 0, 0);

// alles andere initialisieren
	_fStyles = SO_Transparent;

	m_iEscapement = 0;
}

// Destruktor -----------------------------------------------------------------
EXPORTTRIAS SchriftObjekt :: ~SchriftObjekt (void) 
{
	ResetBase();	// ExtShapeObjekt zurücksetzen
	DELETE (_pGT);
}

void SchriftObjekt :: ResetAttributes (void)
{
	ChangeFont (NULL);
}


// Routine, die ZeichenAttribute einstellt ------------------------------------
VisInfo *SchriftObjekt :: SetAttributes (CIdentifikator *pId, Dimension DotsPerMM, 
					 CTable &, VisType, short fFlags) 
{
// Korrdinaten setzen
	pt = OCtoDC (GT().X(), GT().Y());

// VisAttribs setzen
	if (pId == NULL) return NULL;

// Farbe aus Identifikator holen und in SchriftObjekt setzen
Color locC = Color ((Colors)0, (Colors)0, (Colors)0);
Dimension locSize (0, 0);
int locBKMode;
int locFrameMode;
int locRoundFrame;

VisInfo *pOldVI = NULL;
DRAWSTATUS rgVisInfoChanged = DRAWSTATUS_VisInfoNotChanged;

	switch (pId -> DType() & DT_DrawingMask) {
	case DT_HasNewVI:
	// eine überschlaue Erweiterung hat eine neue VI für uns
		rgVisInfoChanged = SpecialEffects (ObjNr(), VT_Text, pId, fFlags, &pOldVI);
		if (DRAWSTATUS_NoDrawing == rgVisInfoChanged)
			return NULL;
		break;

	case DT_Normal:
	// alles wie gehabt
		{
		CoOrd dX = pId -> Size(VT_Text).Height();

			if (PrintEFlag && (abs(dX) / M()) < 4) {
			// Schriften kleiner 4Pt werden am Bildschirm ignoriert, 
			// wenn Größe gegeben ist
				DEXD_ObjectNotDrawed4 (ObjNr());
				return NULL;
			}
		}
		break;

	default:
		DEXD_ObjectNotDrawed2 (ObjNr());
		return NULL;
	}

	FullDCInit() &= ~FDC_ActivateOnly;

// Testen, ob VisInfo gegeben ist
	if (!pId -> isCustomized(TPText)) 	// Warnung ausgeben
		pId -> ReportVisInfoError (WC_NOVISINFOTEXT, RC_SetAttributesText, VT_Text);

	locSize = pId -> Size(VT_Text);
	locC = pId -> GetColor (VT_Text);
	locBKMode = pId -> BKMode (VT_Text);
	locFrameMode = pId -> FrameMode();
	locRoundFrame = pId -> RoundFrame();
		
	ChangeColor (&locC);

// Fontgröße berechnen
double dDelta = (locSize.Height() > 0) ? 0.5 : -0.5;
CoOrd PtX = (CoOrd)(((double)DotsPerMM.Width() * (double)(locSize.Width()) * 0.3176) / M() + dDelta);
CoOrd PtY = (CoOrd)(((double)DotsPerMM.Height() * (double)(locSize.Height()) * 0.3176) / M() + dDelta);
Dimension FontSize (PtX, PtY);

// Font holen 
	ChangeFont (pId -> GetFont (FontSize));

// Ausrichtung setzen
	ChangeMode (locBKMode);
	ChangeFrame (locFrameMode);
	RoundFrame (locRoundFrame);
	
	SetAlignStyle (pId -> AlignStyle());
 	SetEscapement (pId -> Escapement());
 	
// Speicher wieder freigeben
	if (DRAWSTATUS_VisInfoChanged == rgVisInfoChanged) 
		return pOldVI != NULL ? pOldVI : VI_Changed;

	return VI_NotChanged;	// erstmal immer zeichnen
}

// alle Spaces als nicht umzubrechen kennzeichnen -----------------------------
#pragma warning (disable:4309)		// truncation of constant value

static char *ReplaceSpaces (char *pText)
{
	if (pText == NULL) return NULL;
	
char *pT = new char [strlen(pText) +1];
char *pReturn = pT;

	if (pT == NULL) return NULL;
	while (*pText) {
		if (*pText == ' ') {
			*pT++ = char (' ' | 0x80);
			pText++;
		} else
			*pT++ = *pText++;
	}
	*pT = '\0';
	
return pReturn;
}

#pragma warning (default:4309)	

// Routine, die SchriftObjekte zeichnet ---------------------------------------
void SchriftObjekt :: DrawEx (DWORD dwData) 
{
// wenn keine Textobjekte gemalt werden sollen, dann weiter
	if (!DrawTextObjs) return;

char *pText = (&GT()) -> Text();

	if (pText == NULL) {
		DEXD_ObjectNotDrawed5 (ObjNr());
		return;		// kein Text da
	}

// Text ausgeben
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HDC hTargetDC = Handle (API_TARGET_HDC);

// bestimmen der realen Textgröße am Bildschirm
	if (_pF) _pF -> Init();		// Font bilden

HFONT hFontT = _pF ? _pF -> Handle(API_FONT_HFONT) : (HFONT)GetStockObject (ANSI_VAR_FONT);
LOGFONT *pLF = NULL;

	if (NULL != _pF && _pF -> GetLogFont (&pLF) && NULL != pLF) {
	// Testen, ob der Text von seiner Größe her überhaupt angezeigt werden soll
		if (0 == pLF -> lfHeight && 0 == pLF -> lfWidth) {
			SetVisible (false);
			DEXD_ObjectNotDrawed4 (ObjNr());
			return;	// nicht zeichnen
		}
	}

HFONT hFont = (HFONT)SelectObject (hDC, hFontT);
HFONT hTFont = 0;

	if (hDC != hTargetDC)
		hTFont = (HFONT)SelectObject (hTargetDC, hFontT);
		
AlignType nAlign = ATLeft;

	_Box.Right() = _Box.Left() = pt.X();
	_Box.Bottom() = _Box.Top() = pt.Y();
	
DatenBasisObjekt *pDBO = (DatenBasisObjekt *)dwData;
bool fPosTextAtBaseLine = (NULL != pDBO) ? pDBO -> PosTextAtBaseLine() : false;
Point ptReal = pt;
TEXTMETRIC TM;

	GetTextMetrics (hTargetDC, &TM);
	if (fPosTextAtBaseLine) {
//		ptReal.Y() -= TM.tmDescent/2;
		nAlign = (AlignType)(nAlign | ATBaseLine);
	}

CoOrd dY = 0;
char *pTmp = NULL;

	if (GetEscapement()) {
		pTmp = ReplaceSpaces (pText);
		dY = Justify (hDC, hTargetDC, pTmp ? pTmp : pText, (POINT *)&ptReal, 
		    (RECT *)&_Box, nAlign, false);
	} else {
		dY = Justify (hDC, hTargetDC, pText, (POINT *)&ptReal, 
		    (RECT *)&_Box, nAlign, false);
	}

	if (dY == -1) {
		SelectObject (hDC, hFont);
		if (hDC != hTargetDC)
			SelectObject (hTargetDC, hTFont);
		DEXD_ObjectNotDrawed5 (ObjNr());
		DELETE (pTmp);
		return;			// kein Text gegeben
	}
	
// wenn Zentrierung geändert werden soll, dann dieses hier tun
short ddX = TM.tmAveCharWidth / 4;

	_Box.Left() -= ddX;
	_Box.Right() += ddX;
	
CoOrd dX = _Box.Right()-_Box.Left();

// alles eine Etage nach oben rücken
//	_Box.Bottom() -= dY;
	_Box.Top() += dY;

	if (_fStyles & SO_Centred) {
	CoOrd dX2 = (dX-ddX)/2;
	CoOrd dY2 = (dY+TM.tmDescent)/2;
		
		_Box.Right() -= dX2;
		_Box.Left() -= dX2;
// JG keine vertikale Zentrierung mehr
//		_Box.Top() -= dY2;	// auch vertikal zentrieren
//		_Box.Bottom() -= dY2;

//		ptReal.Y() -= dY2;

		nAlign = ATCentre;	// zentrieren

	} else if (_fStyles & SO_RightAlign) {
		_Box.Right() -= dX;
		_Box.Left() -= dX;

		nAlign = ATRight;	// rechtsbündig
	} else if (_fStyles & SO_Justified) 
		nAlign = ATJust;	// Blocksatz

// Drehwinkel einarbeiten
Point Pts[4];
Point ptRot = ptReal;

	if (fPosTextAtBaseLine && ATCentre != nAlign) {
		ptRot.Y() += TM.tmDescent/2;
		nAlign = (AlignType)(nAlign | ATBaseLine);
	}
	RotateRect (Pts, ptRot, _Box, GetEscapement(), _fStyles & SO_AlignStyle);

// Wenn dieses Textobjekt innerhalb des aktuellen Bildschirmbereiches liegt,
// dann SichtbarkeitsFlag setzen
Rectangle rcC = GetCanvas() -> CanvasRect();

	if (_Box.Right() < rcC.Left() || _Box.Left() > rcC.Right() ||
	    _Box.Top() < rcC.Bottom() || _Box.Bottom() > rcC.Top()) 
		SetVisible (false);
	else
		SetVisible (true);

// wenn dieses Textobjekt außerhalb der ClippingArea liegt, dann wieder raus
Rectangle rcEA = EA();

	if (GenerateLegendOnly || 	// nur Sichtbarkeit testen
	    _Box.Right() < rcEA.Left() || _Box.Left() > rcEA.Right() ||
	    _Box.Top() < rcEA.Bottom() || _Box.Bottom() > rcEA.Top()) 
	{
		SelectObject (hDC, hFont);
		if (hDC != hTargetDC)
			SelectObject (hTargetDC, hTFont);
		DEXD_ObjectNotDrawed4 (ObjNr());
		DELETE (pTmp);
		return;	// nicht zeichnen
	}
	
// wenn Rahmen gezeichnet werden soll, dann dieses jetzt tun
int oldBkMode;
HPALETTE hOldPalette;

	if (FullDCInit()) {
		if (hPalette != NULL) {
		// Palette einstellen       
			hOldPalette = SelectPalette (hDC, hPalette, false);
			RealizePalette (hDC);
		}
		FullDCInit() &= ~FDC_PaletteOnly;
	}

	if (_fStyles & SO_hasBox) {	
	long AssocON = AssociatedObjekt (GT().DB().DBDesc(), ObjNr());
	COLORREF _C;

		if (!(_fStyles & SO_Transparent) || AssocON == 0) 
			_C = RGB (255, 255, 255);
		else {
		// Farbe des Rechtecks von Bezugsobjekt holen
			_C = DEX_GetObjColor (labs(AssocON));
			if (hPalette)
				_C = PALETTEINDEX (GetNearestPaletteIndex (hPalette, _C));
		}

	HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, CreateSolidBrush (_C));

		oldBkMode = SetBkMode (hDC, OPAQUE);
		if (_fStyles & SO_RoundFrame) {
		short iD = 2*ddX;
		
			RoundRect (hDC, _Box.Left()-iD, _Box.Top()+iD, 
					_Box.Right()+iD, _Box.Bottom()-iD,
					4*iD, 4*iD);
		} else
			Polygon (hDC, (LPPOINT)Pts, 4);		// Rahmen zeichnen

		DeleteObject (SelectObject (hDC, hOldBr));
		SetBkMode (hDC, oldBkMode);
	}

// Schreiben des Textes ins aktuelle Fenster
COLORREF oC = SetTextColor (hDC, *(COLORREF *)&_C);

	oldBkMode = SetBkMode (hDC, TRANSPARENT);	// Text auf jeden Fall Transparent
	
// Text ausgeben
	_Box.Left() += ddX;

// Gedrehte Texte mit Leerzeichen werden zuweilen umgebrochen, da in Justify
// die Drehung nicht in betracht gezogen werden kann (GetTextExtentPoint ...)
// Daher werden einfach alle Spaces als ' ' | 0x80 ausgegeben
	Justify (hDC, hTargetDC, pTmp ? pTmp : pText, (POINT *)&ptReal, 
		 (RECT *)&_Box, nAlign, true, NULL, GetEscapement());
	DELETE (pTmp);

	_Box.Left() -= ddX;			// für Clipping wieder rücksetzen
	
	SetBkMode (hDC, oldBkMode);
	SetTextColor (hDC, oC);
	SelectObject (hDC, hFont);
	if (hDC != hTargetDC)
		SelectObject (hTargetDC, hTFont);

	if (FullDCInit() && hPalette)
		SelectPalette (hDC, hOldPalette, false);
}

// Aus der Position des Umschließenden Rechtecks und dem BezugsMode die Punkt-
// Koordinate berechnen
void SchriftObjekt :: CorrectPosition (Point &Pt)
{
	Pt.X() += (pt.X() - _Box.Left()) -1;
	Pt.Y() += (pt.Y() - _Box.Bottom()) -1;

//CoOrd dX = _Box.Right()-_Box.Left();
//CoOrd dY = _Box.Top() - _Box.Bottom();

//	if (_fStyles & SO_Centred) 		{ Pt.X() += dX/2; Pt.Y() += dY/2; }
//	else if (_fStyles & SO_RightAlign)	Pt.X() -= dX;
}

// Routinen, die ZeichenAttribute der Schrift ändern --------------------------
Color SchriftObjekt :: ChangeColor (Color *pC) 
{
Color oldColor = _C;

	_C = *pC;

return oldColor;
}

pFont SchriftObjekt :: ChangeFont (pFont pF) 
{
pFont pOldFont = _pF;

	_pF = pF;

return pOldFont;
}

bool SchriftObjekt :: ChangeMode (bool newBKMode) 
{
bool oldBKMode = (bool)(_fStyles & SO_Transparent);

	_fStyles &= ~SO_Transparent;
	if (newBKMode & TV_BKMode)
		_fStyles |= SO_Transparent;

return oldBKMode;
}

bool SchriftObjekt :: ChangeFrame (bool newFrameMode) 
{
bool oldFrameMode = (bool)((_fStyles & SO_hasBox) ? TV_Frame : 0);

	_fStyles &= ~SO_hasBox;
	if (newFrameMode & TV_Frame)
		_fStyles |= SO_hasBox;

return oldFrameMode;
}


bool SchriftObjekt :: RoundFrame (bool newRoundFrame) 
{
bool oldRoundFrame = (bool)((_fStyles & SO_RoundFrame) ? TV_RoundFrame : 0);

	_fStyles &= ~SO_RoundFrame;
	if (newRoundFrame)
		_fStyles |= SO_RoundFrame;

return oldRoundFrame;
}

short SchriftObjekt :: SetAlignStyle (short newAlignStyle)
{
short oldAlignStyle = (_fStyles & SO_AlignStyle) << 6;

	_fStyles &= ~SO_AlignStyle;
	_fStyles |= (newAlignStyle & TV_AlignStyle) >> 6;

return oldAlignStyle;
}


void SchriftObjekt :: SetEscapement (short newEscape)
{
	m_iEscapement = newEscape; 
}


// Austauschen des Textes im GeoText ------------------------------------------
char *SchriftObjekt :: ChangeText (char *newText) 
{
	return (&GT()) -> ChangeText(newText);
}


// sonstige virtuelle Funktionen ----------------------------------------------
SchriftObjekt :: operator GeoObjekt * (void) { return &GT(); }
GeoObjekt *SchriftObjekt :: operator -> (void) { return &GT(); }
ObjTyp SchriftObjekt :: isTyp (void) { return GT().isA(); }
long &SchriftObjekt :: Id (void) { return GT().Id(); }
long &SchriftObjekt :: ObjNr (void) { return GT().ObjNr(); }

GeoObjekt * EXPORTTRIAS SchriftObjekt :: NewGI (GeoObjekt *pNewGT) 
{
	if (pNewGT == NULL) return NULL;

GeoObjekt *pOldGT = _pGT;

	_pGT = (BasicGeoText *)pNewGT;

// ShapeObject verschieben
	ChangePosition (OCtoDC (((BasicGeoText *)_pGT) -> X(), 
				((BasicGeoText *)_pGT) -> Y()));

return pOldGT;
}


// Drehen eines Rechteckes, berechnen des neuen umschließenden Rechtecks ------
inline void RotatePoint (Point &ptRes, CoOrd x, CoOrd y, Point &ptRot, 
			 double dSin, double dCos)
{
	ptRes.X() = (CoOrd)( (x - ptRot.X()) * dCos + (y - ptRot.Y()) * dSin + ptRot.X() + 0.5);
	ptRes.Y() = (CoOrd)(-(x - ptRot.X()) * dSin + (y - ptRot.Y()) * dCos + ptRot.Y() + 0.5);
}

const double PI = 2 * asin (1.0);

void RotateRect (Point *pPts, Point &pt,  Rectangle &Rc, short iEsc, short iStyle)
{
Point ptRot (pt);

	if (iStyle & SO_Centred) 
		ptRot.X() = (Rc.Left() + Rc.Right())/2;
	else if (iStyle & SO_RightAlign)
		ptRot.X() = Rc.Right();
		
double dPhi = (iEsc * PI)/1800;
double dSinE = sin (dPhi);
double dCosE = cos (dPhi);

	RotatePoint (pPts[0], Rc.Left(), Rc.Bottom(), ptRot, dSinE, dCosE);
	RotatePoint (pPts[1], Rc.Left(), Rc.Top(), ptRot, dSinE, dCosE);
	RotatePoint (pPts[2], Rc.Right(), Rc.Top(), ptRot, dSinE, dCosE);
	RotatePoint (pPts[3], Rc.Right(), Rc.Bottom(), ptRot, dSinE, dCosE);
	
// neues umschließendes Rechteck berechnen
	Rc.Left() = Rc.Right() = pPts[0].X();
	Rc.Bottom() = Rc.Top() = pPts[0].Y();
	
	for (short i = 1; i < 4; i++) {
	Point *pPt = &pPts[i];
	
		if (pPt -> X() < Rc.Left()) Rc.Left() = pPt -> X();
		if (pPt -> X() > Rc.Right()) Rc.Right() = pPt -> X();
		if (pPt -> Y() < Rc.Bottom()) Rc.Bottom() = pPt -> Y();
		if (pPt -> Y() > Rc.Top()) Rc.Top() = pPt -> Y();
	}
}


