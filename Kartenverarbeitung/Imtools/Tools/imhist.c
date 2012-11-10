/**
 **     $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imhist.c,v 1.11 1995/06/29 01:05:35 bduggan Exp $
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

#define HEADER  "    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imhist.c,v 1.11 1995/06/29 01:05:35 bduggan Exp $"

/**
 **  FILE
 **	imhist.c	-  Compute a histogram of an image
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 ** 	imhist computes a histogram of selected fields in an image.
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
 **	toolFlagsTable	v  a table for the storage of read flags
 **
 **	toolFill	v  Flip direction 
 **	toolFillMessage	v  Flip diagnostic message 
 **
 **	toolInit	f  initialize things for the tool
 **
 **  HISTORY
 **	$Log: imhist.c,v $
 **	Revision 1.11  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.10  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.9  1995/06/15  19:18:11  bduggan
 **	removed some useless vars
 **
 **	Revision 1.8  1995/05/18  00:02:32  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.7  1995/01/11  00:01:58  bduggan
 **	changed "wether" to "whether"
 **
 **	Revision 1.6  94/10/03  15:49:29  nadeau
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
 **
 **/

#include "imtools.h"
#include "iminternal.h"

/**
 **  CODE CREDITS
 **
 **  	Custom development, Dave Nadeau, San Diego Supercomputer Center, 1992.
 **	Custom development, Chris Groening, San Diego Supercomputer Center, 1992.
 **
 **/


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
	/* command name */		"imhist",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command computes a histogram of pixel values for all pixel fields, or\n\
just those selected on the command-line (RGB, or just red, or just hue and\n\
saturation, etc.).  Histogram computation produces a list of unique pixel\n\
field values and the number of times each occurs in the input images.  The\n\
list is written to stdout or an output text file, together with header\n\
statistics on the image.\n\
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
    Compute a histogram based only on the red field of pixels:\n\
        %command image.rgb -red histo.text\n\
    Compute a histogram based only on the color index field of pixels:\n\
        %command image.rgb -index histo.text\n\
    Compute a histogram based upon the red, green, and blue fields together:\n\
        %command image.rgb -red -green -blue histo.text\n\
    Compute a histogram based upon the hue, saturation, and intenstity:\n\
        %command image.rgb -hue -intensity -saturation histo.text\n\
";

static char *toolFullHelp = "\n\
Files:\n\
    -infile selects the file whose images are to be used in the computation\n\
    of a pixel color occurrence histogram.  -outfile selects the text file\n\
    into which to write the histogram data.  The input file is unaltered.\n\
    If no output file is given, histogram data is written to stdout.\n\
\n\
Histograms:\n\
    Histograms are computed by counting the number of occurrences of each\n\
    unique pixel color combination in the image.  By default, histograms are\n\
    computed on the combination of pixel fields present in the image, such as\n\
    color indexes, or RGB values, or RGB-Alpha values.\n\
\n\
    The histogram may be computed on a subset of fields, or upon the virtual\n\
    fields Hue, Saturation, and Intensity, by specifically naming the fields\n\
    on the command line using one or more of:  -mono, -index, -red, -green,\n\
    -blue, -hue, -saturation, -intensity, and -alpha.  Color spaces cannot\n\
    be mixed (such as -red and -hue, or -mono and -green).\n\
\n\
    Histogram computation time and memory requirements can become very large\n\
    when working with large images and/or images with large numbers of unique\n\
    color combinations.\n\
\n\
Output Options:\n\
    By default, output includes a header giving min and max values, followed\n\
    by a sorted list of pixel occurrence counts.  Header information may be\n\
    suppressed with the -outnoheader option.  Computing of histogram data\n\
    may be suppressed (if all you want is the header info) with the\n\
    -outnohistogram option.  Sorting of occurrence values may be suppressed\n\
    with the -outnosort option.\n\
\n\
Image File Formats and Filenames:\n\
    By default, input file image file formats are determined by the file's\n\
    magic number, or the filename extension (like .hdf for HDF files, or .pix\n\
    for PIX files).\n\
\n\
    To override the default, explicit format names may precede the filename,\n\
    such as -hdf for an HDF file, or -pix for a PIX file.\n\
\n\
    A single dash ('-') for an input filename indicates stdin.  When using\n\
    stdin, an explicit format name is necessary.\n\
\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

#define IM_TOOLNOPTIONS	14
static ArgOption toolOptions[IM_TOOLNOPTIONS] =
{
	{ "infile", "image_filename", "Specify an input image file name%end\
    The -%option argument specifies the name of the input file.              \n\
                                                                             \n\
    The file's format may be specified with the -informat flag.             \n\
                                                                             \n\
    A single dash ('-') for the filename indicates stdin.  When using stdin, \n\
    an explicit format name may be necessary.                                 \
",
	  ARGFIMPKEYWORD | ARGFREQUIRED, 1, 1, ARGTSTRING },

	{ "outfile", "text_filename", "Specify an output text file name%end\
    The -outfile option indicates that the histogram results should be stored\n\
    in the given text file.",
	  ARGFIMPKEYWORD, 1, 1, ARGTSTRING },

	{ "outnoheader", NULL, "Suppress output of header data%end\
    The -outnoheader flag indicates that you'd prefer not to see the\n\
    name of the file, resolution, number of pixels, number of combinations,\n\
    and range of pixels.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "outnosort", NULL, "Suppress sorting of occurrence values%end\
   Normally,  values are sorted from most number of occurences to least\n\
   number of occurences.  If you don't want the values to be sorted this way,\n\
   use the -outnosort option.'",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "outnohistogram", NULL, "Suppress output of histogram data%end\
   If you'd just like to see the name of the file, resolution, pixel count, and\n\
   pixel combinations, then use the -outnohistogram option.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "index", NULL, "Compute on color indexes%end\
   The -%option option will compute the histogram on the index field of the\n\
   incoming file.  That is, it will group the pixels according to the value\n\
   of their indexes.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "mono", NULL, "Compute on monochrome values%end\
   The -%option option will compute the histogram on the mono field of the\n\
   incoming file.  That is, it will group the pixels according to their\n\
   monochrome value.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "red", NULL , "Compute on red values%end\
   The -%option option will compute the histogram on the red field of the\n\
   incoming file.  That is, it will group the pixels according to the value\n\
   of their red component.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "green", NULL , "Compute on green values%end\
   The -%option option will compute the histogram on the green field of the\n\
   incoming file.  That is, it will group the pixels according to the value\n\
   of their green component.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "blue", NULL , "Compute on blue values%end\
   The -%option option will compute the histogram on the green field of the\n\
   incoming file.  That is, it will group the pixels according to the value\n\
   of their green component.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "hue", NULL , "Compute on hue values%end\
   The -%option option will compute the histogram on the (virtual) hue field of\n\
   the incoming file.  That is, it will group the pixels according to their hues.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "saturation", NULL , "Compute on saturation values%end\
   The -%option option will compute the histogram on the (virtual) saturation\n\
   field of the incoming file.  That is, it will group the pixels according to\n\
   their saturations.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "intensity", NULL , "Compute on intensity values%end\
   The -%option option will compute the histogram on the (virtual) intensity\n\
   field of the incoming file.  That is, it will group the pixels according to\n\
   their intensities.",
	  ARGFNONE, 0, 0, ARGTNONE },

	{ "alpha", NULL , "Compute on alpha values%end\
   The -%option option will compute the histogram on the alpha field of the\n\
   incoming file.  That is, it will group the pixels according to the value\n\
   of their alpha component.",
	  ARGFNONE, 0, 0, ARGTNONE},

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
 *	toolFlagsTable	-  a table for the storage of read flags
 *
 *  DESCRIPTION
 *	Data held by these variables is used throughout the tool.
 */

static char      toolInFilename[1024];	/* Input file name		*/
static char      toolInFormat[1024];	/* Input file's format name	*/

static char      toolOutFilename[1024];/* Output file name		*/

static TagTable *toolInTable;		/* Data tag table		*/
static TagTable *toolFlagsTable;	/* Flags tag table		*/

static int	  toolField;		/* What fields to change 	*/
static int	  toolSort;		/* Whether to sort histogram or not*/
static int	  toolHeader;		/* Whether to display header or not*/
static int	  toolOutHist;		/* whether to do a histogram	*/





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Control things:
 *		-  Initialize things (parse arguments and set up tables).
 *		-  Read in the input file (put data into data table).
 *		-  Fill each image.
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

#define IM_DOSTAT( vfb, outFp, histFields, field, name )			\
{									\
	/* Compute statistics for a field.				*/\
	if ( (histFields) & (field) )					\
	{								\
		float data[IMMAXNUMSTATS];	/* Statistical data	*/\
		ImVfbStat( (vfb), (field), data );			\
		fprintf( (outFp), "%s:\n", (name) );			\
		fprintf( (outFp), "    %-20s %f\n",			\
			"Maximum:", data[IMMAXIMUM] );			\
		fprintf( (outFp), "    %-20s %f\n",			\
			"Minimum:", data[IMMINIMUM] );			\
		fprintf( (outFp), "    %-20s %d\n",			\
			"Unique Values:", (int)data[IMUNIQUEVAL] );	\
	}								\
}

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
	int         i,j;		/* Counter			*/

	TagEntry   *dataEntry;		/* Entry from data table	*/
	FILE	   *outFp;		/* Output file pointer		*/

	ImVfb      *sourceVfb;		/* Source image			*/
	ImVfb      *tmpVfb;		/* Temporary VFB pointer	*/
        ImHistTable *histTable;		/* return data structure        */
	int	   fieldMask;		/* fieldmask for incoming image */
	int	   requiredFields;	/* Fields required of VFB	*/

	int	   histFields;		/* Fields on which to do histogram*/
	int    doHeader;		/* Output the header?		*/
	int	   doHist;		/* Output the histogram?	*/

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
	ImToolsFileRead( toolInFilename, toolInFormat, toolFlagsTable,
		toolInTable );


        /*
         *  Check for errors
         *      -  no input images
         */
	nInVfb = TagTableQNEntry( toolInTable, "image vfb" );
	if ( nInVfb == 0 )
	{
		fprintf( stderr, "%s: Input file contains no images!\n",                                ImToolsProgram );
		exit( 1 );
	}


	/*
	 *  Open the output file.
	 */
	if ( *toolOutFilename != '\0' )
	{
		outFp = fopen( toolOutFilename, "w" );
		if ( outFp == NULL )
		{
			fprintf( stderr, "%s: %s:  Cannot open output file\n", ImToolsProgram, toolOutFilename );
			perror( ImToolsProgram );
			exit( 1 );
		}
	}
	else
		outFp = stdout;


	/*
	 *  Compute the Histogram!
	 *	-  Walk the data table looking for images.  For each one found,
	 *	   get the VFB and compute an occurrence histogram on the
	 *	   selected fields.
	 */
        for ( j = 0; j < nInVfb; j++ )
        {
                /*
                 *  Get the next image out of the data table.
                 */
                dataEntry = TagTableQDirect( toolInTable, "image vfb", j );
                TagEntryQValue( dataEntry, &sourceVfb );


		fieldMask = ImVfbQFields( sourceVfb );
		histFields = toolField;

		/*
		 *  If an explicit field list was not given on the
		 *  command-line, default to all fields in the image.
		 */
		if ( histFields == 0 )
		{
			if ( fieldMask & IMVFBINDEX8 )	histFields |= IMINDEX8;
			if ( fieldMask & IMVFBINDEX16)	histFields |= IMINDEX16;
			if ( fieldMask & IMVFBMONO )	histFields |= IMMONO;
			if ( fieldMask & IMVFBALPHA )	histFields |= IMALPHA;
			if ( fieldMask & IMVFBRGB )	histFields |= IMRED|IMGREEN|IMBLUE;
			requiredFields = fieldMask;
		}
		else
		{
			requiredFields = 0;
			if ( histFields & IMINDEX8 )	requiredFields |= IMVFBINDEX8;
			if ( histFields & IMINDEX16 ) requiredFields |= IMVFBINDEX16;
			if ( histFields & IMMONO )	requiredFields |= IMVFBMONO;
			if ( histFields & IMALPHA )	requiredFields |= IMVFBALPHA;
			if ( histFields & IMRED )	requiredFields |= IMVFBRGB;
			if ( histFields & IMGREEN )	requiredFields |= IMVFBRGB;
			if ( histFields & IMBLUE )	requiredFields |= IMVFBRGB;
			if ( histFields & IMHUE )	requiredFields |= IMVFBRGB;
			if ( histFields & IMSATURATION ) requiredFields |= IMVFBRGB;
			if ( histFields & IMINTENSITY ) requiredFields |= IMVFBRGB;
		}


		/*
		 *  Promote the image to RGB if RGB field computation is
		 *  requested.
		 */
		if ( (requiredFields & IMVFBRGB) && !(fieldMask & IMVFBRGB) )
		{
			tmpVfb = ImVfbToRgb( sourceVfb, IMVFBNEW );

			/*
			 *  Free the old VFB to save on memory.  We won't
			 *  need it again.  This leaves the data table pointing
			 *  to a bogus VFB entry, but that's OK.  We won't
			 *  be referencing the VFB via the table again.
			 */
			ImVfbFree( sourceVfb );
			sourceVfb = tmpVfb;
			fieldMask = ImVfbQFields( sourceVfb );
		}


		/*
		 *  Choose the appropriate color index fields.
		 */
                if ( (fieldMask & IMVFBINDEX16) && (requiredFields & IMVFBINDEX8) )
		{
                        requiredFields = (requiredFields & ~IMVFBINDEX8) | IMVFBINDEX16;
                        histFields = (histFields & ~IMVFBINDEX8) | IMVFBINDEX16;
		}
                else if ( (fieldMask & IMVFBINDEX8) && (requiredFields & IMVFBINDEX16) )
		{
                        requiredFields = (requiredFields & ~IMVFBINDEX16)| IMVFBINDEX8;
                        histFields = (histFields & ~IMVFBINDEX16)| IMVFBINDEX8;
		}


                if ( ImToolsVerbose )
                {
			fprintf( stderr, "%s: Computing histogram on image %d of %d.\n",
			     ImToolsProgram, j + 1, nInVfb);
			fprintf( stderr, "%s: Computing on fields:",
				ImToolsProgram );
			if (histFields&IMRED)	fprintf (stderr, " Red");
			if (histFields&IMGREEN)	fprintf (stderr, " Green");
			if (histFields&IMBLUE)	fprintf (stderr, " Blue");
			if (histFields&IMALPHA)	fprintf (stderr, " Alpha");
			if (histFields&IMHUE)	fprintf (stderr, " Hue");
			if (histFields&IMSATURATION) fprintf (stderr, " Saturation");
			if (histFields&IMINTENSITY) fprintf (stderr, " Intensity");
			if (histFields&IMINDEX8) fprintf (stderr, " Index8");
			if (histFields&IMINDEX16) fprintf (stderr, " Index16");
			if (histFields&IMALPHA)	fprintf (stderr, " Alpha");
			fprintf( stderr, "\n" );
                }


                /*
                 *  Make sure it's got the fields we need for computing.
                 */
                if ( (fieldMask & requiredFields) != requiredFields )
                {
                        fprintf( stderr, "%s: The input image %d of %d doesn't have those fields!\n", ImToolsProgram, j+1, nInVfb );
			fprintf( stderr, "%s: Couldn't compute histogram for image %d of %d.\n",
				ImToolsProgram, j + 1, nInVfb );
			/*
			 *  Free the VFB to save on memory.  We won't
			 *  need it again.  This leaves the data table pointing
			 *  to a bogus VFB entry, but that's OK.  We won't
			 *  be referencing the VFB via the table again.
			 */
			ImVfbFree( sourceVfb );
			continue;
                }


		/*
		 *  Compute it!
		 */
		doHeader = toolHeader;
		doHist   = toolOutHist;
		if ( doHist )
		{
			histTable = ImVfbHist( sourceVfb, histFields, toolSort);
			if ( histTable == NULL )
			{
				ImPError( ImToolsProgram );
				fprintf( stderr, "%s: Histogram computation aborted.\n", ImToolsProgram );
				doHist = FALSE;
			}
		}


		/*
		 *  Compute and output header information, if requested.
		 */
		if ( doHeader )
		{
			fprintf( outFp, "%-24s %s\n",
				"File:", toolInFilename );
			fprintf( outFp, "%-24s %d x %d\n",
				"Resolution:", ImVfbQWidth( sourceVfb ),
				ImVfbQHeight( sourceVfb ) );
			fprintf( outFp, "%-24s %d\n",
				"Number of Pixels:", (ImVfbQWidth(sourceVfb) *
				ImVfbQHeight(sourceVfb)));
			if ( doHist )
				fprintf( outFp, "%-24s %d\n",
					"Number of Combinations:",
					histTable->imhist_nEntries );

			IM_DOSTAT( sourceVfb, outFp, histFields, IMMONO, "1-bit Monochrome" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMINDEX8, "8-bit Color Indexes" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMINDEX16, "16-bit Color Indexes" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMRED, "Red" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMGREEN, "Green" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMBLUE, "Blue" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMALPHA, "Alpha" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMHUE, "Hue" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMSATURATION, "Saturation" );
			IM_DOSTAT( sourceVfb, outFp, histFields, IMINTENSITY, "Intensity" );
		}


		/*
		 *  Free the VFB to save on memory.  We won't
		 *  need it again.  This leaves the data table pointing
		 *  to a bogus VFB entry, but that's OK.  We won't
		 *  be referencing the VFB via the table again.
		 */
		ImVfbFree( sourceVfb );


		if ( !doHist )
			/* Don't dump the histogram table.		*/
			continue;

		if ( doHeader )
		{
			/* Print out a nice column header for the data.	*/
			fprintf( outFp, "Number");
			if ( histFields & IMMONO ) fprintf( outFp, "\tMONO" );
			if ( histFields & IMINDEX8 ) fprintf( outFp, "\tINDEX8" );
			if ( histFields & IMINDEX16 ) fprintf( outFp, "\tINDEX16" );
			if ( histFields & IMHUE ) fprintf( outFp, "\tHUE" );
			if ( histFields & IMSATURATION ) fprintf( outFp, "\tSAT" );
			if ( histFields & IMINTENSITY ) fprintf( outFp, "\tINTEN" );
			if ( histFields & IMRED ) fprintf( outFp, "\tRED" );
			if ( histFields & IMGREEN ) fprintf( outFp, "\tGREEN" );
			if ( histFields & IMBLUE ) fprintf( outFp, "\tBLUE" );
			if ( histFields & IMALPHA ) fprintf( outFp, "\tALPHA" );
			fprintf( outFp, "\n" );
		}


		/*
		 *  Dump the table.
		 */
		for ( i = 0; i < histTable->imhist_nEntries; i++ )
		{
			fprintf( outFp, "%6d", histTable->imhist_nOccur[i] );
			if ( histFields & IMMONO )
				fprintf( outFp, "\t%d", histTable->imhist_mono[i] );
			if ( histFields & IMINDEX8 )
				fprintf( outFp, "\t%d", histTable->imhist_index8[i] );
			if ( histFields & IMINDEX16 )
				fprintf( outFp, "\t%d", histTable->imhist_index16[i] );
			if ( histFields & IMHUE )
				fprintf( outFp, "\t%3.2f", histTable->imhist_hue[i] );
			if ( histFields & IMSATURATION )
				fprintf( outFp, "\t%1.4f", histTable->imhist_saturation[i] );
			if ( histFields & IMINTENSITY )
				fprintf( outFp, "\t%1.4f", histTable->imhist_intensity[i] );
			if ( histFields & IMRED )
				fprintf( outFp, "\t%d", histTable->imhist_red[i] );
			if ( histFields & IMGREEN )
				fprintf( outFp, "\t%d", histTable->imhist_green[i] );
			if ( histFields & IMBLUE )
				fprintf( outFp, "\t%d", histTable->imhist_blue[i] );
			if ( histFields & IMALPHA )
				fprintf( outFp, "\t%d", histTable->imhist_alpha[i] );
			fprintf( outFp, "\n" );

		}
		if ( doHist )
			ImVfbHistTableFree( histTable );
	}

	if ( *toolOutFilename != '\0')
		fclose( outFp );
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
	ArgOption  *options;		/* Argument options		*/
	ArgOption  *options1;		/* Argument options		*/
	ArgEquiv   *equivs;		/* Argument equivalent keywords	*/
	ArgEquiv   *equivs1;		/* Argument equivalent keywords	*/

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
	 * Set up the incoming flags table
	 * and get the names and types of our files.
	 */
	toolFlagsTable = ImToolsMakeStandardFlagsTable();
	ImToolsAddReadWriteFlags(toolFlagsTable, "in");
	ImToolsGetNameAndFormat ( "in", 0, toolInFilename, toolInFormat);


	/*
	 *  Get the output file's name (-outfile), if any.
	 */
	if (ArgQNOccur ("outfile")!=0)
		strcpy( toolOutFilename, ArgQValue( "outfile", 0, 0 )->arg_s );
	else
		*toolOutFilename = '\0';


	/*
	 *  Get the field list, if any.
	 */
	toolField = 0;
        if ( ArgQNOccur( "red" ) != 0 )                 toolField |= IMRED;
        if ( ArgQNOccur( "green" ) != 0 )               toolField |= IMGREEN;
        if ( ArgQNOccur( "blue" ) != 0 )                toolField |= IMBLUE;
        if ( ArgQNOccur( "alpha" ) != 0 )               toolField |= IMALPHA;
        if ( ArgQNOccur( "index" ) != 0 )		toolField |= IMINDEX8;
        if ( ArgQNOccur( "mono" ) != 0 )                toolField |= IMMONO;
        if ( ArgQNOccur( "hue" ) != 0 )                 toolField |= IMHUE;
        if ( ArgQNOccur( "saturation" ) != 0 )          toolField |= IMSATURATION;
        if ( ArgQNOccur( "intensity" ) != 0 )           toolField |= IMINTENSITY;


        if ( toolField & (IMRED | IMGREEN | IMBLUE) )
        {
                if ( (toolField & ~(IMRED | IMGREEN | IMBLUE | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Histograms can only be computed in one color space at a time.\n", ImToolsProgram );
                        fprintf( stderr, "%s: RGB, HSI, mono and color index options cannot be mixed\n", ImToolsProgram );
                        exit( 1 );
                }
        }
        else if ( toolField & (IMHUE | IMSATURATION | IMINTENSITY) )
        {
                if ( (toolField & ~(IMHUE | IMSATURATION | IMINTENSITY | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Histograms can only be computed in one color space at a time.\n", ImToolsProgram );
                        fprintf( stderr, "%s: RGB, HSI, mono and color index options cannot be mixed\n", ImToolsProgram );
                }
        }
        else if ( toolField & IMMONO )
        {
                if ( (toolField & ~(IMMONO | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Histograms can only be computed in one color space at a time.\n", ImToolsProgram );
                        fprintf( stderr, "%s: RGB, HSI, mono and color index options cannot be mixed\n", ImToolsProgram );
                        exit( 1 );
                }
        }
        else if ( toolField & IMINDEX8 )
        {
                if ( (toolField & ~(IMINDEX8 | IMALPHA)) != 0 )
                {
                        fprintf( stderr, "%s: Histograms can only be computed in one color space at a time.\n", ImToolsProgram );
                        fprintf( stderr, "%s: RGB, HSI, mono and color index options cannot be mixed\n", ImToolsProgram );
                        exit( 1 );
                }
        }


	/*
	 *  Get output options.
	 */
	if ( ArgQNOccur( "outnoheader" ) != 0 )
		toolHeader = FALSE;
	else
		toolHeader = TRUE;

	if ( ArgQNOccur( "outnosort" ) != 0 )
		toolSort = FALSE;
	else
		toolSort = TRUE;

	if ( ArgQNOccur( "outnohistogram" ) != 0 )
		toolOutHist = FALSE;
	else
		toolOutHist = TRUE;
}
