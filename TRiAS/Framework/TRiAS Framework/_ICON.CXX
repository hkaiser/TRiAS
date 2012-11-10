/* $Header:   G:/cv.win/pvcs/commonvu/src/_icon.cxv   1.4   04 Oct 1991 12:56:36   RONAN  $
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
 *
 *	converted to implementation format by jcf 21 Aug 89
 */

#include "tfrmpre.hxX"

 _DLLENTRY Icon::  Icon	( ResID RscName )
{
	icon_Imp = new Icon_Imp(RscName);

}  

 _DLLENTRY Icon::  Icon	( StdIcon icon )
{
	icon_Imp = new Icon_Imp(icon);

}

_DLLENTRY Icon::Icon (HICON hIcon)
{
	icon_Imp = new Icon_Imp (hIcon);
}

_DLLENTRY Icon::Icon (HICON hIcon, BOOL fAutoDeatch)
{
	icon_Imp = new Icon_Imp (hIcon, fAutoDeatch);
}

HICON _DLLENTRY Icon::Detach (void)
{
	return icon_Imp -> Detach();
}
 _DLLENTRY Icon ::  ~Icon ()
{
	delete icon_Imp;
}

HICON	 _DLLENTRY Icon::  Handle ( Service s_ID )
{
	if ( s_ID == API_ICON_HICON )
		return icon_Imp -> Handle(s_ID);
	else
		return NULL;
}


