// Memberfuntktionen fuer die Legende -----------------------------------------
// File: LEGENDE.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>
#include <funcs03.h>

#include "triasres.h"
#include "clbmpobj.hxx"

#include "legdinfo.hxx"
#include "legdinfo.inl"
#include "prlayout.hxx"
#include "legende.hxx"

#include "legmerkm.hxx"		// lexer/parser

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MYROPCODE 		0x00b8074a

extern HPALETTE hPalette;

_TRIAS02_ENTRY BOOL EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);

///////////////////////////////////////////////////////////////////////////////
// 
#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

// Einträge der Legende -------------------------------------------------------
CLegendeItem::CLegendeItem (pWindow pW, DatenBasisObjekt &rDBO, CIdentifikator &rId, 
			      VisType iVTyp, Point Pt, Dimension Dim, 
			      Dimension DotsPerMM, bool fShown, 
			      char *pText, long lONr, CLegSizeCache &rCache,
			      short iTextX, bool fScaleMode) 
	      : DrawObject (Pt), m_ID (rId), m_rDBO (rDBO), m_rCache(rCache)
{
	m_Dim = Dim;
	ChangeSize (m_Dim);
	m_pW = pW;			// FensterHandle merken
	m_DotsPerMM = DotsPerMM;	// Scaling merken
	m_iVTyp = iVTyp;
	m_fShown = fShown;
	m_fScaleMode = fScaleMode;
	m_pText = NULL;			// für alle Fälle
	if (pText) 
		m_pText = StrDupF (pText);
	m_lONr = lONr;
		
// Größe der beiden Bereiche berechnen
	m_Pt = Pt;
	if (iTextX == 0) {
	long lWidth = m_rCache.KastenBreite (MulDiv(Dim.Width(), 4000, 25000));
	long lMiddle = m_rCache.KastenZwischenBreite (2*m_DotsPerMM.Width());

		m_TextX = (CoOrd)(Pt.X() + lWidth + lMiddle);
	} else
		m_TextX = Pt.X() + iTextX;
}

CLegendeItem::~CLegendeItem (void) 
{
	DELETE (m_pText);
}	

// Zeichnen eines LegendenEintrages -------------------------------------------
void CLegendeItem::Draw (void) 
{
// BereichsGröße berechnen
long lWidth = m_rCache.KastenZwischenBreite (2*m_DotsPerMM.Width());
Dimension dimSign ((CoOrd)(m_TextX - m_Pt.X() - lWidth), m_Dim.Height());

// entsprechend Typ zeichnen
	switch (m_iVTyp) {
	case VT_Punkt:
		LDrawPunkt (dimSign);
		break;

	case VT_Linie:
		LDrawLinie (dimSign);
		break;

	case VT_Flaeche:
		dimSign.Height() = MulDiv(dimSign.Height(), m_rCache.KastenHoehe(100), 100L);
		LDrawFlaeche (dimSign);
		break;

	case VT_Text:		// nur für Einzelobjekte
		if (LDrawText (dimSign)) 
			LDrawDescText (dimSign);
		return;
			
	case VT_Default:
		LDrawFlaeche (dimSign);
		break;

	default:
		break;
	}

// Text dazumalen
	LDrawDescText (dimSign);
}

HRGN CLegendeItem::SelectClipRegion (HDC hDC, Dimension &rDim)
{
// bisherige ClipRgn besorgen
HRGN hClipRgn = CreateRectRgn (0, 0, 0, 0);

	if (0 == GetClipRgn (hDC, hClipRgn)) {
		DeleteObject (hClipRgn);
		hClipRgn = NULL;
	}

// neue ClipRgn generieren, Y-Coord kippen
//Rectangle rc = m_pW -> CanvasRect();
//Point pt = m_Pt;
//
//	pt.Y() = rc.Height() - pt.Y() -1;

Rectangle rc(m_Pt.Y(), m_Pt.X(), m_Pt.Y()-rDim.Height(), m_Pt.X()+rDim.Width());

	LPtoDP(hDC, (LPPOINT)&rc, 2);

HRGN hRgn = CreateRectRgn (rc.Left(), rc.Top(), rc.Right(), rc.Bottom());

	if (NULL == hRgn) return hClipRgn;

HRGN hNewRgn = NULL;

	if (NULL != hClipRgn) {
	HRGN hNewRgn = ::CreateRectRgn (0, 0, 0, 0);

		::CombineRgn (hNewRgn, hRgn, hClipRgn, RGN_AND);

	// neue ClipRgn jetzt selektieren
		::SelectClipRgn (hDC, hNewRgn);
		::DeleteObject (hNewRgn);
		::DeleteObject (hRgn);
	} else {
		::SelectClipRgn (hDC, hRgn);
		::DeleteObject (hRgn);
	}
	
	return hClipRgn;	// liefer bisherige ClipRgn
}

// Zeichnen eines PunktSymboles in der Legende --------------------------------
void CLegendeItem::LDrawPunkt (Dimension &Dim) 
{
// wenn ein Objekt gezeichnet werden soll, dann hier in die Runde rufen
short iDrawResult = DO_UnChanged;
VisInfo *pOldVI = NULL;

	if (m_lONr != -1) switch (m_ID.DType() & DT_DrawingMask) {
	case DT_HasNewVI:	// eine überschlaue Erweiterung hat eine neue VI für uns
		{		// nur beim normalen Zeichnen
		DRAWOBJECTEX dObj;

			INITSTRUCT(dObj, DRAWOBJECTEX);
			dObj.lObjNr = m_lONr;		// ObjektNummer
			if (m_ID.hasVI (VT_Punkt))
				dObj.pNewVI = (VisInfo *)m_ID.VI(VT_Punkt).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = m_ID.Id();
			dObj.m_fFlags = DF_Analyze;

			DEXN_DrawObjectEx (dObj);
			if ((iDrawResult = (short)dObj.m_lResult) & DT_NoDrawing) {
				if (dObj.pNewVI) delete dObj.pNewVI;
				return;		// nicht zeichnen
			}

			if (iDrawResult & DO_VisInfoChanged) {
//				if (hPalette && iDrawResult & DO_ColorChanged)
				// evtl. Farbe, die noch nicht in der Palette existiert
//					ExpandPalette (hPalette, dObj.pNewVI);
				pOldVI = m_ID.ChangeVisInfo (dObj.pNewVI, VT_Punkt);
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			}
		}
		break;

	case DT_Normal:		// alles wie gehabt
		break;

	default:		// irgend was falsch
		return;
	}

// MittelPunktsKoordinaten des PunktSymboles bestimmen
Point Centre (m_Pt.X()+Dim.Width()/2, m_Pt.Y()-Dim.Height()/2);
Dimension PtSize = ((PVisInfo *)(&m_ID.VI(m_iVTyp))) -> Size();
#if defined(_FORCE_LEGACY_CODE)
double res = (DBO().DB().GetDBVersion() >= VERSION05000004) ? 100L : 10L;
#else
double res = 100;
#endif // defined(_FORCE_LEGACY_CODE)

	if (GetScaleMode())	res *= DBO().M();

CoOrd logPX = MulDiv(m_DotsPerMM.Width(), PtSize.Width(), res);
CoOrd logPY = MulDiv(m_DotsPerMM.Height(), PtSize.Height(), res);

Dimension BMInitDim (logPX, logPY);

HPALETTE hOldPalette;			// Palette einstellen
HDC hDC = Handle (API_DRAWOBJECT_HDC);

	if (hPalette != 0) {
	// Palette einstellen       
		hOldPalette = SelectPalette (hDC, hPalette, false);
		RealizePalette (hDC);
	}

// Symbol am Rechteck clippen
HRGN hOldClipRgn = SelectClipRegion (hDC, Dim);

// jetzt wird gezeichnet
	if (!m_rDBO.FNewPnts()) {
	Bitmap BM (ResID (m_ID.Marker()));
	ExtBitmapObject EBMO (Centre, BMInitDim, &BM, m_ID.VI(m_iVTyp).PrimColor());
	
		m_pW -> Draw (&EBMO);
	} else {
	// Bitmaps werden je nach Größe aus dem entsprechenden Streifen gezeichnet
	unsigned int uiMarker = m_rDBO.FGetIndex(m_ID.Marker() + 1 - MARKER1);
	CBitmapBar *pBmp = m_rDBO.GetBmp (uiMarker, BMInitDim);

		if (pBmp) {
		CColorBitmapObject CBMO (Centre, BMInitDim, *pBmp, 
					 m_ID.VI(m_iVTyp).PrimColor(), 
					 m_ID.Get2ndColor(),
					 uiMarker, m_ID.Rotation());
		
			m_pW -> DrawEx (&CBMO, DWORD((void *)hPalette));
		}
	}

	::SelectClipRgn (hDC, hOldClipRgn);
	if (hOldClipRgn) DeleteObject (hOldClipRgn);

	if (hPalette) SelectPalette (hDC, hOldPalette, false);

	if (pOldVI) {		// wieder freigeben der neuen VI
	VisInfo *pVI = m_ID.ChangeVisInfo (pOldVI, VT_Punkt);

		DELETE (pVI);
	}
}


// LinienEintrag in Legende generieren ----------------------------------------
void CLegendeItem::LDrawLinie (Dimension &Dim) 
{
// wenn ein Objekt gezeichnet werden soll, dann hier in die Runde rufen
short iDrawResult = DO_UnChanged;
VisInfo *pOldVI = NULL;

	if (m_lONr != -1) switch (m_ID.DType() & DT_DrawingMask) {
	case DT_HasNewVI:	// eine überschlaue Erweiterung hat eine neue VI für uns
		{		// nur beim normalen Zeichnen
		DRAWOBJECTEX dObj;

			INITSTRUCT(dObj, DRAWOBJECTEX);
			dObj.lObjNr = m_lONr;		// ObjektNummer
			if (m_ID.hasVI (VT_Linie))
				dObj.pNewVI = (VisInfo *)m_ID.VI(VT_Linie).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = m_ID.Id();
			dObj.m_fFlags = DF_Analyze;

			DEXN_DrawObjectEx (dObj);
			if ((iDrawResult = (short)dObj.m_lResult) & DT_NoDrawing) {
				if (dObj.pNewVI) delete dObj.pNewVI;
				return;		// nicht zeichnen
			}

			if (iDrawResult & DO_VisInfoChanged) {
//				if (hPalette && iDrawResult & DO_ColorChanged)
				// evtl. Farbe, die noch nicht in der Palette existiert
//					ExpandPalette (hPalette, dObj.pNewVI);
				pOldVI = m_ID.ChangeVisInfo (dObj.pNewVI, VT_Linie);
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			}
		}
		break;

	case DT_Normal:		// alles wie gehabt
		break;

	default:		// irgend was falsch
		return;
	}

// Anfangs- und Endpunkt der Linie bestimmen
//CoOrd X = Dim.Width()/8;
CoOrd X = 0;
CoOrd Y = m_Pt.Y() - Dim.Height()/2;
long locWidth = m_ID.Width();

// neuerdings Linienbreite in 1/100 mm
#if defined(_FORCE_LEGACY_CODE)
	if (DBO().DB().GetDBVersion() >= VERSION05000004) 
#endif // defined(_FORCE_LEGACY_CODE)
	{
	double res = 100.0;

		if (GetScaleMode()) res *= DBO().M();
		locWidth = long( ( (double(locWidth) * double(m_DotsPerMM.Width())) / res ) + 0.5);
	} 
#if defined(_FORCE_LEGACY_CODE)
	else {
	double res = 1.0;

		if (GetScaleMode()) res = DBO().M();
		locWidth = long(locWidth / res + 0.5);
	}
#endif // defined(_FORCE_LEGACY_CODE)

// Palette einstellen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HPALETTE hOldPalette;

	if (hPalette != 0) {		// Palette einstellen       
		hOldPalette = SelectPalette (hDC, hPalette, false);
		RealizePalette (hDC);
	}

// Symbol am Rechteck clippen
HRGN hOldClipRgn = SelectClipRegion (hDC, Dim);

// Linie zeichnen
ExtPen *pEPen = (ExtPen *)m_ID.GetPen (VT_Linie, short(locWidth));

// alle Linien dieses ExtPens ausgeben
	for (int iCnt = 0; iCnt < pEPen -> iCnt(); iCnt++) {
	HPEN hOldPen;
	
	// aktuellen Pen selektieren
		if (pEPen != NULL) 
			hOldPen = (HPEN)SelectObject (hDC, pEPen -> GetHandle(iCnt));

	// Linie zeichnen         
		MoveToEx (hDC, m_Pt.X() + X, Y, NULL);
		LineTo (hDC, m_Pt.X() + Dim.Width() - X, Y);

	// DeviceKontext zurücksetzen
		if (pEPen != NULL) SelectObject (hDC, hOldPen);
	}

	::SelectClipRgn (hDC, hOldClipRgn);
	if (hOldClipRgn) ::DeleteObject (hOldClipRgn);

	if (hPalette) SelectPalette (hDC, hOldPalette, false);

	if (pOldVI) {		// wieder freigeben der neuen VI
	VisInfo *pVI = m_ID.ChangeVisInfo (pOldVI, VT_Linie);

		DELETE (pVI);
	}
}


// Flächeneintrag generieren --------------------------------------------------
void CLegendeItem::LDrawFlaeche (Dimension &Dim) 
{
// wenn ein Objekt gezeichnet werden soll, dann hier in die Runde rufen
short iDrawResult = DO_UnChanged;
VisInfo *pOldVI = NULL;

	if (m_lONr != -1) switch (m_ID.DType() & DT_DrawingMask) {
	case DT_HasNewVI:	// eine überschlaue Erweiterung hat eine neue VI für uns
		{		// nur beim normalen Zeichnen
		DRAWOBJECTEX dObj;

			INITSTRUCT(dObj, DRAWOBJECTEX);
			dObj.lObjNr = m_lONr;		// ObjektNummer
			if (m_ID.hasVI (VT_Flaeche))
				dObj.pNewVI = (VisInfo *)m_ID.VI(VT_Flaeche).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = m_ID.Id();
			dObj.m_fFlags = DF_Analyze;

			DEXN_DrawObjectEx (dObj);
			if ((iDrawResult = (short)dObj.m_lResult) & DT_NoDrawing) {
				if (dObj.pNewVI) delete dObj.pNewVI;
				return;		// nicht zeichnen
			}

			if (iDrawResult & DO_VisInfoChanged) {
//				if (hPalette && iDrawResult & DO_ColorChanged)
				// evtl. Farbe, die noch nicht in der Palette existiert
//					ExpandPalette (hPalette, dObj.pNewVI);
				pOldVI = m_ID.ChangeVisInfo (dObj.pNewVI, VT_Flaeche);
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			}
		}
		break;

	case DT_Normal:		// alles wie gehabt
		break;

	default:		// irgend was falsch
		return;
	}

// AnfangsPunkt und Größe des Rechtecks berechnen
long X = Dim.Width(), Y = Dim.Height();
Point Begin (CoOrd(m_Pt.X()), CoOrd(m_Pt.Y() - MulDiv(Y, 7000, 8000)));
Dimension Size (CoOrd(Dim.Width()), CoOrd(Dim.Height() - MulDiv(Y, 2000, 8000)));
HDC hDC = Handle (API_DRAWOBJECT_HDC);	// Rechteck zeichnen
HPALETTE hOldPalette;			// Palette einstellen

	if (hPalette != 0) {
	// Palette einstellen       
		hOldPalette = SelectPalette (hDC, hPalette, false);
		RealizePalette (hDC);
	}

// neuen Brush setzen
HBRUSH hOldBrush;
VisInfo *pVI = &m_ID.VI(m_iVTyp);	// muß != NULL sein
Bitmap *pBmp = NULL;
pBrush pB = m_ID.GetBrush (Handle (API_TARGET_HDC), false, &pBmp);

	if (pB != NULL)
		hOldBrush = (HBRUSH)SelectObject (hDC, pB -> Handle());
	else
		hOldBrush = (HBRUSH)SelectObject (hDC, GetStockObject (NULL_BRUSH));

COLORREF crOldBkCol;
int oldBkMode;

	if (!m_ID.isOpaque() && NULL != pBmp) {
	// transparent patterns
	COLORREF crOldTextColor = ::SetTextColor (hDC, RGB(0, 0, 0));

		crOldBkCol = ::SetBkColor (hDC, RGB(255, 255, 255));

	HDC hDCSrc = ::CreateCompatibleDC (hDC);
	HBITMAP hOldBmp = (HBITMAP)::SelectObject (hDCSrc, pBmp -> Handle());

	Dimension dim (pBmp -> GetSize());
	Rectangle R (Begin.Y(), Begin.X(), Begin.Y()+Size.Height(), Begin.X()+Size.Width());
	Rectangle rcDP (R);

		LPtoDP (hDC, (LPPOINT)&rcDP, 2);

	// passende ClippingRegion erzeugen und selektieren
	HRGN hRgn = CreateRectRgnIndirect((const RECT *)&rcDP);
	HRGN hRgnClip = CreateRectRgn (0, 0, 0, 0);

		if (GetClipRgn (hDC, hRgnClip) <= 0) {
		// no selected clipping region
			DeleteObject (hRgnClip);
			hRgnClip = NULL;
		}
		SelectClipRgn (hDC, hRgn);

	// Rechteck geclipt ausgeben
	long lX = MulDiv (dim.Width(), R.Width(), rcDP.Width());
	long lY = MulDiv (dim.Height(), abs(R.Height()), rcDP.Height());

		_ASSERTE(dim.Height() > 0 && dim.Width() > 0 && lX > 0 && lY > 0);
		if (dim.Height() > 0 && dim.Width() > 0) {
			for (long y = R.Top(); y <= R.Bottom(); y += lY) 
				for (long x = R.Left(); x <= R.Right(); x += lX) 
					StretchBlt (hDC, x, y, lX, lY, hDCSrc, 0, 0, dim.Width(), dim.Height(), MYROPCODE);
		}

	// ClippingRegion wieder zurücksetzen
		SelectClipRgn (hDC, hRgnClip);		// ggf. wird NULL selektiert
		if (NULL != hRgnClip) 
			DeleteObject (hRgnClip);
		DeleteObject (hRgn);

	// alles andere wieder zurücksetzen bzw. freigeben
		SelectObject (hDCSrc, hOldBmp);
		DeleteDC (hDCSrc);

	// hier duchfallen und Rahmen mit zeichnen lassen
		SetTextColor (hDC, crOldTextColor);
		SelectObject (hDC, GetStockObject (NULL_BRUSH));
	} 

// Rahmen bzw. nicht transparente Füllmuster zeichnen
	{
	// evtl. neuen Stift setzen
	HPEN hOldPen;
	int locWidth = m_ID.FrameWidth();

	// neuerdings Linienbreite in 1/100 mm
#if defined(_FORCE_LEGACY_CODE)
		if (DBO().DB().GetDBVersion() >= VERSION05000004)
#endif // defined(_FORCE_LEGACY_CODE)
			locWidth = MulDiv(locWidth, m_DotsPerMM.Width(), 100L);

	pPen pP = m_ID.GetPen (VT_Flaeche, locWidth);

		if (pP != NULL)
			hOldPen = (HPEN)SelectObject (hDC, pP -> Handle());
		else 
			hOldPen = (HPEN)SelectObject (hDC, GetStockObject (BLACK_PEN));

		crOldBkCol = ::SetBkColor (hDC, (COLORREF &)m_ID.GetBkColor());
		oldBkMode = ::SetBkMode (hDC, m_ID.isOpaque() ? OPAQUE : TRANSPARENT);

		DrawRectangle (hDC, Begin.X(), Begin.Y(), Begin.X()+Size.Width(), Begin.Y()+Size.Height());

	// DeviceContext rücksetzen
		::SelectObject (hDC, hOldPen);
	}

	::SetBkColor (hDC, crOldBkCol);
	::SetBkMode (hDC, oldBkMode);
	::SelectObject (hDC, hOldBrush);	
	if (hPalette)
		::SelectPalette (hDC, hOldPalette, false);

	if (pOldVI) {		// wieder freigeben der neuen VI
	VisInfo *pVI = m_ID.ChangeVisInfo (pOldVI, VT_Flaeche);

		DELETE (pVI);
	}
}


// Ein Textobjekt ist in der Legende ------------------------------------------
bool CLegendeItem::LDrawText (Dimension &Dim)
{
	if (m_lONr != -1L) {		// nur ObjektTexte
	HDC hDC = Handle (API_DRAWOBJECT_HDC);	// Rechteck zeichnen
	HDC hTargetDC = Handle (API_TARGET_HDC);
	
//		if (!DEX_isObjectVisible (m_lONr))
//			return false;		// Objekt nicht sichtbar

	char *pBuffer = new char [_MAX_PATH];

		if (pBuffer == NULL) return false;	// Fehler
			
	long lIconWidth = m_TextX - m_Pt.X();	// reale Breite des Bildchens
		
		HandleIcon (hDC, hTargetDC, DBO(), m_ID, m_lONr, TPText, m_Pt, pBuffer, m_Dim.Height(), lIconWidth, true);

		DELETE (pBuffer);		// Speicher freigeben
	} 
	return true;
}


// Beschreibenden Text für einen LegendenEintrag ausgeben ---------------------
void CLegendeItem::LDrawDescText (Dimension &dimSign) 
{
// nur zeichnen, wenn nicht Begleitobjekt
//	if (!m_ID.hasVI(m_iVTyp) || m_ID.VI(m_iVTyp).isA() == VT_Text)
//		return;

// auszugebenden Text besorgen
LPCSTR szText = m_pText;

	if (szText == NULL || *szText == '\0') 
		szText = m_ID.GetLangText();	// KurzText holen

	if (szText == NULL || *szText == '\0') 
		szText = m_ID.GetKurzText();

	if (szText == NULL || *szText == '\0')
		szText = "\\ ";		// Leerzeile ausgeben
	
// wenn dieser Eintrag nicht angezeigt ist, dann grau kennzeichnen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HDC hTargetDC = Handle (API_TARGET_HDC);
COLORREF cr = GetTextColor (hDC);

	if (!m_fShown) 
		SetTextColor (hDC, GetSysColor (COLOR_GRAYTEXT));

// Text ausgeben
Rectangle rc (Point (m_TextX, m_Pt.Y()), Dimension (m_Dim.Width() - (m_TextX - m_Pt.X()), 0));

short iLineCnt = 0;	// ZeilenAnzahl bestimmen
CoOrd iLine = Justify (hDC, hTargetDC, szText, NULL, (RECT *)&rc, ATLeft, false, &iLineCnt);

	if (dimSign.Height() > iLine) {
		rc.Top() -= (dimSign.Height())/16;
		if (iLineCnt <= 1) 	// an Unterkante ausrichten
			rc.Top() -= MulDiv(dimSign.Height(), 7000, 8000) - iLine;
	} else
		rc.Top() += dimSign.Height()/8;

	rc.Bottom() = rc.Top();
	Justify (hDC, hTargetDC, szText, NULL, (RECT *)&rc, ATLeft, true);

	SetTextColor (hDC, cr);

long lTop = m_rCache.KastenVorHoehe (iLine/12);
long lBottom = m_rCache.KastenNachHoehe (iLine/12);

	m_Dim.Height() = CoOrd(rc.Height() + (lTop+lBottom));	// aktuelle Höhe
}

///////////////////////////////////////////////////////////////////////////////
// Zwischenüberschrift zeichnen
CHeadLineItem::CHeadLineItem(
		Window *pW, Point &rPt, Dimension &rDim, Dimension &rMM, 
		CLegSizeCache &rCache, int iFontH, LPCSTR pcText) :
	m_pW(pW), m_Pt(rPt), m_Dim(rDim), m_DotsPerMM(rMM), m_rCache(rCache), 
	m_iFontH(iFontH), m_strText(pcText)
{
	ChangeSize (m_Dim);
}

void CHeadLineItem::Draw()
{
HDC hDC = Handle (API_DRAWOBJECT_HDC);	// Rechteck zeichnen
HDC hTargetDC = Handle (API_TARGET_HDC);

// Font erzeugen und einstellen
ResString rsArial (IDS_ARIAL, 20);
int iFontHL = m_iFontH;	// Defaultgröße der Überschrift ist identisch mit anderem Textes (nur bold)
bool fBold = true;
bool fItalic = false;
bool fUnderline = false;
string strFontName (rsArial.Addr());
int iFamily = Swiss;

	m_rCache.ZwischenUeberschriftFont (iFamily, strFontName, iFontHL, fBold, fItalic, fUnderline);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont CapFont ((StdFamily)iFamily, Dimension(0, -iFontHL), strFontName.c_str());
#else
Font CapFont ((StdFamily)iFamily, Dimension(0, -iFontHL), strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	
	if (fBold) CapFont.SetBold();
	if (fItalic) CapFont.SetItalic();
	if (fUnderline) CapFont.SetUnderline();
	CapFont.Init();
	
HFONT hOldFont = (HFONT)SelectObject (hDC, CapFont.Handle (API_FONT_HFONT));

// Text ausgeben
long lVorHoehe = (LEGENTRYTYPE_TEXT == isA()) ? m_rCache.ZwischenUeberschriftVorHoehe(2*m_DotsPerMM.Height()) : 0;
Rectangle rc (Point (m_Pt.X(), m_Pt.Y()-lVorHoehe), Dimension (m_Dim.Width(), 0));
CoOrd iLine = Justify (hDC, hTargetDC, m_strText.c_str(), NULL, (RECT *)&rc, ATLeft, false);

	rc.Bottom() = rc.Top();
	Justify (hDC, hTargetDC, m_strText.c_str(), NULL, (RECT *)&rc, ATLeft, true);
	SelectObject (hDC, hOldFont);
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für gesamte Legende 
CLegendeObjekt *CLegendeObjekt::CreateInstance (
	pWindow pW, DatenBasisObjekt &rDBO, Rectangle *pRc, PrinterPars *pPP) 
{
CLegendeObjekt *pLO = new CLegendeObjekt (pW, rDBO);

	if (pLO == NULL || !pLO -> FInit (pRc, pPP)) {
		DELETE (pLO);
		return NULL;
	}
	return pLO;
}

bool CLegendeObjekt::FInit (Rectangle *pRc, PrinterPars *pPP)
{
	if (pRc) {
		m_pR = new Rectangle();
		if (m_pR == NULL) 
			return false;
		*m_pR = *pRc;		// kopieren

	// wenn pRc gegeben ist, dann ists eine Drucklegende und 
	// pPP muß gegeben sein
		if (NULL == pPP || !m_PrLayout.FInit (*pPP))
		{
			return false;
		}
	}

	m_pParser = CLegEntryParser::CreateInstance();
	if (m_pParser == NULL) return false;

	m_pBuffer = new char [_MAX_PATH];
	if (m_pBuffer == NULL) return false;

// Baum der darzustellenden LegendenEinträge anlegen
	m_pItems = CLegendInfo::CreateInstance (*m_pParser, DBO(), m_lMCode);
	if (m_pItems == NULL) 
		return false;
	return true;
}

CLegendeObjekt::CLegendeObjekt (pWindow pW, DatenBasisObjekt &rDBO)
	        : DrawObject(), m_rDBO(rDBO), m_pW(pW)
{
// Variablen initialisieren
	m_pR = NULL;
	m_iIdCnt = 0;
	m_ptOrg = Point (0, 0);
	m_iLine = 0;

	m_fDirty = false;
	m_fShowAllEntries = false;

// MerkmalsCode für LegendenInfo besorgen
	m_lMCode = m_rDBO.GetHeaderMCode (false, IDS_LEGENDINFOMCODE); 
	
// Parser generieren und initialisieren
	m_pItems = NULL;
	m_pBuffer = NULL;
	m_pParser = NULL;
}

CLegendeObjekt::~CLegendeObjekt (void) 
{
	DELETE (m_pR);
	#pragma TODO("Delete wieder einfügen und zerkloppten Speicher suchen!")
//	DELETE (m_pItems);
	DELETE (m_pParser);
	DELETE (m_pBuffer);
}


bool CLegendeObjekt::RefreshLegend (void)
{
	if (m_pItems == NULL) return false;
	if (isDirty()) {
		if (!DEX_GetROModeEx(HACTPROJECT))
			SaveLegend();
		m_fDirty = false;
	}
	return m_pItems -> FInit (IDs());
}

// setzen der Papierabmessungen (DruckSpiegel) --------------------------------
void CLegendeObjekt::SetBaseValues (Rectangle &rRC, HDC hTargetDC)
{
Dimension mm (GetDotsPerMM (hTargetDC));
long lWidth = MulDiv(rRC.Width(), 100L, mm.Width());
long lHeight = MulDiv(rRC.Height(), 100L, mm.Height());

	m_PrLayout.SetBaseValues (lWidth, lHeight);
}

bool CLegendeObjekt::GetViewDesc (string &rstr)
{
VIEWDESC VD;
char cbBuffer[_MAX_PATH];

	VD.m_dwSize = sizeof(VIEWDESC);
	VD.m_pView = NULL;		// aktuelle Sicht verwenden
	VD.m_pDesc = cbBuffer;
	VD.m_iLen = _MAX_PATH;
	
	if (!DEX_GetViewDescription (VD)) {	// nichts gegeben
#if _TRiAS_VER < 0x0400
	ResString rsLegCap ((0 != g_dwVer4) ? IDS_LEGENDECAP : IDS_LEGENDECAP_0300, 32);
#else
	ResString rsLegCap (IDS_LEGENDECAP, 32);
#endif // _TRiAS_VER < 0x0400

		rstr = rsLegCap.Addr();
		return true;
	}
	rstr = cbBuffer;
	return true;
}

bool CLegendeObjekt::AddObject (long lONr)
{
	if (m_pItems == NULL) return false;

WORD iOrder = USHRT_MAX;
bool fRet = m_pItems -> AddObject (lONr, iOrder);

	if (fRet) 
		m_fDirty = true;
	return fRet;
}

bool CLegendeObjekt::ViewSelected (LPCSTR pcView)
{
	if (NULL == m_pItems)
		return false;
	return m_pItems -> ViewSelected (pcView);
}

// Größe der Legende berechnen/Font dimensionieren ----------------------------
Dimension CLegendeObjekt::FitLegendSize (Rectangle *pR, HDC hDefDC, HDC hDefTargetDC)
{
long lWidth = pR->Right() - pR->Left();	// Breite ist fest
long lHeight = 0;					// soll berechnet werden
HDC hDC = NULL;
HDC hTargetDC = NULL;
HWND hWnd = NULL;

	if (NULL != hDefDC) 
		hDC = hDefDC;
	else {
		hWnd = m_pW -> Handle (API_WINDOW_HWND);
		hDC = ::GetDC (hWnd);
	}

	if (NULL != hDefTargetDC)
		hTargetDC = hDefTargetDC;
	else
		hTargetDC = hDC;

Dimension mm (GetDotsPerMM (hTargetDC));
int iDelta = MulDiv (mm.Height(), 3176L, 20000L);	// 0.5pt Delta
bool fContinue;

	if (iDelta == 0) iDelta = 1;

ResString rsArial (IDS_ARIAL, 20);

	m_iFontH = 5*mm.Height();		// mit 5mm anfangen
	m_fBold = false;
	m_fItalic = false;
	m_fUnderline = false;
	m_strFontName = rsArial.Addr();
	m_iFamily = Swiss;

	m_PrLayout.KastenFont (m_iFamily, m_strFontName, m_iFontH, m_fBold, m_fItalic, m_fUnderline);
	m_iFontOrg = m_iFontH;

long lLeft = m_PrLayout.KastenVorBreite (2*mm.Width());
long lRight = m_PrLayout.KastenNachBreite (2*mm.Width());

	lWidth -= (lLeft + lRight);		// Breite des Textbereiches
	
// Font ausgehend von einer AnfangsGröße solange kleiner machen, bis die
// ganze Legende im vorgegebenen Bereich Platz hat

	do {		// Font auswählen
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	CVFont locFont ((StdFamily)m_iFamily, Dimension (0, -m_iFontH), m_strFontName.c_str());
#else
	Font locFont ((StdFamily)m_iFamily, Dimension (0, -m_iFontH), m_strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

		if (m_fBold) locFont.SetBold();
		if (m_fItalic) locFont.SetItalic();
		if (m_fUnderline) locFont.SetUnderline();
		locFont.Init();
		
	HFONT hOldFont = (HFONT)SelectObject (hDC, locFont.Handle (API_FONT_HFONT));
	
	// für diesen Font Größe generieren, Gesamthöhe berechnen		
		lHeight = m_PrLayout.LegendeVorHoehe (0);	// neu initialisieren
		m_iIdCnt = 0;			// Zähler der Einträge

	// Höhe der gesamten Legende berechnen
		fContinue = !GetLegendSize (hDC, hTargetDC, lWidth, mm, m_iFontH, true, lHeight);
		lHeight += m_PrLayout.LegendeNachHoehe (0);

	// Font wieder abmelden
		SelectObject (hDC, hOldFont);
		if ((m_iFontH -= iDelta) <= 0)
			break;		// Font zu klein: abbrechen

	} while (fContinue || lHeight > pR->Top() - pR->Bottom());
	m_iFontH += iDelta;	// da war einmal zuviel da
		
// aufräumen
	if (NULL == hDefDC) 
		::ReleaseDC (hWnd, hDC);

	if (m_iFontH > 0) 
		return Dimension (pR->Right() - pR->Left(), lHeight);
	return Dimension();
}


// Umrechnen eines Vistyp's in einen Objekttyp --------------------------------
short VTypToBits (VisType iVTyp)
{
	switch (iVTyp) {
	case VT_Punkt:		return TPPunkt;
	case VT_Linie:		return TPLinie;
	case VT_Flaeche:	return TPFlaeche;
	case VT_Text:		return TPText;
	case VT_Default:
	default:
		break;
	}
	return 0;	// no type at all
}

// Höhe der Legende mit einem Font berechnen ----------------------------------
Dimension CLegendeObjekt::GetRealSize (Rectangle *pR, bool &fFitWidth)
{
HWND hWnd = m_pW -> Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);
Dimension mm (GetDotsPerMM (hDC));
long lWidth = pR->Right() - pR->Left();	// Breite ist fest
long lHeight = 2*mm.Height();			// soll berechnet werden

	m_iFontH = 5*mm.Height();			// alles 5mm groß
	m_iFontOrg = m_iFontH;
	m_iIdCnt = 0;		// Zähler der Einträge

ResString rsArial (IDS_ARIAL, 20);
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont locFont (Swiss, Dimension (0, -m_iFontH), rsArial);
#else
Font locFont (Swiss, Dimension (0, -m_iFontH), rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

	locFont.Init();
		
// für diesen Font Größe generieren
HFONT hOldFont = (HFONT)SelectObject (hDC, locFont.Handle (API_FONT_HFONT));

// Höhe der gesamten Legende berechnen
	lWidth -= 4*mm.Width();		// Rand lassen
	fFitWidth = GetLegendSize (hDC, hDC, lWidth, mm, m_iFontH, false, lHeight);
	
// Font wieder abmelden, aufräumen
	SelectObject (hDC, hOldFont);
	::ReleaseDC (hWnd, hDC);
	return Dimension (pR->Right() - pR->Left(), int(lHeight));
}


// Höhe der gesamten Legende mit der aktuellen FontGröße berechnen ------------
bool CLegendeObjekt::GetLegendSize (
	HDC hDC, HDC hTargetDC, long lWidth, Dimension &mm, int iFontH, bool fBreak, long &rlHeight)
{
// Überschrift reinrechnen
string strLegCap;

	GetViewDesc (strLegCap);

ResString rsArial (IDS_ARIAL, 20);
bool fBold = true;
bool fItalic = false;
bool fUnderline = false;
string strFontName (rsArial.Addr());
int iFamily = Swiss;
int iDummy = 0;

	m_iCapFontH = MulDiv(iFontH, 7000L, 5000L);		// Überschrift ist (anfangs) 7/5 des anderen Textes
	m_PrLayout.LegendeKopfFont (iFamily, strFontName, iDummy, fBold, fItalic, fUnderline);

long lFullWidth = lWidth;

	lWidth -= m_PrLayout.KastenZwischenBreite (2*mm.Width());
	lWidth -= m_PrLayout.KastenBreite (MulDiv(lFullWidth, 4000L, 25000L));

int iDelta = MulDiv (mm.Height(), 3176L, 20000L);	// 0.5pt Delta
int iCapHeight = 0;
CoOrd iLine = 0;

	if (iDelta == 0) iDelta = 1;

	do {
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	CVFont CapFont ((StdFamily)iFamily, Dimension(0, -m_iCapFontH), strFontName.c_str());
#else
	Font CapFont ((StdFamily)iFamily, Dimension(0, -m_iCapFontH), strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	
		if (fBold) CapFont.SetBold();
		if (fItalic) CapFont.SetItalic();
		if (fUnderline) CapFont.SetUnderline();
		CapFont.Init();
	
	HFONT hOldFont = (HFONT)SelectObject (hDC, CapFont.Handle (API_FONT_HFONT));
	Rectangle rcSize (Point(), Dimension (lWidth, 0));

		iLine = Justify (hDC, hTargetDC, strLegCap.c_str(), NULL, (RECT *)&rcSize, ATLeft, false);
		SelectObject (hDC, hOldFont);
		iCapHeight = rcSize.Height();
		if (lWidth >= rcSize.Width() || (m_iCapFontH -= iDelta) <= 0)
			break;		// solange verkleinern, bis der Text reinpaßt bzw. Font nicht zu klein wird

	} while (true);
	m_iCapFontH += iDelta;	// da war einmal zuviel da
	rlHeight += iCapHeight;

long lLegTop = MulDiv(m_PrLayout.LegendeKopfVorHoehe(2*mm.Height()), iFontH, m_iFontOrg);
long lLegBottom = MulDiv(m_PrLayout.LegendeKopfNachHoehe(iLine), iFontH, m_iFontOrg);

	rlHeight += lLegTop + lLegBottom;

// sonstige LegendenEinträge dazurechen
CTable tId (IDs().IdentTree());
bool fFitWidth = true;

	TX_ASSERT(NULL != m_pItems);
	{
	// nur entsprechende LegEntries aus diesem Baum berücksichtigen
	CTable t (*m_pItems);
//	long lETop = (m_PrLayout.KastenVorHoehe(m_iLine/12)*iFontH)/m_iFontOrg;
//	long lEBottom = (m_PrLayout.KastenNachHoehe(m_iLine/12)*iFontH)/m_iFontOrg;

		for (t.First(); t.Valid(); t.Next()) {
		CLegendInfoEntryLock l(t);
		
			if (!l) continue;
			
		// wenn nicht alle anzeigen und dieser gehört nicht dazu, dann weiter
			if (!ShowAll() && !l -> isShown()) 
				continue;

		long lONr = -1L;
		long lIdent = -1L;
		LEGENTRYTYPE rgLType = l -> isA();
					
			switch (rgLType) {
			case LEGENTRYTYPE_OBJECT:
				lONr = ((CLegendInfoObject *)(CLegendInfoEntry *)l) -> GetONr();
				lIdent = DEX_GetObjIdentEx (lONr);
			// hier durchfallen
						
			case LEGENTRYTYPE_IDENT:
				{
					if (lIdent == -1L) {	// kein Objekt
					CLegendInfoIdent *pLId = (CLegendInfoIdent *)(CLegendInfoEntry *)l;
						
						lIdent = pLId -> GetIdent();
					}
					if (!tId.Find (&lIdent)) 
						continue;
						
				CIdentifikatorLock lId (tId);

					if (!lId) continue;

				// Höhe dieses Eintrages berechnen
//					rlHeight += lETop;

				long lPosition = rlHeight;
				char *pText = l -> GetText();
				short iNewWidth = 0;

					l -> SetPosition (lPosition/* - lETop*/);
					if (!GetIdentEntrySize (hDC, hTargetDC, *lId, rlHeight, lWidth, fFitWidth, fBreak, VTypToBits (l -> GetVType()), pText, lONr, &iNewWidth))
					{
						DELETE (pText);
						return false;	// abbrechen, wenn zu groß
					}
//					rlHeight += lEBottom;

				// Höhe des Eintrages merken
					if (l -> hasSpace()) 	// Leerzeile einfügen
						rlHeight += m_PrLayout.LeerzeileHoehe (MulDiv(iLine, 1200L, 1000L));

					l -> SetHeight (rlHeight - lPosition);

				// wenn Objekteintrag großes Bildchen hat
					if (iNewWidth && rgLType == LEGENTRYTYPE_OBJECT) {
					long lMiddle = m_PrLayout.KastenZwischenBreite (2*mm.Width());

						((CLegendInfoObject *)(CLegendInfoEntry *)l) -> IconWidth() = iNewWidth + lMiddle;
					}
					DELETE (pText);
				}
				break;

			case LEGENTRYTYPE_SPACELINE:
			case LEGENTRYTYPE_TEXT:		// Zwischenüberschrift
				{
				long lPosition = rlHeight;
				char *pText = (LEGENTRYTYPE_TEXT == rgLType) ? l -> GetText() : NULL;

					l -> SetPosition (lPosition);

				// Höhe berechnen
					if (!GetHeadLineSize(hDC, hTargetDC, pText, lFullWidth, iFontH, mm, fFitWidth, rlHeight, fBreak))
					{
						DELETE (pText);
						return false;	// abbrechen, wenn zu groß
					}

				// Höhe des Eintrages merken
					if (l -> hasSpace()) 	// Leerzeile einfügen
						rlHeight += m_PrLayout.LeerzeileHoehe (MulDiv(iLine, 1200L, 1000L));
					l -> SetHeight (rlHeight - lPosition);
					DELETE (pText);
				}
				break;

			default:
				continue;
			}
		}
	}
	return fFitWidth;
}

// Höhe einer Zwischenüberschrift bestimmen
int CLegendeObjekt::GetHeadLineSize (
	HDC hDC, HDC hTargetDC, LPCSTR pcText, long lWidth, int iFontH, Dimension &mm,
	bool &rfFitWidth, long &riHeight, bool fBreak)
{
ResString rsArial (IDS_ARIAL, 20);
int iFontHL = iFontH;	// Defaultgröße der Überschrift ist identisch mit anderem Text (nur bold)
bool fBold = true;
bool fItalic = false;
bool fUnderline = false;
string strFontName (rsArial.Addr());
int iFamily = Swiss;

	m_PrLayout.ZwischenUeberschriftFont (iFamily, strFontName, iFontHL, fBold, fItalic, fUnderline);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont CapFont ((StdFamily)iFamily, Dimension(0, -iFontHL), strFontName.c_str());
#else
Font CapFont ((StdFamily)iFamily, Dimension(0, -iFontHL), strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	
	if (fBold) CapFont.SetBold();
	if (fItalic) CapFont.SetItalic();
	if (fUnderline) CapFont.SetUnderline();
	CapFont.Init();
	
HFONT hOldFont = (HFONT)SelectObject (hDC, CapFont.Handle (API_FONT_HFONT));

Rectangle rcSize (Point(), Dimension (lWidth-1, 0));
CoOrd iLine = Justify (hDC, hTargetDC, (NULL != pcText) ? pcText : "\\ ", NULL, (RECT *)&rcSize, ATLeft, false);
CoOrd iHeight = rcSize.Height();

	SelectObject (hDC, hOldFont);

// ein negativer Wert weist darauf hin, daß ein Wort länger als die Zeile ist
	if (rcSize.Right() > lWidth) {
		rfFitWidth = false;
		if (fBreak) 
			return false;		// gleich weitermachen
	}
	riHeight += iHeight;
	if (NULL != pcText) {
	// Zwischenüberschrift (nicht Zwischenzeile)
		riHeight += m_PrLayout.ZwischenUeberschriftVorHoehe(2*mm.Height());
		riHeight += m_PrLayout.ZwischenUeberschriftNachHoehe(2*mm.Height());
	}
	return true;
}

// Höhe eines sonstigen Eintrages (Objekt oder Identifikator) bestimmen
bool CLegendeObjekt::GetIdentEntrySize (
		HDC hDC, HDC hTargetDC, CIdentifikator &rId, long &rlHeight, long lWidth,
		bool &rfFitWidth, bool fBreak, short iBits, char *pText, 
		long lONr, short *piNewWidth)
{
long lKasten = m_PrLayout.KastenBreite (MulDiv(lWidth, 4000L, 25000L));	// Standardbreite des Bildchens
short fVisible = 0;
// wenn objektspezifisch Visualisiert werden soll
int iIconHeight = 0;	// Höhe des Bildchens
bool fObject = false;

	if (lONr != -1L) {
		fVisible = DEX_isObjectVisible (lONr);
		if (ShowAreaOnly() && !fVisible) 
			return true;	// Objekt nicht sichtbar

		fVisible = iBits;		// ObjectTyp speichern

	long lIconWidth = 0;		// reale Breite des Bildchens
	Point pt (0, 0);			// nur Größe bestimmen
	
		iIconHeight = HandleIcon (hDC, hTargetDC, DBO(), rId, lONr, iBits, pt, m_pBuffer, 0, lIconWidth, false);

		if (lIconWidth > lKasten) {	// breiter als vorgesehen
			lWidth -= (lIconWidth - lKasten);
			if (piNewWidth) 
				*piNewWidth = lIconWidth;
		}
		fObject = true;
	} 
	else {	// Identifikatorweise
	// Objekte außerhalb des Bildausschnittes nicht zeichnen
 		fVisible = rId.isVisible (iBits);	// sind gesuchte Objekttypen sichtbar 
		if (ShowAreaOnly() && !fVisible) 
			return true;	// gehört nicht dazu
	}
		
int iT = GetItemHeight (hDC, hTargetDC, rId, lWidth, pText);	// Größe des Beschreibenden Textes
			
	if (iT < 0) { 	// ein Wort ist länger als gesamte Zeile
		rfFitWidth = false;
		if (fBreak) 
			return false;		// gleich weitermachen
		iT = -iT;	// als Zeilenhöhe auswerten
	}

short fToPaint = rId.toPaint();
long lItemTop = MulDiv(m_PrLayout.KastenVorHoehe(m_iLine/12), m_iFontH, m_iFontOrg);
long lItemBottom = MulDiv(m_PrLayout.KastenNachHoehe(m_iLine/12), m_iFontH, m_iFontOrg);

	iT = max (iT, iIconHeight);		// Maximum der beiden Teile
	if ((!ShowAreaOnly() && (fToPaint & TPPunkt) && (iBits & TPPunkt)) || (fVisible & TPPunkt)) {
		rlHeight += iT + (lItemTop+lItemBottom);
		m_iIdCnt++;
	}
	if ((!ShowAreaOnly() && (fToPaint & TPLinie) && (iBits & TPLinie)) || (fVisible & TPLinie)) {
		rlHeight += iT + (lItemTop+lItemBottom);
		m_iIdCnt++;
	}
	if ((!ShowAreaOnly() && (fToPaint & TPFlaeche) && (iBits & TPFlaeche)) || (fVisible & TPFlaeche)) {
		rlHeight += max (iT, MulDiv(m_iLine, m_PrLayout.KastenHoehe(100), 100L));
		rlHeight += (lItemTop+lItemBottom);
		m_iIdCnt++;
	}
	if (fObject && ((!ShowAreaOnly() && (fToPaint & TPText) && (iBits & TPText)) || (fVisible & TPText))) 
	{
	// für Einzelobjekte auch Texte
		rlHeight += iT + (lItemTop+lItemBottom);
		m_iIdCnt++;
	}
	return true;
}

int CLegendeObjekt::GetItemHeight (
	HDC hDC, HDC hTargetDC, CIdentifikator &rCId, long lWidth, char *pText)
{
// anzuzeigenden Text besorgen
LPCSTR szText = pText;

	if (szText == NULL || *szText == '\0') 
		szText = rCId.GetLangText();	// Kurz/LangText holen

	if (szText == NULL || *szText == '\0') 
		szText = rCId.GetKurzText();

	if (szText == NULL || *szText == '\0')
		szText = "\\ ";		// Leerzeile ausgeben

Rectangle rcSize (Point(), Dimension (lWidth-1, 0));
CoOrd iLine = Justify (hDC, hTargetDC, szText, NULL, (RECT *)&rcSize, ATLeft, false);
CoOrd iHeight = rcSize.Height();

	m_iLine = iLine;	// aktuelle ZeilenHöhe merken
	
// ein negativer Wert weist darauf hin, daß ein Wort länger als die Zeile ist
	return (rcSize.Right() > lWidth) ? -iHeight : iHeight;
}

int HandleIcon (HDC hDC, HDC hTargetDC, DatenBasisObjekt &rDBO, CIdentifikator &rId, 
		long lONr, short iBits, Point pt, char *pBuffer, CoOrd iHeight, 
		long &rlIconWidth, bool fDraw)
{
// ObjektTypSpezifisch entscheiden
	if (!(iBits & TPText)) 
		return 0;	// alle anderen Typen ordnen sich ein
	
// Text besorgen
GETTEXTDATA GTD;

	INITSTRUCT(GTD, GETTEXTDATA);
	GTD.m_lONr = lONr;
	GTD.m_pText = pBuffer;
	GTD.m_iLen = _MAX_PATH;
	if (!DEX_GetTextObjectText(GTD) || GTD.m_iLen == 0) 
		return 0;
	
// evtl. objektbezogene Visualisierung berücksichtigen
short iDrawResult = DO_UnChanged;
VisInfo *pOldVI = NULL;

	switch (rId.DType() & DT_DrawingMask) {
	case DT_HasNewVI:	// eine überschlaue Erweiterung hat eine neue VI für uns
		{		// nur beim normalen Zeichnen
		DRAWOBJECTEX dObj;

			INITSTRUCT(dObj, DRAWOBJECTEX);
			dObj.lObjNr = lONr;		// ObjektNummer
			if (rId.hasVI (VT_Text))
				dObj.pNewVI = (VisInfo *)rId.VI(VT_Text).Copy();	// neue VI
			else
				dObj.pNewVI = NULL;
			dObj.lIdent = rId.Id();
			dObj.m_fFlags = DF_Analyze;

			DEXN_DrawObjectEx (dObj);
			if ((iDrawResult = (short)dObj.m_lResult) & DT_NoDrawing) {
				if (dObj.pNewVI) delete dObj.pNewVI;
				return 0;		// nicht zeichnen
			}

			if (iDrawResult & DO_VisInfoChanged) {
//				if (hPalette && iDrawResult & DO_ColorChanged)
				// evtl. Farbe, die noch nicht in der Palette existiert
//					ExpandPalette (hPalette, dObj.pNewVI);
				pOldVI = rId.ChangeVisInfo (dObj.pNewVI, VT_Text);
			} else {
				if (dObj.pNewVI) delete dObj.pNewVI;
			}
		}
		break;

	case DT_Normal:		// alles wie gehabt
		break;

	default:		// irgend was falsch
		return 0;
	}

// Font generieren und selektieren
//int locBKMode = rId.BKMode (VT_Text);
//int locFrameMode = rId.FrameMode();

Dimension mm (GetDotsPerMM (hTargetDC));
Dimension locSize = rId.Size(VT_Text);
//double dDelta = (locSize.Height() > 0) ? 0.5 : -0.5;
CoOrd PtX = ToCoOrd((double)mm.Width() * (double)(locSize.Width()) * 0.3176);
CoOrd PtY = ToCoOrd((double)mm.Height() * (double)(locSize.Height()) * 0.3176);
Dimension FontSize (PtX, PtY);
pFont pF = rId.GetFont (FontSize);
HFONT hFont = 0;

	if (pF) {
		pF -> Init();		// Font initialisieren
		hFont = (HFONT)SelectObject (hDC, pF -> Handle (API_FONT_HFONT));
	}

// Textgröße bestimmen, umschließendes Rechteck vorbereiten, Höhe berechnen lassen
Point locPt (pt.X(), pt.Y()-iHeight);
Rectangle rc (locPt, Dimension (0, 0));	
short iLineCnt = 0;		// Anzahl der Zeilen
CoOrd iH = Justify (hDC, hTargetDC, pBuffer, (POINT *)&locPt, (RECT *)&rc, ATLeft, false, &iLineCnt);

	if (fDraw) {	// sonstige Attribute setzen
	Color locC = rId.GetColor (VT_Text);
	COLORREF oC = SetTextColor (hDC, *(COLORREF *)&locC);
	int oldBkMode = SetBkMode (hDC, TRANSPARENT);	// Text auf jeden Fall Transparent

	// einzeilige Texte zentrieren	
		if (1 == iLineCnt && (rlIconWidth > rc.Width())) {	// Rechteck ggf. zentrieren
//		int iDelta = (rlIconWidth - (rc.Right() - rc.Left()))/2;
		int iDelta = rlIconWidth/2;

			rc.Left() += iDelta;
			rc.Right() += iDelta;
		}

	// evtl. Textrahmen zeichnen
		if (rId.FrameMode()) {	
		long lAssocON = AssociatedObjekt (lONr, NULL);
		COLORREF crC;
	
			if (!rId.BKMode (VT_Text) || lAssocON == 0) 
				crC = RGB (255, 255, 255);
			else {
			// Farbe des Rechtecks von Bezugsobjekt holen
				crC = DEX_GetObjColor (lAssocON);
				if (hPalette)
					crC = PALETTEINDEX (GetNearestPaletteIndex (hPalette, crC));
			}
	
		HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, CreateSolidBrush (crC));
	
			oldBkMode = SetBkMode (hDC, OPAQUE);
			rc.Top() += iH;
			
			if (rId.RoundFrame()) {
			TEXTMETRIC TM;
			short iD = 0;
			
				GetTextMetrics (hDC, &TM);
				iD = TM.tmAveCharWidth / 2;
				::RoundRect (hDC, rc.Left()-iD, rc.Top()+iD, rc.Right()+iD, rc.Bottom()-iD, 4*iD, 4*iD);
			} else 
				DrawRectangle (hDC, rc.Left(), rc.Top(), rc.Right(), rc.Bottom());

			DeleteObject (SelectObject (hDC, hOldBr));
			SetBkMode (hDC, oldBkMode);
		}
	
	// Einzeilige Texte zentrieren, sonst normal linksbündig
		rc = Rectangle (locPt, Dimension (int(rlIconWidth), 0));
		Justify (hDC, hTargetDC, pBuffer, (POINT *)&locPt, (RECT *)&rc, ((iLineCnt <= 1) && (rlIconWidth > rc.Width())) ? ATCentre : ATLeft, true);
	
	// Attribute wieder freigeben
		SetTextColor (hDC, oC);
		SetBkMode (hDC, oldBkMode);
	}

//	iH = (iH * 400)/300;		// + 1/3 der Zeilenhöhe als Zwischenraum
	if (pF) SelectObject (hDC, hFont);
	
// wieder freigeben der neuen VI
	if (pOldVI) {
	VisInfo *pVI = rId.ChangeVisInfo (pOldVI, VT_Text);

		DELETE (pVI);
	}
	rlIconWidth = rc.Right() - rc.Left();
	return rc.Top() - rc.Bottom() + iH;		// liefert Höhe zurück
}

///////////////////////////////////////////////////////////////////////////////
// Legende zeichnen 
void CLegendeObjekt::DrawEx (DWORD dwData) 
{
// ClippingBereich für Legende setzen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HDC hTargetDC = Handle (API_TARGET_HDC);

	SaveDC (hDC);	// alten DC merken

// ClippingRechteck muß explizit gesetzt werden (nur wenn vorgegeben)
HRGN hRgn = NULL;

	if (dwData) {
		hRgn = CreateRectRgnIndirect ((RECT *)dwData);
		if (hRgn) 
			SelectClipRgn (hDC, hRgn);
	}

// Legendenposition festlegen
	SetWindowOrgEx (hDC, m_ptOrg.X(), m_ptOrg.Y(), NULL);

Rectangle CRc = m_pW -> CanvasRect();
Rectangle Rc = m_pR ? *m_pR : CRc;			// Fenstergröße
int OldBkMode = SetBkMode (hDC, TRANSPARENT);
HPALETTE hOldPalette = NULL;
	
	if (hPalette != NULL) {		// Palette einstellen       
		hOldPalette = SelectPalette (hDC, hPalette, false);
		RealizePalette (hDC);
	}

// Flächenaufteilung für Legende festlegen
Dimension mm (GetDotsPerMM (Handle (API_TARGET_HDC)));
string strLegCap;

	GetViewDesc (strLegCap);

// Formatierung bestimmen
long lLeft = m_PrLayout.KastenVorBreite (2*mm.Width());
long lRight = m_PrLayout.KastenNachBreite (2*mm.Width());

long lTop = m_PrLayout.LegendeVorHoehe (0);
long lBottom = m_PrLayout.LegendeNachHoehe (0);
long lLegTop = MulDiv(m_PrLayout.LegendeKopfVorHoehe (2*mm.Height()), m_iFontH, m_iFontOrg);
long lLegBottom = MulDiv(m_PrLayout.LegendeKopfNachHoehe (2*mm.Height()), m_iFontH, m_iFontOrg);

Point LEntriesPoint (CoOrd(Rc.Left() + lLeft), CoOrd(Rc.Top() - lTop - lLegTop));
Dimension LEntriesDim (CoOrd(Rc.Right()-Rc.Left() - (lLeft+lRight)),
		       CoOrd(Rc.Top()-Rc.Bottom() - (lTop+lBottom+lLegTop+lLegBottom)));
Point LEntryPoint (LEntriesPoint);	// linke untere Ecke der Einträge

// Font für Überschrift generieren, Größe der Überschrift holen
ResString rsArial (IDS_ARIAL, 20);
bool fBold = true;
bool fItalic = false;
bool fUnderline = false;
string strFontName = rsArial.Addr();
int iFamily = Swiss;
int iDummy = 0;

	m_PrLayout.LegendeKopfFont (iFamily, strFontName, iDummy, fBold, fItalic, fUnderline);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont locFont ((StdFamily)iFamily, Dimension(0, -m_iCapFontH), strFontName.c_str());
#else
Font locFont ((StdFamily)iFamily, Dimension(0, -m_iCapFontH), strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

	if (fBold) locFont.SetBold();
	if (fItalic) locFont.SetItalic();
	if (fUnderline)locFont.SetUnderline();
	locFont.Init();
	
HFONT hOldFont = (HFONT)SelectObject (hDC, locFont.Handle (API_FONT_HFONT));
Rectangle rcSize (LEntriesPoint, Dimension (LEntriesDim.Width(), 0));

// erstmal feststellen, wieviele Zeilen die Überschrift einnimmt, dann ausgeben
short iLineCnt = 0;

	Justify (hDC, hTargetDC, strLegCap.c_str(), NULL, (RECT *)&rcSize, ATLeft, false, &iLineCnt);
	rcSize.Bottom() = rcSize.Top();
	Justify (hDC, hTargetDC, strLegCap.c_str(), NULL, (RECT *)&rcSize, iLineCnt <= 1 ? ATCentre : ATLeft, true);
	SelectObject (hDC, hOldFont);

CoOrd iLine = rcSize.Top() - rcSize.Bottom();

	LEntryPoint.Y() -= CoOrd(iLine + lLegBottom);
	LEntriesDim.Height() -= CoOrd(iLine + lLegBottom);
	
// LegendenEinträge malen
Dimension LEntryDim (LEntriesDim.Width(), m_iFontH /*short((m_iFontH*800L)/700L)*/);
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont locFont1 ((StdFamily)m_iFamily, Dimension (0, -m_iFontH), m_strFontName.c_str());
#else
Font locFont1 ((StdFamily)m_iFamily, Dimension (0, -m_iFontH), m_strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
CTable tId (IDs().IdentTree());

	if (m_fBold) locFont1.SetBold();
	if (m_fItalic) locFont1.SetItalic();
	if (m_fUnderline) locFont1.SetUnderline();
	locFont1.Init();

	SelectObject (hDC, locFont1.Handle (API_FONT_HFONT));	
	TX_ASSERT(NULL != m_pItems);

	{
	CTable t (*m_pItems);
	char *pText = NULL;
			
		for (t.First(); t.Valid(); t.Next()) {
		CLegendInfoEntryLock l(t);
		
			if (!l) continue;

		// wenn nicht alle anzeigen und dieser gehört nicht dazu, dann weiter
		bool fShown = l -> isShown();
		
			if (!ShowAll() && !fShown) 
				continue;
			DELETE (pText);

		// LegendenEintrag an die Stelle setzen, die berechnet wurde
		long lONr = -1L;	// für alle Fälle
		long lIdent = -1L;
		short iIconWidth = 0;
		LEGENTRYTYPE rgLType = l -> isA();
		
			LEntryPoint.Y() = CoOrd(Rc.Top() - l -> GetPosition());
			switch (rgLType) {
			case LEGENTRYTYPE_OBJECT:
				{
				CLegendInfoObject * pLIO = (CLegendInfoObject *)(CLegendInfoEntry *)l;
					
					lONr = pLIO -> GetONr();
					if (ShowAreaOnly() && !DEX_isObjectVisible (lONr))
						continue;
					lIdent = DEX_GetObjIdentEx (lONr);
					iIconWidth = pLIO -> IconWidth();
				}
			// hier durchfallen

			case LEGENTRYTYPE_IDENT:
				{
					if (lIdent == -1L) {
					CLegendInfoIdent *pLId = (CLegendInfoIdent *)(CLegendInfoEntry *)l;

						lIdent = pLId -> GetIdent();
					}
					if (!tId.Find (&lIdent)) 
						continue;
						
				CIdentifikatorLock lId (tId);

					if (!lId) continue;
		
				// LegendeEinträge zeichnen (Textobjekte nicht in Legende)
					pText = l -> GetText();
				
					switch (l -> GetVType()) {
					case VT_Punkt:
						if (ShowAreaOnly() && !(lId -> isVisible (TPPunkt)))
							continue;
						GenLegEntry (*lId, LEntryPoint, LEntryDim, mm, VT_Punkt, fShown, pText, lONr);
						break;
						
					case VT_Linie:
						if (ShowAreaOnly() && !(lId -> isVisible (TPLinie)))
							continue;
						GenLegEntry (*lId, LEntryPoint, LEntryDim, mm, VT_Linie, fShown, pText, lONr);
						break;
						
					case VT_Flaeche:
						if (ShowAreaOnly() && !(lId -> isVisible (TPFlaeche)))
							continue;
						GenLegEntry (*lId, LEntryPoint, LEntryDim, mm, VT_Flaeche, fShown, pText, lONr);
						break;
						
					case VT_Text:
						if (rgLType != LEGENTRYTYPE_OBJECT)
							break;	// nur für Objekte
						GenLegEntry (*lId, LEntryPoint, LEntryDim, mm, VT_Text, fShown, pText, lONr, iIconWidth);
						break;

					default:
						continue;
					}
				}
				break;

			case LEGENTRYTYPE_TEXT:		// Zwischenüberschrift
				pText = l -> GetText();
				GenHeadLine (LEntryPoint, LEntryDim, mm, m_iFontH, pText);
				break;

			case LEGENTRYTYPE_SPACELINE:
				GenHeadLine (LEntryPoint, LEntryDim, mm, m_iFontH, "\\ ");
				break;

			default:
				continue;
			}
			DELETE(pText);
		}
	}
	SelectObject (hDC, hOldFont);

// ClippingRegion wieder freigeben
	if (hRgn) DeleteObject (hRgn);
	SetBkMode (hDC, OldBkMode);

// Palette zurücksetzen
	if (hPalette) SelectPalette (hDC, hOldPalette, false);

// alten DC wiederherstellen
	RestoreDC (hDC, -1);
}

///////////////////////////////////////////////////////////////////////////////
// ZwischenÜberschrift zeichnen
int CLegendeObjekt::GenHeadLine (Point &Pt, Dimension &Dim, Dimension &mm, int iFontH, LPCSTR pcText)
{
	if (NULL != pcText) {
	CHeadLineItem HI (m_pW, Pt, Dim, mm, m_PrLayout, iFontH, pcText);

		m_pW -> Draw(&HI);
		return HI.Height();
	} 
	else {
	CSpaceLineItem HI (m_pW, Pt, Dim, mm, m_PrLayout, iFontH);

		m_pW -> Draw(&HI);
		return HI.Height();
	}
}

///////////////////////////////////////////////////////////////////////////////
// LegendenEintra zeichnen
int CLegendeObjekt::GenLegEntry (
	CIdentifikator &ID, Point &Pt, Dimension &Dim, Dimension &mm, VisType iVTyp, bool fShown, 
	char *pText, long lONr, int iTextX)
{
	if (ID.hasVI (iVTyp)) {
	CLegendeItem LI (m_pW, m_rDBO, ID, iVTyp, Pt, Dim, mm, fShown, pText, lONr, m_PrLayout, iTextX, GetScaleMode());

		m_pW -> Draw (&LI);
		return LI.Height();		// nächster Eintrag
	}
	return 0;
}

// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster -----
Dimension GetDotsPerMM (HDC hDC, DoublePair *pDPair) 
{
HDC hDCloc;
DoublePair dimD(0, 0);

	if (NULL != hDC) 
		hDCloc = hDC;
	else
		hDCloc = GetDC (GetDesktopWindow());

	switch (GetMapMode (hDCloc)) {
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			if (0 != HorzSize && 0 != VertSize)
				dimD = DoublePair(double(HorzRes)/double(HorzSize), double(VertRes)/double(VertSize));
			else
				dimD = DoublePair(100, 100);	// default HIMETRIC
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		dimD = DoublePair(100, 100);
		break;
		
	case MM_LOMETRIC:	// [0.1 mm]
		dimD = DoublePair(10, 10);
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		dimD = DoublePair(1000.0/2540.0, 1000.0/2540.0);
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		dimD = DoublePair(100.0/2540.0, 100.0/2540.0);
		break;
		
	case MM_TWIPS:
		dimD = DoublePair(20.0/0.3176, 20.0/0.3176);
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) 
		ReleaseDC (GetDesktopWindow(), hDCloc);

	if (NULL != pDPair)
		*pDPair = dimD;

	return Dimension(ToCoOrd(dimD.X()), ToCoOrd(dimD.Y()));
}


// ----------------------------------------------------------------------------
// WrapperFunktionen für EntryBaum --------------------------------------------
bool CLegendeObjekt::isShown (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return false;
	return pLIE -> isShown();
}


bool CLegendeObjekt::isShown (WORD iOrder, bool fShown)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL || !(pLIE -> isShown() ^ fShown)) 
		return false;
		
// wenn neuer Wert eingestellt werden soll, dann dieses hier tun
	pLIE -> isShown (fShown);
	SetDirty();
	return true;
}

bool CLegendeObjekt::hasSpace (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;
	return pLIE -> hasSpace();
}

// Typ eines LegendenEintrages festellen --------------------------------------
LEGENTRYTYPE CLegendeObjekt::isA (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return LEGENTRYTYPE_UNKNOWN;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return LEGENTRYTYPE_UNKNOWN;
	return pLIE -> isA();
}

// VisTyp eines LegendenEintrages festellen -----------------------------------
VisType CLegendeObjekt::GetVType (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return VT_Default;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return VT_Default;	// nicht gefunden
	return pLIE -> GetVType();
}


// LegendenText setzen bzw. ändern --------------------------------------------
char *CLegendeObjekt::GetText (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return NULL;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return NULL;
	return pLIE -> GetText();
}


void CLegendeObjekt::SetText (WORD iOrder, char *pText)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE != NULL) {
		pLIE -> SetText (pText);
		SetDirty();
	}
}

bool CLegendeObjekt::ResetText (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE != NULL && pLIE -> CustomizedText()) {
		pLIE -> ResetText();
		SetDirty();
		return true;
	}
	return false;
}

bool CLegendeObjekt::CustomizedText (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return false;
	return pLIE -> CustomizedText();
}

// Ident eines Identifikatoreintrages festellen -------------------------------
long CLegendeObjekt::GetIdent (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return -1L;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return -1L;		// nicht gefunden
	return ((CLegendInfoIdent *)pLIE) -> GetIdent();
}

// Legende rücksetzen ---------------------------------------------------------
bool CLegendeObjekt::ResetLegend (char *pView)
{
	if (!DEX_GetROModeEx(HACTPROJECT))
	 	m_pItems -> ResetLegend (pView);	// rücksetzen
 	m_fDirty = false;
	return m_pItems -> FInit (IDs());		// neu initialisieren
}

// LegendenEintrag nach oben verschieben --------------------------------------
bool CLegendeObjekt::MoveUp (WORD &iActSel, bool fShowAll)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;
	
bool iRet = m_pItems -> MoveUp (iActSel, fShowAll);

	if (iRet) 
		SetDirty();
	return iRet;
}

// LegendenEintrag nach unten verschieben -------------------------------------
bool CLegendeObjekt::MoveDown (WORD &iActSel, bool fShowAll)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

bool iRet = m_pItems -> MoveDown (iActSel, fShowAll);

	if (iRet) 
		SetDirty();
	return iRet;
}

// Leerzeile einfügen/entfernen -----------------------------------------------
bool CLegendeObjekt::EnterSpace (WORD iActSel)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

	if (m_pItems -> hasSpace (iActSel, true))
		SetDirty();
	return true;
}

bool CLegendeObjekt::RemoveSpace (WORD iActSel)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

	if (m_pItems -> hasSpace (iActSel, false))
		SetDirty();
	return true;
}

// LegendenEintrag entfernen --------------------------------------------------
bool CLegendeObjekt::RemoveEntry (WORD iActSel)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

bool iRet = m_pItems -> RemoveEntry (iActSel);		// aus Baum entfernen

	if (iRet) 
		SetDirty();
	return iRet;
}

bool CLegendeObjekt::InsertHeadLine	(WORD iActSel, LPCSTR pcText, bool fInsertBefore)
{
// wenn nichts selektiert ist, dann wieder raus
bool fRet = m_pItems -> InsertHeadLine (iActSel, pcText, fInsertBefore);

	if (fRet)
		SetDirty();
	return fRet;
}

// Feststellen, welcher Eintrag vom MausKlick getroffen wurde -----------------
WORD CLegendeObjekt::FindEntry (short iPos)
{
	if (m_pItems == NULL) return USHRT_MAX;
	
// nur entsprechende LegEntries aus diesem Baum berücksichtigen
CTable t (*m_pItems);
		
	for (t.First(); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);
		
		if (!l) continue;
		
	// wenn nicht alle anzeigen und dieser gehört nicht dazu, dann weiter
		if (!ShowAll() && !l -> isShown()) continue;
		if (l -> HitTest (long(iPos))) 
			return l -> FGetWORD();		// lfde Nummer liefern
	}
	return USHRT_MAX;	// nichts gefunden	
}

bool CLegendeObjekt::GetEntrySize (WORD iOrder, Range &rR)
{
CLegendInfoEntry *pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;
	
	rR.Min() = CoOrd(pLIE -> GetPosition()) - m_iLine/6;
	rR.Max() = rR.Min() + CoOrd(pLIE -> GetHeight());
	return true;
}

bool CLegendeObjekt::GetEntryDesc (
	WORD iOrder, char *pBuffer, LEGENTRYTYPE &rrgType, VisType &rgVType, 
	INT_PTR &rlTarget, INT_PTR &rlMCode)
{
CLegendInfoEntry *pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return false;

	rlMCode = NULL;
	switch (rrgType = pLIE -> isA()) {
	case LEGENTRYTYPE_IDENT:
		rlTarget = ((CLegendInfoIdent *)pLIE) -> GetIdent();
		break;
		
	case LEGENTRYTYPE_OBJECT:
		rlTarget = ((CLegendInfoObject *)pLIE) -> GetONr();
		break;

	case LEGENTRYTYPE_SPACELINE:
	case LEGENTRYTYPE_TEXT:		// Zwischenüberschrift
		rlTarget = (INT_PTR)((CLegendInfoText *)pLIE) -> GetView();
		rlMCode = ((CLegendInfoText *)pLIE) -> GetMCode();
		break;

	default:
	case LEGENTRYTYPE_UNKNOWN:
		return false;
	}
	*pBuffer = '\0';
	rgVType = pLIE -> GetVType();
	return FormatString (pBuffer, pLIE);
}

