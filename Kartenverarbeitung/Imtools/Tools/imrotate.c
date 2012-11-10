/**
 ** 	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imrotate.c,v 1.13 1995/06/30 22:20:15 bduggan Exp $
 ** 	Copyright (c) 1989-1995  San Diego Supercomputer Center (SDSC)
 ** 			a division of General Atomics, San Diego, California, USA
 **
 ** 	Users and possessors of this source code are hereby granted a
 ** 	nonexclusive, royalty-free copyright and design patent license to
 ** 	use this code in individual software.  License is not granted for
 ** 	commercial resale, in whole or in part, without prior written
 ** 	permission from SDSC.  This source is provided "AS IS" without express
 ** 	or implied warranty of any kind.
 **
 ** 	For further information contact:
 ** 			E-Mail: 		info@sds.sdsc.edu
 **
 ** 			Surface Mail:	Information Center
 ** 							San Diego Supercomputer Center
 ** 							P.O. Box 85608
 ** 							San Diego, CA  92138-5608
 ** 							(619) 534-5000
 **/

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imrotate.c,v 1.13 1995/06/30 22:20:15 bduggan Exp $"

/**
 **  FILE
 ** imrotate.c	-  rotate an image
 **
 **  PROJECT
 ** IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 ** imrotate rotate an image(s) clockwise, or counterclockwise, and
 ** stores the resulting image(s) into a new file. 
 **
 **  PUBLIC CONTENTS
 ** 		d =defined constant
 ** 		f =function
 ** 		m =defined macro
 ** 		t =typedef/struct/union
 ** 		v =variable
 ** 		? =other
 **
 ** main		f  main program
 **
 **  PRIVATE CONTENTS
 ** toolCommand v  tool-specific tool info
 ** toolHelp	v  tool-specific help
 ** toolFullHelp	v  tool-specific help
 ** toolOptions v  tool-specific options
 ** toolEquivs	v  tool-specific equivalent keywords
 **
 ** toolInFilename	v  the name of the input file (could be 'stdin')
 ** toolOutFilename v  the name of the output file (could be 'stdout')
 **
 ** toolInFormat	v  the name of the input file's format (could be '\0')
 ** toolOutFormat	v  the name of the output file's format (could be '\0')
 **
 ** toolInTable v  a table for the storage of data read in
 ** toolInFlagsTable  v  a table for the storage of read flags
 ** toolOutFlagsTable v  a table for the storage of write flags
 **
 ** toolRotate	v  Rotational amount 
 ** toolField	v  What field to fill in vfb
 ** toolFieldStart	v  What to start filling field with
 ** toolFieldEnd	v  What to end filling field with
 **
 ** toolInit	f  initialize things for the tool
 ** fill		f  prepares vfb to send to ImVfbFill
 ** imValParse	f  gets the start and end values for use in ImVfbFill
 **
 **  HISTORY
 ** $Log: imrotate.c,v $
 ** Revision 1.13  1995/06/30  22:20:15  bduggan
 ** added some casts
 **
 ** Revision 1.12  1995/06/29  01:05:35  bduggan
 ** changed date in arg structure to be 95
 **
 ** Revision 1.11  1995/06/29  00:40:07  bduggan
 ** updated copyright
 **
 ** Revision 1.10  1995/06/15  19:39:24  bduggan
 ** took out some useless vars
 **
 ** Revision 1.9  1995/05/18  00:04:16	bduggan
 ** Added new read-write options routines.	Added option-specific help.
 **
 ** Revision 1.8  94/10/03	15:49:42  nadeau
 ** Updated to ANSI C and C++ compatibility.
 ** Removed all use of register keyword.
 ** Minimized use of custom SDSC types (e.g., uchar vs. unsigned char)
 ** Changed all float arguments to double.
 ** Added forward declarations.
 ** Added misc. casts to passify SGI and DEC compilers.
 ** Changed all macros and defined constants to have names
 ** starting with IM.
 ** Updated comments.
 ** Updated indenting on some code.
 ** Updated copyright message.
 ** 
 ** Revision 1.7  93/01/27	01:21:02  secoskyj
 ** Bug fix.  Would Seg. Fault when a alpha channel is used as a background
 ** and an alpha channel is not in the image to be rotated.  Also inserted
 ** condition into imValParse so that background fill values would be
 ** bound checked between zero and thier maximum values.
 ** 
 ** Revision 1.6  92/12/03	13:05:57  nadeau
 ** More include file fixes.
 ** 
 ** Revision 1.5  92/12/03	11:51:31  nadeau
 ** Added another include file.
 ** 
 ** Revision 1.4  92/12/01	22:39:34  nadeau
 ** Corrected help message.
 ** 
 ** Revision 1.3  92/12/01	14:07:59  nadeau
 ** Total rewrite.
 ** 
 ** Revision 1.2  92/11/04	13:51:29  groening
 ** problems with reattaching clt fixed
 ** 
 ** Revision 1.1  92/09/02	11:13:12  groening
 ** Initial revision
 **
 **/

/**
 **  CODE CREDITS
 ** 	Custom development, Chris Groening, San Diego Supercomputer Center, 1992.
 **/

#include <math.h>
#ifndef M_PI
#include <values.h>
#endif
#include "imtools.h"


#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static void imValParse( char *option, float maxV);
#else
static void toolInit( );		/* Initialize things		*/
static void imValParse( );				/* parse after a field			*/
#endif





/*
 *	GLOBALS
 *	toolCommand 	-  tool-specific tool info
 *	toolHelp		-  tool-specific help
 *	toolOptions 	-  tool-specific options
 *	toolEquivs		-  tool-specific equivalent keywords
 *
 *	DESCRIPTION
 *	toolCommand describes the command to the arg package.
 *
 *	toolHelp is the tool-specific help for the tool.  It will be
 *	concatenated with the generic image tools help message and
 *	added to the toolCommand structure as the help string to be
 *	printed after the option listing.
 *
 *	toolOptions is the tool-specific option list.  It will be merged
 *	with the generic image tools options, and the list of image file
 *	format names supported by the library.	This larger option list
 *	is then used as the list of options supported by the tool.
 *
 *	toolEquivs is the tool-specific option equivalent keyword list.
 *	It will be merged with the generic image tools equivs.	This large
 *	equivs list is then used as the list of equivs supported by the tool.
 */

static ArgCommand toolCommand =
{
	/* command name */		"imrotate",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command rotates an input image by an arbitrary angle, positive or\n\
negative, and stores the result in the output file.  Input and output \n\
files may have different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags 	*/
	"[options...] infilename outfilename",
	"[options...] infilename outfilename",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
	Rotate a PIXAR PIC image counter-clockwise 90 degrees:\n\
		%command infile.pic -rotate 90 outfile.pic\n\
	Rotate an Alias PIX image clockwise 40 degrees and store as PIC file:\n\
		%command infile.pix -rotate 40 outfile.pic\n\
";

static char *toolFullHelp = "\n\
Files:\n\
	-infile selects the file whose images are to be rotated.  -outfile\n\
	selects the file into which to write the resulting rotated images.	The\n\
	input file is unaltered.\n\
\n\
Rotating:\n\
	-rotate gives the number of degrees by which to rotate the image.\n\
	Positive angles rotate counter-clockwise (right-hand rule), while\n\
	negative angles rotate clockwise.\n\
\n\
	Rotated images are usually larger than the originals and have 'empty'\n\
	triangular corners.\n\
\n\
Filling:\n\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
	This is an abbreviated help listing.  For a full listing of options,\n\
	including information about file formats supported, type:\n\
		%command -fullhelp\n\
	For help about a specific option, type\n\
		%command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS 13
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
	The -%option argument specifies the name of the input file. 			 \n\
																			 \n\
	The file's format may be specified with the -in1format flag.			 \n\
																			 \n\
	A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
	an explicit format name may be necessary.								  \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
	The -%option argument specifies the name of the output file.			 \n\
																			 \n\
	The file's format may be specified with the -outformat flag.			 \n\
																			 \n\
	A single dash ('-') for the filename indicates stdout.	When using		 \n\
	stdout, an explicit format name is necessary.							  \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "rotate", "degrees", "Specify rotation angle%end\
	-rotate gives the number of degrees by which to rotate the image.\n\
	Positive angles rotate counter-clockwise (right-hand rule), while\n\
	negative angles rotate clockwise.",
	  ARGFREQUIRED, 1, 1, ARGTFLOAT },

		{ "index", "value_range", "Fill color index%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "red", "value_range", "Fill red%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "graduate", "direction", "Select direction for gradation%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTSTRING },

		{ "green", "value_range", "Fill green%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "blue", "value_range", "Fill blue%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "mono", "value_range", "Fill monochrome%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "hue", "value_range", "Fill hue%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "saturation", "value_range", "Fill saturation%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "intensity", "value_range", "Fill intensity%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

		{ "alpha", "value_range", "Fill alpha%end\
	'Empty' triangles left over from rotating the image may be filled with\n\
	specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
	-hue, -saturation, -intensity, and -alpha.	Each of these options takes a\n\
	value or range of values to use in filling the area.\n\
\n\
	Gradient fills (ramps) may be done by using a fill value range, such as\n\
	'-red 0-255' and a gradient fill direction with -graduate.	Gradient\n\
	directions are 'none', 'vertical', or 'horizontal'.",
		  ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

};

#define IM_TOOLNEQUIVS	0
#if IM_TOOLNEQUIVS == 0
static ArgEquiv *toolEquivs;
#else
static ArgEquiv toolEquivs[IM_TOOLNEQUIVS] =
{
};
#endif





/*
 *	GLOBALS
 *	toolInFilename	-  the name of the input file (could be 'stdin')
 *	toolOutFilename -  the name of the output file (could be 'stdout')
 *
 *	toolInFormat	-  the name of the input file's format (could be NULL)
 *	toolOutFormat	-  the name of the output file's format (could be NULL)
 *
 *	toolInTable -  a table for the storage of data read in
 *	toolInFlagsTable -	a table for the storage of read flags
 *	toolOutFlagsTable-	a table for the storage of write flags
 *
 *	toolRotate	-  Rotational direction 
 *	toolField	-  What field to fill with the fill options
 *	toolFieldStart	-  What to start filling field with
 *	toolFieldEnd	-  What to end filling field with
 *	toolGraduate	-  Which way to ramp filling
 *
 *	DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char 	 toolInFilename[1024];	/* Input file name		*/
static char 	 toolInFormat[1024];	/* Input file's format name */

static char 	 toolOutFilename[1024];/* Output file name		*/
static char 	 toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolInTable;		/* Data tag table		*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable; /* Flags tag table		*/

static float	  toolRotate;		/* Rotational amount		*/

static float	 toolFieldStart;	   /* Blue data to fill 		   */
static float	 toolFieldEnd;		   /* Alpha data to fill		   */

static int		 toolField; 		   /* What fields to change 	   */
static int		 toolGraduate;		   /* which way to fill area	   */

#define IM_FILL(color,option,maxValue)									\
		if ( toolField & (color) )										\
		{																\
				imValParse( option, (maxValue) );						\
				if ( ImVfbFill( dstVfb, 0, 0,				\
						ImVfbQWidth(dstVfb), ImVfbQHeight(dstVfb),	\
			(color), toolFieldStart,				\
						toolFieldEnd, IMVFBINSIDE, toolGraduate,		\
						dstVfb ) == IMVFBNULL ) 						\
				{														\
						ImPError( ImToolsProgram ); 					\
						exit( 1 );										\
				}														\
		}





/*
 *	FUNCTION
 *	main	-  main program
 *
 *	DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Rotate each image.
 *		-  Replace the data table images with their rotated images.
 *		-  Write out the output file (get data from data table).
 *	That's about it.
 *
 *	NOTES
 *	This 'main' is pretty much the same for each of the image tools.
 *	Differences between tools include:
 *		-  the number of input files read in
 *		-  the number of output files written out
 *		-  the actions taken on the data between read and write
 */

void
#ifdef __STDC__
main( int argc, char *argv[] )
#else
main( argc, argv )
	int argc;						/* Argument count				*/
	char *argv[];					/* Argument vector				*/
#endif
{
	int 		nInVfb; 	/* Number of images in file */
	int 		i;			/* Counter			*/

	TagEntry   *dataEntry;		/* Entry from data table	*/

	ImVfb	   *vfb;		/* Source image 		*/
	ImVfb	   *sourceVfb;		/* Source image 		*/
	ImVfb	   *dstVfb; 	/* Destination image		*/
		TagEntry   *newEntry;			/* Entry from data table		*/
		int 	   nEntry;				/* index into vfb as to where image is*/
	int    fieldMask;		/* fields in incoming vfb	*/
		int    requiredFieldMask;	/* required mask for vfb	*/

	double	   rotation;		/* Rotation angle		*/
	double	   rad; 		/* Rotation angle in radians	*/
	int    hDst, wDst;		/* dst height and width 	*/
	int    hSrc, wSrc;		/* src height and width 	*/

//	argc = __argc;
//	argv = __argv;

	/*
	 *	Initialize things:
	 *	-  Prepare the arg parsing data, then parse the command-line.
	 *	-  Prepare the flags table based upon command-line args.
	 *	-  Determine the file formats for input and output files.
	 */
	toolInit( argc, argv );

		requiredFieldMask = 0;
		if ( toolField & (IMRED | IMGREEN | IMBLUE | IMHUE |
		 IMSATURATION | IMINTENSITY) )
				requiredFieldMask |= IMVFBRGB;
		if ( toolField & IMALPHA )
				requiredFieldMask |= IMVFBALPHA;
		if ( toolField & IMMONO )
				requiredFieldMask |= IMVFBMONO;
		if ( toolField & IMINDEX8 )
				requiredFieldMask |= IMVFBINDEX8;
		if ( toolField & IMINDEX16 )
				requiredFieldMask |= IMVFBINDEX16;



	/*
	 *	Read in the input file.
	 *	-  Open the file (or stdin) and read data into the data table.
	 */
	ImToolsFileRead( toolInFilename, toolInFormat, toolInFlagsTable,
		toolInTable );


	/*
	 *	Check for errors
	 *	-  no input images
	 */
	nInVfb = TagTableQNEntry( toolInTable, "image vfb" );
	if ( nInVfb == 0 )
	{
		fprintf( stderr, "%s: Input file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}


	/*
	 *	Modulo the rotation angle by 360.0 and convert to radians.
	 */
	rotation = toolRotate - ((int)(toolRotate / 360.0)) * 360.0;
	rad 	 = rotation * (M_PI / 180.0);


	/*
	 *	Rotate!
	 *	-  Walk the data table looking for images.	For each one found,
	 *	   get the VFB and rotate it.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *	Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );

		fieldMask = ImVfbQFields( sourceVfb );
		hSrc	  = ImVfbQHeight( sourceVfb );
		wSrc	  = ImVfbQWidth(  sourceVfb );

		if ( ImToolsVerbose )
		{
			fprintf( stderr, "%s: Rotating image %d of %d by %f degrees\n",
				ImToolsProgram, i + 1, nInVfb, toolRotate );
		}


		/*
		 *	If we are requested to fill an ALPHA channel, but the
		 *	image doesn't have one, them make one and clear it.
		 */
		if ( (toolField & IMALPHA) && !(fieldMask & IMVFBALPHA) )
		{
			/*
			 *	Copy the image into a new VFB with an Alpha.
			 */
			if ( (vfb = ImVfbAlloc( wSrc, hSrc, fieldMask | IMVFBALPHA ))== IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				fprintf( stderr, "%s: Couldn't rotate image %d of %d.\n",
					ImToolsProgram, i + 1, nInVfb );
				fprintf( stderr, "%s: Unrotated image copied to output file.\n",
					ImToolsProgram );
				continue;
			}
			if ( (vfb = ImVfbCopy( sourceVfb, 0, 0, wSrc, hSrc, fieldMask, vfb, 0, 0 )) == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				fprintf( stderr, "%s: Couldn't rotate image %d of %d.\n",
					ImToolsProgram, i + 1, nInVfb );
				fprintf( stderr, "%s: Unrotated image copied to output file.\n",
					ImToolsProgram );
				continue;
			}
			ImVfbClear( IMVFBALPHA, 0, vfb );
			fieldMask |= IMVFBALPHA;
			ImVfbSClt( vfb, ImVfbQClt( sourceVfb ) );


		/*
		 *	Replace the image in the data table and toss
		 *	the original.
		 */
			nEntry	 = TagEntryQNthEntry( dataEntry );
			newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
			TagTableReplace( toolInTable, nEntry, newEntry );
			ImVfbFree( sourceVfb );
			sourceVfb = vfb;
		}

		if ( (fieldMask & IMVFBINDEX16) && (requiredFieldMask & IMVFBINDEX8) )
			requiredFieldMask = (requiredFieldMask & ~IMVFBINDEX8) | IMVFBINDEX16;
		else if ( (fieldMask & IMVFBINDEX8) && (requiredFieldMask & IMVFBINDEX16) )
			requiredFieldMask = (requiredFieldMask & ~IMVFBINDEX16)|IMVFBINDEX8;


		/*
		 *	Make sure it's got the fields we need for filling.
		 */
		if ( (fieldMask & requiredFieldMask) != requiredFieldMask )
		{
			fprintf( stderr, "%s: The input image %d of %d doesn't have those fields!\n", ImToolsProgram, i+1, nInVfb );
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't rotate image %d of %d.\n", ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Unrotated image copied to output file.\n", ImToolsProgram );
			continue;
		}


		/*
		 *	Allocate a destination VFB big enough for the rotated image.
		 */
		wDst = (int) (0.5 + fabs( sin( rad )*hSrc ) + fabs( cos( rad )*wSrc ));
		hDst = (int) (0.5 + fabs( sin( rad )*wSrc ) + fabs( cos( rad )*hSrc ));
		if ( (dstVfb = ImVfbAlloc( wDst, hDst, fieldMask )) ==IMVFBNULL)
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't rotate image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Unrotated image copied to output file.\n",
				ImToolsProgram );
			continue;
		}
		ImVfbClear( fieldMask, 0, dstVfb );


		/*
		 *	If the source image has a color table, link the same
		 *	one to the destination image.
		 */
		ImVfbSClt( dstVfb, ImVfbQClt( sourceVfb ) );


		/*
		 *	Fill the image in place.
		 */
		IM_FILL( IMRED, 	   "red",		 255.0 );
		IM_FILL( IMGREEN,	   "green", 	 255.0 );
		IM_FILL( IMBLUE,	   "blue",		 255.0 );
		IM_FILL( IMALPHA,	   "alpha", 	 255.0 );
		IM_FILL( IMINDEX8,	   "index", 	 255.0 );
		IM_FILL( IMINDEX16,    "index", 	 65535.0 );
		IM_FILL( IMMONO,	   "mono",		 1.0 );
		IM_FILL( IMINTENSITY,  "intensity",  1.0 );
		IM_FILL( IMSATURATION, "saturation", 1.0 );
		IM_FILL( IMHUE, 	   "hue",		 360.0 );


		/*
		 *	Rotate the image.
		 */
		if ( ImVfbRotate( sourceVfb, rotation, dstVfb ) == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't rotate image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Unrotated image copied to output file.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *	Replace the tagTable VFB with the rotated one and
		 *	toss the original.
		 */
		nEntry	 = TagEntryQNthEntry( dataEntry );
		newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &dstVfb );
		TagTableReplace( toolInTable, nEntry, newEntry );
		ImVfbFree( sourceVfb );
	}

	/*
	 *	Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolInTable );
	ImVfbFree( dstVfb );

	exit( 0 );
}





/*
 *	FUNCTION
 *	toolInit	-  initialize things for the tool
 *
 *	DESCRIPTION
 *	The tool's argument parsing data structures are set up to include:
 *		- the full help message (generic help + tool-specific help)
 *		- the full option list (generic options + tool-specific options)
 *		- the full equivs list (generic equivs + tool-specific equivs)
 *
 *	Command-line arguments are then parsed.  The results are used to
 *	set up the flags table (the generic -out* options).
 *
 *	Input and output file's names and formats are determined from the
 *	command-line arguments.
 *
 *	NOTES
 *	This function is included in most of the image tools and differs
 *	only in slight ways.  Typical differences include:
 *		-  the number of input and output file names found
 *		-  the number of input and output file formats found
 *		-  the number of command-line arg flags checked for
 */

static void 			/* Returns nothing		*/
#ifdef __STDC__
toolInit(int argc, char *argv[]) 
#else
toolInit( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argument vector		*/
#endif
{
	int 	i;			/* Counter			*/
	int 		nOpt;		/* Number of options		*/
	int 		nEquiv; 	/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options 	*/
	ArgOption  *options;		/* Argument options 	*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords */
	ArgEquiv   *equivs; 	/* Argument equivalent keywords */

	char	   *tmp;		/* Temporary string holder	*/


	/*
	 *	Save the name of the program, as invoked.
	 */
	ImToolsProgram = argv[0];


	/*
	 *	Make a data table to hold the incomming data.
	 */
	if ( (toolInTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}


	/*
	 *	Use the standard Image Tools user registration and feedback forms.
	 */
	toolCommand.arg_register = ImToolsRegister;
	toolCommand.arg_feedback = ImToolsFeedback;




	/* Make help string 	 */
	toolCommand.arg_help2 = ImToolsMergeHelp(toolHelp, toolNote);

	/* Make full help string */
	tmp = toolHelp;
	tmp = ImToolsMergeHelp (tmp, toolFullHelp );
	tmp = ImToolsMergeHelp (tmp, ImToolsInHelp );
	tmp = ImToolsMergeHelp (tmp, ImToolsOutHelp);
	toolCommand.arg_fullhelp2 = tmp;


	/*
	 *	Build up an option list by merging the tool-specific options,
	 *	read options, write options, other standard options, and options for
	 *	the various image file formats.
	 *	Do the same for the equivalence lists.
	 */
	nOpt = ImToolsMergeOptions( "in", IM_TOOLNOPTIONS, toolOptions,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "out", nOpt, options,
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "in", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs );
	nEquiv = ImToolsMergeEquivs( "out", nEquiv, equivs,
		IMTOOLSNWRITEEQUIVS, ImToolsWriteEquivs, &equivs1 );
	nEquiv = ImToolsMergeEquivs( "", nEquiv, equivs1,
		IMTOOLSNOTHEREQUIVS, ImToolsOtherEquivs, &equivs );

	if ( nOpt == -1 || nEquiv==-1)
	{
		ImPError( ImToolsProgram );
		exit( 1 );
	}


	/*
	 *	Parse the command line!
	 */
	nOpt = ArgParse( argc, argv, &toolCommand, nOpt, options,
		nEquiv, equivs );

#if defined(_USE_MMFS_FOR_VFB_OPTIONAL)
// Speicherhandling auswerten
	if (ArgQNOccur("memory") != 0) {
	char *tmp = ArgQValue( "memory", 0, 0 )->arg_s;

		if (strcmp (tmp, "ram") && strcmp (tmp, "file")) {
			fprintf( stderr, "%s: -memory must be 'ram' or 'file'\n",
				ImToolsProgram );
			exit( 1 );
		}
		ImToolsSetUseMMFiles(strcmp (tmp, "ram") ? 1 : 0);
	} else
		ImToolsSetUseMMFiles(1);
#endif // defined(_USE_MMFS_FOR_VFB_OPTIONAL)


	/*
	 *	Get the rotational direction.
	 */

	if ( ArgQNOccur( "rotate" ) != 0 )
		toolRotate	=  (float)(ArgQValue( "rotate", 0, 0 )->arg_f);

	toolField = 0;
	toolGraduate = IMGRADHORIZ;
		if (ArgQNOccur ("graduate")!=0)
		{
				tmp = ArgQValue( "graduate", 0, 0 )->arg_s;
				i	= strlen( tmp );
				if ( strncmp( tmp, "none", i ) == 0 )
						toolGraduate=IMGRADNONE;
				else if ( strncmp( tmp, "vertical", i ) == 0 )
						toolGraduate=IMGRADVERT;
				else if ( strncmp( tmp, "horizontal", i ) == 0 )
						toolGraduate = IMGRADHORIZ;
				else
				{
						fprintf( stderr, "%s: Unknown gradation direction '%s'\n",
								ImToolsProgram, tmp );
				}
	}


		/*
		 *	Get the fields to fill.
		 */
		if ( ArgQNOccur( "red" ) != 0 ) 				toolField |= IMRED;
		if ( ArgQNOccur( "green" ) != 0 )				toolField |= IMGREEN;
		if ( ArgQNOccur( "blue" ) != 0 )				toolField |= IMBLUE;
		if ( ArgQNOccur( "alpha" ) != 0 )				toolField |= IMALPHA;
		if ( ArgQNOccur( "index" ) != 0 )				toolField |= IMINDEX8;
		if ( ArgQNOccur( "mono" ) != 0 )				toolField |= IMMONO;
		if ( ArgQNOccur( "hue" ) != 0 ) 				toolField |= IMHUE;
		if ( ArgQNOccur( "saturation" ) != 0 )			toolField |= IMSATURATION;
		if ( ArgQNOccur( "intensity" ) != 0 )			toolField |= IMINTENSITY;


		if ( toolField & (IMRED | IMGREEN | IMBLUE) )
		{
				if ( (toolField & ~(IMRED | IMGREEN | IMBLUE | IMALPHA)) != 0 )
				{
						fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
						fprintf( stderr, "%s: RGB, HSI, mono and color index fill options cannot be mixed\n", ImToolsProgram );
						exit( 1 );
				}
		}
		else if ( toolField & (IMHUE | IMSATURATION | IMINTENSITY) )
		{
				if ( (toolField & ~(IMHUE | IMSATURATION | IMINTENSITY | IMALPHA)) != 0 )
				{
						fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
						fprintf( stderr, "%s: RGB, HSI, mono and color index fill options cannot be mixed\n", ImToolsProgram );
				}
		}
		else if ( toolField & IMMONO )
		{
				if ( (toolField & ~(IMMONO | IMALPHA)) != 0 )
				{
						fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
						fprintf( stderr, "%s: RGB, HSI, mono and color index fill options cannot be mixed\n", ImToolsProgram );
						exit( 1 );
				}
		}
		else if ( toolField & IMINDEX8 )
		{
				if ( (toolField & ~(IMINDEX8 | IMALPHA)) != 0 )
				{
						fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
						fprintf( stderr, "%s: RGB, HSI, mono and color index fill options cannot be mixed\n", ImToolsProgram );
						exit( 1 );
				}
		}




	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolInFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolInFlagsTable, "in");
	ImToolsGetNameAndFormat ( "in", 0, toolInFilename, toolInFormat);

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);

}



/*
 *	FUNCTION
 *		imValParse		-  get a value range
 *
 *	DESCRIPTION
 *	Take an argument value range and split it up into the start and end.
 */
static void 						   /* Returns nothing			   */
#ifdef __STDC__
imValParse( char *option, float maxV)
#else
imValParse( option, maxV)
		char	  *option;				/* Option name					*/
		float	   maxV;				/* maximum value field can take */
#endif

{
		ArgValue   *value;				/* Argument value				*/

		value = ArgQValue( option, 0, 0 );
		switch ( value->arg_rform )
		{
		case ARGRCLOSED:		/* n-m	start and end values	*/
				toolFieldStart = (float)(value->arg_fr1);
				toolFieldEnd   = (float)(value->arg_fr2);
				break;

		case ARGROPEN:			/* n-	length only 			*/
				toolFieldStart = (float)(value->arg_f);
				toolFieldEnd = maxV;
		break;

		case ARGRSINGLE:		/* n	length only 			*/
				toolFieldStart = (float)(value->arg_f);
				toolFieldEnd = (float)(value->arg_f);
				break;
		}

	if ( toolFieldStart > maxV || toolFieldEnd > maxV ||
		toolFieldStart < 0 || toolFieldEnd < 0 )
	{
		fprintf( stderr, "%s: -%s value invalid.  Must be between 0 and %g.\n", ImToolsProgram, option, maxV, option );
		exit( 1 );
	}
}
