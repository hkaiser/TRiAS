/*****************************************************************************
 *                                                                           *
 * grp.h                                                                     *
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
 * 	[1997/06/23  12:11:54  tbartley]
 */


#if !defined(_DOWNHILL_GRP_H)
#define _DOWNHILL_GRP_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include <sys/types.h>


/* Struct stuff **************************************************************/
struct group
{
	char* gr_name;
	char* gr_passwd;
	gid_t gr_gid;
	char* gr_mem[2];
};


#ifndef DOWNHILL_NO_FUNCTIONS
/* Prototype stuff ***********************************************************/
#if (_DOWNHILL_POSIX_SOURCE == 0)
struct group* getgrent(void);
void          setgrent(void);
void          endgrent(void);
#endif
struct group* getgrgid(gid_t group_Id);
struct group* getgrnam(char* group_Name);

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_GRP_H */
