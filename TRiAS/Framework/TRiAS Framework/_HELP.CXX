/* $Header:   G:/cv.win/pvcs/commonvu/src/_help.cxv   3.0.1.0   14 Jul 1992 11:55:40   RONAN  $
 *
 *	_ h e l p . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Created	25Apr90 from _accel.cxx as public interface (nc)
 *
 *	Mods log:
 *	1.0	rs		19 Oct 1990	 Initial development
 *
 */ 
#include "tfrmpre.hxx"
#include 	<_link.hxx>



/* Commands to pass WinHelp() */
//#define HELP_CONTEXT	0x0001	 /* Display topic in ulTopic */
//#define HELP_QUIT		0x0002	 /* Terminate help */
//#define HELP_INDEX		0x0003	 /* Display index */
//#define HELP_HELPONHELP 	0x0004	 /* Display help on using help */
//#define HELP_SETINDEX		0x0005	 /* Set the current Index for multi index help */
//#define HELP_KEY		0x0101	 /* Display topic for keyword in offabData */
//#define HELP_MULTIKEY   	0x0201

//extern "C" long	_cdecl	atol(const char *);

//=======================================================
// HelpDisplay functions
//=======================================================

_DLLENTRY HelpDisplay :: HelpDisplay ( const char* name)
{
	hd_imp = new HelpDisp_Imp(name);
}

_DLLENTRY HelpDisplay :: ~HelpDisplay ()
{
	if (hd_imp)
		delete hd_imp;
}

BOOL _DLLENTRY HelpDisplay :: Show ( const char* key)
{
	return hd_imp -> Show(key);
}

BOOL _DLLENTRY HelpDisplay :: Show ( ulong key)
{
	return hd_imp -> Show(key);
}


HdError _DLLENTRY HelpDisplay :: HelpError()
{
	return hd_imp -> HelpError();
}  

HANDLE	_DLLENTRY HelpDisplay :: Handle(Service)
{
	return 0;
}


//==========================================
// HelpDisp_Imp functions
//==========================================
HelpDisp_Imp :: HelpDisp_Imp ( const char* name)
{
	helpfile = CV_strdup(name);
	error = HdOk;
	helpwnd = 0;
}

HelpDisp_Imp :: ~HelpDisp_Imp ()
{
	if (helpwnd) {
		WinHelp(helpwnd, helpfile, HELP_QUIT, (ulong)0);
		DestroyWindow(helpwnd);
		helpwnd = 0;
	}
	if (helpfile)
		delete helpfile;
}

BOOL HelpDisp_Imp :: VerifyHelp (void)
{
	if (!helpwnd) {	// Create dummy window for use with help system 
	pApp_Imp AppImpInst = _AppImpFind();

		helpwnd = CreateWindow (GetRegClassString(Rcs_AppWindow), 
					StaticPtr(""),
					WS_CLIPCHILDREN | WS_OVERLAPPED,
					CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
					0, 0,
					CV_RunTime :: App_hApp(AppImpInst),
					0
			  );
		if (!helpwnd) {
			error = HdUnknown;
			return false;
		}
	}

return true;
}

/*=========================================================================
 *
 * The following forms may be used for getting help in windows :-
 *
 * Show("<number>"); 				shows context specified by number
 * Show("HelpOnHelp");
 * Show("HelpOnKeys");
 * Show("HelpIndex");
 * Show("HelpIndex:<number>");		use alternative index.
 * Show("[<context>]<keyword>"); 	look up keyword in context 
 * Show("<keyword>"); 				look up keyword 
 *
 *========================================================================*/
BOOL HelpDisp_Imp :: Show (const char* key)
{	
BOOL retval;
int len;

 	if (!key || ((len = lstrlen(key)) == 0)) {
		error = HdInvalidKey;
		return false; 
	}
	if (!VerifyHelp())
		return false;

	if ((key[0] >= '0') && (key[0] <= '9')) {
		ulong l = atol ( key);
		retval = WinHelp(helpwnd, helpfile, HELP_CONTEXT, l);
	}
	else if ((key[0] == '[') && (len > 3) && (key[2] == ']')) {
	int ms = sizeof(MULTIKEYHELP) + len;
	MULTIKEYHELP *mkey = (MULTIKEYHELP*) new char[ms];
	
		mkey -> mkSize = ms;
		mkey -> mkKeylist = key[1];
		lstrcpy ((char *)mkey -> szKeyphrase, &(key[3]));
		retval = WinHelp(helpwnd, helpfile, HELP_MULTIKEY, (ulong)mkey);
		delete mkey;
	} else {
		if (lstrcmp("HelpOnHelp", key) == 0)	
			retval = WinHelp (helpwnd, helpfile, HELP_HELPONHELP, (ulong)0);
		else if (lstrcmp("HelpIndex", key) == 0)	
			retval = WinHelp (helpwnd, helpfile, HELP_INDEX, (ulong)0);
		else {
			retval = WinHelp (helpwnd, helpfile, HELP_KEY, (ulong)key);
			if (!retval)
				retval = WinHelp (helpwnd, helpfile, HELP_INDEX, (ulong)0);
		}
	}
	if (!retval)
		error = HdInvalidKey;
	else
		error = HdOk;

return retval;
}

BOOL HelpDisp_Imp :: Show (ulong key)
{
BOOL retval;

	if (!VerifyHelp())
		return false;

	retval = WinHelp (helpwnd, helpfile, HELP_CONTEXT, key);
	if (!retval)
		error = HdInvalidKey;
	else
		error = HdOk;

return retval;
}

HdError HelpDisp_Imp :: HelpError()
{
	return error;
}	

//=======================================================
// Wind_Imp Functions for HelpSupport
//=======================================================
void Wind_Imp :: EnableHelp (BOOL enabled, HelpDisp_Imp *hdi)
{
	if (enabled && !WindMgt.HelpOn) {
		WindMgt.HelpOn = true;
		if (GetActiveWindow() == hEContext)
			_AppImpFind() -> SetHelpWind(hEContext, HM_GENERAL);
		CurrentHelp = hdi;
	}
	else if (WindMgt.HelpOn && (!enabled)) {
		WindMgt.HelpOn = false;
		EnableHelpCursor(false);
		if (GetActiveWindow() == hEContext)
			_AppImpFind() -> SetHelpWind(0, HM_NONE);
		CurrentHelp = 0;
	}
}

void Wind_Imp :: EnableHelpCursor (BOOL enabled)
{
	WindMgt.HelpMenu = enabled;
	if (enabled && (!WindMgt.HelpCursorOn)) {
		WindMgt.HelpCursorOn = true;
		SetCursor(hHelpCursor);
		if (GetActiveWindow() == hEContext)
			_AppImpFind() -> SetHelpWind(hEContext, HM_MOUSE);
	}
	else if ((!enabled) && WindMgt.HelpCursorOn) {
		WindMgt.HelpCursorOn = false;
		if (isVisible() && (!GetCapture())) {
		Point p;
		long hitArea;
		
			GetCursorPos((POINT *)&p);

		// Locate Window or ChildWindow currently containing cursor.
		// This is needed for passing to WM_SETCURSOR
		HWND hWndCursor = WindowFromPoint(*(POINT *)&p); // TopAppWindow containing point.
		HWND hWndChildCursor = ChildWindowFromPoint(hWndCursor, *(POINT *)&p);

			if (hWndChildCursor && IsWindowVisible (hWndChildCursor))
				hWndCursor = hWndChildCursor;

			hitArea = SendMessage(hEContext, WM_NCHITTEST, 0, (*((long*)(&p))) );
			SendMessage(hEContext, WM_SETCURSOR, (WPARAM)hWndCursor, hitArea | (WM_MOUSEMOVE >> 16));
		}
		if (GetActiveWindow() == hEContext)
			_AppImpFind() -> SetHelpWind(hEContext, HM_GENERAL);
	}
}							  

BOOL Wind_Imp :: ProcessHelpCursor (HWND hw, uint area)
{
pApp_Imp AppImpInst = _AppImpFind();

// is it a window or child window
	if  ((hw == hEContext) ||
	     (AppImpInst -> ContextList() -> TaskFind ((HANDLE)hw)))
	{
	WindowArea w = UnknownArea;

		switch (area) {
		case HTCAPTION:	
			w = Caption;
			break;

		case HTCLIENT:
			w = WindowCanvas;
			break;

		case HTBOTTOM:
		case HTBOTTOMLEFT:
		case HTBOTTOMRIGHT:
		case HTTOP:
		case HTLEFT:
		case HTRIGHT:
		case HTTOPLEFT:
		case HTTOPRIGHT:
			w = Border;
			break;

		case HTREDUCE:
			w = MinBox;
			break;

		case HTZOOM:
			w = MaxBox;
			break;

		case HTSYSMENU:
			w = SysMenuBox;
			break;

		case HTMENU:
//			w = MenuBar;
//			break;
// erstmal durchfallen .....
		default:
			w = UnknownArea;
			break;
		}

		if ((w == UnknownArea) && (area != HTNOWHERE)) 
			return false;
		
		PostMessage(hw, WM_CVHELP, (uint)HelpWindow, (ulong)w);
	}
	else {	// Its a control
	HWND oldc;
	
		do {	// Find its parent
			oldc = hw;
			hw = ::GetParent (oldc);
		} while ((hw != hEContext) &&
		         !(AppImpInst -> ContextList() -> TaskFind ((HANDLE)hw)));
		
		PostMessage(hw, WM_CVHELP, (WPARAM)HelpControl, (LPARAM)(HANDLE)oldc);
	}

return true;
}

BOOL Wind_Imp :: FilterHelpCursor (uint area)
{
WindowArea w = UnknownArea;

	switch (area) {
	case HTCAPTION:	
		w = Caption;
		break;

	case HTCLIENT:
		w = WindowCanvas;
		break;

	case HTBOTTOM:
	case HTBOTTOMLEFT:
	case HTBOTTOMRIGHT:
	case HTTOP:
	case HTLEFT:
	case HTRIGHT:
	case HTTOPLEFT:
	case HTTOPRIGHT:
		w = Border;
		break;

	case HTREDUCE:
		w = MinBox;
		break;

	case HTZOOM:
		w = MaxBox;
		break;

	case HTSYSMENU:
		w = SysMenuBox;
		break;

	case HTMENU:
//		w = MenuBar;
//		break;
// erstmal durchfallen .....
	default:
		w = UnknownArea;
		break;
	}

	if (w == UnknownArea)
		return false;
	else
		return true;
}

//=======================================================
// HelpRequestEvt Functions 
//=======================================================
HelpType _DLLENTRY HelpRequestEvt :: RequestType (void) 
{
	return (HelpType)wParam;
}

uint _DLLENTRY HelpRequestEvt :: GetItemID (void) 
{
	if (((HelpType)wParam) == HelpMenu)
		return (uint) lParam;
	else if (((HelpType)wParam) == HelpControl) {
	uint id;
#if !defined(WIN32)
		if ((id = GetWindowWord ((HWND)lParam, GWW_ID)) == (-1))
#else
		if ((id = GetWindowLong ((HWND)lParam, GWL_ID)) == (-1))
#endif
			return id;
		else
			return (id & ~CV_CTRL_Mask);
	} else
		return 0;
}

Point _DLLENTRY HelpRequestEvt :: Where (void) 
{
Point p;

	  GetCursorPos ((POINT *)&p);
	  ScreenToClient (CV_RunTime :: Handle((pWind_Imp)EvtExtra), (POINT *)&p);

return CV_RunTime :: DevToLog ((pWind_Imp)EvtExtra, (Point&)p);
}

WindowArea _DLLENTRY HelpRequestEvt :: GetWindowArea (void)
{
	if (RequestType() == HelpWindow)
		return (WindowArea)lParam;
	else
		return UnknownArea;
}

//=======================================================
// HelpRequest Functions 
//=======================================================
void CAWind_Imp::  HelpRequest (HelpRequestEvt e)
{
	SendMessage (CV_RunTime :: Handle(WndParent), WM_CVHELP, 
		     CV_RunTime :: Event_wParam(e),
		     CV_RunTime :: Event_lParam(e));
}

void DocWind_Imp :: HelpRequest (HelpRequestEvt e)
{
	SendMessage (CV_RunTime :: Handle(WndParent), WM_CVHELP, 
		     CV_RunTime :: Event_wParam(e),
		     CV_RunTime :: Event_lParam(e));
}

void Wind_Imp :: HelpRequest (HelpRequestEvt e)
{
char buffer[60];
bool doSearch = true;

	buffer[0] = '\0';
	switch (e.RequestType()) {
	case HelpMenu:
		{
			if (e.GetItemID() && (e.GetItemID() != (-1))) {
			char MenuText[40];
			char MenuCleanText[40];
			int i = 0, j = 0;

			// Get menu string for menu item selected
			pMenu menu;

				if (CV_RunTime :: Event_lParam(e) & 0x00010000) // Its a system menu
				{
					menu = (pMenu)(_AppImpFind() -> MenuList()	
						->Find ((HANDLE)GetSystemMenu (hEContext, false)));
				} else
	 				menu = WndMenu;

				if (!menu) {
					doSearch = false;
					break;
				}
				GetMenuString (menu -> Handle(),	// KickDown
					       e.GetItemID(), MenuText,
					       39, MF_BYCOMMAND);

			// Process menu string for lookup
				if (!MenuText[0]) {
					doSearch = false;
					break;
				}

			// Skip leading spaces
				while (MenuText[i] && (MenuText[i] == ' '))
					i++;
				
				while (MenuText[i] && (MenuText[i] != '\t')) {
					switch (MenuText[i]) {
					case '&':
						i++;
						break;

					case ' ':
						MenuCleanText[j++] = '_';
						i++;
						break;

					case '.':
						{
						int k = i+1; 

							while (MenuText[k] && (MenuText[k] == '.'))
								k++;
							if (k == (i+1))
								MenuCleanText[j++] = '.';
 							else
								i = k;
							break;
						}

					default:
						MenuCleanText[j++] = MenuText[i++];
						break;
					}
				}
				MenuCleanText[j] = '\0';
				wsprintf(buffer, "[C]Menu_%s", MenuCleanText);
			}
		}
		break;

	case HelpWindow:
		{
		char AreaName[20];
		
			if (e.GetWindowArea() == UnknownArea)
				wsprintf(buffer, "HelpIndex");
			else {
			uint AreaIndex = (uint)e.GetWindowArea();
			
				if (AreaIndex > 7) 
					AreaIndex = 7;
				LoadString (CV_LibHandle(), 0x0800 + AreaIndex, AreaName, 20);
				wsprintf(buffer, "[C]Window_%s", AreaName);
			}
		}
		break;

	case HelpControl:
		{
		int i = (int)e.GetItemID();

			if (i < 0)
				doSearch = false;
			else
				wsprintf(buffer, "[C]Control_%d", e.GetItemID());
		}
		break;
	};

	if (CurrentHelp && doSearch)
		CurrentHelp -> Show (buffer);
}


void _DLLENTRY Window :: HelpRequest (HelpRequestEvt e)
{
	((pWind_Imp)ec_Imp) -> HelpRequest (e);
}


void _DLLENTRY Window :: EnableHelp (BOOL enabled, HelpDisplay * AutoHelp)
{
	((pWind_Imp)ec_Imp) -> EnableHelp (enabled, CV_RunTime :: pHD_to_pImp(AutoHelp));
}


