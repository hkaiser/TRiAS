
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_err
//
//  FILE DESCRIPTION:     error and error message object support 
//
//  MODIFICATION HISTORY:
//
//    04/05/94   bz/cc    yy_err_printf(), yy_err_report(), and yy_err_exit()
//                        are no longer friend functions.
//    10/20/93   bz/cc    removed yy_err.tbl inclusion -- it is now passed
//                        into the constructor.  Also, merged syntax assists
//                        into error objects.
//    04/05/93   bz/cc    native C++ rewrite of the error and error message
//                        object.  
//    10/30/92   bz       removed setjmp header.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    02/08/92   bz       removed yy_err_dmp.
//    03/30/90   bz/cc    coding and review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_err_c_
#define yy_err_c_ 1
#endif /* yy_err_c_ */

#include "yy_ansi.h"
#include "yy_err.h"
#include "yy_asrt.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"


//////////////////////////////////////////////////////////////////////////////
//
//  CONFIGURATION CONSTANTS:
//
//  yy_err_num_abort_   is the number for the internal message to generate
//                      when the error processor is terminating the 
//                      application.
//
//  yy_err_num_exit_msg_ 
//                      is the number for the internal message to generate 
//                      when the application is exiting and wishes to display
//                      the number of warnings and errors and the highest 
//                      severity.
//
//  yy_err_num_not_in_file_  
//                      is the number for the internal message to generate
//                      when the error number to report is not listed in
//                      a user specified errorfile.
//
//  yy_err_num_not_in_tbl_
//                      is the number for the internal message to generate
//                      when the error number to report is not listed in the 
//                      internal error tables.
//
//  yy_err_severity_msg[] 
//                      is the list of descriptive names to be displayed for
//                      the different severity levels.
//
//////////////////////////////////////////////////////////////////////////////

enum yy_err_num_enum { 
   yy_err_num_exit_msg_    = 0,
   yy_err_num_not_in_file_ = 1,
   yy_err_num_not_in_tbl_  = 2,
   yy_err_num_abort_       = 3
};
    
const char * const yy_err_severity_msg[] = {
    "note",             // level 0 and below, not counted
    "warning",          // level 1, counted by themselves
    "error",            // level 2, counted with those below
    "fatal error",      // level 3, counted with level 2
    "internal error",   // level 4, counted with level 2
    "fatal error",      // level 5, counted with level 2
    };


//////////////////////////////////////////////////////////////////////////////
//
//  STATIC FIELD INITIALIZATIONS:
//
//  yy_err_failsafe    static initialized to NULL to allow the first 
//                     yy_err_gen_obj created to be the "failsafe" 
//                     error object. 
//
//////////////////////////////////////////////////////////////////////////////

yy_err_gen_ptr yy_far yy_err_gen_obj::yy_err_failsafe = NULL;


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_obj::~yy_err_obj()
//
//  This is the destructor for the abstract error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_obj::~yy_err_obj()
{
}   // destructor for yy_err_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_gen_ptr yy_err_failsafe_obj(void)
//
//  yy_err_failsafe_obj() returns the failsafe error object.  If a failsafe
//  error object doesn't exist, it creates one which discards all errors
//  to be displayed.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_gen_ptr yy_err_failsafe_obj()
{

    if (yy_err_gen_obj::yy_err_failsafe == NULL) {
        yy_err_gen_obj::yy_err_failsafe = new yy_err_gen_obj;
        }

    assert(yy_err_gen_obj::yy_err_failsafe != NULL);

    return(yy_err_gen_obj::yy_err_failsafe);

}   // yy_err_failsafe_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_gen_obj::yy_err_gen_obj()
//
//  This is the constructor for the generic error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_gen_obj::yy_err_gen_obj(
        yy_errmsg_dflt_ptr    yy_new_err_tbl,
        int                   yy_new_err_tbl_max,
        yy_synamsg_dflt_ptr   yy_new_syna_tbl,
        int                   yy_new_syna_tbl_max
    ) :
    yy_err_max_errors(yy_err_max_errors_),
    yy_err_max_warnings(yy_err_max_warnings_),
    yy_err_min_display(yy_err_min_display_),
    yy_err_min_fail(yy_err_min_fail_),
    yy_err_severity(0),
    yy_err_total_errors(0),
    yy_err_total_warnings(0),
    yy_err_tbl_max(yy_new_err_tbl_max),
    yy_err_syna_tbl_max(yy_new_syna_tbl_max),
    yy_err_syna_assists(yy_true),
    yy_err_tbl(yy_new_err_tbl),
    yy_err_syna_tbl(yy_new_syna_tbl),
    yy_err_loc_stack(new yy_loc_stack_obj)
{
    if (yy_err_failsafe == NULL) {
        yy_err_failsafe = this;
        }

//  initialize the syntax assist prefix

    yy_err_syna_prefix = new char[8];

    if (yy_err_syna_prefix == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        }

    memcpy(yy_err_syna_prefix, "  -->  ", 8);

}   // constructor for yy_err_gen_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_gen_obj::~yy_err_gen_obj()
//
//  This is the destructor for the generic implementation error object.
//
//  If this is the "failsafe" error object, the failsafe error object is
//  reset to NULL.
//
//  Deletes the location stack associated with this error object.
//
//  Deletes the syntax assist prefix associated with this error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_gen_obj::~yy_err_gen_obj()
{

    if (yy_err_failsafe == this) {
        yy_err_failsafe = NULL;
        }

    if (yy_err_loc_stack != NULL) {
        delete yy_err_loc_stack;
        yy_err_loc_stack = NULL;
        }

    if (yy_err_syna_prefix != NULL) {
        delete [] yy_err_syna_prefix;
        yy_err_syna_prefix = NULL;
        }

}   // destructor for yy_err_gen_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_err_exit(void)
//
//  yy_err_exit() displays the summary of how many times yy_err_report()
//  was called for warnings and/or errors and exits after displaying the 
//  summary.  This generic version does not terminate the program.
//
//  yy_err_exit() displays a "special" error summary message, which informs 
//  the user of the number of warnings and errors.  Since this is an 
//  information message and not really an error, the severity of the summary
//  message is not relevant.  However, since the message comes from the
//  error message table, it has one, which we now ignore.  When displaying
//  this message, location information, such as the file name and line number
//  when processing a file, is not displayed.
//
//  After displaying this final message, versions in derived classes should
//  terminate the program.
//
//////////////////////////////////////////////////////////////////////////////

void yy_err_gen_obj::yy_err_exit()    
{
    yy_errmsg_ptr     yy_cur_errmsg;

//  lookup the special error message

    yy_cur_errmsg = yy_err_lookup_msg(yy_err_num_exit_msg_);

//  display it

    if (yy_cur_errmsg != NULL) {
        yy_err_printf(yy_cur_errmsg -> yy_errmsg_format(), 
            yy_err_total_errors, yy_err_total_warnings, yy_err_severity);
        }

//  if the highest severity is less than the min fail threshhold, 
//  do not return it as the program status code.

    if (yy_err_severity < yy_err_min_fail) {
        yy_err_severity = 0;
        }

}   // yy_err_exit


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_err_exit(void)
//
//  yy_err_exit() displays the summary of how many times yy_err_report()
//  was called for warnings and/or errors and exits after displaying the 
//  summary.   This function does not have an error object of its own so 
//  it uses the failsafe error object.
//
//////////////////////////////////////////////////////////////////////////////

void yy_err_exit()    
{

//  if there is a failsafe error object, use it.  Otherwise we have no
//  error information, so give up and do nothing.

    if (yy_err_failsafe_obj() != NULL) {
        yy_err_failsafe_obj() -> yy_err_exit();
        }

}   // yy_err_exit


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_ptr yy_err_lookup_msg(yy_err_num)
//
//  yy_err_lookup_msg() is called to retrieve an error message by number
//  in the error message table.  It returns a pointer to the error message
//  which was found or NULL if the error message was not found.      
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_ptr yy_err_gen_obj::yy_err_lookup_msg(int yy_err_num)
{
    int         hi, lo, mid;

//  if there is no error table, the search fails

    if (yy_err_tbl == NULL) {
        return(NULL);
        }

//  we use a binary search when looking up messages in the error table

    lo = 0;
    hi = yy_err_tbl_max;
    mid = (lo + hi) >> 1;

    while (lo <= hi) {
        if (yy_err_num < yy_err_tbl[mid].yy_errmsg_number()) hi = mid-1;
        else if (yy_err_tbl[mid].yy_errmsg_number() < yy_err_num) lo = mid+1;
        else break;
        mid = (lo + hi) >> 1;
        }

//  error message out of table range -- return NULL
            
    if (mid < 0 || yy_err_tbl_max < mid) {
        return(NULL);
        }

//  located the error message -- return pointer to it

    if (yy_err_num == yy_err_tbl[mid].yy_errmsg_number()) {
        return(&yy_err_tbl[mid]);
        }

//  error message not within table -- return NULL

    return(NULL);

}   // yy_err_lookup_msg


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_ptr yy_err_lookup_syna_msg(yy_syna_num)
//
//  yy_err_lookup_syna_msg() is called to retrieve a syntax assist by number
//  in the synatx assist table.  It returns a pointer to the synax assist
//  which was found or NULL if the syntax assist was not found.      
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_ptr yy_err_gen_obj::yy_err_lookup_syna_msg(int yy_syna_num)
{
    int         hi, lo, mid;

//  if there is no syntax assist table, the search fails

    if (yy_err_syna_tbl == NULL) {
        return(NULL);
        }

//  we use a binary search when looking up messages in the syntax assist table

    lo = 0;
    hi = yy_err_syna_tbl_max;
    mid = (lo + hi) >> 1;

    while (lo <= hi) {
        if (yy_syna_num < yy_err_syna_tbl[mid].yy_synamsg_number()) hi = mid-1;
        else if (yy_err_syna_tbl[mid].yy_synamsg_number() < yy_syna_num) lo = mid+1;
        else break;
        mid = (lo + hi) >> 1;
        }

//  error message out of table range -- return NULL
            
    if (mid < 0 || yy_err_syna_tbl_max < mid) {
        return(NULL);
        }

//  located the error message -- return pointer to it

    if (yy_syna_num == yy_err_syna_tbl[mid].yy_synamsg_number()) {
        return(&yy_err_syna_tbl[mid]);
        }

//  error message not within table -- return NULL

    return(NULL);

}   // yy_err_lookup_syna_msg


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_printf(yy_err_fmt, ...)
//
//  yy_err_printf() formats and displays text by sending its arguments onto
//  yy_err_vprintf().   
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_obj::yy_err_printf(
        const char *yy_err_fmt,
        ...
        )
{
    va_list     yy_var_args;
    int         yy_return_value;

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_fmt);

//  pass them on for processing

    yy_return_value = yy_err_vprintf(yy_err_fmt, yy_var_args);

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_printf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_printf(yy_err_fmt, ...)
//
//  yy_err_printf() formats and displays text by sending its arguments onto
//  yy_err_vprintf().   This function does not have an error object of its 
//  own so it uses the failsafe error object.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_printf(
        const char *yy_err_fmt,
        ...
        )
{
    va_list     yy_var_args;
    int         yy_return_value;

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_fmt);

//  if there is a failsafe error object, use it.  Otherwise we have no
//  information on where to display this error so give up and do nothing.

    if (yy_err_failsafe_obj() != NULL) {
        yy_return_value = 
            yy_err_failsafe_obj() -> yy_err_vprintf(yy_err_fmt, yy_var_args);
        }
    else {
        yy_return_value = 0;
        }

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_printf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_puts(yy_text)
//
//  yy_err_puts() would normally display a string onto the output stream.
//  However in this generic class, no display actually occurs.  This 
//  function is merely a placeholder to be overridden in implementation 
//  classes derived from this generic error class.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_gen_obj::yy_err_puts(
    const char *)
{
    return(0);

}   // yy_err_puts


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_report(yy_err_num, ...)
//
//  yy_err_report() looks up an error message in the error table and then
//  displays it by calling yy_err_vreport().
//
//  Note: in this generic class, no display actually occurs.  The display
//  functions in the generic class perform all the steps up to displaying 
//  the actual text.  They lookup an error message and format the text
//  and then call yy_err_puts() to do the actual display of the error.  
//  The display function yy_err_puts() does nothing in the generic
//  error class.  This class design enables the classes which actually do 
//  display text, to simply override the yy_err_puts() function, but to
//  inherit all other functionality.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_obj::yy_err_report(
    int     yy_err_num,
    ...)
{
    va_list     yy_var_args;
    int         yy_return_value;

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_num);

//  pass them on for processing

    yy_return_value = yy_err_vreport(yy_err_num, yy_var_args);

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_report


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_syntax_assist(yy_syna_num)
//
//  yy_err_syntax_assist() looks up a syntax assist in the synax assist table
//  and then displays it by calling yy_err_puts().
//  
//  Note: in this generic class, no display actually occurs.  The display
//  functions in the generic class perform all the steps up to displaying 
//  the actual text.  They lookup a syntax assist message and format the text
//  and then call yy_err_puts() to do the actual display of the error.  
//  The display function yy_err_puts() does nothing in the generic
//  error class.  This class design enables the classes which actually do 
//  display text, to simply override the yy_err_puts() function, but to
//  inherit all other functionality.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_gen_obj::yy_err_syntax_assist(
    int     yy_syna_num)
{
    yy_synamsg_ptr      yy_cur_synamsg;

//  get the desired syntax assist message

    yy_cur_synamsg = yy_err_lookup_syna_msg(yy_syna_num);

//  if we couldn't get the syntax assist, return a zero (0) to the caller
//  to let them know that no message was displayed

    if (yy_cur_synamsg == NULL) {
        return(0);
        }

//  if we can't print out the prefix, return a zero (0) to the caller
//  to let them know that no message was displayed

    if (yy_err_puts(yy_err_syna_prefix) == 0) {
        return(0);
        }

//  print out the syntax assist itself, returning the result code to the
//  caller to let them know whether a message was displayed or not
    
    return(yy_err_puts(yy_cur_synamsg->yy_synamsg_message()));

}   // yy_err_syntax_assist


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_report(int yy_err_num, ...)
//
//  yy_err_report() looks up an error message in the error table and then
//  displays it by calling yy_err_vreport().   This function does not have 
//  an error object of its own so it uses the failsafe error object.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_report(
    int                 yy_err_num,
    ...)
{
    va_list     yy_var_args;
    int         yy_return_value;

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_num);

//  if there is a failsafe error object, use it.  Otherwise we have no
//  information on where to display this error so give up and do nothing.

    if (yy_err_failsafe_obj() != NULL) {
        yy_return_value = 
            yy_err_failsafe_obj() -> yy_err_vreport(yy_err_num, yy_var_args);
        }
    else {
        yy_return_value = 0;
        }

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_report


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_vprintf(yy_err_fmt, yy_var_args)
//
//  yy_err_vprintf() formats and displays text by passing the formatted
//  text onto yy_err_puts().
//
//  Note: in this generic class, no display actually occurs.  All of the
//  display functions merely perform all of the steps upto displaying the
//  actual text, and for that step call yy_err_puts which does nothing.
//  This allows the classes which actually do display text, to override only
//  the yy_err_puts function.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_gen_obj::yy_err_vprintf(
    const char *yy_err_fmt,
    va_list yy_var_args)
{
    char        yy_text[yy_err_msg_max_];
    int         yy_return_value;

//  format the text

    yy_return_value = (int)vsprintf(yy_text, yy_err_fmt, yy_var_args);

//  if unsuccessful, leave without displaying

    if (yy_return_value == 0) {
        return(0);
        }

//  display the text

    return(yy_err_puts(yy_text));

}   // yy_err_vprintf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_vreport(yy_err_num, yy_var_args)
//
//  yy_err_vreport() formats and displays text onto the error output stream
//  given an error number and a va_list as returned from the va_start macro.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_gen_obj::yy_err_vreport(
    int     yy_err_num,
    va_list yy_var_args)
{
    yy_errmsg_ptr   yy_cur_errmsg;
    int             yy_return_value, yy_errmsg_severity;

//  get the desired error message

    yy_cur_errmsg = yy_err_lookup_msg(yy_err_num);

//  if we couldn't get the error message, return a zero (0) to the caller
//  to let them know that no message was displayed

    if (yy_cur_errmsg == NULL) {
        return(0);
        }

//  determine the severity of the message

    yy_errmsg_severity = yy_cur_errmsg -> yy_errmsg_severity();

//  if we don't need to display the error message because the severity is less
//  than the minimum display value, return a zero (0) to the caller to let 
//  them know that no message was displayed.

    if (yy_errmsg_severity < yy_err_min_display) {
        return(0);
        }

//  the severity message is normally determined by the severity of the error

    if (yy_errmsg_severity > 1) {

//  if the severity is too high, the severity message is always "fatal error"

        if (yy_err_severity_max_ < yy_errmsg_severity) {
            yy_errmsg_severity = yy_err_severity_max_;
            }

//  if this is the highest severity message displayed, update the global 
//  maximum severity value 

        if (yy_err_severity < yy_errmsg_severity) {
            yy_err_severity = yy_errmsg_severity;
            }

// if maximum number of errors reached, clean up and abort

        ++yy_err_total_errors;

        if (yy_err_total_errors == yy_err_max_errors + 1) {
            yy_err_report(300, yy_err_max_errors);   
            yy_err_exit();
            yy_assert_fail("yy_err_exit() did not abort the program", 
                __FILE__, __LINE__);
            abort();
            }
        }

    else if (yy_errmsg_severity == 1) {

//  if this is the highest severity message displayed, update the global 
//  maximum severity value 

        if (yy_err_severity < yy_errmsg_severity) {
            yy_err_severity = yy_errmsg_severity;
            }

//  if maximum number of warnings reached, clean up and abort

        ++yy_err_total_warnings;
        if (yy_err_total_warnings == yy_err_max_warnings + 1) {
            yy_err_report(301, yy_err_max_warnings);   
            yy_err_exit();
            yy_assert_fail("yy_err_exit() did not abort the program", 
                __FILE__, __LINE__);
            abort();
            }
        }

//  if the severity is too low, the severity message is always "note"

    else {
        yy_errmsg_severity = 0;
        }

//  the first part of the error message is obtained from the top location 
//  object on the stack, which knows what to display for the location.  
//  For example, an input file object may display the file name and line 
//  number, but an interactive input object may not display any location.

    if (yy_err_loc_stack != NULL) {
        if (yy_err_loc_stack -> yy_loc_stack_top() != NULL) {
            yy_err_loc_stack -> yy_loc_stack_top() -> yy_loc_print_self(this);
            }
        }

//  the second part of the error message is the severity message and 
//  error number.  For example, a severity 3 will display "fatal error".

    yy_err_printf("%s %d: ", yy_err_severity_msg[yy_errmsg_severity], 
        yy_err_num);

//  the last part is the actual error message and the additional arguments 

    yy_return_value = yy_err_vprintf(yy_cur_errmsg -> yy_errmsg_format(), 
        yy_var_args);
    yy_err_puts("\n");

    va_end(yy_var_args);

//  if we need to immediately exit, do so

    if (yy_err_severity_immed_exit_ <= yy_errmsg_severity) { 
        yy_err_exit();
        yy_assert_fail("yy_err_exit() did not abort the program", 
            __FILE__, __LINE__);
        abort();
        }

//  if we need to abort, clean up and abort

    if (yy_err_severity_abort_ <= yy_errmsg_severity) {
        yy_err_report(302);     // aborting
        yy_err_exit();
        yy_assert_fail("yy_err_exit() did not abort the program", 
            __FILE__, __LINE__);
        abort();
        }

//  if we displayed an error message, and didn't exit, return a one (1) to 
//  the caller to let them know that an error was displayed

    return(yy_return_value);

}   // yy_err_vreport


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_dflt_obj::yy_errmsg_dflt_obj()
//
//  This is the no argument constructor for the default error message object.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_dflt_obj::yy_errmsg_dflt_obj() :
    yy_errmsg_num(0),
    yy_errmsg_sev(0),
    yy_errmsg_fmt(NULL)
{
}   // constructor for yy_errmsg_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_dflt_obj::yy_errmsg_dflt_obj(...)
//
//  This is the constructor for the default implementation error message
//  object whose parameter list corresponds to the fields in the error
//  message object.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_dflt_obj::yy_errmsg_dflt_obj(
        int   yy_new_errmsg_num, 
        int   yy_new_errmsg_sev, 
        const char  *yy_new_errmsg_fmt
    ) :
    yy_errmsg_num(yy_new_errmsg_num),
    yy_errmsg_sev(yy_new_errmsg_sev),
    yy_errmsg_fmt((char *)yy_new_errmsg_fmt)
{
}   // constructor for yy_errmsg_dflt_obj


/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_dflt_obj::~yy_errmsg_dflt_obj()
//
//  This is the destructor for the default implementation error message
//  object.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_dflt_obj::~yy_errmsg_dflt_obj()
{
}   // destructor for yy_errmsg_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_dflt_obj::yy_synamsg_dflt_obj()
//
//  This is the no argument constructor for the default syntax assist object.
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_dflt_obj::yy_synamsg_dflt_obj() :
    yy_synamsg_num(0),
    yy_synamsg_msg(NULL)
{
}   // constructor for yy_synamsg_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_dflt_obj::yy_synamsg_dflt_obj(...)
//
//  This is the constructor for the default implementation syntax assist
//  object whose parameter list corresponds to the fields in the error
//  message object.
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_dflt_obj::yy_synamsg_dflt_obj(
        int   yy_new_synamsg_num, 
        const char  *yy_new_synamsg_msg
    ) :
    yy_synamsg_num(yy_new_synamsg_num),
    yy_synamsg_msg((char *)yy_new_synamsg_msg)
{
}   // constructor for yy_synamsg_dflt_obj


/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_dflt_obj::~yy_synamsg_dflt_obj()
//
//  This is the destructor for the default implementation syntax assist
//  object.
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_dflt_obj::~yy_synamsg_dflt_obj()
{
}   // destructor for yy_synamsg_dflt_obj
