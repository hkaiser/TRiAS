// Behandeln der Events vom Floating-TextobjektMenu ---------------------------
// File: TEXTMENU.CXX

#include "triaspre.hxx"

#include "schrift.hxx"
#include "edittext.hxx"

#include "triasres.h"

#if defined(WIN32)
#include <funcs03.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#endif

extern HINSTANCE hInstance;
extern HPALETTE hPalette;

#define MCODESIZE	40

static long NEAR locONr = -1L;
static HMENU NEAR hSubMenu = NULL;
static Rectangle NEAR locR;
static Point NEAR locPt;

extern class CLegendeWindow *pLegende;	// Legende

bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags = 0);

// Hier kommen die Menuevts vom Floatingmenu an -------------------------------
bool IrisWind :: HandleTextObjectMenu (unsigned int iItem) 
{
bool fResult = false;

	switch (iItem) {
	case IDM_CREATETEXTOBJ:		// neues Textobjekt bilden
		EditTextObject (this, -1L);
		fResult = true;
		break;

	case IDM_DELETETEXTOBJ:		// Textobjekt rauslöschen
		if (locONr != -1L) {
			DeleteTextObject (locONr, locR);
			fResult = true;
		}
		break;

	case IDM_EDITTEXTOBJ:		// Text editieren
		if (locONr != -1L) {
			EditTextObject (this, locONr);
			fResult = true;
		}
		break;

	case IDM_CREATEBREL:		// Begleitrelation aufbauen
		if (locONr != -1L) {
			if (ObjInfoListe.Count() >= 1) { // jetzt das letzte aktive
			CEierUhr Wait (this);
			long lSelObj = ObjInfoListe.GetSelectedObject();

				if (lSelObj != -1L) {
					PutRelation (DBO().DB().DBDesc(), lSelObj, locONr, 0L, BRELA);
#if defined(WIN32)
				LPUNDOREDOCREATEOBJECTRELATION pIUndo = NULL;
				HRESULT hr = UndoCreateInstance (IID_IUndoRedoCreateObjectRelation,
								 (LPVOID *)&pIUndo);

					if (SUCCEEDED(hr) && 
					    pIUndo -> Init (lSelObj, locONr, 0L, BRELA) == NOERROR) 
					{
						DEX_AddUndoRedo (pIUndo);
					}
					if (pIUndo) pIUndo -> Release();
#endif
				}
			}
			fResult = true;
		}
		break;

	case IDM_DELETEBREL:		// Begleitrelation auflösen
		if (locONr != -1L) {
		CEierUhr Wait (this);
		HPROJECT hDB = DBO().DB().DBDesc();
		long lAssocON = AssociatedObjekt (hDB, locONr);

			if (lAssocON != 0L) {
				DelRelation (hDB, labs(lAssocON), locONr, 0L, BRELA);
#if defined(WIN32)
			LPUNDOREDODELETEOBJECTRELATION pIUndo = NULL;
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteObjectRelation,
							 (LPVOID *)&pIUndo);

				if (SUCCEEDED(hr) && 
				    pIUndo -> Init (labs(lAssocON), locONr, 0L, BRELA) == NOERROR) 
				{
					DEX_AddUndoRedo (pIUndo);
				}
				if (pIUndo) pIUndo -> Release();
#endif
			}
			fResult = true;
		}
		break;

	case IDM_ADDTOLEGEND:
		if (locONr != -1L) {
			DEX_AddObjectToLegend (locONr);
			DEX_RefreshLegend();	
			DEX_RepaintLegend();
			fResult = true;
		}
		break;
	}
	locONr = -1L;

return fResult;
}

// FloatingMenu aufbauen ------------------------------------------------------
void IrisWind :: TrackTextObjectMenu (Point Pt, long ONr, Rectangle Box) 
{
HMENU hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (TEXTOBJMENU));

	if (hMenu == NULL) 	// irgend was stimmt nicht
		return;

// TextObjektNummer merken
	locONr = ONr;
	locR = Box;
	locPt = Pt;

// Menu generieren
	hSubMenu = GetSubMenu (hMenu, 0);		// SubMenu holen

Rectangle Rc = CanvasRect();

	Pt.Y() = Rc.Top() - Rc.Bottom() - Pt.Y();	// in WindowsKoord umrechnen
	ClientToScreen (Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
	TrackPopupMenu (hSubMenu, 0, Pt.X(), Pt.Y(), 
			0, Handle (API_CLIENT_HWND), NULL);

// wieder aufräumen
	hSubMenu = NULL;
	DestroyMenu (hMenu);
}

// MenuHilfsFunktionen --------------------------------------------------------
inline Bool CheckMenu (HMENU hMenu, WORD id) 
	{ return CheckMenuItem (hMenu, id, MF_BYCOMMAND+MF_CHECKED); }
inline Bool UnCheckMenu (HMENU hMenu, WORD id) 
	{ return CheckMenuItem (hMenu, id, MF_BYCOMMAND+MF_UNCHECKED); }
inline Bool EnableMenu (HMENU hMenu, WORD id) 
	{ return EnableMenuItem (hMenu, id, MF_BYCOMMAND+MF_ENABLED); }
inline Bool GrayMenu (HMENU hMenu, WORD id)
	{ return EnableMenuItem (hMenu, id, MF_BYCOMMAND+MF_GRAYED); }

inline Bool AdjustCheckMark (HMENU hMenu, WORD id, Bool iFlag) 
{
Bool iResult;

	if (iFlag) iResult = CheckMenu (hMenu, id);
	else	   iResult = UnCheckMenu (hMenu, id);

return iResult;
}

inline Bool AdjustEnableStatus (HMENU hMenu, WORD id, Bool iFlag) 
{
Bool iResult;

	if (iFlag) iResult = EnableMenu (hMenu, id);
	else	   iResult = GrayMenu (hMenu, id);

return iResult;
}


// Initialisieren des Menus entsprechend den Eigenschaften des gefundenen 
// Textobjektes 
bool IrisWind :: InitTextObjectMenu (void) 
{
	if (hSubMenu) {
	// nur wenn Menu aktiv ist
	Bool isValidON = locONr != -1L;
	Bool isSubText = isValidON ? isDBSubTextObjekt (DBO().DB().DBDesc(), locONr) : FALSE;
	Bool isSubTextInd = isValidON ? isDBSubTextObjektInd (DBO().DB().DBDesc(), locONr) : FALSE;

		AdjustEnableStatus (hSubMenu, IDM_CREATETEXTOBJ, !isValidON);
		AdjustEnableStatus (hSubMenu, IDM_DELETETEXTOBJ, 
			isValidON && !isSubText);
		AdjustEnableStatus (hSubMenu, IDM_EDITTEXTOBJ, isValidON);
//		AdjustEnableStatus (hSubMenu, IDM_MODIDTEXTOBJ, isValidON);
	// verwendet jetzt letztes aktives ORFenster: #HK950218
		AdjustEnableStatus (hSubMenu, IDM_CREATEBREL, 
			isValidON && !isSubText && ObjInfoListe.Count() >= 1);
		AdjustEnableStatus (hSubMenu, IDM_DELETEBREL, 
			isSubText && !isSubTextInd);
		AdjustEnableStatus (hSubMenu, IDM_ADDTOLEGEND, 
			pLegende != NULL && isValidON);

		return true;
	}

return false;
}

///////////////////////////////////////////////////////////////////////////////
// Modifizieren des Textes eines Textobjektes
bool IrisWind::ChangeTextObjectText (LONG lONr, LPCSTR pcNewText)
{
CTable tabObj (DBO().Shapes().ObjNumTree());

	if (tabObj.Find (&lONr)) {
	ExtShapeObjectLock l(tabObj);

		if (l) {
		char *pText = ((SchriftObjekt *)((ExtShapeObject *)l)) -> ChangeText ((char *)pcNewText);

			DELETE(pText);
			return true;
		}
	}
	return false;
}

// Editieren eines TextObjektes -----------------------------------------------
bool IrisWind :: EditTextObject (pWindow pW, long lONr) 
{
char *oldText = NULL;
Punkt ptPkt;		// TextKoordinate 
long lIdent;
TEXTGEOMETRIE GS;
	
	memset (&GS, '\0', sizeof(TEXTGEOMETRIE));
	GS.dwSize = sizeof(TEXTGEOMETRIE);
	GS.iObjTyp = OT_TEXT;
	GS.lCnt = 1;

TextObjTyp ToTyp = TOT_TEXT;

	if (lONr != -1L) {
	GeoDB &rDB = DBO().DB();
	
		if (rDB.ReadText (lONr, oldText, ToTyp) != EC_OKAY)
			return false;
	
		if (ToTyp == TOT_TEXTIND) {
		// indirektes Textobjekt, Text vom Bezugsobjekt holen
		long MCode = *(long *)oldText;
		long lAssoc = AssociatedObjekt (rDB.DBDesc(), lONr);
	
			if (lAssoc == 0) {
				db_error (WC_NOASSOCOBJ, RC_EditTextObj);
				return false;	// Fehler: kein Bezugsobjekt
			}
			DELETE (oldText);
			if (GetMiText (rDB.DBDesc(), MCode, labs(lAssoc), OBL_OLD, &oldText) != EC_OKAY)
				return false;
		}

		GS.lONr = lONr;
		GS.lIdent = 0;
		GS.pdblX = &ptPkt.X();
		GS.pdblY = &ptPkt.Y();
			
		if (!DBO().QueryObjGeometrie ((OBJGEOMETRIE *)&GS)) return false;
		
		lIdent = GS.lIdent;		// Ident merken
	} else {
	// Objekt neu erzeugen
		ptPkt = DCtoOC (locPt);
		lIdent = GetLastIdent();
	}
	
EditTextObjektDialog ETODlg (pW, oldText, ptPkt, lIdent, DBO().pCT());

	ETODlg.SetEditRO(TOT_TEXTINDOBJPROP == ToTyp ? TRUE : FALSE);
	ETODlg.Show();

// Speicher bereinigen
	DELETE (oldText);

	if (!ETODlg.Result()) return false;		// abgebrochen

// Text geändert, wegschreiben
char *newText = ETODlg.GetNewText();
long lNewIdent = -1L;

	if (lONr == -1) {
	// Ident abfragen, wenn unverändert, dann bleibt lIdent gleich
		ETODlg.GetIdent (lIdent);
		lONr = CreateTextObject (ptPkt, lIdent, newText);	// neu erzeugen
		DEX_RePaintObject (lONr);		// zum ersten mal zeichnen
		SetLastIdent (lIdent);
		return true;
	} 
	
	DBO().DB().SetDirty();

// bestehendes Textobjekt wurde modifiziert
bool fModIdent = ETODlg.GetIdent (lNewIdent);

	if (!fModIdent)
		lNewIdent = lIdent;

	GS.lONr = lONr;
	GS.lIdent = lNewIdent;
	GS.iFlags = OGModObject|OGForceGeometry;
	GS.pText = newText;
	GS.iKCnt = strlen (newText);
	GS.pdblX = &ptPkt.X();
	GS.pdblY = &ptPkt.Y();

#if defined(WIN32)	// mit Undo
ResString resUndo (IDS_UNDOMODIFYTEXT, 64);
char cbBuffer[64];

	wsprintf (cbBuffer, resUndo.Addr(), lONr);
	DEX_BeginUndoLevel (cbBuffer);

LPUNDOREDOMODIFYOBJECT pIUndo = NULL;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoModifyObject,
				 (LPVOID *)&pIUndo);

	if (SUCCEEDED(hr))
		hr = pIUndo -> Init (lONr, (OBJGEOMETRIE *)&GS, NULL);

	if (ETODlg.GetPunkt (ptPkt)) {		// Koordinaten sind neu
	// Geometrie und Text wegschreiben
		if (!DBO().ModObjGeometrie ((OBJGEOMETRIE *)&GS)) {
			DEX_CancelUndoLevel (true);	// UndoRecording abbrechen
			return false;
		}
	}
	else if (DBO().DB().WriteText (lONr, newText, (TOT_TEXTINDOBJPROP == ToTyp) ? TRUE : FALSE) != EC_OKAY) {
	// nur Text wegschreiben (fehlgeschlagen)
		DEX_CancelUndoLevel (true);	// UndoRecording abbrechen
		return false;
	}
	if (hr == NOERROR)
		DEX_AddUndoRedo (pIUndo);	// Geometrie/Text-Undo

// wenn Ident geändert wurde, dann nachziehen
	if (fModIdent) {
		DBO().ModIdent (lONr, lNewIdent, lIdent, MODIDENT_TEXT|MODIDENT_ADDTOVIEW);
		lIdent = lNewIdent;
	}

	DEX_EndUndoLevel();	// Undo abschließen
#else // WIN32
	if (ETODlg.GetPunkt (ptPkt)) {		// Koordinaten sind neu
	// Geometrie und Text wegschreiben
		if (!DBO().ModObjGeometrie ((OBJGEOMETRIE *)&GS)) 
			return false;
	}
	else if (DBO().DB().WriteText (lONr, newText) != EC_OKAY) 
		return false;		// nur Text wegschreiben (fehlgeschlagen)

// wenn Ident geändert wurde, dann nachziehen
	if (fModIdent) {
		DBO().ModIdent (lONr, lNewIdent, lIdent, MODIDENT_TEXT|MODIDENT_ADDTOVIEW);
		lIdent = lNewIdent;
	}
#endif // WIN32

	SetLastIdent (lIdent);

// neu zeichnen
CTable tabObj (DBO().Shapes().ObjNumTree());

	if (tabObj.Find (&lONr)) {
	ExtShapeObjectLock l(tabObj);

		if (l) {
		Rectangle oldBox = l -> BoundingBox();

			oldText = ((SchriftObjekt *)((ExtShapeObject *)l)) -> ChangeText (newText);
			if (oldText != NULL) {
			Rectangle rcT = l -> BoundingBox();
				
				RePaintRect (oldBox.Union (rcT));
				delete oldText;
			} else
				RePaint();
		}
	}

	return true;
}


// Löschen eines Textobjektes aus der GeoDB -----------------------------------
void IrisWind :: DeleteTextObject (long lONr, Rectangle R) 
{
#if defined(WIN32)
ResString resUndo (IDS_UNDODELETETEXT, 64);
char cbBuffer[64];

	wsprintf (cbBuffer, resUndo.Addr(), lONr);
	DEX_BeginUndoLevel (cbBuffer);

// Textobjekt selbst zwischenspeichern
LPUNDOREDODELETETEXT pIUndo = NULL;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteText,
				 (LPVOID *)&pIUndo);
//HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//		CLSCTX_INPROC_SERVER, IID_IUndoRedoDeleteText,
//		(LPVOID *)&pIUndo);

	if (SUCCEEDED(hr))
		hr = pIUndo -> Init (lONr, (RECT *)&R);

	if (DBO().DeleteObjekt (lONr, true)) {	// Objekt aus DB löschen
		RePaintRect (R);		// Rechteck neuzeichnen

		if (hr == NOERROR)
			DEX_AddUndoRedo (pIUndo);
		DEX_EndUndoLevel();
	} else
		DEX_CancelUndoLevel (true);	// UndoRecording abbrechen

	if (pIUndo) pIUndo -> Release();
#else
MessBox mb (ResString (IDS_OBJDELCAPTION, 20), 
	    ResString (IDS_OBJDELQUERY, 150), this);

	mb.SetType (ExclamationIcon | YesNoButtons);
	switch (mb.Show()) {
	case YesReply:
		{
			DEX_DeleteObject (lONr);	// Objekt aus DB löschen
			RePaintRect (R);		// Rechteck neuzeichnen
		}
		break;

	case NoReply:
	// das war wohl nichts
		break;
	}
#endif
}


// Generieren eines neuen Textobjektes ----------------------------------------
long IrisWind :: CreateTextObject (Punkt ptPkt, long lIdent, char *pText) 
{
	if (lIdent == -1L) return -1L;
	
long newON = -1L;

// Ident zu aktueller Sicht hizufügen
	DBO().DB().SetDirty();
	if (!DBO().Idents().AddNewIdent (lIdent, hPalette, ANI_AddToView, MODIDENT_TEXT)) 
		return -1L;
		
// PunktObjekt in der DB anlegen
	if (PutTextObject (DBO().DB().DBDesc(), &newON, lIdent, DBO().DB().TOMCode(), 
			   ptPkt.X(), ptPkt.Y(), pText, FALSE) != EC_OKAY)
		return -1L;

// PunktObjekt im Speicher anlegen 
	{
	ExtShapeObjectDCreator DOC (DBO().Shapes());
	ExtShapeObject *pESO;

		if (DBO().GetGI (newON, DOC, &pESO) != EC_OKAY)
			return -1L;
	}

#if defined(WIN32)
// Undo/Redo vorbereiten
ResString resUndo (IDS_UNDOCREATETEXT, 64);

	DEX_BeginUndoLevel (resUndo.Addr());

LPUNDOREDOCREATETEXT pIUndo = NULL;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoCreateText,
				 (LPVOID *)&pIUndo);
//HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//		CLSCTX_INPROC_SERVER, IID_IUndoRedoCreateText,
//		(LPVOID *)&pIUndo);

	if (SUCCEEDED(hr) && pIUndo -> Init (newON) == NOERROR)
	{
		DEX_AddUndoRedo (pIUndo);
	}
	if (pIUndo) pIUndo -> Release();
#endif

// UniqueIdent vergeben
long lUIMCode = DEX_GetUniqueIdentMCode();
char cbBuffer[64];

	if (lUIMCode != 0L) {
		wsprintf (cbBuffer, ResString (IDS_UIFORMAT, 20), newON);
		WriteTextMerkmal (TT_Objekt, newON, lUIMCode, cbBuffer);
	}

#if defined(WIN32)
// Undo/Redo vorbereiten
	if (lUIMCode != 0L) {
	LPUNDOREDOOBJECTFEATURE pIUndo = NULL;
	
		hr = UndoCreateInstance (IID_IUndoRedoObjectFeature,
					 (LPVOID *)&pIUndo);
//		hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//			CLSCTX_INPROC_SERVER, IID_IUndoRedoObjectFeature,
//			(LPVOID *)&pIUndo);

		if (SUCCEEDED(hr) && 
		    pIUndo -> Init (newON, lUIMCode, cbBuffer, NULL) == NOERROR) 
		{
			DEX_AddUndoRedo (pIUndo);
		}
		if (pIUndo) pIUndo -> Release();
	}
	DEX_EndUndoLevel();
#endif

return newON;
}

#if defined(WIN32)
// Doppeln eines TextObjektes -----------------------------------------------
bool IrisWind :: CopyText (long lONr, Punkt &rPkt, bool fRO, long *plNewONr) 
{
	if (0 == lONr) return false;

char *oldText = NULL;
long lIdent = DEX_GetObjIdent (lONr);
TextObjTyp ToTyp;
	
	if (DBO().DB().ReadText (lONr, oldText, ToTyp) != EC_OKAY) {
		DELETE(oldText);
		return false;
	}

	if (ToTyp == TOT_TEXTIND) {
	// indirektes Textobjekt, Text vom Bezugsobjekt holen
	long lMCode = *(long *)oldText;
	long lAssoc = AssociatedObjekt (DBO().DB().DBDesc(), lONr);

		DELETE(oldText);
		if (lAssoc == 0) {
			db_error (WC_NOASSOCOBJ, RC_EditTextObj);
			return false;	// Fehler: kein Bezugsobjekt
		}
		DELETE (oldText);
		if (GetMiText (DBO().DB().DBDesc(), lMCode, labs(lAssoc), OBL_OLD, &oldText) != EC_OKAY)
			return false;
	}

// Ident abfragen, wenn unverändert, dann bleibt lIdent gleich
long lNewONr = CreateTextObject (rPkt, lIdent, oldText);	// neu erzeugen

	DEX_RePaintObject (lONr);		// zum ersten mal zeichnen
	DELETE(oldText);
	
	if (plNewONr) *plNewONr = lNewONr;

return true;
}

#endif // WIN32

