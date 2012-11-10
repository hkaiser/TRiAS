// Routinen fuer PaletteWindow ------------------------------------------------
// File: PPALWIND.CXX

#include "triaspre.hxx"

#include <owncombo.hxx>
#include "clbmpobj.hxx"

#include "palwind.h"
#include "triasres.h"

#include "dcolor.hxx"
#include "feature.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"
#include "dcbmpwnd.hxx"

// Konstruktor der DialogFensterInstanz ---------------------------------------
#pragma warning (disable: 4355)

PointPaletteWindow :: PointPaletteWindow (pWindow pW, DatenBasisObjekt &rDBO, 
	Color C, Dimension D, short Style, bool fHSB, short iRot, Color SecC)
		    : PaletteWindow (rDBO.FNewPnts() ? PUNKTFARBSELEKTION_NEU : PUNKTFARBSELEKTION, 
		    		     pW, rDBO, C, fHSB),
		      ShowPoint (this, rDBO, IDT_FARBE, C, D, Style, iRot, SecC),
		      PointStyle (this, IDC_STYLE),
		      SymbolX (this, IDE_SIZEX, IDCC_SIZEX, Range (0, 10000)),
		      SymbolY (this, IDE_SIZEY, IDCC_SIZEY, Range (0, 10000))
{
// Parameter setzen
	_oldSymbol = Style;
	_oldSize = D;
	m_iOldRot = iRot;
	m_SecC = SecC;

// Controls initialisieren
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
PointPaletteWindow :: ~PointPaletteWindow (void) {}

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
		PaletteWindow :: ButtonClick (e);
		break;

	case IDCANCEL:
	// alte Attribute wieder einstellen
		GetPointSymbol() = _oldSymbol;
		GetSize() = _oldSize;

	// und dann an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;

	default:
	// an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;
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
bool EXPORTTRIAS PointPaletteWindow :: DeleteItem (DeleteItemEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		delete (Feature *)e.GetItemData();	// Daten freigeben
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

bool EXPORTTRIAS PointPaletteWindow :: DrawEntireItem (DrawItemEvt e) 
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
#if defined(WIN32)
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

	default:
	// sonstige EditControls
		PaletteWindow :: EditFocusChg (e);
		return;
	}
// neuen Mode aktivieren
Color C = ModColor();
	ModColor (&C);
}
