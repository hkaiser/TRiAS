/*****************************************************************************
 *                                                                           *
 * sys/utsname.h                                                             *
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
 * 	[1997/06/23  12:12:43  tbartley]
 */


#if !defined(_DOWNHILL_SYS_UTSNAME_H)
#define _DOWNHILL_SYS_UTSNAME_H


/* Include stuff *************************************************************/
#include <sys/param.h>


/* Struct stuff **************************************************************/

/* utsname struct ========================================================== */
struct utsname
{
	char sysname[64+1];
	char nodename[MAXHOSTNAMELEN+1];
	char version[64+1];
	char release[64+1];
	char machine[64+1];
	char idnumber[16+1];
};


#ifndef	DOWNHILL_NO_FUNCTIONS

/* Prototype stuff ***********************************************************/
int uname(struct utsname* utsname_Info);

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_SYS_UTSNAME_H */
