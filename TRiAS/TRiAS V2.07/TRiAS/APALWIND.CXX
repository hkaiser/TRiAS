// Routinen fuer PaletteWindow ------------------------------------------------
// File: APALWIND.CXX

#include "triaspre.hxx"

#include <rgb_hsb.hxx>
#include <owncombo.hxx>

#include "palwind.h"

#include "clbmpobj.hxx"
#include "dcolor.hxx"
#include "feature.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"

#include "triasres.h"

#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelpRGB[] = {
	IDC_FARBEN, 	IDH_AREAFARBSELEKTION_IDC_FARBEN, 
	IDT_FARBAUSWAHL, IDH_AREAFARBSELEKTION_IDC_FARBEN, 
	IDC_STYLE, 	IDH_AREAFARBSELEKTION_IDC_STYLE, 
	IDT_STYLE, 	IDH_AREAFARBSELEKTION_IDC_STYLE, 
	IDE_LINEWIDTH, 	IDH_AREAFARBSELEKTION_IDE_LINEWIDTH, 
	IDCC_LINEWIDTH, IDH_AREAFARBSELEKTION_IDE_LINEWIDTH, 
	IDT_LINEWIDTH, 	IDH_AREAFARBSELEKTION_IDE_LINEWIDTH, 
	IDC_BKCONTURE, 	IDH_AREAFARBSELEKTION_IDC_BKCONTURE, 
	IDSB_ROT, 	IDH_AREAFARBSELEKTION_ID_ROT, 
	IDE_ROT, 	IDH_AREAFARBSELEKTION_ID_ROT, 
	IDT_ROT, 	IDH_AREAFARBSELEKTION_ID_ROT, 
	IDSB_GRUEN, 	IDH_AREAFARBSELEKTION_ID_GRUEN, 
	IDE_GRUEN, 	IDH_AREAFARBSELEKTION_ID_GRUEN, 
	IDT_GRUEN, 	IDH_AREAFARBSELEKTION_ID_GRUEN, 
	IDSB_BLAU, 	IDH_AREAFARBSELEKTION_ID_BLAU, 
	IDE_BLAU, 	IDH_AREAFARBSELEKTION_ID_BLAU, 
	IDT_BLAU, 	IDH_AREAFARBSELEKTION_ID_BLAU, 
	IDT_FARBE, 	IDH_AREAFARBSELEKTION_IDT_FARBE, 
	IDR_SCNDCOLOR, 	IDH_AREAFARBSELEKTION_IDR_SCNDCOLOR, 
	IDR_FRSTCOLOR, 	IDH_AREAFARBSELEKTION_IDR_FRSTCOLOR, 
	IDCB_TRANSPARENT, IDH_AREAFARBSELEKTION_IDCB_TRANSPARENT, 
	IDOK, 		IDH_AREAFARBSELEKTION_IDOK, 
	IDCANCEL, 	IDH_AREAFARBSELEKTION_IDCANCEL, 
	0,		0,		// EndeKennung
};

static DWORD s_dwHelpHSB[] = {
	IDC_FARBEN, 	IDH_AREAFARBSELEKTION_IDC_FARBEN, 
	IDT_FARBAUSWAHL, IDH_AREAFARBSELEKTION_IDC_FARBEN, 
	IDC_STYLE, 	IDH_AREAFARBSELEKTION_IDC_STYLE, 
	IDT_STYLE, 	IDH_AREAFARBSELEKTION_IDC_STYLE, 
	IDE_LINEWIDTH, 	IDH_AREAFARBSELEKTION_IDE_LINEWIDTH, 
	IDCC_LINEWIDTH, IDH_AREAFARBSELEKTION_IDE_LINEWIDTH, 
	IDT_LINEWIDTH, 	IDH_AREAFARBSELEKTION_IDE_LINEWIDTH, 
	IDC_BKCONTURE, 	IDH_AREAFARBSELEKTION_IDC_BKCONTURE, 
	IDSB_ROT, 	IDH_AREAFARBSELEKTION_ID_HUE, 
	IDE_ROT, 	IDH_AREAFARBSELEKTION_ID_HUE, 
	IDT_ROT, 	IDH_AREAFARBSELEKTION_ID_HUE, 
	IDSB_GRUEN, 	IDH_AREAFARBSELEKTION_ID_SATURATION, 
	IDE_GRUEN, 	IDH_AREAFARBSELEKTION_ID_SATURATION, 
	IDT_GRUEN, 	IDH_AREAFARBSELEKTION_ID_SATURATION, 
	IDSB_BLAU, 	IDH_AREAFARBSELEKTION_ID_BRIGHTNESS, 
	IDE_BLAU, 	IDH_AREAFARBSELEKTION_ID_BRIGHTNESS, 
	IDT_BLAU, 	IDH_AREAFARBSELEKTION_ID_BRIGHTNESS, 
	IDT_FARBE, 	IDH_AREAFARBSELEKTION_IDT_FARBE, 
	IDR_SCNDCOLOR, 	IDH_AREAFARBSELEKTION_IDR_SCNDCOLOR, 
	IDR_FRSTCOLOR, 	IDH_AREAFARBSELEKTION_IDR_FRSTCOLOR, 
	IDCB_TRANSPARENT, IDH_AREAFARBSELEKTION_IDCB_TRANSPARENT, 
	IDOK, 		IDH_AREAFARBSELEKTION_IDOK, 
	IDCANCEL, 	IDH_AREAFARBSELEKTION_IDCANCEL, 
	0,		0,		// EndeKennung
};

void AreaPaletteWindow :: HelpRequest (HelpRequestEvt e)
{
	if (HelpWmHelp == e.RequestType()) {
	const HELPINFO *pHI = e.GetHelpInfo();
	char cbHelpFile[_MAX_PATH];

		strcpy (cbHelpFile, g_cbHelpPath);
		strcat (cbHelpFile, DIALOG_HELP_FILE);

		WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, HELP_WM_HELP, 
			 m_fHSB ? (DWORD)s_dwHelpHSB : (DWORD)s_dwHelpRGB);
	}
}

#endif

// abgeleitete Fenster für Punkt-/Linien- und Flächenobjkete ------------------
#pragma warning (disable: 4355)

#if defined(OLDVISINFO)
AreaPaletteWindow :: AreaPaletteWindow (pWindow pW, DatenBasisObjekt &rDBO, Color MainC, Color SecC, 
					short Style, bool fHSB)
#else
inline short CorrectWidth (short iWidth) { return iWidth >= 0 ? short(iWidth) : 0; }

AreaPaletteWindow :: AreaPaletteWindow (pWindow pW, DatenBasisObjekt &rDBO, Color MainC, Color SecC, 
					short Style, short iWidth, bool fHSB, 
					bool fBkConture, bool fOpaque)
#endif // OLDVISINFO
		   : PaletteWindow (AREAFARBSELEKTION, pW, rDBO, SecC, fHSB),
		     ShowArea (this, rDBO, IDT_FARBE, MainC, SecC, Style),
		     FillStyles (this, IDC_STYLE),
		     FirstColor (this, IDR_FRSTCOLOR),
		     SecondColor (this, IDR_SCNDCOLOR),
		     LineWidth (this, IDE_LINEWIDTH, IDCC_LINEWIDTH, Range (0, SHRT_MAX/100)),
		     _Transparent (this, IDCB_TRANSPARENT),
		     m_cbBkConture (this, IDC_BKCONTURE)
{
// fehlende Buttons ausblenden
//	NewButton.Hide();
//	DelButton.Hide();

// Controls initialisieren
#if defined(OLDVISINFO)
	FillStyles.FInit (short((Style & ~BMOpaque) % 100));
	LineWidth.SetValue (short((_oldStyle / 100) > 0 ? _oldStyle / 100 : 0));

	_oldStyle = short(Style & ~BMOpaque);	// Parameter setzen
	if ((StdHatchStyle)(_oldStyle % 100) > DiagonalCrossHatch +1) {
		AdjustBkMode (OPAQUE);
		_Transparent.Disable();
	} else
		AdjustBkMode (Style & BMOpaque ? OPAQUE : TRANSPARENT);
	m_cbBkConture.Disable();
#else
	FillStyles.FInit (short(Style));
	LineWidth.SetValue (CorrectWidth (iWidth));

	_oldStyle = short(Style);	// Parameter setzen
	m_iOldWidth = iWidth;
	m_fOldBkConture = fBkConture;

#if !defined(TRANSPARENT_PATTERNS)
	if ((StdHatchStyle)(_oldStyle) > DiagonalCrossHatch +1) 
#else
	if (m_rDBO.Compatibility() &&
		((StdHatchStyle)(_oldStyle) > DiagonalCrossHatch +1)) 
#endif // TRANSPARENT_PATTERNS
	{
		AdjustBkMode (TRANSPARENT, fBkConture);
		_Transparent.Disable();
	} else if ((StdHatchStyle)(_oldStyle) <= SolidHatch +1) {
		AdjustBkMode (TRANSPARENT, false);
		_Transparent.Disable();
	} else {
		if (fOpaque) 
			AdjustBkMode (OPAQUE, fBkConture);
		else
			AdjustBkMode (TRANSPARENT, false);
	}
#endif // OLDVISINFO

	_oldSecC = SecC;

// Anfangszustand definiert setzen
	QueryColor.LocControl() -> SetFocus ();

// RadioButtons initialisieren
	FirstColor.SetState (false);
	SecondColor.SetState (true);

// Scrollmode auf fein einstellen
	RedScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	GreenScrollBar.SetMode (ColorScrollBar :: SB_Fine);
	BlueScrollBar.SetMode (ColorScrollBar :: SB_Fine);

// neuen Mode aktivieren
Color C = ModColor();
		
	ModColor (&C);
}

#pragma warning (default: 4355)

// Destruktoren ---------------------------------------------------------------
AreaPaletteWindow :: ~AreaPaletteWindow (void) {}

// EventHandler (das Leben der DialogBox) -------------------------------------
// Nutzer drückt Knöpfchen ----------------------------------------------------
void AreaPaletteWindow :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDOK:	// OKButton
		if (LineWidth.isModified()) {
			LineWidth.CopyToSpin();
			SetWidth (LineWidth.GetValue());
		}
		PaletteWindow :: ButtonClick (e);
		break;

	case IDCANCEL:
	// alte Füllfarbe wieder einstellen
		GetFillColor () = _oldSecC;
#if defined(OLDVISINFO)
		SetFillStyle (short(_oldStyle % 100));
		SetWidth (short(_oldStyle / 100));
#else
		SetFillStyle (short(_oldStyle));
		SetWidth (short(m_iOldWidth));
		SetBkConture (m_fOldBkConture);
#endif // OLDVISINFO

	// und dann an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;

	case IDR_FRSTCOLOR:
		{
		bool fChanged = false;

			if (GetKeyState (VK_CONTROL) < 0) {
			// Control-Taste zusätzlich gedrückt
				GetMainColor() = GetFillColor();
				fChanged = true;
			} 
		
		// ScrollBalken entsprechend RandFarbe setzen
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

	case IDR_SCNDCOLOR:
		{
		bool fChanged = false;

			if (GetKeyState (VK_CONTROL) < 0) {
			// Control-Taste zusätzlich gedrückt
				GetFillColor() = GetMainColor();
				fChanged = true;
			}

		// ScrollBalken entsprechend FüllFarbe setzen
		Color C = GetFillColor();

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

#if defined(OLDVISINFO)
	case IDCB_TRANSPARENT:
		AdjustBkMode (_Transparent.isChecked() ? TRANSPARENT : OPAQUE);
		break;

#else
	case IDCB_TRANSPARENT:
	case IDC_BKCONTURE:
		if (_Transparent.isChecked())
			AdjustBkMode (TRANSPARENT, false);
		else 
			AdjustBkMode (OPAQUE, m_cbBkConture.isChecked());
		break;
#endif
				
	default:
	// an PaletteWindow weiterreichen
		PaletteWindow :: ButtonClick (e);
		break;
	}
}

void AreaPaletteWindow :: Expose (ExposeEvt) 
{
	ShowArea.RePaint();
}

// ResultatFunktionen ---------------------------------------------------------
Color &AreaPaletteWindow :: GetFillColor (void) { return ShowArea.GetBrushColor(); }
short AreaPaletteWindow :: GetFillStyle (void) { return short(ShowArea.GetStyle()%100); }
short AreaPaletteWindow :: GetWidth (void) { return short(ShowArea.GetStyle()/100); }
short AreaPaletteWindow :: GetBkMode (void) { return _Transparent.isChecked() ? 0 : short(BMOpaque); }

#if !defined(OLDVISINFO)
short AreaPaletteWindow :: GetBkContureMode (void) { return m_cbBkConture.isChecked() ? short(BMBkConture) : 0; }

void AreaPaletteWindow :: SetFillStyle (short newStyle) 
{
	ShowArea.GetStyle() = short(((ShowArea.GetStyle() / 100) * 100) + newStyle);
}

void AreaPaletteWindow :: SetWidth (short newWidth) 
{
	if (newWidth <= 0) newWidth = 1;
	ShowArea.GetStyle() = short((ShowArea.GetStyle() % 100) + (newWidth * 100));
}

void AreaPaletteWindow :: SetBkConture (bool fBkConture) 
{
	ShowArea.SetBkConture (fBkConture);
}
#else
void AreaPaletteWindow :: SetFillStyle (short newStyle) 
{
	ShowArea.GetStyle() = short(((ShowArea.GetStyle() / 100) * 100) + newStyle);
}

void AreaPaletteWindow :: SetWidth (short newWidth) 
{
	if (newWidth <= 0) newWidth = 1;
	ShowArea.GetStyle() = short((ShowArea.GetStyle() % 100) + (newWidth * 100));
}
#endif // OLDVISINFO

// Virtuelle Funktionen -------------------------------------------------------
Color AreaPaletteWindow :: ModColor (Color *pC) 
{
	if (FirstColor.GetState())
		return PaletteWindow :: ModColor (pC);	// Randfarbe bearbeiten

	if (pC == NULL) {	// nur Abfrage
	Color C = GetFillColor();	// Füllfarbe abfragen
	
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

ColorBox &AreaPaletteWindow :: CBox (void) { return ShowArea; }

// OwnerDrawEventHandler ------------------------------------------------------
// das Gleiche für AreaPaletteWindow ------------------------------------------
bool EXPORTTRIAS AreaPaletteWindow :: DeleteItem (DeleteItemEvt e) 
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

bool EXPORTTRIAS AreaPaletteWindow :: DrawEntireItem (DrawItemEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		// Einen Eintrag malen
		Rectangle Rc = e.ItemSize();	// aktuellen Bereich holen

			InflateRect ((LPRECT)&Rc, -3, -3);	// verkleinern

		// 1. Rechteck zeichnen
		Feature *pData = (Feature *)e.GetItemData();
		HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
		pBrush pBr = NULL;
		pBitmap pBM = NULL;

			if (pData -> _Style > 0) {
				if ((StdHatchStyle)pData -> _Style > DiagonalCrossHatch+1) {
				// Bitmap als Brush verwenden
					pBM = new Bitmap (ResID (pData -> _Style + FIRSTFILLBMP));
					if (pBM == NULL) return false;
					pBr = new Brush (pBM);
				} else 
					pBr = new Brush (Color (Colors(BLACK)), 
							 (StdHatchStyle)(pData -> _Style -1));
			} else 
				pBr = new Brush (HollowBrush);

			if (pBr == NULL) return false;

		HBRUSH hBr = pBr -> Handle();
		CoOrd dX = CoOrd(Rc.Bottom()-Rc.Top());

		// Stile selektieren
		HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, hBr);

		// Bereich entsprechend Stil ausmalen
			DrawRectangle (hDC, Rc.Left(), Rc.Top(), Rc.Left()+2*dX, Rc.Top()+dX);
			SelectObject (hDC, hOldBr);

		// 2. Text dazuschreiben
		char *StyleName = pData -> _StyleName;
		Rectangle RcText (CoOrd(Rc.Top()-3), CoOrd(Rc.Left()+2*dX), 
				  CoOrd(Rc.Bottom()+3), CoOrd(Rc.Right()));

			ExtTextOut (hDC, RcText.Left(), RcText.Top(), 
					ETO_CLIPPED|ETO_OPAQUE, 
					(const RECT *)&RcText, 
					StyleName, strlen (StyleName), 
					NULL
				 );
			DELETE (pBr);
			DELETE (pBM);

			if (e.isSelected()) DrawItemSelect (e);
			if (e.hasFocus()) DrawItemFocus (e);
		}
		return true;

	case IDC_FARBEN:
		return PaletteWindow :: DrawEntireItem (e);
	}

return false;
}

int EXPORTTRIAS AreaPaletteWindow :: CompareItem (OwnerDrawEvt e, void *pData1, void *pData2) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:
		{
		Feature *pF1 = (Feature *)pData1;
		Feature *pF2 = (Feature *)pData2;

			switch (FillStyles.GetSearchMode()) {
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

return false;
}

void AreaPaletteWindow :: ListBoxSel (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:		// Füllmode ausgewählt
		{
		short iCurrPos = short(FillStyles.LocControl() -> GetCurrentIndex());

			if (iCurrPos == -1) return;	// no selected item

		Feature *pData = (Feature *)FillStyles.GetItem(iCurrPos);

			SetFillStyle (pData -> _Style);

		// Transparent nur für StandardFüllModi erlauben
#if !defined(TRANSPARENT_PATTERNS)
			if ((StdHatchStyle)pData -> _Style > DiagonalCrossHatch +1) 
#else
			if (m_rDBO.Compatibility() &&
				(StdHatchStyle)pData -> _Style > DiagonalCrossHatch +1) 
#endif // TRANSPARENT_PATTERNS
			{
				AdjustBkMode (OPAQUE, m_cbBkConture.isChecked());
				_Transparent.Disable();
			} else if ((StdHatchStyle)pData -> _Style <= SolidHatch +1) {
				AdjustBkMode (TRANSPARENT, false);
				_Transparent.Disable();
			} else {
				AdjustBkMode (_oldBkMode, false);
				_Transparent.Enable();
			}

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


void AreaPaletteWindow :: ListBoxClk (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDC_STYLE:		// Füllmode ausgewählt und raus
		break;

	case IDC_FARBEN:
		PaletteWindow :: ListBoxClk (e);
		return;
	}
}

void AreaPaletteWindow :: VertScroll (ScrollEvt e)
{
	if (e.GetScrollBar() -> GetID() != IDCC_LINEWIDTH)
		return;

	LineWidth.CopyToEdit();
	SetWidth (LineWidth.GetValue());

// neuen Mode aktivieren
Color C = ModColor ();
	
	ModColor (&C);
}

void AreaPaletteWindow :: EditFocusChg (EditFocusChgEvt e)
{
	if ((uint)e.GetControlID() == IDE_LINEWIDTH) {
		if (e.gotFocus()) 
			return;

	// Wert neu setzen
		if (LineWidth.GetValue() > SHRT_MAX/100) {
			LineWidth.SetValue (SHRT_MAX/100);
			MessageBeep (0);
		}
		LineWidth.CopyToSpin();
		SetWidth (LineWidth.GetValue());

	// neuen Mode aktivieren
	Color C = ModColor();
	
		ModColor (&C);
	} else
		PaletteWindow :: EditFocusChg (e);	// weiterreichen
}

#if defined(OLDVISINFO)
void AreaPaletteWindow :: AdjustBkMode (short iBkMode)
{
	_oldBkMode = iBkMode;
	if (_oldBkMode == OPAQUE) {
	ResString rs1st (IDS_1STCOLOROPAQUE, 40);
	ResString rs2nd (IDS_2NDCOLOROPAQUE, 40);
	
		_Transparent.SetChecked (false);
		FirstColor.SetText (rs1st);
		SecondColor.SetText (rs2nd);
		ShowArea.SetBkMode (true);
	} else {
	ResString rs1st (IDS_1STCOLORTRANSPARENT, 40);
	ResString rs2nd (IDS_2NDCOLORTRANSPARENT, 40);
	
		_Transparent.SetChecked (true);
		FirstColor.SetText (rs1st);
		SecondColor.SetText (rs2nd);
		ShowArea.SetBkMode (false);
	}
// neuen Mode aktivieren
Color C = ModColor ();
		
	ModColor (&C);
}
#else
void AreaPaletteWindow :: AdjustBkMode (short iBkMode, bool fBkConture)
{
	_oldBkMode = iBkMode;
	m_fOldBkConture = fBkConture;
	
	if (_oldBkMode == OPAQUE) {
	ResString rs1st (IDS_1STCOLOROPAQUE, 40);
	ResString rs2nd (IDS_2NDCOLOROPAQUE, 40);
	
		_Transparent.SetChecked (false);
		FirstColor.SetText (rs1st);
		SecondColor.SetText (rs2nd);
		ShowArea.SetBkMode (true);
		
		m_cbBkConture.Enable();
		m_cbBkConture.SetChecked (fBkConture);
		ShowArea.SetBkConture (fBkConture);
	} else {
	ResString rs1st (IDS_1STCOLORTRANSPARENT, 40);
	ResString rs2nd (IDS_2NDCOLORTRANSPARENT, 40);
	
		_Transparent.SetChecked (true);
		FirstColor.SetText (rs1st);
		SecondColor.SetText (rs2nd);
		ShowArea.SetBkMode (false);
		
		m_cbBkConture.SetChecked (false);
		m_cbBkConture.Disable();
		ShowArea.SetBkConture (false);
	}
	
// neuen Mode aktivieren
Color C = ModColor ();
		
	ModColor (&C);
}
#endif // OLDVISINFO
