
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_inp
//                        (note that this was yy_file at previous revs)
//
//  FILE DESCRIPTION:     nested input object support 
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	  Removed yy_no_myref_inlines_ as it didn't work with
//			  several compilers.
//    09/01/98   bz       added single parameter yy_inp_is_string() to match
//                        LOL documentation.
//    06/24/98   cc       pick up yy_inp_dmp parameter change from rev 2.1
//			  solaris version -- a hiding problem
//    05/08/98   bz       prevent reference to yy_myref.h when compiling LOL.
//    08/06/95   bz/cc    removed copying of buffer into input object since
//                        setting yy_inp_cur_lex(NULL) already does it and
//                        doing it twice turns the first copy into a memory
//                        leak.
//    04/06/94   bz       added yy_inp_cur_offset().
//    03/14/94   bz       further safeguarded the string input object from
//                        ever attempting to delete the user string. The 
//                        input string class now has its own yy_inp_close().
//    01/20/94   bz       moved yy_filename related code to base object.
//    11/08/93   cc       changed semantics relating to input, lexer, and
//                        buffer object connections so the buffer pointer
//                        is no longer set to NULL on a close but rather
//                        set to point back to the lexer's buffer.  (fixes
//                        eofa).  
//    09/29/93   bz/cc    close the input object in the string destructor,
//                        because the base destructor will not call the string
//                        objects close function (as that would require a 
//                        virtual call).
//    04/19/93   bz/cc    native C++ rewrite of input (file) object.
//    04/05/93   bz       new forwarding scheme for yy_err_report() and
//                        removed yy_file_is_textsw().
//    10/30/92   bz       disabled warning 4505 for Microsoft 7.0.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and review completed.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_inp_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdef.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_inp.h"
#include "yy_lex.h"
#include "yy_trace.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_obj::yy_inp_obj()
//
//  This is the no argument constructor for the base class input object.
//
//  This can only be constructed from a derived class.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_obj::yy_inp_obj() :
    yy_filename(NULL),
    yy_this_buf_obj(NULL),
    yy_this_err_obj(NULL),
    yy_this_lex_obj(NULL),
    yy_prev_ptr(NULL),
    yy_buf_state(yy_inp_buf_state_init_)
{
}   // no argument constructor for yy_inp_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_obj::yy_inp_obj(yy_this_err_ptr)
//
//  This is the constructor for the base class input object whose parameter 
//  list is an error object.  
//
//  All Yacc++ derived input classes contain a constructor which matches
//  this one.  And it is this particular constructor in the derived class
//  which is typically used when creating an input object that is the 
//  initial input object for a given lexer and parser.
//
//  This can only be constructed from a derived class.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_obj::yy_inp_obj(
    yy_err_ptr  yy_this_err_ptr
    ) :
    yy_filename(NULL),
    yy_this_buf_obj(NULL),
    yy_this_err_obj(yy_this_err_ptr),
    yy_this_lex_obj(NULL),
    yy_prev_ptr(NULL),
    yy_buf_state(yy_inp_buf_state_init_)
{

//  push this input object onto the error stack given as the parameter, so 
//  this input object determines the location displayed when an error occurs

    if (yy_this_err_ptr != NULL) {
        yy_this_err_ptr -> yy_err_push_location(this);
        }

}   // constructor for yy_inp_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   nesting constructor yy_inp_obj::yy_inp_obj(yy_this_inp_ptr)
//
//  This is the constructor for the base class input object whose parameter 
//  list is a pointer to an input object.  
//
//  This constructor creates a new input object which becomes the top input 
//  object on the stack.  The new input object is associated with the same 
//  lexer and error object as "yy_this_inp_ptr" which is now the previous 
//  entry on the stack.
//
//  All Yacc++ derived input classes contain a nesting constructor which
//  matches this one.  And it is the nesting constructor in the derived
//  class which is typically used when creating an input object which is
//  a nested input object for a given lexer and parser.
//
//  This can only be constructed from a derived class.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_obj::yy_inp_obj(
    yy_inp_ptr  yy_this_inp_ptr
    ) :
    yy_filename(NULL),
    yy_this_buf_obj(NULL),
    yy_this_err_obj(NULL),
    yy_this_lex_obj(NULL),
    yy_prev_ptr(yy_this_inp_ptr),
    yy_buf_state(yy_inp_buf_state_init_)
{

//  if the parameter was NULL, act like the default constructor -- do nothing

    if (yy_this_inp_ptr == NULL) {
        return;
        }

//  otherwise, copy the error object from the object which used to be on the
//  top of the stack

    yy_this_err_obj = yy_this_inp_ptr -> yy_this_err_obj;

//  push this input object onto the error stack 

    if (yy_this_err_obj != NULL) {
        yy_this_err_obj -> yy_err_push_location(this);
        }

//  if the input object just copied is using the lexer as its buffer,
//  associate this input object with that lexer object

    if (yy_this_inp_ptr -> yy_buf_state & yy_inp_buf_state_lexer_) {

        //  save a pointer to the lexer used in the previous input object

        yy_lex_ptr prev_lexer = yy_this_inp_ptr -> yy_this_lex_obj;

        //  save the buffer of the object which used to be on the top of the
        //  stack this disassociates the object from the lexer

        yy_this_inp_ptr -> yy_inp_buf_save();

        //  associate this new input object with the lexer

        yy_inp_cur_lex(prev_lexer);

        return;
        }

//  if the input object was not using a lexer, just save the buffer

    yy_this_inp_ptr -> yy_inp_buf_save();

}   // nesting constructor for yy_inp_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_inp_obj::~yy_inp_obj()
//
//  This is the destructor for the base class input object.  
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_obj::~yy_inp_obj() 
{

//  if the input is still open, close it

    if (yy_buf_state & yy_inp_buf_state_open_) {
        yy_inp_close(yy_true);
        }

//  if there is a filename, delete it

    if (yy_filename != NULL) { 
        delete [] yy_filename;
        yy_filename = NULL;
        }

//  if there is a lexer object, remove the input object from its stack

    if (yy_this_lex_obj != NULL) {
        if (yy_prev_ptr != NULL) {
            yy_prev_ptr -> yy_inp_cur_lex(yy_this_lex_obj);
            }
        yy_this_lex_obj = NULL;
        yy_this_buf_obj = NULL;
        }
        
//  if there still is a buffer, delete it

    if (yy_this_buf_obj != NULL) {
        delete yy_this_buf_obj;
        yy_this_buf_obj = NULL;
        }

//  if there is an error object, remove the input object from its stack

    if (yy_this_err_obj != NULL) {
        yy_this_err_obj -> yy_err_pop_location();
        yy_this_err_obj = NULL;
        }

//  if there is a nested input object on the stack, restore its buffer

    if (yy_prev_ptr != NULL) {
        yy_prev_ptr -> yy_inp_buf_restore();
        }

}   // destructor for yy_inp_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_restore()
//
//  yy_inp_buf_restore() restores a saved input buffer.      
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_obj::yy_inp_buf_restore()
{ 

//  un-mark the input object as nested

    yy_buf_state &= ~yy_inp_buf_state_nested_;

}   // yy_inp_buf_restore


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_save()
//
//  yy_inp_buf_save() saves the input buffer (in its own local copy).
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_obj::yy_inp_buf_save()
{ 

//  mark the input object as being nested

    yy_buf_state |= yy_inp_buf_state_nested_;

//  if the input object is using the lexer as its buffer, make it
//  use its own copy of the buffer and disassociate it from the lexer

    if (yy_buf_state & yy_inp_buf_state_lexer_) {

        assert(yy_this_lex_obj != NULL);

//  disassociate the input and lexer objects 
//  this will give the lexer an empty buffer

        yy_inp_cur_lex(NULL);

        }

}   // yy_inp_buf_save


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_close(yy_free_the_filename)
//
//  yy_free_the_filename     true if the filename stored within the 
//                           input stream object should be freed.
//                           (note that sometimes the filename isn't freed
//                           so the location print function still has access
//                           to the filename for error messages).
//
//  yy_inp_close() closes the input object by de-allocating the buffer.
//  It returns true if the input is successfully closed and false otherwise.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_obj::yy_inp_close(
    yy_boolean     yy_free_the_filename)
{ 

//  if the buffer is not open, don't do anything

    if ((yy_buf_state & yy_inp_buf_state_open_) == 0) {
        return(yy_false);
        }

//  delete the buffer from the buffer object

    if (yy_this_buf_obj -> yy_buf_start() != NULL) {
        delete [] yy_this_buf_obj -> yy_buf_start();
        yy_this_buf_obj -> yy_buf_start(NULL);
        }

//  if there is no lexer object, delete the buffer object

    if ((yy_buf_state & yy_inp_buf_state_lexer_) == 0) {
        assert(yy_this_lex_obj == NULL);
        if (yy_this_buf_obj != NULL) {
            delete yy_this_buf_obj;
            yy_this_buf_obj = NULL;
            }
        }

//  otherwise, we are using the buffer in the lexer object

    else {

        assert(yy_this_lex_obj != NULL);

        // use the lexer's buffer for this input object's buffer 

        yy_this_buf_obj = yy_buf_ptr(yy_this_lex_obj);

        // set the buffer into the initial state

        yy_this_buf_obj -> yy_buf_start(NULL);
        yy_this_buf_obj -> yy_buf_init();
        }

//  mark that we have closed the buffer

    yy_buf_state &= ~yy_inp_buf_state_open_;

//  free the filename, if requested

    if (yy_free_the_filename) {
        if (yy_filename != NULL) {
            delete [] yy_filename;
            yy_filename = NULL;
            }
        }

    return(yy_true);

}   // yy_inp_close


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_lex_ptr yy_inp_cur_lex(yy_new_lex_obj)
//
//  yy_inp_cur_lex() sets the lexer object associated with the input object.
//  If the argument is NULL then there is no lexer object associated with
//  the input object.
//
//////////////////////////////////////////////////////////////////////////////

yy_lex_ptr yy_inp_obj::yy_inp_cur_lex(
    yy_lex_ptr yy_new_lex_obj)
{ 

//  if request is to link to the same lexer object, no need to do anything

    if (yy_this_lex_obj == yy_new_lex_obj) {
        return(yy_this_lex_obj);
        }

//  only associate one lexer with an input object, so if this input object
//  already has a lexer object associated with it, disconnect that lexer
//  object first

    if (yy_this_lex_obj != NULL) {

        assert(yy_buf_state & yy_inp_buf_state_lexer_);

        //  if the file is open, it will need a private buffer

        if (yy_buf_state & yy_inp_buf_state_open_) {
            yy_this_buf_obj = new yy_buf_obj;
            if (yy_this_buf_obj == NULL) {
                yy_err_report(406);
                yy_assert_fail("space unavailable from new", 
                    __FILE__, __LINE__);
                return(yy_false);
                }

            //  copy the buffer portion of the lexer object into the 
            //  private buffer 

            *yy_this_buf_obj = *yy_buf_ptr(yy_this_lex_obj);

            //  set the lexer's buffer into the initial state

            yy_this_lex_obj -> yy_buf_start(NULL);
            yy_this_lex_obj -> yy_buf_init();
        
            }
        else {
            yy_this_buf_obj = NULL;
            }

        yy_this_lex_obj = NULL;
        yy_buf_state &= ~yy_inp_buf_state_lexer_;

        }

//  at this point in the code, there should be no lexer associated with the
//  input object.

    assert(yy_this_lex_obj == NULL);
    assert((yy_buf_state & yy_inp_buf_state_lexer_) == 0);

//  Nothing more needs to be done when the argument is a NULL lexer object.
//  (the code above already disassociated the lexer object from the input
//  object).  

    if (yy_new_lex_obj == NULL) {
        return(NULL);
        }

//  associate the lexer object from the input object when given a non-NULL
//  lexer object.  First mark the input object as having an associated
//  lexer object.

    yy_buf_state |= yy_inp_buf_state_lexer_;

//  if the input stream is already open, copy the buffer pointers into the
//  lexer, delete the old buffer object (but don't delete the buffer
//  itself as the lexer is pointing to it).  Finally, use the buffer
//  object in the lexer as the buffer object for this input.

    if (yy_buf_state & yy_inp_buf_state_open_) {

        assert(yy_this_buf_obj != NULL);
        assert(yy_buf_ptr(yy_new_lex_obj) != yy_this_buf_obj);

        //  copy the buffer into the buffer portion of the lexer object

        *yy_buf_ptr(yy_new_lex_obj) = *yy_this_buf_obj;

        //  get rid of the local buffer object, but not the buffer inside it
        //  if yy_start is NULL, the buffer won't be deleted in the destructor

        yy_this_buf_obj -> yy_buf_start(NULL);
        delete yy_this_buf_obj;

        //  use the lexer's buffer for this input object's buffer 

        yy_this_buf_obj = yy_buf_ptr(yy_new_lex_obj);

        }

//  if the input stream is not open, use the lexer's buffer and make empty

    else {

        assert((yy_buf_state & yy_inp_buf_state_open_) == 0);
        assert(yy_this_buf_obj == NULL);

        // use the lexer's buffer for this input object's buffer 

        yy_this_buf_obj = yy_buf_ptr(yy_new_lex_obj);

        // set the buffer into the initial state

        yy_this_buf_obj -> yy_buf_start(NULL);
        yy_this_buf_obj -> yy_buf_init();
        
        }

//  make the lexer object point to this input object
    
    yy_new_lex_obj -> yy_lex_cur_inp() = this;

//  link this input object back to the associated lexer object and we're done

    return(yy_this_lex_obj = yy_new_lex_obj); 

}   // yy_inp_cur_lex


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_dmp(yy_err_ptr yy_new_err_obj, 
//                      const char *yy_dmp_title)
//
//  yy_new_err_obj  is an error object where this dump is to be displayed.
//           
//  yy_dmp_title     a character string to identify the dump.
//
//  yy_inp_dmp() displays the values of the input object data members.  It
//  is a debugging function we used when we were developing Yacc++.  We
//  have included this function as a member of the input object in case 
//  you need to dump the internal state of the input being lexed and parsed.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_obj::yy_inp_dmp(
    yy_err_ptr   yy_new_err_obj, 
    const char   *yy_dmp_title)    
{

//  use the failsafe error object, if no error object to dump to

    if (yy_new_err_obj == NULL) {
        yy_new_err_obj = yy_err_failsafe_obj();
        }

//  display the title for the dump, if any

    if (yy_dmp_title != NULL) {
        yy_new_err_obj -> yy_err_printf("TITLE: %s\n", yy_dmp_title);
        }

//  print the location in the input buffer -- a line number by default

    yy_loc_print_self(yy_new_err_obj);

//  dump the fields specific to this object

    if (yy_filename != NULL) {
        yy_new_err_obj -> yy_err_printf("filename: %s ", yy_filename);
        }

//  display the buffer state

    switch(yy_buf_state) {

        case(yy_inp_buf_state_init_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=init\n");
            break;

        case(yy_inp_buf_state_open_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=open\n");
            break;

        case(yy_inp_buf_state_lexer_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=lexer\n");
            break;

        case(yy_inp_buf_state_lexer_and_open_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=lexer open\n");
            break;

        case(yy_inp_buf_state_nested_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=nested\n");
            break;

        case(yy_inp_buf_state_nested_open_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=nested open\n");
            break;

        case(yy_inp_buf_state_nested_lexer_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=nested lexer\n");
            break;

        case(yy_inp_buf_state_nested_lexer_and_open_): 
            yy_new_err_obj -> yy_err_puts(
                "buffer state=nested lexer open\n");
            break;
        
        default:
            yy_new_err_obj -> yy_err_printf(
                "Unknown buffer state=%d\n", yy_buf_state);
            break;
        };

//  display the contents of the buffer too

    if (yy_this_buf_obj != NULL) {
        yy_this_buf_obj -> yy_buf_dmp(yy_new_err_obj, NULL);
        }

}   // yy_inp_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_open_buf()
//
//  yy_inp_open_buf() opens the input object by allocating the input buffer.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_obj::yy_inp_open_buf()
{ 

//  the buffer must not be already opened

    assert((yy_buf_state & yy_inp_buf_state_open_) == 0);

//  if there is no lexer object, create a buffer object for the input

    if ((yy_buf_state & yy_inp_buf_state_lexer_) == 0) {
        assert(yy_this_lex_obj == NULL);
        yy_this_buf_obj = new yy_buf_obj;
        if (yy_this_buf_obj == NULL) {
            yy_err_report(406);
            yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
            return(yy_false);
            }
        }

//  otherwise, use the buffer in the lexer object

    else {
        assert(yy_this_lex_obj != NULL);
        assert(yy_this_buf_obj == yy_buf_ptr(yy_this_lex_obj));
        }

//  there should not be a buffer already in the buffer object

    assert(yy_this_buf_obj -> yy_buf_start() == NULL);
    assert(0 < yy_this_buf_obj -> yy_buf_size());

//  create the buffer in the buffer object with the default buffer size

    yy_this_buf_obj -> yy_buf_start(
        new char [yy_this_buf_obj -> yy_buf_size() + 1]);

    if (yy_this_buf_obj -> yy_buf_start() == NULL) {
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(yy_false);
        }

//  initialize the other buffer pointers

    yy_this_buf_obj -> yy_buf_init();

//  mark that we have opened the buffer

    yy_buf_state |= yy_inp_buf_state_open_;

    return(yy_true);

}   // yy_inp_open_buf


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_open_buf_finish_setup(yy_num_new_chars)
//
//  yy_num_new_chars    is the number of new characters inserted in the 
//                      buffer as a result of reading the first block
//
//  yy_inp_open_buf_finish_setup() sets the end of buffer pointer once
//  the first block in the buffer has been read.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_obj::yy_inp_open_buf_finish_setup(
    int     yy_num_new_chars)
{ 

//  the buffer must be open already

    assert(yy_buf_state & yy_inp_buf_state_open_);
    assert(yy_this_buf_obj != NULL);

//  adjust the end of buffer pointer

    yy_this_buf_obj -> yy_buf_end(
        yy_this_buf_obj -> yy_buf_start() + yy_num_new_chars);

//  all done

    return(yy_true);

}   // yy_inp_open_buf_finish_setup


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_rewind()
//
//  yy_inp_rewind() rewinds the input object stack to have one input object
//  in its initial state.
//
//  yy_inp_rewind() first closes all but the bottom most input object on
//  the stack.
// 
//  The type of the bottom input object determines what happens when it
//  is rewound.  Each derived input object redefines this function and
//  specifies the appropriate semantics for rewinding that type of input
//  object.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_obj::yy_inp_rewind()
{
    yy_inp_ptr  prev_inp_obj;      

//  close nested input objects on the stack (if any)

    if (yy_prev_ptr != NULL) {
        prev_inp_obj = yy_prev_ptr;
        yy_inp_close(yy_true);
        delete this;
        prev_inp_obj -> yy_inp_rewind();
        return;
        }

//  ok, we're through the recursive closes and we now know we are at
//  the bottom of the stack, but in the base object we don't have any
//  specific semantics for resetting the buffer pointers so we do nothing

}   // yy_inp_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_valid_obj()
//
//  yy_inp_valid_obj() returns true for any input object.  A derived
//  object may override this function and provide more meaningful checking
//  on the validity of an input object.  For example, the input signature
//  object checks the signature field to determine the validity of the object.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_obj::yy_inp_valid_obj()
{ 
    return(yy_true); 

}   // yy_inp_valid_obj()


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_report(yy_err_num, ...)
//
//  yy_err_report() looks up an error message in the error table and then
//  displays it by calling yy_err_vreport().  This function uses the
//  error object associated with this input object.  If the error is
//  displayed, it returns a non-zero value.  If the error is not displayed,
//  for example, there is no error object associated with this input object,
//  then 0 is returned.
//
//////////////////////////////////////////////////////////////////////////////

int yy_inp_obj::yy_err_report(
    int         yy_err_num,
    ...)
{
    va_list     yy_var_args;
    int         yy_return_value;

//  if we don't have an error object associated with this input object,
//  we're unable to display errors.  Return 0 that error was not displayed.

    if (yy_inp_cur_err() == NULL) {
        return(0);
        }

//  gather up the variable number of arguments for this format

    va_start(yy_var_args, yy_err_num);

//  use the associated error object to lookup, format, and display the error

    yy_return_value = yy_inp_cur_err() -> yy_err_vreport(yy_err_num, 
                          yy_var_args);

//  cleanup variable argument processing

    va_end(yy_var_args);

//  pass along return code -- 0 if nothing was displayed

    return(yy_return_value);

}   // yy_err_report


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_loc_print_self(yy_this_err)
//
//  yy_this_err     the error reporting object which controls where
//                  the location is to be displayed.
//
//  yy_loc_print_self() redefines the default location printing function.
//  The default location object displays nothing.  (input objects are 
//  derived from location objects).  For the base input object, the current
//  "filename" and line number is the location being tracked and displayed 
//  instead of nothing.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_obj::yy_loc_print_self(
    yy_err_ptr yy_this_err
    )
{

//  if there is no filename, display only a line number

    if (yy_filename == NULL) { 

        //  if there is no buffer, use ??? as the line number

        if (yy_this_buf_obj == NULL) {
            return(yy_this_err -> yy_err_puts("???: "));
            }

        return(yy_this_err -> yy_err_printf("line %d: ", 
            yy_this_buf_obj -> yy_buf_lineno()));
        }

//  if it has a filename, but there is no buffer, use the filename 
//  with ??? as the line number

    if (yy_this_buf_obj == NULL) {
        return(yy_this_err -> yy_err_printf("\"%s\", ???: ",
            yy_filename));
        }

//  if it has a filename and line number, display both

    return(yy_this_err -> yy_err_printf("\"%s\", line %d: ", 
        yy_filename, yy_this_buf_obj -> yy_buf_lineno()));

}   // yy_loc_print_self


//////////////////////////////////////////////////////////////////////////////
//
//      +----------------------+          +----------------------+
//      |        input         | -------> |     buffer class     |
//      | generic base class   | links to |      (yy_buf.h)      |
//      +----------------------+          +----------------------+
//                 | derives      
//                 |
//      +----------------------+
//      |  input string class  |
//      +----------------------+
//
//  Functions for the input string class begin below.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_string_obj::yy_inp_string_obj()
//
//  This is the no argument constructor for the input string object.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_string_obj::yy_inp_string_obj() :
    yy_inp_obj()
{
}   // constructor for yy_inp_string_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_string_obj::yy_inp_string_obj(
//                              yy_this_err)
//
//  This is the constructor typically used when creating an input string 
//  object which is the initial input object for a given lexer and parser.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_string_obj::yy_inp_string_obj(
    yy_err_ptr  yy_this_err) :
    yy_inp_obj(yy_this_err)
{
}   // constructor for yy_inp_string_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   nesting constructor yy_inp_string_obj::yy_inp_string_obj(
//                                      yy_this_inp_ptr)
//
//  This is the constructor for the input string object whose parameter list
//  is a pointer to an input object.  This constructor is typically used when
//  creating an input string object which is used to process a string input
//  nested within another input.
//
//  This constructor creates a new input string object which becomes the top
//  input object on the stack.  The new input object is associated with the
//  same lexer and error object as "yy_this_inp_ptr" which is now the previous
//  entry on the stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_string_obj::yy_inp_string_obj(
    yy_inp_ptr  yy_this_inp_ptr
    ) :
    yy_inp_obj(yy_this_inp_ptr)
{
}   // nesting constructor for yy_inp_string_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_inp_string_obj::~yy_inp_string_obj()
//
//  This is the destructor for the input string object.  This destructor
//  removes the string from the buffer so that the buffer deletion code in
//  the base close function does not attempt to delete the string.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_string_obj::~yy_inp_string_obj()
{

//  remove string from buffer

    if (yy_this_buf_obj != NULL && 
        (yy_buf_state & yy_inp_buf_state_open_)) {
        yy_this_buf_obj -> yy_buf_start(NULL);
        }

//  if the input is still open, close it

    if (yy_buf_state & yy_inp_buf_state_open_) {
        yy_inp_close(yy_true);
        }

}   // destructor for yy_inp_string_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_fill()
//
//  yy_inp_buf_fill() redefines the function in the base input object
//  which refills the input buffer.  
//
//  When parsing a string, a refill isn't needed.  yy_inp_buf_fill()
//  just adjusts the buffer to a clean final state for the lexer object.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_string_obj::yy_inp_buf_fill()    
{

//  as long as yy_buf_read and yy_buf_end are at the same position,
//  the lexer object will know that no more characters were read in
//  on this fill buffer call.

    yy_this_buf_obj -> yy_buf_read(yy_this_buf_obj -> yy_buf_end());

//  once the lexer realizes it has no additional characters read into
//  the buffer, it will check for EOF and terminate.

    yy_this_buf_obj -> yy_buf_eof_read(yy_true);

}   // yy_inp_buf_fill


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_close(yy_free_the_filename)
//
//  yy_inp_close() closes the input object by marking the buffer as closed,
//  not actually attempting to de-allocate the user string.  It returns 
//  true if the input is successfully closed and false otherwise.
//
//  note: yy_free_the_filename is not used by the string input object, but
//  it is included so the function signature matches in all input objects.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_string_obj::yy_inp_close(
    yy_boolean     yy_free_the_filename)
{
    // remove string from buffer to prevent attempts to delete it

    if (yy_this_buf_obj != NULL &&
        (yy_buf_state & yy_inp_buf_state_open_)) {
        yy_this_buf_obj->yy_buf_start(NULL);
        }

    // call the base input object close function

    return(yy_inp_obj::yy_inp_close(yy_free_the_filename));

}   // yy_inp_close


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   unsigned long yy_inp_cur_offset()
//
//  yy_inp_cur_offset() returns the offset in the input string of the 
//  character currently being lexed.
//
//////////////////////////////////////////////////////////////////////////////

unsigned long yy_inp_string_obj::yy_inp_cur_offset()
{

//  return the value of the string specific function cast to the generic type

    return((unsigned long)yy_inp_cur_offset_as_stringpos());

}   // yy_inp_cur_offset


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_string(yy_string_ptr) 
//
//  ** single parameter version **
//
//  yy_inp_is_string() puts the string into the input buffer.  This does
//  its own variation of yy_inp_open_buf() inline, because it uses the
//  string as the buffer itself so we don't have to copy the string (for
//  performance reasons).
//  
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_string_obj::yy_inp_is_string(
        char    *yy_string_ptr
        )
{
//  there must be a string to input from

    assert(yy_string_ptr != NULL);

    return( yy_inp_is_string(yy_string_ptr, strlen(yy_string_ptr)) );

}   // yy_inp_is_string


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_string(yy_string_ptr, yy_strlen)
//
//  yy_inp_is_string() puts the string into the input buffer.  This does
//  its own variation of yy_inp_open_buf() inline, because it uses the
//  string as the buffer itself so we don't have to copy the string (for
//  performance reasons).
//  
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_string_obj::yy_inp_is_string(
        char    *yy_string_ptr,
        int     yy_strlen
        )
{

//  there must be a string to input from

    assert(yy_string_ptr != NULL);

//  if this input file object is already open, we cannot open it again until
//  it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        yy_err_report(14);  
        return(yy_false);
        }

//  the buffer must not be opened already

    assert((yy_buf_state & yy_inp_buf_state_open_) == 0);

//  if there is no lexer object, create a buffer object for the input

    if ((yy_buf_state & yy_inp_buf_state_lexer_) == 0) {
        assert(yy_this_lex_obj == NULL);
        yy_this_buf_obj = new yy_buf_obj;
        if (yy_this_buf_obj == NULL) {
            yy_err_report(406);
            yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
            return(yy_false);
            }
        }

//  otherwise, use the buffer in the lexer object

    else {
        assert(yy_this_lex_obj != NULL);
        yy_this_buf_obj = yy_buf_ptr(yy_this_lex_obj);
        }

//  there should not be a buffer already in the buffer object

    assert(yy_this_buf_obj -> yy_buf_start() == NULL);

//  create the buffer in the buffer object with the default buffer size

    yy_this_buf_obj -> yy_buf_size(yy_strlen);
    yy_this_buf_obj -> yy_buf_start(yy_string_ptr);

//  initialize the other buffer pointers

    yy_this_buf_obj -> yy_buf_init();

//  mark that we have opened the buffer

    yy_buf_state |= yy_inp_buf_state_open_;

//  now set the end of buffer pointer

    return(yy_inp_open_buf_finish_setup(yy_strlen));

}   // yy_inp_is_string


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_rewind()
//
//  yy_inp_rewind() rewinds the input object stack to have one input object
//  in its initial state.
//
//  yy_inp_rewind() first closes all but the bottom most input object on
//  the stack.
// 
//  If the remaining input object on the stack is an input string object
//  which is open, yy_inp_rewind() resets it to its initial state --
//  the buffer pointing to the beginning of the string.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_string_obj::yy_inp_rewind()
{
    yy_inp_ptr  prev_inp_obj;      

//  close nested input objects on the stack (if any)

    if (yy_prev_ptr != NULL) {
        prev_inp_obj = yy_prev_ptr;
        yy_inp_close(yy_true);
        delete this;
        prev_inp_obj -> yy_inp_rewind();
        return;
        }

//  ok, we're through the recursive closes and we now know we are at
//  the bottom of the stack and the remaining input object is a string
//  input object.  If the string input object is open, we rewind it to
//  its initial state.  If it is already closed, we do nothing.

    if (yy_buf_state & yy_inp_buf_state_open_) {
        yy_this_buf_obj -> yy_buf_init();
        yy_inp_open_buf_finish_setup(yy_this_buf_obj -> yy_buf_size());
        }

}   // yy_inp_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_loc_print_self(yy_err_ptr)
//
//  yy_loc_print_self() redefines the default location printing function.
//  The base input object displays the current line number as the location
//  being tracked.  For string input, display the string up to and including
//  the current character, but no more than 40 characters.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_string_obj::yy_loc_print_self(
    yy_err_ptr yy_this_err
    )
{
    int     code;
    char    save_char;
    size_t  offset;

//  temporarily terminate the string one character beyond current location

    save_char = *(yy_this_buf_obj -> yy_buf_tkn_end()+1);
    *(yy_this_buf_obj -> yy_buf_tkn_end()+1) = '\0';

//  limit display to 40 characters -- compute offset accordingly

    offset = (size_t) (yy_this_buf_obj -> yy_buf_tkn_end() - 
        yy_this_buf_obj -> yy_buf_start());

    if (offset > 40) {
        offset = offset - 40;
        }
    else {
        offset = 0;
        }

//  display the string up to and including the current location

    code = yy_this_err -> yy_err_printf("at %s\n\n", 
        yy_this_buf_obj -> yy_buf_start()+offset);

//  restore buffer to original state

    *(yy_this_buf_obj -> yy_buf_tkn_end()+1) = save_char;

    return(code);

}   // yy_loc_print_self
