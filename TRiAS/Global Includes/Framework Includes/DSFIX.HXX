//	Header file for Computer Associates FreeStore release 2.0
//
//	Implementation of Computer Associates FreeStore release 3.1
//
//	Computer Associates Framework for object storage
//
//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//  dsfix.hxx - This file declares the DS_fixup class to implement 
//	scoped data segment fixups.
//
//-------------------------------------------------------------------------
#ifndef DSFIX_HXX
#define DSFIX_HXX 1

extern "C" {
extern unsigned _cdecl _getDS( void );
extern unsigned _cdecl _setDS( unsigned );
}

class DS_fixup
{
	unsigned saveseg;
public:
	DS_fixup ( unsigned seg )
	{
		saveseg = _setDS( seg );
	}
	~DS_fixup ( )
	{
		_setDS ( saveseg );
	}
};
#endif
