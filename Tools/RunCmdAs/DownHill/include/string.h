/*****************************************************************************
 *                                                                           *
 * string.h                                                                 *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/

#if !defined(_DOWNHILL_STRING_H)
#define _DOWNHILL_STRING_H


/* Include stuff *************************************************************/
#include "DOWNHILL/DH_POSIX.H"
#include "DOWNHILL/DH_INC.H"
#include _DOWNHILL_INCLUDE_DIR/string.h>

/* Define stuff **************************************************************/
#if defined(_MSC_VER) && !defined(_NTSDK)
#  define strdup _strdup
#endif

#endif /* _DOWNHILL_STRING_H */
