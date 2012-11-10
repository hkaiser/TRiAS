
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-94, Compiler Resources, Inc.
//
//  FILENAME:             yy_loc
//
//  FILE DESCRIPTION:     location tracking object support
//
//  MODIFICATION HISTORY:
//
//    04/05/93   bz/cc    initial coding of location tracking classes.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#ifndef yy_loc_code_
#define yy_loc_code_ 1
#endif /* yy_loc_code_ */

#include "yy_ansi.h"
#include "yy_strng.h"
#include "yy_err.h"
#include "yy_loc.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_loc_dflt_obj()
//
//  This is the constructor for the default location tracking object.
//
//////////////////////////////////////////////////////////////////////////////

yy_loc_dflt_obj::yy_loc_dflt_obj() :
    yy_loc_obj(), 
    yy_loc_dflt_msg(NULL)
{
}   // yy_loc_dflt_obj -- no arg constructor


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_loc_dflt_obj(yy_msg)
//
//  This is the constructor for the default location object which fills in
//  the fields in a yy_loc_dflt_obj with values that cause "yy_msg", the
//  message given as an argument, to be displayed as the location being
//  tracked.
//
//  yy_msg         the message to be displayed.
//
//////////////////////////////////////////////////////////////////////////////

yy_loc_dflt_obj::yy_loc_dflt_obj(
    const char  *yy_msg
    ) :
    yy_loc_obj()
{
    size_t      yy_msg_len;

//  create a copy of the new message

    if (yy_msg != NULL) {
        yy_msg_len = strlen(yy_msg);
        yy_loc_dflt_msg = new char [yy_msg_len];
        memcpy(yy_loc_dflt_msg, yy_msg, yy_msg_len);
        }
    else {
        yy_loc_dflt_msg = NULL;
        }

}   // yy_loc_dflt_obj -- 1 arg constructor


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor ~yy_loc_dflt_obj()
//
//  This is the destructor for the default location object.  It deletes
//  the message string if there is one.
//
//////////////////////////////////////////////////////////////////////////////

yy_loc_dflt_obj::~yy_loc_dflt_obj()
{

//  if there is a message, delete it

    if (yy_loc_dflt_msg != NULL) {
        delete [] yy_loc_dflt_msg;
        yy_loc_dflt_msg = NULL;
        }

}   // ~yy_loc_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_loc_msg(yy_msg)
//  
//  yy_loc_msg() sets the message string in the location object.
//
//  yy_msg  the message to be displayed.
//
//////////////////////////////////////////////////////////////////////////////

char *yy_loc_dflt_obj::yy_loc_msg(
    const char          *yy_msg
    )
{
    int                 yy_msg_len;

//  delete the old message

    if (yy_loc_dflt_msg != NULL) {
        delete [] yy_loc_dflt_msg;
        yy_loc_dflt_msg = NULL;
        }

//  insert a new message

    if (yy_msg != NULL) {
        yy_msg_len = strlen(yy_msg);
        yy_loc_dflt_msg = new char [yy_msg_len];
        memcpy(yy_loc_dflt_msg, yy_msg, yy_msg_len);
        }
    else {
        yy_loc_dflt_msg = NULL;
        }

    return(yy_loc_dflt_msg);

}   // yy_loc_msg -- 1 arg


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_loc_print_self(yy_this_err)
//
//  yy_loc_print_self() displays the message string as the location being 
//  tracked.  If the message string is NULL, nothing is diplayed.
//
//  yy_this_err     the error object on which the location is displayed.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_loc_dflt_obj::yy_loc_print_self(
    yy_err_ptr yy_this_err
    )
{

//  if there is a message, display it;  otherwise, display nothing

    if (yy_loc_dflt_msg != NULL && yy_this_err != NULL) {
        return(yy_this_err->yy_err_puts(yy_loc_dflt_msg));
        }
    else {
        return(0);
        }

}   // yy_loc_print_self


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_loc_stack_obj()
//
//  This is the no argument constructor for the stack of location tracking
//  objects.  This constructor is used for the creation of a new stack of
//  location tracking objects.
//
//////////////////////////////////////////////////////////////////////////////

yy_loc_stack_obj::yy_loc_stack_obj() :
    yy_top(new yy_loc_dflt_obj)
{
}   // yy_loc_stack_obj -- no arg constructor


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_loc_stack_obj(yy_loc)
//
//  This is the constructor for the stack of location tracking objects.
//  This constructor is used for the creation of a new stack of location
//  tracking objects, when a special location tracking object should be
//  at the bottom of the stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_loc_stack_obj::yy_loc_stack_obj(
    yy_loc_ptr      yy_loc
    ) :
    yy_top(yy_loc)
{
}   // yy_loc_stack_obj -- 1 arg constructor


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor ~yy_loc_stack_obj()
//
//  This function deletes all of the location tracking objects on the stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_loc_stack_obj::~yy_loc_stack_obj()
{
    yy_loc_ptr yy_loc_prev;

    while (yy_top != NULL) {
        yy_loc_prev = yy_top -> yy_loc_prev();
        yy_top -> yy_loc_prev(NULL);
        delete yy_top;
        yy_top = yy_loc_prev;
        }

}   // ~yy_loc_stack_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_loc_stack_pop()
//  
//  yy_loc_stack_pop() removes the top location tracking object from the 
//  stack, unless the stack would become empty.
//
//////////////////////////////////////////////////////////////////////////////

void yy_loc_stack_obj::yy_loc_stack_pop()
{
    yy_loc_ptr        yy_loc_prev;

//  if we are at the bottom of the stack, do nothing

    if (yy_top == NULL || yy_top -> yy_loc_prev() == NULL) {
        return;
        }

//  save a pointer to the next to top element

    yy_loc_prev = yy_top -> yy_loc_prev();

//  clear out the former top elements, prev pointer

    yy_top -> yy_loc_prev(NULL);

//  set the top pointer to the new top of the stack

    yy_top = yy_loc_prev;

}   // yy_loc_stack_pop


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_loc_stack_push(yy_loc)
//  
//  yy_loc_stack_push() adds the location tracking object to the top of the 
//  stack.
//
//////////////////////////////////////////////////////////////////////////////

void yy_loc_stack_obj::yy_loc_stack_push(
    yy_loc_ptr      yy_loc
    )
{

//  link the new top element to its previous element on the stack

    yy_loc -> yy_loc_prev(yy_top);

//  put the location object in the top element on the stack

    yy_top = yy_loc;

}   // yy_loc_stack_push
