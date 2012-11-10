
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_starg.h
//
//  FILE DESCRIPTION:     insert file with ANSI i/o macros and prototypes.
//
//  MODIFICATION HISTORY:
//
//    09/11/97   bz       support for ANSI C++ headers for cstdarg.
//    09/29/93   cc       re-added yy_extern_wrapper_reqd_ ifdefs.
//                        These ifdefs are for systems like Glockenspiel
//                        which have C header files with a C++ compiler.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//  --------------------------------------------------------------------------
//
//  "yy_starg.h" contains the manifest constants and prototypes which should
//  be found in a standard confroming ANSI C <stdarg.h> header file, but may
//  be missing if the header files are not standard conforming.  This file
//  also declares the equivalent "Unix" functions.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_starg_h_
#define yy_starg_h_

#ifndef yy_ansi_h_
#include "yy_ansi.h"
#endif

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_stdarg_ok_
#ifdef yy_use_ansicxx_hdrs_
#include <cstdarg>
#else
#include <stdarg.h>
#endif /* yy_use_ansicxx_hdrs_ */
#else /* yy_stdarg_ok_ */
#include <varargs.h>
#endif /* yy_stdarg_ok_ */

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

#endif /* yy_starg_h_ */
