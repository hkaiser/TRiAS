/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/imvfbtext.c,v 1.0
 **	Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC)
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
 **				San Diego, CA  92186-9784
 **				(619) 534-5000
 **/

#define HEADER	"    $Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/imvfbtext.c,v 1.0 "

/**
 **  FILE
 **	imvfbtext.c	-   Add text to a VFB
 **
 **  PROJECT
 **	libim		-  SDSC image manipulation library
 **
 **  DESCRIPTION
 **	imvfbtext.c has routines for adding text to a VFB
 **    
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **	ImVfbText	f  Add text to a VFB
 **
 **
 **  PRIVATE CONTENTS
 **	ImBDFReadProperties		f	Read properties of a BDF
 **	ImBDFReadBitmap			f	Read BDF bitmap
 **	ImBDFReadLetter			f	Read one letter of a font
 **	ImBDFRead			f	Read an entire BDF font into memory
 **	ImChangeFontStructToVfbFont	f	Change a font struct to a VFB font
 **  	ImBDFWriteCharacters		f	Write BDF characters
 **	ImBDFWrite			f	Take a list of VFB's and write it out as a BDF
 **	ImFontStructInitialize		f 	Allocate memory for a FontStruct
 **	fontStruct			t	stores a font
 *	intToBin 			f	convert integer int binary
 *	lineRead			f	read a line
 *	lineWrite 			f	write a line
 **  HISTORY
 **	$Log: imvfbtext.c,v $
 * Revision 1.1  1994/10/03  11:32:46  nadeau
 * Initial revision
 *
 **  
 **/

#include "iminternal.h"
#include <malloc.h>

/* 
 *  FIX: These should not exist, the areas where these are used should utilize
 *  a dynamic allocation method, not static. 
 */

#define IM_ALPHABETSIZE 256	/* Maximum size of alphabet- 256 chars	*/
#define IM_BITMAPSIZEMAX 1024      /* Length of Bitmap- arbitrary		*/
#define IM_STRINGSIZE 256		/* Length of string 			*/
#define IM_VERBOSE 0

#define IM_XSPACING 3		/* Spacing between letters in X		*/
#define IM_YSPACING 2		/* Spacing between letters in Y		*/
#define IM_TABSIZE 4		/* Number of boxes to tab over		*/

#ifdef __STDC__
static void intToBin( int val, char string[IM_STRINGSIZE], int minWidth );
static void lineRead( int ioType, int fd, FILE *fp, char *string );
static void lineWrite( int ioType, int fd, FILE *fp, char *string );
#else
static void intToBin( );
static void lineRead(  );
static void lineWrite( );
#endif





/*
 *  TYPEDEF & STRUCTURE
 *
 *  DESCRIPTION
 *	fontLetterStruct - holds info requarding a letter
 *	fontStruct - holds the entire font, including fontLetterStructs
 *
 *	These structs apply directly to the BDF fonts, and have been generalized
 *	somewhat to apply to all fonts.
 *
 *	The reason the data is divided up this way is since some of it 
 *	should be store in the tag table seperately. This is the order
 *	in which things are stored:
 *		- font name
 *		- font data struct (fontStruct)
 *	Then, for each character, three packages of information are store:
 *		- character name
 *		- character data struct (fontLetterStruct)
 *		- character VFB
 *
 *	(The tag table is the structure in which all the font data is
 *	eventually stored after reading in, and it is the structure into
 *	which the write functions look to get the data they need.)
 *
 *	Some of the data structures are just used during reading or writing,
 *	and there memory can be forgotten after use. These structures are
 *	allocated statically, as are ImBitmapLength and ImBitmap. On the 
 *	other hand, charName entries and fontName must have malloced memory so 
 *	that it is not tossed out at the end of these functions.
 */

/* 
 *  FIX: It is possible that, if a user uses the imtools to create their own
 *  font, that bitmaps will be extremely wide. In this case the bitmaps probably
 *  cannot be decribed as ints since the width of the bitmap will surely exceed
 *  integer widths. This is a problem that will probably need char strings. 
 */

char *ImFontName;			/* Name of the font		*/
char *ImCharNames[ IM_ALPHABETSIZE ];	/* Name of the characters	*/ 
int ImBitmapLengths[ IM_ALPHABETSIZE ];	/* Number of rows in the bitmap	*/
int *ImBitmaps[ IM_ALPHABETSIZE ];	 	/* Bitmaps of characters	*/

typedef struct fontLetterStruct
{
        int encoding;			/* ASCII enoding value 		*/
        int xSWidth, ySWidth;		/* Scalable widths		*/
        int xDWidth, yDWidth;		/* 	 			*/
        int BBw,BBh;			/* Width and height of letter	*/
	float BBxoffPerc, BByoffPerc;	/* Letter offsets expressed as 
						percentages of BBw and 
						BBy respectively.	*/
	int defined;			/* Specifies whether this letter
						is actually defined. Must 
						be set to TRUE if there 
						is a vfb and other data 
						available for a letter.	*/
} fontLetterStruct;

typedef struct fontStruct
{
        int numProperties;          	/* Number of font properties    */
        int numCharacters;          	/* How many characters          */
        int pointSize;			/* Point size			*/
        int xResolution;		/* X resolution			*/
        int yResolution;		/* Y resolution			*/	
        int xFontBoundingBox;		/* Maximum x size		*/
        int yFontBoundingBox;		/* Maximum y size		*/
        int xDisplacement;		/* How far to translate in x	*/
        int yDisplacement;		/* How far to translate in y	*/
        struct fontLetterStruct *letters[ IM_ALPHABETSIZE ];
					/* The whole alphabet struct	*/
                                        /* Array length IM_ALPHABETSIZE 	*/
	char version[ IM_STRINGSIZE ];	/* Version of font 		*/
} fontStruct;


fontStruct* ImFontStructInitialize( );


/*
 *  FUNCTION
 *	intToBin 
 *
 *  DESCRIPTION
 *	Converts an integer (val) into a binary string (string)
 *	that has minimum width (minWidth). 
 *
 *  NOTES
 *	This function is used by ImChangeFontStructToVfbFont to determine 
 *	bitmap information.
 */

static void 
#ifdef __STDC__
intToBin( int val, char string[IM_STRINGSIZE], int minWidth )
#else
intToBin( val, string, minWidth )
	int val;		/* Integer to make into binary string	*/
	char string[ IM_STRINGSIZE ]; /* Destination string 		*/
	int minWidth;		/* Minimum width allowed for string 	*/
#endif
{
	int place = 1;		/* Place holder for binary number 	*/
	int count = 0;		/* Location in string			*/
	int done = 0;		/* Done flag 				*/
	char temp;		/* Temporary string holder		*/	

	/*
	 *  Find out where to one's and zeros are in the integer
	 */
	while ( !done )
	{
		if ( val & place ) string[ count ] = '1';
		else string[count] = '0';
		++count;
		place *= 2;
		if ( count > minWidth ) done = 1;
	}
	string[count] = '\0';

	/*
	 *  The string is backwards, flip it around
	 */
	for ( place = 0; place < count / 2; place++)
	{
		temp = string[place];
		string[ place ] = string[ count - place - 1 ];
		string[ count - place - 1 ] = temp;
	}
}



/*
 *  FUNCTION
 *	lineRead 
 *
 *  DESCRIPTION
 *	This function reads in a buffer from the specified file
 *	pointer OR file descriptor. The selection of which one to use
 *	is determined by the value of ioType, which may either be 
 *	IMFILEIOFD for file descriptors or IMFILEIOFP for file 
 *	pointers.
 *
 *  NOTES
 *	This function is used by all functions that require reading from file
 *	pointers or file descriptors.
 */

static void 
#ifdef __STDC__
lineRead( int ioType, int fd, FILE *fp, char *string )
#else
lineRead( ioType, fd, fp, string )
        int     ioType;                 /* I/O flags                    */
        int     fd;                     /* Input file descriptor        */
        FILE    *fp;                    /* Input file pointer           */
	char	*string;
#endif
{
	char c;
	int count = 0;

	if ( ioType & IMFILEIOFD )
	{
		while ( c != '\0' )
		{
			read( fd, &c, 1 );
			string[ count ] = c;
			++count;
		}
	}
	
	if ( ioType & IMFILEIOFP )
	{
		fgets( string, IM_STRINGSIZE, fp );
	}
}


/*
 *  FUNCTION
 *	lineWrite 
 *
 *  DESCRIPTION
 *	This function writes out a buffer to the specified file
 *	pointer OR file descriptor. The selection of which one to use
 *	is determined by the value of ioType, which may either be 
 *	IMFILEIOFD for file descriptors or IMFILEIOFP for file 
 *	pointers.
 *
 *  NOTES
 *	This function is used by all functions wanting to write using a 
 *	file descriptor or file pointer.
 */
static void 
#ifdef __STDC__
lineWrite( int ioType, int fd, FILE *fp, char *string )
#else
lineWrite( ioType, fd, fp, string )
        int     ioType;                 /* I/O flags                    */
        int     fd;                     /* Input file descriptor        */
        FILE    *fp;                    /* Input file pointer           */
        char    *string;		/* The string to write		*/
#endif
{
	int count = 0;

	if ( ioType & IMFILEIOFD )
	{
		while ( ( string[count] != '\0' ) && ( count < IM_STRINGSIZE ) )
		{
			write( fd, &string[count], 1 );
			++count;
		}
	}

	if ( ioType & IMFILEIOFP )
	{
		fputs( string, fp );
		fputs( "\0", fp );
	}
}




/******************************** BDF FONT FUNCTIONS *************************/


/*
 *  FUNCTION
 *	ImBDFReadProperties	
 *
 *  DESCRIPTION
 *	Reads BDF properties assuming that all data
 *	up to an including STARTPROPERTIES has been read first
 *
 *  NOTES
 *	This function is used by ImBDFRead to get past the properties info.
 *
 *  WARNING
 *	For now, all properties are read but ignored. That is why there is
 *	no other structure passed in other than the IO information, because
 *	none of the properties are stored anywhere. It seems we've been getting
 *	on just fine without them so far anyway.
 */

void
#ifdef __STDC__
ImBDFReadProperties( int ioType, int fd, FILE *fp )
#else
ImBDFReadProperties( ioType, fd, fp )
        int     ioType;                 /* I/O flags                    */
        int     fd;                     /* Input file descriptor        */
        FILE    *fp;                    /* Input file pointer           */
#endif
{
	int done = 0;			/* done flag 			*/
	char string[ IM_STRINGSIZE ];	/* string to read in 		*/
	char line[ IM_STRINGSIZE ];	/* string to read in 		*/
	
	if ( IM_VERBOSE ) fprintf( stderr, "Reading BDF properties...\n" );

	/*
	 *  Look for ENDPROPERTIES then leave
	 */
	while ( !done )
	{
		lineRead( ioType, fd, fp, line );
		sscanf( line, "%s", string );
		if ( strcmp( string, "ENDPROPERTIES" ) == 0 )
			done = 1;
	}

	if ( IM_VERBOSE ) fprintf( stderr, "Done reading BDF properties...\n" );
}



/*
 *  FUNCTION		
 *	ImBDFReadBitmap	
 *
 *  DESRIPTION
 *	Reads a bitmap from the file assuming everything up to an including 
 *	"BITMAP" has been read first
 *
 *  NOTES
 *	This function is used by ImBDFReadLetter, which is in turn used by
 *	ImBDFRead.
 */

int 
#ifdef __STDC__
ImBDFReadBitmap( int ioType, int fd, FILE *fp, int aBitmap[IM_BITMAPSIZEMAX] )
#else
ImBDFReadBitmap( ioType, fd, fp, aBitmap )
        int ioType;                 	/* I/O flags                    */
        int fd;                     	/* Input file descriptor        */
        FILE *fp;                    	/* Input file pointer           */
	int aBitmap[ IM_BITMAPSIZEMAX ];	/* The bitmap			*/
#endif
{
	int done = 0;			/* Done flag			*/
	char string[ IM_STRINGSIZE ];	/* String in a line		*/
	char line[ IM_STRINGSIZE ];	/* Line to read in		*/
	int count = 0;			/* Bitmap integer counter	*/	
	int compiled = 0;		/* All bitmap rows ORed together */	
	int shift = 0;			/* How far to shift each row over */	
	int loop;			/* Looper 			*/
	char temp[ 40 ];		/* Temporary storage string 	*/
	int pwr = 1;			/* Highest power of 2 found	*/

	if ( IM_VERBOSE ) fprintf( stderr, "Reading BDF bitmaps...\n" );
	
	/*
	 *  Read in HEX strings and store them as INT's 
	 */
	while ( !done )
	{
		lineRead( ioType, fd, fp, line );
		sscanf( line, "%s", string );

		if ( strcmp( string, "ENDCHAR" ) == 0 )
			done = 1;
		else 
		{	
			sscanf( string, "%x", &aBitmap[ count ] );
			compiled |= aBitmap[ count ];
		}
			
		++count;
	}


	/*
	 *  Right shift the bitmap all the way to the right as far as we can.
	 */

        while ( ( ( compiled & pwr ) == 0 ) && ( pwr <= compiled ) ) 
	{
		pwr *= 2;
		++shift;
	}

	if ( shift ) --shift;

	for ( loop = 0; loop < count; loop++ )
		aBitmap[ loop ] = ( aBitmap[ loop ] >> shift );

	if ( IM_VERBOSE ) fprintf( stderr, "Done reading BDF bitmaps...\n" );

	return( count - 1 );
}



/*
 *  FUNCTION
 *	ImBDFReadLetter	
 *
 *  DESCRIPTION
 *	Reads all information about a character in the font, including the 
 *	bitmap
 *
 *  NOTES
 *	This function is used by ImBDFRead.
 */

void
#ifdef __STDC__
ImBDFReadLetter( int ioType, int fd, FILE *fp, fontLetterStruct *letter )
#else
ImBDFReadLetter( ioType, fd, fp, letter )
        int     ioType;                 /* I/O flags                    */
        int     fd;                     /* Input file descriptor        */
        FILE    *fp;                    /* Input file pointer           */
	fontLetterStruct* letter;	/* Letter that we read in	*/
#endif
{
	int done = 0;			/* Done flag 			*/
	char line[ IM_STRINGSIZE ];	/* A line of characters read in	*/
	int aBitmap[ IM_BITMAPSIZEMAX ];	/* A bitmap read in		*/
	char	string[ IM_STRINGSIZE ] ;	/* String read in		*/
	int	intList[ 4 ];		/* Integers of info read in	*/

	if ( IM_VERBOSE ) fprintf( stderr, "Reading a BDF letter...\n" );
	
	/*
	 *  Make some brave defaults. These may be bad defaults, but they
	 *  really must be specified in the BDF file. If they aren't found in
	 *  in the BDF file itself, the file does not follow standard and is
	 *  seriously lacking. 
	 */ 
	letter->encoding = 0;
	letter->xSWidth = 0;
	letter->ySWidth = 0;
	letter->xDWidth = 0;
	letter->yDWidth = 0;
	letter->BBw = 0;
	letter->BBh = 0;
	letter->BBxoffPerc = 0.0;
	letter->BByoffPerc = 0.0;
	letter->defined = FALSE;

	while ( !done )
	{
		/*
		 *  Read in a line and divide it up into a string and some
		 *  integers.
		 */

		intList[ 0 ] = 0;
		intList[ 1 ] = 0;
		intList[ 2 ] = 0;
		intList[ 3 ] = 0;
		lineRead( ioType, fd, fp, line );
		sscanf( line, "%s%d%d%d%d", string, &intList[ 0 ], 
			&intList[ 1 ], &intList[ 2 ], &intList[ 3 ] );

		/*
		 *  Handle the string.
		 */

		if ( strcmp( string, "ENDCHAR" ) == 0 ) 
			done=1;

		else if ( strcmp( string, "ENCODING" ) == 0 )
		{
			if ( intList[ 0 ] > 0 )
				letter->encoding = intList[ 0 ];

			else
				{
				/*
				 *  FIX: Some BDF files contain negative 
				 *  encoding values. For now, they are ignored
				 */

				fprintf( stderr, "ImVfbText: Negative encoding value ignored.\n");
				return;
				}
		}
		else if ( strcmp( string, "SWIDTH" ) == 0 )
		{
			letter->xSWidth = intList[ 0 ];
			letter->ySWidth = intList[ 1 ];
		}	
		else if ( strcmp( string, "DWIDTH" ) == 0 )
		{
			letter->xDWidth = intList[ 0 ];
			letter->yDWidth = intList[ 1 ];
		}	
		else if ( strcmp( string, "BBX" ) == 0 )
		{
			letter->BBw = intList[ 0 ];
			letter->BBh = intList[ 1 ];
			letter->BBxoffPerc = ( float ) intList[ 2 ] / 
				( float ) intList[ 0 ];
			letter->BByoffPerc = ( float ) intList[ 3 ] / 
				( float ) intList[ 1 ];
		}
		else if ( strcmp( string, "BITMAP" ) == 0 )
		{
			/*
			 *  If the BDF file follows the standard, the encoding
			 *  value will have already been read in. We first find
			 *  the bitmap length as we read it into a static 
			 *  bitmap. Then, after we allocate space for the 
			 *  bitmap in the bitmap array, we memcpy as much of it
			 *  that we need into this array position.
			 */

			ImBitmapLengths[ letter->encoding ] =
				ImBDFReadBitmap( ioType, fd, fp, aBitmap );

			ImBitmaps[ letter->encoding ] = (int *)malloc( sizeof( int ) *
				ImBitmapLengths[ letter->encoding ] );

			memcpy( ImBitmaps[ letter->encoding],
				aBitmap, sizeof( int ) * 
				ImBitmapLengths[ letter->encoding ] );

			letter->defined = TRUE;

			if ( IM_VERBOSE ) fprintf( stderr, "Done reading a BDF letter...\n" );

			return; /* Since this is also end of character. */
		}
	}

}



/*
 *  FUNCTION
 *	ImBDFRead	-  read a BDF font into memory
 *
 *  DESCRIPTION
 * 	The font file is read in. Each of the characters are stored in
 *	the tag table as a bunch of VFBs, one for each letter.
 *
 *  NOTES
 *	This function is a top level function that is used by no other
 *	function in this file. It is used by the imtext program.
 */

int				/* returns number of characters read */
#ifdef __STDC__
ImBDFRead( int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *fontAsVFBs )
#else
ImBDFRead( ioType, fd, fp, flagsTable, fontAsVFBs )
	int	ioType;			/* I/O flags 			*/
	int	fd;			/* Input file descriptor	*/
	FILE 	*fp;			/* Input file pointer 		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *fontAsVFBs;		/* Font stored as vfb list	*/
#endif
{
	char	line[ IM_STRINGSIZE ];	/* used to capture a whole line */
	int 	done = 0;		/* done reading flag 		*/
	int	letterCounter = 0;	/* counter for how many letters read */
	fontStruct *fontAsFontStruct;	/* structure to hold the font 	*/
	fontLetterStruct *aLetter;	/* A letter we are reading in	*/
	char	string[ IM_STRINGSIZE ] ;	/* String			*/
	int	intList[ 4 ];		/* Integers			*/
	char	stringList[ 4 ][ IM_STRINGSIZE ]; /* Strings		*/

	if ( IM_VERBOSE ) fprintf( stderr, "Reading BDF font...\n" );

	/*
	 *  Ready out font struct.
	 */
        fontAsFontStruct = ImFontStructInitialize();

	/*
	 *  Make some brave defaults. These may be bad defaults, but they
	 *  really must be specified in the BDF file. If they aren't found in
	 *  in the BDF file itself, the file does not follow standard and is
	 *  seriously lacking.
	 */ 
	strcpy( fontAsFontStruct->version, "1.0" );
	strcpy( ImFontName, "-SDSC-ImTools-NoName-" );
	fontAsFontStruct->pointSize = 0;
	fontAsFontStruct->xResolution = 0; 
	fontAsFontStruct->yResolution = 0; 
	fontAsFontStruct->xFontBoundingBox = 0; 
	fontAsFontStruct->yFontBoundingBox = 0;
	fontAsFontStruct->xDisplacement = 0; 
	fontAsFontStruct->yDisplacement = 0;
	fontAsFontStruct->numProperties = 0; 
	fontAsFontStruct->numCharacters = 0;

	/*
	 * Read in the font.
	 * Store each letter of the font as VFBs.
	 */
	while ( !done )
	{
		/*
		 *  Read in a line and divide it up into strings and integers
		 *  for easy parsing.
		 */

		intList[ 0 ] = 0;
		intList[ 1 ] = 0;
		intList[ 2 ] = 0;
		intList[ 3 ] = 0;
		lineRead( ioType, fd, fp, line );
		sscanf( line, "%s%d%d%d%d", string, &intList[ 0 ], 
			&intList[ 1 ], &intList[ 2 ], &intList[ 3 ] );
		sscanf( line, "%s%s%s%s%s", string, stringList[ 0 ], 
			stringList[ 1 ], stringList[ 2 ], stringList[ 3 ] );
	
		/*
		 *  Handle the string.
		 */

		if ( strcmp( string, "STARTFONT" ) == 0 )
		{
			strcpy( fontAsFontStruct->version, stringList[ 0 ] );
		}

		else if ( strcmp( string, "FONT" ) == 0 )
		{
			strcpy( ImFontName, stringList[ 0 ] );
		}

		else if ( strcmp( string, "COMMENT" ) == 0 )
		{
			/* Do nothing with comments. */
		}

		else if ( strcmp( string, "SIZE" ) == 0 )
		{
			fontAsFontStruct->pointSize = intList[ 0 ];
			fontAsFontStruct->xResolution = intList[ 1 ];
			fontAsFontStruct->yResolution = intList[ 2 ]; 
		}

		else if ( strcmp( string, "FONTBOUNDINGBOX" ) == 0 )
		{
			fontAsFontStruct->xFontBoundingBox = intList[ 0 ];
			fontAsFontStruct->yFontBoundingBox = intList[ 1 ];
			fontAsFontStruct->xDisplacement = intList[ 2 ];
			fontAsFontStruct->yDisplacement = intList[ 3 ];
		}

		else if ( strcmp( string, "STARTPROPERTIES" ) == 0 )
		{
			fontAsFontStruct->numProperties = intList[ 0 ];
			ImBDFReadProperties( ioType, fd, fp );
		}

		else if ( strcmp( string, "CHARS" ) == 0 )
		{
			fontAsFontStruct->numCharacters = intList[ 0 ];
		}

		else if ( strcmp( string, "STARTCHAR" ) == 0 )
		{
			aLetter = (fontLetterStruct *)malloc( sizeof( fontLetterStruct ) );
			ImBDFReadLetter( ioType, fd, fp, aLetter );

			if ( aLetter->defined == TRUE )
			{
				strcpy( ImCharNames[ aLetter->encoding ],
					stringList[ 0 ] );
				fontAsFontStruct->letters[ aLetter->encoding ] =
					aLetter;
				++letterCounter;
			}
		}
		else if ( strcmp( string, "ENDFONT" ) == 0 )
			done = 1;
	}

        ImChangeFontStructToVfbFont( fontAsFontStruct, fontAsVFBs );

	if ( IM_VERBOSE ) fprintf( stderr, "Reading BDF font...\n" );

	return( letterCounter );
}



/*
 *  FUNCTION
 *	ImChangeVfbFontToFontStruct
 *
 *  DESCRIPTION
 *	Takes a VFB font and fills the different font structs with the 
 *	information.
 *
 *  NOTES
 *	This function is a top level function and is used by no other function
 *	in this file.
 */

void
#ifdef __STDC__
ImChangeVfbFontToFontStruct( TagTable *fontTagTable, fontStruct *aFont )
#else
ImChangeVfbFontToFontStruct( fontTagTable, aFont )
        TagTable        *fontTagTable;
        fontStruct      *aFont;
#endif
{
#if NOTEVENCLOSETOBEINGREADY
/* 
 *  FIX: This needs to be written. It won't be too hard.
 */
#endif
}



/*
 *  FUNCTION
 *	ImChangeFontStructToVfbFont
 *
 *  DESCRIPTION
 *	changes a BDF font as read in into a font represented as a group of
 *	VFB's
 *
 *  NOTES
 *	This function is used by ImBDFRead at the end of its reading cycle to
 *	convert the font structs it fills into a tag table font.
 */

int
#ifdef __STDC__
ImChangeFontStructToVfbFont( fontStruct * aFont, TagTable *fontTagTable )
#else
ImChangeFontStructToVfbFont( aFont, fontTagTable )
	fontStruct 	*aFont;
	TagTable	*fontTagTable;
#endif
{
	int loop, x, y;
	int shiftDown, shiftRight;
	ImVfb *vfb;
	ImVfbPtr pPixel;
	char binary[ IM_BITMAPSIZEMAX ];
	fontLetterStruct *aLetter;
	int width, height;


	if ( IM_VERBOSE ) fprintf( stderr, "Changing BDF font to general...\n" );

	/*
	 *  Store the name first. Next, insert font information so we can get 
	 *  at the rest of the font data.
	 */
	TagTableAppend( fontTagTable, TagEntryAlloc( "image font name" , 
		POINTER, &ImFontName ) );
	TagTableAppend( fontTagTable, TagEntryAlloc( "image font data" , 
		POINTER, &aFont ) );


	/*
         * Turn each of the font characters into a vfb
	 */
	for ( loop = 0; loop < IM_ALPHABETSIZE; loop++ )
	{
		/*
		 *  Store the character name and its data in the tag table.
		 */
 
		aLetter = aFont->letters[ loop ];
		TagTableAppend( fontTagTable, TagEntryAlloc( 
			"image name" , POINTER, &ImCharNames[ loop ] ) );
		TagTableAppend( fontTagTable, TagEntryAlloc( 
			"image character data" , POINTER, &aLetter ) );

		/*
		 *  Find width and height of character VFB.
		 */

		width =  aFont->letters[ loop ]->BBw;
		height = aFont->letters[ loop ]->BBh;

		/*
		 * Allocate space for a character's vfb
		 */

		if ( ( vfb = ImVfbAlloc( width, height,
			IMVFBMONO ) ) == IMVFBNULL )
		{
			ImErrorFatal( ImQError( ), -1, ImErrNo );
		}

		/*
		 * Set pointer at VFB beginning for this character
		 */

		pPixel = ImVfbQFirst( vfb );

		/* 
		 * Now start filling in the character data into a VFB
		 */

		for ( y = 0; y < height; y++ )	
		{
			/* 
			 * Get a string representation for the bitmap part
			 * we are at.
			 */
			intToBin( ImBitmaps[ loop ][ y ], binary, width);

			/*
			 * Copy this row of the bitmap into the VFB
			 */
			for ( x = 0; x < width; x++ )	
			{
				if ( binary[ x ] == '1' )
				{
					ImVfbSMono( vfb, pPixel, 0x1 );
				}
				else
				{
					ImVfbSMono( vfb, pPixel, 0x0 );
				}
					
                        	ImVfbSInc( vfb, pPixel );
			}
		}

		/*
		 * Stick the new VFB in our tag table
		 */

		TagTableAppend( fontTagTable, TagEntryAlloc( "image vfb" , 
			POINTER, &vfb ) );
	} 

	if ( IM_VERBOSE ) fprintf( stderr, "Done changing BDF font\n" );
}


/*
 *  FUNCTION
 *  	ImBDFWriteCharacters
 *
 *  DESCRIPTION
 *	This function will write out all of the character information in BDF
 *	format. This serves as a sub function of ImBDFWrite.
 *
 *  NOTES
 *	This function is used by ImBDFWrite to handle the operation of writing
 *	out all of the character information.
 */

void
#ifdef __STDC__
ImBDFWriteCharacters( int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *fontTagTable )
#else
ImBDFWriteCharacters( ioType, fd, fp, flagsTable, fontTagTable )
	int	ioType;			/* I/O flags 			*/
	int	fd;			/* Input file descriptor	*/
	FILE 	*fp;			/* Input file pointer 		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *fontTagTable;		/* Font stored as vfb list	*/
#endif
{
	TagEntry *fontDataTagEntry;	/* Tag table entry holding font data */
	TagEntry *letterVfbTagEntry;	/* Tag table entry holding letter vfb */
	TagEntry *charNameTagEntry;	/* Tag table entry holding letter vfb */
	ImVfb *letterVfb;		/* The letter vfb itself 	*/
	struct fontStruct* fontData; /* Data about the font		*/
	struct fontLetterStruct* letterData; /* Data about a letter	*/
	int count = 0;			/* A counter			*/
	int done = 0;			/* Done flag			*/
	char string[ IM_STRINGSIZE ];	/* A general outputing string	*/
	char *aCharName;
	ImVfbPtr pLetterVfb;		/* Pixel pointer into the letter vfb */
	int hold;			/* Byte value for a vfb row	*/
	int x,y,l;			/* Counters			*/

	/*
	 *  Get the general font information that should be stored in the
	 *  tag table. If it's not, it's an error.
	 */

	fontDataTagEntry=TagTableQDirect( fontTagTable, "image font data", 0 );
	TagEntryQValue( fontDataTagEntry, &fontData );

	/*
	 *  Go through each letter one at a time and output those that are
	 *  actually defined only.
	 */

	for ( count = 0; count < IM_ALPHABETSIZE; count ++ )
	if ( fontData->letters[ count ]->defined )
	{
		/*
		 *  Get a handle to the letter data then do all the IO.
		 */

		letterData = fontData->letters[ count ];

		charNameTagEntry = TagTableQDirect( fontTagTable, "image name",
			count );
		TagEntryQValue( charNameTagEntry, &aCharName );
		sprintf( string, "STARTCHAR %s\n", aCharName ); 
		lineWrite( ioType, fd, fp, string );

		sprintf( string, "ENCODING %d\n", letterData->encoding );
		lineWrite( ioType, fd, fp, string );

		sprintf( string, "SWIDTH %d %d\n",
			letterData->xSWidth,
			letterData->ySWidth );
		lineWrite( ioType, fd, fp, string );

		sprintf( string, "DWIDTH %d %d\n",
        		letterData->xDWidth, letterData->yDWidth );
		lineWrite( ioType, fd, fp, string );

		sprintf( string, "BBX %d %d %d %d\n",
        		letterData->BBw, 
			letterData->BBh, 
			(int)(letterData->BBxoffPerc * (float)letterData->BBw), 
			(int)(letterData->BByoffPerc * (float)letterData->BBh));
		lineWrite( ioType, fd, fp, string );

		lineWrite( ioType, fd, fp, "BITMAP\n" );


                /*
                 *  Get letter vfb
                 */

                letterVfbTagEntry = TagTableQDirect( fontTagTable, "image vfb",
			count );
                TagEntryQValue( letterVfbTagEntry, &letterVfb );


		/*
		 *  Form a Hex Number from a whole horizontal row of pixels
		 */
		
		for ( y = 0; y < ImVfbQHeight( letterVfb ); y++ )
		{
			hold = 0;

			for ( x = 0; x < ImVfbQWidth( letterVfb ); x++ )
			{
				hold *= 2;
				pLetterVfb = ImVfbQPtr( letterVfb, x, y );
				if ( ImVfbQMono( letterVfb, pLetterVfb ) )
					hold += 1;
			}

/* 
 *  FIX: 'hold' should actually be left shifted to the nearest eight bits, not
 *  just multiplied by two 
 */
			hold *= 2;
			sprintf( string, "%x", hold );

			sprintf( string, "%s\n", string );
			lineWrite( ioType, fd, fp, string );
		}

		lineWrite( ioType, fd, fp, "ENDCHAR\n" );
	}
}



/*
 *  FUNCTION
 *	ImBDFWrite	-  Take a list of VFB's and write it out as a BDF
 *		font.
 *
 *  DESCRIPTION
 *	The vfb's must be stored in a tag table in consectutive order. The
 *	first encoding value must be stored in a "font data" tag table entry
 *	which must be a fontStruct.
 *
 *  NOTES
 *	This is a top level function and is not used by any other function
 *	in this file.
 */

int				/* returns number of characters read */
#ifdef __STDC__
ImBDFWrite( int ioType, int fd, FILE *fp, TagTable *flagsTable, TagTable *fontAsVFBs )
#else
ImBDFWrite( ioType, fd, fp, flagsTable, fontAsVFBs )
	int	ioType;			/* I/O flags 			*/
	int	fd;			/* Input file descriptor	*/
	FILE 	*fp;			/* Input file pointer 		*/
	TagTable *flagsTable;		/* Flags			*/
	TagTable *fontAsVFBs;		/* Font stored as vfb list	*/
#endif
{
	TagEntry *fontDataTagEntry;	/* Tag table entry holding font data */
	TagEntry *fontNameTagEntry;	/* Tag table entry holding font data */
	struct fontStruct *fontData; 	/* Data about the font		*/
	char string[ IM_STRINGSIZE ];	/* General purpose string 	*/
	char *aFontName;		/* Font name from tag table	*/


	/*
	 *  Get the general font information that should be stored in the
	 *  tag table. If it's not, it's an error.
	 */

	fontDataTagEntry = TagTableQDirect( fontAsVFBs, "image font data", 0 );
	TagEntryQValue( fontDataTagEntry, &fontData );

	
	/*
	 *  Write out the header.
	 */

	
	sprintf( string, "STARTFONT %s\n", fontData->version ); 
	lineWrite( ioType, fd, fp, string );

	lineWrite( ioType, fd, fp, "COMMENT *** This font was generated by SDSC images tools. ***\n");
	lineWrite( ioType, fd, fp, "COMMENT It may or may not be the font that the following FONT line specifies.\n" );
	lineWrite( ioType, fd, fp, "COMMENT Also, the sizes and such may have been altered by the other image tools if the user decided to do so.\n" );
	lineWrite( ioType, fd, fp, "COMMENT SDSC and Shane Cooper are in no way responsible for catastrophes that may result from this.\n" );

	fontNameTagEntry = TagTableQDirect( fontAsVFBs, "image font name", 0 );
	TagEntryQValue( fontNameTagEntry, &aFontName );
	sprintf( string, "FONT %s\n", aFontName ); 
	lineWrite( ioType, fd, fp, string );

	sprintf( string, "SIZE %d %d %d\n", 
		fontData->pointSize,
		fontData->xResolution, 
		fontData->yResolution );
	lineWrite( ioType, fd, fp, string );

	sprintf( string, "FONTBOUNDINGBOX %d %d %d %d\n",
		fontData->xFontBoundingBox, 
		fontData->yFontBoundingBox,
		fontData->xDisplacement, 
		fontData->yDisplacement );
	lineWrite( ioType, fd, fp, string );

	lineWrite( ioType, fd, fp, "STARTPROPERTIES 0\n" );
	lineWrite( ioType, fd, fp, "ENDPROPERTIES\n" );

	sprintf( string, "CHARS %d\n", fontData->numCharacters );
	lineWrite( ioType, fd, fp, string );
	

	/*
	 *  Write out the individual characters.
	 */

	ImBDFWriteCharacters( ioType, fd, fp, flagsTable, fontAsVFBs );
	
	lineWrite( ioType, fd, fp, "ENDFONT\n" );
}


/******************************** IMVFBTEXT FUNCTIONS ***********************/


/*
 *  FUNCTION
 *      ImFontStructInitialize 
 *
 *  DESCRIPTION 
 *	Allocate new space for a font struct and initialize some wise defaults.
 *
 *  NOTES
 *	This function is used by ImBDFRead to set up a new fontStruct.
 */

fontStruct*
ImFontStructInitialize( )
{
        fontStruct* aFont;
        int l;

	/*
	 *  Allocate and make some wise default values.
	 */

        aFont = (fontStruct *)malloc( sizeof( fontStruct ) );
	ImFontName = (char *)malloc( sizeof( char ) * IM_STRINGSIZE );

	strcpy( ImFontName, "-SDSC-ImTools-Font-" );
        strcpy( aFont->version, "1.0" );

        aFont->numProperties = 0;
        aFont->numCharacters = 0;
        aFont->pointSize = 0;
        aFont->xResolution = 0;
        aFont->yResolution = 0;
        aFont->xFontBoundingBox = 0;
        aFont->yFontBoundingBox = 0;
        aFont->xDisplacement = 0;
        aFont->yDisplacement = 0;

        for ( l = 0; l < IM_ALPHABETSIZE; l++ )
	{
                aFont->letters[ l ] = (fontLetterStruct *)malloc( sizeof( fontLetterStruct ) );
		aFont->letters[ l ]->encoding = l;
		aFont->letters[ l ]->defined = FALSE;
		aFont->letters[ l ]->BBw = 0;
		aFont->letters[ l ]->BBh = 0;
        	aFont->letters[ l ]->xSWidth = 0;
		aFont->letters[ l ]->ySWidth = 0;
        	aFont->letters[ l ]->xDWidth = 0;
		aFont->letters[ l ]->yDWidth = 0;
        	aFont->letters[ l ]->BBxoffPerc = 0.0;
		aFont->letters[ l ]->BByoffPerc = 0.0;
		ImBitmapLengths[ l ] = 0;

		ImCharNames[ l ] = (char *)malloc( sizeof( char ) * IM_STRINGSIZE );
		sprintf( ImCharNames[ l ], "ascii_%d", l );
	}

        return ( aFont );
}



/*
 *  FUNCTION
 *	ImVfbTextMonoVfbToColorVfb - change a monochrome vfb to an RGB-ALPHA 
 *	vfb with the specified colors and alpha
 *
 *  DESCRIPTION
 *	The monochrome vfb and the color vfb must be the same dimensions. Also,
 *	the color vfb must be properly allocated prior to this call with RGB
 *	and alpha fields.
 *
 *  NOTES
 *	This is called by ImVfbText to convert a letter of a tag table font
 *	into a new letter of the desired color and alpha.
 */

void 
#ifdef __STDC__
ImVfbTextMonoVfbToColorVfb( ImVfb *vfbMono, int red, int green, int blue, int alpha, ImVfb *vfbColor )
#else
ImVfbTextMonoVfbToColorVfb( vfbMono, red, green, blue, alpha, vfbColor )
	ImVfb *vfbMono;		/* Monochrome vfb to convert from	*/
	int red;		/* Red value to convert too		*/
	int green;		/* Green value to convert too		*/
	int blue;		/* Blue value to convert too		*/
	int alpha;		/* Alpha value to convert too		*/
	ImVfb *vfbColor;	/* The target converted vfb		*/
#endif
{
	ImVfbPtr pixelMono;	/* A pointer into the monochrome vfb	*/
	ImVfbPtr pixelColor;	/* A pointer into the color vfb		*/
	int width;		/* Width counter			*/
	int height;		/* Height counter			*/


	/*
	 *  Go through the monochrome vfb. For every pixel that is set, change
	 *  the corresponding pixel in the color vfb to the color and alpha 
	 *  values needed.
	 */

	for ( width  = 0; width  < ImVfbQWidth(  vfbMono ); width++  )
	for ( height = 0; height < ImVfbQHeight( vfbMono ); height++ )
	{
		pixelMono =  ImVfbQPtr( vfbMono,  width, height );
		pixelColor = ImVfbQPtr( vfbColor, width, height );

		if ( ImVfbQMono( vfbMono, pixelMono ) )
		{
			ImVfbSRed(   vfbColor, pixelColor, red );
			ImVfbSGreen( vfbColor, pixelColor, green );
			ImVfbSBlue(  vfbColor, pixelColor, blue );
			ImVfbSAlpha( vfbColor, pixelColor, alpha );
		}

		else
		{
			ImVfbSRed(   vfbColor, pixelColor, 0x0 );
			ImVfbSGreen( vfbColor, pixelColor, 0x0 );
			ImVfbSBlue(  vfbColor, pixelColor, 0x0 );
			ImVfbSAlpha( vfbColor, pixelColor, 0x0 );
		}
	}
}


/*
 *  FUNCTION
 *	ImVfbText
 *
 *  DESCRIPTION:
 *	This function composites message on top of imageVfb in the desired
 *	red, green, blue, and alpha values. The message can be placed in the
 *	field using xPosition and yPosition. The fontTagTable must contain the
 *	font the user desires to use. This font is stored like this:
 *
 *	First:		char* font_name
 *			fontStruct* font_info
 *	Each character:	char* character_name
 *			fontLetterStruct* font_letter_info
 *			ImVfb* fontLetterVfb font_letter_vfb
 *
 *	Note that each of the tag table entries must be filled in with valid
 *	values, including the fields in the structs themselves. For those
 *	letters not defined by the font, this data should still exist in those
 *	positions, but the defined flag of the fontLetterStruct should
 *	be set false. 
 *
 *  NOTES
 *	This is the main function here that actually places the text onto a 
 *	VFB. This is a top level function, and is called by the imtext program.
 */

/*
 *  FIX:
 *	Right now, I am only accepting MONO vfbs in the font tag table, and
 *	the image vfb must be RGB|ALPHA. Vfbs should be promoted to whatever
 *	they need to be for this function to work properly.
 */

ImVfb *
#ifdef __STDC__
ImVfbText( TagTable *fontTagTable, ImVfb *imageVfb, char *message, int red, int green, int blue,
	int alpha, int xPosition, int yPosition )
#else
ImVfbText( fontTagTable, imageVfb, message, red, green, blue,
	alpha, xPosition, yPosition )
	TagTable *fontTagTable;		/* Tag table containing font 	*/
	ImVfb *imageVfb;		/* Vfb holding image 		*/
	char *message;			/* The message itself		*/
	int red;			/* Red value 			*/
	int green;			/* Green value 			*/
	int blue;			/* Blue value 			*/
	int alpha;			/* Alpha value			*/
	int xPosition;			/* X starting position, pixels	*/
	int yPosition;			/* Y starting position, pixels	*/
#endif
{	
	TagEntry *fontTagEntry;		/* Entry in the font tag table	*/
	TagTable *combinedTagTable;	/* Tag table, image with text	*/ 
	TagEntry *combinedTagEntry;	/* Tag entry, image with text	*/
	ImVfb *fontLetterVfbMono;	/* Vfb for the letter of the font */
	ImVfb *fontLetterVfbColored;	/* Vfb for letter, but colored	*/
	ImVfb *combinedVfb;		/* Vfb holding image with text	*/
	int l = 0;			/* Loop variable		*/
	int xPositionHome = 0;		/* Starting X position		*/
	int yPositionHome = 0;		/* Starting Y position		*/
	TagEntry *fontDataTagEntry;	/* Entry for fontData		*/
	struct fontStruct* fontData; 	/* Data about the font		*/
	int letterNumber = 0;		/* Number of letter in font table */
	int xOffset = 0;		/* How far to displace character in x */
	int yOffset = 0;		/* How far to displace character in y */
	int baseLine = 0;		/* The baseline of the font 	*/


	/* 
	 *  Initialize
	 *  	- allocate a new tag table
	 *	- set home positions 
	 *	- get the font data from the table
	 */

	combinedTagTable = TagTableAlloc( );
	xPositionHome = xPosition;
	yPositionHome = yPosition;

	fontDataTagEntry=TagTableQDirect( fontTagTable, "image font data", 0 );
	TagEntryQValue( fontDataTagEntry, &fontData );

	
	/* 
	 *  Plop the message onto image image vfb letter by letter 
	 *  (it cummulates onto the image vfb) 
	 */

	for ( l = 0; l < strlen( message ); l++ )
	{

		/*
		 *  Handle the special characters (such as \n)
		 */

		if ( message[ l ] == '\\' )
		{
			++l;

			if ( message[ l ] == 'n' )
			{
				xPosition = xPositionHome;
				yPosition += fontData->yFontBoundingBox + 
					IM_YSPACING;
			}
	
			else if ( message[ l ] == 't' )
			{
				xPosition += IM_TABSIZE * ( 								fontData->xFontBoundingBox + IM_XSPACING );
			}

			else
			{
				fprintf( stderr, "ImVfbText: Special character \\%c not yet supported.\n", message[ l ] );
			}
		}


		/*
		 *  Handle the regular characters
		 */

		else
		{
			letterNumber = message[ l ];

			/* 
			 *  Get letter vfb 
			 */

			fontTagEntry=TagTableQDirect( fontTagTable, "image vfb",
				letterNumber );
			TagEntryQValue( fontTagEntry, &fontLetterVfbMono );


			/* 
			 *  Color the font letter 
			 */

        		fontLetterVfbColored = ImVfbAlloc( 
				ImVfbQWidth( fontLetterVfbMono ), 
				ImVfbQHeight( fontLetterVfbMono ),
                		IMVFBRGB | IMVFBALPHA );
        		ImVfbClear( IMVFBRGB,   0, fontLetterVfbColored );
        		ImVfbClear( IMVFBALPHA, 0, fontLetterVfbColored );

			ImVfbTextMonoVfbToColorVfb( fontLetterVfbMono, red, 
				green, blue, alpha, fontLetterVfbColored );


			/* 
			 *  Combine 
			 *	- x offset is how far to offset the character
			 * 		in x
			 * 	- y offset is how far to offset the character
			 *		in y, and consists of moving it from
			 * 		the baseline
			 *	- the baseline must be calculated for each
			 *	 	character, I remember taking golf
			 *		lessons in Orange County
			 */

			baseLine = 
				fontData->yFontBoundingBox -
                                fontData->letters[ letterNumber ]->BBh;

			xOffset = 
			(int)(fontData->letters[ letterNumber ]->BBxoffPerc *
				(float)fontData->letters[ letterNumber ]->BBw);

			yOffset = 
			baseLine -
			(int)(fontData->letters[ letterNumber ]->BByoffPerc *
				(float)fontData->letters[ letterNumber ]->BBh);

			combinedVfb = ImVfbComp( fontLetterVfbColored, 0, 0, 
				ImVfbQWidth( fontLetterVfbColored ), 
				ImVfbQHeight( fontLetterVfbColored ), 
				IMRED|IMGREEN|IMBLUE, IMCOMPOVER, imageVfb, 
				xPosition + xOffset, yPosition + yOffset );

			ImVfbFree( fontLetterVfbColored );

			xPosition += 
				fontData->letters[ letterNumber ]->BBw +
				xOffset + IM_XSPACING;
		}
	}

	return( combinedVfb );
}


