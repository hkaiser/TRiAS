/*    PortTool v2.2     _appw_im.cxx          */

/* $Header:   G:/cv.win/pvcs/commonvu/src/_appw_im.cxv   3.0.1.0   14 Jul 1992 11:48:14   RONAN  $
 *
 *	a p p w i n d . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	------ Milestone 2.. Beta 2 shipped -------
 *	0.1	ferg	08nov88	moved TopAppWindow,ChildAppWindow,and AppWindow
 *						constructors + AppWindow Create and Show here
 *						from appwind.cxx. Also get AppImpInst from DLL and 
 *						show flag from App.
 *	0.2	ferg	18nov88	new AppWindow functions EnableVScroll, DisableVScroll, 
 *						EnableHScroll and DisableHScroll.
 *	0.3	ferg	18nov88	EventContext::Create is now private.
 *	0.4	ferg	22nov88	AppWindow::SetBackground is gone.
 *	0.5	ferg	28nov88	enable SetCaption after Show.
 *	0.6 jk		29nov88 ------ Milestone 2A. Beta 2A shipped ------
 *	0.7 jk		02dec88	Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2	rs		23aug89 Debug information	
 *	1.3 rs		24Nov89	Long -> Void event handlers
 *	1.4 rs		07Dec89	Support for EnableSysMenu
 *	1.5 hlj		07Dec89 Fix for SetIcon
 *	1.6 rs		??Dec89	Removed Disable functions.
 *						All enable functions now take bool to indicate whether
 *						feature is to be enabled or not.
 *						Addition of EnableMinBox, EnableMaxBox
 *						Temporal dependency removal in current enable functions
 *	1.7 rs		03Jan90	Flagging of windows to support correct style updating.
 *						Also WndFlags is now used to indicate whether window
 *						is a ModeLessDialog or a DeleteWindow.
 *	1.8 hl		05feb90	Code to tag windows as open or closed.
 *	1.9 rs	   	05feb90	Creation of windows in constructor.
 *						This simplifies the implementation of show.
 *	1.10 rs		21feb90 Moved caption handling into Window.
 *						AppWindow:: SetCaption Becomes Window::SetCaption
 *	1.11 rs		27feb90	initialise window size after creation.
 *	1.12 rs		27feb90	Windows which are shown zoomed or iconised don't recieve
 *						WM_SHOW or WM_SETVISIBLE. Need to use WM_SIZE to cater for
 *						these cases when updating the window count.
 *	1.13 rs		20Mar90	Rs from HLJ - Code to decrement close count in 
 *						destructor.
 *	1.14 rs		04Apr90 Improved handling of icon display and erasing.
 *	1.15 rs		04Jun90 Call to move kids when window is resized.
 *	1.16 rs		20Nov90 Send help request events to parent if not handled here
 *	1.17 rs		03Dec90 HelpSystem changes.
 *	1.2  pc		15May92	Removed the handling of WM_CTLCOLOR from AppWindow :: Dispatch.  This is now
 *				passed to WindIm :: Dispatch (see change log 1.4 in _wind_im.cxx).
 *	1.21 pc		05Jun92	Inserted a call to SetStyle to remove the WS_THICKFRAME style,
 *				which was overriding the WS_BORDER style. Also removed the SetStyle(WS_BORDER)
 *				call, since this is automatically performed in EnsureBorder().
 */

#include "tfrmpre.hxx"
#include	<_Link.hxx>   


AWind_Imp::  AWind_Imp	( AppWindow * req, pAWind_Imp from )
: Wind_Imp(req)
{
    // * 2.0 * AppImpInst not needed.

    AppWndVert = AppWndHorz = 0;
	
	if (from)
	{
		WndMenu				= from -> WndMenu;
		WndFont				= from -> WndFont;
		WndBrush			= from -> WndBrush;
		WndPen				= from -> WndPen;
		WndBitmap			= from -> WndBitmap;
		WndAccel			= from -> WndAccel;
		WndSize				= from -> WndSize;
		WndPosition			= from -> WndPosition;
		WndStyle			= from -> WndStyle;
		WndBackground		= from -> WndBackground;
		WndPointer		    = from -> WndPointer;

		AppWndIcon			= from -> AppWndIcon;
		this -> SetCaption( from -> WndCapt);

	}	
	else
	{
		WndCapt				= 0;   
		AppWndIcon			= 0;
		WndBackground		= 0;
	}	

	WindMgt.Anchoring = TRUE;
}	

															// * 0.2 Begin *

/*
 *	Also the derivatives of "AppWindow", namely "TopAppWindow" which is the
 *	top level window without a parent. Also "ChildAppWindow" which has a
 *	parent, and may not overlap with top level windows other than it's parent.
 */

TAWind_Imp::  TAWind_Imp	( AppWindow *req, pAWind_Imp copy_from )
	:	AWind_Imp( req, copy_from )
{
	pApp_Imp AppImpInst = _AppImpFind();
	WndFlags |= ( WF_HAS_CAPTION);				// * 1.7 *
	SetStyle ( WS_CLIPCHILDREN | WS_OVERLAPPED );
											   // * 1.9 start *		
	 hEContext = CreateWindow	(	GetRegClassString(Rcs_AppWindow),
								StaticPtr(""),
								WndStyle,
								CW_USEDEFAULT,
								0,
								CW_USEDEFAULT,
								0,
								0,
								0,
								CV_RunTime :: App_hApp(AppImpInst),
								0
							);
	CV_ASSERT_VALID(hEContext);
	AppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
											   // * 1.9 end *		
 	InitSize();

}	

// #HK951225 ------------------------------------------------------------------
TAWind_Imp :: TAWind_Imp (AppWindow *req, long dwExStyle, char *pClassName)
			: AWind_Imp (req, NULL)
{
pApp_Imp AppImpInst = _AppImpFind();

	WndFlags |= ( WF_HAS_CAPTION);
	SetStyle (WS_CLIPCHILDREN | WS_OVERLAPPED);

	if (NULL == pClassName)		// set DefaultClassName 
		pClassName = GetRegClassString (Rcs_AppWindow);

	if (0L == dwExStyle) {
		hEContext = CreateWindow(pClassName,
									StaticPtr(""),
									WndStyle,
									CW_USEDEFAULT,
									0,
									CW_USEDEFAULT,
									0,
									0,
									0,
									CV_RunTime :: App_hApp(AppImpInst),
									0
								);
	} else {
		hEContext = CreateWindowEx (dwExStyle,
									pClassName,
									StaticPtr(""),
									WndStyle,
									CW_USEDEFAULT,
									0,
									CW_USEDEFAULT,
									0,
									0,
									0,
									CV_RunTime :: App_hApp(AppImpInst),
									0
								);
	}
	CV_ASSERT_VALID(hEContext);
	AppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
											   // * 1.9 end *		
 	InitSize();

}	
// #HK951225

CAWind_Imp::  CAWind_Imp	( AppWindow * req, pWind_Imp parent, pAWind_Imp copy_from )
	: AWind_Imp( req, copy_from )
{
pApp_Imp AppImpInst = _AppImpFind();
HWND hParent = 0;

	if (WndParent = parent) {
		SetStyle ( WS_CHILD  | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
		WndFlags |= WF_IS_CHILD;				// * 1.7 *
		hParent = CV_RunTime :: Handle(WndParent);
		CV_ASSERT_VALID(hParent);
	   	hEContext = CreateWindow (GetRegClassString(Rcs_AppWindow),
					  StaticPtr(""),
					  WndStyle,
					  0, 0,
					  0, 0,
					  hParent,
					  0,
					  CV_RunTime :: App_hApp(AppImpInst),
					  0
			    );
		}
	else
		{
		SetStyle ( WS_CLIPCHILDREN | WS_OVERLAPPED );
		WndFlags |= ( WF_HAS_CAPTION);				// * 1.7 *
											   // * 1.9 start *		
	 	hEContext = CreateWindow	(	GetRegClassString(Rcs_AppWindow),
								StaticPtr(""),
								WndStyle,
								CW_USEDEFAULT,
								(CV_RunTime :: App_WindowCount(AppImpInst) 
										? 0 : CV_RunTime :: App_Scmd(AppImpInst)),
								CW_USEDEFAULT,
								0,
								0,
								0,
								CV_RunTime :: App_hApp(AppImpInst),
								0
							);
		}

	CV_ASSERT_VALID(hEContext);
	AppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
 	InitSize();
}	

														// * 0.1 End *

// #HK930803 ------------------------------------------------------------------
CAWind_Imp :: CAWind_Imp (AppWindow *req, pWind_Imp parent, 
			  pchar pClassName, long dwExStyle, UINT uiID)
	    : AWind_Imp (req, NULL)
{
pApp_Imp AppImpInst = _AppImpFind();
HWND hParent = 0;

	if (pClassName == NULL) // set DefaultClassName 
		pClassName = GetRegClassString (Rcs_AppWindow);

	if (WndParent = parent)	{
		SetStyle (WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		WndFlags |= WF_IS_CHILD;
		hParent = CV_RunTime :: Handle (WndParent);
		CV_ASSERT_VALID(hParent);

		hEContext = CreateWindowEx (
					dwExStyle,
					pClassName,
					pClassName,
					WndStyle,
					0, 0,
					0, 0,
					hParent,
					(HMENU)uiID,		// #HK960220
					CV_RunTime :: App_hApp (AppImpInst),
					0
			    );
	} else {
		SetStyle ( WS_CLIPCHILDREN | WS_OVERLAPPED );
		WndFlags |= (WF_HAS_CAPTION);
											   // * 1.9 start *		
	 	CV_RunTime :: Window_Handle (this) = 
	 		CreateWindowEx (dwExStyle,
					pClassName,
					pClassName,
					WndStyle,
					CW_USEDEFAULT,
					(CV_RunTime :: App_WindowCount (AppImpInst) ? 
						0 : CV_RunTime :: App_Scmd (AppImpInst)),
					CW_USEDEFAULT,	0,
					0,
					0,
					CV_RunTime :: App_hApp (AppImpInst),
					0
			);
		}

	CV_ASSERT_VALID(hEContext);
	AppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
 	InitSize();
}
// ----------------------------------------------------------------------------
														// * 0.1 End *

void	AWind_Imp::  Default ( Event e )
{
	CV_ASSERT_VALID(hEContext);
	long ret = DefWindowProc	(	hEContext,
								CV_RunTime :: Event_wMsg ( e ),
								CV_RunTime :: Event_wParam ( e ),
								CV_RunTime :: Event_lParam ( e )
							);
	CV_RunTime :: EC_SetRetval(this,(long)ret);


}	


// * 1.6 * start

void	AWind_Imp::  EnableBorder	( int BorderType )
{

    switch ( BorderType)
    {
     case (int) AppWindow:: SizingBorder :
		if (WndFlags & WF_HAS_CAPTION)
			SetStyle(WS_CAPTION, TRUE);
    	CV_RunTime :: Window_EnsureBorder(this, WF_HAS_BORDER, TRUE);
    	SetStyle ( WS_THICKFRAME, TRUE );
        break;

    case (int) AppWindow:: NonSizingBorder:
		if (WndFlags & WF_HAS_CAPTION)
			SetStyle(WS_CAPTION, TRUE);
	    CV_RunTime :: Window_EnsureBorder(this, WF_HAS_BORDER, TRUE);
    	SetStyle ( WS_THICKFRAME, FALSE );				//1.21
        break;

    case (int) AppWindow:: NoBorder:
		{
    	SetStyle ( WS_THICKFRAME, FALSE );
		CV_RunTime :: Window_EnsureBorder(this, WF_HAS_BORDER, FALSE);
		if (WndFlags & WF_HAS_CAPTION)
			SetStyle(WS_CAPTION, FALSE);
		else
    		SetStyle ( WS_BORDER, FALSE );

        break;
		}

    default:
        break;
}
	if (hEContext)
		WndFlags |= WF_SIZE_CHANGED;
	if (WndFlags & WF_NEED_UPDATE)
		CV_RunTime :: Window_UpdateFrame(this);
}	


pSysMenu	AWind_Imp::  EnableSysMenu(BOOL EnableFlag )	// * 1.4 * start
{
	pApp_Imp AppImpInst =  _AppImpFind();	
	pSysMenu retval = 0;
	CV_RunTime :: Window_EnsureCaption(this, WF_SYSMENU, EnableFlag);
	SetStyle ( WS_SYSMENU , EnableFlag );
	
	if ( hEContext)
		{
		retval = (pSysMenu)AppImpInst->MenuList() 
				-> Find ((HANDLE)GetSystemMenu (hEContext, FALSE));
		if ((EnableFlag && !retval) || (retval && ! EnableFlag))
			{
			//
			// Perform this section only if status needs to change
 			//
 			if (WndFlags & WF_IS_SHOWN)
 				WndFlags |= WF_MENU_CHANGED;
 			if (!retval)
 				retval = (pSysMenu) new SystemMenu((pWindow)pRequestor);
 			else
 				{
 				delete retval;
 				retval = 0;
 				}
 			}
		}

	if ( WndFlags & WF_NEED_UPDATE)
		CV_RunTime :: Window_UpdateFrame(this);
	return retval;
}	

															// * 0.2 Begin *
void	AWind_Imp::  EnableMinBox	(BOOL EnableFlag )
{
	CV_RunTime :: Window_EnsureCaption( this, WF_MINBOX, EnableFlag);
	SetStyle (  WS_MINIMIZEBOX , EnableFlag);
	if (WndFlags & WF_IS_SHOWN)
		WndFlags |= WF_MENU_CHANGED;
	if (WndFlags & WF_NEED_UPDATE)
		CV_RunTime :: Window_UpdateFrame(this);

}	

void	AWind_Imp::  EnableMaxBox	(BOOL EnableFlag )
{
	CV_RunTime :: Window_EnsureCaption( this, WF_MAXBOX, EnableFlag);
	SetStyle (  WS_MAXIMIZEBOX , EnableFlag);
	if (WndFlags & WF_IS_SHOWN)
		WndFlags |= WF_MENU_CHANGED;
	if (WndFlags & WF_NEED_UPDATE)
		CV_RunTime :: Window_UpdateFrame(this);

}	
	// * 1.6 * end

void	AWind_Imp::  SetIcon	( pIcon icon )
{
	AppWndIcon	= icon;
}	


void	AWind_Imp::  SetPointer	( pPointer cursor )
{
	ChangePointer(cursor);

}	

AWind_Imp::  ~AWind_Imp()
{
	WindMgt.Anchoring = FALSE;
	WindMgt.Destructor = TRUE;

	if (hEContext && IsWindow( hEContext))
		{
		if( !(WndFlags & WF_IS_CHILD))
			{
			if(WindMgt.Opened)
				{
				pApp_Imp AppImpInst = _AppImpFind();
		 		WindMgt.Opened = FALSE;
					// tests if this is the last TopAppWindow
				CV_RunTime :: App_WindowCount( AppImpInst) -= 1;
				if (!CV_RunTime :: App_WindowCount(AppImpInst) && AppImpInst -> QuitOnLast())
						AppImpInst->Quit();
				}
			}
		EvtEnd ( );
		::DestroyWindow( hEContext );
		}
	SetCaption((pchar)0);
}
															// * 1.1 start *
															// * 1.1 end *

void	CAWind_Imp::  Show	(ShowState s )
{

		Wind_Imp :: Show(s);
		BringWindowToTop ( hEContext);
}	

void	TAWind_Imp::  Show	(ShowState s )
{
		CV_ASSERT_VALID(hEContext);

		pApp_Imp AppInst = _AppImpFind();

		// Generate WindowInit event if  necessary 

        if (!WindMgt.Initialised)
            Initialise();

		if (!CV_RunTime :: App_WindowCount(AppInst) && (s == Normal ))
		{
		if	( CV_RunTime :: Window_Capt(this))									// * 1.26 *
	   		SetWindowText ( hEContext, CV_RunTime :: Window_Capt(this));
		ShowWindow(hEContext, CV_RunTime :: App_Scmd(AppInst));
		}
		else
			Wind_Imp :: Show(s);
		UpdateWindow(hEContext);
}	


LRESULT	AWind_Imp::  Dispatch	(Event e)
{
LRESULT retval = 0;

LRESULT * oldptr;

	oldptr = CV_RunTime :: EC_pRetval(this);
	CV_RunTime :: EC_SetpRetval(this, &retval);
    
	switch	(CV_RunTime :: Event_wMsg ( e )) {
	case WM_MOUSEACTIVATE:
		if (WindMgt.HelpOn && WindMgt.HelpCursorOn)
				CV_RunTime :: EC_SetRetval(this, retval = MA_ACTIVATEANDEAT);
		else
			((pDW)pRequestor) -> _Default ( e );
		break;

	case WM_SETCURSOR:				// * 1.19 start *
		{
			HandlePointer(e,InCursorHelpMode());
			break;
		}

	case WM_NCLBUTTONDOWN:
		if (WindMgt.HelpOn && WindMgt.HelpCursorOn) {
			if (!FilterHelpCursor(CV_RunTime :: Event_wParam(e)))
				((pDW)pRequestor) -> _Default ( e );
		}
		else
			((pDW)pRequestor) -> _Default ( e );
		break;

	case WM_LBUTTONDOWN:
		 // Ignore if we're in Help Cursor mode
		 if (!WindMgt.HelpOn || !WindMgt.HelpCursorOn) {
			Report(this, CVEVT_MouseButtonDn, e );
			((pDW)pRequestor) -> _MouseButtonDn ((MouseEvt&)e );
		}
		break;

	case WM_NCPAINT:
		((pDW)pRequestor) -> _Default(e);
		break;
		
	case WM_PAINT:
		{
		PAINTSTRUCT ps;

	   		CV_RunTime :: EventContext_EvtEnd ( this );
			CV_RunTime :: Window_hDC(this)	= BeginPaint (hEContext, &ps);
			PaintInfo = (void*) &ps;

			if ( !IsIconic( hEContext ) ) {
				GetDC();
				Report(this, CVEVT_Expose, e );
				((pDW)pRequestor) -> _Expose ((ExposeEvt&)e );
			} else {	
			HICON hicon;

				DefWindowProc(hEContext, WM_ICONERASEBKGND, (WPARAM)ps.hdc, 0L);
				if (AppWndIcon)
					hicon = CV_RunTime :: Icon_hIcon (AppWndIcon);
				else
					hicon = LoadIcon(NULL, IDI_APPLICATION);
            			DrawIcon(ps.hdc, 0, 0, hicon);

			/* Code to erase background for ICON with parent
			{			 
			HANDLE hparent, icondc;
			if (hparent = ::GetParent(Handle()))
				{
				if (icondc = GetWindowDC( Handle()))
					{
					SendMessage(hparent, WM_ERASEBKGND,icondc, CV_RunTime :: Event_lParam(e));
					ReleaseDC(Handle(), icondc);
					}
				}
			}
			*/
		}	  
		EndPaint (hEContext, &ps );
		CV_RunTime :: Window_hDC(this)	= 0;
		DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
		DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
		DCFlags.BrushNeeded = 0;
		PaintInfo = 0;
		break;
		}	

	case WM_ERASEBKGND:
		{
			if (!IsIconic(hEContext)) {
				if ((!DCFlags. Erasing) && GetWindow(hEContext, GW_CHILD)) {
				Rectangle R;
                                
					GetUpdateRect(hEContext, (RECT *)&R, FALSE);
					DCFlags.Erasing = 1;

				pControl_Imp pc;
				pApp_Imp AppImpInst = _AppImpFind();

					AppImpInst -> ControlList() -> LockOrder (TRUE);
			
				pCVLink	 head =  AppImpInst -> ControlList() -> First();

					while (head && (pc = (Control_Imp *) (head -> Item()))) {
						if (pc -> GetParentImp() == this)
							pc -> Erase();
						head = head -> Next();
					}
					AppImpInst -> ControlList() -> LockOrder (FALSE);
					DCFlags.Erasing = 0;
				}
				Wind_Imp :: Dispatch(e);
			}
			else
				CV_RunTime :: EC_SetRetval(this, retval = TRUE);
		}	
		break;

	case WM_SIZE:
		if ((CV_RunTime :: Event_wParam (e) == SIZEICONIC) ||
			(CV_RunTime :: Event_wParam (e) == SIZEFULLSCREEN))
		{
			if (IsWindowVisible (hEContext)) {
				WndFlags |= WF_IS_SHOWN;
				WndFlags &= (~WF_MENU_CHANGED);
					
			/* **************************************** 
				If this is a top app window 
					if not opened 
						tag it open 
						increment the window count
			 ************************************************ */
				if(!((WndFlags & WF_IS_CHILD) || (WindMgt.Opened))) {
					WindMgt.Opened = TRUE;
				   	CV_RunTime :: App_WindowCount (_AppImpFind()) += 1;		
				}
				if ((WndFlags & WF_IS_CHILD) && 			// * 1.14 * start
				    (CV_RunTime :: Event_wParam (e) == SIZEICONIC)) {
					SetActiveWindow (CV_RunTime :: Handle (WndParent));
					if (!GetFocus())
						::SetFocus (CV_RunTime :: Handle (WndParent));
				}										// * 1.14 * end
			} 
		}

		Report(this, CVEVT_ReSize, e );
		CV_RunTime :: AppWindow_MoveKids(this);					// * 1.15 *
	    	((pDW)pRequestor) -> _ReSize ((ReSizeEvt&)e );
		break;

	case WM_SHOWWINDOW:	// * 1.15 start *
			if ( CV_RunTime :: Event_wParam ( e ) && (!(WndFlags & WF_IS_CHILD)))
				{
				/* **************************************** 
					If this is a top app window 
						if not opened 
							tag it open 
							increment the window count
				 ************************************************ */
				if(!WindMgt.Opened)
					{
					WindMgt.Opened = TRUE;
			   		CV_RunTime :: App_WindowCount( _AppImpFind()) += 1;		
					}
				}		
			if ( CV_RunTime :: Event_wParam ( e ))
				{
				WndFlags |= WF_IS_SHOWN;
				WndFlags &= (~WF_MENU_CHANGED);
				}
			else
				WndFlags &= (~(WF_IS_SHOWN | WF_MENU_CHANGED));
			((pDW)pRequestor) -> _Default ( e );
			break;		// * 1.15 end *

	case WM_DESTROY:				
			if (WndFlags & WF_SYSMENU)
				EnableSysMenu(FALSE);
			Wind_Imp::Dispatch ( e );
			break;					

	case WM_QUERYDRAGICON:
		if (AppWndIcon)
			retval = (LRESULT)(void *)CV_RunTime :: Icon_hIcon (AppWndIcon);
		else
			retval = 0;
		break;

   	default:
        	Wind_Imp::Dispatch( e);
   	}

	CV_RunTime :: EC_SetpRetval (this, oldptr);

return retval;
}

BOOL AWind_Imp :: CloseHandler(CloseStyle cs, Event e)
{
	if (cs == ChCloseAndTidy)
		{
		Report(this, CVEVT_Close, e );
		((pDW)pRequestor) -> _Close ( e );
		if (IsWindow(hEContext))
			if( !(WndFlags & WF_IS_CHILD))
			{
				if( WindMgt.Opened)
				{
				pApp_Imp AppImpInst = _AppImpFind();
		 		WindMgt.Opened = FALSE;
			// tests if this is the last TopAppWindow
				CV_RunTime :: App_WindowCount( AppImpInst) -= 1;
				if (!CV_RunTime :: App_WindowCount(AppImpInst) && AppImpInst -> QuitOnLast())
					AppImpInst->Quit();
				}
			}		
		ShowOwnedPopups(Handle(), 0);
		ShowWindow(Handle(), 0);
		return TRUE;
		}
	else
		return Wind_Imp:: CloseHandler(cs, e);
}

