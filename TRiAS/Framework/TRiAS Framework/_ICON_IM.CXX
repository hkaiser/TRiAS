/* $Header:   G:/cv.win/pvcs/commonvu/src/_icon_im.cxv   1.3.1.0   14 Jul 1992 11:55:42   RONAN  $
 *
 *	_ i c o n . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1 ferg	02nov88	Icon::Icon() moved here from icon.cxx + minor change
 *						to get App pointer from DLL dataseg. icon.cxx now 
 *						defunct.
 *	0.2	jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.3 jk		02dec88	Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		07feb90	Use GetCurrentTask instead of _AppFind if only
 *						Handle to App is required.
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 */

#include "tfrmpre.hxx"

const char	  *Convert_Icon	( StdIcon icon )
{
	switch	( icon )
	{
	case Hand:
			return	IDI_HAND;

	case QuestionMark:
			return	IDI_QUESTION;

	case Exclamation:
			return	IDI_EXCLAMATION;

	case Asterisk:
			return	IDI_ASTERISK;

	default:
		break;

	}	// End of SWITCH

	return IDI_APPLICATION;

}	// End of FUNCTION "Convert_Icon"

													// * 0.1 Begin *
Icon_Imp::  Icon_Imp	( ResID RscName )
{
	hIcon = LoadIcon (CV_RunTime :: ResID_handle (RscName, _AppImpFind(), RT_ICON), 
			 (char*)((ulong)((uint)RscName)));	// * 1.2 *
	m_fAutoDetach = false;
}	// End of "Icon_Imp" CONSTRUCTOR "(pchar)"
												   // * 0.1 End *

Icon_Imp::  Icon_Imp	( StdIcon icon )
{
	hIcon	= LoadIcon ( 0, Convert_Icon ( icon ));
	m_fAutoDetach = false;
}	// End of "Icon_Imp" CONSTRUCTOR "(StdIcon)"


Icon_Imp::  Icon_Imp	(HICON hI, BOOL fAutoDetach)
{
	m_fAutoDetach = fAutoDetach;
	hIcon	= hI;
}	// End of "Icon_Imp" CONSTRUCTOR "(StdIcon)"

Icon_Imp::~Icon_Imp	(void)
{
	if (m_fAutoDetach)
		Detach();
}	// End of "Icon_Imp" CONSTRUCTOR "(StdIcon)"

HICON Icon_Imp::Detach (void)
{
HICON hI = hIcon;

	hIcon = NULL;
	return hI;
}
