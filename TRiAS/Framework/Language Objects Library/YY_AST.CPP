
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_ast
//
//  FILE DESCRIPTION:     header file with the abstract syntax tree 
//                        (AST) object class declarations
//  
//  MODIFICATION HISTORY:
//  
//    06/14/96   bz       yy_valid_obj() now part of yy_ast_dump_obj.
//    08/31/93   bz/cc    recoded to be only an abstract base class.
//    10/30/92   bz       C7 -- removed setjmp header
//    08/07/92   bz       no longer uses alloc macros for object creation.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_ast_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_ast.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_valid_obj()
//
//  yy_valid_obj() returns true for any abstract syntax tree (AST) object.  
//  A derived object may override this function and provide more meaningful 
//  checking on the validity of an abstract syntax tree object.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_ast_dump_obj::yy_valid_obj()
{ 
    return(yy_true); 

}   // yy_valid_obj()
