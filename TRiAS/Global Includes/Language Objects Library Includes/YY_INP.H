            
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_inp.h
//  
//  FILE DESCRIPTION:     header file with input object class declarations
//                        (input objects were file objects at previous revs).
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
// +------------------+
// |   input file     |
// | with signatures  |
// | (see yy_signc.h) |
// +------------------+
//        
//  NOTE:  there is no input object abstract base class.  The purpose of
//  abstract base classes is to provide virtual function definitions that
//  allow easy redefinitions matching an interface.  The input object is
//  so key to lexer performance, that the performance penalty for virtual
//  functions for this object was considered unacceptable.   
//
//  MODIFICATION HISTORY:
//  
//    09/01/98   bz       added single parameter yy_inp_is_string() to match
//                        LOL documentation.
//    04/06/94   bz       added yy_inp_cur_offset() and relatives.
//    03/31/94   bz       made yy_err_report() non-virtual as compilers such
//                        as Watcom don't accept ... parameters of virtuals.
//    03/14/94   bz       gave the string input class its own yy_inp_close().
//    01/20/94   bz       made yy_inp_filename() part of the base class
//                        for generic input object access.
//    10/05/93   bz       added compatibility macro for yy_prev_file_ptr.
//    04/19/93   bz/cc    native C++ rewrite of input (file) object.
//    04/05/93   bz       type yy_err_obj_ptr is now named yy_err_ptr and
//                        new forwarding scheme for yy_err_report().
//    03/22/93   bz       added yy_export for use of classes in a DLL.
//    09/24/92   bz       Extended charset support needed additional casts
//                        on Sparc.
//    09/10/92   bz       changed yy_buf_unread_len(), yy_lex_len() and
//                        other pointer differences to cast return value
//                        to int as pointer differences default to long
//                        on the PC rather than int as they do on the Sparc.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    12/15/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_inp_h_
#define yy_inp_h_

#include "yy_ansi.h"
#include "yy_bool.h"
#include "yy_err.h"
#include "yy_buf.h"

#include "yy_stdio.h"
#include "yy_strng.h"
#include "yy_asrt.h"

//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_inp_ptr           is a typedef which defines a pointer to an input 
//                       object.  This references the generic base class.
//
//                       (There is no abstract base class so this is the
//                       pointer type to use when passing input objects
//                       when you don't know their specific class.)
//
//  yy_inp_string_ptr    is a typedef which defines a pointer to an input 
//                       string object. 
//
//  yy_lex_ptr          is a typedef which defines a pointer to a lexer
//                      object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_inp_obj        *yy_inp_ptr;
typedef class yy_export yy_inp_string_obj *yy_inp_string_ptr;

typedef class yy_export yy_lex_obj        *yy_lex_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_inp_obj
//
//  The yy_inp_obj is the generic base class for the input object.
//  It represents the input to be lexed and parsed and is very closely
//  associated with a lexer object.
//
//  CONFIGURATION CONSTANTS:
//
//  yy_inp_buf_state_init_
//                      is the value of yy_inp_buf_state when a non-nested
//                      input object is created, but has not been opened nor
//                      associated with a lexer.
//
//  yy_inp_buf_state_open_
//                      is the value of yy_inp_buf_state when a non-nested
//                      input object is created and opened, but has not been
//                      associated with a lexer.
//
//  yy_inp_buf_state_lexer_
//                      is the value of yy_inp_buf_state when a non-nested
//                      input object is created and associated with a lexer,
//                      but has not been opened.
//
//  yy_inp_buf_state_lexer_and_open_
//                      is the value of yy_inp_buf_state when a non-nested
//                      input object is created, opened, and associated with 
//                      a lexer.
//
//  yy_inp_buf_state_nested_
//                      is the value of yy_inp_buf_state when a nested
//                      input object is created, but has not been opened nor
//                      associated with a lexer.
//
//  yy_inp_buf_state_nested_open_
//                      is the value of yy_inp_buf_state when a nested
//                      input object is created and opened, but has not been
//                      associated with a lexer.
//
//  yy_inp_buf_state_nested_lexer_
//                      is the value of yy_inp_buf_state when a nested
//                      input object is created and associated with a lexer,
//                      but has not been opened.
//
//  yy_inp_buf_state_nested_lexer_and_open_
//                      is the value of yy_inp_buf_state when a nested
//                      input object is created, opened, and associated with 
//                      a lexer.
//
//  PUBLIC FUNCTIONS:
//
//  ~yy_inp_obj()       destructor for an input object.
//
//  yy_inp_attached()   returns true if the input object corresponds to an
//                      open input source.
//
//  yy_inp_buf_fill()   refills the input buffer.
//
//  yy_inp_close()      closes the input object by de-allocating the buffer.
//                      Note: most derived objects should call this function
//                      as part of their close operation.
//
//  yy_inp_cur_buf([yy_buf_ptr]) 
//                      gets (or sets with an argument) the buffer object
//                      associated with this input object.
//
//  yy_inp_cur_err([yy_err_ptr]) 
//                      gets (or sets with an argument) the error object
//                      associated with this input object.
//
//  yy_inp_cur_lex([yy_lex_ptr]) 
//                      gets (or sets with an argument) the lexer object
//                      associated with this input object.
//
//  yy_inp_cur_offset() gets the offset from the beginning of this input of
//                      the character being lexed.
//
//  yy_inp_dmp()        produces a diagnostic display (symbolic dump) of the
//                      contents of an input object. 
//
//  yy_inp_filename([char *])
//                      gets (or sets with an argument) the current name 
//                      associated with the input.  This is NULL in this
//                      abstract base class, but has meaning in many derived
//                      input objects.  Note this is informational only.  
//                      Setting it causes no action -- for example, it does 
//                      not cause a new file to be opened.
//
//  yy_inp_not_attached()
//                      returns true if the input object does not have
//                      an open input source.
//
//  yy_inp_prev_ptr([yy_inp_ptr])
//                      gets (or sets with an argument) the pointer to the
//                      input object which represents the input which is next 
//                      to the top of the stack.  It returns NULL if the 
//                      stack does not contain another input stream.
//
//  yy_inp_rewind()     re-establishes the input object to the "rewound" 
//                      state.
//
//  yy_inp_valid_obj()  supports yy_inp_valid_ptr(inp_ptr) by returning TRUE 
//                      for a valid input object.
//
//  yy_err_report()     routes error messages from this input object to
//                      the associated error object.  Otherwise, the errors
//                      would go to the default error object.
//
//  yy_loc_print_self() displays the "filename" and the line number in the 
//                      buffer object associated with this input object as the
//                      location.  This redefines the behavior from the 
//                      default location object.
//                      
//  INTERNAL FUNCTIONS:  
//
//  yy_inp_obj()        constructors for an input object.
//                                  
//  yy_inp_buf_restore()
//                      restores a saved input buffer.      
//
//  yy_inp_buf_save()   saves the input buffer.
//
//  yy_inp_open_buf()   opens the input object by allocating the input buffer.
//
//  yy_inp_open_buf_finish_setup() 
//                      sets the end of buffer pointer and the lookahead
//                      character once the first characters in the buffer 
//                      have been read in.
//
//  INTERNAL STATE:  
//
//  yy_filename         is a pointer to the name of the current input.
//
//  yy_this_buf_obj     pointer to the buffer object associated with this 
//                      input object.
//
//  yy_this_err_obj     pointer to the error object associated with this 
//                      input object.
//
//  yy_this_lex_obj     pointer to the lexer object associated with this
//                      input object.
//
//  yy_prev_ptr         is a pointer to the previous yy_inp_obj in the stack
//                      of input objects.  This is for processing nested
//                      input.   For example, lexing from include files.
//
//  yy_buf_state        is the state of the pointer to the associated buffer
//                      object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_inp_obj : public yy_loc_obj {

 protected:
 
    enum yy_inp_buf_state_enum { 
        yy_inp_buf_state_init_ = 0,
        yy_inp_buf_state_open_ = 1,
        yy_inp_buf_state_lexer_ = 2,
        yy_inp_buf_state_lexer_and_open_ = 3,
        yy_inp_buf_state_nested_ = 4,
        yy_inp_buf_state_nested_open_ = 5,
        yy_inp_buf_state_nested_lexer_ = 6,
        yy_inp_buf_state_nested_lexer_and_open_ = 7
        };

 public:

    virtual ~yy_inp_obj();

    inline yy_boolean yy_inp_attached();

    virtual void yy_inp_buf_fill() = 0;

    virtual yy_boolean yy_inp_close(yy_boolean);
    
    inline yy_buf_ptr yy_inp_cur_buf();

    inline yy_buf_ptr yy_inp_cur_buf(yy_buf_ptr yy_new_buf_obj);
        
    inline yy_err_ptr yy_inp_cur_err();

    inline yy_err_ptr yy_inp_cur_err(yy_err_ptr yy_new_err_obj);
        
    inline yy_lex_ptr yy_inp_cur_lex();

    virtual yy_lex_ptr yy_inp_cur_lex(yy_lex_ptr yy_new_lex_obj);
        
    virtual unsigned long yy_inp_cur_offset() = 0;

    virtual void yy_inp_dmp(
        yy_err_ptr   yy_this_err_obj, 
        const char   *yy_dmp_title);

    inline const char *yy_inp_filename();
    
    inline const char *yy_inp_filename(const char *yy_new_filename);
    
    inline yy_boolean yy_inp_not_attached();

    inline yy_inp_ptr &yy_inp_prev_ptr();

    inline yy_inp_ptr yy_inp_prev_ptr(yy_inp_ptr yy_new_prev_ptr);

    virtual void yy_inp_rewind();

    virtual yy_boolean yy_inp_valid_obj();

    int yy_err_report(
        int         yy_err_num,
        ...);

    virtual yy_boolean yy_loc_print_self(yy_err_ptr);

 protected:

    yy_inp_obj();

    yy_inp_obj(yy_err_ptr  yy_this_err_ptr);

    yy_inp_obj(yy_inp_ptr  yy_this_inp_ptr);

    virtual void yy_inp_buf_restore();
    
    virtual void yy_inp_buf_save();
    
    virtual yy_boolean yy_inp_open_buf();
    
    virtual yy_boolean yy_inp_open_buf_finish_setup(int yy_num_new_chars);

    char                *yy_filename;
    yy_buf_ptr          yy_this_buf_obj;
    yy_err_ptr          yy_this_err_obj;
    yy_lex_ptr          yy_this_lex_obj;
    yy_inp_ptr          yy_prev_ptr;
    int                 yy_buf_state;

    };  // yy_inp_obj


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_inp_valid_ptr(yy_this_inp)
//
//  yy_inp_valid_ptr checks the validity of a pointer to a yy_inp_obj.
//  Before calling the virtual function in the input object which performs 
//  the check, it checks here for NULL (to avoid unexpected crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_inp_valid_ptr(
    yy_inp_ptr  yy_this_inp)
{
   if (yy_this_inp != NULL) {
      return(yy_this_inp->yy_inp_valid_obj());       
      }
   else {
      return(yy_false);
      }
   
}  // yy_inp_valid_ptr


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_inp_string_obj
//
//  The yy_inp_string_obj is the input object for lexing and parsing
//  from string input not using C++ string streams.
//
//  PUBLIC FUNCTIONS:
//
//  yy_inp_string_obj()   constructors for an input string object.
//                                  
//  ~yy_inp_string_obj()  destructor for an input string object.
//
//  yy_inp_buf_fill()     parsing from a string doesn't needs refills.
//
//  yy_inp_close()        closes the input string object by marking its
//                        buffer as closed.  (no de-allocation for strings)
//
//  yy_inp_cur_offset()   gets the offset from the beginning of this input
//                        of the character being lexed.
//
//  yy_inp_cur_offset_as_stringpos() 
//                        gets the offset from the beginning of this input
//                        of the character being lexed.
//
//  yy_inp_is_string()    uses a string as the input source.
//
//  yy_inp_rewind()       returns the input object to the "rewound" state.
//
//  yy_loc_print_self()   no location is displayed for an input string object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_inp_string_obj : public yy_inp_obj {
    
 public:

    yy_inp_string_obj();
        
    yy_inp_string_obj(yy_err_ptr yy_this_err);

    yy_inp_string_obj(yy_inp_ptr yy_this_inp_ptr);

    virtual ~yy_inp_string_obj();

    virtual void yy_inp_buf_fill();

    virtual yy_boolean yy_inp_close(yy_boolean);

    unsigned long yy_inp_cur_offset();

    inline size_t yy_inp_cur_offset_as_stringpos();

    virtual yy_boolean yy_inp_is_string(
        char    *yy_string_ptr
        );

    virtual yy_boolean yy_inp_is_string(
        char    *yy_string_ptr,
        int     yy_strlen
        );

    virtual void yy_inp_rewind();

    virtual yy_boolean yy_loc_print_self(yy_err_ptr);

    };  // yy_inp_string_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the base input object, defined above.
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_inp_obj::yy_inp_attached()
    { return(yy_buf_state & yy_inp_buf_state_open_); }

inline yy_buf_ptr yy_inp_obj::yy_inp_cur_buf()
    { return(yy_this_buf_obj); }

inline yy_buf_ptr yy_inp_obj::yy_inp_cur_buf(yy_buf_ptr yy_new_buf_obj)
    { return(yy_this_buf_obj = yy_new_buf_obj); }
        
inline yy_err_ptr yy_inp_obj::yy_inp_cur_err()
    { return(yy_this_err_obj); }

inline yy_err_ptr yy_inp_obj::yy_inp_cur_err(yy_err_ptr yy_new_err_obj)
    { return(yy_this_err_obj = yy_new_err_obj); }
        
inline yy_lex_ptr yy_inp_obj::yy_inp_cur_lex()
    { return(yy_this_lex_obj); }

inline const char *yy_inp_obj::yy_inp_filename()
    { return(yy_filename); }

inline const char *yy_inp_obj::yy_inp_filename(
        const char *yy_new_filename)
    { 
        if (yy_filename != NULL) {
            delete [] yy_filename;
            }
        if (yy_new_filename != NULL) {
            yy_filename = new char[strlen(yy_new_filename) + 1];
            strcpy(yy_filename, yy_new_filename);
            }
        else {
            yy_filename = NULL;
            }
        return(yy_filename); 
    }

inline yy_boolean yy_inp_obj::yy_inp_not_attached()
    { return((yy_buf_state & yy_inp_buf_state_open_) == 0); }

inline yy_inp_ptr &yy_inp_obj::yy_inp_prev_ptr()
    { return(yy_prev_ptr); }

inline yy_inp_ptr yy_inp_obj::yy_inp_prev_ptr(yy_inp_ptr yy_new_prev_ptr)
    { return(yy_prev_ptr = yy_new_prev_ptr); }

inline size_t yy_inp_string_obj::yy_inp_cur_offset_as_stringpos()
{ 
    if (yy_this_buf_obj->yy_buf_start()) {
        return((size_t)(yy_this_buf_obj->yy_buf_tkn_end() - 
               yy_this_buf_obj->yy_buf_start()));
        }
    else {
        return((size_t)(-1));
        }
}


//////////////////////////////////////////////////////////////////////////////
//
//  COMPATIBILITY MACROS:
//
//  For backward compatibility, the following macros preserve the old names.
//
//  yy_buf_fill             ==> calls yy_inp_buf_fill
//
//  yy_cur_filename         ==> calls yy_inp_filename
//
//  yy_file_attached        ==> calls yy_inp_attached
//
//  yy_file_close           ==> calls yy_inp_close
//
//  yy_file_open            ==> calls yy_inp_is_file
//
//  yy_no_file_attached     ==> calls yy_inp_not_attached
//
//  yy_prev_file_ptr        ==> calls yy_inp_prev_ptr
//
//////////////////////////////////////////////////////////////////////////////

#define yy_buf_fill         yy_inp_buf_fill
#define yy_cur_filename     yy_inp_filename
#define yy_file_attached    yy_inp_attached
#define yy_file_close       yy_inp_close
#define yy_file_open        yy_inp_is_file
#define yy_no_file_attached yy_inp_not_attached
#define yy_prev_file_ptr    yy_inp_prev_ptr

#endif /* yy_inp_h_ */
