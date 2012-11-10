/* $Header:   G:/cv.win/pvcs/commonvu/src/_accl_im.cxv   1.5.1.0   14 Jul 1992 11:48:08   RONAN  $
 *
 *	_ a c c e l . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1 ferg	02nov88	Accel_Imp::Accel_Imp() moved here from app.cxx + minor change
 *						to get App pointer from DLL dataseg. Accel_Imp.cxx now 
 *						defunct.
 *	0.2 jk		29nov88	------ Milestone 2A. Beta 2A shipped. ------
 *	0.3 jk		02dec88 Fast Compile defines added.
 *  0.4 rs      22jan89 Extended accelerators to include receiver window
 *  0.5 rs      08mar89 ResId's
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		15Nov89	Added Accel_Imp destructor
 *						Integration of constructors
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 *						removed redundant destructor
 */
#include "tfrmpre.hxx"

// * 1.2 * start
Accel_Imp:: Accel_Imp	(ResID name)
{
	if (!(uint)name)
		hAccel = 0;
	else {
		hAccel = LoadAccelerators (CV_RunTime :: ResID_handle(name, _AppImpFind(), RT_ACCELERATOR), 		   // * 1.3
									(char*)((ulong)((uint)name))); 	// * 0.1 *
		CV_ASSERT_VALID(hAccel);
	}
}	// End of "Accel_Imp" CONSTRUCTOR "(pchar)"				


Accel_Imp:: Accel_Imp	(HACCEL newhAccel)
{
	hAccel = newhAccel;
	CV_ASSERT_VALID (hAccel);
}	// End of "Accel_Imp" CONSTRUCTOR "(HACCEL)"

