/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imformats.c,v 1.13 1995/10/03 16:41:23 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imformats.c,v 1.13 1995/10/03 16:41:23 bduggan Exp $"

/**
 **  FILE
 **	imformats.c	-  Image file known format listing
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imformats.c lists to stdout all of the image file formats currently
 **	understood by the image library.
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
 **	toolCommand	g  command info for arg parsing pkg
 **	toolOptions	g  option info for arg parsing pkg
 **
 **	printFormat	f  print a format entry
 **
 **  HISTORY
 **	$Log: imformats.c,v $
 **	Revision 1.13  1995/10/03  16:41:23  bduggan
 **	Fixed overwriting of a static char*
 **	which caused a core dump on suns
 **
 **	Revision 1.12  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.11  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.10  1995/06/15  19:15:12  bduggan
 **	Removed use of global ImFileFormats variable.
 **
 **	Revision 1.9  1995/05/18  00:01:51  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.8  94/10/03  15:49:25  nadeau
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
 **	Revision 1.7  92/12/01  14:05:01  nadeau
 **	Updated to use new ImFileFormats table structure.
 **	
 **	Revision 1.6  92/08/31  17:07:55  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.5  92/05/28  12:54:07  vle
 **	Added a function prototype for printFormats().
 **	
 **	Revision 1.4  91/10/03  13:20:41  nadeau
 **	Update to version 2.0 of arg parsing package.
 **	Minor printing cosmetics.
 **	
 **	Revision 1.3  91/03/11  14:39:05  nadeau
 **	Updated to use new file formats table and print more info.
 **	
 **	Revision 1.2  91/02/05  16:41:55  nadeau
 **	Fixed a minor printing bug in lists of equivalent format names.
 **	
 **	Revision 1.1  90/07/02  13:16:42  nadeau
 **	Initial revision
 **	
 **/

/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1990.
 **/

#include "imtools.h"
#include <malloc.h>

#ifdef __STDC__
static int printFormat( ImFileFormat *pFmt, int longForm );
#else
static int printFormat();
#endif



/*
 *  GLOBALS
 *	toolCommand		-  command info for arg parsing pkg
 *	toolOptions		-  option info for arg parsing pkg
 *
 *  DESCRIPTION
 *	toolCommand describes the command and gives the help text.
 *
 *	toolOptions lists the arg options accepted.
 */

static ArgCommand toolCommand =
{
	/* command name */		"imformats",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command lists information on the image file formats supported by the SDSC\n\
Image Tools.\n\
",

	/* -help post-option list information				*/
	NULL,				/* filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* Use same message as for -help*/

	ARGFNONE,			/* No special flags		*/
	"[options...]",
	"[options...]",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    List formats supported:\n\
        %command\n\
    List details of support for TIFF and GIF formats:\n\
        %command -long -tiff -gif\n\
    List extensive details on support for TIFF and GIF formats:\n\
        %command -long -long -tiff -gif\n\
";

static char *toolFullHelp = "\n\
Output:\n\
    With no options, %command prints a table to stdout listing the names of\n\
    all formats supported by the SDSC Image Tools.\n\
\n\
    -long expands the table to include information on the format's creator,\n\
    other names the format is known by, and a summary of what format variants\n\
    are supported for read and write operations.\n\
\n\
    Given twice, -long further expands on the format table by exchanging the\n\
    format variant summary for an explicit and detailed list of what variants\n\
    of the file format can be read and written.\n\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type\n\
        %command -help -<option name>\n\
";

static ArgOption toolOptions[] =
{
	{ "long", NULL, "Show a long form of the information%end\
    Use %command -long to see a long version of the format information.\n\
    Use %command -long -long to see a really long version of the format information.\n\
",
	  ARGFMULTIPLE, 0, 0, ARGTNONE },
};
#define TOOLNOPTIONS	1

#define TOOLNEQUIVS	0
#if TOOLNEQUIVS == 0
static ArgEquiv *toolEquivs;
#else
static ArgEquiv toolEquivs[TOOLNEQUIVS] =
{
};
#endif


#ifdef __STDC__
static int imFormatsMergeFormatOptions( int baseNOptions, ArgOption *baseOptions,
	ArgOption **totalOptions );
static int imFormatsMergeFormatEquivs( int baseNEquivs, ArgEquiv *baseEquivs,
	ArgEquiv **totalEquivs );
#else
static int imFormatsMergeFormatOptions( );
static int imFormatsMergeFormatEquivs( );
#endif




/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	The file format list is walked and printed to stdout.
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
	int            longForm;	/* Use long form?		*/
	ImFileFormat **ppFmt;		/* Format list pointer		*/
	char          *pName;		/* Format name to get		*/
	char         **pNames;		/* Format name list pointer	*/
	int            i;		/* Counter			*/
	int            nOpt;		/* Number of options		*/
	int            nEquiv;		/* Number of equivalences	*/
	int	       noccur;		/* Number of occurrences	*/
	ArgOption     *options;		/* Argument options		*/
	ArgEquiv      *equivs;		/* Argument equivalent keywords	*/
	char	      *tmp;		/* Temp string			*/

	argc = __argc;
	argv = __argv;

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
	toolCommand.arg_fullhelp2 = tmp;

	/*
	 *  Add the file formats to the argument and equivalences list
	 *  and parse the command-line arguments.
	 */
	ImToolsProgram = argv[0];

	nOpt = imFormatsMergeFormatOptions( TOOLNOPTIONS, toolOptions, &options );
	nEquiv = imFormatsMergeFormatEquivs( TOOLNEQUIVS, toolEquivs, &equivs );

	if ( nOpt == -1 || nEquiv==-1)
	{
		ImPError( ImToolsProgram );
		exit( 1 );
	}

	nOpt = ArgParse( argc, argv, &toolCommand, nOpt, options,
		nEquiv, equivs );
	i = nOpt;
	longForm = ArgQNOccur( "long" );
	i -= longForm;

	/*
	 *  Print information on each selected format, or all of them if
	 *  none was selected.
	 */
	if ( i == 0 )
	{
		/*
		 *  No explicit list given.  Show everything.
		 */
		printf( "Format  Description\n" );
		printf( "------------------------------------------------------------------------\n" );
		for ( ppFmt = ImGetFileFormats(); *ppFmt; ppFmt++ )
		{
			printFormat( *ppFmt, longForm );
		}
		exit( 0 );
	}

	/*
	 *  Explicit list given.  List them in the order given.
	 */
	if ( i != 1 )
	{
		printf( "Format  Description\n" );
		printf( "------------------------------------------------------------------------\n" );
	}

	for ( i = 0; i < nOpt; i++ )
	{
		pName = ArgQOpt( i, &noccur );

		if ( strcmp( pName, "long" ) == 0 )
			continue;

		for ( ppFmt = ImGetFileFormats(); *ppFmt; ppFmt++ )
		{
			pNames = &(*ppFmt)->format_names[0];
			for ( ; *pNames; pNames++ )
			{
				if ( strcmp( *pNames, pName ) == 0 )
				{
					printFormat( *ppFmt, longForm );
					break;
				}
			}
			if ( *pNames )
				break;
		}
	}
}




/*
 *  FUNCTION
 *	printFormat	-  print a format entry
 *
 *  DESCRIPTION
 *	The format's information is printed out nicely.
 */

static int				/* Returns status		*/
#ifdef __STDC__
printFormat( ImFileFormat *pFmt, int longForm )
#else
printFormat( pFmt, longForm )
	ImFileFormat *pFmt;		/* Format list pointer		*/
	int           longForm;		/* Use long form?		*/
#endif
{
	char        **pNames;		/* Equivalenet names pointer	*/
	char          buffer[80];	/* Output buffer		*/
	char	     *pSupport;		/* Support message pointer	*/
	char	     *pSupport2;	/* Support message pointer	*/
	ImFileFormatReadMap *pRead;	/* Read map info		*/
	ImFileFormatWriteMap *pWrite;	/* Read map info		*/
	char         *ptr;		/* temporary char pointer       */

	printf( "%-7s %s\n", pFmt->format_names[0], pFmt->format_help );

	if ( longForm == 0 )
		return ( 0 );

	pNames = &pFmt->format_names[1];
	if ( pNames != NULL && *pNames != NULL )
	{
		sprintf( buffer, "        a.k.a.:   %s",
			*pNames++ );
		for ( ; *pNames; pNames++ )
		{
			if ( (strlen( buffer )+2+strlen( *pNames )) >80)
			{
				printf( "%s,\n", buffer );
				strcpy( buffer, "          " );
			}
			else
				strcat( buffer, ", " );
			strcat( buffer, *pNames );
		}
		printf( "%s\n", buffer );
	}

	printf( "        Creator:  %s\n", pFmt->format_creator );

	if ( longForm == 1 )
	{
		/* Print the summary.					*/
		printf( "        Read support:\n" );
		pSupport = pFmt->format_readSupport;
		if ( pSupport == NULL )
			printf( "          None.\n" );
		else
			while ( *pSupport != '\0' )
			{
				/*
				 * Print one line at a time so that we
				 * can indent things.
				 */
				pSupport2 = pSupport;
				while ( *pSupport != '\0' && *pSupport != '\n' )
					pSupport++;
				if ( *pSupport == '\0' )
				{
					/* 
					 * We've reached the end of the string.
					 * Print from pSupport2.
					 */
					printf( "          %s\n", pSupport2 );
				}
				else
				{	
					 /*
					  * We want to print the string between
					  * the pointers pSupport2 and pSupport.
					  * Unforunately on some machine/compiler
					  * combinations, we are not allowed to
					  * alter the contents of strings declared
					  * at run-time.  i.e. we cannot set
					  * *pSupport to be '\0'.  This is 
					  * unfortunate.
					  *
					  * Instead, we'll just loop through 
					  * the string with another pointer.
					  */
					printf( "          ");
					for (ptr=pSupport2; ptr<pSupport; ptr++)
						printf("%c",*ptr);
					printf( "\n");

					pSupport++;
				}
			}

		printf( "        Write support:\n" );
		pSupport = pFmt->format_writeSupport;
		if ( pSupport == NULL )
			printf( "          None.\n" );
		else
			while ( *pSupport != '\0' )
			{
				pSupport2 = pSupport;
				while ( *pSupport != '\0' && *pSupport != '\n' )
					pSupport++;
				if ( *pSupport == '\0' )
					printf( "          %s\n", pSupport2 );
				else
				{
					 /*
					  * We want to print the string between
					  * the pointers pSupport2 and pSupport.
					  * Unforunately on some machine/compiler
					  * combinations, we are not allowed to
					  * alter the contents of strings declared
					  * at run-time.  i.e. we cannot set
					  * *pSupport to be '\0'.  This is 
					  * unfortunate.
					  *
					  * Instead, we'll just loop through 
					  * the string with another pointer.
					  */
					printf( "          ");
					for (ptr=pSupport2; ptr<pSupport; ptr++)
						printf("%c",*ptr);
					printf( "\n");

					pSupport++;
				}
			}
		printf( "\n" );
		return ( 0 );
	}

	/* Print the exact format read and write map.			*/
	printf( "        Read support:\n" );
	pRead = pFmt->format_readMap;
	if ( pRead == NULL )
		printf( "            None.\n" );
	else
	{
		printf( "            Type   #chan  #bits  CLT?  Alpha?  Compression  Interleaving\n" );
		printf( "            -----  -----  -----  ----  ------  -----------  -----------\n" );
		for ( ; pRead->map_inType != -1; pRead++ )
		{
			printf( "            " );
			switch ( pRead->map_inType )
			{
			case IMTYPEINDEX:
				printf( "index " );
				break;
			case IMTYPERGB:	
				printf( "rgb   " );
				break;
			case IMTYPE2D:	
				printf( "2D geometry\n" );
				continue;
			default:
				printf( "unknown?\n" );
				continue;
			}
			printf( " %-5d  %-5d", pRead->map_inNChannels,
				pRead->map_inChannelDepth );
			if ( pRead->map_inAttributes & IMCLTYES )
				printf( "  yes " );
			else
				printf( "  no  " );
			if ( pRead->map_inAttributes & IMALPHAYES )
				printf( "  yes    " );
			else
				printf( "  no     " );
			switch ( pRead->map_inAttributes & IMCOMPMASK )
			{
			case IMCOMPNO:	printf( " none       " ); break;
			case IMCOMPRLE:	printf( " RLE        " ); break;
			case IMCOMPLZW:	printf( " LZW        " ); break;
			case IMCOMPPB:	printf( " PackBits   " ); break;
			case IMCOMPDCT:	printf( " DCT        " ); break;
			case IMCOMPCCITTRLE:	printf( " CCITTRLE   " ); break;
			case IMCOMPCCITTFAX3:	printf( " CCITTFax3  " ); break;
			case IMCOMPCCITTFAX4:	printf( " CCITTFax4  " ); break;
			}
			switch ( pRead->map_inAttributes & IMINTERMASK )
			{
			case IMINTERNO:	printf( "  none" ); break;
			case IMINTERLINE:printf( "  scanline" ); break;
			case IMINTERPLANE:printf( "  plane" ); break;
			}
			printf( "\n" );
		}
	}

	printf( "        Write support:\n" );
	pWrite = pFmt->format_writeMap;
	if ( pWrite == NULL )
		printf( "            None.\n" );
	else
	{
		printf( "            Type   #chan  #bits  CLT?  Alpha?  Compression  Interleaving\n" );
		printf( "            -----  -----  -----  ----  ------  -----------  -----------\n" );
		for ( ; pWrite->map_outType != -1; pWrite++ )
		{
			printf( "            " );
			switch ( pWrite->map_outType )
			{
			case IMTYPEINDEX:
				printf( "index " );
				break;
			case IMTYPERGB:	
				printf( "rgb   " );
				break;
			case IMTYPE2D:	
				printf( "2D geometry\n" );
				continue;
			default:
				printf( "unknown?\n" );
				continue;
			}
			printf( " %-5d  %-5d", pWrite->map_outNChannels,
				pWrite->map_outChannelDepth );
			if ( pWrite->map_outAttributes & IMCLTYES )
				printf( "  yes " );
			else
				printf( "  no  " );
			if ( pWrite->map_outAttributes & IMALPHAYES )
				printf( "  yes    " );
			else
				printf( "  no     " );
			switch ( pWrite->map_outAttributes & IMCOMPMASK )
			{
			case IMCOMPNO:	printf( " none       " ); break;
			case IMCOMPRLE:	printf( " RLE        " ); break;
			case IMCOMPLZW:	printf( " LZW        " ); break;
			case IMCOMPPB:	printf( " PackBits   " ); break;
			case IMCOMPDCT:	printf( " DCT        " ); break;
			case IMCOMPCCITTRLE:	printf( " CCITTRLE   " ); break;
			case IMCOMPCCITTFAX3:	printf( " CCITTFax3  " ); break;
			case IMCOMPCCITTFAX4:	printf( " CCITTFax4  " ); break;
			}
			switch ( pWrite->map_outAttributes & IMINTERMASK )
			{
			case IMINTERNO:	printf( "  none" ); break;
			case IMINTERLINE:printf( "  scanline" ); break;
			case IMINTERPLANE:printf( "  plane" ); break;
			}
			printf( "\n" );
		}
	}

	printf( "\n" );
	return ( 0 );
}


/*
 *  FUNCTION
 *	imFormatsMergeFormatOptions	-  add format names to arg option list
 *	imFormatsMergeFormatEquivs	-  add format equiv names to arg equivs list
 *
 *  DESCRIPTION
 *	These two functions are provided to those tools that wish to have one
 *	arg-parsing package keyword per format name.
 *
 *	ImToolsFormatOptions() creates a new ArgOption array big enough for
 *	the caller's base options (everything but format names), plus all
 *	of the format names in the format table.  The base options are
 *	copied into the new list, followed by the names of all formats in
 *	the format table.
 *
 *	ImToolsFormatEquivs() creates a new ArgEquiv array big enough for the
 *	caller's base equivs (everything but format names), plus all of the
 *	format equivalent names in the format table.  The base equivs are
 *	copied into the new list, followed by the equiv names for each of
 *	the formats in the format table.
 */

static int					/* Returns new # of options	*/
#ifdef __STDC__
imFormatsMergeFormatOptions( int baseNOptions, ArgOption *baseOptions,
	ArgOption **totalOptions )
#else
imFormatsMergeFormatOptions( baseNOptions, baseOptions, totalOptions )
	int            baseNOptions;	/* # of base options		*/
	ArgOption     *baseOptions;	/* Base options			*/
	ArgOption    **totalOptions;	/* Returns full option list	*/
#endif
{
	int            i;		/* Counter			*/
	ArgOption     *pOpt;		/* Option list pointer		*/
	ImFileFormat **pFmt;		/* Format list pointer		*/

	/*
	 *  Allocate space for the total option set.
	 */
	if ( (pOpt = (ArgOption *)malloc( (baseNOptions + ImFileQNFormat( )) *
		sizeof( ArgOption ) )) == NULL )
	{
		ImErrNo = IMEMALLOC;
		return ( -1 );
	}
	*totalOptions = pOpt;

	/*
	 *  Copy the base options into it then Add an option for each format.
	 */
	for ( i = 0; i < baseNOptions; i++ )
		*pOpt++ = *baseOptions++;

	for ( pFmt = ImGetFileFormats(); *pFmt; i++, pFmt++, pOpt++ )
	{
		pOpt->arg_keyword    = (*pFmt)->format_names[0];
		pOpt->arg_valuenames = NULL;
		pOpt->arg_help       = (*pFmt)->format_help;
		pOpt->arg_flags      = ARGFMULTIPLE | ARGFFULLHELP;
		pOpt->arg_minvalues  = 0;
		pOpt->arg_maxvalues  = 0;
		pOpt->arg_type       = ARGTNONE;
	}

	return ( i );
}



static int					/* Returns new # of equivs	*/
#ifdef __STDC__
imFormatsMergeFormatEquivs( int baseNEquivs, ArgEquiv *baseEquivs,
	ArgEquiv **totalEquivs )
#else
imFormatsMergeFormatEquivs( baseNEquivs, baseEquivs, totalEquivs )
	int            baseNEquivs;	/* # of base equivs		*/
	ArgEquiv      *baseEquivs;	/* Base equivs			*/
	ArgEquiv     **totalEquivs;	/* Returns full equiv list	*/
#endif
{
	int            i;		/* Counter			*/
	ArgEquiv      *pEquiv;		/* Equiv list pointer		*/
	ImFileFormat **pFmt;		/* Format list pointer		*/
	ArgEquiv      *newEquiv;	/* New equiv list		*/
	int            allocSize;	/* Allocate size of new list	*/
	char         **pName;		/* Name list pointer		*/

	/*
	 *  Allocate space for the total equivalences set.
	 */
	allocSize = baseNEquivs + ImFileQNFormat( ) * 10;
	if ( (newEquiv = (ArgEquiv *)malloc( allocSize * sizeof( ArgEquiv ) )) == NULL )
	{
		ImErrNo = IMEMALLOC;
		return ( -1 );
	}

	/*
	 *  Copy the base equivs into it then add an equiv for each format.
	 */
	pEquiv = newEquiv;
	for ( i = 0; i < baseNEquivs; i++ )
		*pEquiv++ = *baseEquivs++;
	for ( pFmt = ImGetFileFormats(); *pFmt; pFmt++ )
	{
		for ( pName = &(*pFmt)->format_names[1]; *pName;
			i++, pName++, pEquiv++ )
		{
			if ( i > allocSize )
			{
				/* Too many equivs.  Realloc.		*/
				allocSize += 200;
				if ( (newEquiv = (ArgEquiv *)realloc( (char *)newEquiv,
					allocSize * sizeof( ArgEquiv ))) == NULL )
				{
					ImErrNo = IMEMALLOC;
					return ( -1 );
				}
				pEquiv = newEquiv + i;
			}

			pEquiv->arg_keyword      = (*pFmt)->format_names[0];
			pEquiv->arg_equivkeyword = *pName;
		}
	}

	*totalEquivs = newEquiv;
	return ( i );
}

