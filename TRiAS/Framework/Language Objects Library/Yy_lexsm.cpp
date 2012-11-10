
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_lexsm
//
//  FILE DESCRIPTION:     small lexer object support
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	  Removed yy_no_myref_inlines_ as it didn't work with
//			  several compilers.
//    05/04/98   cc       extracted various sub-objects from the parser object.
//    10/17/94   bz/cc    fixed dependency on define yy_error_ with call
//                        to yy_psr_aborts_on_error()
//    09/29/94   bz/cc    fixed yy_trace_name for yy_trace_lex_rdc_.
//    10/25/93   bz/cc    initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_lexsm_c_ 
#define yy_lexsm_c_ 1
#endif /* yy_lexsm_c_ */

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
#include "yy_lexsm.h"
#include "yy_psr.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_obj_small::yy_lex_obj_small()
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_obj_small::yy_lex_obj_small(
    int                         yy_new_lex_min_type,
    int                         yy_new_lex_max_type,
    int                        *yy_new_lex_cmd,
    yy_lex_small_ptr            *yy_new_lex_dt,
    yy_inp_ptr                  yy_new_this_inp_obj,
    yy_symtab_ptr               yy_new_this_symtab_obj,
    int                        *yy_new_lex_start_state,
    int                         yy_new_lex_max_class,
    int                         yy_new_lex_class)
    : yy_lex_obj(
           yy_new_lex_min_type,
           yy_new_lex_max_type,
	   yy_new_lex_cmd,
           yy_new_this_inp_obj,
           yy_new_this_symtab_obj,
           yy_new_lex_start_state,
           yy_new_lex_max_class,
           yy_new_lex_class),
      yy_lex_dt(yy_new_lex_dt)
{
}  //  constructor for yy_lex_obj_small


//////////////////////////////////////////////////////////////////////////////
//
//  The following macros implement various internal actions taken by a Yacc++ 
//  lexer.
//
//  yy_lex_chg_macro    performs a lexer change state action.
//
//  yy_lex_epops_macro  performs a lexer epops action.
//
//  yy_lex_pop_macro    performs a lexer pop action.
//
//  yy_lex_push_macro   performs the start a sequence of shift actions for a 
//                      production.  We save the current state since the shift
//                      will cause us to change states and we will need to 
//                      return to this state after reducing the lexer nterm.
//
//  yy_lex_rdc_macro    performs a lexer token reduce action.  This empties
//                      the current token and either transmits it to the
//                      parser or discards it depending on the type.
//
//  yy_lex_rdc_nterm_macro 
//                      performs a lexical non-terminal reduce action.
//
//  yy_lex_read_lhead   assures that the look-ahead character has been read.
//
//  yy_lex_shf_macro1   shifts the next character in the lexer buffer.
//  yy_lex_shf_macro2  
//  yy_lex_shf_macro3  
//  yy_lex_shf_macro4  
//
//  yy_lex_shf_nterm_macro
//                      shifts a lexical non-terminal out of the lexer 
//                      look-ahead.
//
//  yy_lex_type_macro   starts a lexer reduce action by inserting the type of 
//                      the tkn_node into the lexer scratch area.
//
//  yy_lex_valid_rdc_ix 
//                      assures that the index to top of the parser scratch 
//                      area's reduce stack is valid (pointing within the 
//                      stack).
//
//////////////////////////////////////////////////////////////////////////////

#define yy_lex_read_lhead() if (yy_buf_lhead_unread()) { \
    if (yy_lex_is_done()) { return; } \
    if (yy_buf_lhead_char() != (int) EOF) { \
    if (!yy_buf_lhead_to_read()) { return; } \
    yy_buf_read_lhead(); } }

#define yy_lex_shf_macro1() if (yy_buf_lhead_char() != (int) EOF) { \
   if (yy_buf_unread_len() < 0) {

#define yy_lex_shf_macro2() yy_buf_extend();

#define yy_lex_shf_macro3() yy_buf_reset(); } } else { if (yy_lex_is_done()) { return; } } 

#define yy_lex_shf_macro4() yy_buf_mark_lhead_read();


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_engine(void)
//
//  yy_lex_ins() is the call-back lexer engine for lexing an array of
//  characters according to the rules in the grammar.  It executes the lexer
//  defined by the lexer tables generated by Yacc++.  It inserts characters
//  from the array into the lexer look-ahead and lexes them.  With each token
//  that is recognized, it calls yy_psr_ins with the type of token recognized
//  and the lexer semantic value variable yy_lex_rslt.  It lexes the number
//  of characters indicated by the parameter array_length and does not 
//  terminate prematurely when a null character ('\0') is seen.  Use the
//  strlen function for calculating the length when processing a null
//  terminated string.
//
//  yy_lex_array_to_insert      is the array of characters to lex.
//
//  yy_lex_array_length         is the number of characters in the character
//                              array to lex.  Use 0 to indicate EOF.
//
//  --------------------------------------------------------------------------
//
//  Algorithm
//
//  Start processing with the 1st character in the buffer.  If there is no
//  first character in the buffer, the lexer has reached the end of file and 
//  processes EOF as the character.  The initial buffer for the 1st file to
//  be read from was filled in by yy_inp_open.  The lexer indicies into this
//  buffer were set up by yy_lex_init.
//
//  Look up the character in the current state. The initial lexer state was
//  set up by yy_lex_init.
//
//  Loop in the lexer engine until one of the calls to the yy_lex_dt_cmd macro
//  causes the lexer to return.
//
//  Select and execute the appropriate lexer action.  There is one case for
//  each lexer opcode.  The mechanics of the lexer opcodes are handled by the 
//  macros defined in yy_lex.h.  Opcodes which end with "nx" differ from those
//  which don't in how the next lexer action is determined.  Opcodes which end
//  in "nx" have an operand which is the index to the next action.  Opcodes
//  which don't end in "nx" use the yy_lex_dt_cmd macro to determine the next
//  action.
//
//////////////////////////////////////////////////////////////////////////////

void yy_lex_obj_small::yy_lex_engine(void)
{
    char        yy_lex_save_char;
#if yy_trace_lex_rdc_ <= yy_trace_
    static char yy_trace_name[4096];
#endif
#ifdef yy_lex_inline_actions_
#include "yy_lex.loc"
#endif /* yy_lex_inline_actions_ */

//  look up the character in the current state

    assert(yy_buf_lhead_unread());

    if (yy_buf_lhead_to_read()) {
#if yy_trace_all_ <= yy_trace_
        yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
            "yy_lex_engine starting with a read");
#endif /* yy_trace_all_ <= yy_trace_ */
        yy_buf_read_lhead();
        }
    else if (yy_buf_eof_read()) {
#if yy_trace_all_ <= yy_trace_
        yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
            "yy_lex_engine starting with an eof");
#endif /* yy_trace_all_ <= yy_trace_ */
        yy_buf_read_eof_lhead();
        }
    else {
#if yy_trace_all_ <= yy_trace_
        yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
            "yy_lex_engine starting with an empty lookahead stream, but no eof");
#endif /* yy_trace_all_ <= yy_trace_ */
        return;
        }

    yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());

//  when recovering from a lexer error, skip until a token start is found

    if (yy_lex_error_flag()) {
        while (yy_lex_this_cmd()[0] == yy_lex_err_) {
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            }   // skip over erroneous characters
        yy_lex_error_flag() = yy_false;
        }

//  loop until a call to the yy_lex_dt_cmd macro causes this routine to return

    for (;;) {

        assert(0 < yy_lex_this_cmd()[0] && 
            yy_lex_this_cmd()[0] < yy_lex_num_of_opcs_);

#if yy_trace_actions_ <= yy_trace_
        sprintf(yy_trace_name, 
            "Lexer: for type %d, state %d, executing cmd[%d]->%s %d %d\n", 
            yy_buf_lhead_char(), yy_lex_state(), 
            yy_lex_this_cmd() - yy_lex_cmd(), 
            yy_lex_opc_tbl[yy_lex_this_cmd()[0]], yy_lex_this_cmd()[1], 
            yy_lex_this_cmd()[2]);
        yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), yy_trace_name);
#endif /* yy_trace_actions_ <= yy_trace_ */

//  select and execute the appropriate lexer action, 
//  one case for each lexer opcode

        switch (yy_lex_this_cmd()[0]) {

        default:

        // bad lexer opcode

            yy_err_report(404, yy_lex_this_cmd() - yy_lex_cmd(), 
                yy_lex_this_cmd()[0]);    
#if yy_trace_after_error_ <= yy_trace_
            yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
                "bad lexer opcode");
#endif /* yy_trace_after_error_ <= yy_trace_ */
            yy_lex_abort();
            return;

//  RISC actions (with no action code)

        case yy_lex_chg_:
            yy_lex_chg_macro(1);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_chg_nx_:
            yy_lex_chg_macro(1);
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(2);
            break;

        case yy_lex_epops_:
            yy_lex_epops_macro(1);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_epops_nx_:
            yy_lex_epops_macro(1);
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(2);
            break;

        case yy_lex_err_:
        case yy_lex_err_nx_:
            yy_lex_cur_psr()->yy_psr_error() = yy_true;
            yy_lex_save_char = yy_lex_token()[yy_lex_len()];
            yy_lex_token()[yy_lex_len()] = '\0';
            yy_err_report(110, yy_buf_lhead_char(), yy_lex_token());
            yy_lex_token()[yy_lex_len()] = yy_lex_save_char;
#if yy_trace_after_error_ <= yy_trace_
            yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
                "at lexer error action");
            yy_lex_cur_psr()->yy_psr_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
                "at lexer error action");
#endif /* yy_trace_after_error_ <= yy_trace_ */
            if (yy_lex_cur_psr()->yy_psr_aborts_on_error()) {
#if yy_trace_after_error_ <= yy_trace_
                yy_lex_cur_inp()->yy_inp_cur_err()->yy_err_puts(
                    "LEXER ABORTING...\n");
#endif /* yy_trace_after_error_ <= yy_trace_ */
                yy_lex_abort();
                return;
                }
#if yy_trace_after_error_ <= yy_trace_
            yy_lex_cur_inp()->yy_inp_cur_err()->yy_err_puts(
                "\nLexer inserting parser error_\n");
#endif /* yy_trace_after_error_ <= yy_trace_ */
	    yy_lex_cur_psr()->yy_psr_rt_type(0) = yy_error_;
            yy_lex_cur_psr()->yy_psr_engine();

            //  Try to recover from the lexical error.  
            //  First, see if it can start a token.  
            //  If it can't, we'll come here again and discard it. 

            if (yy_lex_state() != yy_lex_cur_start_state()) { 
                                         // reset to initial state
                yy_lex_state() = yy_lex_cur_start_state();
                yy_lex_rdc_ix = 0;
                }
            else {                      // discard the offending character
                yy_lex_read_lhead();
                yy_lex_shf_macro1();
                yy_lex_shf_macro2();
                yy_lex_shf_macro3();
                yy_lex_shf_macro4();
                }
            if (yy_lex_this_cmd()[0] == yy_lex_err_) {
                yy_lex_error_flag() = yy_true;
                yy_lex_read_lhead();
                yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), 
						yy_lex_state());
                while (yy_lex_this_cmd()[0] == yy_lex_err_) {
                    yy_lex_shf_macro1();
                    yy_lex_shf_macro2();
                    yy_lex_shf_macro3();
                    yy_lex_shf_macro4();
                    yy_lex_read_lhead();
                    yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), 
						    yy_lex_state());
                    }   // skip over erroneous characters
                yy_lex_error_flag() = yy_false;
                }
            else {
                yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(1);
                }
            break;

        case yy_lex_push_:
            yy_lex_push_macro();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_push_nx_:
            yy_lex_push_macro();
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(1);
            break;

        case yy_lex_rdc_:
            yy_lex_rdc_macro();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_rdc_nx_:
            yy_lex_rdc_macro();
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(1);
            break;

        case yy_lex_rdc_nterm_:
            yy_lex_rdc_nterm_macro();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_rdc_nterm_nx_:
            yy_lex_rdc_nterm_macro();
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(1);
            break;

        case yy_lex_shf_:
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_nx_:
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(1);
            break;

        case yy_lex_shf_nterm_:
            yy_lex_shf_nterm_macro();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_nterm_nx_:
            yy_lex_shf_nterm_macro();
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(1);
            break;

        case yy_lex_type_:
            yy_lex_type_macro(1);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_type_nx_:
            yy_lex_type_macro(1);
            yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(2);
            break;

//  CISC actions (with no action code)

        case yy_lex_push_shf_rdc_nterm_:
            yy_lex_push_macro();
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_type_macro(1);
            yy_lex_rdc_nterm_macro();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_rdc_chg_:
            yy_lex_type_macro(1);
            yy_lex_rdc_macro();
            yy_lex_chg_macro(2);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_chg_:
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_chg_macro(1);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_nterm_chg_:
            yy_lex_shf_nterm_macro();
            yy_lex_chg_macro(1);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_rdc_:
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_type_macro(1);
            yy_lex_rdc_macro();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_nterm_rdc_:
            yy_lex_shf_nterm_macro();
            yy_lex_type_macro(1);
            yy_lex_rdc_macro();
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_rdc_nterm_:
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_type_macro(1);
            yy_lex_rdc_nterm_macro();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

        case yy_lex_shf_rdc_chg_:
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_type_macro(1);
            yy_lex_rdc_macro();
            yy_lex_chg_macro(2);
            yy_lex_read_lhead();
            yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), yy_lex_state());
            break;

//  RISC and CISC actions with action code

        case yy_lex_shf_sact_:
        case yy_lex_shf_sact_chg_:
        case yy_lex_shf_sact_rdc_:
            yy_lex_read_lhead();
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            goto execute_act;

        case yy_lex_shf_ract_rdc_:
            yy_lex_read_lhead();
            yy_lex_shf_macro1();
            yy_lex_shf_macro2();
            yy_lex_shf_macro3();
            yy_lex_shf_macro4();
            yy_lex_type_macro(2);
            goto execute_act;

        case yy_lex_type_ract_rdc_:
            yy_lex_type_macro(2);
            // fall through 

        case yy_lex_ract_:
        case yy_lex_ract_nx_:
        case yy_lex_sact_:
        case yy_lex_sact_nx_:

execute_act:

            yy_lex_do_action(yy_lex_get_opnd(1));

            switch(yy_lex_this_cmd()[0]) {

            default:

            //  lexer opcode overwritten

                yy_err_report(405, yy_lex_this_cmd() - yy_lex_cmd(),
                    yy_lex_this_cmd()[0]); 
#if yy_trace_after_error_ <= yy_trace_
                yy_lex_dmp(yy_lex_cur_inp()->yy_inp_cur_err(), 
                    "lexer opcode overwritten");
#endif /* yy_trace_after_error_ <= yy_trace_ */
                yy_lex_abort();
                return;

            case yy_lex_shf_sact_chg_:
                yy_lex_chg_macro(2);
                yy_lex_read_lhead();
                yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), 
						yy_lex_state());
                break;

            case yy_lex_shf_sact_rdc_:
                yy_lex_type_macro(2);
                // fall through

            case yy_lex_shf_ract_rdc_:
                yy_lex_rdc_macro();
                yy_lex_read_lhead();
                yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), 
						yy_lex_state());
                break;

            case yy_lex_type_ract_rdc_:
                yy_lex_rdc_macro();
                // fall through

            case yy_lex_ract_:
            case yy_lex_sact_:
            case yy_lex_shf_sact_:
                yy_lex_read_lhead();
                yy_lex_this_cmd() = yy_lex_dt_cmd(yy_buf_lhead_char(), 
						yy_lex_state());
                break;

            case yy_lex_ract_nx_:
            case yy_lex_sact_nx_:
                yy_lex_this_cmd() = yy_lex_cmd() + yy_lex_get_opnd(2);
                break;

            }   // end switch

        }   // opcode switch statement

    }   // lexer inner interpreter loop on actions

}   // yy_lex_engine

#undef yy_lex_read_lhead

#undef yy_lex_shf_macro1

#undef yy_lex_shf_macro2

#undef yy_lex_shf_macro3

#undef yy_lex_shf_macro4
