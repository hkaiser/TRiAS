/*
 *
 *	_ m d i . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	sm		Original version
 *
 */
#include "tfrmpre.hxx"

_DLLENTRY ShellWindow :: ShellWindow (void)
{
	ec_Imp = new ShellWind_Imp (this);
	EnableSysMenu();
	EnableBorder();
	EnableMinBox();
	EnableMaxBox();
}

_DLLENTRY ShellWindow :: ~ShellWindow (void)
{
}


void _DLLENTRY ShellWindow :: Arrange (ArrangeStyle s)
{
	((ShellWind_Imp *)ec_Imp)->Arrange((int)s);
}
