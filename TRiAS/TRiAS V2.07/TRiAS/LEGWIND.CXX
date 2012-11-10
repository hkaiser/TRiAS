// Fenster in welchem Legende gezeichnet werden kann --------------------------
// File: LEGWIND.CXX

#include "triaspre.hxx"

#include <dirisole.h>

#if defined(WIN32)
#include "extmain3.hxx"
#endif

#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#include "legtxted.hxx"
#include "ldroptgt.hxx"
#include "ldropsrc.hxx"

#include "triasres.h"
#include "strings.h"

// #define _DUMP

extern bool LegendeCFlag;
extern HPALETTE hPalette;
extern HINSTANCE hInstance;

Dimension GetDotsPerMM (HDC hDC = NULL);

#define WM_SHOWLEGENDMENU	WM_USER+2000

// LegendeFenster -------------------------------------------------------------
CLegendeWindow *CLegendeWindow :: CreateInstance (pWindow pParent, char *pCaption, 
				  DatenBasisObjekt &rDBO) 
{
CEierUhr Wait (pParent);
CLegendeWindow *pLeg = new CLegendeWindow (pParent, pCaption, rDBO);

	if (pLeg == NULL || !pLeg -> FInit()) {
		DELETE (pLeg);
		return NULL;
	}
	
return pLeg;
}

CLegendeWindow :: CLegendeWindow (pWindow pParent, char *pCaption, 
				  DatenBasisObjekt &rDBO) 
	        : DialogWindow (pParent, ResID (LEGENDEDLG), false),
	 	  m_rDBO (rDBO),
		  m_LMenu (LEGENDEMENU),
		  m_Dim (0, 0)
{
// Mode initialisieren
	m_fFitFont = true;			// Default: Font anpassen
	m_fSetScrollBars = false;	// HilfsFlag
	m_fPainting = false;		// Semaphore für Zeichnen
	m_fShowMenu = false;
	m_fSelRect = false;
	m_fPendingReSel = false;
	m_fNeedsCalculation = true;
			
	m_pVertSB = NULL;
	m_pHorzSB = NULL;
	m_pLO = NULL;
	m_hMenu = NULL;
	m_iActSelection = 0;		// damit ResetSelection() funktioniert
				
	m_fBrushToDelete = false;
	m_fIsDropSource = false;	
	m_pDropTgt = NULL;
	m_iDropPos = -1;
	m_iDropOrder = USHRT_MAX;
	m_iClipOrder = USHRT_MAX;
	m_uiScrollInset = g_dwScrollInset;
	m_uiScrollDelay = g_dwScrollDelay;
	m_uiHorzScrollCode = USHRT_MAX;
	m_uiVertScrollCode = USHRT_MAX;
	m_uiLastTest = UDROP_NONE;
	m_dwTimeLast = 0L;
		
	m_hWnd = Handle (API_WINDOW_HWND);

#if defined(WIN32)
	m_hAccel = NULL;
#endif // WIN32

// Überschrift setzen
	SetCaption (pCaption);
	ChangeMenu (&m_LMenu);
	
// Kontextmenu im Hauptmenu passivieren
	ResetSelection();

// Menupunkte eines Fensters mit SysMenu entfernen
HMENU hSysMenu = ::GetSystemMenu (m_hWnd, false);

	::RemoveMenu (hSysMenu, SC_MINIMIZE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_RESTORE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

bool CLegendeWindow :: FInit (void)
{
// DragDrop-initialisierungen
	m_cf = RegisterClipboardFormat (ResString (IDS_LEGENDCLIPBOARDFMT, 30));

	m_hBr = CreateInvBrush();
	if (m_hBr == NULL) {
		m_hBr = (HBRUSH)GetStockObject (GRAY_BRUSH);
		m_fBrushToDelete = false;
	} else
		m_fBrushToDelete = true;
	
// anlegen und registrieren des DropTargets
	m_pDropTgt = new CLegWindDropTarget (this);
	if (m_pDropTgt != NULL)	{
		m_pDropTgt -> AddRef();
		CoLockObjectExternal ((LPUNKNOWN)m_pDropTgt, true, false);
		RegisterDragDrop (m_hWnd, (LPDROPTARGET)m_pDropTgt);
	}
		
// Größe und Lage Voreinstellen
Rectangle rcC = GetParent() -> CanvasRect();
short iWidth = ((rcC.Right()-rcC.Left())*5)/16;
Point ptOrg (rcC.Right()-iWidth, 0);
// Rectangle rcL (rcC.Top()-rcC.Bottom(), rcC.Right()-iWidth, 0, rcC.Right());

// LegendeFenster maximal so hoch machen, wie Client vom Hauptfenster
	ChangeSize (Dimension (iWidth, rcC.Top()-rcC.Bottom()));
	ChangePosition (ptOrg);

Rectangle rcL = CanvasRect();

	m_pLO = CLegendeObjekt :: CreateInstance (this, m_rDBO);
	if (m_pLO == NULL) return false;		// Fehler

bool fFitWidth = true;	

	if (m_fFitFont) 
		m_Dim = m_pLO -> FitLegendSize (&rcL);	// Größe mit Anpassen
	else
		m_Dim = m_pLO -> GetRealSize (&rcL, fFitWidth);	// Größe ohne Anpassen
	m_fNeedsCalculation = false;

// Fenster positionieren
	ptOrg.Y() = ((rcC.Top()-rcC.Bottom()) - ptOrg.Y());
	
Rectangle rcT = Rectangle (ptOrg, Dimension (m_Dim.Width(), -m_Dim.Height()));

#if defined(WIN32)
	AdjustWindowRectEx ((RECT *)&rcT, WS_CHILD|WS_CAPTION|WS_THICKFRAME, true, IsWin40() ? WS_EX_TOOLWINDOW : 0);
	m_hAccel = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_LEGMENUACCEL));
	if (NULL == m_hAccel) return false;
#else
	AdjustWindowRect ((RECT *)&rcT, WS_CHILD|WS_CAPTION|WS_THICKFRAME, true);
#endif // WIN32

	ChangeSize (Dimension (rcT.Right()-rcT.Left(), rcT.Bottom()-rcT.Top()));
	ChangePosition (Point (rcT.Left(), 0));
	
return true;
}


// Legende neu zeichnen (entsprechend aktueller Sicht) ------------------------
void CLegendeWindow :: Expose (ExposeEvt e) 
{
	if (m_pLO == NULL) return;

	if (!m_fPainting) {
	CEierUhr Wait (this);
	
		m_fPainting = true;
	
	Rectangle rcL = CanvasRect();
	Rectangle rcEA = e.GetExposedArea();
	bool fFitWidth = true;
	
	// das Rechteck muß auch gekippt werden, da das Dialogfenster ein auf dem Kopf
	// stehendes Koordinatensystem hat
	CoOrd dY = rcL.Top() - rcL.Bottom();
	
		rcEA.Top() = dY - rcEA.Top();
		rcEA.Bottom() = dY - rcEA.Bottom();
		CanvasErase (rcEA);	// Hintergrund löschen muß explizit gemacht werden
		
		if (m_fNeedsCalculation) {
			if (m_fFitFont) 
				m_Dim = m_pLO -> FitLegendSize (&rcL);	// Größe mit Anpassen
			else	
				m_Dim = m_pLO -> GetRealSize (&rcL, fFitWidth);	// Größe ohne Anpassen
			m_fNeedsCalculation = false;
		}
			
		if (m_fSetScrollBars) {
			SetScrollRanges();
			m_fSetScrollBars = false;
		}
		DrawEx (m_pLO, (DWORD)&rcEA);	// gesamte aktuelle Legende zeichnen

		ShowSelection (m_iActSelection, true);	// SelRect einblenden
		DrawDropSelection (rcL);	// DropSelection neu zeichnen
		m_fPainting = false;
	}
	DialogWindow :: Expose (e);
}

#if defined(WIN32)
BOOL CLegendeWindow::PreTranslateMsg (MSG *pMsg)		// Accels bearbeiten
{
	if (m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		return true;
	return DialogWindow::PreTranslateMsg(pMsg);		// nicht für uns
}
#endif

// Legende neu generieren bei Sichtwechsel etc. -------------------------------
bool CLegendeWindow :: RefreshLegend (void)
{ 
CEierUhr Wait (this);

	m_fNeedsCalculation = true;
	return m_pLO -> RefreshLegend(); 
}


CLegendeWindow :: ~CLegendeWindow (void) 
{
CEierUhr Wait (this);

	SaveLegend();		// evtl. wegschreiben
	DELETE (m_pLO);
	
	if (m_fBrushToDelete)
		DeleteObject (m_hBr);

// DropTarget abmelden, wenn's noch nicht passiert ist
	if (m_pDropTgt) {
		RevokeDragDrop (m_hWnd);
		CoLockObjectExternal ((LPUNKNOWN)m_pDropTgt, false, true);
		m_pDropTgt -> Release();
		m_pDropTgt = NULL;
	}
}


BOOL CLegendeWindow :: QueryClose (Event) 
{
// Legende speichern, wenn notwendig
CEierUhr Wait (this);

	SaveLegend();

// Legende ausblenden
	if (LegendeCFlag) {
	// wenn über Systemmenu geschlossen, dann MenuPunkt simulieren
		PostMessage (GetParent() -> Handle (API_WINDOW_HWND), WM_COMMAND,
			     IDM_LEGENDE, 0);	
	}

// DropTarget abmelden
	if (m_pDropTgt) {
		RevokeDragDrop (m_hWnd);
		CoLockObjectExternal ((LPUNKNOWN)m_pDropTgt, false, true);
		m_pDropTgt -> Release();
		m_pDropTgt = NULL;
	}
		
return true;	// auf jeden Fall raus
}


// MenuPunkte angeklickt ------------------------------------------------------
void CLegendeWindow :: MenuCommand (MenuCommandEvt e)
{
	switch (e.GetItemID()) {
	case IDM_FITLEGENDENTRIES:
		m_fFitFont = !m_fFitFont;
		if (!m_fFitFont)
			m_fSetScrollBars = true;	// beim nächsten zeichnen Scrolls setzen
		else {
		// Scrollbalken ausblenden
			m_pHorzSB = EnableHScroll (false);
			m_pVertSB = EnableVScroll (false);
			if (m_pLO) {
				m_pLO -> m_ptOrg.X() = 0;
				m_pLO -> m_ptOrg.Y() = 0;
			}
		}
		m_fNeedsCalculation = true;
		HideSelection (m_iActSelection);	// SelRect ausblenden
		RePaint();
		break;

	case IDM_SIZESLIKESCALING:
		m_pLO -> SetScaleMode (!m_pLO -> GetScaleMode());
		m_pLO -> SetDirty();

		m_fNeedsCalculation = true;
		HideSelection(m_iActSelection);	// SelRect ausblenden
		RePaint();
		break;

	case IDM_LEGENDSELFONT:
		break;
		
	case IDM_SHOWALLENTRIES:
		m_pLO -> ShowAll (!m_pLO -> ShowAll());
		m_fNeedsCalculation = true;
		HideSelection (m_iActSelection);	// SelRect ausblenden
		RePaint();
		break;
		
	case IDM_LEGENDRESET:				// Legende rücksetzen
		{
		CEierUhr Wait (this);
		char *pView = new char [_MAX_PATH];
		
			if (pView == NULL) break;	// Fehler
			if (DEX_GetActiveSight(pView) != NULL) {
				m_pLO -> ResetLegend (pView);
				m_fNeedsCalculation = true;
				ResetSelection();
				RePaint();
			}
			DELETE (pView);
		}
		break;
		
	case IDM_LEGENDSAVE:
		SaveLegend();	// Legende speichern, wenn notwendig
		break;
	
	// PopupMenu 
	case IDM_LEGENTRYSHOWENTRY:
		if (m_iActSelection >= 0) {
		bool fShown = m_pLO -> isShown (m_iActSelection);
		
			m_pLO -> isShown (m_iActSelection, !fShown);
			m_fNeedsCalculation = true;
			HideSelection (m_iActSelection);
			ResetSelection();	// Paint überschreibt SelRect
			RePaint();
		}
		break;
		
	case IDM_LEGENTRYREMOVEENTRY:		// nur für Objekteinträge
		if (m_iActSelection >= 0) {
			m_pLO -> RemoveEntry (m_iActSelection);
			m_fNeedsCalculation = true;
			HideSelection (m_iActSelection); // Selektion freigeben
			ResetSelection();		
			RePaint();			 // neu zeichnen
		}		
		break;
		
	case IDM_LEGENTRYVISPARAMS:
		HandleVisParams();
		break;
		
	case IDM_LEGENTRYEDITTEXT:
		HandleEditText();
		break;
		
	case IDM_LEGENTRYRESETTEXT:
		if (m_pLO -> ResetText (m_iActSelection)) {
			m_fNeedsCalculation = true;
			RePaint();
		}
		break;

	case IDM_LEGENTRYMOVEUP:		// eine Etage hoch
		if (m_pLO -> MoveUp (m_iActSelection, m_fShowAllEntries)) {
			m_fNeedsCalculation = true;
			RePaint();
		}
		break;
		
	case IDM_LEGENTRYMOVEDOWN:
		if (m_pLO -> MoveDown (m_iActSelection, m_fShowAllEntries)) {
			m_fNeedsCalculation = true;
			RePaint();
		}
		break;

	case IDM_ENTERSPACELINE:
		if (m_pLO -> EnterSpace (m_iActSelection)) {
			m_fNeedsCalculation = true;
			RePaint();
		}
		break;
		
	case IDM_REMOVESPACELINE:
		if (m_pLO -> RemoveSpace (m_iActSelection)) {
			m_fNeedsCalculation = true;
			RePaint();
		}
		break;

	case IDM_LEGENDE_ANAUSSCHNITTANPASSEN:
		m_pLO -> SetAreaOnly (!m_pLO -> ShowAreaOnly());
		m_pLO -> SetDirty();

		m_fNeedsCalculation = true;
		RePaint();
		break;
	}
}


// MenuHandler ----------------------------------------------------------------
void CLegendeWindow :: HandleVisParams (void)
{
	switch (m_pLO -> isA (m_iActSelection)) {
	case LEGENTRYTYPE_IDENT:
		{
		long lIdent = m_pLO -> GetIdent (m_iActSelection);
		VisType iVTyp = m_pLO -> GetVType (m_iActSelection);
				
			if (DefineNewIdentVisInfo (lIdent, iVTyp, GetKeyState (VK_CONTROL) < 0)) {
				m_fNeedsCalculation = true;
				DEX_RePaintWait();	// Hauptfenster neu zeichnen
			}
		} 
		break;
				
	case LEGENTRYTYPE_OBJECT:
		break;
		
	case LEGENTRYTYPE_UNKNOWN:
	default:
		break;
	}			
}


void CLegendeWindow :: HandleEditText (void)
{
	switch (m_pLO -> isA (m_iActSelection)) {
	case LEGENTRYTYPE_OBJECT:
	case LEGENTRYTYPE_IDENT:
		{
		char *pText = m_pLO -> GetText (m_iActSelection);
		CEditLegTextDlg *pDlg = CEditLegTextDlg :: CreateInstance (this, pText);
		
			if (pDlg != NULL) {
				pDlg -> Show();
				if (pDlg -> Result()) {
					m_pLO -> SetText (m_iActSelection, pDlg -> GetNewText());
					m_fNeedsCalculation = true;
					RePaint();
				}
			}
			DELETE (pText);
			DELETE (pDlg);
		}
		break;
				
	case LEGENTRYTYPE_UNKNOWN:
	default:
		break;
	}			
}


// MenuInitialisierungen ------------------------------------------------------
void MenuCheck (pMenu pM, int MenuItem, bool Flag);
void MenuEnable (pMenu pM, int MenuItem, bool Flag);

void CLegendeWindow :: MenuInit (MenuInitEvt)
{
// Hauptmenu initialisieren
	MenuCheck (&m_LMenu, IDM_FITLEGENDENTRIES, m_fFitFont);
	MenuCheck (&m_LMenu, IDM_SHOWALLENTRIES, m_pLO -> ShowAll());
	MenuCheck (&m_LMenu, IDM_LEGENDE_ANAUSSCHNITTANPASSEN, m_pLO -> ShowAreaOnly());
	MenuCheck (&m_LMenu, IDM_SIZESLIKESCALING, !m_pLO -> GetScaleMode());

HMENU hMenu = GetSubMenu (m_LMenu.Handle(API_MENU_HMENU), 0);
	
// Ein Trick am Rande, der erlaubt die Legende on the fly zu speichern.
// (mit der ControlTaste das erste SubMenu der Legende öffnen :-) )

	if (GetKeyState (VK_CONTROL) < 0) {	// ControlTaste gedrückt
		ModifyMenu (hMenu, 7,	// letzter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, 
			    IDM_LEGENDSAVE, 
			    ResString (IDS_LEGENDSAVE, 64).Addr());
	} else {	// Normaler Mode
		ModifyMenu (hMenu, 7,	// letzter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, 
			    IDM_LEGENDRESET, 
			    ResString (IDS_LEGENDRESET, 64).Addr());
	}
	
//	MenuEnable (&m_LMenu, IDM_LEGENDRESET, m_pLO -> isDirty());
//	MenuEnable (&m_LMenu, IDM_LEGENDSELFONT, !m_fFitFont);

	if (m_iActSelection == USHRT_MAX) return;
	
// KontextMenu im Hauptmenu initialisieren
bool fShown = m_pLO -> isShown (m_iActSelection);
bool fSpace = m_pLO -> hasSpace (m_iActSelection);
bool fIdentEntry = m_pLO -> isA (m_iActSelection) == LEGENTRYTYPE_IDENT;
bool fCustText = m_pLO -> CustomizedText (m_iActSelection);
bool fNotFirst = !m_pLO -> isFirstEntry (m_iActSelection);
bool fNotLast = !m_pLO -> isLastEntry (m_iActSelection);

	hMenu = GetSubMenu (m_LMenu.Handle(API_MENU_HMENU), 1);
// Identifikator/ObjektEintrag
	if (fIdentEntry) {	// IdentifikatorEintrag
		ModifyMenu (hMenu, 0,	// erster Eintrag
			    MF_BYPOSITION | (fShown ? MF_CHECKED : MF_UNCHECKED), 
			    IDM_LEGENTRYSHOWENTRY, 
			    ResString (IDS_LEGENTRYSHOW, 64).Addr());
	} else {		// ObjektEintrag
		ModifyMenu (hMenu, 0,	// erster Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, IDM_LEGENTRYREMOVEENTRY, 
			    ResString (IDS_LEGENTRYREMOVE, 64).Addr());
	}
// Leerzeile vorhanden/nicht vorhanden
	if (fSpace) {	// Leerzeile vorhanden
		ModifyMenu (hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, IDM_REMOVESPACELINE, 
			    ResString (IDS_REMOVESPACELINE, 64).Addr());
	} else {		// ObjektEintrag
		ModifyMenu (hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED|(fNotLast ? MF_ENABLED : MF_GRAYED), 
			    IDM_ENTERSPACELINE, 
			    ResString (IDS_ENTERSPACELINE, 64).Addr());
	}
	
	MenuEnable (&m_LMenu, IDM_LEGENTRYVISPARAMS, fIdentEntry);
	MenuEnable (&m_LMenu, IDM_LEGENTRYRESETTEXT, fCustText);

	MenuEnable (&m_LMenu, IDM_LEGENTRYMOVEUP, fNotFirst);
	MenuEnable (&m_LMenu, IDM_LEGENTRYMOVEDOWN, fNotLast);

	if (m_hMenu == 0) return;	// kein Kontextmenu offen

// KontextMenu initialisieren
// Identifikator/Objekteintrag
	if (fIdentEntry) {	// IdentifikatorEintrag
		ModifyMenu (m_hMenu, 0,	// erster Eintrag
			    MF_BYPOSITION | (fShown ? MF_CHECKED : MF_UNCHECKED), 
			    IDM_LEGENTRYSHOWENTRY, 
			    ResString (IDS_LEGENTRYSHOWENTRY, 64).Addr());
	} else {		// ObjektEintrag
		ModifyMenu (m_hMenu, 0,	// erster Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, IDM_LEGENTRYREMOVEENTRY, 
			    ResString (IDS_LEGENTRYREMOVEENTRY, 64).Addr());
	}
// Leerzeile vorhanden/nicht vorhanden
	if (fSpace) {	// Leerzeile vorhanden
		ModifyMenu (m_hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, IDM_REMOVESPACELINE, 
			    ResString (IDS_REMOVESPACELINE, 64).Addr());
	} else {		// ObjektEintrag
		ModifyMenu (m_hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED|(fNotLast ? MF_ENABLED : MF_GRAYED), 
			    IDM_ENTERSPACELINE, 
			    ResString (IDS_ENTERSPACELINE, 64).Addr());
	}

	EnableMenuItem (m_hMenu, IDM_LEGENTRYVISPARAMS, 
			MF_BYCOMMAND | (fIdentEntry ? MF_ENABLED : MF_GRAYED));	
	EnableMenuItem (m_hMenu, IDM_LEGENTRYRESETTEXT, 
			MF_BYCOMMAND| (fCustText ? MF_ENABLED : MF_GRAYED));	
	EnableMenuItem (m_hMenu, IDM_LEGENTRYMOVEUP, 
			MF_BYCOMMAND| (fNotFirst ? MF_ENABLED : MF_GRAYED));	
	EnableMenuItem (m_hMenu, IDM_LEGENTRYMOVEDOWN, 
			MF_BYCOMMAND| (fNotLast ? MF_ENABLED : MF_GRAYED));	
}

void CLegendeWindow :: ReSize (ReSizeEvt) 
{	// ScrollBereich neu setzen
	if (!m_fFitFont)
		SetScrollRanges ();

	m_fNeedsCalculation = true;			// Font neu berechnen
	HideSelection (m_iActSelection);	// SelRect ausblenden
	RePaint();	// neu zeichnen
}

void CLegendeWindow :: HorizScroll (ScrollEvt e) 
{
	if (m_pHorzSB == NULL) return;		// kein ScrollBalken da
	
Range HorzR;
short iPos, dn;
Rectangle rcT;

// neue vertikale Rollposition berechnen
	HorzR = m_pHorzSB -> GetRange();
	iPos = e.GetOldPos();
	rcT = CanvasRect();
	switch (e.GetScrollType()) {
	case UnitDecrement:	dn = -rcT.Right() / 16 + 1; break;
	case UnitIncrement:	dn =  rcT.Right() / 16 - 1; break;
	case BlockDecrement:	dn = -rcT.Right() / 2 + 1; break;
	case BlockIncrement:	dn =  rcT.Right() / 2 - 1; break;
	case ThumbDrag:		dn =  e.GetPos() - iPos; break;
	default:		dn =  0; break;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	if ((dn = BOUND (iPos + dn, HorzR.Min(), HorzR.Max()) - iPos) != 0) {
		HideSelection (m_iActSelection);
		Scroll (Dimension (-dn, 0), rcT);
		m_pHorzSB -> SetThumbPos (iPos + dn);
		if (m_pLO) m_pLO -> m_ptOrg.X() = iPos + dn;
	}
}


void CLegendeWindow :: VertScroll (ScrollEvt e) 
{
	if (m_pVertSB == NULL) return;		// kein ScrollBalken da

Range VertR;
short iPos, dn;
Rectangle rcT;

// neue vertikale Rollposition berechnen
	VertR = m_pVertSB -> GetRange();
	iPos = e.GetOldPos();
	rcT = CanvasRect();
	switch (e.GetScrollType()) {
	case UnitDecrement:	dn = -rcT.Top() / 16 + 1; break;
	case UnitIncrement:	dn =  rcT.Top() / 16 - 1; break;
	case BlockDecrement:	dn = -rcT.Top() / 2 + 1; break;
	case BlockIncrement:	dn =  rcT.Top() / 2 - 1; break;
	case ThumbDrag:		dn =  e.GetPos() - iPos; break;
	default:		dn =  0; break;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	if ((dn = BOUND (iPos + dn, VertR.Min(), VertR.Max()) - iPos) != 0) {
		HideSelection (m_iActSelection);
		Scroll (Dimension (0, dn), rcT);
		m_pVertSB -> SetThumbPos (iPos + dn);
		if (m_pLO) m_pLO -> m_ptOrg.Y() = -(iPos + dn);

#if defined(_DUMP)
char cbBuffer[256];

	wsprintf (cbBuffer, "VertScroll: %d\r\n", m_pLO -> m_ptOrg.Y());
	OutputDebugString (cbBuffer);
#endif // _DUMP
	
	}
}

// ScrollBereiche neu setzen --------------------------------------------------
void CLegendeWindow :: SetScrollRanges (void) 
{
Rectangle rcT;
static int iScrollSem = 0;
CoOrd iRangeH, iRangeV, i;

	if (!iScrollSem) {
		iScrollSem++;
		rcT = RealCanvasRect();
		for (i = 0; i < 2; i++) {
			iRangeV = m_Dim.Height() - (rcT.Top()-rcT.Bottom());
			iRangeH = m_Dim.Width() - rcT.Right();
			if (iRangeH < 0) iRangeH = 0;
			if (iRangeV < 0) iRangeV = 0;

		// etwas neuzeichnen ?
		int yThumbPos = m_pVertSB != NULL ? m_pVertSB -> GetThumbPos() : 0;
		int xThumbPos = m_pHorzSB != NULL ? m_pHorzSB -> GetThumbPos() : 0;

			if ((iRangeV && yThumbPos >= iRangeV) || 
			    (iRangeH && xThumbPos >= iRangeH)) 
			{
				HideSelection (m_iActSelection);	// SelRect ausblenden
				RePaint();
			}

		// ScrollBalken anzeigen bzw. löschen
			if (iRangeV > 0) {
				m_pVertSB = EnableVScroll (true);
				m_pVertSB -> SetRange (Range (0, iRangeV));
			} else {
				if (m_pVertSB) m_pVertSB -> SetRange (Range (0, 0));
				m_pVertSB = EnableVScroll (false);
				if (m_pLO) m_pLO -> m_ptOrg.Y() = 0;
			}
			if (iRangeH > 0) {
				m_pHorzSB = EnableHScroll (true);
				m_pHorzSB -> SetRange (Range (0, iRangeH));
			} else {
				if (m_pHorzSB) m_pHorzSB -> SetRange (Range (0, 0));
				m_pHorzSB = EnableHScroll (false);
				if (m_pLO) m_pLO -> m_ptOrg.X() = 0;
			}

		// zweite Runde
			rcT = CanvasRect();
		}
		iScrollSem--;
	}
}

// Berechnung der ClientFlaeche unter Beruecksichtigung der Rollbalken
Rectangle CLegendeWindow :: RealCanvasRect (void) 
{
long dwStyle = GetWindowLong (Handle (API_CLIENT_HWND), GWL_STYLE);
							// FensterStil
Rectangle rcT = CanvasRect();

	if (dwStyle & WS_HSCROLL)
		rcT.Bottom() += GetSystemMetrics (SM_CYHSCROLL);
	if (dwStyle & WS_VSCROLL)
		rcT.Right() -= GetSystemMetrics (SM_CXVSCROLL);

return rcT;
}

// MouseEvents auswerten ------------------------------------------------------
void CLegendeWindow :: MouseButtonDn (MouseEvt e)
{
	if (m_pLO == NULL || m_hMenu) 
		return;		// Fehler, oder Menu offen: nichts tun
	
Point pt = e.Where();
WORD iOrder = FindEntry (pt);	// passenden Einrag finden

	if (iOrder == USHRT_MAX) return;
	if (e.isRightButton()) {
	// Rechteck zeichnen
		if (ShowSelection (iOrder)) {
		// Menu anzeigen
			pt.Y() += m_pLO -> m_ptOrg.Y();		// korrigieren
			PostMessage (m_hWnd, WM_SHOWLEGENDMENU, 
				     iOrder, MAKELONG (pt.X(), pt.Y()));
		} else 
			ResetSelection();	// nichts aktiv

	} else if (e.isLeftButton()) {
		if (iOrder == m_iActSelection) 
		// erst beim MouseButtonUp Selektion löschen
			m_fPendingReSel = true;
		else
			ShowSelection (iOrder);		// neue Selektion setzen
	}
}

void CLegendeWindow :: MouseButtonUp (MouseEvt e)
{
Point pt = e.Where();
WORD iOrder = FindEntry (pt);	// passenden Einrag finden

	if (e.isLeftButton() && m_fPendingReSel) {
	// alte Selektion muß evtl. gelöscht werden
		if (iOrder == m_iActSelection) {
			HideSelection (iOrder);		// Selektion freigeben
			ResetSelection();
		} else
			ShowSelection (iOrder);
		m_fPendingReSel = false;
	}
}

void CLegendeWindow :: MouseDrag (MouseEvt e)
{
	if (!e.isLeftButton()) return;		// Drag beginnt mit linker Taste
	
Point pt = e.Where();

	m_iClipOrder = FindEntry (pt);		// passenden Einrag finden
	if (m_iClipOrder == USHRT_MAX || m_iClipOrder != m_iActSelection)
		return;

// zu bewegende Daten erzeugen
LPDATAOBJECT pIDataObject = TransferObjectCreate (m_iClipOrder);
SCODE sc = E_FAIL;
DWORD dwEffect;

	if (pIDataObject != NULL) {
	// DropSource generieren
	CLegWindDropSource *pIDropSrc = NULL;
	
		TX_TRY(pIDropSrc = new CLegWindDropSource (this));
		if (pIDropSrc == NULL) {
			m_iClipOrder = USHRT_MAX;
			return;		// kein Drop möglich
		}
		pIDropSrc -> AddRef();
		m_fIsDropSource = true;
		
	HRESULT hr = DoDragDrop (pIDataObject, pIDropSrc, 
				 DROPEFFECT_MOVE|DROPEFFECT_COPY, &dwEffect);

		m_fIsDropSource = false;	
		pIDropSrc -> Release();		// DropSource freigeben
		pIDataObject -> Release();	// Daten freigeben

		sc = GetScode (hr);		// Resultat der Aktion merken
	}

	if (sc == DRAGDROP_S_DROP) {
		if (dwEffect == DROPEFFECT_MOVE) 
			FClipEntry (m_iClipOrder);	// alten Eintrag rausnehmen
		RePaint();
	}
	m_iClipOrder = USHRT_MAX;
}

void CLegendeWindow :: MouseButtonDblClk (MouseEvt) 
{
}

#if 0 // ======================================================================
void CLegendeWindow :: KeyDown (KeyEvt e) 
{ 
// wenn nichts selektiert ist, dann weiter
	if (m_iActSelection == USHRT_MAX) return;
	
// selektiertes Item verschieben
	if (e.ASCIIChar() == '\0') {
		switch (e.Keycode()) {
		case VK_UP:
			if (!m_pLO -> isFirstEntry (m_iActSelection))
				PostMessage (m_hWnd, WM_COMMAND, IDM_LEGENTRYMOVEUP, 0L);
			return;

		case VK_DOWN:
			if (!m_pLO -> isLastEntry (m_iActSelection))
				PostMessage (m_hWnd, WM_COMMAND, IDM_LEGENTRYMOVEDOWN, 0L);
			return;
		}
	}
}
#endif // =====================================================================

LRESULT EXPORTTRIAS CLegendeWindow :: Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_SHOWLEGENDMENU:
		if (!m_fShowMenu) {
			m_fShowMenu = true;
			ShowMenu (LOWORD(e.LParam()), HIWORD(e.LParam()));
			m_fShowMenu = false;
		}
		return true;

	case WM_ERASEBKGND:
		return true;
		
	default:
		break;
	}

return DialogWindow :: Dispatch (e);
}


// Kontextmenu anzeigen -------------------------------------------------------
void CLegendeWindow :: ShowMenu (short X, short Y)
{
// Menu generieren und anzeigen
Menu menuLeg (LEGENDEDROPDOWNMENU);
Point Pt (X, Y);

	m_hMenu = GetSubMenu (menuLeg.Handle(API_MENU_HMENU), 0);	// SubMenu holen
	ClientToScreen (Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
	if (!TrackPopupMenu (m_hMenu, 0, Pt.X(), Pt.Y(), 0, 
			     Handle (API_CLIENT_HWND), NULL)) 
	{	// Fehler 
		HideSelection (m_iActSelection);
		ResetSelection();
	}
	m_hMenu = 0;
}


// SelectionsRechteck ausblenden/anzeigen -------------------------------------
bool CLegendeWindow :: HideSelection (WORD iOrder)
{
	if (m_pLO == NULL || !m_fSelRect || iOrder == USHRT_MAX) 
		return false;

Rectangle rc = CanvasRect();
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
Range r;

	if (m_pLO -> GetEntrySize (iOrder, r)) {
		rc.Top() = r.Min() + iScrPos;
		rc.Bottom() = r.Max() + iScrPos;
		PaintSelection (rc);
		m_fSelRect = false;
		return true;
	}
	
return false;
}			

// Selektiert einen Eintrag, wenn ein anderer Selektiert war, dann wird dieser
// vorher deselektiert, Ist der Eintrag selbst bereits selektiert, passiert
// garnichts
bool CLegendeWindow :: ShowSelection (WORD iOrder, bool fForce)
{
	if (m_pLO == NULL || iOrder == USHRT_MAX) return false;

	if (m_fSelRect && !fForce) {
		if (m_iActSelection == iOrder) 
			return true;
		HideSelection (m_iActSelection);	// anderes deselektieren
	}
				
Rectangle rc = CanvasRect();
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
Range r;

	if (m_pLO -> GetEntrySize (iOrder, r)) {
		rc.Top() = r.Min() + iScrPos;
		rc.Bottom() = r.Max() + iScrPos;
		m_iActSelection = iOrder;
		PaintSelection (rc);
		EnableMenuItem (m_LMenu.Handle(), 1, MF_BYPOSITION | MF_ENABLED);
		DrawMenuBar (m_hWnd);
		m_fSelRect = true;
		return true;
	}
	
return false;
}			

// Rechteck zeichnen ----------------------------------------------------------
#define DD		2	// Dicke der SelektionsLinie [Pixel]

void CLegendeWindow :: PaintSelection (Rectangle &rRc)
{
HDC hDC = GetDC (m_hWnd);

// Rechteck zeichnen
	PatBlt (hDC, rRc.Left(), rRc.Top()-DD, 
		     rRc.Right()-rRc.Left(), DD, DSTINVERT);		// Top
	PatBlt (hDC, rRc.Left(), rRc.Bottom()-DD, 
		     rRc.Right()-rRc.Left(), DD, DSTINVERT);		// Bottom
	PatBlt (hDC, rRc.Left(), rRc.Top(), 
		     DD, rRc.Bottom()-rRc.Top()-DD, DSTINVERT);	// Left
	PatBlt (hDC, rRc.Right()-DD, rRc.Top(), 
		     DD, rRc.Bottom()-rRc.Top()-DD, DSTINVERT);	// Right

	ReleaseDC (m_hWnd, hDC);
}

// einen Eintrag anhand einer MausKoordinate finden ---------------------------
// kippt außerdem y-Koordinate im Punkt
WORD CLegendeWindow :: FindEntry (Point &pt)
{
Rectangle rc = CanvasRect();
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
	
	pt.Y() = (rc.Top()-rc.Bottom()) - pt.Y();	// Y kippen
	pt.Y() -= iScrPos;			// ScrollPos beachten
	
return m_pLO -> FindEntry (short(pt.Y()));
}

bool CLegendeWindow :: ResetSelection (void)
{
	if (m_iActSelection == USHRT_MAX)
		return false;
	
	m_iActSelection = USHRT_MAX;
	EnableMenuItem (m_LMenu.Handle(), 1, MF_BYPOSITION | MF_GRAYED);
	DrawMenuBar (m_hWnd);

return true;
}

// Alle LegendenEinträge(Merkmale) dieser Sicht aus der DB löschen ------------
bool CLegendeWindow :: ResetLegend (void)
{
CEierUhr Wait (this);
char *pView = new char [_MAX_PATH];
bool iRet = false;
		
	if (pView == NULL) 
		return false;	// Fehler
	if (DEX_GetActiveSight(pView) != NULL) {
		iRet = m_pLO -> ResetLegend (pView);
		ResetSelection();
	}
	DELETE (pView);
	
return iRet;
}

// Zustand der Legende an der aktuellen Sicht speichern -----------------------
bool CLegendeWindow :: SaveLegend (void)
{
// Legende nur speichern, wenn notwendig
CEierUhr Wait (this);

	if (m_pLO -> isDirty())
		return m_pLO -> SaveLegend();
	return true;	// nichts zu tun
}

// Objekt zu Legende hinzufügen -----------------------------------------------
bool CLegendeWindow :: AddObject (long lONr)
{
	return m_pLO -> AddObject (lONr);
}

// Generieren des DataTransferObjektes für eine DragDropOperation -------------
LPDATAOBJECT CLegendeWindow :: TransferObjectCreate (WORD iOrder)
{
	if (iOrder == USHRT_MAX) return NULL;

LPDATAOBJECT pIDataObject = NULL;
HRESULT hr = CoCreateInstance (CLSID_DataTransferObject, NULL, 
			       CLSCTX_INPROC_SERVER, IID_IDataObject, 
			       (LPLPVOID)&pIDataObject);
	if (FAILED(hr)) return NULL;

// Copy from known obj into transfer obj.  Ordering is important!
char *pTmp = NULL;

	TX_TRY(pTmp = new char [5*_MAX_PATH]);

LEGENTRYTYPE rgLType;
VisType rgVType;
long lTarget;

	if (pTmp == NULL || 
	    !m_pLO -> GetEntryDesc (iOrder, pTmp, rgLType, rgVType, lTarget)) 
	{
		pIDataObject -> Release();
		return NULL;
	}
	
// Generate placeable object structure
STGMEDIUM stm;

	stm.tymed = TYMED_HGLOBAL;
	stm.pUnkForRelease = NULL;
	stm.hGlobal = GlobalAlloc (GHND, sizeof(DRAGDROPLEGENTRY) + strlen (pTmp));
	if (stm.hGlobal == NULL) {
		DELETE_VEC (pTmp);
		pIDataObject -> Release();
		return NULL;
	}

// Beschreibung des zu bewegenden LegendenEintrages generieren
LPDRAGDROPLEGENTRY pLegDesc = (LPDRAGDROPLEGENTRY)GlobalLock (stm.hGlobal);

	pLegDesc -> m_dwSize = sizeof(DRAGDROPLEGENTRY);
	pLegDesc -> m_rgLEType = rgLType;
	pLegDesc -> m_rgVType = rgVType;
	pLegDesc -> m_lTarget = lTarget;
	strcpy (pLegDesc -> m_cbLegDesc, pTmp);		// Daten reinkopieren
			
	DELETE_VEC (pTmp);
	GlobalUnlock(stm.hGlobal);

FORMATETC fe;

	SETDefFormatEtc (fe, m_cf, TYMED_HGLOBAL);
	pIDataObject -> SetData (&fe, &stm, true);
	
// als zweites Format den blanken LegendenText mit übergeben
	pTmp = m_pLO -> GetText (iOrder);
	
	stm.tymed = TYMED_HGLOBAL;
	stm.pUnkForRelease = NULL;
	stm.hGlobal = GlobalAlloc (GHND, strlen(pTmp) +1);
	if (stm.hGlobal == NULL) {
		DELETE_VEC (pTmp);
		pIDataObject -> Release();
		return NULL;
	}

char *pText = (char *)GlobalLock (stm.hGlobal);
	
	strcpy (pText, pTmp);		// Text reinkopieren
	DELETE_VEC (pTmp);
	GlobalUnlock(stm.hGlobal);

	SETDefFormatEtc (fe, CF_TEXT, TYMED_HGLOBAL);
	pIDataObject -> SetData (&fe, &stm, true);

return pIDataObject;    // Caller now responsible
}

// Erzeugen der Einfügemarke bei DragDrop-Operationen -------------------------
bool CLegendeWindow :: DropSelectTargetWindow (POINTL *pptl, 
					       bool fRemove, bool fPaint)
{
Rectangle rc = CanvasRect();

// nur vorherige Einfügemarke entfernen
	if (fRemove) {
		DrawDropSelection (rc);
		m_iDropPos = -1;
		m_iDropOrder = USHRT_MAX;
		return true;
	}

// neue Einfügemarke erzeugen
Point pt (CoOrd(pptl -> x), CoOrd(pptl -> y));

	ScreenToClient (m_hWnd, (POINT *)&pt);
	pt.Y() = (rc.Top()-rc.Bottom()) - pt.Y();

WORD iOrder = FindEntry (pt);

	if (iOrder == USHRT_MAX) 
		return false;	// außerhalb des gültigen Bereiches

Range r;
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
		
	if (m_pLO -> GetEntrySize (iOrder, r)) {
	// Position der Einfügemarke bestimmen
		if (pt.Y() > (r.Max()+r.Min())/2)
			pt.Y() = r.Max() + iScrPos;
		else 
			pt.Y() = r.Min() + iScrPos;

		if (pt.Y() != m_iDropPos) {
		// vorherige Einfügemarke entfernen
			if (fPaint) DrawDropSelection (rc);
			
		// Einfügemarke zeichnen
			m_iDropOrder = iOrder;
			m_iDropPos = short(pt.Y());
			if (fPaint) DrawDropSelection (rc);
		}
	}

return true;
}

bool CLegendeWindow :: DrawDropSelection (Rectangle &rRc)
{
	if (m_iDropPos < 0) return false;
	
#if defined(_DUMP)
char cbBuffer[256];

	wsprintf (cbBuffer, "DrawDropSelection: %d\r\n", m_iDropPos);
	OutputDebugString (cbBuffer);
#endif // _DUMP
	
	UnrealizeObject (m_hBr);

HDC hDC = GetDC (m_hWnd);
HBRUSH hBrush = (HBRUSH)SelectObject (hDC, m_hBr);

	PatBlt (hDC, rRc.Left()+DD, m_iDropPos-DD/2, 
		     rRc.Right()-rRc.Left()-2*DD, DD, PATINVERT);

	SelectObject (hDC, hBrush);
	ReleaseDC (m_hWnd, hDC);

return true;
}

bool CLegendeWindow :: FQueryPasteFromData (LPDATAOBJECT pIDataObject)
{
FORMATETC fe;

	SETDefFormatEtc (fe, m_cf, TYMED_HGLOBAL);
	
return (pIDataObject -> QueryGetData (&fe) == NOERROR);
}

UINT CLegendeWindow :: UTestDroppablePoint (LPPOINTL pptl)
{
POINT pt;
RECT rcC;
UINT uRet;

	POINTFROMPOINTL (pt, *pptl);
	ScreenToClient (m_hWnd, &pt);
	GetClientRect (m_hWnd, &rcC);

// Check for at least a client area hit.
	if (!PtInRect (&rcC, pt)) return UDROP_NONE;

	uRet = UDROP_CLIENT;

	if (m_fFitFont) return uRet;	// kein Scrollen notwendig
	
// Check horizontal inset
	if (pt.x <= rcC.left + (int)m_uiScrollInset)
		uRet |= UDROP_INSETLEFT;
	else if (pt.x >= rcC.right - (int)m_uiScrollInset)
		uRet |= UDROP_INSETRIGHT;

// Check vertical inset
	if (pt.y <= rcC.top + (int)m_uiScrollInset)
		uRet |= UDROP_INSETTOP;
	else if (pt.y >= rcC.bottom - (int)m_uiScrollInset)
		uRet |= UDROP_INSETBOTTOM;

return uRet;
}

bool CLegendeWindow :: FPasteFromData (LPDATAOBJECT pIDataObject)
{
// wenn keine Verschiebung resultiert, dann wieder raus
	if (!FQueryDrop()) return false;

// Eintrag einfügen
FORMATETC fe;
STGMEDIUM stm;
bool fRet;

	SETDefFormatEtc (fe, m_cf, TYMED_HGLOBAL);
	fRet = SUCCEEDED(pIDataObject -> GetData (&fe, &stm));
	if (fRet && stm.hGlobal) {
	LPDRAGDROPLEGENTRY pDDLegEntry = (LPDRAGDROPLEGENTRY)GlobalLock (stm.hGlobal);
	
		if (m_iDropOrder < m_iClipOrder)
			m_iClipOrder++;
		else if (m_iDropOrder > m_iClipOrder)
			m_iDropOrder++;

		m_pLO -> FPasteEntry (pDDLegEntry, m_iDropOrder);
		GlobalUnlock (stm.hGlobal);
		ReleaseStgMedium (&stm);

		m_fNeedsCalculation = true;
		ShowSelection (m_iDropOrder);	// neue Selektion anzeigen
	}
	
return fRet;
}

bool CLegendeWindow :: FClipEntry (WORD iOrder)
{
	return m_pLO -> FClipEntry (iOrder);
}

HBRUSH WINAPI CreateInvBrush (void)
{
HBITMAP hBM = LoadBitmap (hInstance, MAKEINTRESOURCE (IDB_INVPATTERN));

	if (hBM == NULL) return NULL;
	
HBRUSH hBr = CreatePatternBrush (hBM);

	DeleteObject (hBM);

return hBr;
}
  

