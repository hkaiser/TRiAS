/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/imcgm.c,v 1.5 1995/06/29 00:28:04 bduggan Exp $
 **	Copyright( c) 1995  San Diego Supercomputer Center( SDSC)
 **		San Diego, California, USA
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
 **				San Diego, CA  92186-9784
 **				(619) 534-5000
 **/

#define HEADER        "    $Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/imcgm.c,v 1.5 1995/06/29 00:28:04 bduggan Exp $"

/**
 **  FILE
 **	imcgm.c		-  CGM file I/O
 **
 **  PROJECT
 **	libim	-  SDSC image manipulation library
 **
 **  DESCRIPTION
 **	imcgm.c contains routines to read and write CGM files for
 **	the image manipulation library.  Raster data read in is stored
 **	in a VFB.  Raster data written out is taken from a tag table.
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	ImCgmRead		f  read a CGM file
 **
 **  PRIVATE CONTENTS
 **	imCgmHeaderInfo		t  CGM file header information
 **	imCgmHeaderFields	v  imCgmHeaderInfo description for Bin pkg
 **
 **  HISTORY
 **	$Log: imcgm.c,v $
 **	Revision 1.5  1995/06/29  00:28:04  bduggan
 **	updated copyright year
 **
 **	Revision 1.4  1994/10/04  20:20:49  bduggan
 **	added IM to macro names
 **
 **	Revision 1.3  91/10/03  08:48:31  nadeau
 **	Fixed #includes.
 **	
 **	Revision 1.2  91/02/12  11:44:17  nadeau
 **	Changed read to make a temp file if input is a pipe or a
 **	file whose name we can't get.  Removed empty write routine.
 **	
 **	Revision 1.1  91/01/30  17:22:33  mjb
 **	Initial revision
 **	
 **/

#include <fcntl.h>
#include "iminternal.h"


/* where to find the gplot program:					*/
#define IMGPLOT		"/usr/local/bin/gplot"

/*
 * use the program as:
 *	gplot -dhdf2 -X1024 -Y1024 filename.cgm images.hdf
 */


private char *hdfFileTemp = { "/usr/tmp/hdf.XXXXXX" };
private char *cgmFileTemp = { "/usr/tmp/cgm.XXXXXX" };





/*
 *  FUNCTION
 *	ImCgmRead	-  read a CGM file
 *
 *  DESCRIPTION
 *	The CGM file is processed by gplot into an hdf file.  The HDF
 *	file is then read in by recursing into the image file read again.
 */

int					/* Returns # tags read in	*/
#ifdef __STDC__
ImCgmRead( int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *tagTable )
#else
ImCgmRead( ioType, fd, fp, flagsTable, tagTable )
	int         ioType;		/* I/O flags			*/
	int         fd;			/* Input file descriptor	*/
	FILE	   *fp;			/* Input file pointer		*/
	TagTable   *flagsTable;		/* Flags			*/
	TagTable   *tagTable;		/* Tag table to add to		*/
#endif
{
	TagEntry    *fileEntry;		/* filename flagsTable entry	*/
	TagTable    *newFlagsTable;	/* New flags table		*/
	char *	     tmp;		/* Tmp name holder		*/
	int	     stat;		/* return status		*/
	char	     cmd[1024];		/* command line			*/

	char         cgmFileName[1024];	/* name of cgm file		*/
	int	     cgmFd;		/* CGM file descriptor		*/
	int	     n;			/* # of bytes read		*/
	char	     buffer[1024];	/* Temp file copy buffer	*/

	FILE *	     hdfFp;		/* hdf file pointer		*/
	char         hdfFileName[1024];	/* name of hdf file		*/


	/*
	 *  Figure out how to get a file name for the CGM data.
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
		strcpy ( cgmFileName, tmp );
		cgmFd = -1;
	}
	else
	{
		/*
		 *  We can't get the file name, or input is a stream.
		 *  In either case, create a temporary file and copy the
		 *  input to that file.
		 */
		strcpy( cgmFileName, cgmFileTemp );
		(void) mktemp( cgmFileName );
		if ( (cgmFd = open( cgmFileName, O_WRONLY | O_CREAT, 0666 )) == -1 )
		{
			ImErrorFatal( "Cannot create temp file", -1, IMESYS );
		}
		if ( ioType & IMFILEIOFD )
		{
			while ( (n = read( fd, buffer, sizeof( buffer ) )) > 0 )
				write( cgmFd, buffer, n );
		}
		else
		{
			while ( (n = fread( buffer, sizeof( buffer ), 1, fp )) > 0 )
				write( cgmFd, buffer, n );
		}
		close( cgmFd );
	}



	/*
	 *  Invoke 'gplot' to do the conversion from a CGM file to an
	 *  HDF image file.
	 */
	strcpy( hdfFileName, hdfFileTemp );
	(void)mktemp( hdfFileName );
	sprintf( cmd, "%s -dhdf2 -X1024 -Y1024 %s %s", IMGPLOT,
		cgmFileName, hdfFileName );
	system( cmd );
	if ( cgmFd != -1 )
		unlink( cgmFileName );


	/*
	 *  Open up the resulting HDF file.
	 */
	if ( (hdfFp = fopen( hdfFileName, "r" )) == NULL )
	{
		ImErrorFatal( "Cannot open HDF temporary file", -1, IMESYS );
	}


	/*
	 *  Create a new flags table that uses the new HDF file's name
	 *  instead of the old CGM file name.  This also passes along to
	 *  the HDF read routines any flags that may have been included.
	 */
	newFlagsTable = TagTableAlloc( );
	if ( newFlagsTable == TAGTABLENULL )
	{
		unlink( hdfFileName );
		ImErrNo = IMEMALLOC;
		ImErrorFatal( ImQError( ), -1, ImErrNo );
	}
	TagTableCopy( flagsTable, newFlagsTable, 0,
		TagTableQNEntry( flagsTable, NULL )-1 );
	fileEntry = TagTableQDirect( newFlagsTable, "file name" );
	tmp = hdfFileName;
	if ( fileEntry == TAGENTRYNULL )
		TagTableAppend( newFlagsTable,
			TagEntryAlloc( "file name", POINTER, &tmp ) );
	else
		TagTableReplace( newFlagsTable, TagEntryQNthEntry( fileEntry ),
			TagEntryAlloc( "file name", POINTER, &tmp ) );


	stat = ImFileFRead( hdfFp, "hdf", flagsTable, tagTable );

	fclose( hdfFp );
	unlink( hdfFileName );

	return( stat );
}
