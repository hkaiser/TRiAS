/* $Header:   G:/cv.win/pvcs/commonvu/src/appidle.cxv   1.3   04 Sep 1991 20:47:22   RONAN  $
 *
 *
 *	A P P I D L E . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	rs		10oct89	Initial development
 */
#include "tfrmlib.hxx"

void	App::  Idle(InvokeStatus InvSts)
{
	CV_RunTime :: App_ResetIdle(app_Imp);
}	// End of "App" FUNCTION "Idle"

