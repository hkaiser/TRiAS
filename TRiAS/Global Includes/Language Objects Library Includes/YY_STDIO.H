
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_stdio.h
//  
//  FILE DESCRIPTION:     insert file with ANSI i/o macros and prototypes.
//  
//  MODIFICATION HISTORY:
//  
//    09/11/97   bz       support for ANSI C++ headers for cstdio.
//    08/27/97   bz/cc    changed open, close, read, lseek, tell to yy_open
//                        et. al. so that C++ open will work with Microsoft.
//    07/07/97   bz/cc    added unistd.h for numerous UNIX systems. 
//    06/12/96   bz       added _tell to the list of prefixed function
//                        names for c8.
//    10/08/92   bz       added yy_prefix_file_funcs_ to get C7 ANSI
//                        compatible names for UNIX file functions.  They
//                        changed at 7.0 to have _ prefix. 
//    08/31/92   cc       re-added yy_extern_wrapper_reqd_ ifdefs.
//                        These ifdefs are for systems like Glockenspiel
//                        which have C header files with a C++ compiler.
//    08/31/92   cc       added prototype for lseek to support SCO Unix.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//  --------------------------------------------------------------------------
//
//  "yy_stdio.h" contains the manifest constants and prototypes which should
//  be found in a standard confroming ANSI C <stdio.h> header file, but may
//  be missing if the header files are not standard conforming.  This file
//  also declares the equivalent "Unix" functions.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_stdio_h_
#define yy_stdio_h_

#ifndef yy_ansi_h_
#include "yy_ansi.h"
#endif

#include "yy_stdef.h"

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_use_ansicxx_hdrs_
#include <cstdio>
#else
#include <stdio.h>
#endif /* yy_use_ansicxx_hdrs_ */

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

#include "yy_starg.h"

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_unistd_ok_
#include <unistd.h>
#endif /* yy_unistd_ok_ */

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_file_decl_needed_
typedef struct yy_FILE_ FILE;
#endif

#ifdef yy_define_null_
#undef NULL
#endif /* yy_define_null_ */

#ifndef NULL
#ifdef yy_null_not_cast_
#ifdef yy_null_l_suffix_
#define NULL    (0L)
#else
#define NULL    (0)
#endif
#else
#ifdef yy_null_l_suffix_
#define NULL    ((yy_void_ptr)0L)
#else
#define NULL    ((yy_void_ptr)0)
#endif
#endif
#endif

#ifndef EOF
#define EOF    (-1)
#endif

extern "C" {

#ifdef yy_fopen_decl_needed_
FILE *fopen(
    const char *yy_filename,
    const char *yy_mode
    );
#endif

#ifdef yy_prefix_file_funcs_
#define yy_close _close
#define yy_lseek _lseek
#define yy_open _open
#define yy_read _read
#define yy_tell _tell
#define yy_O_APPEND _O_APPEND
#define yy_O_BINARY _O_BINARY
#define yy_O_CREAT _O_CREAT
#define yy_O_EXCL _O_EXCL
#define yy_O_RDONLY _O_RDONLY
#define yy_O_RDWR _O_RDWR
#define yy_O_TEXT _O_TEXT
#define yy_O_TRUNC _O_TRUNC
#define yy_O_WRONLY _O_WRONLY
#else /* yy_prefix_file_funcs_ */
#define yy_close close
#define yy_lseek lseek
#define yy_open open
#define yy_read read
#define yy_tell tell
#define yy_O_APPEND O_APPEND
#define yy_O_BINARY O_BINARY
#define yy_O_CREAT O_CREAT
#define yy_O_EXCL O_EXCL
#define yy_O_RDONLY O_RDONLY
#define yy_O_RDWR O_RDWR
#define yy_O_TEXT O_TEXT
#define yy_O_TRUNC O_TRUNC
#define yy_O_WRONLY O_WRONLY
#endif /* yy_prefix_file_funcs_ */

#ifdef yy_open_decl_needed_
int yy_open(
    const char *yy_filename,
    int yy_flags,
    /* [int yy_mode] */ ...
    );
#endif

#ifdef yy_freopen_decl_needed_
FILE *freopen(
    const char *yy_filename,
    const char *yy_mode,
    FILE *yy_stream
    );
#endif

#ifdef yy_fflush_decl_needed_
int fflush(
    FILE *yy_stream
    );
#endif

#ifdef yy_fclose_decl_needed_
int fclose(
    FILE *yy_stream
    );
#endif

#ifdef yy_close_decl_needed_
int yy_close(
    int yy_filenum
    );
#endif

#ifdef yy_remove_decl_needed_
int remove(
    const char *yy_filename
    );
#endif

#ifdef yy_rename_decl_needed_
int rename(
    const char *yy_filename,
    const char *yy_newname
    );
#endif

#ifdef yy_tmpfile_decl_needed_
FILE *tmpfile(
    void
    );
#endif

#ifdef yy_tmpnam_decl_needed_
char *tmpnam(
    char *yy_tmpname
    );
#endif

#ifdef yy_setvbuf_decl_needed_
int setvbuf(
    FILE *yy_stream,
    char *yy_buf,
    int yy_mode,            
    size_t yy_buf_size
    );
#endif

#ifdef yy_setbuf_decl_needed_
int setbuf(
    FILE *yy_stream,
    char *yy_buf
    );
#endif

#ifdef yy_fprintf_decl_needed_
int fprintf(
    FILE *yy_stream,
    const char *yy_format,
    ...
    );
#endif

#ifdef yy_printf_decl_needed_
int printf(
    const char *yy_format,
    ...
    );
#endif

#ifdef yy_sprintf_decl_needed_
int sprintf(
    char *yy_target,
    const char *yy_format,
    ...
    );
#endif

#ifdef yy_vfprintf_decl_needed_
int vfprintf(
    FILE *yy_stream,
    const char *yy_format,
    va_list arg
    );
#endif

#ifdef yy_vprintf_decl_needed_
int vprintf(
    const char *yy_format,
    va_list arg
    );
#endif

#ifdef yy_vsprintf_decl_needed_
int vsprintf(
    char *yy_target,
    const char *yy_format,
    va_list arg
    );
#endif

#ifdef yy_fscanf_decl_needed_
int fscanf(
    FILE *yy_stream,
    const char *yy_format,
    ...
    );
#endif

#ifdef yy_scanf_decl_needed_
int scanf(
    const char *yy_format,
    ...
    );
#endif

#ifdef yy_sscanf_decl_needed_
int sscanf(
    char *yy_target,
    const char *yy_format,
    ...
    );
#endif

#ifdef yy_fgetc_decl_needed_
int fgetc(
    FILE *yy_stream
    );
#endif

#ifdef yy_fgets_decl_needed_
char *fgets(
    char *yy_to_fill,
    int yy_size,
    FILE *yy_stream
    );
#endif

#ifdef yy_fputc_decl_needed_
int fputc(
    int yy_char,
    FILE *yy_stream
    );
#endif

#ifdef yy_fputs_decl_needed_
char *fputs(
    char *yy_to_put,
    FILE *yy_stream
    );
#endif

#ifdef yy_getc_decl_needed_
int getc(
    FILE *yy_stream
    );
#endif

#ifdef yy_getchar_decl_needed_
int getchar(
    void
    );
#endif

#ifdef yy_gets_decl_needed_
char *gets(
    char *yy_to_fill,
    int yy_size,
    FILE *yy_stream
    );
#endif

#ifdef yy_putc_decl_needed_
int putc(
    int yy_char,
    FILE *yy_stream
    );
#endif

#ifdef yy_putchar_decl_needed_
int putchar(
    int yy_char
    );
#endif

#ifdef yy_puts_decl_needed_
char *puts(
    char *yy_to_put,
    FILE *yy_stream
    );
#endif

#ifdef yy_ungetc_decl_needed_
int ungetc(
    int yy_char,
    FILE *yy_stream
    );
#endif

#ifdef yy_read_decl_needed_
int yy_read(
    int         file_number,
    char        *buffer,
    size_t      size
    );
#endif

#ifdef yy_filbuf_decl_needed_
int _filbuf(
    FILE *yy_stream
    );
#endif

#ifdef yy_flsbuf_decl_needed_
int _flsbuf(
    FILE *yy_stream
    );
#endif

#ifdef yy_lseek_decl_needed_
long yy_lseek( 
    int, 
    long, 
    int 
    );
#endif

#ifdef yy_tell_decl_needed_
long yy_tell(
    int
    );
#endif

}

#endif
