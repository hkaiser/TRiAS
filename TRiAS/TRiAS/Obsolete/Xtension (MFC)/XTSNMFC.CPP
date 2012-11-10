// Routinen für Klasse TriasExtension ----------------------------------------
// File: XTSNMFC.CPP

#include <afxwin.h>

extern "C" {
	#include <xtension.h>
	#include <xtensnx.h>
	#include <stdlib.h>
	#include <string.h>
	#include <protos.h>             
	#include <resstrg.h>            
}

#include <xtsnmfc.hpp>
#include <errcodes.hxx>         

// gloable Variablen                      
HINSTANCE g_hInstance;                    

extern "C" {
	UINT __DexReg;
	UINT __DexUnReg;
	UINT __DexCmd;
	UINT __DexNotify;
	HWND __hWndM;
}
  

// Funktionsprototypen --------------------------------------------------------
CTriasExtension *g_pTE = NULL;  // diese Erweiterung

extern "C" {    // TriasExtensionProc soll von auáen gerufen werden

// Routine, welche exportiert werden muá, da sie die eigentliche Schnittstelle
// zu TRIAS(R) darstellt. Diese Routine wird von TRIAS(R) für jede übergebene
// Message gerufen. Sie muß in jeder Erweiterung identisch heiáen und 
// identische Parametertypen erwarten.
                          
_XTENSN_ENTRY LRESULT WINAPI __export TriasExtensionProc (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)                          
{

	switch (wMsg) {
	case DEX_LOADEXTENSION:                     
	//
	// DEX_LOADEXTENSION wird gerufen, nachdem DLL geladen wurde.
	// Die Erweiterung muá an dieser Stelle initialisiert werden. Auáerdem
	// muß ein Handle auf das Menu der Erweiterung, sowie ein im Hauptmenu
	// von TRIAS(R) für dieses Menu anzuzeigender Menutext zurück übergeben
	// werden.
	//
		{
		// Die Datenstruktur 'TRIAS_LOAD' dient der Übergabe aller
		// zur Einbindung in TRIAS(R) notwendigen Informationen zur 
		// und von der Erweiterung. (s. XTENSION.H)
		TRIAS_LOAD *pTL = (TRIAS_LOAD *)lParam;

			if (pTL == NULL) return EC_ILLPARS;     // ParameterFehler

		// An dieser Stelle wird die vom Nutzer bereitgestellte Funktion
		// NewExtension gerufen, die nicht weiter tun darf und muá, als 
		// die Erweiterung (als Klasse) typrichtig zu erzeugen.
			g_pTE = NewExtension (pTL);     // muß vom Nutzer bereitgestellt sein
			if (g_pTE == NULL) 
				return EC_NOMEMORY;

		// übergebene Parameter merken
			g_pTE -> m_hDex = (HDEX)wParam;

			__hWndM = hWnd;
			g_pTE -> m_pMWnd = new CWnd();
			g_pTE -> m_pMWnd -> Attach (hWnd);
			
			g_pTE -> m_DefProc = pTL -> fcDef;              // DefaultProcedure     
			g_pTE -> m_uiMenuOffset = pTL -> wMenuDelta;

		// MenuHandle's und MenuTexte speichern und an TRIAS(R) zurück-
		// liefern
			if (pTL -> hMenu = g_pTE -> MenuHandle())
				strncpy (pTL -> szMenuName, g_pTE -> MenuEntry(), DEX_MENUNAMELEN);
			if (pTL -> hORMenu = g_pTE -> ORMenuHandle())
				strncpy (pTL -> szORMenuName, g_pTE -> ORMenuEntry(), DEX_MENUNAMELEN);
		}
		return EC_OKAY;         // EC_OKAY: kein Fehler

	case DEX_UNLOADEXTENSION:       
	//
	// DEX_UNLOADEXTENSION wird gerufen bevor DLL freigegeben wird.
	// an dieser Stelle kann der gesamte von der Erweiterung angeforderte
	// Speicher freigegeben werden, sowie sonstige Aufräumarbeiten durch-
	// geführt werden.
	//
		if (g_pTE) {
		BOOL Result = g_pTE -> UnLoadExtension ();      // virtuelle Funktion rufen

		// Hier wird die von Nutzer bereitgestellte Funktion DeleteExtension
		// gerufen, die die ErweiterungsKlasse typrichtig freigibt.
			DeleteExtension (g_pTE);        // Extension wieder freigeben
			return Result;
		}
		return FALSE;           // ansonsten Fehler melden

	default:
		if (g_pTE) 
			return g_pTE -> Dispatch (hWnd, wMsg, wParam, lParam);
	}

return FALSE;
}

}       // extern "C"

// Platzhalter für die virtuellen EventHandler der Erweiterung ----------------
BOOL CTriasExtension :: InitExtension (short) { return TRUE; }
BOOL CTriasExtension :: UnLoadExtension (void) { return TRUE; }
BOOL CTriasExtension :: MenuInit (HMENU, HWND) { return TRUE; }
BOOL CTriasExtension :: MenuSelect (WPARAM, HWND) { return TRUE; }
BOOL CTriasExtension :: MenuCommand (WPARAM, HWND) { return TRUE; }
LRESULT CTriasExtension :: Notification (WPARAM, LPARAM) { return FALSE; }
LRESULT CTriasExtension :: WindowsNotification (UINT, WPARAM, LPARAM) { return FALSE; }

// lokaler EventDispatcher ----------------------------------------------------
LRESULT CTriasExtension :: Dispatch (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
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
		return InitExtension (wParam);  // virtuelle Funktion rufen

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
		return MenuSelect (wParam, (HWND)lParam);       // virtuelle Funktion rufen

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
		else if (hWnd == (HWND)hDex())
			return WindowsNotification (wMsg, wParam, lParam);

	//
	// Alle nicht durch diese Erweiterung bearbeiteten Messages von
	// TRIAS(R) müssen an die Standardverarbeitungsroutine in TRIAS(R)
	// zurückgeliefert werden. Das ist notwendig, um in jedem Fall eine 
	// definierte Reaktion auf eine Message zu erhalten.
	//
//              return (*m_DefProc)(hDex(), wMsg, wParam, lParam);
	}

return FALSE;
}

// ----------------------------------------------------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
CTriasExtension :: CTriasExtension (UINT iMenuID, UINT iORMenuID)
{
// Flag für alle Fälle rücksetzen
	m_fIsValid = FALSE;
	m_DefProc = NULL;
	m_pMWnd = NULL;

	AfxSetResourceHandle (g_hInstance);
	
// Daten dieser Extension initialisieren
// evtl. HauptMenu aufbauen
	if (iMenuID) {
		m_pLoadedMenu = new CMenu ();
		if (m_pLoadedMenu == NULL) return;      
		m_pLoadedMenu -> LoadMenu (iMenuID);

	// PopUpMenu und MenuText holen
	HMENU hMenu = m_pLoadedMenu -> m_hMenu;

		m_hPopUpMenu = GetSubMenu (hMenu, 0);
		m_pMenuEntry =  new char [DEX_MENUNAMELEN+1];
		if (m_pMenuEntry == NULL) return;
		GetMenuString (hMenu, 0, m_pMenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
	} else {
		m_hPopUpMenu = 0;
		m_pLoadedMenu = NULL;
		m_pMenuEntry = NULL;
	}

	if (iORMenuID) {
		m_pLoadedORMenu = new CMenu ();
		if (m_pLoadedORMenu == NULL) return;    
		m_pLoadedORMenu -> LoadMenu (iORMenuID);

	// PopUpMenu und MenuText holen
	HMENU hMenu = m_pLoadedORMenu -> m_hMenu;

		m_hPopUpORMenu = GetSubMenu (hMenu, 0);
		m_pORMenuEntry = new char [DEX_MENUNAMELEN+1];
		if (m_pORMenuEntry == NULL) return;
		GetMenuString (hMenu, 0, m_pORMenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
	} else {
		m_hPopUpORMenu = 0;
		m_pLoadedORMenu = NULL;
		m_pORMenuEntry = NULL;
	}

// Registrieren der Messages
CString resStr;

	resStr.LoadString (IDS_DEXMESSAGE);
	__DexCmd = RegisterWindowMessage (resStr);
	resStr.Empty();
	resStr.LoadString (IDS_QNFYMESSAGE);
	__DexReg = RegisterWindowMessage (resStr);
	resStr.Empty();
	resStr.LoadString (IDS_QNFYUNREGMESSAGE);
	__DexUnReg = RegisterWindowMessage (resStr);
	resStr.Empty();
	resStr.LoadString (IDS_NOTIFICATION);
	__DexNotify = RegisterWindowMessage (resStr);
	resStr.Empty();

	if (__DexCmd == 0 || __DexReg == 0 || __DexUnReg == 0 || __DexNotify == 0) 
		return;

// alles ok
	m_fIsValid = TRUE;              // Objekt ist gültig
}

CTriasExtension :: ~CTriasExtension (void) 
{
	DELETE (m_pLoadedMenu);
	DELETE (m_pLoadedORMenu);
	DELETE (m_pMenuEntry);
	DELETE (m_pORMenuEntry);

	if (m_pMWnd) {
		m_pMWnd -> Detach();
		delete m_pMWnd;
	}
}


// Notifikationsbehandlung ----------------------------------------------------
LRESULT CTriasExtension :: RegisterNotification (UINT wMsg, BOOL isLocal) 
{
	return SendMessage (__hWndM, __DexReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal)); 
}

LRESULT CTriasExtension :: UnRegisterNotification (UINT wMsg, BOOL isLocal)
{
	return SendMessage (__hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));
}


HWND CTriasExtension :: GetActiveORWindow (void)
{
	return (HWND)SendMessage (__hWndM, __DexCmd, (WPARAM)DEX_QUERYACTIVEORWINDOW, 0L);
}


UINT CTriasExtension :: InstallMenuItem (UINT iMenuID, UINT iMenuStr, 
					 BOOL iORMenu, short iPopupNum,
					 short iMenuPos)
{
INSTALLMENUITEM imi;
CString RS;

	RS.LoadString (iMenuStr);

	imi.dwSize = sizeof (INSTALLMENUITEM);
	imi.pMenuText = (char *)(const char *)RS;
	imi.hDex = hDex();
	imi.iMenuID = iMenuID;
	imi.iFlag = iORMenu;
	imi.iMenuNum = iPopupNum;
	imi.iMenuPos = iMenuPos;

	DEX_InstallMenuItem (imi);

return imi.iMenuID;             // neuen MenuID merken
}

void CTriasExtension :: RemoveMenuItem (UINT iMenuID, BOOL iORMenu, short iPopupNum)
{
REMOVEMENUITEM rmi;

	rmi.dwSize = sizeof(REMOVEMENUITEM);
	rmi.hDex = hDex();
	rmi.iMenuID = iMenuID;
	rmi.iMenuNum = iPopupNum;
	rmi.iFlag = iORMenu;
	DEX_RemoveMenuItem (rmi);
}

// Einklinken eines neuen Werkzeuges in das Werkzeugfenster -------------------
short CTriasExtension :: InstallTool (UINT rsc, const char *pDesc)
{
	if (rsc == 0) return -1;

// Laden der Bitmap 
CBitmap CBmp;

	CBmp.LoadBitmap (rsc);

INSTALLTOOL IT;

	memset (&IT, '\0', sizeof(INSTALLTOOL));
	IT.dwSize = sizeof (INSTALLTOOL);
	IT.hBmp = (HBITMAP)CBmp.Detach();
	IT.pDesc = (char *)pDesc;

// die Bitmap gehört ab jetzt vollständig TRIAS !
	
return DEX_InstallTool (IT);
}


short CTriasExtension :: InstallTool (const char *pRsc, const char *pDesc)
{
	if (pRsc == NULL) return -1;

// Laden der Bitmap 
CBitmap CBmp;

	CBmp.LoadBitmap (pRsc);

INSTALLTOOL IT;

	memset (&IT, '\0', sizeof(INSTALLTOOL));
	IT.dwSize = sizeof (INSTALLTOOL);
	IT.hBmp = (HBITMAP)CBmp.Detach();
	IT.pDesc = (char *)pDesc;

// die Bitmap gehört ab jetzt vollständig TRIAS !
	
return DEX_InstallTool (IT);
}


void CTriasExtension :: RemoveTool (short iToolID)
{
	DEX_RemoveTool (iToolID);
}

/////////////////////////////////////////////////////////////////////////////
// Library init -- wird von der MFC gerufen

BOOL CExtDLL::InitInstance()
{
	// any DLL initialization goes here
	// TRACE("TextExt.DLL initializing\n");
	SetDialogBkColor();     // grey dialogs in the DLL as well
	g_hInstance = m_hInstance;
	return TRUE;
}

int CExtDLL::ExitInstance()
{
	// any DLL termination goes here (WEP-like code)
	return CWinApp::ExitInstance();
}

