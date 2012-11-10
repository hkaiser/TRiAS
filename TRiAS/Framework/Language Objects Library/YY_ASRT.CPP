
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_asrt
//
//  FILE DESCRIPTION:     assertion support
//
//  CALLING INTERFACE:  
//
//    int yy_assert_fail(expr, file, line);
//        processes assertions which have failed.
//
//  MODIFICATION HISTORY:
//
//    04/10/98	 cc	  added yy_assert_disable for run-time disabling of
//			  asserts (e.g. in dumps).
//    03/22/96   bz/cc    allow yy_assert_fail to accept constant arguments.
//    04/16/93   bz/cc    changed to use yy_err_printf() for output.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_asrt_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_asrt.h"
#include "yy_err.h"
#include "yy_trace.h"

#ifdef yy_abort_decl_needed_
extern void abort(void);
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  EXTERNAL VARIABLE INITIALIZATIONS:
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_assertion_failed = yy_false;

unsigned int yy_assert_disable_flag = 0;

char yy_assert_msg[] = "Assertion failed: %s, file %s, line %d\n";

yy_assert_cleanup_f yy_assert_cleanup = yy_assert_cleanup_f(0);


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_assert_fail(expr, file, line);
//
//  yy_assert_fail is called when an assertion fails. It prints the failure 
//  message and aborts execution.
//
//  expr        is a string which contains the expression which failed.
//              In ANSI C, this would be obtained by using the stringize (#)
//              operator on the expression in the assert macro.
//
//  file        is the name of the file containing the assert statement which
//              failed.  In ANSI C, this is the value of __FILE__.
//
//  line        is the line number of the line containing the assert statement
//              which failed.  In ANSI C, this is the value of __LINE__.
//
//  yy_assert_fail always returns a zero (0).
//
//  --------------------------------------------------------------------------
//
//  If there is a cleanup function defined (yy_assert_cleanup != NULL), it 
//  will call that function before aborting the execution.
//
//  If yy_assert_fail is called (indirectly) recursively, it is presumed that
//  an assertion failed while trying to execute the cleanup function, and 
//  aborts immediately.
//
//  yy_assert_fail is called by the macro assert(expr) when expr is false.
//  For more information on the macro assert(expr), see yy_asrt.h
//
//////////////////////////////////////////////////////////////////////////////

int yy_export yy_assert_fail(
    const char  *expr, 
    const char  *file, 
    int         line)
{

    static int recursive_death = 0; // no recursive call has occured 

//  If assertions are diabled (at run-time), ignore the failure

    if (yy_assert_disable_flag != 0) return(1);
    
//  Determine if this is a recursive call to this routine

    switch (recursive_death) {

//  not a recursive call, print the assertion failure message and cleanup

    case 0:
        recursive_death = 1;
        yy_assertion_failed = yy_true;
        if (yy_err_failsafe_obj() != NULL) {
            yy_err_failsafe_obj() -> 
                yy_err_printf(yy_assert_msg, expr, file, line);
            }
        if (yy_assert_cleanup != NULL) {
            (* yy_assert_cleanup)();
            }
        break;

//  a recursive call, print a warning about recursive failure

    case 1:
        recursive_death = 2;
        if (yy_err_failsafe_obj() != NULL) {
            yy_err_failsafe_obj() -> 
                yy_err_printf("\nRecursive assertion failure.\n");
            }
        break;

//  either a double recursive failure or our local static was trashed

    default:
        abort();
        }  // recursive death switch

    yy_err_exit();
    abort();
    return(0);

}   // yy_assert_fail


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   unsigned int &yy_assert_disable()
//
//  yy_assert_disable allows disabling of assertions at run-time.
//
//  yy_assert_disable returns a reference to the disabling flag
//
//////////////////////////////////////////////////////////////////////////////

unsigned int &yy_assert_disable(void)
{
    ++yy_assert_disable_flag;

    return(yy_assert_disable_flag);

}   // yy_assert_disable


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   unsigned int &yy_assert_enable()
//
//  yy_assert_enable allows enabling of assertions at run-time.
//
//  yy_assert_enable returns a reference to the disabling flag
//
//////////////////////////////////////////////////////////////////////////////

unsigned int &yy_assert_enable(void)
{
    if (0 < yy_assert_disable_flag) {
	--yy_assert_disable_flag;
    }
    
    return(yy_assert_disable_flag);

}   // yy_assert_enable


