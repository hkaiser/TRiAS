// IRIS - Mainprogramm -- Version fuer Win32 ----------------------------------
// File: IRISMAI2.CXX

#include "triaspre.hxx"

#include <TransEx.h>
#include <new>

#include <ole2ver.h>
#include <fnamestr.h>
#include <printer.hxx>
#include <TRiASMode.h>
#include <ScopeVar.h>

#include <dirisole.h>

#include "triasres.h"
#include "extmain3.hxx"

#include "tools.hxx"
#if defined(OLD_COORDS)
#include "coords.hxx"   // Koordinatenanzeige
#endif // OLD_COORDS
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#include "ausschn.hxx"
#include "saveopt.hxx"
#include "opendb.hxx"
#include "bildobj.hxx"
#include "signon.hxx"
#include "overview.hxx"
#include "selectid.hxx"
#include "selnview.hxx"
#if !defined(_OLD_DRAGNDROP)
#include "viewdrop.h"
#endif // !_OLD_DRAGNDROP

#include <prntpars.hxx>
#include <registry.hxx>

#include "triasres.h"
#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

///////////////////////////////////////////////////////////////////////////////
//
VisType VMskToVTyp (short iVMsk, short iMsk);
int ShowCreateNewDBDialog (pWindow pW, string &strDBName, string &strUserName, string &strPWD);
HRESULT CreateShortCut (LPCSTR pszShortcutFile, LPCSTR pszLink, LPCSTR pszDesc);
void InitWindowsVersion (void);

///////////////////////////////////////////////////////////////////////////////
//
ExtDirisWindow *CurrActDirisW = NULL;	// derzeit aktives Datenfenster

App *g_pCurrApp = NULL;            // aktuelle Programminstanz
short GCancelFlag = GCFNormal;       // General Cancel Flag

// Variablen für die Hilfeverwaltung
HelpDisplay *IrisHD = NULL;
bool wasHelpEvt = false;

int g_iActTool = NUMARROW;

CLegendeWindow *pLegende = NULL;		// Legende
COverView *pOverView = NULL;			// Übersichtsanzeige
bool LegendeCFlag = false;				// Legende angezeigt
bool LegendToRepaint = false;
bool OverViewCFlag = false;

bool PrintEFlag = true;                 // Drucken

#if !defined(NOPROJEKTION)
bool GeographicCFlag = true;            // geografische Koordinaten
bool WorldCFlag = false;                // Weltprojektion
#endif

bool inzFlag = false;                   // aktuelle DB ist verschnitten
bool DrawTextObjs = true;				// TextObjekte zeichnen

///////////////////////////////////////////////////////////////////////////////
// Enable-Fags für MenuPunkte 
bool CloseEFlag = false;                // Projekt schlieáen
bool EditHeaderEFlag = false;           // DB-Header editieren
bool DrawEFlag = false;                 // Geometrie neu zeichnen
bool IdentSelEFlag = false;             // IdentifikatorSelektion

// Timer für Sepichern alle x Minuten
extern short g_iMinutes;
extern short g_iTicks;

short g_iHideFlags = ROSortObjNr|ROHideIdent;	// was soll ausgeblendet werden

short g_iSignOnTicks = 0;
CSignOnDlg *g_pSODlg = NULL;			// SignOnDlg

bool g_fPendingSave = false;			// Speichern muß gemacht werden
bool g_fPendingReReadCaption = false;	// ReReadCaption notwendig

Timer *g_pT = NULL;

bool g_fMenu = true;					// Menu's anzeigen
extern bool g_fFilters;					// Exportfilter installiert

// externe Variablen
extern HPALETTE hPalette;				// aktive Farbpalette

HINSTANCE hInstance = 0;				// Handle dieser Programminstanz

// Zentrales Verzeichnis für DQLScripte
extern char cbDefaultDir[_MAX_PATH+1];	// StandardWurzelVerzeichnis der Projekte

char g_cbHelpPath[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop support
DWORD g_dwScrollInset = ::GetProfileInt (g_cbWindowsSection, g_cbScrollInset, DD_DEFSCROLLINSET);
DWORD g_dwScrollDelay = ::GetProfileInt (g_cbWindowsSection, g_cbScrollDelay, DD_DEFSCROLLDELAY);

///////////////////////////////////////////////////////////////////////////////
// support für PreTranslateMsg in nichtmodalen Dialogen
// bool App_PreTranslateMessage (MSG *pMsg);
// bool (*g_pPreTransMsgProcChain)(MSG *) = NULL;

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die MenuPunkt freigeben bzw. kennzeichnen 
void MenuCheck (pMenu pM, int MenuItem, bool Flag) 
{
	if (Flag) pM -> CheckItem (MenuItem);
	else      pM -> unCheckItem (MenuItem);
}
void MenuEnable (pMenu pM, int MenuItem, bool Flag) 
{
	if (Flag) pM -> EnableItem (MenuItem);
	else      pM -> DisableItem (MenuItem);
}

// Analysieren der Kommandozeile ----------------------------------------------

// Variablen, die vordefinierte DB eröffnen -----------------------------------
static char *s_pToOpenDBName = NULL;		// DBName
static char *s_pToOpenUserName = NULL;		// NutzerName
static bool s_fToOpenROMode = false;		// Read/Only - Mode
static bool s_fStandardSight = false;		// StandardSicht aktivieren
static bool s_fToInit3d = true;			// CTL3D verwenden
static bool s_fToShow = true;			// Haupfenster anzeigen
static bool s_fSignOn = true;			// SignOn anzeigen

static bool g_fSilentReg = false;		// Fertigmeldung nach /regserver bzw. /unregserver
static bool g_fFullUninstall = false;	// unregserver:full
static bool g_fRegServer = false;		// selfregistering
static bool g_fFullRegServer = false;	// full selfregistering
static bool g_fRegServerSetup = false;	// RegServer im Setup
static bool g_fRegServerCont = false;	// RegServer im Setup und weitermachen
static bool g_fRegisterAsDemo = false;	// als Demovariante registrieren
static bool g_fUnRegServer = false;		// and unregistering
static bool g_fInitDB = false;			// DB anlegen und exit
static bool g_fInitDBInteractive = false;	// GeoDB-Namen abfragen
static bool g_fInitDBDesktop = false;		// DB auf Desktop ablegen

bool g_fAutomation = false;			// durch OLE Automation gestartet
bool g_fStartByOle = false;			// mit /Embedding gestartet
bool g_fUser = true;				// durch Nutzer gestartet
bool g_fTip = false;				// TipOfTheDay

static void PrintUsage (void) 
{
	VMessageBox (NULL, IDS_PRINTUSAGECAP, ExclamationIcon|OkayButton, IDS_PRINTUSAGE);
}

bool ParseCmdString (const int argc, const char *argv[]) 
{
register int i;
register char *p;

/* Kommandozeile auswerten */
	for (i = 1; i < argc; ++i) {
		p = (char *)argv[i];
		if (*p == '-' || *p == '/') {
		++p; switch (*p++) {
			case 'R':
			case 'r':
				if (*p) {	// selfregistering
				string strCmd = strupr (p-1);

					if (NPOS != strCmd.find ("REGSERVER")) {
						g_fRegServer = true;
						if (NPOS != strCmd.find("ADMIN"))
							g_fFullRegServer = true;
						if (NPOS != strCmd.find("SILENT"))
							g_fSilentReg = true;
						if (NPOS != strCmd.find("SETUP"))
							g_fRegServerSetup = true;
						if (NPOS != strCmd.find("CONTINUE"))
							g_fRegServerCont = true;
						if (NPOS != strCmd.find("DEMOREGNUM"))
							g_fRegisterAsDemo = true;
						break;
					}
				}
				s_fToOpenROMode = true;
				break;

			case 'i':		// Init Database and exit
			case 'I':
				if (*p) {
				string strCmd = strupr (p-1);

					if (NPOS != strCmd.find ("INIT")) {
						g_fInitDB = true;
						if (NPOS != strCmd.find("ASK"))
							g_fInitDBInteractive = true;
						if (NPOS != strCmd.find("NOSHORTCUT"))
							g_fInitDBDesktop = true;
					}
				}
				break;

#if !defined(WIN32)
			case '3':
				s_fToInit3d = false;
				break;
#endif // !WIN32
			case 'A':	// /Automation ?
			case 'a':
				g_fAutomation = !strcmp (strupr(p-1), "AUTOMATION");
				s_fToShow = false;	// erstmal nicht anzeigen
				break;
				
			case 'e':	// /Embedding bzw. -Embedding testen
			case 'E':
				g_fStartByOle = !strcmp (strupr(p-1), "EMBEDDING");
				s_fToShow = false;	// erstmal nicht anzeigen
				break;
				
			case 's':
			case 'S':
				s_fStandardSight = true;
				break;

			case 'h':	// Fenster nicht anzeigen
			case 'H':
				s_fToShow = false;
				break;

			case 'n':	// n SignOnDlg
			case 'N':
				s_fSignOn = false;
				break;
				
			case 'm':
			case 'M':
				g_fMenu = false;
				break;
				
			case 't':	// force TipOfTheDay
			case 'T':
				g_fTip = true;
				break;

			case 'U':
			case 'u':
				{
				string strCmd = strupr (p-1);
				
				// selfunregistering ?
					g_fUnRegServer = (NPOS != strCmd.find ("UNREGSERVER"));
					if (g_fUnRegServer) {
						if (NPOS != strCmd.find("SILENT"))
							g_fSilentReg = true;
						if (NPOS != strCmd.find("FULL"))
							g_fFullUninstall = true;
						break;
					}

				// ansonsten UserName
					if (s_pToOpenUserName == NULL) {
						s_pToOpenUserName = new char [strlen(p) +1];
						if (s_pToOpenUserName == NULL) {
							db_error (EC_NOMEMORY, RC_ParseCmdString);
							DELETE (s_pToOpenDBName);
							return false;
						}
						strcpy (s_pToOpenUserName, p);
						strlwr (s_pToOpenUserName);
					}
				}
				break;

			default:
				PrintUsage ();
				DELETE (s_pToOpenDBName);
			}
		} else if (s_pToOpenDBName == NULL) {
		/* ASCII-Dateiname */
			s_pToOpenDBName = new char [strlen(p) +1];
			if (s_pToOpenDBName == NULL) {
				db_error (EC_NOMEMORY, RC_ParseCmdString);
				return false;
			}
			strcpy (s_pToOpenDBName, p);
		} else {
		/* ungueltiger Parameter */
			PrintUsage ();
			DELETE (s_pToOpenDBName);
			return false;
		}
	}

// überprüfen, ob Extension gegeben ist, wenn nicht, dann Standard setzen
	if (s_pToOpenDBName != NULL) {
	char *pPath = new char [_MAX_PATH];
	char *pDrive = new char [_MAX_DRIVE];
	char *pName = new char [_MAX_FNAME];
	char *pExt = new char [_MAX_EXT];

		_splitpath (s_pToOpenDBName, pDrive, pPath, pName, pExt);
		if (*pExt == '\0') {
		// neue Erweiterung einsetzen, wenn keine da ist
			_makepath (s_pToOpenDBName, pDrive, pPath, pName, 
					    ResString (IDS_RISEXT, 6)+1);
		}
		DELETE (pPath);
		DELETE (pDrive);
		DELETE (pName);
		DELETE (pExt);
	}

// wenn kein Nutzername gegeben ist, dann default USER generieren
	if (s_pToOpenDBName != NULL && s_pToOpenUserName == NULL) {
	char *pUserName = new char [_MAX_FNAME];

		_splitpath (s_pToOpenDBName, NULL, NULL, pUserName, NULL);
		if (s_pToOpenUserName == NULL || pUserName == NULL) {
			s_pToOpenUserName = new char [strlen(p) +1];
			if (s_pToOpenUserName == NULL) {
				db_error (EC_NOMEMORY, RC_ParseCmdString);
				DELETE (s_pToOpenDBName);
				DELETE (pUserName);
				return false;
			}
			strcpy (s_pToOpenUserName, pUserName);
			strlwr (s_pToOpenUserName);
		}
		DELETE (pUserName);
	}

	if (g_fInitDB && !g_fInitDBDesktop && 
	    !g_fInitDBInteractive && NULL == s_pToOpenDBName) 
	{
		PrintUsage ();
		return false;
	}

return true;
}


// Hauptprogramm --------------------------------------------------------------
bool g_fCtl3dInit = false;
bool g_fOleInitialized = false;

static bool InitOle (void);

CFreeStore *App :: InitApp (CFreeStore *pFS)
{
// OLE2.0 initialisieren
	if (!InitOle()) return NULL;		// InitialisierungsFehler
	
return pFS;
}


void App :: DeInitApp (void)
{
	if (g_fOleInitialized)
		OleUninitialize();	// OLE wieder freigeben
}


// Initialisieren von Ole, wenn keine Erweiterung es getan hat ----------------
static bool InitOle (void)
{
	if (OleInitialize (NULL) == S_OK)
		g_fOleInitialized = true;
	else
		g_fOleInitialized = false;

return true;
}

static void GenerateNewFile (bool fInteractive, bool fDesktop)
{
	if (fDesktop && !IsWin40()) {
		VMessageBox (NULL, IDS_BADOLEVERSIONCAP,
					ExclamationIcon|OkayButton, IDS_NOWIN40);
		return;		// nur unter 4.0
	}

string strDeskTop (_MAX_PATH, default_size);
string strDBName;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{		// Pfad der DeskTop-Dateien finden
	CCurrentUser regDT (TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"));
	DWORD dw = strDeskTop.length();

		regDT.GetSubSZ (TEXT("Desktop"), (LPSTR)strDeskTop.c_str(), dw);
	}
	strDeskTop.adjustlen();
	if (strDeskTop.rfind ('\\') != strDeskTop.length())
		strDeskTop += '\\';	// garantiert mit '\\' abschließen

	if (fInteractive) {
	string strUserName, strPWD;
	Window MWnd (GetDesktopWindow());
	int iIndex = ShowCreateNewDBDialog (&MWnd, strDBName, strUserName, strPWD);

		if (iIndex > 0) {
		LPSTORAGE pIStorage = NULL;

			::CreateNewGeoDB (strDBName.c_str(), (iIndex == 1) ? &pIStorage : NULL, 0, 
				strUserName.c_str(), strPWD.c_str());	// GeoDB erzeugen
			if (pIStorage) pIStorage -> Release();
		}
	} else {
		if (fDesktop && strDeskTop.length() > 0)		// auf Desktop erzeugen
			strcpy (cbDefaultDir, strDeskTop.c_str());	// kein Pfad --> Desktop

		if (NULL == s_pToOpenDBName || '\0' == *s_pToOpenDBName)
			strDBName = ResString (IDS_NONAME, 32).Addr();
		else
			strDBName = s_pToOpenDBName;

	LPSTORAGE pIStorage = NULL;

		if (::CreateNewGeoDB (strDBName.c_str(), &pIStorage)) {
			if (!fDesktop) {
			STATSTG stg;		// aktuellen Projektnamen besorgen

				pIStorage -> Stat (&stg, STATFLAG_DEFAULT);
				strDBName = AnsiString (stg.pwcsName);
				CoTaskMemFree (stg.pwcsName);
			}
			pIStorage -> Commit (STGC_DEFAULT);
			pIStorage -> Release();
		}
	}

// hier noch Link zu neuer GeoDB erzeugen und in Desktop ablegen, wenn nicht
// schon das Projekt selbst dort ist
	if (!fDesktop && strDBName.length() > 0) {
	ResString resSCutDesc (IDS_SHORTCUTDESCTEMPLATE, 64);

		strDeskTop += resSCutDesc.Addr();
		strDeskTop += get_name (strDBName);
		strDeskTop += ".lnk";

	string strDesc = resSCutDesc.Addr();

		strDesc += get_name (strDBName);
		CreateShortCut (strDBName.c_str(), strDeskTop.c_str(), strDesc.c_str());
	}
	delete [] s_pToOpenDBName;
}

#if defined(_DEBUG)
#include <crtdbg.h>
#endif // _DEBUG

void App :: Start (const int argc, const char *argv[]) 
{
#if !defined(ENABLE_WIN32_CODE)
	if (IsWin32s()) {
		VMessageBox (NULL, IDS_BADOLEVERSIONCAP, 
					ExclamationIcon|OkayButton, IDS_NOTFORWIN32);
		return;
	}
#endif

	hInstance = Handle (API_APP_HAPP);  // ApplikationHandle speichern

#if defined(_DEBUG)
DWORD dwShowSignOnTopMost = true;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegConfig);
	DWORD dwHaltOnStartup = false;

		regCfg.GetDWORD (TEXT("HaltOnStartup"), dwHaltOnStartup);
		TX_ASSERT(dwHaltOnStartup == false);	// bei Bedarf sofort nach dem Start anhalten

	DWORD dwMemDbg = _CrtSetDbgFlag (_CRTDBG_REPORT_FLAG);
	DWORD dwNewMemDbg = 0;

		if (regCfg.GetDWORD (TEXT("UseCrtMemDbgFlag"), dwNewMemDbg) && dwNewMemDbg) {
			if (regCfg.GetDWORD (TEXT("CrtMemDbgFlag"), dwNewMemDbg))
				_CrtSetDbgFlag (dwMemDbg|dwNewMemDbg);
		}

		regCfg.GetDWORD (TEXT("ShowSignOnTopMost"), dwShowSignOnTopMost);
	}
#endif // _DEBUG

// Behandlung von Exceptions
	{
	CCurrentUser regCfg (g_cbRegConfig);
#if defined(_DEBUG)
	DWORD dwHandleExceptions = CWin32Exception::W32EXP_None;
#else
	const UINT TRIAS_DEFAULT_EXCEPTIONS = 
		CWin32Exception::W32EXP_MathException |
		CWin32Exception::W32EXP_PrivInstruction |
		CWin32Exception::W32EXP_AccessViolation |
		CWin32Exception::W32EXP_DatatypeMisalignment |
		CWin32Exception::W32EXP_ArrayBoundsExceeded;

	DWORD dwHandleExceptions = (IsWin40() && IsWinNT()) ? 
		TRIAS_DEFAULT_EXCEPTIONS : CWin32Exception::W32EXP_None;
#endif 
		regCfg.GetDWORD (TEXT("HandleExceptions"), dwHandleExceptions);
		if (dwHandleExceptions != CWin32Exception::W32EXP_None) {
			CWin32Exception::Translate (dwHandleExceptions);
			CWin32Exception::SetTranslator();
		}

// TRiASMode einlesen
		{
		CCurrentUser reg (g_cbFakeMFCKey);

			g_dwTRiASMode = 
				TRIASMODE_SubClassTRiAS | 
				TRIASMODE_HookTRiAS | 
				TRIASMODE_SubClassTRiASView |
				TRIASMODE_InterTRiAS;
#if defined(_DEBUG)
				g_dwTRiASMode |= TRIASMODE_GDO;
#endif // _DEBUG
			reg.GetDWORD (g_cbTRiASMode, g_dwTRiASMode);
		}

	// Namen ändern/initialisieren
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize)) {
			if (g_dwTRiASMode & TRIASMODE_InterTRiAS)
				strcpy (g_cbTRiAS, g_cbCopyrightNameT);		// default: InterTRiAS
			else
				strcpy (g_cbTRiAS, g_cbCopyrightName);		// default: TRiAS

		// für alle Erweiterungen hier wegschreiben
			regCfg.SetSubSZ (g_cbTRiASName, g_cbTRiAS);
		}
	}

// sonstige Initialisierungen
bool fParsed = ParseCmdString (argc, argv);

// wenn GeoDB angelegt werden soll, dann selbiges tun und wieder raus
	if (g_fInitDB) {
		if (fParsed)
			GenerateNewFile (g_fInitDBInteractive, g_fInitDBDesktop);
		return;
	}

// verhindern, daß PostQuitMessage(0) gerufen wird, wenn Fenster zugehen
	SetQuitOnLast (false);

// CTL3D initialisieren
	if (IsWin40()) {
		s_fToInit3d = false;		// Win95 & WinNT40 keine CTL3D verwenden
		g_fCtl3dInit = false;
	}
	if (s_fToInit3d && (g_fCtl3dInit = Ctl3dRegister (hInstance)))
		Ctl3dAutoSubclass (hInstance);

// wenn nur selfregistering bzw. unregistering, dann selbiges tun und wieder raus
	if (g_fRegServer) {	
		TriasRegInit (true, g_fFullRegServer, 
			(g_fSilentReg||!s_fToShow), (g_fRegServerSetup||g_fRegServerCont));
		if (g_fRegisterAsDemo)
			RegisterDemoRegNum();

		if (!g_fRegServerCont)
			return;
	}
	if (g_fUnRegServer) {
		TriasRegUnInit((g_fSilentReg || !s_fToShow), g_fFullUninstall);
		return;
	}

///////////////////////////////////////////////////////////////////////////////
// Env testen, Registry nachführen etc.
Rectangle MWnd;         // FensterGröße
bool IF, ZF;            // IconicFlag und ZoomedFlag

	if (!TestEnv (Handle (API_APP_HAPP)))
		return;                 // Umgebungsbedingungen stimmen nicht

	if (!InitIrisApp (MWnd, ZF, IF))	// diverse Initialisierungen
		return;                 // irgend was stimmt nicht, also raus

///////////////////////////////////////////////////////////////////////////////
// hier geht's richtig los
	g_pSODlg = NULL;

	if (s_fToShow && s_fSignOn) {
		g_pSODlg = CSignOnDlg :: CreateInstance (NULL, hInstance);
		if (g_pSODlg) {
			g_pSODlg -> Show();		// SignOn anzeigen
#if defined(_DEBUG)
			if (dwShowSignOnTopMost)
#endif
			{
				SetWindowPos (g_pSODlg -> Handle (API_WINDOW_HWND),
						  HWND_TOPMOST, 0, 0, 0, 0, 
						  SWP_NOMOVE|SWP_NOSIZE);
			}
			g_pSODlg -> Update();
			g_pSODlg -> PlaySound16();
			g_iSignOnTicks = 0;
		}
	} else
		g_pSODlg = NULL;

#if defined(OLD_TOOLBOX)
	pToolBox = NULL;                // Zeiger auf Werkzeugfenster initialisieren
	ToolBoxCFlag = false;           // Fenster ist nicht angezeigt
#endif // OLD_TOOLBOX

// Zeiger auf diese App merken (muß vor Konstruktor von ExtDirisWindow sein)
	g_pCurrApp = this;

ExtDirisWindow MainWindow (MWnd);             // Hauptfenster

// nicht mehr verhindern, daß PostQuitMessage(0) gerufen wird, wenn Fenster zugehen
	SetQuitOnLast (true);

	MainWindow.FToInit3d (s_fToInit3d);
	MainWindow.FToShow (s_fToShow);

	CurrActDirisW = &MainWindow;	// HauptFenster merken

// PreTranslateMsgproc anbinden, damit in ORFenster Acceleratoren funktionieren
//	g_pPreTransMsgProcChain = DEX_AttachPreTranslateMsgProc (App_PreTranslateMessage);

// Help aktivieren
	{
	char HelpPath[_MAX_PATH];
	char Drive[_MAX_DRIVE];
	char Path[_MAX_DIR];

		_splitpath (argv[0], Drive, Path, NULL, NULL);
		_makepath (g_cbHelpPath, Drive, Path, "", "");
		_makepath (HelpPath, Drive, Path, ResString (IDS_HELPFILE, _MAX_FNAME), 
						  ResString (IDS_HELPEXT, _MAX_EXT));
		wasHelpEvt = false;
		IrisHD = new HelpDisplay (HelpPath);
		if (IrisHD == NULL) {
			db_error (EC_NOHELPFILE, RC_Start);
			return;
		}
	}

// Anfangsparameter des Hauptfensters festlegen
ShowState MSF;

// initialen AnzeigeStatus festlegen
	if (IF) MSF = Iconized;         // als Ikone starten
	else if (ZF) MSF = Zoomed;      // als VollBild starten
	else MSF = Normal;

// Timer erzeugen
Timer Timer1 (500, TIMER_HALFSECOND);	// Timer zur Beseitigung der ObjInfoFenster und
			// für blinken der aktiven Objekte
	if (!MainWindow.SetStrobe (&Timer1)) {
		db_error (EC_NOTIMER, RC_Start);
		return;         // Timer kann nicht gestartet werden
	}

// Speichern aller x Minuten
	if (g_iMinutes) {
		g_pT = new Timer (6000, TIMER_MINUTE);
		if (g_pT == NULL || !MainWindow.SetStrobe (g_pT)) {
			db_error (EC_NOTIMER, RC_Start);
			return;         // Timer kann nicht gestartet werden
		}
	}
	
// verifizieren, ob OLE wirklich aktiv ist
	g_fUser = true;
	s_fToShow = true;
	if (g_fAutomation) g_fAutomation = DEXN_AutomationHandled();
	if (g_fStartByOle) g_fStartByOle = DEXN_EmbeddingHandled();
	if (g_fStartByOle || g_fAutomation) {
		g_fUser = false;
		s_fToShow = false;
	} 

// wenn auf der Kommandozeile ein Projekt gegeben ist, dann dieses eröffnen
	if (fParsed) {
		if (s_pToOpenDBName && g_fUser) {
			g_fTip = DEXN_TipOfTheDay(TOTD_ForceNoTips);

		short gfMode = s_fToOpenROMode ? OM_RO : OM_Normal;

			if (s_fStandardSight) gfMode |= OM_NoStandard;
			if (!MainWindow.FToShow())
				gfMode |= OM_HideWindow;

			if (MSF == Iconized) MSF = Normal;	// bei default Projekt nicht Zoomed 

		// Hauptfenster anzeigen
			MainWindow.InitMenues();		// MRU initialisieren
			MainWindow.Show ((ShowState)(MainWindow.FToShow() ? MSF : HideWindow));

		// Projekt öffnen, Fenster anzeigen etc.
			if (MainWindow.CreateView (s_pToOpenDBName, s_pToOpenUserName, 
									   g_cbNil, gfMode))
			{
				DELETE (g_pSODlg);		// SignOn ausblenden
			} else
				MainWindow.InitMenues();
		} else {	
		// Hauptfenster anzeigen, oder eben auch nicht
			MainWindow.InitMenues();

		// Tips of the Day nur anzeigen lassen, wenn Trias sichtbar ist
		DWORD dwTOTD = s_fToShow ? (g_fTip ? TOTD_ForceTips : TOTD_LookAtRegistry) : TOTD_ForceNoTips;

			g_fTip = DEXN_TipOfTheDay (dwTOTD);
			if (g_fTip) {
				DELETE (g_pSODlg);	// SignOn ausblenden, wenn TipOfTheDay gefordert
			}
			MainWindow.Show ((ShowState)(MainWindow.FToShow() ? MSF : HideWindow));
		}

		DELETE (s_pToOpenDBName);
		DELETE (s_pToOpenUserName);

	// normale Arbeit
		MainWindow.DoExec();
	}

// Timer wieder abschalten
	DELETE (g_pSODlg);	// für alle Fälle: SignOn ausblenden
	MainWindow.CancelStrobe (&Timer1);

	if (g_pT) {
		MainWindow.CancelStrobe (g_pT);
		delete g_pT;
	}

#if defined(OLD_TOOLBOX)
	DELETE (pToolBox);
#endif // OLD_TOOLBOX
	DELETE (IrisHD);

// CTL3D freigeben
	if (g_fCtl3dInit) Ctl3dUnregister (hInstance);

// alle noch offenen Datenbanken schließen
	CleanUpTrias01();
}

///////////////////////////////////////////////////////////////////////////////
// HauptMessageSchleife
void ExtDirisWindow::DoExec (void)
{
//	DEXN_ServerInitialized();	// fertig initialisiert	- jetzt in App::Idle (#HK960117)
	_Module.Init (NULL, hInstance);	// _ATL_CODE

// Messageschleife
bool fWasException;

	do {
		fWasException = false;

		try {
		// MessageLoop rufen, bis wirklich alles beendet wurde
			App::Exec (ExecNormal);

		// alle möglichen Exceptions hier auffangen und an Nutzer  mitteilen
		} catch (CWin32Exception e) {
		// Nutzer warnen, daß eine unhandled Exception aufgetreten ist
			VMessageBox (this, 
					FakeTRiASName(IDS_UNHANDLEDEXCEPTION_CAPTION, g_cbTRiAS).c_str(),
					HandIcon|OkayButton|SetForeground|SystemModal, 
					IDS_UNHANDLEDEXCEPTION, e.what(), g_cbTRiAS);
			fWasException = true;
		}

	} while (fWasException);

	_Module.Term();					// _ATL_CODE
}

//////////////////////////////////////////////////////////////////////////////
// ViewFenster
IrisWind *IrisWind :: CreateInstance (ExtDirisWindow *pFrame, IrisWind *& rpView,
	LPCSTR pcDBName, LPCSTR pcUserName, LPCSTR pcPassWord, short gfMode, DWORD dwMode) 
{
IrisWind *pView = NULL;

	try {
		pView = new IrisWind (pFrame);
		rpView = pView;		// schon mal vorab setzen
		if (!pView -> FInit (pFrame, pcDBName, pcUserName, pcPassWord, gfMode, dwMode)) 
		{
			pView -> CloseDB (false);	// alles wieder schließen
			delete pView;
			return NULL;
		}

	} catch (bad_alloc) {
		return NULL;
	}

return pView;
}

bool IrisWind :: FInit (ExtDirisWindow *pFrame, 
	LPCSTR pcDBName, LPCSTR pcUserName, LPCSTR pcPassWord, short gfMode, DWORD dwMode)
{
#if !defined(_OLD_DRAGNDROP)
// kritische VariablenInitialisierungen
// anlegen und registrieren des DropTargets
CComObject<CViewDropTarget> *pTarget = NULL;

	try {
		THROW_FAILED_HRESULT(CComObject<CViewDropTarget>::CreateInstance(&pTarget));
		THROW_FAILED_HRESULT(pTarget -> QueryInterface (IID_IDropTarget, (LPVOID *)&m_pDropTgt));

		pTarget -> FInit (this);
		CoLockObjectExternal (m_pDropTgt, true, false);
		RegisterDragDrop (Handle(API_WINDOW_HWND), m_pDropTgt);

	} catch (_com_error&) {
		DELETE(pTarget);
		m_pDropTgt = NULL;
		TX_TRACE("TRiAS:Could not initialize DropTarget for View\n");
		// no target, no Drag'n Drop
	}
#endif // !_OLD_DRAGNDROP

	try {
	// Liste der DatenBasisObjekte bilden
		m_pDBOs = new CDBOArray;

	// HintergrundBrush bilden und aktivieren        
		_IrisBGBrush = new Brush (Color ((Colors)192,(Colors)192,(Colors)192));
		_emptyBrush = new Brush (HollowBrush);
		ChangeBackground (_IrisBGBrush);        // Hintergrund setzen

	// Fenster an Frame anpassen (Größe)
	// ...
	//	CanvasErase();							// Fenster löschen

	// entsprechend Vorgaben Dokument eröffnen bzw. erzeugen
	bool fResult = true;

		if (NULL == pcDBName)
			fResult = CreateNewGeoDB (gfMode);
		else
			fResult = (EC_OKAY == OpenDB (pcDBName, pcUserName, pcPassWord, gfMode, dwMode));
		if (!fResult) return false;

	 // wurde wirklich geöffnet
		TX_ASSERT(m_pDBOs -> Count() && DBO().DB().isOpened());

		pFrame -> InitProjectMenu();			// Menu auf Dokument einstellen

	} catch (bad_alloc) {
		return false;
	}

	m_fCleanedUp = false;		// erfolgreich initialisiert
	return true;
}

// Konstruktor für Hauptfenster
IrisWind :: IrisWind (ExtDirisWindow *pFrame)
		  : ChildAppWindow (pFrame, ID_TRIASVIEW_GEODB, (LPSTR)g_cbViewClass,
							IsWin40() ? WS_EX_CLIENTEDGE : 0)
{
//	EnableBorder (NonSizingBorder);
	m_pPD = NULL;
	m_pDBOs = NULL;
	_IrisBGBrush = NULL;
	_emptyBrush = NULL;

// Flags initialisieren
	m_fFirstDrawing = false;
	m_fFullRedrawOnScroll = false;
	m_fHandleCancelMode = false;
	m_fReReadCaption = false;
	m_fCommitOnClose = false;
	m_fCleanedUp = true;		// don't send notification on failure
	m_fPreventRepaint = false;

	m_iDrawSem = 0;
	m_lLastIdent = -1L;
		
// sonstige lokale Parameter initialisieren
	m_fRePaintFlag = false;

	m_pWVS = EnableVScroll();				// ScrollBars initialisieren
	m_kSX = 1;
	m_pWHS = EnableHScroll();
	m_kSY = 1;

	DRO = NULL;                             // DragRechteck initialisieren
	m_pPrinter = NULL;						// derzeit kein Printer aktiv

	AspectRatio = GetAspectRatio();			// AspectRatio bestimmen

// Stack für Vergrößerungen initialisieren
ObjContainer locOC(0, 0, 0, 0);

	actClip.Push (locOC);

	EnableHelp (true, IrisHD);			// Kontextsensitive Hilfe erlauben

#if !defined(_OLD_DRAGNDROP)
// Drag'n Drop
	m_fIsDropSource = false;
	m_pDropTgt = NULL;
#else
// Dragging initialisieren
	DragAcceptFiles (Handle (API_WINDOW_HWND), true);
#endif // _OLD_DRAGNDROP
}

// Destruktor 
IrisWind :: ~IrisWind (void) 
{
	CleanUpView();

	DELETE (m_pPD);
	DELETE (m_pDBOs);		// DatenBasisObjekt(e) freigeben
	DELETE (_IrisBGBrush);	
	DELETE (_emptyBrush);
	if (hPalette != NULL) {
		DeleteObject (hPalette); hPalette = NULL;
	}
}

#if !defined(_OLD_DRAGNDROP)
// Die folgende Funktion ist nicht inline, da ExtDirisWindow nicht 
// global bekannt ist
bool IrisWind::IsDropSourceInst (void)
{ 
	return ((ExtDirisWindow *)GetParent())->IsDropSource(); 
}
#endif // _OLD_DRAGNDROP

// Initialisierungen der FensterKlasse (Menu etc.) ----------------------------
// Menu wird initialisiert ----------------------------------------------------
void IrisWind :: MenuInit (MenuInitEvt e) 
{
	if (!g_fMenu) return;

// MenuPunkte vom FloatingMenu aktivieren
	if (InitTextObjectMenu()) return;

// Neu zeichnen/Abbrechen einstellen (MenuPunkt IDM_DRAW verändern)
pMenu pM = e.GetMenu();

	TX_ASSERT(NULL != pM);

HMENU hMenu = pM -> Handle(API_MENU_HMENU);
	
// Menupunkt auf Abbrechen/Neuzeichnen setzen
	ModifyMenu (hMenu, IDM_DRAW, MF_BYCOMMAND, IDM_DRAW, 
				ResString (m_iDrawSem > 0 ? IDS_CANCELDRAW : IDS_DRAW, 25));

// Checkmarks verteilen, nur wenn IrisMenu aktiv ist
DatenBasisObjekt &rDBO = DBO();
bool ifRO = !DEX_GetROMode();

	MenuEnable (pM, IDM_EDITHEADER, ifRO && EditHeaderEFlag);  // Header editieren
	MenuEnable (pM, IDM_DRAW, DrawEFlag);           // Geometrie zeichnen
	MenuEnable (pM, IDM_SELOBJ, ifRO && IdentSelEFlag);     // Id-Selektion

	MenuEnable (pM, IDM_PRINT, PrintEFlag);         // Drucken

#if !defined(_DEBUG)
	MenuEnable (pM, IDM_COPYTOCLIPBOARD, DRO != NULL);
#endif // !_DEBUG

	MenuCheck (pM, ID_GEOVIEW_PREVENT_REPAINT, m_fPreventRepaint);           // Neuzeichnen unterbinden
	MenuCheck (pM, IDM_LEGENDE, LegendeCFlag);	// Legende
	MenuCheck (pM, IDM_OVERVIEW, OverViewCFlag);	// GesamtÜbersicht

	MenuEnable (pM, IDM_TEXT, GetGeoDBVersion() >= NEWDBVERSION);
	MenuEnable (pM, IDM_VISTEXTOBJ, GetGeoDBVersion() >= NEWDBVERSION);
	MenuCheck (pM, IDM_VISTEXTOBJ, DrawTextObjs && GetGeoDBVersion() >= NEWDBVERSION);

	MenuEnable (pM, IDM_EXPORT, g_fFilters);	// Export erlauben
	MenuEnable (pM, IDM_COORDMODE, rDBO.pCT() -> CanConfig());

	if (GetGeoDBVersion() >= VERSION05000008) {
	ObjContainer OC (0, 0, 0, 0);

		MenuEnable (pM, IDM_SELSICHTCONT, ifRO);
		MenuEnable (pM, IDM_DELSICHTCONT, 
			ifRO && rDBO.GetActSichtCont(&OC) == EC_OKAY);

	// sind wir noch in der AnfangsVergrößerung
	bool iFlag = IsInitialContainer (OC);

		MenuEnable (pM, IDM_PREVSELAUSSCHNITT, iFlag);
		MenuEnable (pM, IDM_RESTOREVIEWCONTAINER, iFlag);
	} else {
		MenuEnable (pM, IDM_SELSICHTCONT, false);
		MenuEnable (pM, IDM_DELSICHTCONT, false);
		MenuEnable (pM, IDM_PREVSELAUSSCHNITT, actClip.Top().isValid());
	}

// alle anderen vom ROMode abhängigen Items behandeln
	MenuEnable (pM, IDM_DELETEVIEWS, ifRO);
	MenuEnable (pM, IDM_SAVEOPT, ifRO);
	MenuEnable (pM, IDM_SAVEDB, rDBO.DB().isDirty());
	MenuEnable (pM, IDM_DELETEIDENTS, ifRO);
	MenuEnable (pM, IDM_MODIFYIDENTS, ifRO);
	
// wenn CompoundFile, dann SaveAs aktiv
	MenuEnable (pM, IDM_SAVEAS, rDBO.isComFile());
	MenuEnable (pM, IDM_SAVECOPYAS, rDBO.isComFile());
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob Ausschnitt der Anfangsvergrößerung entspricht
bool IrisWind::IsInitialContainer (ObjContainer &rOC)
{
bool fResult = false;

	if (rOC.isValid()) {
	ObjContainer ocT = actClip.Top();
		
		if (rOC >= ocT)
			fResult = true;
		else if (rOC < ocT) {
			if (rOC > DBO().GetExtend()) 
				fResult = true;
		} else
				fResult = true;
	} else 
		fResult = true;

return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// Aktuellen Bildausschnitt im Overview Fenster anzeigen
bool IrisWind::InitOverView (ObjContainer &rOC)
{
	if (OverViewCFlag && pOverView) {
	ObjContainer ocT1 = DBO().DB().DBCont();

	// Selektion immer dann anzeigen, wenn Rechteck kleiner als DBRect ist und
	// sich mit DBRect überschneidet
		if (rOC ^ ocT1 && 
			(rOC.Breite() < ocT1.Breite() || rOC.Hoehe() < ocT1.Hoehe()))
		{
		Rectangle rcC = CanvasRect();
		ObjContainer OC = (Rectangle &)rcC;

			pOverView -> SetActVP (OC);
		} else
			pOverView -> ResetActVP();
	}

return true;
}

// Menukommandos verarbeiten --------------------------------------------------
void IrisWind :: MenuCommand (MenuCommandEvt e) 
{
	BEGIN_COMMANDS(e) 
		ON_COMMAND_ID(IDM_BACKGRNDCOLOR, doChangeBKColor);	// Hintergrundfarbe vorgeben (E_NOTIMPL)
		ON_COMMAND_ID(IDM_SAVEDB, doSaveDB);				// GeoDB speichern
		ON_COMMAND_ID(IDM_SAVEAS, doSaveAsGeoDB);			// Speichern unter
		ON_COMMAND_ID(IDM_SAVECOPYAS, doExportAsGeoDB);		// Kopie Speichern als
		ON_COMMAND_ID(IDM_EDITHEADER, doEditHeader);		// GeoDB-Header editieren
		ON_COMMAND_ID(IDM_SELOBJ, doShowIdentSel);			// Ansicht definieren
		ON_COMMAND_ID(IDM_DELETEVIEWS, doDeleteViews);		// Ansichten löschen
		ON_COMMAND_ID(IDM_REBUILD, doRebuild);				// Ansicht neu generieren
		ON_COMMAND_ID(IDM_DRAW, doDraw);					// neu Zeichnen
		ON_COMMAND_ID(ID_GEOVIEW_PREVENT_REPAINT, doPreventRepaint);	// neu Zeichnen unterbinden
		ON_COMMAND_ID(IDM_CANCEL, doCancel);				// allgemeiner Abbruch
		ON_COMMAND_ID(IDM_PRINT, doPrint);					// Drucken
		ON_COMMAND_ID(IDM_TEXTSEARCH_PP, doTextRech);		// RechercheParameter einstellen
		ON_COMMAND_ID(IDM_GENTEXTOBJECTS, doGenTextObjects);		// Textobjekte erzeugen
#if defined(OLD_COORDS)
		ON_COMMAND_ID(IDM_COORDS, doCoords);				// KoordiantenFenster anzeigen/ausblenden
#endif // OLD_COORDS
#if defined(OLD_MASSTAB)
		ON_COMMAND_ID(IDM_MASSTAB, doSelectMasstab);		// Ausschnit über Maßstab wählen
#endif // OLD_MASSTAB
		ON_COMMAND_ID(IDM_SAVEOPT, doSaveOpt);				// SpeicherOptionen auswählen
		ON_COMMAND_ID(IDM_EXPORT, doExport);				// Daten exportieren
		ON_COMMAND_ID(IDM_SYMBOLPARS, doSymbolPars);		// Darstellungsparameter vorgeben
		ON_COMMAND_ID(IDM_PRIORITYSELECT, doPriority);		// Darstellungspriorität vorgeben
		ON_COMMAND_ID(IDM_COPYTOCLIPBOARD, doCopyClipBoard);	// ZwischenAblage bedienen
		ON_COMMAND_ID(IDM_SELSICHTCONT, doSelSichtCont);	// SichtAusschnitt vorgeben
		ON_COMMAND_ID(IDM_DELSICHTCONT, doDelSichtCont);	// Sichtausschnitt wieder löschen
		ON_COMMAND_ID(IDM_LEGENDE, doLegende);				// Legende anzeigen/ausblenden
		ON_COMMAND_ID(IDM_OVERVIEW, doOverView);			// Übersicht anzeigen/ausblenden
		ON_COMMAND_ID(IDM_VISTEXTOBJ, doViewTexts);			// Textobjekte anzeigen/nicht anzeigen
		ON_COMMAND_ID(IDM_SELAUSSCHNITT, doSelAusschnitt);	// Ausschnitt auswählen
		ON_COMMAND_ID(IDM_PREVSELAUSSCHNITT, doPrevAusschnitt);	// vorhergehenden Ausschnitt wieder einstellen
		ON_COMMAND_ID(IDM_SELECTVIEWS, doSelectView);		// Ansicht über Dialog auswählen
		ON_COMMAND_ID(IDM_SIGHTS+MAXSHOWNVIEWS, doSelectView);
		ON_COMMAND_ID(IDM_ZOOMOUT, doZoomOut);				// Ausschnitt vergrößern
		ON_COMMAND_ID(IDM_ZOOMIN, doZoomIn);				// Ausschnitt verkleinern
		ON_COMMAND_ID(IDM_RESTOREVIEWCONTAINER, doRestoreContainer);	// Ausschnitt auf Anfangszustand setzen
		ON_COMMAND_ID(IDM_SELECTIDENTS, doSelIdents);		// Objekte über Idents auswählen 
		ON_COMMAND_ID(IDM_DELETEIDENTS, doDelIdents);		// Objekte über Idents löschen
		ON_COMMAND_ID(IDM_MODIFYIDENTS, doModIdents);		// Objekte über Idents umklassifizieren
		ON_COMMAND_ID(IDM_COPYOBJECTS, doCopyObjectsIdent);		// Objekte über Idents doppeln
		ON_COMMAND_ID(IDM_DEFAULTVIEW, doCopyColors);		// Farben in andere Sicht übernehmen
		ON_COMMAND_ID(IDM_COORDMODE, doCoordMode);			// Parameter der Koordinateneinstellung vorgeben

		ON_COMMAND(IDM_CREATETEXTOBJ, doHandleTextObjectMenu, e);	// Befehl aus TextObjektMenu
		ON_COMMAND(IDM_DELETETEXTOBJ, doHandleTextObjectMenu, e);
		ON_COMMAND(IDM_EDITTEXTOBJ, doHandleTextObjectMenu, e);
		ON_COMMAND(IDM_CREATEBREL, doHandleTextObjectMenu, e);
		ON_COMMAND(IDM_DELETEBREL, doHandleTextObjectMenu, e);
		ON_COMMAND(IDM_ADDTOLEGEND, doHandleTextObjectMenu, e);
#if defined(OLD_TOOLBOX)
		ON_COMMAND(IDM_TOOLS, doTools, e);					// Werkzeugfenster anzeigen bzw. verstecken
#endif // OLD_COORDS

#if !defined(NOPROJEKTION)
		ON_COMMAND_ID(IDM_GEOGRAPH, doResetPrj);			// Geografische Koordinaten anzeigen
		ON_COMMAND_ID(IDM_WORLD, doWorldPrj);				// Weltprojektion anzeigen
#endif

		DEFAULT_COMMANDS(doDefaultCmd, e);					// alles sonstige
	END_COMMANDS;
}


// EventHandlerRoutine für SessionEnde ----------------------------------------
ErrCode CantCloseWhenDrawing (Window *pW);

bool IrisWind::myQueryClose (bool) 
{
	m_fCommitOnClose = false;

	DEX_SaveLegend();

bool fCommitOnClose = false;
ErrCode EC = AskUserToClose (fCommitOnClose);

	m_fCommitOnClose = fCommitOnClose ? true : false;
	if (EC_OKAY != EC)
		return false;	// Abbrechen oder Fehler

	{	// dieses Fenster nun auch schließen
	Event eClose;

		eClose.Msg() = WM_CLOSE;
		eClose.WParam() = 0L;
		eClose.LParam() = 0L;
		ForwardEvent (eClose);
	}

return true;
}

void IrisWind::Close (Event e)
{
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) 		// DB noch eröffnet
	{
	// Projekt schließen
		if (EC_OKAY != CloseDB (m_fCommitOnClose))
			return;

	// Frame wieder in Ausgangszustand versetzen
		GetFrame() -> RestoreStartConfig();
	} 
	CleanUpView();
}


typedef struct tagADDOBJECTDATA {
	ObjNummerCreator *m_pcrON;
	short m_iOTyp;
} ADDOBJECTDATA;

extern "C" 
bool EXPORTTRIAS WINAPI AddObjectsCallback (long lONr, short iOTyp, void *pData)
{
ObjNummerCreator *pObjs = ((ADDOBJECTDATA *)pData) -> m_pcrON;

	if (!(iOTyp & (((ADDOBJECTDATA *)pData) -> m_iOTyp)))
		return true;	// interessiert nicht
	
	return ContCreate (*pObjs, ObjNummer)(lONr) != NULL;
}


bool AddObjects (ObjFeld &rObjs, long lIdent, short iOTyp)
{
ObjNummerCreator crON (rObjs);
ADDOBJECTDATA AOD;

	AOD.m_pcrON = &crON;
	AOD.m_iOTyp = iOTyp;
	
ENUMLONGKEY ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYPROC)AddObjectsCallback;
	ELK.ePtr = &AOD;

return DEX_EnumIdentObjects (ELK);
}


// Darstellungsparameter einzelner(aller) Idents in andere Ansicht durchschreiben
bool IrisWind :: DefineDefaultView (void)
{
CCopyVisInfoDlg *pDlg = CCopyVisInfoDlg :: CreateInstance (this, 
				IDD_COPYVISINFODLG, IDL_IDENTSLIST);
	if (pDlg == NULL) return false;
	pDlg -> Show (Centre);

char cbView[64];

	if (pDlg -> Result() && pDlg -> GetViewName (cbView, sizeof(cbView))) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	CTable t(DBO().Idents().IdentTree());	// Navigator für Sicht
	VisInfo *pVI[4];
	long lIdent = -1L;
	short iOTyp = 0;
	Sicht S (DBO().DB(), cbView);
		
		memset (pVI, '\0', 4 * sizeof(VisInfo *));
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
			// beim ersten mal sinnlos
				DELETE(pVI[0]);
				DELETE(pVI[1]);
				DELETE(pVI[2]);
				DELETE(pVI[3]);

			// Farben aus aktuellen Sicht lesen
				if (t.Find(&lIdent)) {
				// VisInfo aus Speicher holen
				CIdentifikatorLock l(t);

					if (!l) continue;
					l -> GetCompleteVisInfo ((VisInfo **)pVI, iOTyp);
				}
			
			// Farben in geforderte Sicht wegschreiben
				if (pDlg -> isDefaultView()) {
				// wenn DefaultSicht, dann immer durchschreiben
					if (S.SetCompleteVisInfo (lIdent, (VisInfo **)pVI, iOTyp) != EC_OKAY)
						break;
				} else {
				ErrInstall WC (WC_NOTFOUND);	// not found Fehler expected
				ErrCode EC = S.GetIDfromSight (lIdent, NULL, VMskToVTyp (iOTyp, TPAll));
				
					if (EC != EC_OKAY && EC != WC_RETURN)
						continue;	// keine Idents hinzufügen
					if (S.SetCompleteVisInfo (lIdent, (VisInfo **)pVI, iOTyp) != EC_OKAY)
						break;
				}
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));

		// wieder alles freigeben
			DELETE(pVI[0]);
			DELETE(pVI[1]);
			DELETE(pVI[2]);
			DELETE(pVI[3]);
		}
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// RegNumber auf Gültigkeit testen
bool IsLegalRegNumber (LPCSTR pcRegEntry);

bool IsLegalRegisteredVersion (Window *pW)
{
#if !defined(_DEBUG)
	if (DEX_QueryMode() & QMSysAdmin)
		return true;

CLocalMachine regName (g_cbRegVersion);
char cbBuffer[128];
DWORD dwLen = sizeof(cbBuffer);

	if (!regName.GetSubSZ (g_cbSerial, cbBuffer, dwLen) ||
		!IsLegalRegNumber (cbBuffer)) 
	{
		VMessageBox (pW, IDS_SHORTCAPTION, ExclamationIcon|OkayButton, 
					 IDS_CANTDOTHAT, g_cbTRiAS);
		return false;
	}
#endif // !_DEBUG

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// MenuKommandos

// Projekt speichern ----------------------------------------------------------
bool IrisWind :: doSaveDB (void)
{
	if (!IsLegalRegisteredVersion(this))
		return false;

	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {	// GeoDB eröffnet
		if (DBO().DB().GetTempMode())	// erstes Speichern überhaupt
			return SaveAsGeoDB();
		else 
			return SaveGeoDB();
	}

return false;
}

// Speichern unter ------------------------------------------------------------
bool IrisWind :: doSaveAsGeoDB (void)
{
	if (!IsLegalRegisteredVersion(this))
		return false;

	return SaveAsGeoDB();
}

// Kopie Speichern als --------------------------------------------------------
bool IrisWind :: doExportAsGeoDB (void)
{
	if (!IsLegalRegisteredVersion(this))
		return false;

	return ExportAsGeoDB();
}

// Projekt Eigenschaften ------------------------------------------------------
bool IrisWind :: doEditHeader (void) 
{
	if (ShowEditHeader()) {
		DEX_ReReadCaption();		// evtl. Caption neu generieren
		return true;
	}

return false;
}

// Ansichten zusammenstellen --------------------------------------------------
bool IrisWind :: doShowIdentSel (void) 
{
	return ShowIdentSel();
}

// Ansichten löschen ----------------------------------------------------------
bool IrisWind :: doDeleteViews (void) 
{
	if (DeleteViews()) {
		DEX_ReReadCaption();		// evtl. Caption neu generieren
		return true;
	}

return false;
}

// Ansicht neu generieren -----------------------------------------------------
bool IrisWind :: doRebuild (void)
{
CEierUhr Wait (this);

	DBO().ProcessMenuEvent (NULL, true);
	m_fRePaintFlag = true;

// jetzt zeichnen
CScopeVar<bool> PreventRePaint (m_fPreventRepaint,  false);

	RePaint();
	
// jetzt aktualisieren, wenn nur einmalig gezeichnet wird
	if (PreventRePaint.GetOldValue())
		Update();

// OverView auch neu zeichnen
	if (OverViewCFlag && pOverView) 
		pOverView -> RePaint();

	return true;
}

// Ansicht neu Zeichnen -------------------------------------------------------
bool IrisWind :: doDraw (void)
{
	if (m_iDrawSem > 0) {	
	// es wird gerade gezeichnet: Abbrechen
		GCancelFlag = GCFAbort;
	} else {
	CEierUhr Wait (this);

	// wenn CTRL-Taste gedrückt, dann Sicht neu einlesen
		if (GetKeyState (VK_CONTROL) < 0) {
		CEierUhr Wait (this);
			
			DBO().ProcessMenuEvent (NULL, true);
		}
		m_fRePaintFlag = true;

	// jetzt zeichnen
	CScopeVar<bool> PreventRePaint (m_fPreventRepaint,  false);

		RePaint();

	// jetzt aktualisieren, wenn nur einmalig gezeichnet wird
		if (PreventRePaint.GetOldValue())
			Update();

	// Übersichtsfenster
//		if (OverViewCFlag && pOverView) 
//			pOverView -> RePaint();
	}

return true;
}

/////////////////////////////////////////////////////////////////////////////
// Neuzeichnen unterbinden
bool IrisWind::doPreventRepaint()
{
	m_fPreventRepaint = !m_fPreventRepaint;
	return true;
}

// Allgemeiner Abbruch --------------------------------------------------------
bool IrisWind :: doCancel (void)
{
	GCancelFlag = GCFAbort;
	return true;
}

// ToolFenster anzeigen/ausblenden --------------------------------------------
bool IrisWind :: doTools (MenuCommandEvt e) 
{
#if defined(OLD_TOOLBOX)
	if (NULL == pToolBox) 
		return false;

	ToolBoxCFlag = !ToolBoxCFlag;
	if (ToolBoxCFlag) {
		pToolBox -> Show();
		pToolBox -> Update();
		ValidateWindow ();
	} else
		pToolBox -> Hide();

return true;
#else
return false;
#endif // OLD_TOOLBOX
}

// Aktuelles Projekt drucken --------------------------------------------------
bool IrisWind :: doPrint (void)
{
	if (!IsLegalRegisteredVersion(this))
		return false;

char cbCaption[_MAX_PATH] = "";

	GetFrame() -> GetCaption (cbCaption, sizeof(cbCaption)-1);

	if (NULL != DRO && 
		((DragRectangleObject *)(DrawObject *)(*DRO)) -> isValid ()) 
	{
	// Ausschnitt ist selektiert: Koordinaten transformieren
	Point pt1 = ((DragRectangleObject *)DRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)DRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);

		return PrintGraphics (cbCaption, ObjContainer(pnt1, pnt2));
	} else {
	// aktuellen Bildschirmausschnitt verwenden
		return PrintGraphics (cbCaption, DBO().GetExtend());
	}
}

// RechercheParameter einstellen ----------------------------------------------
bool IrisWind :: doTextRech (void)
{
	return TextRecherche(Handle(API_WINDOW_HWND));
}

/////////////////////////////////////////////////////////////////////////////
// Textobjekte erzeugen
bool IrisWind::doGenTextObjects (void)
{
	return GenerateTextObjects(Handle(API_WINDOW_HWND));
}

// KoordiantenFenster anzeigen/ausblenden -------------------------------------
bool IrisWind :: doCoords (void)
{
#if defined(OLD_COORDS)
	CoordsCFlag = !CoordsCFlag;
	if (CoordsCFlag) {
		if (!pCoords) {   
			pCoords = new CoordsDlg (this, DBO().pCT());
			if (NULL == pCoords) return false;
		}

		pCoords -> Show();      // anzeigen
		SetFocus();             // Focus im Hauptfenster lassen
		ValidateWindow ();      // Kein RePaint 
	} else if (pCoords) {
		pCoords -> Hide();      // nicht mehr anzeigen
		delete pCoords;         // Speicher freigeben
		pCoords = NULL;
	}
	
	return true;
#else
	return false;
#endif // OLD_COORDS
}

#if defined(OLD_MASSTAB)
// Ausschnit über Maßstab wählen ----------------------------------------------
bool IrisWind :: doSelectMasstab (void)
{
	return MenuSelectMasstab();
}
#endif // OLD_MASSTAB

// SpeicherOptionen auswählen -------------------------------------------------
bool IrisWind :: doSaveOpt (void)
{
CSaveOptionsDlg *pSODlg = CSaveOptionsDlg :: CreateInstance (this);

	if (NULL == pSODlg) return false;

	pSODlg -> Show();
	if (pSODlg -> Result()) {
		if (g_iMinutes != pSODlg -> SaveDelta()) {
			if (g_pT) {
				CancelStrobe (g_pT);
				delete g_pT;
				g_pT = NULL;
			}
			g_iMinutes = pSODlg -> SaveDelta();
			if (g_iMinutes > 0) 
				g_pT = new Timer (6000, 2);
			if (g_pT) SetStrobe (g_pT);

			g_iTicks = 0;
		}
	}
	DELETE (pSODlg);

return true;
}

// Daten exportieren ----------------------------------------------------------
bool IrisWind :: doExport (void)
{
	if (!IsLegalRegisteredVersion(this))
		return false;

	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
	ObjContainer OC;

		if (DRO != NULL) {	// nur selektierten Bereich
		Point pt1 = ((DragRectangleObject *)DRO)->LowerLeft();
		Point pt2 = ((DragRectangleObject *)DRO)->UpperRight();
		Punkt pnt1 = DCtoOC (pt1);
		Punkt pnt2 = DCtoOC (pt2);

			OC = ObjContainer (pnt1, pnt2);
			return (EC_OKAY == DBO().doExport (this, &OC));
		} else if (actClip.Top().isValid()) {
		// aktueller Bildausschnitt
		Rectangle rcT = CanvasRect();
		
			OC = rcT;
			return (EC_OKAY == DBO().doExport (this, &OC));
		} else
			return (EC_OKAY == DBO().doExport (this));	// gesamte DB
	}

return false;
}

// HinterGrundfarbe einstellen ------------------------------------------------
bool IrisWind :: doChangeBKColor (void)
{
	return true;		// E_NOTIMPL
}

// Darstellungsparameter vorgeben ---------------------------------------------
bool IrisWind :: doSymbolPars (void)
{
// neu zeichnen abbrechen, wenn neuer Dialog erzeugt wird
bool fResult;

	m_fHandleCancelMode = true;
	fResult = (EC_OKAY == ChangeIdVisInfo());
	m_fHandleCancelMode = false;

return fResult;
}

// Darstellungspriorität vorgeben ---------------------------------------------
bool IrisWind :: doPriority (void)
{
char cbBuffer[SIGHTMENUITEM+1];

	DBO().GetActiveSightName(cbBuffer, sizeof(cbBuffer));
	return doPrioritySelect (this, DBO().Idents(), cbBuffer);
}

// ZwischenAblage bedienen ----------------------------------------------------
bool IrisWind :: doCopyClipBoard (void)
{
	if (DRO != NULL) {
	// selektierten Bereich kopieren
	Rectangle Rc = ((DragRectangleObject *)(DrawObject *)(*DRO)) -> GetRect();

		return (EC_OKAY == CopyToClipBoard (this, Rc));
	} else {
	// gesamten Bildschirmbreich kopieren
	Rectangle Rc = CanvasRect();
	CoOrd tmpC = CoOrd(Rc.Bottom() - Rc.Top());			// Koordinaten kippen
	
		Rc.Bottom() = CoOrd(Rc.Top() - tmpC);
		return (EC_OKAY == CopyToClipBoard (this, Rc));
	}

return false;
}

// SichtAusschnitt vorgeben ---------------------------------------------------
bool IrisWind :: doSelSichtCont (void)
{
	if (DRO != NULL && ((DragRectangleObject *)(DrawObject *)(*DRO)) -> isValid ()) {
	// Ausschnitt ist selektiert: Koordinaten transformieren
	Point pt1 = ((DragRectangleObject *)DRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)DRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);
	ObjContainer OC (pnt1, pnt2);

		OC.InflateCont (10);	// Container anpassen
		return (EC_OKAY == DBO().SetActSichtCont (OC));
	} else {
	// aktuellen Bildschirmausschnitt verwenden
		return (EC_OKAY == DBO().SetActSichtCont (DBO().GetExtend()));
	}
}

// Sichtausschnitt wieder löschen ---------------------------------------------
bool IrisWind :: doDelSichtCont (void)
{
	return (EC_OKAY == DBO().DelActSichtCont());
}

// Legende anzeigen/ausblenden ------------------------------------------------
bool IrisWind :: doLegende (void)
{
	LegendeCFlag = !LegendeCFlag;
	if (LegendeCFlag) {
	char cbCaption[SIGHTMENUITEM +1];

		if (!pLegende) {
			DBO().GetActiveSightName (cbCaption, sizeof(cbCaption));
			pLegende = CLegendeWindow :: CreateInstance (this, cbCaption, DBO());
		}
		if (pLegende == NULL)
			return false;
			
		DEX_KickIdle();
		pLegende -> Show (ShowState(Normal|NoActivate));	// anzeigen
		LegendToRepaint = false;
//		SetFocus();             // Focus im Hauptfenster lassen
//		ValidateWindow ();      // Kein RePaint 
	} else if (pLegende) {
		pLegende -> SaveLegend();	// Legende Speichern
		pLegende -> Hide();      // nicht mehr anzeigen
		LegendToRepaint = false;
		delete pLegende;         // Speicher freigeben
		pLegende = NULL;
	}

return true;
}

// Übersicht anzeigen/ausblenden ----------------------------------------------
bool IrisWind :: doOverView (void)
{
	if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened()) 
		return false;

	OverViewCFlag = !OverViewCFlag;
	DELETE (pOverView);				// für alle Fälle

	if (OverViewCFlag) {
	ObjContainer OC = DBO().DB().DBCont();
	// bei ControlTaste Overview neu generieren
	bool fInitNew = (GetKeyState (VK_CONTROL) < 0) ? true : false;
	double dRatio = DBO().pCT() -> CoordTransAspectRatio (OC);

		pOverView = COverView::CreateOverView (this, OC, fInitNew, AspectRatio, dRatio);
		if (pOverView) {
 			if (DBO().GetExtend() < OC) {
			Rectangle rcC = CanvasRect();
			ObjContainer OC = (Rectangle &)rcC;
		
				pOverView -> SetActVP (OC);
			} else
				pOverView -> ResetActVP();
		}
		ValidateWindow ();      // Kein RePaint 
	}

return true;
}

// Textobjekte anzeigen/nicht anzeigen ----------------------------------------
bool IrisWind :: doViewTexts (void)
{			
	DrawTextObjs = !DrawTextObjs;
	RePaint();			// alles neu zeichnen

return true;
}

// Ausschnitt auswählen -------------------------------------------------------
bool IrisWind :: doSelAusschnitt (void)
{
CAusschnittsDlg *pADlg = new CAusschnittsDlg (this, DBO().pCT(), DBO().DotsPerMM());
Rectangle Rc (0, 0, 0, 0);

	if (DRO) Rc = ((DragRectangleObject *)DRO) -> GetRect();
	
	if (pADlg && pADlg -> Init (DRO ? &Rc : NULL)) {
		pADlg -> Show(Centre);
		if (pADlg -> Result()) {	// richtige Eingabe ist erfolgt
		// alten Ausschnitt merken
			actClip.Push (DBO().GetExtend());
		
		// neuen Ausschnitt einstellen
		ObjContainer ocT = pADlg -> NewRect();
		
			DBO().SetExtend (this, ocT, AspectRatio);
			DELETE (DRO);

			InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
			InitOverView (ocT);		// Übersichtsfenster

		// neu zeichnen
			LegendToRepaint = true;
			m_fRePaintFlag = true;
			RePaint ();
		}
		delete pADlg;
		return true;
	}
	DELETE (pADlg);

return false;
}

// vorhergehenden Ausschnitt wieder einstellen --------------------------------
bool IrisWind :: doPrevAusschnitt (void)
{
	if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened())
		return false;

	if (actClip.Top().isValid()) {  // gültiger Ausschnitt
	// vorhergehenden Ausschnitt einstellen
	ObjContainer OC (0, 0, 0, 0);
	ObjContainer ocT (0, 0, 0, 0);
	
		if (DBO().GetActSichtCont (&OC) == EC_OKAY && 
			OC.isValid()) 
		{
			ocT = actClip.Top();
			if (OC > ocT) {
				actClip.Pop();
				DBO().SetExtend (this, ocT, AspectRatio);
			} else if (OC < ocT) {
				if (OC > DBO().GetExtend()) 
					DBO().SetExtend (this, OC, AspectRatio);
				else
					return false;
			} else {
				actClip.Pop();
				DBO().SetExtend (this, ocT, AspectRatio);
			}
		} else {
		// vorhergehenden Ausschnitt einstellen
			ocT = actClip.Pop();
			DBO().SetExtend (this, ocT, AspectRatio);
		}

		InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
		InitOverView (ocT);		// Übersichtsfenster

	// neu zeichnen
		m_fRePaintFlag = true;
		LegendToRepaint = true;
		RePaint ();
	}

return true;
}

// Ansicht über Dialog auswählen ----------------------------------------------
bool IrisWind :: doSelectView (void)
{
	return SelectView();
}

// Halber Bildschirmausschnitt ------------------------------------------------
bool IrisWind :: doZoomOut (void) 
{
	if (m_pDBOs -> Count() == 0 || !DBO().DB().isOpened()) 
		return false;

// wenn Ctrl gedrückt, dann vollständig zurücksetzen
	if (GetKeyState (VK_CONTROL) < 0)
		return doRestoreContainer();

ObjContainer OC = DBO().GetExtend();

	if (OC.isValid()) {
	// Bildschirmausschnitt halbieren
	KoOrd dX = (OC.XMax() - OC.XMin())/2;
	KoOrd dY = (OC.YMax() - OC.YMin())/2;
	ObjContainer ocT (OC.XMin() - dX, OC.XMax() + dX, OC.YMin() - dY, OC.YMax() + dY);
		
		DBO().SetExtend (this, ocT, AspectRatio);	// neuen Ausschnitt setzen		
			
		InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
		InitOverView (ocT);		// Übersichtsfenster

	// neu zeichnen
		m_fRePaintFlag = true;
		LegendToRepaint = true;
		RePaint ();
		return true;
	}

return false;
}

// Doppelter Bildschirmausschnitt ---------------------------------------------
bool IrisWind :: doZoomIn (void)
{
	if (m_pDBOs -> Count() == 0) return false;

ObjContainer OC = DBO().GetExtend();

	if (OC.isValid()) {
	// Bildschirmausschnitt halbieren
	KoOrd dX = (OC.XMax() - OC.XMin())/4;
	KoOrd dY = (OC.YMax() - OC.YMin())/4;
	ObjContainer ocT (OC.XMin() + dX, OC.XMax() - dX, OC.YMin() + dY, OC.YMax() - dY);
		
		if (!ocT.isValid()) return false;
		
		DBO().SetExtend (this, ocT, AspectRatio);	// neuen Ausschnitt setzen		
	
		InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
		InitOverView (ocT);		// Übersichtsfenster

	// neu zeichnen
		m_fRePaintFlag = true;
		LegendToRepaint = true;
		RePaint ();
		return true;		// alles ok
	}

return false;
}

///////////////////////////////////////////////////////////////////////////////
// BildAusschnitt auf Anfangswert zurücksetzn
bool IrisWind :: doRestoreContainer (void)
{
// ObjContainerStack rücksetzen
	while (actClip.Top().isValid())
		actClip.Pop();

// DatenBasisObjekt Ausschnitt definieren
DatenBasisObjekt &rDBO = DBO();
ObjContainer ocT = rDBO.DB().DBCont(true).InflateCont(10);

	rDBO.SetExtend (this, ocT, AspectRatio);

	if (rDBO.GetActSichtCont (&ocT) == EC_OKAY && ocT.isValid())
		DEX_SetActiveSightContainer (ocT); 

	InitWndScrollBars();	// bei Bedarf ScrollBars einblenden und initialisieren
	InitOverView(ocT);		// Übersichtsfenster

// neu zeichnen
	m_fRePaintFlag = true;
	LegendToRepaint = true;
	RePaint ();

	return true;
}

// Farben in andere Sicht übernehmen ------------------------------------------
bool IrisWind :: doCopyColors (void)
{
	return DefineDefaultView();
}

// Parameter der Koordinateneinstellung vorgeben ------------------------------
extern LRESULT SelectCoordSysParams (pWindow pW, UINT uiID, CoordTrans * = NULL);

bool IrisWind :: doCoordMode (void)
{
	return SelectCoordSysParams (this, IDS_COORDFMTDLGCAP, NULL);
}

// Alles sonstige landet hier -------------------------------------------------
bool IrisWind :: doDefaultCmd (MenuCommandEvt e)
{
uint iItemID = e.GetItemID();

#if defined(OLD_TOOLBOX)
// MenuPunkt für Werkzeugkiste
	if (iItemID >= IDM_ARROW && iItemID < IDM_ARROW + 50) {
		if (pToolBox) 
			pToolBox -> SetTool (iItemID-IDM_ARROW);
		return true;
	}
#endif // OLD_TOOLBOX

// evtl. AnsichtMenuItem aktiviert
	if (DBO().ProcessMenuEvent (iItemID)) {
		InitWndScrollBars();		// Rollbalken zuschalten
		DEX_ReReadCaption();
		RePaint();					// neue Ansicht zeichnen
		return true;
	}

return false;
}

// Befehl aus TextObjektMenu behandeln ----------------------------------------
bool IrisWind :: doHandleTextObjectMenu (MenuCommandEvt e) 
{
	return HandleTextObjectMenu (e.GetItemID());
}

///////////////////////////////////////////////////////////////////////////////
// ProjektionsFunktionen behandeln
#if !defined(NOPROJEKTION)
bool IrisWind :: doResetPrj (void)
{
// DatenBasisObjekt Ausschnitt definieren
	DBO().SetPrjFcn (NULL, NULL);
	DBO().SetExtend (DBO().DBCont().InflateCont(10), AspectRatio);

// Menupunkte markieren
	GeographicCFlag = true;
	WorldCFlag = false;

return true;
}

bool IrisWind :: doWorldPrj (void)
{
// DatenBasisObjekt Ausschnitt definieren
	DBO().SetPrjFcn (geowel, NULL);
	DBO().SetExtend (DBO().DBCont().InflateCont(10), AspectRatio);

// Menupunkte markieren
	WorldCFlag = true;
	GeographicCFlag = false;

return true;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// RechercheFenster erzeugen
inline POINT lpFcn (OIPOSPROC pFcn, Window *pW, void *pData)
{
	return ((OIPOSCALLBACK)pFcn) (pW, pData);
}

HWND IrisWind :: CreateObjektInfo (
		DEXXCREATEOBJEKTINFO *pcrOI, ExtensionList &rEL)
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
	if (0 == (iFlags & ROHideFlags)) 
		iFlags |= (g_iHideFlags & ROHideFlags);	// globale Voreinstellung
	if (0 == (iFlags & ROSortFlags)) 
		iFlags |= (g_iHideFlags & ROSortFlags);	// globale Voreinstellung
				
ObjektInfo *pOIDlg = ObjektInfo::CreateInstance (
				this, DBO(), rEL, *(ObjFeld *)pcrOI -> lcObjs, 
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
char *pNewCaption = NULL;

	TX_ASSERT(pOIDlg -> m_ulActCount <= pOIDlg -> GetCount());
	try {
	string strT = ObjInfoListe.CorrectCaption (pOIDlg, pcrOI -> lpCaption);

		pNewCaption = new char [strlen (pcrOI -> lpCaption) + 20];
		wsprintf (pNewCaption, "%s (%d/%ld)", strT.c_str(),
			  pOIDlg -> m_ulActCount, pOIDlg -> GetCount());
		pOIDlg -> SetCaption (pNewCaption);

	} catch (bad_alloc) {
		pOIDlg -> SetCaption (pcrOI -> lpCaption);
	}
	DELETE(pNewCaption);

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
	if (!(iFlags & ROCreateHidden))
		pOIDlg -> Show ();		// DlgFenster anzeigen
	
	DEXN_RechObjWindowCreated (pOIDlg -> hWnd());	// die Welt informieren
	return pOIDlg -> hWnd();
}

HWND IrisWind :: CreateObjektInfo (
		CREATEOBJEKTINFO *pcrOI, ExtensionList &rEL)
{
	if (pcrOI == NULL) return NULL;

// ObjektFeld aufbauen, welches vom Fenster erwartet wird
ObjFeld OF;

	{
	ObjNummerCreator ONC (OF);

		for (unsigned short i = 0; i < (unsigned short)pcrOI -> iNumObjs; i++) 
			OF.NewObj (ONC, pcrOI -> plObjs[i]);
	}

short iFlags = 0;
CMPONRPROC pProc = NULL;
DWORD dwData = 0L;
LPUNKNOWN pIUnk = NULL;

	if (pcrOI -> dwSize >= sizeof (CREATEOBJEKTINFOEX)) {
	// wenn Fenster bereits existiert, dann zu diesem hinzufügen
		if (pcrOI -> dwSize == sizeof(CREATEOBJEKTINFOEX2))
			pIUnk = ((CREATEOBJEKTINFOEX2 *)pcrOI) -> m_pIObjProp;

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
	if (0 == (iFlags & ROHideFlags)) 
		iFlags |= (g_iHideFlags & ROHideFlags);	// globale Voreinstellung
	if (0 == (iFlags & ROSortFlags)) 
		iFlags |= (g_iHideFlags & ROSortFlags);	// globale Voreinstellung

ObjektInfo *pOIDlg = ObjektInfo::CreateInstance (
				this, DBO(), rEL, OF, iFlags, pProc, dwData
				, pIUnk	// anzuzeigende Objekteigenschaft
			);
	{
	ObjektInfoCreator Cr(ObjInfoListe);

		if (pOIDlg == NULL) {
			db_error (EC_NOMEMORY, RC_CreateObjektInfo);
			return NULL;
		}
		Cr.InsertPtr (pOIDlg);
	}	// wegspeichern

// Caption setzen, Objektanzahl hinzufügen
char *pNewCaption = NULL;

	TX_ASSERT(pOIDlg -> m_ulActCount <= pOIDlg -> GetCount());
	try {
	string strT = ObjInfoListe.CorrectCaption (pOIDlg, pcrOI -> lpCaption);

		pNewCaption = new char [strlen (pcrOI -> lpCaption) + 20];
		wsprintf (pNewCaption, "%s (%d/%ld)", strT.c_str(),
			  pOIDlg -> m_ulActCount, pOIDlg -> GetCount());
		pOIDlg -> SetCaption (pNewCaption);

	} catch (bad_alloc) {
		pOIDlg -> SetCaption (pcrOI -> lpCaption);
	}
	DELETE(pNewCaption);

// Farbe setzen
	pOIDlg -> SetColor (*(Color *)&pcrOI -> cMColor);

// Dialogfenster positionieren
	pOIDlg -> m_ptWantedPos = pOIDlg -> ChangePosition (*(Point *)&pcrOI -> pntPos);

// Dialogfenster anzeigen
	if (!(iFlags & ROCreateHidden))
		pOIDlg -> Show ();		// DlgFenster anzeigen

	DEXN_RechObjWindowCreated (pOIDlg -> hWnd());	// die Welt informieren
	return pOIDlg -> hWnd();
}

// Zugriff auf aktuellen BildAusschnitt ---------------------------------------
bool IrisWind :: SetActViewContainer (ObjContainer &rOC)
{
	if (!actClip.Top().isValid()) 
	// erster Eintrag: DBCont merken
		actClip.Push (DBO().GetExtend());
	if (DRO != NULL) {
		Draw (*DRO);
		DELETE (DRO);	// evtl. DragObjekt freigeben
	}

	DBO().SetExtend (this, rOC, AspectRatio);

	InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
	InitOverView (rOC);		// Übersichtsfenster

return true;
}

bool IrisWind :: GetActViewContainer (ObjContainer &rOC)
{
	if (DRO != NULL) {
	Point pt1 = ((DragRectangleObject *)DRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)DRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);

		rOC = ObjContainer (pnt1, pnt2);
		return true;
	} else {
	Rectangle rcC = CanvasRect();
		
		rOC = rcC;
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Projektverwaltung
bool IrisWind :: EnumProjects (ENUMNOKEY *pK)
{
CRing r(*m_pDBOs);

	for (r.First(); r.Valid(); ) {
	DatenBasisObjektLock l(r);
	bool fLast = !r.Next();

		TX_ASSERT(NULL != (DatenBasisObjekt *)l);

	string str = l -> DB().GetDBName();

		strupr ((LPSTR)str.c_str());
		if (false == (*(ENUMNOKEYCALLBACK)pK -> eFcn)((char *)str.c_str(), fLast, pK -> ePtr))
			return (LRESULT)false;
	}

return (LRESULT)true;
}

HPROJECT IrisWind :: GetProjectHandle (LPCSTR pcName)
{
CRing r(*m_pDBOs);
string strMatch = pcName;

	strupr((LPSTR)strMatch.c_str());

	for (r.First(); r.Valid(); ) {
	DatenBasisObjektLock l(r);
	bool fLast = !r.Next();

		TX_ASSERT(NULL != (DatenBasisObjekt *)l);

	string str = l -> DB().GetDBName();

		strupr((LPSTR)str.c_str());
		if (str == strMatch)
			return l -> DB().DBDesc();
	}

return NULL;
}

HPROJECT IrisWind :: MakeProjectActive (HPROJECT hPr)
{
	if (0 == m_pDBOs -> Count()) return NULL;

short iIndex = m_pDBOs -> FFindItem (hPr);

	TX_ASSERT(-1 != iIndex);

short iOldIndex = m_pDBOs -> FActivateItem (iIndex);

	TX_ASSERT(-1 != iOldIndex);

return DBO(iOldIndex).DB().DBDesc();
}

///////////////////////////////////////////////////////////////////////////////
// liefert die Höhe des aktuellen AusgabeFensters (Druckers etc.)
CoOrd IrisWind :: GetOutputHeight (void)
{
Rectangle rc = (NULL != m_pPrinter) ? m_pPrinter -> CanvasRect() : CanvasRect();

	return rc.Top() - rc.Bottom();
}

