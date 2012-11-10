/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imscale.c,v 1.13 1995/06/30 22:20:25 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imscale.c,v 1.13 1995/06/30 22:20:25 bduggan Exp $"

/**
 **  FILE
 **	imscale.c	-  Scale the size of an image
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imscale scales an image into a new file.
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
 **	toolXScale	v  X scale factor
 **	toolYScale	v  Y scale factor
 **	toolXSize	v  X desired size
 **	toolYSize	v  Y desired size
 **
 **	toolInit	f  initialize things for the tool
 **	toolPromoteRgb	f  promote an image to RGB
 **	toolDemoteRgb	f  demote an image from RGB
 **
 **  HISTORY
 **	$Log: imscale.c,v $
 **	Revision 1.13  1995/06/30  22:20:25  bduggan
 **	added some casts
 **
 **	Revision 1.12  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.11  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.10  1995/06/15  19:41:10  bduggan
 **	took out some useless vars
 **
 **	Revision 1.9  1995/05/18  00:04:22  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.8  1994/11/01  21:23:55  bduggan
 **	Undid multiple image changes, since TagTableReplace now replaces
 **	entries without touching the NthOccur field.
 **
 **	Revision 1.7  1994/10/25  18:18:50  bduggan
 **	Fixed problem with freeing up too much memory.
 **	Also fixed multiple image bug.
 **
 **	Revision 1.6  1994/10/03  15:49:44  nadeau
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
 **	Revision 1.5  92/09/21  18:40:07  vle
 **	Cleaned up some comments.  Added -scale flag.
 **	
 **	Revision 1.4  92/09/01  20:15:12  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.3  92/09/01  12:23:26  nadeau
 **	Added more error checks.  Changed -replicate to -pixelrep and
 **	-interpolate to -bilinear.  Updated help information.
 **	
 **	Revision 1.2  92/08/25  16:59:04  groening
 **	Added -replicate option.
 **	
 **	Revision 1.1  91/10/03  13:20:03  nadeau
 **	Initial revision
 **	
 **
 **/

#include "imtools.h"


/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1991.
 **/

#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static ImVfb* toolPromoteRgb( ImVfb *srcVfb );
static ImVfb* toolDemoteRgb( ImVfb *srcVfb, int dstFields );
#else
static void   toolInit( );		/* Initialize things		*/
static ImVfb *toolPromoteRgb( );	/* Promote to RGB		*/
static ImVfb *toolDemoteRgb( );		/* Demote from RGB		*/
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
	/* command name */		"imscale",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command scales input images by a selected scale factor, or scales them\n\
up or down to a desired size.  Input and output files may have different\n\
image file formats.\n\
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
    Scale a 640x480 image up to 1280x1024 (non-uniform scaling):\n\
        %command small.pix -xscale 2.0 -yscale 2.133 large.pix\n\
        %command small.pix -xsize 1280 -ysize 1024 large.pix\n\
    Reduce an image to 1/3 its original size:\n\
        %command large.pix -scale 0.33 small.pix\n\
        %command large.pix -xscale 0.33 -yscale 0.33 small.pix\n\
    Double an image with pixel replication instead of bilinear interpolation:\n\
        %command begin.pix -scale 2 double.pix -pixelrep\n\
        %command begin.pix -xscale 2 -yscale 2 double.pix -pixelrep\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose images are to be scaled.  -outfile\n\
    selects the file into which to write the resulting scaled images.  The\n\
    input file is unaltered.\n\
\n\
Image Resizing:\n\
    -scale, -xscale and -yscale specify floating point scale factors.\n\
    To increase the size of an image, use a scale factor greater than\n\
    1.0.  To decrease an image's size, use a scale factor less than 1.0.\n\
    Default is 1.0.\n\
\n\
    -xsize and -ysize specify desired image size in pixels.  The scale factor\n\
    needed to enlarge or reduce the incoming image to the desired size is\n\
    automatically computed and applied.  Default is the input image size.\n\
\n\
    -xsize, -ysize, -xscale, and -yscale may be used together as long as at\n\
    most one of -xsize and -xscale are used, and at most one of -ysize and\n\
    -yscale are used.  -scale may not be used with -xsize, -ysize, -xscale\n\
    or -yscale.\n\
\n\
Scaling Algorithm:\n\
    -bilinear uses bilinear interpolation to increase or decrease the image\n\
    size.  This is the default.\n\
\n\
    -pixelrep uses pixel replication to increase the image size.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS 	9	
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -%option argument specifies the name of the input file.              \n\
                                                                             \n\
    The file's format may be specified with the -informat flag.             \n\
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

	{ "scale", "xy", "Specify XY scale factor%end\
    -scale, -xscale and -yscale specify floating point scale factors.\n\
    To increase the size of an image, use a scale factor greater than\n\
    1.0.  To decrease an image's size, use a scale factor less than 1.0.\n\
    Default is 1.0.\n\
\n\
    -xsize, -ysize, -xscale, and -yscale may be used together as long as at\n\
    most one of -xsize and -xscale are used, and at most one of -ysize and\n\
    -yscale are used.  -scale may not be used with -xsize, -ysize, -xscale\n\
    or -yscale.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "xscale", "x", "Specify X scale factor%end\
    -scale, -xscale and -yscale specify floating point scale factors.\n\
    To increase the size of an image, use a scale factor greater than\n\
    1.0.  To decrease an image's size, use a scale factor less than 1.0.\n\
    Default is 1.0.\n\
\n\
    -xsize, -ysize, -xscale, and -yscale may be used together as long as at\n\
    most one of -xsize and -xscale are used, and at most one of -ysize and\n\
    -yscale are used.  -scale may not be used with -xsize, -ysize, -xscale\n\
    or -yscale.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "yscale", "y", "Specify Y scale factor%end\
    -scale, -xscale and -yscale specify floating point scale factors.\n\
    To increase the size of an image, use a scale factor greater than\n\
    1.0.  To decrease an image's size, use a scale factor less than 1.0.\n\
    Default is 1.0.\n\
\n\
    -xsize, -ysize, -xscale, and -yscale may be used together as long as at\n\
    most one of -xsize and -xscale are used, and at most one of -ysize and\n\
    -yscale are used.  -scale may not be used with -xsize, -ysize, -xscale\n\
    or -yscale.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "xsize", "x", "Specify desired width in pixels%end\
    -xsize and -ysize specify desired image size in pixels.  The scale factor\n\
    needed to enlarge or reduce the incoming image to the desired size is\n\
    automatically computed and applied.  Default is the input image size.\n\
\n\
    -xsize, -ysize, -xscale, and -yscale may be used together as long as at\n\
    most one of -xsize and -xscale are used, and at most one of -ysize and\n\
    -yscale are used.  -scale may not be used with -xsize, -ysize, -xscale\n\
    or -yscale.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ysize", "y", "Specify desired height in pixels%end\
    -xsize and -ysize specify desired image size in pixels.  The scale factor\n\
    needed to enlarge or reduce the incoming image to the desired size is\n\
    automatically computed and applied.  Default is the input image size.\n\
\n\
    -xsize, -ysize, -xscale, and -yscale may be used together as long as at\n\
    most one of -xsize and -xscale are used, and at most one of -ysize and\n\
    -yscale are used.  -scale may not be used with -xsize, -ysize, -xscale\n\
    or -yscale.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "pixelrep", NULL, "Use pixel replication%end\
    -pixelrep uses pixel replication to increase the image size.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "bilinear", NULL, "Use bilinear interpolation%end\
    -bilinear uses bilinear interpolation to increase or decrease the image\n\
    size.  This is the default scaling algorithm.",
	  ARGFNONE, 0, 0, ARGTNONE },

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
 *			    and for the outgoing data 
 *	toolInFlagsTable -  a table for the storage of read flags
 *	toolOutFlagsTable-  a table for the storage of write flags
 *
 *	toolXScale	-  X scale factor
 *	toolYScale	-  Y scale factor
 *	toolXSize	-  X desired size
 *	toolYSize	-  Y desired size
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolInTable;	/* Data tag table		*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static float	  toolXScale;		/* X Position			*/
static float	  toolYScale;		/* Y Position			*/
static int	  toolXSize;		/* Width			*/
static int	  toolYSize;		/* Height			*/
static int	  toolScaleOpt;		/* wether to interpolate or replicate*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Copy part of each image.
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

	ImVfb      *srcVfb;		/* Source image			*/
	ImVfb	   *srcRgbVfb;		/* Temporary RGB image		*/
	int         srcFields;		/* Source image's fields	*/
	int         srcRgbFields;	/* RGB source image's fields	*/
	int	    srcW, srcH;		/* Source image dimensions	*/
	ImVfb      *dstVfb;		/* Desintation image		*/
	ImVfb	   *dstRgbVfb;		/* Temporary RGB image		*/
	int	    xsize, ysize;	/* New image resolution		*/

//	argc = __argc;
//	argv = __argv;

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
	 *  Scale!
	 *	-  Walk the data table looking for images.  For each one found,
	 *	   get the VFB, resize it, and replace the original with the
	 *	   resized image back in the same data table.
	 *
	 *  Watch for two special cases:
	 *	-  The source image is not an RGB image.  ImVfbResize()
	 *	   interpolates pixel values.  For RGB images this produces
	 *	   new intermediary colors.  For color index and monochrome
	 *	   images this creates new color indexes, which may correspond
	 *	   to CLT entries that don't have the right color.  To create
	 *	   a good image from a non-RGB source, we first promote the
	 *	   image to RGB.  In order to cause predictable output casting
	 *	   operations for file format output, we then demote the RGB
	 *	   image back to the same image type as the source.
	 *
	 *	-  The source image has additional fields besides just color
	 *	   (such as alpha or Z-buffer).  Intermediate images must
	 *	   have these fields as well, and the too must be resized.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &srcVfb );
		srcW         = ImVfbQWidth( srcVfb );
		srcH         = ImVfbQHeight( srcVfb );
		srcFields    = ImVfbQFields( srcVfb );
		srcRgbFields = (srcFields & (~IMVFBIMAGEMASK)) | IMVFBRGB;


		/*
		 *  Determine the X and Y scale factors to use.
		 */
		if ( toolXSize == -1 )
			xsize = (int) (toolXScale * srcW);
		else
			xsize = toolXSize;
		if ( toolYSize == -1 )
			ysize = (int) (toolYScale * srcH);
		else
			ysize = toolYSize;


		/*
		 *  If the source image is not RGB, then promote it to RGB
		 *  so that the resize will interpolate colors, rather than
		 *  color table indexes.  Maintain all non-image fields and
		 *  their data.
		 */
		srcRgbVfb = toolPromoteRgb( srcVfb );
		if ( srcRgbVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't create temporary RGB image for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Full size original image placed into output file.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Make a new destination image of the right size, and with
		 *  the same fields as the original (RGB version).
		 */
		dstRgbVfb = ImVfbAlloc( xsize, ysize, srcRgbFields );
		if ( dstRgbVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't create temporary RGB image for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Full size original image placed into output file.\n",
				ImToolsProgram );
			if ( srcVfb != srcRgbVfb )
				ImVfbFree( srcRgbVfb );
			continue;
		}


		/*
		 *  Resize the RGB image.
		 */
		if ( ImToolsVerbose )
			fprintf( stderr, "%s: Resizing image to %d X %d for image %d of %d\n",
				ImToolsProgram, xsize, ysize, i + 1, nInVfb );

		dstVfb = ImVfbResize( srcRgbVfb,	/* Use this VFB*/
			toolScaleOpt,			/* Interpolate	*/
			dstRgbVfb,			/* Put it here	*/
			xsize, ysize );			/* Make it this big*/
		if ( dstVfb == IMVFBNULL )
		{
			switch ( ImErrNo )
			{
			case IMEPIXELREP:
				fprintf( stderr, "%s: New size must be exact multiple of original size\n", ImToolsProgram);
				fprintf( stderr, "%s: when using pixel replication.\n", ImToolsProgram );
				break;

			case IMEWIDTH:
				fprintf( stderr, "%s: New width must be greater than original width\n", ImToolsProgram);
				fprintf( stderr, "%s: when using pixel replication.\n", ImToolsProgram );
				break;

			case IMEHEIGHT:
				fprintf( stderr, "%s: New height must be greater than original height\n", ImToolsProgram);
				fprintf( stderr, "%s: when using pixel replication.\n", ImToolsProgram );
				break;

			default:
				ImPError( ImToolsProgram );
			}
			fprintf( stderr, "%s: Couldn't resize for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Full size original image placed into output file.\n",
				ImToolsProgram );
			if ( srcVfb != srcRgbVfb )
				ImVfbFree( srcRgbVfb );
			ImVfbFree( dstRgbVfb );
			continue;
		}


		/*
		 *  If the source image was not RGB, demote the resized
		 *  image to the same image type.  Be careful to maintain
		 *  extra non-image fields, if any.
		 */
		dstVfb = toolDemoteRgb( dstRgbVfb, srcFields );
		if ( dstVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't create temporary RGB image for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Full size original image placed into output file.\n",
				ImToolsProgram );
			if ( srcVfb != srcRgbVfb )
				ImVfbFree( srcRgbVfb );
			ImVfbFree( dstRgbVfb );
			continue;
		}
		if ( (srcFields & IMVFBINDEX8) && ImVfbQClt( srcVfb)==IMCLTNULL)
		{
			/*
			 *  Source was grayscale (no CLT).  Convert the
			 *  new image to grayscale and remove its CLT.
			 */
			if ( ImVfbToGray( dstVfb, dstVfb ) == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				fprintf( stderr, "%s: Couldn't post-process image for image %d of %d.\n",
					ImToolsProgram, i + 1, nInVfb );
				fprintf( stderr, "%s: Full size original image placed into output file.\n",
					ImToolsProgram );
				if ( srcVfb != srcRgbVfb )
					ImVfbFree( srcRgbVfb );
				ImVfbFree( dstRgbVfb );
				continue;
			}
			ImCltFree( ImVfbQClt( dstVfb ) );
			ImVfbSClt( dstVfb, IMCLTNULL );
		}


		/*
		 *  Replace the source image with the destination image in the
		 *  same data table.
		 */
		TagTableReplace( toolInTable,
			TagEntryQNthEntry( dataEntry ),
			TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &dstVfb ));


		/*
		 *  Destroy the extra VFBs.
		 */
		if (srcRgbVfb!=srcVfb)
			ImVfbFree( srcRgbVfb );
		ImVfbFree( srcVfb );
		if ( dstVfb != dstRgbVfb )
			ImVfbFree( dstRgbVfb );
	}


	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolInTable );
	ImVfbFree( dstVfb );


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
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/

	char       *tmp;		/* Temporary string holder	*/

	int	   xscaleflag = FALSE;	/* TRUE if -xscale is used	*/
	int	   yscaleflag = FALSE;	/* TRUE if -yscale is used	*/

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
	 *  Get the image scale and size selections.
	 */
	toolXSize = toolYSize = -1;
	if ( ArgQNOccur( "xsize" ) != 0 )
	{
		toolXSize = (int) ArgQValue( "xsize", 0, 0 )->arg_i;
		if ( toolXSize <= 0 )
		{
			fprintf( stderr, "%s: -xsize must be positive\n",
				ImToolsProgram );
			exit( 1 );
		}
	}
	if ( ArgQNOccur( "ysize" ) != 0 )
	{
		toolYSize = (int) ArgQValue( "ysize", 0, 0 )->arg_i;
		if ( toolYSize <= 0 )
		{
			fprintf( stderr, "%s: -ysize must be positive\n",
				ImToolsProgram );
			exit( 1 );
		}
	}
	toolXScale = toolYScale = 1.0;
	if ( ArgQNOccur( "xscale" ) != 0 )
	{
		toolXScale = (float)(ArgQValue( "xscale", 0, 0 )->arg_f);
		if ( toolXScale <= 0.0 )
		{
			fprintf( stderr, "%s: -xscale must be greater than zero\n",
				ImToolsProgram );
			exit( 1 );
		}
		if ( toolXSize != -1 )
		{
			fprintf( stderr, "%s: only one of -xscale or -xsize may be given at a time\n",
				ImToolsProgram );
			exit( 1 );
		}
		xscaleflag = TRUE;
	}
	if ( ArgQNOccur( "yscale" ) != 0 )
	{
		toolYScale = (float)(ArgQValue( "yscale", 0, 0 )->arg_f);
		if ( toolYScale <= 0.0 )
		{
			fprintf( stderr, "%s: -yscale must be greater than zero\n",
				ImToolsProgram );
			exit( 1 );
		}
		if ( toolYSize != -1 )
		{
			fprintf( stderr, "%s: only one of -yscale or -ysize may be given at a time\n",
				ImToolsProgram );
			exit( 1 );
		}
		yscaleflag = TRUE;
	}
	if ( ArgQNOccur( "scale" ) != 0 )
	{
		if ( ( toolXSize != -1 ) || ( toolYSize != -1 ) ||
		     ( xscaleflag ) || (yscaleflag ) )
		{
			fprintf( stderr, "%s: -scale may not be used with -xsize, -ysize, -xscale, or -yscale\n",
				ImToolsProgram );
			exit( 1 );
		}
		toolXScale = toolYScale = (float)(ArgQValue( "scale", 0, 0 )->arg_f);
		if( toolXScale <= 0.0 )
		{
			fprintf( stderr, "%s: -scale must be greater than zero\n",
				ImToolsProgram );
			exit( 1 );
		}
	}

	if ( ArgQNOccur( "pixelrep" ) != 0 )
	{
		if ( ArgQNOccur( "bilinear" ) != 0 )
		{
			fprintf( stderr, "%s: only one of -bilinear or -pixelrep may be given at a time\n",
				ImToolsProgram );
			exit( 1 );
		}
		toolScaleOpt = IMVFBPIXELREP;
	}
	else
	{
		if ( ArgQNOccur( "pixelrep" ) != 0 )
		{
			fprintf( stderr, "%s: only one of -bilinear or -pixelrep may be given at a time\n",
				ImToolsProgram );
			exit( 1 );
		}
		toolScaleOpt = IMVFBBILINEAR;
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
 *	toolPromoteRgb	-  promote an image to RGB
 *
 *  DESCRIPTION
 *	An incomming image is promoted, if necessary, to an RGB image with
 *	the same non-image fields (and their data) as the incomming image.
 */

static ImVfb *				/* Returns new RGB image	*/
#ifdef __STDC__
toolPromoteRgb( ImVfb *srcVfb )
#else
toolPromoteRgb( srcVfb )
	ImVfb *srcVfb;			/* Image to turn into RGB	*/
#endif
{
	int srcFields;			/* Field mask of source image	*/
	int srcRgbFields;		/* New RGB image's fields	*/
	ImVfb *srcRgbVfb;		/* New RGB VFB			*/
	int srcW, srcH;			/* Source dimensions		*/


	/*
	 *  If the source image is already RGB, just return it.
	 */
	srcFields = ImVfbQFields( srcVfb );
	if ( srcFields & IMVFBRGB )
		return ( srcVfb );


	/*
	 *  If the source image doesn't have any non-image fields, such as
	 *  an alpha plane or Z-buffer, just convert it to a new VFB and
	 *  return the new VFB.
	 */
	if ( (srcFields & (~IMVFBIMAGEMASK)) == 0 )
		return ( ImVfbToRgb( srcVfb, IMVFBNEW ) );


	/*
	 *  The source image has "extra" fields not associated with image data.
	 *  We need to allocate a new VFB with an RGB image field, as well as
	 *  the other non-image fields from the source.
	 *
	 *  The source's non-image field data must then be copied into the new
	 *  VFB, and the source's image fields promoted to RGB data.
	 */
	srcW = ImVfbQWidth( srcVfb );
	srcH = ImVfbQHeight( srcVfb );
	srcRgbFields = (srcFields & (~IMVFBIMAGEMASK)) | IMVFBRGB;

	srcRgbVfb = ImVfbAlloc( srcW, srcH, srcRgbFields );
	if ( srcRgbVfb == IMVFBNULL )
		return ( IMVFBNULL );

	if ( ImVfbCopy( srcVfb,
		0, 0, srcW, srcH, srcFields & (~IMVFBIMAGEMASK),
		srcRgbVfb, 0, 0 ) == IMVFBNULL )
	{
		ImVfbFree( srcRgbVfb );
		return ( IMVFBNULL );
	}

	if ( ImVfbToRgb( srcVfb, srcRgbVfb ) == IMVFBNULL )
	{
		ImVfbFree( srcRgbVfb );
		return ( IMVFBNULL );
	}

	return ( srcRgbVfb );
}





/*
 *  FUNCTION
 *	toolDemoteRgb	-  demote an image from RGB
 *
 *  DESCRIPTION
 *	The incomming image is demoted to the given field type and returned.
 */

static ImVfb *				/* Returns demoted VFB		*/
#ifdef __STDC__
toolDemoteRgb( ImVfb *srcVfb, int dstFields )
#else
toolDemoteRgb( srcVfb, dstFields )
	ImVfb *srcVfb;			/* Image to demote		*/
	int    dstFields;		/* Desired fields		*/
#endif
{
	int srcW, srcH;			/* Source dimensions		*/
	ImVfb *dstVfb;			/* New destination VFB		*/
	ImVfb *tmpVfb;			/* Temporary VFB pointer holder	*/


	/*
	 *  If the source image already has the desired fields, just return
	 *  the source image.
	 */
	if ( ImVfbQFields( srcVfb ) == dstFields )
		return ( srcVfb );


	/*
	 *  If the destination fields include non-image fields, make a new
	 *  VFB and copy those non-image fields to it.
	 */
	if ( dstFields & (~IMVFBIMAGEMASK) )
	{
		srcW = ImVfbQWidth( srcVfb );
		srcH = ImVfbQHeight( srcVfb );

		dstVfb = ImVfbAlloc( srcW, srcH, dstFields );
		if ( dstVfb == IMVFBNULL )
			return ( IMVFBNULL );

		if ( ImVfbCopy( srcVfb,
			0, 0, srcW, srcH, dstFields & (~IMVFBIMAGEMASK),
			dstVfb, 0, 0 ) == IMVFBNULL )
		{
			ImVfbFree( dstVfb );
			return ( IMVFBNULL );
		}
	}
	else
		dstVfb = IMVFBNEW;


	/*
	 *  Convert the image to the desired image type.
	 */
	switch ( dstFields & IMVFBIMAGEMASK )
	{
	case IMVFBMONO:
		tmpVfb = ImVfbToMono( srcVfb, 127, dstVfb );
		break;

	case IMVFBINDEX8:
		tmpVfb = ImVfbToIndex8( srcVfb, dstVfb );
		break;

	case IMVFBINDEX16:
		tmpVfb = ImVfbToIndex16( srcVfb, dstVfb );
		break;
	}

	if ( tmpVfb == IMVFBNULL )
	{
		if ( dstVfb != IMVFBNULL )
			ImVfbFree( dstVfb );
		return ( IMVFBNULL );
	}

	return ( tmpVfb );
}
