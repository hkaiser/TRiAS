/*------------------------------------------------------------------------
 * filename - fnsplit.c
 *
 * function(s)
 *        CopyIt   - copies a string to another
 *        DotFound - checks for special directory names
 *        fnsplit  - splits a full path name into its components
 *----------------------------------------------------------------------- */

#include <dir.h>
#include <string.h>

/* ----------------------------------------------------------------------------

Name		CopyIt - copies a string to another

Usage		void pascal near CopyIt(char *dst, const char *src,
					unsigned maxlen)

Prototype in	local to this module

Description	copies string scr to string dst.

Return value	nothing

---------------------------------------------------------------------------- */
static void pascal near CopyIt (char *dst, const char *src, unsigned maxlen)
{
	if (dst) {
		if(strlen(src) >= maxlen)
		{
			strncpy(dst, src, maxlen);
			dst[maxlen] = 0;
		}
		else
			strcpy(dst, src);
	}
}

/* ----------------------------------------------------------------------------

Name		DotFound - checks for special dir name cases

Usage		int pascal near DotFound(char *pB);

Prototype in	local to this module

Description	checks for special directory names

---------------------------------------------------------------------------- */
static int pascal near DotFound (char *pB)
{
	if (*(pB-1) == '.')
		pB--;
	switch (*--pB) {
	case ':'  :
		if (*(pB-2) != '\0')
			break;
	case '/'  :
	case '\\' :
	case '\0' :
		return 1;
	}
	return 0;
}

/* ----------------------------------------------------------------------------

Name		fnsplit - splits a full path name into its components

Usage		#include <dir.h>
		void fnsplit(const char *path, char * drive, char * dir,
			     char * name, char * ext);

Related
functions usage	int fnmerge(char *path, const char *drive, const char *dir,
			    const char *name, const char *ext);

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

		These two functions are invertible; if you split a given path
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

--------------------------------------------------------------------------- */
int _far _pascal
        fnsplit (const char *pathP, 
		 char *driveP, char *dirP, char *nameP, char *extP) {

	register char   *pB;
	register int    Wrk;
	int     Ret;
	char    buf[MAXPATH+2];

// Set all string to default value zero
	Ret = 0;
	if (driveP) 	*driveP = 0;
	if (dirP)	*dirP = 0;
	if (nameP)	*nameP = 0;
	if (extP)	*extP = 0;

// Copy filename into template up to MAXPATH characters
	pB = buf;
	while (*pathP == ' ')
		pathP++;
	if ((Wrk = strlen(pathP)) > MAXPATH)
		Wrk = MAXPATH;
	*pB++ = 0;
	strncpy(pB, pathP, Wrk);
	*(pB += Wrk) = 0;

// Split the filename and fill corresponding nonzero pointers
	Wrk = 0;
	for (; ; ) {
		switch (*--pB) {
		case '.'  :
			if (!Wrk && (*(pB+1) == '\0'))
				Wrk = DotFound(pB);
			if ((!Wrk) && ((Ret & EXTENSION) == 0)) {
				Ret |= EXTENSION;
				CopyIt(extP, pB, MAXEXT - 1);
				*pB = 0;
			}
			continue;
		case ':'  :
			if (pB != &buf[2])
				continue;
		case '\0' :
			if (Wrk) {
				if (*++pB)
					Ret |= DIRECTORY;
				CopyIt(dirP, pB, MAXDIR - 1);
				*pB-- = 0;
				break;
			}
		case '/'  :
		case '\\' :
			if (!Wrk) {
				Wrk++;
				if (*++pB)
					Ret |= FILENAME;
				CopyIt(nameP, pB, MAXFILE - 1);
				*pB-- = 0;
				if (*pB == 0 || (*pB == ':' && pB == &buf[2]))
					break;
			}
			continue;
		case '*'  :
		case '?'  :
			if (!Wrk)
				Ret |= WILDCARDS;
		default :
			continue;
		}
		break;
	}
	if (*pB == ':') {
		if (buf[1])
			Ret |= DRIVE;
		CopyIt(driveP, &buf[1], MAXDRIVE - 1);
	}
	return (Ret);
}
