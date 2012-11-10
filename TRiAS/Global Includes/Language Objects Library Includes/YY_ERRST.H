
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_errst.h
//
//  FILE DESCRIPTION:     header file with error stream object declarations
//
//  CLASS HIERARCHY:
//
//                  +------------------------+
//                  |    error reporting     |
//                  |  abstract base class   |
//                  |    (see yy_err.h)      |
//                  +------------------------+
//                              | derives      
//                  +------------------------+
//                  |    error reporting     |
//                  | generic implementation |
//                  |    (see yy_err.h)      |
//                  +------------------------+
//                              | derives      
//              +---------------+----------------+
//              |               |                |
//              |   +------------------------+   |
//              |   |    error reporting     |   |
//              |   |  stream implementation |   |
//              |   +------------------------+   |
//              |               |                |
//  +-----------------------+   |   +------------------------+        
//  |   error reporting     |   |   |    error reporting     |
//  |  MFC implementation   |   |   |   OWL implementation   |
//  |   (see yy_errmf.h)    |   |   |    (see yy_errow.h)    |
//  +-----------------------+   |   +------------------------+
//                              |
//                              | derives
//                  +------------------------+
//                  |    error reporting     |
//                  | default implementation |
//                  +------------------------+
//                              | derives      
//                  +------------------------+
//                  |    error reporting     |
//                  | default implementation |
//                  |    with signatures     |
//                  |    (see yy_signc.h)    |
//                  +------------------------+
//
//
//                  +------------------------+
//                  |     error message      |
//                  |  abstract base class   |
//                  |     (see yy_err.h)     |
//                  +------------------------+
//                             | derives      
//                  +------------------------+
//                  |     error message      |
//                  | default implementation |
//                  |     (see yy_err.h)     |
//                  +------------------------+
//                             | derives
//                  +------------------------+
//                  |     error message      |
//                  |  cache implementation  |
//                  +------------------------+
//                             | derives
//                  +------------------------+
//                  |     error message      |
//                  |  cache implementation  |
//                  |    with signatures     |
//                  |    (see yy_signc.h)    |
//                  +------------------------+
//
//
//                  +------------------------+
//                  |     syntax assist      |
//                  |  abstract base class   |
//                  |     (see yy_err.h)     |
//                  +------------------------+
//                             | derives      
//                  +------------------------+
//                  |     syntax assist      |
//                  | default implementation |
//                  |     (see yy_err.h)     |
//                  +------------------------+
//                             | derives
//                  +------------------------+
//                  |     syntax assist      |
//                  |  cache implementation  |
//                  +------------------------+
//                             | derives
//                  +------------------------+
//                  |     syntax assist      |
//                  |  cache implementation  |
//                  |    with signatures     |
//                  |    (see yy_signc.h)    |
//                  +------------------------+
//
//
//  MODIFICATION HISTORY:
//
//    07/28/97   bz/cc    support for ANSI C++ headers. + 9/11 change
//    10/20/93   bz/cc    moved syntax assist messages into the error object.
//    04/09/93   bz       initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_errst_h_
#define yy_errst_h_

#ifdef yy_use_ansicxx_hdrs_
#include <fstream>
#include <iostream>
using namespace std;
#else
#include <fstream.h>
#include <iostream.h>
#endif /* yy_use_ansicxx_hdrs_ */

#include "yy_err.h"
#include "yy_stdio.h"
#include "yy_strng.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_err_stream_ptr   is a typedef which defines a pointer to a stream
//                      error reporting object.
//
//  yy_err_dflt_ptr     is a typedef which defines a pointer to a default
//                      error reporting object based on a C++ stream.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_err_stream_obj    *yy_err_stream_ptr;
typedef class yy_export yy_err_dflt_obj      *yy_err_dflt_ptr;

typedef class yy_export yy_errmsg_cache_obj  *yy_errmsg_cache_ptr;

typedef class yy_export yy_synamsg_cache_obj *yy_synamsg_cache_ptr;


//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_err_stream_obj
//
//  The yy_err_stream_obj is the error class which provides error reporting
//  to a C++ stream.  It is derived from the generic class and overrides
//  the yy_err_puts() function which actually does the display.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_err_exit()      displays the summary of how many times yy_err_report()
//                     was called for warnings and/or errors.  Exits the 
//                     application after displaying the summary.
//
//  yy_err_output_stream([ostream *])
//                     gets (or sets with an argument) the C++ stream
//                     where the errors will be displayed.
//
//  yy_err_puts()      displays a string onto the error output stream.
//
//  INTERNAL STATE:
//
//  yy_err_stream      is the C++ stream where the errors will be displayed.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_err_stream_obj : public yy_err_gen_obj {

 public:

    yy_err_stream_obj(
        yy_errmsg_dflt_ptr    yy_new_err_tbl = NULL,
        int                   yy_new_err_tbl_max = 0,
        yy_synamsg_dflt_ptr   yy_new_syna_tbl = NULL,
        int                   yy_new_syna_tbl_max = 0,
        ostream              *yy_stream = &cout
        );  

    virtual ~yy_err_stream_obj();
    
    virtual void yy_err_exit();
    
    virtual ostream *yy_err_output_stream()
        {
        return(yy_err_stream); 
        }

    virtual ostream *yy_err_output_stream(ostream *yy_new_value)
        {
        return(yy_err_stream = yy_new_value);             
        }
        
    virtual int yy_err_puts(
        const char *yy_text
        );

 protected:

    ostream     *yy_err_stream;

    };  // yy_err_stream_obj

    
//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_err_dflt_obj
//
//  The yy_err_dflt_obj is the default implementation class for the Yacc++
//  error reporting object.  It provides error reporting to a C++ stream.
//  It is derived from the stream class and overrides the yy_err_lookup()
//  function to provide support for looking up errors from a file, not
//  just a pre-compiled table.
// 
//  CONFIGURATION CONSTANTS:
//
//  yy_err_fmt_max_         maximum size of the error message format which
//                          can be read from an alternate errorfile.
//
//  PUBLIC FUNCTIONS:
//
//  yy_err_filename([char *])
//                          gets (or sets with an argument) the current
//                          alternate error file name.
//
//  yy_err_lookup_msg()     retrieves an error message by number by first
//                          looking in the error file and then in the error
//                          message table.
//
//  INTERNAL STATE:  
//
//  yy_cache_root           is a pointer to the root of the tree of error 
//                          message cache objects of the messages for errors 
//                          which have already been looked up.
//
//  yy_syna_cache_root      is a pointer to the root of the tree of syntax
//                          assist cache objects of the messages for syntax
//                          assists which have already been looked up.
//
//  yy_filename             is a pointer to the name of the alternate file 
//                          with the error messages the user wishes to use in 
//                          place of the default error messages built in to 
//                          the application.  The alternate errorfile name 
//                          may be specified with the -errorfile option.
//
//  yy_syna_filename        is a pointer to the name of the alternate file 
//                          with the syntax assists the user wishes to use in 
//                          place of the default syntax assists built in to 
//                          the application.  The alternate assistfile name 
//                          may be specified with the -assistfile option.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_err_dflt_obj : public yy_err_stream_obj {

 protected:

    enum yy_err_fmt_max_enum { 
        yy_err_fmt_max_ = 1024
        };
        
 public:

    yy_err_dflt_obj(
        yy_errmsg_dflt_ptr    yy_new_err_tbl = NULL,
        int                   yy_new_err_tbl_max = 0,
        yy_synamsg_dflt_ptr   yy_new_syna_tbl = NULL,
        int                   yy_new_syna_tbl_max = 0,
        ostream              *yy_stream = &cout
        );  

    virtual ~yy_err_dflt_obj();
    
    inline const char *yy_err_filename();

    inline const char *yy_err_filename(const char *yy_new_filename);

    inline const char *yy_err_syna_filename();

    inline const char *yy_err_syna_filename(const char *yy_new_filename);

    virtual yy_errmsg_ptr yy_err_lookup_msg(int yy_err_num);

    virtual yy_synamsg_ptr yy_err_lookup_syna_msg(int yy_syna_num);

    virtual int yy_err_puts(
        const char *yy_text
        );

 protected:

    yy_errmsg_cache_ptr     yy_cache_root;
    yy_synamsg_cache_ptr    yy_syna_cache_root;
    char                    *yy_filename;
    char                    *yy_syna_filename;
    
    };  // yy_err_dflt_obj
    

//////////////////////////////////////////////////////////////////////////////
// 
//  CLASS: yy_errmsg_cache_obj 
// 
//  The yy_errmsg_cache_obj is the error message object class with cached
//  error message lookup from a file or from an error table.
//
//  PUBLIC FUNCTIONS:
//
//  yy_errmsg_cache_obj()   constructors for cached error message objects.
//                                  
//  ~yy_errmsg_cache_obj()  destructor for a cached error message object.
//
//  INTERNAL STATE:  
//
//  yy_less_ptr         is a pointer to an error message cache object with
//                      a smaller error number.
//
//  yy_more_ptr         is a pointer to an error message cache object with
//                      a larger number.
//
//  yy_par_ptr          is a pointer to an error message cache object which
//                      is the parent to this object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_errmsg_cache_obj : public yy_errmsg_dflt_obj {

 public:

    yy_errmsg_cache_obj();
        
    yy_errmsg_cache_obj(
        int                     yy_errmsg_number, 
        int                     yy_errmsg_severity, 
        char                    *yy_errmsg_format,
        yy_errmsg_cache_ptr     yy_new_less_ptr,
        yy_errmsg_cache_ptr     yy_new_more_ptr,
        yy_errmsg_cache_ptr     yy_new_par_ptr
        );

    virtual ~yy_errmsg_cache_obj();

    virtual void yy_errmsg_cache_delete_all();
    
    inline yy_errmsg_cache_ptr yy_errmsg_less_ptr();
    
    inline yy_errmsg_cache_ptr yy_errmsg_less_ptr(
        yy_errmsg_cache_ptr yy_new_less_ptr);

    inline yy_errmsg_cache_ptr yy_errmsg_more_ptr();

    inline yy_errmsg_cache_ptr yy_errmsg_more_ptr(
        yy_errmsg_cache_ptr yy_new_more_ptr);

    inline yy_errmsg_cache_ptr yy_errmsg_parent_ptr();
    
    inline yy_errmsg_cache_ptr yy_errmsg_parent_ptr(
        yy_errmsg_cache_ptr yy_new_par_ptr);
        
 protected:

    yy_errmsg_cache_ptr    yy_less_ptr;
    yy_errmsg_cache_ptr    yy_more_ptr;
    yy_errmsg_cache_ptr    yy_par_ptr;

    };  // yy_errmsg_cache_obj

    
//////////////////////////////////////////////////////////////////////////////
// 
//  CLASS: yy_synamsg_cache_obj 
// 
//  The yy_synamsg_cache_obj is the error message object class with cached
//  error message lookup from a file or from an error table.
//
//  PUBLIC FUNCTIONS:
//
//  yy_synamsg_cache_obj()   constructors for cached error message objects.
//                                  
//  ~yy_synamsg_cache_obj()  destructor for a cached error message object.
//
//  INTERNAL STATE:  
//
//  yy_less_ptr         is a pointer to an error message cache object with
//                      a smaller error number.
//
//  yy_more_ptr         is a pointer to an error message cache object with
//                      a larger number.
//
//  yy_par_ptr          is a pointer to an error message cache object which
//                      is the parent to this object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_synamsg_cache_obj : public yy_synamsg_dflt_obj {

 public:

    yy_synamsg_cache_obj();
        
    yy_synamsg_cache_obj(
        int                     yy_synamsg_number, 
        char                    *yy_synamsg_message,
        yy_synamsg_cache_ptr    yy_new_less_ptr,
        yy_synamsg_cache_ptr    yy_new_more_ptr,
        yy_synamsg_cache_ptr    yy_new_par_ptr
        );

    virtual ~yy_synamsg_cache_obj();

    virtual void yy_synamsg_cache_delete_all();
    
    inline yy_synamsg_cache_ptr yy_synamsg_less_ptr();
    
    inline yy_synamsg_cache_ptr yy_synamsg_less_ptr(
        yy_synamsg_cache_ptr yy_new_less_ptr);

    inline yy_synamsg_cache_ptr yy_synamsg_more_ptr();

    inline yy_synamsg_cache_ptr yy_synamsg_more_ptr(
        yy_synamsg_cache_ptr yy_new_more_ptr);

    inline yy_synamsg_cache_ptr yy_synamsg_parent_ptr();
    
    inline yy_synamsg_cache_ptr yy_synamsg_parent_ptr(
        yy_synamsg_cache_ptr yy_new_par_ptr);
        
 protected:

    yy_synamsg_cache_ptr    yy_less_ptr;
    yy_synamsg_cache_ptr    yy_more_ptr;
    yy_synamsg_cache_ptr    yy_par_ptr;

    };  // yy_synamsg_cache_obj

    
//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the error default object, defined
//  above.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_err_dflt_obj::yy_err_filename()
    { return(yy_filename); }

inline const char *yy_err_dflt_obj::yy_err_filename(
        const char *yy_new_filename)
    { 
        if (yy_filename != NULL) {
            delete [] yy_filename;
            }

        if (yy_new_filename != NULL) {
            yy_filename = new char[strlen(yy_new_filename) + 1];
            strcpy(yy_filename, yy_new_filename);
            }
        else {
            yy_filename = NULL;
            }

        return(yy_filename); 

    }

inline const char *yy_err_dflt_obj::yy_err_syna_filename()
    { return(yy_syna_filename); }

inline const char *yy_err_dflt_obj::yy_err_syna_filename(
        const char *yy_new_filename)
    { 
        if (yy_syna_filename != NULL) {
            delete [] yy_syna_filename;
            }

        if (yy_new_filename != NULL) {
            yy_syna_filename = new char[strlen(yy_new_filename) + 1];
            strcpy(yy_syna_filename, yy_new_filename);
            }
        else {
            yy_syna_filename = NULL;
            }

        return(yy_syna_filename); 
    }


inline yy_errmsg_cache_ptr yy_errmsg_cache_obj::yy_errmsg_less_ptr() 
    { return(yy_less_ptr); }

inline yy_errmsg_cache_ptr yy_errmsg_cache_obj::yy_errmsg_less_ptr(
    yy_errmsg_cache_ptr yy_new_less_ptr) 
    { return(yy_less_ptr = yy_new_less_ptr); }

inline yy_errmsg_cache_ptr yy_errmsg_cache_obj::yy_errmsg_more_ptr()
    { return(yy_more_ptr); }

inline yy_errmsg_cache_ptr yy_errmsg_cache_obj::yy_errmsg_more_ptr(
    yy_errmsg_cache_ptr yy_new_more_ptr) 
    { return(yy_more_ptr = yy_new_more_ptr); }

inline yy_errmsg_cache_ptr yy_errmsg_cache_obj::yy_errmsg_parent_ptr()
    { return(yy_par_ptr); }

inline yy_errmsg_cache_ptr yy_errmsg_cache_obj::yy_errmsg_parent_ptr(
    yy_errmsg_cache_ptr yy_new_par_ptr) 
    { return(yy_par_ptr = yy_new_par_ptr); }

inline yy_synamsg_cache_ptr yy_synamsg_cache_obj::yy_synamsg_less_ptr() 
    { return(yy_less_ptr); }

inline yy_synamsg_cache_ptr yy_synamsg_cache_obj::yy_synamsg_less_ptr(
    yy_synamsg_cache_ptr yy_new_less_ptr) 
    { return(yy_less_ptr = yy_new_less_ptr); }

inline yy_synamsg_cache_ptr yy_synamsg_cache_obj::yy_synamsg_more_ptr()
    { return(yy_more_ptr); }

inline yy_synamsg_cache_ptr yy_synamsg_cache_obj::yy_synamsg_more_ptr(
    yy_synamsg_cache_ptr yy_new_more_ptr) 
    { return(yy_more_ptr = yy_new_more_ptr); }

inline yy_synamsg_cache_ptr yy_synamsg_cache_obj::yy_synamsg_parent_ptr()
    { return(yy_par_ptr); }

inline yy_synamsg_cache_ptr yy_synamsg_cache_obj::yy_synamsg_parent_ptr(
    yy_synamsg_cache_ptr yy_new_par_ptr) 
    { return(yy_par_ptr = yy_new_par_ptr); }

#endif /* yy_errst_h_ */
