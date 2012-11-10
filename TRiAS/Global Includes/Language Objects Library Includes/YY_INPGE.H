
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_inpge.h
//  
//  FILE DESCRIPTION:     header file with the input object class 
//                        declarations specific to reading with getc().
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
//    12/28/98   bz/cc	  changed yy_inp_cur_fp to return reference so that
//			  FLEX assignments to yyin will compile.
//    07/07/97   bz/cc    added yy_far to FILE * for Win16.
//    03/25/96   bz/cc    added non-suffix and path versions of inp_is_file.
//    04/06/94   bz       added yy_inp_cur_offset() and relatives.
//    12/10/93   bz/cc    added yy_inp_cur_fp() for LEX lexers.
//    04/19/93   bz/cc    native C++ rewrite of input (file) object.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_inp_getc_h_
#define yy_inp_getc_h_

#include "yy_inp.h"
#include "yy_stdio.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_inp_getc_ptr     is a typedef which defines a pointer to an input 
//                      object which processes input from a file using getc().
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_inp_getc_obj   *yy_inp_getc_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_inp_getc_obj
//
//  The yy_inp_getc_obj is the getc implementation class for the Yacc++
//  input object.  It lexes and parses file input using getc() calls.  Each 
//  input file is associated with one input getc object.  The getc() function
//  is an ANSI C library input function which gets one character at a time
//  from an input buffer.  
//
//  PUBLIC FUNCTIONS:
//
//  yy_inp_getc_obj()       constructors for an input getc object.
//                                  
//  ~yy_inp_getc_obj()      destructor for an input getc object.
//
//  yy_inp_buf_fill()       refills the input buffer by reading from the
//                          file.  Note that only one character is obtained
//                          per call.
//
//  yy_inp_buf_restore      redefines the restoring of a saved input buffer.  
//
//  yy_inp_buf_save         redefines the saving of the input buffer.
//
//  yy_inp_close()          closes the file and de-allocates its buffer.
//                          It optionally frees the filename.
//
//  yy_inp_cur_fp()         gets the current file pointer.
//
//  yy_inp_cur_offset()     gets the offset from the beginning of this 
//                          input of the character being lexed.
//
//  yy_inp_cur_offset_as_getcpos() 
//                          gets the offset from the beginning of this 
//                          input of the character being lexed.
//
//  yy_inp_dmp()            displays the values of the input getc object
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
//  yy_fp               is the file pointer (to a C library FILE object).
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_inp_getc_obj : public yy_inp_obj {
    
 public:

    yy_inp_getc_obj();

    yy_inp_getc_obj(yy_err_ptr yy_this_err_ptr);

    yy_inp_getc_obj(yy_inp_ptr yy_this_inp_ptr);

    virtual ~yy_inp_getc_obj();

    virtual void yy_inp_buf_fill();

    virtual void yy_inp_buf_restore();

    virtual void yy_inp_buf_save();
    
    virtual yy_boolean yy_inp_close(yy_boolean yy_free_the_filename);

    virtual void yy_inp_dmp(
        yy_err_ptr   yy_this_err_obj, 
        const char   *yy_dmp_title
        );

    inline FILE yy_far *&yy_inp_cur_fp();

    unsigned long yy_inp_cur_offset();

    inline long yy_inp_cur_offset_as_getcpos();

    virtual yy_boolean yy_inp_is_file(
        const char   *yy_filename
        );

    virtual yy_boolean yy_inp_is_file(
        const char   *yy_filename,
        const char   *yy_suffixes[]
        );

    virtual yy_boolean yy_inp_is_file(
        const char   *yy_filename,
        const char   *yy_suffixes[],
        const char   *yy_paths[]
        );

    virtual yy_boolean yy_inp_is_stdin();

    virtual void yy_inp_rewind();

    virtual yy_boolean yy_loc_print_self(yy_err_ptr);
    
 protected:

    FILE yy_far             *yy_fp;
 
    };  // yy_inp_getc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the input getc object, defined
//  above.
//
//////////////////////////////////////////////////////////////////////////////

inline long yy_inp_getc_obj::yy_inp_cur_offset_as_getcpos()
{ 
    if (yy_fp) {
        return(ftell(yy_fp) - 
               (yy_this_buf_obj->yy_buf_end() -
                yy_this_buf_obj->yy_buf_tkn_end()));
        }
    else {
        return(-1);
        }
}

inline FILE yy_far *&yy_inp_getc_obj::yy_inp_cur_fp()
    {
        return(yy_fp);
    }


//////////////////////////////////////////////////////////////////////////////
//
//  COMPATIBILITY MACROS:
//
//  For backward compatibility, the following macros preserve the old names.
//
//  yy_cur_fp               ==> calls yy_inp_cur_fp
//
//////////////////////////////////////////////////////////////////////////////

#define yy_cur_fp           yy_inp_cur_fp

#endif  /* yy_inp_getc_h_ */

