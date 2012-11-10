
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_lex.h
//  
//  FILE DESCRIPTION:     insert file with lexer declarations.
//                        (for Microsoft C++ compiler)
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
//  01/04/99	bz/cc	Removed yy_no_myref_inlines_ as it didn't work with
//			several compilers.
//  12/22/98    bz      Make sure inline definitions match declarations.
//                      (Borland C++ caught ones missing inline on the 
//                      definition).  Changed some inline code, to get
//			more of the inlines actually generated inline.
//			Note g++ silently failed, neither generating an
//			out-of-line copy, nor inlining the code.
//  04/16/98	cc	changes to remove union size and output union
//			header name dependencies.
//  09/12/97    bz      make yy_err_report() virtual for overrides.
//  01/15/96 	bz/cc   Added inline qualifier to yy_lex_cur_obj function
//			declaration in class to match the definition.
//  10/25/93    bz/cc   removed manifest constants which previously were    
//                      used to recompile specially configured libraries:
//                      -- removed yy_lex_dmp_ as dumping functions are 
//                         always present in the lexer classes.  
//                      -- removed yy_lex_inline_actions_ as this is no
//                         longer possible with base and derived lexer
//                         classes.  do_action is a member function always
//                         present in the generated lexer class(es).
//                      -- removed yy_use_lex_ as using a LEX lexer is
//                         now indicated via syntax in the grammar.
//                      -- removed all table specific generated constants
//                         as it's all done with derived classes.
//                      -- removed yy_lex_abstract_ as this is always an
//                         abstract lexer base class.
//  07/07/93    bz      merged yy_lex1.h and yy_lex2.h.
//  05/05/93    bz      changes for native C++ rewrite of the input object
//                      with removing of the yy_use_getc_ code too.
//  04/19/93    bz/cc   removed forwarding functions yy_cur_filename(), 
//                      yy_file_open(), yy_file_close(), and 
//                      yy_file_is_stdin() as these are not members of the 
//                      input object generic base class.
//  04/05/93    bz      New forwarding scheme for yy_err_report().
//                      Also changes for native C++ rewrite of file object.
//                      Also, removed yy_use_getc_ code.
//  04/05/93    bz      yy_err2.h and yy_file2.h no longer exists.
//  03/31/93    bz      added inline for symtab_remove_sym().
//  03/22/93    bz      added yy_export for use of classes in a DLL.
//  02/26/93    bz      yy_sym2.h no longer exists.  Added inlines for
//                      new symbol table lookup only functions.
//  10/04/92    cc      yy_lex_abort marks lhead as consumed to force lexer
//                      to check eof flag before processing next token.
//  08/07/92    bz      removed macros and #ifdefs in C++ only version.
//  01/10/92    cc      rev 1.4 -- lexer object changes for separate 
//                      compilation of actions.
//  03/30/90    bz/cc   coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_lex_h_
#define yy_lex_h_ 1


//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES
//
//  Note all header files are included below except for:
//
//	yy_psr.h which is included after the declaration of the class 
//		yy_lex_obj to allow some mutual recursive inline functions 
//		between the lexer and parser objects.
//
//      yy_inlin.h which is included at the bottom so that it can depend
//		on the yy_myref.h but not introduce circular header file
//		dependencies.
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_bool.h"
#include "yy_buf.h"
#include "yy_inp.h"
#include "yy_err.h"
#include "yy_stdio.h"
#include "yy_sym.h"
#include "yy_trace.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_lex_ptr          is a typedef which defines a pointer to a lexer
//                      object.
//
//  yy_psr_ptr          is a typedef which defines a pointer to a parser
//                      object.
//
//  yy_ref_factory_ptr 	is a typedef which defines a pointer to a reference
//                      factory object.
//
//  yy_ref_ptr          is a typedef which defines a pointer to a reference
//                      object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_lex_obj      	*yy_lex_ptr;

typedef class yy_export yy_psr_obj	      	*yy_psr_ptr;

typedef class yy_export yy_ref_factory_obj	*yy_ref_factory_ptr;

typedef class yy_export yy_ref_obj		*yy_ref_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_static_obj
//
//  The yy_lex_static_obj is the base class which provides the "static" data
//  (that is data which does not normally change as a parse progresses, for
//  example the lexer-parser connection) for a lexer object.  Most of this
//  information is the data which is contained in the lexer tables generated
//  by Yacc++.
//
//  This class represents the information which is not saved when a lexer
//  memento object is created (nor restored when a lexer memento is used to
//  create a new lexer object or update a running one).  If you, as a user,
//  wish to save any of this information into your lexer memento, you will
//  need to code special memento save and restore functions to do so.
//
//
//  PUBLIC FUNCTIONS:
//
//  yy_lex_static_obj() constructor for a lexer static object.
//
//  ~yy_lex_static_obj()
//			destructor for a lexer static object.
//
//  INTERNAL STATE:
//
//  yy_this_lex_min_type
//			the lowest value of a character or non-terminal
//			number.
//
//  yy_this_lex_max_type
//			the highest value of a character or non-terminal
//			number.
//
//  yy_this_lex_num_states
//			the number of states in the lexer tables.
//
//  yy_this_lex_max_class
//			the maximum class number for the generated lexer.
//
//  yy_this_lex_obj	the lexer object associated with the lexer.
//		
//
//  yy_this_lex_cmd	the lexer engine actions for the generated lexer.
//
//  yy_this_lex_syna	the syntax assist tables for the generated lexer.
//
//  yy_this_lex_last_start
//			the last start state for each class in the generated
//			lexer.
//
//  yy_this_lex_start_state
//			the start state table for the generated lexer.
//
//  yy_this_lex_spelling_tbl
//			spellings for the types defined in the user grammar.
//
//  yy_this_lex_opc_tbl lexer engine opcode spellings for use in traces.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_static_obj : public yy_const
{

 public:

    yy_lex_static_obj(
        yy_psr_ptr                  yy_new_psr_obj,
        int                         yy_new_lex_min_type,
        int                         yy_new_lex_max_type,
        int                         yy_new_lex_max_class,
        int                         *yy_new_lex_cmd,
        int			    *yy_new_lex_start_state
        );

    virtual ~yy_lex_static_obj();

    inline yy_psr_ptr &yy_lex_cur_psr(void);
    
    inline int &yy_lex_min_type(void);

    inline int &yy_lex_max_type(void);

    inline int &yy_lex_max_class(void);

    inline int *yy_lex_cmd(void);
    
    inline int *yy_lex_start_state(void);

    inline char * yy_far *yy_lex_opc_tbl(void);

 protected:

    yy_psr_ptr                  yy_this_psr_obj;
    int                         yy_this_lex_min_type;
    int                         yy_this_lex_max_type;
    int                         yy_this_lex_max_class;
    int                         *yy_this_lex_cmd;
    int				*yy_this_lex_start_state;
    static char * yy_far        yy_this_lex_opc_tbl[yy_lex_num_of_opcs_];

};  // yy_lex_static_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_dynamic_obj
//
//  The yy_lex_dynamic_obj is the base class which provides the
//  "dynamic" data (that is data which normally changes as a parse
//  progresses, for example the lexer state) for a lexer object.
//
//  This class represents the information which is saved when a lexer
//  memento object is created (and restored when a lexer memento is
//  used to create a new lexer object or update a running one).
//
//  PUBLIC FUNCTIONS:
//
//  yy_lex_dynamic_obj()
//			constructor for a dynamic portion of a lexer
//  			object.
//
//  ~yy_lex_dynamic_obj()
//			destructor for a dynamic portion of a lexer
//			object.
//
//  yy_lex_aborts_on_error()
//                      returns a reference to the current lexer
//                      abort-on-error value.  when this value is true
//                      and the lexer encounters an error, the lexer
//                      aborts rather than attempting error recovery.
//
//  yy_restore_data(yy_data_ptr)
//			copies the dynamic portion of a lexer object from
//			the space reserved for it in a memento object.
//
//  yy_save_data(yy_data_ptr)
//			copies the dynamic portion of a lexer object to
//			the space reserved for it in a memento object.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold the dynamic portion of a lexer
//			object.
//
//
//  INTERNAL STATE:
//
//  yy_this_lex_is_done is true when the lexer is to do no further
//                      processing.
//
//  yy_this_lex_aborts_on_error
//			is true when the lexer should abort when
//			encountering a syntax error rahter than attempting
//			error recovery.
//
//  yy_this_lex_err_value
//			is true when the lexer is attempting to recover from
//                      a syntax error.
//
//  yy_this_lex_state 	describes the lexer state at a particular token.
//                      The state and the input token determine what
//                      actions the lexer will take.
//
//  yy_this_lex_class	the class the lexer is parsing with (consulted only
//			when finding the start state).
//
//  yy_this_lex_start_sym
//			the goal symbol the lexer is attempting match
//			(consulted only when finding the start state).
//
//  yy_this_lex_cur_start_state
//			the start state the lexer begins parsing in
//			(consulted only to begin the parsing).
//
//  yy_this_lex_cmd	the current lexer engine action.
//
//  yy_this_lex_bktrk_mode
//			the lexer backtracking mode.
//
//////////////////////////////////////////////////////////////////////////////

typedef struct yy_export yy_lex_dymamic_struct_
{
    yy_inp_ptr                  yy_this_inp_obj;
    yy_symtab_ptr               yy_this_symtab_obj;
    yy_ref_ptr                  yy_this_lex_rslt_val;
    yy_boolean                  yy_this_lex_is_done;
    yy_boolean                  yy_this_lex_error_flag;
    int                         yy_this_lex_tkn_count;
    int                         yy_this_lex_state;
    int                         yy_this_lex_class;
    int                         yy_this_lex_cur_start_state;
    int		                *yy_this_lex_cmd;
}   yy_lex_dynamic_struct;


class yy_export yy_lex_dynamic_obj
{

 public:

    yy_lex_dynamic_obj(
	yy_inp_ptr                  yy_new_inp_obj,
	yy_symtab_ptr               yy_new_symtab_obj,
	yy_ref_ptr                  yy_new_lex_rslt_val,
	yy_boolean                  yy_new_lex_is_done,
	yy_boolean                  yy_new_lex_error_flag,
	int                         yy_new_lex_tkn_count,
	int                         yy_new_lex_state,
	int                         yy_new_lex_class,
	int                         yy_new_lex_cur_start_state,
	int		            *yy_new_lex_cmd
        );

    virtual ~yy_lex_dynamic_obj();

    inline yy_inp_ptr &yy_lex_cur_inp(void);

    inline yy_symtab_ptr &yy_lex_cur_symtab(void);

    inline yy_ref_ptr &yy_lex_cur_rslt(void);

    inline yy_boolean &yy_lex_error_flag(void);

    inline yy_boolean &yy_lex_is_done(void);

    inline int &yy_lex_cur_tkn_count(void);

    inline int &yy_lex_state(void);

    inline int &yy_lex_class(void);

    inline int &yy_lex_cur_start_state(void);

    inline int *&yy_lex_this_cmd(void);

    inline const char *yy_restore_data(
	const char		*yy_data_ptr);

    inline char *yy_save_data(
	char			*yy_data_ptr);

    inline size_t yy_sizeof_data(void);

    yy_lex_dynamic_struct	yy_lex_dynamic_data;

};  // yy_lex_dynamic_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_lex_obj
//
//  The yy_lex_obj is the base class which provides the lexing engines for
//  your application.  Each lexer object is independent and in conjunction
//  with the lexer tables contains complete state information.
// 
//  CONFIGURATION CONSTANTS:
//
//  yy_lex_dflt_class_  is the default lexer class to create.
//
//  yy_lex_rdc_max_     controls the depth of production nesting the lexer
//                      stack will support.  This stack is only used to 
//                      support lexer non-terminals.
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
//  yy_lex_chg_ ...     opcodes for lexer actions
//        
//  PUBLIC FUNCTIONS:
// 
//  yy_lex_obj()        constructor for a lexer object.
//
//  ~yy_lex_obj()       destructor for a base lexer object.
//
//  yy_lex()            is a driver for the lexer engine which lexes input.
// 
//  yy_lex_abort()      is a macro which forces the lexer to abort.  This
//                      macro is called from the parser when a fatal error has
//                      occurred and the lexer is to abandon returning any
//                      more tokens.
//
//  yy_lex_cur_inp()    returns the input object associated with the lexer.
// 
//  yy_lex_cur_psr()    returns the parser object associated with the lexer.
// 
//  yy_lex_cur_symtab() returns the symbol table object associated with the 
//                      lexer.
// 
//  yy_lex_cur_tkn_count() returns the number of tokens lexed by this lexer.
// 
//  yy_lex_discard()    returns the lexer discard type.
//
//  yy_lex_dmp()        displays the values of the lexer state variables.  
// 
//  yy_lex_ins()
//
//  yy_lex_is_done()    is a macro which returns true if the lexer is paused
//                      or has finished lexing.
// 
//  yy_lex_pause()      is a macro which forces the lexer to pause and stop
//                      lexing characters.
// 
//  yy_lex_quit()       is a macro which forces the lexer to quit (returning
//                      at most one more token yy_eof).
// 
//  yy_lex_rdc()
//
//  yy_lex_resume()     is a macro which allows the lexer to resume lexing
//                      characters after a call to yy_lex_pause().
// 
//  yy_lex_rewind()
//
//  yy_lex_rslt()
//
//  yy_lex_rslt_init()  is a macro which initializes the lexer semantic result
//                      variable "yy_lex_rslt()" at the start of each token 
//                      production.  The yy_lex_rslt variable is normally 
//                      initialized to zero (0).  If yy_ltkns_ is defined, 
//                      this variable is initialized to the number of the 
//                      current token.  By overriding the definition of 
//                      yy_lex_rslt_init, the initial value of the yy_lex_rslt
//                      variable can be set to any specific value needed by an
//                      application.
// 
//  yy_lex_valid_obj()  supports yy_lex_valid_ptr(lex_ptr) for validity 
//                      checking of a lexer object.
//
//  INTERNAL STATE:
// 
//  yy_lex_done         is true when the lexer is to do no further processing.
// 
//  yy_lex_error_flag   is true when the lexer is skipping through error 
//                      characters.
// 
//  yy_lex_min_type 	is the lowest character or lexer non-terminal number.
//
//  yy_lex_max_type	is the highest character or lexer non-terminal number.
//
//  yy_lex_tkn_count    [optional] is the count of the current token when
//  			the manifest constant yy_lex_tkn_count_ is defined.
//  			This becomes the initial value for the lexer result
//  			value, yy_this_lex_rslt_val.
// 
//  yy_lex_state        describes the lexer state at a particular character.
//                      The state and the input character determine what 
//                      actions the lexer will take.
// 
//  yy_lex_nterm_lhead_ix                        
//                      is the index to the top of the lexical non-terminal
//                      look-ahead stack.
// 
//  yy_lex_rdc_ix       is an index into the rdc state stack for push and
//                      nterm_rdc actions.
// 
//  yy_this_inp_obj     is a pointer to the associated input object.
// 
//  yy_this_symtab_obj  is a pointer to the associated symtab object.
//
//  yy_this_psr_obj     is a pointer to the associated parser object.
// 
//  yy_lex_nterm_lhead[]
//                      is the stack of look-aheads saved when a lexical 
//                      non-terminal is reduced.  This stack is popped when
//                      the lexical non-terminal is shifted.
// 
//  yy_lex_rdc_state[]  is the state at time we pushed for the start of the 
//                      lexical non-terminal production.
// 
//  yy_lex_start_state  is the initial lexer start state.
//
//  yy_this_lex_rslt_val 
//			is the result variable passed to the parser on the
//                      next token reduction.
//
//  yy_lex_max_class	is the maximum class defined in the lexer tables.
// 
//  yy_lex_class        is the current class of the lexer.
//
//  yy_lex_cur_start_state
//			is the state the lexer begins each token in.
// 
//  yy_lex_cur_obj_ptr  is a pointer to the current lexer object.
//
//  yy_lex_opc_tbl      opcode spellings for use in traces
// 
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_lex_obj : public yy_buf_obj
{

 public:

    yy_lex_obj(
        int                         yy_new_lex_min_type,
        int                         yy_new_lex_max_type,
        int                         *yy_new_lex_cmd,
        yy_inp_ptr                  yy_new_this_inp_obj,
        yy_symtab_ptr               yy_new_this_symtab_obj,
        int                         *yy_new_lex_start_state,
        int                         yy_new_lex_max_class,
        int                         yy_new_lex_class);
        
    virtual ~yy_lex_obj();

    virtual void yy_lex(void);

    inline void yy_lex_abort(void);

    inline yy_inp_ptr &yy_lex_cur_inp(void);

    inline friend yy_lex_ptr &yy_lex_cur_obj();

    inline yy_psr_ptr &yy_lex_cur_psr(void);

    inline yy_ref_ptr &yy_lex_cur_rslt(void);

    inline yy_ref_ptr yy_lex_new_rslt(void);

    virtual yy_ref_ptr yy_lex_new_rslt1(void) = 0;

    inline yy_symtab_ptr &yy_lex_cur_symtab(void);

    inline int &yy_lex_cur_tkn_count(void);

    inline void yy_lex_discard();

    virtual void yy_lex_dmp(
        yy_err_ptr  yy_this_err_obj,
        const char  *yy_dmp_title
        );

    virtual void yy_lex_do_action(
        int                     yy_lex_action_index
        ) = 0;

    virtual void yy_lex_engine(void) = 0;

    inline int yy_lex_get_opnd(
	int		yy_ix);

    inline void yy_lex_ins(
        char                    *yy_lex_array_to_insert,
        int                     yy_lex_array_length
        );

    inline yy_boolean &yy_lex_is_done(void);

    inline void yy_lex_pause();

    inline void yy_lex_quit();

    virtual int &yy_lex_rdc() = 0;

    inline void yy_lex_resume();

    inline void yy_lex_rewind();

    virtual yy_ref_obj &yy_lex_rslt() = 0;

    inline void yy_lex_start(int yy_lex_class);

    inline int yy_lex_rslt_init();

    virtual yy_boolean yy_lex_valid_obj();

    inline void yy_lex_chg_macro(
	int		yy_ix);
	
    inline void yy_lex_epops_macro(
	int		yy_ix);

    inline void yy_lex_pop_macro(
	int		yy_ix);

    inline void yy_lex_push_macro(void);

    inline void yy_lex_valid_rdc_ix(void);
    
    inline void yy_lex_rdc_macro(void);

    inline void yy_lex_rdc_nterm_macro(void);
    
    inline void yy_lex_shf_nterm_macro(void);

    inline void yy_lex_type_macro(
	int		yy_ix);


//  forwarding functions for user convenience when writing lexer action code

    virtual int yy_err_report(
        int         yy_err_num,
        ...);

    inline yy_boolean yy_inp_attached();

    inline yy_boolean yy_inp_close(
        yy_boolean          yy_free_it
        );

    inline const char *yy_inp_filename();

    inline yy_boolean yy_inp_not_attached();

    inline yy_inp_ptr &yy_inp_prev_ptr();

    inline void yy_inp_rewind();

    inline yy_sym_ptr yy_symtab_lookup_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        );

    inline yy_sym_ptr yy_symtab_lookup(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        );

    inline yy_sym_ptr yy_symtab_lookup_only_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        );

    inline yy_sym_ptr yy_symtab_lookup_only(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type
        );

    inline yy_boolean yy_symtab_remove_sym(
        yy_sym_ptr      sy_ptr
        );

    inline int &yy_lex_min_type(void);

    inline int &yy_lex_max_type(void);

    inline int &yy_lex_max_class(void);

    inline int *yy_lex_cmd(void);
    
    inline int *yy_lex_start_state(void);

    inline char * yy_far *yy_lex_opc_tbl(void);

    inline yy_boolean &yy_lex_error_flag(void);

    inline int &yy_lex_state(void);

    inline int &yy_lex_class(void);

    inline int &yy_lex_cur_start_state(void);

    inline int *&yy_lex_this_cmd(void);

    inline yy_boolean yy_lex_valid_type(
	int		yy_type);

    inline const char *yy_restore_data(
	const char		*yy_data_ptr);

    inline char *yy_save_data(
	char			*yy_data_ptr);

    inline size_t yy_sizeof_data(void);

 protected:

    yy_lex_static_obj		yy_lex_static_part;
    yy_lex_dynamic_obj		yy_lex_dynamic_part;
    int                         yy_lex_nterm_lhead_ix;
    int                         yy_lex_rdc_ix;
    int                         *yy_lex_nterm_lhead;
    int                         *yy_lex_rdc_state;
    static yy_lex_ptr yy_far    yy_lex_cur_obj_ptr;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline functions for the lexer object, defined above.
//  These inline functions do not depend on the parser object or the user's
//  union declaration.
//
//////////////////////////////////////////////////////////////////////////////


inline yy_lex_ptr &yy_lex_cur_obj()
    { return(yy_lex_obj::yy_lex_cur_obj_ptr); }

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_ins(yy_lex_array_to_insert, yy_lex_array_length)
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
//////////////////////////////////////////////////////////////////////////////

inline void yy_lex_obj::yy_lex_ins(
    char           *yy_lex_array_to_insert,
    int            yy_lex_array_length)
{

    yy_buf_ins(yy_lex_array_to_insert, yy_lex_array_length);

    yy_lex_engine();
    
}   // yy_lex_ins


inline void yy_lex_obj::yy_lex_pause()         
{ 

    yy_lex_is_done() = yy_true; 

}   // yy_lex_pause

inline void yy_lex_obj::yy_lex_quit()  
{ 

    yy_buf_set_eof();
    yy_lex_pause(); 

}   // yy_lex_quit

inline void yy_lex_obj::yy_lex_resume()        
{ 

    yy_lex_is_done() = yy_false; 

}   // yy_lex_resume

inline void yy_lex_obj::yy_lex_start(int yy_lex_new_class)
{

    yy_lex_class() = yy_lex_new_class; 
    yy_lex_cur_start_state() = yy_lex_start_state()[yy_lex_new_class]; 
    yy_lex_state() = yy_lex_cur_start_state();
    
}   // yy_lex_start
    
inline int yy_lex_obj::yy_lex_rslt_init()
{

#ifdef yy_lex_tkn_count_
    return(++yy_lex_cur_tkn_count());
#else /* yy_lex_tkn_count_ */
    return(0);
#endif /* yy_lex_tkn_count_ */

}   // yy_lex_rslt_init

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_lex_valid_ptr(yy_this_lex)
//
//  yy_lex_valid_ptr checks the validity of a pointer to a yy_lex_obj.
//  Before calling the virtual function in the lexer object which performs
//  the check, it checks here for NULL (to avoid unexpected crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_lex_valid_ptr(yy_lex_ptr  yy_this_lex)
{

   if (yy_this_lex != NULL) {
      return(yy_this_lex->yy_lex_valid_obj());       
      }
   else {
      return(yy_false);
      }
   
}  // yy_lex_valid_ptr


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the lexer object declared 
//  above.  These inline functions depend on the parser object.
//
//  Note: "yy_psr.h" is included to allow some mutual recursive inline 
//  functions between the lexer and parser objects.
//
//////////////////////////////////////////////////////////////////////////////


#include "yy_psr.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_abort()
//
//  yy_lex_abort terminates the execution of the lexer object at the next
//  convenient point.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_lex_obj::yy_lex_abort() 
{ 
    yy_lex_state() = yy_lex_cur_start_state(); 

    if (yy_lex_cur_psr() != NULL) {
        if (! yy_lex_cur_psr()->yy_psr_is_done()) { 
            yy_lex_cur_psr()->yy_psr_abort(); 
	    }
        }

    yy_lex_quit(); 
    yy_buf_mark_lhead_read();

}   // yy_lex_abort


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_discard()
//
//  yy_lex_discard sets the type of the next token the lexer will create to
//  be a discard token, which means it will not get passed to the parser.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_lex_obj::yy_lex_discard()           
{ 

    yy_lex_rdc() = yy_discard_type_;

}   // yy_lex_discard


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_lex_rewind()
//
//  yy_lex_rewind sets the lexer to its initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_lex_obj::yy_lex_rewind()
{ 
    yy_lex_state() = yy_lex_cur_start_state(); 
    yy_lex_cur_tkn_count() = 0;
    yy_lex_nterm_lhead_ix = 0;
    yy_lex_rdc_ix = 0;
    yy_lex_is_done() = yy_false;
    yy_lex_error_flag() = yy_false; 

    yy_lex_discard();

    if (yy_lex_cur_inp() != NULL) { 
        yy_lex_cur_inp() -> yy_inp_rewind(); 
        } 

}   // yy_lex_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_ref_ptr &yy_lex_new_rslt()
//
//  yy_lex_new_rslt returns a reference to the result variable when the lexer
//  is not connected to a Yacc++ parser (creating it if needed).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_ptr yy_lex_obj::yy_lex_new_rslt(void)
{

    return(yy_lex_dynamic_part.yy_lex_cur_rslt() ?
	   yy_lex_dynamic_part.yy_lex_cur_rslt() :
	   yy_lex_dynamic_part.yy_lex_cur_rslt() = yy_lex_new_rslt1());

}    // yy_lex_new_rslt


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FORWARDING FUNCTIONS:
//
//  These are the inline function definitions for the forwarding functions
//  of the lexer object declared above.  The forwarding functions are for 
//  user convenience when writing lexer action code.  As a user you may add
//  or delete from this list as convenient to you.  No library code depends
//  on these forwarding functions.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_lex_obj::yy_inp_attached()
{ 

    return(yy_lex_cur_inp()->yy_inp_attached()); 

}   // yy_inp_attached

inline yy_boolean yy_lex_obj::yy_inp_close(
        yy_boolean          yy_free_it)
{

    return(yy_lex_cur_inp()->yy_inp_close(yy_free_it)); 

}   // yy_inp_close

inline const char *yy_lex_obj::yy_inp_filename()
{

    return(yy_lex_cur_inp()->yy_inp_filename()); 

}   // yy_inp_filename

inline yy_boolean yy_lex_obj::yy_inp_not_attached()
{

    return(yy_lex_cur_inp()->yy_inp_not_attached()); 

}   // yy_inp_not_attached

inline yy_inp_ptr &yy_lex_obj::yy_inp_prev_ptr()   
{

    return(yy_lex_cur_inp()->yy_inp_prev_ptr()); 

}   // yy_inp_prev_ptr

inline void yy_lex_obj::yy_inp_rewind()
{

    yy_lex_cur_inp()->yy_inp_rewind(); 

}   // yy_inp_rewind

inline yy_sym_ptr yy_lex_obj::yy_symtab_lookup_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type)
{

    return(yy_lex_cur_symtab()->yy_symtab_lookup_kw(yy_text_ptr, yy_len, 
						    yy_type));

}   // yy_symtab_lookup_kw

inline yy_sym_ptr yy_lex_obj::yy_symtab_lookup(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type)
{

    return(yy_lex_cur_symtab()->yy_symtab_lookup(yy_text_ptr, yy_len, 
						 yy_type)); 

}   // yy_symtab_lookup

inline yy_sym_ptr yy_lex_obj::yy_symtab_lookup_only(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type)
{

    return(yy_lex_cur_symtab()->yy_symtab_lookup_only(yy_text_ptr, yy_len, 
						      yy_type)); 

}   // yy_symtab_lookup_only

inline yy_sym_ptr yy_lex_obj::yy_symtab_lookup_only_kw(
        const char          *yy_text_ptr,
        int                 yy_len,
        int                 yy_type)
{

    return(yy_lex_cur_symtab()->yy_symtab_lookup_only_kw(yy_text_ptr, yy_len, 
							 yy_type)); 

}   // yy_symtab_lookup_only_kw

inline yy_boolean yy_lex_obj::yy_symtab_remove_sym(
        yy_sym_ptr      sy_ptr)
{

    return(yy_lex_cur_symtab()->yy_symtab_remove_sym(sy_ptr)); 

}   // yy_symtab_remove_sym




//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_psr_ptr &yy_lex_cur_psr()
//
//  yy_lex_cur_psr returns a reference to the parser object associated with
//  the lexer.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_psr_ptr &yy_lex_static_obj::yy_lex_cur_psr(void)
{

    return(yy_this_psr_obj);

}    // yy_lex_cur_psr


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_min_type()
//
//  yy_lex_min_type returns a reference to the lowest character or lexer
//  non-terminal number.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_static_obj::yy_lex_min_type(void)
{

    return(yy_this_lex_min_type);

}    // yy_lex_min_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_max_type()
//
//  yy_lex_max_type returns a reference to the highest character or lexer
//  non-terminal number.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_static_obj::yy_lex_max_type(void)
{

    return(yy_this_lex_max_type);

}    // yy_lex_max_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_max_class()
//
//  yy_lex_max_class returns a reference to the maximum class number for the
//  generated lexer.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_static_obj::yy_lex_max_class(void)
{

    return(yy_this_lex_max_class);

}    // yy_lex_max_class


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_lex_cmd()
//
//  yy_lex_cmd returns the lexer command tables.
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_lex_static_obj::yy_lex_cmd(void)
{

    return(yy_this_lex_cmd);

}    // yy_lex_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_lex_start_state()
//
//  yy_lex_start_state returns the initial lexer start state.
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_lex_static_obj::yy_lex_start_state(void)
{

    return(yy_this_lex_start_state);

}    // yy_lex_start_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    char * yy_far *yy_lex_opc_tbl()
//
//  yy_lex_opc_tbl returns the lexer engine opcode spellings for use in
//  traces.
//
//////////////////////////////////////////////////////////////////////////////

inline char * yy_far *yy_lex_static_obj::yy_lex_opc_tbl(void)
{

    return(yy_this_lex_opc_tbl);

}    // yy_lex_opc_tbl


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_inp_ptr &yy_lex_cur_inp()
//
//  yy_lex_cur_inp returns a reference to the pointer the associated input
//  object.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_inp_ptr &yy_lex_dynamic_obj::yy_lex_cur_inp(void)
{

    return(yy_lex_dynamic_data.yy_this_inp_obj);

}    // yy_lex_cur_inp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_ref_ptr &yy_lex_cur_rslt()
//
//  yy_lex_cur_rslt returns a reference to the result variable when the lexer
//  is not connected to a Yacc++ parser.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_ptr &yy_lex_dynamic_obj::yy_lex_cur_rslt(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_rslt_val);

}    // yy_lex_cur_rslt


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_symtab_ptr &yy_lex_cur_symtab()
//
//  yy_lex_cur_symtab returns a reference to the pointer to the associated
//  symtab object.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_symtab_ptr &yy_lex_dynamic_obj::yy_lex_cur_symtab(void)
{

    return(yy_lex_dynamic_data.yy_this_symtab_obj);

}    // yy_lex_cur_symtab


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_lex_is_done()
//
//  yy_lex_is_done returns a reference to the lexer termination flag.  This
//  is true when the lexer is to do no further processing.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_lex_dynamic_obj::yy_lex_is_done(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_is_done);

}    // yy_lex_is_done


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_lex_error_flag()
//
//  yy_lex_error_flag returns a reference to the lexer error flag.  This is
//  true when the lexer is skipping through error characters.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_lex_dynamic_obj::yy_lex_error_flag(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_error_flag);

}    // yy_lex_error_flag


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_cur_tkn_count()
//
//  yy_lex_cur_tkn_count returns a reference to the count of the current
//  token when the manifest constant yy_lex_tkn_count_ is defined.  This
//  becomes the initial value for yy_this_lex_rslt_val.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_dynamic_obj::yy_lex_cur_tkn_count(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_tkn_count);

}    // yy_lex_cur_tkn_count


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_state()
//
//  yy_lex_state returns a reference to the current lexer state.  This
//  describes the lexer state at a particular character.  The state and the
//  input character determine what actions the lexer will take.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_dynamic_obj::yy_lex_state(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_state);

}    // yy_lex_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_class()
//
//  yy_lex_class returns a reference to the current lexer class. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_dynamic_obj::yy_lex_class(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_class);

}    // yy_lex_class


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_cur_start_state()
//
//  yy_lex_cur_start_state returns a reference to the current lexer start
//  state.  This is the state the lexer begins each token in.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_dynamic_obj::yy_lex_cur_start_state(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_cur_start_state);

}    // yy_lex_cur_start_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *&yy_lex_this_cmd()
//
//  yy_lex_this_cmd returns a reference to the current lexer engine action.
//
//////////////////////////////////////////////////////////////////////////////

inline int *&yy_lex_dynamic_obj::yy_lex_this_cmd(void)
{

    return(yy_lex_dynamic_data.yy_this_lex_cmd);

}    // yy_lex_this_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr)
//
//  yy_restore_data copies the dynamic portion of a lexer object from the
//  space reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_lex_dynamic_obj::yy_restore_data(
    const char		*yy_data_ptr)
{

    yy_memmove(&yy_lex_dynamic_data, yy_data_ptr,
	       sizeof(yy_lex_dynamic_data));

    yy_data_ptr += sizeof(yy_lex_dynamic_data);

    return(yy_data_ptr);

}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr)
//
//  yy_save_data copies the dynamic portion of a lexer object to the space
//  reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

inline char *yy_lex_dynamic_obj::yy_save_data(
    char		*yy_data_ptr)
{

    yy_memmove(yy_data_ptr, &yy_lex_dynamic_data,
	       sizeof(yy_lex_dynamic_data));

    yy_data_ptr += sizeof(yy_lex_dynamic_data);

    return(yy_data_ptr);

}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
//
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold the dynamic portion of a lexer object.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_lex_dynamic_obj::yy_sizeof_data(void)
{
    return(sizeof(yy_lex_dynamic_data));

}  // yy_sizeof_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_psr_ptr &yy_lex_cur_psr()
//
//  yy_lex_cur_psr returns a reference to the parser object associated with
//  the lexer.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_psr_ptr &yy_lex_obj::yy_lex_cur_psr(void)
{

    return(yy_lex_static_part.yy_lex_cur_psr());

}    // yy_lex_cur_psr


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_min_type()
//
//  yy_lex_min_type returns a reference to the lowest character or lexer
//  non-terminal number.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_min_type(void)
{

    return(yy_lex_static_part.yy_lex_min_type());

}    // yy_lex_min_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_max_type()
//
//  yy_lex_max_type returns a reference to the highest character or lexer
//  non-terminal number.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_max_type(void)
{

    return(yy_lex_static_part.yy_lex_max_type());

}    // yy_lex_max_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_max_class()
//
//  yy_lex_max_class returns a reference to the maximum class number for the
//  generated lexer.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_max_class(void)
{

    return(yy_lex_static_part.yy_lex_max_class());

}    // yy_lex_max_class


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_lex_cmd()
//
//  yy_lex_cmd returns the lexer command tables.
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_lex_obj::yy_lex_cmd(void)
{

    return(yy_lex_static_part.yy_lex_cmd());

}    // yy_lex_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_lex_start_state()
//
//  yy_lex_start_state returns the initial lexer start state.
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_lex_obj::yy_lex_start_state(void)
{

    return(yy_lex_static_part.yy_lex_start_state());

}    // yy_lex_start_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    char * yy_far *yy_lex_opc_tbl()
//
//  yy_lex_opc_tbl returns the lexer engine opcode spellings for use in
//  traces.
//
//////////////////////////////////////////////////////////////////////////////

inline char * yy_far *yy_lex_obj::yy_lex_opc_tbl(void)
{

    return(yy_lex_static_part.yy_lex_opc_tbl());

}    // yy_lex_opc_tbl


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_inp_ptr &yy_lex_cur_inp()
//
//  yy_lex_cur_inp returns a reference to the pointer the associated input
//  object.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_inp_ptr &yy_lex_obj::yy_lex_cur_inp(void)
{

    return(yy_lex_dynamic_part.yy_lex_cur_inp());

}    // yy_lex_cur_inp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_ref_ptr &yy_lex_cur_rslt()
//
//  yy_lex_cur_rslt returns a reference to the result variable when the lexer
//  is not connected to a Yacc++ parser.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_ptr &yy_lex_obj::yy_lex_cur_rslt(void)
{

    return(yy_lex_dynamic_part.yy_lex_cur_rslt());

}    // yy_lex_cur_rslt


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_symtab_ptr &yy_lex_cur_symtab()
//
//  yy_lex_cur_symtab returns a reference to the pointer to the associated
//  symtab object.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_symtab_ptr &yy_lex_obj::yy_lex_cur_symtab(void)
{

    return(yy_lex_dynamic_part.yy_lex_cur_symtab());

}    // yy_lex_cur_symtab


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_lex_is_done()
//
//  yy_lex_is_done returns a reference to the lexer termination flag.  This
//  is true when the lexer is to do no further processing.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_lex_obj::yy_lex_is_done(void)
{

    return(yy_lex_dynamic_part.yy_lex_is_done());

}    // yy_lex_is_done


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_lex_error_flag()
//
//  yy_lex_error_flag returns a reference to the lexer error flag.  This is
//  true when the lexer is skipping through error characters.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_lex_obj::yy_lex_error_flag(void)
{

    return(yy_lex_dynamic_part.yy_lex_error_flag());

}    // yy_lex_error_flag


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_cur_tkn_count()
//
//  yy_lex_cur_tkn_count returns a reference to the count of the current
//  token when the manifest constant yy_lex_tkn_count_ is defined.  This
//  becomes the initial value for yy_this_lex_rslt_val.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_cur_tkn_count(void)
{

    return(yy_lex_dynamic_part.yy_lex_cur_tkn_count());

}    // yy_lex_cur_tkn_count


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_state()
//
//  yy_lex_state returns a reference to the current lexer state.  This
//  describes the lexer state at a particular character.  The state and the
//  input character determine what actions the lexer will take.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_state(void)
{

    return(yy_lex_dynamic_part.yy_lex_state());

}    // yy_lex_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_class()
//
//  yy_lex_class returns a reference to the current lexer class
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_class(void)
{

    return(yy_lex_dynamic_part.yy_lex_class());

}    // yy_lex_class


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_lex_cur_start_state()
//
//  yy_lex_cur_start_state returns a reference to the current lexer start
//  state.  This is the state the lexer begins each token in.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_lex_obj::yy_lex_cur_start_state(void)
{

    return(yy_lex_dynamic_part.yy_lex_cur_start_state());

}    // yy_lex_cur_start_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *&yy_lex_this_cmd()
//
//  yy_lex_this_cmd returns a reference to the current lexer engine action.
//
//////////////////////////////////////////////////////////////////////////////

inline int *&yy_lex_obj::yy_lex_this_cmd(void)
{

    return(yy_lex_dynamic_part.yy_lex_this_cmd());

}    // yy_lex_this_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_lex_valid_type(yy_type)
//
//  yy_lex_valid_type checks the validity of a character or non-terminal
//  type.
//
//  yy_type		the character or non-terminal type to check.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_lex_obj::yy_lex_valid_type(
    int			yy_type)
{
    return ((yy_lex_min_type() <= yy_type) && (yy_type <= yy_lex_max_type()));

}  // yy_lex_valid_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_lex_get_opnd(yy_ix)
//
//  yy_lex_get_opnd extracts an operand of a lexer engine action.
//
//  yy_ix		The index of the operand to extract. The index of
//			0 is the opcode, 1 is the first operand, and 2 is
//			the second.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_lex_obj::yy_lex_get_opnd(
    int		yy_ix)
{
    return(yy_lex_this_cmd()[yy_ix]);

}   // yy_lex_get_opnd


inline void yy_lex_obj::yy_lex_valid_rdc_ix(void)
{
    assert(-1 <= yy_lex_rdc_ix && yy_lex_rdc_ix <= yy_lex_rdc_max_);
}


inline void yy_lex_obj::yy_lex_chg_macro(
    int		yy_ix)
{
    yy_lex_state() = yy_lex_get_opnd(yy_ix);
}

inline void yy_lex_obj::yy_lex_epops_macro(
    int		yy_ix)
{
    yy_lex_rdc_ix -= yy_lex_get_opnd(yy_ix);    
}

inline void yy_lex_obj::yy_lex_pop_macro(
    int		yy_ix)
{
    yy_lex_rdc_ix -= yy_lex_get_opnd(yy_ix);
    yy_lex_state() = yy_lex_rdc_state[yy_lex_rdc_ix + 1];    
}

inline void yy_lex_obj::yy_lex_push_macro(void)
{
    yy_lex_valid_rdc_ix();
    ++yy_lex_rdc_ix;
    yy_lex_rdc_state[yy_lex_rdc_ix] = yy_lex_state();    
}


inline void yy_lex_obj::yy_lex_rdc_macro(void)
{
    
    assert(yy_lex_rdc_ix == 0);

    if (yy_lex_cur_psr()->yy_psr_rt_type(0) != yy_discard_type_) { \

#if yy_trace_lex_rdc_ <= yy_trace_
        static char yy_trace_name[4096];
	yy_assert_disable();
        sprintf(yy_trace_name, "lexed[%d]:",
		yy_lex_cur_psr()->yy_psr_rt_type(0));
        yy_err_printf("%s %.*s\n", yy_trace_name, yy_lex_len(), 
            yy_lex_token());
	yy_assert_enable();
#endif /* yy_trace_lex_rdc_ <= yy_trace_ */

        yy_lex_cur_psr()->yy_psr_engine();
        }

    yy_buf_start_tkn();

    yy_lex_cur_psr()->yy_psr_rt_int() = yy_lex_rslt_init();

    yy_lex_state() = yy_lex_cur_start_state();

}

inline void yy_lex_obj::yy_lex_rdc_nterm_macro(void)
{
    
    assert(yy_lex_rdc_ix != 0);

    yy_lex_state() = yy_lex_rdc_state[yy_lex_rdc_ix];

    yy_lex_valid_rdc_ix();
    --yy_lex_rdc_ix;

    yy_lex_nterm_lhead[yy_lex_nterm_lhead_ix] = yy_buf_lhead_char();
    ++yy_lex_nterm_lhead_ix;

    yy_buf_mark_nterm_lhead();

    yy_buf_lhead_char(yy_lex_cur_psr()->yy_psr_rt_type(0));

}


inline void yy_lex_obj::yy_lex_shf_nterm_macro(void)
{

    --yy_lex_nterm_lhead_ix;

    yy_buf_lhead_char(yy_lex_nterm_lhead[yy_lex_nterm_lhead_ix]);

    if (yy_lex_nterm_lhead_ix == 0) {
	yy_buf_mark_nterm_read(); 
	}
    
}

inline void yy_lex_obj::yy_lex_type_macro(
    int		yy_ix)
{
    
    yy_lex_cur_psr()->yy_psr_rt_type(0) = yy_lex_get_opnd(yy_ix);
    
}

//////////////////////////////////////////////////////////////////////////////
//
//  COMPATIBILITY MACROS:
//
//  For backward compatibility, the following macros preserve the old names.
//
//  yy_lex_cur_file        ==> calls yy_lex_cur_inp
//
//////////////////////////////////////////////////////////////////////////////

#define yy_lex_cur_file    yy_lex_cur_inp


#endif /* yy_lex_h_ */
