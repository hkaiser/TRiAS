
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_psr.h
//
//  FILE DESCRIPTION:     header file with parser object declarations
//
//  CLASS HIERARCHY:
//
//               +----------------------+
//               |   constants class    |
//               |     (yy_const.h)     |
//               +----------------------+
//                           |	       
//               +----------------------+     +----------------+
//               |    parser abstract   | has | parser static  |
//               |      base class      |--+--|   data class   |
//               |      (yy_psr.h)      |  |  |   (yy_psr.h)   | 
//               +----------------------+  |  +----------------+
//                           | derives     |  +----------------+
//                           |	           |  | parser dynamic |
//                           |	           +--|   data class   |
//                           |	           |  |   (yy_psr.h)   | 
//                           |	           |  +----------------+
//                           |	           |  +----------------+
//                           |	           |  |  parser input  |
//                           |	           +--|  stack class   |
//                           |	           |  |  (yy_psrsk.h)  |
//                           |	           |  +----------------+
//                           |	           |  +----------------+
//                           |	           |  | parser reduce  |
//                           |	           +--|  stack class   |
//                           |	           |  | (yy_rdcsk.h)   |
//                           |	           |  +----------------+
//                           |	           |  +----------------+
//                           |	           |  | psr backtrack  |
//                           |	           +--|  queue class   |
//                           |	           |  |  (yy_bktrk.h)  |
//                           |	           |  +----------------+
//                           |	           |  +----------------+
//                           |	           |  | psr backtrack  |
//                           |	           +--|  stack class   |
//                           |	              |  (yy_bktrk.h)  |
//                           |	              +----------------+
//                           |
//        +------------------+-------------------+
//        |                  |                   |
// +--------------+  +-----------------+  +--------------+
// | parser class |  |  parser class   |  | parser class |
// | fast tables  |  | readable tables |  | small tables |
// | (yy_psrfa.h) |  |  (yy_psrrd.h)   |  | (yy_psrsm.h) |
// +--------------+  +-----------------+  +--------------+
//        |                  |                   |
//        +------------------+-------------------+
//                           | one of them derives
//                           |
//             +----------------------------+
//             | generated parser class(es) |
//             |     from your grammar      |
//             |       (yy_mypsr.h)         |
//             +----------------------------+
//
//
//  MODIFICATION HISTORY:
//
//  01/04/99	bz/cc	Removed yy_no_myref_inlines_ as it didn't work with
//			several compilers.
//  12/22/98    bz      Make sure inline definitions match declarations.
//                      (Borland C++ caught ones missing inline on the 
//                      definition).
//  05/18/98    bz      return a reference to yy_psr_left_entries so it can
//                      be changed from within the grammar (as was true of
//                      yy_psr_left at previous revs).
//  05/04/98	cc	extracted various sub-objects from the parser object.
//  09/11/97	bz   	support for ANSI C++ headers.
//  08/07/97	bz   	make yy_err_report() virtual for overrides.
//  04/21/97	bz   	added runtime support for decision predicates parsing.
//  10/20/93	bz/cc	removed manifest constants which previously were
//		     	used to recompile specially configured libraries:
//		     	-- removed yy_psr_dmp_ as dumping functions are
//		     	   always present in the parser classes.
//		     	-- removed yy_psr_inline_actions_ as this is no
//		     	   longer possible with base and derived parser
//		     	   classes.  do_action is a member function always
//		     	   present in the generated parser class(es).
//		     	-- removed yy_use_lex_ as using a LEX lexer is
//		     	   now indicated via syntax in the grammar.
//		     	-- removed all table specific generated constants
//		     	   as it's all done with derived classes.
//		     	-- removed yy_psr_abstract_ as this is always an
//		     	   abstract parser base class.
//		     	-- removed yy_psr_knows_parent_ as adding
//		     	   application specific data members and member
//		     	   functions is now done via syntax in the grammar.
//		     	-- ?? yy_has_synas_
//		     	Moved syntax assist function to the error object.
//  07/07/93	bz   	merged yy_psr1.h and yy_psr2.h.
//  06/21/93	bz   	Added yy_psr_display_expected() to parser class.
//  04/05/93	bz   	New forwarding scheme for yy_err_report().
//		     	Also changes for native C++ rewrite of file object.
//		     	Also, removed yy_use_getc_ code.
//  03/22/93	bz   	added yy_export for use of classes in a DLL.
//  02/26/93	bz   	yy_sym1.h now merged into yy_sym.h.
//  09/16/92	bz   	added yy_psr_err_sync() to force a syntax error for
//		     	syntax error synchronization a la yacc YYERROR.
//  09/10/92	bz   	changed yy_psr_last() to cast return value to int
//		     	as pointer differences default to long on the PC
//		     	rather than int as they do on the Sparc.
//  08/07/92	bz   	removed macros and #ifdefs in C++ only version.
//  03/30/90	bz/cc	coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_psr_h_
#define yy_psr_h_


//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES:
//
//  Note all header files are included below except for:
//
//	yy_lex.h which is included after the declaration of the class
//		yy_psr_obj to allow some mutual recursive inline functions
//		between the lexer and parser objects.
//
//      yy_inlin.h which is included after the declaration of the class
//		yy_psr_obj so that the inline functions can depend on the
//		yy_myref.h but not introduce circular header file
//		dependencies.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef yy_use_ansicxx_hdrs_
#include <limits>
using namespace std;
#else
#include <limits.h>
#endif /* yy_use_ansicxx_hdrs_ */

#include "yy_const.h"
#include "yy_err.h"
#include "yy_sym.h"
#include "yy_stdio.h"
#include "yy_bktrk.h"
#include "yy_psrsk.h"
#include "yy_rdcsk.h"
#include "yy_psrmm.h"
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
//  yy_psr_memento_ptr	is a typedef which defines a pointer to a parser
//                      memento object.
//
//  yy_ref_factory_ptr 	is a typedef which defines a pointer to a reference
//                      factory object.
//
//  yy_ref_ptr          is a typedef which defines a pointer to a reference
//                      object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_lex_obj      	*yy_lex_ptr;

typedef class yy_export yy_psr_obj      	*yy_psr_ptr;

typedef class yy_export yy_psr_memento_obj     	*yy_psr_memento_ptr;

typedef class yy_export yy_ref_factory_obj	*yy_ref_factory_ptr;

typedef class yy_export yy_ref_obj		*yy_ref_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  DATA STRUCTURES
//
//  These data structure typedefs are used to hold related information
//  kept in the parser state variables which are arrays.
//
//  yy_psr_start_state_tbl contains information which allows the parser to
//                      start in the appropriate state given a class and
//                      goal non-terminal.
//
//////////////////////////////////////////////////////////////////////////////

typedef struct yy_psr_start_state_tbl_ {
    int yy_psr_sym;
    int yy_psr_state;
    } yy_psr_start_state_tbl;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_static_obj
//
//  The yy_psr_static_obj is the base class which provides the "static" data
//  (that is data which does not normally change as a parse progresses, for
//  example the lexer-parser connection) for a parser object.  Most of this
//  information is the data which is contained in the parser tables
//  generated by Yacc++.
//
//  This class represents the information which is not saved when a parser
//  memento object is created (nor restored when a parser memento is used to
//  create a new parser object or update a running one).  If you, as a user,
//  wish to save any of this information into your parser memento, you will
//  need to code special memento save and restore functions to do so.
//
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_static_obj() constructor for a parser static object.
//
//  ~yy_psr_static_obj()
//			destructor for a parser static object.
//
//  INTERNAL STATE:
//
//  yy_this_psr_min_type
//			the lowest value of a token or non-terminal number.
//
//  yy_this_psr_max_type
//			the highest value of a token or non-terminal number.
//
//  yy_this_psr_tkn_max_type 
//			the highest value of a token number.
//
//  yy_this_psr_num_states
//			the number of states in the parser tables.
//
//  yy_this_psr_max_class
//			the maximum class number for the generated parser.
//
//  yy_this_lex_obj	the lexer object associated with the parser.
//		
//
//  yy_this_psr_cmd	the parser engine actions for the generated parser.
//
//  yy_this_psr_syna	the syntax assist tables for the generated parser.
//
//  yy_this_psr_last_start
//			the last start state for each class in the generated
//			parser.
//
//  yy_this_psr_start_state
//			the start state table for the generated parser.
//
//  yy_this_psr_spelling_tbl
//			spellings for the types defined in the user grammar.
//
//  yy_this_psr_opc_tbl parser engine opcode spellings for use in traces.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_static_obj : public yy_const
{

 public:

    yy_psr_static_obj(
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
        char                        **yy_new_spelling_tbl
        );

    virtual ~yy_psr_static_obj();

    inline const yy_ref_factory_obj &yy_psr_ref_factory(void) const;

    inline yy_lex_ptr &yy_psr_cur_lex(void);

    inline const yy_lex_ptr &yy_psr_cur_lex(void) const;
    
    inline int &yy_psr_min_type(void);

    inline int &yy_psr_max_type(void);

    inline int &yy_psr_tkn_max_type(void);
    
    inline int &yy_psr_num_states(void);
    
    inline int &yy_psr_max_class(void);

    inline int *yy_psr_cmd(void) const;
    
    inline int *yy_psr_syna(void) const;

    inline int *yy_psr_last_start(void) const;

    inline yy_psr_start_state_tbl *yy_psr_start_state(void) const;

    inline char * yy_far *yy_psr_spelling_tbl(void) const;

    inline char * yy_far *yy_psr_opc_tbl(void) const;

 protected:

    const yy_ref_factory_obj	&yy_this_ref_factory;
    yy_lex_ptr                  yy_this_lex_obj;
    int                         yy_this_psr_min_type;
    int                         yy_this_psr_max_type;
    int                         yy_this_psr_tkn_max_type;
    int                         yy_this_psr_num_states;
    int                         yy_this_psr_max_class;
    int                         *yy_this_psr_cmd;
    int                         *yy_this_psr_syna;
    int                         *yy_this_psr_last_start;
    yy_psr_start_state_tbl      *yy_this_psr_start_state;
    char * yy_far 		*yy_this_psr_spelling_tbl;
    static char * yy_far        yy_this_psr_opc_tbl[yy_psr_num_of_opcs_];

};  // yy_psr_static_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_dynamic_obj
//
//  The yy_psr_dynamic_obj is the base class which provides the
//  "dynamic" data (that is data which normally changes as a parse
//  progresses, for example the parser state) for a parser object.
//
//  This class represents the information which is saved when a parser
//  memento object is created (and restored when a parser memento is
//  used to create a new parser object or update a running one).
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_dynamic_obj()
//			constructor for a dynamic portion of a parser
//  			object.
//
//  ~yy_psr_dynamic_obj()
//			destructor for a dynamic portion of a parser
//			object.
//
//  yy_psr_aborts_on_error()
//                      returns a reference to the current parser
//                      abort-on-error value.  When this value is true
//                      and the parser encounters an error, the parser
//                      aborts rather than attempting error recovery.
//
//  yy_restore_data(yy_data_ptr)
//			copies the dynamic portion of a parser object from
//			the space reserved for it in a memento object.
//
//  yy_save_data(yy_data_ptr)
//			copies the dynamic portion of a parser object to
//			the space reserved for it in a memento object.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold the dynamic portion of a parser
//			object.
//
//
//  INTERNAL STATE:
//
//  yy_this_psr_is_done is true when the parser is to do no further
//                      processing.
//
//  yy_this_psr_aborts_on_error
//			is true when the parser should abort when
//			encountering a syntax error rahter than attempting
//			error recovery.
//
//  yy_this_psr_err_value
//			is true when the parser is attempting to recover from
//                      a syntax error.
//
//  yy_this_psr_state 	describes the parser state at a particular token.
//                      The state and the input token determine what
//                      actions the parser will take.
//
//  yy_this_psr_class	the class the parser is parsing with (consulted only
//			when finding the start state).
//
//  yy_this_psr_start_sym
//			the goal symbol the parser is attempting match
//			(consulted only when finding the start state).
//
//  yy_this_psr_cur_start_state
//			the start state the parser begins parsing in
//			(consulted only to begin the parsing).
//
//  yy_this_psr_cmd	the current parser engine action.
//
//  yy_this_psr_bktrk_mode
//			the parser backtracking mode.
//
//////////////////////////////////////////////////////////////////////////////

typedef struct yy_export yy_psr_dymamic_struct_
{
    yy_boolean                  yy_this_psr_is_done;
    yy_boolean                  yy_this_psr_aborts_on_error;
    int                         yy_this_psr_err_value;
    int                         yy_this_psr_state;
    int                         yy_this_psr_class;
    int                         yy_this_psr_start_sym;
    int                         yy_this_psr_cur_start_state;
    int		                *yy_this_psr_cmd;
    yy_const::yy_psr_bktrk_mode_enum 	yy_this_psr_bktrk_mode;
}   yy_psr_dynamic_struct;


class yy_export yy_psr_dynamic_obj
{

 public:

    yy_psr_dynamic_obj(
        yy_boolean 		yy_new_psr_aborts_on_error
        );

    virtual ~yy_psr_dynamic_obj();

    inline yy_boolean &yy_psr_aborts_on_error(void);

    inline yy_const::yy_psr_bktrk_mode_enum &yy_psr_bktrk_mode(void);

    inline int &yy_psr_class(void);

    inline int &yy_psr_cur_start_state(void);

    inline int &yy_psr_error(void);

    inline yy_boolean &yy_psr_is_done(void);

    inline int &yy_psr_state(void);

    inline int &yy_psr_start_sym(void);

    inline int *&yy_psr_this_cmd(void);

    inline const char *yy_restore_data(
	const char		*yy_data_ptr);

    inline char *yy_save_data(
	char			*yy_data_ptr) const;

    inline size_t yy_sizeof_data(void) const;

  protected:

    yy_psr_dynamic_struct	yy_psr_dynamic_data;

};  // yy_psr_dynamic_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_obj
//
//  The yy_psr_obj is the base class which provides the parsing engine for
//  your application.  Each parser object is independent and in conjunction
//  with the parser tables contains complete state information.
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_obj()        constructor for a parser object.
//
//  ~yy_psr_obj()       destructor for a parser object.
//
//  yy_psr(yy_psr_obj)	is called to request that a parse be performed.  When
//                      this function returns, the parser has read all of the
//                      input related to the parse and either accepted it as
//                      a "valid sentence of the grammar" or terminated in an
//                      error state.
//
//  yy_psr()		same as yy_psr(yy_psr_obj).
//
//  yy_psr_abort()      forces the parser to abort (quit).  This function
//			also terminates the lexer.
//
//  yy_psr_acpt()       performs a parser accept action.
//
//  yy_psr_chg          performs a parser change state action.
//
//  yy_psr_cur_lex()    returns the lexer object associated with the parser.
//
//  yy_psr_display_expected()
//                      displays the expected tokens for the current state.
//                      This function is virtual because each table type
//                      requires a different look-up mechanism to determine
//                      which tokens and non-terminals are legal in a given
//                      state.  Users may also wish to override this
//                      function.
//
//  yy_psr_dmp(yy_err_obj, yy_title)
//		        displays the values of the parser state variables.
//
//  yy_psr_do_action()  executes user action code embedded in class grammar
//                      for this parser.  This function is virtual because
//			each generated grammar has a different set of
//			embedded actions.
//
//  yy_psr_do_rdc       performs a parser reduce action by inserting the type
//                      of the tkn_node or nterm_node at the beginning of the
//                      right hand side of the parser stack.  It also inserts
//                      the value of the yy_psr_rslt as the value of the
//                      referenced variable.
//
//  yy_psr_engine()	executes parsing actions until the look-ahead is
//			emptied (or the parser is paused or aborted).  The
//			new lexer engine calls this function instead of
//			yy_psr_ins().
//
//  yy_psr_err()        reports a syntax error to the user based on the
//                      current parser state variables.  This function is
//			virtual because each table type requires a different
//			look-up mechanism for syntax assists.  Users may also
//			wish to override this function.
//
//  yy_psr_err_sync(yy_type, yy_overwrite)
//		 	forces error synchronization by inserting a yy_error
//  			token.
//
//  yy_psr_error()	returns the current parser error value.
//
//  yy_psr_error(yy_new_psr_err_value)
//			sets the current parser error value.
//
//  yy_psr_get_opnd(yy_ix)
//			extracts an operand of a parser engine action.
//
//  yy_psr_ins(yy_new_ref_obj)
//		        is a function to insert a new token into the parser
//			look-ahead and then run the parser to consume it.
//			This is the old interface from a lexer to a parser.
//			It is retained for user use.
//
//  yy_psr_is_done()    returns true if the parser has completed parsing the
//                      input.
//
//  yy_psr_last()       returns the number of tokens, keywords, and parser
//                      non-terminals shifted in the rule.
//
//  yy_psr_next_cmd     looks up the next parser action, for a nx opcode.
//
//  yy_psr_pause()      forces a parser object to pause and stop parsing
//                      tokens.  This function works by pausing the
//                      associated lexer object (and will not pause the
//                      parser until it returns to the lexer).
//
//  yy_psr_pop          performs a parser pop action.
//
//  yy_psr_push         performs the start a sequence of shift actions for a
//                      production.  We save the position in the parser stack
//                      where we will place the first tkn_node/nterm_node of
//                      the shifting sequence.  We save the current state
//                      since the shift will cause us to change states and we
//                      will need to return to this state.
//
//  yy_psr_quit()       forces the parser to quit.  This function does not
//			also terminate the lexer.
//
//  yy_psr_ref(yy_ix)	returns the semantic value of the desired entry in
//			the current rule.
//
//  yy_psr_resume()     allows a parser object to resume parsing characters
//                      after a call to yy_psr_pause().  This function works
//                      by resuming the associated lexer object.
//
//  yy_psr_rewind()     resets the parser and associated lexer into their
//                      initial states and rewinds the associated input
//                      object.
//
//  yy_psr_start()      sets the parser object into the start state.
//
//  yy_psr_type(yy_ix)  returns the type of the desired entry in the current
//  			rule.
//
//  yy_psr_valid_obj()  supports yy_psr_valid_ptr(yy_psr_ptr) for validity
//                      checking of a parser object.  This function is
//			virtual so that different parser object (e.g.
//			the signed parser objects) can have different
//			checks for validity.
//
//  yy_psr_valid_ptr(yy_psr_ptr)
//                      checks a pointer to a parser object for validity.
//
//  yy_psr_valid_type(yy_type)
//			checks the validity of a token or non-terminal type.
//
//  yy_err_report(...)	reports errors to the error object associated with
//			the lexer associated with the parser.  This function
//			is virtual so that users can easily override its
//			behavior.
//
//  yy_restore_data(yy_data_ptr)
//			copies a parser object from the space reserved for
//			it in a memento object.
//
//  yy_save_data(yy_data_ptr)
//			copies a parser object to the space reserved for it
//			in a memento object.
//
//  yy_sizeof_data()	returns the amount of space required in a memento
//			object to hold a parser object.
//
//  Additional parser functions are derived from the yy_psr_stack_obj,
//  yy_psr_rdc_stack_obj, yy_psr_bktrk_queue_obj, and
//  yy_psr_bktrk_stack_obj.  See them for further documentation.
//
//
//  INTERNAL STATE:
//
//  yy_psr_last_obj_ptr	the last parser object constructed.
//
//  Additional internal state is derived from the yy_psr_static_obj,
//  yy_psr_dynamic_obj, yy_psr_stack_obj, yy_psr_rdc_stack_obj,
//  yy_psr_bktrk_queue_obj, and yy_psr_bktrk_stack_obj.  See them for
//  further documentation.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_obj : public yy_const
{

 public:

    yy_psr_obj(
        yy_boolean                  yy_new_psr_aborts_on_error,
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
        const yy_ref_factory_obj    &yy_new_ref_factory,
        int                         yy_new_psr_max_class,
        int                         yy_new_psr_left_max = yy_psr_left_max_,
        int                         yy_new_psr_rt_max = yy_psr_rt_max_,
        int                         yy_new_psr_rdc_max = yy_psr_rdc_max_,
	int			    yy_new_psr_bktrk_max = yy_psr_bktrk_max_,
	int			    yy_new_psr_bktrk_stack_max = yy_psr_bktrk_stack_max_
        );

    virtual ~yy_psr_obj();

    friend inline int yy_psr(
        yy_psr_ptr   	yy_this_psr_obj
        );

    inline int yy_psr(void);

    inline void yy_psr_abort(void);

    inline yy_boolean &yy_psr_aborts_on_error(void);

    inline void yy_psr_acpt(void);

    inline yy_const::yy_psr_bktrk_mode_enum &yy_psr_bktrk_mode(void);

    inline void yy_psr_bktrk_pop(void);

    inline void yy_psr_bktrk_push(void);

    inline yy_boolean yy_psr_bktrk_queue_empty(void) const;
    
    inline size_t yy_psr_bktrk_queue_entries(void);
    
    inline yy_ref_obj &yy_psr_bktrk_queue_entry(void) const;

    inline yy_ref_obj &yy_psr_bktrk_queue_entry(
	size_t			yy_ix) const;

    inline int yy_psr_bktrk_queue_int(
	size_t			yy_ix) const;

    inline int &yy_psr_bktrk_queue_int(
	size_t			yy_ix);

    inline void yy_psr_bktrk_queue_push(
	yy_ref_obj		&yy_new_bktrk_entry);

    inline size_t yy_psr_bktrk_queue_read_ix(void) const;
    
    inline void yy_psr_bktrk_queue_redo(
	size_t 			yy_redo_count);

    inline void yy_psr_bktrk_queue_remove(
	size_t 			yy_remove_count);

    inline void yy_psr_bktrk_queue_reset_to(
	size_t 			yy_new_read_ix);

    inline void yy_psr_bktrk_queue_rewind(void);
    
    inline int yy_psr_bktrk_queue_type(
	size_t			yy_ix) const;

    inline int &yy_psr_bktrk_queue_type(
	size_t			yy_ix);

    inline yy_boolean yy_psr_bktrk_read(void);

    inline void yy_psr_bktrk_redo(void);

    inline yy_boolean yy_psr_bktrk_stack_empty(void) const;
    
    inline size_t yy_psr_bktrk_stack_entries(void);
    
    inline void yy_psr_bktrk_stack_grow();

    inline void yy_psr_bktrk_stack_pop(
	size_t 			yy_pop_count);

    inline void yy_psr_bktrk_stack_push(
	size_t			yy_new_psr_bktrk_start);

    inline void yy_psr_bktrk_stack_rewind(void);
    
    inline size_t &yy_psr_bktrk_start(void) const;

    inline size_t &yy_psr_bktrk_start(
	size_t			yy_ix) const;

    inline void yy_psr_chg(
	int		yy_ix);

    inline int &yy_psr_class(void);

    inline int *yy_psr_cmd(void) const;
    
    inline yy_lex_ptr &yy_psr_cur_lex(void);

    inline const yy_lex_ptr &yy_psr_cur_lex(void) const;

    inline int &yy_psr_cur_start_state(void);

    virtual void yy_psr_display_expected(void) = 0;

    virtual void yy_psr_dmp(
        yy_err_ptr  	yy_this_err_obj,
        const char  	*yy_dmp_title);

    inline void yy_psr_dmp(
        yy_err_ptr  	yy_this_err_obj,
        const char  	*yy_dmp_title) const;

    inline void yy_psr_dmp(
        const char  	*yy_dmp_title = 0) const;

    inline void yy_psr_do_rdc(
	int		yy_ix);

    virtual void yy_psr_engine(void) = 0;

    virtual void yy_psr_err(void) = 0;

    inline void yy_psr_err_sync(
	int		yy_type = 0,
	yy_boolean	yy_overwrite = yy_false
	);

    inline int &yy_psr_error(
	int		yy_new_psr_err_value);

    inline int &yy_psr_error(void);

    inline int yy_psr_get_opnd(
	int		yy_ix);

    inline void yy_psr_ins(
        yy_ref_obj	&yy_psr_tkn_ref_val);

    inline yy_boolean &yy_psr_is_done(void);

    inline size_t yy_psr_last(void);

    inline size_t &yy_psr_left_entries(void);

    inline yy_ref_obj &yy_psr_left_entry(
	size_t			yy_ix) const;

    inline void yy_psr_ign(void);

    inline int *yy_psr_last_start(void) const;

    inline int yy_psr_left_int(
	size_t			yy_ix) const;

    inline int &yy_psr_left_int(
	size_t			yy_ix);

    inline void yy_psr_left_pop(
	size_t			yy_pop_count = 1);

    inline void yy_psr_left_pop_to(
	size_t 			yy_new_psr_left_top);

    inline void yy_psr_left_remove(
	size_t			yy_ix,
	size_t			yy_remove_count = 1);

    inline int yy_psr_left_type(
	size_t			yy_ix) const;

    inline int &yy_psr_left_type(
	size_t			yy_ix);

    inline int &yy_psr_max_class(void);

    inline int &yy_psr_max_type(void);

    inline int &yy_psr_min_type(void);

    inline int &yy_psr_num_states(void);
    
    inline void yy_psr_next_cmd(
	int		yy_ix);

    inline char * yy_far *yy_psr_opc_tbl(void) const;

    inline void yy_psr_pause(void);

    inline void yy_psr_pop(
	int		yy_ix);

    inline void yy_psr_push(void);

    inline void yy_psr_quit(void);

    inline int &yy_psr_rdc() const;

    inline int &yy_psr_rdc(
	int			yy_new_type);

    inline size_t yy_psr_rdc_stack_entries(void);

    inline void yy_psr_rdc_stack_push(
	int 			yy_new_psr_rdc_state,
	size_t			yy_new_psr_rdc_start,
	yy_ref_obj		&yy_new_psr_rdc_rslt);

    inline void yy_psr_rdc_stack_push_if_empty(
	int 			yy_new_psr_rdc_state,
	size_t			yy_new_psr_rdc_start,
	yy_ref_obj		&yy_new_psr_rdc_rslt);

    inline void yy_psr_rdc_stack_pop(
	size_t 			yy_pop_count);

    inline void yy_psr_rdc_stack_rewind(void);

    inline size_t &yy_psr_rdc_start(void) const;

    inline size_t &yy_psr_rdc_start(
	size_t			yy_ix) const;

    inline int &yy_psr_rdc_state(void);

    inline int &yy_psr_rdc_state(
	size_t			yy_ix) const;

    inline yy_ref_obj &yy_psr_ref(
	size_t		yy_ix) const;

    inline const yy_ref_factory_obj &yy_psr_ref_factory(void) const;
    
    inline void yy_psr_resume(void);

    inline void yy_psr_rewind(void);

    inline yy_ref_obj &yy_psr_rslt(void) const;

    inline yy_ref_obj &yy_psr_rslt(
	size_t			yy_ix) const;

    inline int yy_psr_rslt_int(
	size_t			yy_ix) const;

    inline int &yy_psr_rslt_int(
	size_t			yy_ix);

    inline int yy_psr_rslt_type(
	size_t			yy_ix) const;

    inline int &yy_psr_rslt_type(
	size_t			yy_ix);

    inline void yy_psr_rt_create(void);

    inline void yy_psr_rt_create_if_empty(void);

    inline yy_boolean yy_psr_rt_empty(void) const;

    inline size_t yy_psr_rt_entries(void) const;

    inline int yy_psr_rt_int(void) const;

    inline int &yy_psr_rt_int(void);

    inline int yy_psr_rt_int(
	size_t			yy_ix) const;

    inline int &yy_psr_rt_int(
	size_t			yy_ix);

    inline void yy_psr_rt_pop(
	size_t 			yy_pop_count);

    inline void yy_psr_rt_rewind(void);

    inline yy_ref_obj &yy_psr_rt_top(void) const;

    inline int yy_psr_rt_type(void) const;

    inline int &yy_psr_rt_type(void);

    inline int yy_psr_rt_type(
	size_t			yy_ix) const;

    inline int &yy_psr_rt_type(
	size_t			yy_ix);

    inline void yy_psr_shf(void);

    inline char * yy_far *yy_psr_spelling_tbl(void) const;

    inline enum yy_psr_stack_layout_enum &yy_psr_stack_layout(void);

    inline void yy_psr_stack_rewind(void);
    
    virtual void yy_psr_start(
        int     	yy_psr_new_class,
        int     	yy_psr_new_start);

    inline yy_psr_start_state_tbl *yy_psr_start_state(void) const;

    inline int &yy_psr_start_sym(void);

    inline int &yy_psr_state(void);

    inline int *yy_psr_syna(void) const;

    inline int *&yy_psr_this_cmd(void);

    inline int &yy_psr_tkn_max_type(void);
    
    inline int yy_psr_type(
	size_t		yy_ix) const;

    inline int &yy_psr_type(
	size_t		yy_ix);

    virtual yy_boolean yy_psr_valid_obj(void) const;

    inline yy_boolean yy_psr_valid_type(
	int		yy_type);

    friend inline yy_boolean yy_psr_valid_ptr(
        yy_psr_ptr	yy_this_psr);

    virtual const char *yy_restore_data(
	const char	*yy_data_ptr);

    virtual char *yy_save_data(
	char		*yy_data_ptr) const;

    virtual size_t yy_sizeof_data(void) const;

    virtual int yy_err_report(
        int         	yy_err_num,
        ...);

    virtual int yy_err_printf(
        const char *yy_err_fmt,
        ...
        );

    virtual int yy_err_puts(
        const char *yy_text
        );

    virtual int yy_err_syntax_assist(
        int     yy_syna_num
        );

 protected:

    yy_psr_static_obj		yy_psr_static_part;
    yy_psr_dynamic_obj		yy_psr_dynamic_part;
    yy_psr_stack_obj		yy_psr_stack_part;
    yy_psr_rdc_stack_obj	yy_psr_rdc_stack_part;
    yy_psr_bktrk_queue_obj	yy_psr_bktrk_queue_part;
    yy_psr_bktrk_stack_obj	yy_psr_bktrk_stack_part;
    static yy_psr_ptr yy_far    yy_psr_last_obj_ptr;

};  // yy_psr_obj


//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES:
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_lex.h"

//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the parser objects
//  declared above.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr(yy_this_psr)
//
//  yy_psr() executes the parser.  This function is the uppermost parser
//  entry point which calls the lexer and reports whether the parse
//  successfully completes or terminates with an error.
//
//  yy_this_psr_obj     is the parser object for parsing
//
//  yy_psr() returns the error code stored as the value of yy_psr_err.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr(
        yy_psr_ptr   yy_this_psr_obj)
{
    assert(yy_this_psr_obj != NULL);

//  if there is a parser object, run it

    if (yy_this_psr_obj != NULL) {
        return(yy_this_psr_obj -> yy_psr());
        }

    return(-1); // should never get here

}   // yy_psr


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr(void)
//
//  yy_psr() executes the parser.  This function is the uppermost parser
//  entry point which calls the lexer and reports whether the parse
//  successfully completes or terminates with an error.
//
//  yy_psr() returns the error code stored as the value of yy_psr_err.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr(void)
{

//  run the lexer until it quits

    if (yy_psr_cur_lex() != NULL) {
	yy_psr_cur_lex() -> yy_lex();
	}

//  return the parser error state

    return(yy_psr_error());

}   // yy_psr


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_abort()
//
//  yy_psr_abort forces the parser to abort (quit).  This function also
//  terminates the lexer.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_abort(void)
{

//  stop the parser

    yy_psr_quit();

//  if the lexer is still running, stop it also

    if (yy_psr_cur_lex() != NULL) {
        if (! yy_psr_cur_lex()->yy_lex_is_done()) {
            yy_psr_cur_lex()->yy_lex_abort();
            }
        }

}   // yy_psr_abort


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_psr_aborts_on_error()
//
//  yy_psr_aborts_on_error returns a reference to the current parser
//  abort-on-error value.  When this value is true and the parser encounters
//  an error, the parser aborts rather than attempting error recovery.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_psr_obj::yy_psr_aborts_on_error(void)
{

    return(yy_psr_dynamic_part.yy_psr_aborts_on_error());

}    // yy_psr_aborts_on_error



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_acpt()
//
//  yy_psr_acpt performs a parser accept action.  This is the action the
//  parser takes when it has recognized a complete "sentence" of the grammar
//  including the terminating yy_eof token.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_acpt(void)
{
    yy_psr_abort();

}   // yy_psr_acpt


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_push()
//
//  A backtrack push indicates it is the beginning of a decision making
//  predicate and needs a push.  A backtrack push starts saving the
//  tokens (which will later be re-parsed).
//
//  This function assumes that it is being called in the same manner that
//  parser objects use it.  In particular, it assumes that there is one
//  entry in the right hand side, which is the lookahead for this backtrack
//  push.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_push()
{

//  the correct action depends upon the backtrack mode

    switch (yy_psr_bktrk_mode()) {
        default:
	    yy_err_report(409, yy_psr_bktrk_mode());
	    yy_assert_fail("unknown backtracking mode", __FILE__, __LINE__);

	case(yy_psr_done_bktrk_):
	case(yy_psr_no_bktrk_):

	    //  the stack should be empty

	    assert(yy_psr_bktrk_stack_empty());

	    //  push the backtracking reset pointer onto its stack.

	    yy_psr_bktrk_stack_push(
		yy_psr_bktrk_queue_entries());

	    //  save the first token in the insertion area, because the
	    //  yy_psr_ins call for this token has already happened and the
	    //  parser will want this token for backtracking

	    yy_psr_bktrk_queue_push(
		yy_psr_rt_top());

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Saving initial backtrack start");

#endif

	    //  the parser is now inserting into the backtrack queue

	    yy_psr_bktrk_mode() = yy_psr_ins_bktrk_;
	    return;

	case(yy_psr_ins_bktrk_):
	    //  we are already inserting into the backtracking queue
	    //  just save the insertion pointer on the stack

	    yy_psr_bktrk_stack_push(
		yy_psr_bktrk_queue_entries());

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Saving a nested backtrack start");

#endif
	    return;

	case(yy_psr_copy_bktrk_):
	    //  we are already inserting into the backtracking queue
	    //  just save the insertion pointer on the stack

	    yy_psr_bktrk_stack_push(
		yy_psr_bktrk_queue_entries());

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Saving a nested backtrack start");

#endif
	    return;

	case(yy_psr_read_bktrk_):
	    //  the token in the rhs has been re-read already, backup over it

	    yy_psr_bktrk_queue_redo(1);

	    // save the read pointer on the stack

	    yy_psr_bktrk_stack_push(
		yy_psr_bktrk_queue_read_ix());

	    //  fixup the first token in the reading area, because the parser
	    //  may have reduced it to something else

	    yy_psr_ref_factory().yy_ref_factory_assign(
		yy_psr_bktrk_queue_entry(),
		yy_psr_rt_top());

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Saving a rereading backtrack start");

#endif
	    //  the parser is now inserting into the backtrack queue
	    //  and reading from the queue also (i.e. copying)

	    yy_psr_bktrk_mode() = yy_psr_copy_bktrk_;
	    return;
	}

}   // yy_psr_bktrk_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_pop()
//
//  A backtrack pop indicates it is at the end of a decision predicate
//  and it is time to reset to the beginning of the tokens which will
//  be re-parsed.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_pop()
{

// find the insertion pointer which started this decision predicate

    yy_psr_bktrk_queue_reset_to(
	yy_psr_bktrk_start());

// pop the backtracking stack

    yy_psr_bktrk_stack_pop(1);

// clear the right hand side

    yy_psr_rt_rewind();

//  the parser is now reading from the queue

    yy_psr_bktrk_mode() = yy_psr_read_bktrk_;

}   // yy_psr_bktrk_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_bktrk_queue_empty()
//
//  yy_psr_bktrk_queue_empty returns true if the parser backtrack queue is
//  empty (nothing left to read).  The queue is empty if the read and insert
//  indexes match.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_obj::yy_psr_bktrk_queue_empty(void) const
{

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_empty());
    
}   // yy_psr_bktrk_queue_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_bktrk_queue_entries()
//
//  yy_psr_bktrk_queue_entries returns the total number of parser backtrack
//  queue entries.  This is the number of entries that will be read if the
//  queue is reset and then read until empty.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_obj::yy_psr_bktrk_queue_entries(void)
{

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_entries());
    
}   // yy_psr_bktrk_queue_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_bktrk_queue_entry()
//
//  yy_psr_bktrk_queue_entry returns the first entry (the entry to parse next)
//  from the parser backtrack queue.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_bktrk_queue_entry(void) const
{

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_entry());
    
}   // yy_psr_bktrk_queue_entry


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_bktrk_queue_entry(
//			yy_ix)
//
//  yy_psr_bktrk_queue_entry returns the desired entry from the parser
//  backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_bktrk_queue_entry(
    size_t		yy_ix) const
{

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_entry(yy_ix));
    
}   // yy_psr_bktrk_queue_entry


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_bktrk_queue_int(yy_ix) const
//
//  yy_psr_bktrk_queue_int returns the semantic value (as an int) for the
//  desired entry in the parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_bktrk_queue_int(
    size_t		yy_ix) const
{ 

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_int(yy_ix));
    
}   // yy_psr_bktrk_queue_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_bktrk_queue_int(yy_ix)
//
//  yy_psr_bktrk_queue_int returns the semantic value (as an int) for the
//  desired entry in the parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_bktrk_queue_int(
    size_t		yy_ix)
{ 

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_int(yy_ix));
    
}   // yy_psr_bktrk_queue_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_push(
//				yy_new_value)
//			
//  yy_psr_bktrk_queue_push pushes the information for a new entry onto the 
//  parser backtrack queue.
//
//  yy_new_value		the reference object to be pushed onto the
//				parser backtrack queue.  This item becomes
//				the newest (last) entry in the queue.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_queue_push(
    yy_ref_obj		&yy_new_value)
{

    yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_push(yy_new_value);
    
}   // yy_psr_bktrk_queue_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_bktrk_queue_read_ix()
//
//  yy_psr_bktrk_queue_read_ix returns the index of the next entry to be
//  read in the parser backtrack queue.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_obj::yy_psr_bktrk_queue_read_ix(void) const
{

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_read_ix());
    
}   // yy_psr_bktrk_queue_read_ix


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_redo(
//			yy_redo_count)
//
//  yy_psr_bktrk_queue_redo restores the desired number of entries to the
//  parser backtrack queue.  This function moves the read index backward in
//  the queue, so that entries which were previously read will be read
//  again.
//
//  yy_redo_count	the number of entries to restore to the queue.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_queue_redo(
    size_t		yy_redo_count)
{

    yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_redo(yy_redo_count);
    
}   // yy_psr_bktrk_queue_redo


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_remove(
//			yy_remove_count)
//
//  yy_psr_bktrk_queue_remove removes the number of entries desired from the
//  front of the parser backtrack queue.  This function moves the read index
//  forward in the queue, so that entries which are read are removed and
//  will not be read again unless they are restored to the queue.
//
//  yy_remove_count	the number of entries to remove from the queue.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_queue_remove(
    size_t		yy_remove_count)
{

    yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_remove(yy_remove_count);
    
}   // yy_psr_bktrk_queue_remove


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_reset_to(
//			yy_new_read_ix)
//
//  yy_psr_bktrk_queue_reset_to resets the parser backtrack queue read index
//  to the desired entry.  This function can either remove or restore
//  entries to the queue.
//
//  yy_new_read_ix	the new queue read index.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_queue_reset_to(
    size_t		yy_new_read_ix)
{

    yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_reset_to(yy_new_read_ix);
    
}   // yy_psr_bktrk_queue_reset_to


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_rewind()
//
//  yy_psr_bktrk_queue_rewind resets the parser backtrack queue to its
//  initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_queue_rewind(void)
{

    yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_rewind();
    
}   // yy_psr_bktrk_queue_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_bktrk_queue_type(yy_ix) const
//
//  yy_psr_bktrk_queue_type returns the type for the desired entry in the
//  parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_bktrk_queue_type(
    size_t		yy_ix) const
{ 

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_type(yy_ix));
    
}   // yy_psr_bktrk_queue_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_bktrk_queue_type(yy_ix)
//
//  yy_psr_bktrk_queue_type returns the type for the desired entry in the
//  parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_bktrk_queue_type(
    size_t		yy_ix)
{ 

    return(yy_psr_bktrk_queue_part.yy_psr_bktrk_queue_type(yy_ix));
    
}   // yy_psr_bktrk_queue_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_redo()
//
//  A backtrack redo indicates it is at the end of one decision predicate
//  and beginning of another it is time to reset to the beginning of the
//  tokens which will be re-parsed, but not to remove the entry from the
//  backtracking stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_redo()
{

// find the insertion pointer which started this decision predicate

    yy_psr_bktrk_queue_reset_to(
	yy_psr_bktrk_start());

// clear the right hand side

    yy_psr_rt_rewind();

//  the parser is now reading from the queue

    yy_psr_bktrk_mode() = yy_psr_read_bktrk_;

}   // yy_psr_bktrk_redo


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_bktrk_read()
//
//  A backtrack read attempts to fill the parser right-hand from the
//  backtracking area.
//
//  If there are no tokens in the backtracking area, it returns false to
//  indicate that the parser is to return to the lexer and get another token
//  from it.
//
//  If there are tokens in the backtracking area, it takes the first token
//  from the area, puts it into the parser right hand side, and then returns
//  true to indicate that there was a backtrack token available.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_obj::yy_psr_bktrk_read()
{

//  the correct action depends upon the backtrack mode

    switch (yy_psr_bktrk_mode()) {
        default:
	    yy_err_report(409, yy_psr_bktrk_mode());
	    yy_assert_fail("unknown backtracking mode", __FILE__, __LINE__);

	case(yy_psr_ins_bktrk_):

	    // if the parser is not reading from the backtrack queue,
	    // the parser must return to the lexer for the next token

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Getting another token for the backtrack queue");

#endif
	    return(yy_false);

	case(yy_psr_done_bktrk_):
	case(yy_psr_no_bktrk_):
	    return(yy_false);

	case(yy_psr_copy_bktrk_):

	    // if there anything to read, do so

	    if (! yy_psr_bktrk_queue_empty()) break;

	    // otherwise, fix the mode

	    yy_psr_bktrk_mode() = yy_psr_ins_bktrk_;

	    // and tell the parser to return to the lexer

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Need another token for the backtrack queue");

#endif
	    return(yy_false);


	case(yy_psr_read_bktrk_):
	    // if there anything to read, do so

	    if (! yy_psr_bktrk_queue_empty()) break;


	    // otherwise, clear the stacks

	    yy_psr_bktrk_stack_rewind();
	    yy_psr_bktrk_queue_rewind();

	    // fix the mode

	    yy_psr_bktrk_mode() = yy_psr_done_bktrk_;

	    // and tell the parser to return to the lexer

#if yy_trace_psr_actions_ <= yy_trace_
	    yy_psr_dmp(
		yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
		"Exhausted the backtrack queue");

#endif
	    return(yy_false);

	}

// read the token from the backtrack area

    yy_psr_rt_create();
    yy_psr_ref_factory().yy_ref_factory_assign(
	yy_psr_rt_top(),
	yy_psr_bktrk_queue_entry());

    yy_psr_bktrk_queue_remove(1);

#if yy_trace_psr_actions_ <= yy_trace_
    yy_psr_dmp(
	yy_psr_cur_lex()->yy_lex_cur_inp()->yy_inp_cur_err(),
	"Reparsing a backtrack token");

#endif
    return(yy_true);

}   // yy_psr_bktrk_read


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_bktrk_stack_empty()
//
//  yy_psr_bktrk_stack_empty returns true if the parser backtrack stack is
//  empty.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_obj::yy_psr_bktrk_stack_empty(void) const
{

    return(yy_psr_bktrk_stack_part.yy_psr_bktrk_stack_empty());
    
}   // yy_psr_bktrk_stack_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_bktrk_stack_entries()
//
//  yy_psr_bktrk_stack_entries returns the number of entries in the parser
//  backtrack stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_obj::yy_psr_bktrk_stack_entries(void)
{

    return(yy_psr_bktrk_stack_part.yy_psr_bktrk_stack_entries());
    
}   // yy_psr_bktrk_stack_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_pop(
//			yy_pop_count)
//
//  yy_psr_bktrk_stack_pop removes the desired number of entries desired
//  from the parser backtrack stack.
//
//  yy_pop_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_stack_pop(
    size_t		yy_pop_count)
{

    yy_psr_bktrk_stack_part.yy_psr_bktrk_stack_pop(yy_pop_count);
    
}   // yy_psr_bktrk_stack_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_push(
//				yy_new_psr_bktrk_start)
//			
//  yy_psr_bktrk_stack_push pushes a new reset position onto the parser
//  backtrack stack.
//
//  yy_new_psr_bktrk_start	the reset position to push onto the parser
//				backtrack stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_stack_push(
    size_t		yy_new_psr_bktrk_start)
{

    yy_psr_bktrk_stack_part.yy_psr_bktrk_stack_push(yy_new_psr_bktrk_start);
    
}   // yy_psr_bktrk_stack_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_rewind()
//
//  yy_psr_bktrk_stack_rewind resets the parser backtrack stack to its
//  initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_bktrk_stack_rewind(void)
{

    yy_psr_bktrk_stack_part.yy_psr_bktrk_stack_rewind();

}   // yy_psr_bktrk_stack_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_bktrk_start(void)
//
//  yy_psr_bktrk_start returns the current (top) reset position on the
//  parser backtrack stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_obj::yy_psr_bktrk_start(void) const
{

    return(yy_psr_bktrk_stack_part.yy_psr_bktrk_start());
    
}   // yy_psr_bktrk_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_bktrk_start(yy_ix)
//
//  yy_psr_bktrk_start returns the desired reset position in the parser
//  backtrack stack.
//
//  yy_ix		is the index of the desired reset position.  The
//  			index of 0 represents the newset entry in the stack
//  			with less recently added entries having higher
//  			indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_obj::yy_psr_bktrk_start(
    size_t		yy_ix) const
{ 

    return(yy_psr_bktrk_stack_part.yy_psr_bktrk_start(yy_ix));

}   // yy_psr_bktrk_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_chg(yy_ix)
//
//  yy_psr_chg performs a parser change state action.
//
//  yy_ix		The index of the operand giving the state to
//			change to. The index of 0 is the opcode, 1 is
//			the first operand, and 2 is the second.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_chg(
    int		yy_ix)
{
    yy_psr_state() = yy_psr_get_opnd(yy_ix);

}   // yy_psr_chg


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_dmp(yy_this_err_obj, yy_dmp_title)
//
//  yy_psr_dmp() displays the values of the parser state variables.  This 
//  version forwards calls from constant parser objects to the one which
//  handles non-constant parser objects (casting away the const).  Dumping 
//  the parser is safe to apply to constant objects, but it applies functions
//  which used in other contexts are not safe.
//
//  yy_this_err_obj  is an error object where this dump is to be displayed.
//           
//  yy_dmp_title  a character string to identify the dump.  For example, 
//                sometimes you might want to identify your symbol table dump
//                with the breakpoint location.  Otherwise, just pass in NULL.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_dmp(
    yy_err_ptr   yy_this_err_obj, 
    const char   *yy_dmp_title) const
{
    yy_psr_ptr(this)->yy_psr_dmp(yy_this_err_obj, yy_dmp_title);

}   // yy_psr_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_dmp(yy_dmp_title)
//
//  yy_psr_dmp() displays the values of the parser state variables.  This 
//  version forwards calls without an error object, so that it is simpler
//  to request a dump with just a string.  (The order of the arguments in
//  the normal dump call is reversed for simply omitting the error object,
//  but is more intuitive for the case where the error object is supplied.
//  This version corrects that problem.)
//
//  yy_dmp_title  a character string to identify the dump.  For example, 
//                sometimes you might want to identify your symbol table dump
//                with the breakpoint location.  Otherwise, just pass in NULL.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_dmp(
    const char   *yy_dmp_title) const
{

    yy_psr_ptr(this)->yy_psr_dmp(NULL, yy_dmp_title);

}   // yy_psr_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_do_rdc(yy_ix)
//
//  yy_psr_do_rdc performs a parser reduce action by inserting the
//  type of the tkn_node or nterm_node at the beginning of the right
//  hand side of the parser stack.  It also inserts the value of the
//  yy_psr_rslt as the value of the referenced variable.
//
//  yy_ix		The index of the operand containing the reduce
//  			non-terminal. The index of 0 is the opcode, 1
//  			is the first operand, and 2 is the second.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_do_rdc(
    int		yy_ix)
{

//  reset the left side to the beginning of the rule

    yy_psr_left_pop_to(
	yy_psr_rdc_start());

//  return to the starting state

    yy_psr_state() =
	yy_psr_rdc_state();

//  set the type of the reducing non-terminal

    yy_psr_rdc(yy_psr_get_opnd(yy_ix));

//  create a spot for it on the right side

    yy_psr_rt_create();

//  copy the reducing non-terminal to the right side

#ifdef yy_decl_union
    yy_psr_rt_top() = yy_psr_rslt();
#else
    yy_psr_ref_factory().yy_ref_factory_assign(
	yy_psr_rt_top(),
	yy_psr_rslt());
#endif

//  remove the rule from the reduce stack

    yy_psr_rdc_stack_pop(1);

}   // yy_psr_do_rdc


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_err_sync(yy_type, yy_overwrite)
//
//  yy_psr_err_sync forces error synchronization by inserting a yy_error
//  token.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_err_sync(
    int		yy_type,
    yy_boolean	yy_overwrite)
{
    yy_ref_ptr          yy_ref_temp;

//  print trace message if desired

#if yy_trace_after_error_ <= yy_trace_
    if (yy_psr_valid_type(yy_type)) {
	yy_err_printf(
	    "\nInserting parser error_ value of %d (type %s causing the error)\n",
	    yy_type, yy_psr_spelling_tbl()[yy_type - yy_psr_min_type()]);
        }
    else {
	yy_err_printf(
	    "\nInserting parser error_ value of %d (an invalid type)",
	    yy_type);
        }
#endif /* yy_trace_after_error_ <= yy_trace_ */

//  supply a yy_error yy_psr_ref(i) value

#ifdef yy_decl_union
    yy_ref_temp = new yy_ref_obj(yy_error_, yy_type);
#else
    yy_ref_temp = yy_psr_ref_factory().yy_ref_factory_new_obj(
	yy_error_, yy_type);
#endif

//  if we encounter an error before any symbol has even been pushed onto the
//  stack, we add an entry to the stack.  We add this entry so that when we
//  reduce the yy_error to synchronize, we will pop back to the start state.

    yy_psr_rdc_stack_push_if_empty(
	yy_psr_cur_start_state(),
	0,
	*yy_ref_temp);

//  insert the error token as the look-ahead item

    if (! yy_overwrite) {
	yy_psr_rt_create();
    }

#ifdef yy_decl_union
    yy_psr_rt_top() = *yy_ref_temp;
#else
    yy_psr_ref_factory().yy_ref_factory_assign(
	yy_psr_rt_top(), *yy_ref_temp);
#endif

}   // yy_psr_err_sync


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_error()
//
//  yy_psr_error returns the current parser error value.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_error(void)
{

    return(yy_psr_dynamic_part.yy_psr_error());

}   // yy_psr_error


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_error(yy_new_psr_err_value)
//
//  yy_psr_error sets the current parser error value.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_error(
    int		yy_new_psr_err_value)
{
    return(yy_psr_error() = yy_new_psr_err_value);

}   // yy_psr_error


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_get_opnd(yy_ix)
//
//  yy_psr_get_opnd extracts an operand of a parser engine action.
//
//  yy_ix		The index of the operand to extract. The index of
//			0 is the opcode, 1 is the first operand, and 2 is
//			the second.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_get_opnd(
    int		yy_ix)
{
    return(yy_psr_this_cmd()[yy_ix]);

}   // yy_psr_get_opnd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_ign()
//
//  yy_psr_ign implements a ignore action for the parser.  An ignore
//  action removes the top entry on the right side, but does not add
//  it to the left side.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_ign(void)
{

    yy_psr_stack_part.yy_psr_ign();

}   // yy_psr_ign


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_ins(yy_psr_tkn_ref_val)
//
//  yy_psr_ins is the interface to the parser engine.  yy_psr_ins accepts a
//  token and then calls the parser engine to consume all outstanding
//  look-ahead.
//
//  yy_psr_tkn_ref_val  is the token to insert as the next lookahead token.
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
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_ins(
    yy_ref_obj          &yy_psr_tkn_ref_val)
{

//  Make certain there is a slot for the look-ahead token

    if (yy_psr_rt_empty()) {
	yy_psr_rt_create();
	}

//  Make the token the current look-ahead token

#ifdef yy_decl_union
    yy_psr_rt_top() = yy_psr_tkn_ref_val;
#else
    yy_psr_ref_factory().yy_ref_factory_assign(
	yy_psr_rt_top(), yy_psr_tkn_ref_val);
#endif /* yy_decl_union */

//  Call the parsing engine to process the look-ahead

    yy_psr_engine();

}   // yy_psr_ins


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean &yy_psr_is_done()
//
//  yy_psr_is_done returns true if the parser has completed parsing the
//  input.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_psr_obj::yy_psr_is_done(void)
{

    return(yy_psr_dynamic_part.yy_psr_is_done());

}   // yy_psr_is_done


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_last()
//
//  yy_psr_last returns the number of tokens, keywords, and parser
//  non-terminals shifted in the rule.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_obj::yy_psr_last(void)
{
    return(yy_psr_left_entries() -
	   yy_psr_rdc_start());

}   // yy_psr_last


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_left_entries()
//
//  yy_psr_left_entries returns the number of entries in the left side of
//  the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_obj::yy_psr_left_entries(void)
{
    return(yy_psr_stack_part.yy_psr_left_entries());

}   // yy_psr_left_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_left_entry(yy_ix)
//
//  yy_psr_left_entry returns the desired entry in the left side of the
//  parser input stack.
//
//  yy_ix    		the index of the desired entry in the left side of
//			the parser input stack.  The index of 0 represents
//			the oldest entry in the left side with more recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_left_entry(
    size_t		yy_ix) const
{

    return(yy_psr_stack_part.yy_psr_left_entry(yy_ix));

}   // yy_psr_left_entry


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_left_int(yy_ix) const
//
//  yy_psr_left returns the semantic value (as an int) for the desired entry
//  in the left side of the parser input stack.
//
//  yy_ix    		the index of the desired entry in the left side of
//			the parser input stack.  The index of 0 represents
//			the oldest entry in the left side with more recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_left_int(
    size_t		yy_ix) const
{
    return(yy_psr_stack_part.yy_psr_left_int(yy_ix));

}   // yy_psr_left_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_left_int(yy_ix)
//
//  yy_psr_left returns the semantic value (as an int) for the desired entry
//  in the left side of the parser input stack.
//
//  yy_ix    		the index of the desired entry in the left side of
//			the parser input stack.  The index of 0 represents
//			the oldest entry in the left side with more recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_left_int(
    size_t		yy_ix)
{
    return(yy_psr_stack_part.yy_psr_left_int(yy_ix));

}   // yy_psr_left_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_left_pop(yy_pop_count)
//
//  yy_psr_left_pop removes the desired number of entries from the left side
//  of the parser input stack.
//
//  yy_pop_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_left_pop(
    size_t		yy_pop_count)
{

    yy_psr_stack_part.yy_psr_left_pop(yy_pop_count);

}   // yy_psr_left_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_left_pop_to(yy_new_psr_left_top)
//
//  yy_psr_left_pop_to removes the top (last) entries from the left side of
//  the parser input stack so that the desired entry is top (last).
//
//  yy_new_psr_left_top	the new top of the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_left_pop_to(
    size_t		yy_new_psr_left_top)
{

    yy_psr_stack_part.yy_psr_left_pop_to(yy_new_psr_left_top);

}   // yy_psr_left_pop_to


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_left_remove(yy_ix, yy_remove_count)
//
//  yy_psr_left_remove removes the desired number of entries from the left
//  side of the parser input stack.
//
//  yy_ix 		index of the first entry to remove from the left
//  			side of the parser input stack.  This version uses
//			the same "current rule" based numbering as 
//			yy_psr_ref().
//
//  yy_remove_count	the number of entries to remove from the stack.
//
//  The underlying function uses "absolute" numbering without regard to the
//  current rule.  This version converts the two numbering conventions so
//  that the version presented to the user has a "natural" interface that
//  matches the other functions they use.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_left_remove(
    size_t		yy_ix,
    size_t		yy_remove_count)
{

    yy_psr_stack_part.yy_psr_left_remove(yy_psr_rdc_start() + yy_ix - 1, 
	yy_remove_count);
    
}   // yy_psr_left_remove


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_left_type(yy_ix) const
//
//  yy_psr_left returns the type for the desired entry in the left side of
//  the parser input stack.
//
//  yy_ix    		the index of the desired entry in the left side of
//			the parser input stack.  The index of 0 represents
//			the oldest entry in the left side with more recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_left_type(
    size_t		yy_ix) const
{

    return(yy_psr_stack_part.yy_psr_left_type(yy_ix));

}   // yy_psr_left_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_left_type(yy_ix)
//
//  yy_psr_left returns the type for the desired entry in the left side of
//  the parser input stack.
//
//  yy_ix    		the index of the desired entry in the left side of
//			the parser input stack.  The index of 0 represents
//			the oldest entry in the left side with more recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_left_type(
    size_t		yy_ix)
{

    return(yy_psr_stack_part.yy_psr_left_type(yy_ix));

}   // yy_psr_left_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: void yy_psr_next_cmd(yy_ix)
//
//  yy_psr_next_cmd looks up the next parser action, for a nx opcode.
//
//  yy_ix		The index of the operand giving the pointer to the
//			next command. The index of 0 is the opcode, 1
//			is the first operand, and 2 is the second.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_next_cmd(
    int		yy_ix)
{

    yy_psr_this_cmd() = yy_psr_cmd() + yy_psr_get_opnd(yy_ix);

}   // yy_psr_next_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_pause()
//
//  yy_psr_pause forces a parser object to pause and stop parsing tokens.
//  This function works by pausing the associated lexer object (and will not
//  pause the parser until it returns to the lexer).
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_pause(void)
{

    yy_psr_cur_lex()->yy_lex_pause();

}   // yy_psr_pause


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_pop(yy_ix)
//
//  yy_psr_pop performs a parser pop action.
//
//  yy_ix		The index of the operand giving the number of reduce
//			stack entries to pop. The index of 0 is the
//			opcode, 1 is the first operand, and 2 is the
//			second.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_pop(
    int		yy_ix)
{

    yy_psr_rdc_stack_pop(yy_psr_get_opnd(yy_ix));

}   // yy_psr_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_push()
//
//  yy_psr_push performs the start a sequence of shift actions for a
//  production.  We save the position in the parser stack where we
//  will place the first tkn_node/nterm_node of the shifting sequence.
//  We save the current state since the shift will cause us to change
//  states and we will need to return to this state.
//
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_push(void)
{

    yy_psr_rdc_stack_push(
	yy_psr_state(),
	yy_psr_left_entries(),
	yy_psr_rt_top());

}   // yy_psr_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_quit()
//
//  yy_psr_quit forces the parser to quit.  This function does not also
//  terminate the lexer.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_quit(void)
{

    yy_psr_is_done() = yy_true;

}   // yy_psr_quit


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rdc(void)
//
//  yy_psr_rdc returns the reduce type for the top non-terminal on the
//  parser reduce stack.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rdc() const
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc());

}   // yy_psr_rdc


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rdc(yy_new_type)
//
//  yy_psr_rdc sets the reduce type for the top non-terminal on the
//  parser reduce stack.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rdc(
    int			yy_new_type)
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc(yy_new_type));

}   // yy_psr_rdc


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_rdc_stack_entries()
//
//  yy_psr_rdc_stack_entries returns the number of entries in the parser
//  reduce stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_obj::yy_psr_rdc_stack_entries(void)
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc_stack_entries());

}   // yy_psr_rdc_stack_entries



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_pop(
//			yy_pop_count)
//
//  yy_psr_rdc_stack_pop removes the desired number of entries from the
//  parser reduce stack.
//
//  yy_pop_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rdc_stack_pop(
    size_t		yy_pop_count)
{

    yy_psr_rdc_stack_part.yy_psr_rdc_stack_pop(yy_pop_count);

}   // yy_psr_rdc_stack_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_push(yy_new_psr_rdc_state,
//			yy_new_psr_rdc_start, yy_new_psr_rdc_rslt)
//
//  yy_psr_rdc_stack_push pushes the information for a new partially
//  processed non-terminal onto the reduce stack.  This is done at the
//  start of each rule.
//
//  yy_new_psr_rdc_state	the state the non-terminal will be processed
//				in when it reduces.
//
//  yy_new_psr_rdc_start	the index of the yy_psr_left_area containing
//			    	the first token or non-terminal which comprises
//                      	this partially recognized non-terminal.
//
//  yy_new_psr_rdc_rslt 	the reference variable for the result of
//                      	reducing this non-terminal.  This holds the
//                      	information the user manipulates with the
//				yy_psr_rslt macro.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rdc_stack_push(
    int			yy_new_psr_rdc_state,
    size_t		yy_new_psr_rdc_start,
    yy_ref_obj		&yy_new_psr_rdc_rslt)
{

    yy_psr_rdc_stack_part.yy_psr_rdc_stack_push(yy_new_psr_rdc_state,
	yy_new_psr_rdc_start, yy_new_psr_rdc_rslt);

}   // yy_psr_rdc_stack_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_push_if_empty(
//			yy_new_psr_rdc_state, yy_new_psr_rdc_start,
//			yy_new_psr_rdc_rslt)
//
//  yy_psr_rdc_stack_push_if_empty pushes the information for a new partially
//  processed non-terminal onto the reduce stack, but only if the stack is
//  empty.  This is used to guarantee that the stack has one entry in error
//  cases where nothing has been pushed yet.
//
//  yy_new_psr_rdc_state	the state the non-terminal will be processed
//				in when it reduces.
//
//  yy_new_psr_rdc_start	the element of the yy_psr_left_area containing
//			    	the first token or non-terminal which comprises
//                      	this partially recognized non-terminal.
//
//  yy_new_psr_rdc_rslt 	the reference variable for the result of
//                      	reducing this non-terminal.  This holds the
//                      	information the user manipulates with the
//				yy_psr_rslt macro.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rdc_stack_push_if_empty(
    int			yy_new_psr_rdc_state,
    size_t		yy_new_psr_rdc_start,
    yy_ref_obj		&yy_new_psr_rdc_rslt)
{

    yy_psr_rdc_stack_part.yy_psr_rdc_stack_push_if_empty(yy_new_psr_rdc_state,
	yy_new_psr_rdc_start, yy_new_psr_rdc_rslt);

}   // yy_psr_rdc_stack_push_if_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_rewind()
//
//  yy_psr_rdc_stack_rewind resets the reduce stack to its initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rdc_stack_rewind(void)
{

    yy_psr_rdc_stack_part.yy_psr_rdc_stack_rewind();

}   // yy_psr_rdc_stack_rewind



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_rdc_start(void)
//
//  yy_psr_rdc_start returns the index of the first item in the current
//  rule (the top rule on the parser reduce stack).
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_obj::yy_psr_rdc_start(void) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc_start());

}   // yy_psr_rdc_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_rdc_start(yy_ix)
//
//  yy_psr_rdc_start returns the index of the first item of the desired
//  non-terminal rule in the parser reduce stack.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_obj::yy_psr_rdc_start(
    size_t		yy_ix) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc_start(yy_ix));

}   // yy_psr_rdc_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rdc_state(void)
//
//  yy_psr_rdc_state returns the state the current non-terminal (the one
//  which is represented by the top rule on the parser reduce stack) will be
//  processed in after it reduces.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rdc_state(void)
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc_state());

}   // yy_psr_rdc_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rdc_state(yy_ix)
//
//  yy_psr_rdc_state returns the state the desired non-terminal will be
//  processed in after it reduces.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rdc_state(
    size_t		yy_ix) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rdc_state(yy_ix));

}   // yy_psr_rdc_state


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_ref(yy_ix)
//
//  yy_psr_ref returns the desired item in the current rule.
//
//  yy_ix		is the index of the desired entry
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_ref(
    size_t		yy_ix) const
{
    return(yy_psr_left_entry(
	yy_psr_rdc_start() + yy_ix - 1));

}   // yy_psr_ref


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_resume()
//
//  yy_psr_resume allows a parser object to resume parsing characters after
//  a call to yy_psr_pause().  This function works by resuming the
//  associated lexer object.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_resume(void)
{

    yy_psr_cur_lex()->yy_lex_resume();

}   // yy_psr_resume


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rewind()
//
//  yy_psr_rewind resets the parser and associated lexer into their initial
//  states and rewinds the associated input object.
//
//  This function is not defined if we are compiling the library because the
//  lexer rewind function cannot be compiled without a UNION declaration.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rewind(void)
{
    yy_psr_state() = yy_psr_cur_start_state();
    yy_psr_is_done() = yy_false;
    yy_psr_error() = 0;
    yy_psr_stack_rewind();
    yy_psr_rdc_stack_rewind();
    yy_psr_bktrk_queue_rewind();
    yy_psr_bktrk_stack_rewind();
    yy_psr_bktrk_mode() = yy_psr_no_bktrk_;

    if (yy_psr_cur_lex() != NULL) {
	yy_psr_rt_create_if_empty();
        yy_psr_cur_lex() -> yy_lex_rewind();
        }

}   // yy_psr_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_rslt(void)
//
//  yy_psr_rslt returns the semantic value for the current (top)
//  non-terminal on the parser reduce stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_rslt(void) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rslt());

}   // yy_psr_rslt


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_rslt(yy_ix)
//
//  yy_psr_rslt returns the semantic value for the desired non-terminal in
//  the parser reduce stack.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_rslt(
    size_t		yy_ix) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rslt(yy_ix));

}   // yy_psr_rslt


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rslt_int(yy_ix) const
//
//  yy_psr_rslt_int returns the semantic value (as an int) for the desired
//  non-terminal in the parser reduce stack.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_rslt_int(
    size_t		yy_ix) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rslt_int(yy_ix));

}   // yy_psr_rslt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rslt_int(yy_ix)
//
//  yy_psr_rslt_int returns the semantic value (as an int) for the desired
//  non-terminal in the parser reduce stack.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rslt_int(
    size_t		yy_ix)
{

    return(yy_psr_rdc_stack_part.yy_psr_rslt_int(yy_ix));

}   // yy_psr_rslt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rslt_type(yy_ix) const
//
//  yy_psr_rslt_type returns the type for the desired non-terminal in the
//  parser reduce stack.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_rslt_type(
    size_t		yy_ix) const
{

    return(yy_psr_rdc_stack_part.yy_psr_rslt_type(yy_ix));

}   // yy_psr_rslt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rslt_type(yy_ix)
//
//  yy_psr_rslt_type returns the type for the desired non-terminal in the
//  parser reduce stack.
//
//  yy_ix    		the index of the desired entry in the parser reduce
//			stack.  The index of 0 represents the newest entry
//			in the stack with less recently added entries having
//			higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rslt_type(
    size_t		yy_ix)
{

    return(yy_psr_rdc_stack_part.yy_psr_rslt_type(yy_ix));

}   // yy_psr_rslt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_create(void)
//
//  yy_psr_rt_create creates a slot for a new entry on the right
//  (look-ahead) side of the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rt_create(void)
{

    yy_psr_stack_part.yy_psr_rt_create();

}   // yy_psr_rt_create


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_create_if_empty(void)
//
//  yy_psr_rt_create creates a slot for a new entry on the right
//  (look-ahead) side of the parser input stack, but only if the right side
//  is empty.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rt_create_if_empty(void)
{

    yy_psr_stack_part.yy_psr_rt_create_if_empty();

}   // yy_psr_rt_create_if_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_rt_empty()
//
//  yy_psr_rt_empty returns true if the right side of the parser input stack
//  is empty.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_obj::yy_psr_rt_empty(void) const
{

    return(yy_psr_stack_part.yy_psr_rt_empty());

}   // yy_psr_rt_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_rt_entries()
//
//  yy_psr_rt_entries returns the number of entries in the right side of the
//  parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_obj::yy_psr_rt_entries(void) const
{

    return(yy_psr_stack_part.yy_psr_rt_entries());

}   // yy_psr_rt_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rt_int(void) const
//
//  yy_psr_rt_int returns the semantic value (as an int) for the top (newest)
//  entry in the right side of the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_rt_int(void) const
{

    return(yy_psr_stack_part.yy_psr_rt_int());

}   // yy_psr_rt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rt_int(void)
//
//  yy_psr_rt_int returns the semantic value (as an int) for the top (newest)
//  entry in the right side of the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rt_int(void)
{

    return(yy_psr_stack_part.yy_psr_rt_int());

}   // yy_psr_rt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rt_int(yy_ix) const
//
//  yy_psr_rt_int returns the semantic value (as an int) for the desired
//  entry in the right side of the parser input stack.
//
//  yy_ix    		the index of the desired entry in the right side of
//			the parser input stack.  The index of 0 represents
//			the newest entry in the right side with less recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_rt_int(
    size_t		yy_ix) const
{

    return(yy_psr_stack_part.yy_psr_rt_int(yy_ix));

}   // yy_psr_rt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rt_int(yy_ix)
//
//  yy_psr_rt_int returns the semantic value (as an int) for the desired
//  entry in the right side of the parser input stack.
//
//  yy_ix    		the index of the desired entry in the right side of
//			the parser input stack.  The index of 0 represents
//			the newest entry in the right side with less recently
//			added entries having higher indexes.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rt_int(
    size_t		yy_ix)
{

    return(yy_psr_stack_part.yy_psr_rt_int(yy_ix));

}   // yy_psr_rt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_pop(yy_pop_count)
//
//  yy_psr_rt_pop removes the desired number of entries from the right side
//  of the parser input stack.
//
//  yy_pop_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rt_pop(
    size_t		yy_pop_count)
{

    yy_psr_stack_part.yy_psr_rt_pop(yy_pop_count);

}   // yy_psr_rt_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_rewind()
//
//  yy_psr_rt_rewind resets the right side of the parser input stack to its
//  initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_rt_rewind(void)
{

    yy_psr_stack_part.yy_psr_rt_rewind();

}   // yy_psr_rt_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_rt_top()
//
//  yy_psr_rt_top returns the top (newest) value in the right side of the
//  parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_obj::yy_psr_rt_top(void) const
{

    return(yy_psr_stack_part.yy_psr_rt_top());

}   // yy_psr_rt_top


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rt_type() const
//
//  yy_psr_rt_type returns the type of the top (newest) value in the right
//  side of the parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_rt_type(void) const
{

    return(yy_psr_stack_part.yy_psr_rt_type());

}   // yy_psr_rt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rt_type()
//
//  yy_psr_rt_type returns the type of the top (newest) value in the right
//  side of the parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rt_type(void)
{

    return(yy_psr_stack_part.yy_psr_rt_type());

}   // yy_psr_rt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rt_type(yy_ix) const
//
//  yy_psr_rt_type returns the type for the desired entry in the right side
//  of the parser input stack.
//
//  yy_ix    		the index of the desired entry in the right side of
//			the parser input stack.  The index of 0 represents
//			the newest entry in the right side with less recently
//			added entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_rt_type(
    size_t		yy_ix) const
{

    return(yy_psr_stack_part.yy_psr_rt_type(yy_ix));

}   // yy_psr_rt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rt_type(yy_ix)
//
//  yy_psr_rt_type returns the type for the desired entry in the right side
//  of the parser input stack.
//
//  yy_ix    		the index of the desired entry in the right side of
//			the parser input stack.  The index of 0 represents
//			the newest entry in the right side with less recently
//			added entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_rt_type(
    size_t		yy_ix)
{

    return(yy_psr_stack_part.yy_psr_rt_type(yy_ix));

}   // yy_psr_rt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_shf()
//
//  yy_psr_shf implements a shift action for the parser.  A shift action
//  moves the top entry (i.e. a token or non-terminal) from the right
//  (look-ahead) side to the left (within the current non-terminal) side of
//  the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_shf(void)
{

    yy_psr_stack_part.yy_psr_shf();

}   // yy_psr_shf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_type(yy_ix) const
//
//  yy_psr_type returns the type of desired item in the current rule.
//
//  yy_ix		is the index of the desired entry
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_obj::yy_psr_type(
    size_t		yy_ix) const
{
    return(yy_psr_stack_part.yy_psr_left_type(
	yy_psr_rdc_start() + yy_ix - 1));

}   // yy_psr_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_type(yy_ix)
//
//  yy_psr_type returns the type of desired item in the current rule.
//
//  yy_ix		is the index of the desired entry
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_type(
    size_t		yy_ix)
{
    return(yy_psr_stack_part.yy_psr_left_type(
	yy_psr_rdc_start() + yy_ix - 1));

}   // yy_psr_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_valid_ptr(yy_this_psr)
//
//  yy_psr_valid_ptr checks the validity of a pointer to a yy_psr_obj.
//  Before calling the virtual function in the symbol table object which
//  performs the check, it checks here for NULL (to avoid unexpected crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_valid_ptr(
    yy_psr_ptr		yy_this_psr)
{
    if (yy_this_psr != NULL) {
	return(yy_this_psr->yy_psr_valid_obj());
	}
    else {
	return(yy_false);
	}

}  // yy_psr_valid_ptr


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_valid_type(yy_type)
//
//  yy_psr_valid_type checks the validity of a token or non-terminal type.
//
//  yy_type		the token or non-terminal type to check.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_obj::yy_psr_valid_type(
    int			yy_type)
{
    return ((yy_psr_min_type() <= yy_type) && (yy_type <= yy_psr_max_type()));

}  // yy_psr_valid_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr)
//
//  yy_restore_data copies the dynamic portion of a parser object from the
//  space reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_psr_dynamic_obj::yy_restore_data(
    const char		*yy_data_ptr)
{

    yy_memmove(&yy_psr_dynamic_data, yy_data_ptr,
	       sizeof(yy_psr_dynamic_data));

    yy_data_ptr += sizeof(yy_psr_dynamic_data);

    return(yy_data_ptr);

}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr)
//
//  yy_save_data copies the dynamic portion of a parser object to the space
//  reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

inline char *yy_psr_dynamic_obj::yy_save_data(
    char		*yy_data_ptr) const
{

    yy_memmove(yy_data_ptr, &yy_psr_dynamic_data,
	       sizeof(yy_psr_dynamic_data));

    yy_data_ptr += sizeof(yy_psr_dynamic_data);

    return(yy_data_ptr);

}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
//
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold the dynamic portion of a parser object.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_dynamic_obj::yy_sizeof_data(void) const
{
    return(sizeof(yy_psr_dynamic_data));

}  // yy_sizeof_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const yy_ref_factory_obj &yy_psr_ref_factory()
//
//  yy_psr_ref_factory returns the parser's reference factory object.
//
//////////////////////////////////////////////////////////////////////////////

inline const yy_ref_factory_obj &yy_psr_static_obj::yy_psr_ref_factory(void) const
{

    return(yy_this_ref_factory);

}   // yy_psr_ref_factory


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_ptr &yy_psr_cur_lex()
//
//  yy_psr_cur_lex returns the lexer object associated with the parser.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_lex_ptr &yy_psr_static_obj::yy_psr_cur_lex(void)
{

    return(yy_this_lex_obj);

}   // yy_psr_cur_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_ptr &yy_psr_cur_lex()
//
//  yy_psr_cur_lex returns the lexer object associated with the parser.
//
//////////////////////////////////////////////////////////////////////////////

inline const yy_lex_ptr &yy_psr_static_obj::yy_psr_cur_lex(void) const
{

    return(yy_this_lex_obj);

}   // yy_psr_cur_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_min_type()
//
//  yy_psr_min_type returns the minimum type defined in the parser tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_static_obj::yy_psr_min_type(void)
{

    return(yy_this_psr_min_type);

}    // yy_psr_min_type



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_max_type()
//
//  yy_psr_max_type returns the maximum type defined in the parser tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_static_obj::yy_psr_max_type(void)
{

    return(yy_this_psr_max_type);

}    // yy_psr_max_type



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_tkn_max_type()
//
//  yy_psr_tkn_max_type returns the maximum token type defined in the parser
//  tables.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_static_obj::yy_psr_tkn_max_type(void)
{

    return(yy_this_psr_tkn_max_type);

}    // yy_psr_tkn_max_type



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_num_states()
//
//  yy_psr_num_states returns the number of states in the parser tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_static_obj::yy_psr_num_states(void)
{

    return(yy_this_psr_num_states);

}    // yy_psr_num_states



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_max_class()
//
//  yy_psr_max_class returns a reference to the maximum class defined in the
//  parser tables.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_static_obj::yy_psr_max_class(void)
{

    return(yy_this_psr_max_class);

}    // yy_psr_max_class



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_psr_cmd()
//
//  yy_psr_cmd returns the parser command tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_static_obj::yy_psr_cmd(void) const
{

    return(yy_this_psr_cmd);

}    // yy_psr_cmd



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_psr_syna()
//
//  yy_psr_syna returns the parser's syntax assist tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_static_obj::yy_psr_syna(void) const
{

    return(yy_this_psr_syna);

}    // yy_psr_syna



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_psr_last_start()
//
//  yy_psr_last_start returns the parser's last start tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_static_obj::yy_psr_last_start(void) const
{

    return(yy_this_psr_last_start);

}    // yy_psr_last_start



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_psr_start_state_tbl *yy_psr_start_state()
//
//  yy_psr_start_state returns the parser's start state tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline yy_psr_start_state_tbl *yy_psr_static_obj::yy_psr_start_state(void)
    const
{

    return(yy_this_psr_start_state);

}    // yy_psr_start_state



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    char **yy_psr_spelling_tbl()
//
//  yy_psr_spelling_tbl returns the parser's vocabulary spelling tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline char **yy_psr_static_obj::yy_psr_spelling_tbl(void) const
{

    return(yy_this_psr_spelling_tbl);

}    // yy_psr_spelling_tbl



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    char * yy_far *yy_psr_opc_tbl()
//
//  yy_psr_opc_tbl returns the parser's opcode spelling tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline char * yy_far *yy_psr_static_obj::yy_psr_opc_tbl(void) const
{

    return(yy_this_psr_opc_tbl);

}    // yy_psr_opc_tbl


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const yy_ref_factory_obj &yy_psr_ref_factory()
//
//  yy_psr_ref_factory returns the parser's reference factory object.
//
//////////////////////////////////////////////////////////////////////////////

inline const yy_ref_factory_obj &yy_psr_obj::yy_psr_ref_factory(void) const
{

    return(yy_psr_static_part.yy_psr_ref_factory());

}   // yy_psr_ref_factory


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_ptr &yy_psr_cur_lex()
//
//  yy_psr_cur_lex returns the lexer object associated with the parser.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_lex_ptr &yy_psr_obj::yy_psr_cur_lex(void)
{

    return(yy_psr_static_part.yy_psr_cur_lex());

}   // yy_psr_cur_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_ptr &yy_psr_cur_lex()
//
//  yy_psr_cur_lex returns the lexer object associated with the parser.
//
//////////////////////////////////////////////////////////////////////////////

inline const yy_lex_ptr &yy_psr_obj::yy_psr_cur_lex(void) const
{

    return(yy_psr_static_part.yy_psr_cur_lex());

}   // yy_psr_cur_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_min_type()
//
//  yy_psr_min_type returns the minimum type defined in the parser tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_min_type(void)
{

    return(yy_psr_static_part.yy_psr_min_type());

}    // yy_psr_min_type



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_max_type()
//
//  yy_psr_max_type returns the maximum type defined in the parser tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_max_type(void)
{

    return(yy_psr_static_part.yy_psr_max_type());

}    // yy_psr_max_type



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_tkn_max_type()
//
//  yy_psr_tkn_max_type returns the maximum token type defined in the parser
//  tables.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_tkn_max_type(void)
{

    return(yy_psr_static_part.yy_psr_tkn_max_type());

}    // yy_psr_tkn_max_type



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_num_states()
//
//  yy_psr_num_states returns the number of states in the parser tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_num_states(void)
{

    return(yy_psr_static_part.yy_psr_num_states());

}    // yy_psr_num_states



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_max_class()
//
//  yy_psr_max_class returns the maximum class defined in the parser tables.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_max_class(void)
{

    return(yy_psr_static_part.yy_psr_max_class());

}    // yy_psr_max_class



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_psr_cmd()
//
//  yy_psr_cmd returns the parser command tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_obj::yy_psr_cmd(void) const
{

    return(yy_psr_static_part.yy_psr_cmd());

}    // yy_psr_cmd



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_psr_syna()
//
//  yy_psr_syna returns the parser's syntax assist tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_obj::yy_psr_syna(void) const
{

    return(yy_psr_static_part.yy_psr_syna());

}    // yy_psr_syna



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *yy_psr_last_start()
//
//  yy_psr_last_start returns the parser's last start tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline int *yy_psr_obj::yy_psr_last_start(void) const
{

    return(yy_psr_static_part.yy_psr_last_start());

}    // yy_psr_last_start



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_psr_start_state_tbl *yy_psr_start_state()
//
//  yy_psr_start_state returns the parser's start state tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline yy_psr_start_state_tbl *yy_psr_obj::yy_psr_start_state(void) const
{

    return(yy_psr_static_part.yy_psr_start_state());

}    // yy_psr_start_state



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    char **yy_psr_spelling_tbl()
//
//  yy_psr_spelling_tbl returns the parser's vocabulary spelling tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline char **yy_psr_obj::yy_psr_spelling_tbl(void) const
{

    return(yy_psr_static_part.yy_psr_spelling_tbl());

}    // yy_psr_spelling_tbl



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    char * yy_far yy_psr_opc_tbl[yy_psr_num_of_opcs_]()
//
//  yy_psr_opc_tbl returns the parser's opcode spelling tables. 
//
//////////////////////////////////////////////////////////////////////////////

inline char * yy_far *yy_psr_obj::yy_psr_opc_tbl(void) const
{

    return(yy_psr_static_part.yy_psr_opc_tbl());

}    // yy_psr_opc_tbl


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_psr_aborts_on_error()
//
//  yy_psr_aborts_on_error returns a reference to the current parser
//  abort-on-error value.  When this value is true and the parser encounters
//  an error, the parser aborts rather than attempting error recovery.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_psr_dynamic_obj::yy_psr_aborts_on_error(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_aborts_on_error);

}    // yy_psr_aborts_on_error



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_const::yy_psr_bktrk_mode_enum &yy_psr_bktrk_mode()
//
//  yy_psr_bktrk_mode returns a reference to the parser backtracking mode.
//  This mode determines how tokens are saved and reread to implement
//  syntactic predicates.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_const::yy_psr_bktrk_mode_enum &yy_psr_dynamic_obj::yy_psr_bktrk_mode(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_bktrk_mode);

}    // yy_psr_bktrk_mode



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_class()
//
//  yy_psr_class returns a reference to the class the parser is parsing with
//  (consulted only when finding the start state).
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_dynamic_obj::yy_psr_class(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_class);

}    // yy_psr_class



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_cur_start_state()
//
//  yy_psr_cur_start_state returns a reference to the start state the parser
//  begins parsing in (consulted only to begin the parsing).
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_dynamic_obj::yy_psr_cur_start_state(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_cur_start_state);

}    // yy_psr_cur_start_state



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_error()
//
//  yy_psr_error returns a reference to the parser error value.  This value
//  is true when the parser is attempting to recover from a syntax error.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_dynamic_obj::yy_psr_error(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_err_value);

}    // yy_psr_error



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_boolean &yy_psr_is_done()
//
//  yy_psr_is_done returns a reference to parser termination flag.  This is
//  true when the parser is to do no further processing.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean &yy_psr_dynamic_obj::yy_psr_is_done(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_is_done);

}    // yy_psr_is_done



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_state()
//
//  yy_psr_state returns a reference to the parser state.  The state and the
//  input token determine what actions the parser will take.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_dynamic_obj::yy_psr_state(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_state);

}    // yy_psr_state



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_start_sym()
//
//  yy_psr_start_sym returns a reference to the goal symbol the parser is
//  attempting match (consulted only when finding the start state).
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_dynamic_obj::yy_psr_start_sym(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_start_sym);

}    // yy_psr_start_sym



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *&yy_psr_this_cmd()
//
//  yy_psr_this_cmd returns a reference to the current parser engine action.
//
//////////////////////////////////////////////////////////////////////////////

inline int *&yy_psr_dynamic_obj::yy_psr_this_cmd(void)
{

    return(yy_psr_dynamic_data.yy_this_psr_cmd);

}    // yy_psr_this_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_const::yy_psr_bktrk_mode_enum &yy_psr_bktrk_mode()
//
//  yy_psr_bktrk_mode returns a reference to the parser backtracking mode.
//  This mode determines how tokens are saved and reread to implement
//  syntactic predicates.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_const::yy_psr_bktrk_mode_enum &yy_psr_obj::yy_psr_bktrk_mode(void)
{

    return(yy_psr_dynamic_part.yy_psr_bktrk_mode());

}    // yy_psr_bktrk_mode



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_class()
//
//  yy_psr_class returns a reference to the class the parser is parsing with
//  (consulted only when finding the start state).
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_class(void)
{

    return(yy_psr_dynamic_part.yy_psr_class());

}    // yy_psr_class



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_cur_start_state()
//
//  yy_psr_cur_start_state returns a reference to the start state the parser
//  begins parsing in (consulted only to begin the parsing).
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_cur_start_state(void)
{

    return(yy_psr_dynamic_part.yy_psr_cur_start_state());

}    // yy_psr_cur_start_state



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_state()
//
//  yy_psr_state returns a reference to the parser state.  The state and the
//  input token determine what actions the parser will take.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_state(void)
{

    return(yy_psr_dynamic_part.yy_psr_state());

}    // yy_psr_state



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int &yy_psr_start_sym()
//
//  yy_psr_start_sym returns a reference to the goal symbol the parser is
//  attempting match (consulted only when finding the start state).
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_obj::yy_psr_start_sym(void)
{

    return(yy_psr_dynamic_part.yy_psr_start_sym());

}    // yy_psr_start_sym



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    int *&yy_psr_this_cmd()
//
//  yy_psr_this_cmd returns a reference to the current parser engine action.
//
//////////////////////////////////////////////////////////////////////////////

inline int *&yy_psr_obj::yy_psr_this_cmd(void)
{

    return(yy_psr_dynamic_part.yy_psr_this_cmd());

}    // yy_psr_this_cmd


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_psr_stack_layout_enum &yy_psr_stack_layout()
//
//  yy_psr_stack_layout returns the layout of the parser input stack. 
//
//////////////////////////////////////////////////////////////////////////////

inline enum yy_psr_stack_obj::yy_psr_stack_layout_enum &yy_psr_obj::yy_psr_stack_layout(void)
{

    return(yy_psr_stack_part.yy_psr_stack_layout());

}    // yy_psr_stack_layout




//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    void yy_psr_stack_rewind()
//
//  yy_psr_stack_rewind rewinds the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_obj::yy_psr_stack_rewind(void)
{

    yy_psr_stack_part.yy_psr_stack_rewind();

}    // yy_psr_stack_rewind

    
#endif /* yy_psr_h_ */
