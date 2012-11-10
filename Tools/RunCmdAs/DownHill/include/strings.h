/*****************************************************************************
 *                                                                           *
 * strings.h                                                                 *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/
/*
 * HISTORY
 * 	Allow selection of macro definitions only.
 * 	That is, provide a compatibility layer that requires no library
 * 	functions only macro definitions. This is enabled by defining the
 * 	macro DOWNHILL_NO_FUNCTIONS.
 * 	[1997/06/23  12:12:07  tbartley]
 */


#if !defined(_DOWNHILL_STRINGS_H)
#define _DOWNHILL_STRINGS_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include <string.h>

/* Define stuff **************************************************************/
#if defined(_MSC_VER) && !defined(_NTSDK)
#  define strdup _strdup
#endif
#if (_DOWNHILL_POSIX_SOURCE == 0)
#  define strcasecmp	_stricmp
#  define strncasecmp	_strnicmp
#endif

#ifndef	DOWNHILL_NO_FUNCTIONS

/* Prototype stuff ***********************************************************/
#if (_DOWNHILL_POSIX_SOURCE == 0)
int   ffs(int bit_Bitmap);
char* index(const char* search_String,char search_Character);
char* rindex(const char* search_String,char search_Character);
#endif

#endif	/* DOWNHILL_NO_FUNCTIONS */


#endif /* _DOWNHILL_STRINGS_H */
