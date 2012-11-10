
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_const.h
//  
//  FILE DESCRIPTION:     header file with constant declarations
//
//  CLASS HIERARCHY:
//
//                     +-------------------------+
//                     |    constants class      |
//                     |      (yy_const.h)       |
//                     +-------------------------+
//                                  | derives
//                                  |
//              +-------------------+--------------------+
//              |                                        |
//  +------------------------+              +-------------------------+
//  |        parser          |              |         parser          |
//  |  abstract base class   |              | reduce stack area class |
//  |      (yy_psr.h)        |              |      (yy_rdcsk.h)       |
//  +------------------------+              +-------------------------+
//
//  MODIFICATION HISTORY:
//  
//  04/03/98	bz/cc	extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_const_h_
#define yy_const_h_

//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_const
//
//  The yy_const class defines the constants used in LOL objects.
//
//  CONFIGURATION CONSTANTS:
//
//  yy_psr_dflt_class_  is the default parser class to create.
//
//  yy_psr_dflt_start_  is the default goal symbol entry point.
//
//  yy_psr_left_max_    is the default value for the length of a production
//                      which can be reduced.
//
//  yy_psr_rt_max_      is the default value for the amount of lookahead the
//                      parser can hold.  The lexer should never get more than
//                      this many tokens ahead of the parser.
//
//  yy_psr_rdc_max_     is the default value for the depth of production 
//                      nesting the parser stack.
//
//  yy_psr_bktrk_max_   is the default value for the maximum length of a 
//                      production on a syntactic decision predicate.
//
//  yy_psr_bktrk_stack_max_ is the default value for the depth of syntactic
//                      decision productions on the backtracking stack for
//                      the parser.
//
//  yy_discard_type_    is the token type number reserved for all discarded
//                      tokens.
//
//  yy_eof_             is the token type number reserved for the end-of-file
//                      token.  It is 0 to match lex lexers.
//
//  yy_error_           is a manifest constant which gives the type number of
//                      the eof token the lexer will pass to the parser when
//                      an error (an unrecognized token) is encountered.  Do
//                      not change this value, it is used implicitly in the
//                      parser tables.
//
//  yy_psr_acpt_ ...    opcodes for parser actions
//
//////////////////////////////////////////////////////////////////////////////

class yy_const {

  public:

    enum yy_ref_stack_max_enum { yy_ref_stack_max_ = 8192 };
    
    enum yy_psr_stack_layout_enum {
	yy_psr_stack_left_and_rt_empty_,
	yy_psr_stack_rt_empty_,
	yy_psr_stack_left_and_rt_joined_,
	yy_psr_stack_left_and_rt_split_
    	};
    
    enum yy_psr_dflt_class_enum { yy_psr_dflt_class_ = 0 };
    
    enum yy_psr_dflt_start_enum { yy_psr_dflt_start_ = 0 };
    
    enum yy_psr_left_max_enum { yy_psr_left_max_ = 8192 };
    
    enum yy_psr_rt_max_enum { yy_psr_rt_max_ = 4 };
    
    enum yy_psr_rdc_max_enum { yy_psr_rdc_max_ = 256 };

    enum yy_psr_bktrk_max_enum { yy_psr_bktrk_max_ = 8192 };
    
    enum yy_psr_bktrk_stack_max_enum { yy_psr_bktrk_stack_max_ = 256 };
    
    enum yy_psr_discard_enum { yy_discard_type_ = -3 };

    enum yy_psr_eof_enum { yy_eof_ = 0 };      
 
    enum yy_psr_error_enum { yy_error_ = -2 };
    
    typedef enum yy_psr_bktrk_mode_enum_ {
	yy_psr_no_bktrk_,
	yy_psr_ins_bktrk_,
	yy_psr_copy_bktrk_,
	yy_psr_read_bktrk_,
	yy_psr_done_bktrk_
        } yy_psr_bktrk_mode_enum;
    
    enum yy_lex_dflt_class_enum { yy_lex_dflt_class_ = 0 };

    enum yy_lex_rdc_max_enum { yy_lex_rdc_max_ = 256 };  

    enum yy_buf_lhead_state_enum { 
        yy_buf_lhead_state_not_read_ = 0,
        yy_buf_lhead_state_read_ = 1,
        yy_buf_lhead_state_nterm_only_ = 2,
        yy_buf_lhead_state_read_nterm_ = 3
        };

    enum yy_buf_grow_by_enum { 
        yy_buf_dflt_grow_by_ = 8192
        };

    enum yy_buf_size_enum {      
        yy_buf_dflt_size_ = 8192
        };
        
    enum yy_lex_opcodes_enum {
        // skip 0       
        yy_lex_chg_                 =  1,
        yy_lex_chg_nx_              =  2,
        yy_lex_epops_               =  3,
        yy_lex_epops_nx_            =  4,
        yy_lex_err_                 =  5,
        yy_lex_err_nx_              =  6,
        yy_lex_push_                =  7,
        yy_lex_push_nx_             =  8,
        yy_lex_ract_                =  9,
        yy_lex_ract_nx_             = 10,
        yy_lex_rdc_                 = 11,
        yy_lex_rdc_nx_              = 12,
        yy_lex_rdc_nterm_           = 13,
        yy_lex_rdc_nterm_nx_        = 14,
        yy_lex_sact_                = 15,
        yy_lex_sact_nx_             = 16,
        yy_lex_shf_                 = 17,
        yy_lex_shf_nx_              = 18,
        yy_lex_shf_nterm_           = 19,
        yy_lex_shf_nterm_nx_        = 20,
        yy_lex_type_                = 21,
        yy_lex_type_nx_             = 22,
        yy_lex_push_shf_rdc_nterm_  = 23,
        yy_lex_rdc_chg_             = 24,
        yy_lex_shf_chg_             = 25,
        yy_lex_shf_nterm_chg_       = 26,
        yy_lex_shf_ract_rdc_        = 27,
        yy_lex_shf_rdc_             = 28,
        yy_lex_shf_nterm_rdc_       = 29,
        yy_lex_shf_rdc_nterm_       = 30,
        yy_lex_shf_rdc_chg_         = 31,
        yy_lex_shf_sact_            = 32,
        yy_lex_shf_sact_chg_        = 33,
        yy_lex_shf_sact_rdc_        = 34,
        yy_lex_type_ract_rdc_       = 35,
        yy_lex_num_of_opcs_         = 36
        };

    // if you add new opcodes below, also add them to the opcode table,
    // yy_psr_opc_tbl in yy_psr.cxx.

    enum yy_psr_opcodes_enum {
        // skip 0 
        yy_psr_acpt_                =  1,
        yy_psr_acpt_nx_             =  2,
        yy_psr_chg_                 =  3,
        yy_psr_chg_nx_              =  4,
        yy_psr_epops_               =  5,
        yy_psr_epops_nx_            =  6,
        yy_psr_err_                 =  7,
        yy_psr_err_nx_              =  8,
        yy_psr_ign_                 =  9,
        yy_psr_ign_nx_              = 10,
        yy_psr_push_                = 11,
        yy_psr_push_nx_             = 12,
        yy_psr_ract_                = 13,
        yy_psr_ract_nx_             = 14,
        yy_psr_rdc_                 = 15,
        yy_psr_rdc_nx_              = 16,
        yy_psr_sact_                = 17,
        yy_psr_sact_nx_             = 18,
        yy_psr_shf_                 = 19,
        yy_psr_shf_nx_              = 20,
        yy_psr_ign_chg_             = 21,
        yy_psr_push_chg_            = 22,
        yy_psr_push_shf_chg_        = 23,
        yy_psr_push_shf_ract_rdc_   = 24,
        yy_psr_push_shf_rdc_        = 25,
        yy_psr_push_shf_sact_chg_   = 26,
        yy_psr_push_shf_sact_rdc_   = 27,
        yy_psr_ract_rdc_            = 28,
        yy_psr_sact_rdc_            = 29,
        yy_psr_shf_acpt_            = 30,
        yy_psr_shf_chg_             = 31,
        yy_psr_shf_ract_rdc_        = 32,
        yy_psr_shf_rdc_             = 33,
        yy_psr_shf_sact_chg_        = 34,
        yy_psr_shf_sact_rdc_        = 35,
        yy_psr_bktrk_push_          = 36,
        yy_psr_bktrk_push_nx_       = 37,
        yy_psr_bktrk_pop_           = 38,
        yy_psr_bktrk_pop_nx_        = 39,
        yy_psr_bktrk_redo_          = 40,
        yy_psr_bktrk_redo_nx_       = 41,
        yy_psr_num_of_opcs_         = 42
        };

    };

#endif /* yy_const_h_ */

