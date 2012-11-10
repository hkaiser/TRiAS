// IRIS - Mainprogramm -- Version fuer Windows 3.1 ----------------------------
// File: IRISMAIN.CXX

#include "triaspre.hxx"

#include <ole2ver.h>
#if defined(WIN32)
#include <fnamestr.h>
#endif

#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX
#include "coords.hxx"   // Koordinatenanzeige
// #include "about.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#if defined(OLD_MASSTAB)
#include "masstab.hxx"
#endif // OLD_MASSTAB
#include "ausschn.hxx"
#include "saveopt.hxx"
#include "opendb.hxx"
#include "bildobj.hxx"
#include "signon.hxx"
#include "overview.hxx"
#include "selident.hxx"
#include "modident.hxx"
#include "selnview.hxx"

#include <prntpars.hxx>
#include <registry.hxx>

#include "triasres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

short doPrioritySelect (pWindow, CIdTree &, char *);
VisType VMskToVTyp (short iVMsk, short iMsk);
int ShowCreateNewDBDialog (pWindow pW, string &strDBName, string &strUserName, string &strPWD);
HRESULT CreateShortCut (LPCSTR pszShortcutFile, LPCSTR pszLink, LPCSTR pszDesc);
void InitWindowsVersion (void);

//long GetGeoDBVersion (void);		// DB-Version holen

Window *CurrActW = NULL;        // derzeit aktiviertes Fenster dieser Instanz
ExtDirisWindow *CurrActDirisW = NULL;	// derzeit aktives Datenfenster

App *CurrApp = NULL;            // aktuelle Programminstanz
bool Profiling = false;         // Profiler eingeschaltet
short GCancelFlag = GCFNormal;       // General Cancel Flag

// Variablen für die Hilfeverwaltung
HelpDisplay *IrisHD = NULL;
bool wasHelpEvt = false;

ToolWind *pToolBox = NULL;              // Werkzeugkiste
TextRechercheDlg *pTextSearch = NULL;   // TextSuchfenster
CoordsDlg *pCoords = NULL;              // Koordinatenanzeige
CLegendeWindow *pLegende = NULL;	// Legende
MasstabDlg *pMasstab = NULL;		// Maßstabsanzeige
COverView *pOverView = NULL;		// Übersichtsanzeige

#if !defined(WIN32)
NomenklaturDlg *pNomenkl = NULL;        // Nomenklaturanzeige
SchrankSchnulli *pSchrank = NULL;       // Schrankfachanzeige

bool Nomen10CFlag = false;              // NomenklaturTyp
bool Nomen25CFlag = false;
bool Nomen50CFlag = false;
bool SchrankCFlag = false;              // Schrankfachanzeige
#endif // WIN32

// Check-Flags für MenüPunkte
bool ToolBoxCFlag = false;              // Werkzeuge

bool CoordsCFlag = false;               // Koordinatenanzeige
bool CoordsEFlag = false;

bool LegendeCFlag = false;		// Legende angezeigt
bool LegendToRepaint = false;
bool OverViewCFlag = false;

bool PrintEFlag = true;                 // Drucken

bool TextSearchCFlag = false;           // TextRecherche
extern int TextMode;                    // SuchMode TextRecherche
long TextCode = 51100000L;              // SuchCode

bool MasstabCFlag = false;		// Masstabsanzeige

#if !defined(NOPROJEKTION)
bool GeographicCFlag = true;            // geografische Koordinaten
bool WorldCFlag = false;                // Weltprojektion
#endif

bool inzFlag = false;                   // aktuelle DB ist verschnitten

bool DrawTextObjs = true;		// TextObjekte zeichnen

// Enable-Fags für MenuPunkte -------------------------------------------------
bool CloseEFlag = false;                // Projekt schlieáen
bool EditHeaderEFlag = false;           // DB-Header editieren
bool DrawEFlag = false;                 // Geometrie neu zeichnen
bool IdentSelEFlag = false;             // IdentifikatorSelektion

// Timer für Sepichern alle x Minuten
extern short g_iMinutes;
extern short g_iTicks;

short g_iHideFlags = ROSortObjNr|ROHideIdent;	// was soll ausgeblendet werden

short g_iSignOnTicks = 0;
CSignOnDlg *g_pSODlg = NULL;		// SignOnDlg

bool g_fPendingSave = false;		// Speichern muß gemacht werden

Timer *g_pT = NULL;

bool g_fMenu = true;			// Menu's anzeigen
extern bool g_fFilters;			// Exportfilter installiert

// externe Variablen
extern HPALETTE hPalette;			// aktive Farbpalette

// Handle dieser Programminstanz
HINSTANCE hInstance = 0;

// Zentrales Verzeichnis für DQLScripte
extern char __near DQLScriptDir[];
extern char cbDefaultDir[_MAX_PATH+1];	// StandardWurzelVerzeichnis der Projekte

#if defined(WIN32)
char g_cbHelpPath[_MAX_PATH];
#endif

// Funktionen, die MenuPunkt freigeben bzw. kennzeichnen ----------------------
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

bool g_fAutomation = false;			// durch OLE Automation gestartet
bool g_fStartByOle = false;			// mit /Embedding gestartet
bool g_fUser = true;				// durch Nutzer gestartet
bool g_fTip = false;				// TipOfTheDay

static bool g_fRegServer = false;		// selfregistering
static bool g_fFullRegServer = false;		// full selfregistering
static bool g_fUnRegServer = false;		// and unregistering
static bool g_fInitDB = false;			// DB anlegen und exit
static bool g_fInitDBInteractive = false;	// GeoDB-Namen abfragen
static bool g_fInitDBDesktop = false;		// DB auf Desktop ablegen

void PrintUsage (void) 
{
MessBox mb (ResString (IDS_PRINTUSAGECAP, 25), 
	    ResString (IDS_PRINTUSAGE, 120), NULL);

	mb.SetType (ExclamationIcon | OkayButton);	
	mb.Show();
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
			case 'r':
			case 'R':
				if (*p) {	// selfregistering
				string strCmd = strupr (p-1);

					if (NPOS != strCmd.find ("REGSERVER")) {
						g_fRegServer = true;
						if (NPOS != strCmd.find("ADMIN"))
							g_fFullRegServer = true;
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
#if defined(WIN32)
						if (NPOS != strCmd.find("NOSHORTCUT"))
							g_fInitDBDesktop = true;
#endif
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
				
#if defined(WIN32)
			case 't':	// force TipOfTheDay
			case 'T':
				g_fTip = true;
				break;
#endif // WIN32

			case 'u':
			case 'U':
			// selfunregistering ?
				g_fUnRegServer = !strcmp (strupr(p-1), "UNREGSERVER");
				if (g_fUnRegServer) break;

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

#if !defined(WIN32)
static void Ole2InitFailure (void) 
{
MessBox mb (ResString (IDS_BADOLEVERSIONCAP, 25), 
	    ResString (IDS_OLEINITFAILURE, 120), NULL);

	mb.SetType (ExclamationIcon | OkayButton);	
	mb.Show();
}


static void Ole2BadVersion (void) 
{
MessBox mb (ResString (IDS_BADOLEVERSIONCAP, 25), 
	    ResString (IDS_BADOLEVERSION, 120), NULL);

	mb.SetType (ExclamationIcon | OkayButton);	
	mb.Show();
}
#endif // WIN32

static bool InitOle (void);

CFreeStore *App :: InitApp (CFreeStore *pFS)
{
#if !defined(WIN32)
// MessageQueue vergrößern (so groß wie möglich, max. 96 Entries)
short cMsg = 96;

	while (!SetMessageQueue (cMsg) && (cMsg -= 8))
		;
	if (cMsg < 8) return NULL;	// Fehler
#endif // WIN32

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
#if !defined(WIN32)
// OLE initialisieren
DWORD dwVer = OleBuildVersion();	// selbst initialisieren
	
	g_fOleInitialized = false;	// für alle Fälle
	if (HIWORD (dwVer) != rmm) {
		Ole2BadVersion();
		return false;		// falsche OleVersion
	}

HRESULT hr = OleInitialize (NULL);

	if (FAILED(hr)) {
		Ole2InitFailure();
		return false;
	}
	if (hr == S_OK) 	// Testen, ob OLE schon initialisiert ist
		g_fOleInitialized = true;
	
return true;
#else // WIN32

	if (OleInitialize (NULL) == S_OK)
		g_fOleInitialized = true;
	else
		g_fOleInitialized = false;

return true;
#endif
}

static void GenerateNewFile (bool fInteractive, bool fDesktop)
{
#if defined(WIN32)
string strDeskTop (_MAX_PATH, default_size);
string strDBName;

	if (!IsWin32s()) {		// Pfad der DeskTop-Dateien finden
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

			::CreateNewGeoDB (strDBName.c_str(), (iIndex == 1) ? &pIStorage : NULL, 
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
#else
	if (NULL != s_pToOpenDBName)
		::CreateNewGeoDB (s_pToOpenDBName);
	else if (fInteractive) {
	string strDBName, strUserName, strPWD;
	Window MWnd (GetDesktopWindow());
	int iIndex = ShowCreateNewDBDialog (&MWnd, strDBName, strUserName, strPWD);

		if (iIndex > 0) {
			::CreateNewGeoDB (strDBName.c_str(), strUserName.c_str(), 
					  strPWD.c_str(), (iIndex == 2));	// GeoDB erzeugen
		}
	} else
		PrintUsage();
#endif // WIN32
	delete [] s_pToOpenDBName;
}

#if defined(_DEBUG) && defined(WIN32)
#include <crtdbg.h>
#endif // WIN32

void App :: Start (const int argc, const char *argv[]) 
{
#if defined(_DEBUG) && defined(WIN32)
	if (!IsWin32s()) {
	CCurrentUser regCfg (TEXT("Software\\uve\\TRiAS\\Config"));
	DWORD dwHaltOnStartup = false;

		regCfg.GetDWORD (TEXT("HaltOnStartup"), dwHaltOnStartup);
		TX_ASSERT(dwHaltOnStartup == false);	// bei Bedarf sofort nach dem Start anhalten

	DWORD dwMemDbg = _CrtSetDbgFlag (_CRTDBG_REPORT_FLAG);
	DWORD dwNewMemDbg = 0;

		if (regCfg.GetDWORD (TEXT("UseCrtMemDbgFlag"), dwNewMemDbg) && dwNewMemDbg) {
			if (regCfg.GetDWORD (TEXT("CrtMemDbgFlag"), dwNewMemDbg))
				_CrtSetDbgFlag (dwMemDbg|dwNewMemDbg);
		}
	}
#endif

// sonstige Initialisierungen
bool fParsed = ParseCmdString (argc, argv);

	hInstance = Handle (API_APP_HAPP);  // ApplikationHandle speichern

// wenn GeoDB angelegt werden soll, dann selbiges tun und wieder raus
	if (g_fInitDB) {
		if (fParsed) 
			GenerateNewFile (g_fInitDBInteractive, g_fInitDBDesktop);
		return;
	}

// wenn nur selfregistering bzw. unregistering, dann selbiges tun und wieder raus
	if (g_fRegServer) {	
		TriasRegInit (true, g_fFullRegServer);
		return;
	}
	if (g_fUnRegServer) {
		TriasRegUnInit();
		return;
	}

#if !defined(WIN32)
	InitWindowsVersion();		// WindowsVersion feststellen
#endif // WIN32

// hier geht's richtig los
	g_pSODlg = NULL;

// CTL3D initialisieren
	if (s_fToInit3d && (g_fCtl3dInit = Ctl3dRegister (hInstance)))
		Ctl3dAutoSubclass (hInstance);

	if (s_fToShow && s_fSignOn) {
		g_pSODlg = CSignOnDlg :: CreateInstance (NULL, hInstance);
		if (g_pSODlg) {
			g_pSODlg -> Show();		// SignOn anzeigen
			SetWindowPos (g_pSODlg -> Handle (API_WINDOW_HWND),
				      HWND_TOPMOST, 0, 0, 0, 0, 
				      SWP_NOMOVE|SWP_NOSIZE);
			g_pSODlg -> Update();
			g_pSODlg -> PlaySound16();
			g_iSignOnTicks = 0;
		}
	} else
		g_pSODlg = NULL;

Rectangle MWnd;         // FensterGröße
bool IF, ZF;            // IconicFlag und ZoomedFlag

	if (!TestEnv (Handle (API_APP_HAPP))) {
		return;                 // Umgebungsbedingungen stimmen nicht
	}
	if (!InitIrisApp (MWnd, ZF, IF)) {       // diverse Initialisierungen
		return;                 // irgend was stimmt nicht, also raus
	}

	pToolBox = NULL;                // Zeiger auf Werkzeugfenster initialisieren
	ToolBoxCFlag = false;           // Fenster ist nicht angezeigt

// Zeiger auf diese App merken (muß vor Konstruktor von ExtDirisWindow sein)
	CurrApp = this;

ExtDirisWindow MainWindow (MWnd);             // Hauptfenster

// Icon in der linken oberen Ecke in Win40 einstellen
Icon IrisIcon (ResID (IRISICON));
#if defined(WIN32)
HICON hOldClassIcon = (HICON)GetClassLong (__hWndM, GCL_HICON);
	
	SetClassLong (__hWndM, GCL_HICON, (LONG)IrisIcon.Handle (API_ICON_HICON));

#else
HICON hOldClassIcon = (HICON)GetClassWord (__hWndM, GCW_HICON);

	SetClassWord (__hWndM, GCW_HICON, (WORD)IrisIcon.Handle (API_ICON_HICON));

#endif
	MainWindow.FToInit3d (s_fToInit3d);
	MainWindow.FToShow (s_fToShow);

	CurrActW = &MainWindow;         // aktiviertes Fenster merken
	CurrActDirisW = &MainWindow;

// Help aktivieren
	{
	char HelpPath[_MAX_PATH];
	char Drive[_MAX_DRIVE];
	char Path[_MAX_DIR];

		_splitpath (argv[0], Drive, Path, NULL, NULL);
#if defined(WIN32)
		_makepath (g_cbHelpPath, Drive, Path, "", "");
#endif // WIN32
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
Timer Timer1 (500);	// Timer zur Beseitigung der ObjInfoFenster und
			// für blinken der aktiven Objekte
	if (!MainWindow.SetStrobe (&Timer1)) {
		db_error (EC_NOTIMER, RC_Start);
		return;         // Timer kann nicht gestartet werden
	}

// Speichern aller x Minuten
	if (g_iMinutes) {
		g_pT = new Timer (6000, 2);
		if (g_pT == NULL || !MainWindow.SetStrobe (g_pT)) {
			db_error (EC_NOTIMER, RC_Start);
			return;         // Timer kann nicht gestartet werden
		}
	}
	
	pTextSearch = NULL;		// Kein TextRechercheFenster aktiv

// verifizieren, ob OLE wirklich aktiv ist
	g_fUser = true;
	if (g_fAutomation) g_fAutomation = DEXN_AutomationHandled();
	if (g_fStartByOle) g_fStartByOle = DEXN_EmbeddingHandled();
	if (g_fStartByOle || g_fAutomation)
		g_fUser = false;

// wenn auf der Kommandozeile ein Projekt gegeben ist, dann dieses eröffnen
	if (fParsed) {
		if (s_pToOpenDBName && g_fUser) {
			g_fTip = DEXN_TipOfTheDay(TOTD_ForceNoTips);

		short gfMode = s_fToOpenROMode ? OM_RO : OM_Normal;

			if (s_fStandardSight) gfMode |= OM_NoStandard;
			/*if (!MainWindow.FToShow())*/
				gfMode |= OM_HideWindow;

			if (MainWindow.OpenDB (s_pToOpenDBName, 
					       s_pToOpenUserName, "", gfMode) == EC_OKAY)
			{
				MainWindow.InitProjectMenu();
				MainWindow.LoadLocalExtensions();
				MainWindow.ReReadCaption();
				DELETE (g_pSODlg);		// SignOn ausblenden
			} else
				MainWindow.InitMenues();

			if (MSF == Iconized) MSF = Normal;	// bei default Projekt nicht Zoomed 
			DELETE (g_pSODlg);			// SignOn ausblenden, da Projekt eröffnet wird
			MainWindow.Show ((ShowState)(MainWindow.FToShow() ? MSF : HideWindow));
		} else {	
		// Hauptfenster anzeigen, oder eben auch nicht
			MainWindow.InitMenues();

		// Tooltip nur anzeigen lassen, wenn Trias sichtbar ist
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
//		DEXN_ServerInitialized();	// fertig initialisiert	- jetzt in App::Idle (#HK960117)
		Exec (ExecNormal);			// MessageLoop
	}

// altes ClassIcon wieder einstellen
#if defined(WIN32)
	SetClassLong (__hWndM, GCL_HICON, (LONG)hOldClassIcon);
#else
	SetClassWord (__hWndM, GCW_HICON, (WORD)hOldClassIcon);
#endif

// Timer wieder abschalten
	DELETE (g_pSODlg);	// für alle Fälle: SignOn ausblenden
	MainWindow.CancelStrobe (&Timer1);

	if (g_pT) {
		MainWindow.CancelStrobe (g_pT);
		delete g_pT;
	}

	DELETE (pToolBox);
	DELETE (IrisHD);

// CTL3D freigeben
	if (g_fCtl3dInit) Ctl3dUnregister (hInstance);

// alle noch offenen Datenbanken schließen
	CleanUpTrias01();
}


// Konstruktor für Hauptfenster
IrisWind :: IrisWind (Rectangle &Rc)
#if defined(WIN32)
	  : StrobeWindow (IsWin40() ? WS_EX_CLIENTEDGE : 0),
	    StartMenu (STARTMENU),
#else
	  : StartMenu (STARTMENU),
#endif
	    IrisMenu (IRISMENU),
	    IrisIcon (ResID (IRISICON)),
	    StartAcc (STARTACCELS),
	    IrisAcc (IRISACCELS)
{
	if (g_fMenu) {
		EnableSysMenu ();                       // Systemmenu anzeigen
		EnableMaxBox ();                        // MinMaxButtons anzeigen
		EnableMinBox ();
	}

#if defined(WIN32)
	m_pMRU = CreateMruMenu  (NBMRUMENUSHOW, NBMRUMENU, _MAX_PATH, IDMRU);
	if (!m_pMRU) {
		db_error (EC_NOMEMORY, RC_ctIrisWind);
		return;
	}
#endif // WIN32

// DruckerDaten initialisieren
	m_pPD = new PrinterPars();		// erstmal nur anlegen
	if (!m_pPD) {
		db_error (EC_NOMEMORY, RC_ctIrisWind);
		return;
	}

// Flags initialisieren
	m_fFullRedrawOnScroll = false;
	m_fHandleCancelMode = false;
	m_iDrawSem = 0;
	
	m_lLastIdent = -1L;
		
// erstes DatenBasisObjekt bilden
//	_DBO = new DatenBasisObjekt;
	m_pDBOs = new CDBOArray;
	if (!m_pDBOs) {
		db_error (EC_NOMEMORY, RC_ctIrisWind);
		return;
	}

// sonstige lokale Parameter initialisieren
	RePaintFlag = false;
	m_pWVS = EnableVScroll ();                // ScrollBars initialisieren
	m_kSX = 1;
	m_pWHS = EnableHScroll ();
	m_kSY = 1;

	DRO = NULL;                             // DragRechteck initialisieren

// HintergrundBrush bilden und aktivieren        
	_IrisBGBrush = new Brush (Color ((Colors)192,(Colors)192,(Colors)192));
	_emptyBrush = new Brush (HollowBrush);
	if (!_IrisBGBrush || !_emptyBrush) {
		db_error (EC_NOMEMORY, RC_ctIrisWind);
		return;
	}
	ChangeBackground (_IrisBGBrush);        // Hintergrund setzen

// AspectRatio bestimmen
	AspectRatio = GetAspectRatio();

// FensterEigenschaften setzen
	EnableBorder ();                        // Rahmen anzeigen
	SetIcon (&IrisIcon);                    // Icon setzen
	SetCaption (ResString (IDS_CAPTION, 120)); // Titelzeile einlesen

// Stack für Vergrößerungen initialisieren
ObjContainer locOC(0, 0, 0, 0);

	actClip.Push (locOC);

// Menu um vorhergehende DB's erweitern
#if !defined(WIN32)
	InitOldDBMenu (true, &IrisMenu, IRISMENUPOS);
	InitOldDBMenu (true, &StartMenu, STARTMENUPOS);
#endif // !WIN32

// Kontextsensitive Hilfe erlauben
	EnableHelp (true, IrisHD);

// aktuelles ScriptFile für Recherche
	SelScriptFile = NULL;		// keine DefaultDatei

// initiale Größe und Lage festlegen
	MOrig = Point (Rc.Left(), Rc.Bottom());
	MSize = Dimension (Rc.Right()-Rc.Left(), Rc.Top()-Rc.Bottom());
	ChangePosition (MOrig);
	ChangeSize (MSize);

	CanvasErase ();
}

// Destruktor 
IrisWind :: ~IrisWind (void) 
{
#if defined(WIN32)
	if (m_pMRU) {
		if (IsWin32s())
			SaveMruInIni (m_pMRU, TEXT("OpenMRU"), ResString (IDS_PROFILE, 20).Addr());
		else
			SaveMruInReg (m_pMRU, TEXT("Software\\uve\\TRiAS\\OpenMRU"));

		DeleteMruMenu (m_pMRU);
		m_pMRU = NULL;
	}
#endif // WIN32
	DELETE (m_pPD);
	DELETE (m_pDBOs);		// DatenBasisObjekt(e) freigeben
	DELETE (_IrisBGBrush);	
	DELETE (_emptyBrush);
	if (hPalette != NULL) {
		DeleteObject (hPalette); hPalette = NULL;
	}
	DELETE (SelScriptFile);
}


// Initialisierungen der FensterKlasse (Menu etc.) ----------------------------
void IrisWind :: InitMenues (void)
{
	if (g_fMenu) {
#if defined(WIN32)
		TX_ASSERT(m_pMRU);

        if (IsWin32s())
			LoadMruInIni (m_pMRU, TEXT("OpenMRU"), ResString(IDS_PROFILE, 20).Addr());
        else
			LoadMruInReg (m_pMRU, TEXT("Software\\uve\\TRiAS\\OpenMRU"));
        PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(StartMenu.Handle(), 0), IDM_EXIT);
#endif // WIN32

		ChangeMenu (&StartMenu);                // Menu einschalten
		ChangeAccel (&StartAcc);                // Acceleratortabelle setzen
	}
}

bool IrisWind :: InitProjectMenu (void)
{
	if (g_fMenu) {
#if defined(WIN32)
		TX_ASSERT(m_pMRU);

        if (IsWin32s()) {
			LoadMruInIni (m_pMRU, TEXT("OpenMRU"), ResString(IDS_PROFILE, 20).Addr());
        } else
			LoadMruInReg (m_pMRU, TEXT("Software\\uve\\TRiAS\\OpenMRU"));
        PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);
#endif // WIN32

		ChangeMenu (&IrisMenu);
		ChangeAccel (&IrisAcc);

		return true;
	}

return false;
}


// Menu wird initialisiert ----------------------------------------------------
void IrisWind :: MenuInit (MenuInitEvt e) 
{
	if (!g_fMenu || ::GetMenu (Handle (API_WINDOW_HWND)) == NULL) 
		return;

pMenu pM = e.GetMenu();

	if (pM == &IrisMenu) {
	// Checkmarks verteilen, nur wenn IrisMenu aktiv ist
	DatenBasisObjekt &rDBO = DBO();
	bool ifRO = !DEX_GetROMode();

		MenuEnable (pM, IDM_CLOSE, CloseEFlag);         // ProjectClose
		
		MenuCheck (pM, IDM_TOOLS, ToolBoxCFlag);        // Werkzeugkiste

		if (pToolBox) {
		ToolIterator TI (pToolBox -> Tools());
		short iTool = TI.FirstTool();

			while (iTool != -1) {
				MenuCheck (pM, IDM_ARROW+iTool, 
					   pToolBox -> ToolCFlag (iTool));
				iTool = TI.NextTool();
			}
		} else {
			MenuCheck (pM, IDM_ARROW, false);
			MenuCheck (pM, IDM_ZOOM, false);
			MenuCheck (pM, IDM_LUPE, false);
			MenuCheck (pM, IDM_LINEAL, false);
			MenuCheck (pM, IDM_SCHERE, false);
			MenuCheck (pM, IDM_TEXT, false);
		}

		MenuCheck (pM, IDM_TEXTSEARCH, TextSearchCFlag);// TextRecherche
		MenuCheck (pM, IDM_COORDS, CoordsCFlag && CoordsEFlag); // Koordinaten
		MenuCheck (pM, IDM_MASSTAB, MasstabCFlag);	// Maástab

		MenuEnable (pM, IDM_EDITHEADER, ifRO && EditHeaderEFlag);  // Header editieren
		MenuEnable (pM, IDM_DRAW, DrawEFlag);           // Geometrie zeichnen
		MenuEnable (pM, IDM_SELOBJ, ifRO && IdentSelEFlag);     // Id-Selektion
		MenuEnable (pM, IDM_COORDS, CoordsEFlag);

		MenuEnable (pM, IDM_PRINT, PrintEFlag);         // Drucken

		MenuEnable (pM, IDM_COPYTOCLIPBOARD, DRO != NULL);

		MenuCheck (pM, IDM_LEGENDE, LegendeCFlag);	// Legende
		MenuCheck (pM, IDM_OVERVIEW, OverViewCFlag);	// GesamtÜbersicht

		MenuEnable (pM, IDM_TEXT, GetGeoDBVersion() >= NEWDBVERSION);
		MenuEnable (pM, IDM_VISTEXTOBJ, GetGeoDBVersion() >= NEWDBVERSION);
		MenuCheck (pM, IDM_VISTEXTOBJ, DrawTextObjs && GetGeoDBVersion() >= NEWDBVERSION);

		MenuEnable (pM, IDM_EXPORT, g_fFilters);	// Export erlauben
		MenuEnable (pM, IDM_COORDMODE, rDBO.pCT() -> CanConfig());

#if !defined(WIN32)
		MenuCheck (pM, IDM_25000, Nomen25CFlag);        // Nomenklaturen
		MenuCheck (pM, IDM_50000, Nomen50CFlag); 
		MenuCheck (pM, IDM_10000, Nomen10CFlag); 
		MenuCheck (pM, IDM_SCHRANK, SchrankCFlag);      // Schrank
#endif // !WIN32

		if (GetGeoDBVersion() >= VERSION05000008) {
		ObjContainer OC (0, 0, 0, 0);
		bool iFlag = false;

			MenuEnable (pM, IDM_SELSICHTCONT, ifRO);
			MenuEnable (pM, IDM_DELSICHTCONT, 
				ifRO && rDBO.GetActSichtCont(&OC) == EC_OKAY);

			if (OC.isValid()) {
			ObjContainer ocT = actClip.Top();
			
				if (OC >= ocT)
					iFlag = true;
				else if (OC < ocT) {
					if (OC > rDBO.GetExtend()) 
						iFlag = true;
				} else
						iFlag = true;
			} else 
				iFlag = true;

			MenuEnable (pM, IDM_PREVSELAUSSCHNITT, iFlag);
		} else {
			MenuEnable (pM, IDM_SELSICHTCONT, false);
			MenuEnable (pM, IDM_DELSICHTCONT, false);
			MenuEnable (pM, IDM_PREVSELAUSSCHNITT, actClip.Top().isValid());
		}

	// alle anderen vom ROMode abhängigen Items behandeln
#if !defined(WIN32)
		MenuEnable (pM, IDM_SAVEDB, ifRO && rDBO.DB().isDirty());
#endif
		MenuEnable (pM, IDM_DELETEVIEWS, ifRO);
		MenuEnable (pM, IDM_SAVEOPT, ifRO);
		MenuEnable (pM, IDM_DELETEIDENTS, ifRO);
		MenuEnable (pM, IDM_MODIFYIDENTS, ifRO);
		
#if !defined(NOPROJEKTION)
		MenuCheck (pM, IDM_GEOGRAPH, GeographicCFlag);  // Koordinatensysteme
		MenuCheck (pM, IDM_WORLD, WorldCFlag);
#endif
#if defined(WIN32)
	// wenn CompoundFile, dann SaveAs aktiv
		MenuEnable (pM, IDM_SAVEAS, rDBO.isComFile());
		MenuEnable (pM, IDM_SAVECOPYAS, rDBO.isComFile());
#endif
	}
// MenuPunkte vom FloatingMenu aktivieren
	InitTextObjectMenu ();
}


// Menukommandos verarbeiten
void IrisWind :: MenuCommand (MenuCommandEvt mcEvt) 
{
	if (wasHelpEvt) {
	// wenn zu diesem Item Hilfe gerufen wird, dann Menupunkt nicht
	// bearbeiten
		wasHelpEvt = false;
		return;
	}
	switch (mcEvt.GetItemID ()) {
	case IDM_NEWDB:		// neue GeoDB anlegen (dbinit)
		CreateNewGeoDB();
		break;
		
	case IDM_OPEN:          // OpenBox anzeigen
		{
		COpenDBDlg ODlg (this);		// Dialogfenster Anzeigen
		string strInitDir = cbDefaultDir;

			ODlg.SetInitialDir (strInitDir.c_str());
			ODlg.Show ();

		// EierUhr anzeigen
		CEierUhr Wait (this);

		// Resultate verarbeiten
			if (ODlg.Result ()) {
			char lDBName[PATHLEN+1];

			// evtl. offene DB schließen
				if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
					if (CloseDB() != EC_OKAY)
						break;	// Fehler oder warten
					DELETE (DRO);
				}

			// DB eröffnen
				ODlg.GetFileSpec (lDBName, PATHLEN+1);
				if (OpenDB (lDBName, ODlg.GetUserName(),
					ODlg.GetPassWord(),
					ODlg.GetROMode() ? OM_RO|OM_ActivateDBO : 
							   OM_Normal|OM_ActivateDBO)
					 != EC_OKAY) 
				{
					break;
				}
				InitProjectMenu();
				ReReadCaption();
			}

		// neue DB zeichnen
			RePaint ();
			break;
		}

	case IDM_SAVEDB:
		if (m_pDBOs -> Count() && DBO().DB().isOpened()) {	// GeoDB eröffnet
#if defined(WIN32)
			if (DBO().DB().GetTempMode())	// erstes Speichern überhaupt
				SaveAsGeoDB();
			else 
#endif // WIN32
				SaveGeoDB();
		}
		break;

#if defined(WIN32)
	case IDM_SAVEAS:
		SaveAsGeoDB();
		break;

	case IDM_SAVECOPYAS:
		ExportAsGeoDB();
		break;
#endif

	case IDM_CLOSE:				// DB Schließen
		if (EC_OKAY == CloseDB())
			DELETE (DRO);
		break;          

	case IDM_EDITHEADER:    		// GeoDB-Header editieren
		ShowEditHeader();
		ReReadCaption();		// evtl. Caption neu generieren
		break;

	case IDM_SELOBJ:        		// Identifikatoren auswählen
		ShowIdentSel ();
		break;

	case IDM_DELETEVIEWS:			// Sichten löschen
		DeleteViews ();
		ReReadCaption();		// evtl. Caption neu generieren
		break;
		
	case IDM_REBUILD:			// Sicht neu generieren
		DBO().ProcessMenuEvent (NULL, true);
		RePaintFlag = true;
		RePaint ();
		if (OverViewCFlag && pOverView) pOverView -> RePaint();
		break;
		
	case IDM_DRAW:          		// DB-Zeichnen
	// wenn CTRL-Taste gedrückt, dann Sicht neu einlesen
		if (GetKeyState (VK_CONTROL) < 0) 
			DBO().ProcessMenuEvent (NULL, true);
		RePaintFlag = true;
		RePaint ();

	// Übersichtsfenster
		if (OverViewCFlag && pOverView) pOverView -> RePaint();
		break;

	case IDM_ABOUT:         		// Aboutbox anzeigen
		{
		CSignOnDlg *pAbout = CSignOnDlg :: CreateInstance (this, hInstance, true);

			if (pAbout) {
				pAbout -> Show (Centre);
				delete pAbout;
			}
		}
//		AboutDialogBox (this, ABOUTBOX).Show ();
		break;

#if !defined(NOPROJEKTION)
	case IDM_GEOGRAPH:      // Geografische Koordinaten anzeigen
		DBO().SetPrjFcn (NULL, NULL);
	// DatenBasisObjekt Ausschnitt definieren
		DBO().SetExtend (DBO().DBCont().InflateCont(10), AspectRatio);
	// Menupunkte markieren
		GeographicCFlag = true;
		WorldCFlag = false;
		break;

	case IDM_WORLD:         // Weltprojektion anzeigen
		DBO().SetPrjFcn (geowel, NULL);
	// DatenBasisObjekt Ausschnitt definieren
		DBO().SetExtend (DBO().DBCont().InflateCont(10), AspectRatio);
	// Menupunkte markieren
		WorldCFlag = true;
		GeographicCFlag = false;
		break;
#endif

	case IDM_TOOLS:		// Werkzeugfenster anzeigen bzw. verstecken
		ToolBoxCFlag = !ToolBoxCFlag;
		if (ToolBoxCFlag) {
			pToolBox -> Show();
			pToolBox -> Update();
			ValidateWindow ();
		} else
			pToolBox -> Hide();
		break;

	case IDM_CANCEL:        // allgemeiner Abbruch
		GCancelFlag = GCFAbort;
		break;

	case IDM_TEXTSEARCH:    // TextrechercheFenster anzeigen
		TextSearchCFlag = !TextSearchCFlag;
		if (TextSearchCFlag) {  // TextRecherche zuschalten
			if (!pTextSearch)
				pTextSearch = new TextRechercheDlg (this, TextCode, TextMode);
			pTextSearch -> Show();  // anzeigen
			ValidateWindow ();      // kein RePaint zulassen
		} else if (pTextSearch) {
			pTextSearch -> Hide();  // nicht mehr anzeigen
			delete pTextSearch;     // Speicher freigeben
			pTextSearch = NULL;
		}
		break;

	case IDM_TEXTPARAMS:    // RechercheParameter einstellen
		ShowTextRecherche ();
		break;

	case IDM_COORDS:
		CoordsCFlag = !CoordsCFlag;
		if (CoordsCFlag) {
			if (!pCoords)   
				pCoords = new CoordsDlg (this, DBO().pCT());
			pCoords -> Show();      // anzeigen
			SetFocus();             // Focus im Hauptfenster lassen
			ValidateWindow ();      // Kein RePaint 
		} else if (pCoords) {
			pCoords -> Hide();      // nicht mehr anzeigen
			delete pCoords;         // Speicher freigeben
			pCoords = NULL;
		}
		break;

#if !defined(WIN32)
	case IDM_SCHRANK:
		MenuSelectSchrank ();
		break;

	case IDM_10000:
		MenuSelectNomen10 ();
		break;

	case IDM_25000:
		MenuSelectNomen25 ();
		break;

	case IDM_50000:
		MenuSelectNomen50 ();
		break;
#endif // !WIN32

	case IDM_MASSTAB:
		MenuSelectMasstab ();
		break;

	case IDM_SAVEOPT:
		{
		CSaveOptionsDlg *pSODlg = new CSaveOptionsDlg (this);
		
			if (pSODlg && pSODlg -> Init()) {
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
			}
			DELETE (pSODlg);
		}
		break;
		
	case IDM_PROFILE:
		Profiling = ~Profiling;
		if (Profiling)  IrisMenu.CheckItem (IDM_PROFILE);
		else            IrisMenu.unCheckItem (IDM_PROFILE);
		break;

	case IDM_PRINT:                 // Drucken
		{
		char Caption[65];

			PrintGraphics(GetCaption (Caption, 64));
		}
		break;

	case IDM_SELPRINT:              // Druckereinrichtung
		PrinterMode ();
		break;

	case IDM_EXPORT:		// Daten exportieren
		if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
		ObjContainer OC;

			if (DRO != NULL) {	// nur selektierten Bereich
			Point pt1 = ((DragRectangleObject *)DRO)->LowerLeft();
			Point pt2 = ((DragRectangleObject *)DRO)->UpperRight();
			Punkt pnt1 = DCtoOC (pt1);
			Punkt pnt2 = DCtoOC (pt2);

				OC = ObjContainer (pnt1, pnt2);
				DBO().doExport (this, &OC);
			} else if (actClip.Top().isValid()) {
			// aktueller Bildausschnitt
			Rectangle rcT = CanvasRect();
			
				OC = rcT;
				DBO().doExport (this, &OC);
			} else
			// gesamte DB
				DBO().doExport (this);
		}
		break;

	case IDM_SYMBOLPARS:		// Darstellungsparameter vorgeben
	// neu zeichnen abbrechen, wenn neuer Dialog erzeugt wird
		m_fHandleCancelMode = true;
		ChangeIdVisInfo ();
		m_fHandleCancelMode = false;
		break;

	case IDM_CHANGEVISINFO:		// DarstellungsTyp ändern
		ChangeIdVisInfo (-1L, true);
		break;

	case IDM_PRIORITYSELECT:	// Darstellungspriorität vorgeben
		{
		char Buffer[SIGHTMENUITEM+1];

			DBO().GetActiveSightName(Buffer, sizeof(Buffer));
			doPrioritySelect (this, DBO().Idents(), Buffer);
		}
		break;

	case IDM_BACKGRNDCOLOR:		// Hintergrundfarbe vorgeben
		break;
	
	case IDM_COPYTOCLIPBOARD:
		if (DRO != NULL) {
		Rectangle Rc = ((DragRectangleObject *)DRO) -> GetRect();

			CopyToClipBoard (this, Rc);
		}
		break;

	case IDM_SELSICHTCONT:
		if (DRO != NULL && ((DragRectangleObject *)DRO) -> isValid ()) {
		// Ausschnitt ist selektiert
		// Koordinaten transformieren
		Point pt1 = ((DragRectangleObject *)DRO)->LowerLeft();
		Point pt2 = ((DragRectangleObject *)DRO)->UpperRight();
		Punkt pnt1 = DCtoOC (pt1);
		Punkt pnt2 = DCtoOC (pt2);
		ObjContainer OC (pnt1, pnt2);

			OC.InflateCont (10);	// Container anpassen
			DBO().SetActSichtCont (OC);
		} else {
		// aktuellen Bildschirmausschnitt verwenden
			DBO().SetActSichtCont (DBO().GetExtend());
		}
		break;

	case IDM_DELSICHTCONT:
		DBO().DelActSichtCont();
		break;

	case IDM_LEGENDE:
		LegendeCFlag = !LegendeCFlag;
		if (LegendeCFlag) {
		char Caption[SIGHTMENUITEM +1];

			if (!pLegende) {
				DBO().GetActiveSightName (Caption, sizeof(Caption));
				pLegende = CLegendeWindow :: CreateInstance (this, Caption, DBO());
			}
			if (pLegende == NULL)
				break;
				
			pLegende -> Show();	// anzeigen
			LegendToRepaint = false;
			SetFocus();             // Focus im Hauptfenster lassen
			ValidateWindow ();      // Kein RePaint 
		} else if (pLegende) {
			pLegende -> SaveLegend();	// Legende Speichern
			pLegende -> Hide();      // nicht mehr anzeigen
			LegendToRepaint = false;
			delete pLegende;         // Speicher freigeben
			pLegende = NULL;
		}
		break;

	case IDM_OVERVIEW:
		if (m_pDBOs -> Count() == 0) 
			break;
		OverViewCFlag = !OverViewCFlag;
		DELETE (pOverView);		// für alle Fälle
		if (OverViewCFlag) {
		ObjContainer OC = DBO().DB().DBCont();
		
			pOverView = COverView :: CreateOverView (this, OC);
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
		break;	
			
	case IDM_VISTEXTOBJ:
		DrawTextObjs = !DrawTextObjs;
		RePaint();			// alles neu zeichnen
		break;

	case IDM_CREATETEXTOBJ:
	case IDM_DELETETEXTOBJ:
	case IDM_EDITTEXTOBJ:
//	case IDM_MODIDTEXTOBJ:
	case IDM_CREATEBREL:
	case IDM_DELETEBREL:
	case IDM_ADDTOLEGEND:
		HandleTextObjectMenu (mcEvt.GetItemID());
		break;

	case IDM_SELAUSSCHNITT:		// Ausschnitt auswählen
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

				// bei Bedarf ScrollBars einblenden und initialisieren
					InitWndScrollBars ();

				// Übersichtsfenster bedienen
					if (OverViewCFlag && pOverView) {
					Rectangle rcC = CanvasRect();
					ObjContainer OC (rcC);
					
						pOverView -> SetActVP (OC);
					}

				// neu zeichnen
					LegendToRepaint = true;
					RePaintFlag = true;
					RePaint ();
				}
			}
			DELETE (pADlg);
		}
		break;

	case IDM_PREVSELAUSSCHNITT:
		if (m_pDBOs -> Count() == 0)
			break;
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
						break;
				} else {
					actClip.Pop();
					DBO().SetExtend (this, ocT, AspectRatio);
				}
			} else {
			// vorhergehenden Ausschnitt einstellen
				ocT = actClip.Pop();
				DBO().SetExtend (this, ocT, AspectRatio);
			}

		// bei Bedarf ScrollBars einblenden und initialisieren
			InitWndScrollBars ();

		// Übersichtsfenster
			if (OverViewCFlag && pOverView) {
			ObjContainer ocT1 = DBO().DB().DBCont();
		
 				if (ocT < ocT1) {
				Rectangle rcC = CanvasRect();
				ObjContainer OC = (Rectangle &)rcC;
			
					pOverView -> SetActVP (OC);
				} else
					pOverView -> ResetActVP();
			}

		// neu zeichnen
			RePaintFlag = true;
			LegendToRepaint = true;
			RePaint ();
		}
		break;

	case IDM_ZOOMOUT:
		ZoomOut();
		break;
		
	case IDM_ZOOMIN:
		ZoomIn();
		break;
		
	case IDM_SELECTIDENTS:
		SelectIdents();
		break;
		
	case IDM_DELETEIDENTS:
		DeleteIdents();
		break;

	case IDM_MODIFYIDENTS:
		ModifyIdents();
		break;
				
	case IDM_DEFAULTVIEW:
		DefineDefaultView();
		break;
		
	case IDM_COORDMODE:
		if (NULL != DBO().pCT() && DBO().pCT() -> CanConfig())
			DBO().pCT() -> CoordTransMode (this);
		break;

/*
#if !defined(WIN32)
	case IDM_IMPORT:
		if (m_pDBOs -> Count() && DBO().DB().isOpened())
			DBO().DB().doImport (this);
		break;
#endif // WIN32
*/		
	case IDM_INDEX:
		IrisHD -> Show ("HelpIndex");
		break;

	case IDM_HELP:
		IrisHD -> Show ("HelpOnHelp");
		break;

	// HilfeMenu
	case IDM_MOUSE: 
	case IDM_GLOSSAR:
	case IDM_KEYBOARD:
		IrisHD -> Show (mcEvt.GetItemID());
		break;

	case IDM_SELECTVIEWS:		// Accelerator
	case IDM_SIGHTS+MAXSHOWNVIEWS:
		SelectView();
		break;

#if !defined(WIN32)
	case IDM_OPENOLD1:      // müssen fortlaufend sein
	case IDM_OPENOLD2:
	case IDM_OPENOLD3:
	case IDM_OPENOLD4:
	// eine der vorhergehenden DB's eröffnen
		if (OpenOld (mcEvt.GetItemID()) != EC_OKAY) 
			break;	// Fehler oder Ende des Zeichnens abwarten: 
				// also weiter
                
		InitProjectMenu();

	// neue DB zeichnen
		ReReadCaption();
		RePaint();
		break;
#endif // WIN32

	default:
		{
		uint iItemID = mcEvt.GetItemID();

#if defined(WIN32)
			if (iItemID > IDMRU && iItemID <= IDMRU+9) {
				if (OpenOld (iItemID) != EC_OKAY) 
					break;	// Fehler oder Ende des Zeichnens abwarten: 
							// also weiter
                
				InitProjectMenu();

			// neue DB zeichnen
				ReReadCaption();
				RePaint();
				break;
			}
#endif // WIN32

		// MenuPunkt für Werkzeugkiste
			if (iItemID >= IDM_ARROW && iItemID < IDM_ARROW + 50) {
				if (pToolBox) 
					pToolBox -> SetTool (iItemID-IDM_ARROW);
				break;
			}

		// evtl. AnsichtMenuItem aktiviert
			if (DBO().ProcessMenuEvent (iItemID)) {
//				ObjInfoListe.EveryDelete();	// ORFenster weg (jetzt in AcivateSight)
				InitWndScrollBars();		// Rollbalken zuschalten
				ReReadCaption();
				RePaint();			// neue Ansicht zeichnen
			}
		}
		break;
	}
}


// EventHandlerRoutine für SessionEnde ----------------------------------------
// bool IrisWind :: QueryClose (Event) 
// {
//	return myQueryClose (true);
// }

bool IrisWind :: myQueryClose (bool CleanUp) 
{
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {		// DB noch eröffnet

		if (m_iDrawSem > 0) {		// zeichnet gerade
		MessBox mb (ResString (IDS_SESSIONENDCAP, 40), 
			    ResString (IDS_SESSIONENDPAINTING, 200),
			    this);

			mb.SetType (ExclamationIcon | OkayButton);
			mb.Show();
			return false;
		}

		if (DEXN_ServerIsClosing()) 
			return false;	// jemand hat was dagegen
				
		if (DEXI_isDrawing())
			GCancelFlag |= GCFAppClosed;
		CloseDB (true);
		DELETE (DRO);

	} else if (DEXN_ServerIsClosing())	// kein Projekt offen
		return false;	// jemand hat was dagegen

	if (CleanUp) EndCleanUp ();
	DEXN_ServerClosed();		// das letzte vom Tage

// erst nach der letzten Message die Pointer Ausnullen
	CurrActW = NULL;
	CurrActDirisW = NULL;
	
return true;
}


// Halber Bildschirmausschnitt ------------------------------------------------
void IrisWind :: ZoomOut (void) 
{
	if (m_pDBOs -> Count() == 0) return;

ObjContainer OC = DBO().GetExtend();

	if (OC.isValid()) {
	// Bildschirmausschnitt halbieren
	KoOrd dX = (OC.XMax() - OC.XMin())/2;
	KoOrd dY = (OC.YMax() - OC.YMin())/2;
	ObjContainer ocT (OC.XMin() - dX, OC.XMax() + dX, OC.YMin() - dY, OC.YMax() + dY);
		
		DBO().SetExtend (this, ocT, AspectRatio);	// neuen Ausschnitt setzen		
			
	// bei Bedarf ScrollBars einblenden und initialisieren
		InitWndScrollBars ();

	// Übersichtsfenster
		if (OverViewCFlag && pOverView) {
		ObjContainer ocT1 = DBO().DB().DBCont();
		
			if (ocT < ocT1) {
			Rectangle rcC = CanvasRect();
			ObjContainer OC = (Rectangle &)rcC;

				pOverView -> SetActVP (OC);
			} else
				pOverView -> ResetActVP();
		}

	// neu zeichnen
		RePaintFlag = true;
		LegendToRepaint = true;
		RePaint ();
	}
}


// Doppelter Bildschirmausschnitt ---------------------------------------------
bool IrisWind :: ZoomIn (void)
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
	
	// bei Bedarf ScrollBars einblenden und initialisieren
		InitWndScrollBars ();

	// Übersichtsfenster
		if (OverViewCFlag && pOverView) {
		ObjContainer ocT1 = DBO().DB().DBCont();
		
			if (ocT < ocT1) {
			Rectangle rcC = CanvasRect();
			ObjContainer OC = rcC;

				pOverView -> SetActVP (OC);
			} else
				pOverView -> ResetActVP();
		}

	// neu zeichnen
		RePaintFlag = true;
		LegendToRepaint = true;
		RePaint ();
		return true;		// alles ok
	}

return false;
}


// Objekte eines/mehrerer Idents selektieren ----------------------------------
bool IrisWind :: SelectIdents (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (this, 
						SELECTIDENTSDLG, 
						IDL_IDENTSLIST);
	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	ObjFeld Objs;
	long lIdent = -1L;
	short iOTyp = 0;
	
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (!AddObjects (Objs, lIdent, iOTyp))
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}
		if (Objs.Count()) {
		// Dialogfenster generieren
		DEXXCREATEOBJEKTINFO crOI;
		
			crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
			crOI.lpCaption = StrDup (ResString (IDS_OBJINFOCAPTION, 30));
			crOI.lcObjs = &Objs;
			crOI.pcMColor = new Color (RED);
			crOI.ppntPos = new Point (0, 0);
			crOI.fcnPos = NULL;
			crOI.pData = NULL;
		
			DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren
		
			if (crOI.ppntPos) delete crOI.ppntPos;
			if (crOI.pcMColor) delete crOI.pcMColor;
			if (crOI.lpCaption) delete crOI.lpCaption;	// Speicher wieder freigeben
		}
	}
	DELETE(pDlg);

return true;
}


// Objekte eines mehrerer Idents löschen --------------------------------------
bool IrisWind :: DeleteIdents (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (this, 
				DELETEIDENTSDLG, IDL_DELETEIDENTSLIST);
	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	long lIdent = -1L;
	short iOTyp = 0;
	
#if defined(WIN32)
	ResString resUndo (IDS_UNDODELETEOBJECT, 30);

		DEX_BeginUndoLevel (resUndo.Addr());
#endif // WIN32
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
			ObjFeld Objs;

				if (!AddObjects (Objs, lIdent, iOTyp))
					break;
				if (0 == Objs.Count()) continue;
			
			CRing r(Objs);
			ErrInstall EI (EC_DELRECORD);
				
				for (r.First(); r.Valid(); r.Next()) {
				ObjNummerLock l(r);
			
					TX_ASSERT(NULL != (ObjNummer *)l);
					DEX_DeleteObjectEx (l -> _ON);
				}

			// Identifikator/ObjektTyp aus IdentListe entfernen
				DBO().Idents().DeleteIdent (lIdent, iOTyp);
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}
#if defined(WIN32)
		DEX_EndUndoLevel();
#endif // WIN32

	// Legende auf den neuesten Stand bringen
		DEX_RefreshLegend();
		DEX_RepaintLegend();

		RePaint();	// Anzeige neu aufbauen
	}
	DELETE(pDlg);
	
return true;
}


// Objekte eines Idents umklassifizieren --------------------------------------

short OTypToBits (ObjTyp iOTyp);

bool IrisWind :: ModifyIdents (void)
{
CModifyIdentDlg *pDlg = CModifyIdentDlg :: CreateInstance (this);

	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	ObjFeld Objs;
	long lIdent = -1L;
	short iOTyp = 0;
	long lNewIdent = pDlg -> GetNewIdent();
		
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (!AddObjects (Objs, lIdent, iOTyp))
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}
		if (Objs.Count()) {
		CRing r(Objs);
		MODOBJIDENT MOI;
				
			MOI.dwSize = sizeof (MODOBJIDENT);
			for (r.First(); r.Valid(); r.Next()) {
			ObjNummerLock l(r);
			
				if (!l) continue;
				
			// umklassifizieren
				MOI.lONr = l -> _ON;
				MOI.lNewIdent = lNewIdent;
				MOI.iMode = MODIDENT_ADDTOVIEW|OTypToBits((ObjTyp)DEX_GetObjectType(MOI.lONr));
				DEX_ModObjectIdent (MOI);
			}
			DEX_RefreshLegend();
			DEX_RepaintLegend();
			RePaint();	// Anzeige neu aufbauen
		}
	}
	DELETE(pDlg);
	
return true;
}


typedef struct tagADDOBJECTDATA {
	ObjNummerCreator *m_pcrON;
	short m_iOTyp;
} ADDOBJECTDATA;

extern "C" bool EXPORTTRIAS WINAPI AddObjectsCallback (long lONr, short iOTyp, void *pData)
{
ObjNummerCreator *pObjs = ((ADDOBJECTDATA *)pData) -> m_pcrON;

	if (!(iOTyp & (((ADDOBJECTDATA *)pData) -> m_iOTyp)))
		return true;	// interessiert nicht
	
	return Create (*pObjs, ObjNummer)(lONr) != NULL;
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


#if defined(WIN32)
// Darstellungsparameter einzelner(aller) Idents in andere Ansicht durchschreiben
bool IrisWind :: DefineDefaultView (void)
{
CCopyVisInfoDlg *pDlg = CCopyVisInfoDlg :: CreateInstance (this, 
				COPYVISINFODLG, IDL_IDENTSLIST);
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
		
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
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
		}
	}

return true;
}

#else

// Darstellungsparameter einzelner(aller) Idents in StandardAnsicht durchschreiben
bool IrisWind :: DefineDefaultView (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (this, 
				SELECTIDENTSDLG, IDL_IDENTSLIST);
	if (pDlg == NULL) return false;
	
	pDlg -> SetCaption (ResString (IDS_DEFAULTVIEWCAP, 80));
	pDlg -> Show (Centre);

	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	CTable t(DBO().Idents().IdentTree());	// Navigator für Sicht
	VisInfo *pVI[4];
	long lIdent = -1L;
	short iOTyp = 0;
		
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
			// Farben aus aktuellen Sicht lesen
				if (t.Find(&lIdent)) {
				// VisInfo aus Speicher holen
				CIdentifikatorLock l(t);

					if (!l) continue;
					l -> GetCompleteVisInfo ((VisInfo **)pVI, iOTyp);
				}
			
			// Farben in geforderte Sicht wegschreiben
				if (SetCompleteDefaultVisInfo (DBO().DB(), lIdent, (VisInfo **)pVI, iOTyp) != EC_OKAY)
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}
	}

return true;
}

#endif // WIN32

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
	InitWndScrollBars ();	// ScrollBars setzen

	if (OverViewCFlag && pOverView) {	// Übersichtsfenster
	Rectangle rcC = CanvasRect();
	ObjContainer OC (rcC);
			
		pOverView -> SetActVP (OC);
	}

return true;
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
			return false;
	}

return true;
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
			return (l -> DB().DBDesc());
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

return (DBO(iOldIndex).DB().DBDesc());
}


///////////////////////////////////////////////////////////////////////////////
//
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

