// Memberfuntktionen fuer die Legende -----------------------------------------
// File: LEGENDE.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>
#include <funcs03.h>

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

extern bool LegendeCFlag;
extern HPALETTE hPalette;

_TRIAS02_ENTRY bool EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);

// Einträge der Legende -------------------------------------------------------
CLegendeItem :: CLegendeItem (pWindow pW, DatenBasisObjekt &rDBO, CIdentifikator &rId, 
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
		m_pText = StrDup (pText);
	m_lONr = lONr;
		
// Größe der beiden Bereiche berechnen
	m_Pt = Pt;
	if (iTextX == 0) {
	long lWidth = m_rCache.KastenBreite ((400L*Dim.Width())/2500L);
	long lMiddle = m_rCache.KastenZwischenBreite (2*m_DotsPerMM.Width());

		m_TextX = (CoOrd)(Pt.X() + lWidth + lMiddle);
	} else
		m_TextX = Pt.X() + iTextX;
}

CLegendeItem :: ~CLegendeItem (void) 
{
	DELETE (m_pText);
}	


// Zeichnen eines LegendenEintrages -------------------------------------------
void CLegendeItem :: Draw (void) 
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
		dimSign.Height() = CoOrd((dimSign.Height()*m_rCache.KastenHoehe(100))/100L);
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
Point pt = m_Pt;
Rectangle rc = m_pW -> CanvasRect();

	pt.Y() = rc.Top()-rc.Bottom()-pt.Y();

HRGN hRgn = CreateRectRgn (pt.X(), pt.Y(), pt.X()+rDim.Width(), pt.Y()+rDim.Height());

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
void CLegendeItem :: LDrawPunkt (Dimension &Dim) 
{
// wenn ein Objekt gezeichnet werden soll, dann hier in die Runde rufen
short iDrawResult = DO_UnChanged;
VisInfo *pOldVI = NULL;

	if (m_lONr != -1) {
	switch (m_ID.DType() & DT_DrawingMask) {
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
	}

// MittelPunktsKoordinaten des PunktSymboles bestimmen
Point Centre (m_Pt.X()+Dim.Width()/2, m_Pt.Y()-Dim.Height()/2);
Dimension PtSize = ((PVisInfo *)(&m_ID.VI(m_iVTyp))) -> Size();
double res = (GetGeoDBVersion() >= VERSION05000004) ? 100L : 10L;

	if (GetScaleMode())	res *= DBO().M();

CoOrd logPX = (CoOrd)(((long)m_DotsPerMM.Width() * (long)PtSize.Width()) / res);
CoOrd logPY = (CoOrd)(((long)m_DotsPerMM.Height() * (long)PtSize.Height()) / res);

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
void CLegendeItem :: LDrawLinie (Dimension &Dim) 
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
	if (GetGeoDBVersion() >= VERSION05000004) {
	double res = 100.0;

		if (GetScaleMode()) res *= DBO().M();
		locWidth = long( ( (double(locWidth) * double(m_DotsPerMM.Width())) / res ) + 0.5);
	} else {
	double res = 1.0;

		if (GetScaleMode()) res = DBO().M();
		locWidth = long(locWidth / res + 0.5);
	}

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
	for (short iCnt = 0; iCnt < pEPen -> iCnt(); iCnt++) {
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
void CLegendeItem :: LDrawFlaeche (Dimension &Dim) 
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
Point Begin (CoOrd(m_Pt.X()), CoOrd(m_Pt.Y() - (7*Y)/8));
Dimension Size (CoOrd(Dim.Width()), CoOrd(Dim.Height() - (2*Y)/8));
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

	Dimension dim = pBmp -> GetSize();
	Rectangle R (Begin.Y(), Begin.X(), Begin.Y()+Size.Height(), Begin.X()+Size.Width());

		for (long y = R.Top()+1; y <= R.Bottom()+1; y += dim.Height()) {
			for (long x = R.Left(); x <= R.Right(); x += dim.Width()) {
			long dX = min(x+dim.Width(), R.Right()) - x;
			long dY = min(y+dim.Height(), R.Bottom()) - y;

				::BitBlt (hDC, x, y, dX, dY, hDCSrc, 0, 0, MYROPCODE);
			}
		}

		::SelectObject (hDCSrc, hOldBmp);
		::DeleteDC (hDCSrc);

	// hier duchfallen und Rahmen mit zeichnen lassen
		::SetTextColor (hDC, crOldTextColor);
		::SelectObject (hDC, GetStockObject (NULL_BRUSH));
	} 

// Rahmen bzw. nicht transparente Füllmuster zeichnen
	{
	// evtl. neuen Stift setzen
	HPEN hOldPen;
	short locWidth = m_ID.FrameWidth();

	// neuerdings Linienbreite in 1/100 mm
		if (GetGeoDBVersion() >= VERSION05000004)
			locWidth = (short)(((long)locWidth * (long)m_DotsPerMM.Width()) / 100L);

	pPen pP = m_ID.GetPen (VT_Flaeche, locWidth);

		if (pP != NULL)
			hOldPen = (HPEN)SelectObject (hDC, pP -> Handle());
		else 
			hOldPen = (HPEN)SelectObject (hDC, GetStockObject (BLACK_PEN));

		crOldBkCol = ::SetBkColor (hDC, (COLORREF &)m_ID.GetBkColor());
		oldBkMode = ::SetBkMode (hDC, m_ID.isOpaque() ? OPAQUE : TRANSPARENT);

		DrawRectangle (hDC, Begin.X(), Begin.Y(), Begin.X()+Size.Width(), Begin.Y()+Size.Height()+1);

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
bool CLegendeItem :: LDrawText (Dimension &Dim)
{
	if (m_lONr != -1L) {		// nur ObjektTexte
	HDC hDC = Handle (API_DRAWOBJECT_HDC);	// Rechteck zeichnen
	
//		if (!DEX_isObjectVisible (m_lONr))
//			return false;		// Objekt nicht sichtbar

	char *pBuffer = new char [_MAX_PATH];

		if (pBuffer == NULL) return false;	// Fehler
			
	long lIconWidth = m_TextX - m_Pt.X();	// reale Breite des Bildchens
		
		HandleIcon (hDC, DBO(), m_ID, m_lONr, TPText, m_Pt, pBuffer, 
			    m_Dim.Height(), lIconWidth, true);

		DELETE (pBuffer);		// Speicher freigeben
	} 
	
return true;
}


// Beschreibenden Text für einen LegendenEintrag ausgeben ---------------------
void CLegendeItem :: LDrawDescText (Dimension &dimSign) 
{
// nur zeichnen, wenn nicht Begleitobjekt
//	if (!m_ID.hasVI(m_iVTyp) || m_ID.VI(m_iVTyp).isA() == VT_Text)
//		return;

// auszugebenden Text besorgen
PBD_Ident *pPBDId = NULL;
char *szText = m_pText;

	if (szText == NULL || *szText == '\0') {
		pPBDId = new PBD_Ident (&PbdDB(), m_ID.Id());	// PBD-Eintrag lesen
		if (pPBDId) {
			szText = pPBDId -> GetLangText();	// KurzText holen
			if (szText == NULL) szText = pPBDId -> GetKurzText();
		} 
		if (szText == NULL || *szText == '\0')
			szText = "\\ ";		// Leerzeile ausgeben
	}
	
// wenn dieser Eintrag nicht angezeigt ist, dann grau kennzeichnen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
COLORREF cr = GetTextColor (hDC);

	if (!m_fShown) SetTextColor (hDC, GetSysColor (COLOR_GRAYTEXT));

// Text ausgeben
Rectangle rc (Point (m_TextX, m_Pt.Y()), 
	      Dimension (m_Dim.Width() - (m_TextX-m_Pt.X()), 0));

short iLineCnt = 0;	// ZeilenAnzahl bestimmen
CoOrd iLine = Justify (hDC, NULL, szText, NULL, (RECT *)&rc, ATLeft, false, &iLineCnt);

	if (dimSign.Height() > iLine) {
		rc.Top() -= (dimSign.Height())/16;
		if (iLineCnt <= 1) 	// an Unterkante ausrichten
			rc.Top() -= ((7*dimSign.Height())/8 - iLine);
	} else
		rc.Top() += (dimSign.Height())/8;

	rc.Bottom() = rc.Top();
	Justify (hDC, hDC, szText, NULL, (RECT *)&rc, ATLeft, true);

	SetTextColor (hDC, cr);

long lTop = m_rCache.KastenVorHoehe (iLine/12);
long lBottom = m_rCache.KastenNachHoehe (iLine/12);

	m_Dim.Height() = CoOrd(rc.Top()-rc.Bottom() + (lTop+lBottom));	// aktuelle Höhe
	
// Speicher freigeben
	DELETE (pPBDId);
}


// ----------------------------------------------------------------------------
// Memberfunktionen für gesamte Legende ---------------------------------------
Dimension GetDotsPerMM (HDC hDC);

CLegendeObjekt *CLegendeObjekt :: CreateInstance (pWindow pW, DatenBasisObjekt &rDBO,
						  Rectangle *pRc, PrinterPars *pPP) 
{
CLegendeObjekt *pLO = new CLegendeObjekt (pW, rDBO);

	if (pLO == NULL || !pLO -> FInit (pRc, pPP)) {
		DELETE (pLO);
		return NULL;
	}
	
return pLO;
}


bool CLegendeObjekt :: FInit (Rectangle *pRc, PrinterPars *pPP)
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

	m_pParser = CLegEntryParser :: CreateInstance();
	if (m_pParser == NULL) return false;

	m_pBuffer = new char [_MAX_PATH];
	if (m_pBuffer == NULL) return false;

// Baum der darzustellenden LegendenEinträge anlegen
	m_pItems = CLegendInfo :: CreateInstance (*m_pParser, IDs(), m_lMCode);
	if (m_pItems == NULL) return false;
	
return true;
}

CLegendeObjekt :: CLegendeObjekt (pWindow pW, DatenBasisObjekt &rDBO)
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
	m_lMCode = GetHeaderMCode (false, IDS_LEGENDINFOMCODE); 
	
// Parser generieren und initialisieren
	m_pItems = NULL;
	m_pBuffer = NULL;
	m_pParser = NULL;
}

CLegendeObjekt :: ~CLegendeObjekt (void) 
{
	DELETE (m_pR);
	DELETE (m_pItems);
	DELETE (m_pParser);
	DELETE (m_pBuffer);
}


bool CLegendeObjekt :: RefreshLegend (void)
{
	if (m_pItems == NULL) return false;
	if (isDirty()) {
		if (!DEX_GetROMode())
			SaveLegend();
		m_fDirty = false;
	}
	
return m_pItems -> FInit (IDs());
}

// setzen der Papierabmessungen (DruckSpiegel) --------------------------------
void CLegendeObjekt :: SetBaseValues (Rectangle &rRC, HDC hDC)
{
Dimension mm = GetDotsPerMM (hDC);
long lWidth = ((rRC.Right()-rRC.Left())*100L)/mm.Width();
long lHeight = ((rRC.Top()-rRC.Bottom())*100L)/mm.Height();

	m_PrLayout.SetBaseValues (lWidth, lHeight);
}

bool CLegendeObjekt :: GetViewDesc (string &rstr)
{
VIEWDESC VD;
char cbBuffer[_MAX_PATH];

	VD.m_dwSize = sizeof(VIEWDESC);
	VD.m_pView = NULL;		// aktuelle Sicht verwenden
	VD.m_pDesc = cbBuffer;
	VD.m_iLen = _MAX_PATH;
	
	if (!DEX_GetViewDescription (VD)) {	// nichts gegeben
	ResString rsLegCap (IDS_LEGENDECAP, 15);

		rstr = rsLegCap.Addr();
		return true;
	}
	rstr = cbBuffer;

return true;
}

bool CLegendeObjekt :: AddObject (long lONr)
{
	if (m_pItems == NULL) return false;

WORD iOrder = USHRT_MAX;
bool fRet = m_pItems -> AddObject (lONr, iOrder);

	if (fRet) 
		m_fDirty = true;
	return fRet;
}

// Größe der Legende berechnen/Font dimensionieren ----------------------------
Dimension CLegendeObjekt :: FitLegendSize (Rectangle *pR, HDC hDefDC)
{
long lWidth = pR->Right() - pR->Left();	// Breite ist fest
long lHeight = 0;					// soll berechnet werden
HDC hDC = NULL;
HWND hWnd = NULL;

	if (hDefDC) 
		hDC = hDefDC;
	else {
		hWnd = m_pW -> Handle (API_WINDOW_HWND);
		hDC = ::GetDC (hWnd);
	}
	
Dimension mm = GetDotsPerMM (hDC);
short iDelta = (short)(((long)mm.Height()*3176L)/20000L);	// 0.5pt Delta
bool fContinue;

	if (iDelta == 0) iDelta = 1;

ResString rsArial (IDS_ARIAL, 20);

	m_iFontH = int(5*mm.Height());		// mit 5mm anfangen
	m_fBold = false;
	m_fItalic = false;
	m_fUnderline = false;
	m_strFontName = rsArial.Addr();
	m_iFamily = Swiss;

	m_PrLayout.KastenFont (m_iFamily, m_strFontName, m_iFontH, 
				   m_fBold, m_fItalic, m_fUnderline);
	m_iFontOrg = m_iFontH;

long lLeft = m_PrLayout.KastenVorBreite (2*mm.Width());
long lRight = m_PrLayout.KastenNachBreite (2*mm.Width());

	lWidth -= (lLeft + lRight);		// Breite des Textbereiches
	
// Font ausgehend von einer AnfangsGröße solange kleiner machen, bis die
// ganze Legende im vorgegebenen Bereich Platz hat

	do {		// Font auswählen
	Font locFont ((StdFamily)m_iFamily, Dimension (0, -m_iFontH), m_strFontName.c_str());

		if (m_fBold) locFont.SetBold();
		if (m_fItalic) locFont.SetItalic();
		if (m_fUnderline) locFont.SetUnderline();
		locFont.Init();
		
	HFONT hOldFont = (HFONT)SelectObject (hDC, locFont.Handle (API_FONT_HFONT));
	
	// für diesen Font Größe generieren, Gesamthöhe berechnen		
		lHeight = m_PrLayout.LegendeVorHoehe (0);	// neu initialisieren
		m_iIdCnt = 0;			// Zähler der Einträge

	// Höhe der gesamten Legende berechnen
		fContinue = !GetLegendSize (hDC, lWidth, mm, m_iFontH, true, lHeight);
		lHeight += m_PrLayout.LegendeNachHoehe (0);

	// Font wieder abmelden
		SelectObject (hDC, hOldFont);
		if ((m_iFontH -= iDelta) <= 0)
			break;		// Font zu klein: abbrechen
	} while (fContinue || lHeight > pR->Top() - pR->Bottom());
	m_iFontH += iDelta;	// da war einmal zuviel da
		
// aufräumen
	if (NULL == hDefDC) ::ReleaseDC (hWnd, hDC);

	if (m_iFontH > 0) 
		return Dimension (pR->Right() - pR->Left(), short(lHeight));
	
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
Dimension CLegendeObjekt :: GetRealSize (Rectangle *pR, bool &fFitWidth)
{
HWND hWnd = m_pW -> Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);
Dimension mm = GetDotsPerMM (hDC);
//long lWidth = ((pR->Right() - pR->Left()) * 400L)/500L;	// Breite ist fest
long lWidth = pR->Right() - pR->Left();	// Breite ist fest
long lHeight = 2*mm.Height();				// soll berechnet werden

	m_iFontH = short(5*mm.Height());			// alles 5mm groß
	m_iFontOrg = m_iFontH;
	m_iIdCnt = 0;		// Zähler der Einträge

ResString rsArial (IDS_ARIAL, 20);
Font locFont (Swiss, Dimension (0, -m_iFontH), rsArial);

	locFont.Init();
		
// für diesen Font Größe generieren
HFONT hOldFont = (HFONT)SelectObject (hDC, locFont.Handle (API_FONT_HFONT));

// Höhe der gesamten Legende berechnen
	lWidth -= 4*mm.Width();		// Rand lassen
	fFitWidth = GetLegendSize (hDC, lWidth, mm, m_iFontH, false, lHeight);
	
// Font wieder abmelden, aufräumen
	SelectObject (hDC, hOldFont);
	::ReleaseDC (hWnd, hDC);

return Dimension (pR->Right() - pR->Left(), short(lHeight));
}


// Höhe der gesamten Legende mit der aktuellen FontGröße berechnen ------------
bool CLegendeObjekt :: GetLegendSize (HDC hDC, long lWidth, Dimension &mm, 
			      short iFontH, bool fBreak, long &rlHeight)
{
// Überschrift reinrechnen
string strLegCap;

	GetViewDesc (strLegCap);

ResString rsArial (IDS_ARIAL, 20);
int iFontHL = (int)((iFontH*700L)/500L);	// Überschrift ist 6/5 des anderen Textes
bool fBold = true;
bool fItalic = false;
bool fUnderline = false;
string strFontName = rsArial.Addr();
int iFamily = Swiss;
int iDummy = 0;

	m_PrLayout.LegendeKopfFont (iFamily, strFontName, iDummy, 	
				    fBold, fItalic, fUnderline);

Font CapFont ((StdFamily)iFamily, Dimension(0, -iFontHL), strFontName.c_str());
	
	if (fBold) CapFont.SetBold();
	if (fItalic) CapFont.SetItalic();
	if (fUnderline) CapFont.SetUnderline();
	CapFont.Init();
	
HFONT hOldFont = (HFONT)SelectObject (hDC, CapFont.Handle (API_FONT_HFONT));
Rectangle rcSize (Point(), Dimension (short(lWidth), 0));
CoOrd iLine = Justify (hDC, hDC, strLegCap.c_str(), NULL, (RECT *)&rcSize, ATCentre, false);

	SelectObject (hDC, hOldFont);
	rlHeight += rcSize.Top() - rcSize.Bottom();

long lLegTop = (m_PrLayout.LegendeKopfVorHoehe(2*mm.Height())*iFontH)/m_iFontOrg;
long lLegBottom = (m_PrLayout.LegendeKopfNachHoehe(iLine)*iFontH)/m_iFontOrg;

	rlHeight += lLegTop + lLegBottom;

// sonstige LegendenEinträge dazurechen
CTable tId (IDs().IdentTree());
bool fFitWidth = true;

	lWidth -= m_PrLayout.KastenZwischenBreite (2*mm.Width());
	lWidth -= m_PrLayout.KastenBreite ((lWidth*400L)/2500L);

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
			if (!ShowAll() && !l -> isShown()) continue;

		long lONr = -1L;
		long lIdent = -1L;
		LEGENTRYTYPE rgLType = l -> isA();
					
			switch (rgLType) {
			case LEGENTRYTYPE_OBJECT:
				lONr = ((CLegendInfoObject *)(CLegendInfoEntry *)l) -> GetONr();
				lIdent = DEX_GetObjIdent (lONr);
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
					if (!GetIdentEntrySize (hDC, *lId, 
						rlHeight, lWidth, fFitWidth, fBreak,
						VTypToBits (l -> GetVType()),
						pText, lONr, &iNewWidth))
					{
						DELETE (pText);
						return false;	// abbrechen, wenn zu groß
					}
//					rlHeight += lEBottom;

				// Höhe des Eintrages merken
					if (l -> hasSpace()) 	// Leerzeile einfügen
						rlHeight += m_PrLayout.LeerzeileHoehe ((iLine*120L)/100L);

					l -> SetHeight (rlHeight - lPosition);

				// wenn Objekteintrag großes Bildchen hat
					if (iNewWidth && rgLType == LEGENTRYTYPE_OBJECT) {
					long lMiddle = m_PrLayout.KastenZwischenBreite (2*mm.Width());

						((CLegendInfoObject *)(CLegendInfoEntry *)l) -> IconWidth() = iNewWidth + short(lMiddle);
					}
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

bool CLegendeObjekt :: GetIdentEntrySize (
		HDC hDC, CIdentifikator &rId, long &rlHeight, long lWidth,
		bool &rfFitWidth, bool fBreak, short iBits, char *pText, 
		long lONr, short *piNewWidth)
{
long lKasten = m_PrLayout.KastenBreite ((lWidth*400L)/2500L);	// Standardbreite des Bildchens
short fVisible = 0;
// wenn objektspezifisch Visualisiert werden soll
short iIconHeight = 0;	// Höhe des Bildchens
bool fObject = false;

	if (lONr != -1L) {
		fVisible = DEX_isObjectVisible (lONr);
		if (ShowAreaOnly() && !fVisible) 
			return true;	// Objekt nicht sichtbar

		fVisible = iBits;		// ObjectTyp speichern
				
	long lIconWidth = 0;			// reale Breite des Bildchens
	Point pt (0, 0);			// nur Größe bestimmen
	
		iIconHeight = HandleIcon (hDC, DBO(), rId, lONr, iBits, 
					  pt, m_pBuffer, 0, lIconWidth, false);

		if (lIconWidth > lKasten) {	// breiter als vorgesehen
			lWidth -= (lIconWidth - lKasten);
			if (piNewWidth) *piNewWidth = short(lIconWidth);
		}
		fObject = true;
	} else {	// Identifikatorweise
	// Objekte außerhalb des Bildausschnittes nicht zeichnen
 		fVisible = rId.isVisible (iBits);	// sind gesuchte Objekttypen sichtbar 
		if (ShowAreaOnly() && !fVisible) 
			return true;	// gehört nicht dazu
	}
		
short iT = GetItemHeight (hDC, rId, lWidth, pText);	// Größe des Beschreibenden Textes
			
	if (iT < 0) { 	// ein Wort ist länger als gesamte Zeile
		rfFitWidth = false;
		if (fBreak) 
			return false;		// gleich weitermachen
		iT = -iT;	// als Zeilenhöhe auswerten
	}

short fToPaint = rId.toPaint();
long lItemTop = (m_PrLayout.KastenVorHoehe(m_iLine/12)*m_iFontH)/m_iFontOrg;
long lItemBottom = (m_PrLayout.KastenNachHoehe(m_iLine/12)*m_iFontH)/m_iFontOrg;

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
		rlHeight += max ((long)iT, (m_iLine*m_PrLayout.KastenHoehe(100))/100L);
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


short CLegendeObjekt :: GetItemHeight (HDC hDC, CIdentifikator &rCId, 
				       long lWidth, char *pText)
{
// anzuzeigenden Text besorgen
PBD_Ident *pPBDId = NULL;
char *szText = pText;

	if (szText == NULL || *szText == '\0') {
		pPBDId = new PBD_Ident (&PbdDB(), rCId.Id());	// PBD-Eintrag lesen
		if (pPBDId) {
			szText = pPBDId -> GetLangText();	// KurzText holen
			if (szText == NULL) szText = pPBDId -> GetKurzText();
		} 
		if (szText == NULL || *szText == '\0')
			szText = "\\ ";				// kein Text gegeben
	}
	
Rectangle rcSize (Point(), Dimension (short(lWidth), 0));
CoOrd iLine = Justify (hDC, hDC, szText, NULL, (RECT *)&rcSize, ATLeft, false);
CoOrd iHeight = rcSize.Top()-rcSize.Bottom();

	m_iLine = short(iLine);	// aktuelle ZeilenHöhe merken
	DELETE (pPBDId);	// Speicher freigeben
	
// ein negativer Wert weist darauf hin, daß ein Wort länger als die Zeile ist
	return short((rcSize.Right() > short(lWidth)) ? -iHeight : iHeight);
}


short HandleIcon (HDC hDC, DatenBasisObjekt &rDBO, CIdentifikator &rId, 
		long lONr, short iBits, Point pt, char *pBuffer, CoOrd iHeight, 
		long &rlIconWidth, bool fDraw)
{
// ObjektTypSpezifisch entscheiden
	if (!(iBits & TPText)) return 0;	// alle anderen Typen ordnen sich ein
	
// Text besorgen
GETTEXTDATA GTD;

	memset (&GTD, 0, sizeof(GETTEXTDATA));
	GTD.m_dwSize = sizeof(GETTEXTDATA);
	GTD.m_lONr = lONr;
	GTD.m_pText = pBuffer;
	GTD.m_iLen = _MAX_PATH;
	if (!DEX_GetTextObjectText(GTD) || GTD.m_iLen == 0) return 0;
	
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

Dimension mm = GetDotsPerMM (hDC);
Dimension locSize = rId.Size(VT_Text);
double dDelta = (locSize.Height() > 0) ? 0.5 : -0.5;
CoOrd PtX = (CoOrd)(((double)mm.Width() * (double)(locSize.Width()) * 0.3176) + dDelta);
CoOrd PtY = (CoOrd)(((double)mm.Height() * (double)(locSize.Height()) * 0.3176) + dDelta);
Dimension FontSize (PtX, PtY);
Font *pF = rId.GetFont (FontSize);
HFONT hFont = 0;

	if (pF) {
		pF -> Init();		// Font initialisieren
		hFont = (HFONT)SelectObject (hDC, pF -> Handle (API_FONT_HFONT));
	}

// Textgröße bestimmen --------------------------------------------------------
// umschließendes Rechteck vorbereiten, Höhe berechnen lassen
Point locPt (pt.X(), pt.Y()-iHeight);
Rectangle rc (locPt, Dimension (0, 0));	
short iLineCnt = 0;		// Anzahl der Zeilen
CoOrd iH = Justify (hDC, NULL, pBuffer, (POINT *)&locPt, (RECT *)&rc, 
		    ATLeft, false, &iLineCnt);

	if (fDraw) {	// sonstige Attribute setzen
	Color locC = rId.GetColor (VT_Text);
	COLORREF oC = SetTextColor (hDC, *(COLORREF *)&locC);
	int oldBkMode = SetBkMode (hDC, TRANSPARENT);	// Text auf jeden Fall Transparent
	
	// evtl. Textrahmen zeichnen
		if (rId.FrameMode()) {	
		long lAssocON = AssociatedObjekt (rDBO.DB().DBDesc(), lONr);
		COLORREF crC;
	
			if (!rId.BKMode (VT_Text) || lAssocON == 0) 
				crC = RGB (255, 255, 255);
			else {
			// Farbe des Rechtecks von Bezugsobjekt holen
				crC = DEX_GetObjColor (labs(lAssocON));
				if (hPalette)
					crC = PALETTEINDEX (GetNearestPaletteIndex (hPalette, crC));
			}
	
		HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, CreateSolidBrush (crC));
	
			oldBkMode = SetBkMode (hDC, OPAQUE);
			if (iLineCnt == 1) {	// rechteck zentrieren
			short iDelta = short(rlIconWidth - (rc.Right() - rc.Left()))/2;
				
				rc.Left() += iDelta;
				rc.Right() += iDelta;
			}
			rc.Top() += iH;
			
			if (rId.RoundFrame()) {
			TEXTMETRIC TM;
			short iD = 0;
			
				GetTextMetrics (hDC, &TM);
				iD = TM.tmAveCharWidth / 2;
				::RoundRect (hDC, rc.Left()-iD, rc.Top()+iD, 
						  rc.Right()+iD, rc.Bottom()-iD,
						  4*iD, 4*iD);
			} else 
				DrawRectangle (hDC, rc.Left(), rc.Top(), 
						  rc.Right(), rc.Bottom());

			DeleteObject (SelectObject (hDC, hOldBr));
			SetBkMode (hDC, oldBkMode);
		}
	
	// Einzeilige Texte zentrieren, sonst normal linksbündig
		rc = Rectangle (locPt, Dimension (short(rlIconWidth), 0));
		Justify (hDC, NULL, pBuffer, (POINT *)&locPt, (RECT *)&rc, 
			 iLineCnt <= 1 ? ATCentre : ATLeft, true);
	
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

return short((rc.Top() - rc.Bottom()) + iH);		// liefert Höhe zurück
}

// ----------------------------------------------------------------------------
// Legende zeichnen -----------------------------------------------------------
void CLegendeObjekt :: DrawEx (DWORD dwData) 
{
// ClippingBereich für Legende setzen
HDC hDC = Handle (API_DRAWOBJECT_HDC);

	SaveDC (hDC);	// alten DC merken

// ClippingRechteck muß explizit gesetzt werden (nur wenn vorgegeben)
HRGN hRgn = NULL;

	if (dwData) hRgn = CreateRectRgnIndirect ((RECT *)dwData);
	if (hRgn) SelectClipRgn (hDC, hRgn);

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
Dimension mm = GetDotsPerMM (Handle (API_TARGET_HDC));
string strLegCap;

	GetViewDesc (strLegCap);

// Formatierung bestimmen
long lLeft = m_PrLayout.KastenVorBreite (2*mm.Width());
long lRight = m_PrLayout.KastenNachBreite (2*mm.Width());

long lTop = m_PrLayout.LegendeVorHoehe (0);
long lBottom = m_PrLayout.LegendeNachHoehe (0);
long lLegTop = (m_PrLayout.LegendeKopfVorHoehe (2*mm.Height())*m_iFontH)/m_iFontOrg;
long lLegBottom = (m_PrLayout.LegendeKopfNachHoehe (2*mm.Height())*m_iFontH)/m_iFontOrg;

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

	m_PrLayout.LegendeKopfFont (iFamily, strFontName, iDummy, 	
				    fBold, fItalic, fUnderline);

int iFontHL = (int)((m_iFontH*700L)/500L);
Font locFont ((StdFamily)iFamily, Dimension(0, -iFontHL), strFontName.c_str());

	if (fBold) locFont.SetBold();
	if (fItalic) locFont.SetItalic();
	if (fUnderline)locFont.SetUnderline();
	locFont.Init();
	
HFONT hOldFont = (HFONT)SelectObject (hDC, locFont.Handle (API_FONT_HFONT));
Rectangle rcSize (LEntriesPoint, Dimension (LEntriesDim.Width(), 0));

// erstmal feststellen, wieviele Zeilen die Überschrift einnimmt, dann ausgeben
short iLineCnt = 0;

	Justify (hDC, NULL, strLegCap.c_str(), NULL, (RECT *)&rcSize, 
		 ATLeft, false, &iLineCnt);
	rcSize.Bottom() = rcSize.Top();
	Justify (hDC, hDC, strLegCap.c_str(), NULL, (RECT *)&rcSize, 
		 iLineCnt <= 1 ? ATCentre : ATLeft, true);
	SelectObject (hDC, hOldFont);

CoOrd iLine = rcSize.Top() - rcSize.Bottom();

	LEntryPoint.Y() -= CoOrd(iLine + lLegBottom);
	LEntriesDim.Height() -= CoOrd(iLine + lLegBottom);
	
// LegendenEinträge malen
Dimension LEntryDim (LEntriesDim.Width(), m_iFontH /*short((m_iFontH*800L)/700L)*/);
Font locFont1 ((StdFamily)m_iFamily, Dimension (0, -m_iFontH), m_strFontName.c_str());
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
		
			if (!ShowAll() && !fShown) continue;

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
					lIdent = DEX_GetObjIdent (lONr);
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
					DELETE (pText);
					pText = l -> GetText();
				
					switch (l -> GetVType()) {
					case VT_Punkt:
						if (ShowAreaOnly() && !(lId -> isVisible (TPPunkt)))
							continue;
						GenLegEntry (*lId, LEntryPoint, 
							     LEntryDim, mm, 
							     VT_Punkt, fShown,
							     pText, lONr);
						break;
						
					case VT_Linie:
						if (ShowAreaOnly() && !(lId -> isVisible (TPLinie)))
							continue;
						GenLegEntry (*lId, LEntryPoint, 
							     LEntryDim, mm, 
							     VT_Linie, fShown,
							     pText, lONr);
						break;
						
					case VT_Flaeche:
						if (ShowAreaOnly() && !(lId -> isVisible (TPFlaeche)))
							continue;
						GenLegEntry (*lId, LEntryPoint, 
							     LEntryDim, mm, 
							     VT_Flaeche, fShown,
							     pText, lONr);
						break;
						
					case VT_Text:
						if (rgLType != LEGENTRYTYPE_OBJECT)
							break;	// nur für Objekte
						GenLegEntry (*lId, LEntryPoint, 
							     LEntryDim, mm, 
							     VT_Text, fShown,
							     pText, lONr, iIconWidth);
						break;

					default:
						continue;
					}
					DELETE (pText);
				}
				break;
				
			default:
				continue;
			}
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


short CLegendeObjekt :: GenLegEntry (CIdentifikator &ID, Point &Pt, 
		Dimension &Dim, Dimension &mm, VisType iVTyp, bool fShown, 
		char *pText, long lONr, short iTextX)
{
	if (ID.hasVI (iVTyp)) {
	CLegendeItem LI (m_pW, m_rDBO, ID, iVTyp, Pt, Dim, mm, fShown, 
			 pText, lONr, m_PrLayout, iTextX, GetScaleMode());

		m_pW -> Draw (&LI);
		return short(LI.Height());		// nächster Eintrag
	}
	
return 0;
}


// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster -----
Dimension GetDotsPerMM (HDC hDC) 
{
HDC hDCloc;
Dimension dimD (0, 0);

	if (hDC != NULL) hDCloc = hDC;
	else		 hDCloc = GetDC (GetDesktopWindow());

	switch (GetMapMode (hDCloc)) {
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			if (0 != HorzSize && 0 != VertSize)
				dimD = Dimension (HorzRes/HorzSize, VertRes/VertSize);
			else
				dimD = Dimension (100, 100);	// default HIMETRIC
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		dimD = Dimension (100, 100);
		break;
		
	case MM_LOMETRIC:	// [0.1 mm]
		dimD = Dimension (10, 10);
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		dimD = Dimension (40, 40);
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		dimD = Dimension (4, 4);
		break;
		
	case MM_TWIPS:
		dimD = Dimension (57, 57);
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) ReleaseDC (GetDesktopWindow(), hDCloc);

return dimD;
}


// ----------------------------------------------------------------------------
// WrapperFunktionen für EntryBaum --------------------------------------------
bool CLegendeObjekt :: isShown (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;
	
return pLIE -> isShown();
}


bool CLegendeObjekt :: isShown (WORD iOrder, bool fShown)
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


bool CLegendeObjekt :: hasSpace (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;
	
return pLIE -> hasSpace();
}


// Typ eines LegendenEintrages festellen --------------------------------------
LEGENTRYTYPE CLegendeObjekt :: isA (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return LEGENTRYTYPE_UNKNOWN;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) 
		return LEGENTRYTYPE_UNKNOWN;
	
return pLIE -> isA();
}

// VisTyp eines LegendenEintrages festellen -----------------------------------
VisType CLegendeObjekt :: GetVType (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return VT_Default;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return VT_Default;	// nicht gefunden

return pLIE -> GetVType();
}


// LegendenText setzen bzw. ändern --------------------------------------------
char *CLegendeObjekt :: GetText (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return NULL;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return NULL;
	
return pLIE -> GetText();
}


void CLegendeObjekt :: SetText (WORD iOrder, char *pText)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE != NULL) {
		pLIE -> SetText (pText);
		SetDirty();
	}
}

bool CLegendeObjekt :: ResetText (WORD iOrder)
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

bool CLegendeObjekt :: CustomizedText (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) return false;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;

return pLIE -> CustomizedText();
}

// Ident eines Identifikatoreintrages festellen -------------------------------
long CLegendeObjekt :: GetIdent (WORD iOrder)
{
	if (m_pItems == NULL || iOrder == USHRT_MAX) 
		return -1L;
	
CLegendInfoEntry * pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return -1L;		// nicht gefunden
	
return ((CLegendInfoIdent *)pLIE) -> GetIdent();
}

// Legende rücksetzen ---------------------------------------------------------
bool CLegendeObjekt :: ResetLegend (char *pView)
{
	if (!DEX_GetROMode())
	 	m_pItems -> ResetLegend (pView);	// rücksetzen
 	m_fDirty = false;

return m_pItems -> FInit (IDs());		// neu initialisieren
}

// LegendenEintrag nach oben verschieben --------------------------------------
bool CLegendeObjekt :: MoveUp (WORD &iActSel, bool fShowAll)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;
	
bool iRet = m_pItems -> MoveUp (iActSel, fShowAll);

	if (iRet) SetDirty();
	
return iRet;
}

// LegendenEintrag nach unten verschieben -------------------------------------
bool CLegendeObjekt :: MoveDown (WORD &iActSel, bool fShowAll)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

bool iRet = m_pItems -> MoveDown (iActSel, fShowAll);

	if (iRet) SetDirty();
	
return iRet;
}

// Leerzeile einfügen/entfernen -----------------------------------------------
bool CLegendeObjekt :: EnterSpace (WORD iActSel)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

	if (m_pItems -> hasSpace (iActSel, true))
		SetDirty();
	
return true;
}

bool CLegendeObjekt :: RemoveSpace (WORD iActSel)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

	if (m_pItems -> hasSpace (iActSel, false))
		SetDirty();
	
return true;
}


// LegendenEintrag entfernen --------------------------------------------------
bool CLegendeObjekt :: RemoveEntry (WORD iActSel)
{
// wenn nichts selektiert ist, dann wieder raus
	if (iActSel == USHRT_MAX) return false;

bool iRet = m_pItems -> RemoveEntry (iActSel);		// aus Baum entfernen

	if (iRet) SetDirty();
	
return iRet;
}


// Feststellen, welcher Eintrag vom MausKlick getroffen wurde -----------------
WORD CLegendeObjekt :: FindEntry (short iPos)
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

bool CLegendeObjekt :: GetEntrySize (WORD iOrder, Range &rR)
{
CLegendInfoEntry *pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;
	
	rR.Min() = CoOrd(pLIE -> GetPosition()) - m_iLine/6;
	rR.Max() = rR.Min() + CoOrd(pLIE -> GetHeight());

return true;
}


bool CLegendeObjekt :: GetEntryDesc (WORD iOrder, char *pBuffer, 
				     LEGENTRYTYPE &rrgType, VisType &rgVType, 
				     long &rlTarget)
{
CLegendInfoEntry *pLIE = m_pItems -> FFindItem (iOrder);

	if (pLIE == NULL) return false;
	switch (rrgType = pLIE -> isA()) {
	case LEGENTRYTYPE_IDENT:
		rlTarget = ((CLegendInfoIdent *)pLIE) -> GetIdent();
		break;
		
	case LEGENTRYTYPE_OBJECT:
		rlTarget = ((CLegendInfoObject *)pLIE) -> GetONr();
		break;
		
	default:
	case LEGENTRYTYPE_UNKNOWN:
		return false;
	}
	*pBuffer = '\0';
	rgVType = pLIE -> GetVType();

return FormatString (pBuffer, pLIE);
}


