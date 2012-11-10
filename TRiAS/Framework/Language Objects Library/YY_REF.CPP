
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:              yy_ref
//
//  FILE DESCRIPTION:      reference stack object
//
//  MODIFICATION HISTORY:
//
//  11/16/98    bz      fixed reference object memory leaks via reference
//                      factory delete interface.
//  04/03/98	bz/cc	extracted from yy_psr.
//  
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_ref_c_
#define yy_ref_c_ 1
#endif /* yy_ref_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_ref.h"
#include "yy_rdcsk.h"
#include "yy_bktrk.h"
#include "yy_err.h"

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_ref_stack_obj::yy_ref_stack_obj(yy_new_ref_factory,
//				yy_new_ref_stack_max)
//
//  This is the constructor for the yy_ref_stack_obj which initializes 
//  the reference stack object.
//
//  yy_new_ref_factory		is the reference factory object which creates
//				the array of reference objects
//
//  yy_new_ref_stack_max	is the maximum value for the depth of 
//				production nesting allowed in the reference 
//				stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_ref_stack_obj::yy_ref_stack_obj(
    const yy_ref_factory_obj	&yy_new_ref_factory,
    size_t			yy_new_ref_stack_max
    )
    : yy_ref_factory(yy_new_ref_factory),
      yy_ref_stack_area(0),
      yy_ref_stack_ix(0),
      yy_ref_stack_max(yy_new_ref_stack_max)
{

//  don't create an array if the size is 0

    if (yy_ref_stack_max == 0) return;
	
//  create the array which holds the stack entries

    yy_ref_stack_area = 
	yy_ref_factory.yy_ref_factory_new_array(yy_ref_stack_max);
    
//  check that space was actually created 

    if (yy_ref_stack_area == NULL) {
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	return;
        }

//  put a reference object which looks like a syntax error on the stack, 
//  so that if that stack is referenced when empty, the syntax error 
//  reference object will be retrieved and the parser will think there 
//  was a syntax error

    yy_ref_ptr yy_ref_temp_ptr = yy_ref_factory.yy_ref_factory_new_obj(yy_error_);

    yy_ref_factory.yy_ref_factory_array_assign(
	yy_ref_stack_area, 0, 
	*yy_ref_temp_ptr);

//  note: we do a reference factory delete here rather than an explicit
//  delete yy_ref_temp_ptr; because it would require an abstract class 
//  for the yy_ref_obj (UNION) for the destructor.  Thus virtual table 
//  pointers -- too much of a space penalty per parser stack entry.

    yy_ref_factory.yy_ref_factory_delete(yy_ref_temp_ptr);

}   // constructor for yy_ref_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_ref_stack_obj::~yy_ref_stack_obj()
//
//  This is the destructor for the reference stack object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_ref_stack_obj::~yy_ref_stack_obj() 
{

//  delete the reference stack area

    if (yy_ref_stack_area != NULL) {
	yy_ref_factory.yy_ref_factory_delete_array(yy_ref_stack_area);
        yy_ref_stack_area = NULL;
        }
    
}   // destructor for yy_ref_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_check_grow()
//			
//  yy_ref_stack_check_grow makes the stack larger when needed.
//
//////////////////////////////////////////////////////////////////////////////

void yy_ref_stack_obj::yy_ref_stack_check_grow(void)
{
    
    yy_ref_stack_check_grow(yy_ref_stack_ix + 1);
    
}   // yy_ref_stack_check_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_ref_stack_obj::yy_ref_stack_grow(
//			yy_new_ref_stack_top)
//			
//  yy_ref_stack_check_grow makes the stack larger.
//
//  yy_new_ref_stack_top	desired minimum size for the new array
//
//////////////////////////////////////////////////////////////////////////////

void yy_ref_stack_obj::yy_ref_stack_grow(
    size_t			yy_new_ref_stack_top)
{
    yy_ref_ptr			yy_ref_stack_area_temp;
    size_t			yy_new_ref_stack_max;
    
//  pick a larger size for the array (double it)

    if (yy_ref_stack_max < 1) {
	yy_new_ref_stack_max = 1;
	}
    else {
	yy_new_ref_stack_max = yy_ref_stack_max;
	}
    
    while (yy_new_ref_stack_max < yy_new_ref_stack_top) {
	yy_new_ref_stack_max = yy_new_ref_stack_max + yy_new_ref_stack_max;
	}

//  do some error checking

    assert(yy_ref_stack_max < yy_new_ref_stack_max);

//  if the array does not exist create a new array

    if (yy_ref_stack_area == NULL) {

	// create the new array

	yy_ref_stack_area = 
	    yy_ref_factory.yy_ref_factory_new_array(yy_new_ref_stack_max);
    
	//  check that space was actually created 

	if (yy_ref_stack_area == NULL) {
	    yy_err_report(406);
	    yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	    return;
	    }

	//  put a reference object which looks like a syntax error on the
	//  stack, so that if that stack is referenced when empty, the
	//  syntax error reference object will be retrieved and the parser
	//  will think there was a syntax error

	yy_ref_factory.yy_ref_factory_array_assign(
	    yy_ref_stack_area, 0, 
	    *yy_ref_factory.yy_ref_factory_new_obj(yy_error_));

	// an array has been created save its size

	yy_ref_stack_max = yy_new_ref_stack_max;

	return;
	}

//  otherwise grow a larger array

    yy_ref_stack_area_temp = 
	yy_ref_factory.yy_ref_factory_grow_array(
	    yy_new_ref_stack_max,
	    yy_ref_stack_area,
	    yy_ref_stack_max,
	    yy_ref_stack_ix,
	    0);
    
//  check that space was actually created 

    if (yy_ref_stack_area_temp == NULL) {
	yy_err_report(406);
	yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	return;
	}

//  delete the old array

    yy_ref_factory.yy_ref_factory_delete_array(yy_ref_stack_area);

//  save the information in the actual object

    yy_ref_stack_area = yy_ref_stack_area_temp;
    yy_ref_stack_max = yy_new_ref_stack_max;
    
}   // yy_ref_stack_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr)
//
//  yy_restore_data copies a reference stack object from the space reserved
//  for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

const char *yy_ref_stack_obj::yy_restore_data(
    const char		*yy_data_ptr)
{
    size_t		yy_index;
    size_t		yy_new_ref_stack_max;
    
    yy_memmove(&yy_ref_stack_ix, yy_data_ptr, 
	       sizeof(yy_ref_stack_ix));
    
    yy_data_ptr += sizeof(yy_ref_stack_ix);
    
    yy_memmove(&yy_new_ref_stack_max, yy_data_ptr, 
	       sizeof(yy_new_ref_stack_max));
    
    yy_data_ptr += sizeof(yy_ref_stack_max);
    
    yy_ref_stack_check_grow(yy_new_ref_stack_max);

    for (yy_index = 0; yy_index < yy_ref_stack_ix; ++yy_index) {
	yy_data_ptr = yy_ref_factory.yy_restore_data(yy_data_ptr,
						  yy_ref_stack_area,
						  yy_index);
	}
    
    return(yy_data_ptr);
    
}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr)
//			
//  yy_save_data copies a reference stack object to the space reserved for
//  it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

char *yy_ref_stack_obj::yy_save_data(
    char		*yy_data_ptr) const
{
    size_t		yy_index;
    
    yy_memmove(yy_data_ptr, &yy_ref_stack_ix, 
	       sizeof(yy_ref_stack_ix));
    
    yy_data_ptr += sizeof(yy_ref_stack_ix);
    
    yy_memmove(yy_data_ptr, &yy_ref_stack_max, 
	       sizeof(yy_ref_stack_max));
    
    yy_data_ptr += sizeof(yy_ref_stack_max);
    
    for (yy_index = 0; yy_index < yy_ref_stack_ix; ++yy_index) {
	yy_data_ptr = yy_ref_factory.yy_save_data(yy_data_ptr,
						  yy_ref_stack_area,
						  yy_index);
	}
    
    return(yy_data_ptr);
    
}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
// 
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold a reference stack object.
//
//////////////////////////////////////////////////////////////////////////////

size_t yy_ref_stack_obj::yy_sizeof_data(void) const
{
    return(sizeof(yy_ref_stack_ix) + sizeof(yy_ref_stack_max) +
	yy_ref_stack_ix * yy_ref_factory.yy_sizeof_data());

}  // yy_sizeof_data


