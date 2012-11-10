/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imsplit.c,v 1.10 1995/06/30 22:20:54 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imsplit.c,v 1.10 1995/06/30 22:20:54 bduggan Exp $"

/**
 **  FILE
 **	imsplit.c	-  Split multi-image files into multiple files
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imsplit takes an input multi-image file and splits it into multiple
 **	single-image output files.
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
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **     $Log: imsplit.c,v $
 **	Revision 1.10  1995/06/30  22:20:54  bduggan
 **	added some casts
 **
 **	Revision 1.9  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.8  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.7  1995/06/15  19:43:30  bduggan
 **	took out some useless vars
 **
 **	Revision 1.6  1995/05/18  00:04:53  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.5  94/10/03  15:49:49  nadeau
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
 **	
 **
 **/

/**
 **  CODE CREDITS
 **
 **	Custom development, Dave Nadeau, San Diego Supercomputer Center, 1992.
 **
 **/

#include "imtools.h"
#include <malloc.h>

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
	/* command name */		"imsplit",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command reads a multi-image input file and splits it into multiple single-\n\
image output files.  Input and output files may have different image file\n\
formats.\n\
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
    Split an HDF multi-image file into multiple RGB files:\n\
        %command many.hdf single%02d.rgb\n\
    Extract images 3, 4, and 5 and save them to Sun rasterfiles:\n\
        %command many.hdf -frames 3-5 single%02d.ras\n\
    Extract images 1, 6, and 9:\n\
        %command lots.tiff -frames 1 6 9 output%d.rgb\n\
    Extract images 1, 6, and 9 again:\n\
        %command lots.tiff -frame 1 -frame 6 -frame 9 output%d.rgb\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile names the multi-image input file from which images are to be\n\
    read.  -outfile gives an output image file name template with an\n\
    embedded %d directive indicating where to insert a frame number.\n\
    An individual output file will be created for each extracted image.\n\
\n\
    By default all images in the input file are extracted into separate\n\
    output files.  -frames may be used to provide a list of frames to\n\
    extract.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	3
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -infile argument gives the name of the multi-image file from\n\
    which images are to be read.\n\
                                                                             \n\
    The file's format may be specified with the -in1format flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
    ",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    -outfile gives an output image file name template with an\n\
    embedded %d directive indicating where to insert a frame number.\n\
    An individual output file will be created for each extracted image.\n\
\n\
    By default all images in the input file are extracted into separate\n\
    output files.  -frames may be used to provide a list of frames to\n\
    extract.\n\
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "frames", "frame_numbers...", "List frames to extract%end\
    By default all images in the input file are extracted into separate\n\
    output files.  -frames may be used to provide a list of frames to\n\
    extract.  For instance, -frames 4-6 will only extract images 4,5 and\n\
    6 from the multi-image file.",
	  ARGFNONE | ARGFMULTIPLE, 1, ARGVNOMAX, ARGTINT | ARGTRANGE },

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
 *	toolInFlagsTable - a table for the storage of read flags
 *	toolOutFlagsTable- a table for the storage of write flags
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolInTable;		/* Data tag table		*/
static TagTable *toolOutTable;		/* Data tag table		*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

typedef struct toolFrames
{
	int frameStart;			/* Starting frame of range	*/
	int frameEnd;			/* Ending frame of range	*/
	struct toolFrames *frameNext;	/* Next frame in list		*/
	struct toolFrames *framePrev;	/* Previous frame in list	*/
} toolFrames;

static toolFrames *toolFramesList = NULL;	/* List of frames	*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Write out each output file (get data from data table).
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
	int         i, j, k;		/* Counters			*/
	int	    n;			/* Number of frames to extract	*/
	TagEntry   *dataEntry;		/* Entry from data table	*/
	TagEntry   *reEntry;		/* copy of Entry from data table*/
	char	   *tag;		/* Entry tag name		*/
	int	    startFrame;		/* Starting frame of a range	*/
	int	    endFrame;		/* Ending frame of a range	*/
	toolFrames *pFrame;		/* Frame list entry		*/
	toolFrames *pFrame2;		/* Frame list pointer		*/
        char        outFilename[1024];  /* output file's name           */
        ArgValue   *value;              /* Argument value               */

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
	 *  Read in each input file.
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
         *  Build up a sorted linked list of frames to extract.
         */
	for ( i = 0, n = 0; i < ArgQNOccur( "frames" ); i++ )
	{
		for ( j = 0; j < ArgQNValue( "frames", i ); j++ )
		{
			value = ArgQValue( "frames", i, j );
			switch ( value->arg_rform )
			{
			case ARGRCLOSED:        /* n-m  start and end values*/
				startFrame = (int) value->arg_ir1;
				endFrame   = (int) value->arg_ir2;
				break;

			case ARGROPEN:          /* n-   start and wildcard*/
				startFrame = (int) value->arg_ir1;
				endFrame   = (int) nInVfb - 1;
				break;

			case ARGRSINGLE:        /* n    one only	*/
				startFrame = (int) value->arg_i;
				endFrame   = startFrame;
				break;
			}
			if ( startFrame > endFrame )
			{
				k = startFrame;
				startFrame = endFrame;
				endFrame = k;
			}
			if ( startFrame < 0 )
			{
				fprintf( stderr, "%s: Frame ranges must be positive!\n", ImToolsProgram );
				exit( 1 );
			}
			if ( endFrame >= nInVfb )
			{
				fprintf( stderr, "%s: There are only %d frames in the input file!\n", ImToolsProgram, nInVfb );
				exit( 1 );
			}
			n += endFrame - startFrame + 1;


			/*
			 *  Allocate a new list entry and initialize it.
			 */
			if ( (pFrame = (toolFrames *)malloc( sizeof( toolFrames ) )) == NULL )
			{
				perror( ImToolsProgram );
				exit( 1 );
			}
			pFrame->frameStart = startFrame;
			pFrame->frameEnd   = endFrame;
			pFrame->frameNext  = NULL;
			pFrame->framePrev  = NULL;


			/*
			 *  Insert the entry into the sorted list of frames.
			 */
			if ( toolFramesList == NULL )
			{
				toolFramesList = pFrame;
				continue;
			}
			pFrame2 = toolFramesList;
			while ( pFrame2->frameNext != NULL )
			{
				if ( startFrame < pFrame2->frameStart )
					break;
				pFrame2 = pFrame2->frameNext;
			}
			if ( pFrame2->frameNext == NULL &&
				startFrame > pFrame2->frameStart )
			{
				/* Add to the end of the list.		*/
				pFrame2->frameNext = pFrame;
				pFrame->framePrev  = pFrame2;
				continue;
			}
			if ( pFrame2->framePrev == NULL )
			{
				/* Add to the start of the list.	*/
				toolFramesList = pFrame;
				pFrame->frameNext = pFrame2;
				pFrame2->framePrev = pFrame;
				continue;
			}
			/* Add before this entry.			*/
			pFrame2->framePrev->frameNext = pFrame;
			pFrame->framePrev = pFrame2->framePrev;
			pFrame2->framePrev = pFrame;
			pFrame->frameNext = pFrame2;
		}
	}
	if ( toolFramesList == NULL )
	{
		if ( (toolFramesList = (toolFrames *)malloc( sizeof( toolFrames ) )) == NULL )
		{
			perror( ImToolsProgram );
			exit( 1 );
		}
		toolFramesList->frameStart = 0;
		toolFramesList->frameEnd   = nInVfb;
		toolFramesList->frameNext  = NULL;
		toolFramesList->framePrev  = NULL;
		n = nInVfb;
	}


	/*
	 *  Make sure we were given an output file name with a printf
	 *  directive when we're supposed to extract more than one file.
	 */
	if ( (strchr( toolOutFilename, '%' ) == NULL) &&
		(nInVfb != 1) && (n != 1) )
	{
		fprintf( stderr, "%s: Output file name template must include a %%d for the\n", ImToolsProgram );
		fprintf( stderr, "%s: frame number when extracting more than 1 image\n", ImToolsProgram );
		exit( 1 );
        }


	/*
	 *  Split!
	 *	-  Scan the tag table.  As we find tags, add them to the
	 *	   output tag table.
	 *		-  If a tag from the input tag table is already present
	 *	   	   in the output table, replace it.
	 *		-  If not, append it.
	 *	-  On each VFB tag, write out the output table if the image
	 *	   number is one of those in the frames list.
	 */
	pFrame = toolFramesList;
	for ( i = 0, k = -1;
		(dataEntry = TagTableQLinear( toolInTable, i )) != TAGENTRYNULL;
		i++ )
	{
		/*
		 *  Get the next tag of the data entry.
		 */
		tag = TagEntryQTag( dataEntry );


		/*
		 *  Add the entry to the output tag table.
		 */
	        reEntry = TagEntryDup( dataEntry );
	        if ( TagTableQNEntry( toolOutTable, tag ) != 0 )
		{
			/*
			 *  Tag is already in the output table.  Replace it.
			 */
			j = TagEntryQNthEntry( TagTableQDirect( toolOutTable, tag, 0 ) );
			TagTableReplace( toolOutTable, j, reEntry );
		}
	        else
		{
			/*
			 *  Tag isn't in output table yet.  Add it.
			 */
			TagTableAppend( toolOutTable, reEntry );
		}


		/*
		 *  Write out the current state of the output tag table
		 *  if the tag we just added was an image, and if it
		 *  is one of the images we want to extract!
		 */
		if ( strcmp( tag, "image vfb" ) != 0 )
			continue;		/* Not an image		*/
		k++;
		while ( pFrame && k > pFrame->frameEnd )
			pFrame = pFrame->frameNext;
		if ( !pFrame )
			break;			/* Done with list	*/
		if ( k < pFrame->frameStart )
			continue;		/* Not in range		*/


		if ( ImToolsVerbose )
		{
			fprintf( stderr, "%s: Extracting image %d of %d \n",
					ImToolsProgram, k+1, nInVfb );
		}

		sprintf( outFilename, toolOutFilename, k );
		ImToolsFileWrite( outFilename, toolOutFormat,
			 toolOutFlagsTable, toolOutTable );
	}
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

#ifdef __STDC__
static void toolInit( int argc, char *argv[] )
#else
static void toolInit(argc, argv )                /* Initialize things            */
int argc;
char *argv[];
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
