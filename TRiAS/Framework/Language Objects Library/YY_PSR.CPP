
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:              yy_psr
//
//  FILE DESCRIPTION:      parser object for Yacc++ parsing support
//
//  MODIFICATION HISTORY:
//
//  01/04/99    bz/cc	Removed yy_no_myref_inlines_ as it didn't work with
//			several compilers.
//  05/04/98	cc	extracted various sub-objects from the parser object.
//                      added casts to quiet HP compiler which now complains
//			about initialization of char * arrays with uncast
//			literals.
//  09/11/97	bz   	moved limits to header for ANSI C++ header support.
//  04/21/97	bz   	added runtime support for decision predicates parsing.
//  03/08/94	bz   	fixed memory leaks for parser stack work areas in
//		     	destructor for the parser base object.
//  07/07/93	bz   	native C++ rewrite of the parser object.
//  06/21/93	bz   	added display of state based expected values along
//		     	with syntax assist display in yy_psr_err().  New
//		     	function is yy_psr_display_expected().
//  04/05/93	bz   	yy_err_set_location() no longer exists -- there
//		     	are now location objects which are stacked with
//		     	the error objects.  Also, new forwarding scheme
//		     	for yy_err_report().
//  03/05/93	bz   	initialize parser object data member 
//		     	yy_psr_abort_on_error to false when yy_error 
//		     	synchronization is present in the parser object.  
//		     	This uninitialized member was randomly causing 
//		     	premature aborts on error synchronization.
//  08/07/92	bz   	removed macros and #ifdefs in C++ only version.
//  02/08/92	bz   	change yy_psr_dmp reference to yy_psr_dmp_this.  
//  01/10/92	cc   	rev 1.4 -- changes for separate compilation 
//		     	of actions.
//  03/30/90	bz/cc	coding and review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_psr_c_
#define yy_psr_c_ 1
#endif /* yy_psr_c_ */

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
#include "yy_psr.h"


//////////////////////////////////////////////////////////////////////////////
//
//  STATIC FIELD INITIALIZATIONS:
//
//  yy_psr_last_obj_ptr     static initialized to NULL
//
//  yy_psr_opc_tbl          static initialized to spellings of opcodes for
//                          use by traces in code
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_ptr yy_far yy_psr_obj::yy_psr_last_obj_ptr = NULL;

char * yy_far yy_psr_static_obj::yy_this_psr_opc_tbl[
    yy_psr_static_obj::yy_psr_num_of_opcs_] 
        = { 
	   (char *)" 0 is not used ",
	   (char *)"yy_psr_acpt_",
	   (char *)"yy_psr_acpt_nx_",
	   (char *)"yy_psr_chg_",
	   (char *)"yy_psr_chg_nx_",
	   (char *)"yy_psr_epops_",
	   (char *)"yy_psr_epops_nx_",
	   (char *)"yy_psr_err_",
	   (char *)"yy_psr_err_nx_",
	   (char *)"yy_psr_ign_",
	   (char *)"yy_psr_ign_nx_",
	   (char *)"yy_psr_push_",
	   (char *)"yy_psr_push_nx_",
	   (char *)"yy_psr_ract_",
	   (char *)"yy_psr_ract_nx_",
	   (char *)"yy_psr_rdc_",
	   (char *)"yy_psr_rdc_nx_",
	   (char *)"yy_psr_sact_",
	   (char *)"yy_psr_sact_nx_",
	   (char *)"yy_psr_shf_",
	   (char *)"yy_psr_shf_nx_",
	   (char *)"yy_psr_ign_chg_",
	   (char *)"yy_psr_push_chg_",
	   (char *)"yy_psr_push_shf_chg_",
	   (char *)"yy_psr_push_shf_ract_rdc_",
	   (char *)"yy_psr_push_shf_rdc_",
	   (char *)"yy_psr_push_shf_sact_chg_",
	   (char *)"yy_psr_push_shf_sact_rdc_",
	   (char *)"yy_psr_ract_rdc_",
	   (char *)"yy_psr_sact_rdc_",
	   (char *)"yy_psr_shf_acpt_",
	   (char *)"yy_psr_shf_chg_",
	   (char *)"yy_psr_shf_ract_rdc_",
	   (char *)"yy_psr_shf_rdc_",
	   (char *)"yy_psr_shf_sact_chg_",
	   (char *)"yy_psr_shf_sact_rdc_",
	   (char *)"yy_psr_bktrk_push_",
	   (char *)"yy_psr_bktrk_push_nx_",
	   (char *)"yy_psr_bktrk_pop_",
	   (char *)"yy_psr_bktrk_pop_nx_",
	   (char *)"yy_psr_bktrk_redo_",
	   (char *)"yy_psr_bktrk_redo_nx_",
            };
        

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_static_obj::yy_psr_static_obj()
//
//  This is the constructor for the yy_psr_static_obj which initializes the 
//  static part of the parser object.
//
//  yy_this_lex_obj_ptr    is the lexer which will supply tokens to the parser
//
//  yy_psr_new_class       is the parser class to create the object from
//
//  yy_psr_new_start       is the goal (start) symbol to parse
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_static_obj::yy_psr_static_obj(
    const yy_ref_factory_obj    &yy_new_ref_factory,
    yy_lex_ptr                  yy_new_lex_obj,
    int                         yy_new_psr_min_type,
    int                         yy_new_psr_max_type,
    int                         yy_new_psr_tkn_max_type,
    int                         yy_new_psr_num_states,
    int                         yy_new_psr_max_class,
    int                         *yy_new_psr_cmd,
    int                         *yy_new_syna,
    int                         *yy_new_psr_last_start,
    yy_psr_start_state_tbl      *yy_new_psr_start_state,
    char * yy_far               *yy_new_spelling_tbl)
    : yy_this_ref_factory(yy_new_ref_factory),
      yy_this_lex_obj(yy_new_lex_obj),
      yy_this_psr_min_type(yy_new_psr_min_type),
      yy_this_psr_max_type(yy_new_psr_max_type),
      yy_this_psr_tkn_max_type(yy_new_psr_tkn_max_type),
      yy_this_psr_num_states(yy_new_psr_num_states),
      yy_this_psr_max_class(yy_new_psr_max_class),      
      yy_this_psr_cmd(yy_new_psr_cmd),
      yy_this_psr_syna(yy_new_syna),
      yy_this_psr_last_start(yy_new_psr_last_start),
      yy_this_psr_start_state(yy_new_psr_start_state),
      yy_this_psr_spelling_tbl(yy_new_spelling_tbl)
{
}   // constructor for yy_psr_static_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_static_obj::~yy_psr_static_obj()
//
//  This is the destructor for the static part of the base class parser
//  object.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_static_obj::~yy_psr_static_obj() 
{
}   // destructor for yy_psr_static_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_dynamic_obj::yy_psr_dynamic_obj()
//
//  This is the constructor for the yy_psr_dynamic_obj which initializes the 
//  dynamic part of the parser object.
//
//  yy_this_lex_obj_ptr    is the lexer which will supply tokens to the parser
//
//  yy_psr_new_class       is the parser class to create the object from
//
//  yy_psr_new_start       is the goal (start) symbol to parse
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_dynamic_obj::yy_psr_dynamic_obj(
    yy_boolean                  yy_new_psr_aborts_on_error)
{
    yy_psr_dynamic_data.yy_this_psr_aborts_on_error = 
	yy_new_psr_aborts_on_error;

    yy_psr_dynamic_data.yy_this_psr_is_done = yy_false;
    
    yy_psr_dynamic_data.yy_this_psr_err_value = 0;
    
    yy_psr_dynamic_data.yy_this_psr_state = 0;
    
    yy_psr_dynamic_data.yy_this_psr_class = 0;
    
    yy_psr_dynamic_data.yy_this_psr_start_sym = 0;
    
    yy_psr_dynamic_data.yy_this_psr_cur_start_state = 0;
    
    yy_psr_dynamic_data.yy_this_psr_cmd = 0;
    
    yy_psr_dynamic_data.yy_this_psr_bktrk_mode = yy_const::yy_psr_no_bktrk_;
    
}   // constructor for yy_psr_dynamic_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_dynamic_obj::~yy_psr_dynamic_obj()
//
//  This is the destructor for the dynamic part of the base class parser
//  object.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_dynamic_obj::~yy_psr_dynamic_obj() 
{
}   // destructor for yy_psr_dynamic_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_obj::yy_psr_obj()
//
//  This is the constructor for the yy_psr_obj which initializes the 
//  parser object.
//
//  yy_this_lex_obj_ptr    is the lexer which will supply tokens to the parser
//
//  yy_psr_new_class       is the parser class to create the object from
//
//  yy_psr_new_start       is the goal (start) symbol to parse
//
//  yy_psr_obj() returns a new parser object from the specified parser class.
//
//  Note: this function does not create backtracking areas by default.
//  This conserves resources for the majority of grammars which do not
//  contain syntactic decision predicates, the only need for the 
//  backtracking areas.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_obj::yy_psr_obj(
    yy_boolean                  yy_new_psr_abort_on_error,
    int                         yy_new_psr_min_type,
    int                         yy_new_psr_max_type,
    int                         yy_new_psr_tkn_max_type,
    yy_lex_ptr                  yy_new_lex_obj,
    int                         yy_new_psr_num_states,
    int                         *yy_new_psr_cmd,
    int                         *yy_new_syna,
    char                        **yy_new_spelling_tbl,
    yy_psr_start_state_tbl      *yy_new_psr_start_state,
    int                         *yy_new_psr_last_start,
    const yy_ref_factory_obj	&yy_new_ref_factory,
    int                         yy_new_psr_max_class,
    int                         yy_new_psr_left_max,
    int                         yy_new_psr_rt_max,
    int                         yy_new_psr_rdc_max,
    int			    	yy_new_psr_bktrk_max,
    int			    	yy_new_psr_bktrk_stack_max)
    : yy_psr_static_part(yy_new_ref_factory, yy_new_lex_obj,
			 yy_new_psr_min_type, yy_new_psr_max_type, 
			 yy_new_psr_tkn_max_type, yy_new_psr_num_states, 
			 yy_new_psr_max_class, yy_new_psr_cmd, yy_new_syna, 
			 yy_new_psr_last_start, yy_new_psr_start_state, 
			 yy_new_spelling_tbl),
      yy_psr_dynamic_part(yy_new_psr_abort_on_error),
      yy_psr_stack_part(yy_new_ref_factory, yy_new_psr_left_max),
      yy_psr_rdc_stack_part(yy_new_ref_factory, yy_new_psr_rdc_max),
      yy_psr_bktrk_queue_part(yy_new_ref_factory, yy_new_psr_bktrk_max),
      yy_psr_bktrk_stack_part(yy_new_psr_bktrk_stack_max)
{

//  connect the remaining pointers which we know the correct values for

    yy_psr_last_obj_ptr = this;

    if (yy_psr_cur_lex() != NULL) {
	yy_psr_cur_lex()->yy_lex_cur_psr() = this;
	}

}   // constructor for yy_psr_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_obj::~yy_psr_obj()
//
//  This is the destructor for the base class parser object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_obj::~yy_psr_obj()
{
    yy_psr_static_part.~yy_psr_static_obj();
    yy_psr_dynamic_part.~yy_psr_dynamic_obj();
    yy_psr_stack_part.~yy_psr_stack_obj();
    yy_psr_rdc_stack_part.~yy_psr_rdc_stack_obj();
    yy_psr_bktrk_queue_part.~yy_psr_bktrk_queue_obj();
    yy_psr_bktrk_stack_part.~yy_psr_bktrk_stack_obj();

}   // destructor for yy_psr_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_dmp(yy_this_err_obj, yy_dmp_title)
//
//  yy_psr_dmp() displays the values of the parser state variables.
//  The calls to yy_psr_dmp() in yy_psr.cpp are conditionally compiled based
//  on the setting of yy_trace_.  The parser object contains this display
//  function in case you need to see the internal state of the parser engine
//  as your application is parsing (for purposes of debugging).
//
//  yy_this_err_obj  is an error object where this dump is to be displayed.
//           
//  yy_dmp_title  a character string to identify the dump.  For example, 
//                sometimes you might want to identify your symbol table dump
//                with the breakpoint location.  Otherwise, just pass in NULL.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_obj::yy_psr_dmp(
    yy_err_ptr   yy_this_err_obj, 
    const char   *yy_dmp_title)    
{
    size_t                     	ref_ix;
    size_t                     	rdc_ix;
    size_t			stack_ix;
    
//  Temporarily disable assertions.

    yy_assert_disable();
    
//  use the failsafe error object, if no error object to dump to
//  if there is no failsafe error object, give up

    if (yy_this_err_obj == NULL) {
        yy_this_err_obj = yy_err_failsafe_obj();
	if (yy_this_err_obj == NULL) return;
        }

//  display the title for the dump, if any

    if (yy_dmp_title != NULL) {
        yy_this_err_obj->yy_err_printf("TITLE: %s\n", yy_dmp_title);
        }

    yy_this_err_obj->yy_err_puts("Contents of the PARSER STACK\n");

//  display the parser state and backtracking mode

    yy_this_err_obj->yy_err_printf("    state %d", 
	yy_psr_state());

    switch (yy_psr_bktrk_mode()) {
        default: 
	    yy_this_err_obj->yy_err_printf("\tbktrk mode %d invalid\n", 
		yy_psr_bktrk_mode());
	    break;

	case(yy_psr_no_bktrk_):
	    yy_this_err_obj->yy_err_printf("\tno bktrk\n");
	    break;
	    
	case(yy_psr_ins_bktrk_):
	    yy_this_err_obj->yy_err_printf("\tbktrk ins\n");
	    break;

	case(yy_psr_copy_bktrk_):
	    yy_this_err_obj->yy_err_printf("\tbktrk copy\n");
	    break;

	case(yy_psr_read_bktrk_):
	    yy_this_err_obj->yy_err_printf("\tbktrk read\n");
	    break;

	case(yy_psr_done_bktrk_):
	    yy_this_err_obj->yy_err_printf("\tbktrk done\n");
	    break;

	}

// display the left area (with reduces entries mixed in)

    rdc_ix = 0;

    if (0 < yy_psr_left_entries()) {
	yy_this_err_obj->yy_err_printf("    left[0..%d]\n", 
				     yy_psr_left_entries());
	for (ref_ix = 0; ref_ix <= yy_psr_left_entries(); ++ref_ix) {
	    if ((rdc_ix <= yy_psr_rdc_stack_entries()) &&
		(yy_psr_rdc_start(rdc_ix) == ref_ix)) {
		while ((rdc_ix <= yy_psr_rdc_stack_entries()) &&
		       (yy_psr_rdc_start(rdc_ix) == ref_ix)) {
		    yy_this_err_obj->yy_err_printf(
			"\tstart[%d]->%d value %d\n",
			rdc_ix, yy_psr_rdc_state(rdc_ix), 
			yy_psr_rslt_int(rdc_ix));
		    ++rdc_ix;
		    }
		}
	    if (ref_ix == yy_psr_left_entries()) {
		yy_this_err_obj->yy_err_printf("\tafter end:\n");
		}
	    if (yy_psr_valid_type(yy_psr_left_type(ref_ix))) {
		yy_this_err_obj->yy_err_printf("\t    %s ", 
		    yy_psr_spelling_tbl()[
			yy_psr_left_type(ref_ix) - yy_psr_min_type()]);
		}
	    else {
		yy_this_err_obj->yy_err_printf( "\t    invalid type %d ", 
		    yy_psr_left_type(ref_ix));
		}
	    yy_this_err_obj->yy_err_printf("%d\n", yy_psr_left_int(ref_ix));
	    }
        yy_this_err_obj->yy_err_puts("\n");
        }
    
// display any left over reduce entries, although there shouldn't be any

    if (rdc_ix <= yy_psr_rdc_stack_entries()) {
	yy_this_err_obj->yy_err_printf("    rdc[%d..%d]\n", rdc_ix, 
	    yy_psr_rdc_stack_entries());
	while (rdc_ix <= yy_psr_rdc_stack_entries()) {
            yy_this_err_obj->yy_err_printf(
		"\t[%d] start %d->%d value %d\n", rdc_ix, 
		yy_psr_rdc_start(rdc_ix), yy_psr_rdc_state(rdc_ix), 
		yy_psr_rslt_int(rdc_ix));
	    ++rdc_ix;
	    }
        yy_this_err_obj->yy_err_puts("\n");
	}
    
// display the right area

    if (0 < yy_psr_rt_entries()) {
	yy_this_err_obj->yy_err_printf("    rt[%d..0]", 
	    yy_psr_rt_entries());
	switch (yy_psr_stack_layout()) {
	    default:
		yy_this_err_obj->yy_err_printf("\tstack layout %d invalid\n", 
		    yy_psr_stack_layout());
		break;

	    case(yy_psr_stack_left_and_rt_empty_):
		yy_this_err_obj->yy_err_printf("\tleft and rt empty\n");
		break;

	    case(yy_psr_stack_rt_empty_):
		yy_this_err_obj->yy_err_printf("\trt empty\n");
		break;

	    case(yy_psr_stack_left_and_rt_joined_):
		yy_this_err_obj->yy_err_printf("\tleft and rt joined\n");
		break;

	    case(yy_psr_stack_left_and_rt_split_):
		yy_this_err_obj->yy_err_printf("\tleft and rt split\n");
		break;
	}
	ref_ix = yy_psr_rt_entries() - 1;
	for (;;) {
	    if (yy_psr_valid_type(yy_psr_rt_type(ref_ix))) {
		yy_this_err_obj->yy_err_printf("\t    %s ", 
		    yy_psr_spelling_tbl()[
			yy_psr_rt_type(ref_ix) - 
			yy_psr_min_type()]);
		}
	    else {
		yy_this_err_obj->yy_err_printf( "\t    invalid type %d ", 
		    yy_psr_rt_type(ref_ix));
		}
	    yy_this_err_obj->yy_err_printf("%d\n", yy_psr_rt_int(ref_ix));
	    if (ref_ix <= 0) break;
	    --ref_ix;
	    }
        yy_this_err_obj->yy_err_puts("\n");
        }
    
// dump the backtracking area if it is active

    switch (yy_psr_bktrk_mode()) {
	case(yy_psr_no_bktrk_):
	    break;
	    
        default: 
	case(yy_psr_ins_bktrk_):
	case(yy_psr_copy_bktrk_):
	case(yy_psr_read_bktrk_):
	case(yy_psr_done_bktrk_):
	    // display the backtrack queue with backtrack stack entries 
	    // mixed in

	    stack_ix = 0;

	    if (0 < yy_psr_bktrk_queue_entries()) {
		yy_this_err_obj->yy_err_printf(
		    "    bktrk[0..%d..%d]\n", 
		    yy_psr_bktrk_queue_read_ix(), 
		    yy_psr_bktrk_queue_entries());
		for (ref_ix = 0; ref_ix < yy_psr_bktrk_queue_entries(); 
		     ++ref_ix) {
		    if ((stack_ix <= yy_psr_bktrk_stack_entries()) &&
			(yy_psr_bktrk_start(stack_ix) == ref_ix)) {
			while ((stack_ix < yy_psr_bktrk_stack_entries()) &&
			       (yy_psr_bktrk_start(stack_ix) == ref_ix)) {
			    yy_this_err_obj->yy_err_printf(
				"\tstart[%d]:\n", stack_ix);
			    ++stack_ix;
			    }
			}
		    else if (ref_ix == yy_psr_bktrk_queue_entries()) {
			yy_this_err_obj->yy_err_printf("\tafter end:\n");
			}
		    if (yy_psr_valid_type(yy_psr_bktrk_queue_type(ref_ix))) {
			yy_this_err_obj->yy_err_printf("\t    %s ", 
			    yy_psr_spelling_tbl()[
				yy_psr_bktrk_queue_type(ref_ix) - 
				yy_psr_min_type()]);
			}
		    else {
			yy_this_err_obj->yy_err_printf(
			    "\t    invalid type %d ", 
			    yy_psr_bktrk_queue_type(ref_ix));
			}
		    yy_this_err_obj->yy_err_printf("%d\n", 
			    yy_psr_bktrk_queue_int(ref_ix));
		    }
		yy_this_err_obj->yy_err_puts("\n");
	        }

	    // display any left over stack entries, 
	    // although there shouldn't be any

	    if (stack_ix < yy_psr_bktrk_stack_entries()) {
		yy_this_err_obj->yy_err_printf(
		    "    bktrk stack[%d..%d]\n", 
		    stack_ix, yy_psr_bktrk_stack_entries());
		while (stack_ix < yy_psr_bktrk_stack_entries()) {
		    yy_this_err_obj->yy_err_printf("\tstart[%d]: %d\n", 
			stack_ix, yy_psr_bktrk_start(stack_ix));
		    ++stack_ix;
		    }
		yy_this_err_obj->yy_err_puts("\n");
		}
        }

//  display the contents of the lexer too

    if (yy_psr_cur_lex() != NULL) {
        yy_psr_cur_lex()->yy_lex_dmp(yy_this_err_obj, NULL);
        }

//  Reenable assertions.

    yy_assert_enable();
    
    return;

}   // yy_psr_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr)
//
//  yy_restore_data copies a parser object from the space reserved for it in
//  a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

const char *yy_psr_obj::yy_restore_data(
    const char		*yy_data_ptr)
{
    yy_data_ptr = yy_psr_dynamic_part.yy_restore_data(yy_data_ptr);
    yy_data_ptr = yy_psr_stack_part.yy_restore_data(yy_data_ptr);
    yy_data_ptr = yy_psr_rdc_stack_part.yy_restore_data(yy_data_ptr);
    yy_data_ptr = yy_psr_bktrk_stack_part.yy_restore_data(yy_data_ptr);
    yy_data_ptr = yy_psr_bktrk_queue_part.yy_restore_data(yy_data_ptr);

    return(yy_data_ptr);

}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr)
//
//  yy_save_data copies a parser object to the space reserved for it in a
//  memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

char *yy_psr_obj::yy_save_data(
    char		*yy_data_ptr) const
{
    yy_data_ptr = yy_psr_dynamic_part.yy_save_data(yy_data_ptr);
    yy_data_ptr = yy_psr_stack_part.yy_save_data(yy_data_ptr);
    yy_data_ptr = yy_psr_rdc_stack_part.yy_save_data(yy_data_ptr);
    yy_data_ptr = yy_psr_bktrk_stack_part.yy_save_data(yy_data_ptr);
    yy_data_ptr = yy_psr_bktrk_queue_part.yy_save_data(yy_data_ptr);

    return(yy_data_ptr);

}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
//
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold a parser object.
//
//////////////////////////////////////////////////////////////////////////////

size_t yy_psr_obj::yy_sizeof_data(void) const
{
    size_t	yy_sizeof;

    yy_sizeof = yy_psr_dynamic_part.yy_sizeof_data();
    yy_sizeof += yy_psr_stack_part.yy_sizeof_data();
    yy_sizeof += yy_psr_rdc_stack_part.yy_sizeof_data();
    yy_sizeof += yy_psr_bktrk_stack_part.yy_sizeof_data();
    yy_sizeof += yy_psr_bktrk_queue_part.yy_sizeof_data();

    return(yy_sizeof);

}  // yy_sizeof_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_obj::yy_psr_start(yy_this_psr_obj, 
//                  yy_psr_new_class, yy_psr_new_start);
//
//  yy_psr_start        places the parser in the start state for a given
//                      grammar class and goal symbol.
//
//  yy_this_psr_obj     is the parser object to place into the start state.
//
//  yy_psr_new_class    is the grammar class.
//
//  yy_psr_new_start    is the goal symbol.
//
//  yy_psr_start has no return value.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_obj::yy_psr_start(
    int yy_psr_new_class,
    int yy_psr_new_start)
{
    int                 yy_lo, yy_hi;

    assert(0 <= yy_psr_new_class && yy_psr_new_class < yy_psr_max_class());

    yy_psr_class() = yy_psr_new_class;
    yy_psr_start_sym() = yy_psr_new_start;

    if (yy_psr_new_start == yy_psr_dflt_start_) {
        if (yy_psr_new_class == 0) {
            yy_psr_cur_start_state() = yy_psr_start_state()[0].yy_psr_state;
            }
        else {
            yy_psr_cur_start_state() = 
                yy_psr_start_state()[yy_psr_last_start()[
			yy_psr_new_class - 1] + 1].yy_psr_state;
            }
        }
    else {
        if (yy_psr_new_class == 0) {
            yy_lo = 0;
            yy_hi = yy_psr_last_start()[0];
            }
        else {
            yy_lo = yy_psr_last_start()[yy_psr_new_class - 1] + 1;
            yy_hi = yy_psr_last_start()[yy_psr_new_class];
            }
        while (yy_lo <= yy_hi) {
            if (yy_psr_new_start == yy_psr_start_state()[yy_lo].yy_psr_sym)
                break;
            ++yy_lo;
            }

        // ensure this sym is an entry point in this class
        assert(yy_psr_new_start == yy_psr_start_state()[yy_lo].yy_psr_sym);

        yy_psr_cur_start_state() = yy_psr_start_state()[yy_lo].yy_psr_state;
        }

    yy_psr_state() = yy_psr_cur_start_state();
    yy_psr_rdc_state() = yy_psr_state();
    
    return;

}   // yy_psr_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_valid_obj()
//
//  yy_psr_valid_obj() is a validity checking function which currently
//  returns true.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_psr_obj::yy_psr_valid_obj() const
{ 
    return(yy_true);

}   //  yy_psr_valid_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_report(yy_err_num, ...)
//
//  yy_err_report() looks up an error message in the error table and then
//  displays it by calling yy_err_vreport().  This function uses the error
//  object associated with the file object associated with the lexer object
//  associated with this parser object.  Whew...
//
//  If the error is displayed, it returns a non-zero value.  If the error 
//  was not displayed then 0 is returned.
//
//////////////////////////////////////////////////////////////////////////////

int yy_psr_obj::yy_err_report(
    int     yy_err_num,
    ...)
{
    va_list     yy_var_args;
    int         yy_return_value;
    yy_err_ptr 	yy_this_err_obj;
    
//  if we have a lexer object that has an input object that has an error
//  object, use that error object to display the error

    if ((yy_psr_cur_lex() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err() != NULL)) {
	yy_this_err_obj = yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err();
	}
    
//  otherwise, attempt use the failsafe object, unless is no error failsafe
//  object, when we return a zero indicating failure

    else {
        yy_this_err_obj = yy_err_failsafe_obj();
	if (yy_this_err_obj == NULL) return (0);
        }

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_num);

//  use the associated error object to lookup, format, and display the error

    yy_return_value = yy_this_err_obj->yy_err_vreport(yy_err_num, yy_var_args);

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_report


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_printf(yy_err_fmt, ...)
//
//  yy_err_printf() formats and displays text by sending its arguments onto
//  yy_err_vprintf().  This function uses the error object associated with
//  the file object associated with the lexer object associated with this
//  parser object.
//
//////////////////////////////////////////////////////////////////////////////

int yy_psr_obj::yy_err_printf(
        const char *yy_err_fmt,
        ...
        )
{
    va_list     yy_var_args;
    int         yy_return_value;
    yy_err_ptr 	yy_this_err_obj;
    
//  if we have a lexer object that has an input object that has an error
//  object, use that error object to display the error

    if ((yy_psr_cur_lex() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err() != NULL)) {
	yy_this_err_obj = yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err();
	}
    
//  otherwise, attempt use the failsafe object, unless is no error failsafe
//  object, when we return a zero indicating failure

    else {
        yy_this_err_obj = yy_err_failsafe_obj();
	if (yy_this_err_obj == NULL) return (0);
        }

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_fmt);

//  pass them on for processing

    yy_return_value = yy_this_err_obj->yy_err_vprintf(yy_err_fmt, yy_var_args);

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_printf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_puts(yy_text)
//
//  yy_err_puts() displays a string onto the error output stream.  This
//  function uses the error object associated with the file object
//  associated with the lexer object associated with this parser object.
//
//////////////////////////////////////////////////////////////////////////////

int yy_psr_obj::yy_err_puts(
    const char *yy_text)
{
    int         yy_return_value;
    yy_err_ptr 	yy_this_err_obj;
    
//  if we have a lexer object that has an input object that has an error
//  object, use that error object to display the error

    if ((yy_psr_cur_lex() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err() != NULL)) {
	yy_this_err_obj = yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err();
	}
    
//  otherwise, attempt use the failsafe object, unless is no error failsafe
//  object, when we return a zero indicating failure

    else {
        yy_this_err_obj = yy_err_failsafe_obj();
	if (yy_this_err_obj == NULL) return (0);
        }

//  call the appropriate error objects function

    yy_return_value = yy_this_err_obj->yy_err_puts(yy_text);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_puts


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_syntax_assist(yy_syna_num)
//
//  yy_err_syntax_assist() looks up a syntax assist in the synax assist
//  table and then displays it by calling yy_err_puts().  This function uses
//  the error object associated with the file object associated with the
//  lexer object associated with this parser object.
//  
//////////////////////////////////////////////////////////////////////////////

int yy_psr_obj::yy_err_syntax_assist(
    int     yy_syna_num)
{
    int         yy_return_value;
    yy_err_ptr 	yy_this_err_obj;
    
//  if we have a lexer object that has an input object that has an error
//  object, use that error object to display the error

    if ((yy_psr_cur_lex() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp() != NULL) &&
	(yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err() != NULL)) {
	yy_this_err_obj = yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err();
	}
    
//  otherwise, attempt use the failsafe object, unless is no error failsafe
//  object, when we return a zero indicating failure

    else {
        yy_this_err_obj = yy_err_failsafe_obj();
	if (yy_this_err_obj == NULL) return (0);
        }

//  call the appropriate error objects function

    yy_return_value = yy_this_err_obj->yy_err_syntax_assist(yy_syna_num);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_syntax_assist


