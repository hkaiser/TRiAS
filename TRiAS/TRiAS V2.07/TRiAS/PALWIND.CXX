// Routinen fuer PaletteWindow ------------------------------------------------
// File: PALWIND.CXX

#include "triaspre.hxx"

#include <owncombo.hxx>
#include <rgb_hsb.hxx>

#include "palwind.h"

#include "clbmpobj.hxx"
#include "dcolor.hxx"
#include "feature.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor der DialogFensterInstanz ---------------------------------------
#pragma warning (disable: 4355)

PaletteWindow :: PaletteWindow (uint rsc, pWindow pW, DatenBasisObjekt &rDBO, Color C, BOOL fHSB) 
	       : OwnerDrawDialogWindow (pW, ResID (rsc)),
	         m_rDBO (rDBO),
		 RedScrollBar (this, IDSB_ROT, IDE_ROT, fHSB ? MAXHUE : MAXCOLORVAL), // SchiebeBalken
		 GreenScrollBar (this, IDSB_GRUEN, IDE_GRUEN, fHSB ? MAXSATURATION : MAXCOLORVAL),
		 BlueScrollBar (this, IDSB_BLAU, IDE_BLAU, fHSB ? MAXBRIGHTNESS : MAXCOLORVAL),
		 m_ftRed (this, IDT_ROT),
		 m_ftGreen (this, IDT_GRUEN),
		 m_ftBlue (this, IDT_BLAU),
		 QueryColor (this, IDC_FARBEN),		// ComboBox für Farben
		 OKButton (this, IDOK),			// PushButtons
#if !defined(WIN32)
		 HelpButton (this, IDB_COLORHELP),
#endif // WIN32
		 CancelButton (this, IDCANCEL)
//		 NewButton (this, IDB_COLORNEW),
//		 DelButton (this, IDB_COLORDEL),
{
// Controls initialisieren
	QueryColor.FInit (C);
	
// wenn HSB, dann Farbe entsprechend umrechnen
	m_fHSB = fHSB;

	_oldColor = C;			// Ausgangsfarbe merken (RGB)
	_oldColor.Reserved() = 0;

	if (fHSB) {
	unsigned long rC = RGBtoHSB (C);

		m_ftRed.SetText (ResString (IDS_HUE, 20));
		m_ftGreen.SetText (ResString (IDS_SATURATION, 20));
		m_ftBlue.SetText (ResString (IDS_BRIGHTNESS, 20));

	// Scrollbalken/EditControls in Anfangszustand bringen
		RedScrollBar.SetColor (GetHValue (rC));
		GreenScrollBar.SetColor (GetSValue (rC));
		BlueScrollBar.SetColor (GetVValue (rC));

		RedScrollBar.SetMode (ColorScrollBar :: SB_Fine);
		GreenScrollBar.SetMode (ColorScrollBar :: SB_Fine);
		BlueScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	} else {
	// Scrollbalken/EditControls in Anfangszustand bringen
		RedScrollBar.SetColor (C.Red());
		GreenScrollBar.SetColor (C.Green());
		BlueScrollBar.SetColor (C.Blue());

//		RedScrollBar.SetMode (ColorScrollBar :: SB_Coarse);
//		GreenScrollBar.SetMode (ColorScrollBar :: SB_Coarse);
//		BlueScrollBar.SetMode (ColorScrollBar :: SB_Coarse);
	}

// Neu und Löschen erstmal passivieren
//	NewButton.Disable();
//	DelButton.Disable();
}

#pragma warning (default: 4355)

// Destruktoren ---------------------------------------------------------------
PaletteWindow :: ~PaletteWindow (void) {}

// EventHandler (das Leben der DialogBox) -------------------------------------
// Nutzer drückt Knöpfchen ----------------------------------------------------
void PaletteWindow :: ButtonClick (ControlEvt e) {

	switch ((uint)e.GetControlID()) {
	case IDOK:
#if defined(WIN32)
		{
		HWND hWnd = DEX_GetActiveViewWindow();

			TX_ASSERT(::IsWindow(hWnd));
			::ValidateRect (hWnd, NULL);	// erst mal nicht zeichnen
		}
#endif // WIN32
		EndDlg (1);		// Dialog erfolgreich beendet
		DEX_RePaint();	// später neu zeichnen
		break;

	case IDCANCEL:
	// alte Farben/Stile etc. wieder einstellen
		GetMainColor() = _oldColor;
		EndDlg();		// Dialog abbrechen
		break;

	case IDB_COLORNEW:
		break;

	case IDB_COLORDEL:
		break;

	case IDB_COLORHELP:
		break;
	}
}

// Nutzer fummelt an Scrollbalken rum -----------------------------------------
void PaletteWindow :: HorizScroll (ScrollEvt e) 
{
ScrollBar *pSB = e.GetScrollBar();
Color locC = ModColor ();

// neue Farbe abfragen
	switch ((uint)pSB -> GetID()) {
	case IDSB_ROT:
		if (m_fHSB) {
		unsigned long rC = *(unsigned long *)&locC;
		short iSat = GetSValue (rC);
		short iBright = GetVValue (rC);
		
			rC = HSB (iSat, iBright, e.GetPos());
			locC = *(Color *)&rC;
		} else {
			locC.Red() = BYTE(e.GetPos());
			locC.Reserved() = 0;	// echte Farbe (kein Index)
		}
		RedScrollBar.SetColor (e.GetPos());
		break;

	case IDSB_BLAU:
		if (m_fHSB) {
		unsigned long rC = *(unsigned long *)&locC;
		short iHue = GetHValue (rC);
		short iSat = GetSValue (rC);
		
			rC = HSB (iSat, e.GetPos(), iHue);
			locC = *(Color *)&rC;
		} else {
			locC.Blue() = BYTE(e.GetPos());
			locC.Reserved() = 0;	// echte Farbe (kein Index)
		}
		BlueScrollBar.SetColor (e.GetPos());
		break;

	case IDSB_GRUEN:
		if (m_fHSB) {
		unsigned long rC = *(unsigned long *)&locC;
		short iHue = GetHValue (rC);
		short iBright = GetVValue (rC);
		
			rC = HSB (e.GetPos(), iBright, iHue);
			locC = *(Color *)&rC;
		} else {
			locC.Green() = BYTE(e.GetPos());
			locC.Reserved() = 0;	// echte Farbe (kein Index)
		}
		GreenScrollBar.SetColor (e.GetPos());
		break;
	}

// neue Farbe einstellen
	ModColor (&locC);
}

// DoppelClick auf ComboBox ---------------------------------------------------
void PaletteWindow :: ListBoxClk (ControlEvt) {}

// Einfacher Click auf ComboBox -----------------------------------------------
void PaletteWindow :: ListBoxSel (ControlEvt) 
{
short iCurrPos = QueryColor.LocControl() -> GetCurrentIndex();

	if (iCurrPos == -1) return;	// no selected item

ColorItem *pData = (ColorItem *)QueryColor.GetItem(iCurrPos);
Color locC = pData -> _C;

	if (m_fHSB) {
	unsigned long rC = RGBtoHSB (locC);
	
		locC = *(Color *)&rC;

		RedScrollBar.SetColor (GetHValue (rC));
		GreenScrollBar.SetColor (GetSValue (rC));
		BlueScrollBar.SetColor (GetVValue (rC));
	} else {
		locC.Reserved() = 0;	// sicherheitshalber

		RedScrollBar.SetColor (locC.Red());
		GreenScrollBar.SetColor (locC.Green());
		BlueScrollBar.SetColor (locC.Blue());
	}

	ModColor (&locC);	// ausgewählte Farbe einstellen

}

// bei FarbEditControl verändert sich Focus -----------------------------------
void PaletteWindow :: EditFocusChg (EditFocusChgEvt e) 
{
// wenn Focus erhalten, dann raus
	if (e.gotFocus()) return;

// entsprechenden RollBalken setzen
Color locC = ModColor();	// aktuelle Farbe holen

	switch ((uint)e.GetControlID ()) {
	case IDE_ROT:
		{
			if (m_fHSB) {
			unsigned long rC = *(unsigned long *)&locC;
			short iHue = RedScrollBar.CopyToScrollBar();
			short iSat = GetSValue (rC);
			short iBright = GetVValue (rC);
		
				rC = HSB (iSat, iBright, iHue);
				locC = *(Color *)&rC;
			} else 
				locC.Red() = (ColorVal)RedScrollBar.CopyToScrollBar();
		}
		break;

	case IDE_BLAU:
		{
			if (m_fHSB) {
			unsigned long rC = *(unsigned long *)&locC;
			short iBright = BlueScrollBar.CopyToScrollBar();
			short iSat = GetSValue (rC);
			short iHue = GetHValue (rC);
		
				rC = HSB (iSat, iBright, iHue);
				locC = *(Color *)&rC;
			} else 
				locC.Blue() = (ColorVal)BlueScrollBar.CopyToScrollBar();
		}
		break;

	case IDE_GRUEN:
		{
			if (m_fHSB) {
			unsigned long rC = *(unsigned long *)&locC;
			short iSat = GreenScrollBar.CopyToScrollBar();
			short iHue = GetHValue (rC);
			short iBright = GetVValue (rC);
		
				rC = HSB (iSat, iBright, iHue);
				locC = *(Color *)&rC;
			} else 
				locC.Green() = (ColorVal)GreenScrollBar.CopyToScrollBar();
		}
		break;
	}

// neue Farbe einstellen
	ModColor (&locC);
}

// Hilfe zu DialogFenster anzeigen --------------------------------------------
void PaletteWindow :: HelpShow (void) {}

// ResultatFunktionen ---------------------------------------------------------
Color &PaletteWindow :: GetMainColor (void) { return CBox().GetPenColor(); }

// Virtuelle Funktionen -------------------------------------------------------
Color PaletteWindow :: ModColor (Color *pC) 
{
	if (pC == NULL)	{	// nur Abfrage
	Color C = GetMainColor();
	
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
		CBox().SetColor (C);
		return *pC;
	}
}

// OwnerDrawEventHandler ------------------------------------------------------
Bool EXPORTTRIAS PaletteWindow :: DeleteItem (DeleteItemEvt e) 
{
ColorItem *pCI = (ColorItem *)e.GetItemData();	// Daten freigeben

	if (pCI) delete pCI;
	return TRUE;
}

Bool EXPORTTRIAS PaletteWindow :: DrawEntireItem (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	InflateRect ((LPRECT)&Rc, -3, -3);	// verkleinern

// Farbe wird als Farbrechteck mit zugehörigem Farbnamen dargestellt
// 1. Palette korrigieren
HPALETTE hPal = QueryColor.CorrectPalette (((ColorItem *)e.GetItemData()) -> _C);

// 2. Rechteck zeichnen
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
HPALETTE holdPal = NULL;

	if (hPal) {
		holdPal = SelectPalette (hDC, hPal, FALSE);
		RealizePalette (hDC);
	}

COLORREF ColIndex = PALETTEINDEX (GetNearestPaletteIndex (hPal, 
			*(COLORREF *)&(((ColorItem *)e.GetItemData()) -> _C)));

HBRUSH hBr = CreateSolidBrush (ColIndex);
CoOrd dX = Rc.Bottom()-Rc.Top();
Rectangle RcCol (Rc.Top(), Rc.Left(), Rc.Top()+dX, Rc.Left()+2*dX);

// FarbBereich ausmalen
	FillRect (hDC, (LPRECT)&RcCol, hBr);
	DeleteObject (hBr);

// 3. Text dazuschreiben
char *_ColName = ((ColorItem *)e.GetItemData()) -> _Name;
Rectangle RcText (Rc.Top()-3, RcCol.Right(), Rc.Bottom()+3, Rc.Right());

	ExtTextOut (hDC, RcText.Left(), RcText.Top(), 
			ETO_CLIPPED|ETO_OPAQUE, (const RECT *)&RcText, 
			_ColName, strlen (_ColName), 
			NULL
		 );

	if (e.isSelected()) DrawItemSelect (e);	
	if (e.hasFocus()) DrawItemFocus (e);

	if (hPal) 
		SelectPalette (hDC, holdPal, FALSE);

return TRUE;
}

Bool EXPORTTRIAS PaletteWindow :: DrawItemFocus (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	InflateRect ((LPRECT)&Rc, -3, -3);	// verkleinern

HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen

// FarbRechteck bestimmen
CoOrd dX = Rc.Bottom()-Rc.Top();
Rectangle RcCol (Rc.Top(), Rc.Left(), Rc.Top()+dX, Rc.Left()+2*dX);

	InflateRect ((LPRECT)&RcCol, 2, 2);	// vergrößern

	if (e.hasFocus()) {
	// Rechteck zeichnen
		FrameRect (hDC, (LPRECT)&RcCol, (HBRUSH)GetStockObject (BLACK_BRUSH));
	} else {
	// SelektionsRechteck wegmachen
	HBRUSH hbr = CreateSolidBrush (GetSysColor (COLOR_WINDOW));

		FrameRect (hDC, (LPRECT)&RcCol, hbr);
		DeleteObject (hbr);
	}

return TRUE;
}

Bool EXPORTTRIAS PaletteWindow :: DrawItemSelect (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	InflateRect ((LPRECT)&Rc, -3, -3);	// verkleinern

HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen

// Farbrechteck reproduzieren
CoOrd dX = Rc.Bottom()-Rc.Top();
Rectangle RcCol (Rc.Top(), Rc.Left(), Rc.Top()+dX, Rc.Left()+2*dX);

	InflateRect ((LPRECT)&RcCol, 3, 3);	// vergrößern

	if (e.isSelected()) {
	// Rechteck zeichnen
		FrameRect (hDC, (LPRECT)&RcCol, (HBRUSH)GetStockObject (GRAY_BRUSH));
	} else {
	// SelektionsRechteck wegmachen
	HBRUSH hbr = CreateSolidBrush (GetSysColor (COLOR_WINDOW));

		FrameRect (hDC, (LPRECT)&RcCol, hbr);
		DeleteObject (hbr);
	}

return TRUE;
}

// Vergleich zweier DarstellungsFarben 
int EXPORTTRIAS PaletteWindow :: CompareItem (OwnerDrawEvt, void *pData1, void *pData2) 
{
ColorItem *pCI1 = (ColorItem *)pData1;
ColorItem *pCI2 = (ColorItem *)pData2;

	if (QueryColor.GetSearchMode() == ColorListBox :: SM_Color) 
	// nach Farben sortieren
		return CmpColor (pCI1 -> _C, pCI2 -> _C);
	else 
	// nach Namen sortieren
		return strcmp (pCI1 -> _Name, pCI2 -> _Name);
}

Bool EXPORTTRIAS PaletteWindow :: MeasureItem (MeasureItemEvt e) 
{
TEXTMETRIC tm;
HWND hDlg = e.Handle (API_DLGWINDOW_HWND);
HDC hDC = GetDC (hDlg);

	GetTextMetrics (hDC, &tm);
	e.SetItemHeight (tm.tmHeight);
	ReleaseDC (hDlg, hDC);

return TRUE;
}

// eigener EventDispatcher für PalettenHandling -------------------------------
long EXPORTTRIAS PaletteWindow :: Dispatch (Event e) 
{
	return OwnerDrawDialogWindow :: Dispatch (e);
}

