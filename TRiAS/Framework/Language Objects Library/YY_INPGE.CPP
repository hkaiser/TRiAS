
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_inpge
//
//  FILE DESCRIPTION:     input getc object for input from a file or stdin
//                        using getc()
//
//  MODIFICATION HISTORY:
//
//    01/04/99	 bz/cc	  Removed yy_no_myref_inlines_ as it didn't work with
//			  several compilers.
//    06/24/98   cc       pick up yy_inp_dmp parameter change from rev 2.1
//			  solaris version -- a hiding problem
//    05/18/98   cc	  set yy_filename to new rather than using 
//			  yy_inp_filename which does a strlen
//    			  also check for null yy_new_paths when searching
//			  paths.
//    05/08/98   bz       prevent reference to yy_myref.h when compiling LOL.
//    12/12/97   cc       filename is now freed if yy_inp_is_file could
//                        not open buffer.
//    03/25/96   bz/cc    added non-suffix and path versions of inp_is_file.
//    08/06/95   bz/cc    removed copying of buffer into input object since
//                        setting yy_inp_cur_lex(NULL) already does it and
//                        doing it twice turns the first copy into a memory
//                        leak.
//    04/06/94   bz       added yy_inp_cur_offset().
//    01/12/94   bz       ensure adequate buffer space in yy_inp_buf_fill().
//    11/08/93   cc       changed semantics relating to input, lexer, and
//                        buffer object connections so the buffer pointer
//                        is no longer set to NULL on a close but rather
//                        set to point back to the lexer's buffer.  (fixes
//                        eofa).  
//    09/29/93   bz/cc    close the input object in this destructor, because
//                        the base destructor will not call this objects close
//                        function (as that would require a virtual call).
//    04/19/93   bz/cc    native C++ rewrite of the input (file) object.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_inp_getc_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdef.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_inp.h"
#include "yy_inpge.h"
#include "yy_lex.h"
#include "yy_trace.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_getc_obj::yy_inp_getc_obj()
//
//  This is the no argument constructor for the input getc object 
//  which lexes and parses input using getc.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_getc_obj::yy_inp_getc_obj() :
    yy_inp_obj(),
    yy_fp(NULL)
{
}   // no argument constructor for yy_inp_getc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_getc_obj::yy_inp_getc_obj(yy_this_err_ptr)
//
//  This is the constructor typically used when creating an input getc
//  object which is the initial input object for a given lexer and parser.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_getc_obj::yy_inp_getc_obj(
    yy_err_ptr  yy_this_err_ptr
    ) :
    yy_inp_obj(yy_this_err_ptr),
    yy_fp(NULL)
{
}   // constructor for yy_inp_getc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   nesting constructor yy_inp_getc_obj::yy_inp_getc_obj(
//                                      yy_this_inp_ptr)
//
//  This is the constructor for the input getc object whose parameter list 
//  is a pointer to an input object.  This constructor is typically used when
//  creating an input getc object which is used to process a file input
//  nested within another input (an include file).
//
//  This constructor creates a new input getc object which becomes the top
//  input object on the stack.  The new input object is associated with the 
//  same lexer and error object as "yy_this_inp_ptr" which is now the previous
//  entry on the stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_getc_obj::yy_inp_getc_obj(
    yy_inp_ptr  yy_this_inp_ptr
    ) :
    yy_inp_obj(yy_this_inp_ptr),
    yy_fp(NULL)
{
}   // nesting constructor for yy_inp_getc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_inp_getc_obj::~yy_inp_getc_obj()
//
//  This is the destructor for the input getc object.  It closes the
//  input.  Deletions such as the object specific filename data member and 
//  the buffer itself occur in the destructor of the input base class.
//  
//////////////////////////////////////////////////////////////////////////////

yy_inp_getc_obj::~yy_inp_getc_obj() 
{

//  if the input is still open close it

    if (yy_buf_state & yy_inp_buf_state_open_) {
        yy_inp_close(yy_true);
        }

}   // destructor for yy_inp_getc_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_fill()
//
//  yy_inp_buf_fill() redefines the function in the base input object
//  which refills the input buffer.  
//
//  yy_inp_buf_fill() fills the input buffer using a getc call.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_getc_obj::yy_inp_buf_fill()
{

//  ensure there is space left in the buffer -- if not, there are 2 cases.
//  If one token fills the entire buffer, grow the buffer.  Otherwise, just
//  move the current token to the beginning of the buffer.

    if (yy_this_buf_obj -> yy_buf_size() <= 
            (size_t)(yy_this_buf_obj -> yy_buf_end() 
            - yy_this_buf_obj -> yy_buf_start())) {
        if (yy_this_buf_obj -> yy_buf_tkn_start() == 
            yy_this_buf_obj -> yy_buf_start()) {
            yy_this_buf_obj -> yy_buf_extend();
            yy_this_buf_obj -> yy_buf_reset();
            }
        else {
            yy_this_buf_obj -> yy_buf_wrap();
            yy_this_buf_obj -> yy_buf_reset();
            }
       }

//  if the EOF has already been read, set the lookahead character to EOF

    if (yy_this_buf_obj -> yy_buf_eof_read()) {
        yy_this_buf_obj -> yy_buf_lhead_char((int)EOF);
        }

//  otherwise, attempt to get another character with getc

    else {
        yy_this_buf_obj -> yy_buf_lhead_char(getc(yy_fp));
        yy_this_buf_obj -> yy_buf_read(yy_this_buf_obj -> yy_buf_end());

//  if getc returned EOF, mark the buffer as containing an EOF

        if (yy_this_buf_obj -> yy_buf_lhead_char() == EOF) { 
            yy_this_buf_obj -> yy_buf_eof_read(yy_true); 
            }

//  if getc returned a valid character, update the buffer pointers

        else {
            *yy_this_buf_obj -> yy_buf_read() = 
                char(yy_this_buf_obj -> yy_buf_lhead_char());
            yy_this_buf_obj -> yy_buf_end(
                yy_this_buf_obj -> yy_buf_end() + 1);
            }
        }

}   // yy_inp_buf_fill


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_restore()
//
//  yy_inp_buf_restore() redefines the restoring of a saved input buffer.
//  This version re-does the getc from the C FILE to restore the lookahead
//  character, which was saved in yy_inp_buf_save().
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_getc_obj::yy_inp_buf_restore()
{ 

//  un-mark the input object as nested

    yy_buf_state &= ~yy_inp_buf_state_nested_;

//  re-establish the lexer buffer association

    if (yy_buf_state & yy_inp_buf_state_lexer_) {
        yy_this_buf_obj -> yy_buf_lhead_char(getc(yy_fp));
        }

}   // yy_inp_buf_restore


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_save()
//
//  yy_inp_buf_save() redefines the saving of the input buffer.  It saves
//  it in its own local copy as the base input object did.  The difference
//  is we do an ungetc on the lookahead character.  This makes sure the
//  lookahead character is in the C FILE in case the file is also being
//  read from somewhere else.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_getc_obj::yy_inp_buf_save()
{ 

//  mark the input object as being nested

    yy_buf_state |= yy_inp_buf_state_nested_;

//  if the input object is using the lexer as its buffer, make it
//  use its own copy of the buffer and give the lexer an empty buffer

    if (yy_buf_state & yy_inp_buf_state_lexer_) {

        assert(yy_this_lex_obj != NULL);

//  we're 1 character ahead of ourselves so we need to save the look-ahead 
//  character away before pushing the new file 

        ungetc(yy_this_buf_obj -> yy_buf_lhead_char(), yy_fp);

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
//                           input getc object should be freed.
//                           (note that sometimes the filename isn't freed
//                           so the location print function still has access
//                           to the filename for error messages).
//              
//  yy_inp_close() calls the input close function in the base object to
//  de-allocate the buffer and filename.  In addition, it also closes the 
//  file itself.  It returns true if the stream successfully deleted and 
//  false otherwise.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_getc_obj::yy_inp_close(
    yy_boolean     yy_free_the_filename)
{

//  de-allocate the buffer via the input close function in the base object

    if (!yy_inp_obj::yy_inp_close(yy_free_the_filename)) {
        return(yy_false);
        }

//  close the file itself

    fclose(yy_fp);
    yy_fp = NULL;

    return(yy_true);

}   // yy_inp_close


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   unsigned long yy_inp_cur_offset()
//
//  yy_inp_cur_offset() returns the offset in the input getc of the 
//  character currently being lexed.
//
//////////////////////////////////////////////////////////////////////////////

unsigned long yy_inp_getc_obj::yy_inp_cur_offset()
{

//  return the value of the getc specific function cast to the generic type

    return((unsigned long)yy_inp_cur_offset_as_getcpos());

}   // yy_inp_cur_offset


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_dmp(yy_err_ptr yy_new_err_obj, 
//                      const char *yy_dmp_title)
//
//  yy_new_err_obj  is an error object where this dump is to be displayed.
//           
//  yy_dmp_title     a character string to identify the dump.
//
//  yy_inp_dmp() displays the values of the input getc object data members.  
//  It is a debugging function we used when we were developing Yacc++.  We
//  have included this function as a member of the input getc object in case 
//  you need to dump the internal state of the file being lexed and parsed.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_getc_obj::yy_inp_dmp(
    yy_err_ptr   yy_new_err_obj, 
    const char   *yy_dmp_title)
{

//  use the failsafe error object, if no error object to dump to

    if (yy_new_err_obj == NULL) {
        yy_new_err_obj = yy_err_failsafe_obj();
        }

//  display the title for the dump, if any

    if (yy_dmp_title != NULL) {
        yy_new_err_obj -> yy_err_printf(" %s\n", yy_dmp_title);
        }

//  dump the fields specific to this object

    yy_new_err_obj -> yy_err_printf("pointer: %d\n", yy_fp);

//  call the base object dump routine

    yy_inp_obj::yy_inp_dmp(yy_new_err_obj, NULL);

}   // yy_inp_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_file(yy_new_filename)
//
//  yy_new_filename     is the name of the file to open.
//
//  yy_inp_is_file() opens the input file specified by yy_new_filename.  
//  If that filename doesn't exist, an error is reported.
//
//  When the file is opened, it allocates the input buffer.
//
//  yy_inp_is_file() returns true if the open was successful and false if
//  an error occurred.
//              
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_getc_obj::yy_inp_is_file(
    const char  *yy_new_filename)
{

//  if this input getc object is already open, we cannot open it again until
//  it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  use the new filename as the filename of the object

    yy_inp_filename(yy_new_filename);

//  open the file for input

    yy_fp = fopen(yy_inp_filename(), "r");

//  if the filename itself did not yield a successful open, report an error

    if (yy_fp == NULL) {
        yy_err_report(2, yy_inp_filename()); 
	yy_inp_filename(NULL);
        return(yy_false);
        }

//  if we make it here, we successfully opened the file.
//  now, allocate the input buffer.

    if (!yy_inp_open_buf()) {  // allocate the input buffer
	yy_inp_filename(NULL);
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_file


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_file(yy_new_filename, yy_new_suffixes)
//
//  yy_new_filename     is the name of the file to open.
//
//  yy_new_suffixes[]   is the list of suffixes to append to the filename.
//
//  yy_inp_is_file() opens the input file specified by yy_new_filename.  
//  It appends the suffixes onto "yy_new_filename" and attempts to open 
//  the file.  If none of the filenames with the appended suffixes exist, 
//  it attempts to open the filename as is.  If that filename also doesn't 
//  exist, an error is reported.
//
//  When the file is opened, it allocates the input buffer.
//
//  yy_inp_is_file() returns true if the open was successful and false if
//  an error occurred.
//              
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_getc_obj::yy_inp_is_file(
    const char  *yy_new_filename,
    const char  *yy_new_suffixes[])
{
    char        *temp_ptr;
    int         i;
    size_t      filename_len, longest_suffix_length;

//  if this input getc object is already open, we cannot open it again until
//  it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  if the input getc object has a filename already, delete it

    yy_inp_filename(NULL);

//  reset the file pointer

    yy_fp = NULL;

//  obtain the length of the desired filename prefix

    filename_len = strlen(yy_new_filename);

//  obtain the length of the longest suffix

    i = 0;
    longest_suffix_length = 0;

    if (yy_new_suffixes != NULL) {
        while (yy_new_suffixes[i] != NULL && *yy_new_suffixes[i] != '\0') {
            if (strlen(yy_new_suffixes[i]) > longest_suffix_length) {
                longest_suffix_length = strlen(yy_new_suffixes[i]);
                }
            ++i;
            }
        }

//  allocate space for the the maximum length we could possibly need
//  for the name of the file including a suffix

    yy_filename = new char[(longest_suffix_length + filename_len + 1)];

    if (yy_inp_filename() == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(yy_false);
        }

//  try opening with suffixes first, then by filename itself, if need be

    i = 0;

    strcpy(yy_filename, yy_new_filename);
    temp_ptr = yy_filename + filename_len;

    if (yy_new_suffixes != NULL) {
        while (yy_fp == NULL && yy_new_suffixes[i] != NULL &&
               *yy_new_suffixes[i] != '\0') {      
            strcpy(temp_ptr, yy_new_suffixes[i]);
            yy_fp = fopen(yy_inp_filename(), "r");
            ++i;
            }
        }   // try suffixes

//  if the suffixes did not yield a successful open, try the filename itself

    if (yy_fp == NULL) {
        *temp_ptr = '\0';
        yy_fp = fopen(yy_inp_filename(), "r");
        }

//  if the filename itself did not yield a successful open, report an error

    if (yy_fp == NULL) {
        yy_err_report(2, yy_inp_filename()); 
	yy_inp_filename(NULL);
        return(yy_false);
        }

//  if we make it here, we successfully opened the file.
//  now, allocate the input buffer.

    if (!yy_inp_open_buf()) {  // allocate the input buffer
	yy_inp_filename(NULL);
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_file


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_file(yy_new_filename, yy_new_suffixes,
//                                        yy_new_paths)
//
//  yy_new_filename     is the name of the file to open.
//
//  yy_new_suffixes[]   is the list of suffixes to append to the filename.
//
//  yy_new_paths[]	is the list of directories to prepend to the filename.
//
//  yy_inp_is_file() opens the input file specified by yy_new_filename.  
//  It first looks in the current directory, then in each directory
//  specified in the paths list.  It appends the suffixes onto 
//  "yy_new_filename" and attempts to open the file.  If none of the 
//  filenames with the appended suffixes exist, it attempts to open the 
//  filename as is.  If that filename also doesn't exist, an error is 
//  reported.
//
//  When the file is opened, it allocates the input buffer.
//
//  yy_inp_is_file() returns true if the open was successful and false if
//  an error occurred.
//              
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_getc_obj::yy_inp_is_file(
    const char  *yy_new_filename,
    const char  *yy_new_suffixes[],
    const char  *yy_new_paths[])
{
    char        *temp_ptr;
    int         i, j;
    size_t      filename_len, longest_suffix_length, longest_path_length;

//  if this input getc object is already open, we cannot open it again until
//  it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  if the input getc object has a filename already, delete it

    yy_inp_filename(NULL);

//  reset the file pointer

    yy_fp = NULL;

//  obtain the length of the desired filename

    filename_len = strlen(yy_new_filename);

//  obtain the length of the longest suffix

    i = 0;
    longest_suffix_length = 0;

    if (yy_new_suffixes != NULL) {
        while (yy_new_suffixes[i] != NULL && *yy_new_suffixes[i] != '\0') {
            if (strlen(yy_new_suffixes[i]) > longest_suffix_length) {
                longest_suffix_length = strlen(yy_new_suffixes[i]);
                }
            ++i;
            }
        }

//  obtain the length of the longest path

    i = 0;
    longest_path_length = 0;

    if (yy_new_paths != NULL) {
        while (yy_new_paths[i] != NULL && *yy_new_paths[i] != '\0') {
            if (strlen(yy_new_paths[i]) > longest_path_length) {
                longest_path_length = strlen(yy_new_paths[i]);
                }
            ++i;
            }
        }

//  allocate space for the the maximum length we could possibly need
//  for the name of the file including a path and a suffix.

    yy_filename = new char[(longest_suffix_length + longest_path_length + 
			    filename_len + 2)];

    if (yy_inp_filename() == NULL) {  // new() failure
        yy_err_report(406);
        yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
        return(yy_false);
        }

// try opening with suffixes first, then by filename itself, if need be

    i = 0;

    strcpy(yy_filename, yy_new_filename);
    temp_ptr = yy_filename + filename_len;

    if (yy_new_suffixes != NULL) {
        while (yy_fp == NULL && yy_new_suffixes[i] != NULL &&
               *yy_new_suffixes[i] != '\0') {      
            strcpy(temp_ptr, yy_new_suffixes[i]);
            yy_fp = fopen(yy_inp_filename(), "r");
            ++i;
            }
        }   // try suffixes

//  if the suffixes did not yield a successful open, try the filename itself

    if (yy_fp == NULL) {
        *temp_ptr = '\0';
        yy_fp = fopen(yy_inp_filename(), "r");
        }

//  if the filename itself did not yield a successful open, search the paths

    if (yy_new_paths != NULL) {

	j = 0;

	while (yy_fp == NULL && yy_new_paths[j] != NULL &&
	       *yy_new_paths[j] != '\0') {      

	    i = 0;

	    strcpy(yy_filename, yy_new_paths[j]);
	    temp_ptr = yy_filename + strlen(yy_filename);
	    *temp_ptr = '/';
	    temp_ptr++;
	    strcpy(temp_ptr, yy_new_filename);
	    temp_ptr += filename_len;

//  search the suffixes for each path

	    if (yy_new_suffixes != NULL) {
		while (yy_fp == NULL && yy_new_suffixes[i] != NULL &&
		       *yy_new_suffixes[i] != '\0') {      
		    strcpy(temp_ptr, yy_new_suffixes[i]);
		    yy_fp = fopen(yy_inp_filename(), "r");
		    ++i;
		    }
		}   // try suffixes

//  if the suffixes did not yield a successful open, try the filename itself

	    if (yy_fp == NULL) {
		*temp_ptr = '\0';
		yy_fp = fopen(yy_inp_filename(), "r");
		}

	    ++j;
	    }   // try paths
	}
    
//  if the file is still not open, report an error

    if (yy_fp == NULL) {
        yy_err_report(2, yy_inp_filename()); 
	yy_inp_filename(NULL);
        return(yy_false);
        }

//  if we make it here, we successfully opened the file.
//  now, allocate the input buffer.

    if (!yy_inp_open_buf()) {  // allocate the input buffer
	yy_inp_filename(NULL);
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_file


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_stdin()
//
//  yy_inp_is_stdin() uses stdin as the source for input.
//
//  yy_inp_is_stdin() returns true if no errors occurred and false if
//  any error occurred.
//                
//  The file "stdin" is used as the file and a buffer is allocated.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_getc_obj::yy_inp_is_stdin()
{

//  if this input getc object is already open, we cannot open it again until
//  it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  set the fields to indicate <stdin> as the input file

    yy_inp_filename(NULL);
    yy_fp = stdin;

//  abort if we don't recognize <stdin> as an open file.

    if (yy_fp == NULL) {  // error opening given filename
        yy_err_report(2, "<stdin>"); 
        return(yy_false);
        }

//  if we make it here, we successfully opened the file.
//  now, allocate the input buffer.

    if (!yy_inp_open_buf()) {  // allocate the input buffer
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1;

    return(yy_true);

}   // yy_inp_is_stdin


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
//  If the remaining input object on the stack is an input getc object
//  which is open, yy_inp_rewind() resets it to its initial state --
//  the buffer pointing to the beginning of the open file.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_getc_obj::yy_inp_rewind()
{
    yy_inp_ptr  prev_file_obj;      

//  back out of any nested include files

    if (yy_prev_ptr != NULL) {
        prev_file_obj = yy_prev_ptr;
        yy_inp_close(yy_true);
        delete this;
        prev_file_obj -> yy_inp_rewind();
        return;
        }

//  ok, we're through the recursive closes and we now know we are at
//  the bottom of the stack and the remaining input object is an input
//  getc object, which we rewind.

//  if the input getc object is closed, we do nothing

    if (!(yy_buf_state & yy_inp_buf_state_open_)) {
        return;
        }

//  if the input getc object is open, we rewind it to its initial state

    fseek(yy_fp, 0L, 0);
        
//  set the buffer pointers back to the initial state, as if we had
//  just opened this file

    yy_this_buf_obj -> yy_buf_init();

    yy_this_buf_obj -> yy_buf_lineno() = 1;

}   // yy_inp_rewind


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_loc_print_self(yy_this_err)
//
//  yy_this_err    the error object on which the location is to be displayed
//
//  yy_loc_print_self() redefines the default location printing function.
//  The default displays nothing.  For an input getc object, the filename
//  and the current line number is the location being tracked and displayed
//  instead of nothing.  If this input getc object is reading from stdin,
//  <stdin> is displayed in place of a filename.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_getc_obj::yy_loc_print_self(
    yy_err_ptr yy_this_err
    )
{

//  if there is no filename, use <stdin> as the filename

    if (yy_inp_filename() == NULL) { 

//  if there is no buffer, use ??? as the line number

        if (yy_this_buf_obj == NULL) {
            return(yy_this_err -> yy_err_puts("<stdin> ???: "));
            }

        return(yy_this_err -> yy_err_printf("<stdin>, line %d: ", 
            yy_this_buf_obj -> yy_buf_lineno()));
        }

//  if there is no buffer, use ??? as the line number

    if (yy_this_buf_obj == NULL) {
        return(yy_this_err -> yy_err_printf("\"%s\", ???: ",
            yy_inp_filename()));
        }

    return(yy_this_err -> yy_err_printf("\"%s\", line %d: ", 
        yy_inp_filename(), yy_this_buf_obj -> yy_buf_lineno()));

}   // yy_loc_print_self
