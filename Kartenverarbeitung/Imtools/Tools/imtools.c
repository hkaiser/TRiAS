/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imtools.c,v 1.21 1995/06/30 22:21:31 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imtools.c,v 1.21 1995/06/30 22:21:31 bduggan Exp $"

/**
 **  FILE
 **	imtools.c	-  generic image tools code used by most tools
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imtools.c contains generic tool code used by most of the image tools.
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	ImToolsProgram		v  the program's name
 **	ImToolsVerbose		v  be verbose?
 **	ImToolsReadOptions	v Basic file reading options for most tools
 **	ImToolsReadEquivs	v Basic file reading equivalencies for most tools
 **	ImToolsWriteOptions	v Basic file writing options for most tools
 **	ImToolsWriteEquivs	v Basic file writing equivalencies for most tools
 **	ImToolsOtherOptions	v Other options for most tools
 **	ImToolsOtherEquivs	v Other equivalencies for most tools
 **
 ** 	ImToolsMergeHelp        f  merge help strings
 **	ImToolsMergeOptions	f  merge option lists
 **	ImToolsMergeEquivs	f  merge equivalences lists
 **	ImToolsIsFormat		f  check if a name is an image file format name
 **
 **	ImToolsChangeTagEntry	f  change a tag table entry
 **	ImToolsMakeStandardFlagsTable f create a new generic flags table
 **	ImToolsGetNameAndFormat f  get file name, format from command line options
 **	ImToolsAddReadWriteFlags f add file i/o flags to a flags table
 **
 **	ImToolsErrorHandler	f  standard error code handler
 **	ImToolsInfoHandler	f  standard info handler
 **	ImToolsOpen		f  open a file/stream & get its format
 **	ImToolsFileRead		f  read in an image file
 **	ImToolsFileWrite	f  write out an image file
 **
 **
 **  PRIVATE CONTENTS
 **	imValidateChannel	f  check for a valid channel name
 **     imStringToLower         f  convert a string to lower case
 **	imMakeFormatHelpString  f  Create a help string w/ format names
 **
 **  HISTORY
 **	$Log: imtools.c,v $
 **	Revision 1.21  1995/06/30  22:21:31  bduggan
 **	fixed non-ansi bug
 **
 **	Revision 1.20  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.20  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.19  1995/06/16  06:55:02  bduggan
 **	added cast to int
 **
 **	Revision 1.18  1995/06/16  06:20:39  bduggan
 **	Added dynamic compression scheme help string.
 **	Added pageheight, pagewidth, dpi flags.
 **	Removed use of global ImFileFormats variable.
 **	Added some prototypes for ANSI compatibility.
 **	Made some things 80 chars long.
 **
 **	Revision 1.17  1995/05/19  13:02:40  bduggan
 **	Modified interface to allow for compressed files.
 **	i.e. we now call ImFileFRead with a NULL format unless
 **	the user specifies one.
 **
 **	Revision 1.16  1995/05/18  00:05:25  bduggan
 **	Added -outtransparency option.
 **	Added filecompression read and write options.
 **
 **	Revision 1.15  1995/05/06  02:00:13  bduggan
 **	Added specific help for all of the i/o options.
 **	Changed format specifiers like -gif to be -informat gif
 **	Added transparency flag for gifs
 **	Added channel mapping capability
 **
 **	Revision 1.13  1995/01/11  00:05:31  bduggan
 **	Added -outgroup option and dct compression option
 **
 **	Revision 1.12  94/10/03  15:49:53  nadeau
 **	Updated base help on file format conversions.
 **	Changed outofdate references to imscatter to imsplit.
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
 **	Revision 1.11  93/03/02  11:52:56  secoskyj
 **	Fixed strcpy problem where strings were being
 **	copied into a space that was not large enough
 **	for them.
 **	
 **	
 **	Revision 1.10  93/02/26  22:28:08  secoskyj
 **	No changes
 **	
 **	Revision 1.9  92/12/03  01:20:38  nadeau
 **	Minor change to info handler.
 **	
 **	Revision 1.8  92/12/01  14:08:55  nadeau
 **	Fixed bogus debug message.
 **	
 **	Revision 1.7  92/11/04  13:59:11  groening
 **	changed *pFmt to **pFmt
 **	since ImFIleFormats type was changed
 **	
 **	Revision 1.6  92/10/19  14:23:55  groening
 **	added \n for read and write
 **	verbose statements for readabliilty
 **	
 **	Revision 1.5  92/10/12  16:09:32  vle
 **	Fixed -verbose flag option.
 **	
 **	Revision 1.4  92/09/23  13:40:37  vle
 **	Changed all "!= 0" checks in ImToolsBuildFlagsTable() to "> 0"
 **	
 **	Revision 1.3  92/08/31  17:16:22  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.2  91/10/03  13:22:42  nadeau
 **	Changed 'interlace' to 'interleave'.
 **	
 **	Revision 1.1  91/10/03  13:20:06  nadeau
 **	Initial revision
 **	
 **/

#include <unistd.h>
#include <malloc.h>

#include "imtools.h"





/*
 *  GLOBALS
 *	ImToolsProgram	-  the program's name
 *	ImToolsVerbose	-  be verbose?
 *
 *  DESCRIPTION
 *	The tool's argv[0] is stored in ImToolsProgram and used in
 *	various error messages.
 *
 *	ImToolsVerbose toggles verbose output.
 */

char   *ImToolsProgram = "imtool";
int ImToolsVerbose = FALSE;
#ifdef __STDC__
static void   imStringToLower(char* str);
static int    imValidateChannel(char* str);
static char*  imMakeFormatHelpString(char* prefix);
static char*  imMakeCompressHelpString(char* prefix);
#else
static void   imStringToLower();
static int    imValidateChannel();
static char*  imMakeFormatHelpString();
static char*  imMakeCompressHelpString();
#endif



/*
 *  GLOBAL
 *      ImToolsInHelp
 *      ImToolsOutHelp
 *
 *  DESCRIPTION
 *      ImToolsInHelp
 *      ImToolsOutHelp
 *	These messages contain help information used by most of the image tools,
 *	in addition to their own tool-specific help.  This generic help
 *	information describes how to specify image file formats, and describes
 *	the standard image input and output options.
 *
 */


char *ImToolsOutHelp =
"\n\
Output File Options\n\
-------------------\n\
    There are a wide variety of options for customizing an output file.\n\
    In addition to specifying the format, you can specify whether or not\n\
    the output file has a color lookup table (CLT), whether or not the\n\
    output file has an alpha channel, the compression method of the output\n\
    file, the number of channels in the output file, the size of each channel\n\
    in the output file, and various other characteristics.  Refer to the list\n\
    of options above for all such output file parameters.  If you'd like more\n\
    information about any one of these, type '%command -help -<option name>'\n\
\n\
    For a list of the image formats that are supported, see the help page\n\
    for an option of the form '-...format', or use the 'imformats' command.\n\
\n\
    By default, output file's image file formats are determined by the file's\n\
    filename extension (like .hdf for HDF files).  To override the default,\n\
    explicit format names may be given using a flag of the form -...format.\n\
    For instance, -outformat hdf to write an hdf file.\n\
    \n\
    A single dash ('-') for an output filename indicates stdout.  When using\n\
    stdout, an explicit format name is necessary.\n\
";


char* ImToolsInHelp = 
"\n\
Input File Options\n\
------------------\n\
    It is possible to remap the channels of a file when it is read in\n\
    by using the options above of the form '-...map'.  For more information\n\
    about how to do this, see the help page for such an option.\n\
\n\
    For a list of the image formats that are supported, see the help page\n\
    for an option of the form '-...format', or use the 'imformats' command.\n\
\n\
    By default, input file's image file formats are determined by the file's\n\
    magic number or the filename extension (like .hdf for HDF files). \n\
    To override the default, explicit format names may be given using a flag of\n\
    the form -...format.  For instance, -informat hdf to read an hdf file.\n\
    \n\
    A single dash ('-') for an input filename indicates stdin.  When using\n\
    stdin, an explicit format name is necessary.\n\
";


/*
 *  GLOBAL
 *	ImToolsReadOptions	- Basic file reading options for most tools
 *	ImToolsReadEquivs	- Basic file reading equivalencies for most tools
 *	ImToolsWriteOptions	- Basic file writing options for most tools
 *	ImToolsWriteEquivs	- Basic file writing equivalencies for most tools
 *	ImToolsOtherOptions	- Other options for most tools
 *	ImToolsOtherEquivs	- Other equivalencies for most tools
 *
 *  DESCRIPTION
 *	The read options are common options for reading in images.  They 
 *  will often have a prefix placed in front of them on the command line
 *  (such as "out").  
 *
 *  	The write options are common options for outputting images.  They
 *  will often be preceeded by "in".
 */

ArgOption ImToolsWriteOptions[IMTOOLSNWRITEOPTIONS] =
{
	{ "index", NULL, "Force output as a color indexed image%end\
    The -%option option forces storage of the image as color indexes.\n\
\n\
    An image file can be either RGB or color indexed.\n\
\n\
    The %option option is used to generate a color indexed file.\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "rgb", NULL, "Force output as an RGB image%end\
    The -%option option forces storage of the image as RGB color values \n\
\n\
    An image file can be either RGB or color indexed.\n\
\n\
    The %option option is used to generate an rgb file.\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "nchan", "no_channels", "Force output of # of channels/pixel%end\
    The -%option option selects the number of channels to store in the output image\n\
\n\
    An image file can be either RGB or color indexed.\n\
\n\
    An RGB image file typically has three channels (red, green, and blue).\n\
\n\
    A color indexed image typically has one channel (the index).\n\
\n\
    The %option option is used to indicate the type of an image.  For instance,\n\
    '-%option 3' indicates that we want to generate an RGB image.\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 1, 1, ARGTINT },

	{ "chandepth", "no_bits", "Force output of # of bits/channel/pixel%end\
\n\
    The %option option allows you to specify the size of each channel in the\n\
    image file.\n\
\n\
    Image files typically have 8 bits per channel.  The most common exceptions to\n\
    this are monochrome images (1 bit per channel) and 16-bit color-indexed\n\
    images (16 bits per channel).\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 1, 1, ARGTINT },

	{ "clt", NULL, "Force output of a CLT with the image%end\n\
    The -%option option allows you to force storage of a color lookup table with\n\
    the image.\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "noclt", NULL, "Block output of a CLT with the image%end\n\
    The -%option option allows you to block storage of a color lookup table with\n\
    the image.\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "threshold", "mono_threshold", "Threshold value for converting to mono image%end\n\
    The -%option option allows you to define the threshold for converting the \n\
	black and white for monochrome output images. Negative values (-255..0) will\n\
	invert the output image (pixel values smaller than the given absolute value\n\
	will appear as white, greater values as black).\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 1, 1, ARGTINT },

	{ "swapbitorder", NULL, "Forces swapping bits in every byte%end.\n\
	The -%option option allows to swap the bits in every read byte (makes sense \n\
	for TIFF format only).\n\
\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "alpha", NULL, "Force output of alpha plane with image%end\
    The -%option option forces storage of an alpha plane with the image.\n\
\n\
    When a new alpha channel is created, it is automatically opaque.\n\
    (i.e.  Every value is 255)\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "noalpha", NULL, "Block output of alpha plane with image%end\
    The -%option option blocks storage of an alpha plane.\n\
\n\
    Please see the man page on imconv for more information about different\n\
    types of images.\n\
\n\
",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "interleave", "inter_type", "Force output of interleaved RGB image%end\
    The -%option option forces the use of an RGB interleaving scheme:\n\
        none      Do not interleave             RGBRGBRGBRGBRGBRGB...\n\
        line      Use scanline interleaving     RRR..GGG..BBB..RRR..GGG..BBB...\n\
        plane     Use plane interleaving        RRRRRR...GGGGGG...BBBBBB...\n\
	\n\
    Interleave only applies to RGB image storage.  Not all formats support all\n\
    schemes.  The default is the best or most widly used scheme supported by\n\
    the format.\n\
    ",
	  ARGFFULLHELP, 1, 1, ARGTSTRING },

	{ "compress", "comp_type", "Force output of compressed image%end\
   The -%option option forces use of a specific image compression scheme:\n\
        none                    Do not compress\n\
        lzw                     Use Limpel-Ziv Welsh compression\n\
        mac, pb, or packbits    Use Macintosh PackBits compression\n\
        rle                     Use Run-Length Encoded compression\n\
        dct, jpeg               Use Discrete Cosine Transform compression\n\
        ascii                   Use ascii compression\n\
	\n\
    Not all formats support all schemes.  The default is the best or most\n\
    widly used compression scheme supported by the format.\
    ",
	  ARGFFULLHELP, 1, 1, ARGTSTRING },

	{ "group", "group_type", "Force output of grouped image%end\
    The -%option option forces the use of a specific method of grouping values:\n\
        tiles       Group values into tiles (i.e. rectangular blocks)\n\
        scanlines   Group values into scanlines (i.e. linear strips)\n\
	\n\
    Some compression schemes require the values to be grouped in a certain\n\
    way.  Not all formats support all grouping methods.  The default is to use\n\
    the most common grouping method for the given compression scheme.\n\
	  ",
	  ARGFFULLHELP, 1, 1, ARGTSTRING },

	{ "map", "channel_map", "Write one channel into another one%end\
    The -%option option indicates that one channel in memory shall be mapped to a\n\
    different channel in the output file.\n\
        blue=red    Output the red channel as blue.\n\
        gray=alpha  Output the alpha channel as gray.\n\
        blue=none   Don't output the blue channel.\n\
	\n\
    A map selection is always of the form <destination>=<source> where \n\
    <destination> and <source> are each one of the following: \n\
              red, green, blue, alpha, grey, index, index16, none\n\
    Multiple channels may be mapped by using the %option option repeatedly. \n\
    For instance, -%option blue=red -%option red=blue will swap the red and blue\n\
    channels.\n\
	  ",
	  ARGFFULLHELP|ARGFMULTIPLE, 1, 1, ARGTSTRING },

	{ "quality", "whole_number", "Force quality of compression%end\
	-%option specifies a value for the quality of the output.\n\
   The significance of the value of the quality depends on the compression\n\
   scheme used.  The possible values also depends on the compression\n\
   scheme used.\n\
	The value must be in the range 0-100 when using Discrete Cosine \n\
  Transform (JPEG) compression.\n\
	  ",
	  ARGFFULLHELP, 1, 1, ARGTINT },
	{ "format", "format_name", NULL, /* help string will be created by imMakeFormatHelpString */
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "transparency", NULL, "Force single-color transparency%end\
	-%option allows you to specify that you would like your image to have a\n\
   transparency field.  A transparency field is an index that may or may not have\n\
   a color in the color lookup table of an image.  Pixels with this index value\n\
   are considered transparent.",
	  ARGFFULLHELP, 0, 0, ARGTNONE },

	{ "transparencyrgb", "r g b", "Force single-color transparency%end\
	-%option allows you to specify that you would like your image to have a\n\
   transparency field.  By using this option, one may set the transparency\n\
   field to be the index in the color lookup table corresponding to the red,\n\
   green, and blue values specified.\n\
	The transparency field of an image is an index value.  Pixels with this index\n\
   value are transparent.",
	  ARGFFULLHELP, 3, 3, ARGTINT },

	{ "transparencyindex", "index", "Force single-color transparency%end\
	-%option allows you to specify that you would like your image to have a\n\
   transparency field.  \n\
	The transparency field of an image is an index value.  Pixels with this index\n\
   value are transparent.",
	  ARGFFULLHELP, 1, 1, ARGTINT },

	{ "filecompression", "scheme", NULL, 
		/* Help string will be generated by imMakeCompressHelpString */
	  ARGFFULLHELP, 1, 1, ARGTSTRING },
};


#if IMTOOLSNWRITEEQUIVS == 0
ArgEquiv ImToolsWriteEquivs[1];
#else
ArgEquiv ImToolsWriteEquivs[IMTOOLSNWRITEEQUIVS] =
{
};
#endif

ArgOption ImToolsReadOptions[IMTOOLSNREADOPTIONS] =
{
	{ "map", "channel_map", "Read one channel into another one%end\
    -%option indicates that one channel in the file shall be mapped to a\n\
     different channel in memory.  \n\
        blue=red    Map a file's blue channel to the red channel in memory\n\
        gray=alpha  Map a file's gray channel to the alpha channel in memory\n\
        blue=none   Ignore the blue channel in the file\n\
    A map selection is always of the form <destination>=<source> where\n\
    <destination> and <source> are each one of the following: \n\
              red, green, blue, alpha, grey, index, index16, none\n\
    Multiple channels may be mapped by using the -%option option repeatedly. \n\
    e.g.  -%option blue=red -%option red=blue will swap the red and blue \n\
    channels.\n\
    ",
	  ARGFFULLHELP|ARGFMULTIPLE, 1, 1, ARGTSTRING },

	{ "format", "format_name", NULL,  /* help string will be created by imMakeFormatHelpString */
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "filecompression", "scheme", NULL, 
		/* Help string will be generated by imMakeCompressHelpString */
	  ARGFNONE, 1, 1, ARGTSTRING },

	{ "dpi", "dots_per_inch", "Specify the dpi of the incoming file%end\
    The %option option allows you to specify the dots per inch of an\n\
    incoming file.  Some file formats (such as postscript) do not have a\n\
    pretermined number of pixels.  Hence this option may be used to \n\
    affect the resolution of the incoming image.\n\
\n\
    The resolution of the image will be the number of dots per inch\n\
    times the dimensions of the page (in inches).\n\
\n\
    If such a format is used without specifying the dots per inch, \n\
    the dpi will default to 288.\n\
",
	  ARGFFULLHELP, 1, 1, ARGTINT },

	{ "pagewidth", "inches", "Specify the page width of an image%end\
    Some file formats (such as postscript) do not have a predetermined\n\
    size associated with the image.  The %option option allows you to \n\
    specify the page width of the incoming image when reading this type of\n\
    file.\n\
\n\
    If this option is omitted and such a file format is used, then the \n\
    page width is assumed to be 8.5 inches.\n\
",
	  ARGFFULLHELP, 1, 1, ARGTFLOAT },

	{ "pageheight", "inches", "Specify the page height of an image%end\
    Some file formats (such as postscript) do not have a predetermined\n\
    size associated with the image.  The %option option allows you to\n\
    specify the page height of the incoming image, when reading this type\n\
    of file. \n\
\n\
    If this option is omitted and such a file format is used, then the \n\
    page height is assumed to be 11 inches.\n\
",
	  ARGFFULLHELP, 1, 1, ARGTFLOAT },
};


#if IMTOOLSNREADEQUIVS == 0
ArgEquiv ImToolsReadEquivs[1];
#else
ArgEquiv ImToolsReadEquivs[IMTOOLSNREADEQUIVS] =
{
};
#endif

ArgOption ImToolsOtherOptions[IMTOOLSNOTHEROPTIONS] =
{
	{ "verbose", NULL, "Be verbose",
	  ARGFFULLHELP, 0, 0, ARGTNONE },
	  
#if defined(_USE_MMFS_FOR_VFB_OPTIONAL)
	{ "memory", "alloc_type", "Define the type of memory allocation scheme to use%end\
   The -%option option defines the type of the used memory allocation scheme:\n\
        ram	                    Allocates all required image memory in ram\n\
        file                    Allocates all required image memory in temporary\n\
                                files.\n\
\n\
   If no -%option option is given, all image memory is allocated in temporary\n\
   files.\n\
    ",
	  ARGFFULLHELP, 1, 1, ARGTSTRING },
#endif // defined(_USE_MMFS_FOR_VFB_OPTIONAL)
};


#if IMTOOLSNOTHEREQUIVS == 0
ArgEquiv ImToolsOtherEquivs[1];
#else
ArgEquiv ImToolsOtherEquivs[IMTOOLSNOTHEREQUIVS] =
{
};
#endif


/*
 *  FUNCTION
 *	ImToolsMergeOptions	-  merge option lists
 *	ImToolsMergeEquivs	-  merge equivalences lists
 *
 *  DESCRIPTION
 *	Typically used to merge the base Image Tools option and equivs lists
 *	with the tool's specific option and equivs lists.  Both functions
 *	create new lists consisting of the contents of the two source lists.
 *
 *	Each one also receives a character string which will be inserted before 
 *	the name of each of the options in the second list.
 *
 *	New memory is allocated for the second set of options passed to this 
 * 	function, but not for the first.
 *
 *	Note:  on an error, the routines exit the program in the standard way.
 */

int				/* Returns # of options in list	*/
#ifdef __STDC__
ImToolsMergeOptions( char* prefix, int nOptions1, ArgOption *options1, int nOptions2, ArgOption *options2, ArgOption **newoptions )
#else
ImToolsMergeOptions( prefix, nOptions1, options1, nOptions2, options2, newoptions )
	char* prefix;		/* prefix for each option       */
	int nOptions1;		/* Length of options1		*/
	ArgOption *options1;	/* 1st list of options		*/
	int nOptions2;		/* Length of options2		*/
	ArgOption *options2;	/* 2nd list of options		*/
	ArgOption **newoptions;	/* Returned new option list	*/
#endif
{
	ArgOption *pOpt;	/* Option list pointer		   */
	int n;			/* Length of new option list       */
	char newName[1024];     /* holds the new name of an option */

	n = nOptions1 + nOptions2;
	if (n==0)
		return 0;
	if ( (*newoptions = pOpt = (ArgOption *)malloc( n *
		sizeof( ArgOption ) )) == NULL )
	{
		perror( ImToolsProgram );
		exit( 1 );
	}

	for ( ; nOptions1; nOptions1-- )
		*pOpt++ = *options1++;
	for ( ; nOptions2; nOptions2-- )
	{
		*pOpt = *options2;   /* copy the structure */

		/*
		 * If this is the "format" option, then create a specific help
		 * message that lists all of the available formats.
		 */
		 if (strcmp(pOpt->arg_keyword,"format")==0)
		 {
			pOpt->arg_help = imMakeFormatHelpString(prefix);
		 }

		 /*
		  * If thie is the "filecompression" option then create a
		  * specific help message that lists all of the available
		  * compression schemes.
		  */
		 if (strcmp(pOpt->arg_keyword,"filecompression")==0)
		 {
			pOpt->arg_help = imMakeCompressHelpString(prefix);
		 }

		/* Insert the prefix */
		sprintf( newName,"%s%s",prefix,pOpt->arg_keyword);
		pOpt -> arg_keyword = _strdup(newName); 

		options2++;
		pOpt++;
	}

	return ( n );
}


int				/* Returns # of options in list	*/
#ifdef __STDC__
ImToolsMergeEquivs( char* prefix, int nEquivs1, ArgEquiv *equivs1, int nEquivs2, ArgEquiv *equivs2, ArgEquiv **newequivs )
#else
ImToolsMergeEquivs( prefix, nEquivs1, equivs1, nEquivs2, equivs2, newequivs )
	char* prefix; 		/* prefix for equivalences      */
	int nEquivs1;		/* Length of equivs1		*/
	ArgEquiv *equivs1;	/* 1st list of equivs		*/
	int nEquivs2;		/* Length of equivs2		*/
	ArgEquiv *equivs2;	/* 2nd list of equivs		*/
	ArgEquiv **newequivs;	/* Returned new equiv list	*/
#endif
{
	ArgEquiv *pEquiv;	/* Equiv list pointer		*/
	int n;			/* Length of new equiv list	*/
	char newName[1024];     /* New name with prefix         */

	n = nEquivs1 + nEquivs2;
	if (n==0)
		return 0;
	if ( (*newequivs = pEquiv = (ArgEquiv *)malloc( n * sizeof( ArgEquiv ) )) == NULL )
	{
		perror( ImToolsProgram );
		exit( 1 );
	}

	for ( ; nEquivs1; nEquivs1-- )
		*pEquiv++ = *equivs1++;
	for ( ; nEquivs2; nEquivs2-- )
	{
		*pEquiv = *equivs2;

		/* Insert the prefix */
		sprintf(newName,"%s%s",prefix,pEquiv->arg_keyword);
		pEquiv->arg_keyword = _strdup(newName);
		sprintf(newName,"%s%s",prefix,pEquiv->arg_equivkeyword);
		pEquiv->arg_equivkeyword = _strdup(newName);
		pEquiv++;
		equivs2++;
	}

	return ( n );
}





/*
 *  FUNCTION
 *	ImToolsIsFormat	-  check if a name is an image file format name
 *
 *  DESCRIPTION
 *	The image format table is scanned to find out if the given
 *	name is the name of a format.  If so, TRUE is returned.  Otherwise
 *	FALSE.
 */

int				/* Returns TRUE or FALSE	*/
#ifdef __STDC__
ImToolsIsFormat( char *name )
#else
ImToolsIsFormat( name )
	char *name;			/* Name to look up		*/
#endif
{
	ImFileFormat **pFmt;	/* Format list pointer		*/
	char        **pNames;		/* Format name list pointer	*/

	for ( pFmt = ImGetFileFormats(); *pFmt; pFmt++ )
	{
		pNames = (*pFmt)->format_names;
		for ( ; *pNames; pNames++ )
		{
			if ( strcmp( *pNames, name ) == 0 )
				return ( TRUE );
		}
	}
	return ( FALSE );
}


/*
 *  FUNCTION
 *	ImToolsChangeTagEntry	-  change a tag table entry
 *
 *  DESCRIPTION
 *	Used by the image tools primarily to change the "file name"
 *	entry in the flags table, this function replaces an entry in
 *	a table, or appends a new one if it isn't already there.
 */

void				/* Returns nothing		*/
#ifdef __STDC__
ImToolsChangeTagEntry( TagTable *table, char *tag, void *newvalue )
#else
ImToolsChangeTagEntry( table, tag, newvalue )
	TagTable *table;		/* Table to change		*/
	char     *tag;			/* Tag whose value is to change	*/
	void      *newvalue;		/* Pointer to new value		*/
#endif
{
	TagEntry *oldEntry;		/* Old tag table entry		*/
	TagEntry *newEntry;		/* New tag table entry		*/
	int       n;			/* Tag entry location		*/


	/*
	 *  Make a new tag table entry.
	 */
	newEntry = TagEntryAlloc( tag, IM_POINTER_TYPE, &newvalue );


	/*
	 *  Replace an existing entry or append the new one.
	 */
	oldEntry = TagTableQDirect( table, tag, 0 );
	if ( oldEntry == TAGENTRYNULL )
	{
		/* No entry in the flags table yet.  Add one.		*/
		TagTableAppend( table, newEntry );
	}
	else
	{
		/* Replace an existing entry.				*/
		n = TagEntryQNthEntry( oldEntry );
		TagTableReplace( table, n, newEntry );
	}
}





/*
 *  FUNCTION
 *	ImToolsErrorHandler	-  standard error code handler
 *	ImToolsInfoHandler	-  standard info handler
 *
 *  DESCRIPTION
 *	Print the error message unless it is one we want to handle specially.
 */

int				/* Returns status		*/
#ifdef __STDC__
ImToolsErrorHandler( int severity, int imerrno, char *message )
#else
ImToolsErrorHandler( severity, imerrno, message )
	int severity;			/* Error severity		*/
	int imerrno;			/* Error number			*/
	char *message;			/* Message to display		*/
#endif
{
	switch ( imerrno )
	{
	case IMENOTPOSSIBLE:
	case IMEMANYVFB:
	case IMENOVFB:
		/* We'll handle these specially later.			*/
		return ( 0 );
	}

	fprintf( stderr, message );
	return ( 0 );
}

int				/* Returns status		*/
#ifdef __STDC__
ImToolsInfoHandler( char *program, char *filename, char *message )
#else
ImToolsInfoHandler( program, filename, message )
	char *program;			/* Program name			*/
	char *filename;			/* File name			*/
	char *message;			/* Message to display		*/
#endif
{
	fprintf( stderr, "%s: %s: %s", program, filename, message );
	return ( 0 );
}





/*
 *  FUNCTION
 *	ImToolsOpen	-  open a file/stream & get its format
 *
 *  DESCRIPTION
 *	If the file name is a '-', use stdin or stdout, depending upon if
 *	we are reading or writing.  Check to see if a file format has been
 *	specified.
 *
 *	Otherwise open the file.  
 *
 *	The only time we specify a format when opening a file is if
 *	it was given on the command line.  Otherwise, we let the
 *	library's read routine try to discern the format.
 */

FILE *				/* Returns open file pointer	*/
#ifdef __STDC__
ImToolsOpen( char *fileName, char *flags, char *format, char *actualFileName, char *actualFormat )
#else
ImToolsOpen( fileName, flags, format, actualFileName, actualFormat )
	char *fileName;			/* Name of file to open		*/
	char *flags;			/* Open flags			*/
	char *format;			/* File format to use (if any)	*/
	char *actualFileName;		/* Processed file name		*/
	char *actualFormat;		/* Processed file format	*/
#endif
{
	FILE *fp;			/* File pointer			*/

	if ( fileName[0] == '-' && fileName[1] == '\0' )
	{
		if ( flags[0] == 'r' )
		{
			strcpy( actualFileName, "stdin" );
			fp = stdin;
		}
		else
		{
			fileName = "stdout";
			fp = stdout;
		}
		if ( format == NULL )
		{
			fprintf( stderr, "%s: Explicit format selection needed when using %s\n", ImToolsProgram, fileName );
			exit( 1 );
		}
		strcpy( actualFormat, format );
		return ( fp );
	}

	/*
	 *  Open the file.
	 */
	strcpy( actualFileName, fileName );
	if ( (fp = fopen( fileName, flags )) == NULL )
	{
		fprintf( stderr, "%s: Cannot open '%s'\n", ImToolsProgram, fileName );
		exit( 1 );
	}

	if (format)	
		strcpy(actualFormat,format);
	else
		actualFormat = NULL;

	return ( fp );
}





/*
 *  FUNCTION
 *	ImToolsFileRead	-  read in an image file
 *
 *  DESCRIPTION
 *	The file is opened.  The flags table is updated to include the
 *	name of the file.  The file is read in, and then closed.  Data
 *	read in is returned to the caller.
 */

void				/* Returns nothing		*/
#ifdef __STDC__
ImToolsFileRead( char *filename, char *format, TagTable *flags, TagTable *data )
#else
ImToolsFileRead( filename, format, flags, data )
	char     *filename;		/* Input file name		*/
	char     *format;		/* File format			*/
	TagTable *flags;		/* Read flags			*/
	TagTable *data;			/* Where to put the data	*/
#endif
{
	FILE     *fp;			/* File pointer			*/
	char      tmpFilename[1024];	/* Tmp string pointer		*/
	char      tmpFormat[1024];	/* Tmp format name		*/


	/*
	 *  Open the file.
	 *
	 *  'filename' is the name of the file, as given on the command-line.
	 *  If this is a '-', then we'll open stdin.  In this case the filename
	 *  returned by ImToolsOpen() will be different from that given.
	 *  
	 *  'format' is the image file format of the file, as given on the
	 *  command-line.  If not given at all, 'format' will be a '\0' string.
	 */
	fp = ImToolsOpen( filename, "r", format, tmpFilename, tmpFormat );

	strcpy( format,   tmpFormat );


	/*
	 *  If we're being verbose, tell the user what we're doing
	 */
	if ( ImToolsVerbose )
		fprintf( stderr, "%s: Reading '%s'\n",
			ImToolsProgram, tmpFilename );


	/*
	 *  Update the flags table to include the name of the file we're
	 *  reading.
	 */
	if ( flags != TAGTABLENULL )
	{
		ImToolsChangeTagEntry( flags, "file name", tmpFilename );
	}


	/*
	 *  Read in the file (might be stdin).
	 */
	if ( ImFileFRead( fp, format, flags, data ) == -1 )
	{
		switch (ImErrNo)
		{
			case IMEFORMATUNKNOWN : 
			fprintf( stderr, "%s: For information about how to select a format, type %s -help.\n", 
				ImToolsProgram, ImToolsProgram );

		}
		fprintf( stderr, "%s: Read failed\n", ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Close the file, if not stdin.
	 */
	if ( fp != stdin )
		fclose( fp );
}





/*
 *  FUNCTION
 *	ImToolsFileWrite-  write out an image file
 *
 *  DESCRIPTION
 *	The file is opened.  The flags table is updated to include the
 *	name of the file.  The file is written out, and then closed.
 */

void				/* Returns nothing		*/
#ifdef __STDC__
ImToolsFileWrite( char *filename, char *format, TagTable *flags, TagTable *data )
#else
ImToolsFileWrite( filename, format, flags, data )
	char    *filename;		/* Output file name		*/
	char    *format;		/* File format			*/
	TagTable *flags;		/* Write flags			*/
	TagTable *data;			/* Where to get the data	*/
#endif
{
	FILE     *fp;			/* File pointer			*/
	char      tmpFilename[1024];	/* Tmp string pointer		*/
	char      tmpFormat[1024];	/* Tmp format name		*/

	/*
	 *  Open the file.
	 *
	 *  'filename' is the name of the file, as given on the command-line.
	 *  If this is a '-', then we'll open stdout.  In this case the filename
	 *  returned by ImToolsOpen() will be different from that given.
	 *  
	 *  'format' is the image file format of the file, as given on the
	 *  command-line.  If not given at all, 'format' will be a '\0' string.
	 */
	fp = ImToolsOpen( filename, "w", format, tmpFilename, tmpFormat );
	strcpy( format,   tmpFormat );


	/*
	 *  If we're being verbose, tell the user what we're doing
	 */
	if ( ImToolsVerbose )
		fprintf( stderr, "%s: Writing '%s'\n",
			ImToolsProgram, tmpFilename );


	/*
	 *  Update the flags table to include the name of the file we're
	 *  writing.
	 */
	if ( flags != TAGTABLENULL )
		ImToolsChangeTagEntry( flags, "file name", tmpFilename );


	/*
	 *  Write the file.
	 *
	 *  The image tool's standard error handler handles most errors by
	 *  simply printing them to stderr.  Some errors, however, have
	 *  rather brief default error messages.  These are handled specially
	 *  here.
	 */
	if ( ImFileFWrite( fp, format, flags, data ) == -1 )
	{
		switch ( ImErrNo )
		{
		case IMENOTPOSSIBLE:
			fprintf( stderr, "%s: The %s format cannot support the output force options given.\n", ImToolsProgram, format );
			fprintf( stderr, "%s: You can get a list of what the format can support\n", ImToolsProgram );
			fprintf( stderr, "%s: by running:  imformats -long -%s\n", ImToolsProgram, format );
			if ( strcmp( tmpFilename, "stdout" ) != 0 )
				_unlink( tmpFilename );
			exit( 1 );

		case IMEMANYVFB:
			fprintf( stderr, "%s: The input file contained multiple images, however the\n", ImToolsProgram );
			fprintf( stderr, "%s: output %s format can only support 1 image per file.\n", ImToolsProgram, format );
			fprintf( stderr, "%s: Use the 'imsplit' tool to split the input file into\n", ImToolsProgram );
			fprintf( stderr, "%s: multiple output files before converting to the %s format.\n", ImToolsProgram, format );
			if ( strcmp( tmpFilename, "stdout" ) != 0 )
				_unlink( tmpFilename );
			exit( 1 );

		case IMENOVFB:
			fprintf( stderr, "%s: The input file contained no images suitable for output\n", ImToolsProgram );
			fprintf( stderr, "%s: in the %s format.\n", ImToolsProgram, format );
			if ( strcmp( tmpFilename, "stdout" ) != 0 )
				_unlink( tmpFilename );
			exit( 1 );

		case IMEFORMATUNKNOWN : 
			fprintf( stderr, "%s: For information about how to select a format, type %s -help.\n", 
				ImToolsProgram, ImToolsProgram );
			if ( strcmp( tmpFilename, "stdout" ) != 0 )
				_unlink( tmpFilename );
			exit( 1 );

		default:
			fprintf( stderr, "%s: Write failed\n", ImToolsProgram );
			if ( strcmp( tmpFilename, "stdout" ) != 0 )
				_unlink( tmpFilename );
			exit( 1 );
		}
	}


	/*
	 *  Close the file, if not stdout.
	 */
	if ( fp != stdout )
		fclose( fp );
}



/*
 *  FUNCTION
 *    ImToolsMakeStandardFlagsTable
 * 
 *  DESCRIPTION
 *    Create a brand new flags table containing:
 *	- an error handler
 *      - an info handler
 *      - the name of the invoking program
 *
 *   Don't call this function before calling ArgParse since this 
 *  function looks for 'verbose' on the command line!
 */

TagTable *
ImToolsMakeStandardFlagsTable()
{
	TagTable *flagsTable;		/* New flags table		*/
#ifdef __STDC__
	int (*infoHandler)( char*, char*, char*); /* Temporary handler func ptr	*/
	int (*errorHandler)( int, int, char*); /* Temporary handler func ptr	*/
#else
	int (*infoHandler)( );		/* Temporary handler func ptr	*/
	int (*errorHandler)( );		/* Temporary handler func ptr	*/
#endif


	if ( (flagsTable = TagTableAlloc( )) == TAGTABLENULL )
	{
		TagPError( ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Program name.
	 */
	TagTableAppend( flagsTable,
		TagEntryAlloc( "program name", IM_POINTER_TYPE, &ImToolsProgram ) );


	/*
	 *  Error handling:  print to stderr.
	 */
	errorHandler = ImToolsErrorHandler;
	TagTableAppend( flagsTable,
		TagEntryAlloc( "error handler", IM_POINTER_TYPE, &errorHandler ) );


	/*
	 *  Verbosity handling:  print to stderr.
	 */
	if ( ArgQNOccur( "verbose" ) > 0 )
	{
		ImToolsVerbose = TRUE;
		infoHandler = ImToolsInfoHandler;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "info handler", IM_POINTER_TYPE, &infoHandler ) );
	}


	return flagsTable;
}

/*
 *  FUNCTION
 *    ImToolsGetNameAndFormat
 *
 *  DESCRIPTION
 *    Parse the command line, and return the file name and format,
 *  (if explicitly specified) corresponding to the given prefix.
 *
 *  Note that if multiple files with this prefix are given then
 *  they will all be assumed to be the same format.  i.e.
 *  	imcat -informat ras one two three -outfile out.gif
 *  implies that "one", "two", and "three" are all Sun
 *  Rasterfile's.
 *  This is consistent with the use of -outindex or -outclt.
 *  i.e. These flags mean that all of the output files should 
 *  be indexed or have clt's.
 *
 *  The index parameter is passed to this routine to indicate the
 *  index of the file we are interested in.  For instance, in
 *  the above example, passing index 0 would return "one" and
 *  "ras" as the name and format of the file.  Passing 1 would
 *  return "two" and "ras".  And so on.
 */

int  /* Returns status */
#ifdef __STDC__
ImToolsGetNameAndFormat( char* prefix , int index, char* retName, char* retFormat)
#else
ImToolsGetNameAndFormat( prefix, index,  retName, retFormat)
char* prefix;
int index;
char* retName;
char* retFormat;
#endif
{
	char formatFlag[1024]; /* the name of the flag for the format        */
	char fileFlag[1024];   /* the name of the flag flag for the filename */

	/*
	 *  Get the file name from the command line.
	 *  ( It's okay not to have a file name.  Lack of mandatory flags will be
	 *  caught by the argument parsing package. )
	 */

	*retFormat = '\0';
	*retName   = '\0';
	strcpy(fileFlag,prefix);
	strcat(fileFlag,"file");
	if ( ArgQNOccur( fileFlag ) > index )
	{
		strcpy(retName, ArgQValue( fileFlag, index, 0 )->arg_s );
	}   

	/*
	 * Get the format
	 */
	 strcpy(formatFlag,prefix);
	 strcat(formatFlag,"format");
	 if ( ArgQNOccur( formatFlag ) > index )
	 {
		strcpy(retFormat, ArgQValue( formatFlag, index, 0 )->arg_s );
	 }   


	return (1);

}

/*
 *  FUNCTION
 *    ImToolsAddReadWriteFlags 
 *
 *  DESCRIPTION
 *    Add file i/o flags to a tag table by
 *   parsing the command line.
 *
 *   The flags searched for will have the parameter
 *  'prefix' inserted before them.  e.g. "out" will
 *  search for "outclt", "outindex", etc..
 */

int  		/* returns status */
#ifdef __STDC__
ImToolsAddReadWriteFlags (TagTable* flagsTable, char* prefix )
#else
ImToolsAddReadWriteFlags (flagsTable, prefix)
TagTable* flagsTable;	/* Flags table to which we'll append stuff */
char* prefix;		/* prefix for relavant arguments (eg "in") */
#endif
{
	char* tmp;			/* temporary char *                          */
	char flagName[1024];            /* Always has prefix at the beginning        */
	int prefixLength;               /* Length of prefix string                   */
	int i, itmp;                    /* temporary integers                        */
	int nOccur;                     /* Number of occurences of a flag            */
	char channel1[510];		/* Hold a channel name for error checking    */
	char channel2[510];		/* Hold a channel name for error checking    */
	char *ptr; 			/* temporary char* pointer                   */
	float ftmp;			/* holds a float                             */

	/*
	 * Set up a nice dummy variable with 
	 * the prefix at the beginning to make
	 * things cleaner later on
	 */
	strcpy(flagName, prefix);
	prefixLength = strlen(prefix);
	
	/*
	 * Channel mapping.  Add all requests to the table.
	 */
	strcpy( flagName + prefixLength, "map");
	if ( (nOccur = ArgQNOccur( flagName)) > 0)
	{
		for (i=0;i<nOccur;i++)
		{
			tmp =  ArgQValue( flagName, i, 0 )->arg_s;
			/*
			 * Check for valid request
			 * Store the string in mapRequest, which has
			 * lots of space allocated to it.
			 */
			imStringToLower(tmp);
			strcpy(channel1,tmp);
			ptr = strchr(channel1, '=');
			if (ptr!=NULL)
			{
				*ptr = '\0';
				strcpy(channel2,ptr+1);
			}
			if (ptr==NULL || !imValidateChannel(channel1) || !imValidateChannel(channel2))
			{
				fprintf( stderr, "%s:  Invalid channel mapping request.\n", ImToolsProgram );
				fprintf( stderr, "          A map request must be of the form <dest>=<source>\n");
				fprintf( stderr, "          where <dest> and <source> are each one of :\n");
				fprintf( stderr, "               red, green, blue, alpha, grey, index, index16, none\n\n");
				fprintf( stderr, "          For instance, \n");
				fprintf(stderr,  "               -inmap blue=green  copies the green channel to the blue channel\n\n");
				exit( 1 );
			}
			if ((tmp = (char*)calloc(30, sizeof(char)))==NULL)
			{
				perror( ImToolsProgram );
				exit( 1 );
			}
			sprintf(tmp,"%s=%s",channel1,channel2);
			TagTableAppend( flagsTable,
				TagEntryAlloc( "channel map request", IM_POINTER_TYPE, &tmp ) );
		}
	}


	/*
	 *  Type forcing.  Check for conflicting options.
	 */
	strcpy(flagName + prefixLength, "index");
	i = 0;
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		itmp = IMTYPEINDEX;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image type request", IM_INT_TYPE, &itmp ) );
	}
	strcpy(flagName + prefixLength, "rgb" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		itmp = IMTYPERGB;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image type request", IM_INT_TYPE, &itmp ) );
	}
	if ( i > 1 )
	{
		fprintf( stderr, "%s:  Only one of -%sindex or -%srgb may be given\n", ImToolsProgram,
			prefix, prefix);
		exit( 1 );
	}


	/*
	 *  Output mono thresholding request
	 */
	strcpy(flagName + prefixLength, "threshold" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		itmp = (int) ArgQValue( flagName, 0, 0 )->arg_i;
		if (-255 > itmp || 255 < itmp)
		{
			fprintf( stderr, "%s:  Mono threshold should be between -255 and 255.\nNegative numbers invert the image.\n", ImToolsProgram);
			exit( 1 );
		}
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image mono threshold", IM_INT_TYPE, &itmp ) );
	}

	/*
	 *  Force swapping of bitorder
	 */
	strcpy(flagName + prefixLength, "swapbitorder" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
	int itmp = 1;
	
		TagTableAppend( flagsTable,
			TagEntryAlloc( "force bitorder swapping", IM_INT_TYPE, &itmp ) );
	}

	/*
	 *  Output CLT forces.  Check for conflicting options.
	 */
	strcpy(flagName + prefixLength, "clt" );
	i = 0;
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		itmp = IMCLTYES;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image clt request", IM_INT_TYPE, &itmp ) );
	}
	strcpy(flagName + prefixLength, "noclt" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		itmp = IMCLTNO;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image clt request", IM_INT_TYPE, &itmp ) );
	}
	if ( i > 1 )
	{
		fprintf( stderr, "%s:  Only one of -%sclt or -%snoclt may be given\n", ImToolsProgram,
			prefix, prefix);
		exit( 1 );
	}


	/*
	 *  Output alpha plane forces.  Check for conflicting options.
	 */
	i = 0;
	strcpy(flagName + prefixLength, "alpha" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		itmp = IMALPHAYES;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image alpha request", IM_INT_TYPE, &itmp ) );
	}
	strcpy(flagName + prefixLength, "noalpha" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		itmp = IMALPHANO;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image alpha request", IM_INT_TYPE, &itmp ) );
	}
	if ( i > 1 )
	{
		fprintf( stderr, "%s:  Only one of -%salpha or -%snoalpha may be given\n", 
			ImToolsProgram, prefix, prefix );
		exit( 1 );
	}


	/*
	 *  Output channel number forcing.
	 */
	strcpy(flagName + prefixLength, "nchan" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		itmp = (int) ArgQValue( flagName, 0, 0 )->arg_i;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image channel number request", IM_INT_TYPE, &itmp ) );
	}


	/*
	 *  Output channel depth forcing.
	 */
	strcpy(flagName + prefixLength, "chandepth" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		itmp = (int) ArgQValue( flagName, 0, 0 )->arg_i;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image channel depth request", IM_INT_TYPE, &itmp ) );
	}


	/*
	 *  Output interleaving forcing.  Check for good scheme name.
	 */
	strcpy(flagName + prefixLength, "interleave" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		tmp = ArgQValue( flagName, 0, 0 )->arg_s;
		i = strlen( tmp );
		if ( strncmp( tmp, "none", i ) == 0 )
			itmp = IMINTERNONE;
		else if ( strncmp( tmp, "line", i ) == 0 )
			itmp = IMINTERLINE;
		else if ( strncmp( tmp, "plane", i ) == 0 )
			itmp = IMINTERPLANE;
		else
		{
			fprintf( stderr, "%s:  Unknown RGB interleave scheme.  Use one of:\n",
				ImToolsProgram );
			fprintf( stderr, "        'none'  Uninterleaved RGB (RGBRGBRGB...)\n" );
			fprintf( stderr, "        'line'  Scanline-interleaved RGB (RR..GG..BB..RR..GG..BB...)\n" );
			fprintf( stderr, "        'plane' Plane-interleaved RGB (RRR..GGG..BBB...)\n" );
			exit( 1 );
		}
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image interleave request", IM_INT_TYPE, &itmp ) );
	}


	/*
	 *  Output grouping forcing.  Check for good scheme name.
	 */
	strcpy(flagName + prefixLength, "group" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		tmp = ArgQValue( flagName, 0, 0 )->arg_s;
		i = strlen( tmp );
		if ( strncmp( tmp, "scanlines", i ) == 0 )
			itmp = IMGROUPSCANLINES;
		else if ( strncmp( tmp, "tiles", i ) == 0 )
			itmp = IMGROUPTILES;
		else
		{
			fprintf( stderr, "%s:  Unknown grouping scheme.  Use one of:\n",
				ImToolsProgram );
			fprintf( stderr, "        'scanlines'  Group values into scanlines\n" );
			fprintf( stderr, "        'tiles'      Group values into tiles\n" );
			exit( 1 );
		}
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image group request", IM_INT_TYPE, &itmp ) );
	}

	/*
	 *  Output compression forcing.  Check for good scheme name.
	 */
	strcpy(flagName + prefixLength, "compress" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		tmp = ArgQValue( flagName, 0, 0 )->arg_s;
		i = strlen( tmp );
		if ( strncmp( tmp, "none", i ) == 0 )
			itmp = IMCOMPNONE;
		else if ( strncmp( tmp, "rle", i ) == 0 )
			itmp = IMCOMPRLE;
		else if ( strncmp( tmp, "ascii", i ) == 0 )
			itmp = IMCOMPASCII;
		else if ( strncmp( tmp, "pb", i ) == 0 )
			itmp = IMCOMPPB;
		else if ( strncmp( tmp, "packbits", i ) == 0 )
			itmp = IMCOMPPB;
		else if ( strncmp( tmp, "mac", i ) == 0 )
			itmp = IMCOMPPB;
		else if ( strncmp( tmp, "lzw", i ) == 0 )
			itmp = IMCOMPLZW;
		else if ( strncmp( tmp, "dct", i ) == 0 )
			itmp = IMCOMPDCT;
		else if ( strncmp( tmp, "jpeg", i ) == 0 )
			itmp = IMCOMPDCT;
		else if ( strncmp( tmp, "ccittrle", i ) == 0 )
			itmp = IMCOMPCCITTRLE;
		else if ( strncmp( tmp, "ccitt3", i ) == 0 )
			itmp = IMCOMPCCITTFAX4;
		else if ( strncmp( tmp, "ccitt4", i ) == 0 )
			itmp = IMCOMPCCITTFAX4;
		else
		{
			fprintf( stderr, "%s:  Unknown image compression scheme.  Use one of:\n",
				ImToolsProgram );
			fprintf( stderr, "        'none'     Uncompressed\n" );
			fprintf( stderr, "        'lzw'      Limpel-Ziv & Welsh compressed\n" );
			fprintf( stderr, "        'mac'      Macintosh PackBits\n" );
			fprintf( stderr, "        'pb'       Macintosh PackBits (same as 'mac')\n" );
			fprintf( stderr, "        'packbits' Macintosh PackBits (same as 'mac')\n" );
			fprintf( stderr, "        'rle'      Run-length encoded\n" );
			fprintf( stderr, "        'dct'      Discrete Cosine Transform\n" );
			fprintf( stderr, "        'jpeg'     Discrete Cosine Transform (same as 'dct')\n" );
			fprintf( stderr, "        'ascii'    Ascii compression\n");
			fprintf( stderr, "        'ccittrle' CCITT Rle compression\n");
			fprintf( stderr, "        'ccitt3'   CCITT Fax 3 compression\n");
			fprintf( stderr, "        'ccitt4'   CCITT Fax 4 compression\n");
			exit( 1 );
		}
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image compression request", IM_INT_TYPE, &itmp ) );
	}


	/*
	 *  Output quality forcing
	 */
	strcpy(flagName + prefixLength, "quality" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		itmp = (int) ArgQValue( flagName, 0, 0 )->arg_i;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image compression quality request", IM_INT_TYPE, &itmp ) );
	}

	/*
	 *  Transparency
	 */

	i = 0;
	strcpy(flagName + prefixLength, "transparency" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		if (!(tmp = (char *)malloc( sizeof( char ) * 15)))
		{
			perror( ImToolsProgram );
			exit( 1 );
		}
		sprintf(tmp,"most common");
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image transparency request", IM_POINTER_TYPE, &tmp ) );
	}
	strcpy(flagName + prefixLength, "transparencyrgb" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		if (!(tmp = (char *)malloc( sizeof( char ) * 15)))
		{
			perror( ImToolsProgram );
			exit( 1 );
		}
		sprintf(tmp,"rgb=%d %d %d", 
			ArgQValue( flagName, 0, 0 )->arg_i,
			ArgQValue( flagName, 0, 1 )->arg_i,
			ArgQValue( flagName, 0, 2 )->arg_i );

		TagTableAppend( flagsTable,
			TagEntryAlloc( "image transparency request", IM_POINTER_TYPE, &tmp ) );
	}
	strcpy(flagName + prefixLength, "transparencyindex" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		i++;
		if (!(tmp = (char *)malloc( sizeof( char ) * 15)))
		{
			perror( ImToolsProgram );
			exit( 1 );
		}
		sprintf(tmp,"index=%d", ArgQValue( flagName, 0, 0 )->arg_i );

		TagTableAppend( flagsTable,
			TagEntryAlloc( "image transparency request", IM_POINTER_TYPE, &tmp ) );
	}
	if ( i > 1 )
	{
		fprintf( stderr, 
		"%s:  Only one of -%stransparency, -%stransparencyrgb, and -%stransparencyindex may be given\n", 
			ImToolsProgram, prefix, prefix, prefix );
		exit( 1 );
	}

	strcpy(flagName + prefixLength, "filecompression" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		tmp = ArgQValue( flagName, 0, 0 )->arg_s;
		if (ImFileFindCompressionScheme(tmp)==NULL)
		{
			fprintf( stderr, "%s:  Unknown file compression scheme.\n",
				ImToolsProgram );
			fprintf( stderr,"           Please type %s -help -%s for a list of schemes.\n",
				ImToolsProgram, flagName);
			exit( 1 );
		}
		else
			TagTableAppend( flagsTable,
				TagEntryAlloc( "file compression", IM_POINTER_TYPE, &tmp ) );
	}


	/*
	 *  Dots per inch 
	 */
	strcpy(flagName + prefixLength, "dpi" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		itmp = (int) ArgQValue( flagName, 0, 0 )->arg_i;
		TagTableAppend( flagsTable,
			TagEntryAlloc( "image dpi request", IM_INT_TYPE, &itmp ) );
	}


	/*
	 *  page width
	 */
	strcpy(flagName + prefixLength, "pagewidth" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		ftmp = (float)(ArgQValue( flagName, 0, 0 )->arg_f);
		TagTableAppend( flagsTable,
			TagEntryAlloc( "page width request", IM_FLOAT_TYPE, &ftmp ) );
	}


	/*
	 *  page height
	 */
	strcpy(flagName + prefixLength, "pageheight" );
	if ( ArgQNOccur( flagName ) > 0 )
	{
		ftmp = (float)(ArgQValue( flagName, 0, 0 )->arg_f);
		TagTableAppend( flagsTable,
			TagEntryAlloc( "page height request", IM_FLOAT_TYPE, &ftmp ) );
	}

	return ( 1);

}

/*
 * FUNCTION
 *   validChannel
 *
 * DESCRIPTION
 *   determine whether or not the argument
 * is the name of a channel.  If it is,
 * copy the full name (i.e. abbreviations are
 * okay) into the string.
 */
 
static int  /* returns 1 if it is, 0 if it ain't */
#ifdef __STDC__
imValidateChannel(char* str)
#else
imValidateChannel(str)
char* str;
#endif
{
 int n;     /* length of our string */

 n = strlen(str);
 if (n==0) return 0;
 if (strncmp(str,"red",n)==0)      { strcpy (str,"red"); return 1; }
 if (strncmp(str,"green",n)==0)    { strcpy (str,"green"); return 1; }
 if (strncmp(str,"blue",n)==0)     { strcpy (str,"blue"); return 1; }
 if (strncmp(str,"alpha",n)==0)    { strcpy (str,"alpha"); return 1; }
 if (strncmp(str,"grey",n)==0)     { strcpy (str,"grey"); return 1; }
 if (strncmp(str,"gray",n)==0)     { strcpy (str,"grey"); return 1; }
 if (strncmp(str,"index",n)==0)    { strcpy (str,"index"); return 1; }
 if (strncmp(str,"index16",n)==0)  { strcpy (str,"index16"); return 1; }
 if (strncmp(str,"none",n)==0)     { strcpy (str,"none"); return 1; }
 return 0;
}

/*
 * FUNCTION
 *   imStringToLower
 *
 * DESCRIPTION
 *   convert a string into lower case
 */

static void
#ifdef __STDC__
imStringToLower(char* str)
#else
imStringToLower(str)
char* str;
#endif
{
 char* ptr;     /* pointer to traverse string */

 for (ptr = str; *ptr!='\0'; ptr++)
 {
 	if ((*ptr)>='A' && (*ptr)<='Z')
 		(*ptr) -= 'A' - 'a';
 }
}


/* FUNCTION
 * 	ImToolsMergeHelp
 *
 * DESCRIPTION
 *	Allocate new memory and concatenate two strings.
 */

char*	
#ifdef __STDC__
ImToolsMergeHelp(char* first, char* second)
#else
ImToolsMergeHelp(first, second)
char* first;
char* second;
#endif
{
	char* tmp;

	if ( (tmp = (char *)malloc( sizeof( char ) * (strlen( first ) +
		strlen( second ) + 1) )) == NULL )
	{
		perror( ImToolsProgram );
		exit( 1 );
	}
	strcpy( tmp, first );
	strcat( tmp, second );
	return tmp;
}



/*
 * FUNCTION
 *    imMakeFormatHelpString
 *
 * DESCRIPTION
 *    Create a help string that contains a list of all of the
 * image formats, as well as some general information about
 * them.
 */

static char *
#ifdef __STDC__
imMakeFormatHelpString(char* prefix)
#else
imMakeFormatHelpString(prefix)
char* prefix;
#endif
{
	char *buf;			/* Return message                */
	char formatBuf[1024];		/* Equivalent format names       */
	char lineBuf[1024];		/* A line of text                */
	ImFileFormat **pFmt;		/* Points to the list of formats */
	int i; 				/* index                         */
	
	buf = (char *)malloc( sizeof( char ) * 12000);
	if (!buf)
	{
		perror( ImToolsProgram );
		exit( 1 );
	}
	sprintf(buf,"Specify the format of the -%sfile%%end",prefix);

	strcat(buf, "The -%option option allows you to give the name of an image file format.\n");
	sprintf(lineBuf,"The format is applied to any file given with the -%sfile option.\n",prefix);
	strcat(buf,lineBuf);
	strcat(buf,"The following are acceptable format names:\n\n");
	for ( pFmt = ImGetFileFormats(); *pFmt; pFmt++ )
	{
		strcpy(formatBuf,(*pFmt)->format_names[0]);
		i = 1;
		while ((*pFmt)->format_names[i])
		{
			strcat(formatBuf,", ");
			strcat(formatBuf,(*pFmt)->format_names[i]);
			i++;
		}
		if (strlen(formatBuf)<35)
			sprintf(lineBuf,"%5s%-30s%s\n"," ",formatBuf,(*pFmt)->format_help);
		else
			sprintf(lineBuf,"%5s%-30s\n%35s%s\n"," ",formatBuf," ",(*pFmt)->format_help);
		strcat(buf,lineBuf);
	}
	strcat(buf,"\nIf you'd like more information about one of the formats listed above,\n");
	strcat(buf,"you may...\n");
	strcat(buf,"      - use the 'imformats' command\n");
	strcat(buf,"      - see the man pages (e.g. man imras describes the ras format)\n");
	strcat(buf,"      - refer to the source code (e.g. imras.c implements ras reading\n");
	strcat(buf,"        and writing)");
	return buf;
}



/*
 * FUNCTION
 *    imMakeCompressHelpString
 *
 * DESCRIPTION
 *    Create a help string that contains a list of all of the
 * image schemes, as well as some general information about
 * them.
 */

static char *
#ifdef __STDC__
imMakeCompressHelpString(char* prefix)
#else
imMakeCompressHelpString(prefix)
char* prefix;
#endif
{
	char *buf;			/* Return message                */
	char formatBuf[1024];		/* Equivalent scheme names       */
	char lineBuf[1024];		/* A line of text                */
	ImCompressScheme **pScheme;	/* Points to the list of schemes */
	int i; 				/* index                         */
	
	buf = (char *)malloc( sizeof( char ) * 2000);
	if (!buf)
	{
		perror( ImToolsProgram );
		exit( 1 );
	}
	sprintf(buf,"Specify compression for the -%sfile%%end",prefix);

	strcat(buf, "The -%option option allows you to give the name of a compression scheme.\n");
	sprintf(lineBuf,"The scheme is applied to any file given with the -%sfile option.\n",prefix);
	strcat(buf,lineBuf);
	strcat(buf,"The following are acceptable scheme names:\n\n");
	for ( pScheme = ImGetCompressSchemes(); *pScheme; pScheme++ )
	{
		strcpy(formatBuf,(*pScheme)->compress_suffixes[0]);
		i = 1;
		while ((*pScheme)->compress_suffixes[i])
		{
			strcat(formatBuf,", ");
			strcat(formatBuf,(*pScheme)->compress_suffixes[i]);
			i++;
		}
		if (strlen(formatBuf)<35)
			sprintf(lineBuf,"%5s%-30s%s\n"," ",formatBuf,(*pScheme)->compress_name);
		else
			sprintf(lineBuf,"%5s%-30s\n%35s%s\n"," ",formatBuf," ",(*pScheme)->compress_name);
		strcat(buf,lineBuf);
	}
   	sprintf(lineBuf,"\nThis option may be used in conjuction with the -%sformat option to specify\n",prefix);
	strcat(buf,lineBuf);
   	strcat(buf,"both the format of the output file, and the file compression scheme to use.");
	return buf;
}

