/* $Header:   G:/cv.win/pvcs/commonvu/src/_mesb_im.cxv   3.0.1.0   14 Jul 1992 11:55:52   RONAN  $
 *
 *	_ m e s s b o x . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1	ferg	07nov88	MessBox::Show moved here from messbox.cxx and changed
 *						to get AppInst from DLL and Show flag from App, 
 *						messbox.cxx now defunct.
 *	0.2	jk		24oct88 Destructor for MessBox added.
 *	0.3 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.4 jk		02dec88	Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		04Dec89	Temporal dependency removal
 *	2.0 rs, nc 	??Jul90 Hiding changes.
 *	2.1 rs		19Jul90 Dont initialise Caption or Text in ErrorBox as
 *						subsequent deletion causes protection violation.
 */

#include "tfrmpre.hxX"

MessBox_Imp::  MessBox_Imp	( const char* caption, const char* text, pWind_Imp parent )
{
	Parent	= parent;
	Type	= 0;			// Default to an Okay box

	if	( text )
		Text	= (char*)CV_strdup ( text );
	else
		Text	= 0;

	if	( caption )
		Caption	= (char*)CV_strdup ( caption );
	else
		Caption	= 0;
    Beep = false;  // Default No Beep    
}	// End of "MessBox_Imp" CONSTRUCTOR

MessBox_Imp::  ~MessBox_Imp ()					// * 0.2 Begin *
{
	if (Caption)
		delete Caption;
	if (Text)
		delete Text;
}											// * 0.2 End *

void MessBox_Imp :: SetBeep( BOOL setting )
{
    Beep = setting;
}
    
												// * 0.1  Begin *

StdMessBoxReply	MessBox_Imp::  Show	()
{
	HWND	hParent	= 0;
	const char* mb_text = Text;
	const char* mb_capt = Caption;

	if (Parent)
		CV_RunTime :: ValidateWindow(Parent);	 // * 1.2 * (Lines deleted also)

	if	( Parent )			// Should have a parent
		hParent	= CV_RunTime :: Handle(Parent);
	else
		{
		hParent = 0;
		Type |= MB_TASKMODAL;
		}
	if	( ! mb_capt )	// An ErrorBox ?
	{
		Type		&= ~0xF0;
		Type		|= HandIcon;	// Always use the Hand Icon for error

		mb_capt = "Error!";		// Change for foreign language support

		if	( ! mb_text )	// Out of memory ?
			{												// * 1.3 * start
			mb_text	= "Memory Allocation Failure";
			Type |= MB_SYSTEMMODAL; 	// MB_SYSTEMMODAL
			Type &= 0xDFFF; 	// MB_SYSTEMMODAL
			}												// * 1.3 * end
	}	// End of IF

	if (Beep)
        MessageBeep(0);

	switch	( MessageBox ( hParent, mb_text, mb_capt, Type ))
	{
	case IDABORT:
			return	AbortReply;
		break;

	case IDCANCEL:
			return	CancelReply;
		break;

	case IDIGNORE:
			return	IgnoreReply;
		break;

	case IDNO:
			return	NoReply;
		break;

	case IDOK:
			return	OkayReply;
		break;

	case IDRETRY:
			return	RetryReply;
		break;

	case IDYES:
			return	YesReply;
		break;

	default:
		break;

	}	// End of SWITCH

	return	OkayReply;

}	// End of "MessBox_Imp" FUNCTION "Show"
											  // * 0.1 End *
void	MessBox_Imp::  SetType	( StdMessBox type )
{
	if	(( type & 0xF ) < 6 )			// Include the buttons
	{
		Type	&= ~0xF;
		Type	|= ( type & 0xF );

	}	// End of IF

	if	(( type & 0xF0 ) < 0x50 )		// Include the icons
	{
		Type	&= ~0xF0;
		Type	|= ( type & 0xF0 );

	}	// End of IF

	Type	|= ( type & ~0xFF );	// Include all other bits

}	// End of "MessBox_Imp" FUNCTION "SetType"

