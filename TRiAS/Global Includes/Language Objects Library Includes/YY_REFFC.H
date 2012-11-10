
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_reffc.h
//  
//  FILE DESCRIPTION:     header file with reference factory object 
//                        declarations
//
//  CLASS HIERARCHY:
//
//                      +-------------------------+
//                      | reference factory class |
//                      |      (yy_reffc.h)       |
//                      +-------------------------+
//                                  | derives
//                                  |
//                      +-------------------------+
//                      |    generated parser     |
//                      | reference factory class |
//                      |      (yy_mypsr.h)       |
//                      +-------------------------+
//
//    
//  MODIFICATION HISTORY:
//  
//  11/17/98    bz      need a single ref delete interface to fix memory leaks.
//  04/21/98	cc	extracted from yy_ref.h.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_reffc_h_
#define yy_reffc_h_


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
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_ref_factory_obj	*yy_ref_factory_ptr;

typedef class yy_export yy_ref_obj        	*yy_ref_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_ref_factory_obj
//
//  A yy_ref_factory_obj creates and manipulates reference objects.  This is
//  the abstract base class which defines reference factory objects.  The
//  real reference factory object is defined in yy_mypsr.h and yy_mypsr.cxx
//  (or the file names specified in the OUTPUT PARSER HEADER and OUTPUT
//  PARSER SOURCE directives).
//
//  Using reference factory objects allows the code in the library to be
//  independent of the implementation of reference objects (or even their
//  declaration) without requiring the reference objects themselves to have
//  a virtual function table (since there will typically be numerous
//  reference objects and some compilers may put the virtual function table
//  with the objects resulting in an unacceptable space penalty).
//
//  It is worth noting that some inline functions (ones intended for use
//  only in user code) in each of the objects do not use the yy_ref_factory
//  interface and refer to the reference objects and their arrays directly.
//  In addition, when the inline functions that use the yy_ref_factory
//  objects are compiled in the presence of a UNION declaration, they also
//  refer to their arrays directly.  This minimizes overhead.
//
//
//  PUBLIC FUNCTIONS:
//
//  ~yy_ref_factory_obj() 
//			destructor for a reference factory object.
//
//  yy_ref_factory_new_obj(type, semantic_int)
//			creates a new reference object with the given integer
//			semantic value and type.
//
//  yy_ref_factory_new_array(size)
//			creates a new array of reference objects of the given
//                      size.
//
//  yy_ref_factory_delete( ... )
//			destroys a reference object.
//
//  yy_ref_factory_delete_array(array)
//			destroys an array of reference objects.
//
//  yy_ref_factory_grow_array(...)
//			creates a a new array array of reference objects 
//                      of the desired (larger) size to replace an existing
//			array of reference objects.
//
//  yy_ref_factory_assign(target_obj, source_obj)
//                      assigns two reference objects.
//
//  yy_ref_factory_array_assign(array, target_ix, source_ix)
//                      assigns two reference objects within an array given
//			their indexes.
//
//  yy_ref_factory_array_assign(array, target_ix, source_obj)
//                      assigns an reference object within an array given
//			its index and the source reference object.
//
//  yy_ref_factory_array_deref(array, source_ix)
//                      extracts the reference object at the given index in
//			the array.
//
//  yy_ref_factory_array_deref_int(array, source_ix)
//			extracts the semantic value (as an int) of the
//			reference object at the given index in the array.
//
//  yy_ref_factory_array_deref_type(array, source_ix)
//			extracts the type of the reference object at the 
//			given index in the array.
//
//  yy_ref_obj_size(size, __FILE__, __LINENO__)
//			tests and returns the size of the reference object
//
//  yy_restore_data(yy_data_ptr, array, target_ix)
//			copies a reference object from the space reserved
//			for it in a memento object.
//
//  yy_save_data(yy_data_ptr, array, source_ix)
//			copies a reference object to the space reserved for
//			it in a memento object.
//
//  yy_sizeof_data()    returns the amount of space required in a memento
//			object to hold a reference object.
//
//
//////////////////////////////////////////////////////////////////////////////

class yy_ref_factory_obj {

  public:

    virtual ~yy_ref_factory_obj() {}

    virtual yy_ref_ptr yy_ref_factory_new_obj(
        int			yy_int = 0,
	int			yy_type = 0) const = 0;

    virtual yy_ref_ptr yy_ref_factory_new_array(
	size_t			yy_size) const = 0;

    virtual void yy_ref_factory_delete(
	yy_ref_ptr		yy_ref) const = 0;

    virtual void yy_ref_factory_delete_array(
	yy_ref_ptr		yy_array) const = 0;

    virtual yy_ref_ptr yy_ref_factory_grow_array(
	size_t			yy_new_size,
	yy_ref_ptr		yy_old_array,
	size_t			yy_old_size,
	size_t			yy_copy_bottom = 0,
	size_t			yy_copy_top = 0) const = 0;

    virtual void yy_ref_factory_assign(
	yy_ref_obj		&yy_target,
	const yy_ref_obj	&yy_source) const = 0;

    virtual void yy_ref_factory_array_assign(
	yy_ref_ptr		yy_array,
	size_t			yy_target,
	size_t			yy_source) const = 0;

    virtual void yy_ref_factory_array_assign(
	yy_ref_ptr		yy_array,
	size_t			yy_target,
	const yy_ref_obj	&yy_source) const = 0;

    virtual yy_ref_obj &yy_ref_factory_array_deref(
	yy_ref_ptr		yy_array,
	size_t			yy_source) const = 0;

    virtual int &yy_ref_factory_array_deref_int(
	yy_ref_ptr		yy_array,
	size_t			yy_source) const = 0;

    virtual int &yy_ref_factory_array_deref_type(
	yy_ref_ptr		yy_array,
	size_t			yy_source) const = 0;

    virtual size_t yy_ref_obj_size(
	size_t			yy_ref_size,
        const char 		*file,
	int			lineno) const = 0;
    
    virtual const char *yy_restore_data(
	const char		*yy_data_ptr,
	yy_ref_ptr		yy_array,
	size_t			yy_target) const = 0;

    virtual char *yy_save_data(
	char			*yy_data_ptr,
	yy_ref_ptr		yy_array,
	size_t			yy_source) const = 0;

    virtual size_t yy_sizeof_data(void) const = 0;

    };


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_assert_sizeof_ref_obj_ok(yy_ref_factory_ptr, 
//			yy_ref_obj)
//
//  yy_assert_sizeof_ref_obj_ok asserts that the size of the reference object
//  in the current file matches the size of the reference object in the
//  factory, which may be separately compiled.
//
//  This "function" is implemented as a macro, so that we can use the 
//  preprocessor __FILE__ and __LINENO__ substitutions, since we wish to
//  pinpoint the two different files which are compiled incompatibly.
//
//////////////////////////////////////////////////////////////////////////////

#define yy_assert_sizeof_ref_obj_ok(yy_ref_factory_ptr, yy_ref_obj_type) \
    assert((yy_ref_factory_ptr)->yy_ref_obj_size(sizeof(yy_ref_obj_type), \
        __FILE__, __LINENO__);

#endif /* yy_reffc_h_ */
