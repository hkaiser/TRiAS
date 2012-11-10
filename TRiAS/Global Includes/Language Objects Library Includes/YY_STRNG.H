
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_strng.h
//
//  FILE DESCRIPTION:     insert file with ANSI i/o macros and prototypes.
//
//  MODIFICATION HISTORY:
//
//    09/11/97   bz       support for ANSI C++ headers for cstring.
//    09/29/93   cc       re-added yy_extern_wrapper_reqd_ ifdefs.
//                        These ifdefs are for systems like Glockenspiel
//                        which have C header files with a C++ compiler.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//  --------------------------------------------------------------------------
//
//  "yy_strng.h" contains the manifest constants and prototypes which should
//  be found in a standard confroming ANSI C <string.h> header file, but may
//  be missing if the header files are not standard conforming.  This file
//  also declares the equivalent "Unix" functions.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_strng_h_
#define yy_strng_h_

#ifndef yy_ansi_h_
#include "yy_ansi.h"
#endif

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_string_ok_
#ifdef yy_use_ansicxx_hdrs_
#include <cstring>
#else
#include <string.h>
#endif /* yy_use_ansicxx_hdrs_ */
#endif

#ifdef yy_memory_hdr_
#include <memory.h>
#endif

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

extern "C" {

#ifdef yy_strcpy_decl_needed_
char *strcpy(
    char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strncpy_decl_needed_
char *strncpy(
    char *yy_target,
    const char *yy_source,
    size_t yy_size
    );
#endif

#ifdef yy_strcat_decl_needed_
char *strcat(
    char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strncat_decl_needed_
char *strncat(
    char *yy_target,
    const char *yy_source,
    size_t yy_size
    );
#endif

#ifdef yy_strcmp_decl_needed_
char *strcmp(
    const char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strncmp_decl_needed_
char *strncmp(
    const char *yy_target,
    const char *yy_source,
    size_t yy_size
    );
#endif

#ifdef yy_strchr_decl_needed_
char *strchr(
    const char *yy_target,
    int yy_look_for
    );
#endif

#ifdef yy_strnchr_decl_needed_
char *strrchr(
    const char *yy_target,
    int yy_look_for
    );
#endif

#ifdef yy_strspn_decl_needed_
size_t strspn(
    const char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strcspn_decl_needed_
size_t strcspn(
    const char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strpbrk_decl_needed_
char *strpbrk(
    const char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strstr_decl_needed_
char *strstr(
    const char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_strlen_decl_needed_
size_t strlen(
    const char *yy_source
    );
#endif

#ifdef yy_strerror_decl_needed_
char *strerror(
    int yy_errno
    );
#endif

#ifdef yy_strtok_decl_needed_
char *strtok(
    char *yy_target,
    const char *yy_source
    );
#endif

#ifdef yy_memcpy_decl_needed_
yy_void_ptr memcpy(
    yy_void_ptr yy_target,
    const yy_void_ptr yy_source,
    size_t yy_size
    );
#endif

#ifdef yy_memmove_decl_needed_
yy_void_ptr memmove(
    yy_void_ptr yy_target,
    const yy_void_ptr yy_source,
    size_t yy_size
    );
#endif

#ifdef yy_memcmp_decl_needed_
int memcmp(
    yy_void_ptr yy_target,
    const yy_void_ptr yy_source,
    size_t yy_size
    );
#endif

#ifdef yy_memchr_decl_needed_
yy_void_ptr memchr(
    const yy_void_ptr yy_target,
    int yy_look_for,
    size_t yy_size
    );
#endif

#ifdef yy_memset_decl_needed_
yy_void_ptr memset(
    yy_void_ptr yy_target,
    int yy_look_for,
    size_t yy_size
    );
#endif

}

#endif
