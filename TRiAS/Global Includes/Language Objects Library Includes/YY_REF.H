
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_ref.h
//  
//  FILE DESCRIPTION:     header file with base parser reference object 
//                        declarations
//
//  CLASS HIERARCHY:
//
//               +-------------------------+
//               |     constants class     |
//               |       (yy_const.h)      |
//               +-------------------------+
//                           | derives
//                           |
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
//    12/22/98    bz      Make sure inline definitions match declarations.
//                        (Borland C++ caught ones missing inline on the 
//                        definition).
//    05/18/98    bz      Needs yy_asrt.h header.
//    04/03/98    cc	  extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_ref_h_
#define yy_ref_h_


//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_const.h"
#include "yy_reffc.h"


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
//  CLASS:  yy_ref_stack_obj
//
//  A yy_ref_stack_obj holds a stack of reference objects.  Reference
//  objects are defined by the UNION declaration in the users grammar, which
//  generates the class yy_ref_obj in yy_myref.h (or the file specified by
//  the OUTPUT UNION HEADER declaration).  
//
//  All storage of reference objects in the library is in reference
//  stacks.  In addition, all library code which manipulates reference
//  objects uses the reference stack's reference factory object
//  (yy_ref_factory_obj defined in yy_reffc.h) to do the actual data
//  movement when the code is not compiled with a UNION declaration
//  visible.  This minimizes the number of places in the library where
//  the size of a reference object needs to be known and protects the
//  library from changes to the user's union size.
//
//  There are three reference stacks in a parser object: the parser input
//  stack, the parser reduce stack, and the parser backtrack queue.
//
//  These stacks are all internal to the parser object.  Users are not
//  expected to manipulate them directly.  If you are tempted to manipulate
//  one of these objects in a way not described in an example provided in
//  the documentation, please contact technical support first.
//
//
//  PUBLIC FUNCTIONS:
//
//  yy_ref_stack_obj(yy_new_ref_factory, yy_new_ref_stack_max)
//			constructor for a reference stack object.
//
//  ~yy_ref_stack_obj() destructor for a reference stack object.
//
//  yy_ref_stack_check_grow([yy_new_ref_stack_top])
//			makes the reference stack larger when needed.  This
//			function is virtual as some of the stacks which
//			depend on this class as their base implementation
//			have a different interpretation of when the stack is
//			full.
//
//  yy_ref_stack_empty()
//			returns true if the reference stack is empty.
//
//  yy_ref_stack_entries()
//			returns the number of entries in the reference
//			stack.
//
//  yy_ref_stack_grow(yy_new_ref_stack_top)
//			makes the reference stack larger.  This function is
//			virtual as some of the stacks which depend on this
//			class as their base implementation have a different
//			interpretation of how the objects should be copied
//			to the new stack.
//
//  yy_ref_stack_int(yy_ix)
//			returns the semantic value (as an int) for the 
//			desired entry in the reference stack.
//
//  yy_ref_stack_pop(yy_pop_count)
//			removes the desired number of entries from the
//			reference stack.
//
//  yy_ref_stack_pop_to(yy_new_ref_top)
//                      removes the top entries from the reference stack so
//			that the desired entry is top.
//
//  yy_ref_stack_push(yy_new_value)
//			pushes a new object onto the reference stack.
//
//  yy_ref_stack_rewind()
//			resets the reference stack to its initial state.
//
//  yy_ref_stack_top()  returns the object on the top of the reference stack.
//
//  yy_ref_stack_type(yy_ix)
//			returns the type for the desired entry in the
//			reference stack.
//
//  yy_ref_obj_size(size, __FILE__, __LINENO__)
//			tests and returns the size of the reference object.
//			This is delegated to the reference factory object.
//
//  yy_restore_data(yy_data_ptr)
//			copies a reference stack object from the space
//			reserved for it in a memento object.
//
//  yy_save_data(yy_data_ptr)
//			copies a reference stack object to the space
//			reserved for it in a memento object.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold a reference stack object.
//
//
//  INTERNAL STATE:
//
//  yy_ref_factory	the reference factory to use to manipulate the array.
//
//  yy_ref_stack_area[] contains the objects on the stack.
//
//  yy_ref_stack_ix	indexes the top of the stack.
//
//  yy_ref_stack_max	maximum number of entries in the stack.
//
//////////////////////////////////////////////////////////////////////////////

class yy_ref_stack_obj : public yy_const {

  public:

    yy_ref_stack_obj(
        const yy_ref_factory_obj
				&yy_new_ref_factory,
        size_t 			yy_new_ref_stack_max = yy_ref_stack_max_);

    virtual ~yy_ref_stack_obj();

    virtual void yy_ref_stack_check_grow();

    inline void yy_ref_stack_check_grow(
        size_t			yy_new_ref_stack_top);

    inline yy_boolean yy_ref_stack_empty(void) const;
    
    inline size_t yy_ref_stack_entries(void) const;
    
    inline size_t &yy_ref_stack_entries(void);
    
    virtual void yy_ref_stack_grow(
        size_t			yy_new_ref_stack_top);

    inline int yy_ref_stack_int(
	size_t			yy_ix) const;

    inline int &yy_ref_stack_int(
	size_t			yy_ix);

    inline void yy_ref_stack_pop(
	size_t 			yy_pop_count = 1);

    inline void yy_ref_stack_pop_to(
	size_t 			yy_new_ref_stack_top);

    inline void yy_ref_stack_push(
	const yy_ref_obj	&yy_new_value);

    inline void yy_ref_stack_rewind(void);
    
    inline const yy_ref_obj &yy_ref_stack_top(void) const;

    inline yy_ref_obj &yy_ref_stack_top(void);

    inline int yy_ref_stack_type(
	size_t			yy_ix) const;

    inline int &yy_ref_stack_type(
	size_t			yy_ix);

    inline size_t yy_ref_obj_size(
	size_t			yy_ref_size,
        const char 		*file,
        int			lineno) const;
    
    virtual const char *yy_restore_data(
	const char		*yy_data_ptr);

    virtual char *yy_save_data(
	char			*yy_data_ptr) const;

    virtual size_t yy_sizeof_data(void) const;

  protected:

    const yy_ref_factory_obj	&yy_ref_factory;
    yy_ref_ptr			yy_ref_stack_area;
    size_t			yy_ref_stack_ix;
    size_t 			yy_ref_stack_max;
    };


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the reference stack
//  objects declared above.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_check_grow(
//			yy_new_ref_stack_top)
//			
//  yy_ref_stack_check_grow makes the stack larger when needed.
//
//  yy_new_ref_stack_top	desired minimum size for the new array
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_ref_stack_obj::yy_ref_stack_check_grow(
    size_t			yy_new_ref_stack_top)
{
    
//  do nothing, if the array still fits

    if (yy_new_ref_stack_top <= yy_ref_stack_max) return;
    
//  grow array 

    yy_ref_stack_grow(yy_new_ref_stack_top);
    
}   // yy_ref_stack_check_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_ref_stack_obj::yy_ref_stack_empty()
//
//  yy_ref_stack_empty returns true if the reference stack is empty.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_ref_stack_obj::yy_ref_stack_empty(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
   
    return(yy_ref_stack_ix == 0); 

}   // yy_ref_stack_empty


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_ref_stack_obj::yy_ref_stack_entries() const
//
//  yy_ref_stack_entries returns the number of entries in the reference
//  stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_ref_stack_obj::yy_ref_stack_entries(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
   
    return(yy_ref_stack_ix); 

}   // yy_ref_stack_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_ref_stack_obj::yy_ref_stack_entries()
//
//  yy_ref_stack_entries returns the number of entries in the reference
//  stack.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_ref_stack_obj::yy_ref_stack_entries(void)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
   
    return(yy_ref_stack_ix); 

}   // yy_ref_stack_entries


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_ref_stack_obj::yy_ref_stack_int(yy_ix) const
//
//  yy_ref_stack_int returns the semantic value (as an int) for the desired
//  entry in the reference stack.
//
//  yy_ix		is the index of the desired entry.  The index of 0
//  			represents the newset entry in the stack with less
//  			recently added entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_ref_stack_obj::yy_ref_stack_int(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix].yy_int);
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_int(
	yy_ref_stack_area, yy_ix));
#endif /* yy_decl_union */		

}   // yy_ref_stack_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_ref_stack_obj::yy_ref_stack_int(yy_ix)
//
//  yy_ref_stack_int returns the semantic value (as an int) for the desired
//  entry in the reference stack.
//
//  yy_ix		is the index of the desired entry.  The index of 0
//  			represents the newset entry in the stack with less
//  			recently added entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_ref_stack_obj::yy_ref_stack_int(
    size_t		yy_ix)
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix].yy_int);
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_int(
	yy_ref_stack_area, yy_ix));
#endif /* yy_decl_union */		

}   // yy_ref_stack_int


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_pop(
//			yy_pop_count)
//
//  yy_ref_stack_pop removes the desired number of entries from the
//  reference stack.
//
//  yy_pop_count	the number of entries to remove from the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_ref_stack_obj::yy_ref_stack_pop(
    size_t		yy_pop_count)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

    // if the stack won't underflow, pop the items

    if (yy_pop_count < yy_ref_stack_ix) {
	yy_ref_stack_ix -= yy_pop_count;
	}

    // otherwise, just empty the stack

    else {
	yy_ref_stack_ix = 0;
        }

}   // yy_ref_stack_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_pop_to(
//			yy_new_ref_stack_top)
//
//  yy_ref_stack_pop_to removes the top entries from the reference stack so
//  that the desired entry is top.
//
//  yy_new_ref_stack_top	the new top of the stack.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_ref_stack_obj::yy_ref_stack_pop_to(
    size_t		yy_new_ref_stack_top)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_new_ref_stack_top &&
	   yy_new_ref_stack_top < yy_ref_stack_ix); 

    yy_ref_stack_ix = yy_new_ref_stack_top;

}   // yy_ref_stack_pop_to


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_push(yy_new_value)
//			
//  yy_ref_stack_push pushes a new object onto the reference stack.
//
//  yy_new_value	the reference object to be pushed onto the
//			reference stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_ref_stack_obj::yy_ref_stack_push(
    const yy_ref_obj		&yy_new_value)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

    // take a new entry

    ++yy_ref_stack_ix;

    // if that overflows the current stack, grow a larger one

    yy_ref_stack_check_grow();
    
    // now that we have a new entry, copy the info into it

#ifdef yy_decl_union
    yy_ref_stack_area[yy_ref_stack_ix] = yy_new_value;
#else
    yy_ref_factory.yy_ref_factory_array_assign(
	yy_ref_stack_area, yy_ref_stack_ix, yy_new_value);
#endif /* yy_decl_union */		

}   // yy_ref_stack_push


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_rewind()
//
//  yy_ref_stack_rewind resets the reference stack to its initial state.
//
//////////////////////////////////////////////////////////////////////////////

inline void yy_ref_stack_obj::yy_ref_stack_rewind(void)
{

    yy_ref_stack_ix = 0; 

}   // yy_ref_stack_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const yy_ref_obj &yy_ref_stack_obj::yy_ref_stack_top(void) const
//
//  yy_ref_stack_top returns the object on top of the reference stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline const yy_ref_obj &yy_ref_stack_obj::yy_ref_stack_top(void) const
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ref_stack_ix]); 
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_ref_stack_ix)); 
#endif /* yy_decl_union */		

}   // yy_ref_stack_top


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_obj &yy_ref_stack_obj::yy_ref_stack_top(void)
//
//  yy_ref_stack_top returns the object on top of the reference stack.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_ref_obj &yy_ref_stack_obj::yy_ref_stack_top(void)
{
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ref_stack_ix]); 
#else
    return(yy_ref_factory.yy_ref_factory_array_deref(
	yy_ref_stack_area, yy_ref_stack_ix)); 
#endif /* yy_decl_union */		

}   // yy_ref_stack_top


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_ref_stack_obj::yy_ref_stack_type(yy_ix) const
//
//  yy_ref_stack_type returns the type for the desired entry in the
//  reference stack.
//
//  yy_ix		is the index of the desired entry.  The index of 0
//  			represents the newset entry in the stack with less
//  			recently added entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int yy_ref_stack_obj::yy_ref_stack_type(
    size_t		yy_ix) const
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix].yy_type());
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ix));
#endif /* yy_decl_union */

}   // yy_ref_stack_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int &yy_ref_stack_obj::yy_ref_stack_type(yy_ix)
//
//  yy_ref_stack_type returns the type for the desired entry in the
//  reference stack.
//
//  yy_ix		is the index of the desired entry.  The index of 0
//  			represents the newset entry in the stack with less
//  			recently added entries having higher indexes.
//
//  This function uses the yy_ref_factory to manipulate elements on the
//  stack when compiled without a UNION declaration visible (as in the
//  library builds), so that it can adjust to the users union without a
//  compilation dependency.  This function manipulates the reference objects
//  and arrays directly when compiled with a UNION declaration visible for
//  efficiency.
//
//////////////////////////////////////////////////////////////////////////////

inline int &yy_ref_stack_obj::yy_ref_stack_type(
    size_t		yy_ix)
{ 
    assert(0 <= yy_ref_stack_ix && yy_ref_stack_ix < yy_ref_stack_max); 
    assert(0 <= yy_ix && yy_ix <= yy_ref_stack_ix); 

#ifdef yy_decl_union
    return(yy_ref_stack_area[yy_ix].yy_type());
#else
    return(yy_ref_factory.yy_ref_factory_array_deref_type(
	yy_ref_stack_area, yy_ix));
#endif /* yy_decl_union */

}   // yy_ref_stack_type


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_ref_stack_obj::yy_ref_obj_size(yy_ref_size, 
//			__FILE__, __LINENO__)
//			
//  yy_ref_obj_size tests and returns the size of the reference object.
//  This function allows the code to assert that the reference stack object
//  has the same size of yy_ref_obj as the user code, and detect size
//  clashes which would occur if this object has not been recompiled to
//  reference the correct sized yy_ref_obj if the user declares a larger one
//  than the default.
//
//  This function is delegated to the reference factory object.  Normally,
//  this means that the size of the reference object will match the size of
//  the reference object compiled into yy_mypsr.cxx (or the file name
//  specified in the OUTPUT PARSER SOURCE directive).  However, this
//  function also checks the size of the yy_ref_obj where it is compiled
//  when it is compiled in with a UNION declaration visible.
//
//  Note, this function is only designed to be used in the macro
//  yy_assert_sizeof_ref_obj_ok (in yy_reffc.h).
//
//  yy_ref_size		the size of the object where this is called.
//
//  __FILE__		the filename where this function was invoked.
//
//  __LINENO__		the line number where the function was invoked.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t yy_ref_stack_obj::yy_ref_obj_size(
    size_t		yy_ref_size,
    const char 		*file,
    int			lineno) const
{
#ifdef yy_decl_union
    assert(yy_ref_size == sizeof(yy_ref_obj));
    return(yy_ref_factory.yy_ref_obj_size(yy_ref_size, file, lineno));
#else
    return(yy_ref_factory.yy_ref_obj_size(yy_ref_size, file, lineno));
#endif /* yy_decl_union */

}   // yy_ref_obj_size


#endif /* yy_ref_h_ */
