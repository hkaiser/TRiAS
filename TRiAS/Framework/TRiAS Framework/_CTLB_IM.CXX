/* $Header:   G:/cv.win/pvcs/commonvu/src/_ctlb_im.cxv   3.0.1.0   14 Jul 1992 11:48:34   RONAN  $
 *
 *      _ c t l b _ i m . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *
 *	0.01 ferg	27sep88	Only Show ControlParent if it has not already been
 *						shown.
 *	0.1	ferg	29sep88	Dummy control constructor for Dialog Controls moved 
 *						to control.cxx .
 *	0.2	ferg	29sep88	Correctly insert dummy controls into 
 *						App_List_of_Controls
 *	0.0	ferg	05oct88	-------- Milestone 2. Beta 2 shipped -------------
 *	0.3	ferg	02nov88	Constructors all moved back here from control.cxx.
 *						Also get AppInst from DLL with _AppFind() also get
 *						SHow flag from App, control.cxx is now defunct.
 *	0.4	rs		17nov88	ferg from rs 27oct88. Addition of ChangeSize and 
 *						ChangePosition for controls
 *	0.5	rs		17nov88	ferg from rs 03nov88. Renamed ScrollBar::SetPos and 
 *						GetPos to SetThumbPos and GetThumbPos
 *	0.6	rs		17nov88	ferg from rs 14nov. Additions for windows scroll bars.
 *						Converted SB_CTL to SBType in all scroll actions
 *                      Added contructors for WndVertScrollBar, WndHorzScrollBar
 *	0.7	ferg	18nov88	use CV_WindowSB to distinguish window scroll bars.
 *	0.8	ferg	23nov88	Kludge to allow virtual showing of Control. Problem
 *						with normal virtual mechanism is that the object vptr
 *						is initialsed with a near vtbl offset in the DLL ds:
 *						and not with the users vtbl offset. Solution is to 
 *						maintain a near pointer to virtual show functions 
 *						is initialised by the ctor. CS: is guarenteed ok when
 *						the virtual show function is invoved.
 *	0.9	ferg	25nov88	destroy control if it still exists in dtor.
 *	0.10 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.11 jk		02dec88	Fast Compile defines added.
 *  0.12 rs     12dec88 Protection against operations on objects with invalid
 *                      handles.
 *  0.13 rs     16jan89 Added Control::Hide, Enable, Disable
 *  0.14 rs     24jan89 Altered ScrollBar::SetRange, SetThumbPosition to only
 *                      automatic repaint if RunTime::App_CVSflg is true
 *  0.15 rs      		Mapping mode compatibility 
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1 rs		19jun89	Altered horizontal scroll bars to show as horizontal		
 *	1.2 rs		26jun89	Added code to initialise size and position of
 *						controls taken from dialog boxes.
 *						Altered useage of ControlWhere to store position 
 *						in mapped form and translate when needed.
 *	1.3 rs		29jun89 Added in code to insert object information on
 *						property list
 *	1.4	rs 		04jul89	Use CV_WindowSB as id for Window scroll bars to
 *						ensure correct operation of Hide.
 *  1.5	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.6	rs		04oct89 Remove temporal dependencies in controls.
 *	1.7 rs		17Dec89	List boxes should not be sorted
 *	1.8 rs		21Dec89	Fixed text uses a copy of the text.
 *						A destructor has been added to free this text
 *	1.9 rs		08Jan89	Always hide WindowScrollBar controls before destroying them
 *	1.10 hl		29jan90 Control::Disable()
 *					test for Window Scrollbars
 *				CV_RunTime::WndScrollBarDisabled()
 *						new function
 *					WndHorzScrollBar & WndVertScrollBar
 *					initialisation of Disabled
 *	1.11 hl		09Feb90	Use of ControlName == CTRL_WndScroll as id for
 *						Window scrollbars in Control::Hide() 
 *	1.12 hl				Fix to support correct showing of Fixed icons
 *	1.13 rs		09Mar90 Remove Control from list when it becomes invalid	
 *	1.14 rs		04Jun90	Correct showing of scroll bars.
 *	1.15 rs		11Jun90	Code from _inline.cxx
 *	1.16 rs		14Jun90	Corrections to GetLine and GetLineLength to
 *				handle current default versions.
 *	2.0  rs,nc	??Jul90 Hiding and large model changes.
 *	2.1  rs		19Jul90	ChangeSize and ChangePosition on a Windows scroll bar
 *	     			should have no effect.
 *	3.0 ls		28May91 Added    Edit::SetModified
 *				         Edit::GetSelection(bool)
 *				         Edit::CanUndo()
 *				Modified Edit::SetTextLimit	
 *					 Edit::GetSelection(buffer,int)
 *					 Edit::ReplaceSelected
 *					 Edit::DeleteSelected
 *				Moved    MultiLineEdit:: Undo() to
 *					 Edit::Undo()
 *  3.0  NC       May91 Tidying up of control class ie
 *                      virtual Show ( bool )   (false for hiding)
 *                      virtual Create() for
                                Control_Imp
                                FixedIcon_Imp
                                FixedText_Imp

 *                      virtual Enable ( bool ) (false for disable)
 *                      Removal of CA-CommonView mask for identifying control
 *                      types
 *
 *                      cvsflg removed as it is now redundant due to virtual 
 *                      create and show  functions
 *
 *  3.1 NC              Altered ScrollBar::SetRange, SetThumbPosition to 
 *                      repaint only if window is visible
 *	3.2 RS				Positioning modifications
 *	3.3 RS		July92	(Integration of PC of May 1992)
 * 		PC		Changed code of ChangeBackground and Change TextColor to force an immediate change.
 *				Added the ManageColor and DefBackgroundBrush members to control class.
 *				Removed UseDefColor from Control class.
 *	3.4	RS		July 92	Use single default background brush from class App_Imp
 *						for painting default bacground of Controls.						
 */


#include "tfrmpre.hxx"

#include	<_Link.hxx>			   				

#ifdef MSCC8
#define ULTOA	_ultoa
#else
#define ULTOA	ultoa
#endif

#if !defined(WIN32)
extern "C" char * _cdecl ULTOA(unsigned long, char *, int);
inline int abs(int x) { return (x < 0) ? (-x) : (x); }
#endif

void Control_Imp :: ProcessRegClassStr(const char * RegClass)
{
	// Process Registered Class Name
	if ( ((ulong)RegClass) > 256 )
		{
		ulong value = _GetStringValue(RegClass);
		// Check if Standard control.
		if (value)
			ControlName = (char * )value;
		else
		// If not , Check if ControlName needs to be added to class list
			{
			// Check for special characters
			char * BaseClass;
		   	pApp_Imp AppImpInst = _AppImpFind();	

			if ((BaseClass = CV_strchr(RegClass, '.')) ||
				(BaseClass = CV_strchr(RegClass, ':')))
				{
				ControlName = CV_strdup(RegClass);
				if (*BaseClass == ':')
					{
					char *EOS = CV_strchr(ControlName, ':');
					*EOS = '\0';
					}
				// Insert value and base class in registered class list
				// This will be looked up on receipt of a WM_COMMAND message
				ulong alias = _GetStringValue (BaseClass+1);
				
					AppImpInst -> RegClassList() -> Insert (alias, ControlName);
				}
			} // else
		}
	else
		ControlName = (char *)RegClass;
}

Control_Imp::  Control_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char * RegClass, ulong InitStyle )
	:	ControlSize (size), ControlWhere (where), ControlParent (parent), ControlID (UsrID)
{
	pRequestor = req;
	hControl	= 0;
	ControlStyle = InitStyle /*| ( WS_CHILD | WS_CLIPSIBLINGS )*/;	// Style an alle Konstruktoren verteilt
	ControlName	= 0;
	ProcessRegClassStr(RegClass);
	ControlBackground = 0;
	WindowName 	= 0;
	fDialogChild = false;
	fAttached = false;
	fInitialized = false;

#if defined(WIN32)
	poldproc = NULL;
#endif // WIN32
	if (ControlParent)
		  CV_RunTime :: ValidateWindow(ControlParent);
}	// End of "Control" CONSTRUCTOR "(uint,pWind_Imp,uint,Point,Dimension)"

Control_Imp::  Control_Imp( pControl pReq, pDWind_Imp parent, ResID RscID, const char * RegClass )// * 0.2 , 0.3 Begin *
	:	ControlParent ((pWind_Imp)parent ), ControlID((uint)RscID)
{
	pRequestor = pReq;

	WindowName 	= 0;
	ControlBackground = 0;
	ControlStyle	= ( WS_CHILD | WS_CLIPSIBLINGS );
	ControlName	= 0;
	ProcessRegClassStr(RegClass);
	hControl = parent -> Handle() ? GetDlgItem (parent -> Handle(), ControlID) : NULL;

	fDialogChild = true;
	fAttached = false;
	fInitialized = false;

#if defined(WIN32)
	poldproc = NULL;
#endif // WIN32
	if (hControl) 
		Control_Imp :: Create();	// Setup the control
}	// End of "Control" CONSTRUCTOR "(pDialog,uint)"

Control_Imp :: Control_Imp (pControl pReq, pWind_Imp pParent, HWND hWnd)
	     : ControlParent (pParent), ControlID((uint)0)
{
	WindowName 	= 0;
	ControlBackground = 0;
	ControlName	= 0;

char cbBuffer[64];	// Fensterklasse speichern&einordnen

	if (GetClassName (hWnd, cbBuffer, sizeof(cbBuffer)))
		ProcessRegClassStr (cbBuffer);

	pRequestor 	= pReq;
	hControl	= hWnd;
	ControlStyle	= GetWindowLong (hWnd, GWL_STYLE);
	fDialogChild 	= true;
	fAttached 	= true;
	fInitialized = false;

#if defined(WIN32)
	poldproc = NULL;
#endif // WIN32

	if (hControl) 
		Control_Imp :: Create();	// Setup the control
}	// End of "Control" CONSTRUCTOR "(pDialog,uint)"

#if defined(WIN32)
LRESULT Control_Imp :: OnDestroy (Event e)
{
// jetzt das Control aus der Liste der uns bekannten herausnehmen
 	_AppImpFind() -> ControlList() -> Delete ((HANDLE)hControl);
	return Default(e);
}

LRESULT Control_Imp :: Default (Event e)	// für subclassing
{
	return CallWindowProc ((WNDPROC)poldproc, hControl,
					CV_RunTime :: Event_wMsg (e),
					CV_RunTime :: Event_wParam (e),
					CV_RunTime :: Event_lParam (e)
				);
}
#endif // WIN32

pWindow Control_Imp :: GetParent()
{
	return (pWindow)(ControlParent->GetRequestor());
}


void	Control_Imp::  SetStyle	( ulong style )
{
// Check if control is a button
// If yes use BM_SETSTYLE

	ControlStyle	|= style;

  	if (Valid()) {
	char	buff[30];

		GetClassName( hControl, buff, 20 );

		if ( _GetStringValue (buff)  == CTRL_Button)
			Button_SetStyle (hControl, style, false);
//        		SendMessage(hControl, BM_SETSTYLE, (int)style, 0L);
	    	else { 
		long sty = GetWindowLong (hControl, GWL_STYLE);

			SetWindowLong (hControl, GWL_STYLE, sty | style); // 1.6 end
    		}
  	}
}	// End of "Control_Imp" FUNCTION "SetStyle"


CvID	Control_Imp::  GetID	()
{
	return	( ControlID  );

}	// End of "Control" FUNCTION "GetID"


void	Control_Imp::  SetFocus	()
{
	if (ValidateControl())    // RSDEBUG
    		::SetFocus (Handle ());
}	// End of "Control_Imp" FUNCTION "Focus"

															// * 0.6 Begin *
Dimension Control_Imp::  ChangeSize (Dimension NewSize)
{
	Dimension tmp = ControlSize;
	ControlSize = NewSize;
	if (ValidateControl())    
			RePosition(0,true, true);
return tmp;
}

HDWP Control_Imp::  RePosition (HDWP hDefer, BOOL ReSize, BOOL ReDraw)
{
	 if (Valid()) {
	 Point p (ControlWhere.X(), ControlWhere.Y()+ ControlSize.Height() - 1);

		p = CV_RunTime ::  LogToDev ( ControlParent, p);

	 	if (!hDefer)
			SetWindowPos( hControl, NULL, p.X(),p.Y(), 
		 			(ReSize ? ControlSize.Width() : 0),
		 			(ReSize ? ControlSize.Height() : 0),
    					( (IsWin31() || ReDraw) ? 0 : SWP_NOREDRAW) | (ReSize ? 0 : SWP_NOSIZE) | SWP_NOZORDER  | SWP_NOACTIVATE);
		else
			hDefer = DeferWindowPos( hDefer, hControl, NULL, p.X(),p.Y(), 
		 			(ReSize ? ControlSize.Width() : 0),
		 			(ReSize ? ControlSize.Height() : 0),
    					(ReSize ? 0 : SWP_NOSIZE )| SWP_NOZORDER  | SWP_NOACTIVATE);
   	}

return hDefer;
}


void Control_Imp::  Erase()
{
 //	Default erase does nothing as control manages own background
}

HDWP GroupBox_Imp::  RePosition (HDWP hDefer, BOOL ReSize, BOOL ReDraw)
{
	return TextControl_Imp :: RePosition(hDefer, ReSize, ReDraw);
}

void GroupBox_Imp::  Erase()
{
Rectangle rErase;

	if (IsWin31() && IsWindowVisible(hControl) && 
	    GetUpdateRect(hControl, (RECT *)&rErase, false))
	{
	Rectangle R;

		GetWindowRect(hControl, (RECT *)&R);

	HDC hWndDC = GetDCEx (hControl,0,  DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_PARENTCLIP | DCX_CLIPSIBLINGS);

		IntersectClipRect (hWndDC,0,0,R.Right() + 1, (R.Bottom() - R.Top()) + 1);
		IntersectClipRect (hWndDC,rErase.Left(),rErase.Top(), rErase.Right(), rErase.Bottom());
		SendMessage (ControlParent -> Handle(), WM_ERASEBKGND, (uint)hWndDC, 0);
		ReleaseDC (hControl,hWndDC);
	}
}

void	Control_Imp::  Show	( BOOL ShowFlag ) 
{
	if (!hControl && ShowFlag) Create () ;

	if (Valid())
       		ShowWindow ( hControl, ShowFlag);
}


void  Control_Imp :: Create() 
{
	if (fInitialized) return;		// wurde bereits initialisiert

pApp_Imp AppImpInst = _AppImpFind();	
HWND ControlParentHandle = (ControlParent ? ControlParent -> Handle() : 0);
             
	if (!fDialogChild) {
	Point CtrlPos = ControlWhere;	

	   	CtrlPos.Y() +=  ControlSize.Height() - 1;
		if ( ControlParent)
			CtrlPos =  CV_RunTime :: LogToDev ( ControlParent, CtrlPos); 
		hControl = CreateWindowEx (0, 
					  (((ulong)ControlName < 256) ?
					  	_GetString ( (int)ControlName ) : ControlName),
					  WindowName,
					  ControlStyle,
					  CtrlPos.X (), CtrlPos.Y (),
					  ControlSize.Width (),	ControlSize.Height (),
					  ControlParentHandle,
			 		  (HMENU)uint (ControlID),
			 		  AppImpInst->Handle (API_APP_HAPP), // hApp
             		  0); 
	// 
	// Update size as size of created control may be different to size 
	// requested. This usually occurs due to list boxes etc being round to the
	// an integral of the height of one item.

	Rectangle CtlRect;
	
		GetWindowRect( hControl, (RECT *)&CtlRect);
		ControlSize = Dimension( CtlRect.Right() - CtlRect.Left() , CtlRect.Bottom() - CtlRect.Top() );
	} else {
	// CONTROL IS A RESOURCE CONTROL
		if (NULL == hControl) {		// reinit
			hControl = GetDlgItem (ControlParentHandle, ControlID);
			if (NULL == hControl)
				return;		// noch nicht initialisiert
		}

		if (NULL != hControl) {
	        Rectangle r;
	
			GetWindowRect(hControl, (RECT *)&r);
			ControlSize = Dimension( r.Right() - r.Left() , r.Bottom() - r.Top() );

			if (NULL != ControlParentHandle) {
				ScreenToClient (ControlParentHandle, (POINT  *)(&r));
				ScreenToClient (ControlParentHandle, (POINT  *) &(((int  *)&r)[2]) );
			}

		Point tmp(r.Left(), r.Bottom()-1);
	
			ControlWhere = CV_RunTime :: DevToLog (ControlParent, tmp);
		}
	}
    if (hControl) {
		AppImpInst -> ControlList() ->Insert ((HANDLE)hControl, this );

#if defined(WIN32)
	// subclassing für WM_DESTROY machen
		poldproc = (WNDPROC)SetWindowLong(hControl, GWL_WNDPROC,
					 	  (long)ControlDispatcher);
#endif // WIN32

		fInitialized = true;		// nicht doppelt initialisieren
	}
}


void     Control_Imp::  Enable ( BOOL flag)
{
	if (Handle())
		  EnableWindow(Handle(), flag );
}

// Funktion, welche das Control richtig zerlegt. Muß aus abgeleitetem
// Destruktor gerufen werden, da während des Destruktors von Control_Imp
// der virtual-Mechanismus für OnDestroy nicht mehr funktioniert (#HK960416).
void Control_Imp::DestroyControl (void)
{
pApp_Imp AppImpInst = _AppImpFind();				// * 0.3 *

	if (Valid()) {
		if (!fAttached)
			DestroyWindow (hControl);
		else 
			AppImpInst -> ControlList() -> Delete ((HANDLE)hControl);
	}

	if ((ulong)ControlName > 256) {
	// remove registered class from parents registered class list
		if (AppImpInst -> RegClassList() -> FindItemShallow(ControlName))
			AppImpInst -> RegClassList() -> Delete();
		// remove copy of class name
		delete ControlName;
		ControlName = NULL;
	}
}

Control_Imp::  ~Control_Imp	()
{
/*
 *	Only delete from App_List_of_Controls if control is not a 
 *	window scroll bar.
 */
	if (ControlName != (const char *)CTRL_WndScroll) 
		DestroyControl();

	if (WindowName) {
		delete WindowName;
		WindowName = NULL;
	}
	ControlParent = NULL;
}	


// It is unnecessary to have separate flags for managing the background
// (as is the case with text color). ControlBackground != 0 implies
// user has supplied background.
// Wind_Imp :: ManageControlBackground uses a set of flags which 
//
// 
pBrush	Control_Imp::  ChangeBackground ( pBrush new_Background )
{
pBrush	old	= ControlBackground;
ControlBackground	= new_Background;

	if (ControlBackground != old) {
	// if Control was being managed but is not now then decrement count
	// if Control is being managed but was not previously then decrement count
		if (ControlParent)
			ControlParent -> ManageControlBackground(ControlBackground ? true :  false);

	// If Control needs updating update it
		if (Valid() && IsWindowVisible(hControl)) {
			InvalidateRect(hControl, NULL, true);
			UpdateWindow(hControl);
		}
	}
	return	old;
}	


Button_Imp::  Button_Imp ( pControl req, pDWind_Imp pW, ResID RscID )
	   : TextControl_Imp( req, pW, RscID )
{
}

Edit_Imp::  Edit_Imp ( pControl req, pDWind_Imp pW, ResID RscID )
	 : TextControl_Imp( req, pW, RscID)
{ 
}

Edit_Imp :: Edit_Imp (pControl req, pWind_Imp pW, HWND hWnd)
	  : TextControl_Imp (req, pW, hWnd)
{ 
}

Point Control_Imp::  ChangePosition (Point p)
{
Point tmp = ControlWhere;
ControlWhere = p;

	if (ValidateControl())    
		RePosition(0,false, true);
	return tmp;
}
															// * 0.6 End *



// ----------------------------- FixedIcon_Imp ----------------------------------

FixedIcon_Imp::  FixedIcon_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, ResID id )
	:	Control_Imp(req,  parent, UsrID, where,
		Dimension ( GetSystemMetrics( SM_CXICON), GetSystemMetrics( SM_CYICON) ), 
		(const char *)CTRL_Static, (WS_CHILD | WS_CLIPSIBLINGS))	// * 1.11 *
{
// *MAPPING window
	SetStyle ( SS_ICON );
	if (WindowName = new char[10]) {
	    WindowName[0] = '#';
		ULTOA((ulong)(uint)id, &WindowName[1], 10);
	}

}	// End of "FixedIcon_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,pchar)"


// ----------------------------- ScrollB_Imp ----------------------------------

ScrollB_Imp::  ScrollB_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size)
	:	Control_Imp(req, parent, UsrID, where, size, (const char*)CTRL_ScrollBar, 
			    WS_CHILD | WS_CLIPSIBLINGS)
{
	SBBlock = SBUnit = 1;
	SBDisabled = SBIgnoreEndScroll = 0;
	SBType = SB_CTL;
}

ScrollB_Imp::  ScrollB_Imp (pControl req, pDWind_Imp pW, ResID RscID)
	: Control_Imp( req, pW, RscID, 0) //* 0.7 *
{ 
	SBBlock = SBUnit = 1;									// * 0.7 *
	SBType = SB_CTL;										// * 0.7 *
	SBDisabled = SBIgnoreEndScroll = 0;
}

void ScrollB_Imp :: Show ( BOOL ShowFlag)
{
    	if (!hControl &&  ShowFlag) Create () ;
	if (hControl )
          	ShowScrollBar (hControl, SB_CTL, ShowFlag) ;
}


// * 0.6, 0.7 Begin *
ScrollB_Imp::  ~ScrollB_Imp()
{
	long mask = ~WS_HSCROLL;
	
	if (ControlParent && !ControlParent -> InDestructor()) {
		if ( Handle() && IsWindow(Handle()))    // * RSDEBUG *
    			ShowScrollBar(Handle(), SBType, 0);

		if ( SBType != SB_CTL) {
			if (SBType == SB_VERT)
				mask = ~WS_VSCROLL;

			if ( Handle() && IsWindow(Handle()))    // * RSDEBUG *
			{
        		long sty = GetWindowLong ( Handle(), GWL_STYLE);

	        		SetWindowLong ( Handle(), GWL_STYLE, sty & mask);
        		}
    		}
	}
}  	
														// * 0.6, 0.7 End *

int	ScrollB_Imp::GetThumbPos()							// * 0.5 *
{
	if (ValidateControl()) {
		if (IsWin40()) {
		SCROLLINFO si;

			memset (&si, 0, sizeof(SCROLLINFO));
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			if (GetScrollInfo (Handle(), SBType, &si))
				return si.nPos;		// ok
		// hier durchfallen
		// ...
		} else
	    	return	GetScrollPos (Handle (), SBType);			// * 0.7 *
   	} 

return 0;
}	// End of "ScrollBar" FUNCTION "GetPos"

void	ScrollB_Imp::  SetThumbPos	( int where )			// * 0.5 *
{
	if (ValidateControl()) {
		if (IsWin40()) {
		SCROLLINFO si;

			memset (&si, 0, sizeof(SCROLLINFO));
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			si.nPos = where;

			SetScrollInfo (Handle(), SBType, &si, IsWindowVisible(Handle()));
		} else
		    SetScrollPos (Handle (), SBType, where, IsWindowVisible(Handle())); // 3.1
	}
}	// End of "ScrollBar" FUNCTION "SetPos"

int	ScrollB_Imp::GetTrackPos (void)			// #HK960411
{
	if (ValidateControl() && IsWin40()) {
	SCROLLINFO si;

		memset (&si, 0, sizeof(SCROLLINFO));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_TRACKPOS;
		if (GetScrollInfo (Handle(), SBType, &si))
			return si.nTrackPos;		// ok
	// hier durchfallen
	// ...
   	} 

return 0;
}	// End of "ScrollBar" FUNCTION "GetTrackPos"


uint	ScrollB_Imp::GetPageSize (void)							// #HK960411
{
	if (ValidateControl() && IsWin40()) {
	SCROLLINFO si;

		memset (&si, 0, sizeof(SCROLLINFO));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE;
		if (GetScrollInfo (Handle(), SBType, &si))
			return si.nPage;		// ok
	// hier durchfallen
	// ...
    }

return 0;
}	// End of "ScrollBar" FUNCTION "GetPageSize"

int ScrollB_Imp::SetPageSize (uint uiSize, BOOL fRedraw)		// #HK960411
{
	if (ValidateControl() && IsWin40()) {
	SCROLLINFO si;

		memset (&si, 0, sizeof(SCROLLINFO));
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE;
		si.nPage = uiSize;

		return SetScrollInfo (Handle(), SBType, &si, fRedraw);
	}

return 0;
}	// End of "ScrollBar" FUNCTION "SetPageSize"


Range	ScrollB_Imp::  GetRange	()
{
Range range;

	if (ValidateControl()) {
		if (IsWin40()) {
		SCROLLINFO si;

			memset (&si, 0, sizeof(SCROLLINFO));
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE;
			if (GetScrollInfo (Handle(), SBType, &si)) {
				range.Min() = si.nMin;
				range.Max() = si.nMax;
			}
		} else {
		int cMin = 0, cMax = 0;

			GetScrollRange (Handle (), SBType, &cMin, &cMax);
			range.Min() = cMin;
			range.Max() = cMax;
		}
	}

return	range;
}	// End of "ScrollBar" FUNCTION "GetRange"

void	ScrollB_Imp::  SetRange	(Range range)
{
	if (ValidateControl()) {
		if (IsWin40()) {
		SCROLLINFO si;

			memset (&si, 0, sizeof(SCROLLINFO));
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE;
			si.nMin = range.Min();
			si.nMax = range.Max();

			SetScrollInfo (Handle(), SBType, &si, IsWindowVisible(Handle()));
		} else
	   		SetScrollRange (Handle (), SBType, range.Min(), range.Max(), IsWindowVisible(Handle())); // 3.1
	}
}	// End of "ScrollBar" FUNCTION "GetRange"

//--------------------------Window Scroll Bars ------------------
														// * 0.7 Begin *
WndScrollB_Imp ::  WndScrollB_Imp ( pControl req,  pWind_Imp parent)  
    : ScrollB_Imp(req,  parent, CV_WindowSB, Point(0,0), Dimension(0,0))
{
	ControlName = (char *)CTRL_WndScroll;	// * 0.8 *
	hControl = parent -> Handle();
}
													
HDWP WndScrollB_Imp::  RePosition (HDWP hDefer, BOOL ReSize, BOOL ReDraw) { return hDefer;}

void WndScrollB_Imp:: Show ( BOOL ShowSbar)
{
	if (Valid() && ControlParent) {
	long sty = GetWindowLong ( hControl, GWL_STYLE);
	pWind_Imp pLocControlParent = ControlParent;

		if ( ((SBType == SB_VERT) && (!(sty & WS_VSCROLL)))
			|| ((SBType == SB_HORZ) && (!(sty & WS_HSCROLL))))
			CV_RunTime::Window_WndFlags(ControlParent) |= WF_SIZE_CHANGED;	// * 1.14 end *
	
		ShowScrollBar (hControl, SBType, ShowSbar);
		CV_RunTime :: Window_UpdateFrame(pLocControlParent);		// #HK960103
	}
} 

void WndScrollB_Imp::  Enable ( BOOL flag)
{
	SBDisabled = (flag ? 0 : 1);	
	if (IsWin31() && Valid())
		EnableScrollBar( hControl, SBType, (flag ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH));
}
// ----------------------------- TextControl --------------------------------


TextControl_Imp ::  TextControl_Imp ( pControl req,  pDWind_Imp parent, ResID id )
:	Control_Imp(req,  parent, id , 0)
{
	ManageColor = false;
	txtColor = GetSysColor(COLOR_WINDOWTEXT);
	InitTextMetrics();
}

TextControl_Imp ::  TextControl_Imp ( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size , const char * RegClass)
:	Control_Imp(req,   parent, UsrID, where, size, (const char *)RegClass, WS_CHILD | WS_CLIPSIBLINGS ), txtColor(Colors(BLACK) )
{
	ManageColor = false;
	txtColor = GetSysColor(COLOR_WINDOWTEXT);
}

TextControl_Imp :: TextControl_Imp (pControl req,  pWind_Imp parent, HWND hWnd)
		 : Control_Imp (req, parent, hWnd)
{
	ManageColor = false;
	txtColor = GetSysColor(COLOR_WINDOWTEXT);
}

void TextControl_Imp :: InitTextMetrics()
{
	if (NULL == hControl) return;	// erst initialisieren, wenn gültig

long lDBUnits;
Rectangle r ;
char ClassName[20];
uint controlType; 

	GetClassName(hControl, ClassName, 19);
	controlType =_GetStringValue( ClassName );


	if (controlType == CTRL_ComboBox || controlType == CTRL_ComboBoxEx) {
    	Rectangle CtrlRect1, CtrlRect2;
    	
   		GetWindowRect(hControl, (RECT *)&CtrlRect2);
		ComboBox_GetDroppedControlRect (hControl, (RECT *)&CtrlRect1);
//		SendMessage(hControl, CB_GETDROPPEDCONTROLRECT, 0,(unsigned long)(&CtrlRect1));
   		UnionRect((RECT *)&r, (RECT *)&CtrlRect1, (RECT *)&CtrlRect2);
	} else
        GetWindowRect(hControl, (RECT *)&r);

int width  = r.Right() - r.Left();
int height = r.Bottom() - r.Top() ;

	lDBUnits = GetDialogBaseUnits();
	Xchars = width/LoWord(lDBUnits) ;
	Ychars = height/HiWord(lDBUnits) ;

//  CHECK THIS !!!
	if ( !(Ychars = height/HiWord(lDBUnits)))
        Ychars = 1;
    txtCtrlFont = 0;
}

void TextControl_Imp :: Create ()
{
	Control_Imp :: Create();
	InitTextMetrics();
}


void	TextControl_Imp::  SetText	( const char* buffer )
{
	if (ValidateControl())    // RSDEBUG
		Static_SetText (Handle(), buffer);
//		SendMessage ( Handle (), WM_SETTEXT, 0, (ulong)buffer );
}	// End of "TextControl" FUNCTION "SetText"


void	TextControl_Imp::  GetText	( pchar buffer, uint maxlen )
{
	if (ValidateControl())    // RSDEBUG
		Static_GetText (Handle(), buffer, maxlen);
//	    	SendMessage ( Handle (), WM_GETTEXT, maxlen, (ulong)buffer );
}	// End of "TextControl" FUNCTION "GetText"


uint	TextControl_Imp::  GetTextLen	()
{
	if (ValidateControl())    // RSDEBUG
		return Static_GetTextLength (Handle());
//		return	(uint)( SendMessage ( Handle (), WM_GETTEXTLENGTH, 0, 0 ));
	else
		return 0;
}	// End of "TextControl" FUNCTION "GetTextLen"


pFont	TextControl_Imp::  ChangeFont ( pFont font, BOOL rescale )
{
HFONT	hfont =  0 ;
HDC hDCtmp ;
TEXTMETRIC tm;
Rectangle r;  
uint width, height ;
pFont	old	= txtCtrlFont;

	if (ValidateControl()) {
    		txtCtrlFont = font ;
    		if ( txtCtrlFont )
	    	{
			CV_RunTime :: Font_Imp( txtCtrlFont) -> Init(0,0);
    		    	hfont = CV_RunTime :: Font_hFont ( txtCtrlFont ) ;
    		}
    		else
        		hfont = (HFONT)GetStockObject (13) ;

    		if ( rescale )  // require metrics of new font if rescalling 
    		{
        		hDCtmp	= :: GetDC ( hControl );

        	HFONT hOldFont = (HFONT)SelectObject (hDCtmp, hfont) ;
        
        		GetTextMetrics(hDCtmp, &tm);
        		SelectObject ( hDCtmp, hOldFont );

			ReleaseDC (hControl, hDCtmp);

        	// adjust width/height
        		width  = Xchars * tm.tmAveCharWidth ;
        		height = Ychars * tm.tmHeight ;
		
			InvalidateRect(hControl, NULL, true);
        		ChangeSize( Dimension ( width, height )) ;
	     	}

	 	SetWindowFont (hControl, (WPARAM)hfont, true);
		return old ;
	 }
	 else
	 	return 0;
}

Color	TextControl_Imp::  ChangeTextColor ( Color SpecifiedColor )
{
	ulong defcol = (GetSysColor(COLOR_WINDOWTEXT)) & 0x00ffffffL;
	ulong newcol = ((long&)SpecifiedColor) & 0x00ffffffL;
	ulong oldcol = defcol;


	if (!ManageColor)
		{
		// If we are not already managing the control's color
		if (newcol != defcol)
			{
			txtColor = newcol;
			ManageColor = true;	
			if (ControlParent)
				ControlParent -> ManageControlText(true);

			if (Valid() && IsWindowVisible(hControl))
			{
				InvalidateRect(hControl, NULL, true);
				UpdateWindow(hControl);
			}

			}
		}
	else
		{
		// We are already managing the control color
		oldcol = txtColor;
		if (newcol != txtColor)
		{
			txtColor = newcol;

		// Check if we need to revert to system default
		if (newcol == defcol)
			{
			ManageColor = false;
			if (ControlParent)
				ControlParent -> ManageControlText(false);
			}

		// Update control 
			if (Valid() && IsWindowVisible(hControl))
			{
				InvalidateRect(hControl, NULL, true);
				UpdateWindow(hControl);
			}
		}
	}
   	return *((Color*)&oldcol);
}

// ----------------------------- Button_Imp -------------------------------------

Button_Imp::  Button_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char * InitText )
	: TextControl_Imp(req,  parent, UsrID, where, size , (const char *) CTRL_Button)
    // *MAPPING window
{
    SetText (InitText);
}	// End of "Button" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"

// ----------------------------- RadioButton_Imp --------------------------------

RadioButton_Imp::  RadioButton_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char * InitText )
	:	Button_Imp(req,  parent, UsrID, where, size, InitText )
{
    // *MAPPING window
	SetStyle ( BS_RADIOBUTTON );

}	// End of "RadioButton_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"


BOOL	RadioButton_Imp::  GetState	()
{
	if (ValidateControl())    // RSDEBUG
		return Button_GetCheck (Handle());
//		return	(bool)( SendMessage ( Handle (), BM_GETCHECK, 0, 0 ));
	else
		return 0;
}	// End of "RadioButton_Imp" FUNCTION "GetState"


void	RadioButton_Imp::  SetState	( BOOL OnOffFlag )
{
	if (ValidateControl())    // RSDEBUG
		Button_SetCheck (Handle(), OnOffFlag);
//    		SendMessage ( Handle (), BM_SETCHECK, OnOffFlag, 0 );

}	// End of "RadioButton_Imp" FUNCTION "SetState"

// ----------------------------- PushButton_Imp ---------------------------------

PushButton_Imp::  PushButton_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char* InitText )
	:	Button_Imp(req,  parent, UsrID, where, size, InitText )
{
    // *MAPPING window
	SetStyle ( BS_PUSHBUTTON );

}	// End of "PushButton_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"

HBITMAP PushButton_Imp::SetImage (HBITMAP hNewBmp)	// #HK960416
{
	if (IsWin40()) 
 		return (HBITMAP)::SendMessage(Handle(), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hNewBmp);

return NULL;
}

HBITMAP PushButton_Imp::GetImage (void)
{
	if (IsWin40()) 
	 	return (HBITMAP)::SendMessage(Handle(), BM_GETIMAGE, 0, 0L);

return NULL;
}

// ----------------------------- CheckBox_Imp -----------------------------------

CheckBox_Imp::  CheckBox_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char* InitText )
	:	Button_Imp(req,  parent, UsrID, where, size, InitText )
{
    // *MAPPING window
	SetStyle ( BS_CHECKBOX );

}	// End of "CheckBox_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"


BOOL	CheckBox_Imp::  isChecked	()
{
	if (ValidateControl())    // RSDEBUG
		return Button_GetCheck (Handle());
//		return	(bool)( SendMessage ( Handle (), BM_GETCHECK, 0, 0 ));
	else
		return 0;
}	// End of "CheckBox_Imp" FUNCTION "isChecked"


void	CheckBox_Imp::  SetChecked	( BOOL OnOffFlag )
{
	if (ValidateControl())    // RSDEBUG
		Button_SetCheck (Handle(), OnOffFlag);
//    		SendMessage ( Handle (), BM_SETCHECK, OnOffFlag, 0 );
}	// End of "CheckBox_Imp" FUNCTION "SetState"


// ----------------------------- Edit_Imp ---------------------------------------

Edit_Imp::  Edit_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size )
	:	TextControl_Imp(req, parent, UsrID, where, size ,  (const char *)CTRL_Edit)
    // *MAPPING window
{}	// End of "Edit_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"


uint	MultiLineEdit_Imp::  GetLineLength	( int index )
{
	if (ValidateControl())    
	{						  
		return Edit_LineLength (Handle(), Edit_LineIndex (Handle(), index));
//		return	(uint)
//		( SendMessage ( Handle (), 
//				EM_LINELENGTH,
//				(WPARAM)SendMessage (Handle (), EM_LINEINDEX, (WPARAM)index, 0L ), 
//				0L ));
	} else
        	return 0;

}	

void Edit_Imp::  SetTabStop ( uint  )  // 3.0
{
// To Be Implemented later
} // End of "Edit_Imp" FUNCTION "SetTabStop"

uint Edit_Imp::  GetTabStop ( )		       // 3.0
{
// To Be Implemented later
return 0;
} // End of "Edit_Imp" FUNCTION "GetTabStop"


BOOL	Edit_Imp::  isModified	()	       // 3.0
{
	if (ValidateControl())    // RSDEBUG
		return Edit_GetModify (Handle());
//    		return	(bool) ( SendMessage ( Handle (), EM_GETMODIFY, 0, 0 ));
    	else
        	return 0;
}	// End of "Edit_Imp" FUNCTION "isModified"


void Edit_Imp::  SetModified(BOOL SetTo)    // 3.0
{
	if (ValidateControl())    // RSDEBUG
		Edit_SetModify (Handle(), SetTo);
//   		SendMessage(Handle(), EM_SETMODIFY, SetTo, 0);
}	// End of "Edit_Imp" FUNCTION "SetModified"
	 

Selection	Edit_Imp::  GetSelection (BOOL toClipBoard)  // 3.0
{
	if (ValidateControl())    // RSDEBUG
	{	  
#if !defined(WIN32)
	ulong tmp = Edit_GetSel (Handle());
	
		if (toClipBoard)
		   	SendMessage (Handle(), WM_COPY, 0, 0);
	
	// ZORTECH, ztc illegal cast "return	(Selection&) tmp;"
		return (*((Selection*)& tmp) );
#else
	DWORD dwStart, dwEnd;

		SendMessage (Handle(), EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		if (toClipBoard)
		   	SendMessage (Handle(), WM_COPY, 0, 0);
		return Selection (CoOrd(dwStart), CoOrd(dwEnd));
#endif
 	}
 	else
        	return Selection(0,0);

}	// End of "Edit_Imp" FUNCTION "GetSelection"

Selection   Edit_Imp::  GetSelection (pchar buffer, int CopyTxtLen) // 3.0
{ 
pchar TxtBuffer;
short first;
short last;
short CopyLen = 0;

   	if (ValidateControl())    // RSDEBUG
   	{
#if !defined(WIN32)
	ulong tmp = Edit_GetSel (Handle ());

		first = LoWord(tmp);
		last  =	HiWord(tmp);
#else
	DWORD dwStart, dwEnd;

		SendMessage (Handle(), EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		first = short(dwStart);
		last = short(dwEnd);
#endif
		if ((last - first) < CopyTxtLen)
		   	CopyLen = (last - first);
		else
	   		CopyLen = CopyTxtLen;

		if (first != last) {
		uint TxtLen = Edit_GetTextLength (Handle());
//		uint TxtLen =	(uint)( SendMessage ( Handle (), WM_GETTEXTLENGTH, 0, 0 ));

			TxtBuffer = new char[ TxtLen + 1 ];
			if (TxtBuffer == NULL)
				return Selection (0, 0);
    			SendMessage (Handle (), WM_GETTEXT, TxtLen + 1, (LPARAM)TxtBuffer);
			if (CopyTxtLen == -1)	{
				CV_strncpy ( buffer, &TxtBuffer[first], (last - first));
				buffer[CopyLen] = '\0';
			} else {
				CV_strncpy ( buffer, &TxtBuffer[first], CopyLen);
				buffer[CopyLen] = '\0';
			}
			delete [] TxtBuffer;
		}
		return Selection (first, last);
   	} else
        	return Selection(0,0);
}	// End of "Edit_Imp" FUNCTION "GetSelection"



void	Edit_Imp::  ChangeSelection	(Selection select) // 3.0
{
	if (ValidateControl())    // RSDEBUG
		Edit_SetSel (Handle(), select.Start(), select.End());
//		SendMessage (Handle(), EM_SETSEL, 0, (*((unsigned long*)&select) ));
}	// End of "Edit_Imp" FUNCTION "ChangeSelection"


void	Edit_Imp::  SetTextLimit (uint nChars)  // 3.0
{ 
ulong TxtLen = 0;
char * buffer = new char[nChars + 1];

	if (buffer == NULL) return;

	if (ValidateControl())    // RSDEBUG
        {
//	        TxtLen =  SendMessage ( Handle (), WM_GETTEXTLENGTH, 0, 0 );
	        TxtLen =  Edit_GetTextLength (Handle());
                if ((uint)TxtLen > nChars)
                {
		    	Edit_GetText (Handle(), buffer, nChars+1);
			Edit_SetText (Handle(), buffer);
//		    	SendMessage ( Handle (), WM_GETTEXT, nChars+1, (ulong)buffer );
//			SendMessage ( Handle (), WM_SETTEXT, 0, (ulong)buffer );
                }
//		SendMessage ( Handle (), EM_LIMITTEXT, nChars, 0 );
		Edit_LimitText (Handle(), nChars);
	}
	delete [] buffer;
}	// End of "Edit_Imp" FUNCTION "SetTextLimit"


BOOL	Edit_Imp::  ReplaceSelected	( const char *text )  // 3.0
{ 
	if (ValidateControl()) {   // RSDEBUG
		if (!text) {
		 	SendMessage (Handle (), WM_CLEAR, 0, 0);
			(bool)SendMessage (Handle (), WM_PASTE, 0, 0);
		} else
			return (bool)SendMessage (Handle (), EM_REPLACESEL, 0, (ulong)text);
	}
	
return false;
}	// End of "Edit_Imp" FUNCTION "ReplaceSelected"


void	Edit_Imp::  DeleteSelected	( BOOL toClipBoard ) // 3.0
{ 
	if (ValidateControl())    // RSDEBUG
	{
		if (toClipBoard)
			SendMessage (Handle (), WM_CUT, 0, 0);
		else
			SendMessage (Handle (), WM_CLEAR, 0, 0);
	}

}	// End of "Edit_Imp" FUNCTION "DeleteSelected"

BOOL	Edit_Imp::  Undo	()
{
	if (ValidateControl())    // RSDEBUG
		return Edit_Undo (Handle());
//    		return	(bool) (SendMessage ( Handle (), EM_UNDO, 0, 0 ));
    	else
        	return 0;
}	// End of "Edit_Imp" FUNCTION "Undo"


BOOL	Edit_Imp::  CanUndo	()   // 3.0
{
	if (ValidateControl())    // RSDEBUG
		return Edit_CanUndo (Handle());
//	    	return	(bool) ( SendMessage ( Handle (), EM_CANUNDO, 0, 0 ));
    	else
        	return 0;
}	// End of "Edit_Imp" FUNCTION "CanUndo"

void Edit_Imp:: SetStdStyle( int style )
{

ulong sty = 0;
  	if (Valid())
		sty = GetWindowLong ( hControl, GWL_STYLE);

    	switch (style) {
    	case (int) Edit::UnBordered :
        	sty	&=~WS_BORDER;
          	ControlStyle	&=~WS_BORDER;
          	break;  

    	case (int) Edit::Bordered :
        	sty	|= WS_BORDER;
          	ControlStyle	|= WS_BORDER;
          	break;


    	case (int) Edit:: PassWord :
        	sty |= ES_PASSWORD;  
          	ControlStyle |= ES_PASSWORD;  
          	break;  

    	case (int) Edit:: ReadOnly :
		if (IsWin31()) {
          		sty |= ES_READONLY;  
          		ControlStyle |= ES_READONLY;  
		}
           	break; 

    	default:
        	break;
	}
  	if (Valid())
       		SetWindowLong (hControl, GWL_STYLE, sty); 
}

// ----------------------------- MultiLineEdit_Imp ------------------------------

MultiLineEdit_Imp::  MultiLineEdit_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size )
	:	Edit_Imp(req,  parent, UsrID, where, size )
{
    // *MAPPING window
	SetStyle ( ES_MULTILINE );

}	// End of "MultiLineEdit_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"


uint MultiLineEdit_Imp :: GetLine (int index, pchar buffer, uint nChars)
{
//	*((pint)buffer)	= nChars;

	if (ValidateControl())    // RSDEBUG
	{
	int retval;
	
		if (index == (-1)) 
//			index = (int)( SendMessage ( Handle (), EM_LINEFROMCHAR, 0xffff, 0 ));
			index = Edit_LineFromChar (Handle(), -1);
//    		if (retval =(uint) ( SendMessage ( Handle (), EM_GETLINE, index, (ulong)buffer )))
    		if (retval = Edit_GetLine (Handle(), index, buffer, nChars))
			buffer[retval] = 0;
		return retval;
	} else
		return 0;
}	// End of "MultiLineEdit_Imp" FUNCTION "GetLine"


uint	MultiLineEdit_Imp::  GetNumLines	()
{
	if (ValidateControl())    // RSDEBUG
//		return	(uint) ( SendMessage ( Handle (), EM_GETLINECOUNT, 0, 0 ));
		return Edit_GetLineCount (Handle());
	else
		return 0;
}	


void	MultiLineEdit_Imp::  ScrollVertical (int nLines)
{
	if (ValidateControl())    // RSDEBUG
		Edit_Scroll (Handle(), nLines, 0);
//		SendMessage (Handle (), EM_LINESCROLL, 0, (ulong)nLines );
}	// End of "MultiLineEdit_Imp" FUNCTION "ScrollVertical"


void	MultiLineEdit_Imp::  ScrollHoriz (int nChars)
{
	if (ValidateControl())    // RSDEBUG
		Edit_Scroll (Handle(), 0, nChars);
//		SendMessage (Handle (), EM_LINESCROLL, (ulong)nChars, 0L);
}	// End of "MultiLineEdit_Imp" FUNCTION "ScrollHoriz"


void	MultiLineEdit_Imp::  PageUp	()
{
	if (ValidateControl())    // RSDEBUG
		SendMessage (Handle(), EM_SCROLL, SB_PAGEUP, 0);
}	// End of "MultiLineEdit_Imp" FUNCTION "PageUp"


void	MultiLineEdit_Imp::  PageDown	()
{
	if (ValidateControl())    // RSDEBUG
		SendMessage (Handle(), EM_SCROLL, SB_PAGEDOWN, 0);
}	// End of "MultiLineEdit_Imp" FUNCTION "PageDown"


void	MultiLineEdit_Imp::  LineUp	()
{
	if (ValidateControl())    // RSDEBUG
		SendMessage (Handle(), EM_SCROLL, SB_LINEUP, 0);

}	// End of "MultiLineEdit_Imp" FUNCTION "LineUp"


void	MultiLineEdit_Imp::  LineDown	()
{
	if (ValidateControl())    // RSDEBUG
		SendMessage (Handle(), EM_SCROLL, SB_LINEDOWN, 0);

}	// End of "MultiLineEdit_Imp" FUNCTION "LineDown"

void MultiLineEdit_Imp:: SetMultiStyle ( int style )
{
ulong sty = 0;

	if (Valid())
	    sty = GetWindowLong ( hControl, GWL_STYLE);

    switch (style)
    {

    case (int) MultiLineEdit:: HScroll:
          sty |= (ES_AUTOHSCROLL | WS_HSCROLL);
          ControlStyle |= (ES_AUTOHSCROLL | WS_HSCROLL);
          break;  

    case (int) MultiLineEdit:: VScroll:
          sty	|= (ES_AUTOVSCROLL | WS_VSCROLL);
          ControlStyle	|= (ES_AUTOVSCROLL | WS_VSCROLL);
          break;

    default:
          break;

    }

  if (Valid())
       SetWindowLong ( hControl, GWL_STYLE, sty); 
}




/*
bool	MultiLineEdit_Imp::  Undo	()   // 3.0
{
	if (ValidateControl())    // RSDEBUG
    	return	(bool) ( SendMessage ( Handle (), EM_UNDO, 0, 0 ));
    else
        return 0;

}	// End of "MultiLineEdit_Imp" FUNCTION "Undo"


*/
// ----------------------------- SingleLineEdit_Imp -----------------------------

SingleLineEdit_Imp::  SingleLineEdit_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size )
	:	Edit_Imp(req,  parent, UsrID, where, size )
    // *MAPPING window
{}	// End of "SingleLineEdit_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"

SingleLineEdit_Imp :: SingleLineEdit_Imp (pControl req, pWind_Imp parent, HWND hWnd)
		    : Edit_Imp (req, parent, hWnd)
{
}

// ----------------------------- FixedText_Imp ----------------------------------

FixedText_Imp::  FixedText_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char* TextName )
	:	TextControl_Imp(req,   parent, UsrID, where, size , (const char *) CTRL_Static)
{
    // *MAPPING window
	WindowName	= CV_strdup(TextName);	// * 1.8 *

	SetStyle ( SS_LEFT );

}	// End of "FixedText_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension,nconst char*)"

void FixedText_Imp:: SetStdStyle( int style )
{
	ulong sty = 0;
  	if (Valid())
       sty = GetWindowLong ( hControl, GWL_STYLE);

    switch (style)
    {
    case (int) FixedText::LeftAlign :
        sty |= SS_LEFT ;
        ControlStyle |= SS_LEFT ;
        break;

    case (int) FixedText::RightAlign :
        sty |= SS_RIGHT;
        ControlStyle |= SS_RIGHT;
        break;

    case (int) FixedText::Centered :
        sty |= SS_CENTER ;
        ControlStyle |= SS_CENTER ;
        break;

    default:
        break;
    }   
        

  if (Valid())
       SetWindowLong ( hControl, GWL_STYLE, sty );
}

GroupBox_Imp :: GroupBox_Imp(pControl req, pWind_Imp parent, CvID id, Point where, Dimension size, const char *text )
                : TextControl_Imp (req, parent, id, where,size, (const char *)CTRL_Button)
{
    SetStyle(BS_GROUPBOX | WS_TABSTOP );
    SetText(text);
}

GroupBox_Imp:: GroupBox_Imp (pControl req , pDWind_Imp parent , ResID id)
             : TextControl_Imp (req, parent, id)
{
    SetStyle(BS_GROUPBOX);
}


//
// Validate control is used to prevent temporal depencencies on the order
// of calling attribute changing functions and Show.
// The pointer to control supplied has not already been shown, 
// it is created and shown "invisibly".
//
int Control_Imp ::   ValidateControl ( ) 
{
	if ( ! hControl)
		Create();

	if (hControl && IsWindow(hControl))
		return true;
	else {											// * 1.13 *
	pApp_Imp AppImpInst = _AppImpFind();
    		
    		AppImpInst -> ControlList()->Delete ((HANDLE)hControl);
		return hControl = 0, false;
	}
}

//
// Code from _inline.cxx 
//


MultiLineEdit_Imp ::  MultiLineEdit_Imp ( pControl req,  pDWind_Imp parent, ResID id )
:	Edit_Imp(req,  parent, id )
{}

SingleLineEdit_Imp ::  SingleLineEdit_Imp ( pControl req,  pDWind_Imp parent, ResID id )
:	Edit_Imp(req,  parent, id )
{}

FixedText_Imp ::  FixedText_Imp ( pControl req,  pDWind_Imp parent, ResID id )
:	TextControl_Imp(req,  parent, id )
{ }

 VScrollB_Imp :: 	VScrollB_Imp ( pControl req, pDWind_Imp parent, ResID id ) 
: ScrollB_Imp(req, parent, id ) 
{}

 VScrollB_Imp :: 	VScrollB_Imp (  pControl req, pWind_Imp parent, CvID UsrID, Point p, Dimension d)
: ScrollB_Imp(req,parent,UsrID, p, d) 
{ SetStyle(SBS_VERT); }

 HScrollB_Imp ::	HScrollB_Imp ( pControl req, pDWind_Imp parent, ResID id) 
: ScrollB_Imp(req, parent, id ) 
{}

 HScrollB_Imp ::	HScrollB_Imp (  pControl req, pWind_Imp parent, CvID UsrID, Point p, Dimension d) 
: ScrollB_Imp(req,parent,UsrID, p, d) 
{ SetStyle(SBS_HORZ); }

 WndVScrollB_Imp :: WndVScrollB_Imp( pControl req , pWind_Imp parent)
: WndScrollB_Imp( req, parent) 
{ SBType =SB_VERT; }

 WndHScrollB_Imp :: WndHScrollB_Imp(  pControl req , pWind_Imp parent)
: WndScrollB_Imp( req, parent) 
{ SBType =SB_HORZ; }

Button_Imp :: ~ Button_Imp () {}

CheckBox_Imp :: ~ CheckBox_Imp() {}


HScrollB_Imp :: ~ HScrollB_Imp() {}

VScrollB_Imp :: ~ VScrollB_Imp() {}

FixedIcon_Imp :: ~FixedIcon_Imp() {}

FixedText_Imp :: ~ FixedText_Imp() {}

PushButton_Imp :: ~ PushButton_Imp() {}

WndScrollB_Imp :: ~ WndScrollB_Imp() {}

WndHScrollB_Imp :: ~ WndHScrollB_Imp() {}

WndVScrollB_Imp :: ~ WndVScrollB_Imp() {}


RadioButton_Imp :: ~ RadioButton_Imp() {}

TextControl_Imp :: ~ TextControl_Imp() {}

MultiLineEdit_Imp :: ~ MultiLineEdit_Imp() {}

SingleLineEdit_Imp :: ~ SingleLineEdit_Imp() {}

Edit_Imp :: ~ Edit_Imp () {}

HBRUSH	Control_Imp ::SetColors (HDC bkDC, uint)
{
pApp_Imp AppImpInst = _AppImpFind();	

	if (ControlBackground) {
	HBRUSH hBr = CV_RunTime :: Brush_hBrush(ControlBackground);
	
		LogicalBrush lbb(hBr);
		SetBkColor(bkDC, lbb.GetColor());
		if (!CV_RunTime :: Brush_isStock(ControlBackground)) {
			UnrealizeObject ( hBr );
		
		Point p;
		
			ClientToScreen (hControl, (POINT *)&p);
#if !defined(WIN32)
			SetBrushOrg (bkDC, p.X(), p.Y());
#else
			SetBrushOrgEx (bkDC, p.X(), p.Y(), NULL);
#endif
		}
		SetTextColor(bkDC, AppImpInst -> GetTextColor());
		return hBr;
	} else
		// Control background is default
	{
		SetBkColor(bkDC, AppImpInst -> GetBackColor());
		return AppImpInst -> GetDefBackBrush();
	}
}

HBRUSH		ScrollB_Imp ::SetColors(HDC bkDC, uint)
{
	if (ControlBackground) {
	HBRUSH hBr = CV_RunTime :: Brush_hBrush(ControlBackground);

		LogicalBrush lbb(hBr);
		SetBkColor(bkDC, GetSysColor(COLOR_CAPTIONTEXT));
		if (!CV_RunTime :: Brush_isStock(ControlBackground)) {
		Point p;
		
			ClientToScreen ( hControl, (POINT *)&p );
			UnrealizeObject ( hBr );
#if !defined(WIN32)
			SetBrushOrg (bkDC, p.X(), p.Y());
#else
			SetBrushOrgEx (bkDC, p.X(), p.Y(), NULL);
#endif
		}
		SetTextColor(bkDC, GetSysColor(COLOR_WINDOWFRAME));
		return hBr;
	} else {
	pApp_Imp AppImpInst = _AppImpFind();	
	
		SetBkColor (bkDC, AppImpInst -> GetBackColor());
		return AppImpInst -> GetDefBackBrush();
	}
}

HBRUSH		TextControl_Imp ::SetColors(HDC bkDC, uint )
{ 
	HBRUSH hBr;
	pApp_Imp AppImpInst = _AppImpFind();	

	if (ManageColor)
		SetTextColor(bkDC, txtColor);
	else
		SetTextColor(bkDC, AppImpInst -> GetTextColor());

	if (ControlBackground)
		{
		hBr = CV_RunTime :: Brush_hBrush(ControlBackground);
		LogicalBrush lbb(hBr);
		SetBkColor(bkDC, lbb.GetColor());
		if (!CV_RunTime :: Brush_isStock(ControlBackground))
			{
			UnrealizeObject ( hBr );
			Point p;
			ClientToScreen ( hControl, (POINT *)&p );
#if !defined(WIN32)
			SetBrushOrg (bkDC, p.X(), p.Y());
#else
			SetBrushOrgEx (bkDC, p.X(), p.Y(), NULL);
#endif
			}
			return hBr;
		}
	else
	{
		SetBkColor(bkDC, AppImpInst -> GetBackColor());
		return AppImpInst -> GetDefBackBrush();
	}
}

HBRUSH		Button_Imp ::SetColors(HDC hDC, uint type)
	{ return TextControl_Imp :: SetColors(hDC, type); }

HBRUSH		PushButton_Imp :: SetColors(HDC hDC, uint type)
	{ return TextControl_Imp :: SetColors(hDC, type); }

HBRUSH		Edit_Imp :: SetColors(HDC hDC, uint type)
	{ return TextControl_Imp :: SetColors(hDC, type); }


// #HK940125: GaugeBox --------------------------------------------------------
extern "C" {
	#include <zyzgauge.h>
}

GaugeBox_Imp :: GaugeBox_Imp (pControl req, pDWind_Imp parent, ResID id)
	      : TextControl_Imp (req,  parent, id )
{
}

GaugeBox_Imp :: GaugeBox_Imp (pControl req, pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char *pIniText)
	      : TextControl_Imp (req,  parent, UsrID, where, size, (const char *)CTRL_Gauge)
{
	if (pIniText) SetText (pIniText);
}


void	GaugeBox_Imp :: SetRange (short iRange)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETRANGE, iRange, 0);
}

void	GaugeBox_Imp :: SetPosition (short iPos)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETPOSITION, iPos, 0);
}

void	GaugeBox_Imp :: SetOrientation (short iOrient)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETORIENTATION, iOrient, 0);
}

void	GaugeBox_Imp :: SetDeltaPos (short iDelta)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETDELTAPOS, iDelta, 0);
}

void	GaugeBox_Imp :: SetFColor (Color C)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETFGCOLOR, 0, *(ulong *)&C);
}

void	GaugeBox_Imp :: SetBkColor (Color C)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETBKCOLOR, 0, *(ulong *)&C);
}

void 	GaugeBox_Imp :: Set3DWidth (short iWidth)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETWIDTH3D, iWidth, 0);
}

void 	GaugeBox_Imp :: SetBezelFace (short iWidth)
{
	if (ValidateControl())
		SendMessage (Handle (), ZYZG_SETBEZELFACE, iWidth, 0);
}

	
short	GaugeBox_Imp :: GetRange (void)
{
	if (ValidateControl())
		return short(SendMessage (Handle (), ZYZG_GETRANGE, 0, 0));
		
return -1;
}

short	GaugeBox_Imp :: GetPosition (void)
{
	if (ValidateControl())
		return short(SendMessage (Handle (), ZYZG_GETPOSITION, 0, 0));
		
return -1;
}

short	GaugeBox_Imp :: GetOrientation (void)
{
	if (ValidateControl())
		return short(SendMessage (Handle (), ZYZG_GETORIENTATION, 0, 0));
		
return -1;
}

Color	GaugeBox_Imp :: GetFColor (void)
{
	if (ValidateControl()) {
	LRESULT lResult = SendMessage (Handle (), ZYZG_GETFGCOLOR, 0, 0);
	
		return *(Color *)&lResult;
	}
		
return Colors (BLACK);
}

Color	GaugeBox_Imp :: GetBkColor (void)
{
	if (ValidateControl()) {
	LRESULT lResult = SendMessage (Handle (), ZYZG_GETBKCOLOR, 0, 0);
	
		return *(Color *)&lResult;
	}
		
return Colors (BLACK);
}

short	GaugeBox_Imp :: Get3DWidth (void)
{
	if (ValidateControl())
		return short(SendMessage (Handle (), ZYZG_GETWIDTH3D, 0, 0));
		
return -1;
}

short	GaugeBox_Imp :: GetBezelFace (void)
{
	if (ValidateControl())
		return short(SendMessage (Handle (), ZYZG_GETBEZELFACE, 0, 0));
		
return -1;
}

