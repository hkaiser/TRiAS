
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:              yy_psrsk
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

#ifndef yy_psrsk_c_
#define yy_psrsk_c_ 1
#endif /* yy_psrsk_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_ref.h"
#include "yy_psrsk.h"
#include "yy_err.h"

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_stack_obj::yy_psr_stack_obj(yy_new_ref_factory,
//				yy_psr_left_max)
//
//  This is the constructor for the yy_psr_stack_obj which initializes 
//  the parser left side reference stack object.
//
//  yy_new_ref_factory		is the reference factory object which creates
//				the array of reference objects
//
//  yy_psr_left_max		is the maximum value for the depth of 
//				production nesting allowed in the reference 
//				stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_stack_obj::yy_psr_stack_obj(
    const yy_ref_factory_obj	&yy_new_ref_factory,
    size_t			yy_new_psr_left_max
    )
    : yy_ref_stack_obj(yy_new_ref_factory, yy_new_psr_left_max),
      yy_this_psr_stack_layout(yy_psr_stack_left_and_rt_empty_),
      yy_psr_stack_rt_ix(0)
{
}   // constructor for yy_psr_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_stack_obj::~yy_psr_stack_obj()
//
//  This is the destructor for the parser left side object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_stack_obj::~yy_psr_stack_obj() 
{
}   // destructor for yy_psr_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_stack_obj::yy_ref_stack_check_grow()
//			
//  yy_ref_stack_check_grow makes the stack larger when needed.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_stack_obj::yy_ref_stack_check_grow(void)
{

//  the layout of the stack determines when the stack can be full

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    

        case(yy_psr_stack_left_and_rt_empty_):

	    // if both sides of the stack are empty, it can't be full

	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    return;


        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);

	    // if the right side is empty, the stack is full if the left
	    // side is full

	    yy_ref_stack_obj::yy_ref_stack_check_grow(yy_ref_stack_ix + 1);

	    return;

        case(yy_psr_stack_left_and_rt_joined_):

	    // the stack is full if the left and right sides are full

	    yy_ref_stack_obj::yy_ref_stack_check_grow(
		yy_ref_stack_ix + yy_psr_stack_rt_ix + 1);

	    return;

        case(yy_psr_stack_left_and_rt_split_):

	    // the stack is full if the left and right sides are full

	    yy_ref_stack_obj::yy_ref_stack_check_grow(
		yy_ref_stack_ix + yy_psr_stack_rt_ix + 1);

	    return;
        }
    
}   // yy_ref_stack_check_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_stack_obj::yy_ref_stack_grow()
//			
//  yy_ref_stack_grow makes the stack larger.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_stack_obj::yy_ref_stack_grow(
    size_t			yy_new_ref_stack_top)
{
    yy_ref_ptr			yy_ref_stack_area_temp;
    size_t			yy_new_ref_stack_max;

//  the layout of the stack determines how the items are copied

    switch (yy_this_psr_stack_layout) {
        default:
	    assert(yy_false);
	    

        case(yy_psr_stack_left_and_rt_empty_):

	    // if both sides of the stack are empty, it can't be full

	    assert(yy_ref_stack_ix == 0);
	    assert(yy_psr_stack_rt_ix == 0);
	    return;


        case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);

	    //  pick a larger size for the array (double it)

	    if (yy_ref_stack_max < 1) {
		yy_new_ref_stack_max = 1;
		}
	    else {
		yy_new_ref_stack_max = yy_ref_stack_max;
		}

	    while (yy_new_ref_stack_max < yy_new_ref_stack_top) {
		yy_new_ref_stack_max = yy_new_ref_stack_max + 
		    yy_new_ref_stack_max;
		}

	    //  if the array does not exist create a new array

	    if (yy_ref_stack_area == NULL) {

		// create the new array

		yy_ref_stack_area = 
		    yy_ref_factory.yy_ref_factory_new_array(
			yy_new_ref_stack_max);

		//  check that space was actually created 

		if (yy_ref_stack_area == NULL) {
		    yy_err_report(406);
		    yy_assert_fail("space unavailable from new", 
				   __FILE__, __LINE__);
		    return;
		    }

		//  put a reference object which looks like a syntax error
		//  on the stack, so that if that stack is referenced when
		//  empty, the syntax error reference object will be
		//  retrieved and the parser will think there was a syntax
		//  error

		yy_ref_ptr yy_ref_temp_ptr = yy_ref_factory.yy_ref_factory_new_obj(yy_error_);

		yy_ref_factory.yy_ref_factory_array_assign(
		    yy_ref_stack_area, 0, 
		   *yy_ref_temp_ptr);

                // note: we do a reference factory delete here rather than an explicit
                // delete yy_ref_temp_ptr; because it would require an abstract class 
                // for the yy_ref_obj (UNION) for the destructor.  Thus virtual table 
                // pointers -- too much of a space penalty per parser stack entry.

		yy_ref_factory.yy_ref_factory_delete(yy_ref_temp_ptr);

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
		    yy_psr_stack_rt_ix);

	    //  check that space was actually created 

	    if (yy_ref_stack_area_temp == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", 
			       __FILE__, __LINE__);
		return;
		}

	    // delete the old array

	    yy_ref_factory.yy_ref_factory_delete_array(yy_ref_stack_area);

	    // save the information in the actual object

	    yy_ref_stack_area = yy_ref_stack_area_temp;
	    yy_ref_stack_max = yy_new_ref_stack_max;

	    return;

        case(yy_psr_stack_left_and_rt_joined_):

	    yy_this_psr_stack_layout = yy_psr_stack_left_and_rt_split_;
	    
	    //  pick a larger size for the array (double it)

	    if (yy_ref_stack_max < 1) {
		yy_new_ref_stack_max = 1;
		}
	    else {
		yy_new_ref_stack_max = yy_ref_stack_max;
		}

	    while (yy_new_ref_stack_max < yy_new_ref_stack_top) {
		yy_new_ref_stack_max = yy_new_ref_stack_max + 
		    yy_new_ref_stack_max;
		}

	    //  if the array does not exist create a new array

	    if (yy_ref_stack_area == NULL) {

		// create the new array

		yy_ref_stack_area = 
		    yy_ref_factory.yy_ref_factory_new_array(
			yy_new_ref_stack_max);

		//  check that space was actually created 

		if (yy_ref_stack_area == NULL) {
		    yy_err_report(406);
		    yy_assert_fail("space unavailable from new", 
				   __FILE__, __LINE__);
		    return;
		    }

		//  put a reference object which looks like a syntax error
		//  on the stack, so that if that stack is referenced when
		//  empty, the syntax error reference object will be
		//  retrieved and the parser will think there was a syntax
		//  error

		yy_ref_ptr yy_ref_temp_ptr = yy_ref_factory.yy_ref_factory_new_obj(yy_error_);

		yy_ref_factory.yy_ref_factory_array_assign(
		    yy_ref_stack_area, 0, 
		   *yy_ref_temp_ptr);

                // note: we do a reference factory delete here rather than an explicit
                // delete yy_ref_temp_ptr; because it would require an abstract class 
                // for the yy_ref_obj (UNION) for the destructor.  Thus virtual table 
                // pointers -- too much of a space penalty per parser stack entry.

		yy_ref_factory.yy_ref_factory_delete(yy_ref_temp_ptr);

		// an array has been created save its size

		yy_ref_stack_max = yy_new_ref_stack_max;

		return;
		}

	    //  otherwise grow a larger array
	    //  note that in the joined case, one element on the right
	    //  is actually tacked onto the left

	    yy_ref_stack_area_temp = 
		yy_ref_factory.yy_ref_factory_grow_array(
		    yy_new_ref_stack_max,
		    yy_ref_stack_area,
		    yy_ref_stack_max,
		    yy_ref_stack_ix + 1,
		    yy_psr_stack_rt_ix - 1);

	    //  check that space was actually created 

	    if (yy_ref_stack_area_temp == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", 
			       __FILE__, __LINE__);
		return;
		}

	    // delete the old array

	    yy_ref_factory.yy_ref_factory_delete_array(yy_ref_stack_area);

	    // save the information in the actual object

	    yy_ref_stack_area = yy_ref_stack_area_temp;
	    yy_ref_stack_max = yy_new_ref_stack_max;

	    return;

        case(yy_psr_stack_left_and_rt_split_):

	    //  pick a larger size for the array (double it)

	    if (yy_ref_stack_max < 1) {
		yy_new_ref_stack_max = 1;
		}
	    else {
		yy_new_ref_stack_max = yy_ref_stack_max;
		}

	    while (yy_new_ref_stack_max < yy_new_ref_stack_top) {
		yy_new_ref_stack_max = yy_new_ref_stack_max + 
		    yy_new_ref_stack_max;
		}

	    //  if the array does not exist create a new array

	    if (yy_ref_stack_area == NULL) {

		// create the new array

		yy_ref_stack_area = 
		    yy_ref_factory.yy_ref_factory_new_array(yy_new_ref_stack_max);

		//  check that space was actually created 

		if (yy_ref_stack_area == NULL) {
		    yy_err_report(406);
		    yy_assert_fail("space unavailable from new", 
				   __FILE__, __LINE__);
		    return;
		    }

		//  put a reference object which looks like a syntax error
		//  on the stack, so that if that stack is referenced when
		//  empty, the syntax error reference object will be
		//  retrieved and the parser will think there was a syntax
		//  error

		yy_ref_ptr yy_ref_temp_ptr = yy_ref_factory.yy_ref_factory_new_obj(yy_error_);

		yy_ref_factory.yy_ref_factory_array_assign(
		    yy_ref_stack_area, 0, 
		   *yy_ref_temp_ptr);

                // note: we do a reference factory delete here rather than an explicit
                // delete yy_ref_temp_ptr; because it would require an abstract class 
                // for the yy_ref_obj (UNION) for the destructor.  Thus virtual table 
                // pointers -- too much of a space penalty per parser stack entry.

		yy_ref_factory.yy_ref_factory_delete(yy_ref_temp_ptr);

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
		    yy_psr_stack_rt_ix);

	    //  check that space was actually created 

	    if (yy_ref_stack_area_temp == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", 
			       __FILE__, __LINE__);
		return;
		}

	    // delete the old array

	    yy_ref_factory.yy_ref_factory_delete_array(yy_ref_stack_area);

	    // save the information in the actual object

	    yy_ref_stack_area = yy_ref_stack_area_temp;
	    yy_ref_stack_max = yy_new_ref_stack_max;

	    return;
        }
    
    
}   // yy_ref_stack_grow


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr)
//
//  yy_restore_data copies a parser input stack object from the space
//  reserved for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

const char *yy_psr_stack_obj::yy_restore_data(
    const char		*yy_data_ptr)
{
    size_t		yy_index;
    
    yy_memmove(&yy_psr_stack_rt_ix, yy_data_ptr, 
	       sizeof(yy_psr_stack_rt_ix));
    
    yy_data_ptr += sizeof(yy_psr_stack_rt_ix);
    
    yy_memmove(&yy_this_psr_stack_layout, yy_data_ptr, 
	       sizeof(yy_this_psr_stack_layout));
    
    yy_data_ptr += sizeof(yy_this_psr_stack_layout);
    
    yy_data_ptr = yy_ref_stack_obj::yy_restore_data(yy_data_ptr);
    
    if (yy_psr_stack_rt_ix == 0) return(yy_data_ptr);

    switch (yy_this_psr_stack_layout) {
	default:
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_joined_):
	    yy_data_ptr = yy_ref_factory.yy_restore_data(yy_data_ptr,
			    yy_ref_stack_area,
			    yy_ref_stack_ix);
	    break;
	    
	case(yy_psr_stack_left_and_rt_split_):
	    yy_data_ptr = yy_ref_factory.yy_restore_data(yy_data_ptr,
			    yy_ref_stack_area, 
			    yy_ref_stack_max - yy_psr_stack_rt_ix);
	    break;
    }
    
    for (yy_index = 1; yy_index < yy_psr_stack_rt_ix; ++yy_index) {
	yy_data_ptr = yy_ref_factory.yy_restore_data(yy_data_ptr,
			yy_ref_stack_area,
			yy_ref_stack_max - yy_psr_stack_rt_ix + yy_index);
	}
    
    return(yy_data_ptr);
    
}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr)
//			
//  yy_save_data copies a parser input stack object to the space reserved
//  for it in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

char *yy_psr_stack_obj::yy_save_data(
    char		*yy_data_ptr) const
{
    size_t		yy_index;
    
    yy_memmove(yy_data_ptr, &yy_psr_stack_rt_ix, 
	       sizeof(yy_psr_stack_rt_ix));
    
    yy_data_ptr += sizeof(yy_psr_stack_rt_ix);
    
    yy_memmove(yy_data_ptr, &yy_this_psr_stack_layout, 
	       sizeof(yy_this_psr_stack_layout));
    
    yy_data_ptr += sizeof(yy_this_psr_stack_layout);
    
    yy_data_ptr = yy_ref_stack_obj::yy_save_data(yy_data_ptr);
    
    if (yy_psr_stack_rt_ix == 0) return(yy_data_ptr);

    switch (yy_this_psr_stack_layout) {
	default:
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_empty_):
	    assert(yy_ref_stack_ix == 0);
	case(yy_psr_stack_rt_empty_):
	    assert(yy_psr_stack_rt_ix == 0);
	    assert(yy_false);

	case(yy_psr_stack_left_and_rt_joined_):
	    yy_data_ptr = yy_ref_factory.yy_save_data(yy_data_ptr,
			    yy_ref_stack_area,
			    yy_ref_stack_ix);
	    break;
	    
	case(yy_psr_stack_left_and_rt_split_):
	    yy_data_ptr = yy_ref_factory.yy_save_data(yy_data_ptr,
			    yy_ref_stack_area, 
			    yy_ref_stack_max - yy_psr_stack_rt_ix);
	    break;
    }
    
    for (yy_index = 1; yy_index < yy_psr_stack_rt_ix; ++yy_index) {
	yy_data_ptr = yy_ref_factory.yy_save_data(yy_data_ptr,
			yy_ref_stack_area,
			yy_ref_stack_max - yy_psr_stack_rt_ix + yy_index);
	}
    
    return(yy_data_ptr);
    
}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
// 
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold a parser input stack object.
//
//////////////////////////////////////////////////////////////////////////////

size_t yy_psr_stack_obj::yy_sizeof_data(void) const
{

    return(yy_ref_stack_obj::yy_sizeof_data() +
	   sizeof(yy_psr_stack_rt_ix) + sizeof(yy_this_psr_stack_layout) +
	   yy_psr_stack_rt_ix * yy_ref_factory.yy_sizeof_data());

}  // yy_sizeof_data


