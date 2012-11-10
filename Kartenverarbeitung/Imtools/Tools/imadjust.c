/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imadjust.c,v 1.11 1995/06/30 22:17:12 bduggan Exp $
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


#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imadjust.c,v 1.11 1995/06/30 22:17:12 bduggan Exp $"

/**
 **  FILE
 **	imadjust.c	-  adjust pixel values in an image
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imadjust modifies pixel values in images in an input file, then
 **	writes the resulting images to an output file.  Adjustments are
 **	performed on pixels that match a selection criteria (like all
 **	pixels with red values between 100 and 200).  Adjustments may set,
 **	add, subtract, multiply, and divide a component of the pixel.
 **	The pixel component changed need not be the same as that used in
 **	the selection criteria.
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
 **     $Log: imadjust.c,v $
 **	Revision 1.11  1995/06/30  22:17:12  bduggan
 **	fixed some grammar
 **
 **	Revision 1.10  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.9  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.8  1995/06/15  17:17:55  bduggan
 **	Took out some useless vars
 **
 **	Revision 1.7  1995/05/17  23:53:15  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.6  94/10/03  15:49:05  nadeau
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
 **     Revision 1.5  92/12/01  14:03:49  nadeau
 **     Changed IMEREPLACEFIELD to IMEADJUSTFIELD.
 **     
 **     Revision 1.4  92/09/01  20:13:26  vle
 **     Updated copyright notice.
 **     
 **     Revision 1.3  92/09/01  12:22:22  nadeau
 **     Added more error checks.  Added -mono.  Updated option
 **     descriptions and help information.
 **     
 **     Revision 1.2  92/08/26  13:01:13  groening
 **     minor changes in conjunction with
 **     imvfbadjust.c to make sure those worked
 **     
 **     Revision 1.1  92/08/07  13:03:37  groening
 **     Initial revision
 **     
 **     
 **	
 **
 **/

/**
 **  CODE CREDITS
 **     Custom development, Chris Groening, San Diego Supercomputer Center, 1990.
 **/

#include "imtools.h"

#define	IM_MAXFIELDS	20

#ifdef __STDC__
static void 	toolInit(int argv, char* arc[]);
static void	imValParse( char *option, int i, float maxV, int isKey);
#else
extern void toolInit( );		/* Initialize things		*/
extern void imValParse( );		/* parse after a field		*/
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
	/* command name */		"imadjust",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command adjusts pixel values in images in an input file and stores the\n\
results to an output file.  Input and output files may have different image\n\
file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] infilename [outfilename]",
	"[options...] infilename [outfilename]",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    Set alpha values to 0 (transparent) for all black pixels:\n\
        %command original.pix -intensity 0.0 -set -alpha 0 alpha.pix\n\
    Brighten a dark image by increasing intensity values:\n\
        %command dim.hdf -intensity 0.0-1.0 -add -intensity 0.2 bright.rle\n\
    Desaturate an image prior to recording to video:\n\
        %command vivid.rgb -sat 0.0-1.0 -set -sat 0.0-0.8 video.rgb\n\
    Invert image intensities to create a pseudo-negative effect:\n\
        %command normal.iff -inten 0.0-1.0 -set -inten 1.0-0.0 invert.ras\n\
    Do weird things to colors:\n\
        %command normal.pix -hue 0.0- -add -hue 100.0 weird.pix\n\
        %command normal.pix -red 0-100 -multiply -blue 0.5 weird.pix\n\
        %command normal.pix -sat 0.25-0.75 -set -hue 360.0-0.0 weird.pix\n\
        %command normal.pix -blue 0-100 -sub -inten 0.5-0.7 weird.pix\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose pixels are to be adjusted.  -outfile\n\
    selects the file into which to write the resulting adjusted images.\n\
    If no output file is given, the adjusted images are written back into\n\
    the input file.\n\
\n\
Selecting Pixels to Adjust:\n\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be tested to see if it should\n\
    be adjusted.  Only one of these options may be given at a time.\n\
\n\
Selecting an Operation:\n\
    -add, -subtract, -multiply, -divide, and -set select the operation to\n\
    be performed on the selected pixels.\n\
\n\
Selecting Pixel Components to Adjust:\n\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha options following an operation option (like -set) select the\n\
    component of the selected pixel that is to be changed.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type:\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	16
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -%option argument specifies the name of the file on which the        \n\
    histogram is to be computed.                                             \n\
                                                                             \n\
    The format of the file may be specified with the -informat flag.         \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    The -%option argument specifies the name of the output file.             \n\
                                                                             \n\
    The format of the file may be specified with the -outformat flag.        \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdout.  When using       \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "add", NULL, "Add a value to the pixel%end\
    -add, -subtract, -multiply, -divide, and -set select the operation to\n\
    be performed on the selected pixels.\n\
    \n\
    For instance,\n\
	%command red.rgb out.ras -red 0-100 -add -blue 100\n\
    will add 100 to the blue component of every pixel whose red component is\n\
    between 0 and 100.",
	  ARGFNONE, 0, 0, ARGTNONE},

	{ "subtract", NULL, "Subtract a value from the pixel%end\
    -add, -subtract, -multiply, -divide, and -set select the operation to\n\
     be performed on the selected pixels.\n\
    \n\
    For instance,\n\
	%command red.rgb out.ras -red 0-100 -subtract -blue 100\n\
    will subtract 100 from the blue component of every pixel with a red\n\
    component between 0 and 100.",
	  ARGFNONE, 0, 0, ARGTNONE},

	{ "multiply", NULL, "Multiply the pixel by a value%end\
    -add, -subtract, -multiply, -divide, and -set select the operation to\n\
    be performed on the selected pixels.\n\
    \n\
    For instance,\n\
	%command red.rgb out.ras -red 0-100 -multiply -blue 10\n\
    will multiply the blue component of every pixel by ten, if the red\n\
    component of that pixel is between 0 and 100",
	  ARGFNONE, 0, 0, ARGTNONE},

	{ "divide", NULL, "Divide the pixel by a value%end\
    -add, -subtract, -multiply, -divide, and -set select the operation to\n\
    be performed on the selected pixels.\n\
    \n\
    For instance,\n\
	%command red.rgb out.ras -red 0-100 -divide -blue 10\n\
    will divide the blue component of every pixel by ten, if the red\n\
    component of that pixel is between 0 and 100",
	  ARGFNONE, 0, 0, ARGTNONE},

	{ "set", NULL, "Set the pixel to a value%end\
    -add, -subtract, -multiply, -divide, and -set select the operation to\n\
    be performed on the selected pixels.\n\
    \n\
    For instance,\n\
	%command red.rgb out.ras -red 0-100 -set -blue 10\n\
    will set the blue component to 10 for each pixel with a red component\n\
    between 0 and 100.",
	  ARGFNONE, 0, 0, ARGTNONE },

        { "red", "value_range", "Select on or change red%end\
    Use -%option to select the %option component of each pixel, or to change\n\
    the %option component of each pixel.\n\
    \n\
    For instance,\n\
	%command -%option 10-99 -add -blue 10\n\
    will add 10 to the blue component of every pixel whose %option component is\n\
    between 10 and 99.\n\
	%command -blue 10-99 -add -%option 10\n\
    will add 10 to the %option component of every pixel whose blue component is\n\
    between 10 and 99.",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "green", "value_range", "Select on or change green%end\
    Use -%option to select the %option component of each pixel, or to change\n\
    the %option component of each pixel.\n\
    \n\
    For instance,\n\
	%command -%option 10-99 -add -blue 10\n\
    will add 10 to the blue component of every pixel whose %option component is\n\
    between 10 and 99.\n\
	%command -blue 10-99 -add -%option 10\n\
    will add 10 to the %option component of every pixel whose blue component is\n\
    between 10 and 99.",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "blue", "value_range", "Select on or change blue%end\
    Use -%option to select the %option component of each pixel, or to change\n\
    the %option component of each pixel.\n\
    \n\
    For instance,\n\
	%command -%option 10-99 -add -red 10\n\
    will add 10 to the red component of every pixel whose %option component is\n\
    between 10 and 99.\n\
	%command -blue 10-99 -add -%option 10\n\
    will add 10 to the %option component of every pixel whose red component is\n\
    between 10 and 99.",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "hue", "value_range", "Select on or change hue%end\
    Use -%option to select the %option of each pixel, or to change the %option\n\
    of each pixel.\n\
    \n\
    For instance,\n\
	%command -%option 10-99 -add -red 10\n\
    will add 10 to the red component of every pixel with a hue between 10 and\n\
    and 99.\n\
	%command -blue 10-99 -add -%option 10\n\
    will add 10 to the hue of every pixel with a red component between 10 and\n\
    and 99.\n\
	%command -hue 0.0- add -hue 130 red.rgb out.ras\n\
    will add 130 to the hue of every pixel.  (This will make a red image green.)",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "saturation", "value_range", "Select on or change saturation%end\
    Use -%option to select the %option value of each pixel, or to change\n\
    the %option value of each pixel.\n\
    \n\
    For instance,\n\
        %command vivid.rgb -sat 0.0-1.0 -set -sat 0.0-0.8 video.rgb\n\
    will desaturate an image to prepare it for video recording.",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "intensity", "value_range", "Select on or change intensity%end\
    Use -%option to select the %option value of each pixel, or to change the\n\
    %option value of each pixel.\n\
    \n\
    For instance,\n\
        imadjust dim.hdf -intensity 0.0-1.0 -add -intensity 0.2 bright.rle\n\
    will brighten a dark image.",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "alpha", "value_range", "Select on or change alpha%end\
    Use -%option to select the %option component of each pixel, or to change\n\
    the %option component of each pixel.\n\
    \n\
    For instance,\n\
	%command -%option 10-99 -add -red 10\n\
    will add 10 to the red component of every pixel whose %option component is\n\
    between 10 and 99.\n\
	%command -intensity 0.0 -set -alpha 0 alpha.rgb\n\
    will set the alpha value to 0 for all pixels that are black.\
",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "index", "value_range", "Select on or change index%end\
    Use -%option to select the %option component of each pixel, or to change\n\
    the %option component of each pixel.\n\
    \n\
    For instance,\n\
	%command -intensity 0 -set -index 5\n\
    will set the index value of all the black pixels to 5.\
    ",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

        { "mono", "value_range", "Select on or change mono%end\
    Use -%option to select the %option component of each pixel, or to change\n\
    the %option component of each pixel.",
          ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE},

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
 * 	toolInFlagsTable  -  a table for the storage of read flags
 * 	toolOutFlagsTable -  a table for the storage of write flags
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file format name	*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file format name	*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static TagTable *toolInTable;		/* Data tag table		*/

static int	 toolOperation;		/* What opeation to perform*/
static float	 toolKeyStart;		/* what value to start keying on */
static float	 toolKeyEnd;		/* what value to end keying on */
static int	 toolKeyField;		/* Field to key on		*/
static float	 toolReplaceStart;	/* what value to start replacing with */
static float	 toolReplaceEnd;	/* what value to end replacing with */
static int	 toolReplaceField;	/* Field to replace with	*/

static char	 toolOperationName[10];/* string names used for printing */
static char	 toolKeyName[15];		
static char	 toolReplaceName[15];





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Adjust each image.
 *		-  Replace the data table images with their adjusted images.
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
	int         nInVfb;		/* Number of images in file	*/
	int         i;			/* Counter			*/

	TagEntry   *dataEntry;		/* Entry from data table	*/
	int	 nEntry;

	ImVfb      *sourceVfb;		/* Source image			*/
	ImVfb      *newVfb;		/* New image			*/
	int	   fieldMask;		/* mask of fields in vfb	*/
        TagEntry   *newEntry;           /* Entry from data table        */
	int     replaceTag;		/* Should we replace the tag entry?*/

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
         *      -  Open the file (or stdin) and read data into the data table.
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
                fprintf( stderr, "%s: Input file contains no images!\n",
                        ImToolsProgram );
                exit( 1 );
        }


        /*
         *  Adjust!
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next image out of the data table.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &sourceVfb );
                fieldMask = ImVfbQFields( sourceVfb );


		/*
		 *  Adjust the fields.
		 */
		if ( ImToolsVerbose )
		{
			fprintf( stderr, "%s: Adjusting image %d of %d \n",
					ImToolsProgram, i + 1, nInVfb);
		}


		/*
		 *  If keying or replacing color indexes, make sure we
		 *  have them and make sure we know to key off INDEX16's if
		 *  that's the type of indexing used by the image.
		 *
		 *  There are lots of other combinations worth checking and
		 *  complaining about, but we'll leave that up to
		 *  ImVfbAdjust() and watch its error codes.
		 */
		if ( !(fieldMask&(IMVFBINDEX8|IMVFBINDEX16) ) )
		{
			/*
			 *  Not a color indexed image.  Make sure we are not
			 *  keying or replacing off of color indexes.
			 */
			if ( toolKeyField == IMINDEX8 || toolKeyField == IMINDEX16 )
			{
				fprintf( stderr, "%s: Input image does not use color indexes.\n", ImToolsProgram );
				fprintf( stderr, "%s: This makes it impossible to adjust based on pixel index values.\n", ImToolsProgram );
				exit( 1 );
			}
			if ( toolReplaceField == IMINDEX8 || toolReplaceField == IMINDEX16 )
			{
				fprintf( stderr, "%s: Input image does not use color indexes.\n", ImToolsProgram );
				fprintf( stderr, "%s: This makes it impossible to adjust pixel index values.\n", ImToolsProgram );
				exit( 1 );
			}
		}
		else if ( fieldMask & IMVFBINDEX16 )
		{
			/*
			 *  Is a 16-bit color indexed image.  Make sure we are
			 *  keying or replacing off the right type.
			 */
			if ( toolKeyField == IMINDEX8 )
				toolKeyField = IMINDEX16;
			if ( toolReplaceField == IMINDEX8 )
				toolReplaceField = IMINDEX16;
		}
		else
		{
			/*
			 *  Is a 8-bit color indexed image.  Make sure we are
			 *  keying or replacing off the right type.
			 */
			if ( toolKeyField == IMINDEX16 )
				toolKeyField = IMINDEX8;
			if ( toolReplaceField == IMINDEX16 )
				toolReplaceField = IMINDEX8;
		}


		/*
		 *  Add an alpha channel if needed.
		 */
		replaceTag = FALSE;
		if ( ((toolKeyField == IMALPHA)||(toolReplaceField ==IMALPHA))&&
			!(fieldMask & IMVFBALPHA) )
		{
			/*
			 *  The image doesn't have an alpha channel, but the
			 *  key or replace values want one.  Rather than
			 *  complain to the user, we'll just add an alpha
			 *  channel to the image and initialize it to opaque
			 *  (alpha = 255).
			 */
			newVfb = ImVfbAlloc( ImVfbQWidth( sourceVfb ),
				ImVfbQHeight( sourceVfb ), fieldMask | IMVFBALPHA );
			if ( newVfb == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			ImVfbClear( IMVFBALPHA, 255, newVfb );
			if ( ImVfbCopy( sourceVfb, 0, 0, ImVfbQWidth( sourceVfb ),
				ImVfbQHeight( sourceVfb ),  IMVFBALL, /* fieldMask, */
				newVfb, 0, 0 ) == IMVFBNULL )
			{
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			ImVfbSClt(newVfb,ImVfbQClt(sourceVfb));
			ImVfbFree( sourceVfb );
			sourceVfb = newVfb;
			replaceTag = TRUE;
		}


		if ( ImToolsVerbose )
		{
			fprintf( stderr, "%s: Performing %s operation on",
				ImToolsProgram, toolOperationName );
			fprintf( stderr, " the %s field (%f to %f),\n\t  based on values",
				toolReplaceName, toolReplaceStart, toolReplaceEnd );
			fprintf( stderr, " from the %s field (%f to %f).\n",
				toolKeyName, toolKeyStart, toolKeyEnd );
		}


		/*
		 *  ImVfbAdjust() can safely adjust with the source and
		 *  destination VFB's the same.  This saves us the need to
		 *  allocate a destination VFB.
		 */
		 if ( ImVfbAdjust( sourceVfb, toolKeyField, toolKeyStart,
			toolKeyEnd, toolOperation, toolReplaceField,
			toolReplaceStart, toolReplaceEnd, sourceVfb ) == IMVFBNULL )
		{
			switch ( ImErrNo )
			{
			case IMEKEYFIELD:
				fprintf( stderr, "%s: the input image does not have a %s component to its pixels.\n",
					ImToolsProgram, toolKeyName );
				break;

			case IMEADJUSTFIELD:
				fprintf( stderr, "%s: the input image does not have a %s component to its pixels.\n",
					ImToolsProgram, toolReplaceName );
				break;

			case IMEKEY:
				fprintf( stderr, "%s: pixel value range for -%s selection is out of range\n",
					ImToolsProgram, toolKeyName );
				break;

			case IMEADJUST:
				fprintf( stderr, "%s: pixel value range for -%s -%s adjustment is out of range\n",
					ImToolsProgram, toolOperationName, toolKeyName );
				break;

			case IMEFIELD:
			case IMEOPERATION:
			case IMENOVFB:
			case IMEWIDTH:
			case IMEHEIGHT:
			case IMEMALLOC:
			default:
				ImPError( ImToolsProgram );
				break;
			}
			exit( 1 );
		}

		if ( replaceTag == TRUE )
		{
			nEntry = TagEntryQNthEntry( dataEntry );
			newEntry = TagEntryAlloc ( "image vfb", IM_POINTER_TYPE,
				&sourceVfb );
			TagTableReplace( toolInTable, nEntry, newEntry );
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


#define IM_LOOKFOR(option,field,maxvalue)				\
	for ( i=0; i<ArgQNOccur( option ); i++ )			\
	{								\
		toolNumFields++;					\
		if ( toolKeyField == 0 )				\
		{							\
			toolKeyNum   = ArgQOccurOpt( option, i );	\
			toolKeyField = field;				\
			imValParse( option, i, maxvalue, TRUE );	\
		}							\
		else							\
		{							\
			toolReplaceNum   = ArgQOccurOpt( option, i );	\
			toolReplaceField = field;			\
			imValParse( option, i, maxvalue, FALSE );	\
		}							\
	}

static void				/* Returns nothing		*/
#ifdef __STDC__
toolInit( int argc, char *argv[] )
#else
toolInit( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argument vector		*/
#endif
{
	int	    i;			/* Counter			*/
	int	    temp;		/* Temporary storage holder	*/
	float       temp2;		/* Temporary storage		*/
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	int	    toolNOper;		/* number of operations requested */
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/

	char       *tmp;		/* Temporary string holder	*/

	int	    toolKeyNum, toolReplaceNum; /* temporary holders	*/
	int	    toolNumFields;	/* number of field counter	*/
	char	    tempName[15];	/* temporary string to copy with */




	/*
	 *  Save the name of the program, as invoked.
	 */
	ImToolsProgram = argv[0];


	/*
	 *  Make a data table to hold the incoming data.
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
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolInFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolInFlagsTable, "in");
	ImToolsGetNameAndFormat ( "in", 0, toolInFilename, toolInFormat);

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );

	if (ArgQNOccur ("outfile") == 0)
		{
			/*
			 *  No output file name given.  Use the input file.
			 */
			strcpy( toolOutFilename, toolInFilename );
			strcpy( toolOutFormat,   toolInFormat );
		}
	else
		ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);

	/* Initialize information */
	toolNOper   = 0;
	toolNumFields    = 0;
	toolKeyField     = 0;
	toolReplaceField = 0;

	/*
	 *  Get the adjustment operation.
	 */
	if ( ArgQNOccur( "add" ) !=0)
	{
		toolOperation = IMADD;
		toolNOper++;
		strcpy( toolOperationName, "add" );
	}

	if ( ArgQNOccur( "subtract" ) !=0)
	{
		toolOperation = IMSUBTRACT;
		toolNOper++;
		strcpy( toolOperationName, "subtract" );
	}

	if ( ArgQNOccur( "multiply" ) !=0)
	{
		toolOperation = IMMULTIPLY;
		toolNOper++;
		strcpy( toolOperationName, "multiply" );
	}

	if ( ArgQNOccur( "divide" ) !=0)
	{
		toolOperation = IMDIVIDE;
		toolNOper++;
		strcpy( toolOperationName, "divide" );
	}

	if ( ArgQNOccur( "set" ) !=0)
	{
		toolOperation = IMSET;
		toolNOper++;
		strcpy( toolOperationName, "set" );
	}

	/*
	 *  Make sure we only got one operation.
	 */
	if ( toolNOper!=1 )
	{
		fprintf (stderr, "%s: Only one operation may be given at a time.\n",
			ImToolsProgram);
		exit(1);
	}


	/*
	 *  Get the key and replace information.
	 *	-  the "key" field is the field we select on when deciding
	 *	   if a pixel is a candidate for adjustment.
	 *	-  the "replace" field is the field we adjust.
	 */
	IM_LOOKFOR( "red",        IMRED,         255.0 );
	IM_LOOKFOR( "green",      IMGREEN,       255.0 );
	IM_LOOKFOR( "blue",       IMBLUE,        255.0 );
	IM_LOOKFOR( "alpha",      IMALPHA,       255.0 );
	IM_LOOKFOR( "index",      IMINDEX8,      65535.0 );
	IM_LOOKFOR( "mono",       IMMONO,        1.0 );
	IM_LOOKFOR( "hue",        IMHUE,         360.0 );
	IM_LOOKFOR( "saturation", IMSATURATION,  1.0 );
	IM_LOOKFOR( "intensity",  IMINTENSITY,   1.0 );


	/*
	 *  Make sure we got two options, one each for key and replace.
	 */
	if ( toolNumFields != 2 )
	{
		fprintf( stderr, "%s: One component selection and one component change option are required.\n",
			ImToolsProgram);
		exit(1);
	}


	/*
	 *  Figure out which field is to be keyed on, and which is to be
	 *  replaced.
	 */
	if ( toolKeyNum > toolReplaceNum )
	{
		/*
		 *  They came in the opposite order we thought they were in.
		 *  Swap them.
		 */
		temp = toolReplaceNum;
		toolReplaceNum = toolKeyNum;
		toolKeyNum = temp;

		temp2 = toolReplaceStart;
		toolReplaceStart = toolKeyStart;
		toolKeyStart = temp2;

		temp2 = toolReplaceEnd;
		toolReplaceEnd = toolKeyEnd;
		toolKeyEnd = temp2;

		temp = toolReplaceField;
		toolReplaceField = toolKeyField;
		toolKeyField = temp;

		strcpy( tempName,        toolReplaceName );
		strcpy( toolReplaceName, toolKeyName );
		strcpy( toolKeyName,     tempName );
	}
}





/*
 *  FUNCTION
 *	imValParse	-  get a value range
 *
 *  DESCRIPTION
 *	Take an argument value range and split it up into the key and
 *	replace values depending upon whether 'isKey' is TRUE or FALSE.
 */
static void				/* Returns nothing		*/
#ifdef __STDC__
imValParse( char* option, int i, float maxV, int isKey )
#else
imValParse( option, i, maxV, isKey )
	char      *option;		/* Option name			*/
	int        i;			/* Option occurrence		*/
	float	   maxV;		/* maximum value field can take */
	int	   isKey;		/* Is it a key?  or a replace?	*/
#endif

{
        ArgValue   *value;              /* Argument value               */

	value = ArgQValue( option, i, 0 );
	if ( isKey )
	{
		strcpy( toolKeyName, option );
		switch ( value->arg_rform )
		{
		case ARGRCLOSED:        /* n-m  start and end values    */
			toolKeyStart = (float)(value->arg_fr1);
			toolKeyEnd   = (float)(value->arg_fr2);
			break;

		case ARGROPEN:          /* n-   length only             */
			toolKeyStart = (float)(value->arg_f);
			toolKeyEnd   = maxV;
			break;

		case ARGRSINGLE:        /* n    length only             */
			toolKeyStart = (float)(value->arg_f);
			toolKeyEnd   = (float)(value->arg_f);
			break;
		}
	}
	else
	{
		strcpy( toolReplaceName, option );
		switch ( value->arg_rform )
		{
		case ARGRCLOSED:        /* n-m  start and end values    */
			toolReplaceStart = (float)(value->arg_fr1);
			toolReplaceEnd   = (float)(value->arg_fr2);
			break;

		case ARGROPEN:          /* n-   length only             */
			toolReplaceStart = (float)(value->arg_f);
			toolReplaceEnd   = maxV;
			break;

		case ARGRSINGLE:        /* n    length only             */
			toolReplaceStart = (float)(value->arg_f);
			toolReplaceEnd   = (float)(value->arg_f);
			break;
		}
	}
}
