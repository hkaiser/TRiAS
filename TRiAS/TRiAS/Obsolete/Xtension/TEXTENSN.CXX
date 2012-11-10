// Routinen fuer Klasse TriasExtension ----------------------------------------
// File: TEXTENSN.CXX

#include "xtensnp.hxx"

extern "C" HINSTANCE hInstance;

extern "C" {
	UINT __DexReg;
	UINT __DexUnReg;
	UINT __DexCmd;
	UINT __DexxCmd;
	UINT __DexNotify;
	HWND __hWndM;

#if defined(__XT) && defined(__DEXPROCS)
	DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
	DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
	DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS
}

// Funktionsprototypen --------------------------------------------------------
static void PreCalcVersion (void);

TriasExtension *pTE = NULL;	// diese Erweiterung

extern "C" {	// TriasExtensionProc soll von auáen gerufen werden

// Routine, welche exportiert werden muß, da sie die eigentliche Schnittstelle
// zu TRIAS(R) darstellt. Diese Routine wird von TRIAS(R) für jede übergebene
// Message gerufen. Sie muß in jeder Erweiterung identisch heiáen und 
// identische Parametertypen erwarten.

_XTENSN_ENTRY
LRESULT WINAPI _XTENSN_EXPORT TriasExtensionProc (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case DEX_LOADEXTENSION:		
	//
	// DEX_LOADEXTENSION wird gerufen, nachdem DLL geladen wurde.
	// Die Erweiterung muß an dieser Stelle initialisiert werden. Außerdem
	// muß ein Handle auf das Menu der Erweiterung, sowie ein im Hauptmenu
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

		// WindowsVersion bestimmen
			PreCalcVersion();

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
		bool fResult = pTE -> UnLoadExtension ();	// virtuelle Funktion rufen

		// Hier wird die von Nutzer bereitgestellte Funktion DeleteExtension
		// gerufen, die die ErweiterungsKlasse typrichtig freigibt.
			if (fResult) {
			// nur löschen, wenn entladen werden soll
				DeleteExtension (pTE);	// Extension wieder freigeben
				pTE = NULL;
			}
			return fResult;
		}
		return false;		// ansonsten Fehler melden

	default:
		if (pTE) return pTE -> Dispatch (hWnd, wMsg, wParam, lParam);
	}

return false;
}

}	// extern "C"

// Platzhalter für die virtuellen EventHandler der Erweiterung ----------------
bool TriasExtension :: InitExtension (short) { return true; }
bool TriasExtension :: UnLoadExtension (void) { return true; }
bool TriasExtension :: MenuInit (HMENU, HWND) { return true; }
bool TriasExtension :: MenuSelect (WPARAM, HWND) { return true; }
bool TriasExtension :: MenuCommand (WPARAM, HWND) { return true; }
LRESULT TriasExtension :: Notification (WPARAM, LPARAM) { return false; }
LRESULT TriasExtension :: WindowsNotification (UINT, WPARAM, LPARAM) { return false; }

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
		bool Res = InitExtension (wParam);	// virtuelle Funktion rufen

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
		return false;

	default:
	// entsprechende virtuelle Funktionen rufen
		if (wMsg == __DexNotify) 
			return Notification (wParam, lParam);
		else if ((HDEX)hWnd == hDex())
			return WindowsNotification (wMsg, wParam, lParam);
	}
//
// Alle nicht durch diese Erweiterung bearbeiteten Messages von
// TRiAS(R) müssen an die Standardverarbeitungsroutine in TRIAS(R)
// zurückgeliefert werden. Das ist notwendig, um in jedem Fall eine 
// definierte Reaktion auf eine Message zu erhalten.
//
return _DefProc (hDex(), wMsg, wParam, lParam);
}

// ----------------------------------------------------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
TriasExtension :: TriasExtension (UINT iMenuID, UINT iORMenuID)
{
// Flag für alle Fälle rücksetzen
	_isValid = false;
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

#if defined(__XT) && defined(__DEXPROCS)
// externe EntryPoints von Trias finden
#if !defined(WIN32)
HMODULE hTrias = NULL;
#else
HMODULE hTrias = GetModuleHandle (TRIAS_MODULENAME);
#endif
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
	g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXXEXTENSIONPROC");
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

// alles ok
	_isValid = true;		// Objekt ist gültig
}

TriasExtension :: ~TriasExtension (void) 
{
	DELETE (_pLoadedMenu);
	DELETE (_pLoadedORMenu);
	DELETE (_pMenuEntry);
	DELETE (_pORMenuEntry);
	DELETE (_pRF);

	g_pDexExtensionProc = NULL;
	g_pDexxExtensionProc = NULL;
	g_pDexNotificationProc = NULL;
}


// Notifikationsbehandlung ----------------------------------------------------
LRESULT TriasExtension :: RegisterNotification (UINT wMsg, bool isLocal) 
{
	return SendMessage (__hWndM, __DexReg, (WPARAM)_hDex, MAKELONG (wMsg, isLocal)); 
}

LRESULT TriasExtension :: UnRegisterNotification (UINT wMsg, bool isLocal)
{
	return SendMessage (__hWndM, __DexUnReg, (WPARAM)_hDex, MAKELONG (wMsg, isLocal));
}

pWindow TriasExtension :: MWind (void) 
{
static pWindow pMWind = NULL;

	if (pMWind == NULL)
		pMWind = (pWindow)DexxExtensionProc((WPARAM)DEXX_MAINWINDOW, 0L);

	return pMWind;
}

pWindow TriasExtension :: ORWind (HWND hWnd)
{
	return (pWindow)DexxExtensionProc((WPARAM)DEXX_ORWINDOW, (LPARAM)hWnd);
}

HWND TriasExtension :: GetActiveORWindow (void)
{
	return (HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEORWINDOW, 0L);
}

HelpDisplay *TriasExtension :: MainHD (void)
{
	return (HelpDisplay *)DexxExtensionProc((WPARAM)DEXX_MAINHELPDISPLAY, 0L);
}

UINT TriasExtension :: InstallMenuItem (UINT iMenuID, UINT iMenuStr, 
					bool iORMenu, short iPopupNum,
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

void TriasExtension :: RemoveMenuItem (UINT iMenuID, bool iORMenu, short iPopupNum)
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


#if !defined(WIN32)
// WindowsVersion feststellen -------------------------------------------------
static bool s_fWin31 = false;
static bool s_fWin40 = false;
static bool s_fWinNT = false;
static bool s_fWin32s = false;

static void PreCalcVersion (void)
{
// Initialise Version Info
DWORD dwVersion = GetVersion();

	s_fWin31 = false;
	s_fWinNT = false;
	s_fWin32s = false;
	s_fWin40 = false;

#if defined(WIN32)
	if (dwVersion < ~0x7fffffff) {			// Windows NT
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin31 = true;
			s_fWinNT = true;
	} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin31 = true;
			s_fWin32s = true;
	} else {					// Chicago
			s_fWin31 = true;
			s_fWin40 = true;
	}
#else
	if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
	    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
		s_fWin31 = true;
#endif
}

bool IsWin31 (void) { return s_fWin31; }
bool IsWin40 (void) { return s_fWin40; }
bool IsWin32s (void) { return s_fWin32s; }
bool IsWinNT (void) { return s_fWinNT; }

#else
static void PreCalcVersion (void) {}
#endif // !WIN32

#if defined(__XT) && defined(__DEXPROCS)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}

LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexxExtensionProc)
		return (*g_pDexxExtensionProc)(w, l);

return :: SendMessage (__hWndM, __DexxCmd, w, l);
}

LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

return :: SendMessage (__hWndM, __DexNotify, w, l);
}

LRESULT PASCAL DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

return :: PostMessage (__hWndM, __DexNotify, w, l);
}

#endif // __XT && __DEXPROCS


#if defined(WIN32)

_TF_ENTRY32 int _DLLENTRY CallAppExec (ExecType et);

int	App :: Exec	(ExecType et)
{
	return CallAppExec (et);
}

#endif
