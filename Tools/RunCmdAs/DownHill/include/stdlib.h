/*****************************************************************************
 *                                                                           *
 * stdlib.h                                                                  *
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
 * 	[1997/06/23  12:12:05  tbartley]
 *
 * 	Add uio calls: readv, writev.
 * 	Make libdownhill installable.
 * 	Put include guards around stdlib.h.
 * 	[1997/05/21  07:35:49  tbartley]
 * 
 * 	Conditionalise the definition of MAXPATHLEN. ON WIN32 _MAX_PATH is only
 * 	(at most) 260. Since we have to interoperate with machines where the
 * 	path may be much longer than that and also becuase MAXPATHLEN has been
 * 	used throughout ODE as a generally large buffer size we allow this
 * 	macro to be predefined. We set it in Makeconf to 2048.
 * 	[1997/05/10  02:44:34  tbartley]
 */
#ifndef _DOWNHILL_STDLIB_H
#define _DOWNHILL_STDLIB_H

/* Include stuff *************************************************************/
#include "DOWNHILL/DH_INC.H"
#include _DOWNHILL_INCLUDE_DIR/stdlib.h>
#include <sys/unistd.h>
#include <malloc.h>

/* Define stuff **************************************************************/
#if defined(_MSC_VER) && !defined(_NTSDK)
#  define mktemp	_mktemp
#endif

#ifndef DOWNHILL_NO_FUNCTIONS

/* Prototype stuff ***********************************************************/
int   setenv(const char *, const char *, int);
void  unsetenv(const char *);
char* Downhill_Getenv(const char *);

/* Redefinition stuff ********************************************************/
#ifdef getenv
#undef getenv
#endif
#define getenv(name) Downhill_Getenv(name)

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_STDLIB_H */
