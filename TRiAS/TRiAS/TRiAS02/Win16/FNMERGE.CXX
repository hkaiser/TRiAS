/*-----------------------------------------------------------------------*
 * filename - fnmerge.c
 *
 * function(s)
 *        fnmerge - make new filename
 *-----------------------------------------------------------------------*/

/*[]---------------------------------------------------[]*/
/*|							|*/
/*|	Turbo C Run Time Library - Version 2.0		|*/
/*|							|*/
/*|							|*/
/*|	Copyright (c) 1987,1988 by Borland International|*/
/*|	All Rights Reserved.				|*/
/*|							|*/
/*[]---------------------------------------------------[]*/


#include <dir.h>
#include <string.h>

/*---------------------------------------------------------------------*

Name		fnmerge - makes new file name

Usage		#include <dir.h>
		void fnmerge(char *path, const char * drive, const char * dir,
			     const char * name, const char * ext);

Related
functions usage	int fnsplit(const char *path, char *drive, char *dir,
			    char *name, char *ext);

Prototype in	dir.h

Description	fnmerge makes a file name from its components. The
		new file's full path name is

			X:\DIR\SUBDIR\NAME.EXT

		where

			X is given by drive
			\DIR\SUBDIR\ is given by dir
			NAME.EXT is given by name and ext

		fnsplit takes a file's full path name (path) as a string
		in the form

			X:\DIR\SUBDIR\NAME.EXT

		and splits path into its four components. It then stores
		those components in the strings pointed to by drive, dir,
		name and ext. (Each component is required but can be a
		NULL, which means the corresponding component will be
		parsed but not stored.)

		The maximum sizes for these strings are given by the
		constants MAXDRIVE, MAXDIR, MAXPATH, MAXNAME and MAXEXT,
		(defined in dir.h) and each size includes space for the
		null-terminator.

			Constant	(Max.)	String

			MAXPATH		(80)	path
			MAXDRIVE	(3)	drive; includes colon (:)
			MAXDIR		(66)	dir; includes leading and
						trailing backslashes (\)
			MAXFILE		(9)	name
			MAXEXT		(5)	ext; includes leading dot (.)

		fnsplit assumes that there is enough space to store each
		non-NULL component. fnmerge assumes that there is enough
		space for the constructed path name. The maximum constructed
		length is MAXPATH.

		When fnsplit splits path, it treats the punctuation as
		follows:

		* drive keeps the colon attached (C:, A:, etc.)

		* dir keeps the leading and trailing backslashes
		  (\turboc\include\,\source\, etc.)

		* ext keeps the dot preceding the extension (.c, .exe, etc.)

		These two functions are invertable; if you split a given path
		with fnsplit, then merge the resultant components with fnmerge,
		you end up with path.

Return value	fnsplit returns an integer (composed of five flags,
		defined in dir.h) indicating which of the full path name
		components were present in path; these flags and the components
		they represent are:

			EXTENSION	an extension
			FILENAME	a filename
			DIRECTORY	a directory (and possibly
					sub-directories)
			DRIVE		a drive specification (see dir.h)
			WILDCARDS	wildcards (* or ? cards)

*---------------------------------------------------------------------*/

// Prototypes
static char *stpcpy (char *, const char *);

void _far _pascal 
fnmerge(register char *pathP,const char *driveP,const char *dirP,
const char *nameP,const char *extP)
{
	if (driveP && *driveP)
	{
		*pathP++ = *driveP++;
		*pathP++ = ':';
	}
	if (dirP && *dirP)
	{
		pathP = stpcpy(pathP,dirP);
		if (*(pathP-1) != '\\' && *(pathP-1) != '/') *pathP++ = '\\';
	}
	if (nameP) pathP = stpcpy(pathP,nameP);
	if (extP)  pathP = stpcpy(pathP,extP);
	*pathP = 0;
}


static char *stpcpy (register char *str1, register const char *str2) {

	strcpy (str1, str2);

return &str1[strlen(str1)];
}

