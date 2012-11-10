/* $Header:   G:/cv.win/pvcs/commonvu/src/_dialog.cxv   3.0   25 Mar 1992 15:19:48   RONAN  $
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
 *	1.1	ferg	15sep89	Original Version.
 */

#include "tfrmpre.hxx"
#include	<_link.hxx>

_DLLENTRY DialogWindow ::   DialogWindow	( pWindow parent, ResID RscID, BOOL isModal )
{
	    ec_Imp = new DWind_Imp (this,  (pWind_Imp)(parent ? CV_RunTime :: pWindow_to_pImp(parent) : 0), RscID, isModal );
}

void	 _DLLENTRY DialogWindow::   EndDlg	( int nResult )
{
	((pDWind_Imp)ec_Imp)->EndDlg ( nResult );
}

pFont	 _DLLENTRY DialogWindow::   ChangeFont	(pFont font, BOOL global )
{
	 return ((pDWind_Imp)ec_Imp)->ChangeFont ( font, global );
}	

int		 _DLLENTRY DialogWindow::   Result	(  )
{
	 return	((pDWind_Imp)ec_Imp)->Result (  );
}	

///////////////////////////////////////////////////////////////////////////////
// #HK970116
_DLLENTRY BOOL DialogWindow::PreTranslateMsg (MSG *pMsg)
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	// for performance: maybe translate dialog key
		return ::IsDialogMessage(CV_RunTime::Window_Handle((pWind_Imp)ec_Imp), pMsg);

	return FALSE;	
}

 _DLLENTRY ModeLessDialog::   ModeLessDialog	( pWindow parent, ResID RscID )
{
	ec_Imp = new DWind_Imp ( this, (pWind_Imp)(parent ? CV_RunTime :: pWindow_to_pImp(parent) : 0), RscID, FALSE );
}

 _DLLENTRY DialogWindow:: DialogWindow () 
{
}

_DLLENTRY DialogWindow:: ~DialogWindow () 
{
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

_DLLENTRY ModeLessDialog:: ~ModeLessDialog () 
{
}
