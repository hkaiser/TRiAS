// Routinen fuer DialogFenster ObjektRecherche --------------------------------
// File: OBJEKTE.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <xtsnguid.h>
#include <undoguid.h>
#include <dirisole.h>
#include <iunredo.hxx>
#include <ScopeVar.h>
#include <funcs02.h>

#include "TRiASMode.h"
#include "extmain3.hxx"

#include "Strings.h"
#include "menuitem.hxx"
#include "schrift.hxx"
#include "relobj.hxx"
#include "edittext.hxx"
#include "objowndr.hxx"

#include "oridents.hxx"
#include "oridents.inl"

//#include <CrtMemDebug.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HelpDisplay *IrisHD;
extern bool g_fDrawTextObjs;		// TextObjekte anzeigen / recherchieren
extern HINSTANCE hInstance;			// Handle dieser Programminstanz

short OTypToBits (ObjTyp iOTyp);

#define EXTRA_OBJECTMENU_POS	3

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;
#endif // _TRiAS_VER < 0x0510

extern double g_dScaleX;
extern double g_dScaleY;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(UndoRedoAddToObjectWnd);

///////////////////////////////////////////////////////////////////////////////
// Konstruktor
ObjektInfo::ObjektInfo (pWindow pW, DatenBasisObjekt &rDBO, ExtensionList &EL, 
			  short iFlags, CMPONRPROC pProc, DWORD dwData, LPUNKNOWN pIUnk)
	    : OwnerDrawDialogWindow (pW, ResID(OBJEKTE40), false),
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
	m_fIgnoreObjProp = false;

// optimieren nur, wenn nicht nach Texten sortiert werden soll und Optimierung nicht ausgeschaltet
	m_fUseEntryCallback = !(iFlags & ROForceNoCallback) && !(iFlags & ROSortText);

// Flags fürs Zerlegen des aktiven Fensters
	m_lCommandActive = 0;
	m_fMustDestroy = false;

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

#if _TRiAS_VER < 0x0400
// ggf. Suchen und ersetzen entfernen
	if (0 == g_dwVer4) {
		ObjektMenu.DeleteItem (IDM_OBJMENU_REPLACE);
		ObjektMenu.DeleteItem (IDM_DELETE_OBJPROPS);
		ObjektMenu.DeleteItem (IDM_OBJMENU_CLASSIFY);
	}
#endif // _TRiAS_VER < 0x0400

#if _TRiAS_VER < 0x0510
// ggf. 'Objektmenge speichern ...'/'Räumlichen Filter erzeugen ...' entfernen
	if (0 == g_dwVer51) {
		ObjektMenu.DeleteItem (ID_OBJMENU_SAVEOBJECTCOLLECTION);
		::RemoveMenu (::GetSubMenu(ObjektMenu.Handle(), 0), 0, MF_BYPOSITION);
		ObjektMenu.DeleteItem (IDM_CONNECTION_FILTER);
	}
#endif // _TRiAS_VER < 0x0400
	ChangeMenu (&ObjektMenu);	// Menu einhängen

// Menupunkt an Systemmenu anhängen
HMENU hSysMenu = ::GetSystemMenu (m_hWnd, false);

	::AppendMenu (hSysMenu, MF_SEPARATOR, 0, (LPSTR)NULL);
#if _TRiAS_VER < 0x0400
	if (0 != g_dwVer4) 
#endif // _TRiAS_VER < 0x0400
	{
		if (g_dwTRiASMode & TRIASMODE_RollUpORWnds) {
			::AppendMenu (hSysMenu, MF_STRING, IDM_MINIMIZEORWNDS, ResString (IDS_MINIMIZEORWNDS, 64));
			::AppendMenu (hSysMenu, MF_STRING, IDM_MAXIMIZEORWNDS, ResString (IDS_MAXIMIZEORWNDS, 64));
			::AppendMenu (hSysMenu, MF_SEPARATOR, 0, (LPSTR)NULL);
		}
	}
	::AppendMenu (hSysMenu, MF_STRING, IDM_REMOVEORWNDS, ResString (IDS_REMOVEORWNDS, 30));

// Menupunkte eines Fensters mit SysMenu entfernen
	::RemoveMenu (hSysMenu, SC_MINIMIZE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_RESTORE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND);

#if !defined(WIN16)
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
#endif // WIN16

#if !defined(_NO_ROLLUP_ORWND)
	m_fPushedButton = false;
	m_fIsRolledUp = false;
	m_fMouseCaptured = false;
	m_hMenu = NULL;
	m_lInitialWidth = 0;
#endif // !defined(_NO_ROLLUP_ORWND)
}

// Destruktor -----------------------------------------------------------------
ObjektInfo::~ObjektInfo (void) 
{
// QueryClose rufen
	locQueryClose();

	DELETE_OBJ (m_pKurzInfo);		// ListBox freigeben
	DELETE_OBJ (m_pOITree);		// ObjInfoItemTree freigeben

// Erweiterungen aus Menu herauslösen
	if (m_rEL.CountLoaded() > 0) {
		RemovePopupMenues();

	HMENU hMainMenu = ObjektMenu.Handle (API_MENU_HMENU);
	int iLast = GetMenuItemCount (hMainMenu)-1;
	HMENU hMenu = GetSubMenu (hMainMenu, iLast);
	CTable r(m_rEL);

		for (r.Last(); r.Valid(); r.Prev()) {
		ExtensionLock l(r);

			if (!l) continue;
			if (l -> ORMenuHandle() != 0) 	// Menu herauslösen
				RemoveMenu (hMenu, l -> ORMenuIndex(), MF_BYPOSITION);
		}
		DrawMenuBar (m_hWnd);
	}
	
	DELETE_OBJ (m_pBuffer);
	DELETE_OBJ (m_pBuffer1);

	if (m_pIObjProp) 
		m_pIObjProp -> Release();

	RevokeDragDrop();				// DragDrop abmelden
	if (m_fBrushToDelete)
		::DeleteObject (m_hBr);

	DeleteCriticalSection (&m_CS);
}


ObjektInfo *ObjektInfo::CreateInstance (
	pWindow pW, DatenBasisObjekt &rDBO, ExtensionList &EL, ObjFeld &OF, 
	short iFlags, CMPONRPROC pProc, DWORD dwData, LPUNKNOWN pIUnk)
{
ObjektInfo *pOInfo = new ObjektInfo (pW, rDBO, EL, iFlags, pProc, dwData, pIUnk);

	if (NULL == pOInfo || !pOInfo -> FInit (OF)) {
		DELETE_OBJ (pOInfo);
		return NULL;
	}
	return pOInfo;
}

ObjektInfo *ObjektInfo::CreateInstance (
	pWindow pW, DatenBasisObjekt &rDBO, ExtensionList &EL, 
	INT_PTR *plONr, long lCnt, short iFlags, CMPONRPROC pProc, DWORD dwData, LPUNKNOWN pIUnk)
{
ObjektInfo *pOInfo = NULL;

	ATLTRY(pOInfo = new ObjektInfo (pW, rDBO, EL, iFlags, pProc, dwData, pIUnk));
	if (NULL == pOInfo || !pOInfo -> FInit(plONr, lCnt)) {
		DELETE_OBJ (pOInfo);
		return NULL;
	}
	return pOInfo;
}

bool ObjektInfo::FInit(ObjFeld &rOF)
{
	if (!FInit1 (rOF.Count()))
		return false;
		
INT_PTR lONr = 0;

	if (!FInit2 (rOF, lONr)) {
		if (!FInit3 (lONr)) 
			return false;
	}

	UpdateCaption();					// Caption dieses Fensters aktualisieren
	return true;
}

bool ObjektInfo::FInit(INT_PTR *plONr, long lCnt)
{
	if (!FInit1 (lCnt))
		return false;
		
INT_PTR lONr = 0;

	if (!FInit2 (plONr, lCnt, lONr)) {
		if (!FInit3 (lONr)) 
			return false;
	}

	UpdateCaption();					// Caption dieses Fensters aktualisieren
	return true;
}

bool ObjektInfo::FInit1(long lCnt)
{
// Baum initialisieren
	COM_TRY {
		if (NULL == m_pOITree) {
			m_pOITree = new ObjInfoItemTree();
			if (NULL == m_pOITree) {
				db_error (EC_NOMEMORY, RC_ctObjInfo);
				return false;
			}
		}
		if (GenerateListBox() != EC_OKAY) 
			return false;		// OwnerDrawMultiSelListBox generieren

		InitExtensionMenus();	// Erweiterungen einhängen
		InitMenuItems();		// zusätzliche MenuItems einhängen

	#if defined(_NEWORMENU)
		m_hAccel = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_OBJMENUACCEL));
		if (NULL == m_hAccel) return false;
	#endif // _NEWORMENU

	// interne ZeichenPuffer anlegen
		if (NULL == m_pBuffer) {
			m_pBuffer = new char [2*_MAX_PATH];
			m_pBuffer1 = new char [2*_MAX_PATH];
			if (NULL == m_pBuffer || NULL == m_pBuffer1)
				return false;
		}
		
	// in Win95 evtl. vorher Speicher anfordern
		if (IsWin40() && lCnt > 100) 
			::SendMessage (m_pKurzInfo -> LocControl() -> Handle(), LB_INITSTORAGE, lCnt, lCnt*64);		// ca. 64 Bytes je Eintrag

	// DragDrop initialisieren
		if (FAILED(InitDragDrop()))	
			return false;

	// Objekteigenschaft rücksetzen, die verwendet werden soll
		m_rEL.ResetActObjProp();

	} COM_CATCH_RETURN(false);
	return true;
}

bool ObjektInfo::FInit2 (ObjFeld &OF, INT_PTR &rlONr)
{
// ListBox mit nötigen Info's aus ObjektFeld füllen
bool fAddToList = (m_pOITree -> Count() != 0) ? true : false;
bool fFirst = fAddToList;

CRing r(OF);
set<INT_PTR> Idents;

	for (r.First(); r.Valid(); r.Next()) {
	ObjNummerLock l(r);

		TX_ASSERT(NULL != (ObjNummer *)l);

	// Objekteigenschaft rücksetzen, die verwendet werden soll
	long lLocONr = l -> _ON;
	os_string strActOProp;
	INT_PTR lIdent = DEX_GetObjIdentEx(lLocONr);

		if (!fAddToList) {
		set<INT_PTR>::iterator it = Idents.find (lIdent);

			if (it == Idents.end()) {
			// Reset für jeden Ident nur einmal rufen
				Idents.insert(lIdent);
				if (S_OK == m_rDBO.Idents().GetObjectProperty (lIdent, strActOProp))
					m_rEL.ResetActObjProp(strActOProp.c_str());
			}
		}

	HRESULT hr = RetrieveObjInfo (lLocONr);

		if (S_OK == hr && !fFirst) {	// erster Neuzugang
		// die erste Objektnummer merken, die in die Listbox kommt
			rlONr = lLocONr;
			fFirst = true;
		}
		if (FAILED(hr)) break;
	}

	m_pOITree -> Optimize();
	if (fAddToList)	
		return true;	// hier aufhören, wenn nicht erstes FInit
	return false;
}

bool ObjektInfo::FInit2 (INT_PTR *plONr, long lCnt, INT_PTR &rlONr)
{
// ListBox mit nötigen Info's aus ObjektFeld füllen
bool fAddToList = (0 != m_pOITree -> Count()) ? true : false;
bool fFirst = fAddToList;

set<INT_PTR> Idents;

	for (long lCurr = 0; lCurr < lCnt; ++lCurr) {
	// Objekteigenschaft rücksetzen, die verwendet werden soll
	long lLocONr = plONr[lCurr];
	os_string strActOProp;
	INT_PTR lIdent = DEX_GetObjIdentEx(lLocONr);

		if (!fAddToList) {
		set<INT_PTR>::iterator it = Idents.find (lIdent);

			if (it == Idents.end()) {
			// Reset für jeden Ident nur einmal rufen
				Idents.insert(lIdent);
				if (S_OK == m_rDBO.Idents().GetObjectProperty (lIdent, strActOProp))
					m_rEL.ResetActObjProp(strActOProp.c_str());
			}
		}

	HRESULT hr = RetrieveObjInfo (lLocONr);

		if (S_OK == hr && !fFirst) {	// erster Neuzugang
		// die erste Objektnummer merken, die in die Listbox kommt
			rlONr = lLocONr;
			fFirst = true;
		}
		if (FAILED(hr)) break;
	}

	m_pOITree -> Optimize();
	if (fAddToList)	
		return true;	// hier aufhören, wenn nicht erstes FInit
	return false;
}

bool ObjektInfo::FInit3(INT_PTR lONr)
{
// ersten Eintrag aktivieren
	if (0 != lONr) {
	int iIndex = FindObject (lONr);

		if (iIndex != -1) {
			m_pKurzInfo -> ChangeSelected (iIndex);
			m_pKurzInfo -> SetCaretIndex (iIndex);
		}
	}

	if (0 == lONr) 
		lONr = -1;
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
ErrCode ObjektInfo::GenerateListBox (void) 
{
	if (m_pKurzInfo != NULL) return EC_OKAY;		// bereits generiert
	
HDC hDC = ::GetDC (m_hWnd);	// hWnd ist Suchschlüssel
TEXTMETRIC tm;

	::GetTextMetrics (hDC, &tm);
	::ReleaseDC (m_hWnd, hDC);

// benötigte Größe berechnen: Listbox muß COUNT_ITEMS Zeilen mit je COUNT_CHARS Zeichen aufnehmen
Rectangle Rc (
	Point (0, 0), 
	Point (long(tm.tmAveCharWidth*m_iCntChars * g_dScaleX) + GetSystemMetrics (SM_CXVSCROLL), 
		   long(tm.tmHeight*m_iCntItems * g_dScaleY)
		  )
	);

	m_pKurzInfo = new ObjektInfoListBox (this, IDL_OBJEKTE, *this);
	if (m_pKurzInfo == NULL) 
		return (ErrCode)db_error (EC_NOMEMORY, RC_ctObjInfo);

	m_pKurzInfo -> LocControl() -> ChangeSize (Dimension (Rc.Right(), Rc.Bottom()));

#if !defined(WIN16)
	m_pKurzInfo -> EnableDragDrop();		// Drag'n Drop erlauben
	if (IsWin40()) 
		AdjustWindowRectEx ((RECT *)&Rc, WS_THICKFRAME|WS_POPUP|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU, true, WS_EX_TOOLWINDOW);
	else
		AdjustWindowRectEx ((RECT *)&Rc, WS_POPUP|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU, true, 0);
#else
	AdjustWindowRect ((RECT *)&Rc, WS_POPUP|WS_CAPTION, true);
#endif // WIN16
	ChangeSize (Dimension (Rc.Right()-Rc.Left(), Rc.Bottom()-Rc.Top()));

#if !defined(_NO_ROLLUP_ORWND)
	m_lInitialWidth = Rc.Width();
#endif // !defined(_NO_ROLLUP_ORWND)
	
	m_pKurzInfo -> ChangePosition (Point (0, 0));
	return EC_OKAY;
}

// Die Menu's aller geladenen Extensions richtig im lokalen Menu aufnehmen
void ObjektInfo::InitExtensionMenus (void)
{
	if (m_fInitExtMenus) return;		// schon erledigt
	
	if (m_rEL.CountLoaded() > 0) {
	HMENU hMainMenu = ObjektMenu.Handle(API_MENU_HMENU);
	int iLast = GetMenuItemCount (hMainMenu)-1;

	CTable r(m_rEL);
	// Datenexport/Rechercheergebnisse/Räumliche Filter hängen jetzt immer drin
	int i = 3;

#if _TRiAS_VER < 0x0510
		if (0 == g_dwVer51)
			i = 2;
#endif // _TRiAS_VER < 0x0510
	
	bool iFirst = true;
	HMENU hMenu = GetSubMenu (hMainMenu, iLast);

		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (!l) continue;
			if (l -> ORMenuHandle() != 0) {		// Menu einhängen
				if (iFirst) {
			 		EnableMenuItem (hMainMenu, iLast, MF_BYPOSITION|MF_ENABLED);
					iFirst = false;
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
void ObjektInfo::InitMenuItems (void)
{
	if (m_fInitMenuItems) return;	// schon erledigt
	
	if (m_rEL.CountLoaded() == 0 || !m_rEL.hasMIL()) return;

HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);
CRing r (m_rEL.MIL());

// zuerst alles, was zu entfernen ist
	for (r.Last(); r.Valid(); r.Prev()) {
	CMenuItemLock l(r);

		if (!l || !(l -> m_fRemoveItem))
			continue;

		RemoveMenuItem (l -> _iMenuID, l -> _iPopup);
	}

// jetzt alle Popups, die hinzuzufügen sind
	for (r.Last(); r.Valid(); r.Prev()) {
	CMenuItemLock l(r);

		if (!l || l -> m_fRemoveItem) continue;
		if (NULL != l -> m_hMenu) {
		UINT uiPos = -1;

			InstallMenuItem (l -> _iPopup, const_cast<char *>(l -> m_strMenuText.c_str()), l -> m_hMenu, l -> m_fIsTopLevel, &uiPos);
			TX_ASSERT(-1 == l -> _iMenuPos || l -> _iMenuPos == uiPos);

			l -> _iMenuPos = uiPos;		// Position fürs Herauslösen speichern
		}
	}

// jetzt alles andere, was hinzuzufügen ist
	for (r.Last(); r.Valid(); r.Prev()) {
	CMenuItemLock l(r);

		if (!l || l -> m_fRemoveItem) continue;
		if (NULL == l -> m_hMenu) {
			if (l -> m_strMenuText.size() > 0) {
				InstallMenuItem (l -> _iMenuID, l -> _iPopup, l -> _iMenuPos, const_cast<char *>(l -> m_strMenuText.c_str()));
			} else {
			// Separator
			UINT uiPos = -1;

				InstallMenuItem (l -> _iMenuID, l -> _iPopup, l -> _iMenuPos, NULL, &uiPos);
				TX_ASSERT(-1 == l -> _iMenuPos || l -> _iMenuPos == uiPos);

				l -> _iMenuPos = uiPos;
			}
		}
	}
	m_fInitMenuItems = true;
}

void ObjektInfo::RemovePopupMenues()
{
CRing r (m_rEL.MIL());
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);

	for (r.Last(); r.Valid(); r.Prev()) {
	CMenuItemLock l(r);

		if (!l || NULL == l -> m_hMenu || l -> m_fRemoveItem) 
			continue;

	// Popupmenu rausnehmen
		if (l -> m_fIsTopLevel)
			RemoveMenu (hMenu, l -> _iPopup, MF_BYPOSITION);
		else {
		HMENU hSubMenu = GetSubMenu (hMenu, l -> _iPopup);
		UINT uiPos = l -> _iMenuPos;

			if (-1 == uiPos)
				uiPos = GetMenuItemCount(hSubMenu)-1;
			RemoveMenu (hSubMenu, uiPos, MF_BYPOSITION);
		}
	}
}

// ----------------------------------------------------------------------------
// InputFocusänderung ---------------------------------------------------------
void EXPORTTRIAS ObjektInfo::FocusChange (FocusChangeEvt e) 
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
	case OT_KO:			return 'K';
	case OT_UNKNOWN:
	default:
		break;
	}
	return 'U';
}

char *FormatROString (char *pText, RECHOBJECT &rRO);
short OTypToBits (ObjTyp iOTyp);

namespace retrieve_objects {
	inline 
	bool FMatchScales (long lActScale, long lUpperScale, long lLowerScale)
	{
		if (0 != lUpperScale && lActScale < lUpperScale)
			return false;

		if (0 != lLowerScale && lActScale > lLowerScale)
			return false;

		return true;
	}

// Zuordnung der Zuordnungsobjektklassen zu den Objektnummern innerhalb dieser
	typedef set<pair<INT_PTR, INT_PTR> > CIdentObjects;

	BOOL CALLBACK GetObjectClassesCB (long lIdent, DWORD hObj, void *pData)
	{
	insert_iterator<CIdentObjects> *pit = reinterpret_cast<insert_iterator<CIdentObjects> *>(pData);

		_ASSERTE(0 != hObj);
		*pit = CIdentObjects::value_type(INT_PTR(lIdent), INT_PTR(hObj));
		return TRUE;
	}

	inline
	BOOL GetObjectClasses (INT_PTR lONr, insert_iterator<CIdentObjects> it, DWORD dwFlags)
	{
	ENUMLONGKEYEX ENK;

		ENK.eKey = lONr;
		ENK.eFcn = reinterpret_cast<ENUMLONGKEYEXPROC>(GetObjectClassesCB);
		ENK.ePtr = reinterpret_cast<void *>(&it);
		ENK.eData = dwFlags;
		return DEX_EnumObjectClasses (ENK);
	}
} // namespace

HRESULT ObjektInfo::RetrieveObjInfo (long lONr, int iIndex, int *piNewIndex, bool fUndo) 
{
	using retrieve_objects::CIdentObjects;
	using retrieve_objects::GetObjectClasses;

CTable t(OITree());
CActDB Act (m_rDBO.DB());

//	TX_ASSERT(IsValidONr(lONr));	// dauert zu lange
	TX_ASSERT(0 != lONr && -1 != lONr);
	
	if (t.Find (&lONr)) 
		return S_FALSE;		// Objekt gibt es schon
	if (!g_fDrawTextObjs && isDBTextObjekt (lONr))
		return S_FALSE;		// BegleitObjekte nicht anzeigen

HRESULT hr = S_FALSE;
int iNewIndex = iIndex;
CIdentObjects ObjsAndClasses;

	if (ROAddPureObjects & m_iFlags)
		ObjsAndClasses.insert (CIdentObjects::value_type(DEX_GetObjIdentEx(lONr), INT_PTR(lONr)));
	else if (!GetObjectClasses (lONr, inserter(ObjsAndClasses, ObjsAndClasses.end()), CFO_ActViewOnly))
		return S_FALSE;

	for (CIdentObjects::iterator it = ObjsAndClasses.begin(); it != ObjsAndClasses.end(); ++it) {	
	// alle Objektklassen (incl. Zuordnungsobjektklassen) mit diesem Objekt durchgehen
		hr = RetrieveObjInfo ((*it).second, (*it).first, iIndex, &iNewIndex, fUndo);
		if (S_OK != hr)
			return hr;
		iIndex = iNewIndex+1;
	}
	if (NULL != piNewIndex)
		*piNewIndex = iNewIndex;
	return hr;
}

HRESULT ObjektInfo::RetrieveObjInfoDirect (long lONr, long lIdent, int iIndex, int *piNewIndex, bool fUndo) 
{
	using retrieve_objects::FMatchScales;

ObjTyp iObjType = m_rDBO.RetrieveObjTyp(lONr);	// ObjektTyp bestimmen

// Testen, ob dieses Objekt fraktal entfällt
long lUpperScale = 0L;
long lLowerScale = 0;

	m_rDBO.RetrieveIdentScaleData (NULL, lIdent, OTypToVTyp(iObjType), &lUpperScale, &lLowerScale);
	if (!FMatchScales (m_rDBO.GetActScale(), lUpperScale, lLowerScale)) 
		return S_FALSE;		// derzeit fraktal ausgeblendet

// Objekteigenschaft bestimmen
bool fExistsForThisObject = true;

HRESULT hr = S_FALSE;		// zumindest OKS besorgen
HPROJECT hPr = DEX_GetObjectsProject(lIdent);

// wenn ObjProp vorgegeben ist, dann diese nutzen, sonst Voreinstellung
	if (m_fExistsOP) {
		if (m_pIObjProp)
			hr = m_pIObjProp -> Eval (lONr, m_pBuffer, _MAX_PATH, NULL);
		else if (!m_fIgnoreObjProp) {
		// nur, wenn globale Objekteigenschaft(en) nicht ignoriert werden soll(en)
		os_string strActOProp;

			if (S_OK == m_rDBO.Idents().GetObjectProperty (lIdent, strActOProp))
				hr = m_rEL.InvokeActObjProp (lONr, m_pBuffer, _MAX_PATH, NULL, strActOProp.c_str());
			else if (NULL != m_rEL.GetActObjPropName()) 
				hr = m_rEL.InvokeActObjProp (lONr, m_pBuffer, _MAX_PATH, NULL);
			else
				hr = S_FALSE;	// auch keine globale ObjProp --> Objektklasse anzeigen
		}

		if (S_OK == hr && !(m_iFlags & ROHideDatasource) && DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		char cbBuffer[_MAX_PATH];

			TX_ASSERT(HACTCONNECTION != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (m_pBuffer, " (");
				strcat (m_pBuffer, cbBuffer);
				strcat (m_pBuffer, ")");
			}
		}
	}

	if (S_OK != hr) {
	// wenn keine OPF gegeben ist, dann IdentKurzText verwenden
	LPCSTR pcKText = m_rDBO.GetKurzText(lIdent, !(m_iFlags & ROHideDatasource));

		TX_ASSERT(NULL != pcKText);

		m_pBuffer[0] = '\0';
		if (NULL != pcKText) 
			strncpy (m_pBuffer, pcKText, _MAX_PATH);	// default: IdKurzText

		m_pBuffer[_MAX_PATH-1] = '\0';
	
		if (S_FALSE != hr && E_FAIL != hr)
			m_fExistsOP = false;
		if (E_FAIL == hr || HRESULT_FROM_ERRCODE(WC_NOTFOUND) == hr)
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
	if (DEXN_QueryRechObject (RO))
		return S_FALSE;				// Objekt hat nicht zu recherchierenden Ident oder jemand hat was dagegen

// angezeigten Eintrag zusammenstellen und zu ListBox hinzufügen
	if (FormatROString (m_pBuffer1, RO)) {
	Color C, cObjProp;

		if (RO.iOTyp == OT_KO) {	// Komplexobjekte werden DunkelGrün
			C = Color (ColorVal(128), ColorVal(0), ColorVal(0));
			cObjProp = fExistsForThisObject ? C : Color(ColorVal(64), ColorVal(0), ColorVal(0));
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
//		if (OITree().Count() % 100 == 0)
//			OITree().Optimize();
		
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
		if (fUndo) {
		WUndoRedoAddToObjectWnd Undo;
		HRESULT hr = UndoCreateInstance (IID_IUndoRedoAddToObjectWnd, Undo.ppv());

			if (SUCCEEDED(hr) && S_OK == Undo -> Init2 (m_hWnd, lONr, FALSE, FALSE)) 
				DEX_AddUndoRedo (Undo.p);
		}
		return S_OK;	// alles ok
	}
	return S_FALSE;		// nicht in Listbox aufgenommen, trotzdem weitermachen
}

HRESULT ObjektInfo::RetrieveObjInfoCallback (
	INT_PTR lONr, INT_PTR lIdent, int iIndex, int *piNewIndex, bool fUndo) 
{
	using retrieve_objects::FMatchScales;

ObjTyp iObjType = m_rDBO.RetrieveObjTyp(lONr);	// ObjektTyp bestimmen

// Testen, ob dieses Objekt fraktal entfällt
long lUpperScale = 0L;
long lLowerScale = 0;

	m_rDBO.RetrieveIdentScaleData (NULL, lIdent, OTypToVTyp(iObjType), &lUpperScale, &lLowerScale);
	if (!FMatchScales (m_rDBO.GetActScale(), lUpperScale, lLowerScale)) 
		return S_FALSE;		// derzeit fraktal ausgeblendet

// Selektierbarkeit, Ausblendestatus etc. abfragen
RECHOBJECT RO;

	m_pBuffer[0] = '\0';
	INITSTRUCT(RO, RECHOBJECT);
	RO.lONr = lONr;
	RO.lIdent = lIdent;
	RO.lpText = m_pBuffer;
	RO.iTextLen = _MAX_PATH-1;
	RO.iOTyp = (short)iObjType;	
	RO.iFlags = m_iFlags & (ROHideFlags|ROShowHidden);	// voreingestellte Bits setzen
	if (DEXN_QueryRechObject (RO))
		return S_FALSE;				// Objekt hat nicht zu recherchierenden Ident oder jemand hat was dagegen

// zuerst versuchen, den Eintrag in den Baum zu schreiben
	{
	ObjInfoItemCreator OIICr (OITree());
	ObjInfoItem *pOII = ContCreate (OIICr, ObjInfoItem)(
        lONr, lIdent, OTypToBits(iObjType), m_C); 

		if (NULL == pOII) {
			db_error (EC_NOMEMORY, RC_RetrieveObjInfo);
			return E_OUTOFMEMORY;		// nicht weitermachen
		}
	}	// wegspeichern
//	if (OITree().Count() % 100 == 0)
//		OITree().Optimize();
	
// dann die gleiche Info in Listbox speichern
int iInsertIndex = (iIndex < GetCount()) ? iIndex : -1;
int iNewIndex = m_pKurzInfo -> AddItemEx (lONr, g_cbNil, iInsertIndex);

	if (0 > iNewIndex) {	// nicht eingefügt
	// Fehlermeldung ausgeben
		VMessageBox (GetParent(), IDS_LISTOUTOFSPACECAP, ExclamationIcon|OkayButton, IDS_LISTOUTOFSPACE);
		return E_OUTOFMEMORY;	// Fehler oder kein Platz mehr
	}
	
	if (piNewIndex) 
		*piNewIndex = iNewIndex;	// Index des neuen Eintrages liefern

	DEXN_ObjectAddedToList(lONr);
	if (fUndo) {
	WUndoRedoAddToObjectWnd Undo;
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoAddToObjectWnd, Undo.ppv());

		if (SUCCEEDED(hr) && S_OK == Undo -> Init2 (m_hWnd, lONr, FALSE, FALSE)) 
			DEX_AddUndoRedo (Undo.p);
	}
	return S_OK;	// alles ok
}

HRESULT ObjektInfo::RetrieveObjInfoCallback(ObjInfoItem *pItem)
{
	_ASSERTE(GetUseEntryCallback());

// Objekteigenschaft bestimmen
bool fExistsForThisObject = true;

INT_PTR lONr = pItem -> ONr();
INT_PTR lIdent = pItem -> GetIdent();

HRESULT hr = S_FALSE;		// zumindest OKS besorgen
HPROJECT hPr = DEX_GetObjectsProject(pItem -> GetIdent());

// wenn ObjProp vorgegeben ist, dann diese nutzen, sonst Voreinstellung
	if (m_fExistsOP) {
		if (m_pIObjProp)
			hr = m_pIObjProp -> Eval (lONr, m_pBuffer, _MAX_PATH, NULL);
		else if (!m_fIgnoreObjProp) {
		// nur, wenn globale Objekteigenschaft(en) nicht ignoriert werden soll(en)
		os_string strActOProp;

			if (S_OK == m_rDBO.Idents().GetObjectProperty (lIdent, strActOProp))
				hr = m_rEL.InvokeActObjProp (lONr, m_pBuffer, _MAX_PATH, NULL, strActOProp.c_str());
			else if (NULL != m_rEL.GetActObjPropName()) 
				hr = m_rEL.InvokeActObjProp (lONr, m_pBuffer, _MAX_PATH, NULL);
			else
				hr = S_FALSE;	// auch keine globale ObjProp --> Objektklasse anzeigen
		}

		if (S_OK == hr && !(m_iFlags & ROHideDatasource) && DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		char cbBuffer[_MAX_PATH];

			TX_ASSERT(HACTCONNECTION != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (m_pBuffer, " (");
				strcat (m_pBuffer, cbBuffer);
				strcat (m_pBuffer, ")");
			}
		}
	}

	if (S_OK != hr) {
	// wenn keine OPF gegeben ist, dann IdentKurzText verwenden
	LPCSTR pcKText = m_rDBO.GetKurzText(lIdent, !(m_iFlags & ROHideDatasource));

		TX_ASSERT(NULL != pcKText);

		m_pBuffer[0] = '\0';
		if (NULL != pcKText) 
			strncpy (m_pBuffer, pcKText, _MAX_PATH);	// default: IdKurzText

		m_pBuffer[_MAX_PATH-1] = '\0';
	
		if (S_FALSE != hr && E_FAIL != hr)
			m_fExistsOP = false;
		if (E_FAIL == hr || HRESULT_FROM_ERRCODE(WC_NOTFOUND) == hr)
			fExistsForThisObject = false;		// Objprop existiert nicht für dieses Objekt
	}

RECHOBJECT RO;

	INITSTRUCT(RO, RECHOBJECT);
	RO.lONr = lONr;
	RO.lIdent = lIdent;
	RO.lpText = m_pBuffer;
	RO.iTextLen = _MAX_PATH-1;
	RO.iOTyp = (short)m_rDBO.RetrieveObjTyp(lONr);	// ObjektTyp bestimmen
	RO.iFlags = m_iFlags & (ROHideFlags|ROShowHidden);	// voreingestellte Bits setzen
	RO.iFlags |= ROShowHidden;			// immer so tun, als ob alles anzuzeigen ist
										// damit RO.iFlags nicht rückgesetzt wird

// Rückkehrwert nicht auswerten, da an dieser Stelle bereits entschieden ist, 
// ob das Objekt dazugehört
	DEXN_QueryRechObject(RO);

// angezeigten Eintrag zusammenstellen und zu ListBox hinzufügen (keine 
// Auswertung des Rückgabewertes - s.o.)
	FormatROString (m_pBuffer1, RO);

Color C, cObjProp;

	if (RO.iOTyp == OT_KO) {	// Komplexobjekte werden DunkelGrün
		C = Color (ColorVal(128), ColorVal(0), ColorVal(0));
		cObjProp = fExistsForThisObject ? C : Color(ColorVal(64), ColorVal(0), ColorVal(0));
	} 
	else {
	COLORREF cr = GetSysColor (COLOR_WINDOWTEXT);

		C = (Color &)cr;
		cr = GetSysColor (COLOR_GRAYTEXT);
		cObjProp = fExistsForThisObject ? C : (Color &)cr;
	}

short iOTyp = OTypToBits ((ObjTyp)RO.iOTyp);
LPCSTR pcText = !(m_iFlags & ROHideText) ? m_pBuffer : g_cbNil;

	pItem -> SetInfo (iOTyp, m_pBuffer1, pcText, C, cObjProp);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// angezeigten Eintrag zusammenstellen 
inline char *EOL (char *pT) { return &pT[strlen(pT)]; }

char *FormatROString (char *pText, RECHOBJECT &rRO)
{
char cbBuffer[64];

	if ((rRO.iFlags & ROHideFlags) == 0) {		// alles anzeigen
		if (FAILED(ClassFromIdent (rRO.lIdent, cbBuffer, sizeof(cbBuffer))))
			return NULL;

#if _TRiAS_VER < 0x0300
		wsprintf (pText, "%04ld:%s:%c:", 
				  rRO.lONr, cbBuffer, cFVisTyp ((ObjTyp)rRO.iOTyp)); //, pBuffer);
#else
		wsprintf (pText, "%s:%c:", cbBuffer, cFVisTyp ((ObjTyp)rRO.iOTyp)); //, pBuffer);
#endif // _TRiAS_VER < 0x0300
		return pText;	// alles angezeigt
	}
	
// Einzelne Bestandteile bei Bedarf generieren
	*pText = '\0';

#if _TRiAS_VER < 0x0300
	if (!(rRO.iFlags & ROHideObjNr)) 	// ObjektNummer anzeigen
		wsprintf (EOL(pText), "%04ld:", rRO.lONr);
#endif // _TRiAS_VER < 0x0300

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
void ObjektInfo::ListBoxSel (ControlEvt) 
{
	if (m_pKurzInfo == NULL) return;	// nichts machen

CEierUhr Wait (GetParent()->GetParent());

	m_ulActCount = UpdateActivation();
	UpdateCaption();					// Caption dieses Fensters aktualisieren
}

ULONG ObjektInfo::UpdateActivation (int iChanged)
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
	bool isSel = !m_fIsRolledUp && m_pKurzInfo -> GetSelection (iIndex);

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

	return ulCountActive;	// liefert Anzahl der selektierten Einträge
}


// Mouse-DoppelClick auf ListBox -- vollständige ObjInfo anzeigen
void ObjektInfo::ListBoxClk (ControlEvt) 
{
	::PostMessage (m_hWnd, WM_COMMAND, IDM_ATTRIBUTE, 0);
//	ShowOIAttribute();
}


// Registrierung einer Verschiebung des Fensters durch den Nutzer
void ObjektInfo::Move (MoveEvt e) 
{
	m_ptWantedPos = e.NewOrigin();	// neue Position merken
}

///////////////////////////////////////////////////////////////////////////////
// Fenster vergrößert/verkleinert
void ObjektInfo::ReSize (ReSizeEvt e)
{
	if (NULL == m_pKurzInfo) {
//		TX_ASSERT(m_fToDelete);
		return;		// Fenster mit umgebrochenem Menu wird gerade zerlegt (oder ReSize sehr früh)
	}

// Listbox mit anpassen
	m_pKurzInfo -> LocCtrl() -> ChangeSize (e.GetNewSize());

#if !defined(WIN16)
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

		m_iCntChars = (rcBox.Width() / long(tm.tmAveCharWidth * g_dScaleX)) + 1;	// sicherheitshalber je eins mehr
		m_iCntItems = (rcBox.Height() / long(iHeight * g_dScaleY)) + 1;
	}
#endif // WIN16
}

// Routine, die vor Schließen des Dialogfenster gerufen wird ------------------
BOOL ObjektInfo::QueryClose (Event) { return locQueryClose(); }

bool ObjektInfo::locQueryClose (void)
{
#if !defined(WIN16)
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

	if (DEXN_ClosingRechObjWindow (hWnd())) {
#if !defined(WIN16)
		LeaveCriticalSection (&m_CS);
#endif // WIN16
		return false;	// nicht schließen, jemand hat was dagegen
	}
	DEXN_RechObjWindowToClose(hWnd());	// soll wirklich geschlossen werden

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
	if (fDraw) 
		DEX_ActivateAllObjects (hWnd());	// alle anderen zeichnen neu

	DEXN_RechObjWindowClosed(hWnd());	// Fenster abmelden

	m_fToDelete = true;					// Fenster kann jetzt gelöscht werden
	
#if !defined(WIN16)
	LeaveCriticalSection (&m_CS);
#endif // WIN16

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
POINT ObjektInfo::CorrectPosition (DragRectangleObject &DRO) 
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
bool ObjektInfoListe::ActivateAllObj (HWND hWnd) 
{
	return Every (RedrawActiveObj, (void *)&hWnd);
}

BOOL EXPORTTRIAS RedrawActiveObj (void *pObj, void *phWnd) 
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
	
		if (pOII -> isSelected()) {	
		// nur nochmal zeichnen 
#if !defined(_NO_ROLLUP_ORWND)
			if ((g_dwTRiASMode & TRIASMODE_RollUpORWnds) && !pOI -> m_fIsRolledUp)
#endif // !defined(_NO_ROLLUP_ORWND)
				pOI -> ActivateObj (pOII -> ONr(), fDraw, false);
		}
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
void ObjektInfoListe::BlinkAllObj (void) 
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

#if !defined(_NO_ROLLUP_ORWND)
	if ((g_dwTRiASMode & TRIASMODE_RollUpORWnds) && pOI->m_fIsRolledUp)
		return;
#endif // !defined(_NO_ROLLUP_ORWND)

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
void ObjektInfo::ActivateObj (long ON, bool fDraw, bool Flag, bool iAssoc) 
{
CONrTable t(m_rDBO.Shapes().ObjNumTree());
long tmpON = ON;
bool handleTO = true;
#if defined(WIN16)
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
	ExtShapeObjectONrLock l(t);
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
		ObjContainer ocT (rcT);
				
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
#if defined(_USE_KOMPLEX_OBJECTS)
					RelationsObjekt *pRO = (RelationsObjekt *)pESO;
					ObjektListeIterator KOI (pRO -> KO().OL());
					long ONr = KOI.FirstONr();
	
						while (ONr != -1L) {
						// untergeordnete Objekte aktivieren
							ActivateObj (ONr, fDraw, false, true);
							ONr = KOI.NextONr();
						}
#endif // defined(_USE_KOMPLEX_OBJECTS)
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
			long AssocON = AssociatedObjekt (ON, NULL);

				if (AssocON != 0) {
				short iBits = OTypToBits ((ObjTyp)DEX_GetObjectType (AssocON));

					if (m_rDBO.Idents().toPaint (m_rDBO.RetrieveIdent(AssocON), iBits)) 
						ActivateObj (AssocON, fDraw, false, false);
				}
			}
		}
			
	// Zeit stoppen, die gebraucht wurde, um alles zu markieren
		if (iFirst) {
#if defined(WIN16)
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
void ObjektInfo::DeActivateObj (bool fDraw, bool Flag, long locON, bool iAssoc) 
{
CONrTable t(m_rDBO.Shapes().ObjNumTree());
long tmpON;

	if (locON == -1) tmpON = m_lActObj;
	else tmpON = locON;

// wenn nichts mehr aktiv ist, dann raus
	if (tmpON == -1L) return;

// bei Bedarf passivieren
	if (Flag) m_lActObj = -1L;

#if defined(WIN16)
TIMERINFO TI;

	memset (&TI, '\0', sizeof(TIMERINFO));
	TI.dwSize = sizeof (TIMERINFO);
	TimerCount (&TI);

DWORD dwTicks = TI.dwmsSinceStart;
#else
DWORD dwTicks = GetTickCount();
#endif

	if (!t.Find (&tmpON)) return;	// unbekanntes Objekt

ExtShapeObjectONrLock l(t);

	TX_ASSERT(NULL != (ExtShapeObject *)l);

	if ((!Flag && locON != -1L) || m_fHighLighted) // ||
//			   (Flag && l -> isTyp() == OT_KO))) 	// über Zeitmessung abgefangen
	{
		if (fDraw) {
		// auf gesamtem Canvasbereich malen
		Window *pWnd = GetParent();
		ExtShapeObject *pESO = (ExtShapeObject *)l;
		Rectangle rcT = pWnd -> CanvasRect();
		ObjContainer ocT (rcT);
				
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
#if defined(_USE_KOMPLEX_OBJECTS)
					RelationsObjekt *pRO = (RelationsObjekt *)pESO;
					ObjektListeIterator KOI (pRO -> KO().OL());
					long ONr = KOI.FirstONr();
	
						while (ONr != -1L) {
							DeActivateObj (fDraw, false, ONr, true);
							ONr = KOI.NextONr();
						}
#endif // defined(_USE_KOMPLEX_OBJECTS)
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
			long AssocON = AssociatedObjekt (tmpON, NULL);

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
#if defined(WIN16)
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
ObjektInfoListe::ObjektInfoListe (void) 
		 : CTree (GetObjInfoKey, HWNDCmp)
{
	m_hLastActiveWnd = NULL;
}

ObjektInfoListe::~ObjektInfoListe (void) 
{
	EveryDelete();
}

void EXPORTTRIAS ObjektInfoListe::UserDelete (void *pItem)  
{
ObjektInfo *pOI = (ObjektInfo *)pItem;

	if (pOI -> hWnd() == m_hLastActiveWnd) {
		m_hLastActiveWnd = NULL;
		pOI->GetParent()->SetFocus();
	}
	pOI -> ~ObjektInfo();
}

HWND ObjektInfoListe::SetLastActive (HWND hWnd)
{
HWND hOldWnd = m_hLastActiveWnd;

	m_hLastActiveWnd = hWnd;
	return hOldWnd;
}

int HWNDCmp (void *pItem1, void *pItem2)
{
	return *(HWND *)pItem1 - *(HWND *)pItem2;
}

long ObjektInfoListe::GetSelectedObject (HWND hWnd) 
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


long ObjektInfoListe::GetAllSelectedObjects (long *plObj)
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
inline BOOL EnumSelectedObjectsCallback (BOOL (*pFcn)(long, BOOL, void *), 
					 long Key, bool iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Key, iFlag, pData);
}

BOOL ObjektInfoListe::EnumSelectedObjects (BOOL (*pFcn)(long, BOOL, void *), 
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


BOOL ObjektInfo::EnumSelectedObjects (BOOL (*pFcn)(long, BOOL, void *), 
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
inline BOOL EnumSelectedObjectsCallbackEx (BOOL (*pFcn)(long, DWORD, void *), 
					 long Key, DWORD dwData, void *pData)
{
	return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(Key, dwData, pData);
}

BOOL ObjektInfoListe::EnumSelectedObjectsEx (BOOL (*pFcn)(long, DWORD, void *), 
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


BOOL ObjektInfo::EnumSelectedObjectsEx (BOOL (*pFcn)(long, DWORD, void *), 
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
inline BOOL EnumAllObjectsCallback (BOOL (*pFcn)(long, BOOL, void *), 
				    long Key, BOOL iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Key, iFlag, pData);
}

BOOL ObjektInfo::EnumAllObjects (BOOL (*pFcn)(long, BOOL, void *), 
				   void *pData, BOOL iShowLast)
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

BOOL ObjektInfoListe::EnumAllObjects (BOOL (*pFcn)(long, BOOL, void *),
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

ulong ObjektInfoListe::CountObjects (HWND hWnd) 
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

///////////////////////////////////////////////////////////////////////////////
// Einen oder alle Objekteinträge ale Fenster neu einlesen
bool ObjektInfoListe::RefreshObjectEntries (INT_PTR lONr)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l) l -> RefreshEntry (lONr, true);
	}
	return true;
}

// Alle Fenster in Kenntnis setzen, daß eine Erweiterung geladen wurde --------
bool ObjektInfoListe::LoadExtension (Extension &E)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l) l -> LoadExtension (E);
	}
	return true;
}

// Alle Fenster in Kenntnis setzen, daß eine Erweiterung freigegeben wurde ----
bool ObjektInfoListe::UnLoadExtension (Extension &E)
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
Color ObjektInfo::SetColor (Color newC)
{
Color oldColor = m_C;

	m_C = newC;
	RePaint();
	return oldColor;
}

// Laden und entladen einer Erweiterung in einem Objektrecherchefenster -------
bool ObjektInfo::LoadExtension (Extension &E)
{
	if (E.isLoaded() == LEFullLoad && E.ORMenuHandle() != 0) {
	// Menu einhängen
	HMENU hMenu = GetSubMenu (ObjektMenu.Handle (API_MENU_HMENU), EXTRA_OBJECTMENU_POS);
	unsigned int nCount = GetMenuItemCount (hMenu);

		if (nCount == 0)
	 	// erstes ORMenu: "Extras" aktivieren
 			EnableMenuItem (ObjektMenu.Handle (API_MENU_HMENU), EXTRA_OBJECTMENU_POS, 
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

bool ObjektInfo::UnLoadExtension (Extension &E, bool iLast)
{
CTable r(m_rEL);
HMENU hMenu = GetSubMenu (ObjektMenu.Handle (API_MENU_HMENU), EXTRA_OBJECTMENU_POS);
int oldMenuIndex = -1;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;
		if (E.ExtName() == l -> ExtName()) {
		// Erweiterung gefunden

			if (l -> ORMenuIndex() >= 0 && l -> ORMenuHandle() != 0) 
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
	if (0 == GetMenuItemCount(hMenu)) 
		EnableMenuItem (ObjektMenu.Handle (API_MENU_HMENU), EXTRA_OBJECTMENU_POS, MF_BYPOSITION|MF_GRAYED);

	DrawMenuBar (m_hWnd);
	return true;
}

// Liefert die Anzahl der Objekte in dieser ListeBox --------------------------
ulong ObjektInfo::GetCount (void)
{ 
	return m_pKurzInfo ? m_pKurzInfo -> LocControl() -> GetCount() : 0; 
} 

// liefert den Index eines bestimmten Objektes in dieser Liste
int ObjektInfo::FindObject (long lONr)
{
CScopeVar<CMPONRPROC> proc (m_pCmpProc, NULL);	// wirklich Objektnummern vergleichen

	return m_pKurzInfo ? m_pKurzInfo -> FindItem (reinterpret_cast<void *>(lONr)) : -1;
}

// Alle Fenster in Kenntnis setzen, daß ein MenuPunkt installiert wurde -------
HMENU ObjektInfoListe::InstallMenuItem (short iMenuID, short iMenuNum, short iMenuPos, char *pText)
{
CTable t(*this);
HMENU hMenu = NULL;

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l) 
			hMenu = l -> InstallMenuItem (iMenuID, iMenuNum, iMenuPos, pText);
	}
	return hMenu;
}

HMENU ObjektInfoListe::InstallMenuItem (short iMenuNum, char *pText, HMENU hMenu, bool fTopLevel)
{
CTable t(*this);
HMENU hRetMenu = NULL;

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l) 
			hRetMenu = l -> InstallMenuItem (iMenuNum, pText, hMenu, fTopLevel);
	}
	return hRetMenu;
}

// Alle Fenster in Kenntnis setzen, daß eine Erweiterung freigegeben wurde ----
bool ObjektInfoListe::RemoveMenuItem (short iMenuID, short iMenuNum)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		TX_ASSERT(NULL != (ObjektInfo *)l);
		if (!l -> RemoveMenuItem (iMenuID, iMenuNum))
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Ein neues MenuItem in diesem Fenster einhängen 
HMENU ObjektInfo::InstallMenuItem (short iMenuID, short iMenuNum, short iMenuPos, char *pText, UINT *puiPos)
{
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);

	if (-1 == iMenuNum)
		iMenuNum = GetMenuItemCount(hMenu)-1;

HMENU hSubMenu = GetSubMenu (hMenu, iMenuNum);

	if (hSubMenu == 0) return 0;

// überprüfen, ob dieser Punkt der erste zusätzliche für dieses SubMenu ist
bool fInsertedSeparator = false;

	if (-1 == iMenuPos && iMenuNum != GetMenuItemCount (hMenu)-1) {
	// aber nur, wenns nicht das letzte Popup ist und am Ende eingefügt werden soll
	Menu TestMenu (OBJMENU);	// Menu für VergleichsZwecke
	HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
	HMENU hTestSubMenu = GetSubMenu (hTestMenu, iMenuNum);

		if (GetMenuItemCount (hTestSubMenu) == GetMenuItemCount (hSubMenu)) {
		// wenn es der erste ist, dann Separator einfügen
			InsertMenu (hSubMenu, (UINT)-1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
			fInsertedSeparator = true;
		}
	}

	if (NULL != pText) 
		InsertMenu (hSubMenu, (UINT)iMenuPos, MF_BYPOSITION|MF_STRING, iMenuID, pText);
	else if (/*-1 == iMenuPos && */!fInsertedSeparator) {
	// ggf. Separator einfügen
		InsertMenu (hSubMenu, /*(UINT)-1*/iMenuPos, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
		if (NULL != puiPos)
			*puiPos = GetMenuItemCount(hSubMenu)-1;		// Position fürs herauslösen speichern
	}
	DrawMenuBar (m_hWnd);
	return hSubMenu;
}

HMENU ObjektInfo::InstallMenuItem (short iMenuNum, char *pText, HMENU hPopMenu, bool fTopLevel, UINT *puiPos)
{
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);

	if (-1 == iMenuNum)
		iMenuNum = GetMenuItemCount(hMenu)-1;

	if (!fTopLevel) {
	HMENU hSubMenu = GetSubMenu (hMenu, iMenuNum);

		if (NULL == hSubMenu) return NULL;

	// überprüfen, ob dieser Punkt der erste zusätzliche für dieses SubMenu ist
	Menu TestMenu (OBJMENU);	// Menu für VergleichsZwecke
	HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
	HMENU hTestSubMenu = GetSubMenu (hTestMenu, iMenuNum);

	// wenn es der erste ist, dann Separator einfügen
		if (GetMenuItemCount (hTestSubMenu) == GetMenuItemCount (hSubMenu))	
			InsertMenu (hSubMenu, (UINT)-1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);

		InsertMenu (hSubMenu, (UINT)-1,	MF_BYPOSITION|MF_POPUP, (UINT_PTR)hPopMenu, pText);

		if (NULL != puiPos)
			*puiPos = GetMenuItemCount(hSubMenu)-1;		// Position fürs herauslösen speichern

		hMenu = hSubMenu;

	} else 
		InsertMenu (hMenu, iMenuNum, MF_BYPOSITION|MF_POPUP, (UINT_PTR)hPopMenu, pText);

	DrawMenuBar (m_hWnd);
	return hMenu;
}

bool ObjektInfo::RemoveMenuItem (short iMenuID, short iMenuNum)
{
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);

	if (-1 == iMenuNum)
		iMenuNum = GetMenuItemCount(hMenu)-1;

HMENU hSubMenu = GetSubMenu (hMenu, iMenuNum);

	if (hSubMenu == 0) return false;

	if (!RemoveMenu (hSubMenu, iMenuID, MF_BYCOMMAND)) {
		TX_ASSERT(false);
		return false;
	}
	
// wenn dieser Punkt der letzte zusätzliche in diesem SubMenu war, dann
// noch den Separator rausnehmen
	if (iMenuNum != GetMenuItemCount (hMenu)-1) {
	// aber nur, wenns nicht das letzte Popup ist
	Menu TestMenu (OBJMENU);	// Menu für VergleichsZwecke
	HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
	HMENU hTestSubMenu = GetSubMenu (hTestMenu, iMenuNum);
	short iLast = GetMenuItemCount (hSubMenu);

		if (GetMenuItemCount (hTestSubMenu) == iLast)		// nicht '-1', da wir schon einen rausgelöscht haben
		// wenn es der letzte war, dann Separator löschen
			RemoveMenu (hSubMenu, iLast, MF_BYPOSITION);
	}
	DrawMenuBar (m_hWnd);
	return true;
}

pWindow ObjektInfoListe::GetORWindow (HWND hWnd)
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

HWND ObjektInfoListe::GetActiveORWindow (void)
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

HWND ObjektInfoListe::SetActiveORWindow (HWND hWnd)
{
CTable t (*this);
HWND hWndOld = GetActiveORWindow();

// Feststellen, ob ein Fenster den Focus hat
bool fHasFocus = false;

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && l -> m_fHasFocus)
			fHasFocus = true;
	}

	if (fHasFocus) {
		if (hWndOld != hWnd) 
			::SetFocus (hWnd);
	} else
		m_hLastActiveWnd = hWnd;

	return hWndOld;
}

// Alle fenster auffordern, dieses Objekt rauszunehmen ------------------------
bool ObjektInfoListe::HandleDeleteObject (long lONr)
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
bool ObjektInfoListe::HandleModifyIdent (long lONr)
{
CTable t (*this);
long lIdent = DEX_GetObjIdent (lONr);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		if (l && !l -> m_fToDelete) {
			if (!l -> HandleModifyIdent (lONr, lIdent, 0L, false, true))
				return false;
			l -> RePaint();		// neu zeichnen
		}
	}
	return true;
}

bool ObjektInfoListe::HandleCancelMode (bool fCmd)
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

bool ObjektInfo::HandleCancelMode (bool fCmd)
{
	m_fCmd = fCmd;
	return true;
}

void ObjektInfoListe::Enable (bool fEnable)
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
			l -> HandleModifyFeature (lONr, pcName);
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
inline BOOL EnumORWindow (BOOL (*pFcn)(long, BOOL, void *), 
			  HWND hWnd, BOOL iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)((LONG)(void *)hWnd, iFlag, pData);
}

BOOL ObjektInfoListe::EnumORWindows (ENUMNOKEYLONG *pK)
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

inline BOOL EnumORIdents (BOOL (*pFcn)(long, BOOL, void *), 
			  long Key, BOOL iFlag, void *pData)
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Key, iFlag, pData);
}

inline BOOL EnumORIdentsEx (BOOL (*pFcn)(long, DWORD, void *), 
			    long Key, DWORD iOTypes, void *pData)
{
	return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(Key, iOTypes, pData);
}

}	// extern "C" 

BOOL ObjektInfo::EnumIdents (BOOL (*pFcn)(long, BOOL, void *), 
			       void *pData, BOOL fSelected, BOOL fWithOTypes)
{
// Identifikatoren in einem Baum aufsammeln und dann Enumerieren
CORIdents Ids;

	{
	CTable t (OITree());	// Baum aller Objekte im Fenster
	
		for (t.First(); t.Valid(); t.Next()) {
		ObjInfoItemLock l(t);

			if (!l) continue;
			
//        ObjInfoItem *pItem = (ObjInfoItem *)l;
		long lONr = l -> ONr();
		int iIndex = FindObject (lONr);
		bool fIsSel = m_pKurzInfo -> GetSelection (iIndex);
		
			if (fSelected && !fIsSel) continue;
			
		long lIdent = DEX_GetObjIdentEx(lONr);
		CORIdent *pId = NULL;
		short iOType = l -> GetOType();
		
			if ((pId = Ids.FFindItem ((ULONG &)lIdent)) == NULL) {
				if (!Ids.FAddItem ((ULONG &)lIdent, iOType))
					break;
			} else if (fWithOTypes)
				pId -> FMergeOTypes (iOType);
		}
	}
	
// Enumeration der gefundenen Identifikatoren
bool fResult = true;

	if (fWithOTypes) {	// ObjektTypen liefern
	CTable t (Ids);
	
		for (t.First(); t.Valid(); t.Next()) {
		CORIdentLock l(t);		
//		CORIdent *pId = (CORIdent *)l;

			if (EnumORIdentsEx ((ENUMNOKEYLONGEXPROC)pFcn, l -> FGetULONG(), 
					    l -> FGetOTypes(), pData) == false) 
			{
				fResult = false;
				break;	// abbrechen
			}
		}
	} else {
	// normale Enumeration
	CTable t (Ids);
	
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
	return fResult;
}

//////////////////////////////////////////////////////////////////////////////
// Objektarten zählen
namespace {
    BOOL CALLBACK
    EnumObjectsQueryCount (HOBJECT lONr, BOOL iFlag, void *pData)
    {
    IDENTOBJECTCOUNTEX *pIOC = reinterpret_cast<IDENTOBJECTCOUNTEX *>(pData);
    BOOL retval = TRUE;

        if (INVALID_HOBJECTS == pIOC->ulIdent ||
            pIOC->ulIdent == DEX_GetObjIdentEx(lONr)) 
        {
            ObjTyp rgType = (ObjTyp)DEX_GetObjectType(lONr);
            if (pIOC->iOTypes & OTypToBits(rgType)) {
                switch(rgType) {
                case OGPunkt:   ++pIOC->lPoints;    break;
                case OGLinie:   ++pIOC->lLines;     break;
                case OGFlaeche: ++pIOC->lAreas;     break;
                case OGText:    ++pIOC->lTexts;     break;
                case OGKO:      ++pIOC->lComplex;   break;
                default:
                    break;                    
                }
            }
        }
        return retval;
    }
}

LONG ObjektInfo::QueryObjectCount(IDENTOBJECTCOUNT *pData)
{
	TX_ASSERT_POINTER(pData, IDENTOBJECTCOUNT);
	TX_ASSERT(sizeof(IDENTOBJECTCOUNT) == pData -> dwSize || 
        sizeof(IDENTOBJECTCOUNTEX) == pData -> dwSize);
    TX_ASSERT(INVALID_HOBJECTS == pData->ulIdent || IsValidIdent(pData->ulIdent));
    TX_ASSERT(0 == (pData->iOTypes & ~OBJECTTYPE_All));

    if (sizeof(IDENTOBJECTCOUNT) == pData -> dwSize) {
    // lediglich Gesamtanzahl liefern
    IDENTOBJECTCOUNTEX IOC;

        INITSTRUCT(IOC, IDENTOBJECTCOUNTEX);
        IOC.iOTypes = pData->iOTypes;
        IOC.ulIdent = pData->ulIdent;

    ENUMLONGKEY ELK;

        ELK.eFcn = reinterpret_cast<ENUMLONGKEYPROC>(EnumObjectsQueryCount);
        ELK.eKey = reinterpret_cast<HGENERIC>(hWnd());
        ELK.ePtr = reinterpret_cast<void *>(&IOC);
        if (DEX_EnumAllORObjects(ELK)) {
            return IOC.lPoints + IOC.lLines + IOC.lAreas + 
                IOC.lTexts + IOC.lComplex;
        }
        return 0;
    }

// alle geforderte Objekttypen zählen
IDENTOBJECTCOUNTEX *pDataEx = (IDENTOBJECTCOUNTEX *)pData;
ENUMLONGKEY ELK;

    ELK.eFcn = reinterpret_cast<ENUMLONGKEYPROC>(EnumObjectsQueryCount);
    ELK.eKey = reinterpret_cast<HGENERIC>(hWnd());
    ELK.ePtr = reinterpret_cast<void *>(pDataEx);
    if (DEX_EnumAllORObjects(ELK)) {
        return pDataEx->lPoints + pDataEx->lLines + pDataEx->lAreas + 
            pDataEx->lTexts + pDataEx->lComplex;
    }
    return 0;
}

void ObjektInfoListe::CloseORWindow (HWND hWnd)
{
CTable t (*this);

	if (t.Find (&hWnd)) {
	bool fToDelete = false;

		{
		ObjektInfoLock l(t);

			TX_ASSERT(NULL != (ObjektInfo *)l);

			if (l && !l -> m_fToDelete) {
				if (l -> m_lCommandActive > 0) 
					l -> m_fMustDestroy = true;		// später zerlegen
				else
					fToDelete = true;				// jetzt zerlegen
			}
		} // Lock goes out of scope
		
		if (fToDelete) 
			t.Delete();		// Fenster freigeben
	}
}

#if !defined(WIN16) && !defined(_OLD_DRAGNDROP)
bool ObjektInfo::IsDropSourceInst (void)
{ 
	return EL().IsDropSource(); 
}

bool ObjektInfo::IsDropSourceORWnd (void)
{ 
	return NULL != DEX_GetDropSourceORWnd(); 
}

HWND ObjektInfoListe::GetDropSourceORWnd()
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);

		TX_ASSERT(NULL != (ObjektInfo *)l);
		if (!l) continue;

		if (l -> IsDropSource())
			return l -> hWnd();		// dieses Fenster ist DragSource
	}
	return NULL;					// keines der Fenster ist DragSource
}

#endif // WIN16
