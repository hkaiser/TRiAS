// Routinen fuer PaletteWindow ------------------------------------------------
// File: LPALWIND.CXX

#include "triaspre.hxx"

#include <owncombo.hxx>
#include <muscroll.hxx>

#include "palwind.h"

#include "clbmpobj.hxx"
#include "dcolor.hxx"
#include "feature.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

LinePaletteWindow :: LinePaletteWindow (pWindow pW, DatenBasisObjekt &rDBO, 
			Color C, short Width, short Style, BOOL fHSB)
		   : PaletteWindow (LINIENFARBSELEKTION, pW, rDBO, C, fHSB),
		     ShowLine (this, rDBO, IDT_FARBE, C, Width, Style),
		     LineStyles (this, IDC_STYLE),
		     LineWidth (this, IDE_LINEWIDTH, IDCC_LINEWIDTH, 
		     Range (0, GetGeoDBVersion() >= VERSION05000004 ? 500 : 20))
{
// Parameter setzen
	_oldWidth = Width;
	_oldStyle = Style;

// Controls initialisieren
	LineStyles.FInit (Style);
	
// Anfangszustand definiert setzen
	QueryColor.LocControl() -> SetFocus();

// SpinControl initialisieren
	LineWidth.SetValue (Width);

// Farbeinstellung auf FEIN einstellen
	RedScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	GreenScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	BlueScrollBar.SetMode (ColorScrollBar :: SB_Fine);
}

#pragma warning (default: 4355)

LinePaletteWindow :: ~LinePaletteWindow (void) {}

// EventHandler (das Leben der DialogBox) -------------------------------------
// Nutzer drückt Knöpfchen ----------------------------------------------------
void LinePaletteWindow :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		if (LineWidth.isModified()) {
			LineWidth.CopyToSpin();
			GetWidth() = LineWidth.GetValue();
		}
		PaletteWindow :: ButtonClick (e);
		break;

	case IDCANCEL:
	// alte Attribute wieder einstellen
		GetLineStyle() = _oldStyle;
		GetWidth() = _oldWidth;

	// und dann an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;

	default:
	// an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;
	}
}

// EventHandler ---------------------------------------------------------------
void LinePaletteWindow :: Expose (ExposeEvt) 
{
	ShowLine.RePaint();
}

// ResultatFunktionen ---------------------------------------------------------
short &LinePaletteWindow :: GetWidth (void) { return ShowLine.GetWidth(); }
short &LinePaletteWindow :: GetLineStyle (void) { return ShowLine.GetStyle(); }

// Virtuelle Funktionen -------------------------------------------------------
ColorBox &LinePaletteWindow :: CBox (void) { return ShowLine; }

// OwnerDrawEventHandler ------------------------------------------------------
// das Gleiche für LinePaletteWindow ------------------------------------------
Bool EXPORTTRIAS LinePaletteWindow :: DeleteItem (DeleteItemEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		delete (Feature *)e.GetItemData();	// Daten freigeben
		return TRUE;

	case IDC_FARBEN:
		return PaletteWindow :: DeleteItem (e);
	}

return FALSE;
}

Bool EXPORTTRIAS LinePaletteWindow :: DrawEntireItem (DrawItemEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		// Einen Eintrag malen
		Rectangle Rc = e.ItemSize();	// aktuellen Bereich holen

			InflateRect ((LPRECT)&Rc, -3, -3);	// verkleinern

		// 1. Linie zeichnen
		Feature *pData = (Feature *)e.GetItemData();
		HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
		ExtPen *pEPen = NULL;

			pEPen = new ExtPen ((StdLineStyle)pData -> _Style, -1,
						Color ((Colors)BLACK));
			if (pEPen == NULL) return FALSE;

			pEPen -> SetSecondColor (Color ((ColorVal)192, (ColorVal)192, (ColorVal)192));

		// alle Linien dieses ExtPens ausgeben
		short iOldROPCode = SetROP2 (hDC, R2_COPYPEN);
		CoOrd dX = Rc.Bottom()-Rc.Top();
		HPEN hOldPen;

			for (short iCnt = 0; iCnt < pEPen -> iCnt(); iCnt++) {
			// aktuellen Pen selektieren
				if (pEPen != NULL) 
					hOldPen = (HPEN)SelectObject (hDC, pEPen -> GetHandle(iCnt));

			// Linie zeichnen         
				:: MoveToEx (hDC, Rc.Left(), Rc.Bottom()-dX/2, NULL);
				:: LineTo (hDC, Rc.Left()+2*dX, Rc.Bottom()-dX/2);

			// DeviceKontext zurücksetzen
				if (pEPen != NULL) SelectObject (hDC, hOldPen);
			}
			SetROP2 (hDC, iOldROPCode);

		// 2. Text dazuschreiben
		char *StyleName = pData -> _StyleName;
		Rectangle RcText (Rc.Top()-3, Rc.Left()+2*dX, 
				  Rc.Bottom()+3, Rc.Right());

			ExtTextOut (hDC, RcText.Left(), RcText.Top(), 
					ETO_CLIPPED|ETO_OPAQUE, 
					(const RECT *)&RcText, 
					StyleName, strlen (StyleName), 
					NULL
				 );
			DELETE (pEPen);

			if (e.isSelected()) DrawItemSelect (e);
			if (e.hasFocus()) DrawItemFocus (e);
		}
		return TRUE;

	case IDC_FARBEN:
		return PaletteWindow :: DrawEntireItem (e);
	}

return FALSE;
}

int EXPORTTRIAS LinePaletteWindow :: CompareItem (OwnerDrawEvt e, void *pData1, void *pData2) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		Feature *pF1 = (Feature *)pData1;
		Feature *pF2 = (Feature *)pData2;

			switch (LineStyles.GetSearchMode()) {
			case StyleComboBox :: SM_Style: 
				{
				// nach Füllmustern sortieren
					if (UINT(pF1 -> _Style) > UINT(pF2 -> _Style)) 
						return 1;
					if (UINT(pF1 -> _Style) < UINT(pF2 -> _Style)) 
						return -1;
					return 0;
				}

			case StyleComboBox :: SM_Name:
			// nach Namen sortieren
				return strcmp (pF1 -> _StyleName, 
					       pF2 -> _StyleName);
			}
		}

	case IDC_FARBEN:
		return PaletteWindow :: CompareItem (e, pData1, pData2);
	}

return -1;
}

void LinePaletteWindow :: ListBoxSel (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:		// LineMode ausgewählt
		{
		short iCurrPos = LineStyles.LocControl() -> GetCurrentIndex();

			if (iCurrPos == -1) return;	// no selected item

		Feature *pData = (Feature *)LineStyles.GetItem(iCurrPos);

			GetLineStyle() = pData -> _Style;

		// neuen Mode aktivieren
		Color C = ModColor ();
			ModColor (&C);
		}
		break;

	case IDC_FARBEN:
		PaletteWindow :: ListBoxSel (e);
		return;
	}
}


void LinePaletteWindow :: ListBoxClk (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:		// Füllmode ausgewählt und raus
		break;

	case IDC_FARBEN:
		PaletteWindow :: ListBoxClk (e);
		return;
	}
}


void LinePaletteWindow :: VertScroll (ScrollEvt e) 
{
	if ((uint)e.GetScrollBar() -> GetID() == IDCC_LINEWIDTH) {
	// LinienDicke verändern
		LineWidth.CopyToEdit();
		GetWidth() = LineWidth.GetValue();

	// neuen Mode aktivieren
	Color C = ModColor ();
		ModColor (&C);
	} else 
	// StandardBearbeitung
		PaletteWindow :: VertScroll (e);
}

void LinePaletteWindow :: EditFocusChg (EditFocusChgEvt e) 
{
	if (e.gotFocus())
		return;		// Focus erhalten: weiter

	if ((uint)e.GetControlID() == IDE_LINEWIDTH) {
	// Nutzer hat Liniendicke mit EditControl verändert
		LineWidth.CopyToSpin();
		GetWidth() = LineWidth.GetValue();

	// neuen Mode aktivieren
	Color C = ModColor ();
		ModColor (&C);
	} else
		PaletteWindow :: EditFocusChg (e);
}
