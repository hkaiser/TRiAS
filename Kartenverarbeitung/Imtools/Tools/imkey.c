/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imkey.c,v 1.7 1995/06/30 22:18:46 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imkey.c,v 1.7 1995/06/30 22:18:46 bduggan Exp $"

/**
 **  FILE
 **	imkey.c		-  Key a foreground image over a background image
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imkey places a foreground image over a background image, letting
 **	the background show through where ever the forground's pixels match
 **	a key color.  The result is saved to an output file.
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
 **	toolFgFilename	v  the name of the foreground file
 **	toolBgFilename	v  the name of the background file
 **	toolOutFilename	v  the name of the output file (could be 'stdout')
 **
 **	toolFgFormat	v  the name of the foreground file's format (could be '\0')
 **	toolBgFormat	v  the name of the background file's format (could be '\0')
 **	toolOutFormat	v  the name of the output file's format (could be '\0')
 **
 **	toolFgTable	v  a table for the storage of data read in
 **	toolBgTable	v  a table for the storage of data read in
 **	toolFgFlagsTable  v  a table for the storage of read flags
 **	toolBgFlagsTable  v  a table for the storage of read flags
 **	toolOutFlagsTable v  a table for the storage of write flags
 **
 **	toolInit	f  initialize things for the tool
 **	imValParse 	f  break down a command line value range into its parts
 **	ImVfbAdjust	f  adjust an image - used here to add alpha channels
 **	ImVfbComp	f  composite two images 
 **
 **  HISTORY
 **     $Log: imkey.c,v $
 **	Revision 1.7  1995/06/30  22:18:46  bduggan
 **	added some casts
 **
 **	Revision 1.6  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.5  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.4  1995/06/15  19:19:51  bduggan
 **	added variable initialization that was causing the whole tool
 **	to not work on suns.
 **
 **	Revision 1.3  1995/05/18  00:02:39  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.2  94/10/03  15:49:31  nadeau
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
 ** Revision 1.1  93/05/14  14:39:24  shane
 ** Initial revision
 ** 
 **	
 **/

/**
 **  CODE CREDITS
 **
 **	  Custom development, Shane Cooper, San Diego Supercomputer Center, 1993.
 **
 **/


#include "im.h"
#include "imtools.h"


#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static void imValParse( char *option,int i, float maxV );
#else
static void imValParse( );              /* Parse argument range values  */
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
	/* command name */		"imkey",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command places a foreground image over a background image, letting the\n\
background show through wherever the foreground's pixels match a key color\n\
specified on the command-line.  The resulting image is stored to an output\n\
file.  Input and output files may have different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] foreground_filename background_filename outfilename",
	"[options...] foreground_filename background_filename outfilename",
	"SDSC Image Tools, April 1993.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    Key a spaceship over a star field by letting the star field show through\n\
    wherever there's a particular set of blues in the spaceship image, such\n\
    as in bluescreen filming:\n\
        %command ship.x stars.x -hue 195-205 ship_and_stars.rgb\n\
\n\
    Key a weather caster on top of a weather map by letting the map show\n\
    through wherever the foreground is green (and hope the weather caster\n\
    isn't wearing any green!):\n\
        %command caster.ras map.rgb -hue 84-140 broadcast.x\n\
\n\
    Key a blue boat on a red background over a picture of an ocean.  Let the\n\
    ocean show through everywhere the boat picture is red:\n\
        %command blueboat.ras ocean.ras -red 255 scene.ras\n\
\n\
    Key one image over another, letting the background show through wherever\n\
    the foreground is dark (intensity less than 0.1):\n\
        %command foreground.rgb background.rgb -intensity 0.0-0.1 result.ras\n\
\n\
    Repeat the spaceship and stars keying above, but offset the spaceship\n\
    position within the background by 20 pixels in X, and 30 in Y:\n\
        %command ship.x -hue 195-205 -xposition 20 -yposition 30 stars.x\n\
          ship_and_stars.rgb\n\
\n\
    Repeat the spaceship and stars keying again, but also select only a\n\
    subregion of the spaceship image to key over the background:\n\
        %command -xstart 10 -ystart 35 -xsize 123 -ysize 201 ship.x\n\
          -hue 195-205 -xposition 20 -yposition 30 stars.x ship_and_stars.rgb\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infgfile and -inbgfile specify the foreground and background image files,\n\
    respectively.  Images in the foreground file will be keyed over those in\n\
    the background file.  Portions of the foreground that match the key colors\n\
    will be treated as transparent and let the background show through.  The\n\
    combined output images are written to the file named by the -outfile\n\
    option.\n\
\n\
    Output images will be the same size and type as those in the background\n\
    image file.  If the foreground image is smaller than the background, all\n\
    pixels 'outside' the foreground image will be considered transparent and\n\
    let the background show through.\n\
\n\
    Input and output files may each have different image file formats.\n\
\n\
Keying:\n\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.\n\
\n\
Positioning:\n\
    -xposition and -yposition give the location in the background image at\n\
    which the upper left-hand corner of the foreground image is to be placed.\n\
    Positions are measured in pixels relative to (0,0) in the upper left-hand\n\
    corner.  Positive X and Y values move the foreground image to the right\n\
    and down.  Negative values left and up.  Position values may move the\n\
    foreground partially (or completely) off the edge of the background image.\n\
\n\
    -xposition and -yposition each default to (0,0) in the background image.\n\
\n"
"Subregions:\n\
    A subregion of the foreground image may be selected using -xstart, -ystart,\n\
    -xsize, and -ysize.  Start values are in pixels measured from (0,0) in the\n\
    upper left-hand corner of the foreground image.  Size values are in pixels.\n\
    Start values must be positive and size values must result in a subregion\n\
    wholely contained within the foreground image.\n\
\n\
    -xstart and -ystart each default to (0,0) in the foreground image.\n\
    -xsize and -ysize each default to the full image width and height from\n\
    the starting location to the edge of the foreground image.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";


#define IM_TOOLNOPTIONS	17
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infgfile", "image_filename", "Specify foreground input image file%end\
    -infgfile gives the name of the foreground image file.\n\
    Use a single dash ('-') as the name of the file if you'd\n\
    like to use stdin.  Use the -infgformat flag to explicitly give\n\
    the format of the foreground file.\n\
    \n\
    -infgfile and -inbgfile specify the foreground and background image files,\n\
    respectively.  Images in the foreground file will be keyed over those in\n\
    the background file.  Portions of the foreground that match the key colors\n\
    will be treated as transparent and let the background show through.  The\n\
    combined output images are written to the file named by the -outfile\n\
    option.",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "inbgfile", "image_filename", "Specify background input image file%end\
    -inbgfile gives the name of the background image file.\n\
    Use a single dash ('-') as the name of the file if you'd\n\
    like to use stdin.  Use the -inbgformat flag to explicitly give\n\
    the format of the background file.\n\
    \n\
    -infgfile and -inbgfile specify the foreground and background image files,\n\
    respectively.  Images in the foreground file will be keyed over those in\n\
    the background file.  Portions of the foreground that match the key colors\n\
    will be treated as transparent and let the background show through.  The\n\
    combined output images are written to the file named by the -outfile\n\
    option.",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file%end\
    -infgfile gives the name of the output image file. Use a single dash \n\
    ('-') as the name of the file if you'd like to use stdout.  Use the \n\
    -outformat flag to explicitly give the format of the output file.\n\
    \n\
    -infgfile and -inbgfile specify the foreground and background image files,\n\
    respectively.  Images in the foreground file will be keyed over those in\n\
    the background file.  Portions of the foreground that match the key colors\n\
    will be treated as transparent and let the background show through.  The\n\
    combined output images are written to the file named by the -outfile\n\
    option.",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "mono", "value_range", "Key on monochrome values%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "index", "value_range", "Key on color indexes%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "red", "value_range", "Key on red channels%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "green", "value_range", "Key on green channels%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "blue", "value_range", "Key on blue channels%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "hue", "value_range", "Key on hues%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "saturation", "value_range", "Key on saturations%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "intensity", "value_range", "Key on intensities%end\
    The options -red, -green, -blue, -mono, -index, -hue, -saturation, and\n\
    -intensity select the key color in the foreground image that is to be\n\
    treated as transparent in order to let the background image show through.\n\
    Each of these options take either a single value, or a numeric range of\n\
    values of the form 'n-m', such as '-green 20-133'.  When a range is given\n\
    all foreground pixels with a color value in that range will be treated as\n\
    transparent.",
	  ARGFMULTIPLE, 1, 1, ARGTFLOAT | ARGTRANGE },

	{ "xstart", "x", "X location of foreground subregion%end\
    A subregion of the foreground image may be selected using -xstart, -ystart,\n\
    -xsize, and -ysize.  Start values are in pixels measured from (0,0) in the\n\
    upper left-hand corner of the foreground image.  Size values are in pixels.\n\
    Start values must be positive and size values must result in a subregion\n\
    wholely contained within the foreground image.\n\
\n\
    -xstart and -ystart each default to (0,0) in the foreground image.\n\
    -xsize and -ysize each default to the full image width and height from\n\
    the starting location to the edge of the foreground image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ystart", "y", "Y location of foreground subregion%end\
    A subregion of the foreground image may be selected using -xstart, -ystart,\n\
    -xsize, and -ysize.  Start values are in pixels measured from (0,0) in the\n\
    upper left-hand corner of the foreground image.  Size values are in pixels.\n\
    Start values must be positive and size values must result in a subregion\n\
    wholely contained within the foreground image.\n\
\n\
    -xstart and -ystart each default to (0,0) in the foreground image.\n\
    -xsize and -ysize each default to the full image width and height from\n\
    the starting location to the edge of the foreground image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xposition", "x", "X position in background%end\
    -xposition and -yposition give the location in the background image at\n\
    which the upper left-hand corner of the foreground image is to be placed.\n\
    Positions are measured in pixels relative to (0,0) in the upper left-hand\n\
    corner.  Positive X and Y values move the foreground image to the right\n\
    and down.  Negative values left and up.  Position values may move the\n\
    foreground partially (or completely) off the edge of the background image.\n\
    \n\
    -xposition and -yposition each default to (0,0) in the background image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "yposition", "y", "Y position in background%end\
    -xposition and -yposition give the location in the background image at\n\
    which the upper left-hand corner of the foreground image is to be placed.\n\
    Positions are measured in pixels relative to (0,0) in the upper left-hand\n\
    corner.  Positive X and Y values move the foreground image to the right\n\
    and down.  Negative values left and up.  Position values may move the\n\
    foreground partially (or completely) off the edge of the background image.\n\
\n\
    -xposition and -yposition each default to (0,0) in the background image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xsize", "width", "Width of foreground subregion%end\
    A subregion of the foreground image may be selected using -xstart, -ystart,\n\
    -xsize, and -ysize.  Start values are in pixels measured from (0,0) in the\n\
    upper left-hand corner of the foreground image.  Size values are in pixels.\n\
    Start values must be positive and size values must result in a subregion\n\
    wholely contained within the foreground image.\n\
\n\
    -xstart and -ystart each default to (0,0) in the foreground image.\n\
    -xsize and -ysize each default to the full image width and height from\n\
    the starting location to the edge of the foreground image.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ysize", "height", "Height of foreground subregion%end\
    A subregion of the foreground image may be selected using -xstart, -ystart,\n\
    -xsize, and -ysize.  Start values are in pixels measured from (0,0) in the\n\
    upper left-hand corner of the foreground image.  Size values are in pixels.\n\
    Start values must be positive and size values must result in a subregion\n\
    wholely contained within the foreground image.\n\
\n\
    -xstart and -ystart each default to (0,0) in the foreground image.\n\
    -xsize and -ysize each default to the full image width and height from\n\
    the starting location to the edge of the foreground image.",
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


#define IM_NOT_SET -1




/*
 *  GLOBALS
 *	toolFgFilename	-  the name of the fg input file (could be 'stdin')
 *	toolBgFilename	-  the name of the bg input file (could be 'stdin')
 *	toolOutFilename	-  the name of the output file (could be 'stdout')
 *
 *	toolFgFormat	-  the name of the first input file's format
 *	toolBgFormat	-  the name of the second input file's format
 *	toolOutFormat	-  the name of the output file's format (could be NULL)
 *
 *	toolFgTable	-  first table for the storage of data read in
 *	toolBgTable	-  second table for the storage of data read in
 *	toolFgFlagsTable -  a table for the storage of read flags
 *	toolBgFlagsTable -  a table for the storage of read flags
 *	toolOutFlagsTable-  a table for the storage of write flags
 *
 *      xPosition       -  x offset of the fg image into the bg
 *      yPosition       -  y offset of the fg image into the bg
 *      xStart          -  starting x position in fg to composite from
 *      yStart          -  starting y position in fg to compostie from
 *      xSize           -  width of the fg to composite
 *      ySize           -  height of the fg to composite
 *
 *	toolKeyField	-  the field of the ikmage to key off of
 *	toolKeyStart	-  the starting range of this key
 *	toolKeyEnd	-  the ending range of this key
 *	toolKeyName	-  the char string name of a key
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolFgFilename[1024];	/* Input file name		*/
static char      toolFgFormat[1024];	/* Input file's format name	*/

static char      toolBgFilename[1024];	/* Input file name		*/
static char      toolBgFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable  *toolFgTable;		/* Data tag table		*/
static TagTable  *toolBgTable;		/* Data tag table		*/

static TagTable  *toolFgFlagsTable;	/* Flags tag table		*/
static TagTable  *toolBgFlagsTable;	/* Flags tag table		*/
static TagTable  *toolOutFlagsTable;	/* Flags tag table		*/

static int       toolKeyField;         /* Field to key on              */
static float     toolKeyStart;         /* What value to start keying on*/
static float     toolKeyEnd;           /* What value to end keying on 	*/
static char	  toolKeyName[15];	/* Name of a key 		*/

static int	  xPosition = 0;	/* X offset of fg into bg 	*/
static int	  yPosition = 0;	/* Y offset of fg into bg 	*/
static int	  xStart = 0;		/* X offset to cut into fg 	*/
static int	  yStart = 0;		/* Y offset to cut into fg 	*/
static int	  xSize = IM_NOT_SET;	/* X length of cut into fg 	*/ 
static int	  ySize = IM_NOT_SET;	/* Y length of cut into fg 	*/




/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Key each image.
 *		-  Replace the data table images with the results.
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
	int         nFgVfb;		/* Number of images in file	*/
	int         nBgVfb;		/* Number of images in file	*/
	int         i;			/* Counter			*/

	TagEntry   *dataOneEntry;	/* Entry from data table	*/
	TagEntry   *dataTwoEntry;	/* Entry from data table	*/

	ImVfb      *sourceBgVfb;	/* Source image			*/
	ImVfb      *sourceFgVfb;	/* Source image			*/
	ImVfb      *sourceFgVfbNew;	/* Source image adjusted	*/
	ImVfb      *vfb;		/* Source image			*/
        TagEntry   *newEntry;           /* Entry from data table        */
        int        nEntry;              /* index into vfb as to where image is*/
	int	   nVfb;		/* how many times to loop 	*/
	int	   sourceFgFields;	/* Source image #1's fields	*/
	int	   sourceBgFields;	/* Source image #2's fields	*/
	int	   tmpFields;		/* Temporary field mask holder	*/
	int	   compField;		/* Fields to composite on	*/
	int 	   xSizeThisFrame;	/* xSize for one frame		*/
	int 	   ySizeThisFrame;	/* ySize for one frame		*/

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
         *  Read in the input files.
         *      -  Open the files (or stdin) and read data into the data tables.
         */
	ImToolsFileRead( toolFgFilename, toolFgFormat, toolFgFlagsTable,
		toolFgTable );
	ImToolsFileRead( toolBgFilename, toolBgFormat, toolBgFlagsTable,
		toolBgTable );


        /*
         *  Check for errors
         *      -  no input images
	 *	-  unequal number of images in two files (except when doing
	 *	   a 1->many composite or a many<-1 composite).
         */
	nFgVfb = TagTableQNEntry( toolFgTable, "image vfb" );
	if ( nFgVfb == 0 )
	{
		fprintf( stderr, "%s: Foreground input file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}

	nBgVfb = TagTableQNEntry( toolBgTable, "image vfb" );
	if ( nBgVfb == 0 )
	{
		fprintf( stderr, "%s: Background input file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}

        if ( (nFgVfb != nBgVfb) && (nFgVfb > 1) && (nBgVfb > 1) )
        {
		fprintf (stderr,"%s: Foreground and background files must have the same number of images\n", ImToolsProgram );
		exit( 1 );
        }


	/*
	 *  Key!
	 *	-  get the input images
	 *	-  convert color indexed images to RGB
	 *	-  do the keying.
	 */
	if ( nFgVfb > nBgVfb )
		nVfb = nFgVfb;
	else
		nVfb = nBgVfb; 
	for ( i = 0; i < nVfb; i++ )
	{
		/*
		 *  Get the first and second composite images.
		 *  We could be compositing in one of several manners:
		 *
		 *	n to n		There's n images in each file (usually
		 *			just one).  Key them one at a
		 *			time.
		 *
		 *	1 to n		There's 1 image in the first file
		 *			and n in the second.  Key the
		 *			1 first image repeatedly with each
		 *			of the n second images.
		 *
		 *	n to 1		There's n images in the first file
		 *			and 1 in the second.  Key each
		 *			of the n first images with the same
		 *			second image.
		 *
		 *  So, on each pass through this loop, figure out which
		 *  method to use and get the next image as appropriate.
		 */
		if ( nFgVfb > i )
		{
			dataOneEntry = TagTableQDirect( toolFgTable,
				"image vfb", i );
			TagEntryQValue( dataOneEntry, &sourceFgVfb );
		}
		if ( nBgVfb > i )
		{
			dataTwoEntry = TagTableQDirect( toolBgTable,
				"image vfb", i );
			TagEntryQValue( dataTwoEntry, &sourceBgVfb );
		}


                if ( ImToolsVerbose )
                        fprintf (stderr, "%s: Keying image set %d of %d\n",
                                ImToolsProgram, i+1, nVfb );



		/*
		 *  If one of the source images is color indexed, while the
		 *  other is RGB, convert the color indexed image to RGB.
		 */
		sourceFgFields = ImVfbQFields( sourceFgVfb );
		sourceBgFields = ImVfbQFields( sourceBgVfb );
		if ( (sourceFgFields & (IMVFBINDEX8 | IMVFBINDEX16)) &&
			(sourceBgFields & IMVFBRGB) )
		{
			/* First image needs to be promoted to RGB.	*/
			if (ImToolsVerbose)
			{
				fprintf (stderr, "%s: Converting first color index image to RGB.\n",
					ImToolsProgram );
			}
			tmpFields = sourceFgFields & ~(IMVFBINDEX8|IMVFBINDEX16);
			vfb = ImVfbAlloc( ImVfbQWidth( sourceFgVfb ),
				ImVfbQHeight( sourceFgVfb ),
				tmpFields | IMVFBRGB );
			if ( vfb == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot allocate memory for first color index image as RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Copy all non-color index fields to new VFB.	*/
			if ( tmpFields && ImVfbCopy( sourceFgVfb, 0, 0,
				ImVfbQWidth( vfb ), ImVfbQHeight( vfb ),
				tmpFields, vfb, 0, 0 ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Problem in copying first color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			if ( ImVfbToRgb( sourceFgVfb, vfb ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot convert first color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/*
			 *  Free the original source image.  This will mean
			 *  that the first input file's tag table entry for
			 *  it becomes bogus (points to VFB that isn't there).
			 *  This is OK since we won't be using the first
			 *  tag table's entry again.
			 */
			ImVfbFree( sourceFgVfb );
			sourceFgVfb = vfb;
			sourceFgFields = ImVfbQFields( sourceFgVfb );
		}
		else if ( (sourceBgFields & (IMVFBINDEX8 | IMVFBINDEX16)) &&
			(sourceFgFields & IMVFBRGB) )
		{
			/* Second image needs to be promoted to RGB.	*/
			if (ImToolsVerbose)
			{
				fprintf (stderr, "%s: Converting second color index image to RGB.\n",
					ImToolsProgram );
			}
			tmpFields = sourceBgFields & ~(IMVFBINDEX8|IMVFBINDEX16);
			vfb = ImVfbAlloc( ImVfbQWidth( sourceBgVfb ),
				ImVfbQHeight( sourceBgVfb ),
				tmpFields | IMVFBRGB );
			if ( vfb == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot allocate memory for second color index image as RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Copy all non-color index fields to new VFB.	*/
			if ( tmpFields && ImVfbCopy( sourceBgVfb, 0, 0,
				ImVfbQWidth( vfb ), ImVfbQHeight( vfb ),
				tmpFields, vfb, 0, 0 ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Problem in copying second color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			if ( ImVfbToRgb( sourceBgVfb, vfb ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot convert second color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Replace in second tag table (will be out table)*/
			nEntry = TagEntryQNthEntry( dataTwoEntry );
			newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
			TagTableReplace( toolBgTable, nEntry, newEntry );
			ImVfbFree( sourceBgVfb );
			sourceBgVfb = vfb;
			sourceBgFields = ImVfbQFields( sourceBgVfb );
		}



		/*
		 *  Confirm our set of fields on which to key. This
		 *  should be all fields common between the two images.
		 */
		compField = sourceFgFields & sourceBgFields;
		if ( compField == 0 )
		{
			fprintf( stderr, "%s: Input images share no common pixel fields on which to composite!\n", ImToolsProgram );
			exit( 1 );
		}

		/*
		 *  Expand IMVFBRGB to IMRED | IMGREEN | IMBLUE
		 */
		if ( compField & IMVFBRGB )
			compField = (compField & ~IMVFBRGB) | IMRED | IMGREEN | IMBLUE;


		/*
		 *  Key! But, make sure that the width and height of the
		 *  foreground are properly represented for each frame (often
		 *  there is only one frame).
		 */
		
		xSizeThisFrame = xSize;
		ySizeThisFrame = ySize;

		if ( xSizeThisFrame == IM_NOT_SET ) 
			xSizeThisFrame = ImVfbQWidth  ( sourceFgVfb );
		if ( ySizeThisFrame == IM_NOT_SET ) 
			ySizeThisFrame = ImVfbQHeight ( sourceFgVfb );

		if ( ImToolsVerbose && xSizeThisFrame < 0 )
			fprintf (stderr,"%s: Negative foreground width will be set to zero. Foreground will be invisible!\n", ImToolsProgram );
		if ( ImToolsVerbose && ySizeThisFrame < 0 )
			fprintf (stderr,"%s: Negative foreground height will be set to zero. Foreground will be invisible!\n", ImToolsProgram );

		if ( ImToolsVerbose && xSizeThisFrame == 0 )
			fprintf (stderr,"%s: Zero foreground width will be cause foreground to be invisible!\n", ImToolsProgram );
		if ( ImToolsVerbose && ySizeThisFrame == 0 )
			fprintf (stderr,"%s: Zero foreground height will be cause foreground to be invisible!\n", ImToolsProgram );


		/*
		 *  Allocate space for the new foreground, copy the old one
		 *  into it, and set its alpha channel as opaque.
		 */

		if ( ImToolsVerbose ) 
			fprintf(stderr,"%s: Creating new foreground image.\n",ImToolsProgram);

		sourceFgVfbNew = ImVfbAlloc( ImVfbQWidth( sourceFgVfb ),
			ImVfbQHeight( sourceFgVfb ), 
			ImVfbQFields( sourceFgVfb ) | IMALPHA );
		ImVfbCopy( sourceFgVfb, 0, 0, ImVfbQWidth( sourceFgVfb),
			ImVfbQHeight( sourceFgVfb ), IMVFBALL, 
			sourceFgVfbNew, 0, 0 );
		ImVfbClear( IMVFBALPHA, 255, sourceFgVfbNew );


		/*  
		 *  Do the actual keying here. This consists of using
		 *  using ImVfbAdjust and ImVfbComp.
		 */

		ImVfbAdjust( sourceFgVfbNew, toolKeyField, toolKeyStart, 
			toolKeyEnd, IMSET, IMALPHA, 0.0, 0.0, 
			sourceFgVfbNew );

		if ( sourceFgVfbNew == IMVFBNULL ) 
		{
                        ImPError( ImToolsProgram );
			fprintf( stderr,"%s: ImVfbAdjust destroyed foreground image %d of %d\n",
				ImToolsProgram, i + 1, nVfb );
                        continue;
		}


		if ( ImToolsVerbose ) 
			fprintf( stderr,"%s: Compositing foreground to background.\n",ImToolsProgram );

		vfb = ImVfbComp( sourceFgVfbNew, xStart, yStart, 
			xSizeThisFrame, ySizeThisFrame, compField, IMCOMPOVER, 
			sourceBgVfb, xPosition, yPosition);

                if ( vfb == IMVFBNULL )
                {
                        ImPError( ImToolsProgram );
                        fprintf( stderr, "%s: Couldn't composite image set %d of %d.\n",
                                ImToolsProgram, i + 1, nVfb );
                        fprintf( stderr, "%s: Untouched second image copied to output file.\n",
                                ImToolsProgram );
                        continue;
                }


		/*
		 *  Replace the second image in its data table.  We'll be
		 *  using this table when we write the output file.
		 */
		nEntry = TagEntryQNthEntry( dataTwoEntry );
		newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
		TagTableReplace( toolBgTable, nEntry, newEntry );
	}
  

	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolBgTable );

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
 */

#define IM_LOOKFOR(option,field,maxvalue)                               \
        for ( i=0; i<ArgQNOccur( option ); i++ )                        \
        {                                                               \
                toolNumFields++;                                        \
                if ( toolKeyField == 0 )                                \
                {                                                       \
                        toolKeyField = field;                           \
                        imValParse( option, i, maxvalue );		\
                }                                                       \
        }

static void                             /* Returns nothing              */
#ifdef __STDC__
toolInit( int argc, char *argv[] )
#else
toolInit( argc, argv )
        int argc;                       /* Argument count               */
        char *argv[ ];                  /* Argument vector              */
#endif

{
	int	    i;			/* Counter			*/
	int         nOpt;		/* Number of options		*/
	int         nEquiv;		/* Number of equivalences	*/
	ArgOption  *options1;		/* Argument options		*/
	ArgOption  *options;		/* Argument options		*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/

	char       *tmp;		/* Temporary string holder	*/
	int	   toolNumFields;	/* number of field counter 	*/


	/*
	 *  Save the name of the program, as invoked.
	 */
	ImToolsProgram = argv[0];


	/*
	 *  Make a data table to hold the incomming data.
	 */
	if ( (toolFgTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}

	if ( (toolBgTable = TagTableAlloc( )) == TAGTABLENULL )
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
	nOpt = ImToolsMergeOptions( "infg", IM_TOOLNOPTIONS, toolOptions,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options1 );
	nOpt = ImToolsMergeOptions( "inbg", nOpt, options1,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "out", nOpt, options,
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "infg", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs1 );
	nEquiv = ImToolsMergeEquivs( "inbg", nEquiv, equivs1,
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

	if ( ArgQNOccur( "verbose" ) != 0 )
		ImToolsVerbose = TRUE;
	if ( ArgQNOccur( "xposition" ) != 0 )
		xPosition = (int) ArgQValue( "xposition", 0, 0 )->arg_i;
	if ( ArgQNOccur( "yposition" ) != 0 )
		yPosition = (int) ArgQValue( "yposition", 0, 0 )->arg_i;
	if ( ArgQNOccur( "xstart" ) != 0 )
		xStart = (int) ArgQValue( "xstart", 0, 0 )->arg_i;
	if ( ArgQNOccur( "ystart" ) != 0 )
		yStart = (int) ArgQValue( "ystart", 0, 0 )->arg_i;
	if ( ArgQNOccur( "xsize" ) != 0 )
		xSize = (int) ArgQValue( "xsize", 0, 0 )->arg_i;
	if ( ArgQNOccur( "ysize" ) != 0 )
		ySize = (int) ArgQValue( "ysize", 0, 0 )->arg_i;



	/* Initialize information */
	toolKeyField = 0;



	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolFgFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolFgFlagsTable, "infg");
	ImToolsGetNameAndFormat ( "infg", 0, toolFgFilename, toolFgFormat);

	toolBgFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolBgFlagsTable, "inbg");
	ImToolsGetNameAndFormat ( "inbg", 0, toolBgFilename, toolBgFormat);

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);


        /*
         *  Get the key and replace information.
         *      -  the "key" field is the field we select on when deciding
         *         if a pixel is a candidate for adjustment.
         *      -  the "replace" field is the field we adjust.
         */
	toolNumFields = 0;
        IM_LOOKFOR( "red",        IMRED,         255.0 );
        IM_LOOKFOR( "green",      IMGREEN,       255.0 );
        IM_LOOKFOR( "blue",       IMBLUE,        255.0 );
        IM_LOOKFOR( "index",      IMINDEX8,      65535.0 );
        IM_LOOKFOR( "mono",       IMMONO,        1.0 );
        IM_LOOKFOR( "hue",        IMHUE,         360.0 );
        IM_LOOKFOR( "saturation", IMSATURATION,  1.0 );
        IM_LOOKFOR( "intensity",  IMINTENSITY,   1.0 );


        /*
         *  Make sure we got one option for key.
         */
        if ( toolNumFields != 1 )
        {
                fprintf( stderr, "%s: One component selection required.\n",
                        ImToolsProgram);
                exit(1);
        }


        /*
         *  Check that the input files are not both stdin.
         */
        if ( strcmp( toolFgFilename, "-" ) == 0 &&
                strcmp( toolBgFilename, "-" ) == 0)
        {
                fprintf( stderr, "%s: -fgfile and -bgfile cannot both be stdin.\n",
                        ImToolsProgram );
                exit( 1 );
        }


}



/*
 *  FUNCTION
 *      imValParse      -  get a value range
 *
 *  DESCRIPTION
 *      Take an argument value range and split it up into the key and
 *      replace values depending upon whether 'isKey' is TRUE or FALSE.
 */
static void                             /* Returns nothing              */
#ifdef __STDC__
imValParse( char *option,int i, float maxV )
#else
imValParse( option,i, maxV )
        char	*option;              /* Option name                  */
	int  	i;
        float 	maxV;                /* maximum value field can take */
#endif
{
        ArgValue   *value;              /* Argument value               */

        value = ArgQValue( option, i, 0 );
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

