/* $Header:   G:/cv.win/pvcs/commonvu/src/_pen.cxv   1.4   04 Oct 1991 12:56:52   RONAN  $
 *
 *	_ p e n . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0 nc      25Apr90	Created 
 */

#include "tfrmpre.hxx"

 _DLLENTRY Pen::   Pen	( StdLineStyle linestyle, uint width, Color colour )
{
	pen_Imp	= new Pen_Imp(linestyle, width, colour);
}

_DLLENTRY Pen::   Pen	(HPEN hP)
{
	pen_Imp	= new Pen_Imp (hP);
}

_DLLENTRY Pen::Pen (HPEN hP, BOOL fAutoDetach)
{
	pen_Imp	= new Pen_Imp (hP, fAutoDetach);
}

 _DLLENTRY Pen::   ~Pen	() 
{
	delete pen_Imp;
}

HPEN _DLLENTRY Pen::Detach (void)
{
	return pen_Imp -> Detach();
}

HPEN	 _DLLENTRY Pen ::  Handle( Service s_ID)
{
	return pen_Imp -> Handle(s_ID);
}

Color _DLLENTRY Pen::GetColor()
{
	return pen_Imp -> GetColor();
}

CoOrd _DLLENTRY Pen::GetWidth()
{
	return pen_Imp -> GetWidth();
}

StdLineStyle _DLLENTRY Pen::GetStyle()
{
	return pen_Imp -> GetStyle();
}

