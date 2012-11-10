
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_buf
//
//  FILE DESCRIPTION:     buffer support used by lexer and input objects
//
//  MODIFICATION HISTORY:
//
//    12/21/98   bz  	  Reordered constructor to match the sequence of 
//                        protected data members in yy_buf_obj class declaration.
//    01/28/98   bz       Changed variable name yy_read to yy_read_ptr.  This
//                        avoids a naming conflict with the yy_stdio.h yy_read 
//                        redefinition needed for prefixing file functions 
//                        for PC compilers.                          
//    05/05/93   bz       native C++ rewrite of input (file) object.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_buf_c_ 1

#include "yy_buf.h"
#include "yy_err.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_buf_obj::yy_buf_obj()
//
//  This is the no argument constructor for the buffer object.
//
//////////////////////////////////////////////////////////////////////////////

yy_buf_obj::yy_buf_obj() :
    yy_start(NULL),
    yy_read_ptr(NULL),
    yy_end(NULL),
    yy_tkn_start(NULL),
    yy_tkn_end(NULL),
    yy_size(yy_buf_dflt_size_),
    yy_grow_by(yy_buf_dflt_grow_by_),
    yy_lhead_state(yy_buf_lhead_state_not_read_),
    yy_lhead_char((int) EOF),
    yy_lineno(0),
    yy_eof_read(yy_false)
{
}   // constructor for yy_buf_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   copy constructor yy_buf_obj::yy_buf_obj(...)
//
//  This is the copy constructor for the buffer object.  It constructs a
//  buffer object which matches the object being copied.
//
//////////////////////////////////////////////////////////////////////////////

yy_buf_obj::yy_buf_obj(
    const yy_buf_obj     &yy_copy_from_buf
    ) :
    yy_start(yy_copy_from_buf.yy_start),
    yy_read_ptr(yy_copy_from_buf.yy_read_ptr),
    yy_end(yy_copy_from_buf.yy_end),
    yy_tkn_start(yy_copy_from_buf.yy_tkn_start),
    yy_tkn_end(yy_copy_from_buf.yy_tkn_end),
    yy_size(yy_copy_from_buf.yy_size),
    yy_grow_by(yy_copy_from_buf.yy_grow_by),
    yy_lhead_state(yy_copy_from_buf.yy_lhead_state),
    yy_lhead_char(yy_copy_from_buf.yy_lhead_char),
    yy_lineno(yy_copy_from_buf.yy_lineno),
    yy_eof_read(yy_copy_from_buf.yy_eof_read)
{
}   // copy constructor for yy_buf_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   assignment operator yy_buf_obj::operator=(...)
//
//  This is the assignment operator for the buffer object.  It assigns
//  the fields from one buffer object to another object.
//
//////////////////////////////////////////////////////////////////////////////

yy_buf_obj &yy_buf_obj::operator=(
    const yy_buf_obj     &yy_copy_from_buf
    )
{

//  assigning to yourself is a no-op

    if (this == &yy_copy_from_buf) {
        return(* this);
        }

//  delete the old buffer if there is one

    if (yy_start != NULL) {
        delete [] yy_start;
        yy_start = NULL;
        }

//  move the fields

    yy_start        = yy_copy_from_buf.yy_start;
    yy_read_ptr     = yy_copy_from_buf.yy_read_ptr;
    yy_end          = yy_copy_from_buf.yy_end;
    yy_tkn_start    = yy_copy_from_buf.yy_tkn_start;
    yy_tkn_end      = yy_copy_from_buf.yy_tkn_end;
    yy_grow_by      = yy_copy_from_buf.yy_grow_by;
    yy_lhead_state  = yy_copy_from_buf.yy_lhead_state;
    yy_lhead_char   = yy_copy_from_buf.yy_lhead_char;
    yy_lineno       = yy_copy_from_buf.yy_lineno;
    yy_size         = yy_copy_from_buf.yy_size;
    yy_eof_read     = yy_copy_from_buf.yy_eof_read;

    return(* this);

}   // assignment operator for yy_buf_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_buf_obj::~yy_buf_obj()
//
//  This is the destructor for the buffer object.
//  
//  If the input has been closed before the delete of the buffer object,
//  there is no open input buffer to delete.  The buffer was deleted at
//  the time of the close and yy_start was set to NULL.  
//
//  If a close operation has not already been performed, the open input
//  buffer is deleted now.
//
//////////////////////////////////////////////////////////////////////////////

yy_buf_obj::~yy_buf_obj() 
{

//  delete the input buffer, if needed

    if (yy_start != NULL) {
        delete [] yy_start;
        yy_start = NULL;
        }
        
}   // destructor for yy_buf_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_buf_dmp(yy_this_err_obj, yy_dmp_title)
//
//  yy_buf_dmp() displays the values of the buffer state variables
//
//  yy_buf_dmp() is a debugging function we used when we were developing 
//  Yacc++.  We have included this function in case you want to dump the 
//  internal state of a buffer object associated with a lexer or input
//  object.
//
//////////////////////////////////////////////////////////////////////////////

void yy_buf_obj::yy_buf_dmp(
    yy_err_ptr   yy_this_err_obj, 
    const char   *yy_dmp_title)
{
    char  *char_ptr;

//  use the failsafe error object, if no error object to dump to

    if (yy_this_err_obj == NULL) {
        yy_this_err_obj = yy_err_failsafe_obj();
        }

//  display the title for the dump, if any

    if (yy_dmp_title != NULL) {
        yy_this_err_obj -> yy_err_printf("TITLE: %s\n", yy_dmp_title);
        }

//  display the EOF status

    if (yy_eof_read) {
        yy_this_err_obj -> yy_err_puts("@ EOF ");
        }

//  display the current token in the buffer

    yy_this_err_obj -> yy_err_printf("buf[%u..%u] = \"", 
        (size_t) (yy_tkn_start - yy_start), (size_t) (yy_tkn_end - yy_start));

    for (char_ptr = yy_tkn_start; char_ptr < yy_tkn_end; char_ptr++) {
        if (char_ptr == yy_end) {
            yy_this_err_obj -> yy_err_puts("EOF");
            break;
            }
        else if (*char_ptr == '\n') {
            yy_this_err_obj -> yy_err_puts("\\n");
            }
        else if (*char_ptr == '\r') {
            yy_this_err_obj -> yy_err_puts("\\r");
            }
        else if (*char_ptr == '\t') {
            yy_this_err_obj -> yy_err_puts("\\t");
            }
        else {
            yy_this_err_obj -> yy_err_printf("%c ", *char_ptr);
            }
        }

//  display the lookahead state and character

    switch(yy_lhead_state) {

        case(yy_buf_lhead_state_not_read_):
            yy_this_err_obj -> yy_err_puts("\"\nlhead state=not read  ");
            break;

        case(yy_buf_lhead_state_read_):
            yy_this_err_obj -> yy_err_puts("\"\nlhead state=read  ");
            break;

        case(yy_buf_lhead_state_nterm_only_):
            yy_this_err_obj -> yy_err_puts("\"\nlhead state=nterm only  ");
            break;

        case(yy_buf_lhead_state_read_nterm_):
            yy_this_err_obj -> yy_err_puts("\"\nlhead state=read nterm  ");
            break;

        default:
            yy_this_err_obj -> yy_err_printf("\"\nunknown lhead state=%d  ", 
                yy_lhead_state);
            break;
        }

    if (yy_lhead_char == EOF) {
        yy_this_err_obj -> yy_err_puts("lhead=EOF  \"");
        }
    else if (yy_lhead_char == '\n') {
        yy_this_err_obj -> yy_err_puts("lhead=\\n  \"");
        }
    else if (yy_lhead_char == '\r') {
        yy_this_err_obj -> yy_err_puts("lhead=\\r  \"");
        }
    else if (yy_lhead_char == '\t') {
        yy_this_err_obj -> yy_err_puts("lhead=\\t  \"");
        }
    else {
        yy_this_err_obj -> yy_err_printf("lhead=%c  \"", 
            yy_lhead_char);
        }

//  display up to 20 chars of additional lookahead 

    for (char_ptr = yy_tkn_end; 
         char_ptr < yy_end && char_ptr < yy_tkn_end + 20; char_ptr++) {
        if (*char_ptr == '\n') {
            yy_this_err_obj -> yy_err_puts("\\n");
            }
        else if (*char_ptr == '\r') {
            yy_this_err_obj -> yy_err_puts("\\r");
            }
        else if (*char_ptr == '\t') {
            yy_this_err_obj -> yy_err_puts("\\t");
            }
        else {
            yy_this_err_obj -> yy_err_printf("%c ", *char_ptr);
            }
        }

//  display other information about the buffer 

    yy_this_err_obj -> yy_err_printf(
    "\"\nsize %u (%u read %u in current token %u unlexed) grow by %u\n",
        yy_size, (size_t) (yy_end - yy_start), 
        (size_t) (yy_tkn_end - yy_tkn_start), (size_t) (yy_end - yy_tkn_end), 
        yy_grow_by);

    yy_this_err_obj -> yy_err_printf(
       "buffer fields:    start %p  read %p  end %p\n",
        yy_start, yy_read_ptr, yy_end);

    yy_this_err_obj -> yy_err_printf("lineno %-6d tkn start %p   end %p\n\n",
        yy_lineno, yy_tkn_start, yy_tkn_end);

}   // yy_buf_dmp
