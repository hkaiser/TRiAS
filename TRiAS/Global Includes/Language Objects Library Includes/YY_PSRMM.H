
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1998, Compiler Resources, Inc.
//
//  FILENAME:             yy_psrmm.h
//  
//  FILE DESCRIPTION:     header file with parser memento object declarations
//
//  CLASS HIERARCHY:
//
//               +------------------------+
//               |    memento abstract    |
//               |      base class        |
//               |     (yy_memen.h)       |
//               +------------------------+
//                           | derives      
//                           |
//               +------------------------+
//               |     parser memento     |
//               |  abstract base class   |
//               |     (yy_psrmm.h)       |
//               +------------------------+
//                           | derives      
//                           |
//             +-----------------------------+
//             |  generated parser memento   |
//             | class(es) from your grammar |
//             |       (yy_mypsr.h)          |
//             +-----------------------------+
//
//    
//  MODIFICATION HISTORY:
//  
//  04/29/98	cc	coding and final review completed.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_psrmm_h_
#define yy_psrmm_h_


//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES:
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_memen.h"

//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_psr_ptr          is a typedef which defines a pointer to a parser
//                      object.
//
//  yy_psr_memento_ptr	is a typedef which defines a pointer to a parser
//                      memento object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_psr_obj      	*yy_psr_ptr;

typedef class yy_export yy_psr_memento_obj     	*yy_psr_memento_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_memento_obj
//
//  The yy_psr_memento_obj is the base class which provides the interface to
//  parser mementos (saved parser states).  A parser memento saves the parts
//  of a parser state which are dynamic during parsing.  It does not save
//  the parts of a parser state which are "static" (normally unchanging
//  during a parse), such as the lexer-parser connection.
//
//  PUBLIC FUNCTIONS:
//
//  ~yy_psr_memento_obj()
//		        destructor for a parser memento object.
//
//  Additional parser memento functions are derived from the yy_memento_obj.
//  See it for further documentation.
//
//
//  INTERNAL FUNCTIONS (only for use in derived objects):
//
//  yy_psr_memento_obj()
//			constructor for a parser memento object.
//		     
//  yy_psr_memento_obj(yy_old_psr_memento)
//			copy constructor for a parser memento object.
//		     
//  operator=		assignment operator for a parser memento object.
//
//
//  INTERNAL STATE:
//
//  Internal state is derived from the yy_memento_obj.  See it for further
//  documentation.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_memento_obj : public yy_memento_obj
{

 public:

    virtual ~yy_psr_memento_obj();

 protected:

    yy_psr_memento_obj();
    
    yy_psr_memento_obj(
	const yy_psr_memento_obj	&yy_old_psr_memento_obj);

    yy_psr_memento_obj(
	const yy_psr_obj		&yy_old_psr_obj);

    yy_psr_memento_obj &operator=(
	const yy_psr_memento_obj	&yy_old_psr_memento_obj);

};  // yy_psr_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the parser memento object
//  declared above.
//
//////////////////////////////////////////////////////////////////////////////


#endif /* yy_psrmm_h_ */
