/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/impaste.c,v 1.10 1995/06/30 22:20:00 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/impaste.c,v 1.10 1995/06/30 22:20:00 bduggan Exp $"

/**
 **  FILE
 **	impaste.c	-  Paste an image into another image
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	impaste copies an image on top of another image, without regard for
 **	alpha planes.
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
 **	toolBackFilenamev  the name of the background file (could be 'stdin')
 **
 **	toolInFormat	v  the name of the input file's format (could be '\0')
 **	toolOutFormat	v  the name of the output file's format (could be '\0')
 **	toolBackFormat	v  the name of the background file's format (could be..)
 **
 **	toolInTable	v  a table for the storage of data read in
 **	toolBackTable	v  a table for the storage of background data read in
 **	toolInFlagsTable   v  a table for the storage of read flags
 **	toolBackFlagsTable v  a table for the storage of read flags
 **	toolOutFlagsTable  v  a table for the storage of write flags
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
 **	$Log: impaste.c,v $
 **	Revision 1.10  1995/06/30  22:20:00  bduggan
 **	added some casts
 **
 **	Revision 1.9  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.8  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.7  1995/06/15  19:36:29  bduggan
 **	took out some useless vars
 **
 **	Revision 1.6  1995/05/18  00:03:01  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.5  94/10/03  15:49:35  nadeau
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
 **	Revision 1.4  92/11/04  14:00:54  groening
 **	minor problem with centering fixed
 **	
 **	Revision 1.3  92/09/18  15:56:17  vle
 **	Fixed bug that passed bad fields to ImVfbCopy(), which caused
 **	ImVfbCopy() to choke.
 **	
 **	Revision 1.2  92/08/31  17:12:28  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.1  91/10/03  13:19:59  nadeau
 **	Initial revision
 **	
 **
 **/

/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1991.
 **/

#include "imtools.h"



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
	/* command name */		"impaste",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command pastes an input image onto a background image and saves the\n\
result into a new file.  Input, background, and output files may have\n\
different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] infilename backfilename [outfilename]",
	"[options...] infilename backfilename [outfilename]",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Pasting Invocations:\n\
    Paste a logo at (10,20) on a background and save it in a new HDF file:\n\
        %command logo.pix -xpos 10 -ypos 20 back.pix result.hdf\n\
    Paste a logo as before, but modify the background file in place:\n\
        %command logo.pix -xpos 10 -ypos 20 back.pix\n\
\n\
Typical Tiling Invocations:\n\
    Tile a pattern across the whole background:\n\
        %command pat.pix -xpos 0 -ypos 0 -xrepeat 0 -yrepeat 0 back.pix\n\
    Tile a pattern 3 times in X and none in Y starting at (-10,-20):\n\
        %command pat.pix -xrepeat 3 -xpos -10 -ypos -20 back.pix\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose images are to be pasted.\n\
\n\
    -backfile selects the file whose images are to act as backgrounds.\n\
\n\
    -outfile selects the file into which to write the resulting images.\n\
\n\
    The background and output files may be the same file.  If no output file\n\
    is given, the background file is used both as the source for background\n\
    images, and as the destination for completed images.\n\
\n\
Pasting:\n\
    Each image in the input file is pasted onto the corresponding image in\n\
    the background file and output to the output file.  If the background\n\
    file only contains a single image, the same background image is used for\n\
    each paste operation.\n\
\n\
    -xposition and -yposition select the location in the background image at\n\
    which the upper-left corner of the paste image is pasted.  (0,0) is the\n\
    upper-left corner of the background.  Positions outside the background\n\
    are allowed.  Paste images are clipped to the borders of the background\n\
    images.\n\
\n\
    -xposition and -yposition default to a position that centers the pasted\n\
    image within the background image.\n\
\n\
    Input images are converted to the same depth as the background before\n\
    pasting.  Pasting occurs independently of any alpha planes in any image.\n\
\n\
Tiling (Repeating):\n\
    -xrepeat and -yrepeat select the number of times to repeat the input image\n\
    in the X and Y directions.  A value of 0 repeats until the edge of the\n\
    background image is reached.  Both repeat counts default to 1.\n\
\n\
    -xdirection and -ydirection select the repeat direction in X and Y.\n\
    X directions may be 'left' or 'right' (default).  Y directions may be\n\
    'up' or 'down' (default).\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";


#define IM_TOOLNOPTIONS	9
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -%option argument specifies the name of the input (foreground) file. \n\
                                                                             \n\
    The file's format may be specified with the -informat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "backfile", "image_filename", "Specify a background image file name%end\
    -backfile selects the file whose images are to act as backgrounds.\n\
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
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "xposition", "x", "Specify left edge of the paste area%end\
    -xposition and -yposition select the location in the background image at\n\
    which the upper-left corner of the paste image is pasted.  (0,0) is the\n\
    upper-left corner of the background.  Positions outside the background\n\
    are allowed.  Paste images are clipped to the borders of the background\n\
    images.\n\
\n\
    -xposition and -yposition default to a position that centers the pasted\n\
    image within the background image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "yposition", "y", "Specify upper edge of the paste area%end\
    -xposition and -yposition select the location in the background image at\n\
    which the upper-left corner of the paste image is pasted.  (0,0) is the\n\
    upper-left corner of the background.  Positions outside the background\n\
    are allowed.  Paste images are clipped to the borders of the background\n\
    images.\n\
\n\
    -xposition and -yposition default to a position that centers the pasted\n\
    image within the background image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xrepeat", "nx", "Select # of times to repeat in X%end\
    -xrepeat and -yrepeat select the number of times to repeat the input image\n\
    in the X and Y directions.  A value of 0 repeats until the edge of the\n\
    background image is reached.  Both repeat counts default to 1.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "yrepeat", "ny", "Select # of times to repeat in Y%end\
    -xrepeat and -yrepeat select the number of times to repeat the input image\n\
    in the X and Y directions.  A value of 0 repeats until the edge of the\n\
    background image is reached.  Both repeat counts default to 1.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xdirection", "xdir", "Select X repeat direction%end\
    -xdirection and -ydirection select the repeat direction in X and Y.\n\
    X directions may be 'left' or 'right' (default).  Y directions may be\n\
    'up' or 'down' (default).",
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "ydirection", "ydir", "Select Y repeat direction%end\
    -xdirection and -ydirection select the repeat direction in X and Y.\n\
    X directions may be 'left' or 'right' (default).  Y directions may be\n\
    'up' or 'down' (default).",
	  ARGFNONE, 1, 1, ARGTSTRING },
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
 *	toolBackFilename-  the name of the background file (could be 'stdin')
 *	toolOutFilename	-  the name of the output file (could be 'stdout')
 *
 *	toolInFormat	-  the name of the input file's format (could be NULL)
 *	toolBackFormat	-  the name of the background file's format (could be NULL)
 *	toolOutFormat	-  the name of the output file's format (could be NULL)
 *
 *	toolInTable	-  a table for the storage of data read in
 *	toolBackTable	-  a table for the storage of background data read in
 *	toolInFlagsTable-  a table for the storage of read flags
 *	toolBackFlagsTable-a table for the storage of read flags
 *	toolOutFlagsTable -a table for the storage of write flags
 *
 *	toolPosX	-  X image position
 *	toolPosY	-  Y image position
 *	toolCenterX	-  Flag X direction centering
 *	toolCenterY	-  Flag Y direction centering
 *	toolTileX	-  X tile count
 *	toolTileY	-  Y tile count
 *	toolDirX	-  X tile direction
 *	toolDirY	-  Y tile direction
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static char      toolBackFilename[1024];/* Background file name	*/
static char      toolBackFormat[1024];	/* Background file's format name*/

static TagTable *toolInTable;		/* Input Data tag table		*/
static TagTable *toolBackTable;		/* Background data tag table	*/
static TagTable *toolInFlagsTable;	/* Flags tag table		*/
static TagTable *toolBackFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static int	  toolPosX;		/* X Position			*/
static int	  toolPosY;		/* Y Position			*/
static int   toolCenterX;		/* Center in X			*/
static int   toolCenterY;		/* Center in Y			*/
static int	  toolTileX;		/* X Repeats			*/
static int	  toolTileY;		/* Y Repeats			*/

static int	  toolDirX;		/* X Direction			*/
static int	  toolDirY;		/* Y Direction			*/

#define IM_TOOL_DIRLEFT	0
#define IM_TOOL_DIRUP	0
#define IM_TOOL_DIRRIGHT	1
#define IM_TOOL_DIRDOWN	1





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

#define imImageType(f)		((f)&IMVFBIMAGEMASK)
#define imIsImage(f)		(((f)&IMVFBIMAGEMASK) != 0)
#define imSameImageType(f1,f2)	(imImageType(f1) == imImageType(f2))

void
#ifdef __STDC__
main(int argc, char *argv[]) 
#else
main( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[];			/* Argument vector		*/
#endif
{
	int         nInVfb;		/* Number of images in input file*/
	int         nBackVfb;		/* Number of images in background file*/
	int         i;			/* Counter			*/
	int	    rep;		/* Repeat count temp		*/
	int	    nPix;		/* Pixel count temp		*/

	TagEntry   *dataEntry;		/* Entry from data table	*/

	ImVfb      *pasteVfb;		/* Paste image			*/
	ImVfb	   *newVfb;		/* New paste image		*/
	ImVfb      *backVfb;		/* Background image		*/
	ImClt	   *backClt;		/* Background image's CLT	*/
	int	    backFields;		/* Background fields		*/
	int         pasteFields;	/* Paste fields			*/
	int	    copyFields;		/* What fields to copy		*/

	int	    regionW;		/* Region width			*/
	int	    regionH;		/* Region height		*/
	int	    regionX;		/* Region left edge		*/
	int	    regionY;		/* Region top edge		*/
	int	    xrep, yrep;		/* X and Y repeat counters	*/
	int	    nxrep, nyrep;	/* # of X and Y repeats		*/
	int	    x, y;		/* Position counters		*/
	int	    dx, dy;		/* Delta X and Y for tiling	*/
	int	    xat, yat;		/* Where to paste it at		*/

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
	 *  Read in the background file.
	 *	-  Open the file (or stdin) and read data into the data table.
	 */
	ImToolsFileRead( toolBackFilename, toolBackFormat, toolBackFlagsTable,
		toolBackTable );


	/*
	 *  Check for errors
	 *	-  no input images
	 *	-  no background images
	 */
	nInVfb = TagTableQNEntry( toolInTable, "image vfb" );
	if ( nInVfb == 0 )
	{
		fprintf( stderr, "%s: Input file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}
	nBackVfb = TagTableQNEntry( toolBackTable, "image vfb" );
	if ( nBackVfb == 0 )
	{
		fprintf( stderr, "%s: Background file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Prep the background data table.
	 *
	 *  We want one background image for each input image.
	 *	-  if there are multiple input images, but only one background
	 *	   image, duplicate the background image a bunch of times.
	 *	-  if there are more input images than background images, take
	 *	   the last background image and add duplicates of it.
	 *	-  if there are more background images than input images,
	 *	   that's OK.
	 */
	if ( nBackVfb < nInVfb )
	{
		dataEntry = TagTableQDirect( toolBackTable, "image vfb",
			nBackVfb - 1 );
		TagEntryQValue( dataEntry, &backVfb );

		for ( i = nBackVfb; i < nInVfb; i++ )
		{
			backVfb = ImVfbDup( backVfb );
			backClt = ImVfbQClt( backVfb );
			if ( backClt != IMCLTNULL )
				TagTableAppend( toolBackTable,
					TagEntryAlloc( "image clt",
					IM_POINTER_TYPE, &backClt ) );
			TagTableAppend( toolBackTable,
				TagEntryAlloc( "image vfb",
				IM_POINTER_TYPE, &backVfb ) );
		}
		nBackVfb = nInVfb;
	}


	/*
	 *  Paste the images
	 *	-  For each input image, paste it onto the equivalent
	 *	   background image and store the result back in-place in
	 *	   the background data table.
	 */
	for ( i = 0; i < nInVfb; i++ )
	{
		/*
		 *  Get the next input and background images out of the tables.
		 */
		dataEntry = TagTableQDirect( toolInTable, "image vfb", i );
		TagEntryQValue( dataEntry, &pasteVfb );
		dataEntry = TagTableQDirect( toolBackTable, "image vfb", i );
		TagEntryQValue( dataEntry, &backVfb );


		/*
		 *  Compute the region.
		 */
		if ( toolCenterX )
			toolPosX = (ImVfbQWidth( backVfb ) - ImVfbQWidth( pasteVfb )) / 2;
		else if ( toolPosX > ImVfbQWidth( backVfb ) )
		{
			fprintf( stderr, "%s: Paste position is out of bounds for background %d of %d.\n",
				ImToolsProgram, i+1, nInVfb );
			fprintf( stderr, "%s: No paste done.\n",
				ImToolsProgram );
			continue;
		}

		if ( toolCenterY )
			toolPosY = (ImVfbQHeight( backVfb ) - ImVfbQHeight( pasteVfb )) / 2;
		else if ( toolPosY > ImVfbQHeight( backVfb ) )
		{
			fprintf( stderr, "%s: Paste position is out of bounds for background %d of %d.\n",
				ImToolsProgram, i+1, nInVfb );
			fprintf( stderr, "%s: No paste done.\n",
				ImToolsProgram );
			continue;
		}


		regionW = ImVfbQWidth( pasteVfb );
		regionH = ImVfbQHeight( pasteVfb );


		/*
		 *  Make sure we have something in common between the paste
		 *  and background VFBs.  The rule is that the output
		 *  results will have the same fields as the background image.
		 *
		 *  Lots of cases exist here:
		 *	1.  The paste and background VFBs have the same fields.
		 *		-  Leave the paste VFB as is.  The paste
		 *		   operation will use the full field set.
		 *
		 *	2.  The paste and background VFBs have some number
		 *	    of fields in common, but not all in common.
		 *	    Two sub-cases exist:
		 *
		 *		a.  Either or both of the background or paste
		 *		    VFBs have no image fields (rgb, index16,
		 *		    index8, or mono).
		 *			-  Leave the paste VFB as is.  The
		 *			   paste operation will use the
		 *			   intersection of the field set.
		 *
		 *		b.  Both background and paste VFBs have
		 *		    image fields.  Two sub-sub-cases exist:
		 *			i.  They are the same image fields.
		 *				-  Leave the paste VFB as is.
		 *				   The paste operation will use
		 *				   the intersection of the
		 *				   field set.
		 *			ii. They are different.
		 *				-  Convert the paste VFB to
		 *				   the same image field type
		 *				   as the background image.
		 *				   The paste operation will use
		 *				   the intersection of the
		 *				   converted paste image's
		 *				   fields and the background
		 *				   image's fields.
		 *
		 *	3.  The paste and background VFBs have no fields
		 *	    in common.  Two sub-cases exist:
		 *
		 *		a.  Either or both of the background or paste
		 *		    VFBs have no image fields (rgb, index16,
		 *		    index8, or mono).
		 *			-  No paste operation is done.
		 *
		 *		b.  Both background and paste VFBs have
		 *		    image fields, but they are different.
		 *			-  Convert the paste VFB to
		 *			   the same image field type
		 *			   as the background VFB.
		 *			   The paste operation will use
		 *			   the intersection of the
		 *			   converted paste VFB's
		 *			   fields and the background
		 *			   VFB's fields.
		 *
		 *  All of this can be reduced to the following test:
		 *
		 *	if both the background and the paste VFBs contain
		 *		image fields, but they aren't the same fields,
		 *			-  Convert the paste VFB's image field
		 *			   data to the same type as the
		 *			   background VFB.
		 *	else if the two VFBs have nothing in common,
		 *			-  Skip the paste.
		 */
		backFields  = ImVfbQFields( backVfb );
		pasteFields = ImVfbQFields( pasteVfb );
		copyFields  = backFields & pasteFields;

		if ( (imIsImage( backFields) && imIsImage( pasteFields )) &&
			!imSameImageType( backFields, pasteFields ) )
		{
			/*
			 *  Convert to the right VFB image type:
			 *	-  Make a new VFB capable of storing the
			 *	   fields common to background and paste VFBs,
			 *	   plus the image type of the background.
			 *	-  Copy the common fields from the paste VFB
			 *	   into the new VFB.
			 *	-  Convert the paste VFB's image fields into
			 *	   that used by the background and new VFBs.
			 */
			pasteFields = copyFields | imImageType( backFields );
			newVfb = ImVfbAlloc( regionW, regionH, pasteFields );

			if( copyFields != 0 )
			{
				if ( ImVfbCopy( pasteVfb,    /* Copy this VFB*/
					0, 0,		     /* Start at top*/
					regionW, regionH,     /* This much*/
					copyFields,           /* These planes*/
					newVfb,		      /* Into this VFB*/
					0, 0 ) == IMVFBNULL ) /* At the top*/
				{
					ImPError( ImToolsProgram );
					fprintf( stderr, "%s: Couldn't create common paste region for background %d of %d.\n", 
						ImToolsProgram, i+1, nInVfb );
					fprintf( stderr, "%s: No paste done.\n",
						ImToolsProgram );
       	                         	continue;
				}
			}

			copyFields = pasteFields;

			switch ( imImageType( backFields ) )
			{
			case IMVFBMONO:
				ImVfbToMono( pasteVfb, 127, newVfb );
				break;

			case IMVFBINDEX8:
				ImVfbToIndex8( pasteVfb, newVfb );
				break;

			case IMVFBINDEX16:
				ImVfbToIndex16( pasteVfb, newVfb );
				break;

			case IMVFBRGB:
				ImVfbToRgb( pasteVfb, newVfb );
				break;
			}
			ImVfbFree( pasteVfb ); 
			pasteVfb = newVfb;
		}
		else if ( copyFields == 0 )
		{
			/* No fields in common!				*/
			fprintf( stderr, "%s: Paste image %d of %d has no per-pixel info in common with\n",
				ImToolsProgram, i, nInVfb );
			fprintf( stderr, "%s: background image %d of %d.  Pasting would have no effect.\n",
				ImToolsProgram, i, nInVfb );
			fprintf( stderr, "%s: No paste done.\n",
				ImToolsProgram );
			continue;
		}


		/*
		 *  Check the tiling repeat counts:
		 *	-  Compute the maximum repeat count possible.
		 *	-  If a 0 repeat count was given (do as many as
		 *	   possible), use the maximum.
		 *	-  If a given repeat count is greater than the max,
		 *	   use the max.
		 */
		if ( toolDirX == IM_TOOL_DIRRIGHT )
			nPix = ImVfbQWidth( backVfb ) - toolPosX;
		else
			nPix = toolPosX;
		rep = nPix / regionW;
		if ( (nPix % regionW) != 0 )
			++rep;			/* Partial paste	*/
		xrep = toolTileX;
		if ( xrep == 0 || xrep > rep )
			xrep = rep;

		if ( toolDirY == IM_TOOL_DIRDOWN )
			nPix = ImVfbQHeight( backVfb ) - toolPosY;
		else
			nPix = toolPosY;
		rep = nPix / regionH;
		if ( (nPix % regionH) != 0 )
			++rep;			/* Partial paste	*/
		yrep = toolTileY;
		if ( yrep == 0 || yrep > rep )
			yrep = rep;


		if ( ImToolsVerbose )
		{
			if ( xrep == 1 && yrep == 1 )
			{
				fprintf( stderr, "%s: Pasting image %d of %d at (%d,%d)\n",
					ImToolsProgram, i + 1, nInVfb,
					toolPosX, toolPosY );
			}
			else
			{
				fprintf( stderr, "%s: Tiling image %d of %d at (%d,%d)\n",
					ImToolsProgram, i + 1, nInVfb,
					toolPosX, toolPosY );
				fprintf( stderr, "%s: Image is repeated %d times in X and %d times in Y\n",
					ImToolsProgram, xrep, yrep );
				fprintf( stderr, "%s: Tiling progresses ",
					ImToolsProgram );
				if ( toolDirX == IM_TOOL_DIRRIGHT )
					fprintf( stderr, "to the right and " );
				else
					fprintf( stderr, "to the left and " );
				if ( toolDirY == IM_TOOL_DIRDOWN )
					fprintf( stderr, "down\n" );
				else
					fprintf( stderr, "up\n" );
			}
		}


		/*
		 *  Tile!
		 *	-  Walk the tile region, with the direction depending
		 *	   upon that selected by command-line arguments.
		 *	-  For each tile position, clip the region to the
		 *	   edges of the background, and copy the paste image
		 *	   into it.
		 */
		if ( toolDirY == IM_TOOL_DIRDOWN )
			dy = regionH;
		else
			dy = -regionH;
		if ( toolDirX == IM_TOOL_DIRRIGHT )
			dx = regionW;
		else
			dx = -regionW;

		y = toolPosY;
		for ( nyrep = 0; nyrep < yrep; nyrep++, y += dy )
		{
			regionY = 0;
			regionH = ImVfbQHeight( pasteVfb );
			yat = y;
			if ( y < 0 )
			{
				/* Clip top off of image.		*/
				regionY = -y;
				regionH -= regionY;
				regionH -= regionY;
				regionH--;
				yat = 0;
			}

			nPix = ImVfbQHeight( backVfb ) - y;
			if ( regionH > nPix )
			{
				/* Clip bottom off of image.		*/
				regionH = nPix;
			}

			if ( regionH <= 0 )
				break;		/* Nothing more to do*/


			x = toolPosX;
			for ( nxrep = 0; nxrep < xrep; nxrep++, x += dx )
			{
				regionX = 0;
				regionW = ImVfbQWidth( pasteVfb );
				xat = x;
				if ( x < 0 )
				{
					/* Clip left off of image.	*/
					regionX = -x;
					regionW -= regionX;
					regionW -= regionX;
					regionW--;
					xat = 0;
				}

				nPix = ImVfbQWidth( backVfb ) - x;
				if ( regionW > nPix )
					regionW = nPix;

				if ( regionW <= 0 )
					break;	/* Nothing more to do	*/

				if ( (copyFields & IMVFBINDEX8) &&
				     (ImVfbQClt(backVfb)!=IMCLTNULL) || (ImVfbQClt(pasteVfb)!=IMCLTNULL) )
				{  	/* 
					 * Strange things could happen.  
					 * Give the user a warning.
					 */
					fprintf(stderr,
					"%s: Warning: At least one of your images has a color-lookup table.\n",
						ImToolsProgram);
					fprintf(stderr,
					"%s: The background's table will be used to create the resulting image.\n",
						ImToolsProgram);
					fprintf(stderr,
					"%s: To avoid this behavior, convert your background image file into\n",
						ImToolsProgram);
					fprintf(stderr, "%s: an rgb file.\n", ImToolsProgram);
				}
				/*
				 *  Copy the region into the background VFB.
				 */
				if ( ImVfbCopy( pasteVfb,      /* Use this VFB*/
						regionX, regionY,/* Start here*/
						regionW, regionH,  /* This big*/
						copyFields,	  /* This deep*/
						backVfb,      /* Put into this*/
						xat,      	/* Put it here*/
						yat ) == IMVFBNULL )
				{
					if ( xrep == 1 && yrep == 1 )
					{
	                                	ImPError( ImToolsProgram );
                                		fprintf( stderr, "%s: Couldn't paste image %d of %d.\n",
                                        		ImToolsProgram, i + 1, nInVfb );
                                		fprintf( stderr, "%s: No paste done.\n",
                                        		ImToolsProgram );
                                		continue;
					}
					else
					{
	                                	ImPError( ImToolsProgram );
                                		fprintf( stderr, "%s: Couldn't tile image %d of %d.\n",
                                        		ImToolsProgram, i + 1, nInVfb );
                                		fprintf( stderr, "%s: No tiling done.\n",
                                        		ImToolsProgram );
						nyrep = yrep;			
                                		break;

					}
				}
			}
		}
	}


	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolBackTable );


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
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/

	char       *xdir, *ydir;	/* X and Y direction names	*/

	char       *tmp;		/* Temporary string holder	*/


	/*
	 *  Save the name of the program, as invoked.
	 */
	ImToolsProgram = argv[0];


	/*
	 *  Make data tables to hold the data.
	 */
	if ( (toolInTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}
	if ( (toolBackTable = TagTableAlloc( )) == TAGTABLENULL )
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
	nOpt = ImToolsMergeOptions( "back", IM_TOOLNOPTIONS, toolOptions,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options1);
	nOpt = ImToolsMergeOptions( "in", nOpt, options1,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "out", nOpt, options,
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "back", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs1 );
	nEquiv = ImToolsMergeEquivs( "in", nEquiv, equivs1,
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
	 *  Get the image position and tiling selections.
	 */
	toolPosX = toolPosY = 0;
	toolCenterX = toolCenterY = TRUE;
	if ( ArgQNOccur( "xposition" ) != 0 )
	{
		toolPosX = (int) ArgQValue( "xposition", 0, 0 )->arg_i;
		toolCenterX = FALSE;
	}
	if ( ArgQNOccur( "yposition" ) != 0 )
	{
		toolPosY = (int) ArgQValue( "yposition", 0, 0 )->arg_i;
		toolCenterY = FALSE;
	}

	toolTileX = toolTileY = 1;
	if ( ArgQNOccur( "xrepeat" ) != 0 )
		toolTileX = (int) ArgQValue( "xrepeat", 0, 0 )->arg_i;
	if ( ArgQNOccur( "yrepeat" ) != 0 )
		toolTileY = (int) ArgQValue( "yrepeat", 0, 0 )->arg_i;
	if ( toolTileX < 0 || toolTileY < 0 )
	{
		fprintf( stderr, "%s:  tile repeats must be zero or positive\n",
			ImToolsProgram );
		exit( 1 );
	}

	toolDirX = IM_TOOL_DIRRIGHT;
	toolDirY = IM_TOOL_DIRDOWN;
	if ( ArgQNOccur( "xdirection" ) != 0 )
	{
		xdir = ArgQValue( "xdirection", 0, 0 )->arg_s;
		i = strlen( xdir );
		if ( strncmp( xdir, "left", i ) == 0 )
			toolDirX = IM_TOOL_DIRLEFT;
		else if ( strncmp( xdir, "right", i ) == 0 )
			toolDirX = IM_TOOL_DIRRIGHT;
		else
		{
			fprintf( stderr, "%s: X direction must select either 'left' or 'right'\n",
				ImToolsProgram );
			exit( 1 );
		}
	}
	if ( ArgQNOccur( "ydirection" ) != 0 )
	{
		ydir = ArgQValue( "ydirection", 0, 0 )->arg_s;
		i = strlen( ydir );
		if ( strncmp( ydir, "up", i ) == 0 )
			toolDirX = IM_TOOL_DIRUP;
		else if ( strncmp( ydir, "down", i ) == 0 )
			toolDirX = IM_TOOL_DIRDOWN;
		else
		{
			fprintf( stderr, "%s: Y direction must select either 'up' or 'down'\n",
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

	toolBackFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolBackFlagsTable, "back" );
	ImToolsGetNameAndFormat ( "back", 0, toolBackFilename, toolBackFormat);

	if ( ArgQNOccur( "outfile" ) == 0 )
	{
		/* No output filename given.  Use the background file.	*/
		strcpy( toolOutFilename, toolBackFilename );
		strcpy( toolOutFormat,   toolBackFormat );
	}
}
