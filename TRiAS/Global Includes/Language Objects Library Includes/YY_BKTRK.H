
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_bktrk.h
//  
//  FILE DESCRIPTION:     header file with parser backtracking object 
//                        declarations
//
//  CLASS HIERARCHY:
//
//                 +-------------------------+
//                 |  reference stack class  |
//                 |       (yy_ref.h)        |
//                 +-------------------------+
//                              | derives
//                              |
//                 +-------------------------+ +-------------------------+
//                 |     parser backtrack    | |     parser backtrack    |
//                 |       queue class       | |       stack class       |
//                 |      (yy_bktrk.h)       | |      (yy_bktrk.h)       |
//                 +-------------------------+ +-------------------------+
//                              |        	            |
//                              +---------------------------+
//                              | both are contained in
//                              |
//                 +-------------------------+
//                 |     parser abstract     |
//                 |       base class        |
//                 |       (yy_psr.h)        |
//                 +-------------------------+
//
//
//  MODIFICATION HISTORY:
//  
//  04/03/98	cc	extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_bktrk_h_
#define yy_bktrk_h_

#ifdef yy_use_ansicxx_hdrs_
#include <limits>
using namespace std;
#else
#include <limits.h>
#endif /* yy_use_ansicxx_hdrs_ */

#include "yy_ref.h"
#include "yy_err.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_psr_bktrk_queue_ptr 	is a typedef which defines a pointer to a 
//                      	parser backtrack area object.
//
//  yy_psr_bktrk_stack_ptr 	is a typedef which defines a pointer to a 
//                      	parser backtrack stack object.
//
//  yy_ref_factory_ptr 		is a typedef which defines a pointer to a 
//                      	reference factory object.
//
//  yy_ref_ptr          	is a typedef which defines a pointer to a 
//                      	reference object.
//
//  yy_size_t_ptr          	is a typedef which defines a pointer to a 
//                      	size_t (a system defined integral type)
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_psr_bktrk_queue_obj	*yy_psr_bktrk_queue_ptr;

typedef class yy_export yy_psr_bktrk_stack_obj	*yy_psr_bktrk_stack_ptr;

typedef class yy_export yy_ref_factory_obj	*yy_ref_factory_ptr;

typedef class yy_export yy_ref_obj        	*yy_ref_ptr;

typedef size_t			        	*yy_size_t_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_bktrk_queue_obj
//
//  The yy_psr_bktrk_queue_obj holds the backtrack reference objects which
//  can be backtracked over.  This is essentially a queue (aka fifo).
//  Objects are pushed in one end and read from the other.  The only hitch
//  is that the point which is being read from can be reset (to re-read
//  entries which have already been removed).
//
//  The parser backtrack queue is part of the syntactic predicate processing
//  of Yacc++.  As syntactic predicates are processed, their tokens (and the
//  initial contents of their parser right side, which may include
//  non-terminals) are pushed onto the queue.  If a syntactic predicate
//  fails, the queue is reset and the next predicate then processes the same
//  tokens.  If a predicate succeeds, the queue is also reset and the normal
//  part of the production processes those tokens one last time.
//
//  This queue is internal to the parser object.  Users are not expected to
//  manipulate it directly.  If you are tempted to manipulate this queue in
//  a way not described in an example provided in the documentation, please
//  contact technical support first.
//
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_bktrk_queue_obj(yy_new_psr_bktrk_max)
//			constructor for a parser backtrack queue object.
//
//  ~yy_psr_bktrk_queue_obj()
//			destructor for a parser backtrack queue object.
//
//  yy_psr_bktrk_queue_empty()
//			returns true if the parser backtrack queue is empty
//			(nothing left to read).
//
//  yy_psr_bktrk_queue_entries()
//			returns the total number of entries in the parser 
//			backtrack queue.
//
//  yy_psr_bktrk_queue_entry()
//			returns the first entry (the entry to parse next)
//			from the parser backtrack queue.
//
//  yy_psr_bktrk_queue_entry(yy_ix)
//			returns the desired entry from the parser backtrack
//  			queue.
//
//  yy_psr_bktrk_queue_int(yy_ix)
//			returns the semantic value (as an int) for the 
//			desired entry in the parser backtrack queue.
//
//  yy_psr_bktrk_queue_push(yy_new_bktrk_entry)
//			pushes a new entry onto the parser backtrack queue.
//
//  yy_psr_bktrk_queue_read_ix()
//			returns the index of the next entry to be read in
//			the parser backtrack queue.
//
//  yy_psr_bktrk_queue_redo(yy_redo_count)
//			restores the desired number of entries to the parser
//			backtrack queue.
//
//  yy_psr_bktrk_queue_remove(yy_remove_count)
//			removes the desired number of entries from the
//			parser backtrack queue.
//
//  yy_psr_bktrk_queue_reset_to(yy_new_read_ix)
//			resets the parser backtrack queue read index to the
//			desired entry.
//
//  yy_psr_bktrk_queue_rewind()
//			resets the parser backtrack queue to its initial
//			state.
//
//  yy_psr_bktrk_queue_type(yy_ix)
//			returns the type for the desired entry in the parser
//			backtrack queue.
//
//  INTERNAL STATE:
//
//  yy_psr_bktrk_read_ix
//			the current parsing position in the parser backtrack
//                      queue.  This is where the parser reads its look-ahead
//                      from when backtracking.
//
//  yy_ref_stack_ix 	the position where entries are inserted into the parser
//			backtrack queue.  In versions before the underlying
//			stack was inherited this was yy_psr_bktrk_ins_ix.
//
//  Additional internal state is derived from the yy_ref_stack_obj.  See it
//  for further documentation.
//
//////////////////////////////////////////////////////////////////////////////

class yy_psr_bktrk_queue_obj : public yy_ref_stack_obj {

  public:

    yy_psr_bktrk_queue_obj(
        const yy_ref_factory_obj
				&yy_new_ref_factory,
        size_t 			yy_new_ref_stack_max = yy_ref_stack_max_);

    virtual ~yy_psr_bktrk_queue_obj();

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

    virtual const char *yy_restore_data(
	const char		*yy_data_ptr);

    virtual char *yy_save_data(
	char			*yy_data_ptr) const;

    virtual size_t yy_sizeof_data(void) const;

  protected:

    size_t		yy_bktrk_read_ix;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_bktrk_stack_obj
//
//  The yy_psr_bktrk_stack_obj holds the stack of reset indexes into the
//  parser backtrack queue.  
//
//  The parse backtrack stack is part of the syntactic predicate processing
//  of Yacc++.  When the start of a syntactic predicate is encountered,
//  the position in the parser backtracking queue is recorded, so that when
//  the entries in the queue need to be reprocessed, the queue can be reset
//  to the appropriate point.
//
//  This stack is internal to the parser object.  Users are not expected to
//  manipulate it directly.  If you are tempted to manipulate this stack in
//  a way not described in an example provided in the documentation, please
//  contact technical support first.
//
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_bktrk_stack_obj(yy_new_psr_bktrk_stack_max)
//			constructor for a parser backtrack stack object.
//
//  ~yy_psr_bktrk_stack_obj()
//			destructor for a parser backtrack stack object.
//
//  yy_psr_bktrk_stack_check_grow([yy_new_psr_bktrk_stack_top])
//			makes the parser backtrack stack larger when needed.
//
//  yy_psr_bktrk_stack_empty()
//			returns true if the parser backtrack stack is empty.
//
//  yy_psr_bktrk_stack_entries()
//			returns the number of entries in the parser
//			backtrack stack.
//
//  yy_psr_bktrk_stack_grow(yy_new_psr_bktrk_stack_top)
//			makes the parser backtrack stack larger.
//
//  yy_psr_bktrk_stack_pop(yy_pop_count)
//			removes the desired number of entries from the
//			parser backtrack stack.
//
//  yy_psr_bktrk_stack_push(yy_new_psr_bktrk_start)
//			pushes a new reset position onto the parser
//			backtrack stack.
//
//  yy_psr_bktrk_stack_rewind()
//			resets the parser backtrack stack to its initial
//			state.
//
//  yy_psr_bktrk_stack_start()
//			returns the current (top) reset position on the
//			parser backtrack stack.
//
//  yy_psr_bktrk_stack_start(yy_ix)
//			returns the desired reset position in the parser
//			backtrack stack.
//
//  yy_restore_data(yy_data_ptr)
//			copies a parser backtrack stack object from the
//			space reserved for it in a memento object.
//
//  yy_save_data(yy_data_ptr)
//			copies a parser backtrack stack object to the space
//			reserved for it in a memento object.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold a parser backtrack stack object.
//
//
//  INTERNAL STATE:
//
//  yy_psr_bktrk_stack_area[]   
//			contains the stack of parser reset positions.  The
//			stack of parser reset positions represents the
//			syntactic predicates which have not been resolved.
//
//  yy_psr_bktrk_stack_ix
//			gives the current number of elements the stack
//			holds.  The top element is one less than this index.
//
//  yy_psr_bktrk_stack_max
//			gives the current maximum number of elements the
//			stack can hold.
//
//////////////////////////////////////////////////////////////////////////////

class yy_psr_bktrk_stack_obj : public yy_const {

  public:

    yy_psr_bktrk_stack_obj(
        size_t 			yy_new_psr_bktrk_stack_max = 
				    yy_psr_bktrk_stack_max_);

    virtual ~yy_psr_bktrk_stack_obj();

    inline void yy_psr_bktrk_stack_check_grow();

    inline void yy_psr_bktrk_stack_check_grow(
	size_t			yy_new_psr_bktrk_stack_top);

    inline yy_boolean yy_psr_bktrk_stack_empty(void) const;
    
    inline size_t yy_psr_bktrk_stack_entries(void) const;
    
    inline void yy_psr_bktrk_stack_grow(
	size_t			yy_new_psr_bktrk_stack_top);

    inline void yy_psr_bktrk_stack_pop(
	size_t 			yy_pop_count);

    inline void yy_psr_bktrk_stack_push(
	size_t			yy_new_psr_bktrk_start);

    inline void yy_psr_bktrk_stack_rewind(void);
    
    inline size_t &yy_psr_bktrk_start(void) const;

    inline size_t &yy_psr_bktrk_start(
	size_t			yy_ix) const;

    virtual const char *yy_restore_data(
	const char		*yy_data_ptr);

    virtual char *yy_save_data(
	char			*yy_data_ptr) const;

    virtual size_t yy_sizeof_data(void) const;

  protected:

    yy_size_t_ptr		yy_psr_bktrk_stack_area;
    size_t			yy_psr_bktrk_stack_ix;
    size_t 			yy_psr_bktrk_stack_max;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the parser backtrack queue
//  and stack objects declared above.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_empty()
//
//  yy_psr_bktrk_queue_empty returns true if the parser backtrack queue is
//  empty (nothing left to read).  The queue is empty if the read and insert
//  indexes match.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_empty(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_bktrk_read_ix && yy_bktrk_read_ix <= yy_ref_stack_ix); 
    
    return(yy_ref_stack_ix == yy_bktrk_read_ix); 

}   // yy_psr_bktrk_queue_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_entries()
//
//  yy_psr_bktrk_queue_entries returns the total number of parser backtrack
//  queue entries.  This is the number of entries that will be read if the
//  queue is reset and then read until empty.
//
//  Note that this is the total number of entries in the queue, not just
//  those between the current read index and the insert index.  Therefore,
//  the queue can be empty (as per yy_psr_bktrk_queue_empty()) and yet
//  still have a positive number of entries.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_entries(void)
{
    return(yy_ref_stack_obj::yy_ref_stack_entries());

}   // yy_psr_bktrk_queue_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_entry()
//
//  yy_psr_bktrk_queue_entry returns the first entry (the entry to parse next)
//  from the parser backtrack queue.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_entry(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_bktrk_read_ix && yy_bktrk_read_ix <= yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_bktrk_read_ix]); 
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_bktrk_read_ix)); 
#endif /* yy_decl_union */		

}   // yy_psr_bktrk_queue_entry


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_entry(
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
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_entry(
    size_t		yy_ix) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix]); 
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_ix)); 
#endif /* yy_decl_union */		

}   // yy_psr_bktrk_queue_entry


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_int(yy_ix) const
//
//  yy_psr_bktrk_queue_int returns the semantic value (as an int) for the
//  desired entry in the parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_int(
    size_t		yy_ix) const
{ 
    return(yy_ref_stack_int(yy_ix));

}   // yy_psr_bktrk_queue_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_int(yy_ix)
//
//  yy_psr_bktrk_queue_int returns the semantic value (as an int) for the
//  desired entry in the parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_int(
    size_t		yy_ix)
{ 
    return(yy_ref_stack_int(yy_ix));

}   // yy_psr_bktrk_queue_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_push(
//				yy_new_value)
//			
//  yy_psr_bktrk_queue_push pushes the information for a new entry onto the 
//  parser backtrack queue.
//
//  yy_new_value		the reference object to be pushed onto the
//				parser backtrack queue.  This item becomes
//				the newest (last) entry in the queue.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_push(
    yy_ref_obj		&yy_new_value)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

    // if the new entry overflows the current stack, grow a larger one

    yy_ref_stack_check_grow();

    // now that we have a new entry, copy the info into it

#ifdef yy_decl_union
    yy_ref_stack_area[yy_ref_stack_ix] = yy_new_value;
#else
    yy_ref_factory.yy_ref_factory_array_assign(
	yy_ref_stack_area, yy_ref_stack_ix, yy_new_value);
#endif

    // take a new entry

    ++yy_ref_stack_ix;

}   // yy_psr_bktrk_queue_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_read_ix()
//
//  yy_psr_bktrk_queue_read_ix returns the index of the next entry to be
//  read in the parser backtrack queue.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_read_ix(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_bktrk_read_ix && yy_bktrk_read_ix <= yy_ref_stack_ix); 
   
    return(yy_bktrk_read_ix); 

}   // yy_psr_bktrk_queue_read_ix


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_redo(
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

inline void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_redo(
    size_t		yy_redo_count)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_bktrk_read_ix && yy_bktrk_read_ix <= yy_ref_stack_ix); 
    assert(yy_redo_count <= yy_bktrk_read_ix);
    
//  redo the desired number of entries

    if (yy_redo_count < yy_bktrk_read_ix) {
	yy_bktrk_read_ix -= yy_redo_count;
        }
    else {
	yy_bktrk_read_ix = 0;
        }

}   // yy_psr_bktrk_queue_redo


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_remove(
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

inline void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_remove(
    size_t		yy_remove_count)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_bktrk_read_ix && yy_bktrk_read_ix <= yy_ref_stack_ix); 
    assert(yy_remove_count <= (yy_ref_stack_ix - yy_bktrk_read_ix));
    
//  remove the desired number of entries

    if (yy_remove_count < (yy_ref_stack_ix - yy_bktrk_read_ix)) {
	yy_bktrk_read_ix += yy_remove_count;
        }
    else {
	yy_bktrk_read_ix = yy_ref_stack_ix;
        }
    
}   // yy_psr_bktrk_queue_remove


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_reset_to(
//			yy_new_read_ix)
//
//  yy_psr_bktrk_queue_reset_to resets the parser backtrack queue read index
//  to the desired entry.  This function can either remove or restore
//  entries to the queue.
//
//  yy_new_read_ix	the new queue read index.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_reset_to(
    size_t		yy_new_read_ix)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_new_read_ix && yy_new_read_ix <= yy_ref_stack_ix); 

    yy_bktrk_read_ix = yy_new_read_ix;

}   // yy_psr_bktrk_queue_reset_to


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_rewind()
//
//  yy_psr_bktrk_queue_rewind resets the parser backtrack queue to its
//  initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_rewind(void)
{
    yy_bktrk_read_ix = 0;
    
    yy_ref_stack_obj::yy_ref_stack_rewind();

}   // yy_psr_bktrk_queue_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_type(yy_ix) const
//
//  yy_psr_bktrk_queue_type returns the type for the desired entry in the
//  parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_type(
    size_t		yy_ix) const
{ 
    return(yy_ref_stack_type(yy_ix));

}   // yy_psr_bktrk_queue_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_type(yy_ix)
//
//  yy_psr_bktrk_queue_type returns the type for the desired entry in the
//  parser backtrack queue.
//
//  yy_ix    		the index of the desired entry in the parser
//      		backtrack queue.  The index of 0 represents the
//      		oldest entry in the queue with more recently added
//      		entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_type(
    size_t		yy_ix)
{ 
    return(yy_ref_stack_type(yy_ix));

}   // yy_psr_bktrk_queue_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_check_grow()
//			
//  yy_psr_bktrk_stack_check_grow makes the parser backtrack stack larger
//  when needed.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_check_grow(void)
{
    
    yy_psr_bktrk_stack_check_grow(yy_psr_bktrk_stack_ix + 1);
    
}   // yy_psr_bktrk_stack_check_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_check_grow()
//			
//  yy_psr_bktrk_stack_check_grow makes the parser backtrack stack larger
//  when needed.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_check_grow(
    size_t			yy_new_psr_bktrk_stack_top)
{
    
//  do nothing, if the array still fits

    if (yy_new_psr_bktrk_stack_top <= yy_psr_bktrk_stack_max) return;
    
//  grow array 

    yy_psr_bktrk_stack_grow(yy_new_psr_bktrk_stack_top);
    
}   // yy_psr_bktrk_stack_check_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_empty()
//
//  yy_psr_bktrk_stack_empty returns true if the parser backtrack stack is
//  empty.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_empty(void) const
{
    assert(0 <= yy_psr_bktrk_stack_ix && 
	   yy_psr_bktrk_stack_ix < yy_psr_bktrk_stack_max); 
    
    return(yy_psr_bktrk_stack_ix == 0); 

}   // yy_psr_bktrk_stack_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_entries()
//
//  yy_psr_bktrk_stack_entries returns the number of entries in the parser
//  backtrack stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_entries(void) const
{
    assert(0 <= yy_psr_bktrk_stack_ix && 
	   yy_psr_bktrk_stack_ix < yy_psr_bktrk_stack_max); 
    
    return(yy_psr_bktrk_stack_ix); 

}   // yy_psr_bktrk_stack_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_grow()
//			
//  yy_psr_bktrk_stack_check_grow makes the parser backtrack stack larger.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_grow(
    size_t			yy_new_psr_bktrk_stack_top)
{
    yy_size_t_ptr		yy_psr_bktrk_stack_area_temp;
    size_t			yy_new_psr_bktrk_stack_max;
    size_t			yy_index;
    
//  pick a larger size for the array (double it)

    if (yy_psr_bktrk_stack_max < 1) {
	yy_new_psr_bktrk_stack_max = 1;
	}
    else {
	yy_new_psr_bktrk_stack_max = yy_psr_bktrk_stack_max;
	}
    
    while (yy_new_psr_bktrk_stack_max < yy_new_psr_bktrk_stack_top) {
	yy_new_psr_bktrk_stack_max = 
	    yy_new_psr_bktrk_stack_max + yy_new_psr_bktrk_stack_max;
	}

//  do some error checking

    assert(yy_psr_bktrk_stack_max < yy_new_psr_bktrk_stack_max);
    assert(yy_new_psr_bktrk_stack_max < (UINT_MAX / sizeof(size_t)));

//  if the array does not exist create a new array

    if (yy_psr_bktrk_stack_area == NULL) {

	// create the new array

	yy_psr_bktrk_stack_area = new size_t [yy_new_psr_bktrk_stack_max];
    
	//  check that space was actually created 

	if (yy_psr_bktrk_stack_area == NULL) {
	    yy_err_report(406);
	    yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	    return;
	    }

	// an array has been created save its size

	yy_psr_bktrk_stack_max = yy_new_psr_bktrk_stack_max;

	return;
	}

//  otherwise grow a larger array

    yy_psr_bktrk_stack_area_temp = new size_t [yy_new_psr_bktrk_stack_max];

//  check that space was actually created 

    if (yy_psr_bktrk_stack_area_temp == NULL) {
	yy_err_report(406);
	yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	return;
	}

//  copy the current contents into the new array

    for (yy_index = 0; yy_index < yy_psr_bktrk_stack_max; ++yy_index) {
	yy_psr_bktrk_stack_area_temp[yy_index] = 
	    yy_psr_bktrk_stack_area[yy_index];
	}

// delete the old area

    delete [] yy_psr_bktrk_stack_area;
    
// save the information in the actual object

    yy_psr_bktrk_stack_area = yy_psr_bktrk_stack_area_temp;
    yy_psr_bktrk_stack_max = yy_new_psr_bktrk_stack_max;
    
}   // yy_psr_bktrk_stack_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_pop(
//			yy_pop_count)
//
//  yy_psr_bktrk_stack_pop removes the desired number of entries desired
//  from the parser backtrack stack.
//
//  yy_pop_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_pop(
    size_t		yy_pop_count)
{
    assert(0 <= yy_psr_bktrk_stack_ix && 
	   yy_psr_bktrk_stack_ix < yy_psr_bktrk_stack_max); 

    // if the stack won't underflow, pop the entries

    if (yy_pop_count < yy_psr_bktrk_stack_ix) {
	yy_psr_bktrk_stack_ix -= yy_pop_count;
	}

    // otherwise, just empty the stack

    else {
	yy_psr_bktrk_stack_ix = 0;
        }

}   // yy_psr_bktrk_stack_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_push(
//				yy_new_psr_bktrk_start)
//			
//  yy_psr_bktrk_stack_push pushes a new reset position onto the parser
//  backtrack stack.
//
//  yy_new_psr_bktrk_start	the reset position to push onto the parser
//				backtrack stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_push(
    size_t		yy_new_psr_bktrk_start)
{
    assert(0 <= yy_psr_bktrk_stack_ix && yy_psr_bktrk_stack_ix < yy_psr_bktrk_stack_max); 

    // if new entry overflows the current stack, grow a larger one

    yy_psr_bktrk_stack_check_grow();
    
    // now that we have a new entry, copy the info into it

    yy_psr_bktrk_stack_area[yy_psr_bktrk_stack_ix] = yy_new_psr_bktrk_start;
    
    // take a new entry

    ++yy_psr_bktrk_stack_ix;

}   // yy_psr_bktrk_stack_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_rewind()
//
//  yy_psr_bktrk_stack_rewind resets the parser backtrack stack to its
//  initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_rewind(void)
{
    yy_psr_bktrk_stack_ix = 0;

}   // yy_psr_bktrk_stack_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_bktrk_stack_obj::yy_psr_bktrk_start(void)
//
//  yy_psr_bktrk_start returns the current (top) reset position on the
//  parser backtrack stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_bktrk_stack_obj::yy_psr_bktrk_start(void) const
{
    assert(0 <= yy_psr_bktrk_stack_ix && 
	   yy_psr_bktrk_stack_ix < yy_psr_bktrk_stack_max); 

    return(yy_psr_bktrk_stack_area[yy_psr_bktrk_stack_ix - 1]); 

}   // yy_psr_bktrk_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_bktrk_stack_obj::yy_psr_bktrk_start(yy_ix)
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

inline size_t &yy_psr_bktrk_stack_obj::yy_psr_bktrk_start(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_psr_bktrk_stack_ix && 
	   yy_psr_bktrk_stack_ix < yy_psr_bktrk_stack_max); 
    assert(0 <= yy_ix && yy_ix < yy_psr_bktrk_stack_max); 
    assert(yy_ix <= yy_psr_bktrk_stack_ix);

    return(yy_psr_bktrk_stack_area[yy_ix]);

}   // yy_psr_bktrk_start


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr)
//
//  yy_restore_data copies a parser backtrack stack object from the space
//  reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_psr_bktrk_stack_obj::yy_restore_data(
    const char		*yy_data_ptr)
{
    size_t		yy_new_psr_bktrk_stack_max;

    yy_memmove(&yy_psr_bktrk_stack_ix, yy_data_ptr, 
	       sizeof(yy_psr_bktrk_stack_ix));
    
    yy_data_ptr += sizeof(yy_psr_bktrk_stack_ix);
    
    yy_memmove(&yy_new_psr_bktrk_stack_max, yy_data_ptr, 
	       sizeof(yy_new_psr_bktrk_stack_max));
    
    yy_data_ptr += sizeof(yy_new_psr_bktrk_stack_max);
    
    yy_psr_bktrk_stack_check_grow(yy_new_psr_bktrk_stack_max);

    if (0 < yy_psr_bktrk_stack_ix) {
	yy_memmove(yy_psr_bktrk_stack_area, yy_data_ptr,
		   yy_psr_bktrk_stack_ix * sizeof(size_t));

	yy_data_ptr += yy_psr_bktrk_stack_ix * sizeof(size_t);
	}
    
    return(yy_data_ptr);
    
}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr)
//			
//  yy_save_data copies a parser backtrack stack object to the space
//  reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

inline char *yy_psr_bktrk_stack_obj::yy_save_data(
    char		*yy_data_ptr) const
{

    yy_memmove(yy_data_ptr, &yy_psr_bktrk_stack_ix, 
	       sizeof(yy_psr_bktrk_stack_ix));
    
    yy_data_ptr += sizeof(yy_psr_bktrk_stack_ix);
    
    yy_memmove(yy_data_ptr, &yy_psr_bktrk_stack_max, 
	       sizeof(yy_psr_bktrk_stack_max));
    
    yy_data_ptr += sizeof(yy_psr_bktrk_stack_max);
    
    if (0 < yy_psr_bktrk_stack_ix) {
	yy_memmove(yy_data_ptr, yy_psr_bktrk_stack_area,
		   yy_psr_bktrk_stack_ix * sizeof(size_t));
    
	yy_data_ptr += yy_psr_bktrk_stack_ix * sizeof(size_t);
	}
    
    return(yy_data_ptr);
    
}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
// 
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold a parser backtrack stack object.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_bktrk_stack_obj::yy_sizeof_data(void) const
{
    return(sizeof(yy_psr_bktrk_stack_ix) + sizeof(yy_psr_bktrk_stack_max) +
	yy_psr_bktrk_stack_ix * sizeof(size_t));

}  // yy_sizeof_data


#endif /* yy_bktrk_h_ */
