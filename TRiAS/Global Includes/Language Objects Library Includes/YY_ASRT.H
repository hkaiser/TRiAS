
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_asrt.h
//  
//  FILE DESCRIPTION:     insert file with assertion processing
//  
//  MODIFICATION HISTORY:
//  
//    04/10/98	 cc	  added yy_assert_disable for run-time disabling of
//			  asserts (e.g. in dumps).
//    03/22/96   bz/cc    allow yy_assert_fail to accept constant arguments.
//    12/10/93   bz/cc    moved variable definitions to .cpp file.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//  
//  ------------------------------------------------------------------------
//
//  Parameters:
//
//    define yy_assert_disable_ to suppress assertion checking.
//   
//    modify yy_assert_fail (in yy_asrt.c) to change the semantics
//    of assertion failure.
//
//    define yy_assert_test(x) if you need special assertion
//    expression semantics.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_asrt_h_
#define yy_asrt_h_

#ifndef yy_ansi_h_
#include "yy_ansi.h"
#endif /* yy_ansi_h_ */

#ifndef yy_stdio_h_
#include "yy_stdio.h"
#endif /* yy_stdio_h_ */

#ifndef yy_bool_h_
#include "yy_bool.h"
#endif /* yy_bool_h_ */


//////////////////////////////////////////////////////////////////////////////
//
//  MACROS
//
//  assert              evaluates an expression and calls yy_assert_fail if 
//                      the expression is false.
//
//  yy_assert_test      evaluates the assert expression.
//
//  yy_assert_disable_  when defined diasbles the evaluation of the assert 
//                      expression and assertions are always treated as if 
//                      they succeed.  When yy_assert_disable_ is defined
//                      assert always returns a 1.
//
//  yy_assert_stringize_ 
//                      when defined allows assert to take advantage of the 
//                      stringizing feature in some non-ANSI compilers which
//                      substitute macro parameter into strings in the 
//                      process of macro replacement.  Note that use of 
//                      this feature may cause problems if assert 
//                      expressions involve quoted strings.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef assert
int assert(
    yy_boolean expr);

#ifdef yy_assert_disable_
#define assert(expr) (yy_true)
#else /* yy_assert_disable_ */
#ifdef yy_stringize_ok_
#define assert(expr) (yy_assert_test(expr) ? yy_true : \
 (yy_assert_fail(#expr, __FILE__, __LINE__)))
#else /* yy_stringize_ok_ */
#ifdef yy_assert_stringize_
#define assert(expr) (yy_assert_test(expr) ? yy_true : \
 (yy_assert_fail("expr", __FILE__, __LINE__)))
#else /* yy_assert_stringize_ */
#define assert(expr) (yy_assert_test(expr) ? yy_true : \
 (yy_assert_fail("", __FILE__, __LINE__)))
#endif /* yy_assert_stringize_ */
#endif /* yy_stringize_ok_ */
#endif /* yy_assert_disable_ */

#ifndef yy_assert_test
#define yy_assert_test(x)  (x)
#endif /* yy_assert_test */
#endif /* assert */

//////////////////////////////////////////////////////////////////////////////
//
//  The following variables control assertion processing.
//
//  yy_assertion_failed true when an assertion has failed.
//
//  yy_assert_msg       the message to be printed when an assertion fails.
//
//  yy_assert_cleanup   pointer to a routine to call after the assertion 
//                      message has been printed to gracefully clean up.
//                      To use this feature, assign this variable the 
//                      address of your clean up routine.  This routine 
//                      can be used to dump the internal state of your 
//                      application after an assertion failure.
//
//////////////////////////////////////////////////////////////////////////////

extern yy_boolean yy_assertion_failed;

extern unsigned int yy_assert_disable_flag;

extern char yy_assert_msg[];

typedef int (*yy_assert_cleanup_f)(
    void
    );

extern yy_assert_cleanup_f yy_assert_cleanup;


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION DECLARATIONS
//
//  yy_assert_fail      is called when an assertion fails. It prints the 
//                      failure message and aborts execution.
//
//  yy_assert_disable   disables assertions at run-time.
//
//  yy_assert_enable    enables assertions at run-time.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_asrt_c_
extern 
#endif /* yy_asrt_c_ */
int yy_export yy_assert_fail(
    const char  *yy_expr, 
    const char  *yy_file, 
    int         yy_line
    );

#ifndef yy_asrt_c_
extern 
#endif /* yy_asrt_c_ */
unsigned int &yy_assert_disable(void);

#ifndef yy_asrt_c_
extern 
#endif /* yy_asrt_c_ */
unsigned int &yy_assert_enable(void);

#endif /* yy_asrt_h_ */
