/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imflip.c,v 1.8 1995/06/29 01:05:35 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imflip.c,v 1.8 1995/06/29 01:05:35 bduggan Exp $"

/**
 **  FILE
 **	imflip.c	-  Flip an image about a speicified axis
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imflip flips an image(s) horizontally, vertically, or both and
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
 **	toolFlip	v  Flip direction 
 **	toolFlipMessage	v  Flip diagnostic message 
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imflip.c,v $
 **	Revision 1.8  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.7  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.6  1995/06/15  19:13:31  bduggan
 **	took out some useless vars
 **
 **	Revision 1.5  1995/05/18  00:01:30  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.4  94/10/03  15:49:23  nadeau
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
 **	Revision 1.3  92/08/31  17:06:48  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.2  91/10/03  13:21:25  nadeau
 **	Changed to allow no flip options if the user so desires.
 **	
 **	Revision 1.1  91/09/18  17:31:13  mcleodj
 **	Initial revision
 **	
 **
 **/

#include "imtools.h"

/*
 * CODE CREDITS
 *
 *	  Custom development, Jim McLeod, San Diego Supercomputer Center, 1991.
 *
 */


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
	/* command name */		"imflip",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command flips an input image vertically, horizontally, or both and stores\n\
the results in the specified output file.  Input and output files may have\n\
different image file formats.\n\
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
    Flip a Pixar PIC image horizontally and save result as a Sun rasterfile:\n\
        %command infile.pic -xflip outfile.ras\n\
    Flip a SGI RGB image vertically and save result as a Wavefront RLA file:\n\
        %command infile.rgb -yflip outfile.rla\n\
    Flip an Alias PIX image about both axes and save as a Pixar PIC file:\n\
        %command infile.pix -xflip -yflip outfile.pic\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose images are to be flipped.  -outfile\n\
    selects the file into which to write the resulting flipped images.  The\n\
    input file is unaltered.\n\
\n\
Flipping:\n\
    -xflip flips the image left-to-right.  -yflip flipts it top-to-bottom.\n\
    One, both, or neither may be given.\n\
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
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -%option argument specifies the name of the input file.              \n\
                                                                             \n\
    By default, the input file's image file format is determined by the      \n\
    file's magic number or the filename extension (like .bmp for BMP files). \n\
    To override the default, explicit format names may be given using the    \n\
    -informat flag.                                                          \n\
                                                                             \n\
    For instance,                                                            \n\
            %command -informat ras myfile -outfile out.rgb                   \n\
    indicates that myfile is a Sun Rasterfile.  For a list of image formats  \n\
    that are supported type '%command -help -informat'.                      \n\
                                                                             \n\
    A single dash ('-') for the input filename indicates stdin.  When using  \n\
    stdin, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    The -%option argument specifies the name of the output file.             \n\
                                                                             \n\
    By default, an output file's image file format is determined by the      \n\
    file's magic number filename extension (like .bmp for BMP files).  To    \n\
    override the default, explicit format names may be given using the       \n\
    -outformat flag.                                                         \n\
                                                                             \n\
    For instance,                                                            \n\
            %command in1.ras -outfile out -outformat hdf                     \n\
    indicates that the output file should be an HDF file.  For a list of     \n\
    image formats that are supported, type '%command -help -outformat'       \n\
                                                                             \n\
    A single dash ('-') for an output filename indicates stdout.  When using \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "xflip", NULL, "Specify horizontal flip%end\
    -xflip flips the image left-to-right",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "yflip", NULL, "Specify vertical flip%end\
    -yflip flips the image top-to-bottom",
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
 *	toolInFlagsTable -  a table for the storage of read flags
 *	toolOutFlagsTable-  a table for the storage of write flags
 *
 *	toolFlip	-  Flip direction
 *	toolFlipMessage	-  Flip diagnostic message 
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

static int	  toolFlip;		/* Flip direction		*/
static char	  toolFlipMessage[10];	/* Flip diagnostic message	*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Flip each image.
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

	ImVfb      *sourceVfb;		/* Source image			*/

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
	 *  Flip!
	 *	-  Walk the data table looking for images.  For each one found,
	 *	   get the VFB and flip the VFB data about specified direction.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );


		/*
		 *  Flip the image in place.
		 */
		if ( ImToolsVerbose )
		{
			if ( toolFlip )
				fprintf( stderr, "%s: Flipping image %d of %d in %s direction\n",
					ImToolsProgram, i + 1, nInVfb, toolFlipMessage);
			else
				fprintf( stderr, "%s: Copying image %d of %d since no flip direction specified\n",
					ImToolsProgram, i + 1, nInVfb );
		}


		/*
		 * Since we can assume that ImVfbFlip will correctly
		 * flip an image whether we write the flipped version
		 * over the original Vfb or not, the sourceVfb will
		 * get overwritten to save an allocation of a new Vfb
		 * (which would be handled by ImVfbFlip any way )
		 */
		if ( toolFlip )
			ImVfbFlip( 	sourceVfb,	/* Use this VFB	     */
					toolFlip,	/* Flip direction    */
					sourceVfb );	/* Write back to VFB */

		if ( sourceVfb == IMVFBNULL )
		{
			ImPError( ImToolsProgram );
			fprintf( stderr, "%s: Couldn't flip image %d of %d.\n",
				ImToolsProgram, i + 1, nInVfb );
			fprintf( stderr, "%s: Unflipped image copied to output file.\n",
				ImToolsProgram );
			continue;
		}
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
	 *  Get the flip direction(s).
	 */
	toolFlip = 0;		/* No flipping				*/
	strcpy( toolFlipMessage, "none" );
	if ( ArgQNOccur( "xflip" ) != 0 )
	{
		toolFlip = IMVFBXFLIP;
		strcpy( toolFlipMessage, "x.");
	}

	if ( ArgQNOccur( "yflip" ) != 0 )
	{
		toolFlip = IMVFBYFLIP;
		strcpy( toolFlipMessage, "y.");
	}

	if ( ( ArgQNOccur( "xflip" ) != 0 ) && ( ArgQNOccur( "yflip" ) != 0 ) )
	{
		toolFlip = IMVFBXYFLIP;
		strcpy( toolFlipMessage, "x and y.");
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

