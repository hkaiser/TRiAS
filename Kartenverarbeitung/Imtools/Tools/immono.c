/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/immono.c,v 1.9 1995/06/29 01:05:35 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/immono.c,v 1.9 1995/06/29 01:05:35 bduggan Exp $"

/**
 **  FILE
 **	immono.c	-  Image File Format Conversion to Monochrome
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	immono converts image files to monochrome.
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
 **	toolThreshold	v  monochrome threshold
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: immono.c,v $
 **	Revision 1.9  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.8  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.7  1995/06/15  19:34:52  bduggan
 **	took out some useless vars
 **
 **	Revision 1.6  1995/05/18  00:02:55  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.5  1995/01/11  00:54:54  bduggan
 **	removed threshold parameter from FSDithertoMono call
 **
 **	Revision 1.4  1995/01/11  00:03:46  bduggan
 **	Added dithering support
 **
 **	Revision 1.3  1994/10/03  15:49:33  nadeau
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
 **	Revision 1.2  92/08/31  17:11:37  vle
 **	Update copyright notice.
 **	
 **	Revision 1.1  91/10/03  13:19:56  nadeau
 **	Initial revision
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
	/* command name */		"immono",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command converts each input image to monochrome and saves it to an output\n\
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
    Convert an RGB Alias PIX image to a monochrome Sun rasterfile:\n\
        %command fullcolor.pix mono.ras\n\
    Convert to monochrome using a specific threshold:\n\
        %command fullcolor.pix -threshold 42 mono.ras\n\
\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

static char *toolFullHelp = "\n\
Typical Invocations:\n\
    Convert an RGB Alias PIX image to a monochrome Sun rasterfile:\n\
        %command fullcolor.pix mono.ras\n\
    Convert to monochrome using a specific threshold:\n\
        %command fullcolor.pix -threshold 42 mono.ras\n\
\n\
Monochrome Threshold:\n\
    The monochrome threshold defines the value below which pixel colors are\n\
    considered black, and above which they are considered white.  Threshold\n\
    values range from 0 to 255.  The default threshold is at 127.\n\
";

#define IM_TOOLNOPTIONS	4
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

	{ "threshold", "n", "Set black vs white threshold to 'n'%end\
    The monochrome threshold defines the value below which pixel colors are\n\
    considered black, and above which they are considered white.  Threshold\n\
    values range from 0 to 255.  The default threshold is at 127.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "dither", NULL, "Use Floyd-Steinberg dithering%end\
    The -dither will dither the image to mono, using Floyd-Steinberg dithering.\n\
    The -threshold option does not have any effect when the -dither option is\n\
    used.",
	  ARGFNONE, 0, 0, ARGTNONE }
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
 *	toolThreshold	-  monochrome threshold
 *	toolFSDither	-  flag indicating whether to use dithering
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

static int	  toolThreshold;	/* Monochrome threshold		*/
static int	  toolFSDither;		/* Flag for dithering		*/ 





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Convert each image to monochrome.
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

	int	    w, h;		/* Width and height of image	*/
	int	    fields;		/* Image fields			*/

	ImVfb      *sourceVfb;		/* Source image			*/
	ImVfb      *monoVfb;		/* New monochrome image		*/

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
	 *  Convert to monochrome.
	 *	-  walk the input image list and convert each one to
	 *	   monochrome.  Replace the input images with the new
	 *	   images.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );


		/*
		 *  Make a new VFB with the same fields as the input VFB,
		 *  but replace its image fields with a monochrome field.
		 */
		w = ImVfbQWidth( sourceVfb );
		h = ImVfbQHeight( sourceVfb );
		fields = ImVfbQFields( sourceVfb );
		monoVfb = ImVfbAlloc( w, h,
			(fields & ~IMVFBIMAGEMASK) | IMVFBMONO );
		if ( monoVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't create monochrome image for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Original image output.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Copy all non-image fields from the original VFB to the
		 *  new soon-to-be-monochrome VFB.
		 */
		if ( fields & ~IMVFBIMAGEMASK )
		{
			if ( ImVfbCopy( sourceVfb,	/* Use this VFB	*/
				0, 0,			/* Start here	*/
				w, h, 			/* This much	*/
				(fields & ~IMVFBIMAGEMASK),/* Take this much*/
				monoVfb,		/* Put in VFB	*/
				0, 0 ) == IMVFBNULL )	/* Put it here	*/
			{
				ImPError( ImToolsProgram );
				fprintf( stderr, "%s: Couldn't create monochrome image for image %d of %d.\n",
					ImToolsProgram, i + 1, nInVfb );
				fprintf( stderr, "%s: Original image output.\n",
					ImToolsProgram );
				continue;
			}
		}

		/*
		 *  Convert the source image to monochrome and save the
		 *  new pixels in the mono VFB.
		 */
		if ( ImToolsVerbose )
			fprintf( stderr, "%s: Converting image %d of %d to monochrome\n",
				ImToolsProgram,
				i + 1, nInVfb );
		if (toolFSDither)
			monoVfb = ImVfbFSDitherToMono ( sourceVfb, monoVfb);
		else
			monoVfb = ImVfbToMono( sourceVfb, toolThreshold, monoVfb );
		
		if ( monoVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't create monochrome image for image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Original image output.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Replace the source image with the mono image in the same
		 *  data table.
		 */
		TagTableReplace( toolInTable,
			TagEntryQNthEntry( dataEntry ),
			TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &monoVfb ) );


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
	toolCommand.arg_help2 = toolHelp;

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
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1);
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
	 *  Get the monochrome threshold
	 */
	if ( ArgQNOccur( "threshold" ) != 0 )
	{
		toolThreshold = ArgQValue( "threshold", 0, 0 )->arg_i;
		if ( toolThreshold < 0 || toolThreshold > 255 )
		{
			fprintf( stderr, "%s: Monochrome thresholds must be in the range 0 to 255\n",
				ImToolsProgram );
			exit ( 1 );
		}
	}
	else
		toolThreshold = 127;

	if (ArgQNOccur( "dither" ) != 0)
		toolFSDither = 1;
	else
		toolFSDither = 0;



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

