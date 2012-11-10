
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_lexsm.h
//  
//  FILE DESCRIPTION:     header file with lexer object class declarations
//                        specific to lexing with small tables
//  
//                      +-----------------------+
//                      |        lexer          |
//                      |  abstract base class  |
//                      |      (yy_lex.h)       |
//                      +-----------------------+
//                                 | derives      
//                                 |
//         +-------------------------------------------------------+
//         |                 |                  |                  |
// +--------------+ +-----------------+ +----------------+ +----------------+
// | lexer class  | |   lexer class   | |  lexer class   | |  lexer class   |
// | fast tables  | | readable tables | |  small tables  | |   LEX lexer    |
// | (yy_lexfa.h) | |  (yy_lexrd.h)   | |  (yy_lexsm.h)  | |  (yy_lexle.h)  |
// +--------------+ +-----------------+ +----------------+ +----------------+
//         |                 |                  |                  |
//         +-------------------------------------------------------+
//                                 | one of them derives
//                                 |
//                  +-----------------------------+
//                  |  generated lexer class(es)  |
//                  |      from your grammar      |
//                  |        (yy_mylex.h)         |
//                  +-----------------------------+
//    
//  MODIFICATION HISTORY:
//  
//    06/03/98   cc       extracted various sub-objects from the lexer object.
//    10/25/93   bz/cc    initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_lexsm_h_
#define yy_lexsm_h_ 1

#include "yy_lex.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_lex_small_ptr    is a typedef which defines a pointer a lexer
//                      state (dispatch) table.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_lex_small_dt  *yy_lex_small_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_small_dt
//
//  The yy_lex_small_dt is the class Yacc++ uses to represent a lexer
//  small (dispatch) table for one lexer state. 
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_small_dt {

 public:    
 
    int     yy_num_lex_rngs;
    
    struct yy_lex_rng_ {
        int      yy_bot;
        int      yy_cmd_ix;
        } yy_lex_rng[1];
 
    };  // yy_lex_small_dt


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_obj_small
//
//  The yy_lex_obj_small is the class Yacc++ uses to represent a lexer object
//  with small tables.  Each lexer object is independent and contains complete
//  state information.
//
//  FUNCTION DECLARATIONS
// 
//  yy_lex_obj_small()  constructor for the small table lexer object.
//
//  yy_lex_do_action()  executes user action code.
// 
//  yy_lex_ins()        is the call-back lexer engine for lexing an array of
//                      characters according to the rules in the grammar.
// 
//  LEXER OBJECT INTERNAL DATA:
//
//  yy_lex_cmd          the lexer state tables -- small format.
//                      Works in conjunction with yy_lex_dt.
//
//  yy_lex_dt           the lexer state tables -- small format.
//                      Works in conjunction with yy_lex_cmd.
// 
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_obj_small : public yy_lex_obj 
{

 public:

    yy_lex_obj_small(
        int                     yy_new_lex_min_type,
        int                     yy_new_lex_max_type,
        int                     *yy_new_lex_cmd,
        yy_lex_small_ptr        *yy_new_lex_dt,
        yy_inp_ptr              yy_new_this_file_obj,
        yy_symtab_ptr           yy_new_this_symtab_obj,
        int                     *yy_new_lex_start_state,
        int                     yy_new_lex_max_class,
        int                     yy_new_lex_class);
        
    inline int *yy_lex_dt_cmd(
	int		yy_lex_cur_rt_type,
	int		yy_lex_cur_state
	);

    void yy_lex_engine(void);

 protected:

    yy_lex_small_ptr            *yy_lex_dt;

};  // yy_lex_obj_small


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int *yy_lex_obj_small::yy_lex_dt_cmd(type, state)
//
//  yy_lex_dt_cmd looks up the appropriate parser action in the command table
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_lex_obj_small::yy_lex_dt_cmd(
    int		yy_lex_cur_rt_type,
    int		yy_lex_cur_state)
{

    int 		l, m, h; 
    yy_lex_small_ptr	p;

    p = yy_lex_dt[yy_lex_cur_state];

    l = 0; 
    h = p->yy_num_lex_rngs - 1; m = (l + h) >> 1;
    while (l <= h) {
	if (yy_lex_cur_rt_type < p->yy_lex_rng[m].yy_bot) h = m - 1;
	else if (p->yy_lex_rng[m+1].yy_bot <= yy_lex_cur_rt_type) l = m + 1;
	else break;
	m = (l + h) >> 1; 
        }

    return(yy_lex_cmd() + p->yy_lex_rng[m].yy_cmd_ix);

}   // yy_lex_dt_cmd


#endif /* yy_lexsm_h_ */
