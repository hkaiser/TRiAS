/**
 **     $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/argtest.c,v 1.6 1995/06/30 21:51:45 bduggan Exp $
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

#define HEADER  "	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/argtest.c,v 1.6 1995/06/30 21:51:45 bduggan Exp $"

/**
 **  FILE
 **     argtest.c       -  Argument Parsing Package Test
 **
 **  PROJECT
 **     libsdsc         -  SDSC Utility Library
 **
 **  DESCRIPTION
 **     This file contains source for an argument parsing package test
 **	program.  It is used to verify the correctness of the argument
 **	parsing package.
 **
 **  PUBLIC CONTENTS
 **                     d =defined constant
 **                     f =function
 **                     m =defined macro
 **                     t =typedef/struct/union
 **                     v =variable
 **                     ? =other
 **
 **	main		f  Main program
 **
 **  HISTORY
 **	$Log: argtest.c,v $
 **	Revision 1.6  1995/06/30  21:51:45  bduggan
 **	added void for main
 **
 **	Revision 1.5  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.4  1994/10/03  16:21:51  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Updated comments.
 **	Updated version number.
 **	Updated copyright message.
 **
 **	Revision 1.3  92/09/02  14:12:14  vle
 **	Updated copyright notice and added comment block.
 **
 **	Revision 1.2  91/09/17  20:06:58  nadeau
 **	Updated to support enhanced ArgCommand struct.
 **
 **	Revision 1.1  91/01/09  16:46:49  nadeau
 **	Initial revision
 **	
 **/

#include "sdsccopyright.h"
#include <stdio.h>
#include "sdsc.h"

ArgCommand cmnd =
{
	"argtest", 3, 0, 0,
	"%command tests the argument parsing package.",

"None of these options actually do anything.  The above option list should\n\
only include -infile and -outfile.\n\
\n\
For additional information and a complete option list, use -fullhelp.",

NULL,
"None of these options actually do anything.  The above option list should\n\
include every option supported by the tool (except -debug).\n\
\n\
The -infile and -outfile options are typical of various tools and test out\n\
the implied keyword, required option, and string value aspects of the package.\n\
\n\
The -debug option is hidden and should not appear on the above option list.\n\
\n\
The -frames option tests out multiple argument, multiple occurrence options.\n\
\n\
The -translate tests out fixed number of value and floating point value\n\
options.",

	ARGFNONE,
	NULL,
	NULL,
"SDSC argument parsing package Verification Tools",
"Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC),\n\
a division of General Atomics, San Diego, California, USA",
	NULL,
	NULL
};

#define NOPTIONS	5
ArgOption options[NOPTIONS] =
{
	{ "infile", "filename", "Input file name",
	  ARGFIMPKEYWORD|ARGFREQUIRED, 1, 1, ARGTSTRING },
	{ "outfile", "filename", "Output file name",
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },
	{ "debug", NULL, "Turn on debugging messages",
	  ARGFHIDDEN, 0, 0, ARGTNONE },
	{ "frames", "frame_nos...", "List of frame numbers",
	  ARGFMULTIPLE|ARGFFULLHELP, 1, ARGVNOMAX, ARGTINT },
	{ "translate", "x y z", "Amount to translate",
	  ARGFFULLHELP, 3, 3, ARGTFLOAT },
};

#define NEQUIVS		2
ArgEquiv equivs[NEQUIVS] =
{
	{ "debug",  "dbg" },
	{ "translate", "xlate" },
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
	ArgParse( argc, argv, &cmnd, NOPTIONS, options, NEQUIVS, equivs );
	fprintf( stderr, "Did nothing.\n" );
}
