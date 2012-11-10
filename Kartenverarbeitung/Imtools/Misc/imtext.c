/**
 **     $Header: /sdsc/dev/vis/image/imtools/v2.2/imtools/src/RCS/imtext.c,v 1.0
93/05/14 14:39:24 shane Exp $
 **     Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC)
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imtext.c,v 1.2 1995/06/14 20:01:30 bduggan Exp $"

/**
 **  FILE
 **     imtext.c        -  Add text over image
 **
 **  PROJECT
 **     IM              -  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	ImText allows the user to place text over an image. Color, alpha,
 **	position, and font of the text is selectable.
 **
 **  PUBLIC CONTENTS
 **                     d =defined constant
 **                     f =function
 **                     m =defined macro
 **                     t =typedef/struct/union
 **                     v =variable
 **                     ? =other
 **
 **     main            f  main program
 **
 **  PRIVATE CONTENTS
 **     toolCommand     v  tool-specific tool info
 **     toolHelp        v  tool-specific help
 **     toolFullHelp    v  tool-specific help
 **     toolOptions     v  tool-specific options
 **     toolEquivs      v  tool-specific equivalent keywords
 **
 **     toolInFilename  v  the name of the input file (could be 'stdin')
 **     toolOutFilename v  the name of the output file (could be 'stdout')
 **
 **     toolInFormat    v  the name of the input file's format (could be '\0')
 **     toolOutFormat   v  the name of the output file's format (could be '\0')
 **
 **     toolInTable     v  a table for the storage of data read in
 **     toolInFlagsTable  v  a table for the storage of read flags
 **
 **     toolInit        f  initialize things for the tool
 **     ImVfbAdjust     f  adjust an image - used here to add alpha channels
 **
 **  HISTORY
 **     $Log: imtext.c,v $
 **	Revision 1.2  1995/06/14  20:01:30  bduggan
 **	updated to new flags table / options parsing mechanisms
 **
 **	Revision 1.1  1994/10/03  15:51:09  nadeau
 **	Initial revision
 **
 ** Revision 1,0  93/05/14  14:39:24  shane
 ** Initial revision
 **
 **
 **/

/**
 ** CODE CREDITS
 **
 **	  Custom development, Shane Cooper, San Diego Supercomputer Center, 1993.
 **
 **/

#include "imtools.h"
#include "iminternal.h"

#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
extern ImVfb *ImVfbText();		/* The text function		*/
#else
static void toolInit();
extern ImVfb *ImVfbText();		/* The text function		*/
#endif

/*
 *  GLOBALS
 *      toolCommand             -  tool-specific tool info
 *      toolHelp                -  tool-specific help
 *      toolOptions             -  tool-specific options
 *      toolEquivs              -  tool-specific equivalent keywords
 *
 *  DESCRIPTION
 *      toolCommand describes the command to the arg package.
 *
 *      toolHelp is the tool-specific help for the tool.  It will be
 *      concatenated with the generic image tools help message and
 *      added to the toolCommand structure as the help string to be
 *      printed after the option listing.
 *
 *      toolOptions is the tool-specific option list.  It will be merged
 *      with the generic image tools options, and the list of image file
 *      format names supported by the library.  This larger option list
 *      is then used as the list of options supported by the tool.
 *
 *      toolEquivs is the tool-specific option equivalent keyword list.
 *      It will be merged with the generic image tools equivs.  This large
 *      equivs list is then used as the list of equivs supported by the tool.
 */

static ArgCommand toolCommand =
{
        /* command name */              "imtext",

        /* major version # */           IMTOOLSMAJOR,
        /* minor version # */           IMTOOLSMINOR,
        /* subminor version # */        IMTOOLSSUBMINOR,

        /* -help pre-option list information                            */
"%command allows the user to place text over an image. Certain aspects of\n\
the text may be selected such as color, alpha, and font. The user is allowed\n\
to position the text in the field of the image by giving x and y positions.\n\
",
        /* -help post-option list information                           */
        NULL,                           /* filled in later on           */

        /* -fullhelp pre-option list information                        */
        NULL,                           /* Use same message as for -help*/
        /* -fullhelp post-option list information                       */
        NULL,                           /* filled in later on           */

        ARGFNONE,                       /* No special flags             */
        "[options...] font_filename background_filename outfilename",
        "[options...] font_filename background_filename outfilename",
        "SDSC Image Tools, April 1993.",
        IMTOOLSCOPYRIGHT,
        NULL,                           /* filled in later on           */
        NULL,                           /* filled in later on           */
};

static char *toolHelp = "\n\
Typical Invocations:\n\
	Place the string 'Hello' over an image of a face.\n\
	imtext -message 'Hello' face.rgb final.rgb\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -fontfile and -imagefile specify the font and image files,\n\
    respectively.\n\
\n\
    Output images will be the same size and type as those in the background\n\
    image file.\n\
\n\
    Input and output files may each have different image file formats.\n\
\n\
Coloring:\n\
    The options -red, -green, -blue, and -alpha...\n\
\n\
Positioning:\n\
    -xposition and -yposition give the location in the background image at\n\
    which the upper left-hand corner of the text is to be placed.\n\
    Positions are measured in pixels relative to (0,0) in the upper left-hand\n\
    corner.  Positive X and Y values move the foreground image to the right\n\
    and down.  Negative values left and up.  Position values may move the\n\
    foreground partially (or completely) off the edge of the background image.\n\
\n\
    -xposition and -yposition each default to (0,0) in the background image.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS    10
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
        { "fontfile", "image_filename", "Specify font input file",
          ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

        { "imagefile", "image_filename", "Specify background input image file",
          ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

        { "outfile", "image_filename", "Specify an output image file",
          ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

        { "message", "string", "Specify a text message",
          ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

        { "red", "value", "Red channel%end\
    Specify the value for the red in the background.",
          ARGFNONE, 1, 1, ARGTINT },

        { "green", "value", "Green channel%end\
    Specify the value for the green in the background.",
          ARGFNONE, 1, 1, ARGTINT },

        { "blue", "value", "Blue channel%end\
    Specify the value for the blue in the background.",
          ARGFNONE, 1, 1, ARGTINT },

        { "alpha", "value", "Alpha channel%end\
    Specify the value for the alpha in the background.",
          ARGFNONE, 1, 1, ARGTINT },

        { "xposition", "x", "X position in background%end\
    -xposition and -yposition give the location in the background image at\n\
    which the upper left-hand corner of the text is to be placed.\n\
    Positions are measured in pixels relative to (0,0) in the upper left-hand\n\
    corner.  Positive X and Y values move the foreground image to the right\n\
    and down.  Negative values left and up.  Position values may move the\n\
    foreground partially (or completely) off the edge of the background image.\n\
\n\
    -xposition and -yposition each default to (0,0) in the background image.",
          ARGFNONE, 1, 1, ARGTINT },

        { "yposition", "y", "Y position in background%end\
    -xposition and -yposition give the location in the background image at\n\
    which the upper left-hand corner of the text is to be placed.\n\
    Positions are measured in pixels relative to (0,0) in the upper left-hand\n\
    corner.  Positive X and Y values move the foreground image to the right\n\
    and down.  Negative values left and up.  Position values may move the\n\
    foreground partially (or completely) off the edge of the background image.\n\
\n\
    -xposition and -yposition each default to (0,0) in the background image.",
          ARGFNONE, 1, 1, ARGTINT },
};

#define IM_TOOLNEQUIVS     0
#if IM_TOOLNEQUIVS == 0
static ArgEquiv *toolEquivs;
#else
static ArgEquiv toolEquivs[IM_TOOLNEQUIVS] =
{
};
#endif

/*
 *  GLOBALS
 *      toolFontFilename-  the name of the font input file (could be 'stdin')
 *      toolImageFilename- the name of the image input file (could be 'stdin')
 *      toolOutFilename -  the name of the output file (could be 'stdout')
 *
 *      toolFontFormat  -  the name of the first input file's format
 *      toolImageFormat -  the name of the second input file's format
 *      toolOutFormat   -  the name of the output file's format (could be NULL)
 *
 *      toolFontTable   -  first table for the storage of data read in
 *      toolImageTable  -  second table for the storage of data read in
 *      toolInFlagsTable-  a table for the storage of read flags
 *      toolOutFlagsTable-  a table for the storage of read flags
 *
 *      xPosition       -  x offset of the fg image into the bg
 *      yPosition       -  y offset of the fg image into the bg
 *      xStart          -  starting x position in fg to composite from
 *      yStart          -  starting y position in fg to compostie from
 *      xSize           -  width of the fg to composite
 *      ySize           -  height of the fg to composite
 *
 *  DESCRIPTION
 *      Data held by these variables is used throughout the tool.
 */

static char      toolFontFilename[1024]; 	/* Input file name	*/
static char      toolFontFormat[1024];   	/* Input file's format name */

static char      toolImageFilename[1024]; 	/* Input file name 	*/
static char      toolImageFormat[1024];		/* Input file's format name */

static char      toolOutFilename[1024];		/* Output file name	*/
static char      toolOutFormat[1024];		/* Output file's format name */

static char	  toolMessage[1024];		/* The text message itself */

static TagTable  *toolFontTable;		/* Data tag table	*/
static TagTable  *toolImageTable;		/* Data tag table	*/
static TagTable  *toolOutTable;			/* Data tag table	*/
static TagTable  *toolInFlagsTable;		/* Flags tag table	*/
static TagTable  *toolOutFlagsTable;		/* Flags tag table	*/

static int       xPosition = 0;			/* X offset of fg into bg */
static int       yPosition = 0;			/* Y offset of fg into bg */

static int 	  red = 0;			/* Red value of text 	*/
static int 	  green = 0;			/* Green value of text	*/
static int 	  blue = 0;			/* Blue value of text	*/
static int 	  alpha = 255;			/* Alpha value of text	*/


/*
 *  FUNCTION
 *      main    -  main program
 *
 *  DESCRIPTION
 *      Control things:
 *              -  Initialize things (parse arguments and set up tables).
 *              -  Read in the input image file (put data into data table).
 *		-  Read in the input font file (put data into data table).
 *              -  Put text over image.
 *              -  Write out the output file (get data from data table).
 *      That's about it.
 *
 *  NOTES
 *      This 'main' is pretty much the same for each of the image tools.
 *      Differences between tools include:
 *              -  the input files read in
 *              -  the number of output files written out
 *              -  the actions taken on the data between read and write
 */

#ifdef __STDC__
main( int argc, char *argv[] ) 
#else
main(argc,argv)
	int argc;
	char **argv;
#endif
{
	TagEntry *imageTagEntry;
	TagEntry *outTagEntry;
	ImVfb *imageVfb;
	ImVfb *outVfb;
	int letterCount;
	int nImageVfb;
	int i;
	FILE *fp;


        /*
         *  Initialize things:
         *      -  Prepare the arg parsing data, then parse the command-line.
         *      -  Prepare the flags table based upon command-line args.
         *      -  Determine the file formats for input and output files.
         */
        toolInit( argc, argv );


	/*
	 *  Get the font file 
	 */
        if ( ( fp = fopen( toolFontFilename, "r" ) ) == NULL )
        {
         	fprintf( stderr, "Font file %s not found.\n", toolFontFilename);
		exit( 1 );
        }
        letterCount = ImBDFRead( IMFILEIOFP, NULL, fp, NULL, toolFontTable);


	/*
	 *  Get the image file
	 */
	ImToolsFileRead( toolImageFilename, "rgb", NULL, toolImageTable );


        /*
         *  Check for errors
         *      -  no input images
         */
        nImageVfb = TagTableQNEntry( toolImageTable, "image vfb" );
        if ( nImageVfb == 0 )
        {
                fprintf( stderr, "%s: Image input file contains no images!\n",
                        ImToolsProgram );
                exit( 1 );
        }


	/*
	 *  Superimpose the text
	 *	-  get the input images
	 *	-  convert color
	 *	-  place text on images
	 */
	for ( i = 0; i < nImageVfb; i++ )
	{
        	imageTagEntry = TagTableQDirect( toolImageTable, "image vfb", i );
        	TagEntryQValue( imageTagEntry, &imageVfb );

        	outVfb = ImVfbText( toolFontTable, imageVfb, 
			toolMessage, red, green, blue, alpha, 
			xPosition, yPosition );
	}


	/*
	 *  Write out the final file
	 */
        outTagEntry = TagEntryAlloc( "image vfb", POINTER, &outVfb );
        TagTableAppend( toolOutTable, outTagEntry );
        ImToolsFileWrite( toolOutFilename , toolOutFormat, toolOutFlagsTable,
                toolOutTable );


}


/*
 *  FUNCTION
 *      toolInit        -  initialize things for the tool
 *
 *  DESCRIPTION
 *      The tool's argument parsing data structures are set up to include:
 *              - the full help message (generic help + tool-specific help)
 *              - the full option list (generic options + tool-specific options) 
 *              - the full equivs list (generic equivs + tool-specific equivs)
 *
 *      Command-line arguments are then parsed.  The results are used to
 *      set up the flags table (the generic -out* options).
 *
 *      Input and output file's names and formats are determined from the
 *      command-line arguments.
 *
 */

static void                            /* Returns nothing              */
#ifdef __STDC__
toolInit( int argc, char *argv[] )
#else
toolInit( argc, argv )
        int argc;                       /* Argument count               */
        char *argv[ ];                  /* Argument vector              */
#endif
{
        int         i;                  /* Counter                      */
        int         noccur;             /* Number of option occurrences */
        int         nOpt;               /* Number of options            */
        int         nEquiv;             /* Number of equivalences       */
        ArgOption  *options;            /* Argument options             */
        ArgOption  *options1;           /* Argument options             */
        ArgEquiv   *equivs1;            /* Argument equivalent keywords */
        ArgEquiv   *equivs;             /* Argument equivalent keywords */
        char       *tmp;                /* Temporary string holder      */
        char       *tmpFormat;          /* Tmp format name              */

        /*
         *  Save the name of the program, as invoked.
         */
        ImToolsProgram = argv[0];


        /*
         *  Make a data table to hold the incoming data.
         */
        if ( (toolImageTable = TagTableAlloc( )) == TAGTABLENULL )
        {
                TagPError( ImToolsProgram );
                exit( 1 );
        }
        if ( (toolFontTable = TagTableAlloc( )) == TAGTABLENULL )
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
	tmp = ImToolsMergeHelp (tmp, toolFullHelp);
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
        if ( ArgQNOccur( "xposition" ) != 0 )
                xPosition = ArgQValue( "xposition", 0, 0 )->arg_i;
        if ( ArgQNOccur( "yposition" ) != 0 )
                yPosition = ArgQValue( "yposition", 0, 0 )->arg_i;
        if ( ArgQNOccur( "red" ) != 0 )
                red = ArgQValue( "red", 0, 0 )->arg_i;
        if ( ArgQNOccur( "green" ) != 0 )
                green = ArgQValue( "green", 0, 0 )->arg_i;
        if ( ArgQNOccur( "blue" ) != 0 )
                blue = ArgQValue( "blue", 0, 0 )->arg_i;
        if ( ArgQNOccur( "alpha" ) != 0 )
                alpha = ArgQValue( "alpha", 0, 0 )->arg_i;
	if ( ArgQNOccur( "message" ) !=0 )
		strcpy( toolMessage, ArgQValue( "message", 0, 0 )->arg_s );
	/* FIGURE OUT HOW TO HANDLE INDEX, MONO, HUE, SAT, INT */
 


	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolInFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolInFlagsTable, "image");
	ImToolsGetNameAndFormat ( "image", 0, toolImageFilename, toolImageFormat);

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);

	ImToolsGetNameAndFormat ( "font", 0, toolFontFilename, toolFontFormat);


        /*
         *  Check that the input files are not both stdin.
         */
        if ( strcmp( toolImageFilename, "-" ) == 0 &&
                strcmp( toolFontFilename, "-" ) == 0)
        {
                fprintf( stderr, "%s: -imagefile and -fontfile cannot both be stdin.\n", ImToolsProgram );
                exit( 1 );
        }

}
