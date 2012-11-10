// Anzeige und Bearbeiten des PunktMenu's -------------------------------------
// File PNTMENU.CXX

#include "editobjp.hxx"

#include "editobjr.h"

#include <dblpair.hxx>
#include <numeditx.hxx>
#include <dblnumex.hxx>
#include <dllbindx.hxx>
#include <ctfx.hxx>

#include <undoguid.h>           // GUID

#include "editpnt.hxx"

extern "C" {

typedef struct tagFOUNDPOINT {
	long lONr;
	RECT Rc;
} FOUNDPOINT;

bool _XTENSN_EXPORT PASCAL FoundObject (long lONr, RECT R, void *pData)
{
	((FOUNDPOINT *)pData) -> lONr = lONr;		// ObjektNummer merken
	((FOUNDPOINT *)pData) -> Rc = R;

return false;	// nur ein Objekt enumerieren
}

}

// Funktion, welche Menu anzeigt, wenn rechte Maustaste gedrückt wurde --------
bool EditObjExtension :: FindPointObjFromPoint (Point &Pt, bool iCorrect)
{
// Enumeration aller PunktObjekte unter dem Mausklick
FINDOBJECT FO;
FOUNDPOINT FP;    
Rectangle CRc = MVWind() -> CanvasRect();	// Y-Koordinate doch drehen
Point cvtPt (0, 0);

	cvtPt.X() = Pt.X();
	cvtPt.Y() = CRc.Top() - CRc.Bottom() - Pt.Y();

	FP.lONr = -1;				// gefundene ObjektNummer
	SetRect (&FP.Rc, 0, 0, 0, 0);		// zugehöriges Rechteck

	memset (&FO, '\0', sizeof (FINDOBJECT));
	FO.dwSize = sizeof (FINDOBJECT);
	FO.Pt = *(POINT *)&cvtPt;
	FO.iFOMode = FOPunkt;		// nur Punktobjekte
	FO.pData = &FP;			// erstes gefundenes Punktobjekt
	FO.eFcn = (FINDOBJECTPROC)FoundObject;
	DEX_FindObjectsFromPoint (FO);

// das Rechteck, welches verschoben werden kann               
Point RcPt (FP.Rc.left, FP.Rc.bottom);
Dimension Dim (FP.Rc.right - FP.Rc.left, FP.Rc.top - FP.Rc.bottom);

	DELETE (_pSRO);			// für alle Fälle
	_pSRO = new ShiftRectangleObject (cvtPt, FP.lONr, RcPt, Dim);
	if (_pSRO == NULL) return false;
	_pSRO -> ChangeRop (ROP_Invert);

// das Menu erscheint am Punkt Pt
	if (FP.lONr != -1L && iCorrect) {		// Objekt gefunden
		Pt = Point (FP.Rc.right, FP.Rc.bottom);	// Menu rechts unten
		Pt.Y() = CRc.Top() - CRc.Bottom() - Pt.Y();
	}

return FP.lONr != -1L;
}
		

// Anzeigen und Auswerten des PunktPopupMenus ---------------------------------
void EditObjExtension :: ShowPointMenu (Point Pt)
{
// neues Rechteck zeichnen
pWindow pW = MVWind();

	pW -> Draw (_pSRO);
	TrackPointObjectMenu (MWind(), pW, Pt);	// TextObjektMenu anzeigen
	pW -> Draw (_pSRO);		// Rechteck wieder wegblenden
}


// Verschieben des Markierungsrechteckes --------------------------------------
void EditObjExtension :: MovePointObj (Point Pt, bool iFlag)
{
pWindow pW = MVWind();
Rectangle CRc = pW -> CanvasRect();

	Pt.Y() = CRc.Top() - CRc.Bottom() - Pt.Y();

	if (iFlag) pW -> Draw (_pSRO);		// evtl. erstes mal zeichnen
	_pSRO -> Process (Pt);
	pW -> Draw (_pSRO);
}



static void AddMenuOffset (HMENU hMenu, short iOffset);

void EditObjExtension :: TrackPointObjectMenu (pWindow pW, pWindow pWCoord, Point Pt)
{
Menu PointTrackMenu (ResID (POINTOBJMENU, &RF()));
HMENU hMenu = PointTrackMenu.Handle (API_MENU_HMENU);

	if (hMenu == NULL) return;	// Resource nicht gefunden
	
// Menu generieren/Offsets addieren
HMENU hSubMenu = GetSubMenu (hMenu, 0);		// SubMenu holen

	AddMenuOffset (hSubMenu, MenuOffset());

	_pSRO -> hMenu() = hSubMenu;

	ClientToScreen (pWCoord -> Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
	TrackPopupMenu (hSubMenu, 0, Pt.X(), Pt.Y(), 
			0, pW -> Handle (API_CLIENT_HWND), NULL);
}


// Modifikation eines Menu's (addieren des Menuoffsets) -----------------------
static void AddMenuOffset (HMENU hMenu, short iOffset)
{
	if (hMenu == 0) return;		// nur für gültige Menu's

int nCount = GetMenuItemCount (hMenu);
char MenuEntry[DEX_MENUNAMELEN+1];

	for (int wItem = 0; wItem < nCount; wItem++) {
	UINT MenuState = GetMenuState (hMenu, wItem, MF_BYPOSITION);
	UINT MenuID = GetMenuItemID (hMenu, wItem);

		if (MenuID == -1) {	// PopUpMenu
			AddMenuOffset (GetSubMenu (hMenu, wItem), iOffset);	
			continue;
		}
		if (MenuState & (MF_MENUBARBREAK | MF_MENUBREAK | MF_SEPARATOR))
			continue;
		GetMenuString (hMenu, wItem, MenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
		ModifyMenu (hMenu, wItem, MF_BYPOSITION | MenuState, MenuID+iOffset, MenuEntry);
	}
}


// Eigentliche MenuFunktionen -------------------------------------------------
// Bilden eines PunktObjektes -------------------------------------------------
#define MCODESIZE	40

bool EditObjExtension :: CreatePointObj (void)
{
	if (_pSRO == NULL) return false;

Point newPt = _pSRO -> actPt();

	DELETE (_pSRO);		// jetzt freigeben

	if (_pIL == NULL) return false;			// keine DB eröffnet

// in DB-Koordinaten konvertieren
COORDCONVERT CC;
Punkt Pkt;
Rectangle CRc = MVWind() -> CanvasRect();

	newPt.Y() = CRc.Top() - CRc.Bottom() - newPt.Y();

	CC.lpPt = (POINT *)&newPt;
	CC.lpPkt = (long *)&Pkt;
	DEX_DCtoOC (CC);

// Identifikator des neuen Punktes abholen
long ID = -1L;

	{
	EditPointObjDlg EPODlg (MVWind(), &RF(), *_pIL, _lLastId, Pkt);

		EPODlg.Show (Centre);
		if (!EPODlg.Result()) return false;

		if (!EPODlg.GetIdent (ID)) 
			return false;		// kein ID eingegegeben

		_lLastId = ID;			// letzten ID merken
		EPODlg.GetPunkt (Pkt);
	}
	
// Punkt in der DB setzen
OBJGEOMETRIE OG;

	INITSTRUCT (OG, OBJGEOMETRIE);

	OG.lONr = -1L;				// noch keine ObjNummer
	OG.lIdent = ID;
	OG.iFlags = OGNewObject|OGForceGeometry;
	OG.lCnt = 1;
	OG.iKCnt = 0;
	OG.pdblX = &Pkt.X();
	OG.pdblY = &Pkt.Y();
        
	DEX_ModObjGeometrie (OG); 
	
// UniqueIdent vergeben
long lUIMCode = DEX_GetUniqueIdentMCode();

	if (lUIMCode != -1L) { 	
	TARGETMERKMAL gm;

		memset (&gm, '\0', sizeof (TARGETMERKMAL));
		gm.dwSize = sizeof(TARGETMERKMAL);
		gm.lTarget = (LPARAM)OG.lONr;		// ObjektNummer
		gm.lMCode = lUIMCode;			// MCode
		gm.imaxLen = MCODESIZE;
		gm.pMText = new char [MCODESIZE+1];
		gm.iTTyp = TT_Objekt;
		if (gm.pMText != NULL) {
			wsprintf (gm.pMText, 
				  ResString (ResID (IDS_UIFORMAT, &RF()), 20),
				  OG.lONr);
			DEX_ModTextMerkmal (gm);
		}
		DELETE (gm.pMText);
	}
	DEX_RePaint ();

return true;
}


// Löschen des ausgewählten Objektes ------------------------------------------
bool EditObjExtension :: DeletePointObj (void)
{
	if (_pSRO == NULL) return false;
	if (_pSRO -> ONr() == -1L) {
		DELETE (_pSRO);
		return false;	// kein Objekt gefunden
	}

#if !defined(WIN32)		// nur unter 16Bit nachfragen, da sonst Undo
MessBox mb (ResString (ResID (IDS_OBJDELCAPTION, &RF()), 20), 
	    ResString (ResID (IDS_OBJDELQUERY, &RF()), 140), MVWind());

	mb.SetType (ExclamationIcon | YesNoButtons);
	switch (mb.Show()) {
	case YesReply:
		break;

	case NoReply:		// das war wohl nichts
		DELETE (_pSRO);
		return false;
	}
#endif // !WIN32


Rectangle RepaintRc = _pSRO -> oldR();

#if defined(WIN32)
LPUNDOREDOMODIFYOBJECT pIUndo = NULL;

	BeginUndoForDelPoint (_pSRO -> ONr(), &pIUndo);
	DEX_DeleteObjectEx (_pSRO -> ONr());	// Objekt löschen (mit Undo)
	EndoUndoForPoint (pIUndo);
#else
	DEX_DeleteObject (_pSRO -> ONr());		// Objekt löschen
#endif // WIN32
	InflateRect ((RECT *)&RepaintRc, 3, -3);
	DEX_RePaintRectWait (RepaintRc);

	DELETE (_pSRO);

return true;
}


// Editieren der Koordinaten des ausgewählten Objektes ------------------------
bool EditObjExtension :: EditPointObj (void)
{
	if (_pSRO == NULL) return false;
	if (_pSRO -> ONr() == -1L) {
		DELETE (_pSRO);
		return false;	// kein Objekt gefunden
	}

Point newPt = _pSRO -> actPt();
long lONr = _pSRO -> ONr();
Rectangle RepaintRc = _pSRO -> oldR();

	if (_pIL == NULL) {
		DELETE (_pSRO);
		return false;			// keine DB eröffnet
	}

// in DB-Koordinaten konvertieren
COORDCONVERT CC;
Punkt Pkt;
Rectangle CRc = MVWind() -> CanvasRect();

	newPt.Y() = CRc.Top() - CRc.Bottom() - newPt.Y();

	CC.lpPt = (POINT *)&newPt;
	CC.lpPkt = (long *)&Pkt;
	DEX_DCtoOC (CC);

	if (EditPointObj (lONr, Pkt)) {
	// neu zeichnen 
		InflateRect ((RECT *)&RepaintRc, 3, -3);
		DEX_RePaintRectWait (RepaintRc);

		RepaintRc = _pSRO -> newR();
		InflateRect ((RECT *)&RepaintRc, 3, -3);
		DEX_RePaintRectWait (RepaintRc);
	}

	DELETE (_pSRO);		// jetzt freigeben

return true;
}


bool EditObjExtension :: EditPointObj (long lONr, Punkt &Pkt, HWND hWnd)
{
OBJGEOMETRIE OG;

	INITSTRUCT(OG, OBJGEOMETRIE);
	OG.lONr = lONr;
	OG.lIdent = -1L;
	OG.lCnt = 1;
	OG.iKCnt = 0;
	OG.pdblX = &Pkt.X();
	OG.pdblY = &Pkt.Y();
	DEX_GetObjGeometrie (OG);

EditPointObjDlg EPODlg (MVWind(), &RF(), *_pIL, OG.lIdent, Pkt);
long lIdent;
short iFlag = 0;

	EPODlg.Show (Centre);
	if (!EPODlg.Result()) return false;	// abgebrochen

bool fChangeIdent = (EPODlg.GetIdent (lIdent) && lIdent != OG.lIdent) ? true : false;
Punkt newPkt (0, 0);
bool fChangeObj = (EPODlg.GetPunkt (newPkt) && (Pkt.X() != newPkt.X() || Pkt.Y() != newPkt.Y())) ? true : false;
	
	OG.lIdent = lIdent;
	OG.pdblX = &newPkt.X();
	OG.pdblY = &newPkt.Y();

#if defined(WIN32)
LPUNDOREDOMODIFYOBJECT pIUndo = NULL;

	if (fChangeIdent || fChangeObj) {
	Rectangle rcn = _pSRO -> newR();
	Rectangle rco = _pSRO -> oldR();
	RECT rcU;

		UnionRect (&rcU, (RECT *)&rco, (RECT *)&rcn);
		BeginUndoForModPoint (OG, &pIUndo, &rcU);
	}
#endif // WIN32

	if (fChangeIdent) {	
	// Identifikator modifizieren
	MODOBJIDENT MOI;

		MOI.dwSize = sizeof (MODOBJIDENT);
		MOI.lONr = lONr;
		MOI.lNewIdent = lIdent;
		if (hWnd)
			DEXOR_ModObjectIdent (hWnd, MOI);
		else
			DEX_ModObjectIdent (MOI);
		_lLastId = lIdent;	// letzten Ident merken
		iFlag++;
	}

	if (fChangeObj) {
		OG.iFlags = OGModObject|OGForceGeometry;
		DEX_ModObjGeometrie (OG);
		iFlag++;
	}

#if defined(WIN32)
// Undo beenden
	EndoUndoForPoint (pIUndo);
#endif // WIN32

return iFlag;
}


// wegspeichern eines Punktes nach einer Verschiebung -------------------------
bool EditObjExtension :: SavePointObj (void)
{
	if (_pSRO == NULL) return false;

pWindow pW = MVWind();

	pW -> Draw (_pSRO);	// ausblenden des Rechteckes
		
Point newPt = _pSRO -> newPos();		// jetziger MittelPunkt
Rectangle RepaintRc = _pSRO -> oldR();

// in DB-Koordinaten konvertieren
COORDCONVERT CC;
Punkt Pkt;
Rectangle CRc = pW -> CanvasRect();

	newPt.Y() = CRc.Top() - CRc.Bottom() - newPt.Y();

	CC.lpPt = (POINT *)&newPt;
	CC.lpPkt = (long *)&Pkt;
	DEX_DCtoOC (CC);

OBJGEOMETRIE OG;

	INITSTRUCT (OG, OBJGEOMETRIE);

	OG.lONr = _pSRO -> ONr();
	OG.lIdent = 0L;			// Ident ohne Änderung
	OG.iFlags = OGModObject|OGForceGeometry;
	OG.lCnt = 1;
	OG.iKCnt = 0;
	OG.pdblX = &Pkt.X();
	OG.pdblY = &Pkt.Y();

#if defined(WIN32)
LPUNDOREDOMODIFYOBJECT pIUndo = NULL;
Rectangle rc = _pSRO -> newR();
RECT rcU;

	UnionRect (&rcU, (RECT *)&RepaintRc, (RECT *)&rc);
	BeginUndoForModPoint (OG, &pIUndo, &rcU);

	DEX_ModObjGeometrie (OG);

	EndoUndoForPoint (pIUndo);	// Undo beenden
#else
	DEX_ModObjGeometrie (OG);
#endif // WIN32

// neu zeichnen 
	InflateRect ((RECT *)&RepaintRc, 3, -3);
	DEX_RePaintRectWait (RepaintRc);

	RepaintRc = _pSRO -> newR();
	InflateRect ((RECT *)&RepaintRc, 3, -3);
	DEX_RePaintRectWait (RepaintRc);
	
	DELETE (_pSRO);		// jetzt freigeben

return true;
}


// UndoRedoFunktionen ---------------------------------------------------------
#if defined(WIN32)

HRESULT EditObjExtension :: BeginUndoForModPoint (
		OBJGEOMETRIE &rOG, IUndoRedoModifyObject **ppIUndo, LPCRECT pcRc)
{
ResString resUndo (ResID (IDS_UNDOMODIFYPOINT, &RF()), 120);
char cbBuffer[64];

	wsprintf (cbBuffer, resUndo.Addr(), rOG.lONr);
	DEX_BeginUndoLevel (cbBuffer);

LPTRIASXTENSIONSITE pXtsnSite = NULL;
HRESULT hr = GetXtensionSite (&pXtsnSite);

	if (SUCCEEDED(hr)) {
		hr = pXtsnSite -> CreateInstance (NULL, CLSID_UndoRedoObject,
							IID_IUndoRedoModifyObject, (LPVOID *)ppIUndo);
		pXtsnSite -> Release();
		if (SUCCEEDED(hr)) 
			hr = (*ppIUndo) -> Init (rOG.lONr, &rOG, pcRc);

		if (FAILED(hr)) {
			(*ppIUndo) -> Release();
			*ppIUndo = NULL;
		}
	}

return NOERROR;
}

HRESULT EditObjExtension :: BeginUndoForDelPoint (
		LONG lONr, IUndoRedoModifyObject **ppIUndo)
{
ResString resUndo (ResID (IDS_UNDODELETEPOINT, &RF()), 120);
char cbBuffer[64];

	wsprintf (cbBuffer, resUndo.Addr(), lONr);
	DEX_BeginUndoLevel (cbBuffer);

return NOERROR;
}

HRESULT EditObjExtension :: EndoUndoForPoint (IUndoRedoModifyObject *pIUndo)
{
	if (NULL != pIUndo)
		DEX_AddUndoRedo (pIUndo);
	DEX_EndUndoLevel();

return NOERROR;
}

#endif // WIN32
