
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:              yy_rdcsk
//
//  FILE DESCRIPTION:      parser reduce stack object
//
//  MODIFICATION HISTORY:
//
//  12/21/98    bz      changed variable index to yy_index to avoid any
//                      potential conflict with index string function.
//  04/03/98	bz/cc	extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_rdcsk_c_
#define yy_rdcsk_c_ 1
#endif /* yy_rdcsk_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_rdcsk.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_rdc_stack_obj::yy_psr_rdc_stack_obj(yy_new_psr_rdc_max)
//
//  This is the constructor for the yy_psr_rdc_stack_obj which initializes 
//  the parser reduce stack object.
//
//  yy_new_psr_rdc_max     is the maximum value for the depth of production
//			   nesting allowed in the parser stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_rdc_stack_obj::yy_psr_rdc_stack_obj(
    const yy_ref_factory_obj	&yy_new_ref_factory,
    size_t 			yy_new_psr_rdc_max
    )
    : yy_ref_stack_obj(yy_new_ref_factory, yy_new_psr_rdc_max),
      yy_psr_rdc_area(0)
{

//  create the reduce area of the parser stack (for non-terminals in 
//  process)

    assert(yy_ref_stack_max < (UINT_MAX / sizeof(yy_psr_rdc_entry_obj)));
    yy_psr_rdc_area = new yy_psr_rdc_entry_obj [yy_ref_stack_max];

    if (yy_psr_rdc_area == NULL) {
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	return;
        }

//  initialize the 1st entry to protective values

    yy_psr_rdc_area[0].yy_psr_rdc_state = 0;
    yy_psr_rdc_area[0].yy_psr_rdc_start = 0;
    
}   // constructor for yy_psr_rdc_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_rdc_stack_obj::~yy_psr_rdc_stack_obj()
//
//  This is the destructor for the parser stack object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_rdc_stack_obj::~yy_psr_rdc_stack_obj() 
{

    //  delete the parser reduce stack area

    if (yy_psr_rdc_area != NULL) {
        delete [] yy_psr_rdc_area;
        yy_psr_rdc_area = NULL;
        }
    
}   // destructor for yy_psr_rdc_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_psr_rdc_stack_obj::yy_ref_stack_grow(void)
//			
//  yy_ref_stack_grow makes the stack larger.
//
//////////////////////////////////////////////////////////////////////////////

void yy_psr_rdc_stack_obj::yy_ref_stack_grow(
    size_t			yy_new_ref_stack_top)
{
    yy_psr_rdc_entry_ptr	yy_psr_rdc_area_temp;
    size_t			yy_old_ref_stack_max;
    size_t			yy_index;

//  save the original array size

    yy_old_ref_stack_max = yy_ref_stack_max;

//  call the base objects growth function

    yy_ref_stack_obj::yy_ref_stack_grow(yy_new_ref_stack_top);
    
//  do some error checking

    assert(yy_old_ref_stack_max < yy_ref_stack_max);
    assert(yy_ref_stack_max < (UINT_MAX / sizeof(yy_psr_rdc_entry_obj)));

//  if the array does not exist create a new array

    if (yy_psr_rdc_area == NULL) {

	// create the new array

	yy_psr_rdc_area = new yy_psr_rdc_entry_obj [yy_ref_stack_max];
    
	//  check that space was actually created 

	if (yy_psr_rdc_area == NULL) {
	    yy_err_report(406);
	    yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	    return;
	    }

	//  initialize the 1st entry to protective values

	yy_psr_rdc_area[0].yy_psr_rdc_state = 0;
	yy_psr_rdc_area[0].yy_psr_rdc_start = 0;

	return;
	}

//  create a new array

    yy_psr_rdc_area_temp = new yy_psr_rdc_entry_obj [yy_ref_stack_max];

//  check that space was actually created 

    if (yy_psr_rdc_area_temp == NULL) {
	yy_err_report(406);
	yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	return;
	}

//  copy the current contents into the new array

    for (yy_index = 0; yy_index < yy_ref_stack_ix; ++yy_index) {
	yy_psr_rdc_area_temp[yy_index] = yy_psr_rdc_area[yy_index];
	}

//  delete the old area

    delete [] yy_psr_rdc_area;

//  save the information in the actual object

    yy_psr_rdc_area = yy_psr_rdc_area_temp;
    
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

const char *yy_psr_rdc_stack_obj::yy_restore_data(
    const char		*yy_data_ptr)
{

    yy_data_ptr = yy_ref_stack_obj::yy_restore_data(yy_data_ptr);
    
    if (0 < yy_ref_stack_ix) {
	yy_memmove(yy_psr_rdc_area, yy_data_ptr, 
		   (yy_ref_stack_ix + 1) * sizeof(yy_psr_rdc_entry_obj));
    
	yy_data_ptr += (yy_ref_stack_ix + 1) * sizeof(yy_psr_rdc_entry_obj);
    
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

char *yy_psr_rdc_stack_obj::yy_save_data(
    char		*yy_data_ptr) const
{
    
    yy_data_ptr = yy_ref_stack_obj::yy_save_data(yy_data_ptr);
    
    if (0 < yy_ref_stack_ix) {
	yy_memmove(yy_data_ptr, yy_psr_rdc_area, 
		   (yy_ref_stack_ix + 1) * sizeof(yy_psr_rdc_entry_obj));
    
	yy_data_ptr += (yy_ref_stack_ix + 1) * sizeof(yy_psr_rdc_entry_obj);
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

size_t yy_psr_rdc_stack_obj::yy_sizeof_data(void) const
{

    return(yy_ref_stack_obj::yy_sizeof_data() +
	   (yy_ref_stack_ix + 1) * sizeof(yy_psr_rdc_entry_obj));

}  // yy_sizeof_data


