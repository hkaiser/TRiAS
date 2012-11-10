/*    PortTool v2.2     _accel.cxx          */

/* $Header:   G:/cv.win/pvcs/commonvu/src/_accel.cxv   1.5.1.0   14 Jul 1992 11:48:08   RONAN  $
 *
 *	_ a c c e l . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Created	25Apr90 from _accel.cxx as public interface (nc)
 *
 *	Mods log:
 *	
 *
 */

#include "tfrmpre.hxx" 													   

  _DLLENTRY Accel::  Accel (ResID name)
{
	accel_Imp = new Accel_Imp(name);
}

  _DLLENTRY Accel::  Accel (HACCEL hAccel)
{
	accel_Imp = new Accel_Imp (hAccel);
}

  _DLLENTRY Accel::  ~Accel (void)
{
	delete	accel_Imp;
}


HACCEL  _DLLENTRY Accel::   Handle( Service s_ID )
{
	if ( s_ID == API_ACCEL_HACCEL )
		return accel_Imp -> Handle(s_ID);
	else
		return NULL;
}

