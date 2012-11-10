/* $Header:   G:/cv.win/pvcs/commonvu/src/_brush.cxv   1.4   04 Oct 1991 12:52:24   RONAN  $
 *
 *	_ b r u s h . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	jf	Sept89 Created new as public interface class
 */

#include "tfrmpre.hxx"


_DLLENTRY Brush::   Brush	( StdBrush Stock )
{
	brush_Imp = new	Brush_Imp(Stock);
	
} 


_DLLENTRY Brush::  Brush	( Color colour, StdHatchStyle hatchstyle )
{
	brush_Imp = new	Brush_Imp(colour,hatchstyle);
	
} 


_DLLENTRY Brush::  Brush	( pBitmap Bm )
{
	brush_Imp = new	Brush_Imp(Bm);

}


_DLLENTRY Brush::  Brush	(HBRUSH hBr)
{
	brush_Imp = new	Brush_Imp (hBr);
}

_DLLENTRY Brush::Brush (HBRUSH hBr, BOOL fAutoDetach)
{
	brush_Imp = new	Brush_Imp (hBr, fAutoDetach);
}

_DLLENTRY Brush::  ~Brush	()					  
{
	delete	brush_Imp;
}

HBRUSH _DLLENTRY Brush::Detach (void)
{
	return brush_Imp -> Detach();
}

HBRUSH	_DLLENTRY Brush:: Handle (Service s_ID)
{
	return brush_Imp -> Handle (s_ID);
}


