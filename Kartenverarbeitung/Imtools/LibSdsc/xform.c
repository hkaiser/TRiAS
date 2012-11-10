/**
 **	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/xform.c,v 1.6 1995/06/30 21:57:14 bduggan Exp $
 **	Copyright (c) 1989-1995  San Diego Supercomputer Center (SDSC)
 **		a division of General Atomics, San Diego, California, USA
 **
 **	Users and possessors of this source code are hereby granted a
 **	nonexclusive, royalty-free copyright and design patent license to
 **	use this code in individual software.  License is not granted for
 **	commercial resale, in whole or in part, without prior written
 **	permission from SDSC.  This source is provided "AS IS" without express
 **	or implied warranty of any kind.
 **
 **	For further information contact:
 **		E-Mail:		info@sds.sdsc.edu
 **
 **		Surface Mail:	Information Center
 **				San Diego Supercomputer Center
 **				P.O. Box 85608
 **				San Diego, CA  92138-5608
 **				(619) 534-5000
 **/

#define HEADER	"    $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/xform.c,v 1.6 1995/06/30 21:57:14 bduggan Exp $"

/**
 **  FILE
 **	xform.c		-  transform geometry
 **
 **  PROJECT
 **	LibSDSC		-  SDSC tool set
 **
 **  DESCRIPTION
 **	This program reads in and transforms a CGM geometry file
 **
 **  PUBLIC CONTENTS
 **	main		-  main program
 **
 **  PRIVATE CONTENTS
 **
 **  HISTORY
 **	$Log: xform.c,v $
 **	Revision 1.6  1995/06/30  21:57:14  bduggan
 **	took out some prototypes and useless var.s
 **
 **	Revision 1.5  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.4  1994/10/03  16:26:28  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Added forward declarations.
 **	Updated comments.
 **	Updated version number.
 **	Updated copyright message.
 **
 **	Revision 1.3  92/09/02  13:34:30  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.2  91/09/17  20:07:24  nadeau
 **	Updated to support enhanced ArgCommand struct.
 **	
 **	Revision 1.1  91/01/09  16:47:03  nadeau
 **	Initial revision
 **	
 **/


/*
 *  NOTE:
 *	This program is currently crippled and serves only as a test of
 *	the argument parsing package.  The input file is not read, the
 *	output file is not written, and no transformations occur.
 */

#include "sdsccopyright.h"
#include <stdio.h>
#include "sdsc.h"
#include <string.h>


/*
 *  DEFINES
 *	VER...	-  version number components
 */
#define VERMAJOR	3
#define VERMINOR	0
#define VERSUBMINOR	0


#ifdef __STDC__
static void openInput( char * );
static void openOutput( char * );
static void closeInput( void );
static void closeOutput( void );
static void scaleUniform( float );
static void scaleXY( float, float );
static void scaleXYZ( float, float, float );
static void translate( float, float, float );
static void rotateX( float );
static void rotateY( float );
static void rotateZ( float );
#else
static void openInput( );
static void openOutput( );
static void closeInput( );
static void closeOutput( );
static void scaleUniform( );
static void scaleXY( );
static void scaleXYZ( );
static void translate( );
static void rotateX( );
static void rotateY( );
static void rotateZ( );
#endif





/*
 *  GLOBALS
 *	cmnd	-  Command information
 *	options	-  Option information
 *
 *  DESCRIPTION
 *	These structure initializations describe the command and its options
 *	for the argument parsing package.
 */
ArgCommand cmnd =
{
	"xform", VERMAJOR, VERMINOR, VERSUBMINOR,
	"%command transforms geometric data from 'infile' to 'outfile'.",
"Transformations occur in command-line order.  All transform options may occur\n\
more than once.  A dash '-' for the infile and/or outfile names indicates use\n\
of stdin for input and stdout for output, respectively.",
	NULL, NULL,
	ARGFNONE,
	NULL,
	NULL,
"SDSC argument parsing package Verification Tools",
"Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC),\n\
a division of General Atomics, San Diego, California, USA",
	NULL,
	NULL,
};

#define NOPTIONS	8
ArgOption options[NOPTIONS] =
{
	{ "infile", "cgm_filename", "Input geometry file name",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "cgm_filename", "Transformed output geometry file name",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "scale", "(u) | (x y) | (x y z)", "scale uniformly, in (X,Y), or in (X,Y,Z)",
	  ARGFMULTIPLE, 1, 3, ARGTFLOAT },

	{ "translate", "x y z", "translate by (X,Y,Z)",
	  ARGFMULTIPLE, 3, 3, ARGTFLOAT },

	{ "verbose", NULL, "Be verbose",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "xrotate", "xangle", "rotate about X-axis by xangle",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT },

	{ "yrotate", "yangle", "rotate about Y-axis by yangle",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT },

	{ "zrotate", "zangle", "rotate about Z-axis by zangle",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT },
};





/*
 *  GLOBALS
 *	verbose		-  Verbosity mode on?
 *	infile		-  Input file name
 *	outfile		-  Output file name
 *
 *  DESCRIPTION
 *	When verbosity is turned on, messages are written to stderr upon
 *	each action.
 *
 *	infile and outfile are the file names of the input and output
 *	files, of course.
 */
static int   verbose;			/* Verbose mode on?		*/
static char *infile;			/* Input geometry file name	*/
static char *outfile;			/* Output geometry file name	*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	main() invokes the argument parser the walks the command-line order
 *	option list.  The input file is then opened and the geometry read in.
 *
 *	On each transformation option, the values for that occurrence of the
 *	option are extracted and the appropriate geometry transformation
 *	routine called.
 *
 *	Upon completion, the transformed geometry is written out to the output
 *	file.
 */

void
#ifdef __STDC__
main( int argc, char *argv[ ] )
#else
main ( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argument vector		*/
#endif
{
	int nopt;			/* Number of options		*/
	int opt;			/* Option counter		*/
	char *keyword;			/* Current keyword		*/
	int noccur;			/* Occurance number		*/


	/*
	 *  Parse the command-line.
	 */
	nopt = ArgParse( argc, argv, &cmnd, NOPTIONS, options, 0, NULL );
	verbose = (ArgQNOccur( "verbose" ) == 0) ? 0 : 1;
	if ( verbose )
		fprintf( stderr, "Verbosity on\n" );


	/*
	 *  Check the input and output file arguments and open the files.
	 */
	infile  = ArgQValue( "infile", 0, 0 )->arg_s;
	outfile = ArgQValue( "outfile", 0, 0 )->arg_s;
	openInput( infile );
	openOutput( outfile );



	/*
	 *  Process the transformations in the order in which they were
	 *  given on the command-line.
	 */
	for ( opt = 0; opt < nopt; opt++ )
	{
		keyword = ArgQOpt( opt, &noccur );
		if ( strcmp( keyword, "verbose" ) == 0 ||
		     strcmp( keyword, "infile" )  == 0 ||
		     strcmp( keyword, "outfile" ) == 0 )
			continue;	/* Already handled		*/
		if ( strcmp( keyword, "scale" ) == 0 )
		{
			switch ( ArgQNValue( keyword, noccur ) )
			{
			case 1:		/* Uniform Scaling.		*/
				scaleUniform( ArgQValue( keyword, noccur, 0 )->arg_f );
				continue;
			case 2:		/* X-Y Scaling.			*/
				scaleXY( ArgQValue( keyword, noccur, 0 )->arg_f,
					ArgQValue( keyword, noccur, 1 )->arg_f);
				continue;
			case 3:		/* X-Y-Z Scaling.		*/
				scaleXYZ( ArgQValue( keyword, noccur, 0)->arg_f,
					ArgQValue( keyword, noccur, 1 )->arg_f,
					ArgQValue( keyword, noccur, 2 )->arg_f);
				continue;
			}
		}
		if ( strcmp( keyword, "translate" ) == 0 )
		{
			translate( ArgQValue( keyword, noccur, 0 )->arg_f,
				ArgQValue( keyword, noccur, 1 )->arg_f,
				ArgQValue( keyword, noccur, 2 )->arg_f );
			continue;
		}
		if ( strcmp( keyword, "xrotate" ) == 0 )
		{
			rotateX( ArgQValue( keyword, noccur, 0 )->arg_f );
			continue;
		}
		if ( strcmp( keyword, "yrotate" ) == 0 )
		{
			rotateY( ArgQValue( keyword, noccur, 0 )->arg_f );
			continue;
		}
		if ( strcmp( keyword, "zrotate" ) == 0 )
		{
			rotateZ( ArgQValue( keyword, noccur, 0 )->arg_f );
			continue;
		}
	}


	/*
	 *  Close the files.
	 */
	closeInput( );
	closeOutput( );
}





/*
 *  FUNCTIONS
 *	openInput	-  open the input file
 *	openOutput	-  open the output file
 *	closeInput	-  close the input file
 *	closeOutput	-  close the output file
 *
 *  DESCRIPTION
 *	The input and output files are opened and created, as appropriate.
 *	The special case of the '-' file name is watched for.
 */

static void				/* Returns nothing		*/
#ifdef __STDC__
openInput( char *filename )
#else
openInput( filename )
	char *filename;			/* Filename			*/
#endif
{
	if ( filename[0] == '-' && filename[1] == '\0' )
	{
		if ( verbose )
			fprintf( stderr, "Input from stdin\n" );
/** Not done in this demo **/
		return;
	}
	if ( verbose )
		fprintf( stderr, "Input from %s\n", filename );
/** Not done in this demo **/
}

static void				/* Returns nothing		*/
#ifdef __STDC__
openOutput( char *filename )
#else
openOutput( filename )
	char *filename;			/* Filename			*/
#endif
{
	if ( filename[0] == '-' && filename[1] == '\0' )
	{
		if ( verbose )
			fprintf( stderr, "Output to stdout\n" );
/** Not done in this demo **/
		return;
	}
	if ( verbose )
		fprintf( stderr, "Output to %s\n", filename );
/** Not done in this demo **/
}

static void				/* Returns nothing		*/
#ifdef __STDC__
closeInput( void )
#else
closeInput( )
#endif
{
/** Not done in this demo **/
}

static void				/* Returns nothing		*/
#ifdef __STDC__
closeOutput( void )
#else
closeOutput( )
#endif
{
/** Not done in this demo **/
}





/*
 *  FUNCTIONS
 *	scaleUniform	-  uniform scaling
 *	scaleXY		-  X-Y scaling
 *	scaleXYZ	-  X-Y-Z scaling
 *	translate	-  translate
 *	rotateX		-  X-Axis rotation
 *	rotateY		-  Y-Axis rotation
 *	rotateZ		-  Z-Axis rotation
 *
 *  DESCRIPTION
 *	These functions each create an appropriate transformation matrix
 *	and apply the transform to the geometry list.
 */

static void				/* Returns nothing		*/
#ifdef __STDC__
scaleUniform( float u )
#else
scaleUniform( u )
	float u;			/* Uniform scale factor		*/
#endif
{
	if ( verbose )
		fprintf( stderr, "Scale uniform by %f\n", u );

	/*
	 *  Scale the geometry.
	 */
/** Not done in this demo **/

}

static void				/* Returns nothing		*/
#ifdef __STDC__
scaleXY( float x, float y )
#else
scaleXY( x, y )
	float x, y;			/* X and Y scale factors	*/
#endif
{
	if ( verbose )
		fprintf( stderr, "Scale by (%f, %f)\n", x, y );

	/*
	 *  Scale the geometry.
	 */
/** Not done in this demo **/

}

static void				/* Returns nothing		*/
#ifdef __STDC__
scaleXYZ( float x, float y, float z )
#else
scaleXYZ( x, y, z )
	float x, y, z;			/* X, Y and Z scale factors	*/
#endif
{
	if ( verbose )
		fprintf( stderr, "Scale by (%f, %f, %f)\n", x, y, z );

	/*
	 *  Scale the geometry.
	 */
/** Not done in this demo **/

}

static void				/* Returns nothing		*/
#ifdef __STDC__
translate( float x, float y, float z )
#else
translate( x, y, z )
	float x, y, z;			/* X, Y and Z translation	*/
#endif
{
	if ( verbose )
		fprintf( stderr, "Translate by (%f, %f, %f)\n", x, y, z );

	/*
	 *  Translate the geometry.
	 */
/** Not done in this demo **/

}

static void				/* Returns nothing		*/
#ifdef __STDC__
rotateX( float angle )
#else
rotateX( angle )
	float angle;			/* Rotation angle		*/
#endif
{
	if ( verbose )
		fprintf( stderr, "X-Axis rotate by %f\n", angle );

	/*
	 *  Rotate the geometry.
	 */
/** Not done in this demo **/

}

static void				/* Returns nothing		*/
#ifdef __STDC__
rotateY( float angle )
#else
rotateY( angle )
	float angle;			/* Rotation angle		*/
#endif
{
	if ( verbose )
		fprintf( stderr, "Y-Axis rotate by %f\n", angle );

	/*
	 *  Rotate the geometry.
	 */
/** Not done in this demo **/

}

static void				/* Returns nothing		*/
#ifdef __STDC__
rotateZ( float angle )
#else
rotateZ( angle )
	float angle;			/* Rotation angle		*/
#endif
{
	if ( verbose )
		fprintf( stderr, "Z-Axis rotate by %f\n", angle );

	/*
	 *  Rotate the geometry.
	 */
/** Not done in this demo **/

}
