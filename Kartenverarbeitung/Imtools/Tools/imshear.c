/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imshear.c,v 1.13 1995/06/30 22:20:38 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imshear.c,v 1.13 1995/06/30 22:20:38 bduggan Exp $"

/**
 **  FILE
 **	imshear.c	-  Shears an image in the x or y direction  
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imshear shears an image(s) horizontally, or vertically, and
 **	stores the resulting image(s) into a new file. 
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	main		f  main program
 **
 **  PRIVATE CONTENTS
 **	toolCommand	v  tool-specific tool info
 **	toolHelp	v  tool-specific help
 **	toolFullHelp	v  tool-specific help
 **	toolOptions	v  tool-specific options
 **	toolEquivs	v  tool-specific equivalent keywords
 **
 **	toolInFilename	v  the name of the input file (could be 'stdin')
 **	toolOutFilename	v  the name of the output file (could be 'stdout')
 **
 **	toolInFormat	v  the name of the input file's format (could be '\0')
 **	toolOutFormat	v  the name of the output file's format (could be '\0')
 **
 **	toolInTable	v  a table for the storage of data read in
 **	toolInFlagsTable  v  a table for the storage of read flags
 **	toolOutFlagsTable v  a table for the storage of write flags
 **
 **	toolShear	v  Rotational direction 
 **	toolField	v  What fields to fill
 **	toolFieldStart  v  Value to start filling fields with
 **	toolFieldEnd	v  Value to End filling fields with
 **	toolXShear	v  Whether to fill in x or y direction
 **
 **	toolInit	f  initialize things for the tool
 **	fill		f  routine to fill in dst vfb
 **	imValParse	f  routine to parse command line inputs
 **
 **  HISTORY
 **	$Log: imshear.c,v $
 **	Revision 1.13  1995/06/30  22:20:38  bduggan
 **	added exit 0
 **
 **	Revision 1.12  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.11  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.10  1995/06/15  19:42:22  bduggan
 **	took out some useless vars
 **
 **	Revision 1.9  1995/05/18  00:04:45  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.8  94/10/03  15:49:47  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Removed all use of register keyword.
 **	Minimized use of custom SDSC types (e.g., uchar vs. unsigned char)
 **	Changed all float arguments to double.
 **	Added forward declarations.
 **	Added misc. casts to passify SGI and DEC compilers.
 **	Changed all macros and defined constants to have names
 **	starting with IM.
 **	Updated comments.
 **	Updated indenting on some code.
 **	Updated copyright message.
 **	
 ** 	Revision 1.7  92/12/03  13:06:04  nadeau
 ** 	More include file fixes.
 ** 	
 ** 	Revision 1.6  92/12/03  11:56:09  nadeau
 ** 	Added another include file.
 ** 	
 ** 	Revision 1.5  92/12/01  14:08:11  nadeau
 ** 	Total rewrite.
 ** 	
 ** 	Revision 1.4  92/11/04  14:03:41  groening
 ** 	problem with reattaching clt fixed
 ** 	
 ** 	Revision 1.3  92/09/02  11:14:55  vle
 ** 	Updated copyright notice.
 ** 	
 ** 	Revision 1.2  92/09/02  11:10:23  groening
 ** 	fixed up fill parts of tool
 ** 	in order to check boundary conditions.
 ** 	
 ** 	Revision 1.1  92/08/31  10:29:26  groening
 ** 	Initial revision
 ** 	
 **	
 **
 **/

/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1992.
 **     Custom development, Chris Groening, San Diego Supercomputer Center, 1992.
 **/

#include <math.h>
#ifndef M_PI
#include <values.h>
#endif
#include "imtools.h"

#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static void imValParse( char *option, float maxV );
#else
static void   toolInit( );		/* Initialize things		*/
static void   imValParse( );            /* parse after a field          */
#endif





/*
 *  GLOBALS
 *	toolCommand		-  tool-specific tool info
 *	toolHelp		-  tool-specific help
 *	toolOptions		-  tool-specific options
 *	toolEquivs		-  tool-specific equivalent keywords
 *
 *  DESCRIPTION
 *	toolCommand describes the command to the arg package.
 *
 *	toolHelp is the tool-specific help for the tool.  It will be
 *	concatenated with the generic image tools help message and
 *	added to the toolCommand structure as the help string to be
 *	printed after the option listing.
 *
 *	toolOptions is the tool-specific option list.  It will be merged
 *	with the generic image tools options, and the list of image file
 *	format names supported by the library.  This larger option list
 *	is then used as the list of options supported by the tool.
 *
 *	toolEquivs is the tool-specific option equivalent keyword list.
 *	It will be merged with the generic image tools equivs.  This large
 *	equivs list is then used as the list of equivs supported by the tool.
 */

static ArgCommand toolCommand =
{
	/* command name */		"imshear",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command shears an input image along the X or Y axis by a positive or\n\
negative shear angle.  The sheared result is stored into the given output\n\
file.  Input and output files may have different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] infilename outfilename",
	"[options...] infilename outfilename",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    Shear a PIXAR PIC image 50 degrees in the xdirection:\n\
        %command infile.pic -xshear 50 outfile.pic\n\
    Shear a PIXAR PIC image 20 degrees in the negative ydirection:\n\
        %command infile.pic -yshear -20 outfile.pic\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose images are to be sheared.  -outfile\n\
    selects the file into which to write the resulting sheared images.  The\n\
    input file is unaltered.\n\
\n\
Shearing:\n\
    Shearing slides one edge of an image along the X or Y axis, creating a\n\
    parallelogram.  An X direction shear slides an edge along the X axis,\n\
    while a Y direction shear slides an edge along the Y axis.  The amount\n\
    of the shear is controlled by a shear angle.  For X direction shears,\n\
    the shear angle is measured relative to the Y axis, and similarly, for\n\
    Y direction shears the shear angle is measured relative to the X axis.\n\
\n\
    -xshear degrees\n\
        Shear the image in the X direction with a shear angle of 'degrees'.\n\
        Positive angles shear counter-clockwise (right-hand rule), and\n\
        negative angles shear clockwise.  Angles are measured relative to a\n\
        vertical Y-axis.  X shears will widen an image creating 'empty'\n\
        triangles on the left and right sides of the source image.\n\
\n\
    -yshear degrees\n\
        Shear the image in the Y direction with a shear angle of 'degrees'.\n\
        Positive angles shear counter-clockwise (right-hand rule), and\n\
        negative angles shear clockwise.  Angles are measured relative to a\n\
        horizontal X-axis.  Y shears will increase the height of an image\n\
        creating 'empty' triangles on the top and bottom of the source image.\n\
Filling:\n\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
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

#define IM_TOOLNOPTIONS	14
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -%option argument specifies the name of the input file.              \n\
                                                                             \n\
    The file's format may be specified with the -in1format flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
    ",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    The -%option argument specifies the name of the output file.             \n\
                                                                             \n\
    The file's format may be specified with the -outformat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdout.  When using       \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "xshear", "degrees", "Shear along the X axis%end\
    -xshear degrees\n\
        Shear the image in the X direction with a shear angle of 'degrees'.\n\
        Positive angles shear counter-clockwise (right-hand rule), and\n\
        negative angles shear clockwise.  Angles are measured relative to a\n\
        vertical Y-axis.  X shears will widen an image creating 'empty'\n\
        triangles on the left and right sides of the source image.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "yshear", "degrees", "Shear along the Y axis%end\
    -yshear degrees\n\
        Shear the image in the Y direction with a shear angle of 'degrees'.\n\
        Positive angles shear counter-clockwise (right-hand rule), and\n\
        negative angles shear clockwise.  Angles are measured relative to a\n\
        horizontal X-axis.  Y shears will increase the height of an image\n\
        creating 'empty' triangles on the top and bottom of the source image.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

        { "index", "value_range", "Fill color index%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "red", "value_range", "Fill red%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "green", "value_range", "Fill green%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "blue", "value_range", "Fill blue%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "mono", "value_range", "Fill monochrome%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "hue", "value_range", "Fill hue%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "saturation", "value_range", "Fill saturation%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "intensity", "value_range", "Fill intensity%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "alpha", "value_range", "Fill alpha%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTFLOAT|ARGTRANGE },

        { "graduate", "direction", "Select direction for gradation%end\
    'Empty' triangles left over from shearing the image may be filled with\n\
    specific colors or alpha values using -mono, -index, -red, -green, -blue,\n\
    -hue, -saturation, -intensity, and -alpha.  Each of these options takes a\n\
    value or range of values to use in filling the area.\n\
\n\
    Gradient fills (ramps) may be done by using a fill value range, such as\n\
    '-red 0-255' and a gradient fill direction with -graduate.  Gradient\n\
    directions are 'none', 'vertical', or 'horizontal'.",
          ARGFNONE, 1, 1, ARGTSTRING },

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
 *  GLOBALS
 *	toolInFilename	-  the name of the input file (could be 'stdin')
 *	toolOutFilename	-  the name of the output file (could be 'stdout')
 *
 *	toolInFormat	-  the name of the input file's format (could be NULL)
 *	toolOutFormat	-  the name of the output file's format (could be NULL)
 *
 *	toolInTable	-  a table for the storage of data read in
 *	toolInFlagsTable -  a table for the storage of read flags
 *	toolOutFlagsTable-  a table for the storage of write flags
 *
 *	toolShear	-  Amount to shear by
 *
 *	toolField	-  Field to fill
 *	teolGraduate	-  Direction to ramp fill in
 *
 *	toolFieldStart  -  What to start filling toolField with
 *	toolFieldEnd    -  What to end filling toolField with
 *
 *	toolShear	-  Shearing direction 
 *	toolXShear	-  Wether to shear in x-direction or not 
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolInTable;		/* Data tag table		*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static float	  toolShear;		/* Rotational amount		*/

static float     toolFieldStart;       /* Blue data to fill            */
static float     toolFieldEnd;         /* Alpha data to fill           */

static int       toolField;            /* What fields to change        */
static int       toolGraduate;         /* which way toefill area       */

static int	  toolXShear;		/* Which way to shear		*/


#define IM_FILL(color,option,maxValue)                                  \
        if ( toolField & (color) )                                      \
        {                                                               \
                imValParse( option, (maxValue) );                       \
                if ( ImVfbFill( dstVfb, 0, 0,   			\
                        ImVfbQWidth(dstVfb), ImVfbQHeight(dstVfb),	\
			(color), toolFieldStart,      			\
                        toolFieldEnd, IMVFBINSIDE, toolGraduate,        \
                        dstVfb ) == IMVFBNULL )                         \
                {                                                       \
                        ImPError( ImToolsProgram );                     \
                        exit( 1 );                                      \
                }                                                       \
        }





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Shear each image.
 *		-  Replace the data table images with their rotated images.
 *		-  Write out the output file (get data from data table).
 *	That's about it.
 *
 *  NOTES
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
	int argc;                       /* Argument count               */
	char *argv[];                   /* Argument vector              */
#endif
{
	int         nInVfb;		/* Number of images in file	*/
	int         i;			/* Counter			*/

	TagEntry   *dataEntry;		/* Entry from data table	*/
        TagEntry   *newEntry;           /* Entry from data table        */
        int        nEntry;              /* index into vfb as to where image is*/

	ImVfb      *sourceVfb;		/* Source image			*/
	ImVfb	   *dstVfb;		/* Destination image		*/
	int	   dstW, dstH;		/* Destination VFB size		*/
	ImVfb	   *vfb;		/* Destination image		*/
	int	   fieldMask;		/* fieldmask of incoming vfb	*/
	int	   requiredFieldMask;	/* Fields required in sourcevfb */

	argc = __argc;
	argv = __argv;

	/*
	 *  Initialize things:
	 *	-  Prepare the arg parsing data, then parse the command-line.
	 *	-  Prepare the flags table based upon command-line args.
	 *	-  Determine the file formats for input and output files.
	 */
	toolInit( argc, argv );


	/*
	 *  Read in the input file.
	 *	-  Open the file (or stdin) and read data into the data table.
	 */
        requiredFieldMask = 0;
        if ( toolField & (IMRED | IMGREEN | IMBLUE | IMHUE | IMSATURATION | IMINTENSITY) )
                requiredFieldMask |= IMVFBRGB;
        if ( toolField & IMALPHA )
                requiredFieldMask |= IMVFBALPHA;
        if ( toolField & IMMONO )
                requiredFieldMask |= IMVFBMONO;
        if ( toolField & IMINDEX8 )
                requiredFieldMask |= IMVFBINDEX8;

  
	ImToolsFileRead( toolInFilename, toolInFormat, toolInFlagsTable,
		toolInTable );


	/*
	 *  Check for errors
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
	 *  Shear!
	 *	-  Walk the data table looking for images.  For each one found,
	 *	   get the VFB and shear the VFB data in the given direction.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );
		fieldMask = ImVfbQFields( sourceVfb );


		/*
		 *  Shear the image into new vfb.
		 */
		if ( ImToolsVerbose )
		{
			fprintf( stderr, 
			"%s: Shearing image %d of %d by %f degrees in the %c-direction\n",
				ImToolsProgram, i + 1, nInVfb,
				toolXShear?'x':'y', toolShear);
		}

		/*
		 *  If the input image has no alpha channel, but we've been
		 *  requested to fill one, create it.
		 */
		if ( (toolField & IMALPHA) && !(fieldMask & IMVFBALPHA) )
		{
			/*
			 *  Make a new VFB with alpha and copy the image
			 *  into it.  Set the alpha plane to 0.
			 */
			if ( (vfb = ImVfbAlloc( ImVfbQWidth( sourceVfb ),
				ImVfbQHeight( sourceVfb ),
				fieldMask | IMVFBALPHA ))== IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			if ( (vfb = ImVfbCopy( sourceVfb, 0, 0,
				ImVfbQWidth( sourceVfb ),
				ImVfbQHeight( sourceVfb ), fieldMask,
				vfb, 0, 0 )) == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			ImVfbClear( IMVFBALPHA, 0, vfb );
			fieldMask |= IMVFBALPHA;

			/*
			 *  Replace the old image in the data table with the
			 *  new VFB with the empty alpha.  Throw away the old
			 *  VFB.
			 */
			nEntry   = TagEntryQNthEntry( dataEntry );
			newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
			TagTableReplace( toolInTable, nEntry, newEntry );
			ImVfbFree( sourceVfb );
			sourceVfb = vfb;
		}

		if ( (fieldMask & IMVFBINDEX16) &&
			(requiredFieldMask & IMVFBINDEX8) )
			requiredFieldMask = (requiredFieldMask & ~IMVFBINDEX8) | IMVFBINDEX16;
		else if ( (fieldMask & IMVFBINDEX8) &&
			(requiredFieldMask & IMVFBINDEX16) )
			requiredFieldMask = (requiredFieldMask & ~IMVFBINDEX16)
				| IMVFBINDEX8;


		/*
		 *  Make sure it's got the fields we need for filling.
		 */
		if ( (fieldMask & requiredFieldMask) != requiredFieldMask )
		{
			fprintf( stderr, "%s: The input image %d of %d doesn't have those fields!\n", ImToolsProgram, i+1, nInVfb );
			exit( 1 );
		}



		/*
		 *  Shearing increases the size of the image.  Figure out
		 *  the new VFB's size.  We'll use this size when given
		 *  fill options.
		 */
		toolShear -= (float)(((int)(toolShear / 360.0)) * 360.0);
		if ( toolShear == 0.0 )
			continue;	/* Don't do anything		*/



		/*
		 *  Allocate an output VFB, clear it, and fill it.
		 */
		if (toolXShear == TRUE)
		{
			dstW = (int) (ImVfbQWidth( sourceVfb ) + 0.5 +
				(ImVfbQHeight( sourceVfb ) *
				fabs( tan( toolShear * M_PI / 180.0 ) )));
			dstH = ImVfbQHeight( sourceVfb );
		}
		else
		{
			dstW = ImVfbQWidth( sourceVfb );
			dstH = (int) (ImVfbQHeight( sourceVfb ) + 0.5 +
				(ImVfbQWidth( sourceVfb ) *
				fabs( sin( toolShear * M_PI/90.0 ) ) ));
		}
		if ( (dstVfb = ImVfbAlloc( dstW, dstH, fieldMask )) ==IMVFBNULL)
		{
			ImPError( ImToolsProgram );
			exit( 1 );
		}
		dstVfb = ImVfbClear( fieldMask, 0, dstVfb );


		/*
		 *  If the image is color indexed and has a CLT,
		 *  attach the same CLT to the destination image.
		 */
		if ( fieldMask & (IMVFBINDEX8 | IMVFBINDEX16) )
			ImVfbSClt( dstVfb, ImVfbQClt( sourceVfb ));


		/*
		 *  Fill the image in place.
		 */
		IM_FILL( IMRED,        "red",        255.0 );
		IM_FILL( IMGREEN,      "green",      255.0 );
		IM_FILL( IMBLUE,       "blue",       255.0 );
		IM_FILL( IMALPHA,      "alpha",      255.0 );
		IM_FILL( IMINDEX8,     "index",      255.0 );
		IM_FILL( IMINDEX16,    "index",      65535.0 );
		IM_FILL( IMMONO,       "mono",       1.0 );
		IM_FILL( IMINTENSITY,  "intensity",  1.0 );
		IM_FILL( IMSATURATION, "saturation", 1.0 );
		IM_FILL( IMHUE,        "hue",        360.0 );


		/*
		 * Shear in the X or Y direction.
		 */
		if ( toolXShear )
			dstVfb = ImVfbXShear( sourceVfb, toolShear, dstVfb );
		else
			dstVfb = ImVfbYShear( sourceVfb, toolShear, dstVfb );
		if ( dstVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't shear image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, 
				"%s: Unsheared image copied to output file.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Replace the tag table entry with the new destination VFB
		 *  and toss the source VFB to save space.
		 */
		nEntry   = TagEntryQNthEntry( dataEntry );
		newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &dstVfb );
		TagTableReplace( toolInTable, nEntry, newEntry );
		ImVfbFree( sourceVfb );
	}

	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolInTable );
	exit( 0 );
}





/*
 *  FUNCTION
 *	toolInit	-  initialize things for the tool
 *
 *  DESCRIPTION
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
 *  NOTES
 *	This function is included in most of the image tools and differs
 *	only in slight ways.  Typical differences include:
 *		-  the number of input and output file names found
 *		-  the number of input and output file formats found
 *		-  the number of command-line arg flags checked for
 */

static void				/* Returns nothing		*/
#ifdef __STDC__
toolInit(int argc, char *argv[]) 
#else
toolInit( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argument vector		*/
#endif
{
	int	    i;			/* Counter			*/
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/

	char       *tmp;		/* Temporary string holder	*/


	/*
	 *  Save the name of the program, as invoked.
	 */
	ImToolsProgram = argv[0];


	/*
	 *  Make a data table to hold the incomming data.
	 */
	if ( (toolInTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Use the standard Image Tools user registration and feedback forms.
	 */
	toolCommand.arg_register = ImToolsRegister;
	toolCommand.arg_feedback = ImToolsFeedback;




	/* Make help string      */
	toolCommand.arg_help2 = ImToolsMergeHelp(toolHelp, toolNote);

	/* Make full help string */
	tmp = toolHelp;
	tmp = ImToolsMergeHelp (tmp, toolFullHelp );
	tmp = ImToolsMergeHelp (tmp, ImToolsInHelp );
	tmp = ImToolsMergeHelp (tmp, ImToolsOutHelp);
	toolCommand.arg_fullhelp2 = tmp;


	/*
	 *  Build up an option list by merging the tool-specific options,
	 *  read options, write options, other standard options, and options for
	 *  the various image file formats.
	 *  Do the same for the equivalence lists.
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
	 *  Parse the command line!
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
	 *  Get the shearing direction and amount and the fill gradiant
	 *  direction.
	 */
	toolShear    = 0.0;
        toolGraduate = IMGRADHORIZ;
	toolXShear   = FALSE;
	if ( ArgQNOccur( "xshear" ) != 0 )
	{
		toolShear  = (float)(ArgQValue( "xshear", 0, 0 )->arg_f);
		toolXShear = TRUE;
	}
	if ( ArgQNOccur( "yshear" ) != 0 )
		toolShear  = (float)(ArgQValue( "yshear", 0, 0 )->arg_f);
	if ( toolShear >= 90.0 )
	{
		fprintf( stderr, "%s: A shear angle of >= 90 is impossible!\n",
			ImToolsProgram );
		fprintf (stderr, "%s: It would flatten your image into non-existance!\n",
			ImToolsProgram );
		exit( 1 );
	}

        if ( ArgQNOccur( "graduate" ) != 0 )
        {
                tmp = ArgQValue( "graduate", 0, 0 )->arg_s;
                i   = strlen( tmp );
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
         *  Get the fields to fill.
         */
	toolField = 0;
        if ( ArgQNOccur( "red" ) != 0 )                 toolField |= IMRED;
        if ( ArgQNOccur( "green" ) != 0 )               toolField |= IMGREEN;
        if ( ArgQNOccur( "blue" ) != 0 )                toolField |= IMBLUE;
#ifdef notdef
#endif
        if ( ArgQNOccur( "alpha" ) != 0 )               toolField |= IMALPHA;
        if ( ArgQNOccur( "index" ) != 0 )               toolField |= IMINDEX8;
        if ( ArgQNOccur( "mono" ) != 0 )                toolField |= IMMONO;
        if ( ArgQNOccur( "hue" ) != 0 )                 toolField |= IMHUE;
        if ( ArgQNOccur( "saturation" ) != 0 )          toolField |= IMSATURATION;
        if ( ArgQNOccur( "intensity" ) != 0 )           toolField |= IMINTENSITY;

        if ( toolField & (IMRED | IMGREEN | IMBLUE) )
        {
                if ( (toolField & ~(IMRED | IMGREEN | IMBLUE | IMALPHA)) != 0 )
                {
fprintf (stderr, "%i\n",toolField);
                        fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
                        fprintf( stderr, "%s: -red, -green, and -blue cannot be mixed with other fill options\n", ImToolsProgram );
                        exit( 1 );
                }
        }
        else if ( toolField & (IMHUE | IMSATURATION | IMINTENSITY) )
        {
                if ( (toolField & ~(IMHUE | IMSATURATION | IMINTENSITY | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
                        fprintf( stderr, "%s: -hue, -saturation, and -intensity cannot be mixed with other\n", ImToolsProgram );
                        fprintf( stderr, "%s: fill options.\n", ImToolsProgram);                        exit( 1 );
                }
        }
        else if ( toolField & IMMONO )
        {
                if ( (toolField & ~(IMMONO | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
                        fprintf( stderr, "%s: -mono cannot be mixed with other fill options\n", ImToolsProgram );
                        exit( 1 );
                }
        }
        else if ( toolField & IMINDEX8 )
        {
                if ( (toolField & ~(IMINDEX8 | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Filling can only occur in one color space at a time\n", ImToolsProgram );
                        fprintf( stderr, "%s: -index cannot be mixed with other fill options\n", ImToolsProgram );
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
 *  FUNCTION
 *	imValParse	-  get a value range
 *
 *  DESCRIPTION
 *	Take an argument value range and split it up into the start and end.
 */
static void				/* Returns nothing		*/
#ifdef __STDC__
imValParse( char *option, float maxV )
#else
imValParse( option, maxV )
	char      *option;		/* Option name			*/
	float	   maxV;		/* maximum value field can take */
#endif

{
        ArgValue   *value;              /* Argument value               */

	value = ArgQValue( option, 0, 0 );
	switch ( value->arg_rform )
	{
	case ARGRCLOSED:        /* n-m  start and end values		*/
		toolFieldStart = (float)(value->arg_fr1);
		toolFieldEnd   = (float)(value->arg_fr2);
		break;

	case ARGROPEN:          /* n-   start to max values		*/
		toolFieldStart = (float)(value->arg_f);
		toolFieldEnd   = maxV;
		break;

	case ARGRSINGLE:        /* n    value only			*/
		toolFieldStart = (float)(value->arg_f);
		toolFieldEnd   = (float)(value->arg_f);
		break;
	}
}
