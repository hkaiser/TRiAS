/**
 **	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/binverify.c,v 1.9 1995/06/30 21:58:03 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/binverify.c,v 1.9 1995/06/30 21:58:03 bduggan Exp $"

/**
 **  FILE
 **	binverify.c	-  binary I/O package verification suite
 **
 **  PROJECT
 **	libSDSC		-  SDSC utilities library
 **
 **  DESCRIPTION
 **	This file contains routines involved in the verification of the binary
 **	I/O package on a computing platform.
 **
 **  PUBLIC CONTENTS
 **
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	main		f  Run the verification
 **
 **  PRIVATE CONTENTS
 **	VERFILE		d  Name of verification data file to use
 **	verProgram	v  Program name
 **	verFD		v  Verification data file descriptor
 **	verErrors	v  Number of errors encountered
 **
 **	verCreate	f  Create the data file
 **	verDestroy	m  Destroy the data file
 **	verOpen		f  Open the data file
 **	verClose	m  Close the data file
 **
 **	verSameSize	f  ver read/write of items the same size as in the file
 **	verSmaller	f  ver read/write of items of smaller size in the file
 **	verBigger	f  ver read/write of items of bigger size in the file
 **
 **	VERINTWRITE	m  build a function to ver writing
 **	VERINTREAD	m  build a function to ver reading
 **	VERINTTYPE	m  build functions to ver a type
 **
 **	verSameSizeWriteType	f  write 'Type' at the same size
 **	verSameSizeReadType	f  read 'Type' at the same size
 **	verSmallerWriteType	f  write 'Type' at a smaller size
 **	verSmallerReadType	f  read 'Type' at a smaller size
 **	verBiggerWriteType	f  write 'Type' at a bigger size
 **	verBiggerReadType	f  read 'Type' at a bigger size
 **
 **	verTruncErrors		v integer truncation error counter
 **	verOverflowErrors	v float overflow error counter
 **	verUnderflowErrors	v float underflow error counter
 **	verErrorHandler		f error handler for truncation errors
 **
 **	verIntegers	f  verify integer write / read
 **
 **	verCheckFloat	f  check two lists of floating point values
 **	verCheckDouble	f  check two lists of double values
 **
 **	verHostFloats	f  verify our understanding of the host's float format
 **	verReadFloats	f  verify reading of floating point formats
 **	verReadCheck	f  do the actual check of a format
 **	verWriteFloats	f  verify pkg write of floating point formats
 **	verWritecheck	f  do the actual check of a format
 **
 **	verReadStructs	f  verify structure read
 **	verWriteStructs	f  verify structure write
 **
 **  HISTORY
 **	$Log: binverify.c,v $
 **	Revision 1.9  1995/06/30  21:58:03  bduggan
 **	changed unsigned char to void
 **
 **	Revision 1.8  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.7  1995/04/21  17:57:29  bduggan
 **	Changed stderr to stdout.
 **	Replaced prototypes for standard functions with
 **	include files.
 **
 **	Revision 1.6  1994/10/03  16:24:06  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Updated comments.
 **	Updated version number.
 **	Updated copyright message.
 **
 **	Revision 1.5  92/09/10  12:16:56  nadeau
 **	Rearranged code to declare functions or function types
 **	before they're used.
 **	
 **	Revision 1.4  92/09/02  13:30:28  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.3  91/12/23  11:41:48  nadeau
 **	Extended integer read and write function-creation macros to
 **	include testing of BinSRead and BinSWrite.
 **	
 **	Revision 1.2  91/09/17  19:21:45  nadeau
 **	Removed usage of empty comments to build names in function
 **	building macros.  Updated comments.  Spiffed up floating
 **	point compares and error prints to include hex byte dumps.
 **	Spiffed up output report comments to explain each of the
 **	tests and what they proved.  Indented things nicer.
 **	
 **	Revision 1.1  91/01/09  16:46:55  nadeau
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
 *  FUNCTION DECLARATIONS
 *
 *	We'd like to include the "proper" include files that provide the
 *	assorted prototypes for everything.  Unfortunately, no two OS's
 *	seem to be able to agree upon the names for such include files.
 *	Is it "strings.h" or "string.h"?  Is it "unistd.h" or "io.h"?
 *	Is it "memory.h" or "bstring.h"?  And so on.
 *
 *	To avoid massive numbers of OS-specific #ifdef's for these inclusions
 *	we just include the necessary prototypes here directly.
 */
#ifdef __STDC__
static void	verCreate( void );
static void	verOpen( void );
static int	verErrorHandler( int, int, int, void *, int, int );
static int	verIntegers( int );
static int	verCheckFloat( float *, int, float * );
static int	verCheckDouble( double *, int, double * );
static int	verHostFloats( void );
static int	verReadFloats( void );
static int	verReadCheck( char *, int, int, int, int );
static int	verWriteFloats( void );
static int	verWriteCheck( char *, int, int, int, int );
static int	verReadStructs( void );
static int	verWriteStructs( void );
#else

static void	verCreate( );
static void	verOpen( );
static int	verErrorHandler( );
static int	verIntegers( );
static int	verCheckFloat( );
static int	verCheckDouble( );
static int	verHostFloats( );
static int	verReadFloats( );
static int	verReadCheck( );
static int	verWriteFloats( );
static int	verWriteCheck( );
static int	verReadStructs( );
static int	verWriteStructs( );
#endif




/*
 *  VERFILE is the name of the temporary data file created by these
 *  routines.  Upon completion of each test, the file is destroyed.
 */
#if defined(MSWIND)
#define VERFILE		"C:\\Temp\\binverify.tmp"
#else
#define VERFILE		"/usr/tmp/binverify.tmp"
#endif // MSWIND

static char *verProgram;	/* Program name				*/
static int   verFD;		/* Data file descriptor			*/
static int   verErrors;		/* Number of errors encountered		*/

static int  *verRes;		/* Resolution table for the types	*/
static char **verNames;		/* Type names				*/
static BinMachineInfo *machineInfo;	/* Machine info			*/





/*
 *  FUNCTION
 *	verTruncErrors		- integer truncation error counter
 *	verShouldTruncErrors	- # integer truncation error we should get
 *	verOverflowErrors	- float overflow error counter
 *	verShouldOverflowErrors	- # float overflow error we should get
 *	verUnderflowErrors	- float underflow error counter
 *	verShouldUnderflowErrors- # float underflow error we should get
 *	verErrorHandler		- error handler for truncation errors
 *
 *  DESCRIPTION
 *	verErrorHandler is nominated as an error handling function to count
 *	errors during binary I/O read and write operations.
 */

static int verTruncErrors     = 0;
static int verOverflowErrors  = 0;
static int verUnderflowErrors = 0;

static int verShouldTruncErrors     = 0;
static int verShouldOverflowErrors  = 0;
static int verShouldUnderflowErrors = 0;

static int				/* Returns nothing		*/
#ifdef __STDC__
verErrorHandler( int fd, int op, int reason, void *data,
	int frombits, int tobits )
#else
verErrorHandler( fd, op, reason, data, frombits, tobits )
	int fd;				/* File descriptor		*/
	int op;				/* Operation code		*/
	int reason;			/* Reason code			*/
	void *data;			/* Faulty data			*/
	int frombits, tobits;		/* From and to size		*/
#endif
{
	switch ( reason )
	{
	case BINEINTEGERTRUNC:	/* Integer truncation occurred.		*/
		verTruncErrors++;
		return ( 0 );

	case BINEFLOATOVERFLOW:	/* Floating point overflow occurred.	*/
		verOverflowErrors++;
		return ( 0 );

	case BINEFLOATUNDERFLOW:/* Floating point underflow occurred.	*/
		verUnderflowErrors++;
		return ( 0 );
	}
	return ( 0 );
}





/*
 *  MACRO
 *	VERINTWRITE	-  build a function to verify integer writing
 *	VERINTREAD	-  build a function to verify integer reading
 *
 *  DESCRIPTION
 *	These macros each create an entire function to verify reading or
 *	writing a specific host integer type, and a specific in-the-file size.
 *	The name of the function to be generated, the host type, and
 *	the in-the-file size are all arguments to the macros.
 *
 *	VERINTWRITE( ) fills a buffer "buf" with a string of values, one for
 *	each bit position in the resolution of the type.  For instance,
 *	for a 1-byte char type with 1-byte resolution and 8-bits per byte
 *	the buffer will contain the sequence:
 *
 *		0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
 *
 *	Each of these are written out in two ways:  via BinWrite( ), and via
 *	BinSWrite( ) to a buffer then write( )-ing that buffer out.
 *
 *	So, the total number of items written out by VERINTWRITE( ) is:
 *
 *		byte-resolution-of-type * 8 bits/byte * 2 write methods
 *
 *	For the 8-bit char type we get:
 *
 *		1 * 8 * 2 = 16 values written to the test file
 *
 *	The number of actual bytes written is dependent upon the size
 *	argument to the macro.  That size, in bytes, is equal to, less than,
 *	or greater than the size of the type itself, depending upon phase
 *	of testing in this verification suite.  For testing of a 2-byte
 *	resolution short, for instance, we'll write out the following number
 *	of values:
 *
 *		2 * 8 * 2 = 32 values
 *
 *	In phase 1 we'll write out each 2-byte short as 2 bytes, giving us:
 *
 *		32 values * 2 bytes/value = 64 bytes
 *
 *	In phase 2 we'll write out each 2-byte short as 1 byte, giving us:
 *
 *		32 values * 1 bytes/value = 32 bytes
 *
 *	And in phase 3 we'll write out each 2-byte short as 3 bytes, giving us:
 *
 *		32 values * 3 bytes/value = 96 bytes
 *
 *
 *	Whenever we write a value out taking fewer bytes than is required,
 *	we'll get truncation.  We count those truncation errors (via the
 *	Binary I/O library's error callback) and make sure we get the right
 *	number (checked in verIntegers( )).  VERINTWRITE( ) computes the
 *	number of truncation errors that *should* occur.  Later, if
 *	verIntegers( ) finds a different number, then something is wrong.
 */

#ifdef __STDC__
#define VERDECLARE( name )						\
static int name( void );						\
									\
static int				/* Returns nothing		*/\
name( void )
#else
#define VERDECLARE( name )						\
static int name( );							\
									\
static int				/* Returns nothing		*/\
name( )
#endif

#define VERINTWRITE( name, type, typename, size )			\
VERDECLARE( name )							\
{									\
	int i;				/* Counter			*/\
	int res;			/* Resolution of type		*/\
	type buf[8*sizeof(type)];	/* Buffer			*/\
	unsigned char data[8*sizeof(type)*sizeof(type)*2];/* Pre-write data buffer*/\
	char msg[100];			/* Message holder		*/\
									\
	res = 8 * verRes[typename];					\
	i = res - 1;							\
	do								\
	{								\
		buf[i] = ((type)1) << i;				\
	}								\
	while ( i-- );							\
	if ( (size) < verRes[typename] )				\
	{								\
		/* will get 1 truncation error for each bit of each */	\
		/* byte in the difference, for each write method    */	\
		verShouldTruncErrors += 8 * (verRes[typename] - (size)) * 2;\
	}								\
	if ( BinWrite( verFD, buf, (typename), (size), res ) == -1)	\
	{								\
		sprintf( msg, "BinWrite %s\n", verNames[typename] );	\
		BinPError( msg );					\
		exit( 1 );						\
	}								\
	if ( (i=BinSWrite( data, buf, (typename), (size), res )) == -1)	\
	{								\
		sprintf( msg, "BinSWrite %s\n", verNames[typename] );	\
		BinPError( msg );					\
		exit( 1 );						\
	}								\
	if ( _write( verFD, data, i ) == -1 )				\
	{								\
		sprintf( msg, "write %s\n", verNames[typename] );	\
		perror( msg );						\
		exit( 1 );						\
	}								\
	return ( 0 );							\
}

#define VERINTREAD( name, type, typename, size )			\
VERDECLARE( name )							\
{									\
	type buf[8*sizeof(type)];	/* Buffer			*/\
	int i, n;			/* Counters			*/\
	unsigned long mask;		/* Mask for values		*/\
	int res;			/* Resolution of type		*/\
	unsigned char data[8*sizeof(type)*sizeof(type)*2];/* read data buffer*/\
	char msg[100];			/* Message holder		*/\
	type wroteOut;			/* What was written		*/\
	type readIn;			/* What was read in		*/\
									\
	res = 8 * verRes[typename];					\
	if ( (size)*8 >= res )						\
		mask = ~((type)0);					\
	else								\
		mask = ~((~((type)0))<<((size)*8));			\
									\
	if ( (n=BinRead( verFD, buf, (typename), (size), res )) == -1 )	\
	{								\
		sprintf( msg, "BinRead %s\n", verNames[typename] );	\
		BinPError( msg );					\
		exit( 1 );						\
	}								\
	for ( i = 0; i < res; i++ )					\
	{								\
		wroteOut = (((type)1)<<i) & (type)mask;			\
		readIn   = buf[i] & (type)mask;				\
		if ( readIn != wroteOut )				\
		{							\
			fprintf( stdout,                                \
"            %s file error:  wrote 0x%016lx, but read 0x%016lx\n",      \
				verNames[typename],                     \
				(unsigned long)wroteOut,                \
				(unsigned long)readIn );                \
			verErrors++;					\
		}							\
	}								\
									\
	if ( _read( verFD, data, n ) == -1 )				\
	{								\
		sprintf( msg, "read %s\n", verNames[typename] );	\
		perror( msg );						\
		exit( 1 );						\
	}								\
	if ( BinSRead( data, buf, (typename), (size), res ) == -1 )	\
	{								\
		sprintf( msg, "BinSRead %s\n", verNames[typename] );	\
		BinPError( msg );					\
		exit( 1 );						\
	}								\
	for ( i = 0; i < res; i++ )					\
	{								\
		wroteOut = (((type)1)<<i) & (type)mask;			\
		readIn   = buf[i] & (type)mask;				\
		if ( readIn != wroteOut )				\
		{							\
			fprintf( stdout, 				\
"            %s string error:  wrote 0x%016lx, but read 0x%016lx\n",    \
				verNames[typename], 			\
				(unsigned long)wroteOut, 		\
				(unsigned long)readIn );		\
			verErrors++;					\
		}							\
	}								\
	return ( 0 );							\
}





/*
 *  MACRO
 *	ver...		-  ver functions
 *
 *  DESCRIPTION
 *	The VERINTREAD and VERINTWRITE macros build six functions for
 *	each type to be tested:
 *
 *		same-size read and write:
 *			the size of the item written to, and read from
 *			the file is the same as the size of the item on
 *			the host.
 *
 *		smaller-size read and write:
 *			the size of the item written to, and read from
 *			the file is one byte smaller than the size of the
 *			item on the host.
 *
 *		bigger-size read and write:
 *			the size of the item written to, and read from
 *			the file is one byte larger than the size of the
 *			item on the host.
 */

VERINTWRITE( verSameSizeWritechar,char, CHAR, verRes[CHAR] )
VERINTREAD(  verSameSizeReadchar, char, CHAR, verRes[CHAR] )
VERINTWRITE( verSmallerWritechar, char, CHAR, verRes[CHAR] - 1 )
VERINTREAD(  verSmallerReadchar,  char, CHAR, verRes[CHAR] - 1 )
VERINTWRITE( verBiggerWritechar,  char, CHAR, verRes[CHAR] + 1 )
VERINTREAD(  verBiggerReadchar,   char, CHAR, verRes[CHAR] + 1 )

VERINTWRITE( verSameSizeWriteuchar,unsigned char, UCHAR, verRes[UCHAR] )
VERINTREAD(  verSameSizeReaduchar, unsigned char, UCHAR, verRes[UCHAR] )
VERINTWRITE( verSmallerWriteuchar, unsigned char, UCHAR, verRes[UCHAR] - 1 )
VERINTREAD(  verSmallerReaduchar,  unsigned char, UCHAR, verRes[UCHAR] - 1 )
VERINTWRITE( verBiggerWriteuchar,  unsigned char, UCHAR, verRes[UCHAR] + 1 )
VERINTREAD(  verBiggerReaduchar,   unsigned char, UCHAR, verRes[UCHAR] + 1 )

VERINTWRITE( verSameSizeWriteshort,short, SHORT, verRes[SHORT] )
VERINTREAD(  verSameSizeReadshort, short, SHORT, verRes[SHORT] )
VERINTWRITE( verSmallerWriteshort, short, SHORT, verRes[SHORT] - 1 )
VERINTREAD(  verSmallerReadshort,  short, SHORT, verRes[SHORT] - 1 )
VERINTWRITE( verBiggerWriteshort,  short, SHORT, verRes[SHORT] + 1 )
VERINTREAD(  verBiggerReadshort,   short, SHORT, verRes[SHORT] + 1 )

VERINTWRITE( verSameSizeWriteushort,unsigned short, USHORT, verRes[USHORT] )
VERINTREAD(  verSameSizeReadushort, unsigned short, USHORT, verRes[USHORT] )
VERINTWRITE( verSmallerWriteushort, unsigned short, USHORT, verRes[USHORT] - 1 )
VERINTREAD(  verSmallerReadushort,  unsigned short, USHORT, verRes[USHORT] - 1 )
VERINTWRITE( verBiggerWriteushort,  unsigned short, USHORT, verRes[USHORT] + 1 )
VERINTREAD(  verBiggerReadushort,   unsigned short, USHORT, verRes[USHORT] + 1 )

VERINTWRITE( verSameSizeWriteint,int, INT, verRes[INT] )
VERINTREAD(  verSameSizeReadint, int, INT, verRes[INT] )
VERINTWRITE( verSmallerWriteint, int, INT, verRes[INT] - 1 )
VERINTREAD(  verSmallerReadint,  int, INT, verRes[INT] - 1 )
VERINTWRITE( verBiggerWriteint,  int, INT, verRes[INT] + 1 )
VERINTREAD(  verBiggerReadint,   int, INT, verRes[INT] + 1 )

VERINTWRITE( verSameSizeWriteuint,unsigned int, UINT, verRes[UINT] )
VERINTREAD(  verSameSizeReaduint, unsigned int, UINT, verRes[UINT] )
VERINTWRITE( verSmallerWriteuint, unsigned int, UINT, verRes[UINT] - 1 )
VERINTREAD(  verSmallerReaduint,  unsigned int, UINT, verRes[UINT] - 1 )
VERINTWRITE( verBiggerWriteuint,  unsigned int, UINT, verRes[UINT] + 1 )
VERINTREAD(  verBiggerReaduint,   unsigned int, UINT, verRes[UINT] + 1 )

VERINTWRITE( verSameSizeWritelong,long, LONG, verRes[LONG] )
VERINTREAD(  verSameSizeReadlong, long, LONG, verRes[LONG] )
VERINTWRITE( verSmallerWritelong, long, LONG, verRes[LONG] - 1 )
VERINTREAD(  verSmallerReadlong,  long, LONG, verRes[LONG] - 1 )
VERINTWRITE( verBiggerWritelong,  long, LONG, verRes[LONG] + 1 )
VERINTREAD(  verBiggerReadlong,   long, LONG, verRes[LONG] + 1 )

VERINTWRITE( verSameSizeWriteulong,unsigned long, ULONG, verRes[ULONG] )
VERINTREAD(  verSameSizeReadulong, unsigned long, ULONG, verRes[ULONG] )
VERINTWRITE( verSmallerWriteulong, unsigned long, ULONG, verRes[ULONG] - 1 )
VERINTREAD(  verSmallerReadulong,  unsigned long, ULONG, verRes[ULONG] - 1 )
VERINTWRITE( verBiggerWriteulong,  unsigned long, ULONG, verRes[ULONG] + 1 )
VERINTREAD(  verBiggerReadulong,   unsigned long, ULONG, verRes[ULONG] + 1 )

#undef VERINTWRITE
#undef VERINTREAD
#undef VERDECLARE




/*
 *  FUNCTION
 *	verCreate	-  Create the data file
 *	verDestroy	-  Destroy the data file
 *	verOpen		-  Open the data file
 *	verClose	-  Close the data file
 *
 *  DESCRIPTION
 *	These routines and macros create, open, or close the binary data file
 *	used by these tests.
 */

static void				/* Returns nothin		*/
#ifdef __STDC__
verCreate( void )
#else
verCreate( )
#endif
{
	if ( (verFD = _open( VERFILE, _O_WRONLY|_O_CREAT, 0666 )) == -1 )
	{
		perror( VERFILE );
		exit( 1 );
	}
}

#define verDestroy()	_unlink( VERFILE )

static void				/* Returns nothin		*/
#ifdef __STDC__
verOpen( void )
#else
verOpen( )
#endif
{
	if ( (verFD = _open( VERFILE, _O_RDWR )) == -1 )
	{
		perror( VERFILE );
		exit( 1 );
	}
}

#define verClose()	_close( verFD )






/*
 *  FUNCTION
 *	main		-  Control the testing
 *
 *  DESCRIPTION
 *	This program verifies the correct functioning of the binary I/O
 *	package.  Three sets of tests are done:
 *
 *		1.  Read and write integers:
 *			Integer data is written and read back at different
 *			sizes and different byte orders.  The data file
 *			created is machine-specific.
 *
 *		2.  Read and write floats:
 *			Floating point data is written and read back in
 *			different formats and different sizes.  Standard
 *			data files are used and compared against.
 *
 *		3.  Read and write structures:
 *			Structures of integers and floats are written and
 *			read back.
 */
void
#ifdef __STDC__
main( int argc, char *argv[ ] )
#else
main( argc, argv )
	int argc;			/* Argument count		*/
	char *argv[ ];			/* Argumetn vector		*/
#endif
{
	/*
	 *  If any arguments are given, issue an error.
	 */
	if ( argc != 1 )
	{
		fprintf( stderr, "Too many arguments.\n" );
		fprintf( stderr, "Usage is:  %s\n", argv[0] );
		fprintf( stderr, "Verify the correct functioning of the binary file I/O package on the\n" );
		fprintf( stderr, "current compute platform.  No arguments are necessary.  Output messages\n" );
		fprintf( stderr, "are written to stderr.\n" );
		exit( 1 );
	}
	verProgram  = argv[0];
	machineInfo = BinQMachine( );
	verRes      = machineInfo->bin_typeRes;
	verNames    = machineInfo->bin_typeName;

	verDestroy( );

	fprintf( stdout, "Binary I/O Verification Suite\n" );
	fprintf( stdout, "------------------------------------------------------------------------\n" );


	/*
	 *  Integer tests.
	 *	First for MBF, then for LBF, write and read back integers
	 *	the same size as the host's, 1 byte smaller than the host's,
	 *	and 1 byte larger than the host's.
	 */
	fprintf( stdout, "\nTest #1:  Integer Read/Write Verification\n" );
	fprintf( stdout, "    Write then read back integers of the same size as the host's, one byte\n" );
	fprintf( stdout, "    smaller than the host's, then one byte larger than the host's.  Repeat\n" );
	fprintf( stdout, "    the procedure for MBF and LBF byte orders.\n\n" );
	fprintf( stdout, "    This confirms that truncation, zero padding and sign-extension are being\n" );
	fprintf( stdout, "    handled properly.  This also checks read and write ability for byte orders\n" );
	fprintf( stdout, "    the same and different from the host's.\n" );
	verIntegers( BINMBF );
	verIntegers( BINLBF );



	/*
	 *  Floating point tests.
	 *	Verify that the pkg's idea of the host's floating point
	 *	format is correct.
	 */
	fprintf( stdout, "\nTest #2:  Host Floating Point Read/Write Verification\n" );
	fprintf( stdout, "    Write floating point values to a file without the binary I/O package, then\n" );
	fprintf( stdout, "    read them in with the package.  Next, write floating point values to a file\n" );
	fprintf( stdout, "    using the package, then read them back in without it\n\n" );
	fprintf( stdout, "    This confirms that we truely understand the host's floating point format on\n" );
	fprintf( stdout, "    read and write operations.\n" );
	verHostFloats( );



	/*
	 *  More Floating point tests.
	 *	Verify that we can read in other floating point formats.
	 *
	 *	Verify that we can write out other floating point formats.
	 */
	fprintf( stdout, "\nTest #3:  General Floating Point Read/Write Verification\n" );
	fprintf( stdout, "    Read floating point values from standard test files for each supported\n" );
	fprintf( stdout, "    floating point format.  Each file contains known good floating point\n" );
	fprintf( stdout, "    values.  Compare the read in values with what we should have received.\n\n" );
	fprintf( stdout, "    Write floating point values in each supported format and read them back in.\n" );
	fprintf( stdout, "    Compare the read in values with what we think we wrote.\n\n" );
	fprintf( stdout, "    This confirms correct handling of each of the supported floating formats\n" );
	fprintf( stdout, "    for both read and write operations.\n\n" );
	fprintf( stdout, "    NOTE!  Floating point formats differ in the size of their mantissas.  These\n" );
	fprintf( stdout, "    tests will report errors when a host float is written, its mantissa\n" );
	fprintf( stdout, "    truncated by the write, then read back in and compared with the untruncated\n" );
	fprintf( stdout, "    mantissa of the original.  This cannot be helped and is not an error!\n\n" );
	fprintf( stdout, "    ALSO NOTE!  The Cray and IEEE formats have different ways of representing\n" );
	fprintf( stdout, "    what should be the same number.  This shows up in the last byte of the\n" );
	fprintf( stdout, "    mantissa.  Again, this is not an error and cannot be helped.\n" );
	verReadFloats( );
	verWriteFloats( );


	/*
	 *  Structure tests.
	 *	Verify that we can read in groups of items as a structure,
	 *	though they weren't written as one.
	 *
	 *	Verify that we can write out a structure and read back in
	 *	as individual items.
	 */
	fprintf( stdout, "\nTest #4:  Structure Read/Write Verification\n" );
	fprintf( stdout, "    A struct of items are written out, one at a time, then read back in as a\n" );
	fprintf( stdout, "    single structure.  The structure is then written out as a structure, then\n" );
	fprintf( stdout, "    read back in one item at a time.\n\n" );
	fprintf( stdout, "    This confirms that host structure padding is being handled properly.\n" );
	verReadStructs( );
	verWriteStructs( );

	fprintf( stdout, "\nDone\n" );
}





/*
 *  FUNCTION
 *	verIntegers	-  verify integer write / read
 *
 *  DESCRIPTION
 *	A data file is created and integers written to it that are...
 *		1.  The same size as they are represented by the host.
 *		2.  1 byte smaller than they are on the host.
 *		3.  1 byte larger than they are on the host.
 *	The data file is then closed, read back in, and checked.
 *
 *	During the writes of smaller size items truncation errors should occur.
 *	An error handler function is nominated to capture the errors and
 *	count them.  If we don't get the right number, an error message is
 *	output.
 *
 *	During the read back, if the value read back is not the same as that
 *	written (after truncation), then an error message is output.
 *
 *	Because the file type size is keyed to the host type size, files
 *	written by these routines are not portable between machines.
 *
 *  SAME SIZE WRITE AND READ
 *	The size of the item in host memory is the same as the size when in
 *	the file.  This size may differ from machine to machine.  For instance:
 *
 *					sizeof( )
 *			char	short	int	long	float	double
 *	SGI 4D series	1	2	4	4	4	8
 *	CRAY XMP	1	8	8	8	8	16
 *
 *	These reads and writes test the short path through the binary
 *	I/O routines.  This path recognizes the case where the size of a type
 *	is the same size as that to be written to or read from the file and
 *	defaults to a simple write() or read() call (if the host and file
 *	byte orders are the same).
 *
 *  SMALLER SIZE WRITE AND READ
 *	The size of the item in host memory is larger than the size when in
 *	the file.  For instance, a Cray writing a 32-bit int (host memory
 *	size = 64 bits).
 *
 *	These reads and writes test the smaller-size path through the binary
 *	I/O routines.  This path recognizes that truncation to the least-
 *	significant bits must happen on writes, and sign-extension must happen
 *	on reads.
 *
 *  BIGGER SIZE WRITE AND READ
 *	The size of the item in host memory is smaller than the size when in
 *	the file.  For instance, an IRIS writing a 64-bit int (IRIS int =
 *	32-bits).
 *
 *	These reads and writes test the bigger-size path through the binary
 *	I/O routines.  This path recognizes that zero padding in the most-
 *	significant bits must happen on writes, and truncation of the most-
 *	significant bits must happen on reads.
 */
static int				/* Returns nothing		*/
#ifdef __STDC__
verIntegers( int bo )
#else
verIntegers( bo )
	int bo;				/* Byte order to verify		*/
#endif
{
	/*
	 *  Select the byte order.
	 */
	if ( bo == BINMBF )
		fprintf( stdout, "\n    MBF byte order\n" );
	else
		fprintf( stdout, "\n    LBF byte order\n" );
	BinByteOrder( bo );



	/*
	 *  Create the file and write out data values.
	 */
	verCreate( );
	BinErrorHandler( verErrorHandler );
	verTruncErrors = 0;
	verShouldTruncErrors = 0;

	fprintf( stdout, "        Writing same size integers:\n" );
	verSameSizeWritechar( );
	verSameSizeWriteuchar( );
	verSameSizeWriteshort( );
	verSameSizeWriteushort( );
	verSameSizeWriteint( );
	verSameSizeWriteuint( );
	verSameSizeWritelong( );
	verSameSizeWriteulong( );

	fprintf( stdout, "        Writing smaller size integers:\n" );
	/* no char's because we can't write 1-byte smaller versions of	*/
	/* 1 byte quantities!						*/
	verSmallerWriteshort( );
	verSmallerWriteushort( );
	verSmallerWriteint( );
	verSmallerWriteuint( );
	verSmallerWritelong( );
	verSmallerWriteulong( );

	fprintf( stdout, "        Writing bigger size integers:\n" );
	verBiggerWritechar( );
	verBiggerWriteuchar( );
	verBiggerWriteshort( );
	verBiggerWriteushort( );
	verBiggerWriteint( );
	verBiggerWriteuint( );
	verBiggerWritelong( );
	verBiggerWriteulong( );

	verClose( );

	BinErrorHandler( BINDEFFUNC );

	/*
	 *  We'll get truncation errors for the smaller-size writes.  The
	 *  number of truncation errors we should get is computed by the
	 *  routines doing the writing as they are called.  If we get the
	 *  wrong number, we've got a problem.
	 */
	if ( verTruncErrors != verShouldTruncErrors )
		fprintf( stdout, "            Wrong number of integer truncations.  Want %d, got %d\n", verShouldTruncErrors, verTruncErrors );



	/*
	 *  Read the file back in and check it.
	 */
	verOpen( );

	fprintf( stdout, "        Reading same size integers:\n" );
	verSameSizeReadchar( );
	verSameSizeReaduchar( );
	verSameSizeReadshort( );
	verSameSizeReadushort( );
	verSameSizeReadint( );
	verSameSizeReaduint( );
	verSameSizeReadlong( );
	verSameSizeReadulong( );

	fprintf( stdout, "        Reading smaller size integers:\n" );
	verSmallerReadshort( );
	verSmallerReadushort( );
	verSmallerReadint( );
	verSmallerReaduint( );
	verSmallerReadlong( );
	verSmallerReadulong( );

	fprintf( stdout, "        Reading bigger size integers:\n" );
	verBiggerReadchar( );
	verBiggerReaduchar( );
	verBiggerReadshort( );
	verBiggerReadushort( );
	verBiggerReadint( );
	verBiggerReaduint( );
	verBiggerReadlong( );
	verBiggerReadulong( );

	verClose( );
	verDestroy( );

	fprintf( stdout, "    %d errors\n", verErrors );
	return ( 0 );
}





/*
 *  GLOBAL
 *	verData	-  Standard floating point test numbers
 *
 *  DESCRIPTION
 *	The verData array contains the standard floating point numbers
 *	written to the data file.
 */

#define NVERDATA	4	/* # of data items			*/
static float verData1[NVERDATA] =	/* Test data			*/
{
	0.0,			/* Tests zero/underflow case		*/
	1.0, 			/* Simple exponent, no mantissa		*/
	(float)3.14159,		/* Just a nice number with a mantissa	*/
	-12345.0,		/* Medium sized negative number		*/
};
static double verData2[NVERDATA] =	/* Test data			*/
{
	0.0,			/* Tests zero/underflow case		*/
	1.0, 			/* Simple exponent, no mantissa		*/
	3.14159,		/* Just a nice number with a mantissa	*/
	-12345.0,		/* Medium sized negative number		*/
};





/*
 *  FUNCTION
 *	verCheckFloat	-  check two lists of floating point values
 *	verCheckDouble	-  check two lists of double values
 *
 *  DESCRIPTION
 *	The two lists are compared element by element.  If the two values
 *	differ, they are printed out in floating point and hex formats.
 *
 *	In order to easily map a float or double to a list of bytes for
 *	hex output, we use a union trick.  This is portable.  Since both
 *	floats are supposedly in the host's floating point format, the
 *	order of hex bytes isn't important, as long as it is the same when
 *	printing out both the good and the erring value.
 */

//#include <pshpack4.h>

typedef union verEquivFloat
{
	float ver_f;		/* Incomming float			*/
	unsigned char ver_c[sizeof(float)];/* Outgoing bytes		*/
} verEquivFloat;

typedef union verEquivDouble
{
	double ver_d;		/* Incomming double			*/
	unsigned char ver_c[sizeof(double)];/* Outgoing bytes		*/
} verEquivDouble;

//#include <poppack.h>

static int			/* Returns # of errors found		*/
#ifdef __STDC__
verCheckFloat( float *pFloat1, int nFloat, float *pFloat2 )
#else
verCheckFloat( pFloat1, nFloat, pFloat2 )
	float *pFloat1;		/* Pointer to list of what was read	*/
	int    nFloat;		/* How many were read			*/
	float *pFloat2;		/* Pointer to list of what should have been*/
#endif
{
	int i, j;		/* Counters				*/
	int nerr = 0;		/* Number of errors			*/
	verEquivFloat equiv;	/* Floating point equivalence		*/


	for ( i = 0; i < nFloat; i++ )
	{
		if ( pFloat1[i] == pFloat2[i] )
			continue;

		if ( nerr == 0 )
			fprintf( stdout, "            %-26s  %-26s\n", "what was read",
				"what it should have been" );

		/* Print it out as floating point and hex byte list.	*/
		fprintf( stdout, "            %-26.24f  %-26.24f\n",
			pFloat1[i], pFloat2[i] );

		fprintf( stdout, "            0x" );
		equiv.ver_f = pFloat1[i];
		for ( j = 0; j < sizeof( float ); j++ )
			fprintf( stdout, "%02x ", equiv.ver_c[j] );
		for ( j = sizeof( float ) * 3; j < 26; j++ )
			fprintf( stdout, " " );
		fprintf( stdout, "0x" );
		equiv.ver_f = pFloat2[i];
		for ( j = 0; j < sizeof( float ); j++ )
			fprintf( stdout, "%02x ", equiv.ver_c[j] );
		fprintf( stdout, "\n" );

		nerr++;
	}

	return ( nerr );
}

static int			/* Returns # of errors found		*/
#ifdef __STDC__
verCheckDouble( double *pDouble1, int nDouble, double *pDouble2 )
#else
verCheckDouble( pDouble1, nDouble, pDouble2 )
	double *pDouble1;	/* Pointer to list of what was read	*/
	int    nDouble;		/* How many were read			*/
	double *pDouble2;	/* Pointer to list of what should have been*/
#endif
{
	int i, j;		/* Counters				*/
	int nerr = 0;		/* Number of errors			*/
	verEquivDouble equiv;	/* Double equivalence			*/


	for ( i = 0; i < nDouble; i++ )
	{
		if ( pDouble1[i] == pDouble2[i] )
			continue;

		if ( nerr == 0 )
			fprintf( stdout, "            %-26s  %-26s\n", "what was read",
				"what it should have been" );

		/* Print it out as double and hex byte list.		*/
		fprintf( stdout, "            %-26.24f  %-26.24f\n",
			pDouble1[i], pDouble2[i] );

		fprintf( stdout, "            0x" );
		equiv.ver_d = pDouble1[i];
		for ( j = 0; j < sizeof( double ); j++ )
			fprintf( stdout, "%02x ", equiv.ver_c[j] );
		for ( j = sizeof( double ) * 3; j < 26; j++ )
			fprintf( stdout, " " );
		fprintf( stdout, "0x" );
		equiv.ver_d = pDouble2[i];
		for ( j = 0; j < sizeof( double ); j++ )
			fprintf( stdout, "%02x ", equiv.ver_c[j] );
		fprintf( stdout, "\n" );

		nerr++;
	}

	return ( nerr );
}





/*
 *  FUNCTION
 *	verHostFloats	-  verify our understanding of the host's float format
 *
 *  DESCRIPTION
 *	Before getting into deeper floating point format verification, we first
 *	need to make sure the binary I/O package's idea of the host's floating
 *	point format is correct.  This includes byte order and the size and
 *	location of the exponent and mantissa in the format.
 *
 *	To verify this, we write the standard data to a data file using
 *	a write() system call, then read it back using the binary I/O package.
 *	The same data is then written using the binary I/O package, and
 *	read back in using a read() system call.  If all agrees, then the
 *	binary I/O package understands the host's floating point format.
 */
static int			/* Returns nothing			*/
#ifdef __STDC__
verHostFloats( void )
#else
verHostFloats( )
#endif
{
	float newdata1[NVERDATA];/* Read in ver data			*/
	double newdata2[NVERDATA];/* Read in ver data			*/

	fprintf( stdout, "\n    Raw write / package read\n" );

	/*
	 *  Create the ver file and write the data raw.
	 */
	fprintf( stdout, "        Writing floats:\n" );
	verErrors = 0;
	verCreate( );
	if ( _write( verFD, verData1, sizeof( verData1 ) ) == -1 )
	{
		perror( "write host float" );
		exit( 1 );
	}
	fprintf( stdout, "        Writing doubles:\n" );
	if ( _write( verFD, verData2, sizeof( verData2 ) ) == -1 )
	{
		perror( "write host double" );
		exit( 1 );
	}
	verClose( );


	/*
	 *  Reopen the file and read the data back using the I/O package.
	 */
	fprintf( stdout, "        Reading floats:\n" );
	verOpen( );
	BinByteOrder(   machineInfo->bin_byteOrder );
	BinFloatFormat( machineInfo->bin_floatFormat );
	if ( BinRead( verFD, newdata1, FLOAT, sizeof( float ), NVERDATA ) == -1 )
	{
		BinPError( "BinRead host float" );
		exit( 1 );
	}
	verErrors += verCheckFloat( newdata1, NVERDATA, verData1 );

	fprintf( stdout, "        Reading doubles:\n" );
	if ( BinRead( verFD, newdata2, DOUBLE, sizeof( double ), NVERDATA ) == -1 )
	{
		BinPError( "BinRead host double" );
		exit( 1 );
	}
	verErrors += verCheckDouble( newdata2, NVERDATA, verData2 );
	verClose( );
	verDestroy( );

	fprintf( stdout, "    %d errors\n", verErrors );

	fprintf( stdout, "\n    package write / raw read\n" );

	/*
	 *  Write using binary I/O.
	 */
	fprintf( stdout, "        Writing floats:\n" );
	verErrors = 0;
	verCreate( );
	if ( BinWrite( verFD, verData1, FLOAT, sizeof( float ), NVERDATA ) == -1 )
	{
		BinPError( "BinWrite host float" );
		exit( 1 );
	}
	fprintf( stdout, "        Writing doubles:\n" );
	if ( BinWrite( verFD, verData2, DOUBLE, sizeof( double ), NVERDATA ) == -1 )
	{
		BinPError( "BinWrite host double" );
		exit( 1 );
	}
	verClose( );


	/*
	 *  Reopen the file and read the data back using a system call.
	 */
	fprintf( stdout, "        Reading floats:\n" );
	verOpen( );
	if ( _read( verFD, newdata1, sizeof( verData1 ) ) == -1 )
	{
		perror( "read host float" );
		exit( 1 );
	}
	verErrors += verCheckFloat( newdata1, NVERDATA, verData1 );

	fprintf( stdout, "        Reading doubles:\n" );
	if ( _read( verFD, newdata2, sizeof( verData2 ) ) == -1 )
	{
		perror( "write host float" );
		exit( 1 );
	}
	verErrors += verCheckDouble( newdata2, NVERDATA, verData2 );
	verClose( );
	verDestroy( ) ;

	fprintf( stdout, "    %d errors\n", verErrors );
	return ( 0 );
}






/*
 *  FUNCTION
 *	verReadFloats	-  verify reading of floating point formats
 *	verReadCheck	-  do the actual check of a format
 *
 *  DESCRIPTION
 *	Read in the standard data from each of several standard
 *	data files.  Each file contains the data in a particular
 *	supported floating point format.
 */
static int				/* Returns nothing		*/
#ifdef __STDC__
verReadFloats( void )
#else
verReadFloats( )
#endif
{
	verReadCheck( "IEEE_MBF",    BINIEEE,    BINMBF, 4, 8 );
	verReadCheck( "IEEE_LBF",    BINIEEE,    BINLBF, 4, 8 );
	verReadCheck( "VAX_LBF",     BINVAX,     BINLBF, 4, 8 );
	verReadCheck( "CRAYMP_MBF",  BINCRAYMP,  BINMBF, 8, 8 );
	return ( 0 );
}

static int				/* Returns nothing		*/
#ifdef __STDC__
verReadCheck( char *filename, int format, int bo, int singlesize, int doublesize )
#else
verReadCheck( filename, format, bo, singlesize, doublesize )
	char *filename;		/* Data file name			*/
	int format;		/* Float format to use			*/
	int bo;			/* Byte order to use			*/
	int singlesize;		/* Size of a single			*/
	int doublesize;		/* Size of a double			*/
#endif
{
	float newdata1[NVERDATA];/* Read in ver data			*/
	double newdata2[NVERDATA];/* Read in ver data			*/


	fprintf( stdout, "\n    read known good %s test file\n", filename );

	/*
	 *  Open the file and set up the binary I/O package.
	 */
	if ( (verFD = _open( filename, _O_RDONLY )) == -1 )
	{
		perror( filename );
		fprintf( stdout, "Skipping format check\n" );
		return ( 0 );
	}
	BinByteOrder(   bo );
	BinFloatFormat( format );


	/*
	 *  Read and check the data.
	 */
	fprintf( stdout, "        Reading floats:\n" );
	verErrors = 0;
	if ( BinRead( verFD, newdata1, FLOAT, singlesize, NVERDATA ) == -1 )
	{
		BinPError( "BinRead of floats" );
		exit( 1 );
	}
	verErrors += verCheckFloat( newdata1, NVERDATA, verData1 );

	fprintf( stdout, "        Reading doubles:\n" );
	if ( BinRead( verFD, newdata2, DOUBLE, doublesize, NVERDATA ) == -1 )
	{
		BinPError( "BinRead of doubles" );
		exit( 1 );
	}
	verErrors += verCheckDouble( newdata2, NVERDATA, verData2 );
	fprintf( stdout, "    %d errors\n", verErrors );
	_close( verFD );
	return ( 0 );
}





/*
 *  FUNCTION
 *	verWriteFloats	-  verify pkg write of floating point formats
 *	verWriteCheck	-  do the actual check of a format
 *
 *  DESCRIPTION
 *	Each supported floating point format is written out and read back in.
 *	verReadFloats() has already confirmed (or not) that we are reading
 *	properly.  If we read back what we have written without errors,
 *	then all is good.
 */
static int				/* Returns nothing		*/
#ifdef __STDC__
verWriteFloats( void )
#else
verWriteFloats( )
#endif
{
	verWriteCheck( "IEEE_MBF",    BINIEEE,    BINMBF, 4, 8 );
	verWriteCheck( "IEEE_LBF",    BINIEEE,    BINLBF, 4, 8 );
	verWriteCheck( "VAX_LBF",     BINVAX,     BINLBF, 4, 8 );
	verWriteCheck( "CRAYMP_MBF",  BINCRAYMP,  BINMBF, 8, 8 );
	return ( 0 );
}

static int				/* Returns nothing		*/
#ifdef __STDC__
verWriteCheck( char *name, int format, int bo, int singlesize, int doublesize )
#else
verWriteCheck( name, format, bo, singlesize, doublesize )
	char *name;		/* Test name				*/
	int format;		/* Float format to use			*/
	int bo;			/* Byte order to use			*/
	int singlesize;		/* Size of a single			*/
	int doublesize;		/* Size of a double			*/
#endif
{
	float newdata1[NVERDATA];/* Read in ver data			*/
	double newdata2[NVERDATA];/* Read in ver data			*/


	fprintf( stdout, "\n    write %s and read back in\n", name );

	/*
	 *  Set up the binary I/O package.
	 */
	BinByteOrder(   bo );
	BinFloatFormat( format );


	/*
	 *  Write out the data.
	 */
	verCreate( );
	fprintf( stdout, "        Writing floats:\n" );
	if ( BinWrite( verFD, verData1, FLOAT, singlesize, NVERDATA ) == -1 )
	{
		BinPError( "BinWrite of floats" );
		exit( 1 );
	}
	fprintf( stdout, "        Writing doubles:\n" );
	if ( BinWrite( verFD, verData2, DOUBLE, doublesize, NVERDATA ) == -1)
	{
		BinPError( "BinWrite of doubles" );
		exit( 1 );
	}
	verClose( );


	/*
	 *  Read and check the data.
	 */
	verOpen( );
	fprintf( stdout, "        Reading floats:\n" );
	verErrors = 0;
	if ( BinRead( verFD, newdata1, FLOAT, singlesize, NVERDATA ) == -1 )
	{
		BinPError( "BinRead of floats" );
		exit( 1 );
	}
	verErrors += verCheckFloat( newdata1, NVERDATA, verData1 );

	fprintf( stdout, "        Reading doubles:\n" );
	if ( BinRead( verFD, newdata2, DOUBLE, doublesize, NVERDATA ) == -1 )
	{
		BinPError( "BinRead of doubles" );
		exit( 1 );
	}
	verErrors += verCheckDouble( newdata2, NVERDATA, verData2 );
	verClose( );
	verDestroy( );

	fprintf( stdout, "    %d errors\n", verErrors );
	return ( 0 );
}



//#include <pshpack4.h>

/*
 *  STRUCT & TYPEDEF
 *	verStruct	-  Structure data description
 *
 *  DESCRIPTION
 *	verStruct describes a struct that, as a unit, is written to and
 *	read from the test data file.
 */
typedef struct verStruct
{
	char	ver_c1;
	short	ver_s1[3];
	int	ver_i1[2];
	char	ver_c2[2];
	float	ver_f1;
	unsigned short	ver_s2;
	double	ver_d1;
} verStruct;


//#include <poppack.h>


/*
 *  GLOBAL
 *	verStructData	-  Structure data
 *	verStructFields	-  Structure description
 *
 *  DESCRIPTION
 *	verStruct is initialized to a set of test data used in the verification
 *	of structure writes and reads.
 *
 *	verFields is a description of the structure as required by the
 *	binary I/O package read and write struct calls.
 */

verStruct verStructData =
{
	'a',
	 1, -2,  3,
	-4,  5,
	'b', 'c',
	(float)1.2345,
	6,
	2.3456,
};

BinField verStructFields[] =
{
	CHAR,	sizeof( char ),		1,
	SHORT,	sizeof( short ),	3,
	INT,	sizeof( int ),		2,
	CHAR,	sizeof( char ),		2,
	FLOAT,	sizeof( float ),	1,
	USHORT,	sizeof( unsigned short ),	1,
	DOUBLE,	sizeof( double ),	1,
	0,	0,			0,
};





/*
 *  FUNCTION
 *	verReadStructs	-  verify structure read
 *
 *  DESCRIPTION
 *	A list of items are written out to a data file, then read back in
 *	as a struct and their values checked.  This confirms that structure
 *	padding on the host is being handled properly on reads.
 */
static int				/* Returns nothing		*/
#ifdef __STDC__
verReadStructs( void )
#else
verReadStructs( )
#endif
{
	verStruct data;			/* Read in structure data	*/

	fprintf( stdout, "\n    item write / struct read\n" );

	/*
	 *  Set up the binary I/O package and create the file.
	 */
	BinByteOrder(   machineInfo->bin_byteOrder );
	BinFloatFormat( machineInfo->bin_floatFormat );


	/*
	 *  Write out each structure item individually.
	 */
	verCreate( );
	fprintf( stdout, "        Writing items:\n" );
	if ( BinWrite( verFD, &verStructData.ver_c1, CHAR, sizeof( char ), 1 ) == -1 )
	{
		BinPError( "BinWrite of char" );
		exit( 1 );
	}
	if ( BinWrite( verFD, verStructData.ver_s1, SHORT, sizeof( short ), 3 ) == -1 )
	{
		BinPError( "BinWrite of short" );
		exit( 1 );
	}
	if ( BinWrite( verFD, verStructData.ver_i1, INT, sizeof( int ), 2 ) == -1 )
	{
		BinPError( "BinWrite of int" );
		exit( 1 );
	}
	if ( BinWrite( verFD, verStructData.ver_c2, CHAR, sizeof( char ), 2 ) == -1 )
	{
		BinPError( "BinWrite of char" );
		exit( 1 );
	}
	if ( BinWrite( verFD, &verStructData.ver_f1, FLOAT, sizeof( float ), 1 ) == -1 )
	{
		BinPError( "BinWrite of float" );
		exit( 1 );
	}
	if ( BinWrite( verFD, &verStructData.ver_s2, USHORT, sizeof( unsigned short ), 1 ) == -1 )
	{
		BinPError( "BinWrite of ushort" );
		exit( 1 );
	}
	if ( BinWrite( verFD, &verStructData.ver_d1, DOUBLE, sizeof( double ), 1 ) == -1 )
	{
		BinPError( "BinWrite of double" );
		exit( 1 );
	}

	verClose( );


	/*
	 *  Read it back in as a structure and check it.
	 */
	fprintf( stdout, "        Reading struct:\n" );
	verErrors = 0;
	verOpen( );
	if ( BinReadStruct( verFD, &data, verStructFields ) == -1 )
	{
		BinPError( "BinReadStruct" );
		exit( 1 );
	}

	if ( data.ver_c1 != verStructData.ver_c1 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %1c           %1c\n", data.ver_c1,
			verStructData.ver_c1 );
		verErrors++;
	}
	if ( data.ver_s1[0] != verStructData.ver_s1[0] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d      %5d\n", data.ver_s1[0],
			verStructData.ver_s1[0] );
		verErrors++;
	}
	if ( data.ver_s1[1] != verStructData.ver_s1[1] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d      %5d\n", data.ver_s1[1],
			verStructData.ver_s1[1] );
		verErrors++;
	}
	if ( data.ver_s1[2] != verStructData.ver_s1[2] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d      %5d\n", data.ver_s1[2],
			verStructData.ver_s1[2] );
		verErrors++;
	}
	if ( data.ver_i1[0] != verStructData.ver_i1[0] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10d  %10d\n", data.ver_i1[0],
			verStructData.ver_i1[0] );
		verErrors++;
	}
	if ( data.ver_i1[1] != verStructData.ver_i1[1] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10d  %10d\n", data.ver_i1[1],
			verStructData.ver_i1[1] );
		verErrors++;
	}
	if ( data.ver_c2[0] != verStructData.ver_c2[0] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %1c           %1c\n", data.ver_c2[0],
			verStructData.ver_c2[0] );
		verErrors++;
	}
	if ( data.ver_c2[1] != verStructData.ver_c2[1] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %1c           %1c\n", data.ver_c2[1],
			verStructData.ver_c2[1] );
		verErrors++;
	}
	if ( data.ver_f1 != verStructData.ver_f1 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10.8f  %10.8f\n", data.ver_f1,
			verStructData.ver_f1 );
		verErrors++;
	}
	if ( data.ver_s2 != verStructData.ver_s2 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d       %5d\n", data.ver_s2,
			verStructData.ver_s2 );
		verErrors++;
	}
	if ( data.ver_d1 != verStructData.ver_d1 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10.8f  %10.8f\n", data.ver_d1,
			verStructData.ver_d1 );
		verErrors++;
	}

	verClose( );
	verDestroy( );

	fprintf( stdout, "    %d errors\n", verErrors );
	return ( 0 );
}





/*
 *  FUNCTION
 *	verWriteStructs	-  verify structure write
 *
 *  DESCRIPTION
 *	A structure is written to a data file as a whole, then read back
 *	in item-by-item and the values checked.  This confirms that structure
 *	padding on the host is being handled properly on writes.
 */
static int				/* Returns nothing		*/
#ifdef __STDC__
verWriteStructs( void )
#else
verWriteStructs( )
#endif
{
	verStruct data;			/* Read in structure data	*/

	fprintf( stdout, "\n    struct write / item read\n" );

	/*
	 *  Set up the binary I/O package and create the file.
	 */
	BinByteOrder(   machineInfo->bin_byteOrder );
	BinFloatFormat( machineInfo->bin_floatFormat );


	/*
	 *  Write out structure as a whole.
	 */
	verCreate( );
	fprintf( stdout, "        Writing struct:\n" );
	if ( BinWriteStruct( verFD, &verStructData, verStructFields ) == -1 )
	{
		BinPError( "BinWriteStruct" );
		exit( 1 );
	}
	verClose( );


	/*
	 *  Read structure in as individual items.
	 */
	fprintf( stdout, "        Reading items:\n" );
	verErrors = 0;
	verOpen( );
	if ( BinRead( verFD, &data.ver_c1, CHAR, sizeof( char ), 1 ) == -1 )
	{
		BinPError( "BinRead of char" );
		exit( 1 );
	}
	if ( BinRead( verFD, data.ver_s1, SHORT, sizeof( short ), 3 ) == -1 )
	{
		BinPError( "BinRead of short" );
		exit( 1 );
	}
	if ( BinRead( verFD, data.ver_i1, INT, sizeof( int ), 2 ) == -1 )
	{
		BinPError( "BinRead of int" );
		exit( 1 );
	}
	if ( BinRead( verFD, data.ver_c2, CHAR, sizeof( char ), 2 ) == -1 )
	{
		BinPError( "BinRead of char" );
		exit( 1 );
	}
	if ( BinRead( verFD, &data.ver_f1, FLOAT, sizeof( float ), 1 ) == -1 )
	{
		BinPError( "BinRead of float" );
		exit( 1 );
	}
	if ( BinRead( verFD, &data.ver_s2, USHORT, sizeof( unsigned short ), 1 ) == -1 )
	{
		BinPError( "BinRead of ushort" );
		exit( 1 );
	}
	if ( BinRead( verFD, &data.ver_d1, DOUBLE, sizeof( double ), 1 ) == -1 )
	{
		BinPError( "BinRead of double" );
		exit( 1 );
	}
	verClose( );
	verDestroy( );

	if ( data.ver_c1 != verStructData.ver_c1 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %1c           %1c\n", data.ver_c1,
			verStructData.ver_c1 );
		verErrors++;
	}
	if ( data.ver_s1[0] != verStructData.ver_s1[0] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d      %5d\n", data.ver_s1[0],
			verStructData.ver_s1[0] );
		verErrors++;
	}
	if ( data.ver_s1[1] != verStructData.ver_s1[1] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d      %5d\n", data.ver_s1[1],
			verStructData.ver_s1[1] );
		verErrors++;
	}
	if ( data.ver_s1[2] != verStructData.ver_s1[2] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d      %5d\n", data.ver_s1[2],
			verStructData.ver_s1[2] );
		verErrors++;
	}
	if ( data.ver_i1[0] != verStructData.ver_i1[0] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10d  %10d\n", data.ver_i1[0],
			verStructData.ver_i1[0] );
		verErrors++;
	}
	if ( data.ver_i1[1] != verStructData.ver_i1[1] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10d  %10d\n", data.ver_i1[1],
			verStructData.ver_i1[1] );
		verErrors++;
	}
	if ( data.ver_c2[0] != verStructData.ver_c2[0] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %1c           %1c\n", data.ver_c2[0],
			verStructData.ver_c2[0] );
		verErrors++;
	}
	if ( data.ver_c2[1] != verStructData.ver_c2[1] )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %1c           %1c\n", data.ver_c2[1],
			verStructData.ver_c2[1] );
		verErrors++;
	}
	if ( data.ver_f1 != verStructData.ver_f1 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10.8f  %10.8f\n", data.ver_f1,
			verStructData.ver_f1 );
		verErrors++;
	}
	if ( data.ver_s2 != verStructData.ver_s2 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %5d       %5d\n", data.ver_s2,
			verStructData.ver_s2 );
		verErrors++;
	}
	if ( data.ver_d1 != verStructData.ver_d1 )
	{
		if ( verErrors == 0 )
			fprintf( stdout, "    read        should have been\n" );
		fprintf( stdout, "    %10.8f  %10.8f\n", data.ver_d1,
			verStructData.ver_d1 );
		verErrors++;
	}

	fprintf( stdout, "    %d errors\n", verErrors );
	return ( 0 );
}
