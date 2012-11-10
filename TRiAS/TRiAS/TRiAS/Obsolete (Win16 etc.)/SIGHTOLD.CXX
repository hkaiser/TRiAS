// Memberfunktionen von DatenBasisObjekt zu Ansichten
// File: SIGHTS.CXX

#include "triaspre.hxx"

#include <switchkc.h>

#include "identsel.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern Window *CurrActW;
extern Window *CurrActDirisW;
extern CLegendeWindow *pLegende;
extern bool LegendToRepaint;
extern bool LegendeCFlag;
extern short SystemSightFlag;

extern HPALETTE hPalette;

extern short MakeCompleteNewVisInfo (VisInfo **ppVI, short iBits, bool fSpecial = false);
// extern "C" long FindLong (long *, long, long);

// Memberfunktionen -----------------------------------------------------------
void DatenBasisObjekt :: InitSightMenu (bool iStandard) 
{
	_SightCount = 0;
// Menueinträge einlesen
ProFile PF (DB().GetDBName());

// Menu aufbauen
	if (_SightMenu == NULL) {
		_SightMenu = new Menu;          // SubMenu
		_SightFlag = false;             // erstes Mal
	}
	if (_SightMenu == NULL) 
		return;

// Namen der Ansichten holen
char **SightNames = (char **)new char *[MAXSIGHTS];	// alle Namen der Ansichten

	if (SightNames == NULL) return;

short MenuBarBreakCnt = 0;

	_SightCount = MAXSIGHTS;        // maximale mögliche SichtAnzahl 
//	GetSightNames ((char **)SightNames, _SightCount);
	GetSightNames();

	MenuBarBreakCnt = (_SightCount < MAXSIGHTS/10+5) ? 0 : MAXSIGHTS/10;

	_activeSight = -1;
	if (_SightCount > 0) {
	// PopupMenu aufbauen
	char *StandardSight = PF.GetStandardSight();
	ResString Standard (IDS_STANDARD, SIGHTMENUITEM+1);
	HMENU hMenu = _SightMenu -> Handle (API_MENU_HMENU);

		for (register int i = 0, j = 0; i < _SightCount; i++, j++) {
			if (strcmp (SightNames[i], Standard)) {
			// Item in Menu eintragen
			UINT uiFlag = (MenuBarBreakCnt && !((i+1) % MenuBarBreakCnt)) ? MF_MENUBARBREAK : 0;

				AppendMenu (hMenu, MF_STRING|uiFlag, IDM_SIGHTS+j, SightNames[i]);

//				_SightMenu -> AppendItem (IDM_SIGHTS+j, 
//								SightNames[i]);
			// Standard voreinstellen
				if (iStandard && !strcmp (SightNames[i], StandardSight)) 
					ProcessMenuEvent (IDM_SIGHTS+j);
			} else
				j--;
		// Speicher wieder freigeben
			if (SightNames[i]) {
				delete SightNames[i];
				SightNames[i] = NULL;
			}

		// nach jeweils 20 Einträgen MENUBARBREAK einfügen
//			if (MenuBarBreakCnt && !((i+1) % MenuBarBreakCnt))
//				AppendMenu (_SightMenu -> Handle (API_MENU_HMENU),
//						MF_MENUBARBREAK, 0, NULL);
		}
		// Standard nicht mitzählen
		if (i != j) 
			_SightCount--;
	}
// Speicher wieder freigeben
	delete SightNames;

	if (Sights() != 0 && !_SightFlag && SightMenu() != NULL) {
	// PopupMenu einklinken
		(((IrisWind *)CurrActDirisW) -> MainMenu()) 
		-> InsertItem (SightMenu(), ResString (IDS_SELSIGHT, 30), IDM_SELOBJ);
		_SightFlag = true;
	}
	DrawMenuBar (CurrActDirisW -> Handle (API_WINDOW_HWND));
}

short DatenBasisObjekt :: AddItemToSightMenu (char *Item) 
{
// evtl. Menu aufbauen
	if (SightMenu() == NULL) {
		_SightMenu = new Menu;          // SubMenu
		_SightFlag = false;             // erstes Mal
		if (SightMenu() == NULL) return -1;         // Fehler, kein Menu verfügbar
	}

HMENU hMenu = (((IrisWind *)CurrActDirisW) -> MainMenu()) -> Handle (API_MENU_HMENU);

	if (Sights() == 0 && !_SightFlag && SightMenu() != NULL) {
	// PopupMenu einklinken
		(((IrisWind *)CurrActDirisW) -> MainMenu()) 
		-> InsertItem (SightMenu(), ResString (IDS_SELSIGHT, 30), IDM_SELOBJ);
		_SightFlag = true;
	}

	for (register int i = 0; i < Sights(); i++) {
	char MenuItem[SIGHTMENUITEM+1];

		GetMenuString (hMenu, IDM_SIGHTS+i, MenuItem, 
						SIGHTMENUITEM, MF_BYCOMMAND);
		if (!strcmp (MenuItem, Item))
			break;
	}

	if (i == Sights() && Sights()+1 < MAXSIGHTS && SightMenu() != NULL) {
	// nur wenn dieser MenuPunkt noch nicht existiert
		SightMenu() -> AppendItem (IDM_SIGHTS+Sights(), Item);
		_SightCount++;
	}
	DrawMenuBar (CurrActDirisW -> Handle (API_WINDOW_HWND));

return IDM_SIGHTS+i;
}

void DatenBasisObjekt :: DeleteAllSightItems (void) 
{
	if (_SightMenu == NULL || Sights() == 0) return;

// alle Sichteinträge löschen
	for (register int i = 0; i < Sights(); i++)
		SightMenu() -> DeleteItem (IDM_SIGHTS+i);

// SubMenu rauslöschen, EIntrag rausnehmen, Menu freigeben
//	(((IrisWind *)CurrActDirisW) -> MainMenu()) -> DeleteItem (SightMenu());

HMENU hMenu = GetSubMenu ((((IrisWind *)CurrActDirisW) -> MainMenu())  
						-> Handle (API_MENU_HMENU), 2);

#if defined(WIN32)
	RemoveMenu (hMenu, 0, MF_BYPOSITION);
#else
	RemoveMenu (hMenu, 2, MF_BYPOSITION);
#endif // WIN32
	DELETE (_SightMenu);
	_SightCount = 0;
	ActualSight() = -1;
	DELETE (_pSightName);

	DrawMenuBar (CurrActDirisW -> Handle (API_WINDOW_HWND));
}


void DatenBasisObjekt :: DeleteSightMenuItem (char *Item) 
{
	if (_SightMenu == NULL) return;

HMENU hMenu = (((IrisWind *)CurrActDirisW) -> MainMenu()) -> Handle (API_MENU_HMENU);
bool fExists = Sights() > 0;

// Eintrag im Menu suchen
	for (register int i = 0; i < Sights(); i++) {
	char MenuItem[SIGHTMENUITEM+1];

		GetMenuString (hMenu, IDM_SIGHTS+i, MenuItem, 
						SIGHTMENUITEM, MF_BYCOMMAND);
		if (!strcmp (MenuItem, Item))
			break;
	}

// wenn gefunden, dann löschen
	if (i < Sights()) {
	// wenn diese Ansicht derzeit aktiv ist, dann CheckMark löschen
		if (IDM_SIGHTS+i == ActualSight()) {
			SightMenu() -> unCheckItem (ActualSight());
			ActualSight() = -1;
		}
		SightMenu() -> DeleteItem (IDM_SIGHTS+i);
		--_SightCount;
		++i;

		while (i <= Sights()) {
		char MenuItem[SIGHTMENUITEM+1];
		// nächste UnterPunkte nachziehen
			GetMenuString (hMenu, IDM_SIGHTS+i, MenuItem, 
						SIGHTMENUITEM, MF_BYCOMMAND);
			ModifyMenu (hMenu, IDM_SIGHTS+i, MF_BYCOMMAND,
						IDM_SIGHTS+i-1, MenuItem);
			++i;    // nächster Eintrag
		}
	}

// wenn Submenu leer ist, dann löschen des Unterpunktes
	if (Sights() == 0 && fExists) {		// nur wenn es leer geworden ist
	// PopupMenu löschen
//		(((IrisWind *)CurrActDirisW) -> MainMenu()) -> DeleteItem (SightMenu());

	HMENU hMenu = GetSubMenu ((((IrisWind *)CurrActDirisW) -> MainMenu())  
					-> Handle (API_MENU_HMENU), 2);
#if defined(WIN32)
		RemoveMenu (hMenu, 0, MF_BYPOSITION);
#else
		RemoveMenu (hMenu, 2, MF_BYPOSITION);
#endif // WIN32
		DELETE (_SightMenu);
		_SightCount = 0;
		ActualSight() = -1;
		DELETE (_pSightName);
	}

	DrawMenuBar (CurrActDirisW -> Handle (API_WINDOW_HWND));
}


bool DatenBasisObjekt :: ProcessMenuEvent (int Cmd) 
{
	if (SightMenu() == NULL) return false;

CActDB ActDB (DB());	// GeoDB aktivieren
char MenuString[SIGHTMENUITEM+1];	// Name der neuen Sicht
bool iRebuild = false;

	memset (MenuString, '\0', SIGHTMENUITEM +1);
	if (Cmd == -1) {		// aktuelle Sicht nochmal aufbauen
		Cmd = ActualSight();
		iRebuild = true;
	}
	if (Cmd <= -IDM_SIGHTS) {	// auf jeden Fall neu zeichnen
		Cmd = -Cmd;
		iRebuild = true;
	}

	if (Cmd >= IDM_SIGHTS && Cmd < IDM_SIGHTS+Sights()) {
	// Neue Ansicht aktivieren, dazu aktivierten MenuText lesen
		GetMenuString (SightMenu()->Handle(API_MENU_HMENU), Cmd, 
			       MenuString, SIGHTMENUITEM, MF_BYCOMMAND);

	// evtl. als DefaultSicht setzen
		if (GetKeyState (VK_CONTROL) < 0) {
			ProFile (DB().GetDBName()).SetStandardSight (MenuString);
		}

	// eine Ansicht wurde ausgewählt
		if (!iRebuild && Cmd == ActualSight())
			return false;	// bereits aktive Ansicht wurde gewählt

		if (DEXN_SightToSelect (MenuString))
			return false;	// jemand hat was dagegen
		
		if (Cmd != ActualSight())
			DEX_RemoveAllORWnds();	// alle ORFenster weg, wenn neue Sicht

		if (!ActivateSight (MenuString))
			return false;

	// neue Ansicht markieren
		SightMenu() -> CheckItem (Cmd);
		ActualSight() = Cmd;
	} else
		return false;           // alle anderen Kommandos

// Identifikatorbaum von nicht mehr benötigten temporären Idents bereinigen
	RemoveTempIdents();
	CIdentifikator :: ReleaseIgnoreTree();		// statische Funktion
	
	if (!iRebuild) DEXN_SightSelected (MenuString);

return true;    // ok, neue Ansicht aktiv
}

// aktivieren einer vorgebebenen Sicht ----------------------------------------
extern void EXPORTTRIAS ResetPaintFlag (void *pObj);

bool DatenBasisObjekt :: ActivateSight (char *pSight)
{
CEierUhr Wait (CurrActDirisW);

	if (ActualSight() != -1) {
		SightMenu() -> unCheckItem (ActualSight());  // unCheck'en
		ActualSight() = -1;	// keine MenuSicht mehr aktiv
	}

	if (pSight == NULL) return false;

// temporäre Idents rauswerfen
	DeleteTempIdents();

	SetActiveSightName (pSight);

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
	
		for (int i = 0; i < Cnt; i++) {
		ErrCode EC;
		short iDBOTypes = 0;

		// doppelte Identbehandlung verhindern (nur 1. verwerten)
			if (FindLong (Id, Cnt, Id[i]) != i) continue;

		// wenn dieser Id in der DB nicht existiert, dann weiter
			if ((EC = DB().FindId (Id[i], NULL, &iDBOTypes)) != EC_OKAY) {
				if (EC == WC_NOTFOUND) continue;
				return false;
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
						MenuSight.GetTypes (Id[i], false)
					);
			} else {
			// VisInfo holen
				fSpec = MenuSight.GetCompleteVisInfo (Id[i], NULL, 
							(VisInfo **)pVI, iDBOTypes);

			// wenn was sein soll und nichts gegeben ist, dann Standard generieren
				fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, fSpec);
			}

		// neuen Satz generieren
			if (!Idents().AddIdent (Id[i], pVI, fSpec, hPalette))
				continue;

			if (tID.Find(&Id[i])) {
			CIdentifikatorLock l(tID);

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
					
					pId -> DType() = DEXN_DrawIdentifikator (Id[i]);
					pId -> SetSpecial (fSpec);
					pId -> SetOTypes (iOldOTypes);
//					l -> EnablePainting (iDBOTypes);
				} else
					continue;
			} else
				continue;
		}
	}
	DELETE (Id);      // Feld wieder freigeben
	DELETE (pVTypes);

// evtl. SichtContainer einstellen
ObjContainer OC (0, 0, 0, 0);

	if (GetActSichtCont (&OC, pSight) == EC_OKAY && OC.isValid())
//	    && OC < GetExtend()) 
	{
		DEX_SetActiveSightContainer (OC); 
	}

// wenn Legende aktiv ist, dann diese neu zeichnen
	LegendToRepaint = true;		// im Hintergrund Legende laufend halten
	if (pLegende) 
		pLegende -> SetCaption (pSight);
	SetPaintFlag (PF_NOTDRAWED);	// Sicht ist wieder gültig

return true;
}

// Namen der aktuellen Ansicht liefern ----------------------------------------
char *DatenBasisObjekt :: GetActiveSightName (char *pBuffer, int maxLen) 
{
	if (ActualSight() != -1 && ActiveSightName() != NULL) {
	// Namen der aktiven Sicht kopieren, wenn aktuelle Sicht existiert
	int locLen = maxLen != -1 ? maxLen : strlen(ActiveSightName())+1;

		TX_ASSERT(TIsValidAddress(pBuffer, locLen, true));	// writeable!
		strncpy (pBuffer, ActiveSightName(), locLen);
		pBuffer[locLen-1] = '\0';
	} else 
	// temporäre Sicht oder keine Sicht ausgewählt
		*pBuffer = '\0';

return pBuffer;
}

void DatenBasisObjekt :: SetActiveSightName (char *pNewName)
{
	if (pNewName == NULL) return;

	DELETE (_pSightName);
	_pSightName = StrDup (pNewName, RC_SetActiveSightName);

// Sicht wieder finden
HMENU hMenu = (((IrisWind *)CurrActDirisW) -> MainMenu()) -> Handle (API_MENU_HMENU);

	for (register int i = 0; i < Sights(); i++) {
	char MenuItem[SIGHTMENUITEM+1];

		GetMenuString (hMenu, IDM_SIGHTS+i, MenuItem, 
			       SIGHTMENUITEM, MF_BYCOMMAND);
		if (!strcmp (MenuItem, _pSightName))
			break;
	}

// wenn gefunden, dann löschen
	if (i < Sights())	// wenn diese Ansicht derzeit aktiv ist, dann CheckMark löschen
		ActualSight() = IDM_SIGHTS+i;
	else
		ActualSight() = -1;	// nicht gefunden
}


ErrCode DatenBasisObjekt :: GetSightNames (char *Names[], short &numSights) 
{
CActDB ActDB (DB());
ErrCode EC;
DB_ADDR dba;
ErrInstall EI (WC_NOTFOUND);

// ersten SichtNamen suchen
	EC = (ErrCode)z_keyfirst (&dba, SICHTNAME);
	if (EC != EC_OKAY) {
	// Fehler aufgetreten
		if (EC == WC_NOTFOUND) EC = EC_OKAY; // nichts gefunden: OK
		numSights = 0;
		return EC;                           // sonstiger Fehler
	}

// für alle weiteren ID's
register int i, j;

	for (i = 0, j = 0; i < numSights; i++) {
	char SichtName[SIGHTMENUITEM+1];

	// ID aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (SichtName);
		SichtName[SIGHTMENUITEM] = '\0';
		if (EC != EC_OKAY) break;

	// wenn nicht DefaultVisInfo oder evtl. SystemSicht, dann bearbeiten
	extern short SystemSightFlag;

		if (strcmp (SichtName, ResString (IDS_DEFAULTVISINFO, 40)) &&
		    (SystemSightFlag || strncmp (SichtName, "__", 2))) 
		{
		// Sichtnamen merken
			Names[j] = new char [strlen(SichtName)+1];
			if (Names[j] == NULL) {
				numSights = j;
				return (ErrCode)db_error (EC_NOMEMORY, RC_GetSightNames);
			}
			strcpy (Names[j], SichtName);
#if defined(MSWIND)
		// Zeichensatzkonvertierung
			OemToAnsi (Names[j], Names[j]);
#endif
			j++;		// Sicht existiert jetzt vollständig
		}
	// nächsten Schlüssel suchen
		EC = (ErrCode)z_keynext (&dba, SICHTNAME);
		if (EC != EC_OKAY)
			break;
	}
	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK
	numSights = j;

return EC;
}

ErrCode DatenBasisObjekt :: WriteSightIDs (char *Sight, long *IDs, 
					   short numIDs, short *pTypInfo,
					   Sicht *pTargetSight, 
					   short fFlags, long CObj) 
{
// CActDB ActDB (DB());
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
			DEXN_SightDeleted (Sight);	// Vollzug melden
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
			Idents().IdentTree().Every (ResetPaintFlag);
			Idents().PrioTree().EveryDelete();	// Prioritäten werden neu aufgebaut
			iTargetRenamed = true;
		}
	}

// Sicht muß u.U. neu angelegt werden, da gleichnamige alte Sicht 
// umbenannt wurde
Sicht NewSight (DB(), Sight);

// Clipping Objekt setzen
	if (CObj != -1L) NewSight.SetObjRgn (CObj);

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
			if (t.Find(&IDs[i])) {
			// VisInfo aus Speicher holen
			CIdentifikatorLock l(t);

				if (l) fSpec = l -> GetCompleteVisInfo ((VisInfo **)pVI, pTypInfo[i]);
			} else if (pTargetSight != NULL) {
			// VisInfo's aus Bezugssicht holen
				fSpec = pTargetSight -> GetCompleteVisInfo (IDs[i], NULL, (VisInfo **)pVI, pTypInfo[i]);
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
	
	{	// Die Welt von diesem Ereignis in Kenntnis setzen
	VIEWCREATED VC;

		INITSTRUCT (VC, VIEWCREATED);
		VC.m_pTarget = pTargetSight -> Name();
		VC.m_pNewName = NewSight.Name();
		if (fFlags & WSDelView || iTargetRenamed) 
			VC.m_iMode |= VCDeleteTarget;
		if (fFlags & WSActVis) 
			VC.m_iMode |= VCUseTargetView;
		if (lMerkmale != 0L || lRelationen != 0L)
			VC.m_iMode |= VCFeaturesMoved;
		DEXN_SightCreated(VC);
	}

// wenn Sicht umbenannt wurde ode alte Sicht gelöscht werden soll, 
// dann diese nun alte Sicht löschen
	if (iTargetRenamed || fFlags & WSDelView) {
		NewSight.MoveAttribs (pTargetSight);	// Merkmale und Relationen retten
		pTargetSight -> DelSight(false);
	} else if (lMerkmale != 0 || lRelationen != 0) {
		NewSight.SetAttribs (lMerkmale, lRelationen);
	}

// wenn alles ok ist, dann != 0 liefern, wenn neue Sicht gleich der alten 
// Sicht ist
return (ErrCode)(EC == EC_OKAY ? (iTargetRenamed ? WC_RETURN : EC_OKAY) : EC);
}

// die EnumerationsFunktion muß 'PASCAL' sein
extern "C" {
inline bool EnumSightsCallback (bool (*pFcn)(char *, bool, void *), 
			        char *SichtName, bool iNext, void *pData) 
{
	return ((ENUMNOKEYCALLBACK)pFcn)(SichtName, iNext, pData);
}

}

// Enumeration der Sichten dieser DatenBasis ----------------------------------
bool DatenBasisObjekt :: EnumSights (bool (*pFcn)(char *, bool, void *), void *pData)
{
CActDB ActDB (DB());
ErrCode EC;
DB_ADDR dba;
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);

// ersten SichtNamen suchen
	EC = (ErrCode)z_keyfirst (&dba, SICHTNAME);
	if (EC != EC_OKAY) {
	// Fehler aufgetreten
		if (EC == WC_NOTFOUND) 
			EC = EC_OKAY; // nichts gefunden: OK
		return EC == EC_OKAY;		// sonstiger Fehler
	}

bool iNext = true;

	while (iNext) {
	char SichtName[SIGHTMENUITEM+1];

	// ID aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (SichtName);
		SichtName[SIGHTMENUITEM] = '\0';
		if (EC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		EC = (ErrCode)z_keynext (&dba, SICHTNAME);
		if (EC != EC_OKAY)
			iNext = false;

	// wenn nicht DefaultVisInfo, dann bearbeiten
		if (strcmp (SichtName, ResString (IDS_DEFAULTVISINFO, 40))) {
			GetKeyContext (&KC);
			OemToAnsi (SichtName, SichtName);
			{
			CActDB UserDB (ActDB.GetOldDB());

				if (EnumSightsCallback (pFcn, SichtName, iNext, pData) == false)
					return false;
			}
			SetKeyContext (&KC);
		}
	}
	if (EC == WC_NOTFOUND) EC = EC_OKAY;	// nichts mehr gefunden: OK

return EC == EC_OKAY;
}


// Löschen einer Sicht --------------------------------------------------------
bool DatenBasisObjekt :: DeleteView (char *pView)
{
	if (!pView) return false;

// diese Sicht ist die aktuelle
	if (ActiveSightName() && !strcmp (pView, ActiveSightName())) {
		CurrActDirisW -> CanvasErase();		// Bildschirm löschen
		DEXN_SightSelected (NULL);
		ActivateSight (NULL);			// keine Sicht aktiv
		DEX_RemoveAllORWnds();			// ORFenster weg
		
	// ObjektListe löschen
		Idents().ResetAllLoaded();		// Nichts mehr geladen
		Shapes().EveryDelete ();		// alle Objekte l”schen
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
char *pStandardSight = PF.GetStandardSight();

	if (!strcmp (pStandardSight, pView))
	// Standardansicht wird gelöscht: 'Standard=...' löschen
		PF.SetStandardSight (NULL);

// Punkt aus Menu löschen
	DeleteSightMenuItem (pView);
	
return true;
}
