 
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1994, Compiler Resources, Inc.
//
//  FILENAME:             yy_errgn.h
//
//  FILE DESCRIPTION:     header file with generic error object declarations
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
//              +---------------+----------------+----------------+
//              |               |                |                |
//              |   +------------------------+   |                |
//              |   |    error reporting     |   |                |
//              |   |  stream implementation |   |                |
//              |   |     (see yy_errst.h    |   |                |
//              |   +------------------------+   |                |
//              |               |                |                |
//  +-----------------------+   |   +------------------------+ +------------------+       
//  |   error reporting     |   |   |    error reporting     | |  error reporting |
//  |  MFC implementation   |   |   |   OWL implementation   | |  generic         |
//  +-----------------------+   |   |    (see yy_errow.h)    | |  implementation  |
//                              |   +------------------------+ +------------------+
//                              |
//                              | derives
//                  +------------------------+
//                  |    error reporting     |
//                  | default implementation |
//                  |    (see yy_errst.h)    |
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
//                  |    (see yy_errst.h)    |
//                  +------------------------+
//                             | derives
//                  +------------------------+
//                  |     error message      |
//                  |  cache implementation  |
//                  |    with signatures     |
//                  |    (see yy_signc.h)    |
//                  +------------------------+
//
//  MODIFICATION HISTORY:
//
//    04/14/93   bz       initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_errgn_h_
#define yy_errgn_h_

#include "yy_err.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_err_tf_ptr      is a typedef which defines a pointer to an TRIASFRM
//                      error reporting object for Windows.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_err_proc_obj    *yy_err_proc_ptr;
typedef int (yy_pascal * yy_err_procedure) (const char *yy_error);

//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_err_proc_obj
//
//  The yy_err_proc_obj is the error class which provides error reporting
//  to a user provided function. It is derived
//  from the generic class and overrides the yy_err_puts() function which
//  actually calls the user function the display.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_err_puts()      converts newlines or carriage returns to carriage
//                     return/line feed pairs and then displays a string
//                     onto the error window.
//
//  INTERNAL STATE:
//
//  yy_err_proc        is the pointer to the user provided function 
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_err_proc_obj : public yy_err_gen_obj {

 public:

    yy_err_proc_obj(
	yy_err_procedure    yy_new_err_proc,
        yy_errmsg_dflt_ptr  yy_new_err_tbl = NULL,
        int                 yy_new_err_tbl_max = 0,
        yy_synamsg_dflt_ptr yy_new_syna_tbl = NULL,
        int                 yy_new_syna_tbl_max = 0
        );  

    virtual ~yy_err_proc_obj();
    
    virtual yy_err_procedure yy_err_output_procedure()
        { return(yy_err_proc); }

    virtual yy_err_procedure yy_err_output_procedure(yy_err_procedure yy_new_value)
        { 
        yy_err_procedure yy_old_value = yy_err_proc;
        
        	return (yy_err_proc = yy_new_value); 
        }

    virtual int yy_err_puts(const char *yy_text);

 protected:

    yy_err_procedure	    yy_err_proc;
	string yy_out_string;
    };  // yy_err_proc_obj
    
#endif /* yy_errgn_h_ */
