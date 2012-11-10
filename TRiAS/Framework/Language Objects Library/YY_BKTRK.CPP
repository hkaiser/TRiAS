
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:              yy_bktrk
//
//  FILE DESCRIPTION:      parser backtrack queue and stack objects
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	Removed yy_no_myref_inlines_ as it didn't work with
//			several compilers.
//    12/21/98   bz     Reordered constructor to match the sequence of protected
//                      data members in yy_psr_bktrk_obj class declaration.
//    04/03/98   bz/cc  extracted from yy_psr.h.
//  
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_bktrk_c_
#define yy_bktrk_c_ 1
#endif /* yy_bktrk_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_bktrk.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_obj(
//				yy_psr_bktrk_queue_max)
//
//  This is the constructor for the yy_psr_bktrk_queue_obj which initializes 
//  the parser backtracking queue object.
//
//  yy_psr_bktrk_queue_max	is the maximum value for the queue size.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_bktrk_queue_obj::yy_psr_bktrk_queue_obj(
    const yy_ref_factory_obj	&yy_new_ref_factory,
    size_t			yy_new_psr_bktrk_queue_max
    )
    : yy_ref_stack_obj(yy_new_ref_factory, yy_new_psr_bktrk_queue_max),
      yy_bktrk_read_ix(0)
{
}   // constructor for yy_psr_bktrk_queue_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_bktrk_queue_obj::~yy_psr_bktrk_queue_obj()
//
//  This is the destructor for the parser backtracking queue object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_bktrk_queue_obj::~yy_psr_bktrk_queue_obj() 
{
}   // destructor for yy_psr_bktrk_queue_obj


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

const char *yy_psr_bktrk_queue_obj::yy_restore_data(
    const char		*yy_data_ptr)
{
    
    yy_data_ptr = yy_ref_stack_obj::yy_restore_data(yy_data_ptr);
    
    yy_memmove(&yy_bktrk_read_ix, yy_data_ptr, 
	       sizeof(yy_bktrk_read_ix));
    
    yy_data_ptr += sizeof(yy_bktrk_read_ix);
    
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

char *yy_psr_bktrk_queue_obj::yy_save_data(
    char		*yy_data_ptr) const
{
    
    yy_data_ptr = yy_ref_stack_obj::yy_save_data(yy_data_ptr);
    
    yy_memmove(yy_data_ptr, &yy_bktrk_read_ix, 
	       sizeof(yy_bktrk_read_ix));
    
    yy_data_ptr += sizeof(yy_bktrk_read_ix);
    
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

size_t yy_psr_bktrk_queue_obj::yy_sizeof_data(void) const
{

    return(yy_ref_stack_obj::yy_sizeof_data() + sizeof(yy_bktrk_read_ix));

}  // yy_sizeof_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_obj(
//				yy_new_psr_bktrk_stack_max)
//
//  This is the constructor for the yy_psr_bktrk_stack_obj which initializes 
//  the parser backtracking stack object.
//
//  yy_new_psr_bktrk_stack_max  is the maximum value for the depth of
//			   	nesting allowed in the backtracking stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_bktrk_stack_obj::yy_psr_bktrk_stack_obj(
    size_t				yy_new_psr_bktrk_stack_max
    )
    : yy_psr_bktrk_stack_area(0),
      yy_psr_bktrk_stack_ix(0),
      yy_psr_bktrk_stack_max(yy_new_psr_bktrk_stack_max)
{

    //  create the backtracking stack

    assert(yy_psr_bktrk_stack_max < (UINT_MAX / sizeof(size_t)));
    yy_psr_bktrk_stack_area = new size_t [yy_psr_bktrk_stack_max];
    if (yy_psr_bktrk_stack_area == NULL) {
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	return;
        }

}   // constructor for yy_psr_bktrk_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_bktrk_stack_obj::~yy_psr_bktrk_stack_obj()
//
//  This is the destructor for the parser backtracking stack object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_bktrk_stack_obj::~yy_psr_bktrk_stack_obj() 
{

    //  delete parser stack work areas

    if (yy_psr_bktrk_stack_area != NULL) {
        delete [] yy_psr_bktrk_stack_area;
        yy_psr_bktrk_stack_area = NULL;
        }
    
}   // destructor for yy_psr_bktrk_stack_obj
