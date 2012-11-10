/*
 *
 *	_ m d i _ i m . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	sm		Original version
 *
 */

#include "tfrmpre.hxx"
#include	<_link.hxx>

#define COLOR_APPWORKSPACE  12
#define MdiFirstChildID 0x8001
#define	SYSMENU_Mask	0xF000
// #define MF_SYSMENU	    0x2000


ShellWind_Imp :: ShellWind_Imp ( AppWindow *req)
    : AWind_Imp (req, 0)
{
	WindMgt.isMDIWindow = true;
	WindMgt.Anchoring = false;
	hwndClient = 0;
	Sf_UsingChildMenu = Sf_UsingOwnMenu = 0;
	Sf_UsingDefMenu = 1;

	tmpMenu = CreateMenu();
	CV_ASSERT(tmpMenu);
	AppendMenu(tmpMenu, MF_POPUP | MF_ENABLED, (uint) CreatePopupMenu(), "");
	CV_ASSERT(GetSubMenu(tmpMenu, 0));

	pApp_Imp AppImpInst = _AppImpFind();
	WndFlags |= ( WF_HAS_CAPTION);				// * 1.7 *
	SetStyle ( WS_CLIPCHILDREN | WS_OVERLAPPED);
											   // * 1.9 start *		
	hEContext = CreateWindow	(	GetRegClassString(Rcs_MdiFrame),
								StaticPtr(""),
								WndStyle,
								CW_USEDEFAULT,
								0,
								CW_USEDEFAULT,
								0,
								0,
								0,
								AppImpInst -> Handle(),
								0
							);

	SetMenu(hEContext, tmpMenu);

	CLIENTCREATESTRUCT	clientcreate;
	clientcreate.hWindowMenu = GetSubMenu(tmpMenu, 0);
	clientcreate.idFirstChild = MdiFirstChildID;

	long ExtraMdiStyles = 0;
	if (IsWin31())
		ExtraMdiStyles = MDIS_ALLCHILDSTYLES;
	hwndClient = CreateWindow ("mdiclient", 0, 
				   WS_CHILD | WS_CLIPCHILDREN | ExtraMdiStyles,
				   0, 0, 0, 0, 
				   hEContext, (HMENU)0xCAC, 
				   AppImpInst -> Handle(),
				   (pchar)&clientcreate);

	AppImpInst -> ContextList()	-> Insert ((HANDLE)hEContext, this );
											   // * 1.9 end *		
	ShowWindow(hwndClient, SW_SHOW);
	InitSize();

	MDICREATESTRUCT mdicreate;
	mdicreate.szClass = GetRegClassString(Rcs_MdiDefChild);
	mdicreate.szTitle = StaticPtr(" ");
	mdicreate.hOwner = CV_RunTime :: App_hApp(AppImpInst);
	mdicreate.x =  mdicreate.y =  mdicreate.cx = mdicreate.cy = 0;
	mdicreate.style = 0; //WS_DISABLED;
	mdicreate.lParam = 0;

	hDefChild = (HWND)SendMessage ( hwndClient, WM_MDICREATE, 0, 
					(long)&mdicreate);
	SetWindowPos(hDefChild, HWND_BOTTOM, 0,0,0,0,SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);

	CV_ASSERT(hDefChild);
	SendMessage(hwndClient, WM_MDICASCADE, 0, 0);
}

void ShellWind_Imp :: Show( ShowState s )
{
if (hwndClient && !IsWindowVisible(hwndClient)) 
	ShowWindow(hwndClient, SW_RESTORE);
	AWind_Imp ::Show(s);
}

void ShellWind_Imp :: Hide(  )
{
if (hwndClient) 
	ShowWindow(hwndClient, 0);
	AWind_Imp :: Hide();
}


void ShellWind_Imp :: Arrange ( int s )
{
	switch (s)
	{
		case (int)ShellWindow::Icons:
			SendMessage(hwndClient,WM_MDIICONARRANGE, 0, 0); 
			break;

		case (int)ShellWindow::Cascade:
			if (IsWin31())
				SendMessage(hwndClient, WM_MDICASCADE, MDITILE_SKIPDISABLED, 0);
			else
				SendMessage(hwndClient, WM_MDICASCADE, 0, 0);
			break;

		case (int)ShellWindow::Tile:
			if (IsWin31())
				SendMessage(hwndClient, WM_MDITILE, MDITILE_SKIPDISABLED, 0);
			else
				SendMessage(hwndClient, WM_MDITILE, 0, 0);
			break;
// added: #HK930214 -----------------------------------------------------------
		case (int)ShellWindow::TileHorz:
			if (IsWin31())
				SendMessage(hwndClient, WM_MDITILE, MDITILE_SKIPDISABLED|MDITILE_HORIZONTAL, 0);
			else
				SendMessage(hwndClient, WM_MDITILE, 0x0, 0);
			break;
			
		case (int)ShellWindow::TileVert:
			if (IsWin31())
				SendMessage(hwndClient, WM_MDITILE, MDITILE_SKIPDISABLED|MDITILE_VERTICAL, 0);
			else
				SendMessage(hwndClient, WM_MDITILE, 0x0, 0);
			break;
// ----------------------------------------------------------------------------
	}
}

void ShellWind_Imp :: AssociateAccel(BOOL set)
{
	if (set) {
	DocWind_Imp* dwi;
	HWND hActive = (HWND)(UINT)SendMessage (hwndClient,WM_MDIGETACTIVE, 0, 0);

		if ((dwi = (DocWind_Imp*)List_of_ChildDocs.Find((HANDLE)hActive)) && (dwi -> GetAccel()))
			dwi -> AssociateAccel(set);
		else
			Wind_Imp :: AssociateAccel(set);
	}
	else
		Wind_Imp :: AssociateAccel(set);
}

void ShellWind_Imp :: AssociateMenu (BOOL ViaPost)
{
	if (!Sf_UsingChildMenu) {
	uint menupos = WndMenu ? CV_RunTime :: Menu_autopos(WndMenu) : 0;
	HMENU	MenuHandle;  

		if (WndMenu) {
			MenuHandle = CV_RunTime :: Menu_hMenu ( WndMenu );
			Sf_UsingOwnMenu = 1;
			Sf_UsingDefMenu = 0;
		}
		else {
			MenuHandle = tmpMenu;
			Sf_UsingOwnMenu = 0;
			Sf_UsingDefMenu = 1;
		}

		if (ViaPost) {
#if !defined(WIN32)
			PostMessage (hEContext, WM_COMMAND, ID_MDISETMENU, 
				MAKELONG(MenuHandle, GetSubMenu (MenuHandle,menupos)));
#else
			PostMessage (hEContext, WM_MYMDISETMENU, 
				(WPARAM)MenuHandle, (LPARAM)GetSubMenu (MenuHandle, menupos));
#endif
		} else {
#if !defined(WIN32)
			SendMessage(hwndClient, WM_MDISETMENU, 0, 
					MAKELONG(MenuHandle, GetSubMenu(MenuHandle,menupos)));
#else
			SendMessage(hwndClient, WM_MDISETMENU, 
					(WPARAM)MenuHandle, (LPARAM)GetSubMenu(MenuHandle,menupos));
#endif
			DrawMenuBar(hEContext);
		}
	}
}

void ShellWind_Imp :: UseChildMenu(Menu* newMenu, BOOL ViaPost)
{
	if (newMenu) {
		Sf_UsingChildMenu = 1;
		Sf_UsingOwnMenu = 0;
		Sf_UsingDefMenu = 0;

	uint menupos = CV_RunTime :: Menu_autopos(newMenu);
	HMENU	MenuHandle = CV_RunTime :: Menu_hMenu ( newMenu );
	
		if (ViaPost) {
#if !defined(WIN32)
			PostMessage (hEContext, WM_COMMAND, ID_MDISETMENU, 
				MAKELONG(MenuHandle, GetSubMenu (MenuHandle,menupos)));
#else
			PostMessage (hEContext, WM_MYMDISETMENU, 
				(WPARAM)MenuHandle, (LPARAM)GetSubMenu (MenuHandle, menupos));
#endif
		} else {
#if !defined(WIN32)
			SendMessage(hwndClient, WM_MDISETMENU, 0, 
					MAKELONG(MenuHandle, GetSubMenu(MenuHandle,menupos)));
#else
			SendMessage(hwndClient, WM_MDISETMENU, 
					(WPARAM)MenuHandle, (LPARAM)GetSubMenu(MenuHandle,menupos));
#endif
			DrawMenuBar(hEContext);
		}
	}
	else {
		if (Sf_UsingChildMenu)
			{
			Sf_UsingChildMenu = 0;
			AssociateMenu(ViaPost);
			}
		}
}

long	ShellWind_Imp :: Dispatch(Event e)
{
long retval = 0;
long *oldptr = CV_RunTime :: EC_pRetval(this);

	CV_RunTime :: EC_SetpRetval(this, &retval);

	switch	(CV_RunTime :: Event_wMsg (e)) {
	case WM_MENUCHAR:
		// Pass back to default to allow MDI subsytem deal with
		// special SysMenu options
		{
		Default(e);
		break;
		}

	case WM_MENUSELECT:
	case WM_INITMENU:
 	case WM_INITMENUPOPUP:
		{
		HWND hwndChild;
		
			SetMenuHandler(false); 
			if ((hwndChild = (HWND)(UINT)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0))
						&& IsWindow(hwndChild) 
						&& List_of_ChildDocs.Find((HANDLE)hwndChild))
				{
				SetMenuHandler(true); // Assume child will handle menu
				SendMessage(hwndChild, CV_RunTime :: Event_wMsg (e), 
							CV_RunTime :: Event_wParam (e),
							CV_RunTime :: Event_lParam (e));
				}
			if (!Sf_HasHandledMenu)
				AWind_Imp :: Dispatch (e);
			}
		break;

	case WM_COMMAND:
#if !defined(WIN32)
	{
	/*
         * If the WM_COMMAND is not a help message (id < 0xFFFD)
         * and not a WINDOW menu option (id >= MDI_FIRSTCHILDID)
         * process it. 
         */
		if ((((uint)CV_RunTime :: Event_wParam(e)) >= MdiFirstChildID) &&
                    (((uint)CV_RunTime :: Event_wParam(e)) < ID_FIRSTSYSTEMID))
			Default(e);

		else if (CV_RunTime :: Event_wParam (e) == ID_MDISETMENU)
		{
			if (IsWin31())
			{
			// Under Windows 3.1 perform verification of Menus
			HMENU hMenu1, hMenu2;

				hMenu1 = (HMENU)CV_RunTime :: Event_lParam (e);
				hMenu2 = (HMENU)((CV_RunTime :: Event_lParam (e) & 0xffff0000) >> 16);
				if ((!hMenu1 || IsMenu(hMenu1)) && (!hMenu2 || IsMenu(hMenu2)))
				{
					SendMessage (hwndClient, WM_MDISETMENU, 0, CV_RunTime :: Event_lParam (e));
					DrawMenuBar (hEContext);
				}
			}
			else {
				SendMessage (hwndClient, WM_MDISETMENU, 0, CV_RunTime :: Event_lParam (e));
				DrawMenuBar (hEContext);
			}
			retval= 0;
			break;
		}
		else {
			if ((! CV_RunTime :: Event_lParam ( e )) ||	// Menu * 0.8 *
			    ( CV_RunTime :: Event_lParam ( e ) == 0x00010000L )) // Accel * 0.8 *
			{
				if (!WindMgt.HelpOn || !HelpFilter(e))
				{
				HWND hwndChild;

					if ((CV_RunTime::Event_wParam (e) & SYSMENU_Mask) == SYSMENU_Mask)
						((pDW)pRequestor) -> _Default ( e );
				else {
					SetMenuHandler(false);
					if ((hwndChild = (HWND)(UINT)SendMessage (hwndClient,WM_MDIGETACTIVE, 0, 0))
					    && IsWindow(hwndChild) 
					    && List_of_ChildDocs.Find((HANDLE)hwndChild))
					{
						SetMenuHandler(true); // Assume child will handle menu
						SendMessage(hwndChild, WM_COMMAND, 
								CV_RunTime :: Event_wParam (e),
								CV_RunTime :: Event_lParam (e));

					}
					if (!Sf_HasHandledMenu)	{
						Report(this, CVEVT_MenuCommand, e );
						((pDW)pRequestor) -> _MenuCommand ((MenuCommandEvt&)e );
					}
				}
			}
		}
		else
			retval = AWind_Imp :: Dispatch (e);
		}
		break;
	}
#else
	{
	/*
         * If the WM_COMMAND is not a help message (id < 0xFFFD)
         * and not a WINDOW menu option (id >= MDI_FIRSTCHILDID)
         * process it. 
         */
	 WORD wl = LOWORD(CV_RunTime :: Event_wParam(e));
	 WORD wh = HIWORD(CV_RunTime :: Event_wParam(e));

		if (((uint)wl >= MdiFirstChildID) && ((uint)wl < ID_FIRSTSYSTEMID))
			Default(e);
		else {
			if ((!CV_RunTime :: Event_lParam(e) && !wh) ||	// Menu * 0.8 *
			    (wh == 1)) // Accel * 0.8 *
			{
				if (!WindMgt.HelpOn || !HelpFilter (e))
				{
				HWND hwndChild;

					if ((wl & SYSMENU_Mask) == SYSMENU_Mask)
						((pDW)pRequestor) -> _Default (e);
				else {
					SetMenuHandler(false);
					if ((hwndChild = (HWND)(UINT)SendMessage (hwndClient, WM_MDIGETACTIVE, 0, 0))
					    && IsWindow(hwndChild) 
					    && List_of_ChildDocs.Find ((HANDLE)hwndChild))
					{
						SetMenuHandler(true); // Assume child will handle menu
						SendMessage(hwndChild, WM_COMMAND, 
								CV_RunTime :: Event_wParam (e),
								CV_RunTime :: Event_lParam (e));

					}
					if (!Sf_HasHandledMenu)	{
						Report(this, CVEVT_MenuCommand, e);
						((pDW)pRequestor) -> _MenuCommand ((MenuCommandEvt&)e);
					}
				}
			}
		}
		else
			retval = AWind_Imp :: Dispatch (e);
		}
		break;
	}

// Ersatz für WIN16: WM_COMMAND, ID_MDISETMENU
	case WM_MYMDISETMENU:
		{
		HMENU hMenu1, hMenu2;

			hMenu1 = (HMENU)CV_RunTime :: Event_wParam (e);
			hMenu2 = (HMENU)CV_RunTime :: Event_lParam (e);
	
			if (IsWin31())
			{
			// Under Windows 3.1 perform verification of Menus
				if ((!hMenu1 || IsMenu(hMenu1)) && (!hMenu2 || IsMenu(hMenu2)))
				{
					SendMessage (hwndClient, WM_MDISETMENU, (WPARAM)hMenu1, (LPARAM)hMenu2);
					DrawMenuBar (hEContext);
				}
			}
			else {
				SendMessage (hwndClient, WM_MDISETMENU, (WPARAM)hMenu1, (LPARAM)hMenu2);
				DrawMenuBar (hEContext);
			}
			retval= 0;
			break;
		}
		break;

#endif

	case WM_SIZE:
		{
			if ((CV_RunTime :: Event_wParam ( e ) == SIZEICONIC) ||
			    (CV_RunTime :: Event_wParam ( e ) == SIZEFULLSCREEN))
			{
				if (IsWindowVisible(hEContext)) {
					WndFlags |= WF_IS_SHOWN;
					WndFlags &= (~WF_MENU_CHANGED);
					
				/* **************************************** 
					If this is a top app window 
						if not opened 
							tag it open 
							increment the window count
				 ************************************************ */
					if(!WindMgt.Opened) {
						WindMgt.Opened = true;
					   	CV_RunTime :: App_WindowCount (_AppImpFind()) += 1;		
					}
				} 
			}

			Report(this, CVEVT_ReSize, e );
		    	((pDW)pRequestor) -> _ReSize ((ReSizeEvt&)e );
			Default(e);
		}
		break;

	case WM_SETFOCUS:
		retval = AWind_Imp :: Dispatch (e);
		Default(e);
		break;

	case WM_DESTROY:
		{
			if (WndFlags & WF_SYSMENU)
				EnableSysMenu(false);
			SetMenu(hEContext, 0);
			ReleaseCapture();
			WndFlags &= ( WF_IS_CHILD | WF_IS_DELETE);
		}
		break;

	case WM_ACTIVATE:
		{
		pApp_Imp AppImpInst = _AppImpFind();

			if (LOWORD(CV_RunTime::Event_wParam(e)))
				AppImpInst -> SetClient(hwndClient);
			else if (AppImpInst -> GetClient() == hwndClient)
					AppImpInst -> SetClient(0);
			retval = AWind_Imp :: Dispatch (e);
		break;
		}

	case WM_SETCURSOR:				
		HandlePointer (e, InCursorHelpMode(), 
			      ((HWND)CV_RunTime :: Event_wParam(e) == hwndClient));
		break;

	default:
		retval = AWind_Imp :: Dispatch (e);

	}
	CV_RunTime :: EC_SetpRetval(this, oldptr);
	return retval;
}

void	DocWind_Imp :: Hide()
{
bool bLastOpen = false;
CVLinked_List * SiblingList = ((ShellWind_Imp*)WndParent ) -> ChildDocList();

	if (SiblingList -> Find((HANDLE)hEContext))
			SiblingList -> Delete((HANDLE)hEContext);
	if (SiblingList -> First())
		SendMessage(hwndClient, WM_MDINEXT, 0 , 0);
	else {
		// Its the last "Open child document"
		bLastOpen = true;
		if (isZoomed())
			SendMessage(hwndClient, WM_MDIRESTORE, (WPARAM)hEContext, 0);
	}
	Wind_Imp :: Hide();

	CV_ASSERT(((ShellWind_Imp*)WndParent ) -> DefaultChild());

	if (bLastOpen && ((ShellWind_Imp*)WndParent ) -> DefaultChild()) {
		SendMessage(hwndClient, 
			    WM_MDIACTIVATE, 
			    (WPARAM)((ShellWind_Imp*)WndParent) -> DefaultChild(), 
			    0);
	}

	if (hEContext == (HWND)(UINT)SendMessage (hwndClient, WM_MDIGETACTIVE, 0, 0))
		((ShellWind_Imp*)WndParent) -> UseChildMenu(0);
}

void	ShellWind_Imp :: Default(Event e)
{
long ret = DefFrameProc	(hEContext, GetWindow(hEContext, GW_CHILD), // hwndClient, 
					CV_RunTime :: Event_wMsg ( e ),
					CV_RunTime :: Event_wParam ( e ),
					CV_RunTime :: Event_lParam ( e )
			);
	CV_RunTime :: EC_SetRetval(this,(long)ret);
}


ShellWind_Imp :: ~ShellWind_Imp (void)
{
	WindMgt.Anchoring = false;
	WindMgt.Destructor = true;

	if (hEContext) ShowWindow(hEContext, 0);

	if (AppWndVert) {
		delete (WndVertScrollBar *)AppWndVert;
		AppWndVert = 0;
	}
	if (AppWndHorz) {
		delete (WndHorzScrollBar *)AppWndHorz;
		AppWndHorz = 0;
	}

	ChangeMenu (NULL);
	if (hEContext && IsWindow (hEContext)) {
		if(WindMgt.Opened) {
		pApp_Imp AppImpInst = _AppImpFind();
		
			WindMgt.Opened = false;
				// tests if this is the last TopAppWindow
			CV_RunTime :: App_WindowCount( AppImpInst) -= 1;
			if (!CV_RunTime :: App_WindowCount(AppImpInst) && AppImpInst -> QuitOnLast())
				AppImpInst->Quit();
		}
		EvtEnd ();
		if (hDefChild && IsWindow(hDefChild) && IsWindow(hwndClient))
		SendMessage( hwndClient, WM_MDIDESTROY, (WPARAM)hDefChild, 0);
		if (tmpMenu)
			DestroyMenu(tmpMenu);
		::DestroyWindow (hEContext);
	}
	hEContext = 0;
	SetCaption ((pchar)0);
	CV_ASSERT(!(List_of_ChildDocs.First()));
}

DocWind_Imp :: DocWind_Imp (AppWindow *req, pWind_Imp parent, pAWind_Imp copy_from)
	     : AWind_Imp (req, copy_from)
{
	WindMgt.isMDIWindow = true;
	WndParent = parent;
	hwndClient = ((ShellWind_Imp*)WndParent) -> ClientWindow();

pApp_Imp AppImpInst = _AppImpFind();

	SetStyle (WS_CHILD  | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	WndFlags |= WF_IS_CHILD;
		
MDICREATESTRUCT mdicreate;

	mdicreate.szClass = GetRegClassString(Rcs_MdiChild);
	mdicreate.szTitle = StaticPtr (" ");
	mdicreate.hOwner = CV_RunTime :: App_hApp(AppImpInst);
	mdicreate.x =  CW_USEDEFAULT ;
	mdicreate.y =  CW_USEDEFAULT ;
	mdicreate.cx = CW_USEDEFAULT ;
	mdicreate.cy = CW_USEDEFAULT ;
	mdicreate.style = WndStyle | WS_BORDER; // WndStyle;
	mdicreate.lParam = 0;

	hEContext = (HWND)SendMessage (hwndClient, WM_MDICREATE, 0, 
					(long)&mdicreate);
	ShowWindow(hEContext,false);

	if (!IsWin31())
		SetWindowLong (hEContext, GWL_WNDPROC, (long)CvMdiChildDispatcher);

	AppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
	InitSize();
}

void DocWind_Imp :: AssociateAccel (BOOL set)
{
	if (set && WndAccel)
		_AppImpFind() -> SetAccelWind( WndAccel -> Handle(), WndParent -> Handle());
	else {
		if (WndParent -> GetAccel())
			_AppImpFind() -> SetAccelWind( WndParent -> GetAccel() -> Handle(),WndParent -> Handle());
		else
			_AppImpFind() -> SetAccelWind( 0,0);
	}
}

void DocWind_Imp :: AssociateMenu (BOOL ViaPost)
{
	if (WndParent && (hEContext == (HWND)(UINT)SendMessage (hwndClient,WM_MDIGETACTIVE, 0, 0)))
	{
		if (IsWindowVisible(hEContext) || isZoomed())
			((ShellWind_Imp*)WndParent) -> UseChildMenu (WndMenu, ViaPost);
		else
			((ShellWind_Imp*)WndParent) -> UseChildMenu (0, ViaPost);
	}
}

long DocWind_Imp :: Dispatch (Event e)
{
long retval = 0;
long * oldptr = CV_RunTime :: EC_pRetval(this);

	CV_RunTime :: EC_SetpRetval(this, &retval);

	switch	(CV_RunTime :: Event_wMsg (e)) {
	case WM_MENUCHAR:
	// Pass back to default to allow MDI subsytem deal with
	// special SysMenu options
		Default (e);
		break;

	case WM_SETCURSOR:				
		{
		bool bHelp = (InCursorHelpMode() || WndParent -> InCursorHelpMode());
		
			HandlePointer (e,bHelp);
		}
		break;

	case WM_CVHELP:
		Report(this, CVEVT_Help, e );
		EnableHelpCursor(false);
		WndParent -> EnableHelpCursor(false);
		((pDW)pRequestor) -> _HelpRequest ( (HelpRequestEvt&)e );
		break;

	case WM_NCACTIVATE:
		if (CV_RunTime :: Event_wParam (e)) {
			AssociateMenu (true);
			AssociateAccel (true);
		} else
			AssociateAccel (false);
		retval = AWind_Imp :: Dispatch (e);
		break;

	case WM_MDIACTIVATE:
		{
#if !defined(WIN32)
		bool fActivated = CV_RunTime :: Event_wParam(e);
#else
		bool fActivated = (HWND)CV_RunTime :: Event_wParam(e) == hEContext;
#endif

			if (fActivated)
			{
				AssociateMenu(true);
				AssociateAccel(true);
			}
			else {
				if ((!(HWND)CV_RunTime :: Event_lParam(e)) ||
				    ((HWND)CV_RunTime :: Event_lParam(e) == ((ShellWind_Imp*)WndParent)  -> DefaultChild()))
				{
					((ShellWind_Imp*)WndParent ) -> UseChildMenu(0, true);
					WndParent  -> AssociateAccel(true);
				}
			}


			if (fActivated) {
				Report(this, CVEVT_Activate, e);
			 	((pDW)pRequestor) -> _Activate (e);
			}
			else {
				Report(this, CVEVT_DeActivate, e);
				((pDW)pRequestor) -> _DeActivate (e);
			}
			retval = 0;
		}
		break;

	case WM_DESTROY:				
		ReleaseCapture();
		WndFlags &= ( WF_IS_CHILD | WF_IS_DELETE);
		break;					

	case WM_SETFOCUS:
		retval = AWind_Imp :: Dispatch (e);
		Default(e);
		break;

	case WM_SIZE:
		if (( CV_RunTime :: Event_wParam (e) == SIZEICONIC ) ||
		( CV_RunTime :: Event_wParam (e) == SIZEFULLSCREEN))
		{
			if (IsWindowVisible (hEContext)) {
				WndFlags |= WF_IS_SHOWN;
				WndFlags &= (~WF_MENU_CHANGED);
			} 
		}

		CV_RunTime :: AppWindow_MoveKids(this);
		Report (this, CVEVT_ReSize, e);
		((pDW)pRequestor) -> _ReSize ((ReSizeEvt&)e );
		Default (e);
		break;


	case WM_MOVE:
		retval = AWind_Imp :: Dispatch (e);
		Default (e);
		break;

	default:
		retval = AWind_Imp :: Dispatch (e);
	}
	CV_RunTime :: EC_SetpRetval(this, oldptr);
	return retval;
}

void	DocWind_Imp :: Default (Event e)
{
long ret = DefMDIChildProc (hEContext,  CV_RunTime :: Event_wMsg (e),
					CV_RunTime :: Event_wParam (e),
					CV_RunTime :: Event_lParam (e)
			);
	CV_RunTime :: EC_SetRetval(this, (long)ret);
}



void DocWind_Imp :: Show (ShowState s)
{
HWND current = (HWND)(UINT)(SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0));

	if ((current == hEContext) && !IsWindowVisible(hEContext) && WndMenu) {
	// Show after a hide 

		AWind_Imp :: Show(s);
		((ShellWind_Imp*)WndParent) -> UseChildMenu (WndMenu);
	} else
		AWind_Imp :: Show(s);

	CVLinked_List * SiblingList = ((ShellWind_Imp*)WndParent ) -> ChildDocList();
	if (!SiblingList -> Find((HANDLE)hEContext))
		SiblingList -> Insert((HANDLE)hEContext, (void*)this);

  	SendMessage (hwndClient, WM_MDIACTIVATE, (WPARAM)hEContext, 0 );
}

void DocWind_Imp::MenuHandler(MhType, Event)
{
// The default procedure is to give the event to the parent
	((ShellWind_Imp*)WndParent) -> SetMenuHandler(false);
}

BOOL ShellWind_Imp :: CloseHandler(CloseStyle cs, Event e)
{
	if ((cs == ChCloseAndTidy) || (cs == ChClose)) {
	CVLink * current;
	
		List_of_ChildDocs.LockOrder(true);

		while (current =List_of_ChildDocs.First()) {
		DocWind_Imp* dwi = (DocWind_Imp *)(current -> Item());
		
			SendMessage (dwi -> Handle(), WM_ENDSESSION, true, 0L);
			current = List_of_ChildDocs. Next();
		}
		List_of_ChildDocs.LockOrder(false);
		return  AWind_Imp :: CloseHandler (cs, e);
	}
	else if (cs == ChQuery) {
		List_of_ChildDocs.LockOrder(true);
	
	CVLink * current = List_of_ChildDocs.First();

		while (current)	{
		DocWind_Imp* dwi = (DocWind_Imp *)(current -> Item());
		
			if (!SendMessage (dwi -> Handle(), WM_QUERYENDSESSION, 0, 0L)) {
				List_of_ChildDocs.LockOrder(false);
				return false;
			}
			current = List_of_ChildDocs. Next();
		}
		return AWind_Imp :: CloseHandler(ChQuery, e);
	}
	return true;
}

BOOL DocWind_Imp :: CloseHandler(CloseStyle cs, Event e)
{
	if ((cs == ChCloseAndTidy) || (cs == ChClose)) {
		Report(this, CVEVT_Close, e);
		((pDW)pRequestor) -> _Close (e);

		Enable(false);
		Hide();
		SetWindowPos(hEContext, HWND_BOTTOM, 0,0,0,0,SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
		ShowOwnedPopups(Handle(), 0);
		return true;
	} else
		return AWind_Imp:: CloseHandler(cs, e);
}



DocWind_Imp :: ~DocWind_Imp()
{
	if (WndMenu)
		ChangeMenu(0);

	WindMgt.Anchoring = false;
	WindMgt.Destructor = true;

	if (AppWndVert) {
		delete (WndVertScrollBar *)AppWndVert;
		AppWndVert = 0;
	}
	if (AppWndHorz) {
		delete (WndHorzScrollBar *)AppWndHorz;
		AppWndHorz = 0;
	}
	EnableSysMenu(false);
	EvtEnd ();

	CV_ASSERT(IsWindow(hwndClient));

HWND htmp = hEContext;

	SendMessage (hwndClient, WM_MDIDESTROY, (WPARAM)hEContext, 0);

// If child still in parents child list
CVLinked_List * SiblingList = ((ShellWind_Imp*)WndParent) -> ChildDocList();

	if (SiblingList -> Find ((HANDLE)htmp))
		SiblingList -> Delete ((HANDLE)htmp);

	hEContext = 0;
}

//	MDI children are created by the sending the message WM_MDICREATE
//	to the client window.  This, however causes the window to be shown
//	immediately.  To stop this occuring it is necessary to use this window
//	procedure as the window is being created and then replace it with the
//	standard CA-CommonView window procedure EventDispatcher.

LRESULT WINAPI _DISPATCH_ENTRY
MDIChildDispatcher	( HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam )
{
	CV_ASSERT_DLLDS();
	
	switch (ecMsg)
	{
	case WM_CREATE:
	case WM_NCCREATE:
		{
		CREATESTRUCT * cs = (CREATESTRUCT *)lParam;
		cs -> style &= 0xEFFFFFFFL;
		((MDICREATESTRUCT*)(cs -> lpCreateParams)) -> style &= 0xEFFFFFFFL;
		long myStyle;
		myStyle = GetWindowLong (hEContext, GWL_STYLE);
		SetWindowLong(hEContext, GWL_STYLE, myStyle & 0xEFFFFFFFl);
		return DefMDIChildProc	(	hEContext, ecMsg, wParam, lParam);
		}
	
	case WM_SHOWWINDOW:
		{
		wParam = 0;
		long myStyle;
		myStyle = GetWindowLong(hEContext, GWL_STYLE);
		SetWindowLong(hEContext, GWL_STYLE, myStyle & 0xEFFFFFFFl);
		return DefMDIChildProc	(	hEContext, ecMsg, wParam, lParam);
		}

	case WM_NCPAINT:
	case WM_NCACTIVATE:
	default:
		{
		long myStyle;
		myStyle = GetWindowLong(hEContext, GWL_STYLE);
		SetWindowLong(hEContext, GWL_STYLE, myStyle & 0xEFFFFFFFl);
		return DefMDIChildProc	(	hEContext, ecMsg, wParam, lParam);
		}
	}
}


LRESULT WINAPI _DISPATCH_ENTRY
MdiDefChildDispatcher	(HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam )
{
	CV_ASSERT_DLLDS();
	return DefMDIChildProc	(hEContext, ecMsg, wParam, lParam);
}


