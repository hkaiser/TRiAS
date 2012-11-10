
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
//  04/03/98	bz/cc	extracted from yy_psr.
//  
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_reffc_c_
#define yy_reffc_c_ 1
#endif /* yy_reffc_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_reffc.h"
#include "yy_myref.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   const char *yy_restore_data(yy_data_ptr, yy_array, yy_target)
//
//  yy_restore_data copies a reference object from the space reserved for it
//  in a memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

const char *yy_ref_factory_obj::yy_restore_data(
    const char		*yy_data_ptr,
    yy_ref_ptr		yy_array,
    size_t		yy_target) const
{
    yy_memmove(yy_array + yy_target, yy_data_ptr, 
	       sizeof(yy_ref_obj));
    
    yy_data_ptr += sizeof(yy_ref_obj);
    
    return(yy_data_ptr);
    
}  // yy_restore_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_save_data(yy_data_ptr, yy_array, yy_source)
//			
//  yy_save_data copies a reference object to the space reserved for it in a
//  memento object.
//
//  yy_data_ptr		the space reserved in the memento object.
//
//////////////////////////////////////////////////////////////////////////////

char *yy_ref_factory_obj::yy_save_data(
    char		*yy_data_ptr,
    yy_ref_ptr		yy_array,
    size_t		yy_source) const
{
    yy_memmove(yy_data_ptr, yy_array + yy_source, 
	       sizeof(yy_ref_obj));
    
    yy_data_ptr += sizeof(yy_ref_obj);
    
    return(yy_data_ptr);
    
}  // yy_save_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t yy_sizeof_data()
// 
//  yy_sizeof_data returns the amount of space required in a memento object
//  to hold a reference object.
//
//////////////////////////////////////////////////////////////////////////////

size_t yy_ref_factory_obj::yy_sizeof_data(void) const
{
    return(sizeof(yy_ref_obj));

}  // yy_sizeof_data
