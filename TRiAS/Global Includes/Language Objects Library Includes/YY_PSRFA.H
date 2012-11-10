
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_psrfa.h
//  
//  FILE DESCRIPTION:     header file with parser object class declarations
//                        specific to parsing with fast tables
//
//  CLASS HIERARCHY:
//
//                      +------------------------+
//                      |        parser          |
//                      |  abstract base class   |
//                      |      (yy_psr.h)        |
//                      +------------------------+
//                                 | derives      
//                                 |
//         +-------------------------------------------------+
//         |                       |                         |
// +----------------+      +------------------+      +----------------+ 
// |  parser class  |      |   parser class   |      |  parser class  |
// |  fast tables   |      |  readable tables |      |  small tables  |
// |  (yy_psrfa.h)  |      |   (yy_psrrd.h)   |      |  (yy_psrsm.h)  | 
// +----------------+      +------------------+      +----------------+ 
//         |                       |                         |
//         +-------------------------------------------------+
//                                 | one of them derives
//                                 |
//                  +------------------------------+
//                  |  generated parser class(es)  |
//                  |      from your grammar       |
//                  |        (yy_mypsr.h)          |
//                  +------------------------------+
//    
//  MODIFICATION HISTORY:
//  
//  05/04/98	cc	extracted various sub-objects from the parser object.
//  04/21/97    bz      added runtime support for decision predicates parsing.
//  03/27/97    bz      port to HP ANSI aC++ on 10.20 flagged x::x
//                      within class.  Should be simply "x" within class.
//  10/20/93    bz/cc   initial coding.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_psrfa_h_
#define yy_psrfa_h_

#include "yy_psr.h"

//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_syna_ix_fast
//
//////////////////////////////////////////////////////////////////////////////

typedef struct yy_syna_ix_fast {
        int     state;
        int     ix;
        } yy_syna_ix_type;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_obj_fast
//
//  The yy_psr_obj_fast is the base class which provides fast parsing engines
//  for your application.  Each parser object is independent and contains 
//  complete state information.
// 
//  PUBLIC FUNCTIONS:
//
//  yy_psr_obj_fast()   constructor for parser objects with fast tables.
//
//  yy_psr_display_expected()
//                      displays the expected tokens for the current state.
//
//  yy_psr_do_action()  executes user action code embedded in class grammar
//                      for this parser.  This function is virtual because
//			each generated grammar has a different set of 
//			embedded actions.
//
//  yy_psr_dt_cmd()     looks up the appropriate parsing command sequence 
//			given a look-ahead entry and a state.
//
//  yy_psr_dt_err()     looks up the appropriate syntax assist list given a
//  			state.
//			
//  yy_psr_engine()	executes parsing actions until the look-ahead is
//			emptied (or the parser is paused or aborted).  The
//			new lexer engine calls this function instead of
//			yy_psr_ins().
//
//  yy_psr_err()        reports a syntax error to the user based on the 
//                      current parser state variables.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_obj_fast : public yy_psr_obj 
{

 public:

    yy_psr_obj_fast(
        yy_boolean                  yy_new_psr_abort_on_error,
        int                         yy_new_psr_min_type,
        int                         yy_new_psr_max_type,
        int                         yy_new_psr_tkn_max_type,
        int                         *yy_new_psr_cmd,
        yy_lex_ptr                  yy_new_lex_obj,
        int                         yy_new_psr_num_states,
        yy_syna_ix_type             *yy_new_syna_ix,
        int                         *yy_new_syna,
        char                        **yy_new_spelling_tbl,
        yy_psr_start_state_tbl      *yy_new_psr_start_state,
        int                         *yy_new_psr_last_start,
        const yy_ref_factory_obj    &yy_new_ref_factory,
        int                         yy_new_psr_max_class,
        int                         yy_new_psr_left_max,
        int                         yy_new_psr_rt_max,
        int                         yy_new_psr_rdc_max,
	int			    yy_new_psr_bktrk_max = yy_psr_bktrk_max_,
	int			    yy_new_psr_bktrk_stack_max = yy_psr_bktrk_stack_max_
        );

    virtual void yy_psr_display_expected(void);

    virtual void yy_psr_do_action(
        int 		yy_psr_action_index) = 0;

    inline int *yy_psr_dt_cmd(
	int		yy_psr_cur_rt_type,
	int		yy_psr_cur_state);

    inline int yy_psr_dt_err(
	int		yy_psr_cur_state);
    
    virtual void yy_psr_engine(void);

    virtual void yy_psr_err(void);

 protected:

    yy_syna_ix_type         *yy_syna_ix;

};  // yy_psr_obj_fast


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int *yy_psr_dt_cmd(type, state)
//
//  yy_psr_dt_cmd looks up the appropriate parser action in the command table
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_obj_fast::yy_psr_dt_cmd(
    int		yy_psr_cur_rt_type,
    int		yy_psr_cur_state)
{

    return(yy_psr_cmd() + yy_psr_cur_state + (3 * yy_psr_cur_rt_type));

}   // yy_psr_dt_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_dt_err(state)
//
//  yy_psr_dt_err looks up the appropriate syntax assists
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj_fast::yy_psr_dt_err(
    int		yy_psr_cur_state)
{
    int yy_lo, yy_mid, yy_hi;

    yy_lo = 0; 
    yy_hi = yy_psr_num_states(); 
    yy_mid = (yy_lo + yy_hi) >> 1;

    while (yy_lo <= yy_hi) {
        if ((yy_psr_cur_state) < yy_syna_ix[yy_mid].state) {
	    yy_hi = yy_mid - 1;
	    }
        else if (yy_syna_ix[yy_mid].state < (yy_psr_cur_state)) {
	    yy_lo = yy_mid + 1;
	    }
        else break;
        yy_mid = (yy_lo + yy_hi) >> 1; 
	}

    return (yy_syna_ix[yy_mid].ix+1);

}   // yy_psr_dt_err


#endif /* yy_psrfa_h_ */
