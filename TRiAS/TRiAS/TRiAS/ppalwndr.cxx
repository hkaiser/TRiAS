// Routinen fuer PaletteWindow ------------------------------------------------
// File: PPALWNDR.CXX
// Version für WIN32

#include "triaspre.hxx"

#include <rgb_hsb.hxx>
#include <owncombo.hxx>

#include "palwind.h"
#include "triasres.h"

#include "clbmpobj.hxx"

#include "dcolor.hxx"
#include "feature.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"
#include "dcbmpwnd.hxx"

// Konstruktor der DialogFensterInstanz ---------------------------------------
#pragma warning (disable: 4355)

PointPaletteWindow :: PointPaletteWindow (pWindow pW, DatenBasisObjekt &rDBO, 
			Color C, Dimension D, short Style, BOOL fHSB, 
			short iRot, Color SecC, BOOL fObjVis)
		    : PaletteWindow (rDBO.FNewPnts() ? PUNKTFARBSELEKTION_NEU : PUNKTFARBSELEKTION, 
		    		     pW, rDBO, C, fHSB),
		      ShowPoint (this, rDBO, IDT_FARBE, C, D, Style, iRot, SecC),
		      PointStyle (this, IDC_STYLE),
		      SymbolX (this, IDE_SIZEX, IDCC_SIZEX, Range (0, 10000)),
		      SymbolY (this, IDE_SIZEY, IDCC_SIZEY, Range (0, 10000))
{
	m_fObjVis = fObjVis;

	if (rDBO.FNewPnts()) {
		m_pRotation = new CSpinControl (this, IDE_ROTATION, IDCC_ROTATION, Range (-1800, 1800));
		m_pRotation -> FInit();
		m_pColor1 = new RadioButton (this, IDC_COLOR1);
		m_pColor2 = new RadioButton (this, IDC_COLOR2);
		if (m_pRotation) m_pRotation -> SetValue (short(iRot));
		if (m_pColor1) m_pColor1 -> SetState (true);
		if (m_pColor2) m_pColor2 -> SetState (false);

	// DBVersion abfragen, verfügbar erst ab V5.00.00.011
#if defined(_FORCE_LEGACY_CODE)
		if (rDBO.DB().GetDBVersion() <= VERSION0500000A && !fObjVis) {
			if (m_pRotation) m_pRotation -> Disable();
			if (m_pColor2) m_pColor2 -> Disable();
		}
#endif // defined(_FORCE_LEGACY_CODE)
	} else {
		m_pRotation = NULL;
		m_pColor1 = NULL;
		m_pColor2 = NULL;
	}

// Parameter setzen
	_oldSymbol = Style;
	_oldSize = D;
	m_iOldRot = iRot;
	m_SecC = SecC;

// Controls initialisieren
	SymbolX.FInit();
	SymbolY.FInit();
	PointStyle.FInit ((unsigned short)Style, rDBO);

// Anfangszustand definiert setzen
	QueryColor.LocControl() -> SetFocus();

// SpinControls initialisieren
	SymbolX.SetValue (short(D.Width()));
	SymbolY.SetValue (short(D.Height()));

// Farbeinstellung auf FEIN einstellen
	RedScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	GreenScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	BlueScrollBar.SetMode (ColorScrollBar :: SB_Fine);
}
 
#pragma warning (default: 4355)

// Destruktoren ---------------------------------------------------------------
PointPaletteWindow :: ~PointPaletteWindow (void) 
{
	DELETE_OBJ(m_pRotation);
	DELETE_OBJ(m_pColor1);
	DELETE_OBJ(m_pColor2);
}

// EventHandler (das Leben der DialogBox) -------------------------------------
// Nutzer drückt Knöpfchen ----------------------------------------------------
void PointPaletteWindow :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		if (SymbolX.isModified()) {
			SymbolX.CopyToSpin();
			GetSize().Width() = SymbolX.GetValue();
		}
		if (SymbolY.isModified()) {
			SymbolY.CopyToSpin();
			GetSize().Height() = SymbolY.GetValue();
		}
		if (m_pRotation && m_pRotation -> isModified()) {
			m_pRotation -> CopyToSpin();
			GetRotation() = m_pRotation -> GetValue();
		}
		PaletteWindow :: ButtonClick (e);
		break;

	case IDCANCEL:
	// alte Attribute wieder einstellen
		GetPointSymbol() = _oldSymbol;
		GetSize() = _oldSize;
		GetRotation() = m_iOldRot;
		Get2ndColor() = m_SecC;

	// und dann an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;

	case IDC_COLOR1:
		{
			if (m_pColor2) m_pColor2 -> SetState (false);

		bool fChanged = false;

#if defined(_FORCE_LEGACY_CODE)
			if ((m_fObjVis || m_rDBO.DB().GetDBVersion() > VERSION0500000A) && 
			    GetKeyState (VK_CONTROL) < 0) 
#else
			if (m_fObjVis && GetKeyState (VK_CONTROL) < 0) 
#endif // defined(_FORCE_LEGACY_CODE)
			{
			// Control-Taste zusätzlich gedrückt
				GetMainColor() = Get2ndColor();
				fChanged = true;
			} 
		
		// ScrollBalken entsprechend 2. Farbe setzen
		Color C = GetMainColor();

			if (m_fHSB) {
			unsigned long rC = RGBtoHSB (C);
			
				RedScrollBar.SetColor (GetHValue (rC));
				GreenScrollBar.SetColor (GetSValue (rC));
				BlueScrollBar.SetColor (GetVValue (rC));
				C = *(Color *)&rC;
			} else {
				RedScrollBar.SetColor (C.Red());
				GreenScrollBar.SetColor (C.Green());
				BlueScrollBar.SetColor (C.Blue());
			}

			if (fChanged) ModColor (&C);
		}
		break;

	case IDC_COLOR2:
		{
			if (m_pColor1) m_pColor1 -> SetState (false);

		bool fChanged = false;

			if (GetKeyState (VK_CONTROL) < 0) {
			// Control-Taste zusätzlich gedrückt
				Get2ndColor() = GetMainColor();
				fChanged = true;
			}

		// ScrollBalken entsprechend FüllFarbe setzen
		Color C = Get2ndColor();

			if (m_fHSB) {
			unsigned long rC = RGBtoHSB (C);
			
				RedScrollBar.SetColor (GetHValue (rC));
				GreenScrollBar.SetColor (GetSValue (rC));
				BlueScrollBar.SetColor (GetVValue (rC));
				C = *(Color *)&rC;
			} else {
				RedScrollBar.SetColor (C.Red());
				GreenScrollBar.SetColor (C.Green());
				BlueScrollBar.SetColor (C.Blue());
			}
			if (fChanged) ModColor (&C);
		}
		break;

	default:	// an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;
	}
}

// Virtuelle Funktionen -------------------------------------------------------
Color PointPaletteWindow :: ModColor (Color *pC) 
{
	if (NULL == m_pColor1 || NULL == m_pColor2)
		return PaletteWindow :: ModColor (pC);

	if (m_pColor1 -> GetState())
		return PaletteWindow :: ModColor (pC);	// Randfarbe bearbeiten

	if (pC == NULL) {		// nur Abfrage
	Color C = Get2ndColor();	// 2. Farbe abfragen
	
		if (m_fHSB) {
		unsigned long rC = RGBtoHSB (C);
		
			C = *(Color *)&rC;		
		} else 
			C.Reserved() = 0;
		return C;	// liefert HauptFarbe (Standardfall)
	} else {
	// neue Farbe einstellen
	Color C = *pC;
	
		if (m_fHSB) {
			C = HSBtoRGB (*(unsigned long *)pC);
			C.Reserved() = 0;
		}
		CBox().SetColor (C, ColorBox :: CT_SecondColor);
		return *pC;
	}
}

// ExposeFunktionen -----------------------------------------------------------
void PointPaletteWindow :: Expose (ExposeEvt) 
{
	ShowPoint.RePaint();
}

// ResultatFunktionen ---------------------------------------------------------
Dimension &PointPaletteWindow :: GetSize (void) { return ShowPoint.GetSize(); }
short &PointPaletteWindow :: GetPointSymbol (void) { return ShowPoint.GetStyle(); }
short &PointPaletteWindow :: GetRotation (void) { return ShowPoint.GetRotation(); }
Color &PointPaletteWindow :: Get2ndColor (void) { return ShowPoint.GetBrushColor(); }

// Virtuelle Funktionen -------------------------------------------------------
ColorBox &PointPaletteWindow :: CBox (void) { return ShowPoint; }

// OwnerDrawEventHandler für PointPaletteWindow -------------------------------
BOOL EXPORTTRIAS PointPaletteWindow :: DeleteItem (DeleteItemEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		Feature *pF = (Feature *)e.GetItemData();

			if (pF)	delete pF;	// Daten freigeben
		}
		return true;

	case IDC_FARBEN:
		return PaletteWindow :: DeleteItem (e);
	}

return false;
}

#if defined(__WATCOMC__)
#pragma warning 604 5;		// lookahead required
#pragma warning 595 5;		// resoveld as an expression
#endif

BOOL EXPORTTRIAS PointPaletteWindow :: DrawEntireItem (DrawItemEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		// Einen Eintrag malen
		Rectangle Rc = e.ItemSize();	// aktuellen Bereich holen
		HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);

			InflateRect ((LPRECT)&Rc, -3, -3);	// verkleinern

		// 1. Punktsymbol zeichnen
		Feature *pData = (Feature *)e.GetItemData();
		CoOrd dX = Rc.Bottom()-Rc.Top();

			if (!m_rDBO.FNewPnts()) {
			// Bereich entsprechend Symbol malen
			Bitmap BM (ResID (pData -> _Style + MARKER1 -1));
			HBITMAP hBM = BM.Handle (API_BITMAP_HBITMAP); // hBitmap holen
	
			// Bitmap darstellen
			HDC hMemDC = CreateCompatibleDC (hDC);
			HBITMAP hOldBM = (HBITMAP)SelectObject (hMemDC, hBM);
	
			// Größen vor und nach der Projektion bestimmen
			Dimension BMdim = BM.GetSize();
	
		//      int Result =
				StretchBlt (hDC,    Rc.Left()+dX/2, Rc.Top(),
						    dX, dX,
					    hMemDC, 0, 0, 
						    BMdim.Width(), BMdim.Height(),
					    SRCCOPY);
	
			// alten Zustand wieder herstellen
				SelectObject (hMemDC, hOldBM);
				DeleteDC (hMemDC);
			} else {
			unsigned int uiMarker = m_rDBO.FGetIndex(pData -> _Style);
			CoOrd ddY = dX;
			CoOrd ddX = dX;
			
				if (m_rDBO.FWidth(uiMarker) > m_rDBO.FHeight(uiMarker)) {
					ddX = CoOrd((ddY*long(m_rDBO.FHeight(uiMarker))) / long(m_rDBO.FWidth(uiMarker)));
				} else {
					ddY = CoOrd((ddX*long(m_rDBO.FWidth(uiMarker))) / long(m_rDBO.FHeight(uiMarker)));
				}

			Dimension dimSize (ddX, ddY);
			CBitmapBar *pBmp = m_rDBO.GetBmp (uiMarker, dimSize);
			
				if (pBmp) {
					dimSize.Height() = -dimSize.Height();

				CColorBitmapObject CBMO (Point (Rc.Left()+dX, Rc.Top()+dX/2-1), 
							 dimSize, *pBmp,
							 Color (BLACK), Color (WHITE), 
							 uiMarker, 0);
#if !defined(WIN16)
					CBMO.SetBlackWhite();	// WHITEONBLACK
#endif
					CBMO.SetSwapMode();	// kippen

				CDCBmpWindow bmpWnd (hDC, Rc, CBMO);
				
					bmpWnd.Render (Rc);	// Bitmap ausgeben
				}
			}

		// 2. Text dazuschreiben
		char *pStyleName = pData -> _StyleName;
		Rectangle RcText (Rc.Top()-2, Rc.Left()+2*dX, 
				  Rc.Bottom()+4, Rc.Right());

			ExtTextOut (hDC, RcText.Left()+4, RcText.Top(), 
					ETO_CLIPPED|ETO_OPAQUE, 
					(const RECT *)&RcText, 
					pStyleName, strlen (pStyleName), 
					NULL
				 );

			if (e.isSelected()) DrawItemSelect (e);
			if (e.hasFocus()) DrawItemFocus (e);
		}
		return true;

	case IDC_FARBEN:
		return PaletteWindow :: DrawEntireItem (e);
	}

return false;
}

int EXPORTTRIAS PointPaletteWindow :: CompareItem (OwnerDrawEvt e, void *pData1, void *pData2) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		Feature *pF1 = (Feature *)pData1;
		Feature *pF2 = (Feature *)pData2;

			switch (PointStyle.GetSearchMode()) {
			case StyleComboBox :: SM_Style: 
				{
				// nach PunktArten sortieren (unsigned int !)
					if (UINT(pF1 -> _Style) > UINT(pF2 -> _Style)) 
						return 1;
					if (UINT(pF1 -> _Style) < UINT(pF2 -> _Style)) 
						return -1;
					return 0;
				}

			case PointStyleComboBox :: SM_Name:
			// nach Namen sortieren
				return strcmp (pF1 -> _StyleName, 
					       pF2 -> _StyleName);
			}
		}

	case IDC_FARBEN:
		return PaletteWindow :: CompareItem (e, pData1, pData2);
	}

return false;
}

void PointPaletteWindow :: ListBoxSel (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:		// Füllmode ausgewählt
		{
		short iCurrPos = PointStyle.LocControl() -> GetCurrentIndex();

			if (iCurrPos == -1) return;	// no selected item

		Feature *pData = (Feature *)PointStyle.GetItem(iCurrPos);

			GetPointSymbol() = pData -> _Style;	// PunktID

			if (m_rDBO.FNewPnts()) {		// wenn neue Punktsymbole, Y mitregeln
			WORD uiIndex = m_rDBO.FGetIndex (pData -> _Style);

				SymbolY.SetValue (short((SymbolX.GetValue() * 
							long(m_rDBO.FWidth(uiIndex))) / 
						  long(m_rDBO.FHeight(uiIndex))));
				GetSize().Height() = SymbolY.GetValue();
			}

		// neuen Mode aktivieren
		Color C = ModColor();

			ModColor (&C);
		}
		break;

	case IDC_FARBEN:
		PaletteWindow :: ListBoxSel (e);
		return;
	}
}


void PointPaletteWindow :: ListBoxClk (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:		// Füllmode ausgewählt und raus
		break;

	case IDC_FARBEN:
		PaletteWindow :: ListBoxClk (e);
		return;
	}
}


void PointPaletteWindow :: VertScroll (ScrollEvt e) 
{
	switch ((uint)e.GetScrollBar() -> GetID()) {
	case IDCC_SIZEX:
		SymbolX.CopyToEdit();
		GetSize().Width() = SymbolX.GetValue();
		if (m_rDBO.FNewPnts()) {		// wenn neue Punktsymbole, Y mitregeln
		short iStyle = m_rDBO.FGetIndex (GetPointSymbol());

			SymbolY.SetValue (short((SymbolX.GetValue() * 
						long(m_rDBO.FWidth(iStyle))) / 
					  long(m_rDBO.FHeight(iStyle))));
			GetSize().Height() = SymbolY.GetValue();
		}
		break;

	case IDCC_SIZEY:
		SymbolY.CopyToEdit();
		GetSize().Height() = SymbolY.GetValue();
		break;

	case IDCC_ROTATION:
		if (m_pRotation) {
			m_pRotation -> CopyToEdit();
			GetRotation() = m_pRotation -> GetValue();
		}
		break;

	default:
		PaletteWindow :: VertScroll (e);
		return;
	}
// neuen Mode aktivieren
Color C = ModColor();

	ModColor (&C);
}

void PointPaletteWindow :: EditFocusChg (EditFocusChgEvt e) 
{
	if (e.gotFocus()) return;	// Focus erhalten: weiter

	switch ((uint)e.GetControlID()) {
	case IDE_SIZEX:
	// Nutzer hat PunktSymbolBreite mit EditControl verändert
		SymbolX.CopyToSpin();
		GetSize().Width() = SymbolX.GetValue();
		if (m_rDBO.FNewPnts()) {		// wenn neue Punktsymbole, Y mitregeln
		short iStyle = m_rDBO.FGetIndex(GetPointSymbol());

			SymbolY.SetValue (short((SymbolX.GetValue() * 
						long(m_rDBO.FWidth(iStyle))) / 
					  long(m_rDBO.FHeight(iStyle))));
			GetSize().Height() = SymbolY.GetValue();
		}
		break;

	case IDE_SIZEY:
	// Nutzer hat PunktSymbolHöhe mit EditControl verändert
		SymbolY.CopyToSpin();
		GetSize().Height() = SymbolY.GetValue();
		break;

	case IDE_ROTATION:
		if (m_pRotation) {
			m_pRotation -> CopyToSpin();
			GetRotation() = m_pRotation -> GetValue();
		}
		break;

	default:
	// sonstige EditControls
		PaletteWindow :: EditFocusChg (e);
		return;
	}
// neuen Mode aktivieren
Color C = ModColor();

	ModColor (&C);
}
