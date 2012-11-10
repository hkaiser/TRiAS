
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_err.h
//
//  FILE DESCRIPTION:     header file with error object declarations
//                        (for Microsoft C++ compiler)
//
//  CLASS HIERARCHY:
//
//                  +------------------------+
//                  |    error reporting     |
//                  |  abstract base class   |
//                  +------------------------+
//                              | derives      
//                  +------------------------+
//                  |    error reporting     |
//                  | generic implementation |
//                  +------------------------+
//                              | derives      
//              +---------------+----------------+
//              |               |                |
//              |   +------------------------+   |
//              |   |    error reporting     |   |
//              |   |  stream implementation |   |
//              |   |   (see yy_errst.h)     |   |
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
//                  |   (see yy_errst.h)     |
//                  +------------------------+
//                              | derives      
//                  +------------------------+
//                  |    error reporting     |
//                  | default implementation |
//                  |    with signatures     |
//                  |   (see yy_signc.h)     |
//                  +------------------------+
//
//
//                  +------------------------+
//                  |     error message      |
//                  |  abstract base class   |
//                  +------------------------+
//                             | derives      
//                  +------------------------+
//                  |     error message      |
//                  | default implementation |
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
//                  |   (see yy_signc.h)     |
//                  +------------------------+
//
//
//  Error processing is built from 3 fundamental abstractions.  There are
//  error report and error messages classes defined in yy_err.h (with 
//  derived classes in yy_errst.h, yy_errmf.h, and  yy_errow.h).  And there 
//  are location classes defined in yy_loc.h.
//
//  The error report classes know how to display text.  Each error report
//  directs text to a specific place.  For example, there is a stream 
//  output class which directs the output to a cerr stream and an OWL 
//  output class which directs the output to a dialog box using Borland's 
//  Object Windows Library.
//
//  The location classes determine what information is displayed for the
//  location of the error.  These classes allow error messages to contain
//  the file name and line number, or similar information.
//
//  The error classes determine the rest of the error processing interface.
//  This includes how error messages are looked up given an error number,
//  how error severities are handled, and what happens upon a fatal error.
//
//  The error classes themselves are defined in terms of 2 related classes:
//  the error reporting classes and the error message classes.  The
//  error reporting classes know how to look up an error message, how to
//  display the message, and how to abort an application if a fatal error 
//  is encountered.
//
//  Two of the error reporting class functions are also provided as 
//  friend functions (requiring no error object).  These functions
//  access a "failsafe" error object and are provided to allow catching
//  errors when the code cannot get access to an error object.
//
//  MODIFICATION HISTORY:
//
//    04/05/94   bz/cc    removed friend declarations for yy_err_printf(),
//                        yy_err_report(), and yy_err_exit() because friend
//                        and member functions can't have the same name. 
//                        (this was caught by the Watcom C++ compiler).
//    10/20/93   bz/cc    merged syntax assists into error objects.  Added new
//                        virtual function yy_err_syntax_assist().  Also added
//                        yy_err_printf which uses yy_err_failsafe.
//    10/04/93   bz/cc    changed static member yy_err_failsafe_obj
//                        to yy_err_failsafe to avoid naming conflict
//                        with function of same name for compilers 
//                        such as Lucid which do not accept name conflict.
//    09/22/93   bz       made yy_err_report() and yy_err_printf() non-virtual
//                        defined functions in abstract base class yy_err_obj
//                        as compilers such as Watcom don't accept ... 
//                        parameters of virtuals.
//    04/02/93   bz       added yy_export for use of classes in a DLL.
//    03/22/93   bz/cc    rewrote the error related classes for the 
//                        Revision 2.0 native C++ rewrite.  Combines
//                        yy_err.h, yy_err1.h, and yy_err2.h.
//    08/12/92   bz       error output now defaults to stdout on DOS and OS/2.
//    08/09/92   bz       added member functions to access error information
//                        yy_total_errs, yy_total_warns, and yy_err_severity.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_err_h_
#define yy_err_h_

#include "yy_ansi.h"
#include "yy_bool.h"
#include "yy_loc.h"
#include "yy_starg.h"
#include "yy_stdio.h"
#include "yy_strng.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_err_ptr          is a typedef which defines a pointer to an error
//                      reporting object.
//
//  yy_err_gen_ptr      is a typedef which defines a pointer to a generic
//                      error reporting object.
//
//  yy_errmsg_ptr       is a typedef which defines a pointer to an error
//                      message object.
//
//  yy_errmsg_dflt_ptr  is a typedef which defines a pointer to a default
//                      error message object.
//
//  yy_synamsg_ptr      is a typedef which defines a pointer to an syntax
//                      assist message object.
//
//  yy_synamsg_dflt_ptr is a typedef which defines a pointer to a default
//                      syntax assist message object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_err_obj           *yy_err_ptr;

typedef class yy_export yy_err_gen_obj       *yy_err_gen_ptr;

typedef class yy_export yy_errmsg_obj        *yy_errmsg_ptr;
typedef class yy_export yy_errmsg_dflt_obj   *yy_errmsg_dflt_ptr;

typedef class yy_export yy_synamsg_obj        *yy_synamsg_ptr;
typedef class yy_export yy_synamsg_dflt_obj   *yy_synamsg_dflt_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_err_obj
//
//  The yy_err_obj is an abstract base class which provides the interface 
//  definition for the error reporting used in the Language Objects Library.
//  If you are replacing the error reporting scheme at the most fundamental
//  level, this class provides the minimal interface you must support.
//  There are additional interface routines in the derived classes which
//  you may also need to provide, but only if you want to use them in your 
//  application.
// 
//  PUBLIC FUNCTIONS:
//
//  ~yy_err_obj()      destructor for an error object.
//
//  yy_err_exit()      displays the summary of how many times yy_err_report()
//                     was called for warnings and/or errors.  Exits the 
//                     application after displaying the summary.
//
//  yy_err_pop_location() 
//                     pops the top location object from the stack, unless
//                     this would make the stack empty.  The bottom location
//                     element on the stack always remains.  
//
//                     Note that yy_err_pop_location() is called from the 
//                     input object destructor to keep track of locations 
//                     within the text being parsed.
//
//  yy_err_printf()    formats and displays text onto the error output stream 
//                     given a format and arguments to fill in the format.
//                     Call this function if you have the arguments at the
//                     place making the call.
//
//  yy_err_push_location() 
//                     pushes a new location object onto the top of the stack.
//
//                     Note that yy_err_push_location() is called from the 
//                     input object constructor to keep track of locations 
//                     within the text being parsed.
//
//  yy_err_puts()      displays a string onto the error output stream.
//                     Call this function if you have the string with no
//                     further formatting requirements.
//
//  yy_err_report()    reports an error message.  It formats and displays 
//                     the error message onto the error output stream given
//                     an error number and arguments to fill in to the error
//                     message.
//
//  yy_err_syntax_assist() 
//                     reports a syntax assist message.  It formats and 
//                     displays the syntax assist message onto the error 
//                     output stream given a syntax assist number.
//
//  yy_err_vprintf()   formats and displays text onto the error output stream 
//                     given a format and a va_list as returned from the 
//                     va_start macro.  Call this function if your function 
//                     has accepted a variable argument list which you need
//                     displayed.
//
//  yy_err_vreport()   formats and displays text onto the error output stream
//                     given an error number and a va_list as returned from 
//                     the va_start macro.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_err_obj {

 public:
    
    virtual ~yy_err_obj();

    virtual void yy_err_exit() = 0;

    virtual void yy_err_pop_location() = 0;

    int yy_err_printf(
        const char *yy_err_fmt,
        ...
        );

    virtual void yy_err_push_location(
        yy_loc_ptr yy_loc
        ) = 0;

    virtual int yy_err_puts(
        const char *yy_text
        ) = 0;

    int yy_err_report(
        int     yy_err_num,
        ...
        );

    virtual int yy_err_syntax_assist(
        int     yy_syna_num
        ) = 0;

    virtual int yy_err_vprintf(
        const char *yy_err_fmt,
        va_list yy_var_args
        ) = 0;

    virtual int yy_err_vreport(
        int     yy_err_num,
        va_list yy_var_args
        ) = 0;

    };  // yy_err_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_err_exit(void)
//
//  yy_err_exit() displays the summary of how many times yy_err_report()
//  was called for warnings and/or errors and exits after displaying the 
//  summary.  This function does not have an error object of its own so 
//  it uses the failsafe error object.
//
//////////////////////////////////////////////////////////////////////////////

void yy_export yy_err_exit();


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_gen_ptr yy_err_failsafe_obj(void)
//
//  yy_err_failsafe_obj() returns the failsafe error object.  If a failsafe
//  error object doesn't exist, it creates one which discards all errors
//  to be displayed.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_gen_ptr yy_export yy_err_failsafe_obj();


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_printf(const char *yy_err_fmt, ...)
//
//  yy_err_printf() formats and displays text onto the error output stream 
//  given a format and arguments to fill in the format.  This  function does 
//  not have an error object of its own so it uses the failsafe error object.
//
//////////////////////////////////////////////////////////////////////////////

int yy_export yy_err_printf(
    const char *yy_err_fmt,
    ...
    );

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_report(int yy_err_num, ...)
//
//  yy_err_report() looks up an error message in the error table and then
//  displays it.  This function does not have an error object of its own so 
//  it uses the failsafe error object.
//
//////////////////////////////////////////////////////////////////////////////

int yy_export yy_err_report(
    int         yy_err_num,
    ...);

    
//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_err_gen_obj
//
//  The yy_err_gen_obj is a generic implementation class which provides 
//  the common semantics for the error reporting used in the Language Objects 
//  Library.  Specialized error reporting classes 
// 
//  CONFIGURATION CONSTANTS:
//
//  yy_err_max_errors_  is the default maximum number of errors to 
//                      process before aborting.  The user may override
//                      this value with "-max_errors n" option.
//
//  yy_err_max_warnings_
//                      is the default maximum number of warnings to 
//                      process before aborting.  The user may override 
//                      this value with "-max_warnings n" option.
//
//  yy_err_min_display_ is the default minimum (severity) level of
//                      errors to  display.  The user may override this
//                      value with "-min_display n" option.
//
//  yy_err_min_fail_    is the default minimum (severity) level of
//                      errors to return as failure codes.  The user may 
//                      override this value with "-min_fail n" option.
//
//  yy_err_msg_max_     is the maximum length of an error message.
//
//  yy_err_severity_abort_   
//                      is the severity level of an error which causes 
//                      the application to terminate.
//
//  yy_err_severity_immed_exit_ 
//                      is the severity level of an error which causes the 
//                      error routines to terminate the application.
//
//  yy_err_severity_internal_   
//                      is the severity level of an error which is caused 
//                      by internal problems within the application.
//
//  yy_err_severity_max_
//                      is the highest severity level of any error.
//
//  PUBLIC FUNCTIONS:
//
//  yy_err_highest_severity_found([int]) 
//                      gets (or sets with an argument) the highest severity 
//                      level of errors seen so far.
//
//  yy_err_lookup_msg() is called to retrieve an error message by number
//                      in the error message table.
//
//  yy_err_lookup_syna_msg() 
//                      is called to retrieve a syntax assist message by 
//                      number in the syntax assist table.
//
//  yy_err_max_errors_allowed([int]) 
//                      gets (or sets with an argument) the number of errors
//                      allowed before the error report facility attempts to
//                      terminate the application.
//
//  yy_err_max_warnings_allowed([int]) 
//                      gets (or sets with an argument) the number of warnings
//                      allowed before the error report facility attempts to
//                      terminate the application.
//
//  yy_err_min_severity_to_display([int]) 
//                      gets (or sets with an argument) the lowest severity 
//                      of errors to be displayed.
//
//  yy_err_min_severity_to_fail([int]) 
//                      gets (or sets with an argument) the lowest severity 
//                      of errors to force termination.
//
//  yy_err_reset()      resets all the internal severity counters so
//                      error reporting is in its initial state.  (no
//                      errors seen yet).
//
//  yy_err_total_errors_found([int]) 
//                      gets (or sets with an argument) the total number of 
//                      errors seen so far.
//
//  yy_err_total_warnings_found([int])
//                      gets (or sets with an argument) the total number of 
//                      warnings seen so far.
// 
//  Note:               this class inherits from the abstract base class and 
//                      thus also provides all of the functions listed in 
//                      that public interface.
//
//  STATIC DATA:
//
//  yy_err_dflt_obj     a default error object for reporting errors not
//                      associated with any specific error object.
//
//  INTERNAL STATE:
//
//  yy_err_max_errors   is the maximum number of errors to display 
//                      before aborting.
//
//  yy_err_max_warnings is the maximum number of warnings to display 
//                      before aborting.
//
//  yy_err_min_display  is the minimum severity of errors to display.
//
//  yy_err_min_fail     is the minimum severity of errors to return as 
//                      failure codes.
//
//  yy_err_severity     is the highest severity level error seen so far.
//
//  yy_err_total_errors is the total number of errors seen so far.
//
//  yy_err_total_warnings is the total number of warnings seen so far.
//
//  yy_err_failsafe     is an error object to use when no other error object
//                      is available.
//  
//  yy_err_loc_stack    is a pointer to a stack of location objects.  The top
//                      object on this stack is used for displaying the 
//                      location information.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_err_gen_obj : public yy_err_obj {

 public:

    enum yy_err_max_errors_enum { yy_err_max_errors_ = 25 };

    enum yy_err_max_warnings_enum {  yy_err_max_warnings_ = 100 };

    enum yy_err_min_display_enum {  yy_err_min_display_ = 1 };

    enum yy_err_min_fail_enum {  yy_err_min_fail_ = 2 };

    enum yy_err_msg_max_enum { yy_err_msg_max_ = 1024 };

    enum yy_err_severity_enum { // the ordering of these enums is important
        yy_err_severity_abort_ = 3,
        yy_err_severity_internal_,
        yy_err_severity_immed_exit_,
        yy_err_severity_max_
        };

    yy_err_gen_obj(
        yy_errmsg_dflt_ptr    yy_new_err_tbl = NULL,
        int                   yy_new_err_tbl_max = 0,
        yy_synamsg_dflt_ptr   yy_new_syna_tbl = NULL,
        int                   yy_new_syna_tbl_max = 0
        );

    virtual ~yy_err_gen_obj();
    
    inline yy_boolean yy_err_display_syna_assists() const;

    inline yy_boolean yy_err_display_syna_assists(yy_boolean yy_new_value);

    virtual void yy_err_exit();
    
    friend yy_export yy_err_gen_ptr yy_err_failsafe_obj(); // get failsafe error object

    inline int yy_err_highest_severity_found() const;

    inline int yy_err_highest_severity_found(int yy_new_value);

    virtual yy_errmsg_ptr yy_err_lookup_msg(int yy_err_num);

    virtual yy_synamsg_ptr yy_err_lookup_syna_msg(int yy_syna_num);

    inline int yy_err_max_errors_allowed() const;

    inline int yy_err_max_errors_allowed(int yy_new_value);

    inline int yy_err_max_warnings_allowed() const;

    inline int yy_err_max_warnings_allowed(int yy_new_value);

    inline int yy_err_min_severity_to_display() const;

    inline int yy_err_min_severity_to_display(int yy_new_value);

    inline int yy_err_min_severity_to_fail() const;

    inline int yy_err_min_severity_to_fail(int yy_new_value);

    inline void yy_err_pop_location();

    inline void yy_err_push_location(yy_loc_ptr yy_loc);

    virtual int yy_err_puts(const char *yy_text);

    inline void yy_err_reset();

    virtual int yy_err_syntax_assist(
        int     yy_syna_num
        );

    inline const char *yy_err_syna_display_prefix() const;

    inline const char *yy_err_syna_display_prefix(const char *yy_new_value);

    inline int yy_err_total_errors_found() const;

    inline int yy_err_total_errors_found(int yy_new_value);

    inline int yy_err_total_warnings_found() const;

    inline int yy_err_total_warnings_found(int yy_new_value);

    virtual int yy_err_vprintf(
        const char *yy_err_fmt,
        va_list yy_var_args
        );

    virtual int yy_err_vreport(
        int     yy_err_num,
        va_list yy_var_args
        );

 protected:

    int                 yy_err_max_errors;
    int                 yy_err_max_warnings;
    int                 yy_err_min_display;
    int                 yy_err_min_fail;
    int                 yy_err_severity;
    int                 yy_err_total_errors;
    int                 yy_err_total_warnings;
    int                 yy_err_tbl_max;
    int                 yy_err_syna_tbl_max;
    yy_boolean          yy_err_syna_assists;
    char                *yy_err_syna_prefix;
    yy_errmsg_dflt_ptr  yy_err_tbl;
    yy_synamsg_dflt_ptr yy_err_syna_tbl;

    yy_loc_stack_ptr    yy_err_loc_stack;

    static yy_err_gen_ptr yy_far yy_err_failsafe;
    
    };  // yy_err_gen_obj

    
//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_errmsg_obj
//
//  The yy_errmsg_obj is an abstract base class which provides the common 
//  semantics for error messages within the error reporting system.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_errmsg_format    is called to get the format of an error message. 
//                      This format is used with the variable arguments to 
//                      yy_err_report to display the actual text of the error
//                      message.
//
//  yy_errmsg_severity  is called to get the severity of an error message.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_errmsg_obj {

 public:

    virtual ~yy_errmsg_obj() {}

    virtual const char *yy_errmsg_format() const = 0;

    virtual int yy_errmsg_severity() const = 0;

    };  // yy_errmsg_obj

    
//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_errmsg_dflt_obj
//
//  The yy_errmsg_dflt_obj is the default implementation class which provides 
//  the common semantics for error messages within the error reporting
//  system in the Language Objects Library.  The error message default object
//  holds the message format string and severity for one error number.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_errmsg_format()  is called to get the format of an error message.  
//                      This format is used with the variable arguments to 
//                      yy_err_report to display the actual text of the error
//                      message.
//
//  yy_errmsg_number()  is called to get the number of an error message.  
//
//  yy_errmsg_severity() is called to get the severity of an error message.
//
//  INTERNAL STATE:
//
//  yy_errmsg_num       is the error number this object represents.
//
//  yy_errmsg_sev       is the severity of this error message.
//
//  yy_errmsg_fmt       is the format used to display this error message.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_errmsg_dflt_obj : public yy_errmsg_obj {

 public:

    yy_errmsg_dflt_obj();

    yy_errmsg_dflt_obj(
        int             yy_errmsg_number, 
        int             yy_errmsg_severity, 
        const char      *yy_errmsg_format
        );

    virtual ~yy_errmsg_dflt_obj();

    inline const char *yy_errmsg_format() const;
    
    inline int yy_errmsg_number() const;

    inline int yy_errmsg_severity() const;
    
 protected:
 
    int                 yy_errmsg_num;
    int                 yy_errmsg_sev;
    char                *yy_errmsg_fmt;
    
    };  // yy_errmsg_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_synamsg_obj
//
//  The yy_synamsg_obj is an abstract base class which provides the common 
//  semantics for syntax assist messages within the error reporting system.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_synamsg_message  is called to get the message of a syntax assist. 
//                      This message is the actual text of the syntax
//                      assist.  It is not further processed.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_synamsg_obj {

 public:

    virtual ~yy_synamsg_obj() {}

    virtual const char *yy_synamsg_message() const = 0;

    };  // yy_synamsg_obj

    
//////////////////////////////////////////////////////////////////////////////
//  
//  CLASS:  yy_synamsg_dflt_obj
//
//  The yy_synamsg_dflt_obj is the default implementation class which provides
//  the common semantics for error messages within the error reporting
//  system in the Language Objects Library.  The error message default object
//  holds the message message string and severity for one error number.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_synamsg_message  is called to get the message of a syntax assist. 
//                      This message is the actual text of the syntax
//                      assist.  It is not further processed.
//
//  yy_synamsg_number()  is called to get the number of a syntax assist.  
//
//  INTERNAL STATE:
//
//  yy_synamsg_num       is the syntax assist number this object represents.
//
//  yy_synamsg_msg       is the message used to display this syntax assist.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_synamsg_dflt_obj : public yy_synamsg_obj {

 public:

    yy_synamsg_dflt_obj();

    yy_synamsg_dflt_obj(
        int             yy_synamsg_number, 
        const char      *yy_synamsg_message
        );

    virtual ~yy_synamsg_dflt_obj();

    inline const char *yy_synamsg_message() const;
    
    inline int yy_synamsg_number() const;

 protected:
 
    int                 yy_synamsg_num;
    char                *yy_synamsg_msg;
    
    };  // yy_synamsg_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the error object, defined above.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_err_gen_obj::yy_err_display_syna_assists() const
    { return(yy_err_syna_assists); }

inline yy_boolean yy_err_gen_obj::yy_err_display_syna_assists(
        yy_boolean yy_new_value)
    { return(yy_err_syna_assists = yy_new_value); }

inline int yy_err_gen_obj::yy_err_highest_severity_found() const
    { return(yy_err_severity); }

inline int yy_err_gen_obj::yy_err_highest_severity_found(int yy_new_value)
    { return(yy_err_severity = yy_new_value); }

inline int yy_err_gen_obj::yy_err_max_errors_allowed() const
    { return(yy_err_max_errors); }

inline int yy_err_gen_obj::yy_err_max_errors_allowed(int yy_new_value)
    { return(yy_err_max_errors = yy_new_value); }

inline int yy_err_gen_obj::yy_err_max_warnings_allowed() const
    { return(yy_err_max_warnings); }

inline int yy_err_gen_obj::yy_err_max_warnings_allowed(int yy_new_value)
    { return(yy_err_max_warnings = yy_new_value); }

inline int yy_err_gen_obj::yy_err_min_severity_to_display() const
    { return(yy_err_min_display); }

inline int yy_err_gen_obj::yy_err_min_severity_to_display(int yy_new_value)
    { return(yy_err_min_display = yy_new_value); }

inline int yy_err_gen_obj::yy_err_min_severity_to_fail() const
    { return(yy_err_min_fail); }

inline int yy_err_gen_obj::yy_err_min_severity_to_fail(int yy_new_value)
    { return(yy_err_min_fail = yy_new_value); }

inline void yy_err_gen_obj::yy_err_pop_location()
    { yy_err_loc_stack -> yy_loc_stack_pop(); }

inline void yy_err_gen_obj::yy_err_push_location(yy_loc_ptr yy_loc) 
    { yy_err_loc_stack -> yy_loc_stack_push(yy_loc); }

inline void yy_err_gen_obj::yy_err_reset() 
    {
    yy_err_severity = 0;
    yy_err_total_errors = 0;
    yy_err_total_warnings = 0;
    }

inline const char *yy_err_gen_obj::yy_err_syna_display_prefix() const
    { return(yy_err_syna_prefix); }

inline const char *yy_err_gen_obj::yy_err_syna_display_prefix(
        const char *yy_new_value)
    { 
        if (yy_err_syna_prefix != NULL) {
            delete [] yy_err_syna_prefix;
            }

        if (yy_new_value != NULL) {
            yy_err_syna_prefix = new char[strlen(yy_new_value) + 1];
            strcpy(yy_err_syna_prefix, yy_new_value);
            }
        else {
            yy_err_syna_prefix = NULL;
            }

        return(yy_err_syna_prefix); 
    }

inline int yy_err_gen_obj::yy_err_total_errors_found() const
    { return(yy_err_total_errors); }

inline int yy_err_gen_obj::yy_err_total_errors_found(int yy_new_value)
    { return(yy_err_total_errors = yy_new_value); }

inline int yy_err_gen_obj::yy_err_total_warnings_found() const
    { return(yy_err_total_warnings); }

inline int yy_err_gen_obj::yy_err_total_warnings_found(int yy_new_value)
    { return(yy_err_total_warnings = yy_new_value); }

    
//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the error message object, defined 
//  above.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_errmsg_dflt_obj::yy_errmsg_format() const
    { return(yy_errmsg_fmt); }

inline int yy_errmsg_dflt_obj::yy_errmsg_number() const
    { return(yy_errmsg_num); }

inline int yy_errmsg_dflt_obj::yy_errmsg_severity() const
    { return(yy_errmsg_sev); }

    
//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the syntax assist object, defined
//  above.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_synamsg_dflt_obj::yy_synamsg_message() const
    { return(yy_synamsg_msg); }

inline int yy_synamsg_dflt_obj::yy_synamsg_number() const
    { return(yy_synamsg_num); }


//////////////////////////////////////////////////////////////////////////////
//
//  COMPATIBILITY MACROS:
//
//  For backward compatibility, the following macros preserve the old names.
//
//  yy_err_highest_sev  ==> calls yy_err_highest_severity_found
//  yy_err_total_errs   ==> calls yy_err_total_errors_found
//  yy_err_total_warns  ==> calls yy_err_total_warnings_found
//  yy_syna_assists     ==> calls yy_err_display_syna_assists
//   
//////////////////////////////////////////////////////////////////////////////

#define yy_err_highest_sev  yy_err_highest_severity_found
#define yy_err_total_errs   yy_err_total_errors_found
#define yy_err_total_warns  yy_err_total_warnings_found
#define yy_syna_assists     yy_err_display_syna_assists

#endif /* yy_err_h_ */
