// Diverse Hilfsroutinen für IRISWIN (Win32)
// File: IRISUTI2.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <stdio.h>
#include <direct.h>
#include <shlobj.h>
#include <shlwapi.h>

#include <registry.hxx>
#include <konsobj.hxx>
#include <printer.hxx>
#include <TRiASMode.h>

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "strings.h"

#include "legdinfo.hxx"
#include "legwind.hxx"

#include "TraceTRiAS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern ExtDirisWindow *CurrActDirisW;

extern HelpDisplay *IrisHD;		// HilfeDatei
extern bool wasHelpEvt;			// Hilfsevent gerufen

extern int g_iActTool;
extern CLegendeClientWindow *pLegende;

// lokale Konstanten
const int FULLPATHSIZE = _MAX_PATH;     // maximale Dateinamenlänge
#if defined(_FORCE_LEGACY_CODE)
const int MAXNUMPAGES = 2048;			// Defaultwert für Pageanzahl in ZIPEDB
#endif // defined(_FORCE_LEGACY_CODE)
const int PALVERSION = 0x300;			// Version der Palettenstruktur
const int TREEOPTDELTA = 256;			// Anzahl der Objekte, nach denen Baum
					// optimiert werden soll

// globale Informationen ------------------------------------------------------
char ErrorDBDir[FULLPATHSIZE+1];        // Verzeichnis der FehlerDatenbasis
char PbdDBDir[FULLPATHSIZE+1];          // Verzeichnis der PBD Datenbasis
char dBaseDir[FULLPATHSIZE+1];		// Verzeichnis der DBaseDateien
char cbDefaultDir[FULLPATHSIZE+1];	// StandardWurzelVerzeichnis der Projekte
char g_cbCursorDir[_MAX_PATH+1];		// Verzeichnis mit Cursoren für TRiAS

short CopyRightFlag;			// CopyRightSensitivity
bool g_fSystemSightFlag = true;	// Systemsichten anzeigen/nicht anzeigen
#if defined(_FORCE_LEGACY_CODE)
bool g_fFilters = false;		// Exportfilter installiert ?
#endif // defined(_FORCE_LEGACY_CODE)
bool g_fSystemAdm = false;		// SystemAdministratorMode
bool g_fHSB = false;			// für Farbeinstellung HSB-Modell verwenden
bool g_fShowSysFeatures = false;	// systeminterne Merkmale anzeigen

#if defined(_USE_FLICKERFREE_DRAWING)
DWORD g_dwTicksBetweenPaints = DEFAULT_TICKS_BETWEEN_PAINTS;
DWORD g_dwTicksBetweenIdleLoops = DEFAULT_TICKS_BETWEEN_IDLELOOPS;
#endif // _USE_FLICKERFREE_DRAWING
DWORD g_dwTRiASMode = TRIASMODE_NativeDB;		// diverse Flags für TRiAS (global)
DWORD g_dwDrawingMode = DRAWMODE_Default;			// DrawMode

short g_iMinutes = 0;			// Speichern aller ... Minuten
short g_iTicks = 0; 

extern DWORD g_iHideFlags;		// nicht anzuzeigende Infos in ORFenstern
extern HINSTANCE hInstance;		// HINSTANCE von TRiAS

// globale AnwendungsFarbPalette
HPALETTE hPalette = NULL;

#if defined(_DEBUG) && !defined(WIN16)
#if _TRiAS_VER < 0x0400
short g_iKonsFlags = KTDNothing;
#endif // _TRiAS_VER < 0x0400
DWORD g_dwTraceLevel = TRACE_NOTRACE;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Skalierungskoeffizienten für DPI resistente Berechnungen
double g_dScaleX = 1.0;
double g_dScaleY = 1.0;

BOOL ReadRegistryOptions (Rectangle &rMWnd, BOOL &rZoomedFlag, BOOL &rIconicFlag);
void ReadIniPathes (void);

extern "C" _TF_ENTRY32 LRESULT WINAPI EventDispatcher (HWND, UINT, WPARAM, LPARAM);

// Initialisierung der Applikation --------------------------------------------
BOOL InitIrisApp (Rectangle &rMWnd, BOOL &rZoomedFlag, BOOL &rIconicFlag) 
{
// FensterKlassen registrieren
WNDCLASS wc;

	if (!GetClassInfo (hInstance, g_cbLegendClass, &wc)) {
		wc.style			= (CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
		wc.lpfnWndProc		= (WNDPROC)EventDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hInstance;
		wc.hIcon			= NULL;
		wc.hCursor			= LoadCursor (NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= g_cbLegendClass;

	ATOM Atom = RegisterClass (&wc);

		TX_ASSERT(0 != Atom);
	}

	if (!GetClassInfo (hInstance, g_cbOverViewClass, &wc)) {
		wc.style			= (CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
		wc.lpfnWndProc		= (WNDPROC)EventDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hInstance;
		wc.hIcon			= NULL;
		wc.hCursor			= LoadCursor (NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= g_cbOverViewClass;

	ATOM Atom = RegisterClass (&wc);

		TX_ASSERT(0 != Atom);
	}

	if (!GetClassInfo (hInstance, g_cbViewClass, &wc)) {
		wc.style			= (CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
		wc.lpfnWndProc		= (WNDPROC)EventDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hInstance;
		wc.hIcon			= NULL;
		wc.hCursor			= LoadCursor (NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= g_cbViewClass;

	ATOM Atom = RegisterClass (&wc);

		TX_ASSERT(0 != Atom);
	}

// We create a special class, one with a different background and without 
// the CS_VREDRAW/CS_HREDRAW style so all the frame window's control bars 
// will not be repainted when the window is resized.
	if (!GetClassInfo (hInstance, g_cbFrameClass, &wc)) {
		wc.style			= CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc		= (WNDPROC)EventDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hInstance;
		wc.hIcon			= LoadIcon (hInstance, MAKEINTRESOURCE(IDI_INTERTRIASBLUE));
		wc.hCursor			= LoadCursor (NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= g_cbFrameClass;
	
	ATOM Atom = RegisterClass (&wc);

		TX_ASSERT(0 != Atom);
	}

// Zentrale Profiles (WIN.INI und RegDB) initialisieren -----------------------
	TriasRegInit();

// aus Registry/INI Voreinstellungen einlesen
	ReadRegistryOptions (rMWnd, rZoomedFlag, rIconicFlag);

// PrivateProfiles lesen und entsprechende Variablen initialisieren -----------
	ReadIniPathes();

// 2. Systemparameter setzen --------------------------------------------------
ResString Profile (IDS_PROFILE, 13);
ResString IrisPars (IDS_IRISPARS, 13);

#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) {
	// initiale PageAnzahl in ZIPEDB
	short NumOfPages = GetPrivateProfileInt (IrisPars,
						ResString (IDS_PAGENUM, 13), MAXNUMPAGES, Profile);
#if defined(_USE_LEGACY_CODE)
		z_setpages (NumOfPages);        // Pageanzahl einstellen
#endif // _USE_LEGACY_CODE

	// diverse sonstige Flags und Werte
		CopyRightFlag = GetPrivateProfileInt (IrisPars,
						ResString (IDS_COPYRIGHTFLAG, 13),
						0, Profile);
		SystemSightFlag = GetPrivateProfileInt (IrisPars,
						ResString (IDS_SYSTEMSIGHTS, 20), 0, Profile);

		g_iMinutes = GetPrivateProfileInt (IrisPars,
						ResString (IDS_SAVEDELTA, 20), 0, Profile);

		g_iHideFlags = GetPrivateProfileInt (IrisPars,
						ResString (IDS_HIDEFLAGS, 20), 
						ROHideIdent, Profile);

		g_fSystemAdm = (0 != GetPrivateProfileInt (IrisPars, g_cbSysAdmin, 0, Profile)) ? 
						true : false;

	// FensterGröße und Lage definieren 
	char PStr[_MAX_PATH];
	CoOrd Left, Right, Top, Bottom;
	ResString IrisStartUp (IDS_STARTUP, 13);        // RessourceStrings
	ResString SizeOrg (IDS_SIZEORG, 13);
	ResString InitStartUp (IDS_INITSTARTUP, 40);

		GetPrivateProfileString (IrisStartUp, SizeOrg, InitStartUp, 
						PStr, _MAX_PATH, Profile);
		sscanf (PStr, "%d,%d,%d,%d,%d,%d", &rZoomedFlag, &rIconicFlag,
				&Top, &Left, &Bottom, &Right);

	// Werte des aktuellen Systems holen
	int DeltaX = GetSystemMetrics (IsWin40() ? SM_CXMAXIMIZED : SM_CXSCREEN);
	int DeltaY = GetSystemMetrics (IsWin40() ? SM_CYMAXIMIZED : SM_CYSCREEN);

	// und nun Vorgaben prüfen und ggf. korrigieren
		if (Right - Left > DeltaX || Right - Left < 0 || Left < 0 || Right > DeltaX) { 
		// X-Ausdehnung inkorrekt
			Left = 10; 
			Right = DeltaX - 10;
		}
		if (Top - Bottom > DeltaY || Top - Bottom < 0 || Bottom < 0 || Top > DeltaY) {
			Bottom = 10; 
			Top = DeltaY - 10;
		}
		rMWnd = Rectangle (Top, Left, Bottom, Right);
	} 
#endif // ENABLE_WIN32S_CODE

#if defined(_FORCE_LEGACY_CODE)
	g_fFilters = GetPrivateProfileInt (IrisPars, 
						ResString(IDS_NUMFILTERS, 15), 0, Profile);
#endif // defined(_FORCE_LEGACY_CODE)

HDC hDC = GetDC(NULL);

	g_dScaleX = GetDeviceCaps(hDC, LOGPIXELSX) / 96.0;
	g_dScaleY = GetDeviceCaps(hDC, LOGPIXELSY) / 96.0;
	ReleaseDC(NULL, hDC);

	g_iTicks = 0;
	hPalette = NULL;
	return TRUE;    // alles ok, es kann losgehen
}

void ReadIniPathes (void)
{
#if defined(_FORCE_LEGACY_CODE)
ResString Profile (IDS_PROFILE, 13);

// 1. Pfade zu Fehler-DB und PBD-DB setzen ------------------------------------
ResString IrisDirs (IDS_IRISDIRS, 64);
ResString ErrorDB (IDS_ERRORDB, 13);
ResString PbdDB (IDS_PBDDB, 13);
ResString DBase (IDS_DBASEINFO, 13);
ResString rsDefaultDir (IDS_DEFAULTPROJECTPATH, 20);
register char *Env;

	GetPrivateProfileString (IrisDirs, ErrorDB, "", ErrorDBDir, FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, PbdDB, "", PbdDBDir, FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, DBase, "", dBaseDir, FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, rsDefaultDir, "", cbDefaultDir, FULLPATHSIZE+1, Profile);

// nichts gefunden, mit Werten aus Environment neu schreiben
	if (!strcmp (ErrorDBDir, "")) {
		if ((Env = getenv (ResString (IDS_ERRORDBENV, 13))) != NULL)
			strcpy (ErrorDBDir, Env);
		else 
			_getdcwd (_getdrive(), ErrorDBDir, FULLPATHSIZE);
		if (ErrorDBDir[strlen(ErrorDBDir)-1] != '\\')
			strcat (ErrorDBDir, "\\");    // '\\' anhängen
		WritePrivateProfileString (IrisDirs, ErrorDB, ErrorDBDir, Profile);
	}
	if (!strcmp (PbdDBDir, "")) {
		if ((Env = getenv (ResString (IDS_PBDDBENV, 13))) != NULL)
			strcpy (PbdDBDir, Env);
		else 
			_getdcwd (_getdrive(), PbdDBDir, FULLPATHSIZE);
		if (PbdDBDir[strlen(PbdDBDir)-1] != '\\')
			strcat (PbdDBDir, "\\");
		WritePrivateProfileString (IrisDirs, PbdDB, PbdDBDir, Profile);
	}
	if (!strcmp (dBaseDir, "")) {
		_getdcwd (_getdrive(), dBaseDir, FULLPATHSIZE);
		if (dBaseDir[strlen(dBaseDir)-1] != '\\')
			strcat (dBaseDir, "\\");
		WritePrivateProfileString (IrisDirs, DBase, dBaseDir, Profile);
	}
	if (!strcmp (cbDefaultDir, "")) {
		_getdcwd (_getdrive(), cbDefaultDir, FULLPATHSIZE);
		if (cbDefaultDir[strlen(cbDefaultDir)-1] != '\\')
			strcat (cbDefaultDir, "\\");
		WritePrivateProfileString (IrisDirs, rsDefaultDir, cbDefaultDir, Profile);
	}
#ifdef DLL
// in DLL Pfad zu Error-DB setzen
	SetErrorDBEnv (ErrorDBDir);     // ErrorDB Env setzen
#endif
#else // defined(_FORCE_LEGACY_CODE)
CRegKey regDirs;

	if (ERROR_SUCCESS == regDirs.Open(HKEY_CURRENT_USER, "Software", KEY_READ) && 
		ERROR_SUCCESS == regDirs.Open(regDirs, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regDirs.Open(regDirs, REG_PRODUCT_KEY, KEY_READ))
	{
	CRegKey regKey;

		if (ERROR_SUCCESS == regKey.Open(regDirs, "Directories") ||
			ERROR_SUCCESS == regKey.Create(regDirs, "Directories"))
		{
			regDirs.Close();
			regDirs.Attach(regKey.Detach());

		ResString rsDefaultDir (IDS_DEFAULTPROJECTPATH, 20);
		DWORD dwLen = sizeof(cbDefaultDir);

			cbDefaultDir[0] = '\0';
			if (ERROR_SUCCESS != regDirs.QueryValue(cbDefaultDir, rsDefaultDir, &dwLen) ||
				'\0' == cbDefaultDir[0]) 
			{
			// ggf. fürs nächste mal schreiben
			DWORD dwFlags = CSIDL_PERSONAL;

				if (IsWinNT() && IsWin50())
					dwFlags |= CSIDL_FLAG_CREATE;

				SHGetFolderPath(NULL, dwFlags, NULL, 0, cbDefaultDir);
				PathAppend(cbDefaultDir, REG_COMPANY_KEY);
				PathAppend(cbDefaultDir, REG_PRODUCT_KEY);

			ResString rsProjects (IDS_PROJECTSUBDIR, 20);

				PathAppend(cbDefaultDir, rsProjects);
				PathAddBackslash(cbDefaultDir);

				regDirs.SetValue(cbDefaultDir, rsDefaultDir);

			// Verzeichnis auch noch erzeugen
				CreateDirectory (cbDefaultDir, NULL);
			}
		}
	}
#endif // defined(_FORCE_LEGACY_CODE)
}

#if defined(_FORCE_LEGACY_CODE)
// Testen, ob Umgebung korrekt ist --------------------------------------------
BOOL TestEnv (HINSTANCE hInst) 
{
// Personalisierungsinformation überprüfen
HRSRC hRes;
HGLOBAL hResCode;
unsigned short *lpCode;
char personal[129];

// Resource laden
	hRes = FindResource (hInst, MAKEINTRESOURCE (PERSONALCODE),
				    MAKEINTRESOURCE (PERSONALCODERES));
	hResCode = LoadResource (hInst, hRes);
	lpCode = (unsigned short *)LockResource (hResCode);

// PersonalisierungsInfo zusammenstellen        
	strcpy (personal, ResString (IDS_PERSONALNAME, 64));
	strcat (personal, ResString (IDS_PERSONALADDRESS, 64));

// Ergebnis vergleichen
	if (lpCode == NULL || *lpCode != mycrypt ((unsigned char *)personal, strlen (personal))) {
	// irgendeiner hat rumgefummelt
		UnlockResource (hResCode);
		FreeResource (hResCode);
		db_error (EC_BADPERSONALINFO, RC_InitIrisApp);
		return FALSE;
	}

// alles ok
	UnlockResource (hResCode);
	FreeResource (hResCode);
		
return TRUE;
}
#endif // defined(_FORCE_LEGACY_CODE)

// Diese Routine wird kurz vor Ende des Programms abgearbeitet
void IrisWind::CleanUpView (void) 
{
#if !defined(_OLD_DRAGNDROP)
// DropTarget abmelden, wenn's noch nicht passiert ist
	if (m_pDropTgt) {
		RevokeDragDrop (Handle(API_WINDOW_HWND));
		CoLockObjectExternal (m_pDropTgt, false, true);
		m_pDropTgt -> Release();
		m_pDropTgt = NULL;
	}
#else
// Dragging wieder ausschalten
	DragAcceptFiles (Handle(API_WINDOW_HWND), false);
#endif // !_OLD_DRAGNDROP

// Pointer säubern um post-mortem Zugriff zu verhindern
	DELETE_OBJ (m_pDRO);
	DELETE_OBJ (pLegende);

	if (!m_fCleanedUp) {
		DEXN_ViewDeleted (Handle(API_WINDOW_HWND));
		m_fCleanedUp = true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// AspectRatio des Fensters holen 
Point IrisWind::GetAspectRatio (void) 
{
	if (m_fHasAspectRatio)
		return AspectRatio;

HWND hWnd = Handle (API_CLIENT_HWND);
HDC hDC =::GetDC (hWnd);

CoOrd LogPixelsX = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSX);
CoOrd LogPixelsY = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSY);

	ReleaseDC (hWnd, hDC);

	AspectRatio = Point (LogPixelsX, LogPixelsY);
	m_fHasAspectRatio = true;
	return AspectRatio;
}

///////////////////////////////////////////////////////////////////////////////
// HilfeRequestEventHandler 
void IrisWind::HelpRequest (HelpRequestEvt e) 
{
	switch (e.RequestType()) {
	case HelpMenu:
		IrisHD -> Show (e.GetItemID());
		wasHelpEvt = TRUE;
		break;

	case HelpWindow:
		switch (e.GetWindowArea()) {
		case Caption:
			IrisHD -> Show (IDW_CAPTION);
			break;

		case WindowCanvas:
			IrisHD -> Show (IDW_CANVAS);
			break;

		case Border:
		case MaxBox:
		case MinBox:
		case SizeBox:
		case SysMenuBox:
		case UnknownArea:
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		case CVMenuBar:
#else
		case MenuBar:
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
		default:
			break;
		}
		break;

	case HelpControl:
	default:
		break;
	}
}

#if defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// Version der GeoDB bestimmen 
static long __GeoDBVersion__ = -1L;

long GetGeoDBVersion (GeoDB *pDB) 
{
// wenn Version schon bestimmt ist
	if (__GeoDBVersion__ != -1L) return __GeoDBVersion__;

	if (NULL != pDB) {
		__GeoDBVersion__ = pDB->GetDBVersion();
	} else {
	GeoDB &rDB = CurrActDirisW -> DBO().DB();

		__GeoDBVersion__ = rDB.GetDBVersion();
	}
	return __GeoDBVersion__;
}

// wenn neue GeoDB eröffnet wird, dann rücksetzen -----------------------------
void ResetGeoDBVersion (void) { __GeoDBVersion__ = -1L; }
#endif // _FORCE_LEGACY_CODE

// Letzten verwendeten Ident für neues Objekt verwalten -----------------------
long IrisWind::GetLastIdent (void)
{
	if (m_lLastIdent == -1L) {
	// letzten verwendeten aus Projekt-INI lesen
	char cbPrj[_MAX_PATH+1];
	
		if (NULL == DEX_GetActiveProject (cbPrj)) 
			return -1L;
	
	ProFile PF (cbPrj);
	
		m_lLastIdent = PF.GetLastIdent();
	}
	return m_lLastIdent;
}


void IrisWind::SetLastIdent (long lIdent)
{
	if (lIdent == m_lLastIdent) return;	// nothing to do

char cbPrj[_MAX_PATH+1];
	
	if (NULL == DEX_GetActiveProject (cbPrj)) 
		return;
	
ProFile PF (cbPrj);

	PF.SetLastIdent (lIdent);
	m_lLastIdent = lIdent;
}

// Aus Registry Voreinstellungen einlesen -------------------------------------
BOOL ReadRegistryOptions (Rectangle &rMWnd, BOOL &rZoomedFlag, BOOL &rIconicFlag)
{
#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) return false;
#endif // ENABLE_WIN32S_CODE

CCurrentUser regCfg (g_cbRegConfig);

// in ORFenstern angezeigte Informationen
DWORD dwData = DWORD(RODefaultFlags);

	regCfg.GetDWORD (g_cbHideFlags, dwData);
	g_iHideFlags = dwData;

// verwendetes Farbmodell
	dwData = 0L;
	regCfg.GetDWORD (g_cbHSBColors, dwData);
	g_fHSB = dwData ? true : false;

// während Zeichnen IdleLoop anwerfen etc.
#if defined(_USE_FLICKERFREE_DRAWING)
	dwData = DEFAULT_DRAW_MODE;	// default is on
	regCfg.GetDWORD (g_cbDrawingMode, dwData);
	g_dwDrawingMode |= (dwData & DRAWMODE_FlickerFreeMask);

// evtl. FlickerFrei zeichnen
	if (g_dwDrawingMode & DRAWMODE_FlickerFree) {
		dwData = DEFAULT_TICKS_BETWEEN_PAINTS/100;		// default ist 0.8 Sek
		regCfg.GetDWORD (g_cbFlickerFreeTime, dwData);
		if (0 != dwData) 
			g_dwTicksBetweenPaints = 100*dwData;	// in Registry stehen 0.1 Sekunden Intervalle

	// evtl. nur nach Interval AppExec rufen
		dwData = DEFAULT_TICKS_BETWEEN_IDLELOOPS/100;	// default ist 0.1 Sek
		regCfg.GetDWORD (g_cbIdleTime, dwData);
		if (0 != dwData) 
			g_dwTicksBetweenIdleLoops = 100*dwData;	// in Registry stehen 0.1 Sekunden Intervalle
	}
#else
	dwData = DRAWMODE_IdleDuringDraw;			// default is on
	regCfg.GetDWORD (g_cbDrawingMode, dwData);
	g_dwDrawingMode |= (dwData & DRAWMODE_FlickerFreeMask);
#endif // defined(_USE_FLICKERFREE_DRAWING)

// SystemAdministration
	dwData = 0L;
	regCfg.GetDWORD (g_cbSysAdmin, dwData);
	g_fSystemAdm = (dwData != 0) ? true : false;

	dwData = 0L;
	regCfg.GetDWORD (g_cbShowSysFeatures, dwData);
	g_fShowSysFeatures = (dwData != 0) ? true : false;

#if defined(_FORCE_LEGACY_CODE)
// PageAnzahl in TRiAS01
ResString resNumPages (IDS_PAGENUM, 13);

	dwData = MAXNUMPAGES;
	regCfg.GetDWORD (resNumPages.Addr(), dwData);
	z_setpages (int(dwData));		// Pageanzahl einstellen
#endif // _FORCE_LEGACY_CODE

// Ansichten, die mit "__" beginnen werden angezeigt
ResString resSysViews (IDS_SYSTEMSIGHTS, 20);

	dwData = 0;
	regCfg.GetDWORD (resSysViews.Addr(), dwData);
	g_fSystemSightFlag = (0 != dwData) ? true : false;

// automatisch speichern aller n Minuten (0 --> nicht automatisch speichern
ResString resSaveDelta (IDS_SAVEDELTA, 20);

	dwData = 0;
	regCfg.GetDWORD (resSaveDelta.Addr(), dwData);
	g_iMinutes = int(dwData);

	CopyRightFlag = 0;				// grundsätzlich 0

// Verzeichnisse einlesen
	{
	CCurrentUser regDirs (g_cbDirectories);
	
		g_cbCursorDir[0] = '\0';
		dwData = _MAX_PATH;
		regDirs.GetSubSZ (g_cbCursorDirectory, g_cbCursorDir, dwData);
	}

// Fenstergröße und Lage rekonstruieren
CoOrd Left, Right, Top, Bottom;
ResString resSizeOrg (IDS_SIZEORG, 13);
char cbStr[_MAX_PATH];

	dwData = _MAX_PATH;
	if (!regCfg.GetSubSZ (resSizeOrg, cbStr, dwData))
		strcpy (cbStr, ResString (IDS_INITSTARTUP, 40));

	sscanf (cbStr, "%d,%d,%d,%d,%d,%d", &rZoomedFlag, &rIconicFlag,
									   &Top, &Left, &Bottom, &Right);
// Werte des aktuellen Systems holen
int DeltaX = GetSystemMetrics (IsWin40() ? SM_CXMAXIMIZED : SM_CXSCREEN);
int DeltaY = GetSystemMetrics (IsWin40() ? SM_CYMAXIMIZED : SM_CYSCREEN);

// und nun Vorgaben prüfen und ggf. korrigieren
	if (Left >= DeltaX || Right <= 0) {
//	if (Right - Left > DeltaX || Right - Left < 0 || Left < 0 || Right > DeltaX) { 
	// X-Ausdehnung inkorrekt
		Left = 10; 
		Right = DeltaX - 10;
	}
	if (Bottom >= DeltaY || Top <= 0) {
//	if (Top - Bottom > DeltaY || Top - Bottom < 0 || Bottom < 0 || Top > DeltaY) {
		Bottom = 10; 
		Top = DeltaY - 10;
	}
	if (Left < 1) Left = 1;
	if (Right > DeltaX) Right = DeltaX -1;
	if (Top > DeltaY) Top = DeltaY - 1;
	if (Top < 1) Top = 1;

	rMWnd = Rectangle (Top, Left, Bottom, Right);

#if defined(_DEBUG)
#if _TRiAS_VER < 0x0400
	g_iKonsFlags = KTDNothing;
	if (regCfg.GetDWORD (TEXT("KonsistenzTest"), dwData))
		g_iKonsFlags = short(dwData);
#endif // _TRiAS_VER < 0x0400

	g_dwTraceLevel = TRACE_NOTRACE;
	if (regCfg.GetDWORD (g_cbTraceLevel, dwData))
		g_dwTraceLevel = dwData;
#endif

	return true;
}


///////////////////////////////////////////////////////////////////////////////
//
void DragRectangleObject::ProcessKey (KeyEvt)
{ 
	Process (m_end); 
}

bool DragRectangleObject::ToProcessKey (void)
{
bool fMouse = GetAsyncKeyState (VK_LBUTTON) < 0 || 
			  GetAsyncKeyState (VK_RBUTTON) < 0;

	if (!fMouse) return false;	// nur, wenn Mouse nicht gedrückt

bool fControl = GetAsyncKeyState (VK_MENU) < 0;
bool fShift = GetAsyncKeyState (VK_SHIFT) < 0;

	return (fControl != m_fControl) || (fShift != m_fShift);
}

bool DragRectangleObject::isDirty (void)
{
	return false;
}

DRAGTYPE DragRectangleObject::isA (void)
{ 
	return DT_DRAGRECTANGLE; 
}

void DragRectangleObject::Process (Point end)
{
bool fMouse = GetAsyncKeyState (VK_LBUTTON) < 0 || 
			  GetAsyncKeyState (VK_RBUTTON) < 0;

	if (!fMouse) return;	// nur, wenn Mouse nicht gedrückt

	m_fControl = (GetAsyncKeyState (VK_MENU) < 0) ? true : false;
	m_fShift = (GetAsyncKeyState (VK_SHIFT) < 0) ? true : false;

	m_end = end;
	if (m_fControl) {
		if (m_fShift) {	// isotrop vom Mittelpunkt aus
			if (abs(end.X()-pt.X()) > abs(end.Y()-pt.Y())) {
				pt = Point (2*m_pt.X()-end.X(), m_pt.Y()+(end.X()-m_pt.X()));
				dim = Dimension (2*(end.X()-m_pt.X())+1, -2*(end.X()-m_pt.X())-1);
			} else {
				pt = Point (m_pt.X()-(end.Y()-m_pt.Y()), 2*m_pt.Y()-end.Y());
				dim = Dimension (2*(end.Y()-m_pt.Y())+1, 2*(end.Y()-m_pt.Y())-1);
			}
		} else {	// bezogen auf Mittelpunkt ändern
			pt = Point (2*m_pt.X()-end.X(), 2*m_pt.Y()-end.Y());
			dim = Dimension (2*(end.X()-m_pt.X())+1, 2*(end.Y()-m_pt.Y())-1);
		}
	}
	else {
		pt = m_pt;
		if (m_fShift) {	// isotrop ändern
			if (abs(end.X()-pt.X()) > abs(end.Y()-pt.Y()))
				dim = Dimension (end.X()-pt.X()+1, -(end.X()-pt.X())-1);
			else
				dim = Dimension (-(end.Y()-pt.Y())+1, end.Y()-pt.Y()-1);
		} else		// normal
			dim = Dimension (end.X()-pt.X()+1, end.Y()-pt.Y()-1);
	}
}


///////////////////////////////////////////////////////////////////////////////
void DragLineObject::Process (Point Pt)
{ 
	end = Pt; 
}

bool DragLineObject::isDirty (void)
{
	return false;
}

DRAGTYPE DragLineObject::isA (void)
{ 
	return DT_DRAGLINE; 
}

void DragLineObject::ProcessKey (KeyEvt) 	// TastenDruck verarbeiten
{
}

bool DragLineObject::ToProcessKey (void)
{
	return false;
}


///////////////////////////////////////////////////////////////////////////////
VisType VMskToVTyp (short iVMsk, short iMsk)
{
	iVMsk &= iMsk;		// nur nach bestimmten suchen

	if (iVMsk & TPPunkt) return VT_Punkt;
	if (iVMsk & TPLinie) return VT_Linie;
	if (iVMsk & TPFlaeche) return VT_Flaeche;
	if (iVMsk & TPText) return VT_Text;

	return VT_Default;
}

#if !defined(WIN16)
// create a shortcut to a file
//
// in:
//   pszShortcutFile     fully qualified path to shortcut file
//   pszTo          shortcut points to this file
//
// returns:
//   standard hres codes
//
// assumes:
//   CoInitialize() has been called...

#include <shlobj.h>

HRESULT CreateShortCut (LPCSTR pszShortcutFile, LPCSTR pszLink, LPCSTR pszDesc)
{
IShellLink *psl = NULL;
HRESULT hr = CoCreateInstance (CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
			       IID_IShellLink, (LPVOID *)&psl);

	if (!SUCCEEDED(hr)) return hr;

IPersistFile *ppf = NULL;

	hr = psl -> QueryInterface (IID_IPersistFile, (LPVOID *)&ppf);
	if (!SUCCEEDED(hr)) goto labelError;

// set the path to the short cut
	hr = psl -> SetPath (pszShortcutFile);
	if (!SUCCEEDED(hr)) goto labelError;

	hr = psl -> SetDescription (pszDesc);
	if (!SUCCEEDED(hr)) goto labelError;

        hr = ppf -> Save (WideString (pszLink), TRUE);

labelError:	// irgend ein Fehler ist aufgetreten
	if (NULL != ppf) ppf -> Release();
	if (NULL != psl) psl -> Release();
   
return hr;
}
#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// Generieren des vollen Pfades einer CursorDatei
LPSTR MakeCursorPath (LPCSTR pcCursor, LPSTR pBuffer, int iLen)
{
CCurrentUser regCursors (g_cbCursors);
char cbBuff[_MAX_PATH];
DWORD dwLen = _MAX_PATH;

	if (!regCursors.GetSubSZ (pcCursor, cbBuff, dwLen))
		return NULL;

	dwLen = SearchPath (g_cbCursorDir, cbBuff, NULL, iLen, pBuffer, NULL);
	if (0 == dwLen)
		return NULL;

	return pBuffer;
}

