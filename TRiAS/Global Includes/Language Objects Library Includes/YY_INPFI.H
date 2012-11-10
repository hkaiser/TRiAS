
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_inpfi.h
//  
//  FILE DESCRIPTION:     header file with the input file object class,
//                        declarations specific to reading from a file
//                        using read() calls.
//  
//  CLASS HIERARCHY:
//
//         +----------------------+          +----------------------+
//         |        input         | -------> |     buffer class     |
//         | generic base class   | links to |      (yy_buf.h)      |
//         +----------------------+          +----------------------+
//                   | derives      
//                   |
//         +--------------------------------------------------------+
//         |                  |                  |                  |
// +---------------+ +----------------+ +----------------+ +----------------+
// |  input file   | |  input stream  | |   input getc   | |  input string  |
// |     class     | |     class      | |     class      | |     class      |
// | (yy_inpfi.h)  | |  (yy_inpst.h)  | |  (yy_inpge.h)  | |   (yy_inp.h)   |
// +---------------+ +----------------+ +----------------+ +----------------+
//         |
// +-----------------+
// |   input file    |
// | with signatures |
// |  (yy_signc.h)   |
// +-----------------+
//        
//  MODIFICATION HISTORY:
//  
//    08/27/97   bz/cc    changed open, close, read, lseek, tell to yy_open
//                        et. al. so that C++ open will work with Microsoft.
//                        Also conditionally defined O_RDONLY et. al. for
//			  Solaris systems.
//    07/07/97   bz/cc    conditionalized to include io.h and tell()
//			  to handle AIX.
//    03/25/96   bz/cc    added non-suffix and path versions of inp_is_file.
//    05/05/94   cc       added conditional define of O_RDONLY for merging 
//                        Solaris sources.
//    04/06/94   bz       added yy_inp_cur_offset() and relatives.  Also
//                        added an open mode on yy_inp_is_file().
//    09/29/93   cc       re-added yy_extern_wrapper_reqd_ ifdefs.
//                        These ifdefs are for systems like Glockenspiel
//                        which have C header files with a C++ compiler.
//    04/19/93   bz/cc    native C++ rewrite of input (file) object.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_inp_file_h_
#define yy_inp_file_h_

#include "yy_inp.h"

#ifdef yy_extern_wrapper_reqd_
extern "C" {
#endif /* yy_extern_wrapper_reqd_ */

#ifdef yy_systypes_ok_
#include <sys/types.h>
#endif /* yy_systypes_ok_ */

#ifdef yy_sys5_files_
#include <fcntl.h>
#include <sys/stat.h>
#ifdef yy_io_h_ok_
#include <io.h>
#endif /* yy_io_h_ok_ */
#else /* yy_sys5_files_ */
#include <sys/file.h>
#endif /* yy_sys5_files_ */

#ifdef yy_prefix_file_funcs_
#ifndef _O_APPEND
#define _O_APPEND 0
#endif
#ifndef _O_BINARY
#define _O_BINARY 0
#endif
#ifndef _O_CREAT
#define _O_CREAT 0
#endif
#ifndef _O_EXCL
#define _O_EXCL 0
#endif
#ifndef _O_RDONLY
#define _O_RDONLY 0
#endif
#ifndef _O_RDWR
#define _O_RDWR 0
#endif
#ifndef _O_TEXT
#define _O_TEXT 0
#endif
#ifndef _O_TRUNC
#define _O_TRUNC 0
#endif
#ifndef _O_WRONLY
#define _O_WRONLY 0
#endif
#else /* yy_prefix_file_funcs_ */
#ifndef O_APPEND
#define O_APPEND 0
#endif
#ifndef O_BINARY
#define O_BINARY 0
#endif
#ifndef O_CREAT
#define O_CREAT 0
#endif
#ifndef O_EXCL
#define O_EXCL 0
#endif
#ifndef O_RDONLY
#define O_RDONLY 0
#endif
#ifndef O_RDWR
#define O_RDWR 0
#endif
#ifndef O_TEXT
#define O_TEXT 0
#endif
#ifndef O_TRUNC
#define O_TRUNC 0
#endif
#ifndef O_WRONLY
#define O_WRONLY 0
#endif
#endif /* yy_prefix_file_funcs_ */

#ifdef yy_extern_wrapper_reqd_
}
#endif /* yy_extern_wrapper_reqd_ */

//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_inp_file_ptr    is a typedef which defines a pointer to an input 
//                     file object which processes input from a file
//                     using read().
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_inp_file_obj   *yy_inp_file_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  yy_stdin_handle_    is the file number for stdin when open/read calls are
//                      used.
//
//////////////////////////////////////////////////////////////////////////////

#define yy_stdin_handle_              0


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_inp_file_obj
//
//  The yy_inp_file_obj is the file implementation class for the Yacc++
//  input object.  It lexes and parses from file input.  Each input file is
//  associated with one input file object.  The input file object uses
//  calls to read().  The read function is a system level input function
//  which does minimal buffering.  Yacc++ buffers the input from
//  read in the buffer provided by the input file object.
//
//  PUBLIC FUNCTIONS:
//
//  yy_inp_file_obj()       constructors for an input file object.
//                                  
//  ~yy_inp_file_obj()      destructor for an input file object.
//
//  yy_inp_buf_fill()       refills the input buffer by reading from the
//                          file using read().
//
//  yy_inp_close()          closes the file and de-allocates its buffer.
//                          It optionally frees the filename.
//
//  yy_inp_cur_offset()     gets the offset from the beginning of this 
//                          input of the character being lexed.
//
//  yy_inp_cur_offset_as_filepos() 
//                          gets the offset from the beginning of this 
//                          input of the character being lexed.
//
//  yy_inp_dmp()            displays the values of the input file object
//                          data members.
//
//  yy_inp_is_file()        opens the input file specified by the filename 
//                          and the list of suffixes.
//
//  yy_inp_is_stdin()       uses stdin as the input file.
//
//  yy_inp_rewind()         rewinds to the beginning of the bottom file on
//                          the include file stack.
//
//  yy_loc_print_self()     displays the filename along with the line number
//                          as the location.
//
//  INTERNAL STATE:  
//
//  yy_file_num         is the file number (handle).
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_inp_file_obj : public yy_inp_obj {
    
 public:

    yy_inp_file_obj();

    yy_inp_file_obj(yy_err_ptr yy_this_err_ptr);

    yy_inp_file_obj(yy_inp_ptr yy_this_inp_ptr);

    virtual ~yy_inp_file_obj();

    virtual void yy_inp_buf_fill();

    virtual yy_boolean yy_inp_close(yy_boolean yy_free_the_filename);

    unsigned long yy_inp_cur_offset();

    inline long yy_inp_cur_offset_as_filepos();

    virtual void yy_inp_dmp(
        yy_err_ptr   yy_this_err_obj, 
        const char   *yy_dmp_title
        );

    virtual yy_boolean yy_inp_is_file(
        const char   *yy_filename,
        int          yy_open_mode = yy_O_RDONLY
        );

    virtual yy_boolean yy_inp_is_file(
        const char   *yy_filename,
        const char   *yy_suffixes[],
        int          yy_open_mode = yy_O_RDONLY
        );

    virtual yy_boolean yy_inp_is_file(
        const char   *yy_filename,
        const char   *yy_suffixes[],
        const char   *yy_paths[],
        int          yy_open_mode = yy_O_RDONLY
        );

    virtual yy_boolean yy_inp_is_stdin();

    virtual void yy_inp_rewind();

    virtual yy_boolean yy_loc_print_self(yy_err_ptr);
    
 protected:

    int                 yy_file_num;

    };  // yy_inp_file_obj



//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the input file object, defined
//  above.
//
//////////////////////////////////////////////////////////////////////////////

inline long yy_inp_file_obj::yy_inp_cur_offset_as_filepos()
{ 
    if (yy_file_num != -1) {
#ifdef yy_use_lseek_for_tell_
        return(yy_lseek(yy_file_num, 0, SEEK_CUR) - 
               (yy_this_buf_obj->yy_buf_end() -
                yy_this_buf_obj->yy_buf_tkn_end()));
#else
        return(yy_tell(yy_file_num) - 
               (yy_this_buf_obj->yy_buf_end() -
                yy_this_buf_obj->yy_buf_tkn_end()));
#endif
        }
    else {
        return(-1);
        }
}

#endif  /* yy_inp_file_h_ */
