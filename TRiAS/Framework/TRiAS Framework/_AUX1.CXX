/*    PortTool v2.2     _aux1.cxx          */

/* $Header:   G:/cv.win/pvcs/commonvu/src/_aux1.cxv   3.0.1.0   14 Jul 1992 11:48:18   RONAN  $
 *
 *	_ A U X 1 . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0 jk		29nov88 ------ Milestone 2A. Beta 2A ship date. ------
 *	0.1 jk		02dec88 Fast Compile defines added.
 *  0.2 rs      07mar89 Added CV_strcpy, CV_strcat
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 */

/* 0.1 Begin */
#include "tfrmpre.hxx"

 _DLLENTRY Color::  Color	( Colors c )
{
	switch	( c )	//	Select for Red
	{
	case RED:
	case MAGENTA:
	case YELLOW:
	case WHITE:
		R	= 255;
		break;

	default:
		R	= 0;
		break;

	}	// End of SWITCH

	switch	( c )	//	Select for Green
	{
	case GREEN:
	case CYAN:
	case YELLOW:
	case WHITE:
		G	= 255;
		break;

	default:
		G	= 0;
		break;

	}	// End of SWITCH

	switch	( c )	//	Select for Red
	{
	case BLUE:
	case CYAN:
	case MAGENTA:
	case WHITE:
		B	= 255;
		break;

	default:
		B	= 0;
		break;

	}
	_reserved = 0;

}	// End of "Color" CONSTRUCTOR "(Colors)"

char*	CV_strdup ( const char *s )
{

	if (s)
		{
		char	*p	= new char[lstrlen ( s ) + 1];
		if (p)
			lstrcpy(p, s);
		return	p;
		}
	else
		return 0;

}	// End of FUNCTION "CV_strdup"

pchar	PASCAL_FUNC CV_strncpy ( char * d, const char * s, uint l )
{
	if	( !l || !d || !s )
		return	0;

	for	( pchar q = d; l; d++, s++, l-- )
		if	( !( *d = *s ))
			break;

	return	q;

}	// End of FUNCTION "CV_strncpy"

pchar	PASCAL_FUNC	 	CV_strchr( const char * str, char ch)
{
    ch &= 0x7f;
	if (str)
    while (*str)
        { 
        if (ch == (*str & 0x7f))
            return (char*)str;
        str = AnsiNext( str );
        }
    return (char*)0;
}



