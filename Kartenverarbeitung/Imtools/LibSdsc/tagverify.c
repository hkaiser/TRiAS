/**
 **	$Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/tagverify.c,v 1.9 1995/06/30 21:54:16 bduggan Exp $
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

#define HEADER	"    $Header: /sdsc/dev/vis/misc/libsdsc/v3.0/libsdsc/src/RCS/tagverify.c,v 1.9 1995/06/30 21:54:16 bduggan Exp $"

/**
 **  FILE
 **	tagverify	-  verify tag table management code
 **
 **  PROJECT
 **	libsdsc		-  SDSC standard function library
 **
 **  DESCRIPTION
 **	This program does a variety of self tests to confirm the correct
 **	functioning of the tag table management code.
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
 **	VER*		d  version numbers
 **	tagCommand	v  Command info for the arg parsing package
 **	tagInfo		t  test data information for the tag table
 **	tagData1	v  test data for the tag table
 **	tagData2	v  test data for the tag table
 **
 **  HISTORY
 **	$Log: tagverify.c,v $
 **	Revision 1.9  1995/06/30  21:54:16  bduggan
 **	removed prototype for strcmp
 **	added void for main
 **
 **	Revision 1.8  1995/06/29  00:17:39  bduggan
 **	updated copyright
 **
 **	Revision 1.7  1994/10/03  16:25:36  nadeau
 **	Updated to ANSI C and C++ compatibility.
 **	Removed all use of register keyword.
 **	Minimized use of custom SDSC types (e.g., uchar vs. unsigned char)
 **	Added forward declarations.
 **	Updated comments.
 **	Updated copyright message.
 **
 **	Revision 1.6  92/09/02  14:26:51  vle
 **	Updated copyright notice.
 **	
 **	Revision 1.5  92/09/02  13:38:33  nadeau
 **	Added extern declarations.
 **	
 **	Revision 1.4  91/10/03  13:07:17  nadeau
 **	Updated to new ArgCommand struct.
 **	
 **	Revision 1.3  91/01/09  16:43:55  nadeau
 **	Removed leading 'im' and 'Im' from calls et al.
 **	
 **	Revision 1.2  90/05/11  09:59:50  nadeau
 **	Major revision.  Changed from 'tag list' to 'tag table' calls after
 **	changes to imtag.c.  Removed out-of-date tests and added new ones.
 **	
 **	Revision 1.1  90/03/06  17:32:41  nadeau
 **	Initial revision
 **	
 **/

#include "sdsccopyright.h"
#include <stdio.h>
#include <string.h>
#include "sdsc.h"





/*
 *  CONSTANTS
 *	VER*		-  version numbers
 *
 *  DESCRIPTION
 *	These are the major, minor, and subminor version numbers for this
 *	test program.
 */
#define VERMAJOR	3
#define VERMINOR	0
#define VERSUBMINOR	0





/*
 *  VARIABLE
 *	tagCommand	-  Command info for the arg parsing package
 *
 *  DESCRIPTION
 *	The tagCommand struct contains information for the argument parsing
 *	package to print on -help and argument errors.
 */

ArgCommand tagCommand =
{
	"tagverify", VERMAJOR, VERMINOR, VERSUBMINOR,
	"%command verifies the correct functioning of the tag table management code of\n\
the SDSC utility library.",
	"There are no custom arguments to %command.  All tests are done automatically\n\
and errors reported to stderr.",
	NULL, NULL,
	ARGFNONE,
	NULL,
	NULL,
"SDSC tag table package Verification Tools",
"Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC),\n\
a division of General Atomics, San Diego, California, USA",
	NULL,
	NULL,
};



/*
 *  MACROS
 *	LINE		-  draw a line across the screen
 */

#define LINE								\
	fprintf( stderr, "-------------------------------------------------------------------------------\n" )

#define ERR( stmnt, errvalue )						\
	if ( (stmnt) == (errvalue) )					\
	{								\
		TagPError( "  " );					\
		numErrors++;						\
	}


/*
 *  TYPEDEF & STRUCTURE
 *	tagInfo		-  test data information for the tag table
 *
 *  DESCRIPTION
 *	Each tagInfo struct gives the name of a tag, and an integer value
 *	to be associated with it in the tag table.
 */

typedef struct tagInfo
{
	char *info_tag;			/* Tag name			*/
	int   info_value;		/* Tag value			*/
} tagInfo;




/*
 *  VARIABLES
 *	tagData1		-  test data for the tag table
 *	tagData2		-  test data for the tag table
 *
 *  DESCRIPTION
 *	The tagData* arrays are sets of tag-value pairs to be used in
 *	building up tagTables to test the ImTag* routines of the image library.
 */

tagInfo tagData1[ ] =
{
	{ "The Meaning of Life",	42 },
	{ "The Number of the Beast",	666 },
	{ "Miracle on xx-th Street",	34 },
	{ "Thing 1 and Thing xx",	2 },
	{ NULL,				0 },
};
#define TAGDATA1LENGTH	4

tagInfo tagData2[ ] =
{
	{ "xx skee-doo",		23 },
	{ "Lottery winning chances",	0 },
	{ "Holy Hand-grenade count",	3 },
	{ NULL,				0 },
};
#define TAGDATA2LENGTH	3





int numErrors = 0;			/* Number of errors		*/





/*
 *  FUNCTION DECLARATIONS
 */
#ifdef __STDC__

static int      tagCheckNEntries( TagTable *tagTable, int shouldBe );
static int      tagCheckEntries( TagTable *tagTable, tagInfo *tagData,
			int startEntry, int endEntry, int stepInfo );
#else

static int      tagCheckNEntries( );
static int      tagCheckEntries( );
#endif





/*
 *  FUNCTION
 *	main	-  main program
 *
 *  DESCRIPTION
 *	Each of the ImTag* routines are tested.  Most paths through the
 *	code are verified.  Error messages are written to stderr and
 *	an error count maintained and printed at the end.
 */

void
#ifdef __STDC__
main( int argc, char *argv[] )
#else
main( argc, argv )
	int        argc;		/* Argument count		*/
	char      *argv[];		/* Argument vector		*/
#endif
{
	TagTable  *tagTable;		/* test tag table		*/
	TagEntry  *tagEntry;		/* working tag entry		*/
	tagInfo   *pInfo;		/* Info table pointer		*/
	int        i, n;		/* Counters			*/
	char      *tag;			/* Tag				*/
	int        value;		/* Value			*/
	int	   nthOccur;		/* Occurrence #			*/
	int	   nthEntry;		/* Entry #			*/
	int	   valueType;		/* Type of value		*/
	double     dvalue;		/* Double value			*/
	char       cvalue;		/* Char value			*/


	/*
	 *  Handle arguments.
	 */
	ArgParse( argc, argv, &tagCommand, 0, NULL, 0, NULL );


	/*
	 *  Allocate a tag table.
	 */
	fprintf( stderr, "Allocating tag table:\n" );
	LINE;
	ERR( tagTable = TagTableAlloc( ), TAGTABLENULL );


	/*
	 *  Append test data set 1 to the empty tag table, check the number
	 *  of entries afterwards (should be equal to the # of items we
	 *  appended), and check and print out each of the entries, watching
	 *  for bad tags or values
	 */
	fprintf( stderr, "\nAppending test data set 1 and checking:\n" );
	LINE;
	for ( pInfo = tagData1; pInfo->info_tag; pInfo++ )
	{
		ERR( TagTableAppend( tagTable,
			TagEntryAlloc( pInfo->info_tag, INT,
			&pInfo->info_value )), -1 );
	}
	tagCheckNEntries( tagTable, TAGDATA1LENGTH );
	tagCheckEntries(  tagTable, tagData1, 0, TAGDATA1LENGTH-1, 1 );


	/*
	 *  Append test data set 1 again.  This should leave every tag
	 *  occuring twice.  Confirm this.
	 */
	fprintf( stderr, "\nAppending test data set 1 again and checking occurrence counts for tags:\n" );
	LINE;
	for ( pInfo = tagData1; pInfo->info_tag; pInfo++ )
	{
		ERR( TagTableAppend( tagTable,
			TagEntryAlloc( pInfo->info_tag, INT,
			&pInfo->info_value )), -1 );
	}
	tagCheckNEntries( tagTable, TAGDATA1LENGTH*2 );
	tagCheckEntries(  tagTable, tagData1, 0, TAGDATA1LENGTH-1, 1 );
	tagCheckEntries(  tagTable, tagData1, TAGDATA1LENGTH,
		TAGDATA1LENGTH*2-1, 1 );
	fprintf( stderr, "\n  Tag:                     Occur:\n" );
	for ( i = 0, pInfo = tagData1; pInfo->info_tag; i++, pInfo++ )
	{
		ERR( n = TagTableQNEntry( tagTable, pInfo->info_tag ), -1 );

		if ( n != 2 )
		{
			fprintf( stderr, "  %-23s  %d  Wrong!  Should be 2!\n",
				pInfo->info_tag, n );
			numErrors++;
			continue;
		}
		fprintf( stderr, "  %-23s  %2d\n", pInfo->info_tag, n );

		/* 1st occurrence					*/
		ERR( tagEntry = TagTableQDirect( tagTable, pInfo->info_tag, 0 ), TAGENTRYNULL );

		ERR( tag      = TagEntryQTag(      tagEntry         ), NULL );
		ERR(            TagEntryQValue(    tagEntry, &value ), -1 );
		ERR( nthOccur = TagEntryQNthOccur( tagEntry         ), -1 );
		ERR( nthEntry = TagEntryQNthEntry( tagEntry         ), -1 );
		ERR( valueType= TagEntryQValueType(tagEntry         ), -1 );

		fprintf( stderr, "          %-23s  %2d     %3d     %2d      %2d\n",
			tag, valueType, value, nthOccur, nthEntry );
		if ( strcmp( tag, pInfo->info_tag ) != 0 )
		{
			fprintf( stderr, "          Wrong tag!.   Should be '%s'!\n",
				pInfo->info_tag );
			numErrors++;
		}
		if ( valueType != INT )
		{
			fprintf( stderr, "          Wrong type!   Should be %d!\n",
				INT );
			numErrors++;
		}
		if ( value != pInfo->info_value )
		{
			fprintf( stderr, "          Wrong value!  Should be %d!\n",
				pInfo->info_value );
			numErrors++;
		}
		if ( nthOccur != 0 )
		{
			fprintf( stderr, "          Wrong occ#!   Should be 0!\n" );
			numErrors++;
		}

		/* 2nd occurrence.					*/
		ERR( tagEntry = TagTableQDirect( tagTable, pInfo->info_tag, 1 ), TAGENTRYNULL );

		ERR( tag      = TagEntryQTag(      tagEntry         ), NULL );
		ERR(            TagEntryQValue(    tagEntry, &value ), -1 );
		ERR( nthOccur = TagEntryQNthOccur( tagEntry         ), -1 );
		ERR( nthEntry = TagEntryQNthEntry( tagEntry         ), -1 );
		ERR( valueType= TagEntryQValueType(tagEntry         ), -1 );

		fprintf( stderr, "          %-23s  %2d     %3d     %2d      %2d\n",
			tag, valueType, value, nthOccur, nthEntry );
		if ( strcmp( tag, pInfo->info_tag ) != 0 )
		{
			fprintf( stderr, "          Wrong tag!.   Should be '%s'!\n",
				pInfo->info_tag );
			numErrors++;
		}
		if ( valueType != INT )
		{
			fprintf( stderr, "          Wrong type!   Should be %d!\n",
				INT );
			numErrors++;
		}
		if ( value != pInfo->info_value )
		{
			fprintf( stderr, "          Wrong value!  Should be %d!\n",
				pInfo->info_value );
			numErrors++;
		}
		if ( nthOccur != 1 )
		{
			fprintf( stderr, "          Wrong occ#!   Should be 1!\n" );
			numErrors++;
		}
	}


	/*
	 *  Insert set data set 2 right after the first batch of entries from
	 *  test data set 1.  Since we'll use the same insert point for all
	 *  of the inserts, test data set 2 will get inserted in reverse order.
	 */
	fprintf( stderr, "\nInserting test data set 2 after entry %d and checking:\n",
		TAGDATA1LENGTH-1 );
	LINE;
	for ( pInfo = tagData2; pInfo->info_tag; pInfo++ )
		ERR( TagTableInsert( tagTable, TAGDATA1LENGTH-1,
			TagEntryAlloc( pInfo->info_tag, INT,
			&pInfo->info_value )), -1 );
	tagCheckNEntries( tagTable, TAGDATA1LENGTH * 2 + TAGDATA2LENGTH );
	tagCheckEntries(  tagTable, tagData1, 0, TAGDATA1LENGTH-1, 1 );
	tagCheckEntries(  tagTable, tagData2+TAGDATA2LENGTH-1,
		TAGDATA1LENGTH, TAGDATA1LENGTH+TAGDATA2LENGTH-1, -1 );
	tagCheckEntries(  tagTable, tagData1, TAGDATA1LENGTH+TAGDATA2LENGTH,
		TAGDATA1LENGTH*2+TAGDATA2LENGTH-1, 1 );


	/*
	 *  Delete the 2nd occurrence of test data set 1 (all at the end
	 *  of the tag table).  Because things will scoot up on each delete,
	 *  the delete entry number can stay the same for each call.
	 */
	fprintf( stderr, "\nDeleting test data set 1 after entry %d and checking:\n",
		TAGDATA1LENGTH + TAGDATA2LENGTH );
	LINE;
	for ( i = 0; i < TAGDATA1LENGTH; i++ )
		ERR( TagTableDelete( tagTable, TAGDATA1LENGTH + TAGDATA2LENGTH ), -1 );
	tagCheckNEntries( tagTable, TAGDATA1LENGTH + TAGDATA2LENGTH );
	tagCheckEntries(  tagTable, tagData1, 0, TAGDATA1LENGTH-1, 1 );
	tagCheckEntries(  tagTable, tagData2+TAGDATA2LENGTH-1, TAGDATA1LENGTH,
		TAGDATA1LENGTH+TAGDATA2LENGTH-1, -1 );


	/*
	 *  Delete the 1st occurrence of test data set 1 items (all at the
	 *  beginning of the table).
	 */
	fprintf( stderr, "\nDeleting test data set 1 before entry %d and checking:\n",
		TAGDATA1LENGTH );
	LINE;
	for ( i = 0; i < TAGDATA1LENGTH; i++ )
		ERR( TagTableDelete( tagTable, 0 ), -1 );
	tagCheckNEntries( tagTable, TAGDATA2LENGTH );
	tagCheckEntries(  tagTable, tagData2+TAGDATA2LENGTH-1, 0,
		TAGDATA2LENGTH-1, -1 );



	/*
	 *  Deallocate the tables.
	 */
	fprintf( stderr, "\nDeallocating table:\n" );
	LINE;
	TagTableFree( tagTable );


	/*
	 *  Allocate a new tag table and add in some strangely-sized values.
	 */
	fprintf( stderr, "\nAllocating new table and filling with odd-sized values:\n" );
	LINE;
	tagTable = TagTableAlloc( );
	fprintf( stderr, "  Entry:  Tag:                     Type:  Value:  Occur:\n" );


	cvalue = 'A';
	ERR( TagTableAppend( tagTable,
		TagEntryAlloc( "char value", CHAR, &cvalue )), -1 );
	ERR( tagEntry = TagTableQDirect( tagTable, "char value", 0 ), TAGENTRYNULL );

	ERR( tag      = TagEntryQTag(      tagEntry         ), NULL );
	ERR( nthOccur = TagEntryQNthOccur( tagEntry         ), -1 );
	ERR( nthEntry = TagEntryQNthEntry( tagEntry         ), -1 );
	ERR( valueType= TagEntryQValueType(tagEntry         ), -1 );
	ERR(            TagEntryQValue(    tagEntry, &cvalue ), -1 );

	fprintf( stderr, "  %2d      %-23s  %2d      %1c      %2d\n",
		nthEntry, tag, valueType, cvalue, nthOccur );
	if ( valueType != CHAR )
	{
		fprintf( stderr, "          Wrong type!   Should be %d!\n", CHAR );
		numErrors++;
	}
	if ( cvalue != 'A' )
	{
		fprintf( stderr, "          Wrong value!  Should be 'A'!\n" );
		numErrors++;
	}

	dvalue = 3.14;
	ERR( TagTableAppend( tagTable,
		TagEntryAlloc( "double value", DOUBLE, &dvalue )), -1 );
	ERR( tagEntry = TagTableQDirect( tagTable, "double value", 0 ), TAGENTRYNULL );
	ERR( tag      = TagEntryQTag(      tagEntry         ), NULL );
	ERR( nthOccur = TagEntryQNthOccur( tagEntry         ), -1 );
	ERR( nthEntry = TagEntryQNthEntry( tagEntry         ), -1 );
	ERR( valueType= TagEntryQValueType(tagEntry         ), -1 );
	ERR(            TagEntryQValue(    tagEntry, &dvalue ), -1 );

	fprintf( stderr, "  %2d      %-23s  %2d      %1.2f    %2d\n",
		nthEntry, tag, valueType, dvalue, nthOccur );
	if ( valueType != DOUBLE )
	{
		fprintf( stderr, "          Wrong type!   Should be %d!\n", DOUBLE );
		numErrors++;
	}
	if ( dvalue != 3.14 )
	{
		fprintf( stderr, "          Wrong value!  Should be 3.14!\n" );
		numErrors++;
	}

	pInfo = tagData1;
	ERR( TagTableAppend( tagTable,
		TagEntryAlloc( "pointer value", POINTER, &pInfo )), -1 );
	ERR( tagEntry = TagTableQDirect( tagTable, "pointer value", 0 ), TAGENTRYNULL );
	ERR( tag      = TagEntryQTag(      tagEntry         ), NULL );
	ERR( nthOccur = TagEntryQNthOccur( tagEntry         ), -1 );
	ERR( nthEntry = TagEntryQNthEntry( tagEntry         ), -1 );
	ERR( valueType= TagEntryQValueType(tagEntry         ), -1 );
	ERR(            TagEntryQValue(    tagEntry, &pInfo ), -1 );

	fprintf( stderr, "  %2d      %-23s  %4d   %08x%2d\n",
		nthEntry, tag, valueType, pInfo, nthOccur );
	if ( valueType != POINTER )
	{
		fprintf( stderr, "          Wrong type!   Should be %d!\n", POINTER );
		numErrors++;
	}
	if ( pInfo != tagData1 )
	{
		fprintf( stderr, "          Wrong value!  Should be 0x%08x!\n",
			tagData1 );
		numErrors++;
	}

	fprintf( stderr, "\n%d errors\n", numErrors );
	fprintf( stderr, "\nDone\n" );
}





/*
 *  FUNCTION
 *	tagCheckNEntries	-  check that # of table entris is correct
 *
 *  DESCRIPTION
 *	The tag table's entry count is checked against what it should be.
 *	If it's wrong, print an error.
 */

static int				/* Returns nothing		*/
#ifdef __STDC__
tagCheckNEntries( TagTable *tagTable, int shouldBe )
#else
tagCheckNEntries( tagTable, shouldBe )
	TagTable *tagTable;		/* Tag table to check		*/
	int       shouldBe;		/* How many should be there	*/
#endif
{
	int       n;			/* Counter			*/

	n = TagTableQNEntry( tagTable, NULL );
	if ( n == shouldBe )
		fprintf( stderr, "  %d Entries in table.\n", n );
	else
	{
		fprintf( stderr, "  %d Entries in table.  Wrong!  Should be %d!\n", n, shouldBe );
		numErrors++;
	}
	return ( 0 );
}





/*
 *  FUNCTION
 *	tagCheckEntries		-  check and print range of entries
 *
 *  DESCRIPTION
 *	The selected range of entries in the table is retrieved and compared
 *	against our test data.  The entry data is printed, along with error
 *	messages if it isn't what its supposed to be.
 */

static int				/* Returns nothing		*/
#ifdef __STDC__
tagCheckEntries( TagTable *tagTable, tagInfo *tagData, int startEntry,
	int endEntry, int stepInfo )
#else
tagCheckEntries( tagTable, tagData, startEntry, endEntry, stepInfo )
	TagTable   *tagTable;		/* Table to check		*/
	tagInfo    *tagData;		/* Info to check against	*/
	int         startEntry;		/* 1st table entry to check	*/
	int         endEntry;		/* last table entry to check	*/
	int         stepInfo;		/* Step count between entries	*/
#endif
{
	tagInfo    *pInfo;		/* Info table pointer		*/
	int         i;			/* Counter			*/
	TagEntry   *tagEntry;		/* Entry holder			*/
	char       *tag;		/* Tag				*/
	int         value;		/* Value			*/
	int	    nthOccur;		/* Occurrence #			*/
	int	    nthEntry;		/* Entry #			*/
	int	    valueType;		/* Size of value, in bytes	*/

	fprintf( stderr, "  Entry:  Tag:                     Type:  Value:  Occur:  Entry:\n" );
	for ( i = startEntry, pInfo = tagData; i <= endEntry;
		i++, pInfo += stepInfo )
	{
		ERR( tagEntry = TagTableQLinear(     tagTable, i      ), TAGENTRYNULL );
		ERR( tag      = TagEntryQTag(      tagEntry         ), NULL );
		ERR(            TagEntryQValue(    tagEntry, &value ), -1 );
		ERR( nthOccur = TagEntryQNthOccur( tagEntry         ), -1 );
		ERR( nthEntry = TagEntryQNthEntry( tagEntry         ), -1 );
		ERR( valueType= TagEntryQValueType(tagEntry         ), -1 );

		fprintf( stderr, "  %2d      %-23s  %2d     %3d     %2d      %2d\n",
			i, tag, valueType, value, nthOccur, nthEntry );
		if ( strcmp( tag, pInfo->info_tag ) != 0 )
		{
			fprintf( stderr, "          Wrong tag!.   Should be '%s'!\n",
				pInfo->info_tag );
			numErrors++;
		}
		if ( valueType != INT )
		{
			fprintf( stderr, "          Wrong type!   Should be %d!\n",
				INT );
			numErrors++;
		}
		if ( value != pInfo->info_value )
		{
			fprintf( stderr, "          Wrong value!  Should be %d!\n",
				pInfo->info_value );
			numErrors++;
		}
		if ( nthOccur != 1 && nthOccur != 0 )
		{
			fprintf( stderr, "          Wrong occ#!   Should be 0 or 1!\n" );
			numErrors++;
		}
		if ( nthEntry != i )
		{
			fprintf( stderr, "          Wrong ent#!   Should be %d!\n", i );
			numErrors++;
		}
	}
	return ( 0 );
}
