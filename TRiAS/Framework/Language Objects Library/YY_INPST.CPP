
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-99, Compiler Resources, Inc.
//
//  FILENAME:             yy_inpst
//
//  FILE DESCRIPTION:     input stream object for input from a C++ stream
//                        -- supports istream, ifstream, and istrstream.
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
//    01/22/98   bz/cc    changed yy_open_mode to int so that ios::nocreate 
//			  could be or'ed in.
//    12/12/97   cc       filename is now freed if yy_inp_is_fstream could
//                        not open buffer.
//    03/25/96   bz/cc    added suffix and path versions of inp_is_fstream.
//    04/06/94   bz       added yy_inp_is_opened_stream() for parsing an 
//                        already open stream and yy_inp_cur_offset() for 
//                        getting the position in the stream.  Added open 
//                        mode parameter to yy_inp_is_fstream().
//    01/12/94   bz       ensure adequate buffer space in yy_inp_buf_fill().
//    09/29/93   bz/cc    close the input object in this destructor, because
//                        the base destructor will not call this objects close
//                        function (as that would require a virtual call).
//    06/02/93   bz/cc    native C++ rewrite of the input (file) object.
//
//////////////////////////////////////////////////////////////////////////////

#include "lolpre.h"		// #HK961211

#define yy_inp_stream_c_ 1

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_stdef.h"
#include "yy_stdlb.h"
#include "yy_strng.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_trace.h"
#include "yy_inpst.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_stream_obj::yy_inp_stream_obj()
//
//  This is the no argument constructor for the input stream object 
//  which lexes and parses input from a C++ stream.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_stream_obj::yy_inp_stream_obj() :
    yy_inp_obj(),
    yy_stream(NULL),
    yy_delete_stream(yy_false)
{
}   // no argument constructor for yy_inp_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   constructor yy_inp_stream_obj::yy_inp_stream_obj(
//                  yy_this_err_ptr)
//
//  This is the constructor typically used when creating an input stream
//  object which is the initial input object for a given lexer and parser.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_stream_obj::yy_inp_stream_obj(
    yy_err_ptr  yy_this_err_ptr
    ) :
    yy_inp_obj(yy_this_err_ptr),
    yy_stream(NULL),
    yy_delete_stream(yy_false)
{
}   // constructor for yy_inp_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   nesting constructor yy_inp_stream_obj::yy_inp_stream_obj(
//                                      yy_this_inp_ptr)
//
//  This is the constructor for the input stream object whose parameter list 
//  is a pointer to an input object.  This constructor is typically used when
//  creating an input stream object which is used to process input nested
//  within another input (for example, an include file or a macro string).
//
//  This constructor creates a new input stream object which becomes the top
//  input object on the stack.  The new input object is associated with the 
//  same lexer and error object as "yy_this_inp_ptr" which is now the previous
//  entry on the stack.
//
//////////////////////////////////////////////////////////////////////////////

yy_inp_stream_obj::yy_inp_stream_obj(
    yy_inp_ptr  yy_this_inp_ptr
    ) :
    yy_inp_obj(yy_this_inp_ptr),
    yy_stream(NULL),
    yy_delete_stream(yy_false)
{
}   // nesting constructor for yy_inp_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   destructor yy_inp_stream_obj::~yy_inp_stream_obj()
//
//  This is the destructor for the input stream object.  It closes the input.
//  It deletes the stream data member here if present.  Deletions such as 
//  the object specific filename data member and the buffer itself occur in
//  the destructor of the input base class.
//  
//////////////////////////////////////////////////////////////////////////////

yy_inp_stream_obj::~yy_inp_stream_obj() 
{

//  if the input is still open close it

    if (yy_buf_state & yy_inp_buf_state_open_) {
        yy_inp_close(yy_true);
        }

//  delete the stream if we should -- don't delete stream for cin

    if (yy_stream != NULL && yy_delete_stream) {
        delete yy_stream;
        yy_stream = NULL;
        }

}   // destructor for yy_inp_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_inp_buf_fill()
//
//  yy_inp_buf_fill() redefines the function in the base input object
//  which refills the input buffer.  
//
//  yy_inp_buf_fill() fills the input buffer using get().
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_stream_obj::yy_inp_buf_fill()
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

//  otherwise, attempt to get another character with get()

    else {
        yy_this_buf_obj -> yy_buf_lhead_char(yy_stream -> get());
        yy_this_buf_obj -> yy_buf_read(yy_this_buf_obj -> yy_buf_end());

//  if get() returned EOF, mark the buffer as containing an EOF

        if (yy_this_buf_obj -> yy_buf_lhead_char() == EOF) { 
            yy_this_buf_obj -> yy_buf_eof_read(yy_true); 
            }

//  if get() returned a valid character, update the buffer pointers

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
//  FUNCTION:   yy_boolean yy_inp_close(yy_free_the_filename)
//
//  yy_free_the_filename     true if the filename stored within the 
//                           input stream object should be freed.
//                           (note that sometimes the filename isn't freed
//                           so the location print function still has access
//                           to the filename for error messages).
//              
//  yy_inp_close() calls the input close function in the base object to
//  de-allocate the buffer and filename.  In addition, it also deletes the 
//  stream itself.  It returns true if the stream successfully deleted and 
//  false otherwise.
//
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_close(
    yy_boolean     yy_free_the_filename)
{

//  de-allocate the buffer via the input close function in the base object

    if (!yy_inp_obj::yy_inp_close(yy_free_the_filename)) {
        return(yy_false);
        }

//  delete the stream itself

    if (yy_stream != NULL && yy_delete_stream) {
        delete yy_stream;
        yy_stream = NULL;
        }

    return(yy_true);

}   // yy_inp_close


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   unsigned long yy_inp_cur_offset()
//
//  yy_inp_cur_offset() returns the offset in the input stream of the 
//  character currently being lexed.
//
//////////////////////////////////////////////////////////////////////////////

unsigned long yy_inp_stream_obj::yy_inp_cur_offset()
{

//  return the value of the stream specific function cast to the generic type

    return((unsigned long)yy_inp_cur_offset_as_streampos());

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
//  yy_inp_dmp() displays the values of the input stream object data members.
//  It is a debugging function we used when we were developing Yacc++.  We
//  have included this function as a member of the input stream object in case
//  you need to dump the internal state of the stream being lexed and parsed.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_stream_obj::yy_inp_dmp(
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

//  call the base object dump routine

    yy_inp_obj::yy_inp_dmp(yy_new_err_obj, NULL);

}   // yy_inp_dmp


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_cin()
//
//  yy_inp_is_cin() uses cin as the source for input.
//
//  yy_inp_is_cin() returns true if no errors occurred and false if
//  any error occurred.
//                
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_is_cin()
{

//  if this input stream object is already open, we cannot open it again
//  until it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  for CIN, use NULL as the filename (for error messages etc.)

    yy_inp_filename(NULL);

//  use the C++ stream cin for input

    yy_stream = &cin;
    yy_delete_stream = yy_false;

//  abort if we don't recognize cin as an open stream

    if ((yy_stream == NULL) || (!(*yy_stream))) {  // open failed
        yy_err_report(2, "cin"); 
        return(yy_false);
        }

//  now, allocate the input buffer

    if (!yy_inp_open_buf()) {  // allocate the input buffer
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_cin


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_fstream(yy_new_filename, yy_open_mode)
//
//  yy_inp_is_fstream() opens the input file specified by yy_new_filename.  
//  When the file is opened, it allocates the input buffer.
//
//  yy_inp_is_fstream() returns true if no errors occurred, and false if
//  any error occurred.
//                
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_is_fstream(
        const char        *yy_new_filename,
        int    		  yy_open_mode)
{

//  if this input stream object is already open, we cannot open it again 
//  until it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  use the stream name as the filename of the object

    yy_inp_filename(yy_new_filename);

//  open the file for input via the C++ file stream

    yy_stream = new ifstream(yy_new_filename, yy_open_mode);
    yy_delete_stream = yy_true;

//  if the open failed report an error 

    if ((yy_stream == NULL) || (!(*yy_stream))) {  // open failed
        yy_err_report(2, yy_new_filename); 
	yy_inp_filename(NULL);
        return(yy_false);
        }

//  now, allocate the input buffer

    if (!yy_inp_open_buf()) {  // allocate the input buffer
	yy_inp_filename(NULL);
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_fstream

        
//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_fstream(yy_new_filename, yy_new_suffixes,
//                                           yy_open_mode)
//
//  yy_new_filename     is the name of the file to open.
//
//  yy_new_suffixes[]   is the list of suffixes to append to the filename.
//
//  yy_open_mode        is the mode to open the file, defaults to READ ONLY
//
//  yy_inp_is_fstream() opens the input file specified by yy_new_filename.  
//  It appends the suffixes onto "yy_new_filename" and attempts to open 
//  the file.  If none of the filenames with the appended suffixes exist, 
//  it attempts to open the filename as is.  If that filename also doesn't 
//  exist, an error is reported.
//
//  When the file is opened, it allocates the input buffer.
//
//  yy_inp_is_fstream() returns true if no errors occurred, and false if
//  any error occurred.
//                
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_is_fstream(
    const char        *yy_new_filename,
    const char 	      *yy_new_suffixes[],
    int		      yy_open_mode)
{
    char        *temp_ptr;
    int         i;
    size_t      filename_len, longest_suffix_length;

//  if this input stream object is already open, we cannot open it again 
//  until it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  reset the stream

    yy_stream = NULL;
    yy_delete_stream = yy_true;

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
//  for the name of the file including a suffix.

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
        while ((yy_stream == NULL  || (!(*yy_stream))) && 
	       yy_new_suffixes[i] != NULL &&
               *yy_new_suffixes[i] != '\0') {      
            strcpy(temp_ptr, yy_new_suffixes[i]);
            yy_stream = new ifstream(yy_inp_filename(), yy_open_mode);
            ++i;
            }
        }   // try suffixes

//  if the suffixes did not yield a successful open, try the filename itself

    if (yy_stream == NULL || (!(*yy_stream))) {
        *temp_ptr = '\0';
        yy_stream = new ifstream(yy_inp_filename(), yy_open_mode);
        }

//  if the open failed report an error 

    if ((yy_stream == NULL) || (!(*yy_stream))) {  // open failed
        yy_err_report(2, yy_new_filename); 
	yy_inp_filename(NULL);
        return(yy_false);
        }

//  now, allocate the input buffer

    if (!yy_inp_open_buf()) {  // allocate the input buffer
	yy_inp_filename(NULL);
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_fstream

        
//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_fstream(yy_new_filename, yy_new_suffixes,
//                                           yy_new_paths, yy_open_mode)
//
//  yy_new_filename     is the name of the file to open.
//
//  yy_new_suffixes[]   is the list of suffixes to append to the filename.
//
//  yy_new_paths[]	is the list of directories to prepend to the filename.
//
//  yy_open_mode        is the mode to open the file, defaults to READ ONLY
//
//  yy_inp_is_fstream() opens the input file specified by yy_new_filename.  
//  It first looks in the current directory, then in each directory
//  specified in the paths list.  It appends the suffixes onto 
//  "yy_new_filename" and attempts to open the file.  If none of the 
//  filenames with the appended suffixes exist, it attempts to open the 
//  filename as is.  If that filename also doesn't exist, an error is 
//  reported.
//
//  When the file is opened, it allocates the input buffer.
//
//  yy_inp_is_fstream() returns true if no errors occurred, and false if
//  any error occurred.
//                
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_is_fstream(
    const char        *yy_new_filename,
    const char        *yy_new_suffixes[],
    const char        *yy_new_paths[],
    int    	      yy_open_mode)
{
    char        *temp_ptr;
    int         i, j;
    size_t      filename_len, longest_suffix_length, longest_path_length;

//  if this input stream object is already open, we cannot open it again 
//  until it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  if the input file object has a filename already, delete it

    yy_inp_filename(NULL);

//  reset the unit number

    yy_stream = NULL;
    yy_delete_stream = yy_true;

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

//  try opening with suffixes first, then by filename itself, if need be

    i = 0;

    strcpy(yy_filename, yy_new_filename);
    temp_ptr = yy_filename + filename_len;

    if (yy_new_suffixes != NULL) {
        while (((yy_stream == NULL) || (!(*yy_stream))) && 
	       yy_new_suffixes[i] != NULL &&
               *yy_new_suffixes[i] != '\0') {      
            strcpy(temp_ptr, yy_new_suffixes[i]);
            yy_stream = new ifstream(yy_inp_filename(), yy_open_mode);
            ++i;
            }
        }   // try suffixes

//  if the suffixes did not yield a successful open, try the filename itself

    if ((yy_stream == NULL) || (!(*yy_stream))) {
        *temp_ptr = '\0';
        yy_stream = new ifstream(yy_inp_filename(), yy_open_mode);
        }

//  if the filename itself did not yield a successful open, search the paths

    if (yy_new_paths != NULL) {

	j = 0;

	while (((yy_stream == NULL) || (!(*yy_stream))) && 
	       yy_new_paths[j] != NULL &&
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
		while (((yy_stream == NULL) || (!(*yy_stream))) && 
		       yy_new_suffixes[i] != NULL &&
		       *yy_new_suffixes[i] != '\0') {      
		    strcpy(temp_ptr, yy_new_suffixes[i]);
		    yy_stream = new ifstream(yy_inp_filename(), yy_open_mode);
		    ++i;
		    }
		}   // try suffixes

//  if the suffixes did not yield a successful open, try the filename itself

	    if ((yy_stream == NULL) || (!(*yy_stream))) {
		*temp_ptr = '\0';
		yy_stream = new ifstream(yy_inp_filename(), yy_open_mode);
		}

	    ++j;
	    }   // try paths
	}
    
//  if the file is still not open, report an error

    if ((yy_stream == NULL) || (!(*yy_stream))) {  // open failed
        yy_err_report(2, yy_inp_filename()); 
	yy_inp_filename(NULL);
        return(yy_false);
        }

//  now, allocate the input buffer

    if (!yy_inp_open_buf()) {  // allocate the input buffer
	yy_inp_filename(NULL);
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_fstream

        
//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_opened_stream(yy_new_stream)
//
//  yy_inp_is_opened_stream() uses an already opened stream as the source 
//  for input.
//
//  yy_inp_is_opened_stream() returns true if no errors occurred, and false 
//  if any error occurred.
//                
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_is_opened_stream(
        istream     *yy_new_stream)
{

//  if this input stream object is already open, we cannot open it again
//  until it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  use NULL as the filename as we don't know if this stream is a file or what

    yy_inp_filename(NULL);

//  if the stream is not open, report an error

    if ((yy_new_stream == NULL) || (!(*yy_new_stream))) {  // no stream?
        yy_err_report(2, "stream"); 
        return(yy_false);
        }

//  use the open stream and the default is for the user to destroy it

    yy_stream = yy_new_stream;
    yy_delete_stream = yy_false;

//  now, allocate the input buffer

    if (!yy_inp_open_buf()) {  // allocate the input buffer
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_opened_stream


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_is_strstream(yy_string_ptr, yy_strlen)
//
//  yy_inp_is_strstream() uses the string as the source for input.
//
//  yy_inp_is_strstream() returns true if no errors occurred, and false if
//  any error occurred.
//                
//////////////////////////////////////////////////////////////////////////////

yy_boolean yy_inp_stream_obj::yy_inp_is_strstream(
        char        *yy_string_ptr,
        int         yy_strlen)
{

//  if this input stream object is already open, we cannot open it again
//  until it has been closed

    if (yy_buf_state & yy_inp_buf_state_open_) {
        return(yy_false);
        }

//  for C++ string streams, we use NULL as the filename

    yy_inp_filename(NULL);

//  open the C++ string stream for input

    yy_stream = new istrstream(yy_string_ptr, yy_strlen);
    yy_delete_stream = yy_true;

//  if the open failed report an error 

    if ((yy_stream == NULL) || (!(*yy_stream))) {  // open failed
        yy_err_report(2, ""); 
        return(yy_false);
        }

//  now, allocate the input buffer

    if (!yy_inp_open_buf()) {  // allocate the input buffer
        return(yy_false);
        }

    yy_this_buf_obj -> yy_buf_lineno() = 1; 

    return(yy_true);

}   // yy_inp_is_strstream


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
//  If the remaining input object on the stack is an input stream object
//  which is open, yy_inp_rewind() resets it to its initial state --
//  the buffer pointing to the beginning of the open stream.
//
//////////////////////////////////////////////////////////////////////////////

void yy_inp_stream_obj::yy_inp_rewind()
{
    yy_inp_ptr  prev_file_obj;      

//  close nested input objects on the stack (if any)

    if (yy_prev_ptr != NULL) {
        prev_file_obj = yy_prev_ptr;
        yy_inp_close(yy_true);
        delete this;
        prev_file_obj -> yy_inp_rewind();
        return;
        }

//  ok, we're through the recursive closes and we now know we are at
//  the bottom of the stack and the remaining input object is an input
//  stream object.

//  if the input stream object is closed, we do nothing

    if (!(yy_buf_state & yy_inp_buf_state_open_)) {
        return;
        }

//  if the input stream object is open, we rewind it to its initial state

    yy_stream -> seekg(0, ios::beg);

//  set the buffer pointers back to the initial state, as if we had
//  just opened this stream

    yy_this_buf_obj -> yy_buf_init();

    yy_this_buf_obj -> yy_buf_lineno() = 1;

}   // yy_inp_rewind
