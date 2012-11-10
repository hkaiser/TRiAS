/* $Header:   G:/cv.win/pvcs/commonvu/src/_pointer.cxv   1.5   04 Oct 1991 12:56:56   RONAN  $
 *
 *	_ p o i n t e r . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 * 	Changed to be the public interface
 * 	Implementation moved to _poin_im.cxx
 *	Sept 89
 */

#include "tfrmpre.hxx"

_DLLENTRY Pointer:: Pointer (ResID RscName)
{
	pointr_Imp = new Pointer_Imp(RscName);
}	// End of "Pointer" CONSTRUCTOR "(uint)"

_DLLENTRY Pointer:: Pointer	(HCURSOR hCursor)
{
	pointr_Imp = new Pointer_Imp (hCursor);
}	// End of "Pointer" CONSTRUCTOR "(HCURSOR)"

_DLLENTRY Pointer:: Pointer	(HCURSOR hCursor, BOOL fAutoDetach)
{
	pointr_Imp = new Pointer_Imp (hCursor, fAutoDetach);
}	// End of "Pointer" CONSTRUCTOR "(HCURSOR)"

_DLLENTRY Pointer::Pointer (StdPointer Stock)
{
	pointr_Imp = new Pointer_Imp(Stock);
}	// End of "Pointer" CONSTRUCTOR "(StdPointer)"

_DLLENTRY Pointer::Pointer (LPCSTR pcCursor, StdPointer Stock)
{
	if (NULL != pcCursor) {
		pointr_Imp = new Pointer_Imp(pcCursor);
		if (NULL == pointr_Imp -> Handle(API_POINTER_HPOINTER)) 
		// Cursor nicht gefunden
			pointr_Imp -> LoadStockPointer (Stock);
	} else
		pointr_Imp = new Pointer_Imp(Stock);
}

HCURSOR _DLLENTRY Pointer::Detach (void)
{
	return pointr_Imp->Detach();
}

Point _DLLENTRY Pointer:: GetPos	()
{
	return pointr_Imp->GetPos();
}	// End of "Pointer" FUNCTION "GetPos"


void	 _DLLENTRY Pointer:: ChangePos	( Point Pt )
{
	pointr_Imp->ChangePos(Pt);
}	// End of "Pointer" FUNCTION "ChangePos"


void	 _DLLENTRY Pointer:: Hide	()
{
	pointr_Imp->Hide();
}	// End of "Pointer" FUNCTION "Hide"


void	 _DLLENTRY Pointer:: Show	()
{
	pointr_Imp->Show();
}	// End of "Pointer" FUNCTION "Show"

							
void	 _DLLENTRY Pointer:: Confine	( Rectangle Rect )
{
	pointr_Imp->Confine(Rect);
	
}	// End of "Pointer" FUNCTION "Confine"



 _DLLENTRY Pointer:: ~Pointer ()
{
	delete	pointr_Imp;
}

HCURSOR	 _DLLENTRY Pointer::  Handle( Service s_ID)
{
	if (s_ID == API_POINTER_HPOINTER)
		return pointr_Imp -> Handle(s_ID);
	else
		return NULL;

}


