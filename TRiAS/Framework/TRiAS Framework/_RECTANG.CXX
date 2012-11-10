/* $Header:   G:/cv.win/pvcs/commonvu/src/_rectang.cxv   3.0   25 Mar 1992 15:21:30   RONAN  $
 *
 *	_ R E C T A N G . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0 jk		29nov88 ------ Milestone 2A. Beta 2A ship date. ------
 *	0.1 jk		02dec88 Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *  1.2 hl		11Jan90 Union
 */

#include "tfrmpre.hxx"

// START_C_FUNCTIONS
// extern	bool	 pascal	PtInRect ( rRectangle, Point );
// END_C_FUNCTIONS

_DLLENTRY Rectangle::   Rectangle	( Point origin, Dimension size )
{
	top = origin.Y();
	left = origin.X();
	bottom 	= top  - size.Height ();
	right 	= left  + size.Width ();
}	


Rectangle	 _DLLENTRY Rectangle::   Union	( rRectangle the_other )
{
	Rectangle	rect;

	Rectangle* rtmp = (Rectangle*)&the_other;

	if (rtmp -> top < rtmp -> bottom)	// * 1.2 *
	{
		int tmp = rtmp -> top;
		rtmp -> top = rtmp -> bottom;
		rtmp -> bottom = tmp;
	}
  
	rect.Top() = ( top > rtmp ->Top()) ?  top : rtmp ->Top() ;
	rect.Bottom() = ( bottom > rtmp ->Bottom()) ?  rtmp ->Bottom() : bottom ;
	rect.Left() = ( left > rtmp ->Left()) ?  rtmp ->Left() : left ;
	rect.Right() = ( right > rtmp ->Right()) ?  right : rtmp ->Right() ;

	return	rect;

}	// End of "Rectangle" FUNCTION "Union"

BOOL	 _DLLENTRY Rectangle::   PtInRect	( Point pt )
{
    if ( ((pt.X() >= left) && (pt.X() < right)) && 
         ( ((pt.Y() <= top) && (pt.Y() > bottom)) ||
         ((pt.Y() > top) && (pt.Y() <= bottom)) ))  
        return TRUE;
    else
        return FALSE;
}	// End of "Rectangle" FUNCTION "PtInRect"

