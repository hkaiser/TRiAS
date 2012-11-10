
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_rdcsk.h
//  
//  FILE DESCRIPTION:     header file with parser reduce stack object 
//                        declarations
//
//  CLASS HIERARCHY:
//
//               +-------------------------+
//               |  reference stack class  |
//               |       (yy_ref.h)        |
//               +-------------------------+
//                           | derives
//                           |
//         +-----------------+--------------------+
//         |                 |                    |
//  +--------------+  +---------------+  +------------------+
//  | parser input |  | parser reduce |  | parser backtrack |
//  | stack class  |  |  stack class  |  |   queue class    |
//  | (yy_psrsk.h) |  | (yy_rdcsk.h)  |  |   (yy_bktrk.h)   |
//  +--------------+  +---------------+  +------------------+
//         |                 |                    |
//         +-----------------+--------------------+
//                           | all of them are contained in
//                           |
//               +-------------------------+
//               |     parser abstract     |
//               |       base class        |
//               |       (yy_psr.h)        |
//               +-------------------------+
//
//
//  MODIFICATION HISTORY:
//  
//  05/04/98	cc	extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_rdcsk_h_
#define yy_rdcsk_h_

#ifdef yy_use_ansicxx_hdrs_
#include <limits>
using namespace std;
#else
#include <limits.h>
#endif /* yy_use_ansicxx_hdrs_ */

#include "yy_ref.h"

//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_psr_rdc_entry_ptr	is a typedef which defines a pointer to a
//                      	parser reduce stack entry object.
//
//  yy_psr_rdc_stack_ptr 	is a typedef which defines a pointer to a 
//                      	parser reduce stack object.
//
//  yy_ref_factory_ptr 		is a typedef which defines a pointer to a 
//                      	reference factory object.
//
//  yy_ref_ptr          	is a typedef which defines a pointer to a 
//                      	reference object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_psr_rdc_entry_obj	*yy_psr_rdc_entry_ptr;

typedef class yy_export yy_psr_rdc_stack_obj	*yy_psr_rdc_stack_ptr;

typedef class yy_export yy_ref_factory_obj	*yy_ref_factory_ptr;

typedef class yy_export yy_ref_obj        	*yy_ref_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_rdc_entry_obj
//
//  The yy_psr_rdc_entry_obj contains information which is pushed onto
//  the parser stack to represent partially recognized non-terminals.
//
//  Although it would seem natural for the reduce entry object to contain
//  the reference object representing the yy_psr_rslt() for that rule.
//  Including a reference object within a reduce entry or deriving a reduce
//  entry object from a reference object makes the parser depend upon the
//  declaration of the reference object.  Therefore, the reduce stack object
//  holds the reduce entry object and the associated reference object in
//  parallel stacks.
//
//
//  INTERNAL STATE:
//
//  yy_psr_rdc_state	the parser state in which the recognition of the
//			non-terminal began.  When the parser reduces the
//                      non-terminal, it returns to this state, and will
//                      there be able to shift the non-terminal.
//
//  yy_psr_rdc_start	indexes the element of the yy_psr_left_area
//                      containing the first token or non-terminal which
//                      comprises this partially recognized non-terminal.
//
//////////////////////////////////////////////////////////////////////////////

class yy_psr_rdc_entry_obj {

  public:

    int                 yy_psr_rdc_state;
    size_t	        yy_psr_rdc_start;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_rdc_stack_obj
//
//  The yy_psr_rdc_stack_obj holds the reduce entry and associated reference
//  objects.  It represents the entire parser reduce stack.
//
//  The parser reduce stack keeps track of the beginning of rules and the
//  state to be returned to on a reduction.  This allows Yacc++ to reduce
//  the variable length rules which are a result of the direct translation
//  of regular expressions.
//
//  This stack is internal to the parser object.  Users are not expected to
//  manipulate it directly.  If you are tempted to manipulate this stack in
//  a way not described in an example provided in the documentation, please
//  contact technical support first.
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_rdc_stack_obj(yy_new_ref_factory, yy_new_psr_rdc_max)
//			constructor for a parser stack object.
//
//  ~yy_psr_rdc_stack_obj()
//			destructor for a parser stack object.
//
//  yy_ref_stack_grow(yy_new_ref_stack_top) 
//			makes the parser reduce stack larger.  This function
//			overrides the version in the yy_ref_stack_obj,
//			because the reduce stack has two parallel stacks to
//			grow simultaneously.
//
//  yy_psr_rdc()        returns the reduce type for the top non-terminal on 
//  			the parser reduce stack.
//
//  yy_psr_rdc(yy_new_type)
//                      sets the reduce type for the top non-terminal on the
//  			parser reduce stack.
//
//  yy_psr_rdc_stack_entries()
//			returns the number of entries in the parser reduce
//			stack.
//
//  yy_psr_rdc_stack_pop(yy_pop_count)
//			removes the desired number of entries from the
//			parser reduce stack.
//
//  yy_psr_rdc_stack_push(yy_new_psr_rdc_state, yy_new_psr_rdc_start,
//	    yy_new_psr_rdc_rslt)
//			pushes a new non-terminal onto the parser reduce
//			stack.
//
//  yy_psr_rdc_stack_push_if_empty(yy_new_psr_rdc_state, yy_new_psr_rdc_start,
//	    yy_new_psr_rdc_rslt)
//			pushes a new non-terminal onto the parser reduce
//			stack if the stack is empty.
//
//  yy_psr_rdc_stack_rewind()
//			resets the parser reduce stack to its initial state.
//
//  yy_psr_rdc_start()  returns the index of the first token or non-terminal
//                      in the current rule.
//
//  yy_psr_rdc_start(yy_ix)
//			returns the index of the first token or non-terminal
//                      in the desired rule.
//
//  yy_psr_rdc_state()  returns the start state the current rule will reduce
//                      into.
//
//  yy_psr_rdc_state(yy_ix)
//			returns the start state the desired rule will reduce
//                      into.
//
//  yy_psr_rslt()       returns the semantic value for the current 
//  			non-terminal on the parser reduce stack.
//
//  yy_psr_rslt(yy_ix)  returns the semantic value for the desired 
//  			non-terminal in the parser reduce stack.
//
//  yy_psr_rslt_int(yy_ix)
//			returns the semantic value (as an int) for the
//  			desired non-terminal in the parser reduce stack.
//
//  yy_psr_rslt_type(yy_ix)
//                      returns the type for the desired non-terminal in the
//  			parser reduce stack.
//
//  yy_restore_data(yy_data_ptr)
//			copies a parser reduce stack object from the space
//			reserved for it in a memento object.  This function
//			overrides the version in the yy_ref_stack_obj.
//
//  yy_save_data(yy_data_ptr)
//			copies a parser reduce stack object to the space
//			reserved for it in a memento object.  This function
//			overrides the version in the yy_ref_stack_obj.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold a parser reduce stack object.  This
//			function overrides the version in the
//			yy_ref_stack_obj.
//
//
//  INTERNAL STATE:
//
//  yy_psr_rdc_area[]   contains the stack of parser reduce entries.  The 
//                      stack of parser reduce entries represents the
//                      non-terminals which have only been partially
//			recognized.
//
//  yy_ref_stack_area[] contains the stack of parser result values.  The
//			stack of parser result values represents the semantic
//			values for the non-terminals which have only been
//			partially recognized.
//
//  Additional internal state is derived from the yy_ref_stack_obj.  See it
//  for further documentation.
//
//////////////////////////////////////////////////////////////////////////////

class yy_psr_rdc_stack_obj : public yy_ref_stack_obj {

  public:

    yy_psr_rdc_stack_obj(
        const yy_ref_factory_obj	&yy_new_ref_factory,
        size_t 			yy_new_psr_rdc_max = yy_psr_rdc_max_);

    virtual ~yy_psr_rdc_stack_obj();

    virtual void yy_ref_stack_grow(
	size_t			yy_new_ref_stack_top);

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

    inline int &yy_psr_rdc_state(void) const;
    
    inline int &yy_psr_rdc_state(
	size_t			yy_ix) const;
    
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

    virtual const char *yy_restore_data(
	const char		*yy_data_ptr);

    virtual char *yy_save_data(
	char			*yy_data_ptr) const;

    virtual size_t yy_sizeof_data(void) const;

  protected:

    yy_psr_rdc_entry_ptr	yy_psr_rdc_area;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the parser reduce stack
//  object declared above.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rdc(void)
//
//  yy_psr_rdc returns the reduce type for the top non-terminal on the
//  parser reduce stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_rdc_stack_obj::yy_psr_rdc() const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

}   // yy_psr_rdc


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rdc(yy_new_type)
//
//  yy_psr_rdc sets the reduce type for the top non-terminal on the
//  parser reduce stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_rdc_stack_obj::yy_psr_rdc(
    int			yy_new_type)
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

#ifdef yy_decl_union
    yy_ref_stack_area[yy_ref_stack_ix].yy_type() = yy_new_type;
    
    return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
    yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ref_stack_ix) = yy_new_type;
    
    return(yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

}   // yy_psr_rdc


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_rdc_stack_entries()
//
//  yy_psr_rdc_stack_entries returns the number of entries in the parser
//  reduce stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_rdc_stack_obj::yy_psr_rdc_stack_entries(void)
{

    return(yy_ref_stack_obj::yy_ref_stack_entries());

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

inline void yy_psr_rdc_stack_obj::yy_psr_rdc_stack_pop(
    size_t		yy_pop_count)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

    yy_ref_stack_obj::yy_ref_stack_pop(yy_pop_count);

}   // yy_psr_rdc_stack_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_push(
//			yy_new_psr_rdc_state, yy_new_psr_rdc_start,
//			yy_new_psr_rdc_rslt)
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

inline void yy_psr_rdc_stack_obj::yy_psr_rdc_stack_push(
    int			yy_new_psr_rdc_state,
    size_t		yy_new_psr_rdc_start,
    yy_ref_obj		&yy_new_psr_rdc_rslt)
{
    // push the result onto the base object, this will expand the arrays
    // if needed

    yy_ref_stack_obj::yy_ref_stack_push(yy_new_psr_rdc_rslt);
    
    // store the information specific to this class
 
    yy_psr_rdc_area[yy_ref_stack_ix].yy_psr_rdc_state = yy_new_psr_rdc_state;
    yy_psr_rdc_area[yy_ref_stack_ix].yy_psr_rdc_start = yy_new_psr_rdc_start;

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

inline void yy_psr_rdc_stack_obj::yy_psr_rdc_stack_push_if_empty(
    int			yy_new_psr_rdc_state,
    size_t		yy_new_psr_rdc_start,
    yy_ref_obj		&yy_new_psr_rdc_rslt)
{
    // if the stack isn't empty, do nothing

    if (! yy_ref_stack_empty()) return;

    // push the result onto the base object

    yy_ref_stack_obj::yy_ref_stack_push(yy_new_psr_rdc_rslt);
    
    // store the information specific to this class
 
    yy_psr_rdc_area[yy_ref_stack_ix].yy_psr_rdc_state = yy_new_psr_rdc_state;
    yy_psr_rdc_area[yy_ref_stack_ix].yy_psr_rdc_start = yy_new_psr_rdc_start;

}   // yy_psr_rdc_stack_push_if_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_rewind()
//
//  yy_psr_rdc_stack_rewind resets the reduce stack to its initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_rdc_stack_obj::yy_psr_rdc_stack_rewind(void)
{

    yy_ref_stack_obj::yy_ref_stack_rewind();

}   // yy_psr_rdc_stack_rewind



//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_rdc_start(void)
//
//  yy_psr_rdc_start returns the index of the first item in the current 
//  rule (the top rule on the parser reduce stack).
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_rdc_stack_obj::yy_psr_rdc_start(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

    return(yy_psr_rdc_area[yy_ref_stack_ix].yy_psr_rdc_start); 

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

inline size_t &yy_psr_rdc_stack_obj::yy_psr_rdc_start(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_max); 
    assert(yy_ix <= yy_ref_stack_ix);

    return(yy_psr_rdc_area[yy_ix].yy_psr_rdc_start);

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

inline int &yy_psr_rdc_stack_obj::yy_psr_rdc_state(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

    return(yy_psr_rdc_area[yy_ref_stack_ix].yy_psr_rdc_state); 

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

inline int &yy_psr_rdc_stack_obj::yy_psr_rdc_state(
    size_t		yy_ix) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_max);
    assert(yy_ix <= yy_ref_stack_ix); 
   
    return(yy_psr_rdc_area[yy_ix].yy_psr_rdc_state);

}   // yy_psr_rdc_state


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

inline yy_ref_obj &yy_psr_rdc_stack_obj::yy_psr_rslt(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ref_stack_ix]); 
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_ref_stack_ix)); 
#endif /* yy_decl_union */		

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

inline yy_ref_obj &yy_psr_rdc_stack_obj::yy_psr_rslt(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix]);
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_ix));
#endif /* yy_decl_union */		

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

inline int yy_psr_rdc_stack_obj::yy_psr_rslt_int(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_ix); 

    return(yy_ref_stack_int(yy_ix));

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

inline int &yy_psr_rdc_stack_obj::yy_psr_rslt_int(
    size_t		yy_ix)
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_ix); 

    return(yy_ref_stack_int(yy_ix));

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

inline int yy_psr_rdc_stack_obj::yy_psr_rslt_type(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_ix); 

    return(yy_ref_stack_type(yy_ix));

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

inline int &yy_psr_rdc_stack_obj::yy_psr_rslt_type(
    size_t		yy_ix)
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_ref_stack_ix); 

    return(yy_ref_stack_type(yy_ix));

}   // yy_psr_rslt_type


#endif /* yy_rdcsk_h_ */
