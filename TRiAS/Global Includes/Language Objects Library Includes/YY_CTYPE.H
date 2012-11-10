
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_ctype.h
//  
//  FILE DESCRIPTION:     insert file with ANSI character type macros 
//                        and prototypes.
//  
//  MODIFICATION HISTORY:
//  
//    09/29/93   cc       re-added yy_extern_wrapper_reqd_ ifdefs.
//                        These ifdefs are for systems like Glockenspiel
//                        which have C header files with a C++ compiler.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//  
//  ------------------------------------------------------------------------
//  
//  "yy_ctype.h" contains the manifest constants and prototypes which should
//  be found in a standard confroming ANSI C <ctype.h> header file, but may
//  be missing if the header files are not standard conforming.
//
//////////////////////////////////////////////////////////////////////////////


#ifndef yy_ctype_h_
#define yy_ctype_h_

#ifndef yy_ansi_h_
#include "yy_ansi.h"
#endif

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_ctype_ok_
#include <ctype.h>
#endif /* yy_ctype_ok_ */

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

#endif
