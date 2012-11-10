// Diverse Hilfsroutinen fuer IRISWIN
// File: IRISUTIL.CXX

#include "triaspre.hxx"

#include <stdio.h>
#include <direct.h>

#if defined(WIN32)
#include <registry.hxx>
#include <konsobj.hxx>
#endif 

#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX
#include "legdinfo.hxx"
#include "legwind.hxx"

extern pWindow CurrActW;
extern ExtDirisWindow *CurrActDirisW;

extern HelpDisplay *IrisHD;		// HilfeDatei
extern Bool wasHelpEvt;			// Hilfsevent gerufen

extern ToolWind *pToolBox;
extern CLegendeWindow *pLegende;

// lokale Konstanten
const int FULLPATHSIZE = _MAX_PATH;      // maximale Dateinamenlänge
const int MAXPAGES = 128;               // Defaultwert für Pageanzahl in ZIPEDB
const int PALVERSION = 0x300;		// Version der Palettenstruktur
const int TREEOPTDELTA = 256;		// Anzahl der Objekte, nach denen Baum
					// optimiert werden soll

// globale Informationen ------------------------------------------------------
char ErrorDBDir[FULLPATHSIZE+1];        // Verzeichnis der FehlerDatenbasis
char PbdDBDir[FULLPATHSIZE+1];          // Verzeichnis der PBD Datenbasis
char dBaseDir[FULLPATHSIZE+1];		// Verzeichnis der DBaseDateien
char DQLScriptDir[FULLPATHSIZE+1];	// Verzeichnis der DQLScripts
char cbDefaultDir[FULLPATHSIZE+1];	// StandardWurzelVerzeichnis der Projekte

unsigned long TreeOptDelta;		// Delta nach dem Bäume optimiert werden
short CopyRightFlag;			// CopyRightSensitivity
short SystemSightFlag;			// Systemsichten anzeigen/nicht anzeigen
bool g_fFilters = false;		// Exportfilter installiert ?
bool g_fSystemAdm = false;		// SystemAdministratorMode

short g_iMinutes = 0;			// Speichern aller ... Minuten
short g_iTicks = 0; 

extern short g_iHideFlags;		// nicht anzuzeigende Infos in ORFenstern

// globale AnwendungsFarbPalette
HPALETTE hPalette = NULL;

#if defined(_DEBUG) && defined(WIN32)
short g_iKonsFlags = KTDDiagnose;
#endif // _DEBUG

bool ReadRegistryOptions (void);
void ReadIniPathes (void);

// Initialisierung der Applikation --------------------------------------------
bool InitIrisApp (Rectangle &MWnd, bool &ZoomedFlag, bool &IconicFlag, bool fForceReg) 
{
// Zentrale Profiles (WIN.INI und RegDB) initialisieren -----------------------
	TriasRegInit (fForceReg);

// aus Registry/INI Voreinstellungen einlesen
	ReadRegistryOptions();

// PrivateProfiles lesen und entsprechende Variablen initialisieren -----------
	ReadIniPathes();

// 2. Systemparameter setzen --------------------------------------------------
ResString Profile (IDS_PROFILE, 13);
ResString IrisPars (IDS_IRISPARS, 13);
short NumOfPages;                       // initiale PageAnzahl in ZIPEDB

	NumOfPages = GetPrivateProfileInt (IrisPars,
				ResString (IDS_PAGENUM, 13), MAXPAGES, Profile);
	z_setpages (NumOfPages);        // Pageanzahl einstellen

	TreeOptDelta = (unsigned long)GetPrivateProfileInt (IrisPars,
					ResString (IDS_TREEOPTDELTA, 13), 
					TREEOPTDELTA, Profile);

	CopyRightFlag = GetPrivateProfileInt (IrisPars,
					ResString (IDS_COPYRIGHTFLAG, 13),
					0, Profile);

	SystemSightFlag = GetPrivateProfileInt (IrisPars,
				ResString (IDS_SYSTEMSIGHTS, 20), 0, Profile);

	g_fFilters = GetPrivateProfileInt (IrisPars, 
				ResString(IDS_NUMFILTERS, 15), 0, Profile);
				
	g_iMinutes = GetPrivateProfileInt (IrisPars,
				ResString (IDS_SAVEDELTA, 20), 0, Profile);
	g_iTicks = 0;

ResString resHide (IDS_HIDEFLAGS, 20);
#if defined(WIN32)
	if (!IsWin32s()) {
	CCurrentUser regCfg (TEXT("Software\\uve\\TRiAS") TEXT("\\") TEXT("Config"));
	DWORD dwData = DWORD(ROSortObjNr|ROHideIdent);
	
		regCfg.GetDWORD (resHide.Addr(), dwData);
		g_iHideFlags = short(dwData);
	} else
#endif
	{
		g_iHideFlags = GetPrivateProfileInt (IrisPars,
				resHide.Addr(), ROSortObjNr|ROHideIdent, Profile);
	}
				
// 3. FensterGröße und Lage definieren ----------------------------------------
char PStr[_MAX_PATH];
CoOrd Left, Right, Top, Bottom;
ResString IrisStartUp (IDS_STARTUP, 13);        // RessourceStrings
ResString SizeOrg (IDS_SIZEORG, 13);
ResString InitStartUp (IDS_INITSTARTUP, 40);

	GetPrivateProfileString (IrisStartUp, SizeOrg, InitStartUp, 
					PStr, _MAX_PATH, Profile);
	sscanf (PStr, "%d,%d,%d,%d,%d,%d", &ZoomedFlag, &IconicFlag,
			&Top, &Left, &Bottom, &Right);

// Werte des aktuellen Systems holen
int DeltaX = GetSystemMetrics (SM_CXSCREEN);
int DeltaY = GetSystemMetrics (SM_CYSCREEN);

// und nun Vorgaben prüfen und ggf. korrigieren
	if (Right - Left > DeltaX || Right - Left < 0) { 
	// X-Ausdehnung inkorrekt
		Left = 10; Right = DeltaX - 10;
	}
	if (Top - Bottom > DeltaY || Top - Bottom < 0) {
		Bottom = 10; Top = DeltaY - 10;
	}
	MWnd = Rectangle (Top, Left, Bottom, Right);

	hPalette = NULL;

return TRUE;    // alles ok, es kann losgehen
}

void ReadIniPathes (void)
{
ResString Profile (IDS_PROFILE, 13);

// 1. Pfade zu Fehler-DB und PBD-DB setzen ------------------------------------
ResString IrisDirs (IDS_IRISDIRS, 64);
ResString ErrorDB (IDS_ERRORDB, 13);
ResString PbdDB (IDS_PBDDB, 13);
ResString DBase (IDS_DBASEINFO, 13);
ResString DQLScript (IDS_DQLSCRIPTINFO, 13);
ResString rsDefaultDir (IDS_DEFAULTPROJECTPATH, 20);
register char *Env;

	GetPrivateProfileString (IrisDirs, ErrorDB, "", ErrorDBDir,
						FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, PbdDB, "", PbdDBDir,
						FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, DBase, "", dBaseDir,
						FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, DQLScript, "", DQLScriptDir,
						FULLPATHSIZE+1, Profile);
	GetPrivateProfileString (IrisDirs, rsDefaultDir, "", cbDefaultDir,
						FULLPATHSIZE+1, Profile);
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
	if (!strcmp (DQLScriptDir, "")) {
		_getdcwd (_getdrive(), DQLScriptDir, FULLPATHSIZE);
		if (DQLScriptDir[strlen(DQLScriptDir)-1] != '\\')
			strcat (DQLScriptDir, "\\");
		WritePrivateProfileString (IrisDirs, DQLScript, DQLScriptDir, Profile);
	}
	if (!strcmp (cbDefaultDir, "")) {
		_getdcwd (_getdrive(), cbDefaultDir, FULLPATHSIZE);
		if (DQLScriptDir[strlen(cbDefaultDir)-1] != '\\')
			strcat (cbDefaultDir, "\\");
		WritePrivateProfileString (IrisDirs, rsDefaultDir, cbDefaultDir, Profile);
	}
#ifdef DLL
// in DLL Pfad zu Error-DB setzen
	SetErrorDBEnv (ErrorDBDir);     // ErrorDB Env setzen
#endif
}

// Testen, ob Umgebung korrekt ist --------------------------------------------
Bool TestEnv (HINSTANCE hInst) 
{
#if !defined(WIN32)
// überprüfen, ob Targetprozessor mindestens 80286 ist, bzw. Windows
// im PMode arbeitet
unsigned long WinMode = GetWinFlags ();

	if (WinMode & WF_CPU086 || WinMode & WF_CPU186) {
		db_error (EC_BADCPU, RC_InitIrisApp);
		return FALSE;
	}
	if (!(WinMode & WF_PMODE)) {
		db_error (EC_BADWINMODE, RC_InitIrisApp);
		return FALSE;
	}
#endif
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

// Diese Routine wird kurz vor Ende des Programms abgearbeitet
void IrisWind :: EndCleanUp (void) 
{
// aktuelle Parameter in ProfileDatei schreiben
// 1. Haupfenstergröße
Bool ZoomedFlag = isZoomed ();
Bool IconFlag = isIconic ();
char PStr[_MAX_PATH];

	if (IconFlag || ZoomedFlag) {
	// wenn Ikone, dann alte CanvasKoordinaten merken
		wsprintf (PStr, "%d,%d,%d,%d,%d,%d", ZoomedFlag, IconFlag,
				MOrig.Y()+MSize.Height(), MOrig.X(),
				MOrig.Y(), MOrig.X()+MSize.Width());
	} else {
	// sonst aktuelle FensterKoordinaten wegschreiben
	Rectangle MWnd = WindowRect ();
		wsprintf (PStr, "0,0,%d,%d,%d,%d",
				MWnd.Top(), MWnd.Left(),
				MWnd.Bottom(), MWnd.Right());
	}

// Wegschreiben
ResString IrisStartUp (IDS_STARTUP, 13);
ResString Profile (IDS_PROFILE, 13);
ResString SizeOrg (IDS_SIZEORG, 13);

	WritePrivateProfileString (IrisStartUp, SizeOrg, PStr, Profile);

ResString IrisPars (IDS_IRISPARS, 13);

	ltoa (g_iMinutes, PStr, 10);
	WritePrivateProfileString (IrisPars,
			ResString (IDS_SAVEDELTA, 20), PStr, Profile);
				
// Pointer säubern um post-mortem Zugriff zu verhindern
	DELETE (pToolBox);
	DELETE (pLegende);
}


// AspectRatio des Fenster holen ----------------------------------------------
Point IrisWind :: GetAspectRatio (void) 
{
HWND hWnd = Handle (API_CLIENT_HWND);
HDC hDC = :: GetDC (hWnd);

CoOrd LogPixelsX = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSX);
CoOrd LogPixelsY = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSY);

	ReleaseDC (hWnd, hDC);

return Point (LogPixelsX, LogPixelsY);
}

// HilfeRequestEventHandler ---------------------------------------------------
void IrisWind :: HelpRequest (HelpRequestEvt e) 
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
		case Unknown:
		case MenuBar:
		default:
			break;
		}
		break;

	case HelpControl:
	default:
		break;
	}
}


// Version der GeoDB bestimmen ------------------------------------------------
static long __GeoDBVersion__ = -1L;

long GetGeoDBVersion (GeoDB *pDB) 
{
// wenn Version schon bestimmt ist
	if (__GeoDBVersion__ != -1L) return __GeoDBVersion__;

CActDB ActDB (pDB ? *pDB : ((IrisWind *)CurrActDirisW) -> DBO().DB());

	if (!ActDB) return -1L;		// Version nicht bestimmbar

return (__GeoDBVersion__ = GetDBVersion());
}

/*
long GetGeoDBVersion (void) 
{
// wenn Version schon bestimmt ist
	if (__GeoDBVersion__ != -1L) return __GeoDBVersion__;

IrisWind *pIW = (IrisWind *)CurrActDirisW;
CActDB ActDB (pIW -> DBO().DB());

	if (!ActDB) return -1L;		// Version nicht bestimmbar

return (__GeoDBVersion__ = GetDBVersion());
}
*/

// wenn neue GeoDB eröffnet wird, dann rücksetzen -----------------------------
void ResetGeoDBVersion (void) { __GeoDBVersion__ = -1L; }


// Letzten verwendeten Ident für neues Objekt verwalten -----------------------
long IrisWind :: GetLastIdent (void)
{
	if (m_lLastIdent == -1L) {
	// letzten verwendeten aus Projekt-INI lesen
	char cbPrj[_MAX_PATH+1];
	
		if (NULL == DEX_GetActiveProject (cbPrj)) return -1L;
	
	ProFile PF (cbPrj);
	
		m_lLastIdent = PF.GetLastIdent();
	}
	
return m_lLastIdent;
}


void IrisWind :: SetLastIdent (long lIdent)
{
	if (lIdent == m_lLastIdent) return;	// nothing to do

char cbPrj[_MAX_PATH+1];
	
	if (NULL == DEX_GetActiveProject (cbPrj)) return;
	
ProFile PF (cbPrj);

	PF.SetLastIdent (lIdent);
	m_lLastIdent = lIdent;
}

#if !defined(WIN32)
// WindowsVersion feststellen -------------------------------------------------
static bool s_fWin31 = false;
static bool s_fWin40 = false;
static bool s_fWinNT = false;
static bool s_fWin32s = false;

void InitWindowsVersion (void)
{
// Initialise Version Info
DWORD dwVersion = GetVersion();

	s_fWin31 = false;
	s_fWinNT = false;
	s_fWin32s = false;
	s_fWin40 = false;

// #if defined(WIN32)
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
/*#else
	if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
	    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
		s_fWin31 = true;
#endif
*/
}

bool IsWin31 (void) { return s_fWin31; }
bool IsWin40 (void) { return s_fWin40; }
bool IsWin32s (void) { return s_fWin32s; }
bool IsWinNT (void) { return s_fWinNT; }

#endif // WIN32

// Aus Registry Voreinstellungen einlesen -------------------------------------
bool ReadRegistryOptions (void)
{
	g_fSystemAdm = false;

#if defined(WIN32)
	if (!IsWin32s()) {
	CCurrentUser regCfg (TEXT("Software\\uve\\TRiAS\\Config"));
	DWORD dwData = 0L;
	
		if (regCfg.GetDWORD (TEXT("SystemAdministration"), dwData))
			g_fSystemAdm = (dwData != 0) ? true : false;
#if defined(_DEBUG)
		g_iKonsFlags = KTDDiagnose;
		if (regCfg.GetDWORD (TEXT("KonsistenzTest"), dwData))
			g_iKonsFlags = short(dwData);
#endif
	} else
#endif // WIN32
	{
	ResString Profile (IDS_PROFILE, 13);
	ResString IrisPars (IDS_IRISPARS, 13);

		g_fSystemAdm = (0 != GetPrivateProfileInt (IrisPars,
					TEXT("SystemAdministration"), 0, Profile)) ? 
				true : false;
	}
	
return true;
}


///////////////////////////////////////////////////////////////////////////////
//
void DragRectangleObject :: ProcessKey (KeyEvt)
{ 
	Process (m_end); 
}

bool DragRectangleObject :: ToProcessKey (void)
{
bool fControl = GetKeyState (VK_MENU) < 0;
bool fShift = GetKeyState (VK_SHIFT) < 0;

	return (fControl != m_fControl) || (fShift != m_fShift);
}

bool DragRectangleObject :: isDirty (void)
{
	return false;
}

DRAGTYPE DragRectangleObject :: isA (void)
{ 
	return DT_DRAGRECTANGLE; 
}

void DragRectangleObject :: Process (Point end)
{
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
void DragLineObject :: Process (Point Pt)
{ 
	end = Pt; 
}

bool DragLineObject :: isDirty (void)
{
	return false;
}

DRAGTYPE DragLineObject :: isA (void)
{ 
	return DT_DRAGLINE; 
}

void DragLineObject :: ProcessKey (KeyEvt) 	// TastenDruck verarbeiten
{
}

bool DragLineObject :: ToProcessKey (void)
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

#if defined(WIN32)
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
#endif // WIN32

