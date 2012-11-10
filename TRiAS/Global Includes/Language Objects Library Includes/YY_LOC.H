
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_loc.h
//
//  FILE DESCRIPTION:     header file with location tracking class 
//                        declarations
//
//  OVERVIEW:
//
//    The location tracking classes determine what information is displayed
//    for the current location.  For example, this class is used throughout
//    the Language Objects Library for error reporting.  Error messages 
//    may contain the file name and line number, or similar information as
//    the location.
//
//    The location tracking classes are all defined in terms of the abstract
//    base class yy_loc_obj, which provides the interace which all location 
//    classes must provide.  The default location class, yy_loc_dflt_obj, 
//    provides the default location information, which is an empty string, 
//    but which can be changed to any string.  A stack of location objects 
//    is provided via the location stack class, yy_loc_stack_obj, which is
//    used in the error class.
//
//    The input and command classes are derived from the abstract location
//    tracking class.  Each class redefines yy_loc_print_self(), the location
//    tracking member function which knows how to display the current location
//    for that class.  
//
//  MODIFICATION HISTORY:
//
//    04/05/93   bz/cc    initial coding of location tracking classes.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_loc_h_
#define yy_loc_h_

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"

typedef class yy_export yy_err_obj           *yy_err_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_loc_ptr          is a typedef which defines a pointer to a location
//                      tracking object.
//
//  yy_loc_dflt_ptr     is a typedef which defines a pointer to a default
//                      location tracking object.
//
//  yy_loc_stack_ptr    is a typedef which defines a pointer to a location
//                      stack object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_loc_obj        *yy_loc_ptr;
typedef class yy_export yy_loc_dflt_obj   *yy_loc_dflt_ptr;
typedef class yy_export yy_loc_stack_obj  *yy_loc_stack_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_loc_obj
//
//  The yy_loc_obj is an abstract base class which provides the interface 
//  definition for the location tracking used in the Language Objects Library.
//  If you are replacing the location tracking scheme at the most fundamental
//  level, this class provides the minimal interface you need to support.
//
//  Classes which know how to display their location, for example the input
//  and command line objects, inherit from this object.
//
//  Location objects can be stacked using a location stack object.  The
//  links holding the stack together are kept in this abstract base class.
//  This means a location tracking object can only be on one location
//  stack.  When a location stack class is deleted, all location tracking
//  objects on the stack are deleted with it.
//
//  How the location tracking class is used:
//
//      If the Language Objects Library detects an error, it calls 
//      yy_err_report() which calls the yy_loc_print_self() of the location
//      object on the top of the location stack associated with the error 
//      object.
//
//  PUBLIC FUNCTIONS:
//
//  yy_loc_obj()        constructors for a location tracking object.
//
//  ~yy_loc_obj()       destructor for a location tracking object.
//
//  yy_loc_prev([yy_loc_ptr])
//                      gets (or sets with an argument) the previous 
//                      location tracking object on the location stack
//                      which this location tracking object is on.
//
//  yy_loc_print_self() displays the location being tracked.
//
//  INTERNAL STATE:
//
//  yy_prev             is a pointer to the previous object on the location 
//                      stack.  This is NULL at the base of the stack.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_loc_obj {

 public:

    yy_loc_obj(): yy_prev(NULL) {}

    yy_loc_obj(yy_loc_ptr yy_new_prev): yy_prev(yy_new_prev) {}

    virtual ~yy_loc_obj() {}

    inline yy_loc_ptr yy_loc_prev();

    inline yy_loc_ptr yy_loc_prev(yy_loc_ptr yy_new_prev);
        
    virtual yy_boolean yy_loc_print_self(
        yy_err_ptr
        ) = 0;

 protected:

    yy_loc_ptr    yy_prev;

    };  // yy_loc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the location object, defined above.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_loc_ptr yy_loc_obj::yy_loc_prev()
    { return (yy_prev); }
    
inline yy_loc_ptr yy_loc_obj::yy_loc_prev(yy_loc_ptr yy_new_prev)
    { return (yy_prev = yy_new_prev); }
    

//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_loc_dflt_obj
//
//  The yy_loc_dflt_obj is the default location tracking class.  By default, 
//  there is no information associated with the current location and nothing
//  is displayed.
//
//  How this class is used:
//
//  1)  When a location stack is created, it is initialized with a pointer
//      to a default location object.  This guarantees there is always a
//      location tracking object on the stack.  If the location object
//      on the bottom of the stack is called to report its location, it
//      displays an empty string.
//
//  2)  This class can also be used to create location tracking objects
//      which display a fixed message.  The second constructor is provided
//      for this purpose.
//
//  PUBLIC FUNCTIONS:
//
//  yy_loc_dflt_obj()   constructors for default location objects.
// 
//  ~yy_loc_dflt_obj()  destructor for default location objects.
// 
//  yy_loc_msg([const char*])
//                      gets (or sets with an argument) the message to 
//                      display.
//
//  yy_loc_print_self() displays the location being tracked.
//
//  INTERNAL STATE:
//
//  yy_loc_dflt_msg     the message to display as the location information.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_loc_dflt_obj : public yy_loc_obj {

 public:
    
    yy_loc_dflt_obj();

    yy_loc_dflt_obj(const char*);

    yy_loc_dflt_obj(
        yy_err_ptr,
        const char* = NULL
        );

    virtual ~yy_loc_dflt_obj();

    virtual char *yy_loc_msg()
        { return(yy_loc_dflt_msg); }

    virtual char *yy_loc_msg(const char*);

    virtual yy_boolean yy_loc_print_self(yy_err_ptr);

 protected:

    char                *yy_loc_dflt_msg;

    };  // yy_loc_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_loc_stack_obj
//
//  The yy_loc_stack_obj provides the stacks of location tracking objects 
//  used in the Language Objects Library.
//
//  The stack of location tracking objects is used to support the concept
//  of a "current location".  The error objects use a stack of location
//  objects for displaying current location information with error reports.
//
//  The location stack provides "pushes" and "pops".  When a location 
//  tracking object is pushed onto the location stack, it is registered as
//  the current location.  Another location tracking object may push itself
//  onto the location stack and become the current location.  When no longer
//  relevant, the location object(s) pop themselves off the location stack.
//
//  SPECIAL NOTES:    
//
//  To guarantee there is always a location tracking object, the bottom
//  element of the location stack is special.
//
//  When the location stack is created, the bottom element of the stack is
//  initialized to point to a yy_loc_dflt_obj, which displays an empty string.
//
//  The special bottom location tracking object is never popped.
//
//  The second constructor allows creation of location stacks with a different
//  location tracking object at the bottom, rather than the default location 
//  tracking object.
//
//  PUBLIC FUNCTIONS:
//
//  yy_loc_stack_obj()  constructors for location stack objects.
// 
//  ~yy_loc_stack_obj() destructor for location stack objects.
//
//  yy_loc_stack_pop()  pops the top location object from the stack, unless
//                      this would make the stack empty.  (The bottom location
//                      element on the stack always remains.)
//
//  yy_loc_stack_push() pushes a new location object onto the top of the 
//                      stack.
//
//  yy_loc_stack_top()  returns the top location object on the stack.
//
//  INTERNAL STATE:
//
//  yy_top              is a pointer to the location object at the top of
//                      the stack.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_loc_stack_obj {

 public:
    
    yy_loc_stack_obj();

    yy_loc_stack_obj(yy_loc_ptr);

    virtual ~yy_loc_stack_obj();

    virtual void yy_loc_stack_pop();

    virtual void yy_loc_stack_push(yy_loc_ptr);

    virtual yy_loc_ptr yy_loc_stack_top()
        { return (yy_top); }

 protected:

    yy_loc_ptr          yy_top;

    };  // yy_loc_stack_obj

#endif /* yy_loc_h_ */
