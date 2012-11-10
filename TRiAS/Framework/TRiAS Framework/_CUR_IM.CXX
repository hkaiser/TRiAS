/* $Header:   G:/cv.win/pvcs/commonvu/src/_cur_im.cxv   3.0.1.0   14 Jul 1992 11:49:04   RONAN  $
 *
 *	_ c u r _ i m . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.1	jk		02dec88	Fast Compile defines added.
 *  0.2 rs      Mapping mode compatibility 
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *  1.2 hl		09jan89	the Cursor class contains pWin instead of hCursor
 *  1.3 hl		09jan89	ChangePos & GetPos use Client coordinates
 *  1.4 hl		15feb90		invert Width & Height when calling 
 *				CreateCaret in the constructor
 *					Cursor class contains CursHeight used
 *				in ChangePos & GetPos.
 *	1.5 rs		21Dec89 GetExposedArea returns wrong rectangle
 *	1.6 hl		16feb90 isShiftButton & isControlButton work for
 *				for all Mouse events						
 *	2.0 nc		19Jun90 rs from nc Apr90 - Hiding
 *	2.1 pc		23Jun92 Changed the initial ChangePos from (0,0) to (0,-1)
 *				to overcome problems with the mapping mode.
 *	2.2 pc		23Jun92 Added the created = true assignment, to allow for
 *				ChangePos to work correctly (it updates only if
 *				created == true).
 *	2.3 pc		29Jun92	Added ChangePos after the creation to ensure that
 *				the cursor is always placed in the same position
 *				as it was when the window lost the focus (the initial
 *				position in the bottome left corner).
 */

#include "tfrmpre.hxx"

Cursor_Imp::  Cursor_Imp	( pWind_Imp Win, Dimension d, BOOL g )
{
HWND hCursor	= CV_RunTime :: EventContext_hEContext ( Win );	// * 1.2 *
Cursor_Imp *old_cursor;

	pWin = Win;
	size = d;
	greyed = g;
	created = false;
	visible = false;
	bitmap = NULL ;
    	ChangePos( Point(0,0 )) ;

// If Window already has caret destroy it
	if (old_cursor = (pWin -> GetWinCursor()))
		old_cursor -> Update(false);
	
// If Window has focus create caret now
	pWin->SetWinCursor(this);
	if (GetFocus() == hCursor)	
		Update(true);
}	// End of "Cursor_Imp" CONSTRUCTOR "(pWindow,Dimension,bool)"



Cursor_Imp::  Cursor_Imp	( pWind_Imp Win, pBitmap Bm )
{
HWND hCursor	= CV_RunTime :: EventContext_hEContext ( Win );	// * 1.2 *
Cursor_Imp *old_cursor;

	pWin = Win;
	size = Bm->GetSize(); 
	visible = false;
	created = false;
	bitmap = CV_RunTime :: pBitmap_to_pImp (Bm) ;
    	ChangePos( Point(0,0 )) ;

// If Window already has caret destroy it
	if (old_cursor = (pWin -> GetWinCursor()))
		old_cursor -> Update(false);

// If Window has focus create caret now
	pWin->SetWinCursor(this);
	if (GetFocus() == hCursor)	
		Update(true);
}	// End of "Cursor_Imp" CONSTRUCTOR "(pWindow,pBitmap)"


void	Cursor_Imp::  Hide	()
{
	if (created && visible)
		HideCaret(pWin->Handle());
	visible = false;
}	// End of "Cursor_Imp" FUNCTION "Hide"

void	Cursor_Imp::  Show	()
{
	if (created && (!visible))
	    ShowCaret (pWin->Handle() );
	visible = true;
}	// End of "Caret" FUNCTION "Show"

void Cursor_Imp :: Update (BOOL creating)
{
// note currently pointer to parent stored may revert back to handle to parent
	if (creating)
		{
		if (!created)
    	{
        	if ( bitmap )
    	    	CreateCaret ( pWin->Handle(), bitmap ->Handle(), 0, 0 );
        	else
	        	CreateCaret ( pWin->Handle(), (HBITMAP)(greyed == true), 
                                	size.Width(), size.Height()); 
			created = true;					// * 2.2
			ChangePos(where);				// * 2.3
    	}
		if (visible)
		    ShowCaret ( pWin->Handle() );
	}
	else
		{
		if (created)
			{
			DestroyCaret();
			created = false;
			}
		}
}

Point	Cursor_Imp::  GetPos()
{
    if ( !created )
    	return where ;

	Point	pt;

	GetCaretPos ( (POINT *)&pt );    // *MAPPING Screen co-ordinates
	pt = CV_RunTime :: DevToLog( pWin, pt);     // * 0.2 * & * 1.3 *
	pt.Y()  = (pt.Y() - size.Height()) + 1;
    return where = pt ;

}	// End of "Cursor_Imp" FUNCTION "GetPos"


void	Cursor_Imp::  ChangePos	( Point Pt )
{
    where = Pt ;
    
    if ( created )
    {
	    Pt.Y() = (Pt.Y() + size.Height() - 1);		// * 1.4 *
    	Pt = CV_RunTime :: LogToDev( pWin, Pt);     // * 0.2 * & * 1.3 *
	    SetCaretPos ( Pt.X (), Pt.Y ());    // *MAPPING Screen co-ordinates
    }
}	// End of "Cursor_Imp" FUNCTION "ChangePos"


uint	Cursor_Imp::  GetBlinkTime	()
{
   	return	GetCaretBlinkTime ();
}	// End of "Cursor_Imp" FUNCTION "GetBlinkTime"


void	Cursor_Imp::  ChangeBlinkTime	( uint MSeconds )
{
	SetCaretBlinkTime ( MSeconds );
}	// End of "Cursor_Imp" FUNCTION "ChangeBlinkTime"

HWND	Cursor_Imp:: Handle (Service ) 	
{ 
	return pWin->Handle(); 
}

Cursor_Imp:: ~Cursor_Imp()
{
	pWin->SetWinCursor(0);
 	if (created)
 		{
 		DestroyCaret();
 		created = false;
 		}
}
