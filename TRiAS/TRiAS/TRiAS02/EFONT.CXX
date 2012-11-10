// Erweiterungen in der FontKlasse -------------------------------------------
// File: EFONT.CXX

#include "trias02p.hxx"

#include <windowsx.h>

#include "fontsel.h"
#include "trias02.h"

#include "trias03m.hxx"		// _TRIAS03_ENTRY und EXPORT02

#include <prntpars.hxx>
#include <VisInfo.hxx>

#include "efont.hxx"

extern "C" HINSTANCE g_hInstance;

// Hier geht's richtig los ----------------------------------------------------
EXPORT02 ExtFont :: ExtFont (StdFamily family, Dimension size, const char* typeface)
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	 : CVFont (family, size, typeface)
#else
	 : Font (family, size, typeface)
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
{
	// nothing to do
}

EXPORT02 ExtFont :: ExtFont (StdFonts id)
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	 : CVFont (id)
#else
	 : Font (id)
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
{
	// nothing to do
}


// #HK920824 ------------------------------------------------------------------
short ExtFont :: SetOrientation (short newOr) 
{
short oldOr = short(font_Imp -> lft -> lfOrientation);

	if (font_Imp -> lft -> lfOrientation != newOr) {
		font_Imp -> lft -> lfOrientation = newOr;
		font_Imp -> FntChanged = 1;
	}

return oldOr;
}


short ExtFont :: SetEscapement (short newOr) 
{
short oldOr = short(font_Imp -> lft -> lfEscapement);

	if (font_Imp -> lft -> lfEscapement != newOr) {
		font_Imp -> lft -> lfEscapement = newOr;
		font_Imp -> FntChanged = 1;
	}

return oldOr;
}
// ----------------------------------------------------------------------------

bool ExtFont :: FontChanged (void) 
{
	return font_Imp -> FntChanged;
}

ExtFont :: ~ExtFont (void)
{
	// nothing to do
}
							   

// zusätzlich zu WINDOWS.H ----------------------------------------------------
#define FF_FAMILYMASK	0xf0

extern "C" {

typedef struct tagCHOOSEFONTEX {
	CHOOSEFONT cfeCF;		// CHOOSEFONT
	bool cfeBKMode;			// Transparent/Opaque
	bool cfeFrameMode;		// Rahmen/ohne Rahmen
	bool cfeRoundFrame;		// Runde Ecken
	int cfeEscapement;
	int cfeOrientation;
	int cfeCustom;			// Objektbezogene Visualiserung
// #HK951124
	bool cfeLeftText;		// Linksbündig
	bool cfeCentredText;
	bool cfeRightText;
	bool cfeJustified;
} CHOOSEFONTEX;

static CHOOSEFONTEX ChFntEx;

#if defined(WIN32)
UINT EXPORT02 APIENTRY SelEFontHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
#else
UINT EXPORT02 WINAPI SelEFontHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
#endif
{
	switch (wMsg) {
	case WM_INITDIALOG:
		{
#if !defined(WIN32)
		// CTL3D initialisieren
			if (Ctl3dEnabled()) // lediglich CTL3D aktivieren
				Ctl3dSubclassDlg (hDlg, CTL3D_ALL);	
#endif // WIN32

		// Caption setzen
		char *lpCaption = (char *) (ChFntEx.cfeCF.lCustData);

			if (lpCaption) SetWindowText (hDlg, lpCaption);

		// zusätzliche Controls initialisieren
			CheckDlgButton (hDlg, IDCB_FONTFRAMED, ChFntEx.cfeFrameMode);
			if (ChFntEx.cfeFrameMode) {
				CheckDlgButton (hDlg, IDCB_FONTTRANSPARENT, ChFntEx.cfeBKMode);
				EnableWindow (GetDlgItem (hDlg, IDCB_FONTTRANSPARENT), true);
				if (ChFntEx.cfeCustom) {
					EnableWindow (GetDlgItem (hDlg, IDCB_ROUNDFRAME), true);
					CheckDlgButton (hDlg, IDCB_ROUNDFRAME, ChFntEx.cfeRoundFrame);
				}
			} else {
				CheckDlgButton (hDlg, IDCB_FONTTRANSPARENT, false);
				EnableWindow (GetDlgItem (hDlg, IDCB_FONTTRANSPARENT), false);
				if (ChFntEx.cfeCustom) {
					EnableWindow (GetDlgItem (hDlg, IDCB_ROUNDFRAME), false);
					CheckDlgButton (hDlg, IDCB_ROUNDFRAME, false);
				}
			}

			SetDlgItemInt (hDlg, IDE_FONTESCAPEMENT, ChFntEx.cfeEscapement, true);
			if (ChFntEx.cfeCustom) {
			// vorerst für Win3.1
				EnableWindow (GetDlgItem (hDlg, IDE_FONTORIENTATION), false);
				EnableWindow (GetDlgItem (hDlg, IDT_FONTORIENTATION), false);

				SetDlgItemInt (hDlg, IDE_FONTORIENTATION, ChFntEx.cfeOrientation, true);

#if defined(WIN32)
				CheckDlgButton (hDlg, IDCB_LEFTTEXT, ChFntEx.cfeLeftText);
				CheckDlgButton (hDlg, IDCB_CENTREDTEXT, ChFntEx.cfeCentredText);
				CheckDlgButton (hDlg, IDCB_RIGHTTEXT, ChFntEx.cfeRightText);
				CheckDlgButton (hDlg, IDCB_JUSTIFIED, ChFntEx.cfeJustified);
#endif // WIN32
			} else {
				EnableWindow (GetDlgItem (hDlg, IDE_FONTORIENTATION), false);
				EnableWindow (GetDlgItem (hDlg, IDT_FONTORIENTATION), false);
				EnableWindow (GetDlgItem (hDlg, IDCB_ROUNDFRAME), false);
			}
		}
		break;

	case WM_COMMAND:
		{
		UINT uiID = GET_WM_COMMAND_ID (wParam, lParam);
//		HWND hCntrl = GET_WM_COMMAND_HWND (wParam, lParam);
		UINT uiCmd = GET_WM_COMMAND_CMD (wParam, lParam);

	// CheckFlags und EditControls auslesen
		switch (uiID) {
		case IDCB_FONTFRAMED:
			ChFntEx.cfeFrameMode = (bool)IsDlgButtonChecked (hDlg, IDCB_FONTFRAMED);
			if (ChFntEx.cfeFrameMode) {
				EnableWindow (GetDlgItem (hDlg, IDCB_FONTTRANSPARENT), true);
				CheckDlgButton (hDlg, IDCB_FONTTRANSPARENT, ChFntEx.cfeBKMode);
				if (ChFntEx.cfeCustom) {
					EnableWindow (GetDlgItem (hDlg, IDCB_ROUNDFRAME), true);
					CheckDlgButton (hDlg, IDCB_ROUNDFRAME, ChFntEx.cfeRoundFrame);
				}
			} else {
				CheckDlgButton (hDlg, IDCB_FONTTRANSPARENT, false);
				EnableWindow (GetDlgItem (hDlg, IDCB_FONTTRANSPARENT), false);
				if (ChFntEx.cfeCustom) {
					EnableWindow (GetDlgItem (hDlg, IDCB_ROUNDFRAME), false);
					CheckDlgButton (hDlg, IDCB_ROUNDFRAME, false);
				}
			}
			return true;

		case IDCB_ROUNDFRAME:		// runde Ecken
			ChFntEx.cfeRoundFrame = (bool)IsDlgButtonChecked (hDlg, IDCB_ROUNDFRAME);
			return true;
			
		case IDCB_FONTTRANSPARENT:
			ChFntEx.cfeBKMode = (bool)IsDlgButtonChecked (hDlg, IDCB_FONTTRANSPARENT);
			return true;
			
#if defined(WIN32)
		case IDCB_LEFTTEXT:
		case IDCB_CENTREDTEXT:
		case IDCB_RIGHTTEXT:
		case IDCB_JUSTIFIED:
			ChFntEx.cfeLeftText = (bool)IsDlgButtonChecked (hDlg, IDCB_LEFTTEXT);
			ChFntEx.cfeCentredText = (bool)IsDlgButtonChecked (hDlg, IDCB_CENTREDTEXT);
			ChFntEx.cfeRightText = (bool)IsDlgButtonChecked (hDlg, IDCB_RIGHTTEXT);
			ChFntEx.cfeJustified = (bool)IsDlgButtonChecked (hDlg, IDCB_JUSTIFIED);
			return true;
#endif // WIN32

		case IDE_FONTESCAPEMENT: 
			if (uiCmd == EN_CHANGE) {
			BOOL fTranslated = false;
			int iVal = (int)GetDlgItemInt (hDlg, IDE_FONTESCAPEMENT, &fTranslated, true);
			int iLen = (int)SendDlgItemMessage (hDlg, IDE_FONTESCAPEMENT, EM_LINELENGTH, 0, 0L);

				if (iLen == 1) {
				short inChar = '\0';
				
					GetDlgItemText (hDlg, IDE_FONTESCAPEMENT, (LPSTR)&inChar, 2);
					if (inChar == '-') iLen = 0;
				}			
				if (iLen > 0 && (!fTranslated || iVal < -1800 || iVal > 1800)) {
					MessageBeep (0);
					SetFocus (GetDlgItem (hDlg, IDE_FONTESCAPEMENT));
				} else if (iLen > 0)
					ChFntEx.cfeEscapement = iVal;
				return true;			
			}
			break;
			
		case IDE_FONTORIENTATION:
			if (uiCmd == EN_CHANGE && ChFntEx.cfeCustom) {
			BOOL fTranslated = false;
			int iVal = (int)GetDlgItemInt (hDlg, IDE_FONTORIENTATION, &fTranslated, true);
			int iLen = (int)SendDlgItemMessage (hDlg, IDE_FONTORIENTATION, EM_LINELENGTH, 0, 0L);
			
				if (iLen == 1) {
				short inChar = '\0';
				
					GetDlgItemText (hDlg, IDE_FONTORIENTATION, (LPSTR)&inChar, 2);
					if (inChar == '-') iLen = 0;
				}			
				if (iLen > 0 && (!fTranslated || iVal < -1800 || iVal > 1800)) {
					MessageBeep (0);
					SetFocus (GetDlgItem (hDlg, IDE_FONTORIENTATION));
				} else if (iLen > 0)
					ChFntEx.cfeOrientation = iVal;
				return true;
			}
			break;

		default:
			break;
		}
		}
		break;

	default:
		break;
	}

return false;
}

}	// extern "C"

#if !defined(WIN32)
typedef UINT (WINAPI *LPCFHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
#endif
		
bool ExtFont :: ChooseFont (HWND hWnd, char *lpCaption, 
			    TVisInfo **ppTVI, PrinterPars &PPDev, short fCustom) 
{
	if (*ppTVI == NULL) return false;

//	ChFntEx.cfeCustom = fCustom;	// objektbezogene Visualisierung
	ChFntEx.cfeCustom = true;

// Struktur zur FontAuswahl initialisieren
	ChFntEx.cfeCF.lStructSize    = sizeof (CHOOSEFONT);
	ChFntEx.cfeCF.hwndOwner      = hWnd;
	ChFntEx.cfeCF.Flags          = CF_BOTH | CF_SCALABLEONLY | CF_WYSIWYG | 
				       CF_EFFECTS | CF_INITTOLOGFONTSTRUCT |
				       CF_ENABLETEMPLATE | CF_ENABLEHOOK;
	ChFntEx.cfeCF.rgbColors      = *(COLORREF *)&((*ppTVI) -> PrimColor());	
	ChFntEx.cfeCF.lCustData      = (DWORD)lpCaption;
	ChFntEx.cfeCF.lpfnHook	     = (LPCFHOOKPROC)SelEFontHookFcn;
#if !defined(WIN16)
	ChFntEx.cfeCF.lpTemplateName = ChFntEx.cfeCustom ? MAKEINTRESOURCE(IDD_SCHRIFTARTOBJ) : MAKEINTRESOURCE(FORMATDLGORD31);
#else
	ChFntEx.cfeCF.lpTemplateName = MAKEINTRESOURCE(FORMATDLGORD31);
#endif // !WIN16
	ChFntEx.cfeCF.hInstance      = g_hInstance;
	ChFntEx.cfeCF.lpszStyle      = (LPSTR)NULL;
	ChFntEx.cfeCF.nFontType      = SCREEN_FONTTYPE | PRINTER_FONTTYPE;
	ChFntEx.cfeCF.nSizeMin       = 0;
	ChFntEx.cfeCF.nSizeMax       = 0;

	ChFntEx.cfeCF.hDC = CreateIC (PPDev.DriverName(), 
				      PPDev.DeviceName(), 
				      PPDev.PortName(), NULL);
	ChFntEx.cfeCF.lpLogFont = font_Imp -> lft;

	ChFntEx.cfeBKMode = (*ppTVI) -> BKMode();
	ChFntEx.cfeFrameMode = (*ppTVI) -> FrameMode();
	ChFntEx.cfeEscapement = -(*ppTVI) -> Rotation();
	ChFntEx.cfeOrientation = -(*ppTVI) -> Orientation();
	ChFntEx.cfeRoundFrame = (*ppTVI) -> RoundFrame();

	ChFntEx.cfeLeftText = (*ppTVI) -> LeftAlign() ? true : false;
	ChFntEx.cfeCentredText = (*ppTVI) -> CentreAlign() ? true : false;
	ChFntEx.cfeRightText = (*ppTVI) -> RightAlign() ? true : false;
	ChFntEx.cfeJustified = (*ppTVI) -> Justified() ? true : false;
	
// Fenster anzeigen, Font auswählen lassen
	if (!::ChooseFont ((CHOOSEFONT *)&ChFntEx)) {	// globale Funktion aus dem WinAPI
		if (ChFntEx.cfeCF.hDC) 
			DeleteDC (ChFntEx.cfeCF.hDC);
		return false;
	}
	if (ChFntEx.cfeCF.hDC) DeleteDC (ChFntEx.cfeCF.hDC);

// VisInfo neu generieren, da alte VisInfo CDefaultVisInfo sein kann
TVisInfo *pNewVI = (TVisInfo *) (*ppTVI) -> TVisInfo :: Copy();

	if (pNewVI == NULL) return false;

// eingestellte Parameter wieder zurückschreiben
	pNewVI -> Size().Width() = font_Imp -> lft -> lfWidth;
	pNewVI -> Size().Height() = font_Imp -> lft -> lfHeight;
	pNewVI -> Rotation() = -ChFntEx.cfeEscapement;
	font_Imp -> lft -> lfEscapement = -ChFntEx.cfeEscapement;
	pNewVI -> Orientation() = -ChFntEx.cfeOrientation;
	font_Imp -> lft -> lfOrientation = -ChFntEx.cfeOrientation;
	pNewVI -> PrimColor() = *(Color *)&ChFntEx.cfeCF.rgbColors;

// Attribute des Fonts zurückschreiben
	if (font_Imp -> lft -> lfItalic)    pNewVI -> Type() |= TV_Italic;
	else				    pNewVI -> Type() &= ~TV_Italic;

	if (font_Imp -> lft -> lfUnderline) pNewVI -> Type() |= TV_Underlined;
	else				    pNewVI -> Type() &= ~TV_Underlined;

	if (font_Imp -> lft -> lfStrikeOut) pNewVI -> Type() |= TV_StrikedThru;
	else				    pNewVI -> Type() &= ~TV_StrikedThru;

	if (font_Imp -> lft -> lfPitchAndFamily & FIXED_PITCH) 
		pNewVI -> Type() |= TV_FixedPitch;
	else	
		pNewVI -> Type() &= ~TV_FixedPitch;	

	pNewVI -> Type() &= ~(TV_Bold | TV_Light);	// alles rücksetzen
	if (font_Imp -> lft -> lfWeight <= FW_LIGHT)	
		pNewVI -> Type() |= TV_Light;
	else if (font_Imp -> lft -> lfWeight >= FW_MEDIUM)	
		pNewVI -> Type() |= TV_Bold;

// SchriftTyp setzen
	pNewVI -> SetVisName (font_Imp -> lft -> lfFaceName);

	switch (font_Imp -> lft -> lfPitchAndFamily & FF_FAMILYMASK) {
	case FF_DECORATIVE:	pNewVI -> Style() = Decorative; break;
	case FF_MODERN:		pNewVI -> Style() = Modern; break;
	case FF_ROMAN:		pNewVI -> Style() = Roman; break;
	case FF_SCRIPT:		pNewVI -> Style() = Script; break;
	case FF_SWISS:		pNewVI -> Style() = Swiss; break;
	case FF_DONTCARE:
	default: 
		break;
	}

// alle Fonts richtig drehen, Zeichen mittendurch schneiden
	font_Imp -> lft -> lfClipPrecision = CLIP_STROKE_PRECIS | CLIP_LH_ANGLES;

// alteMode für Hintergrund und Rahmen erhalten
	if (ChFntEx.cfeBKMode)
		pNewVI -> Type() |= TV_BKMode;
	else
		pNewVI -> Type() &= ~TV_BKMode;

	if (ChFntEx.cfeFrameMode)
		pNewVI -> Type() |= TV_Frame;
	else
		pNewVI -> Type() &= ~TV_Frame;

	if (ChFntEx.cfeRoundFrame)
		pNewVI -> Type() |= TV_RoundFrame;
	else
		pNewVI -> Type() &= ~TV_RoundFrame;
	
	pNewVI -> Type() &= ~TV_AlignStyle;
	if (ChFntEx.cfeCentredText)
		pNewVI -> Type() |= TV_CentreAlign;
	else if (ChFntEx.cfeRightText)
		pNewVI -> Type() |= TV_RightAlign;
	else if (ChFntEx.cfeJustified)
		pNewVI -> Type() |= TV_Justified;
	
	font_Imp -> FntChanged = 1;	// FontParameter geändert
	
// neue VI liefern
	delete *ppTVI;
	*ppTVI = pNewVI;

return true;
}

// Generieren eines Fonts entsprechend der Einstellungen in pTVI --------------
pFont MakeFont (TVisInfo *pTVI, Dimension Size) 
{
pFont pF = NULL;

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	TX_TRY(pF = new CVFont ((StdFamily)pTVI -> Style(), Size, pTVI -> TName()));
#else
	TX_TRY(pF = new Font ((StdFamily)pTVI -> Style(), Size, pTVI -> TName()));
#endif //!defined(_TRIAS_OLDIMPLEMENTATION2)
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

