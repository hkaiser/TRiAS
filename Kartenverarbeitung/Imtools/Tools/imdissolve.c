/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imdissolve.c,v 1.8 1995/06/30 22:18:09 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imdissolve.c,v 1.8 1995/06/30 22:18:09 bduggan Exp $"

/**
 **  FILE
 **	imdissolve.c	-  Dissolve between two images
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imdissolve dissolves between two images or a sequence of pairs of
 **	images, much like a video whipe or fade.
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
 **	toolIn1Filename	v  the name of the input file (could be 'stdin')
 **	toolOutFilename	v  the name of the output file (could be 'stdout')
 **	toolIn2Filenamev  the name of the background file (could be 'stdin')
 **
 **	toolIn1Format	v  the name of the input file's format (could be '\0')
 **	toolOutFormat	v  the name of the output file's format (could be '\0')
 **	toolIn2Format	v  the name of the background file's format (could be..)
 **
 **	toolIn1Table	v  a table for the storage of data read in
 **	toolIn2Table	v  a table for the storage of background data read in
 **	toolIn1FlagsTable v  a table for the storage of read flags
 **	toolIn2FlagsTable v  a table for the storage of read flags
 **	toolOutFlagsTable v  a table for the storage of write flags
 **
 **	toolPosX	v  X image position
 **	toolPosY	v  Y image position
 **	toolCenterX	v  Flag X direction centering
 **	toolCenterY	v  Flag Y direction centering
 **	toolTileX	v  X tile count
 **	toolTileY	v  Y tile count
 **	toolDirX	v  X tile direction
 **	toolDirY	v  Y tile direction
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imdissolve.c,v $
 **	Revision 1.8  1995/06/30  22:18:09  bduggan
 **	made main into type void
 **
 **	Revision 1.7  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.6  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.5  1995/06/29  00:33:06  bduggan
 **	added some casts
 **
 **	Revision 1.4  1995/05/17  23:59:34  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **	Added default filling of channels that are not dissolved upon.
 **
 **
 **/

#include <unistd.h>
#include <values.h>
#include "imtools.h"

/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1991.
 **/



#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static void toolMixMultiVfb( int frame, int nIn1Vfb, int nIn2Vfb );
static void toolMix( int frame );
#else
static void toolInit( );                /* Initialize things            */
static void toolMixMultiVfb( );
static void toolMix( );
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
	/* command name */		"imdissolve",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command dissolves or fades images or sets of images and saves the\n\
results into a new file.  Input and output files may have different\n\
image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] infile1name [infile2name] outfilename",
	"[options...] infile1name [infile2name] outfilename",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Fade-to-black Invocations:\n\
    Dim a single image to 50%:\n\
        %command -weight 0.5 image.pix result.hdf\n\
    Generate 20 frames fading a static image to black:\n\
        %command image.pix -frames 20 result.%02d.ras\n\
    Generate 20 frames fading from black to a static image:\n\
        %command -weight 0.0-1.0 -frames 20 image.rla result.%02d.xwd\n\
    Fade to black a sequence of 10 frames (10-19):\n\
        %command -frames 10-19 anim%05d.gif final.%05d.tiff\n\
\n\
Typical Dissolve Between Frames Invocations:\n\
    Mix together 50% each of two images:\n\
        %command -weight 0.5 first.pix second.rla output.pcx\n\
    Mix together 70% each of the first image with 30% of the second image:\n\
        %command -weight 0.7 first.pix second.rla output.pcx\n\
    Generate 10 sgi rgb files by dissolving between two static images:\n\
        %command static1.rgb static2.rgb -frames 30 anim.%03d -outformat rgb\n\
    Generate 30 frames dissolving between two static images:\n\
        %command static1.gif static2.gif -frames 30 anim.%03d.gif\n\
    Dissolve a sequence of 10 frames into a static image:\n\
        %command anim.%02d.tiff -frames 0-9 static.ras resultanim.%03d.x\n\
    Dissolve between two sequences of 100 frames:\n\
        %command first.%d.hdf second.%d.hdf -frames 100 final.%d.hdf\n\
    Dissolve between two sequences of 100 frames outputting every 10th frame:\n\
        %command first.%d.hdf second.%d.hdf -frames 100 -frameincrement 10 final.%d.hdf\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -in1file selects the first source image file for fades and dissolves.\n\
\n\
    -in2file selects the second source image for dissolves.  If not given,\n\
    operations fade to black instead of a second source image.\n\
\n\
    -outfile selects the file into which to write the results.\n\
\n\
    File names may embedd a C printf %d to indicate the location in the name\n\
    at which a frame number is to be inserted when reading, or writing\n\
    multiple image files.  For example:\n\
        %command first.%03d.hdf second.%03d.hdf -frames 100 results.%03d.hdf\n\
    reads source images from files named 'first.000.hdf', 'first.001.hdf',\n\
    and 'second.000.hdf', 'second.0001.hdf'. Resulting images are written to\n\
    files named 'results.000.hdf', 'results.001.hdf', etc.\n\
\n\
    Input images are converted to equal depth before fading and dissolving.\n\
    Operations occur independently of any alpha planes in any image.\n\
\n\
Weighting factors:\n\
    The weighting factor indicates the amount of the first source image to\n\
    include in the result.  A fade to black is computed using:\n\
        result = source1 * weight\n\
    A dissolve between two images is computed using:\n\
        result = source1 * weight + source2 * (1.0-weight)\n\
\n\
    Single-frame fades or dissolves use a default weight of 1.0 unless\n\
    overriden by the -weight option.\n\
\n\
Fade to black:\n\
    A fade merges a source image with an internally generated black image\n\
    based upon a weighting factor.\n\
\n\
    A single-frame fade uses a single source image file and generates a\n\
    single output image file.  The weighting factor is constant.\n\
\n\
    A multi-frame fade may use either a single static source image, or a\n\
    range of source image files, and generates multiple output image files.\n\
    The weighting factor is animated from its starting to ending values as\n\
    given by -weight (default is 1.0-0.0).\n\
\n\
Dissolve between images:\n\
    A dissolve merges two source images based upon a weighting factor.\n\
\n"
"    A single-frame dissolve uses two single-image source files and generates\n\
    a single output image file.  The weighting factor is constant.\n\
\n\
    A multi-frame dissolve may use either a single static source image file\n\
    and a range of secondary source image files, or two ranges of source\n\
    image files.  The weighting factor is animated from its starting to\n\
    ending values as given by -weight (default is 1.0-0.0).\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including a list of image file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";


#define IM_TOOLNOPTIONS	18
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "in1file", "image_filename_1", "Specify first input image file name%end\
    -in1file selects the first source image file for fades and dissolves.",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "in2file", "image_filename_2", "Specify second input image file name%end\
    -in2file selects the second source image for dissolves.  If not given,\n\
    operations fade to black instead of a second source image.",
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\n\
    -outfile selects the file into which to write the results.",
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "weight", "weight_range", "Specify dissolve image weighting%end\
Weighting factors:\n\
    The weighting factor indicates the amount of the first source image to\n\
    include in the result.  A fade to black is computed using:\n\
        result = source1 * weight\n\
    A dissolve between two images is computed using:\n\
        result = source1 * weight + source2 * (1.0-weight)\n\
\n\
    Single-frame fades or dissolves use a default weight of 1.0 unless\n\
    overriden by the -weight option.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "frames", "frame_range", "Specify range of frames to use",
	  ARGFNONE, 1, 1, ARGTINT | ARGTRANGE },

	{ "frameincrement", "frame_increment", "Specify frame incrementation value",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "rgbfield", NULL, "Specify to dissolve the rgb fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "redfield", NULL, "Specify to dissolve the red fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "bluefield", NULL, "Specify to dissolve the blue fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "greenfield", NULL, "Specify to dissolve the green fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "index8field", NULL, "Specify to dissolve the index8 fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "index16field", NULL, "Specify to dissolve the index16 fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "monofield", NULL, "Specify to dissolve the mono fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "alphafield", NULL, "Specify to dissolve the alpha fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "zbufferfield", NULL, "Specify to dissolve the zbuffer fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "idatafield", NULL, "Specify to dissolve integer data fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "fdatafield", NULL, "Specify to dissolve floating pt. fields",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "wprotfield", NULL, "Specify to dissolve write prot. fields",
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
 *	toolIn1Filename	-  the name of the input 1 file (could be 'stdin')
 *	toolIn2Filename	-  the name of the input 2 file (could be 'stdin')
 *	toolOutFilename	-  the name of the output file (could be 'stdout')
 *
 *	toolIn1Format	-  the name of the input 1 file's format (could be NULL)
 *	toolIn2Format	-  the name of the input 2 file's format (could be NULL)
 *	toolOutFormat	-  the name of the output file's format (could be NULL)
 *
 *	toolIn1Table	-  a table for the storage of input 1 data read in
 *	toolIn2Table	-  a table for the storage of input 2 data read in
 *	toolIn1FlagsTable -a table for the storage of read flags
 *	toolIn2FlagsTable -a table for the storage of read flags
 *	toolOutFlagsTable -a table for the storage of write flags
 *
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolIn1Filename[1024];/* Input 1 file name		*/
static char      toolIn1Format[1024];	/* Input 1 file's format name	*/

static char      toolIn2Filename[1024];/* Input 2 file name		*/
static char      toolIn2Format[1024];	/* Input 2 file's format name*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolIn1Table;		/* Input 1 data tag table	*/
static TagTable *toolIn2Table;		/* Input 2 data tag table	*/
static TagTable *toolOutTable;		/* Input 2 data tag table	*/
static TagTable *toolIn1FlagsTable;	/* Flags tag table		*/
static TagTable *toolIn2FlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static ImVfb    *toolIn1Vfb;		/* Input 1 image		*/
static ImVfb    *toolIn2Vfb;		/* Input 2 image		*/

static float     toolWeightStart;	/* Starting weight		*/
static float     toolWeightEnd;		/* Ending weight		*/

static int       toolFrameStart;	/* Starting frame #		*/
static int       toolFrameEnd;		/* Ending frame #		*/

static int	  toolIn1Animate;
static int	  toolIn2Animate;

static int       toolField;            /* What fields to change        */
static int       toolFrameInc;         /* What to increment frames by  */




/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Dissolve the image.
 *		-  Replace the data table images with their smaller copy pieces.
 *		-  Write out the output file (get data from data table).
 *		-  Repeat for all frames.
 *	That's about it.
 *
 *  NOTES
 *	This 'main' is pretty much the same for each of the image tools.
 *	Differences between tools include:
 *		-  the number of input files read in
 *		-  the number of output files written out
 *		-  the actions taken on the data between read and write
 */

#define imImageType(f)		((f)&IMVFBIMAGEMASK)
#define imIsImage(f)		(((f)&IMVFBIMAGEMASK) != 0)
#define imSameImageType(f1,f2)	(imImageType(f1) == imImageType(f2))

void
#ifdef __STDC__
main( int argc, char *argv[] )
#else
main( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[];			/* Argument vector		*/
#endif
{
	int	    frame;		/* Current frame number		*/
	float	    divisor;		/* What to increment weight by  */
	TagEntry   *dataEntry;		/* Entry from data table	*/
	int	    i;			/* counter			*/
	char        in1Filename[1024];	/* Input file's name		*/
	char        in2Filename[1024];	/* Input file's name		*/
	int	    nIn1Vfb, nIn2Vfb;	/* number of vfb's in a file    */

	argc = __argc;
	argv = __argv;

	/*
	 *  Initialize things:
	 *	-  Prepare the arg parsing data, then parse the command-line.
	 *	-  Prepare the flags table based upon command-line args.
	 *	-  Determine the file formats for input and output files.
	 */
	toolInit( argc, argv );

	nIn1Vfb=0;
	nIn2Vfb=0;


	/*
	 *  Determine which file names are being animated.  Read in image
	 *  data for those that are not.
	 *	-  Open the file (or stdin) and read data into the data table.
	 *	-  Check for 0 or >1 images.
	 */
	if ( strchr( toolIn1Filename, '%' ) != NULL )
	{
		toolIn1Animate = TRUE;
		/* error check to make sure that files inputted are accessable */
		for (i=toolFrameStart; i<=toolFrameEnd; i++)
	        {
                   sprintf( in1Filename, toolIn1Filename, i );
		   if ( _access (in1Filename, R_OK)== -1)
		   {
		      fprintf (stderr, "Can't _access file '%s'\n",in1Filename);
		      exit(1);
		   }
		}
	}
	else
	{
		/* Static image.  Read it in.				*/
		toolIn1Animate = FALSE;
                ImToolsFileRead( toolIn1Filename, toolIn1Format, toolIn1FlagsTable,
                	toolIn1Table );
		dataEntry      = TagTableQDirect( toolIn1Table, "image vfb", 0);
		TagEntryQValue( dataEntry, &toolIn1Vfb );
                nIn1Vfb = TagTableQNEntry( toolIn1Table, "image vfb" );
		if ( nIn1Vfb>1) 
			toolIn1Animate = TRUE;
                if ( nIn1Vfb == 0 )
                {
                        fprintf( stderr, "%s: Input file contains no images!\n",
			ImToolsProgram );
                        exit( 1 );
                }
	}

	if ( *toolIn2Filename != '\0' )
	{
		/* A 2nd source file was given.				*/
		if ( strchr( toolIn2Filename, '%' ) != NULL )
		{
			toolIn2Animate = TRUE;
			/* error check to make sure that files inputted are accessable */
			for (i=toolFrameStart; i<=toolFrameEnd; i++)
			{
			   sprintf( in2Filename, toolIn2Filename, i );
			   if ( _access (in2Filename,R_OK)== -1)
			   {
			      fprintf (stderr, "Can't _access file '%s'\n",in2Filename);
			      exit(1);
			   }
			}
		}

		else
		{
			/* Static image.  Read it in.			*/
			toolIn2Animate = FALSE;
                	ImToolsFileRead( toolIn2Filename, toolIn2Format,
					 toolIn2FlagsTable, toolIn2Table );
			dataEntry      = TagTableQDirect( toolIn2Table,
				"image vfb", 0 );
			TagEntryQValue( dataEntry, &toolIn2Vfb );
			nIn2Vfb = TagTableQNEntry( toolIn2Table, "image vfb" );
			if ( nIn2Vfb == 0 )
			{
				fprintf( stderr, "%s: Input file contains no images!\n",
				ImToolsProgram );
				exit( 1 );
			}
			if ( nIn2Vfb>1) toolIn2Animate = TRUE;
		}
	}
	else
		toolIn2Vfb = IMVFBNULL;


	/* more error checking */

	if ( ((toolFrameEnd-toolFrameStart)>1) &&
		(strchr (toolOutFilename, '%') ==NULL) )
	{
	   fprintf (stderr, "%s: insufficient output filename given.\n", ImToolsProgram);
	   exit(1);
	}

	if (( nIn1Vfb!=nIn2Vfb) && (nIn1Vfb>1) && (nIn2Vfb>1))
	{
	  fprintf (stderr,"%s: unequal amount of images in the two files given.\n", ImToolsProgram);
	  exit(1);
	}

	if ( (toolWeightStart<0.0) || (toolWeightStart>1.0) ||
	     (toolWeightStart<0.0) || (toolWeightStart>1.0))
	{
	  fprintf (stderr, "%s: Invalid weight range.\n", ImToolsProgram);
	  exit(1);
	}

	if ( (toolWeightEnd!=0.0) && ( (toolFrameEnd-toolFrameStart)==0) )
	{
	  fprintf (stderr, "%s: Received a weight range but no frame range.\n",
			ImToolsProgram);
	  exit(1);
	}

	if ( (toolFrameEnd-toolFrameStart) == 0) 
		divisor = 0;
	else
		divisor = ( ( (toolWeightEnd-toolWeightStart)/
			(toolFrameEnd- toolFrameStart) ) * toolFrameInc );

	if (  (toolIn1Animate==TRUE) &&
	     ( (toolFrameStart==0) && (toolFrameEnd==0)))
	{ 
             sprintf( in1Filename, toolIn1Filename, toolFrameEnd );
	     while ( _access (in1Filename,R_OK)!=-1)
	     {
		toolFrameEnd++;
                sprintf( in1Filename, toolIn1Filename, toolFrameEnd );
	     }
		toolFrameEnd--;
       	}     

	if ( ( toolIn2Animate==TRUE) &&
	     ( (toolFrameStart==0) && (toolFrameEnd==0)))
	{ 
		sprintf( in2Filename, toolIn2Filename, toolFrameEnd );
		while ( _access (in2Filename,R_OK)!=-1)
		{
			toolFrameEnd++;
			sprintf( in2Filename, toolIn2Filename, toolFrameEnd );
		}
		toolFrameEnd--;
       	}     

	/*
	 *  Cycle through the frames.
	 */

	if ( (nIn1Vfb>1) || (nIn2Vfb>1) )
	{
	for ( frame = toolFrameStart; frame <=toolFrameEnd;frame+=toolFrameInc )
	{
		toolMixMultiVfb( frame, nIn1Vfb, nIn2Vfb );
		toolWeightStart+=divisor;
	}
	}
	else 
	{
	for ( frame = toolFrameStart; frame <=toolFrameEnd;frame+=toolFrameInc )
	{
		toolMix( frame );
		toolWeightStart+=divisor;
	}
        }

	exit(0);
}


/*
 * FUNCTION: toolMixMultiVfb
 *
 * DESCRIPTION: takes files with multiple vfb's, and then dissolves
 *   them together by circling through the images.
 */
static void
#ifdef __STDC__
toolMixMultiVfb( int frame, int nIn1Vfb, int nIn2Vfb )
#else
toolMixMultiVfb( frame, nIn1Vfb, nIn2Vfb )
	int frame;			/* Current frame number		*/
	int nIn1Vfb, nIn2Vfb;		/* number of vfb's to play with */
#endif
{
	TagEntry   *dataEntry;		/* Entry from data table	*/

	ImVfb	   *newVfb;		/* New paste image		*/
	ImVfb	   *tempVfb;		/* New paste image		*/

	char	    outFilename[1024];  /* output file's name		*/
	int	    rotations;		/* max number of vfb's		*/
	int	    i;			/* number of rotations		*/
	ImVfb        *retval;		/* return value from imvfbmix   */
	int	   dw,dh;		/* width and height		*/

	rotations = nIn1Vfb < nIn2Vfb ? nIn2Vfb : nIn1Vfb;

        if ( *toolIn2Filename == '\0' )
        {
                /* Black image.                                         */

                /*
                 *  Make sure we have a black image to fade against:
                 *      -- if we've got one already, check its size.
                 *         if not right size, free old black frame.
                 *      -- if don't have black frame, allocate at same
                 *         size and depth as input 1's image.
                 */
                if ( toolIn2Vfb != IMVFBNULL &&
                        (ImVfbQWidth(toolIn2Vfb) != ImVfbQWidth(toolIn1Vfb) ||
                        ImVfbQHeight(toolIn2Vfb) != ImVfbQHeight(toolIn1Vfb)))
                {
                        /* Wrong size this time.  Free it.              */
                        ImVfbFree( toolIn2Vfb );
                        toolIn2Vfb = IMVFBNULL;
                }

                if ( toolIn2Vfb == IMVFBNULL )
                {
                        /* Allocate a black frame same size as input.   */
                        toolIn2Vfb = ImVfbAlloc( ImVfbQWidth( toolIn1Vfb ),
                                ImVfbQHeight( toolIn1Vfb ),
                                ImVfbQFields( toolIn1Vfb ) );
                        if ( toolIn2Vfb == IMVFBNULL )
                        {
                                ImPError( ImToolsProgram );
                                exit( 1 );
                        }

                        /* Clear it.                                    */
                        ImVfbClear( IMVFBALL, 0, toolIn2Vfb );
                }
        }


	/* go through all of the images in tag table */
	for (i=0; i<rotations; i++)
	{
		if (toolIn1Animate == TRUE) /* get next vfb */
		{
                dataEntry = TagTableQDirect( toolIn1Table, "image vfb", 0 );
                TagEntryQValue( dataEntry, &toolIn1Vfb );
		}
 
		if (toolIn2Animate == TRUE) /* get next vfb */
		{
                dataEntry = TagTableQDirect( toolIn2Table, "image vfb", 0 );
                TagEntryQValue( dataEntry, &toolIn2Vfb );
		}

		/* make sure that images have rgb vfb type */
		if ( !(ImVfbQFields(toolIn1Vfb)&IMVFBRGB) )
			{
			tempVfb=ImVfbToRgb (toolIn1Vfb,IMVFBNEW);
			TagTableReplace (toolIn1Table, 0,
				TagEntryAlloc ( "image vfb", IM_POINTER_TYPE, &tempVfb) );
			ImVfbFree (toolIn1Vfb);
			toolIn1Vfb = tempVfb;
		}
		if ( !(ImVfbQFields(toolIn2Vfb)&IMVFBRGB) )
		{
			tempVfb=ImVfbToRgb (toolIn2Vfb,IMVFBNEW);
			TagTableReplace (toolIn2Table,0,
				TagEntryAlloc ( "image vfb", IM_POINTER_TYPE, &tempVfb) );
			ImVfbFree (toolIn2Vfb);
			toolIn2Vfb = tempVfb;
		}

		dw = ImVfbQWidth( toolIn1Vfb ) < ImVfbQWidth( toolIn2Vfb ) ?
			ImVfbQWidth( toolIn1Vfb ) : ImVfbQWidth( toolIn2Vfb );
		dh = ImVfbQHeight( toolIn1Vfb ) < ImVfbQHeight( toolIn2Vfb ) ?
			ImVfbQHeight( toolIn1Vfb ) : ImVfbQHeight( toolIn2Vfb );

		newVfb= ImVfbAlloc( dw,dh, ImVfbQFields( toolIn1Vfb ) );

		/* mix the two vfb's together */
		retval=ImVfbMix (toolIn1Vfb,toolWeightStart,toolIn2Vfb,
			(1-toolWeightStart), toolField, newVfb);

		if (toolField!=IMVFBALL)
		/*
		 * Copy each channel that was not mixed.
		 */
		{
			if (ImVfbQFields(toolIn1Vfb) & IMVFBRGB )
			{
				if (!(toolField & IMVFBRED))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBRED, newVfb, IMVFBRED);
				if (!(toolField & IMVFBGREEN))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBGREEN, newVfb, IMVFBGREEN);
				if (!(toolField & IMVFBBLUE))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBBLUE, newVfb, IMVFBBLUE);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBINDEX8 )
			{
				if (!(toolField & IMVFBINDEX8))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBINDEX8, newVfb, IMVFBINDEX8);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBINDEX16 )
			{
				if (!(toolField & IMVFBINDEX16))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBINDEX16, newVfb, IMVFBINDEX16);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBALPHA )
			{
				if (!(toolField & IMVFBALPHA))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBALPHA, newVfb, IMVFBALPHA);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBZ )
			{
				if (!(toolField & IMVFBZ))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBZ, newVfb, IMVFBZ);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBWPROT )
			{
				if (!(toolField & IMVFBWPROT))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBWPROT, newVfb, IMVFBWPROT);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBFDATA )
			{
				if (!(toolField & IMVFBFDATA))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBFDATA, newVfb, IMVFBFDATA);
			}
			if (ImVfbQFields(toolIn1Vfb) & IMVFBIDATA )
			{
				if (!(toolField & IMVFBIDATA))
					ImVfbCopyChannel( toolIn1Vfb, IMVFBIDATA, newVfb, IMVFBIDATA);
			}
		}



		if (retval==IMVFBNULL)
		{
			fprintf (stderr, "%s: no fields to mix in images",
			ImToolsProgram);
			exit(1);
		}
		/* Attach vfb to tag table */
		TagTableAppend (toolOutTable,TagEntryAlloc("image vfb", IM_POINTER_TYPE, &newVfb));

	}
	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */

	if ( (nIn1Vfb>1) || (nIn2Vfb>1) ||
		(strchr (toolOutFilename, '%') !=NULL) )
	{
		sprintf( outFilename, toolOutFilename, frame );
		ImToolsFileWrite( outFilename, toolOutFormat, toolOutFlagsTable,
			toolOutTable );
	}
	else ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolOutTable );


}

/*
 * FUNCTION toolMix
 *
 * DESCRIPTION: gets new images if there is animation to be done, then
 *	dissolves the two images together.
 *
 */
static void
#ifdef __STDC__
toolMix( int frame )
#else
toolMix( frame )
	int frame;			/* Current frame number		*/
#endif
{
	TagEntry   *dataEntry;		/* Entry from data table	*/

	ImVfb	   *newVfb;		/* New paste image		*/
	ImVfb	   *tempVfb;		/* New paste image		*/

	char        in1Filename[1024];	/* Input file's name		*/
	char        in2Filename[1024];	/* Input file's name		*/
	char	    outFilename[1024];  /* output file's name		*/
	int	    nInVfb;		/* number of inpput vfb's	*/
	ImVfb	    *retval;		/* return value of imvfbmix	*/
	int	    dw, dh;		/* width and height		*/


	/*
	 *  Read in the animated input files.
	 *	-  Open the file (or stdin) and read data into the data table.
	 *	-  Check for 0 or >1 images.
	 */
	if ( toolIn1Animate == TRUE )
	{
		/* New file.  Read it in and get its image.		*/
		sprintf( in1Filename, toolIn1Filename, frame );
		TagTableFree (toolIn1Table);
        	if ( (toolIn1Table = TagTableAlloc( )) == TAGTABLENULL )
        	{
                	TagPError( ImToolsProgram );
                	exit( 1 );
        	}
                ImToolsFileRead( in1Filename, toolIn1Format, toolIn1FlagsTable,
			toolIn1Table );
		dataEntry = TagTableQDirect( toolIn1Table, "image vfb", 0 );
		TagEntryQValue( dataEntry, &toolIn1Vfb );
                nInVfb = TagTableQNEntry( toolIn1Table, "image vfb" );
                if ( nInVfb == 0 )
                {
                       fprintf( stderr, "%s: Input file1 contains no images!\n",
		       ImToolsProgram );
                        exit( 1 );
                }
                if ( nInVfb != 1 )
                {
               fprintf( stderr, "%s: I don't do many files with many images!\n",
	       ImToolsProgram );
                        exit( 1 );
                }
	}

	if ( toolIn2Animate == TRUE )
	{
		/* New file.  Read it in and get its image.		*/
		sprintf( in2Filename, toolIn2Filename, frame );
		TagTableFree (toolIn2Table);
        	if ( (toolIn2Table = TagTableAlloc( )) == TAGTABLENULL )
        	{
                	TagPError( ImToolsProgram );
                	exit( 1 );
        	}
                ImToolsFileRead( in2Filename, toolIn2Format,
			 toolIn2FlagsTable, toolIn2Table );
		dataEntry = TagTableQDirect( toolIn2Table, "image vfb", 0 );
		TagEntryQValue( dataEntry, &toolIn2Vfb );
                nInVfb = TagTableQNEntry( toolIn2Table, "image vfb" );
                if ( nInVfb == 0 )
                {
                      fprintf( stderr, "%s: Input file2 contains no images!\n",
		      ImToolsProgram );
                        exit( 1 );
                }
                if ( nInVfb != 1 )
                {
               		fprintf( stderr, "%s: I don't do many files with many images!\n",
			ImToolsProgram );
                        exit( 1 );
                }

	}
	else if ( *toolIn2Filename == '\0' )
	{
		/* Black image.						*/
		strcpy( in2Filename, "black" );

		/*
		 *  Make sure we have a black image to fade against:
		 *	-- if we've got one already, check its size.
		 *	   if not right size, free old black frame.
		 *	-- if don't have black frame, allocate at same
		 *	   size and depth as input 1's image.
		 */
		if ( toolIn2Vfb != IMVFBNULL &&
			(ImVfbQWidth(toolIn2Vfb) != ImVfbQWidth(toolIn1Vfb) ||
			ImVfbQHeight(toolIn2Vfb) != ImVfbQHeight(toolIn1Vfb)))
		{
			/* Wrong size this time.  Free it.		*/
			ImVfbFree( toolIn2Vfb );
			toolIn2Vfb = IMVFBNULL;
		}

		if ( toolIn2Vfb == IMVFBNULL )
		{
			/* Allocate a black frame same size as input.	*/
			toolIn2Vfb = ImVfbAlloc( ImVfbQWidth( toolIn1Vfb ),
				ImVfbQHeight( toolIn1Vfb ),
				ImVfbQFields( toolIn1Vfb ) );
			if ( toolIn2Vfb == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Clear it.					*/
			ImVfbClear( IMVFBALL, 0, toolIn2Vfb );
		}
	}

	/* make sure that images have rgb vfb type */
	if ( !(ImVfbQFields(toolIn1Vfb)&IMVFBRGB) )
	{
		tempVfb=ImVfbToRgb (toolIn1Vfb,IMVFBNEW);
		TagTableReplace (toolIn1Table, 0, TagEntryAlloc( "image vfb",
			IM_POINTER_TYPE, &tempVfb) );
		ImVfbFree (toolIn1Vfb);
		toolIn1Vfb = tempVfb;
	}
	if ( !(ImVfbQFields(toolIn2Vfb)&IMVFBRGB) )
	{
		tempVfb=ImVfbToRgb (toolIn2Vfb,IMVFBNEW);
		TagTableReplace (toolIn2Table, 0, TagEntryAlloc("image vfb",
			IM_POINTER_TYPE, &tempVfb) );
		ImVfbFree (toolIn2Vfb);
		toolIn2Vfb = tempVfb;
	}


        dw = ImVfbQWidth( toolIn1Vfb ) < ImVfbQWidth( toolIn2Vfb ) ?
                ImVfbQWidth( toolIn1Vfb ) : ImVfbQWidth( toolIn2Vfb );
        dh = ImVfbQHeight( toolIn1Vfb ) < ImVfbQHeight( toolIn2Vfb ) ?
                ImVfbQHeight( toolIn1Vfb ) : ImVfbQHeight( toolIn2Vfb );

	newVfb = ImVfbAlloc(  dw, dh, ImVfbQFields( toolIn1Vfb ) );

        retval=ImVfbMix (toolIn1Vfb,toolWeightStart,toolIn2Vfb,
                (1-toolWeightStart), toolField, newVfb);
	if (retval==IMVFBNULL)
	{
		fprintf (stderr, "%s: nofields to mix in images",
		ImToolsProgram);
		exit(1);
	}

	if (toolField!=IMVFBALL)
	/*
	 * Copy each channel that was not mixed.
	 */
	{
		if (ImVfbQFields(toolIn1Vfb) & IMVFBRGB )
		{
			if (!(toolField & IMVFBRED))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBRED, newVfb, IMVFBRED);
			if (!(toolField & IMVFBGREEN))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBGREEN, newVfb, IMVFBGREEN);
			if (!(toolField & IMVFBBLUE))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBBLUE, newVfb, IMVFBBLUE);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBINDEX8 )
		{
			if (!(toolField & IMVFBINDEX8))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBINDEX8, newVfb, IMVFBINDEX8);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBINDEX16 )
		{
			if (!(toolField & IMVFBINDEX16))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBINDEX16, newVfb, IMVFBINDEX16);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBALPHA )
		{
			if (!(toolField & IMVFBALPHA))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBALPHA, newVfb, IMVFBALPHA);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBZ )
		{
			if (!(toolField & IMVFBZ))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBZ, newVfb, IMVFBZ);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBWPROT )
		{
			if (!(toolField & IMVFBWPROT))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBWPROT, newVfb, IMVFBWPROT);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBFDATA )
		{
			if (!(toolField & IMVFBFDATA))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBFDATA, newVfb, IMVFBFDATA);
		}
		if (ImVfbQFields(toolIn1Vfb) & IMVFBIDATA )
		{
			if (!(toolField & IMVFBIDATA))
				ImVfbCopyChannel( toolIn1Vfb, IMVFBIDATA, newVfb, IMVFBIDATA);
		}
	}

        /* Attach vfb to tag table */
        TagTableAppend (toolOutTable,TagEntryAlloc("image vfb", IM_POINTER_TYPE, &newVfb));

        /* Attach vfb to tag table */
	TagTableFree (toolOutTable);
       	if ( (toolOutTable = TagTableAlloc( )) == TAGTABLENULL )
       	{
               	TagPError( ImToolsProgram );
               	exit( 1 );
       	}
        TagTableAppend (toolOutTable,TagEntryAlloc("image vfb", IM_POINTER_TYPE, &newVfb));

	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */

	if ( (toolIn2Animate==TRUE) || (toolIn1Animate==TRUE) ||
		(strchr (toolOutFilename, '%') !=NULL) )
	{
		sprintf( outFilename, toolOutFilename, frame );
		ImToolsFileWrite( outFilename, toolOutFormat, toolOutFlagsTable,
			toolOutTable );
	}
	else ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolOutTable );

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
 *	Input, output and background file's names and formats are determined
 *	from the command-line arguments.
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
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/
	ArgValue   *value;		/* Argument value		*/

	char       *tmp;		/* Temporary string holder	*/


	/*
	 *  Save the name of the program, as invoked.
	 */
	ImToolsProgram = argv[0];

	if ( (toolIn1Table = TagTableAlloc( )) == TAGTABLENULL )
        {
                TagPError( ImToolsProgram );
                exit( 1 );
        }
        if ( (toolIn2Table = TagTableAlloc( )) == TAGTABLENULL )
        {
                TagPError( ImToolsProgram );
                exit( 1 );
        }
        if ( (toolOutTable = TagTableAlloc( )) == TAGTABLENULL )
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
	nOpt = ImToolsMergeOptions( "in1", IM_TOOLNOPTIONS, toolOptions,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options1 );
	nOpt = ImToolsMergeOptions( "in2", nOpt, options1,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "out", nOpt, options,
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "in1", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs1 );
	nEquiv = ImToolsMergeEquivs( "in2", nEquiv, equivs1,
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
	if ( ArgQNOccur( "verbose" ) != 0 )
		ImToolsVerbose = TRUE;

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
	 *  Get the fields to dissolve.
	 */
	 toolField = 0;

	if ( ArgQNOccur( "redfield" ) != 0 )     toolField |= IMVFBRED;
	if ( ArgQNOccur( "bluefield" ) != 0 )    toolField |= IMVFBBLUE;
	if ( ArgQNOccur( "greenfield" ) != 0 )   toolField |= IMVFBGREEN;
	if ( ArgQNOccur( "rgbfield" ) != 0 )     toolField |= (IMVFBRED|IMVFBGREEN|IMVFBBLUE);
	if ( ArgQNOccur( "monofield" ) != 0 )    toolField |= IMVFBMONO;
	if ( ArgQNOccur( "index16field" ) != 0 ) toolField |= IMVFBINDEX16;
	if ( ArgQNOccur( "index8field" ) != 0 )  toolField |= IMVFBINDEX8;
	if ( ArgQNOccur( "zbufferfield" ) != 0 ) toolField |= IMVFBZ;
	if ( ArgQNOccur( "wprotfield" ) != 0 ) toolField |= IMVFBWPROT;
	if ( ArgQNOccur( "alphafield" ) != 0 ) toolField |= IMVFBALPHA;
	if ( ArgQNOccur( "fdatafield" ) != 0 ) toolField |= IMVFBFDATA;
	if ( ArgQNOccur( "idatafield" ) != 0 ) toolField |= IMVFBIDATA;

	if (!toolField) toolField = IMVFBALL;


	/*
	 *  Get the weighting factor range.
	 */
	toolWeightStart = 1.0;
	toolWeightEnd   = 0.0;
	if ( ArgQNOccur( "weight" ) != 0 )
	{
		value = ArgQValue( "weight", 0, 0 );
		switch ( value->arg_rform )
		{
		case ARGRCLOSED:	/* n-m  start and end values	*/
			toolWeightStart = (float)(value->arg_fr1);
			toolWeightEnd   = (float)(value->arg_fr2);
			break;

		case ARGROPEN:		/* n-   start only		*/
		case ARGRSINGLE:	/* n    start only		*/
			toolWeightStart = (float)(value->arg_f);
			break;
		}
	}


	/*
	 *  Get frame incrementation.
	 */
	toolFrameInc = 1;
	if ( ArgQNOccur( "frameincrement" ) != 0 )
	{
		toolFrameInc = (int) ArgQValue ("frameincrement",0,0)->arg_i; 
	}

	/*
	 *  Get the number of frames.
	 */
	toolFrameStart = toolFrameEnd = 0;
	if ( ArgQNOccur( "frames" ) != 0 )
	{
		value = ArgQValue( "frames", 0, 0 );
		switch ( value->arg_rform )
		{
		case ARGRCLOSED:	/* n-m  start and end values	*/
			toolFrameStart = (int) value->arg_ir1;
			toolFrameEnd   = (int) value->arg_ir2;
			break;

		case ARGROPEN:		/* n-   length only		*/
		case ARGRSINGLE:	/* n    length only		*/
			toolFrameEnd = (int) value->arg_i - 1;
			break;
		}
	}



	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolIn1FlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolIn1FlagsTable, "in");
	ImToolsGetNameAndFormat ( "in1", 0, toolIn1Filename, toolIn1Format);

	toolIn2FlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolIn2FlagsTable, "in");
	ImToolsGetNameAndFormat ( "in2", 0, toolIn2Filename, toolIn2Format);

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);


	/*
	 *  Check that the input files are not both stdin.
	 */
	if ( strcmp( toolIn1Filename, "-" ) == 0 &&
		strcmp( toolIn2Filename, "-" ) == 0)
	{
		fprintf( stderr, "%s: -in1file and -in2file cannot both be stdin.\n",
			ImToolsProgram );
		exit( 1 );
	}

	/* 
         *  See if the second input image was omitted
	 *  If so then swap input2 with output
         */
	if ( (*toolOutFilename == '\0') && (*toolIn2Filename == '\0'))
	{
		fprintf (stderr, "%s: no output file given.\n", ImToolsProgram);
		exit(1);
	}
	if ( *toolOutFilename == '\0')
	{
	   strcpy (toolOutFilename, toolIn2Filename);
	   *toolIn2Format = '\0';
	   *toolIn2Filename ='\0';
	}
	
}
