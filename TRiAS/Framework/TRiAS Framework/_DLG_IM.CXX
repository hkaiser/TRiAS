/* $Header:   G:/cv.win/pvcs/commonvu/src/_dlg_im.cxv   3.0.1.0   14 Jul 1992 11:49:14   RONAN  $
 *
 *	_ d i a l o g . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1	ferg	02nov88	moved DialogWindow::Create and DialogWindow::ctor to
 *						here from dialog.cxx.
 *	0.2	rs		16nov88	ferg from rs 26oct88. added Dialog::Dispatch.
 *	0.3 ferg 	18nov88	EventContext::Create is now private.
 *	0.4 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.5 jk		02dec88	Fast Compile defines added.
 *  0.6 rs      09jan89 Change to stop ids being modified
 *  0.7 rs      23jan89 Additions for Dialog handling of WM_PAINT
 *  0.8 rs      24feb89 Due to mapping  considerations it was necessary to
 *                      amalgamate references to a parent window for child
 *                      and dialog windows into a WndParent pointer in the general
 *                      Window class and change uses of ChildWindow, etc to
 *                      reflect this.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	 1.2	rs		23aug89	The Close event handler is not being called for 
 *								DialogWindows ( as WM_CLOSE is not being generated)
 *	 1.3	rs		23aug89	Debugging info
 *	 1.4 	rs		24Nov89	Long -> Void event handlers
 *	 1.5	rs		18Dec89	return true after WindowInit to set focus to 
 *							default push buttons.
 *	 1.6	rs		??jan90 Simulation of DialogWindows using ModelessDialogs.
 *							This paves the way for creation of windows in
 *							constructors.
 *							Much of modeless dialog behaviour has moved back 
 *							into DialogWindow.
 *
 *	 1.7 	rs		05feb90	Creation of windows in constructor
 *							and destruction in destructor.
 *							This simplifies the implementation of show.
 *							Use of App_LastDlgHandle to initialise handle.
 *							Need for WindowInit is removed due to new 
 *							window opening sequence - see dispatch.cxx
 *							Removed Close and QueryClose.
 *
 *	1.8		rs,hl 	20feb90	Need to reverse sense of QueryClose result for 
 *							DialogWindows WM_QUERYENDSESSION message.
 *	1.9 	rs		27feb90	initialise window size after creation.
 *	1.10	rs		28feb90	prevent active window changing during creation
 *							of dialogs. 
 *	1.11 	RS		28feb90 Need to set focus to default push button before
 *							you show it.
 *	1.12	hl		05apr90 DialogWindow::EndDlg only enables the parent if it is
 *						a modal DialogBox
 *
 */

#include "tfrmpre.hxX"
#include	<_Link.hxx>   

#define SYSTEM_FONT	    13  // testing only

/* 0.5 End */

#if !defined(WIN32)
extern "C" BOOL _pascal _loadds SetChildFontProc ( HWND hwnd, unsigned long lParam);
extern "C" BOOL _pascal _loadds ShowControlProc ( HWND hWnd, unsigned long lParam) ;
inline int abs(int x) { return (x < 0) ? (-x) : (x); }
#else
extern "C" BOOL WINAPI SetChildFontProc (HWND hwnd, unsigned long lParam);
extern "C" BOOL WINAPI ShowControlProc (HWND hWnd, unsigned long lParam) ;
#endif

typedef struct	{
    HFONT hFont;       // handle to the new font
    HWND hDlg; 			// Window handle of dialog box
    uint Xbase;       	// original base X
    uint Ybase;       	// original base Y
    uint fontX;		    // font width
    uint fontY;		    // font height
} DIALOG_VARS;


DWind_Imp::  DWind_Imp	(DialogWindow * req, pWind_Imp parent, ResID RscID, BOOL isModal )	// * 1.7 begin *
: Wind_Imp(req), dialogID ((uint)RscID)
{
char buffer[80];
long lDBUnits;
pApp_Imp AppImpInst = _AppImpFind();

	pActiveContext = 0;
	WndParent = parent;               // * 0.8 *
	result = 0;
	hModeless = 0;
	m_poldProc = NULL;
	m_hWndLast = NULL;

	WindMgt.isModal = (isModal) ? true : false;
	DlgFlags.IsShown = false;
	DlgFlags.fParentsDisabled = false;

	hModeless = CreateDialogParam(
		CV_RunTime::ResID_handle (RscID, AppImpInst, RT_DIALOG),
		(char *)((ulong)((uint)dialogID)),
		(WndParent ? (CV_RunTime::Handle(WndParent)) : 0),
		(DLGPROC)DialogDispatcher, (unsigned long)this
	);
	CV_ASSERT_VALID(hModeless);

	hEContext = CV_RunTime::App_LastDlgHandle (AppImpInst);
	CV_ASSERT_VALID (hEContext);

	CV_RunTime::App_LastDlgHandle (AppImpInst) = 0;

	if (GetWindowText(hEContext, buffer,79))
	{
		buffer[79] = '\0';
		SetCaption(buffer);
	}

	AppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);
	InitSize();

Rectangle r ;

	GetClientRect (hEContext, (RECT *)&r);

//	int width  = r.Right() - r.Left();
//  int height = r.Bottom() - r.Top() ;

	lDBUnits = GetDialogBaseUnits();
	Xbase = LoWord(lDBUnits) ;
	Ybase = HiWord(lDBUnits) ;

	Xchars = r.Right()/Xbase;
	Ychars = r.Bottom()/Ybase;
}	// End of "DWind_Imp" CONSTRUCTOR
														// * 0.1 End *
DWind_Imp ::  DWind_Imp (DialogWindow * req)  : Wind_Imp(req), dialogID((uint)0)
{
	pActiveContext = 0;
	result = 0;
	WndParent = 0;
	hModeless = 0;
	m_poldProc = NULL;

	WindMgt.isModal = false;
	DlgFlags.IsShown = false;
	DlgFlags.fParentsDisabled = false;
}


void DWind_Imp::  Default (Event e)
{
// #HK960809: für PropertySheets
	if (NULL != m_poldProc) {
		CV_RunTime :: EC_SetRetval(this, 
			CallWindowProc(m_poldProc, CV_RunTime :: Handle (this),
						CV_RunTime :: Event_wMsg (e),
						CV_RunTime :: Event_wParam (e),
						CV_RunTime :: Event_lParam (e)
					));
	} else
		CV_RunTime::EC_SetRetval(this, 0L);			// * 1.4 *
}	// End of "DWind_Imp" FUNCTION "Default"


void DWind_Imp :: EndDlg (int nResult)		// * 1.6 start *
{
	result = nResult;

	if (hModeless && hEContext) {
		if (WindMgt.isModal) {
			if (DlgFlags.IsShown && IsWindow (hEContext)) {
			HWND hp = hEContext;

				DlgFlags.IsShown = false;
			
				if(WndParent) {
					if (WndParent -> WindMgt.isPropPage) {
					HWND hpParent = ::GetParent(hp);

						CV_ASSERT(::IsWindow(hpParent));
						EnableWindow (hpParent, true);

					pWind_Imp pW = WndParent -> WndParent;

						if (pW && pW -> WindMgt.isModal) {
							CV_ASSERT(::IsWindow(::GetParent(hpParent)));
							EnableWindow (::GetParent(hpParent), true);
						} else if (DlgFlags.fParentsDisabled) {
							while (hpParent = ::GetParent(hpParent)) {
								if (NULL != m_hWndLast && hpParent == m_hWndLast)
									break;
								EnableWindow(hpParent, true);
							}
						}
					} 
					else if (WndParent -> WindMgt.isModal) {
						EnableWindow (::GetParent(hp), true);
					} 
					else if (DlgFlags.fParentsDisabled) {
						while (hp = ::GetParent(hp)) {
							if (NULL != m_hWndLast && hp == m_hWndLast)
								break;
							EnableWindow(hp, true);
						}
					}
				} 
				else if (DlgFlags.fParentsDisabled) {
					while (hp = ::GetParent(hp)) {
						if (NULL != m_hWndLast && hp == m_hWndLast)
							break;
						EnableWindow(hp, true);
					}
				}
				m_hWndLast = NULL;
																// * 1.12 end *
				if (IsWindow (hModeless))
					ShowWindow (hModeless, SW_HIDE);	

				if (pActiveContext) {
				// setzt das Flag zurück, welches MessageSchleife am Leben hält 
					(*pActiveContext) = false;
					pActiveContext = 0; 
				}
			}
		}
		else if (IsWindow (hModeless))
			ShowWindow (hModeless, SW_HIDE);

	// Fenster zerlegen
//		DestroyWindow();
//		CV_ASSERT(NULL == hEContext);
//		hModeless = 0;
//		WindMgt.isModal = false;
	}												// * 1.6 end *
}	// End of "DWind_Imp" FUNCTION "EndDlg"

														// * 0.2 Begin *
long DWind_Imp :: Dispatch (Event e)
{
long retval = true;
long *oldptr = CV_RunTime::EC_pRetval(this);

	CV_RunTime::EC_SetpRetval(this, &retval);

	switch (CV_RunTime::Event_wMsg (e)) {
	case WM_PAINT:  // * 0.7 * start
		{
			PaintStruct	ps;
			if (GetUpdateRect(hEContext, (RECT *)&ps.rcPaint, ps.fErase = false))
			{
			DefWindowProc	(	hEContext,
								CV_RunTime::Event_wMsg ( e ),
								CV_RunTime::Event_wParam ( e ),
								CV_RunTime::Event_lParam ( e )
							);

			PaintInfo = (void*) &ps;
			Report(this, CVEVT_Expose, e );
			((pDW)pRequestor) -> _Expose ((ExposeEvt&)e );
			}
			PaintInfo = 0;

			retval = true;
		}	
		break; // * 0.7 * end

	case WM_COMMAND:
#if !defined(WIN32)
	{
		if ((!CV_RunTime::Event_lParam (e)) &&	// Is it a key button event ?
		    (GetDlgItem (hEContext,CV_RunTime::Event_wParam(e)) ||
		     (CV_RunTime::Event_wParam(e) == 1) ||
		     (CV_RunTime::Event_wParam(e) == 2))) 
		{
		// Set up handle for control button
            
			((HWND *)( &CV_RunTime::Event_lParam(e)))[0] =
				GetDlgItem (hEContext,CV_RunTime::Event_wParam(e));

		// Set up notification code
			((int *)( &CV_RunTime::Event_lParam (e)))[1] = BN_CLICKED;

			Report(this, CVEVT_ButtonClick, e );
			((pDW)pRequestor) -> _ButtonClick ( (ControlEvt&)e );
		}
		else if	( (!CV_RunTime::Event_lParam (e)) ||	// Menu * 0.8 *
			  (CV_RunTime::Event_lParam (e) == 0x00010000L)) // Accel * 0.8 *
		{
			if ((WindMgt.HelpOn) && ((CV_RunTime::Event_wParam(e)) >=  ID_CVHELPOFF))
			{
				if ((CV_RunTime::Event_wParam(e) ==  ID_CVHELP) ||
				    (CV_RunTime::Event_wParam(e) ==  ID_CVHELPON))
				{
				HWND h;
						
					if (IsChild(hEContext, h = GetFocus()) || (h == hEContext))
						ProcessHelpCursor (h, HTNOWHERE);
				}
			}
			else
	        		Wind_Imp::Dispatch( e);
		}
		else
			Wind_Imp::Dispatch( e);
	}
#else
	{
	WORD wl = LOWORD(CV_RunTime::Event_wParam(e));
	WORD wh = HIWORD(CV_RunTime::Event_wParam(e));

		if ((!CV_RunTime::Event_lParam(e) && !wh) &&	// Is it a key button event ?
		    (GetDlgItem (hEContext, wl) || (wl == 1) || (wl == 2))) 
		{
		// Set up handle for control button
			CV_RunTime::Event_lParam(e) = (LPARAM)GetDlgItem (hEContext, wl);

		// Set up notification code
			CV_RunTime::Event_wParam(e) = MAKELONG (wl, BN_CLICKED);

			Report(this, CVEVT_ButtonClick, e);
			((pDW)pRequestor) -> _ButtonClick ( (ControlEvt&)e );
		}
		else if	( (!CV_RunTime::Event_lParam(e) && !wh) ||	// Menu * 0.8 *
			  (wh == 1)) // Accel * 0.8 *
		{
			if ((WindMgt.HelpOn) && (wl >=  ID_CVHELPOFF))
			{
				if ((wl ==  ID_CVHELP) || (wl ==  ID_CVHELPON))
				{
				HWND h;
						
					if (IsChild (hEContext, h = GetFocus()) || (h == hEContext))
						ProcessHelpCursor (h, HTNOWHERE);
				}
			}
			else
	        		Wind_Imp::Dispatch (e);
		}
		else
			Wind_Imp::Dispatch (e);
	}
#endif
	break;

	case WM_DESTROY:
		{
			if (!(GetWindowLong (hEContext, GWL_STYLE) & WS_CHILD))
				SetMenu (hEContext, 0);
			ReleaseCapture();
			WndFlags &= (WF_IS_CHILD | WF_IS_DELETE);
			retval = true;
		}
		break;

	case WM_ACTIVATE:
		{
		pApp_Imp AppImpInst = _AppImpFind();

			if (LOWORD(CV_RunTime::Event_wParam(e)))
				AppImpInst -> SetActiveDialog(hModeless);
			else if (AppImpInst -> GetActiveDialog() == hModeless)
				AppImpInst -> SetActiveDialog(0);
			Wind_Imp :: Dispatch (e);
		}
		break;

	case WM_QUERYENDSESSION:		// * 1.8 *
		retval = !CloseHandler (ChQuery, e);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
		// 
		// Normally the handling of the key down message tests for WM_CHAR
		// and if there is a WM_CHAR message on the queue, CA-CommonView will 
		// defer generating KeyDown events until the arrival of the WM_CHAR message
		// However the Dialog Function filters this out so we must generate the
		// KeyDown on the WM_KEYDOWN event.
		//
			Report (this, CVEVT_KeyDown, e);
			((pDW)pRequestor) -> _KeyDown ((KeyEvt &)e);	
			retval = true;
		}
		break;

// #HK950307
	case WM_CANCELMODE:	// Parentfenster muá das sehen
		{
			if (WndParent && WndParent -> hEContext) 
				SendMessage (WndParent -> hEContext, 
					     WM_CANCELMODE,
					     CV_RunTime::Event_wParam(e),
					     CV_RunTime::Event_lParam(e));
			retval = false;
		}
		break;

	default:
		Wind_Imp::Dispatch( e);
	}

	CV_RunTime::EC_SetpRetval(this, oldptr);

return retval;
}	// End of "DWind_Imp" FUNCTION "Dispatch"
														// * 0.2 End *

int	DWind_Imp ::  Result () 
{ 
	return result; 
}

DWind_Imp::  ~DWind_Imp()					
{
	EndDlg(0);

	if (IsWindow(hEContext)) {
		::DestroyWindow(hEContext);
		hModeless = 0;
		WindMgt.isModal = false;
	}
	SetCaption((const char*)0);
}													

_TF_ENTRY32 void CentreWindow (HWND hWndP, HWND hWnd);

void	DWind_Imp::  Show	(ShowState s)	// * 1.6, 1.7 Start *
{
pApp_Imp AppImpInst = _AppImpFind();
	
	if (!WindMgt.Initialised)
        	Initialise();
	result = 0;	//Re-initialise result before each showing;

	CV_ASSERT_VALID(hEContext);
	if (IsWindow(hEContext)) {
		if (CV_RunTime::Window_Capt(this))	// * 1.26 *
	   		SetWindowText (hEContext, CV_RunTime::Window_Capt(this));

		if ((ShowState)(s & SHOWSTATE_STATE) == Centre) 
			CentreWindow (::GetParent(hModeless), hModeless);

		if (s & NoActivate)
			ShowWindow (hModeless, SW_SHOWNOACTIVATE);
		else
			ShowWindow (hModeless, SW_SHOW);

		AppImpInst -> SetActiveDialog(hModeless);
		UpdateWindow (hModeless);			// #HK970215

		if (WindMgt.isModal && (!DlgFlags.IsShown))
		{
		HWND h = GetFocus();

			if (!h || !((h == hModeless) || IsChild(hModeless, h)))
				::SetFocus(hModeless);

		HWND hp = hEContext;

			DlgFlags.IsShown = true;
			if (!(s & NoParentDisabling)) {
				while (hp = ::GetParent(hp)) {
					if (IsWindowEnabled(hp))
						EnableWindow(hp, 0);
					else
						m_hWndLast = hp;
				}
				DlgFlags.fParentsDisabled = true;
			} else {
				m_hWndLast = NULL;
				DlgFlags.fParentsDisabled = false;
			}

		ExecType et = ExecNormal;

			if (NoQuitOnHide & s)
				et = ExecNormalNoQuitOnHide;
			CV_RunTime::App_Exec(AppImpInst, et, &pActiveContext);

		// aktiven Dialog wieder rücksetzen
			if (AppImpInst -> GetActiveDialog() == hModeless)
				AppImpInst -> SetActiveDialog(0);
		}
	}												// * 1.6, 1.7 end *
}	
				 
/*************************************************************************
 *                                                                       *
 *  Font management functions                                            *
 *                                                                       *
 *************************************************************************/

#if !defined(WIN32)
extern "C" BOOL _pascal _loadds ShowControlProc ( HWND hWnd, unsigned long lParam)
#else
extern "C" BOOL WINAPI ShowControlProc (HWND hWnd, unsigned long lParam)
#endif
{
	if (::GetParent(hWnd) != (HWND)lParam)
		return 0;

   	ShowWindow (hWnd, 1);

return 1 ;
}

#if !defined(WIN32)
extern "C" BOOL _pascal _loadds SetChildFontProc ( HWND hWnd, unsigned long lParam)
#else
extern "C" BOOL WINAPI SetChildFontProc (HWND hWnd, unsigned long lParam)
#endif
{
char ClassName[20];
uint controlType; 
Rectangle CtrlRect;
int xo, yo, newWidth, newHeight;
const DIALOG_VARS *dv = (DIALOG_VARS *)lParam;

// Is this a direct child of the dialog
	if (::GetParent(hWnd) != dv -> hDlg)
		return 1;


// Determine class type

	GetClassName (hWnd, ClassName, 19);
	controlType = _GetStringValue( ClassName );

// Get position and size of Control in display units

   	ShowWindow ( hWnd, 0);  // hide control

	if (controlType == CTRL_ComboBox || controlType == CTRL_ComboBoxEx) {
    	Rectangle CtrlRect1, CtrlRect2;

	    	GetWindowRect(hWnd, (RECT *)&CtrlRect2);
		ComboBox_GetDroppedControlRect (hWnd, (RECT *)&CtrlRect);
//		SendMessage(hWnd,CB_GETDROPPEDCONTROLRECT, 0,(unsigned long)(&CtrlRect1));
    		UnionRect((RECT *)&CtrlRect, (RECT *)&CtrlRect1, (RECT *)&CtrlRect2);
	}
	else
        	GetWindowRect(hWnd, (RECT *)&CtrlRect);

Point p1 ( CtrlRect.Left(), CtrlRect.Top()) ;

   	ScreenToClient(dv->hDlg, (POINT *)&p1);

Point p0 ( CtrlRect.Right(), CtrlRect.Bottom()) ;

   	ScreenToClient(dv->hDlg, (POINT *)&p0);

	xo = (p1.X() * dv->fontX) / dv->Xbase  ;
	yo = (p0.Y() * dv->fontY) / dv->Ybase  ;


// determine the new width and height for the control
	newWidth = (abs(CtrlRect.Right() - CtrlRect.Left()) *  (dv->fontX))/dv->Xbase ;
	newHeight = (abs(CtrlRect.Bottom() - CtrlRect.Top()) * (dv->fontY))/dv->Ybase ;
	yo -= newHeight ;
	SetWindowFont (hWnd, dv->hFont, true);
//	SendMessage(hWnd, WM_SETFONT, (WPARAM)dv->hFont, true);
	SetWindowPos(hWnd,NULL, xo, yo, newWidth, newHeight, SWP_NOZORDER  | SWP_NOACTIVATE);

// if control is a CA-CommonView object change store size and position
pControl_Imp pci = (pControl_Imp)(_AppImpFind()->ControlList()->Find ((HANDLE)hWnd ));
 
	if ( pci ) {
		pci->SetControlWhere (Point( xo,yo) ) ;
		pci->SetControlSize  (Dimension( newWidth, newHeight ) );
	}

return 1;				    // continue enumerating
}



pFont	DWind_Imp::  ChangeFont	( pFont new_Font, BOOL rescale )
{
    if ( !rescale )
        return Wind_Imp::ChangeFont( new_Font );

	pFont	old	= WndFont;
	WndFont		= new_Font;

    DIALOG_VARS dialogInfo;
    TEXTMETRIC tm;
    HDC hDCtmp ;
    HFONT	hfont =  0 ;
    Rectangle DlgRect;  
    int xo, yo;


    if ( hDC )
    {
		DCFlags.FontInUse = 1;
		DCFlags.FontNeeded = 0;
		GetDC();
    }

	CV_ASSERT_VALID(hModeless);

    dialogInfo.hDlg = hModeless ;
    hDCtmp	= ::GetDC ( hModeless );

    if ( WndFont ) 
    {
		CV_RunTime::Font_Imp(WndFont) -> Init(0, hDCtmp);
        dialogInfo.hFont = WndFont->Handle();
        hfont = CV_RunTime::Font_hFont ( WndFont ) ;
    }
    else
        hfont = (HFONT)GetStockObject (13 ) ;

	CV_ASSERT_VALID(hfont);

    // require metrics of new font if rescalling 
    HFONT hOldFont = (HFONT)SelectObject(hDCtmp, hfont) ;
    GetTextMetrics(hDCtmp, &tm);
    SelectObject ( hDCtmp, hOldFont );
    ReleaseDC(hModeless, hDCtmp);

    dialogInfo.fontX = tm.tmAveCharWidth;
    dialogInfo.fontY = tm.tmHeight;
    dialogInfo.Xbase = Xbase ;
    dialogInfo.Ybase = Ybase ;

    Xbase = tm.tmAveCharWidth ;
    Ybase = tm.tmHeight ;

    EnumChildWindows(hModeless,(WNDENUMPROC)SetChildFontProc, (long)(&dialogInfo));

    GetClientRect(hModeless, (RECT *)&DlgRect);

    // keep bottom left in screen co-ordinates
    Point p1 ( DlgRect.Left(),  DlgRect.Top()) ;
    Point p0 ( DlgRect.Right(), DlgRect.Bottom()) ;
   	ClientToScreen(hModeless, (POINT *)&p0);
   	ClientToScreen(hModeless, (POINT *)&p1);
    xo = p1.X() ;
    yo = p0.Y() ;

    // adjust width/height (client co-ordinates )
    DlgRect.Right()  = tm.tmAveCharWidth * Xchars ;
	DlgRect.Bottom() = tm.tmHeight * Ychars ;
    AdjustWindowRect((RECT *)&DlgRect, GetWindowLong(hModeless, GWL_STYLE), 
				(::GetMenu(hModeless) ? true : false));	

    // convert to screen co-ordinates
    Point p2 ( DlgRect.Left(),  DlgRect.Top()) ;
    Point p3 ( DlgRect.Right(), DlgRect.Bottom() ) ;
	ClientToScreen(hModeless, (POINT *)&p2);
    ClientToScreen(hModeless, (POINT *)&p3);


    // calculate origin in relation to BottomLeft and reposition
    yo -= abs(p3.Y()-p2.Y()) ;
    MoveWindow(hModeless, xo, yo, abs(p3.X()-p2.X()), abs(p3.Y()-p2.Y()),false);

    // reshow controls hidden during rescalling
    EnumChildWindows(hModeless,(WNDENUMPROC)ShowControlProc,(LPARAM)(HANDLE)hModeless) ;

	return	old;
}


BOOL DWind_Imp::  CloseHandler(CloseStyle cs, Event e)
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
			EndDlg(0);
	 		CV_RunTime::EC_SetRetval(this,1L);
		}
	return true;
}
