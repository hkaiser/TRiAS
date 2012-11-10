/**
 **     $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/argtest2.c,v 1.7 1995/06/30 21:52:09 bduggan Exp $
 **     Copyright (c) 1989-1995  San Diego Supercomputer Center (SDSC)
 **             a division of General Atomics, San Diego, California, USA
 **
 **     Users and possessors of this source code are hereby granted a
 **     nonexclusive, royalty-free copyright and design patent license to
 **     use this code in individual software.  License is not granted for
 **     commercial resale, in whole or in part, without prior written
 **     permission from SDSC.  This source is provided "AS IS" without express
 **     or implied warranty of any kind.
 **
 **     For further information contact:
 **             E-Mail:         info@sds.sdsc.edu
 **
 **             Surface Mail:   Information Center
 **                             San Diego Supercomputer Center
 **                             P.O. Box 85608
 **                             San Diego, CA  92138-5608
 **                             (619) 534-5000
 **/

#define HEADER  "	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/argtest2.c,v 1.7 1995/06/30 21:52:09 bduggan Exp $"

/**
 **  FILE
 **     argtest.c       -  Argument Parsing Package Test
 **
 **  PROJECT
 **     libsdsc         -  SDSC Utility Library
 **
 **  DESCRIPTION
 **     This file contains source for an argument parsing package test
 **     program.  It is used to verify the correctness of the argument
 **     parsing package.
 **
 **  PUBLIC CONTENTS
 **                     d =defined constant
 **                     f =function
 **                     m =defined macro
 **                     t =typedef/struct/union
 **                     v =variable
 **                     ? =other
 **
 **	main		f  main program
 **
 **  HISTORY
 **     $Log: argtest2.c,v $
 **	Revision 1.7  1995/06/30  21:52:09  bduggan
 **	took out strcmp
 **
 **	Revision 1.6  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.5  1994/10/03  16:22:42  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Updated comments.
 **	Updated version number.
 **	Updated copyright message.
 **
 **	Revision 1.4  92/09/02  14:21:34  vle
 **	Added comment block at top of file.
 **	
 **	Revision 1.3  92/09/02  13:27:28  vle
 **	Updated copyright notice.
 **
 **	Revision 1.2  91/09/17  20:07:16  nadeau
 **	Updated to support enhanced ArgCommand struct.
 **
 **	Revision 1.1  91/01/09  16:46:51  nadeau
 **	Initial revision
 **/
 
#include "sdsccopyright.h"
#include <stdio.h>
#include <string.h>
#include "sdsc.h"


ArgCommand cmnd =
{
	"argtest2", 3, 0, 0,
	"%command tests the argument parsing package.",
	"None of these options actually do anything.  They are just provided\n\
to give the package something to put into its hash table.",
	NULL, NULL,
	ARGFNONE,
	NULL,
	NULL,
"SDSC argument parsing package Verification Tools",
"Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC),\n\
a division of General Atomics, San Diego, California, USA",
"This is a test, and only a test.  If this had been a real registration form\n\
you would have been told what to do and to where to send it.\n",
"This is a test, and only a test.  If this had been a real feedback form\n\
you would have been told what to do and to where to send it.\n",
};

#define NOPTIONS	2
ArgOption options[NOPTIONS] =
{
	{ "verbose", NULL, "Be verbose",
	  ARGFFULLHELP, 0, 0, ARGTNONE },
	{ "list", "thing", "List of things",
	  ARGFIMPKEYWORD|ARGFMULTIPLE, 1, 1, ARGTSTRING },
};


void
#ifdef __STDC__
main ( int argc, char *argv[ ] )
#else
main ( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argument vector		*/
#endif
{
	int i, nOpt, noccur;
	char *keyword;

	nOpt = ArgParse( argc, argv, &cmnd, NOPTIONS, options, 0, NULL );
	printf( "%d options received:\n", nOpt );

	for ( i = 0; i < nOpt; i++ )
	{
		keyword = ArgQOpt( i, &noccur );
		if ( strcmp( "verbose", keyword ) == 0 )
			printf( "  %d:  %s\n", i, keyword );
		else
			printf( "  %d:  %s %s\n", i, keyword,
				ArgQValue( keyword, noccur, 0 )->arg_s );
	}
}
