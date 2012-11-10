/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imcomp.c,v 1.14 1995/06/30 22:17:37 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imcomp.c,v 1.14 1995/06/30 22:17:37 bduggan Exp $"

/**
 **  FILE
 **	imcomp.c	-  Composite two images together 
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imcomp combines two images based upon alpha channel values and a
 **	selected compositing operation.  The result is saved to an output file.
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
 **	toolIn1Filename		v  the name of the first input file (could be 'stdin')
 **	toolIn2Filename		v  the name of the second input file (could be 'stdin')
 **	toolInAlphaFilename	v  the name of the alpha file (could be 'stdin')
 **	toolOutFilename		v  the name of the output file (could be 'stdout')
 **
 **	toolIn1Format		v  the name of the input file's format (could be '\0')
 **	toolIn2Format		v  the name of the input file's format (could be '\0')
 **	toolInAlphaFormat 	v  the name of the alpha file's format
 **	toolOutFormat		v  the name of the output file's format (could be '\0')
 **
 **	toolInTable		v  a table for the storage of data read in
 **	toolIn1FlagsTable	v  a table for the storage of read flags
 **	toolIn2FlagsTable	v  a table for the storage of read flags
 **	toolAlphaFlagsTable	v  a table for the storage of read flags
 **	toolOutFlagsTable	v  a table for the storage of write flags
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imcomp.c,v $
 **	Revision 1.14  1995/06/30  22:17:37  bduggan
 **	added some casts
 **
 **	Revision 1.13  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.12  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.11  1995/06/15  18:56:32  bduggan
 **	took out some useless vars
 **
 **	Revision 1.10  1995/05/17  23:55:25  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.9  1994/10/22  18:44:51  bduggan
 **	Added -inalpha option
 **
 **	Revision 1.8  1994/10/03  15:49:11  nadeau
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
 **	Revision 1.7  93/04/12  11:00:35  shane
 **	Fixed code so it would be standardized.
 **	
 **	Revision 1.6  93/04/06  12:08:39  shane
 **	Repaired an error in the fullhelp. Added a new example.
 **	
 **	Revision 1.5  93/04/06  10:39:52  shane
 **	Added error checking for sizes. Added information to help messages 
 **	reguarding positioning.
 **	
 **	Revision 1.4  93/03/30  12:03:57  shane
 **	Fixed imvfbcomp call to be compatible with new interface.
 **	
 **	Revision 1.3  92/11/18  17:19:08  nadeau
 **	Updated comments, updated help information, rearranged code,
 **	added more error checking, etc.
 **	
 **	Revision 1.2  92/08/31  17:01:36  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.1  92/08/26  12:59:54  groening
 **	Initial revision
 **	
 **/

#include "imtools.h"

/**
 **  CODE CREDITS
 **     Custom development, Chris Groening, San Diego Supercomputer Center, 1992.
 **/




#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
#else
static void toolInit( );                /* Initialize things            */
#endif


/*
 **  GLOBALS
 **	toolCommand		-  tool-specific tool info
 **	toolHelp		-  tool-specific help
 **	toolOptions		-  tool-specific options
 **	toolEquivs		-  tool-specific equivalent keywords
 **
 **  DESCRIPTION
 **	toolCommand describes the command to the arg package.
 **
 **	toolHelp is the tool-specific help for the tool.  It will be
 **	concatenated with the generic image tools help message and
 **	added to the toolCommand structure as the help string to be
 **	printed after the option listing.
 **
 **	toolOptions is the tool-specific option list.  It will be merged
 **	with the generic image tools options, and the list of image file
 **	format names supported by the library.  This larger option list
 **	is then used as the list of options supported by the tool.
 **
 **	toolEquivs is the tool-specific option equivalent keyword list.
 **	It will be merged with the generic image tools equivs.  This large
 **	equivs list is then used as the list of equivs supported by the tool.
 */

static ArgCommand toolCommand =
{
	/* command name */		"imcomp",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command combines two input images together using a digital compositing\n\
operation and alpha channels (coverage masks) on one or both input images.\n\
The resulting composite image is stored to an output file.  Input and output\n\
files may have different image file formats.\n\
",
	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* filled in later on		*/

	ARGFNONE,			/* No special flags		*/
	"[options...] infilename1 infilename2 outfilename",
	"[options...] infilename1 infilename2 outfilename",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
     Composite two Sun rasterfiles using the OVER alogrithm:\n\
        %command inone.ras intwo.ras out.rgb\n\
     Composite just the red field and the ATOP algorithm:\n\
        %command inone.ras intwo.ras -red -atop out.ras\n\
     Composite the saturation and hue fields and the OUTSIDE alogorithm:\n\
        %command inone.ras intwo.ras -saturation -hue -outside out.ras\n\
     Composite two Sun image files, offsetting the foreground to the right:\n\
        %command boat.ras sea.ras -xposition 20 scene.ras\n\
     Composite two Sun image files, only using a part of the foreground:\n\
        %command boat.ras sea.ras -xstart 21 -xsize 50 scene.ras\n\
     Composite against a background, using an Alias mask file for the\n\
     alpha channel:\n\
	%command spaceship.pix stars.rgb out.rgb \\\n\
               -inalphafile mask.pix -inalphamap alpha=grey\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -in1file names the first input file, while -in2file names the second.\n\
    Compositing will combine selected fields in the first file with those\n\
    in the second to produce an output image stored into the file named by\n\
    the -outfile option.  A file containing an alpha channel may be used\n\
    purely for its alpha component with the -inalphafile option.  The alpha \n\
    component of this file will then replace any alpha channel in the first\n\
    input file.  Input, output, and alpha file formats may each be different.\n\
\n\
Compositing:\n\
    -over, -atop, -inside, and -outside, select the compositing algorithm:\n\
\n\
        -over    Place opaque parts of image 1 over image 2.  Default.\n\
                     OutField = In1Field * (In1Alpha/255.0) +\n\
                                In2Field * (1.0 - (In1Alpha/255.0))\n\
\n\
        -atop    Combine opaque parts of image 2 with image 1.\n\
                     OutField = In1Field * (In2Alpha/255.0) +\n\
                                In2Field * (1.0 - (In1Alpha/255.0))\n\
\n\
        -inside  Use image 1 where image 2 is opaque.\n\
                     OutField = In1Field * (In2Alpha/255.0)\n\
\n\
        -outside Use image 1 where image 2 is transparent.\n\
                     OutField = In1Field * (1.0 - (In2Alpha/255.0))\n\
\n\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
\n\
Positioning:\n\
    -xposition, -yposition, -xstart, -ystart, -xsize, -ysize, control\n\
    foreground positioning inside the background:\n\
\n"
"    -xposition x  -yposition y\n\
		Often the user will desire to position the foreground\n\
		somewhere other than the default, which is the upper left\n\
		hand corner of the background. These options allow you to\n\
		do this. The x and y values are measured in pixels, and\n\
		may be either positive or negative. A positive x value will\n\
		move the foreground left by x pixels whereas a negative x\n\
		value will move it right x pixels. This works similarly for\n\
		y, where positive values move the foreground down y pixels\n\
		and a negavtive value will move it up y pixels.\n\
\n\
    -xstart x  -ystart y  -xsize w  -ysize h\n\
		The user may wish to composite only a subregion of the\n\
		foreground. The flags xstart and ystart can be used to\n\
		specify the upper left hand corner of this subregion of the\n\
		foreground image, and xsize and ysize specify the width and\n\
		height repsectively. All values are measured in pixels.\n\
\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type:\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	23
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "in1file", "image_filename", "Specify a first input image file name%end\
    The -in1file argument specifies the name of the first input file.        \n\
    The significance of this file depends on the compositing algorithm used. \n\
                                                                             \n\
    The file's format may be specified with the -in1format flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "in2file", "image_filename", "Specify a second input image file name%end\
    The -in2file argument specifies the name of the second input file.       \n\
    The significance of this file depends on the compositing algorithm used. \n\
                                                                             \n\
    The file's format may be specified with the -in2format flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    The -outfile argument specifies the name of the output file.             \n\
                                                                             \n\
    The file's format may be specified with the -outformat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdout.  When using       \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED | ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "over", NULL, "Use the over algorithm%end\
        The -over option places opaque parts of image 1 over image 2.\n\
	This is the default if no algorithm is selected.            \n\
                     OutField = In1Field * (In1Alpha/255.0) +\n\
                                In2Field * (1.0 - (In1Alpha/255.0))\n\
",
	  ARGFNONE,0,0,ARGTNONE},

	{ "inside", NULL, "Use the inside algorithm%end\
        The -inside option uses image 1 where image 2 is opaque.\n\
                     OutField = In1Field * (In2Alpha/255.0)\n\
",
	  ARGFNONE,0,0,ARGTNONE},

	{ "outside", NULL, "Use the outside algorithm%end\
        The -outside option uses image 1 where image 2 is transparent.\n\
",
	  ARGFNONE,0,0,ARGTNONE},

	{ "atop", NULL, "Use the atop algorithm%end\
        The -atop option combines opaque parts of image 2 with image 1.\n\
                     OutField = In1Field * (In2Alpha/255.0) +\n\
                                In2Field * (1.0 - (In1Alpha/255.0))\n\
",
	  ARGFNONE,0,0,ARGTNONE},

	{ "mono", NULL, "Composite monochrome values%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0,0, ARGTNONE },

	{ "index", NULL, "Composite color indexes%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0,0, ARGTNONE },

	{ "red", NULL, "Composite red channels%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "green", NULL, "Composite green channels%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "blue", NULL, "Composite blue channels%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "hue", NULL, "Composite hues%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "saturation", NULL, "Composite saturations%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "intensity", NULL, "Composite intensities%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "alpha", NULL, "Composite alphas%end\
    By default all fields in the first input image are composited into the\n\
    second.  Alternatively, explicit field compositing may be done by\n\
    listing the desired fields on the command-line:  -red, -green, -blue,\n\
    -mono, -index, -hue, -saturation, -intensity, and -alpha.\n\
",
	  ARGFNONE, 0, 0, ARGTNONE},

	{ "xstart", "x", "Specify starting X within foreground%end\
    The user may wish to composite only a subregion of the\n\
    foreground. The flags xstart and ystart can be used to\n\
    specify the upper left hand corner of this subregion of the\n\
    foreground image, and xsize and ysize specify the width and\n\
    height repsectively. All values are measured in pixels.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ystart", "y", "Specify starting Y within foreground%end\
    The user may wish to composite only a subregion of the\n\
    foreground. The flags xstart and ystart can be used to\n\
    specify the upper left hand corner of this subregion of the\n\
    foreground image, and xsize and ysize specify the width and\n\
    height repsectively. All values are measured in pixels.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xposition", "x", "Specify left edge of composite area%end\
    Often the user will desire to position the foreground\n\
    somewhere other than the default, which is the upper left\n\
    hand corner of the background. The -xposition and -yposition\n\
    options allow you to do this. The x and y values are measured\n\
    in pixels, and may be either positive or negative. A positive x\n\
    value will move the foreground left by x pixels whereas a \n\
    negative x value will move it right x pixels. This works similarly\n\
    for y, where positive values move the foreground down y pixels\n\
    and a negative value will move it up y pixels.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "yposition", "y", "Specify right edge of composite area%end\
    Often the user will desire to position the foreground\n\
    somewhere other than the default, which is the upper left\n\
    hand corner of the background. The -xposition and -yposition\n\
    options allow you to do this. The x and y values are measured\n\
    in pixels, and may be either positive or negative. A positive x\n\
    value will move the foreground left by x pixels whereas a \n\
    negative x value will move it right x pixels. This works similarly\n\
    for y, where positive values move the foreground down y pixels\n\
    and a negative value will move it up y pixels.\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xsize", "width", "Specify width of composite area%end\
    The user may wish to composite only a subregion of the\n\
    foreground. The flags xstart and ystart can be used to\n\
    specify the upper left hand corner of this subregion of the\n\
    foreground image, and xsize and ysize specify the width and\n\
    height repsectively. All values are measured in pixels.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ysize", "height", "Specify height of composite area%end\
    The user may wish to composite only a subregion of the\n\
    foreground. The flags xstart and ystart can be used to\n\
    specify the upper left hand corner of this subregion of the\n\
    foreground image, and xsize and ysize specify the width and\n\
    height repsectively. All values are measured in pixels.\n\
",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "inalphafile", "image_filename", "Specify file name for the alpha channel%end\
   The -inalphafile option allows one to bring in the alpha channel from\n\
   another file and use it as the alpha channel for in1file.  This option can be\n\
   used in conjunction with the -inalphamap option to use any channel of another\n\
   file as the alpha channel for the first input file.\n\
\n\
   For instance,\n\
	%command spaceship.pix stars.rgb out.rgb \\\n\
	       -inalphafile mask.pix -inalphamap alpha=grey\n\
   will composite spaceship.pix against stars.rgb, using an alias mask file's\n\
   greyscale value as the alpha channel of spaceship.pix.\n\
    \n\
   The file's format may be specified with the -inalphaformat flag.         \n\
                                                                             \n\
   A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
   an explicit format name may be necessary.                                 \
",
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

#define IM_NOT_SET -1




/*
 *  GLOBALS
 *	toolIn1Filename	  -  the name of the first input file (could be 'stdin')
 *	toolIn2Filename	  -  the name of the second input file (could be 'stdin')
 *	toolInAlphaFilename- the name of the alpha channel file (could be '\0')
 *	toolOutFilename	   - the name of the output file (could be 'stdout')
 *
 *	toolIn1Format	  -  the name of the first input file's format
 *	toolIn2Format	  -  the name of the second input file's format
 *	toolInAlphaFormat -  the name of the alpha channel file's format (could be '\0')
 *	toolOutFormat	  -  the name of the output file's format (could be NULL)
 *
 *	toolIn1Table	  -  first table for the storage of data read in
 *	toolIn2Table	  -  second table for the storage of data read in
 *	toolOutTable	  -  table storing outgoing data
 *
 *	toolIn1FlagsTable  -  a table for the storage of read flags
 *	toolIn2FlagsTable  -  a table for the storage of read flags
 *	toolInAlphaFlagsTable -  a table for the storage of read flags
 *	toolOutFlagsTable     -  a table for the storage of write flags
 *
 *	toolOperator	  -  compositing operator to use
 *	toolField	  -  compositing fields
 *
 *      xPosition         -  x offset of the fg image into the bg
 *      yPosition         -  y offset of the fg image into the bg
 *      xStart            -  starting x position in fg to composite from
 *      yStart            -  starting y position in fg to compostie from
 *      xSize             -  width of the fg to composite
 *      ySize             -  height of the fg to composite
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolIn1Filename[1024]; /* Input file name		*/
static char      toolIn1Format[1024];	/* Input file's format name	*/

static char      toolIn2Filename[1024]; /* Input file name		*/
static char      toolIn2Format[1024];	/* Input file's format name	*/

static char      toolInAlphaFilename[1024];/* Alpha file name		*/
static char      toolInAlphaFormat[1024];/* Alpha file's format name	*/

static char      toolOutFilename[1024]; /* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static TagTable *toolIn1Table;		/* Data tag table		*/
static TagTable *toolIn2Table;		/* Data tag table		*/
static TagTable *toolOutTable;		/* Data tag table		*/
static TagTable *toolInAlphaTable;	/* Alpha tag table		*/
static TagTable *toolIn1FlagsTable;	/* Flags tag table		*/
static TagTable *toolIn2FlagsTable;	/* Flags tag table		*/
static TagTable *toolInAlphaFlagsTable;	/* Flags tag table		*/
static TagTable *toolOutFlagsTable;	/* Flags tag table		*/

static int	  toolOperator;		/* where to fill in area	*/
static int	  toolField;		/* What fields to change 	*/

static int	  xPosition = 0;	/* x offset of fg into bg */
static int	  yPosition = 0;	/* y offset of fg into bg */
static int	  xStart = 0;		/* x offset to cut into fg */
static int	  yStart = 0;		/* y offset to cut into fg */
static int	  xSize = IM_NOT_SET;	/* x length of cut into fg */
static int	  ySize = IM_NOT_SET;	/* y length of cut into fg */



/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Composite each image.
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
	int         nIn1Vfb;		/* Number of images in file	*/
	int         nIn2Vfb;		/* Number of images in file	*/
	int         nInAVfb;		/* Number of images in file	*/
	int         i;			/* Counter			*/

	TagEntry   *dataOneEntry;	/* Entry from data table	*/
	TagEntry   *dataTwoEntry;	/* Entry from data table	*/
	TagEntry   *dataAlphaEntry;	/* Entry from data table	*/

	ImVfb      *newVfb;		/* Temporary vfb holder         */
	ImVfb      *source2Vfb;		/* Source image			*/
	ImVfb      *source1Vfb;		/* Source image			*/
	ImVfb      *sourceAlphaVfb;	/* Source image			*/
	ImVfb      *vfb;		/* Source image			*/
        TagEntry   *newEntry;           /* Entry from data table        */
        int        nEntry;              /* index into vfb as to where image is*/
	int	   nVfb;		/* how many times to loop 	*/
	int	   fieldMask;		/* Field mask of images		*/
	int	   source1Fields;	/* Source image #1's fields	*/
	int	   source2Fields;	/* Source image #2's fields	*/
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
	ImToolsFileRead( toolIn1Filename, toolIn1Format, toolIn1FlagsTable,
		toolIn1Table );
	ImToolsFileRead( toolIn2Filename, toolIn2Format, toolIn2FlagsTable,
		toolIn2Table );
	if (toolInAlphaFilename[0] != '\0') 
		ImToolsFileRead( toolInAlphaFilename, toolInAlphaFormat, toolInAlphaFlagsTable,
			toolInAlphaTable );


        /*
         *  Check for errors
         *      -  no input images
	 *	-  unequal number of images in two files (except when doing
	 *	   a 1->many composite or a many<-1 composite).
         */
	nIn1Vfb = TagTableQNEntry( toolIn1Table, "image vfb" );
	if ( nIn1Vfb == 0 )
	{
		fprintf( stderr, "%s: First input file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}

	nIn2Vfb = TagTableQNEntry( toolIn2Table, "image vfb" );
	if ( nIn2Vfb == 0 )
	{
		fprintf( stderr, "%s: Second input file contains no images!\n",
			ImToolsProgram );
		exit( 1 );
	}

	if (toolInAlphaFilename[0]!='\0')
	{
		nInAVfb = TagTableQNEntry( toolInAlphaTable, "image vfb" );
		if ( nInAVfb == 0 )
		{
			fprintf( stderr, "%s: Alpha file contains no images!\n",
				ImToolsProgram );
			exit( 1 );
		}
	}
	else nInAVfb = 0;

	if ( nIn1Vfb > nIn2Vfb )
		nVfb = nIn1Vfb;
	else
		nVfb = nIn2Vfb; 
	if (nInAVfb > nVfb)
		nVfb = nInAVfb;

	if ( (nInAVfb > 1 && nInAVfb!=nVfb) ||
	     (nIn1Vfb > 1 && nIn1Vfb!=nVfb) ||
	     (nIn2Vfb > 1 && nIn2Vfb!=nVfb)) 
	{
		fprintf (stderr,"%s: Input files must have the same number of images\n", ImToolsProgram );
		exit( 1 );
	}

	/*
	 *  Composite!
	 *	-  get the input images
	 *	-  convert color indexed images to RGB
	 *	-  composite.
	 */
	for ( i = 0; i < nVfb; i++ )
	{
		/*
		 *  Get the first and second composite images.
		 *  We could be compositing in one of several manners:
		 *
		 *	n to n		There's n images in each file (usually
		 *			just one).  Composite them one at a
		 *			time.
		 *
		 *	1 to n		There's 1 image in the first file
		 *			and n in the second.  Composite the
		 *			1 first image repeatedly with each
		 *			of the n second images.
		 *
		 *	n to 1		There's n images in the first file
		 *			and 1 in the second.  Composite each
		 *			of the n first images with the same
		 *			second image.
		 *
		 *  So, on each pass through this loop, figure out which
		 *  method to use and get the next image as appropriate.
		 * 
		 *  Multiple files can also be specified with the -inalphafile
		 *  option.  There can be either n or 1 of these images.
		 *  The manner for compositing in these cases is analagous to
		 *  that described above.
		 *
		 */
		if ( nIn1Vfb > i )
		{
			dataOneEntry = TagTableQDirect( toolIn1Table,
				"image vfb", i );
			TagEntryQValue( dataOneEntry, &source1Vfb );
		}
		if ( nIn2Vfb > i )
		{
			dataTwoEntry = TagTableQDirect( toolIn2Table,
				"image vfb", i );
			TagEntryQValue( dataTwoEntry, &source2Vfb );
		}
		if ( nInAVfb > i )
		{
			dataAlphaEntry = TagTableQDirect( toolInAlphaTable,
				"image vfb", i );
			TagEntryQValue( dataAlphaEntry, &sourceAlphaVfb );
		}


                if ( ImToolsVerbose )
                        fprintf (stderr, "%s: Compositing image set %d of %d\n",
                                ImToolsProgram, i+1, nVfb );



		/*
		 *  If one of the source images is color indexed, while the
		 *  other is RGB, convert the color indexed image to RGB.
		 */
		source1Fields = ImVfbQFields( source1Vfb );
		source2Fields = ImVfbQFields( source2Vfb );
		if ( (source1Fields & (IMVFBINDEX8 | IMVFBINDEX16)) &&
			(source2Fields & IMVFBRGB) )
		{
			/* First image needs to be promoted to RGB.	*/
			if (ImToolsVerbose)
			{
				fprintf (stderr, "%s: Converting first color index image to RGB.\n",
					ImToolsProgram );
			}
			tmpFields = source1Fields & ~(IMVFBINDEX8|IMVFBINDEX16);
			vfb = ImVfbAlloc( ImVfbQWidth( source1Vfb ),
				ImVfbQHeight( source1Vfb ),
				tmpFields | IMVFBRGB );
			if ( vfb == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot allocate memory for first color index image as RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Copy all non-color index fields to new VFB.	*/
			if ( tmpFields && ImVfbCopy( source1Vfb, 0, 0,
				ImVfbQWidth( vfb ), ImVfbQHeight( vfb ),
				tmpFields, vfb, 0, 0 ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Problem in copying first color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			if ( ImVfbToRgb( source1Vfb, vfb ) == IMVFBNULL )
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
			ImVfbFree( source1Vfb );
			source1Vfb = vfb;
			source1Fields = ImVfbQFields( source1Vfb );
		}
		else if ( (source2Fields & (IMVFBINDEX8 | IMVFBINDEX16)) &&
			(source1Fields & IMVFBRGB) )
		{
			/* Second image needs to be promoted to RGB.	*/
			if (ImToolsVerbose)
			{
				fprintf (stderr, "%s: Converting second color index image to RGB.\n",
					ImToolsProgram );
			}
			tmpFields = source2Fields & ~(IMVFBINDEX8|IMVFBINDEX16);
			vfb = ImVfbAlloc( ImVfbQWidth( source2Vfb ),
				ImVfbQHeight( source2Vfb ),
				tmpFields | IMVFBRGB );
			if ( vfb == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot allocate memory for second color index image as RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Copy all non-color index fields to new VFB.	*/
			if ( tmpFields && ImVfbCopy( source2Vfb, 0, 0,
				ImVfbQWidth( vfb ), ImVfbQHeight( vfb ),
				tmpFields, vfb, 0, 0 ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Problem in copying second color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}
			if ( ImVfbToRgb( source2Vfb, vfb ) == IMVFBNULL )
			{
				fprintf( stderr, "%s: Cannot convert second color index image to RGB.\n", ImToolsProgram );
				ImPError( ImToolsProgram );
				exit( 1 );
			}

			/* Replace in second tag table (will be out table)*/
			nEntry = TagEntryQNthEntry( dataTwoEntry );
			newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
			TagTableReplace( toolIn2Table, nEntry, newEntry );
			ImVfbFree( source2Vfb );
			source2Vfb = vfb;
			source2Fields = ImVfbQFields( source2Vfb );
		}


		/*
		 *  Make sure the alpha channels we need are there
		 *  (unless a seperate alpha file is given).
		 */
		if (nInAVfb == 0)
		{
		switch ( toolOperator )
		{
		case IMCOMPOVER:	/* Requires 1st image have alpha*/
			if ( !(source1Fields & IMVFBALPHA) )
			{
				fprintf( stderr, "%s: The -over option requires that the first image have an alpha channel,\n", ImToolsProgram );
				fprintf( stderr, "%s: yet it doesn't have one.  You may use tools like imfill and\n", ImToolsProgram );
				fprintf( stderr, "%s: imadjust to create alpha channels.\n", ImToolsProgram );
				exit( 1 );
			}
			break;

		case IMCOMPATOP:	/* Requires both have alpha	*/
			if ( !(source1Fields & IMVFBALPHA) )
			{
				fprintf( stderr, "%s: The -atop option requires that the first image have an alpha channel,\n", ImToolsProgram );
				fprintf( stderr, "%s: yet it doesn't have one.  You may use tools like imfill and\n", ImToolsProgram );
				fprintf( stderr, "%s: imadjust to create alpha channels.\n", ImToolsProgram );
				exit( 1 );
			}
			if ( !(source2Fields & IMVFBALPHA) )
			{
				fprintf( stderr, "%s: The -atop option requires that the second image have an alpha channel,\n", ImToolsProgram );
				fprintf( stderr, "%s: yet it doesn't have one.  You may use tools like imfill and\n", ImToolsProgram );
				fprintf( stderr, "%s: imadjust to create alpha channels.\n", ImToolsProgram );
				exit( 1 );
			}
			break;

		case IMCOMPINSIDE:	/* Requires 2nd image have alpha*/
			if ( !(source2Fields & IMVFBALPHA) )
			{
				fprintf( stderr, "%s: The -inside option requires that the second image have an alpha channel,\n", ImToolsProgram );
				fprintf( stderr, "%s: yet it doesn't have one.  You may use tools like imfill and\n", ImToolsProgram );
				fprintf( stderr, "%s: imadjust to create alpha channels.\n", ImToolsProgram );
				exit( 1 );
			}
			break;

		case IMCOMPOUTSIDE:	/* Requires 2nd image have alpha*/
			if ( !(source2Fields & IMVFBALPHA) )
			{
				fprintf( stderr, "%s: The -outside option requires that the second image have an alpha channel,\n", ImToolsProgram );
				fprintf( stderr, "%s: yet it doesn't have one.  You may use tools like imfill and\n", ImToolsProgram );
				fprintf( stderr, "%s: imadjust to create alpha channels.\n", ImToolsProgram );
				exit( 1 );
			}
			break;
		} /* end of switch */
		} /* end of if no alpha file */


		/*
		 *  Confirm our set of fields on which to composite.
		 */
	        if ( toolField == 0 ) 
	        {
			/*
			 *  No explicit field list given.  Composite on all
			 *  fields common to the two images.
			 */
			compField = source1Fields & source2Fields;
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
	        }
		else
		{
			/*
			 *  Make sure the fields listed actually exist in
			 *  both input images.
			 */
			if ( toolField & (IMHUE | IMSATURATION | IMINTENSITY) )
				fieldMask = IMVFBRGB |
					(toolField & ~(IMHUE | IMSATURATION | IMINTENSITY));
			else if ( toolField & (IMRED | IMGREEN | IMBLUE) )
				fieldMask = IMVFBRGB |
					(toolField & ~(IMRED | IMGREEN|IMBLUE));
			else
				fieldMask = toolField;
			if ( (source1Fields & fieldMask) != fieldMask )
			{
				fprintf( stderr, "%s: First input image doesn't have those pixel fields!\n", ImToolsProgram );
				exit( 1 );
			}
			if ( (source2Fields & fieldMask) != fieldMask )
			{
				fprintf( stderr, "%s: Second input image doesn't have those pixel fields!\n", ImToolsProgram );
				exit( 1 );
			}
			compField = toolField;
		}


		/*
		 *  Composite! But, make sure that the width and height of the
		 *  foreground are properly represented for each frame (often
		 *  there is only one frame).
		 */
		
		xSizeThisFrame = xSize;
		ySizeThisFrame = ySize;

		if ( xSizeThisFrame == IM_NOT_SET ) 
			xSizeThisFrame = ImVfbQWidth  ( source1Vfb );
		if ( ySizeThisFrame == IM_NOT_SET ) 
			ySizeThisFrame = ImVfbQHeight ( source1Vfb );

		if ( ImToolsVerbose && xSizeThisFrame < 0 )
			fprintf (stderr,"%s: Negative foreground width will be set to zero. Foreground will be invisible!\n", ImToolsProgram );
		if ( ImToolsVerbose && ySizeThisFrame < 0 )
			fprintf (stderr,"%s: Negative foreground height will be set to zero. Foreground will be invisible!\n", ImToolsProgram );

		if ( ImToolsVerbose && xSizeThisFrame == 0 )
			fprintf (stderr,"%s: Zero foreground width will be cause foreground to be invisible!\n", ImToolsProgram );
		if ( ImToolsVerbose && ySizeThisFrame == 0 )
			fprintf (stderr,"%s: Zero foreground height will be cause foreground to be invisible!\n", ImToolsProgram );

		if (nInAVfb>0)  /* add alpha channel from sourceAlphaVfb to source1Vfb */
		{

			/* Be sure that the alpha vfb has an alpha channel */
			if (!(ImVfbQFields(sourceAlphaVfb) & IMVFBALPHA))
			{
				fprintf(stderr,"%s: files specified with the -inalphafile option must have an alpha channel\n",
					ImToolsProgram);	
				exit(1);
			}
			/* If we don't have an alpha channel, make a new vfb with an alpha channel. */
			if (!(ImVfbQFields(source1Vfb) & IMVFBALPHA))
			{
				newVfb = ImVfbAlloc( ImVfbQWidth( source1Vfb ),
					ImVfbQHeight( source1Vfb ),
					ImVfbQFields(source1Vfb) | IMVFBALPHA );
				if ( newVfb == IMVFBNULL )
				{
				 	ImPError( ImToolsProgram );
					exit( 1 );
				}
				/* Copy source1Vfb into our new vfb */
				ImVfbCopy(source1Vfb, xStart, yStart, xSizeThisFrame, ySizeThisFrame,
					ImVfbQFields(source1Vfb), newVfb, xStart, yStart);
				/*
				 *  Free the original source image.  This will mean
				 *  that the first input file's tag table entry for
				 *  it becomes bogus (points to VFB that isn't there).
				 *  This is OK since we won't be using the first
				 *  tag table's entry again.
				 */
				ImVfbFree( source1Vfb);
				source1Vfb = newVfb;
			}
			ImVfbCopy(sourceAlphaVfb, xStart, yStart, xSizeThisFrame, ySizeThisFrame,
				IMVFBALPHA, source1Vfb,xStart, yStart);
		}
		/* Copy source2Vfb to a safe place in case it is used again (going through the loop) */
		newVfb = ImVfbDup(source2Vfb);
		vfb = ImVfbComp( source1Vfb, xStart, yStart, xSizeThisFrame, 
			ySizeThisFrame, compField, toolOperator, newVfb, 
			xPosition, yPosition);

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
		newEntry = TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb );
		TagTableAppend(toolOutTable, newEntry);
	}
  

	/*
	 *  Write out the output file.
	 *	-  Open the file (or stdout) and write the data in the data
	 *	   table.  Upon failure, remove the bad output file.
	 */
	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolOutTable );

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
	int	    numOps;		/* number ofoperations on command line*/
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
	 *  Make a data table to hold the incoming data.
	 */
	if ( (toolIn1Table = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}

	if ( (toolIn2Table = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}

	if ( (toolInAlphaTable = TagTableAlloc( )) == TAGTABLENULL )
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
	nOpt = ImToolsMergeOptions( "in1", IM_TOOLNOPTIONS, toolOptions,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "in2", nOpt, options,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options1 );
	nOpt = ImToolsMergeOptions( "inalpha", nOpt, options1,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "out", nOpt, options,
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "in1", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs );
	nEquiv = ImToolsMergeEquivs( "in2", nEquiv, equivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs1 );
	nEquiv = ImToolsMergeEquivs( "inalpha", nEquiv, equivs1,
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
	toolOperator = IMCOMPOVER;
	numOps =0;

	/*
	 *  Get the operator information.
	 */
	if (ArgQNOccur ("over")!=0)
	{
		toolOperator = IMCOMPOVER;
		numOps++;
	}

	if (ArgQNOccur ("inside")!=0)
	{
		toolOperator = IMCOMPINSIDE;
		numOps++;
	}

	if (ArgQNOccur ("atop")!=0)
	{
		toolOperator = IMCOMPATOP;
		numOps++;
	}

	if (ArgQNOccur ("outside")!=0)
	{
		toolOperator=IMCOMPOUTSIDE;
		numOps++;
	}

	if ( numOps > 1 )
        {
                fprintf( stderr, "%s: Only one compositing operator is allowed at a time\n", ImToolsProgram );
                exit( 1 );
        }


	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	toolIn1FlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolIn1FlagsTable, "in1");
	ImToolsGetNameAndFormat ( "in1", 0, toolIn1Filename, toolIn1Format);

	toolIn2FlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolIn2FlagsTable, "in2");
	ImToolsGetNameAndFormat ( "in2", 0, toolIn2Filename, toolIn2Format);

	toolInAlphaFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolInAlphaFlagsTable, "inalpha");
	ImToolsGetNameAndFormat ( "inalpha", 0, toolInAlphaFilename, toolInAlphaFormat);

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);


        /*
         *  Check that the input files are not both stdin.
         */
        if ( strcmp( toolIn1Filename, "-" ) == 0 &&
                strcmp( toolIn2Filename, "-" ) == 0)
        {
                fprintf( stderr, "%s: -in1file and -in2file cannot both be stdin.\n",
                        ImToolsProgram );
                exit( 1 );
        }


	/*
	 *  Get the composite fields.
	 */
	toolField = 0;
	if ( ArgQNOccur( "red" ) != 0 )			toolField |= IMRED;
	if ( ArgQNOccur( "green" ) != 0 )		toolField |= IMGREEN;
	if ( ArgQNOccur( "blue" ) != 0 )		toolField |= IMBLUE;
	if ( ArgQNOccur( "alpha" ) != 0 )		toolField |= IMALPHA;
	if ( ArgQNOccur( "index" ) != 0 )		toolField |= IMINDEX8;
	if ( ArgQNOccur( "mono" ) != 0 )		toolField |= IMMONO;
	if ( ArgQNOccur( "hue" ) != 0 )			toolField |= IMHUE;
	if ( ArgQNOccur( "saturation" ) != 0 )		toolField |= IMSATURATION;
	if ( ArgQNOccur( "intensity" ) != 0 )		toolField |= IMINTENSITY;


	if ( toolField & (IMRED | IMGREEN | IMBLUE) )
	{
		if ( (toolField & ~(IMRED | IMGREEN | IMBLUE | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Compositing can only occur in one color space at a time\n", ImToolsProgram );
			fprintf( stderr, "%s: -red, -green, and -blue cannot be mixed with other field options\n", ImToolsProgram );
			exit( 1 );
		}
	}
	else if ( toolField & (IMHUE | IMSATURATION | IMINTENSITY) )
	{
		if ( (toolField & ~(IMHUE | IMSATURATION | IMINTENSITY | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Compositing can only occur in one color space at a time\n", ImToolsProgram );
			fprintf( stderr, "%s: -hue, -saturation, and -intensity cannot be mixed with other\n", ImToolsProgram );
			fprintf( stderr, "%s: field options.\n",ImToolsProgram);
			exit( 1 );
		}
	}
	else if ( toolField & IMMONO )
	{
		if ( (toolField & ~(IMMONO | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Compositing can only occur in one color space at a time\n", ImToolsProgram );
			fprintf( stderr, "%s: -mono cannot be mixed with other field options\n", ImToolsProgram );
			exit( 1 );
		}
	}
	else if ( toolField & IMINDEX8 )
	{
		if ( (toolField & ~(IMINDEX8 | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Compositing can only occur in one color space at a time\n", ImToolsProgram );
			fprintf( stderr, "%s: -index cannot be mixed with other field options\n", ImToolsProgram );
			exit( 1 );
		}
	}
}

