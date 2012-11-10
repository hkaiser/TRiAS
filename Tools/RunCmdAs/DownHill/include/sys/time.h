/*****************************************************************************
 *                                                                           *
 * sys/time.h                                                                *
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
 * 	[1997/06/23  12:12:37  tbartley]
 *
 * 	Allow provision of an external system socket header file.
 * 	[1997/05/26  07:42:49  tbartley]
 */


#if !defined(_DOWNHILL_SYS_TIME_H)
#define _DOWNHILL_SYS_TIME_H


/* Include stuff *************************************************************/
#ifdef DOWNHILL_INCLUDE_SYS_SOCKET
#include DOWNHILL_INCLUDE_SYS_SOCKET
#else
#ifdef DOWNHILL_USE_WINSOCK2
#include <winsock2.h>
#else
#include <winsock.h>
#endif
#endif
#include <time.h>


/* Struct stuff **************************************************************/
struct timezone
{
	int tz_minuteswest;
	int tz_dsttime;
};


#ifndef	DOWNHILL_NO_FUNCTIONS

/* Prototype stuff ***********************************************************/
int gettimeofday(struct timeval* time_Info,struct timezone* timezone_Info);

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif /* _DOWNHILL_SYS_TIME_H */
