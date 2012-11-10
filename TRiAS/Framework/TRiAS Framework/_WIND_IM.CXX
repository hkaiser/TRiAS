/* $Header:   G:/cv.win/pvcs/commonvu/src/_wind_im.cxv   3.0.1.0   14 Jul 1992 11:56:10   RONAN  $
*
* 	_ W I N D _ I M . C X X
*	
*  Copyright (c) 1992 Trischford Limited 
*  ( A wholly owned subsidary of Computer Associates International, Inc)
*  All Rights Reserved
*
*	Version 3.1			Nov 1992
*
*	Modification log:
*	0.1	ferg	26sep88	new member of Window, TextSize().
*	0.2	ferg	28sep88	fix to secure dispatching of Control Notifications
*						to their correct CA-CommonView events.
*	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
*	0.3	ferg	02nov88	moved Window ctor, Show and GetDc here from window.cxx
*						also changes to get AppImpInst from DLL and Show flag from
*						App. Window.cxx is now defunct.
*	0.4 jk		02nov88	WM_ERASEBKGND message now handled properly
*						to allow Window::ChangeBackground().
*	0.5	jk		09nov88	The old pen/brush/font in the hDC is not being put
*						back into the DC.
*	0.6	ferg	15nov88	use background brush not window brush.
*	0.7	rs		03Nov88	additions for scroll bars to implement window scroll
*						bars.
*	0.8 jk		21nov88 Fix to WM_COMMAND processing in the dispatcher
*						to fix list box messages.
*	0.9 jk		23nov88	Fix to ChangeSize and ChangePosition to use
*						GetWindowRect rather than WndSize and WndPosition
*						when the window handle exists.
*	0.10 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
*	0.11 jk		02dec88	Fast Compile defines added.
*	0.12 ferg	06nov88	virtual EvtEnd function to be called after every Event
*						handler.
*  0.13 rs     09jan89 Only modify ID for controls if not in a resource file
*  0.14 rs     16jan89 Added Window::Enable, Disable, Hide
*  0.15 rs     02feb89 Corrections for cursors
*  0.16 rs     22feb89 Mapping mode compatibility
*  0.17 rs     24feb89 Due to mapping  considerations it was necessary to
*                      amalgamate references to a parent window for child
*                      and dialog windows into a WndParent pointer in the general
*                      Window class and change uses of ChildWindow, etc to
*                      reflect this.
*  0.18 rs     13mar89 Added Window:: Draw 
*  0.19 rs     14mar89 Fixed bug in rectangle draw etc
*                      Rectangles to be painted should always have Top < Bottom
*                      IRRESPECTIVE OF MAPPING MODE
*  1.0	 rs		29mar89 -------Release 1.0 ship date ----------------
*	1.1  rs		22jun89	In case of user override of Window::Close
*						the window doesn't close - need to call DefWindowProc
*  1.2  rs		23jun89	WindowRect and Client rect return 
*						0 .. ymax,  not 0 .. ymax -1 ::need to cater for 
*						this.
*	1.3  rs		28jun89 Corrections for window positioning and sizing
*	1.4  rs		29jun89 Added in code to remove object information from
*						property list [DISABLED]
*	1.5  rs		30jun89	Corrections to background erasing to use
*						standard class background brush if none available
*  1.6	 rs		07jul89 -------Release 1.0a ship date ---------------
*	1.7  rs		17jul89 WindowRect should return parent/client co-ordinates.\
*	1.8	 rs		23aug89 DebugInfo 
*	1.9	 rs		05oct89	Remove temporal dependencies from windows
*		 rs		15oct89	ChangeBitmap removed.
*						ASCIIKey removed.
*	1.10 rs		11nov89	RePaint takes no arguments
*						RePaintRect added.
*	1.11 rs		24Nov89	Long -> Void event handlers
*	1.12 rs		07Dec89 Code to allow updating of menu bars correctly
*	1.13 hl		20Dec89	Changes for correct point mapping
*	1.14 hl		21Dec89 Change for correct positioning of Dialog Windows.
*						Dialog boxes use screen co-ordinates, all other
*						child windows use parent client co-ordinates.
*	1.15 rs		03Jan90	Flagging of windows to support correct style updating.
*						Also WndFlags is now used to indicate whether window
*						is a ModeLessDialog or a DeleteWindow.
*	1.16 rs		08Jan90	Added WM_DESTROY to cope with menus being deleted
*						along with the menu to which they are attached.
*						Setting the menu to zero prevents this from happening
*						hence allowing menus to be shared by several windows.
*	1.17 hl		11Jan90 PaintRectangle
*	1.18 hl		12Jan90 use PeekMessage to prevent call to the KeyDown
*		 				EventHandler for WM_KEYDOWN message.
*	1.19 RS		14jAN90 Use WM_SETCURSOR to allow different cursors within the 
*					   same window class.
*	1.20 rs		01feb90 Proper maintenance of background brushes. 
*	1.21 rs		01feb90 Changed use of Handle() to CV_RunTime::Handle(this)
*						This is inline implementation of Handle.
*	1.22 hl		05feb90	Rs From Herve  29 January. 
*						Enabling/Disabling  scrollbars in Dispatch.
*
*	1.23 rs		08feb90 Support for creation of windows in constructors
*						and destruction in destructors.
*						QueryClose just returns true
*						WindowInit and Close have null operations.
*						Show is now relegated to just showing the window.
*
*	1.24 rs		??feb90 Moved AppWindow specific operations in dispatcher
*						to AppWindow::Dispatch. 
*						This includes calling of Close, painting icons etc.
*	1.25 rs		20feb90 Removed calls to ValidateWindow as they are unneeded
*						under Current model ( see 1.23) 
*						Removed some calls to IsWindow for the same reason.
*	1.26 rs		21feb90 Moved caption handling into Window.
*	1.27 rs		28feb90 Mods to support MenuEvt::GetMenu()
*
*		 rs		Conversion to C++ 2.0	
*
*	1.28 rs		08may90	C++ 2.0 A cannot handle negative integers in switch
*						statements - must right shift value before testing.
*	1.29 rs		08may90 C++ 2.0 cannot coerce return type to reference.
*						Must save in temporary value first.
*	1.30 rs		06Jun90 Anchoring support.
*	1.31 rs		15Jun90 In Windows 3.0 Scrolling must remove EndScroll messages 
*						following ThumbPosition in order to prevent two EndScroll
*						events being triggered.
*	1.32 rs		22jun90 rs from hl 07 Jun - new function Window::Scroll
*	1.33 rs		22jun90 rs from hl 07 Jun  convert the coordinates before
*				calling InvalidateRect
*	1.34 hl		18jun90 conversion to pScrollBar_Imp when calling 
*				WndScrollBarDisabled.
*	1.35 rs,nc  ??aug90 Hiding.
*	1.36 rs		24oct90 Use of bitfields for flags.
*	1.37 rs		24oct90 Addition of Wind_Imp::Initialise
*	1.38 rs		05Apr91 Wind_Imp::GetPosition corrected
*/

#include "tfrmpre.hxx"

#define	SYSMENU_Mask		0xF000
#define SYSTEM_KEYCODE		0x20000000

/* WH_MSGFILTER Filter Proc Codes */
#define MSGF_DIALOGBOX	    0
#define MSGF_MESSAGEBOX	    1
#define MSGF_MENU	    2
#define MSGF_MOVE	    3
#define MSGF_SIZE	    4
#define MSGF_SCROLLBAR	    5
#define MSGF_NEXTWINDOW	    6

Dimension  PASCAL_FUNC FrameSize(HWND hwnd);
extern "C" HINSTANCE  WINAPI CV_LibHandle (void);

Dimension  PASCAL_FUNC FrameSize(HWND hwnd)
{
	Rectangle r;
	Dimension d;
	GetWindowRect(hwnd, (RECT *)&r);
	d = Dimension( r.Right() - r.Left(), 
		r.Bottom() - r.Top());
	if (!d.Height() )
		d.Height() = GetSystemMetrics(SM_CYMIN);
	if (!d.Width() )
		d.Width() = GetSystemMetrics(SM_CXMIN);
	return d;
}

#if !defined(WIN32)
static void ScreenToParent (HWND hwnd, Point  *p)	// * 1.7 start *
{
	HWND hparent;
	
	if (hparent = (HWND)GetWindowWord (hwnd, GWW_HWNDPARENT))
		ScreenToClient (hparent, (POINT *)p);
} 																	// * 1.7 end *
#else
inline void ScreenToParent (HWND hparent, Point  *p)	// * 1.7 start *
{
	if (hparent)
		ScreenToClient (hparent, (POINT *)p);
} 																	// * 1.7 end *
#endif
// * 1.3 * end
Wind_Imp::  Wind_Imp	(pWindow req) : EC_Imp(req)
{
	hDC = 0;
	hTargetDC 	= 0;		// #HK940119
	hEContext 	= 0;
	fAttached 	= false;
	
	WndMenu		= 0;
	WndFont		= 0;
	WndBrush	= 0;
	WndPen		= 0;
	WndBitmap	= 0;
	WndAccel	= 0;
	WndPointer	= 0;
	WndCapt 	= 0;	// * 1.26 *
	WndCursor   	= 0;
	
	
	WndSize		= Dimension ( CW_USEDEFAULT, CW_USEDEFAULT );
	WndPosition	= Point ( CW_USEDEFAULT, CW_USEDEFAULT );
	WndParent 	= 0;                                     // * 0.17 *
	WndStyle 	= 0;
	WndBackground 	= 0;							
	WndFlags 	= 0;									// * 1.15 *
	
	// Initialise Windows DC flags
	DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
		DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
		DCFlags.BrushNeeded = DCFlags.Erasing = 0;
	PaintInfo = 0;
	
	WindMgt.Opened = WindMgt.Initialised = WindMgt.NoRedraw = WindMgt.Anchoring = 
		WindMgt.Destructor = WindMgt.HelpCursorOn = WindMgt.HelpMenu =
		WindMgt.HelpOn = WindMgt.isMDIWindow = WindMgt.isModal = 
		WindMgt.isPropPage = false;
	
	// Initialise flags to indicate that Window doesn't manage control painting
	ColorMgt.TextClr =	 ColorMgt.TrapCtlColor = 0;
	
	CurrentHelp = 0;
	LastKeyCode = uint(-1);
	
	AppWndHorz = 0;
	AppWndVert = 0;
}	// End of "Wind_Imp" CONSTRUCTOR

// Konstruktor, der von einem  HWND ausgeht und ein CommonVu Window erzeugt ---
Wind_Imp::  Wind_Imp	(pWindow req, HWND hWnd) : EC_Imp(req)
{
	hDC 		= 0;
	hTargetDC 	= 0;		// #HK940119
	hEContext 	= hWnd;
	fAttached 	= true;
	
	WndMenu		= 0;
	WndFont		= 0;
	WndBrush	= 0;
	WndPen		= 0;
	WndBitmap	= 0;
	WndAccel	= 0;
	WndPointer	= 0;
	WndCapt 	= 0;	// * 1.26 *
	WndCursor   	= 0;
	
	Rectangle rcPos;
	
	GetClientRect (hWnd, (RECT *)&rcPos);
	
	WndParent 	= 0;                                     // * 0.17 *
	WndSize		= Dimension (rcPos.Right()-rcPos.Left(), rcPos.Bottom()-rcPos.Top());
	WndPosition	= Point (rcPos.Right(), rcPos.Bottom());
   	WndStyle 	= GetWindowLong (hWnd, GWL_STYLE);
	WndBackground 	= 0;							
	WndFlags 	= 0;									// * 1.15 *
	
	DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
		DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
		DCFlags.BrushNeeded = DCFlags.Erasing = 0;
	PaintInfo = 0;
	
	WindMgt.Opened = WindMgt.Initialised = WindMgt.NoRedraw = WindMgt.Anchoring = 
		WindMgt.Destructor = WindMgt.HelpCursorOn = WindMgt.HelpMenu =
		WindMgt.HelpOn = WindMgt.isMDIWindow = WindMgt.isModal = 
		WindMgt.isPropPage = false;
	
	// Initialise flags to indicate that Window doesn't manage control painting
	ColorMgt.TextClr =	 ColorMgt.TrapCtlColor = 0;
	
	CurrentHelp = 0;
	LastKeyCode = uint(-1);
	
	AppWndHorz = 0;
	AppWndVert = 0;
}	// End of "Wind_Imp" CONSTRUCTOR


Wind_Imp::~Wind_Imp (void)
{
	if (fAttached) Detach ();	// HWND abkoppeln
	if (AppWndVert) {
		delete (WndVertScrollBar *)AppWndVert;
		AppWndVert = NULL;
	}
	if (AppWndHorz) {
		delete (WndHorzScrollBar *)AppWndHorz;
		AppWndHorz = NULL;
	}
	if (WndCapt) {
		delete WndCapt;
		WndCapt = NULL;
	}
}


HWND Wind_Imp::Attach (HWND hWnd)		// FensterHandle zuweisen
{
	HWND hWndOld = hEContext;
	
	_ASSERTE(NULL == hWndOld);		// muß das erste mal sein
	
	fAttached = true;
	hEContext = hWnd;
	
	pApp_Imp pAppImpInst = _AppImpFind();
	
	pAppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
	
	return hWndOld;
}

HWND Wind_Imp::Detach (void)
{
	HWND hWnd = hEContext;
	
	hEContext = 0;
	fAttached = false;
	
	return hWnd;
}

void 	Wind_Imp:: ManageControlBackground( BOOL incrementing )
{
	// Essentially the TrapCtlColor var keeps a count of the controls
	// for which the window manages the background.
	// If this hits zero the Window does not manage the background of its child controls
	
	if (incrementing) ColorMgt.TrapCtlColor++;
	else if (ColorMgt.TrapCtlColor) ColorMgt.TrapCtlColor--;
}

void 	Wind_Imp:: ManageControlText( BOOL incrementing )
{
	// Essentially the TextClr var keeps a count of the controls
	// for which the window manages the text color.
	// If this hits zero the Window does not manage the background of its child controls
	
	if (incrementing) ColorMgt.TextClr++;
	else if (ColorMgt.TextClr) ColorMgt.TextClr--;
}

_TF_ENTRY32 void _DLLENTRY CentreWindow (HWND hWndP, HWND hWnd)
{
	if (NULL == hWndP || !IsWindow(hWndP))
		hWndP = GetDesktopWindow();	// kein parent -> Desktop
	
RECT rcP, rc;
	
// Höhe und Breite des Parentfensters
	GetWindowRect (hWndP, &rcP);
	
int iwParent = rcP.right - rcP.left;
int ihParent = rcP.bottom - rcP.top;
	
// Höhe und Breite des Childfensters
	GetWindowRect (hWnd, &rc);
	
int iwChild = rc.right - rc.left;
int ihChild = rc.bottom - rc.top;
	
// Bildgrenzen ermitteln
int iwScreen = GetSystemMetrics (IsWin40() ? SM_CXMAXIMIZED : SM_CXSCREEN);
int ihScreen = GetSystemMetrics (IsWin40() ? SM_CYMAXIMIZED : SM_CYSCREEN);
	
// evtl. zusätzlichen Offset beachten
int iOffsetX = reinterpret_cast<int>(GetProp (hWndP, "OffsetPositionX"));
int iOffsetY = reinterpret_cast<int>(GetProp (hWndP, "OffsetPositionY"));

// neue X-Position berechnen, Bildgrenzen beachten
int iLeft = rcP.left + ((iwParent - iwChild)/2) + iOffsetX;
	
	if (iLeft < 0) 
		iLeft = 0;
	else if ((iLeft + iwChild) > iwScreen)
		iLeft = iwScreen - iwChild;
	
// neue Y-Position berechnen, Bildgrenzen beachten
int iTop = rcP.top + ((ihParent - ihChild)/2) + iOffsetY;
	
	if (iTop < 0)
		iTop = 0;
	else if ((iTop + ihChild) > ihScreen)
		iTop = ihScreen - ihChild;

// neue Position einstellen
	SetWindowPos (hWnd, NULL, iLeft, iTop, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
}

_TF_ENTRY32 void _DLLENTRY CentreWindow (pWindow pWndP, pWindow pWnd)
{
	if (NULL != pWnd)
		CentreWindow (pWndP ? pWndP -> Handle() : NULL, pWnd -> Handle());
}

void	Wind_Imp::  Show (ShowState s)		// * 1.23 start *
{
	s = (ShowState)(s & SHOWSTATE_STATE);		// Flags ausblenden
	if (hEContext) {
		if (WndCapt)							// * 1.26 *
			SetWindowText (hEContext, WndCapt);
		
		if ((WndStyle & WS_MAXIMIZE) || (s == Zoomed))
			ShowWindow (hEContext, SW_SHOWMAXIMIZED);
		else if ((WndStyle & WS_MINIMIZE) || (s == Iconized))
			ShowWindow (hEContext, SW_SHOWMINNOACTIVE);
		else if (s == Centre) {
			CentreWindow (::GetParent(hEContext), hEContext);
			ShowWindow (hEContext, SW_SHOWNORMAL);
		} else
			ShowWindow (hEContext, SW_SHOWNORMAL);
	}													// * 1.23 end *
}	// End of "Wind_Imp" FUNCTION "Show"

// * 0.13 start *

void     Wind_Imp::  Enable (BOOL tf)
{
    if (hEContext  )	// * 1.9 , 1.25 * 
        EnableWindow(hEContext, tf);
}

void    Wind_Imp::  Hide()
{
    if (hEContext )	// * 1.9, 1.25 * 
		ShowWindow ( hEContext, SW_HIDE );
}

// * 0.13 end *
HDC	Wind_Imp::GetDC	(void)
{
	if	( !hEContext)
	{
		DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
			DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
			DCFlags.BrushNeeded = 0;
		PaintInfo = 0;
		return (hDC = 0);
	}
	
	if ( !hDC )		// * 1.25 *
	{
		hDC = ::GetDC(hEContext);
		CV_ASSERT_VALID(hDC);
		DCFlags.Initialised = DCFlags.FontInUse =
			DCFlags.PenInUse = DCFlags.BrushInUse = 0;
	}
	
	if (hDC) {
		
		if ( !DCFlags.Initialised)
		{
			SetMapMode(hDC, MM_TEXT); 
			SetMapMode( hDC, MM_ANISOTROPIC);
			
#if !defined(WIN32)
			SetViewportExt(hDC, WndSize.Width(), WndSize.Height()); 
			SetWindowExt(hDC, WndSize.Width(), -WndSize.Height()); 
			SetViewportOrg(hDC, 0, WndSize.Height() -1);			
#else
			SetViewportExtEx (hDC, WndSize.Width(), WndSize.Height(), NULL); 
			SetWindowExtEx (hDC, WndSize.Width(), -WndSize.Height(), NULL); 
			SetViewportOrgEx (hDC, 0, WndSize.Height() -1, NULL);
#endif
			DCFlags.Initialised = 1;
			LogBackBrush lbb(this);
			SetBkColor(hDC, lbb.GetColor());
			if (lbb.GetType() == BS_HOLLOW)
				SetBkMode(hDC, TRANSPARENT);
			else
				SetBkMode(hDC, OPAQUE);
		}                                                   // * 0.17 * end
		
		if (DCFlags.FontNeeded && !DCFlags.FontInUse)
		{
			HFONT	font = 0;
			
			if (WndFont)
			{
				CV_RunTime::Font_Imp(WndFont) -> Init(0, hDC);
				font = CV_RunTime::Font_hFont ( WndFont );
			}
			else
				font = (HFONT)GetStockObject(13);
			CV_ASSERT_VALID(font);
			SelectObject ( hDC, font );					// * 0.5 *
			DCFlags.FontInUse = 1;
			DCFlags.FontNeeded = 0;
			SetTextAlign(hDC, TA_LEFT | TA_BOTTOM );
		}
		if ( DCFlags.PenNeeded && !DCFlags.PenInUse)
		{
			if	( WndPen )
			{
				SelectObject ( hDC, 
					CV_RunTime::Pen_hPen ( WndPen )); // * 0.5 *
				LogicalPen p(WndPen);
				SetTextColor(hDC, p.GetColor());
			}
			else
			{
				SelectObject ( hDC, GetStockObject ( 7 ));	  // * 0.5 *
				SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
			}
			// Stock Object 7 is default pen
			DCFlags.PenInUse = 1;
			DCFlags.PenNeeded = 0;
		}
		
		if ( DCFlags.BrushNeeded && !DCFlags.BrushInUse)
		{
			if	( WndBrush )
				SelectObject ( hDC,  CV_RunTime::Brush_hBrush ( WndBrush ));	// * 0.5 *
			else
				SelectObject ( hDC,  GetStockObject ( 4 ));// * 0.5 *
			// Stock Object 4 is default brush
			DCFlags.BrushInUse = 1;
			DCFlags.BrushNeeded = 0;
		}
	}
	return hDC;
}	
// * 0.3 End *

// #HK980424 ------------------------------------------------------------------
HDC Wind_Imp::SetDC (HANDLE hH)
{
HDC hOldTarget = CV_RunTime::Window_hDC (this);
	
	CV_RunTime::Window_hDC(this) = (HDC)hH;

	DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =	DCFlags.Initialised = 0;
	DCFlags.FontNeeded = DCFlags.PenNeeded = DCFlags.BrushNeeded = 1;
	GetDC();			// neu initialisieren

	return hOldTarget;
}

HDC Wind_Imp::SetTargetDC (HANDLE hDC)
{
HDC hOldTarget = CV_RunTime::Window_hTargetDC (this);
	
	CV_RunTime::Window_hTargetDC (this) = (HDC)hDC;
	return hOldTarget;
}
// #HK980424 ------------------------------------------------------------------

// #HK940119 ------------------------------------------------------------------
HDC Wind_Imp::GetTargetDC	(void)
{
	if (CV_RunTime::Window_hTargetDC (this))
		return CV_RunTime::Window_hTargetDC (this);
	
	return CV_RunTime::Window_GetDC (this);		// FensterDC besorgen
}

HDC Wind_Imp::SetDrawTarget (HDC hNewTarget)
{
HDC hOldTarget = CV_RunTime::Window_hTargetDC (this);
	
	CV_RunTime::Window_hTargetDC (this) = hNewTarget;
	return hOldTarget;
}

HDC Wind_Imp::GetDrawTarget (void)
{
	return CV_RunTime::Window_hTargetDC (this);
}


long	Wind_Imp::  Dispatch	( Event e )
{
	long retval = 0;
	uint ControlType = 0;
	
	switch	( CV_RunTime::Event_wMsg (e)) {
#if !defined(WIN32)
	case WM_CTLCOLOR:
		{
			HWND hControl = (HWND)LoWord(CV_RunTime::Event_lParam(e));
			UINT ControlType = HiWord(CV_RunTime::Event_lParam ( e ));
			HBRUSH hBrush;
			
			//		if (ColorMgt.TrapCtlColor || ColorMgt.TextClr)
			if (true) {
				switch(ControlType) {
				case CTLCOLOR_STATIC:		
					{
						Control_Imp *pCI = (Control_Imp*)(_AppImpFind() -> ControlList() -> Find((HANDLE)hControl));
						
						// Check if its an icon
						// May need rewrite to account for User Defined Controls.
						// This code relies on thye fact that the RegClassName will be zero for 
						// CA-CommonView FixedIcon control.
						
						if ((pCI) && (((pCI->GetRegClassName() == 0L) && 
							((GetWindowLong (hControl, GWL_STYLE) & SS_ICON) == SS_ICON)) ||
							((pCI->GetStyle() & SS_ICON) == SS_ICON)))
						{
							if ( pCI && pCI -> bManageBackground())
							{
								hBrush = pCI -> SetColors ((HDC)CV_RunTime::Event_wParam(e), ControlType);
								CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
								return (LRESULT)(HANDLE)hBrush;
							}
							else
								((pDW)pRequestor) -> _Default(e);
							break;
						}
						
						// If its not an icon 
						// fall through to case to handle text.
					}
					
				case CTLCOLOR_EDIT:		
				case CTLCOLOR_LISTBOX:	
				case CTLCOLOR_BTN:		
					{
						TextControl_Imp *pTCI = (TextControl_Imp*)(_AppImpFind() -> ControlList() -> Find((HANDLE)hControl));
						
						if (pTCI && (pTCI -> bManageColor() || pTCI -> bManageBackground()) )
						{
							hBrush = pTCI -> SetColors((HDC)CV_RunTime::Event_wParam(e), ControlType);
							CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
							return (LRESULT)(HANDLE)hBrush;
						}
						else
							((pDW)pRequestor) -> _Default(e);
					}
					break;
					
				case CTLCOLOR_SCROLLBAR:
					{
						Control_Imp *pCI = (Control_Imp*)(_AppImpFind() -> ControlList() -> Find ((HANDLE)hControl));
						
						if (pCI && pCI -> bManageBackground() )
						{
							hBrush = pCI -> SetColors((HDC)CV_RunTime::Event_wParam(e),ControlType);
							CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
							return (LRESULT)(HANDLE)hBrush;
						}
						else
							((pDW)pRequestor) -> _Default( e);
					}
					break;
					
				case CTLCOLOR_MSGBOX:
				case CTLCOLOR_DLG:		
				default:
					((pDW)pRequestor) -> _Default( e);
					break;
				}
			}
			else 
				((pDW)pRequestor) -> _Default( e);
		}
		break;
		
#else // WIN32
	case WM_CTLCOLORSTATIC:
		{
			HWND hControl = (HWND)CV_RunTime::Event_lParam(e);
			Control_Imp *pCI = (Control_Imp*)(_AppImpFind() -> ControlList() -> Find((HANDLE)hControl));
			
			// Check if its an icon
			// May need rewrite to account for User Defined Controls.
			// This code relies on thye fact that the RegClassName will be zero for 
			// CA-CommonView FixedIcon control.
			
			if ((pCI) && (((pCI->GetRegClassName() == 0L) && 
				((GetWindowLong (hControl, GWL_STYLE) & SS_ICON) == SS_ICON)) ||
				((pCI->GetStyle() & SS_ICON) == SS_ICON)))
			{
				if ( pCI && pCI -> bManageBackground())
				{
					HBRUSH hBrush = pCI -> SetColors ((HDC)CV_RunTime::Event_wParam(e), CTLCOLOR_STATIC);
					
					CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
					return (LRESULT)(HANDLE)hBrush;
				}
				else
					((pDW)pRequestor) -> _Default(e);
				break;
			}
			
			// If its not an icon 
			// fall through to case to handle text.
		}
		
	case WM_CTLCOLOREDIT:
		ControlType = CTLCOLOR_EDIT;
		//durchfallen
		
	case WM_CTLCOLORLISTBOX:
		ControlType = CTLCOLOR_LISTBOX;
		// durchfallen
		
	case WM_CTLCOLORBTN:
		ControlType = CTLCOLOR_BTN;
		
		{
			Control_Imp *pCI = (Control_Imp*)(_AppImpFind() -> ControlList() -> Find((HANDLE)CV_RunTime::Event_lParam(e)));
            if (NULL != pCI) {
            uint classname = (uint)pCI->GetRegClassName();

                switch(classname) {
                case CTRL_Static:
                case CTRL_Button:
                case CTRL_ListBox:
                case CTRL_Edit:
                case CTRL_ComboBox:
                case CTRL_Gauge:
                    {
			        TextControl_Imp *pTCI = (TextControl_Imp *)pCI;
			
			            if (pTCI && (pTCI -> bManageColor() || pTCI -> bManageBackground()) ) {
				            HBRUSH hBrush = pTCI -> SetColors((HDC)CV_RunTime::Event_wParam(e), ControlType);
				            
				            CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
				            return (LRESULT)(HANDLE)hBrush;
			            }
			            else
				            ((pDW)pRequestor) -> _Default(e);
                    }
                    break;

                default:
				    ((pDW)pRequestor) -> _Default(e);
                    break;
                }
            }
            else
				((pDW)pRequestor) -> _Default(e);
		}
		break;
		
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORDLG:
		((pDW)pRequestor) -> _Default( e);
		break;
		
	case WM_CTLCOLORSCROLLBAR:
		{
			Control_Imp *pCI = (Control_Imp*)(_AppImpFind() -> ControlList() -> Find ((HANDLE)CV_RunTime::Event_lParam(e)));
			
			if (pCI && pCI -> bManageBackground() )
			{
				HBRUSH hBrush = pCI -> SetColors((HDC)CV_RunTime::Event_wParam(e), CTLCOLOR_SCROLLBAR);
				
				CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
				return (LRESULT)(HANDLE)hBrush;
			}
			else
				((pDW)pRequestor) -> _Default( e);
		}
		break;
#endif // WIN32
		
		// Mouse message handling 
		
	case WM_SETCURSOR:				// * 1.19 start *
		HandlePointer(e);
		break;					// * 1.19 end *
		
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		Report(this, CVEVT_MouseButtonDn, e );
		((pDW)pRequestor) -> _MouseButtonDn ((MouseEvt&)e );
		break;
		
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		Report(this, CVEVT_MouseButtonUp, e );
		((pDW)pRequestor) -> _MouseButtonUp ((MouseEvt&)e );
		break;
		
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
		Report(this, CVEVT_MouseButtonDblClk, e );
		((pDW)pRequestor) -> _MouseButtonDblClk ((MouseEvt&)e );
		break;
		
	case WM_MOUSEMOVE:
		if ( CV_RunTime::Event_wParam ( e )) {
			Report(this, CVEVT_MouseDrag, e );
			((pDW)pRequestor) -> _MouseDrag ((MouseEvt&)e );
		}
		else {
			Report(this, CVEVT_MouseMove, e );
			((pDW)pRequestor) -> _MouseMove ((MouseEvt&)e );
		}
		break;
		
		// Help Messages
	case WM_ENTERIDLE:
		if ( WindMgt.HelpOn  && (CV_RunTime::Event_wParam(e) == MSGF_MENU) && 
			(GetKeyState(KeyF1) & 0x8000))	
		{
			WindMgt.HelpMenu = true;
			PostMessage(hEContext, WM_KEYDOWN, KeyEnter, 0L);
		}
		break;
		
	case WM_CVHELP:
		Report(this, CVEVT_Help, e);
		EnableHelpCursor(false);
		((pDW)pRequestor) -> _HelpRequest ( (HelpRequestEvt&)e );
		break;
		
	case WM_DESTROY:				// * 1.16 start *
		if (!(GetWindowLong (hEContext, GWL_STYLE) & WS_CHILD))
			SetMenu (hEContext, 0);		// will fail on childs
		//		SetMenu(hEContext, 0);
		ReleaseCapture();
		WndFlags &= (WF_IS_CHILD | WF_IS_DELETE);
		((pDW)pRequestor) -> _Default (e);
		break;					// * 1.16 end *
		
		
	case WM_SHOWWINDOW:	// * 1.15 start *
	case WM_SETVISIBLE:	// * 1.15 start *
		if ( CV_RunTime::Event_wParam ( e )) {
			WndFlags |= WF_IS_SHOWN;
			WndFlags &= (~WF_MENU_CHANGED);
		}
		else
			WndFlags &= (~(WF_IS_SHOWN | WF_MENU_CHANGED));
		((pDW)pRequestor) -> _Default ( e );
		break;		// * 1.15 end *
		
	case WM_SYSCOLORCHANGE:
		{
			pApp_Imp AppImpInst = _AppImpFind();	
			
			AppImpInst -> InitColors();
			//			InvalidateRect ( hEContext, NULL, true ); 
			((pDW)pRequestor) -> _Default ( e );
		}
		break;
		
	case WM_SIZE:
		Report(this, CVEVT_ReSize, e);
		((pDW)pRequestor) -> _ReSize ((ReSizeEvt&)e );
		break;
		
	case WM_MOVE:
		Report(this, CVEVT_Move, e );
		((pDW)pRequestor) -> _Move ((MoveEvt&)e );
		break;
		
	case WM_ACTIVATE:
		{
			pApp_Imp AppImpInst = _AppImpFind();
			
			if (LOWORD(CV_RunTime::Event_wParam(e))) {
				if (WindMgt.HelpOn) {
					if (WindMgt.HelpCursorOn)
						AppImpInst -> SetHelpWind(hEContext, HM_MOUSE);
					else
						AppImpInst -> SetHelpWind(hEContext, HM_GENERAL);
				}
				AssociateAccel(true);
#if defined(WIN32)
				//				CV_RunTime::Event_wMsg(e) = WM_QUERYNEWPALETTE;
				//				((pDW)pRequestor) -> _PaletteChange ((PaletteChangeEvt &)e);	// Palette behandeln
				//				CV_RunTime::Event_wMsg(e) = WM_ACTIVATE;
#endif
				Report(this, CVEVT_Activate, e);
				((pDW)pRequestor) -> _Activate (e);
			}
			else {
				if (WindMgt.HelpOn)
					AppImpInst -> SetHelpWind(0,HM_NONE);
				AssociateAccel (false);
				Report(this, CVEVT_DeActivate, e);
				((pDW)pRequestor) -> _DeActivate (e);
			}
		}
		break;
		
	case WM_SETFOCUS:
	case WM_KILLFOCUS:
		if (WndCursor)
			WndCursor->Update (WM_SETFOCUS == CV_RunTime::Event_wMsg (e));
		Report(this, CVEVT_FocusChange, e );
		((pDW)pRequestor) -> _FocusChange ((FocusChangeEvt&)e );
		break;
		
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Report(this, CVEVT_KeyUp, e);
		((pDW)pRequestor) -> _KeyUp ((KeyEvt&)e );
		break;
		
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
			MSG msg;
			
			if(!PeekMessage (&msg, hEContext, WM_CHAR, WM_CHAR, PM_NOREMOVE))
			{
				Report (this, CVEVT_KeyDown, e);
				((pDW)pRequestor) -> _KeyDown ((KeyEvt&)e);	// * 1.18 *
			}
			else
				LastKeyCode = CV_RunTime::Event_wParam(e);
		}
		break;
		
	case WM_CHAR:
		// Check if the removal of the following line causes side effects.
		// 			if ( !(CV_RunTime::Event_lParam(e) & SYSTEM_KEYCODE ))
		{
			Report(this, CVEVT_KeyDown, e );
			((pDW)pRequestor) -> _KeyDown ((KeyEvt&)e );
		}
		//			else
		//				((pDW)pRequestor) -> _Default ( e );
		LastKeyCode = uint(-1);
		break;
		
	case WM_PAINT:
		if ( !IsIconic( hEContext ) )
		{
			PAINTSTRUCT	ps;
			
			EvtEnd();
			PaintInfo = (void*) &ps;
			hDC	= BeginPaint ( hEContext, &ps );
			GetDC();
			
			Report(this, CVEVT_Expose, e );
			((pDW)pRequestor) -> _Expose ((ExposeEvt&)e );
			EndPaint ( hEContext, &ps );
			hDC	= 0;
			DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
				DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
				DCFlags.BrushNeeded = 0;
			PaintInfo = 0;
		}
		break;
		// * 0.4 Begin *
	case WM_ERASEBKGND:
		{
			if (WndBackground)
				PaintBackground((HDC)CV_RunTime::Event_wParam ( e ));
			else
				((pDW)pRequestor) -> _Default ( e );
		}	
		break;
		// * 0.4 End *
		
	case WM_QUERYENDSESSION:
		CV_RunTime::EC_SetRetval (this, retval = (long)CloseHandler(ChQuery, e));
		break;
		
	case WM_CLOSE:
		if (CloseHandler(ChQuery,e)) 
			CV_RunTime::EC_SetRetval (this, retval = CloseHandler(ChCloseAndTidy,e));
		break;
		
	case WM_ENDSESSION:
		if (CV_RunTime::Event_wParam (e))
			CV_RunTime::EC_SetRetval (this, retval = CloseHandler(ChClose, e));
		else
			((pDW)pRequestor) -> _Default(e);
		break;
		
	case WM_INITMENU:
	case WM_INITMENUPOPUP:
		Report(this, CVEVT_MenuInit, e);
		((pDW)pRequestor) -> _MenuInit ((MenuInitEvt&)e );
		break;
		
	case WM_MENUSELECT:
#if defined(WIN32)
		if (NULL == CV_RunTime::Event_lParam(e)) 	// hMenu
#else
			if (NULL == HIWORD(CV_RunTime::Event_lParam(e)))	
#endif // WIN32
				((pDW)pRequestor) -> _Default(e);
			else {
				Report (this, CVEVT_MenuSelect, e);
				((pDW)pRequestor) -> _MenuSelect ((MenuSelectEvt&)e);
			}
			break;
			
	case WM_HSCROLL:
	case WM_VSCROLL:
		{
			ScrollEvt& k = (ScrollEvt &) e;
			ScrollBar *pSB = k.GetScrollBar();
			ScrollB_Imp *sbi = (ScrollB_Imp*)0;
			
			if (pSB)
				sbi = (ScrollB_Imp *) CV_RunTime::pControl_to_pImp(pSB);
			
			if (sbi && CV_RunTime::ScrollBar_GetIgnore (sbi)
				&& (LOWORD(CV_RunTime::Event_wParam(e)) == SB_ENDSCROLL))
			{
				CV_RunTime::ScrollBar_SetIgnore (sbi, 0);
				((pDW)pRequestor) -> _Default(e);
				break;
			}
			
			if (!IsWin31() && sbi &&
#if !defined(WIN32)
				(! HIWORD(CV_RunTime::Event_lParam(k)) ) )
#else
				(! (HWND)CV_RunTime::Event_lParam(k) ) ) 
#endif
			{
				// Window ScrollBar
				if( CV_RunTime::WndScrollBarDisabled(sbi)) 
					break;
			}
			
			if ( CV_RunTime ::Event_wMsg (e) == WM_HSCROLL)
			{
				Report(this, CVEVT_HorizScroll, e);
				((pDW)pRequestor) -> _HorizScroll (k);
			}
			else {
				Report(this, CVEVT_VertScroll, e);
				((pDW)pRequestor) -> _VertScroll (k);
			}
			
			// Required for Windows 3.x onwards
			if (sbi && LOWORD(CV_RunTime ::Event_wParam(e)) == SB_THUMBPOSITION)
				CV_RunTime::ScrollBar_SetIgnore (sbi, 1);
		}
		break;
		// * 0.7 End *
	case WM_COMMAND:
		{
		/* 0.8 Fixes - The conditionals have been changed and the order
		has been changed to handle controls first, then menu items and
		finally Accelerator messages. Theoretically, we could then
		include a test within the menu handling bit to see if we have
		a button click event via keyboard input, which looks the same
		as a menu item event.
		
		  EVENT		wParam		Hi ( lParam )		Lo ( lParam )
		  Control		Control ID	Notification Code	Window Handle
		  Button with	Control ID		0					0
		  keyboard I/O
		  Menu		MenuItem		0					0
		  Accel		Accel ID		1					0
			*/
#if !defined(WIN32)
			if ( (int) CV_RunTime::Event_lParam ( e ) )		// Control	* 0.8 *
			{
				char buff[20];
				
				GetClassName(((HWND *)(&CV_RunTime::Event_lParam (e)))[0], buff, 20 );
				
				int StrVal =_GetStringValue (buff);
				
				if (!StrVal) {
					pApp_Imp AppImpInst = _AppImpFind();	
					StrVal = AppImpInst -> RegClassList() -> FindItemDeep(buff);
				}
				switch (StrVal) {
				case CTRL_Button:
					switch ( ((int*)( &CV_RunTime::Event_lParam (e))) [1])
					{
					case BN_CLICKED:
						Report(this, CVEVT_ButtonClick, e);
						((pDW)pRequestor) -> _ButtonClick ((ControlEvt&)e );
						break;
					case BN_DOUBLECLICKED:
						Report(this, CVEVT_ButtonDblClk, e );
						((pDW)pRequestor) -> _ButtonDblClk ((ControlEvt&)e );
						break;
					default:
						((pDW)pRequestor) -> _Default ( e );
						break;
					}
					break;
					
					case CTRL_ListBox:
						switch ( ((int*)( &CV_RunTime::Event_lParam ( e )))[ 1 ])
						{
						case LBN_DBLCLK:
							Report(this, CVEVT_ListBoxClk, e );
							((pDW)pRequestor) -> _ListBoxClk ((ControlEvt&)e );
							break;
						case LBN_SELCHANGE:
							Report(this, CVEVT_ListBoxSel, e );
							((pDW)pRequestor) -> _ListBoxSel ((ControlEvt&)e );
							break;
						default:
							((pDW)pRequestor) -> _Default ( e );
							break;
						}
						break;
						
						case CTRL_Edit:
							switch ( (int)(((int*)( &CV_RunTime::Event_lParam ( e )))[ 1 ]) )
							{
							case EN_CHANGE:
								//				case EN_UPDATE:
								Report(this, CVEVT_EditChange, e );
								((pDW)pRequestor) -> _EditChange ((ControlEvt&)e );
								break;
							case EN_HSCROLL:
							case EN_VSCROLL:
								Report(this, CVEVT_EditScroll, e );
								((pDW)pRequestor) -> _EditScroll ((ControlEvt&)e );
								break;
							case EN_KILLFOCUS:
							case EN_SETFOCUS:
								Report(this, CVEVT_EditFocusChg, e );
								((pDW)pRequestor) -> _EditFocusChg ((EditFocusChgEvt&)e );
								break;
							default:
								((pDW)pRequestor) -> _Default ( e );
								break;
							}
							break;
							
							case CTRL_ComboBox:
								switch ( ((int*)( &CV_RunTime::Event_lParam ( e )))[ 1 ])
								{
								case CBN_DBLCLK:
									Report(this, CVEVT_ListBoxClk, e );
									((pDW)pRequestor) -> _ListBoxClk ((ControlEvt&)e );
									break;
									
								case CBN_SELCHANGE:
									Report(this, CVEVT_ListBoxSel, e );
									((pDW)pRequestor) -> _ListBoxSel ((ControlEvt&)e );
									break;
									
									// #HK940214 ------------------------------------------
								case CBN_EDITCHANGE:
									Report(this, CVEVT_EditChange, e );
									((pDW)pRequestor) -> _EditChange ((ControlEvt&)e );
									break;
									
								case CBN_KILLFOCUS:
								case CBN_SETFOCUS:
									Report(this, CVEVT_EditFocusChg, e );
									((pDW)pRequestor) -> _EditFocusChg ((EditFocusChgEvt&)e );
									break;
									// ----------------------------------------------------
								default:
									((pDW)pRequestor) -> _Default ( e );
									break;
								}
								break;
								
								default:
									((pDW)pRequestor) -> _Default ( e );
									break;
				}	// End of SWITCH
                } 
				else if	( (! CV_RunTime::Event_lParam ( e ))	// Menu * 0.8 *
					|| ( CV_RunTime::Event_lParam ( e ) == 0x00010000L )) // Accel * 0.8 *
				{
					if (!WindMgt.HelpOn || !HelpFilter(e))
					{
						Report(this, CVEVT_MenuCommand, e );
						((pDW)pRequestor) -> _MenuCommand ((MenuCommandEvt&)e );
					}
				}
				else										// * 0.8 *
					((pDW)pRequestor) -> _Default ( e );							// * 0.8 *
#else // WIN32
				WORD wl = LOWORD(CV_RunTime::Event_wParam (e));
				WORD wh = HIWORD(CV_RunTime::Event_wParam (e));
				HWND hWndl = (HWND)CV_RunTime::Event_lParam (e);
				
				if (hWndl) {		// Control	* 0.8 *
					static char buff[64];
					
					GetClassName (hWndl, buff, 64);
					
					int StrVal =_GetStringValue (buff);
					
					if (!StrVal) {
						pApp_Imp AppImpInst = _AppImpFind();	
						
						StrVal = AppImpInst -> RegClassList() -> FindItemDeep(buff);
					}
					switch (StrVal) {
					case CTRL_Button:
						switch (wh) {
						case BN_CLICKED:
							Report(this, CVEVT_ButtonClick, e);
							((pDW)pRequestor) -> _ButtonClick ((ControlEvt &)e);
							break;
							
						case BN_DOUBLECLICKED:
							Report(this, CVEVT_ButtonDblClk, e);
							((pDW)pRequestor) -> _ButtonDblClk ((ControlEvt &)e);
							break;
							
						default:
							((pDW)pRequestor) -> _Default (e);
							break;
						}
						break;
						
					case CTRL_ListBox:
						switch (wh) {
						case LBN_DBLCLK:
							Report(this, CVEVT_ListBoxClk, e);
							((pDW)pRequestor) -> _ListBoxClk ((ControlEvt&)e);
							break;
							
						case LBN_SELCHANGE:
							Report(this, CVEVT_ListBoxSel, e);
							((pDW)pRequestor) -> _ListBoxSel ((ControlEvt&)e);
							break;
							
						default:
							((pDW)pRequestor) -> _Default (e);
							break;
						}
						break;
							
					case CTRL_Edit:
						switch (wh) {
						case EN_CHANGE:
							//				case EN_UPDATE:
							Report(this, CVEVT_EditChange, e);
							((pDW)pRequestor) -> _EditChange ((ControlEvt&)e);
							break;
							
						case EN_HSCROLL:
						case EN_VSCROLL:
							Report(this, CVEVT_EditScroll, e);
							((pDW)pRequestor) -> _EditScroll ((ControlEvt&)e);
							break;
							
						case EN_KILLFOCUS:
						case EN_SETFOCUS:
							Report(this, CVEVT_EditFocusChg, e);
							((pDW)pRequestor) -> _EditFocusChg ((EditFocusChgEvt&)e);
							break;
							
						default:
							((pDW)pRequestor) -> _Default (e);
							break;
						}
						break;
								
					case CTRL_ComboBoxEx:	// #HK030317
					case CTRL_ComboBox:
						switch (wh) {
						case CBN_DBLCLK:
							Report(this, CVEVT_ListBoxClk, e);
							((pDW)pRequestor) -> _ListBoxClk ((ControlEvt&)e);
							break;
							
						case CBN_SELCHANGE:
							Report(this, CVEVT_ListBoxSel, e);
							((pDW)pRequestor) -> _ListBoxSel ((ControlEvt&)e);
							break;
							
							// #HK940214 ------------------------------------------
						case CBN_EDITCHANGE:
							Report(this, CVEVT_EditChange, e);
							((pDW)pRequestor) -> _EditChange ((ControlEvt&)e);
							break;
							
						case CBN_KILLFOCUS:
						case CBN_SETFOCUS:
							Report(this, CVEVT_EditFocusChg, e);
							((pDW)pRequestor) -> _EditFocusChg ((EditFocusChgEvt&)e);
							break;
							// ----------------------------------------------------
						default:
							((pDW)pRequestor) -> _Default (e);
							break;
						}
						break;
									
					case CTRL_ToolBarCtrl:		// wie MenuCommand behandeln
						Report(this, CVEVT_MenuCommand, e);
						((pDW)pRequestor) -> _MenuCommand ((MenuCommandEvt&)e);
						break;
						
					default:
						((pDW)pRequestor) -> _Default (e);
						break;
					}	// End of SWITCH
                } 
				else if	((!hWndl && !wh) || (wh == 1)) // Accel or Menu * 0.8 *
				{
					if (!WindMgt.HelpOn || !HelpFilter(e))
					{
						Report(this, CVEVT_MenuCommand, e);
						((pDW)pRequestor) -> _MenuCommand ((MenuCommandEvt&)e);
					}
				}
				else										// * 0.8 *
					((pDW)pRequestor) -> _Default (e);							// * 0.8 *
#endif // WIN32
	}
	break;
	
#if defined(WIN32)
	// OwnerDraw Messages
	case WM_COMPAREITEM:	// Vergleich zweier Einträge (Items)
		Report(this, CVEVT_CompareItem, e);
		retval = ((pDW)pRequestor) -> _CompareItem ((OwnerDrawEvt &)e,
			(void *)(((COMPAREITEMSTRUCT *)CV_RunTime::Event_lParam(e)) -> itemData1),
			(void *)(((COMPAREITEMSTRUCT *)CV_RunTime::Event_lParam(e)) -> itemData2));
		CV_RunTime::EC_SetRetval (this, retval);
		break;
		
	case WM_DELETEITEM:	// Item wird gelöscht
		Report(this, CVEVT_DeleteItem, e);
		retval = ((pDW)pRequestor) -> _DeleteItem ((DeleteItemEvt &)e);
		CV_RunTime::EC_SetRetval (this, retval);
		break;
		
	case WM_DRAWITEM:	// Item neu zeichnen 
		{
			DRAWITEMSTRUCT *pDI = (DRAWITEMSTRUCT *)CV_RunTime::Event_lParam(e);
			
			Report(this, CVEVT_DrawItem, e);
			if (pDI -> itemID == -1) {
				// keine Elemente in Control
				retval = ((pDW)pRequestor) -> _DrawItemFocus ((DrawItemEvt &)e);
			} else switch (pDI -> itemAction) {
				// Element normal behandeln
	case ODA_DRAWENTIRE:
		((pDW)pRequestor) -> _DrawEntireItem ((DrawItemEvt &)e);
		retval = true;
		break;
		
	case ODA_SELECT:
		retval = ((pDW)pRequestor) -> _DrawItemSelect ((DrawItemEvt &)e);
		break;
		
	case ODA_FOCUS:
		retval = ((pDW)pRequestor) -> _DrawItemFocus ((DrawItemEvt &)e);
		break;
		
	default:
		((pDW)pRequestor) -> _Default ( e );
		break;
			}
			CV_RunTime::EC_SetRetval (this, retval);
		}
		break;
		
	case WM_MEASUREITEM:	// Größe eines Items bestimmen
		Report(this, CVEVT_MeasureItem, e);
		CV_RunTime::Event_SetExtra(e, &hEContext);	// HWND merken			
		retval = ((pDW)pRequestor) -> _MeasureItem ((MeasureItemEvt &)e);
		CV_RunTime::EC_SetRetval (this, retval);
		break;
		
	case WM_TIMER:
		Report(this, CVEVT_Strobe, e);
		((pDW)pRequestor) -> _Strobe ((StrobeEvt &)e);
		CV_RunTime::EC_SetRetval (this, retval = true);
		break;
		
		// PalettenBehandlung
	case WM_PALETTEISCHANGING:
	case WM_PALETTECHANGED:
	case WM_QUERYNEWPALETTE:
		Report(this, CVEVT_PaletteChange, e);
		((pDW)pRequestor) -> _PaletteChange ((PaletteChangeEvt &)e);
		CV_RunTime::EC_SetRetval (this, retval = true);
		break;
		
	case WM_HELP:		// ins normale Helpsystem einspeisen
		SendMessage (hEContext, WM_CVHELP, (uint)HelpWmHelp, (ulong)CV_RunTime::Event_lParam(e));
		CV_RunTime::EC_SetRetval (this, retval = true);
		break;
		
	case WM_NOTIFY:
		{
			HWND hwndfrom = ((LPNMHDR)CV_RunTime::Event_lParam(e)) -> hwndFrom;
			pWind_Imp pWI = NULL;
			
			if (::IsWindow(hwndfrom))
				pWI = (pWind_Imp)(_AppImpFind() -> ControlList() -> Find ((HANDLE)hwndfrom));
			
			CV_RunTime::Event_SetExtra (e, pWI);
			
			switch (((LPNMHDR)CV_RunTime::Event_lParam(e)) -> code) {
			case NM_CLICK:
			case NM_RCLICK:
				Report(this, CVEVT_NfyClick, e);
				((pDW)pRequestor) -> _NfyClick ((NotifyEvt &)e );
				break;
				
			case NM_DBLCLK:
			case NM_RDBLCLK:
				Report(this, CVEVT_NfyDblClick, e);
				((pDW)pRequestor) -> _NfyDblClick ((NotifyEvt &)e);
				break;
				
			case NM_KILLFOCUS:
			case NM_SETFOCUS:
				Report(this, CVEVT_FocusChange, e);
				((pDW)pRequestor) -> _FocusChange ((FocusChangeEvt&)e);
				break;
				
				// control - spezifische Notifikationen
			case TVN_KEYDOWN:	// TreeView
			case LVN_KEYDOWN:	// ListView
				Report (this, CVEVT_KeyDown, e);
				((pDW)pRequestor) -> _NfyKeyDown ((NotifyEvt &)e);
				break;
				
			case TVN_BEGINDRAG:	// TreeView
			case LVN_BEGINDRAG:	// ListView
			case TBN_BEGINDRAG:	// ToolBar
				Report (this, CVEVT_NfyBeginDrag, e);
				((pDW)pRequestor) -> _NfyBeginDrag ((NotifyEvt &)e);	
				break;
				
			case TBN_ENDDRAG:	// ToolBar
				Report (this, CVEVT_NfyEndDrag, e);
				((pDW)pRequestor) -> _NfyEndDrag ((NotifyEvt &)e);	
				break;
				
			case TBN_RESET:		// ToolBar
				Report (this, CVEVT_NfyReset, e);
				((pDW)pRequestor) -> _NfyReset ((NotifyEvt &)e);	
				break;
				
			case TVN_BEGINRDRAG:	// TreeView
			case LVN_BEGINRDRAG:	// ListView
				Report (this, CVEVT_NfyBeginRDrag, e);
				((pDW)pRequestor) -> _NfyBeginRDrag ((NotifyEvt &)e);	
				break;
				
			case TVN_BEGINLABELEDIT:	// TreeView
			case LVN_BEGINLABELEDIT:	// ListView
			case CBEN_BEGINEDIT:		// ComboBoxEx
				Report (this, CVEVT_NfyBeginLabelEdit, e);
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					(LONG)((pDW)pRequestor) -> _NfyBeginLabelEdit ((NotifyEvt &)e));
				break;
				
			case TVN_ENDLABELEDIT:	// TreeView
			case LVN_ENDLABELEDIT:	// ListView
			case CBEN_ENDEDIT:		// ComboBoxEx
				Report (this, CVEVT_NfyEndLabelEdit, e);
				((pDW)pRequestor) -> _NfyEndLabelEdit ((NotifyEvt &)e);	
				break;
				
			case TBN_QUERYDELETE:	// ToolBar
				Report (this, CVEVT_NfyQueryDelete, e);
				// ACHTUNG: verkehrte Welt true <--> false
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					retval = (LONG)((pDW)pRequestor) -> _NfyQueryDelete ((NotifyEvt &)e) ? false : true);
				CV_RunTime::EC_SetRetval (this, retval);
				break;

			case TVN_DELETEITEM:	// TreeView
			case LVN_DELETEITEM:	// ListView
			case CBEN_DELETEITEM:	// ComboBoxEx
				Report (this, CVEVT_NfyDeleteItem, e);
				((pDW)pRequestor) -> _NfyDeleteItem ((NotifyEvt &)e);	
				break;
				
			case LVN_DELETEALLITEMS:	// ListView
				Report (this, CVEVT_NfyDeleteAllItems, e);
				((pDW)pRequestor) -> _NfyDeleteAllItems ((NotifyEvt &)e);	
				break;
				
			case TVN_GETDISPINFO:	// TreeView
			case LVN_GETDISPINFO:	// ListView
				Report (this, CVEVT_NfyGetDispInfo, e);
				((pDW)pRequestor) -> _NfyGetDispInfo ((NotifyEvt &)e);	
				break;
				
			case TVN_SETDISPINFO:	// TreeView
			case LVN_SETDISPINFO:	// ListView
				Report (this, CVEVT_NfySetDispInfo, e);
				((pDW)pRequestor) -> _NfySetDispInfo ((NotifyEvt &)e);	
				break;
				
			case TBN_QUERYINSERT:	// ToolBar
				Report (this, CVEVT_NfyQueryInsert, e);
				// ACHTUNG: verkehrte Welt true <--> false
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					retval = (LONG)((pDW)pRequestor) -> _NfyQueryInsert ((NotifyEvt &)e) ? false : true);
				CV_RunTime::EC_SetRetval (this, retval);
				break;

			case LVN_INSERTITEM:	// ListView
			case CBEN_INSERTITEM:	// ComboBoxEx
				Report (this, CVEVT_NfyInsertItem, e);
				((pDW)pRequestor) -> _NfyInsertItem ((NotifyEvt &)e);	
				break;
				
			case TVN_ITEMEXPANDING:	// TreeView
				Report (this, CVEVT_NfyItemExpanding, e);
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					(LONG)((pDW)pRequestor) -> _NfyItemExpanding ((NotifyEvt &)e));
				break;
				
			case TVN_ITEMEXPANDED:	// TreeView
				Report (this, CVEVT_NfyItemExpanded, e);
				((pDW)pRequestor) -> _NfyItemExpanded ((NotifyEvt &)e);	
				break;
				
			case LVN_ITEMCHANGING:	// ListView
				Report (this, CVEVT_NfyItemChanging, e);
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					(LONG)((pDW)pRequestor) -> _NfyItemChanging ((NotifyEvt &)e));
				break;
				
			case LVN_ITEMCHANGED:	// ListView
				Report (this, CVEVT_NfyItemChanged, e);
				((pDW)pRequestor) -> _NfyItemChanged ((NotifyEvt &)e);	
				break;
				
			case LVN_COLUMNCLICK:	// ListView
				Report (this, CVEVT_NfyColumnClick, e);
				((pDW)pRequestor) -> _NfyColumnClick ((NotifyEvt &)e);	
				break;
				
			case TVN_SELCHANGING:	// TreeView
				Report (this, CVEVT_NfySelChanging, e);
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					(LONG)((pDW)pRequestor) -> _NfySelChanging ((NotifyEvt &)e));
				break;
				
			case TVN_SELCHANGED:	// TreeView
				Report (this, CVEVT_NfySelChanged, e);
				((pDW)pRequestor) -> _NfySelChanged ((NotifyEvt &)e);	
				break;
				
			case TBN_BEGINADJUST:	// Toolbar
				Report (this, CVEVT_NfyBeginAdjust, e);
				((pDW)pRequestor) -> _NfyBeginAdjust ((NotifyEvt &)e);	
				break;
				
			case TBN_ENDADJUST:	// Toolbar
				Report (this, CVEVT_NfyEndAdjust, e);
				((pDW)pRequestor) -> _NfyEndAdjust ((NotifyEvt &)e);	
				break;
				
			case TBN_CUSTHELP:	// Toolbar
				Report (this, CVEVT_NfyCustHelp, e);
				((pDW)pRequestor) -> _NfyCustHelp ((NotifyEvt &)e);	
				break;
				
			case TBN_GETBUTTONINFO:	// Toolbar
				Report (this, CVEVT_NfyGetButtonInfo, e);
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					retval = (LONG)((pDW)pRequestor) -> _NfyGetButtonInfo ((NotifyEvt &)e));
				CV_RunTime::EC_SetRetval (this, retval);
				break;
				
			case TBN_TOOLBARCHANGE:	// Toolbar
				Report (this, CVEVT_NfyToolBarChange, e);
				((pDW)pRequestor) -> _NfyToolBarChange ((NotifyEvt &)e);	
				break;
				
			case TTN_NEEDTEXT:	// ToolTip
				Report (this, CVEVT_NfyNeedText, e);
				((pDW)pRequestor) -> _NfyNeedText ((ToolTipEvt &)e);
				break;
				
			case TTN_POP:
				Report (this, CVEVT_NfyHidingTip, e);
				((pDW)pRequestor) -> _NfyHidingTip ((ToolTipEvt &)e);
				break;
				
			case TTN_SHOW:
				Report (this, CVEVT_NfyShowingTip, e);
				((pDW)pRequestor) -> _NfyShowingTip ((ToolTipEvt &)e);
				break;
				
			case UDN_DELTAPOS:
				Report (this, CVEVT_NfyDeltaPos, e);
				SetWindowLong (hEContext, DWL_MSGRESULT, 
					retval = (LONG)((pDW)pRequestor) -> _NfyDeltaPos ((NotifyEvt &)e));
				CV_RunTime::EC_SetRetval (this, retval);
				break;
				
			default:
				((pDW)pRequestor) -> _Default (e);
				break;
		}
		break;
	}	// WM_NOTIFY
#endif
	
	case WM_SYSCOMMAND:
		if (WindMgt.HelpOn && (WindMgt.HelpCursorOn || WindMgt.HelpMenu))
		{
			if ((( CV_RunTime::Event_wParam ( e ) & SC_MASK ) != SC_MOUSEMENU )
				&& (( CV_RunTime::Event_wParam ( e ) & SC_MASK ) != SC_KEYMENU ))
				SendMessage(hEContext, WM_CVHELP,
				(uint)HelpMenu,((((ulong)CV_RunTime::Event_wParam(e)) | 0x10000) & 0x1ffff));
			else
				((pDW)pRequestor) -> _Default ( e );
			break;
		}
		if (( CV_RunTime::Event_wParam ( e ) & SYSMENU_Mask ) == SYSMENU_Mask )
			((pDW)pRequestor) -> _Default ( e );
		else
		{
			Report(this, CVEVT_MenuCommand, e );
			((pDW)pRequestor) -> _MenuCommand ((MenuCommandEvt&)e );
		}
		break;
		
	default:
		((pDW)pRequestor) -> _Default ( e );
		break;
	}	// End of SWITCH
	
	return retval;
}	// End of "Window" FUNCTION "Dispatch"



void	Wind_Imp::  MenuHandler	( MhType mt , Event e )
{
	if (mt != MhCommand)
		Default(e);
}	// End of "Window" FUNCTION "MenuCommand"


void	Wind_Imp::  ButtonClick	( ControlEvt e )
{
	ulong current_state;
	ulong current_check;
	HWND hctrl =  (HWND)LoWord (CV_RunTime::Event_lParam(e));
	
	if (hctrl) {
		long current_sty = GetWindowLong (hctrl, GWL_STYLE);
       	long ButtonMask = 0x00000007;
		
        switch( (int)(ButtonMask & current_sty)) {
		case BS_CHECKBOX :
			current_check = Button_GetCheck (hctrl);
			Button_SetCheck (hctrl, !current_check);
			//            current_check = SendMessage (hctrl,BM_GETCHECK,0,0L);
			//            SendMessage(hctrl,  BM_SETCHECK, ! (int)current_check,0L);
            break;
			
        case BS_3STATE:
			current_state = Button_GetState (hctrl);
			if (current_state == 8) 
				Button_SetState (hctrl, 1);
			else if (current_state == 9) 
				Button_SetState (hctrl, 2);
			else
				Button_SetState (hctrl, 0);
			break;
			
			//            current_state = SendMessage(hctrl,BM_GETSTATE,0,0L);
			//            if ( current_state == 8 )
			//                SendMessage( hctrl,BM_SETCHECK,1,0L);
			//            else if ( current_state == 9 )     
			//                SendMessage( hctrl, BM_SETCHECK,2,0L);
			//            else
			//                SendMessage( hctrl, BM_SETCHECK,0,0L);
			//            break;
			
		default:
			Default ((Event&)e );
		}
	}
	else
		Default ((Event&)e );
	
}	// End of "Window" FUNCTION "ButtonClick"



void	Wind_Imp:: Default( Event ) 
{ };

void	Wind_Imp::  SetStyle (ulong style , BOOL setflag)
{
	if (setflag)
		WndStyle	|= style;
	else
		WndStyle	&= (~style);
	
	if (hEContext) {
		long current_sty = GetWindowLong (hEContext, GWL_STYLE);
		
		if (setflag)	
			current_sty |= style;
		else
			current_sty &= (~style);
		SetWindowLong (hEContext, GWL_STYLE, current_sty );
	}
}	// End of "Wind_Imp" FUNCTION "SetStyle"


void	Wind_Imp::  Update	()
{
    if (hEContext  )	// * 1.9, 1.25 * 
		UpdateWindow ( hEContext);
}	


void	Wind_Imp::  RePaint	()
{
	if (hEContext  )		// * 1.9, 1.25 * 
		InvalidateRect ( hEContext, NULL, true );	// * 1.10 *
}	

void	Wind_Imp::  RePaintRect	(Rectangle area)		// * 1.10 * start
{
	if (hEContext )	// * 1.25 *, * 1.33 *
	{
		area. Top() =                               
			CV_RunTime:: DevToLog( this, area.UpperLeft()).Y();
		area. Bottom() = 
			CV_RunTime:: DevToLog( this, area.LowerRight()).Y();
		
		InvalidateRect ( hEContext, (RECT *)&area, true );
	}
}	// * 1.10 * end

Point	Wind_Imp::  ChangePosition ( Point origin )
{
	// * 0.9, 1.3 Begin *
	Point old;
	HWND hparent;
	
	old = WndPosition;
	WndPosition = origin;
	
	if	( hEContext )		// * 1.25 *
	{
		Dimension fs = FrameSize(hEContext);
		
#if defined(WIN32)			// #HK960401
		Point p(WndPosition.X(),  WndPosition.Y() + fs.Height() - 1);
		
		origin = CV_RunTime::LogToDev(WndParent, p); // * 1.13 *
		if (WndParent) 
			hparent = WndParent -> hEContext;
		else
			hparent = ::GetParent(hEContext); 
		
		if (hparent) 			       // * 1.14 *
		{
			if ( !( WS_CHILD & (GetWindowLong (hEContext, GWL_STYLE)))) {
				if (WS_CHILD & (GetWindowLong (hparent, GWL_STYLE))) {
					origin = CV_RunTime::LogToDev (WndParent, p);
					ClientToScreen (hparent, (POINT *)&origin);
					//					origin.Y() += (fs.Height() -1);
				} else {
					origin = CV_RunTime::LogToDev (WndParent, p);
					ClientToScreen( hparent, (POINT *)&origin);
				}
			} else if (WndParent && (WndParent -> WindMgt.NoRedraw))	// * 1.30 *
			{
				SetWindowPos(hEContext, NULL, origin.X (), origin.Y (), 0,0,
					SWP_NOREDRAW |SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
				return	old;
			}
		}
#else
		Point p(WndPosition.X(),  WndPosition.Y() + fs.Height() - 1);
		
		origin = CV_RunTime::LogToDev(WndParent, p); // * 1.13 *
		if (hparent = (HWND)GetWindowWord (hEContext, GWW_HWNDPARENT)) 			       // * 1.14 *
		{
			if ( !( WS_CHILD & (GetWindowLong( hEContext, GWL_STYLE))))
				ClientToScreen( hparent, (POINT *)&origin);
			else if (WndParent && (WndParent -> WindMgt.NoRedraw))	// * 1.30 *
			{
				SetWindowPos(hEContext, NULL, origin.X (), origin.Y (), 0,0,
					SWP_NOREDRAW |SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
				return	old;
			}
		}
#endif
		
		MoveWindow ( hEContext, origin.X (), origin.Y (), 
			fs.Width (), fs.Height (), 
			true );
	}
	//* 0.9, 1.3 End *
	return	old;
}	


Dimension	Wind_Imp::  ChangeSize ( Dimension size )
{
	HWND hparent;			   
	// * 0.9, 1.3 Begin *
	if (hEContext)	// * 1.25 *
	{
		Point p(WndPosition.X(), WndPosition.Y() + size.Height() -1); 	// * 1.13 *
		p = CV_RunTime::LogToDev(WndParent,p);
#if !defined(WIN32)
		if ((hparent = (HWND)GetWindowWord (hEContext, GWW_HWNDPARENT)) 			       // * 1.14 *
#else
			if ((hparent = (HWND)GetWindowLong (hEContext, GWL_HWNDPARENT)) 			       // * 1.14 *
#endif
				&& !( WS_CHILD & (GetWindowLong( hEContext, GWL_STYLE))))
				ClientToScreen( hparent, (POINT *)&p);
			
			MoveWindow (hEContext, p.X(), p.Y(), size.Width(), size.Height(), true);
			return	FrameSize(hEContext);
	}
	else {
		Dimension old;
		
		old = WndSize;
		WndSize = size;
		return old;
	}
	// * 0.9, 1.3 End *
}	

void Wind_Imp::PaintBackground (HDC bkDC, Rectangle *prc)
{
	HBRUSH hBrush = 0;
	BOOL isStock = true;
	BOOL tmpBrush = false;
	
	if (WndBackground) {
		hBrush = CV_RunTime::Brush_hBrush (WndBackground);
		isStock = CV_RunTime::Brush_isStock (WndBackground);
	}
#if !defined(WIN32)
	else if ((UINT)(hBrush = (HBRUSH)GetClassWord (hEContext, GCW_HBRBACKGROUND)) < (COLOR_ENDCOLORS+1))
#else
		else if ((UINT)(hBrush = (HBRUSH)GetClassLong (hEContext, GCL_HBRBACKGROUND)) < (COLOR_ENDCOLORS+1))
#endif
	{
		if (!hBrush)
			hBrush	= CreateSolidBrush (GetSysColor(COLOR_WINDOW));
		else
			hBrush	= CreateSolidBrush (GetSysColor(((UINT)(hBrush)) - 1));
		isStock = false;
		tmpBrush = true;
	}
	
	if (!isStock)
	{
		Point p;
		
		UnrealizeObject (hBrush);
		ClientToScreen (hEContext, (POINT *)&p);
#if !defined(WIN32)
		SetBrushOrg (bkDC, p.X()%8, p.Y()%8);
#else
		SetBrushOrgEx (bkDC, p.X()%8, p.Y()%8, NULL);
#endif
	}
	
	Rectangle r;
	
	if (prc) {
		r = *prc;
		r.Top() = CV_RunTime::DevToLog (this, r.UpperLeft()).Y();
		r.Bottom() = CV_RunTime::DevToLog (this, r.LowerRight()).Y();
	} else
		GetClipBox (bkDC, (RECT *)&r);
	FillRect (bkDC, (RECT *)&r, hBrush);
	if (tmpBrush)
		DeleteObject(hBrush);
}

void	Wind_Imp::  CanvasErase	(Rectangle *prc)
{
    if (hEContext )	
		PaintBackground(GetDC(), prc);
}	

Dimension	Wind_Imp::  TextSize ( const char* what )    // * 0.1 Begin *
{
	DCFlags.FontNeeded = 1;
	if	( GetDC() )								// * 1.29 *
	{
#if !defined(WIN32)
		ulong d =   GetTextExtent( hDC, what,  CV_strlen( what ));
#else
		SIZE d;
		
		GetTextExtentPoint (hDC, what, CV_strlen(what), &d);
#endif
		return (*((Dimension *)&d));				/* 0.5 End */
	}	
	return Dimension();
}	


void	Wind_Imp::  ToTop	()
{
    if (hEContext) {		// * 1.9 , 1.25 *
		if (hEContext != GetForegroundWindow()) 
			SetForegroundWindow (hEContext);
		BringWindowToTop (hEContext);
	}
}	// End of "Wind_Imp" FUNCTION "ToTop"


Rectangle	Wind_Imp::  CanvasRect	()
{
	Rectangle	rect(0,0,0,0);
	if (hEContext)	// * 1.25 *
	{
		GetClientRect ( hEContext, (RECT *)&rect );
#ifdef RECT_INCLUSIVE
		rect. Top() =                               // * 0.17 start *
			CV_RunTime:: DevToLog( this, rect.UpperLeft()).Y(); // * 1.1 * 
#else
		rect. Top() =                               // * 0.17 start *
			CV_RunTime:: DevToLog( this, rect.UpperLeft()).Y() + 1; // * 1.1 * 
#endif
		rect. Bottom() = 
			CV_RunTime:: DevToLog( this, rect.LowerRight()).Y() + 1;  // * 1.1 *
	}
	return	rect;                                   // * 0.17 end *
	
}	// End of "Wind_Imp" FUNCTION "CanvasRect"


Rectangle	Wind_Imp::  WindowRect	()
{
	Rectangle	rect(0,0,0,0);
	
	if (hEContext) 	// * 1.25 *
	{
		GetWindowRect ( hEContext, (RECT *)&rect );
#if !defined(WIN32)
		ScreenToParent( hEContext, ((Point*)(&rect)));			// * 1.7 *
		ScreenToParent( hEContext, &(((Point*)(&rect))[1]));	// * 1.7 *
#else
		HWND hparent;
		
		if (WndParent) 
			hparent = WndParent -> hEContext;
		else
			hparent = ::GetParent (hEContext); 
		
		ScreenToParent( hparent, ((Point*)(&rect)));
		ScreenToParent( hparent, &(((Point*)(&rect))[1]));
#endif
		
#ifdef RECT_INCLUSIVE
		rect. Top() =                               // * 0.17 start *
			CV_RunTime:: DevToLog( WndParent, rect.UpperLeft()).Y(); // * 1.1 *
#else
		rect. Top() =                               // * 0.17 start *
			CV_RunTime:: DevToLog( WndParent, rect.UpperLeft()).Y() + 1; // * 1.1 *
#endif
		rect. Bottom() = 
			CV_RunTime:: DevToLog( WndParent, rect.LowerRight()).Y() + 1; // * 1.1 *
	}
	return	rect;                                   // * 0.17 end *
	
}	// End of "Wind_Imp" FUNCTION "WindowRect"


BOOL	Wind_Imp::  isIconic	()
{
	if (hEContext)	// * 1.25 *
		return	IsIconic ( hEContext);
	else
		return false;
	
}	// End of "Wind_Imp" FUNCTION "isIconic"


BOOL	Wind_Imp::  isVisible	()
{
	if (hEContext)			// * 1.25 *
		return	IsWindowVisible ( hEContext);
	else
		return false;
	
}	// End of "Wind_Imp" FUNCTION "isVisible"


BOOL	Wind_Imp::  isZoomed	()
{
	if ( hEContext)	// * 1.25 *
		return	IsZoomed ( hEContext);
	else
		return false;
	
}	// End of "Wind_Imp" FUNCTION "isZoomed"

static char output [512];

void	Wind_Imp::  TextPrintf (Point where, const char* what,  const char * args )
{
	wvsprintf(output, what, (char *)args);
	TextPrint(output, where);
}

void	Wind_Imp::  TextPrintf( const char* what, const char * args )
{
	wvsprintf(output, what, (char *)args);
	
	if (hEContext )	// * 1.9 , 1.25 * 
	{
		DCFlags.FontNeeded = 1;
		DCFlags.PenNeeded = 1;
		
		if	( GetDC() )
		{
#if !defined(WIN32)
			ulong l = GetCurrentPosition(hDC);
			Point p (LoWord(l), HiWord(l)); 
#else
			POINT p;
			
			GetCurrentPositionEx (hDC, &p);
#endif
			SetTextAlign(hDC, TA_LEFT | TA_BOTTOM | TA_UPDATECP);
			TextPrint (output, (Point &)p);
			SetTextAlign(hDC, TA_LEFT | TA_BOTTOM | TA_NOUPDATECP);
		}
	}	// End of IF
}

void	Wind_Imp::  TextPrint	( const char* what, Point where )
{
	DCFlags.FontNeeded = 1;
	DCFlags.PenNeeded = 1;
    if (hEContext )	// * 1.9 , 1.25 * 
	{
		if	( GetDC() )
		{
			ulong oldback;
			int old_mode;
			int new_mode = TRANSPARENT;
			BOOL using_brush = false;
			
			if (WndBrush)
			{
				LogicalBrush lb(WndBrush);
				if (lb.GetType() != BS_HOLLOW)
				{
					oldback = SetBkColor(hDC, lb.GetColor());
					new_mode = OPAQUE;
					using_brush = true;
				}
			}
			old_mode = SetBkMode(hDC, new_mode);
			TextOut ( hDC, where.X (), where.Y(), what, CV_strlen ( what ));
			SetBkMode(hDC, old_mode);
			if (using_brush)
				SetBkColor(hDC, oldback);
		}
	}	// End of IF
}	// End of "Wind_Imp" FUNCTION "TextPrint"


Point	Wind_Imp::  MoveTo	( Point where )
{
    if (hEContext )	// * 1.9, 1.25 * 
	{
		DCFlags.PenNeeded = 1;
		
		if	( GetDC() )			 
		{
#if !defined(WIN32)
			ulong ul =  ::MoveTo (hDC, where.X (), where.Y ());
#else
			POINT ul;
			
			::MoveToEx (hDC, where.X (), where.Y (), &ul);
#endif
			
			return	*((Point *)&ul);
		}
	}
	return	Point ( 0, 0 );
}	


void	Wind_Imp::  LineTo	( Point where )
{
	if (hEContext )	// * 1.9, 1.25 * 
	{
		DCFlags.PenNeeded = 1;
		if (GetDC())
			::LineTo ( hDC, where.X (), where.Y ());
	}
}	// End of "Wind_Imp" FUNCTION "LineTo"


void	Wind_Imp::  PaintRectangle	( Rectangle rect, PaintMode pm )
{
    if (hEContext )	// * 1.9, 1.25 * 
	{
		if	( GetDC() )
		{
			HBRUSH hBrush;
			if (WndBrush)
				hBrush = CV_RunTime::Brush_hBrush ( WndBrush );
			else
				hBrush = (HBRUSH)GetStockObject ( 4 );
			
			if (rect.Top() > rect.Bottom())		// * 1.17 *
			{
				int tmp;
				tmp = rect.Top();
				rect.Top() = rect.Bottom();
				rect.Bottom() = tmp;
			}
			
			// Move Rectangle down one pixel to allow for Windows drawing.
			rect.Top() = rect.Top()-1;
			rect.Bottom() = rect.Bottom()-1;
			
			if (rect.Left() > rect.Right())
			{
				int tmp;
				tmp = rect.Left();
				rect.Left() = rect.Right();
				rect.Right() = tmp;
			}                                       // * 0.19 end *
			
			switch	( pm )
			{
			case Frame:
				FrameRect ( hDC, (RECT *)&rect, hBrush );
				break;
				
			case Invert:
				InvertRect ( hDC, (RECT *)&rect );
				break;
				
			default:
				FillRect ( hDC, (RECT *)&rect, hBrush );
				break;
				
			}	// End of SWITCH
		}	// End of IF
	}
}	// End of "Wind_Imp" FUNCTION "PaintRectangle"


pPointer Wind_Imp::ChangePointer (pPointer new_Pointer)
{
	pPointer old	= WndPointer;
	
	WndPointer = new_Pointer;
	
	if (hEContext) {					// * 1.19 , 1.25 *
		HCURSOR hCursor = NULL;
		
		if (new_Pointer)
			hCursor = SetCursor (CV_RunTime::Pointer_hPointer (new_Pointer));
		else
			hCursor = SetCursor (LoadCursor (NULL, IDC_ARROW));
		
		// #HK970121
		//		if (NULL == old && NULL != hCursor)
		//			old = new Pointer (hCursor);		// Wrapper erzeugen
	}
	
	return old;
}	// End of "Wind_Imp" FUNCTION "ChangePointer"


// * 0.4 Begin *
pBrush	Wind_Imp::  ChangeBackground ( pBrush new_Background )
{
	pBrush	old	= WndBackground;
	WndBackground	= new_Background;
	if (hDC)			// * 1.20 start *
	{
		LogBackBrush lbb(this);
		SetBkColor(hDC, lbb.GetColor());
		if (lbb.GetType() == BS_HOLLOW)
			SetBkMode(hDC, TRANSPARENT);
		else
			SetBkMode(hDC, OPAQUE);
	}								// * 1.20 end *
	return	old;
	
}	// End of "Wind_Imp" FUNCTION "ChangeBackground"
// * 0.4 End *

pBrush	Wind_Imp::  ChangeBrush	( pBrush new_Brush )
{
	pBrush	old	= WndBrush;
	WndBrush	= new_Brush;
	
	DCFlags.BrushInUse = 0; 
	DCFlags.BrushNeeded = 1;
	GetDC();
	return old;
	
}	// End of "Wind_Imp" FUNCTION "ChangeBrush"


pFont	Wind_Imp::  ChangeFont	( pFont new_Font )
{
	pFont	old	= WndFont;
	WndFont		= new_Font;
	
	if (hDC)
	{
		DCFlags.FontNeeded = 1;
		DCFlags.FontInUse = 0;
		GetDC();
	}
	return	old;
	
}	// End of "Wind_Imp" FUNCTION "ChangeFont"


pMenu	Wind_Imp::  ChangeMenu	( pMenu new_Menu )
{									// * 1.12, 1.15 start *
	pMenu	old	= WndMenu;
	WndMenu		= new_Menu;
	HMENU	MenuHandle = (new_Menu ? CV_RunTime::Menu_hMenu ( new_Menu ) : 0); 
	
	CV_RunTime::Window_EnsureCaption (this, WF_HAS_MENU, MenuHandle != 0);
	if ( hEContext)	// * 1.25 *
	{
		AssociateMenu(false);
		WndFlags  &= (~WF_MENU_CHANGED);	// Update menu changes.
	}
	return	old;							   // * 1.12, 1.15 end *
	
}	// End of "Wind_Imp" FUNCTION "ChangeMenu"

void Wind_Imp::AssociateMenu(BOOL ViaPost )
{
	HMENU	MenuHandle = (WndMenu ? CV_RunTime::Menu_hMenu ( WndMenu ) : 0); 
	SetMenu (hEContext, MenuHandle);
}

pPen	Wind_Imp::  ChangePen	( pPen new_Pen )
{
	pPen	old	= WndPen;
	WndPen		= new_Pen;
	
	DCFlags.PenNeeded = 1;
	DCFlags.PenInUse = 0;
	GetDC();
	return old;
	
}	// End of "Wind_Imp" FUNCTION "ChangePen"


pAccel	Wind_Imp::  ChangeAccel	( pAccel new_Accel )
{
	pAccel	old	= WndAccel;
	WndAccel	= new_Accel;
	
	if (GetActiveWindow() == hEContext)
		AssociateAccel(WndAccel ? true : false);
	
	return	old;
}	

void Wind_Imp::AssociateAccel(BOOL set)
{
	if (set)
		_AppImpFind() -> SetAccelWind( (WndAccel ? WndAccel -> Handle() : 0), 
		hEContext);
	else
		_AppImpFind() -> SetAccelWind( 0,0);
}

void	Wind_Imp:: 	EvtEnd ()								// * 0.10 Begin *
{
	if (hDC) {
		if (!PaintInfo)			// Release the Device Context if any
		{
			if (hEContext && IsWindow( hEContext))
				ReleaseDC ( hEContext, hDC );
			DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
				DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
				DCFlags.BrushNeeded = 0;
			hDC = 0;
		}
	}
}

void Wind_Imp:: Draw ( pDrawObject pDO)                  // * 0.18 start *
{
	//    if (hEContext )	// * 1.9, 1.25 * 
	CV_RunTime::Window_Draw(pDO, this);
}                                                           // * 0.18 end *


void Wind_Imp:: DrawEx (pDrawObject pDO, DWORD dwData) 	// * 0.18 start *
{
	//    if (hEContext)	// * 1.9, 1.25 * 
	CV_RunTime::Window_DrawEx (pDO, this, dwData);
}                                                                       // * 0.18 end *


int CV_RunTime::  ValidateWindow ( Wind_Imp * pc ) 
{
	if (pc && Handle(pc))
		return  IsWindow(Handle(pc));
	else
		return false;
}

void Wind_Imp:: MouseTrap (Bool OnOffFlag)
{
    if (hEContext )	// * 1.9, 1.25 * 
	{
		if (OnOffFlag)
			SetCapture( hEContext );	
		else
			ReleaseCapture();
	}
}

void	Wind_Imp::  SetCaption	( const char* caption, BOOL fSetText )	// * 1.26 start *
{
	if (WndCapt)
	{
		delete (char*)WndCapt;
		WndCapt = 0;
	}
	if (caption)
	{
		WndCapt	= CV_strdup ( caption );	// Take a copy
		CV_RunTime::Window_EnsureCaption(this, WF_HAS_CAPTION, true);
		if (fSetText && IsWindow(hEContext) ) 											// * 0.5 *
		{
			WndFlags &= (~WF_MENU_CHANGED);
			SetWindowText ( hEContext, (pchar)((char*)WndCapt) );
		}
	}
	else
	{
		if (fSetText && IsWindow(hEContext) ) 											// * 0.5 *
		{
			WndFlags &= (~WF_MENU_CHANGED);
			SetWindowText ( hEContext, (pchar)0 );
			CV_RunTime::Window_EnsureCaption(this, WF_HAS_CAPTION, false);
		}
	}
	if (WndFlags & WF_NEED_UPDATE)
		CV_RunTime::Window_UpdateFrame(this);
	// * 1.26 end *
}	// End of "Wind_Imp" FUNCTION "SetCaption"


void	Wind_Imp::  Scroll( Dimension d, Rectangle rect, BOOL clip )
{	// * 1.31 *
	pRectangle	pRectClip;
	
	rect.Top() = CV_RunTime:: DevToLog( this, rect.UpperLeft()).Y();
	rect.Bottom() = CV_RunTime:: DevToLog( this, rect.LowerRight()).Y();
	
	if (clip) pRectClip = &rect;
	else      pRectClip = 0;
	
	ScrollWindow (hEContext, d.Width(), - d.Height(), 
		(RECT *)&rect, (RECT *)pRectClip);
}

void	Wind_Imp::  Initialise()
{
	WindMgt.Initialised = true;
	Event fake_ev;
	CV_RunTime::Event_wMsg( fake_ev) = WM_CREATE;
	CV_RunTime::Event_wParam ( fake_ev ) = 0;
	CV_RunTime::Event_lParam( fake_ev ) = 0;
	((pDW)pRequestor) -> _WindowInit( fake_ev);
	EvtEnd ( );
}

// Query functions
Point	 Wind_Imp::    GetPosition (  )		/* 1.38 */
{
	Rectangle r = WindowRect();
	return Point(r.Left(), r.Bottom());
}



Dimension	 Wind_Imp::    GetSize (  )
{
	if (hEContext)
		return FrameSize(hEContext);
	else
		return Dimension(0,0);
}

pchar	 Wind_Imp::    GetCaption	( pchar buffer, int len )
{
	if (WndCapt  && buffer)
	{
		int i;
		for (i = 0; (WndCapt[i] && (i < (len -1))); i++)
			buffer[i] = WndCapt[i];
		buffer[i] = '\0';
		return buffer;
	}
	else
		return (char*)0;
}









void	 Wind_Imp::    SetFocus	(  )
{
	::SetFocus(hEContext);
}

void Wind_Imp:: InitSize()
{
	if (IsWindow(hEContext))
	{
		Rectangle r;
		
		// Setup window size
		GetClientRect (hEContext, (RECT *)&r);
		WndSize	= Dimension( r.Right() - r.Left() , r.Bottom() - r.Top() );
		
		// Setup window position
		GetWindowRect(hEContext, (RECT *)&r);
		
		// r.Bottom is one more than actual 
		// bottom position as we are using 
		// Windows co-ordinates (top-left is 0,0).
		
		Point p(r.Left(), r.Bottom()-1);
#if !defined(WIN32)
		if (GetWindowWord(hEContext, GWW_HWNDPARENT))
			ScreenToClient(WndParent -> hEContext, (POINT *)&p);
#else
		HWND hParent = (HWND)GetWindowLong(hEContext, GWL_HWNDPARENT);
		
		if (NULL != hParent) {
			if (WndParent)
				ScreenToClient(WndParent -> hEContext, (POINT *)&p);
			else
				ScreenToClient(hParent, (POINT *)&p);
		}
#endif
		WndPosition = CV_RunTime::DevToLog (WndParent,p);
	}
}


void 	Wind_Imp::HandlePointer(Event e, BOOL isHelp, BOOL isClient)
{
	if (isHelp)
	{
		SetCursor(hHelpCursor);
		if (HiWord(CV_RunTime::Event_lParam(e)) == WM_LBUTTONDOWN)
			ProcessHelpCursor(isClient ? hEContext : (HWND)CV_RunTime::Event_wParam(e), 
			(UINT)LoWord(CV_RunTime::Event_lParam(e)));
		CV_RunTime::EC_SetRetval(this, true);
	}
	else
	{
		if ( WndPointer
			&& ((CV_RunTime::Event_lParam ( e ) & 0xffff) == HTCLIENT)
			&& ((hEContext == (HWND) CV_RunTime::Event_wParam ( e )) || isClient))
		{
			SetCursor( CV_RunTime::Pointer_hPointer( WndPointer));
			CV_RunTime::EC_SetRetval(this,  true);
		}
		else
			((pDW)pRequestor) -> _Default( e);
	}
}

BOOL Wind_Imp::HelpFilter(Event e) 
{
#if !defined(WIN32)
	WORD w = CV_RunTime::Event_wParam(e);
#else
	WORD w = LOWORD(CV_RunTime::Event_wParam(e));
#endif
	
	if ((WindMgt.HelpCursorOn || WindMgt.HelpMenu) && 
		(w !=  ID_CVHELPOFF))
	{
		SendMessage(hEContext, WM_CVHELP, (uint)HelpMenu, (ulong)w);
		//	((pDW)pRequestor) -> _Default ( e );							// * 0.8 *
		return true;
	}
	else if (w >=  ID_CVHELPOFF) {
		if (w ==  ID_CVHELP)
		{
			HWND h;
			if (IsChild(hEContext, h = GetFocus()) || (h == hEContext))
				ProcessHelpCursor (h, HTNOWHERE);
		}
		else if (w ==  ID_CVHELPON)
			EnableHelpCursor(true);
		else if (w ==  ID_CVHELPOFF)
			EnableHelpCursor(false);
		return true;
	}
	
	return false;
}

BOOL Wind_Imp::CloseHandler(CloseStyle cs, Event e)
{
	switch (cs)
	{
	case ChQuery:
		Report(this, CVEVT_QueryClose, e );
		return ((pDW)pRequestor) -> _QueryClose ( e );
		break;
		
	case ChClose:
		Report(this, CVEVT_Close, e );
		((pDW)pRequestor) -> _Close ( e );
		break;
		
	case ChCloseAndTidy:
		Report(this, CVEVT_Close, e );
		((pDW)pRequestor) -> _Close ( e );
		if (IsWindow(hEContext))
			ShowWindow(hEContext,0);
	}
	return true;
}

BOOL Wind_Imp:: ToggleClipChildren( BOOL SetFlag)
{
	long tmpStyle = GetWindowLong(hEContext, GWL_STYLE);
	BOOL retval = ((tmpStyle & WS_CLIPCHILDREN) ? true : false);
	if (SetFlag && !retval)
	{
		tmpStyle = tmpStyle | WS_CLIPCHILDREN;
		SetWindowLong(hEContext, GWL_STYLE, tmpStyle);
	}
	else 
		if ((!SetFlag) && retval)
		{
			tmpStyle = tmpStyle & (~WS_CLIPCHILDREN);
			SetWindowLong(hEContext, GWL_STYLE, tmpStyle);
		}
		return retval;
}

//pScrollBar Wind_Imp::GetWndScrollBar(uint )
//{	
//	return (pScrollBar)0;
//}

// #HK940711 -----------------------------------------------------------------
pScrollBar Wind_Imp::GetWndScrollBar (uint type)
{	
	if (type == SB_HORZ)
		return AppWndHorz;
	else
		return AppWndVert;
}

pWndVertScroll Wind_Imp::  EnableVScroll (BOOL EnableFlag )
{
	CV_RunTime::Window_EnsureBorder(this, WF_VERTSCROLL, EnableFlag);
	if (EnableFlag)
	{
		if ( !AppWndVert )
			return (pWndVertScroll)(AppWndVert = CV_RunTime::WndVertScrollBar__ctor ( CV_RunTime::Wind_Requestor(this) ));
		else
			return (pWndVertScroll)AppWndVert;
	}
	else
	{
		if ( AppWndVert )
			CV_RunTime::WndVertScrollBar__dtor ( AppWndVert );
		return (pWndVertScroll)(AppWndVert = NULL);
	}
	
}	

pWndHorzScroll Wind_Imp::  EnableHScroll (BOOL EnableFlag )
{
	CV_RunTime::Window_EnsureBorder(this, WF_HORZSCROLL, EnableFlag);
	if (EnableFlag)
	{
		if ( !AppWndHorz )
			return (pWndHorzScroll)(AppWndHorz = CV_RunTime::WndHorzScrollBar__ctor ( CV_RunTime::Wind_Requestor(this) ));
		else
			return (pWndHorzScroll)AppWndHorz;
	}
	else
	{
		if ( AppWndHorz )
			CV_RunTime::WndHorzScrollBar__dtor ( AppWndHorz );
		return (pWndHorzScroll)(AppWndHorz = NULL);
	}
	
}	
// #HK940711 -----------------------------------------------------------------

// #HK960320 -----------------------------------------------------------------
BOOL Wind_Imp::DrawCallUp (DrawObject *, BOOL)
{
	return false;		// default does nothing
}
// #HK960320 -----------------------------------------------------------------

// #HK970116 -----------------------------------------------------------------
BOOL Wind_Imp::PreTranslateMsg (MSG *pMsg)
{
	if (NULL != pRequestor)
		return ((pDW)pRequestor) -> _PreTranslateMsg(pMsg);
	return false;
}
// #HK970116 -----------------------------------------------------------------

// #HK970824 -----------------------------------------------------------------
BOOL Wind_Imp::DestroyWindow (void)
{
	if (NULL == hEContext)
		return FALSE;
	
#ifdef _DEBUG
	HWND hWndOrig = hEContext;
#endif
	
	BOOL bResult = ::DestroyWindow (hEContext);
	
	hEContext = NULL;
	return bResult;
}
// #HK970824 -----------------------------------------------------------------

