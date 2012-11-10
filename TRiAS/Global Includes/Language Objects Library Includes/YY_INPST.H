
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_inpst.h
//  
//  FILE DESCRIPTION:     header file with the input object class declarations
//                        specific to reading from C++ streams including
//                        istreams, ifstreams, and/or istrstreams.
//  
//  CLASS HIERARCHY:
//
//         +----------------------+          +----------------------+
//         |        input         | -------> |     buffer class     |
//         | generic base class   | links to |      (yy_buf.h)      |
//         +----------------------+          +----------------------+
//                   | derives      
//                   |
//         +--------------------------------------------------------+
//         |                  |                  |                  |
// +---------------+ +----------------+ +----------------+ +----------------+
// |  input file   | |  input stream  | |   input getc   | |  input string  |
// |     class     | |     class      | |     class      | |     class      |
// | (yy_inpfi.h)  | |  (yy_inpst.h)  | |  (yy_inpge.h)  | |   (yy_inp.h)   |
// +---------------+ +----------------+ +----------------+ +----------------+
//         |
// +-----------------+
// |   input file    |
// | with signatures |
// |  (yy_signc.h)   |
// +-----------------+
//        
//  MODIFICATION HISTORY:
//  
//    01/22/98   bz/cc    changed yy_open_mode to int so that ios::nocreate 
//			  could be or'ed in.
//    07/07/97   bz/cc    support for ANSI C++ headers + 9/11/97.
//   			  Also conditionalized strstream.h/strstrea.h.
//    03/25/96   bz/cc    added suffix and path versions of inp_is_fstream.
//    06/12/95   cc       Replaced <strstream.h> with <strstrea.h>.
//    04/06/94   bz       Added yy_inp_cur_offset() and relatives.  Also 
//                        added yy_inp_is_opened_stream() and an open mode
//                        on yy_inp_is_fstream().
//    06/02/93   bz/cc    native C++ rewrite of the input (file) object.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_inp_st_h_
#define yy_inp_st_h_

#ifdef yy_use_ansicxx_hdrs_
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;
#else
#include <iostream.h>
#include <fstream.h>
#ifdef yy_short_filenames_
#include <strstrea.h>
#else
#include <strstream.h>
#endif /* yy_short_filenames_ */
#endif /* yy_use_ansicxx_hdrs_ */

#include "yy_inp.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_inp_stream_ptr   is a typedef which defines a pointer to an input 
//                      object using a C++ stream as input.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_inp_stream_obj   *yy_inp_stream_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_inp_stream_obj
//
//  The yy_inp_stream_obj is the input object which processes input from
//  a C++ stream -- istreams, ifstreams, and/or istrstreams.
//
//  CONFIGURATION CONSTANTS:
//
//  PUBLIC FUNCTIONS:
//
//  yy_inp_stream_obj()     constructors for an input stream object.
//                                  
//  ~yy_inp_stream_obj()    destructor for an input stream object.
//
//  yy_inp_buf_fill()       refills the input buffer by reading from the
//                          stream using get.
//
//  yy_inp_close()          closes the input stream and de-allocates the
//                          input buffer.
//
//  yy_inp_cur_offset()     gets the offset from the beginning of this 
//                          input of the character being lexed.
//
//  yy_inp_cur_offset_as_streampos() 
//                          gets the offset from the beginning of this 
//                          input of the character being lexed.
//
//  yy_inp_cur_stream()     gets the C++ stream currently opened for input.
//
//  yy_inp_delete_stream([yy_boolean])
//                          gets (or sets with an argument) whether the C++
//                          stream object will be deleted when the input 
//                          stream object is closed.
//
//  yy_inp_dmp()            displays the values of the input stream object
//                          data members.
//
//  yy_inp_is_cin()         uses cin as the input file.
//
//  yy_inp_is_fstream()     uses an ifstream as the input file.
//
//  yy_inp_is_opened_stream() uses an already opened stream as the input.
//
//  yy_inp_is_strstream()   uses an istrstream as the input string.
//
//  yy_inp_rewind()         rewinds to the beginning of the bottom file on
//                          the include file stack.
//
//  INTERNAL STATE:  
//
//  yy_stream           is the pointer to the C++ input stream.
//
//  yy_delete_stream    is the flag for whether the stream is to be deleted.
//                      Currently this is true only for cin.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_inp_stream_obj : public yy_inp_obj {
    
 public:

    yy_inp_stream_obj();

    yy_inp_stream_obj(yy_err_ptr yy_this_err_ptr);

    yy_inp_stream_obj(yy_inp_ptr yy_this_inp_ptr);

    virtual ~yy_inp_stream_obj();

    virtual void yy_inp_buf_fill();

    virtual yy_boolean yy_inp_close(yy_boolean yy_free_the_filename);

    unsigned long yy_inp_cur_offset();

    inline streampos yy_inp_cur_offset_as_streampos();

    inline istream *yy_inp_cur_stream();

    inline yy_boolean yy_inp_delete_stream();

    inline yy_boolean yy_inp_delete_stream(yy_boolean yy_new_delete_stream);

    virtual void yy_inp_dmp(
        yy_err_ptr   yy_this_err_obj, 
        const char   *yy_dmp_title
        );

    virtual yy_boolean yy_inp_is_cin();
        
    virtual yy_boolean yy_inp_is_fstream(
        const char        *yy_new_filename,
        int    		  yy_open_mode = ios::in | ios::nocreate
        );

    virtual yy_boolean yy_inp_is_fstream(
        const char        *yy_new_filename,
        const char        *yy_suffixes[],
        int    		  yy_open_mode = ios::in | ios::nocreate
        );

    virtual yy_boolean yy_inp_is_fstream(
        const char        *yy_new_filename,
        const char        *yy_suffixes[],
        const char        *yy_paths[],
        int    		  yy_open_mode = ios::in | ios::nocreate
        );

    virtual yy_boolean yy_inp_is_opened_stream(
        istream *yy_new_stream);
        
    virtual yy_boolean yy_inp_is_strstream(
        char        *yy_string_ptr,
        int         yy_strlen
        );      

    virtual void yy_inp_rewind();

 protected:

    istream         *yy_stream;
    yy_boolean      yy_delete_stream;

    };  // yy_inp_stream_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the input stream object, defined
//  above.
//
//////////////////////////////////////////////////////////////////////////////

inline streampos yy_inp_stream_obj::yy_inp_cur_offset_as_streampos()
{ 
    if (yy_stream) {
#ifdef yy_streampos_minus_needs_temp_
	streampos result;

        result = yy_stream->tellg();
        result -= yy_this_buf_obj->yy_buf_end() - yy_this_buf_obj->yy_buf_tkn_end();
        return(result);
#else
        return(yy_stream->tellg() - 
               (yy_this_buf_obj->yy_buf_end() -
                yy_this_buf_obj->yy_buf_tkn_end()));
#endif
        }
    else {
        return(-1);
        }
}

inline istream *yy_inp_stream_obj::yy_inp_cur_stream()
    { return(yy_stream); }

inline yy_boolean yy_inp_stream_obj::yy_inp_delete_stream()
    { return(yy_delete_stream); }

inline yy_boolean yy_inp_stream_obj::yy_inp_delete_stream(
        yy_boolean yy_new_delete_stream)
    { return(yy_delete_stream = yy_new_delete_stream); }

#endif  /* yy_inp_st_h_ */
