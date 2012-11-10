// Funktionen zur Selektion der zu zeichnenden Objekte ------------------------
// File: IDENT.CXX

#include "trias02p.hxx"

#define MYROPCODE 0x00b8074a

#include <deltree.hxx>
#include <ident.hxx>
#include <pbd.hxx>
#include <efont.hxx>
#include <epen.hxx>
#include <viserror.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Farbe aus Palette holen ----------------------------------------------------
static Color ConvertPalette (Color C, HPALETTE hPal)
{
	if (hPal && C.Reserved() != 0) {
		GetPaletteEntries (hPal, C.Red(), 1, (PALETTEENTRY *)&C);
		C.Reserved() = 0;
	}

return C;
}

// Identifikator -- Konstruktor -----------------------------------------------
CIdentifikator :: CIdentifikator (long Ident, VisInfo *ppVI[4], 
				  short fSpec, HPALETTE hPalette) 
{
// Member initialisieren
	m_hPalette = hPalette;	// lokale Farbpalette
	m_lIdent = Ident;	// Identifikator

// alle Flags richten 
	m_fIdPaint = 0;
	m_fOTypes = 0;
	m_fIdLoaded = false;
	m_fIdTemp = false;
	m_fIdModified = false;
	m_fIdNotAllLoaded = true;
	m_fIdIsDrawn = false;
	m_fhasColor = false;
	m_fSearchAble = TPAll;
	m_fMovedAway = false;
	m_fObjectsDrawn = false;
	
	m_fSpecial = fSpec;

	m_fMetaDC = false;
	m_fhasKO = false;
	m_fOTypesSet = false;

	m_fhasPen = false;
	m_pP = NULL;
	m_fhasBrush = false;
	m_pB = NULL;
	m_pBM = NULL;		// Bitmap für FlächenFüllung
	m_fhasFont = false;
	m_pF = NULL;

	m_DrawType = DT_Normal;	// wie immer zeichnen

	m_pPVI = NULL;
	m_pLVI = NULL;
	m_pFVI = NULL;
	m_pTVI = NULL;

	m_lPCnt = 0;			// Zähler der geladenen Objekte
	m_lLCnt = 0;
	m_lFCnt = 0;
	m_lTCnt = 0;
	m_lKCnt = 0;
#if defined(WIN32)
	m_pObjs = NULL;
#endif // WIN32

// VisInfo typgerecht einstellen 
short fToPaint = 0;

	for (short i = 0; i < 4; i++) {
	VisInfo *pVI = ppVI[i];

		if (pVI == NULL) continue;	// diese VI nicht gewünscht

		switch (pVI -> isA()) {
		case VT_Punkt:
			m_pPVI = (PVisInfo *)pVI;
			ChangeMainColor (m_pPVI);
			if (m_hPalette) {
			long pIndex = PALETTEINDEX(GetNearestPaletteIndex (
							m_hPalette,
							*(COLORREF *)&(((PVisInfo *)m_pPVI) -> SecColor()) 
						   )
				      );
				((PVisInfo *)m_pPVI) -> SecColor() = *(Color *)&pIndex;
			}
			fToPaint |= TPPunkt;
			break;

		case VT_Linie:
			m_pLVI = (LVisInfo *)pVI;
			ChangeMainColor (m_pLVI);
			fToPaint |= TPLinie;
			break;

		case VT_Flaeche:
			{
				m_pFVI = (FVisInfo *)pVI;
				ChangeMainColor (m_pFVI);
				if (m_hPalette) {
				long pIndex = PALETTEINDEX(GetNearestPaletteIndex (
								m_hPalette,
								*(COLORREF *)&(((FVisInfo *)m_pFVI) -> SecColor()) 
							   )
					      );
					((FVisInfo *)m_pFVI) -> SecColor() = *(Color *)&pIndex;
				}
				fToPaint |= TPFlaeche;
			}
			break;

		case VT_Text:
			m_pTVI = (TVisInfo *)pVI;
			ChangeMainColor (m_pTVI);
			fToPaint |= TPText;
			break;

		case VT_Default:
			continue;

		default:
			TX_ASSERT(false);
			break;
		}
	}
	m_fIdPaint = fToPaint;		// PaintFlags entsprechend setzen
}


// FarbAttribut setzen (MainColor) --------------------------------------------
void CIdentifikator :: ChangeMainColor (VisInfo *pVI) 
{
	if (pVI == NULL) return;

	if (*(long *)&(pVI -> PrimColor()) != -1) {
	// Farbe gegeben: muß über Systempalette konvertiert werden
	VisType iVTyp = pVI -> isA();

		hasColor (true);
		if ((iVTyp == VT_Punkt || iVTyp == VT_Flaeche) && m_hPalette) 
		{
		long pIndex = PALETTEINDEX(GetNearestPaletteIndex (m_hPalette, 
					   *(COLORREF *)&(pVI -> PrimColor()) ));

			pVI -> PrimColor() = *(Color *)&pIndex;
		}
	} else {
	// Systemeigenschaften verwenden
		hasColor (false);

	unsigned long SysC = GetSysColor (COLOR_WINDOWTEXT);

		pVI -> PrimColor() = *(Color *)&SysC;
	}
}

// Neueinstellen der VisInfo für diesen Identifikator -------------------------
VisInfo *CIdentifikator :: ChangeVisInfo (VisInfo *pNewVI, VisType iVTyp) 
{
// wenn NULL eingestellt werden soll
	if (pNewVI == VI_Changed) pNewVI = NULL;

// alte Werte löschen
	ResetResources();

// Visualisierungsinformationen setzen
	ChangeMainColor (pNewVI);

VisInfo *pOldVI = NULL;

// wenn kein InfoTyp gegeben, aus neuer VisInfo holen
	if (iVTyp == VT_Default && pNewVI != NULL)
		iVTyp = pNewVI -> isA();

// wenn neue VisInfo eine DefaultInfo ist, dann dieses speichern
short iNewSpec = (pNewVI != NULL) ? pNewVI -> isType() : 0;

	if (iNewSpec & TPDefaultInfo)
		iNewSpec &= ~TPDefaultInfo;
	else
		iNewSpec = 0;
		 
	switch (iVTyp) {
	case VT_Punkt:
		{
			if (m_fSpecial & TPPunkt)	// evtl. DefaultVis löschen
				m_fSpecial &= ~TPPunkt;

			pOldVI = m_pPVI;
			if (m_pPVI = pNewVI) {
			 	m_fIdPaint |= TPPunkt;
				m_fSpecial |= iNewSpec;
			} else
				m_fIdPaint &= ~TPPunkt;

		// für Punktsymbol 2. Farbe setzen
			if (m_pPVI && m_hPalette) {
			long pIndex = PALETTEINDEX(GetNearestPaletteIndex (
							m_hPalette,
							*(COLORREF *)&( ((PVisInfo *)m_pPVI) -> SecColor() ) 
						   )
				      );
				((PVisInfo *)m_pPVI) -> SecColor() = *(Color *)&pIndex;
			}
		}
		break;

	case VT_Linie:
		if (m_fSpecial & TPLinie)	// evtl. DefaultVis löschen
			m_fSpecial &= ~TPLinie;
		pOldVI = m_pLVI;

		if (m_pLVI = pNewVI) {
		 	m_fIdPaint |= TPLinie;
			m_fSpecial |= iNewSpec;
		} else 
			m_fIdPaint &= ~TPLinie;
		break;

	case VT_Flaeche:
		{
			if (m_fSpecial & TPFlaeche)	// evtl. DefaultVis löschen
				m_fSpecial &= ~TPFlaeche;

			pOldVI = m_pFVI;
			if (m_pFVI = pNewVI) {
			 	m_fIdPaint |= TPFlaeche;
				m_fSpecial |= iNewSpec;
			} else 
				m_fIdPaint &= ~TPFlaeche;

		// für Fläche Füllfarbe setzen
			if (m_pFVI && m_hPalette) {
			long pIndex = PALETTEINDEX(GetNearestPaletteIndex (
							m_hPalette,
							*(COLORREF *)&( ((FVisInfo *)m_pFVI) -> SecColor() ) 
						   )
				      );
				((FVisInfo *)m_pFVI) -> SecColor() = *(Color *)&pIndex;
			}
		}
		break;

	case VT_Text:
		if (m_fSpecial & TPText) 	// evtl. DefaultVis löschen
			m_fSpecial &= ~TPText;

		pOldVI = m_pTVI;
		if (m_pTVI = pNewVI) {
			m_fIdPaint |= TPText;
			m_fSpecial |= iNewSpec;
		} else 
			m_fIdPaint &= ~TPText;
		break;

	case VT_Default:	// gar nichts machen
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return pOldVI;
}

// VisInfo zu einem DarstellungsTyp holen -------------------------------------
VisInfo *CIdentifikator :: GetVisInfo (VisType iVTyp) 
{
	switch (iVTyp) {
	case VT_Punkt:
		return m_pPVI ? CopyVisInfo (m_pPVI) : NULL;

	case VT_Linie:
		return m_pLVI ? CopyVisInfo (m_pLVI) : NULL;

	case VT_Flaeche:
		return m_pFVI ? CopyVisInfo (m_pFVI) : NULL;

	case VT_Text:
		return m_pTVI ? CopyVisInfo (m_pTVI) : NULL;

	case VT_Default:
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return CopyVisInfo (NULL);	// DefaultVisInfo generieren
}

VisInfo *CIdentifikator :: CopyVisInfo (VisInfo *pVI)
{
	if (pVI != NULL) {
	// neue Instanz anlegen und Farben zurückkonvertieren
	VisInfo *pNewVI = (VisInfo *)pVI -> Copy();	// liefert neue Instanz

		if (pNewVI == NULL) return NULL;

		pNewVI -> PrimColor() = ConvertPalette (pNewVI -> PrimColor(), m_hPalette);
		if (pNewVI -> isA() == VT_Flaeche) {
		FVisInfo *pFVI = (FVisInfo *)pNewVI;

			pFVI -> SecColor() = ConvertPalette (pFVI -> SecColor(), m_hPalette);
		} else if (VT_Punkt == pNewVI -> isA()) {
		PVisInfo *pPVI = (PVisInfo *)pNewVI;

			pPVI -> SecColor() = ConvertPalette (pPVI -> SecColor(), m_hPalette);
		}
		return pNewVI;
	} else
		return new CDefaultVisInfo();	// generiert default Eigenschaften
}

// Feststellen, ob eine bestimmte VisualiserungsArt gegeben ist ---------------
bool CIdentifikator :: hasVI (VisType iVTyp)
{
	switch (iVTyp) {
	case VT_Punkt:
		return m_pPVI != NULL;

	case VT_Linie:
		return m_pLVI != NULL;

	case VT_Flaeche:
		return m_pFVI != NULL;

	case VT_Text:
		return m_pTVI != NULL;

	case VT_Default:	// irgend eine gegeben
		return m_pPVI || m_pLVI || m_pFVI || m_pTVI;

	default:
		TX_ASSERT(false);
		break;
	}

return false;	// keine VisInfo gegeben
}

// Liefert einen bestimmten VisualiserungsTyp ---------------------------------
VisInfo &CIdentifikator :: VI (VisType iVTyp)
{
	switch (iVTyp) {
	case VT_Punkt:
		if (m_pPVI != NULL) return *m_pPVI;
		break;

	case VT_Linie:
		if (m_pLVI != NULL) return *m_pLVI;
		break;

	case VT_Flaeche:
		if (m_pFVI != NULL) return *m_pFVI;
		break;

	case VT_Text:
		if (m_pTVI != NULL) return *m_pTVI;
		break;

	case VT_Default:
	default:		// this should not happen
		TX_ASSERT(false);
		break;
	}

return *(new CDefaultVisInfo());	// DefaultVisInfo generieren
}

// Pen dieses Identifikators liefern ------------------------------------------
pPen CIdentifikator :: GetPen (VisType iVTyp, short locWidth) 
{
	if (iVTyp == VT_Linie && m_pLVI == NULL) return m_pP;
	if (iVTyp == VT_Flaeche && m_pFVI == NULL) return m_pP;

// wenn neue Breite verwendet wird, dann Pen neu generieren
	if (hasPen() && m_Width != locWidth) {
		if (m_pP) {
			delete (ExtPen *)m_pP;
			m_pP = NULL;
		}
		hasPen (false);
	}

	if (!hasPen() && hasColor()) {
	// Pen generieren
		if (iVTyp == VT_Linie) {
		// Pen für LinienSignatur generieren
		StdLineStyle locStyle = (StdLineStyle)(m_pLVI -> Style());

		// wenn die Breite negativ ist, dann bei ExtLineStyles DefDicke verwenden
			if (locWidth < 0) {
				if (locStyle > InsideFrameLine)	locWidth = -1;
				else				locWidth = -locWidth;
			}
			m_Width = locWidth;	// neue Dicke merken

		Color C = m_pLVI -> PrimColor();

//			if ((locStyle == SolidLine || locStyle >= InsideFrameLine) && 
//			    (m_Width > 1 || m_Width == -1))
//			{

		// alle Linien über Farbpalette konvertieren
			if (!m_fMetaDC) {
			long pIndex = PALETTEINDEX(
					GetNearestPaletteIndex (m_hPalette, 
					(COLORREF &)C)
				      );

				C = (Color &)pIndex;
			}
			if (locStyle == SolidLine)
				locStyle = InsideFrameLine;

//			} else
//				C = m_pLVI -> PrimColor();
			m_pP = new ExtPen (locStyle, m_Width, C);
		} else if (iVTyp == VT_Flaeche) {
		// Pen für FlächenRand

			m_Width = locWidth;
			if (isBkConture()) {
			Color C2 = ((FVisInfo *)m_pFVI) -> SecColor();

				if (m_fMetaDC) C2 = ConvertPalette (C2, m_hPalette);
				m_pP = new ExtPen (InsideFrameLine, m_Width, C2);
			} else {
			Color C2 = m_pFVI -> PrimColor();

				if (m_fMetaDC) C2 = ConvertPalette (C2, m_hPalette);
				m_pP = new ExtPen (InsideFrameLine, m_Width, C2);
			}
		}
		if (m_pP == NULL) {
			db_error (EC_NOMEMORY, RC_IdGetPen);
			return NULL;
		}
		hasPen (true);         // ok
	} 

return m_pP;	// generierten Pen liefern
}

// Brush dieses Identifikators liefern ----------------------------------------
_TRIAS02_ENTRY pBitmap EXPORT02 CreateColorPattern (HDC, HPALETTE, uint, Color, Color);
_TRIAS02_ENTRY pBitmap EXPORT02 CreateHatchPattern (HDC, HPALETTE, uint);

pBrush CIdentifikator::GetBrush (HDC hDC, bool fForceOpaque, Bitmap **ppBmp) 
{
	if (NULL == m_pFVI) {
		if (NULL != ppBmp) *ppBmp = m_pBM;
		return m_pB;
	}

short newStyle = FillMode();
short BStyle = ((FVisInfo *)m_pFVI) -> Type();	// letzte beiden Stellen

	if (BStyle != newStyle) {
		DELETE (m_pB);
		DELETE (m_pBM);
		hasBrush (false);
	} 

	if (NULL != ppBmp)
		*ppBmp = NULL;		// für alle Fälle

	if (NULL != hDC && !hasBrush() && hasColor() && BStyle) {
	// Brush generieren, wenn Fläche füllen und noch kein Brush da
	Color C1 = (Color &)(m_pFVI -> PrimColor());
	Color C2 = (Color &)((FVisInfo *)m_pFVI) -> SecColor();

		if ((StdHatchStyle)(BStyle-1) > DiagonalCrossHatch) {
		// eingefärbte Bitmap als Brush verwenden
			DELETE (m_pBM);

			if (fForceOpaque || ((FVisInfo *)m_pFVI) -> isOpaque())	{
				m_pBM = CreateColorPattern (hDC, m_hPalette, BStyle + FIRSTFILLBMP, C1, C2);

			// resultierenden Pinsel erstellen
				if (NULL != m_pBM) {
					TX_TRY(m_pB = new Brush (m_pBM));
				}
			} else {
				m_pBM = CreateHatchPattern(hDC, m_hPalette, BStyle + FIRSTFILLBMP);
//				TX_TRY(m_pBM = new Bitmap(ResID(BStyle + FIRSTFILLBMP)));
				if (NULL != ppBmp) *ppBmp = m_pBM;		// wenn gewünscht Bitmap liefern

			// resultierenden Pinsel erstellen (hier: Füllfarbe)
				if (NULL != m_pBM) {
					TX_TRY(m_pB = new Brush (C2, SolidHatch));
				}
			}

			if (m_pBM == NULL) {
				db_error (EC_NOMEMORY, RC_IdGetBrush);
				return NULL;
			}

		} else {
			if (m_fMetaDC) {
				C1 = ConvertPalette (C1, m_hPalette);
				C2 = ConvertPalette (C2, m_hPalette);
			}

			DELETE (m_pB);		// für alle Fälle
			TX_TRY(m_pB = new Brush (((FVisInfo *)m_pFVI) -> isOpaque() ? C1 : C2, 
					  (StdHatchStyle)(BStyle -1)));

			DELETE (m_pBM);
		}

	// Fehler auswerten
		if (m_pB == NULL) {
			db_error (EC_NOMEMORY, RC_IdGetBrush);
			return NULL;
		}
		hasBrush (true);       // ok
	
	} else if (NULL != ppBmp) {
	// Bitmap wird nur bei transparenten patterns geliefert
		if ((StdHatchStyle)(BStyle-1) > DiagonalCrossHatch && !((FVisInfo *)m_pFVI) -> isOpaque())
			*ppBmp = m_pBM;
	}

	return m_pB;
}

#define WIDTHBYTES(i)	((i+31)/32*4)

pBitmap EXPORT02 CreateColorPattern (HDC hDC, HPALETTE hPal, uint resid, 
				     Color SecC, Color PrimC)
{
pBitmap pBMSrc = NULL;

	TX_TRY(pBMSrc = new Bitmap (ResID (resid)));	// schwarz/weiß Bitmap

	if (pBMSrc == NULL) return NULL;

HDC hDCMemSrc = CreateCompatibleDC (hDC);

	SelectObject (hDCMemSrc, pBMSrc -> Handle (API_BITMAP_HBITMAP));

HDC hDCMemDst = CreateCompatibleDC (hDC);
HBITMAP hBmpDst = CreateCompatibleBitmap (hDC, 8, 8);	// Pattern
HPALETTE hOldPal;

	if (hPal) {
		hOldPal = SelectPalette (hDCMemDst, hPal, false);
		RealizePalette (hDCMemDst);
	}
	SetTextColor (hDCMemDst, (COLORREF &)SecC);	// Vordergrund bunt
	SetBkColor (hDCMemDst, (COLORREF &)PrimC);	// HinterGrund bunt
	SelectObject (hDCMemDst, hBmpDst);

	PatBlt (hDCMemDst, 0, 0, 8, 8, WHITENESS);	// Bitmap initialisieren
	BitBlt (hDCMemDst, 0, 0, 8, 8, hDCMemSrc, 0, 0, SRCCOPY /*MYROPCODE*/);
        
// aufräumen
	if (hPal) SelectPalette (hDCMemDst, hOldPal, false);
	DeleteDC (hDCMemSrc);
	DeleteDC (hDCMemDst);
	DELETE (pBMSrc);

Bitmap *pBmp = NULL;

	TX_TRY(pBmp = new Bitmap ((HBITMAP)hBmpDst));	// gefärbte Bitmap liefern
	return pBmp;
}

// Generieren einer Bitmap, die 'etwas größer' ist als der AusgangsPattern
#define PATTERNSIZEX	256
#define PATTERNSIZEY	256

pBitmap EXPORT02 CreateHatchPattern (HDC hDC, HPALETTE hPal, uint resid)
{
pBitmap pBMSrc = NULL;

	TX_TRY(pBMSrc = new Bitmap (ResID (resid)));	// schwarz/weiß Bitmap
	if (pBMSrc == NULL) return NULL;

HDC hDCMemSrc = CreateCompatibleDC (hDC);

	SelectObject (hDCMemSrc, pBMSrc -> Handle (API_BITMAP_HBITMAP));

HDC hDCMemDst = CreateCompatibleDC (hDC);
HBITMAP hBmpDst = CreateCompatibleBitmap (hDC, PATTERNSIZEX, PATTERNSIZEY);	// Pattern
HPALETTE hOldPal;

	if (hPal) {
		hOldPal = SelectPalette (hDCMemDst, hPal, false);
		RealizePalette (hDCMemDst);
	}
	SetTextColor (hDCMemDst, RGB(0, 0, 0));		// Vordergrund schwarz
	SetBkColor (hDCMemDst, RGB(255, 255, 255));	// HinterGrund weiß
	SelectObject (hDCMemDst, hBmpDst);

	PatBlt (hDCMemDst, 0, 0, PATTERNSIZEX, PATTERNSIZEY, WHITENESS);	// Bitmap initialisieren

Dimension dim (pBMSrc -> GetSize());

	for (int x = 0; x <= PATTERNSIZEX; x += dim.Width()) {
		for (int y = 0; y <= PATTERNSIZEY; y += dim.Height()) {
		int dX = min(x+dim.Width(), (CoOrd)PATTERNSIZEX) - x;
		int dY = min(y+dim.Height(), (CoOrd)PATTERNSIZEY) - y;

			BitBlt (hDCMemDst, x, y, dX, dY, hDCMemSrc, 0, 0, SRCCOPY);
		}
	}
        
// aufräumen
	if (hPal) SelectPalette (hDCMemDst, hOldPal, false);
	DeleteDC (hDCMemSrc);
	DeleteDC (hDCMemDst);
	DELETE (pBMSrc);

Bitmap *pBmp = NULL;

	TX_TRY(pBmp = new Bitmap ((HBITMAP)hBmpDst));	// gefärbte Bitmap liefern
	return pBmp;
}

// Liefert den Font, der für eine TextObjekt mit diesem Identifikator ---------
// verwendet werden soll 
pFont CIdentifikator :: GetFont (Dimension actSize) 
{
	if (m_pTVI == NULL) return m_pF;

// wenn Font verändert wurde, dann so tun, als ob kein Font gegeben wäre
	if (m_pTVI -> isA() != VT_Text)
		return NULL;

TVisInfo *pTVI = (TVisInfo *)m_pTVI;

	if (hasFont() && 
	    (actSize.Width() != m_FontSize.Width() || 
	     actSize.Height() != m_FontSize.Height() ||
	     ((ExtFont *)m_pF) -> FontChanged())) 
	{
		DELETE (m_pF);
		hasFont (false);
	}

	if (!hasFont()) {
	// Font muß noch generiert werden
		m_FontSize = actSize;
		if ((m_pF = MakeFont (pTVI, m_FontSize)) == NULL)
			return NULL;	// Fehlermeldung war schon
		hasFont (true);	// ok
	}

return m_pF;
}

// Generieren eines Fonts entsprechend der Einstellungen in pTVI --------------
Font * EXPORT02 MakeFont (TVisInfo *pTVI, Dimension Size) 
{
Font *pF = NULL;

	TX_TRY(pF = new Font ((StdFamily)pTVI -> Style(), Size, pTVI -> TName()));
	if (pF == NULL) {
		db_error (EC_NOMEMORY, RC_IdGetFont);
		return NULL;
	}

// Fontspezifikation setzen
	if (pTVI -> isItalic()) pF -> SetItalic();

	if (pTVI -> isStrikedthru()) 	 pF -> SetStrikethru();
	if (pTVI -> isUnderlined()) 	 pF -> SetUnderline();

	if (pTVI -> isFixedPitch()) 	 pF -> SetFixedPitch();
	else 				 pF -> SetVariablePitch();

	if (pTVI -> isBold())		 pF -> SetBold();
	else if (pTVI -> isLight())	 pF -> SetLight();

	((ExtFont *)pF) -> SetEscapement (pTVI -> Rotation());
	((ExtFont *)pF) -> SetOrientation (pTVI -> Orientation());

return pF;
}

// Funktion, die lediglich aktuellen Font liefert -----------------------------
pFont CIdentifikator :: GetFont (void) 
{
	if (m_pTVI == NULL || m_pTVI -> isA() != VT_Text || !hasFont()) 
		return NULL;

return m_pF;
}

// Destruktor -----------------------------------------------------------------
CIdentifikator :: ~CIdentifikator (void) 
{
	if (m_pP) {		// ZeichenAttribute freigeben
		delete (ExtPen *)m_pP;
		m_pP = NULL;
	}
	DELETE (m_pB);
	DELETE (m_pF);
	DELETE (m_pBM);

	DELETE (m_pPVI);	// VisTypeAttribs freigeben
	DELETE (m_pLVI);
	DELETE (m_pFVI);
	DELETE (m_pTVI);

#if defined(WIN32)
	DELETE(m_pObjs);
#endif // WIN32
}

// Funktionen für den Zugriff auf die BaumSuchSchlüssel -----------------------
void * EXPORT02 GetIdent (void *pObj) 
{ 
	return & ((CIdentifikator *)pObj) -> Id(); 
}

void * EXPORT02 GetPriority (void *pObj) 
{ 
	return & ((CIdRef *)pObj) -> FPriority (); 
}

// Funktionen, die auf interna der Ident-VisInfo zugreifen --------------------
bool CIdentifikator :: FrameMode (void) 
{
	if (m_pTVI && m_pTVI -> isA() == VT_Text) 
		return ((TVisInfo *)m_pTVI) -> FrameMode();

return false;
}

bool CIdentifikator :: RoundFrame (void) 
{
	if (m_pTVI && m_pTVI -> isA() == VT_Text) 
		return ((TVisInfo *)m_pTVI) -> RoundFrame();

return false;
}

short CIdentifikator :: BKMode (VisType iVTyp) 
{
	if (iVTyp == VT_Text && m_pTVI && m_pTVI -> isA() == VT_Text) 
		return short(((TVisInfo *)m_pTVI) -> BKMode());
	
	if (iVTyp == VT_Flaeche && m_pFVI && m_pFVI -> isA() == VT_Flaeche) 
		return short(((FVisInfo *)m_pFVI) -> isOpaque() ? OPAQUE : TRANSPARENT);

return TRANSPARENT;
}

bool CIdentifikator :: isBkConture (void)
{
	if (m_pFVI && m_pFVI -> isA() == VT_Flaeche) 
		return ((FVisInfo *)m_pFVI) -> isBkConture();
		
return false;
}

short CIdentifikator :: Escapement (void) 
{
	if (m_pTVI && m_pTVI -> isA() == VT_Text) 
		return ((TVisInfo *)m_pTVI) -> Rotation();

return 0;
}

short CIdentifikator :: Rotation (void) 
{
	if (m_pPVI && m_pPVI -> isA() == VT_Punkt)
		return ((PVisInfo *)m_pPVI) -> Rotation();

return 0;
}

short CIdentifikator :: AlignStyle (void) 
{
	if (m_pTVI && m_pTVI -> isA() == VT_Text)
		return ((TVisInfo *)m_pTVI) -> AlignStyle();

return TV_LeftAlign;
}


static short __auxPrio__ = DEF_PRIORITY;	// Hilfsvariable für Referenzen

short &CIdentifikator :: Priority (VisType iVTyp) 
{
	switch (iVTyp) {
	case VT_Punkt:
		if (m_pPVI) return m_pPVI -> Priority();
		__auxPrio__ = DEF_PRIORITY_PUNKT;
		break;

	case VT_Linie:
		if (m_pLVI) return m_pLVI -> Priority();
		__auxPrio__ = DEF_PRIORITY_LINIE;
		break;

	case VT_Flaeche:
		if (m_pFVI) return m_pFVI -> Priority();
		__auxPrio__ = DEF_PRIORITY_FLAECHE;
		break;

	case VT_Text:
		if (m_pTVI) return m_pTVI -> Priority();
		__auxPrio__ = DEF_PRIORITY_TEXT;
		break;

	case VT_Default:
		__auxPrio__ = DEF_PRIORITY;
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return __auxPrio__;
}

static short __auxWidth__ = DEF_WIDTH_LINIE;

short &CIdentifikator :: Width (void) 
{
	if (m_pLVI && m_pLVI -> isA() == VT_Linie)
		return ((LVisInfo *)m_pLVI) -> Width();

	__auxWidth__ = DEF_WIDTH_LINIE;

return __auxWidth__;
}

short CIdentifikator :: FrameWidth (void) 
{
	if (m_pFVI && m_pFVI -> isA() == VT_Flaeche)
		return ((FVisInfo *)m_pFVI) -> Width(); 

return DEF_WIDTH_FRAME; 
}

short CIdentifikator :: FillMode (void) 
{
	if (m_pFVI && m_pFVI -> isA() == VT_Flaeche)
		return ((FVisInfo *)m_pFVI) -> Type();

return DEF_STYLE; 
}

short CIdentifikator :: toFill (VisType iVTyp) 
{
	switch (iVTyp) {
	case VT_Punkt:
		if (m_pPVI) return m_pPVI -> Style();
		return DEF_STYLE_PUNKT;

	case VT_Linie:
		if (m_pLVI) return m_pLVI -> Style();
		break;

	case VT_Flaeche:
		if (m_pFVI) return ((FVisInfo *)m_pFVI) -> Type();
		break;

	case VT_Text:
		if (m_pTVI) return m_pTVI -> Style();
		return DEF_STYLE_TEXT;

	case VT_Default:
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return DEF_STYLE;
}

Color CIdentifikator :: GetColor (VisType iVTyp, Colors defColor) 
{
	if (hasVI (iVTyp)) {
	VisInfo &rVI = VI (iVTyp);

		switch (rVI.isA()) {
		case VT_Punkt:
//			return ConvertPalette (((PVisInfo &)rVI).SecColor(), m_hPalette);

		case VT_Linie:
		case VT_Text:
		case VT_Default:
			if (m_fMetaDC) 
				return ConvertPalette (rVI.PrimColor(), m_hPalette);
			return rVI.PrimColor();

		case VT_Flaeche:
			return ConvertPalette (((FVisInfo &)rVI).SecColor(), m_hPalette);

		default:
			TX_ASSERT(false);
			break;
		}
	}

return Color(defColor);
}

Color EXPORT02 CIdentifikator :: GetBkColor (void) 
{
	if (m_pFVI && m_pFVI -> isA() == VT_Flaeche && 
	    ((FVisInfo *)m_pFVI) -> isOpaque()) 
	{
		if (m_fMetaDC)
			return ConvertPalette (((FVisInfo *)m_pFVI) -> SecColor(), m_hPalette);
		return ((FVisInfo *)m_pFVI) -> SecColor();
	}

return Color((ColorVal)255, (ColorVal)255, (ColorVal)255);
}

Color EXPORT02 CIdentifikator :: Get2ndColor (void) 
{
	if (m_pPVI && m_pPVI -> isA() == VT_Punkt)
	{
		if (m_fMetaDC)
			return ConvertPalette (((PVisInfo *)m_pPVI) -> SecColor(), m_hPalette);
		return ((PVisInfo *)m_pPVI) -> SecColor();
	}

return Color((ColorVal)255, (ColorVal)255, (ColorVal)255);	// Standard ist weiß
}

bool EXPORT02 CIdentifikator :: isOpaque (void)
{
	if (m_pFVI && m_pFVI -> isA() == VT_Flaeche)
		return ((FVisInfo *)m_pFVI) -> isOpaque();

return false;
}


// Größe von PunktObjekten/Texten liefern -------------------------------------
static Dimension __D__ (0, 0);

Dimension &CIdentifikator :: Size (VisType iVTyp) 
{
	if (iVTyp == VT_Punkt) {
		if (m_pPVI && m_pPVI -> isA() == VT_Punkt)
			return ((PVisInfo *)m_pPVI) -> Size();
		__D__ = DEF_SIZE_PUNKT;	// 2*2 mm
	}		
	if (iVTyp == VT_Text) {
		if (m_pTVI && m_pTVI -> isA() == VT_Text)
			return ((TVisInfo *)m_pTVI) -> Size();
		__D__ = DEF_SIZE_TEXT;	// 14 Pt
	}

return __D__;
}

// alle gebundenen Ressourcen freigeben ---------------------------------------
void CIdentifikator :: ResetResources (void) 
{
	if (hasPen()) {
		if (m_pP) {
			delete (ExtPen *)m_pP;
			m_pP = NULL;
		}
		hasPen (false);
	}
	if (hasBrush()) {
		DELETE (m_pB);
		DELETE (m_pBM);
		hasBrush (false);
	}
	if (hasFont()) {
		DELETE (m_pF);
		hasFont (false);
	}
}

// VisInfo aus Speicher holen -------------------------------------------------
short CIdentifikator :: GetCompleteVisInfo (VisInfo **ppVI, short iBits, short *piGot)
{
short fRet = 0;

	if (NULL != piGot) *piGot = 0;

	if (iBits & TPPunkt) {
		ppVI[0] = GetVisInfo (VT_Punkt);
		if (NULL != piGot) *piGot |= TPPunkt;
	}
	if (iBits & TPLinie) {
		ppVI[1] = GetVisInfo (VT_Linie);
		if (NULL != piGot) *piGot |= TPLinie;
	}
	if (iBits & TPFlaeche) {
		ppVI[2] = GetVisInfo (VT_Flaeche);
		if (NULL != piGot) *piGot |= TPFlaeche;
	}
	if (iBits & TPText) {
		ppVI[3] = GetVisInfo (VT_Text);
		if (NULL != piGot) *piGot |= TPText;
	}

return GetSpecial (iBits);
}


// Bearbeiten des Fehlers 'Fehlende VisInfo' ----------------------------------
CIgnoreVisErrorTree *CIdentifikator :: m_pIVET = NULL; 

ErrCode CIdentifikator :: ReportVisInfoError (ErrCode EC, RoutCode RC, short iVTyp)
{
ErrInstall EI1 (WC_NOVISINFOPUNKT, ReportVisError);
ErrInstall EI2 (WC_NOVISINFOLINIE, ReportVisError);
ErrInstall EI3 (WC_NOVISINFOFLAECHE, ReportVisError);
ErrInstall EI4 (WC_NOVISINFOTEXT, ReportVisError);

	if (m_pIVET == NULL) {
		TX_TRY(m_pIVET = new CIgnoreVisErrorTree());
	}

	if (m_pIVET && m_pIVET -> FFindItem (m_lIdent, iVTyp)) 
		return EC_OKAY;		// bereits bearbeitet

ErrCode ecResult = EC_OKAY;
short iCnt = 0;
CVisError VE (m_lIdent, iVTyp);

	do {		// versuchen, bis Fehler behoben oder ignoriert ist
		ecResult = (ErrCode)db_error (EC, RC, (void *)&VE);
		if (ecResult == EC_OKAY && isCustomized()) 	// noch mal versuchen
			break;
	} while (ecResult == EC_OKAY && iCnt++ < 3);

// erstes mal, also Ident/Typ Speichern
	if (m_pIVET && ecResult != EC_OKAY) 
		m_pIVET -> FAddItem (m_lIdent, iVTyp);
	
	return ecResult;
}

void EXPORT02 CIdentifikator :: ReleaseIgnoreTree (void)
{
	DELETE (m_pIVET);
}

// Liefern der in der Datenbasis vorhandenen Objekttypen dieses Idents
short EXPORT02 CIdentifikator::GetOTypes (GeoDB &rDB)
{
bool fReturn = true;

	if (!GetOTypesSet() || NULL == m_pObjs) {
	short iOTypes = 0;	// gesuchte OTypes
	long lFlexNum = 0;	// Nummer des intern belegten Flex'

		if (!FindId (rDB, &lFlexNum, &iOTypes)) {
			ResetInit();
			fReturn = false;	// Fehler
		}
		if (0 != lFlexNum) ferel_ (&lFlexNum);
	}
	return fReturn ? GetOTypes() : 0;
}

#if defined(WIN32)
bool CIdentifikator::FindId (GeoDB &rDB, long *plFlex, short *pOTypes)
{
LONG lObjCnts[4];

	ZeroMemory (lObjCnts, 4*sizeof(LONG));
	if (EC_OKAY != rDB.FindId (m_lIdent, plFlex, pOTypes, lObjCnts))
		return false;

// ObjektZähler initialisieren
	m_lPCnt = lObjCnts[0];
	m_lLCnt = lObjCnts[1];
	m_lFCnt = lObjCnts[2];
	m_lTCnt = lObjCnts[3];

bool fReturn = true;

	if (NULL != plFlex) {
		TX_ASSERT(0 != *plFlex);
		if (SetObjectList (*plFlex)) {
			if (NULL != pOTypes) {
				SetOTypes (*pOTypes);
				SetHasKO (*pOTypes & TPKO);
			}
		} else
			fReturn = false;
	
	} else if (NULL != pOTypes) {
		SetOTypes (*pOTypes);
		SetHasKO (*pOTypes & TPKO);
	}		
	return fReturn;
}

bool CIdentifikator::GetOTypesEx (GeoDB &rDB, short &rOTypes)
{
bool fReturn = true;

	if (!GetOTypesSet() || NULL == m_pObjs) {
	short iOTypes = 0;	// gesuchte OTypes
	long lFlexNum = 0;	// Nummer des intern belegten Flex'

		if (!FindId (rDB, &lFlexNum, &iOTypes)) {
			ResetInit();
			fReturn = false;	// Fehler
		}
		if (0 != lFlexNum) ferel_ (&lFlexNum);
	}
	if (fReturn) rOTypes = GetOTypes();
	return fReturn;
}

bool CIdentifikator::SetObjectList (long lFlexNum)
{
	try {
		if (NULL == m_pObjs) {
			TX_TRY(m_pObjs = new CIdentObjects());
		}

	long *pObjs = NULL;
	long lCnt = 0L;

		felen_ (&lFlexNum, &lCnt);
		FlexAdr ((short)lFlexNum, &pObjs);

		if (0 == lCnt || NULL == pObjs)
			return false;

	// Objektnummern in CIdentObjects speichern
		m_pObjs -> clear();

	insert_iterator<CIdentObjects> ins (*m_pObjs, m_pObjs -> begin());

		copy (pObjs, pObjs+lCnt, ins);		// Objekte hierher kopieren

	} catch (bad_alloc) {
		return false;
	}

	return true;
}

void CIdentifikator::ResetObjectList (void)
{
	if (NULL != m_pObjs) m_pObjs -> clear();
}

bool CIdentifikator::AddObjectToList (GeoDB &rDB, long lONr)
{
	try {
		if (NULL == m_pObjs) {
		short iOTypes = 0;

			if (!GetOTypesEx (rDB, iOTypes))
				return false;
		}
	
	CIdentObjects::iterator it = m_pObjs->insert (m_pObjs->begin(), lONr);

		if (it == m_pObjs->end())
			return false;		// Objekt existiert bereits
	
	} catch (bad_alloc) {
		return false;
	}
	return true;
}

bool CIdentifikator::RemoveObjectFromList (GeoDB &rDB, long lONr)
{
	if (NULL == m_pObjs) {		// ObjektListe nicht existent
	short iOTypes = 0;

		if (!GetOTypesEx (rDB, iOTypes))
			return false;
	}

CIdentObjects::size_type lCnt = m_pObjs->erase (lONr);

	return lCnt != 0 ? true : false;
}

bool CIdentifikator::IsObjectInList (long lONr)
{
	if (NULL == m_pObjs) return false;

CIdentObjects::iterator it = m_pObjs->find (lONr);

	return it != m_pObjs->end() ? true : false;
}

bool CIdentifikator::GetObjectList (CIdentObjects &rObjs)
{
	try {
		if (NULL == m_pObjs) 
			m_pObjs = new CIdentObjects();

		rObjs = *m_pObjs;		// Objektliste kopieren
	} catch (bad_alloc) {
		return false;
	}
	return true;
}

#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Objekte zählen
long EXPORT02 CIdentifikator::GetObjectCount (ObjTyp rgOTyp)
{
	switch (rgOTyp) {
	case OT_PUNKT:	return m_lPCnt;
	case OT_KANTE:	return m_lLCnt;
	case OT_FLAECHE:
	case OT_KREIS:	return m_lFCnt;
	case OT_LABEL:
	case OT_TEXT:	return m_lTCnt;
	case OT_KO:		return m_lKCnt;
	default:
		TX_ASSERT(false);
		break;
	}
	return 0L;
}

long EXPORT02 CIdentifikator::IncrementObjectCount (ObjTyp rgOTyp)
{
	switch (rgOTyp) {
	case OT_PUNKT:	return ++m_lPCnt;
	case OT_KANTE:	return ++m_lLCnt;
	case OT_FLAECHE:
	case OT_KREIS:	return ++m_lFCnt;
	case OT_LABEL:
	case OT_TEXT:	return ++m_lTCnt;
	case OT_KO:		return ++m_lKCnt;
	default:
		TX_ASSERT(false);
		return false;
	}
	return true;
}

long EXPORT02 CIdentifikator::DecrementObjectCount (ObjTyp rgOTyp)
{
	switch (rgOTyp) {
	case OT_PUNKT:	m_lPCnt--; /*TX_ASSERT(m_lPCnt >= 0);*/ return m_lPCnt;
	case OT_KANTE:	m_lLCnt--; /*TX_ASSERT(m_lLCnt >= 0);*/ return m_lLCnt;
	case OT_FLAECHE:
	case OT_KREIS:	m_lFCnt--; /*TX_ASSERT(m_lFCnt >= 0);*/ return m_lFCnt;
	case OT_LABEL:
	case OT_TEXT:	m_lTCnt--; /*TX_ASSERT(m_lTCnt >= 0);*/ return m_lTCnt;
	case OT_KO:		m_lKCnt--; /*TX_ASSERT(m_lKCnt >= 0);*/ return m_lKCnt;
	default:
		TX_ASSERT(false);
		return 0L;
	}
}

long EXPORT02 CIdentifikator::InitObjectCount (ObjTyp rgOTyp, long lObjCnt)
{
	switch (rgOTyp) {
	case OT_PUNKT:	return m_lPCnt = lObjCnt;
	case OT_KANTE:	return m_lLCnt = lObjCnt;
	case OT_FLAECHE:
	case OT_KREIS:	return m_lFCnt = lObjCnt;
	case OT_LABEL:
	case OT_TEXT:	return m_lTCnt = lObjCnt;
	case OT_KO:		return m_lKCnt = lObjCnt;
	default:
		TX_ASSERT(false);
		return 0L;
	}
}

bool EXPORT02 CIdentifikator::SetMetaDC (bool fMetaDC)
{
	if (m_fMetaDC ^ fMetaDC) {	// vor Meta/nach Meta alles rücksetzen
		ResetResources();
		m_fMetaDC = fMetaDC;
		return true;
	}

return false;
}

///////////////////////////////////////////////////////////////////////////////
// Klasse, die beide Bäume verwaltet 

// Extrahieren der IdentifikatorVisInfo für einen Ident 
bool CIdTree :: RetrieveVisInfo (long lIdent, short iVTyp, VISINFO &rVI)
{
	TX_ASSERT(IsValidIdent(lIdent));

CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);

		if (!l -> hasVI((VisType)iVTyp)) 
			return false;

	// VisInfo besorgen und Konvertieren
	VisInfo *pNewVI = l -> CopyVisInfo (&(l -> VI((VisType)iVTyp)));
	
		if (pNewVI) {
			pNewVI -> CopyTo (rVI);
			delete pNewVI;

			if (iVTyp == VT_Default) {
			// sonstige GeoTypen
				TX_ASSERT(TIsValidAddress(&rVI, sizeof(DVISINFO), true));

				((DVISINFO &)rVI).m_iDefTypes = l -> GetSpecial();
			}
			return true;
		} else
			return false;
	}
	
return false;
}

EXPORT02 CIdTree :: CIdTree (GeoDB &rDB) : m_rDB (rDB) { /* nothing to do */ }
EXPORT02 CIdTree :: ~CIdTree (void) { /* nothing to do */ }

void EXPORT02 CIdTree :: AllDelete (void)
{
	CIdTree1 :: EveryDelete();
	CIdTree2 :: EveryDelete();
}

void EXPORT02 CIdTree :: ResetAllLoaded (void)
{
CTable t(IdentTree());

	for (t.First(); t.Valid(); t.Next()) {
	CIdentifikatorLock l(t);

		if (!l) continue;
		l -> UnLoad();		// nichts mehr geladen
	}
}

// Baum, der Identifikatoren enthält ------------------------------------------
CIdTree1 :: CIdTree1 (void)
	  : UniqueTree (GetIdent, ULongCmp)
{
	// nothing else to do
}

CIdTree1 :: ~CIdTree1 (void)
{
	EveryDelete();
}

void EXPORT02 CIdTree1 :: UserDelete (void *pObj)
{
	((CIdentifikator *)pObj) -> /*CIdentifikator ::*/ ~CIdentifikator();
}

// Klasse, in CIdTree2, die Referenzen auf CIdent's enthält und Prioritäten
// verwaltet
CIdRef :: CIdRef (CIdentifikator &rCId, VisType iVTyp)
	: m_rCId (rCId)
{
	m_iVTyp = iVTyp;
	m_iPriority = m_rCId.Priority (m_iVTyp);	// Priorität holen
}


CIdRef :: CIdRef (CIdentifikator &rCId, VisType iVTyp, short iPrio)
	: m_rCId (rCId)
{
	m_iVTyp = iVTyp;
	m_iPriority = iPrio;	// Priorität merken
}


CIdRef :: ~CIdRef (void)
{
	// nothing to do
}

int ShortCmp (void *pObj1, void *pObj2)
{
	return *(short *)pObj1 - *(short *)pObj2;
}

CIdTree2 :: CIdTree2 (void)
	  : CTree (GetPriority, ShortCmp)
{
	// nothing else to do
}

CIdTree2 :: ~CIdTree2 (void)
{
	EveryDelete();		// Elemente löschen
}

void EXPORT02 CIdTree2 :: UserDelete (void *pObj)
{
	((CIdRef *)pObj) -> /*CIdRef ::*/ ~CIdRef();
}

bool CIdTree2 :: AddEntry (CIdentifikator &rCId, VisInfo *pVI)
{
	if (pVI == NULL) return false;

short iPrio = pVI -> Priority();
CTable tP(*this);
bool fFound = false;
VisType iVTyp = pVI -> isA();

	for (!tP.FindFirst(&iPrio); tP.Valid(); tP.FindNext (&iPrio)) {
	CIdRefLock l(tP);

		if (l.isValid() && l -> Id() == rCId.Id() && 
		    ((CIdRef *)l) -> FVisTyp() == iVTyp) 
		{
			fFound = true;
			break;
		}
	}

	if (fFound && tP.Valid()) {	// Eintrag existiert bereits
		return tP.ReInsert (&iPrio, sizeof (iPrio));
	} else {
	// neuen Eintrag zu existierendem CIdentifikator generieren
	CIdRefCreator CIdCr (*this);

		return ContCreate (CIdCr, CIdRef) (rCId, iVTyp, iPrio) != NULL;
	}

return false;
}

// Identifikator zu Sicht und IdTree hinzufügen -------------------------------
bool CIdTree::AddNewIdent (
	long newId, HPALETTE hPalette, short iFlags, short iVTyp, long lTargetId) 
{
CTable tID (IdentTree());
short oldDrawType = DT_Normal;
bool oldLoadInfo = false;
bool oldTempInfo = false;
bool fAllLoaded = false;
VisInfo *newpVI[4];
bool fTempFlag = iFlags & ANI_Temp;

// wenn BezugsIdent nicht gegeben ist, dann neuen Ident verwenden
	if (lTargetId == -1L) lTargetId = newId;
	
	memset (newpVI, '\0', 4 * sizeof(VisInfo *));

// Id im IdTree suchen
short fSpec = 0;
short iToPaint = iVTyp;
short iOTypes = iVTyp;
bool fMovedAway = false;
short fSearchAble = iVTyp;
long lPCnt = 0, lLCnt = 0, lFCnt = 0, lTCnt = 0, lKCnt = 0;
CIdentObjects *pObjs = NULL;

	if (tID.Find (&lTargetId)) {		// Id gibt es schon: löschen
	CIdentifikatorLock l(tID);

		TX_ASSERT(NULL != (CIdentifikator *)l);

	CIdentifikator *pId = (CIdentifikator *)l;

		oldDrawType = pId -> DType();	// DrawType merken
		oldLoadInfo = pId -> loaded();
		oldTempInfo = pId -> isTemp();

		if (lTargetId == newId) {
			iOTypes = pId -> GetOTypes() | iVTyp;
			iToPaint = pId -> toPaint() | iVTyp;
		} else {
			iOTypes = pId -> GetOTypes() & iVTyp;
			iToPaint = pId -> toPaint() & iVTyp;
		}
		fAllLoaded = pId -> AreAllLoaded();
		fMovedAway = pId ->  MovedAway();
		fSearchAble = pId -> GetSearchAble();
					
	// alter Ident ist nicht mehr vollständig
		if (fTempFlag) {
			pId -> MovedAway (true);
			if (newId == lTargetId)
				fMovedAway = true;
		}

		lPCnt = pId -> GetPointCount();
		lLCnt = pId -> GetLineCount();
		lFCnt = pId -> GetAreaCount();
		lTCnt = pId -> GetTextCount();
		lKCnt = pId -> GetComplexCount();
		pObjs = pId -> DetachObjList();
	}
	
// VisInfo von neuem Ident holen, wenn dieser bekannt ist, ansonsten in
// Sicht nachsehen
char *pView = NULL;
short iExistOTypes = 0;

	TX_TRY(pView = new char [_MAX_PATH]);
	if (pView) DEX_GetActiveSight (pView);	// aktuellen Sichtnamen holen

	if (tID.Find (&newId)) {
	CIdentifikatorLock l(tID);

		if (l) fSpec = l -> GetCompleteVisInfo ((VisInfo **)newpVI, iToPaint, &iExistOTypes);
	} 
	
	if (iToPaint != (iExistOTypes & iToPaint)) {
		if (pView && *pView != '\0') {
		Sicht S (m_rDB, pView);

			S.GetCompleteVisInfo (newId, 0, (VisInfo **)newpVI, iToPaint);
		}	
	}

// wenn immer noch nichts ist, dann in DefaultSicht nachsehen	
	GetCompleteDefaultVisInfo (m_rDB, newId, 0, (VisInfo **)newpVI, iToPaint);
	fSpec |= MakeCompleteNewVisInfo ((VisInfo **)newpVI, iToPaint, true); // <<-- true für CreateObject ?? (#hk950603)

// bei Bedarf Ident zur aktuellen Sicht hinzufügen
	if (pView && iFlags & ANI_AddToView) {
	Sicht S (m_rDB, pView);
	ErrCode EC = EC_OKAY;
	
	// neue VisInfo wegschreiben
		if (fSpec == TPAll) {	// nur DefaultInfo schreiben
			if (newpVI[0]) S.AddIDtoSight (newId, newpVI[0], TPAll);
		} else {		// nur nicht DefaultSätze schreiben
			if (!(fSpec & TPPunkt) && newpVI[0]) 
				EC = S.AddIDtoSight (newId, newpVI[0]);
			if (!(fSpec & TPLinie) && EC == EC_OKAY && newpVI[1]) 
				EC = S.AddIDtoSight (newId, newpVI[1]);
			if (!(fSpec & TPFlaeche) && EC == EC_OKAY && newpVI[2]) 
				EC = S.AddIDtoSight (newId, newpVI[2]);
			if (!(fSpec & TPText) && EC == EC_OKAY && newpVI[3]) 
				EC = S.AddIDtoSight (newId, newpVI[3]);

		// Ident/Typ ohne VisInfo wegschreiben bzw. DefaultSatz löschen
			if (EC == EC_OKAY && fSpec != 0)
				S.AddIDtoSight (newId, NULL, fSpec);
		}
	}
	DELETE (pView);

	DeleteIdent (newId);		// Ident löschen

// Identifikatoreintrag in Baum generieren
	if (AddIdent (newId, newpVI, fSpec, hPalette) && tID.Find (&newId)) {
	CIdentifikatorLock l (tID);

		TX_ASSERT(NULL != (CIdentifikator *)l);

	CIdentifikator *pId = (CIdentifikator *)l;

	// LoadStatus von altem Identifikator übernehmen
		if (oldLoadInfo || fTempFlag)
			pId -> Load();
		else
			pId -> UnLoad();
		if (fAllLoaded || fTempFlag)
			pId -> AllLoaded();
		else
			pId -> NotAllLoaded();
		
	// wenn der alte oder der neue Ident temp ist, dann muß es 
	// der neue auf jeden Fall auch sein
		if (oldTempInfo || fTempFlag)
			pId -> Temp();
		else
			pId -> Perm();
		
		pId -> DType() = oldDrawType;
		pId -> SetSpecial (fSpec|pId -> GetSpecial());
		pId -> SetOTypes (iOTypes|pId -> GetOTypes());
		pId -> SetSearchAble (fSearchAble);
		if (fTempFlag && newId == lTargetId)
			pId -> MovedAway (fMovedAway);

		pId -> InitPointCount (lPCnt);
		pId -> InitLineCount (lLCnt);
		pId -> InitAreaCount (lFCnt);
		pId -> InitTextCount (lTCnt);
		pId -> InitComplexCount (lKCnt);
		TX_VERIFY (NULL == pId -> AttachObjList (pObjs));
		pObjs = NULL;
	}
	DELETE(pObjs);

return true;
}

// Funktionen für IdentifikatorBaum -------------------------------------------
bool CIdTree :: DeleteIdent (long lIdent, short iVTyp) 
{
CTable tId (IdentTree());	// Table für Identifikatoren
CTable tPr (PrioTree());	// Table für Prioritäten
short iPPrio, iLPrio, iFPrio, iTPrio;

	if (!tId.Find (&lIdent)) return false;

// Priorität holen
	{
	CIdentifikatorLock lId(tId);

		if (lId) {
			iPPrio = lId -> Priority (VT_Punkt);
			iLPrio = lId -> Priority (VT_Linie);
			iFPrio = lId -> Priority (VT_Flaeche);
			iTPrio = lId -> Priority (VT_Text);
		} else 
			return false;
	}

// gleichen Satz in Prio-Baum wiederfinden
	if (iVTyp & TPPunkt) DeletePriority (tPr, iPPrio, VT_Punkt, lIdent);
	if (iVTyp & TPLinie) DeletePriority (tPr, iLPrio, VT_Linie, lIdent);
	if (iVTyp & TPFlaeche) DeletePriority (tPr, iFPrio, VT_Flaeche, lIdent);
	if (iVTyp & TPText) DeletePriority (tPr, iTPrio, VT_Text, lIdent);

	if (!hasIdent (tPr, lIdent))
		tId.Delete();		// IdentifikatorSatz rausnehmen

	return true;
}

void CIdTree :: DeletePriority (CTable &t, short iPrio, VisType iVTyp, long lIdent)
{
// Satz mit gegebener Prio/VisTyp und lIdent wiederauffinden
	for (t.FindFirst (&iPrio); t.Valid(); t.FindNext (&iPrio)) {
	CIdRefLock l(t);

		if (l.isValid() && l -> Id() == lIdent && 
		    ((CIdRef *)l) -> FVisTyp() == iVTyp) 
		{
		VisInfo *pVI = l -> ChangeVisInfo (NULL, iVTyp);

			DELETE(pVI);	// alte VI löschen
			break;		// Satz gefunden
		}
	}

// wenn Satz gefunden
	if (t.Valid()) t.Delete();	// Satz löschen
}

bool CIdTree :: hasIdent (CTable &t, long lIdent)
{
// Satz mit gegebenem lIdent wiederauffinden
	for (t.First(); t.Valid(); t.Next()) {
	CIdRefLock l(t);

		if (l.isValid() && l -> Id() == lIdent)
			return true;		// Satz gefunden
	}

return false;
}

bool CIdTree::hasIdentVType (long lIdent, VisType iVTyp)
{
CTable t (PrioTree());		// Table für Prioritäten

// Satz mit gegebenem lIdent wiederauffinden
	for (t.First(); t.Valid(); t.Next()) {
	CIdRefLock l(t);

		if (l.isValid() && 
			l -> Id() == lIdent && 
			((CIdRef *)l) -> FVisTyp() == iVTyp)
		{
			return true;		// Satz gefunden
		}
	}

return false;
}

bool CIdTree::AddIdent (long lIdent, VisInfo *ppVI[4], short fSpec, HPALETTE hPal)
{
CIdentifikator *pId = NULL;
bool fOK = true;

	{
	CIdentifikatorCreator IdCr (IdentTree());

		pId = ContCreate (IdCr, CIdentifikator) (lIdent, ppVI, fSpec, hPal);
		if (pId == NULL) {
			db_error (EC_NOMEMORY, RC_CIdTreeAddIdent);
			return false;
		}
	}	// einfügen
	{
	CIdRefCreator IdRefCr (PrioTree());
	CIdRef *pIdR = NULL;

		if (pId -> hasVI (VT_Punkt)) {
			pIdR = ContCreate (IdRefCr, CIdRef) (*pId, VT_Punkt);
			if (pIdR == NULL) fOK = false;
		}
		if (fOK && pId -> hasVI (VT_Linie)) {
			pIdR = ContCreate (IdRefCr, CIdRef) (*pId, VT_Linie);
			if (pIdR == NULL) fOK = false;
		}
		if (fOK && pId -> hasVI (VT_Flaeche)) {
			pIdR = ContCreate (IdRefCr, CIdRef) (*pId, VT_Flaeche);
			if (pIdR == NULL) fOK = false;
		}
		if (fOK && pId -> hasVI (VT_Text)) {
			pIdR = ContCreate (IdRefCr, CIdRef) (*pId, VT_Text);
			if (pIdR == NULL) fOK = false;
		}
	}	// letzten Satz einhängen

	if (!fOK) {	// Fehler aufgetreten
		db_error (EC_NOMEMORY, RC_CIdTreeAddIdent);
		DeleteIdent (lIdent);
	}

return fOK;
}


// HilfsFunktion, die VisType in entsprechende Bits umsetzt -------------------
static short VTypToBits (VisType iVTyp)
{
	switch (iVTyp) {
	case VT_Punkt:		return TPPunkt;
	case VT_Linie:		return TPLinie;
	case VT_Flaeche:	return TPFlaeche;
	case VT_Text:		return TPText;
	case VT_Default:	return 0;

	default:
		TX_ASSERT(false);
		break;
	}

return 0;	// no type at all
}

// Verändern der Priorität eines Eintrages ------------------------------------
bool CIdTree :: ChangePriority (long lIdent, short newPrio, VisType iVTyp,
			        bool isChanged)
{
CTable tID (IdentTree());
short oldPrio;		// alte Priorität

	if (!tID.Find (&lIdent)) return false;	// Ident nicht gefunden
	{
	CIdentifikatorLock lID(tID);

		if (!lID) return false;		// Fehler
		oldPrio = lID -> Priority (iVTyp);
	}

// wenn Priorität nicht geändert wurde, dann wieder raus
	if (oldPrio == newPrio)
		return true;
				
CTable tP (PrioTree());
bool fFound = false;

	for (tP.FindFirst (&oldPrio); tP.Valid(); tP.FindNext (&oldPrio)) {
	CIdRefLock lP (tP);

		if (lP.isValid() && lP -> Id() == lIdent && 
		    ((CIdRef *)lP) -> FVisTyp() == iVTyp) 
		{
			fFound = true;
			if (isChanged) lP -> Modified();
			break;
		}
	}

	if (fFound && tP.Valid()) {
		tP.ReInsert (&newPrio, sizeof(newPrio));

		if (tID.Find (&lIdent)) {	// Ident wiederfinden
		CIdentifikatorLock lID(tID);

			if (!lID) return false;
			
		// wenn alte VisInfo Default war, dann neue VisInfo generieren
			if (!lID -> isCustomized (VTypToBits (iVTyp))) {
				if (!lID -> hasVI (iVTyp)) 
					return false;	// should'nt happen

			VisInfo *pOldVI = &(lID -> VI (iVTyp));
			VisInfo *pVI = (VisInfo *) pOldVI -> CopyCustom();

				pVI = lID -> ChangeVisInfo (pVI, iVTyp);
				DELETE (pVI);
			} 

		// neue Priorität auch in CIdTree1
			lID -> Priority (iVTyp) = newPrio;
			return true;
		}
	}

return false;
}


// Funktion, die liefert, ob eine Identifikator gezeichnet werden soll --------
short CIdTree :: toPaint (long lIdent, short iMsk) 
{
CTable t(IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		if (l) return l -> toPaint(iMsk);
	}

return 0;
}

// Funktion, die Farbe des gesuchten Id's liefert -----------------------------
Color CIdTree :: GetColor (long lIdent, VisType iVTyp)
{
CTable t(IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		if (l) return l -> GetColor (iVTyp, WHITE);
	}

return Color (WHITE);
}


// Testen, ob ein Ident in DB vertreten ist -----------------------------------
bool CIdTree::isUsed (GeoDB &rDB, long lIdent) 
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		if (l) return l->GetOTypes (rDB) != 0;
	}
	return false;
}


// zurückschreiben der VisInfo's, wenn ein Id modifiziert wurde ---------------
ErrCode CIdTree :: WriteBack (char *pSichtName) 
{
// wenn Sicht temporär ist, dann wieder raus
	if (pSichtName == NULL) return EC_OKAY;

CTable t(IdentTree());
Sicht locSicht (m_rDB, pSichtName);
ErrCode RC;

	for (t.First(); t.Valid(); t.Next()) {
	CIdentifikatorLock l(t);

		if (!l) continue;
		if (l -> isModified()) {
			DBASSERT (WriteBackVisInfo (l, locSicht, VT_Punkt));
			DBASSERT (WriteBackVisInfo (l, locSicht, VT_Linie));
			DBASSERT (WriteBackVisInfo (l, locSicht, VT_Flaeche));
			DBASSERT (WriteBackVisInfo (l, locSicht, VT_Text));
			l -> UnModified();	// nicht mehr modifiziert
		}
	}

return EC_OKAY;
}

ErrCode CIdTree :: WriteBackVisInfo (CIdentifikator *pId, Sicht &locSicht, 
				     VisType iVTyp) 
{
	if (pId -> hasVI (iVTyp)) {
	VisInfo *pVI = (VisInfo *)pId -> VI (iVTyp).Copy();
	ErrCode RC;
	VisType ilocVTyp = pVI -> isA();

	// Fläche oder Punkt: MainColor konvertieren
		pVI -> PrimColor() = ConvertPalette (pVI -> PrimColor(), pId -> hPal());

	// wenn Ident Punkt, 2. Farbe konvertieren
		if (ilocVTyp == VT_Punkt) {
		PVisInfo *pPVI = (PVisInfo *)pVI;
			
			pPVI -> SecColor() = ConvertPalette (pPVI -> SecColor(), pId -> hPal());
		}

	// wenn Ident Fläche, FüllFarbe konvertieren
		if (ilocVTyp == VT_Flaeche) {
		FVisInfo *pFVI = (FVisInfo *)pVI;
			
			pFVI -> SecColor() = ConvertPalette (pFVI -> SecColor(), pId -> hPal());
		}
		DBASSERT (locSicht.AddIDtoSight (pId -> Id(), pVI));
	}

return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// ObjektZähler verwalten 
long EXPORT02 CIdTree::GetPointCount (long lIdent)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> GetPointCount();
	}

	return 0L;
}

long EXPORT02 CIdTree::GetLineCount (long lIdent)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> GetLineCount();
	}

	return 0L;
}

long EXPORT02 CIdTree::GetAreaCount (long lIdent)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> GetAreaCount();
	}

	return 0L;
}

long EXPORT02 CIdTree::GetTextCount (long lIdent)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> GetTextCount();
	}

	return 0L;
}

long EXPORT02 CIdTree::GetComplexCount (long lIdent)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> GetComplexCount();
	}

	return 0L;
}

long EXPORT02 CIdTree::GetObjectCount (long lIdent, ObjTyp rgOTyp)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> GetObjectCount (rgOTyp);
	}

	return 0L;
}

long EXPORT02 CIdTree::IncrementObjectCount (GeoDB &rDB, long lIdent, ObjTyp rgOTyp, long lONr)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) {
			if (0L != lONr) l -> AddObjectToList (rDB, lONr);
			return l -> IncrementObjectCount (rgOTyp);
		}
	}

	return 0L;
}

long EXPORT02 CIdTree::DecrementObjectCount (GeoDB &rDB, long lIdent, ObjTyp rgOTyp, long lONr)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) {
			if (0L != lONr) l -> RemoveObjectFromList (rDB, lONr);
			return l -> DecrementObjectCount (rgOTyp);
		}
	}

	return 0L;
}

long EXPORT02 CIdTree::InitPointCount (long lIdent, long lPCnt)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> InitPointCount (lPCnt);
	}

	return 0L;
}

long EXPORT02 CIdTree::InitLineCount (long lIdent, long lLCnt)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> InitLineCount (lLCnt);
	}

	return 0L;
}

long EXPORT02 CIdTree::InitAreaCount (long lIdent, long lFCnt)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> InitAreaCount (lFCnt);
	}

	return 0L;
}

long EXPORT02 CIdTree::InitTextCount (long lIdent, long lTCnt)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> InitTextCount (lTCnt);
	}

	return 0L;
}

long EXPORT02 CIdTree::InitComplexCount (long lIdent, long lKCnt)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> InitComplexCount (lKCnt);
	}

	return 0L;
}

long EXPORT02 CIdTree::InitObjectCount (long lIdent, ObjTyp rgOTyp, long lObjCnt)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> InitObjectCount (rgOTyp, lObjCnt);
	}

	return 0L;
}

#if defined(WIN32)
bool CIdTree::FindId (GeoDB &rDB, long lIdent, long *plFlex, short *pOTypes)
{
CTable t (IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) return l -> FindId (rDB, plFlex, pOTypes);
	}
	return false;
}

bool CIdTree::ModifyIdent (GeoDB &rDB, long lONr, long lNewId, long lOldId)
{
CTable t (IdentTree());
bool fResult = false;

	if (t.Find (&lOldId)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) {
			l -> RemoveObjectFromList (rDB, lONr);
			fResult = true;
		}
	}
	if (fResult && t.Find (&lNewId)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) 
			fResult = l -> AddObjectToList (rDB, lONr);
	} else
		fResult = false;

	return fResult;
}

int CIdRef::GetLayerCount (double dScale)
{
	if (VT_Linie != m_iVTyp)	// derzeit spezielbehandlung nur für Linien
		return 1;

// Maßstab rausrechnen
short iWidth = short( double(m_rCId.Width()) * dScale );
StdLineStyle locStyle = (StdLineStyle)(m_rCId.LVI().Style());

// wenn die Breite negativ ist, dann bei ExtLineStyles DefDicke verwenden
	if (iWidth < 0) {
		if (locStyle > InsideFrameLine)
			iWidth = -1;
		else
			iWidth = -iWidth;
	}

// Reale breite der Linie und Anzahl der Layers berechnen
short iCnt = 1;

	ExtPen::EPenWidth (locStyle, iWidth, iCnt);
	return iCnt;
}

#endif // WIN32
