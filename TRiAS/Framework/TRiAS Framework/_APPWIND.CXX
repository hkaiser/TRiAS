/*    PortTool v2.2     _appwind.cxx          */

/* $Header:   G:/cv.win/pvcs/commonvu/src/_appwind.cxv   3.0.1.0   14 Jul 1992 11:48:16   RONAN  $
 *
 *	_ a p p w i n d . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *	Mods log:
 *	1.1	14sep89	ferg	Original Version.
 */

#include "tfrmpre.hxx"

#include	<_link.hxx>



_DLLENTRY TopAppWindow :: TopAppWindow (pAppWindow copy_from) 
{

	if ( copy_from)
		ec_Imp = new TAWind_Imp( this, (pAWind_Imp)CV_RunTime :: pWindow_to_pImp(copy_from) );
	else
		ec_Imp = new TAWind_Imp( this, (pAWind_Imp )0);

	EnableSysMenu();
	EnableBorder();
	EnableMinBox();
	EnableMaxBox();
}

_DLLENTRY TopAppWindow :: TopAppWindow (long dwExStyle, const char *pcClassName) 
{
	ec_Imp = new TAWind_Imp (this, dwExStyle, (char *)pcClassName);
	EnableSysMenu();
	EnableBorder();
	EnableMinBox();
	EnableMaxBox();
}

_DLLENTRY ChildAppWindow::  ChildAppWindow	( pWindow parent, pAppWindow copy_from , BOOL isWindowManaged)
{
	if (isWindowManaged && CV_RunTime :: Window_isMDIWindow(CV_RunTime :: pWindow_to_pImp(parent)))
		{
		ec_Imp = new DocWind_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), 
						copy_from ? ((pAWind_Imp)CV_RunTime :: pWindow_to_pImp(copy_from)) : 0);
		EnableSysMenu();
		EnableBorder();
		EnableMinBox();
		EnableMaxBox();
		}
	else
		{
		ec_Imp = new CAWind_Imp( this, 
								CV_RunTime :: pWindow_to_pImp(parent), 
								copy_from ? (pAWind_Imp)CV_RunTime :: pWindow_to_pImp(copy_from) : 0);
		if (isWindowManaged)
			EnableBorder(AppWindow::NonSizingBorder);
		}
}


// #HK930803 ------------------------------------------------------------------
// erlaubt die vorgabe von FensterKlasse und erweitertem Style ----------------
_DLLENTRY ChildAppWindow :: ChildAppWindow (pWindow parent, pchar pClassName, 
					    long dwExStyle)
{
	ec_Imp = new CAWind_Imp (this, CV_RunTime :: pWindow_to_pImp (parent), 
				 pClassName, dwExStyle);
}
// ----------------------------------------------------------------------------

// #HK960220 ------------------------------------------------------------------
// erlaubt die vorgabe von FensterKlasse und erweitertem Style und ChildID
_DLLENTRY ChildAppWindow :: ChildAppWindow (
		pWindow parent, UINT uiID, pchar pClassName, long dwExStyle)
{
	ec_Imp = new CAWind_Imp (this, CV_RunTime :: pWindow_to_pImp (parent), 
				 pClassName, dwExStyle, uiID);
}
// ----------------------------------------------------------------------------

void	  _DLLENTRY AppWindow::  EnableBorder	(  BorderType type )
{
        ((pAWind_Imp)ec_Imp) ->EnableBorder ( type );
}

void	  _DLLENTRY AppWindow::  EnableMinBox ( BOOL state )
{
	((pAWind_Imp)ec_Imp) ->EnableMinBox (  state );

}

void	  _DLLENTRY AppWindow::  EnableMaxBox ( BOOL state )
{
	((pAWind_Imp)ec_Imp) ->EnableMaxBox (  state );
}

pSysMenu	  _DLLENTRY AppWindow::  EnableSysMenu	( BOOL state)
{
	return ((pAWind_Imp)ec_Imp) ->EnableSysMenu( state ) ;

}

	

void	  _DLLENTRY AppWindow::  SetIcon	( pIcon icon )
{
	((pAWind_Imp)ec_Imp) ->SetIcon ( icon );
}


void	  _DLLENTRY AppWindow::  SetPointer	( pPointer pointer )
{
	((pAWind_Imp)ec_Imp) ->SetPointer ( pointer );
}

_DLLENTRY TopAppWindow :: ~TopAppWindow()
{
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

_DLLENTRY ChildAppWindow :: ~ ChildAppWindow()
{
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

_DLLENTRY AppWindow :: AppWindow()
{
}

_DLLENTRY AppWindow :: ~ AppWindow()
{
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}
