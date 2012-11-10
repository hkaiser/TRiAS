/* $Header:   G:/cv.win/pvcs/commonvu/src/_brsh_im.cxv   1.5.1.0   14 Jul 1992 11:48:22   RONAN  $
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
 *	0.0	ferg	05oct88	--------- Milestone 2. Beta 2 shipped ---------
 *	0.1	jk		24oct88 Delete function made into a destructor.
 *	0.2 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.3	jk		02dec88	Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 */

#include "tfrmpre.hxx"

static	short	 	Convert_Brush	( StdBrush Stock )
{
	switch	( Stock )
	{
	case BlackBrush:
			return	BLACK_BRUSH;
		break;

	case DarkBrush:
			return	DKGRAY_BRUSH;
		break;

	case MediumBrush:
			return	GRAY_BRUSH;
		break;

	case LightBrush:
			return	LTGRAY_BRUSH;
		break;

	case HollowBrush:
			return	HOLLOW_BRUSH;
		break;

	case ClearBrush:
			return	NULL_BRUSH;
		break;

	default:
		break;

	}	// End of SWITCH

	return	WHITE_BRUSH;

}	// End of FUNCTION "Convert_Brush"


static	short	 	Convert_Hatch	( StdHatchStyle hatchstyle )
{
	switch	( hatchstyle )
	{
	case Diagonal_45:
			return	HS_BDIAGONAL;
		break;

	case VerticalHatch:
			return	HS_VERTICAL;
		break;

	case Diagonal_135:
			return	HS_FDIAGONAL;
		break;

	case HorizontalHatch:
			return	HS_HORIZONTAL;
		break;

	case OrthogonalCrossHatch:
			return	HS_CROSS;
		break;

	default:
		break;

	}	// End of SWITCH

	return	HS_DIAGCROSS;

}	// End of FUNCTION "Convert_Hatch"


Brush_Imp::  Brush_Imp	(StdBrush Stock)
{
	isStock = true;
	hBrush	= (HBRUSH)GetStockObject(Convert_Brush (Stock));
	m_fAutoDetach = false;
}	// End of "Brush" CONSTRUCTOR "(StdBrush)"


Brush_Imp::  Brush_Imp	( Color colour, StdHatchStyle hatchstyle )
{
	isStock = false;
	if (hatchstyle == SolidHatch )
		hBrush	= CreateSolidBrush ( (ulong&)colour );
	else
		hBrush	= CreateHatchBrush ( Convert_Hatch ( hatchstyle ), (ulong&)colour );
	m_fAutoDetach = false;
}	// End of "Brush" CONSTRUCTOR "(Color,HatchStyle)"


Brush_Imp::  Brush_Imp	(pBitmap Bm)
{
	isStock = false;
	hBrush	= CreatePatternBrush (CV_RunTime :: Bitmap_hBitmap (Bm));
	m_fAutoDetach = false;
}	// End of "Brush" CONSTRUCTOR "(pBitmap)"


Brush_Imp::  Brush_Imp	(HBRUSH hBr, BOOL fAutoDetach)
{
	isStock = false;
	hBrush	= hBr;
	m_fAutoDetach = fAutoDetach;
}	// End of "Brush" CONSTRUCTOR "(HBRUSH)"

Brush_Imp::  ~Brush_Imp	()							// * 0.1 *
{
	if (m_fAutoDetach)
		Detach();

	if (!isStock && hBrush)
		:: DeleteObject (hBrush);
}	// End of "Brush" FUNCTION "Delete"

HBRUSH Brush_Imp::Detach (void)
{
HBRUSH hBr = hBrush;

	hBrush = NULL;
	return hBr;
}

LogicalBrush ::  LogicalBrush(pBrush brush)
{
	if (!brush) {
		lbColor = (ulong&)Color(BLACK);
		lbHatch = SolidHatch;
	} else
		GetObject (CV_RunTime :: Brush_hBrush(brush), sizeof(LogicalBrush), (char  *)this);
}

LogicalBrush ::  LogicalBrush (HBRUSH hbrush)
{
	GetObject (hbrush, sizeof(LogicalBrush), (char  *)this);
}

LogBackBrush ::  LogBackBrush(Wind_Imp *pw )
{
HBRUSH hBr = 0;

	if (pw -> GetBackground())
		hBr = CV_RunTime :: Brush_hBrush (pw -> GetBackground());
	else
#if !defined(WIN32)
		hBr= (HBRUSH)GetClassWord (pw -> Handle(), GCW_HBRBACKGROUND);
#else
		hBr= (HBRUSH)GetClassLong (pw -> Handle(), GCL_HBRBACKGROUND);
#endif
	if (!hBr) {
		lbColor = GetSysColor(COLOR_WINDOW);
		lbHatch = SolidHatch;
		lbStyle = BS_SOLID;
	} else {
		if (hBr <= (HBRUSH)(COLOR_ENDCOLORS+1)) {
			lbColor = GetSysColor(((uint)(hBr)) - 1);
			lbHatch = SolidHatch;
			lbStyle = BS_SOLID;
		} else
			GetObject (hBr , sizeof(LogicalBrush), (char  *)this);
	}
}
