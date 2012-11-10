// IRIS - Version für Win32 -- EventVerarbeitung ------------------------------
// File: IRISEVT2.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <xtensnxx.h>
#include <rect.hxx>
#if defined(_USE_FLICKERFREE_DRAWING)
#include <MemoryDC.h>
#include <ScopeVar.h>
#include "DrawCallUpMode.h"
#endif // _USE_FLICKERFREE_DRAWING

#include <dirisole.h>
#include <TRiASMode.h>

#include "extmain3.hxx"
#include "tools.hxx"    // ToolBoxKonstanten
#if defined(OLD_COORDS)
#include "coords.hxx"
#endif // OLD_COORDS
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#include "shift.hxx"
#if defined(OLD_MASSTAB)
#include "masstab.hxx"
#endif // OLD_MASSTAB

#define NOSIGNONCODE
#include "bildobj.hxx"
#include "SignOnDlg.h"
#include "overview.hxx"
#include "selectn.hxx"
#include "extqnfy2.hxx"

#include "strings.h"

#include <funcs03.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define BOUND(x,min,max) ((x)<(min)?(min):((x)>(max)?(max):(x)))

///////////////////////////////////////////////////////////////////////////////
#if defined(OLD_TOOLBOX)
extern ToolWind *pToolBox;
#else
extern int g_iActTool;
#endif // OLD_TOOLBOX

#if defined(OLD_COORDS)
extern CoordsDlg *pCoords;
#endif // OLD_COORDS
extern COverViewClientWindow *pOverView;		// Übersichtsanzeige

extern bool Profiling;

extern short GCancelFlag;
extern bool PrintEFlag;

extern bool LegendToRepaint;
extern bool LegendeCFlag;
extern bool OverViewCFlag;
extern bool GenerateLegendOnly;	// PseudoZeichnen, um genaue Legende zu haben

extern CLegendeClientWindow *pLegende;

#if defined(OLD_MASSTAB)
extern MasstabDlg *pMasstab;
#endif // OLD_MASSTAB

extern HPALETTE hPalette;				// derzeit aktive Palette des IrisWind

extern short g_iMinutes;
extern short g_iTicks;
extern short g_iSignOnTicks;

extern bool g_fPendingSave;				// Speichern muß gemacht werden
extern bool g_fPendingReReadCaption;	// Caption muß neu gelesen werden

extern CSignOnDlg *g_pSODlg;	// SignOnDlg

///////////////////////////////////////////////////////////////////////////////
// externe Funktionsdeklarationen 
Rectangle InflateRect (Rectangle &R, short iDelta);

///////////////////////////////////////////////////////////////////////////////
// lediglich feststellen, daß wir jetzt angezeigt werden
void IrisWind::Show (ShowState s)
{
	if (HideWindow != s && !isVisible())
		m_fFirstDrawing = true;
	ChildAppWindow::Show(s);
}

///////////////////////////////////////////////////////////////////////////////
// Teile des Fensters neu zeichnen --------------------------------------------
void IrisWind::Expose (ExposeEvt e) 
{
	if (!IsValidView()/* || !Transformation::IsValid()*/) 
		return;		// noch nicht fertig initialisiert

	if (m_fPreventRepaint)
		return;		// garnicht zeichnen

	if (DBO().toPaint() != PF_INVALID) {
		if (m_iDrawSem > 0) {
		// es läuft eine Zeichenaktion
			GCancelFlag |= GCFRepaint;	// aktuelle abbrechen

		Rectangle rcEA = e.GetExposedArea();
		Rectangle rcT = DBO().EA();
				
			rcEA = rcEA + rcT;
			DBO().SetEA (rcEA);
			return;
		}

	// verhindert doppeltes Zeichnen
		if (DBO().isDrawing()) return;

	CEierUhr Wait (this, CursorPath(g_cbCursorWait));	// EierUhr anzeigen
	
		++m_iDrawSem; 
		GCancelFlag = GCFNormal;

	// Accelerator für Abbruch installieren
	Accel newAccel (CANCELACCELS);
	pAccel oldAccel = GetParent() -> ChangeAccel (&newAccel);

//		DrawMenuBar (Handle (API_WINDOW_HWND));

	// eigentliche Zeichenroutinen
#if !defined(NOGITTER)
	// evtl. Gitternetz zeichnen
		m_fRePaintFlag = false;
		if (Gitter.GitterFlag()) // Gitternetz zeichnen
			Draw ((DrawObject *)&Gitter);
#endif
	// DB neu zeichnen (Ausschnitt)
	Rectangle rcEA = e.GetExposedArea();

		InflateRect ((RECT *)&rcEA, 0, -2);
		if (rcEA.Bottom() < 0) rcEA.Bottom() = -1;
		 
//		if (rcEA.Top() > 0) rcEA.Top()--; 	// CommonVu - BugFixing
//		if (rcEA.Bottom() > 0) rcEA.Bottom()--;
		DBO().SetEA(rcEA);	// neu zu zeichnendes Rechteck
		
	// Fenster neu skalieren
		DBO().SetExtend (this, DBO().GetExtend(), AspectRatio);

	// bei Bedarf ScrollBars einblenden und initialisieren
		if (m_fFirstDrawing) {
			InitWndScrollBars();
			m_fFirstDrawing = false;
		}

	// Rahmen neu zeichnen
		SetWindowPos (Handle (API_WINDOW_HWND), NULL, 0, 0, 0, 0, 
			SWP_DRAWFRAME|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER);

#if defined(OLD_MASSTAB)
	// Maßstab neu angeben
		if (PrintEFlag && pMasstab != NULL)
			pMasstab -> SetMasstab (CanvasRect());
#else
		if (PrintEFlag)
			SetMasstab (CanvasRect());
#endif // OLD_MASSTAB

		GenerateLegendOnly = false;
		{
#if defined(_USE_FLICKERFREE_DRAWING)
		HBITMAP *phBmp = NULL;

			if (g_dwDrawingMode & DRAWMODE_StoreCanvas)
				phBmp = &m_hCanvasBmp;

		CMemoryDC MemDC (this, g_dwDrawingMode & DRAWMODE_FlickerFree, phBmp);
		CScopeVar<CMemoryDC *> Scope (m_pMemDC, &MemDC);

			if (NULL == phBmp || GetShouldRedraw() || !MemDC.IsValid()) {
				if (MemDC.IsValid())
					CanvasErase();						// evtl. Bitmap initialisieren
				DrawEx ((DrawObject *)&DBO(), 0);
			} else
				MemDC.Draw (TRUE);

#else // _USE_FLICKERFREE_DRAWING
			DrawEx ((DrawObject *)&DBO(), 0);
#endif // _USE_FLICKERFREE_DRAWING
		}

	// fertig mit Zeichnen (DEXN_... nach CMemoryDC (wegen Markierungspunkten aus GeoEdit))
		if (DBO().IsTRiASDBBased()) {
		HDC hDCs[2];
		
			hDCs[0] = (HDC)Handle (API_WINDOW_HDC);
			hDCs[1] = (HDC)Handle (API_WINDOW_TARGETHDC);
			if (!(GCancelFlag & GCFAppClosed)) {	// wenn App nicht geschlossen wurde
				DBO().DrawImpressum (hDCs[0], hDCs[1], CanvasRect());	// evtl. Impressum anzeigen
				DEXN_PaintTopLayer (hDCs);			// DeckerLayer zeichnen
			}
		}

	// Rahmen neu zeichnen
		SetWindowPos (Handle (API_WINDOW_HWND), NULL, 0, 0, 0, 0, 
			SWP_DRAWFRAME|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER);

		if (m_pDBOs -> Count() == 0 || !DBO().isOpened()) {
		// DB wurde inzwischen zu gemacht
			if (GCancelFlag & GCFAppClosed)
				App::Quit();
			GCancelFlag = GCFNormal;
			return;
		}
			
		if (PrintEFlag)		// evtl. aktivierte Obj's neu zeichnen
			ObjInfoListe.ActivateAllObj();	// nur wenn nicht gedruckt wird und nicht abgebrochen wurde

	// evtl. Legende neu zeichnen
		if (LegendToRepaint) {
			LegendToRepaint = false;
			if (LegendeCFlag) {
				pLegende -> RefreshLegend();
				pLegende -> RePaint();
			}
		}

	// Select-Rahmen evtl. neu zeichnen
		if (m_pDRO != NULL) {
			SelectClipRgn ((HDC)Handle (API_WINDOW_HDC), NULL);	// nicht mehr clippen
			Draw (*m_pDRO);
		}

	// Wieder alte Acceleratoren
		GetParent() -> ChangeAccel (oldAccel);
//		DrawMenuBar (Handle (API_WINDOW_HWND));

	// neu zeichnen auslösen
		if (GCancelFlag & GCFRepaint) {
		static Rectangle s_rcT;
		
			s_rcT = DBO().EA();
			DEX_RePaintRect (s_rcT);
		}
			
		GCancelFlag = GCFNormal;
		--m_iDrawSem;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Wird gerufen, wenn FlickerFreeDrawingCode die Gelegenheit geben will,
// derzeitige Anzeige zu aktualisieren
#if defined(_USE_FLICKERFREE_DRAWING)
BOOL IrisWind::DrawCallUp (DrawObject *pDO, BOOL fForce)
{
	if (NULL == m_pMemDC)
		return FALSE;

// fForce:	0 --> Zeichnen nicht erzwingen
//			1 --> Zeichnen erzwingen
//			2 --> Zeichnen vollständig abgeschlossen
	if (fForce & DRAWCALLUPMODE_Finished)
		m_fShouldRedraw = false;			// alles weitere nur noch über gespeicherte Bitmap

	return m_pMemDC -> Draw (fForce);
}
#endif // _USE_FLICKERFREE_DRAWING

/////////////////////////////////////////////////////////////////////////////
// Behandlung der MausEvents 
// MausTaste gedrückt

void IrisWind::MouseButtonDn (MouseEvt e) 
{
	SetFocus();				// alles weitere geht zu uns

// evtl. SignOn ausblenden
	DELETE_OBJ (g_pSODlg);

// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// evtl. Markierungsrechteck löschen
	if (m_pDRO != NULL && !m_iRightButtonSem && !m_iLeftButtonSem && !m_fTrackObjectMenuFlag) 
	{
		Draw (*m_pDRO);	// Rechteck löschen
		DELETE_OBJ (m_pDRO);
	}

#if defined(OLD_TOOLBOX)
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
int actTool = g_iActTool;
#endif // OLD_TOOLBOX

// MouseEventVerarbeitung
	if (e.isLeftButton() && !m_iRightButtonSem) {
		switch (actTool) {
		case NUMARROW:
		case NUMZOOM:
		case NUMLUPE:
		case NUMSCHERE:
			m_iLeftButtonSem++;	// linke Maustaste auswerten
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
			MouseTrap (CVOn);		// alle MausEvents an dieses Fenster
#else
			MouseTrap (On);		// alle MausEvents an dieses Fenster
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
#if defined(OLD_COORDS)
			if (pCoords != NULL) 	// Koordinatenanzeige aktualisieren
				pCoords -> SetMode (CoordsDlg::CM_Rectangle);
#endif // OLD_COORDS
		
			DELETE_OBJ (m_pDRO);		// DragRechteck initialisieren
			TX_TRY(m_pDRO = new DragRectangleObject (e.Where(), Dimension(), &emptyBrush()));
			if (m_pDRO == NULL) return;
			(*m_pDRO) -> ChangeRop (ROP_Invert);
			Draw (*m_pDRO);		// DragRechteck zeichnen
			break;

		case NUMLINEAL:
		// Mode: Entfernungen messen
			m_iLeftButtonSem++;
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
			MouseTrap (CVOn);		// alle MausEvents an dieses Fenster
#else
			MouseTrap (On);		// alle MausEvents an dieses Fenster
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
#if defined(OLD_COORDS)
			if (pCoords != NULL)	// Mode von Koordinatenanzeige
				pCoords -> SetMode (CoordsDlg::CM_Measure);
#endif // OLD_COORDS
			DELETE_OBJ (m_pDRO);
			TX_TRY(m_pDRO = new DragLineObject (e.Where()));
			if (m_pDRO == NULL) return;
			(*m_pDRO) -> ChangeRop (ROP_Invert);
			break;

		case NUMSCHRIFT:
			{		// Mode: Schrift verschieben
			Rectangle R;
			long lONr;
			Point pt = e.Where();
			
				if (!DBO().Shapes().FindSchriftObjekt (pt, lONr, R))
					return;

				DELETE_OBJ(m_pDRO);
				TX_TRY(m_pDRO = new ShiftRectangleObject (pt, lONr, R, this));
				if (m_pDRO == NULL) return;
				(*m_pDRO) -> ChangeRop (ROP_Invert);

				m_iLeftButtonSem++;
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
				MouseTrap (CVOn);		// alle MausEvents an dieses Fenster
#else
				MouseTrap (On);		// alle MausEvents an dieses Fenster
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

				Draw (*m_pDRO);		// neues Rechteck zeichnen
			}
			break;
		}
	}
	else if (e.isRightButton() && !m_iLeftButtonSem) {
	// rechte Maustaste auswerten
		switch (actTool) {
		case NUMARROW:
		case NUMLUPE:
		case NUMSCHERE:
			m_iRightButtonSem++;	// rechte Maustaste auswerten
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
			MouseTrap (CVOn);		// alle MausEvents an dieses Fenster
#else
			MouseTrap (On);			// alle MausEvents an dieses Fenster
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
#if defined(OLD_COORDS)
			if (pCoords != NULL) 	// Koordinatenanzeige aktualisieren
				pCoords -> SetMode (CoordsDlg::CM_Rectangle);
#endif // OLD_COORDS
		
			DELETE_OBJ (m_pDRO);		// DragRechteck initialisieren
			TX_TRY(m_pDRO = new DragRectangleObject (e.Where(), Dimension(), &emptyBrush()));
			if (m_pDRO == NULL) return;
			(*m_pDRO) -> ChangeRop (ROP_Invert);
			Draw (*m_pDRO);		// DragRechteck zeichnen
			break;

		case NUMZOOM:
		// Vergrößerung zurückschalten
			m_iRightButtonSem++;
			if (GetKeyState(VK_CONTROL) < 0)
				PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_RESTOREVIEWCONTAINER, 0L);
			else
				PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_PREVSELAUSSCHNITT, 0L);
			break;

		case NUMSCHRIFT:
		// TextObjectFloatingMenu anzeigen und auswerten
			if (!m_fTrackObjectMenuFlag) {
			long ONr;	// ObjektNummer des Textes
			Rectangle R;	// UmrißRechteck des TextObjektes
			Point Pt;	// Punkt, an dem Menu erscheint

				if (!DBO().Shapes().FindSchriftObjekt (e.Where(), ONr, R)) {
					ONr = -1;
					Pt = e.Where();
				} else
					Pt = Point (R.Right(), R.Bottom());

			Point pt = e.Where();

				DELETE_OBJ(m_pDRO);
				m_pDRO = new ShiftRectangleObject (pt, ONr, R);
				if (m_pDRO == NULL) return;
				(*m_pDRO) -> ChangeRop (ROP_Invert);

				m_iRightButtonSem++;
				m_fTrackObjectMenuFlag = true;

				Draw (*m_pDRO);				// neues Rechteck zeichnen
				if (!TrackTextObjectMenu (Pt, ONr, R)) {	// TextObjektMenu anzeigen
					m_iRightButtonSem--;		// Fenster wird direkt angezeigt und schluckt sonst MouseBttnUp
					Draw (*m_pDRO);				// Rechteck wieder wegblenden (nur, wenn kein Menu da war)
				}
				DELETE_OBJ (m_pDRO);
				m_fTrackObjectMenuFlag = false;
			}
			break;
		}
	}
}

// Maus wird bewegt
void IrisWind::MouseMove (MouseEvt e) 
{
// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

	MousePos = e.Where();   // aktuelle MouseKoordinaten merken

#if defined(OLD_COORDS)
// wenn Koordinatenanzeige aktiv ist, dann neue Koordinaten anzeigen
	if (pCoords != NULL) pCoords -> SetCoords (MousePos);
#endif // OLD_COORDS
}


// Maus bei gedrückter Maustaste bewegt
void IrisWind::MouseDrag (MouseEvt e) 
{
// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// Koordinaten immer anzeigen
	MousePos = e.Where();
#if defined(OLD_COORDS)
	if (pCoords != NULL) pCoords -> SetCoords (MousePos);
#endif // OLD_COORDS

// nur linke MausTaste auswerten
//	if (!m_iLeftButtonSem || !e.isLeftButton () || DRO == NULL) 
	if (NULL == m_pDRO) return;

// Masstab neu anzeigen
#if defined(OLD_TOOLBOX)
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
int actTool = g_iActTool;
#endif // OLD_TOOLBOX
#if defined(OLD_MASSTAB)
	if (pMasstab != NULL && actTool == NUMZOOM)
		pMasstab -> SetMasstab (((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> GetRect());
#else
	if (NUMZOOM == actTool)
		SetMasstab (((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> GetRect());
#endif // OLD_MASSTAB

// DragRechteck neu Dimensionieren und neu Zeichen
	Draw (*m_pDRO);
	(*m_pDRO) -> Process (MousePos);
	Draw (*m_pDRO);
}

// Maustaste wieder freigegeben
void IrisWind::MouseButtonUp (MouseEvt e) 
{
// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// Semaphore wieder löschen
bool fIsLeft = e.isLeftButton();
bool fIsRight = e.isRightButton();

	if (fIsRight && m_iRightButtonSem > 0) 
		m_iRightButtonSem--;
	if (fIsLeft && m_iLeftButtonSem > 0)
		m_iLeftButtonSem--;

//	if (!m_iLeftButtonSem || !e.isLeftButton () || DRO == NULL) 
	if (NULL == m_pDRO) return;	// fertig

// MausEvents wieder freigeben
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	MouseTrap (CVOff);
#else
	MouseTrap (Off);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

#if defined(OLD_COORDS)
// Koordinatenanzeige wieder in alten Zustand bringen
	if (pCoords != NULL) pCoords -> SetMode (CoordsDlg::CM_Normal);
#endif // OLD_COORDS

// Dragrechteck löschen, wenn nicht selektieren
#if defined(OLD_TOOLBOX)
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
int actTool = g_iActTool;
#endif // OLD_TOOLBOX

	Draw (*m_pDRO);		// ausblenden
	(*m_pDRO) -> Process (e.Where());

	if (actTool == NUMARROW || actTool == NUMZOOM || 
	    actTool == NUMLUPE || actTool == NUMSCHERE)
		((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> CorrectCoOrds(); // Rect ggf. kippen

// je nach aktivem Werkzeug Aktion auswählen
	switch (actTool) {
	case NUMARROW:
		if (fIsLeft) {
			if (!((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> isValid()) {
			// Rechteck ist entartet --> löschen
				DELETE_OBJ (m_pDRO);
				break;
			} else
				Draw (*m_pDRO); 	// DragRechteck neuzeichnen
		}
		else if (fIsRight) {	// SelectRectDlg anzeigen
			TX_ASSERT(NULL != m_pDRO);

		// Der Dialog übernimmt den Rest
			Draw (*m_pDRO); 	// DragRechteck neuzeichnen

			TX_ASSERT(NULL != DBO().pCT());

		CSelectRectDlg SRDlg (this, DBO().pCT(), *(DragRectangleObject *)(DrawObject *)(*m_pDRO));

			SRDlg.RemoveOnEnd (false);	// blendet DRO bei OK am Schluß nicht aus
			SRDlg.Show();
			if (!SRDlg.Result()) {
				DELETE_OBJ(m_pDRO);
			}
		}
		break;		// sonst nichts machen, Rechteck ist angezeigt

	case NUMLUPE:           // Recherche
	case NUMSCHERE:		// Recherche und Objekte löschen
		if (fIsRight) {	// SelectRectDlg anzeigen (nur Rechts)
			TX_ASSERT(NULL != m_pDRO);

			Draw (*m_pDRO); 	// DragRechteck neuzeichnen
			TX_ASSERT(NULL != DBO().pCT());

		CSelectRectDlg SRDlg (this, DBO().pCT(), *(DragRectangleObject *)(DrawObject *)(*m_pDRO));

			SRDlg.RemoveOnEnd (true);	// blendet DRO bei OK am Schluß aus
			SRDlg.Show();
			if (!SRDlg.Result())
				break;		// abbrechen
		} 
	// sowohl Rechts, als auch Links
		{
			if (!(((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> isValid()))
			// kein Rechteck aufgezogen
				((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> InflateRect (3);
				// Rechteck generieren (4x4Pix)

		// Koordinaten transformieren
		Point pt1 = ((DragRectangleObject *)(DrawObject *)(*m_pDRO))->LowerLeft();
		Point pt2 = ((DragRectangleObject *)(DrawObject *)(*m_pDRO))->UpperRight();
		Punkt Pt1 = DCtoOC (pt1);
		Punkt Pt2 = DCtoOC (pt2);
		ObjContainer OC (Pt1, Pt2);

			ObjektRecherche (*(DragRectangleObject *)(DrawObject *)(*m_pDRO), OC, actTool == NUMSCHERE);
		}
		break;

	case NUMZOOM:          // Bildausschnitt wählen, Selektieren
		if (!fIsLeft) return;

	// Testen ob Rechteck entartet ist
		if (((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> isValid() && 
			!((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> isNull()) 
		{
		// Koordinaten transformieren
		Point pt1 = ((DragRectangleObject *)(DrawObject *)(*m_pDRO))->LowerLeft();
		Point pt2 = ((DragRectangleObject *)(DrawObject *)(*m_pDRO))->UpperRight();
		Punkt Pt1 = DCtoOC (pt1);
		Punkt Pt2 = DCtoOC (pt2);
		ObjContainer OC (Pt1, Pt2);

		// wenn Auflösungsgrenze erreicht wurde
			if (!OC.isValid()) break;	// raus --> Fehlermeldung ???
		
			actClip.Push (DBO().GetExtend());	// alten Ausschnitt merken

		// neuen Ausschnitt einstellen
		ObjContainer oc = OC.InflateCont (10);
		
			SetExtend (oc);

			InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
			InitOverView (oc);		// Übersichtsfenster

			LegendToRepaint = true;		// neuen Ausschnitt darstellen
			m_fRePaintFlag = true;
			RePaint ();
		} 
		else {
		// bei einfachem Klick im Vergrößerungsmode ZoomIn machen
		Point pt = ((DragRectangleObject *)(DrawObject *)(*m_pDRO))->LowerLeft();
		Punkt Pt = DCtoOC (pt);

			doZoomIn (&Pt);
		}
		break;

	case NUMSCHRIFT:	// Schrift verschieben
		if (!fIsLeft) return;

		if (IsValidView()) {
		// neue TextKoordinaten wegschreiben
		ShiftRectangleObject *pSRO = (ShiftRectangleObject *)(DrawObject *)(*m_pDRO);
		Rectangle BRc = pSRO -> BoundingBox();

		// je nach BezugsPunkt den Punkt korrigieren
		Point Pt = Point (BRc.Left(), BRc.Bottom());
		long lONr = pSRO -> ONr();
		bool fRO = DEX_GetROModeEx (DEX_GetObjectProject(lONr));
		bool fTemp = DEX_GetObjectStatus (lONr) & OSTemp;

		// auf Bezugspunkt des Textes normalisieren
			DBO().Shapes().CorrectPosition (lONr, Pt);

		Punkt Pkt = DCtoOC (Pt);	// Geometrie ändern
		KoOrd x = Pkt.GetX();
		KoOrd y = Pkt.GetY();
		bool fHasRepaint = false;

#if defined(_KOORD_ISDOUBLE)
			DBO().pCT() -> Transform (&x, &y);
			Pkt = Punkt(x, y);
#endif // defined(_KOORD_ISDOUBLE)

			pSRO -> ResetPointer();	// Cursor rücksetzen
			if (GetKeyState (VK_CONTROL) >= 0) {
				if (!pSRO -> isDirty())
					break;		// keine Änderung

			// normales Text verschieben
			ResString resUndo (IDS_UNDOMODIFYTEXTPOINT, 64);
			char cbBuffer[64];

				wsprintf (cbBuffer, resUndo.Addr(), lONr);
				DEX_BeginUndoLevel (cbBuffer);

			LPUNDOREDOMODIFYOBJECT pIUndo = NULL;
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoModifyObject, (LPVOID *)&pIUndo);
			TEXTGEOMETRIEEX TG;

				if (SUCCEEDED(hr)) {
					INITSTRUCT(TG, TEXTGEOMETRIEEX);
					TG.lONr = lONr;
					TG.iObjTyp = OT_TEXT;
					TG.lCnt = 1;
					TG.iFlags = OGModObject;
#if defined(_KOORD_ISDOUBLE)
					TG.iFlags |= OGConverted;
#endif // defined(_KOORD_ISDOUBLE)
					TG.pdblX = &x;
					TG.pdblY = &y;
					TG.iKCnt = _MAX_PATH;
					hr = pIUndo -> Init (lONr, (OBJGEOMETRIE *)&TG, NULL);

					if (SUCCEEDED(hr) && !fRO && !fTemp) {
					char cbBuffer[_MAX_PATH];

						TG.pText = cbBuffer;
						DEX_GetObjGeometrie(TG);	
						x = Pkt.GetX();				// Koordinaten neu setzen
						y = Pkt.GetY();
						if (DEX_ModObjGeometrie (TG)) {
							if (SUCCEEDED(hr))
								DEX_AddUndoRedo (pIUndo);
							DEX_EndUndoLevel();

						Rectangle rc = InflateRect (pSRO -> oldR(), 5);
						Rectangle rc1 = InflateRect (pSRO -> BoundingBox(), 5);

							rc = rc + rc1;
							DEX_RePaintRectWait (rc);
							fHasRepaint = true;
						} else {
							DEX_CancelUndoLevel(true);
							break;
						}
					} else 	// nur in DB schieben, wenn nicht temp oder RO
						DEX_CancelUndoLevel(false);
				}
			}
			else 
				CopyText (lONr, Pkt, fRO);	// Text doppeln

			if (!fHasRepaint) {
			Rectangle rc = InflateRect (pSRO -> BoundingBox(), 5);
				
				DEX_RePaintRectWait (rc);
			}
		}
		break;
	}

// DrawObject freigeben, wenn nicht Pfeil
	if (actTool != NUMARROW)
		DELETE_OBJ (m_pDRO);
}

// EventHandler für MouseDoppelClick ------------------------------------------
void IrisWind::MouseButtonDblClk (MouseEvt e) 
{
// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	return;		// für DebuggingZwecke
}

// EventHandler für den Fall, daß das Fenster vom Nutzer verschoben wird
void IrisWind::Move (MoveEvt e) 
{
	return;		// für DebuggingZwecke
}

// EventHandler für den Fall, daß Fenstergröße vom Nutzer verändert wird ------
void IrisWind::ReSize (ReSizeEvt e) 
{
	if (IsValidView()) {
	// DB noch eröffnet
		InitWndScrollBars();	// bei Bedarf ScrollBars einblenden und initialisieren
		SetShouldRedraw();

	// wenn Übersicht angezeigt wird, dann Rechteck aktualisieren
	ObjContainer ocT = DBO().GetExtend();

		InitOverView (ocT);

#if defined(OLD_TOOLBOX)
		if (pToolBox)		// Werkzeugkasten neu positionieren
			pToolBox -> PositionTools();
#endif // OLD_TOOLBOX
	}
}

// Initialisierungsfunktion, die ObjInfoDlg-Fenster anzeigt -------------------
extern "C" {

typedef struct tagDELINFODATA {
	DragRectangleObject *pDRO;
	bool iDelFlag;
} DELINFODATA;

POINT EXPORTTRIAS WINAPI OICorrectPosition (pWindow pW, void *pData)
{
DELINFODATA *pDID = (DELINFODATA *)pData;

#if defined(WIN16)
	if (pDID -> iDelFlag) 
		((ObjektInfo *)pW) -> EnableDeleteMenu();
#endif // WIN16

return ((ObjektInfo *)pW) -> CorrectPosition (*pDID -> pDRO);
}

} // extern "C"


void IrisWind::ObjektRecherche (DragRectangleObject &rDRO, ObjContainer &OC, bool fDelFlag) 
{
ObjFeld Objekte;                // ArrayContainer
CEierUhr Wait (this);		// EierUhr anzeigen
HWND hWnd = NULL;

	if (GetKeyState (VK_CONTROL) < 0) 
		hWnd = ObjInfoListe.GetActiveORWindow();
		
// alle Objekte in diesem Rechteck suchen
	{
	ErrInstall EI (WC_NOON, ReportNotFoundError);
	HRESULT hr = DBO().GIWindow (OC, Objekte, TRUE, TRUE);   // Objektnummern aufsammeln, über Ansicht Filtern

		if (FAILED(hr)) 
			return;		// Fehler wurde bereits angezeigt

		if (0 == Objekte.Count()) {
			db_error (WC_NOON, RC_RechResults, "");
			return;
		}
	}

// Dialogfenster generieren
DEXXCREATEOBJEKTINFOEX crOI;
DELINFODATA DID;

	DID.pDRO = &rDRO;
	DID.iDelFlag = fDelFlag;

	memset (&crOI, '\0', sizeof(DEXXCREATEOBJEKTINFOEX));
	crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFOEX);

// mit neuer Toolbar gibt es keinen 'delete-knopf' mehr
//	if (!fDelFlag)	crOI.lpCaption = StrDupF (ResString (IDS_OBJINFOCAPTION, 30), RC_ObjRecherche);
//	else 		crOI.lpCaption = StrDupF (ResString (IDS_OBJDELCAPTION, 30), RC_ObjRecherche);
Color color(RED);
Point pt (0, 0);

	crOI.lpCaption = StrDupF (ResString (IDS_OBJINFOCAPTION, 30), RC_ObjRecherche);
	crOI.lcObjs = &Objekte;
	crOI.pcMColor = &color;
	crOI.ppntPos = &pt;
	crOI.fcnPos = (OIPOSPROC)OICorrectPosition;
	crOI.pData = &DID;

	crOI.m_hWnd = hWnd;		// zu existierendem hinzufügen
	
	DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren

	if (crOI.lpCaption) delete crOI.lpCaption;	// Speicher wieder freigeben
}


// TimerEvts ------------------------------------------------------------------
void EXPORTTRIAS IrisWind::Strobe (StrobeEvt e) 
{
	switch (e.GetStrobeID()) {
	case TIMER_HALFSECOND:
		{
		// Alle bestehenden Objektfenster durchsehen, ob noch alle
		// angezeigt werden, wenn nicht, dann löschen
			ObjInfoListe.CleanUpDeleted();

		// blinken wenn nicht gedruckt wird
			if (PrintEFlag && ObjInfoListe.Count()) 
				ObjInfoListe.BlinkAllObj();

		// evtl. Übersichtsfenster löschen
			if (pOverView && pOverView -> fToDelete()) {
				pOverView -> Hide();
				OverViewCFlag = false;
				COverView::DeleteInstance(pOverView);
				_ASSERTE(NULL == pOverView);
			}
		}
		break;

	default:
		break;
	}
}

// Parameter der ScrollBalken einstellen --------------------------------------
static LONG s_lScrollSem = -1L;

bool IrisWind::InitWndScrollBars (void) 
{
// wenn keine DB offen ist, dann wieder raus
	if (!IsValidView() || !Transformation::IsValid()) 
		return false;		// noch nicht fertig initialisiert

WndHorzScrollBar *pWHS = m_pWHS;	// nur für Vergleichszwecke
WndVertScrollBar *pWVS = m_pWVS;

	if (0 == piInterlockedIncrement (&s_lScrollSem)) {	// doppeltes rufen verhindern
	// Wertebereiche der ScrollBar's
	Rectangle Rc = RealCanvasRect();
	ObjContainer DBCont = DBO().DBCont();	// DatenbasisContainer

		for (short i = 0; i < 2; i++) {
		Punkt Pkt1 = DCtoOC (Rc.Left(), Rc.Bottom());
		Punkt Pkt2 = DCtoOC (Rc.Right(), Rc.Top());
		ObjContainer OC (Pkt1, Pkt2);
		ObjContainer ocDBContEx (DBCont);
		
			ocDBContEx += OC;
			ocDBContEx.InflateCont(5);	// 10% größer machen
						
		// TransformationsKoeffizienten
		KoOrd dSX;
		KoOrd dSY;
			
#if defined(ENABLE_WIN32S_CODE)
			if (IsWin32s()) {
				dSX = KoOrdMax (0, ocDBContEx.Breite()-OC.Breite());
				dSY = KoOrdMax (0, ocDBContEx.Hoehe()-OC.Hoehe());
				m_kSX = dSX/SHRT_MAX +1;
				m_kSY = dSY/SHRT_MAX +1;
			} else 
#endif // ENABLE_WIN32S_CODE
			{
				dSX = KoOrdMax (0, ocDBContEx.Breite());
				dSY = KoOrdMax (0, ocDBContEx.Hoehe());
				m_kSX = m_kSY = 1.0;
			}

		// Berechnen der ScrollBalken (auf long begrenzen)
			if (dSX < 0) dSX = 0.0;
			if (dSX > LONG_MAX) dSX = LONG_MAX;

			if (dSY < 0) dSY = 0.0;
			if (dSY > LONG_MAX) dSY = LONG_MAX;

		long iRangeH = dSX / m_kSX;
		long iRangeV = dSY / m_kSY;

			if (iRangeH < 0) iRangeH = 0;
			if (iRangeV < 0) iRangeV = 0;

		// etwas neuzeichnen ?
		long xThumbPos = m_pWHS ? m_pWHS -> GetThumbPos() : 0;
		long yThumbPos = m_pWVS ? m_pWVS -> GetThumbPos() : 0;

			if (yThumbPos > iRangeV || xThumbPos > iRangeH)
				RePaint();

		// vertikalen ScrollBalken anzeigen bzw. löschen
		int iPosRangeV = (ocDBContEx.Hoehe()-OC.Hoehe()) / m_kSY;

			if (iPosRangeV > 0) {
				m_pWVS = EnableVScroll (true);
				TX_ASSERT(NULL != m_pWVS);
				m_pWVS -> Show();
				m_pWVS -> SetRange (Range (0, iRangeV));
				yThumbPos = (OC.YMin()- ocDBContEx.YMin()) / m_kSY;
				yThumbPos = BOUND (yThumbPos, 0, iPosRangeV); // nur positive Zahlen
				m_pWVS -> SetThumbPos (iPosRangeV-yThumbPos);
#if defined(ENABLE_WIN32S_CODE)
				if (!IsWin32s())
#endif // ENABLE_WIN32S_CODE
					m_pWVS -> SetPageSize (OC.Hoehe() / m_kSY);
			} else {
				if (m_pWVS) m_pWVS -> Hide();
				if (m_pWVS) m_pWVS -> SetRange (Range (0, 0));

				EnableVScroll (false);
				m_pWVS = NULL;
				m_kSY = 1;
			}

		// Horizontalen Rollbalken anzeigen bzw. löschen
		int iPosRangeH = (ocDBContEx.Breite()-OC.Breite()) / m_kSX;

			if (iPosRangeH > 0) {
				m_pWHS = EnableHScroll (true);
				TX_ASSERT(NULL != m_pWHS);
				m_pWHS -> Show();
				m_pWHS -> SetRange (Range (0, iRangeH));
				xThumbPos = (OC.XMin()- ocDBContEx.XMin()) / m_kSX; 
				xThumbPos = BOUND (xThumbPos, 0, iPosRangeH); // nur positive Zahlen
				m_pWHS -> SetThumbPos (xThumbPos);
#if defined(ENABLE_WIN32S_CODE)
				if (!IsWin32s())
#endif // ENABLE_WIN32S_CODE
					m_pWHS -> SetPageSize (OC.Breite() / m_kSX);
			} else {
				if (m_pWHS) m_pWHS -> Hide();
				if (m_pWHS) m_pWHS -> SetRange (Range (0, 0));

				EnableHScroll (false);
				m_pWHS = NULL;
				m_kSX = 1.0;
			}

		// nur für die zweite Runde
			if (i == 0) Rc = CanvasRect();
		}
	}

	piInterlockedDecrement (&s_lScrollSem);

return (pWHS != m_pWHS) || (pWVS != m_pWVS);
}


// Verarbeitung der ScrollEvt's -----------------------------------------------
static IDLEPAINT NEAR g_ipIdlePaint;	// Struktur für Rollen/Neuzeichnen 

void App::Idle (InvokeStatus s)	// wenn sonst nichts zu tun ist
{
	if (s == IdleInit) {			// kommt nur einmal am Anfang
		g_ipIdlePaint.m_hWnd = NULL;
		g_ipIdlePaint.m_hRgn = NULL;

		DEXN_ServerInitialized();	// fertig initialisiert, MessageLoop läuft

		return;
	}
	if (g_ipIdlePaint.m_hWnd) {
	// Request is pending: Redraw
		if (g_ipIdlePaint.m_hRgn) {
		// Request is pending: RegionRedraw
			InvalidateRgn (g_ipIdlePaint.m_hWnd,
				       g_ipIdlePaint.m_hRgn, true);
					       			
		// ReInit IdlePaintStruct
			DeleteObject (g_ipIdlePaint.m_hRgn);
			g_ipIdlePaint.m_hRgn = NULL;
			g_ipIdlePaint.m_hWnd = NULL;	// doppeltes WM_PAINT verhindern
		} else {
		// FullRedraw
			InvalidateRect (g_ipIdlePaint.m_hWnd, NULL, true);
			g_ipIdlePaint.m_hWnd = NULL;	// doppeltes WM_PAINT verhindern
		}
	}
	if (g_fPendingSave) {
		g_fPendingSave = false;
		if (NULL != __hWndM)
			PostMessage (__hWndM, WM_COMMAND, IDM_AUTOSAVEDB, 0L);
	}
	if (g_fPendingReReadCaption) {	// Caption jetzt neu lesen
		g_fPendingReReadCaption = false;
		DEX_ReReadCaption();
	}
}

void IrisWind::VertScroll (ScrollEvt e)
{
	if (m_iDrawSem || m_pWVS == NULL) 
		return;		// nicht während des Zeichnens

ScrollType rgType = e.GetScrollType();

	if (EndScrollThumb == rgType/* && OverViewCFlag*/) {
		DEX_RePaint();
		return;
	}

// aktuelle RollBalkenParameter lesen
KoOrd iOldPos;
KoOrd iNewPos;

#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) {
		 iOldPos = e.GetOldPos();
		 iNewPos = e.GetPos();
	} else 
#endif // ENABLE_WIN32S_CODE
	{
		 iOldPos = m_pWVS -> GetThumbPos();
		 iNewPos = m_pWVS -> GetTrackPos();
	}
	if (ThumbDrag == rgType && iOldPos == iNewPos) 
		return;	// nothing to do
		
Rectangle Rc = CanvasRect();
Punkt Pkt1 = DCtoOC (Rc.Left(), Rc.Bottom());
Punkt Pkt2 = DCtoOC (Rc.Right(), Rc.Top());
ObjContainer OC (Pkt1, Pkt2);			// Container des aktuellen Fensters
Range r = m_pWVS -> GetRange();			// Scrollbereich lesen
KoOrd dSY = (r.Max()-r.Min())*m_kSY;
KoOrd Delta = 0;						// Fensterverschiebung besorgen

// neue horizontale Rollposition berechnen
	iOldPos *= m_kSY;
	iNewPos *= m_kSY;

	switch (rgType) {
	case UnitDecrement:	Delta = -OC.Hoehe() / 32;  break;
	case UnitIncrement:	Delta =  OC.Hoehe() / 32;  break;
	case BlockDecrement:	Delta = -OC.Hoehe() / 3;   break;
	case BlockIncrement:	Delta =  OC.Hoehe() / 3;   break;
	case ThumbDrag:		Delta = iNewPos - iOldPos; break;
	default:		Delta =  0; 		   
		return;
	}

// Rollen auf aktuellen Rollbereich begrenzen
uint uiSize = 0;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
		uiSize = m_pWVS -> GetPageSize();

	Delta = BOUND (iOldPos + Delta, 0, static_cast<int>(dSY - uiSize)) - iOldPos;
	if (Delta != 0) {
	HWND hWnd = Handle (API_WINDOW_HWND);
	CoOrd dY = -OCtoDCYDelta (Delta);
	
#if defined(OLD_TOOLBOX)
		if (pToolBox) pToolBox -> Hide();
#endif // OLD_TOOLBOX

		if (!(/*OverViewCFlag && */e.GetScrollType() == ThumbDrag)) {
		// wenn Overview angezeigt ist und stetiges scrollen, dann erst
		// am Schluß zeichnen
			if (m_pDRO != NULL) {
				Draw(*m_pDRO);		// DRO ausblenden
				DELETE_OBJ (m_pDRO);		// und freigeben
			}

// beim Abwärtsscrollen eins weniger
			DEXN_ScrollingVert (dY);
			ScrollWindow (hWnd, 0, (dY < 0) ? dY+1 : dY, NULL, NULL);
	#if defined(OLD_TOOLBOX)
			if (pToolBox) {
				pToolBox -> PositionTools();
				pToolBox -> Show();
			}
	#endif // OLD_TOOLBOX

			g_ipIdlePaint.m_hWnd = hWnd;

			if (!GetFullRedrawOnScroll()) {
			HRGN hRgn = CreateRectRgn (0, 0, 0, 0);
		
				GetUpdateRgn (hWnd, hRgn, false);
		
				if (g_ipIdlePaint.m_hRgn) {
				HRGN hCRgn = CreateRectRgn (0, 0, 0, 0);
				
					OffsetRgn (g_ipIdlePaint.m_hRgn, 0, dY);
					CombineRgn (hCRgn, hRgn, g_ipIdlePaint.m_hRgn, RGN_OR);
					DeleteObject (hRgn);
					DeleteObject (g_ipIdlePaint.m_hRgn);
					g_ipIdlePaint.m_hRgn = hCRgn;
				} else
					g_ipIdlePaint.m_hRgn = hRgn;
			} else
					g_ipIdlePaint.m_hRgn = NULL;
			                		
			ValidateRect (hWnd, NULL);	// nicht jetzt zeichnen 
		}
				
		m_pWVS -> SetThumbPos ((iOldPos + Delta)); // /m_kSY);

	// neuen Bildausschnitt in GeoDB einstellen
	Ausdehnung locA (0, -Delta);

		DBO().SetExtend (this, DBO().GetExtend().ShiftCont(locA), AspectRatio);
		if (OverViewCFlag && pOverView) 
			pOverView -> SetActVP (CanvasRect());
		SetShouldRedraw();
	}
}


void IrisWind::HorizScroll (ScrollEvt e) 
{
	if (m_iDrawSem || m_pWHS == NULL) 
		return;		// nicht während des Zeichnens

ScrollType rgType = e.GetScrollType();

	if (EndScrollThumb == rgType/* && OverViewCFlag*/) {
		DEX_RePaint();
		return;
	}

// aktuelle RollBalkenParameter lesen
KoOrd iOldPos;
KoOrd iNewPos;

#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) {
		 iOldPos = e.GetOldPos();
		 iNewPos = e.GetPos();
	} else 
#endif // ENABLE_WIN32S_CODE
	{
		 iOldPos = m_pWHS -> GetThumbPos();
		 iNewPos = m_pWHS -> GetTrackPos();
	}
	if (ThumbDrag == rgType && iOldPos == iNewPos) 
		return;		// nothing to do
		
Rectangle Rc = CanvasRect();
Punkt Pkt1 = DCtoOC (Rc.Left(), Rc.Bottom());
Punkt Pkt2 = DCtoOC (Rc.Right(), Rc.Top());
ObjContainer OC (Pkt1, Pkt2);			// Container des aktuellen Fensters
Range r = m_pWHS -> GetRange();			// Scrollbereich lesen
KoOrd dSX = (r.Max()-r.Min())*m_kSX;
KoOrd Delta = 0;				// Fensterverschiebung besorgen

// neue horizontale Rollposition berechnen
	iOldPos *= m_kSX;
	iNewPos *= m_kSX;
	
	switch (rgType) {
	case UnitDecrement:	Delta = -OC.Breite() / 32; break;
	case UnitIncrement:	Delta =  OC.Breite() / 32; break;
	case BlockDecrement:	Delta = -OC.Breite() / 3;  break;
	case BlockIncrement:	Delta =  OC.Breite() / 3;  break;
	case ThumbDrag:		Delta = iNewPos - iOldPos; break;
	default:		Delta =  0; 		   
		return;
	}

// Rollen auf aktuellen Rollbereich begrenzen
uint uiSize = 0;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
		uiSize = m_pWHS -> GetPageSize();

	Delta = BOUND (iOldPos + Delta, 0, static_cast<int>(dSX-uiSize)) - iOldPos;
	if (Delta != 0) {
	HWND hWnd = Handle (API_WINDOW_HWND);
	CoOrd dX = -OCtoDCXDelta (Delta);

#if defined(OLD_TOOLBOX)
		if (pToolBox) pToolBox -> Hide();	// Werkzeugkasten richten
#endif // OLD_TOOLBOX

		if (!(/*OverViewCFlag && */e.GetScrollType() == ThumbDrag)) {
		// wenn Overview angezeigt ist und stetiges scrollen, dann erst
		// am Schluß zeichnen
			if (m_pDRO != NULL) {
				Draw(*m_pDRO);				// DRO ausblenden
				DELETE_OBJ (m_pDRO);
			}
			
			DEXN_ScrollingHorz (dX);		// es soll gescrollt werden

			ScrollWindow (hWnd, dX, 0, NULL, NULL);
	#if defined(OLD_TOOLBOX)
			if (pToolBox) {
				pToolBox -> PositionTools();
				pToolBox -> Show();
			}
	#endif // OLD_TOOLBOX

			g_ipIdlePaint.m_hWnd = hWnd;

			if (!GetFullRedrawOnScroll()) {
			HRGN hRgn = CreateRectRgn (0, 0, 0, 0);
			
				GetUpdateRgn (hWnd, hRgn, false);
		
				if (g_ipIdlePaint.m_hRgn) {
				HRGN hCRgn = CreateRectRgn (0, 0, 0, 0);
				
					OffsetRgn (g_ipIdlePaint.m_hRgn, dX, 0);
					CombineRgn (hCRgn, hRgn, g_ipIdlePaint.m_hRgn, RGN_OR);
					DeleteObject (hRgn);
					DeleteObject (g_ipIdlePaint.m_hRgn);
					g_ipIdlePaint.m_hRgn = hCRgn;
				} else
					g_ipIdlePaint.m_hRgn = hRgn;
			} else
					g_ipIdlePaint.m_hRgn = NULL;
                		
			ValidateRect (hWnd, NULL);	// nicht jetzt zeichnen 
		}
				
		m_pWHS -> SetThumbPos ((iOldPos + Delta)); // /m_kSX);

	// neuen Bildausschnitt in GeoDB einstellen
	Ausdehnung locA (Delta, 0);

		DBO().SetExtend (this, DBO().GetExtend().ShiftCont(locA), AspectRatio);   
		if (OverViewCFlag && pOverView) 
			pOverView -> SetActVP (CanvasRect());
		SetShouldRedraw();
	}
}

// FocusChangeEvt -------------------------------------------------------------
void IrisWind::FocusChange (FocusChangeEvt e) { ChildAppWindow::FocusChange(e); }

// KeyEvents ------------------------------------------------------------------
void IrisWind::KeyDown (KeyEvt e) 
{ 
// evtl. SignOn ausblenden
	DELETE_OBJ (g_pSODlg);

// an Xtensions schicken
HWND hWnd = Handle (API_WINDOW_HWND);
	
	if (GetFrame() -> DispatchThroughXtensions (hWnd, (Event &)e))
		return;

// evtl. Cursor umschalten
	if (NULL != m_pDRO && m_pDRO -> ToProcessKey()) {
		Draw (*m_pDRO);
		m_pDRO -> ProcessKey(e);
		Draw (*m_pDRO);
	}

// RollBalken bedienen
	if (e.ASCIIChar() == '\0') {
		switch (e.Keycode()) {
		case VK_UP:
			if (m_pWVS) PostMessage (hWnd, WM_VSCROLL, SB_LINEUP,   0L);
			return;

		case VK_DOWN:
			if (m_pWVS) PostMessage (hWnd, WM_VSCROLL, SB_LINEDOWN, 0L);
			return;

		case VK_PRIOR:
			if (m_pWVS) PostMessage (hWnd, WM_VSCROLL, SB_PAGEUP,   0L);
			return;

		case VK_NEXT:
			if (m_pWVS) PostMessage (hWnd, WM_VSCROLL, SB_PAGEDOWN, 0L);
			return;

		case VK_HOME:
			if (m_pWHS) PostMessage (hWnd, WM_HSCROLL, SB_PAGEUP,   0L);
			return;

		case VK_END:
			if (m_pWHS) PostMessage (hWnd, WM_HSCROLL, SB_PAGEDOWN, 0L);
			return;
		
		case VK_LEFT:
			if (m_pWHS) PostMessage (hWnd, WM_HSCROLL, SB_LINEUP,   0L);
			return;

		case VK_RIGHT:
			if (m_pWHS) PostMessage (hWnd, WM_HSCROLL, SB_LINEDOWN, 0L);
			return;

		default:		// weiterreichen
			break;
		}
	}
	ChildAppWindow::KeyDown (e); 
}


void IrisWind::KeyUp (KeyEvt e) 
{ 
HWND hWnd = Handle (API_WINDOW_HWND);

// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (hWnd, (Event &)e))
		return;

	if (NULL != m_pDRO && m_pDRO -> ToProcessKey()) {
		Draw (*m_pDRO);
		m_pDRO -> ProcessKey(e);
		Draw (*m_pDRO);
	}

// ScrollBalken behandeln
	if (e.ASCIIChar() == '\0') {
		switch (e.Keycode()) {
		case VK_UP:
		case VK_DOWN:
		case VK_PRIOR:
		case VK_NEXT:
			if (m_pWVS) PostMessage (hWnd, WM_VSCROLL, SB_ENDSCROLL, 0L);
			return;

		case VK_HOME:
		case VK_END:
		case VK_LEFT:
		case VK_RIGHT:
			if (m_pWHS) PostMessage (hWnd, WM_HSCROLL, SB_ENDSCROLL, 0L);
			return;
			
		default:	// weiterreichen
			break;
		}
	}
	ChildAppWindow::KeyUp (e); 
}


// PaletteHandling ------------------------------------------------------------
void EXPORTTRIAS IrisWind::PaletteChange (PaletteChangeEvt e) 
{
HWND hWnd = Handle (API_CLIENT_HWND);
int i = 0;

	switch (e.GetPalAction()) {
	case PaletteChangeEvt::PaletteChanged:
	// Palette wurde von einem Fenster neu realisiert
		if (hPalette != NULL && hWnd != e.hPalChgWnd()) {
		HDC hDC = GetDC (hWnd);
		HPALETTE hOldPal = SelectPalette (hDC, hPalette, false);
			
			i = RealizePalette (hDC);
			if (i) UpdateColors (hDC);
			SelectPalette (hDC, hOldPal, false);
			ReleaseDC (hWnd, hDC);
		}	
		break;

	case PaletteChangeEvt::PaletteIsChanging:
		break;

	case PaletteChangeEvt::QueryNewPalette:
		if (hPalette) {
		HDC hDC = GetDC (hWnd);
		HPALETTE hOldPal = SelectPalette (hDC, hPalette, false);
			
			i = RealizePalette (hDC);
			SelectPalette (hDC, hOldPal, false);
			ReleaseDC (hWnd, hDC);
			if (i) InvalidateRect (hWnd, (LPRECT)NULL, true);
		}	
		break;

	default:
		Default ((Event &)e);
	}
}


// Member für DragRectangleObject ---------------------------------------------
void DragRectangleObject::InflateRect (int iPixels) 
{
	pt.X() -= iPixels; 
	pt.Y() += iPixels;
	dim.Width() += 2*iPixels; 
	dim.Height() -= 2*iPixels;
}

// Rechteck ggf. kippen
void DragRectangleObject::CorrectCoOrds (void) 
{
// Dimension ist bei Punkt (1, 1) !!
	if (dim.Width() < 1) {
		pt.X() = pt.X() + dim.Width();
		dim.Width() = -dim.Width();
	}
	if (dim.Height() > -1) {
		pt.Y() = pt.Y() + dim.Height();
		dim.Height() = -dim.Height();
	}
}

// Rechteck vergrößern/verkleinern --------------------------------------------
Rectangle InflateRect (Rectangle &R, short iDelta) 
{
	return Rectangle (R.Top() + iDelta, R.Left() - iDelta, 
			  R.Bottom() - iDelta, R.Right() + iDelta);
}


// Berechnung der ClientFlaeche unter Berücksichtigung der Rollbalken
Rectangle IrisWind::RealCanvasRect (void) 
{
long dwStyle = GetWindowLong (Handle (API_CLIENT_HWND), GWL_STYLE);
							// FensterStil
Rectangle Rc = CanvasRect();

	if (dwStyle & WS_HSCROLL)
		Rc.Bottom() -= GetSystemMetrics (SM_CYHSCROLL);
	if (dwStyle & WS_VSCROLL)
		Rc.Right() -= GetSystemMetrics (SM_CXVSCROLL);

return Rc;
}

// Dispatcher für das IrisWind ------------------------------------------------
#if defined(_USE_CTL3D)
extern bool g_fCtl3dInit;		// CTL3D.DLL richtig initialisiert
#endif // defined(_USE_CTL3D)

LRESULT EXPORTTRIAS IrisWind::Dispatch (Event e)
{
register UINT uiMsg = e.Msg();

	switch (uiMsg) {
#if defined(_OLD_DRAGNDROP)
	case WM_DROPFILES:	// Dragging bearbeiten 
		return DragFunc (e.WParam());
#endif // _OLD_DRAGNDROP

	case WM_SYSCOLORCHANGE:
#if defined(_USE_CTL3D)
		if (g_fCtl3dInit) Ctl3dColorChange();
#endif // defined(_USE_CTL3D)
		break;

	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
		DELETE_OBJ (g_pSODlg);	// SignOn sicher freigeben
		break;

	case WM_CANCELMODE:
		if (m_fHandleCancelMode)
			GCancelFlag = GCFAbort;		// Zeichnen abbrechen
		break;

	case WM_DEVMODECHANGE:		// Druckereinstellung geändert ?
		{
		char *pT = (char *)e.LParam();
		}
		break;

#if defined(_USE_FLICKERFREE_DRAWING)
	case WM_ERASEBKGND:
	// Fensterhintergrund nicht löschen, wenn doublebuffering eingeschaltet ist,
	// außerdem muß Ansicht aktiv sein
		if (m_fPreventRepaint)
			break;				// nicht ständig neu zeichnen
		if (!IsValidView())
			break;				// kein gültiges Fenster etc.
		if (PF_INVALID == DBO().toPaint())
			break;				// derzeit nicht zeichnen
		if (!DBO().HasActiveSight())
			break;				// keine aktuelle Ansicht
		if (!PrintEFlag)
			break;				// derzeit wird gedruckt
		if (!(g_dwDrawingMode & DRAWMODE_FlickerFree))
			break;				// normal (nicht flickerarm) zeichnen
		if (m_fShouldRedrawRect) {
			m_fShouldRedrawRect = false;
			break;				// nur einen Ausschnitt neu zeichnen (diesen herausschneiden)
		}

	// Hintergrund nicht löschen
		return FALSE;
#endif // _USE_FLICKERFREE_DRAWING
	}

	return ChildAppWindow::Dispatch (e);
}
