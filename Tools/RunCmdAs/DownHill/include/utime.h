/*****************************************************************************
 *                                                                           *
 * utime.h                                                                   *
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
 * 	[1997/06/23  12:12:46  tbartley]
 */


#if !defined(_DOWNHILL_UTIME_H)
#define _DOWNHILL_UTIME_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include <windows.h>
#include <sys/utime.h>

/* Define stuff **************************************************************/
#if defined(_MSC_VER) && !defined(_NTSDK)
#  define utimbuf	_utimbuf
#  define utime		_utime
#endif

#ifndef DOWNHILL_NO_FUNCTIONS

/* Prototype stuff ***********************************************************/
#if (_DOWNHILL_POSIX_SOURCE == 0)
int utimes(char* file_Name,struct timeval* file_Time);
#endif

#endif	/* DOWNHILL_NO_FUNCTIONS */


#endif /* _DOWNHILL_UTIME_H */
