// IRIS - Version für Win32 -- EventVerarbeitung ------------------------------
// File: IRISEVT2.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <xtensnxx.h>
#include <rect.hxx>

#include <dirisole.h>

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
#include "signon.hxx"
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
extern COverView *pOverView;		// Übersichtsanzeige

extern bool Profiling;

extern short GCancelFlag;
extern bool PrintEFlag;

extern bool LegendToRepaint;
extern bool LegendeCFlag;
extern bool OverViewCFlag;
extern bool GenerateLegendOnly;	// PseudoZeichnen, um genaue Legende zu haben

extern CLegendeWindow *pLegende;

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
// externe Funktionsdeklarationen ---------------------------------------------
Dimension GetDotsPerMM (HANDLE hDC);
Rectangle InflateRect (Rectangle &R, short iDelta);

///////////////////////////////////////////////////////////////////////////////
// lediglich feststellen, daß wir jetzt angezeigt werden
void IrisWind :: Show (ShowState s)
{
	if (HideWindow != s && !isVisible())
		m_fFirstDrawing = true;
	ChildAppWindow::Show(s);
}

///////////////////////////////////////////////////////////////////////////////
// Teile des Fensters neu zeichnen --------------------------------------------
void IrisWind :: Expose (ExposeEvt e) 
{
	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;
		
	if (m_fPreventRepaint)
		return;		// gar nicht zeichnen

	if (DBO().DB().isOpened() && DBO().toPaint() != PF_INVALID) {
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
	// Rahmen neu zeichnen
		SetWindowPos (Handle (API_WINDOW_HWND), NULL, 0, 0, 0, 0, 
			SWP_DRAWFRAME|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER);

	// DB neu zeichnen (Ausschnitt)
	Rectangle rcEA = e.GetExposedArea();

		InflateRect ((RECT *)&rcEA, 0, -2);
		if (rcEA.Bottom() < 0) rcEA.Bottom() = 0;
		 
//		if (rcEA.Top() > 0) rcEA.Top()--; 	// CommonVu - BugFixing
//		if (rcEA.Bottom() > 0) rcEA.Bottom()--;
		DBO().SetEA(rcEA);	// neu zu zeichnendes Rechteck
		
	// Fenster neu skalieren
		DBO().Scale (this, DBO().GetExtend(), AspectRatio);
	
	// bei Bedarf ScrollBars einblenden und initialisieren
		if (m_fFirstDrawing) {
			InitWndScrollBars();
			m_fFirstDrawing = false;
		}

#if defined(OLD_MASSTAB)
	// Maßstab neu angeben
		if (PrintEFlag && pMasstab != NULL)
			pMasstab -> SetMasstab (CanvasRect());
#else
		if (PrintEFlag)
			SetMasstab (CanvasRect());
#endif // OLD_MASSTAB

		GenerateLegendOnly = false;
		DrawEx ((DrawObject *)&DBO(), 0);

		if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened()) {
		// DB wurde inzwischen zu gemacht
			if (GCancelFlag & GCFAppClosed)
				App :: Quit();
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
		if (DRO != NULL) {
			SelectClipRgn ((HDC)Handle (API_WINDOW_HDC), NULL);	// nicht mehr clippen
			Draw (*DRO);
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


// Behandlung der MausEvents --------------------------------------------------
// MausTaste gedrückt

static short NEAR LeftButtonSem = false;	// Semaphor für linke MausTaste
static short NEAR RightButtonSem = false;	// Semaphor für rechte Maustaste
static short NEAR TrackObjectMenuFlag = false;	// Semaphore für Floating Mneu

void IrisWind :: MouseButtonDn (MouseEvt e) 
{
	SetFocus();				// alles weitere geht zu uns

// evtl. SignOn ausblenden
	DELETE (g_pSODlg);

// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// evtl. Markierungsrechteck löschen
	if (DRO != NULL && !RightButtonSem && !LeftButtonSem && !TrackObjectMenuFlag) 
	{
		Draw (*DRO);	// Rechteck löschen
		DELETE (DRO);
	}

#if defined(OLD_TOOLBOX)
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
int actTool = g_iActTool;
#endif // OLD_TOOLBOX

// MouseEventVerarbeitung
	if (e.isLeftButton() && !RightButtonSem) {
		switch (actTool) {
		case NUMARROW:
		case NUMZOOM:
		case NUMLUPE:
		case NUMSCHERE:
			LeftButtonSem++;	// linke Maustaste auswerten
			MouseTrap (On);		// alle MausEvents an dieses Fenster
#if defined(OLD_COORDS)
			if (pCoords != NULL) 	// Koordinatenanzeige aktualisieren
				pCoords -> SetMode (CoordsDlg :: CM_Rectangle);
#endif // OLD_COORDS
		
			DELETE (DRO);		// DragRechteck initialisieren
			DRO = new DragRectangleObject (e.Where(), Dimension(), &emptyBrush());
			if (DRO == NULL) return;
			(*DRO) -> ChangeRop (ROP_Invert);
			Draw (*DRO);		// DragRechteck zeichnen
			break;

		case NUMLINEAL:
		// Mode: Entfernungen messen
			LeftButtonSem++;
			MouseTrap (On);		// alle MausEvt's an dieses Fenster
#if defined(OLD_COORDS)
			if (pCoords != NULL)	// Mode von Koordinatenanzeige
				pCoords -> SetMode (CoordsDlg :: CM_Measure);
#endif // OLD_COORDS
			DELETE (DRO);
			DRO = new DragLineObject (e.Where());
			if (DRO == NULL) return;
			(*DRO) -> ChangeRop (ROP_Invert);
			break;

		case NUMSCHRIFT:
			{		// Mode: Schrift verschieben
			Rectangle R;
			long lONr;
			Point pt = e.Where();
			
				if (!DBO().Shapes().FindSchriftObjekt (pt, lONr, R))
					return;

				DRO = new ShiftRectangleObject (pt, lONr, R, this);
				if (DRO == NULL) return;
				(*DRO) -> ChangeRop (ROP_Invert);

				LeftButtonSem++;
				MouseTrap (On);		// alle MouseEvt's an dieses Fenster

				Draw (*DRO);		// neues Rechteck zeichnen
			}
			break;
		}
	}
	else if (e.isRightButton() && !LeftButtonSem) {
	// rechte Maustaste auswerten
		switch (actTool) {
		case NUMARROW:
		case NUMLUPE:
		case NUMSCHERE:
			RightButtonSem++;	// rechte Maustaste auswerten
			MouseTrap (On);		// alle MausEvents an dieses Fenster
#if defined(OLD_COORDS)
			if (pCoords != NULL) 	// Koordinatenanzeige aktualisieren
				pCoords -> SetMode (CoordsDlg :: CM_Rectangle);
#endif // OLD_COORDS
		
			DELETE (DRO);		// DragRechteck initialisieren
			DRO = new DragRectangleObject (e.Where(), Dimension(), &emptyBrush());
			if (DRO == NULL) return;
			(*DRO) -> ChangeRop (ROP_Invert);
			Draw (*DRO);		// DragRechteck zeichnen
			break;

		case NUMZOOM:
		// Vergrößerung zurückschalten
			RightButtonSem++;
			if (GetKeyState(VK_CONTROL) < 0)
				PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_RESTOREVIEWCONTAINER, 0L);
			else
				PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_PREVSELAUSSCHNITT, 0L);
			break;

		case NUMSCHRIFT:
		// TextObjectFloatingMenu anzeigen und auswerten
			if (!TrackObjectMenuFlag) {
			long ONr;	// ObjektNummer des Textes
			Rectangle R;	// UmrißRechteck des TextObjektes
			Point Pt;	// Punkt, an dem Menu erscheint

				if (!DBO().Shapes().FindSchriftObjekt (e.Where(), ONr, R)) {
					ONr = -1;
					Pt = e.Where();
				} else
					Pt = Point (R.Right(), R.Bottom());

			Point pt = e.Where();
			
				DRO = new ShiftRectangleObject (pt, ONr, R);
				if (DRO == NULL) return;
				(*DRO) -> ChangeRop (ROP_Invert);

				RightButtonSem++;
				TrackObjectMenuFlag = true;

				Draw (*DRO);				// neues Rechteck zeichnen
				TrackTextObjectMenu (Pt, ONr, R);	// TextObjektMenu anzeigen

				Draw (*DRO);				// Rechteck wieder wegblenden
				DELETE (DRO);
				TrackObjectMenuFlag = false;
			}
			break;
		}
	}
}

// Maus wird bewegt
void IrisWind :: MouseMove (MouseEvt e) 
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
void IrisWind :: MouseDrag (MouseEvt e) 
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
//	if (!LeftButtonSem || !e.isLeftButton () || DRO == NULL) 
	if (NULL == DRO) return;

// Masstab neu anzeigen
#if defined(OLD_TOOLBOX)
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
int actTool = g_iActTool;
#endif // OLD_TOOLBOX
#if defined(OLD_MASSTAB)
	if (pMasstab != NULL && actTool == NUMZOOM)
		pMasstab -> SetMasstab (((DragRectangleObject *)(DrawObject *)(*DRO)) -> GetRect());
#else
	if (NUMZOOM == actTool)
		SetMasstab (((DragRectangleObject *)(DrawObject *)(*DRO)) -> GetRect());
#endif // OLD_MASSTAB

// DragRechteck neu Dimensionieren und neu Zeichen
	Draw (*DRO);
	(*DRO) -> Process (MousePos);
	Draw (*DRO);
}

// Maustaste wieder freigegeben
void IrisWind :: MouseButtonUp (MouseEvt e) 
{
// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// Semaphore wieder löschen
bool fIsLeft = e.isLeftButton();
bool fIsRight = e.isRightButton();

	if (fIsRight && RightButtonSem > 0) 
		RightButtonSem--;
	if (fIsLeft && LeftButtonSem > 0)
		LeftButtonSem--;

//	if (!LeftButtonSem || !e.isLeftButton () || DRO == NULL) 
	if (NULL == DRO) return;	// fertig

// MausEvents wieder freigeben
	MouseTrap (Off);

#if defined(OLD_COORDS)
// Koordinatenanzeige wieder in alten Zustand bringen
	if (pCoords != NULL) pCoords -> SetMode (CoordsDlg :: CM_Normal);
#endif // OLD_COORDS

// Dragrechteck löschen, wenn nicht selektieren
#if defined(OLD_TOOLBOX)
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
int actTool = g_iActTool;
#endif // OLD_TOOLBOX

	Draw (*DRO);		// ausblenden
	(*DRO) -> Process (e.Where());

	if (actTool == NUMARROW || actTool == NUMZOOM || 
	    actTool == NUMLUPE || actTool == NUMSCHERE)
		((DragRectangleObject *)(DrawObject *)(*DRO)) -> CorrectCoOrds(); // Rect ggf. kippen

// je nach aktivem Werkzeug Aktion auswählen
	switch (actTool) {
	case NUMARROW:
		if (fIsLeft) {
			if (!((DragRectangleObject *)(DrawObject *)(*DRO)) -> isValid()) {
			// Rechteck ist entartet --> löschen
				DELETE (DRO);
				break;
			} else
				Draw (*DRO); 	// DragRechteck neuzeichnen
		}
		else if (fIsRight) {	// SelectRectDlg anzeigen
			TX_ASSERT(NULL != DRO);

		// Der Dialog übernimmt den Rest
			Draw (*DRO); 	// DragRechteck neuzeichnen

		CSelectRectDlg SRDlg (this, DBO().pCT(), *(DragRectangleObject *)(DrawObject *)(*DRO));

			SRDlg.RemoveOnEnd (false);	// blendet DRO bei OK am Schluß nicht aus
			SRDlg.Show();
			if (!SRDlg.Result()) {
				DELETE(DRO);
			}
		}
		break;		// sonst nichts machen, Rechteck ist angezeigt

	case NUMLUPE:           // Recherche
	case NUMSCHERE:		// Recherche und Objekte löschen
		if (fIsRight) {	// SelectRectDlg anzeigen (nur Rechts)
			TX_ASSERT(NULL != DRO);

			Draw (*DRO); 	// DragRechteck neuzeichnen

		CSelectRectDlg SRDlg (this, DBO().pCT(), *(DragRectangleObject *)(DrawObject *)(*DRO));

			SRDlg.RemoveOnEnd (true);	// blendet DRO bei OK am Schluß aus
			SRDlg.Show();
			if (!SRDlg.Result())
				break;		// abbrechen
		} 
	// sowohl Rechts, als auch Links
		{
			if (!(((DragRectangleObject *)(DrawObject *)(*DRO)) -> isValid()))
			// kein Rechteck aufgezogen
				((DragRectangleObject *)(DrawObject *)(*DRO)) -> InflateRect (3);
				// Rechteck generieren (4x4Pix)

		// Koordinaten transformieren
		Point pt1 = ((DragRectangleObject *)(DrawObject *)(*DRO))->LowerLeft();
		Point pt2 = ((DragRectangleObject *)(DrawObject *)(*DRO))->UpperRight();
		Punkt Pt1 = DCtoOC (pt1);
		Punkt Pt2 = DCtoOC (pt2);
		ObjContainer OC (Pt1, Pt2);

			ObjektRecherche (*(DragRectangleObject *)(DrawObject *)(*DRO), OC, 
					 actTool == NUMSCHERE);
		}
		break;

	case NUMZOOM:          // Bildausschnitt wählen, Selektieren
		if (!fIsLeft) return;

	// Testen ob Rechteck entartet ist
		if (((DragRectangleObject *)(DrawObject *)(*DRO)) -> isValid ()) {
		// Koordinaten transformieren
		Point pt1 = ((DragRectangleObject *)(DrawObject *)(*DRO))->LowerLeft();
		Point pt2 = ((DragRectangleObject *)(DrawObject *)(*DRO))->UpperRight();
		Punkt Pt1 = DCtoOC (pt1);
		Punkt Pt2 = DCtoOC (pt2);
		ObjContainer OC (Pt1, Pt2);
		// wenn Auflösungsgrenze erreicht wurde
			if (!OC.isValid()) break;	// raus --> Fehlermeldung ???
		
			actClip.Push (DBO().GetExtend());	// alten Ausschnitt merken

		// neuen Ausschnitt einstellen
		ObjContainer oc = OC.InflateCont (10);
		
			DBO().SetExtend (this, oc, AspectRatio);

			InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
			InitOverView (oc);		// Übersichtsfenster

			LegendToRepaint = true;		// neuen Ausschnitt darstellen
			m_fRePaintFlag = true;
			RePaint ();
		}
		break;

	case NUMSCHRIFT:	// Schrift verschieben
		if (!fIsLeft) return;

		if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
		// neue TextKoordinaten wegschreiben
		ShiftRectangleObject *pSRO = (ShiftRectangleObject *)(DrawObject *)(*DRO);
		Rectangle BRc = pSRO -> BoundingBox();

		// je nach BezugsPunkt den Punkt korrigieren
		Point Pt = Point (BRc.Left(), BRc.Bottom());
		long lONr = pSRO -> ONr();
		bool fRO = DEX_GetROMode();
		bool fTemp = DEX_GetObjectStatus (lONr) & OSTemp;

		// auf Bezugspunkt des Textes normalisieren
			DBO().Shapes().CorrectPosition (lONr, Pt);

		Punkt Pkt = DCtoOC (Pt);	// Geometrie ändern

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
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoModifyObject, 
							 (LPVOID *)&pIUndo);
				if (SUCCEEDED(hr)) {
				TEXTGEOMETRIE TG;

					INITSTRUCT(TG, TEXTGEOMETRIE);
					TG.lONr = lONr;
					TG.lCnt = 1;
					TG.iFlags = OGModObject;
					TG.pdblX = &Pkt.X();
					TG.pdblY = &Pkt.Y();
					TG.iKCnt = _MAX_PATH;
					hr = pIUndo -> Init (lONr, (OBJGEOMETRIE *)&TG, NULL);
				}

				if (!fRO && !fTemp) {
					if (EC_OKAY == DBO().DB().ModGIPunkt (lONr, Pkt)) {
						if (SUCCEEDED(hr))
							DEX_AddUndoRedo (pIUndo);
						DEX_EndUndoLevel();
					} else {
						DEX_CancelUndoLevel(true);
						break;
					}
				} else 	// nur in DB schieben, wenn nicht temp oder RO
					DEX_CancelUndoLevel(false);

				if (DBO().Shapes().ModGIText (lONr, Pkt)) {
				Rectangle rc = pSRO -> oldR();
			
					RePaintRect (InflateRect (rc, 5));
				} 
			}
			else 
				CopyText (lONr, Pkt, fRO);	// Text doppeln

		Rectangle rc = pSRO -> BoundingBox();
			
			RePaintRect (InflateRect (rc, 5));
		}
		break;
	}

// DrawObject freigeben, wenn nicht Pfeil
	if (actTool != NUMARROW)
		DELETE (DRO);
}

// EventHandler für MouseDoppelClick ------------------------------------------
void IrisWind :: MouseButtonDblClk (MouseEvt e) 
{
// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (Handle(API_WINDOW_HWND), (Event &)e))
		return;

	return;		// für DebuggingZwecke
}

// EventHandler für den Fall, daß das Fenster vom Nutzer verschoben wird
void IrisWind :: Move (MoveEvt e) 
{
	return;		// für DebuggingZwecke
}

// EventHandler für den Fall, daß Fenstergröße vom Nutzer verändert wird ------
void IrisWind :: ReSize (ReSizeEvt e) 
{
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
	// DB noch eröffnet
		InitWndScrollBars();	// bei Bedarf ScrollBars einblenden und initialisieren

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

#if !defined(WIN32)
	if (pDID -> iDelFlag) 
		((ObjektInfo *)pW) -> EnableDeleteMenu();
#endif // !WIN32

return ((ObjektInfo *)pW) -> CorrectPosition (*pDID -> pDRO);
}

} // extern "C"


void IrisWind :: ObjektRecherche (DragRectangleObject &DRO, ObjContainer &OC, bool fDelFlag) 
{
ObjFeld Objekte;                // ArrayContainer
CEierUhr Wait (this);		// EierUhr anzeigen
HWND hWnd = NULL;

	if (GetKeyState (VK_CONTROL) < 0) 
		hWnd = ObjInfoListe.GetActiveORWindow();
		
// alle Objekte in diesem Rechteck suchen
	{
	ErrInstall EI (WC_NOON, ReportNotFoundError);
	ErrCode EC = DBO().DB().GIWindow (OC, Objekte, true);   // Objektnummern aufsammeln

		if (EC != EC_OKAY) return;

	// nach Identifikatoren filtern
		DBO().DB().IdFilter (Objekte, DBO().Idents());
		if (0 == Objekte.Count()) {
			db_error (WC_NOON, RC_RechResults, "");
			return;
		}
	}

// Dialogfenster generieren
DEXXCREATEOBJEKTINFOEX crOI;
DELINFODATA DID;

	DID.pDRO = &DRO;
	DID.iDelFlag = fDelFlag;

	memset (&crOI, '\0', sizeof(DEXXCREATEOBJEKTINFOEX));
	crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFOEX);

// mit neuer Toolbar gibt es keinen 'delete-knopf' mehr
//	if (!fDelFlag)	crOI.lpCaption = StrDup (ResString (IDS_OBJINFOCAPTION, 30), RC_ObjRecherche);
//	else 		crOI.lpCaption = StrDup (ResString (IDS_OBJDELCAPTION, 30), RC_ObjRecherche);
	crOI.lpCaption = StrDup (ResString (IDS_OBJINFOCAPTION, 30), RC_ObjRecherche);
	crOI.lcObjs = &Objekte;
	crOI.pcMColor = new Color (RED);
	crOI.ppntPos = new Point (0, 0);
	crOI.fcnPos = (OIPOSPROC)OICorrectPosition;
	crOI.pData = &DID;

	crOI.m_hWnd = hWnd;		// zu existierendem hinzufügen
	
	DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren

	if (crOI.ppntPos) delete crOI.ppntPos;
	if (crOI.pcMColor) delete crOI.pcMColor;
	if (crOI.lpCaption) delete crOI.lpCaption;	// Speicher wieder freigeben
}


// TimerEvts ------------------------------------------------------------------
void EXPORTTRIAS IrisWind :: Strobe (StrobeEvt e) 
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
				DELETE (pOverView);
			}
		}
		break;

	default:
		break;
	}
}

// Parameter der ScrollBalken einstellen --------------------------------------
static LONG s_lScrollSem = -1L;

bool IrisWind :: InitWndScrollBars (void) 
{
// wenn keine DB offen ist, dann wieder raus
	if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened() || DBO().isClosing()) 
		return false;
	
	if (!Transformation::IsValid())
		return false;		// noch nicht fertig initialisiert

WndHorzScrollBar *pWHS = m_pWHS;	// nur für Vergleichszwecke
WndVertScrollBar *pWVS = m_pWVS;

	if (0 == piInterlockedIncrement (&s_lScrollSem)) {	// doppeltes rufen verhindern
	// Wertebereiche der ScrollBar's
	Rectangle Rc = RealCanvasRect();
	ObjContainer DBCont = DBO().DB().DBCont();	// DatenbasisContainer

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
				m_kSX = m_kSY = 1;
			}

		// Berechnen der ScrollBalken
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
				m_kSX = 1;
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

void App :: Idle (InvokeStatus s)	// wenn sonst nichts zu tun ist
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
			PostMessage (__hWndM, WM_COMMAND, IDM_SAVEDB, 0L);
	}
	if (g_fPendingReReadCaption) {	// Caption jetzt neu lesen
		g_fPendingReReadCaption = false;
		DEX_ReReadCaption();
	}
}

void IrisWind :: VertScroll (ScrollEvt e)
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
			if (DRO != NULL) {
				Draw(*DRO);		// DRO ausblenden
				DELETE (DRO);		// und freigeben
			}
			
			DEXN_ScrollingVert (dY);

			ScrollWindow (hWnd, 0, dY, NULL, NULL);
	#if defined(OLD_TOOLBOX)
			if (pToolBox) {
				pToolBox -> PositionTools();
				pToolBox -> Show();
			}
	#endif // OLD_TOOLBOX

			g_ipIdlePaint.m_hWnd = hWnd;

			if (!m_fFullRedrawOnScroll) {
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

		DBO().Scale (this, DBO().GetExtend().ShiftCont (locA), AspectRatio);
		if (OverViewCFlag && pOverView) {
		Rectangle rcC = CanvasRect();
		ObjContainer OC (rcC);
			
			pOverView -> SetActVP (OC);
		}
	}
}


void IrisWind :: HorizScroll (ScrollEvt e) 
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
			if (DRO != NULL) {
				Draw(*DRO);				// DRO ausblenden
				DELETE (DRO);
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

			if (!m_fFullRedrawOnScroll) {
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

		DBO().Scale (this, DBO().GetExtend().ShiftCont (locA), AspectRatio);   
		if (OverViewCFlag && pOverView) {
		Rectangle rcC = CanvasRect();
		ObjContainer OC (rcC);
			
			pOverView -> SetActVP (OC);
		}
	}
}

// FocusChangeEvt -------------------------------------------------------------
void IrisWind :: FocusChange (FocusChangeEvt e) { ChildAppWindow :: FocusChange(e); }

// KeyEvents ------------------------------------------------------------------
void IrisWind :: KeyDown (KeyEvt e) 
{ 
// evtl. SignOn ausblenden
	DELETE (g_pSODlg);

// an Xtensions schicken
HWND hWnd = Handle (API_WINDOW_HWND);
	
	if (GetFrame() -> DispatchThroughXtensions (hWnd, (Event &)e))
		return;

// evtl. Cursor umschalten
	if (NULL != DRO && DRO -> ToProcessKey()) {
		Draw (*DRO);
		DRO -> ProcessKey(e);
		Draw (*DRO);
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
	ChildAppWindow :: KeyDown (e); 
}


void IrisWind :: KeyUp (KeyEvt e) 
{ 
HWND hWnd = Handle (API_WINDOW_HWND);

// an Xtensions schicken
	if (GetFrame() -> DispatchThroughXtensions (hWnd, (Event &)e))
		return;

	if (NULL != DRO && DRO -> ToProcessKey()) {
		Draw (*DRO);
		DRO -> ProcessKey(e);
		Draw (*DRO);
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
	ChildAppWindow :: KeyUp (e); 
}


// PaletteHandling ------------------------------------------------------------
void EXPORTTRIAS IrisWind :: PaletteChange (PaletteChangeEvt e) 
{
HWND hWnd = Handle (API_CLIENT_HWND);
int i = 0;

	switch (e.GetPalAction()) {
	case PaletteChangeEvt :: PaletteChanged:
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

	case PaletteChangeEvt :: PaletteIsChanging:
		break;

	case PaletteChangeEvt :: QueryNewPalette:
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
void DragRectangleObject :: InflateRect (int iPixels) 
{
	pt.X() -= iPixels; 
	pt.Y() += iPixels;
	dim.Width() += 2*iPixels; 
	dim.Height() -= 2*iPixels;
}

// Rechteck ggf. kippen
void DragRectangleObject :: CorrectCoOrds (void) 
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
Rectangle IrisWind :: RealCanvasRect (void) 
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
extern bool g_fCtl3dInit;		// CTL3D.DLL richtig initialisiert

LRESULT EXPORTTRIAS IrisWind :: Dispatch (Event e)
{
register UINT uiMsg = e.Msg();

	switch (uiMsg) {
#if defined(_OLD_DRAGNDROP)
	case WM_DROPFILES:	// Dragging bearbeiten 
		return DragFunc (e.WParam());
#endif // _OLD_DRAGNDROP

	case WM_SYSCOLORCHANGE:
		if (g_fCtl3dInit) Ctl3dColorChange();
		break;

	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
		DELETE (g_pSODlg);	// SignOn sicher freigeben
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
	}

return ChildAppWindow :: Dispatch (e);
}
