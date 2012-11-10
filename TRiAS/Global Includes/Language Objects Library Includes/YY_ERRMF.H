 
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1994, Compiler Resources, Inc.
//
//  FILENAME:             yy_errmf.h
//
//  FILE DESCRIPTION:     header file with mfc error object declarations
//                        for Windows using the Microsoft Foundation 
//                        Class Library
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
//              |   |     (see yy_errst.h    |   |
//              |   +------------------------+   |
//              |               |                |
//  +-----------------------+   |   +------------------------+        
//  |   error reporting     |   |   |    error reporting     |
//  |  MFC implementation   |   |   |   OWL implementation   |
//  +-----------------------+   |   |    (see yy_errow.h)    |
//                              |   +------------------------+
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

#ifndef yy_errmf_h_
#define yy_errmf_h_

#include <afxwin.h>

#include "yy_err.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_err_mfc_ptr      is a typedef which defines a pointer to an MFC
//                      error reporting object for Windows.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_err_mfc_obj    *yy_err_mfc_ptr;


//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_err_mfc_obj
//
//  The yy_err_mfc_obj is the error class which provides error reporting
//  to a Windows error popup via the Microsoft C++ MFC library.  It is derived
//  from the generic class and overrides the yy_err_puts() function which
//  actually does the display.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_err_output_window([CEdit *])
//                     gets (or sets with an argument) the pointer to the
//                     popup window where the errors will be displayed.
//
//  yy_err_puts()      converts newlines or carriage returns to carriage
//                     return/line feed pairs and then displays a string
//                     onto the error window.
//
//  INTERNAL STATE:
//
//  yy_err_window      is the pointer to the popup window where the errors
//                     will be displayed.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_err_mfc_obj : public yy_err_gen_obj {

 public:

    yy_err_mfc_obj(
        CEdit               *yy_new_err_window = NULL,
        yy_errmsg_dflt_ptr  yy_new_err_tbl = NULL,
        int                 yy_new_err_tbl_max = 0,
        yy_synamsg_dflt_ptr yy_new_syna_tbl = NULL,
        int                 yy_new_syna_tbl_max = 0
        );  

    virtual ~yy_err_mfc_obj();
    
    virtual CEdit *yy_err_output_window()
        { return(yy_err_window); }

    virtual CEdit *yy_err_output_window(CEdit *yy_new_value)
        { return(yy_err_window = yy_new_value); }

    virtual int yy_err_puts(const char *yy_text);

 protected:

    CEdit    *yy_err_window;
    
    };  // yy_err_mfc_obj
    
#endif /* yy_errmf_h_ */
