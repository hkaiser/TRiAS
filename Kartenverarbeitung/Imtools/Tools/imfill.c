/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imfill.c,v 1.15 1995/06/30 22:18:33 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imfill.c,v 1.15 1995/06/30 22:18:33 bduggan Exp $"

/**
 **  FILE
 **	imfill.c	-  Fill an image with a color or ramp of colors
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imfill fills a portion of each input image with a solid color, or
 **	a ramp of colors, then saves the result to an output file.
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
 **	toolFill	v  Flip direction 
 **	toolFillMessage	v  Flip diagnostic message 
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imfill.c,v $
 **	Revision 1.15  1995/06/30  22:18:33  bduggan
 **	added some casts
 **
 **	Revision 1.14  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.13  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.12  1995/06/15  19:09:51  bduggan
 **	took out some useless vars.  Made the type of main 'void'.
 **
 **	Revision 1.11  1995/05/18  00:01:19  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.10  94/10/03  15:49:21  nadeau
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
 **     Revision 1.9  93/01/27  01:01:44  secoskyj
 **     Placed a condition in imValParse.  If the value being parsed
 **     is not between 0 and the passed maxValue then an error is
 **     output and the program exits.
 **     
 **     Revision 1.8  93/01/09  23:56:08  secoskyj
 **     "Full hue" spell chg -> "Fill gue" in toolOptions
 **     initialization.
 **     
 **     Revision 1.7  92/11/18  21:38:13  nadeau
 **     Corrected argument set typos.
 **     
 **     Revision 1.6  92/09/01  20:14:17  vle
 **     Updated copyright notice.
 **     
 **     Revision 1.5  92/09/01  12:20:53  nadeau
 **     Rearranged code a lot.  Added more error checks.  Added -mono.
 **     Removed default filling of all fields if no options given.
 **     Updated call arguments to ImVfbFill.  Updated option descriptions
 **     and help information.
 **     
 **     Revision 1.4  92/08/28  20:37:17  groening
 **     Very minor bug fixes.
 **     
 **     Revision 1.3  92/08/07  13:09:35  groening
 **     fixed index bugs
 **     
 **     Revision 1.2  92/07/07  09:24:40  groening
 **     fixed minor bugs, error messages
 **     
 **     Revision 1.1  92/06/12  11:02:57  groening
 **     Initial revision
 **     
 **	
 **
 **/

#include "imtools.h"


/**
 **  CODE CREDITS
 **     Custom development, Chris Groening, San Diego Supercomputer Center, 1992.
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1992.
 **/

#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static void imValParse( char *option, float maxV );
#else
static void imValParse( );		/* Parse argument range values	*/
static void toolInit( );                /* Initialize things            */
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
	/* command name */		"imfill",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command fills an image area with a single pixel value or gradation of pixel\n\
values, then stores the results in an output file.  Input and output files\n\
may have different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] [infilename] outfilename",
	"[options...] [infilename] outfilename",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    Create an RGB Sun rasterfile with black:\n\
	%command -xsize 640 -ysize 480 -red 0 -green 0 -blue 0 rgbblack.ras\n\
    Create an HDF image with red and alpha values of 255:\n\
	%command -xsize 640 -ysize 480 -red 255 -alpha 255 rgbared.hdf\n\
    White out the middle of an Alias PIX and ouput as an RGB file\n\
	%command map.pix -xpos 50 -ypos 50 -xsize 50 -ysize 50\n\
            -red 255 -blue 255 -green 255 mapwhite.rgb\n\
    Create a horizontal ramp shading from blue to red:\n\
	%command -xsize 200 -ysize 200 -red 20-120 -blue 150-50 purple.rgb\n\
    Create a vertical ramp shading from light grey to dark grey:\n\
	%command -xsize 200 -ysize 200 -inten .2-.6 -grad vertical gray.rgb\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file within which pixels will be filled.  -outfile\n\
    selects the file into which to write the resulting filled images.  The\n\
    input file is unaltered.\n\
\n\
    If no input file is given, a new output file is created containing a\n\
    single image xsize x ysize in size.\n\
\n\
Filling:\n\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
\n\
Graduations:\n\
    -graduate selects in what direction to compute a graduated fill (a ramp)\n\
    when a range of fill values are given to -red, -green, etc.:\n\
        none        Do not graduate.  Use the first value only.\n\
        horizontal  Graduate varying pixel values left to right.  Default.\n\
        vertical    Graduate varying pixel values top to bottom.\n\
\n\
Fill Area:\n\
    -xsize and -ysize select the size of the area to fill.  Both default to\n\
    the full width and height of the image.\n\
\n\
    -xposition and -yposition select the upper-left corner of the area to\n\
    fill and must both be within the bounds of the source image.  (0,0) is\n\
    the upper-left corner of the image.  Both default to the upper-left\n\
    corner.\n\
\n\
    -inside selects filling of the inside of the rectangle chosen by\n\
    -xposition, -yposition, -xsize, and -ysize.  -outside selects filling\n\
    of the area outside this rectangle instead.  -inside is the default.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	18
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    -infile selects the file within which pixels will be filled. \n\
\n\
    If no input file is given, a new output file is created containing a\n\
    single image xsize x ysize in size.\n\
                                                                             \n\
    The file's format may be specified with the -in1format flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
",
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    The -%option argument specifies the name of the output file.             \n\
                                                                             \n\
    The file's format may be specified with the -outformat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdout.  When using       \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "graduate", "direction", "Select direction for gradation%end\
Graduations:\n\
    -graduate selects in what direction to compute a graduated fill (a ramp)\n\
    when a range of fill values are given to -red, -green, etc.:\n\
        none        Do not graduate.  Use the first value only.\n\
        horizontal  Graduate varying pixel values left to right.  Default.\n\
        vertical    Graduate varying pixel values top to bottom.\
",
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "xposition", "x", "Specify left edge of fill area%end\
    -xposition and -yposition select the upper-left corner of the area to\n\
    fill and must both be within the bounds of the source image.  (0,0) is\n\
    the upper-left corner of the image.  Both default to the upper-left\n\
    corner.\
",
	  ARGFNONE,1,1,ARGTINT},

	{ "yposition", "y", "Specify top edge of fill area%end\
    -xposition and -yposition select the upper-left corner of the area to\n\
    fill and must both be within the bounds of the source image.  (0,0) is\n\
    the upper-left corner of the image.  Both default to the upper-left\n\
    corner.\
",
	  ARGFNONE,1,1,ARGTINT},

	{ "xsize", "width", "Specify width of fill area%end\
    -xsize and -ysize select the size of the area to fill.  Both default to\n\
    the full width and height of the image.",
	  ARGFNONE,1,1,ARGTINT},

	{ "ysize", "height", "Specify height of fill area%end\
    -xsize and -ysize select the size of the area to fill.  Both default to\n\
    the full width and height of the image.",
	  ARGFNONE,1,1,ARGTINT},

	{ "inside", NULL, "Fill inside of area%end\
    -inside selects filling of the inside of the rectangle chosen by\n\
    -xposition, -yposition, -xsize, and -ysize.  \n\
    \n\
    This is the default method.",
	  ARGFNONE,0,0,ARGTNONE},

	{ "outside", NULL, "Fill outside of area%end\
    -outside selects filling of the outside of the rectangle chosen by\n\
    -xposition, -yposition, -xsize, and -ysize.",
	  ARGFNONE,0,0,ARGTNONE},

	{ "index", "value_range", "Fill color index%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The index value must be between 0 and the 255 or 0 and 65536, \n\
    (depending on whether the image is 8-bit or 16-bit.)",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "mono", "value_range", "Fill monochrome%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The mono value must be 0 or 1.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "red", "value_range", "Fill red%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The red value must be between 0 and 255.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "green", "value_range", "Fill green%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The green value must be between 0 and 255.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "blue", "value_range", "Fill blue%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The blue value must be between 0 and 255.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "hue", "value_range", "Fill hue%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The hue must be between 0 and 360.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "saturation", "value_range", "Fill saturation%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The saturation must be between 0.0 and 1.0.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "intensity", "value_range", "Fill intensity%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The intensity must be between 0.0 and 1.0.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "alpha", "value_range", "Fill alpha%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
    \n\
    The alpha value must be between 0 and 255.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

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

static int	  toolXPosition;	/* left position of fill area	*/
static int       toolYPosition;	/* upper edge of the fill area  */
static int	  toolXSize;		/* width of the fill area	*/
static int	  toolYSize;		/* length of the fill area	*/
static int	  toolInOut;		/* where to fill in area	*/

static float	  toolFieldStart;	/* Blue data to fill		*/	
static float	  toolFieldEnd;		/* Alpha data to fill		*/	

static int	  toolField;		/* What fields to change 	*/
static int	  toolGraduate;		/* which way to fill area	*/




#define IM_FILL(color,option,maxValue)					\
	if ( toolField & (color) )					\
	{								\
		imValParse( option, (maxValue) );			\
		if ( ImVfbFill( srcVfb, toolXPosition, toolYPosition,	\
			regionW, regionH, (color), toolFieldStart,	\
			toolFieldEnd, toolInOut, toolGraduate,		\
			srcVfb ) == IMVFBNULL )				\
		{							\
			ImPError( ImToolsProgram );			\
			exit( 1 );					\
		}							\
	}



/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Fill each image.
 *		-  Replace the data table images with their smaller copy pieces.
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
main( int argc, char* argv[] )
#else
main( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[];			/* Argument vector		*/
#endif
{
	int         nInVfb;		/* Number of images in file	*/
	int         i;			/* Counter			*/

	TagEntry   *dataEntry;		/* Entry from data table	*/
	TagEntry   *newEntry;		/* Entry for data table		*/
	int	    nEntry;		/* index into vfb as to where image is*/

	ImVfb      *srcVfb;		/* Source image			*/
	ImVfb      *vfb;		/* Source image			*/
	int         fieldMask;		/* Source VFB fields		*/
	int	    requiredFieldMask;	/* Fields required in source VFB*/
	int         regionW, regionH;	/* Region width and height	*/
	int	    w, h;		/* Image width and height	*/

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
	 *  Read in the input file (if any).
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

        if ( *toolInFilename == '\0')
        {
		/*
		 *  No input file.
		 *	-  Allocate an image at the correct size and depth.
		 *	-  Clear it to all zeroes.
		 *	-  Add it to the data table as if it had been read in.
		 */
		if ( toolXSize == -1 || toolYSize == -1 )
		{
			fprintf( stderr, "%s: -xsize and -ysize must be given when no input file is provided\n",
				ImToolsProgram );
			exit( 1 );
		}
		if ( toolField == 0 )
                	vfb = ImVfbAlloc( toolXSize, toolYSize, IMVFBRGB );
		else
                	vfb = ImVfbAlloc( toolXSize, toolYSize, requiredFieldMask );

                if ( vfb == IMVFBNULL )
		{
			perror( ImToolsProgram );
                        exit(1);
                }
	        ImVfbClear( IMVFBALL, 0, vfb );

                TagTableAppend( toolInTable,
			TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb ) );
                nInVfb = 1;
        }
        else
        {
		/*
		 *  Read in the input file.
		 *      -  Open the file (or stdin) and read data into the
		 *	   data table.
		 */
                ImToolsFileRead( toolInFilename, toolInFormat, toolInFlagsTable,
			toolInTable );

		/*
		 *  Check for errors
		 *      -  no input images
		 */
                nInVfb = TagTableQNEntry( toolInTable, "image vfb" );
                if ( nInVfb == 0 )
                {
                        fprintf( stderr, "%s: Input file contains no images!\n",                                ImToolsProgram );
                        exit( 1 );
                }
        }


	/*
	 *  Fill each image in the input file.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &srcVfb );
                fieldMask = ImVfbQFields( srcVfb );


		/*
		 *  Fill it.
		 */
		if ( ImToolsVerbose )
		{
			fprintf( stderr, "%s: Filling image %d of %d \n",
					ImToolsProgram, i + 1, nInVfb);
		}


		/*
		 *  If the input image has no alpha channel, but we've been
		 *  requested to fill one, create it.
		 */
		if ( (toolField & IMALPHA) && !(fieldMask & IMVFBALPHA) )
		{
			/*
			 *  Copy the image into a new VFB with an Alpha.
			 */
			w = ImVfbQWidth( srcVfb );
			h = ImVfbQHeight( srcVfb );
			if ( (vfb = ImVfbAlloc( w, h, fieldMask | IMVFBALPHA ))== IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			if ( (vfb = ImVfbCopy( srcVfb, 0, 0, w, h, fieldMask,
				vfb, 0, 0 )) == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}
	        	ImVfbClear( IMVFBALPHA, 0, vfb );
			fieldMask |= IMVFBALPHA;

			/*
			 *  Replace the image in the data table.
			 */
			nEntry = TagEntryQNthEntry( dataEntry );
			newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
			TagTableReplace( toolInTable, nEntry, newEntry );
			ImVfbFree( srcVfb );
			srcVfb = vfb;
		}

		if ( (fieldMask & IMVFBINDEX16) && (requiredFieldMask & IMVFBINDEX8) )
			requiredFieldMask = (requiredFieldMask & ~IMVFBINDEX8) | IMVFBINDEX16;
		else if ( (fieldMask & IMVFBINDEX8) && (requiredFieldMask & IMVFBINDEX16) )
			requiredFieldMask = (requiredFieldMask & ~IMVFBINDEX16) | IMVFBINDEX8;


		/*
		 *  Make sure it's got the fields we need for filling.
		 */
		if ( (fieldMask & requiredFieldMask) != requiredFieldMask )
		{
			fprintf( stderr, "%s: The input image %d of %d doesn't have those fields!\n", ImToolsProgram, i+1, nInVfb );
			exit( 1 );
		}


		/*
		 *  Make sure the position is within the image.
		 */
		if ( toolXPosition > ImVfbQWidth( srcVfb ) ||
		     toolYPosition > ImVfbQHeight( srcVfb ) )
		{
			fprintf( stderr, "%s: Fill position is out of bounds for image %d of %d.\n",
				ImToolsProgram, i+1, nInVfb );
			exit( 1 );
		}


		/*
		 *  Get the width and height if none given.  Check given
		 *  height and width.
		 */
		if ( toolXSize == -1 )
		{
			/* No size given.  Fill to right edge of image.	*/
			regionW = ImVfbQWidth( srcVfb ) - toolXPosition;
		}
		else
		{
			/* Size given.  Clip to right edge of image.	*/
			regionW = toolXSize;
			if ( regionW > ImVfbQWidth( srcVfb ) - toolXPosition )
				regionW = ImVfbQWidth( srcVfb ) - toolXPosition;
		}
		if ( toolYSize == -1 )
		{
			/* No size given.  Fill to right edge of image.	*/
			regionH = ImVfbQHeight( srcVfb ) - toolYPosition;
		}
		else
		{
			/* Size given.  Clip to right edge of image.	*/
			regionH = toolYSize;
			if ( regionH > ImVfbQHeight( srcVfb ) - toolYPosition )
				regionH = ImVfbQHeight( srcVfb ) -toolYPosition;
		}


		/*
		 *  Check that the resulting fill region is reasonable.
		 */
		if ( regionW <= 0 || regionH <= 0 )
		{
			fprintf( stderr, "%s: Fill region size is zero for image %d of %d.\n", ImToolsProgram, i+1, nInVfb );
			exit( 1 );
		}


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

static void                             /* Returns nothing              */
#ifdef __STDC__
toolInit( int argc, char *argv[] )
#else
toolInit( argc, argv )
        int argc;                       /* Argument count               */
        char *argv[ ];                  /* Argument vector              */
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


	/* Initialize information */
	toolXPosition = 0;
	toolYPosition = 0;
	toolXSize     = -1;
	toolYSize     = -1;
	toolInOut     = IMVFBINSIDE;
	toolFieldStart= 0.0;
	toolFieldEnd  = 0.0;
	toolGraduate  = IMGRADHORIZ;
	toolField     = 0;

	/*
	 *  Get the fill information.
	 */
	if (ArgQNOccur ("xposition")!=0)
	{
		toolXPosition = (int) ArgQValue ("xpos",0,0)->arg_i;
		if ( toolXPosition < 0 )
		{
			fprintf (stderr, "%s: -xposition must be positive!\n",
				ImToolsProgram);
			exit(1);
		}
	}

	if (ArgQNOccur ("yposition")!=0)
	{
		toolYPosition = (int) ArgQValue ("ypos",0,0)->arg_i;
		if ( toolYPosition < 0 )
		{
			fprintf (stderr, "%s: -yposition must be positive!\n",
				ImToolsProgram);
			exit(1);
		}
	}

	if (ArgQNOccur ("xsize")!=0)
	{
		toolXSize = (int) ArgQValue ("xsize",0,0)->arg_i;
		if ( toolXSize <= 0 )
		{
			fprintf (stderr, "%s: -xsize must be > 0!\n",
				ImToolsProgram);
			exit(1);
		}
	}

	if (ArgQNOccur ("ysize")!=0)
	{
		toolYSize = (int) ArgQValue ("ysize",0,0)->arg_i;
		if ( toolYSize <= 0 )
		{
			fprintf (stderr, "%s: -ysize must be > 0!\n",
				ImToolsProgram);
			exit(1);
		}
	}

	if (ArgQNOccur ("outside")!=0)
	{
		if ( ArgQNOccur( "inside" ) != 0 )
		{
			fprintf( stderr, "%s: Only one of -inside or -outside may be given\n",
				ImToolsProgram );
			exit( 1 );
		}
		toolInOut=IMVFBOUTSIDE;
	}

	if (ArgQNOccur ("graduate")!=0)
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
	if ( ArgQNOccur( "red" ) != 0 )			toolField |= IMRED;
	if ( ArgQNOccur( "green" ) != 0 )		toolField |= IMGREEN;
	if ( ArgQNOccur( "blue" ) != 0 )		toolField |= IMBLUE;
	if ( ArgQNOccur( "alpha" ) != 0 )		toolField |= IMALPHA;
	if ( ArgQNOccur( "index" ) != 0 )		toolField |= IMINDEX8;
	if ( ArgQNOccur( "mono" ) != 0 )		toolField |= IMMONO;
	if ( ArgQNOccur( "hue" ) != 0 )			toolField |= IMHUE;
	if ( ArgQNOccur( "saturation" ) != 0 )		toolField |= IMSATURATION;
	if ( ArgQNOccur( "intensity" ) != 0 )		toolField |= IMINTENSITY;


	if ( toolField & (IMRED | IMGREEN | IMBLUE) )
	{
		if ( (toolField & ~(IMRED | IMGREEN | IMBLUE | IMALPHA)) != 0 )
		{
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
			fprintf( stderr, "%s: fill options.\n", ImToolsProgram);
			exit( 1 );
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


	/*
	 *  If only one filename has been given, consider it the output file.
	 */
	if ( *toolInFilename == '\0' )
	{
		if ( *toolOutFilename == '\0' )
		{
			fprintf( stderr, "%s:  An output file name must be given.\n", ImToolsProgram );
			fprintf( stderr, "%s:  Type '%s -help' for a list of options.\n", ImToolsProgram, ImToolsProgram );
			exit( 1 );
		}
	}
	else
	{
		if ( *toolOutFilename == '\0' )
		{
			strcpy( toolOutFilename, toolInFilename );
			*toolInFilename = '\0';
			strcpy( toolOutFormat, toolInFormat );
			*toolInFormat = '\0';
		}
	}
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

	if ( toolFieldStart > maxV || toolFieldEnd > maxV ||
		toolFieldStart < 0 || toolFieldEnd < 0 )
	{
		fprintf( stderr, "%s: -%s value invalid.  Must be between 0 and %g.\n", ImToolsProgram, option, maxV, option );
		exit( 1 );
	}
}
