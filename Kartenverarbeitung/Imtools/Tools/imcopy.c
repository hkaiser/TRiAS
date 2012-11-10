/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imcopy.c,v 1.10 1995/06/30 22:17:55 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imcopy.c,v 1.10 1995/06/30 22:17:55 bduggan Exp $"

/**
 **  FILE
 **	imcopy.c	-  Copy a part of an image
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imcopy copies a piece of an image into a new file.
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
 **	toolPosX	v  X image position
 **	toolPosY	v  Y image position
 **	toolCenterX	v  Flag X direction centering
 **	toolCenterY	v  Flag Y direction centering
 **	toolSizeW	v  Image width
 **	toolSizeH	v  Image height
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imcopy.c,v $
 **	Revision 1.10  1995/06/30  22:17:55  bduggan
 **	added some casts
 **
 **	Revision 1.9  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.8  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.7  1995/06/15  19:06:12  bduggan
 **	took out some useless vars
 **
 **	Revision 1.6  1995/05/17  23:59:20  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.5  1994/11/01  21:18:21  bduggan
 **	Undid changes for multiple images, since TagTableReplace has now been
 **	changed to not replace the NthOccur field when an entry is replaced.
 **
 **	Revision 1.4  1994/10/25  17:22:40  bduggan
 **	Fixed multiple image bug
 **
 **	Revision 1.3  1994/10/03  15:49:13  nadeau
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
 **	Revision 1.2  92/08/31  17:03:19  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.1  91/10/03  13:19:44  nadeau
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
#else
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
	/* command name */		"imcopy",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command copies a portion of an input image into a new file.  Input and\n\
output files may have different image file formats.\n\
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
    Clip out a 100x100 pixel image whose upper-left corner is at (10,20),\n\
    and save the clipped piece into an HDF file:\n\
        %command infile.pix -xpos 10 -ypos 20 -xsize 100 -ysize 100 outfile.hdf\n\
    Clip out the top 5 scanlines and save them in a Compuserve GIF file:\n\
        %command infile.pix -ypos 0 -ysize 5 outfile.gif\n\
    Clip out a centered 100x100 pixel region and save it as a TIFF file:\n\
        %command infile.hdf -xsize 100 -ysize 100 outfile.tiff\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose images are to be copied.  -outfile\n\
    selects the file into which to write the resulting image copies.  The\n\
    input file is unaltered.\n\
\n\
Copying:\n\
    A region of each image in the input file is copied out into a new image\n\
    and placed into the output file.\n\
\n\
    -xsize and -ysize select the size of the region to copy.  Both default to\n\
    the full width and height of the image.\n\
\n\
    -xposition and -yposition select the upper-left corner of the region to\n\
    copy and must both be within the bounds of the source image.  (0,0) is\n\
    the upper-left corner of the image.  Both default to a position that\n\
    centers the copy region within the source image.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type:\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	6
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

	{ "xposition", "x", "Specify left edge of copy region%end\
    -xposition and -yposition select the upper-left corner of the region to\n\
    copy and must both be within the bounds of the source image.  (0,0) is\n\
    the upper-left corner of the image.  Both default to a position that\n\
    centers the copy region within the source image.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "yposition", "y", "Specify top edge of copy region%end\
    -xposition and -yposition select the upper-left corner of the region to\n\
    copy and must both be within the bounds of the source image.  (0,0) is\n\
    the upper-left corner of the image.  Both default to a position that\n\
    centers the copy region within the source image.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xsize", "x", "Specify width of copy region in pixels%end\
    -xsize and -ysize select the size of the region to copy.  Both default to\n\
    the full width and height of the image.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ysize", "y", "Specify height of copy region in pixels%end\
    -xsize and -ysize select the size of the region to copy.  Both default to\n\
    the full width and height of the image.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

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
 *	toolPosX	-  X image position
 *	toolPosY	-  Y image position
 *	toolCenterX	-  Flag X direction centering
 *	toolCenterY	-  Flag Y direction centering
 *	toolSizeW	-  Image width
 *	toolSizeH	-  Image height
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

static int	  toolPosX;		/* X Position			*/
static int	  toolPosY;		/* Y Position			*/
static int   toolCenterX;		/* Center in X			*/
static int   toolCenterY;		/* Center in Y			*/
static int	  toolSizeW;		/* Width			*/
static int	  toolSizeH;		/* Height			*/





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
main(int argc, char *argv[]) 
#else
main( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[];			/* Argument vector		*/
#endif
{
	int         nInVfb;		/* Number of images in file	*/
	int         i;			/* Counter			*/

	TagEntry   *dataEntry;		/* Entry from data table	*/

	ImVfb      *sourceVfb;		/* Source image			*/
	ImVfb      *regionVfb;		/* Region image			*/
	int         regionFields;	/* Region fields		*/
	int	    regionW;		/* Region width			*/
	int	    regionH;		/* Region height		*/

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
	 *  Copy!
	 *	-  Walk the data table looking for images.  For each one found,
	 *	   get the VFB, copy the region out of it, and replace the
	 *	   original with the copy back in the same data table.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );


		/*
		 *  Compute the copy region position if asked to center.
		 */
		if ( toolCenterX )
		{
			if ( toolSizeW == -1 )
				toolPosX = 0;
			else
				toolPosX = (ImVfbQWidth( sourceVfb ) - toolSizeW) / 2;
		}
		else if ( toolPosX > ImVfbQWidth( sourceVfb ) )
		{
			fprintf( stderr, "%s: Copy position is out of bounds for image %d of %d.\n",
				ImToolsProgram, i+1, nInVfb );
			fprintf( stderr, "%s: Entire image copied.\n",
				ImToolsProgram );
			continue;
		}

		if ( toolCenterY )
		{
			if ( toolSizeH == -1 )
				toolPosY = 0;
			else
				toolPosY = (ImVfbQHeight( sourceVfb ) - toolSizeH) / 2;
		}
		else if ( toolPosY > ImVfbQHeight( sourceVfb ) )
		{
			fprintf( stderr, "%s: Copy position is out of bounds for image %d of %d.\n",
				ImToolsProgram, i+1, nInVfb );
			fprintf( stderr, "%s: Entire image copied.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Determine the dimensions of the region to copy.
		 */
		if ( toolSizeW == -1 )
		{
			/*
			 *  No region given on the command-line.  Take
			 *  everything from the starting position up to the
			 *  right edge of the image.
			 */
			regionW = ImVfbQWidth( sourceVfb )  - toolPosX;
		}
		else
		{
			/*
			 *  Region size was given on the command-line.
			 *  Clip it to the edge of this image.
			 */
			regionW = toolSizeW;
			if ( regionW > ImVfbQWidth( sourceVfb ) - toolPosX )
				regionW = ImVfbQWidth( sourceVfb ) - toolPosX;
		}
		if ( toolSizeH == -1 )
		{
			/*
			 *  No region given on the command-line.  Take
			 *  everything from the starting position up to the
			 *  bottom edge of the image.
			 */
			regionH = ImVfbQHeight( sourceVfb ) - toolPosY;
		}
		else
		{
			/*
			 *  Region size was given on the command-line.
			 *  Clip it to the edge of this image.
			 */
			regionH = toolSizeH;
			if ( regionH > ImVfbQHeight( sourceVfb ) - toolPosY )
				regionH = ImVfbQHeight( sourceVfb ) - toolPosY;
		}
		regionFields = ImVfbQFields( sourceVfb );


		/*
		 *  Check that the resulting copy region is reasonable.
		 */
		if ( regionW <= 0 || regionH <= 0 )
		{
			fprintf( stderr, "%s: Copy size is zero for image %d of %d.\n",
				ImToolsProgram, i+1, nInVfb );
			fprintf( stderr, "%s: Entire image copied.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Copy the region into a new VFB.  Give it the same CLT
		 *  (if any) as the source image.
		 */
		if ( ImToolsVerbose )
			fprintf( stderr, "%s: Copying region at (%d,%d) of size (%d,%d) for image %d of %d\n",
				ImToolsProgram,
				toolPosX, toolPosY, regionW, regionH,
				i + 1, nInVfb );
		regionVfb = ImVfbCopy( sourceVfb,	/* Use this VFB	*/
			toolPosX, toolPosY,		/* Start here	*/
			regionW, regionH, regionFields,	/* Take this much*/
			IMVFBNEW,			/* Make a new VFB*/
			0, 0 );				/* Put it here	*/
		if ( regionVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't copy image region for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Entire image copied.\n",
				ImToolsProgram );
			continue;
		}
		ImVfbSClt( regionVfb, ImVfbQClt( sourceVfb ) );


		/*
		 *  Replace the source image with the region image in the same
		 *  data table.
		 */
		TagTableReplace( toolInTable,
			TagEntryQNthEntry( dataEntry ),
			TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &regionVfb ) );


		/*
		 *  Destroy the source VFB.
		 */
		ImVfbFree( sourceVfb );
	}


	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolInTable );
	ImVfbFree( regionVfb );


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
	 *  Get the image position and size selections.
	 */
	toolPosX = toolPosY = 0;
	toolCenterX = toolCenterY = TRUE;
	if ( ArgQNOccur( "xposition" ) != 0 )
	{
		toolPosX = (int) ArgQValue( "xposition", 0, 0 )->arg_i;
		if ( toolPosX < 0 )
		{
			fprintf( stderr, "%s: -xposition must be positive\n",
				ImToolsProgram );
			exit( 1 );
		}
		toolCenterX = FALSE;
	}
	if ( ArgQNOccur( "yposition" ) != 0 )
	{
		toolPosY = (int) ArgQValue( "yposition", 0, 0 )->arg_i;
		if ( toolPosY < 0 )
		{
			fprintf( stderr, "%s: -yposition must be positive\n",
				ImToolsProgram );
			exit( 1 );
		}
		toolCenterY = FALSE;
	}

	toolSizeW = toolSizeH = -1;
	if ( ArgQNOccur( "xsize" ) != 0 )
	{
		toolSizeW = (int) ArgQValue( "xsize", 0, 0 )->arg_i;
		if ( toolSizeW <= 0 )
		{
			fprintf( stderr, "%s: -xsize must be positive\n",
				ImToolsProgram );
			exit( 1 );
		}
	}
	if ( ArgQNOccur( "ysize" ) != 0 )
	{
		toolSizeH = (int) ArgQValue( "ysize", 0, 0 )->arg_i;
		if ( toolSizeH <= 0 )
		{
			fprintf( stderr, "%s: -ysize must be positive\n",
				ImToolsProgram );
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

