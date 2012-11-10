
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-97, Compiler Resources, Inc.
//
//  FILENAME:             yy_ast.h
//  
//  FILE DESCRIPTION:     header file with the abstract syntax tree 
//                        (AST) object class declarations
//  
//  CLASS HIERARCHY:
//
//
//  +--------------------------+     +--------------------------+
//  |  AST abstract base class |     |  AST abstract base class |
//  |    with dump functions   |     |  without dump functions  |
//  |     yy_ast_dump_obj      |     |     yy_ast_nodump_obj    |     
//  +--------------------------+     +--------------------------+
//            |                                   |
//            +-----------------------------------+
//                     | one of them derives
//                     |
//         +------------------------+          +------------------------+
//         |          AST           | -------> |          AST           |
//         |  abstract base class   | derives  |     with signatures    |
//         +      yy_ast_obj        +          +------------------------+
//         +------------------------+
//                     | derives                       
//         +------------------------+
//         |     BASE CONSTRUCT     |
//         |      per class (?)     |
//         |   from your grammar    |
//         +------------------------+
//                     | derives                       
//         +------------------------+
//         | per token, parser non- |
//         | terminal, alternative  |
//         | as specified in your   |
//         |        grammar         |
//         +------------------------+
//
//  The yy_ast is an element in an abstract syntax tree (AST).  An AST
//  is the tree representation of the input after it was lexed and parsed.
//
//  The abstract base classes define the interface used by other parts
//  of the Language Objects Library.  If you are using your own AST
//  class, you need to define an interface matching the abstract base
//  classes. 
//
//  If you do not use the CONSTRUCT declaration in your grammar, you can
//  delete yy_ast.cxx from your Language Objects Library.
//
//
//  MODIFICATION HISTORY:
//  
//    07/07/97   bz/cc    added missing yy_bool.h.
//    06/12/96   bz       changed the yy_ast_obj hierarchy to include a
//                        choice of yy_ast_nodump_obj or yy_ast_dump_obj
//                        as its abstract base class.  This was done 
//                        in conjunction with "yxx -no_ast_dump".
//    09/07/93   bz/cc    recoded to be abstract base class only.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_ast_h_
#define yy_ast_h_

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"

typedef class yy_export yy_err_obj           *yy_err_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_ast_ptr           is a typedef which defines a pointer to an abstract
//                       syntax tree (AST).
//
//  yy_ast_dump_ptr      is a typedef which defines a pointer to an abstract
//                       syntax tree (AST) with dump functions.
//
//  yy_ast_nodump_ptr    is a typedef which defines a pointer to an abstract
//                       syntax tree (AST) without dump functions.
// 
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_ast_obj          *yy_ast_ptr;

typedef class yy_export yy_ast_dump_obj     *yy_ast_dump_ptr;

typedef class yy_export yy_ast_nodump_obj   *yy_ast_nodump_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_ast_dump_obj
//
//  The yy_ast_dump_obj is an element in an abstract syntax tree (AST).  
//  An AST is the tree representation of the input after it was lexed and 
//  parsed.  It does not include REMOVE symbols or DISCARD tokens.
//
//  The difference between this class and the yy_ast_nodump_obj class is that
//  it contains the yy_dump member function for each AST in the tree and
//  supports the yy_valid_obj validity checking.
//
//  PUBLIC FUNCTIONS:
//
//  ~yy_ast_dump_obj()  destructor for an AST object.
//
//  yy_type()           returns the AST type of the AST object.
//
//  yy_dump()           dumps the contents of an AST object.
//
//  yy_valid_obj()      supports yy_ast_valid_ptr(ast_ptr) by returning TRUE
//                      for a valid AST object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_ast_dump_obj {

 public:

    virtual ~yy_ast_dump_obj() {}

    virtual int yy_type() = 0;

    virtual void yy_dump(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dump_title) = 0;

    virtual yy_boolean yy_valid_obj();

    };  // yy_ast_dump_obj
    

//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_ast_nodump_obj
//
//  The yy_ast_nodump_obj is an element in an abstract syntax tree (AST).  
//  An AST is the tree representation of the input after it was lexed and 
//  parsed.  It does not include REMOVE symbols or DISCARD tokens.
//
//  PUBLIC FUNCTIONS:
//
//  ~yy_ast_nodump_obj()
//                      destructor for an AST object.
//
//  yy_type()           returns the AST type of the AST object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_ast_nodump_obj {

 public:

    virtual ~yy_ast_nodump_obj() {}

    virtual int yy_type() = 0;

    };  // yy_ast_nodump_obj
    

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_ast_valid_ptr(yy_this_ast)
//
//  yy_ast_valid_ptr checks the validity of a pointer to a yy_ast.
//  Before calling the virtual function in the AST object which performs 
//  the check, it checks here for NULL (to avoid unexpected crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_ast_valid_ptr(
    yy_ast_dump_ptr  yy_this_ast)
{

   if (yy_this_ast != NULL) {
      return(yy_this_ast->yy_valid_obj());       
      }
   else {
      return(yy_false);
      }
   
}  // yy_ast_valid_ptr


#endif /* yy_ast_h_ */


