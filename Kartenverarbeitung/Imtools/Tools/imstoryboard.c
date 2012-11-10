/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imstoryboard.c,v 1.27 1995/06/30 22:21:05 bduggan Exp $
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

#define HEADER  "$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imstoryboard.c,v 1.27 1995/06/30 22:21:05 bduggan Exp $"

/**
 **  FILE
 **	imstoryboard.c	-  Storyboard images
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	An image tool to create a storyboard, or grid, of images from a given
 **	set of images.
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
 **	toolPreOptHelp	v  tool-specific help
 **	toolHelp	v  tool-specific help
 **	toolOptions	v  tool-specific options
 **	toolEquivs	v  tool-specific equivalent keywords
 **
 **	toolInFilenames	v  the name of the input files
 **	toolInFormats	v  the name of the input files' format
 **	toolInTable	v  a table for the storage of data read in
 **	toolInFlagsTable  v  a table for the storage of read flags
 **	toolOutFlagsTable v  a table for the storage of write flags
 **
 **	toolOutFilename	v  the name of the output file
 **	toolOutFormat	v  the name of the output file's format
 **
 **	toolBackFilenamev  the name of the background file
 **	toolBackFormat	v  the name of the background file's format
 **	toolBackTable	v  stores the data read in for the background image
 **
 **	toolFrameStart	v  start value for a range of frames
 **	toolFrameEnd	v  end value for a range of frames
 **
 **	toolField	v  bit mask specifying background fill parameters
 **	toolFieldStart	v  start value for a range of color for a fill
 **	toolFieldEnd	v  end value for a range of color for a fill
 **
 **	toolGraduate	v  how to fill area of background image
 **
 **	toolXSize	v  horiz. size of generated output background image
 **	toolYSize	v  vert. size of generated output background image
 **
 **	toolPreRead	v  flag indicating whether or not to pre-read files
 **
 **	toolInit	f  parse args, check user input data, and init globals
 **	toolValParse	f  get argument range values from command line
 **	toolPromoteRgb	f  converts any image to RGB format.  Rtrns a new VFB.
 **	toolDemoteRgb	f  converts an image from RGB back to it's native fmt.
 **	toolScaleVfb	f  resize any image type (imscale in a func)
 **	toolClearTable	f  Frees all data and nodes, and allocs a new tag table
 **
 **	IM_BACK_FILL	m  fill a color for the background image
 **	IM_GET_POS_INT_ARG
 **                     m  get a positive int argument from the command line
 **	IM_GET_NAT_INT_ARG
 **			m  get a "> 0" int argument from the command line
 **
 **  HISTORY
 **	$Log: imstoryboard.c,v $
 **	Revision 1.27  1995/06/30  22:21:05  bduggan
 **	added some casts
 **
 **	Revision 1.26  1995/06/29  01:08:59  bduggan
 **	took out a NODEF
 **
 **	Revision 1.25  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.24  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.23  1995/06/29  00:35:16  bduggan
 **	took out some unused vars
 **
 **	Revision 1.22  1995/05/18  00:04:59  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.21  1995/01/11  00:04:49  bduggan
 **	Added -preread option
 **
 **	Revision 1.20  1994/10/22  18:46:12  bduggan
 **	fixed bug with multiple-image files
 **
 **	Revision 1.19  1994/10/04  20:39:46  bduggan
 **	Fixed bug with ico and cur formats (wasn't promoting correctly)
 **
 **	Revision 1.18  1994/08/31  17:44:13  nadeau
 **	Updated to ANSI C compatibility.
 **
 **	Revision 1.17  1994/06/27  17:01:36  secoskyj
 **	Bug Fixes:
 **	  - With more than one %d -frame entries, counts all frames instead
 **	    of just frames from first %d entry
 **	  - +1 on malloc for toolPreOptHelp for '\0'
 **	  - Spelling error ysrame to yframe
 **	  - toolClearTable uses parameter now instead of toolInTable (global)
 **
 **	Revision 1.16  94/06/27  15:36:32  secoskyj
 **	Ansification, private -> static and boolean -> int
 **	
 **	Revision 1.15  93/04/09  17:39:19  secoskyj
 **	Fixed bug where images were entering copy conditional
 **	multiple times when it should only follow that program
 **	branch fewer times.
 **	
 **	Revision 1.14  93/04/06  18:36:16  secoskyj
 **	Fixed bug where both input images and background
 **	images were coming from stdin.
 **	Removed xcenter and ycenter options
 **	
 **	Revision 1.13  93/02/18  21:33:56  secoskyj
 **	Bug fixes: -cols to -columns, cannot specify scale and frame sizes,
 **	cannot specify -scale and -x or y scale at same time.  More fullhelp
 **	examples.  
 **	
 **	Revision 1.12  93/02/15  21:20:32  secoskyj
 **	Bug Fix version (first 10 bugs).  Bugs fixes: changed handling of multi
 **	image input files, no zero frame size, -scale option added, corrects
 **	bug of frame size being used as output image size.
 **	Misc message and comment changes.
 **	
 **	Revision 1.11  93/02/05  16:12:31  secoskyj
 **	touch up fixes from first few minor bugs.
 **	
 **	
 **	Revision 1.10  93/01/23  20:01:29  secoskyj
 **	Now will read files with %d and paste them in storyboard
 **	Fixed a few other bugs and comment messages.
 **	See 930122.ppp (/users/vis/secoskyj/Workspace/P3) for more
 **	information on bugs fixed.
 **	
 **	Revision 1.9  93/01/21  17:51:04  secoskyj
 **	Test version used with code review with Dave.
 **	Many fixes and additions (too numerous to mention
 **	here)
 **	
 **	Revision 1.8  93/01/12  22:36:56  secoskyj
 **	Several misc. cleanups from last version.  Most of changes in messages
 **	output to screen and to bugs found during script file testing.
 **	
 **	Revision 1.7  93/01/08  13:18:50  secoskyj
 **	Checkin after migration to Auspex
 **	Just checking to make sure check in and 
 **	out works.
 **	
 **	> Revision 1.6  93/01/09  23:10:00  secoskyj
 **	> No revision 1.6.  Lost in migration to Auspex.
 **	> Weird things happened with first check out
 **	> and check in tests.  This revision notice
 **	> manually entered by secoskyj.
 **
 **	Revision 1.5  92/12/16  15:23:12  secoskyj
 **	Now reliably calculates data for formatting
 **	images for the storyboard.  Some bugs in the
 **	file handling and deciding how to construct
 **	certain default values.  This version is
 **	one step about the last checked in version.
 **	
 **	Revision 1.4  92/12/13  22:10:03  secoskyj
 **	Added ability to read multiple image files from the
 **	CLI and the ability to construct a background image
 **	based on parameters from the CLI.  Early version
 **	of imstoryboard.
 **	
 **	Revision 1.3  92/11/25  09:58:10  secoskyj
 **	Added $Log rcs macro
 **	
 **/


/**
 **  CODE CREDITS
 **     Custom development, Jason Secosky, San Diego Supercomputer Center, 1992.
 **/



#include <math.h>			/* ceil, abs			*/
#include <unistd.h>
#include <malloc.h>
#include "imtools.h"

/* These are taken from unistd.h on the sgi.  They aren't in every */
/* architecture's unstd.h.                                         */
#ifndef F_OK
#define R_OK    004     /* Test for Read permission */
#define W_OK    002     /* Test for Write permission */
#define X_OK    001     /* Test for eXecute permission */
#define F_OK    000     /* Test for existence of File */
#endif


#ifdef __STDC__
static void toolInit( int argc, char *argv[] );
static void toolValParse( char *option, float maxV );
static ImVfb *toolPromoteRgb( ImVfb *srcVfb );
static ImVfb * toolDemoteRgb( ImVfb *srcVfb, int dstFields );
static ImVfb * toolScaleVfb( ImVfb *srcVfb, int xsize, int ysize );
static void toolClearTable( TagTable **clrTable );
#else
static void toolInit( );		/* Init globals from user ins	*/
static void toolValParse( );		/* Parse argument range values	*/
static ImVfb *toolPromoteRgb ( );	/* Convert an img to RGB	*/
static ImVfb *toolDemoteRgb ( );	/* Convert img back to orig fmt	*/
static ImVfb *toolScaleVfb( );		/* Identical to imscale		*/
static void toolClearTable( );		/* Clear (free) an entire table	*/
#endif




/*
 *  GLOBALS
 *	toolCommand		-  tool-specific tool info
 *	toolPreOptHelp		-  tool-specific help
 *	toolHelp		-  tool-specific help
 *	toolOptions		-  tool-specific options
 *	toolEquivs		-  tool-specific equivalent keywords
 *
 *  DESCRIPTION
 *	toolCommand	messaging informatoin passed globally to arg. parsing
 *			package.
 *
 *	toolPreOptHelp	help message to be output before argument options
 *			for tool.
 *
 *	toolHelp 	is the tool-specific help for the tool.  It will be
 *			concatenated with the generic image tools help message
 *			and added to the toolCommand structure as the help
 *			string to be printed after the option listing.
 *
 *	toolOptions	is the tool-specific option list.  It will be merged
 *			with the generic image tools options, and the list of
 *			image file format names supported by the library.
 *			This larger option list is then used as the list of
 *			options supported by the tool.
 *
 *	toolEquivs	is the tool-specific option equivalent keyword list.
 *			It will be merged with the generic image tools equivs.
 *			This large equivs list is then used as the list of
 *			equivs supported by the tool.
 */


static ArgCommand toolCommand =
{
	"imstoryboard",		/* command name			*/

	IMTOOLSMAJOR,		/* major version #		*/
	IMTOOLSMINOR,		/* minor version #		*/
	IMTOOLSSUBMINOR,	/* subminor version #		*/

	NULL,			/* -help pre-option list info	*/
	NULL,			/* -help post-option list info	*/
	NULL,			/* -fullhelp pre-option info	*/
	NULL,			/* -fullhelp post-option info	*/
	ARGFNONE,		/* don't output help msg on err	*/

	"[options...] infilename(s) outfilename",
	"[options...] infilename(s) outfilename",
	"SDSC Image Tools, January 1993.",
	IMTOOLSCOPYRIGHT,

	NULL,			/* registration info string	*/
	NULL			/* feedback info string		*/
};

static char *toolPreOptHelp = "\
%command creates a storyboard, or grid, of images on top of a background\n\
image.  The resulting image is saved into a new file.  Input, background,\n\
and output files may have different image file formats.  All distances\n\
below are in pixels.\n\
";

static char *toolHelp = "\n\
Typical Invocations:\n\
    Storyboard four images on a background and save it in a new HDF file:\n\
	%command sdsc.pix boris.gif brs.rgb im52.rgb result.hdf\n\
\n\
    Storyboard the same four images scaled 50%:\n\
	%command sdsc.pix boris.gif brs.rgb im52.rgb result.hdf\n\
	    -xscale 0.5 -yscale 0.5\n\
\n\
    Storyboard the same four images on a graduated red background:\n\
	%command sdsc.pix boris.gif brs.rgb im52.rgb -graduate vertical\n\
	    -red 255-0 result.hdf\n\
\n\
    Storyboard the same four images on a background RGB file:\n\
	%command sdsc.pix boris.gif brs.rgb im52.rgb -backfile backimg.rgb\n\
	    -outfile result.hdf\n\
\n\
    Storyboard two images with a left and right margin of 30 pixels\n\
	%command house.gif garage.gif -xmargin 30 result.rgb\n\
\n\
    Storyboard two images with a grid frame height of 100 pixels and a \n\
    grid frame width of 200 pixels\n\
	%command stereoL.rgb stereoR.rgb -xframe 200 -yframe 100 result.rle\n\
\n\
    Storyboard four images in one column\n\
	%command sdsc.pix boris.gif brs.rgb im52.rgb -columns 1 result.hdf\n\
";

static char *toolFullHelp = "\n\
File options:\n\
    -infile selects the files to be included in the storyboard.\n\
\n\
    When listing input files explicitly, each input file name is given on\n\
    the command line.\n\
\n\
    Input files may be listed implicitly by giving a file name template with\n\
    an embedded %d (ala printf) where the frame number should be placed.\n\
    The -frames argument then gives a range of frame numbers to use for\n\
    input file names.\n\
\n\
    -backfile selects the file to be the background image of the storyboard.\n\
\n\
    -outfile selects the file to write the storyboard out to.  \n\
\n\
Background image generation options:\n\
    If a backfile is not explicitly given, then %command will generate\n\
    one for you.  The following options are used to specify the type of\n\
    background.  An error will result if a backfile and background image\n\
    options are both given.\n\
\n\
    -xsize and -ysize select the size of the background image and the size\n\
    of the output image used for the storyboard.  Defaults to size needed\n\
    to fit all of images onto storyboard (dynamic size).  If a background\n\
    image is given, via -backfile option, then the background image will be\n\
    scaled to the xsize and ysize settings.\n\
\n\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.\n\
\n\
    -graduate selects in what direction to compute a graduated fill (a ramp)\n\
    when a range of fill values are given to -red, -green, etc.:\n\
        none        Do not graduate.  Use the first value only.\n\
        horizontal  Graduate varying pixel values left to right.  Default.\n\
        vertical    Graduate varying pixel values top to bottom.\n\
\n\
Storyboard layout options:\n\
    -rows and -columns selects the number of rows and columns to make up the\n\
    storyboard.  Defaults to the most square output image possible based\n\
    on the number of input files.\n\
\n"
"    -xframe and -yframe selects the width and height of the frames that\n\
    make up the storyboard.  Defaults to the size of the first input image\n\
    if the background image size is not known (-xsize or -ysize defaulted).\n\
    If the background size is known, then partitions all space left over \n\
    for the frames after giving space to the margins and gutters.\n\
\n\
    -xmargin and -ymargin selects the size of the left and right, and top\n\
    and bottom margins.  Defaults to 10% of the frame size.  (i.e. xmargin\n\
    will default to 10% of the x frame size.)\n\
\n\
    -xgutter and -ygutter selects the width and height between images of\n\
    the storyboard.  Defaults to 10% of the frame size.  (i.e. ygutter\n\
    will default to 10% of the y frame size.)\n\
\n\
    -xscale and -yscale select what multiple of the input frame size to make\n\
    the actual frame size.  This option will only be effective if the\n\
    background size is unknown.  Defaults to 1.0.\n\
\n\
    -scale sets both the -xscale and -yscale to the same value.  -scale\n\
    cannot be used in conjunction with -xscale and -yscale.\n\
    Defaults to 1.0 if -xscale or -yscale not specified.\n\
\n\
    -preread reads each of the files an extra time before placing images on \n\
    the storyboard.  Using this option will make the tool take twice as long \n\
    to run, but will enable storyboarding of multiple images within a single \n\
    file.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    including information about file formats supported, type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";


#define IM_TOOLNOPTIONS	28
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	/*
	 *  File management CLI
	 */

	{ "infile", "image_filenames", "Specify input image file names%end\
    -infile selects the files to be included in the storyboard.\n\
\n\
    When listing input files explicitly, each input file name is given on\n\
    the command line.\n\
\n\
    Input files may be listed implicitly by giving a file name template with\n\
    an embedded %d (ala printf) where the frame number should be placed.\n\
    The -frames argument then gives a range of frame numbers to use for\n\
    input file names.\n\
    \n\
    A single dash ('-') signifies stdin as an input file.\n\
    \n\
    Use the -informat flag to specify the format of the input file.",
	  ARGFREQUIRED|ARGFMULTIPLE|ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "frames", "range", "Specify frame numbers of input files%end\
    The -frames argument gives a range of frame numbers to use for\n\
    input file names, when one of the input file names contains a %d.",
	  ARGFNONE , 1, 1, ARGTINT | ARGTRANGE },

	{ "backfile", "image_filename", "Specify a background image file name%end\
    -backfile selects the file to be the background image of the storyboard.",
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "outfile", "image_filename", "Specify an output image file name%end\
    The -%option argument specifies the name of the output file.             \n\
                                                                             \n\
    The file's format may be specified with the -outformat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdout.  When using       \n\
    stdout, an explicit format name is necessary.                             \
",
	  ARGFREQUIRED, 1, 1, ARGTSTRING },


	/*
	 *  Fill image management CLI
	 */

	{ "graduate", "direction", "Select direction for backgrnd gradation%end\
    The -graduate option is used to select the direction for filling a background\n\
    image.  It should be used in conjunction with an option that uses a range of\n\
    values.  e.g. -red 0-255 -graduate vertical will create a background screen\n\
    with a vertical red ramp.\n\
    \n\
        none        Do not graduate.  Use the first value only.\n\
        horizontal  Graduate varying pixel values left to right.  Default.\n\
        vertical    Graduate varying pixel values top to bottom.",
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "xsize", "width", "Specify width of background fill area%end\
    -xsize and -ysize select the size of the background image and the size\n\
    of the output image used for the storyboard.  Defaults to size needed\n\
    to fit all of images onto storyboard (dynamic size).  If a background\n\
    image is given, via -backfile option, then the background image will be\n\
    scaled to the xsize and ysize settings.",
	  ARGFNONE, 1, 1, ARGTINT},

	{ "ysize", "height", "Specify height of background fill area%end\
    -xsize and -ysize select the size of the background image and the size\n\
    of the output image used for the storyboard.  Defaults to size needed\n\
    to fit all of images onto storyboard (dynamic size).  If a background\n\
    image is given, via -backfile option, then the background image will be\n\
    scaled to the xsize and ysize settings.",
	  ARGFNONE, 1, 1, ARGTINT},

	{ "index", "value_range", "Background fill color index%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "mono", "value_range", "Background fill monochrome%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "red", "value_range", "Background fill red%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "green", "value_range", "Background fill green%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "blue", "value_range", "Background fill blue%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "hue", "value_range", "Background fill hue%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "saturation", "value_range", "Background fill saturation%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "intensity", "value_range", "Background fill intensity%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},

	{ "alpha", "value_range", "Background fill alpha%end\
    -red, -green, -blue, -mono, -index, -hue, -saturation, -intensity, and\n\
    -alpha select the component of each pixel to be filled and the value or\n\
    range (gradation) of values with which to fill.",
	  ARGFNONE, 1, 1, ARGTFLOAT | ARGTRANGE},


	/*
	 *  Storyboard layout CLI
	 */

	{ "rows", "number_rows", "Specify number of rows for storyboard%end\
    -rows and -columns selects the number of rows and columns to make up the\n\
    storyboard.  Defaults to the most square output image possible based\n\
    on the number of input files.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "columns", "number_cols", "Specify number of columns for storyboard%end\
    -rows and -columns selects the number of rows and columns to make up the\n\
    storyboard.  Defaults to the most square output image possible based\n\
    on the number of input files.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xframe", "frame_width", "Select storyboard frame width%end\
    -xframe and -yframe selects the width and height of the frames that\n\
    make up the storyboard.  Defaults to the size of the first input image\n\
    if the background image size is not known (-xsize or -ysize defaulted).\n\
    If the background size is known, then partitions all space left over \n\
    for the frames after giving space to the margins and gutters.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "yframe", "frame_height", "Select storyboard frame height%end\
    -xframe and -yframe selects the width and height of the frames that\n\
    make up the storyboard.  Defaults to the size of the first input image\n\
    if the background image size is not known (-xsize or -ysize defaulted).\n\
    If the background size is known, then partitions all space left over \n\
    for the frames after giving space to the margins and gutters.",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xgutter", "gutter_width", "Select gutter width between frames%end\
    -xgutter and -ygutter selects the width and height between images of\n\
    the storyboard.  Defaults to 10% of the frame size.  (i.e. ygutter\n\
    will default to 10% of the y frame size.)",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ygutter", "gutter_height", "Select gutter height between frames%end\
    -xgutter and -ygutter selects the width and height between images of\n\
    the storyboard.  Defaults to 10% of the frame size.  (i.e. ygutter\n\
    will default to 10% of the y frame size.)",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "xmargin", "margin_width", "Select margin width%end\
    -xmargin and -ymargin selects the size of the left and right, and top\n\
    and bottom margins.  Defaults to 10% of the frame size.  (i.e. xmargin\n\
    will default to 10% of the x frame size.)",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "ymargin", "margin_height", "Select margin height%end\
    -xmargin and -ymargin selects the size of the left and right, and top\n\
    and bottom margins.  Defaults to 10% of the frame size.  (i.e. xmargin\n\
    will default to 10% of the x frame size.)",
	  ARGFNONE, 1, 1, ARGTINT },

	{ "scale", "scale_value", "Select scale value for both axes%end\
    -xscale and -yscale select what multiple of the input frame size to make\n\
    the actual frame size.  This option will only be effective if the\n\
    background size is unknown.  Defaults to 1.0.\n\
\n\
    -scale sets both the -xscale and -yscale to the same value.  -scale\n\
    cannot be used in conjunction with -xscale and -yscale.\n\
    Defaults to 1.0 if -xscale or -yscale not specified.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "xscale", "width_scale", "Select scale value for frame width%end\
    -xscale and -yscale select what multiple of the input frame size to make\n\
    the actual frame size.  This option will only be effective if the\n\
    background size is unknown.  Defaults to 1.0.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "yscale", "height_scale", "Select scale value for frame height%end\
    -xscale and -yscale select what multiple of the input frame size to make\n\
    the actual frame size.  This option will only be effective if the\n\
    background size is unknown.  Defaults to 1.0.",
	  ARGFNONE, 1, 1, ARGTFLOAT },

	{ "preread", NULL, "Allow for reading of multi-image files%end\
    -preread reads each of the files an extra time before placing images on \n\
    the storyboard.  Using this option will make the tool take twice as long \n\
    to run, but will enable storyboarding of multiple images within a single \n\
    file.",
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
 *	toolInFilenames	-  the name of the input files
 *	toolInFormats	-  the name of the input files' format
 *	toolInTable	-  a table for the storage of data read in
 *	toolInFlagsTable-  a table for the storage of read flags
 *
 *	toolOutFilename	 - the name of the output file
 *	toolOutFormat	 - the name of the output file's format
 *	toolOutFlagsTable- a table for the storage of write flags
 *
 *	toolBackFilename  -the name of the background file
 *	toolBackFormat	  -the name of the background file's format
 *	toolBackTable	  -stores the data read in for the background image
 *	toolBackFlagsTable-a table for the storage of read flags
 *
 *	toolFrameStart	-  start value for a range of frames
 *	toolFrameEnd	-  end value for a range of frames
 *
 *	toolField	-  bit mask specifying fill parameters for background
 *	toolFieldStart	-  start value for a range of color for a fill
 *	toolFieldEnd	-  end value for a range of color for a fill
 *
 *	toolGraduate	-  how to fill area of background image
 *
 *	toolXSize	-  horiz. size of generated output background image
 *	toolYSize	-  vert. size of generated output background image
 *
 *	toolNRows	-  # of rows in storyboard
 *	toolNCols	-  # of columns in storyboard
 *
 *	toolXFrame	-  width of storyboard frames
 *	toolYFrame	-  height of storyboard frames
 *
 *	toolXGutter	-  amount of width between frames
 *	toolYGutter	-  amount of height between frames
 *
 *	toolXMargin	-  amount of width for the horizontal margin
 *	toolYMargin	-  amount of height for the vertical margin
 *
 *	toolXScale	-  fraction, to scale frame width
 *	toolYScale	-  fraction, to scale frame height
 *
 *	toolPreRead	-  flag indicating whether or not to pre-read files
 *
 *  DESCRIPTION
 *	Data held by these variables is used as global strings, or to hold
 *	data gathered from the user interface.
 */

static char      **toolInFilenames;	/* Input file name		*/
static int	  toolNInFiles;		/* # of input files		*/
static char      **toolInFormats;	/* Input files' format name	*/

static char      toolOutFilename[1024]; /* Output file name		*/
static char      toolOutFormat[1024];	/* Output file's format name	*/

static char      toolBackFilename[1024];
					/* Background file name	*/
static char      toolBackFormat[1024];	/* Background file's format name*/

static TagTable  *toolTmpTable;		/* Temporary tag table		*/
static TagTable  *toolInTable;		/* Input Data tag table		*/
static TagTable  *toolBackTable;	/* Input Data tag table		*/
static TagTable  *toolInFlagsTable;	/* Flags tag table		*/
static TagTable  *toolOutFlagsTable;	/* Flags tag table		*/
static TagTable  *toolBackFlagsTable;	/* Flags tag table		*/

static int	  toolFrameStart;	/* start of frames		*/
static int	  toolFrameEnd;		/* end of frames		*/

static int	  toolXSize;		/* width of the fill area	*/
static int	  toolYSize;		/* length of the fill area	*/

static float	  toolFieldStart;	/* Fill data start range	*/	
static float	  toolFieldEnd;		/* Fill data end range		*/	

static int	  toolField;		/* what fields to fill 		*/
static int	  toolGraduate;		/* which way to fill area	*/

static int	  toolNRows;		/* number of rows for storybrd	*/
static int	  toolNCols;		/* number of cols for storybrd	*/
static int	  toolXFrame;		/* frame width			*/
static int	  toolYFrame;		/* frame height			*/
static int	  toolXGutter;		/* gutter width			*/
static int	  toolYGutter;		/* gutter height		*/
static int	  toolXMargin;		/* margin width			*/
static int	  toolYMargin;		/* margin height		*/

static float	  toolXScale;		/* frame width  * toolXScale	*/
static float	  toolYScale;		/* frame height * toolYScale	*/

static int	  toolPreRead;		/* Whether to pre-read the files */



/*
 *  MACRO
 *	IM_BACK_FILL( color, option, maxValue )	
 *
 *  DESCRIPTION
 *	Get a color fill command line option.  If a value for a start or
 *	end range is not given, then fill that value with maxValue.
 *	Then fill the vfb (global) with a box toolXSize by toolYSize with
 *	the correct color value.  Also bound checks all possible input
 *	conditions within function toolValParse.
 *
 *  PARAMETERS
 *	color		-  value for what type of color to fill image with
 *	option		-  string identifying this color on the command line
 *	maxValue	-  default value for unsupplied start and end ranges
 *
 */
#define IM_BACK_FILL( color, option, maxValue )				\
	if ( toolField & (color) )					\
	{								\
		toolValParse( option, (maxValue) );			\
		if ( ImVfbFill( vfb, 0, 0,				\
			toolXSize, toolYSize, (color), toolFieldStart,	\
			toolFieldEnd, IMVFBINSIDE, toolGraduate,	\
			vfb ) == IMVFBNULL )				\
		{							\
			ImPError( ImToolsProgram );			\
			exit( 1 );					\
		}							\
	}



/*
 *  MACRO
 *	IM_GET_POS_INT_ARG( arg, argVar )
 *
 *  DESCRIPTION
 *	Get an integer argument from the command line and makes sure it
 *	is positive.  If it is not positive, then output an error message
 *	and exit the program.
 *
 *  PARAMETERS
 *	arg	-  Command line argument descriptor
 *	argVar	-  Pointer to where to store the data found on the command line
 *
 */
#define IM_GET_POS_INT_ARG( arg, argVar )				\
	if ( ArgQNOccur( arg ) != 0 )					\
	{								\
		*(argVar) = (int) ArgQValue( arg, 0, 0 )->arg_i;	\
		if ( *(argVar) < 0 )					\
		{							\
			fprintf( stderr, "%s: -%s value cannot be negative, please reenter.\n", ImToolsProgram, arg );					\
			exit( 1 );					\
		}							\
	}								\



/*
 *  MACRO
 *	IM_GET_NAT_INT_ARG( arg, argVar )
 *
 *  DESCRIPTION
 *	Get an integer argument from the command line and makes sure it
 *	is greater than zero, or a natural integer.  If it is not greater
 *	than zero, then output an error message	and exit the program.
 *
 *  PARAMETERS
 *	arg	-  Command line argument descriptor
 *	argVar	-  Pointer to where to store the data found on the command line
 *
 */
#define IM_GET_NAT_INT_ARG( arg, argVar )				\
	if ( ArgQNOccur( arg ) != 0 )					\
	{								\
		*(argVar) = (int) ArgQValue( arg, 0, 0 )->arg_i;	\
		if ( *(argVar) <= 0 )					\
		{							\
			fprintf( stderr, "%s: -%s value cannot be negative or zero, please reenter.\n", ImToolsProgram, arg );				\
			exit( 1 );					\
		}							\
	}								\



/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input files (put data into data table).
 *		-  Read / Generate background image
 *		-  Get an image and scale to cell size
 *		-  Paste image onto backimage
 *		-  Loop to get an image until no more images left
 *		-  Write out the output file (get data from data table).
 *
 *  NOTES
 *	This 'main' is pretty much the same for each of the image tools.
 *	Differences between tools include:
 *		-  the number of input files read in
 *		-  the number of output files written out
 *		-  the actions taken on the data between read and write
 *
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
	int	i, j;			/* counters			*/
	int	iCurImg, iCurFile;	/* index to current img or file	*/
	int	iFrame;			/* index to current frame (%d)	*/
	int	x, y;			/* posn counters while pasting	*/
	int	trueNFiles;		/* num of files incl -frames	*/
	char	inFilename[1024];	/* input file name temp storage	*/
	int	hadError      = FALSE;	/* error flag			*/
	int	framesNeeded  = FALSE;	/* frames present flag		*/
	int	updateFrameSz = FALSE;	/* flag for updating frame size	*/
	int dfltRowsCols  = FALSE;	/* are rows or cols defaulted?	*/
	int framesFlag    = FALSE;	/* are we reading frames now?	*/
	ImVfb	*vfb;			/* generated background image	*/
	ImVfb	*pasteVfb, *backVfb;	/* store vfb's while pasting	*/
	ImVfb	*pres;			/* temp pointer result		*/
	TagEntry *dataEntry;		/* temporary tag entry storage	*/

	int	pasteFields;		/* fields for input images	*/
	int	imgPasteFields;		/* image fields for input images*/
	int	datPasteFields;		/* data fields for input images	*/
	int	backFields;		/* fields for background image	*/
	int	imgBackFields;		/* image fields for back image	*/
	int	datBackFields;		/* data fields for back image	*/
	int	comboFields;		/* temp fields during conversion*/
	int	numImages;		/* # of images in a file        */

	float	res;			/* temporary result variable	*/
	float	gutterScale;		/* percent of frame to gutter	*/
	float	marginScale;		/* percent of frame to margin	*/

	argc = __argc;
	argv = __argv;

	/*
	 *  Initialize things:
	 *	-  Prepare the arg parsing data, then parse the command-line.
	 *	-  Prepare the flags table based upon command-line args.
	 *	-  Determine the file formats for input, output, and
	 *		background files.
	 *	-  Set values of background image command line args.
	 */
	toolInit( argc, argv );


	/*
	 *  Make sure all the input files exist.  Doing this first, before
	 *  trying to open and read the files can save the user quite a bit
	 *  of reading time when they make a filename typo.
	 */
	trueNFiles = toolNInFiles;
	for ( i = 0; i < toolNInFiles; i++ )
	{
		if ( strcmp( toolInFilenames[i], "-" ) == 0 )
		{
			if ( strcmp( toolBackFilename, "-" ) == 0 )
			{
				fprintf( stderr, "%s: -infile and -backfile cannot both be stdin.\n", ImToolsProgram );
				exit( 1 );
			}

			continue;
		}

		if ( strchr( toolInFilenames[i], '%' ) == NULL )
		{
			/*
			 *  Explicit file name without embedded printf %d.
			 *  Check the file.
			 */
			if ( _access( toolInFilenames[i], R_OK ) == -1 )
			{
				if (ImToolsVerbose )
					fprintf( stderr, "%s: Warning: Input file %s cannot be read.\n", ImToolsProgram, toolInFilenames[i] );
				hadError = TRUE;
			}
			continue;
		}

		/*
		 *  Implicit file name with embedded printf %d. Access all
		 *  of them.
		 */
		trueNFiles--;
		framesNeeded = TRUE;
		if ( toolFrameStart == -1 )
		{
			/* No frame range given.	*/
			fprintf( stderr, "%s: Use of a %%d in an input file name requires a -frames option\n", ImToolsProgram );
			fprintf( stderr, "%s: to indicate what range of frame numbers to put there.\n", ImToolsProgram );
			exit( 1 );
		}

		
		if ( toolFrameStart < toolFrameEnd )
		{
		int iFirst = TRUE;

			for ( j = toolFrameStart; j <= toolFrameEnd; j++ )
			{
				sprintf( inFilename, toolInFilenames[i], j );
				if ( _access( inFilename, R_OK ) == -1 )
				{
					if (ImToolsVerbose )
						fprintf( stderr, "%s: Warning: Input file %s cannot be read.\n", ImToolsProgram, inFilename );
					if (iFirst)
						hadError = TRUE;
				}
				trueNFiles++;
				iFirst = FALSE;
			}
		}
		else
		{
		int iFirst = TRUE;

			for ( j = 0; j <= toolFrameStart - toolFrameEnd; j++)
			{
				sprintf( inFilename, toolInFilenames[i],
					toolFrameStart - j );
				if ( _access( inFilename, R_OK ) == -1 )
				{
					if (ImToolsVerbose)
						fprintf( stderr, "%s: Warning: Input file %s cannot be read.\n", ImToolsProgram, inFilename );
					if (iFirst)
						hadError = TRUE;
				}
				trueNFiles++;
				iFirst = FALSE;
			}
		}
	}

//	if ( hadError )
//	{
//		fprintf( stderr, "%s: Aborted due to problems accessing the first input file.\n", ImToolsProgram );
//		exit( 1 );
//	}
	if ( toolFrameStart != -1 && framesNeeded == FALSE )
	{
		fprintf( stderr, "%s: -frames requires that input files include %%d in their names.\n", ImToolsProgram );
		exit( 1 );
	}


	if (toolPreRead == 1)
	{
		/* 
		 * Loop through the files looking for multiple image files. 
		 * Don't allow for multiple images within multiple frames, however, 
		 * because that situation probably won't occur.
		 *
		 */
		for (i=0;i<toolNInFiles;i++)
		{
			if (strchr(toolInFilenames[i], '%') == NULL)
			{
				ImToolsFileRead( toolInFilenames[i], toolInFormats[i], 
					toolInFlagsTable, toolTmpTable );
				numImages = TagTableQNEntry(toolTmpTable,"image vfb");
				if (numImages > 1)
				{
					trueNFiles += (numImages - 1);
				}
				toolClearTable(&toolTmpTable); 
			}
		}
		TagTableFree(toolTmpTable);
	}

	/*
	 *  Read in first file and base necessary defaults on characteristics
	 *	of this first file.
	 *  Can assume at this point that at least one input filename has been
	 *	passed in via the user interface.  This filename is at index
	 *	zero in the filename/format string arrays.
	 */

	if ( strchr( toolInFilenames[0], '%' ) == NULL )
	{
		/*
		 *  Explicit file name without embedded printf %d.
		 */
		strcpy( inFilename, toolInFilenames[0] );
	}
	else
	{
		/*
		 *  Implicit file name with embedded printf %d.  Read the
		 *	first one in.  Must add the number of frames to
		 *	the count of true input files.
		 */

		iFrame = toolFrameStart;
		framesFlag = TRUE;

		sprintf( inFilename, toolInFilenames[0], iFrame );
	}

	ImToolsFileRead( inFilename, toolInFormats[0],
		toolInFlagsTable, toolInTable );


	/*
	 *  Check for errors
	 *	-  no input images
	 */
	if ( TagTableQNEntry( toolInTable, "image vfb" ) == 0 )
	{
		fprintf( stderr, "%s: The first input file '%s' contained no images!\n", ImToolsProgram, inFilename );
		exit( 1 );
	}




	if ( *toolBackFilename != '\0' )
        {
		/*
		 *  Read in the background input file.
		 *      -  Open the file and read data into the
		 *	   data table.
		 */
                ImToolsFileRead( toolBackFilename, toolBackFormat,
			toolBackFlagsTable, toolBackTable );

		/*
		 *  Check for errors
		 *      -  no input images
		 */
                if ( TagTableQNEntry( toolBackTable, "image vfb" ) == 0 )
                {
                        fprintf( stderr, "%s: Background file contains no images!\n", ImToolsProgram );
                        exit( 1 );
                }

		dataEntry = TagTableQDirect( toolBackTable, "image vfb", 0 );
		TagEntryQValue( dataEntry, &vfb );

		if ( toolXSize < 0 )
			toolXSize = ImVfbQWidth( vfb );

		if ( toolYSize < 0 )
			toolYSize = ImVfbQHeight( vfb );

		if ( toolXSize != ImVfbQWidth( vfb ) ||
			toolYSize != ImVfbQHeight( vfb ) )
		{
			vfb = toolScaleVfb( vfb, toolXSize, toolYSize );
			TagTableReplace( toolBackTable,
				TagEntryQNthEntry( dataEntry ),
				TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb ));
		}
        }



	res = (float)(sqrt( (double)trueNFiles ));
	if ( toolNCols < 0 )
	{
		/*
		 *  Check to see if there are enough rows to hold all frames
		 *  if so, then have only one column
		 */

		if ( toolNRows > 0 )
			toolNCols = (int)ceil( (double)trueNFiles / toolNRows );
		else
			toolNCols = (int)ceil( res );

		dfltRowsCols = TRUE;
	}


	if ( toolNRows < 0 )
	{
		/*
		 *  Check to see if there are enough columns to hold all frames
		 *  if so then have only one row
		 */

		if ( dfltRowsCols == FALSE && toolNCols > 0 )
			toolNRows = (int)ceil( (double)trueNFiles / toolNCols );
		else
			toolNRows = (int)( res + 0.5 );

		dfltRowsCols = TRUE;
	}


	/*
	 *  Initialize scale value defaults
	 *
	 *  Defaults:
	 *	If the output image size is known
	 *		frame size gets equally split up output image size
	 *		gutter get 10% of the frame size
	 *		margin get 10% of the frame size
	 *		frame size now updated to accomodate the margin and
	 *		    gutter defaults
	 *
	 *	Else the output image size is unknown (output size flexible)
	 *		frame size gets size of first input image * scale value
	 *		gutter gets 10% of frame size
	 *		margin gets 10% of frame size
	 *		output size set to enough space to hold all frames
	 *		    along with margins and gutters
	 */
	
	gutterScale = (float)(0.1);
	marginScale = (float)(0.1);

	if ( toolXSize > 0 )
	{
		if ( toolXFrame < 0 )
		{
			toolXFrame = toolXSize;
			if ( toolXGutter > 0 )
				toolXFrame -= (toolNCols - 1) * toolXGutter;
			
			if ( toolXMargin > 0 )
				toolXFrame -= 2 * toolXMargin;

			toolXFrame = (int)((float)toolXFrame / toolNCols);
			updateFrameSz = TRUE;
		}

		if ( toolXGutter < 0 )
			toolXGutter = (int)(gutterScale * toolXFrame);

		if ( toolXMargin < 0 )
			toolXMargin = (int)(marginScale * toolXFrame);

		if ( updateFrameSz == TRUE )
		{	
			toolXFrame = (int)((float)
				(toolXSize - 2*toolXMargin -
				(toolNCols-1) * toolXGutter) / toolNCols);
			updateFrameSz = FALSE;
		}

	}
	else
	{
		if ( toolXFrame < 0 )
		{
			dataEntry = TagTableQDirect( toolInTable,
							"image vfb", 0 );

			TagEntryQValue( dataEntry, &vfb );

			toolXFrame = (int)(ImVfbQWidth( vfb ) * toolXScale);
		}

		if ( toolXGutter < 0 )
			toolXGutter = (int)(gutterScale * toolXFrame);

		if ( toolXMargin < 0 )
			toolXMargin = (int)(marginScale * toolXFrame);

		if ( toolXSize <= 0 )
			toolXSize = toolNCols * toolXFrame +
					(toolNCols-1) * toolXGutter +
					2*toolXMargin;
	}


	if ( toolXSize <= 0 )
	{
		fprintf( stderr, "%s: Width of the output image must be positive.\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Make sure that the images don't go outside of the storyboard
	 *  boundaries.
	 */

	i = toolXFrame * toolNCols + (toolNCols-1) *
		toolXGutter + 2*toolXMargin;

	if ( i > toolXSize)
	{
		fprintf( stderr, "%s: Not enough output image width, need %d more pixels.\n", ImToolsProgram, i-toolXSize );
		exit( 1 );
	}


	if ( toolYSize > 0 )
	{
		if ( toolYFrame < 0 )
		{
			toolYFrame = toolYSize;
			if ( toolYGutter > 0 )
				toolYFrame -= (toolNRows - 1) * toolYGutter;
			
			if ( toolYMargin > 0 )
				toolYFrame -= 2 * toolYMargin;

			toolYFrame = (int)((float)toolYFrame / toolNRows);
			updateFrameSz = TRUE;
		}

		if ( toolYGutter < 0 )
			toolYGutter = (int)(gutterScale * toolYFrame);

		if ( toolYMargin < 0 )
			toolYMargin = (int)(marginScale * toolYFrame);

		if ( updateFrameSz == TRUE )
		{	
			toolYFrame = (int)((float)
				(toolYSize - 2*toolYMargin -
				(toolNRows-1) * toolYGutter) / toolNRows);

			updateFrameSz = FALSE;
		}
	}
	else
	{
		if ( toolYFrame < 0 )
		{
			dataEntry = TagTableQDirect( toolInTable,
							"image vfb", 0 );
			TagEntryQValue( dataEntry, &vfb );

			toolYFrame = (int)(ImVfbQHeight( vfb ) * toolYScale);
		}

		if ( toolYGutter < 0 )
			toolYGutter = (int)(gutterScale * toolYFrame);

		if ( toolYMargin < 0 )
			toolYMargin = (int)(marginScale * toolYFrame);

		if ( toolYSize <= 0 )
			toolYSize = toolNRows * toolYFrame +
				(toolNRows-1) * toolYGutter +
				2*toolYMargin;
	}


	if ( toolYSize <= 0 )
	{
		fprintf( stderr, "%s: Height of output image must be positive.\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Make sure that storyboard images don't overrun storyboard 
	 *  boundaries.
	 */

	i = toolYFrame * toolNRows + (toolNRows-1) *
		toolYGutter + 2*toolYMargin;

	if ( i > toolYSize)
	{
		fprintf( stderr, "%s: Not enough output image height, need %d more pixels.\n", ImToolsProgram, i-toolYSize );
		exit( 1 );
	}


	/*
	 *  Construct a background image if one is not given
	 */

        if ( *toolBackFilename == '\0' )
        {
		/*
		 *  No input background file file.
		 *	-  Allocate an image at the correct size and depth.
		 *	-  Clear it to all zeroes.
		 *	-  Add it to the data table as if it had been read in.
		 */

		backFields = 0;
		if ( toolField & (IMRED | IMGREEN | IMBLUE |
					IMHUE | IMSATURATION | IMINTENSITY) )
			backFields |= IMVFBRGB;
		if ( toolField & IMALPHA )
			backFields |= IMVFBALPHA;
		if ( toolField & IMMONO )
			backFields |= IMVFBMONO;
		if ( toolField & IMINDEX8 )
			backFields |= IMVFBINDEX8;


		if ( ( backFields & IMVFBIMAGEMASK ) == 0 )
                	vfb = ImVfbAlloc( toolXSize, toolYSize, 
				IMVFBRGB | backFields );
		else
                	vfb = ImVfbAlloc( toolXSize, toolYSize, backFields );

                if ( vfb == IMVFBNULL )
		{
			perror( ImToolsProgram );
                        exit( 1 );
                }
	        ImVfbClear( IMVFBALL, 0, vfb );

		/*
		 *  Fill the background image.
		 */
		IM_BACK_FILL( IMRED,        "red",        255.0 );
		IM_BACK_FILL( IMGREEN,      "green",      255.0 );
		IM_BACK_FILL( IMBLUE,       "blue",       255.0 );
		IM_BACK_FILL( IMALPHA,      "alpha",      255.0 );
		IM_BACK_FILL( IMINDEX8,     "index",      255.0 );
		IM_BACK_FILL( IMINDEX16,    "index",      65535.0 );
		IM_BACK_FILL( IMMONO,       "mono",       1.0 );
		IM_BACK_FILL( IMINTENSITY,  "intensity",  1.0 );
		IM_BACK_FILL( IMSATURATION, "saturation", 1.0 );
		IM_BACK_FILL( IMHUE,        "hue",        360.0 );

                TagTableAppend( toolBackTable,
			TagEntryAlloc( "image vfb", IM_POINTER_TYPE, &vfb ) );
        }



	if ( ImToolsVerbose )
	{
		fprintf( stderr, "%s: Output filename: '%s'\n",
			ImToolsProgram, toolOutFilename );

		if ( *toolBackFilename != '\0' )
		{
			fprintf( stderr, "%s: Background filename: '%s'\n",
				ImToolsProgram, toolBackFilename );
		}
		else
		{
			fprintf( stderr, "%s: Background image generated by %s\n", ImToolsProgram, ImToolsProgram );
		}

		fprintf( stderr, "%s:\t\tX\t\tY\n", ImToolsProgram );
		fprintf( stderr, "%s: Size\t%d\t\t%d\n", ImToolsProgram, 
			toolXSize, toolYSize );
		fprintf( stderr, "%s: Rows\t\t\t%d\n", ImToolsProgram,
			toolNRows );
		fprintf( stderr, "%s: Cols\t%d\n", ImToolsProgram,
			toolNCols );
		fprintf( stderr, "%s: Margin\t%d\t\t%d\n", ImToolsProgram,
			toolXMargin, toolYMargin );
		fprintf( stderr, "%s: Frame\t%d\t\t%d\n", ImToolsProgram,
			toolXFrame, toolYFrame );
		fprintf( stderr, "%s: Scale\t%g\t\t%g\n", ImToolsProgram,
			toolXScale, toolYScale );
	}



	/*
	 *  Initialize pasting loop data
	 */

	dataEntry = TagTableQDirect( toolBackTable, "image vfb", 0 );
	TagEntryQValue( dataEntry, &backVfb );

	backFields    = ImVfbQFields( backVfb );
	imgBackFields = backFields & IMVFBIMAGEMASK;
	datBackFields = backFields & IMVFBOTHERMASK;

	x = toolXMargin;	/* x and y position of where to paste	*/
	y = toolYMargin;
	iCurImg  = 0;		/* used to index multiple image files	*/
	iCurFile = 0;		/* indexes current input file		*/

	/*
	 *  Perform pasting
	 */

	for ( i = 0; i < toolNRows; i++ )
	{
		for ( j = 0; j < toolNCols; j++ )
		{
		int iStop = FALSE;

			/*
			 *  Put the input image into a VFB
			 */

			dataEntry = TagTableQDirect( toolInTable,
							"image vfb", iCurImg );
			TagEntryQValue( dataEntry, &pasteVfb );

			/*
			 *  If the input image is of a shallower image data
			 *  depth than the background image, then convert
			 *  the image up to the depth of
			 *  the background image without losing any data fields
			 *  present in the input image.
			 *
			 *  If the input image has data fields not present
			 *  in the background image, then:
			 *
			 *  1. Create a new VFB that can hold the background
			 *     image and background data fields along with
			 *     the data fields of the input image.
			 *
			 *  2. Convert the input image to the image type of the 
			 *     background image.  During this conversion none
			 *     of the imput image's data fields data are
			 *     copied to the new image.
			 *
			 *  3. Copy the data fields of the input image into
			 *     the converted input image. (if necessary)
			 *
			 */

			pasteFields = ImVfbQFields( pasteVfb );
			imgPasteFields = pasteFields & IMVFBIMAGEMASK;
			datPasteFields = pasteFields & IMVFBOTHERMASK;

			if ( imgPasteFields != imgBackFields )
			{
				/*
				 * Change the input image to have the depth of
				 * the background image.
				 */

				vfb = ImVfbAlloc( ImVfbQWidth( pasteVfb ),
					ImVfbQHeight( pasteVfb ),
					imgBackFields );

				if ( vfb == IMVFBNULL )
				{
					fprintf( stderr, "%s: Unable to allocate memory for conversion VFB during paste.\n", ImToolsProgram );
					exit( 1 );
				}


				pres = IMVFBNULL;

				switch ( imgBackFields & IMVFBIMAGEMASK )
				{
				case IMVFBMONO:
					pres= ImVfbToMono( pasteVfb, 127, vfb );
					break;
				
				case IMVFBINDEX8:
					pres = ImVfbToIndex8( pasteVfb, vfb );
					break;

				case IMVFBINDEX16:
					pres = ImVfbToIndex16( pasteVfb, vfb );
					break;

				case IMVFBRGB:
					pres = ImVfbToRgb( pasteVfb, vfb );
					break;

				default:
					break;
				}

				if ( pres == IMVFBNULL )
				{
					fprintf( stderr, "%s: Not enough information in source image\n", ImToolsProgram );
					fprintf( stderr, "%s: to convert it to background image type.\n", ImToolsProgram );
					exit( 1 );
				}

//				ImVfbFree( pasteVfb );
				pasteVfb = vfb;
				pasteFields = ImVfbQFields( pasteVfb );
				imgPasteFields = pasteFields & IMVFBIMAGEMASK;
				datPasteFields = pasteFields & IMVFBOTHERMASK;
			}


			/*
			 *  If the input image contains data fields that are
			 *  not present in the background image, then promote
			 *  the background image to be able to store the 
			 *  extra data of the input image.  Initialize the 
			 *  new fields in the background data to zero.
			 */

			if ( (datPasteFields | datBackFields) != datBackFields)
			{
				comboFields = backFields | datPasteFields;


				/*
				 *  Create a destintion that can hold the
				 *  current background image information and
				 *  the data fields of the input image
				 */

				vfb = ImVfbAlloc( toolXSize, toolYSize,
					comboFields );

				if ( vfb == IMVFBNULL )
				{
					fprintf( stderr, "%s: Unable to allocate memory for conversion VFB during paste.\n", ImToolsProgram );
					exit( 1 );
				}


				/*
				 *  Initialize the new fields for the
				 *  background to zero.
				 */

				ImVfbClear( datPasteFields, 0, vfb );


				/*
				 *  Copy exiting background data into newly
				 *  allocated vfb.
				 */

				if ( ImVfbCopy( backVfb,      /* vfb to copy */
					0, 0,                 /* start here  */
					toolXSize, toolYSize, /* end here    */
					IMVFBALL,             /* orig planes */
					vfb,                  /* dest vfb    */
					0, 0 ) == IMVFBNULL ) /* at the top  */
				{
					fprintf( stderr, "%s: Couldn't create common paste region for background.\n", ImToolsProgram );
					fprintf( stderr, "%s: Cannot guarantee validity of input image paste onto background.\n", ImToolsProgram );
					ImVfbFree( vfb );
				}
				else
				{
					dataEntry =
						TagTableQDirect( toolBackTable,
							"image vfb", 0 );

					TagTableReplace( toolBackTable,
						TagEntryQNthEntry( dataEntry ),
						TagEntryAlloc( "image vfb",
							IM_POINTER_TYPE, &vfb ));

					ImVfbFree( backVfb );
					backVfb = vfb;

					backFields = comboFields;
					imgBackFields = backFields &
								IMVFBIMAGEMASK;
					datBackFields = backFields &
								IMVFBOTHERMASK;
				}
			}



			/*
			 *  Scale image to paste onto background
			 */

			if ( toolXFrame != ImVfbQWidth( pasteVfb ) ||
				toolYFrame != ImVfbQHeight( pasteVfb ) )
			{
				vfb = toolScaleVfb( pasteVfb,
						toolXFrame, toolYFrame );

//				ImVfbFree( pasteVfb );

				pasteVfb = vfb;
				pasteFields = ImVfbQFields( pasteVfb );
				imgPasteFields = pasteFields & IMVFBIMAGEMASK;
				datPasteFields = pasteFields & IMVFBOTHERMASK;
			}


			/*
			 *  Paste scaled input image onto background
			 */

			if ( ImVfbCopy( pasteVfb,
				0, 0,			/* start at origin  */
				toolXFrame, toolYFrame,	/* all of paste img */
				pasteFields,
				backVfb,		/* destination      */
				x, y ) == IMVFBNULL )	/* position of copy */
			{
				fprintf( stderr, "%s: Unable to paste image on background image at (%d, %d). (%d)\n", ImToolsProgram, x, y, ImErrNo );
				exit( 1 );
			}


			/*
			 *  Check for multiple image vfb's
			 *  If we haven't pre-read the files, then just take
			 *  one image from each file.
			 */

			iCurImg++;
			if ( toolPreRead == 0 && 
				iCurImg < TagTableQNEntry( toolInTable,"image vfb" ))
			{
				fprintf( stderr, "%s: Warning: Skipping multiple images in file %d of %d.\n", 
					ImToolsProgram, iCurFile+1, toolNInFiles);
				fprintf( stderr, "%s: Use -preread to storyboard files with multiple images\n", 
					ImToolsProgram );
				iCurImg = TagTableQNEntry( toolInTable,"image vfb" );
			}
			if ( iCurImg >= TagTableQNEntry( toolInTable,"image vfb" ) )
			{

				/*
				 *  Time to read another image file in
				 *
				 *  Must check to see if there are any more
				 *  files to read or if the current
				 *  file is a %d frames file.
				 */
			int iFirst = TRUE;

				do {
					if (iFirst)
						iFirst = FALSE;
					else {
					// Koordinaten und Indizies richten
						x += toolXFrame + toolXGutter;	/* goto next col    */
						if (++j == toolNCols) {
							x = toolXMargin;			/* goto beg of line */
							y += toolYFrame + toolYGutter;		/* goto next line   */

							j = 0;
							if (++i == toolNRows) {
								iStop = TRUE;
								break;
							}
						}
					}

					if ( framesFlag == TRUE )
					{
						if ( toolFrameStart < toolFrameEnd )
						{
							iFrame++;

							if ( iFrame > toolFrameEnd )
								framesFlag = FALSE;
						}
						else
						{
							iFrame--;

							if ( iFrame < toolFrameEnd )
								framesFlag = FALSE;
						}

						if ( toolFrameStart == toolFrameEnd )
							framesFlag = FALSE;
					}


					if ( framesFlag == TRUE )
					{
						sprintf( inFilename,
							toolInFilenames[iCurFile],
							iFrame );
					}
					else
					{
						iCurFile++;

						if ( iCurFile >= toolNInFiles )	
						{
							/*
							 *  Have read all image files
							 *  Quit storyboard loop
							 */

							 i = toolNRows;
							 j = toolNCols;
							 iStop = TRUE;
							 break;
						}

						strcpy( inFilename,
							toolInFilenames[iCurFile] );

						if ( strchr( inFilename, '%' )
							!= NULL )
						{
							iFrame = toolFrameStart;
							framesFlag = TRUE;

							sprintf( inFilename, 
								toolInFilenames[iCurFile], 
								iFrame );
						}
					}

				} while (_access(inFilename, R_OK) == -1);
				if (iStop)
					continue;		// end storyboard

				toolClearTable( &toolInTable );

				ImToolsFileRead( inFilename,
					toolInFormats[iCurFile], toolInFlagsTable,
					toolInTable );

				if ( TagTableQNEntry( toolInTable, "image vfb" )
					== 0 )
				{
					fprintf( stderr, "%s: Input file '%s' contains no images!\n", ImToolsProgram, toolInFilenames[iCurFile] );
					exit( 1 );
				}

				/*
				 *  Otherwise we got a file, reset image
				 *  index variable.
				 */

				
				iCurImg = 0;
			}	

			x += toolXFrame + toolXGutter;	/* goto next col    */
		}
		x = toolXMargin;			/* goto beg of line */
		y += toolYFrame + toolYGutter;		/* goto next line   */
	}
				

	/*
	 *  Check to see if we dropped out of the loop without pasting all
	 *  images
	 */

	if ( iCurFile < toolNInFiles )
	{
		fprintf( stderr, "%s: Warning: could not fit all images on storyboard.\n", ImToolsProgram );
	}

	ImToolsFileWrite( toolOutFilename, toolOutFormat, toolOutFlagsTable,
		toolBackTable );

	exit( 0 );
}





/*
 *  FUNCTION
 *	toolInit	-  initialize global variables and user interface
 *			   storage.  Also check user input for errors.
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
	int	    i;			/* Counters			*/
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
	 *  Use the standard Image Tools user registration and feedback forms.
	 */
	toolCommand.arg_register = ImToolsRegister;
	toolCommand.arg_feedback = ImToolsFeedback;


	toolCommand.arg_help1     = toolPreOptHelp;
	toolCommand.arg_fullhelp1 = toolPreOptHelp;

	/* Make help string      */
	toolCommand.arg_help2 = ImToolsMergeHelp( toolHelp, toolNote);

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
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options1 );
	nOpt = ImToolsMergeOptions( "back", nOpt, options1,
		IMTOOLSNREADOPTIONS, ImToolsReadOptions, &options );
	nOpt = ImToolsMergeOptions( "out", nOpt, options,
		IMTOOLSNWRITEOPTIONS, ImToolsWriteOptions, &options1 );
	nOpt = ImToolsMergeOptions( "", nOpt, options1,
		IMTOOLSNOTHEROPTIONS, ImToolsOtherOptions, &options );

	nEquiv = ImToolsMergeEquivs( "in", IM_TOOLNEQUIVS, toolEquivs,
		IMTOOLSNREADEQUIVS, ImToolsReadEquivs, &equivs1 );
	nEquiv = ImToolsMergeEquivs( "back", nEquiv, equivs1,
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
	 *  Make data tables to hold the data.
	 */

	if ( (toolTmpTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}

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
			fprintf( stderr, "%s: Missing end of frame range on -frames option.\n", ImToolsProgram );
			exit( 1 );

                case ARGRSINGLE:        /* n    length only             */
			toolFrameStart = 0;
                        toolFrameEnd   = (int) (value->arg_i - 1);
                        break;
                }

		if ( toolFrameStart < 0 )
		{
			fprintf ( stderr, "%s: -frame start number must be positive.\n", ImToolsProgram );
			exit( 1 );
		}
		if ( toolFrameEnd < 0 )
		{
			fprintf ( stderr, "%s: -frame end number must be positive.\n", ImToolsProgram );
			exit( 1 );
		}
        }


	/*
	 *  Determine how many input files we've got and allocate space for
	 *  their names.
	 */
	toolNInFiles = 0;
	toolNInFiles =  ArgQNOccur( "infile" );

	toolInFilenames = (char **)malloc( sizeof( char * ) * toolNInFiles );
	if ( toolInFilenames == NULL )
	{
		perror( ImToolsProgram );
		exit( 1 );
	}

	toolInFormats = (char **)malloc( sizeof( char * ) * toolNInFiles );
	if ( toolInFormats == NULL )
	{
		perror( ImToolsProgram );
		exit( 1 );
	}




	/*
	 * Set up the incoming and outgoing flags tables
	 * and get the names and types of our files.
	 */
	for (i=0;i<toolNInFiles;i++)
	{
		toolInFilenames[i] = (char *) malloc(sizeof(char) * 500);
		toolInFormats[i]   = (char *) malloc(sizeof(char) * 500);
		ImToolsGetNameAndFormat ( "in", i, toolInFilenames[i], toolInFormats[i]);
	}
	toolInFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolInFlagsTable, "in");

	toolOutFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolOutFlagsTable, "out" );
	ImToolsGetNameAndFormat ( "out", 0, toolOutFilename, toolOutFormat);

	toolBackFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolBackFlagsTable, "back" );
	ImToolsGetNameAndFormat ( "back", 0, toolBackFilename, toolBackFormat);

	/*
	 * Determine whether or not we should pre-read the files
	 */
	if (ArgQNOccur("preread") == 0)
		toolPreRead = 0;
	else
		toolPreRead = 1;

	/*
	 *  Get fill data to construct a background image
	 *  if no backfile is given.
	 */

	toolXSize = -1;
	toolYSize = -1;
	toolFieldStart = 0.0;
	toolFieldEnd   = 0.0;
	toolGraduate = IMGRADHORIZ;
	toolField = 0;


	IM_GET_NAT_INT_ARG( "xsize", &toolXSize )
	IM_GET_NAT_INT_ARG( "ysize", &toolYSize )
	
	
	if ( ArgQNOccur ( "graduate" ) != 0 )
	{
		tmp = ArgQValue( "graduate", 0, 0 )->arg_s;
		i   = strlen( tmp );
		if ( strncmp( tmp, "none", i ) == 0 )
			toolGraduate=IMGRADNONE;
		else if ( strncmp( tmp, "vertical", i ) == 0 )
			toolGraduate=IMGRADVERT;
		else if ( strncmp( tmp, "horizontal", i ) == 0 )
			toolGraduate = IMGRADHORIZ;
		else
		{
			fprintf( stderr, "%s: Unknown gradation direction '%s'.\n", ImToolsProgram, tmp );
		}
	}

	/*
	 *  Get the fields to fill.
	 */
	if ( ArgQNOccur( "red" ) != 0 )		toolField |= IMRED;
	if ( ArgQNOccur( "green" ) != 0 )	toolField |= IMGREEN;
	if ( ArgQNOccur( "blue" ) != 0 )	toolField |= IMBLUE;
	if ( ArgQNOccur( "alpha" ) != 0 )	toolField |= IMALPHA;
	if ( ArgQNOccur( "index" ) != 0 )	toolField |= IMINDEX8;
	if ( ArgQNOccur( "mono" ) != 0 )	toolField |= IMMONO;
	if ( ArgQNOccur( "hue" ) != 0 )		toolField |= IMHUE;
	if ( ArgQNOccur( "saturation" ) != 0 )	toolField |= IMSATURATION;
	if ( ArgQNOccur( "intensity" ) != 0 )	toolField |= IMINTENSITY;


	/*
	 *  Check to see if information to generate a background image and
	 *	a background image filename are given.  If so, the user must
	 *	choose one or the other, but not both, exit.
	 */

	if( toolField != 0 && *toolBackFilename != '\0' )
	{
		fprintf( stderr, "%s: Cannot supply both background image and\n", ImToolsProgram );
		fprintf( stderr, "%s: background image generation data.\n", ImToolsProgram );
		exit( 1 );
	}


	if ( toolField & (IMRED | IMGREEN | IMBLUE) )
	{
		if ( (toolField & ~(IMRED | IMGREEN | IMBLUE |
			IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Filling can only occur in one color space at a time.\n", ImToolsProgram );
			fprintf( stderr, "%s: -red, -green, and -blue cannot be mixed with other fill options.\n", ImToolsProgram );
			exit( 1 );
		}
	}
	else if ( toolField & (IMHUE | IMSATURATION | IMINTENSITY) )
	{
		if ( (toolField & ~(IMHUE | IMSATURATION
					| IMINTENSITY | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Filling can only occur in one color space at a time.\n", ImToolsProgram );
			fprintf( stderr, "%s: -hue, -saturation, and -intensity cannot be mixed with other\n", ImToolsProgram );
			fprintf( stderr, "%s: fill options.\n", ImToolsProgram);
			exit( 1 );
		}
	}
	else if ( toolField & IMMONO )
	{
		if ( (toolField & ~(IMMONO | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Filling can only occur in one color space at a time.\n", ImToolsProgram );
			fprintf( stderr, "%s: -mono cannot be mixed with other fill options.\n", ImToolsProgram );
			exit( 1 );
		}
	}
	else if ( toolField & IMINDEX8 )
	{
		if ( (toolField & ~(IMINDEX8 | IMALPHA)) != 0 )
		{
			fprintf( stderr, "%s: Filling can only occur in one color space at a time.\n", ImToolsProgram );
			fprintf( stderr, "%s: -index cannot be mixed with other fill options.\n", ImToolsProgram );
			exit( 1 );
		}
	}


	

	/*
	 *  Parse in storyboard formatting options.
	 */

	toolNRows   = toolNCols   = -1;
	toolXFrame  = toolYFrame  = -1;
	toolXGutter = toolYGutter = -1;
	toolXMargin = toolYMargin = -1;
	toolXScale  = toolYScale  = -1.0;

	if ( ArgQNOccur( "scale" ) != 0 )
	{
		toolXScale = (float)(ArgQValue( "scale", 0, 0 )->arg_f);
		toolYScale = toolXScale;

		if ( toolXScale < 0 )
		{
			fprintf( stderr, "%s: -scale value cannot be negative, please reenter.\n", ImToolsProgram );
			exit( 1 );
		}
	}
	
	if ( ArgQNOccur( "xscale" ) != 0 )
	{
		if ( toolXScale > 0 )
		{
			fprintf( stderr, "%s: -xscale and -scale options overlap, may not both be specified\n", ImToolsProgram ); 
			exit( 1 );
		}

		toolXScale = (float)(ArgQValue( "xscale", 0, 0 )->arg_f);

		if ( toolXScale < 0 )
		{
			fprintf( stderr, "%s: -xscale value cannot be negative, please reenter.\n", ImToolsProgram );
			exit( 1 );
		}
	}

	if ( ArgQNOccur( "yscale" ) != 0 )
	{
		if ( toolYScale > 0 )
		{
			fprintf( stderr, "%s: -yscale and -scale options overlap, may not both be specified\n", ImToolsProgram ); 
			exit( 1 );
		}

		toolYScale = (float)(ArgQValue( "yscale", 0, 0 )->arg_f);

		if ( toolYScale < 0 )
		{
			fprintf( stderr, "%s: -yscale value cannot be negative, please reenter.\n", ImToolsProgram );
			exit( 1 );
		}
	}


	/*
	 *  Get command line arguments that must be >= 1
	 */

	IM_GET_NAT_INT_ARG( "rows", &toolNRows );
	IM_GET_NAT_INT_ARG( "columns", &toolNCols );
	IM_GET_NAT_INT_ARG( "xframe", &toolXFrame );
	IM_GET_NAT_INT_ARG( "yframe", &toolYFrame );


	if ( (toolXScale > 0 && toolXFrame > 0) ||
		(toolYScale > 0 && toolYFrame > 0) )
	{
		fprintf( stderr, "%s: Frame size can only be specified by one parameter.\n", ImToolsProgram );
		fprintf( stderr, "%s: Cannot mix frame scaling and frame size options.\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Assign defaults if a scale value was not
	 *  specified on the command line
	 */

	if ( toolXScale < 0 )
		toolXScale = 1.0;

	if ( toolYScale < 0 )
		toolYScale = 1.0;


	/*
	 *  Get command line arguments that must be > 0
	 */

	IM_GET_POS_INT_ARG( "xgutter", &toolXGutter );
	IM_GET_POS_INT_ARG( "ygutter", &toolYGutter );
	IM_GET_POS_INT_ARG( "xmargin", &toolXMargin );
	IM_GET_POS_INT_ARG( "ymargin", &toolYMargin );

}




/*
 *  FUNCTION
 *	toolValParse	-  get a value range
 *
 *  DESCRIPTION
 *	Take an argument value range and split it up into the start and end.
 *	Also check bounds of known input parameters.  If an out of range 
 *	value is entered, output an error message and exit the program.
 *
 */
static void				/* Returns nothing		*/
#ifdef __STDC__
toolValParse( char *option, float maxV )
#else
toolValParse( option, maxV )
	char      *option;		/* Option name			*/
	float	   maxV;		/* maximum value field can take */

#endif
{
        ArgValue   *value;              /* Argument value               */

	value = ArgQValue( option, 0, 0 );

	switch ( value->arg_rform )
	{
	case ARGRCLOSED:        /* n-m  start and end values		*/
		toolFieldStart = (float)(value->arg_fr1);
		toolFieldEnd   = (float)(value->arg_fr2);
		break;

	case ARGROPEN:          /* n-   start to max values		*/
		toolFieldStart = (float)(value->arg_f);
		toolFieldEnd   = maxV;
		break;

	case ARGRSINGLE:        /* n    value only			*/
		toolFieldStart = (float)(value->arg_f);
		toolFieldEnd   = (float)(value->arg_f);
		break;
	}

	if ( toolFieldStart > maxV || toolFieldEnd > maxV ||
		toolFieldStart < 0 || toolFieldEnd < 0 )
	{
		fprintf( stderr, "%s: -%s value invalid.  Must be between 0 and %g.\n", ImToolsProgram, option, maxV, option );
		exit( 1 );
	}
}



/*
 *  FUNCTION
 *	toolPromoteRgb	-  promote an image to RGB
 *
 *  DESCRIPTION
 *	An incomming image is promoted, if necessary, to an RGB image with
 *	the same non-image fields (and their data) as the incomming image.
 *
 */

static ImVfb *				/* Returns new RGB image	*/
#ifdef __STDC__
toolPromoteRgb( ImVfb *srcVfb )
#else
toolPromoteRgb( srcVfb )
	ImVfb *srcVfb;			/* Image to turn into RGB	*/
#endif
{
	int srcFields;			/* Field mask of source image	*/
	int srcRgbFields;		/* New RGB image's fields	*/
	ImVfb *srcRgbVfb;		/* New RGB VFB			*/
	int srcW, srcH;			/* Source dimensions		*/


	/*
	 *  If the source image is already RGB, just return it.
	 */
	srcFields = ImVfbQFields( srcVfb );
	if ( srcFields & IMVFBRGB )
		return ( srcVfb );


	/*
	 *  If the source image doesn't have any non-image fields, such as
	 *  an alpha plane or Z-buffer, just convert it to a new VFB and
	 *  return the new VFB.
	 */
	if ( (srcFields & (~IMVFBIMAGEMASK)) == 0 )
		return ( ImVfbToRgb( srcVfb, IMVFBNEW ) );


	/*
	 *  The source image has "extra" fields not associated with image data.
	 *  We need to allocate a new VFB with an RGB image field, as well as
	 *  the other non-image fields from the source.
	 *
	 *  The source's non-image field data must then be copied into the new
	 *  VFB, and the source's image fields promoted to RGB data.
	 */
	srcW = ImVfbQWidth( srcVfb );
	srcH = ImVfbQHeight( srcVfb );
	srcRgbFields = (srcFields & (~IMVFBIMAGEMASK)) | IMVFBRGB;

	srcRgbVfb = ImVfbAlloc( srcW, srcH, srcRgbFields );
	if ( srcRgbVfb == IMVFBNULL )
		return ( IMVFBNULL );

	if ( ImVfbCopy( srcVfb,
		0, 0, srcW, srcH, srcFields & (~IMVFBIMAGEMASK),
		srcRgbVfb, 0, 0 ) == IMVFBNULL )
	{
		ImVfbFree( srcRgbVfb );
		return ( IMVFBNULL );
	}

	if ( ImVfbToRgb( srcVfb, srcRgbVfb ) == IMVFBNULL )
	{
		ImVfbFree( srcRgbVfb );
		return ( IMVFBNULL );
	}

	return ( srcRgbVfb );
}





/*
 *  FUNCTION
 *	toolDemoteRgb	-  demote an image from RGB
 *
 *  DESCRIPTION
 *	The incomming image is demoted to the given field type and returned.
 */

static ImVfb *				/* Returns demoted VFB		*/
#ifdef __STDC__
toolDemoteRgb( ImVfb *srcVfb, int dstFields )
#else
toolDemoteRgb( srcVfb, dstFields )
	ImVfb *srcVfb;			/* Image to demote		*/
	int    dstFields;		/* Desired fields		*/
#endif
{
	int srcW, srcH;			/* Source dimensions		*/
	ImVfb *dstVfb;			/* New destination VFB		*/
	ImVfb *tmpVfb;			/* Temporary VFB pointer holder	*/


	/*
	 *  If the source image already has the desired fields, just return
	 *  the source image.
	 */
	if ( ImVfbQFields( srcVfb ) == dstFields )
		return ( srcVfb );


	/*
	 *  If the destination fields include non-image fields, make a new
	 *  VFB and copy those non-image fields to it.
	 */
	if ( dstFields & (~IMVFBIMAGEMASK) )
	{
		srcW = ImVfbQWidth( srcVfb );
		srcH = ImVfbQHeight( srcVfb );

		dstVfb = ImVfbAlloc( srcW, srcH, dstFields );
		if ( dstVfb == IMVFBNULL )
			return ( IMVFBNULL );

		if ( ImVfbCopy( srcVfb,
			0, 0, srcW, srcH, dstFields & (~IMVFBIMAGEMASK),
			dstVfb, 0, 0 ) == IMVFBNULL )
		{
			ImVfbFree( dstVfb );
			return ( IMVFBNULL );
		}
	}
	else
		dstVfb = IMVFBNEW;


	/*
	 *  Convert the image to the desired image type.
	 */
	switch ( dstFields & IMVFBIMAGEMASK )
	{
	case IMVFBMONO:
		tmpVfb = ImVfbToMono( srcVfb, 127, dstVfb );
		break;

	case IMVFBINDEX8:
		tmpVfb = ImVfbToIndex8( srcVfb, dstVfb );
		break;

	case IMVFBINDEX16:
		tmpVfb = ImVfbToIndex16( srcVfb, dstVfb );
		break;
	}

	if ( tmpVfb == IMVFBNULL )
	{
		if ( dstVfb != IMVFBNULL )
			ImVfbFree( dstVfb );
		return ( IMVFBNULL );
	}

	return ( tmpVfb );
}




/*
 *  FUNCTION
 *	toolScaleVfb	-  imscale imtool in a function
 *
 *  DESCRIPTION
 *	Given a source VFB and the new size (x, y) of the VFB image this
 *	routine with resize the image to (x, y).  This function is exactly like
 *	using imscale.  As much image data a possible will be saved in the
 *	scaling.
 *
 */
static ImVfb *				/* Return a resized VFB		*/
#ifdef __STDC__
toolScaleVfb( ImVfb *srcVfb, int xsize, int ysize )
#else
toolScaleVfb( srcVfb, xsize, ysize )
	ImVfb	*srcVfb;		/* VFB img to resize		*/
	int	xsize;			/* new xsize for resulting img	*/
	int	ysize;			/* new ysize for resulting img	*/
#endif
{
	ImVfb	*srcRgbVfb;		/* Temporary RGB image		*/
	int      srcFields;		/* Source image's fields	*/
	int      srcRgbFields;		/* RGB source image's fields	*/
	ImVfb	*dstVfb;
	ImVfb	*dstRgbVfb;		/* Temporary RGB image		*/
	int	scaleAlg;		/* type of resizing alg. to use	*/

	scaleAlg     = IMVFBBILINEAR;
	srcFields    = ImVfbQFields( srcVfb );
	srcRgbFields = (srcFields & (~IMVFBIMAGEMASK)) | IMVFBRGB;

	/*
	 *  If the source image is not RGB, then promote it
	 *  to RGB so that the resize will interpolate colors,
	 *  rather than color table indexes.  Maintain all
	 *  non-image fields and their data.
	 */
	srcRgbVfb = toolPromoteRgb( srcVfb );
	if ( srcRgbVfb == IMVFBNULL )
	{
		fprintf( stderr, "%s: Couldn't create temporary RGB image during resize.\n", ImToolsProgram );
		exit( 1 );
	}



	/*
	 *  Make a new destination image of the right size,
	 *  and with the same fields as the original (RGB
	 *  version).
	 */
	dstRgbVfb = ImVfbAlloc( xsize, ysize, srcRgbFields );
	if ( dstRgbVfb == IMVFBNULL )
	{
		fprintf( stderr, "%s: Couldn't create temporary RGB image during resize.\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Resize the RGB image.
	 */
	dstVfb = ImVfbResize( srcRgbVfb, scaleAlg, dstRgbVfb, xsize, ysize );


	if ( dstVfb == IMVFBNULL )
	{
		fprintf( stderr, "%s: Couldn't resize input image, possibly not enough memory.\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  If the source image was not RGB, demote the resized
	 *  image to the same image type.  Be careful to
	 *  maintain extra non-image fields, if any.
	 */
	dstVfb = toolDemoteRgb( dstRgbVfb, srcFields );
	if ( dstVfb == IMVFBNULL )
	{
		fprintf( stderr, "%s: Couldn't create temporary RGB image during resize.\n", ImToolsProgram );
		exit( 1 );
	}

	if ( (srcFields & IMVFBINDEX8) && ImVfbQClt( srcVfb ) == IMCLTNULL)
	{
		/*
		 *  Source was grayscale (no CLT).  Convert the
		 *  new image to grayscale and remove its CLT.
		 */
		if ( ImVfbToGray( dstVfb, dstVfb )==IMVFBNULL )
		{
			fprintf( stderr, "%s: Couldn't post-process image during resize.\n", ImToolsProgram );
			exit( 1 );
		}
		ImCltFree( ImVfbQClt( dstVfb ) );
		ImVfbSClt( dstVfb, IMCLTNULL );
	}

	if ( dstRgbVfb != dstVfb )
		ImVfbFree( dstRgbVfb );

	return dstVfb;
}




/*
 *  FUNCTION
 *	toolClearTable	-  Free a tag table, including all it's data.
 *
 *  DESCRIPTION
 *	Free all the nodes of a tag table and free all the data pointed
 *	at by the nodes' data pointers.  Return a newly allocated tag table.
 *
 */
static void				/* Returns nothing	*/
#ifdef __STDC__
toolClearTable( TagTable **clrTable )
#else
toolClearTable( clrTable )
	TagTable **clrTable;		/* Tag Table to clear	*/
#endif
{
	int 		i;
	TagEntry 	*dataEntry;	/* used to obtain correct entries   */
	ImVfb 		*vfb;		/* variables used to clear out data */
	ImClt 		*clt;
	char		*name;
	ImHotSpotPtr	*hotspot;
	
	i = TagTableQNEntry( *clrTable, "image vfb" ) - 1;

	for( ; i >= 0; i-- )
	{
		dataEntry = TagTableQDirect( *clrTable, "image vfb", i );
		TagEntryQValue( dataEntry, &vfb );
		ImVfbFree( vfb );
	}
	
	i = TagTableQNEntry( *clrTable, "image clt" ) - 1;

	for( ; i >= 0; i-- )
	{
		dataEntry = TagTableQDirect( *clrTable, "image clt", i );
		TagEntryQValue( dataEntry, &clt );
		ImCltFree( clt );
	}

	i = TagTableQNEntry( *clrTable, "image name" ) - 1;

	for( ; i >= 0; i-- )
	{
		dataEntry = TagTableQDirect( *clrTable, "image name", i );
		TagEntryQValue( dataEntry, &name );
		free( name );
	}

	i = TagTableQNEntry( *clrTable, "image hot spot" ) - 1;

	for( ; i >= 0; i-- )
	{
		dataEntry = TagTableQDirect( *clrTable, "image hot spot", i );
		TagEntryQValue( dataEntry, &hotspot );
		free( hotspot );
	}


	TagTableFree( *clrTable );

	if ( (*clrTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}
}
