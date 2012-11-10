/* $Header:   G:/cv.win/pvcs/commonvu/src/_context.cxv   1.5.1.0   14 Jul 1992 11:48:26   RONAN  $
 *
 *	_ e c . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *
 *
 *	0.0 nc		24May90	Hiding
 *
 *
 */
#include "tfrmpre.hxx"
#include	<_Link.hxx>  			// * 0.1  Begin *

_DLLENTRY EventContext:: EventContext () {}

_DLLENTRY EventContext:: ~EventContext ()
{
	if ( ec_Imp )
	{
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

long  _DLLENTRY EventContext::  Dispatch (Event e)
{
	return ec_Imp -> Dispatch(e);
}

void  _DLLENTRY EventContext::  Default (Event e)
{
	ec_Imp -> Default(e);
}





