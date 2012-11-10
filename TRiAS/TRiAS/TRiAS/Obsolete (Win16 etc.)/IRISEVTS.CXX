// IRIS - Version fuer Windows 3.1 -- EventVerarbeitung -----------------------
// File: IRISEVTS.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <xtensnxx.h>
#include <rect.hxx>

#if defined(OLD_TOOLBOX)
#include "tools.hxx"    // ToolBoxKonstanten
#endif // OLD_TOOLBOX
#include "coords.hxx"
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

#if !defined(WIN32)
#include "nomenkl.hxx"
#else
#include <funcs03.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#endif // !WIN32


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define BOUND(x,min,max) ((x)<(min)?(min):((x)>(max)?(max):(x)))

extern Window *CurrActW;        // HauptFenster
extern App *CurrApp;
extern ToolWind *pToolBox;
extern TextRechercheDlg *pTextSearch;

extern CoordsDlg *pCoords;
extern COverView *pOverView;		// Übersichtsanzeige

#if !defined(WIN32)
extern NomenklaturDlg *pNomenkl;
#endif // !WIN32

extern bool Profiling;

extern short GCancelFlag;
extern bool TextSearchCFlag;
extern bool PrintEFlag;

extern bool LegendToRepaint;
extern bool LegendeCFlag;
extern bool OverViewCFlag;
extern bool GenerateLegendOnly;	// PseudoZeichnen, um genaue Legende zu haben

extern CLegendeWindow *pLegende;

extern MasstabDlg *pMasstab;

extern HPALETTE hPalette;	// derzeit aktive Palette des IrisWind

extern short g_iMinutes;
extern short g_iTicks;
extern short g_iSignOnTicks;

extern bool g_fPendingSave;	// Speichern muß gemacht werden

extern CSignOnDlg *g_pSODlg;	// SignOnDlg

// externe Funktionsdeklarationen ---------------------------------------------
Dimension GetDotsPerMM (HANDLE hDC);
Rectangle InflateRect (Rectangle &R, short iDelta);

// Teile des Fensters neu zeichnen --------------------------------------------
void IrisWind :: Expose (ExposeEvt e) 
{
	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;
		
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

	CEierUhr Wait (this);		// EierUhr anzeigen
	
		++m_iDrawSem; 

	// MenuPunkt IDM_DRAW verändern
	HMENU hMenu = IrisMenu.Handle(API_MENU_HMENU);
	
		ModifyMenu (hMenu, IDM_DRAW, MF_BYCOMMAND, 
			    IDM_CANCEL, ResString (IDS_CANCELDRAW, 25));

	// Accelerator für Abbruch installieren
        Accel newAccel (CANCELACCELS);
	pAccel oldAccel = ChangeAccel (&newAccel);

		DrawMenuBar (Handle (API_WINDOW_HWND));
		GCancelFlag = GCFNormal;

	// eigentliche Zeichenroutinen
#if !defined(NOGITTER)
	// evtl. Gitternetz zeichnen
		RePaintFlag = false;
		if (Gitter.GitterFlag()) // Gitternetz zeichnen
			Draw ((DrawObject *)&Gitter);
#endif
	// DB neu zeichnen (Ausschnitt)
	Rectangle rcEA = e.GetExposedArea();

		InflateRect ((RECT *)&rcEA, 0, -2);
		if (rcEA.Bottom() < 0) rcEA.Bottom() = 0;
		 
//		if (rcEA.Top() > 0) rcEA.Top()--; 	// CommonVu - BugFixing
//		if (rcEA.Bottom() > 0) rcEA.Bottom()--;
		DBO().SetEA(rcEA);	// neu zu zeichnendes Rechteck
		
	// Fenster neu skalieren
		DBO().Scale (this, DBO().GetExtend(), AspectRatio);

	// Maßstab neu angeben
		if (PrintEFlag && pMasstab != NULL)
			pMasstab -> SetMasstab (CanvasRect());

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

	// MenuPunkt IDM_REDRAW wieder initialisieren
		ModifyMenu (hMenu, IDM_CANCEL, MF_BYCOMMAND, 
			    IDM_DRAW, ResString (IDS_DRAW, 25));

	// Wieder alte Acceleratoren
		ChangeAccel (oldAccel);
		DrawMenuBar (Handle (API_WINDOW_HWND));

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
// evtl. SignOn ausblenden
	DELETE (g_pSODlg);
	
	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// evtl. Markierungsrechteck löschen
	if (DRO != NULL && !RightButtonSem && !LeftButtonSem && !TrackObjectMenuFlag) 
	{
		Draw (*DRO);	// Rechteck löschen
		DELETE (DRO);
	}

short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;

// MouseEventVerarbeitung
	if (e.isLeftButton() && !RightButtonSem) {
		switch (actTool) {
		case NUMARROW:
		case NUMZOOM:
		case NUMLUPE:
		case NUMSCHERE:
			LeftButtonSem++;	// linke Maustaste auswerten
			MouseTrap (On);		// alle MausEvents an dieses Fenster
			if (pCoords != NULL) 	// Koordinatenanzeige aktualisieren
				pCoords -> SetMode (CoordsDlg :: CM_Rectangle);
		
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
			if (pCoords != NULL)	// Mode von Koordinatenanzeige
				pCoords -> SetMode (CoordsDlg :: CM_Measure);
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
#if defined(WIN32)
		case NUMARROW:
		case NUMLUPE:
		case NUMSCHERE:
			RightButtonSem++;	// rechte Maustaste auswerten
			MouseTrap (On);		// alle MausEvents an dieses Fenster
			if (pCoords != NULL) 	// Koordinatenanzeige aktualisieren
				pCoords -> SetMode (CoordsDlg :: CM_Rectangle);
		
			DELETE (DRO);		// DragRechteck initialisieren
			DRO = new DragRectangleObject (e.Where(), Dimension(), NULL, &emptyBrush());
			if (DRO == NULL) return;
			(*DRO) -> ChangeRop (ROP_Invert);
			Draw (*DRO);		// DragRechteck zeichnen
			break;
#endif // WIN32

		case NUMZOOM:
		// Vergrößerung zurückschalten
			RightButtonSem++;
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
	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

	MousePos = e.Where();   // aktuelle MouseKoordinaten merken

// wenn Koordinatenanzeige aktiv ist, dann neue Koordinaten anzeigen
	if (pCoords != NULL) pCoords -> SetCoords (MousePos);

#if !defined(WIN32)
// wenn Nomenklaturanzeige aktiv ist, dann Nomenklatur neu anzeigen
	if (pNomenkl != NULL) pNomenkl -> SetCoords (MousePos);
#endif // !WIN32
}


// Maus bei gedrückter Maustaste bewegt
void IrisWind :: MouseDrag (MouseEvt e) 
{
	if (NULL == m_pDBOs || 0 == m_pDBOs -> Count())
		return;

// Koordinaten immer anzeigen
	MousePos = e.Where();
	if (pCoords != NULL) pCoords -> SetCoords (MousePos);

// nur linke MausTaste auswerten
//	if (!LeftButtonSem || !e.isLeftButton () || DRO == NULL) 
	if (NULL == DRO) return;

// Masstab neu anzeigen
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;

	if (pMasstab != NULL && actTool == NUMZOOM)
		pMasstab -> SetMasstab (((DragRectangleObject *)(DrawObject *)(*DRO)) -> GetRect());

// DragRechteck neu Dimensionieren und neu Zeichen
	Draw (*DRO);
	(*DRO) -> Process (MousePos);
	Draw (*DRO);
}

// Maustaste wieder freigegeben
void IrisWind :: MouseButtonUp (MouseEvt e) 
{
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

// Koordinatenanzeige wieder in alten Zustand bringen
	if (pCoords != NULL) pCoords -> SetMode (CoordsDlg :: CM_Normal);

// Dragrechteck löschen, wenn nicht selektieren
short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;

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
#if defined(WIN32)
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
#endif // WIN32
		break;		// sonst nichts machen, Rechteck ist angezeigt

	case NUMLUPE:           // Recherche
	case NUMSCHERE:		// Recherche und Objekte löschen
#if defined(WIN32)
		if (fIsRight) {	// SelectRectDlg anzeigen (nur Rechts)
			TX_ASSERT(NULL != DRO);

			Draw (*DRO); 	// DragRechteck neuzeichnen

		CSelectRectDlg SRDlg (this, DBO().pCT(), *(DragRectangleObject *)(DrawObject *)(*DRO));

			SRDlg.RemoveOnEnd (true);	// blendet DRO bei OK am Schluß aus
			SRDlg.Show();
			if (!SRDlg.Result())
				break;		// abbrechen
		} 
#endif // WIN32
		{	// sowohl Rechts, als auch Links
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

		// bei Bedarf ScrollBars einblenden und initialisieren
			InitWndScrollBars ();
			
		// wenn Übersicht angezeigt wird, dann Rechteck aktualisieren
			if (OverViewCFlag && pOverView) {
			Rectangle rcC = CanvasRect();
			ObjContainer OC (rcC);
			
				pOverView -> SetActVP (OC);
			}

			LegendToRepaint = true;		// neuen Ausschnitt darstellen
			RePaintFlag = true;
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

#if defined(WIN32)
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
#else // WIN32
		// normales Text verschieben
			if (!fRO && !fTemp && (DBO().DB().ModGIPunkt (lONr, Pkt) != EC_OKAY))
				break;		// nur in DB schieben, wenn nicht temp oder RO

			if (DBO().Shapes().ModGIText (lONr, Pkt)) {
			Rectangle rc = pSRO -> oldR();
			
				RePaintRect (InflateRect (rc, 5));
			}
#endif // WIN32
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
void IrisWind :: MouseButtonDblClk (MouseEvt) 
{
	return;		// für DebuggingZwecke
}


// EventHandler für den Fall, daß Fenstergröße vom Nutzer verändert wird ------
void IrisWind :: ReSize (ReSizeEvt e) 
{
// neue FensterGröße merken
	MSize = e.GetNewSize();

// bei Bedarf ScrollBars einblenden und initialisieren
	InitWndScrollBars();

// wenn Übersicht angezeigt wird, dann Rechteck aktualisieren
	if (OverViewCFlag && pOverView) {
	ObjContainer ocT = DBO().GetExtend();
	ObjContainer ocT1 = DBO().DB().DBCont();

		if (ocT < ocT1) {
		Rectangle rcC = CanvasRect();
		ObjContainer OC (rcC);
			
			pOverView -> SetActVP (OC);
		}
	}

	if (pToolBox)		// Werkzeugkasten neu positionieren
		pToolBox -> PositionTools();
}

// EventHandler für den Fall, daß das Fenster vom Nutzer verschoben wird
void IrisWind :: Move (MoveEvt e) 
{	// neuen FensterUrsprung merken
	MOrig = e.NewOrigin();
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

	if (pDID -> iDelFlag) 
		((ObjektInfo *)pW) -> EnableDeleteMenu();

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
	if (!fDelFlag)	crOI.lpCaption = StrDup (ResString (IDS_OBJINFOCAPTION, 30), RC_ObjRecherche);
	else 		crOI.lpCaption = StrDup (ResString (IDS_OBJDELCAPTION, 30), RC_ObjRecherche);
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


// Initialisierungsfunktion, die ObjInfoDlg-Fenster anzeigt -------------------
ErrCode IrisWind :: ShowOIRechResults (ObjFeld &OF) 
{
#if 0 // ======================================================================
// Dialogfenster generieren
DEXXCREATEOBJEKTINFOEX crOI;
ErrCode RC;

	memset (&crOI, '\0', sizeof(DEXXCREATEOBJEKTINFOEX));
	crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
	crOI.lpCaption = StrDup (ResString (IDS_DBASEINFOCAPTION, 30), RC_RechResults);
	crOI.lcObjs = &OF;
	crOI.pcMColor = new Color (RED);
	crOI.ppntPos = new Point (0, 0);
	crOI.fcnPos = NULL;
	crOI.pData = NULL;

	RC = DEXX_CreateObjektInfo (crOI) != NULL ? EC_OKAY ? WC_RETURN;	// RechercheFenster generieren

	if (crOI.ppntPos) delete crOI.ppntPos;
	if (crOI.pcMColor) delete crOI.pcMColor;
	if (crOI.lpCaption) delete crOI.lpCaption;	// Speicher wieder freigeben

//	ValidateWindow ();		// Hauptfenster nicht neu zeichnen

return RC;
#endif // =====================================================================

return EC_OKAY;
}

// TimerEvts ------------------------------------------------------------------
void EXPORTTRIAS IrisWind :: Strobe (StrobeEvt e) 
{
	switch (e.GetStrobeID()) {
	case 1:
		{
		CTable t(ObjInfoListe);
		// Alle bestehenden Objektfenster durchsehen, ob noch alle
		// angezeigt werden, wenn nicht, dann löschen
			for (t.First(); t.Valid(); ) {
			register bool toDelete = false;
				{
				ObjektInfoLock l(t);

					if (l && l -> m_fToDelete) toDelete = true;
				}
				if (toDelete) {
					if (!t.Delete()) break;
				} else {
					if (!t.Next()) break;
				}
			}
			if (PrintEFlag && ObjInfoListe.Count()) 
				ObjInfoListe.BlinkAllObj ();	// blinken wenn nicht gedruckt wird

		// evtl. Übersichtsfenster löschen
			if (pOverView && pOverView -> fToDelete()) {
				DELETE (pOverView);
			}
				
		// SignOn nach spätestens 5 Sekunden ausblenden
			if (g_iSignOnTicks == 10) {
				DELETE (g_pSODlg);
			} else if (g_iSignOnTicks < 10)
				g_iSignOnTicks++;
		}
		break;
		
	case 2: 	// TimerEvent kommt jede Minute, FlushDB auslösen
		{
			if ((g_iTicks++/10) < g_iMinutes)
				break;
			g_iTicks = 0;
			g_fPendingSave = true;
		}
		break;
	}
}


// Parameter der ScrollBalken einstellen --------------------------------------
void IrisWind :: InitWndScrollBars (void) 
{
// wenn keine DB offen ist, dann wieder raus
	if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened() || DBO().isClosing()) 
		return;
	
static short NEAR iScrollSem = 0;

	if (!iScrollSem) {
		iScrollSem++;			// doppeltes rufen verhindern

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
		KoOrd dSX = KoOrdMax (0, ocDBContEx.Breite() - OC.Breite());
		KoOrd dSY = KoOrdMax (0, ocDBContEx.Hoehe() - OC.Hoehe());
			
			m_kSX = dSX/SHRT_MAX +1;
			m_kSY = dSY/SHRT_MAX +1;

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

		// ScrollBalken anzeigen bzw. löschen
			if (iRangeV > 0) {
				m_pWVS = EnableVScroll (true);
				m_pWVS -> Show();
				m_pWVS -> SetRange (Range (0, short(iRangeV)));
				yThumbPos = (OC.YMin()- ocDBContEx.YMin()) / m_kSY;
				yThumbPos = BOUND (yThumbPos, 0, iRangeV); // nur positive Zahlen
				m_pWVS -> SetThumbPos (short(iRangeV-yThumbPos));
			} else {
				if (m_pWVS) m_pWVS -> Hide();
				if (m_pWVS) m_pWVS -> SetRange (Range (0, 0));

				EnableVScroll (false);
				m_pWVS = NULL;
				m_kSY = 1;
			}
			if (iRangeH > 0) {
				m_pWHS = EnableHScroll (true);
				m_pWHS -> Show();
				m_pWHS -> SetRange (Range (0, short (iRangeH)));
				xThumbPos = (OC.XMin()- ocDBContEx.XMin()) / m_kSX; 
				xThumbPos = BOUND (xThumbPos, 0, iRangeH); // nur positive Zahlen
				m_pWHS -> SetThumbPos (short(xThumbPos));
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
		iScrollSem--;
	}
}


// Verarbeitung der ScrollEvt's -----------------------------------------------
static IDLEPAINT NEAR g_ipIdlePaint;	// Struktur für Rollen/Neuzeichnen 

void App :: Idle (InvokeStatus s)	// wenn sonst nichts zu tun ist
{
	if (s == IdleInit) {		// komt nur einmal am Anfang
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
}


void IrisWind :: VertScroll (ScrollEvt e)
{
	if (m_iDrawSem || m_pWVS == NULL) 
		return;		// nicht während des zeichnens
	
// aktuelle RollBalkenParameter lesen
KoOrd iOldPos = e.GetOldPos();
KoOrd iNewPos = e.GetPos();

	if (iOldPos == iNewPos) return;	// nothing to do
		
Rectangle Rc = CanvasRect();
Punkt Pkt1 = DCtoOC (Rc.Left(), Rc.Bottom());
Punkt Pkt2 = DCtoOC (Rc.Right(), Rc.Top());
ObjContainer OC (Pkt1, Pkt2);			// Container des aktuellen Fensters
Range r = m_pWVS -> GetRange();			// Scrollbereich lesen
KoOrd dSY = (r.Max()-r.Min())*m_kSY;
KoOrd Delta = 0;				// Fensterverschiebung besorgen

// neue horizontale Rollposition berechnen
	iOldPos *= m_kSY;
	iNewPos *= m_kSY;

	switch (e.GetScrollType()) {
	case UnitDecrement:	Delta = -OC.Hoehe() / 32;  break;
	case UnitIncrement:	Delta =  OC.Hoehe() / 32;  break;
	case BlockDecrement:	Delta = -OC.Hoehe() / 3;   break;
	case BlockIncrement:	Delta =  OC.Hoehe() / 3;   break;
	case ThumbDrag:		Delta = iNewPos - iOldPos; break;
	default:		Delta =  0; 		   
		return;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	Delta = BOUND (iOldPos + Delta, 0, dSY) - iOldPos;
	if (Delta != 0) {
	HWND hWnd = Handle (API_WINDOW_HWND);
	CoOrd dY = -OCtoDCYDelta (Delta);
	
		if (pToolBox) pToolBox -> Hide();
		if (DRO != NULL) {
			Draw(*DRO);		// DRO ausblenden
			DELETE (DRO);		// und freigeben
		}
		
		DEXN_ScrollingVert (dY);

		ScrollWindow (hWnd, 0, dY, NULL, NULL);
		if (pToolBox) {
			pToolBox -> PositionTools();
			pToolBox -> Show();
		}

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
		
		m_pWVS -> SetThumbPos (short((iOldPos + Delta)/m_kSY));

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
	
// aktuelle RollBalkenParameter lesen
KoOrd iOldPos = e.GetOldPos();
KoOrd iNewPos = e.GetPos();

	if (iOldPos == iNewPos) return;		// nothing to do
		
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
	
	switch (e.GetScrollType()) {
	case UnitDecrement:	Delta = -OC.Breite() / 32; break;
	case UnitIncrement:	Delta =  OC.Breite() / 32; break;
	case BlockDecrement:	Delta = -OC.Breite() / 3;  break;
	case BlockIncrement:	Delta =  OC.Breite() / 3;  break;
	case ThumbDrag:		Delta = iNewPos - iOldPos; break;
	default:		Delta =  0; 		   
		return;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	Delta = BOUND (iOldPos + Delta, 0, dSX) - iOldPos;
	if (Delta != 0) {
	HWND hWnd = Handle (API_WINDOW_HWND);
	CoOrd dX = -OCtoDCXDelta (Delta);

		if (pToolBox) pToolBox -> Hide();	// Werkzeugkasten richten
		if (DRO != NULL) {
			Draw(*DRO);				// DRO ausblenden
			DELETE (DRO);
		}
		
		DEXN_ScrollingHorz (dX);		// es soll gescrollt werden

		ScrollWindow (hWnd, dX, 0, NULL, NULL);
		if (pToolBox) {
			pToolBox -> PositionTools();
			pToolBox -> Show();
		}

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
		
		m_pWHS -> SetThumbPos (short((iOldPos + Delta)/m_kSX));

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
void EXPORTTRIAS IrisWind :: FocusChange (FocusChangeEvt e) { StrobeWindow :: FocusChange (e); }

// KeyEvents ------------------------------------------------------------------
void IrisWind :: KeyDown (KeyEvt e) 
{ 
// evtl. SignOn ausblenden
	DELETE (g_pSODlg);

#if defined(WIN32)
// evtl. Cursor umschalten
	if (NULL != DRO) {

		if (DRO -> ToProcessKey()) {
			Draw (*DRO);
			DRO -> ProcessKey(e);
			Draw (*DRO);
		}
	}
#endif // WIN32

// RollBalken bedienen
	if (e.ASCIIChar() == '\0') {
	HWND hWnd = Handle (API_WINDOW_HWND);
	
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
	StrobeWindow :: KeyDown (e); 
}


void IrisWind :: KeyUp (KeyEvt e) 
{ 
#if defined(WIN32)
	if (NULL != DRO) {

		if (DRO -> ToProcessKey()) {
			Draw (*DRO);
			DRO -> ProcessKey(e);
			Draw (*DRO);
		}
	}
#endif // WIN32

// ScrollBalken behandeln
	if (e.ASCIIChar() == '\0') {
	HWND hWnd = Handle (API_WINDOW_HWND);
	
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
	StrobeWindow :: KeyUp (e); 
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
register UINT uiMsg = ((NakedEvt &)e).wmsg();

	switch (uiMsg) {
	case WM_DROPFILES:	// Dragging bearbeiten 
		return DragFunc (((NakedEvt &)e).wparam());

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
		char *pT = (char *)((NakedEvt &)e).lparam();
		}
		break;
	}

return StrobeWindow :: Dispatch (e);
}
