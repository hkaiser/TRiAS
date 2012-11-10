/**
 **     $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/binprint.c,v 1.4 1995/06/29 00:17:39 bduggan Exp $
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

#define HEADER  "	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/binprint.c,v 1.4 1995/06/29 00:17:39 bduggan Exp $"

/**
 **  FILE
 **     binprint.c      -  Display info used by Binary I/O package
 **
 **  PROJECT
 **     libsdsc         -  SDSC Utility Library
 **
 **  DESCRIPTION
 **	This file contains source for a program to display information
 **	used by the binary package.
 **
 **  PUBLIC CONTENTS
 **                     d =defined constant
 **                     f =function
 **                     m =defined macro
 **                     t =typedef/struct/union
 **                     v =variable
 **                     ? =other
 **
 **  HISTORY
 **	$Log: binprint.c,v $
 **	Revision 1.4  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.3  1994/10/03  16:27:25  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Removed all use of register keyword.
 **	Updated print columns.
 **	Updated copyright message.
 **
 **	Revision 1.2  92/09/02  14:25:15  vle
 **	Added comment block at top of file.
 **	
 **/

#include "sdsccopyright.h"
#include <stdio.h>
#include "sdsc.h"

main( )
{
	int i;				/* Counter			*/
	BinMachineInfo *info;		/* Machine information		*/

	info = BinQMachine( );

	printf( "Machine Characteristics:\n" );
	printf( "  Vendor       = %s\n", info->bin_vendorName );
	printf( "  Machine      = %s\n", info->bin_machineName );
	printf( "  CPU          = %s\n", info->bin_cpuName );
	printf( "  OS           = %s\n", info->bin_osName );

	printf( "  byte order   = %s\n", info->bin_byteOrderName );
	printf( "  float format = %s\n", info->bin_floatFormatName );

	printf( "Type Characteristics:\n" );
	printf( "  Type            Signed?  Size  Res  Pad  Mask\n" );
	for ( i = 0; i <= BINMAXTYPE; i++ )
	{
		printf( "  %-15s %-8s %4d %4d %4d  0x%08x\n",
			info->bin_typeName[i],
			(info->bin_typeSigned[i])?"signed":"unsigned",
			info->bin_typeSize[i],
			info->bin_typeRes[i],
			info->bin_typePad[i],
			info->bin_typePadMask[i] );
	}
}
