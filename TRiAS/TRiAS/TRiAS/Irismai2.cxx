// IRIS - Mainprogramm -- Version fuer Win32 ----------------------------------
// File: IRISMAI2.CXX

#include "triaspre.hxx"

#include <shlobj.h>

#include <TransEx.h>
#include <new>

#include <ole2ver.h>
#include <fnamestr.h>
#include <printer.hxx>
#include <ospace/file/path.h>
#include <ScopeVar.h>
#include <TRiASMode.h>
#include <Esnecil.h>

#include <dirisole.h>
#include <funcs02.h>

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
#include "SignOnDlg.h"
#include "overview.hxx"
#include "selectid.hxx"
#include "selnview.hxx"
#if !defined(_OLD_DRAGNDROP)
#include "viewdrop.h"
#endif // !_OLD_DRAGNDROP

#include <prntpars.hxx>
#include <registry.hxx>

#include <regprop.hxx>
#include "cordprop.hxx"

#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

CLASSFACTORY_CACHE_BEGIN(ClassFactories)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSRectangleGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPointGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPoint)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSBoundaryGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPolygonGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPolylineGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSLineGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSTextPointGeometry)
CLASSFACTORY_CACHE_END()

///////////////////////////////////////////////////////////////////////////////
//
VisType VMskToVTyp (short iVMsk, short iMsk);
int ShowCreateNewDBDialog (pWindow pW, string &strDBName, string &strUserName, string &strPWD);
HRESULT CreateShortCut (LPCSTR pszShortcutFile, LPCSTR pszLink, LPCSTR pszDesc);
void InitWindowsVersion (void);

///////////////////////////////////////////////////////////////////////////////
// 
#if _TRiAS_VER < 0x0400
DWORD g_dwVer4 = 0;
#endif // _TRiAS_VER < 0x0400

#if _TRiAS_VER < 0x0510
DWORD g_dwVer51 = 0;
#endif // _TRiAS_VER < 0x0510

#if defined(_DEBUG)
bool g_fGlobalLic = false;
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
//
ExtDirisWindow *CurrActDirisW = NULL;	// derzeit aktives Datenfenster

App *g_pCurrApp = NULL;					// aktuelle Programminstanz
short GCancelFlag = GCFNormal;			// General Cancel Flag

// Variablen für die Hilfeverwaltung
HelpDisplay *IrisHD = NULL;
bool wasHelpEvt = false;

int g_iActTool = NUMARROW;

CLegendeClientWindow *pLegende = NULL;		// Legende
bool LegendeCFlag = false;					// Legende angezeigt
bool LegendToRepaint = false;

COverViewClientWindow *pOverView = NULL;	// Übersichtsanzeige
bool OverViewCFlag = false;

bool PrintEFlag = true;                 // Drucken

#if !defined(NOPROJEKTION)
bool GeographicCFlag = true;            // geografische Koordinaten
bool WorldCFlag = false;                // Weltprojektion
#endif

//bool inzFlag = false;                   // aktuelle DB ist verschnitten
bool g_fDrawTextObjs = true;			// TextObjekte zeichnen

///////////////////////////////////////////////////////////////////////////////
// Enable-Fags für MenuPunkte 
bool g_fCloseEFlag = false;				// Projekt schlieáen
bool EditHeaderEFlag = false;           // DB-Header editieren
bool DrawEFlag = false;                 // Geometrie neu zeichnen
bool IdentSelEFlag = false;             // IdentifikatorSelektion

// Timer für Sepichern alle x Minuten
extern short g_iMinutes;
extern short g_iTicks;

DWORD g_iHideFlags = RODefaultFlags;	// was soll ausgeblendet werden

short g_iSignOnTicks = 0;
CSignOnDlg *g_pSODlg = NULL;			// SignOnDlg

bool g_fPendingSave = false;			// Speichern muß gemacht werden
bool g_fPendingReReadCaption = false;	// ReReadCaption notwendig

Timer *g_pT = NULL;

DWORD g_dwMenu = 0L;						// Menu's selbst behandeln
#if defined(_FORCE_LEGACY_CODE)
extern bool g_fFilters;					// Exportfilter installiert
#endif // defined(_FORCE_LEGACY_CODE)

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

///////////////////////////////////////////////////////////////////////////////
// Analysieren der Kommandozeile 

// Variablen, die vordefinierte DB eröffnen 
namespace {
	char *s_pToOpenDBName = NULL;		// DBName
	char *s_pToOpenUserName = NULL;		// NutzerName
	bool s_fToOpenROMode = false;		// Read/Only - Mode
	bool s_fStandardSight = false;		// StandardSicht aktivieren
#if defined(_USE_CTL3D)
	bool s_fToInit3d = true;			// CTL3D verwenden
#endif // defined(_USE_CTL3D)
	bool s_fToShow = true;				// Haupfenster anzeigen
	bool s_fSignOn = true;				// SignOn anzeigen

	bool s_fSilentReg = false;			// Fertigmeldung nach /regserver bzw. /unregserver
	bool s_fFullUninstall = false;		// unregserver:full
	bool s_fRegServer = false;			// selfregistering
	bool s_fFullRegServer = false;		// full selfregistering
	bool s_fRegServerSetup = false;		// RegServer im Setup
	bool s_fRegServerCont = false;		// RegServer im Setup und weitermachen
#if _TRiAS_VER < 0x0400
	bool s_fRegisterAsDemo = false;		// als Demovariante registrieren
#endif // _TRiAS_VER < 0x0400
	bool s_fUnRegServer = false;		// and unregistering
	bool s_fInitDB = false;				// DB anlegen und exit
	bool s_fInitDBInteractive = false;	// GeoDB-Namen abfragen
	bool s_fInitDBDesktop = false;		// DB auf Desktop ablegen
	bool s_fConvertRis = false;			// Ris --> Riw gefordert
	bool s_fTRiASNameGiven = false;		// TRiASName auf CommandLine gegeben
} // namespace

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
						s_fRegServer = true;
						if (NPOS != strCmd.find("ADMIN"))
							s_fFullRegServer = true;
						if (NPOS != strCmd.find("SILENT"))
							s_fSilentReg = true;
						if (NPOS != strCmd.find("SETUP"))
							s_fRegServerSetup = true;
						if (NPOS != strCmd.find("CONTINUE"))
							s_fRegServerCont = true;
#if _TRiAS_VER < 0x0400
						if (NPOS != strCmd.find("DEMOREGNUM"))
							s_fRegisterAsDemo = true;
#endif // _TRiAS_VER < 0x0400
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
						s_fInitDB = true;
						if (NPOS != strCmd.find("ASK"))
							s_fInitDBInteractive = true;
						if (NPOS != strCmd.find("NOSHORTCUT"))
							s_fInitDBDesktop = true;
					}
				}
				break;

#if defined(WIN16)
			case '3':
				s_fToInit3d = false;
				break;
#endif // WIN16
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

			case 'f':
			case 'F':
				{
				string strCmd = strupr(p-1);

					s_fTRiASNameGiven = (NPOS != strCmd.find ("FAKETRIASNAME"));
					if (s_fTRiASNameGiven) {
					int iPos = strCmd.find (g_cbColon);

						if (NPOS != iPos && strlen(&p[iPos]) > 0)
							strcpy (g_cbTRiAS, &p[iPos]);
						else
							s_fTRiASNameGiven = false;	// war doch nichts
					}
				}
				break;

			case 'c':
			case 'C':
				s_fConvertRis = !strcmp (strupr(p-1), "CONVERT");
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
				g_dwMenu = HANDLEMENU_MainMenu;		// MeinMenu nicht anzeigen
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
					s_fUnRegServer = (NPOS != strCmd.find ("UNREGSERVER"));
					if (s_fUnRegServer) {
						if (NPOS != strCmd.find("SILENT"))
							s_fSilentReg = true;
						if (NPOS != strCmd.find("FULL"))
							s_fFullUninstall = true;
						break;
					}

				// ansonsten UserName
					if (s_pToOpenUserName == NULL) {
						s_pToOpenUserName = new char [strlen(p) +5];
						if (s_pToOpenUserName == NULL) {
							db_error (EC_NOMEMORY, RC_ParseCmdString);
							DELETE_OBJ (s_pToOpenDBName);
							return false;
						}
						strcpy (s_pToOpenUserName, p);
						strlwr (s_pToOpenUserName);
					}
				}
				break;

			default:
				PrintUsage ();
				DELETE_OBJ (s_pToOpenDBName);
			}
		} else if (s_pToOpenDBName == NULL) {
		/* ASCII-Dateiname */
			s_pToOpenDBName = new char [strlen(p) +5];
			if (s_pToOpenDBName == NULL) {
				db_error (EC_NOMEMORY, RC_ParseCmdString);
				return false;
			}
			strcpy (s_pToOpenDBName, p);
		} else {
		/* ungueltiger Parameter */
			PrintUsage ();
			DELETE_OBJ (s_pToOpenDBName);
			return false;
		}
	}

// überprüfen, ob Extension gegeben ist, wenn nicht, dann Standard setzen
	if (s_pToOpenDBName != NULL) {
	os_path path = os_string(s_pToOpenDBName);

		if (!path.has_extension())
			path.extension (os_string(ResString (IDS_RISEXT, 6)+1));

		strcpy (s_pToOpenDBName, (LPCSTR)path);
	}

// wenn kein Nutzername gegeben ist, dann default USER generieren
	if (s_pToOpenDBName != NULL && s_pToOpenUserName == NULL) {
	char *pUserName = new char [_MAX_FNAME];

		_splitpath (s_pToOpenDBName, NULL, NULL, pUserName, NULL);
		if (s_pToOpenUserName == NULL || pUserName == NULL) {
			s_pToOpenUserName = new char [strlen(p) +5];
			if (s_pToOpenUserName == NULL) {
				db_error (EC_NOMEMORY, RC_ParseCmdString);
				DELETE_OBJ (s_pToOpenDBName);
				DELETE_OBJ (pUserName);
				return false;
			}
			strcpy (s_pToOpenUserName, pUserName);
			strlwr (s_pToOpenUserName);
		}
		DELETE_OBJ (pUserName);
	}

	if (s_fInitDB && !s_fInitDBDesktop && 
	    !s_fInitDBInteractive && NULL == s_pToOpenDBName) 
	{
		PrintUsage ();
		return false;
	}

return true;
}


// Hauptprogramm --------------------------------------------------------------
#if defined(_USE_CTL3D)
bool g_fCtl3dInit = false;
#endif // defined(_USE_CTL3D)
bool g_fOleInitialized = false;

static bool InitOle (void);

CFreeStore *App::InitApp (CFreeStore *pFS)
{
// OLE2.0 initialisieren
	if (!InitOle()) return NULL;		// InitialisierungsFehler
	
return pFS;
}


void App::DeInitApp (void)
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
		VMessageBox (NULL, FakeTRiASName(IDS_BADOLEVERSIONCAP, g_cbTRiAS).c_str(),
					ExclamationIcon|OkayButton, IDS_NOWIN40, g_cbTRiAS);
		return;		// nur unter 4.0
	}

string strDBName;
char cbBuffer[_MAX_PATH];

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{		// Pfad der DeskTop-Dateien finden
	CCurrentUser regDT (TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"));
	DWORD dw = sizeof(cbBuffer);

		regDT.GetSubSZ (TEXT("Desktop"), cbBuffer, dw);
	}

string strDeskTop(cbBuffer);

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
			if (pIStorage) {
				pIStorage -> Commit (STGC_DEFAULT);
				pIStorage -> Release();
			}
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
	DELETE_OBJ(s_pToOpenDBName);
}

#if defined(_DEBUG)
#include <crtdbg.h>
#endif // _DEBUG

//BOOL AmIAdministrator (void)
//{
//// Plagerized from Microsoft Knowledge Base article Q118626
//HANDLE access_token_handle = NULL;
//BYTE buffer[1024];
//PTOKEN_GROUPS token_groups_p = (PTOKEN_GROUPS) buffer;
//DWORD buffer_size = 0;
//
//	if (!OpenThreadToken (GetCurrentThread(), TOKEN_QUERY, TRUE, &access_token_handle)) {
//		if (ERROR_NO_TOKEN != GetLastError())
//			return FALSE;
//
//	// retry against process token if no thread token exists
//		if (!OpenProcessToken (GetCurrentProcess(), TOKEN_QUERY, &access_token_handle))
//			return FALSE;
//	}
//
//BOOL success = GetTokenInformation (access_token_handle, TokenGroups, buffer, 1024, &buffer_size);
//
//	CloseHandle (access_token_handle);
//	access_token_handle = NULL;
//	if (!success)
//		return FALSE;
//
//SID_IDENTIFIER_AUTHORITY nt_authority_sid = SECURITY_NT_AUTHORITY;
//PSID administrators_sid_p = NULL;
//
//	if (!AllocateAndInitializeSid (&nt_authority_sid, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &administrators_sid_p))
//		return FALSE;
//
//// assume that we don't find the admin SID.
//	success = FALSE;
//	for (UINT x = 0; x < token_groups_p->GroupCount; x++)
//	{
//		if (!EqualSid (administrators_sid_p, token_groups_p->Groups[x].Sid)) {
//			success = TRUE;
//			break;
//		}
//	}
//	FreeSid (administrators_sid_p);
//	return success;
//}

#if _TRiAS_VER < 0x0510
namespace {
	bool IsLicencedForInternalUse()
	{
		return m_esnecil.VerifyLevel(CKILEVEL_PLUS) && 
			m_esnecil.VerifyOptions(CKIOPTION_INTERNAL_FEATURES);
	}
}
#endif // _TRiAS_VER < 0x0510

void App::Start (const int argc, const char *argv[]) 
{
#if !defined(ENABLE_WIN32_CODE)
	if (IsWin32s()) {
		VMessageBox (NULL, IDS_BADOLEVERSIONCAP, 
					ExclamationIcon|OkayButton, IDS_NOTFORWIN32, g_cbTRiAS, g_cbTRiAS);
		return;
	}
#endif
//	if (IsWinNT() && !AmIAdministrator()) {
//		VMessageBox (NULL, IDS_BADOLEVERSIONCAP, 
//					ExclamationIcon|OkayButton, IDS_NOADMIN, g_cbTRiAS, g_cbTRiAS);
//		return;
//	}

// und jetzt gehts erst richtig los
	hInstance = Handle (API_APP_HAPP);  // ApplikationHandle speichern
	_Module.Init (NULL, hInstance);	// _ATL_CODE
	ClassFactoryCacheInit(GetClassFactories());

#if defined(_DEBUG)
DWORD dwShowSignOnTopMost = true;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegConfig);
	DWORD dwHaltOnStartup = 0;

		regCfg.GetDWORD (TEXT("HaltOnStartup"), dwHaltOnStartup);
		_ASSERTE(0 == dwHaltOnStartup);	// bei Bedarf sofort nach dem Start anhalten

	DWORD dwMemDbg = _CrtSetDbgFlag (_CRTDBG_REPORT_FLAG);
	DWORD dwNewMemDbg = 0;

		if (regCfg.GetDWORD (TEXT("UseCrtMemDbgFlag"), dwNewMemDbg) && dwNewMemDbg) {
			if (regCfg.GetDWORD (TEXT("CrtMemDbgFlag"), dwNewMemDbg))
				_CrtSetDbgFlag (dwMemDbg|dwNewMemDbg);
		}

		regCfg.GetDWORD (TEXT("ShowSignOnTopMost"), dwShowSignOnTopMost);

	// globale Lizensierung überprüfen
	DWORD dwLic = 0;

		regCfg.GetDWORD (TEXT("GlobalLicense"), dwLic);
		g_fGlobalLic = dwLic ? true : false;
	}
#endif // _DEBUG

// sonstige Initialisierungen
bool fParsed = ParseCmdString (argc, argv);

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

#if _TRiAS_VER < 0x0400
		g_dwVer4 = 0;
		regCfg.GetDWORD("FakeTRiAS4", g_dwVer4);			// TRiAS4 heißt eben 'TRiAS' !
#endif // _TRiAS_VER < 0x0400
#if _TRiAS_VER < 0x0510
		g_dwVer51 = 0;
		regCfg.GetDWORD("FakeTRiAS51", g_dwVer51);			// TRiAS5.1
#endif // _TRiAS_VER < 0x0510

// TRiASMode einlesen
		g_dwTRiASMode = 
				TRIASMODE_SubClassTRiAS | 
				TRIASMODE_HookTRiAS | 
				TRIASMODE_SubClassTRiASView |
				TRIASMODE_InterTRiAS;
#if _TRiAS_VER >= 0x0300
				g_dwTRiASMode |= TRIASMODE_GDO;
#endif // _TRiAS_VER >= 0x0300
#if _TRiAS_VER < 0x0400
				if (0 != g_dwVer4)
#endif // _TRiAS_VER >= 0x0400
					g_dwTRiASMode |= TRIASMODE_RollUpORWnds;

		regCfg.GetDWORD (g_cbTRiASMode, g_dwTRiASMode);
		if (QMSysAdmin & DEX_QueryMode())
			g_dwTRiASMode |= TRIASMODE_GDO;

	// Namen ändern/initialisieren
	DWORD dwSize = _MAX_PATH;

		if (s_fRegServer || !regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize)) {
			if (!s_fTRiASNameGiven || !s_fRegServer) {		// -FAKETRIASNAME:Name nur gemeinsam mit -REGSERVER
			// TRiASName ist nicht auf CommandLine gegeben
#if _TRiAS_VER < 0x0400
				if ((g_dwTRiASMode & TRIASMODE_InterTRiAS) && 0 == g_dwVer4)
					strcpy (g_cbTRiAS, g_cbCopyrightNameT);		// default: InterTRiAS
				else
#endif // _TRiAS_VER < 0x0400
					strcpy (g_cbTRiAS, g_cbCopyrightName);		// default: TRiAS
			}

		// für alle Erweiterungen hier wegschreiben
			regCfg.SetSubSZ (g_cbTRiASName, g_cbTRiAS);
		}
	}

// wenn GeoDB angelegt werden soll, dann selbiges tun und wieder raus
	if (s_fInitDB) {
		if (fParsed)
			GenerateNewFile (s_fInitDBInteractive, s_fInitDBDesktop);
		return;
	}

// verhindern, daß PostQuitMessage(0) gerufen wird, wenn Fenster zugehen
	SetQuitOnLast (false);

#if defined(_USE_CTL3D)
// CTL3D initialisieren
	if (IsWin40()) {
		s_fToInit3d = false;		// Win95 & WinNT40 keine CTL3D verwenden
		g_fCtl3dInit = false;
	}
	if (s_fToInit3d && (g_fCtl3dInit = Ctl3dRegister (hInstance)))
		Ctl3dAutoSubclass (hInstance);
#endif // defined(_USE_CTL3D)

// wenn nur selfregistering bzw. unregistering, dann selbiges tun und wieder raus
	if (s_fRegServer) {	
		TriasRegInit (true, s_fFullRegServer, 
			(s_fSilentReg||!s_fToShow), (s_fRegServerSetup||s_fRegServerCont));
#if _TRiAS_VER < 0x0400
		if (s_fRegisterAsDemo)
			RegisterDemoRegNum();
#endif // _TRiAS_VER < 0x0400

		if (!s_fRegServerCont)
			return;
	}
	if (s_fUnRegServer) {
		TriasRegUnInit((s_fSilentReg || !s_fToShow), s_fFullUninstall);
		return;
	}

///////////////////////////////////////////////////////////////////////////////
// Env testen, Registry nachführen etc.
Rectangle MWnd;							// FensterGröße
BOOL IF = FALSE, ZF = FALSE;            // IconicFlag und ZoomedFlag

#if defined(_FORCE_LEGACY_CODE)
	if (!TestEnv (Handle (API_APP_HAPP)))
		return;                 // Umgebungsbedingungen stimmen nicht
#endif // defined(_FORCE_LEGACY_CODE)

	if (!InitIrisApp (MWnd, ZF, IF))	// diverse Initialisierungen
		return;                 // irgend was stimmt nicht, also raus

#if _TRiAS_VER < 0x0510
// ggf. in Registry vermerken, daß wir eigentlich TRiAS6 sind
#if defined(_DEBUG)
	if (0 == g_dwVer51 && (IsLicencedForInternalUse() || g_fGlobalLic)) {
#else
	if (0 == g_dwVer51 && IsLicencedForInternalUse()) {
#endif
	CCurrentUser regCfg (g_cbRegConfig);

		regCfg.SetDWORD("FakeTRiAS51", 1);
		g_dwVer51 = 1;
	}
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// hier geht's richtig los
	g_pSODlg = NULL;

	if (s_fToShow && s_fSignOn) {
		g_pSODlg = CSignOnDlg::CreateInstance (NULL, hInstance);
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
//			g_pSODlg -> PlaySound16();
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

#if defined(_USE_CTL3D)
	MainWindow.FToInit3d (s_fToInit3d);
#else
	MainWindow.FToInit3d (false);
#endif // defined(_USE_CTL3D)
	MainWindow.FToShow (s_fToShow);

	CurrActDirisW = &MainWindow;	// HauptFenster merken

///////////////////////////////////////////////////////////////////////////////
// DockingFenster anmelden
	CLegendeWindow::RegisterTabWindow();
	COverView::RegisterTabWindow();

// PreTranslateMsgproc anbinden, damit in ORFenster Acceleratoren funktionieren
//	g_pPreTransMsgProcChain = DEX_AttachPreTranslateMsgProc (App_PreTranslateMessage);

// Help aktivieren
	{
	os_path path = os_string(argv[0]);

		path.base (os_string(g_cbNil));
		path.extension (os_string(g_cbNil));
		strcpy (g_cbHelpPath, (LPCSTR)path);

		path.base (os_string(ResString (IDS_HELPFILE, _MAX_FNAME)));
		path.extension (os_string(ResString (IDS_HELPEXT, _MAX_EXT)+1));

		wasHelpEvt = false;
		TX_TRY(IrisHD = new HelpDisplay (LPCSTR(path)));
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
										// für Blinken der aktiven Objekte

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

// nachfragen, ob jemand die Menues behandeln will
	g_dwMenu = DEXN_MenuesHandled();

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

#if defined(_FORCE_LEGACY_CODE)
		// Projekt öffnen, Fenster anzeigen etc.
			if (MainWindow.CreateView (s_pToOpenDBName, s_pToOpenUserName, 
									   g_cbNil, gfMode))
			{
				DELETE_OBJ (g_pSODlg);		// SignOn ausblenden
			} else
				MainWindow.InitMenues();
#else
			DELETE_OBJ (g_pSODlg);			// SignOn ausblenden (für alle Fälle)

			if (s_fConvertRis) gfMode |= OM_ConvertRisOnTheFly;

		TRIAS_OPEN TO;

			INITSTRUCT(TO, TRIAS_OPEN);
			TO.lpProject = s_pToOpenDBName;
			TO.lpUser = s_pToOpenUserName;
			TO.iMode = gfMode;
			DEX_OpenProject(TO);
#endif // defined(_FORCE_LEGACY_CODE)
		} 
		else {	
		// Hauptfenster anzeigen, oder eben auch nicht
			MainWindow.InitMenues();

		// Tips of the Day nur anzeigen lassen, wenn Trias sichtbar ist
		DWORD dwTOTD = s_fToShow ? (g_fTip ? TOTD_ForceTips : TOTD_LookAtRegistry) : TOTD_ForceNoTips;

			g_fTip = DEXN_TipOfTheDay (dwTOTD);
			if (g_fTip) {
				DELETE_OBJ (g_pSODlg);	// SignOn ausblenden, wenn TipOfTheDay gefordert
			}
			MainWindow.Show ((ShowState)(MainWindow.FToShow() ? MSF : HideWindow));
		}

		DELETE_OBJ (s_pToOpenDBName);
		DELETE_OBJ (s_pToOpenUserName);

	// normale Arbeit
		MainWindow.DoExec();
	}

// Timer wieder abschalten
	DELETE_OBJ (g_pSODlg);	// für alle Fälle: SignOn ausblenden
	MainWindow.CancelStrobe (&Timer1);

	if (g_pT) {
		MainWindow.CancelStrobe (g_pT);
		delete g_pT;
	}

#if defined(OLD_TOOLBOX)
	DELETE_OBJ (pToolBox);
#endif // OLD_TOOLBOX
	DELETE_OBJ (IrisHD);

#if defined(_USE_CTL3D)
// CTL3D freigeben
	if (g_fCtl3dInit) Ctl3dUnregister (hInstance);
#endif // defined(_USE_CTL3D)

#if defined(_FORCE_LEGACY_CODE)
// alle noch offenen Datenbanken schließen
	CleanUpTrias01();
#endif // defined(_FORCE_LEGACY_CODE)

	CleanUpTrias02();
	ClassFactoryCacheTerm(GetClassFactories());
	_Module.Term();					// _ATL_CODE
}

///////////////////////////////////////////////////////////////////////////////
// HauptMessageSchleife
void ExtDirisWindow::DoExec (void)
{
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
}

//////////////////////////////////////////////////////////////////////////////
// ViewFenster
#if defined(_USE_LEGACY_CODE)
IrisWind *IrisWind::CreateInstance (ExtDirisWindow *pFrame, IrisWind *& rpView,
	LPCSTR pcDBName, LPCSTR pcUserName, LPCSTR pcPassWord, short gfMode, DWORD dwMode) 
{
IrisWind *pView = NULL;

	TX_TRY(pView = new IrisWind (pFrame));
	if (NULL == pView) return NULL;

	rpView = pView;		// schon mal vorab setzen
	if (!pView -> FInit (pFrame, pcDBName, pcUserName, pcPassWord, gfMode, dwMode)) 
	{
		pView -> CloseDB (false);	// alles wieder schließen
		delete pView;
		return NULL;
	}

	return pView;
}
#endif // defined(_USE_LEGACY_CODE)

IrisWind *IrisWind::CreateInstance (
	ExtDirisWindow *pFrame, IrisWind *& rpView, BSTR bstrName)
{
IrisWind *pView = NULL;

	TX_TRY(pView = new IrisWind (pFrame));
	if (NULL == pView) return NULL;

	rpView = pView;		// schon mal vorab setzen
	if (!pView -> FInit (bstrName)) 
	{
		pView -> CloseDB (false);	// alles wieder schließen
		delete pView;
		return NULL;
	}

	return pView;
}

#if defined(_USE_LEGACY_CODE)
bool IrisWind::FInit (ExtDirisWindow *pFrame, 
	LPCSTR pcDBName, LPCSTR pcUserName, LPCSTR pcPassWord, short gfMode, DWORD dwMode)
{
#if !defined(_OLD_DRAGNDROP)
// kritische VariablenInitialisierungen
// anlegen und registrieren des DropTargets
CComObject<CViewDropTarget> *pTarget = NULL;

	try {
		THROW_FAILED_HRESULT(CComObject<CViewDropTarget>::CreateInstance(&pTarget));
		THROW_FAILED_HRESULT(pTarget -> QueryInterface (IID_IDropTarget, (LPVOID *)&m_pDropTgt));

		pTarget -> FInit (this, this);
		CoLockObjectExternal (m_pDropTgt, true, false);
		RegisterDragDrop (Handle(API_WINDOW_HWND), m_pDropTgt);

	} catch (_com_error&) {
		DELETE_OBJ(pTarget);
		m_pDropTgt = NULL;
		TX_TRACE("TRiAS: Could not initialize DropTarget for View\n");
		// no target, no Drag'n Drop
	}
#endif // !_OLD_DRAGNDROP

// Liste der DatenBasisObjekte bilden
	TX_TRY(m_pDBOs = new CDBOArray);
	if (NULL == m_pDBOs) return false;

// HintergrundBrush bilden und aktivieren        
	TX_TRY(_IrisBGBrush = new Brush (Color ((Colors)192,(Colors)192,(Colors)192)));
	TX_TRY(_emptyBrush = new Brush (HollowBrush));
	if (NULL == _IrisBGBrush || NULL == _emptyBrush) return false;

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
	_ASSERTE(m_pDBOs -> Count() && (DBO().IsTRiASDBBased() || DBO().DB().isOpened())); 

	pFrame -> InitProjectMenu();			// Menu auf Dokument einstellen

	m_fCleanedUp = false;		// erfolgreich initialisiert
	return true;
}
#endif // defined(_USE_LEGACY_CODE)

// kritische VariablenInitialisierungen
bool IrisWind::FInit (BSTR bstrName)
{
#if !defined(_OLD_DRAGNDROP)
// anlegen und registrieren des DropTargets
CComObject<CViewDropTarget> *pTarget = NULL;

	try {
		THROW_FAILED_HRESULT(CComObject<CViewDropTarget>::CreateInstance(&pTarget));
		THROW_FAILED_HRESULT(pTarget -> QueryInterface (IID_IDropTarget, (LPVOID *)&m_pDropTgt));

		pTarget -> FInit (this, this);
		CoLockObjectExternal (m_pDropTgt, true, false);
		RegisterDragDrop (Handle(API_WINDOW_HWND), m_pDropTgt);

	} catch (_com_error&) {
		DELETE_OBJ(pTarget);
		m_pDropTgt = NULL;
		TX_TRACE("TRiAS: Could not initialize DropTarget for View\n");
		// no target, no Drag'n Drop
	}
#endif // !_OLD_DRAGNDROP

// Liste der DatenBasisObjekte bilden
	TX_TRY(m_pDBOs = new CDBOArray);
	if (NULL == m_pDBOs) return false;

// HintergrundBrush bilden und aktivieren        
	TX_TRY(_IrisBGBrush = new Brush (Color ((Colors)192,(Colors)192,(Colors)192)));
	TX_TRY(_emptyBrush = new Brush (HollowBrush));
	if (NULL == _IrisBGBrush || NULL == _emptyBrush) return false;
	ChangeBackground (_IrisBGBrush);        // Hintergrund setzen

	return true;
}

// zweite Stufe der Initialisierung, nach erfolgreichem Öffnen aller Connections
bool IrisWind::InitializeView (
	ExtDirisWindow *pFrame, ITRiASProject *pIPrj, OPENMODE rgMode)
{
// entsprechend Vorgaben Dokument eröffnen bzw. erzeugen
	if (FAILED(OpenDB (pIPrj, rgMode)))
		return false;

// wurde wirklich geöffnet
//	_ASSERTE(m_pDBOs -> Count() && DBO().DB().isOpened());
	pFrame -> InitProjectMenu();			// Menu auf Dokument einstellen

	m_fCleanedUp = false;					// erfolgreich initialisiert
	return true;
}

// Konstruktor für Hauptfenster
IrisWind::IrisWind (ExtDirisWindow *pFrame)
	: ChildAppWindow (pFrame, ID_TRIASVIEW_GEODB, (LPSTR)g_cbViewClass,	IsWin40() ? WS_EX_CLIENTEDGE : 0)
{
//	EnableBorder (NonSizingBorder);
	m_pPD = NULL;
	m_pDBOs = NULL;
	_IrisBGBrush = NULL;
	_emptyBrush = NULL;

// MouseBttnSupport etc.
	m_iLeftButtonSem = 0;
	m_iRightButtonSem = 0;
	m_fTrackObjectMenuFlag = false;

// Flags initialisieren
	m_fFirstDrawing = false;
	m_fFullRedrawOnScroll = false;
	m_fHandleCancelMode = false;
	m_fReReadCaption = false;
	m_fCommitOnClose = false;
	m_fCleanedUp = true;					// don't send notification on failure
	m_fIsClosing = false;
	m_fPreventRepaint = false;

	m_fHasAspectRatio = false;
	AspectRatio = GetAspectRatio();			// AspectRatio bestimmen

	m_iDrawSem = 0;
	m_lLastIdent = -1L;
		
// sonstige lokale Parameter initialisieren
	m_fRePaintFlag = false;

	m_pWVS = EnableVScroll();				// ScrollBars initialisieren
	m_kSX = 1;
	m_pWHS = EnableHScroll();
	m_kSY = 1;

	m_lFakeZoom = 0;

	m_pDRO = NULL;							// DragRechteck initialisieren
	m_pPrinter = NULL;						// derzeit kein Printer aktiv
#if defined(_USE_FLICKERFREE_DRAWING)
	m_pMemDC = NULL;
	m_hCanvasBmp = NULL;
	m_fShouldRedraw = true;
	m_fShouldRedrawRect = false;
#endif // _USE_FLICKERFREE_DRAWING

	m_uiEditHeader = (UINT)-1;

// Stack für Vergrößerungen initialisieren
ObjContainer locOC(0, 0, 0, 0);

	actClip.Push (locOC);

	EnableHelp (true, IrisHD);				// Kontextsensitive Hilfe erlauben

#if !defined(_OLD_DRAGNDROP)
// Drag'n Drop
	m_fIsDropSource = false;
	m_pDropTgt = NULL;
#else
// Dragging initialisieren
	DragAcceptFiles (Handle (API_WINDOW_HWND), true);
#endif // _OLD_DRAGNDROP

	m_dwCookie = 0L;
	m_dwCookieViews = 0L;

// Texte editieren
	m_lTextONr = -1L;
	m_hTextMenu = NULL;
}

// Destruktor 
IrisWind::~IrisWind (void) 
{
	CleanUpView();

#if defined(_USE_FLICKERFREE_DRAWING)
	if (NULL != m_hCanvasBmp) {
		::DeleteObject (m_hCanvasBmp);
		m_hCanvasBmp = NULL;
	}
#endif // _USE_FLICKERFREE_DRAWING
	DELETE_OBJ (m_pPD);
	DELETE_OBJ (m_pDBOs);		// DatenBasisObjekt(e) freigeben

	ChangeBackground(NULL);
	DELETE_OBJ (_IrisBGBrush);	
	DELETE_OBJ (_emptyBrush);
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
void IrisWind::MenuInit (MenuInitEvt e) 
{
	if (HIWORD(e.LParam()))
		return;			// SystemMenu

//	if (!g_dwMenu) return;

// MenuPunkte vom FloatingMenu aktivieren
	if (InitTextObjectMenu()) return;

// Neu zeichnen/Abbrechen einstellen (MenuPunkt IDM_DRAW verändern)
pMenu pM = e.GetMenu();
bool fToDelete = false;

	if (NULL == pM) {
		ATLTRY(pM = new Menu (reinterpret_cast<HMENU>(e.WParam()), TRUE));
		if (NULL == pM) return;

		fToDelete = true;
	}

HMENU hMenu = pM -> Handle(API_MENU_HMENU);

	if (WM_INITMENUPOPUP == e.Msg())
		InitEditHeaderMenu (hMenu, reinterpret_cast<HMENU>(e.WParam()));	// Eigenschaften editieren richtig stellen

// Menupunkt auf Abbrechen/Neuzeichnen setzen
	ModifyMenu (hMenu, IDM_DRAW, MF_BYCOMMAND, IDM_DRAW, 
				ResString (m_iDrawSem > 0 ? IDS_CANCELDRAW : IDS_DRAW, 25));

// Checkmarks verteilen, nur wenn IrisMenu aktiv ist
DatenBasisObjekt &rDBO = DBO();
bool ifRO = !DEX_GetROModeEx(HACTPROJECT);

	MenuEnable (pM, IDM_EDITHEADER, ifRO && EditHeaderEFlag);	// Header editieren
	MenuEnable (pM, IDM_EDITDATASOURCEHEADER, ifRO && EditHeaderEFlag);	// Header editieren
	MenuEnable (pM, IDM_DRAW, DrawEFlag);						// Geometrie zeichnen
	MenuEnable (pM, IDM_SELOBJ, ifRO && IdentSelEFlag);			// Id-Selektion

	MenuEnable (pM, IDM_PRINT, PrintEFlag);         // Drucken

//#if !defined(_DEBUG)
//	MenuEnable (pM, IDM_COPYTOCLIPBOARD, m_pDRO != NULL && m_pDRO -> isValidDragObject());
//#endif // !_DEBUG
BOOL fLegendVisible = TRUE;
BOOL fOverViewVisible = TRUE;
BOOL fMayOpenLegend = DEX_MayOpenLegend();
BOOL fMayOpenOverview = DEX_MayOpenOverview();

	DEX_IsProjectBarVisible(fLegendVisible);
	DEX_IsOverViewBarVisible(fOverViewVisible);
	MenuCheck (pM, IDM_LEGENDE, LegendeCFlag && fLegendVisible);		// Legende
	MenuCheck (pM, IDM_OVERVIEW, OverViewCFlag && fOverViewVisible);	// GesamtÜbersicht
	MenuCheck (pM, ID_GEOVIEW_PREVENT_REPAINT, m_fPreventRepaint);		// Neuzeichnen unterbinden

// Legende/Overview aktivieren/passivieren
	MenuEnable(pM, IDM_LEGENDE, (LegendeCFlag && fLegendVisible) || fMayOpenLegend);
	MenuEnable(pM, IDM_OVERVIEW, (OverViewCFlag && fOverViewVisible) || fMayOpenOverview);

GeoDB &rDB = rDBO.DB();

//	MenuEnable (pM, IDM_TEXT, rDB.GetDBVersion() >= NEWDBVERSION);
//	MenuEnable (pM, IDM_VISTEXTOBJ, rDB.GetDBVersion() >= NEWDBVERSION);
	MenuCheck (pM, IDM_VISTEXTOBJ, g_fDrawTextObjs/*&& rDB.GetDBVersion() >= NEWDBVERSION*/);

//	MenuEnable (pM, IDM_EXPORT, g_fFilters);	// Export erlauben
	MenuEnable (pM, IDM_EXPORT, FALSE);			// Export hier unterbinden

	if (NULL != rDBO.pCT())
		MenuEnable (pM, IDM_COORDMODE, rDBO.pCT() -> CanConfig());
	else
		MenuEnable (pM, IDM_COORDMODE, FALSE);

#if defined(_FORCE_LEGACY_CODE)
	if (rDB.GetDBVersion() >= VERSION05000008) 
#endif // defined(_FORCE_LEGACY_CODE)
	{
	ObjContainer OC (0, 0, 0, 0);

		MenuEnable (pM, IDM_SELSICHTCONT, ifRO);
		MenuEnable (pM, IDM_DELSICHTCONT, ifRO && rDBO.GetSichtCont(&OC) == EC_OKAY);

	// sind wir noch in der AnfangsVergrößerung
	bool iFlag = IsInitialContainer (OC);

		MenuEnable (pM, IDM_PREVSELAUSSCHNITT, iFlag);
		MenuEnable (pM, IDM_RESTOREVIEWCONTAINER, iFlag);
	} 
#if defined(_FORCE_LEGACY_CODE)
	else {
		MenuEnable (pM, IDM_SELSICHTCONT, false);
		MenuEnable (pM, IDM_DELSICHTCONT, false);
		MenuEnable (pM, IDM_PREVSELAUSSCHNITT, actClip.Top().isValid());
	}
#endif // defined(_FORCE_LEGACY_CODE)

// alle anderen vom ROMode abhängigen Items behandeln
	MenuEnable (pM, IDM_DELETEVIEWS, ifRO);
//	MenuEnable (pM, IDM_SAVEOPT, ifRO);
	MenuEnable (pM, IDM_SAVEDB, rDBO.isDirty());
	MenuEnable (pM, IDM_DELETEIDENTS, ifRO);
	MenuEnable (pM, IDM_MODIFYIDENTS, ifRO);
	
// wenn CompoundFile, dann SaveAs aktiv
	MenuEnable (pM, IDM_SAVEAS, rDBO.isComFile());
	MenuEnable (pM, IDM_SAVECOPYAS, rDBO.isComFile());

	if (fToDelete)
	{
		DELETE_OBJ(pM);
	}
}

///////////////////////////////////////////////////////////////////////////////
// evtl. Modifizieren des SubMenues für Header editieren
namespace {
	UINT FindMenuItem (HMENU hMenu, UINT uiID)
	{
		if (NULL == hMenu)
			return (UINT)-1L;

	UINT uiCnt = GetMenuItemCount(hMenu);

		for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
			if (uiID == GetMenuItemID (hMenu, uiLoop))
				return uiLoop;
		}
		return (UINT)-1L;		// nichts gefunden
	}
	UINT FindPopupMenuWithItem (HMENU hMenu, UINT uiID)
	{
		if (NULL == hMenu)
			return (UINT)-1L;

	UINT uiCnt = GetMenuItemCount(hMenu);

		for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
			if (MF_POPUP & GetMenuState (hMenu, uiLoop, MF_BYPOSITION)) {
			HMENU hSubMenu = GetSubMenu (hMenu, uiLoop);

				if ((UINT)-1 != FindMenuItem (hSubMenu, uiID))
					return uiLoop;
			}
		}
		return (UINT)-1L;		// nichts gefunden
	}
};

bool IrisWind::InitEditHeaderMenu (HMENU hMenu, HMENU hActMenu)
{
HMENU hSubMenu = GetSubMenu (hMenu, PROJECT_MENU_POS);

	if (NULL == hMenu)
		return false;

BOOL fFoundEditHeader = FindMenuItem (hActMenu, IDM_EDITDATASOURCEHEADER) != (UINT)-1;

	if ((UINT)-1 == m_uiEditHeader)	{	// beim ersten mal ist Originaleintrag noch drin
		m_uiEditHeader = FindMenuItem (hSubMenu, IDM_EDITHEADER);
		if ((UINT)-1 == m_uiEditHeader)
			m_uiEditHeader = FindPopupMenuWithItem (hSubMenu, IDM_EDITDATASOURCEHEADER);
	}
	_ASSERTE((UINT)-1 != m_uiEditHeader);

#if defined(_DEBUG)
	if (!(GetKeyState (VK_CONTROL) < 0) ||	// nicht Ctrl
		fFoundEditHeader)					// nicht uns selbst rauswerfen
#else
	if (!(DEX_QueryMode() & QMSysAdmin) ||	// nicht im AdminMode
		!(GetKeyState (VK_CONTROL) < 0) ||	// nicht Ctrl
		fFoundEditHeader)					// nicht uns selbst rauswerfen
#endif // defined(_DEBUG)
	{
		if (!fFoundEditHeader && (MF_POPUP & GetMenuState (hSubMenu, m_uiEditHeader, MF_BYPOSITION))) {
			DeleteMenu (hSubMenu, m_uiEditHeader, MF_BYPOSITION);
			InsertMenu (hSubMenu, m_uiEditHeader, MF_BYPOSITION|MF_STRING, IDM_EDITHEADER, ResString (IDS_EDITHEADER, 64));
		}
		return false;
	}

// einzelnen Menupunkt durch Popupmenu ersetzen
HMENU hEditMenu = CreatePopupMenu();

	AppendMenu (hEditMenu, MF_STRING, IDM_EDITDATASOURCEHEADER, ResString(IDS_EDITPROJECTHEADER, 64));

CRing r (DBO().GetGeoDBs());
char cbBuffer[_MAX_PATH];
int iCnt = 0;

	for (r.First(); r.Valid(); r.Next(), iCnt++) {
	GeoDBLock l(r);

		_ASSERTE(NULL != (GeoDB *)l);
		if (!l -> isOpened() || FAILED(l -> GetDataSourceName (cbBuffer, sizeof(cbBuffer))))
			continue;

		if (1 == iCnt)		// der 0. ist immer geschlossen
			AppendMenu (hEditMenu, MF_SEPARATOR, -1, NULL);
		AppendMenu (hEditMenu, MF_STRING, IDM_EDITDATASOURCEHEADER+iCnt, cbBuffer);
	}

	DeleteMenu (hSubMenu, m_uiEditHeader, MF_BYPOSITION);
	InsertMenu (hSubMenu, m_uiEditHeader, MF_BYPOSITION|MF_POPUP, (UINT)hEditMenu, ResString (IDS_EDITHEADERSUB, 32));
	return true;
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
	if (OverViewCFlag && pOverView) 
		pOverView -> SetActVP (CanvasRect());
	return true;
}

// Menukommandos verarbeiten --------------------------------------------------
void IrisWind::MenuCommand (MenuCommandEvt e) 
{
	BEGIN_COMMANDS(e.GetItemID()) 
		ON_COMMAND_ID(IDM_BACKGRNDCOLOR, doChangeBKColor);	// Hintergrundfarbe vorgeben (E_NOTIMPL)
		ON_COMMAND_ID(IDM_SAVEDB, doSaveDB);				// GeoDB speichern
		ON_COMMAND_ID(IDM_AUTOSAVEDB, doAutoSaveDB);		// automatisches GeoDB speichern
		ON_COMMAND_ID(IDM_SAVEAS, doSaveAsGeoDB);			// Speichern unter
		ON_COMMAND_ID(IDM_SAVECOPYAS, doExportAsGeoDB);		// Kopie Speichern als
		ON_COMMAND_ID(IDM_EDITHEADER, doEditHeader);		// Projekt-Header editieren
		ON_COMMAND_ID(IDM_EDITDATASOURCEHEADER, doEditHeader);		// Projekt-Header editieren
		ON_COMMAND_ID(IDM_SELOBJ, doShowIdentSel);			// Ansicht definieren
		ON_COMMAND_ID(IDM_DELETEVIEWS, doDeleteViews);		// Ansichten löschen
		ON_COMMAND_ID(IDM_REBUILD, doRebuild);				// Ansicht neu generieren
		ON_COMMAND_ID(IDM_DRAW, doDraw);					// neu Zeichnen
		ON_COMMAND_ID(ID_GEOVIEW_PREVENT_REPAINT, doPreventRepaint);	// neu Zeichnen unterbinden
		ON_COMMAND_ID(IDM_CANCEL, doCancel);				// allgemeiner Abbruch
		ON_COMMAND_ID(IDM_PRINT, doPrint);					// Drucken
		ON_COMMAND_ID(IDM_TEXTSEARCH_PP, doTextRech);		// RechercheParameter einstellen
		ON_COMMAND_ID(IDM_TEXTREPLACE_PP, doTextReplace);	// Suchen und Ersetzen
		ON_COMMAND_ID(IDM_CLASSIFY, doClassify);			// Klassifikation
		ON_COMMAND_ID(IDM_GENTEXTOBJECTS, doGenTextObjects);		// Textobjekte erzeugen
#if defined(OLD_COORDS)
		ON_COMMAND_ID(IDM_COORDS, doCoords);				// KoordiantenFenster anzeigen/ausblenden
#endif // OLD_COORDS
#if defined(OLD_MASSTAB)
		ON_COMMAND_ID(IDM_MASSTAB, doSelectMasstab);		// Ausschnit über Maßstab wählen
#endif // OLD_MASSTAB
//		ON_COMMAND_ID(IDM_SAVEOPT, doSaveOpt);				// SpeicherOptionen auswählen
		ON_COMMAND_ID(IDM_EXPORT, doExport);				// Daten exportieren
		ON_COMMAND_ID(IDM_SYMBOLPARS, doSymbolPars);		// Darstellungsparameter vorgeben
		ON_COMMAND_ID(IDM_PRIORITYSELECT, doPriority);		// Darstellungspriorität vorgeben
		ON_COMMAND_ID(IDM_COPYTOCLIPBOARD, doCopyClipBoard);	// ZwischenAblage bedienen
		ON_COMMAND_ID(IDM_SELSICHTCONT, doSelSichtCont);	// SichtAusschnitt vorgeben
		ON_COMMAND_ID(IDM_DELSICHTCONT, doDelSichtCont);	// Sichtausschnitt wieder löschen
		ON_COMMAND(IDM_LEGENDE, doLegende, e);				// Legende anzeigen/ausblenden
		ON_COMMAND(IDM_SHOWLEGENDE, doLegende, e);			// Legende anzeigen/ausblenden
		ON_COMMAND(IDM_OVERVIEW, doOverView, e);			// Übersicht anzeigen/ausblenden
		ON_COMMAND(IDM_SHOWOVERVIEW, doOverView, e);		// Übersicht anzeigen/ausblenden
		ON_COMMAND_ID(IDM_VISTEXTOBJ, doViewTexts);			// Textobjekte anzeigen/nicht anzeigen
		ON_COMMAND_ID(IDM_SELAUSSCHNITT, doSelAusschnitt);	// Ausschnitt auswählen
		ON_COMMAND_ID(IDM_PREVSELAUSSCHNITT, doPrevAusschnitt);	// vorhergehenden Ausschnitt wieder einstellen
		ON_COMMAND_ID(IDM_SELECTVIEWS, doSelectView);		// Ansicht über Dialog auswählen
		ON_COMMAND_ID(IDM_SIGHTS+MAXSHOWNVIEWS, doSelectView);
		ON_COMMAND_ID(IDM_ZOOMOUT, doZoomOut);				// Ausschnitt vergrößern
		ON_COMMAND_ID(IDM_ZOOMIN, doZoomIn);				// Ausschnitt verkleinern
		ON_COMMAND_ID(IDM_RESTOREVIEWCONTAINER, doRestoreContainer);	// Ausschnitt auf Anfangszustand setzen
		ON_COMMAND_ID(IDM_DELETE_OBJPROPERTIES, doDeleteObjProps);		// Objekteigenschaften löschen
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

bool IrisWind::myQueryClose (bool fForceCleanUp) 
{
	m_fCommitOnClose = false;
	DEX_SaveLegend();

bool fCommitOnClose = false;
ErrCode EC = AskUserToClose (fCommitOnClose, fForceCleanUp);

	m_fCommitOnClose = fCommitOnClose ? true : false;
	if (WC_RETURN == EC)
		return false;	// Nutzer hat gebrochen (und zwar ab)

// #HK000718: bei evtl. aufgetretenem Fehler trotzdem schließen (hier durchfallen)
// da sonst das UI blockiert wird (ständige Fehlermeldungen)
// ...

// dieses Fenster nun auch schließen
	if (DEXI_isInteractive())
		ForwardEvent (WM_CLOSE);
	return true;
}

void IrisWind::Close (Event e)
{
	if (m_pDBOs -> Count() && 
		(DBO().IsTRiASDBBased() || DBO().DB().isOpened())) 
	{	
	// DB noch eröffnet
		if (!m_fIsClosing) {
		CScopeVar<bool> fClosing (m_fIsClosing, true);

		// Projekt schließen
			if (EC_OKAY != CloseDB (m_fCommitOnClose))
				return;
		}

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
BOOL EXPORTTRIAS WINAPI AddObjectsCallback (long lONr, int iOTyp, void *pData)
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
bool IrisWind::DefineDefaultView (void)
{
CCopyVisInfoDlg *pDlg = CCopyVisInfoDlg::CreateInstance (this, 
				IDD_COPYVISINFODLG, IDL_IDENTSLIST);
	if (pDlg == NULL) return false;
	pDlg -> Show (Centre);

char cbView[MAXVIEWNAMESIZE+1];

	if (pDlg -> Result() && pDlg -> GetViewName (cbView, sizeof(cbView))) {		
	// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	CTable t(DBO().Idents().IdentTree());	// Navigator für Sicht
	VisInfo *pVI[4];
	long lIdent = -1L;
	short iOTyp = 0;

	// Info fürs übernehmen der VisInfo
	COPYVISINFO CVI;
	char cbActView[MAXVIEWNAMESIZE+1] = { '\0' };

		DBO().GetActiveSightName(cbActView, sizeof(cbActView));
		INITSTRUCT(CVI, COPYVISINFO);
		CVI.m_pTarget = cbActView;
		CVI.m_pNewName = cbView;
		
		memset (pVI, '\0', 4 * sizeof(VisInfo *));
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
			// beim ersten mal sinnlos
				DELETE_OBJ(pVI[0]);
				DELETE_OBJ(pVI[1]);
				DELETE_OBJ(pVI[2]);
				DELETE_OBJ(pVI[3]);

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
					if (EC_OKAY == DBO().SetCompleteVisInfo (cbView, lIdent, (VisInfo **)pVI, iOTyp))
						break;
				} 
				else {
					if (!DBO().RetrieveVisInfo (cbView, lIdent, VMskToVTyp(iOTyp, TPAll), NULL))
						continue;	// keine Idents hinzufügen

				// neue Vis wegschreiben
					DBO().SetCompleteVisInfo (cbView, lIdent, (VisInfo **)pVI, iOTyp);

#if defined(_USE_OBJECT_COPYVISINFO)
				// objektbezogene Visualisierung auch übernehmen
					CVI.lIdent = lIdent;
					CVI.iOTyp = BitsToOTyp(iOTyp); 
					DEXN_VisInfoCopied(CVI);
#endif // defined(_USE_OBJECT_COPYVISINFO)
				}
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));

		// wieder alles freigeben
			DELETE_OBJ(pVI[0]);
			DELETE_OBJ(pVI[1]);
			DELETE_OBJ(pVI[2]);
			DELETE_OBJ(pVI[3]);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// RegNumber auf Gültigkeit testen
#if _TRiAS_VER < 0x0400
bool IsLegalRegNumber (LPCSTR pcRegEntry);
#endif // _TRiAS_VER < 0x0400

bool IsLegalRegisteredVersion (Window *pW, UINT uiCaption)
{
#if defined(_DEBUG)
	if (g_fGlobalLic || DEX_QueryMode() & QMSysAdmin)
		return true;
#endif // defined(_DEBUG)

#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) {
	CLocalMachine regName (KEY_READ, g_cbRegVersion);
	char cbBuffer[128];
	DWORD dwLen = sizeof(cbBuffer);

		if (!regName.GetSubSZ (g_cbSerial, cbBuffer, dwLen) || !IsLegalRegNumber (cbBuffer)) {
		ResString resCap (uiCaption, 128);
		char cbBuffer[128];

			wsprintf (cbBuffer, "%s - %s", g_cbTRiAS, resCap.Addr());
			VMessageBox (pW, cbBuffer, ExclamationIcon|OkayButton, IDS_CANTDOTHAT, g_cbTRiAS);
			return false;
		}
	} else
#endif // _TRiAS_VER < 0x0400
	{
	ResString resCap (uiCaption, 128);
	VERIFYLICENSE VL;

		INITSTRUCT(VL, VERIFYLICENSE);
		VL.lLevelOrOption = CKILEVEL_DEMO;
		VL.iMode = VERIFYMODE_Equal;
		VL.pcCaption = resCap.Addr();
		VL.hWndParent = pW -> Handle(API_WINDOW_HWND);
		if (!DEX_VerifyLicenseLevel(VL))
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// MenuKommandos

// Projekt speichern ----------------------------------------------------------
bool IrisWind::doSaveDB()
{
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_SAVEDB))
		return false;

	if (m_pDBOs -> Count() &&
		(DBO().IsTRiASDBBased() || DBO().DB().isOpened()))	// überhaupt was geöffnet
	{
		if (DBO().GetTempMode())	// erstes Speichern überhaupt
			return SaveAsGeoDB();
		else {
		CEierUhr Wait(this);

			return SaveGeoDB();
		}
	}
	return false;
}

bool IrisWind::doAutoSaveDB()
{
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_SAVEDB))
		return false;

	if (m_pDBOs -> Count() &&
		(DBO().IsTRiASDBBased() || DBO().DB().isOpened()))	// überhaupt was geöffnet
	{
		_ASSERTE(!DBO().GetTempMode());		// muß bereits gespeichert sein

	CEierUhr Wait(this);

		return SaveGeoDB(true);
	}
	return false;
}

// Speichern unter ------------------------------------------------------------
bool IrisWind::doSaveAsGeoDB (void)
{
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_SAVEDBAS))
		return false;

	return SaveAsGeoDB();
}

// Kopie Speichern als --------------------------------------------------------
bool IrisWind::doExportAsGeoDB (void)
{
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_EXPORTDB))
		return false;

	return ExportAsGeoDB();
}

// Projekt Eigenschaften ------------------------------------------------------
bool IrisWind::doEditHeader (void) 
{
WTRiASProject Prj;

	DBO().GetTRiASProject (Prj.ppi());		// Fehler ignorieren
	if (ShowEditHeader(Prj, HACTPROJECT)) {
		DEX_ReReadCaption();				// evtl. Caption neu generieren
		return true;
	}
	return false;
}

DefineSmartInterface(TRiASDatabase);

bool IrisWind::doEditHeader (int iDataSource) 
{
	_ASSERTE(iDataSource > 0 && iDataSource <= 256);

WTRiASConnection Conn;
WTRiASDatabase DBase;
GeoDB &rDB = DBO().GetGeoDBs().DB(iDataSource);		// Index=0 ist dummy GeoDB

	if (FAILED(rDB.GetConnection (Conn.ppi())) || 
		FAILED(Conn -> get_Database (DBase.ppi()))) 
	{
		_ASSERTE(FALSE);
		return false;
	}
	if (ShowEditHeader(DBase, rDB.DBDesc())) {
		DEX_ReReadCaption();				// evtl. Caption neu generieren
		return true;
	}
	return false;
}

// Ansichten zusammenstellen --------------------------------------------------
bool IrisWind::doShowIdentSel (void) 
{
	return ShowIdentSel();
}

// Ansichten löschen ----------------------------------------------------------
bool IrisWind::doDeleteViews (void) 
{
	if (DeleteViews()) {
		DEX_ReReadCaption();		// evtl. Caption neu generieren
		return true;
	}
	return false;
}

// Ansicht neu generieren -----------------------------------------------------
bool IrisWind::doRebuild (HPROJECT hPr)
{
CEierUhr Wait (this);

	if (hPr == HACTCONNECTION) {
		DBO().Idents().ResetAllLoaded();		// nichts mehr geladen
		DBO().Shapes().EveryDelete();			// alle Objekte rauswerfen
	}
	DBO().ProcessMenuEvent (NULL, true, false);	// Ansicht neu einlesen
	m_fRePaintFlag = true;

// jetzt zeichnen
CScopeVar<bool> PreventRePaint (m_fPreventRepaint,  false);

	SetShouldRedraw();
	InitWndScrollBars();		// Rollbalken zuschalten
	DEX_ReReadCaption();

	RePaint();

// jetzt aktualisieren, wenn nur einmalig gezeichnet wird
	if (PreventRePaint.GetOldValue())
		Update();
	
// Overview auch neu zeichnen
	if (OverViewCFlag && pOverView) 
		pOverView -> RePaint();

	return true;
}

// Ansicht neu Zeichnen -------------------------------------------------------
bool IrisWind::doDraw (void)
{
	if (m_iDrawSem > 0) {	
	// es wird gerade gezeichnet: Abbrechen
		GCancelFlag = GCFAbort;
	} else {
	// wenn CTRL-Taste gedrückt, dann Sicht neu einlesen
		if (GetKeyState (VK_CONTROL) < 0) {
		CEierUhr Wait (this);
			
			DBO().ProcessMenuEvent (NULL, true);
		}
		m_fRePaintFlag = true;

	// jetzt zeichnen
	CScopeVar<bool> PreventRePaint (m_fPreventRepaint,  false);

#if defined(_USE_FLICKERFREE_DRAWING)
		if (g_dwDrawingMode & DRAWMODE_StoreCanvas)
			SetShouldRedraw();
#endif // _USE_FLICKERFREE_DRAWING
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
bool IrisWind::doCancel (void)
{
	GCancelFlag = GCFAbort;
	return true;
}

// ToolFenster anzeigen/ausblenden --------------------------------------------
bool IrisWind::doTools (MenuCommandEvt e) 
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
bool IrisWind::doPrint (void)
{
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_PRINT))
		return false;

char cbCaption[_MAX_PATH] = "";

	GetFrame() -> GetCaption (cbCaption, sizeof(cbCaption)-1);

	if (NULL != m_pDRO && m_pDRO -> isValidDragObject()) {
	// Ausschnitt ist selektiert: Koordinaten transformieren
	Point pt1 = ((DragRectangleObject *)m_pDRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)m_pDRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);

		return PrintGraphics (cbCaption, ObjContainer(pnt1, pnt2));
	} else {
	// aktuellen Bildschirmausschnitt verwenden
		return PrintGraphics (cbCaption, DBO().GetExtend());
	}
}

// RechercheParameter einstellen ----------------------------------------------
#if !defined(_USE_XML_GEOCOMPONENTS)
bool TextRecherche(HWND hWnd, bool fORWnd = false);
bool TextReplace(HWND hWnd, bool fORWnd = false);
bool ClassifyObjects(HWND hWnd, bool fORWnd = false);
bool GenerateTextObjects(HWND hWnd, bool fORWnd = false);

bool IrisWind::doTextRech (void)
{
	return TextRecherche(Handle(API_WINDOW_HWND));
}

///////////////////////////////////////////////////////////////////////////////
// Suchen und Ersetzen
bool IrisWind::doTextReplace (void)
{
	return TextReplace (Handle(API_WINDOW_HWND));
}

///////////////////////////////////////////////////////////////////////////////
// Klassifizieren
bool IrisWind::doClassify (void)
{
	return ClassifyObjects (Handle(API_WINDOW_HWND));
}

/////////////////////////////////////////////////////////////////////////////
// Textobjekte erzeugen
bool IrisWind::doGenTextObjects (void)
{
	return GenerateTextObjects(Handle(API_WINDOW_HWND));
}
#endif // !defined(_USE_XML_GEOCOMPONENTS)

// KoordiantenFenster anzeigen/ausblenden -------------------------------------
bool IrisWind::doCoords (void)
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
bool IrisWind::doSelectMasstab (void)
{
	return MenuSelectMasstab();
}
#endif // OLD_MASSTAB

//// SpeicherOptionen auswählen -------------------------------------------------
//bool IrisWind::doSaveOpt (void)
//{
//CSaveOptionsDlg *pSODlg = CSaveOptionsDlg::CreateInstance (this);
//
//	if (NULL == pSODlg) return false;
//
//	pSODlg -> Show();
//	if (pSODlg -> Result()) {
//		if (g_iMinutes != pSODlg -> SaveDelta()) {
//			if (g_pT) {
//				CancelStrobe (g_pT);
//				delete g_pT;
//				g_pT = NULL;
//			}
//			g_iMinutes = pSODlg -> SaveDelta();
//			if (g_iMinutes > 0) 
//				g_pT = new Timer (6000, 2);
//			if (g_pT) SetStrobe (g_pT);
//
//			g_iTicks = 0;
//		}
//	}
//	DELETE_OBJ (pSODlg);
//
//return true;
//}

// Daten exportieren ----------------------------------------------------------
bool IrisWind::doExport (void)
{
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_EXPORT))
		return false;

	if (m_pDBOs -> Count() && 
		(DBO().IsTRiASDBBased() || DBO().DB().isOpened())) 
	{
	ObjContainer OC;

		if (m_pDRO != NULL && m_pDRO -> isValidDragObject()) {	// nur selektierten Bereich
		Point pt1 = ((DragRectangleObject *)m_pDRO)->LowerLeft();
		Point pt2 = ((DragRectangleObject *)m_pDRO)->UpperRight();
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
bool IrisWind::doChangeBKColor (void)
{
	return true;		// E_NOTIMPL
}

// Darstellungsparameter vorgeben ---------------------------------------------
bool IrisWind::doSymbolPars (void)
{
// neu zeichnen abbrechen, wenn neuer Dialog erzeugt wird
bool fResult;

	m_fHandleCancelMode = true;
	fResult = (EC_OKAY == ChangeIdVisInfo());
	m_fHandleCancelMode = false;

return fResult;
}

// Darstellungspriorität vorgeben ---------------------------------------------
bool IrisWind::doPriority (void)
{
	return PrioritySelect();
}

// ZwischenAblage bedienen ----------------------------------------------------
bool IrisWind::doCopyClipBoard (void)
{
	if (m_pDRO != NULL && m_pDRO -> isValidDragObject()) {
	// selektierten Bereich kopieren
	Rectangle Rc = ((DragRectangleObject *)(DrawObject *)(*m_pDRO)) -> GetRect();

		return (EC_OKAY == DBO().CopyToClipBoard (this, Rc));
	} 
	else {
	// gesamten Bildschirmbreich kopieren
	Rectangle Rc (CanvasRect());
	CoOrd tmpC = CoOrd(Rc.Bottom() - Rc.Top());			// Koordinaten kippen
	
		Rc.Bottom() = CoOrd(Rc.Top() - tmpC);
		return (EC_OKAY == DBO().CopyToClipBoard (this, Rc));
	}
}

// SichtAusschnitt vorgeben ---------------------------------------------------
bool IrisWind::doSelSichtCont (void)
{
	if (m_pDRO != NULL && m_pDRO -> isValidDragObject()) {
	// Ausschnitt ist selektiert: Koordinaten transformieren
	Point pt1 = ((DragRectangleObject *)m_pDRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)m_pDRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);
	ObjContainer OC (pnt1, pnt2);

		OC.InflateCont (10);	// Container anpassen
		return (EC_OKAY == DBO().SetSichtCont (OC));
	} else {
	// aktuellen Bildschirmausschnitt verwenden
		return (EC_OKAY == DBO().SetSichtCont (DBO().GetExtend()));
	}
}

// Sichtausschnitt wieder löschen ---------------------------------------------
bool IrisWind::doDelSichtCont (void)
{
	return (EC_OKAY == DBO().DelSichtCont());
}

// Legende anzeigen/ausblenden ------------------------------------------------
bool IrisWind::doLegende (MenuCommandEvt e)
{
UINT uiID = e.GetItemID();

	if (IDM_LEGENDE == uiID) {
	// normales Handling
		LegendeCFlag = !LegendeCFlag;
		if (LegendeCFlag) {
		char cbCaption[SIGHTMENUITEM +1];

			if (NULL == pLegende) {
				DBO().GetActiveSightName (cbCaption, sizeof(cbCaption));
				pLegende = CLegendeWindow::CreateInstance (this, cbCaption, DBO());
			}
			if (NULL == pLegende)
				return false;
				
			LegendToRepaint = false;
		} 
		else if (pLegende) {
			pLegende -> SaveLegend();	// Legende Speichern
			LegendToRepaint = false;
			CLegendeWindow::DeleteInstance(pLegende);         // Speicher freigeben
			_ASSERTE(NULL == pLegende);
		}
	}
	else if (IDM_SHOWLEGENDE == uiID) {
	// Sonderfall, wenn Legende noch exitieren sollte, aber das Projektfenster geschlossen war
		_ASSERTE(LegendeCFlag && NULL != pLegende);		// Legende muß existieren
		pLegende -> ReShow();
	}
	else {
		_ASSERTE(IDM_LEGENDE == uiID || IDM_SHOWLEGENDE == uiID);
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Übersicht anzeigen/ausblenden/wiederanzeigen
bool IrisWind::doOverView (MenuCommandEvt e)
{
	if (0 == m_pDBOs -> Count() || 
		(!DBO().IsTRiASDBBased() && !DBO().DB().isOpened())) 
	{
		return false;
	}

UINT uiID = e.GetItemID();

	if (IDM_OVERVIEW == uiID) {
	// normales Handling
		OverViewCFlag = !OverViewCFlag;
		if (OverViewCFlag) {
			_ASSERTE(NULL != DBO().pCT());

		// bei ControlTaste Overview neu generieren
		ObjContainer OC (DBO().DBCont());
		bool fInitNew = (GetKeyState (VK_CONTROL) < 0) ? true : false;
		double dRatio = (NULL != DBO().pCT()) ? DBO().pCT() -> CoordTransAspectRatio (OC) : 1.0;

			pOverView = COverView::CreateOverView (this, OC, fInitNew, AspectRatio, dRatio, DBO());
			if (pOverView) 
				pOverView -> SetActVP (CanvasRect());
		}
		else {
			pOverView -> Hide();
			OverViewCFlag = false;
			COverView::DeleteInstance(pOverView);
			_ASSERTE(NULL == pOverView);
		}
	}
	else if (IDM_SHOWOVERVIEW == uiID) {
	// Sonderfall, wenn Overview noch exitieren sollte, aber das Projektfenster geschlossen war
		_ASSERTE(OverViewCFlag && NULL != pOverView);		// Overview muß existieren
		pOverView -> ReShow();
		pOverView -> SetActVP (CanvasRect());
	}
	else {
		_ASSERTE(IDM_OVERVIEW == uiID || IDM_SHOWOVERVIEW == uiID);
		return false;
	}
	return true;
}

// Textobjekte anzeigen/nicht anzeigen ----------------------------------------
bool IrisWind::doViewTexts (void)
{			
	g_fDrawTextObjs = !g_fDrawTextObjs;

	DBO().SetShowTexts (g_fDrawTextObjs);	// an Ansicht abspeichern
	SetShouldRedraw();
	RePaint();								// alles neu zeichnen
	return true;
}

// Ausschnitt auswählen -------------------------------------------------------
bool IrisWind::doSelAusschnitt (void)
{
	_ASSERTE(NULL != DBO().pCT());

CAusschnittsDlg *pADlg = new CAusschnittsDlg (this, DBO().pCT(), DBO().DotsPerMM());
Rectangle Rc (0, 0, 0, 0);
bool fUseRectangle = false;

	if (m_pDRO && m_pDRO -> isValidDragObject()) {
		Rc = ((DragRectangleObject *)m_pDRO) -> GetRect();
		fUseRectangle = true;
	}

	if (pADlg && pADlg -> Init (fUseRectangle ? &Rc : NULL)) {
		pADlg -> Show(Centre);
		if (pADlg -> Result()) {	// richtige Eingabe ist erfolgt
		// alten Ausschnitt merken
			actClip.Push (DBO().GetExtend());
		
		// neuen Ausschnitt einstellen
		ObjContainer ocT = pADlg -> NewRect();
		
			SetExtend (ocT);
			DELETE_OBJ (m_pDRO);

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
	DELETE_OBJ (pADlg);

return false;
}

// vorhergehenden Ausschnitt wieder einstellen --------------------------------
bool IrisWind::doPrevAusschnitt (void)
{
	if (0 == m_pDBOs -> Count() || 
		(!DBO().IsTRiASDBBased() && !DBO().DB().isOpened())) 
	{
		return false;
	}

	if (actClip.Top().isValid()) {  // gültiger Ausschnitt
	// vorhergehenden Ausschnitt einstellen
	ObjContainer OC (0, 0, 0, 0);
	ObjContainer ocT (0, 0, 0, 0);
	
		if (DBO().GetSichtCont (&OC) == EC_OKAY && OC.isValid()) {
			ocT = actClip.Top();
			if (OC > ocT) {
				actClip.Pop();
				SetExtend (ocT);
			} else if (OC < ocT) {
				if (OC > DBO().GetExtend()) 
					SetExtend (OC);
				else
					return false;
			} else {
				actClip.Pop();
				SetExtend (ocT);
			}
		} else {
		// vorhergehenden Ausschnitt einstellen
			ocT = actClip.Pop();
			SetExtend (ocT);
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
bool IrisWind::doSelectView (void)
{
	return SelectView();
}

// Halber Bildschirmausschnitt ------------------------------------------------
bool IrisWind::doZoomOut (void) 
{
	if (0 == m_pDBOs -> Count() || 
		(!DBO().IsTRiASDBBased() && !DBO().DB().isOpened())) 
	{
		return false;
	}

// wenn Ctrl gedrückt, dann vollständig zurücksetzen
	if (GetKeyState (VK_CONTROL) < 0)
		return doRestoreContainer();

ObjContainer OC = DBO().GetExtend();

	if (OC.isValid()) {
	// Bildschirmausschnitt halbieren
	KoOrd dX = (OC.XMax() - OC.XMin())/2;
	KoOrd dY = (OC.YMax() - OC.YMin())/2;
	ObjContainer ocT (OC.XMin() - dX, OC.XMax() + dX, OC.YMin() - dY, OC.YMax() + dY);
	ObjContainer ocView (0, 0, 0, 0);		// evtl. Ansichtsausschnitt
	
		if (EC_OKAY == DBO().GetSichtCont (&ocView) && ocView.isValid()) {
			if (ocView > ocT) {
			// neuen Ausschnitt einstellen (paßt vollständig in Ansichtsausschnitt)
				SetExtend (ocT);
			} 
			else if (ocView < ocT) {
			// paßt nicht mehr in Ansichtsausschnitt, also Ansichtsauschnitt verwenden
				ocT = ocView;
				SetExtend (ocView);	
			} 
			else {
			// neuen Ausschnitt einstellen
				SetExtend (ocT);
			}
		} 
		else {
		// neuen Ausschnitt einstellen
		ObjContainer ocPrj (DBO().DBCont());

			if (ocPrj > ocT)
				SetExtend (ocT);
			else {
				ocT = ocPrj;
				SetExtend (ocPrj);
			}
		}
		InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
		InitOverView (ocT);		// Übersichtsfenster

	// neu zeichnen
		m_fRePaintFlag = true;
		LegendToRepaint = true;
		RePaint();
		return true;
	}
	return false;
}

// Doppelter Bildschirmausschnitt ---------------------------------------------
bool IrisWind::doZoomIn (Punkt *pPt)
{
	if (0 == m_pDBOs -> Count() || 
		(!DBO().IsTRiASDBBased() && !DBO().DB().isOpened())) 
	{
		return false;
	}

ObjContainer OC = DBO().GetExtend();

	if (OC.isValid()) {
	// Bildschirmausschnitt halbieren
	KoOrd dXMin = OC.XMin();
	KoOrd dXMax = OC.XMax();
	KoOrd dYMin = OC.YMin();
	KoOrd dYMax = OC.YMax();
	KoOrd dX = (dXMax - dXMin)/4;
	KoOrd dY = (dYMax - dYMin)/4;

		if (NULL != pPt) {
		// neue Mittelpunktskoordinate gegeben, also alles entsprechend verschieben
		KoOrd ddX = pPt -> GetX() - (dXMax + dXMin)/2;
		KoOrd ddY = pPt -> GetY() - (dYMax + dYMin)/2;

			dXMin += ddX;
			dXMax += ddX;
			dYMin += ddY;
			dYMax += ddY;
		}

	ObjContainer ocT (dXMin + dX, dXMax - dX, dYMin + dY, dYMax - dY);
		
		if (!ocT.isValid()) 
			return false;

		if (NULL != pPt)
			actClip.Push (DBO().GetExtend());	// alten Ausschnitt merken (bei Vergrößerung über Maus)

		SetExtend (ocT);	// neuen Ausschnitt setzen		
	
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
bool IrisWind::doRestoreContainer (void)
{
// ObjContainerStack rücksetzen
	ResetObjContainerStack();

// DatenBasisObjekt Ausschnitt definieren
DatenBasisObjekt &rDBO = DBO();
ObjContainer ocT = rDBO.DBCont(true).InflateCont(10);

	SetExtend (ocT);

	if (rDBO.GetSichtCont (&ocT) == EC_OKAY && ocT.isValid()) {
	long lCont[4];
	KoOrd dX, dY;

		if (!rDBO.ScaleCTF (ocT.XMin(), ocT.YMin(), &dX, &dY))
			return false;
		lCont[0] = dX;
		lCont[2] = dY;

		if (!rDBO.ScaleCTF (ocT.XMax(), ocT.YMax(), &dX, &dY))
			return false;
		lCont[1] = dX;
		lCont[3] = dY;

		DEX_SetActiveSightContainer (lCont); 
	}

	InitWndScrollBars();	// bei Bedarf ScrollBars einblenden und initialisieren
	InitOverView(ocT);		// Übersichtsfenster

// neu zeichnen
	m_fRePaintFlag = true;
	LegendToRepaint = true;
	RePaint ();

	return true;
}

// Farben in andere Sicht übernehmen ------------------------------------------
bool IrisWind::doCopyColors (void)
{
	return DefineDefaultView();
}

// Parameter der Koordinateneinstellung vorgeben ------------------------------
extern LRESULT SelectCoordSysParams (pWindow pW, UINT uiID, DatenBasisObjekt &rDBO, CoordTrans * = NULL);

bool IrisWind::doCoordMode (void)
{
	return SelectCoordSysParams (this, IDS_COORDFMTDLGCAP, DBO(), NULL);
}

// Alles sonstige landet hier -------------------------------------------------
bool IrisWind::doDefaultCmd (MenuCommandEvt e)
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

// evtl. DatenquellenHeader editieren
	if (iItemID > IDM_EDITDATASOURCEHEADER && iItemID <= IDM_EDITDATASOURCEHEADER + 256)
		return doEditHeader (iItemID - IDM_EDITDATASOURCEHEADER);

// evtl. AnsichtMenuItem aktiviert
	if (DBO().ProcessMenuEvent (iItemID)) {
		SetShouldRedraw();
		InitWndScrollBars();		// Rollbalken zuschalten
		DEX_ReReadCaption();
		RePaint();					// neue Ansicht zeichnen
		return true;
	}
	return false;
}

// Befehl aus TextObjektMenu behandeln ----------------------------------------
bool IrisWind::doHandleTextObjectMenu (MenuCommandEvt e) 
{
	return HandleTextObjectMenu (e.GetItemID());
}

///////////////////////////////////////////////////////////////////////////////
// ProjektionsFunktionen behandeln
#if !defined(NOPROJEKTION)
bool IrisWind::doResetPrj (void)
{
// DatenBasisObjekt Ausschnitt definieren
	DBO().SetPrjFcn (NULL, NULL);
	DBO().SetExtend (DBO().DBCont().InflateCont(10), AspectRatio);

// Menupunkte markieren
	GeographicCFlag = true;
	WorldCFlag = false;

return true;
}

bool IrisWind::doWorldPrj (void)
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

HWND IrisWind::CreateObjektInfo (
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

	_ASSERTE(pOIDlg -> m_ulActCount <= pOIDlg -> GetCount());

string strT = ObjInfoListe.CorrectCaption (pOIDlg, pcrOI -> lpCaption);

	TX_TRY(pNewCaption = new char [strlen (pcrOI -> lpCaption) + 20]);
	if (NULL != pNewCaption) {
		wsprintf (pNewCaption, "%s (%d/%ld)", strT.c_str(),
			  pOIDlg -> m_ulActCount, pOIDlg -> GetCount());
		pOIDlg -> SetCaption (pNewCaption);
	} else
		pOIDlg -> SetCaption (pcrOI -> lpCaption);

	DELETE_OBJ(pNewCaption);

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

HWND IrisWind::CreateObjektInfo (CREATEOBJEKTINFO *pcrOI, ExtensionList &rEL)
{
	if (NULL == pcrOI) 
		return NULL;

// ObjektFeld aufbauen, welches vom Fenster erwartet wird
//ObjFeld OF;
//
//	if (sizeof(CREATEOBJEKTINFOEX3) == pcrOI -> dwSize) {
//	ObjNummerCreator ONC (OF);
//
//		for (long i = 0; i < ((CREATEOBJEKTINFOEX3 *)pcrOI) -> lNumObjs; i++) 
//			OF.NewObj (ONC, pcrOI -> plObjs[i]);
//	}
//	else {
//	ObjNummerCreator ONC (OF);
//
//		for (short i = 0; i < pcrOI -> iNumObjs; i++) 
//			OF.NewObj (ONC, pcrOI -> plObjs[i]);
//	}

short iFlags = 0;
CMPONRPROC pProc = NULL;
DWORD dwData = 0L;
LPUNKNOWN pIUnk = NULL;
long lCnt = pcrOI -> iNumObjs;

	if (pcrOI -> dwSize >= sizeof (CREATEOBJEKTINFOEX)) {
	// wenn Fenster bereits existiert, dann zu diesem hinzufügen
		if (pcrOI -> dwSize >= sizeof(CREATEOBJEKTINFOEX2))
			pIUnk = ((CREATEOBJEKTINFOEX2 *)pcrOI) -> m_pIObjProp;

		if (((CREATEOBJEKTINFOEX *)pcrOI) -> m_hWnd) {
		// zu existierendem Fenster hinzufügen
		HWND hWnd = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_hWnd;
		ObjektInfo *pOIDlg = (ObjektInfo *)ObjInfoListe.GetORWindow (hWnd);

			if (sizeof(CREATEOBJEKTINFOEX3) == pcrOI -> dwSize) {
				if (pOIDlg && pOIDlg -> FInit (pcrOI -> plObjs, ((CREATEOBJEKTINFOEX3 *)pcrOI) -> lNumObjs)) 
					return hWnd;
			} 
			else {
				if (pOIDlg && pOIDlg -> FInit (pcrOI -> plObjs, pcrOI -> iNumObjs)) 
					return hWnd;
			}
		}
		else if (sizeof(CREATEOBJEKTINFOEX3) == pcrOI -> dwSize)
			lCnt = ((CREATEOBJEKTINFOEX3 *)pcrOI) -> lNumObjs;

	// zusätzliche Variablen werden für neues Fenster gebraucht
		iFlags = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_iFlags;
		pProc = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_pCmpProc;
		dwData = ((CREATEOBJEKTINFOEX *)pcrOI) -> m_dwData;
	}
	if (0 == (iFlags & ROHideFlags)) 
		iFlags |= (g_iHideFlags & ROHideFlags);	// globale Voreinstellung
	if (0 == (iFlags & ROSortFlags)) 
		iFlags |= (g_iHideFlags & ROSortFlags);	// globale Voreinstellung

//ObjektInfo *pOIDlg = ObjektInfo::CreateInstance (this, DBO(), rEL, OF, iFlags, pProc, dwData, pIUnk);
ObjektInfo *pOIDlg = ObjektInfo::CreateInstance (this, DBO(), rEL, pcrOI -> plObjs, lCnt, iFlags, pProc, dwData, pIUnk);

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

	_ASSERTE(pOIDlg -> m_ulActCount <= pOIDlg -> GetCount());

string strT = ObjInfoListe.CorrectCaption (pOIDlg, pcrOI -> lpCaption);

	TX_TRY(pNewCaption = new char [strlen (pcrOI -> lpCaption) + 20]);
	if (NULL != pNewCaption) {
		wsprintf (pNewCaption, "%s (%d/%ld)", strT.c_str(),
			  pOIDlg -> m_ulActCount, pOIDlg -> GetCount());
		pOIDlg -> SetCaption (pNewCaption);
	} else
		pOIDlg -> SetCaption (pcrOI -> lpCaption);

	DELETE_OBJ(pNewCaption);

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
bool IrisWind::SetActViewContainer (ObjContainer &rOC)
{
	if (!actClip.Top().isValid()) 
	// erster Eintrag: DBCont merken
		actClip.Push (DBO().GetExtend());
	if (m_pDRO != NULL) {
		Draw (*m_pDRO);
		DELETE_OBJ (m_pDRO);	// evtl. DragObjekt freigeben
	}

	SetExtend (rOC);

	InitWndScrollBars ();	// bei Bedarf ScrollBars einblenden und initialisieren
	InitOverView (rOC);		// Übersichtsfenster
	return true;
}

bool IrisWind::GetActViewContainer (ObjContainer &rOC)
{
	if (m_pDRO != NULL && m_pDRO -> isValidDragObject()) {
	Point pt1 = ((DragRectangleObject *)m_pDRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)m_pDRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);

		rOC = ObjContainer (pnt1, pnt2);
		return true;		// Selektion existiert
	} else {
	Rectangle rcC (CanvasRect());
		
		rOC = rcC;
		return false;		// kein SelektionsViereck
	}
}

///////////////////////////////////////////////////////////////////////////////
// Projektverwaltung
bool IrisWind::EnumProjects (ENUMNOKEY *pK)
{
CRing r(*m_pDBOs);
char cbBuffer[_MAX_PATH];

	for (r.First(); r.Valid(); ) {
	DatenBasisObjektLock l(r);
	bool fLast = !r.Next();

		_ASSERTE(NULL != (DatenBasisObjekt *)l);

		l -> GetDBName(cbBuffer);
		strupr (cbBuffer);
		if (false == (*(ENUMNOKEYCALLBACK)pK -> eFcn)(cbBuffer, fLast, pK -> ePtr))
			return (LRESULT)false;
	}
	return (LRESULT)true;
}

HPROJECT IrisWind::GetProjectHandle (LPCSTR pcName)
{
CRing r(*m_pDBOs);
char cbBuffer[_MAX_PATH];

	for (r.First(); r.Valid(); r.Next()) {
	DatenBasisObjektLock l(r);

		_ASSERTE(NULL != (DatenBasisObjekt *)l);
		if (!stricmp (l -> GetDBName(cbBuffer), pcName))
			return l -> DBDesc();
	}
	return NULL;
}

HPROJECT IrisWind::MakeProjectActive (HPROJECT hPr)
{
	if (0 == m_pDBOs -> Count()) return NULL;

int iIndex = m_pDBOs -> FFindItem (hPr);

	_ASSERTE(-1 != iIndex);

int iOldIndex = m_pDBOs -> FActivateItem (iIndex);

	_ASSERTE(-1 != iOldIndex);
	return DBO(iOldIndex).DBDesc();
}

///////////////////////////////////////////////////////////////////////////////
// liefert die Höhe des aktuellen AusgabeFensters (Druckers etc.)
CoOrd IrisWind::GetOutputHeight (void)
{
Rectangle rc = (NULL != m_pPrinter) ? m_pPrinter -> CanvasRect() : CanvasRect();

	return rc.Top() - rc.Bottom();
}

///////////////////////////////////////////////////////////////////////////////
// Auswahl der Koordinatensystemparameter 
LRESULT SelectCoordSysParams (pWindow pW, UINT uiID, DatenBasisObjekt &rDBO, CoordTrans *)
{
	_ASSERTE(NULL != pW);

// Dialogfenster generieren
CEierUhr Wait (pW);
CCoordProperties CoordProps (pW, uiID); 
WTRiASProject Prj;

	rDBO.GetTRiASProject (Prj.ppi());
	CoordProps.LoadPages(Prj);			// zusätzliche Pages aus Registry laden
	
	if (CoordProps.GetPageCount() == 0) {
		VMessageBox (pW, uiID, OkayButton|ExclamationIcon, IDS_COORDCANTCONFIG);
		return false;
	}

// Dialogfenster anzeigen
	Wait.Hide();
	CoordProps.Show (Centre);	// KoordinatenProps editieren
	if (CoordProps.Result()) {
		DEXN_ReReadHeader();		// alle sollen Header neu lesen
		DEX_SetDirtyGeoDB(true);	// DirtyFlag setzen
	}

	CoFreeUnusedLibraries();	// DLL's wieder freigeben
	return CoordProps.Result();
}

///////////////////////////////////////////////////////////////////////////////
// PropertySheet --------------------------------------------------------------
CCoordProperties::CCoordProperties (pWindow pWnd, UINT uiIDCap)
	: CPropertySheetExt (ResString (uiIDCap, 64), pWnd)
{
}

HRESULT CCoordProperties::LoadPages (IUnknown *pIUnkSite)
{
// alle sonstigen Pages aus der Registry laden
WStorage IStg;
WDataObject IDO;

	if (DEX_GetProjectStorage (*IStg.ppv())) 
		CreateDataObject (IStg, IDO);

string strKey (g_cbDocSubKey);

	strKey += string(g_cbDel) + g_cbCoordinates;
	return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, g_cbDocKey, strKey.c_str(), IDO, NULL, pIUnkSite);
}

HRESULT CCoordProperties::CreateDataObject (WStorage &rIStg, WDataObject &rIDO)
{ 
// DataObject generieren
HRESULT hr = DataObjectCreateInstance (NULL, IID_IDataObject, rIDO.ppv()); 

	if (FAILED(hr)) return hr;

// Storage im DataObject wegspeichern
STGMEDIUM stm;

	stm.tymed = TYMED_ISTORAGE;
	stm.pstg = rIStg.detach();		// übergibt AddRef()
	stm.pUnkForRelease = NULL;

FORMATETC fe;
UINT uiCf = RegisterClipboardFormat (g_cbDocKey);

	SETDefFormatEtc (fe, uiCf, TYMED_ISTORAGE);

return rIDO -> SetData (&fe, &stm, true);
}

