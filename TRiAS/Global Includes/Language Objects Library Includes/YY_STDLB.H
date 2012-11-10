
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_stdlb.h
//
//  FILE DESCRIPTION:     insert file with ANSI I/O macros and prototypes.
//
//  MODIFICATION HISTORY:
//
//    09/11/97   bz       support for ANSI C++ headers for stdlib.
//    09/29/93   cc       re-added yy_extern_wrapper_reqd_ ifdefs.
//                        These ifdefs are for systems like Glockenspiel
//                        which have C header files with a C++ compiler.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//  --------------------------------------------------------------------------
//
//  "yy_stdlb.h" contains the manifest constants and prototypes which should
//  be found in a standard confroming ANSI C <stdlib.h> header file, but may
//  be missing if the header files are not standard conforming.  This file
//  also declares the equivalent "Unix" functions.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_stdlb_h_
#define yy_stdlb_h_

#ifndef yy_ansi_h_
#include "yy_ansi.h"
#endif /* yy_ansi_h_ */

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_stdlib_ok_
#ifdef yy_use_ansicxx_hdrs_
#include <cstdlib>
#else
#include <stdlib.h>
#endif /* yy_use_ansicxx_hdrs_ */
#endif /* yy_stdlib_ok_ */

#ifdef yy_memory_hdr_
#include <memory.h>
#endif /* yy_memory_hdr_ */

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

extern "C" {

#ifdef yy_abs_decl_needed_
int abs(
    int yy_number
    );
#endif

#ifdef yy_labs_decl_needed_
long labs(
    long yy_number
    );
#endif

#ifdef yy_atof_decl_needed_
double atof(
    const char *yy_to_convert
    );
#endif

#ifdef yy_atoi_decl_needed_
int atoi(
    const char *yy_to_convert
    );
#endif

#ifdef yy_atol_decl_needed_
long atol(
    const char *yy_to_convert
    );
#endif

#ifdef yy_strtod_decl_needed_
double strtod(
    const char *yy_to_convert,
    char **yy_endp
    );
#endif

#ifdef yy_strtol_decl_needed_
long strtol(
    const char *yy_to_convert,
    char **yy_endp
    );
#endif

#ifdef yy_strtoul_decl_needed_
unsigned long strtoul(
    const char *yy_to_convert,
    char **yy_endp
    );
#endif

#ifdef yy_div_decl_needed_
int div(
    int yy_numerator,
    int yy_denominator
    );
#endif

#ifdef yy_ldiv_decl_needed_
long ldiv(
    long yy_numerator,
    long yy_denominator
    );
#endif

#ifdef yy_rand_decl_needed_
int rand(
    void
    );
#endif

#ifdef yy_srand_decl_needed_
void srand(
    unsigned int yy_seed
    );
#endif

#ifdef yy_abort_decl_needed_
void abort(
    void
    );
#endif

#ifdef yy_exit_decl_needed_
void exit(
    int yy_status
    );
#endif

#ifdef yy_atexit_decl_needed_
int atexit(
    void (*yy_exit_func)(void)
    );
#endif

#ifdef yy_system_decl_needed_
int system(
    const char *yy_command_line
    );
#endif

#ifdef yy_getenv_decl_needed_
char *getenv(
    const char *yy_env_name
    );
#endif

#ifdef yy_bsearch_decl_needed_
yy_void_ptr bsearch(
    const yy_void_ptr yy_key,
    const yy_void_ptr yy_base,
    size_t yy_num_elts,
    size_t yy_elt_size,
    int (*yy_cmp_func)(const yy_void_ptr yy_key_val, const yy_void_ptr yy_data_val)
    );
#endif

#ifdef yy_qsort_decl_needed_
yy_void_ptr qsort(
    const yy_void_ptr yy_base,
    size_t yy_num_elts,
    size_t yy_elt_size,
    int (*yy_cmp_func)(const yy_void_ptr yy_key_val, const yy_void_ptr yy_data_val)
    );
#endif

}

#endif
