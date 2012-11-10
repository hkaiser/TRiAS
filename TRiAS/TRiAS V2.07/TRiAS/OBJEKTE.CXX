// Routinen fuer DialogFenster ObjektRecherche --------------------------------
// File: OBJEKTE.CXX

#include "triaspre.hxx"

#include "triasres.h"

#if !defined(WIN32)
#include <toolhelp.h>
#else
#include <xtsnguid.h>
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "Strings.h"
#include "menuitem.hxx"
#include "merkedit.hxx"
#include "schrift.hxx"
#include "relobj.hxx"
#include "edittext.hxx"
#include "objowndr.hxx"

#include "oridents.hxx"
#include "oridents.inl"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HelpDisplay *IrisHD;
extern bool DrawTextObjs;			// TextObjekte anzeigen / recherchieren
extern HINSTANCE hInstance;			// Handle dieser Programminstanz

short OTypToBits (ObjTyp iOTyp);

///////////////////////////////////////////////////////////////////////////////
// Konstruktor
ObjektInfo :: ObjektInfo (pWindow pW, DatenBasisObjekt &rDBO, ExtensionList &EL, 
			  short iFlags, CMPONRPROC pProc, DWORD dwData
#if defined(WIN32)
			  , LPUNKNOWN pIUnk
#endif
			  )
#if defined(WIN32)
	    : OwnerDrawDialogWindow (pW, IsWin40() ? ResID(OBJEKTE40) : ResID(OBJEKTE), false),
#else
	    : OwnerDrawDialogWindow (pW, ResID(OBJEKTE), false),
#endif
	      ObjektMenu (OBJMENU),		// Menu
	      m_rEL(EL), m_rDBO(rDBO)
{
	m_hWnd = Handle (API_WINDOW_HWND);	// unser HWND
	
	m_pKurzInfo = NULL;		// erstmal NullSetzen
	m_pOITree = NULL;
	m_ptWantedPos = Point (-1, -1);	// unbestimmte Anfangsposition
	ChangePosition (m_ptWantedPos);

	m_lActObj = -1L;		// erstmal kein aktiviertes Objekt
	m_ulActCount = 0;		// keine selektierten Objekte
	m_iActObjTypes = 0;

	m_C = Color (RED);		// Markierungsfarbe setzen
	m_C.Reserved() = 0;		// oberstes Byte sicher Nullsetzen
	
	m_pBuffer = NULL;
	m_pBuffer1 = NULL;

// CheckmarkFlags etc. initialisieren
	m_fToDelete = false;		// Flag, ob dieses Fenster noch angezeigt ist
	m_fHighLighted = false;		// Objekt noch nicht aktiviert

	m_fAreaEFlag = false;
	m_fCentreEFlag = false;
	
	m_fNoBlinking = false;				// erstmal blinken
	m_fSystem = (DEX_QueryMode() & QMShowSysFeatures) ? true : false;		// SystemMerkmale anzeigen
	
	m_fInitExtMenus = false;	// ExtensionMenu's bereits eingehangen
	m_fInitMenuItems = false;	// EinzelMenuPunkte bereits eingehangen

	m_fCmd = false;
		
	m_iFlags = iFlags;		// zusätzliche Flags
	m_pCmpProc = pProc;		// Vergleichsfunktion
	m_dwData = dwData;		// zugehörige Daten
	
	if (m_pCmpProc == NULL && !(iFlags & ROSortObjNr)) {
	// keine externen Vorgaben und nicht nach ObjektNummer sortieren
		m_pCmpProc = (CMPONRPROC)CompareObjs;	// interner Vergleich
		m_dwData = (DWORD)this;
	}
	
// DummyEintrag aus Menu herausnehmen
	ObjektMenu.DeleteItem (IDM_DUMMY);
	ChangeMenu (&ObjektMenu);	// Menu einhängen

// Menupunkt an Systemmenu anhängen
HMENU hSysMenu = ::GetSystemMenu (m_hWnd, false);

	::AppendMenu (hSysMenu, MF_SEPARATOR, 0, (LPSTR)NULL);
	::AppendMenu (hSysMenu, MF_STRING, IDM_REMOVEORWNDS, ResString (IDS_REMOVEORWNDS, 30));

// Menupunkte eines Fensters mit SysMenu entfernen
	::RemoveMenu (hSysMenu, SC_MINIMIZE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_RESTORE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND);

#if defined(WIN32)
	InitializeCriticalSection (&m_CS);

	m_pIObjProp = NULL;
	if (NULL != pIUnk) 
		pIUnk -> QueryInterface (IID_IObjectProperty, (LPVOID *)&m_pIObjProp);

	m_fExistsOP = true;

	m_pDropTgt = NULL;			// Drag'n Drop Support
	m_fIsDropSource = false;
	m_fIsDropTarget = false;
	m_iDropPos = -1;
	m_iDropIndex = -1;
	m_hBr = NULL;
	m_fBrushToDelete = false;

	m_hAccel = NULL;

	m_iCntItems = COUNT_ITEMS;
	m_iCntChars = COUNT_CHARS;
#endif // WIN32
}

// Destruktor -----------------------------------------------------------------
ObjektInfo :: ~ObjektInfo (void) 
{
// QueryClose rufen
	locQueryClose();

	DELETE (m_pKurzInfo);		// ListBox freigeben
	DELETE (m_pOITree);		// ObjInfoItemTree freigeben

// Erweiterungen aus Menu herauslösen
	if (m_rEL.CountLoaded() > 0) {
	HMENU hMenu = GetSubMenu (ObjektMenu.Handle (API_MENU_HMENU), 2);
	CTable r(m_rEL);

		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (!l) continue;
			if (l -> ORMenuHandle() != 0) 	// Menu herauslösen
				RemoveMenu (hMenu, 0, MF_BYPOSITION);
		}
		DrawMenuBar (m_hWnd);
	}
	
	DELETE (m_pBuffer);
	DELETE (m_pBuffer1);

#if defined(WIN32)
	if (m_pIObjProp) 
		m_pIObjProp -> Release();

	RevokeDragDrop();				// DragDrop abmelden
	if (m_fBrushToDelete)
		::DeleteObject (m_hBr);

	DeleteCriticalSection (&m_CS);
#endif // WIN32
}


ObjektInfo *ObjektInfo :: CreateInstance (pWindow pW, DatenBasisObjekt &rDBO,
					  ExtensionList &EL, 
					  ObjFeld &OF, short iFlags, 
					  CMPONRPROC pProc, DWORD dwData
#if defined(WIN32)
					  , LPUNKNOWN pIUnk
#endif
					  )
{
ObjektInfo *pOInfo = new ObjektInfo (pW, rDBO, EL, iFlags, pProc, dwData
#if defined(WIN32)
				     , pIUnk
#endif // WIN32
				     );

	if (pOInfo == NULL || !pOInfo -> FInit (OF)) {
		DELETE (pOInfo);
		return NULL;
	}
	
return pOInfo;
}


bool ObjektInfo :: FInit (ObjFeld &OF)
{
// Baum initialisieren
	if (m_pOITree == NULL) {
		m_pOITree = new ObjInfoItemTree();
		if (m_pOITree == NULL) {
			db_error (EC_NOMEMORY, RC_ctObjInfo);
			return false;
		}
	}
	if (GenerateListBox() != EC_OKAY) 
		return false;	// OwnerDrawMultiSelListBox generieren
	InitExtensionMenus();	// Erweiterungen einhängen
	InitMenuItems();	// zusätzliche MenuItems einhängen

#if defined(_NEWORMENU)
	m_hAccel = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_OBJMENUACCEL));
	if (NULL == m_hAccel) return false;
#endif // _NEWORMENU

// interne ZeichenPuffer anlegen
	if (m_pBuffer == NULL) {
		m_pBuffer = new char [_MAX_PATH];
		m_pBuffer1 = new char [_MAX_PATH];
		if (m_pBuffer == NULL || m_pBuffer1 == NULL)
			return false;
	}
	
// ListBox mit nötigen Info's aus ObjektFeld füllen
bool fAddToList = (m_pOITree -> Count() != 0) ? true : false;
bool fFirst = fAddToList;
long lONr = 0L;

#if defined(WIN32)
// in Win95 evtl. vorher Speicher anfordern
	if (IsWin40() && OF.Count() > 100) {
		::SendMessage (m_pKurzInfo -> LocControl() -> Handle(), LB_INITSTORAGE, 
					   OF.Count(), OF.Count()*64);	// ca. 64 Bytes je Eintrag
	}

// DragDrop initialisieren
	if (FAILED(InitDragDrop()))	return false;
#endif // WIN32

// Objekteigenschaft rücksetzen, die verwendet werden soll
#if defined(WIN32)
	if (!fAddToList) m_rEL.ResetActObjProp();
#endif
	{
	CRing r(OF);

		for (r.First(); r.Valid(); r.Next()) {
		ObjNummerLock l(r);

			TX_ASSERT(NULL != (ObjNummer *)l);

		long lLocONr = l -> _ON;
		HRESULT hr = RetrieveObjInfo (lLocONr);

			if (S_OK == hr && !fFirst) {	// erster Neuzugang
			// die erste Objektnummer merken, die in die Listbox kommt
				lONr = lLocONr;
				fFirst = true;
			}
			if (FAILED(hr)) break;
		}
	}
	m_pOITree -> Optimize();
	if (fAddToList)	return true;	// hier aufhören, wenn nicht erstes FInit
			
// ersten Eintrag aktivieren
	if (fFirst) {
	short iIndex = (short)m_pKurzInfo -> FindItem ((void *)lONr);

		if (iIndex != -1) {
			m_pKurzInfo -> ChangeSelected (iIndex);
			m_pKurzInfo -> SetCaretIndex (iIndex);
		}
	}

	if (lONr == 0) lONr = -1;
	ActivateObj (lONr);	// erstes Objekt aktivieren

// im Baum erstes Element ebenfalls kennzeichnen
	{
	CTable t(OITree());

		if (t.Find (&lONr)) {
		ObjInfoItemLock l (t);
		ObjInfoItem *pOII = (ObjInfoItem *)l;

			TX_ASSERT(NULL != pOII);

			pOII -> isActive (true);
			pOII -> isSelected (true);
			m_ulActCount = 1;
			m_iActObjTypes = pOII -> GetOType();
		}
	}
	if (-1 != lONr) {
		DEXN_ObjectSelected (lONr);
		DEXN_ObjectActivated (lONr);
	}
		
// ListBox anzeigen
	m_pKurzInfo -> LocControl() -> Show (); 
	m_pKurzInfo -> SetFocus();	// Focus auf ListBox setzen              

	return true;
}


// ListBox (Control) generieren -----------------------------------------------
ErrCode ObjektInfo :: GenerateListBox (void) 
{
	if (m_pKurzInfo != NULL) return EC_OKAY;		// bereits generiert
	
HDC hDC = GetDC (m_hWnd);	// hWnd ist Suchschlüssel
TEXTMETRIC tm;

	GetTextMetrics (hDC, &tm);
	ReleaseDC (m_hWnd, hDC);

// benötigte Größe berechnen: Listbox muß COUNT_ITEMS Zeilen mit je COUNT_CHARS Zeichen aufnehmen
Rectangle Rc (Point (0, 0), Point (tm.tmAveCharWidth*m_iCntChars+
				   GetSystemMetrics (SM_CXVSCROLL), 
				   tm.tmHeight*m_iCntItems));
	m_pKurzInfo = new ObjektInfoListBox (this, IDL_OBJEKTE, *m_pOITree);
	if (m_pKurzInfo == NULL) 
		return (ErrCode)db_error (EC_NOMEMORY, RC_ctObjInfo);

	m_pKurzInfo -> LocControl() -> ChangeSize (Dimension (Rc.Right(), Rc.Bottom()));

#if defined(WIN32)
	m_pKurzInfo -> EnableDragDrop();		// Drag'n Drop erlauben
	if (IsWin40()) 
		AdjustWindowRectEx ((RECT *)&Rc, DS_MODALFRAME|WS_POPUP|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU, true, WS_EX_TOOLWINDOW);
	else
		AdjustWindowRectEx ((RECT *)&Rc, WS_POPUP|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU, true, 0);
#else
	AdjustWindowRect ((RECT *)&Rc, WS_POPUP|WS_CAPTION, true);
#endif // WIN32
	ChangeSize (Dimension (Rc.Right()-Rc.Left(), Rc.Bottom()-Rc.Top()));

	m_pKurzInfo -> ChangePosition (Point (0, 0));

return EC_OKAY;
}


// Die Menu's aller geladenen Extensions richtig im lokalen Menu aufnehmen
void ObjektInfo :: InitExtensionMenus (void)
{
	if (m_fInitExtMenus) return;		// schon erledigt
	
	if (m_rEL.CountLoaded() > 0) {
	HMENU hMenu = GetSubMenu (ObjektMenu.Handle(API_MENU_HMENU), 2);

	CTable r(m_rEL);
	short i = 0;
	bool iFirst = false;

		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (!l) continue;
			if (l -> ORMenuHandle() != 0) {		// Menu einhängen
				if (!iFirst) {
			 		EnableMenuItem (ObjektMenu.Handle (API_MENU_HMENU), 2, 
			 				MF_BYPOSITION|MF_ENABLED);
					iFirst = true;
				}
				l -> ORMenuIndex() = i;
				InsertMenu (hMenu, i, MF_POPUP|MF_BYPOSITION,
					    (UINT)l -> ORMenuHandle(), l -> ORMenuString().c_str());
				i++;
			}
		}
		DrawMenuBar (m_hWnd);
	}
	m_fInitExtMenus = true;
}


// Alle zusätzlich installierten Menupunkte aufnehmen -------------------------
void ObjektInfo :: InitMenuItems (void)
{
	if (m_fInitMenuItems) return;	// schon erledigt
	
	if (m_rEL.CountLoaded() == 0 || !m_rEL.hasMIL()) return;

HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);
CRing r (m_rEL.MIL());

	for (r.First(); r.Valid(); r.Next()) {
	MenuItemLock l(r);

		if (!l) continue;
		InstallMenuItem (l -> _iMenuID, l -> _iPopup, l -> _pMenuText);
	}
	m_fInitMenuItems = true;
}


// ----------------------------------------------------------------------------
// InputFocusänderung ---------------------------------------------------------
void EXPORTTRIAS ObjektInfo :: FocusChange (FocusChangeEvt e) 
{
// merken, ob dieses Fenster den Focus hat
	m_fHasFocus = e.gotFocus();

// Notification absetzen
	DEXN_ObjWndFocusChanged (hWnd(), m_fHasFocus ? true : false);
}


// Zusammenstellen der Kurzinformation für ein Objekt ------------------------
char cFVisTyp (ObjTyp iOTyp)
{
	switch (iOTyp) {
	case OT_PUNKT:		return 'P';
	case OT_KANTE:		return 'L';
	case OT_KREIS:
	case OT_FLAECHE:	return 'F';
	case OT_LABEL:
	case OT_TEXT:		return 'T';
	case OT_KO:		return 'K';
	case OT_UNKNOWN:
	default:
		break;
	}

return 'U';
}

char *FormatROString (char *pText, RECHOBJECT &rRO);
short OTypToBits (ObjTyp iOTyp);

namespace {
inline 
bool FMatchScales (long lActScale, long lUpperScale, long lLowerScale)
{
	if (0 != lUpperScale && lActScale < lUpperScale)
		return false;

	if (0 != lLowerScale && lActScale > lLowerScale)
		return false;

	return true;
}
} // namespace

HRESULT EXPORTTRIAS ObjektInfo :: RetrieveObjInfo (long lONr, int iIndex, int *piNewIndex) 
{
CTable t(OITree());

//	TX_ASSERT(IsValidONr(lONr));	// dauert zu lange
	TX_ASSERT(0 < lONr);
	
	if (t.Find (&lONr)) return ResultFromScode(S_FALSE);	// Objekt gibt es schon
	if (!DrawTextObjs && isDBTextObjekt (m_rDBO.DB().DBDesc(), lONr))
		return ResultFromScode(S_FALSE);	// BegleitObjekte nicht anzeigen

long lIdent = m_rDBO.RetrieveIdent(lONr);	// Identifikator bestimmen
ObjTyp iObjType = m_rDBO.RetrieveObjTyp(lONr);	// ObjektTyp bestimmen

// Testen, ob dieses Objekt fraktal entfällt
long lUpperScale = 0L;
long lLowerScale = 0L;

	m_rDBO.RetrieveIdentScaleData (NULL, lIdent, OTypToVTyp(iObjType), &lUpperScale, &lLowerScale);
	if (!FMatchScales (m_rDBO.GetActScale(), lUpperScale, lLowerScale)) 
		return S_FALSE;		// derzeit fraktal ausgeblendet

// Objekteigenschaft bestimmen
bool fExistsForThisObject = true;

#if defined(WIN32)
HRESULT hr = S_FALSE;	// zumindest OKS besorgen

// wenn ObjProp vorgegeben ist, dann diese nutzen, sonst Voreinstellung
	if (m_fExistsOP) {
		if (m_pIObjProp)
			hr = m_pIObjProp -> Eval (lONr, m_pBuffer, _MAX_PATH, NULL);
		else 
			hr = m_rEL.InvokeActObjProp (lONr, m_pBuffer, _MAX_PATH, NULL);
	}

	if (S_OK != GetScode(hr)) 
#endif // WIN32
	{
	// wenn keine OPF gegeben ist, dann IdentKurzText verwenden
	PBD_Ident Id (&(m_rDBO.PbdDB()), lIdent);

		strncpy (m_pBuffer, Id.GetKurzText(), TEXTLEN);	// default: IdKurzText
		m_pBuffer[TEXTLEN] = '\0';
	
		if (S_FALSE != GetScode(hr) && E_FAIL != GetScode(hr))
			m_fExistsOP = false;
		if (E_FAIL == GetScode(hr))
			fExistsForThisObject = false;		// Objprop existiert nicht für dieses Objekt
	}

RECHOBJECT RO;

	INITSTRUCT(RO, RECHOBJECT);
	RO.lONr = lONr;
	RO.lIdent = lIdent;
	RO.lpText = m_pBuffer;
	RO.iTextLen = _MAX_PATH-1;
	RO.iOTyp = (short)iObjType;		// DEX_GetObjectType (lONr);	// ObjektTyp bestimmen
	RO.iFlags = m_iFlags & (ROHideFlags|ROShowHidden);	// voreingestellte Bits setzen

	if (!DEXN_QueryRechObject (RO) && 	// Objekt hat zu rechierenden Ident
	    FormatROString (m_pBuffer1, RO))	// angezeigten Eintrag zusammenstellen
	{
	// und zu ListBox hinzufügen
	Color C, cObjProp;

		if (RO.iOTyp == OT_KO) {	// Komplexobjekte werden DunkelGrün
			C = Color (ColorVal(128), ColorVal(0), ColorVal(0));
			cObjProp = m_fExistsOP ? C : Color(ColorVal(64), ColorVal(0), ColorVal(0));
		} else {
		COLORREF cr = GetSysColor (COLOR_WINDOWTEXT);

			C = (Color &)cr;
			cr = GetSysColor (COLOR_GRAYTEXT);
			cObjProp = fExistsForThisObject ? C : (Color &)cr;
		}

	// zuerst versuchen, den Eintrag in den Baum zu schreiben
		{
		ObjInfoItemCreator OIICr (OITree());
		ObjInfoItem *pOII = ContCreate (OIICr, ObjInfoItem) 
					    (lONr, OTypToBits ((ObjTyp)RO.iOTyp), m_pBuffer1, 
					     !(m_iFlags & ROHideText) ? m_pBuffer : g_cbNil, 
					     C, m_C, cObjProp);

			if (pOII == NULL) {
				db_error (EC_NOMEMORY, RC_RetrieveObjInfo);
				return ResultFromScode(E_OUTOFMEMORY);		// nicht weitermachen
			}
		}	// wegspeichern
		if (OITree().Count() % 100 == 0)
			OITree().Optimize();
		
	// dann die gleiche Info in Listbox speichern
	int iInsertIndex = (iIndex >= (int)GetCount()) ? iIndex : -1;
	string str = string(m_pBuffer1) + m_pBuffer;
	int iNewIndex = m_pKurzInfo -> AddItemEx (lONr, str.c_str(), iInsertIndex);

		if (0 > iNewIndex) {	// nicht eingefügt
		// Fehlermeldung ausgeben
			VMessageBox (GetParent(), IDS_LISTOUTOFSPACECAP, 
						ExclamationIcon|OkayButton, IDS_LISTOUTOFSPACE);
			return E_OUTOFMEMORY;	// Fehler oder kein Platz mehr
		}
		
		if (piNewIndex) *piNewIndex = iNewIndex;	// Index des neuen Eintrages liefern

		DEXN_ObjectAddedToList(lONr);
		return S_OK;	// alles ok
	}

	return S_FALSE;		// nicht in Listbox aufgenommen, trotzdem weitermachen
}


// angezeigten Eintrag zusammenstellen ----------------------------------------
inline char *EOL (char *pT) { return &pT[strlen(pT)]; }

char *FormatROString (char *pText, RECHOBJECT &rRO)
{
char cbBuffer[64];

	if ((rRO.iFlags & ROHideFlags) == 0) {		// alles anzeigen
		if (FAILED(ClassFromIdent (rRO.lIdent, cbBuffer, sizeof(cbBuffer))))
			return NULL;

		wsprintf (pText, "%04ld:%s:%c:", 
				  rRO.lONr, cbBuffer, cFVisTyp ((ObjTyp)rRO.iOTyp)); //, pBuffer);
		return pText;	// alles angezeigt
	}
	
// Einzelne Bestandteile bei Bedarf generieren
	*pText = '\0';
	if (!(rRO.iFlags & ROHideObjNr)) 	// ObjektNummer anzeigen
		wsprintf (EOL(pText), "%04ld:", rRO.lONr);
	if (!(rRO.iFlags & ROHideIdent)) {	// Identifikator anzeigen
		if (FAILED(ClassFromIdent (rRO.lIdent, cbBuffer, sizeof(cbBuffer))))
			return NULL;
		wsprintf (EOL(pText), "%s:", cbBuffer);
	}
	if (!(rRO.iFlags & ROHideObjTyp))	// ObjektTyp anzeigen
		wsprintf (EOL(pText), "%c:", cFVisTyp ((ObjTyp)rRO.iOTyp));

// wenn nichts angezeigt werden soll, dann Eintrag nicht in ListBox nehmen		
	if (strlen(pText) == 0 && rRO.iFlags & ROHideText) 
		return NULL;
	
return pText;
}

// Eventhandler ---------------------------------------------------------------
// Mouse-Click auf ListBox -- Dieses Objekt hervorheben
void ObjektInfo :: ListBoxSel (ControlEvt) 
{
	if (m_pKurzInfo == NULL) return;	// nichts machen

CEierUhr Wait (GetParent()->GetParent());

	m_ulActCount = UpdateActivation();
	UpdateCaption();					// Caption dieses Fensters aktualisieren
}

ULONG ObjektInfo :: UpdateActivation (int iChanged)
{
ULONG ulCountActive = 0L;
int iCurrIndex = m_pKurzInfo -> GetCaretIndex();

	if (iChanged == -1 || iChanged == iCurrIndex) {
	long lONr = GetActiveObj();

		DEXN_ObjectUnSelected (lONr);
		DeActivateObj();	// aktuelles Objekt soll nicht mehr blinken
	}

CTable t (OITree());	// Navigator für ObjInfoItemTree
int iFirstIndex = (iChanged == -1) ? 0 : iChanged; 
int iLastIndex = (iChanged == -1) ? GetCount() : iChanged+1;

// alle selektierten Objekte markieren
	if (iChanged == -1) 
		m_iActObjTypes = 0;
	
bool fDraw = true;	// erstmal immer zeichnen

	GetAsyncKeyState (VK_ESCAPE);	// reset buffer
	
	for (int iIndex = iFirstIndex; iIndex < iLastIndex; iIndex++) {
	long lONr = (long)m_pKurzInfo -> GetItem (iIndex);	// ObjektNummer holen
	bool isSel = m_pKurzInfo -> GetSelection (iIndex);

		if (isSel) {
			TX_ASSERT(ulCountActive < OITree().Count());
			ulCountActive++;
		}

		if (t.Find (&lONr)) {
		ObjInfoItemLock l(t);

			TX_ASSERT(NULL != (ObjInfoItem *)l);
			
		ObjInfoItem *pOII = (ObjInfoItem *)l;
		
			pOII -> isActive (false);		// bei allen rücksetzen
			if (pOII -> isSelected()) {
				if (!isSel) {
				// muß deselektiert werden
					DEXN_ObjectDeActivated (lONr);
					if (iCurrIndex == iIndex) {
						ActivateObj (lONr, fDraw);
						DEXN_ObjectSelected (lONr);
					} else
						DeActivateObj (fDraw, false, lONr);
					pOII -> isSelected (false);
				} else {
					if (iCurrIndex == iIndex) {
					// wenn aktiviertes wieder aktiviert wird
						ActivateObj (lONr, fDraw);
						DEXN_ObjectSelected (lONr);
					} else
						ActivateObj (lONr, fDraw, false);
					m_iActObjTypes |= pOII -> GetOType();
				}
			} else {
				if (isSel) {
				// neu zu selektieren
					if (iCurrIndex == iIndex) {
						ActivateObj (lONr, fDraw);
						DEXN_ObjectSelected (lONr);
					} else
						ActivateObj (lONr, fDraw, false);
					DEXN_ObjectActivated (lONr);
					pOII -> isSelected (true);
					m_iActObjTypes |= pOII -> GetOType();
				}
			}
			if (iCurrIndex == iIndex)
				pOII -> isActive (true);
		}

	// testen, ob Markierung abgebrochen werden soll
		if (GetAsyncKeyState (VK_ESCAPE))
			fDraw = false;		// nicht mehr markieren
	}

// Alle anderen Fenster auffordern, ihre Objekte neu zu markieren
	if (fDraw) DEX_ActivateAllObjects (hWnd());

	return ulCountActive;	// liefert Anzahl der selektiereten Einträge
}


// Mouse-DoppelClick auf ListBox -- vollständige ObjInfo anzeigen
void ObjektInfo :: ListBoxClk (ControlEvt) 
{
	::PostMessage (m_hWnd, WM_COMMAND, IDM_ATTRIBUTE, 0);
//	ShowOIAttribute();
}


// Registrierung einer Verschiebung des Fensters durch den Nutzer
void ObjektInfo :: Move (MoveEvt e) 
{
	m_ptWantedPos = e.NewOrigin();	// neue Position merken
}

///////////////////////////////////////////////////////////////////////////////
// Fenster vergrößert/verkleinert
void ObjektInfo::ReSize (ReSizeEvt e)
{
// Listbox mit anpassen
	m_pKurzInfo -> LocCtrl() -> ChangeSize (e.GetNewSize());

#if defined(WIN32)
// neue Zeichen/ZeilenAnzahl ausrechnen
HWND hCtrl = m_pKurzInfo->Handle(API_WINDOW_HWND);
int iTop = ListBox_GetTopIndex(hCtrl);

	if (LB_ERR != iTop) {
	Rectangle rcBox = m_pKurzInfo->CanvasRect();
	int iHeight = ListBox_GetItemHeight (hCtrl, iTop);
	HDC hDC = ::GetDC (hCtrl);	// hWnd ist Suchschlüssel
	TEXTMETRIC tm;

		::GetTextMetrics (hDC, &tm);
		::ReleaseDC (hCtrl, hDC);

		m_iCntChars = (rcBox.Width() / tm.tmAveCharWidth) + 1;	// sicherheitshalber je eins mehr
		m_iCntItems = (rcBox.Height() / iHeight) + 1;
	}
#endif // WIN32
}

// Routine, die vor Schließen des Dialogfenster gerufen wird ------------------
bool ObjektInfo :: QueryClose (Event) { return locQueryClose(); }

bool ObjektInfo :: locQueryClose (void)
{
#if defined(WIN32)
	EnterCriticalSection (&m_CS);
	if (m_fToDelete) {
		LeaveCriticalSection (&m_CS);
		return true;	// nicht doppelt abarbeiten
	}
#else
	if (m_fToDelete) return true;	// nicht doppelt abarbeiten
#endif

// der Welt mitteilen, daß dieses Fenster nun geschlossen werden soll
CEierUhr Wait (GetParent());

	if (DEXN_RechObjWindowClosed (hWnd())) {
#if defined(WIN32)
		LeaveCriticalSection (&m_CS);
#endif // WIN32
		return false;	// nicht schließen, jemand hat was dagegen
	}

// als letztes passivieren des aktiven Objektes
long lONr = GetActiveObj();

	DEXN_ObjectUnSelected (lONr);
	DeActivateObj();       // evtl. markiertes Objekt deaktivieren

// bevor alles passiviert wird, alle Objekte wieder normal zeichnen
CTable t(OITree());
bool fDraw = true;	// erstmal alles passivieren

	for (t.First(); t.Valid(); t.Next()) {
	ObjInfoItemLock l(t);
	
		TX_ASSERT(NULL != (ObjInfoItem *)l);
		
	ObjInfoItem *pOII = (ObjInfoItem *)l;

		GetAsyncKeyState (VK_ESCAPE);	// reset buffer
		
		if (pOII -> isSelected()) {
			DEXN_ObjectDeActivated (pOII -> ONr());
			DeActivateObj (fDraw, false, pOII -> ONr());
			pOII -> isSelected (false);

		// feststellen, ob abgebrochen werden soll
			if (GetAsyncKeyState (VK_ESCAPE))
				fDraw = false;	// zeichnen abbrechen
		}
	}
	if (fDraw) DEX_ActivateAllObjects (hWnd());	// alle anderen zeichnen neu

	m_fToDelete = true;       // Fenster kann jetzt gelöscht werden

#if defined(WIN32)
	LeaveCriticalSection (&m_CS);
#endif // WIN32

return true;    // auf jeden Fall Fenster schließen
}


// BaumZugriffsfunktionen -----------------------------------------------------
// Liefert SuchSchlüssel für ein ObjektInfo-Fenster
void *GetObjInfoKey (void *pObj) 
{
	return (void *)(& ((ObjektInfo *)pObj) -> m_hWnd);
}


// sonstige Funktionen --------------------------------------------------------
// Positionierung so vornehmen, daß Fenster vollständig sichtbar bleibt
POINT ObjektInfo :: CorrectPosition (DragRectangleObject &DRO) 
{
// Position nur dann neu berechnen, wenn Fenster von Nutzer noch nicht
// explizit an einen bestimmten Platz geschoben wurde
//	if (m_ptWantedPos.X() != -1 || m_ptWantedPos.Y() != -1)
//		return (POINT &)m_ptWantedPos;

Rectangle ObjWRc = WindowRect ();               // ChildFensterGröße
Rectangle Canvas = GetParent() -> CanvasRect ();   // MainFensterGröße

// Variablen, die Lage der Rechtecke zueinander beschreiben
CoOrd b = ObjWRc.Right() - ObjWRc.Left();       // Breite
CoOrd h = ObjWRc.Top() - ObjWRc.Bottom();       // Höhe
CoOrd r = DRO.LowerRight().X() + b;     // Platz rechts
CoOrd u = DRO.LowerRight().Y() - h;     // Platz unten
CoOrd l = DRO.UpperLeft().X() - b;      // Platz links
CoOrd o = DRO.UpperLeft().Y() + h;      // Platz oben
POINT pt;

	if (r <= Canvas.Right()) {
		if (u >= Canvas.Bottom()) {
			pt.x = DRO.LowerRight().X(), pt.y = u;
		} else {
			pt.x = DRO.LowerRight().X(), pt.y = Canvas.Bottom()+h;
		}
	} else if (u >= Canvas.Bottom()) {
		pt.x = Canvas.Right()-b, pt.y = u;
	} else if (o <= Canvas.Top()) {
		pt.x = Canvas.Right()-b, pt.y = DRO.UpperLeft().Y();
	} else if (l >= Canvas.Left()) {
		pt.x = DRO.UpperRight().X()-b, pt.y = Canvas.Top()-h;
	} else {
		pt.x = Canvas.Right()-b, pt.y = Canvas.Bottom()+h;
	}

return pt;
}

// ----------------------------------------------------------------------------
// Funktion, die alle Fenster auffordert, ihre aktivierten Objekte zu zeichnen
bool ObjektInfoListe :: ActivateAllObj (HWND hWnd) 
{
	return Every (RedrawActiveObj, (void *)&hWnd);
}

bool EXPORTTRIAS RedrawActiveObj (void *pObj, void *phWnd) 
{
ObjektInfo *pOI = (ObjektInfo *)pObj;

	if (pOI -> m_fToDelete || *(HWND *)phWnd == pOI -> hWnd()) 
		return true;	// wenn Fenster ungültig ist

CTable t (pOI -> OITree());
bool fDraw = true;	// erstmal alles zeichnen

	for (t.First(); t.Valid(); t.Next()) {
	ObjInfoItemLock l(t);

		TX_ASSERT(NULL != (ObjInfoItem *)l);
		
	ObjInfoItem *pOII = (ObjInfoItem *)l;
	
		if (pOII -> isSelected())	// nur nochmal zeichnen 
			pOI -> ActivateObj (pOII -> ONr(), fDraw, false);
	}

return fDraw;	// weitermachen
}

// Alle bestehenden Objektfenster durchsehen, ob noch alle
// angezeigt werden, wenn nicht, dann löschen
bool ObjektInfoListe::CleanUpDeleted (void)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	register bool toDelete = false;
		{
		ObjektInfoLock l(t);

			if (l && l -> m_fToDelete) 
				toDelete = true;
		}
		if (toDelete) {
			if (!t.Delete()) break;
		} else {
			if (!t.Next()) break;
		}
	}
	return true;
}

// Funktion, die alle Fenster auffordert ihre aktiven Objekte als passiv zu
// zeichnen, intern bleiben sie jedoch aktiv (für 'Blinken')
void ObjektInfoListe :: BlinkAllObj (void) 
{
	if (!IsIconic (__hWndM))	// nur wenn Hauptfenster keine Icone ist
		Every (Blink);			// alle Fenster auffordern, zu blinken
}

// als Aktiv/Inaktiv zeichnen, jedoch nicht passivieren -----------------------
void EXPORTTRIAS Blink (void *pObj) 
{
static bool iActSem = false;
ObjektInfo *pOI = (ObjektInfo *)pObj;

	if (pOI -> m_fToDelete || pOI -> IsDropSource()) 
		return;	// wenn Fenster ungültig ist 

	if (!iActSem) {
		iActSem = true;
		if (pOI -> m_fHighLighted) {
		// blinken - aus, nur wenns nicht zu lange dauert
			if (!pOI -> m_fNoBlinking && !pOI -> m_fCmd)	
				pOI -> DeActivateObj (true, false);
		} else				// blinken - ein
			pOI -> ActivateObj (-1L, true, false);
		iActSem = false;
	}
}


// Hervorheben eines der Objekte ----------------------------------------------
// Flag gibt an, ob m_lActObj (das aktive Objekt) beeinflußt werden soll
// ON gibt die Nummer des zu aktivierenden Objektes an (-1L: wird ignoriert)
void ObjektInfo :: ActivateObj (long ON, bool fDraw, bool Flag, bool iAssoc) 
{
CTable t(m_rDBO.Shapes().ObjNumTree());
long tmpON = ON;
bool handleTO = true;
#if !defined(WIN32)
TIMERINFO TI;

	memset (&TI, '\0', sizeof(TIMERINFO));
	TI.dwSize = sizeof (TIMERINFO);
	TimerCount (&TI);

DWORD dwTicks = TI.dwmsSinceStart;
#else
DWORD dwTicks = GetTickCount();
#endif

	if (ON == -1) {                 // aktiviertes Objekt verwenden
		ON = m_lActObj;
		if (ON == -1)           // kein aktiviertes Objekt
			return;
	}
	
	if (m_fHighLighted && Flag && ON != -1L)
		m_fHighLighted = false;	// Notanker für alle Fälle
		
	if (!m_fHighLighted && t.Find (&ON)) {
	ExtShapeObjectLock l(t);
	bool iFirst = false;

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		
		if (tmpON != -1L && !m_fHighLighted) iFirst = true;
		if (Flag) m_lActObj = ON;

		if (fDraw) {	// nur wenn gezeichnet werden soll
		// auf gesamtem Canvasbereich malen
		Color oldColor;
		Window *pWnd = GetParent();
		ExtShapeObject *pESO = (ExtShapeObject *)l;
		Rectangle rcT = pWnd -> CanvasRect();
		ObjContainer ocT = rcT;
				
			m_rDBO.SetEA (rcT);
			m_rDBO.SetExpOC (ocT);

		// Hervorheben des selektierten Objektes
			pESO -> FullDCInit() = FDC_FullInit | FDC_ActivateOnly;

		// Attribute für dieses Objekt einstellen
		VisInfo *pVI = (VisInfo *)DEX_SetAttributes (ON);           

			if (pVI != NULL) {
			Color ActC = m_C;
	
				switch (pESO -> isTyp()) {
				case OT_PUNKT:	// PunktObjekt
					{
					PunktObjekt *pPO = (PunktObjekt *)pESO;
	
						oldColor = pPO -> ChangeColor (&ActC);
						pWnd -> DrawEx (pPO, (DWORD)&m_rDBO);
						pPO -> ChangeColor (&oldColor);
					}
					break;
	
				case OT_LABEL:
				case OT_TEXT:	// SchriftObjekt (immer ohne Rahmen)
					{
					SchriftObjekt *pSO = (SchriftObjekt *)pESO;
					short oldFrameMode = pSO -> ChangeFrame (0);
	
						oldColor = pSO -> ChangeColor (&ActC);
						pWnd -> DrawEx (pSO, (DWORD)&m_rDBO);
						pSO -> ChangeColor (&oldColor);
						pSO -> ChangeFrame (oldFrameMode);
					}
					break;
	
				case OT_KO:	// KomplexObjekt
					if (iFirst) {
					RelationsObjekt *pRO = (RelationsObjekt *)pESO;
					ObjektListeIterator KOI (pRO -> KO().OL());
					long ONr = KOI.FirstONr();
	
						while (ONr != -1L) {
						// untergeordnete Objekte aktivieren
							ActivateObj (ONr, fDraw, false, true);
							ONr = KOI.NextONr();
						}
					} else
						handleTO = false;
					break;
	
				case OT_UNKNOWN:
					break;
	
				case OT_KANTE:
				case OT_FLAECHE:
				case OT_KREIS:
				default:
					{
					ExtPen actPen (SolidLine, 1, ActC);
					pPen oldPen = pESO -> ChangePen (&actPen);
	
					// Flächen nicht füllen
					Brush Hollow(HollowBrush);
					pBrush oldBrush = pESO -> ChangeBrush (&Hollow);
	
						pWnd -> DrawEx (pESO, (DWORD)&m_rDBO);
						pESO -> ChangeBrush (oldBrush);            
						pESO -> ChangePen (oldPen);
					}
					break;
				}
				pESO -> FullDCInit() = FDC_ActivateOnly;
			}
			
		// Attribute wieder rücksetzen
		RESETATTRDATA RAD;

			RAD.lONr = ON;
			RAD.pVI = pVI;
			DEX_ResetAttributes (&RAD);

		// nachsehen, ob Textobjekt dranhängt
			if (iAssoc && handleTO) {
			ErrInstall EI (EC_DELRECORD);	// für Objektlöschen
			ErrInstall EI2 (EC_INVADDR);	// für temporäre Objekte
			long AssocON = labs (AssociatedObjekt (m_rDBO.DB().DBDesc(), ON));

				if (AssocON != 0) {
				short iBits = OTypToBits ((ObjTyp)DEX_GetObjectType (AssocON));

					if (m_rDBO.Idents().toPaint (m_rDBO.RetrieveIdent(AssocON), iBits)) 
						ActivateObj (AssocON, fDraw, false, false);
				}
			}
		}
			
	// Zeit stoppen, die gebraucht wurde, um alles zu markieren
		if (iFirst) {
#if !defined(WIN32)
			TimerCount (&TI);
			dwTicks = TI.dwmsSinceStart - dwTicks;
#else
			dwTicks = GetTickCount() - dwTicks;
#endif
			if (dwTicks > MAXHIGHLIGHTTIME) 
				m_fNoBlinking = true;	// nicht mehr blinken
			else
				m_fNoBlinking = false;	// blinken
		}
		if (tmpON == -1L && !Flag) m_fHighLighted = true;
	}
}


// ----------------------------------------------------------------------------
// Wieder löschen der Hervorhebung bei Objekt locON, 
// wenn Flag == true, dann Objekt gleichzeitig passivieren
void ObjektInfo :: DeActivateObj (bool fDraw, bool Flag, long locON, bool iAssoc) 
{
CTable t(m_rDBO.Shapes().ObjNumTree());
long tmpON;

	if (locON == -1) tmpON = m_lActObj;
	else tmpON = locON;

// wenn nichts mehr aktiv ist, dann raus
	if (tmpON == -1L) return;

// bei Bedarf passivieren
	if (Flag) m_lActObj = -1L;

#if !defined(WIN32)
TIMERINFO TI;

	memset (&TI, '\0', sizeof(TIMERINFO));
	TI.dwSize = sizeof (TIMERINFO);
	TimerCount (&TI);

DWORD dwTicks = TI.dwmsSinceStart;
#else
DWORD dwTicks = GetTickCount();
#endif

	if (!t.Find (&tmpON)) return;	// unbekanntes Objekt

ExtShapeObjectLock l(t);

	TX_ASSERT(NULL != (ExtShapeObject *)l);

	if ((!Flag && locON != -1L) || m_fHighLighted) // ||
//			   (Flag && l -> isTyp() == OT_KO))) 	// über Zeitmessung abgefangen
	{
		if (fDraw) {
		// auf gesamtem Canvasbereich malen
		Window *pWnd = GetParent();
		ExtShapeObject *pESO = (ExtShapeObject *)l;
		Rectangle rcT = pWnd -> CanvasRect();
		ObjContainer ocT = rcT;
				
			m_rDBO.SetEA (rcT);
			m_rDBO.SetExpOC (ocT);

		// Attribute für dieses Objekt einstellen
			pESO -> FullDCInit() = FDC_FullInit | FDC_ActivateOnly;

		VisInfo *pVI = (VisInfo *)DEX_SetAttributes (tmpON);

			if (NULL != pVI) {
				switch (pESO -> isTyp()) {
				case OT_PUNKT:
				// Punktobjekte nur neu malen
					pWnd -> DrawEx (pESO, (DWORD)&m_rDBO);
					break;
	
				case OT_LABEL:
				case OT_TEXT:
					{
					SchriftObjekt *pSO = (SchriftObjekt *)pESO;
					short oldFrameMode = pSO -> ChangeFrame (0);
	
						pWnd -> DrawEx (pSO, (DWORD)&m_rDBO);
						pSO -> ChangeFrame (oldFrameMode);
					}
					break;
					
				case OT_KO:
					if (Flag) {
					RelationsObjekt *pRO = (RelationsObjekt *)pESO;
					ObjektListeIterator KOI (pRO -> KO().OL());
					long ONr = KOI.FirstONr();
	
						while (ONr != -1L) {
							DeActivateObj (fDraw, false, ONr, true);
							ONr = KOI.NextONr();
						}
					}
					break;
	
				case OT_UNKNOWN:
					break;	// do nothing
	
				default:
				case OT_KANTE:
				case OT_FLAECHE:
				case OT_KREIS:
					{
					// Flächen nicht füllen
					Brush Hollow(HollowBrush);
					pBrush oldBrush = pESO -> ChangeBrush (&Hollow);
					
						pWnd -> DrawEx (pESO, (DWORD)&m_rDBO);	// zeichnen
						pESO -> ChangeBrush (oldBrush);		// wieder herstellen
					}
					break;
				}
				pESO -> FullDCInit() = FDC_NoInit;
			}
			
		// Attribute wieder rücksetzen
		RESETATTRDATA RAD;

			RAD.lONr = tmpON;
			RAD.pVI = pVI;
			DEX_ResetAttributes (&RAD);

		// nachsehen, ob TextObjekt dranhängt
			if (iAssoc) {
			ErrInstall EI (EC_DELRECORD);	// für Objektlöschen
			ErrInstall EI2 (EC_INVADDR);	// für temporäre Objekte
			long AssocON = labs(AssociatedObjekt (m_rDBO.DB().DBDesc(), tmpON));

				if (AssocON != 0) {
				short iBits = OTypToBits ((ObjTyp)DEX_GetObjectType (AssocON));

					if (m_rDBO.Idents().toPaint (m_rDBO.RetrieveIdent(AssocON), iBits)) 
						DeActivateObj (fDraw, false, AssocON, false);
				}
			}
		}	// fDraw
					
	// wenn passivieren zu lange dauert, dann in Zukunft 
	// Blinken abschalten
		if (!Flag) {
#if !defined(WIN32)
			TimerCount (&TI);
			dwTicks = TI.dwmsSinceStart - dwTicks;
#else
			dwTicks = GetTickCount() - dwTicks;
#endif
			if (dwTicks > MAXHIGHLIGHTTIME)
				m_fNoBlinking = true;
			else
				m_fNoBlinking = false;			
		}
	}
	if (locON == -1L) m_fHighLighted = false;
}

// Memberfunktionen für ObjektInfoListe ---------------------------------------
// Konstruktor und Destruktor
ObjektInfoListe :: ObjektInfoListe (void) 
		 : CTree (GetObjInfoKey, HWNDCmp)
{
	m_hLastActiveWnd = NULL;
}

ObjektInfoListe :: ~ObjektInfoListe (void) 
{
	EveryDelete();
}

void EXPORTTRIAS ObjektInfoListe :: UserDelete (void *pItem)  
{
ObjektInfo *pOI = (ObjektInfo *)pItem;

	if (pOI -> hWnd() == m_hLastActiveWnd)
		m_hLastActiveWnd = NULL;
	pOI -> ~ObjektInfo();
}

HWND ObjektInfoListe :: SetLastActive (HWND hWnd)
{
HWND hOldWnd = m_hLastActiveWnd;

	m_hLastActiveWnd = hWnd;
	return hOldWnd;
}

int HWNDCmp (void *pItem1, void *pItem2)
{
	return *(HWND *)pItem1 - *(HWND *)pItem2;
}

long ObjektInfoListe :: GetSelectedObject (HWND hWnd) 
{
CTable t(*this);

	if (hWnd == 0) hWnd = m_hLastActiveWnd;

	if (hWnd != 0) {
	// ein bestimmtes Fenster fragen
		if (t.Find ((void *)&hWnd)) {
		ObjektInfoLock l(t);

			if (l) return l -> GetActiveObj();
			else return -1L;
		} else
			return -1L;
	}

// ansonsten normaler Algorithmus
	if (Count() == 1 && t.First()) {
	// nur ein Fenster da
	ObjektInfoLock l(t);

		if (l) return l -> GetActiveObj();
		else return -1L;
	}

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && l -> m_fHasFocus) 	// nur wenn Focus da ist
			return l -> GetActiveObj();
	}
	
	if (Count() && t.First()) {
	// mehrere Fenster da aber keines hat Focus
	ObjektInfoLock l(t);

		if (l) return l -> GetActiveObj();	// erstes Fenster auswerten
	}

return -1L;
}


long ObjektInfoListe :: GetAllSelectedObjects (long *plObj)
{
	TX_ASSERT(NULL != plObj);

#if defined(_DEBUG)
CTable tDebug(*this);
long lDebugCnt = 0;

	for (tDebug.First(); tDebug.Valid(); tDebug.Next()) {
	ObjektInfoLock l(tDebug);

		TX_ASSERT(NULL != (ObjektInfo *)l);
		TX_ASSERT(0 < l -> GetActiveObj());

		lDebugCnt++;
	}
	TX_ASSERT(TIsValidAddress(plObj, sizeof(LONG)*lDebugCnt, true));	// writeable!
#endif // _DEBUG

// wenn Feld NULL ist, dann wieder raus
	if (NULL == plObj) return 0L;

// ansonsten ObjektNummern kopieren
CTable t(*this);
long lCnt = 0;

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		TX_ASSERT(NULL != (ObjektInfo *)l);

		plObj[lCnt] = l -> GetActiveObj();
		lCnt++;
	}

return lCnt;
}


extern "C" 
inline bool EnumSelectedObjectsCallback (bool (*pFcn)(long, bool, void *), 
					 long Key, bool iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Key, iFlag, pData);
}

bool ObjektInfoListe :: EnumSelectedObjects (bool (*pFcn)(long, bool, void *), 
					     void *pData, HWND hWnd)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	long ONr = 0;
	ObjektInfoLock l(t);
	bool iNotLast = t.Next();

		TX_ASSERT(NULL != (ObjektInfo *)l);

		if (hWnd != 0 && l -> hWnd() != hWnd)
			continue; 
		if (l -> EnumSelectedObjects (pFcn, pData) == false)
			return false;
	}

return true;
}


bool ObjektInfo :: EnumSelectedObjects (bool (*pFcn)(long, bool, void *), 
					void *pData)
{
CTable t (OITree());

	for (t.First(); t.Valid(); ) {
	long lONr = -1L;
	bool iNotLast;

		{
		ObjInfoItemLock l(t);

			TX_ASSERT(NULL != (ObjInfoItem *)l);
			
			iNotLast = t.Next();
			if (!l -> isSelected()) continue;
			
			lONr = l -> ONr();
		} // Lock aufheben


		if (EnumSelectedObjectsCallback (pFcn, lONr, 
						 iNotLast, pData) == false)
			return false;
	}

return true;
}

extern "C" 
inline bool EnumSelectedObjectsCallbackEx (bool (*pFcn)(long, DWORD, void *), 
					 long Key, DWORD dwData, void *pData)
{
	return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(Key, dwData, pData);
}

bool ObjektInfoListe :: EnumSelectedObjectsEx (bool (*pFcn)(long, DWORD, void *), 
				void *pData, DWORD dwData, HWND hWnd)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	long ONr = 0;
	ObjektInfoLock l(t);
	bool iNotLast = t.Next();

		TX_ASSERT(NULL != (ObjektInfo *)l);

		if (hWnd != 0 && l -> hWnd() != hWnd)
			continue; 
		if (l -> EnumSelectedObjectsEx (pFcn, pData, dwData) == false)
			return false;
	}

return true;
}


bool ObjektInfo :: EnumSelectedObjectsEx (bool (*pFcn)(long, DWORD, void *), 
					  void *pData, DWORD dwData)
{
CTable t (OITree());

	for (t.First(); t.Valid(); t.Next()) {
	long lONr = -1L;
	DWORD dwOType = 0;

		{
		ObjInfoItemLock l(t);

			TX_ASSERT(NULL != (ObjInfoItem *)l);
			
		// ist Objekt selektiert ?
			if (!l -> isSelected()) continue;

		// stimmt ObjektTyp ?
			dwOType = l -> GetOType();
			if (!(dwOType & dwData)) continue;
							
			lONr = l -> ONr();
		} // Lock aufheben


		if (EnumSelectedObjectsCallbackEx (
				pFcn, lONr, dwOType, pData) == false)
			return false;
	}

return true;
}

extern "C" 
inline bool EnumAllObjectsCallback (bool (*pFcn)(long, bool, void *), 
				    long Key, bool iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Key, iFlag, pData);
}

bool ObjektInfo :: EnumAllObjects (bool (*pFcn)(long, bool, void *), 
				   void *pData, bool iShowLast)
{
CTable t (OITree());

	for (t.First(); t.Valid(); ) {
	long lONr = -1L;
	bool iNotLast;

		{
		ObjInfoItemLock l(t);

			iNotLast = t.Next();
			if (!l) continue;
			lONr = l -> ONr();
		} // Lock aufheben

		if (EnumAllObjectsCallback (pFcn, lONr, 
				iShowLast ? iNotLast : false, pData) == false)
			return false;
	}

return true;
}

bool ObjektInfoListe :: EnumAllObjects (bool (*pFcn)(long, bool, void *),
					void *pData, HWND hWnd)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	ObjektInfoLock l(t);
	bool iNotLast = t.Next();

		if (!l) continue;
		if (hWnd != 0 && l -> hWnd() != hWnd) 
			continue;
		if (l -> EnumAllObjects (pFcn, pData, !iNotLast) == false)
			return false;
	}

return true;
}

ulong ObjektInfoListe :: CountObjects (HWND hWnd) 
{
CTable t(*this);
ulong lCnt = 0L;

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (!l) continue;
		if (hWnd != 0 && l -> hWnd() != hWnd)
			continue;
		lCnt += l -> GetCount();
	}

return lCnt;
}

// Alle Fenster in Kenntnis setzen, daß eine Erweiterung geladen wurde --------
bool ObjektInfoListe :: LoadExtension (Extension &E)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l) l -> LoadExtension (E);
	}

return true;
}

// Alle Fenster in Kenntnis setzen, daß eine Erweiterung freigegeben wurde ----
bool ObjektInfoListe :: UnLoadExtension (Extension &E)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	ObjektInfoLock l(t);

		t.Next();	// schon auf nächstes Fenster stellen
		if (l) l -> UnLoadExtension (E, !t.Valid());
	}

return true;
}


// MarkierungsFarbe setzen ----------------------------------------------------
Color ObjektInfo :: SetColor (Color newC)
{
Color oldColor = m_C;

	m_C = newC;
	RePaint();
	
return oldColor;
}

// Laden und entladen einer Erweiterung in einem Objektrecherchefenster -------
bool ObjektInfo :: LoadExtension (Extension &E)
{
	if (E.isLoaded() == LEFullLoad && E.ORMenuHandle() != 0) {
	// Menu einhängen
	HMENU hMenu = GetSubMenu (ObjektMenu.Handle (API_MENU_HMENU), 2);
	unsigned int nCount = GetMenuItemCount (hMenu);

		if (nCount == 0)
	 	// erstes ORMenu: "Extras" aktivieren
 			EnableMenuItem (ObjektMenu.Handle (API_MENU_HMENU), 2, 
					MF_BYPOSITION|MF_ENABLED);

		if (E.ORMenuIndex() == -1) 
		// dieses Fenster ist das erste, MenuIndex setzen
			E.ORMenuIndex() = nCount;

		InsertMenu (hMenu, E.ORMenuIndex(), MF_POPUP|MF_BYPOSITION, 
			    (UINT)E.ORMenuHandle(), E.ORMenuString().c_str());

		DrawMenuBar (m_hWnd);
		return true;
	}

return false;
}

bool ObjektInfo :: UnLoadExtension (Extension &E, bool iLast)
{
CTable r(m_rEL);
HMENU hMenu = GetSubMenu (ObjektMenu.Handle (API_MENU_HMENU), 2);
int oldMenuIndex = -1;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;
		if (E.ExtName() == l -> ExtName()) {
		// Erweiterung gefunden

			if (l -> isLoaded() == LEFullLoad && 
			    l -> ORMenuHandle() != 0) 
			{
			// hat eigenes ORMenu
				oldMenuIndex = l -> ORMenuIndex();
				RemoveMenu (hMenu, oldMenuIndex, MF_BYPOSITION);
				break;		// Schleife abbrechen
			}
		}
	}

// alle nachfolgenden nachziehen, wenn dieses Fenster das letzte ist
short iCnt = 0;

	if (oldMenuIndex != -1) {
		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (!l) continue;
			if (l -> ORMenuHandle() != 0) {
				iCnt++;		// Zähler für ORMenus
				if (iLast) {
					if (l -> ORMenuIndex() == oldMenuIndex) 
						l -> ORMenuIndex() = -1;
					else if (l -> ORMenuIndex() > oldMenuIndex)
						(l -> ORMenuIndex()) --;
				}
			}
		}
	}

// "Extras" passivieren, wenn die letzte Erweiterung herausgenommen wurde
	if (iCnt == 1) 
		EnableMenuItem (ObjektMenu.Handle (API_MENU_HMENU), 2, MF_BYPOSITION|MF_GRAYED);

	DrawMenuBar (m_hWnd);

return true;
}

// Liefert die Anzahl der Objekte in dieser ListeBox --------------------------
ulong ObjektInfo :: GetCount (void)
{ 
	return m_pKurzInfo ? m_pKurzInfo -> LocControl() -> GetCount() : 0; 
} 


// Alle Fenster in Kenntnis setzen, daß ein MenuPunkt installiert wurde -------
HMENU ObjektInfoListe :: InstallMenuItem (short iMenuID, short iMenuNum, char *pText)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l) return l -> InstallMenuItem (iMenuID, iMenuNum, pText);
	}

return 0;
}

// Alle Fenster in Kenntnis setzen, daß eine Erweiterung freigegeben wurde ----
bool ObjektInfoListe :: RemoveMenuItem (short iMenuID, short iMenuNum)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	ObjektInfoLock l(t);

		t.Next();	// schon auf nächstes Fenster stellen

		TX_ASSERT(NULL != (ObjektInfo *)l);
		if (!l -> RemoveMenuItem (iMenuID, iMenuNum))
			return false;
	}

return true;
}


// Ein neues MenuItem in diesem Fenster einhängen -----------------------------
HMENU ObjektInfo :: InstallMenuItem (short iMenuID, short iMenuNum, char *pText)
{
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);
HMENU hSubMenu = GetSubMenu (hMenu, iMenuNum);

	if (hSubMenu == 0) return 0;

// überprüfen, ob dieser Punkt der erste zusätzliche für dieses SubMenu ist
	{
	Menu TestMenu (OBJMENU);	// Menu für VergleichsZwecke
	HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
	HMENU hTestSubMenu = GetSubMenu (hTestMenu, iMenuNum);

		if (GetMenuItemCount (hTestSubMenu) == GetMenuItemCount (hSubMenu))
		// wenn es der erste ist, dann Separator einfügen
			InsertMenu (hSubMenu, (uint)-1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
        }
	InsertMenu (hSubMenu, (uint)-1, MF_BYPOSITION|MF_STRING, iMenuID, pText);
	DrawMenuBar (m_hWnd);

return hSubMenu;
}


bool ObjektInfo :: RemoveMenuItem (short iMenuID, short iMenuNum)
{
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);
HMENU hSubMenu = GetSubMenu (hMenu, iMenuNum);

	if (hSubMenu == 0) return false;

	if (!DeleteMenu (hSubMenu, iMenuID, MF_BYCOMMAND)) {
		TX_ASSERT(false);
		return false;
	}
	
// wenn dieser Punkt der letzte zusätzliche in diesem SubMenu war, dann
// noch den Separator rausnehmen
	{
	Menu TestMenu (OBJMENU);	// Menu für VergleichsZwecke
	HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
	HMENU hTestSubMenu = GetSubMenu (hTestMenu, iMenuNum);
	short iLast = GetMenuItemCount (hSubMenu);

		if (GetMenuItemCount (hTestSubMenu) == iLast)		// nicht '-1', da wir schon einen rausgelöscht haben
		// wenn es der letzte war, dann Separator löschen
			DeleteMenu (hSubMenu, iLast, MF_BYPOSITION);
	}
	DrawMenuBar (m_hWnd);

return true;
}

pWindow ObjektInfoListe :: GetORWindow (HWND hWnd)
{
CTable t (*this);

	if (t.Find (&hWnd)) {
//	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete/* && l -> hWnd() == hWnd*/)
			return (ObjektInfo *)l;
	}

return NULL;
}

HWND ObjektInfoListe :: GetActiveORWindow (void)
{
CTable t (*this);

// Fenster mit Focus liefern
	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && l -> m_fHasFocus)
			return l -> hWnd();
	}

	if (m_hLastActiveWnd) {		// letztes aktives liefern
		if (t.Find ((void *)&m_hLastActiveWnd)) {
		ObjektInfoLock l(t);

			if (l && !l -> m_fToDelete) 
				return m_hLastActiveWnd;
		}
	}

// ansonsten erstbestes liefern
	if (t.First()) {
	ObjektInfoLock l(t);

		if (l) return l -> hWnd();
	}
	
return 0;
}

// Alle fenster auffordern, dieses Objekt rauszunehmen ------------------------
bool ObjektInfoListe :: HandleDeleteObject (long lONr)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete) {
			if (!l -> HandleDeleteObject (lONr))
				return false;
		}
	}

return true;
}

// Alle Fenster auffordern, dieses Objekt umzuklassifizieren ------------------
bool ObjektInfoListe :: HandleModifyIdent (long lONr)
{
CTable t (*this);
long lIdent = DEX_GetObjIdent (lONr);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete) {
			if (!l -> HandleModifyIdent (lONr, lIdent))
				return false;
			l -> RePaint();		// neu zeichnen
		}
	}

return true;
}

bool ObjektInfoListe :: HandleCancelMode (bool fCmd)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete) {
			if (!l -> HandleCancelMode (fCmd))
				return false;
		}
	}

return true;
}

bool ObjektInfo :: HandleCancelMode (bool fCmd)
{
	m_fCmd = fCmd;
	
return true;
}

void ObjektInfoListe :: Enable (bool fEnable)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		TX_ASSERT(NULL != (ObjektInfo *)l);
		if (!l -> m_fToDelete) {
			if (fEnable) 
				l -> Enable();
			else
				l -> Disable();
		}
	}
}

// Alle Fenster auffordern, dieses Objekt neu einzulesen ----------------------
bool ObjektInfoListe::HandleModifyFeature (long lONr, LPCSTR pcName)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete) {
			if (!l -> HandleModifyFeature (lONr, pcName))
				return false;
			l -> RePaint();		// neu zeichnen
		}
	}

return true;
}

// Hauptfenster wurde angezeigt/ausgeblendet, ORFenster nachziehen ------------
void ObjektInfoListe::ShowORWindows (ShowState s)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete) 
			l -> Show(s);
	}
}

// Enumeration aller ORFenster ------------------------------------------------
extern "C" 
inline bool EnumORWindow (bool (*pFcn)(long, bool, void *), 
			  HWND hWnd, bool iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)((LONG)(void *)hWnd, iFlag, pData);
}

bool ObjektInfoListe :: EnumORWindows (ENUMNOKEYLONG *pK)
{
CTable t (*this);

	for (t.First(); t.Valid(); ) {
	ObjektInfoLock l(t);
	bool fNext = t.Next();

		if (l && !l -> m_fToDelete) {
			if (false == EnumORWindow (pK -> eFcn, l -> hWnd(), 
						   !fNext, pK -> ePtr))
				return false;	// abgebrochen
		}
	}

return true;
}


// Enumeration aller Identifikatoren im RechercheFenster ----------------------
extern "C" {

inline bool EnumORIdents (bool (*pFcn)(long, bool, void *), 
			  long Key, bool iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Key, iFlag, pData);
}

inline bool EnumORIdentsEx (bool (*pFcn)(long, DWORD, void *), 
			    long Key, DWORD iOTypes, void *pData)
{
	return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(Key, iOTypes, pData);
}

}	// extern "C" 

bool ObjektInfo :: EnumIdents (bool (*pFcn)(long, bool, void *), 
			       void *pData, bool fSelected, bool fWithOTypes)
{
// Identifikatoren in einem Baum aufsammeln und dann Enumerieren
CORIdents *pT = new CORIdents;

	if (pT == NULL) return false;
	{
	CTable t (OITree());	// Baum aller Objekte im Fenster
	
		for (t.First(); t.Valid(); t.Next()) {
		ObjInfoItemLock l(t);

			if (!l) continue;
			
		long lONr = l -> ONr();
		short iIndex = (short)m_pKurzInfo -> FindItem ((void *)lONr);
		bool fIsSel = m_pKurzInfo -> GetSelection (iIndex);
		
			if (fSelected && !fIsSel) continue;
			
		long lIdent = DEX_GetObjIdent(lONr);
		CORIdent *pId = NULL;
		short iOType = l -> GetOType();
		
			if ((pId = pT -> FFindItem ((ULONG &)lIdent)) == NULL) {
				if (!pT -> FAddItem ((ULONG &)lIdent, iOType))
					break;
			} else if (fWithOTypes)
				pId -> FMergeOTypes (iOType);
		}
	}
	
// Enumeration der gefundenen Identifikatoren
bool fResult = true;

	if (fWithOTypes) {	// ObjektTypen liefern
	CTable t (*pT);
	
		for (t.First(); t.Valid(); t.Next()) {
		CORIdentLock l(t);		
		
			if (EnumORIdentsEx ((ENUMNOKEYLONGEXPROC)pFcn, l -> FGetULONG(), 
					    l -> FGetOTypes(), pData) == false) 
			{
				fResult = false;
				break;	// abbrechen
			}
		}
	} else {
	// normale Enumeration
	CTable t (*pT);
	
		for (t.First(); t.Valid(); ) {
		CORIdentLock l(t);		
		bool fNext = t.Next();

			if (EnumORIdents (pFcn, l -> FGetULONG(), fNext, pData) == false) 
			{
				fResult = false;
				break;	// abbrechen
			}
		}
	}

// aufräumen
	DELETE (pT);
	
return fResult;
}

void ObjektInfoListe :: CloseORWindow (HWND hWnd)
{
CTable t (*this);

	if (t.Find (&hWnd)) {
//	for (t.First(); t.Valid(); t.Next()) {
	bool fToDelete = false;

		{
		ObjektInfoLock l(t);

			TX_ASSERT(NULL != (ObjektInfo *)l);

			if (l && !l -> m_fToDelete)
				fToDelete = true;
		} // Lock goes out of scope
		
		if (fToDelete) 
			t.Delete();		// Fenster freigeben
	}
}

#if defined(WIN32) && !defined(_OLD_DRAGNDROP)
bool ObjektInfo::IsDropSourceInst (void)
{ 
	return EL().IsDropSource(); 
}

bool ObjektInfo::IsDropSourceORWnd (void)
{ 
	return ((IrisWind *)GetParent())->IsDropSourceORWnd(); 
}

bool ObjektInfoListe::IsDropSourceORWnd (void)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		TX_ASSERT(NULL != (ObjektInfo *)l);
		if (!l) continue;

		if (l -> IsDropSource())
			return true;		// dieses Fenster ist DragSource
	}

return false;		// keines der Fenster ist DragSource
}

#endif // WIN32
