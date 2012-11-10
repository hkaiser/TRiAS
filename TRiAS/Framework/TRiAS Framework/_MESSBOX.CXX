/* $Header:   G:/cv.win/pvcs/commonvu/src/_messbox.cxv   3.0   25 Mar 1992 15:21:10   RONAN  $
 *
 *	_ m e s s b o x . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	2.0		NC	??Jun90		Hidden version.
 */

#include "tfrmpre.hxX"

_DLLENTRY MessBox:: MessBox	( const char* caption, const char* text, pWindow parent )
{
   	messBox_Imp = new MessBox_Imp ( caption, text, parent ? CV_RunTime :: pWindow_to_pImp(parent) : NULL);
}  

_DLLENTRY MessBox:: ~MessBox ()					
{
	if ( messBox_Imp)
		delete messBox_Imp ;
}										

StdMessBoxReply	 _DLLENTRY MessBox:: Show	()
{
	return messBox_Imp -> Show();
}
										
StdMessBox	 _DLLENTRY MessBox:: GetType	()
{
	return	messBox_Imp -> GetType () ;
} 

void	 _DLLENTRY MessBox:: SetType	( StdMessBox type )
{
	messBox_Imp -> SetType ( type ) ;
}


HWND	 _DLLENTRY MessBox::  Handle ( Service  s_ID) 
{
	return messBox_Imp -> Handle(s_ID); 
}	

_DLLENTRY ErrorBox :: ErrorBox ( const char* text, pWindow parent )
    : MessBox(0, text, parent)
{
    SetType(HandIcon);
    messBox_Imp->SetBeep(TRUE);
}

_DLLENTRY InfoBox :: InfoBox (const char* caption, const char* text, pWindow parent )
    :MessBox( caption , text , parent)
{
    SetType(AsteriskIcon | OkayButton);
}


_DLLENTRY WarningBox :: WarningBox (const char* caption, const char* text, pWindow parent )
    :MessBox( caption, text , parent)
{
    SetType(ExclamationIcon | YesNoButtons);
    messBox_Imp->SetBeep(TRUE);
}
