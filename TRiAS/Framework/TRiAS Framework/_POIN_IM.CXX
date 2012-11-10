/* $Header:   G:/cv.win/pvcs/commonvu/src/_poin_im.cxv   3.0.1.0   14 Jul 1992 11:55:56   RONAN  $
 *
 *	_ c u r s o r . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1 ferg	02nov88	Pointer::Pointer() moved here from app.cxx +minor change
 *						to get App pointer from DLL dataseg. Pointer.cxx now 
 *						defunct.
 *	0.2	jk		15nov88	from jk 24oct88. Pointer Delete removed since no 
 *						corresponding function in Windows.
 *	0.3 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.4 jk		02dec88	Fast Compile defines added.
 *  0.5 rs      Mapping mode compatibility 
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		20jun89	Dummy pointer destructor added for PM compatibility
 *  1.2	rs		07jul89 -------Release 1.0a ship date ----------------
 *	1.3 rs		07feb90	Use GetCurrentTask instead of _AppFind if only
 *						Handle to App is required.
 *	2.0 nc		19Jun90 rs from nc Apr90 - Hiding
 */

#include "tfrmpre.hxx"

static	const char*	Convert_Pointer	( StdPointer Stock )
{
	switch	( Stock )
	{
	case CrossHairs:
			return	IDC_CROSS;
		break;

	case IBeam:
			return	IDC_IBEAM;
		break;

	case Icon_Pointer:
			return	IDC_ICON;
		break;

	case FourPointArrow:
			return	IDC_SIZE;
		break;

	case UpArrow:
			return	IDC_UPARROW;
		break;

	case HourGlass:
			return	IDC_WAIT;
		break;

	default:
		break;

	}	// End of SWITCH

	return	IDC_ARROW;

}	// End of FUNCTION "Convert_Pointer"


Pointer_Imp::  Pointer_Imp	( ResID RscName )			// * 0.1 function moved *
{
	hPointer = LoadCursor (CV_RunTime :: ResID_handle (RscName, _AppImpFind(), RT_CURSOR), 
			       (char*)((ulong)((uint)RscName)));
	m_fAutoDetach = false;
}	

Pointer_Imp::  Pointer_Imp	( StdPointer Stock )
{
	hPointer = LoadCursor (0, Convert_Pointer(Stock));
	m_fAutoDetach = false;
}	

Pointer_Imp::  Pointer_Imp	(HCURSOR hC, BOOL fAutoDetach)
{
	hPointer = hC;
	m_fAutoDetach = fAutoDetach;
}	

Pointer_Imp::Pointer_Imp (LPCSTR pcCursor)
{
	hPointer = LoadCursorFromFile (pcCursor);
	m_fAutoDetach = false;
}	

Pointer_Imp::~Pointer_Imp (void)
{
	if (m_fAutoDetach)
		Detach();
}	

HCURSOR Pointer_Imp::Detach (void)
{
HCURSOR hC = hPointer;

	hPointer = NULL;
	return hC;
}

BOOL Pointer_Imp::LoadStockPointer (StdPointer Stock)
{
	hPointer = LoadCursor (0, Convert_Pointer(Stock));
	return NULL != hPointer;
}

Point	Pointer_Imp::  GetPos ()
{
	Point	pt;

	GetCursorPos ( (POINT *)&pt );   // *MAPPING screen co-ordinates
    	return CV_RunTime :: DevToLog( 0, pt);     // * 0.5 *
}	


void	Pointer_Imp::  ChangePos	( Point Pt )
{
    Pt = CV_RunTime :: LogToDev( 0, Pt);     // * 0.5 *
	SetCursorPos ( Pt.X (), Pt.Y ());   // *MAPPING screen 
}	


void	Pointer_Imp::  Hide	()
{
//	while (ShowCursor ( FALSE ) >= 0);
 ShowCursor ( FALSE );

}	// End of "Pointer_Imp" FUNCTION "Hide"


void	Pointer_Imp::  Show	()
{
	// It is necessary to loop around showing the cursor until the display
	// count is greater than zero
	
//	while (ShowCursor ( TRUE ) < 0);
	ShowCursor ( TRUE );

}	// End of "Pointer_Imp" FUNCTION "Show"

											// * 0.** Pointer::Delete gone *
							
void	Pointer_Imp::  Confine	( Rectangle Rect )
{
	if (Rect . Left() || Rect . Right() || Rect . Top()  || Rect . Bottom())
        {
        	Rect.Top() = CV_RunTime :: LogToDev(0, Rect.UpperLeft()).Y();
        	Rect.Bottom() = CV_RunTime :: LogToDev(0, Rect.LowerRight()).Y();
		ClipCursor ( (RECT *)&Rect );
        }
	else
		ClipCursor ( 0 );

}	// End of "Pointer_Imp" FUNCTION "Confine"
