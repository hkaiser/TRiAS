/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/imps.c,v 1.28 1995/06/30 22:09:26 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/imps.c,v 1.28 1995/06/30 22:09:26 bduggan Exp $"

/**
 **  FILE
 **	imps.c		-  PostScript file output
 **
 **  PROJECT
 **	libim	-  SDSC image manipulation library
 **
 **  DESCRIPTION
 **	imps.c contains routines to _read and _write PostScript files for
 **	the image manipulation library.  Raster data written out is
 **	taken from a tag table.
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	imPsRead	f  _read an Adobe PostScript file
 **	imPsWrite1	f  _write a 1-bit monochrome image to a PostScript file
 **	imPsWriteGray	f  _write a grayscale image to a PostScript file
 **	imPsWrite8	f  _write an 8-bit index image to a PostScript file
 **	imPsWriteRGB	f  _write an RGB image to a PostScript file
 **
 **  PRIVATE CONTENTS
 **	imPsHex		v  Integer->Hex character conversion table
 **	imPsHeader	v  PostScript header section
 **	imPsProlog	v  PostScript prolog section
 **	imPsImageColor	v  Color printing PostScript procedure
 **	imPsImageGray	v  Grayscale printing PostScript procedure
 **	imPsImageMono	v  Monochrome printing PostScript procedure
 **	imPsScript	v  PostScript page script section
 **	imPsData	v  PostScript data section
 **	imPsTrailer	v  PostScript trailer section
 **
 **  HISTORY
 **	$Log: imps.c,v $
 **	Revision 1.28  1995/06/30  22:09:26  bduggan
 **	added some casts
 **
 **	Revision 1.27  1995/06/29  00:28:04  bduggan
 **	updated copyright year
 **
 **	Revision 1.26  1995/06/29  00:20:49  bduggan
 **	removed magic number
 **
 **	Revision 1.25  1995/06/15  20:56:13  bduggan
 **	added some casts & includes
 **	added support for pageheight, pagewidth, dpi flags
 **
 **	Revision 1.24  1995/05/17  23:46:49  bduggan
 **	Fixed magic number.  ( was !%, now it's %! )
 **
 **	Revision 1.23  1995/04/26  21:58:52  bduggan
 **	Added capability to use environment variable for ghostscript path
 **
 **	Revision 1.22  1995/04/21  20:33:49  bduggan
 **	Changed exec to execlp to avoid needing a hardcoded path.
 **
 **	Revision 1.21  1995/04/03  21:47:58  bduggan
 **	took out #ifdef NEWMAGIC
 **
 **	Revision 1.20  1995/01/16  21:38:37  bduggan
 **	Added John Moreland's ghostscript support
 **	to allow for _read capability
 **
 **	Revision 1.18  94/06/01  09:20:41  moreland
 **	Changed default width from 1280 to 612 and height from 1024 to 792
 **	to match the PostScript page standard.  Also changed default image
 **	depth from 24 to 8 to reduce default image output size.
 **	
 **	Revision 1.17  94/04/22  15:43:21  moreland
 **	Rewrote call to "gs" from using 'system' call to using fork and execl call.
 **	
 **	Revision 1.16  94/04/18  08:40:00  moreland
 **	Get image dpi, width, height, and color depth from flagTable or use defaults.
 **	
 **	Revision 1.15  94/04/15  09:18:53  moreland
 **	First ImPsRead routine working using "system" call.
 **	
 **	Revision 1.16  94/04/13  15:23:31  moreland
 **	First attempt at a PostScript _read routine.
 **	
 **	Revision 1.15  94/03/28  12:23:21  nadeau
 **	Removed use of register, public, and private keywords.
 **	
 **	Revision 1.14  93/03/15  14:04:18  nadeau
 **	Actually fixed the problem that caused landscape mode
 **	printing to clip off the bottom of the image.  A 'lt'
 **	should have been a 'gt'.
 **	
 **	Revision 1.13  93/02/05  17:31:00  nadeau
 **	Fixed bug that prevented autoorientation from properly
 **	choosing between landscape and portrait mode.  This may
 **	be the cause of multiple complaints that images were
 **	being clipped when printed.
 **	
 **	Revision 1.12  92/12/03  01:51:31  nadeau
 **	Corrected info messages.
 **	
 **	Revision 1.11  92/11/04  12:05:47  groening
 **	put ImFIleFormat info and magic number info
 **	from imfmt.c into this file.
 **	
 **	Revision 1.10  92/10/19  14:13:28  groening
 **	added ImInfo statements
 **	
 **	Revision 1.9  92/08/31  17:33:06  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.8  91/10/03  09:16:19  nadeau
 **	Extensive rewrite to update to match Adobe 3.0 DSC.
 **	
 **	Revision 1.7  91/09/17  20:17:10  nadeau
 **	Added color PostScript support.
 **	
 **	Revision 1.6  91/02/12  10:53:58  nadeau
 **	Removed the tag table checking and VFB conversion now
 **	handled by ImFileWrite.  Updated to use INDEX8 instead
 **	of GRAY VFB.  Changed 'Creator' comment to include the
 **	program name from the flags table, if given.
 **	
 **	Revision 1.5  90/11/27  16:40:44  mjb
 **	Removed spaces in between hex bytes (xerox says this will make it
 **	_read much faster).   Made 'image' byte string size the same as vfb
 **	width (ditto above comment)
 **	
 **	Revision 1.4  90/07/02  13:21:33  nadeau
 **	Updated to the new error handling mechanism.
 **	
 **	Revision 1.3  90/06/25  14:36:16  nadeau
 **	Changed ImTag* to Tag* (new names).
 ** 
 **	Revision 1.2  90/05/16  07:47:03  todd
 **	Add #include "iminternal.h" to top of file
 ** 
 **	Revision 1.1  90/05/11  14:28:23  nadeau
 **	Initial revision
 ** 
 **/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/wait.h>
#include "iminternal.h"

#ifdef __STDC__
/* extern char* mktemp( char* ); */
#else
extern char* mktemp( );
#endif

#ifndef IM_GHOSTSCRIPT
#define IM_GHOSTSCRIPT "gs"   /* Ghostscript executable name */
#endif

/*
 *  PS - Adobe PostScript
 *      For information on these structures, how to use them, etc. please
 *      see imfmt.c.
 */
#ifdef __STDC__
static int imPsRead( int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable );
static int imPsWrite1(ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable );
static int  imPsWriteGray( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable);
static int  imPsWrite8( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable);static int  imPsWriteRGB( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable);
#else
static int imPsRead( );
static int imPsWrite1( ), imPsWriteGray( ), imPsWrite8( ), imPsWriteRGB( );
#endif




static char *imPsNames[ ]  = { "ps", "postscript", NULL };
/*
 * We omit the magic number so that it doesn't
 * clash with the .eps magic number.
 */
/* static unsigned char imPsMagicNumber[ ] = { '%', '!' }; */

static ImFileMagic imFilePsMagic []=
{
/*      { 0, 2, imPsMagicNumber}, */
        { 0, 0, NULL },
};

static ImFileFormatWriteMap imPsWriteMap[ ] =
{
        /* in                   out                                     */
        /* VFB type,    attr.,  type,ch,dep,    attr.,  func            */
        { IMVFBMONO,    0,      IN,1,1,         0,      imPsWrite1 },
        { IMVFBINDEX8,  0,      IN,1,8,         0,      imPsWriteGray },
        { IMVFBINDEX8,  C,      IN,1,8,         C,      imPsWrite8 },
        { IMVFBRGB,     0,      RGB,3,8,        0,      imPsWriteRGB },
        { -1,           0,      -1,             0,      0 },
};

static ImFileFormatReadMap imPsReadMap[ ] =
{
	/* in                   out                                     */
	/* type,ch,dep, attr.   VFB type        attr.                   */
	{ IN,1,1,       PB,     IMVFBRGB,       0 },
	{ IN,1,2,       PB | C, IMVFBRGB,       0 },
	{ IN,1,4,       PB | C, IMVFBRGB,       0 },
	{ IN,1,8,       PB | C, IMVFBRGB,       0 },
	{ RGB,3,5,      PB,     IMVFBRGB,       0 },
	{ RGB,3,8,      PB,     IMVFBRGB,       0 },
	{ -1,           0,      -1,             0 },
};


ImFileFormat ImFilePsFormat =
{
	imPsNames, "Adobe PostScript file",
	"Adobe",
#ifdef USE_GHOSTSCRIPT
	"1-bit monochrome, 8-bit grayscale, 8-bit color index, and 24-bit\n\
RGB color images.",	/* Read support */
#else
	"none",		/* Read support */
#endif
	"1-bit monochrome, 8-bit grayscale, 8-bit color index, and 24-bit\n\
RGB color images.",
	imFilePsMagic,
	IMNOMULTI, IMNOPIPE,
	IMNOMULTI, IMPIPE,
#ifdef USE_GHOSTSCRIPT
	imPsRead, 
	imPsReadMap, 
#else
	NULL,
	NULL,
#endif
	imPsWriteMap
};


static char imPsHex[] = "0123456789abcdef" ;


/*
 * FUNCTION
 *	imPsRead  -  _read an Adobe PostScript file
 *
 * DESCRIPTION
 *	A tag must be passed in containing the desired resolution to be RIPed.
 *	The PostScript file is parsed and orientation of the image determined
 *	based on the requested resolution and the parsed orientation,
 *	space is allocated for the VFB and the PostScript file is then
 *	passed to the GhostScript code to RIP the image.
 *	RGB values in the VFB and the completed VFB added to the tag list.
 */
static int	/* Returns # tags _read in */
#ifdef __STDC__
imPsRead( int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable )
#else
imPsRead( ioType, fd, fp, flagsTable, tagTable )
	int		ioType;		/* I/O flags               */
	int		fd;		/* Input file descriptor   */
	FILE		*fp;		/* Input file pointer      */
	TagTable	*flagsTable;	/* Flags                   */
	TagTable	*tagTable;	/* Tag table to add to     */
#endif
{
	TagEntry    *fileEntry;		/* filename flagsTable entry	*/
	TagTable    *newFlagsTable;	/* New flags table		*/
	char *	     tmp;		/* Tmp name holder		*/
	int	     result;		/* return status		*/
	char	     cmd[1024];		/* command line			*/
	char         psFileName[1024];	/* name of PS file		*/
	int	     psFd;		/* PS file descriptor		*/
	int	     n;			/* # of bytes _read		*/
	char	     buffer[1024];	/* Temp file copy buffer	*/
	FILE *	     ppmFp;		/* PPM file pointer		*/
	char         ppmFileName[1024];	/* name of PPM file		*/
	char         ppmTmpFileNames[1024]; /* names of PPM tmp files	*/
	struct _stat statBuf;		/* For testing PPM tmp files */
	TagEntry*    flagsEntry;	/* entry in the flags table     */
	int i;

	/* unsigned int dpi=72;		Dots per inch		*/
	/* unsigned int width=612;	Image Width			*/
	/* unsigned int height=792;	Image Height			*/
	unsigned int dpi=288;		/* Dots per inch		*/
	unsigned int width;		/* image width (in pixels)      */
	unsigned int height;		/* image height (in pixels)     */
	float pageWidth = 8.5;		/* page width  (in inches)      */
	float pageHeight = 11.0;	/* page height (in inches)	*/
	unsigned int depth=8;		/* Image Color Depth		*/

	int my_pid;			/* My PID */
	int gs_pid;			/* Child PID of 'gs'		*/
	int gs_ret;			/* Exec return value of 'gs'	*/
	char arg_dpi[80];		/* Arguments for Exec of 'gs'   */
	char arg_depth[80];		/* Arguments for Exec of 'gs'   */
	char arg_size[80];		/* Arguments for Exec of 'gs'   */
	char arg_ppmFileName[80];	/* Arguments for Exec of 'gs'   */

	char message[100];		/* for error message            */
	char exec_name[1024];           /* ghostscript pathname         */
	char *env_var;			/* Environ. variable w/ gs path */


	/*
	 *  Figure out how to get a file name for the PS data.
	 */
	fileEntry = TAGENTRYNULL;
	if ( flagsTable != TAGTABLENULL && ioType & IMFILEIOFILE )
	{
		/*
		 *  I/O is for a file and we have a flag table.  Perhaps we
		 *  can get it's file name.
		 */
		fileEntry = TagTableQDirect( flagsTable, "file name", 0 );
	}
	if ( fileEntry != TAGENTRYNULL )
	{
		/*
		 *  Yes.  We have a file name.  Use it directly.
		 */
		TagEntryQValue( fileEntry, &tmp );
		strcpy ( psFileName, tmp );
		psFd = -1;
	}
	else
	{
		/*
		 *  We can't get the file name, or input is a stream.
		 *  In either case, create a temporary file and copy the
		 *  input to that file.
		 */
		strcpy( psFileName, "/tmp/ps_XXXXXX" );
		_mktemp( psFileName );
		if ( (psFd = _open( psFileName, _O_WRONLY | _O_CREAT, 0666 )) == -1 )
		{
			ImErrorFatal( "Cannot create temp file", -1, IMESYS );
		}
		if ( ioType & IMFILEIOFD )
		{
			while ( (n = _read( fd, buffer, sizeof( buffer ) )) > 0 )
				_write( psFd, buffer, n );
		}
		else
		{
			while ( (n = fread( buffer, sizeof( buffer ), 1, fp )) > 0 )
				_write( psFd, buffer, n );
		}
		_close( psFd );
	}

	/*
	 *  Figure out what image dpi, width, height is desired 
	 *  (otherwise use defaults).
	 */

	flagsEntry = TagTableQDirect( flagsTable, "image dpi request", 0 );
	if ( flagsEntry != TAGENTRYNULL ) TagEntryQValue( flagsEntry, &dpi );

	flagsEntry = TagTableQDirect( flagsTable, "page width request", 0 );
	if ( flagsEntry != TAGENTRYNULL ) TagEntryQValue( flagsEntry, &pageWidth );

	flagsEntry = TagTableQDirect( flagsTable, "page height request", 0 );
	if ( flagsEntry != TAGENTRYNULL ) TagEntryQValue( flagsEntry, &pageHeight );

	width = (unsigned int) (dpi * pageWidth);
	height = (unsigned int) (dpi * pageHeight);
	/*
	 *  Pre-parse the PostScript input file.
	 *  See if an explicit orientation is specified in the first few lines.
	 */

	/*
	 *  Constuct a string to be used for temporary ppm file names
	 */

	my_pid = (int) _getpid();
	sprintf( ppmTmpFileNames, "/tmp/imps_%%d_%d.ppm", my_pid );

	/*
	 *  Invoke 'gs' to convert from a PS file to a PPM image file.
	 */

	gs_pid = fork();

	if ( gs_pid == 0 )
	{
                /* We are the child process */

		sprintf( arg_dpi, "-r%d", dpi );
		sprintf( arg_depth, "-dBitsPerPixel=%d", depth );
		sprintf( arg_size, "-g%dx%d", width, height );
		sprintf( arg_ppmFileName, "-sOutputFile=%s", ppmTmpFileNames );
		env_var = getenv("IM_GHOSTSCRIPT");
		if (env_var)
			strcpy(exec_name,env_var);
		else
			strcpy(exec_name,IM_GHOSTSCRIPT);
			

		gs_ret = execlp( exec_name,
				exec_name,
				"-q",
				"-dNOPAUSE",
				"-dQUIET",
				"-sDEVICE=ppmraw",
				arg_dpi,
				arg_depth,
				arg_size,
				arg_ppmFileName,
				"--",
				psFileName,
				0 );

		/* We should never get here unless the exec fails */
		sprintf(message,"Could not execute ghostscript ('%s')",exec_name);
		ImErrorFatal( message, -1, IMESYS );
	}
	else if ( gs_pid > 0 )
	{
                /* We are the parent process */
		/* Wait for child pid "gs_pid" to finish */

		wait( &gs_ret );

		if ( gs_ret != 0 )
		{
			/* GhostScript failed for some reason */
			ImErrorFatal( "GhostScript failed", -1, IMESYS );
		}
	}
	else
	{
		/* We should never get here unless the fork fails */
		ImErrorFatal( "fork for gs failed", -1, IMESYS );
	}


	/*
	 *  If we made a temporary PostScript file, then remove it now
	 */
	if ( psFd != -1 ) unlink( psFileName );

	/*
 	 *  Create a new flags table that uses the new PPM file's name
 	 *  instead of the old PS file name.  This also passes along to
 	 *  the PPM _read routines any flags that may have been included.
 	 */
	newFlagsTable = TagTableAlloc( );
	if ( newFlagsTable == TAGTABLENULL )
	{
		ImErrNo = IMEMALLOC;
		ImErrorFatal( ImQError( ), -1, ImErrNo );
	}
	TagTableCopy( flagsTable, newFlagsTable, 0,
		TagTableQNEntry( flagsTable, NULL )-1 );
	fileEntry = TagTableQDirect( newFlagsTable, "file name", 0 );
	tmp = ppmTmpFileNames;
	if ( fileEntry == TAGENTRYNULL )
		TagTableAppend( newFlagsTable,
			TagEntryAlloc( "file name", POINTER, &tmp ) );
	else
		TagTableReplace( newFlagsTable, TagEntryQNthEntry( fileEntry ),
			TagEntryAlloc( "file name", POINTER, &tmp ) );

	/*
	 *  Open the resulting PPM file(s) that 'gs' created.
	 */

	for ( i=1; i<32000; i++ )
	{
		sprintf( ppmFileName, ppmTmpFileNames, i );

		result = stat( ppmFileName, &statBuf ); 
		if ( result != 0 ) return( 0 );

		if ( (ppmFp = fopen( ppmFileName, "r" )) == NULL )
		{
			ImErrorFatal( "Cannot _open PPM temporary file", -1, IMESYS );
		}

		result = ImFileFRead( ppmFp, "ppm", flagsTable, tagTable );

		fclose( ppmFp );
		unlink( ppmFileName );

		if ( result == -1 ) return( result );
	}

	return( result );
}



/*
 *  GLOBAL
 *	imPsHeader	-  PostScript header section
 *
 *  DESCRIPTION
 *	The PostScript file header is a set of special comments conforming
 *	to the Adobe Document Structuring Conventions (DSC) as specified
 *	in the Adobe PostScript Language Reference Manual (second edition).
 *
 *	The DSC comments give the document name, creator, and whatnot.
 *	Most importantly, the DSC also gives the bounding box for the
 *	document.
 */

static char *imPsHeader = "\
%%!PS-Adobe-3.0\n\
%%%%Creator:       %s\n\
%%%%For:           %s\n\
%%%%CreationDate:  %s\
%%%%Title:         %s\n\
%%%%BoundingBox:   0 0 612 792\n\
%%%%Orientation:   Portrait\n\
%%%%PageOrder:     Ascend\n\
%%%%Pages:         1\n\
%%%%EndComments\n\
";





/*
 *  GLOBAL
 *	imPsProlog	-  PostScript prolog section
 *
 *  DESCRIPTION
 *	The PostScript file prolog defines the various functions (procs)
 *	to be used in the PostScript program.  In our case we define some
 *	functions to convert inches to dots, we define some flags, and we
 *	define the generic, super-flexible ImPsPrepare routine.
 */

static char *imPsProlog = "\
%%BeginProlog\n\
\n\
\n\
\n\
%  WANT TO CHANGE THE IMAGE SIZE AND POSITION ?\n\
%	This is easy!  Search forward for 'CHANGE THIS' for instructions.\n\
\n\
\n\
\n\
%  PROC\n\
%	value inch\n\
%	value inches\n\
%	value inchs\n\
%\n\
%  DESCRIPTION\n\
%	Map inches to dots.\n\
\n\
/inch   { 72 mul } bind def\n\
/inches { 72 mul } bind def\n\
/inchs  { 72 mul } bind def\n\
\n\
\n\
%  CONSTANTS\n\
%	autosize\n\
%	autosizeInches\n\
%	autoorient\n\
%	landscape\n\
%	portrait\n\
\n\
/autosize   -1 def\n\
/autosizeInches autosize inches def\n\
/autoorient -1 def\n\
/landscape   1 def\n\
/portrait    2 def\n\
\n\
\n\
%  PROC\n\
%	ImPsPrepare\n\
%\n\
%  DESCRIPTION\n\
%	The orientation, position, and size of the image are determined and\n\
%	transforms made.\n\
%\n\
%	If no explicit image size has been given, the image is autosized to\n\
%	make maximum use of available space.  The aspect ratio of the page is\n\
%	compared with that of the image in order to decide if rotating the\n\
%	image will allow us to scale it up bigger.  The image is then\n\
%	positioned and scaled as large as possible, while maintaining its\n\
%	original aspect ratio.\n\
\n\
/ImPsPrepare\n\
{\n\
	/ImPsImageAspect ImPsImageH ImPsImageW div def\n\
\n\
	% Determine the orientation to use for the image.\n\
	ImPsOrient autoorient eq\n\
	{\n\
		% Defaulted.  Set it to the direction that will let us scale\n\
		% the image up the most.\n\
		ImPsImageAspect 1 lt\n\
		{\n\
			/ImPsOrient landscape def\n\
		}\n\
		{\n\
			/ImPsOrient portrait def\n\
		} ifelse\n\
	} if\n\
\n\
\n\
	% Position and size the image.\n\
	ImPsOrient portrait eq\n\
	{\n\
		% Upright orientation.  Determine size of printed image.\n\
\n\
		ImPsPageLLCornerX ImPsPositionX add\n\
		ImPsPageLLCornerY ImPsPositionY add translate\n\
\n\
		ImPsSizeW autosize eq ImPsSizeW autosizeInches eq or\n\
		ImPsSizeH autosize eq ImPsSizeH autosizeInches eq or and\n\
		{\n\
			% Both sizes defaulted.\n\
			/ImPsSizeH ImPsPageH ImPsPositionX sub def\n\
			/ImPsSizeW ImPsPageW ImPsPositionY sub def\n\
			/ImPsPageAspect ImPsSizeH ImPsSizeW div def\n\
\n\
			ImPsImageAspect ImPsPageAspect lt\n\
			{\n\
				/ImPsSizeH ImPsSizeW ImPsImageAspect mul def\n\
			}\n\
			{\n\
				/ImPsSizeW ImPsSizeH ImPsImageAspect div def\n\
			} ifelse\n\
		}\n"
		"{\n\
			% One or the other size specified.  Set the other one.\n\
			ImPsSizeW autosize eq ImPsSizeW autosizeInches eq or\n\
			{\n\
				% Height given.  Set width.\n\
				/ImPsSizeW ImPsSizeH ImPsImageAspect div def\n\
			} if\n\
			ImPsSizeH autosize eq ImPsSizeH autosizeInches eq or\n\
			{\n\
				% Width given.  Set height.\n\
				/ImPsSizeH ImPsSizeW ImPsImageAspect mul def\n\
			} if\n\
		} ifelse\n\
		ImPsSizeW ImPsSizeH scale\n\
	}\n\
	{\n\
		% Sideways orientation.  Determine size of printed image.\n\
\n\
		ImPsSizeW autosize eq ImPsSizeW autosizeInches eq or\n\
		ImPsSizeH autosize eq ImPsSizeH autosizeInches eq or and\n\
		{\n\
			% Both sizes defaulted.\n\
			/ImPsSizeH ImPsPageW ImPsPositionX sub def\n\
			/ImPsSizeW ImPsPageH ImPsPositionY sub def\n\
			/ImPsPageAspect ImPsSizeH ImPsSizeW div def\n\
\n\
			ImPsImageAspect ImPsPageAspect lt\n\
			{\n\
				/ImPsSizeH ImPsSizeW ImPsImageAspect mul def\n\
			}\n\
			{\n\
				/ImPsSizeW ImPsSizeH ImPsImageAspect div def\n\
			} ifelse\n\
		}\n\
		{\n\
			ImPsSizeW ImPsSizeH\n\
			/ImPsSizeW exch def\n\
			/ImPsSizeH exch def\n\
\n\
			% One or the other size specified.  Set the other one.\n\
			ImPsSizeW autosize eq ImPsSizeW autosizeInches eq or\n\
			{\n\
				% Height given.  Set width.\n\
				/ImPsSizeW ImPsSizeH ImPsImageAspect div def\n\
			} if\n\
			ImPsSizeH autosize eq ImPsSizeH autosizeInches eq or\n\
			{\n\
				% Width given.  Set height.\n\
				/ImPsSizeH ImPsSizeW ImPsImageAspect mul def\n\
			} if\n\
		} ifelse\n\
		ImPsPageLLCornerX ImPsPositionX add ImPsSizeH add\n\
		ImPsPageLLCornerY ImPsPositionY add translate\n\
		90 rotate\n\
\n\
		ImPsSizeW ImPsSizeH scale\n\
	} ifelse\n\
} bind def\n\
\n\
\n\
";





/*
 *  GLOBALS
 *	imPsImageColor	-  Color printing PostScript procedure
 *	imPsImageGray	-  Grayscale printing PostScript procedure
 *	imPsImageMono	-  Monochrome printing PostScript procedure
 *
 *  DESCRIPTION
 *	Each of these three globals defines the same function (proc) for the
 *	PostScript file header.  In each case, the ImPsImage function takes
 *	hex image data and renders it onto the page.  The difference is only
 *	in the type of data being fed ImPsImage.
 *
 *	Some parts of this PostScript code were inspired by similar procedures
 *	designed by Loren "Buck" Buchanan of the Naval Research Lab at
 *	Kestrel Associates Inc.  His ideas are used here with his permission
 *	and our thanks.
 */

static char *imPsImageColor = "\
%  PROC\n\
%	ImPsImage\n\
%\n\
%  DESCRIPTION\n\
%	RGB hex image data is _read from the current file.  If the PostScript\n\
%	device can handle color, the RGB image is imaged as is.  If not, the\n\
%	RGB pixels are converted to grayscale using the NTSC Y equation and\n\
%	imaged.\n\
\n\
/ImPsImage\n\
{\n\
	/buffer     ImPsImageW 3 mul string def\n\
	/graybuffer ImPsImageW string       def\n\
\n\
	ImPsPrepare\n\
\n\
	ImPsImageW ImPsImageH 8\n\
	[ ImPsImageW   0\n\
	  0            ImPsImageH neg\n\
	  0            ImPsImageH ]\n\
\n\
	% Determine if the PostScript device can handle color by checking if\n\
	% the colorimage operator is defined.\n\
	systemdict /colorimage known\n\
	{\n\
		{\n\
			currentfile buffer readhexstring pop\n\
		} false 3\n\
		colorimage\n\
	}\n\
	{\n\
		% The PostScript device cannot do color.  Convert to grayscale.\n\
		{\n\
			% Get the RGB data\n\
			currentfile buffer readhexstring pop pop\n\
\n\
			% For each pixel...\n\
			0 1 ImPsImageW 1 sub\n\
			{\n\
				% Compute gray value and store in graybuffer\n\
				graybuffer exch\n\
				dup 3 mul dup 1 add dup 1 add\n\
				     buffer exch get 0.114 mul\n\
				exch buffer exch get 0.587 mul add\n\
				exch buffer exch get 0.299 mul add\n\
				cvi\n\
				put\n\
			} for\n\
			graybuffer\n\
		}\n\
		image\n\
	} ifelse\n\
	showpage\n\
} bind def\n\
\n\
%%EndProlog\n\
";


static char *imPsImageGray = "\
%  PROC\n\
%	ImPsImage\n\
%\n\
%  DESCRIPTION\n\
%	Grayscale hex image data is _read from the current file and imaged.\n\
\n\
/ImPsImage\n\
{\n\
	/buffer ImPsImageW string def\n\
\n\
	ImPsPrepare\n\
\n\
	ImPsImageW ImPsImageH 8\n\
	[ ImPsImageW   0\n\
	  0            ImPsImageH neg\n\
	  0            ImPsImageH ]\n\
	{\n\
		currentfile buffer readhexstring pop\n\
	}\n\
	image\n\
	showpage\n\
} bind def\n\
\n\
%%EndProlog\n\
";


static char *imPsImageMono = "\
%  PROC\n\
%	ImPsImage\n\
%\n\
%  DESCRIPTION\n\
%	Grayscale hex image data is _read from the current file and imaged.\n\
\n\
/ImPsImage\n\
{\n\
	/buffer ImPsImageW 7 add 8 idiv string def\n\
\n\
	ImPsPrepare\n\
\n\
	ImPsImageW ImPsImageH 1\n\
	[ ImPsImageW   0\n\
	  0            ImPsImageH neg\n\
	  0            ImPsImageH ]\n\
	{\n\
		currentfile buffer readhexstring pop\n\
	}\n\
	image\n\
	showpage\n\
} bind def\n\
\n\
%%EndProlog\n\
";





/*
 *  GLOBAL
 *	imPsScript	-  PostScript page script section
 *
 *  DESCRIPTION
 *	The PostScript file script is executed for each page (in our case
 *	only one).  The generic portion of the script sets some variables
 *	and gives comments to a potential editor of the PostScript file.
 */

static char *imPsScript = "\
%%Page:  1 1\n\
%%BeginPageSetup\n\
\n\
% Determine the available print area.\n\
gsave clippath pathbbox grestore\n\
/ImPsPageH 		exch def\n\
/ImPsPageW  		exch def\n\
/ImPsPageLLCornerY      exch def\n\
/ImPsPageLLCornerX      exch def\n\
/ImPsPageH 		ImPsPageH ImPsPageLLCornerY sub def\n\
/ImPsPageW  		ImPsPageW ImPsPageLLCornerX sub def\n\
\n\
%%EndPageSetup\n\
\n\
\n\
\n\
% CHANGE THIS !\n\
%	If you want to override the automatic sizing and positioning\n\
%	of the image when printing, change the following lines to your\n\
%	desired values.\n\
%\n\
%	If you leave one or the other size set to 'autosize', it will be\n\
%	filled in automatically, maintaining the image's aspect ratio.\n\
\n\
/ImPsOrient	autoorient def		% landscape or portrait or autoorient\n\
\n\
/ImPsSizeH	autosize inches def	% Height in inches\n\
/ImPsSizeW	autosize inches def	% Width in inches\n\
\n\
/ImPsPositionX	0 inches def		% Lower-left corner\n\
/ImPsPositionY	0 inches def		% Lower-left corner\n\
\n\
\n\
\n\
% Do not change this.\n\
";





/*
 *  GLOBAL
 *	imPsData	-  PostScript data section
 *
 *  DESCRIPTION
 *	The data section of a PostScript script gives the image data itself.
 *	In our case it defines the size of the image and invokes the image
 *	rendering procedure.  Following it we dump the image data.
 */

static char *imPsData = "\
/ImPsImageW	%d def			%% Width in pixels\n\
/ImPsImageH	%d def			%% Height in pixels\n\
%%%%BeginData:  %d Hex Lines\n\
ImPsImage\n\
";





/*
 *  GLOBAL
 *	imPsTrailer	-  PostScript trailer section
 *
 *  DESCRIPTION
 *	The trailer of the page, and file, is just a bunch of DSC keywords.
 */

static char *imPsTrailer = "\
%%EndData\n\
%%PageTrailer\n\
%%Trailer\n\
%%EOF\n\
";





/*
 *  FUNCTION
 *	imPsWrite1	-  _write a 1-bit monochrome image to a PostScript file
 *	imPsWriteGray	-  _write a grayscale image to a PostScript file
 *	imPsWrite8	-  _write an 8-bit index image to a PostScript file
 *	imPsWriteRGB	-  _write an RGB image to a PostScript file
 *
 *  DESCRIPTION
 *	The image is retrieved from the tag table and a PostScript header
 *	giving the image's dimensions output.  The appropriate PostScript
 *	procedure is dumped (grayscale or color pixel handling), followed
 *	by standard execution code and the pixels themselves.
 */

static int				/* Returns # of entries used	*/
#ifdef __STDC__
imPsWrite1( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable )
#else
imPsWrite1( pMap, ioType, fd, fp, flagsTable, tagTable )
	ImFileFormatWriteMap *pMap;	/* Write map entry to adhear to	*/
	int      ioType;		/* Type of I/O to perform	*/
	int      fd;			/* Output file descriptor	*/
	FILE     *fp;			/* Output file pointer		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *tagTable;		/* Table of info to _write	*/
#endif
{
	int   ipix;		/* pixel counter		*/
	ImVfbPtr p;		/* VFB pixel pointer		*/
	int   pixel;		/* Gray pixel color		*/
	int   x;		/* Column location		*/
	int       xdim;			/* # columns			*/
	int       ydim;			/* # rows			*/
	ImVfb    *srcVfb;		/* VFB to convert		*/
	time_t     clock;		/* Clock time			*/
	char	   message[512];	/* char string for ImInfo to printout */


	/*  Turn fd into fp so we can use fprintf.			*/
	if ( (ioType & IMFILEIOFD) && (fp = fdopen( fd, "r" )) == NULL )
	{
		ImErrNo = IMESYS;
		return ( -1 );
	}


	/* Dump the header, prolog, script, and data sections.		*/
	TagEntryQValue( TagTableQDirect( tagTable, "image vfb", 0 ), &srcVfb );
	xdim = ImVfbQWidth( srcVfb );
	ydim = ImVfbQHeight( srcVfb );
	clock = time( NULL );
	fprintf( fp, imPsHeader,
		ImErrorProgramName,		/* Creator:		*/
		getlogin( ),			/* For:			*/
		ctime( &clock ),		/* CreationDate:	*/
		ImErrorFileName );		/* Title:		*/

        sprintf (message, "%d x %d",xdim, ydim);
        ImInfo ("Resolution",message);
        ImInfo ("Type","1-bit Monochrome");

	fprintf( fp, "%s", imPsProlog );
	fprintf( fp, "%s", imPsImageMono );
	fprintf( fp, "%s", imPsScript );
	fprintf( fp, imPsData,
		xdim,				/* ImPsImageWidth	*/
		ydim,				/* ImPsImageHeight	*/
		1 + (((xdim + 7) / 8) * 2 * ydim + 71) / 72 );


	/* Dump the pixels.						*/
	p = ImVfbQFirst( srcVfb );
	for ( ipix = 0; ydim; ydim-- )
	{
		for ( pixel = 0, x = 1; x <= xdim; x++, ImVfbSInc( srcVfb, p ) )
		{
			pixel = (pixel << 1) | (ImVfbQMono( srcVfb, p ) & 0x1);
			if ( (x & 0x7) == 0 )
			{
				putc( imPsHex[ ((pixel >> 4) & 0xF) ], fp );
				putc( imPsHex[ (pixel & 0xF) ], fp );
				pixel = 0;
				if( ++ipix >= 36 )
				{
					putc( '\n', fp );
					ipix = 0;
				}
			}
		}
		if ( (xdim & 0x7) != 0 )
		{
			pixel <<= 8 - (xdim & 0x7);
			putc( imPsHex[ ((pixel >> 4) & 0xF) ], fp );
			putc( imPsHex[ (pixel & 0xF) ], fp );
			if( ++ipix >= 36 )
			{
				putc( '\n', fp );
				ipix = 0;
			}
		}
	}

	/* Dump the trailer.						*/
	fprintf( fp, "\n%s", imPsTrailer );
	fflush( fp );

	return ( 1 );		/* Used VFB from tag table		*/
}

static int				/* Returns # of entries used	*/
#ifdef __STDC__
imPsWriteGray( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable )
#else
imPsWriteGray( pMap, ioType, fd, fp, flagsTable, tagTable )
	ImFileFormatWriteMap *pMap;	/* Write map entry to adhear to	*/
	int      ioType;		/* Type of I/O to perform	*/
	int      fd;			/* Output file descriptor	*/
	FILE     *fp;			/* Output file pointer		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *tagTable;		/* Table of info to _write	*/
#endif
{
	int   ipix;		/* pixel counter		*/
	ImVfbPtr p;		/* VFB pixel pointer		*/
	int   pixel;		/* Gray pixel color		*/
	ImVfbPtr last;		/* Last pixel in VFB		*/
	int       xdim;			/* # columns			*/
	int       ydim;			/* # rows			*/
	ImVfb    *srcVfb;		/* VFB to convert		*/
	time_t     clock;		/* Clock time			*/
	char	   message[512];	/* char string for ImInfo to printout */


	/*  Turn fd into fp so we can use fprintf.			*/
	if ( (ioType & IMFILEIOFD) && (fp = fdopen( fd, "r" )) == NULL )
	{
		ImErrNo = IMESYS;
		return ( -1 );
	}


	/* Dump the header, prolog, script, and data sections.		*/
	TagEntryQValue( TagTableQDirect( tagTable, "image vfb", 0 ), &srcVfb );
	xdim = ImVfbQWidth( srcVfb );
	ydim = ImVfbQHeight( srcVfb );
	clock = time( NULL );
	fprintf( fp, imPsHeader,
		ImErrorProgramName,		/* Creator:		*/
		getlogin( ),			/* For:			*/
		ctime( &clock ),		/* CreationDate:	*/
		ImErrorFileName );		/* Title:		*/

        sprintf (message, "%d x %d",xdim, ydim);
        ImInfo ("Resolution",message);
        ImInfo ("Type","8-bit Grayscale");

	fprintf( fp, "%s", imPsProlog );
	fprintf( fp, "%s", imPsImageGray );
	fprintf( fp, "%s", imPsScript );
	fprintf( fp, imPsData,
		xdim,				/* ImPsImageWidth	*/
		ydim,				/* ImPsImageHeight	*/
		1 + (xdim * 2 * ydim + 71) / 72 );


	/* Dump the pixels.						*/
	p    = ImVfbQFirst( srcVfb );
	last = ImVfbQLast( srcVfb );
	for ( ipix = 0; p <= last; ImVfbSInc( srcVfb, p ) )
	{
		pixel = ImVfbQGray( srcVfb, p );
		putc( imPsHex[ (pixel>>4) & 0xf ], fp );
		putc( imPsHex[ pixel & 0xf ], fp );

		if( ++ipix >= 36 )
		{
			putc( '\n', fp );
			ipix = 0;
		}
	}

	/* Dump the trailer.						*/
	fprintf( fp, "\n%s", imPsTrailer );
	fflush( fp );

	return ( 1 );		/* Used VFB from tag table		*/
}

static int				/* Returns # of entries used	*/
#ifdef __STDC__
imPsWrite8( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable )
#else
imPsWrite8( pMap, ioType, fd, fp, flagsTable, tagTable )
	ImFileFormatWriteMap *pMap;	/* Write map entry to adhear to	*/
	int      ioType;		/* Type of I/O to perform	*/
	int      fd;			/* Output file descriptor	*/
	FILE     *fp;			/* Output file pointer		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *tagTable;		/* Table of info to _write	*/
#endif
{
	int   ipix;		/* pixel counter		*/
	ImVfbPtr p;		/* VFB pixel pointer		*/
	int   value;		/* CLT value			*/
	ImVfbPtr last;		/* Last pixel in VFB		*/
		 int   pixel;		/* Gray pixel color		*/
		 ImClt *clt;		/* VFB's color lookup table	*/
		 ImCltPtr c;		/* CLT entry pointer		*/
	int       xdim;			/* # columns			*/
	int       ydim;			/* # rows			*/
	ImVfb    *srcVfb;		/* VFB to convert		*/
	time_t     clock;		/* Clock time			*/
	char	   message[512];	/* char string for ImInfo to printout */


	/*  Turn fd into fp so we can use fprintf.			*/
	if ( (ioType & IMFILEIOFD) && (fp = fdopen( fd, "r" )) == NULL )
	{
		ImErrNo = IMESYS;
		return ( -1 );
	}


	/* Dump the header, prolog, script, and data sections.		*/
	TagEntryQValue( TagTableQDirect( tagTable, "image vfb", 0 ), &srcVfb );
	xdim = ImVfbQWidth( srcVfb );
	ydim = ImVfbQHeight( srcVfb );
	clock = time( NULL );
	fprintf( fp, imPsHeader,
		ImErrorProgramName,		/* Creator:		*/
		getlogin( ),			/* For:			*/
		ctime( &clock ),		/* CreationDate:	*/
		ImErrorFileName );		/* Title:		*/

        sprintf (message, "%d x %d",xdim, ydim);
        ImInfo ("Resolution",message);
        ImInfo ("Type","8-bit Color Indexed");

	fprintf( fp, "%s", imPsProlog );
	fprintf( fp, "%s", imPsImageColor );
	fprintf( fp, "%s", imPsScript );
	fprintf( fp, imPsData,
		xdim,				/* ImPsImageWidth	*/
		ydim,				/* ImPsImageHeight	*/
		1 + (xdim * 6 * ydim + 71) / 72 );


	/* Dump the pixels.						*/
	p    = ImVfbQFirst( srcVfb );
	last = ImVfbQLast( srcVfb );
	clt  = ImVfbQClt( srcVfb );
	for ( ipix = 0; p <= last; ImVfbSInc( srcVfb, p ) )
	{
		pixel = ImVfbQIndex8( srcVfb, p );
		c     = ImCltQPtr( clt, pixel );

		value = ImCltQRed( c );
		putc( imPsHex[ (value>>4) & 0xf ], fp );
		putc( imPsHex[ value & 0xf ], fp );

		value = ImCltQGreen( c );
		putc( imPsHex[ (value>>4) & 0xf ], fp );
		putc( imPsHex[ value & 0xf ], fp );

		value = ImCltQBlue( c );
		putc( imPsHex[ (value>>4) & 0xf ], fp );
		putc( imPsHex[ value & 0xf ], fp );

		if( ++ipix >= 12 )
		{
			putc( '\n', fp );
			ipix = 0;
		}
	}

	/* Dump the trailer.						*/
	fprintf( fp, "\n%s", imPsTrailer );
	fflush( fp );

	return ( 2 );		/* Used VFB & CLT from tag table	*/
}

static int				/* Returns # of entries used	*/
#ifdef __STDC__
imPsWriteRGB( ImFileFormatWriteMap *pMap, int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable )
#else
imPsWriteRGB( pMap, ioType, fd, fp, flagsTable, tagTable )
	ImFileFormatWriteMap *pMap;	/* Write map entry to adhear to	*/
	int      ioType;		/* Type of I/O to perform	*/
	int      fd;			/* Output file descriptor	*/
	FILE     *fp;			/* Output file pointer		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *tagTable;		/* Table of info to _write	*/
#endif
{
	int   ipix;		/* pixel counter		*/
	ImVfbPtr p;		/* VFB pixel pointer		*/
	int   pixel;		/* RGB pixel color		*/
	ImVfbPtr last;		/* Last pixel in VFB		*/
	int       xdim;			/* # columns			*/
	int       ydim;			/* # rows			*/
	ImVfb    *srcVfb;		/* VFB to convert		*/
	time_t      clock;		/* Clock time			*/
	char	   message[512];	/* char string for ImInfo to printout */


	/* Turn fd into fp so we can use fprintf.			*/
	if ( (ioType & IMFILEIOFD) && (fp = fdopen( fd, "r" )) == NULL )
	{
		ImErrNo = IMESYS;
		return ( -1 );
	}


	/* Dump the header, prolog, script, and data sections.		*/
	TagEntryQValue( TagTableQDirect( tagTable, "image vfb", 0 ), &srcVfb );
	xdim = ImVfbQWidth( srcVfb );
	ydim = ImVfbQHeight( srcVfb );
	clock = time( NULL );
	fprintf( fp, imPsHeader,
		ImErrorProgramName,		/* Creator:		*/
		getlogin( ),			/* For:			*/
		ctime( &clock ),		/* CreationDate:	*/
		ImErrorFileName );		/* Title:		*/

        sprintf (message, "%d x %d",xdim, ydim);
        ImInfo ("Resolution",message);
        ImInfo ("Type","24-bit RGB");


	fprintf( fp, "%s", imPsProlog );
	fprintf( fp, "%s", imPsImageColor );
	fprintf( fp, "%s", imPsScript );
	fprintf( fp, imPsData,
		xdim,				/* ImPsImageWidth	*/
		ydim,				/* ImPsImageHeight	*/
		1 + (xdim * 6 * ydim + 71) / 72 );


	/* Dump the pixels.						*/
	p    = ImVfbQFirst( srcVfb );
	last = ImVfbQLast( srcVfb );
	for ( ipix = 0; p <= last; ImVfbSInc( srcVfb, p ) )
	{
		pixel = ImVfbQRed( srcVfb, p );
		putc( imPsHex[ (pixel>>4) & 0xf ], fp );
		putc( imPsHex[ pixel & 0xf ], fp );

		pixel = ImVfbQGreen( srcVfb, p );
		putc( imPsHex[ (pixel>>4) & 0xf ], fp );
		putc( imPsHex[ pixel & 0xf ], fp );

		pixel = ImVfbQBlue( srcVfb, p );
		putc( imPsHex[ (pixel>>4) & 0xf ], fp );
		putc( imPsHex[ pixel & 0xf ], fp );

		if( ++ipix >= 12 )
		{
			putc( '\n', fp );
			ipix = 0;
		}
	}

	/* Dump the trailer.						*/
	fprintf( fp, "\n%s", imPsTrailer );
	fflush( fp );

	return ( 1 );		/* Used VFB from tag table		*/
}
