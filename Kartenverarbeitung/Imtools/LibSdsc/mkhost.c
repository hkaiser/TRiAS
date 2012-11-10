/**
 **	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/mkhost.c,v 1.5 1995/06/30 21:52:54 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/mkhost.c,v 1.5 1995/06/30 21:52:54 bduggan Exp $"

/**
 **  FILE
 **	mkhost.c	-  Write host format floats to file
 **
 **  PROJECT
 **	libSDSC		-  SDSC standard function library
 **
 **  DESCRIPTION
 **	This program writes a set of float and double test data to a file
 **	named after the host's floating point format.  Writing is done using
 **	the write() system call... not the binary I/O package.
 **
 **  PUBLIC CONTENTS
 **	main		-  main program
 **
 **  PRIVATE CONTENTS
 **	none
 **
 **  HISTORY
 **	$Log: mkhost.c,v $
 **	Revision 1.5  1995/06/30  21:52:54  bduggan
 **	took out prototypes
 **
 **	Revision 1.4  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.3  1994/10/03  16:28:03  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Added forward declarations.
 **	Updated copyright message.
 **
 **	Revision 1.2  92/09/02  13:31:20  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.1  91/01/09  16:46:59  nadeau
 **	Initial revision
 **	
 **/

#include "sdsccopyright.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "sdsc.h"



/*
 *  GLOBAL
 *	verData	-  Standard floating point test numbers
 *
 *  DESCRIPTION
 *	The verData array contains the standard floating point numbers
 *	written to the test file for each float format/size/byte order
 *	combination.
 */

#define NVERDATA	4	/* # of test data items			*/
float verData1[NVERDATA] =	/* verification data			*/
{
	0.0,			/* vers zero/underflow case		*/
	1.0, 			/* Simple exponent, no mantissa		*/
	3.14159,		/* Just a nice number with a mantissa	*/
	-12345.0,		/* Medium sized negative number		*/
};
double verData2[NVERDATA] =	/* verification data			*/
{
	0.0,			/* vers zero/underflow case		*/
	1.0, 			/* Simple exponent, no mantissa		*/
	3.14159,		/* Just a nice number with a mantissa	*/
	-12345.0,		/* Medium sized negative number		*/
};





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	The test file is opened (destroying the old one, if any) and the
 *	floating point test data written using a write() call.
 */

void
main( )
{
	int fd;			/* ver file's descriptor		*/
	BinMachineInfo *mi;	/* Machine information			*/
	char filename[100];	/* ver file's name			*/

	mi = BinQMachine( );
	sprintf( filename, "%s_%s", mi->bin_floatFormatName, mi->bin_byteOrderName );

	/*
	 *  Destroy the current data file (if any), and create a
	 *  new one.
	 */
	_unlink( filename );
	if ( (fd = _open( filename, O_WRONLY|O_CREAT, 0666 )) == -1 )
	{
		perror( filename );
		exit( 1 );
	}


	/*
	 *  Write data to the file using a write() system call.  This
	 *  guarantees that the bytes in the file are in the same format
	 *  as they are on the host.
	 */
	if ( _write( fd, verData1, sizeof( verData1 ) ) == -1 )
	{
		perror( filename );
		exit( 1 );
	}
	if ( _write( fd, verData2, sizeof( verData2 ) ) == -1 )
	{
		perror( filename );
		exit( 1 );
	}
	_close( fd );
	printf( "Wrote %d bytes to '%s'\n", sizeof( verData1 ) +
		sizeof( verData2 ), filename );
}
