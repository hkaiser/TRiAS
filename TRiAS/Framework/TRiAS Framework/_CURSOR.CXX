/* $Header:   G:/cv.win/pvcs/commonvu/src/_cursor.cxv   3.0   25 Mar 1992 15:19:44   RONAN  $
 *
 * _ C U R S O R . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 * Mod Logs:
 *
 *	0.0	nc	25Apr90 Created 
 */

#include "tfrmpre.hxx"

 _DLLENTRY Cursor::   Cursor	( pWindow Win, Dimension size, BOOL greyed )
{
	cursor_Imp = new Cursor_Imp(CV_RunTime :: pWindow_to_pImp(Win),size,greyed);
}


 _DLLENTRY Cursor::   Cursor	( pWindow Win, pBitmap Bm )
{
	cursor_Imp = new Cursor_Imp(CV_RunTime :: pWindow_to_pImp(Win),Bm);
}

 _DLLENTRY Cursor::   ~Cursor	()
{
	delete	cursor_Imp;
}


void	 _DLLENTRY Cursor::   Hide	()
{
	cursor_Imp->Hide();
	
}


void	 _DLLENTRY Cursor:: Show	()
{
	cursor_Imp->Show();
	
}

/****
bool	 _DLLENTRY Cursor:: isVisible	()
{
	return cursor_Imp->isVisible();
	
}	// End of "Cursor" FUNCTION "isVisible"
****/

Point	 _DLLENTRY Cursor:: GetPos()
{
	return	cursor_Imp->GetPos();
	
}


void	 _DLLENTRY Cursor:: ChangePos	( Point Pt )
{
	cursor_Imp->ChangePos(Pt);
	
}


uint	 _DLLENTRY Cursor:: GetBlinkTime	()
{
	return	cursor_Imp->GetBlinkTime();
	
}


void	 _DLLENTRY Cursor:: ChangeBlinkTime	( uint MSeconds )
{
	cursor_Imp->ChangeBlinkTime(MSeconds);
	
}

HWND	 _DLLENTRY Cursor:: Handle ( Service s_ID ) 
{
	return cursor_Imp -> Handle(s_ID);
}	


