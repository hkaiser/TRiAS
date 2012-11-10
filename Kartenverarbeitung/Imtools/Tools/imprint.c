/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imprint.c,v 1.6 1995/06/29 01:05:35 bduggan Exp $
 **     Copyright (c) 1989, 1995  San Diego Supercomputer Center (SDSC)
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imprint.c,v 1.6 1995/06/29 01:05:35 bduggan Exp $"

/**
 **  FILE
 **	imprint.c	-  Display the contents of a vfb 
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imprint displays the pixel values of the vfb  
 **	either in the range of 0-255 or 0.0-1.0 and stores
 **	ascii display into a specified file	
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
 **
 **	toolInTable	v  a table for the storage of data read in
 **	toolFlagsTable	v  a table for the storage of read flags
 **
 **	toolPrint	v  Type of pixel range ( int or float ) 
 **	toolPrMessage	v  Print diagnostic message 
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imprint.c,v $
 **	Revision 1.6  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.5  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.4  1995/06/29  00:34:54  bduggan
 **	changed macro name
 **
 **	Revision 1.3  1995/05/18  00:03:29  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.2  94/10/03  15:49:38  nadeau
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
 **	Revision 1.1  92/12/01  14:07:37  nadeau
 **	Initial revision
 **	
 **	
 **
 **/

#include "imtools.h"

/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1992.
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
	/* command name */		"imprint",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command displays the pixel values of an image \n\
and stores the output in the specified output file.  \n\
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
	"SDSC Image Tools, October 1991.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    Display the contents of a Pixar pic rgb file (0-255) and save in file\n\
        %command infile.pic -int outfile\n\
    Display the contents of an Alias pix rgb file (0.0-1.0) and save in file\n\
        %command infile.pix -float outfile\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose pixels are to be displayed.  -outfile\n\
    selects the file into which to write the resulting output.  The\n\
    input file is unaltered.\n\
\n\
Printing:\n\
    -int displays pixel values in the range of 0 to 255.  \n\
    -float displays pixels values in the range of 0.0 to 1.0.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	4
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output file name",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "int", NULL, "Specify an int (0-255) display",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "float", NULL, "Specify a float (0.0-1.0) display",
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
 *
 *	toolInTable	-  a table for the storage of data read in
 *	toolFlagsTable	-  a table for the storage of read flags
 *
 * 	toolPrint	-  Type of pixel range ( int or float ) 
 * 	toolPrMessage	-  Print diagnostic message 
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/

static TagTable *toolInTable;		/* Data tag table		*/
static TagTable *toolFlagsTable;	/* Flags tag table		*/

static int	  toolPrint;		/* Display format		*/
static char	  toolPrMessage[10];	/* Print diagnostic message	*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Rotate each image.
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

#ifdef __STDC__
main( int argc, char *argv[] )
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
	FILE	   *fp;			/* Output file name if any	*/

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
	ImToolsFileRead( toolInFilename, toolInFormat, toolFlagsTable,
		toolInTable );

	/*
	 *  Prepare output file for writing
	 *	- Open file for write
	 */
        if ( (fp=fopen(toolOutFilename, "w")) == NULL )
        {
            fprintf( stderr, "Cannot create file:%s \n",toolOutFilename);
            exit(1);
        }

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
	 *  Print!
	 *	-  Walk the data table looking for images.  For each one found,
	 *	   get the VFB and display the contents of the VFB data.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );

		/*
		 *  Rotate the image into new vfb.
		 */
		if ( ImToolsVerbose )
		{
			if ( toolPrint )
				fprintf( stderr, "%s: Printing image %d of %d with %s values\n",
					ImToolsProgram, i + 1, nInVfb, toolPrMessage);
			else
				fprintf( stderr, "%s: Not printing image %d of %d since no value format specified\n",
					ImToolsProgram, i + 1, nInVfb );
		}

		/*
		 *  Print the image if command option was specified
		 */
		if ( toolPrint )
		{
			fprintf( fp, "Image %i :\n", i+1 );
			ImVfbPrint ( fp, toolPrint, sourceVfb );
		}

                /*
                 *  Destroy the source VFB.
                 */
                ImVfbFree( sourceVfb );

	}

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
toolInit( int argc, char *argv[] )
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
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "in", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs1 );
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
	 *  Get the printing format.
	 */
	toolPrint = 0;		
	if ( ArgQNOccur( "float" ) != 0 )
	{
		toolPrint = IMVFBPRINTFLOAT;
		strcpy( toolPrMessage, "float");
	}

	if ( ArgQNOccur( "int" ) != 0 )
	{
		toolPrint = IMVFBPRINTINT;
		strcpy( toolPrMessage, "int");
	}

	if ( ( ArgQNOccur( "float" ) != 0 ) && ( ArgQNOccur( "int" ) != 0 ) )
	{
		toolPrint = IMVFBPRINTINTFLOAT;
		strcpy( toolPrMessage, "both");
	}

	if ( toolPrint==0 )
	{  	/* Default to int. */
		toolPrint = IMVFBPRINTINT;
		strcpy( toolPrMessage, "int");
	}



	/*
	 * Set up the incoming flags table
	 * and get the name and type of our file.
	 */
	toolFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolFlagsTable, "in");
	ImToolsGetNameAndFormat ( "in", 0, toolInFilename, toolInFormat);

	/*
	 * Get the name of the output file
	 */
	 strcpy( toolOutFilename, ArgQValue( "outfile", 0, 0 )->arg_s );
}

