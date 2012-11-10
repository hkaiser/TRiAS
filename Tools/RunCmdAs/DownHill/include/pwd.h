/*****************************************************************************
 *                                                                           *
 * pwd.h                                                                     *
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
 * 	[1997/06/23  12:11:58  tbartley]
 */


#if !defined(_DOWNHILL_PWD_H)
#define _DOWNHILL_PWD_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include <sys/types.h>


/* Struct stuff **************************************************************/
struct passwd
{
	char* pw_name;
	char* pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	char* pw_gecos;
	char* pw_dir;
	char* pw_shell;
};


#ifndef DOWNHILL_NO_FUNCTIONS

/* Prototype stuff ***********************************************************/
#if (_DOWNHILL_POSIX_SOURCE == 0)
struct passwd* getpwent(void);
void           setpwent(void);
void           endpwent(void);
#endif
struct passwd* getpwuid(uid_t user_Id);
struct passwd* getpwnam(char* user_Name);

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_PWD_H */
