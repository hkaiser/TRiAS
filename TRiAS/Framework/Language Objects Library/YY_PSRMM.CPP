
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1998-99, Compiler Resources, Inc.
//
//  FILENAME:              yy_psrmm
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

#ifndef yy_psrmm_c_
#define yy_psrmm_c_ 1
#endif /* yy_psrmm_c_ */

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_trace.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_psr.h"
#include "yy_psrmm.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_memento_obj::yy_psr_memento_obj()
//
//  This is the constructor for the yy_psr_memento_obj which initializes the 
//  parser memento object.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_memento_obj::yy_psr_memento_obj()
    : yy_memento_obj()
{
}   // constructor for yy_psr_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_memento_obj::yy_psr_memento_obj()
//
//  This is the copy constructor for the yy_psr_memento_obj.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_memento_obj::yy_psr_memento_obj(
    const yy_psr_memento_obj	&yy_old_psr_memento_obj)
    : yy_memento_obj(yy_old_psr_memento_obj)
{
}   // constructor for yy_psr_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_memento_obj::yy_psr_memento_obj()
//
//  This is the constructor for the yy_psr_memento_obj given a parser object.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_memento_obj::yy_psr_memento_obj(
    const yy_psr_obj	&yy_old_psr_obj)
    : yy_memento_obj()
{

//  determine how much data the memento needs to store
    
    yy_sizeof_data() = yy_old_psr_obj.yy_sizeof_data();

//  allow the parser to save the data in the memento

    yy_old_psr_obj.yy_save_data(yy_data_ptr());
    
}   // constructor for yy_psr_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_psr_memento_obj::operator=()
//
//  This is the assignment operator for the yy_psr_memento_obj.
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_memento_obj &yy_psr_memento_obj::operator=(
    const yy_psr_memento_obj	&yy_old_psr_memento_obj)
{

    yy_memento_obj::operator=(yy_old_psr_memento_obj);

    return (*this);
    
}   // constructor for yy_psr_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_psr_memento_obj::~yy_psr_memento_obj()
//
//  This is the destructor for the parser memento object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_psr_memento_obj::~yy_psr_memento_obj()
{
}   // destructor for yy_psr_memento_obj
