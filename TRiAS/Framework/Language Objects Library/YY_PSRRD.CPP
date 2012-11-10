
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:              yy_psrrd
//
//  FILE DESCRIPTION:      parser object for Yacc++ readable parsing support
//
//  MODIFICATION HISTORY:
//
//  01/04/99	bz/cc	Removed yy_no_myref_inlines_ as it didn't work with
//			several compilers.
//  12/24/98	bz/cc	yy_psr_opc_tbl member is now function.
//  05/04/98	cc	extracted various sub-objects from the parser object.
//  04/21/97    bz      added runtime support for decision predicates parsing.
//  10/20/93    bz/cc   initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_psrrd_c_
#define yy_psrrd_c_ 1
#endif /* yy_psrrd_c_ */

#ifndef yy_psr_code_
#define yy_psr_code_ 1
#endif /* yy_psr_code_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_inp.h"
#include "yy_lex.h"
#include "yy_psrrd.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_obj_readable::yy_psr_obj_readable()
//
//  This is the constructor for the yy_psr_obj_readable which initializes the 
//  parser object.
//
//  yy_this_lex_obj_ptr    is the lexer which will supply tokens to the parser
//
//  yy_psr_new_class       is the parser class to create the object from
//
//  yy_psr_new_start       is the goal (start) symbol to parse
//
//  yy_psr_obj_readable() returns a new parser object from the specified
//  parser class.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_obj_readable::yy_psr_obj_readable(
    yy_boolean                  yy_new_psr_abort_on_error,
    int                         yy_new_psr_min_type,
    int                         yy_new_psr_max_type,
    int                         yy_new_psr_tkn_max_type,
    int                         *yy_new_psr_cmd,
    yy_psr_readable_ptr         *yy_new_psr_dt,
    yy_lex_ptr                  yy_new_lex_obj,
    int                         yy_new_psr_num_states,
    int                         *yy_new_syna_ix,
    int                         *yy_new_syna,
    char                        **yy_new_spelling_tbl,
    yy_psr_start_state_tbl      *yy_new_psr_start_state,
    int                         *yy_new_psr_last_start,
    const yy_ref_factory_obj    &yy_new_ref_factory,
    int                         yy_new_psr_max_class,
    int                         yy_new_psr_left_max,
    int                         yy_new_psr_rt_max,
    int                         yy_new_psr_rdc_max,
    int			    	yy_new_psr_bktrk_max,
    int			    	yy_new_psr_bktrk_stack_max
    )
    : yy_psr_obj(
        yy_new_psr_abort_on_error,
        yy_new_psr_min_type,
        yy_new_psr_max_type,
        yy_new_psr_tkn_max_type,
        yy_new_lex_obj,
        yy_new_psr_num_states,
	yy_new_psr_cmd,
        yy_new_syna,
        yy_new_spelling_tbl,
        yy_new_psr_start_state,
        yy_new_psr_last_start,
	yy_new_ref_factory,
        yy_new_psr_max_class,
        yy_new_psr_left_max,
        yy_new_psr_rt_max,
        yy_new_psr_rdc_max,
	yy_new_psr_bktrk_max,
	yy_new_psr_bktrk_stack_max
        ),
      yy_psr_dt(yy_new_psr_dt),
      yy_syna_ix(yy_new_syna_ix)
{
}  // constructor for yy_psr_obj_readable


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_display_expected()
//
//  yy_psr_display_expected() displays the expected tokens for the current
//  state.  These are the tokens that would be legal at this point in the
//  parse. 
//
//  It obtains the expected values by looking at every token entry in the
//  current state and determining which ones would not have given an error.
//  Note that because it directly accesses the parser tables, the access
//  code in this function is highly dependent on what type of tables were
//  generated -- fast, small, or readable -- and the algorithm used varies
//  accordingly.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_obj_readable::yy_psr_display_expected(
    )
{
    int     entry, expecteds;

//
//  accessing entries in a -table readable parser table
//
    expecteds = 0;
    for (entry = 1; entry <= yy_psr_tkn_max_type(); ++entry) {
        if (*(yy_psr_cmd()+(yy_psr_dt[(yy_psr_state())]->
			  yy_cmd_ix[(entry)-yy_psr_min_type()])) != 
	    yy_psr_err_) {
                if (expecteds == 0) {  // first one
                    yy_err_printf("Expected... %s", 
			yy_psr_spelling_tbl()[entry-yy_psr_min_type()]);
                    }
                else {
                    if (expecteds % 3 == 0) {
                        yy_err_printf("\n           ");
                        }
                    yy_err_printf(" or %s", 
			yy_psr_spelling_tbl()[entry-yy_psr_min_type()]);
                    }
            ++expecteds;
            }  // have a non-error entry in the parser table
        }
    yy_err_puts(".\n\n");

}   // yy_psr_display_expected()


//////////////////////////////////////////////////////////////////////////////
//
//  These macros are used internally to the parser to peform the parse.
//  
//  yy_psr_find_cmd     finds the next sequence of parser actions or returns 
//                      if there is none.  Used for actions which shifted a
//                      token.  This must remain a macro because it causes
//			the parser engine to return when the look-ahead is
//			exhausted.
//
//////////////////////////////////////////////////////////////////////////////

#define yy_psr_find_cmd(type, state)     \
    if (yy_psr_rt_empty() && (!yy_psr_bktrk_read())) { \
	yy_psr_rt_create(); return; } \
    yy_psr_this_cmd() = yy_psr_dt_cmd(type, state);


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_engine()
//
//  yy_psr_engine_primitive is the parser engine.  It processes a token at a
//  time, performing all parser actions such as shifting and reducing 
//  according to the rules defined by the parser tables generated by Yacc++.  
//
//  -----------------------------------------------------------------------
//
//  This routine always completely empties the parser's right-hand-side,
//  consuming all look-ahead tokens therein.  Therefore, this can be used
//  in a loop whose invariant is that the parser rhs is empty and whose
//  termination condition is that there are no un-inserted look-ahead 
//  tokens.  (The correctness and termination of this routine are dependent 
//  on the correctness of the Yacc++ generated tables.)
//
//  -----------------------------------------------------------------------
//
//  yy_psr_engine is the new interface to the parser engine.  
//
//  It is designed to lower the overhead of parsing by reducing the
//  number of times entries are copied into the parser right-hand-side
//  and then from the right to the left-hand-side.  This is done by
//  having the lexer engine use the insertion point in the
//  right-hand-side as its definition of the lexer result value.
//
//  This version of the engine, thus calls the engine primitive to empty
//  the right-hand-side and then before returning creates a new slot in
//  the right-hand-side for the next token the lexer wishes to create.
//
//  The reason this is done in the parser object rather than the lexer
//  object is so that the lexer object can avoid all references to the
//  users union (yy_ref_obj) and thus aviod union size and output union
//  header name dependencies.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_obj_readable::yy_psr_engine(void)
{

#if yy_trace_psr_rdc_ <= yy_trace_
    yy_err_printf("      received  %s [%d]\n", 
	yy_psr_spelling_tbl()[yy_psr_rt_type() - yy_psr_min_type()],
	yy_psr_rt_type());
#endif

//  If backtracking is enabled, add this token to the backtracking 
//  token list for later re-parsing.

    switch (yy_psr_bktrk_mode()) {
        default: 
	    yy_err_report(409, yy_psr_bktrk_mode());
	    yy_assert_fail("unknown backtracking mode", __FILE__, __LINE__);
	    
	case(yy_psr_done_bktrk_):
	case(yy_psr_no_bktrk_):
	case(yy_psr_read_bktrk_):
	    break;
	    
	case(yy_psr_copy_bktrk_):
	    yy_psr_bktrk_mode() = yy_psr_ins_bktrk_;
	    
	case(yy_psr_ins_bktrk_):
	    yy_psr_bktrk_queue_push(yy_psr_rt_top());
#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp("Saving a backtrack token");
#endif
	    break;
        }

//
//    Inner interpreter loop which performs the parser actions.
//
//    A cmd_node contains the opcode for the action to be performed 
//    and contains the necessary operands.
//

    yy_psr_this_cmd() = yy_psr_dt_cmd(yy_psr_rt_type(), yy_psr_state());

    for (;;) {

        assert(0 < yy_psr_this_cmd()[0] &&
	       yy_psr_this_cmd()[0] < yy_psr_num_of_opcs_);

#if yy_trace_psr_actions_ <= yy_trace_
    {
        static char yy_trace_name[4096];
	yy_assert_disable();
        sprintf(yy_trace_name, 
		"Parser: for type %d, state %d, executing cmd[%d]->%s %d %d\n", 
		yy_psr_rt_type(), yy_psr_state(), 
		yy_psr_this_cmd()-yy_psr_cmd(), 
		yy_psr_opc_tbl()[yy_psr_this_cmd()[0]], yy_psr_this_cmd()[1],
		yy_psr_this_cmd()[2]);
	yy_psr_dmp(yy_trace_name);
	yy_assert_enable();
    }
#endif /* yy_trace_psr_actions_ <= yy_trace_ */

        switch (yy_psr_this_cmd()[0]) {

        default:

        // bad parser opcode

            yy_err_report(402, yy_psr_this_cmd() - yy_psr_cmd(), 
                yy_psr_this_cmd()[0]);

#if yy_trace_after_error_ <= yy_trace_
            yy_psr_dmp("bad parser opcode");
#endif
            yy_psr_abort();
	    yy_psr_rt_create_if_empty();
            return;

        case yy_psr_shf_acpt_:
            yy_psr_shf();
            // fall through

        case yy_psr_acpt_:
        case yy_psr_acpt_nx_:
            yy_psr_acpt();
	    yy_psr_rt_create_if_empty();
            return;

        case yy_psr_push_shf_chg_:
            yy_psr_push();
            // fall through

        case yy_psr_shf_chg_:
            yy_psr_shf();
            // fall through

        case yy_psr_chg_:
            yy_psr_chg(1);
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_chg_nx_:
            yy_psr_chg(1);
            yy_psr_next_cmd(2);
            break;

        case yy_psr_epops_:
            yy_psr_pop(1);
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_epops_nx_:
            yy_psr_pop(1);
            yy_psr_next_cmd(2);
            break;

        case yy_psr_err_:
        case yy_psr_err_nx_:
            yy_psr_error() = yy_true;
#if yy_trace_after_error_ <= yy_trace_
            yy_psr_dmp("parser error action");
#endif /* yy_trace_after_error_ <= yy_trace_ */
            yy_psr_err();
            if (yy_psr_aborts_on_error()) {
                yy_psr_abort();
		yy_psr_rt_create_if_empty();
                return;
                }
#ifdef yy_psr_err_no_overwrite_
            yy_psr_err_sync(yy_psr_rt_type(), yy_false);
#else
            yy_psr_err_sync(yy_psr_rt_type(), yy_true);
#endif /* yy_psr_err_no_overwrite_ */
            if (yy_psr_this_cmd()[0] == yy_psr_err_nx_) {
                yy_psr_next_cmd(1);
                break;
                }
            yy_psr_this_cmd() = yy_psr_dt_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_bktrk_push_:
            yy_psr_bktrk_push();
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_bktrk_push_nx_:
            yy_psr_bktrk_push();
            yy_psr_next_cmd(1);
            break;

        case yy_psr_bktrk_pop_:
            yy_psr_bktrk_pop();
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_bktrk_pop_nx_:
            yy_psr_bktrk_pop();
            yy_psr_next_cmd(1);
            break;

        case yy_psr_bktrk_redo_:
            yy_psr_bktrk_redo();
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_bktrk_redo_nx_:
            yy_psr_bktrk_redo();
            yy_psr_next_cmd(1);
            break;

        case yy_psr_ign_:
            yy_psr_ign();
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_ign_nx_:
            yy_psr_ign();
            yy_psr_next_cmd(1);
            break;

        case yy_psr_ign_chg_:
            yy_psr_ign();
            yy_psr_chg(1);
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_push_:
            yy_psr_push();
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_push_nx_:
            yy_psr_push();
            yy_psr_next_cmd(1);
            break;

        case yy_psr_push_chg_:
            yy_psr_push();
            yy_psr_chg(1);
            yy_psr_this_cmd() = yy_psr_dt_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_rdc_:
#if yy_trace_psr_actions_ <= yy_trace_
            yy_psr_dmp("parser reduce action");
#endif
            yy_psr_do_rdc(1);
#if yy_trace_psr_rdc_ <= yy_trace_
	    yy_err_printf("parser reduced  %s [%d]\n", 
		yy_psr_spelling_tbl()[yy_psr_rt_type() - yy_psr_min_type()],
		yy_psr_rt_type());
#endif
            yy_psr_this_cmd() = yy_psr_dt_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_rdc_nx_:
#if yy_trace_psr_actions_ <= yy_trace_
            yy_psr_dmp("parser reduce action");
#endif
            yy_psr_do_rdc(1);
#if yy_trace_psr_rdc_ <= yy_trace_
	    yy_err_printf("parser reduced  %s [%d]\n", 
		yy_psr_spelling_tbl()[yy_psr_rt_type() - yy_psr_min_type()],
		yy_psr_rt_type());
#endif
            yy_psr_next_cmd(2);
            break;

        case yy_psr_shf_:
            yy_psr_shf();
            yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_shf_nx_:
            yy_psr_shf();
            yy_psr_next_cmd(1);
            break;

        case yy_psr_push_shf_rdc_:
            yy_psr_push();
            // fall through

        case yy_psr_shf_rdc_:
            yy_psr_shf();
#if yy_trace_psr_actions_ <= yy_trace_
            yy_psr_dmp("parser shift/reduce action");
#endif
            yy_psr_do_rdc(1);
#if yy_trace_psr_rdc_ <= yy_trace_
	    yy_err_printf("parser reduced  %s [%d]\n", 
		yy_psr_spelling_tbl()[yy_psr_rt_type() - yy_psr_min_type()],
		yy_psr_rt_type());
#endif
            yy_psr_this_cmd() = yy_psr_dt_cmd(yy_psr_rt_type(), yy_psr_state());
            break;

        case yy_psr_push_shf_sact_chg_:
        case yy_psr_push_shf_ract_rdc_:
        case yy_psr_push_shf_sact_rdc_:
            yy_psr_push();
            // fall through
            
        case yy_psr_shf_ract_rdc_:
        case yy_psr_shf_sact_chg_:
        case yy_psr_shf_sact_rdc_:
            yy_psr_shf();
            // fall through

        case yy_psr_ract_:
        case yy_psr_sact_:
        case yy_psr_ract_nx_:
        case yy_psr_sact_nx_:
        case yy_psr_ract_rdc_:
        case yy_psr_sact_rdc_:

#if yy_trace_psr_user_actions_ <= yy_trace_
            yy_psr_dmp("before user action code");
#endif
            yy_psr_do_action(yy_psr_get_opnd(1));
#if yy_trace_psr_user_actions_ <= yy_trace_
            yy_psr_dmp("after user action code");
#endif

            switch (yy_psr_this_cmd()[0]) {

                case yy_psr_ract_nx_:
                case yy_psr_sact_nx_:
                    yy_psr_next_cmd(2);
                    break;

                case yy_psr_ract_:
                case yy_psr_sact_:
                    yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
                    break;

                case yy_psr_push_shf_sact_chg_:
                case yy_psr_shf_sact_chg_:
                    yy_psr_chg(2);
                    yy_psr_find_cmd(yy_psr_rt_type(), yy_psr_state());
                    break;

                case yy_psr_push_shf_ract_rdc_:
                case yy_psr_push_shf_sact_rdc_:
                case yy_psr_shf_ract_rdc_:
                case yy_psr_shf_sact_rdc_:
                case yy_psr_ract_rdc_:
                case yy_psr_sact_rdc_:
#if yy_trace_psr_actions_ <= yy_trace_
                    yy_psr_dmp("parser action reduce action");
#endif
                    yy_psr_do_rdc(2);
#if yy_trace_psr_rdc_ <= yy_trace_
		    yy_err_printf("parser reduced  %s [%d]\n", 
			yy_psr_spelling_tbl()[yy_psr_rt_type() - yy_psr_min_type()],
			yy_psr_rt_type());
#endif
                    yy_psr_this_cmd() = 
			yy_psr_dt_cmd(yy_psr_rt_type(), yy_psr_state());
                    break;

                default:

                // parser opcode overwritten

                    yy_err_report(403, yy_psr_this_cmd() - yy_psr_cmd(),
                        yy_psr_this_cmd()[0]); 

#if yy_trace_after_error_ <= yy_trace_
                    yy_psr_dmp("parser opcode overwritten");
#endif
		    yy_psr_abort();
		    yy_psr_rt_create_if_empty();
                    return;
                
                }   // end inner switch of opc for act... cases
            break;

            }   // opcode switch statement

        }   // for (;;)

}   // yy_psr_engine

#undef yy_psr_find_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_err(void);
//
//  yy_psr_err reports a syntax error to the user based on the current 
//  parser state variables.
//
//  yy_ths_psr_obj  is the parser object which was directing the parse 
//                  which encountered the error.
//
//  yy_psr_err has no return value.
//
//  -------------------------------------------------------------------------
//
//  algorithm:
//
//    display line number, text and position within line of error
//
//    display psr state and tkn type (for debugging only)
//
//    for -assist, display syntax strings for productions being built 
//    in the current state
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_obj_readable::yy_psr_err()
{
    char                temp_char;
    char                *end_char;
    int                 num_synas, start_ix, *start_syna;

//  display line number and token

    end_char = &(yy_psr_cur_lex()->yy_lex_token()
            [yy_psr_cur_lex()->yy_lex_len()]);
    temp_char = *end_char;
    *end_char = '\0';

//  when yy_err_report returns 0 we have the very odd case of 
//  not displaying the syntax error due to min_display

    if (yy_err_report(100, yy_psr_cur_lex()->yy_lex_token()) == 0) {
        *end_char = temp_char;
        return;
        }

    *end_char = temp_char;

    // display the legal expected values, then the syntax assists

    yy_psr_display_expected();

    if (yy_syna_ix != NULL) {

        start_ix = yy_psr_dt_err(yy_psr_state());
        start_syna = yy_psr_syna() + start_ix;
        num_synas = yy_psr_syna()[start_ix - 1];

        while (num_synas > 0) {
	    yy_err_syntax_assist(*start_syna);
            --num_synas;
            ++start_syna;
            }

        yy_err_puts("\n");
        }

#if yy_trace_after_error_ <= yy_trace_
    yy_psr_dmp("parser error");
#endif

}   // yy_psr_err
