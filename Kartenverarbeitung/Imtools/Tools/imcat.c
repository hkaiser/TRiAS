/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imcat.c,v 1.15 1995/06/30 22:17:25 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imcat.c,v 1.15 1995/06/30 22:17:25 bduggan Exp $"

/**
 **  FILE
 **	imcat.c		-  Concatenate images into a multi-image file
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imcat takes multiple input image files, combines their data, and writes
 **	the information out as a multi-image file.
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
 **	toolInFilenames	v  the names of the input files (could be 'stdin')
 **	toolOutFilename v  the name of the output file (could be 'stdout')
 **
 **	toolInFormats	v  the name of the input files' formats (could be '\0')
 **	toolOutFormat	v  the name of the output file's format (could be '\0')
 **
 **	toolInTable	v  a table for the storage of data read in
 **	toolInFlagsTable  v  a table for the storage of read flags
 **	toolOutFlagsTable v  a table for the storage of write flags
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imcat.c,v $
 **	Revision 1.15  1995/06/30  22:17:25  bduggan
 **	added some casts
 **
 **	Revision 1.14  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.13  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.12  1995/06/15  18:52:42  bduggan
 **	took out some extra vars
 **
 **	Revision 1.11  1995/05/17  23:51:23  bduggan
 **	Added new options-merging routines.  Added option-specific help.
 **
 **	Revision 1.10  1994/10/03  15:49:07  nadeau
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
 ** 	Revision 1.9  93/03/02  11:32:33  secoskyj
 ** 	Does not try to check read permissions on filename "-", which
 ** 	represents stdin
 ** 
 ** 	Revision 1.8  93/02/10  16:41:30  nadeau
 ** 	Fixed file header so that RCS log messages would be included.
 ** 
 **	Revision 1.7  93/01/11  23:18:12  secoskyj
 **	Fixed infinite loop bug when -frames x-x occurs, where x is an integer.
 **
 **	Revision 1.6  92/12/09  18:44:33  nadeau
 **	Corrected includes.
 **
 **	Revision 1.5  92/12/09  16:54:18  nadeau
 **	Updated include files used to satisfy the Cray.
 **
 **	revision 1.4        
 **	Revision 1.4  92/12/13  11:05:31  groening
 **	changed count =-1 to count = -1 to make dev compiler happy
 **
 **	Revision 1.3  92/11/04  13:17:13  groening
 **	changed it so differnt file types can be joined together
 **
 **	Revision 1.2  92/10/12  14:26:20  nadeau
 **	Rearranged the code to match other image tools' structure.
 **	Added additional error checking.
 **
 **	Revision 1.1  92/07/08  09:24:03  groening
 **	Initial revision
 **
 **/

/**
 **  CODE CREDITS
 **     Custom development, Chris Groening, San Diego Supercomputer Center, 1992.
 **/

#include <sys/types.h>
#include "imtools.h"
#include <malloc.h>
#include <unistd.h>
#include <values.h>

#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
#else
static void toolInit( );		/* Initialize things		*/
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
	/* command name */		"imcat",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command concatenates information found in multiple input image files and\n\
writes it to a single multi-image file.  Input and output files may have\n\
different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] infilenames... -outfile outfilename",
	"[options...] infilenames... -outfile outfilename",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    Concatenate 6 rgb files (single03-single08) into an HDF multi-image file:\n\
	%command single%02d.rgb -frames 3-8 -outfile many.hdf\n\
    Concatenate three differently named XWD images into a TIFF file:\n\
	%command one.xwd tiger.xwd beer.xwd -outfile many.tiff\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile lists the image files to be concatenated.  -outfile gives the\n\
    name of the file in which to place the results.\n\
\n\
    When listing input files explicitly, each input file name is given on\n\
    the command line.\n\
\n\
    Input files may be listed implicitly by giving a file name template with\n\
    an embedded %d (ala printf) where the frame number should be placed.\n\
    The -frames argument then gives a range of frame numbers to use for\n\
    input file names.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type:\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	3
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_infilename", "Specify an incoming image file name%end\
    The -infile argument specifies the name one of the input files.          \n\
                                                                             \n\
    The file's format may be specified with the -informat flag.              \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
",
	  ARGFREQUIRED|ARGFMULTIPLE|ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_outfilename", "Specify the outgoing image file name%end\
    The -%option argument specifies the name of the output file.             \n\
                                                                             \n\
    The file's format may be specified with the -outformat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdout.  When using       \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED, 1, 1, ARGTSTRING },

	{ "frames", "range", "Specify frame numbers of input files%end\
    The -%option argument specifies the frame number of the input files.     \n\
                                                                             \n\
    This option may be used to read in files whose names are the same except \n\
    for a single number.                                                     \n\
                                                                             \n\
    To use this option, embed a %d in the name of the template filename.  Then\n\
    specify the range of values with the -%option option.                   \n\
                                                                            \n\
    For instance,                                                           \n\
	%command single%02d.rgb -frames 3-8 -outfile many.hdf               \n\
    will concatenate 6 rgb files (single03-single08) into an HDF multi-image\n\
    file.\
",
	  ARGFNONE , 1, 1, ARGTINT | ARGTRANGE },

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
 *	toolInFilenames	-  the names of the input files (could be 'stdin')
 *	toolOutFilename	-  the name of the output file (could be 'stdout')
 *
 *	toolInFormats	-  the names of the input files' formats (could be NULL)
 *	toolOutFormat	-  the name of the output file's format (could be NULL)
 *
 *	toolInTable	-  a table for the storage of data read in
 *	toolInFlagsTable -  a table for the storage of read flags
 *	toolOutFlagsTable-  a table for the storage of write flags
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      **toolInFilenames;	/* Input file name		*/
static int	  toolNInFiles;		/* # of input files		*/
static char      **toolInFormats;	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolInTable;		/* Data tag table		*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static int	  toolFrameStart;	/* start of frames		*/
static int	  toolFrameEnd;		/* end of frames		*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in all input files, putting data into data table.
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
	int argc;			/* Argument count		*/
	char *argv[];			/* Argument vector		*/
#endif
{
	int         i, j;		/* Counter			*/
	int	    nInVfb;		/* Number of input images	*/
	char	    inFilename[1024];	/* Input file name		*/
	int	    hadError = FALSE;	/* Did we have an error?	*/
	int	    framesNeeded = FALSE;/* Is a -frames arg needed?	*/

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
	 *  Make sure all the input files exist.  Doing this first, before
	 *  trying to open and read the files can save the user quite a bit
	 *  of reading time when they make a filename typo.
	 */
	for ( i = 0; i < toolNInFiles; i++ )
	{
		if ( strcmp( toolInFilenames[i], "-" ) == 0 )
			continue;

		if ( strchr( toolInFilenames[i], '%' ) == NULL )
		{
			/*
			 *  Explicit file name without embedded printf %d.
			 *  Check the file.
			 */
			if ( _access( toolInFilenames[i], R_OK ) == -1 )
			{
				fprintf( stderr, "%s: Input file %s cannot be read\n", ImToolsProgram, toolInFilenames[i] );
				hadError = TRUE;
			}
			continue;
		}

		/*
		 *  Implicit file name with embedded printf %d.  Read them
		 *  all in.
		 */
		framesNeeded = TRUE;
		if ( toolFrameStart == -1 )
		{
			/* No frame range given.  Complain.		*/
			fprintf( stderr, "%s: Use of a %%d in an input file name requires a -frames option\n", ImToolsProgram );
			fprintf( stderr, "%s: to indicate what range of frame numbers to put there.\n", ImToolsProgram );
			exit( 1 );
		}
		if ( toolFrameStart < toolFrameEnd )
		{
			for ( j = toolFrameStart; j <= toolFrameEnd; j++ )
			{
				sprintf( inFilename, toolInFilenames[i], j );
				if ( _access( inFilename, R_OK ) == -1 )
				{
					fprintf( stderr, "%s: Input file %s cannot be read\n", ImToolsProgram, inFilename );
					hadError = TRUE;
				}
			}
		}
		else
		{
			for ( j = 0; j <= toolFrameStart - toolFrameEnd; j++)
			{
				sprintf( inFilename, toolInFilenames[i],
					toolFrameStart - j );
				if ( _access( inFilename, R_OK ) == -1 )
				{
					fprintf( stderr, "%s: Input file %s cannot be read\n", ImToolsProgram, inFilename );
					hadError = TRUE;
				}
			}
		}
	}
	if ( hadError )
	{
		fprintf( stderr, "%s: Aborted due to problems with input files.\n", ImToolsProgram );
		exit( 1 );
	}
	if ( toolFrameStart != -1 && framesNeeded == FALSE )
	{
		fprintf( stderr, "%s: -frames requires that input files include %%d in their names\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Read in each input file.
	 *	-  Open the file (or stdin) and read data into the data table.
	 */
	for ( i = 0; i < toolNInFiles; i++ )
	{
		if ( strchr( toolInFilenames[i], '%' ) == NULL )
		{
			/*
			 *  Explicit file name without embedded printf %d.
			 *  Read the file in.
			 */
			ImToolsFileRead( toolInFilenames[i], toolInFormats[i],
				toolInFlagsTable, toolInTable );
			continue;
		}

		/*
		 *  Implicit file name with embedded printf %d.  Read them
		 *  all in.
		 */
		if ( toolFrameStart < toolFrameEnd )
		{
			for ( j = toolFrameStart; j <= toolFrameEnd; j++ )
			{
				sprintf( inFilename, toolInFilenames[i], j );
				ImToolsFileRead( inFilename, toolInFormats[i],
					toolInFlagsTable, toolInTable );
			}
		}
		else
		{
			for ( j = 0; j <= toolFrameStart - toolFrameEnd; j++)
			{
				sprintf( inFilename, toolInFilenames[i],
					toolFrameStart - j );
				ImToolsFileRead( inFilename, toolInFormats[i],
					toolInFlagsTable, toolInTable );
			}
		}
	}


	/*
	 *  Check for errors
	 *	-  no input images
	 */
	nInVfb = TagTableQNEntry( toolInTable, "image vfb" );
	if ( nInVfb == 0 )
	{
		fprintf( stderr, "%s: Input files contained no images!\n",
			ImToolsProgram );
		exit( 1 );
	}

	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename,
		toolOutFormat, toolOutFlagsTable, toolInTable );
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
toolInit( int argc, char *argv[] )
#else
toolInit( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argument vector		*/
#endif
{
	int	    k;			/* Counter			*/
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/
        ArgValue   *value;              /* Argument value               */

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
	 *  Determine how many input files we've got and allocate space for
	 *  their names.
	 */
	toolNInFiles = ArgQNOccur("infile");

	toolInFilenames = (char **)malloc( sizeof( char *) * toolNInFiles );
	toolInFormats   = (char **)malloc( sizeof( char *) * toolNInFiles );

	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolInFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolInFlagsTable, "in");

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );

	for (k = 0; k< toolNInFiles; k++)
	{
		toolInFilenames[k] = (char*) malloc( sizeof(char) * 500);
		toolInFormats[k]   = (char*) malloc( sizeof(char) * 50);
		ImToolsGetNameAndFormat ( "in", k, toolInFilenames[k], toolInFormats[k]);
	}
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);

        /*
         *  Get the number of frames.
         */
        toolFrameStart = toolFrameEnd = -1;
        if ( ArgQNOccur( "frames" ) != 0 )
        {
                value = ArgQValue( "frames", 0, 0 );
                switch ( value->arg_rform )
                {
                case ARGRCLOSED:        /* n-m  start and end values    */
                        toolFrameStart = (int) value->arg_ir1;
                        toolFrameEnd   = (int) value->arg_ir2;
                        break;

                case ARGROPEN:          /* n-   length only             */
			fprintf( stderr, "%s: Missing end of frame range on -frames option\n", ImToolsProgram );
			exit( 1 );

                case ARGRSINGLE:        /* n    length only             */
			toolFrameStart = 0;
                        toolFrameEnd   = (int) value->arg_i - 1;
                        break;
                }

		if (toolFrameStart<0)
		{
			fprintf (stderr, "%s: -frame start number must be positive!\n",
				ImToolsProgram);
			exit(1);
		}
		if (toolFrameEnd<0)
		{
			fprintf (stderr, "%s: -frame end number msut be positive!\n",
				ImToolsProgram);
			exit(1);
		}
        }



}
