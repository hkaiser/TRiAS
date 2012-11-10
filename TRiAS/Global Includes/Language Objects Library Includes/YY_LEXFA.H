
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_lexfa.h
//  
//  FILE DESCRIPTION:     header file with lexer object class declarations
//                        specific to lexing with fast tables
//  
//  CLASS HIERARCHY:
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

#ifndef yy_lexfa_h_
#define yy_lexfa_h_ 1

#include "yy_lex.h"


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_obj_fast
//
//  The yy_lex_obj_fast is the class Yacc++ uses to represent a lexer object
//  with fast tables.  Each lexer object is independent and contains complete
//  state information.
// 
//  FUNCTION DECLARATIONS
// 
//  yy_lex_obj_fast()   constructor for the fast table lexer object.
//
//  yy_lex_do_action()  executes user action code.
//
//  yy_lex_ins()        is the call-back lexer engine for lexing an array of
//                      characters according to the rules in the grammar.
// 
//  LEXER OBJECT INTERNAL DATA:
//
//  yy_lex_cmd          the lexer state tables -- fast format.
// 
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_obj_fast : public yy_lex_obj 
{

 public:

    yy_lex_obj_fast(
        int                     yy_new_lex_min_type,
        int                     yy_new_lex_max_type,
        int                     *yy_new_lex_cmd,
        yy_inp_ptr              yy_new_this_inp_obj,
        yy_symtab_ptr           yy_new_this_symtab_obj,
        int                     *yy_new_lex_start_state,
        int                     yy_new_lex_max_class,
        int                     yy_new_lex_class
        );
        
    inline int *yy_lex_dt_cmd(
	int		yy_lex_cur_rt_type,
	int		yy_lex_cur_state
	);

    void yy_lex_engine(void);

};  // yy_lex_obj_fast


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int *yy_lex_obj_fast::yy_lex_dt_cmd(type, state)
//
//  yy_lex_dt_cmd looks up the appropriate parser action in the command table
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_lex_obj_fast::yy_lex_dt_cmd(
    int		yy_lex_cur_rt_type,
    int		yy_lex_cur_state)
{

    return(yy_lex_cmd() + yy_lex_cur_state + (3 * yy_lex_cur_rt_type));

}   // yy_lex_dt_cmd


#endif /* yy_lexfa_h_ */
