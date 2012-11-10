/* $Header:   G:/cv.win/pvcs/commonvu/src/_editwnd.cxv   3.0   25 Mar 1992 15:20:08   RONAN  $
 *
 *	_ e d i t w n d . c x x 
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	rs      16jan89 Initial development
 *	0.1 rs, nc 	24may90	Hiding of editwindows.
 */

#include "tfrmpre.hxx"

 _DLLENTRY ControlWindow::   ControlWindow ( pControl pctrl )
{
	if (pctrl)
		ec_Imp = new CWind_Imp ( this, pctrl );	
	else
		ec_Imp = 0;											
}

void	 _DLLENTRY ControlWindow::    VertScroll	( ScrollEvt e )
{
	Default ((Event&)e );
}

void	 _DLLENTRY ControlWindow::    HorizScroll	( ScrollEvt e )
{
	Default ((Event&)e );
}

pControl	 _DLLENTRY ControlWindow::   GetControl ( )
{
	return ((pCWind_Imp)ec_Imp)->GetControl();				
}

void  _DLLENTRY ControlWindow::   Expose( ExposeEvt e)
{
	((pCWind_Imp)ec_Imp) -> Expose ( e );
}

void  _DLLENTRY ControlWindow::   Hide ()
{
	GetControl()->Hide();
}

void  _DLLENTRY ControlWindow::   Enable ()
{
	GetControl()->Enable ();
}

void  _DLLENTRY ControlWindow::   Disable ()
{
	GetControl()->Disable ();
}

CvID  _DLLENTRY ControlWindow::   GetID ()
{
	return GetControl()->GetID ();
}

void  _DLLENTRY ControlWindow::   SetFocus ()
{
	GetControl()->SetFocus ();
}

Point  _DLLENTRY ControlWindow::   ChangePosition ( Point p)
{
	return GetControl()->ChangePosition (  p );
}

Dimension  _DLLENTRY ControlWindow::   ChangeSize ( Dimension d)
{
	return GetControl()->ChangeSize ( d );
}



 _DLLENTRY EditWindow::  	EditWindow ( pDialogWindow parent, ResID RscID )
{
	ec_Imp = new EWind_Imp ( this,  parent, RscID );	
}

 _DLLENTRY EditWindow::   EditWindow ( pWindow parent, CvID UsrID, Point p, Dimension d)
: ControlWindow ( (pControl)0 )
{
	ec_Imp = new EWind_Imp (this, parent, UsrID, p, d);	
}

void  _DLLENTRY EditWindow::   SetText ( const char* buf )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->SetText ( buf );
}

void  _DLLENTRY EditWindow::   GetText ( pchar buf , uint max )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->GetText( buf, max );
}

uint  _DLLENTRY EditWindow::    GetTextLen( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	return pC->GetTextLen ( );
}

BOOL  _DLLENTRY EditWindow::    isModified( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	return pC->isModified ( );
}

Selection  _DLLENTRY EditWindow::    GetSelection( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	return pC->GetSelection ( );
}

void  _DLLENTRY EditWindow::    ChangeSelection(Selection s )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->ChangeSelection ( s);
}

void  _DLLENTRY EditWindow::    SetTextLimit( uint n )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->SetTextLimit ( n );
}

void  _DLLENTRY EditWindow::    ReplaceSelected( const char* p )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->ReplaceSelected ( p );
}

void  _DLLENTRY EditWindow::    DeleteSelected(BOOL toClipBoard )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->DeleteSelected ( toClipBoard );
}

uint  _DLLENTRY EditWindow::    GetLine( uint index, pchar buffer, uint nChars )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	return pC->GetLine ( index, buffer, nChars );
}

uint  _DLLENTRY EditWindow::    GetNumLines( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	return pC->GetNumLines ( );
}

void  _DLLENTRY EditWindow::    ScrollVertical( uint n)
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->ScrollVertical ( n );
}

void  _DLLENTRY EditWindow::    ScrollHoriz( uint n )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->ScrollHoriz ( n);
}

void  _DLLENTRY EditWindow::    PageUp( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->PageUp ( );
}

void  _DLLENTRY EditWindow::    PageDown( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->PageDown ( );
}

void  _DLLENTRY EditWindow::    LineUp( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->LineUp ( );
}

void  _DLLENTRY EditWindow::    LineDown( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	pC->LineDown ( );
}

BOOL  _DLLENTRY EditWindow::    Undo( )
{
	MultiLineEdit *  pC = (MultiLineEdit * )GetControl();
	return pC->Undo ( );
}

_DLLENTRY ControlWindow :: ControlWindow () {
}

_DLLENTRY ControlWindow :: ~ControlWindow () {
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

BOOL _DLLENTRY ControlWindow :: FInit (void)
{
	if (ec_Imp) 
		return ((pCWind_Imp)ec_Imp) -> FInit();

return false;
}


_DLLENTRY EditWindow :: ~EditWindow () {
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}


