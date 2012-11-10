/* $Header:   G:/cv.win/pvcs/commonvu/src/_pen_im.cxv   3.0.1.0   14 Jul 1992 11:55:54   RONAN  $
 *
 *	_ p e n . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *   (A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	ferg	05oct88	--------- Milestone 2.. Beta 2 shipped --------
 *	0.1	jk		24oct88 Delete function made into a destructor.
 *	0.2 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.3 jk		02dec88 Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 */

#include "tfrmpre.hxx"

static short Convert_LineStyle (StdLineStyle linestyle) 
{
	switch (linestyle) {
	case Dashed:
			return 1;
		break;

	case Dotted:
			return 2;
		break;

	case Dash_Dot:
			return 3;
		break;

	case Dash_Dot_Dot:
			return 4;
		break;

	case ClearLine:
			return 5;
		break;

	case InsideFrameLine:
			return 6;
		break;

	default:
		break;
	}	// End of SWITCH

	return 0;	// Solid
}	// End of FUNCTION "Convert_LineStyle"

static StdLineStyle Convert_LineStyleBack (short linestyle) 
{
	switch (linestyle) {
	case 1:
			return Dashed;
		break;

	case 2:
			return Dotted;
		break;

	case 3:
			return Dash_Dot;
		break;

	case 4:
			return Dash_Dot_Dot;
		break;

	case 5:
			return ClearLine;
		break;

	case 6:
			return InsideFrameLine;
		break;

	default:
		break;
	}	// End of SWITCH

	return SolidLine;
}

Pen_Imp::Pen_Imp (StdLineStyle linestyle, uint width, Color colour) 
{
	m_fAutoDetach = false;
	hPen = CreatePen  (Convert_LineStyle  (linestyle) , width, (ulong&)colour) ;
	CV_ASSERT_VALID(hPen);
}	// End of "Pen" CONSTRUCTOR

Pen_Imp::Pen_Imp (HPEN hP, BOOL fAutoDeatch)
{
	m_fAutoDetach = fAutoDeatch;
	hPen = hP;
	CV_ASSERT_VALID(hPen);
}	// End of "Pen" CONSTRUCTOR

HPEN Pen_Imp::Detach (void)
{
HPEN hP = hPen;

	hPen = NULL;
	return hP;
}

Pen_Imp::~Pen_Imp()				// * 0.1 *
{
	CV_ASSERT_VALID(hPen);
	if (m_fAutoDetach)
		Detach();
	DeleteObject (hPen) ;
}	// End of "Pen_Imp" FUNCTION "Delete"

Color Pen_Imp::GetColor()
{
LogicalPen lpen(hPen);
COLORREF clr = lpen.GetColor();

	return (Color &)clr;
}

CoOrd Pen_Imp::GetWidth()
{
LogicalPen lpen(hPen);

	return lpen.GetWidth();
}

StdLineStyle Pen_Imp::GetStyle()
{
LogicalPen lpen(hPen);

	return Convert_LineStyleBack(lpen.GetType());
}

LogicalPen::LogicalPen(pPen pen)
{
	if (!pen) {
	    lopnStyle = SolidLine;
	    lopnColor = (ulong &)Color(BLACK);
		lopnWidth.X() = 1;
	}
	else {
		CV_ASSERT_VALID(CV_RunTime :: Pen_hPen(pen));
		GetObject (CV_RunTime :: Pen_hPen(pen), sizeof(LogicalPen), (char *)this);
	}
}

LogicalPen::LogicalPen(HPEN hPen)
{
	if (NULL == hPen) {
	    lopnStyle = SolidLine;
	    lopnColor = (ulong &)Color(BLACK);
		lopnWidth.X() = 1;
	}
	else {
		CV_ASSERT_VALID(hPen);
		GetObject (hPen, sizeof(LogicalPen), (char *)this);
	}
}

