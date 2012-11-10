/*
 *	_ D S F I X . H X X
 *
 *	Class to implement scoped data segment fix up,s
 *
 *	Mods Log:
 *	0.0	08nov89	ferg	Original version.
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 */
#ifndef _DSFIX_HXX
#define _DSFIX_HXX 1

// ZORTECH - changed getDS and setDS

#if !defined(WIN32)
extern "C" uint  cdecl _getDS( void );
extern "C" uint  cdecl _setDS( uint );
#endif

class DS_fixup
{
#if !defined(WIN32)
	uint saveseg;
public:
	DS_fixup ( uint seg )
	{
		saveseg = _setDS( seg );
	}

	DS_fixup (  )
	{

		saveseg = _setDS( _AppImpFind() -> DS() );
	}

	~DS_fixup ( )
	{
		_setDS ( saveseg );
	}
#else
public:
	DS_fixup (void) {}
	DS_fixup (uint) {}
	~DS_fixup (void) {}
#endif	// WIN32
};

#endif
