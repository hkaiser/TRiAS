
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_cmd
//
//  FILE DESCRIPTION:     command line processing support
//
//  PORTABILITY ISSUES:
//
//     Each string in argv[] is one word where the definition of word depends 
//     upon the operating system.  The code in yy_cmd_line() assumes the 
//     switch character and the option name are one word.  Thus, an option,
//     "-help" for example, is expected as one word in argv[].
//
//  MODIFICATION HISTORY:
//
//    02/27/98   bz       merged -I option that was in the DEC version.
//    12/06/93   bz/cc    syntax assists are now in the error object and 
//                        name changes so classes and members do not have
//                        the same names.
//    04/05/93   bz       updated for native C++ error rewrite.
//    10/30/92   bz       disabled warning 4505 for Microsoft 7.0.
//    09/10/92   bz       changed i and offset to int so they can be used as
//                        array subscripts without warnings from Borland C++.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    02/08/92   bz       updated traces to use macros which compile for both 
//                        c and c++.  
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#define yy_cmd_c_ 1

#include "yy_ansi.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_starg.h"
#include "yy_ctype.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_inp.h"
#include "yy_inpst.h"
#include "yy_help.h"
#include "yy_trace.h"
#include "yy_cmd.h"


//////////////////////////////////////////////////////////////////////////////
//
//  CONFIGURATION CONSTANTS
//
//  yy_cmd_file_suffixes[] array of suffixes for the filename being opened.
//                      The default is not to process suffixes.  To support 
//                      suffix searches, add the suffixes in the order they
//                      are to be searched.  Each suffix must be a separate 
//                      string, and the final string must be "".
//
//  yy_cmd_switch_chars prefix string indicating a command line option.
//                      defaults to "-".  For example, -help.  Each character
//                      of the string represents one character which can
//                      begin an option.  For example, if you wish to also 
//                      accept options which begin with a slash, use "-/".
//
//////////////////////////////////////////////////////////////////////////////

const char *yy_cmd_file_suffixes[] = { "" };

const char *yy_cmd_switch_chars = "-";


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_cmd_dflt_obj::yy_cmd_dflt_obj();
//
//  This is the no argument constructor for the default implementation 
//  command line processing object.
//
//////////////////////////////////////////////////////////////////////////////

yy_cmd_dflt_obj::yy_cmd_dflt_obj() :
    yy_argc(0),
    yy_arg_num(0),
    yy_argv(NULL),
    yy_filename(NULL),
    yy_this_err_obj(NULL),
    yy_this_inp_obj(NULL)
{
}   // constructor for yy_cmd_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_cmd_dflt_obj::yy_cmd_dflt_obj(...);
//
//  This is the constructor for the default implementation command line 
//  processing object whose parameter list corresponds to the fields in the 
//  command line processing object.
//
//////////////////////////////////////////////////////////////////////////////

yy_cmd_dflt_obj::yy_cmd_dflt_obj(
        yy_inp_file_ptr  yy_new_inp,
        yy_err_dflt_ptr  yy_new_err
    ) :
    yy_argc(0),
    yy_arg_num(0),
    yy_argv(NULL),
    yy_filename(NULL),
    yy_this_err_obj(yy_new_err),
    yy_this_inp_obj(yy_new_inp)
{
}   // constructor for yy_cmd_dflt_obj


/////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_cmd_dflt_obj::~yy_cmd_dflt_obj();
//
//  This is the destructor for the default implementation command line 
//  processing object.
//
//////////////////////////////////////////////////////////////////////////////

yy_cmd_dflt_obj::~yy_cmd_dflt_obj()
{

//  if there is a filename, delete it

    if (yy_filename != NULL) {
        delete [] yy_filename;
        yy_filename = NULL;
        }

}   // destructor for yy_cmd_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_cmd_line(argc, argv)
//
//  yy_cmd_line() processes the command line arguments for the invocation of
//  an application built with Yacc++.
//
//  argc        is the number of command line arguments plus one.
//
//  argv        is an array of strings containing the command line invocation.
//              This first string is the application name, the command was 
//              invoked by.  The following strings are the remainder of the
//              command line including the filename and command line options
//              in the order they appeared.
//
//  --------------------------------------------------------------------------
//
//  yy_cmd_line() opens the input file which the user specifies on the command
//  line so that the lexer and parser will process input from the file.
//
//  It sets globally visible flags to indicate which options the user has 
//  selected.  Option names begin with a switch character to distinguish them
//  from file names.
//
//  Options may appear in any case.  yy_cmd_line() translates to lower case 
//  before doing the comparisons.  Option arguments such as pathnames are
//  always processed as is.
//
//  For options which have filenames or numeric arguments, these values are 
//  also saved in global variables.
//
//  If the -help option is specified, the function yy_help() is called and
//  no further processing occurs.
//
//  yy_cmd_line() does some checking of the validity of the options and 
//  calls yy_err_report() if the options are unacceptable.
//
//  yy_cmd_switch_chars is initialized to the switch character "-".  
//
//////////////////////////////////////////////////////////////////////////////

void yy_cmd_dflt_obj::yy_cmd_line(
        int     yy_new_argc,
        char    *yy_new_argv[])
{
    size_t              offset;
    yy_ptr_sized_int    argument;

//  make sure we have an error object to work with

    if (yy_this_err_obj == NULL) {
        yy_this_err_obj = yy_err_dflt_ptr(yy_err_failsafe_obj());
        }

//  push the command line object onto the error stack, so that errors
//  are reported as occurring in the command line arguments

    if (yy_this_err_obj != NULL) {
        yy_this_err_obj -> yy_err_push_location(this);
        }

//  save the command line arguments in the object

    yy_argc = yy_new_argc;
    yy_argv = yy_new_argv;

//  process each string from the command line, skipping the invocation name

    for (yy_arg_num = 1; yy_arg_num < yy_argc; ++yy_arg_num) {

//  if the option does not begin with a switch char, it must be a file name

        if (strchr(yy_cmd_switch_chars, yy_argv[yy_arg_num][0]) == NULL) {

          if (yy_filename != NULL) {
                yy_err_report(6, yy_argv[yy_arg_num]);
                }
            else {
                yy_this_inp_obj -> yy_inp_is_file(yy_argv[yy_arg_num],
                    yy_cmd_file_suffixes);
                yy_filename = new char
                    [strlen(yy_this_inp_obj -> yy_inp_filename()) + 1];
                if (yy_filename == NULL) {
                    yy_err_report(406);
                    yy_assert_fail("space unavailable from new", __FILE__, 
                        __LINE__);
                    return;
                    }
                strcpy(yy_filename, yy_this_inp_obj -> yy_inp_filename());
                }
            }

        //  begins with a switch character, we have an option

        else {

            //  translate the option to lower case, if need be, 
            //  before doing the string compares

            offset = strlen(yy_argv[yy_arg_num]) - 1;
            while (offset > 0) { // don't bother with yy_argv[0], 
                                 // it is the switch char
                if (yy_argv[yy_arg_num][offset] >= 'A' && 
                    yy_argv[yy_arg_num][offset] <= 'Z') {
                    yy_argv[yy_arg_num][offset] = 
                        (char)(yy_argv[yy_arg_num][offset] + ('a' - 'A'));
                    }
                --offset;
                }

            //  process the help option 

            if (strcmp(yy_argv[yy_arg_num]+1, "h") == 0 || 
                strcmp(yy_argv[yy_arg_num]+1, "help") == 0) {
                yy_help();
                exit(0);
                }

            //  process the assist/no_assist options

            else if (strcmp(yy_argv[yy_arg_num]+1, "a") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "assist") == 0) {
                yy_this_err_obj -> yy_err_display_syna_assists(yy_true);
                }

            else if (strcmp(yy_argv[yy_arg_num]+1, "na") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "no_assist") == 0) {
                yy_this_err_obj -> yy_err_display_syna_assists(yy_false);
                }

            //  process the assistfile filename option

            else if (strcmp(yy_argv[yy_arg_num]+1, "af") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "assistfile") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num || strchr(yy_cmd_switch_chars, 
                    yy_argv[yy_arg_num][0]) != NULL) {
                    yy_err_report(11, yy_argv[yy_arg_num-1]);
                    }
                else {
                    yy_this_err_obj -> yy_err_syna_filename(
                        yy_argv[yy_arg_num]);
                    }
                }

            //  process the no_assistfile option

            else if (strcmp(yy_argv[yy_arg_num]+1, "naf") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "no_assistfile") == 0) {
                yy_this_err_obj -> yy_err_syna_filename(NULL);
                }

            //  process the errorfile filename option

            else if (strcmp(yy_argv[yy_arg_num]+1, "ef") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "errorfile") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num || strchr(yy_cmd_switch_chars, 
                    yy_argv[yy_arg_num][0]) != NULL) {
                    yy_err_report(11, yy_argv[yy_arg_num-1]);
                    }
                else {
                    yy_this_err_obj -> yy_err_filename(yy_argv[yy_arg_num]);
                    }
                }

            //  process the no_errorfile option

            else if (strcmp(yy_argv[yy_arg_num]+1, "nef") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "no_errorfile") == 0) {
                 yy_this_err_obj -> yy_err_filename(NULL);
                }

            //  process the include option(s) -- the order the -I options 
	    //  appear in is preserved as the order they appear on the command 
	    //  line determines the order the include search rules are tried 
	    //  at include file open time.  The order is preserved by adding 
	    //  the new entry to the end of the linked list.

            else if (strcmp(yy_argv[yy_arg_num]+1, "i") == 0 ||
                     strcmp(yy_argv[yy_arg_num]+1, "include") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num || strchr(yy_cmd_switch_chars, 
                    yy_argv[yy_arg_num][0]) != NULL) {
                    yy_err_report(15, yy_argv[yy_arg_num-1]);
                    }
                else {
		    yy_cmd_paths_extend(yy_argv[yy_arg_num]);
                    }
                }

            //  process the include option with no space between -I and 
	    //  pathname as is done some by C++/C compilers.  This is for 
	    //  -Ipath only, not longer spelling -INCLUDE path.

            else if ('i' == yy_argv[yy_arg_num][1]) {
		    yy_cmd_paths_extend(yy_argv[yy_arg_num]+2);
                    }
           
            //  process the max_errors option

            else if (strcmp(yy_argv[yy_arg_num]+1, "me") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "max_errors") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num) {
                    yy_err_report(12, yy_argv[yy_arg_num-1]);
                    }
                else {
                    argument = atoi(yy_argv[yy_arg_num]);
                    if (argument < 1) {
                        yy_err_report(9, argument, 
                             yy_this_err_obj -> yy_err_max_errors_);
                        yy_this_err_obj -> yy_err_max_errors_allowed(
                             yy_this_err_obj -> yy_err_max_errors_);
                        }
                    else {
                        yy_this_err_obj -> yy_err_max_errors_allowed(
                             (int) argument);
                        }
                    }
                }

            //  process the max_warnings option

            else if (strcmp(yy_argv[yy_arg_num]+1, "mw") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "max_warnings") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num) {
                    yy_err_report(12, yy_argv[yy_arg_num-1]);
                    }
                else {
                    argument = atoi(yy_argv[yy_arg_num]);
                    if (argument < 1) {
                        yy_err_report(10, argument, 
                            yy_this_err_obj -> yy_err_max_warnings_);
                        yy_this_err_obj -> yy_err_max_warnings_allowed(
                            yy_this_err_obj -> yy_err_max_warnings_);
                        }
                    else {
                        yy_this_err_obj -> yy_err_max_warnings_allowed(
                            (int) argument);
                        }
                    }
                }

            //  process the min_display option

            else if (strcmp(yy_argv[yy_arg_num]+1, "md") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "min_display") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num) {
                    yy_err_report(12, yy_argv[yy_arg_num-1]);
                    }
                else {
                    argument = atoi(yy_argv[yy_arg_num]);
                    if (argument > 5) {
                        yy_err_report(7, argument, 
                            yy_this_err_obj -> yy_err_min_display_);
                        yy_this_err_obj -> yy_err_min_severity_to_display(
                            yy_this_err_obj -> yy_err_min_display_);
                        }
                    else if (argument < 0) {
                        yy_err_report(8, argument, 
                            yy_this_err_obj -> yy_err_min_display_);
                        yy_this_err_obj -> yy_err_min_severity_to_display(
                            yy_this_err_obj -> yy_err_min_display_);
                        }
                    else {
                        yy_this_err_obj -> yy_err_min_severity_to_display(
                            (int) argument);
                        }
                    }
                }

            //  process the min_fail option

            else if (strcmp(yy_argv[yy_arg_num]+1, "mf") == 0 || 
                     strcmp(yy_argv[yy_arg_num]+1, "min_fail") == 0) {
                ++yy_arg_num;
                if (yy_argc <= yy_arg_num) {
                    yy_err_report(12, yy_argv[yy_arg_num-1]);
                    }
                else {
                    argument = atoi(yy_argv[yy_arg_num]);
                    if (argument > 5) {
                        yy_err_report(7, argument, 
                            yy_this_err_obj -> yy_err_min_fail_);
                        yy_this_err_obj -> yy_err_min_severity_to_fail(
                            yy_this_err_obj -> yy_err_min_fail_);
                        }
                    else if (argument < 0) {
                        yy_err_report(8, argument, 
                            yy_this_err_obj -> yy_err_min_fail_);
                        yy_this_err_obj -> yy_err_min_severity_to_fail(
                            yy_this_err_obj -> yy_err_min_fail_);
                        }
                    else {
                        yy_this_err_obj -> yy_err_min_severity_to_fail(
                            (int) argument);
                        }
                    }
                }

            //  an unknown command line option was encountered, ignore it

            else {
                yy_err_report(3, yy_argv[yy_arg_num]); 
                }

            }  //  else has leading switch character

        }  //  for yy_argv loop : process all command line options

//  one of the options should have been an input filename

    if (yy_this_inp_obj -> yy_inp_not_attached()) {
        yy_err_report(1);   // no input file specified
        }

//  pop the command line object off the error stack, so that errors
//  are no longer reported as occurring in the command line arguments

    if (yy_this_err_obj != NULL) {
        yy_this_err_obj -> yy_err_pop_location();
        }

}   // yy_cmd_line


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_loc_print_self(yy_this_err)
//
//  yy_this_err    the error object on which the location is to be displayed
//
//  yy_loc_print_self() redefines the default location printing function.
//  The default displays nothing.  For a command line object, the argument
//  number and/or text is the location being tracked and displayed instead 
//  of nothing.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_cmd_dflt_obj::yy_loc_print_self(
    yy_err_ptr yy_this_err
    )
{

//  if the argument # is out of bounds, don't display the argument # 

    if (yy_arg_num < 0 || yy_argc <= yy_arg_num) {
        return(yy_this_err -> yy_err_printf("command line, "));
        }

//  if there is no argument text, just display the number

    if (yy_argv[yy_arg_num] == NULL) { 
        return(yy_this_err -> yy_err_printf("command line argument %d, ",
            yy_arg_num));
        }

//  otherwise, display both the argument # and text

    return(yy_this_err -> yy_err_printf("command line argument %d \"%s\", ",
            yy_arg_num, yy_argv[yy_arg_num]));

}   // yy_loc_print_self
