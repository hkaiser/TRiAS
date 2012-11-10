
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_lex
//
//  FILE DESCRIPTION:     lexer skeleton file used to build a Yacc+ lexer  
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	  Removed yy_no_myref_inlines_ as it didn't work with
//			  several compilers.
//    12/21/98   bz   	  linux port (g++ warning): added char * casts to 
//                        char array initializers.
//    05/04/98   cc	  extracted various sub-objects from the lexer object.
//    03/18/96   bz/cc    fixed lexer not pausing when buffer is empty and
//                        reading from a pipe (previously this would block). 
//    03/08/94   bz       fixed memory leaks for lexer stack work areas in
//                        the destructor for the lexer base object.
//    12/07/93   bz       updated for Revision 2.0 native C++ lexer object.
//    02/26/93   bz       updated for Revision 2.0 native C++ symbol table
//                        and symbol object creation and deletion.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    01/10/92   cc       Rev 1.4 -- support precompilation of LOL lexer.
//    03/30/90   bz/cc    coding and final review completed.  
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_lex_c_ 
#define yy_lex_c_ 1
#endif /* yy_lex_c_ */

#ifndef yy_lex_code_
#define yy_lex_code_ 1
#endif /* yy_lex_code_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_inp.h"
#include "yy_lex.h"
#include "yy_psr.h"


//////////////////////////////////////////////////////////////////////////////
//
//  STATIC FIELD INITIALIZATIONS:
//
//  yy_lex_cur_obj_ptr      static initialized to NULL
//
//  yy_lex_opc_tbl          static initialized to spellings of opcodes for
//                          use by traces in code
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_ptr yy_far yy_lex_obj::yy_lex_cur_obj_ptr = NULL;

char * yy_far yy_lex_static_obj::yy_this_lex_opc_tbl[yy_lex_obj::yy_lex_num_of_opcs_] 
        = { 
           (char *)" 0 is not used ",
           (char *)"yy_lex_chg_",
           (char *)"yy_lex_chg_nx_",
           (char *)"yy_lex_epops_",
           (char *)"yy_lex_epops_nx_",
           (char *)"yy_lex_err_",
           (char *)"yy_lex_err_nx_",
           (char *)"yy_lex_push_",
           (char *)"yy_lex_push_nx_",
           (char *)"yy_lex_ract_",
           (char *)"yy_lex_ract_nx_",
           (char *)"yy_lex_rdc_",
           (char *)"yy_lex_rdc_nx_",
           (char *)"yy_lex_rdc_nterm_",
           (char *)"yy_lex_rdc_nterm_nx_",
           (char *)"yy_lex_sact_",
           (char *)"yy_lex_sact_nx_",
           (char *)"yy_lex_shf_",
           (char *)"yy_lex_shf_nx_",
           (char *)"yy_lex_shf_nterm_",
           (char *)"yy_lex_shf_nterm_nx_",
           (char *)"yy_lex_type_",
           (char *)"yy_lex_type_nx_",
           (char *)"yy_lex_push_shf_rdc_nterm_",
           (char *)"yy_lex_rdc_chg_",
           (char *)"yy_lex_shf_chg_",
           (char *)"yy_lex_shf_nterm_chg_",
           (char *)"yy_lex_shf_ract_rdc_",
           (char *)"yy_lex_shf_rdc_",
           (char *)"yy_lex_shf_nterm_rdc_",
           (char *)"yy_lex_shf_rdc_nterm_",
           (char *)"yy_lex_shf_rdc_chg_",
           (char *)"yy_lex_shf_sact_",
           (char *)"yy_lex_shf_sact_chg_",
           (char *)"yy_lex_shf_sact_rdc_",
           (char *)"yy_lex_type_ract_rdc_",
            };


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_static_obj::yy_lex_static_obj(...)
//
//  This is the constructor for the static part of lexer object.  It
//  initializes the data members of the abstract base class.  The
//  constructor in the derived class specific to the user's grammar handles
//  grammar specific initialization.
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_static_obj::yy_lex_static_obj(
    yy_psr_ptr                  yy_new_psr_obj,
    int                         yy_new_lex_min_type,
    int                         yy_new_lex_max_type,
    int                         yy_new_lex_max_class,
    int                         *yy_new_lex_cmd,
    int				*yy_new_lex_start_state)
    : yy_this_psr_obj(yy_new_psr_obj),
      yy_this_lex_min_type(yy_new_lex_min_type),
      yy_this_lex_max_type(yy_new_lex_max_type),
      yy_this_lex_max_class(yy_new_lex_max_class),
      yy_this_lex_cmd(yy_new_lex_cmd),
      yy_this_lex_start_state(yy_new_lex_start_state)
{
}   // constructor for yy_lex_static_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_lex_static_obj::~yy_lex_static_obj()
//
//  This is the destructor for the base class lexer object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_static_obj::~yy_lex_static_obj() 
{
}   // destructor for yy_lex_static_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_dynamic_obj::yy_lex_dynamic_obj(...)
//
//  This is the constructor for the dynamic part of lexer object.  It
//  initializes the data members of the abstract base class.  The
//  constructor in the derived class specific to the user's grammar handles
//  grammar specific initialization.
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_dynamic_obj::yy_lex_dynamic_obj(
    yy_inp_ptr                  yy_new_inp_obj,
    yy_symtab_ptr               yy_new_symtab_obj,
    yy_ref_ptr                  yy_new_lex_rslt_val,
    yy_boolean                  yy_new_lex_is_done,
    yy_boolean                  yy_new_lex_error_flag,
    int                         yy_new_lex_tkn_count,
    int                         yy_new_lex_state,
    int                         yy_new_lex_class,
    int                         yy_new_lex_cur_start_state,
    int 			*yy_new_lex_cmd)
{

    yy_lex_dynamic_data.yy_this_inp_obj = yy_new_inp_obj;

    yy_lex_dynamic_data.yy_this_symtab_obj = yy_new_symtab_obj;

    yy_lex_dynamic_data.yy_this_lex_rslt_val = yy_new_lex_rslt_val;

    yy_lex_dynamic_data.yy_this_lex_is_done = yy_new_lex_is_done;

    yy_lex_dynamic_data.yy_this_lex_error_flag = yy_new_lex_error_flag;

    yy_lex_dynamic_data.yy_this_lex_tkn_count = yy_new_lex_tkn_count;

    yy_lex_dynamic_data.yy_this_lex_state = yy_new_lex_state;

    yy_lex_dynamic_data.yy_this_lex_class = yy_new_lex_class;

    yy_lex_dynamic_data.yy_this_lex_cur_start_state = 
	yy_new_lex_cur_start_state;

    yy_lex_dynamic_data.yy_this_lex_cmd = yy_new_lex_cmd;

}   // constructor for yy_lex_dynamic_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_lex_dynamic_obj::~yy_lex_dynamic_obj()
//
//  This is the destructor for the base class lexer object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_dynamic_obj::~yy_lex_dynamic_obj() 
{
}   // destructor for yy_lex_dynamic_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_obj::yy_lex_obj(...)
//
//  This is the constructor for the lexer object.  It initializes the
//  data members of the abstract base class.  The constructor in the derived
//  class specific to the user's grammar handles grammar specific 
//  initialization.
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_obj::yy_lex_obj(
    int                         yy_new_lex_min_type,
    int                         yy_new_lex_max_type,
    int                         *yy_new_lex_cmd,
    yy_inp_ptr                  yy_new_this_inp_obj,
    yy_symtab_ptr               yy_new_this_symtab_obj,
    int                         *yy_new_lex_start_state,
    int                         yy_new_lex_max_class,
    int                         yy_new_lex_class)
    : yy_lex_static_part(NULL, 
			 yy_new_lex_min_type, 
			 yy_new_lex_max_type,
			 yy_new_lex_max_class, 
			 yy_new_lex_cmd, 
			 yy_new_lex_start_state),
      yy_lex_dynamic_part(yy_new_this_inp_obj, 
			  yy_new_this_symtab_obj,
			  NULL, 
			  yy_false, 
			  yy_false, 
			  0, 
			  yy_lex_start_state()[yy_new_lex_class], 
			  yy_new_lex_class,
			  yy_lex_start_state()[yy_new_lex_class], 
			  NULL),
      yy_lex_nterm_lhead_ix(0),
      yy_lex_rdc_ix(0),
      yy_lex_nterm_lhead(NULL),
      yy_lex_rdc_state(NULL)
{
    assert(0 <= yy_new_lex_class && yy_new_lex_class < yy_lex_max_class());

    if (yy_lex_cur_inp() != NULL) {
        yy_lex_cur_inp()->yy_inp_cur_lex(this);
        }

    yy_lex_nterm_lhead = new int [yy_lex_rdc_max_];
    if (yy_lex_nterm_lhead == NULL) {
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        }
//      yy_lex_nterm_lhead_ptr = yy_lex_nterm_lhead;

    yy_lex_rdc_state = new int [yy_lex_rdc_max_];
    if (yy_lex_rdc_state == NULL) {
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        }
//      yy_lex_rdc_state_ptr = yy_lex_rdc_state;

}   // constructor for yy_lex_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_lex_obj::~yy_lex_obj()
//
//  This is the destructor for the base class lexer object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_obj::~yy_lex_obj() 
{

//  disconnect lexer from input object

    if (yy_lex_cur_inp() != NULL) {
        yy_lex_cur_inp()->yy_inp_cur_lex(NULL);
        }

//  destroy sub-objects

    yy_lex_static_part.~yy_lex_static_obj();

    yy_lex_dynamic_part.~yy_lex_dynamic_obj();
    
//  delete lexer stack work areas

    if (yy_lex_nterm_lhead != NULL) {
        delete [] yy_lex_nterm_lhead;
        yy_lex_nterm_lhead = NULL;
        }
    
    if (yy_lex_rdc_state != NULL) {
        delete [] yy_lex_rdc_state;
        yy_lex_rdc_state = NULL;
        }
    
}   // destructor for yy_lex_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_obj::yy_lex();
//
//  yy_lex() is a driver for the lexer engine which feeds it the entire 
//  source input.
//
//////////////////////////////////////////////////////////////////////////////

void yy_lex_obj::yy_lex()
{
    yy_lex_cur_obj_ptr = this;

//  do nothing if the lexer is done (or paused)

    if (yy_lex_is_done()) return;
    
//  create a lex result value if none exists.  note this only handles the
//  case when there is a parser object.  if there isn't a parser object,
//  the yy_lex_rslt function creates the lex result value temporary itself.
					  
    if (yy_lex_cur_psr() != NULL) {
	yy_lex_cur_psr()->yy_psr_rt_create_if_empty();
	}

//  lex the input until done

    for (;;) {  // loop exits from middle -- 18 Mar 96
	yy_lex_ins(yy_buf_read(), (size_t) yy_buf_unread_len());
	if (yy_lex_is_done()) {
	    yy_buf_read(yy_buf_tkn_start()); // reposition read pointer
	    break;
	    }
	yy_lex_cur_inp()->yy_inp_buf_fill();
	}

}   // yy_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_dmp(yy_this_err_obj, yy_dmp_title)
//
//  yy_lex_dmp() displays the values of the lexer state variables.
//  The calls to yy_lex_dmp() in yy_lex.cpp are conditionally compiled based
//  on the setting of yy_trace_.  The lexer object contains this display
//  function in case you need to see the internal state of the lexer engine
//  as your application is lexing (for purposes of debugging).
//
//  yy_this_err_obj  is an error object where this dump is to be displayed.
//           
//  yy_dmp_title  a character string to identify the dump.  For example, 
//                sometimes you might want to identify your symbol table dump
//                with the breakpoint location.  Otherwise, just pass in NULL.
//
//////////////////////////////////////////////////////////////////////////////

void yy_lex_obj::yy_lex_dmp(
    yy_err_ptr   yy_this_err_obj, 
    const char   *yy_dmp_title)    
{

//  use the failsafe error object, if no error object to dump to

    if (yy_this_err_obj == NULL) {
        yy_this_err_obj = yy_err_failsafe_obj();
        }

//  display the title for the dump, if any

    if (yy_dmp_title != NULL) {
        yy_this_err_obj->yy_err_printf("TITLE: %s\n", yy_dmp_title);
        }

    yy_this_err_obj->yy_err_puts("LEXER OBJECT\n");

    yy_this_err_obj->yy_err_printf(
        "\tstate %d     ", yy_lex_state());

    yy_this_err_obj->yy_err_printf(
        "rdc_type %d     ", yy_lex_cur_psr()->yy_psr_rt_type(0));

    yy_this_err_obj->yy_err_printf(
        "result %d     \n\n", yy_lex_cur_psr()->yy_psr_rt_int());

//  display the contents of the buffer too

    if (yy_lex_cur_inp() != NULL) {
        yy_lex_cur_inp()->yy_inp_dmp(
            yy_this_err_obj, "INPUT OBJECT LINKED TO LEXER OBJECT");
        }

}   // yy_lex_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_lex_valid_obj()
//
//  yy_lex_valid_obj() is a validity checking function which currently
//  returns true.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_lex_obj::yy_lex_valid_obj()
{ 
    return(yy_true);

}   //  yy_lex_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_report(yy_err_num, ...)
//
//  yy_err_report() looks up an error message in the error table and then
//  displays it by calling yy_err_vreport().  This function uses the
//  error object associated with the file object associated with this 
//  lexer object.  
//
//  If the error is displayed, it returns a non-zero value.  If the error 
//  was not displayed then 0 is returned.
//
//////////////////////////////////////////////////////////////////////////////

int yy_lex_obj::yy_err_report(
    int     yy_err_num,
    ...)
{
    va_list     yy_var_args;
    int         yy_return_value;

//  if we don't have a file object associated with this lexer object,
//  we're unable to display errors.  Return 0 as error was not displayed.

    if (yy_lex_cur_inp() == NULL) {
        return(0);
        }

//  if we don't have an error object associated with the file object
//  associated with this lexer object, we're unable to display errors.
//  Return 0 as error was not displayed.

    if (yy_lex_cur_inp()->yy_inp_cur_err() == NULL) {
        return(0);
        }

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_num);

//  use the associated error object to lookup, format, and display the error

    yy_return_value = yy_lex_cur_inp()->yy_inp_cur_err()->
                          yy_err_vreport(yy_err_num, yy_var_args);

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_report
