
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_psrsk.h
//  
//  FILE DESCRIPTION:     header file with parser input stack object 
//			  declarations
//                        
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
//  12/22/98    bz      Make sure inline definitions match declarations.
//                      (Borland C++ caught ones missing inline on the 
//                      definition).
//  05/18/98    bz      return a reference to yy_psr_left_entries so it can
//                      be changed from within the grammar (as was true of
//                      yy_psr_left at previous revs).
//  04/03/98	cc	extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_psrsk_h_
#define yy_psrsk_h_


//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_ref.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_ref_factory_ptr 	is a typedef which defines a pointer to a reference
//                      factory object.
//
//  yy_ref_ptr          is a typedef which defines a pointer to a reference
//                      object.
//
//  yy_ref_stack_ptr 	is a typedef which defines a pointer to a reference
//                      stack object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_ref_factory_obj	*yy_ref_factory_ptr;

typedef class yy_export yy_ref_obj        	*yy_ref_ptr;

typedef class yy_export yy_ref_stack_obj	*yy_ref_stack_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_stack_obj
//
//  The yy_psr_stack_obj holds the tokens and non-terminals which the parser
//  is working on.  This is the parser input stack class.  It is divided
//  into two parts.  The left and right sides.
//
//  The left side holds portion of the parser rule which is to the left of
//  the dot.  That is the tokens and non-terminals that have already been
//  shifted.  The left side is contained in the normal part of the stack as
//  implemented by the underlying yy_ref_stack_obj.  The left side of the
//  parser input stack corresponds to what is normally considered the parser
//  stack (as in yacc).
//
//  The right side holds portion of the parser rule which is to the right of
//  the dot.  That is the tokens and non-terminals which are still part of
//  the look-ahead.  The right side is implemented by an auxiliary stack
//  kept in the upper half of the stack area.  However, the top element of
//  the right stack is usually kept at the location one past the left stack
//  (the layout determines where the the top of the right side is kept).
//
//
//  PUBLIC FUNCTIONS:
//
//  yy_psr_stack_obj(yy_new_ref_factory, yy_new_psr_left_max)
//			constructor for a parser input stack object.
//
//  ~yy_psr_stack_obj()	destructor for a parser input stack object.
//
//  yy_ref_stack_check_grow()
//			checks that both sides of the parser input stack fit
//			in the current area.  This function overrides the
//			version in the yy_ref_stack_obj, because there are
//			two sides to check when attempting to determine if
//			the parser input stack has out-grown the current
//			allocation.
//
//  yy_ref_stack_grow(yy_new_ref_stack_top)	
//			makes the parser input stack larger.  This function
//			overrides the version in the yy_ref_stack_obj,
//			because the two sides are copied to the ends of the
//			new array leaving the gap in the middle.
//
//  yy_psr_ign()        implements a ignore action for the parser.  An
//  			ignore action removes the top entry on the
//  			right side, but does not add it to the left
//  			side.
//
//  yy_psr_shf()	implements a shift action for the parser.  A shift
//			action moves the top entry on the right side of the
//			parser input stack to the left side.
//
//  yy_psr_stack_rewind()
//			resets both the left and right sides of the parser
//			input stack to their initial states.
//
//  yy_psr_left_entries()
//			returns the number of entries in the left side of
//			the parser input stack.
//
//  yy_psr_left_entry(yy_ix)
//			returns the desired entry in the left side of the
//			parser input stack.
//
//  yy_psr_left_int(yy_ix)
//			returns the semantic value (as an int) for the
//			desired entry in the left side of the parser input
//			stack.
//
//  yy_psr_left_pop(yy_pop_count)
//			removes the desired number of entries from the left
//			side of the parser input stack.
//
//  yy_psr_left_pop_to(yy_new_ref_top)
//                      removes the top (last) entries from the left side of
//                      the parser input stack so that the desired entry is
//                      top (last).
//
//  yy_psr_left_type(yy_ix)
//			returns the type for the desired entry in the
//			left side of the parser input stack.
//
//  yy_psr_rt_create()  creates a slot for a new entry on the right side of
//			the parser input stack.
//		
//  yy_psr_rt_create_if_empty()  
//			creates a slot for a new entry on the right side of
//			the parser input stack, but only if the right side
//			is empty.
//		
//  yy_psr_rt_empty()	returns true if the right side of the parser input
//			stack is empty.
//		
//  yy_psr_rt_entries()	returns the number of entries in the right side of
//			the parser input stack.
//		
//  yy_psr_rt_int()	returns the semantic value (as an int) for the top
//			(newest) entry in the right side of the parser input
//			stack.
//		
//  yy_psr_rt_int(yy_ix)
//			returns the semantic value (as an int) for the
//			desired entry in the right side of the parser input
//			stack.
//
//  yy_psr_rt_pop(yy_pop_count)
//			removes the desired number of entries from the
//			right side of the parser input stack.
//
//  yy_psr_rt_rewind()	resets the right side of the parser input stack to
//			its initial state.
//			
//  yy_psr_rt_top()	returns the top (newest) value in the right side of 
//			the parser input stack.
//
//  yy_psr_rt_type()	returns the type of the top (newest) value in the 
//			right side of the parser input stack.
//
//  yy_psr_rt_type(yy_ix)
//			returns the type for the desired entry in the
//			right side of the parser input stack.
//
//  yy_restore_data(yy_data_ptr)
//			copies a parser input stack object from the space
//			reserved for it in a memento object.  This function
//			overrides the version in the yy_ref_stack_obj.
//
//  yy_save_data(yy_data_ptr)
//			copies a parser input stack object to the space
//			reserved for it in a memento object.  This function
//			overrides the version in the yy_ref_stack_obj.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold a parser input stack object.  This
//			function overrides the version in the
//			yy_ref_stack_obj.
//
//
//  INTERNAL STATE:
//
//  yy_psr_stack_layout how the left and right sides are arranged in the
//			array.
//
//  yy_psr_stack_rt_ix  the number of elements in the right side of the
//			parser input stack.
//
//  yy_ref_stack_ix 	the number of elements in the left side of the
//			parser input stack.
//
//  Additional internal state is derived from the yy_ref_stack_obj.  See it
//  for further documentation.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_stack_obj : public yy_ref_stack_obj {

  public:

    yy_psr_stack_obj(
        const yy_ref_factory_obj
				&yy_new_ref_factory,
        size_t 			yy_new_psr_left_max = yy_psr_left_max_);

    virtual ~yy_psr_stack_obj();

    virtual void yy_ref_stack_check_grow(void);

    virtual void yy_ref_stack_grow(
	size_t			yy_new_ref_stack_top);

    inline void yy_psr_ign(void);
    
    inline void yy_psr_shf(void);
    
    inline void yy_psr_stack_rewind(void);
    
    // functions which manipulate the left side

    inline size_t &yy_psr_left_entries(void);

    inline yy_ref_obj &yy_psr_left_entry(
	size_t			yy_ix) const;

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

    // functions which manipulate the right side

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

    inline enum yy_psr_stack_layout_enum yy_psr_stack_layout(void) const;

    inline enum yy_psr_stack_layout_enum &yy_psr_stack_layout(void);

    virtual const char *yy_restore_data(
	const char		*yy_data_ptr);

    virtual char *yy_save_data(
	char			*yy_data_ptr) const;

    virtual size_t yy_sizeof_data(void) const;

  protected:

    enum yy_psr_stack_layout_enum	yy_this_psr_stack_layout;
    size_t				yy_psr_stack_rt_ix;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the parser input stack
//  objects declared above.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_ign()
//
//  yy_psr_ign implements a ignore action for the parser.  An ignore
//  action removes the top entry on the right side, but does not add
//  it to the left side.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_ign(void)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 < yy_psr_stack_rt_ix && yy_psr_stack_rt_ix < yy_ref_stack_max); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

        case(yy_psr_stack_left_and_rt_joined_):
	    --yy_psr_stack_rt_ix;
	    if (yy_psr_stack_rt_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
	        }
	    else if (yy_ref_stack_ix + yy_psr_stack_rt_ix < 
		     yy_ref_stack_max) {
		yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
	        }
	    return;
	    
        case(yy_psr_stack_left_and_rt_split_):
	    --yy_psr_stack_rt_ix;
	    if (yy_psr_stack_rt_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
	        }
	    return;
    }

}   // yy_psr_ign


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_shf()
//
//  yy_psr_shf implements a shift action for the parser.  A shift action
//  moves the top entry (i.e. a token or non-terminal) from the right
//  (look-ahead) side to the left (within the current non-terminal) side of
//  the parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_shf(void)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 < yy_psr_stack_rt_ix && yy_psr_stack_rt_ix < yy_ref_stack_max); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

        case(yy_psr_stack_left_and_rt_joined_):
	    ++yy_ref_stack_ix;
	    --yy_psr_stack_rt_ix;
	    if (yy_psr_stack_rt_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
	        }
	    else if (yy_ref_stack_ix + yy_psr_stack_rt_ix < 
		     yy_ref_stack_max) {
		yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
	        }
	    return;
	    
        case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
	    yy_ref_stack_area[yy_ref_stack_ix] =
		yy_ref_stack_area[yy_ref_stack_max - yy_psr_stack_rt_ix];
#else
	    yy_ref_factory.yy_ref_factory_array_assign(
		yy_ref_stack_area, yy_ref_stack_ix, 
		yy_ref_stack_max - yy_psr_stack_rt_ix);
#endif /* yy_decl_union */		
	    ++yy_ref_stack_ix;
	    --yy_psr_stack_rt_ix;
	    if (yy_psr_stack_rt_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
	        }
	    return;
    }

}   // yy_psr_shf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_stack_rewind()
//
//  yy_psr_stack_rewind resets both the left and right sides of the parser
//  input stack to their initial states.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_stack_rewind(void)
{

    yy_ref_stack_ix = 0;
    yy_psr_stack_rt_ix = 0;
    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_empty_;

}   // yy_psr_stack_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_psr_left_entries()
//
//  yy_psr_left_entries returns the number of entries in the left side of
//  the parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_psr_stack_obj::yy_psr_left_entries(void)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix <= yy_ref_stack_max); 

    return(yy_ref_stack_entries());

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
//  These indexes include all entries on the left hand side and not just the
//  ones in the current rule.  The function yy_psr_ref(yy_ix) references
//  just the entries in the current rule.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_psr_stack_obj::yy_psr_left_entry(
    size_t		yy_ix) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert((0 <= yy_ix && yy_ix < yy_ref_stack_ix) ||
	   (yy_ix == 0 && yy_ref_stack_ix == 0)); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix]); 
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_ix)); 
#endif /* yy_decl_union */

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

inline int yy_psr_stack_obj::yy_psr_left_int(
    size_t		yy_ix) const
{ 
    return(yy_ref_stack_int(yy_ix));

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

inline int &yy_psr_stack_obj::yy_psr_left_int(
    size_t		yy_ix)
{ 
    return(yy_ref_stack_int(yy_ix));

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

inline void yy_psr_stack_obj::yy_psr_left_pop(
    size_t		yy_pop_count)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix <= yy_ref_stack_max); 
    assert(0 <= yy_pop_count && yy_pop_count <= yy_ref_stack_ix); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    return;
	    
        case(yy_psr_stack_left_and_rt_joined_):
	    if (yy_ref_stack_ix + yy_psr_stack_rt_ix < 
		yy_ref_stack_max) {
#ifdef yy_decl_union
		yy_ref_stack_area[yy_ref_stack_max - yy_psr_stack_rt_ix] =
		    yy_ref_stack_area[yy_ref_stack_ix];
#else
		yy_ref_factory.yy_ref_factory_array_assign(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix,
		    yy_ref_stack_ix);
#endif /* yy_decl_union */		
	        }
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
	    /* fall-through */

        case(yy_psr_stack_left_and_rt_split_):
	    if (yy_pop_count < yy_ref_stack_ix) {
		yy_ref_stack_ix -= yy_pop_count;
		return;
		}
	    yy_ref_stack_ix = 0;
	    return;
	    
        case(yy_psr_stack_rt_empty_):
	    if (yy_pop_count < yy_ref_stack_ix) {
		yy_ref_stack_ix -= yy_pop_count;
		return;
		}
	    yy_ref_stack_ix = 0;
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_empty_;
	    return;
    }
    
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

inline void yy_psr_stack_obj::yy_psr_left_pop_to(
    size_t		yy_new_psr_left_top)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix <= yy_ref_stack_max); 
    assert(0 <= yy_new_psr_left_top && 
	   yy_new_psr_left_top <= yy_ref_stack_ix); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    return;
	    
        case(yy_psr_stack_left_and_rt_joined_):
	    if (yy_ref_stack_ix == yy_new_psr_left_top) {
		return;
	        }
	    
	    if (yy_ref_stack_ix + yy_psr_stack_rt_ix < 
		yy_ref_stack_max) {
#ifdef yy_decl_union
		yy_ref_stack_area[yy_ref_stack_max - yy_psr_stack_rt_ix] =
		    yy_ref_stack_area[yy_ref_stack_ix];
#else
		yy_ref_factory.yy_ref_factory_array_assign(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix,
		    yy_ref_stack_ix);
#endif /* yy_decl_union */		
	        }
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
	    /* fall-through */

        case(yy_psr_stack_rt_empty_):
        case(yy_psr_stack_left_and_rt_split_):
	    assert(yy_new_psr_left_top <= yy_ref_stack_ix); 
	    yy_ref_stack_ix = yy_new_psr_left_top;
	    return;

    }
    
}   // yy_psr_left_pop_to


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_left_remove(yy_ix, yy_remove_count)
//
//  yy_psr_left_remove removes the desired number of entries from the left
//  side of the parser input stack.
//
//  yy_ix 		index of the first entry to remove from the left
//  			side of the parser input stack.  The index of 0
//  			represents the oldest entry in the left side with
//  			more recently added entries having higher indexes.
//
//  yy_remove_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_left_remove(
    size_t		yy_ix,
    size_t		yy_remove_count)
{
    size_t		yy_loop_ix;
    
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix <= yy_ref_stack_max); 
    assert(0 <= yy_remove_count && yy_remove_count <= yy_ref_stack_ix); 
    assert(0 <= yy_ix && yy_ix <= yy_ref_stack_ix - yy_remove_count); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    return;
	    
        case(yy_psr_stack_left_and_rt_joined_):
	    if (yy_ref_stack_ix + yy_psr_stack_rt_ix < 
		yy_ref_stack_max) {
#ifdef yy_decl_union
		yy_ref_stack_area[yy_ref_stack_max - yy_psr_stack_rt_ix] =
		    yy_ref_stack_area[yy_ref_stack_ix];
#else
		yy_ref_factory.yy_ref_factory_array_assign(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix,
		    yy_ref_stack_ix);
#endif /* yy_decl_union */		
	        }
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
	    /* fall-through */

        case(yy_psr_stack_left_and_rt_split_):
	    if (yy_remove_count < yy_ref_stack_ix) {
		yy_ref_stack_ix -= yy_remove_count;
		for (yy_loop_ix = yy_ix; yy_loop_ix < yy_ref_stack_ix; 
		     ++yy_loop_ix) {
#ifdef yy_decl_union
		    yy_ref_stack_area[yy_loop_ix] =
			yy_ref_stack_area[yy_loop_ix + yy_remove_count];
#else
		    yy_ref_factory.yy_ref_factory_array_assign(
			yy_ref_stack_area, yy_loop_ix, 
			yy_loop_ix + yy_remove_count);
#endif /* yy_decl_union */		
		    }
		return;
		}
	    yy_ref_stack_ix = 0;
	    return;
	    
        case(yy_psr_stack_rt_empty_):
	    if (yy_remove_count < yy_ref_stack_ix) {
		yy_ref_stack_ix -= yy_remove_count;
		for (yy_loop_ix = yy_ix; yy_loop_ix < yy_ref_stack_ix; 
		     ++yy_loop_ix) {
#ifdef yy_decl_union
		    yy_ref_stack_area[yy_loop_ix] =
			yy_ref_stack_area[yy_loop_ix + yy_remove_count];
#else
		    yy_ref_factory.yy_ref_factory_array_assign(
			yy_ref_stack_area, yy_loop_ix, 
			yy_loop_ix + yy_remove_count);
#endif /* yy_decl_union */		
		    }
		return;
		}
	    yy_ref_stack_ix = 0;
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_empty_;
	    return;
    }
    
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

inline int yy_psr_stack_obj::yy_psr_left_type(
    size_t		yy_ix) const
{ 
    return(yy_ref_stack_type(yy_ix));

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

inline int &yy_psr_stack_obj::yy_psr_left_type(
    size_t		yy_ix)
{ 
    return(yy_ref_stack_type(yy_ix));

}   // yy_psr_left_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_create(void)
//
//  yy_psr_rt_create creates a slot for a new entry on the right
//  (look-ahead) side of the parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_rt_create(void)
{
    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_joined_;
	    yy_psr_stack_rt_ix = 1;
	    return;

        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    yy_ref_stack_check_grow();
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_joined_;
	    yy_psr_stack_rt_ix = 1;
	    return;

        case(yy_psr_stack_left_and_rt_joined_):
	    yy_ref_stack_check_grow();
	    assert(yy_ref_stack_ix + yy_psr_stack_rt_ix < yy_ref_stack_max);
#ifdef yy_decl_union
	    yy_ref_stack_area[yy_ref_stack_max - yy_psr_stack_rt_ix] =
		yy_ref_stack_area[yy_ref_stack_ix];
#else
	    yy_ref_factory.yy_ref_factory_array_assign(
		yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix,
		yy_ref_stack_ix);
#endif /* yy_decl_union */		
	    ++yy_psr_stack_rt_ix;
	    return;

        case(yy_psr_stack_left_and_rt_split_):
	    yy_ref_stack_check_grow();
	    ++yy_psr_stack_rt_ix;
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_joined_;
	    return;
    }

}   // yy_psr_rt_create


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_create_if_empty(void)
//
//  yy_psr_rt_create creates a slot for a new entry on the right
//  (look-ahead) side of the parser input stack, but only if the right side
//  is empty.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_rt_create_if_empty(void)
{
    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_joined_;
	    yy_psr_stack_rt_ix = 1;
	    return;

        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    yy_ref_stack_check_grow();
	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_joined_;
	    yy_psr_stack_rt_ix = 1;
	    return;

        case(yy_psr_stack_left_and_rt_joined_):
        case(yy_psr_stack_left_and_rt_split_):
	    assert(0 < yy_psr_stack_rt_ix &&
		   yy_psr_stack_rt_ix <= yy_ref_stack_max); 
	    return;
    }

}   // yy_psr_rt_create_if_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_psr_rt_empty()
//
//  yy_psr_rt_empty returns true if the right side of the parser input stack
//  is empty.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_psr_stack_obj::yy_psr_rt_empty(void) const
{
    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    return(yy_true);

        case(yy_psr_stack_left_and_rt_joined_):
        case(yy_psr_stack_left_and_rt_split_):
	    assert(0 < yy_psr_stack_rt_ix &&
		   yy_psr_stack_rt_ix <= yy_ref_stack_max); 
	    return(yy_false);
    }

}   // yy_psr_rt_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_psr_rt_entries()
//
//  yy_psr_rt_entries returns the number of entries in the right side of the
//  parser input stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_psr_stack_obj::yy_psr_rt_entries(void) const
{
    assert(0 <= yy_psr_stack_rt_ix && yy_psr_stack_rt_ix <= yy_ref_stack_max); 

    return(yy_psr_stack_rt_ix);

}   // yy_psr_rt_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_psr_rt_int(void) const
//
//  yy_psr_rt_int returns the semantic value (as an int) for the top (newest)
//  entry in the right side of the parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_stack_obj::yy_psr_rt_int(void) const
{ 
    switch (yy_this_psr_stack_layout) {
	default:
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix].yy_int);
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_int(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

	case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[
		yy_ref_stack_max - yy_psr_stack_rt_ix].yy_int);
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_int(
		yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
    }

}   // yy_psr_rt_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_psr_rt_int(void)
//
//  yy_psr_rt_int returns the semantic value (as an int) for the top (newest)
//  entry in the right side of the parser input stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_stack_obj::yy_psr_rt_int(void)
{ 
    switch (yy_this_psr_stack_layout) {
	default:
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix].yy_int);
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_int(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

	case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[
		yy_ref_stack_max - yy_psr_stack_rt_ix].yy_int);
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_int(
		yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
    }

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
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_psr_stack_obj::yy_psr_rt_int(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_psr_stack_rt_ix && 
	   yy_psr_stack_rt_ix <= yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_psr_stack_rt_ix);

    if (yy_ix == 0) {
	switch (yy_this_psr_stack_layout) {
	    default:
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_empty_):
		assert(yy_ref_stack_ix == 0);
	    case(yy_psr_stack_rt_empty_):
		assert(yy_psr_stack_rt_ix == 0);
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[yy_ref_stack_ix].yy_int);
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_int(
		    yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

	    case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[
		    yy_ref_stack_max - yy_psr_stack_rt_ix].yy_int);
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_int(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
	}
    }
    
#ifdef yy_decl_union
    return(yy_ref_stack_area[
	yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix].yy_int);
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_int(
	yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix));
#endif /* yy_decl_union */		

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
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_psr_stack_obj::yy_psr_rt_int(
    size_t		yy_ix)
{ 
    assert(0 <= yy_psr_stack_rt_ix && 
	   yy_psr_stack_rt_ix <= yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_psr_stack_rt_ix);

    if (yy_ix == 0) {
	switch (yy_this_psr_stack_layout) {
	    default:
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_empty_):
		assert(yy_ref_stack_ix == 0);
	    case(yy_psr_stack_rt_empty_):
		assert(yy_psr_stack_rt_ix == 0);
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[yy_ref_stack_ix].yy_int);
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_int(
		    yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

	    case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[
		    yy_ref_stack_max - yy_psr_stack_rt_ix].yy_int);
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_int(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
	}
    }
    
#ifdef yy_decl_union
    return(yy_ref_stack_area[
	yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix].yy_int);
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_int(
	yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix));
#endif /* yy_decl_union */		

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

inline void yy_psr_stack_obj::yy_psr_rt_pop(
    size_t		yy_pop_count)
{
    assert(0 <= yy_psr_stack_rt_ix && yy_psr_stack_rt_ix <= yy_ref_stack_max); 
    assert(0 <= yy_pop_count && yy_pop_count <= yy_psr_stack_rt_ix); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	    /* fall-through */

        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    return;

        case(yy_psr_stack_left_and_rt_joined_):

	    // if the stack won't underflow, pop the items

	    if (yy_pop_count < yy_psr_stack_rt_ix) {
		yy_psr_stack_rt_ix -= yy_pop_count;
		yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
		}

	    // otherwise, just empty the stack

	    else if (yy_ref_stack_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_empty_;
		yy_psr_stack_rt_ix = 0;
		}
	    else {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
		yy_psr_stack_rt_ix = 0;
		}
	    return;

        case(yy_psr_stack_left_and_rt_split_):

	    // if the stack won't underflow, pop the items

	    if (yy_pop_count < yy_psr_stack_rt_ix) {
		yy_psr_stack_rt_ix -= yy_pop_count;
		}

	    // otherwise, just empty the stack

	    else if (yy_ref_stack_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_empty_;
		yy_psr_stack_rt_ix = 0;
		}
	    else {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
		yy_psr_stack_rt_ix = 0;
		}
	    return;
    }

}   // yy_psr_rt_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rt_rewind()
//
//  yy_psr_rt_rewind resets the right side of the parser input stack to its
//  initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_psr_stack_obj::yy_psr_rt_rewind(void)
{

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
        case(yy_psr_stack_rt_empty_):
	    return;

        case(yy_psr_stack_left_and_rt_joined_):
        case(yy_psr_stack_left_and_rt_split_):
	    if (yy_ref_stack_ix == 0) {
		yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_empty_;
		yy_psr_stack_rt_ix = 0;
		}
	    else {
		yy_this_psr_stack_layout = yy_psr_stack_rt_empty_;
		yy_psr_stack_rt_ix = 0;
		}
	    return;
    }

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

inline yy_ref_obj &yy_psr_stack_obj::yy_psr_rt_top(void) const
{
    assert(0 <= yy_ref_stack_ix && 
	   yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_psr_stack_rt_ix && yy_psr_stack_rt_ix < yy_ref_stack_max); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

        case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix]);
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

        case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_max - yy_psr_stack_rt_ix]);
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref(
		yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
    }

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

inline int yy_psr_stack_obj::yy_psr_rt_type(void) const
{
    assert(0 <= yy_ref_stack_ix && 
	   yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_psr_stack_rt_ix && yy_psr_stack_rt_ix < yy_ref_stack_max); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_type(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

        case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_type(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

        case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[
		yy_ref_stack_max - yy_psr_stack_rt_ix].yy_type());
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_type(
		yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		

    }

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

inline int &yy_psr_stack_obj::yy_psr_rt_type(void)
{
    assert(0 <= yy_ref_stack_ix && 
	   yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_psr_stack_rt_ix && yy_psr_stack_rt_ix < yy_ref_stack_max); 

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    
        case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_type(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

        case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_type(
		yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

        case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
	    return(yy_ref_stack_area[
		yy_ref_stack_max - yy_psr_stack_rt_ix].yy_type());
#else
	    return(yy_ref_factory.yy_ref_factory_array_deref_type(
		yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		

    }

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

inline int yy_psr_stack_obj::yy_psr_rt_type(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_psr_stack_rt_ix && 
	   yy_psr_stack_rt_ix <= yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_psr_stack_rt_ix);

    if (yy_ix == 0) {
	switch (yy_this_psr_stack_layout) {
	    default:
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_empty_):
		assert(yy_ref_stack_ix == 0);
	    case(yy_psr_stack_rt_empty_):
		assert(yy_psr_stack_rt_ix == 0);
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_type(
		    yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

	    case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[
		    yy_ref_stack_max - yy_psr_stack_rt_ix].yy_type());
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_type(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
	}
    }
    
#ifdef yy_decl_union
    return(yy_ref_stack_area[
	yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix].yy_type());
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix));
#endif /* yy_decl_union */		

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

inline int &yy_psr_stack_obj::yy_psr_rt_type(
    size_t		yy_ix)
{ 
    assert(0 <= yy_psr_stack_rt_ix && 
	   yy_psr_stack_rt_ix <= yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_psr_stack_rt_ix);

    if (yy_ix == 0) {
	switch (yy_this_psr_stack_layout) {
	    default:
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_empty_):
		assert(yy_ref_stack_ix == 0);
	    case(yy_psr_stack_rt_empty_):
		assert(yy_psr_stack_rt_ix == 0);
		assert(yy_false);

	    case(yy_psr_stack_left_and_rt_joined_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[yy_ref_stack_ix].yy_type());
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_type(
		    yy_ref_stack_area, yy_ref_stack_ix));
#endif /* yy_decl_union */		

	    case(yy_psr_stack_left_and_rt_split_):
#ifdef yy_decl_union
		return(yy_ref_stack_area[
		    yy_ref_stack_max - yy_psr_stack_rt_ix].yy_type());
#else
		return(yy_ref_factory.yy_ref_factory_array_deref_type(
		    yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix));
#endif /* yy_decl_union */		
	}
    }
    
#ifdef yy_decl_union
    return(yy_ref_stack_area[
	yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix].yy_type());
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ref_stack_max - yy_psr_stack_rt_ix + yy_ix));
#endif /* yy_decl_union */		

}   // yy_psr_rt_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:    yy_psr_stack_layout_enum &yy_psr_stack_layout()
//
//  yy_psr_stack_layout returns the layout of the parser input stack. 
//
//////////////////////////////////////////////////////////////////////////////

inline enum yy_psr_stack_obj::yy_psr_stack_layout_enum &yy_psr_stack_obj::yy_psr_stack_layout(void)
{

    return(yy_this_psr_stack_layout);

}    // yy_psr_stack_layout


#endif /* yy_psrsk_h_ */
