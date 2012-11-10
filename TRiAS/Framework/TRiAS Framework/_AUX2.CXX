/*    PortTool v2.2     _aux2.cxx          */

/* $Header:   G:/cv.win/pvcs/commonvu/src/_aux2.cxv   3.0.1.0   14 Jul 1992 11:48:20   RONAN  $
 *
 *	_ a u x 2 . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.1	ferg	28sep88	added functions for returning the #defined value
 *						of a string.
 *	0.0 ferg	05oct88	------- Milestone 2. Beta 2 Shipped ---------
 *	0.2	ferg	02nov88	implemented registration of App Instance within DLL
 *						gets over dependencies on AppInst in User data seg.
 *	0.3 jk		29nov88 ------ Milestone 2A. Beta 2A shipped ------
 *	0.4 jk		02dec88	Fast Compile defines added.
 *  0.5 rs      18jan89 Added directory seperator to strings table
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *	1.1 rs		28jun89	Routines to manipulate window information on
 *						property list.
 *  1.2	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.3	rs		23aug89	Debugging code
 *	1.4	rs		09oct89 Version number tracking to support Windows 3.0
 *  1.5	hl		20sep89	use AnsiUpper instead of toupper                                      
 *
 *	1.6 rs		Rewrite of debugging system .
 *				The library module handle is maintained to allow
 *				debugging strings etc to go into dynalink resource file
 *				(hence using no local heap space).
 *
 *
 */


#include "tfrmpre.hxx"

#include <_Link.hxx>
#include <zyzgauge.h>

// #define	GMEM_FIXED	0

extern "C" {
	extern void PASCAL StaticDataInit(HINSTANCE);			// * 1.2 *
	HINSTANCE PASCAL CV_LibHandle(void);
#if !defined(WIN32)
	extern char  * StaticPtr(void near *);
#endif
}

int 			CVDebugging = 0;
int 			CVProfiling = 0;
HCURSOR			hHelpCursor = 0;

static bool	bWin31 = false;	// * 1.4 * 
#if defined(WIN32)
static bool	bWinNT = false;	// * 1.4 * 
static bool	bWin40 = false;	// * 1.4 * 
static bool bWin32s = false;
#endif
static HINSTANCE	hLib	= 0;
static bool bIstrueTypeEnabled = false;
static bool bUsetrueTypeOnly = false;
static bool bUsePrivateDC= false;

 /* ======================================================================= */
 /*    Debugging code                                                       */
 /* ======================================================================= */
#if defined(_DEBUG)
static void DebugInit();
DebugOptions Options;
#endif
 /* ======================================================================= */
 /*    End of Debugging code                                                */
 /* ======================================================================= */

static	const char	* Strings[ 22 ]	=
{
	"Static",	// CTRL_Static
	"ScrollBar",	// CTRL_ScrollBar
	"Button",	// CTRL_Button
	"ListBox",	// CTRL_ListBox
	"Edit",		// CTRL_Edit
	"ComboBox",	// CTRL_ComboBox
#if defined(WIN32)
	"GaugeBox32",	// CTRL_GaugeBox32
	WC_TREEVIEW,	// CTRL_CTreeListCtrl
	WC_LISTVIEW,	// CTRL_ListViewCtrl
	TOOLTIPS_CLASS,	// CTRL_ToolTipCtrl
	TOOLBARCLASSNAME,	// CTRL_ToolBarCtrl
	STATUSCLASSNAME,	// CTRL_StatusBarCtrl
	UPDOWN_CLASS,	// CTRL_SpinButtonCtrl
	PROGRESS_CLASS,	// CTRL_ProgressBarCtrl
	ANIMATE_CLASS,	// CTRL_AnimateCtrl
	HOTKEY_CLASS,	// CTRL_HotkeyCtrl
	WC_COMBOBOXEX,	// CTRL_ComboBoxEx
#else
	"GaugeBox",	// CTRL_GaugeBox
#endif
	"\0" 		// An empty string
};

static char CvMFW[30] = "TRiASMdiFrame";
static char CvAppW[30] = "TRiASMain";
static char CvMCW[30] = "TRiASMdiChild";
static char CvMDI_Default[30] = "TRiASMdiDef";

/************************************************************************
 * InitRegClassString()
 *
 * Initialise class names for CA-CommonView registered classes
 * These must be constructed based on the DLL name to avoid conflicts when
 * using different versions of the CA-CommonView DLL simultaneously
 * This implementation may need to be changed when using later versions of
 * Windows to cope with file names > 8
 *************************************************************************/
#if !defined(WIN32)
void  _loadds InitRegClassString ( ) 
#else
void InitRegClassString (void) 
#endif
{
char mfn [_MAX_PATH+1];

// Parse module name

	GetModuleFileName (hLib, mfn, _MAX_PATH);

int offset = lstrlen (mfn);

// Skip to '.' of extension

	while (offset && (mfn[offset-1] != '.'))
		   offset --;
	if (offset) {
		mfn[--offset] = '\0';
		while(offset && (mfn[offset-1] != '\\') && (mfn[offset-1] != ':'))  
			--offset;
	}

// We are now positioned at start of DLL name
	if (offset) {
		wsprintf (CvMFW, "TRiASMdiFrame_%.8s", &mfn[offset]);
		wsprintf (CvAppW, "TRiASMain_%.8s", &mfn[offset]);
		wsprintf (CvMCW, "TRiASMdiChild_%.8s", &mfn[offset]);
		wsprintf (CvMDI_Default, "TRiASMdiDef_%.8s", &mfn[offset]);
	} else {
		lstrcpy (CvMFW, "TRiASMdiFrame");
		lstrcpy (CvAppW, "TRiASMain");
		lstrcpy (CvMCW, "TRiASMdiChild");
		lstrcpy (CvMDI_Default, "TRiASMdiDef");
 	}
}

char*  GetRegClassString (RegClassString r) 
{
	switch (r) {
	case Rcs_MdiFrame:
		return CvMFW;
		break;

	case Rcs_MdiChild:
		return CvMCW;
		break;

	case Rcs_MdiDefChild:
		return CvMDI_Default;
		break;

	case Rcs_AppWindow:
	default:
		return CvAppW;
	}
}

const char* 	PASCAL_FUNC _GetString ( uint i )
{
	if (i) 
		return	Strings[ i - 1 ];
	else
		return 0;

}	// End of FUNCTION "_GetString"

/*														* 0.1 Begin *
 *	_GetStringValue()
 *
 *	return the integer value corresponding to the specified string.
 *	e.g for "ScrollBar" return CTRL_ScrollBar.
 */
uint	PASCAL_FUNC _GetStringValue ( const char * s1 )
{
	uint ret = 0;

	for ( int n = 0; * Strings[ n ]; ++n )
	{
		if ( lstrcmpi ( s1, Strings[ n ] ) == 0 )
			ret =  n + 1 ;
	}
	return ret;
}

extern "C" HINSTANCE WINAPI CV_LibHandle (void) 	// * 1.6 * 
{
	return hLib;
}

int   PASCAL_FUNC IsWin31()
{
	return bWin31;
}

#if defined(WIN32)
bool IsWin40 (void)
{
	return bWin40;
}
bool IsWinNT (void)
{
	return bWinNT;
}
bool IsWin32s (void)
{
	return bWin32s;
}
#endif

int   PASCAL_FUNC IsTrueTypeEnabled()
{
	return bIstrueTypeEnabled;
}

int   PASCAL_FUNC UseTrueTypeOnly()
{
	return bUsetrueTypeOnly;
}

int   PASCAL_FUNC UsePrivateDC()
{
	return bUsePrivateDC || IsWinNT();	// #HK980510: unter NT immer OWNDC's
}


bool   PASCAL_FUNC isDSinDLL(uint thisDS)
{
#if !defined(WIN32)
	return (thisDS == _getDS());
#else
	return true;	// immer richtig
#endif
}


/*
void  _cdecl __pure_virtual_called()
{
	FatalAppExit (0, StaticPtr ("C++ : Pure virtual function called"));
} 
*/

 /* ======================================================================= */
 /*    Desktop management code                                              */
 /* ======================================================================= */
#ifdef BETA
FARPROC oldDeskTopProc = NULL;
static char BetaBanner[_MAX_PATH+1];

void SubclassDeskTop()
{
	if (oldDeskTopProc) return;	// only once

	oldDeskTopProc = (FARPROC) SetWindowLong(GetDesktopWindow(), GWL_WNDPROC, (unsigned long) CvDesktopDispatcher);
	if (!LoadString(hLib, ID_BETABANNER, BetaBanner, _MAX_PATH))
		lstrcpy(BetaBanner, "TRiAS® Framework Debugging");
	InvalidateRect(GetDesktopWindow(), NULL, true);
}

void UnSubclassDeskTop()
{
	SetWindowLong(GetDesktopWindow(), GWL_WNDPROC, (unsigned long) oldDeskTopProc);
	InvalidateRect(GetDesktopWindow(), NULL, true);
	oldDeskTopProc = NULL;
}
#endif

extern "C" long WINAPI _DISPATCH_ENTRY
CvDesktopDispatcher (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef BETA

	CV_ASSERT_DLLDS();

long result = 0L;

    switch (message) {

	case WM_ERASEBKGND:
	case WM_PAINT:
		{
			HANDLE hDC;
			int oldMode;
			unsigned long cr;
	    	result = CallWindowProc((ulong)oldDeskTopProc, hWnd, message, wParam, lParam);
			hDC = GetDC(hWnd);
			oldMode = SetBkMode(hDC,TRANSPARENT);
			TextOut(hDC, 13,13, BetaBanner, lstrlen(BetaBanner));
			cr = SetTextColor(hDC, 0x0ffffff);
			TextOut(hDC, 10,10, BetaBanner, lstrlen(BetaBanner));
			SetTextColor(hDC, cr);
			SetBkMode(hDC, oldMode);
			ReleaseDC(hWnd, hDC);
			return result;
		}
		
	default:
	    return CallWindowProc((ulong)oldDeskTopProc, hWnd, message, wParam, lParam);
    }
#endif
    return NULL;
}

 /* ======================================================================= */
 /*    DLL init and cleanup code                                            */
 /* ======================================================================= */

extern "C" void WINAPI StaticDataInit (HINSTANCE hl)	// * 1.4 * start
{
	hLib = hl;									// * 1.6 *

// Initialise Version Info
DWORD dwVersion = GetVersion();

	bWin31 = false;

#if defined(WIN32)
	bWin40 = false;
	if (dwVersion < ~0x7fffffff) {			// Windows NT
		bWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				bWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 3) {
			bWin40 = true;	// NT4.0
			bWin31 = true;
		}
	} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			bWin31 = true;
		bWin32s = true;
	} else {					// Chicago
		bWin31 = true;
		bWin40 = true;
	}
#else
	if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
	    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
		bWin31 = true;
#endif

// Initialise trueType Info 
	if (bWin31) {
		if (GetProfileInt("trueType", "TTEnable", 0)) {
			bIstrueTypeEnabled = true;
			if (GetProfileInt("trueType", "TTOnly", 0))
				bUsetrueTypeOnly = true;
		}
	}

// Initialise help system 
	hHelpCursor = LoadCursor (hLib, "HelpCursor");

	InitRegClassString();

#if defined(_DEBUG)
	DebugInit();
#endif

// Initialise class for CA-CommonView windows, but only once
WNDCLASS wc;
		
// Class for CA-CommonView App Window
	if (!GetClassInfo (hLib, (pchar)GetRegClassString(Rcs_AppWindow), &wc)) {
		wc.style		= (CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | (UsePrivateDC() ? CS_OWNDC :0));
		wc.lpfnWndProc		= (WNDPROC)EventDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hLib;
		wc.hIcon		= NULL;
		wc.hCursor		= LoadCursor ( NULL, IDC_ARROW );
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= (pchar)GetRegClassString(Rcs_AppWindow);
		RegisterClass (&wc);
	}

// Class for CA-CommonView MDI Child Window 
	if (!GetClassInfo (hLib, (pchar)GetRegClassString(Rcs_MdiChild), &wc)) {
		wc.style		= (CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | (UsePrivateDC() ? CS_OWNDC :0));
		if (IsWin31())
			wc.lpfnWndProc	= (WNDPROC)CvMdiChildDispatcher;
		else
			wc.lpfnWndProc	= (WNDPROC)MDIChildDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hLib;
		wc.hIcon		= NULL;
		wc.hCursor		= LoadCursor ( NULL, IDC_ARROW );
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= (pchar)GetRegClassString(Rcs_MdiChild);
		RegisterClass (&wc);
	}

// Class for CA-CommonView Shell Window 
	if (!GetClassInfo (hLib, (pchar)GetRegClassString(Rcs_MdiFrame), &wc)) {
		wc.style		= (CS_GLOBALCLASS | CS_DBLCLKS | CS_BYTEALIGNCLIENT);
		wc.lpfnWndProc		= (WNDPROC)CvMdiFrameDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 4;
		wc.hInstance		= hLib;
		wc.hIcon		= NULL;
		wc.hCursor		= LoadCursor ( NULL, IDC_ARROW );
		wc.hbrBackground	= (HBRUSH)COLOR_APPWORKSPACE+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= (pchar)GetRegClassString(Rcs_MdiFrame);
		RegisterClass (&wc);
	}

// Class for CA-CommonView MDI Default Child Window 
	if (!GetClassInfo (hLib, (pchar)GetRegClassString(Rcs_MdiDefChild), &wc)) {
		wc.style		= ( CS_GLOBALCLASS | CS_BYTEALIGNCLIENT);
		wc.lpfnWndProc		= (WNDPROC)MdiDefChildDispatcher;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= hLib;
		wc.hIcon		= NULL;
		wc.hCursor		= LoadCursor ( NULL, IDC_ARROW );
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW+1;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= (pchar)GetRegClassString(Rcs_MdiDefChild);
		RegisterClass (&wc);
	}

	GaugeBoxInit (hLib);	// Init GaugeBox CustomControl

#ifdef BETA
	SubclassDeskTop();
#endif
}						  
	
#if !defined(WIN32)
void   PASCAL_FUNC _loadds StaticDataCleanup()
#else
extern "C" void WINAPI StaticDataCleanup (void)
#endif
{
// Do not cause the sending of messages at this point as the queue may be in
// an unstable state.

#ifdef BETA
	UnSubclassDeskTop();
#endif
}

 /* ======================================================================= */
 /*    Debugging code                                                       */
 /* ======================================================================= */

#if defined(_DEBUG)

void    DebugInit()
{
char buffer[20];

	Options.DebugCount = 0;
	Options.Tracking = 0;
	Options.TmpFlag = 0;

// Is profiling enabled
// Is debugging output enabled 
	CVDebugging = GetProfileInt ("TRiASFrameWork", "DebugMessageOutput", 0);

// is debug message counting enabled
	GetProfileString("TRiASFrameWork", "DebugCounting", "NO", buffer,20);
	if (lstrcmpi(AnsiUpper(buffer), "YES") == 0)
		Options.DebugCountOn = 1;
	else
		Options.DebugCountOn = 0;

// Is event tracking on
	GetProfileString("TRiASFrameWork", "EventTracking", "", buffer,20);
	if (lstrcmpi(AnsiUpper(buffer), "ALL") == 0)
		Options.Tracking |= 
			(CVTRACK_MOUSE | CVTRACK_WINDOWS | CVTRACK_INPUT |
			CVTRACK_SYSTEM | CVTRACK_INIT | CVTRACK_CLIPBOARD |
			CVTRACK_DDE	| CVTRACK_NONCLIENT	);
	else {
	int i = 0;
	
		while (buffer[i]) {
			switch (buffer[i]) {
			case 'M':
			case 'm':
				Options.Tracking |= CVTRACK_MOUSE;
				break;

			case 'W':
			case 'w':
				Options.Tracking |= CVTRACK_WINDOWS;
				break;

			case 'N':
			case 'n':
				Options.Tracking |= CVTRACK_INPUT;
				break;

			case 'S':
			case 's':
				Options.Tracking |= CVTRACK_SYSTEM;
				break;

			case 'I':
			case 'i':
				Options.Tracking |= CVTRACK_INIT;
				break;

			case 'c':
			case 'C':
				Options.Tracking |= CVTRACK_CLIPBOARD;
				break;

			case 'd':
			case 'D':
				Options.Tracking |= CVTRACK_DDE;
				break;

			case 'z':
			case 'Z':
				Options.Tracking |= CVTRACK_NONCLIENT;
				break;

			case ' ':
			default:
				break;
			}
			 i++;
		}
	}

	if (Options.DebugFlag && Options.Tracking) {
	char banner[_MAX_PATH+1];
	
		OutputDebugString("====================================================\n\r");
		if (LoadString(hLib, ID_DEBUGBANNER, banner, _MAX_PATH))
			OutputDebugString(banner);
		else
			OutputDebugString("TRiAS® Framework \n\r");
		OutputDebugString("====================================================\n\r");
	}

// Use captions as window names ???
	GetProfileString("TRiASFrameWork", "EventTrackingNames", "NO", buffer,20);
	if (lstrcmpi(AnsiUpper(buffer), "YES") == 0)
		Options.Tracking |= CVTRACK_NAMES;

// Use private dc's in CA-CommonView app windows
	GetProfileString("TRiASFrameWork", "UsePrivateDC", "NO", buffer,20);
	if (lstrcmpi(AnsiUpper(buffer), "YES") == 0)
		bUsePrivateDC = true;
}

DebugOptions  * CVDebugOptions()
{
	return &Options;
}

#endif // _DEBUG
 /* ======================================================================= */
 /*    End of Debugging code                                                */
 /* ======================================================================= */

