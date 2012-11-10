// Behandeln der Events vom Floating-TextobjektMenu ---------------------------
// File: TEXTMENU.CXX
//
// 09.03.2001 09:57:18
//		BUGFIX: Menupunkt 'IDM_CREATETEXTOBJ' ist jetzt immer aktiv (auch, wenn 
//				existierender Text getroffen wurde

#include "triaspre.hxx"

#include "schrift.hxx"
#include "edittext.hxx"

#include "triasres.h"

#include <funcs02.h>
#include <funcs03.h>
#include <FormatString.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <Com/CStructHelper.h>
#include <strdup.hxx>

#include "ExtMain3.hxx"

extern HINSTANCE hInstance;
extern HPALETTE hPalette;

#define MCODESIZE	40

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(UndoRedoModifyObject);
DefineSmartInterface(UndoRedoDeleteText);
DefineSmartInterface(UndoRedoCreateText);
DefineSmartInterface(UndoRedoObjectFeature);

///////////////////////////////////////////////////////////////////////////////
//
extern class CLegendeClientWindow *pLegende;	// Legende

// Hier kommen die Menuevts vom Floatingmenu an -------------------------------
bool IrisWind::HandleTextObjectMenu (unsigned int iItem) 
{
bool fResult = false;

	switch (iItem) {
	case IDM_CREATETEXTOBJ:		// neues Textobjekt bilden
		EditTextObject (this, -1L);
		fResult = true;
		break;

	case IDM_DELETETEXTOBJ:		// Textobjekt rauslöschen
		if (m_lTextONr != -1L) {
			DeleteTextObject (m_lTextONr, m_rcTextSel);
			fResult = true;
		}
		break;

	case IDM_EDITTEXTOBJ:		// Text editieren
		if (m_lTextONr != -1L) {
			EditTextObject (this, m_lTextONr);
			fResult = true;
		}
		break;

	case IDM_CREATEBREL:		// Begleitrelation aufbauen
		if (m_lTextONr != -1L) {
			if (ObjInfoListe.Count() >= 1) { // jetzt das letzte aktive
			CEierUhr Wait (this);
			long lSelObj = ObjInfoListe.GetSelectedObject();

				if (lSelObj != -1L) {
				MODRELATIONEX MR;

					INITSTRUCT(MR, MODRELATIONEX);
					MR.lPONr = lSelObj;
					MR.lSONr = m_lTextONr;
					MR.lRCode = 0;
					MR.iRTyp = RTBegleitO;
					MR.fUndo = TRUE;
					if (EC_OKAY == DEX_ModifyRelation(MR))
						fResult = true;
				}
			}
		}
		break;

	case IDM_DELETEBREL:		// Begleitrelation auflösen
		if (m_lTextONr != -1L) {
		CEierUhr Wait (this);
		DatenBasisObjekt &rDBO = DBO();
		long lAssocON = AssociatedObjekt (m_lTextONr, NULL);

			if (lAssocON != 0L) {
			DELRELATIONEX DR;

				INITSTRUCT(DR, DELRELATIONEX);
				DR.lPONr = lAssocON;
				DR.lSONr = m_lTextONr;
				DR.lRCode = 0;
				DR.iRTyp = RTBegleitO;
				DR.fUndo = TRUE;
				if (EC_OKAY == DEX_DeleteRelation(DR))
					fResult = true;
			}
		}
		break;

	case IDM_ADDTOLEGEND:
		if (m_lTextONr != -1L) {
			DEX_AddObjectToLegend (m_lTextONr);
			DEX_RefreshLegend();	
			DEX_RepaintLegend();
			fResult = true;
		}
		break;
	}
	m_lTextONr = -1L;
	return fResult;
}

// FloatingMenu aufbauen ------------------------------------------------------
bool IrisWind::TrackTextObjectMenu (Point Pt, long ONr, Rectangle Box) 
{
// TextObjektNummer merken
	m_lTextONr = ONr;
	m_rcTextSel = Box;
	m_ptTextPos = Pt;

	if (-1L != ONr) {
	HMENU hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (TEXTOBJMENU));

		if (hMenu == NULL) 	// irgend was stimmt nicht
			return true;

	// Menu generieren
		m_hTextMenu = GetSubMenu (hMenu, 0);		// SubMenu holen

	Rectangle Rc = CanvasRect();

		Pt.Y() = Rc.Top() - Rc.Bottom() - Pt.Y();	// in WindowsKoord umrechnen
		ClientToScreen (Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
		TrackPopupMenu (m_hTextMenu, 0, Pt.X(), Pt.Y(), 
				0, Handle (API_CLIENT_HWND), NULL);

	// wieder aufräumen
		m_hTextMenu = NULL;
		DestroyMenu (hMenu);
		return true;
	} else {
	// kein Objekt getroffen
		PostEvent (WM_COMMAND, IDM_CREATETEXTOBJ);	// Text sofort erzeugen
		return false;
	}
}

// MenuHilfsFunktionen --------------------------------------------------------
inline bool CheckMenu (HMENU hMenu, WORD id) 
	{ return CheckMenuItem (hMenu, id, MF_BYCOMMAND+MF_CHECKED) ? true : false; }
inline bool UnCheckMenu (HMENU hMenu, WORD id) 
	{ return CheckMenuItem (hMenu, id, MF_BYCOMMAND+MF_UNCHECKED) ? true : false; }
inline bool EnableMenu (HMENU hMenu, WORD id) 
	{ return EnableMenuItem (hMenu, id, MF_BYCOMMAND+MF_ENABLED) ? true : false; }
inline bool GrayMenu (HMENU hMenu, WORD id)
	{ return EnableMenuItem (hMenu, id, MF_BYCOMMAND+MF_GRAYED) ? true : false; }

inline Bool AdjustCheckMark (HMENU hMenu, WORD id, Bool iFlag) 
{
	if (iFlag) 
		return CheckMenu (hMenu, id);
	return UnCheckMenu (hMenu, id);
}

inline Bool AdjustEnableStatus (HMENU hMenu, WORD id, Bool iFlag) 
{
	if (iFlag) 
		return EnableMenu (hMenu, id);
	return GrayMenu (hMenu, id);
}

///////////////////////////////////////////////////////////////////////////////
// Initialisieren des Menus entsprechend den Eigenschaften des gefundenen Textobjektes 
bool IrisWind::InitTextObjectMenu (void) 
{
	if (m_hTextMenu) {
	// nur wenn Menu aktiv ist
	bool isValidON = m_lTextONr != -1L;
	bool isSubText = isValidON ? isDBSubTextObjekt (m_lTextONr) : false;
	bool isSubTextInd = isValidON ? isDBSubTextObjektInd (m_lTextONr) : false;

		AdjustEnableStatus (m_hTextMenu, IDM_CREATETEXTOBJ, true);		// #HK010309: immer aktiv!
		AdjustEnableStatus (m_hTextMenu, IDM_DELETETEXTOBJ, isValidON && !isSubText);
		AdjustEnableStatus (m_hTextMenu, IDM_EDITTEXTOBJ, isValidON);

	// verwendet jetzt letztes aktives ORFenster: #HK950218
	HPROJECT hPrText = DEX_GetObjectProject(m_lTextONr);
	bool fCreateBRel = DEX_GetTRiASDataSourceEx(hPrText) && isValidON && !isSubText && ObjInfoListe.Count() >= 1;
	
		if (fCreateBRel) {
		INT_PTR lONrAct = ObjInfoListe.GetSelectedObject();
		HPROJECT hPrAct = DEX_GetObjectProject(lONrAct);

			if (hPrText != hPrAct)
				fCreateBRel = false;	// andere Datenquelle
		}
		AdjustEnableStatus (m_hTextMenu, IDM_CREATEBREL, fCreateBRel);
		AdjustEnableStatus (m_hTextMenu, IDM_DELETEBREL, isSubText && !isSubTextInd);
		AdjustEnableStatus (m_hTextMenu, IDM_ADDTOLEGEND, NULL != pLegende && isValidON);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Modifizieren des Textes eines Textobjektes
bool DatenBasisObjekt::ChangeTextObjectText (LONG lONr, LPCSTR pcNewText)
{
CONrTable tabObj (Shapes().ObjNumTree());

	if (tabObj.Find (&lONr)) {
	ExtShapeObjectONrLock l(tabObj);

		if (l) {
		char *pText = ((SchriftObjekt *)((ExtShapeObject *)l)) -> ChangeText ((char *)pcNewText);

			DELETE_OBJ(pText);
			return true;
		}
	}
	return false;
}

namespace {
// dafür sorgen, daß ein Fenster vollständig auf dem Bildschirm zu sehen ist
	bool FitWindowToScreen(Window *pW)
	{
	HWND hWnd = pW->Handle(API_WINDOW_HWND);
	Rectangle rc;

		GetWindowRect(hWnd, (RECT *)&rc);

	bool fChanged = false;
	Rectangle rcNew (rc);
	int iX = ::GetSystemMetrics(SM_CXFULLSCREEN);
	int iY = ::GetSystemMetrics(SM_CYFULLSCREEN);
	
		if (rc.Bottom() > iY) {
			rcNew.Bottom() = iY;
			rcNew.Top() = rcNew.Bottom() - abs(rc.Height());
			fChanged = true;
		}
		if (rc.Right() > iX) {
			rcNew.Right() = iX;
			rcNew.Left() = rcNew.Right() - rc.Width();
			fChanged = true;
		}

		if (fChanged)
			SetWindowPos(hWnd, NULL, rcNew.Left(), rcNew.Top(), 0, 0, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
		return fChanged;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Editieren eines TextObjektes 
inline void Clear (TEXTGEOMETRIEEX *pData) { DELETE_VEC(pData->pText); }
typedef CStructEx<TEXTGEOMETRIEEX> CTextGeometryEx;

inline void Clear (MODOBJIDENT *pData) {}
typedef CStructEx<MODOBJIDENT> CModObjIdent;

bool IrisWind::EditTextObject (pWindow pW, long lONr) 
{
string strText;
Punkt ptPkt;		// TextKoordinate 
long lIdent = 0;
TextObjTyp rgToTyp = TOT_TEXT;

	if (0 != lONr && -1 != lONr) {
	// Objekt editieren
		if (!GetTextObject (lONr, ptPkt, lIdent, strText, rgToTyp))
			return false;
	} else {
	// Objekt neu erzeugen
		ptPkt = DCtoOC (m_ptTextPos);

#if defined(_KOORD_ISDOUBLE)
	KoOrd dX = ptPkt.GetX();
	KoOrd dY = ptPkt.GetY();
	CoordTrans *pCTF = DBO().pCT();

		pCTF -> Transform (&dX, &dY);
		ptPkt = Punkt (dX, dY);
#endif // _KOORD_ISDOUBLE

		lIdent = DEX_GetLastIdent();
	}

// bei 'Editieren' nur die Idents der Datenquelle dieses Objektes
HPROJECT hPr = (0 != lONr && -1 != lONr) ? DEX_GetObjectProject(lONr) : NULL;
EditTextObjektDialog ETODlg (pW, strText.size() > 0 ? strText.c_str() : NULL, ptPkt, lIdent, DBO().pCT(), hPr);
ResString resCap ((0 != lONr && -1 != lONr) ? IDS_MODIFY_TEXT : IDS_CREATE_TEXT, 128);

// Dialog am Mausklick positionieren
Point pt (m_ptTextPos);
Dimension dim (ETODlg.GetSize());

	pt.Y() -= dim.Height();
	ETODlg.ChangePosition(pt);
	FitWindowToScreen(&ETODlg);

// Dialog anzeigen
	ETODlg.SetCaption (resCap);
	ETODlg.SetEditRO(TOT_TEXTINDOBJPROP == rgToTyp ? TRUE : FALSE);
	ETODlg.Show();
	if (!ETODlg.Result()) 
		return false;		// abgebrochen

// Text geändert, wegschreiben
char *newText = ETODlg.GetNewText();
long lNewIdent = -1L;

	if (lONr == -1) {
		ETODlg.GetIdent (lIdent);
		lONr = CreateTextObject (ptPkt, lIdent, newText);	// neu erzeugen
		DEX_RePaintObject (lONr);							// zum ersten mal zeichnen
		DEX_SetLastIdent (lIdent);
		return RePaintTextObject (lONr);
	} 
	
// bestehendes Textobjekt wurde modifiziert
BOOL fModIdent = ETODlg.GetIdent (lNewIdent);

	if (!fModIdent)
		lNewIdent = lIdent;

BOOL fModPt = ETODlg.GetPunkt (ptPkt);

KoOrd dX = ptPkt.GetX();
KoOrd dY = ptPkt.GetY();
CTextGeometryEx GS;

	GS.lONr = lONr;
	GS.iObjTyp = (TOT_TEXT == rgToTyp) ? OT_TEXT : OT_LABEL;
	GS.lIdent = lNewIdent;
	GS.iFlags = OGModObject|OGForceGeometry;
#if defined(_KOORD_ISDOUBLE)
	GS.iFlags |= OGConverted;
#endif // defined(_KOORD_ISDOUBLE)
	GS.pText = StrDupF(newText);
	GS.iKCnt = strlen (newText);
	GS.lCnt = 1;
	GS.pdblX = &dX;
	GS.pdblY = &dY;

	{
	// mit Undo speichern
	ResString resUndo (IDS_UNDOMODIFYTEXT, 64);
	char cbBuffer[64];

		wsprintf (cbBuffer, resUndo.Addr(), lONr);
		DEX_BeginUndoLevel (cbBuffer);

	WUndoRedoModifyObject Undo;
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoModifyObject, Undo.ppv());

		if (SUCCEEDED(hr))
			hr = Undo -> Init (lONr, (OBJGEOMETRIE *)&((TEXTGEOMETRIEEX &)GS), NULL);

	// wenn Ident geändert wurde, dann nachziehen
		if (fModIdent) {
		CModObjIdent MOI;

			MOI.lONr = lONr;
			MOI.lNewIdent = lNewIdent;
			MOI.iMode = MODIDENT_TEXT|MODIDENT_ADDTOVIEW;
			DEX_ModObjectIdent (MOI);
			lIdent = lNewIdent;
		}
		if (!DEX_ModObjGeometrie ((TEXTGEOMETRIEEX &)GS)) {	// Geometrie und Text wegschreiben
			DEX_CancelUndoLevel (true);		// UndoRecording abbrechen
			return false;
		}
		if (hr == NOERROR)
			DEX_AddUndoRedo (Undo.detach());	// Geometrie/Text-Undo

		DEX_EndUndoLevel();	// Undo abschließen
	}

	DEX_RePaintObject (lONr);							// zum ersten mal zeichnen
	DEX_SetLastIdent(lIdent);
	return RePaintTextObject (lONr, newText);
}

bool IrisWind::RePaintTextObject (long lONr, LPCSTR pcNewText)
{
// neu zeichnen
CONrTable tabObj (DBO().Shapes().ObjNumTree());

	if (tabObj.Find (&lONr)) {
	ExtShapeObjectONrLock l(tabObj);

		if (l) {
			SetShouldRedraw (false);

			if (NULL != pcNewText) {
			Rectangle oldBox = l -> BoundingBox();
			char *oldText = ((SchriftObjekt *)((ExtShapeObject *)l)) -> ChangeText (const_cast<char *>(pcNewText));

				if (NULL != oldText) {
				Rectangle rcT = l -> BoundingBox();

					RePaintRect (oldBox.Union (rcT));
					delete oldText;
				} else
					RePaint();
			} else {
			Rectangle rcT = l -> BoundingBox();

				RePaintRect (rcT);
			}
		} else
			return false;
	}
	return true;
}

bool IrisWind::GetTextObject (long lONr, Punkt &rPt, long &lIdent, string &rStrText, TextObjTyp &rToTyp)
{
CTextGeometryEx GS;

	GS.dwSize = sizeof(OBJSTATISTIK);
	GS.lONr = lONr;
#if defined(_KOORD_ISDOUBLE)
	GS.iFlags = OGConverted;
#endif // _KOORD_ISDOUBLE
	if (!DEX_GetObjStatistik (GS))
		return false;

	TX_TRY(GS.pText = new char [GS.iKCnt+1]);
	if (NULL == GS.pText) return false;

KoOrd dX, dY;

	GS.pdblX = &dX;
	GS.pdblY = &dY;
	GS.dwSize = sizeof(TEXTGEOMETRIEEX);
	if (!DEX_GetObjGeometrie ((TEXTGEOMETRIEEX &)GS)) 
		return false;

	rStrText = GS.pText;

	rPt.SetX(*(KoOrd *)GS.pdblX);
	rPt.SetY(*(KoOrd *)GS.pdblY);
	lIdent = GS.lIdent;		// Ident merken
	rToTyp = GS.fIndObjProp ? TOT_TEXTINDOBJPROP : TOT_TEXT;

	return true;
}

// Löschen eines Textobjektes aus der GeoDB -----------------------------------
void IrisWind::DeleteTextObject (long lONr, Rectangle R) 
{
ResString resUndo (IDS_UNDODELETETEXT, 64);
char cbBuffer[64];

	wsprintf (cbBuffer, resUndo.Addr(), lONr);
	DEX_BeginUndoLevel (cbBuffer);

// Textobjekt selbst zwischenspeichern
WUndoRedoDeleteText Undo;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteText, Undo.ppv());

	if (SUCCEEDED(hr))
		hr = Undo -> Init (lONr, (RECT *)&R);

DELETEOBJECTRECT DOR;

	INITSTRUCT(DOR, DELETEOBJECTRECT);
	DOR.lONr = lONr;
	DOR.fUndo = true;
	if (DEX_DeleteObjectRect(DOR)) {	// Objekt aus DB löschen
		SetShouldRedraw (false);
		RePaintRect (R);		// Rechteck neuzeichnen
		if (hr == NOERROR)
			DEX_AddUndoRedo (Undo.detach());
		DEX_EndUndoLevel();
	} else
		DEX_CancelUndoLevel (true);	// UndoRecording abbrechen
}


// Generieren eines neuen Textobjektes ----------------------------------------
long IrisWind::CreateTextObject (Punkt ptPkt, long lIdent, const char *pcText, TextObjTyp rgToTyp) 
{
	if (lIdent == -1L) return -1L;

CTextGeometryEx GS;
KoOrd dX = ptPkt.GetX();
KoOrd dY = ptPkt.GetY();

	GS.lONr = -1L;
	GS.lIdent = lIdent;
	GS.iObjTyp = (rgToTyp == TOT_TEXT) ? OGText : OGLabel;
	GS.iFlags = OGNewObject|OGAddToView;
#if defined(_KOORD_ISDOUBLE)
	GS.iFlags |= OGConverted;
#endif // defined(_KOORD_ISDOUBLE)
	GS.lCnt = 1;
	GS.pdblX = &dX;
	GS.pdblY = &dY;
	GS.iKCnt = strlen(pcText);
	GS.pText = const_cast<char *>(pcText);
	GS.fIndObjProp = (rgToTyp == TOT_TEXT) ? FALSE : TRUE;
	if (!DEX_ModObjGeometrie((TEXTGEOMETRIEEX &)GS)) {
		GS.pText = NULL;		// doppeltes delete verhindern
		return -1L;
	}

	GS.pText = NULL;		// doppeltes delete verhindern

	ptPkt.SetX(dX);
	ptPkt.SetY(dY);

// Undo/Redo vorbereiten
	{
	ResString resUndo (IDS_UNDOCREATETEXT, 64);

		DEX_BeginUndoLevel (resUndo.Addr());

	WUndoRedoCreateText Undo;
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoCreateText, Undo.ppv());

		if (SUCCEEDED(hr) && S_OK == Undo -> Init (GS.lONr))
			DEX_AddUndoRedo (Undo.detach());
	}
	GenerateUniqueIdent (GS.lONr);
	return GS.lONr;
}

bool IrisWind::GenerateUniqueIdent (long lONr)
{
// UniqueIdent vergeben
long lUIMCode = DEX_GetUniqueIdentMCodeEx(DEX_GetObjectProject(lONr));
string strUIdent;

	if (lUIMCode != 0L) {
		Format (strUIdent, ResString (IDS_UIFORMAT, 20), lONr);
		WriteTextMerkmal (TT_Objekt, lONr, lUIMCode, const_cast<char *>(strUIdent.c_str()));
	}

// Undo/Redo vorbereiten
	if (lUIMCode != 0L) {
	WUndoRedoObjectFeature Undo;
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature, Undo.ppv());

		if (SUCCEEDED(hr) && S_OK == Undo -> Init (lONr, lUIMCode, strUIdent.c_str(), NULL)) 
			DEX_AddUndoRedo (Undo.detach());
	}
	DEX_EndUndoLevel();
	return true;
}

// Doppeln eines TextObjektes -----------------------------------------------
bool IrisWind::CopyText (long lONr, Punkt &rPkt, bool fRO, long *plNewONr) 
{
	if (0 == lONr || -1 == lONr) 
		return false;

long lIdent = 0L;
string strText;
TextObjTyp rgToTyp = TOT_TEXT;
Punkt pktOld;

	if (!GetTextObject (lONr, pktOld, lIdent, strText, rgToTyp))
		return false;

// Ident abfragen, wenn unverändert, dann bleibt lIdent gleich
long lNewONr = CreateTextObject (rPkt, lIdent, strText.c_str(), rgToTyp);	// neu erzeugen

	if (plNewONr) {
		CopyFeatures(lNewONr, lONr);
		*plNewONr = lNewONr;
	}
	DEX_RePaintObject (lNewONr);		// zum ersten mal zeichnen
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// sämtliche Objekteigenschaften (außer UIdent) an ein anderes Objekt übernehmen
namespace {
// eine Objekteigenschft an ein anderes Objekt kopieren
	typedef struct tagCOPYFEATURES {
		INT_PTR lONrSrc;
		INT_PTR lClassDest;
		INT_PTR lONrDest;
		INT_PTR lMCodeUIdent;
		INT_PTR lMCodeOldUIdent;
		INT_PTR lMCodeGuid;
	} COPYFEATURES;

	extern "C"
	BOOL CALLBACK CopyFeatureToDestObject(long lMCode, BOOL iNotLast, void *pData)
	{
	COPYFEATURES *pCF = reinterpret_cast<COPYFEATURES *>(pData);

		if (lMCode == pCF -> lMCodeOldUIdent || lMCode == pCF -> lMCodeGuid)
			return TRUE;						// OldUIdent/Guid nicht überschreiben
		if (lMCode == pCF -> lMCodeUIdent)
			lMCode = pCF -> lMCodeOldUIdent;	// UIdent wird zum OldUIdent

	char cbBuffer[_MAX_PATH];

		if (ReadTextMerkmal(TT_Objekt, pCF -> lONrSrc, lMCode, cbBuffer, sizeof(cbBuffer))) 
			WriteTextMerkmal(TT_Objekt, pCF -> lONrDest, lMCode, cbBuffer);
		return TRUE;
	}
}

bool IrisWind::CopyFeatures(INT_PTR lONrDest, INT_PTR lONrSrc)
{
#if defined(_DEBUG)
// die Objekte müssen einen identischen Satz von Objekteigenschaften besitzen
// (TRiAS-Projekte: identische Datenquelle, nicht TRiAS-Projekte: identische Objektklasse)
HPROJECT hPrSrc = DEX_GetObjectProject(lONrSrc);
HPROJECT hPrDest = DEX_GetObjectProject(lONrDest);

	if (DEX_GetTRiASDataSourceEx(hPrDest) && DEX_GetTRiASDataSourceEx(hPrSrc)) 
		_ASSERTE(hPrSrc == hPrDest);
	else
		_ASSERTE(DEX_GetObjIdentEx(lONrSrc) == DEX_GetObjIdentEx(lONrDest));
#endif // defined(_DEBUG)

COPYFEATURES CF;
HPROJECT hPr = DEX_GetObjectProject(lONrDest);

	CF.lONrDest = lONrDest;
	CF.lClassDest = DEX_GetObjIdentEx(lONrDest);
	CF.lONrSrc = lONrSrc;
	CF.lMCodeUIdent = DEX_GetUniqueIdentMCodeEx(hPr);
	CF.lMCodeOldUIdent = DEX_GetOldUniqueIdentMCodeEx(hPr);
	CF.lClassDest = DEX_GetObjGuidMCode(CF.lClassDest);

ENUMLONGKEY ELK;

	ELK.eKey = lONrSrc;
	ELK.eFcn = (ENUMLONGKEYPROC)CopyFeatureToDestObject;
	ELK.ePtr = &CF;
	return DEX_EnumObjektMerkmale(ELK);
}

