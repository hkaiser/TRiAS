// Routinen fuer Klasse TriasExtension ----------------------------------------
// File: TEXTENSN.CXX

extern "C" {
	#include <windows.h>
	#include <stdlib.h>
	#include <string.h>

	#include <protos.h>

	#include <xtension.h>
	#include <xtensnx.h>
	#include <xtensnxx.h>

	#include <resstrg.h>
}

#include <commonvu.hxx>

#include <errcodes.hxx>
#include <textensn.hxx>

extern HINSTANCE hInstance;

extern "C" {
	UINT __DexReg;
	UINT __DexUnReg;
	UINT __DexCmd;
	UINT __DexxCmd;
	UINT __DexNotify;
	HWND __hWndM;
}

// Funktionsprototypen --------------------------------------------------------
TriasExtension *pTE = NULL;	// diese Erweiterung

extern "C" {	// TriasExtensionProc soll von auáen gerufen werden

// Routine, welche exportiert werden muá, da sie die eigentliche Schnittstelle
// zu TRIAS(R) darstellt. Diese Routine wird von TRIAS(R) für jede übergebene
// Message gerufen. Sie muß in jeder Erweiterung identisch heiáen und 
// identische Parametertypen erwarten.

DWORD PASCAL __export TriasExtensionProc (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{

	switch (wMsg) {
	case DEX_LOADEXTENSION:		
	//
	// DEX_LOADEXTENSION wird gerufen, nachdem DLL geladen wurde.
	// Die Erweiterung muá an dieser Stelle initialisiert werden. Auáerdem
	// muá ein Handle auf das Menu der Erweiterung, sowie ein im Hauptmenu
	// von TRIAS(R) für dieses Menu anzuzeigender Menutext zurück übergeben
	// werden.
	//
		{
		// Die Datenstruktur 'TRIAS_LOAD' dient der Übergabe aller
		// zur Einbindung in TRIAS(R) notwendigen Informationen zur 
		// und von der Erweiterung. (s. XTENSION.H)
		TRIASLOADEX *pTL = (TRIASLOADEX *)lParam;

			if (pTL == NULL) 
				return EC_ILLPARS;	// ParameterFehler

		// An dieser Stelle wird die vom Nutzer bereitgestellte Funktion
		// NewExtension gerufen, die nichts weiter tun darf und muß, als 
		// die Erweiterung (als Klasse) typrichtig zu erzeugen.
			if (pTE == NULL) {
				pTE = NewExtension ((TRIAS_LOAD *)pTL);	
					// muß vom Nutzer bereitgestellt sein
				if (pTE == NULL || !*pTE)
					return EC_NOMEMORY;

			// übergebene Parameter merken
				pTE -> _hDex = (HDEX)wParam;
				__hWndM = hWnd;
				pTE -> _DefProc = pTL -> m_fcDef;		// DefaultProcedure	
				pTE -> _MenuOffset = pTL -> m_wMenuDelta;

				if (pTL -> m_dwSize == sizeof(TRIASLOADEX))
					pTE -> m_iMode = pTL -> m_iMode;
			}

		// MenuHandle's und MenuTexte speichern und an TRIAS(R) zurück-
		// liefern
			if (pTL -> m_hMenu = pTE -> MenuHandle())
				strncpy (pTL -> m_szMenuName, pTE -> MenuEntry(), DEX_MENUNAMELEN);
			if (pTL -> m_hORMenu = pTE -> ORMenuHandle())
				strncpy (pTL -> m_szORMenuName, pTE -> ORMenuEntry(), DEX_MENUNAMELEN);
		}
		return EC_OKAY;		// EC_OKAY: kein Fehler

	case DEX_UNLOADEXTENSION:	
	//
	// DEX_UNLOADEXTENSION wird gerufen bevor DLL freigegeben wird.
	// an dieser Stelle kann der gesamte von der Erweiterung angeforderte
	// Speicher freigegeben werden, sowie sonstige Aufräumarbeiten durch-
	// geführt werden.
	//
		if (pTE) {
		Bool Result = pTE -> UnLoadExtension ();	// virtuelle Funktion rufen

		// Hier wird die von Nutzer bereitgestellte Funktion DeleteExtension
		// gerufen, die die ErweiterungsKlasse typrichtig freigibt.
			DeleteExtension (pTE);	// Extension wieder freigeben
			pTE = NULL;
			return Result;
		}
		return FALSE;		// ansonsten Fehler melden

	default:
		if (pTE) return pTE -> Dispatch (hWnd, wMsg, wParam, lParam);
	}

return FALSE;
}

}	// extern "C"

// Platzhalter für die virtuellen EventHandler der Erweiterung ----------------
Bool TriasExtension :: InitExtension (short) { return TRUE; }
Bool TriasExtension :: UnLoadExtension (void) { return TRUE; }
Bool TriasExtension :: MenuInit (HMENU, HWND) { return TRUE; }
Bool TriasExtension :: MenuSelect (WPARAM, HWND) { return TRUE; }
Bool TriasExtension :: MenuCommand (WPARAM, HWND) { return TRUE; }
LRESULT TriasExtension :: Notification (WPARAM, LPARAM) { return FALSE; }
LRESULT TriasExtension :: WindowsNotification (UINT, WPARAM, LPARAM) { return FALSE; }

// lokaler EventDispatcher ----------------------------------------------------
LRESULT TriasExtension :: Dispatch (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case DEX_INITEXTENSION:
	// 
	// DEX_INITEXTENSION ist die eigentliche Fertigmeldung von TRIAS(R) 
	// an eine Erweiterung, die einmalig ausgelöst wird, wenn die 
	// Erweiterung erfolgreich im System installiert ist. An dieser Stelle
	// sollte die gesamte Initialisierung der Erweiterung erfolgen. So
	// können beispielsweise Speicherressourcen angefordert werden oder
	// Notifikationsanforderungen an TRIAS(R) abgesetzt werden. Alle an 
	// dieser Stelle angeforderten Ressourcen bzw. Notifikationen sollten
	// spätestens während der Bearbeitung der Meldung DEX_UNLOADEXTENSION
	// wieder freigegeben werden.
	//
		{
		Bool Res = InitExtension (wParam);	// virtuelle Funktion rufen

			m_iMode = wParam;		// Mode merken
			return Res;
		}

	case DEX_MENUINIT:
	//
	// DEX_MENUINIT wird gerufen, wenn das DLL-eigene Menu aufgeklappt 
	// wird. An dieser Stelle können Befehle zur Menuinitialisierung
	// des DLL-eigenen Menus eingebaut werden (ENABLE/DISABLE/GRAY etc.).
	//
		return MenuInit ((HMENU)wParam, (HWND)HIWORD(lParam));

	case WM_MENUSELECT:
	// 
	// WM_MENUSELCT wird geliefert, wenn ein MenuPunkt des Erweiterungs-
	// menu's ausgewählt wurde (nicht angeklickt). Das kann z.B. für eine
	// kontextsensitive Hilfe verwendet werden.
	// In wParam befindet sich der ID des ausgewählten MenuPunktes.
	//
		return MenuSelect (wParam, (HWND)lParam);	// virtuelle Funktion rufen

	case WM_COMMAND:
	//
	// WM_COMMAND wird geliefert, wenn ein MenuPunkt des DLL-eigenen
	// Menus selektiert wurde. Hier findet folglich die Verarbeitung 
	// der Menukommandos statt. In wParam wird dabei der ID des ange-
	// klickten Menupunktes übergeben.
	//
		return MenuCommand (wParam, (HWND)lParam);

	case DEX_CAPABILITIES:
		return FALSE;

	default:
	// entsprechende virtuelle Funktionen rufen
		if (wMsg == __DexNotify) 
			return Notification (wParam, lParam);
		else if ((HDEX)hWnd == hDex())
			return WindowsNotification (wMsg, wParam, lParam);

	//
	// Alle nicht durch diese Erweiterung bearbeiteten Messages von
	// TRIAS(R) müssen an die Standardverarbeitungsroutine in TRIAS(R)
	// zurückgeliefert werden. Das ist notwendig, um in jedem Fall eine 
	// definierte Reaktion auf eine Message zu erhalten.
	//
//		return (*_DefProc)(hDex(), wMsg, wParam, lParam);
	}

return FALSE;
}

// ----------------------------------------------------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
TriasExtension :: TriasExtension (UINT iMenuID, UINT iORMenuID)
{
// Flag für alle Fälle rücksetzen
	_isValid = FALSE;
	_DefProc = NULL;

// als erstes ResourceFile bilden
char szBuffer[_MAX_PATH];

	GetModuleFileName (hInstance, szBuffer, sizeof(szBuffer));
	_pRF = new ResourceFile (szBuffer);
	if (_pRF == NULL) return;

// Daten dieser Extension initialisieren
// evtl. HauptMenu aufbauen
	if (iMenuID) {
		_pLoadedMenu = new Menu (ResID (iMenuID, _pRF));
		if (_pLoadedMenu == NULL) return;	

	// PopUpMenu und MenuText holen
	HMENU hMenu = _pLoadedMenu -> Handle (API_MENU_HMENU);

		_hPopUpMenu = GetSubMenu (hMenu, 0);
		_pMenuEntry = new char [DEX_MENUNAMELEN+1];
		if (_pMenuEntry == NULL) return;
		GetMenuString (hMenu, 0, _pMenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
	} else {
		_hPopUpMenu = 0;
		_pLoadedMenu = NULL;
		_pMenuEntry = NULL;
	}

	if (iORMenuID) {
		_pLoadedORMenu = new Menu (ResID (iORMenuID, _pRF));
		if (_pLoadedORMenu == NULL) return;	

	// PopUpMenu und MenuText holen
	HMENU hMenu = _pLoadedORMenu -> Handle (API_MENU_HMENU);

		_hPopUpORMenu = GetSubMenu (hMenu, 0);
		_pORMenuEntry = new char [DEX_MENUNAMELEN+1];
		if (_pORMenuEntry == NULL) return;
		GetMenuString (hMenu, 0, _pORMenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
	} else {
		_hPopUpORMenu = 0;
		_pLoadedORMenu = NULL;
		_pORMenuEntry = NULL;
	}

// Registrieren der Messages
	__DexCmd = RegisterWindowMessage (ResString (ResID (IDS_DEXMESSAGE, _pRF), 30));
	__DexxCmd = RegisterWindowMessage (ResString (ResID (IDS_DEXXMESSAGE, _pRF), 30));
	__DexReg = RegisterWindowMessage (ResString (ResID (IDS_QNFYMESSAGE, _pRF), 30));
	__DexUnReg = RegisterWindowMessage (ResString (ResID (IDS_QNFYUNREGMESSAGE, _pRF), 30));
	__DexNotify = RegisterWindowMessage (ResString (ResID (IDS_NOTIFICATION, _pRF), 30));

	if (__DexCmd == 0 || __DexReg == 0 || 
	    __DexUnReg == 0 || __DexNotify == 0 || __DexxCmd == 0) 
	{
		return;
	}

// alles ok
	_isValid = TRUE;		// Objekt ist gltig
}

TriasExtension :: ~TriasExtension (void) 
{
	DELETE (_pLoadedMenu);
	DELETE (_pLoadedORMenu);
	DELETE (_pMenuEntry);
	DELETE (_pORMenuEntry);
	DELETE (_pRF);
}


// Notifikationsbehandlung ----------------------------------------------------
LRESULT TriasExtension :: RegisterNotification (UINT wMsg, Bool isLocal) 
{
	return SendMessage (__hWndM, __DexReg, (WPARAM)_hDex, MAKELONG (wMsg, isLocal)); 
}

LRESULT TriasExtension :: UnRegisterNotification (UINT wMsg, Bool isLocal)
{
	return SendMessage (__hWndM, __DexUnReg, (WPARAM)_hDex, MAKELONG (wMsg, isLocal));
}

pWindow TriasExtension :: MWind (void) 
{
static pWindow pMWind = NULL;

	if (pMWind == NULL)
		pMWind = (pWindow)SendMessage (__hWndM, __DexxCmd, (WPARAM)DEXX_MAINWINDOW, 0L);

	return pMWind;
}

pWindow TriasExtension :: ORWind (HWND hWnd)
{
	return (pWindow)SendMessage (__hWndM, __DexxCmd, (WPARAM)DEXX_ORWINDOW, (LPARAM)hWnd);
}

HWND TriasExtension :: GetActiveORWindow (void)
{
	return (HWND)SendMessage (__hWndM, __DexCmd, (WPARAM)DEX_QUERYACTIVEORWINDOW, 0L);
}

HelpDisplay *TriasExtension :: MainHD (void)
{
	return (HelpDisplay *)SendMessage(__hWndM, __DexxCmd, (WPARAM)DEXX_MAINHELPDISPLAY, 0L);
}

UINT TriasExtension :: InstallMenuItem (UINT iMenuID, UINT iMenuStr, 
					BOOL iORMenu, short iPopupNum,
					short iMenuPos)
{
INSTALLMENUITEM imi;
ResString RS (ResID (iMenuStr, &RF()), 50);

	imi.dwSize = sizeof (INSTALLMENUITEM);
	imi.pMenuText = (char *)RS.Addr();
	imi.hDex = hDex();
	imi.iMenuID = iMenuID;
	imi.iFlag = iORMenu;
	imi.iMenuNum = iPopupNum;
	imi.iMenuPos = iMenuPos;

	DEX_InstallMenuItem (imi);

return imi.iMenuID;		// neuen MenuID merken
}

void TriasExtension :: RemoveMenuItem (UINT iMenuID, BOOL iORMenu, short iPopupNum)
{
REMOVEMENUITEM rmi;

	rmi.dwSize = sizeof(REMOVEMENUITEM);
	rmi.hDex = hDex();
	rmi.iMenuID = iMenuID;
	rmi.iMenuNum = iPopupNum;
	rmi.iFlag = iORMenu;
	DEX_RemoveMenuItem (rmi);
}

// Neues Hauptmenü unterschieben ----------------------------------------------
HMENU TriasExtension :: EmptyMenu()
{
	if ( !_hPopUpMenu ) return _hPopUpMenu;
	short n = GetMenuItemCount( _hPopUpMenu );
	if ( !n ) return _hPopUpMenu;
	short i, id;

	for ( i = n-1; i >= 0; i-- )
	{
		id = GetMenuItemID( _hPopUpMenu, i );
		if ( id < 0 )
			DestroyMenu( GetSubMenu( _hPopUpMenu, i ));
		DeleteMenu( _hPopUpMenu, i, MF_BYPOSITION );
	}
	return _hPopUpMenu;
}


// Neues OR-Menü unterschieben ------------------------------------------------
HMENU TriasExtension :: EmptyORMenu()
{
	if ( !_hPopUpORMenu ) return _hPopUpORMenu;
	short n = GetMenuItemCount( _hPopUpORMenu );
	if ( !n ) return _hPopUpORMenu;
	short i, id;

	for ( i = n-1; i >= 0; i-- )
	{
		id = GetMenuItemID( _hPopUpORMenu, i );
		if ( id < 0 )
			DestroyMenu( GetSubMenu( _hPopUpORMenu, i ));
		DeleteMenu( _hPopUpORMenu, i, MF_BYPOSITION );
	}
	return _hPopUpORMenu;
}

// Einklinken eines neuen Werkzeuges in das Werkzeugfenster -------------------
short TriasExtension :: InstallTool (ResID rsc, const char *pDesc)
{
	if (rsc.Handle() == 0) return -1;

// Laden der Bitmap 
HBITMAP hBmp;

	if ((uint)rsc) hBmp = LoadBitmap (rsc.Handle(), MAKEINTRESOURCE((uint)rsc));
	else	       hBmp = LoadBitmap (rsc.Handle(), (const char *)rsc);

INSTALLTOOL IT;

	memset (&IT, '\0', sizeof(INSTALLTOOL));
	IT.dwSize = sizeof (INSTALLTOOL);
	IT.hBmp = hBmp;
	IT.pDesc = (char *)pDesc;

// die Bitmap gehört ab jetzt vollständig TRIAS !

return DEX_InstallTool (IT);
}

void TriasExtension :: RemoveTool (short iToolID)
{
	DEX_RemoveTool (iToolID);
}

