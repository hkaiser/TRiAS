
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_errst
//
//  FILE DESCRIPTION:     error stream object support 
//
//  MODIFICATION HISTORY:
//
//    12/21/98   cc	  fixed some parameter declarations that were hiding
//			  member variables.
//    06/03/98   cc       needed yy_err_puts.
//    09/11/97   bz       moved fstream to header for ANSI C++ header support.
//    07/07/97   bz/cc    added flush to yy_err_puts() to handle
//			  case where program dies immediately.
//    10/20/93   bz/cc    moved syntax assists to error stream object.
//    04/09/93   bz       initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_errst_c_
#define yy_errst_c_ 1
#endif /* yy_errst_c_ */

#include "yy_stdlb.h"
#include "yy_asrt.h"
#include "yy_errst.h"


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_stream_obj::yy_err_stream_obj(...)
//
//  This is the constructor for the stream error object whose parameter 
//  list corresponds to the fields in the stream error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_stream_obj::yy_err_stream_obj(
        yy_errmsg_dflt_ptr      yy_new_err_tbl,
        int                     yy_new_err_tbl_max,
        yy_synamsg_dflt_ptr     yy_new_syna_tbl,
        int                     yy_new_syna_tbl_max,
        ostream                 *yy_stream
    ) :
    yy_err_gen_obj(yy_new_err_tbl, yy_new_err_tbl_max, yy_new_syna_tbl,
        yy_new_syna_tbl_max),
    yy_err_stream(yy_stream)
{
}   // constructor for yy_err_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_stream_obj::~yy_err_stream_obj()
//
//  This is the destructor for the stream error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_stream_obj::~yy_err_stream_obj()
{
}  // destructor for yy_err_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   void yy_err_exit(void)
//
//  yy_err_exit() displays the summary of how many times yy_err_report()
//  was called for warnings and/or errors and exits after displaying the 
//  summary.  This version redefines the version from the generic error
//  class to use exit() to terminate the program.
//
//  After displaying this final message, the program is terminated by calling
//  exit() with the severity of the highest severity error ever displayed.
//
//////////////////////////////////////////////////////////////////////////////

void yy_err_stream_obj::yy_err_exit()    
{

//  call the generic error object to display the error exit message

    yy_err_gen_obj::yy_err_exit();

//  exit the program with the severity as the program status code

    exit(yy_err_severity);

}   // yy_err_exit


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_puts(yy_text)
//
//  yy_err_puts() displays a string onto the error output stream.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_stream_obj::yy_err_puts(
    const char *yy_text)
{

    *yy_err_stream << yy_text << flush;
    
    return(yy_err_stream->good());

}   // yy_err_puts


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_dflt_obj::yy_err_dflt_obj(...)
//
//  This is the constructor for the default error object whose parameter 
//  list corresponds to the fields in the default error object.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_dflt_obj::yy_err_dflt_obj(
        yy_errmsg_dflt_ptr      yy_new_err_tbl,
        int                     yy_new_err_tbl_max,
        yy_synamsg_dflt_ptr     yy_new_syna_tbl,
        int                     yy_new_syna_tbl_max,
        ostream                 *yy_stream
    ) :
    yy_err_stream_obj(yy_new_err_tbl, yy_new_err_tbl_max, yy_new_syna_tbl, 
        yy_new_syna_tbl_max, yy_stream),
    yy_cache_root(NULL),
    yy_syna_cache_root(NULL),
    yy_filename(NULL),
    yy_syna_filename(NULL)
{
}   // constructor for yy_err_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_err_dflt_obj::~yy_err_dflt_obj()
//
//  This is the destructor for the default error object.  It deletes the
//  filename and error cache if present.
//
//////////////////////////////////////////////////////////////////////////////

yy_err_dflt_obj::~yy_err_dflt_obj()
{

//  if there is an alternate error message filename, delete it

    if (yy_filename != NULL) {
        delete [] yy_filename;
        yy_filename = NULL;
        }

//  if there is an alternate syntax assist filename, delete it
 
    if (yy_syna_filename != NULL) {
        delete [] yy_syna_filename;
        yy_syna_filename = NULL;
        }

//  if there is an error cache, delete it

    if (yy_cache_root != NULL) {
        yy_cache_root -> yy_errmsg_cache_delete_all();
        yy_cache_root = NULL;
        }

//  if there is a syntax assist cache, delete it

    if (yy_syna_cache_root != NULL) {
        yy_syna_cache_root -> yy_synamsg_cache_delete_all();
        yy_syna_cache_root = NULL;
        }

}   // destructor for yy_err_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_ptr yy_err_lookup_msg(yy_err_num)
//
//  yy_err_lookup_msg() is called to retrieve an error message by number
//  in the error message table.  It returns a pointer to the error message
//  which was found or NULL if the error message was not found.      
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_ptr yy_err_dflt_obj::yy_err_lookup_msg(int yy_err_num)
{

    yy_errmsg_cache_ptr cur_err_ptr, par_err_ptr;
    ifstream            *alterr_fstream;
    int                 cur_yy_err_num, severity;
    char                *yy_fmt, *yy_fmt_begin, *temp_filename;
    int                 ch;

//  look for the error message in the cache of already reported error messages

    cur_err_ptr = yy_cache_root;
    par_err_ptr = NULL;

    while (cur_err_ptr != NULL) {
        par_err_ptr = cur_err_ptr;
        if (yy_err_num < cur_err_ptr -> yy_errmsg_number()) {
            cur_err_ptr = par_err_ptr -> yy_errmsg_less_ptr();
            }
        else if (cur_err_ptr -> yy_errmsg_number() < yy_err_num) {
            cur_err_ptr = par_err_ptr -> yy_errmsg_more_ptr();
            }
        else {
            return(cur_err_ptr);
            }
        } // while cache entries to look at 

//  it did not find the error message in the cache of already reported 
//  error messages.  if the user specified an alternate errorfile, search
//  for the error message in the user specified errorfile

    if (yy_filename != NULL) {
        
//  open and close the errorfile each time to position 
//  to the beginning of the file 

        alterr_fstream = new ifstream(yy_filename, ios::in);

        if (alterr_fstream == NULL || ! (*alterr_fstream)) {
            temp_filename = yy_filename;
            yy_filename = NULL;
            yy_err_report(13, temp_filename); // error file not found
            alterr_fstream = NULL;
            }

        if (alterr_fstream != NULL) {

//  position past comment to 1st error message

            ch = alterr_fstream -> get();

            while (ch != EOF && ch != '\n') {
                ch = alterr_fstream -> get();
                }

//  get error number following the newline and reset current character

            *alterr_fstream >> cur_yy_err_num;
            ch = ' ';

//  search errorfile for matching error number, continue looping while no
//  match and not yet end-of-file

            while (alterr_fstream -> good() && cur_yy_err_num != yy_err_num) {

//  ignore the rest of error message

                while (ch != EOF && ch != '\n') {       
                    ch = alterr_fstream -> get();
                    }
                *alterr_fstream >> cur_yy_err_num;
                ch = ' ';
                }

            if (cur_yy_err_num == yy_err_num) {

                yy_fmt = yy_fmt_begin = new char[yy_err_fmt_max_];

                if (yy_fmt == NULL) {
                    yy_err_report(406);
                    yy_assert_fail("space unavailable from new", __FILE__, 
                        __LINE__);
                    return(NULL);
                    }

                *alterr_fstream >> severity;
                ch = ' ';

//  collect the error message

                while (ch != EOF && ch != '\n') {   

                    ch = alterr_fstream -> get();

//  if there is a backslash, need to check the next character

                    if (ch != '\\') {  
                        *yy_fmt++ = (char)ch;
                        }

                    else {
                        ch = alterr_fstream -> get();

                        switch (ch) {

                            case 'n':
                                *yy_fmt++ = '\n';
                                break;

                            case 't':
                                *yy_fmt++ = '\t';
                                break;

                            default:
                                *yy_fmt++ = (char)ch;
                                break;

                            }  // switch on char following backslash

                        }  // have a backslash

                    }   // collect error message

                *yy_fmt = '\0';

                delete alterr_fstream;
                alterr_fstream = NULL;

                cur_err_ptr = new yy_errmsg_cache_obj(
                    yy_err_num, severity, yy_fmt_begin, 
                    NULL, NULL, par_err_ptr);

                if (cur_err_ptr == NULL) {
                    yy_err_report(406);
                    yy_assert_fail("space unavailable from new", __FILE__, 
                        __LINE__);
                    return(NULL);
                    }

                if (par_err_ptr == NULL) {
                    yy_cache_root = cur_err_ptr;
                    }
                else if (yy_err_num < par_err_ptr -> yy_errmsg_number()) {
                    par_err_ptr-> yy_errmsg_less_ptr(cur_err_ptr);
                    }
                else {
                    par_err_ptr -> yy_errmsg_more_ptr(cur_err_ptr);
                    }

                return(cur_err_ptr);

                }  // have a match

            }  // have an errorfile

        }  // user specified errorfile 

//  if not found in error file, use the built-in error message table

    return(yy_err_gen_obj::yy_err_lookup_msg(yy_err_num));

}   // yy_err_lookup_msg


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   int yy_err_puts(yy_text)
//
//  yy_err_puts() displays a string onto the error output stream.
//
//////////////////////////////////////////////////////////////////////////////

int yy_err_dflt_obj::yy_err_puts(
    const char *yy_text)
{

    cout << flush;
    
    *yy_err_stream << yy_text << flush;
    
    return(yy_err_stream->good());

}   // yy_err_puts


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_ptr yy_err_lookup_syna_msg(yy_syna_num)
//
//  yy_err_lookup_syna_msg() is called to retrieve an syntax assist by number
//  in the syntax assist table.  It returns a pointer to the syntax assist
//  which was found or NULL if the syntax assist was not found.      
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_ptr yy_err_dflt_obj::yy_err_lookup_syna_msg(int yy_syna_num)
{

    yy_synamsg_cache_ptr    cur_syna_ptr, par_syna_ptr;
    ifstream                *alterr_fstream;
    int                     cur_yy_syna_num;
    char                    *yy_fmt, *yy_fmt_begin, *temp_filename;
    int                     ch;

//  look for the syntax assist in the cache of already reported syntax assists

    cur_syna_ptr = yy_syna_cache_root;
    par_syna_ptr = NULL;

    while (cur_syna_ptr != NULL) {
        par_syna_ptr = cur_syna_ptr;
        if (yy_syna_num < cur_syna_ptr -> yy_synamsg_number()) {
            cur_syna_ptr = par_syna_ptr -> yy_synamsg_less_ptr();
            }
        else if (cur_syna_ptr -> yy_synamsg_number() < yy_syna_num) {
            cur_syna_ptr = par_syna_ptr -> yy_synamsg_more_ptr();
            }
        else {
            return(cur_syna_ptr);
            }
        } // while cache entries to look at 

//  it did not find the syntax assist in the cache of already reported 
//  syntax assists.  if the user specified an alternate errorfile, search
//  for the syntax assist in the user specified errorfile

    if (yy_syna_filename != NULL) {
        
//  open and close the errorfile each time to position 
//  to the beginning of the file 

        alterr_fstream = new ifstream(yy_syna_filename, ios::in);

        if (alterr_fstream == NULL || ! (*alterr_fstream)) {
            temp_filename = yy_syna_filename;
            yy_syna_filename = NULL;
            yy_err_report(13, temp_filename); // error file not found
            alterr_fstream = NULL;
            }

        if (alterr_fstream != NULL) {

//  position past comment to 1st syntax assist

            ch = alterr_fstream -> get();

            while (ch != EOF && ch != '\n') {
                ch = alterr_fstream -> get();
                }

//  get error number following the newline and reset current character

            *alterr_fstream >> cur_yy_syna_num;
            ch = ' ';

//  search errorfile for matching error number, continue looping while no
//  match and not yet end-of-file

            while (alterr_fstream -> good() && cur_yy_syna_num != yy_syna_num) {

//  ignore the rest of syntax assist

                while (ch != EOF && ch != '\n') {       
                    ch = alterr_fstream -> get();
                    }
                *alterr_fstream >> cur_yy_syna_num;
                ch = ' ';
                }

            if (cur_yy_syna_num == yy_syna_num) {

                yy_fmt = yy_fmt_begin = new char[yy_err_fmt_max_];

                if (yy_fmt == NULL) {
                    yy_err_report(406);
                    yy_assert_fail("space unavailable from new", __FILE__, 
                        __LINE__);
                    return(NULL);
                    }

                ch = ' ';

//  collect the syntax assist

                while (ch != EOF && ch != '\n') {   

                    ch = alterr_fstream -> get();

//  if there is a backslash, need to check the next character

                    if (ch != '\\') {  
                        *yy_fmt++ = (char)ch;
                        }

                    else {
                        ch = alterr_fstream -> get();

                        switch (ch) {

                            case 'n':
                                *yy_fmt++ = '\n';
                                break;

                            case 't':
                                *yy_fmt++ = '\t';
                                break;

                            default:
                                *yy_fmt++ = (char)ch;
                                break;

                            }  // switch on char following backslash

                        }  // have a backslash

                    }   // collect syntax assist

                *yy_fmt = '\0';

                delete alterr_fstream;
                alterr_fstream = NULL;

                cur_syna_ptr = new yy_synamsg_cache_obj(
                    yy_syna_num, yy_fmt_begin, 
                    NULL, NULL, par_syna_ptr);

                if (cur_syna_ptr == NULL) {
                    yy_err_report(406);
                    yy_assert_fail("space unavailable from new", __FILE__, 
                        __LINE__);
                    return(NULL);
                    }

                if (par_syna_ptr == NULL) {
                    yy_syna_cache_root = cur_syna_ptr;
                    }
                else if (yy_syna_num < par_syna_ptr -> yy_synamsg_number()) {
                    par_syna_ptr-> yy_synamsg_less_ptr(cur_syna_ptr);
                    }
                else {
                    par_syna_ptr -> yy_synamsg_more_ptr(cur_syna_ptr);
                    }

                return(cur_syna_ptr);

                }  // have a match

            }  // have an errorfile

        }  // user specified errorfile 

//  if not found in error file, use the built-in syntax assist table

    return(yy_err_gen_obj::yy_err_lookup_syna_msg(yy_syna_num));

}   // yy_err_lookup_syna_msg


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_cache_obj::yy_errmsg_cache_obj()
//
//  This is the constructor for the cached error message object.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_cache_obj::yy_errmsg_cache_obj() :
    yy_errmsg_dflt_obj()
{
}   // constructor for yy_errmsg_cache_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_cache_obj::yy_errmsg_cache_obj(...)
//
//  This is the constructor for the cached error message object.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_cache_obj::yy_errmsg_cache_obj(
    int                     yy_new_errmsg_number, 
    int                     yy_new_errmsg_severity, 
    char                    *yy_new_errmsg_format,
    yy_errmsg_cache_ptr     yy_new_less_ptr,
    yy_errmsg_cache_ptr     yy_new_more_ptr,
    yy_errmsg_cache_ptr     yy_new_par_ptr
        ) :
    yy_errmsg_dflt_obj(
        yy_new_errmsg_number, yy_new_errmsg_severity, yy_new_errmsg_format),
    yy_less_ptr(yy_new_less_ptr),
    yy_more_ptr(yy_new_more_ptr),
    yy_par_ptr(yy_new_par_ptr)
    
{
}   // constructor for yy_errmsg_cache_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_cache_obj::~yy_errmsg_cache_obj()
//
//  This is the destructor for the cached error message object.
//
//////////////////////////////////////////////////////////////////////////////

yy_errmsg_cache_obj::~yy_errmsg_cache_obj()
{

//  if there is a format, delete it

    if (yy_errmsg_fmt != NULL) {
        delete [] yy_errmsg_fmt;
        yy_errmsg_fmt = NULL;
        }

}   // destructor for yy_errmsg_cache_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_errmsg_cache_delete_all()
//
//  yy_errmsg_cache_delete_all() deletes all the error messages cache objects
//  in an error message cache.
//
//////////////////////////////////////////////////////////////////////////////

void yy_errmsg_cache_obj::yy_errmsg_cache_delete_all()
{

//  delete the part of the cache in the left sub-tree 

    if (yy_less_ptr != NULL) {
        yy_less_ptr -> yy_errmsg_cache_delete_all();
        }
//  delete the part of the cache in the right sub-tree 

    if (yy_more_ptr != NULL) {
        yy_more_ptr -> yy_errmsg_cache_delete_all();
        }

//  delete this node itself

    delete this;

}

//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_cache_obj::yy_synamsg_cache_obj()
//
//  This is the constructor for the cached syntax assist object.
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_cache_obj::yy_synamsg_cache_obj() :
    yy_synamsg_dflt_obj()
{
}   // constructor for yy_synamsg_cache_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_cache_obj::yy_synamsg_cache_obj(...)
//
//  This is the constructor for the cached syntax assist object.
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_cache_obj::yy_synamsg_cache_obj(
    int                     yy_new_synamsg_number, 
    char                    *yy_new_synamsg_message,
    yy_synamsg_cache_ptr    yy_new_less_ptr,
    yy_synamsg_cache_ptr    yy_new_more_ptr,
    yy_synamsg_cache_ptr    yy_new_par_ptr
        ) :
    yy_synamsg_dflt_obj(
        yy_new_synamsg_number, yy_new_synamsg_message),
    yy_less_ptr(yy_new_less_ptr),
    yy_more_ptr(yy_new_more_ptr),
    yy_par_ptr(yy_new_par_ptr)
    
{
}   // constructor for yy_synamsg_cache_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_cache_obj::~yy_synamsg_cache_obj()
//
//  This is the destructor for the cached syntax assist object.
//
//////////////////////////////////////////////////////////////////////////////

yy_synamsg_cache_obj::~yy_synamsg_cache_obj()
{

//  if there is a message, delete it

    if (yy_synamsg_msg != NULL) {
        delete [] yy_synamsg_msg;
        yy_synamsg_msg = NULL;
        }

}   // destructor for yy_synamsg_cache_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_synamsg_cache_delete_all()
//
//  yy_synamsg_cache_delete_all() deletes all the syntax assist cache objects
//  in a syntax assist cache.
//
//////////////////////////////////////////////////////////////////////////////

void yy_synamsg_cache_obj::yy_synamsg_cache_delete_all()
{

//  delete the part of the cache in the left sub-tree 

    if (yy_less_ptr != NULL) {
        yy_less_ptr -> yy_synamsg_cache_delete_all();
        }
//  delete the part of the cache in the right sub-tree 

    if (yy_more_ptr != NULL) {
        yy_more_ptr -> yy_synamsg_cache_delete_all();
        }

//  delete this node itself

    delete this;

}

