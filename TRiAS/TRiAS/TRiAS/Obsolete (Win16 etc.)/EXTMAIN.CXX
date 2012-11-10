// Hauptfenster, Erweiterungen und deren Verwaltung, sonstiges ----------------
// File: EXTMAIN2.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <shellapi.h>
#include <xtensnxx.h>

#undef NAKEDEVT

#include "menuitem.hxx"
#if defined(WIN32)
#include <registry.hxx>
#include <checklst.hxx>
#include "managext.hxx"
#include "extqnfy2.hxx"
#else
#include "extload.hxx"
#include "extqnfy.hxx"
#endif // WIN32

#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX

#include <initguid.h>
#include <dirisole.h>
#include <xtsnguid.h>

#if defined(WIN32)
#include <undoguid.h>
#include <iunredo.hxx>
#include <undohelp.hxx>
#endif // WIN32

#if !defined(WIN32)
#include <olenls.h>
#include <dispatch.h>
#include <olectl.h>
//#include <olectlid.h>		// IID_IClassFactory2
#else
#include <olectl.h>
//#include <olectlid.h>		// IID_IClassFactory2
#endif

#include <ienumobj.hxx>
#include "ienumonr.hxx"
#include "selident.hxx"
#include "objprop.hxx"
#include "license.hxx"
#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInstance;
extern short g_iHideFlags;

extern class Window *CurrActDirisW;
HWND __hWndM;		// HauptfensterHandle (für alle möglichen Messages)

// Funktionsdeklarationen -----------------------------------------------------
void MenuEnable (pMenu, int, bool);
#if !defined(WIN32)
bool IsWin32s (void);
#endif

extern "C" {
	_TRIAS01_ENTRY void FUNCTYPE InitTrias01 (HWND, UINT, UINT, UINT);
	_TRIAS02_ENTRY void FUNCTYPE InitTrias02 (HWND, UINT, UINT, UINT);
	_TRIAS03_ENTRY void FUNCTYPE InitTrias03 (HWND, UINT, UINT, UINT);
}

void AddMenuOffset (HMENU, short);

// Registrierte Messages/HauptFensterHandle -----------------------------------
UINT __DexCmd = 0;	// MessageWert für allgemeine Schnittstelle
UINT __DexReg = 0;	// MessageWert für NotificationMessages
UINT __DexUnReg = 0;	// MessageWert für Notification abmelden
UINT __DexxCmd = 0;	// MessageWert für C++ Schnittstelle
UINT __DexNotify = 0;	// MessageWert für NotifikationsMeldung

// extern "C" LRESULT PASCAL DexExtensionProcExt (UINT uiMsg, WPARAM w, LPARAM l);

HWND WendtWnd;

// Konstruktor/Destruktor der neuen HauptfensterKlasse ------------------------
ExtDirisWindow :: ExtDirisWindow (Rectangle &MWnd)
		: IrisWind (MWnd), m_eiExt (EC_EXTINITFAILURE, ReportExtError)
{
// Sprungverteiler Initialisieren
	FInitDexProcs();	// wenn was schief geht, dann über switch arbeiten

// Daten initialisieren
	m_iMenuOffset = DEX_FIRSTMENUOFFSET - DEX_MENUOFFSETDELTA;

// ExtensionList anlegen
	m_pEL = new ExtensionList;
	if (m_pEL == NULL) {
 		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
	  	return;
	}  

// MessageHash anlegen
	m_pQNH = new QueryNotifyHash();
	if (m_pQNH == NULL) {
		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
		return;
	}

#if defined(WIN32)
// UndoredoVerwaltung
	m_pUndoRedo = CManageUndoRedo :: CreateInstance (DEFAULTUNDOCNT);
	if (m_pUndoRedo == NULL) {
		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
		return;
	}
#endif // WIN32

// allgemeine SchnittstellenMessage
	__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));

// NotificationSchnittstellenMessages
	__DexReg = RegisterWindowMessage (ResString (IDS_QNFYMESSAGE, 30));
	__DexUnReg = RegisterWindowMessage (ResString (IDS_QNFYUNREGMESSAGE, 30));
	__DexNotify = RegisterWindowMessage (ResString (IDS_NOTIFICATION, 30));

// C++ - SchnittstellenMessage
	__DexxCmd = RegisterWindowMessage (ResString (IDS_DEXXMESSAGE, 30));
	if (__DexCmd == 0 || __DexReg == 0 || 
	    __DexUnReg == 0 || __DexNotify == 0 || __DexxCmd == 0) 
	{
		db_error (EC_NODEXMESSAGE, RC_ctExtDirisWindow);
		return;
	}
	
	__hWndM = Handle (API_WINDOW_HWND);

// alle zu ladenden Extensions laden
	{
	ErrInstall EI (EC_EXTINITFAILURE);	// Fehlermeldung unterdrücken
	ResString Profile (IDS_PROFILE, 15);

		LoadAllExtensions (Profile);
	}

// alle anderen Module von TRIAS(R) initialisieren ----------------------------
WendtWnd = Handle(API_WINDOW_HWND);
	InitTrias01 (Handle(API_WINDOW_HWND), __DexCmd, __DexxCmd, __DexNotify);
	InitTrias02 (Handle(API_WINDOW_HWND), __DexCmd, __DexxCmd, __DexNotify);
	InitTrias03 (Handle(API_WINDOW_HWND), __DexCmd, __DexxCmd, __DexNotify);

// Dumy MenuPunkt entfernen
	MainMenu() -> DeleteItem (IDM_DUMMY);

// Flags initialisieren
	m_fToShow = true;
	m_fIsShown = false;

// Dragging initialisieren, wenn ales andere initialisiert wurde
	DragAcceptFiles (Handle (API_WINDOW_HWND), true);
}

ExtDirisWindow :: ~ExtDirisWindow (void) 
{
// Dragging wieder ausschalten
	DragAcceptFiles (Handle (API_WINDOW_HWND), false);

#if defined(WIN32)
	DELETE (m_pUndoRedo);	// UndoRedoVerwaltung
#endif // WIN32

	DELETE (m_pEL);		// alle geladenen Extensions rauswerfen
	DELETE (m_pQNH);	// HashTabelle freigeben

// Sprungverteiler freigeben
	DELETE_VEC (m_cbDexProcs/*, m_iDexProcsNum*/);
	
// globale Variablen nullsetzen
	__DexCmd = 0;
	__DexxCmd = 0;
	__DexNotify = 0;
	__DexReg = 0;
	__DexUnReg = 0;
	__hWndM = 0;
}

// Memberfunktionen der neuen Hauptfensterklasse ------------------------------
void ExtDirisWindow :: MenuCommand (MenuCommandEvt e) 
{
// MenuEvents aus NutzerMenu herausfiltern
	if (m_pEL -> DispatchMenuCommand (e)) return;

// MenuEvents für ExtDirisWindow herausfiltern 
short iItem = e.GetItemID();

	switch (iItem) {
	case IDM_LOADEXTENSION:		// eine Extension laden
		doLoadExtension();
		break;

	case IDM_UNLOADEXTENSION:	// eine Extension freigeben
		doUnLoadExtension();
		break;

	case IDM_OPENOLD1:      	// müssen fortlaufend sein
	case IDM_OPENOLD2:
	case IDM_OPENOLD3:
	case IDM_OPENOLD4:
		{	// alte DB schließen
			if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
			// wenn nicht geschlossen wurde, dann weiter
				if (CloseDB () != EC_OKAY) break;
				DELETE (DRO);
				UnLoadLocalExtensions();
#if defined(WIN32)				
				m_pUndoRedo -> EveryDelete();
#endif
			}
		}
		// durchfallen ...

	case IDM_OPEN:
		IrisWind :: MenuCommand (e);
		if (m_pDBOs -> Count() && DBO().DB().isOpened()) 	// nur wenn wirklich geschlossen wurde
			LoadLocalExtensions();
		break;
		
	case IDM_CLOSE:
		IrisWind :: MenuCommand (e);
		if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened()) {// nur wenn wirklich geschlossen wurde
			UnLoadLocalExtensions();
#if defined(WIN32)
			m_pUndoRedo -> EveryDelete();
#endif
		}
		break;
		
	case IDM_EXIT:          		// Programm beenden
		if (QueryClose ((Event &)e))	// Fragen, ob wirklich beenden  
			App :: Quit ();         // raus
		break;

	case IDM_IMPORT:
		if (m_pDBOs -> Count() && DBO().DB().isOpened())
			doImport();
		break;

#if defined(WIN32)
	case IDM_UNDO:
		if (GetKeyState (VK_CONTROL) >= 0) {
		CEierUhr Wait (this);

			if (m_pUndoRedo -> Undo() & UNDOREDOCAPS_REPAINT)
				DEX_RePaint();
		} else 
			ShowUndoList();
		break;

	case IDM_REDO:
		if (GetKeyState (VK_CONTROL) >= 0) {
		CEierUhr Wait (this);

			if (m_pUndoRedo -> Redo() & UNDOREDOCAPS_REPAINT)
				RePaint();
		} else
			ShowRedoList();
		break;
#endif // WIN32
		
	case IDM_OBJPROPERTIES:
		GenObjectProperties();
		break;

	default: 
	// nichts gefunden, also weiterleiten
		IrisWind :: MenuCommand (e);
		break;
	}
}


// Laden aller Projektbesogenen Erweiterungen --------------------------------
bool ExtDirisWindow :: LoadLocalExtensions (void)
{
char cbActProject[_MAX_PATH];
char *pIni = DEX_GetActiveProject (cbActProject);
		
	if (pIni) {
	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_PATH];
	char *pFName = new char [_MAX_FNAME];
		
	// Pfad der lokalen INI-Datei zusammenbauen
		_splitpath (pIni, pDrive, pPath, pFName, NULL);
		_makepath (pIni, pDrive, pPath, pFName, ResString (IDS_EXTPROFILE, 5));
		LoadAllExtensionsINI (pIni, false);

	// Speicher wieder freigeben
		DELETE (pDrive);
		DELETE (pPath);
		DELETE (pFName);
		return true;
	}

return false;
}


// MenuPunkt wurde ausgewählt (nicht selektiert) ------------------------------
void ExtDirisWindow :: MenuSelect (MenuSelectEvt e) 
{
// MenuEvents aus NutzerMenu herausfiltern
CRing r (*m_pEL);
short iItem = e.GetItemID();

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;
		if (l -> isMyID (iItem)) {
			l -> MenuSelect (e);
			return;		// ok, weiter
		}
	}
	IrisWind :: MenuSelect (e);
}

void ExtDirisWindow :: MenuInit (MenuInitEvt e) 
{
CRing r(*m_pEL);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;

	short iRet = 0;

		if ((iRet = l -> isMyMenu (e)) != 0) {
		// wenn Menu gefunden wurde
			l -> MenuInit (e);
			if (iRet == 1) return;		// ok, Ende der Vorstellung
		}
	}	

#if !defined(WIN32)
// eigene MenuCommandos verwalten
short cntNotUnLoadable = 0;
short cntLoaded = m_pEL -> CountLoaded (&cntNotUnLoadable);
short cntUnLoaded = short (m_pEL -> Count() - cntLoaded);

	cntLoaded -= cntNotUnLoadable;		// nicht entladbare berücksichtigen
	MenuEnable (MainMenu(), IDM_LOADEXTENSION, cntUnLoaded);
	MenuEnable (StartUpMenu(), IDM_LOADEXTENSION, cntUnLoaded);

	MenuEnable (MainMenu(), IDM_UNLOADEXTENSION, cntLoaded);
	MenuEnable (StartUpMenu(), IDM_UNLOADEXTENSION, cntLoaded);
#else
// Undo/Redo
LPTSTR pDesc = NULL;
HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);
char cbItem[64];

// UndoMenuPunkt behandeln
	if (m_pUndoRedo -> GetNextUndoDesc (&pDesc) & UNDOREDOCAPS_CANUNDO) {
	char *pAnsi = strtok (pDesc, "|");	// nur erste Phrase

		if (pAnsi == NULL) pAnsi = pDesc;

		if (pAnsi) wsprintf (cbItem, ResString (IDS_UNDOTEMPL, 30), pAnsi);
		else	   strcpy (cbItem, ResString (IDS_UNDOUNKNOWN, 30));

		ModifyMenu (hMenu, IDM_UNDO, MF_BYCOMMAND|MF_ENABLED, IDM_UNDO, cbItem);
	} else {
		ModifyMenu (hMenu, IDM_UNDO, MF_BYCOMMAND|MF_GRAYED, 
			    IDM_UNDO, ResString (IDS_UNDONOTHING, 40).Addr());
	}
	if (pDesc) {
		CoTaskMemFree (pDesc);
		pDesc = NULL;
	}

// RedoMenuPunkt behandeln
	if (m_pUndoRedo -> GetNextRedoDesc (&pDesc) & UNDOREDOCAPS_CANREDO) {
	char *pAnsi = strtok (pDesc, "|");	// nur erste Phrase

		if (pAnsi == NULL) pAnsi = pDesc;

		if (pAnsi) wsprintf (cbItem, ResString (IDS_REDOTEMPL, 30), pAnsi);
		else	   strcpy (cbItem, ResString (IDS_REDOUNKNOWN, 30));

		ModifyMenu (hMenu, IDM_REDO, MF_BYCOMMAND|MF_ENABLED, IDM_REDO, cbItem);
	} else {
		ModifyMenu (hMenu, IDM_REDO, MF_BYCOMMAND|MF_GRAYED, 
			    IDM_REDO, ResString (IDS_REDONOTHING, 40).Addr());
	}
	if (pDesc) CoTaskMemFree (pDesc);
#endif

// nichts gefunden, also an IrisWind weiterleiten
	IrisWind :: MenuInit (e);
}


// eigener Event-Dispatcher, der Anforderungen der Erweiterung an Diris abfängt
LRESULT EXPORTTRIAS ExtDirisWindow :: Dispatch (Event e) 
{
NakedEvt &ne = (NakedEvt &)e;
LRESULT R;

// interne NotifikationsVerarbeitung
	if (ne.wmsg() == __DexNotify)
		DispatchNotification (ne.wparam(), ne.lparam());

// an alle Erweiterungen verschicken, die es wollen
	if (m_pQNH && (R = m_pQNH -> Dispatch (e)) != 0)
		return R;

	if (ne.wmsg() == __DexCmd) {
	// diese Meldung ist für uns
		return FullFillWill (ne.wparam(), ne.lparam());
	} else if (ne.wmsg() == __DexxCmd) {
		return FullFillCPPWill (ne.wparam(), ne.lparam());
	} else if (ne.wmsg() == __DexReg) {	// Notifikation anfordern
		if (m_pQNH) {
		Extension *pExt = m_pEL -> FindExt ((HDEX)ne.wparam());

			if (pExt == NULL) return false;
			return m_pQNH -> RegisterQNFY (*pExt, __hWndM, ne.lparam());
		} else	   return false;
	} else if (ne.wmsg() == __DexUnReg) {	// Notifikation abmelden
		if (m_pQNH) {
		Extension *pExt = m_pEL -> FindExt ((HDEX)ne.wparam());

			if (pExt == NULL) return false;
			return m_pQNH -> UnRegisterQNFY (*pExt, ne.lparam());
		} else	   return false;
	} 
	return IrisWind :: Dispatch (e);	// weiterleiten
}

extern "C" {

LRESULT EXPORTTRIAS WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	LRESULT R;
	
	// an alle Erweiterungen verschicken, die es wollen
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexCmd, w, l)) != 0)
			return R;
		return ((ExtDirisWindow *)CurrActDirisW) -> FullFillWill (w, l);
	}
		
return SendMessage(__hWndM, __DexCmd, w, l);
}


LRESULT EXPORTTRIAS WINAPI DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	LRESULT R;
	
	// an alle Erweiterungen verschicken, die es wollen
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexxCmd, w, l)) != 0)
			return R;
		return ((ExtDirisWindow *)CurrActDirisW) -> FullFillCPPWill (w, l);
	}
		
return SendMessage(__hWndM, __DexxCmd, w, l);
}


LRESULT EXPORTTRIAS WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{	// Message muß gepostet werden
	if (__hWndM)
		return PostMessage (__hWndM, __DexNotify, w, l);

return false;
}

LRESULT EXPORTTRIAS WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
LRESULT R = false;

	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	
		pW -> DispatchNotification (w, l);	// interne NotifikationsVerarbeitung

	// an alle Erweiterungen verschicken, die es wollen
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexNotify, w, l)) != 0)
			return R;
	} else	// Notanker
		return SendMessage(__hWndM, __DexNotify, w, l);

return R;
}

LRESULT EXPORTTRIAS WINAPI DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost)
{
	if (fPost)
		return PostMessage (__hWndM, __DexNotify, w, l);
		

LRESULT R = false;

	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	
		pW -> DispatchNotification (w, l);	// interne NotifikationsVerarbeitung

	// an alle Erweiterungen verschicken, die es wollen
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexNotify, w, l)) != 0)
			return R;
	} else	// Notanker
		return SendMessage(__hWndM, __DexNotify, w, l);

return R;
}

}


// Laden und freigeben einer Erweiterung --------------------------------------
extern "C" {
_TRIAS_ENTRY DWORD EXPORTTRIAS WINAPI DefTriasExtensionProc (HDEX, UINT, WPARAM, LPARAM);
}

HDEX ExtDirisWindow :: LoadExtension (
		LPCSTR pExtName, LPCSTR pDLLName, short toLoad, 
		EXTENSIONFLAG rgFlags)
{
// wenn Erweiterung bereits geladen ist, dann nicht mehr laden
short isLoaded = 0;

	{
	HDEX hDex = 0;
	
		if (toLoad && 
		    (isLoaded = m_pEL -> isLoaded (pDLLName, hDex)) >= toLoad) {
			m_pEL -> AddRef (pDLLName);
			return hDex;
		}
	}

// wenn kein Name gegeben ist, dann Versuchen diesen zu finden
char *pLocExtName = NULL;

	if (pExtName == NULL) {
		pLocExtName = m_pEL -> RetrieveExtName (pDLLName);
		if (pLocExtName == NULL) {
		// zusätzlich in die Liste aufnehmen
			pLocExtName = StrDup (pDLLName, RC_LoadExtension);
			if (pLocExtName == NULL) 
				return 0;		// Fehler
			rgFlags = EXTENSIONFLAG(rgFlags & ~EF_Global);
		}
		pExtName = pLocExtName;
	}

// Extension bilden und in Baum reinhängen
Extension *pExt;

// Flags mit evtl. bekannter Extension mergen
	rgFlags = EXTENSIONFLAG(rgFlags | m_pEL -> GetFlags (pDLLName));

// Testen, ob der pDLLName ein Dateiname ist, oder ob es ein ProdID ist.
// Wenn pDLLName als Datei existiert, dann annehmen, daß es kein ProgID ist.
#if defined(WIN32)
DLLBind *pDLL = DLLBind :: CreateInstance (pDLLName, 
			DONT_RESOLVE_DLL_REFERENCES|LOAD_LIBRARY_AS_DATAFILE);
#else
DLLBind *pDLL = DLLBind :: CreateInstance (pDLLName);
#endif

// neue Extension anlegen, wenn sie noch nicht da ist
	if (pDLL != NULL) {
		delete pDLL;	// wieder freigeben
		if ((pExt = new CDirectExtension (Handle (API_CLIENT_HWND), 
					pExtName, pDLLName, toLoad)) == NULL) 
		{
			DELETE (pLocExtName);
			db_error (EC_NOMEMORY, RC_LoadExtension);
			return 0;
		}
	} else {
	// pDLLName ist ProgID
	CLSID clsID;
	
		if (FAILED(CLSIDFromProgID (WideString(pDLLName), &clsID))) {
			DELETE (pLocExtName);
			db_error (EC_EXTINITFAILURE, RC_LoadExtension);
			return 0;
		}
			
		if ((pExt = new COleExtension (Handle (API_CLIENT_HWND),
				pExtName, pDLLName, clsID, toLoad)) == NULL) 
		{
			DELETE (pLocExtName);
			db_error (EC_NOMEMORY, RC_LoadExtension);
			return 0;
		}
	}
	pExt -> SetGlobal (rgFlags & EF_Global);
	pExt -> SetUnLoadable (rgFlags & EF_UnLoadable);
	pExt -> SetVisible (rgFlags & EF_Visible);
	pExt -> SetImport (rgFlags & EF_CanImport);

// MenuOffset neu berechnen und an Extension weiterleiten
TRIASLOADEX DLoad;
HDEX hDex = NULL;

	if (toLoad) {
		if (!isLoaded) {
		// Extension zum ersten mal zu laden
			m_iMenuOffset += DEX_MENUOFFSETDELTA;

			memset (&DLoad, '\0', sizeof (TRIASLOADEX));
			DLoad.m_dwSize = sizeof (TRIASLOADEX);
			DLoad.m_wMenuDelta = m_iMenuOffset;
			DLoad.m_fcDef = m_pEL -> DefaultProc();
//			DLoad.m_fcDef = (DEXCALLBACK)DexExtensionProcExt;
			DLoad.m_iMode = toLoad;
		
			if ((hDex = pExt -> Load (DLoad)) == 0) {
				DELETE (pLocExtName);
				db_error (EC_EXTINITFAILURE, RC_LoadExtension);
				DELETE (pExt);
				return 0;
			}

			pExt -> MenuOffset() = m_iMenuOffset;	// MenuOffset eintragen
			pExt -> MenuHandle() = DLoad.m_hMenu;	// MenuHandle merken
			pExt -> MenuString().assign (DLoad.m_szMenuName, DEX_MENUNAMELEN);
			pExt -> ORMenuHandle() = DLoad.m_hORMenu;
			pExt -> ORMenuString().assign (DLoad.m_szORMenuName, DEX_MENUNAMELEN);
		} else {
		// ist bereits geladen, soll sichtbar werden
		CRing r(*m_pEL);
			
			for (r.First(); r.Valid(); r.Next()) {
			ExtensionLock l(r);

				if (!l || (l -> ExtName() != pExtName)) 
					continue;

				pExt -> MenuOffset() = l -> MenuOffset();
				pExt -> MenuHandle() = l -> MenuHandle();
				pExt -> MenuString() = l -> MenuString();
				pExt -> ORMenuHandle() = l -> ORMenuHandle();
				pExt -> ORMenuString() = l -> ORMenuString();
				break;		// gefunden
			}
		}
	} 

// Extension rausnehmen, um sie neu reinhängen zu können
	UnLoadExtension (pExtName, false);

// Extension in Liste einhängen
ExtensionCreator EC (*m_pEL);
Extension *pNewExt;

	if (pExt -> isA() == Extension::DirectExt) {
		pNewExt = Create (EC, CDirectExtension)(*(CDirectExtension *)pExt); 
	} else {
		pNewExt = Create (EC, COleExtension)(*(COleExtension *)pExt); 
	}

	DELETE (pExt);	// altes 'template' freigeben
	if (pNewExt == NULL) 
	{
		db_error (EC_NOMEMORY, RC_LoadExtension);
		DELETE (pLocExtName);
		return 0;
	}

	EC.Insert();	// wirklich in den Baum speichern

// wenn nicht geladen werden soll, dann raus
	if (!toLoad) {
		DELETE (pLocExtName);
		return 0;
	}

// Menu mit MENUOFFSET korrigieren
	if (!isLoaded) {
		AddMenuOffset (pNewExt -> MenuHandle(), m_iMenuOffset);
		AddMenuOffset (pNewExt -> ORMenuHandle(), m_iMenuOffset);
	}

// Menu in Hauptfenster einhängen, wenn eines gegeben ist, wenn's gefordert ist
	if (toLoad == LEFullLoad && pNewExt ->MenuHandle() != 0) {
	int nCount = GetMenuItemCount (MainMenu() -> Handle(API_MENU_HMENU));

		pNewExt -> MenuIndex() = nCount -1;	// Position im Menu merken

		InsertMenu (MainMenu() -> Handle(API_MENU_HMENU), nCount -1,
			    MF_POPUP|MF_BYPOSITION, (UINT)DLoad.m_hMenu, 
			    DLoad.m_szMenuName);
		DrawMenuBar (Handle (API_CLIENT_HWND));
	} else
		pNewExt -> MenuIndex() = -1;

	pNewExt -> AddRef();	// Zähler hochsetzen
	pNewExt -> Init (toLoad);	// Erweiterung vom Erfolg des Einbindens 
				// in Kenntnis setzen

	ObjInfoListe.LoadExtension (*pNewExt);

	DELETE (pLocExtName);

return pNewExt -> hLib();		// liefert Handle der geladenen DLL
}

// Extension gezielt freigeben ------------------------------------------------
bool ExtDirisWindow :: UnLoadExtension (const char *pExtName, bool fForce) 
{
// wenn Parameter NULL ist, dann gleich mit Fehler wieder raus
	if (pExtName == NULL) return false;

// Extension in der Liste wiederfinden und rauswerfen
CRing r (*m_pEL);
UINT oldMenuIndex = UINT_MAX;
string strSrch (pExtName);

	for (r.First(); r.Valid(); ) {
	bool toDelete = false;
		{
		ExtensionLock l(r);

			if (!l) continue;
			if (strSrch == l -> ExtName()) {
				if (!fForce && l -> Release() > 0) 
					return true;
					
				if (l -> isLoaded()) {		// DLL rausnehmen
					if (l -> UnLoad()) {
					// darf entladen werden 
						if (l -> MenuHandle() != 0) {
					// HauptMenu behandlen
	
							oldMenuIndex = l -> MenuIndex();
							if (oldMenuIndex != -1) {
							// gefunden: PopupMenu rausnehmen
								RemoveMenu (MainMenu() -> Handle (API_MENU_HMENU), 
									    oldMenuIndex, 
									    MF_BYPOSITION);
								DrawMenuBar (Handle (API_CLIENT_HWND));
							}
						}
						
					// Extension aus ORMenu herausnehmen
						ObjInfoListe.UnLoadExtension (*l);
	
					// alle NotifikationsAnforderungen rauswerfen
						if (m_pQNH) m_pQNH -> UnRegisterAllQNFYs (*l);
        				} else 
        					return false;
				}
				toDelete = true;	// löschen
			}
		}
		if (toDelete) { 
		// Extension löschen und freigeben
			r.Delete(); 
			break; 
		} else if (!r.Next()) 
			return false; 
	}

// wenn kein Menu da war, dann erfolgreich raus
	if (oldMenuIndex == -1) return true;

// alle nachfolgenden MenuPunkte wieder vorziehen
	if (oldMenuIndex != UINT_MAX) {
		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (l && (UINT)l -> MenuIndex() > oldMenuIndex)
				(l -> MenuIndex()) --;
		}
	} else 
		return false;

return true;
}

// Nachfragen, ob die Sitzung wirklich beendet werden soll --------------------
#if defined(WIN32)
bool SavePreloadStatus (const string &strProgID, bool fPreload);
#endif
bool ExtDirisWindow :: QueryClose (Event e) 
{
	if (IrisWind :: myQueryClose (true)) {
	// Liste der Erweiterungen durchgehen und PreLoadStatus wegschreiben
	ProFile PF (ResString (IDS_PROFILE, 20));
	CRing r (*m_pEL);

	// Extension-Zustand in INI-Datei merken
		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (!l) continue;
#if defined(WIN32)
			if (!IsWin32s() && l -> isA() == Extension::OleExt) {
				SavePreloadStatus (l -> DLLName(), l -> isLoaded());
			} else
#endif
			{
			EXTENSIONFLAG rgFlags = l -> GetFlags();
			int iFlag = l -> isLoaded() ? 1 : 0;

				if (!(rgFlags & EF_UnLoadable)) iFlag += EF_UnLoadable;
				if (!(rgFlags & EF_Visible)) iFlag += EF_Visible;
				if (rgFlags & EF_CanImport) iFlag += EF_CanImport;

				PF.SetPreLoad ((char *)l -> ExtName().c_str(), iFlag);
			}
		}
			
	// jetzt Extensions abkopplen und freigeben
		for (r.First(); r.Valid(); r.Next()) {
		string strExtName;
		
			{
			ExtensionLock l(r);

				if (!l) continue;
				strExtName = l -> ExtName();
			}
			UnLoadExtension (strExtName.c_str(), true);	// entladen
		}
		DELETE (m_pEL);		// ExtensionListe freigeben
		return true;		// Ende der Vorstellung
	}

return false;		// nicht rausgehen
}

// Fenster wird geschlossen ---------------------------------------------------
void ExtDirisWindow :: Close (Event e) 
{
	App :: Quit();
}

// ----------------------------------------------------------------------------
// ExtensionList - Memberfunktionen -------------------------------------------
ExtensionList :: ExtensionList (void) 
	       : CListContainer ()
{
	m_pDefaultProc = (FARPROC)DefTriasExtensionProc;
	m_pMIL = NULL;
}

ExtensionList :: ~ExtensionList (void) 
{
	EveryDelete ();

	m_pDefaultProc = NULL;
	DELETE (m_pMIL);
}

void EXPORTTRIAS ExtensionList :: UserDelete (void *pObj)
{
	((Extension *)pObj) -> ~Extension();
}

Extension *ExtensionList :: FindExt (HDEX hDex)
{
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && l -> hLib() == hDex)
			return (Extension *)l;
	}

return NULL;
}

short ExtensionList :: CountLoaded (short *piNotUnLoadable)
{
CRing r(*this);
short iCnt = 0;

	if (piNotUnLoadable) 
		*piNotUnLoadable = 0;	// zählt geladene, nicht entladbare Extensions

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && l -> isLoaded() && l -> isGlobal()) {
			iCnt++;
			if (!l -> isUnLoadable() && piNotUnLoadable) 
				(*piNotUnLoadable)++;
		}
	}

return iCnt;
}

char *ExtensionList :: RetrieveDLLName (LPCSTR pExtName) 
{
CRing r(*this);
string strSrch (pExtName);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> ExtName() == strSrch)) // gefunden
			return StrDup (l -> DLLName().c_str(), RC_RetrieveDLLName);
	}

return NULL;	// nichts gefunden
}

char *ExtensionList :: RetrieveExtName (LPCSTR pDLLName) 
{
CRing r(*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());		// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return StrDup (l -> ExtName().c_str(), RC_RetrieveExtName);
	}

return NULL;	// nichts gefunden
}

// Prüft, ob eine Erweiterung bereits geladen ist -----------------------------
short ExtensionList :: isLoaded (LPCSTR pDLLName, HDEX &hDex) 
{
CRing r(*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {	// gefunden
			hDex = (HDEX)l -> hLib();	// HDEX liefern
			return l -> isLoaded();
		}
	}

return 0;	// nichts gefunden
}

#if 0 // =====================================================================

// Prüft, ob eine Erweiterung global geladen ist ------------------------------
bool ExtensionList :: isGlobal (LPCSTR pDLLName) 
{
CRing r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> isGlobal();
	}

return false;	// nichts gefunden
}


bool ExtensionList :: isUnLoadable (LPCSTR pDLLName) 
{
CRing r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> isUnLoadable();
	}

return false;	// nichts gefunden
}

bool ExtensionList :: isVisible (LPCSTR pDLLName) 
{
CRing r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> isVisible();
	}

return false;	// nichts gefunden
}

bool ExtensionList :: FCanImport (LPCSTR pDLLName) 
{
CRing r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> FCanImport();
	}

return false;	// nichts gefunden
}

#endif // =====================================================================

EXTENSIONFLAG ExtensionList :: GetFlags (LPCSTR pDLLName) 
{
CRing r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> GetFlags();
	}

return (EXTENSIONFLAG)0;	// nichts gefunden
}


// ReferenzZähler für eine Erweiterung richten --------------------------------
long ExtensionList :: AddRef (LPCSTR pDLLName) 
{
CRing r(*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> AddRef();
	}

return -1;	// nichts gefunden
}


long ExtensionList :: Release (LPCSTR pDLLName) 
{
CRing r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) 	// gefunden
			return l -> Release();
	}

return -1;	// nichts gefunden
}



// überprüft, ob ein MenuEvent zu einer Extenson gehört und leitet diesen ggf.
// entsprechend weiter
bool ExtensionList :: DispatchMenuCommand (MenuCommandEvt e, HWND iORMenu)
{
short iItem = e.GetItemID();
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;
		if (l -> isMyID (iItem)) {
			l -> MenuCommand (e, iORMenu);
			return true;		// ok, weiter
		}
	}

return false;
}

// Memberfunktionen für die Extension selbst ----------------------------------
// Konstruktoren/Destruktoren -------------------------------------------------
Extension :: Extension (HWND hWnd, LPCSTR pExtName, LPCSTR pDLLName, int toLoad)
	   : m_strExtName (pExtName),
	     m_strDLLName (pDLLName),
	     m_iToLoad (toLoad)
{
	strupr ((LPSTR)m_strDLLName.c_str());		// GroßBuchstaben

	m_hWnd = hWnd;		// FensterHandle
	m_uiMenuOffset = 0;
	m_hMenuHandle = 0;
	m_iMenuIndex = 0;
	m_hORMenuHandle = 0;
	m_iORMenuIndex = -1;
	m_fIsGlobal = true;
	m_fUnLoadable = true;
#if defined(WIN32)
	m_fVisible = true;
#endif // WIN32
	m_fCanImport = false;
		
	m_ulRefCnt = 0;
}

Extension :: Extension (Extension &Ext) 
	   : m_strExtName (Ext.m_strExtName),
	     m_strDLLName (Ext.m_strDLLName),
	     m_strMenuString (Ext.m_strMenuString),
	     m_strORMenuString (Ext.m_strORMenuString)
{
// Werte aus alter Extension kopieren
	m_hWnd = Ext.hWnd();
	m_uiMenuOffset = Ext.m_uiMenuOffset;

	m_hMenuHandle = Ext.m_hMenuHandle;
	m_hORMenuHandle = Ext.m_hORMenuHandle;
	m_iMenuIndex = Ext.m_iMenuIndex;
	m_iORMenuIndex = Ext.m_iORMenuIndex;

	m_iToLoad = Ext.m_iToLoad;
	m_fIsGlobal = Ext.m_fIsGlobal;
	m_fUnLoadable = Ext.m_fUnLoadable;
#if defined(WIN32)
	m_fVisible = Ext.m_fVisible;
#endif // WIN32
	m_fCanImport = Ext.m_fCanImport;
	
	m_ulRefCnt = Ext.m_ulRefCnt;

// Pointer in alter Extension ausnullen, um doppeltes delete zu vermeiden
	Ext.m_hMenuHandle = 0;
	Ext.m_hORMenuHandle = 0;
	Ext.m_iToLoad = 0;
	Ext.m_ulRefCnt = 0;
	Ext.m_strMenuString.remove();
	Ext.m_strORMenuString.remove();
}

Extension :: ~Extension (void) 
{
	m_hMenuHandle = 0;
	m_hORMenuHandle = 0;
}

EXTENSIONFLAG Extension :: GetFlags (void)
{
EXTENSIONFLAG rgFlags = isGlobal() ? EF_Global : 0;

	if (isUnLoadable()) rgFlags = EXTENSIONFLAG(rgFlags | EF_UnLoadable);
	if (isVisible()) rgFlags = EXTENSIONFLAG(rgFlags | EF_Visible);
	if (FCanImport()) rgFlags = EXTENSIONFLAG(rgFlags | EF_CanImport);

return rgFlags;
}

// Erweiterung alten Typs -----------------------------------------------------
Extension::ExtensionType CDirectExtension :: isA (void) { return DirectExt; }
Extension::ExtensionType COleExtension :: isA (void) { return OleExt; }

CDirectExtension :: CDirectExtension (HWND hWnd, LPCSTR pExtName, 
				      LPCSTR pDLLName, int toLoad)
	       : Extension (hWnd, pExtName, pDLLName, toLoad)
{
	m_pDLL = NULL;
	if (toLoad != false) {
		m_pDLL = new DLLBind (pDLLName);
		if (m_pDLL == NULL) {
			db_error (EC_NOMEMORY, RC_ctExtension);
			m_hWnd = 0;
			m_pExtEntry = NULL;
			return;
		}
		m_pExtEntry = (DEXENTRY)m_pDLL -> GetProcAddress (ResString (IDS_EXTENTRYNAME, 20));
	} else {
	// Extension nicht anbinden
		m_pExtEntry = NULL;
	}
}

CDirectExtension :: CDirectExtension (HWND hWnd, LPCSTR pExtName, 
				      DLLBind *pDLL, LPCSTR pDLLName, 
				      bool toLoad)
	       : Extension (hWnd, pExtName, pDLLName, toLoad)
{
	m_pDLL = pDLL;		// übernimmt Pointer
	if (toLoad != false) 
		m_pExtEntry = (DEXENTRY)m_pDLL -> GetProcAddress (ResString (IDS_EXTENTRYNAME, 20));
	else 	// Extension nicht anbinden
		m_pExtEntry = NULL;
}

CDirectExtension :: CDirectExtension (CDirectExtension &rExt)
		  : Extension (rExt), 
		    m_pExtEntry (rExt.m_pExtEntry), m_pDLL (rExt.m_pDLL)
{
	rExt.m_pExtEntry = NULL;
	rExt.m_pDLL = NULL;
}

CDirectExtension :: ~CDirectExtension (void)
{
// wenn DLL noch geladen ist, dann UnLoad() abarbeiten
	if (m_pDLL) {
		if (hLib() != 0) 
			UnLoad();
		m_pExtEntry = NULL;
		delete m_pDLL;
		m_pDLL = NULL;
	}
}

// Erweiterung, die über OLE geladen wird -------------------------------------
COleExtension :: COleExtension (HWND hWnd, LPCSTR pExtName, LPCSTR pProgID, 
				REFCLSID rClsId, bool toLoad)
	       : Extension (hWnd, pExtName, pProgID, toLoad),
	         m_ClsId (rClsId)
{
	m_pTE = NULL;
	m_pOPs = NULL;
	m_fHasOPs = true;	// erst mal für Angeklagten entscheiden
	m_hDex = NULL;
}

COleExtension :: COleExtension (COleExtension &rExt)
	       : Extension (rExt), m_ClsId (rExt.m_ClsId), m_hDex (rExt.m_hDex)
{
	m_pTE = rExt.m_pTE;
	if (m_pTE) m_pTE -> AddRef();

	m_pOPs = rExt.m_pOPs;
	if (m_pOPs) m_pOPs -> AddRef();
	m_fHasOPs = rExt.m_fHasOPs;
}

COleExtension :: ~COleExtension (void)
{
// wenn DLL noch geladen ist, dann UnLoad() abarbeiten
	if (hLib() != 0) 
		UnLoad();
	if (m_pOPs) m_pOPs -> Release();
	if (m_pTE) m_pTE -> Release();

	if (m_pTE != NULL || m_pOPs != NULL) {
		CoFreeUnusedLibraries();	// DLL freigeben
		m_pTE = NULL;
		m_pOPs = NULL;
	}
	m_hDex = NULL;
}


// virtuelle Funkltionen ------------------------------------------------------
HDEX CDirectExtension :: Load (TRIASLOADEX &DL) 
{
	if (m_pDLL == NULL) {
	// DLL noch nicht angebunden
		m_pDLL = new DLLBind (DLLName().c_str());
		if (m_pDLL == NULL) {
			db_error (EC_NOMEMORY, RC_LoadExtension);
			m_hWnd = 0;
			m_pExtEntry = NULL;
			return 0;
		}
	}
	if (!isLoaded() || m_pExtEntry == NULL) {
		SetLoaded (DL.m_iMode);
		m_pExtEntry = (DEXENTRY)m_pDLL -> GetProcAddress (ResString (IDS_EXTENTRYNAME, 20));
	}
	if (m_pExtEntry != NULL) {
		if ((*m_pExtEntry)(hWnd(), DEX_LOADEXTENSION, (WPARAM)hLib(), (LPARAM)&DL) != 0)
			return 0;
	} else
		return 0;

return hLib();
}

HDEX COleExtension :: Load (TRIASLOADEX &DL) 
{
	if (!isLoaded() || m_pTE == NULL) {
	// DLL noch nicht angebunden
	HRESULT hr = CoCreateInstance (m_ClsId, NULL, CLSCTX_INPROC_SERVER, 
			IID_ITriasXtension, (LPVOID *)&m_pTE);

// TODO: Licensing implementieren
		if (CLASS_E_NOTLICENSED == GetScode(hr))
			hr = HandleLicense();	// Lizensierung behandeln

		if (FAILED(hr)) return NULL;		// Fehler, nicht ladbar
		SetLoaded (DL.m_iMode);
	}
	if (m_pTE == NULL || (m_hDex = m_pTE -> LoadExtension (&DL, hWnd())) == NULL)
		return NULL;

return m_hDex;
}

static void ShowNotLicensed (pWindow pW, string &strName)
{
ResString resCap (IDS_LICENSING, 64);
ResString resLicText (IDS_NOTLICENSED, 256);
string str = resLicText.Addr();
string newText (_MAX_PATH, default_size);

	wsprintf ((LPSTR)newText.c_str(), str.c_str(), strName.c_str());

MessBox mb (resCap, newText.c_str(), pW);

	mb.Show();
}

HRESULT COleExtension :: HandleLicense (void)
{
// versuchen, Erweiterung doch noch zu laden
LPCLASSFACTORY2 pCF2 = NULL;
HRESULT hr = CoGetClassObject (m_ClsId, CLSCTX_INPROC_SERVER, NULL, 
			       IID_IClassFactory2, (LPVOID *)&pCF2);

	if (FAILED(hr)) return hr;	// not available

// ok, jetzt Key abfragen
BSTR bKey;
Window Wnd (m_hWnd);

	{
	CLicenseDlg LDlg (&Wnd, ExtName());

		LDlg.Show (Centre);
		if (0 == LDlg.Result()) {
			ShowNotLicensed (&Wnd, ExtName());
			pCF2 -> Release();
			return ResultFromScode (CLASS_E_NOTLICENSED);
		}
		bKey = LDlg.GetKey();
	}

// jetzt versuchen, mit Lizenz zu laden
	hr = pCF2 -> CreateInstanceLic (NULL, NULL, IID_ITriasXtension, 
					bKey, (LPVOID *)&m_pTE);
	pCF2 -> Release();
	SysFreeString (bKey);

// wenn Lizenz nicht verifiziert werden konnte
	if (CLASS_E_NOTLICENSED == GetScode(hr))
		ShowNotLicensed (&Wnd, ExtName());

return hr;
}

bool CDirectExtension :: UnLoad (void) 
{
	if (isLoaded() && m_pExtEntry != NULL) {
	bool fResult = (bool)(*m_pExtEntry)(hWnd(), DEX_UNLOADEXTENSION, 0, 0);
	
		SetLoaded (fResult ? 0 : isLoaded());
		return fResult;
	}

return false;
}

bool COleExtension :: UnLoad (void) 
{
	if (isLoaded() && m_pTE != NULL) {
	bool fResult = m_pTE -> UnLoadExtension();
	
		SetLoaded (fResult ? 0 : isLoaded());
		m_hDex = NULL;
		return fResult;
	}

return false;
}

// Extension wurde erfolgreich geladen, selbiges kundtun ----------------------
bool CDirectExtension :: Init (short iMode) 
{
	if (isLoaded() && m_pExtEntry != NULL) 
		return (*m_pExtEntry)(hWnd(), DEX_INITEXTENSION, iMode, 0) != 0;

return false;
}

bool COleExtension :: Init (short iMode) 
{
	if (isLoaded() && m_pTE != NULL) 
		return m_pTE -> InitExtension (iMode);

return false;
}

LRESULT CDirectExtension :: Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (Entry()) return (*Entry())(hWnd, uiMsg, wParam, lParam);

return false;
}

LRESULT COleExtension :: Notify (HWND, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_pTE == NULL) return false;

	if (uiMsg == __DexNotify)	// interne Message
		return m_pTE -> Notification (wParam, lParam);

return m_pTE -> WindowsNotification (uiMsg, wParam, lParam);
}

HRESULT COleExtension :: GetImportIF (LPIMPORTGEODATA *ppIImport) 
{
	if (m_pTE == NULL) ResultFromScode (E_FAIL);

return m_pTE -> QueryInterface (IID_IImportGeoData, (LPVOID *)ppIImport);
}

// überprüfen, ob diese MenuMeldung für uns ist -------------------------------
bool Extension :: isMyID (UINT wItem) 
{
	return (isLoaded() && wItem > MenuOffset() && 
		wItem <= MenuOffset() + DEX_MENUOFFSETDELTA);
}

// überprüfen, ob unser PopupMenu gerufen wird --------------------------------
short Extension :: isMyMenu (MenuInitEvt e) 
{
	if (!isLoaded()) return 0;

NakedEvt &ne = (NakedEvt &)(Event &)e;

// wenn es kein MenuInit für ein PopupMenu ist
	if (ne.wmsg() != WM_INITMENUPOPUP) return 0;

// wenn es mein PopupMenu ist
	if (((HMENU)ne.wparam() == ORMenuHandle() || 
	     (HMENU)ne.wparam() == MenuHandle()))
		return 1;

// wenn es ein Popupmenu ist, in welchem ich meine MenuPunkte habe
	if (hasMenuItems (LOWORD (ne.lparam())))
		return 2;

return 0;
}


// Feststellen, ob in diesem PopupMenu MenuItems dieser Extension hängen
bool Extension :: hasMenuItems (short /*iPopupCnt*/)
{
	return true;	// erstmal immer wahr liefern
}

// Initialisieren der MenuItems in der Nutzer-DLL -----------------------------
bool CDirectExtension :: MenuInit (MenuInitEvt e, HWND hWndOR) 
{
	if (m_pExtEntry != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return (*m_pExtEntry)(hWnd(), DEX_MENUINIT, ne.wparam(), 
				MAKELONG(LOWORD(ne.lparam()), hWndOR)) != 0;
	}

return false;
}

bool COleExtension :: MenuInit (MenuInitEvt e, HWND hWnd) 
{
	if (m_pTE) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return m_pTE -> MenuInit ((HMENU)ne.wparam(), ne.lparam(), hWnd);
	}

return false;
}

// Auswählender MenuCommands in de Nutzer-DLL ---------------------------------
bool CDirectExtension :: MenuSelect (MenuSelectEvt e, HWND) 
{
	if (m_pExtEntry != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return (*m_pExtEntry)(hWnd(), ne.wmsg(), 
			LOWORD(ne.wparam())-MenuOffset(), ne.lparam()) != 0;
	}

return false;
}

bool COleExtension :: MenuSelect (MenuSelectEvt e, HWND hWnd) 
{
	if (m_pTE) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;
#if defined(WIN32)
	HMENU hMenu = (HMENU)ne.lparam();
#else
	HMENU hMenu = (HMENU)HIWORD(ne.lparam());
#endif
		return m_pTE -> MenuSelect (LOWORD(ne.wparam())-MenuOffset(), 
					    hMenu, hWnd);
	}

return false;
}

// Auslösen der MenuCommands in de Nutzer-DLL ---------------------------------
bool CDirectExtension :: MenuCommand (MenuCommandEvt e, HWND hORWnd) 
{
	if (m_pExtEntry != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return (*m_pExtEntry)(hWnd(), ne.wmsg(), 
			LOWORD(ne.wparam())-MenuOffset(), (LPARAM)(void *)hORWnd) != 0;
	}

return false;
}

bool COleExtension :: MenuCommand (MenuCommandEvt e, HWND hORWnd) 
{
	if (m_pTE != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return m_pTE -> MenuCommand (LOWORD(ne.wparam())-MenuOffset(), hORWnd);
	}

return false;
}


// Abfragen einer ErweiterungsEigenschaft ------------------------------------
int CDirectExtension :: GetCapability (WPARAM iCapType)
{
	if (m_pExtEntry != NULL) 
		return (int)(*m_pExtEntry)(hWnd(), DEX_CAPABILITIES, iCapType, 0L);

return false;
}	

int COleExtension :: GetCapability (WPARAM iCapType)
{
	if (m_pTE) return (int)m_pTE -> GetCapabilities (iCapType);

return 0;
}	

// Enumeration der EnumPropFunctionen einer Erweiterung ----------------------
bool CDirectExtension :: EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD)
{
	if (!GetCapability (DEXCAP_OBJPROPFUNCS)) return true;
	if (m_pExtEntry != NULL) 
		return (bool)(*m_pExtEntry)(hWnd(), DEX_ENUMEXTENSIONPROP, 0, (LPARAM)pEOPD);

return false;
}

bool COleExtension :: EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD)
{
	if (!m_fHasOPs || NULL == m_pTE) return true;

	if (NULL == m_pOPs) {
	HRESULT hr = m_pTE -> QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs);

		if (FAILED(hr)) 
		{
			m_fHasOPs = false;
			return true;
		}
	}

LPENUMOBJPROPS pIEnumOPs = NULL;
LPOBJECTPROPERTY pIOP = NULL;

	if (FAILED(m_pOPs -> EnumObjectProps (&pIEnumOPs))) {
		m_fHasOPs = false;
		return true;
	}

bool fR = true;

	for (pIEnumOPs -> Reset(); 
	     S_OK == pIEnumOPs -> Next(1, (LPUNKNOWN *)&pIOP, NULL); )
	{
	char cbBuffer[_MAX_PATH];

		pIOP -> Name(cbBuffer, _MAX_PATH);

	// neue Erweiterungen haben hier keinen FuncID (alles geht über den Namen -
	// nomen est omen)
		fR = (*pEOPD -> pFunc)(cbBuffer, 0, true, pEOPD -> pPtr);
		if (pIOP) pIOP -> Release();
		if (!fR) break;
	}
	pIEnumOPs -> Release();

return fR;
}


char *CDirectExtension :: InvokePropFunc (INVOKEOBJPROPDATA *pIOPD)
{
	if (m_pExtEntry != NULL)
		return (char *)(m_pExtEntry)(hWnd(), DEX_INVOKEOBJPROPFUNC, 0, (LPARAM)pIOPD);

return NULL;
}

char *COleExtension :: InvokePropFunc (INVOKEOBJPROPDATA *pIOPD)
{
	if (!m_fHasOPs) return NULL;	// hat keine OPF's

	if (m_pOPs == NULL) {	
	HRESULT hr = m_pTE -> QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs);

		if (FAILED(hr)) 
		{
			m_fHasOPs = false;
			return NULL;	// hat keine OPF's
		}
	}

LPOBJECTPROPERTY pIObjProp = NULL;
LPENUMOBJPROPS pIEnumProps = NULL;
HRESULT hr = m_pOPs -> EnumObjectProps (&pIEnumProps);

	if (FAILED(hr)) return NULL;

	if (0 == pIOPD -> iFuncID) {
		if (pIOPD -> dwSize != sizeof(INVOKEOBJPROPDATAEX)) 
			hr = ResultFromScode (E_FAIL);
		else
			hr = pIEnumProps -> FindByName (((INVOKEOBJPROPDATAEX *)pIOPD) -> pFName, &pIObjProp);
	} else
		hr = ResultFromScode (E_FAIL);

	pIEnumProps -> Release();
	if (FAILED(hr)) return NULL;

	if (0 < pIOPD -> lONr) {
		hr = pIObjProp -> Eval (pIOPD -> lONr, pIOPD -> pBuff, 
					pIOPD -> iBuffLen, NULL);
	} else switch (OBJPROPTYPE(pIOPD -> lONr)) {
	case OBJPROP_RESET:
		hr = pIObjProp -> Reset();
		break;

	case OBJPROP_COUNT:
		{
		ULONG ulCnt = pIObjProp -> Count();

			hr = NOERROR;
			ultoa (pIObjProp -> Count(), pIOPD -> pBuff, 10);
		}
		break;

	case OBJPROP_CUMULATION:
		hr = pIObjProp -> Cumulation (pIOPD -> pBuff, 
					      pIOPD -> iBuffLen, NULL);
		break;

	case OBJPROP_GETHELPTEXT:	// hier verboten
	case OBJPROP_EVAL:		// bereits behandelt
	default:
		TX_ASSERT(false);
		hr = ResultFromScode (E_FAIL);
		break;
	}
	pIObjProp -> Release();

return SUCCEEDED(hr) ? pIOPD -> pBuff : NULL;
}


char *CDirectExtension :: GetHelpText (GETHELPTEXTDATA *pGHTD)
{
	if (m_pExtEntry != NULL)
		return (char *)(m_pExtEntry)(hWnd(), DEX_OBJPROPGETHELPTEXT, 0, (LPARAM)pGHTD);

return NULL;
}

char *COleExtension :: GetHelpText (GETHELPTEXTDATA *pGHTD)
{
	if (!m_fHasOPs) return NULL;	// hat keine OPF's

	if (m_pOPs == NULL) {
	HRESULT hr = m_pTE -> QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs);

		if (FAILED(hr)) 
		{
			m_fHasOPs = false;
			return NULL;	// hat keine OPF's
		}
	}

LPOBJECTPROPERTY pIObjProp = NULL;
LPENUMOBJPROPS pIEnumProps = NULL;
HRESULT hr = m_pOPs -> EnumObjectProps (&pIEnumProps);

	if (FAILED(hr)) return NULL;

	if (0 == pGHTD -> iFuncID) {
		if (pGHTD -> dwSize != sizeof(GETHELPTEXTDATAEX)) 
			hr = ResultFromScode (E_FAIL);
		else
			hr = pIEnumProps -> FindByName (((GETHELPTEXTDATAEX *)pGHTD) -> pFName, &pIObjProp);
	} else
		hr = ResultFromScode (E_FAIL);

	pIEnumProps -> Release();
	if (FAILED(hr)) return NULL;

	if (pGHTD -> dwSize == sizeof(GETHELPTEXTDATA)) {
		hr = pIObjProp -> HelpInfo (pGHTD -> pBuff, pGHTD -> iBuffLen, 
					    NULL, NULL, NULL);
	} else if (pGHTD -> dwSize == sizeof(GETHELPTEXTDATAEX)) {
	GETHELPTEXTDATAEX *pGHTDEx = (GETHELPTEXTDATAEX *)pGHTD;

		hr = pIObjProp -> HelpInfo (pGHTDEx -> pBuff, pGHTDEx -> iBuffLen, 
					    NULL, pGHTDEx -> pHelpFile, &pGHTDEx -> ulHelpCtx);
	}
	pIObjProp -> Release();

return SUCCEEDED(hr) ? pGHTD -> pBuff : NULL;
}

HDEX CDirectExtension :: hLib (void) { return m_pDLL ? (HDEX)m_pDLL -> hLib() : 0; }
HDEX COleExtension :: hLib (void) { return m_hDex; }


// Einlesen der TRIAS-Erweiterungen ------------------------------------------
ErrCode ExtDirisWindow :: LoadAllExtensions (const char *pIni, bool isGlobal) 
{
ErrInstall EI (EC_EXTINITFAILURE);		// keine Fehler melden

	LoadAllExtensionsRegistry();		// erst aus Registry

return LoadAllExtensionsINI (pIni, isGlobal);		// dann aus INI
}


// Aus der SystemRegistry ----------------------------------------------------
bool ExtDirisWindow :: LoadAllExtensionsRegistry (void)
{
#if defined(WIN32)
	if (IsWin32s()) return true;

HKEY hKey = NULL;
DWORD i = 0;
char cbTriasKey[_MAX_PATH];
DWORD retCode = RegOpenKey (HKEY_CURRENT_USER, g_cbRegExtensions, &hKey);

	if (retCode != ERROR_SUCCESS) return false;
	while (RegEnumKey (hKey, i++, cbTriasKey, _MAX_PATH) == ERROR_SUCCESS) {
	string strTriasKey = cbTriasKey;

		LoadExtensionRegistry (strTriasKey);
	}

	RegCloseKey (hKey);   // Close the key handle.

#endif // WIN32
return true;
}

#if defined(WIN32)

bool ExtDirisWindow :: LoadExtensionRegistry (string &strProgID)
{
// auswerten der registry
string strExtKey (g_cbRegExtensions);
string strName = strProgID;

	{
	CCurrentUser regExt (strExtKey.c_str());

		if (regExt.isValid()) {
		TCHAR cbName [_MAX_PATH];
		LONG lLen = _MAX_PATH;

			if (regExt.GetSZ (strProgID.c_str(), cbName, lLen))
				strName = cbName;
		}
	}
	strExtKey += string(g_cbDel) + strProgID + g_cbDel + g_cbConfig;

CCurrentUser regCfg (strExtKey.c_str());
int fToLoad = LENoLoad;
EXTENSIONFLAG rgFlags = EF_Global;

	if (regCfg.isValid()) {
	DWORD dwData = 0L;

		if (regCfg.GetDWORD (TEXT("PreLoad"), dwData))
			fToLoad = dwData ? LEFullLoad : LENoLoad;
		if (regCfg.GetDWORD (TEXT("UnLoadable"), dwData))
			if (dwData) rgFlags = EXTENSIONFLAG(rgFlags | EF_UnLoadable);
		if (regCfg.GetDWORD (TEXT("Visible"), dwData))
			if (dwData) rgFlags = EXTENSIONFLAG(rgFlags | EF_Visible);
		if (regCfg.GetDWORD (TEXT("CanImport"), dwData))
			if (dwData) rgFlags = EXTENSIONFLAG(rgFlags | EF_CanImport);
	}

// eigentliches Laden
	LoadExtension (strName.c_str(), strProgID.c_str(), fToLoad, rgFlags);

return true;
}

bool SavePreloadStatus (const string &strProgID, bool fPreload)
{
string strKey = TEXT("Software\\uve\\TRiAS\\Extensions") TEXT("\\");
HKEY hKey = NULL;
DWORD dwData = fPreload ? true : false;
LONG fReturn = ERROR_SUCCESS;

	strKey += strProgID;
	strKey += TEXT("\\Config");
	if (::RegOpenKey (HKEY_CURRENT_USER, strKey.c_str(), &hKey) == ERROR_SUCCESS) {
		fReturn = ::RegSetValueEx (hKey, TEXT("PreLoad"), 0, REG_DWORD, 
			     (CONST BYTE *)&dwData, sizeof(dwData));
		::RegCloseKey (hKey);
	}

return fReturn == ERROR_SUCCESS;
}

#endif

// Aus der gegebenen INI -----------------------------------------------------
ErrCode ExtDirisWindow :: LoadAllExtensionsINI (const char *pIni, bool isGlobal) 
{
ResString Params (IDS_IRISPARS, 15);
ResString Extension (IDS_EXTENSION, 15);

// evtl. Erweiterungen laden
int ExtNums = GetPrivateProfileInt (Params, 
				    ResString (IDS_EXTNUMS, 15), 
				    0, pIni);

	if (ExtNums > 0) {
	// wenn Extensionen gegeben sind
	char *ExtNamesStr = new char [ExtNums*80+1];
	char **ExtNames = new char *[ExtNums];

		if (ExtNamesStr == NULL || ExtNames == NULL) {
			DELETE (ExtNamesStr);
			return (ErrCode)db_error (EC_NOMEMORY, RC_LoadAllExtensions);
		}
		GetPrivateProfileString (Extension, NULL, "", ExtNamesStr,
						    ExtNums*80+1, pIni);
		ExtNames[0] = ExtNamesStr;

	int len = 0;
	int i;
		for (i = 1; i < ExtNums; i++)
			ExtNames[i] = &ExtNamesStr[len += strlen(ExtNames[i-1])+1];

	// Laden der beim Start zu ladenden Extensionen
		for (i = 0; i < ExtNums; i++) {
		char currExt[80];

		// Beschreibung der Extension lesen
			GetPrivateProfileString (Extension, ExtNames[i], "",
						 currExt, 80, pIni);

		// Wenn Extension geladen werden soll, dann selbiges auch tun
		char *pDLLName = strtok (currExt, ",; ");
		bool toLoad = atoi (strtok (NULL, ",; "));
		EXTENSIONFLAG rgFlags = (EXTENSIONFLAG)0;
		
			if (!(toLoad & 0x02)) rgFlags = EXTENSIONFLAG(rgFlags | EF_UnLoadable);
			if (!(toLoad & 0x04)) rgFlags = EXTENSIONFLAG(rgFlags | EF_Visible);
			if (toLoad & 0x08) rgFlags = EXTENSIONFLAG(rgFlags | EF_CanImport);

			if (isGlobal) rgFlags = EXTENSIONFLAG(rgFlags | EF_Global);
			else {
				toLoad = 1;
				rgFlags = EXTENSIONFLAG(rgFlags & ~EF_Global);
			}

			LoadExtension (ExtNames[i], pDLLName, 
				       (toLoad & 0x1) ? LEFullLoad : LENoLoad, 
				       rgFlags);
		}
	// Speicher wieder freigeben
		DELETE (ExtNames);
		DELETE (ExtNamesStr);
	}

return EC_OKAY;
}

bool ExtDirisWindow :: doLoadExtension (void)
{
#if !defined(WIN32)
ExtLoadDLLDlg *pELDlg = ExtLoadDLLDlg :: CreateInstance (this, *m_pEL);

	if (pELDlg == NULL) return false;
	
	pELDlg -> Show();
	if (pELDlg -> Result()) {	// ok DLL's laden
		if (pELDlg -> GetFirstExtName()) {
			do {
				LoadExtension (pELDlg -> GetExtName(), 
					       pELDlg -> GetDLLName(), 
					       LEFullLoad, pELDlg -> GetFlags());
			} while (pELDlg -> GetNextExtName());
		}
		delete pELDlg;
		return true;
	}
	delete pELDlg;
#else
CManageExtDlg *pDlg = CManageExtDlg :: CreateInstance (this, *m_pEL);

	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {
	CEierUhr Wait (this);		// kann etwas dauern

	// alles, was zu entladen ist, entladen
		if (pDlg -> GetFirstExtName()) {
			do {
				if (pDlg -> toUnload()) {
					ReUnLoadExtension (pDlg -> GetExtName(), 
							   pDlg -> GetDLLName());
				}
			} while (pDlg -> GetNextExtName());
		}
	// alles, was zu laden ist, laden
		if (pDlg -> GetFirstExtName()) {
			do {
				if (pDlg -> toLoad()) {
					LoadExtension (pDlg -> GetExtName(), 
						       pDlg -> GetDLLName(), 
						       LEFullLoad, pDlg -> GetFlags());
				}
			} while (pDlg -> GetNextExtName());
		}
		delete pDlg;
		return true;
	}
	delete pDlg;
#endif

return false;
}

bool ExtDirisWindow :: doUnLoadExtension (void) 
{
#if !defined(WIN32)
ExtUnLoadDLLDlg *pEUDlg = ExtUnLoadDLLDlg :: CreateInstance (this, *m_pEL);

	if (pEUDlg == NULL) return false;
		
	pEUDlg -> Show();
	if (pEUDlg -> Result()) {	// ok DLL's freigeben
		if (pEUDlg -> GetFirstExtName()) {
			do {
				ReUnLoadExtension (pEUDlg -> GetExtName(), 
						   pEUDlg -> GetDLLName());
			} while (pEUDlg -> GetNextExtName());
		}
		delete pEUDlg;
		return true;
	}
	delete pEUDlg;
#endif // WIN32
return false;
}

bool ExtDirisWindow :: ReUnLoadExtension (
		const char *pExtName, const char *pDLLName, short iMode)
{
// das Ganze nur machen, wenn diese Erweiterung wirklich geladen ist
HDEX hDex = 0;

	if (!m_pEL -> isLoaded (pDLLName, hDex) || 
	    (iMode != LEFullLoad && m_pEL -> Release (pDLLName) > 0)) 
	{
		return false;
	}

EXTENSIONFLAG rgFlags = m_pEL -> GetFlags (pDLLName);

// Erweiterung rausnehmen und gleich wieder reinbauen
	if (UnLoadExtension (pExtName, true)) 
		LoadExtension (pExtName, pDLLName, 0, rgFlags);

return true;
}


bool ExtDirisWindow :: UnLoadLocalExtensions (void)
{
	if (m_pEL == NULL) return false;
	
CRing r (*m_pEL);

	for (r.First(); r.Valid(); r.Next()) {
	bool toDelete = false;
	string strExtName;

		{
		ExtensionLock l(r);

			if (l && !l -> isGlobal()) {
				toDelete = true;
				strExtName = l -> ExtName();
			}
		}
		if (toDelete) 
			UnLoadExtension (strExtName.c_str(), true);
	}

return true;
}


// Modifikation eines Menu's (addieren des Menuoffsets) -----------------------
void AddMenuOffset (HMENU hMenu, short iOffset)
{
	if (hMenu == 0) return;		// nur für gültige Menu's

WORD nCount = (WORD)GetMenuItemCount (hMenu);
char MenuEntry[_MAX_PATH+1];

	for (WORD wItem = 0; wItem < nCount; wItem++) {
	UINT MenuState = GetMenuState (hMenu, wItem, MF_BYPOSITION);
	UINT MenuID = GetMenuItemID (hMenu, wItem);

		if (MenuID == -1) {	// PopUpMenu
			AddMenuOffset (GetSubMenu (hMenu, wItem), iOffset);	
			continue;
		}
		if (MenuState & (MF_MENUBARBREAK | MF_MENUBREAK | MF_SEPARATOR))
			continue;
		GetMenuString (hMenu, wItem, MenuEntry, _MAX_PATH, MF_BYPOSITION);
		ModifyMenu (hMenu, wItem, MF_BYPOSITION | MenuState, MenuID+iOffset, MenuEntry);
	}
}


// ----------------------------------------------------------------------------
// DefaultProcedure zur Verwaltung nicht bearbeiteter Messages an die 
// Erweiterungen
extern "C" {

DWORD EXPORTTRIAS WINAPI DefTriasExtensionProc (HDEX, UINT, WPARAM, LPARAM)
{
	return false;
}

inline POINT lpFcn (OIPOSPROC pFcn, Window *pW, void *pData)
{
	return ((OIPOSCALLBACK)pFcn) (pW, pData);
}

}	// extern "C" 

// Generieren eines ObjektrechercheFensters -----------------------------------
HWND ExtDirisWindow :: CreateObjektInfo (DEXXCREATEOBJEKTINFO *pcrOI)
{
	if (pcrOI == NULL) return NULL;

short iFlags = 0;
CMPONRPROC pProc = NULL;
DWORD dwData = 0L;

	if (pcrOI -> dwSize == sizeof (DEXXCREATEOBJEKTINFOEX)) {
	// wenn Fenster bereits existiert, dann zu diesem hinzufügen
		if (((DEXXCREATEOBJEKTINFOEX *)pcrOI) -> m_hWnd) {
		// zu existierendem Fenster hinzufügen
		HWND hWnd = ((DEXXCREATEOBJEKTINFOEX *)pcrOI) -> m_hWnd;
		ObjektInfo *pOIDlg = (ObjektInfo *)ObjInfoListe.GetORWindow (hWnd);
		
			if (pOIDlg && pOIDlg -> FInit (*(ObjFeld *)pcrOI -> lcObjs)) {
				pOIDlg -> UpdateCaption();
				return hWnd;	
			}
		}

	// zusätzliche Variablen werden für neues Fenster gebraucht
		iFlags = ((DEXXCREATEOBJEKTINFOEX *)pcrOI) -> m_iFlags;
		pProc = ((DEXXCREATEOBJEKTINFOEX *)pcrOI) -> m_pCmpProc;
		dwData = ((DEXXCREATEOBJEKTINFOEX *)pcrOI) -> m_dwData;
	}
	if (iFlags == 0) iFlags = g_iHideFlags;	// globale Voreinstellung
				
ObjektInfo *pOIDlg = ObjektInfo :: CreateInstance (
				this, DBO(), *m_pEL, *(ObjFeld *)pcrOI -> lcObjs, 
				iFlags, pProc, dwData);
	{
	ObjektInfoCreator Cr(ObjInfoListe);

		if (pOIDlg == NULL) {
			db_error (EC_NOMEMORY, RC_CreateObjektInfo);
			return NULL;
		}
		Cr.InsertPtr (pOIDlg);
	}	// wegspeichern

// Caption setzen, Objektanzahl hinzufügen
char *pNewCaption = new char [strlen (pcrOI -> lpCaption) + 20];

	if (pNewCaption == NULL)
		pOIDlg -> SetCaption (pcrOI -> lpCaption);
	else {
		wsprintf (pNewCaption, "%s (%d/%ld)", pcrOI -> lpCaption, 
			  pOIDlg -> m_iActCount, pOIDlg -> GetCount());
		pOIDlg -> SetCaption (pNewCaption);
		delete pNewCaption;
	}

// Farbe setzen
	pOIDlg -> SetColor (*pcrOI -> pcMColor);

// Dialogfenster positionieren
	if (pcrOI -> fcnPos == NULL) {
		pOIDlg -> m_ptWantedPos = 
			pOIDlg -> ChangePosition (*pcrOI -> ppntPos);
	} else {
	POINT pt = lpFcn (pcrOI -> fcnPos, pOIDlg, pcrOI -> pData);

		pOIDlg -> m_ptWantedPos = pOIDlg -> ChangePosition (*(Point *)&pt);
	}

// Dialogfenster anzeigen
	pOIDlg -> Show ();		// DlgFenster anzeigen
	DEXN_RechObjWindowCreated (pOIDlg -> hWnd());	// die Welt informieren

return pOIDlg -> Handle (API_WINDOW_HWND);
}

// Das gleiche aber für C-Schnittstelle ---------------------------------------
HWND ExtDirisWindow :: CreateObjektInfo (CREATEOBJEKTINFO *pcrOI)
{
	if (pcrOI == NULL) return NULL;

// ObjektFeld aufbauen, welches vom Fenster erwartet wird
ObjFeld OF;

#if !defined(WIN32)
	if ((unsigned int)pcrOI -> iNumObjs >= USHRT_MAX/sizeof(long)) {
	ObjNummerCreator ONC (OF);

		for (unsigned short i = 0; i < (unsigned short)pcrOI -> iNumObjs; i++) 
			OF.NewObj (ONC, ((long __huge *)pcrOI -> plObjs)[i]);
	} else
#endif // WIN32
	{
	ObjNummerCreator ONC (OF);

		for (unsigned short i = 0; i < (unsigned short)pcrOI -> iNumObjs; i++) 
			OF.NewObj (ONC, pcrOI -> plObjs[i]);
	}

short iFlags = 0;
CMPONRPROC pProc = NULL;
DWORD dwData = 0L;

	if (pcrOI -> dwSize == sizeof (CREATEOBJEKTINFOEX)) {
	// wenn Fenster bereits existiert, dann zu diesem hinzufügen
		if (((CREATEOBJEKTINFOEX *)pcrOI) -> m_hWnd) {
		// zu existierendem Fenster hinzufügen
		HWND hWnd = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_hWnd;
		ObjektInfo *pOIDlg = (ObjektInfo *)ObjInfoListe.GetORWindow (hWnd);
		
			if (pOIDlg && pOIDlg -> FInit (OF)) 
				return hWnd;	
		}

	// zusätzliche Variablen werden für neues Fenster gebraucht
		iFlags = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_iFlags;
		pProc = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_pCmpProc;
		dwData = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_dwData;
	}
	if (iFlags == 0) iFlags = g_iHideFlags;	// globale Voreinstellung
		
ObjektInfo *pOIDlg = ObjektInfo :: CreateInstance (
			this, DBO(), *m_pEL, OF, iFlags, pProc, dwData);
	{
	ObjektInfoCreator Cr(ObjInfoListe);

		if (pOIDlg == NULL) {
			db_error (EC_NOMEMORY, RC_CreateObjektInfo);
			return NULL;
		}
		Cr.InsertPtr (pOIDlg);
	}	// wegspeichern

// Caption setzen, Objektanzahl hinzufügen
char *pNewCaption = new char [strlen (pcrOI -> lpCaption) + 20];

	if (pNewCaption == NULL)
		pOIDlg -> SetCaption (pcrOI -> lpCaption);
	else {
		wsprintf (pNewCaption, "%s (%d/%ld)", pcrOI -> lpCaption, 
			  pOIDlg -> m_iActCount, pOIDlg -> GetCount());
		pOIDlg -> SetCaption (pNewCaption);
		delete pNewCaption;
	}

// Farbe setzen
	pOIDlg -> SetColor (*(Color *)&pcrOI -> cMColor);

// Dialogfenster positionieren
	pOIDlg -> m_ptWantedPos = pOIDlg -> ChangePosition (*(Point *)&pcrOI -> pntPos);

// Dialogfenster anzeigen
	pOIDlg -> Show ();		// DlgFenster anzeigen
	DEXN_RechObjWindowCreated (pOIDlg -> hWnd());	// die Welt informieren
	
return pOIDlg -> Handle (API_WINDOW_HWND);
}

// MenuPunkt installieren -----------------------------------------------------
HMENU ExtDirisWindow :: InstallMenuItem (INSTALLMENUITEM *pIMI)
{
	if (m_pEL == NULL) return 0;	// Fehler

CRing r(*m_pEL);
bool iFound = false;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l || l -> hLib() != pIMI -> hDex)
			continue;
	// Extension gefunden
		pIMI -> iMenuID += l -> MenuOffset();	// Offset drauftun
		iFound = true;
		break;
	}

	if (!iFound) return 0;		// Extension nicht wiedergefunden

	if (pIMI -> iFlag) {
	// in ORFenster einhängen
		if (m_pEL -> m_pMIL == NULL) {
			m_pEL -> m_pMIL = new MenuItemList();
			if (m_pEL -> m_pMIL == NULL)
				return 0;
		}

	// MenuItem erzeugen ...
	MenuItemCreator MICr (*(m_pEL -> m_pMIL));

	MenuItem *pMI =	Create (MICr, MenuItem)(
					pIMI -> pMenuText,
					pIMI -> hDex,
					pIMI -> iMenuID,
					pIMI -> iMenuNum
			       );
	// ... und in alle offenen Fenster einbauen
	return ObjInfoListe.InstallMenuItem (pIMI -> iMenuID, 
					     pIMI -> iMenuNum,
					     pIMI -> pMenuText);
	} else {
	// sofort ins Hauptfenster einhängen
	HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);
	HMENU hSubMenu = GetSubMenu (hMenu, pIMI -> iMenuNum);

		if (hSubMenu == 0) return 0;	// Error

	// wenn MenuPosition gegeben ist, dann dort einhängen
		if (pIMI -> dwSize == sizeof (INSTALLMENUITEM) && 
		    pIMI -> iMenuPos != -1)
		{	// neue Struktur und Wert gegeben
		// normalen MenuPunkt einfügen
			InsertMenu (hSubMenu, 
				    pIMI -> iMenuPos,		// insert
				    MF_BYPOSITION|MF_STRING, 
				    pIMI -> iMenuID, 
				    pIMI -> pMenuText);
			DrawMenuBar (Handle (API_CLIENT_HWND));
			return hSubMenu;		// hier fertig
		}
 
	// überprüfen, ob dieser Punkt der erste zusätzliche für dieses SubMenu ist
		{
		Menu TestMenu (IRISMENU);	// Menu für VergleichsZwecke
		HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
		HMENU hTestSubMenu = GetSubMenu (hTestMenu, pIMI -> iMenuNum);

			if (GetMenuItemCount (hTestSubMenu) == GetMenuItemCount (hSubMenu))
			// wenn es der erste ist, dann Separator einfügen
				InsertMenu (hSubMenu, (uint)-1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
	
	        }
	// normalen MenuPunkt einfügen
		InsertMenu (hSubMenu, (uint)-1,	// append
			    MF_BYPOSITION|MF_STRING, 
			    pIMI -> iMenuID, 
			    pIMI -> pMenuText);
		DrawMenuBar (Handle (API_CLIENT_HWND));
		return hSubMenu;
	}
}

// MenuPunkt wieder entfernen -------------------------------------------------
bool ExtDirisWindow :: RemoveMenuItem (REMOVEMENUITEM *pRMI)
{
	if (m_pEL == NULL || m_pEL -> m_pMIL == NULL) 
		return false;	// Fehler oder noch keine Menuitems da

CRing r(*m_pEL);
bool iFound = false;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		TX_ASSERT(NULL != (Extension *)l);

		if (l -> hLib() == pRMI -> hDex) {
		// Extension gefunden
			pRMI -> iMenuID += l -> MenuOffset();	// Offset drauftun
			iFound = true;
			break;
		}
	}
	if (!iFound) return false;		// Extension nicht wiedergefunden
	
	if (pRMI -> iFlag) {
	// in ORFenstern entfernen
		ObjInfoListe.RemoveMenuItem (pRMI -> iMenuID, pRMI -> iMenuNum);

	// aus der Liste entfernen
		return m_pEL -> m_pMIL -> RemoveMenuItem (pRMI -> iMenuID);
	} else {
	// sofort im Hauptfenster rausnehmen
	HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);

		if (!DeleteMenu (hMenu, pRMI -> iMenuID, MF_BYCOMMAND)) {
			TX_ASSERT(false);
			return false;
		}

	// wenn dieser Punkt der letzte zusätzliche in diesem SubMenu war, dann
	// noch den Separator rausnehmen
		{
		Menu TestMenu (IRISMENU);	// Menu für VergleichsZwecke
		HMENU hSubMenu = GetSubMenu (hMenu, pRMI -> iMenuNum);
		HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
		HMENU hTestSubMenu = GetSubMenu (hTestMenu, pRMI -> iMenuNum);
		short iLast = GetMenuItemCount (hSubMenu);

			if (GetMenuItemCount (hTestSubMenu) == iLast -1)
			// wenn es der letzte war, dann Separator löschen
				DeleteMenu (hSubMenu, iLast -1, MF_BYPOSITION);
	        }
		DrawMenuBar (Handle (API_CLIENT_HWND));
	}

return true;
}

// Werkzeug einhängen/entfernen -----------------------------------------------
extern ToolWind *pToolBox;	// Werkzeugfenster
extern bool ToolBoxCFlag;

#if defined(WIN32)
#define TOOLMAINPOPUP	4
#define TOOLPOPUP	3
#else
#define TOOLMAINPOPUP	4
#define TOOLPOPUP	1
#endif // WIN32

short ExtDirisWindow :: InstallTool (INSTALLTOOL *pIT)
{
short iToolID = -1;	// für den FehlerFall
pBitmap pBmp = new Bitmap (pIT -> hBmp);

// in Werkzeugfenster einhängen
	if (!pToolBox)		// evtl. ToolFenster neu bilden
		pToolBox = new ToolWind (this);

	if (pToolBox) iToolID = pToolBox -> AddTool (pBmp);

	if (iToolID == -1) {
		DELETE (pBmp);
		return -1;	// Fehler		
	}

// zusätzlichen Punkt im Menu etablieren
HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);
HMENU hSubMenu = GetSubMenu (hMenu, TOOLMAINPOPUP);

	hSubMenu = GetSubMenu (hSubMenu, TOOLPOPUP);	// ToolMenu besorgen
	AppendMenu (hSubMenu, MF_STRING, IDM_ARROW+iToolID, pIT -> pDesc);
	DrawMenuBar (Handle (API_WINDOW_HWND));
	
return iToolID;
}


bool ExtDirisWindow :: RemoveTool (short iToolID)
{
// im Werkzeugfenster entfernen
bool fResult = false;

	if (pToolBox) {
		fResult = pToolBox -> RemoveTool (iToolID);
		TX_ASSERT(fResult);
	
	// im Menu rausnehmen
		if (fResult) {
		HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);

			DeleteMenu (hMenu, IDM_ARROW+iToolID, MF_BYCOMMAND);
			DrawMenuBar (Handle (API_WINDOW_HWND));
		}
	}

return fResult;
}


// Funktion, die das Fenster anzeigt bzw. ausblendet --------------------------
void ExtDirisWindow :: Show (ShowState s)
{
	if (s == HideWindow) {
		if (m_fIsShown) {
			Hide();
			m_fIsShown = false;
		}
		return;
	}
	if (!m_fIsShown) {
		m_fIsShown = true;
		Window :: Show (s);		// weiterreichen
	}
}


void ExtDirisWindow :: Expose (ExposeEvt e)
{
	if (FIsShown()) 	// nur wenn angezeigt, dann zeichnen
		IrisWind :: Expose (e);
}


// Dragging einer Datei auf das TriasFenster ist erfolgt ----------------------
bool IrisWind :: DragFunc (WPARAM wParam)
{
WORD cFiles = DragQueryFile ((HDROP)wParam, UINT_MAX, NULL, 0);
char *pPath = new char [_MAX_PATH];
ResString StbExt (IDS_REGSTBEXTENSION, 6);
ResString RisExt (IDS_REGRISEXTENSION, 6);
char pExt[_MAX_EXT];

	if (pPath == NULL) return false;
	for (WORD i = 0; i < cFiles; i++) {
		DragQueryFile ((HDROP)wParam, i, pPath, _MAX_PATH);
		strlwr (pPath);
		_splitpath (pPath, NULL, NULL, NULL, pExt);
		if (strcmp (pExt, StbExt) && strcmp (pExt, RisExt))
			continue;

	// Projekt öffnen
	TRIAS_OPEN TO;
	char *pUser = new char [_MAX_FNAME];

		_splitpath (pPath, NULL, NULL, pUser, NULL);
		TO.dwSize = sizeof (TRIAS_OPEN);
		TO.lpProject = pPath;
		TO.lpUser = pUser;
		TO.lpPassWord = NULL;
		TO.iMode = OM_Normal;
		DEX_OpenProject (TO);	// Projekt eröffnen

		DELETE (pUser);
		break;			// nur das erste Projekt
	}
	DragFinish ((HDROP)wParam);
	DELETE (pPath);

return true;
}


// Initialisierung des Sprungverteilers für die externen Messages -------------

#include "extfcns.tab"		// Sprungverteiler-Template

bool ExtDirisWindow :: FInitDexProcs (void)
{
// allgemeine Initialisierungen
	m_cbDexProcs = NULL;		// Sprungverteiler
	m_i1stDexProc = 0;		// erste Funktion
	m_iDexProcsNum = 0;		// Anzahl der Funktionen in Tabelle

// größten und kleinsten MessageID suchen
unsigned short iFirst = USHRT_MAX;
unsigned short iLast = 0;
const DEXMESSAGE_ENTRY *pDME = DexMessageEntries;

	for (short i = 0; i < DEXMESSAGE_ENTRYNUM; i++, pDME++) {
	UINT uiMsg = pDME -> m_uiMsg;
	
		if (iFirst > uiMsg) iFirst = uiMsg;
		if (iLast < uiMsg) iLast = uiMsg;
	}
	if (iFirst == USHRT_MAX || iLast == 0)
		return false;
	
	m_iDexProcsNum = iLast-iFirst+1;
	m_i1stDexProc = iFirst;

	TX_ASSERT(m_iDexProcsNum >= 1);
					
// Tabelle anlegen und initialisieren
	m_cbDexProcs = new DEXMESSAGE_PROC [m_iDexProcsNum];
	if (m_cbDexProcs == NULL) return false;

	for (unsigned short j = 0; j < m_iDexProcsNum; j++) 
		 m_cbDexProcs[j] = ExtDirisWindow :: OnNotDefinedMessage;
	
// Funktionen eintragen
	pDME = DexMessageEntries;
	for (i = 0; i < DEXMESSAGE_ENTRYNUM; i++, pDME++) {
	// erste Zuweisung ?
		TX_ASSERT(ExtDirisWindow :: OnNotDefinedMessage == m_cbDexProcs[(pDME -> m_uiMsg) - iFirst]);
		m_cbDexProcs[(pDME -> m_uiMsg) - iFirst] = pDME -> m_pProc;
	}

return true;
}

extern "C" bool EXPORTTRIAS WINAPI FillONrEnum (long lONr, bool, void *pData);

static bool AddObjectsToEnum (CEnumObjectsByNumber *pEnum, long lIdent, short iOTyp)
{
ENUMLONGKEY ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYPROC)FillONrEnum;
	ELK.ePtr = pEnum;

return DEX_EnumIdentObjects (ELK);
}

bool ExtDirisWindow :: GenObjectProperties (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (this, 
				OBJPROPIDENTDLG, IDL_OBJPROPIDENTSLIST);

	if (pDlg == NULL) return false;

	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	long lIdent = -1L;
	short iOTyp = 0;
	CEnumObjectsByNumber *pEnum = CEnumObjectsByNumber :: CreateInstance();
		
		if (pEnum == NULL) return false;
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (!AddObjectsToEnum (pEnum, lIdent, iOTyp))
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}

	ObjectPropertyDlg OPDlg (this, m_pEL, pEnum);

		Wait.Hide();
		OPDlg.Show (Centre);
		pEnum -> Release();
	}

return true;
}
