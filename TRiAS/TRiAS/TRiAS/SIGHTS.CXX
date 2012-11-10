// Memberfunktionen von DatenBasisObjekt zu Ansichten
// File: SIGHTS.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <ScopeVar.h>

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include <Com/Thunk.h>

#include "identsel.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"

#include "viewtree.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern ExtDirisWindow *CurrActDirisW;
extern CLegendeClientWindow *pLegende;
extern bool LegendToRepaint;
extern bool LegendeCFlag;
extern bool g_fSystemSightFlag;
extern bool g_fDrawTextObjs;			// TextObjekte zeichnen
extern DWORD g_iHideFlags;

extern HPALETTE hPalette;

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASRelations);
DefineSmartInterface(TRiASProperties);

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen 
// Sichtmenu initialisieren, wird bei OpenDB gerufen 
bool DatenBasisObjekt::InitSightMenu (pMenu pM, bool fStandard) 
{
// Namen der Ansichten holen
//	DeleteAllSightItems (pM);	// bisherige Ansichten löschen
	DELETE_OBJ (m_pViews);

#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		m_pViews = CViewsTree::CreateInstance (DB());
	} else
#endif // _USE_LEGACY_CODE
	{
		m_pViews = CViewsTree::CreateInstance (m_Prj);
	}
	if (NULL == m_pViews) 
		return false;	// Fehler

	if (0 == m_pViews -> Count()) 
		return false;	// keine Ansichten da

// PopupMenu aufbauen
CTable t(*m_pViews);
bool fDraw = false;
UINT uiID = 0;

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

	// Item in Menu eintragen
		fDraw = AddItemToSightMenu (GetViewWindow()->GetFrame(), pM, (l -> FGetstring()).c_str(), uiID);
		l -> SetInMenu (uiID > 0 ? true : false);

	// evtl. Standard voreinstellen
		if (fStandard && l -> isDefaultView()) 
			ProcessMenuEvent ((l -> FGetstring()).c_str(), false, true);
	}
	return fDraw;
}

bool DatenBasisObjekt::AddItemToSightMenu (Window *pWnd, pMenu pM, 
	LPCSTR pcView, LPCSTR pcConnFilter)
{
	TX_ASSERT (m_pViews);

UINT uiID = 0;
bool fDraw = false;

#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		m_pViews -> FAddItem (pcView);
		fDraw = AddItemToSightMenu (pWnd, pM, pcView, uiID);
		m_pViews -> SetInMenu (pcView, uiID > 0 ? true : false);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (m_pViews -> FAddView (pcView)) {	// __[View] nicht einhängen
			m_pViews -> SetConnectionFilter(pcView, pcConnFilter);	// #HK030318
			fDraw = AddItemToSightMenu (pWnd, pM, pcView, uiID);
			m_pViews -> SetInMenu (pcView, uiID > 0 ? true : false);

		// StartAnsicht einstellen
			if (m_pViews -> isDefaultView (pcView)) {
				ProcessMenuEvent (pcView, 
					!(NULL == pcConnFilter || 0 == pcConnFilter[0]), true);
			}
		}
	}
	return fDraw;
}

///////////////////////////////////////////////////////////////////////////////
// Räumliche Filter verwalten
bool DatenBasisObjekt::GetViewConnectFilter(LPCSTR pcView, LPSTR pConnFilter, int iLen)
{
	return m_pViews -> GetConnectionFilter(pcView, pConnFilter, iLen);
}

bool DatenBasisObjekt::SetViewConnectFilter(LPCSTR pcView, LPCSTR pcConnFilter)
{
	return m_pViews -> SetConnectionFilter(pcView, pcConnFilter);
}

bool DatenBasisObjekt::AddItemToSightMenu (
		Window *pWnd, pMenu pM, const char *pcItem, unsigned int &ruiID) 
{
// Ansicht muß schon im Baum drinsein
	TX_ASSERT (m_pViews);
	TX_ASSERT (m_pViews -> FFindItem (pcItem));	

// evtl. PopupMenu aufbauen und einhängen
	if (NULL == _SightMenu) {
		TX_TRY(_SightMenu = new Menu);     	// SubMenu erzeugen
		_SightFlag = false;             	// erstes Mal
		if (NULL == _SightMenu) {
			ruiID = 0;
			return false;					// Fehler, kein Menu verfügbar
		}
	}

MENUCHANGED MC;

	INITSTRUCT(MC, MENUCHANGED);
	MC.hWnd = pWnd -> Handle(API_WINDOW_HWND);
	MC.hMenu = pM -> Handle(API_MENU_HMENU);
	MC.fPopupMenu = TRUE;

	if (!DEXN_ChangingMenu(MC)) {
	// neues MenuItem einhängen, wenn noch Platz ist und es noch nicht drin ist
	HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);
	int iCnt = GetMenuItemCount (hMenu);
	bool fDrawMenuBar = false;

		if (0 == iCnt && !_SightFlag) {			// PopupMenu einklinken
		ResString resItem (IDS_SELSIGHT, 30);

			pM -> InsertItem (SightMenu(), resItem, IDM_SELOBJ);
			_SightFlag = true;
			fDrawMenuBar = true;
		}

		if (iCnt > MAXSHOWNVIEWS) {
			ruiID = 0;
			TX_ASSERT(!fDrawMenuBar);
			return false;	// kein Platz mehr
		}
		
		if (MAXSHOWNVIEWS == iCnt) {
		ResString resMoreViews (IDS_MOREVIEWS, 32);

			SightMenu() -> AppendSeparator();
			SightMenu() -> AppendItem (IDM_SIGHTS+MAXSHOWNVIEWS, resMoreViews);
			ruiID = 0;				// nicht hinzugefügt

			DEXN_MenuChanged(MC);	// Vollzug melden
			return true;			// evtl. DrawMenuBar
		}

	// testen, ob diese Sicht bereits im Menu ist
	char cbMenuItem[MAXVIEWNAMESIZE+1];
	int i = 0;

		for (/**/; i < iCnt; i++) {
			GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
						  sizeof(cbMenuItem), MF_BYCOMMAND);
			if (!strcmp (cbMenuItem, pcItem)) {
				ruiID = IDM_SIGHTS+i;	// existiert bereits
				return fDrawMenuBar;	// evtl. kein DrawMenuBar
			}
		}

	// dieser MenuPunkt existiert noch nicht 
		SightMenu() -> AppendItem (IDM_SIGHTS+i, pcItem);
		ruiID = IDM_SIGHTS+i;

		DEXN_MenuChanged(MC);		// Vollzug melden
		return true; 				// evtl. DrawMenuBar
	}
	return false;
}

// Sicht mit Checkmark versehen und als aktiv kennzeichnen --------------------
bool DatenBasisObjekt::CheckItemAsActive (LPCSTR pcView)
{
	TX_ASSERT (m_pViews);

	m_pViews -> SetActView (pcView, true);

HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);
int iCnt = GetMenuItemCount (hMenu);

// Sichteintrag markieren, wenn er im Menu ist
char cbMenuItem[MAXVIEWNAMESIZE+1];

	iCnt = min((UINT)iCnt, MAXSHOWNVIEWS);
	for (int i = 0; i < iCnt; i++) {
		GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
				      sizeof(cbMenuItem), MF_BYCOMMAND);
		if (!strcmp (cbMenuItem, pcView)) {
			SightMenu() -> CheckItem (IDM_SIGHTS+i);
			return true;
		}
	}

// Sichteintrag ist nicht im Menu: letzte Sicht im Menu austauschen
	if (MAXSHOWNVIEWS == iCnt) {
		GetMenuString (hMenu, IDM_SIGHTS+MAXSHOWNVIEWS-1, cbMenuItem, 
				      sizeof(cbMenuItem), MF_BYCOMMAND);

		if (ModifyMenu (hMenu, IDM_SIGHTS+MAXSHOWNVIEWS-1,
			    MF_BYCOMMAND|MF_STRING|MF_CHECKED, 
			    IDM_SIGHTS+MAXSHOWNVIEWS-1, pcView))
		{
			m_pViews -> SetInMenu (cbMenuItem, false);
			m_pViews -> SetInMenu (pcView, true);
			return true;
		}
	}
	return false;
}

// alte Sicht als inaktive kennzeichnen und Checkmark entfrnen ----------------
bool DatenBasisObjekt::UnCheckItemAsActive (void)
{
	TX_ASSERT (m_pViews);

char cbItem[MAXVIEWNAMESIZE+1];

	if (!GetActiveSightName (cbItem, sizeof(cbItem)))
		return false;

	m_pViews -> SetActView (cbItem, false);		// keine mehr aktiv

HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);
int iCnt = GetMenuItemCount (hMenu);
char cbMenuItem[MAXVIEWNAMESIZE+1];

	iCnt = min((UINT)iCnt, MAXSHOWNVIEWS);
	for (int i = 0; i < iCnt; i++) {
		GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
				      sizeof(cbMenuItem), MF_BYCOMMAND);
		if (!strcmp (cbMenuItem, cbItem)) {
			SightMenu() -> unCheckItem (IDM_SIGHTS+i);
			return true;
		}
	}
	return false;
}

// Gesamtes Ansichtmenu löschen und freigeben ---------------------------------
bool DatenBasisObjekt::DeleteAllSightItems (Window *pWnd, pMenu pM) 
{
	if (NULL == SightMenu()) return false;

	TX_ASSERT (m_pViews);

MENUCHANGED MC;

	INITSTRUCT(MC, MENUCHANGED);
	MC.hWnd = pWnd -> Handle(API_WINDOW_HWND);
	MC.hMenu = pM -> Handle(API_MENU_HMENU);
	MC.fPopupMenu = TRUE;

	if (!DEXN_ChangingMenu(MC)) {
	int iCnt = GetMenuItemCount (SightMenu() -> Handle (API_MENU_HMENU));

	// alle Sichteinträge löschen
		for (int i = 0; i < iCnt; i++)
			SightMenu() -> DeleteItem (IDM_SIGHTS+i);

	// SubMenu rauslöschen, Eintrag rausnehmen, Menu freigeben
		::RemoveMenu (::GetSubMenu (pM -> Handle (API_MENU_HMENU), THEMA_MENU_POS), 0, MF_BYPOSITION);

		DELETE_OBJ (_SightMenu);
		DEXN_MenuChanged(MC);
		return true;
	}
	return false;
}

// Einen Eintrag aus dem AnsichtenMenu herausnehmen. Im ViewTree muß die Ansicht
// aber noch drin sein.
bool DatenBasisObjekt::DeleteSightMenuItem (Window *pWnd, pMenu pM, LPCSTR pcItem) 
{
	if (NULL == SightMenu()) return false;

	TX_ASSERT (m_pViews);
	if (!m_pViews -> FFindItem (pcItem))
		return false;			// bereits gelöscht

HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);
int iCnt = GetMenuItemCount (hMenu);

	if (0 == iCnt) return false;	// ist bereits leer

// Eintrag im Menu suchen
char cbMenuItem[MAXVIEWNAMESIZE+1];
bool fDrawMenuBar = false;
int i = 0;

	iCnt = min((UINT)iCnt, MAXSHOWNVIEWS);
	for (/**/; i < iCnt; i++) {
		GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
				      sizeof(cbMenuItem), MF_BYCOMMAND);
		if (!strcmp (cbMenuItem, pcItem))
			break;
	}

// wenn gefunden, dann löschen
MENUCHANGED MC;

	INITSTRUCT(MC, MENUCHANGED);
	MC.hWnd = NULL != pWnd ? pWnd -> Handle(API_WINDOW_HWND) : NULL;
	MC.hMenu = NULL != pM ? pM -> Handle(API_MENU_HMENU) : NULL;
	MC.fPopupMenu = TRUE;

bool fChangeMenu = false;

	if (NULL != pWnd && NULL != pM) 
		fChangeMenu = DEXN_ChangingMenu(MC);

	if (!fChangeMenu) {
		if (i < iCnt) {
			if (m_pViews -> isActView (cbMenuItem)) 
				m_pViews -> SetActView (cbMenuItem, false);

			SightMenu() -> DeleteItem (IDM_SIGHTS+i);
			fDrawMenuBar = true;

		// nächste UnterPunkte nachziehen
			++i;
			while (i < iCnt) {
				GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
							  sizeof(cbMenuItem), MF_BYCOMMAND);
				ModifyMenu (hMenu, IDM_SIGHTS+i, MF_BYCOMMAND,
						   IDM_SIGHTS+i-1, cbMenuItem);
				++i;    // nächster Eintrag
			}

		// evtl. leer gewordenen Platz neu besetzen
			if (MAXSHOWNVIEWS < m_pViews -> Count()) {
			string strNext;

				if (m_pViews -> GetNext (strNext)) {
					InsertMenu (hMenu, MAXSHOWNVIEWS-1, MF_BYPOSITION, 
							IDM_SIGHTS+MAXSHOWNVIEWS-1, strNext.c_str());
					m_pViews -> SetInMenu (strNext.c_str(), true);
					fDrawMenuBar = true;
				}
				if (MAXSHOWNVIEWS+1 == m_pViews -> Count()) {	// 'Weite Ansichten ...' entfernen
					DeleteMenu (hMenu, MAXSHOWNVIEWS, MF_BYPOSITION);
					DeleteMenu (hMenu, IDM_SIGHTS+MAXSHOWNVIEWS, MF_BYCOMMAND);
					fDrawMenuBar = true;
				}
			}
		}

	// wenn Submenu jetzt leer ist, dann löschen des Unterpunktes
		if (0 == GetMenuItemCount (hMenu) && NULL != pM) {	// wenn PopUpMenu leer geworden ist, dann löschen
			::RemoveMenu (::GetSubMenu (pM -> Handle (API_MENU_HMENU), THEMA_MENU_POS), 0, MF_BYPOSITION);
			DELETE_OBJ (_SightMenu);
			fDrawMenuBar = true;
		}

		if (NULL != pWnd && NULL != pM) 
			DEXN_MenuChanged(MC);		// Vollzug melden
	}

// jetzt den Eintrag aus dem Baum entfernen
	m_pViews -> FDeleteItem (pcItem);	// aus Baum löschen
	return fDrawMenuBar;
}

bool DatenBasisObjekt::ProcessMenuEvent (UINT uiMenuID) 
{
	if (SightMenu() == NULL) return false;

	if (uiMenuID < IDM_SIGHTS || uiMenuID >= IDM_SIGHTS+MAXSHOWNVIEWS)
		return false;		// nicht für uns

char cbMenuItem[SIGHTMENUITEM+1];	// Name der neuen Sicht
HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);

	if (GetMenuString (hMenu, uiMenuID, cbMenuItem, sizeof(cbMenuItem), MF_BYCOMMAND) > 0)
		return ProcessMenuEvent (cbMenuItem, false, true);
	return false;
}

bool DatenBasisObjekt::ProcessMenuEvent (LPCSTR pcView, bool fForce, 
	bool fNotify) 
{
	if (SightMenu() == NULL) return false;

char cbMenuString[SIGHTMENUITEM+1];	// Name der neuen Sicht
char *pNewView = (NULL != pcView) ? (LPSTR)pcView : cbMenuString;

	GetActiveSightName (cbMenuString, sizeof(cbMenuString));

// evtl. als DefaultSicht setzen
	if (GetKeyState (VK_CONTROL) < 0 && !fForce) 
		DEX_SetDefaultView(pNewView);

// eine Ansicht wurde ausgewählt
bool fNew = strcmp (cbMenuString, pNewView);

	if (NULL == pcView || '\0' == *pNewView) {
		fForce = true;	// keine Sicht: also immer neu generieren
		fNotify = false;
	}
	if (!fForce && !fNew) 
		return false;	// bereits aktive Ansicht wurde gewählt

	if (fNotify) {
		if (DEXN_SightToSelect (pNewView))
			return false;		// jemand hat was dagegen
	}
	if (fNew) 
		DEX_RemoveAllORWnds();	// alle ORFenster weg, wenn neue Sicht

	if (!ActivateSight (pNewView))		// Sicht auswählen
		return false;

	if (fNotify) 
		DEXN_SightSelected (pNewView);

// Identifikatorbaum von nicht mehr benötigten temporären Idents bereinigen
	RemoveTempIdents();
	CIdentifikator::ReleaseIgnoreTree();		// statische Funktion

	TX_ASSERT(NULL != m_pViewWnd);
	m_pViewWnd -> SetShouldRedraw();
	DEX_ReReadCaption();

	return true;    // ok, neue Ansicht aktiv
}

// aktivieren einer vorgebebenen Sicht ----------------------------------------
extern void EXPORTTRIAS ResetPaintFlag (void *pObj);

///////////////////////////////////////////////////////////////////////////////
// für alle Datenquellen einen neuen räumlichen Filter setzen
BOOL DatenBasisObjekt::EnumConnectionsForConnFilter(long hPr, BOOL, void *pData)
{
char cbDataSourceName[_MAX_PATH];

	if (!DEX_GetDataSourceShortName(reinterpret_cast<HPROJECT>(hPr), cbDataSourceName))
		return FALSE;

GETATTACHEDCONNECTIONFILTER GACF;

	INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
	GACF.pcConnName = cbDataSourceName;

ATTACHCONNECTIONFILTER ACF;

	INITSTRUCT(ACF, ATTACHCONNECTIONFILTER);
	ACF.pcConnName = cbDataSourceName;

	if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF))) 
		DEX_DetachConnectionFilter(ACF);	// bestehenden Filter herauslösen

	if (NULL != pData) {
		ACF.pcName = (char const *)pData;
		return SUCCEEDED(DEX_AttachConnectionFilter(ACF));
	}
	return TRUE;
}

BOOL DatenBasisObjekt::SetAllConnectionFilters(LPCSTR pcConnFilter)
{
ENUMNOKEYLONG ENK;
CStdThunkImpl<DatenBasisObjekt, ENUMNOKEYLONGPROC> 
	Thunk(this, &DatenBasisObjekt::EnumConnectionsForConnFilter);

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = (void *)pcConnFilter;
	return DEX_EnumDataSourceHandles(ENK);
}

BOOL DatenBasisObjekt::GetConnectionFilter (LPCSTR pcView , LPSTR pConnFilter, int iLen)
{
	_ASSERTE(NULL != m_pViews);
	return m_pViews->GetConnectionFilter(pcView, pConnFilter, iLen);
}

BOOL DatenBasisObjekt::SetConnectFilter(LPCSTR pcView, LPCSTR pcConnFilter)
{
	_ASSERTE(NULL != m_pViews);
	return m_pViews->SetConnectionFilter(pcView, pcConnFilter);
}

bool DatenBasisObjekt::ActivateSight (char *pSight)
{
CActDB ActDB (DB());	// GeoDB aktivieren
// CEierUhr Wait (CurrActDirisW);

// bisherigen Ansichtsnamen besorgen
char cbActView[MAXVIEWNAMESIZE+1] = { 0 };
char cbOldConnFilter[_MAX_PATH];

	GetActiveSightName (cbActView, sizeof(cbActView));

// alte Ansicht unmarkieren
	UnCheckItemAsActive();	
	if (NULL == pSight) {
		if (GetViewConnectFilter(cbActView, cbOldConnFilter, sizeof(cbOldConnFilter))) 
			SetAllConnectionFilters(NULL);
		return false;
	}

// temporäre Idents rauswerfen
	ResetLoadedRects();
	DeleteTempIdents();
	SetActiveSightName (pSight);
	ResetIdentScaleMCodes (true);

	if ('\0' == *pSight) 
		return true;	// temporäre Ansicht
		
// evtl. räumlichen Filter voreinstellen
bool fMustRebuild = false;

#if _TRiAS_VER < 0x0510
	if (g_dwVer51) 
#endif // _TRiAS_VER < 0x0510
	{
	char cbConnFilter[_MAX_PATH];

		if (GetViewConnectFilter(pSight, cbConnFilter, sizeof(cbConnFilter))) {
			SetAllConnectionFilters(cbConnFilter);

			if (GetViewConnectFilter(cbActView, cbOldConnFilter, sizeof(cbOldConnFilter)))
				fMustRebuild = fMustRebuild || strcmp(cbConnFilter, cbOldConnFilter);
			else
				fMustRebuild = true;
		}
		else if (GetViewConnectFilter(cbActView, cbOldConnFilter, sizeof(cbOldConnFilter))) {
			fMustRebuild = true;
			SetAllConnectionFilters(NULL);
		}
	}

	if (fMustRebuild) {
		DEXN_ReReadIdents();
		DEXN_ReReadContainer();
		DEXN_ReScale();
	}

short Cnt = 0;
long *Id = NULL;
short *pVTypes = NULL;

	Idents().IdentTree().Every (ResetPaintFlag);	// alle Idents deAktivieren
	Idents().PrioTree().EveryDelete();				// Prioritäten werden neu aufgebaut

	ClipRegionONr() = GetClipRegionONr(pSight);	// ClippingObjekt

	if (!GetViewIdents (pSight, &Id, Cnt, &pVTypes))
		return false;
	if (Cnt == 0)                   // kein Eintrag oder Fehler
		return false;

// Palette neu generieren
	if (hPalette != NULL) 		// alte Palette freigeben
		DeleteObject (hPalette);
	hPalette = GetViewPalette(pSight, Id, Cnt, pVTypes);

	DEXN_SetNewPalette (hPalette);

// einzelne Idents aktivieren, das kann eine Weile dauern
CIdentObjects *pObjs = NULL;

	{
	// für gegebene Id's Paintflag wieder setzen
	CTable tID(Idents().IdentTree());
	VisInfo *pVI[4];
	bool oldLoadInfo = false;
	bool allLoaded = false;
	bool fMovedAway = false;
	short iOldOTypes = 0;
	long lPCnt = 0, lLCnt = 0, lFCnt = 0, lTCnt = 0, lKCnt = 0;
	
		for (int i = 0; i < Cnt; i++) {
//		ErrCode EC;
		short iDBOTypes = 0;

			pObjs = NULL;
		// doppelte Identbehandlung verhindern (nur 1. verwerten)
			if (FindLong (Id, Cnt, Id[i]) != i) continue;

		// wenn dieser Id in der DB nicht existiert, dann weiter
			if (!Idents().FindId (Id[i], NULL, &iDBOTypes)) 
				continue;
			if (iDBOTypes & TPKO) iDBOTypes |= TPAll;
			
			memset (pVI, '\0', 4 * sizeof(VisInfo *));

		// wenn Id in DB exitiert, dann neue VI laden etc.
			if (tID.Find(&Id[i])) {
			CIdentifikatorLock l(tID);

				if (l) {
				CIdentifikator *pId = (CIdentifikator *)l;
				
					oldLoadInfo = pId -> loaded();
					allLoaded = pId -> AreAllLoaded();
					iOldOTypes = pId -> GetOTypes();
					fMovedAway = pId -> MovedAway();
				
					lPCnt = pId -> GetPointCount();
					lLCnt = pId -> GetLineCount();
					lFCnt = pId -> GetAreaCount();
					lTCnt = pId -> GetTextCount();
					lKCnt = pId -> GetComplexCount();
					pObjs = pId -> DetachObjList();
				} else
					continue;
			} else
				continue;

		// alten Ident herauslöschen, um Platz für neuen zu machen
			Idents().DeleteIdent (Id[i]);

		// wenn nur DefaultSatz da ist, dann gesonderte Behandlung
		int fSpec = 0;

			if (pVTypes[i] == VT_Default) {
				TX_ASSERT(pVTypes[i] != VT_Default);		// snh with IsTRiASDBBased()
//				fSpec = MakeCompleteNewVisInfo (
//						(VisInfo **)pVI, 
//						MenuSight.GetTypes (Id[i], false), false
//					);
			} 
			else {
			// VisInfo holen
				GetCompleteVisInfo (pSight, Id[i], (VisInfo **)pVI, iDBOTypes, NULL, NULL, &fSpec);

			// wenn was sein soll und nichts gegeben ist, dann Standard generieren
				fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, fSpec, false);
			}

#if defined(_DEBUG)
// dem Mystischen auf der Spur ...
			_ASSERTE(NULL == pVI[0] || pVI[0]->IsLocatable());
			_ASSERTE(NULL == pVI[1] || pVI[1]->IsLocatable());
			_ASSERTE(NULL == pVI[2] || pVI[2]->IsLocatable());
			_ASSERTE(NULL == pVI[3] || pVI[3]->IsLocatable());
#endif // defined(_DEBUG)

		// neuen Satz generieren
			if (!Idents().AddIdent (*this, Id[i], pVI, fSpec, hPalette))
				continue;

			if (tID.Find(&Id[i])) {
			CIdentifikatorLock l(tID);

				DELETE_OBJ(pObjs);
				if (l) {
				CIdentifikator *pId = (CIdentifikator *)l;
				
					if (oldLoadInfo) pId -> Load();
					if (allLoaded) 	pId -> AllLoaded();
					else			pId -> NotAllLoaded();

				// wenn in der vorhergehenden Sicht Objekte temporär umklassifiziert
				// wurden, dann diesen Ident jetzt als nicht vollständig geladen 
				// kennzeichnen
					if (fMovedAway)	{
						pId -> NotAllLoaded();
						pId -> MovedAway (false);
					}

				DRAWIDENTEX DI;

					INITSTRUCT (DI, DRAWIDENTEX);
					DI.m_lIdent = Id[i];
					DEXN_DrawIdentifikatorEx (DI);
					pId -> DType() = DI.m_lResult & DT_DrawingMask;

					pId -> SetSpecial (fSpec);
					pId -> SetOTypes (iDBOTypes/*iOldOTypes*/);
					pId -> InitPointCount (lPCnt);
					pId -> InitLineCount (lLCnt);
					pId -> InitAreaCount (lFCnt);
					pId -> InitTextCount (lTCnt);
					pId -> InitComplexCount (lKCnt);
					TX_VERIFY(NULL == pId -> AttachObjList (pObjs));
					pObjs = NULL;
//					l -> EnablePainting (iDBOTypes);
				} else
					continue;
			} else
				continue;
		}
	}
	DELETE_OBJ (pObjs);
	DELETE_OBJ (Id);      // Feld wieder freigeben
	DELETE_OBJ (pVTypes);

// evtl. SichtContainer einstellen
ObjContainer OC (0, 0, 0, 0);

	if (GetSichtCont (&OC, pSight) == EC_OKAY && OC.isValid())
//	    && OC < GetExtend()) 
	{
	long lCont[4];
	KoOrd dX, dY;

		if (!ScaleCTF (OC.XMin(), OC.YMin(), &dX, &dY))
			return false;
		lCont[0] = dX;
		lCont[2] = dY;

		if (!ScaleCTF (OC.XMax(), OC.YMax(), &dX, &dY))
			return false;
		lCont[1] = dX;
		lCont[3] = dY;

		DEX_SetActiveSightContainer (lCont); 
	}

// wenn Legende aktiv ist, dann diese neu zeichnen
	LegendToRepaint = true;		// im Hintergrund Legende laufend halten
//	if (pLegende) 
//		pLegende -> SetCaption (pSight);
	SetPaintFlag (PF_NOTDRAWED);	// Sicht ist wieder gültig

// Speichern, ob Texte in Ansicht gezeichnet werden sollen
	GetShowTexts (g_fDrawTextObjs, pSight);

// anzuzeigende Objekteigenschaft lesen und anzeigen
char cbObjProp[_MAX_PATH];
int iFlags = g_iHideFlags;

	if (SUCCEEDED(GetObjPropToShow(NULL, cbObjProp, sizeof(cbObjProp), &iFlags))) {
		if ('\0' != cbObjProp)
			DEX_SetActObjPropName(cbObjProp);
		else
			DEX_SetActObjPropName(NULL);

		g_iHideFlags = iFlags;
	}

// neue Ansicht markieren
	CheckItemAsActive (pSight);	
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Namen der aktuellen Ansicht liefern
bool DatenBasisObjekt::GetActiveSightName (char *pBuffer, int maxLen) 
{
	if (NULL == m_pViews) {
		pBuffer[0] = '\0';
		return false;
	}

// Namen der aktiven Sicht kopieren, wenn aktuelle Sicht existiert
int locLen = maxLen != -1 ? maxLen : MAXVIEWNAMESIZE+1;

	TX_ASSERT(TIsValidAddress(pBuffer, locLen, true));	// writeable!
	return m_pViews -> GetActView (pBuffer, locLen);
}

bool DatenBasisObjekt::SetActiveSightName (LPCSTR pNewName)
{
	if (NULL == pNewName) 
		return false;
	return m_pViews -> SetActView (pNewName, true);
}

// Festellen, ob eine Ansicht aktiv ist
bool DatenBasisObjekt::HasActiveSight() 
{
	if (NULL == m_pViews) 
		return false;
	return m_pViews -> HasActView();
}

///////////////////////////////////////////////////////////////////////////////
// Namen der Standard-Ansicht liefern 
bool DatenBasisObjekt::GetDefaultSightName (char *pBuffer, int maxLen) 
{
	if (NULL == m_pViews) {
		if (NULL != pBuffer)
			pBuffer[0] = '\0';
		return false;
	}

// Namen der aktiven Sicht kopieren, wenn aktuelle Sicht existiert
int locLen = maxLen != -1 ? maxLen : MAXVIEWNAMESIZE+1;

	TX_ASSERT(NULL == pBuffer || TIsValidAddress(pBuffer, locLen, true));	// writeable!
	return m_pViews -> GetDefaultView (pBuffer, locLen);
}

bool DatenBasisObjekt::SetDefaultSightName (LPCSTR pNewName)
{
	if (NULL == pNewName) 
		return false;
	return m_pViews -> SetDefaultView (pNewName);
}

ErrCode DatenBasisObjekt::WriteSightIDs (
	LPCSTR pcSight, long *IDs, short numIDs, short *pTypInfo,
	LPCSTR pcTargetSight, short fFlags, long CObj) 
{
CEierUhr Wait (CurrActDirisW);
ErrCode EC = EC_OKAY;	// FehlerCode
bool iTargetRenamed = false;
#if defined (_FORCE_LEGACY_CODE)
long lMerkmale = 0;
long lRelationen = 0;
#endif // _USE_LEGACY_CODE
WTRiASProperties Props;
WTRiASRelations Rels;
os_string strTargetView;

	if (NULL != pcTargetSight)
		strTargetView = pcTargetSight;

// wenn eine Sicht gelöscht werden soll
	if (NULL == IDs) {
	// allen sagen, daß Sicht gelöscht werden soll
		if (DEXN_SightToDelete (pcSight))
			return WC_RETURN;		// jemand hat was dagegen

	// Sicht löschen
		DeleteView (pcSight);
		DEXN_SightDeleted (pcSight);		// Vollzug melden
		return EC_OKAY;
	}

// Sicht muß außerdem herausgelöscht werden, wenn neue Sicht
// bereits existiert und alte Sicht temporär oder nicht gleich 
// der neuen Sicht ist
	if (ProjectHasView (pcSight) && 
	   (NULL == pcTargetSight || strcmp (pcSight, pcTargetSight)))
	{
#if defined(_FORCE_LEGACY_CODE)
		GetViewAttribs (pcTargetSight, &lMerkmale, &lRelationen);
#endif // _USE_LEGACY_CODE
		GetViewAttribs (pcTargetSight, Props.ppi(), Rels.ppi());

		if (!DeleteView (pcSight))
			return EC_FAIL;

//			WrSight.GetAttribs (&lMerkmale, &lRelationen);
//			if ((EC = WrSight.DelSight(false)) != EC_OKAY && EC != WC_NOTFOUND) 
//				return EC;
	}

// Sicht muß einen temporären Namen erhalten, wenn Sicht bereits 
// existiert und die BezugsSicht gleich der neuen Sicht ist
	if (!(fFlags & WSDelView) && ProjectHasView (pcSight) && 
		NULL != pcTargetSight && !strcmp (pcSight, pcTargetSight)) 
	{
	// zeitweiliges umbenennen der Sicht
		strTargetView = os_string("$") + strTargetView;
		RenameView (pcTargetSight, strTargetView.c_str());

	// da diese Sicht gleich neu dargestellt werden soll, erstmal für alle
	// IDs ZeichenFlag zurücksetzen
//			jetzt weiter unten, da die PaintFlags noch benötigt werden
//			Idents().IdentTree().Every (ResetPaintFlag);
//			Idents().PrioTree().EveryDelete();	// Prioritäten werden neu aufgebaut
		iTargetRenamed = true;
	}

// Sicht muß u.U. neu angelegt werden, da gleichnamige alte Sicht 
// umbenannt wurde
	CreateView (pcSight);

//Sicht NewSight (DB(), Sight);

// SpeicherAbbild der Sicht
CTable t(Idents().IdentTree());	// Navigator für Sicht
VisInfo *pVI[4];

	memset (pVI, '\0', 4 * sizeof(VisInfo *));
	for (register int i = 0; i < numIDs; i++) {
	// bei der ersten Runde ist dies natürlich sinnlos
	short fToPaint = 0;
	short fSpec = 0;

		DELETE_OBJ (pVI[0]);	// beim 1. mal sinnlos
		DELETE_OBJ (pVI[1]);
		DELETE_OBJ (pVI[2]);
		DELETE_OBJ (pVI[3]);

	// Info aus BezugsSicht Sicht holen
		if (fFlags & WSActVis) {
		short iExistOTypes = 0;

			if (t.Find(&IDs[i])) {
			// VisInfo aus Speicher holen
			CIdentifikatorLock l(t);

				if (l && l -> toPaint(pTypInfo[i])) // wenn Ident/OTyp in dieser Sicht vorhanden ist
					fSpec = l -> GetCompleteVisInfo ((VisInfo **)pVI, pTypInfo[i], &iExistOTypes);
			} 
		
		// Visualisierung ist nicht in aktueller Ansicht vertreten
			if ((strTargetView.size() > 0) && (pTypInfo[i] != (pTypInfo[i] & iExistOTypes))) {
			// die restlichen VisInfo's aus Bezugssicht holen
			int iNewSpec = 0;

				if (GetCompleteVisInfo (strTargetView.c_str(), IDs[i], (VisInfo **)pVI, pTypInfo[i] & ~iExistOTypes, NULL, NULL, &iNewSpec))
					fSpec |= iNewSpec;
			}
		}

	// keine VisInfo gefunden: aus DefaultSicht laden
		EC = GetCompleteDefaultVisInfo (IDs[i], (VisInfo **)pVI, pTypInfo[i]) ? EC_OKAY : EC_FAIL;

	// wenn immer noch nicht da ist, dann Standard generieren, SonderFall beachten
		fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, pTypInfo[i], true);

	// neue VisInfo wegschreiben
		if (fSpec == TPAll) {	// nur DefaultInfo schreiben
			if (EC == EC_OKAY && pVI[0]) 
				EC = AddIdentToView (pcSight, IDs[i], TPAll) ? EC_OKAY : EC_FAIL;
		} else {		// nur nicht DefaultSätze schreiben
			if (!(fSpec & TPPunkt) && EC == EC_OKAY && pVI[0]) 
				EC = SaveVI (pVI[0], pcSight, IDs[i], VT_Punkt);
			if (!(fSpec & TPLinie) && EC == EC_OKAY && pVI[1]) 
				EC = SaveVI (pVI[1], pcSight, IDs[i], VT_Linie);
			if (!(fSpec & TPFlaeche) && EC == EC_OKAY && pVI[2]) 
				EC = SaveVI (pVI[2], pcSight, IDs[i], VT_Flaeche);
			if (!(fSpec & TPText) && EC == EC_OKAY && pVI[3]) 
				EC = SaveVI (pVI[3], pcSight, IDs[i], VT_Text);

		// Ident/Typ ohne VisInfo wegschreiben bzw. DefaultSatz löschen
			if (EC == EC_OKAY) {
				if (fSpec != 0)
					AddIdentToView (pcSight, IDs[i], fSpec);
				else
					RemoveIdentFromView (pcSight, IDs[i], TPAll, TPAll);
			}
		}
	}
	DELETE_OBJ (pVI[0]);
	DELETE_OBJ (pVI[1]);
	DELETE_OBJ (pVI[2]);
	DELETE_OBJ (pVI[3]);
	
// Clipping Objekt setzen
#if 0	// %TODO: implement the following functionality
	if (CObj != -1L) NewSight.SetObjRgn (CObj);
#endif // 0

// Die Welt von diesem Ereignis in Kenntnis setzen
	{
	VIEWCREATED VC;
	char cbNewName[MAXVIEWNAMESIZE+1];
	char cbTarget[MAXVIEWNAMESIZE+1];

		if (pcTargetSight)
			strcpy (cbTarget, pcTargetSight);
		else
			cbTarget[0] = '\0';
		strcpy (cbNewName, pcSight);

		INITSTRUCT (VC, VIEWCREATED);
		VC.m_pTarget = cbTarget;
		VC.m_pNewName = cbNewName;
		if (fFlags & WSDelView || iTargetRenamed) 
			VC.m_iMode |= VCDeleteTarget;
		if (fFlags & WSActVis) 
			VC.m_iMode |= VCUseTargetView;
#if defined(_FORCE_LEGACY_CODE)
		if (lMerkmale != 0L || lRelationen != 0L)
			VC.m_iMode |= VCFeaturesMoved;
#endif // defined(_USE_LEGACY_CODE)
		if (Props.IsValid() || Rels.IsValid())
			VC.m_iMode |= VCFeaturesMoved;
		DEXN_SightCreated(VC);
	}

// wenn Sicht umbenannt wurde oder alte Sicht gelöscht werden soll, 
// dann diese nun alte Sicht löschen
	if (iTargetRenamed || fFlags & WSDelView) {
		MoveViewAttribs (pcSight, strTargetView.c_str());	// Merkmale und Relationen retten
		DeleteView (strTargetView.c_str(), false);

	// da diese Sicht gleich neu dargestellt werden soll, erstmal für alle
	// IDs ZeichenFlag zurücksetzen
		Idents().IdentTree().Every (ResetPaintFlag);
		Idents().PrioTree().EveryDelete();	// Prioritäten werden neu aufgebaut
#if defined(_FORCE_LEGACY_CODE)
	} else if (lMerkmale != 0 || lRelationen != 0) {
		SetViewAttribs (pcSight, lMerkmale, lRelationen);
#else
	} else if (Props.IsValid() || Rels.IsValid()) {
		SetViewAttribs (strTargetView.c_str(), pcSight, Props, Rels);
#endif // _FORCE_LEGACY_CODE
	}

// wenn alles ok ist, dann != 0 liefern, wenn neue Sicht gleich der alten 
// Sicht ist
	return (ErrCode)(EC == EC_OKAY ? (iTargetRenamed ? WC_RETURN : EC_OKAY) : EC);
}

// Enumeration der Sichten dieser DatenBasis ----------------------------------
// die EnumerationsFunktion muß 'PASCAL' sein ---------------------------------
extern "C" {
inline BOOL EnumSightsCallback (BOOL (*pFcn)(char *, BOOL, void *), 
			        char *SichtName, BOOL iNext, void *pData) 
{
	return ((ENUMNOKEYCALLBACK)pFcn)(SichtName, iNext, pData);
}

typedef struct tagENUMSIGHTSDATA {
	void *pData;
	BOOL (*pFcn)(char *, BOOL, void *);
} ENUMSIGHTSDATA;

bool CViewEntryEnumProc (CViewEntry &rVE, bool fNotLast, void *pESData)
{
	return EnumSightsCallback (
			((ENUMSIGHTSDATA *)pESData) -> pFcn, 
			(char *)rVE.FGetstring().c_str(),
			fNotLast, ((ENUMSIGHTSDATA *)pESData) -> pData
	       );
}

} // extern "C"

bool DatenBasisObjekt::EnumSights (BOOL (*pFcn)(char *, BOOL, void *), void *pData)
{
	if (NULL == m_pViews) {
#if defined(_USE_LEGACY_CODE)
		if (!IsTRiASDBBased()) {
			m_pViews = CViewsTree::CreateInstance (DB());
		} else
#endif // _USE_LEGACY_CODE
		{
			m_pViews = CViewsTree::CreateInstance (m_Prj);
		}
		if (NULL == m_pViews) return false;	// Fehler
	}
	
ENUMSIGHTSDATA ESData;

	ESData.pData = pData;
	ESData.pFcn = pFcn;
	return m_pViews -> FEnumAllItems (CViewEntryEnumProc, &ESData);
}

///////////////////////////////////////////////////////////////////////////////
// Löschen einer Sicht 
bool DatenBasisObjekt::DeleteView (pMenu pM, LPCSTR pView)
{
CScopeVar<bool> Semaphore (m_fIsDeletingView, true);

	if (Semaphore.GetOldValue() || !pView) 
		return false;		// rekursiven Aufruf verhindern

// diese Sicht ist die aktuelle
char cbBuffer[MAXVIEWNAMESIZE+1];

	if (GetActiveSightName (cbBuffer, sizeof(cbBuffer)) && !strcmp (pView, cbBuffer)) {
		DEX_ViewCanvasErase();			// Bildschirm löschen

		DEXN_SightSelected (NULL);
		ActivateSight (NULL);			// keine Sicht aktiv
		DEX_RemoveAllORWnds();			// ORFenster weg
		
	// ObjektListe löschen
		Idents().ResetAllLoaded();		// Nichts mehr geladen
		Shapes().EveryDelete();			// alle Objekte löschen
		SetPaintFlag (PF_INVALID); 
		
	// Rollbalken entfernen, Legende ausblenden etc.
		if (LegendeCFlag) 	// Legende ist angezeigt
			GetViewWindow()->GetFrame()->PostEvent (WM_COMMAND, IDM_LEGENDE);
	}

// Sicht rauslöschen
	if (WriteSightIDs (pView, NULL, 0, NULL) != EC_OKAY)	// Sicht löschen
		return false;

	DEX_GetDefaultView(cbBuffer);
	if (!strcmp (cbBuffer, pView))	
	// Standardansicht wird gelöscht: 'Standard=...' löschen
		DEX_SetDefaultView (NULL);

// Punkt aus Menu entfernen 
	DeleteSightMenuItem (GetViewWindow()->GetFrame(), pM, pView);
	m_pViews -> FDeleteItem (pView);	// aus Baum löschen
	return true;
}
