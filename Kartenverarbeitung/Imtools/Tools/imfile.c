/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imfile.c,v 1.11 1995/06/29 01:05:35 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/imfile.c,v 1.11 1995/06/29 01:05:35 bduggan Exp $"

/**
 **  FILE
 **	imfile.c	-  Image file known format query
 **
 **  PROJECT
 **	IM		-  Image Manipulation Tools
 **
 **  DESCRIPTION
 **	imfile opens the file or files and tries to figure out what kind of
 **	image file they are.
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
 **  HISTORY
 **	$Log: imfile.c,v $
 **	Revision 1.11  1995/06/29  01:05:35  bduggan
 **	changed date in arg structure to be 95
 **
 **	Revision 1.10  1995/06/29  00:40:07  bduggan
 **	updated copyright
 **
 **	Revision 1.9  1995/06/15  19:07:42  bduggan
 **	Changed function pointer to have arguments in it's declaration (as per ANSI c)
 **	Removed use of global ImFileFormats variable
 **
 **	Revision 1.8  1995/05/30  17:47:28  bduggan
 **	Added compression scheme support
 **
 **	Revision 1.7  1995/05/18  00:00:59  bduggan
 **	Added new read-write options routines.  Added option-specific help.
 **
 **	Revision 1.6  94/10/03  15:49:18  nadeau
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
 **	Revision 1.5  92/12/01  18:45:10  nadeau
 **	Updated info message printing.
 **	
 **	Revision 1.4  92/08/31  17:06:04  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.3  91/10/03  13:20:21  nadeau
 **	Update to version 2.0 of the Arg parsing package.
 **	
 **	Revision 1.2  91/03/11  14:38:43  nadeau
 **	Updated comments and updated to use new file formats table.
 **	
 **	Revision 1.1  90/07/02  13:16:37  nadeau
 **	Initial revision
 **	
 **	Revision 1.5  90/05/11  14:27:18  nadeau
 **	Removed old ifdefed dispatch table stuff and added more comments.
 **	
 **/

#include <unistd.h>
#include "imtools.h"


/**
 **  CODE CREDITS
 **     Custom development, Dave Nadeau, San Diego Supercomputer Center, 1990.
 **/




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
	/* command name */		"imfile",

	/* major version # */		IMTOOLSMAJOR,
	/* minor version # */		IMTOOLSMINOR,
	/* subminor version # */	IMTOOLSSUBMINOR,

	/* -help pre-option list information				*/
"%command determines the type of image file format used by each file on its\n\
command line and prints it to stdout.\n\
",

	/* -help post-option list information				*/
	NULL,				/* Filled in later on		*/

	/* -fullhelp pre-option list information			*/
	NULL,				/* Use same message as for -help*/
	/* -fullhelp post-option list information			*/
	NULL,				/* Use same message as for -help*/

	ARGFNONE,			/* No special flags		*/
	"[options...] filenames...",
	"[options...] filenames...",
	"SDSC Image Tools, October 1992.",
	IMTOOLSCOPYRIGHT,
	NULL,				/* filled in later on		*/
	NULL,				/* filled in later on		*/
};

static char *toolHelp = "\n\
Typical Invocations:\n\
    List file formats for all files in the current directory:\n\
        %command *\n\
";

static char *toolFullHelp = "\n\
Output:\n\
    Output is a table giving the file name, its format name, and a description\n\
    of that format.  If %command cannot figure out the type of image file, the\n\
    words 'Unknown image file format' are printed beside the file name.\n\
    \n\
    A single dash ('-') may be used as the filename to indicate stdin.\
";

static char *toolNote = "\n\
Additional Help:\n\
    This is an abbreviated help listing.  For a full listing of options,\n\
    type:\n\
        %command -fullhelp\n\
    For help about a specific option, type:\n\
        %command -help -<option name>\n\
";

#define TOOLNOPTIONS	2
static ArgOption toolOptions[TOOLNOPTIONS] =
{
	{ "infile", "filenames...", "Names of files to query%end\
    The -%option argument specifies the name of the input file.              \n\
                                                                             \n\
    A single dash ('-') for the input filename indicates stdin.\
",
	  ARGFIMPKEYWORD|ARGFREQUIRED, 1, ARGVNOMAX, ARGTSTRING },

	{ "long", NULL, "Show a long form of the information%end\
    The -long option tells information about a file such as the size of the\n\
    image, whether it is color indexed or RGB, how many bits per channel it\n\
    has, and the compression scheme used.",
	  ARGFNONE, 0, 0, ARGTNONE },
};

#define TOOLNEQUIVS	0
#if TOOLNEQUIVS == 0
static ArgEquiv *toolEquivs;
#else
static ArgEquiv toolEquivs[TOOLNEQUIVS] =
{
};
#endif





/*
 * GLOBALS
 *	toolsDataTable	- a table for the storage of data read in
 *	toolsFlagsTable	- a table for the storage of read flags
 */

static TagTable *toolDataTable;	/* Data tag table		*/
static TagTable *toolFlagsTable;/* Flags tag table		*/





/*
 *  FUNCTION
 *	imFileInfoHandler	- info handler for imfile
 *
 *  DESCRIPTION
 *	Called on each "info" message printed by the Image Tools file
 *	read routines, this handler prints the message to stdout as part
 *	of the -long option.  Unlike the default ImToolsInfoHandler, this
 *	handler intentionally omitts preceeding each message line with the
 *	program name and input file name.
 */

static int				/* Returns nothing		*/
#ifdef __STDC__
imFileInfoHandler( char *program, char *filename, char *message )
#else
imFileInfoHandler( program, filename, message )
	char *program;			/* Program name			*/
	char *filename;			/* File name			*/
	char *message;			/* Message to display           */
#endif
{
	fprintf( stdout, "		%s", message );
	return ( 0 );
}





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	The incoming argument list is walked and each file checked
 *	to see what kind of image file format it uses.
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
	int           i, j;		/* Counters			*/
	int	      n;		/* Number of entries		*/
	int	      numFiles;		/* Number of file names		*/
	char          fileName[1024];	/* Input file name		*/
	char         *formatName;	/* Input file's format		*/
	ImFileFormat **pFmt;		/* Format list pointer		*/
	ImVfb        *vfb;		/* Image			*/
	ImClt	     *clt;		/* Color lookup table		*/
	int           fd;		/* File descriptor		*/
	char          buffer[1024];	/* Output buffer		*/
	char	     *tmp;		/* Temp string			*/
	int	      doLong = FALSE;	/* Do long output?		*/
	TagEntry     *dataEntry;	/* Tag table entry		*/
	char	     *compressName;	/* name of compression scheme   */
	ImCompressScheme* pScheme;	/* description of scheme        */
#ifdef __STDC__
	int         (*handler)( char*, char*, char* );	/* Temporary handler func ptr	*/
#else
	int         (*handler)( );	/* Temporary handler func ptr	*/
#endif

//	argc = __argc;
//	argv = __argv;

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
	 *  Parse arguments.
	 */
	ImToolsProgram = argv[0];
	ArgParse( argc, argv, &toolCommand, TOOLNOPTIONS, toolOptions,
		TOOLNEQUIVS, toolEquivs );

#if defined(_USE_MMFS_FOR_VFB_OPTIONAL)
// Speicherhandling auswerten
	if (ArgQNOccur("memory") > 0) {
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

	numFiles = ArgQNValue( "infile", 0 );


	if ( ArgQNOccur( "long" ) != 0 )
	{

		/*
		 * Set up the incoming and outgoing flags tables
		 * and get the names and types of our files.
		 */
		toolFlagsTable = ImToolsMakeStandardFlagsTable();

		handler = imFileInfoHandler;
		TagTableReplace( toolFlagsTable, 0,
			TagEntryAlloc( "info handler", IM_POINTER_TYPE, &handler ) );
		doLong = TRUE;
	}


	/*
	 *  List the files and the formats they use.
	 */
	for ( i = 0; i < numFiles; i++ )
	{
		strcpy( fileName, ArgQValue( "infile", 0, i )->arg_s );

		sprintf( buffer, "%s:", fileName );

		if ( (fd = _open( fileName, _O_RDONLY )) == -1 )
		{
			printf( "%-15s Cannot open file\n", buffer );
			continue;
		}
		
		/*
		 * Is it compressed?
		 */
	        if ((compressName = ImFileQCompression( fd, toolFlagsTable))!=NULL)
		{
			/* compressed */
			pScheme = ImFileFindCompressionScheme(compressName);
			printf("%-15s Compressed File ('%s', %s)\n",buffer,
				pScheme->compress_suffixes[0],
				pScheme->compress_name);
			if (! doLong)
				printf("%-15s Use the -long flag to query the image format.\n",buffer);
		}
		else
		{
			/* not compressed */
			formatName = ImFileQFormat( fd, fileName );
			if ( formatName == NULL )
			{
				printf( "%-15s Unknown image file format\n", buffer );
				_close( fd );
				continue;
			}

			for ( pFmt = ImGetFileFormats(); *pFmt; pFmt++ )
				if ( strcmp( (*pFmt)->format_names[0], formatName)== 0 )
					break;
			printf( "%-15s '%s', %s, %s\n", buffer, formatName,
				(*pFmt)->format_help, (*pFmt)->format_creator );
		}
		if ( doLong )
		{
			/*
			 *  Make a data table to hold the incoming data.
			 */
			if ( (toolDataTable = TagTableAlloc( )) == TAGTABLENULL)
			{
				TagPError( ImToolsProgram );
				exit( 1 );
			}

			/*
			 *  Update the flags table to include the name of
			 *  the file we're reading.
			 */
			ImToolsChangeTagEntry( toolFlagsTable,
					"file name", fileName );

			/*
			 * Seek to beginning of file
			 */
			_lseek( fd, 0, 0 );

			/*
			 *  Read in the file, printing info along the way.
			 */
			if ( ImFileRead( fd, formatName, toolFlagsTable,
				toolDataTable ) == -1 )
			{
				/* Error message already output.	*/
				exit( 1 );
			}


			/*
			 *  Blow away all the VFB's and CLT's in the tag table.
		 	 *  For some file formats, there'll be additional
			 *  allocated space for image file names, hot spots,
			 *  and other things.  Since we don't know what all of
			 *  these are, or how to free their space, we'll just
			 *  let them slide as a memory leak and hope it doesn't
			 *  leak too much.  The VFB and CLT are the most
			 *  likely big memory hogs anyway.
			 */
			n = TagTableQNEntry( toolDataTable, "image vfb" );
			for ( j = 0; j < n; j++ )
			{
				dataEntry = TagTableQDirect( toolDataTable,
					"image vfb", j );
				TagEntryQValue( dataEntry, &vfb );
				if( vfb != IMVFBNULL )
					ImVfbFree( vfb );
			}
			n = TagTableQNEntry( toolDataTable, "image clt" );
			for ( j = 0; j < n; j++ )
			{
				dataEntry = TagTableQDirect( toolDataTable,
					"image clt", j );
				TagEntryQValue( dataEntry, &clt );
				if( clt != IMCLTNULL )
					ImCltFree( clt );
			}


			/*
			 *  And toss the data table itself.
			 */
			TagTableFree( toolDataTable );
		}

		_close( fd );
	}
}
