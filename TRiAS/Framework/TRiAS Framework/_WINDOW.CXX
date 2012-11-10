/* $Header:   G:/cv.win/pvcs/commonvu/src/_window.cxv   1.12   24 Oct 1991 19:28:22   RONAN  $
 *
 * 	_ W I N D O W . C X X
 *	
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Window class member functions ( Requestor functions)
 *
 *	Modification log:
 *	1.1	06sep89	ferg	Original version. Carved out of original _window.cxx
 *						which is now _wind_im.cxx and contains the Window 
 *						implementor functions.
 */

#include "tfrmpre.hxx"

// ------------------------------------------------------------------------
// 
//	Window default constructor does nothing since it should never be called 
//	directly by the client.
//
// ------------------------------------------------------------------------


void	 _DLLENTRY Window::   Show	( ShowState state )
{
	((pWind_Imp)ec_Imp) -> Show ( state );
}

void	 _DLLENTRY Window ::   	Hide ()
{
	((pWind_Imp)ec_Imp) -> Hide ();
}

void	 _DLLENTRY Window ::   	Enable ()
{
	((pWind_Imp)ec_Imp) -> Enable (1);
}

void	 _DLLENTRY Window ::    	Disable ()
{
	((pWind_Imp)ec_Imp) -> Enable(0);
}


// ------------------------------------------------------------------------
//
//	Dispatcher and Event handling members
//
// ------------------------------------------------------------------------

LRESULT _DLLENTRY Window :: ForwardEvent (Event e)
{
	return ::SendMessage (Handle(), CV_RunTime::Event_wMsg(e),
		CV_RunTime::Event_wParam(e),CV_RunTime::Event_lParam(e));
}

LRESULT _DLLENTRY Window :: ForwardEvent (UINT wMsg, WPARAM wParam , LPARAM lParam)
{
	return ::SendMessage (Handle(), wMsg, wParam, lParam);
}

void _DLLENTRY Window::PostEvent (Event e)		// #HK960915
{
	::PostMessage (Handle(), CV_RunTime::Event_wMsg(e),
		CV_RunTime::Event_wParam(e),CV_RunTime::Event_lParam(e));
}

void _DLLENTRY Window::PostEvent (UINT wMsg, WPARAM wParam , LPARAM lParam)		// #HK970903
{
	::PostMessage (Handle(), wMsg, wParam, lParam);
}


void	 _DLLENTRY Window::    WindowInit	( Event  )
{
}


// Mouse Event Handling members

void	 _DLLENTRY Window::    MouseButtonDn	( MouseEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    MouseButtonUp	( MouseEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    MouseButtonDblClk	( MouseEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    MouseMove	( MouseEvt e )
{
		Default ((Event&)e );
}


void	 _DLLENTRY Window::    MouseDrag	( MouseEvt e )
{
		Default ((Event&)e );
}


// Keyboard Event Handlers

void	 _DLLENTRY Window::    KeyDown	( KeyEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    KeyUp	( KeyEvt e )
{
	Default ((Event&)e );
}


// Window status Event handlers

void	 _DLLENTRY Window::    Activate	( Event e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window ::    DeActivate	( Event e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window ::    FocusChange	( FocusChangeEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    ReSize	( ReSizeEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    Move	( MoveEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    Expose	( ExposeEvt e )
{
	Default ((Event&)e );
}


BOOL	 _DLLENTRY Window::    QueryClose	( Event  )
{
	return	TRUE;
}


void	 _DLLENTRY Window::    Close	( Event  )
{
	//	Dont call for WINDOWS
}


// Menu Event handling menbers

void	 _DLLENTRY Window::    MenuInit	( MenuInitEvt e )
{
	((pWind_Imp)ec_Imp) ->MenuHandler(Wind_Imp :: MhInit, (Event&)e);
}

void	 _DLLENTRY Window::    MenuSelect	( MenuSelectEvt e )
{
	((pWind_Imp)ec_Imp) ->MenuHandler(Wind_Imp :: MhSelect, (Event&)e);
}

void	 _DLLENTRY Window::    MenuCommand	( MenuCommandEvt e)
{
	((pWind_Imp)ec_Imp) ->MenuHandler(Wind_Imp :: MhCommand, (Event&)e);
}

void	 _DLLENTRY Window::    VertScroll	( ScrollEvt e )
{
        if (e.GetScrollBar())
		e.GetScrollBar()->SetThumbPos(e.GetPos());
}

void	 _DLLENTRY Window::    HorizScroll	( ScrollEvt e )
{
        if (e.GetScrollBar())
		e.GetScrollBar()->SetThumbPos(e.GetPos());
}

void	 _DLLENTRY Window::    ButtonClick	( ControlEvt e )
{
//	Default ((Event&)e );
	((pWind_Imp)ec_Imp) ->ButtonClick(e);
}


void	 _DLLENTRY Window::    ButtonDblClk	( ControlEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    EditChange	( ControlEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    EditScroll	( ControlEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    EditFocusChg	( EditFocusChgEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    ListBoxClk	( ControlEvt e )
{
	Default ((Event&)e );
}


void	 _DLLENTRY Window::    ListBoxSel	( ControlEvt e )
{
	Default ((Event&)e );
}

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
void	 _DLLENTRY Window::    SetStyle	( ulong style, CVOnOff onoff )
#else
void	 _DLLENTRY Window::    SetStyle	( ulong style, OnOff onoff )
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
{
	((pWind_Imp)ec_Imp) -> SetStyle ( style, onoff );
}


void	 _DLLENTRY Window::    Update	( )
{
	((pWind_Imp)ec_Imp) -> Update ( );
}


void	 _DLLENTRY Window::    RePaint	( )
{
	((pWind_Imp)ec_Imp) -> RePaint () ;
}

void	 _DLLENTRY Window::    RePaintRect	( Rectangle r)
{
	((pWind_Imp)ec_Imp) -> RePaintRect ( r );
}


Point	 _DLLENTRY Window::    ChangePosition ( Point origin )
{
	return ((pWind_Imp)ec_Imp) -> ChangePosition ( origin );
}


Dimension	 _DLLENTRY Window::    ChangeSize ( Dimension size )
{
	return ((pWind_Imp)ec_Imp) -> ChangeSize ( size );
}


void	 _DLLENTRY Window::    CanvasErase	()
{
	((pWind_Imp)ec_Imp) -> CanvasErase ();
}

void	 _DLLENTRY Window::    CanvasErase	(Rectangle &rc)
{
	((pWind_Imp)ec_Imp) -> CanvasErase (&rc);
}

Dimension	 _DLLENTRY Window::    TextSize ( const char* what )
{
	return ((pWind_Imp)ec_Imp) -> TextSize ( what );
}


void	 _DLLENTRY Window::    ToTop	()
{
	((pWind_Imp)ec_Imp) -> ToTop ();
}


Rectangle	 _DLLENTRY Window::    CanvasRect	()
{
	return	((pWind_Imp)ec_Imp) -> CanvasRect ();
}


Rectangle	 _DLLENTRY Window::    WindowRect	()
{
	return	((pWind_Imp)ec_Imp) -> WindowRect ();
}


BOOL	 _DLLENTRY Window::    isIconic	()
{
	return ((pWind_Imp)ec_Imp) -> isIconic();
}


BOOL	 _DLLENTRY Window::    isVisible	()
{
	return ((pWind_Imp)ec_Imp) -> isVisible ();
}


BOOL	 _DLLENTRY Window::    isZoomed	()
{
	return ((pWind_Imp)ec_Imp) -> isZoomed();
}


#if !defined(_TRIAS_OLDIMPLEMENTATION2)
void	 _DLLENTRY Window::    	MouseTrap ( CVOnOff state )
#else
void	 _DLLENTRY Window::    	MouseTrap ( OnOff state )
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
{
	((pWind_Imp)ec_Imp)	->MouseTrap ( state );
}

pPointer	 _DLLENTRY Window::    ChangePointer	( pPointer new_Pointer )
{
	return ((pWind_Imp)ec_Imp) -> ChangePointer ( new_Pointer );
}


pBrush	 _DLLENTRY Window::    ChangeBackground ( pBrush new_Background )
{
	return ((pWind_Imp)ec_Imp) -> ChangeBackground ( new_Background );
}

pBrush	 _DLLENTRY Window::    ChangeBrush	( pBrush new_Brush )
{
	return ((pWind_Imp)ec_Imp) -> ChangeBrush ( new_Brush );
}


pFont	 _DLLENTRY Window::    ChangeFont	( pFont new_Font )
{
	return ((pWind_Imp)ec_Imp) -> ChangeFont ( new_Font );
}


pMenu	 _DLLENTRY Window::    ChangeMenu	( pMenu new_Menu )
{
	return ((pWind_Imp)ec_Imp) -> ChangeMenu ( new_Menu );
}


pPen	 _DLLENTRY Window::    ChangePen	( pPen new_Pen )
{
	return ((pWind_Imp)ec_Imp) -> ChangePen ( new_Pen );
}


pAccel	 _DLLENTRY Window::    ChangeAccel	( pAccel new_Accel )
{
	return ((pWind_Imp)ec_Imp) -> ChangeAccel ( new_Accel );
}

// Canvas Rendering member functions

void	 _DLLENTRY Window::    TextPrint	( const char* what, Point where )
{
	((pWind_Imp)ec_Imp) -> TextPrint ( what, where );
}


Point	 _DLLENTRY Window::    MoveTo	( Point where )
{
	return ((pWind_Imp)ec_Imp) -> MoveTo ( where );
}


void	 _DLLENTRY Window::    LineTo	( Point where )
{
	((pWind_Imp)ec_Imp) -> LineTo ( where );
}


void	 _DLLENTRY Window::    PaintRectangle	( Rectangle rect, PaintMode pm )
{
	((pWind_Imp)ec_Imp) -> PaintRectangle ( rect, pm );
}

void  _DLLENTRY Window ::     Draw ( pDrawObject pDO )
{
	((pWind_Imp)ec_Imp) -> Draw ( pDO );
}

void  _DLLENTRY Window ::     DrawEx (pDrawObject pDO, DWORD dwData)
{
	((pWind_Imp)ec_Imp) -> DrawEx (pDO, dwData);
}

void	 _DLLENTRY Window::    SetCaption	( const char* caption )
{
	((pAWind_Imp)ec_Imp) ->SetCaption (caption, true);

}

void	 _DLLENTRY Window::UpdateCaption (const char* caption)
{
	((pAWind_Imp)ec_Imp) ->SetCaption (caption, false);
}

void	 _DLLENTRY Window::  Scroll( Dimension d, Rectangle rect, BOOL clip )
{
	((pWind_Imp)ec_Imp) ->Scroll(d, rect, clip);
}

_DLLENTRY Window :: ~Window()
{
	if ( ec_Imp )
		delete ec_Imp;
	ec_Imp = 0;
}

_DLLENTRY Window :: Window()
{
}

// Query functions
Point	 _DLLENTRY Window::    GetPosition (  )
{
	return ((pWind_Imp)ec_Imp) -> GetPosition (  );
}



Dimension	 _DLLENTRY Window::    GetSize (  )
{
	return ((pWind_Imp)ec_Imp) -> GetSize ( );
}

pchar	 _DLLENTRY Window::    GetCaption	( pchar buffer, int len )
{
	return ((pAWind_Imp)ec_Imp) ->GetCaption ( buffer, len );

}


pPointer	 _DLLENTRY Window::    GetPointer	(  )
{
	return ((pWind_Imp)ec_Imp) -> GetPointer (  );
}


pBrush	 _DLLENTRY Window::    GetBackground (  )
{
	return ((pWind_Imp)ec_Imp) -> GetBackground (  );
}

pBrush	 _DLLENTRY Window::    GetBrush	(  )
{
	return ((pWind_Imp)ec_Imp) -> GetBrush ( );
}


pFont	 _DLLENTRY Window::    GetFont	(  )
{
	return ((pWind_Imp)ec_Imp) -> GetFont (  );
}


pMenu	 _DLLENTRY Window::    GetMenu	(  )
{
	return ((pWind_Imp)ec_Imp) -> GetMenu (  );
}


pPen	 _DLLENTRY Window::    GetPen	( )
{
	return ((pWind_Imp)ec_Imp) -> GetPen ( );
}

pWindow	 _DLLENTRY Window::    GetParent	( )
{
	return ((pWind_Imp)ec_Imp) -> GetParent( );
}



pAccel	 _DLLENTRY Window::    GetAccel	(  )
{
	return ((pWind_Imp)ec_Imp) -> GetAccel (  );
}

void	 _DLLENTRY Window::    SetFocus	(  )
{
	((pWind_Imp)ec_Imp) -> SetFocus (  );
}

void	_DLLENTRY	Window :: TextPrintf ( Point where,const char *what,  ... )
{
	((pWind_Imp)ec_Imp) -> TextPrintf ( where, what,  (const char *)(((char*)(&what)) + sizeof(what)) );
}

void	_DLLENTRY	Window :: TextPrintf ( const char *what,  ... )
{
	((pWind_Imp)ec_Imp) -> TextPrintf (  what,  (const char *)(((char*)(&what)) + sizeof(what)) );
}

// #HK940119 ------------------------------------------------------------------
HDC _DLLENTRY 	Window :: SetDrawTarget (HDC hDC)
{
	return ((pWind_Imp)ec_Imp) -> 	SetDrawTarget (hDC);
}


HDC _DLLENTRY 	Window :: GetDrawTarget (void)
{
	return ((pWind_Imp)ec_Imp) -> 	GetDrawTarget ();
}


HWND _DLLENTRY Window :: Detach (void)
{
	return ((pWind_Imp)ec_Imp) -> 	Detach();
}


_DLLENTRY Window :: Window (HWND hWnd)
{
	ec_Imp = new Wind_Imp (this, hWnd);
}

// #HK940711 -----------------------------------------------------------------
pWndHorzScroll   _DLLENTRY Window::  EnableHScroll ( BOOL state )
{
	return ((pWind_Imp)ec_Imp) ->EnableHScroll( state ) ;
}

pWndVertScroll   _DLLENTRY Window::  EnableVScroll ( BOOL state)
{
	return ((pWind_Imp)ec_Imp) -> EnableVScroll ( state ) ;

}
// #HK940711 -----------------------------------------------------------------

// #HK960320 -----------------------------------------------------------------
BOOL _DLLENTRY Window::DrawCallUp (DrawObject *pDO, BOOL fForce)
{
	return ((pWind_Imp)ec_Imp) -> DrawCallUp (pDO, fForce);
}
// #HK960320 -----------------------------------------------------------------

BOOL _DLLENTRY Window::DestroyWindow (void)
{
	return ((pWind_Imp)ec_Imp) -> DestroyWindow();
}
