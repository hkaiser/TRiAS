/*****************************************************************************
 *                                                                           *
 * sys/param.c                                                               *
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
 * 	[1997/06/23  12:12:10  tbartley]
 *
 * 	Make definition of MAXPATHLEN conditional on a pre-existing definition
 * 	[1997/05/08  03:21:11  tbartley]
 */


#if !defined(_DOWNHILL_SYS_PARAM_H)
#define _DOWNHILL_SYS_PARAM_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include <stdlib.h>


/* Define stuff **************************************************************/
#if (_DOWNHILL_POSIX_SOURCE == 0)
#ifndef MAXPATHLEN
#  define MAXPATHLEN _MAX_PATH
#endif
#define MAXHOSTNAMELEN 64
#define howmany(x,y)   (((x)+((y)-1))/(y))
#define roundup(x,y)   ((((x)+((y)-1))/(y))*(y))
#endif

#ifndef DOWNHILL_NO_FUNCTIONS

/* Prototypes ****************************************************************/
void  Downhill_DOS_to_UNIX(char *);
void  Downhill_UNIX_to_DOS(char *);

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_SYS_PARAM_H */
