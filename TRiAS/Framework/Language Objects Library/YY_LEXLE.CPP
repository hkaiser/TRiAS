
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_lexle
//
//  FILE DESCRIPTION:     LEX lexer object support
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	  Removed yy_no_myref_inlines_ as it didn't work with
//			  several compilers.
//    06/03/98   cc       switched to using member function interface.
//    10/25/93   bz/cc    initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_lexle_c_ 
#define yy_lexle_c_ 1
#endif /* yy_lexle_c_ */

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
#include "yy_lexle.h"
#include "yy_psr.h"

static int yy_dummy_lex_start_state[1] = { 0 };


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_obj_lex::yy_lex_obj_lex()
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_obj_lex::yy_lex_obj_lex(
    yy_inp_ptr                  yy_new_this_inp_obj,
    yy_symtab_ptr               yy_new_this_symtab_obj)
    : yy_lex_obj(
           0,
           255,
	   0,
           yy_new_this_inp_obj,
           yy_new_this_symtab_obj,
           yy_dummy_lex_start_state,
           1,
           0)
{
}   // constructor for yy_lex_obj_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_obj_lex::yy_lex();
//
//  yy_lex() is a driver for the lexer engine which feeds it the entire source
//  file.
//
//////////////////////////////////////////////////////////////////////////////

void yy_lex_obj_lex::yy_lex()
{
    yy_lex_cur_obj_ptr = this;

    while (! yy_lex_is_done()) { 

//  create a lex result value if none exists.  note this only handles the
//  case when there is a parser object.  if there isn't a parser object,
//  the yy_lex_rslt function creates the lex result value temporary itself.
					  
	if (yy_lex_cur_psr() != NULL) {
	    yy_lex_cur_psr()->yy_psr_rt_create_if_empty();
	    }

//  lex the input until done

        yy_lex_cur_psr() -> yy_psr_rt_type() = yylex();
        yy_lex_cur_psr() -> yy_psr_engine();
        } 

}   // yy_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_obj_lex::yy_lex_do_action(action_index)
//
//  yy_lex_do_action executes the action code in the grammar
//
//////////////////////////////////////////////////////////////////////////////

void yy_lex_obj_lex::yy_lex_do_action(
        int                     yy_lex_action_index)
{

    assert(yy_false);
    
}   // yy_lex_do_action


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_obj_lex::yy_lex_engine(action_index)
//
//  yy_lex_engine processes one token
//
//////////////////////////////////////////////////////////////////////////////

void yy_lex_obj_lex::yy_lex_engine(void)
{

//  create a lex result value if none exists.  note this only handles the
//  case when there is a parser object.  if there isn't a parser object,
//  the yy_lex_rslt function creates the lex result value temporary itself.
					  
	if (yy_lex_cur_psr() != NULL) {
	    yy_lex_cur_psr()->yy_psr_rt_create_if_empty();
	    }

//  lex the input

        yy_lex_cur_psr() -> yy_psr_rt_type() = yylex();
        yy_lex_cur_psr() -> yy_psr_engine();
    
}   // yy_lex_engine


yy_boolean yywrap(void)
{

return(1);

}
