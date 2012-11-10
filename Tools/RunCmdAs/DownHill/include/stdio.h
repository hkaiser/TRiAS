/*****************************************************************************
 *                                                                           *
 * stdio.h                                                                   *
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
 * 	[1997/06/23  12:11:59  tbartley]
 */

#if !defined(_DOWNHILL_STDIO_H)
#define _DOWNHILL_STDIO_H

/* Include stuff *************************************************************/
#include "DOWNHILL/DH_INC.H"
#include _DOWNHILL_INCLUDE_DIR/stdio.h>
#include _DOWNHILL_INCLUDE_DIR/io.h>
#include <sys/unistd.h>
#include <sys/errno.h>

/* Define stuff **************************************************************/
#if defined(_MSC_VER) && !defined(_NTSDK)
#  define fcloseall _fcloseall
#  define fdopen    _fdopen
#  define fgetchar  _fgetchar
#  define fileno    _fileno
#  define flushall  _flushall
#  define fputchar  _fputchar
#  define getw      _getw
#  define pclose    _pclose
#  define popen	    _popen
#  define putw      _putw
#  define rmtmp     _rmtmp
#  define tempnam   _tempnam
#endif

#ifndef	DOWNHILL_NO_FUNCTIONS

/* Redefinition stuff ********************************************************/
#ifdef rename
#undef rename
#endif
#define rename		Downhill_File_Rename
extern int		Downhill_File_Rename(const char* from, const char* to);

#endif	/* DOWNHILL_NO_FUNCTIONS */

#endif
