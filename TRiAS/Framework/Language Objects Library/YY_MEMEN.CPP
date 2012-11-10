
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1998-99, Compiler Resources, Inc.
//
//  FILENAME:              yy_memen
//
//  FILE DESCRIPTION:      parser memento object for Yacc++ parsing support
//
//  MODIFICATION HISTORY:
//
//  01/04/99	bz/cc	Removed yy_no_myref_inlines_ as it didn't work with
//			several compilers.
//  06/03/98	bz/cc	coding and review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_memen_c_
#define yy_memen_c_ 1
#endif /* yy_memen_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_memen.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_memento_obj::yy_memento_obj()
//
//  This is the constructor for the yy_memento_obj which initializes the 
//  memento object.
//
//////////////////////////////////////////////////////////////////////////////

yy_memento_obj::yy_memento_obj()
    : yy_memento_sizeof_data(0),
      yy_memento_sizeof_data_max(0),
      yy_memento_data_ptr(0)
{
}   // constructor for yy_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_memento_obj::yy_memento_obj()
//
//  This is the copy constructor for the yy_memento_obj.
//
//////////////////////////////////////////////////////////////////////////////

yy_memento_obj::yy_memento_obj(
    const yy_memento_obj	&yy_old_memento)
{

    // copy the new desired size

    yy_memento_sizeof_data = yy_old_memento.yy_memento_sizeof_data;

    // only copy the old data area if it is valid

    if ((yy_old_memento.yy_memento_data_ptr != NULL) &&
	(yy_old_memento.yy_memento_sizeof_data <= 
	 yy_old_memento.yy_memento_sizeof_data_max)) {

	// assure that sufficient space is allocated

	if (yy_memento_sizeof_data_max < yy_memento_sizeof_data) {

	    // delete any old space

	    if (yy_memento_data_ptr != NULL) {
		delete [] yy_memento_data_ptr;
		}

	    // allocate new space

	    yy_memento_data_ptr = new char[yy_memento_sizeof_data];

	    if (yy_memento_data_ptr == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		return;
		}

	    yy_memento_sizeof_data_max = yy_memento_sizeof_data;
	    }

	// there is now sufficient space so that the move will succeed

	yy_memmove(yy_memento_data_ptr,
		   yy_old_memento.yy_memento_data_ptr,
		   yy_memento_sizeof_data);
	}

}   // constructor for yy_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_memento_obj::operator=()
//
//  This is the assignment operator for the yy_memento_obj.
//
//////////////////////////////////////////////////////////////////////////////

yy_memento_obj &yy_memento_obj::operator=(
    const yy_memento_obj	&yy_old_memento)
{

    if (this != &yy_old_memento) {

	// copy the new desired size

	yy_memento_sizeof_data = yy_old_memento.yy_memento_sizeof_data;
	
	// only copy the old data area if it is valid

	if ((yy_old_memento.yy_memento_data_ptr != NULL) &&
	    (yy_old_memento.yy_memento_sizeof_data <= 
	     yy_old_memento.yy_memento_sizeof_data_max)) {

	    // assure that sufficient space is allocated

	    if (yy_memento_sizeof_data_max < yy_memento_sizeof_data) {

		// delete any old space

		if (yy_memento_data_ptr != NULL) {
		    delete [] yy_memento_data_ptr;
		    }
		
		// allocate new space

		yy_memento_data_ptr = new char[yy_memento_sizeof_data];

		if (yy_memento_data_ptr == NULL) {
		    yy_err_report(406);
		    yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		    return(*this);
		    }

		yy_memento_sizeof_data_max = yy_memento_sizeof_data;
		}

	    // there is now sufficient space so that the move will succeed

	    yy_memmove(yy_memento_data_ptr,
		       yy_old_memento.yy_memento_data_ptr,
		       yy_memento_sizeof_data);
	    }
	
	}

    return (*this);
    
}   // constructor for yy_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_memento_obj::~yy_memento_obj()
//
//  This is the destructor for the parser memento object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_memento_obj::~yy_memento_obj()
{

    if (yy_memento_data_ptr != NULL) {
	delete [] yy_memento_data_ptr;
	yy_memento_data_ptr = NULL;
	}

}   // destructor for yy_memento_obj
