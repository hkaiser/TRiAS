// Memberfunktionen von DatenBasisObjekt zu Ansichten
// File: SIGHTS.CXX

#include "triaspre.hxx"

#include "triasres.h"

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

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
extern CLegendeWindow *pLegende;
extern bool LegendToRepaint;
extern bool LegendeCFlag;
extern short SystemSightFlag;

extern HPALETTE hPalette;

// Memberfunktionen -----------------------------------------------------------

// Sichtmenu initialisieren, wird bei OpenDB gerufen --------------------------
bool DatenBasisObjekt :: InitSightMenu (pMenu pM, bool fStandard) 
{
// Namen der Ansichten holen
	DELETE (m_pViews);

	m_pViews = CViewsTree :: CreateInstance (DB());
	if (NULL == m_pViews) return false;	// Fehler

	if (0 == m_pViews -> Count()) return false;	// keine Ansichten da

// PopupMenu aufbauen
CTable t(*m_pViews);
bool fDraw = false;
UINT uiID = 0;

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

	// Item in Menu eintragen
		fDraw = AddItemToSightMenu (pM, (l -> FGetstring()).c_str(), uiID);
		l -> SetInMenu (uiID > 0 ? true : false);

	// evtl. Standard voreinstellen
		if (fStandard && l -> isDefaultView()) 
			ProcessMenuEvent ((l -> FGetstring()).c_str(), false);
	}

return fDraw;
}

bool DatenBasisObjekt :: AddItemToSightMenu (pMenu pM, LPCSTR pcView)
{
	TX_ASSERT (m_pViews);

UINT uiID = 0;
bool fDraw = false;

	m_pViews -> FAddItem (pcView);
	fDraw = AddItemToSightMenu (pM, pcView, uiID);
	m_pViews -> SetInMenu (pcView, uiID > 0 ? true : false);

return fDraw;
}

bool DatenBasisObjekt :: AddItemToSightMenu (
		pMenu pM, const char *pcItem, unsigned int &ruiID) 
{
// Ansicht muß schon im Baum drinsein
	TX_ASSERT (m_pViews);
	TX_ASSERT (m_pViews -> FFindItem (pcItem));	

// evtl. PopupMenu aufbauen und einhängen
	if (NULL == _SightMenu) {
		_SightMenu = new Menu;          	// SubMenu erzeugen
		_SightFlag = false;             	// erstes Mal
		if (NULL == _SightMenu) {
			ruiID = 0;
			return false;         // Fehler, kein Menu verfügbar
		}
	}

// neues MenuItem einhängen, wenn noch Platz ist und es noch nicht drin ist
HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);
int iCnt = GetMenuItemCount (hMenu);

	if (0 == iCnt && !_SightFlag) {	// PopupMenu einklinken
	ResString resItem (IDS_SELSIGHT, 30);

		pM -> InsertItem (SightMenu(), resItem, IDM_SELOBJ);
		_SightFlag = true;
	}

	if (iCnt > MAXSHOWNVIEWS) {
		ruiID = 0;
		return false;	// kein Platz mehr
	}
	
	if (MAXSHOWNVIEWS == iCnt) {
	ResString resMoreViews (IDS_MOREVIEWS, 32);

		SightMenu() -> AppendSeparator();
		SightMenu() -> AppendItem (IDM_SIGHTS+MAXSHOWNVIEWS, resMoreViews);
		ruiID = 0;		// nicht hinzugefügt
		return true;		// evtl. DrawMenuBar
	}

// testen, ob diese Sicht bereits im Menu ist
char cbMenuItem[MAXVIEWNAMESIZE+1];
int i = 0;

	for (/**/; i < iCnt; i++) {
		GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
				      sizeof(cbMenuItem), MF_BYCOMMAND);
		if (!strcmp (cbMenuItem, pcItem)) {
			ruiID = IDM_SIGHTS+i;	// existiert bereits
			return false;		// kein DrawMenuBar
		}
	}

// dieser MenuPunkt existiert noch nicht 
	SightMenu() -> AppendItem (IDM_SIGHTS+i, pcItem);
	ruiID = IDM_SIGHTS+i;

return true; 	// evtl. DrawMenuBar
}

// Sicht mit Checkmark versehen und als aktiv kennzeichnen --------------------
bool DatenBasisObjekt :: CheckItemAsActive (LPCSTR pcView)
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
bool DatenBasisObjekt :: UnCheckItemAsActive (void)
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
bool DatenBasisObjekt :: DeleteAllSightItems (pMenu pM) 
{
	if (NULL == SightMenu()) return false;

	TX_ASSERT (m_pViews);

int iCnt = GetMenuItemCount (SightMenu() -> Handle (API_MENU_HMENU));

// alle Sichteinträge löschen
	for (int i = 0; i < iCnt; i++)
		SightMenu() -> DeleteItem (IDM_SIGHTS+i);

// SubMenu rauslöschen, EIntrag rausnehmen, Menu freigeben
#if defined(WIN32)
	::RemoveMenu (::GetSubMenu (pM -> Handle (API_MENU_HMENU), 2), 0, MF_BYPOSITION);
#else
	::RemoveMenu (::GetSubMenu (pM -> Handle (API_MENU_HMENU), 2), 2, MF_BYPOSITION);
#endif // WIN32

	DELETE (_SightMenu);

return true;
}

// Einen Eintrag aus dem AnsichtenMenu herausnehmen. Im ViewTree muß die Ansicht
// aber noch drin sein.
bool DatenBasisObjekt :: DeleteSightMenuItem (pMenu pM, LPCSTR pcItem) 
{
	if (NULL == SightMenu()) return false;

	TX_ASSERT (m_pViews);
	TX_ASSERT (m_pViews -> FFindItem (pcItem));	// Ansicht muß noch im Baum drinsein

HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);
int iCnt = GetMenuItemCount (hMenu);

	if (0 == iCnt) return false;	// ist bereits leer

// Eintrag im Menu suchen
char cbMenuItem[MAXVIEWNAMESIZE+1];
bool fDraw = false;
int i = 0;

	iCnt = min((UINT)iCnt, MAXSHOWNVIEWS);
	for (/**/; i < iCnt; i++) {
		GetMenuString (hMenu, IDM_SIGHTS+i, cbMenuItem, 
				      sizeof(cbMenuItem), MF_BYCOMMAND);
		if (!strcmp (cbMenuItem, pcItem))
			break;
	}

// wenn gefunden, dann löschen
	if (i < iCnt) {
		if (m_pViews -> isActView (cbMenuItem)) 
			m_pViews -> SetActView (cbMenuItem, false);

		SightMenu() -> DeleteItem (IDM_SIGHTS+i);
		fDraw = true;

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
				fDraw = true;
			}
			if (MAXSHOWNVIEWS+1 == m_pViews -> Count()) {	// 'Weite Ansichten ...' entfernen
				DeleteMenu (hMenu, MAXSHOWNVIEWS, MF_BYPOSITION);
				DeleteMenu (hMenu, IDM_SIGHTS+MAXSHOWNVIEWS, MF_BYCOMMAND);
				fDraw = true;
			}
		}
	}

// wenn Submenu leer ist, dann löschen des Unterpunktes
	if (0 == GetMenuItemCount (hMenu) && NULL != pM) {	// wenn PopUpMenu leer geworden ist, dann löschen
#if defined(WIN32)
		::RemoveMenu (::GetSubMenu (pM -> Handle (API_MENU_HMENU), 2), 0, MF_BYPOSITION);
#else
		::RemoveMenu (::GetSubMenu (pM -> Handle (API_MENU_HMENU), 2), 2, MF_BYPOSITION);
#endif // WIN32
		DELETE (_SightMenu);
	}

// jetzt de Eintrag aus dem Baum entfernen
	m_pViews -> FDeleteItem (pcItem);	// aus Baum löschen

return fDraw;
}

bool DatenBasisObjekt :: ProcessMenuEvent (UINT uiMenuID) 
{
	if (SightMenu() == NULL) return false;

	if (uiMenuID < IDM_SIGHTS || uiMenuID >= IDM_SIGHTS+MAXSHOWNVIEWS)
		return false;		// nicht für uns

char cbMenuItem[SIGHTMENUITEM+1];	// Name der neuen Sicht
HMENU hMenu = SightMenu() -> Handle (API_MENU_HMENU);

	if (GetMenuString (hMenu, uiMenuID, cbMenuItem, sizeof(cbMenuItem), MF_BYCOMMAND) > 0)
		return ProcessMenuEvent (cbMenuItem, false);

return false;
}

bool DatenBasisObjekt :: ProcessMenuEvent (LPCSTR pcView, bool fForce) 
{
	if (SightMenu() == NULL) return false;

char cbMenuString[SIGHTMENUITEM+1];	// Name der neuen Sicht
char *pNewView = (NULL != pcView) ? (LPSTR)pcView : cbMenuString;

	GetActiveSightName (cbMenuString, sizeof(cbMenuString));

// evtl. als DefaultSicht setzen
	if (GetKeyState (VK_CONTROL) < 0 && !fForce) {
		ProFile (DB().GetDBName()).SetStandardSight (pNewView);
		m_pViews -> SetDefaultView (pNewView);
	}

// eine Ansicht wurde ausgewählt
bool fNew = strcmp (cbMenuString, pNewView);

	if (NULL == pcView || '\0' == *pNewView) 
		fForce = true;	// keine Sicht: also immer neu generieren

	if (!fForce) {
		if (!fNew) return false;	// bereits aktive Ansicht wurde gewählt
		if (DEXN_SightToSelect (pNewView))
			return false;		// jemand hat was dagegen
	}
	if (fNew) DEX_RemoveAllORWnds();	// alle ORFenster weg, wenn neue Sicht

	if (!ActivateSight (pNewView))		// Sicht auswählen
		return false;

	if (!fForce) DEXN_SightSelected (pNewView);

// Identifikatorbaum von nicht mehr benötigten temporären Idents bereinigen
	RemoveTempIdents();
	CIdentifikator :: ReleaseIgnoreTree();		// statische Funktion

return true;    // ok, neue Ansicht aktiv
}

// aktivieren einer vorgebebenen Sicht ----------------------------------------
extern void EXPORTTRIAS ResetPaintFlag (void *pObj);

bool DatenBasisObjekt :: ActivateSight (char *pSight)
{
CActDB ActDB (DB());	// GeoDB aktivieren
// CEierUhr Wait (CurrActDirisW);

// alte Ansicht unmarkieren
	UnCheckItemAsActive();	
	if (NULL == pSight) return false;

// temporäre Idents rauswerfen
	ResetLoadedRects();
	DeleteTempIdents();
	SetActiveSightName (pSight);
	ResetIdentScaleMCodes (true);

	if ('\0' == *pSight) return true;	// temporäre Ansicht
		
short Cnt = 0;
long *Id;
short *pVTypes;
Sicht MenuSight (DB(), pSight);

	ClipRegionONr() = MenuSight.GetObjRgn();	// ClippingObjekt
	if (MenuSight.GetSightIDs (&Id, Cnt, &pVTypes) != EC_OKAY)
		return false;
	if (Cnt == 0)                   // kein Eintrag oder Fehler
		return false;

// Palette neu generieren
	if (hPalette != NULL) 		// alte Palette freigeben
		DeleteObject (hPalette);
	hPalette = MenuSight.GetPalette();

	DEXN_SetNewPalette (hPalette);

// einzelne Idents aktivieren, das kann eine Weile dauern
CIdentObjects *pObjs = NULL;

	Idents().IdentTree().Every (ResetPaintFlag);	// alle Idents deAktivieren
	Idents().PrioTree().EveryDelete();	// Prioritäten werden neu aufgebaut
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
			if (!Idents().FindId (DB(), Id[i], NULL, &iDBOTypes)) {
				continue;
//				return false;
			}
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
		short fSpec = 0;

			if (pVTypes[i] == VT_Default) {
				fSpec = MakeCompleteNewVisInfo (
						(VisInfo **)pVI, 
						MenuSight.GetTypes (Id[i], false), false
					);
			} else {
			// VisInfo holen
				fSpec = MenuSight.GetCompleteVisInfo (Id[i], NULL, 
							(VisInfo **)pVI, iDBOTypes);

			// wenn was sein soll und nichts gegeben ist, dann Standard generieren
				fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, fSpec, false);
			}

		// neuen Satz generieren
			if (!Idents().AddIdent (Id[i], pVI, fSpec, hPalette))
				continue;

			if (tID.Find(&Id[i])) {
			CIdentifikatorLock l(tID);

				DELETE(pObjs);
				if (l) {
				CIdentifikator *pId = (CIdentifikator *)l;
				
					if (oldLoadInfo) pId -> Load();
					if (allLoaded) 	pId -> AllLoaded();
					else		pId -> NotAllLoaded();

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
	DELETE (pObjs);
	DELETE (Id);      // Feld wieder freigeben
	DELETE (pVTypes);

// evtl. SichtContainer einstellen
ObjContainer OC (0, 0, 0, 0);

	if (GetActSichtCont (&OC, pSight) == EC_OKAY && OC.isValid())
	{
		DEX_SetActiveSightContainer (OC); 
	}

// wenn Legende aktiv ist, dann diese neu zeichnen
	LegendToRepaint = true;		// im Hintergrund Legende laufend halten
	if (pLegende) 
		pLegende -> SetCaption (pSight);
	SetPaintFlag (PF_NOTDRAWED);	// Sicht ist wieder gültig

// neue Ansicht markieren
	CheckItemAsActive (pSight);	

return true;
}

// Namen der aktuellen Ansicht liefern ----------------------------------------
bool DatenBasisObjekt :: GetActiveSightName (char *pBuffer, int maxLen) 
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

bool DatenBasisObjekt :: SetActiveSightName (LPCSTR pNewName)
{
	if (pNewName == NULL) return false;

return m_pViews -> SetActView (pNewName, true);
}

///////////////////////////////////////////////////////////////////////////////
// Namen der Standard-Ansicht liefern 
bool DatenBasisObjekt::GetDefaultSightName (char *pBuffer, int maxLen) 
{
	if (NULL == m_pViews) {
		pBuffer[0] = '\0';
		return false;
	}

// Namen der aktiven Sicht kopieren, wenn aktuelle Sicht existiert
int locLen = maxLen != -1 ? maxLen : MAXVIEWNAMESIZE+1;

	TX_ASSERT(TIsValidAddress(pBuffer, locLen, true));	// writeable!

return m_pViews -> GetDefaultView (pBuffer, locLen);
}

bool DatenBasisObjekt :: SetDefaultSightName (LPCSTR pNewName)
{
	if (pNewName == NULL) return false;

return m_pViews -> SetDefaultView (pNewName);
}

ErrCode DatenBasisObjekt :: WriteSightIDs (char *Sight, long *IDs, 
					   short numIDs, short *pTypInfo,
					   Sicht *pTargetSight, 
					   short fFlags, long CObj) 
{
CActDB ActDB (DB());		// #ActDB
CEierUhr Wait (CurrActDirisW);
ErrCode EC = EC_OKAY;	// FehlerCode
ErrInstall EI (WC_NOTFOUND);
bool iTargetRenamed = false;
long lMerkmale = 0;
long lRelationen = 0;

	{
	// wenn eine Sicht gelöscht werden soll
	Sicht WrSight (DB(), Sight);	// zu beschreibende Sicht

		if (IDs == NULL) {
		// allen sagen, daß Sicht gelöscht werden soll
			if (DEXN_SightToDelete (Sight))
				return WC_RETURN;		// jemand hat was dagegen

		// Sicht löschen
			if ((EC = WrSight.DelSight ()) != EC_OKAY) {
				if (EC == WC_NOTFOUND)
					EC = EC_OKAY;
			}

			DEXN_SightDeleted (Sight);		// Vollzug melden
			return EC;
		}

	// Sicht muß außerdem herausgelöscht werden, wenn neue Sicht
	// bereits existiert und alte Sicht temporär oder nicht gleich 
	// der neuen Sicht ist
		if (WrSight.isValid() && (pTargetSight == NULL || 
		    strcmp (WrSight.Name(), pTargetSight -> Name())))
		{
			WrSight.GetAttribs (&lMerkmale, &lRelationen);
			if ((EC = WrSight.DelSight(false)) != EC_OKAY && EC != WC_NOTFOUND) 
				return EC;
		}

	// Sicht muß einen temporären Namen erhalten, wenn Sicht bereits 
	// existiert und die BezugsSicht gleich der neuen Sicht ist
		if (!(fFlags & WSDelView) && WrSight.isValid() && 
		    pTargetSight != NULL &&
		    !strcmp (WrSight.Name(), pTargetSight -> Name())) 
		{
		// zeitweiliges umbenennen der Sicht
		char NewName[SIGHTNAMESIZE+2];

			strcpy (NewName, "$");
			strcat (NewName, pTargetSight -> Name());
			pTargetSight -> Rename (NewName);

		// da diese Sicht gleich neu dargestellt werden soll, erstmal für alle
		// IDs ZeichenFlag zurücksetzen
//			jetzt weiter unten, da die PaintFlags noch benötigt werden
//			Idents().IdentTree().Every (ResetPaintFlag);
//			Idents().PrioTree().EveryDelete();	// Prioritäten werden neu aufgebaut
			iTargetRenamed = true;
		}
	}

// Sicht muß u.U. neu angelegt werden, da gleichnamige alte Sicht 
// umbenannt wurde
Sicht NewSight (DB(), Sight);

// SpeicherAbbild der Sicht
CTable t(Idents().IdentTree());	// Navigator für Sicht
VisInfo *pVI[4];

	memset (pVI, '\0', 4 * sizeof(VisInfo *));
	for (register int i = 0; i < numIDs; i++) {
	// bei der ersten Runde ist dies natürlich sinnlos
	short fToPaint = 0;
	short fSpec = 0;

		DELETE (pVI[0]);	// beim 1. mal sinnlos
		DELETE (pVI[1]);
		DELETE (pVI[2]);
		DELETE (pVI[3]);

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
			if (NULL != pTargetSight &&
				pTypInfo[i] != (pTypInfo[i] & iExistOTypes)) 
			{
			// die restlichen VisInfo's aus Bezugssicht holen
				fSpec = pTargetSight -> GetCompleteVisInfo (IDs[i], NULL, (VisInfo **)pVI, pTypInfo[i] & ~iExistOTypes);
			}
		}

	// keine VisInfo gefunden: aus DefaultSicht laden
		EC = GetCompleteDefaultVisInfo (DB(), IDs[i], NULL, (VisInfo **)pVI, pTypInfo[i]);

	// wenn immer noch nicht da ist, dann Standard generieren, SonderFall
	// beachten
		fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, pTypInfo[i], true);

	// neue VisInfo wegschreiben
		if (fSpec == TPAll) {	// nur DefaultInfo schreiben
			if (EC == EC_OKAY && pVI[0]) 
				EC = NewSight.AddIDtoSight (IDs[i], pVI[0], TPAll);
		} else {		// nur nicht DefaultSätze schreiben
			if (!(fSpec & TPPunkt) && EC == EC_OKAY && pVI[0]) 
				EC = NewSight.AddIDtoSight (IDs[i], pVI[0]);
			if (!(fSpec & TPLinie) && EC == EC_OKAY && pVI[1]) 
				EC = NewSight.AddIDtoSight (IDs[i], pVI[1]);
			if (!(fSpec & TPFlaeche) && EC == EC_OKAY && pVI[2]) 
				EC = NewSight.AddIDtoSight (IDs[i], pVI[2]);
			if (!(fSpec & TPText) && EC == EC_OKAY && pVI[3]) 
				EC = NewSight.AddIDtoSight (IDs[i], pVI[3]);

		// Ident/Typ ohne VisInfo wegschreiben bzw. DefaultSatz löschen
			if (EC == EC_OKAY) {
				if (fSpec != 0)
					NewSight.AddIDtoSight (IDs[i], NULL, fSpec);
				else
					NewSight.DelIDfromSight (IDs[i], VT_Default);
			}
		}
	}
	DELETE (pVI[0]);
	DELETE (pVI[1]);
	DELETE (pVI[2]);
	DELETE (pVI[3]);
	
// Clipping Objekt setzen
	if (CObj != -1L) NewSight.SetObjRgn (CObj);

// Die Welt von diesem Ereignis in Kenntnis setzen
	{
	VIEWCREATED VC;
	char cbNewName[MAXVIEWNAMESIZE+1];
	char cbTarget[MAXVIEWNAMESIZE+1];

		if (pTargetSight)
			OemToAnsi (pTargetSight -> Name(), cbTarget);
		else
			cbTarget[0] = '\0';
		OemToAnsi (NewSight.Name(), cbNewName);

		INITSTRUCT (VC, VIEWCREATED);
		VC.m_pTarget = cbTarget;
		VC.m_pNewName = cbNewName;
		if (fFlags & WSDelView || iTargetRenamed) 
			VC.m_iMode |= VCDeleteTarget;
		if (fFlags & WSActVis) 
			VC.m_iMode |= VCUseTargetView;
		if (lMerkmale != 0L || lRelationen != 0L)
			VC.m_iMode |= VCFeaturesMoved;
		DEXN_SightCreated(VC);
	}

// wenn Sicht umbenannt wurde oder alte Sicht gelöscht werden soll, 
// dann diese nun alte Sicht löschen
	if (iTargetRenamed || fFlags & WSDelView) {
		NewSight.MoveAttribs (pTargetSight);	// Merkmale und Relationen retten
		pTargetSight -> DelSight(false);

	// da diese Sicht gleich neu dargestellt werden soll, erstmal für alle
	// IDs ZeichenFlag zurücksetzen
		Idents().IdentTree().Every (ResetPaintFlag);
		Idents().PrioTree().EveryDelete();	// Prioritäten werden neu aufgebaut
	} else if (lMerkmale != 0 || lRelationen != 0) {
		NewSight.SetAttribs (lMerkmale, lRelationen);
	}

// wenn alles ok ist, dann != 0 liefern, wenn neue Sicht gleich der alten 
// Sicht ist
return (ErrCode)(EC == EC_OKAY ? (iTargetRenamed ? WC_RETURN : EC_OKAY) : EC);
}

// Enumeration der Sichten dieser DatenBasis ----------------------------------
// die EnumerationsFunktion muß 'PASCAL' sein ---------------------------------
extern "C" {
inline bool EnumSightsCallback (bool (*pFcn)(char *, bool, void *), 
			        char *SichtName, bool iNext, void *pData) 
{
	return ((ENUMNOKEYCALLBACK)pFcn)(SichtName, iNext, pData);
}

typedef struct tagENUMSIGHTSDATA {
	void *pData;
	bool (*pFcn)(char *, bool, void *);
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

bool DatenBasisObjekt :: EnumSights (bool (*pFcn)(char *, bool, void *), void *pData)
{
	if (NULL == m_pViews) {
		m_pViews = CViewsTree :: CreateInstance (DB());
		if (NULL == m_pViews) return false;	// Fehler
	}
	
ENUMSIGHTSDATA ESData;

	ESData.pData = pData;
	ESData.pFcn = pFcn;

return m_pViews -> FEnumAllItems (CViewEntryEnumProc, &ESData);
}


// Löschen einer Sicht --------------------------------------------------------
bool DatenBasisObjekt :: DeleteView (pMenu pM, char *pView)
{
	if (!pView) return false;

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
		if (LegendeCFlag) {	// Legende ist angezeigt
			PostMessage (CurrActDirisW -> Handle (API_WINDOW_HWND), 
				     WM_COMMAND, IDM_LEGENDE, 0);
		}
	}

// Sicht rauslöschen
	if (WriteSightIDs (pView, NULL, 0, NULL) != EC_OKAY)	// Sicht löschen
		return false;

ProFile PF (DB().GetDBName());

	if (!strcmp (PF.GetStandardSight(), pView)) 
	// Standardansicht wird gelöscht: 'Standard=...' löschen
		PF.SetStandardSight (NULL);

// Punkt aus Menu entfernen 
	DeleteSightMenuItem (pM, pView);
	m_pViews -> FDeleteItem (pView);	// aus Baum löschen
	
return true;
}
